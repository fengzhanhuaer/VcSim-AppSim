#ifndef SPTAPPTASK_H
#define SPTAPPTASK_H


namespace spt
{
	typedef void(*AppTaskCallBack)();

	class SampAppTask
	{
	public:
		struct RunTime
		{
			uint32 schdCnt;//运行计数
		};
	public:
		void ClearLoadInfo();
		void Do();
		struct TaskRunInfo& RunInfo() { return runInfo; };
	protected:
		AppTaskCallBack callBack;
		char name[40];
		uint32 period;//调用周期
		bool8 enable;
		RunTime runTime;
		struct TaskRunInfo runInfo;
	};
	/// <summary>
	/// 应用任务调度
	/// </summary>
	class SptSampAppTaskScheduler :public Task
	{
	public:
		int32 PostSem();
		/// <summary>
		/// 上电后应用调度tick
		/// </summary>
		/// <returns></returns>
		uint64 PowerUpSampIntCnt();
		/// <summary>
		/// 上电后采样中断微秒时间戳
		/// </summary>
		/// <returns></returns>
		uint64 PowerUpSampStamp();
		/// <summary>
		/// 应用中断调度tick计数
		/// </summary>
		/// <returns></returns>
		uint32 SampIntRunCnt();
		/// <summary>
		/// APP的Ms计数器
		/// </summary>
		/// <returns></returns>
		uint32 SampMs();
		virtual int32 PowerUpIni(int32 Para);
		int32 OneSampIntLoop();
		virtual int32 OneLoop();
		virtual int32 DoOnce();
		void ClearAppLoad();
	public:
		M_Singleton(SptSampAppTaskScheduler);
	protected:
		SptSampAppTaskScheduler();
		void AppScheduler();
	private:
		SemaphoreC RunSem;
		volatile uint64 powerUpSampIntCnt;
		volatile uint64 powerUpSampStamp;
		volatile uint32 sampIntCnt;
		uint32 sampMs;
		struct TaskRunInfo msgRunInfo;
		struct TaskRunInfo dateRunInfo;
		struct TaskRunInfo IoInRunInfo;
		struct TaskRunInfo appRunInfo;
		struct TaskRunInfo IoOutRunInfo;
	};

}


#endif // !SPTAPPTASK_H

