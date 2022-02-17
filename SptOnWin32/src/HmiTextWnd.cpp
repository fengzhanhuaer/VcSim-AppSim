#include "SptProject.h"
using namespace spt;
HmiTextWndPage spt::HmiTextWnd::text[CN_Max_WndCell];
spt::HmiTextWnd::HmiTextWnd(DispType Mode)
{
	updateFunc = 0;
	mode = Mode;
	IniAllPage();
}

void spt::HmiTextWnd::SetPage(uint32 Page, const char* Text)
{
	HmiTextWndPage* page = GetWndCell(Page % CN_Max_WndCell);
	if (page)
	{
		page->SetPage(Page, Text);
	}
}

void spt::HmiTextWnd::Show()
{
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
		text[i].Clear();
	}
}


HmiTextWndPage* spt::HmiTextWnd::GetWndCell(uint32 Index)
{
	if (Index < M_ArrLen(text))
	{
		return &text[Index];
	}
	return 0;
}

HmiTextWndPage* spt::HmiTextWnd::GetWndPage(uint32 Page)
{
	for (uint32 i = 0; i < M_ArrLen(text); i++)
	{
		if (text[i].Page() == Page)
		{
			return &text[i];
		}
	}
	return 0;
}

void spt::HmiTextWnd::ShowSelf()
{
	if (mode == E_SinglePage)
	{
		if ((isUpdate || (lastPage != page)))
		{
			HmiTextWndPage* wndpage = GetWndPage(page);
			if (wndpage)
			{
				ClearCtx();
			}
			else
			{
				ClearCtx();
			}
		}
	}
	else if (mode == E_ScrollPage)
	{

	}
	else if (mode == E_ContinuePage)
	{

	}
	WidTextWnd::ShowSelf();
}

void spt::HmiTextWnd::ShowSinglePage()
{
	HmiKey key;
	SetPeriodUpdate(1, 200);
	uint32 step;
	if (updateFunc)
	{
		key.Key1 = 0;
		updateFunc(*this, 0, totalPage, key);
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
					SetUpdate(1);
					break;
				case spt::EK_LEFT:
					step = totalPage / 10;
					if (!step)
					{
						step = 1;
					}
					if (page > step)
					{
						page = page - step;
					}
					else
					{
						page = 0;
					}
					if (updateFunc)
					{
						updateFunc(*this, page, totalPage, key);
					}
					SetUpdate(1);
					break;
				case spt::EK_UP:
					step = 1;
					if (page >= step)
					{
						page = page - step;
					}
					else
					{
						page = totalPage - step;
					}
					if (updateFunc)
					{
						updateFunc(*this, page, totalPage, key);
					}
					SetUpdate(1);
					break;
				case spt::EK_RIGHT:
					step = totalPage / 10;
					if (!step)
					{
						step = 1;
					}
					page = page + step;
					if (page >= totalPage)
					{
						page = totalPage - 1;
					}
					if (updateFunc)
					{
						updateFunc(*this, page, totalPage, key);
					}
					SetUpdate(1);
					break;
				case spt::EK_DOWN:
					step = 1;
					page = totalPage + step;
					if (page >= totalPage)
					{
						page = 0;
					}
					if (updateFunc)
					{
						updateFunc(*this, page, totalPage, key);
					}
					SetUpdate(1);
					break;
				case spt::EK_ESC:
					ReDrawRect();
					gd->Update(rect);
					return;
				case spt::EK_MD_STOP:
					ReDrawRect();
					gd->Update(rect);
					return;
				default:
					break;
				}
				HmiMain::Instance().MsSleep(20);
			}
			else if (updateFunc)
			{
				if (key.Key1 == EK1_ASSIC)
				{
					updateFunc(*this, page, totalPage, key);
					SetUpdate(1);
				}
				HmiMain::Instance().MsSleep(50);
			}
		}
		else
		{
			HmiMain::Instance().MsSleep(100);
		}
		WidTextWnd::Show();
	}
	ReDrawRect();
	gd->Update(rect);
	return;
}

void spt::HmiTextWnd::ShowScrollPage()
{
	HmiKey key;
	SetPeriodUpdate(1, 200);
	uint32 step;
	if (updateFunc)
	{
		key.Key1 = 0;
		updateFunc(*this, 0, totalPage, key);
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
					SetUpdate(1);
					break;
				case spt::EK_LEFT:
					step = totalPage / 10;
					if (!step)
					{
						step = 1;
					}
					if (page > step)
					{
						page = page - step;
					}
					else
					{
						page = 0;
					}
					if (updateFunc)
					{
						updateFunc(*this, page, totalPage, key);
					}
					SetUpdate(1);
					break;
				case spt::EK_UP:
					step = 1;
					if (page >= step)
					{
						page = page - step;
					}
					else
					{
						page = totalPage - step;
					}
					if (updateFunc)
					{
						updateFunc(*this, page, totalPage, key);
					}
					SetUpdate(1);
					break;
				case spt::EK_RIGHT:
					step = totalPage / 10;
					if (!step)
					{
						step = 1;
					}
					page = page + step;
					if (page >= totalPage)
					{
						page = totalPage - 1;
					}
					if (updateFunc)
					{
						updateFunc(*this, page, totalPage, key);
					}
					SetUpdate(1);
					break;
				case spt::EK_DOWN:
					step = 1;
					page = page + step;
					if (page >= totalPage)
					{
						page = 0;
					}
					if (updateFunc)
					{
						updateFunc(*this, page, totalPage, key);
					}
					SetUpdate(1);
					break;
				case spt::EK_ESC:
					ReDrawRect();
					gd->Update(rect);
					return;
				case spt::EK_MD_STOP:
					ReDrawRect();
					gd->Update(rect);
					return;
				default:

					break;
				}
				HmiMain::Instance().MsSleep(20);
			}
			else if (updateFunc)
			{
				if (key.Key1 == EK1_ASSIC)
				{
					updateFunc(*this, page, totalPage, key);
					SetUpdate(1);
				}
				HmiMain::Instance().MsSleep(50);
			}
		}
		else
		{
			HmiMain::Instance().MsSleep(100);
		}
		WidTextWnd::Show();
	}
	ReDrawRect();
	gd->Update(rect);
	return;
}

void spt::HmiTextWnd::ShowContinuePage()
{
	HmiKey key;
	SetPeriodUpdate(1, 200);
	uint32 step;
	if (updateFunc)
	{
		key.Key1 = 0;
		updateFunc(*this, 0, totalPage, key);
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
					SetUpdate(1);
					break;
				case spt::EK_LEFT:
					step = 1;
					if (page > step)
					{
						page = page - step;
					}
					else
					{
						page = 0;
					}
					if (updateFunc)
					{
						updateFunc(*this, page, totalPage, key);
					}
					SetUpdate(1);
					break;
				case spt::EK_UP:
					step = DispMaxCtxLine() - 1;
					if (line >= step)
					{
						line = line - step;
					}
					else
					{
						line = 0;
					}
					if (updateFunc)
					{
						updateFunc(*this, page, totalPage, key);
					}
					SetUpdate(1);
					break;
				case spt::EK_RIGHT:
					step = 1;
					if (!step)
					{
						step = 1;
					}
					page = page + step;
					if (page >= totalPage)
					{
						page = totalPage - 1;
					}
					if (updateFunc)
					{
						updateFunc(*this, page, totalPage, key);
					}
					SetUpdate(1);
					break;
				case spt::EK_DOWN:
					step = DispMaxCtxLine() - 1;
					uint32 c;
					c = line + step;
					if (c < totalLine)
					{
						line = c;
					}
					if (updateFunc)
					{
						updateFunc(*this, page, totalPage, key);
					}
					SetUpdate(1);
					break;
				case spt::EK_ESC:
					ReDrawRect();
					gd->Update(rect);
					return;
				case spt::EK_MD_STOP:
					ReDrawRect();
					gd->Update(rect);
					return;
				default:

					break;
				}
				HmiMain::Instance().MsSleep(20);
			}
			else if (updateFunc)
			{
				if (key.Key1 == EK1_ASSIC)
				{
					updateFunc(*this, page, totalPage, key);
					SetUpdate(1);
				}
				HmiMain::Instance().MsSleep(50);
			}
		}
		else
		{
			HmiMain::Instance().MsSleep(100);
		}
		WidTextWnd::Show();
	}
	ReDrawRect();
	gd->Update(rect);
	return;
}

uint16 spt::HmiTextWndPage::Page()
{
	return dispPageNum;
}

void spt::HmiTextWndPage::SetPage(uint32 Page, const char* Text)
{
	dispPageNum = Page;
	if (ctx != Text)
	{
		ctx = Text;
		isctxupdate = 1;
	}
}

void spt::HmiTextWndPage::Clear()
{
	isctxupdate = 1;
	dispPageNum = -1;
	ctx.Clear();
}

void spt::HmiTextWndPage::SetUpdate()
{
	isctxupdate = 1;
}
