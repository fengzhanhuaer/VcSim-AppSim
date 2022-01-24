#ifndef SalEvent_h
#define SalEvent_h

namespace spt
{
	union  StatusQ
	{
		struct
		{
			uint32 test : 1;//����
			uint32 invalid : 2;//��Ч
			uint32 debug : 1;//����
			uint32 res1 : 12;//����
			uint32 isEvent : 1;//�Ƿ�������
			uint32 powerUpIni : 1;//�ϵ��ʼ���������һ��Update�Ľ��Ϊ0�����ֵΪ1�������ֵΪ0
			uint32 retrn : 1;//����
			uint32 isUnDisp : 1;//����ʾ
			uint32 isForce : 1;//ǿ��
			uint32 res2 : 3;
			uint32 tq : 8;//ʱ��Ʒ��
		}st;
		struct
		{
			uint8 appState;
			uint8 res;
			uint8 sptState;
			uint8 tq;
		}byte;
		uint32 u32;
	};
	const uint8 CN_StatusMaxExInfo = 9;
	struct StatusData
	{
		uint8 typeId;
		uint8 boardId;
		uint16 eventId;
		uint8 eventActTimes;
		uint8 eType;//SalStatus::EventType
		uint8 res1;
		uint8 res2;
		StatusQ q;
		u32value oldStatus;
		u32value status;
		u32value exInfo[CN_StatusMaxExInfo];
		uint64 stamp;
		uint16 res3;
		uint16 res4;
		uint16 res5;
		uint16 crc;
		bool8 toLcdStr(SalString& Str, uint16 LineW)const;
		bool8 UtcTimeToStr(SalString& Str, uint16 LineW)const;
		bool8 QStr(SalString& Str, uint16 LineW)const;
		bool8 ActStr(SalString& Str, uint16 LineW)const;
		bool8 ExternInfoStr(SalString& Str, uint16 LineW)const;
		bool8 ExternInfoStr(uint16 Index, SalString& NameStr, SalString& DataStr, SalString& UnitStr)const;
		uint8 ExternInfoNum()const;
		const char* BoardName()const;
		const char* Name()const;
		bool8 ValueStr(SalString& Str, uint16 LineW)const;
		bool8 OldValueStr(SalString& Str, uint16 LineW)const;
		bool8 ValueStr(u32value Status, SalString& Str, uint16 LineW)const;
		bool8 AddCrc();
		bool8 IsCrcOk()const;
		bool8 GetStamp(SalDateStamp& Stamp)const;
		const class SalStatus* StatusDes()const;
	};
	struct StatusExInfoDesItem
	{
		char name[20];
		uint8 valueType;//��������
		uint8 dataWidth;//���ݿ��
		uint8 dotNum;//С��λ��
		const VarUnits* units;
		const SalEnumDes* pEnum;
		uint8 EnumNum;
	};
	struct StatusExInfoDes
	{
		uint32 infoNum;
		StatusExInfoDesItem exInfoDes[CN_StatusMaxExInfo];
	};
	extern const SalEnumDes DpEnumDes[4];
	class SalStatus :public InstObject
	{
	public:
		union Flags
		{
			struct stFlags
			{
				uint32 isHoldOn : 1;//���籣��
				uint32 isManualRevert : 1;//�ֶ�����
				uint32 isDispUs : 1;//��ʾ΢��
				uint32 isUnDispRtn : 1;//����ʾ��������
				uint32 isUnDispValueChange : 1;//����ʾ��ֵ��λ
				uint32 isAutoRtn : 1;//�Զ����ء�ֻ�����1������Ҫ����0��������������Զ�������������ʾ��������
				uint32 isDispQ : 1;//��ʾƷ��
				uint32 isUnDispRrnExInfo : 1;//����ʾ��������ĸ���״̬��Ϣ
				uint32 isFirstInfoIsPhase : 1;//��һ��������Ϣ�����enum E_Ang_Phase
			}st;
			uint32 u32;
		};
		enum EventType
		{
			E_BOOL,//bool��
			E_DPOS,//˫������
			E_Hex8,//Hex8״̬��
			E_Hex16,//Hex16״̬��
		};
	public:
		void PowerUpIni(const char* Name, const char* DesName, class SalStatusGroup* Group, uint32 type, uint32 flag);
		void ExInfoPowerUpIni(StatusExInfoDesItem* Inf1, StatusExInfoDesItem* Inf2, StatusExInfoDesItem* Inf3, StatusExInfoDesItem* Inf4, StatusExInfoDesItem* Inf5, StatusExInfoDesItem* Inf6, StatusExInfoDesItem* Inf7, StatusExInfoDesItem* Inf8, StatusExInfoDesItem* Inf9);
		bool8 Update(uint32 Status, SalDateStamp* stamp, StatusQ* Q);
		bool8 ForceUpdate(uint32 Status, SalDateStamp* stamp, StatusQ* Q);
		bool8 Update(StatusData& Data);
		bool8 SetDisp(bool8 blDisp);
		bool8 IsDisp()const;
		uint8 ValueType();
		const u32value& Value()const;
		const u32value& OldValue()const;
		const Flags& Flag()const { return flags; };
		void UpdateStatus(u32value S1, u32value S2, u32value S3);
		void UpdateStatus(u32value S1, u32value S2, u32value S3, u32value S4, u32value S5, u32value S6);
		void UpdateStatus(u32value S1, u32value S2, u32value S3, u32value S4, u32value S5, u32value S6, u32value S7, u32value S8, u32value S9);
		bool8 UtcTimeToStr(const StatusData& Data, SalString& Str, uint16 LineW)const;
		bool8 ActStr(const StatusData& Data, SalString& Str, uint16 LineW)const;
		bool8 BoardStr(const StatusData& Data, SalString& Str, uint16 LineW)const;
		bool8 QStr(const StatusData& Data, SalString& Str, uint16 LineW)const;
		bool8 ExternInfoStr(const StatusData& Data, SalString& Str, uint16 LineW)const;
		bool8 ExternInfoStr(const StatusData& Data, uint16 Index, SalString& NameStr, SalString& DataStr, SalString& UnitStr)const;
		uint8 ExternInfoNum()const;
		bool8 toLcdStr(const StatusData& data, SalString& Str, uint16 LineW)const;
		const char* BoardName()const;
		bool8 blSignalForce() { return blsignalForce; };
		bool8 blSignalForce(bool8 Flag) { return blsignalForce = Flag; };
		const StatusData& Data()const { return data; };
	protected:
		bool8 blsignalForce;
		void afterSave();
		bool8 update(uint32 Status, SalDateStamp* stamp, StatusQ* Q);
		bool8 setValue(uint32 Status, SalDateStamp* stamp, StatusQ* Q);
		bool8 ifNeedUpdate(uint32 Status);
		StatusQ q;
		Flags flags;
		bool8 disp;
		bool8 blIni;
		StatusData data;
		StatusExInfoDes exInfoDes;
	};
	typedef SalStatus* PSalStatus;
	struct EventGroupDataHeader
	{
		uint16 eventVer;
		uint16 eventNum;
		uint16 eventSize;
		uint16 eventPoolSize;
		uint16 eventSaveWriter;
		uint16 eventSaveReader;
		uint16 eventSaveNum;
		uint16 eventValidNum;
		uint16 res[7];
		uint16 crc;
	};
	struct EventGroupDataPool
	{
		EventGroupDataHeader header;
		StatusData data[1];
		uint32 SizeOfEventPool() { return sizeof(header) + header.eventPoolSize * sizeof(StatusData); };
	};
	class SalStatusGroup :public InstObjectGroup
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint16 EventNum, SalEnumDes* BoardDes, uint8 BoardTypeNum, uint8 BoardIndex);
		const struct stAppFlags* AppFlags()const;
		int32 SaveStatus(uint16 eventId, StatusData& status);
		const StatusData* GetStatus(uint16 eventId);
		SalStatus* GetDes(uint16 eventId);
		virtual int32 SaveFile();
		virtual int32 SaveText();
		SalEnumDes* BoardDes() { return boardDes; };
		uint8 BoardTypeNum() { return boardTypeNum; };
		const char* BoardName(uint16 Index)const;
	protected:
		void allocBuf();
	protected:
		const struct stAppFlags* appFlags;
		struct EventGroupDataHeader stdheader;
		struct EventGroupDataPool* statusBuf;
		bool8 statusIsUpdate;
		SalEnumDes* boardDes;
		uint8 boardTypeNum;
		uint8 boardIndex;
	};
	class SalEvent :public SalStatus
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, class SalEventGroup* Group, uint32 type, uint32 flags);
		//����б�λ�����ָ����ʱ���������,ʹ��ָ����Ʒ��λ
		bool8 Update(uint32 Status, SalDateStamp* stamp, StatusQ* Q);
		bool8 SetValue(uint32 Status, SalDateStamp* stamp, StatusQ* Q);
		bool8 ForceUpdate(uint32 Status, SalDateStamp* stamp, StatusQ* Q);
		bool8 Update(StatusData& Data);
	protected:

	};
	typedef SalEvent* PSalEvent;
	class SalEventGroup :public SalStatusGroup
	{
	public:
		//Name��ʾ����
		//DesName�̵�ַ
		//EventNum�������
		//EventPoolSize�������(ѭ��������)��С
		//FlagsӦ�ñ�־��
		void PowerUpIni(const char* Name, const char* DesName, uint16 EventNum, uint32 EventPoolSize, const stAppFlags* Flags, SalEnumDes* BoardDes, uint8 BoardTypeNum, uint8 BoardIndex);
		int32 SaveEvent(uint16 eventId, StatusData& status);
		uint32 EventPoolSize();
		/// <summary>
		/// �������ݵ��±�
		/// </summary>
		/// <returns></returns>
		uint32 NewestEventIndex();
		/// <summary>
		/// ����������±�
		/// </summary>
		/// <returns></returns>
		uint32 OldestEventIndex();
		uint32 ValidNum();
		/// <summary>
		/// ��ȡ��BaseΪ��׼ָ��ĵ�Num����Ч�ļ�¼
		/// </summary>
		/// <param name="Base"></param>
		/// <param name="Num"></param>
		/// <param name="Record"></param>
		/// <param name="isForDisp">�Ƿ�������ʾ���������������ͨѶ����������ʾ</param> 
		/// <returns>-1����ȡʧ�ܣ��ɹ����ؼ�¼��ָ��ֵ</returns>
		int32 GetNextValidEvent(uint32 Base, uint32 Num, StatusData& Record, bool8 isForDisp);
		SalEvent* GetEventDes(uint32 InstId);
		virtual int32 SaveFile();
		int32 LoadFile();
		void ClearEvent();
	protected:
		void allocBuf();
		int32 save2File();
		int32 save2File(const char* FileName);
		int32 loadFile(const char* FileName);
		int32 bak2File(const char* FileName);
	protected:
		struct EventGroupDataPool* eventTempBuf;
		struct EventGroupDataPool* eventSaveBuf;
		uint8 eventIsUpdate;
	};

	class SptEventPublishTask :public Task
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
		M_Singleton(SptEventPublishTask);
	public:
		virtual int32 PowerUpIni(int32 Para);
		virtual int32 OneLoop();
	public:
		int32 SaveEvent(SalStatusGroup* EventGroup);
		int32 SaveEventText(uint32 LineWidth);
		/// <summary>
		/// ���ô洢��������
		/// </summary>
		void SetSaveBlockPara(uint32 LowLimit = 80, uint32 HighLimit = 2000) { saveLowLimit = LowLimit; saveHighLimit = HighLimit; };
	protected:
		uint32 saveLowLimit;
		uint32 saveHighLimit;
	protected:
		SptEventPublishTask();
		int32 SaveAllEvent();
	protected:
		SemaphoreB saveSem;
		int32 saveStep;
		int32 saveSemCnt;
	};
}

#endif // !SptEvent_h

