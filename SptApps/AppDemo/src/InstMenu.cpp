#include "InstResource.h"

IsOkMenuFunction nullMenu = 0;
uint32 MenuDispDisp = 1;
uint32 MenuDispUnDisp = 0;

ApiMenu menuProgramUpdate[]
{
	{"操作系统升级",OsUpdate},
	{"Boot0升级",Boot0Update},
	{"UBoot升级",UbootUpdate},
	{"FPGA1升级",UpdateFpga1},
	{"FPGA2升级",UpdateFpga2},
	{"FPGA3升级",UpdateFpga3},
	{EndOfInst}
};
ApiMenu menuProgramUpdate1[]
{
	{"操作系统升级",OsUpdate1},
	{"Boot0升级",Boot0Update1},
	{"UBoot升级",UbootUpdate1},
	{EndOfInst}
};
ApiMenu menuProgramUpdateRoot[]
{
	{"从sdcard0升级",menuProgramUpdate},
	{"从sd卡(sdcard1)升级",menuProgramUpdate1},
	{EndOfInst}
};
ApiMenu menuFileFormat[]
{
	{"格式化系统盘",FormatSysCard},
	{"格式化数据盘",FormatDataCard},
	{EndOfInst}
};
ApiMenu menuFileTrans[]
{
	{"发送配置文件",HmiSendFile2SubBoard},
	{EndOfInst}
};
ApiMenu menuBakup[]
{
	{"FLASH备份",FlashBak},
	{EndOfInst}
};
ApiMenu menuRestore[]
{
	{"FLASH参数还原",RestoreFlashPara},
	{EndOfInst}
};
ApiMenu menuSptTools[]
{
	{"程序升级",menuProgramUpdateRoot},
	{"文件系统",menuFileFormat},
	{"文件传输",menuFileTrans},
	{"备份功能",menuBakup},
	{"还原功能",menuRestore},
	{"加载日志开关",UpdateLogCfg},
	{EndOfInst}
};
ApiMenu menuSptInfo[]
{
	{"平台状态信息",ViewSptWarnStatus},
	{"负载信息",DispTaskLoadInfo},
	{"周期信息",DispTaskPeriodInfo},
	{"进程通信状态",HmiSptCmmState},
	{"清空统计信息",ClearTaskRunCalInfo},
	{EndOfInst}
};
ApiMenu menuSptDebug[] =
{
	{"平台工具",menuSptTools},
	{"平台信息",menuSptInfo},
	{"应用网络参数",AppEthnetPara},
	{EndOfInst}
};
ApiMenu menuAppDebug[] =
{
	{"LED灯调试",HmiLedFlowWaterSim},
	{"默认定值",DefaultProtSetPara},
	{"手动校准",EditPtctParaSet},
	{EndOfInst}
};
ApiMenu menuFactoryDebug[] =
{
	{"平台调试",menuSptDebug},
	{"应用调试",menuAppDebug},
	{EndOfInst}
};
ApiMenu menuUnitDebug[] =
{
	{"GOOSE出口调试",HmiDoOutSim},
	{"常规出口调试",HmiGooseOutSim},
	{"厂家调试",menuFactoryDebug},
	{EndOfInst}
};

ApiMenu menuInfoView[] =
{
	{"模拟量信息",ViewAnglog},
	{"版本信息",ViewPrivateVersion},
	{"告警状态",ViewWarnStatus},
	{"告警详细状态",ViewWarnDetailedStatus},
	{"查看保护定值",DispProtSet},
	{"查看PTCT系数",DispPtctParaSet},
	{EndOfInst}
};
ApiMenu menuEventView[] =
{
	{"动作报告",DispActReport},
	{"告警事项",DispWarnEvent},
	{EndOfInst}
};
ApiMenu menuPrint[] =
{
	{"打印全部事项",PrintAllEvent2Txt},
	{EndOfInst}
};
ApiMenu menuSjyViewMenu[] =
{
	{"用户登录",ViewUserLogSjRecord},
	{EndOfInst}
};
ApiMenu menuSjyExportMenu[] =
{
	{"用户登录",ExportUserLogSjRecord},
	{EndOfInst}
};
ApiMenu menuSjyMenu[] =
{
	{"查看记录",menuSjyViewMenu},
	{"导出记录",menuSjyExportMenu},
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
	{"创建操作账号",GlyCreatUsr},
	{"创建管理账号",GlyCreatGly},
	{EndOfInst}
};
ApiMenu menuGlyMenu[] =
{
	{"查看账号",ViewAccountInfo},
	{"创建账号",menuGlyCreatUserMenu},
	{"删除账号",GlyDeleteUsr},
	{"停用账号",GlyStopUsr},
	{"启用账号",GlyEnableUsr},
	{"修改密码",GlyChangeUsrPasswordMenu},
	{"权限编辑",GlyEditPrioUsr},
	{"设置",GlyEditAccountPara},
	{EndOfInst}
};
ApiMenu AppUnitSetMenu[] =
{
	{"时间设置",HmiSetSystemDate},
	{"以太网设置",EditEthnetPara},
	{EndOfInst}
};
ApiMenu AppOperatorMenu[] =
{
	{"CeShi",FuncMenuTest},
	{"信息查看",menuInfoView},
	{"报告查询",menuEventView},
	{"定值整定",EditProtSet},
	{"调试",EnterDebugMode,menuUnitDebug,ExitDebugMode},
	{"打印",menuPrint},
	{"装置设置",AppUnitSetMenu},
	{EndOfInst}
};
ApiMenu AppFirstMenu[] =
{
	{"操作员功能",AppOperatorMenu},
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