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
		ApiHmiDateEditDialog dig("设置时间", dateStart);
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
			ApiWarnDialog dig("设置时间成功", 0, 0, 0, 0);
			dig.Show();
		}
		else
		{
			ApiWarnDialog dig("设置时间失败", 0, 0, 0, 0);
			dig.Show();
		}
	}
	else
	{
		ApiWarnDialog dig("装置时间同步正常", "禁止手动修改时间", 0, 0, 0);
		dig.Show();
	}
	return 1;
}
