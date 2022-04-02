#include "ApiProject.h"
using namespace spt;

spt::ApiIedToolsDialog::ApiIedToolsDialog(const char* Name, int32 WaitTime)
	:IedToolsDialog(Name, WaitTime)
{

}
int32 spt::ApiIedToolsDialog::SetInfo(const char* Name, int32 WaitTime)
{
	return IedToolsDialog::SetInfo(Name, WaitTime);
}
int32 spt::ApiIedToolsDialog::ShowAskIdPw(SalString& DefId, SalString& Id, SalString& Pw)
{
	SalTransFrame512B msg;
	msg.SetMsgIniInfo(E_ITMT_ShowDialog, 0);
	uint32 u32 = E_AskAccountPw;
	msg.Write(&u32, sizeof(u32));
	char buf[40];
	StrNCpy(buf, title, sizeof(buf));
	msg.Write(buf, sizeof(buf));
	StrNCpy(buf, DefId.Str(), sizeof(buf));
	msg.Write(buf, sizeof(buf));
	SendMsg(msg.Header());
	if (RecMsg(E_ITMT_ShowDialog, waitTime, msg.Header().salHeader, msg.FrameBufLen()) == 0)
	{
		msg.Read(&u32, sizeof(u32));
		int32 i32;
		msg.Read(&i32, sizeof(i32));
		if (u32 == E_AskAccountPw)
		{
			if (i32 == 0)
			{
				msg.Read(&buf, sizeof(buf));
				DecryptData(buf, sizeof(buf), 156);
				Id = buf;
				msg.Read(&buf, sizeof(buf));
				DecryptData(buf, sizeof(buf), 56);
				Pw = buf;
				return 0;
			}
			else
			{
				return -2;
			}
		}
	}
	return -1;
}

spt::ApiIedToolsCascadeWnd::ApiIedToolsCascadeWnd(const char* Name)
	:IedToolsCascadeWnd(Name, 0, 0, 0, 0, 0)
{

}

spt::ApiIedToolsCascadeWnd::ApiIedToolsCascadeWnd(const char* Name, WndFunc EnterFunc, ApiIedToolsCascadeWnd* ChildWnd, WndFunc ExitFunc, const uint32* pDisp)
	: IedToolsCascadeWnd(Name, EnterFunc, ChildWnd, 0, ExitFunc, pDisp)
{

}

spt::ApiIedToolsCascadeWnd::ApiIedToolsCascadeWnd(const char* Name, WndFunc EnterFunc, WorkFunc WorkFunc, WndFunc ExitFunc, const uint32* pDisp)
	: IedToolsCascadeWnd(Name, EnterFunc, 0, WorkFunc, ExitFunc, pDisp)
{

}

