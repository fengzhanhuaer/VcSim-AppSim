#ifndef HALFACTORYTOOLS_H
#define HALFACTORYTOOLS_H

extern "C"
{
	typedef int(*HalProcess)(int Step, const char* info);
	int FactoryModeFormat(int (*Process)(int Step, const char* info));
	int UpdateBoot0ForLcd(const char* SptOsName, int (*Process)(int Step, const char* info));
	int UpdateUBootForLcd(const char* SptOsName, int (*Process)(int Step, const char* info));
	int UpdateOsForLcd(const char* SptOsName, int (*Process)(int Step, const char* info));
	int BakUpFlashForLcd(int (*Process)(int Step, const char* info));
	int RestoreFlashPara(int (*Process)(int Step, const char* info));
	int FormatSysCard(int (*Process)(int Step, const char* info));
	int FormatDataCard(int (*Process)(int Step, const char* info));
}

namespace spt
{
	class FactoryModeCfg :public CfgFile
	{
	public:
		int32 PowerUpIni(int32 Para);
		static FactoryModeCfg& Instance();
	protected:
		virtual PCfgDataBase* CfgPool() { return pool; };
		virtual uint32 CfgPoolSize() { return M_ArrLen(pool); };
	public:
		CfgBool UpdateBoot0;
		CfgBool UpdateUBoot;
		CfgBool UpdateSystem;
		CfgBool FormatSysCard;
		CfgBool FormatDataCard;
	private:
		PCfgDataBase pool[50];
	};
}




#endif // !HALFACTORYTOOLS_H
