#ifndef LCDMAIN_H
#define LCDMAIN_H
#include"SptProject.h"
#include"LcdHal.h"
#include"HmiVirLcdLayer.h"
#ifdef WIN32_SIM
#endif // WIN32_SIM



namespace spt
{
#ifdef WIN32_SIM
	class LcdMain :public Task
#else 
	class LcdMain
#endif
	{
	public:
		static LcdMain& Instance();
	public:
		virtual int32 PowerUpIni(int32 Para);
		virtual int32 OneLoop();
		uint32 Version() { return version; };
		uint32 ProgDate() { return progDate; };
		uint32 ProgCrc() { return progCrc; };
		uint32 CheckCrc() { return checkCrc; };
	protected:
		LcdMain();
		uint32 version;
		uint32 progDate;
		uint32 progCrc;
		uint32 checkCrc;
	};
}



#endif // !LCDMAIN_H

