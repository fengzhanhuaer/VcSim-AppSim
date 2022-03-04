#ifndef SPTMAIN_H
#define SPTMAIN_H

#include "SptMsInt.h"
namespace spt
{
	class SptMain
	{
	public:
		enum E_StartMode
		{
			E_Normal,
			E_Factory,
		};
	public:
		const struct ApiAppCfg* AppCfg();
		void SetAppCfg(struct ApiAppCfg* AppCfg, int argc, char** argv);
		E_StartMode StartMode();
	public:
		const SalString& AppRoot();
		static SptMain& Instance();
		void PowerUpIni(int32 Para);
		void Run();
	protected:
		void PowerUpDealStartPara(int argc, char** argv);
		SptMain();
		~SptMain();
	private:
		String100B appRoot;
		struct ApiAppCfg* appCfg;
		E_StartMode startmode;
	};
	void LogMsg(const char* Msg, int32 Data1, int32  Data2, int32  Data3);
}

extern "C" {
	int SptEntry(int argc, char** argv);
	int OsStartUp();
}


#endif // !SPTMAIN_H

