#ifndef SALFAULTRECORD_H
#define SALFAULTRECORD_H

namespace spt
{
	class SalFwWaveCfgCell :public InstObject
	{
	public:
		enum CfgType
		{
			E_Null,
			E_Digital,
			E_Analog,
			E_Event,
			E_FaultInfo,
		};
		union uFlags
		{
			uint32 u32;
			struct stFlag
			{
				uint32 isDatAngCfg : 1;//故障录波模拟量
				uint32 isDatDigCfg : 1;//故障录波数字量
				uint32 isEvent : 1;//动作报告事项
				uint32 isHdrDig : 1;//故障报告HDR中状态量
				uint32 isHdrFaultInfo : 1;//故障报告HDR中故障数据
				uint32 isMidAng : 1;//中间节点文件mid中的模拟量
				uint32 isMidDig : 1;//中间节点文件mid中的状态量
			}st;
		};
	public:
		void PowerUpIni(const char* Name, const char* DesName, class SalFwRecordGroup* Group, uint32 CfgType, uint32 Flag);
		const st32value& Value() { return value; };
		uint8 Type() { return cfgType; }
		const uFlags& Flags() { return flags; }
		const SalString& Ccbm() { return ccbm; };
		int32 Phase() { return phase; };
		void SetDisp(bool8 Disp);
		bool8 IsDisp();
		uint16 AngId() { return angId; };
		uint16 DigId() { return digId; };
		uint16 EventId() { return eventId; };
		uint16 SetAngId(uint16 Id) { return angId = Id; };
		uint16 SetDigId(uint16 Id) { return digId = Id; };
		uint16 SetEventId(uint16 Id) { return eventId = Id; };
	protected:
		class SalFwRecordGroup* fwGroup;
		const uint32* groupSampWriter;
		const uint32* groupSampBufLen;
		uint16 angId;
		uint16 digId;
		uint16 eventId;
		uFlags flags;
		uint8 cfgType;
		st32value value;
		String65B ccbm;
		int32 phase;
		bool8 isDisp;
	};
	class SalFaultInfo :public SalFwWaveCfgCell
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, class SalFwRecordGroup* Group, const VarUnits& Units);
		bool8 IsAct() { return isAct; };
		void  Update(uint8 Act, int32 Value);
	protected:
		bool8 isAct;
		const VarUnits* units;
		st32value actValue;
	};
	class SalFwDigitalCfgSignal :public SalFwWaveCfgCell
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, class SalFwRecordGroup* Group, E_Ang_Phase Phase, const char* Ccbm, bool8 SteadyState, uint32 Flag, uint16 upBeforeSetCnt, uint16 UpAfterSetCnt, uint16 DownBeforeSetCnt, uint16 DownAfterSetCnt, bool8 IsDisp);
		void SetValue(uint32 Value);
		void Update2Buf();
		uint16 UpBeforeSetCnt() { return upBeforeSetCnt; };
		uint16 UpAfterSetCnt() { return upAfterSetCnt; };
		uint16 DownBeforeSetCnt() { return downBeforeSetCnt; };
		uint16 DownAfterSetCnt() { return downAfterSetCnt; };
		bool8 SteadyState() { return steadyState; };
	protected:
		uint16 upBeforeSetCnt;
		uint16 upAfterSetCnt;
		uint16 downBeforeSetCnt;
		uint16 downAfterSetCnt;
		bool8 steadyState;
		bool8 isChange;
		bool8* sampBuf;
	};
	class SalFwAnalogCfgSignal :public SalFwWaveCfgCell
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, class SalFwRecordGroup* Group, E_Ang_Phase Phase, const char* Ccbm, const VarUnits& Units, float32 Skew, float32 CoeA, float32 CoeB, float32 Primary, float32 Secondary, bool8 IsPrimary, uint32 Flag, bool8 IsDisp);
		void SetCoePS(float32 Primary, float32 Secondary);
		void SetCoeAB(float32 CoeA, float32 CoeB);
		void SetValue(float32 Value);
		void Update2Buf();
		const VarUnits* Units() { return units; };
		float32 Skew() { return skew; };
		float32 Primary() { return primary; };
		float32 CoeA() { return coeA; };
		float32 CoeB() { return coeB; };
		float32 Secondary() { return secondary; };
		bool8 IsPrimary() { return isPrimary; };
	protected:
		const VarUnits* units;
		float32 skew;
		float32 coeA;
		float32 coeB;
		float32 primary;
		float32 secondary;
		bool8 isPrimary;
		u32value* sampBuf;
	};
	class SalFwEventCfgSignal :public SalFwDigitalCfgSignal
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, SalEvent* Event, class SalFwRecordGroup* Group, E_Ang_Phase Phase, const char* Ccbm, bool8 SteadyState, uint32 Flag, uint16 UpBeforeSetCnt, uint16 UpAfterSetCnt, uint16 DownBeforeSetCnt, uint16 DownAfterSetCnt, bool8 IsDisp);
		void SetValue(uint32 Value);
		bool8 UpdateFromEvent();
		const SalEvent& Event() { return *pEvent; };
	protected:
		SalEvent* pEvent;
	};
	class SalFwDigitalCfgArray :public SingleStackBuf
	{
	public:
		class SalFwDigitalCfgSignal* GetCfg(uint32 No);
		int32 RgsCfgCell(class SalFwDigitalCfgSignal* Cfg);
		int32 InstNum();
	};
	class SalFwAnalogCfgArray :public SingleStackBuf
	{
	public:
		class SalFwAnalogCfgSignal* GetCfg(uint32 No);
		int32 RgsCfgCell(class SalFwAnalogCfgSignal* Cfg);
		int32 InstNum();
	};
	class SalFwActCfgArray :public SingleStackBuf
	{
	public:
		class SalFwEventCfgSignal* GetCfg(uint32 No);
		int32 RgsCfgCell(class SalFwProtEventCfgSignal* Cfg);
		int32 InstNum();
	};
	class SalFwFaultInfoCfgArray :public SingleStackBuf
	{
	public:
		class SalFaultInfo* GetCfg(uint32 No);
		int32 RgsCfgCell(class SalFaultInfo* Cfg);
		int32 InstNum();
	};

	class SalFwRecordCfg
	{
	public:
		void PowerUpIni(uint16 FwAngMaxNum, uint16 FwDigMaxNum, uint16 FwProtMaxNum, uint16 HdrFaultInfoMaxNum, uint16 HdrDigMaxNum, uint16 MidAngMaxNum, uint16 MidDigMaxNum);
		int32 RgsCfgCell(SalFwWaveCfgCell* Cfg);
		SalFwAnalogCfgArray& AngCfg() { return angCfg; };
		SalFwDigitalCfgArray& DigCfg() { return digCfg; };
		SalFwAnalogCfgArray& AngDatCfg() { return angDatCfg; };
		SalFwDigitalCfgArray& DigDatCfg() { return digDatCfg; };
		SalFwActCfgArray& ActEvent() { return actCfg; }
		SalFwFaultInfoCfgArray& FaultInfoHdrCfg() { return faultInfoHdrCfg; }
		SalFwDigitalCfgArray& DigHdrCfg() { return digHdrCfg; }
		SalFwAnalogCfgArray& AngMidCfg() { return angMidCfg; }
		SalFwDigitalCfgArray& DigMidCfg() { return digMidCfg; }
		int32 SetParaGroup(int32 Index, SalParaGroup* Group);
		SalParaGroup* GetParaGroup(int32 Index);
	protected:
		SalParaGroup* paraGroup[4];
		SalFwDigitalCfgArray digCfg;
		SalFwAnalogCfgArray angCfg;
		SalFwDigitalCfgArray digDatCfg;
		SalFwAnalogCfgArray angDatCfg;
		SalFwActCfgArray actCfg;
		SalFwDigitalCfgArray digHdrCfg;
		SalFwFaultInfoCfgArray faultInfoHdrCfg;
		SalFwAnalogCfgArray angMidCfg;
		SalFwDigitalCfgArray digMidCfg;
	};
	struct SalFwSampData1PointHeader
	{
	public:

	public:
		uint32 SampSerNo;//采样值序号
		uint16 RecContinueCnt;//连续采样个数
		uint16 res1;
		uint32 res2;
		SalDateStamp SampUtc;//UTC时间
		uint64 SampStamp;//采样时刻
	};
	struct SalFwSampData1Point :public SalFwSampData1PointHeader
	{
	public:
		u32value Data[1];
	};
	struct SalFileChannelDataCfg
	{
		uint32 Cn;
		uint8 ChanType;
		SalFwWaveCfgCell::uFlags Flag;
		char Name[40];
		char Phase[12];
		char Ccbm[40];
		char Unit[12];
		u32value CoeA;
		u32value CoeB;
		u32value Skew;
		u32value Min;
		u32value Max;
		u32value Primary;
		u32value Secondary;
		u32value Bin16Primary;
		u32value Bin16Secondary;
		bool8 IsPrimary;
		bool8 Y;
		bool8 IsDisp;
	};
	struct FwEventData
	{
		uint16 EverntSerNo;
		uint32 ActTimeMs;
		StatusData EventData;
		bool8 ToStr(SalString& Str)const;
		bool8 SerNoToStr(SalString& Str)const;
		bool8 ActTimeToStr(SalString& Str)const;
		bool8 UtcTimeToStr(SalString& Str)const;
		bool8 ActStr(SalString& Str)const;
		bool8 ExternInfoStr(SalString& Str, uint32 LineW)const;
		bool8 QStr(SalString& Str, uint16 LineW)const;
		const char* BoardName()const;
	};
	struct SalFwData
	{
	public:
		enum DatFileType
		{
			EFT_ASCII,
			EFT_BIN16,
			EFT_BIN32,
			EFT_FLOAT32,
		};
		enum DataType
		{
			EDT_Null,
			EDT_Event = 0x01,
			EDT_Dat = 0x02,
		};
		enum RecState
		{
			E_Null,
			E_StartRec = 0x01,
			E_EndRec = 0x02,
		};
		enum ActState
		{
			E_Start,//启动
			E_Act = 0x01,//动作
		};
		enum SaveState
		{
			E_Null2,
			E_StartSave = 0x01,
			E_CheckEnd = 0x02,
			E_EndAddCnt = 0x04,
			E_EndSave = 0x08,
			E_PriFileSaved = 0x10,
			E_AllFileSaved = 0x20,
		};
	public:
		//常量
		uint32 MaxEventNum;//事项最大个数
		uint32 MaxSampPoint;//采样缓冲区点数（单位为sizeof(SalFwSampData1Point)）
		uint32 CellPerSamp;//采样缓冲区元素个数（单位为sizeof(u32value)）
		uint32 DigCellPerSamp;//采样缓冲区元素个数（单位为个）
		uint32 AngCellPerSamp;//采样缓冲区元素个数（单位为个）
		uint32 LenPerSamp;//采样缓冲区单点长度含头（单位为byte）
		uint16 SysFreq;//系统频率
		uint16 SampPerCircle;//采样频率
		uint8 DatFileType;
		//变量
		char filePriName[40];
		char fileName[128];
		uint16 AngCfgNum;
		uint16 DigCfgNum;
		uint32 ActStartTimeMs;
		uint32 SampWriter;//数据区写指针
		uint32 SaveRtReader;
		uint32 SaveRtCheckReader;
		uint16 ContinueSamp;
		uint16 CircleSampCnt;
		uint8 CircleLimitIndex;
		uint32 RecordStartWriter;//开始录波时的写指针
		uint32 RecordEndWriter;//结束录波时的写指针
		uint32 RecordContinueCnt;
		uint32 CheckContinueCnt;
		uint8 BufSerNo;//缓冲区序号
		uint8 RecordSerNo;//录波序号
		uint8 RecordState;//录波状态
		uint8 SaveState;//存储状态
		uint8 ActType;//动作状态
		uint16 EventWriter;//事项写指针
		SalDateStamp TrigT;//采样时刻(开始录波时刻)
		SalDateStamp FirstSampT;//采样时刻(开始录波时刻)
		uint64 RecSampStampDif;//采样时长(最后一个采样点的时刻)
		uint16 timeMult;
		struct FwEventData* Event;
		SalFileChannelDataCfg* DataCfg;
		void* DataBuf;
	public:
		int32 Malloc();
		void StatusClear();
		SalFwSampData1Point* PointAt(uint32 Index);
		/// <summary>
		/// 转换为LCD显示的字符串
		/// </summary>
		/// <param name="Str"></param>
		/// <param name="DispExInfo">是否显示附属信息</param>
		/// <param name="UnDispReturn">不显示返回值</param>
		/// <param name="LineW">屏宽度</param>
		/// <returns></returns>
		bool8 ToLcdStr(SalString& Str, bool8 DispExInfo, bool8 UnDispReturn, uint32 LineW)const;
	public:
		int32 Save2PriFile(const char* FileName, SalFwRecordCfg* FwCfg);
		int32 Save2PubFile(const char* FileName, SalFwRecordCfg* FwCfg);
		int32 LoadPriFile(const char* FileName);
		int32 SeekPriSet(SalFile& File);
		int32 GetNextPriSet(SalFile& File, SalString& Str);
		int32 DeleteAllFile();
	private:
		int32 SavePriPub(SalFile& File);
		int32 SavePriEvent(SalFile& File);
		int32 SavePriCfg(SalFile& File);
		int32 SavePriSet(SalFile& File, SalFwRecordCfg* FwCfg);
		int32 SavePriEventBin(SalFile& File);
		int32 SavePriDatBin(SalFile& File);
		int32 LoadPriPub(SalFile& File);
		int32 LoadPriCfg(SalFile& File);
		int32 LoadPriEventBin(SalFile& File);
		int32 LoadPriDatBin(SalFile& File);
		int32 SavePubCfg1999File(const char* FileName);
		int32 SavePubDatAssic1999File(const char* FileName);
		int32 SavePubHdrFile(const char* FileName, SalFwRecordCfg* FwCfg);
		int32 SavePubMidFile(const char* FileName);
		int32 SavePubDesFile(const char* FileName);
		int32 PrepareSaveData(SalFwRecordCfg* FwCfg);
	};
	struct SalFwRtData
	{
	public:
		//常量
		uint32 MaxSampPoint;//采样缓冲区点数（单位为sizeof(SalFwSampData1Point)）
		uint32 AngCellNum;//采样缓冲区个数（单位为sizeof(SalFwSampData)）
		uint32 DigCellNum;//采样缓冲区个数（单位为sizeof(SalFwSampData)）
		//变量
		uint32 SampSerNo;//采样值序号
		uint32 SampWriter;
		SalDateStamp SampUtc;//UTC时间
		uint64 SampStamp;//采样时刻
		SalFwSampData1PointHeader* Header;
		u32value* U32SampBuf;
		bool8* DigSampBuf;
	public:
		bool8* GetDigBuf(uint32 DigIndex);
		bool8 GetDig(uint32 DigIndex, uint32 Reader);
		u32value* GetU32Buf(uint32 AngIndex);
		u32value GetU32(uint32 AngIndex, uint32 Reader);
	public:

	};
	class SalFwRecordGroup :public InstObjectGroup
	{
	public:
		static const uint32 MaxRecordFwRamData = 11;
		static const uint32 MaxEventRamData = 50;
		static const uint32 MaxRecordSerNo = 100;
		union uFlags
		{
			struct stFlag
			{
				uint32 is2t860 : 1;//通过61850上送
				uint32 isPrivate : 1;//私有录波，不转为标准Comtrade，不对外展示
			}st;
			uint32 u32;
		};
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint32 SysFreq, uint32 SampPerCircle, int32 MaxRecordPoint, uint16 UpBeforeSetCnt, uint16 UpAfterSetCnt, uint16 FwAngMaxNum, uint16 FwDigMaxNum, uint16 FwProtMaxNum, uint16 HdrFaultInfoMaxNum, uint16 HdrDigMaxNum, uint16 MidAngMaxNum, uint16 MidDigMaxNum, uint32 Flag);
		int32 RgsCfgCell(SalFwWaveCfgCell* Cfg);
		uint8 FwSerialNo();//录波完成的序号
		uint8 FwSerialWriter();//录波写指针
		SalFwData* MallocDataBuf();
		const SalFwData* GetHmiViewDataByNo(uint32 SerialNo);
		const SalFwData* GetCmmViewDataByNo(uint32 SerialNo);
		const SalFwData* GetPrinterViewDataByNo(uint32 SerialNo);
		const SalFwData* GetHmiViewDataByIndex(uint32 Index);
		const SalFwData* GetCmmViewDataByIndex(uint32 Index);
		const SalFwData* GetPrinterViewDataByIndex(uint32 Index);
		const uFlags& Flag() { return flags; }
		uint16 UpBeforeSetCnt() { return upBeforeSetCnt; };
		uint16 UpAfterSetCnt() { return upAfterSetCnt; };
	public:
		void Save2File();
		SalFwRtData& RtData() { return rtData; };
		uint32 SysFreq() { return sysFreq; };
		uint32 SampPerCircle() { return sampPerCircle; };
	protected:
		void RecordOnePoint(SalDateStamp& stamp, uint64 SampStamp);
		void SetActType(uint32 Type);
		int32 LoadHdrData();
		int32 SaveHdrData();
		int32 LoadFwData();
		void SavePrivateFile(SalFwData* Data);
		void SavePubFile(SalFwData* Data);
		void StartRecord(bool8 isStart);
		SalFwData* FwData(uint16 Index);
		int32 StartSaveData(SalFwData* DstData);
		int32 CheckAndSave(SalFwData* DstData);
		void SetContinueSaveCnt(uint32 Now, uint32 Before, uint32 After);
		int32 SetParaGroup(int32 Index, SalParaGroup* Group);
		bool8 Copy(SalFwData* Dst, SalFwData* Sur);
		void ClearRecord();
	protected:
		struct stNeedSave
		{
			uint32 version;
			uint8 recordOverSerNo;//录波完成序号
			uint8 fwWriter;
			uint8 fwReader;
		};
	protected:
		uFlags flags;
		bool8 allocErr;
		bool8 isStartRecord;
		bool8 isStartRecordLast;
		uint16 upBeforeSetCnt;
		uint16 upAfterSetCnt;
		uint32 sysFreq;
		uint32 sampPerCircle;
		uint32 maxRecSampPoint;
		SalFwRecordCfg fwCfg;
		stNeedSave savedFlag;
		SalFwRtData rtData;
		SalFwData* rtIntFwData;
		SalFwData* fwData[MaxRecordFwRamData];
		SalFwData* hmiViewData;
		SalFwData* cmmViewData;
		SalFwData* printViewData;
	};
	class SalFwRecordTask :public Task
	{
	public:
		M_Singleton(SalFwRecordTask);
		virtual int32 PowerUpIni(int32 Para);
		virtual int32 OneLoop();
	protected:
		SalFwRecordTask();
	};
}

#endif // !SALFAULTRECORD_H

