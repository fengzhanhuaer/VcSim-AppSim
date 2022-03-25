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
#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;
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
	forceExit = 1;
	while (forceExit)
	{
		if (status == E_Exited)
		{
			break;
		}
		if (status == E_Default)
		{
			break;
		}
		if (status == E_Stoped)
		{
			break;
		}
		if (status == E_Suspend)
		{
			break;
		}
		MsSleep(10);
	}
	return 0;
}

void spt::Task::ClearRunCalInfo()
{
	runInfo.ClearLoadInfo();
}
const TaskRunInfo* spt::Task::RunInfo()
{
	return &runInfo;
}
int32 spt::Task::PowerUpIni(int32 Para)
{
	InstObject::PowerUpIni(name, name, &TaskGroup::Instance(), EIOT_TASK, TaskGroup::Instance().InstId(), TaskGroup::Instance().InstNum());
	runInfo.SetName(name);
	runInfo.Rgs2TaskMonitorRunInfo();
	return 0;
}
int32 spt::Task::Do()
{
	status = E_Running;
	forceExit = 0;
	while (1)
	{
		DoOnce();
		if (forceExit)
		{
			break;
		}
	}
	forceExit = 0;
	status = E_Exited;
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
	LogWarn.Stamp() << "Task " << name << " using dofault Oneloop.You need instantiate it.\n ";
	return 0;
}
void spt::Task::MsSleep(uint32 Ms)
{
	CheckLoadEnd();
	spt::MsSleep(Ms);
	CheckLoadStart();
}
void spt::Task::SaveIds(void* Ele)
{
	tinyxml2::XMLElement* ele = (tinyxml2::XMLElement*)Ele;
	ele->SetAttribute("InstId", instId);
	ele->SetAttribute("GroupId", groupId);
	ele->SetAttribute("Name", name);
	ele->SetAttribute("DesName", desName);
	ele->SetAttribute("Priority", priority);
	ele->SetAttribute("StackSize", stackSize);
	String100B info;
	info = group->DesName();
	info << "." << desName;
	ele->SetAttribute("sAddr", info.Str());
}
void spt::Task::CheckLoadStart()
{
	runInfo.RunStart();
}
void spt::Task::CheckLoadEnd()
{
	runInfo.RunEnd();
}
spt::Task::~Task()
{
	Exit();
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
	SetThreadAffinityMask(Handle, U32OneBitIsTrue[Kernel]);
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
int32 spt::TaskGroup::PowerUpIni(int32 Para)
{
	InstObjectGroup::PowerUpIni("TaskGroup", "TaskGroup", EIOT_TASK, 50);
	return 0;
}

spt::TaskGroup::TaskGroup()
{
	PowerUpIni(0);
}

void spt::TaskRunInfo::RunStart()
{
	uint32 us = HwUsCnt();
	runCnt++;
	if (runCnt == 1)
	{
		lastRunInTime = us;
		return;
	}
	uint32 deltaperiod = us - lastRunInTime;
	lastRunInTime = us;
	if (deltaperiod > 90000000)
	{
		return;
	}
	realTimePeriod = deltaperiod;

	if (deltaperiod > maxHourPeriod)
	{
		maxHourPeriod = deltaperiod;
		if (maxDayPeriod < deltaperiod)
		{
			maxDayPeriod = deltaperiod;
			if (maxAllPeriod < deltaperiod)
			{
				maxAllPeriod = deltaperiod;
			}
		}
	}
	if (deltaperiod < minHourPeriod)
	{
		minHourPeriod = deltaperiod;
		if (minDayPeriod > deltaperiod)
		{
			minDayPeriod = deltaperiod;
			if (minAllPeriod > deltaperiod)
			{
				minAllPeriod = deltaperiod;
			}
			else if (0 == minAllPeriod)
			{
				minAllPeriod = deltaperiod;
			}
		}
		else if (0 == minDayPeriod)
		{
			minDayPeriod = deltaperiod;
		}
	}
	else if (0 == minHourPeriod)
	{
		minHourPeriod = deltaperiod;
	}
	status = Task::E_Runin;
}

void spt::TaskRunInfo::RunEnd()
{
	uint32 us = HwUsCnt();
	uint32 deltaload = us - lastRunInTime;
	if (deltaload > 90000000)
	{
		return;
	}
	lastRunOutTime = us;
	realTimeLoad = deltaload;
	if (deltaload > maxHourLoad)
	{
		maxHourLoad = deltaload;
		if (maxDayLoad < deltaload)
		{
			maxDayLoad = deltaload;
			if (maxAllLoad < deltaload)
			{
				maxAllLoad = deltaload;
			}
		}
	}
	if (deltaload < minHourLoad)
	{
		minHourLoad = deltaload;
		if (minDayLoad > deltaload)
		{
			minDayLoad = deltaload;
			if (minAllLoad > deltaload)
			{
				minAllLoad = deltaload;
			}
			else if (minAllLoad == 0)
			{
				minAllLoad = deltaload;
			}
		}
		else  if (minDayLoad == 0)
		{
			minDayLoad = deltaload;
		}
	}
	else if (minHourLoad == 0)
	{
		minHourLoad = deltaload;
	}
	if (exInfo1Max < exInfo1)
	{
		exInfo1Max = exInfo1;
	}
	if (exInfo1Min > exInfo1)
	{
		exInfo1Min = exInfo1;
	}
	status = Task::E_Runout;
}

void spt::TaskRunInfo::ClearLoadInfo()
{
	maxAllLoad = 0;
	maxDayLoad = 0;
	maxHourLoad = 0;
	minAllLoad = -1;
	minDayLoad = -1;
	minHourLoad = -1;

	maxAllPeriod = 0;
	maxDayPeriod = 0;
	maxHourPeriod = 0;
	minAllPeriod = -1;
	minDayPeriod = -1;
	minHourPeriod = -1;
	exInfo1Max = 0;
	exInfo1Min = -1;
}

void spt::TaskRunInfo::SetName(const char* Name)
{
	StrNCpy(name, Name, sizeof(name));
}

const char* spt::TaskRunInfo::Name()const
{
	return name;
}

int32 spt::TaskRunInfo::Rgs2TaskMonitorRunInfo()
{
	return TaskMonitor::Instance().RgsRunInfo(this);
}
