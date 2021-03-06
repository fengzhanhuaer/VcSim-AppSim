#include "SptProject.h"
using namespace spt;
int32 spt::DbgSimCfg::PowerUpIni(int32 Para)
{
	DataNum = 0;
	EnableDbgServer.Set("EnableDbgServer", "使用调试服务器", 1);
	AddCfgData(&EnableDbgServer);
	EnableSimLcd.Set("EnableSimLcd", "使用虚拟液晶", 1);
	AddCfgData(&EnableSimLcd);
	EnableIedTools.Set("EnableIedTools", "使用配置工具", 1);
	AddCfgData(&EnableIedTools);
	EnableDbgTools.Set("EnableDbgTools", "使用调试工具", 1);
	AddCfgData(&EnableDbgTools);
	NeedCheckDeviceId.Set("NeedCheckDeviceId", "验证唯一性代码", 0);
	AddCfgData(&NeedCheckDeviceId);
	NeedUsrLog.Set("NeedUsrLog", "使能用户登录", 0);
	AddCfgData(&NeedUsrLog);
	if (SptMain::Instance().IsDevice(ED_SAU31_Sub))
	{
		ServerIp.Set("ServerIp", "", "100.100.100.101");
	}
	else
	{
		ServerIp.Set("ServerIp", "", "100.100.100.100");
	}
	AddCfgData(&ServerIp);
	if (SptMain::Instance().StartMode() == SptMain::E_Factory)
	{
		EnableGmssl.Set("EnableGmssl", "使用国密加密", 0);
	}
	else
	{
		EnableGmssl.Set("EnableGmssl", "使用国密加密", 0);
	}
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
int32 spt::DbgClientCfg::PowerUpIni(int32 Para)
{
	DataNum = 0;
	ServerIp.Set("ServerIp", "", "100.100.100.100");
	ClientIp.Set("ClientIp", "", "0.0.0.0");
	ClientPort.Set("ClientPort", "Client端口33001~35000", 33001);
	EnableGmssl.Set("EnableGmssl", "使用国密加密", 0);
	EnableGmCrtCheck.Set("EnableGmCrtCheck", "使能证书自检", 0);
	GmsslVerifyMode.Set("GmsslVerifyMode", "证书验证方式0是SSL_VERIFY_NONE，1是SSL_VERIFY_PEER，2是SSL_VERIFY_FAIL_IF_NO_PEER_CERT", 1);
	GmsslLinkMode.Set("GmsslLinkMode", "加密方式ECDHE-SM2-WITH-SMS4-SM3(默认)SM2-WITH-SMS4-SM3(双证书)ECDHE-SM2-WITH-SMS4-GCM-SM3（单证书）", "ECDHE-SM2-WITH-SMS4-SM3");
	GmsslCrtFormat.Set("GmsslCrtFormat", "证书格式1是pem(默认)，2是asn1", 1);
	path.Set(CN_CFG_FILE_ROOT);
	name.Set("DbgSim.cfg");
	return 0;
}
DbgSimCfg& spt::DbgSimCfg::Instance()
{
	static DbgSimCfg inst;
	return inst;
}

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
	IedToolsServer::Instance().PowerUpIni(0);
	DbgTools::Instance().PowerUpIni(0);
	return 0;
}

DbgToolsServer& spt::DbgToolsServer::Instance()
{
	static DbgToolsServer inst;
	return inst;
}

void spt::DbgToolsServer::SetCheckDeviceIdFunc(CheckDeviceIdFunc func)
{
	checkDeviceIdFunc = func;
}

void spt::DbgToolsServer::SetUserLogOnFunc(UserLogOnFunc func)
{
	userLogOnFunc = func;
}

void spt::DbgToolsServer::SetUserLinkCloseFunc(UserLinkCloseFunc func)
{
	userLinkCloseFunc = func;
}
void spt::DbgToolsServer::SetUserLinkFunc(UserLinkFunc func)
{
	userLinkFunc = func;
}

void spt::DbgToolsServer::SetClientClose(E_MsgType MsgType, const char* Ip)
{
	if (userLinkCloseFunc)
	{
		userLinkCloseFunc(MsgType, Ip);
	}
}

bool8 spt::DbgToolsServer::LogOn(E_MsgType MsgType, DbgSocket& Sock)
{
	MsTimer timer;
	timer.UpCnt(30 * timer.Mt1Second);
	timer.Enable(1);
	timer.Restart();
	int32 res = 0;
	DbgLogOnMsg msg;
	while (!timer.Status())
	{
		int32 rtn = Sock.Recv(msg.dbgMsg);
		if (rtn > 0)
		{
			uint16 data;
			DecryptData(msg.msg.buf, 200, 66);
			MemCpy(&data, &msg.msg.buf, sizeof(data));
			if (data == E_ServiceAsk)
			{
				String20B name;
				String20B pw;
				String40B id;
				name << (char*)&msg.msg.buf[2];
				pw << (char*)&msg.msg.buf[22];
				id << (char*)&msg.msg.buf[42];
				String100B str;
				Sock.GetRemote(str);
				MemSet(&msg, 0, sizeof(msg));
				msg.dbgMsg.header.len = sizeof(msg.msg.header) + sizeof(res) + 66;
				uint16 data = E_ServiceAsk;
				MemCpy(&msg.msg.buf, &data, sizeof(data));
				msg.msg.header.version = 1;
				if (DbgSimCfg::Instance().NeedCheckDeviceId.Data())
				{
					if (checkDeviceIdFunc)
					{
						if (0 != checkDeviceIdFunc(MsgType, str.Str(), id.Str()))
						{
							res = -1;
							MemCpy(&msg.msg.buf[2], &res, sizeof(res));
							msg.dbgMsg.header.len = sizeof(msg.msg.header) + 100;
							Sock.Send(msg.dbgMsg);
							return 0;
						}
					}
				}
				if (DbgSimCfg::Instance().NeedUsrLog.Data())
				{
					if (userLogOnFunc)
					{
						int32 res = userLogOnFunc(MsgType, str.Str(), name.Str(), pw.Str());
						if (0 != res)
						{
							MemCpy(&msg.msg.buf[2], &res, sizeof(res));
							msg.dbgMsg.header.len = sizeof(msg.msg.header) + 100;
							Sock.Send(msg.dbgMsg);
							return 0;
						}
					}
				}
				res = 0;
				MemCpy(&msg.msg.buf[2], &res, sizeof(res));
				msg.dbgMsg.header.len = sizeof(msg.msg.header) + 100;
				Sock.Send(msg.dbgMsg);
				return 1;
			}
			else if (data == E_HeartBeat)
			{
				timer.Restart();
			}
		}
		if (rtn < 0)
		{
			res = -4;
			MemCpy(&msg.msg.buf[2], &res, sizeof(res));
			msg.dbgMsg.header.len = sizeof(msg.msg.header) + 100;
			Sock.Send(msg.dbgMsg);
			return 0;
		}
		MsSleep(200);
	}
	res = -5;
	msg.dbgMsg.header.len = sizeof(msg.msg.header) + 100;
	MemCpy(&msg.msg.buf[2], &res, sizeof(res));
	Sock.Send(msg.dbgMsg);
	return 0;
}

spt::DbgToolsServer::DbgToolsServer()
	:Task("tDbgMain", TaskBasePriority - 50, 2048 * 1024, E_T_FLOAT, E_AuxCore)
{
}

int32 spt::DbgToolsServer::OneLoop()
{
	MsTimer timer;
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
		break;
	}
	case E_WaitClient:
	{
		if (signIn.ClientSock() > 0)
		{
			signIn.CloseClient();
			MsSleep(100);
			break;
		}
		else
		{
			if (signIn.IsReadAble() == 0)
			{
				signIn.SetRemoteIp("0.0.0.0");
				signIn.SetRemotePort(0);
				MsSleep(100);
				break;
			}
			if (signIn.Accept() <= 0)
			{
				MsSleep(100);
				break;
			}
			signIn.SetClientSocketNonBlock(1);
			String100B str;
			signIn.GetRemote(str);
			if ((signIn.RemotePort().u16 < 33001) && (signIn.RemotePort().u16 > 35000))
			{
				if (userLinkFunc)
				{
					userLinkFunc(E_HeartBeat, str.Str(), -1);
				}
				taskStep = E_NetStorm;
				signIn.CloseClient();
				LogMsg.Stamp() << "Client Port is not allow .\n";
				break;
			}
			DbgLogOnMsg msg;
			uint32 data = 0;
			timer.UpCnt(3000);
			timer.Enable(1);
			timer.Restart();
			while (!timer.Status())
			{
				int32 len = signIn.Recv(msg.dbgMsg);
				if (len <= 0)
				{
					MsSleep(20);
				}
				else if ((msg.msg.header.version == 1) && (msg.dbgMsg.header.header == 0xd555))
				{
					if (len != msg.dbgMsg.header.len)
					{
						msTimer.Enable(1);
						signIn.Close();
						taskStep = E_NetStorm;
						if (userLinkFunc)
						{
							userLinkFunc(E_HeartBeat, str.Str(), -2);
						}
						return 0;
					}
					MemCpy(&data, msg.msg.buf, sizeof(data));
					DecryptData(&data, sizeof(data), 16);
					if (data == 0x12fa990)
					{
						break;
					}
					else
					{
						signIn.CloseClient();
						taskStep = E_NetStorm;
						if (userLinkFunc)
						{
							userLinkFunc(E_HeartBeat, str.Str(), -2);
						}
						return 0;
					}
				}
				else
				{
					if (userLinkFunc)
					{
						userLinkFunc(E_HeartBeat, str.Str(), -2);
					}
					signIn.CloseClient();
					taskStep = E_NetStorm;
					return 0;
				}
			}
			if (timer.Status())
			{
				signIn.CloseClient();
				if (userLinkFunc)
				{
					userLinkFunc(E_HeartBeat, str.Str(), -3);
				}
				return 0;
			}
			uint64  ms = SptMsInt::Instance().MsCnt64();
			uint64 msbak = ms;
			msg.msg.header.version = 1;
			EncryptData(&ms, sizeof(ms), 3);
			MemCpy(msg.msg.buf, &ms, sizeof(ms));
			msg.dbgMsg.header.len = sizeof(msg.msg.header) + sizeof(ms) + 55;
			if (signIn.Send(msg.dbgMsg) > 0)
			{
				char buf[50];
				MemCpy(buf, &msbak, sizeof(msbak));
				EncryptData(buf, sizeof(ms), 52);
				uint16 crc = Crc16ModBus.AddCrc(buf, sizeof(ms) + 2);
				uint16 crc1;
				MsTimer timer;
				timer.UpCnt(1000);
				timer.Enable(1);
				timer.Restart();
				while (!timer.Status())
				{
					MsSleep(20);
					int32 len = signIn.Recv(msg.dbgMsg);
					if (len <= 0)
					{
						continue;
					}
					MemCpy(&crc1, msg.msg.buf, sizeof(crc1));
					if ((crc == crc1) && (msg.dbgMsg.header.len == len))
					{
						break;
					}
					else
					{
						signIn.CloseClient();
						taskStep = E_NetStorm;
						if (userLinkFunc)
						{
							userLinkFunc(E_HeartBeat, str.Str(), -2);
						}
						return 0;
					}
				}
				if (timer.Status())
				{
					signIn.CloseClient();
					if (userLinkFunc)
					{
						userLinkFunc(E_HeartBeat, str.Str(), -3);
					}
					return 0;
				}
			}
			else
			{
				signIn.CloseClient();
				if (userLinkFunc)
				{
					userLinkFunc(E_HeartBeat, str.Str(), -3);
				}
				return 0;
			}
			msg.msg.header.version = 1;
			HandshakeMsg hdmsg;
			hdmsg.msg[0] = E_ServiceAsk;
			hdmsg.msg[1] = E_ServiceAsk >> 8;
			hdmsg.msg[2] = DbgSimCfg::Instance().EnableGmssl.Data();
			hdmsg.msg[3] = DbgSimCfg::Instance().GmsslVerifyMode.Data();
			hdmsg.msg[4] = DbgSimCfg::Instance().NeedCheckDeviceId.Data();
			hdmsg.msg[5] = DbgSimCfg::Instance().NeedUsrLog.Data();
			hdmsg.msg[32] = StrLen(DbgSimCfg::Instance().GmsslLinkMode.StrData());
			MemCpy(&hdmsg.msg[33], DbgSimCfg::Instance().GmsslLinkMode.StrData(), hdmsg.msg[32] + 1);
			EncryptData(&hdmsg, sizeof(hdmsg), 27);
			MemCpy(msg.msg.buf, &hdmsg, sizeof(hdmsg));
			msg.dbgMsg.header.len = sizeof(msg.msg.header) + sizeof(hdmsg);
			if (signIn.Send(msg.dbgMsg) > 0)
			{
				MsTimer timer;
				timer.UpCnt(1000);
				timer.Enable(1);
				timer.Restart();
				int32 len;
				while (!timer.Status())
				{
					MsSleep(20);
					len = signIn.Recv(msg.dbgMsg);
					if (len > 0)
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
							if (!DbgSimCfg::Instance().EnableSimLcd.Data())
							{
								LogMsg.Stamp() << "VirLcd Is not Enable .\n";
								signIn.SetClientSock(-1);
								signIn.CloseClient();
								return 0;
							}
							if (HmiLcdCmm::Instance().StartServer(signIn.LocalIp().u32, signIn.LocalPort().u16, signIn.RemoteIp().u32, signIn.RemotePort().u16, signIn.ClientSock()) == 0)
							{
								taskStep = E_CheckClient;
								signIn.SetClientSock(-1);
								LogMsg.Stamp() << "VirLcd connected .\n";
								if (userLinkFunc)
								{
									userLinkFunc(E_VirLcd, str.Str(), 0);
								}
								return 0;
							}
							else
							{
								if (userLinkFunc)
								{
									userLinkFunc(E_VirLcd, str.Str(), -4);
								}
								signIn.CloseClient();
								LogMsg.Stamp() << "VirLcd connect failed .\n";
								taskStep = E_CheckClient;
								return 0;
							}
							return 0;
						}
						case E_IedTools:
						{
							if (!DbgSimCfg::Instance().EnableIedTools.Data())
							{
								LogMsg.Stamp() << "IedTools Is not Enable .\n";
								signIn.SetClientSock(-1);
								signIn.CloseClient();
								return 0;
							}
							if (IedToolsServer::Instance().StartServer(signIn.LocalIp().u32, signIn.LocalPort().u16, signIn.RemoteIp().u32, signIn.RemotePort().u16, signIn.ClientSock()) == 0)
							{
								taskStep = E_CheckClient;
								signIn.SetClientSock(-1);
								LogMsg.Stamp() << "IedTools connected .\n";
								if (userLinkFunc)
								{
									userLinkFunc(E_IedTools, str.Str(), 0);
								}
								return 0;
							}
							else
							{
								if (userLinkFunc)
								{
									userLinkFunc(E_IedTools, str.Str(), -4);
								}
								signIn.CloseClient();
								LogMsg.Stamp() << "IedTools connect failed .\n";
								taskStep = E_CheckClient;
								return 0;
							}
							return 0;
						}
						case E_DbgTools:
						{
							if (!DbgSimCfg::Instance().EnableDbgTools.Data())
							{
								LogMsg.Stamp() << "DbgTools Is not Enable .\n";
								signIn.SetClientSock(-1);
								signIn.CloseClient();
								return 0;
							}
							if (DbgTools::Instance().StartServer(signIn.LocalIp().u32, signIn.LocalPort().u16, signIn.RemoteIp().u32, signIn.RemotePort().u16, signIn.ClientSock()) == 0)
							{
								taskStep = E_CheckClient;
								signIn.SetClientSock(-1);
								LogMsg.Stamp() << "DbgTools connected .\n";
								if (userLinkFunc)
								{
									userLinkFunc(E_DbgTools, str.Str(), 0);
								}
								return 0;
							}
							else
							{
								if (userLinkFunc)
								{
									userLinkFunc(E_DbgTools, str.Str(), -4);
								}
								signIn.CloseClient();
								LogMsg.Stamp() << "IedTools connect failed .\n";
								taskStep = E_CheckClient;
								return 0;
							}
							return 0;
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
		}
		signIn.CloseClient();
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

void spt::DbgClient::SendLogHeartBeat()
{
	DbgSocket* sock = &gmsock;
	if (sock)
	{
		DbgLogOnMsg msg;
		msg.dbgMsg.header.len = sizeof(msg.msg.header) + 200;
		uint16 data = DbgToolsServer::E_HeartBeat;
		MemCpy(&msg.msg.buf, &data, sizeof(data));
		msg.msg.header.version = 1;
		EncryptData(msg.msg.buf, 200, 66);
		sock->Send(msg.dbgMsg);
	}
}
void spt::DbgClient::ReConnect()
{
	if (lastUpdateReconnected.IsEnable())
	{
		if (!lastUpdateReconnected.Status(2000))
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
void spt::DbgClient::ClientIni()
{
	if (cfg)
	{
#ifdef WIN32_SIM

#endif
		signIn.SetLocalIp(cfg->ClientIp.StrData());
		signIn.SetLocalPort(cfg->ClientPort.Data());
		signIn.SetRemoteIp(cfg->ServerIp.StrData());
		signIn.SetRemotePort(33000);
		taskStep = E_WaitConnect;
	}
}
int32 spt::DbgClient::PowerUpIni(int32 Para)
{
	DbgGmSslClientIni(cfg->GmsslLinkMode.StrData(), cfg->GmsslCrtFormat.Data(), cfg->GmsslVerifyMode.Data());
	return 0;
}
void spt::DbgClient::WaitConnect()
{
	if (logTimer.Status())
	{
		isAskConnect = 1;
	}
	else if (!logTimer.IsEnable())
	{
		logTimer.UpCnt(2000);
		logTimer.Enable(1);
	}
	if (isAskConnect)
	{
		isAskConnect = 0;
		taskStep = E_AskConnect;
		logTimer.Enable(0);
	}
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
					if (cfg && (StrCmp(cfg->GmsslLinkMode.StrData(), (const char*)&hdmsg.msg[33])
						|| (cfg->GmsslVerifyMode.Data() != hdmsg.msg[3])
						|| (cfg->EnableGmssl.Data() != hdmsg.msg[2]))
						)
					{
						cfg->GmsslVerifyMode.SetData(hdmsg.msg[3]);
						cfg->EnableGmssl.SetData(hdmsg.msg[2]);
						cfg->GmsslLinkMode.SetData((const char*)&hdmsg.msg[33]);
						cfg->SaveAll();
						OpenSslLibClean();
						DbgGmSslClientIni(cfg->GmsslLinkMode.StrData(), cfg->GmsslCrtFormat.Data(), cfg->GmsslVerifyMode.Data());
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
	taskStep = E_ClentIni;
}
void spt::DbgClient::OneLoopPowerUpIni()
{
	isAskConnect = 1;
	taskStep = E_ClentIni;
	if (cfg)
	{
		cfg->ReadAll();
	}
}
int32 spt::DbgClient::StartClient(uint16 Cmd, uint32 LocalIp, uint16 LocalPort, uint32 RemoteIp, uint16 RemotePort, int32 ClientSock)
{
	gmsock.SetLocalIp(LocalIp);
	gmsock.SetLocalPort(LocalPort);
	gmsock.SetRemoteIp(RemoteIp);
	gmsock.SetRemotePort(RemotePort);
	gmsock.EnableGmssl(cfg->EnableGmssl.Data());
	gmsock.SetClientSock(ClientSock);
	MsSleep(100);
	MsTimer timer;
	if (cfg->EnableGmssl.Data())
	{
		gmsock.CreatGmSock();
		timer.UpCnt(5000);
		timer.Enable(1);
		timer.Restart();
		while (!timer.Status())
		{
			MsSleep(50);
			if (gmsock.GmConnect() >= 0)
			{
				break;
			}
		}
		if (timer.Status())
		{
			gmsock.Close();
			return -1;
		}
		MsSleep(100);
	}
	gmsock.SetLinkOk(1);
	if (LogOn((DbgToolsServer::E_MsgType)Cmd, gmsock))
	{
		return 0;
	}
	gmsock.Close();
	return -1;
}
bool8 spt::DbgClient::LogOn(DbgToolsServer::E_MsgType MsgType, DbgSocket& Sock)
{
	msgType = MsgType;
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
	Sock.Send(msg.dbgMsg);
	MsTimer timer;
	timer.UpCnt(2 * timer.Mt1Second);
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
		MsSleep(20);
	}
	logstatus = E_LogOverTime;
	return 0;
}