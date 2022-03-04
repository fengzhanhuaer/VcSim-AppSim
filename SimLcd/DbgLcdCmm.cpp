#include "SptProject.h"
#include "DbgLcdCmm.h"
using namespace spt;

void spt::VirLcdCmmClient::ReConnect()
{
	DbgClient::ReConnect();
	if (HmiLcdCmm::Instance().IsLcdCmmOk())
	{
		return;
	}
	HmiLcdCmm::Instance().Close();
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
		OneLoopPowerUpIni();
		break;
	}
	case DbgClient::E_ClentIni:
	{
		ClientIni();
		break;
	}
	case E_WaitConnect:
	{
		WaitConnect();
		break;
	}
	case DbgClient::E_AskConnect:
	{
		AskConnect(DbgToolsServer::E_VirLcd);
		break;
	}
	case DbgClient::E_LogOn:
	{
		if (HmiLcdCmm::Instance().StartClient(signIn.LocalIp().u32, signIn.LocalPort().u16, signIn.RemoteIp().u32, signIn.RemotePort().u16, signIn.ClientSock()) == 0)
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
