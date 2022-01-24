#ifndef SALSAMPINTCMM_H
#define SALSAMPINTCMM_H
//��ģ�鲻�����̰߳�ȫ�ԣ������ڵ��̻߳�����ʹ��
namespace spt
{
#define CN_SAMPINTMSG_DATA_LEN	(1024*3-22)
	struct SampIntMsg
	{
		uint8 dstMac[6];
		uint8 surMac[6];
		uint16 frameType;
		uint16 res;
		uint16 frameLen;//��У��ͣ�����������
		uint8 buf[CN_SAMPINTMSG_DATA_LEN];
		bool8 IsSumOk();
	};
	enum SampIntMsgBufState
	{
		E_SIMBS_INI = 0,//Ĭ��̬
		E_SIMBS_ALLOCED = 0x01,//�ѷ���
		E_SIMBS_WRITING = 0x02,//��д��
		E_SIMBS_WRITED = 0x04,//��д��
		E_SIMBS_READING = 0x08,//����ȡ
		E_SIMBS_READED = 0x10,//�Ѷ�ȡ
	};
	struct SampIntMsgDesFlag
	{
		void PowerUpIni(SampIntMsg* Buf);
		int32 Write(void* Buf, int32 Len);
		int32 Read(void* Buf, int32 Len);
		//Len��sum
		int32 Write(uint16 Type, void* Buf, int32 Len);
		void SetWrited(uint16 Len);
		void SetReaded();
		uint32 state;
		int32 BufLen;
		int32 DataLen;
		SampIntMsg* pBuf;
	};
	struct SampIntMsgPool
	{
		void PowerUpIni(int32 BufNum);
		int32 Push(void* Buf, int32 Len);
		int32 Pop(void* Buf, int32 Len);
		SampIntMsgDesFlag* GetNextWriteDes();
		void UpdateWriter();
		SampIntMsgDesFlag* GetNextReadDes();
		void UpdateReader();
		bool8 IsFull();
		bool8 IsEmpty();
		void ClearData();
		uint32 SendMsgNum;
		uint32 RecvMsgNum;
		int32 DesNum;
		SampIntMsgDesFlag* Des;
		int32 Write;
		int32 Read;
	};
	class SptSampIntMsgProc
	{
	public:
		M_Singleton(SptSampIntMsgProc);
	public:
		int32 PowerUpIni(int32 Para);
		int32 Proc(int32 Para);
		int32 SendMsg(void* Buf, int32 Len);
		int32 RecvMsg(void* Buf, int32 BufLen);
		class FpgaMsgProc* FpgaMsgProc();
	public:

	protected:
		SptSampIntMsgProc();
	private:
		class FpgaMsgProc* fpgaMsgProc;
	};
}
#endif // !SALSAMPINTCMM_H

