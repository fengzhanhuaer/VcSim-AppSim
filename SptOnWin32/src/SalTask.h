#include "SalTypes.h"
#ifndef SALTASK_H
#define SALTASK_H

namespace spt
{
	struct TaskRunInfo
	{
	public:
		uint32 status;//Task::Status
		uint32 realTimeLoad;//实时负载
		uint32 realTimePeriod;//实时周期
		uint32 maxHourLoad;//小时负载情况
		uint32 maxDayLoad;//天负载情况
		uint32 maxAllLoad;//负载情况
		uint32 minHourLoad;//小时负载情况
		uint32 minDayLoad;//天负载情况
		uint32 minAllLoad;//负载情况
		uint32 maxHourPeriod;//小时周期情况
		uint32 maxDayPeriod;//天周期情况
		uint32 maxAllPeriod;//周期情况
		uint32 minHourPeriod;//小时周期情况
		uint32 minDayPeriod;//天周期情况
		uint32 minAllPeriod;//周期情况
		uint32 exInfo1;//附加信息1(调用者私有信息数据)
		uint32 exInfo1Max;//附加信息1最大值
		uint32 exInfo1Min;//附加信息1最小值
		uint64 runCnt;//运行次数
		/// <summary>
		/// 运行开始
		/// </summary>
		void RunStart();
		/// <summary>
		/// 运行结束
		/// </summary>
		void RunEnd();
		/// <summary>
		/// 清空统计信息
		/// </summary>
		void ClearLoadInfo();
		/// <summary>
		/// 设置名称
		/// </summary>
		void SetName(const char* Name);
		/// <summary>
		/// 名称
		/// </summary>
		/// <returns></returns>
		const char* Name()const;
		/// <summary>
		/// 注册至监视任务
		/// </summary>
		/// <returns></returns>
		int32 Rgs2TaskMonitorRunInfo();
	protected:
		char name[20];
		uint32 lastRunInTime;//单位us
		uint32 lastRunOutTime;//单位us
	};

	typedef void* (*TaskFunction)(void* Para);
	class Task :public InstObject
	{
	public:
		static const uint8 TaskBasePriority = 150;
		static const uint8 RealTimeTaskPriority = 5;
		enum TaskFlag
		{
			E_T_Default,
			E_T_FLOAT = 0x00000001
		};
		enum TaskCore
		{
			E_DefCore,//默认核心
			E_AppCore,//应用核心
			E_ServiceCore,//重要服务核心
			E_AuxCore,//辅助功能核心
		};
		enum Status
		{
			E_Default,
			E_IniedAndNotRun,
			E_Running,
			E_Runin,
			E_Runout,
			E_Suspend,
			E_Exited,
			E_Stoped,
		};
		struct runCheckStattus
		{
			struct Private
			{
				class MsPeriodTimer hourTimer;
				class MsPeriodTimer dayTimer;
			}pri;
			struct Out
			{
				uint32 status;
				uint32 realTimeLoad;
				uint32 realTimePeriod;
				uint32 lastRunInTime;//单位us
				uint32 lastRunOutTime;//单位us
				uint32 maxHourLoad;//小时负载情况
				uint32 maxDayLoad;//天负载情况
				uint32 maxAllLoad;//负载情况
				uint32 minHourLoad;//小时负载情况
				uint32 minDayLoad;//天负载情况
				uint32 minAllLoad;//负载情况
				uint32 maxHourPeriod;//小时周期情况
				uint32 maxDayPeriod;//天周期情况
				uint32 maxAllPeriod;//周期情况
				uint32 minHourPeriod;//小时周期情况
				uint32 minDayPeriod;//天周期情况
				uint32 minAllPeriod;//周期情况
				uint64 runCnt;//运行次数
			}output;
		};
	public:
		Task(const char* Name, uint32 Priority, uint32 StackSize, uint32 Flag, TaskCore Core);
		int32 Start();
		int32 Suspend();
		int32 Exit();
		void ClearRunCalInfo();
		const TaskRunInfo* RunInfo();
		virtual int32 Do();
		virtual int32 DoOnce();
		virtual int32 PowerUpIni(int32 Para);
		virtual int32 OneLoop();
		void MsSleep(uint32 Ms);
		virtual void SaveIds(void* Ele);
		uint32 TaskStep() { return taskStep; }
		uint32 TaskLastStep() { return taskLastStep; }
		uint32 TaskStatus() { return status; }
	protected:
		void CheckLoadStart();
		void CheckLoadEnd();
		virtual ~Task();
	private:
		static void* TaskRunEntry(void* Para);
	protected:
		bool8 forceExit;
		uint32 core;
		uint32 status;
		uint32 taskStep;
		uint32 taskLastStep;
		char name[40];
		uint32 priority;
		uint32 stackSize;
		uint32 flag;
		void* taskHandle;
		TaskRunInfo runInfo;
	};
	class TaskGroup :public InstObjectGroup
	{
	public:
		M_Singleton(TaskGroup);
		int32 PowerUpIni(int32 Para);
	protected:
		TaskGroup();
	};

	void* StartTask(const char* Name, TaskFunction Func, void* Para, unsigned Priority, unsigned StackSize, unsigned Flag, unsigned Core);
	void SetProcessRunAt(uint32 Kernel);
	void SetTaskRunAt(void* Handle, uint32 Kernel);
}

#endif // !SALTASK_H

