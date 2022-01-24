#include"SptProject.h"
using namespace spt;
spt::HmiWidDialog::HmiWidDialog()
{
	SetVisible(1);
}

int32 spt::HmiWidDialog::EditSelf(HmiKeyMsg key)
{
	E_KEY2 k2 = (E_KEY2)key.key.Key2;
	if (key.key.Key1 != EK1_KEYVALUE)
	{
		key.isDealed = 1;
		return 0;
	}
	switch (k2)
	{
	case spt::EK_ENTER:
		return EditChild(key);
		break;
	case spt::EK_ESC:
		break;
	case spt::EK_LEFT:
	case spt::EK_UP:
		if (selectedChild && selectedChild->Last())
		{
			selectedChild = selectedChild->Last();
		}
		break;
	case spt::EK_RIGHT:
	case spt::EK_DOWN:
		if (selectedChild && selectedChild->Next())
		{
			selectedChild = selectedChild->Next();
		}
		break;
	case spt::EK_MD_STOP:
		break;
	default:
		break;
	}
	key.isDealed = 1;
	return 0;
}

void spt::HmiWidDialog::AutoLayout()
{
	rect.w = (lineWidth + 4) * gd->FontWidth();
	rect.h = (lineCount + 1) * (gd->FontHeight() + gd->SpaceOfFont());
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
}

void spt::HmiAssicInputDialog::AutoLayout()
{
	maxTextLine = 0;
	curse.Row = 0;
	curse.Col = 6;
	if (mode == E_Full)
	{
		text[0].Text() = "!@#$%^&*()-='?<>";
		text[1].Text() = "abcdefghijklmn";
		text[2].Text() = "opqrstuvwxyz_+|\\";
		text[3].Text() = "0123456789{}[]\x1B";
		text[4].Text() = "ABCDEFGHIJKLMN`'";
		text[5].Text() = "OPQRSTUVWXYZ,./~";
		maxTextLine = 6;
		curse.Row = 3;
		curse.Col = 6;
	}
	else if (mode == E_HEX)
	{
		text[0].Text() = "0123456789.";
		text[1].Text() = "ABCDEF\x1B";
		maxTextLine = 2;
	}
	else if (mode == E_Number)
	{
		text[0].Text() = "0123456789.\x1B";
		maxTextLine = 1;
	}
	lineCount = maxTextLine + 1;
	lineWidth = inputMaxLen;
	HmiWidDialog::AutoLayout();
	input.Rect().x = rect.x + gd->FontWidth();
	input.Rect().y = rect.y + gd->FontWidth() / 2 + gd->SpaceOfFont();
	input.Rect().w = (inputMaxLen + 2) * gd->FontWidth();
	input.Rect().h = gd->FontHeight() + gd->SpaceOfFont() * 2;
	input.SetVisible(1);
	AddChild(&input);
	text[0].Rect().w = (text[0].Text().StrLen() + 1) * gd->FontWidth();
	text[0].Rect().x = rect.x + rect.w / 2 - text[0].Rect().w / 2;
	text[0].Rect().y = input.Rect().YEnd() + gd->SpaceOfFont();
	text[0].Rect().h = gd->FontHeight() + gd->SpaceOfFont();
	text[0].SetVisible(1);
	AddChild(&text[0]);
	for (uint32 i = 1; i < maxTextLine; i++)
	{
		text[i].Rect().x = text[i - 1].Rect().x;
		text[i].Rect().y = text[i - 1].Rect().y + gd->FontHeight() + gd->SpaceOfFont();
		text[i].Rect().w = text[i - 1].Rect().w;
		text[i].Rect().h = text[i - 1].Rect().h;
		text[i].SetVisible(1);
		AddChild(&text[i]);
	}
	curse.IsCanBeSelect() = 1;
	curse.IsSelected() = 1;
}

spt::HmiAssicInputDialog::HmiAssicInputDialog(E_Mode Mode)
{
	isSelected = 1;
	isCanBeSelect = 1;
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
	maxTextLine = Max(inputMaxLen,(uint32) inputStr.StrLen());
}

void spt::HmiAssicInputDialog::Show(ShowType Type)
{
	input.IsUpdate() = 1;
	input.SetText(inputStr.Str());
	input.Text() << "_";
	curse.Text().Clear();
	curse.IsUpdate() = 1;
	curse.Text() << text[curse.Row].Text().Str()[curse.Col];
	curse.Rect() = text[curse.Row].Rect();
	curse.Rect().x += curse.Col * gd->FontWidth();
	curse.Rect().w = gd->FontWidth();
	HmiWidRect::Show(Type);
	curse.Show(Type);
}

int32 spt::HmiAssicInputDialog::Edit()
{
	HmiKey key;
	bool8 first = 1;
	MsPeriodTimer timer;
	timer.UpCnt(200);
	timer.Enable(1);
	AutoLayout();
	bool8 virok = HmiLcdCmm::Instance().IsVirLcdCmmOk();
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
						char d = text[curse.Row].Text().Str()[curse.Col];
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
						UnShow();
						gd->Update(rect);
						return E_OK;
					}
					break;
				}
				case spt::EK_ADD:
				{
					break;
				}
				case spt::EK_ESC:
					UnShow();
					gd->Update(rect);
					return E_ESC;
					break;
				case spt::EK_LEFT:
					if (curse.Col)
					{
						curse.Col--;
					}
					text[curse.Row].IsUpdate() = 1;
					break;
				case spt::EK_UP:
					text[curse.Row].IsUpdate() = 1;
					if (curse.Row)
					{
						curse.Row--;
					}
					if (curse.Col >= text[curse.Row].Text().StrLen())
					{
						curse.Col = text[curse.Row].Text().StrLen() - 1;
					}
					text[curse.Row].IsUpdate() = 1;
					break;
				case spt::EK_RIGHT:
					text[curse.Row].IsUpdate() = 1;
					curse.Col++;
					if (curse.Col >= text[curse.Row].Text().StrLen())
					{
						curse.Col = text[curse.Row].Text().StrLen() - 1;
					}
					break;
				case spt::EK_DOWN:
					text[curse.Row].IsUpdate() = 1;
					curse.Row++;
					if (curse.Row >= maxTextLine)
					{
						curse.Row--;
					}
					if (curse.Col >= text[curse.Row].Text().StrLen())
					{
						curse.Col = text[curse.Row].Text().StrLen() - 1;
					}
					text[curse.Row].IsUpdate() = 1;
					break;
				case spt::EK_MD_STOP:
					UnShow();
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
					}
					UnShow();
					gd->Update(rect);
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
			}
		}
		else
		{
			HmiMain::Instance().MsSleep(10);
		}
		if (first || timer.Status())
		{
			first = 0;
			Show(E_AllFrame);
			gd->Update(rect);
		}
	}
	UnShow();
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
		titleMaxLen = Max(title[lineCount].Text().StrLen(),(int32) titleMaxLen);
		text[lineCount].IsCanBeSelect() = 1;
		lineCount++;
	}
	else
	{
		return;
	}
	if (Str2)
	{
		title[lineCount].SetText(Str2);
		titleMaxLen = Max(title[lineCount].Text().StrLen(),(int32) titleMaxLen);
		text[lineCount].IsCanBeSelect() = 1;
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
		text[lineCount].IsCanBeSelect() = 1;
		lineCount++;
	}
	else
	{
		return;
	}
	if (Str4)
	{
		title[lineCount].SetText(Str4);
		titleMaxLen = Max(title[lineCount].Text().StrLen(),(int32) titleMaxLen);
		text[lineCount].IsCanBeSelect() = 1;
		lineCount++;
	}
	else
	{
		return;
	}
	if (Str5)
	{
		title[lineCount].SetText(Str5);
		titleMaxLen = Max(title[lineCount].Text().StrLen(),(int32) titleMaxLen);
		text[lineCount].IsCanBeSelect() = 1;
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
	text[0].IsCanBeSelect() = EditAble1;
	text[1].IsCanBeSelect() = EditAble2;
	text[2].IsCanBeSelect() = EditAble3;
	text[3].IsCanBeSelect() = EditAble4;
	text[4].IsCanBeSelect() = EditAble5;
}

void spt::HmiStrEditDialog::Show(ShowType Type)
{
	HmiWidRect::Show(Type);
}

void spt::HmiStrEditDialog::SetMaxInputLen(uint32 Len)
{
	inputMaxLen = Len;
}

int32 spt::HmiStrEditDialog::Edit()
{
	HmiKey key;
	bool8 first = 1;
	MsPeriodTimer timer;
	timer.UpCnt(200);
	timer.Enable(1);
	AutoLayout();
	SetSelectedChildAt(0);
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
					if (selectedChild && selectedChild->IsSelected())
					{
						HmiAssicInputDialog dig(HmiAssicInputDialog::E_Full);
						HmiWidTextLine* cur = (HmiWidTextLine*)selectedChild;
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
							selectedChild->GoToNextCanBeSelected();
						}
						first = 1;
					}
					break;
				}
				case spt::EK_ESC:
					UnShow();
					gd->Update(rect);
					return E_ESC;
					break;
				case spt::EK_LEFT:
					break;
				case spt::EK_UP:
					selectedChild->GoToLastCanBeSelected();
					break;
				case spt::EK_RIGHT:
					break;
				case spt::EK_DOWN:
					selectedChild->GoToNextCanBeSelected();
					break;
				case spt::EK_MD_STOP:
					UnShow();
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
		if (first)
		{
			first = 0;
			Show(E_AllFrame);
			gd->Update(rect);
		}
		if (timer.Status())
		{
			Show(E_Update);
			gd->Update(rect);
		}
	}
	UnShow();
	gd->Update(rect);
	return -1;
}

void spt::HmiStrEditDialog::AutoLayout()
{
	lineWidth = inputMaxLen + 1 + titleMaxLen;
	HmiWidDialog::AutoLayout();
	title[0].Rect().x = rect.x + gd->FontWidth();
	title[0].Rect().y = rect.y + gd->FontWidth() / 2 + gd->SpaceOfFont();
	title[0].Rect().w = (titleMaxLen + 1) * gd->FontWidth();
	title[0].Rect().h = gd->FontHeight() + gd->SpaceOfFont() * 2;
	text[0].Rect().w = (inputMaxLen + 1) * gd->FontWidth();
	text[0].Rect().x = title[0].Rect().x + title[0].Rect().w;
	text[0].Rect().h = title[0].Rect().h;
	text[0].Rect().y = title[0].Rect().y;
	title[0].SetVisible(1);
	text[0].SetVisible(1);
	AddChild(&title[0]);
	AddChild(&text[0]);
	for (uint32 i = 1; i < lineCount; i++)
	{
		title[i].Rect().x = title[i - 1].Rect().x;
		title[i].Rect().y = title[i - 1].Rect().y + gd->FontHeight() + gd->SpaceOfFont();
		title[i].Rect().w = title[i - 1].Rect().w;
		title[i].Rect().h = title[i - 1].Rect().h;

		text[i].Rect().w = text[i - 1].Rect().w;
		text[i].Rect().x = title[0].Rect().x + title[0].Rect().w;
		text[i].Rect().h = title[0].Rect().h;
		text[i].Rect().y = title[i].Rect().y;
		title[i].SetVisible(1);
		text[i].SetVisible(1);
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

void spt::HmiWarnDialog::SetTitle(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5)
{
	HmiInfoDialog::SetTitle(Str1, Str2, Str3, Str4, Str5, "按任意键继续");
}

void spt::HmiInfoDialog::AutoLayout()
{
	lineWidth = lineWidth;
	HmiWidDialog::AutoLayout();
	title[0].Rect().w = (title[0].Text().StrLen() + 1) * gd->FontWidth();
	title[0].Rect().x = rect.x + rect.w / 2 - title[0].Rect().w / 2;
	title[0].Rect().y = rect.y + gd->FontWidth() / 2 + gd->SpaceOfFont();
	title[0].Rect().h = gd->FontHeight() + gd->SpaceOfFont() * 2;
	title[0].SetVisible(1);
	AddChild(&title[0]);
	for (uint32 i = 1; i < lineCount; i++)
	{
		title[i].Rect().y = title[i - 1].Rect().y + gd->FontHeight() + gd->SpaceOfFont();
		title[i].Rect().w = (title[i].Text().StrLen() + 1) * gd->FontWidth();
		title[i].Rect().h = title[i - 1].Rect().h;
		title[i].Rect().x = rect.x + rect.w / 2 - title[i].Rect().w / 2;
		title[i].SetVisible(1);
		AddChild(&title[i]);
	}
}

int32 spt::HmiWarnDialog::Edit()
{
	HmiKey key;
	bool8 first = 1;
	MsPeriodTimer timer;
	timer.UpCnt(200);
	timer.Enable(1);
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
					UnShow();
					gd->Update(rect);
					return E_OK;
					break;
				case spt::EK_ESC:
					UnShow();
					gd->Update(rect);
					return E_ESC;
					break;
				case spt::EK_MD_STOP:
					UnShow();
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
		if (first)
		{
			first = 0;
			Show(E_AllFrame);
			gd->Update(rect);
		}
		if (timer.Status())
		{
			Show(E_Update);
			gd->Update(rect);
		}
	}
	UnShow();
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
	bool8 first = 1;
	MsPeriodTimer timer;
	timer.UpCnt(200);
	timer.Enable(1);
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
					UnShow();
					gd->Update(rect);
					return E_OK;
					break;
				case spt::EK_ESC:
					UnShow();
					gd->Update(rect);
					return E_ESC;
					break;
				case spt::EK_MD_STOP:
					UnShow();
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
		if (first)
		{
			first = 0;
			Show(E_AllFrame);
			gd->Update(rect);
		}
		if (timer.Status())
		{
			Show(E_Update);
			gd->Update(rect);
		}
	}
	UnShow();
	gd->Update(rect);
	return -1;
}

int32 spt::HmiTimeEditDialog::Edit()
{
	selectIndex = 0;
	HmiKey key;
	bool8 first = 1;
	MsPeriodTimer timer;
	timer.UpCnt(200);
	timer.Enable(1);
	AutoLayout();
	char d;
	SetSelectedChildAt(0);
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
					first = 1;
					UnShow();
					gd->Update(rect);
					UpdateDate();
					return E_OK;
				}
				case spt::EK_ESC:
					UnShow();
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
					curse.Text().Clear();
					curse.Text() << text[0].Text().Str()[selectIndex];
					curse.Rect().x = text[0].Rect().x + gd->FontWidth() * selectIndex;
					curse.SetUpdate();
					text[0].SetUpdate();
					title[0].SetUpdate();
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
					text[0].Text().Str()[selectIndex] = d;
					curse.Text().Clear();
					curse.Text() << d;
					curse.SetUpdate();
					text[0].SetUpdate();
					title[0].SetUpdate();
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
					curse.Text().Clear();
					curse.Text() << text[0].Text().Str()[selectIndex];
					curse.Rect().x = text[0].Rect().x + gd->FontWidth() * selectIndex;
					curse.SetUpdate();
					text[0].SetUpdate();
					title[0].SetUpdate();
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
					text[0].Text().Str()[selectIndex] = d;
					curse.Text().Clear();
					curse.Text() << d;
					curse.SetUpdate();
					text[0].SetUpdate();
					title[0].SetUpdate();
					break;
				case spt::EK_MD_STOP:
					UnShow();
					gd->Update(rect);
					UpdateDate();
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
		if (first)
		{
			first = 0;
			Show(E_AllFrame);
			gd->Update(rect);
		}
		if (timer.Status())
		{
			Show(E_Update);
			gd->Update(rect);
		}
	}
	UnShow();
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
	title[0].Rect().x = rect.x + gd->FontWidth();
	title[0].Rect().y = rect.y + gd->FontWidth() / 2 + gd->SpaceOfFont();
	title[0].Rect().w = (titleMaxLen + 1) * gd->FontWidth();
	title[0].Rect().h = gd->FontHeight() + gd->SpaceOfFont() * 2;
	text[0].Rect().w = (inputMaxLen + 1) * gd->FontWidth();
	text[0].Rect().x = title[0].Rect().x + title[0].Rect().w;
	text[0].Rect().h = title[0].Rect().h;
	text[0].Rect().y = title[0].Rect().y;
	text[0].Text().Clear();
	date.ToStrHzFmt1(text[0].Text());
	title[0].SetVisible(1);
	text[0].SetVisible(1);
	AddChild(&title[0]);
	AddChild(&text[0]);
	curse.Rect() = text[0].Rect();
	curse.Rect().w = gd->FontWidth();
	selectIndex = text[0].Text().StrLen() - 1;
	curse.Rect().x = text[0].Rect().x + gd->FontWidth() * selectIndex;
	curse.Text().Clear();
	curse.Text() << text[0].Text().Str()[selectIndex];
	AddChild(&curse);
	curse.IsSelected() = 1;
}

spt::HmiTimeEditDialog::HmiTimeEditDialog()
{
	dataNum = 6;
	text[0].SetText("    年  月  日  :  :  ");
	inputMaxLen = text[0].Text().StrLen();
	titleMaxLen = 0;
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
	bool8 first = 1;
	MsPeriodTimer timer;
	timer.UpCnt(200);
	timer.Enable(1);
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
						UnShow();
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
							UnShow();
							gd->Update(rect);
							return E_OK;
						}
					}
					break;
				}
				case spt::EK_ESC:
					UnShow();
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
							text[2].Text().Str()[selectIndex] = '0';
						}
					}
					curse.Rect().x = text[2].Rect().x + gd->FontWidth() * selectIndex;
					curse.Text().Clear();
					curse.Text() << text[2].Text().Str()[selectIndex];
					text[2].IsUpdate() = 1;
					curse.IsUpdate() = 1;
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
					text[2].Text().Str()[selectIndex] = d;
					curse.Text().Clear();
					curse.Text() << d;
					text[2].IsUpdate() = 1;
					curse.IsUpdate() = 1;
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
					curse.Rect().x = text[2].Rect().x + gd->FontWidth() * selectIndex;
					curse.Text().Clear();
					curse.Text() << text[2].Text().Str()[selectIndex];
					text[2].IsUpdate() = 1;
					curse.IsUpdate() = 1;
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
					text[2].Text().Str()[selectIndex] = d;
					curse.Text().Clear();
					curse.Text() << d;
					text[2].IsUpdate() = 1;
					curse.IsUpdate() = 1;
					break;
				case spt::EK_MD_STOP:
					UnShow();
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
					text[2].Text().Str()[selectIndex] = d;
					curse.Text().Clear();
					curse.Text() << d;
				}
				text[2].IsUpdate() = 1;
				curse.IsUpdate() = 1;
			}
		}
		else
		{
			HmiMain::Instance().MsSleep(10);
		}
		if (first || timer.Status())
		{
			first = 0;
			Show(E_AllFrame);
			gd->Update(rect);
		}
	}
	UnShow();
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
	text[0].Text().Format(Max, 11, DotNum, 0, ' ');
	text[1].Text().Format(Min, 11, DotNum, 0, ' ');
	text[2].Text().Format(Def, 11, DotNum, 0, ' ');
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
	bool8 first = 1;
	MsPeriodTimer timer;
	timer.UpCnt(200);
	timer.Enable(1);
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
						UnShow();
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
							UnShow();
							gd->Update(rect);
							return E_OK;
						}
					}
					break;
				}
				case spt::EK_ESC:
					UnShow();
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
							text[2].Text().Str()[selectIndex] = '0';
						}
					}
					curse.Rect().x = text[2].Rect().x + gd->FontWidth() * selectIndex;
					curse.Text().Clear();
					curse.Text() << text[2].Text().Str()[selectIndex];
					text[2].IsUpdate() = 1;
					curse.IsUpdate() = 1;
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
					text[2].Text().Str()[selectIndex] = d;
					curse.Text().Clear();
					curse.Text() << d;
					text[2].IsUpdate() = 1;
					curse.IsUpdate() = 1;
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
					curse.Rect().x = text[2].Rect().x + gd->FontWidth() * selectIndex;
					curse.Text().Clear();
					curse.Text() << text[2].Text().Str()[selectIndex];
					text[2].IsUpdate() = 1;
					curse.IsUpdate() = 1;
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
					text[2].Text().Str()[selectIndex] = d;
					curse.Text().Clear();
					curse.Text() << d;
					text[2].IsUpdate() = 1;
					curse.IsUpdate() = 1;
					break;
				case spt::EK_MD_STOP:
					UnShow();
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
					text[2].Text().Str()[selectIndex] = d;
					curse.Text().Clear();
					curse.Text() << d;
				}
				text[2].IsUpdate() = 1;
				curse.IsUpdate() = 1;
			}
		}
		else
		{
			HmiMain::Instance().MsSleep(10);
		}
		if (first || timer.Status())
		{
			first = 0;
			Show(E_AllFrame);
			gd->Update(rect);
		}
	}
	UnShow();
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
	text[0].Text().Format(Max, 11, DotNum, 0, ' ');
	text[1].Text().Format(Min, 11, DotNum, 0, ' ');
	text[2].Text().Format(Def, 11, DotNum, 0, ' ');
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
	text[2].IsCanBeSelect() = 1;
	lineWidth = inputMaxLen + 1 + titleMaxLen;
	HmiWidDialog::AutoLayout();
	titleMid.Rect().x = rect.x + rect.w / 2 - titleMid.Text().StrLen() * gd->FontWidth() / 2;
	titleMid.Rect().y = rect.y + gd->FontWidth() / 2 + gd->SpaceOfFont();
	titleMid.Rect().w = (titleMaxLen + 1) * gd->FontWidth();
	titleMid.Rect().h = gd->FontHeight() + gd->SpaceOfFont() * 2;
	titleMid.SetVisible(1);
	AddChild(&titleMid);
	title[0].Rect().x = rect.x + gd->FontWidth();
	title[0].Rect().y = titleMid.Rect().y + gd->FontHeight() + gd->SpaceOfFont();
	title[0].Rect().w = (titleMaxLen + 1) * gd->FontWidth();
	title[0].Rect().h = gd->FontHeight() + gd->SpaceOfFont() * 2;
	text[0].Rect().w = (inputMaxLen + 1) * gd->FontWidth();
	text[0].Rect().x = title[0].Rect().x + title[0].Rect().w;
	text[0].Rect().h = title[0].Rect().h;
	text[0].Rect().y = title[0].Rect().y;
	title[0].SetVisible(1);
	text[0].SetVisible(1);
	AddChild(&title[0]);
	AddChild(&text[0]);
	for (uint32 i = 1; i < M_ArrLen(title); i++)
	{
		title[i].Rect().x = title[i - 1].Rect().x;
		title[i].Rect().y = title[i - 1].Rect().y + gd->FontHeight() + gd->SpaceOfFont();
		title[i].Rect().w = title[i - 1].Rect().w;
		title[i].Rect().h = title[i - 1].Rect().h;

		text[i].Rect().w = text[i - 1].Rect().w;
		text[i].Rect().x = title[0].Rect().x + title[0].Rect().w;
		text[i].Rect().h = title[0].Rect().h;
		text[i].Rect().y = title[i].Rect().y;
		title[i].SetVisible(1);
		text[i].SetVisible(1);
		AddChild(&title[i]);
		AddChild(&text[i]);
	}
	curse.Rect() = text[2].Rect();
	curse.Rect().w = gd->FontWidth();
	curse.Text().Clear();
	selectIndex = text[2].Text().StrLen() - 1;
	curse.Rect().x = text[2].Rect().x + gd->FontWidth() * selectIndex;
	curse.Text() << text[2].Text().Str()[selectIndex];
	AddChild(&curse);
	curse.IsSelected() = 1;
}

int32 spt::HmiHex32DataDialog::Edit()
{
	HmiKey key;
	bool8 first = 1;
	MsPeriodTimer timer;
	timer.UpCnt(200);
	timer.Enable(1);
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
						UnShow();
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
							UnShow();
							gd->Update(rect);
							return E_OK;
						}
					}
					break;
				}
				case spt::EK_ESC:
					UnShow();
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
					curse.Rect().x = text[2].Rect().x + gd->FontWidth() * selectIndex;
					curse.Text().Clear();
					curse.Text() << text[2].Text().Str()[selectIndex];
					text[2].IsUpdate() = 1;
					curse.IsUpdate() = 1;
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
					text[2].Text().Str()[selectIndex] = d;
					curse.Text().Clear();
					curse.Text() << d;
					text[2].IsUpdate() = 1;
					curse.IsUpdate() = 1;
					break;
				case spt::EK_RIGHT:
					int32 r;
					r = selectIndex + 1;
					if (r < text[2].Text().StrLen())
					{
						selectIndex = r;
					}
					curse.Rect().x = text[2].Rect().x + gd->FontWidth() * selectIndex;
					curse.Text().Clear();
					curse.Text() << text[2].Text().Str()[selectIndex];
					text[2].IsUpdate() = 1;
					curse.IsUpdate() = 1;
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
					text[2].Text().Str()[selectIndex] = d;
					curse.Text().Clear();
					curse.Text() << d;
					text[2].IsUpdate() = 1;
					curse.IsUpdate() = 1;
					break;
				case spt::EK_MD_STOP:
					UnShow();
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
					text[2].Text().Str()[selectIndex] = d;
					curse.Text().Clear();
					curse.Text() << d;
				}
				else if ((d >= 'A') && (d <= 'F'))
				{
					text[2].Text().Str()[selectIndex] = d;
					curse.Text().Clear();
					curse.Text() << d;
				}
				else if ((d >= 'a') && (d <= 'f'))
				{
					text[2].Text().Str()[selectIndex] = d - 'a' + 'A';
					curse.Text().Clear();
					curse.Text() << d;
				}
				text[2].IsUpdate() = 1;
				curse.IsUpdate() = 1;
			}
		}
		else
		{
			HmiMain::Instance().MsSleep(10);
		}
		if (first || timer.Status())
		{
			first = 0;
			Show(E_AllFrame);
			gd->Update(rect);
		}
	}
	UnShow();
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
	text[0].Text().FormatHex(Max);
	text[1].Text().FormatHex(Min);
	text[2].Text().FormatHex(Def);
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
	HmiKey key;
	bool8 first = 1;
	MsPeriodTimer timer;
	timer.UpCnt(200);
	timer.Enable(1);
	char d = 0;
	uint8 minL = text[2].Text().StrLen() - DotNum;
	uint8 MaxL = text[2].Text().StrLen() - 1;
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
						UnShow();
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
							UnShow();
							gd->Update(rect);
							return E_OK;
						}
					}
					break;
				}
				case spt::EK_ESC:
					UnShow();
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
					curse.Rect().x = text[2].Rect().x + gd->FontWidth() * selectIndex;
					text[1].SetText(Des[MaxL - selectIndex].des);
					text[2].Text().Clear();
					text[2].Text().FormatBin(Cur);
					curse.Text().Clear();
					curse.Text() << text[2].Text().Str()[selectIndex];
					text[2].IsUpdate() = 1;
					curse.IsUpdate() = 1;
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
					text[0].Text().Clear();
					text[0].Text().FormatHex(Cur);
					text[2].Text().Clear();
					text[2].Text().FormatBin(Cur);
					curse.Text().Clear();
					curse.Text() << text[2].Text().Str()[selectIndex];
					text[2].IsUpdate() = 1;
					curse.IsUpdate() = 1;
					break;
				case spt::EK_RIGHT:
					int32 r;
					r = selectIndex + 1;
					if (r < text[2].Text().StrLen())
					{
						selectIndex = r;
					}
					curse.Rect().x = text[2].Rect().x + gd->FontWidth() * selectIndex;
					text[1].SetText(Des[MaxL - selectIndex].des);
					text[2].Text().Clear();
					text[2].Text().FormatBin(Cur);
					curse.Text().Clear();
					curse.Text() << text[2].Text().Str()[selectIndex];
					text[2].IsUpdate() = 1;
					curse.IsUpdate() = 1;
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
					text[0].Text().Clear();
					text[0].Text().FormatHex(Cur);
					text[2].Text().Clear();
					text[2].Text().FormatBin(Cur);
					curse.Text().Clear();
					curse.Text() << text[2].Text().Str()[selectIndex];
					text[2].IsUpdate() = 1;
					curse.IsUpdate() = 1;
					break;
				case spt::EK_MD_STOP:
					UnShow();
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
				text[0].Text().Clear();
				text[0].Text().FormatHex(Cur);
				text[2].Text().Clear();
				text[2].Text().FormatBin(Cur);
				curse.Text().Clear();
				curse.Text() << text[2].Text().Str()[selectIndex];
				text[2].IsUpdate() = 1;
				curse.IsUpdate() = 1;
				text[2].IsUpdate() = 1;
				curse.IsUpdate() = 1;
			}
		}
		else
		{
			HmiMain::Instance().MsSleep(10);
		}
		if (first || timer.Status())
		{
			first = 0;
			Show(E_AllFrame);
			gd->Update(rect);
		}
	}
	UnShow();
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
	text[0].Text().FormatHex(Def);
	text[1].Text() << Des[0].des;
	text[2].Text().FormatBin(Def);
	title[0].SetText("当前值:0x");
	title[1].SetText("比特:");
	title[2].SetText("");

	titleMaxLen = 8;
	inputMaxLen = 21;
	lineCount = 4;
	text[2].IsCanBeSelect() = 1;
	lineWidth = inputMaxLen + 1 + titleMaxLen;
	HmiWidDialog::AutoLayout();
	titleMid.Rect().x = rect.x + rect.w / 2 - titleMid.Text().StrLen() * gd->FontWidth() / 2;
	titleMid.Rect().y = rect.y + gd->FontWidth() / 2 + gd->SpaceOfFont();
	titleMid.Rect().w = (titleMaxLen + 1) * gd->FontWidth();
	titleMid.Rect().h = gd->FontHeight() + gd->SpaceOfFont() * 2;
	titleMid.SetVisible(1);
	AddChild(&titleMid);
	title[0].Rect().x = rect.x + gd->FontWidth();
	title[0].Rect().y = titleMid.Rect().y + gd->FontHeight() + gd->SpaceOfFont();
	title[0].Rect().w = (titleMaxLen + 1) * gd->FontWidth();
	title[0].Rect().h = gd->FontHeight() + gd->SpaceOfFont() * 2;
	text[0].Rect().w = (inputMaxLen + 1) * gd->FontWidth();
	text[0].Rect().x = title[0].Rect().x + title[0].Rect().w;
	text[0].Rect().h = title[0].Rect().h;
	text[0].Rect().y = title[0].Rect().y;
	title[0].SetVisible(1);
	text[0].SetVisible(1);
	AddChild(&title[0]);
	AddChild(&text[0]);
	title[1].Rect().x = title[0].Rect().x;
	title[1].Rect().y = title[0].Rect().y + gd->FontHeight() + gd->SpaceOfFont();
	text[1].Rect().y = title[1].Rect().y;
	text[1].Rect().x = title[1].Rect().x;
	text[1].SetVisible(1);
	AddChild(&text[1]);
	title[2].Rect().x = title[1].Rect().x;
	title[2].Rect().y = title[1].Rect().y + gd->FontHeight() + gd->SpaceOfFont();
	text[2].Rect().y = title[2].Rect().y;
	text[2].Rect().x = title[2].Rect().x;
	text[2].SetVisible(1);
	AddChild(&text[2]);
	curse.Rect() = text[2].Rect();
	curse.Rect().w = gd->FontWidth();
	curse.Rect().h = gd->FontHeight() + gd->SpaceOfFont();
	curse.Text().Clear();
	selectIndex = text[2].Text().StrLen() - 1;
	curse.Rect().x = text[2].Rect().x + gd->FontWidth() * selectIndex;
	curse.Text() << text[2].Text().Str()[selectIndex];
	AddChild(&curse);
	curse.IsSelected() = 1;
}

int32 spt::HmiEnum32DataDialog::Edit()
{
	HmiKey key;
	bool8 first = 1;
	MsPeriodTimer timer;
	timer.UpCnt(200);
	timer.Enable(1);
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
						UnShow();
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
							UnShow();
							gd->Update(rect);
							return E_OK;
						}
					}
					break;
				}
				case spt::EK_ESC:
					UnShow();
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
					break;
				case spt::EK_MD_STOP:
					UnShow();
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
		if (first || timer.Status())
		{
			first = 0;
			Show(E_AllFrame);
			gd->Update(rect);
		}
	}
	UnShow();
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
	text[0].Text() = Des[Min].des;
	text[1].Text() = Des[Max].des;
	text[2].Text() = Des[Def].des;
	title[0].SetText("起始值:");
	title[1].SetText("结束值:");
	title[2].SetText("当前值:");

	titleMaxLen = 8;
	inputMaxLen = spt::Max(text[0].Text().StrLen(), text[1].Text().StrLen());
	inputMaxLen = spt::Max((int32)inputMaxLen, text[2].Text().StrLen());
	lineCount = 4;
	text[2].IsCanBeSelect() = 1;
	lineWidth = inputMaxLen + 1 + titleMaxLen;
	HmiWidDialog::AutoLayout();
	titleMid.Rect().x = rect.x + rect.w / 2 - titleMid.Text().StrLen() * gd->FontWidth() / 2;
	titleMid.Rect().y = rect.y + gd->FontWidth() / 2 + gd->SpaceOfFont();
	titleMid.Rect().w = (titleMaxLen + 1) * gd->FontWidth();
	titleMid.Rect().h = gd->FontHeight() + gd->SpaceOfFont() * 2;
	titleMid.SetVisible(1);
	AddChild(&titleMid);
	title[0].Rect().x = rect.x + gd->FontWidth();
	title[0].Rect().y = titleMid.Rect().y + gd->FontHeight() + gd->SpaceOfFont();
	title[0].Rect().w = (titleMaxLen + 1) * gd->FontWidth();
	title[0].Rect().h = gd->FontHeight() + gd->SpaceOfFont() * 2;
	text[0].Rect().w = (inputMaxLen + 1) * gd->FontWidth();
	text[0].Rect().x = title[0].Rect().x + title[0].Rect().w;
	text[0].Rect().h = title[0].Rect().h;
	text[0].Rect().y = title[0].Rect().y;
	title[0].SetVisible(1);
	text[0].SetVisible(1);
	AddChild(&title[0]);
	AddChild(&text[0]);
	for (uint32 i = 1; i < M_ArrLen(title); i++)
	{
		title[i].Rect().x = title[i - 1].Rect().x;
		title[i].Rect().y = title[i - 1].Rect().y + gd->FontHeight() + gd->SpaceOfFont();
		title[i].Rect().w = title[i - 1].Rect().w;
		title[i].Rect().h = title[i - 1].Rect().h;

		text[i].Rect().w = text[i - 1].Rect().w;
		text[i].Rect().x = title[0].Rect().x + title[0].Rect().w;
		text[i].Rect().h = title[0].Rect().h;
		text[i].Rect().y = title[i].Rect().y;
		title[i].SetVisible(1);
		text[i].SetVisible(1);
		AddChild(&title[i]);
		AddChild(&text[i]);
	}
	text[2].IsSelected() = 1;
	text[2].Rect().w = text[2].Text().StrLen() * gd->FontWidth();
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
		lineWidth = Max(title[lineCount].Text().StrLen(),(int32) lineWidth);
		lineCount++;
		return;
	}
	if (Str3)
	{
		title[lineCount].SetText(Str3);
		lineWidth = Max(title[lineCount].Text().StrLen(),(int32) lineWidth);
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
		lineWidth = Max(title[lineCount].Text().StrLen(),(int32) lineWidth);
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
	Show(E_Update);
	gd->Update(rect);
	return 0;
}
