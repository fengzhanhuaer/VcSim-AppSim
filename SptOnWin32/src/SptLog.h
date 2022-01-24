#ifndef SPTLOG_H
#define SPTLOG_H

namespace spt
{
	class SptLog :InstObject
	{
		//public service interface
	public:
		SptLog& PrintLine(const char* Msg);//打印一行信息，（自动回车）
		SptLog& Stamp();//打印当前时间戳
		SptLog& Print(const char* Msg);//打印一条信息
		SptLog& EndLine();//输出换行符
		SptLog& NotEqual(const char* Name, int32 Data1, int32 Data2);
		SptLog& operator<<(const char* Msg);//打印一条信息
		SptLog& operator<<(int32 Msg);//打印一条信息
		SptLog& operator<<(uint32 Msg);//打印一条信息
		SptLog& operator<<(SalString& Msg);//打印一条信息
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
		/// 设置存储阻塞参数
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
	extern SptLog LogReal;//实时信息
	extern SptLog LogMsg;//一般信息
	extern SptLog LogWarn;//告警信息
	extern SptLog LogErr;//错误信息
	extern SptLog LogTest;//调试信息，调试专用
	extern SptLog LogApp;//应用信息，应用专用
	extern SptLog LogLoad;//负载信息，平台专用
	extern SptLog LogAct;//动作信息，平台专用
}




#endif//SPTLOG_H
