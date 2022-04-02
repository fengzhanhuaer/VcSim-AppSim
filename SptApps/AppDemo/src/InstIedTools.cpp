#include "InstResource.h"

bool8 InstIedToolsMenuEnterFunc(ApiIedToolsCascadeWnd* Wnd)
{
	String100B Id, DefId, Pw;
	DefId = "UsrName";
	ApiIedToolsDialog askIdWnd("请输入密码", 1 * MsTimer::Mt1Minute);
	if (askIdWnd.ShowAskIdPw(DefId, Id, Pw))
	{
		return 0;
	}
	return 1;
}
bool8 InstIedToolsMenuExitFunc(ApiIedToolsCascadeWnd* Wnd)
{
	return 1;
}
int32 ViewUnitInfo(class ApiIedToolsCascadeWnd* wnd, IedToolsCascadeWnd::Flags& flag, IedToolsCascadeWnd::IedToolsWndPara& Para)
{


	return 0;
}
ApiIedToolsCascadeWnd InstIedToolsAnglogView[] =
{
	{"交流量"},
	{"直流量"},
	{EndOfInst}
};
ApiIedToolsCascadeWnd InstIedToolsProtSetView[] =
{
	{"控制字"},
	{"数值定值"},
	{EndOfInst}
};
ApiIedToolsCascadeWnd InstIedToolsInfoView[] =
{
	{"模拟量",0,InstIedToolsAnglogView,0,0},
	{"保护定值",0,InstIedToolsProtSetView,0,0},
	{EndOfInst}
};
ApiIedToolsCascadeWnd InstIedToolsProtEventView[] =
{
	{"故障报告"},
	{"行为报告"},
	{"告警事项"},
	{EndOfInst}
};
ApiIedToolsCascadeWnd InstIedToolsEventView[] =
{
	{"保护报告",0,InstIedToolsProtEventView,0,0},
	{"故障报告"},
	{"告警事项"},
	{EndOfInst}
};
ApiIedToolsCascadeWnd InstIedToolsFactoryDebugView[] =
{
	{"装置信息",0,ViewUnitInfo,0,0},
	{EndOfInst}
};
ApiIedToolsCascadeWnd InstIedToolsDebugView[] =
{
	{"指示灯调试"},
	{"出口调试"},
	{"厂家调试",0,InstIedToolsFactoryDebugView,0,0},
	{EndOfInst}
};
ApiIedToolsCascadeWnd InstIedToolsUnitSetView[] =
{
	{"时间设置"},
	{"密码设置"},
	{EndOfInst}
};
ApiIedToolsCascadeWnd InstIedToolsOperatorFirstMenu[] =
{
	{"信息查看",0,InstIedToolsInfoView,0,0},
	{"报告查询",0,InstIedToolsEventView,0,0},
	{"调试",InstIedToolsMenuEnterFunc,InstIedToolsDebugView,InstIedToolsMenuExitFunc,0},
	{"装置设置",0,InstIedToolsUnitSetView,0,0},
	{EndOfInst}
};
/// <summary>
/// 根菜单有且仅能够有一个项目
/// 必须在客户端连接前设置完成是否显示子窗口
/// </summary>
ApiIedToolsCascadeWnd InstIedToolsOperatorRootMenu[] =
{
	{"操作员根菜单",0,InstIedToolsOperatorFirstMenu,0,0},
	{EndOfInst}
};



