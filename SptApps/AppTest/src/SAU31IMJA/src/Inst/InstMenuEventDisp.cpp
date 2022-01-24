#include"InstResource.h"

int32 UpdateEventHmiTextWnd(class HmiTextWnd& Wnd, uint16 Page, uint16 TotalPage, HmiKey key)
{
	uint32 pageEnd = Min(TotalPage, Page + 10);
	String500B str;
	uint32 page = 0;
	StatusData* record;
	for (uint32 i = Page; i < pageEnd; i++)
	{
		page = TotalPage - i - 1;
		str.Clear();
		record = &HmiViewEventPool.record[page];
		record->toLcdStr(str, 40);
		Wnd.SetPage(i, str.Str());
	}
	return 0;
}

bool8 DispEvent(ApiMenu* Menu, SalEventGroup* Group)
{
	SalDateStamp dateStart, dateEnd;
	dateEnd.Now();
	dateStart.Set(dateEnd.Us() - SalDateStamp::Dt1Day);
	ApiHmiDateEditDialog dig("开始时间", dateStart);
	int32 res = dig.Show();
	// 按键“ESC”可以查看所有事项
	if (res == -1)
	{
		HmiViewEventPool.GetValid(Group, 0x0, (uint64)0xffffffffffffffff, 1);
	}
	else
	{
		dateStart = dig.Stamp();
		ApiHmiDateEditDialog dig2("结束时间", dateEnd);
		dig2.Show();
		dateEnd = dig2.Stamp();
		HmiViewEventPool.GetValid(Group, (uint64)dateStart.Us(), (uint64)dateEnd.Us(), 1);
	}
	if (HmiViewEventPool.validRecordNum == 0)
	{
		ApiWarnDialog dig("该时间段内无记录产生", 0, 0, 0, 0);
		dig.Show();
		return 0;
	}
	ApiHmiTextWnd wnd(HmiTextWnd::E_ScrollPage, UpdateEventHmiTextWnd);
	wnd.SetTitle(Menu->Name(), HmiViewEventPool.validRecordNum);
	wnd.Show();
	return 1;
}
bool8 DispActEvent(ApiMenu* Menu)
{
	DispEvent(Menu, (SalEventGroup*)&AppEventActGroup);
	return 1;
}
bool8 DispWarnEvent(ApiMenu* Menu)
{
	DispEvent(Menu, (SalEventGroup*)&AppEventWarnGroup);
	return 1;
}
bool8 DispChekEvent(ApiMenu* Menu)
{
	DispEvent(Menu, (SalEventGroup*)&AppEventChekGroup);
	return 1;
}
bool8 DispRunEvent(ApiMenu* Menu)
{
	DispEvent(Menu, (SalEventGroup*)&AppEventRunGroup);
	return 1;
}

bool8 DispOptEvent(ApiMenu* Menu)
{
	DispEvent(Menu, (SalEventGroup*)&AppEventOptGroup);
	return 1;
}
bool8 DispDiEvent(ApiMenu* Menu)
{
	DispEvent(Menu, (SalEventGroup*)&AppEventDISoeGroup);
	return 1;
}
bool8 DispDoEvent(ApiMenu* Menu)
{
	DispEvent(Menu, (SalEventGroup*)&AppEventDOSoeGroup);
	return 1;
}
bool8 DispGoInEvent(ApiMenu* Menu)
{
	DispEvent(Menu, (SalEventGroup*)&AppEventGoInSoeGroup);
	return 1;
}
bool8 DispGoOutEvent(ApiMenu* Menu)
{
	DispEvent(Menu, (SalEventGroup*)&AppEventGoOutSoeGroup);
	return 1;
}
bool8 DispLedEvent(ApiMenu* Menu)
{
	DispEvent(Menu, (SalEventGroup*)&AppEventLedSoeGroup);
	return 1;
}
bool8 DispFlagEvent(ApiMenu* Menu)
{
	DispEvent(Menu, (SalEventGroup*)&AppEventFlagSoeGroup);
	return 1;
}
bool8 DispDpiEvent(ApiMenu* Menu)
{
	DispEvent(Menu, (SalEventGroup*)&AppEventDpiSoeGroup);
	return 1;
}

