#include "InstResource.h"

int32 AppCheckFunction1(SptCheckTask::CheckAppInst* Inst)
{
	return 0;
}

SptCheckTask::CheckAppInst appCheckInst[] =
{
	{1,50,0,AppCheckFunction1}
};

void AppCheckPowerUpIni()
{
	for (uint32 i = 0; i < M_ArrLen(appCheckInst); i++)
	{
		SptCheckTask::Instance().AddAppCheckInst(&appCheckInst[i]);
	}
}
