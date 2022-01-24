#include"SptProject.h"
using namespace spt;

#ifdef  WIN32_SIM
#ifndef _WINDOWS_
#include<windows.h>
#endif
unsigned int HwUsCnt()
{
	LARGE_INTEGER m_nFreq;
	LARGE_INTEGER m_Time;

	QueryPerformanceFrequency(&m_nFreq); // 获取时钟周期
	QueryPerformanceCounter(&m_Time); // 获取时钟计数

	uint64 stamp = (uint64)m_Time.QuadPart;
	double coe = 1000000.0 / m_nFreq.QuadPart;
	stamp = (uint64)(stamp * coe);

	return (unsigned int)stamp;
}

extern"C"  int SptSetEthnetPara(int NetNo, char* Ip, char* Mask, char* Gate, char* Mac, char* Flag) { return 0; }
extern"C"  int SptSetEthnetWhiteBill(int NetNo, char* Ip) { return 0; }
extern"C"  int SptEnableEthnetPara(int Type, char Para) { return 0; }
#endif //  WIN32_SIM

#include"SptProject.h"
using namespace spt;

static SptIntData msIntData = { 0 };

#ifdef WIN32_SIM
#include<Windows.h>
#pragma  comment (lib, "winmm.lib")
void IntThread(uint32 Us)
{
	HANDLE hProc = GetCurrentProcess();
	bool res = SetPriorityClass(hProc, REALTIME_PRIORITY_CLASS);
	//SetProcessAffinityMask(hProc, 4);
	static HANDLE hThread = GetCurrentThread();
	res = SetThreadPriority(hThread, THREAD_PRIORITY_ABOVE_NORMAL);
	uint32 start = HwUsCnt();
	uint32 delta = 0;
	uint32 now = 0;
	uint32 period = Us;
	uint32 mscnt = 0;
	while (1)
	{
		now = HwUsCnt();
		delta = now - start;
		if (delta >= period)
		{
			while (delta >= period)
			{
				mscnt++;
				delta -= period;
				if (msIntData.Enable == 1)
				{
					msIntData.func();
				}

			}
			start = now - delta;
		}
		else
		{
			MsSleep(1);
		}
	}
}
void StartIntThread(uint32 Us)
{
	static int flag = 0;
	if (flag)
	{
		return;
	}
	flag = 1;
	static  TIMECAPS  OSTick_TimerCap;
	if (timeGetDevCaps(&OSTick_TimerCap, sizeof(OSTick_TimerCap)) != TIMERR_NOERROR) {
		return;
	}

	if (OSTick_TimerCap.wPeriodMin < 1) {
		OSTick_TimerCap.wPeriodMin = 1;
	}

	if (timeBeginPeriod(OSTick_TimerCap.wPeriodMin) != TIMERR_NOERROR) {

		return;
	}
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)IntThread, (LPVOID)Us, 0, 0);
}

extern"C" void SetMsInt(void(*MsIntFunc)(), char Enable)
{
	//顺序不能颠倒
	msIntData.func = MsIntFunc;
	msIntData.Enable = Enable;
	StartIntThread(1000);
}
extern"C" void SetSampInt(void(*MsIntFunc)(), char Enable, unsigned int Us)
{
	//顺序不能颠倒
	msIntData.func = MsIntFunc;
	msIntData.Enable = Enable;
	StartIntThread(Us);
}
VOID CALLBACK onTimeFunc(PVOID lpParam, BOOLEAN TimerOrWaitFired)
{
	if (msIntData.Enable == 1)
	{
		for (size_t i = 0; i < 10; i++)
		{
			msIntData.func();
		}
	}
}

int32 StartIntNormalThread()
{
	HANDLE hTimer = NULL;
	HANDLE hTimerQueue = NULL;

	HANDLE hProc = GetCurrentProcess();
	//bool res = SetPriorityClass(hProc, REALTIME_PRIORITY_CLASS);
	//SetProcessAffinityMask(hProc, 2);

	static HANDLE hThread = GetCurrentThread();
	//res = SetThreadPriority(hThread, THREAD_PRIORITY_TIME_CRITICAL);

	static  TIMECAPS  OSTick_TimerCap;

	if (timeGetDevCaps(&OSTick_TimerCap, sizeof(OSTick_TimerCap)) != TIMERR_NOERROR) {
		return -1;
	}

	if (OSTick_TimerCap.wPeriodMin < 1) {
		OSTick_TimerCap.wPeriodMin = 1;
	}

	if (timeBeginPeriod(OSTick_TimerCap.wPeriodMin) != TIMERR_NOERROR) {

		return -1;
	}

	// Create the timer queue.
//	hTimerQueue = CreateTimerQueue();
	//if (NULL == hTimerQueue)
	{
		//DbgErr << "CreateTimerQueue failed (" << (uint32)GetLastError() << ")\n";
	//	return 0;
	}

	// Set a timer to call the timer routine in 1 seconds.
	if (!CreateTimerQueueTimer(&hTimer, hTimerQueue,
		(WAITORTIMERCALLBACK)onTimeFunc, 0, 500, 10, WT_EXECUTEINTIMERTHREAD))
	{
		//DbgErr << "CreateTimerQueueTimer failed(" << (uint32)GetLastError() << ")\n";
		return 0;
	}

#if 0
	// TODO: Do other useful work here 

	printf("Call timer routine in 10 seconds...\n");

	// Wait for the timer-queue thread to complete using an event 
	// object. The thread will signal the event at that time.

	if (WaitForSingleObject(gDoneEvent, INFINITE) != WAIT_OBJECT_0)
		printf("WaitForSingleObject failed (%d)\n", GetLastError());

	CloseHandle(gDoneEvent);

	// Delete all timers in the timer queue.
	if (!DeleteTimerQueue(hTimerQueue))
		printf("DeleteTimerQueue failed (%d)\n", GetLastError());
#endif
	return 0;
}
void SetMsNormalInt(void(*MsIntFunc)(), char Enable)
{
	//顺序不能颠倒
	msIntData.func = MsIntFunc;
	msIntData.Enable = Enable;
	StartIntNormalThread();
}

#elif defined(SYLIX_GZK)
void SetMsNormalInt(void(*MsIntFunc)(), char Enable)
{
	msIntData.func = MsIntFunc;
	msIntData.Enable = Enable;
}
#endif // WIN32_SIM


