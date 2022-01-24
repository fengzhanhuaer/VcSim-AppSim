#ifndef  HMIPROJECT_H
#define HMIPROJECT_H


#include"DbgTools.h"
#include"HmiVirLcdLayer.h"
#include"HmiCmm.h"
#include"HmiKey.h"
#include"HmiLedStatus.h"

namespace spt
{
	class HmiMain :public Task
	{
	public:
		enum TaskStep
		{
			E_PowerUpIni = 0,
			E_MenuWnd,
		};
	public:
		void DrawStartUpWnd();
	public:
		int32 PowerUpIni(int32 Type);
		virtual int32 OneLoop();
		static HmiMain& Instance();
	protected:
		HmiMain();
	private:
		GraphicDevice& gd;
	};
}
#endif//HMIPROJECT_H