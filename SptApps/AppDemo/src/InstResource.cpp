#include "InstResource.h"

void App1SampPointInt();

ApiSampAppTask sampAppArr[1] =
{
	{"1SampInt",App1SampPointInt,1,1},
};


ApiAppCfg AppRunTimeCfg =
{
	{EH_GZKSAU,ES_GZKSAU,ED_SAU31},
	{AppRootMenu,"平台工具集","Soft platform tools",1,"GZK-35kV-T3-Tools-001-S-1-SD-INFO","DTools"},
	{sampAppArr,M_ArrLen(sampAppArr),50000,80}
};
