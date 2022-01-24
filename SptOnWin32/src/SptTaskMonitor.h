#ifndef SPTTASKMONITOR_H
#define SPTTASKMONITOR_H

namespace spt
{
	class TaskMonitor :public Task
	{
	public:
		enum TaskStep
		{
			E_PowerUpIni = 0,
			E_Work,
			E_Check,
		};
		//任务运行统计信息
		struct RunInfo
		{
			bool8 isInfoOk;
			uint32 taskNum;
			struct TaskInfo
			{
				const TaskRunInfo* taskRunInfo;
			}info[100];
		};
	public:
		M_Singleton(TaskMonitor);
	protected:
		TaskMonitor();
	public:
		virtual int32 PowerUpIni(int32 Para);
		virtual int32 OneLoop();
	public:
		int32 RgsRunInfo(TaskRunInfo* taskRunInfo);
		void ClearCalRunInfo();
		const RunInfo& TaskRunInfo();
	protected:
		void CheckLoad();
		void PrintLoad();
	private:
		bool8 cmdClearRunInfo;
		MsPeriodTimer HourTimer;
		MsPeriodTimer DayTimer;
		RunInfo taskRunInfo;
	};




}

#endif // !SPTTASKMONITOR_H

