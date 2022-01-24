#ifndef HALBOARDIO_H
#define HALBOARDIO_H

namespace spt
{
	struct SampCell
	{
		uint32 q;
		u32value value;
	};
	enum NormalBoardCmmType
	{
		E_Board_YX_1 = 1,//ң�ſ����ң�Ű忨֡
		E_Board_Ang_1,//ģ��������忨֡
		E_Board_Do_1,//Do֡
		E_Board_DIO_1,//DIO֡
		E_Board_Dc_1,//DC����֡
		E_Board_OPB_YX_1,//OPB�忨��YX�忨
	};
	struct GzkBoardCmmIoNorDIFrame
	{
		uint8 frm_header;//֡ͷ
		uint8 frm_len;//֡��
		uint8 type_addr;//�忨����_��ַ
		uint8 frm_no;//ÿ֡��һ����������
		uint8 frm_status_type;//�忨״̬��Ϣ
		uint8 frm_status1;
		uint8 frm_status2;
		uint8 DigitalInput1;
		uint8 DigitalInput2;
		uint8 DigitalInput3;
		uint8 DigitalInput4;
		uint8 frm_sumL;//У���
		uint8 frm_sumH;
	};
	struct GzkBoardCmmIoNorDOFrame
	{
		uint8 frm_header;//֡ͷ
		uint8 frm_len;//֡��
		uint8 type_addr;//�忨����_��ַ
		uint8 frm_st;//
		uint8 frm_sq;//
		uint8 frm_status_type;//�忨״̬��Ϣ
		uint8 frm_status1;
		uint8 frm_status2;
		uint8 start;
		uint8 board0L;
		uint8 board0H;
		uint8 board1L;
		uint8 board1H;
		uint8 board2L;
		uint8 board2H;
		uint8 board3L;
		uint8 board3H;
		uint8 board4L;
		uint8 board4H;
		uint8 board5L;
		uint8 board5H;
		uint8 crc;
		uint8 frm_sumL;//У���
		uint8 frm_sumH;
	};
	/// <summary>
	/// Len����Ϊ2��ָ����
	/// </summary>
	/// <typeparam name="T1"></typeparam>
	template<typename T1, const uint32 Len>
	struct SampRingBuf
	{
	public:
		static SampRingBuf* Alloc()
		{
			return (SampRingBuf*)spt::Calloc(1, sizeof(SampRingBuf<T1, Len>));
		}
		bool8 Push(const T1* Cell)
		{
			sampBuf[writer] = *Cell;
			writer++;
			writer = (writer >= Len ? 0 : writer);
			writed++;
			return 1;
		}
		const T1* Pop()
		{
			if (reader != writer)
			{
				const T1* p = &sampBuf[reader];
				reader++;
				reader = (reader >= Len ? 0 : reader);
				readed++;
				return p;
			}
			return 0;
		}
		const T1* Get()
		{
			const T1* p = &sampBuf[reader];
			return p;
		}
		const T1* GetNewWrited(uint32 Index)
		{
			uint32 r = (writer + Len - Index - 1);
			r = (r >= Len ? 0 : r);
			const T1* p = &sampBuf[r];
			return p;
		}
		T1* GetNextWriteBuf()
		{
			return  &sampBuf[writer];
		}
		uint32 WriterAdd(int32 Add)
		{
			writer += Len + Add;
			writer = (writer >= Len ? 0 : writer);
			writed += Add;
			return writer;
		}
	public:
		uint32 reader;
		uint32 writer;
		uint32 writed;
		uint32 readed;
		T1 sampBuf[Len];
	};
	class HalBoard :public InstObjectGroup
	{
	public:
		enum HalInstType
		{
			E_BoardBegin = 0,
			//����忨���Ͷ���
			E_Board_YX32Pin_1 = E_BoardBegin,//32��ң�ſ����ң�Ű忨
			E_Board_Do32Pin_1,//32��Do����
			E_Board_Dc32Pin_1,//32��DC������
			E_Board_Ang24Pin_1,//24��ģ��������忨
			E_Board_DIO_YX14_1,//DIO�忨��YX�忨
			E_Board_DIO_DO7_1,//DIO�忨��DO�忨
			E_Board_OPB_YX_1,//OPB�忨��YX�忨
			E_Board_GoSv_1,
			//����忨���Ͷ���
			E_Vir_Board_SV_DataSetIn1 = 100000,//ģ�����������ݼ�
			E_Vir_Board_SV_DataSetOut1,//ģ����������ݼ�
			E_Vir_BoardCMM_SV_DataSetIn1,//���ģ�����������ݼ�
			E_Vir_BoardCMM_SV_DataSetOut1,//���ģ����������ݼ�
			E_Vir_Board_AngIn_1,//����忨ģ��������
			E_Vir_Board_AngOut_1,//����忨ģ�������
			E_Vir_Board_GoIn_1,//Goose����
			E_Vir_Board_GoOut_1,//Goose���
			E_Vir_Board_FrameGoIn_1,//Goose����
			E_Vir_Board_FrameGoOut_1,//Goose���
			E_BoardEnd,
		};
		struct stOutStatus
		{
			SalComVersion Version1;//�汾��
			SalComVersion Version2;//���ã�������CPU/FPGA��ʱ��
			uint32 recvFrameOkCnt;//����֡����
			uint32 recvFrameErrCnt;//����֡����
			uint32 sendFrameOkCnt;//����֡����
			uint32 sendFrameErrCnt;//����֡����
			uint32 checkStatus1;//�Լ�״̬1
			uint32 checkStatus2;//�Լ�״̬2
			TaskRunInfo runInfo;//����ͳ��
		};
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum);
		class HalIoCell* GetIoCell(uint32 Index);
		uint32 StateNumb();//״̬���
		uint32 SequenceNumb();//˳�����
		const struct SalDateStamp& Stamp();
		uint32 CardAddr();
		uint32 SetCardAddr(uint32 CardAddr);
		uint32 IoType();
		bool8 IsIoType(int32 IoType);
		uint32 CmmType();
		bool8 IsCmmType(int32 CmmType);
		virtual int32 ProcIni();
		virtual int32 ProcIn();
		virtual int32 ProcOut();
		uint32 SetFrameIndex(uint32 FrameIndex);
		uint32 FrameIndex();
		HalBoard* VirBoard();
		void SetVirBoard(HalBoard* VirBoard);
		stOutStatus& OutStatus() { return ostatus; };
	protected:
		struct SalDateStamp stamp;
		stOutStatus ostatus;
		uint32 stateNmb;
		uint32 sequenceNmb;
		uint32 ioType;
		uint32 cmmType;
		uint32 cardAddr;
		uint32 frameIndex;
		HalBoard* virBoard;
	};
	class HalIoCell :public InstObject
	{
	public:
		enum HalInstType
		{
			E_IoCellBegin = 0,
			E_Normal_YX = E_IoCellBegin,//����ң�ſ���
			E_Normal_Ang,//����ģ��������
			E_Normal_DC,//����ֱ������
			E_Normal_Prot_Start,//���汣����������
			E_Normal_Sinal_Do,//�����źų���
			E_Normal_Prot_Do,//���汣������
			E_9_2_Ang_In,
			E_9_2_Ang_Out,
			E_Local_9_2_Ang_In,
			E_Local_9_2_Ang_Out,
			E_Go_BOOL_In1,
			E_Go_Dp_In1,
			E_Go_Int32_In1,
			E_Go_UInt32_In1,
			E_Go_Float32_In1,
			E_Go_Union32_In1,
			E_Go_Utc_In1,
			E_Go_BOOL_Out1,
			E_Go_Dp_Out1,
			E_Go_Int32_Out1,
			E_Go_UInt32_Out1,
			E_Go_Float32_Out1,
			E_Go_Union32_Out1,
			E_Go_Utc_Out1,
			E_IoCellEnd
		};
		void PowerUpIni(const char* Name, const char* DesName, class  HalBoard* Group, HalBoard* virBoard, uint32 IoType, uint32 Node);
		uint32 StateNumb();//״̬���
		uint32 SequenceNumb();//˳�����
		uint32 Node();
		uint32 IoType();
		HalBoard* VirBoard();
		void SetVirBoard(HalBoard* VirBoard);
		uint32 SetFrameIndex(uint32 FrameIndex);
		uint32 FrameIndex();
		bool8 blSignalForce() { return blsignalForce; };
		bool8 blSignalForce(bool8 Flag) { return blsignalForce = Flag; };
	protected:
		bool8 blsignalForce;
		uint32 stateNmb;
		uint32 sequenceNmb;
		uint32 ioType;
		uint32 node;
		uint32 frameIndex;
		HalBoard* virBoard;
	};




}

#endif // !HALBOARDIO_H

