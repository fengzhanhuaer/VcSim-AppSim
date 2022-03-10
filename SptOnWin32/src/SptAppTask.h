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
			uint32 schdCnt;//���м���
		};
	public:
		void ClearLoadInfo();
		void Do();
		struct TaskRunInfo& RunInfo() { return runInfo; };
	protected:
		AppTaskCallBack callBack;
		char name[40];
		uint32 period;//��������
		bool8 enable;
		RunTime runTime;
		struct TaskRunInfo runInfo;
	};
	/// <summary>
	/// Ӧ���������
	/// </summary>
	class SptSampAppTaskScheduler :public Task
	{
	public:
		int32 PostSem();
		/// <summary>
		/// �ϵ��Ӧ�õ���tick
		/// </summary>
		/// <returns></returns>
		uint64 PowerUpSampIntCnt();
		/// <summary>
		/// �ϵ������ж�΢��ʱ���
		/// </summary>
		/// <returns></returns>
		uint64 PowerUpSampStamp();
		/// <summary>
		/// Ӧ���жϵ���tick����
		/// </summary>
		/// <returns></returns>
		uint32 SampIntRunCnt();
		/// <summary>
		/// APP��Ms������
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

