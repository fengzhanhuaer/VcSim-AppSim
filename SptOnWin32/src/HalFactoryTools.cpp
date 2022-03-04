#include "SptProject.h"
using namespace spt;

const char* FactoryRoot = "/media/sdcard1/Update/";

extern "C" int FactoryModeFormat(int (*Process)(int Step, const char* info))
{
	LogMsg << "Program run into factory mode.\n";

	FactoryModeCfg::Instance().PowerUpIni(0);
	int Step = 0;
	FactoryModeCfg& cfg = FactoryModeCfg::Instance();
	String100B str;
	if (cfg.UpdateBoot0.Data())
	{
		str = FactoryRoot;
		str << FilePath::DivFlag << "Sylix.Boot0.bin";
		if (0 != Access(str.Str(), 0))
		{
			str = CN_UPDATE_FILE_ROOT;
			str << FilePath::DivFlag << "Sylix.Boot0.bin";
		}

		int res = UpdateBoot0ForLcd(str.Str(), 0);
		if (res)
		{
			str = "Boot0升级失败。";
		}
		else
		{
			str = "Boot0升级成功。";
		}
		if (Process)
		{
			Process(Step, str.Str());
		}
		LogMsg << str << "\n\n";
		Step++;
	}
	if (cfg.UpdateUBoot.Data())
	{
		str = FactoryRoot;
		str << FilePath::DivFlag << "Sylix.UBoot.bin";
		if (0 != Access(str.Str(), 0))
		{
			str = CN_UPDATE_FILE_ROOT;
			str << FilePath::DivFlag << "Sylix.UBoot.bin";
		}

		int res = UpdateUBootForLcd(str.Str(), 0);
		if (res)
		{
			str = "UBoot升级失败。";
		}
		else
		{
			str = "UBoot升级成功。";
		}
		if (Process)
		{
			Process(Step, str.Str());
		}
		LogMsg << str << "\n\n";
		Step++;
	}
	if (cfg.UpdateSystem.Data())
	{
		str = FactoryRoot;
		str << FilePath::DivFlag << "Sylix.T3BSP.bin";
		if (0 != Access(str.Str(), 0))
		{
			str = CN_UPDATE_FILE_ROOT;
			str << FilePath::DivFlag << "Sylix.T3BSP.bin";
		}
		int res = UpdateOsForLcd(str.Str(), 0);
		if (res)
		{
			str = "操作系统升级失败。";
		}
		else
		{
			str = "操作系统升级成功。";
		}
		if (Process)
		{
			Process(Step, str.Str());
		}
		LogMsg << str << "\n\n";
		Step++;
	}
	if (cfg.FormatSysCard.Data())
	{
		int res = FormatSysCard(0);
		if (res)
		{
			str = "系统盘格式化失败。";
		}
		else
		{
			str = "系统盘格式化成功。";
		}
		if (Process)
		{
			Process(Step, str.Str());
		}
		LogMsg << str << "\n\n";
		Step++;
	}
	if (cfg.FormatDataCard.Data())
	{
		int res = FormatDataCard(0);
		if (res)
		{
			str = "数据盘格式化失败。";
		}
		else
		{
			str = "数据盘格式化成功。";
		}
		if (Process)
		{
			Process(Step, str.Str());
		}
		LogMsg << str << "\n\n";
		Step++;
	}
	if (Process)
	{
		Process(Step, "按任意键继续");
	}
	return 0;
}

int32 spt::FactoryModeCfg::PowerUpIni(int32 Para)
{
	UpdateBoot0.SetIfNoDefault("UpdateBoot0", 0);
	AddCfgData(&UpdateBoot0);
	UpdateUBoot.SetIfNoDefault("UpdateUBoot", 0);
	AddCfgData(&UpdateUBoot);
	UpdateSystem.SetIfNoDefault("UpdateSystem", 0);
	AddCfgData(&UpdateSystem);
	FormatSysCard.SetIfNoDefault("格式化系统盘", 0);
	AddCfgData(&FormatSysCard);
	FormatDataCard.SetIfNoDefault("格式化数据盘", 0);
	AddCfgData(&FormatDataCard);

	path.Set(SptMain::Instance().AppRoot().Str());
	name.Set("FactoryMode.cfg");
	if ((uint32)ReadAll() != CfgDataNum())
	{
		SaveAll();
	}
	return 0;
}

FactoryModeCfg& spt::FactoryModeCfg::Instance()
{
	static FactoryModeCfg inst;
	return inst;
}
