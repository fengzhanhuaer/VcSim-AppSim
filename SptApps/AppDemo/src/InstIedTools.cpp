#include "InstResource.h"

bool8 InstIedToolsMenuEnterFunc(ApiIedToolsCascadeWnd* Wnd)
{
	String100B Id, DefId, Pw;
	DefId = "UsrName";
	ApiIedToolsDialog askIdWnd("����������", 1 * MsTimer::Mt1Minute);
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
	{"������"},
	{"ֱ����"},
	{EndOfInst}
};
ApiIedToolsCascadeWnd InstIedToolsProtSetView[] =
{
	{"������"},
	{"��ֵ��ֵ"},
	{EndOfInst}
};
ApiIedToolsCascadeWnd InstIedToolsInfoView[] =
{
	{"ģ����",0,InstIedToolsAnglogView,0,0},
	{"������ֵ",0,InstIedToolsProtSetView,0,0},
	{EndOfInst}
};
ApiIedToolsCascadeWnd InstIedToolsProtEventView[] =
{
	{"���ϱ���"},
	{"��Ϊ����"},
	{"�澯����"},
	{EndOfInst}
};
ApiIedToolsCascadeWnd InstIedToolsEventView[] =
{
	{"��������",0,InstIedToolsProtEventView,0,0},
	{"���ϱ���"},
	{"�澯����"},
	{EndOfInst}
};
ApiIedToolsCascadeWnd InstIedToolsFactoryDebugView[] =
{
	{"װ����Ϣ",0,ViewUnitInfo,0,0},
	{EndOfInst}
};
ApiIedToolsCascadeWnd InstIedToolsDebugView[] =
{
	{"ָʾ�Ƶ���"},
	{"���ڵ���"},
	{"���ҵ���",0,InstIedToolsFactoryDebugView,0,0},
	{EndOfInst}
};
ApiIedToolsCascadeWnd InstIedToolsUnitSetView[] =
{
	{"ʱ������"},
	{"��������"},
	{EndOfInst}
};
ApiIedToolsCascadeWnd InstIedToolsOperatorFirstMenu[] =
{
	{"��Ϣ�鿴",0,InstIedToolsInfoView,0,0},
	{"�����ѯ",0,InstIedToolsEventView,0,0},
	{"����",InstIedToolsMenuEnterFunc,InstIedToolsDebugView,InstIedToolsMenuExitFunc,0},
	{"װ������",0,InstIedToolsUnitSetView,0,0},
	{EndOfInst}
};
/// <summary>
/// ���˵����ҽ��ܹ���һ����Ŀ
/// �����ڿͻ�������ǰ��������Ƿ���ʾ�Ӵ���
/// </summary>
ApiIedToolsCascadeWnd InstIedToolsOperatorRootMenu[] =
{
	{"����Ա���˵�",0,InstIedToolsOperatorFirstMenu,0,0},
	{EndOfInst}
};



