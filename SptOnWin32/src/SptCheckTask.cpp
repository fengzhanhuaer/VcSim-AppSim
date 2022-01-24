#include"ApiProject.h"
using namespace spt;

int32 spt::SptCheckTask::AddAppCheckInst(CheckAppInst* Inst)
{
	int32 cnt = (int32)checkInstNum;
	if (cnt >= (int32)M_ArrLen(checkInst))
	{
		return -1;
	}
	checkInst[cnt] = Inst;
	checkInstNum++;
	return cnt;
}

int32 spt::SptCheckTask::PowerUpIni(int32 Para)
{
	Task::PowerUpIni(0);
	Start();
	return 0;
}

int32 spt::SptCheckTask::OneLoop()
{
	if (checkInstNum)
	{
		uint32 msNow = SptMsInt::Instance().MsCnt32();
		for (uint32 i = 0; i < checkInstNum; i++)
		{
			if (checkInst[i] && checkInst[i]->enable && checkInst[i]->func)
			{
				uint32 delta = msNow - checkInst[i]->lastRunTime;
				if (delta > checkInst[i]->period)
				{
					checkInst[i]->func(checkInst[i]);
					checkInst[i]->lastRunTime = msNow;
				}
				MsSleep(2);
			}
		}
	}
	else
	{
		MsSleep(100);
	}
	MsSleep(10);
	return 0;
}

spt::SptCheckTask::SptCheckTask()
	:Task("tCheck", TaskBasePriority + 50, 1 * 1024 * 1024, Task::TaskFlag::E_T_FLOAT, E_ServiceCore)
{
	checkInstNum = 0;
}