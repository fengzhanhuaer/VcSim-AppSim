#include "SptProject.h"
#include "DbgLcdCmm.h"
using namespace spt;

void spt::VirLcdCmmClient::ReConnect()
{
	if (lastUpdateReconnected.IsEnable())
	{
		if (!lastUpdateReconnected.Status(2000))
		{
			if (HmiLcdCmm::Instance().IsLcdCmmOk())
			{
				return;
			}
		}
	}
	else
	{
		lastUpdateReconnected.Enable(1);
	}
	if (HmiLcdCmm::Instance().IsLcdCmmOk())
	{
		HmiLcdCmm::Instance().Close();
	}
	lastUpdateReconnected.StartTimer();
}

int32 spt::VirLcdCmmClient::PowerUpIni(int32 Type)
{
#ifdef WIN32_SIM
	Task::PowerUpIni(0);


#endif
	return 0;
}

int32 spt::VirLcdCmmClient::OneLoop()
{
	switch (taskStep)
	{
	case DbgClient::E_PowerUpIni:
	{
#ifdef WIN32_SIM
		DbgSimCfg::Instance().ReadAll();
#endif
		taskStep = E_ClentIni;
		break;
	}
	case DbgClient::E_ClentIni:
	{
#ifdef WIN32_SIM

#endif
		signIn.SetLocalIp("0.0.0.0");
		signIn.SetLocalPort(33001);
		signIn.SetRemoteIp(DbgSimCfg::Instance().ServerIp.StrData());
		signIn.SetRemotePort(33000);
		if (signIn.StartNonBlock() == 0)
		{
			taskStep = E_LogOn;
		}
		break;
	}
	case DbgClient::E_LogOn:
	{
		LogOn();
		break;
	}
	case DbgClient::E_SendCmd:
	{
		uint32 data;
		DbgLogOnMsg msg;
		data = DbgToolsServer::E_ServiceAsk;
		MsTimer timer;
		timer.UpCnt(3000);
		timer.Enable(1);
		timer.Restart();
		while (!timer.Status())
		{
			MsSleep(10);
			if (signIn.Recv(&msg, sizeof(msg), 0) > 0)
			{
				msg.msg.header.version = 1;
				DbgToolsServer::HandshakeMsg hdmsg;
				MemCpy(&hdmsg, msg.msg.buf, sizeof(hdmsg));
				DecryptData(&hdmsg, sizeof(hdmsg), 27);
				DbgSimCfg::Instance().EnableGmssl.SetData(hdmsg.msg[2]);
				DbgSimCfg::Instance().GmsslVerifyMode.SetData(hdmsg.msg[3]);
				if (StrLen((const char*)&hdmsg.msg[33]) == hdmsg.msg[32])
				{
					DbgSimCfg::Instance().GmsslLinkMode.SetData((const char*)&hdmsg.msg[33]);
				}
				hdmsg.msg[0] = DbgToolsServer::E_ServiceAsk;
				hdmsg.msg[1] = DbgToolsServer::E_ServiceAsk >> 8;
				hdmsg.msg[2] = DbgToolsServer::E_VirLcd;
				hdmsg.msg[3] = DbgToolsServer::E_VirLcd >> 8;
				MemCpy(&msg.msg.buf, &hdmsg, sizeof(hdmsg));
				msg.dbgMsg.header.len = sizeof(msg.msg.header) + sizeof(hdmsg);
				signIn.SendTo(&msg, msg.dbgMsg.header.len, 0);
				if (HmiLcdCmm::Instance().StartClient(0, 33003, signIn.RemoteIp().u32, 33002) == 0)
				{
					taskStep = E_AskIniInfo;
					GraphicDevice::Instance().ClearAll();
				}
				else
				{
					taskStep = E_ClentIni;
				}
				break;
			}
		}
		if (timer.Status())
		{
			taskStep = E_ClentIni;
		}
		break;
	}
	case E_AskIniInfo:
	{
		LcdMsgContext lmc;
		lmc.type = E_IedName;
		lmc.len = sizeof(lmc.type) + sizeof(lmc.len);
		HmiLcdCmm::Instance().Send((LcdMsgContext*)&lmc);
		taskStep = E_Work;
		checkTimer.UpCnt(5000);
		checkTimer.Enable(1);
		IsIedInfoAsked = 1;
		IsIedInfoInied = 0;
		break;
	}
	case E_Work:
	{
		if (HmiLcdCmm::Instance().IsLinkOk() == 0)
		{
			taskStep = E_Check;
		}
		break;
	}
	case E_Check:
	{
		if (HmiLcdCmm::Instance().IsLinkOk() == 0)
		{
			taskStep = E_ClentIni;
		}
		break;
	}
	default:
		taskStep = E_ClentIni;
		break;
	}
	return 0;
}

void spt::VirLcdCmmClient::SetIedInfoIniedFlag(bool8 inied)
{
	IsIedInfoInied = inied;
}

VirLcdCmmClient& spt::VirLcdCmmClient::Instance()
{
	static VirLcdCmmClient inst;
	return inst;
}

spt::VirLcdCmmClient::VirLcdCmmClient()
{
	taskStep = 0;
}
