#include "InstResource.h"

ApiIedToolsCascadeWnd InstIedToolsInfoView[] =
{
	{"ģ����"},
	{"������ֵ"},
	{EndOfInst}
};
ApiIedToolsCascadeWnd InstIedToolsOperatorFirstMenu[] =
{
	{"��Ϣ�鿴",0,InstIedToolsInfoView,0,0},
	{"�����ѯ"},
	{"װ������",0,InstIedToolsInfoView,0,0},
	{EndOfInst}
};
/// <summary>
/// ���˵����ҽ��ܹ���һ����Ŀ
/// </summary>
ApiIedToolsCascadeWnd InstIedToolsOperatorRootMenu[] =
{
	{"����Ա���˵�",InstIedToolsMenuEnterFunc,InstIedToolsOperatorFirstMenu,0,0},
	{EndOfInst}
};

bool8 InstIedToolsMenuEnterFunc(ApiIedToolsCascadeWnd* Wnd)
{
	return 1;
}
