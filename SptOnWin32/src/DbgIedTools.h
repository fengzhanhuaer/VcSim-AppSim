#ifndef DBGIEDTOOLS_H
#define DBGIEDTOOLS_H
namespace spt
{
	enum E_IedToolsMsgType
	{
		E_ITMT_HeartBeat = SalTransProtocol::E_PriDataTrans,
		E_ITMT_SockClose,
		E_ITMT_AskClientInfo,
		E_ITMT_AskClientInfoAck,
		E_ITMT_ShowDialog,
		E_ITMT_AskWnd,
		E_ITMT_AskWndAck,
		E_ITMT_EnterWnd,
		E_ITMT_EnterWndAck,
		E_ITMT_ShowWnd,
		E_ITMT_ShowWndAck,
		E_ITMT_ExitWnd,
		E_ITMT_ExitWndAck,
		E_ITMT_Total
	};
	struct IedToolHeartBeatMsg
	{
		SalTransHeader header;
		struct
		{
			SalDateStamp stamp;
			uint32 version;
			uint8 res[64];
		}data;
		uint16 crc;
	};
	class IedToolsDialog
	{
	public:
		enum Type
		{
			E_AskAccountPw,//索要帐号密码
		};
		IedToolsDialog(const char* Name, int32 WaitTime);
		int32 SetInfo(const char* Name, int32 WaitTime);
		int32 SendMsg(SalTransHeader& msg);
		int32 RecMsg(uint32 MsgType, int32 WaitTime, SalCmmMsgHeader& msg, uint32 MsgBufLen);
	protected:
		int32 waitTime;
		int32 result;
		char title[40];
	};

	class IedToolsTextWnd
	{
	public:
		typedef int32(*UpdateWndFunc)(class ApiIedToolsTextWnd* wnd);
	protected:
		UpdateWndFunc updateFunc;
		char title[40];
		String50kB text;
	};
	class IedToolsCascadeWnd
	{
	public:
		enum WndType
		{
			WT_Null,
		};
		struct IedToolsWndPara
		{
			uint32 sizePara;//客户端返回的sizeof(WndPara)
			bool8 isCheck1;
			bool8 isCheck2;
			bool8 isCheck3;
			bool8 isCheck4;
			bool8 isCheck5;
			bool8 isClick1;
			bool8 isClick2;
			bool8 isClick3;
			bool8 isClick4;
			bool8 isClick5;
			float64 Para1;
			float64 Para2;
			float64 Para3;
			float64 Para4;
			float64 Para5;
			SalDateStamp stamp1;
			SalDateStamp stamp2;
			char Str1[60];
			char Str2[60];
			char Str3[60];
		};
		struct Flags
		{
			bool8 isFirstCreat;//初次刷新
		};
	public:
		typedef bool8(*WndFunc)(class ApiIedToolsCascadeWnd* wnd);
		typedef int32(*WorkFunc)(class ApiIedToolsCascadeWnd* wnd, Flags& flag, IedToolsWndPara& Para);
		bool8 IsEnd();
		uint32 SetParent(IedToolsCascadeWnd* Wnd);
	protected:
		IedToolsCascadeWnd(const char* Name, WndFunc EnterFunc, class ApiIedToolsCascadeWnd* ChildWnd, WorkFunc WorkFunc, WndFunc ExitFunc, const uint32* pDisp);
	protected:
		IedToolsCascadeWnd* parent;
		uint32 wndId;
		uint32 firstChildId;
		uint32 lastChildId;
		WndFunc enterFunc;
		WorkFunc workFunc;
		WndFunc exitFunc;
		IedToolsCascadeWnd* childWnd;
		char title[40];
		const uint32* pdisp;
		friend class IedToolsServer;
	};
	class IedToolsServer :public Task
	{
	public:
		enum TaskStepStatus
		{
			E_PowerUpIni,
			E_WaitClient,
			E_ClientIni,
			E_Work,
			E_Check,
		};
	public:
		int32 StartServer(uint32 LocalIp, uint16 LocalPort, uint32 RemoteIp, uint16 RemotePort, int32 ClientSock);
		void SetIedToolsWndRoot(class ApiIedToolsCascadeWnd* Wnd);
		virtual int32 PowerUpIni(int32 Para);
		virtual int32 OneLoop();
		int32 RecMsg(SalCmmMsgHeader& msg, uint32 MsgBufLen);
		int32 RecMsg(uint32 MsgType, int32 WaitTime, SalCmmMsgHeader& msg, uint32 MsgBufLen);
		int32 SendMsg(SalCmmMsgHeader& msg);
		int32 SendMsg(SalCmmMsgHeader& msg, uint32 DataLen);
		int32 SendMsg(SalTransHeader& msg);
		void SendHeartBeat();
		M_Singleton(IedToolsServer);
	protected:
		IedToolsServer();
		int32 Check();
		int32 Work();
		int32 Unpack(SalCmmMsgHeader& msg);
		int32 CloseSock();
		int32 SendCascadeWnd(IedToolsCascadeWnd* Wnd);
		int32 EnterWnd(IedToolsCascadeWnd* Wnd);
		IedToolsCascadeWnd* SearchBoard(IedToolsCascadeWnd* RootBook, uint32 Id);
	protected:
		class IedToolsCascadeWnd* wndRoot;
		MsTimer checkTimer;
		MsTimer heartbeatTimer;
		uint8 lastSec;
		SemaphoreB msgSem;
		uint32 recMsgOkCnt;
		uint32 recMsgLastOkCnt;
		uint32 recMsgErrCnt;
		uint32 sendMsgOkCnt;
		uint32 sendMsgErrCnt;
		DbgTcpGmServer gmSock;
		bool8 isLogOn;
	};
}
#endif // !DBGIEDTOOLS_H

