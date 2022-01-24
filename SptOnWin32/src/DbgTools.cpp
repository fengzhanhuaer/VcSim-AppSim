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

DbgToolsServer& spt::DbgToolsServer::Instance()
{
	static DbgToolsServer inst;
	return inst;
}

spt::DbgToolsServer::DbgToolsServer()
	:Task("tDbgMain", TaskBasePriority, 2048 * 1024, E_T_FLOAT, E_AuxCore)
{
	signInStep = 0;
}

int32 spt::DbgToolsServer::OneLoop()
{
	switch (taskStep)
	{
	case E_PowerUpIni:
	{
		DbgSimCfg::Instance().PowerUpIni(0);
		msTimer.UpCnt(10000);
		checkTimer.UpCnt(1000);
		checkTimer.Enable(1);
		taskStep = E_IniServer;
		MsSleep(300);
		break;
	}
	case E_IniServer:
	{
		MsSleep(300);
		if (!DbgSimCfg::Instance().EnableDbgServer.Data())
		{
			MsSleep(10000);
			break;
		}
		signIn.SetLocalIp(DbgSimCfg::Instance().ServerIp.StrData());
		signIn.SetLocalPort(33000);
		if (signIn.StartNonBlock() == 0)
		{
			taskStep = E_WaitClient;
		}
		else
		{
			MsSleep(5000);
		}
		signInStep = E_Wait;
		break;
	}
	case E_WaitClient:
	{
		switch (signInStep)
		{
		case E_Wait:
		{
			DbgLogOnMsg msg;
			uint32 data = 0;
			int32 len = signIn.RecvFrom(&msg, sizeof(msg), 0);
			if (len <= 0)
			{
				MsSleep(1000);
				if (checkTimer.Status())
				{
					taskStep = E_CheckClient;
				}
				break;
			}
			else if ((msg.msg.header.version == 1) && (msg.dbgMsg.header.header == 0xd555))
			{
				if (len != msg.dbgMsg.header.len)
				{
					msTimer.Enable(1);
					signIn.Close();
					taskStep = E_NetStorm;
					break;
				}
				MemCpy(&data, msg.msg.buf, sizeof(data));
				DecryptData(&data, sizeof(data), 16);
				if (data == 0x12fa990)
				{
					signInStep = E_StartLog;
				}
				else
				{
					signIn.Close();
					taskStep = E_NetStorm;
					break;
				}
			}
			else
			{
				signIn.Close();
				taskStep = E_NetStorm;
				break;
			}
			break;
		}
		case E_StartLog:
		{
			DbgLogOnMsg msg;
			uint64  ms = SptMsInt::Instance().MsCnt64();
			uint64 msbak = ms;
			msg.msg.header.version = 1;
			EncryptData(&ms, sizeof(ms), 3);
			MemCpy(msg.msg.buf, &ms, sizeof(ms));
			msg.dbgMsg.header.len = sizeof(msg.msg.header) + sizeof(ms);
			if (signIn.SendTo(&msg, msg.dbgMsg.header.len, 0) > 0)
			{
				char buf[50];
				MemCpy(buf, &msbak, sizeof(msbak));
				EncryptData(buf, sizeof(ms), 52);
				uint16 crc = Crc16ModBus.AddCrc(buf, sizeof(ms) + 2);
				uint16 crc1;
				MsTimer timer;
				timer.UpCnt(3000);
				timer.Enable(1);
				timer.Restart();
				while (!timer.Status())
				{
					MsSleep(20);
					int32 len = signIn.Recv(&msg, sizeof(msg), 0);
					if (len <= 0)
					{
						continue;
					}
					MemCpy(&crc1, msg.msg.buf, sizeof(crc1));
					if ((crc == crc1) && (msg.dbgMsg.header.len == len))
					{
						signInStep = E_WaitCmd;
						break;
					}
					else
					{
						signIn.Close();
						taskStep = E_NetStorm;
						break;
					}
				}
				if (timer.Status())
				{
					taskStep = E_IniServer;
				}
			}
			else
			{
				signInStep = E_Wait;
			}
		}
		case E_WaitCmd:
		{
			DbgLogOnMsg msg;
			msg.msg.header.version = 1;
			HandshakeMsg hdmsg;
			hdmsg.msg[0] = E_ServiceAsk;
			hdmsg.msg[1] = E_ServiceAsk >> 8;
			hdmsg.msg[2] = DbgSimCfg::Instance().EnableGmssl.Data();
			hdmsg.msg[3] = DbgSimCfg::Instance().GmsslVerifyMode.Data();
			hdmsg.msg[32] = StrLen(DbgSimCfg::Instance().GmsslLinkMode.StrData());
			MemCpy(&hdmsg.msg[33], DbgSimCfg::Instance().GmsslLinkMode.StrData(), hdmsg.msg[32] + 1);
			EncryptData(&hdmsg, sizeof(hdmsg), 27);
			MemCpy(msg.msg.buf, &hdmsg, sizeof(hdmsg));
			msg.dbgMsg.header.len = sizeof(msg.msg.header) + sizeof(hdmsg);
			if (signIn.SendTo(&msg, msg.dbgMsg.header.len, 0) > 0)
			{
				MsTimer timer;
				timer.UpCnt(3000);
				timer.Enable(1);
				timer.Restart();
				int32 len;
				while (!timer.Status())
				{
					MsSleep(20);
					len = signIn.Recv(&msg, sizeof(msg), 0);
					if (len == msg.msg.header.dbgheader.len)
					{
						uint16 data;
						MemCpy(&data, &msg.msg.buf, sizeof(data));
						if (data != E_ServiceAsk)
						{
							taskStep = E_CheckClient;
							break;
						}
						MemCpy(&data, &msg.msg.buf[sizeof(data)], sizeof(data));
						switch (data)
						{
						case E_VirLcd:
						{
							if (HmiLcdCmm::Instance().StartServer(0, 33002, signIn.RemoteIp().u32, 33003) == 0)
							{
								taskStep = E_CheckClient;
								const char* msginfo = "VirLcd connected .\n";
								LogMsg.Stamp() << msginfo;
								return 0;
							}
							else
							{
								const char* msginfo = "VirLcd connect failed .\n";
								LogMsg.Stamp() << msginfo;
								taskStep = E_CheckClient;
								return 0;
							}
							break;
						}
						case E_DbgServer:
						{
							if (DbgServer::Instance().IsRuning())
							{
								taskStep = E_CheckClient;
								return 0;
							}
							DbgServer::Instance().SetLocalIp("0.0.0.0");
							DbgServer::Instance().Instance().SetLocalPort(33004);
							DbgServer::Instance().SetRemoteIp(signIn.RemoteIp().u32);
							DbgServer::Instance().SetRemotePort(33005);
							if (DbgServer::Instance().StartServer() == 0)
							{
								const char* msginfo = "DbgClient connected .\n";
								LogMsg.Stamp() << msginfo;
								taskStep = E_CheckClient;
								return 0;
							}
							else
							{
								const char* msginfo = "DbgClient connect failed .\n";
								LogMsg.Stamp() << msginfo;
								taskStep = E_CheckClient;
								return 0;
							}
							taskStep = E_CheckClient;
							return 0;
							break;
						}
						default:
							taskStep = E_IniServer;
							break;
						}

					}
					else if (len <= 0)
					{
						continue;
					}
					else
					{
						taskStep = E_CheckClient;
						break;
					}

				}
				if (timer.Status())
				{
					taskStep = E_IniServer;
				}
			}
			else
			{
				taskStep = E_IniServer;
			}
			break;
		}

		default:
			signInStep = E_Wait;
			break;
		}
		break;
	}
	case E_NetStorm:
	{
		MsSleep(1000);
		signIn.Close();
		if (msTimer.IsEnable())
		{
			if (msTimer.Status())
			{
				msTimer.Enable(0);
				taskStep = E_IniServer;
			}
			break;
		}
		else
		{
			msTimer.UpCnt(10000);
			msTimer.Enable(1);
		}
		break;
	}
	case E_CheckClient:
	{
		if (signIn.IsOk())
		{
			taskStep = E_WaitClient;
			signInStep = E_Wait;
		}
		else
		{
			taskStep = E_IniServer;
		}
		break;
	}
	default:
		taskStep = E_IniServer;
		break;
	}
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
	msg.msg.header.dbgheader.len = sizeof(msg.msg.header) + sizeof(data);
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
				msg.msg.header.dbgheader.len = sizeof(msg.msg.header) + sizeof(crc);
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
	}
	else
	{
		MsSleep(1000);
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
	if (SptMain::Instance().IsDevice(ED_SAU31_Sub))
	{
		ServerIp.Set("ServerIp", "100.100.100.101");
	}
	else
	{
		ServerIp.Set("ServerIp", "100.100.100.100");
	}
	AddCfgData(&ServerIp);
	if (SptMain::Instance().StartMode() == SptMain::E_Factory)
	{
		EnableGmssl.Set("EnableGmssl", 0);
	}
	else
	{
		EnableGmssl.Set("EnableGmssl", 0);
	}

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
