#include"InstResource.h"

ApiHmiLedGroup hmiLedGroup;

ApiHmiLed hmiLed[5];

void AppHmiLedPowerUpIni()
{
	hmiLedGroup.PowerUpIni("Һ����ʾ��", "hmiLedGroup", M_ArrLen(hmiLed));

	hmiLed[0].PowerUpIni("����", "hmiLed1", hmiLedGroup, HmiLed::E_GREEN, 0, 0, 0);
	hmiLed[1].PowerUpIni("�澯", "hmiLed1", hmiLedGroup, HmiLed::E_RED, 1, 1, 0);
	hmiLed[2].PowerUpIni("�쳣", "hmiLed1", hmiLedGroup, HmiLed::E_YELLOW, 2, 2, 0);
	hmiLed[3].PowerUpIni("��բ", "hmiLed1", hmiLedGroup, HmiLed::E_GREEN, 3, 4, 1);
	hmiLed[4].PowerUpIni("ʧ��", "hmiLed1", hmiLedGroup, HmiLed::E_RED, 4, 6, 0);
}