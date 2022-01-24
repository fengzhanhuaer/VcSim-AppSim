#include "ApiProject.h"
using namespace spt;
spt::ApiSampAppTask::ApiSampAppTask(const char* TaskName, AppTaskCallBack CallBack, bool8 Enable, uint32 Period)
{
	period = Period;
	callBack = CallBack;
	enable = Enable;
	StrNCpy(name, TaskName, sizeof(name));
	runInfo.SetName(name);
}

uint64 spt::ApiSampAppTask::RunCnt()
{
	return runInfo.runCnt;
}
bool8 spt::ApiSampAppTask::IsEnable()
{
	return enable;
}
bool8 spt::ApiSampAppTask::Enable(bool8 En)
{
	return enable = En;
}

void spt::ApiSampAppTask::ClearLoadInfo()
{
	SampAppTask::ClearLoadInfo();
}
