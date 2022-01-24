#ifndef SALCMM_H
#define SALCMM_H

namespace spt
{
	enum SalCmmType
	{
		SCT_NULL,
		SCT_LCD,
		SCT_AppInnerData,//Ӧ�������ݣ�����оƬ��
		SCT_AppFastCmm,//Ӧ��Ƭ�⽻����������
		SCT_AppSlowCmm,//Ӧ��Ƭ�⽻����������
		SCT_SptInnerData,//ƽ̨���ݣ�����оƬ��
		SCT_SptFastCmm,//ƽ̨Ƭ�⽻����������
		SCT_SptSlowCmm,//ƽ̨Ƭ�⽻����������
	};
	struct SalCmmMsgHeader
	{
		uint16 header;
		uint16 sur;
		uint16 dst;
		uint16 type;
		uint16 len;//��header��checkcode(����)
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
		uint32 bufSize;//��header��ʼ��ͷ����
		bool8 isCheckOk;
		bool8 isUsed;
		bool8 isFree;
		uint8 state;
		uint32 ctxLen;//���ݳ��Ⱥ�ͷ��У���
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
		uint32 SnedRepeatCnt;//�ط�����
		uint32 LastSendMs;
		uint32 SendMsgCnt;//��Ӧ�ò�ʹ��
		uint32 SendMsgLastCnt;//��Ӧ�ò�ʹ��
		bool8 HasNewToRecv;//��Ӧ�ò�ʹ��
		bool8 recvMutex;
		uint32 RecvState;//��Ӧ�ò�ʹ��
		uint32 RecvMsgCnt;//��Ӧ�ò�ʹ��
		uint32 RecvMsgLastCnt;//��Ӧ�ò�ʹ��
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
		virtual int32 ProcIn() = 0;
		virtual int32 Proc() = 0;
		virtual int32 ProcOut() = 0;
		uint16 Sur() { return frmHeader.sur; };
		uint16 Dst() { return frmHeader.dst; };
		uint16 Type() { return frmHeader.type; };
		uint16 FrameBufLen() { return frameBufLen; };
		struct stOutPut& OutPut() { return outPut; };
	protected:
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

}


#endif // !SALCMM_H
