#include "ApiProject.h"
using namespace spt;

const struct ApiAppCfg* spt::SptMain::AppCfg()
{
	return appCfg;
}

bool8 spt::SptMain::IsHardWare(E_HARDWARE hd)
{
	return appCfg && (appCfg->platform.hardware == hd);
}

bool8 spt::SptMain::IsSoftWare(E_SOFTWARE hd)
{
	return appCfg && (appCfg->platform.software == hd);
}

bool8 spt::SptMain::IsDevice(E_DEVTYPE hd)
{
	return appCfg && (appCfg->platform.devtype == hd);
}

void spt::SptMain::SetAppCfg(struct ApiAppCfg* AppCfg, int argc, char** argv)
{
	appCfg = AppCfg;
	PowerUpDealStartPara(argc, argv);
	SptLogTask::Instance().PowerUpIni(0);
	SpStatusPowerUpIni();
	ApiSysEthNetCfg::Instance().PowerUpIni(0);
	SptDateTask::Instance().PowerUpIni(0);
}

SptMain::E_StartMode spt::SptMain::StartMode()
{
	return startmode;
}

const SalString& spt::SptMain::AppRoot()
{
	return appRoot;
}

SptMain& spt::SptMain::Instance()
{
	static SptMain inst;
	return inst;
}

void spt::SptMain::PowerUpIni(int32 Para)
{
#ifdef WIN32_SIM
	SetProcessRunAt(Task::E_DefCore);
#elif defined(SYLIX_GZK)
	SetProcessRunAt(Task::E_DefCore);
#endif
	ApiUnitCfg::Instance().PowerUpIni(0);
	LogMsg.Stamp() << "Program run into spt SptMain.PowerUpIni.\n";
	SocketEnvStartUp();
	SptT860Info::Instance().PowerUpIni(0);
	SptEventPublishTask::Instance().PowerUpIni(0);
	SalSjRecordDispachTask::Instance().PowerUpIni(0);
	SptSampIntMsgProc::Instance().PowerUpIni(0);
	SptMsInt::Instance().PowerUpIni(0);
	SptSampInt::Instance().PowerUpIni(0);
	HmiMainFramePowerUpIni();
	HmiLcdCmm::Instance().PowerUpIni(0);
	SptSampAppTaskScheduler::Instance().PowerUpIni(0);
	SalParaGroupSaveTask::Instance().PowerUpIni(0);
	SptIoProcess::Instance().PowerUpIni(0);
	DbgServer::Instance().PowerUpIni(0);
	SalUserMng::Instance().PowerUpIni();
	SptAppCmmTask::Instance().PowerUpIni(0);
	SptCheckTask::Instance().PowerUpIni(0);
	SalFwRecordTask::Instance().PowerUpIni(0);
	SptPublicCmmTask::Instance().PowerUpIni(0);
}
void spt::SptMain::Run()
{
	TaskMonitor::Instance().PowerUpIni(0);
	LogMsg.Stamp() << "Program run into SptMain.Run.\n";
	InstObjectRoot::Instance().PowerUpOver(1);
	SimSysStartUp();
	isStartOver = 1;
#if  defined(WIN32_SIM) ||defined(SYLIX_GZK)
	while (1)
	{
		MsSleep(10000);
	}
#elif defined(SYLIX_GZK)
	MsSleep(5000);
#endif
	LogMsg.Stamp() << "Program exit SptMain.Run.\n";
}
bool8 spt::SptMain::IsStartOver()
{
	return isStartOver;
}
void spt::SptMain::PowerUpDealStartPara(int argc, char** argv)
{
	CalcAppCrc(argc, argv);

	if (argc >= 2)
	{
		String100B str;
		str = argv[1];
		if (str == "FactoryMode")
		{
			SptLogTask::Instance().LogCfg().filePrint.SetData(0);
			startmode = E_Factory;
			FactoryModeFormat(0);
		}
		else if (str == "AppRun")
		{
			startmode = E_Normal;
		}
	}
}
void spt::SptMain::CalcAppCrc(int argc, char** argv)
{
	LogReal.Stamp() << "App Start Up Para Num is " << argc << ".Para is ";
	for (int i = 0; i < argc; i++)
	{
		LogReal << argv[i] << " ";
	}
	LogReal << "\n";

	SalFile file;
	file.SetFullName(argv[0]);
	StrNCpy(ApiVersionInfo::Instance().AppVersion().programName, file.Name().Name(), sizeof(ApiVersionInfo::Instance().AppVersion().programName));
	file.Open("rb");
	if (file.IsOpened())
	{
		ApiVersionInfo::Instance().AppVersion().binSize = (uint32)file.Size();
		ApiVersionInfo::Instance().AppVersion().fileSize = (uint32)file.Size();
		ApiVersionInfo::Instance().AppVersion().crc = file.GetCrc();
		appRoot = file.Path().Path();
	}
	else
	{
		appRoot = CN_APPS_ROOT;
	}
	ApiVersionInfo::Instance().UpdateInfo();
}
spt::SptMain::SptMain()
{
	isStartOver = 0;
	appCfg = 0;
	startmode = E_Normal;
}
spt::SptMain::~SptMain()
{
	SocketEnvClearUp();
}

