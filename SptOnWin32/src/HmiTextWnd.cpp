#include "SptProject.h"
using namespace spt;
HmiTextWndCell spt::HmiTextWnd::text[CN_Max_WndCell];
spt::HmiTextWnd::HmiTextWnd(DispType Mode)
{
	updateFunc = 0;
	firstTextPage = 0;
	mode = Mode;
	IniAllPage();
	context.SetVisible(1);
	title.SetVisible(1);
	for (uint32 i = 0; i < CN_Max_WndCell; i++)
	{
		text[i].ResetStatus();
		text[i].Text().Clear();
	}
	scrollPage.ResetStatus();
	scrollPage.Text().Clear();
	context.AddChild(&scrollPage);
}

void spt::HmiTextWnd::SetPage(uint32 Page, const char* Text)
{
	HmiTextWndCell* cell = GetWndCell(Page % CN_Max_WndCell);
	if (cell)
	{
		cell->IsEnable() = 1;
		cell->SetText(Text);
		cell->SetDispPageNum(Page);
		cell->SetVisible(1);
	}
}

void spt::HmiTextWnd::Show()
{
	HmiWidSinglePage::AutoLayerOut();
	if (mode == E_SinglePage)
	{
		ShowSinglePage();
	}
	else if (mode == E_ScrollPage)
	{
		ShowScrollPage();
	}
	else if (mode == E_ContinuePage)
	{
		ShowContinuePage();
	}
}

void spt::HmiTextWnd::IniAllPage()
{
	for (uint32 i = 0; i < CN_Max_WndCell; i++)
	{
		text[i].IsEnable() = 0;
		text[i].IsVisible() = 0;
		text[i].IsUpdate() = 0;
		text[i].SetFirstDispLine(0);
	}
	scrollPage.IsEnable() = 0;
	scrollPage.SetFirstDispLine(0);
}


HmiTextWndCell* spt::HmiTextWnd::GetWndCell(uint32 Index)
{
	if (Index < M_ArrLen(text))
	{
		return &text[Index];
	}
	return 0;
}

void spt::HmiTextWnd::SetFirstTextPage(uint16 Page)
{
	firstTextPage = Page;
}

uint16 spt::HmiTextWnd::FirstTextPage()
{
	return firstTextPage;
}

void spt::HmiTextWnd::AutoLayerOut()
{
	if (mode == E_SinglePage)
	{
		uint32 firstindex = (firstTextPage + title.Page()) % CN_Max_WndCell;
		if (((text[firstindex].DispPageNum() == (title.Page()))))
		{
			scrollPage.SetText(text[firstindex].Text().Str());
		}
		else
		{
			scrollPage.SetText(0);
		}
		scrollPage.Row = scrollPage.Col = 0;
		scrollPage.SetVisible(1);
	}
	else if (mode == E_ScrollPage)
	{
		uint32 firstindex = (firstTextPage + title.Page()) % CN_Max_WndCell;
		if (((text[firstindex].DispPageNum() == (title.Page()))))
		{
			scrollPage.SetText(text[firstindex].Text().Str());
			uint32 page = title.Page();
			for (uint32 i = 1; i < CN_Max_WndCell; i++)
			{
				uint32 index = (firstindex + i) % CN_Max_WndCell;
				if (text[index].DispPageNum() != (page + i))
				{
					break;
				}
				if (text[index].IsEnable() && text[index].IsVisible())
				{
					scrollPage.Text() << text[index].Text();
				}
				if (scrollPage.LineNum() > context.MaxDispRowNum())
				{
					break;
				}
			}
		}
		else
		{
			scrollPage.SetText(0);
		}
		scrollPage.Row = scrollPage.Col = 0;
		scrollPage.SetVisible(1);
	}
	else if (mode == E_ContinuePage)
	{
		uint32 firstindex = (firstTextPage + title.Page()) % CN_Max_WndCell;
		if (((text[firstindex].DispPageNum() == (title.Page()))))
		{
			scrollPage.SetText(text[firstindex].Text().Str());
		}
		else
		{
			scrollPage.SetText(0);
		}
		scrollPage.Row = scrollPage.Col = 0;
		scrollPage.SetVisible(1);
		scrollPage.SetFirstDispLine(curLine);
		totalLine = scrollPage.LineNum();
		title.SetLine(curLine, totalLine);
		title.SetUpdate();
	}
}

void spt::HmiTextWnd::ShowSinglePage()
{
	HmiKey key;
	bool8 first = 1;
	MsStampTimer timer;
	timer.Enable(1);
	uint32 total;
	uint32 step;
	uint32 page;
	if (updateFunc)
	{
		key.Key1 = 0;
		updateFunc(*this, 0, title.TotalPage(), key);
	}
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
					first = 1;
					break;
				case spt::EK_LEFT:
					total = title.TotalPage();
					step = total / 10;
					if (!step)
					{
						step = 1;
					}
					page = title.Page();
					if (page > step)
					{
						page = page - step;
					}
					else
					{
						page = 0;
					}
					title.SetPage(page, total);
					first = 1;
					if (updateFunc)
					{
						updateFunc(*this, page, total, key);
					}
					break;
				case spt::EK_UP:
					total = title.TotalPage();
					step = 1;
					page = title.Page();
					if (page >= step)
					{
						page = page - step;
					}
					else
					{
						page = total - step;
					}
					title.SetPage(page, total);
					first = 1;
					if (updateFunc)
					{
						updateFunc(*this, page, total, key);
					}
					break;
				case spt::EK_RIGHT:
					total = title.TotalPage();
					step = total / 10;
					if (!step)
					{
						step = 1;
					}
					page = title.Page() + step;
					if (page >= total)
					{
						page = total - 1;
					}
					title.SetPage(page, total);
					first = 1;
					if (updateFunc)
					{
						updateFunc(*this, page, total, key);
					}
					break;
				case spt::EK_DOWN:
					total = title.TotalPage();
					step = 1;
					page = title.Page() + step;
					if (page >= total)
					{
						page = 0;
					}
					title.SetPage(page, total);
					first = 1;
					if (updateFunc)
					{
						updateFunc(*this, page, total, key);
					}
					break;
				case spt::EK_ESC:
					UnShow();
					gd->Update(rect);
					return;
				case spt::EK_MD_STOP:
					UnShow();
					gd->Update(rect);
					return;
				default:
					break;
				}
			}
			else if (updateFunc)
			{
				total = title.TotalPage();
				page = title.Page();
				if (key.Key1 == EK1_ASSIC)
				{
					updateFunc(*this, page, total, key);
					first = 1;
				}
			}
		}
		else
		{
			HmiMain::Instance().MsSleep(50);
		}
		if (timer.Status(100))
		{
			if (first)
			{
				first = 0;
				AutoLayerOut();
				HmiWidSinglePage::Show(E_AllFrame);
				gd->Update(rect);
				timer.StartTimer();
			}
			else if (timer.Status(2000))
			{
				HmiWidSinglePage::Show(E_Update);
				gd->Update(rect);
				timer.StartTimer();
			}
		}
	}
	UnShow();
	gd->Update(rect);
	return;
}

void spt::HmiTextWnd::ShowScrollPage()
{
	HmiKey key;
	bool8 first = 1;
	MsStampTimer timer;
	timer.Enable(1);
	uint32 total;
	uint32 step;
	uint32 page;
	if (updateFunc)
	{
		key.Key1 = 0;
		updateFunc(*this, 0, title.TotalPage(), key);
	}
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
					first = 1;
					break;
				case spt::EK_LEFT:
					total = title.TotalPage();
					step = total / 10;
					if (!step)
					{
						step = 1;
					}
					page = title.Page();
					if (page > step)
					{
						page = page - step;
					}
					else
					{
						page = 0;
					}
					title.SetPage(page, total);
					first = 1;
					if (updateFunc)
					{
						updateFunc(*this, page, total, key);
					}
					break;
				case spt::EK_UP:
					total = title.TotalPage();
					step = 1;
					page = title.Page();
					if (page >= step)
					{
						page = page - step;
					}
					else
					{
						page = total - step;
					}
					title.SetPage(page, total);
					first = 1;
					if (updateFunc)
					{
						updateFunc(*this, page, total, key);
					}
					break;
				case spt::EK_RIGHT:
					total = title.TotalPage();
					step = total / 10;
					if (!step)
					{
						step = 1;
					}
					page = title.Page() + step;
					if (page >= total)
					{
						page = total - 1;
					}
					title.SetPage(page, total);
					first = 1;
					if (updateFunc)
					{
						updateFunc(*this, page, total, key);
					}
					break;
				case spt::EK_DOWN:
					total = title.TotalPage();
					step = 1;
					page = title.Page() + step;
					if (page >= total)
					{
						page = 0;
					}
					title.SetPage(page, total);
					first = 1;
					if (updateFunc)
					{
						updateFunc(*this, page, total, key);
					}
					break;
				case spt::EK_ESC:
					UnShow();
					gd->Update(rect);
					return;
				case spt::EK_MD_STOP:
					UnShow();
					gd->Update(rect);
					return;
				default:

					break;
				}
			}
			else if (updateFunc)
			{
				total = title.TotalPage();
				page = title.Page();
				if (key.Key1 == EK1_ASSIC)
				{
					updateFunc(*this, page, total, key);
					first = 1;
				}
			}
		}
		else
		{
			HmiMain::Instance().MsSleep(50);
		}
		if (timer.Status(100))
		{
			if (first)
			{
				first = 0;
				AutoLayerOut();
				HmiWidSinglePage::Show(E_AllFrame);
				gd->Update(rect);
				timer.StartTimer();
			}
			else if (timer.Status(2000))
			{
				HmiWidSinglePage::Show(E_Update);
				gd->Update(rect);
				timer.StartTimer();
			}
		}
	}
	UnShow();
	gd->Update(rect);
	return;
}

void spt::HmiTextWnd::ShowContinuePage()
{
	HmiKey key;
	bool8 first = 1;
	MsStampTimer timer;
	timer.Enable(1);
	uint32 total;
	uint32 step;
	uint32 page;
	if (updateFunc)
	{
		key.Key1 = 0;
		updateFunc(*this, 0, title.TotalPage(), key);
	}
	totalLine = text[0].LineNum();
	curLine = 0;
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
					first = 1;
					break;
				case spt::EK_LEFT:
					total = title.TotalPage();
					step = 1;
					if (!step)
					{
						step = 1;
					}
					page = title.Page();
					if (page > step)
					{
						page = page - step;
					}
					else
					{
						page = 0;
					}
					curLine = 0;
					title.SetPage(page, total);
					first = 1;
					if (updateFunc)
					{
						updateFunc(*this, page, total, key);
					}
					AutoLayerOut();
					break;
				case spt::EK_UP:
					total = title.TotalPage();
					step = context.MaxDispRowNum() - 1;
					page = title.Page();
					if (curLine >= step)
					{
						curLine = curLine - step;
					}
					else
					{
						curLine = 0;
					}
					title.SetLine(curLine, totalLine);
					title.SetPage(page, total);
					first = 1;
					AutoLayerOut();
					break;
				case spt::EK_RIGHT:
					total = title.TotalPage();
					step = 1;
					if (!step)
					{
						step = 1;
					}
					page = title.Page() + step;
					if (page >= total)
					{
						page = total - 1;
					}
					curLine = 0;
					title.SetPage(page, total);
					first = 1;
					if (updateFunc)
					{
						updateFunc(*this, page, total, key);
					}
					AutoLayerOut();
					break;
				case spt::EK_DOWN:
					total = title.TotalPage();
					step = context.MaxDispRowNum() - 1;
					page = title.Page();
					uint32 c;
					c = curLine + step;
					if (c < totalLine)
					{
						curLine = c;
					}
					title.SetLine(curLine, totalLine);
					title.SetPage(page, total);
					first = 1;
					AutoLayerOut();
					break;
				case spt::EK_ESC:
					UnShow();
					gd->Update(rect);
					return;
				case spt::EK_MD_STOP:
					UnShow();
					gd->Update(rect);
					return;
				default:

					break;
				}
			}
			else if (updateFunc)
			{
				total = title.TotalPage();
				page = title.Page();
				if (key.Key1 == EK1_ASSIC)
				{
					updateFunc(*this, page, total, key);
					first = 1;
				}
			}
		}
		else
		{
			HmiMain::Instance().MsSleep(50);
		}
		if (timer.Status(100))
		{
			if (first)
			{
				AutoLayerOut();
				first = 0;
				HmiWidSinglePage::Show(E_AllFrame);
				gd->Update(rect);
				timer.StartTimer();
			}
			else if (timer.Status(2000))
			{
				HmiWidSinglePage::Show(E_Update);
				gd->Update(rect);
				timer.StartTimer();
			}
		}
	}
	UnShow();
	gd->Update(rect);
	return;
}

void spt::HmiTextWndCell::ShowSelf(ShowType Type)
{
	if (isVisible && isEnable)
	{

	}
	else
	{
		return;
	}
	uint32 row = 0;
	if (IsHmiWidContextParent())
	{
		HmiWidContextArea* p = (HmiWidContextArea*)parent;
		TransString ts;
		ts.SetBuf(text.Str());
		String100B str;
		uint16 y = Row;
		while (!ts.IsEnd())
		{
			str.Clear();
			if (ts.GetLine(str))
			{
				row++;
				if (row < firstDispLine)
				{
					continue;
				}
				p->SetText(y, Col, str.Str());
				y++;
				if (y >= p->MaxDispRowNum())
				{
					break;
				}
			}
		}
	}
}

uint16 spt::HmiTextWndCell::DispPageNum()
{
	return dispPageNum;
}

void spt::HmiTextWndCell::SetDispPageNum(uint16 page)
{
	dispPageNum = page;
}

uint16 spt::HmiTextWndCell::FirstDispLine()
{
	return firstDispLine;
}

uint16 spt::HmiTextWndCell::SetFirstDispLine(uint16 FirstDispLine)
{
	return firstDispLine = FirstDispLine;
}
