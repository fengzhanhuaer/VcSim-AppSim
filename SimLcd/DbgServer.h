#ifndef DBGSERVER_H
#define DBGSERVER_H

namespace spt
{
	class DbgServer :public DbgTcpGmServer, public Task
	{
	public:
		struct MsgHeadr
		{
			uint16 header;
			uint16 type1;
			uint16 type2;
			uint16 total;
			uint16 series;
			uint16 len;//从帧头至校验和(含)
			uint8 data[4];
		};
		struct Msg5K
		{
			uint16 header;
			uint16 type1;
			uint16 type2;
			uint16 total;
			uint16 series;
			uint16 len;//从帧头至校验和(含)
			uint8 data[1024 * 5];
			int32 GetDataLen();
			void AddSum();
			void Set(uint16 Type1, uint16 Type2, uint16 Seri, uint16 Total);
			uint16 Write(const void* Sur, uint16 Len);
			bool8 IsSumOk();
		};
		struct MsgCtrl
		{
			void SetMsg5KBuf(Msg5K* Buf);
			uint16 Read(void* Dst, uint16 Len);
			uint16 reader;
			uint16 msgLen;
			Msg5K* buf;
		};
		enum TaskStep
		{
			E_PowerUpIni,
			E_WaitMsg,
			E_RecNoMsgDelay,
			E_RecFullMsg,
			E_UnpackMsg,
		};
		static const uint16 Header = 0xd555;
		static const uint16 HeaderLen = sizeof(MsgHeadr) - 4;
		enum MSG_TYPE1
		{
			E_MSG_HELLO = 0x0001,
			E_MSG_Real_Stamp = 0x0002,
			E_MSG_File_Trans = 0x0003,
		};
	public:
		M_Singleton(DbgServer);
		int32 StartServer();
		bool8 IsRuning();
		int32 CheckStatus(bool8 Restart);
		virtual int32 PowerUpIni(int32 Para);
		virtual int32 OneLoop();
		void UnpackMsg(Msg5K* Msg);
		int32 RecvMsg(Msg5K* Msg, int32 Ms);
		virtual int32 Send(const void* buf, int32 bufLen, uint32 flags);
		int32 Send(Msg5K* Msg);
	protected:
		DbgServer();
	protected:
		MsTimer msgTimer;
		MsTimer checkTimer;
		SingleCharBuf MsgBuf;
		uint32 recvPacket;
		uint32 recvPacketLast;
		uint32 recvPacketErr;
		uint32 sendPacket;
		uint32 sendPacketLast;
		class FileTrans* fileTrans;
		const struct ApiAppCfg* appCfg;
	};

	class FileTrans
	{
	public:
		FileTrans();
		enum FileMsgType
		{
			E_ASK_PATH_Info = 1,
			E_SendStart = 2,
			E_SendIng = 3,
			E_SendEnd = 4,
			E_ASK_File = 5,
			E_PushFileApply = 6,
			E_PushFile = 7,
			E_Info = 8,
			E_ASK_PathRoot = 9,
			E_DeleteFile = 10,
		};
		enum FileErrType
		{
			E_Null,
			E_NoExist,
			E_OpenErr,
			E_ReadErr,
			E_WriteErr,
			E_DeleteErr,
			E_Err,
		};
	public:
		virtual int32 RecvMsg(DbgServer::Msg5K* msg);
	protected:
		DbgServer* server;
	};
	class FileTransGzk :public FileTrans
	{
	public:
		virtual int32 RecvMsg(DbgServer::Msg5K* msg);
		void SendPathInfo(DbgServer::Msg5K* msg);
		void SendDirInfo(const char* Dir, int Dep);
		void SendInfo(uint32 Mode, int64 date, uint32 Size, const char* Dir);
		void TransFile(const char* File);
		void RecvFile(DbgServer::Msg5K* msg);
		void ReplyPathRoot(DbgServer::Msg5K* msg);
		void DeleteFile(DbgServer::Msg5K* msg);
	};

}



#endif // !DBGSERVER_H

