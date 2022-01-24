#ifndef  HMIPROJECT_H
#define HMIPROJECT_H

#include"DbgTools.h"
#include"HmiVirLcdLayer.h"
#include"HmiCmm.h"
#include"HmiKey.h"
#include"HmiWidgets.h"
#include"HmiLedStatus.h"
#include"HmiStatusBar.h"
#include"HmiMenu.h"
#include"HmiDialog.h"
#include"HmiGridWnd.h"
#include"HmiTextWnd.h"
namespace spt
{
	class HmiMain :public Task, public HmiWidRect
	{
	public:
		enum TaskStep
		{
			E_PowerUpIni = 0,
			E_AlertWnd,
			E_MenuWnd,
		};
	public:
		void DrawFrameWnd();
	public:
		int32 PowerUpIni(int32 Type);
		virtual int32 OneLoop();
		static HmiMain& Instance();
	protected:
		HmiMain();
	private:
		HmiMenuService* menuService;
	};
}
#endif//HMIPROJECT_H