#include "ApiProject.h"
using namespace spt;

bool8 spt::HmiSetSystemDate(ApiMenu* Menu)
{
	SalDateStamp date;
	date.Now();
	if (date.Q().bits.isSyncErr)
	{
		SalDateStamp dateStart;
		dateStart.Now();
		ApiHmiDateEditDialog dig("����ʱ��", dateStart);
		dig.Show();
		dateStart = dig.Stamp();
		SalRtc rtc = dig.Rtc();
		if (rtc.minute >= 60)
		{
			rtc.minute = 59;
		}
		if (rtc.second >= 60)
		{
			rtc.second = 59;
		}
		dateStart.Set(&rtc);
		if (SptDateTask::Instance().HmiSetDateTime(dateStart))
		{
			ApiWarnDialog dig("����ʱ��ɹ�", 0, 0, 0, 0);
			dig.Show();
		}
		else
		{
			ApiWarnDialog dig("����ʱ��ʧ��", 0, 0, 0, 0);
			dig.Show();
		}
	}
	else
	{
		ApiWarnDialog dig("װ��ʱ��ͬ������", "��ֹ�ֶ��޸�ʱ��", 0, 0, 0);
		dig.Show();
	}
	return 1;
}
