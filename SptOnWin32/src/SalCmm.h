#ifndef SALCMM_H
#define SALCMM_H

namespace spt
{
	enum SalCmmType
	{
		SCT_NULL,
		SCT_LCD,
		SCT_AppInnerData,//应用内数据（不出芯片）
		SCT_AppFastCmm,//应用片外交互快速数据
		SCT_AppSlowCmm,//应用片外交互慢速数据
		SCT_SptInnerData,//平台数据（不出芯片）
		SCT_SptFastCmm,//平台片外交互快速数据
		SCT_SptSlowCmm,//平台片外交互慢速数据
		SCT_IEDTools,
		SCT_DBGTools,
	};
	struct SalCmmMsgHeader
	{
		uint16 header;
		uint16 sur;
		uint16 dst;
		uint16 type;
		uint16 len;//由header至checkcode(不含)
		uint16 res;
		uint16 CalcCrc();
		uint16 AddCrc();
		uint16 IsCrcOk();
	};
	template <uint32 BufMaxLen>
	struct SalCmmMsg
	{
		SalCmmMsgHeader header;
		uint8 data[BufMaxLen];
		uint16 checkCode;
		uint16 res;
	};

	struct SalCmmEthNetPara
	{
		CfgUint32 port;
		CfgIp ip;
		CfgIp musk;//musk
		CfgIp gate;
		CfgMac mac;
		CfgHex32 exInfo;
	};

	typedef SalCmmMsg<2> SalCmmTemplateHeader;
	enum SalCtrlState
	{
		E_SCS_Inied = 0,
		E_SCS_Alloced = 0x01,
		E_SCS_Writing = 0x02,
		E_SCS_Writed = 0x04,
		E_SCS_Reading = 0x08,
		E_SCS_Readed = 0x10,
	};
	struct SalCmmMsgBufCtrl
	{
		uint32 bufSize;//由header开始的头长度
		bool8 isCheckOk;
		bool8 isUsed;
		bool8 isFree;
		uint8 state;
		uint32 ctxLen;//内容长度含头与校验和
		struct SalCmmMsgCtrlPool* pool;
		SalCmmTemplateHeader* buf;
		void PowerUpIni(uint32 BufSize);
		void FreeBuf();
		void SetFlag(uint32 Flag);
		void UnSetFlag(uint32 Flag);
		void SetWrited();
		void SetReaded();
		uint16 CalcCrc();
		uint16 AddCrc();
		uint16 IsCrcOk();
	};
	struct SalCmmMsgCtrlPool
	{
		uint32 bufNum;
		uint32 reader;
		uint32 writer;
		uint32 usedNum;
		struct OutPut
		{
			uint32 writeCnt;
			uint32 getWriteBufErrCnt;
			uint32 readCnt;
		}outPut;
		SalCmmMsgBufCtrl* Ctrl;
		void PowerUpIni(uint32 BufNum, uint32 BufSize);
		SalCmmMsgBufCtrl* GetNextWriteBuf();
		SalCmmMsgBufCtrl* GetNextReadBuf();
		void UpdateReader();
		void FreeBuf(SalCmmMsgBufCtrl* Ctrl);
		void FreeAllBuf();
	};
	typedef int32(*SalCmmMsgSendFunc)(class SalCmmChannel* Cmm, struct CmmMsgDriver* Driver);
	typedef int32(*SalCmmMsgRecvFunc)(class SalCmmChannel* Cmm, struct CmmMsgDriver* Driver, SalCmmMsgHeader* Header);
	struct CmmMsgDriver
	{
		char Name[20];
		uint32 Index;
		uint32 Type;
		SalCmmMsgSendFunc SendFunc;
		SalCmmMsgRecvFunc RecvFunc;
		void* SendPtr;
		uint32 SendPara;
		void* RecvPtr;
		uint32 RecvPara;
		bool8 sendMutex;
		bool8 HasNewToSend;
		uint32 SendState;
		uint32 SnedRepeatCnt;//重发次数
		uint32 LastSendMs;
		uint32 SendMsgCnt;//供应用层使用
		uint32 SendMsgLastCnt;//供应用层使用
		bool8 HasNewToRecv;//供应用层使用
		bool8 recvMutex;
		uint32 RecvState;//供应用层使用
		uint32 RecvMsgCnt;//供应用层使用
		uint32 RecvMsgLastCnt;//供应用层使用
	};
	class SalCmmChannel
	{
	public:
		struct stOutPut
		{
			uint32 recvCnt;
			uint32 recvErrCnt;
			uint32 sendCnt;
			uint32 sendErrCnt;
		};
		const char* Name() { return name; }
		virtual int32 ProcIn() = 0;
		virtual int32 Proc() = 0;
		virtual int32 ProcOut() = 0;
		uint16 Sur() { return frmHeader.sur; };
		uint16 Dst() { return frmHeader.dst; };
		uint16 Type() { return frmHeader.type; };
		uint16 FrameBufLen() { return frameBufLen; };
		struct stOutPut& OutPut() { return outPut; };
		CmmMsgDriver* Driver(int32 DriverIndex) { return &driver[DriverIndex]; };
		uint32 DriverNum() { return driverNum; };
	protected:
		SalCmmChannel();
	protected:
		char name[20];
		struct stOutPut outPut;
		SalCmmMsgCtrlPool appSendMsgPool;
		SalCmmMsgCtrlPool appRecMsgPool;
		uint16 frameBufLen;
		RingCharBuf halSendPool;
		RingCharBuf halRecvPool;
		CmmMsgDriver* driver;
		uint32 driverNum;
		SalCmmMsgHeader frmHeader;
	};
	struct SalTransHeader
	{
		int32 SetHeader(uint16 Type, uint16 UnpackIndex, uint16 DataLen);
		SalCmmMsgHeader salHeader;
		uint16 unPackIndex;
		uint16 type;
		uint16 dataLen;//数据长度，不含头与校验和
		uint16 res;
	};
	struct SalTransFrame
	{
		SalTransHeader Header;
		uint8 data[1];
	};
	struct SalTransFrameCtrl
	{
	public:
		SalTransFrameCtrl(SalTransFrame* Frame, uint32 DataBufLen);
		void SetMsgIniInfo(uint32 Type, uint32 unPackIndex);
		SalTransHeader& Header() { return frame->Header; }
		uint32 DataBufLen() { return dataBufLen; };
		uint32 FrameBufLen() { return dataBufLen + sizeof(SalTransHeader); };
		int32 Write(void* Data, uint32 DataLen);
		int32 Write(uint32& Data) { return Write(&Data, sizeof(Data)); }
		int32 Write(uint16& Data) { return Write(&Data, sizeof(Data)); }
		int32 Write(uint8& Data) { return Write(&Data, sizeof(Data)); }
		int32 Read(void* Data, uint32 DataBufLen);
		int32 Read(uint32& Data) { return Read(&Data, sizeof(Data)); }
		int32 Read(uint16& Data) { return Read(&Data, sizeof(Data)); }
		int32 Read(uint8& Data) { return Read(&Data, sizeof(Data)); }
	protected:
		uint32 reader;
		uint32 writer;
		uint32 dataBufLen;
		SalTransFrame* frame;
	};
	template <const uint32 CN_DataBufLen>
	struct SalTransFrameBufCtrl :public SalTransFrameCtrl
	{
		SalTransFrameBufCtrl() :SalTransFrameCtrl((SalTransFrame*)&frame, CN_DataBufLen) {}
	protected:
		struct Frame
		{
			SalTransHeader Header;
			uint8 data[CN_DataBufLen];
		}frame;
	};
	typedef SalTransFrameBufCtrl<256> SalTransFrame256B;
	typedef SalTransFrameBufCtrl<512> SalTransFrame512B;
	typedef SalTransFrameBufCtrl<1024> SalTransFrame1kB;
	typedef SalTransFrameBufCtrl<2048> SalTransFrame2kB;
	typedef SalTransFrameBufCtrl<1024 * 5> SalTransFrame5kB;
	typedef SalTransFrameBufCtrl<1024 * 10> SalTransFrame10kB;
	typedef SalTransFrameBufCtrl<1024 * 60> SalTransFrame60kB;

	class SalTransCmm :public SalCmmChannel
	{
	public:
		static const uint32 SalTransFrameHeaderLen = sizeof(SalTransHeader);
		void PowerUpIni(uint32 AppSendBufLen, uint32 AppSendBufNum, uint32 AppRecvBufLen, uint32 AppRecvBufNum, uint32 HalSendBufLen, uint32 HalRecvBufLen);
		int32 SendMsg(uint32 UnPackIndex, uint16 Type, uint16 DataLen, void* Data);
		virtual int32 SendMsgTo(uint16 Dst, uint32 UnPackIndex, uint16 Type, uint16 DataLen, void* Data);
	protected:
		SalTransCmm();
	};
	class SalTransProtocol
	{
	public:
		enum Type
		{
			E_FileTrans = 0x0101,
			E_ParaTrans = 0x0102,
			E_MsgTrans = 0x0103,
			E_PriDataTrans = 0x8000,
		};
		enum Result
		{
			E_SendOk = 0,//发送成功
			E_SendErr = -1,//发送失败
			E_NoExist = -2,//发送失败
			E_TooLarge = -3,//发送失败
			E_InfoErr = -4,//发送失败
			E_ReadLenErr = -5,//文件读取异常
			E_RecvOk = 0,//接收成功
			E_RecvErr = -10000,//接收失败
			E_CheckErr = -10001,//校验失败
			E_RecvOverTime = -1000000,
		};
		enum Process
		{
			E_Begin,
			E_SendStart,
			E_SendStartAck,
			E_Trans,
			E_TransAck,
			E_TransErr,
			E_TransErrAck,
			E_Check,
			E_CheckAck,
			E_SendEnd = 1000000,
		};
	public:
		SalTransProtocol(AdtBufDes& recMsg, SalCmmChannel* Cmm, uint16 Dst, struct CmmMsgDriver* Driver);
		int32 Recv(struct CmmMsgDriver* Driver, SalCmmMsgHeader* Header);
		int32 SendMsg(uint16 DataLen, void* Data);
		enum Process GetProcess() { return (Process)process; };
		int32 GetRusult() { return result; }
		uint16 Dst() { return dst; }
	protected:
		int32 WaitMsg(uint32 Type, int32 Ms);
		int32 WaitMsgOk(uint32 Type, int32 Ms);
		int32 WaitMsgOk(uint32 Type, int32*& Info, int32 Ms);
		void LogInfo(SalString& Info, bool8 toPrc, bool8 toPrt);
	protected:
		int32 logStep;
		int32(*infoFunc)(int32 Step, const char* info);
		AdtBufDes& recMsg;
		bool8 recOk;
		SalTransCmm* cmm;
		uint16 dst;
		struct CmmMsgDriver* driver;
		int32 result;
		int32 process;
	};
	class SalFileTrans :public SalTransProtocol
	{
	public:

	public:
		SalFileTrans(AdtBufDes& recMsg, SalCmmChannel* Cmm, uint16 Dst, struct CmmMsgDriver* Driver);
		int32 Recv(struct CmmMsgDriver* Driver, SalCmmMsgHeader* Header);
		int32 Send(int32(*Process)(int32 Step, const char* info), const char* SurFile, const char* DstFile);
		SalString& DstFile() { return dstFile; };
	protected:

	protected:
		String100B  surFile;
		String100B  dstFile;
		uint32 fileSize;
	};
	class SalParaTrans :public SalTransProtocol
	{
	public:

	public:
		SalParaTrans(AdtBufDes& recMsg, AdtBufDes& editMsg, SalCmmChannel* Cmm, uint16 Dst, struct CmmMsgDriver* Driver);
		int32 Recv(struct CmmMsgDriver* Driver, SalCmmMsgHeader* Header);
		int32 Send(int32(*Process)(int32 Step, const char* info), uint32 Zone, const char* DesFile);
	protected:

	protected:
		AdtBufDes& editMsg;
		String40B  desFile;
		uint32 zone;
		uint32 paraLen;//(含CRC)
		class SalParaGroup* paraGroup;
	};
	class SalMsgTrans :public SalTransProtocol
	{
	public:
		struct Msg
		{
			uint32 type;
			int32 paras;
			uint32 msgLen;
			uint8 data[1];
		};
		struct SalMsg
		{
			SalTransHeader tsheader;
			Msg msg;
		};
	public:
		SalMsgTrans(AdtBufDes& recMsg, SalCmmChannel* Cmm, uint16 Dst, struct CmmMsgDriver* Driver);
		int32 Recv(struct CmmMsgDriver* Driver, SalCmmMsgHeader* Header);
		int32 WaitMsg(uint32 Type, struct Msg*& Msg, int32 Ms);
		int32 Send(uint32 Type, int32 Para, uint8* Msg, uint32 MsgLen);
	protected:

	protected:
		String40B  desFile;
		uint32 zone;
	};
}


#endif // !SALCMM_H
