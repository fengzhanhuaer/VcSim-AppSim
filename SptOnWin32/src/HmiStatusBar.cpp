#include "SptProject.h"
using namespace spt;


int32 spt::HmiStatusBar::Show()
{
	if (updateTimer.Status())
	{
		HmiWidLine line;
		line.SetVisible(1);
		line.Rect().h = rect.h;
		line.Rect().w = 1;
		line.Rect().y = rect.y;
		line.Rect().x = rect.x;
		SalDateStamp date;
		date.Now();
		//int64 d = date.Us() / date.Dt1Second;
		SalRtc rtc;
		rtc.FromStamp(&date);
		rtc.Now();
		if (rtc.second != lastSec)
		{
			HmiWidRect::Show(E_AllFrame);
			lastSec = rtc.second;
			String30B str;
			rtc.ToStrHzFmt1(str);
			HmiWidTextLine text;
			text.SetVisible(1);
			text.SetPos(rect.x + 2, rect.y + 2, str.StrLen());
			text.SetText(str.Str());
			text.Show(E_AllFrame);
			line.Rect().x = 22 * gd->FontWidth() + 4;
			line.Show(E_AllFrame);
			if (date.q.bits.isSyncErr == 0)
			{
				if (DatePara::Instance().AdJustMode.Data() == DatePara::E_LIGHT_IRIG_B)
				{
					GraphicDevice::Instance().DrawBitMap(line.Rect().x + 2, line.Rect().y + 2, E_BMT_IRIG_B_SYN, GraphicDevice::E_Black);
				}
				else if (DatePara::Instance().AdJustMode.Data() == DatePara::E_ELE_IRIG_B)
				{
					GraphicDevice::Instance().DrawBitMap(line.Rect().x + 2, line.Rect().y + 2, E_BMT_IRIG_B_SYN, GraphicDevice::E_Black);
				}
				else if (DatePara::Instance().AdJustMode.Data() == DatePara::E_SNTP)
				{
					GraphicDevice::Instance().DrawBitMap(line.Rect().x + 2, line.Rect().y + 2, E_BMT_SNTP_SYN, GraphicDevice::E_Black);
				}

			}
			line.Rect().x += gd->FontWidth() * 2 + 4;
			line.Show(E_AllFrame);
			gd->Update(rect);
		}
		UpdateHmiLedInfo();
	}
	else if (!updateTimer.IsEnable())
	{
		updateTimer.UpCnt(200);
		updateTimer.Enable(1);
	}
	return 0;
}

spt::HmiStatusBar::HmiStatusBar()
{
	rect.x = 0;
	rect.y = gd->LcdHeight() - gd->FontHeight() - 2 * gd->SpaceOfFont();
	rect.w = gd->LcdWidth();
	rect.h = gd->LcdHeight() - rect.y;
	SetVisible(1);
	hmiLedGroup = 0;
	hmiLedOldStatus.Alloc(1, 100);
	SetSaveBlockPara();
}

void spt::HmiStatusBar::UpdateHmiLedInfo()
{
	if (SptIoProcess::Instance().SptFlag().IsPowerDownAtRange(saveLowLimit, saveHighLimit))
	{
		return;
	}
	bool8 update = 0;
	uint16 num = 0;
	uint8* buf = (uint8*)hmiLedOldStatus.BufBase();
	if (hmiLedGroup)
	{
		if (hmiLedOldStatus.BufSize() < hmiLedGroup->InstNum())
		{
			return;
		}
		num = hmiLedGroup->InstNum();
		update = hmiLedGroup->GetValue(buf, hmiLedOldStatus.BufSize());
	}
	else
	{
		InstObjectGroup* gp = InstObjectRoot::Instance().GetGroup(EIOT_HMILED);
		hmiLedGroup = (HmiLedGroup*)gp;
		return;
	}
	if (update || updateHmiLedTimer.Status())
	{
		hmiLedGroup->SaveFile();
		LcdIedInfo lmc;
		lmc.type = E_LedInfoVal;
		lmc.len = sizeof(lmc) - sizeof(lmc.data) + num;
		lmc.ledNum = num;
		for (uint32 i = 0; i < num; i++)
		{
			lmc.data[i] = buf[i];
		}
		HmiLcdCmm::Instance().Send((LcdMsgContext*)&lmc);
	}
	else if (!updateHmiLedTimer.IsEnable())
	{
		updateHmiLedTimer.UpCnt(5000);
		updateHmiLedTimer.Enable(1);
	}
}
