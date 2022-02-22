#include"SptProject.h"
using namespace spt;
spt::HmiWidDialog::HmiWidDialog()
{

}

void spt::HmiWidDialog::AutoLayout()
{
	rect.w = (lineWidth + 4) * gd->FontWidth();
	rect.h = (lineCount) * (gd->FontHeight() + 2 * gd->SpaceOfFont()) + 5 * gd->SpaceOfFont();
	if (gd->LcdWidth() == 480)
	{
		rect.x = 440 / 2 - rect.w / 2;
		rect.y = 250 / 2 - rect.h / 2;
	}
	else if (gd->LcdWidth() == 320)
	{
		rect.x = 300 / 2 - rect.w / 2;
		rect.y = 220 / 2 - rect.h / 2;
	}
	SetUpdateSelf(1);
}

void spt::HmiAssicInputDialog::AutoLayout()
{
	maxTextLine = 0;
	curse.SetRow(0);
	curse.SetCol(6);
	if (mode == E_Full)
	{
		text[0].SetText("!@#$%^&*()-='?<>");
		text[1].SetText("abcdefghijklmn");
		text[2].SetText("opqrstuvwxyz_+|\\");
		text[3].SetText("0123456789{}[]\x1B");
		text[4].SetText("ABCDEFGHIJKLMN`'");
		text[5].SetText("OPQRSTUVWXYZ,./~");
		maxTextLine = 6;
		curse.SetRow(3);
		curse.SetCol(6);
	}
	else if (mode == E_HEX)
	{
		text[0].SetText("0123456789.");
		text[1].SetText("ABCDEF\x1B");
		maxTextLine = 2;
	}
	else if (mode == E_Number)
	{
		text[0].SetText("0123456789.\x1B");
		maxTextLine = 1;
	}
	lineCount = maxTextLine + 1;
	lineWidth = inputMaxLen;
	HmiWidDialog::AutoLayout();
	input.SetRect(rect.x + gd->FontWidth(), rect.y + gd->FontWidth() / 2 + gd->SpaceOfFont(), (inputMaxLen + 2) * gd->FontWidth(), gd->FontHeight() + gd->SpaceOfFont() * 2);
	AddChild(&input);
	text[0].SetRect(rect.x + rect.w / 2 - text[0].Rect().w / 2, input.Rect().YEnd() + gd->SpaceOfFont(), (text[0].Text().StrLen() + 1) * gd->FontWidth(), gd->FontHeight() + gd->SpaceOfFont());
	AddChild(&text[0]);
	for (uint32 i = 1; i < maxTextLine; i++)
	{
		text[i].SetRect(text[i - 1].Rect().x, text[i - 1].Rect().y + gd->FontHeight() + gd->SpaceOfFont(), text[i - 1].Rect().w, text[i - 1].Rect().h);
		AddChild(&text[i]);
	}
	curse.SetRect(text[curse.Row()].Rect().x, text[curse.Row()].Rect().y, gd->FontWidth(), gd->FontHeight());
	AddChild(&curse);
}

spt::HmiAssicInputDialog::HmiAssicInputDialog(E_Mode Mode)
{
	inputMaxLen = 25;
	mode = Mode;
}

void spt::HmiAssicInputDialog::SetMaxInputLen(uint32 Len)
{
	inputMaxLen = Len;
}

void spt::HmiAssicInputDialog::SetDefault(const char* Def)
{
	inputStr = Def;
	maxTextLine = Max(inputMaxLen, (uint32)inputStr.StrLen());
}

int32 spt::HmiAssicInputDialog::ShowSelf()
{
	if (!isInied)
	{
		ClearRect();
		WidRect::ShowSelf();
	}
	if (isUpdate)
	{
		String100B str;
		str = inputStr.Str();
		str << "_";
		input.SetText(str.Str());
		input.ClearRect();
		str.Clear();
		str << text[curse.Row()].Text().Str()[curse.Col()];
		curse.SetText(str.Str());
		curse.SetPos(text[curse.Row()].Rect().x + curse.Col() * gd->FontWidth(), text[curse.Row()].Rect().y);
		for (uint32 i = 0; i < maxTextLine; i++)
		{
			text[i].ClearRect();
			text[i].SetUpdate(1);
		}
	}
	return 0;
}

int32 spt::HmiAssicInputDialog::Edit()
{
	HmiKey key;
	AutoLayout();
	bool8 virok = HmiLcdCmm::Instance().IsVirLcdCmmOk();
	uint32 col;
	uint32 row;
	FindFirstSelChild();
	while (1)
	{
		if (this->key->Pop(key))
		{
			if (key.Key1 == EK1_KEYVALUE)
			{
				E_KEY2 k2 = (E_KEY2)key.Key2;
				switch (k2)
				{
				case spt::EK_ENTER:
				{
					if (!virok)
					{
						char d = text[curse.Row()].Text().Str()[curse.Col()];
						if ((d == '\x1B') && (inputStr.StrLen()))
						{
							String100B s;
							s = inputStr.Str();
							s.Str()[s.StrLen() - 1] = 0;
							inputStr = s.Str();
						}
						else if (inputStr.StrLen() < (int32)inputMaxLen)
						{
							inputStr << d;
						}
					}
					else
					{
						ClearRect();
						Update();
						return E_OK;
					}
					SetUpdateSelf(1);
					break;
				}
				case spt::EK_ADD:
				{
					break;
				}
				case spt::EK_ESC:
					ClearRect();
					Update();
					return E_ESC;
					break;
				case spt::EK_LEFT:
					if (curse.Col())
					{
						curse.SetCol(curse.Col() - 1);
						SetUpdateSelf(1);
						text[curse.Row()].SetUpdateSelf(1);
					}
					break;
				case spt::EK_UP:
					if (curse.Row())
					{
						text[curse.Row()].SetUpdateSelf(1);
						curse.SetRow(curse.Row() - 1);
						if (curse.Col() >= text[curse.Row()].Text().StrLen())
						{
							curse.SetCol(text[curse.Row()].Text().StrLen() - 1);
						}
						SetUpdateSelf(1);
						text[curse.Row()].SetUpdateSelf(1);
					}
					break;
				case spt::EK_RIGHT:
					col = curse.Col() + 1;
					if ((int32)col < text[curse.Row()].Text().StrLen())
					{
						text[curse.Row()].SetUpdateSelf(1);
						curse.SetCol(col);
						SetUpdateSelf(1);
						text[curse.Row()].SetUpdateSelf(1);
					}
					break;
				case spt::EK_DOWN:
					row = curse.Row() + 1;
					if (row < maxTextLine)
					{
						text[curse.Row()].SetUpdateSelf(1);
						curse.SetRow(row);
						if (curse.Col() >= text[curse.Row()].Text().StrLen())
						{
							curse.SetCol(text[curse.Row()].Text().StrLen() - 1);
						}
						SetUpdateSelf(1);
						text[curse.Row()].SetUpdateSelf(1);
					}
					break;
				case spt::EK_MD_STOP:
					ClearRect();
					gd->Update(rect);
					return E_FORCE_ESC;
					break;
				case spt::EK_BACK:
					if ((inputStr.StrLen()))
					{
						String100B s;
						s = inputStr.Str();
						s.Str()[s.StrLen() - 1] = 0;
						inputStr = s.Str();
						SetUpdateSelf(1);
					}
					break;
				default:
					break;
				}
			}
			else if (key.Key1 == EK1_ASSIC)
			{
				char d = key.Key2;
				if (inputStr.StrLen() < (int32)inputMaxLen)
				{
					inputStr << d;
				}
				SetUpdateSelf(1);
			}
			HmiMain::Instance().MsSleep(50);
		}
		else
		{
			HmiMain::Instance().MsSleep(200);
		}
		HmiWidDialog::Show();
		Update();
	}
	ClearRect();
	gd->Update(rect);
	return -1;
}

const char* spt::HmiAssicInputDialog::InputStr()
{
	return inputStr.Str();
}

void spt::HmiStrEditDialog::SetTitle(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5)
{
	SetMaxInputLen(20);
	titleMaxLen = 0;
	lineCount = 0;
	if (Str1)
	{
		title[lineCount].SetText(Str1);
		titleMaxLen = Max(title[lineCount].Text().StrLen(), (int32)titleMaxLen);
		text[lineCount].SetCanBeSelect(1);
		lineCount++;
	}
	else
	{
		return;
	}
	if (Str2)
	{
		title[lineCount].SetText(Str2);
		titleMaxLen = Max(title[lineCount].Text().StrLen(), (int32)titleMaxLen);
		text[lineCount].SetCanBeSelect(1);
		lineCount++;
	}
	else
	{
		return;
	}
	if (Str3)
	{
		title[lineCount].SetText(Str3);
		titleMaxLen = Max(title[lineCount].Text().StrLen(), (int32)titleMaxLen);
		text[lineCount].SetCanBeSelect(1);
		lineCount++;
	}
	else
	{
		return;
	}
	if (Str4)
	{
		title[lineCount].SetText(Str4);
		titleMaxLen = Max(title[lineCount].Text().StrLen(), (int32)titleMaxLen);
		text[lineCount].SetCanBeSelect(1);
		lineCount++;
	}
	else
	{
		return;
	}
	if (Str5)
	{
		title[lineCount].SetText(Str5);
		titleMaxLen = Max(title[lineCount].Text().StrLen(), (int32)titleMaxLen);
		text[lineCount].SetCanBeSelect(1);
		lineCount++;
	}
	else
	{
		return;
	}
}

void spt::HmiStrEditDialog::SetText(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5)
{
	if (Str1)
	{
		text[0].SetText(Str1);
	}
	else
	{
		return;
	}
	if (Str2)
	{
		text[1].SetText(Str2);
	}
	else
	{
		return;
	}
	if (Str3)
	{
		text[2].SetText(Str3);
	}
	else
	{
		return;
	}
	if (Str4)
	{
		text[3].SetText(Str4);
	}
	else
	{
		return;
	}
	if (Str5)
	{
		text[4].SetText(Str5);
	}
	else
	{
		return;
	}
}

void spt::HmiStrEditDialog::SetEditAble(bool8 EditAble1, bool8 EditAble2, bool8 EditAble3, bool8 EditAble4, bool8 EditAble5)
{
	text[0].SetCanBeSelect(EditAble1);
	text[1].SetCanBeSelect(EditAble2);
	text[2].SetCanBeSelect(EditAble3);
	text[3].SetCanBeSelect(EditAble4);
	text[4].SetCanBeSelect(EditAble5);
}

void spt::HmiStrEditDialog::SetMaxInputLen(uint32 Len)
{
	inputMaxLen = Len;
}

int32 spt::HmiStrEditDialog::Edit()
{
	HmiKey key;
	SetPeriodUpdate(1, 200);
	AutoLayout();
	FindFirstSelChild();
	while (1)
	{
		if (this->key->Pop(key))
		{
			E_KEY2 k2 = (E_KEY2)key.Key2;
			if (key.Key1 == EK1_KEYVALUE)
			{
				switch (k2)
				{
				case spt::EK_ENTER:
				{
					if (cursepos && cursepos->IsSelected())
					{
						HmiAssicInputDialog dig(HmiAssicInputDialog::E_Full);
						WidTextLine* cur = (WidTextLine*)cursepos;
						dig.SetDefault(cur->Text().Str());
						dig.AutoLayout();
						int res = dig.Edit();
						cur->SetText(dig.InputStr());
						int goL = cur - text + 1;
						if ((uint32)goL == lineCount)
						{
							return res;
						}
						else
						{
							Go2NextSelChild();
						}
					}
					SetInied(0);
					SetUpdateSelf(1);
					break;
				}
				case spt::EK_ESC:
					ClearRect();
					gd->Update(rect);
					return E_ESC;
					break;
				case spt::EK_LEFT:
					break;
				case spt::EK_UP:
					Go2LastSelChild();
					SetUpdateSelf(1);
					break;
				case spt::EK_RIGHT:
					break;
				case spt::EK_DOWN:
					Go2NextSelChild();
					SetUpdateSelf(1);
					break;
				case spt::EK_MD_STOP:
					ClearRect();
					gd->Update(rect);
					return E_FORCE_ESC;
					break;
				default:
					break;
				}
			}
			HmiMain::Instance().MsSleep(50);
		}
		else
		{
			HmiMain::Instance().MsSleep(200);
		}
		HmiWidDialog::Show();
		Update();
	}
	ClearRect();
	gd->Update(rect);
	return -1;
}

void spt::HmiStrEditDialog::AutoLayout()
{
	lineWidth = inputMaxLen + 1 + titleMaxLen;
	HmiWidDialog::AutoLayout();
	title[0].SetRect(rect.x + gd->FontWidth(), rect.y + gd->FontWidth() / 2 + gd->SpaceOfFont(), (titleMaxLen + 1) * gd->FontWidth(), gd->FontHeight());
	text[0].SetRect(title[0].Rect().x + title[0].Rect().w, title[0].Rect().y, (inputMaxLen + 1) * gd->FontWidth(), title[0].Rect().h);
	AddChild(&title[0]);
	AddChild(&text[0]);
	for (uint32 i = 1; i < lineCount; i++)
	{
		title[i].SetRect(title[i - 1].Rect().x, title[i - 1].Rect().y + gd->FontHeight() + 2 * gd->SpaceOfFont(), title[i - 1].Rect().w, title[i - 1].Rect().h);
		text[i].SetRect(title[0].Rect().x + title[0].Rect().w, title[i].Rect().y, text[i - 1].Rect().w, title[0].Rect().h);
		AddChild(&title[i]);
		AddChild(&text[i]);
	}
}

const char* spt::HmiStrEditDialog::InputStr(uint32 Index)
{
	if (Index < lineCount)
	{
		return text[Index].Text().Str();
	}
	return 0;
}

int32 spt::HmiStrEditDialog::ShowSelf()
{
	if (!isInied)
	{
		ClearRect();
		WidRect::ShowSelf();
		for (uint32 i = 0; i < lineCount; i++)
		{
			text[i].SetUpdate(1);
			title[i].SetUpdate(1);
		}
	}
	if (isUpdate)
	{
		for (uint32 i = 0; i < lineCount; i++)
		{
			if (text[i].IsSelected() == 1)
			{
				gd->ClearRect(text[i].Rect().x, text[i].Rect().y, text[i].Color(), text[i].Rect().w, text[i].Rect().h);
			}
			else
			{
				gd->ClearRect(text[i].Rect().x, text[i].Rect().y, text[i].Backcolor(), text[i].Rect().w, text[i].Rect().h);
				text[i].SetUpdate(1);
			}
		}
	}
	return 0;
}

void spt::HmiWarnDialog::SetTitle(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5)
{
	HmiInfoDialog::SetTitle(Str1, Str2, Str3, Str4, Str5, "按任意键继续");
}

void spt::HmiInfoDialog::AutoLayout()
{
	lineWidth = lineWidth;
	HmiWidDialog::AutoLayout();
	uint16 w = (title[0].Text().StrLen() + 1) * gd->FontWidth();
	title[0].SetRect(rect.x + rect.w / 2 - w / 2, rect.y + gd->FontWidth() / 2 + gd->SpaceOfFont(), w, gd->FontHeight() + gd->SpaceOfFont() * 2);
	AddChild(&title[0]);
	for (uint32 i = 1; i < lineCount; i++)
	{
		w = (title[i].Text().StrLen() + 1) * gd->FontWidth();
		title[i].SetRect(rect.x + rect.w / 2 - w / 2, title[i - 1].Rect().y + gd->FontHeight() + 3 * gd->SpaceOfFont(), w, title[i - 1].Rect().h);
		AddChild(&title[i]);
	}
}

int32 spt::HmiWarnDialog::Edit()
{
	HmiKey key;
	AutoLayout();
	while (1)
	{
		if (this->key->Pop(key))
		{
			E_KEY2 k2 = (E_KEY2)key.Key2;
			if (key.Key1 == EK1_KEYVALUE)
			{
				switch (k2)
				{
				case spt::EK_ENTER:
				case spt::EK_LEFT:
				case spt::EK_UP:
				case spt::EK_RIGHT:
				case spt::EK_DOWN:
					ClearRect();
					gd->Update(rect);
					return E_OK;
					break;
				case spt::EK_ESC:
					ClearRect();
					gd->Update(rect);
					return E_ESC;
					break;
				case spt::EK_MD_STOP:
					ClearRect();
					gd->Update(rect);
					return E_FORCE_ESC;
					break;
				default:
					break;
				}
			}
			HmiMain::Instance().MsSleep(50);
		}
		else
		{
			HmiMain::Instance().MsSleep(200);
		}
		HmiWidDialog::Show();
		Update();
	}
	ClearRect();
	gd->Update(rect);
	return -1;
}

void spt::HmiSelectDialog::SetTitle(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5)
{
	HmiInfoDialog::SetTitle(Str1, Str2, Str3, Str4, Str5, "<确认>或<取消>");
}

int32 spt::HmiSelectDialog::Edit()
{
	HmiKey key;
	SetPeriodUpdate(1, 200);
	AutoLayout();
	while (1)
	{
		if (this->key->Pop(key))
		{
			E_KEY2 k2 = (E_KEY2)key.Key2;
			if (key.Key1 == EK1_KEYVALUE)
			{
				switch (k2)
				{
				case spt::EK_ENTER:
					ClearRect();
					gd->Update(rect);
					return E_OK;
					break;
				case spt::EK_ESC:
					ClearRect();
					gd->Update(rect);
					return E_ESC;
					break;
				case spt::EK_MD_STOP:
					ClearRect();
					gd->Update(rect);
					return E_FORCE_ESC;
					break;
				default:
					break;
				}
			}
		}
		else
		{
			HmiMain::Instance().MsSleep(10);
		}
		HmiWidDialog::Show();
		Update();
	}
	ClearRect();
	gd->Update(rect);
	return -1;
}

int32 spt::HmiSelectDialog::ShowSelf()
{
	if (!isInied)
	{
		ClearRect();
		WidRect::ShowSelf();
	}
	HmiWidDialog::ShowSelf();
	return 0;
}

int32 spt::HmiTimeEditDialog::Edit()
{
	selectIndex = 0;
	HmiKey key;
	SetPeriodUpdate(1, 200);
	AutoLayout();
	char d;
	FindFirstSelChild();
	while (1)
	{
		if (this->key->Pop(key))
		{
			E_KEY2 k2 = (E_KEY2)key.Key2;
			if (key.Key1 == EK1_KEYVALUE)
			{
				switch (k2)
				{
				case spt::EK_ENTER:
				{
					ClearRect();
					gd->Update(rect);
					UpdateDate();
					return E_OK;
				}
				case spt::EK_ESC:
					ClearRect();
					gd->Update(rect);
					UpdateDate();
					return E_ESC;
					break;
				case spt::EK_LEFT:
					if (selectIndex)
					{
						selectIndex--;
						if ((uint8)text[0].Text().Str()[selectIndex] > 127)
						{
							selectIndex -= 2;
						}
						else if (text[0].Text().Str()[selectIndex] == ':')
						{
							selectIndex--;
						}
						else if (text[0].Text().Str()[selectIndex] == ' ')
						{
							selectIndex--;
						}
					}
					SetUpdateSelf(1);
					break;
				case spt::EK_UP:
					d = text[0].Text().Str()[selectIndex];
					if (selectIndex == 0)
					{
						if (d == '1')
						{
							d = '2';
						}
						else
						{
							d = '1';
						}
					}
					else if ((selectIndex == 6))
					{
						if (d == '0')
						{
							d = '1';
						}
						else
						{
							d = '0';
						}
					}
					else
					{
						if (d >= '9')
						{
							d = '0';
						}
						else
						{
							d++;
						}
					}
					text[0].SetText(selectIndex, d);
					SetUpdateSelf(1);
					break;
				case spt::EK_RIGHT:
					selectIndex++;
					if (selectIndex < text[0].Text().StrLen())
					{
						if ((uint8)text[0].Text().Str()[selectIndex] > 128)
						{
							selectIndex += 2;
						}
						else if (text[0].Text().Str()[selectIndex] == ':')
						{
							selectIndex++;
						}
						else if (text[0].Text().Str()[selectIndex] == ' ')
						{
							selectIndex--;
						}
					}
					else
					{
						selectIndex = text[0].Text().StrLen() - 1;
					}
					SetUpdateSelf(1);
					break;
				case spt::EK_DOWN:
					d = text[0].Text().Str()[selectIndex];
					if ((selectIndex == 0))
					{
						if (d == '1')
						{
							d = '2';
						}
						else
						{
							d = '1';
						}
					}
					else if ((selectIndex == 6))
					{
						if (d == '0')
						{
							d = '1';
						}
						else
						{
							d = '0';
						}
					}
					else
					{
						if (d <= '0')
						{
							d = '9';
						}
						else
						{
							d--;
						}
					}
					text[0].SetText(selectIndex, d);
					SetUpdateSelf(1);
					break;
				case spt::EK_MD_STOP:
					ClearRect();
					gd->Update(rect);
					UpdateDate();
					return E_FORCE_ESC;
					break;
				default:
					break;
				}
			}
			HmiMain::Instance().MsSleep(50);
		}
		else
		{
			HmiMain::Instance().MsSleep(200);
		}
		HmiWidDialog::Show();
		Update();
	}
	ClearRect();
	gd->Update(rect);
	return -1;
}

void spt::HmiTimeEditDialog::SetDefaultDate(SalDateStamp& Date)
{
	date = Date;
	SalRtc rtc;
	rtc.FromStamp(&Date);
	u64value v;
	v.u16 = rtc.year;
	data[0].SetData(E_SVT_U16, v, 1, 4, 0, 1);
	v.u16 = rtc.month;
	data[1].SetData(E_SVT_U16, v, 1, 2, 0, 1);
	v.u16 = rtc.day;
	data[2].SetData(E_SVT_U16, v, 1, 2, 0, 1);
	v.u16 = rtc.hour;
	data[3].SetData(E_SVT_U16, v, 1, 2, 0, 1);
	v.u16 = rtc.minute;
	data[4].SetData(E_SVT_U16, v, 1, 2, 0, 1);
	v.u16 = rtc.second;
	data[5].SetData(E_SVT_U16, v, 1, 2, 0, 1);
	rtc.ms = 0;
	rtc.us = 0;
}

void spt::HmiTimeEditDialog::SetTitle(const char* Str1)
{
	lineWidth = 0;
	lineCount = 0;
	if (Str1)
	{
		title[lineCount].SetText(Str1);
		titleMaxLen = title[lineCount].Text().StrLen();
		lineCount++;
	}
	else
	{
		return;
	}
}

void spt::HmiTimeEditDialog::AutoLayout()
{
	lineWidth = inputMaxLen + 1 + titleMaxLen;
	HmiWidDialog::AutoLayout();
	title[0].SetRect(rect.x + gd->FontWidth(), rect.y + gd->FontWidth() / 2 + gd->SpaceOfFont(), (titleMaxLen + 1) * gd->FontWidth(), gd->FontHeight() + gd->SpaceOfFont() * 2);
	text[0].SetRect(title[0].Rect().x + title[0].Rect().w, title[0].Rect().y, (inputMaxLen + 1) * gd->FontWidth(), title[0].Rect().h);
	String100B str;
	date.ToStrHzFmt1(str);
	text[0].SetText(str.Str());
	AddChild(&title[0]);
	AddChild(&text[0]);
	curse.SetRect(text[0].Rect().x + gd->FontWidth() * selectIndex, text[0].Rect().y, gd->FontWidth(), gd->FontHeight());
	selectIndex = text[0].Text().StrLen() - 1;
	str.Clear();
	str << text[0].Text().Str()[selectIndex];
	curse.SetText(str.Str());
	AddChild(&curse);
}

spt::HmiTimeEditDialog::HmiTimeEditDialog()
{
	dataNum = 6;
	text[0].SetText("    年  月  日  :  :  ");
	inputMaxLen = text[0].Text().StrLen();
	titleMaxLen = 0;
}

int32 spt::HmiTimeEditDialog::ShowSelf()
{
	if (!isInied)
	{
		ClearRect();
		WidRect::ShowSelf();
	}
	text[0].ClearRect();
	String10B str;
	str << text[0].Text().Str()[selectIndex];
	curse.SetText(str.Str());
	curse.SetPos(text[0].Rect().x + gd->FontWidth() * selectIndex, curse.Rect().YStart());
	text[0].SetUpdateSelf(1);
	HmiWidDialog::ShowSelf();
	return 0;
}

void spt::HmiTimeEditDialog::UpdateDate()
{
	rtc.FromStrHzFmt1(text[0].Text().Str());
	rtc.Check();
	date.Set(&rtc);
}

int32 spt::HmiInt32DataDialog::Edit()
{
	HmiKey key;
	SetPeriodUpdate(1, 200);
	char d = 0;
	while (1)
	{
		if (this->key->Pop(key))
		{
			if (key.Key1 == EK1_KEYVALUE)
			{
				E_KEY2 k2 = (E_KEY2)key.Key2;
				switch (k2)
				{
				case spt::EK_ENTER:
				{
					TransString ts;
					ts.SetBuf(text[2].Text().Str());
					uint8 dodd;
					ts.GetFixedInt(Cur, 0, dodd);
					if ((Cur >= Min) && (Cur <= Max))
					{
						ClearRect();
						gd->Update(rect);
						return E_OK;
					}
					else
					{
						HmiSelectDialog dig;
						dig.SetTitle("输入越限，请重新输入!", 0, 0, 0, 0);
						if (dig.Edit() == 0)
						{

						}
						else
						{
							Cur = Def;
							ClearRect();
							gd->Update(rect);
							return E_OK;
						}
					}
					SetInied(0);
					break;
				}
				case spt::EK_ESC:
					ClearRect();
					gd->Update(rect);
					return E_ESC;
					break;
				case spt::EK_LEFT:
					if (selectIndex)
					{
						selectIndex--;
						if (text[2].Text().Str()[selectIndex] == '.')
						{
							selectIndex--;
						}
						if (text[2].Text().Str()[selectIndex] == ' ')
						{
							text[2].SetText(selectIndex, '0');
						}
					}
					SetUpdateSelf(1);
					break;
				case spt::EK_ADD:
				case spt::EK_UP:
					d = text[2].Text().Str()[selectIndex];
					if (d == '9')
					{
						d = '-';
					}
					else if (d == '-')
					{
						d = '+';
					}
					else if ((d >= '0') && (d < '9'))
					{
						d++;
					}
					else
					{
						d = '0';
					}
					text[2].SetText(selectIndex, d);
					SetUpdateSelf(1);
					break;
				case spt::EK_RIGHT:
					int32 r;
					r = selectIndex + 1;
					if (r < text[2].Text().StrLen())
					{
						selectIndex = r;
						if (text[2].Text().Str()[selectIndex] == '.')
						{
							selectIndex++;
						}
					}
					SetUpdateSelf(1);
					break;
				case spt::EK_SUB:
				case spt::EK_DOWN:
					d = text[2].Text().Str()[selectIndex];
					if (d == '0')
					{
						d = '+';
					}
					else if (d == '+')
					{
						d = '-';
					}
					else if ((d > '0') && (d <= '9'))
					{
						d--;
					}
					else
					{
						d = '9';
					}
					text[2].SetText(selectIndex, d);
					SetUpdateSelf(1);
					break;
				case spt::EK_MD_STOP:
					ClearRect();
					gd->Update(rect);
					return E_FORCE_ESC;
					break;
				default:

					break;
				}
			}
			else if (key.Key1 == EK1_ASSIC)
			{
				char d = key.Key2;
				if (((d >= '0') && (d <= '9')) || (d == '-') || (d == '+'))
				{
					text[2].SetText(selectIndex, d);
					SetUpdateSelf(1);
				}
			}
			HmiMain::Instance().MsSleep(50);
		}
		else
		{
			HmiMain::Instance().MsSleep(200);
		}
		HmiWidDialog::Show();
		Update();
	}
	ClearRect();
	gd->Update(rect);
	return 0;
}

spt::HmiInt32DataDialog::HmiInt32DataDialog()
{
}

void spt::HmiInt32DataDialog::Set(const char* Title, int32 Min, int32 Def, int32 DotNum, int32 Max)
{
	this->Min = Min;
	Cur = this->Def = Def;
	this->DotNum = DotNum;
	this->Max = Max;
	titleMid.SetText(Title);
	String100B str;
	str.Clear();
	str.Format(Max, 11, DotNum, 0, ' ');
	text[0].SetText(str.Str());
	str.Clear();
	str.Format(Min, 11, DotNum, 0, ' ');
	text[1].SetText(str.Str());
	str.Clear();
	str.Format(Def, 11, DotNum, 0, ' ');
	text[2].SetText(str.Str());
	title[0].SetText("最大值:");
	title[1].SetText("最小值:");
	title[2].SetText("当前值:");
	AutoLayout();
}

int32 spt::HmiInt32DataDialog::Data()
{
	return Cur;
}

int32 spt::HmiUInt32DataDialog::Edit()
{
	HmiKey key;
	char d = 0;
	while (1)
	{
		if (this->key->Pop(key))
		{
			if (key.Key1 == EK1_KEYVALUE)
			{
				E_KEY2 k2 = (E_KEY2)key.Key2;
				switch (k2)
				{
				case spt::EK_ENTER:
				{
					TransString ts;
					ts.SetBuf(text[2].Text().Str());
					uint8 dodd;
					ts.GetFixedInt(Cur, 0, dodd);
					if ((Cur >= Min) && (Cur <= Max))
					{
						ClearRect();
						gd->Update(rect);
						return E_OK;
					}
					else
					{
						HmiSelectDialog dig;
						dig.SetTitle("输入越限，请重新输入!", 0, 0, 0, 0);
						if (dig.Edit() == 0)
						{

						}
						else
						{
							Cur = Def;
							ClearRect();
							gd->Update(rect);
							return E_ESC;
						}
					}
					SetInied(0);
					break;
				}
				case spt::EK_ESC:
					ClearRect();
					gd->Update(rect);
					return E_ESC;
					break;
				case spt::EK_LEFT:
					if (selectIndex)
					{
						selectIndex--;
						if (text[2].Text().Str()[selectIndex] == '.')
						{
							selectIndex--;
						}
						if (text[2].Text().Str()[selectIndex] == ' ')
						{
							text[2].SetText(selectIndex, '0');
						}
					}
					SetUpdateSelf(1);
					break;
				case spt::EK_ADD:
				case spt::EK_UP:
					d = text[2].Text().Str()[selectIndex];
					if ((d >= '0') && (d < '9'))
					{
						d++;
					}
					else
					{
						d = '0';
					}
					text[2].SetText(selectIndex, d);
					SetUpdateSelf(1);
					break;
				case spt::EK_RIGHT:
					int32 r;
					r = selectIndex + 1;
					if (r < text[2].Text().StrLen())
					{
						selectIndex = r;
						if (text[2].Text().Str()[selectIndex] == '.')
						{
							selectIndex++;
						}
					}
					SetUpdateSelf(1);
					break;
				case spt::EK_SUB:
				case spt::EK_DOWN:
					d = text[2].Text().Str()[selectIndex];
					if ((d > '0') && (d <= '9'))
					{
						d--;
					}
					else
					{
						d = '9';
					}
					text[2].SetText(selectIndex, d);
					SetUpdateSelf(1);
					break;
				case spt::EK_MD_STOP:
					ClearRect();
					gd->Update(rect);
					return E_FORCE_ESC;
					break;
				default:
					break;
				}
			}
			else if (key.Key1 == EK1_ASSIC)
			{
				d = key.Key2;
				if (((d >= '0') && (d <= '9')))
				{
					text[2].SetText(selectIndex, d);
					SetUpdateSelf(1);
				}
			}
			HmiMain::Instance().MsSleep(50);
		}
		else
		{
			HmiMain::Instance().MsSleep(200);
		}
		HmiWidDialog::Show();
		Update();
	}
	ClearRect();
	gd->Update(rect);
	return 0;
}

spt::HmiUInt32DataDialog::HmiUInt32DataDialog()
{
}

void spt::HmiUInt32DataDialog::Set(const char* Title, uint32 Min, uint32 Def, uint32 DotNum, uint32 Max)
{
	this->Min = Min;
	Cur = this->Def = Def;
	this->DotNum = DotNum;
	this->Max = Max;
	titleMid.SetText(Title);
	String100B str;
	str.Clear();
	str.Format(Max, 11, DotNum, 0, ' ');
	text[0].SetText(str.Str());
	str.Clear();
	str.Format(Min, 11, DotNum, 0, ' ');
	text[1].SetText(str.Str());
	str.Clear();
	str.Format(Def, 11, DotNum, 0, ' ');
	text[2].SetText(str.Str());
	title[0].SetText("最大值:");
	title[1].SetText("最小值:");
	title[2].SetText("当前值:");
	AutoLayout();
}

uint32 spt::HmiUInt32DataDialog::Data()
{
	return Cur;
}

void spt::HmiIntDataEditDialog::AutoLayout()
{
	titleMaxLen = 8;
	inputMaxLen = Max(text[0].Text().StrLen(), text[1].Text().StrLen());
	inputMaxLen = Max((int32)inputMaxLen, text[2].Text().StrLen());
	lineCount = 4;
	text[2].SetCanBeSelect(1);
	lineWidth = inputMaxLen + 1 + titleMaxLen;
	HmiWidDialog::AutoLayout();
	titleMid.SetRect(rect.x + rect.w / 2 - titleMid.Text().StrLen() * gd->FontWidth() / 2, rect.y + gd->FontWidth() / 2 + gd->SpaceOfFont(), (titleMaxLen + 1) * gd->FontWidth(), gd->FontHeight() + gd->SpaceOfFont() * 2);
	AddChild(&titleMid);
	title[0].SetRect(rect.x + gd->FontWidth(), titleMid.Rect().y + gd->FontHeight() + gd->SpaceOfFont(), (titleMaxLen + 1) * gd->FontWidth(), gd->FontHeight() + gd->SpaceOfFont() * 2);
	text[0].SetRect(title[0].Rect().x + title[0].Rect().w, title[0].Rect().y, (inputMaxLen + 1) * gd->FontWidth(), title[0].Rect().h);
	AddChild(&title[0]);
	AddChild(&text[0]);
	for (uint32 i = 1; i < M_ArrLen(title); i++)
	{
		title[i].SetRect(title[i - 1].Rect().x, title[i - 1].Rect().y + gd->FontHeight() + gd->SpaceOfFont(), title[i - 1].Rect().w, title[i - 1].Rect().h);
		text[i].SetRect(title[0].Rect().x + title[0].Rect().w, title[i].Rect().y, text[i - 1].Rect().w, title[0].Rect().h);
		AddChild(&title[i]);
		AddChild(&text[i]);
	}
	selectIndex = text[2].Text().StrLen() - 1;
	curse.SetRect(text[2].Rect().x + gd->FontWidth() * selectIndex, text[2].Rect().y, gd->FontWidth(), gd->FontHeight());
	AddChild(&curse);
}

int32 spt::HmiIntDataEditDialog::ShowSelf()
{
	if (!isInied)
	{
		ClearRect();
		WidRect::ShowSelf();
	}
	if (isUpdate)
	{
		text[2].ClearRect();
		curse.SetPosX(text[2].Rect().x + gd->FontWidth() * selectIndex);
		String10B str;
		str << text[2].Text().Str()[selectIndex];
		curse.SetText(str.Str());
		curse.SetUpdateSelf(1);
	}
	return 0;
}

int32 spt::HmiHex32DataDialog::Edit()
{
	HmiKey key;
	char d = 0;
	uint8 minL = text[2].Text().StrLen() - 8;
	while (1)
	{
		if (this->key->Pop(key))
		{
			if (key.Key1 == EK1_KEYVALUE)
			{
				E_KEY2 k2 = (E_KEY2)key.Key2;
				switch (k2)
				{
				case spt::EK_ENTER:
				{
					TransString ts;
					ts.SetBuf(text[2].Text().Str());
					ts.GetHex(Cur, 0);
					if ((Cur >= Min) && (Cur <= Max))
					{
						ClearRect();
						gd->Update(rect);
						return E_OK;
					}
					else
					{
						HmiSelectDialog dig;
						dig.SetTitle("输入越限，请重新输入!", 0, 0, 0, 0);
						if (dig.Edit() == 0)
						{

						}
						else
						{
							Cur = Def;
							ClearRect();
							gd->Update(rect);
							return E_OK;
						}
					}
					SetInied(0);
					break;
				}
				case spt::EK_ESC:
					ClearRect();
					gd->Update(rect);
					return E_ESC;
					break;
				case spt::EK_LEFT:
					if (selectIndex)
					{
						selectIndex--;
						if (minL > selectIndex)
						{
							selectIndex++;
						}
					}
					SetUpdateSelf(1);
					break;
				case spt::EK_ADD:
				case spt::EK_UP:
					d = text[2].Text().Str()[selectIndex];
					if (d == 'F')
					{
						d = '0';
					}
					else  if ((d >= 'A') && (d < 'F'))
					{
						d++;
					}
					else if ((d >= '0') && (d < '9'))
					{
						d++;
					}
					else if (d == '9')
					{
						d = 'A';
					}
					text[2].SetText(selectIndex, d);
					SetUpdateSelf(1);
					break;
				case spt::EK_RIGHT:
					int32 r;
					r = selectIndex + 1;
					if (r < text[2].Text().StrLen())
					{
						selectIndex = r;
					}
					SetUpdateSelf(1);
					break;
				case spt::EK_SUB:
				case spt::EK_DOWN:
					d = text[2].Text().Str()[selectIndex];
					if (d == 'A')
					{
						d = '9';
					}
					else  if ((d > 'A') && (d <= 'F'))
					{
						d--;
					}
					else if ((d > '0') && (d <= '9'))
					{
						d--;
					}
					else if (d == '0')
					{
						d = 'F';
					}
					text[2].SetText(selectIndex, d);
					SetUpdateSelf(1);
					break;
				case spt::EK_MD_STOP:
					ClearRect();
					gd->Update(rect);
					return E_FORCE_ESC;
					break;
				default:
					break;
				}
			}
			else if (key.Key1 == EK1_ASSIC)
			{
				d = key.Key2;
				if ((d >= '0') && (d <= '9'))
				{
					text[2].SetText(selectIndex, d);
					SetUpdateSelf(1);
				}
				else if ((d >= 'A') && (d <= 'F'))
				{
					text[2].SetText(selectIndex, d);
					SetUpdateSelf(1);
				}
				else if ((d >= 'a') && (d <= 'f'))
				{
					text[2].SetText(selectIndex, d);
					SetUpdateSelf(1);
				}
			}
		}
		else
		{
			HmiMain::Instance().MsSleep(10);
		}
		HmiWidDialog::Show();
		Update();
	}
	ClearRect();
	gd->Update(rect);
	return 0;
}

spt::HmiHex32DataDialog::HmiHex32DataDialog()
{

}

void spt::HmiHex32DataDialog::Set(const char* Title, uint32 Min, uint32 Def, uint32 Max)
{
	this->Min = Min;
	Cur = this->Def = Def;
	this->Max = Max;
	titleMid.SetText(Title);
	String100B str;
	str.FormatHex(Max);
	text[0].SetText(str.Str());
	str.Clear();
	str.FormatHex(Min);
	text[1].SetText(str.Str());
	str.Clear();
	str.FormatHex(Def);
	text[2].SetText(str.Str());
	title[0].SetText("最大值:0x");
	title[1].SetText("最小值:0x");
	title[2].SetText("当前值:0x");
	AutoLayout();
}

uint32 spt::HmiHex32DataDialog::Data()
{
	return Cur;
}

int32 spt::HmiBit32DataDialog::Edit()
{
	AutoLayout();
	HmiKey key;
	SetPeriodUpdate(1, 200);
	char d = 0;
	uint8 minL = text[2].Text().StrLen() - DotNum;
	uint8 MaxL = text[2].Text().StrLen() - 1;
	BitNum = MaxL;
	while (1)
	{
		if (this->key->Pop(key))
		{
			if (key.Key1 == EK1_KEYVALUE)
			{
				E_KEY2 k2 = (E_KEY2)key.Key2;
				switch (k2)
				{
				case spt::EK_ENTER:
				{
					if ((Cur >= Min) && (Cur <= Max))
					{
						ClearRect();
						gd->Update(rect);
						return E_OK;
					}
					else
					{
						HmiSelectDialog dig;
						dig.SetTitle("输入越限，请重新输入!", 0, 0, 0, 0);
						if (dig.Edit() == 0)
						{

						}
						else
						{
							Cur = Def;
							ClearRect();
							gd->Update(rect);
							return E_OK;
						}
					}
					SetInied(0);
					break;
				}
				case spt::EK_ESC:
					ClearRect();
					gd->Update(rect);
					return E_ESC;
					break;
				case spt::EK_LEFT:
					if (selectIndex)
					{
						selectIndex--;
						if (minL > selectIndex)
						{
							selectIndex++;
						}
					}
					SetUpdateSelf(1);
					break;
				case spt::EK_ADD:
				case spt::EK_UP:
					if (GetBit(Cur, MaxL - selectIndex))
					{
						SetBit(Cur, MaxL - selectIndex, 0);
					}
					else
					{
						SetBit(Cur, MaxL - selectIndex, 1);
					}
					SetUpdateSelf(1);
					break;
				case spt::EK_RIGHT:
					int32 r;
					r = selectIndex + 1;
					if (r < text[2].Text().StrLen())
					{
						selectIndex = r;
					}
					SetUpdateSelf(1);
					break;
				case spt::EK_SUB:
				case spt::EK_DOWN:
					if (GetBit(Cur, MaxL - selectIndex))
					{
						SetBit(Cur, MaxL - selectIndex, 0);
					}
					else
					{
						SetBit(Cur, MaxL - selectIndex, 1);
					}
					SetUpdateSelf(1);
					break;
				case spt::EK_MD_STOP:
					ClearRect();
					gd->Update(rect);
					return E_FORCE_ESC;
					break;
				default:
					break;
				}
			}
			else if (key.Key1 == EK1_ASSIC)
			{
				d = key.Key2;
				if ((d == '0'))
				{
					SetBit(Cur, MaxL - selectIndex, 0);
				}
				else if (d == '1')
				{
					SetBit(Cur, MaxL - selectIndex, 1);
				}
				SetUpdateSelf(1);
			}
			HmiMain::Instance().MsSleep(50);
		}
		else
		{
			HmiMain::Instance().MsSleep(200);
		}
		HmiWidDialog::Show();
		Update();
	}
	ClearRect();
	gd->Update(rect);
	return 0;
}

spt::HmiBit32DataDialog::HmiBit32DataDialog()
{
}

void spt::HmiBit32DataDialog::Set(const char* Title, uint32 Min, uint32 Def, uint32 Max, SalBitDes* Des, uint8 BitLen)
{
	this->Des = Des;
	this->Min = Min;
	Cur = this->Def = Def;
	this->Max = Max;
	this->DotNum = BitLen;
	titleMid.SetText(Title);
	String100B str;
	str.FormatHex(Cur);
	text[0].SetText(str.Str());
	text[1].SetText(Des[0].des);
	str.Clear();
	str.FormatBin(Cur);
	text[2].SetText(str.Str());
	title[0].SetText("当前值:0x");
	title[1].SetText("比  特:");
	title[2].SetText("");

	titleMaxLen = 8;
	inputMaxLen = 21;
	lineCount = 4;
	lineWidth = inputMaxLen + 1 + titleMaxLen;
	HmiWidDialog::AutoLayout();
	titleMid.SetRect(rect.x + rect.w / 2 - titleMid.Text().StrLen() * gd->FontWidth() / 2, rect.y + gd->FontWidth() / 2 + gd->SpaceOfFont(), (titleMaxLen + 1) * gd->FontWidth(), gd->FontHeight() + gd->SpaceOfFont() * 2);
	AddChild(&titleMid);
	title[0].SetRect(rect.x + gd->FontWidth(), titleMid.Rect().y + gd->FontHeight() + gd->SpaceOfFont(), (titleMaxLen + 1) * gd->FontWidth(), gd->FontHeight() + gd->SpaceOfFont() * 2);
	text[0].SetRect(title[0].Rect().x + title[0].Rect().w, title[0].Rect().y, (inputMaxLen + 1) * gd->FontWidth(), title[0].Rect().h);
	AddChild(&title[0]);
	AddChild(&text[0]);
	title[1].SetPos(title[0].Rect().x, title[0].Rect().y + gd->FontHeight() + gd->SpaceOfFont());
	text[1].SetRect(title[0].Rect().x + title[0].Rect().w, title[1].Rect().y, text[0].Rect().w, text[0].Rect().h);
	AddChild(&text[1]);
	title[2].SetPos(title[1].Rect().x, title[1].Rect().y + gd->FontHeight() + gd->SpaceOfFont());
	text[2].SetRect(title[0].Rect().x + title[0].Rect().w, title[2].Rect().y, text[0].Rect().w, text[0].Rect().h);
	AddChild(&text[2]);
	curse.SetRect(text[2].Rect().x, text[2].Rect().y, gd->FontWidth(), gd->FontHeight());
	selectIndex = text[2].Text().StrLen() - 1;
	curse.SetPosX(text[2].Rect().x + gd->FontWidth() * selectIndex);
	str.Clear();
	str << text[2].Text().Str()[selectIndex];
	curse.SetText(str.Str());
	AddChild(&curse);
}

int32 spt::HmiBit32DataDialog::ShowSelf()
{
	if (!isInied)
	{
		ClearRect();
		WidRect::ShowSelf();
	}
	String100B str;
	curse.SetPosX(text[2].Rect().x + gd->FontWidth() * selectIndex);
	str.FormatHex(Cur);
	text[0].ClearRect();
	text[1].ClearRect();
	text[2].ClearRect();
	text[0].SetUpdateSelf(1);
	text[1].SetUpdateSelf(1);
	text[2].SetUpdateSelf(1);
	text[0].SetText(str.Str());
	text[1].SetText(Des[BitNum - selectIndex].des);
	str.Clear();
	str.FormatBin(Cur);
	text[2].SetText(str.Str());
	str.Clear();
	str << text[2].Text().Str()[selectIndex];
	curse.SetText(str.Str());
	return 0;
}

int32 spt::HmiEnum32DataDialog::Edit()
{
	HmiKey key;
	while (1)
	{
		if (this->key->Pop(key))
		{
			if (key.Key1 == EK1_KEYVALUE)
			{
				E_KEY2 k2 = (E_KEY2)key.Key2;
				switch (k2)
				{
				case spt::EK_ENTER:
				{
					if ((Cur >= Min) && (Cur <= Max))
					{
						ClearRect();
						gd->Update(rect);
						return E_OK;
					}
					else
					{
						HmiSelectDialog dig;
						dig.SetTitle("输入越限，请重新输入!", 0, 0, 0, 0);
						if (dig.Edit() == 0)
						{

						}
						else
						{
							Cur = Def;
							ClearRect();
							gd->Update(rect);
							return E_OK;
						}
					}
					SetInied(0);
					break;
				}
				case spt::EK_ESC:
					ClearRect();
					gd->Update(rect);
					return E_ESC;
					break;
				case spt::EK_LEFT:
					break;
				case spt::EK_ADD:
				case spt::EK_UP:
					if (Cur < Max)
					{
						Cur++;
					}
					text[2].SetText(Des[Cur].des);
					SetUpdateSelf(1);
					break;
				case spt::EK_RIGHT:

					break;
				case spt::EK_SUB:
				case spt::EK_DOWN:
					if (Cur > Min)
					{
						Cur--;
					}
					text[2].SetText(Des[Cur].des);
					SetUpdateSelf(1);
					break;
				case spt::EK_MD_STOP:
					ClearRect();
					gd->Update(rect);
					return E_FORCE_ESC;
					break;
				default:
					break;
				}
			}
			HmiMain::Instance().MsSleep(50);
		}
		else
		{
			HmiMain::Instance().MsSleep(200);
		}
		HmiWidDialog::Show();
		Update();
	}
	ClearRect();
	gd->Update(rect);
}

spt::HmiEnum32DataDialog::HmiEnum32DataDialog()
{
}

void spt::HmiEnum32DataDialog::Set(const char* Title, uint32 Min, uint32 Def, uint32 Max, SalEnumDes* Des)
{
	this->Des = Des;
	this->Min = Min;
	Cur = this->Def = Def;
	this->Max = Max;
	titleMid.SetText(Title);
	text[0].SetText(Des[Min].des);
	text[1].SetText(Des[Max].des);
	text[2].SetText(Des[Def].des);
	title[0].SetText("起始值:");
	title[1].SetText("结束值:");
	title[2].SetText("当前值:");

	titleMaxLen = 8;
	inputMaxLen = spt::Max(text[0].Text().StrLen(), text[1].Text().StrLen());
	inputMaxLen = spt::Max((int32)inputMaxLen, text[2].Text().StrLen());
	lineCount = 4;
	lineWidth = inputMaxLen + 1 + titleMaxLen;
	HmiWidDialog::AutoLayout();
	titleMid.SetRect(rect.x + rect.w / 2 - titleMid.Text().StrLen() * gd->FontWidth() / 2, rect.y + gd->FontWidth() / 2 + gd->SpaceOfFont(), (titleMaxLen + 1) * gd->FontWidth(), gd->FontHeight() + gd->SpaceOfFont() * 2);
	AddChild(&titleMid);
	title[0].SetRect(rect.x + gd->FontWidth(), titleMid.Rect().y + gd->FontHeight() + 2 * gd->SpaceOfFont(), (titleMaxLen + 1) * gd->FontWidth(), gd->FontHeight());
	text[0].SetRect(title[0].Rect().x + title[0].Rect().w, title[0].Rect().y, (inputMaxLen)*gd->FontWidth(), title[0].Rect().h);
	AddChild(&title[0]);
	AddChild(&text[0]);
	for (uint32 i = 1; i < M_ArrLen(title); i++)
	{
		title[i].SetRect(title[i - 1].Rect().x, title[i - 1].Rect().y + gd->FontHeight() + 2 * gd->SpaceOfFont(), title[i - 1].Rect().w, title[i - 1].Rect().h);
		text[i].SetRect(title[0].Rect().x + title[0].Rect().w, title[i].Rect().y, text[0].Rect().w, text[0].Rect().h);
		AddChild(&title[i]);
		AddChild(&text[i]);
	}
	text[2].Backcolor() = curse.Backcolor();
	text[2].Color() = curse.Color();
}

int32 spt::HmiEnum32DataDialog::ShowSelf()
{
	if (!isInied)
	{
		ClearRect();
		WidRect::ShowSelf();
	}
	text[2].ClearRect();
	text[2].SetUpdate(1);
	return 0;
}

void spt::HmiInfoDialog::SetTitle(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5)
{
	HmiInfoDialog::SetTitle(Str1, Str2, Str3, Str4, Str5, "请稍等------");
}

void spt::HmiInfoDialog::SetTitle(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5, const char* warn)
{
	lineWidth = 0;
	lineCount = 0;
	if (Str1)
	{
		title[lineCount].SetText(Str1);
		lineWidth = Max(title[lineCount].Text().StrLen(), (int32)lineWidth);
		lineCount++;
	}
	else
	{
		title[lineCount].SetText(warn);
		lineWidth = Max(title[lineCount].Text().StrLen(), (int32)lineWidth);
		lineCount++;
		return;
	}
	if (Str2)
	{
		title[lineCount].SetText(Str2);
		lineWidth = Max(title[lineCount].Text().StrLen(), (int32)lineWidth);
		lineCount++;
	}
	else
	{
		title[lineCount].SetText(warn);
		lineWidth = Max(title[lineCount].Text().StrLen(), (int32)lineWidth);
		lineCount++;
		return;
	}
	if (Str3)
	{
		title[lineCount].SetText(Str3);
		lineWidth = Max(title[lineCount].Text().StrLen(), (int32)lineWidth);
		lineCount++;
	}
	else
	{
		title[lineCount].SetText(warn);
		lineWidth = Max(title[lineCount].Text().StrLen(), (int32)lineWidth);
		lineCount++;
		return;
	}
	if (Str4)
	{
		title[lineCount].SetText(Str4);
		lineWidth = Max(title[lineCount].Text().StrLen(), (int32)lineWidth);
		lineCount++;
	}
	else
	{
		title[lineCount].SetText(warn);
		lineWidth = Max(title[lineCount].Text().StrLen(), (int32)lineWidth);
		lineCount++;
		return;
	}
	if (Str5)
	{
		title[lineCount].SetText(Str5);
		lineWidth = Max(title[lineCount].Text().StrLen(), (int32)lineWidth);
		lineCount++;
	}
	else
	{
		return;
	}
}

int32 spt::HmiInfoDialog::Edit()
{
	AutoLayout();
	ClearRect();
	HmiWidDialog::Show();
	Update();
	return 0;
}

int32 spt::HmiInfoDialog::ShowSelf()
{
	if (!isInied)
	{
		ClearRect();
		WidRect::ShowSelf();
	}
	HmiWidDialog::ShowSelf();
	return 0;
}
