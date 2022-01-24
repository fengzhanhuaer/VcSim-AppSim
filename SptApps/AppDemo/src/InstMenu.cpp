#include "InstResource.h"

IsOkMenuFunction nullMenu = 0;
uint32 MenuDispDisp = 1;
uint32 MenuDispUnDisp = 0;

ApiMenu menuProgramUpdate[]
{
	{"����ϵͳ����",OsUpdate},
	{"Boot0����",Boot0Update},
	{"UBoot����",UbootUpdate},
	{"FPGA1����",UpdateFpga1},
	{"FPGA2����",UpdateFpga2},
	{"FPGA3����",UpdateFpga3},
	{EndOfInst}
};
ApiMenu menuProgramUpdate1[]
{
	{"����ϵͳ����",OsUpdate1},
	{"Boot0����",Boot0Update1},
	{"UBoot����",UbootUpdate1},
	{EndOfInst}
};
ApiMenu menuProgramUpdateRoot[]
{
	{"��sdcard0����",menuProgramUpdate},
	{"��sd��(sdcard1)����",menuProgramUpdate1},
	{EndOfInst}
};
ApiMenu menuFileFormat[]
{
	{"��ʽ��ϵͳ��",FormatSysCard},
	{"��ʽ��������",FormatDataCard},
	{EndOfInst}
};
ApiMenu menuFileTrans[]
{
	{"���������ļ�",HmiSendFile2SubBoard},
	{EndOfInst}
};
ApiMenu menuBakup[]
{
	{"FLASH����",FlashBak},
	{EndOfInst}
};
ApiMenu menuRestore[]
{
	{"FLASH������ԭ",RestoreFlashPara},
	{EndOfInst}
};
ApiMenu menuSptTools[]
{
	{"��������",menuProgramUpdateRoot},
	{"�ļ�ϵͳ",menuFileFormat},
	{"�ļ�����",menuFileTrans},
	{"���ݹ���",menuBakup},
	{"��ԭ����",menuRestore},
	{"������־����",UpdateLogCfg},
	{EndOfInst}
};
ApiMenu menuSptInfo[]
{
	{"ƽ̨״̬��Ϣ",ViewSptWarnStatus},
	{"������Ϣ",DispTaskLoadInfo},
	{"������Ϣ",DispTaskPeriodInfo},
	{"����ͨ��״̬",HmiSptCmmState},
	{"���ͳ����Ϣ",ClearTaskRunCalInfo},
	{EndOfInst}
};
ApiMenu menuSptDebug[] =
{
	{"ƽ̨����",menuSptTools},
	{"ƽ̨��Ϣ",menuSptInfo},
	{"Ӧ���������",AppEthnetPara},
	{EndOfInst}
};
ApiMenu menuAppDebug[] =
{
	{"LED�Ƶ���",HmiLedFlowWaterSim},
	{"Ĭ�϶�ֵ",DefaultProtSetPara},
	{"�ֶ�У׼",EditPtctParaSet},
	{EndOfInst}
};
ApiMenu menuFactoryDebug[] =
{
	{"ƽ̨����",menuSptDebug},
	{"Ӧ�õ���",menuAppDebug},
	{EndOfInst}
};
ApiMenu menuUnitDebug[] =
{
	{"GOOSE���ڵ���",HmiDoOutSim},
	{"������ڵ���",HmiGooseOutSim},
	{"���ҵ���",menuFactoryDebug},
	{EndOfInst}
};

ApiMenu menuInfoView[] =
{
	{"ģ������Ϣ",ViewAnglog},
	{"�汾��Ϣ",ViewPrivateVersion},
	{"�澯״̬",ViewWarnStatus},
	{"�澯��ϸ״̬",ViewWarnDetailedStatus},
	{"�鿴������ֵ",DispProtSet},
	{"�鿴PTCTϵ��",DispPtctParaSet},
	{EndOfInst}
};
ApiMenu menuEventView[] =
{
	{"��������",DispActReport},
	{"�澯����",DispWarnEvent},
	{EndOfInst}
};
ApiMenu menuPrint[] =
{
	{"��ӡȫ������",PrintAllEvent2Txt},
	{EndOfInst}
};
ApiMenu menuSjyViewMenu[] =
{
	{"�û���¼",ViewUserLogSjRecord},
	{EndOfInst}
};
ApiMenu menuSjyExportMenu[] =
{
	{"�û���¼",ExportUserLogSjRecord},
	{EndOfInst}
};
ApiMenu menuSjyMenu[] =
{
	{"�鿴��¼",menuSjyViewMenu},
	{"������¼",menuSjyExportMenu},
	{"�޸�����",UsrChangePasswordMenu},
	{EndOfInst}
};
ApiMenu menuGlyChangPwMenu[] =
{
	{"�޸������û�����",GlyChangeUsrPasswordMenu},
	{"�޸ĵ�ǰ�ʺ�����",UsrChangePasswordMenu},
	{EndOfInst}
};
ApiMenu menuGlyCreatUserMenu[] =
{
	{"���������˺�",GlyCreatUsr},
	{"���������˺�",GlyCreatGly},
	{EndOfInst}
};
ApiMenu menuGlyMenu[] =
{
	{"�鿴�˺�",ViewAccountInfo},
	{"�����˺�",menuGlyCreatUserMenu},
	{"ɾ���˺�",GlyDeleteUsr},
	{"ͣ���˺�",GlyStopUsr},
	{"�����˺�",GlyEnableUsr},
	{"�޸�����",GlyChangeUsrPasswordMenu},
	{"Ȩ�ޱ༭",GlyEditPrioUsr},
	{"����",GlyEditAccountPara},
	{EndOfInst}
};
ApiMenu AppUnitSetMenu[] =
{
	{"ʱ������",HmiSetSystemDate},
	{"��̫������",EditEthnetPara},
	{EndOfInst}
};
ApiMenu AppOperatorMenu[] =
{
	{"CeShi",FuncMenuTest},
	{"��Ϣ�鿴",menuInfoView},
	{"�����ѯ",menuEventView},
	{"��ֵ����",EditProtSet},
	{"����",EnterDebugMode,menuUnitDebug,ExitDebugMode},
	{"��ӡ",menuPrint},
	{"װ������",AppUnitSetMenu},
	{EndOfInst}
};
ApiMenu AppFirstMenu[] =
{
	{"����Ա����",AppOperatorMenu},
	{"���Ա����",LcdComptrollerLogIn,menuSjyMenu,LcdExitAccount,&MenuDispDisp},
	{"����Ա����",LcdMngLogIn,menuGlyMenu,LcdExitAccount,&MenuDispDisp},
	{EndOfInst}
};
//�����Ǽ����˵�
ApiMenu AppRootMenu[] =
{
	{"���˵�",AppFirstMenu},
	{EndOfInst}
};