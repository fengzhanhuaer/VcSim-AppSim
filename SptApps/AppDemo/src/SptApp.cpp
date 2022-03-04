#include "InstResource.h"

//初始化参数配置，此时参数还未加载，参数不可用
void AppPowerUpStep0()
{
	AppParaPowerUpIni();
	AppCmmPowerUpIni();
}
//初始化一般性IO配置，此时参数已经加载完成，可以根据参数个性化的初始化IO（此时平台功能还未加载，不可进行依赖于平台运行的行为）
//所有的依赖于平台的资源均应在此Step0与Step1中进行
//Step0与Step1的区别是Step0中，所有的参数还未初始化完成，因此参数是不可用的。Step1中参数已经初始化并加载完成，Step1中可以使用参数、定值等信息
void AppPowerUpStep1()
{
	AppDbgPowerUpIni();
	AppEventPowerUpIni();
	AppAngInPowerUpIni();
	AppAngOutPowerUpIni();
	AppHmiLedPowerUpIni();
	AppStateInPowerUpIni();
	AppStateOutPowerUpIni();
	AppSjRecordPowerUpIni();
	AppFwRecordPowerUpIni();
	T860PowerUpIni();
	AppCheckPowerUpIni();
}
struct TaskRunInfo sampLoadnfo;//负载监视
//此时平台已经完成初始化，但是采样中断还未开启，此时可以进行一些采样值，应用层IO初始化、重启事项生成等工作
//61850已经初始化完毕，可以读取一些配置信息
//此函数中不能进行需要进行资源分配的活动，所有对平台依赖资源的配置均应在Setp0与Step1中完成
void AppPowerUpStep2()
{
	SjUsrLogRecord.CreatRecord("SptMain", "操作系统", "应用程序", "上电启动", 0, 0, 0);
#ifdef WIN32_SIM

#elif defined(SYLIX_GZK)
	//检查操作系统校验标志
	if (!ApiVersionInfo::Instance().MainSysVersion().IsProgOk())
	{
		LogErr.Stamp() << "MainSysVersion PowerUp Check err.\n";
	}
	if (!ApiVersionInfo::Instance().BakSysVersion().IsProgOk())
	{
		LogErr.Stamp() << "BakSysVersion PowerUp Check err.\n";
	}
#endif // WIN32_SIM
	sampLoadnfo.SetName("AppSamp");
	sampLoadnfo.ClearLoadInfo();
	sampLoadnfo.Rgs2TaskMonitorRunInfo();
}

//逐点中断
void App1SampPointInt()
{
	sampLoadnfo.RunStart();
	UpdateNorStateIn();
	AppAngSampIn();
	AppFwUpdate();
	sampLoadnfo.RunEnd();
}
void App2SampPointInt()
{


}
void App3SampPointInt()
{


}
extern "C" int main(int argc, char** argv)
{
	LogApp.Stamp() << "Program run into app main.\n";
	ApiVersionInfo::Instance().AppVersion().FillInfo(0, 2, 0, "fengzhanhua", __DATE__, __TIME__);
	//向平台配置应用信息，平台解析启动参数，如果是FactoryMode启动的，平台会解析FactoryMode.cfg并执行相应的操作
	SptMain::Instance().SetAppCfg(&AppRunTimeCfg, argc, argv);
	//初始化参试配置
	AppPowerUpStep0();
	//初始化IO信息
	AppPowerUpStep1();
	//平台功能初始化、启动平台内自有的任务等
	SptMain::Instance().PowerUpIni(0);
	//初始化应用层IO信息，产生重启事项等
	AppPowerUpStep2();
	//所有初始化已经完成，进入平台运行循环，此函数不返回
	SptMain::Instance().Run();
	return  (0);
}
