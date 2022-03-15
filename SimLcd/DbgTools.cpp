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

void spt::DbgClient::AskConnect(uint16 Cmd)
{
	if (signIn.StartNonBlock() != 0)
	{
		taskStep = E_ClentIni;
		return;
	}
	uint32 data = 0x12fa990;
	EncryptData(&data, sizeof(data), 16);
	DbgLogOnMsg msg;
	msg.msg.header.version = 1;
	msg.dbgMsg.header.header = 0xd555;
	msg.msg.header.dbgheader.len = sizeof(msg.msg.header) + sizeof(data) + 40;
	MemCpy(msg.msg.buf, &data, sizeof(data));
	if (signIn.Send(msg.dbgMsg) > 0)
	{
		MsTimer timer;
		timer.UpCnt(3000);
		timer.Enable(1);
		timer.Restart();
		while (!timer.Status())
		{
			MsSleep(10);
			uint64 ms;
			int32 res = signIn.Recv(msg.dbgMsg);
			if (res > 0)
			{
				MemCpy(&ms, msg.msg.buf, sizeof(ms));
				DecryptData(&ms, sizeof(ms), 3);
				char buf[50];
				MemCpy(buf, &ms, sizeof(ms));
				EncryptData(buf, sizeof(ms), 52);
				uint16 crc = Crc16ModBus.AddCrc(buf, sizeof(ms) + 2);
				MemCpy(msg.msg.buf, &crc, sizeof(crc));
				msg.msg.header.dbgheader.len = sizeof(msg.msg.header) + sizeof(buf);
				if (signIn.Send(msg.dbgMsg) > 0)
				{
					break;
				}
				else
				{
					taskStep = E_ClentIni;
					return;
				}
			}
		}
		if (timer.Status())
		{
			taskStep = E_ClentIni;
			return;
		}
		else
		{
			timer.UpCnt(1000);
			timer.Enable(1);
			timer.Restart();
			while (!timer.Status())
			{
				MsSleep(10);
				int32 res = signIn.Recv(msg.dbgMsg);
				if (res > 0)
				{
					msg.msg.header.version = 1;
					DbgToolsServer::HandshakeMsg hdmsg;
					MemCpy(&hdmsg, msg.msg.buf, sizeof(hdmsg));
					DecryptData(&hdmsg, sizeof(hdmsg), 27);
					isIdCheck = hdmsg.msg[4];
					isPwCheck = hdmsg.msg[5];
					if (StrCmp(DbgSimCfg::Instance().GmsslLinkMode.StrData(), (const char*)&hdmsg.msg[33])
						|| (DbgSimCfg::Instance().GmsslVerifyMode.Data() != hdmsg.msg[3])
						|| (DbgSimCfg::Instance().EnableGmssl.Data() != hdmsg.msg[2])
						)
					{
						DbgSimCfg::Instance().GmsslVerifyMode.SetData(hdmsg.msg[3]);
						DbgSimCfg::Instance().EnableGmssl.SetData(hdmsg.msg[2]);
						DbgSimCfg::Instance().GmsslLinkMode.SetData((const char*)&hdmsg.msg[33]);
						DbgSimCfg::Instance().SaveAll();
						OpenSslLibClean();
						OpenSslLibIni();
					}
					hdmsg.msg[0] = DbgToolsServer::E_ServiceAsk;
					hdmsg.msg[1] = DbgToolsServer::E_ServiceAsk >> 8;
					hdmsg.msg[2] = (uint8)Cmd;
					hdmsg.msg[3] = (uint8)(Cmd >> 8);
					MemCpy(&msg.msg.buf, &hdmsg, sizeof(hdmsg));
					msg.dbgMsg.header.len = sizeof(msg.msg.header) + sizeof(hdmsg);
					signIn.Send(msg.dbgMsg);
					taskStep = E_LogOn;
					return;
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

void spt::DbgClient::SendLogHeartBeat()
{
	if (sock)
	{
		DbgLogOnMsg msg;
		msg.dbgMsg.header.len = sizeof(msg.msg.header) + 200;
		uint16 data = DbgToolsServer::E_HeartBeat;
		MemCpy(&msg.msg.buf, &data, sizeof(data));
		msg.msg.header.version = 1;
		EncryptData(msg.msg.buf, 200, 66);
		int32 res = sock->Send(msg.dbgMsg);
	}
}

void spt::DbgClient::ReConnect()
{
	if (lastUpdateReconnected.IsEnable())
	{
		if (!lastUpdateReconnected.Status(5000))
		{
			return;
		}
	}
	else
	{
		lastUpdateReconnected.Enable(1);
	}
	isAskConnect = 1;
	lastUpdateReconnected.StartTimer();
}

void spt::DbgClient::OneLoopPowerUpIni()
{
#ifdef WIN32_SIM
	DbgSimCfg::Instance().ReadAll();
#endif
	isAskConnect = 1;
	taskStep = E_ClentIni;
}

bool8 spt::DbgClient::LogOn(DbgToolsServer::E_MsgType MsgType, DbgSocket& Sock)
{
	msgType = MsgType;
	sock = &Sock;
	DbgLogOnMsg msg;
	msg.dbgMsg.header.len = sizeof(msg.msg.header) + 200;
	uint16 data = DbgToolsServer::E_ServiceAsk;
	MemCpy(&msg.msg.buf, &data, sizeof(data));
	msg.msg.header.version = 1;
	String100B id;
	String100B name;
	String100B pw;
	logstatus = E_InputPw;
	AskForLogOnInfo(isIdCheck, isPwCheck, id, name, pw, 0);
	logstatus = E_CheckPw;
	StrNCpy((char*)&msg.msg.buf[2], name.Str(), 20);
	StrNCpy((char*)&msg.msg.buf[22], pw.Str(), 20);
	StrNCpy((char*)&msg.msg.buf[42], id.Str(), 40);
	EncryptData(msg.msg.buf, 200, 66);
	int32 res = Sock.Send(msg.dbgMsg);
	MsTimer timer;
	timer.UpCnt(1 * timer.Mt1Second);
	timer.Enable(1);
	timer.Restart();
	while (!timer.Status())
	{
		DbgLogOnMsg msg;
		int32 rtn = Sock.Recv(msg.dbgMsg);
		if (rtn > 0)
		{
			uint16 data;
			MemCpy(&data, &msg.msg.buf, sizeof(data));
			if (data == DbgToolsServer::E_ServiceAsk)
			{
				int32 res;
				MemCpy(&res, &msg.msg.buf[2], sizeof(res));
				if (res == 0)
				{
					logstatus = E_LogOnOk;
					return 1;
				}
				if (res == -1)
				{
					logstatus = E_LogOnIdErr;
					return 0;
				}
				if (res == -2)
				{
					logstatus = E_LogOnAccountErr;
					return 0;
				}
				if (res == -3)
				{
					logstatus = E_LogOnAccountLock;
					return 0;
				}
				if (res == -4)
				{
					logstatus = E_LogOnLinkErr;
					return 0;
				}
				if (res == -5)
				{
					logstatus = E_LogOverTime;
					return 0;
				}
			}
		}
		if (rtn < 0)
		{
			logstatus = E_LogOnLinkErr;
			return 0;
		}
		MsSleep(20);
	}
	logstatus = E_LogOverTime;
	return 0;
}

void spt::DbgClient::ClientIni()
{
#ifdef WIN32_SIM

#endif
	signIn.SetLocalIp(DbgSimCfg::Instance().ClientIp.StrData());
	signIn.SetLocalPort(DbgSimCfg::Instance().ClientPort.Data());
	signIn.SetRemoteIp(DbgSimCfg::Instance().ServerIp.StrData());
	signIn.SetRemotePort(33000);
	taskStep = E_WaitConnect;
}

void spt::DbgClient::WaitConnect()
{
	if (logTimer.Status())
	{
		isAskConnect = 1;
	}
	else if (!logTimer.IsEnable())
	{
		logTimer.UpCnt(5000);
		logTimer.Enable(1);
	}
	if (isAskConnect)
	{
		isAskConnect = 0;
		taskStep = E_AskConnect;
		logTimer.Enable(0);
	}
}

int32 spt::DbgSimCfg::PowerUpIni(int32 Para)
{
	DataNum = 0;
	ServerIp.Set("ServerIp", "", "100.100.100.100");
	AddCfgData(&ServerIp);
	ClientIp.Set("ClientIp", "", "0.0.0.0");
	AddCfgData(&ClientIp);
	ClientPort.Set("ClientPort", "Client端口33001~35000", 33001);
	AddCfgData(&ClientPort);
	EnableGmssl.Set("EnableGmssl", "使用国密加密", 0);
	AddCfgData(&EnableGmssl);
	EnableGmCrtCheck.Set("EnableGmCrtCheck", "使能证书自检", 0);
	AddCfgData(&EnableGmCrtCheck);
	GmsslVerifyMode.Set("GmsslVerifyMode", "证书验证方式0是SSL_VERIFY_NONE，1是SSL_VERIFY_PEER，2是SSL_VERIFY_FAIL_IF_NO_PEER_CERT", 1);
	AddCfgData(&GmsslVerifyMode);
	GmsslLinkMode.Set("GmsslLinkMode", "加密方式ECDHE-SM2-WITH-SMS4-SM3(默认)SM2-WITH-SMS4-SM3(双证书)ECDHE-SM2-WITH-SMS4-GCM-SM3（单证书）", "ECDHE-SM2-WITH-SMS4-SM3");
	AddCfgData(&GmsslLinkMode);
	GmsslCrtFormat.Set("GmsslCrtFormat", "证书格式1是pem(默认)，2是asn1", 1);
	AddCfgData(&GmsslCrtFormat);
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
