#ifndef SALPARA_H
#define SALPARA_H

namespace spt
{
	struct ParaGroupDataHeader
	{
		uint8 version;
		uint8 status;
		uint8 zoneIndex;
		uint8 headerSize;
		uint8 elementSize;
		uint8 dataChanCnt;
		uint16 elementNum;
		uint16 res2[2];
	};
	struct ParaGroupData
	{
		ParaGroupDataHeader header;
		int32* data;
		uint32 AddCrc();
		bool8 IsCrcOk()const;
		uint32 CalCrc()const;
		uint32 GetCrc()const;
		uint32 SizeOfDataWithCrc()const;
		uint32 SizeOfData()const;//不含CRC
		int32 PowerUpIni(uint32 ElementNum, uint32 Zone);
		void* AddrOf(uint32 No);
	};
	class ParaGroupDataAll :protected ArrayBuf
	{
	public:
		void SetElement(uint32 ZoneNum, uint32 ElementNum);
		ParaGroupData* Group(uint32 Zone);
	};

	const uint32 CN_MaxParaZone = 30;
	class SalParaGroup :public InstObjectGroup
	{
	public:
		enum E_SaveStep
		{
			E_SaveNull,
			E_SaveStart,
			E_SaveOver,
		};
		enum E_ParaStatus
		{
			E_NonIni,//未初始化
			E_OK,//正常
			E_HeaderNotMatch,//头文件不匹配
			E_DataNotExist,//数据文件不存在
			E_DataCrcIsErr,//数据文件CRC异常
			E_DataOverRange,//数据越限
		};
		enum E_SaveType
		{
			E_LoadAll,//加载所有缓冲区
			E_LoadZone,//加载单个缓冲区
			E_SaveDataAll,//存储全部
			E_SaveSingleZone,//存储单个区
			E_ChangeZone,//切区
		};
	public:
		uint32 GetCrc(uint8 Zone);
		bool8 UpdateForUse();
		int32 PowerUpIni(const char* Name, const char* DesName, uint16 CurZone, uint16 MaxZone, uint16 ElementNum);
		int32 DefaultData();
		int32 CheckStatus();//1 is ok,others is error.
		int32 ElementSize();
		ParaGroupDataAll& DataGroup();
		//整区存储参数，BufLen必须大于等于本存储区大小
		int32 SavePara(void* Buf, int32 BufLen, int32 Zone);
		int32 ChangeZone(int32 Zone);
		int32 LoadPara(int32 Para, int32 ZoneNum);
		uint16 DataChanCnt();
		const int32* UsingData(uint32 Zone);//应用区缓冲区首地址
		uint16 UsingZone();//当前定值区
		uint32 MaxZone();
		class SalPara* GetDes(uint32 No);
		uint32 GetDataOffSet(uint32 dwsize);//dwsize salpara占用的dword数目
		uint32 DataOffSet() { return dataOffSet; };
		int32 CheckEditZoneRange(int32* AddrBase);//定值越限检查
		const struct stAppFlags* AppFlags()const;
	protected:
		int32 SavePara(SalParaGroup* Group, int32 Type, int32 ZoneNum);
		int32 loadBakParaForUse(int32 ZoneNum);
		int32 getSaveStepFlag(uint32 Zone);
	protected:
		uint16 dataElementNum;
		uint16 curZone;
		uint16 maxZone;
		E_ParaStatus status;
		ParaGroupDataAll usingData;
		ParaGroupDataAll editData;//数据编辑完成后，先存入该缓冲区后，由存储任务统一进行转存。
		uint16 dataChanCnt;
		uint32 dataOffSet;
		const struct stAppFlags* appFlags;
		friend class SalParaGroupSaveTask;
	};

	class SalPara :public InstObject
	{
	public:
		union Flags
		{
			struct stFlags
			{
				uint32 isReadOnly : 1;
				uint32 isRelatedOthoers : 1;//例如电流型定值
			}st;
			uint32 u32;
		};
		enum ParaType
		{
			E_PT_Int32,//普通Int32定值
			E_PT_UInt32,//普通Int32定值
			E_PT_Ct_Second,//CT二次值
			E_PT_Str,//字符型
			E_PT_Enum,//枚举型
			E_PT_HEX8,
			E_PT_HEX16,
			E_PT_HEX32,
			E_PT_BIT8,
			E_PT_BIT16,
			E_PT_BIT32,
			E_PT_UnitSet,//间隔投退型
			E_PT_Zone,//定值区号
		};
	public:
		void PowerUpIni(const char* Name, const char* DesName, class SalParaGroup* Group, int32 Min, int32 Def, int32 Max, uint8 DotNum, uint8 ValueType, const VarUnits& Units);
		void SetRange(int32 Max, int32 Min);
		uint8 ValueType();
		uint8 DotNum();
		uint8 UnitType();
		const char* Unit();
		int32 Max();
		int32 Min();
		int32 Default();
		bool8 Disp();
		bool8 SetDisp(bool8 Disp);
		bool8 ReadOnly();
		int32 DataOffSet();
		const st32value& UsingValue();
		const st32value& ExInfo1();//附加数据
		virtual void SaveIds(void* Ele);
		int32 Int32();//当前组定值数值，定点数
		int32 EnumVal();
		float32 Float32();//当前组定值数值，浮点数
		uint32 Uint32();//当前组定值数值，定点数
		bool8 UpdateForUse();
		bool8 Value2Str(SalString& Str);
		bool8 Value2Str(u32value Value, SalString& Str);
	public:

	protected:
		int32 dataOffSet;
		st32value usingValue;
		st32value editValue;
		uint8 valueType;
		uint8 dotNum;
		bool8 disp;
		const VarUnits* units;
		int32 max;
		int32 min;
		int32 def;
		st32value exInfo1;//附加数据
		Flags flags;
	};
	class SalParaEditCell
	{
	public:
		int32* Buf() { return buf; }
		int32 SetDes(SalPara* Des, int32* Buf);
		SalPara* Des() { return des; }
		bool8 SetValue(uint32 Val);
		bool8 SetValue(const char* Val);
	protected:
		SalPara* des;
		int32* buf;
	};
	/// <summary>
	/// 定值参数编辑类，提供一个修改定值的临时缓冲区
	/// 该类仅能在HMI/61850等线程中调用，禁止在应用中断中调用
	/// </summary>
	class SalParaEditGroup
	{
	public:
		void PowerUpIni(uint32 ElementNum);//上电分配内存空间
		uint32 EditCellNum();//缓冲区总个数
		uint32 CurEditCellNum();//当前可编辑参数个数
		SalParaEditCell* EditCell(uint32 No);
		int32 Set(SalParaGroup* Group, uint32 Zone);
		const SalParaGroup* Group();
		/// <summary>
		/// 用使用值更新操作缓冲区
		/// </summary>
		/// <returns></returns>
		int32 UpdateEditValue();
		/// <summary>
		/// 该函数仅能在HMI/61850等线程中调用，禁止在应用中断中调用
		/// </summary>
		/// <returns></returns>
		int32 SavePara();
	protected:
		SalParaEditCell* editCellBuf;
		ArrayBuf editBuf;
		SalParaGroup* group;
		uint32 zoneNum;
		uint32 curEditCellNum;
		uint32 elementNum;
	};

	class SalParaGroupSaveTask :public Task
	{
	public:
		enum TaskStep
		{
			E_PowerUpIni,
			E_WaitCmd,
		};
		enum SaveStep
		{
			E_Wait,
			E_BeginSave,
			E_EndSave,
		};
		M_Singleton(SalParaGroupSaveTask);
	public:
		virtual int32 PowerUpIni(int32 Para);
		virtual int32 OneLoop();
	public:
		int32 SavePara(SalParaGroup* Group, int32 Para, int32 ZoneNum);
		/// <summary>
		/// 设置存储阻塞参数
		/// </summary>
		void SetSaveBlockPara(uint32 LowLimit = 50, uint32 HighLimit = 2000) { saveLowLimit = LowLimit; saveHighLimit = HighLimit; };
	protected:
		SalParaGroupSaveTask();
	protected:
		uint32 saveLowLimit;
		uint32 saveHighLimit;
		SemaphoreB saveSem;
		SalParaGroup* group;
		int32 savePara;
		int32 saveStep;
		int32 saveZone;
		int32 saveRes;
	};



}

#endif // !SALPARA_H

