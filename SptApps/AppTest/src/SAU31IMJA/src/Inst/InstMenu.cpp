#include "InstResource.h"
IsOkMenuFunction nullMenu = 0;
uint32 MenuDispDisp = 1;
uint32 MenuDispUnDisp = 0;
// 厂家调试显示设置
uint32 MenuDispDbgDisp = 0;
uint32 MenuDispDbgIn = 0;


ApiMenu menuAnaView[] =
{
	{"模拟量基波信息"         , EnterAnaJMenu   , ViewAnglog   ,ExitAnaJMenu},
	{"模拟量积分信息"         , EnterAnaMenu    , ViewAnglog   ,ExitAnaMenu},
	{"频率信息"            , EnterAnaFrMenu  , ViewFrlog    ,ExitAnaFrMenu},
	//{"谐波信息"            , ViewAnglog},
	{"直流量信息"           , ViewDclog},
	{EndOfInst}
};

ApiMenu menuSwitchView[] =
{
	{"硬开入",         ViewDiStatus},
	{"硬开出",         ViewDoStatus},
	{"GOOSE开入",     ViewGoInStatus},
	{"GOOSE开出",     ViewGoOutStatus},
	{"指示灯",         ViewLedStatus},
	{"双点遥信",        ViewDpiStatus},
	//	{"虚遥信",         ViewFlagStatus},
		{EndOfInst}
};

ApiMenu menuDevView[] =
{
	{"板卡信息",                ViewDevlog},
#if(CN_DEV_CPU1)
	{"CPU 1x板光口信息",        ViewOpt1log},
#endif
	{"CPU 2X板光口信息",        ViewOpt2log},
	{EndOfInst}
};
ApiMenu menuCcdView[] =
{
#if(CN_DEV_CPU1)
	{"SV订阅",          DispCcdSvSub},
#endif
	{"SV发布",          DispCcdSvPub},
	{"GOOSE订阅",       DispCcdGooseSub},
	{"GOOSE发布",       DispCcdGoosePub},
	//	{"配置下装状态",     DispCcdToFPGA},
		{EndOfInst}
};
ApiMenu menuEventStatusView[] =
{
	{"GOOSE命令状态",     ViewActStatus},
	{"告警状态",          ViewWarnStatus},
	{"自检状态",          ViewChekStatus},
	{EndOfInst}
};


ApiMenu menuStatusView[] =
{
	{"状态监视",menuDevView},
	{"订阅信息",menuCcdView},
	{"事项状态",menuEventStatusView},
	{EndOfInst}
};
ApiMenu menuEventDiView[] =
{
	{"单点SOE",       DispDiEvent},
	{"双点SOE",       DispDpiEvent},
	{EndOfInst}
};
ApiMenu menuEventView[] =
{
	{"GOOSE命令",     DispActEvent},
	{"告警事项",        DispWarnEvent},
	{"自检事项",        DispChekEvent},
	{"运行事项",        DispRunEvent},
	{"操作事项",        DispOptEvent},
	{"硬开入SOE",      menuEventDiView},
	{"硬开出SOE",      DispDoEvent},
	{"GOOSE开入SOE",  DispGoInEvent},
	{"GOOSE开出SOE",  DispGoOutEvent},
	{"指示灯SOE",      DispLedEvent},
	//	{"虚遥信SOE",      DispFlagEvent},
		{EndOfInst}
};
ApiMenu menuSptParaDsp[] =
{
	{"开入参数"  ,    DispProtSetDI},
	{"直流参数"  ,    DispProtSetDC},
	{"模拟量参数",    DispProtSetSam},
	{"功能参数"  ,    DispProtSetFun},
	{"直流量校准系数",  DispProtSetDcCoe},
	{"模拟量校准系数",  DispProtSetAmCoe},
	{"模拟量直流补偿",  DispProtSetDcBcCoe},
	{"模拟量相位补偿",  DispProtSetAngCoe},
	{"网络参数",  DispEthnetPara},
	{EndOfInst}
};
ApiMenu menuSptParaSet[] =
{
	{"开入参数"  ,       EditProtSetDI},
	{"直流参数"  ,       EditProtSetDC},
	{"模拟量参数",       EditProtSetSam},
	{"功能参数"  ,       EditProtSetFun},
	{"直流量校准系数",        EditProtSetDcCoe,&MenuDispDbgDisp},
	{"模拟量直流补偿",        EditProtSetDcBcCoe,&MenuDispDbgDisp},
	{"模拟量校准系数",        EditProtSetAmCoe,&MenuDispDbgDisp},
	{"模拟量相位补偿",        EditProtSetAngCoe,&MenuDispDbgDisp},
	{EndOfInst}
};
ApiMenu menuSptInfo[] =
{
	{"平台状态信息",ViewSptWarnStatus},
	{"负载信息",    DispTaskLoadInfo},
	{"周期信息",    DispTaskPeriodInfo},
	{"进程通信状态",HmiSptCmmState},
	{"清空统计信息",ClearTaskRunCalInfo},
	{EndOfInst}
};
ApiMenu menuSptInter[] =
{
	{"内部记录"  ,        DispPrvtSoeEvent},
	{"内部操作"  ,        DispPrvtOptEvent},
	{"内部信息",          ViewInterlog},
	{"平台信息",          menuSptInfo},
	{EndOfInst}
};
ApiMenu menuProgramUpdate[] =
{
	{"操作系统升级",OsUpdate},
	{"Boot0升级",Boot0Update},
	{"UBoot升级",UbootUpdate},
	{"CPU板FPGA1升级",UpdateFpga1},
#if(CN_DEV_CPU1)
	{"CPU板FPGA2升级",UpdateFpga2},
#endif
	{EndOfInst}
};
ApiMenu menuProgramUpdate1[] =
{
	{"操作系统升级",OsUpdate1},
	{"Boot0升级",Boot0Update1},
	{"UBoot升级",UbootUpdate1},
	{EndOfInst}
};
ApiMenu menuProgramUpdateRoot[] =
{
	{"从sdcard0升级",menuProgramUpdate},
	{"从sd卡(sdcard1)升级",menuProgramUpdate1},
	{EndOfInst}
};
ApiMenu menuFileFormat[] =
{
	{"格式化系统盘",FormatSysCard},
	{"格式化数据盘",FormatDataCard},
	{EndOfInst}
};
ApiMenu menuFileTrans[]
{
	{"发送用户配置",HmiSendFile2SubBoard},
	{EndOfInst}
};
ApiMenu menuBakup[] =
{
	{"FLASH备份",FlashBak},
	{EndOfInst}
};
ApiMenu menuRestore[] =
{
	{"FLASH参数还原",RestoreFlashPara},
	{EndOfInst}
};
ApiMenu menuSptTools[] =
{
	{"程序升级",menuProgramUpdateRoot},
	{"文件系统",menuFileFormat},
	{"文件传输",menuFileTrans},
	{"备份功能",menuBakup},
	//{"还原功能",menuRestore},
	{"加载日志开关",UpdateLogCfg},
	{EndOfInst}
};

ApiMenu menuAdjustAnaAuto[] =
{
	{"直流补偿自动校准",EnterAnaMenu,AutoAnaDcParaSet,EnterAnaMenu},
	{"校准系数自动校准",EnterAnaJMenu,AutoAnaAmParaSet,ExitAnaJMenu},
	{"相位补偿自动校准",EnterAnaJMenu,AutoAnaAngParaSet,ExitAnaJMenu},
	{EndOfInst}
};

ApiMenu menuAdjustAnaManual[] =
{
	{"直流补偿手动校准",EnterAnaMenu,EditAnaDcParaSet,EnterAnaMenu},
	{"校准系数手动校准",EnterAnaJMenu,EditAnaAmParaSet,ExitAnaJMenu},
	{"相位补偿手动校准",EnterAnaJMenu,EditAnaAngParaSet,ExitAnaJMenu},
	{EndOfInst}
};

ApiMenu menuAppAdjustAna[] =
{
	{"交流量自动校准",menuAdjustAnaAuto},
	{"交流量手动校准",menuAdjustAnaManual},
	{EndOfInst}
};
ApiMenu menuAppAdjustDc[] =
{
	{"直流量自动校准",AutoDcParaSet},
	{"直流量手动校准",EditDcParaSet},
	{EndOfInst}
};
ApiMenu menuAppClearEvent[] =
{
	{"清除GOOSE命令事项",ClaerActEvent},
	{"清除告警事项",ClaerAlmEvent},
	{"清除自检事项",ClaerChkEvent},
	{"清除硬开入SOE事项",ClaerDiSoe},
	{"清除硬开出SOE事项",ClaerDoSoe},
	{"清除GOOSE开入SOE事项",ClaerGoInSoe},
	{"清除GOOSE开出SOE事项",ClaerGoOutSoe},
	{"清除指示灯SOE事项",ClaerLedSoe},
	{"清除双点遥信SOE事项",ClaerDpiSoe},
	//	{"清除虚遥信SOE事项",ClaerFlagSoe},
		{EndOfInst}
};
ApiMenu menuAppClearInterEvent[] =
{
	{"清除所有事项",ClaerAllEvent},
	{"清除运行事项",ClaerRunEvent},
	{"清除操作事项",ClaerOptEvent},
	{"清除内部事项",ClaerPrvtSoeEvent},
	{"清除内部操作",ClaerPrvtOptEvent},
	//	{"清除虚遥信SOE事项",ClaerFlagSoe},
		{EndOfInst}
};

ApiMenu menuAppDefaultPara[] =
{
	{"所有参数初始化",DefaultAllPara},
	{"开入参数初始化",DefaultDiPara},
	{"直流参数初始化",DefaultDcPara},
	{"模拟量参数初始化",DefaultAnaPara},
	{"功能参数初始化",DefaultFunPara},
	{"直流量校准系数初始化",DefaultDcCoePara},
	{"模拟量校准系数初始化",DefaultAmCoePara},
	{"模拟量直流补偿初始化",DefaultDcBcCoePara},
	{"模拟量相位补偿初始化",DefaultAngCoePara},
	{EndOfInst}
};
ApiMenu menuSjyExportMenu[] =
{
	{"用户登录",ExportUserLogSjRecord},
	{"用户管理",ExportUserAdmSjRecord},
	{"控制类",     ExportControlSjRecord},
	{EndOfInst}
};
ApiMenu menuEthnet[] =
{
	{"以太网参数设置",EditEthnetPara},
	{"以太网参数导入",AppEthnetPara},
	{EndOfInst}
};
ApiMenu menuFactoryDebug[] =
{
	{"交流模拟量校准",menuAppAdjustAna},
	{"直流模拟量校准",menuAppAdjustDc},
	{"清除记录",menuAppClearEvent},
	{"清除记录(厂家)",menuAppClearInterEvent,&MenuDispDbgDisp},
	{"参数初始化",menuAppDefaultPara,&MenuDispDbgDisp},
	{"平台工具",    menuSptTools,&MenuDispDbgDisp},
	{"以太网设置",  menuEthnet,&MenuDispDbgDisp},
	{"导出审计记录",menuSjyExportMenu,&MenuDispDbgDisp},
	{EndOfInst}
};
ApiMenu menuUnitDebug[] =
{
#if(CN_DEV_CPU1)
	{"指示灯调试",HmiLedFlowWaterSim},
#endif
	{"GOOSE单点出口调试",HmiGooseOutSSim},
	{"GOOSE双点出口调试",HmiGooseOutDSim},
	{"GOOSE模拟量调试",HmiGooseOutDcSim},
	{"常规出口调试",HmiDoOutSim},
	{"厂家调试",EnterFactDebugMode,menuFactoryDebug,ExitFactDebugMode,&MenuDispDisp},
	{EndOfInst}
};
#if 0
ApiMenu menuPrint[] =
{
	{"打印全部事项",PrintAllEvent2Txt},
	{EndOfInst}
};
#endif
ApiMenu menuInfoView[] =
{
	{"模拟量信息",menuAnaView},
	{"开关量信息",menuSwitchView},
	{"状态信息",menuStatusView},
	{"事项记录",menuEventView},
	{"参数信息",menuSptParaDsp},
	{"装置信息",ViewPublicVersion},
	{EndOfInst}
};
ApiMenu AppUnitSetMenu[] =
{
	//{"时间设置",  HmiSetSystemDate},
	{EndOfInst}
};
ApiMenu AppOperatorMenu[] =
{
	{"用户设置",LcdOperUsrParaLogIn,menuSptParaSet,NULL,&MenuDispDisp},
#if(CN_DEV_CPU1)
	{"装置设置",LcdOperUsrDevSetLogIn,AppUnitSetMenu,NULL,&MenuDispDisp},
#endif
	{"装置调试",EnterDebugMode,    menuUnitDebug,ExitDebugMode,&MenuDispDisp},
	{"厂家查看",menuSptInter,&MenuDispDbgDisp},
#if 0
	{"打印",      menuPrint},
#endif
	{EndOfInst}
};
ApiMenu menuSjyViewMenu[] =
{
	{"用户登录",ViewUserLogSjRecord},
	{"用户管理",ViewUserAdmSjRecord},
	{"控制类",     ViewControlSjRecord},
	{EndOfInst}
};
ApiMenu menuSjyMenu[] =
{
	{"查看记录",menuSjyViewMenu},
	{"修改密码",UsrChangePasswordMenu},
	{EndOfInst}
};
ApiMenu menuGlyChangPwMenu[] =
{
	{"修改其他用户密码",GlyChangeUsrPasswordMenu},
	{"修改当前帐号密码",UsrChangePasswordMenu},
	{EndOfInst}
};
ApiMenu menuGlyCreatUserMenu[] =
{
	{"创建操作用户",GlyCreatUsr},
	{"创建审计用户",GlyCreatSjy},
	{"创建管理用户",GlyCreatGly},
	{EndOfInst}
};
ApiMenu menuGlyMenu[] =
{
	{"查看用户",ViewAccountInfo},
	{"创建用户",menuGlyCreatUserMenu},
	{"删除用户",GlyDeleteUsr},
	{"停用用户",GlyStopUsr},
	{"启用用户",GlyEnableUsr},
	{"解锁用户",GlyUnLockUsr},
	{"修改密码",GlyChangeUsrPasswordMenu},
	{"权限编辑",GlyEditPrioUsr},
	{"设置"    ,GlyEditAccountPara},
	{EndOfInst}
};
ApiMenu AppFirstMenu[] =
{
	{"信息查看"  ,menuInfoView},
	{"操作员功能",LcdOperLogIn,AppOperatorMenu,LcdExitAccount,&MenuDispDisp},
	{"审计员功能",LcdComptrollerLogIn,menuSjyMenu,LcdExitAccount,&MenuDispDisp},
	{"管理员功能",LcdMngLogIn,menuGlyMenu,LcdExitAccount,&MenuDispDisp},
	{EndOfInst}
};
//必须是级联菜单
ApiMenu AppRootMenu[] =
{
	{"根菜单",AppFirstMenu},
	{EndOfInst}
};
