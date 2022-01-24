#include "SptProject.h"
using namespace spt;
#include "ApiProject.h"

void spt::HmiMain::DrawFrameWnd()
{
	HmiWidRect::Show(E_AllFrame);
	gd->Update(rect);
}

int32 spt::HmiMain::PowerUpIni(int32 Type)
{
	Task::PowerUpIni(Type);
	rect.x = 0;
	rect.y = 0;
	rect.w = gd->LcdWidth();
	rect.h = HmiStatusBar::Instance().Rect().y - gd->SpaceOfFont();
	Start();
	return 0;
}

int32 spt::HmiMain::OneLoop()
{
	switch (taskStep)
	{
	case E_PowerUpIni:
	{
		DrawFrameWnd();
		taskStep = E_AlertWnd;
		break;
	}
	case E_AlertWnd:
	{
		const struct ApiAppCfg* cfg = SptMain::Instance().AppCfg();
		DrawFrameWnd();
		if (!cfg)
		{
			return 0;
		}
		if (EH_GZKSAU == cfg->platform.hardware)
		{
			goto defaultDisp;
		}
		else
		{
		defaultDisp:
			{
				ApiInfoDialog dig(cfg->hmicfg.DispName, cfg->hmicfg.FullTypeName, 0, 0, 0, "按任意键进入主菜单");
				dig.Show();
				int32 key = DispPressAnyKey(2000);
				if (key && (key != EK_MD_STOP))
				{
					taskStep = E_MenuWnd;
				}
			}
		}
		break;
	}
	case E_MenuWnd:
	{
		DrawFrameWnd();
		menuService->StartService((HmiMenu*)SptMain::Instance().AppCfg()->hmicfg.AppRootMenu);
		taskStep = E_PowerUpIni;
		break;
	}
	default:
		break;
	}
	MsSleep(100);
	return 0;
}

HmiMain& spt::HmiMain::Instance()
{
	static HmiMain inst;
	return inst;
}

spt::HmiMain::HmiMain()
	:Task("tHmi", TaskBasePriority + 5, 2 * 1024 * 1024, E_T_FLOAT, E_AuxCore)
{
	menuService = &HmiMenuService::Instance();
	SetVisible(1);
}
void spt::HmiMainFramePowerUpIni()
{
	GraphicDevice::Instance().PowerUpIni(0);
	HmiWidObject::gd = &GraphicDevice::Instance();
	HmiWidObject::key = &HmiKeyService::Instance();
	HmiMain::Instance().PowerUpIni(0);
}