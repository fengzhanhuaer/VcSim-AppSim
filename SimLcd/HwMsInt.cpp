#include"SptProject.h"
using namespace spt;

typedef void(*IntFunc)();

typedef struct
{
	char Enable;
	IntFunc func;
}SptIntData;
#ifdef WIN32_SIM
static SptIntData msIntData = { 0 };
#include<Windows.h>
#pragma  comment (lib, "winmm.lib")
void IntThread()
{
	HANDLE hProc = GetCurrentProcess();
	bool res = SetPriorityClass(hProc, REALTIME_PRIORITY_CLASS);
	//SetProcessAffinityMask(hProc, 2);
	static HANDLE hThread = GetCurrentThread();
	res = SetThreadPriority(hThread, THREAD_PRIORITY_ABOVE_NORMAL);
	uint32 start = HwUsCnt();
	uint32 delta = 0;
	uint32 now = 0;
	uint32 period = 1000;
	uint32 mscnt = 0;
	while (1)
	{
		now = HwUsCnt();
		delta = now - start;
		if (delta >= period)
		{
			static int dbgcnt = 0;

			if (dbgcnt++ >= 1000)
			{
				dbgcnt = 0;
				//DbgMsg << "IntThread delta time is " << delta << "us.\n";
			}
			while (delta >= period)
			{
				mscnt++;
				delta -= period;
				try {
					if (msIntData.Enable == 1)
					{
						msIntData.func();
					}
				}
				catch (...)
				{
					//DbgErr << "SimInt Has Err.\n";
				}
			}
			start = now - delta;
		}
		else
		{
			//Thread::SpinWait(period - delta);
		}
	}
}
void StartIntThread()
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
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)IntThread, 0, 0, 0);
}

extern"C" void SetMsInt(void(*MsIntFunc)(), char Enable)
{
	//Ë³Ðò²»ÄÜµßµ¹
	msIntData.func = MsIntFunc;
	msIntData.Enable = Enable;
	StartIntThread();
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
	//bool res = SetThreadPriority(hThread, THREAD_PRIORITY_ABOVE_NORMAL);

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
	//Ë³Ðò²»ÄÜµßµ¹
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
