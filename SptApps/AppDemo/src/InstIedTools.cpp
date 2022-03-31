#include "InstResource.h"

ApiIedToolsCascadeWnd InstIedToolsInfoView[] =
{
	{"模拟量"},
	{"保护定值"},
	{EndOfInst}
};
ApiIedToolsCascadeWnd InstIedToolsOperatorFirstMenu[] =
{
	{"信息查看",0,InstIedToolsInfoView,0,0},
	{"报告查询"},
	{"装置设置",0,InstIedToolsInfoView,0,0},
	{EndOfInst}
};
/// <summary>
/// 根菜单有且仅能够有一个项目
/// </summary>
ApiIedToolsCascadeWnd InstIedToolsOperatorRootMenu[] =
{
	{"操作员根菜单",InstIedToolsMenuEnterFunc,InstIedToolsOperatorFirstMenu,0,0},
	{EndOfInst}
};

bool8 InstIedToolsMenuEnterFunc(ApiIedToolsCascadeWnd* Wnd)
{
	return 1;
}
