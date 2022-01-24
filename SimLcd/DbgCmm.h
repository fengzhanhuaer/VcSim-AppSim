#ifndef  DBGCMM_H
#define DBGCMM_H


namespace spt
{
	typedef SalCmmMsg<1400> DbgMsg;

	union DbgLogOnMsg
	{
		DbgMsg dbgMsg;
		struct
		{
			struct
			{
				SalCmmMsgHeader dbgheader;
				uint16 version;
			}header;
			uint8 buf[500];
		}msg;
	};

	class DbgSocket
	{
	public:
		int32 SetLocalIp(const char* Ip);
		int32 SetLocalIp(uint32 Ip);
		int32 SetRemoteIp(const char* Ip);
		int32 SetRemoteIp(uint32 Ip);
		int32 SetLocalPort(uint16 Port);
		int32 SetRemotePort(uint16 Port);
		virtual int32 Send(const void* buf, int32 bufLen, uint32 flags);
		virtual int32 SendTo(const void* buf, int32 bufLen, uint32 flags, uint32 Ip, uint16 Port);
		virtual int32 Recv(void* buf, int32 bufLen, uint32 flags);
		virtual int32 RecvFrom(void* buf, int32 bufLen, uint32 flags, uint32& Ip, uint16& Port);
		int32 Send(DbgMsg& Msg);
		int32 SendTo(const void* buf, int32 bufLen, uint32 flags);
		int32 Recv(DbgMsg& Msg);
		int32 RecvFrom(void* buf, int32 bufLen, uint32 flags);
		int32 SetSocketNonBlock(bool8 block);
		int32 SetSocketRecvTimeOut(int32 Sec, int32 uSec);
		int32 Bind();
		virtual int32 Connect();
		virtual void Close();
		bool8 IsOk() { return sock > 0; };
		uint32 SendOkCnt() { return sendOkCnt; }
		uint32 SendErrCnt() { return sendErrCnt; };
		uint32 RecvOkCnt() { return recvOkCnt; };
		uint32 RecvErrCnt() { return recvErrCnt; };
	public:
		u4bytes& RemoteIp() { return remoteIp; }
	public:
		DbgSocket();
		~DbgSocket();
	protected:
		u4bytes localIp;
		u2bytes localPort;
		u4bytes remoteIp;
		u2bytes remotePort;
		uint32 sendOkCnt;
		uint32 sendErrCnt;
		uint32 recvOkCnt;
		uint32 recvErrCnt;
		int32 sock;
	};

	class DbgUdpCmm :public DbgSocket
	{
	public:
		int32 CreatSocket();
	private:

	};

	class DbgUdpServer :public DbgUdpCmm
	{
	public:
		int32 Start();
		int32 StartNonBlock();
	};

	class DbgUdpClient :public DbgUdpCmm
	{
	public:
		int32 Start();
		int32 StartNonBlock();
	};

	class DbgTcpCmm :public DbgSocket
	{
	public:
		DbgTcpCmm();
		virtual int32 Send(const void* buf, int32 bufLen, uint32 flags);
		virtual int32 Recv(void* buf, int32 bufLen, uint32 flags);
		int32 CreatSocket();
		int32 Accept();
		bool8 IsClientOk();
		virtual void Close();
	protected:
		int32 clientsock;
	};
	class DbgTcpServer :public DbgTcpCmm
	{
	public:
		int32 Start();
		int32 StartNonBlock();
		void CloseListener();
		void CloseClient();
		bool8 IsReadAble();
	protected:

	};
	class DbgTcpClient :public DbgTcpCmm
	{
	public:
		int32 Start();
		int32 StartNonBlock();
		bool8 IsReadAble();
	};

	class DbgTcpGmCmm
	{
	public:
		void SetLinkOk(bool8 Ok);
		bool8 EnableGmssl(bool8 Enable);
		bool8 IsEnableGmssl() { return enableGmssl; }
	protected:
		bool8 enableGmssl;
		void* gmSock;
		bool8 gmlinkOk;
	};
	class DbgTcpGmServer :public DbgTcpServer, public DbgTcpGmCmm
	{
	public:
		bool8 IsLinkOk();
		virtual int32 Send(const void* buf, int32 bufLen, uint32 flags);
		virtual int32 Recv(void* buf, int32 bufLen, uint32 flags);
		virtual void Close();
		int32 GmAccept();
		int32 StartNonBlock();
		void CreatGmSock();
	};
	class DbgTcpGmClient :public DbgTcpClient, public DbgTcpGmCmm
	{
	public:
		bool8 IsLinkOk();
		virtual int32 Send(const void* buf, int32 bufLen, uint32 flags);
		virtual int32 Recv(void* buf, int32 bufLen, uint32 flags);
		virtual void Close();
		int32 StartNonBlock();
		int32 GmConnect();
		DbgTcpGmClient();
	};
	class UdpCmmTest :public Task, public DbgUdpServer
	{
	public:
		union TestMsg
		{
			struct
			{
				uint32 period;
				uint32 cmd;
				uint32 ser;
				uint32 remotedif;
				uint32 remoteser;
				uint32 remoteserlast;
			}msg;
			int32 data[64];
		};

		enum Step
		{
			E_PowerUpIni,
			E_WaitSendMsg,
			E_WaitRecvMsg,
		};

		UdpCmmTest();

		virtual int32 PowerUpIni(int32 Para);

		virtual int32 OneLoop();
		uint32 period;
		uint32 series;
		uint32 lastRemoteSer;
		uint32 lastRemoteSerLast;
		uint32 lastRemoteSerDif;
		MsTimer msTimer;
	};

}
#endif//DBGCMM_H
