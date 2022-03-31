#include"ApiProject.h"
using namespace spt;

int32 spt::IedToolsServer::StartServer(uint32 LocalIp, uint16 LocalPort, uint32 RemoteIp, uint16 RemotePort, int32 ClientSock)
{
	if (gmSock.IsClientOk())
	{
		LogMsg.Stamp() << "IedTools Socket is aready opened.\n";
		return -1;
	}
	gmSock.SetLocalIp(LocalIp);
	gmSock.SetLocalPort(LocalPort);
	gmSock.SetRemoteIp(RemoteIp);
	gmSock.SetRemotePort(RemotePort);
	gmSock.EnableGmssl(DbgSimCfg::Instance().EnableGmssl.Data());
	gmSock.SetClientSock(ClientSock);
	MsTimer timer;
	if (gmSock.IsEnableGmssl())
	{
		gmSock.CreatGmSock();
		timer.UpCnt(5000);
		timer.Enable(1);
		timer.Restart();
		while (!timer.Status())
		{
			MsSleep(50);
			if (gmSock.GmAccept() >= 0)
			{
				break;
			}
		}
		if (timer.Status())
		{
			gmSock.Close();
			LogWarn.Stamp() << "IedTools GmAccept Socket Accept Failed." << GetSocketLastError() << "\n";
			return -1;
		}
		else
		{
			LogMsg.Stamp() << "IedTools GmSocket Accept Ok.\n";
		}
		MsSleep(100);
	}
	gmSock.SetLinkOk(1);
	String40B str;
	gmSock.GetRemote(str);
	isLogOn = 0;
	if (DbgToolsServer::Instance().LogOn(DbgToolsServer::E_IedTools, gmSock))
	{
		LogMsg.Stamp() << "IedTools Log Ok.\n";
		isLogOn = 1;
	}
	else
	{
		LogMsg.Stamp() << "IedTools Log Err.\n";
		gmSock.Close();
		return -1;
	}
	return  0;
}

void spt::IedToolsServer::SetIedToolsWndRoot(ApiIedToolsCascadeWnd* Wnd)
{
	wndRoot = (IedToolsCascadeWnd*)Wnd;
	IedToolsCascadeWnd* wnd = (IedToolsCascadeWnd*)Wnd;
	wnd->SetId(0);
}

int32 spt::IedToolsServer::PowerUpIni(int32 Para)
{
	Task::PowerUpIni(0);
	msgSem.Creat(1);
	Start();
	return 0;
}

int32 spt::IedToolsServer::OneLoop()
{
	uint32 step = taskStep;
	switch (step)
	{
	case E_PowerUpIni:
	{
		taskStep = E_WaitClient;
		break;
	}
	case E_WaitClient:
	{
		if (isLogOn)
		{
			isLogOn = 0;
			taskStep = E_ClientIni;
		}
		MsSleep(100);
		break;
	}
	case E_ClientIni:
	{
		taskStep = E_Work;
		MsSleep(100);
		break;
	}
	case E_Work:
	{
		taskStep = E_Check;
		Work();
		MsSleep(10);
		break;
	}
	case E_Check:
	{
		if (!gmSock.IsClientOk())
		{
			taskStep = E_WaitClient;
			break;
		}
		if (Check() >= 0)
		{
			taskStep = E_Work;
		}
		else
		{
			taskStep = E_WaitClient;
		}
		MsSleep(10);
		break;
	}
	default:
		break;
	}
	return 0;
}

int32 spt::IedToolsServer::RecMsg(SalCmmMsgHeader& msg, uint32 MsgBufLen)
{
	if (gmSock.IsLinkOk() == 0)
	{
		return -1;
	}
	if (msgSem.Wait(1000) < 0)
	{
		return -1;
	}
	SalCmmMsgHeader header;
	int cnt = 0;
	while (gmSock.Recv(&header, sizeof(header), 0) == sizeof(header))
	{
		if (header.header == 0xd555)
		{
			MemCpy(&msg, &header, sizeof(header));
			int len = msg.len - sizeof(header) + sizeof(DbgMsg::checkCode);
			if ((uint32)(msg.len + 2) >= MsgBufLen)
			{
				continue;
			}
			int32 remLen = 0;
			int32 recLen = 0;
			int32 breakcnt = 0;
			do
			{
				recLen += remLen = gmSock.Recv(((uint8*)&msg) + sizeof(SalCmmMsgHeader), len - recLen, 0);
				if (remLen < 0)
				{
					breakcnt++;
					if (breakcnt > 5)
					{
						break;
					}
				}
				else
				{
					breakcnt = 0;
				}
				MsSleep(10);
			} while (recLen < len);
			if (recLen == len)
			{
				if (msg.IsCrcOk())
				{
					msgSem.Post();
					recMsgOkCnt++;
					return  msg.len;
				}
				recMsgErrCnt++;
			}
			else
			{
				recMsgErrCnt++;
				msgSem.Post();
				return -1;
			}
		}
		else
		{
			cnt++;
			if (cnt > 10)
			{
				msgSem.Post();
				return -1;
			}
		}
	}
	msgSem.Post();
	return -1;
}

int32 spt::IedToolsServer::RecMsg(uint32 MsgType, int32 WaitTime, SalCmmMsgHeader& Msg, uint32 MsgBufLen)
{
	if (gmSock.IsLinkOk() == 0)
	{
		return -1;
	}
	MsTimer timer;
	timer.UpCnt(WaitTime);
	timer.Enable(1);
	SalTransFrame* msg = (SalTransFrame*)&Msg;
	while (!timer.Status())
	{
		if (RecMsg(Msg, MsgBufLen) < 0)
		{
			MsSleep(200);
			SendHeartBeat();
		}
		else if (msg->Header.type == MsgType)
		{
			return 0;
		}
	}
	return -1;
}

int32 spt::IedToolsServer::SendMsg(SalCmmMsgHeader& msg)
{
	if (gmSock.IsLinkOk() == 0)
	{
		return 0;
	}
	if (msgSem.Wait(1000) < 0)
	{
		return 0;
	}
	msg.header = 0xd555;
	msg.type = SCT_IEDTools;
	msg.sur = gmSock.LocalIp().u2b[1].u16;
	msg.dst = gmSock.RemoteIp().u2b[1].u16;
	msg.AddCrc();
	gmSock.Send(&msg, msg.len + sizeof(SalCmmMsg<2>::checkCode), 0);
	msgSem.Post();
	sendMsgOkCnt++;
	return msg.len;
}

int32 spt::IedToolsServer::SendMsg(SalCmmMsgHeader& msg, uint32 DataLen)
{
	msg.len = (uint16)DataLen + sizeof(msg.header);
	return SendMsg(msg);
}

int32 spt::IedToolsServer::SendMsg(SalTransHeader& msg)
{
	msg.salHeader.len = (uint16)msg.dataLen + sizeof(SalTransHeader);
	return SendMsg(msg.salHeader);
}

void spt::IedToolsServer::SendHeartBeat()
{
	SalDateStamp s;
	s.Now();
	IedToolHeartBeatMsg msg;
	msg.data.stamp = s;
	msg.header.SetHeader(E_ITMT_HeartBeat, 0, sizeof(msg.data));
	SendMsg(msg.header.salHeader);
	heartbeatTimer.Restart();
}

spt::IedToolsServer::IedToolsServer()
	:Task("tIedTools", TaskBasePriority + 30, 2 * 1048 * 1024, E_T_FLOAT, E_AuxCore)
{

}

int32 spt::IedToolsServer::Check()
{
	if (checkTimer.IsEnable())
	{
		if (recMsgLastOkCnt != recMsgOkCnt)
		{
			checkTimer.Restart();
		}
		recMsgLastOkCnt = recMsgOkCnt;
	}
	else if (gmSock.IsLinkOk())
	{
		checkTimer.UpCnt(10000);
		checkTimer.Enable(1);
	}
	else
	{
		checkTimer.Enable(0);
		return -1;
	}
	if (checkTimer.Status())
	{
		SalTransFrame2kB ctrl;
		ctrl.SetMsgIniInfo(E_ITMT_SockClose, 0);
		SendMsg(ctrl.Header());
		MsSleep(100);
		CloseSock();
		LogMsg.Stamp() << "IedTools 心跳超时 关闭连接.\n";
		return -1;
	}
	if (heartbeatTimer.IsEnable())
	{
		if (heartbeatTimer.Status())
		{
			SalDateStamp s;
			s.Now();
			uint8  now = (uint8)(s.Us() / s.Dt1Second);
			if (lastSec != now)
			{
				IedToolHeartBeatMsg msg;
				msg.data.stamp = s;
				msg.header.SetHeader(E_ITMT_HeartBeat, 0, sizeof(msg.data));
				SendMsg(msg.header.salHeader);
				heartbeatTimer.Restart();
				lastSec = now;
			}
		}
	}
	else
	{
		heartbeatTimer.UpCnt(500);
		heartbeatTimer.Enable(1);
	}
	return 0;
}

int32 spt::IedToolsServer::Work()
{
	SalTransFrame5kB recMsgBuf;
	if (RecMsg(recMsgBuf.Header().salHeader, recMsgBuf.FrameBufLen()) <= 0)
	{
		MsSleep(10);
		return 0;
	}
	Unpack(recMsgBuf.Header().salHeader);
	return 0;
}

int32 spt::IedToolsServer::Unpack(SalCmmMsgHeader& Msg)
{
	SalTransHeader* msg = (SalTransHeader*)&Msg;
	uint16 type = msg->type;
	switch (type)
	{
	case E_ITMT_HeartBeat:
	{
		break;
	}
	case E_ITMT_SockClose:
	{
		CloseSock();
		LogMsg.Stamp() << "IedTools Client ask 关闭连接.\n";
		break;
	}
	case E_ITMT_AskClientInfo:
	{
		if (SptMain::Instance().AppCfg())
		{
			String1000B str;
			str << SptMain::Instance().AppCfg()->hmicfg.DispName << "," << SptMain::Instance().AppCfg()->hmicfg.FullTypeName << "," << ApiUnitCfg::Instance().DeviceID.StrData();
			SalTransFrame5kB ctrl;
			ctrl.SetMsgIniInfo(E_ITMT_AskClientInfoAck, 0);
			ctrl.Write(str.Str(), str.StrLen() + 1);
			SendMsg(ctrl.Header());
		}
		break;
	}
	case E_ITMT_AskRootWnd:
	{
		if (wndRoot)
		{
			SendCascadeWnd(wndRoot->childWnd);
		}
		break;
	}
	default:
		break;
	}
	return 0;
}

int32 spt::IedToolsServer::CloseSock()
{
	gmSock.Close();
	String100B str;
	gmSock.GetRemote(str);
	DbgToolsServer::Instance().SetClientClose(DbgToolsServer::E_IedTools, str.Str());
	checkTimer.Enable(0);
	return 0;
}

int32 spt::IedToolsServer::SendCascadeWnd(IedToolsCascadeWnd* Wnd)
{
	while (Wnd && (!Wnd->IsEnd()))
	{
		if (Wnd->pdisp && *Wnd->pdisp)
		{
			SalTransFrame5kB ctrl;
			ctrl.SetMsgIniInfo(E_ITMT_AskRootWndAck, 0);

			SendMsg(ctrl.Header());
			MsSleep(2);
		}
		Wnd++;
	}
	return 0;
}

spt::IedToolsDialog::IedToolsDialog(const char* Name, int32 WaitTime)
{
	SetInfo(Name, WaitTime);
}

int32 spt::IedToolsDialog::SetInfo(const char* Name, int32 WaitTime)
{
	StrNCpy(title, Name, sizeof(title));
	waitTime = WaitTime;
	result = -1;
	if (waitTime < 0)
	{
		waitTime = 0;
	}
	return 0;
}

int32 spt::IedToolsDialog::SendMsg(SalTransHeader& msg)
{
	return 	IedToolsServer::Instance().SendMsg(msg);
}

int32 spt::IedToolsDialog::RecMsg(uint32 MsgType, int32 WaitTime, SalCmmMsgHeader& msg, uint32 MsgBufLen)
{
	return 	IedToolsServer::Instance().RecMsg(MsgType, WaitTime, msg, MsgBufLen);
}

spt::IedToolsCascadeWnd::IedToolsCascadeWnd(const char* Name, WndFunc EnterFunc, ApiIedToolsCascadeWnd* ChildWnd, WndFunc WorkFunc, WndFunc ExitFunc, const uint32* pDisp)
{
	StrNCpy(title, Name, sizeof(title));
	enterFunc = EnterFunc;
	workFunc = WorkFunc;
	childWnd = (IedToolsCascadeWnd*)ChildWnd;
	exitFunc = ExitFunc;
	pdisp = pDisp;
	if (!pdisp)
	{
		pdisp = &MenuDisp;
	}
	wndId = 0;
}

bool8 spt::IedToolsCascadeWnd::IsEnd()
{
	return StrNCmp(title, EndOfInst, sizeof(title)) == 0;
}

uint32 spt::IedToolsCascadeWnd::SetId(uint32 Id)
{
	wndId = Id + 1;
	if (IsEnd())
	{
		return wndId;
	}
	lastChildId = firstChildId = wndId;
	if (childWnd)
	{
		IedToolsCascadeWnd* wnd = childWnd;
		while (wnd)
		{
			if (wnd->IsEnd())
			{
				return lastChildId;
			}
			lastChildId = wnd->SetId(lastChildId);
			wnd++;
		}
	}
	return wndId;
}
