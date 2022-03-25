#ifndef DBGIEDTOOLS_H
#define DBGIEDTOOLS_H
namespace spt
{
	typedef  SalCmmMsg<1024 * 60> IedToolsMsg60kb;
	typedef  SalCmmMsg<1024 * 10> IedToolsMsg10kb;
	typedef  SalCmmMsg<1024 * 5> IedToolsMsg5kb;
	typedef  SalCmmMsg<1024 * 1> IedToolsMsg1kb;

	enum E_IedToolsMsgType
	{
		E_ITMT_HeartBeat = SalTransProtocol::E_PriDataTrans,
		E_ITMT_SockClose,
		E_ITMT_AskClientInfo,
		E_ITMT_AskClientInfoAck,
		E_ITMT_Total
	};
	struct IedToolsMsgHeader :public SalTransHeader
	{
		void SetHeader(uint32 Type, uint32 unPackIndex, uint32 DataLen);
	};
	struct IedToolHeartBeatMsg
	{
		IedToolsMsgHeader header;
		struct
		{
			SalDateStamp stamp;
			uint32 version;
			uint8 res[64];
		}data;
		uint16 crc;
	};
	struct IedToolsMsg :public IedToolsMsgHeader
	{
		uint8 data[2048];
		uint16 crc;
	};
	struct IedToolMsgCtrl
	{
		void SetMsgIniInfo(uint32 Type, uint32 unPackIndex);
		int32 Write(void* Data, uint32 Len);
		IedToolsMsgHeader& Header();
	private:
		IedToolsMsg msg;
		uint32 writer;
		uint32 reader;
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
		virtual int32 PowerUpIni(int32 Para);
		virtual int32 OneLoop();
		int32 RecMsg(SalCmmMsgHeader& msg);
		int32 SendMsg(SalCmmMsgHeader& msg);
		int32 SendMsg(SalCmmMsgHeader& msg, uint32 DataLen);
		int32 SendMsg(IedToolsMsgHeader& msg);
		M_Singleton(IedToolsServer);
	protected:
		IedToolsServer();
		int32 Check();
		int32 Work();
		int32 CloseSock();
	protected:
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
		IedToolsMsg60kb* recMsgBuf;
		IedToolsMsg60kb* sendMsgBuf;
	};
}
#endif // !DBGIEDTOOLS_H

