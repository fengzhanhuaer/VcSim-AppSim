#include "ApiProject.h"
using namespace spt;

void spt::ApiHmiTextWnd::SetTitle(const char* Title)
{
	this->Title().SetTitle(Title);
}

void spt::ApiHmiTextWnd::SetTitle(const char* Title, uint32 TotalPage)
{
	this->Title().SetInfo(Title, 0, 0, 0, TotalPage);
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
	Rect() = HmiMenuService::Instance().Rect();
	updateFunc = UpdateFunction;
}

void spt::ApiHmiTextWnd::Show()
{
	HmiTextWnd::Show();
}
