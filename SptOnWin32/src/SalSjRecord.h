#ifndef SALSJRECORD_H
#define SALSJRECORD_H

namespace spt
{
	struct SalSjRecordData
	{
		char stamp[40];//ʱ�������
		char process[40];//�����¼������������
		char usr[40];//�¼����壬�û�ID��Զ��IP��
		char object[40];//���壬�˵�����ֵ��ѹ���
		char result[40];//������ɹ���ʧ�ܣ��ܾ���
		char exInfo1[40];//������Ϣ������ʧ��ԭ�򣬿���ľ�ֵ��
		char exInfo2[40];//������Ϣ������ʧ��ԭ�򣬿������ֵ��
		char exInfo3[40];//������Ϣ������ʧ��ԭ�򣬿������ֵ��
		uint32 sum;
		void SetStamp(SalDateStamp& stamp);
		void GetStamp(SalDateStamp& stamp);
		//��¼��ʱ��ʱ��
		void StampNow();
		void SetProcess(const char* Process);
		void SetUsr(const char* Usr);
		void SetObject(const char* Object);
		void SetResult(const char* Result);
		void SetExInfo(const char* exInfo1, const char* exInfo2, const char* exInfo3);
		void SetRecord(const char* Process, const char* Usr, const char* Object, const char* Result, const char* exInfo1, const char* exInfo2, const char* exInfo3);
		uint32 CalcSum();
		bool8 IsSumOk();
		bool8 IsRecordOk();
		uint32 AddSum();
	};
	struct SalSjRecordHdr
	{
		char fileName[40];
		char eventType[40];
		uint16 version;
		uint16 hdrSize;
		uint16 elementPoolSize;
		uint16 elementSize;
		uint16 usdNum;
		uint16 validNum;
		uint16 writer;
		uint16 reader;
		uint32 sum;
		uint32 CalcSum();
		bool8 IsSumOk();
		uint32 AddSum();
	};
	class SalSjRecordGroup :public InstObjectGroup
	{
	public:
		int32 PowerUpIni(const char* Name, const char* DesName, uint32 ElementNum, uint32 PoolSize);
		int32 LoadRecord();
		int32 DeleteAll();
		uint32 NewestRecordIndex();
		uint32 OldestRecordIndex();
		uint32 ValidNum();
		uint32 PoolSize();
		/// <summary>
		/// ��ȡ��BaseΪ��׼ָ��ĵ�Num����Ч�ļ�¼
		/// </summary>
		/// <param name="Base"></param>
		/// <param name="Num"></param>
		/// <param name="Record"></param>
		/// <returns>-1����ȡʧ�ܣ��ɹ����ؼ�¼��ָ��ֵ</returns>
		int32 GetNextValidEvent(uint32 Base, uint32 Num, struct SalSjRecordData& Record);
		int32 CreatEvent(SalSjRecordData& Record);
		int32 SaveAll();
		int32 SaveAppend();
		bool8 HasNew();
		const SalSjRecordHdr& Header();
		void ClearEvent();
	protected:
		int32 save2File(const char* exName);
		int32 bak2File();
		int32 loadFile();
	protected:
		SalSjRecordHdr hdr;
		SalSjRecordHdr savehdr;
		ArrayBuf buf;
		bool8 isUpdate;
	};

	class SalSjRecordDispachTask :public Task
	{
	public:
		M_Singleton(SalSjRecordDispachTask);
		virtual int32 PowerUpIni(int32 Para);
		virtual int32 OneLoop();
		int32 SaveEvent(SalSjRecordGroup* EventGroup);
	public:
		enum TaskStep
		{
			E_PowerUpIni,
			E_Work,
		};
		enum SaveStep
		{
			E_Wait,
			E_BeginSave,
			E_EndSave,
		};
		/// <summary>
		/// ���ô洢��������
		/// </summary>
		void SetSaveBlockPara(uint32 LowLimit = 80, uint32 HighLimit = 2000) { saveLowLimit = LowLimit; saveHighLimit = HighLimit; };
	protected:
		uint32 saveLowLimit;
		uint32 saveHighLimit;
	protected:
		SalSjRecordDispachTask();
	protected:
		SemaphoreB saveSem;
		int32 saveStep;
		int32 saveSemCnt;
	};

}

#endif// SALSJRECORD_H
