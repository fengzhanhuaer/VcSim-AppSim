#ifndef LCDHAL_H
#define LCDHAL_H

#include"LcdHalDriver.h"

namespace spt
{
	void LcdHalPowerUpIni();
	void LcdSetDispInfo(uint16 IedNum, const char* Name);
	void LcdSetLedDispInfo(uint16 IedSerial, uint16 Cor, const char* LedName);
}
#endif // !LCDHAL_H

