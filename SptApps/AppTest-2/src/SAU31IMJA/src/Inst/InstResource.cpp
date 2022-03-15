#include "InstResource.h"

void App1SampPointInt();

ApiSampAppTask sampAppArr[1] =
{
	{"1SampInt",App1SampPointInt,0,1},
};

ApiAppCfg AppRunTimeCfg =
{
#if(CN_DEV_CPU1)
	{EH_GZKSAU,ES_GZKSAU,ED_SAU31},
	{AppRootMenu,"间隔Ⅰ采集执行单元C1","SAU-32IMJA-DA-GZK",1,"GZK-35kV-T3-Tools-001-S-1-SD-INFO"},
#elif(CN_DEV_CPU2)
	{EH_GZKSAU,ES_GZKSAU,ED_SAU31_Sub},
	{AppRootMenu,"间隔Ⅰ采集执行单元C2","SAU-32IMJA-DA-GZK",1,"GZK-35kV-T3-Tools-001-S-1-SD-INFO"},
#endif
	{sampAppArr,M_ArrLen(sampAppArr),50,80}
};

