#include"InstResource.h"

ApiHmiLedGroup hmiLedGroup;

ApiHmiLed hmiLed[CN_NUM_LED];
// 指示灯初始化
void AppHmiLedPowerUpIni()
{
	WORD i;
	const tagLedTab  *ptLedTab;
	ptLedTab=&g_tLedTab[0];
	hmiLedGroup.PowerUpIni("指示灯", "hmiLedGroup", M_ArrLen(hmiLed));
	for(i=0;i<CN_NUM_LED;i++)
	{
		switch(ptLedTab->bycolor)
		{
			case EN_COLOR_RED:
				hmiLed[i].PowerUpIni(ptLedTab->byName, ptLedTab->byPinName, hmiLedGroup, HmiLed::E_RED,ptLedTab->byCol,ptLedTab->byRow,ptLedTab->bHld);
				break;
			case EN_COLOR_GREEN:
				hmiLed[i].PowerUpIni(ptLedTab->byName, ptLedTab->byPinName, hmiLedGroup, HmiLed::E_GREEN,ptLedTab->byCol,ptLedTab->byRow,ptLedTab->bHld);
				break;
			case EN_COLOR_YELLOW:
				hmiLed[i].PowerUpIni(ptLedTab->byName, ptLedTab->byPinName, hmiLedGroup, HmiLed::E_YELLOW,ptLedTab->byCol,ptLedTab->byRow,ptLedTab->bHld);
				break;
			case EN_COLOR_NULL:
				hmiLed[i].PowerUpIni(ptLedTab->byName, ptLedTab->byPinName, hmiLedGroup, HmiLed::E_NULL,ptLedTab->byCol,ptLedTab->byRow,ptLedTab->bHld);
				break;
		}
		// 恢复掉电保持指示灯标志
		if(ptLedTab->bHld)
		{
			g_tagIO.bLedOutHld[i]=hmiLed[i].Value();
		}

		ptLedTab++;
	}
}
// 更新指示灯状态
void AppHmiLedOutRef()
{
	BYTE byLedPtr=g_tagIO.byLedPtr;
	if(byLedPtr<CN_NUM_LED)
	{
		hmiLed[byLedPtr].SetValue(g_tagIO.bLedOut[byLedPtr]);
	}
}

