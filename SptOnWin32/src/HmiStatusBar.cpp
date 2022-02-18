#include "SptProject.h"
using namespace spt;

void spt::HmiStatusBar::Show()
{
	if (updateTimer.Status())
	{
		SalRtc rtc;
		rtc.Now();
		if (rtc.second != lastSec)
		{
			SetUpdate(1);
			WidLine line;
			line.SetRect(rect.x, rect.y, rect.h, 1);
			WidRect::ClearRect();
			WidRect::Show();
			lastSec = rtc.second;
			String30B str;
			rtc.ToStrHzFmt1(str);
			WidTextLine text;
			text.SetPos(rect.x + 2, rect.y + 2);
			text.SetText(str.Str());
			text.Show();
			line.SetPos(line.Rect().x + 22 * gd->FontWidth() + 4, line.Rect().y);
			line.Show();
			SalDateQ q;
			q.q = rtc.q;
			if (q.bits.isSyncErr == 0)
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
			line.SetPos(line.Rect().x + gd->FontWidth() * 2 + 4, line.Rect().y);
			line.Show();
			gd->Update(rect);
			updateTimer.Restart();
		}
		UpdateHmiLedInfo();
	}
	else if (!updateTimer.IsEnable())
	{
		updateTimer.UpCnt(500);
		updateTimer.Enable(1);
	}
	return;
}

spt::HmiStatusBar::HmiStatusBar()
{
	rect.x = 0;
	rect.y = gd->LcdHeight() - gd->FontHeight() - 2 * gd->SpaceOfFont();
	rect.w = gd->LcdWidth();
	rect.h = gd->LcdHeight() - rect.y;
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
		updateHmiLedTimer.Restart();
	}
	else if (!updateHmiLedTimer.IsEnable())
	{
		updateHmiLedTimer.UpCnt(5000);
		updateHmiLedTimer.Enable(1);
	}
}
