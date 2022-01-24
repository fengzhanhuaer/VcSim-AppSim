#include"InstResource.h"

int32 UpdateSjRecordHmiTextWnd(class HmiTextWnd& Wnd, uint16 Page, uint16 TotalPage, HmiKey key)
{
	uint32 pageEnd = Min(TotalPage, Page + 10);
	String500B str;
	uint32 page = 0;
	SalSjRecordData* record;
	for (uint32 i = Page; i < pageEnd; i++)
	{
		page = TotalPage - i - 1;
		str.Clear();
		record = &HmiSjRecordViewPool.record[page];
		str << "时间:" << record[0].stamp << "\n";
		if (record[0].process[0])
		{
			str << "组件:" << record[0].process << "\n";
		}
		if (record[0].usr[0])
		{
			str << "主体:" << record[0].usr << "\n";
		}

		if (record[0].object[0])
		{
			str << "客体:" << record[0].object << "\n";
		}
		if (record[0].result[0])
		{
			str << "结果:" << record[0].result << "\n";
		}
		if (record[0].exInfo1[0])
		{
			str << "信息1:" << record[0].exInfo1 << "\n";
			if (record[0].exInfo2[0])
			{
				str << "信息2:" << record[0].exInfo2 << "\n";
				if (record[0].exInfo3[0])
				{
					str << "信息3:" << record[0].exInfo3 << "\n";
				}
			}
		}
		Wnd.SetPage(i, str.Str());
	}
	return 0;
}

bool8 ViewSjRecord(ApiMenu* Menu, SalSjRecordGroup* SjRecordGroup)
{
	SalDateStamp dateStart, dateEnd;
	dateEnd.Now();
	dateStart.Set(dateEnd.Us() - SalDateStamp::Dt1Day);
	ApiHmiDateEditDialog dig("开始时间", dateStart);
	dig.Show();
	dateStart = dig.Stamp();
	ApiHmiDateEditDialog dig2("结束时间", dateEnd);
	dig2.Show();
	dateEnd = dig2.Stamp();
	HmiSjRecordViewPool.GetValid(SjRecordGroup, (uint64)dateStart.Us(), (uint64)dateEnd.Us());
	if (HmiSjRecordViewPool.validRecordNum == 0)
	{
		ApiWarnDialog dig("该时间段内无记录产生", 0, 0, 0, 0);
		dig.Show();
		return 0;
	}
	ApiHmiTextWnd wnd(HmiTextWnd::E_ScrollPage, UpdateSjRecordHmiTextWnd);
	wnd.SetTitle(SjRecordGroup->Name(), HmiSjRecordViewPool.validRecordNum);
	wnd.Show();
	return 0;
}
bool8 ViewUserLogSjRecord(ApiMenu* Menu)
{
	ViewSjRecord(Menu, (SalSjRecordGroup*)&SjUsrLogRecord);
	return 0;
}
bool8 ExportSjRecord(ApiMenu* Menu, SalSjRecordGroup* SjRecordGroup)
{
	SalDateStamp dateStart, dateEnd;
	dateEnd.Now();
	dateStart.Set(dateEnd.Us() - SalDateStamp::Dt1Day);
	ApiHmiDateEditDialog dig("开始时间", dateStart);
	dig.Show();
	dateStart = dig.Stamp();
	ApiHmiDateEditDialog dig2("结束时间", dateEnd);
	dig2.Show();
	dateEnd = dig2.Stamp();
	HmiSjRecordViewPool.GetValid(SjRecordGroup, (uint64)dateStart.Us(), (uint64)dateEnd.Us());
	if (HmiSjRecordViewPool.validRecordNum == 0)
	{
		ApiWarnDialog dig("该时间段内无记录产生", 0, 0, 0, 0);
		dig.Show();
		return 0;
	}
	HmiSjRecordViewPool.ExportCsv(SjRecordGroup, 0);
	return 0;
}
bool8 ExportUserLogSjRecord(ApiMenu* Menu)
{
	ExportSjRecord(Menu, (SalSjRecordGroup*)&SjUsrLogRecord);
	return 0;
}