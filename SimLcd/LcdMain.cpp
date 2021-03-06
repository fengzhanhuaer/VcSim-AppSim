#include"LcdMain.h"
using namespace spt;

LcdMain& spt::LcdMain::Instance()
{
	static LcdMain inst;
	return inst;
}
#ifndef WIN32_LCD_SIM
extern uint16 __checksum;
void spt::LogMsg(const char* Msg, int32 Data1, int32  Data2, int32  Data3)
{

}
#endif
int32 spt::LcdMain::PowerUpIni(int32 Para)
{
	version = 91;
	progDate = 0x20220211;
	progCrc = 0xFFFF;
	checkCrc = 0xFFFF;
	LcdHalPowerUpIni();
	HmiLcdCmm::Instance().PowerUpIni(0);
	GraphicDevice::Instance().PowerUpIni(0);
	SptMsInt::Instance().PowerUpIni(1);
#ifdef WIN32_LCD_SIM
	VirLcdCmmClient::Instance().PowerUpIni(0);
	SocketEnvStartUp();
	Start();
#else 
	checkCrc = Crc16ModBus.CalCrc((void*)0x80000000, 1024 * 300);
	//checkCrc = __checksum;
#endif // LCD_SIM
	return 0;
}
uint32 mainLoopLoaddelta;
int32 spt::LcdMain::OneLoop()
{
	uint32 start = HwUsCnt();
	HmiLcdCmm::Instance().Proc();
	HalLcdDriver::Instance().OneLoop();
	uint32 end = HwUsCnt();
#ifdef WIN32_LCD_SIM
	VirLcdCmmClient::Instance().OneLoop();
	mainLoopLoaddelta = (end - start) / 1000;
	MsSleep(20);
#endif
	return 0;
}

spt::LcdMain::LcdMain()
#ifdef WIN32_LCD_SIM
	:Task("tLcdMain", RealTimeTaskPriority, 128 * 1024, 0, Task::E_DefCore)
#endif
{

}

#ifndef WIN32_LCD_SIM
extern "C" void AppLoop()
{
	LcdMain::Instance().OneLoop();
}
extern "C" void AppPowerUpIni()
{
	LcdMain::Instance().PowerUpIni(0);
}
#endif