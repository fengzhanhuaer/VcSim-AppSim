#include "ApiProject.h"
using namespace spt;

void spt::ApiHmiTextWnd::SetTitle(const char* Title)
{
	HmiTextWnd::SetInfo(Title);
}

void spt::ApiHmiTextWnd::SetTitle(const char* Title, uint32 TotalPage)
{
	HmiTextWnd::SetInfo(Title, 0, 0, 0, TotalPage);
}

void spt::ApiHmiTextWnd::SetTotalPage(uint32 TotalPage)
{
	HmiTextWnd::SetTotalPage(TotalPage);
}

uint32 spt::ApiHmiTextWnd::MaxPageCache()
{
	return CN_Max_WndCell;
}

void spt::ApiHmiTextWnd::SetPage(uint32 Page, const char* Text)
{
	HmiTextWnd::SetPage(Page, Text);
}

spt::ApiHmiTextWnd::ApiHmiTextWnd(DispType Mode, UpdateHmiTextWnd UpdateFunction)
	:HmiTextWnd(Mode)
{
	SetRect(HmiMenuService::Instance().Rect());
	updateFunc = UpdateFunction;
}

int32 spt::ApiHmiTextWnd::Show()
{
	return HmiTextWnd::Show();
}
