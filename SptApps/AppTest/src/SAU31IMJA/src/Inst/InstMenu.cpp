#include "InstResource.h"
IsOkMenuFunction nullMenu = 0;
uint32 MenuDispDisp = 1;
uint32 MenuDispUnDisp = 0;
// ���ҵ�����ʾ����
uint32 MenuDispDbgDisp = 0;
uint32 MenuDispDbgIn = 0;


ApiMenu menuAnaView[] =
{
	{"ģ����������Ϣ"         , EnterAnaJMenu   , ViewAnglog   ,ExitAnaJMenu},
	{"ģ����������Ϣ"         , EnterAnaMenu    , ViewAnglog   ,ExitAnaMenu},
	{"Ƶ����Ϣ"            , EnterAnaFrMenu  , ViewFrlog    ,ExitAnaFrMenu},
	//{"г����Ϣ"            , ViewAnglog},
	{"ֱ������Ϣ"           , ViewDclog},
	{EndOfInst}
};

ApiMenu menuSwitchView[] =
{
	{"Ӳ����",         ViewDiStatus},
	{"Ӳ����",         ViewDoStatus},
	{"GOOSE����",     ViewGoInStatus},
	{"GOOSE����",     ViewGoOutStatus},
	{"ָʾ��",         ViewLedStatus},
	{"˫��ң��",        ViewDpiStatus},
	//	{"��ң��",         ViewFlagStatus},
		{EndOfInst}
};

ApiMenu menuDevView[] =
{
	{"�忨��Ϣ",                ViewDevlog},
#if(CN_DEV_CPU1)
	{"CPU 1x������Ϣ",        ViewOpt1log},
#endif
	{"CPU 2X������Ϣ",        ViewOpt2log},
	{EndOfInst}
};
ApiMenu menuCcdView[] =
{
#if(CN_DEV_CPU1)
	{"SV����",          DispCcdSvSub},
#endif
	{"SV����",          DispCcdSvPub},
	{"GOOSE����",       DispCcdGooseSub},
	{"GOOSE����",       DispCcdGoosePub},
	//	{"������װ״̬",     DispCcdToFPGA},
		{EndOfInst}
};
ApiMenu menuEventStatusView[] =
{
	{"GOOSE����״̬",     ViewActStatus},
	{"�澯״̬",          ViewWarnStatus},
	{"�Լ�״̬",          ViewChekStatus},
	{EndOfInst}
};


ApiMenu menuStatusView[] =
{
	{"״̬����",menuDevView},
	{"������Ϣ",menuCcdView},
	{"����״̬",menuEventStatusView},
	{EndOfInst}
};
ApiMenu menuEventDiView[] =
{
	{"����SOE",       DispDiEvent},
	{"˫��SOE",       DispDpiEvent},
	{EndOfInst}
};
ApiMenu menuEventView[] =
{
	{"GOOSE����",     DispActEvent},
	{"�澯����",        DispWarnEvent},
	{"�Լ�����",        DispChekEvent},
	{"��������",        DispRunEvent},
	{"��������",        DispOptEvent},
	{"Ӳ����SOE",      menuEventDiView},
	{"Ӳ����SOE",      DispDoEvent},
	{"GOOSE����SOE",  DispGoInEvent},
	{"GOOSE����SOE",  DispGoOutEvent},
	{"ָʾ��SOE",      DispLedEvent},
	//	{"��ң��SOE",      DispFlagEvent},
		{EndOfInst}
};
ApiMenu menuSptParaDsp[] =
{
	{"�������"  ,    DispProtSetDI},
	{"ֱ������"  ,    DispProtSetDC},
	{"ģ��������",    DispProtSetSam},
	{"���ܲ���"  ,    DispProtSetFun},
	{"ֱ����У׼ϵ��",  DispProtSetDcCoe},
	{"ģ����У׼ϵ��",  DispProtSetAmCoe},
	{"ģ����ֱ������",  DispProtSetDcBcCoe},
	{"ģ������λ����",  DispProtSetAngCoe},
	{"�������",  DispEthnetPara},
	{EndOfInst}
};
ApiMenu menuSptParaSet[] =
{
	{"�������"  ,       EditProtSetDI},
	{"ֱ������"  ,       EditProtSetDC},
	{"ģ��������",       EditProtSetSam},
	{"���ܲ���"  ,       EditProtSetFun},
	{"ֱ����У׼ϵ��",        EditProtSetDcCoe,&MenuDispDbgDisp},
	{"ģ����ֱ������",        EditProtSetDcBcCoe,&MenuDispDbgDisp},
	{"ģ����У׼ϵ��",        EditProtSetAmCoe,&MenuDispDbgDisp},
	{"ģ������λ����",        EditProtSetAngCoe,&MenuDispDbgDisp},
	{EndOfInst}
};
ApiMenu menuSptInfo[] =
{
	{"ƽ̨״̬��Ϣ",ViewSptWarnStatus},
	{"������Ϣ",    DispTaskLoadInfo},
	{"������Ϣ",    DispTaskPeriodInfo},
	{"����ͨ��״̬",HmiSptCmmState},
	{"���ͳ����Ϣ",ClearTaskRunCalInfo},
	{EndOfInst}
};
ApiMenu menuSptInter[] =
{
	{"�ڲ���¼"  ,        DispPrvtSoeEvent},
	{"�ڲ�����"  ,        DispPrvtOptEvent},
	{"�ڲ���Ϣ",          ViewInterlog},
	{"ƽ̨��Ϣ",          menuSptInfo},
	{EndOfInst}
};
ApiMenu menuProgramUpdate[] =
{
	{"����ϵͳ����",OsUpdate},
	{"Boot0����",Boot0Update},
	{"UBoot����",UbootUpdate},
	{"CPU��FPGA1����",UpdateFpga1},
#if(CN_DEV_CPU1)
	{"CPU��FPGA2����",UpdateFpga2},
#endif
	{EndOfInst}
};
ApiMenu menuProgramUpdate1[] =
{
	{"����ϵͳ����",OsUpdate1},
	{"Boot0����",Boot0Update1},
	{"UBoot����",UbootUpdate1},
	{EndOfInst}
};
ApiMenu menuProgramUpdateRoot[] =
{
	{"��sdcard0����",menuProgramUpdate},
	{"��sd��(sdcard1)����",menuProgramUpdate1},
	{EndOfInst}
};
ApiMenu menuFileFormat[] =
{
	{"��ʽ��ϵͳ��",FormatSysCard},
	{"��ʽ��������",FormatDataCard},
	{EndOfInst}
};
ApiMenu menuFileTrans[]
{
	{"�����û�����",HmiSendFile2SubBoard},
	{EndOfInst}
};
ApiMenu menuBakup[] =
{
	{"FLASH����",FlashBak},
	{EndOfInst}
};
ApiMenu menuRestore[] =
{
	{"FLASH������ԭ",RestoreFlashPara},
	{EndOfInst}
};
ApiMenu menuSptTools[] =
{
	{"��������",menuProgramUpdateRoot},
	{"�ļ�ϵͳ",menuFileFormat},
	{"�ļ�����",menuFileTrans},
	{"���ݹ���",menuBakup},
	//{"��ԭ����",menuRestore},
	{"������־����",UpdateLogCfg},
	{EndOfInst}
};

ApiMenu menuAdjustAnaAuto[] =
{
	{"ֱ�������Զ�У׼",EnterAnaMenu,AutoAnaDcParaSet,EnterAnaMenu},
	{"У׼ϵ���Զ�У׼",EnterAnaJMenu,AutoAnaAmParaSet,ExitAnaJMenu},
	{"��λ�����Զ�У׼",EnterAnaJMenu,AutoAnaAngParaSet,ExitAnaJMenu},
	{EndOfInst}
};

ApiMenu menuAdjustAnaManual[] =
{
	{"ֱ�������ֶ�У׼",EnterAnaMenu,EditAnaDcParaSet,EnterAnaMenu},
	{"У׼ϵ���ֶ�У׼",EnterAnaJMenu,EditAnaAmParaSet,ExitAnaJMenu},
	{"��λ�����ֶ�У׼",EnterAnaJMenu,EditAnaAngParaSet,ExitAnaJMenu},
	{EndOfInst}
};

ApiMenu menuAppAdjustAna[] =
{
	{"�������Զ�У׼",menuAdjustAnaAuto},
	{"�������ֶ�У׼",menuAdjustAnaManual},
	{EndOfInst}
};
ApiMenu menuAppAdjustDc[] =
{
	{"ֱ�����Զ�У׼",AutoDcParaSet},
	{"ֱ�����ֶ�У׼",EditDcParaSet},
	{EndOfInst}
};
ApiMenu menuAppClearEvent[] =
{
	{"���GOOSE��������",ClaerActEvent},
	{"����澯����",ClaerAlmEvent},
	{"����Լ�����",ClaerChkEvent},
	{"���Ӳ����SOE����",ClaerDiSoe},
	{"���Ӳ����SOE����",ClaerDoSoe},
	{"���GOOSE����SOE����",ClaerGoInSoe},
	{"���GOOSE����SOE����",ClaerGoOutSoe},
	{"���ָʾ��SOE����",ClaerLedSoe},
	{"���˫��ң��SOE����",ClaerDpiSoe},
	//	{"�����ң��SOE����",ClaerFlagSoe},
		{EndOfInst}
};
ApiMenu menuAppClearInterEvent[] =
{
	{"�����������",ClaerAllEvent},
	{"�����������",ClaerRunEvent},
	{"�����������",ClaerOptEvent},
	{"����ڲ�����",ClaerPrvtSoeEvent},
	{"����ڲ�����",ClaerPrvtOptEvent},
	//	{"�����ң��SOE����",ClaerFlagSoe},
		{EndOfInst}
};

ApiMenu menuAppDefaultPara[] =
{
	{"���в�����ʼ��",DefaultAllPara},
	{"���������ʼ��",DefaultDiPara},
	{"ֱ��������ʼ��",DefaultDcPara},
	{"ģ����������ʼ��",DefaultAnaPara},
	{"���ܲ�����ʼ��",DefaultFunPara},
	{"ֱ����У׼ϵ����ʼ��",DefaultDcCoePara},
	{"ģ����У׼ϵ����ʼ��",DefaultAmCoePara},
	{"ģ����ֱ��������ʼ��",DefaultDcBcCoePara},
	{"ģ������λ������ʼ��",DefaultAngCoePara},
	{EndOfInst}
};
ApiMenu menuSjyExportMenu[] =
{
	{"�û���¼",ExportUserLogSjRecord},
	{"�û�����",ExportUserAdmSjRecord},
	{"������",     ExportControlSjRecord},
	{EndOfInst}
};
ApiMenu menuEthnet[] =
{
	{"��̫����������",EditEthnetPara},
	{"��̫����������",AppEthnetPara},
	{EndOfInst}
};
ApiMenu menuFactoryDebug[] =
{
	{"����ģ����У׼",menuAppAdjustAna},
	{"ֱ��ģ����У׼",menuAppAdjustDc},
	{"�����¼",menuAppClearEvent},
	{"�����¼(����)",menuAppClearInterEvent,&MenuDispDbgDisp},
	{"������ʼ��",menuAppDefaultPara,&MenuDispDbgDisp},
	{"ƽ̨����",    menuSptTools,&MenuDispDbgDisp},
	{"��̫������",  menuEthnet,&MenuDispDbgDisp},
	{"������Ƽ�¼",menuSjyExportMenu,&MenuDispDbgDisp},
	{EndOfInst}
};
ApiMenu menuUnitDebug[] =
{
#if(CN_DEV_CPU1)
	{"ָʾ�Ƶ���",HmiLedFlowWaterSim},
#endif
	{"GOOSE������ڵ���",HmiGooseOutSSim},
	{"GOOSE˫����ڵ���",HmiGooseOutDSim},
	{"GOOSEģ��������",HmiGooseOutDcSim},
	{"������ڵ���",HmiDoOutSim},
	{"���ҵ���",EnterFactDebugMode,menuFactoryDebug,ExitFactDebugMode,&MenuDispDisp},
	{EndOfInst}
};
#if 0
ApiMenu menuPrint[] =
{
	{"��ӡȫ������",PrintAllEvent2Txt},
	{EndOfInst}
};
#endif
ApiMenu menuInfoView[] =
{
	{"ģ������Ϣ",menuAnaView},
	{"��������Ϣ",menuSwitchView},
	{"״̬��Ϣ",menuStatusView},
	{"�����¼",menuEventView},
	{"������Ϣ",menuSptParaDsp},
	{"װ����Ϣ",ViewPublicVersion},
	{EndOfInst}
};
ApiMenu AppUnitSetMenu[] =
{
	//{"ʱ������",  HmiSetSystemDate},
	{EndOfInst}
};
ApiMenu AppOperatorMenu[] =
{
	{"�û�����",LcdOperUsrParaLogIn,menuSptParaSet,NULL,&MenuDispDisp},
#if(CN_DEV_CPU1)
	{"װ������",LcdOperUsrDevSetLogIn,AppUnitSetMenu,NULL,&MenuDispDisp},
#endif
	{"װ�õ���",EnterDebugMode,    menuUnitDebug,ExitDebugMode,&MenuDispDisp},
	{"���Ҳ鿴",menuSptInter,&MenuDispDbgDisp},
#if 0
	{"��ӡ",      menuPrint},
#endif
	{EndOfInst}
};
ApiMenu menuSjyViewMenu[] =
{
	{"�û���¼",ViewUserLogSjRecord},
	{"�û�����",ViewUserAdmSjRecord},
	{"������",     ViewControlSjRecord},
	{EndOfInst}
};
ApiMenu menuSjyMenu[] =
{
	{"�鿴��¼",menuSjyViewMenu},
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
	{"���������û�",GlyCreatUsr},
	{"��������û�",GlyCreatSjy},
	{"���������û�",GlyCreatGly},
	{EndOfInst}
};
ApiMenu menuGlyMenu[] =
{
	{"�鿴�û�",ViewAccountInfo},
	{"�����û�",menuGlyCreatUserMenu},
	{"ɾ���û�",GlyDeleteUsr},
	{"ͣ���û�",GlyStopUsr},
	{"�����û�",GlyEnableUsr},
	{"�����û�",GlyUnLockUsr},
	{"�޸�����",GlyChangeUsrPasswordMenu},
	{"Ȩ�ޱ༭",GlyEditPrioUsr},
	{"����"    ,GlyEditAccountPara},
	{EndOfInst}
};
ApiMenu AppFirstMenu[] =
{
	{"��Ϣ�鿴"  ,menuInfoView},
	{"����Ա����",LcdOperLogIn,AppOperatorMenu,LcdExitAccount,&MenuDispDisp},
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
