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
	ApiHmiDateEditDialog dig("��ʼʱ��", dateStart);
	dig.Show();
	dateStart = dig.Stamp();
	ApiHmiDateEditDialog dig2("����ʱ��", dateEnd);
	dig2.Show();
	dateEnd = dig2.Stamp();
	HmiViewEventPool.GetValid(Group, (uint64)dateStart.Us(), (uint64)dateEnd.Us(), 1);
	if (HmiViewEventPool.validRecordNum == 0)
	{
		ApiWarnDialog dig("��ʱ������޼�¼����", 0, 0, 0, 0);
		dig.Show();
		return 0;
	}
	ApiHmiTextWnd wnd(HmiTextWnd::E_ScrollPage, UpdateEventHmiTextWnd);
	wnd.SetTitle(Menu->Name(), HmiViewEventPool.validRecordNum);
	wnd.Show();
	return 1;
}

bool8 DispWarnEvent(ApiMenu* Menu)
{
	DispEvent(Menu, (SalEventGroup*)&AppEventWarnGroup);
	return 1;
}

bool8 DispActReport(ApiMenu* Menu)
{
	ApiHmiTextWnd wnd(HmiTextWnd::E_ContinuePage, 0);
	SalFwRecordGroup* group = (SalFwRecordGroup*)&FwGroupPub;
	uint32 PageNum = 0;
	for (uint32 i = 0; i < group->MaxRecordFwRamData; i++)
	{
		String5000B str;
		str.Clear();
		const SalFwData* data = group->GetHmiViewDataByIndex(i);
		if (data)
		{
			data->ToLcdStr(str, 1, 0, 60);//�ڶ���������ʾ�Ƿ���ʾ������Ϣ��������������ʾ�Ƿ���ʾ������Ϣ�����һ��������ʾ����ȣ��ֽڣ�
			wnd.SetPage(PageNum, str.Str());
			PageNum++;
		}
	}
	if (PageNum >= group->MaxRecordFwRamData)
	{
		PageNum = group->MaxRecordFwRamData - 1;
	}
	if (PageNum == 0)
	{
		ApiWarnDialog dig("�޼�¼����", 0, 0, 0, 0);
		dig.Show();
		return 1;
	}
	wnd.SetTitle(Menu->Name(), PageNum);
	wnd.Show();
	return 1;
}
