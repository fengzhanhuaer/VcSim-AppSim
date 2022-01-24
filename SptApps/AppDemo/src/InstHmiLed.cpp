#include"InstResource.h"

ApiHmiLedGroup hmiLedGroup;

ApiHmiLed hmiLed[5];

void AppHmiLedPowerUpIni()
{
	hmiLedGroup.PowerUpIni("液晶显示灯", "hmiLedGroup", M_ArrLen(hmiLed));

	hmiLed[0].PowerUpIni("运行", "hmiLed1", hmiLedGroup, HmiLed::E_GREEN, 0, 0, 0);
	hmiLed[1].PowerUpIni("告警", "hmiLed1", hmiLedGroup, HmiLed::E_RED, 1, 1, 0);
	hmiLed[2].PowerUpIni("异常", "hmiLed1", hmiLedGroup, HmiLed::E_YELLOW, 2, 2, 0);
	hmiLed[3].PowerUpIni("跳闸", "hmiLed1", hmiLedGroup, HmiLed::E_GREEN, 3, 4, 1);
	hmiLed[4].PowerUpIni("失电", "hmiLed1", hmiLedGroup, HmiLed::E_RED, 4, 6, 0);
}