#include "ApiProject.h"
using namespace spt;

void spt::ApiVersionInfo::Print()
{
	String5000B str;
	SalFile file;
	if (SptMain::Instance().StartMode() != SptMain::E_Normal)
	{
		return;
	}
	if (SptMain::Instance().AppCfg() == 0)
	{
		return;
	}
	str = "\n\n";
	LogReal << str;
	str.Clear();
	file.Path().Set(CN_INFO_FILE_ROOT);
	file.Name().Set("UnitInfo.bin");
	file.Creat();
	str << "½Úµã:" << ApiUnitCfg::Instance().NodeId.Data() << " ";
	str << SptMain::Instance().AppCfg()->hmicfg.DispName << " ";
	str << SptMain::Instance().AppCfg()->hmicfg.FullTypeName << " ";
	str << SptMain::Instance().AppCfg()->hmicfg.FatcoryTypeName << " ";
	str << "\n";
	LogReal << str;
	file.Write(str);
	str.Clear();
#ifdef SYLIX_GZK
	str.Clear();
	Boot0Version().ToStr(str);
	LogReal << str;
	file.Write(str);
	str.Clear();
	UbootVersion().ToStr(str);
	LogReal << str;
	file.Write(str);
	str.Clear();
	MainSysVersion().ToStr(str);
	LogReal << str;
	file.Write(str);
	str.Clear();
	BakSysVersion().ToStr(str);
	LogReal << str;
	file.Write(str);
	str.Clear();
#endif // SYSLIX_GZK
	CmmLiteVersion().ToStr(str);
	LogReal << str;
	file.Write(str);
	str.Clear();
	apiVersion.SetOk(1);
	ApiVersion().ToStr(str);
	LogReal << str;
	file.Write(str);
	str.Clear();
	appVersion.SetOk(1);
	AppVersion().ToStr(str);
	LogReal << str;
	file.Write(str);
	str.Clear();
	LcdVersion().ToStr2(str);
	LogReal << str;
	file.Write(str);
	str.Clear();
	VirLcdVersion().ToStr2(str);
	LogReal << str;
	file.Write(str);
	uint32  arrlen = M_ArrLen(other);
	for (uint32 i = 0; i < arrlen; i++)
	{
		str.Clear();
		other[i].ToStr2(str);
		LogReal << str;
		file.Write(str);
	}
	file.Encry(58);
	file.Close();
	//file.Decry(58);
}
#ifdef WIN32_SIM
void spt::ApiVersionInfo::UpdateInfo()
{

}
#endif

ApiVersionInfo& spt::ApiVersionInfo::Instance()
{
	static ApiVersionInfo inst;
	return inst;
}

spt::ApiVersionInfo::ApiVersionInfo()
{
	apiVersion.progOk = 0x5a5a5a5aa5a5a5a5;
	apiVersion.preamble = 0x12fa990;
	apiVersion.major = 0;
	apiVersion.minor = 94;
	apiVersion.reversion = 3;
	StrNCpy(apiVersion.publisher, "fengzhanhua", sizeof(apiVersion.publisher));
	StrNCpy(apiVersion.programName, "Software Platform", sizeof(apiVersion.programName));
	apiVersion.binSize = 0;
	apiVersion.fileSize = 0;
	SalDateStamp date;
	date.FromStrBuild(__DATE__, __TIME__);
	apiVersion.datetimeus = date.Us();
	apiVersion.crc = 0;
	lcdVersion.SetName("LCD");
	virlcdVersion.SetName("VIRLCD");
}
