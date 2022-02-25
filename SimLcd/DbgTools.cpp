#include "SptProject.h"
using namespace spt;

int32 spt::DbgToolsServer::PowerUpIni(int32 Type)
{
	Task::PowerUpIni(Type);
	DbgSimCfg::Instance().PowerUpIni(0);
	if (DbgSimCfg::Instance().EnableGmCrtCheck.Data())
	{
		CheckDbgServerCrt();
	}
	OpenSslLibIni();
	Start();
	return 0;
}

spt::DbgClient::DbgClient()
	:Task("tDbgMain", TaskBasePriority - 5, 1024 * 1024, E_T_FLOAT, E_AuxCore)
{
	signInStep = 0;
}

void spt::DbgClient::LogOn()
{
	uint32 data = 0x12fa990;
	EncryptData(&data, sizeof(data), 16);
	DbgLogOnMsg msg;
	msg.msg.header.version = 1;
	msg.dbgMsg.header.header = 0xd555;
	msg.msg.header.dbgheader.len = sizeof(msg.msg.header) + sizeof(data) + 40;
	MemCpy(msg.msg.buf, &data, sizeof(data));
	if (signIn.SendTo(&msg, msg.msg.header.dbgheader.len, 0) > 0)
	{
		MsTimer timer;
		timer.UpCnt(5000);
		timer.Enable(1);
		timer.Restart();
		while (!timer.Status())
		{
			MsSleep(10);
			uint64 ms;
			if (signIn.RecvFrom(&msg, sizeof(msg), 0) == msg.msg.header.dbgheader.len)
			{
				MemCpy(&ms, msg.msg.buf, sizeof(ms));
				DecryptData(&ms, sizeof(ms), 3);
				char buf[50];
				MemCpy(buf, &ms, sizeof(ms));
				EncryptData(buf, sizeof(ms), 52);
				uint16 crc = Crc16ModBus.AddCrc(buf, sizeof(ms) + 2);
				MemCpy(msg.msg.buf, &crc, sizeof(crc));
				msg.msg.header.dbgheader.len = sizeof(msg.msg.header) + sizeof(buf);
				if (signIn.SendTo(&msg, msg.msg.header.dbgheader.len, 0) > 0)
				{
					taskStep = E_SendCmd;
					break;
				}
				else
				{
					taskStep = E_ClentIni;
				}
			}
		}
		if (timer.Status())
		{
			taskStep = E_ClentIni;
		}
	}
	else
	{
		MsSleep(1000);
		taskStep = E_ClentIni;
	}
}

int32 spt::DbgSimCfg::PowerUpIni(int32 Para)
{
	DataNum = 0;
	EnableDbgServer.Set("EnableDbgServer", 1);
	EnableDbgServer.SetNotes("使用调试服务器");
	AddCfgData(&EnableDbgServer);
	NeedUsrLog.Set("NeedUsrLog", 0);
	NeedUsrLog.SetNotes("使能用户登录");
	AddCfgData(&NeedUsrLog);
	ServerIp.Set("ServerIp", "100.100.100.100");
	AddCfgData(&ServerIp);
	EnableGmssl.Set("EnableGmssl", 1);
	EnableGmssl.SetNotes("使用国密加密");
	AddCfgData(&EnableGmssl);
	EnableGmCrtCheck.Set("EnableGmCrtCheck", 1);
	EnableGmCrtCheck.SetNotes("使能证书自检");
	AddCfgData(&EnableGmCrtCheck);
	GmsslVerifyMode.Set("GmsslVerifyMode", 0);
	GmsslVerifyMode.SetNotes("证书验证方式");
	AddCfgData(&GmsslVerifyMode);
	GmsslLinkMode.Set("GmsslLinkMode", "SM2-WITH-SMS4-SM3");
	GmsslLinkMode.SetNotes("加密方式");
	AddCfgData(&GmsslLinkMode);
	path.Set(CN_CFG_FILE_ROOT);
	name.Set("DbgSim.cfg");

	if ((uint32)ReadAll() != CfgDataNum())
	{
		if (Para == 0)
		{
			SaveAll();
		}
	}
	return 0;
}

DbgSimCfg& spt::DbgSimCfg::Instance()
{
	static DbgSimCfg inst;
	return inst;
}
