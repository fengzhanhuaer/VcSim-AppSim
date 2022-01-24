#include "InstResource.h"


ApiEvent AppEventWarn[E_Warn_Total];
ApiEventGroup AppEventWarnGroup;
ApiEventViewPool HmiViewEventPool;

StatusExInfoDesItem eventData[9] =
{
	{"相别",E_SVT_ENUM32,8,3,&Unit_NULL,EPhaseStr,M_ArrLen(EPhaseStr)},
	{"Ia",E_SVT_I32,8,3,&Unit_A,0,0},
	{"Ib",E_SVT_I32,8,2,&Unit_A,0,0},
	{"Ic",E_SVT_I32,8,3,&Unit_A,0,0},
	{"Ua",E_SVT_I32,8,2,&Unit_V,0,0},
	{"Ub",E_SVT_I32,8,3,&Unit_V,0,0},
	{"Uc",E_SVT_I32,8,2,&Unit_V,0,0},
	{"Code1",E_SVT_HEX32,8,3,&Unit_V,0,0},
};

void AppEventWarnPowerUpIni()
{
	AppEventWarnGroup.PowerUpIni("保护告警信号", "AppEventWarnGroup", E_Warn_Total, 512);
	AppEventWarn[E_Test1].BlPowerUpIni("告警测试1", "E_Test1", AppEventWarnGroup, 0);
	AppEventWarn[E_Test1].ExInfoPowerUpIni(&eventData[0], &eventData[1], &eventData[2], &eventData[3], &eventData[4], &eventData[5]);
	AppEventWarn[E_Test2].DpPowerUpIni("告警测试2", "E_Test2", AppEventWarnGroup, 0);
	HmiViewEventPool.PowerUpIni(5000);
}

void AppEventPowerUpIni()
{
	AppEventWarnPowerUpIni();
}
