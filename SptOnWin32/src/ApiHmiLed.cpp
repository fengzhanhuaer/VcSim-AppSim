#include"ApiProject.h"
using namespace spt;

void spt::ApiHmiLedGroup::PowerUpIni(const char* Name, const char* DesName, uint16 EventNum)
{
	HmiLedGroup::PowerUpIni(Name, DesName, EventNum);
}

void spt::ApiHmiLed::PowerUpIni(const char* Name, const char* DesName, ApiHmiLedGroup& Group, Color color, uint8 Col, uint8 Row, bool8 HoldOn)
{
	HmiLedGroup* g = (HmiLedGroup*)&Group;
	HmiLed::PowerUpIni(Name, DesName, g, color, Col, Row, HoldOn);
}

void spt::ApiHmiLed::SetValue(uint8 Val)
{
	HmiLed::SetValue(Val);
}

uint8 spt::ApiHmiLed::Value()
{
	return val != 0;
}
