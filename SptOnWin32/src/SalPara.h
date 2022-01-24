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
		uint32 SizeOfData()const;//����CRC
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
			E_NonIni,//δ��ʼ��
			E_OK,//����
			E_HeaderNotMatch,//ͷ�ļ���ƥ��
			E_DataNotExist,//�����ļ�������
			E_DataCrcIsErr,//�����ļ�CRC�쳣
			E_DataOverRange,//����Խ��
		};
		enum E_SaveType
		{
			E_LoadAll,//�������л�����
			E_LoadZone,//���ص���������
			E_SaveDataAll,//�洢ȫ��
			E_SaveSingleZone,//�洢������
			E_ChangeZone,//����
		};
	public:
		uint32 GetCrc(uint8 Zone);
		bool8 UpdateForUse();
		int32 PowerUpIni(const char* Name, const char* DesName, uint16 CurZone, uint16 MaxZone, uint16 ElementNum);
		int32 DefaultData();
		int32 CheckStatus();//1 is ok,others is error.
		int32 ElementSize();
		ParaGroupDataAll& DataGroup();
		//�����洢������BufLen������ڵ��ڱ��洢����С
		int32 SavePara(void* Buf, int32 BufLen, int32 Zone);
		int32 ChangeZone(int32 Zone);
		int32 LoadPara(int32 Para, int32 ZoneNum);
		uint16 DataChanCnt();
		const int32* UsingData(uint32 Zone);//Ӧ�����������׵�ַ
		uint16 UsingZone();//��ǰ��ֵ��
		uint32 MaxZone();
		class SalPara* GetDes(uint32 No);
		uint32 GetDataOffSet(uint32 dwsize);//dwsize salparaռ�õ�dword��Ŀ
		uint32 DataOffSet() { return dataOffSet; };
		int32 CheckEditZoneRange(int32* AddrBase);//��ֵԽ�޼��
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
		ParaGroupDataAll editData;//���ݱ༭��ɺ��ȴ���û��������ɴ洢����ͳһ����ת�档
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
				uint32 isRelatedOthoers : 1;//��������Ͷ�ֵ
			}st;
			uint32 u32;
		};
		enum ParaType
		{
			E_PT_Int32,//��ͨInt32��ֵ
			E_PT_UInt32,//��ͨInt32��ֵ
			E_PT_Ct_Second,//CT����ֵ
			E_PT_Str,//�ַ���
			E_PT_Enum,//ö����
			E_PT_HEX8,
			E_PT_HEX16,
			E_PT_HEX32,
			E_PT_BIT8,
			E_PT_BIT16,
			E_PT_BIT32,
			E_PT_UnitSet,//���Ͷ����
			E_PT_Zone,//��ֵ����
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
		const st32value& ExInfo1();//��������
		virtual void SaveIds(void* Ele);
		int32 Int32();//��ǰ�鶨ֵ��ֵ��������
		int32 EnumVal();
		float32 Float32();//��ǰ�鶨ֵ��ֵ��������
		uint32 Uint32();//��ǰ�鶨ֵ��ֵ��������
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
		st32value exInfo1;//��������
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
	/// ��ֵ�����༭�࣬�ṩһ���޸Ķ�ֵ����ʱ������
	/// ���������HMI/61850���߳��е��ã���ֹ��Ӧ���ж��е���
	/// </summary>
	class SalParaEditGroup
	{
	public:
		void PowerUpIni(uint32 ElementNum);//�ϵ�����ڴ�ռ�
		uint32 EditCellNum();//�������ܸ���
		uint32 CurEditCellNum();//��ǰ�ɱ༭��������
		SalParaEditCell* EditCell(uint32 No);
		int32 Set(SalParaGroup* Group, uint32 Zone);
		const SalParaGroup* Group();
		/// <summary>
		/// ��ʹ��ֵ���²���������
		/// </summary>
		/// <returns></returns>
		int32 UpdateEditValue();
		/// <summary>
		/// �ú���������HMI/61850���߳��е��ã���ֹ��Ӧ���ж��е���
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
		/// ���ô洢��������
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

