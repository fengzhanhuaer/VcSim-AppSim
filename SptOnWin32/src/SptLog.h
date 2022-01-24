#ifndef SPTLOG_H
#define SPTLOG_H

namespace spt
{
	class SptLog :InstObject
	{
		//public service interface
	public:
		SptLog& PrintLine(const char* Msg);//��ӡһ����Ϣ�����Զ��س���
		SptLog& Stamp();//��ӡ��ǰʱ���
		SptLog& Print(const char* Msg);//��ӡһ����Ϣ
		SptLog& EndLine();//������з�
		SptLog& NotEqual(const char* Name, int32 Data1, int32 Data2);
		SptLog& operator<<(const char* Msg);//��ӡһ����Ϣ
		SptLog& operator<<(int32 Msg);//��ӡһ����Ϣ
		SptLog& operator<<(uint32 Msg);//��ӡһ����Ϣ
		SptLog& operator<<(SalString& Msg);//��ӡһ����Ϣ
		SptLog& operator<<(SalDateStamp& Stamp);
		//platform function interface
	public:
		SptLog(const char* Name, uint32 BufSize, bool8 LocalPrint, bool8 FilePrint, bool8 NetPrint);
	protected:
		void Save2File();
		void Save2Net();
		void Save2Local();
		void ClearBuf();
		void Flush();
		int32 PowerUpIni(int32 Para, class SptLogCfg& File);
	private:
		bool8 isLogIng;
		CfgBool localPrint;
		CfgBool filePrint;
		CfgBool netPrint;
		int32 log(const char* Msg);
		uint32 fileMaxSize;
		SingleCharBuf saveBuf;
		friend class SptLogTask;
	};
	class SptLogCfg :public CfgFile
	{
	public:
		int32 PowerUpIni(int32 Para, const char* CfgFileName);
	protected:
		virtual PCfgDataBase* CfgPool() { return pool; };
		virtual uint32 CfgPoolSize() { return M_ArrLen(pool); };
	public:
		CfgBool localPrint;
		CfgBool filePrint;
		CfgBool netPrint;
	private:

		PCfgDataBase pool[50];
	};
	class SptLogTask :public InstObjectGroup, public Task
	{
	public:

	public:
		enum TaskStep
		{
			E_PowerUpIni = 0,
			E_Work,
			E_Check,
		};
	public:
		void LoadCfg();
		virtual int32 PowerUpIni(int32 Para);
		virtual int32 OneLoop();
		SptLogCfg& LogCfg();
		/// <summary>
		/// ���ô洢��������
		/// </summary>
		void SetSaveBlockPara(uint32 LowLimit = 100, uint32 HighLimit = 2000) { saveLowLimit = LowLimit; saveHighLimit = HighLimit; };
	protected:
		uint32 saveLowLimit;
		uint32 saveHighLimit;
	public:
		M_Singleton(SptLogTask);
	protected:
		SptLogTask();
		MsPeriodTimer logTimer;
		SptLogCfg logCfg;
	};
	extern SptLog LogReal;//ʵʱ��Ϣ
	extern SptLog LogMsg;//һ����Ϣ
	extern SptLog LogWarn;//�澯��Ϣ
	extern SptLog LogErr;//������Ϣ
	extern SptLog LogTest;//������Ϣ������ר��
	extern SptLog LogApp;//Ӧ����Ϣ��Ӧ��ר��
	extern SptLog LogLoad;//������Ϣ��ƽ̨ר��
	extern SptLog LogAct;//������Ϣ��ƽ̨ר��
}




#endif//SPTLOG_H
