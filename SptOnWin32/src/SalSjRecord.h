#ifndef SALSJRECORD_H
#define SALSJRECORD_H

namespace spt
{
	struct SalSjRecordData
	{
		char stamp[40];//时间戳明文
		char process[40];//发生事件的组件、进程
		char usr[40];//事件主体，用户ID，远程IP等
		char object[40];//客体，菜单、定值、压板等
		char result[40];//结果，成功、失败，拒绝等
		char exInfo1[40];//附加信息，例如失败原因，客体的旧值等
		char exInfo2[40];//附件信息，例如失败原因，客体的新值等
		char exInfo3[40];//附件信息，例如失败原因，客体的新值等
		uint32 sum;
		void SetStamp(SalDateStamp& stamp);
		void GetStamp(SalDateStamp& stamp);
		//记录此时的时标
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
		/// 获取以Base为基准指针的第Num个有效的记录
		/// </summary>
		/// <param name="Base"></param>
		/// <param name="Num"></param>
		/// <param name="Record"></param>
		/// <returns>-1，获取失败，成功返回记录的指针值</returns>
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
		/// 设置存储阻塞参数
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
