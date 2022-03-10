#include "ApiProject.h"
using namespace spt;


int32 spt::SptSampAppTaskScheduler::PostSem()
{
	return RunSem.Post();
}

uint64 spt::SptSampAppTaskScheduler::PowerUpSampIntCnt()
{
	return powerUpSampIntCnt;
}

uint64 spt::SptSampAppTaskScheduler::PowerUpSampStamp()
{
	return 	powerUpSampStamp;
}

uint32 spt::SptSampAppTaskScheduler::SampIntRunCnt()
{
	return sampIntCnt;
}

uint32 spt::SptSampAppTaskScheduler::SampMs()
{
	return sampMs;
}

int32 spt::SptSampAppTaskScheduler::PowerUpIni(int32 Para)
{

	Task::PowerUpIni(0);
	RunSem.Creat(0, 48);
	Start();
	msgRunInfo.SetName("SampMsg");
	msgRunInfo.ClearLoadInfo();
	msgRunInfo.Rgs2TaskMonitorRunInfo();
	dateRunInfo.SetName("SampDate");
	dateRunInfo.ClearLoadInfo();
	dateRunInfo.Rgs2TaskMonitorRunInfo();
	IoInRunInfo.SetName("SampIoIn");
	IoInRunInfo.ClearLoadInfo();
	IoInRunInfo.Rgs2TaskMonitorRunInfo();
	appRunInfo.SetName("SampApp");
	appRunInfo.ClearLoadInfo();
	appRunInfo.Rgs2TaskMonitorRunInfo();
	IoOutRunInfo.SetName("SampIoOut");
	IoOutRunInfo.ClearLoadInfo();
	IoOutRunInfo.Rgs2TaskMonitorRunInfo();
	const struct ApiAppCfg* appcfg = SptMain::Instance().AppCfg();
	if (!appcfg)
	{
		return -1;
	}
	ApiSampAppTask* taskBase = appcfg->sampAppCfg.AppArrBase;
	if (!taskBase)
	{
		return -1;
	}
	uint32 taskNum = appcfg->sampAppCfg.AppArrLen;
	SampAppTask* task;
	for (uint32 i = 0; i < taskNum; i++)
	{
		task = (SampAppTask*)(taskBase + i);
		task->RunInfo().ClearLoadInfo();
		task->RunInfo().Rgs2TaskMonitorRunInfo();
	}
	return 0;
}
//WIM32 ·ÂÕæ
extern "C" int HalSimSampProcess();
int32 spt::SptSampAppTaskScheduler::OneSampIntLoop()
{
	sampIntCnt++;
	powerUpSampIntCnt++;
	powerUpSampStamp += SptSampInt::Instance().PeriodUs();
#ifdef WIN32_SIM
	HalSimSampProcess();
#endif
	msgRunInfo.RunStart();
	SptSampIntMsgProc::Instance().Proc(0);
	msgRunInfo.RunEnd();
	dateRunInfo.RunStart();
	SptDateTask::Instance().UpdateTimeInSampInt();
	dateRunInfo.RunEnd();
	IoInRunInfo.RunStart();
	SptIoProcess::Instance().ProcIn();
	IoInRunInfo.RunEnd();
	if (SptIoProcess::Instance().IsIoPowerUpOver())
	{
		if (powerUpSampIntCnt > 4000)
		{
			appRunInfo.RunStart();
			AppScheduler();
			appRunInfo.RunEnd();
		}
	}
	IoOutRunInfo.RunStart();
	SptIoProcess::Instance().ProcOut();
	IoOutRunInfo.RunEnd();
	return 0;
}

int32 spt::SptSampAppTaskScheduler::OneLoop()
{
	sampMs = SptMsInt::Instance().MsCnt32();
	OneSampIntLoop();
	return 0;
}

int32 spt::SptSampAppTaskScheduler::DoOnce()
{
	if (RunSem.Wait(-1) < 0)
	{
		return 0;
	}
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

void spt::SptSampAppTaskScheduler::ClearAppLoad()
{
	const struct ApiAppCfg* appcfg = SptMain::Instance().AppCfg();
	if (!appcfg)
	{
		return;
	}
	ApiSampAppTask* taskBase = appcfg->sampAppCfg.AppArrBase;
	if (!taskBase)
	{
		return;
	}
	uint32 taskNum = appcfg->sampAppCfg.AppArrLen;
	SampAppTask* task;
	for (uint32 i = 0; i < taskNum; i++)
	{
		task = (SampAppTask*)(taskBase + i);
		task->ClearLoadInfo();
	}
	msgRunInfo.ClearLoadInfo();
	dateRunInfo.ClearLoadInfo();
	IoInRunInfo.ClearLoadInfo();
	appRunInfo.ClearLoadInfo();
	IoOutRunInfo.ClearLoadInfo();
}

spt::SptSampAppTaskScheduler::SptSampAppTaskScheduler()
	:Task("tAppShd", RealTimeTaskPriority, 5 * 1024 * 1024, Task::TaskFlag::E_T_FLOAT, E_AppCore)
{

}

void spt::SptSampAppTaskScheduler::AppScheduler()
{
	const struct ApiAppCfg* appcfg = SptMain::Instance().AppCfg();
	if (!appcfg)
	{
		return;
	}
	ApiSampAppTask* taskBase = appcfg->sampAppCfg.AppArrBase;
	if (!taskBase)
	{
		return;
	}
	uint32 taskNum = appcfg->sampAppCfg.AppArrLen;
	SampAppTask* task;
	for (uint32 i = 0; i < taskNum; i++)
	{
		task = (SampAppTask*)(taskBase + i);
		task->Do();
	}
}

void spt::SampAppTask::ClearLoadInfo()
{
	runInfo.ClearLoadInfo();
}

void spt::SampAppTask::Do()
{
	runTime.schdCnt++;
	if (runTime.schdCnt < period)
	{
		return;
	}
	runTime.schdCnt = 0;
	if (enable && callBack)
	{
		runInfo.RunStart();
		callBack();
		runInfo.RunEnd();
	}
}
