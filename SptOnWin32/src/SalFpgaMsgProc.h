#ifndef SALFPGAMSGPROC_H
#define SALFPGAMSGPROC_H

namespace spt
{
	union CpuFpgaCmmMsg
	{
		SampIntMsg msg;
		struct
		{
			uint8 dstMac[6];
			uint8 surMac[6];
			uint16 frameType;
			uint16 res;
			uint16 frameLen;//含校验和，数据区长度
			uint8 dstMac1[6];
			uint8 surMac1[6];
			uint16 frameType1;
			uint16 res1;
			uint16 frameLen1;//含校验和，数据区长度
			uint8 data1[CN_SAMPINTMSG_DATA_LEN - 18];
		}BoardCmm;
	};
	struct CpuFpgaCmmMsgBuf
	{
		CpuFpgaCmmMsgBuf();
		CpuFpgaCmmMsg msg;
		uint16 reader;
		uint16 writer;
		int32 SlowSend(int32 EmacNo, uint16 Type);
		int32 IntSend(int32 EmacNo, uint16 Type);
		int32 RtSend(int32 EmacNo, uint16 Type);
		int32 BoardCmmSlowSend(int32 EmacNo, uint16 Dst, uint16 Type);
		int32 BoardCmmIntSend(int32 EmacNo, uint16 Dst, uint16 Type);
		uint16 Write(void* Sur, uint16 Size);
		bool8 IsCmmSumOk();
		bool8 IsBoardCmmSumOk();
		uint16 CalcSum();
		uint16 AddSum();
	};
	class FpgaMsgProc
	{
	public:
		typedef void (*CmmCallBack)(void*);
		enum MsgType
		{
			E_CPU_FPGA_Time = 0x2200,//时间控制帧
			E_CPU_FPGA_AngQ = 0x2201,//模拟量品质信息
			E_CPU_FPGA_CfgCtrl = 0x2202,//配置发送控制信息
			E_CPU_FPGA_ADCOE = 0x2203,//AD校准系数
			E_CPU_FPGA_ADADJUST = 0x2204,//AD微调系数
			E_CPU_FPGA_SVSUB = 0x2210,//SV订阅信息
			E_CPU_FPGA_SVSELECT = 0x2211,//SV挑数信息
			E_CPU_FPGA_GOSUB1 = 0x2220,//GO订阅信息
			E_CPU_FPGA_GOSUB2 = 0x2221,//GO订阅信息
			E_CPU_FPGA_GOSELECT1 = 0x2222,//GO挑数信息
			E_CPU_FPGA_GOSELECT2 = 0x2223,//GO挑数信息
			E_CPU_FPGA_GOSELECT3 = 0x2224,//GO挑数信息
			E_CPU_FPGA_GOPUB1 = 0x2230,//GO发布信息
			E_CPU_FPGA_SVPUB1 = 0x2240,//SV发布信息
			E_CPU_FPGA_SVPUB2 = 0x2241,//SV发布信息
			E_CPU_FPGA_SVPUB3 = 0x2242,//板间SV发布信息
			E_CPU_FPGA_BOARD_CMM = 0x2251,//板间CPU信息
			E_Board_Cmm_C2F = 0x2250,//CPU向FPGA下发的板间交互信息帧
			E_Board_Cmm_F2C = 0x8850,//FPGA发送的板间交互信息
			E_Board_FPGA_Update = 0x8855,
			E_WIN32_Sim = 0x3232,
			E_FPGA_CPU_HIO_CMM = 0x8811,//硬件分板卡交互
			E_FPGA_CPU_TIME = 0x8810,//时间信息帧
			E_FPGA_CPU_AngSamp_CMM = 0x8820,//模拟量采样交互帧
			E_FPGA_CPU_SVCB_STATE = 0x8821,//SV控制块状态
			E_FPGA_CPU_GOCB_POSSUB = 0x8830,//GOPOS状态
			E_FPGA_CPU_GOCB_ANGSUB = 0x8831,//GOANG状态
			E_FPGA_CPU_GOCB_STATE = 0x8832,//GO控制块状态
			E_FPGA_CPU_BOARD_STATE = 0x8840,//板卡状态
			E_FPGA_CPU_BOARD_LIGHT = 0x8841,//激光头信息
			E_FPGA_CPU_Board_CMM = 0x8851,//CPU板间交互
		};
		enum MsgWIN32Type
		{
			E_NULL,
			E_WIN32_SV_IN,
			E_WIN32_GO_IN,
		};
	public:
		FpgaMsgProc();
		~FpgaMsgProc();
		virtual int32 PowerUpIni(int32 Para);
		virtual int32 SendProc();
		virtual int32 RecvProc();
		virtual int32 RtSend(uint32 No,void* Buf, int32 MsgLen);
		virtual int32 RtRecv(uint32 No, void* Buf, int32 BufLen);
		int32 IntSend(void* Buf, int32 MsgLen);
		int32 IntRecv(void* Buf, int32 BufLen);
		int32 SlowSend(void* Buf, int32 MsgLen);
		int32 SlowSend(CpuFpgaCmmMsg* Msg);
	public:
		const SampIntMsgPool& SampIntSendMsg() { return sampIntSendMsg; };
		const SampIntMsgPool& SampIntRecvMsg() { return sampIntRecvMsg; };
		const SampIntMsgPool& SlowTaskSendMsg() { return slowTaskSendMsg; };
		const SampIntMsgPool& SlowTaskRecvMsg() { return slowTaskRecvMsg; };
	protected:
		void Send2Hal(SampIntMsgPool& Pool);
		void RecvFromHal(SampIntMsgPool& Pool);
	protected:
		SampIntMsgPool sampIntSendMsg;
		SampIntMsgPool sampIntRecvMsg;
		SampIntMsgPool slowTaskSendMsg;
		SampIntMsgPool slowTaskRecvMsg;
		SemaphoreB slowMsgWriteSem;
		struct TaskRunInfo msgDateTime;
		struct TaskRunInfo msgAnglog;
		struct TaskRunInfo msgGoPos;
		struct TaskRunInfo msgGoAng;
		struct TaskRunInfo msgDioMsg;
		struct TaskRunInfo msgSvState;
		struct TaskRunInfo msgGoState;
		struct TaskRunInfo msgBoardState;
		struct TaskRunInfo msgBoardCmm;
		struct TaskRunInfo msgBoardLig;
	};
	//国产化/新一代常规装置
	class GzkFpgaMsgGzk35KvProts :public FpgaMsgProc
	{
	public:
		virtual int32 PowerUpIni(int32 Para);
		GzkFpgaMsgGzk35KvProts();
		~GzkFpgaMsgGzk35KvProts();
	protected:

	};
	//国产化/智能备自投、多合一母联
	class GzkFpgaMsgGzk35KvSmart :public FpgaMsgProc
	{
	public:
		virtual int32 PowerUpIni(int32 Para);
		GzkFpgaMsgGzk35KvSmart();
		~GzkFpgaMsgGzk35KvSmart();
		virtual int32 RecvProc()override;
	protected:

	};
	//国产化采集执行单元
	class GzkFpgaMsgSau31 :public FpgaMsgProc
	{
	public:
		virtual int32 PowerUpIni(int32 Para);
		GzkFpgaMsgSau31();
		~GzkFpgaMsgSau31();
		virtual int32 RecvProc()override;
	protected:
		SampIntMsg msgPool[60];
		uint32 writer;
		SampIntMsg* dateTime;
		SampIntMsg* angSamp;
		SampIntMsg* goPos;
		SampIntMsg* goAng;
	};

	class GzkFpgaUpdate
	{
	public:
		enum Step
		{
			E_UpdateStart,
			E_UpdateStart_Send,
			E_UpdateStart_Wait,
			E_UpdateBitStreamClose,
			E_UpdateBitStreamClose_Send,
			E_UpdateBitStreamClose_Wait,
			E_UpdateErase,
			E_UpdateErase_Send,
			E_UpdateErase_Wait,
			E_UpdateProgram_Start,
			E_UpdateProgram,
			E_UpdateProgram_Send,
			E_UpdateProgram_Wait,
			E_UpdateProgramCheck,
			E_UpdateProgramCheck_Send,
			E_UpdateProgramCheck_Wait,
			E_UpdateBitStreamOpen,
			E_UpdateBitStreamOpen_Send,
			E_UpdateBitStreamOpen_Wait,
			E_UpdateEnd,
			E_UpdateErr,
			E_UpdateSumErr,
			E_UpdateTimeOver,
			E_CLEAR,
		};
	public:
		static void FpgaUpdateMsgRecv(void* Buf, int32 MsgLen);
		GzkFpgaUpdate(const char* FileName, uint32 FpgaFileSize, uint16 FpgaAddr, uint16 FrameLen, uint16 MaxRepeat);
		~GzkFpgaUpdate();
		int32 Run(int32(*Process)(int32 Step, const char* info));
	protected:
		void UpdateMsgRecv(void* Buf, int32 MsgLen);
		void SendCmd(uint16 cmd, uint8 NextStep);
		void GoOneStep(uint16 cmd, uint16 WaitCmd, uint8 StepNow, uint8 WaitStep, uint8 NextStep, uint16 WaitTime);
		void SendProg(uint8* data, uint16 FrameLen, uint16 Total, uint16 FrameNum, uint16 WaitTime);
	protected:
		uint8 updateStep;
		uint8 stepPathWriter;
		uint8 stepPath[20];
		String100B fileName;
		uint32 fileSum;
		uint32 checkSum;
		uint32 bufSize;
		uint32 fileSize;
		uint32 programSize;
		uint16 frameTotal;
		uint16 frameNum;
		uint8* fpgaFileBuf;
		uint16 fpgaAddr;
		uint16 frameLen;
		FpgaMsgProc* msgProc;
		static GzkFpgaUpdate* handle;
		static bool8 enable;
		uint16 maxRepeat;
		uint16 repeatCnt;
		MsStampTimer sendDelay;
		CpuFpgaCmmMsg recMsg;
		bool8 recOk;
	};
}
#endif // !SALFPGAMSGPROC_H

