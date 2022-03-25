#include "SalTypes.h"
#ifndef SALTASK_H
#define SALTASK_H

namespace spt
{
	struct TaskRunInfo
	{
	public:
		uint32 status;//Task::Status
		uint32 realTimeLoad;//ʵʱ����
		uint32 realTimePeriod;//ʵʱ����
		uint32 maxHourLoad;//Сʱ�������
		uint32 maxDayLoad;//�츺�����
		uint32 maxAllLoad;//�������
		uint32 minHourLoad;//Сʱ�������
		uint32 minDayLoad;//�츺�����
		uint32 minAllLoad;//�������
		uint32 maxHourPeriod;//Сʱ�������
		uint32 maxDayPeriod;//���������
		uint32 maxAllPeriod;//�������
		uint32 minHourPeriod;//Сʱ�������
		uint32 minDayPeriod;//���������
		uint32 minAllPeriod;//�������
		uint32 exInfo1;//������Ϣ1(������˽����Ϣ����)
		uint32 exInfo1Max;//������Ϣ1���ֵ
		uint32 exInfo1Min;//������Ϣ1��Сֵ
		uint64 runCnt;//���д���
		/// <summary>
		/// ���п�ʼ
		/// </summary>
		void RunStart();
		/// <summary>
		/// ���н���
		/// </summary>
		void RunEnd();
		/// <summary>
		/// ���ͳ����Ϣ
		/// </summary>
		void ClearLoadInfo();
		/// <summary>
		/// ��������
		/// </summary>
		void SetName(const char* Name);
		/// <summary>
		/// ����
		/// </summary>
		/// <returns></returns>
		const char* Name()const;
		/// <summary>
		/// ע������������
		/// </summary>
		/// <returns></returns>
		int32 Rgs2TaskMonitorRunInfo();
	protected:
		char name[20];
		uint32 lastRunInTime;//��λus
		uint32 lastRunOutTime;//��λus
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
			E_DefCore,//Ĭ�Ϻ���
			E_AppCore,//Ӧ�ú���
			E_ServiceCore,//��Ҫ�������
			E_AuxCore,//�������ܺ���
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
				uint32 lastRunInTime;//��λus
				uint32 lastRunOutTime;//��λus
				uint32 maxHourLoad;//Сʱ�������
				uint32 maxDayLoad;//�츺�����
				uint32 maxAllLoad;//�������
				uint32 minHourLoad;//Сʱ�������
				uint32 minDayLoad;//�츺�����
				uint32 minAllLoad;//�������
				uint32 maxHourPeriod;//Сʱ�������
				uint32 maxDayPeriod;//���������
				uint32 maxAllPeriod;//�������
				uint32 minHourPeriod;//Сʱ�������
				uint32 minDayPeriod;//���������
				uint32 minAllPeriod;//�������
				uint64 runCnt;//���д���
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

