#include "SalTypes.h"
#ifndef SALTASK_H
#define SALTASK_H

namespace spt
{
	typedef void* (*TaskFunction)(void* Para);
	class Task
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
			E_Default = 0,
			E_IniedAndNotRun = 0x01,
			E_Running = 0x02,
			E_Runin = 0x04,
			E_Runout = 0x08,
			E_Suspend = 0x10,
			E_Exited = 0x20,
			E_Stoped = 0x40,
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
		const runCheckStattus::Out& RunCheckStatus();
		void ClearRunCalInfo();
		virtual int32 Do();
		virtual int32 DoOnce();
		virtual int32 PowerUpIni(int32 Para);
		virtual int32 OneLoop();
		void MsSleep(uint32 Ms);
	protected:
		void CheckLoadStart();
		void CheckLoadEnd();
	private:
		static void* TaskRunEntry(void* Para);
	protected:
		uint32 core;
		uint32 status;
		uint32 taskStep;
		uint32 taskLastStep;
		char name[40];
		uint32 priority;
		uint32 stackSize;
		uint32 flag;
		void* taskHandle;
		runCheckStattus checkstatus;
	};

	void* StartTask(const char* Name, TaskFunction Func, void* Para, unsigned Priority, unsigned StackSize, unsigned Flag, unsigned Core);
	void SetProcessRunAt(uint32 Kernel);
	void SetTaskRunAt(void* Handle, uint32 Kernel);
}

#endif // !SALTASK_H

