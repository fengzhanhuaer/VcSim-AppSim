#include"SptProject.h"
using namespace spt;

spt::TaskMonitor::TaskMonitor()
	:Task("tMonitor", RealTimeTaskPriority + 50, 1024 * 1024, Task::E_T_FLOAT, E_ServiceCore)
{

}

int32 spt::TaskMonitor::PowerUpIni(int32 Para)
{
	Task::PowerUpIni(0);
	Start();
	taskRunInfo.isInfoOk = 1;
	return 0;
}

int32 spt::TaskMonitor::OneLoop()
{
	switch (taskStep)
	{
	case E_PowerUpIni:
	{
		taskStep = E_Work;
		break;
	}
	case E_Work:
	{
		MsSleep(100);
		CheckLoad();
		break;
	}
	default:
		taskStep = E_PowerUpIni;
		break;
	}
	return 0;
}

int32 spt::TaskMonitor::RgsRunInfo(spt::TaskRunInfo* taskRunInfo)
{
	if (taskRunInfo && (this->taskRunInfo.taskNum < M_ArrLen(this->taskRunInfo.info)))
	{
		this->taskRunInfo.info[this->taskRunInfo.taskNum].taskRunInfo = taskRunInfo;
		this->taskRunInfo.taskNum++;
		return 0;
	}
	return -1;
}

void spt::TaskMonitor::ClearCalRunInfo()
{
	for (uint32 i = 0; i < taskRunInfo.taskNum; i++)
	{
		spt::TaskRunInfo* out = (spt::TaskRunInfo*)taskRunInfo.info[i].taskRunInfo;
		out->ClearLoadInfo();
	}
}

const TaskMonitor::RunInfo& spt::TaskMonitor::TaskRunInfo()
{
	return taskRunInfo;
}

void spt::TaskMonitor::CheckLoad()
{
	if (HourTimer.Status())
	{
		HourTimer.Restart();
		PrintLoad();
		for (uint32 i = 0; i < taskRunInfo.taskNum; i++)
		{
			spt::TaskRunInfo* out = (spt::TaskRunInfo*)taskRunInfo.info[i].taskRunInfo;
			out->minHourLoad = -1;
			out->maxHourLoad = 0;
			out->minHourPeriod = -1;
			out->maxHourPeriod = 0;
		}
	}
	else if (!HourTimer.IsEnable())
	{
		HourTimer.UpCnt(HourTimer.Mt1Hour);
		HourTimer.Enable(1);
		return;
	}
	else
	{
		return;
	}
	if (DayTimer.Status())
	{
		DayTimer.Restart();
		for (uint32 i = 0; i < taskRunInfo.taskNum; i++)
		{
			spt::TaskRunInfo* out = (spt::TaskRunInfo*)taskRunInfo.info[i].taskRunInfo;
			out->minDayLoad = -1;
			out->maxDayLoad = 0;
			out->minDayPeriod = -1;
			out->maxDayPeriod = 0;
		}
	}
	else if (!DayTimer.IsEnable())
	{
		DayTimer.UpCnt(DayTimer.Mt1Day);
		DayTimer.Enable(1);
		return;
	}
	else
	{
		return;
	}
}

void spt::TaskMonitor::PrintLoad()
{
	String1000B str;
	str << "PowerUpTime ";
	str.FormatMs(SptMsInt::Instance().MsCnt64());
	LogLoad.Stamp().Print("任务运行监视 单位(us)").Print(str.Str()).EndLine();
	LogLoad.PrintLine("Task              运行次数      实时周期   最大周期(时)  最小周期(时)  最大周期(天)  最小周期(天)     最大周期      最小周期      实时负载   最大负载(时)  最小负载(时)  最大负载(天)  最小负载(天)     最大负载      最小负载");
	for (uint32 i = 0; i < taskRunInfo.taskNum; i++)
	{
		const spt::TaskRunInfo* out = taskRunInfo.info[i].taskRunInfo;
		str.Clear();

		str.Format(out->Name(), 12, 1, ' ');
		str.Format(out->runCnt, 14, ' ');
		str.Format(out->realTimePeriod, 14, ' ');
		str.Format(out->maxHourPeriod, 14, ' ');
		str.Format(out->minHourPeriod, 14, ' ');
		str.Format(out->maxDayPeriod, 14, ' ');
		str.Format(out->minDayPeriod, 14, ' ');
		str.Format(out->maxAllPeriod, 14, ' ');
		str.Format(out->minAllPeriod, 14, ' ');


		str.Format(out->realTimeLoad, 14, ' ');
		str.Format(out->maxHourLoad, 14, ' ');
		str.Format(out->minHourLoad, 14, ' ');
		str.Format(out->maxDayLoad, 14, ' ');
		str.Format(out->minDayLoad, 14, ' ');
		str.Format(out->maxAllLoad, 14, ' ');
		str.Format(out->minAllLoad, 14, ' ');
		LogLoad << str << "\n";
	}
}

