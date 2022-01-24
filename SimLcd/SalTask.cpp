#include "SptProject.h"
using namespace spt;
#ifdef WIN32_SIM
#include<Windows.h>
#endif

#ifdef SYLIX_GZK
#include <pthread.h>
#include <unistd.h>
#include <sys/resource.h>
#include <SylixOS.h>
#endif
spt::Task::Task(const char* Name, uint32 Priority, uint32 StackSize, uint32 Flag, TaskCore Core)
{
	status = 0;
	taskStep = 0;
	StrNCpy(name, Name, sizeof(name));
	flag = Flag;
	stackSize = StackSize;
	priority = Priority;
	taskHandle = 0;
	taskLastStep = 0;
	core = Core;
}


int32 spt::Task::Start()
{
	if ((status == E_Running) || (status == E_Suspend))
	{
		return 0;
	}
	return (int32)(taskHandle = StartTask(name, TaskRunEntry, (Task*)this, priority, stackSize, flag, core));
}

int32 spt::Task::Suspend()
{
	return 0;
}

int32 spt::Task::Exit()
{
	return status = E_Exited;
}
const Task::runCheckStattus::Out& spt::Task::RunCheckStatus()
{
	return checkstatus.output;
}
int32 spt::Task::PowerUpIni(int32 Para)
{
	return 0;
}
int32 spt::Task::Do()
{
	while ((status & E_Exited) == 0)
	{
		DoOnce();
	}
	return 0;
}
int32 spt::Task::DoOnce()
{
	CheckLoadStart();
	uint32 step = taskStep;
	OneLoop();
	if (step != taskStep)
	{
		taskLastStep = step;
	}
	CheckLoadEnd();
	return 0;
}
int32 spt::Task::OneLoop()
{
	return 0;
}
void spt::Task::MsSleep(uint32 Ms)
{
	CheckLoadEnd();
	spt::MsSleep(Ms);
	CheckLoadStart();
}
void spt::Task::CheckLoadStart()
{
	uint32 us = HwUsCnt();
	checkstatus.output.runCnt++;
	uint32 deltaperiod = us - checkstatus.output.lastRunInTime;

	if (checkstatus.output.lastRunInTime == 0)
	{
		checkstatus.output.lastRunInTime = us;
		return;
	}
	checkstatus.output.lastRunInTime = us;
	if (deltaperiod > 90000000)
	{
		return;
	}
	checkstatus.output.realTimePeriod = deltaperiod;

	if (checkstatus.pri.hourTimer.Status())
	{
		checkstatus.pri.hourTimer.Restart();
		checkstatus.output.maxHourPeriod = deltaperiod;
		checkstatus.output.minHourPeriod = deltaperiod;
		checkstatus.output.maxHourLoad = 0;
		checkstatus.output.minHourLoad = -1;
		if (checkstatus.pri.dayTimer.Status())
		{
			checkstatus.pri.dayTimer.Restart();
			checkstatus.output.maxDayPeriod = deltaperiod;
			checkstatus.output.minDayPeriod = deltaperiod;
			checkstatus.output.maxDayLoad = 0;
			checkstatus.output.minDayLoad = -1;
		}
		else if (!checkstatus.pri.dayTimer.IsEnable())
		{
			checkstatus.pri.dayTimer.UpCnt(MsTimer::Mt1Day);
			checkstatus.pri.dayTimer.Enable(1);
		}
	}
	else if (!checkstatus.pri.hourTimer.IsEnable())
	{
		checkstatus.pri.hourTimer.UpCnt(MsTimer::Mt1Hour);
		checkstatus.pri.hourTimer.Enable(1);
	}
	if (deltaperiod > checkstatus.output.maxHourPeriod)
	{
		checkstatus.output.maxHourPeriod = deltaperiod;
		if (checkstatus.output.maxDayPeriod < deltaperiod)
		{
			checkstatus.output.maxDayPeriod = deltaperiod;
			if (checkstatus.output.maxAllPeriod < deltaperiod)
			{
				checkstatus.output.maxAllPeriod = deltaperiod;
			}
		}
	}
	if (deltaperiod < checkstatus.output.minHourPeriod)
	{
		checkstatus.output.minHourPeriod = deltaperiod;
		if (checkstatus.output.minDayPeriod > deltaperiod)
		{
			checkstatus.output.minDayPeriod = deltaperiod;
			if (checkstatus.output.minAllPeriod > deltaperiod)
			{
				checkstatus.output.minAllPeriod = deltaperiod;
			}
			else if (0 == checkstatus.output.minAllPeriod)
			{
				checkstatus.output.minAllPeriod = deltaperiod;
			}
		}
		else if (0 == checkstatus.output.minDayPeriod)
		{
			checkstatus.output.minDayPeriod = deltaperiod;
		}
	}
	else if (0 == checkstatus.output.minHourPeriod)
	{
		checkstatus.output.minHourPeriod = deltaperiod;
	}

	checkstatus.output.status = E_Runin;
}
void spt::Task::CheckLoadEnd()
{
	uint32 us = HwUsCnt();

	uint32 deltaload = us - checkstatus.output.lastRunInTime;

	if (deltaload > 90000000)
	{
		return;
	}

	checkstatus.output.lastRunOutTime = us;
	checkstatus.output.realTimeLoad = deltaload;
	if (deltaload > checkstatus.output.maxHourLoad)
	{
		checkstatus.output.maxHourLoad = deltaload;
		if (checkstatus.output.maxDayLoad < deltaload)
		{
			checkstatus.output.maxDayLoad = deltaload;
			if (checkstatus.output.maxAllLoad < deltaload)
			{
				checkstatus.output.maxAllLoad = deltaload;
			}
		}
	}
	if (deltaload < checkstatus.output.minHourLoad)
	{
		checkstatus.output.minHourLoad = deltaload;
		if (checkstatus.output.minDayLoad > deltaload)
		{
			checkstatus.output.minDayLoad = deltaload;
			if (checkstatus.output.minAllLoad > deltaload)
			{
				checkstatus.output.minAllLoad = deltaload;
			}
			else if (checkstatus.output.minAllLoad == 0)
			{
				checkstatus.output.minAllLoad = deltaload;
			}
		}
		else  if (checkstatus.output.minDayLoad == 0)
		{
			checkstatus.output.minDayLoad = deltaload;
		}
	}
	else if (checkstatus.output.minHourLoad == 0)
	{
		checkstatus.output.minHourLoad = deltaload;
	}

	checkstatus.output.status = E_Runout;
}
void* spt::Task::TaskRunEntry(void* Para)
{
	Task* task = (Task*)Para;
	task->Do();
	return 0;
}
#ifdef WIN32_SIM
typedef struct tagTHREADNAME_INFO {
	DWORD dwType;  // Must be 0x1000.
	LPCSTR szName;  // Pointer to name (in user addr space).
	DWORD dwThreadID;  // Thread ID (-1=caller thread).
	DWORD dwFlags;  // Reserved for future use, must be zero.
} THREADNAME_INFO;
void* spt::StartTask(const char* Name, TaskFunction Func, void* Para, unsigned Priority, unsigned StackSize, unsigned Flag, unsigned Core)
{
	uint32 flag = 0;
	if (Flag & Task::E_T_FLOAT)
	{
		flag = 0;
	}

	DWORD  threadId;
	void* handle = CreateThread(0, StackSize, (PTHREAD_START_ROUTINE)Func, Para, flag, &threadId);
	if (handle)
	{
		SetTaskRunAt(handle, Core);
	}
	if (Priority < 50)
	{
		//	SetThreadPriority(handle, THREAD_PRIORITY_ABOVE_NORMAL);
	}
#if 0
	const DWORD kVCThreadNameException = 0x406D1388;

	if (!::IsDebuggerPresent())
	{
		return handle;
	}
	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = Name;
	info.dwThreadID = threadId;
	info.dwFlags = 0;

	try
	{
		RaiseException(kVCThreadNameException, 0, sizeof(info) / sizeof(DWORD), reinterpret_cast<DWORD_PTR*>(&info));
	}
	catch (...)
	{

	}
#endif
	return handle;
}

#elif defined(SYLIX_GZK)
#include <pthread.h>
#include <unistd.h>
#include <sys/resource.h>
#include <SylixOS.h>
void* spt::StartTask(const char* Name, TaskFunction Func, void* Para, unsigned Priority, unsigned StackSize, unsigned Flag, unsigned Core)
{
	uint32 flag = 0;
	if (Flag & Task::E_T_FLOAT)
	{
		flag |= LW_OPTION_THREAD_USED_FP;
	}
	flag |= LW_OPTION_THREAD_STK_CHK | LW_OPTION_THREAD_STK_CLR;
	LW_CLASS_THREADATTR threadattr;
	Lw_ThreadAttr_Build(&threadattr,
		StackSize,
		Priority,
		flag,
		Para);
	void* handle = (void*)Lw_Thread_Create(Name, Func, &threadattr, LW_NULL);
	if (handle)
	{
		SetTaskRunAt(handle, Core);
	}
	return handle;
}
#endif // WIN32_SIM

void spt::SetProcessRunAt(uint32 Kernel)
{
#ifdef WIN32_SIM
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	if (Kernel > SystemInfo.dwNumberOfProcessors)
	{
		Kernel = SystemInfo.dwNumberOfProcessors;
	}
	//SetProcessAffinityMask(GetCurrentProcess(), U32OneBitIsTrue[Kernel]);
#elif defined(SYLIX_GZK)
	if (Kernel == Task::E_DefCore)
	{
		Kernel = 2;
	}
	else
	{
		return;
	}
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(Kernel, &cpuset);
	sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpuset);
#endif // WIN32_SIM

}

void spt::SetTaskRunAt(void* Handle, uint32 Kernel)
{
#ifdef WIN32_SIM
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	if (Kernel > SystemInfo.dwNumberOfProcessors)
	{
		Kernel = SystemInfo.dwNumberOfProcessors;
	}
	//SetThreadAffinityMask(Handle, U32OneBitIsTrue[Kernel]);
#elif defined(SYLIX_GZK)
	if (Kernel == Task::E_AppCore)
	{
		Kernel = 3;
	}
	else
	{
		Kernel = 2;
	}
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(Kernel, &cpuset);
	pthread_setaffinity_np((LW_HANDLE)Handle, sizeof(cpu_set_t), &cpuset);
	CPU_ZERO(&cpuset);
	CPU_SET(3, &cpuset);
	Lw_Cpu_SetSchedAffinity(sizeof(cpu_set_t), &cpuset);
#endif
}
