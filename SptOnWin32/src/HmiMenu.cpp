#include "ApiProject.h"
using namespace spt;


void spt::HmiMenu::SetMenu(const char* Name, HmiMenu* ChildMenu, IsOkMenuFunction AllowFunction, IsOkMenuFunction Function, IsOkMenuFunction ExitFunction, const uint32* PDisp)
{
	gd = &GraphicDevice::Instance();
	SetDisp(PDisp);
	SetName(Name);
	child = ChildMenu;
	function = Function;
	allowFunction = AllowFunction;
	exitFunction = ExitFunction;
}

void spt::HmiMenu::SetName(const char* Name)
{
	name.Clear();
	name << Name;
}

void spt::HmiMenu::SetDisp(const uint32* pD)
{
	pDisp = pD;
	if (!pD)
	{
		pDisp = &MenuUnDisp;
	}
}

SalString& spt::HmiMenu::Name()
{
	return name;
}

bool8 spt::HmiMenu::IsDisp()
{
	return *pDisp;
}

bool8 spt::HmiMenu::IsEnd()
{
	return name == EndOfInst;
}

void spt::HmiMenu::Disp(HmiPos pos, bool8 Selected)
{
	GraphicDevice& gd = *this->gd;
	if (Selected == 0)
	{
		gd.ClearRect(pos.x, pos.y, gd.E_White, (strLen)*gd.FontWidth() + 1, gd.FontHeight() + gd.SpaceOfFont());
		gd.DrawStr(pos.x + 1, pos.y + (gd.SpaceOfFont() >> 1), gd.E_Black, name.Str());
	}
	else
	{
		gd.ClearRect(pos.x, pos.y, gd.E_Black, (strLen)*gd.FontWidth() + 1, gd.FontHeight() + gd.SpaceOfFont());
		gd.DrawStr(pos.x + 1, pos.y + (gd.SpaceOfFont() >> 1), gd.E_White, name.Str());
	}
	return;
}

void spt::HmiMenuBar::StartService(HmiMenu* Childs, uint16 BarId, HmiMenuBar* Parent)
{
	gd = &GraphicDevice::Instance();
	Id = BarId;
	parent = Parent;
	currentMenu = 0;
	SetChilds(Childs);
	return;
}

uint16 spt::HmiMenuBar::MaxMenuBuf()
{
	return M_ArrLen(child);
}

void spt::HmiMenuBar::SetPos(HmiPos Pos)
{
	SetPos(Pos.x, Pos.y);
}

void spt::HmiMenuBar::SetPos(int16 x, int16 y)
{
	rect.x = x;
	rect.y = y;
}

void spt::HmiMenuBar::SetChilds(HmiMenu* Childs)
{
	if (!Childs)
	{
		return;
	}
	Clear();
	HmiMenu* now = Childs;
	while (!(now->IsEnd()))
	{
		if (now->IsDisp())
		{
			InsertMenu(now);
		}
		now++;

	}
	GraphicDevice& gd = *this->gd;
	rect.w = (maxChildStrLen + 1) * gd.FontWidth();
	rect.h = (totalChild) * (gd.SpaceOfFont() + gd.FontHeight()) + gd.SpaceOfFont() * 2 + 1;
}

void spt::HmiMenuBar::Clear()
{
	totalChild = 0;
	maxChildStrLen = 0;
	currentMenu = 0;
}

void spt::HmiMenuBar::Disp()
{
	GraphicDevice& gd = *this->gd;
	gd.DrawRect(rect.x, rect.y, gd.E_Black, rect.w, rect.h);

	HmiPos pos = { (int16)(rect.x + gd.FontWidth() / 2)  ,(int16)(rect.y + gd.SpaceOfFont() + 1) };

	for (int16 i = 0; i < totalChild; i++)
	{
		child[i]->Disp(pos, i == currentMenu);
		pos.y += gd.FontHeight() + gd.SpaceOfFont();
	}
	lastMenu = currentMenu;
}

void spt::HmiMenuBar::SelectChg()
{
	if (lastMenu == currentMenu)
	{
		return;
	}
	GraphicDevice& gd = *this->gd;
	HmiPos pos;
	pos.x = this->rect.x + (int16)(gd.FontWidth() / 2);
	pos.y = this->rect.y + gd.SpaceOfFont() + 1 + (gd.FontHeight() + gd.SpaceOfFont()) * lastMenu;

	child[lastMenu]->Disp(pos, 0);

	pos.y = this->rect.y + gd.SpaceOfFont() + 1 + (gd.FontHeight() + gd.SpaceOfFont()) * currentMenu;
	child[currentMenu]->Disp(pos, 1);

	lastMenu = currentMenu;
	gd.Update(rect);
}

void spt::HmiMenuBar::UnDisp()
{
	gd->ClearRect(rect.x, rect.y, gd->E_White, rect.w, rect.h);
	gd->Update(rect);
}

void spt::HmiMenuBar::InsertMenu(HmiMenu* Child)
{
	if (totalChild >= MaxMenuBuf())
	{
		LogErr.Stamp() << "too many menu." << Child->Name().Str() << "\n";
		return;
	}
	Child->Id = totalChild;
	child[totalChild++] = Child;
	Child->strLen = StrLen(Child->Name().Str());
	if (maxChildStrLen < Child->strLen)
	{
		maxChildStrLen = StrLen(Child->Name().Str());
	}
}

HmiMenu* spt::HmiMenuBar::CascadeChild()
{
	HmiMenu* menu = child[currentMenu % totalChild];

	if (menu->child)
	{
		return menu->child;
	}
	return 0;
}

bool8 spt::HmiMenuBar::IsCascade()
{
	HmiMenu* menu = child[currentMenu % totalChild];

	if (menu->child && (!menu->function))
	{
		return 1;
	}
	return 0;
}

bool8 spt::HmiMenuBar::AllowExit()
{
	HmiMenu* menu = child[currentMenu % totalChild];
	if (menu->exitFunction)
	{
		return menu->exitFunction((ApiMenu*)menu);
	}
	return 1;
}

bool8 spt::HmiMenuBar::AllowEnter()
{
	HmiMenu* menu = child[currentMenu % totalChild];
	if (menu->allowFunction)
	{
		return menu->allowFunction((ApiMenu*)menu);
	}
	return 1;
}

bool8 spt::HmiMenuBar::DoFunc()
{
	HmiMenu* menu = child[currentMenu % totalChild];
	if (menu->function)
	{
		return menu->function((ApiMenu*)menu);
	}
	return 1;
}

spt::HmiMenuService::HmiMenuService()
{
	hmiMain = 0;
	rect.x = gd->FontWidth() / 2;
	rect.y = gd->SpaceOfFont();
	rect.w = gd->LcdWidth() - gd->FontWidth();
	rect.h = gd->LcdHeight() - rect.y - gd->FontHeight() - 4 * gd->SpaceOfFont();
}

uint16 spt::HmiMenuService::MaxMenuBarBuf()
{
	return M_ArrLen(menuBar);
}

HmiMenuService& spt::HmiMenuService::Instance()
{
	static HmiMenuService inst;
	return inst;
}

void spt::HmiMenuService::StartService(HmiMenu* MenuRoot)
{
	StartService(MenuRoot, 0, 0);
}

void spt::HmiMenuService::StartService(HmiMenu* MenuRoot, IsOkMenuFunction AllowFunction, IsOkMenuFunction ExitFunction)
{
	if (!MenuRoot)
	{
		LogErr.Stamp() << " HmiMenuService menu root is null.\n";
		return;
	}
	allowFunction = AllowFunction;
	exitFunction = ExitFunction;
	if (allowFunction)
	{
		if (!allowFunction((ApiMenu*)MenuRoot))
		{
			return;
		}
	}
	SetVisible(1);
	HmiWidRect::Show(E_AllFrame);
	stampTimer.Enable(1);
	stampTimer.StartTimer();
	hmiMain = &HmiMain::Instance();
	HmiKeyService& ks = HmiKeyService::Instance();
	taskStep = E_PowerUp;
	HmiPos mutp;
	mutp.x = rect.x + gd->FontWidth() / 2;
	mutp.y = rect.y + 2;
	while (1)
	{
		switch (taskStep)
		{
		case E_PowerUp:
		{
			menuBar[0].StartService(MenuRoot, 0, 0);
			curMenu = &menuBar[0];
			if (curMenu->AllowEnter())
			{
				if (curMenu->IsCascade())
				{
					if (curMenu < &menuBar[M_ArrLen(menuBar) - 2])
					{
						curMenu[1].StartService(curMenu->CascadeChild(), curMenu - menuBar, curMenu);
						curMenu++;
					}
				}
				else
				{
					curMenu->DoFunc();
					curMenu->AllowExit();
					HmiWidRect::Show(E_AllFrame);
					return;
				}
			}
			else
			{
				return;
			}
			curMenu->SetPos(mutp);
			leftMenu = curMenu;
			HmiMenuBar* now = leftMenu;
			while (now <= curMenu)
			{
				now->Disp();
				now++;
			}
			gd->Update(rect);
			taskStep = E_DispAll;
			break;
		}
		case E_DispAll:
		{
			HmiMenuBar* now = leftMenu;
			while (now <= curMenu)
			{
				now->Disp();
				now++;
			}
			gd->Update(rect);
			taskStep = E_WaitKey;
			break;
		}
		case E_WaitKey:
		{
			HmiKey key;

			if (ks.Pop(key))
			{
				if (key.Key1 == EK1_KEYVALUE)
				{
					E_KEY2 k2 = (E_KEY2)key.Key2;
					switch (k2)
					{
					case EK_UP:
					{
						curMenu->currentMenu = (curMenu->currentMenu + curMenu->totalChild - 1) % curMenu->totalChild;
						taskStep = E_SelectChg;
						break;
					}
					case EK_DOWN:
					{
						curMenu->currentMenu = (curMenu->currentMenu + 1) % curMenu->totalChild;
						taskStep = E_SelectChg;
						break;
					}
					case EK_RIGHT:
					case EK_ENTER:
					{
						curMenu->UnDisp();
						if (curMenu->AllowEnter())
						{
							if (curMenu->IsCascade())
							{
								if (curMenu < &menuBar[M_ArrLen(menuBar) - 2])
								{
									curMenu[1].StartService(curMenu->CascadeChild(), curMenu - menuBar, curMenu);
									curMenu[1].SetPos(mutp);
									curMenu++;
									leftMenu = curMenu;
									taskStep = E_DispAll;
									break;
								}
								else
								{
									LogErr.Stamp() << " HmiMenuService menu cascade number is overflow.\n";
									break;
								}
							}
							else
							{
								curMenu->DoFunc();
								curMenu->AllowExit();
								HmiWidRect::Show(E_AllFrame);
								gd->Update(rect);
								taskStep = E_DispAll;
							}
						}
						else
						{
							taskStep = E_DispAll;
						}
						break;
					}
					case EK_LEFT:
					case EK_ESC:
					case EK_MD_STOP:
					{
						if (curMenu[-1].AllowExit())
						{
							curMenu->UnDisp();
							curMenu--;
							leftMenu = curMenu;
							if (curMenu <= &menuBar[0])
							{
								if (exitFunction)
								{
									if (exitFunction((ApiMenu*)MenuRoot))
									{
										HmiWidRect::UnShow();
										gd->Update(rect);
										return;
									}
								}
								else
								{
									HmiWidRect::UnShow();
									gd->Update(rect);
									return;
								}
							}
							else
							{
								taskStep = E_DispAll;
							}
						}
						else
						{
							taskStep = E_DispAll;
						}
						break;
					}
					default:
						break;
					}
				}
			}
			else
			{
				if (stampTimer.Status(5000))
				{
					taskStep = E_DispAll;
					stampTimer.StartTimer();
				}
				hmiMain->MsSleep(10);
			}
			break;
		}
		case E_DispCurMenu:
		{
			taskStep = E_WaitKey;
			curMenu->Disp();
			gd->Update(curMenu->Rect());
			break;
		}
		case E_SelectChg:
		{
			taskStep = E_WaitKey;
			curMenu->SelectChg();
			break;
		}
		default:
			taskStep = E_PowerUp;
			break;
		}
	}
	HmiWidRect::UnShow();
	gd->Update(rect);
	return;
}
