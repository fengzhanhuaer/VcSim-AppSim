#include "ApiProject.h"
using namespace spt;

spt::ApiHmiGridWnd::ApiHmiGridWnd()
	:ApiHmiGridWnd(0)
{

}

spt::ApiHmiGridWnd::ApiHmiGridWnd(HmiGridWndUpdateData UpdateData)
{
	SetRect(HmiMenuService::Instance().Rect());
	updateData = UpdateData;
}

void spt::ApiHmiGridWnd::SetInfo(const char* Title, uint32 crc, uint32 crcLen)
{
	SetTitle(Title);
	SetCrc(crc, crcLen);
}

void spt::ApiHmiGridWnd::SetColTitle(const char* Title1, const char* Title2, const char* Title3, const char* Title4, const char* Title5, const char* Title6, const char* Title7, const char* Title8, const char* Title9, const char* Title10)
{
	HmiGridWnd::SetColTitle(Title1, Title2, Title3, Title4, Title5, Title6, Title7, Title8, Title9, Title10);
}

struct HmiGridWndDataMapRow* spt::ApiHmiGridWnd::CreatRow()
{
	if (map.rowNum < M_ArrLen(map.row))
	{
		map.row[map.rowNum].isEnable = 1;
		return &map.row[map.rowNum++];
	}
	return 0;
}

int32 spt::ApiHmiGridWnd::Show()
{
	return HmiGridWnd::Show();
}

int32 spt::ApiHmiGridWnd::Edit()
{
	return HmiGridWnd::Edit();
}

bool8 spt::ApiHmiGridWnd::IsEditData()
{
	return isEditData;
}

bool8 spt::ApiHmiGridWnd::IsDataChange()
{
	return isDataChange;
}
