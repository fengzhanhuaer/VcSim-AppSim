#include "SptProject.h"
using namespace spt;

int32 spt::HmiStatusBar::Show()
{
	if (updateTimer.Status())
	{
		SalRtc rtc;
		rtc.Now();
		if (rtc.second != lastSec)
		{
			SetUpdate(1);
			HmiWidLine line;
			line.SetWidth(1);
			line.SetStartPos(rect.x, rect.y);
			line.SetEndPos(rect.x, rect.y + rect.h);
			HmiWidRect::ClearRect();
			HmiWidRect::Show();
			lastSec = rtc.second;
			String30B str;
			rtc.ToStrHzFmt1(str);
			HmiWidTextLine text;
			text.SetPos(rect.x + 2, rect.y + 2);
			text.SetText(str.Str());
			text.Show();
			line.SetStartPos(line.StartPos().x + 22 * gd->FontWidth() + 4, line.StartPos().y);
			line.SetEndPos(line.EndPos().x + 22 * gd->FontWidth() + 4, line.EndPos().y);
			line.Show();
			SalDateQ q;
			q.q = rtc.q;
			if (q.bits.isSyncErr == 0)
			{
				if (DatePara::Instance().AdJustMode.Data() == DatePara::E_LIGHT_IRIG_B)
				{
					GraphicDevice::Instance().DrawBitMap(line.StartPos().x + 2, line.StartPos().y + 2, E_BMT_IRIG_B_SYN, GraphicDevice::E_Black);
				}
				else if (DatePara::Instance().AdJustMode.Data() == DatePara::E_ELE_IRIG_B)
				{
					GraphicDevice::Instance().DrawBitMap(line.StartPos().x + 2, line.StartPos().y + 2, E_BMT_IRIG_B_SYN, GraphicDevice::E_Black);
				}
				else if (DatePara::Instance().AdJustMode.Data() == DatePara::E_SNTP)
				{
					GraphicDevice::Instance().DrawBitMap(line.StartPos().x + 2, line.StartPos().y + 2, E_BMT_SNTP_SYN, GraphicDevice::E_Black);
				}
			}
			line.SetStartPos(line.StartPos().x + gd->FontWidth() * 2 + 4, line.StartPos().y);
			line.SetEndPos(line.EndPos().x + gd->FontWidth() * 2 + 4, line.EndPos().y);
			line.Show();
			gd->Update(rect);
			updateTimer.Restart();
		}
		UpdateHmiLedInfo();
	}
	else if (!updateTimer.IsEnable())
	{
		updateTimer.UpCnt(990);
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
