#include "InstResource.h"
// �������
ApiEvent AppEventAct[CN_NUM_ACT];
ApiEvent AppEventWarn[CN_NUM_ALM];
ApiEvent AppEventChek[CN_NUM_CHK];
ApiEvent AppEventRun[CN_NUM_RUN];
ApiEvent AppEventOpt[CN_NUM_OPT];
// SOE����
ApiEvent AppEventDISoe[CN_NUM_DI];
ApiEvent AppEventGoInSoe[CN_NUM_GOIN];
ApiEvent AppEventFlagSoe[CN_NUM_FLAG];
ApiEvent AppEventDOSoe[CN_NUM_DO];
ApiEvent AppEventGoOutSoe[CN_NUM_GOOUT];
ApiEvent AppEventLedSoe[CN_NUM_LED];
// ˫��SOE����
ApiEvent AppEventDpiSoe[CN_NUM_DPI];
// �ڲ�����
ApiEvent AppEventPrvtSoe[CN_NUM_PRVT_SOE];
ApiEvent AppEventPrvtOpt[CN_NUM_PRVT_OPT];

ApiEventGroup AppEventActGroup;
ApiEventGroup AppEventWarnGroup;
ApiEventGroup AppEventChekGroup;
ApiEventGroup AppEventRunGroup;
ApiEventGroup AppEventOptGroup;

ApiEventGroup AppEventDISoeGroup;
ApiEventGroup AppEventGoInSoeGroup;
ApiEventGroup AppEventFlagSoeGroup;
ApiEventGroup AppEventDOSoeGroup;
ApiEventGroup AppEventGoOutSoeGroup;
ApiEventGroup AppEventLedSoeGroup;
ApiEventGroup AppEventDpiSoeGroup;

ApiEventGroup AppEventPrvtSoeGroup;
ApiEventGroup AppEventPrvtOptGroup;

ApiEventViewPool HmiViewEventPool;

void AppEventActPowerUpIni()
{
	WORD i;
	const tagActTab* ptActTab;
	tagMEATab* ptMEATab;
	StatusExInfoDesItem* peventData0, * peventData1, * peventData2, * peventData3, * peventData4, * peventData5;
	SalStatus::Flags  uiFlag;
	// �澯�����ʼ��
	AppEventActGroup.PowerUpIni("GOOSE��������", "AppEventActGroup", CN_NUM_ACT, CN_NUM_RPT_ACT);
	ptMEATab = &g_tMEATab[0];
	ptActTab = &g_tActTab[0];
	uiFlag.u32 = 0;
	uiFlag.st.isUnDispValueChange = 1;
	for (i = 0; i < CN_NUM_ACT; i++)
	{
		AppEventAct[i].BlPowerUpIni(ptActTab->byName, ptActTab->byPinName, AppEventActGroup, uiFlag.u32);
		// �����¼����ʼ��
		peventData0 = (ptActTab->wValType1 < EN_MEA_END) ? &ptMEATab[ptActTab->wValType1].eventData : NULL;
		peventData1 = (ptActTab->wValType2 < EN_MEA_END) ? &ptMEATab[ptActTab->wValType2].eventData : NULL;
		peventData2 = (ptActTab->wValType3 < EN_MEA_END) ? &ptMEATab[ptActTab->wValType3].eventData : NULL;
		peventData3 = (ptActTab->wValType4 < EN_MEA_END) ? &ptMEATab[ptActTab->wValType4].eventData : NULL;
		peventData4 = (ptActTab->wValType5 < EN_MEA_END) ? &ptMEATab[ptActTab->wValType5].eventData : NULL;
		peventData5 = (ptActTab->wValType6 < EN_MEA_END) ? &ptMEATab[ptActTab->wValType6].eventData : NULL;
		AppEventAct[i].ExInfoPowerUpIni(peventData0, peventData1, peventData2, peventData3, peventData4, peventData5);
		ptActTab++;
	}
}
void AppEventWarnPowerUpIni()
{
	WORD i;
	const tagAlmTab* ptAlmTab;
	tagMEATab* ptMEATab;
	StatusExInfoDesItem* peventData0, * peventData1, * peventData2;
	SalStatus::Flags  uiFlag;

	// �澯������г�ʼ��
	AppEventWarnGroup.PowerUpIni("�澯����", "AppEventWarnGroup", CN_NUM_ALM, CN_NUM_RPT_ALM);
	// �澯�����ʼ��
	ptAlmTab = &g_tAlmTab[0];
	ptMEATab = &g_tMEATab[0];
	uiFlag.u32 = 0;
	for (i = 0; i < CN_NUM_ALM; i++)
	{
		AppEventWarn[i].BlPowerUpIni(ptAlmTab->byName, ptAlmTab->byPinName, AppEventWarnGroup, uiFlag.u32);
		// �����¼����ʼ��
		peventData0 = (ptAlmTab->wValType1 < EN_MEA_END) ? &ptMEATab[ptAlmTab->wValType1].eventData : NULL;
		peventData1 = (ptAlmTab->wValType2 < EN_MEA_END) ? &ptMEATab[ptAlmTab->wValType2].eventData : NULL;
		peventData2 = (ptAlmTab->wValType3 < EN_MEA_END) ? &ptMEATab[ptAlmTab->wValType3].eventData : NULL;
		AppEventWarn[i].ExInfoPowerUpIni(peventData0, peventData1, peventData2);
		ptAlmTab++;
	}
}

void AppEventChekPowerUpIni()
{
	WORD i;
	const tagChkTab* ptChkTab;
	tagMEATab* ptMEATab;
	StatusExInfoDesItem* peventData0, * peventData1, * peventData2;
	SalStatus::Flags  uiFlag;
	// �Լ������ʼ��
	AppEventChekGroup.PowerUpIni("�Լ�����", "AppEventChekGroup", CN_NUM_CHK, CN_NUM_RPT_CHK);
	ptChkTab = &g_tChkTab[0];
	ptMEATab = &g_tMEATab[0];
	uiFlag.u32 = 0;
	for (i = 0; i < CN_NUM_CHK; i++)
	{
		AppEventChek[i].BlPowerUpIni(ptChkTab->byName, ptChkTab->byPinName, AppEventChekGroup, uiFlag.u32);
		peventData0 = (ptChkTab->wValType1 < EN_MEA_END) ? &ptMEATab[ptChkTab->wValType1].eventData : NULL;
		peventData1 = (ptChkTab->wValType2 < EN_MEA_END) ? &ptMEATab[ptChkTab->wValType2].eventData : NULL;
		peventData2 = (ptChkTab->wValType3 < EN_MEA_END) ? &ptMEATab[ptChkTab->wValType3].eventData : NULL;
		AppEventChek[i].ExInfoPowerUpIni(peventData0, peventData1, peventData2);
		ptChkTab++;
	}
}
void AppEventRunPowerUpIni()
{
	WORD i;
	const tagRunTab* ptRunTab;
	SalStatus::Flags  uiFlag;

	AppEventRunGroup.PowerUpIni("��������", "AppEventRunGroup", CN_NUM_RUN, CN_NUM_RPT_RUN);
	ptRunTab = &g_tRunTab[0];
	// ���������ʼ��
	uiFlag.u32 = 0;
	uiFlag.st.isUnDispRtn = 1;
	uiFlag.st.isUnDispValueChange = 1;
	uiFlag.st.isAutoRtn = 1;
	for (i = 0; i < CN_NUM_RUN; i++)
	{
		AppEventRun[i].BlPowerUpIni(ptRunTab->byName, ptRunTab->byPinName, AppEventRunGroup, uiFlag.u32);
		ptRunTab++;
	}
}

void AppEventOptPowerUpIni()
{
	WORD i;
	const tagOptTab* ptOptTab;
	tagMEATab* ptMEATab;
	StatusExInfoDesItem* peventData0, * peventData1, * peventData2;
	SalStatus::Flags  uiFlag;

	AppEventOptGroup.PowerUpIni("��������", "AppEventOptGroup", CN_NUM_OPT, CN_NUM_RPT_OPT);
	// ���������ʼ��
	ptOptTab = &g_tOptTab[0];
	ptMEATab = &g_tMEATab[0];
	uiFlag.u32 = 0;
	uiFlag.st.isUnDispRtn = 1;
	uiFlag.st.isUnDispValueChange = 1;
	uiFlag.st.isAutoRtn = 1;
	for (i = 0; i < CN_NUM_OPT; i++)
	{
		AppEventOpt[i].BlPowerUpIni(ptOptTab->byName, ptOptTab->byPinName, AppEventOptGroup, uiFlag.u32);
		peventData0 = (ptOptTab->wValType1 < EN_MEA_END) ? &ptMEATab[ptOptTab->wValType1].eventData : NULL;
		peventData1 = (ptOptTab->wValType2 < EN_MEA_END) ? &ptMEATab[ptOptTab->wValType2].eventData : NULL;
		peventData2 = (ptOptTab->wValType3 < EN_MEA_END) ? &ptMEATab[ptOptTab->wValType3].eventData : NULL;
		AppEventOpt[i].ExInfoPowerUpIni(peventData0, peventData1, peventData2);
		ptOptTab++;
	}
}

void AppEventDISoePowerUpIni()
{
	WORD i;
	const tagDiTab* ptDiTab;
	SalStatus::Flags  uiFlag;
	AppEventDISoeGroup.PowerUpIni("Ӳ����SOE", "AppEventDISoeGroup", CN_NUM_DI, CN_NUM_RPT_DI);
	uiFlag.u32 = 0;
	uiFlag.st.isDispUs = 1;
	ptDiTab = &g_tDiTab[0];
	for (i = 0; i < CN_NUM_DI; i++)
	{
		AppEventDISoe[i].BlPowerUpIni(ptDiTab->byName, ptDiTab->byPinName, AppEventDISoeGroup, uiFlag.u32);
		ptDiTab++;
	}
}

void AppEventGoInSoePowerUpIni()
{
	WORD i;
	const tagGoInTab* ptGoInTab;
	SalStatus::Flags  uiFlag;
	AppEventGoInSoeGroup.PowerUpIni("GOOSE����SOE", "AppEventGoInSoeGroup", CN_NUM_GOIN, CN_NUM_RPT_GOIN);
	ptGoInTab = &g_tGoInTab[0];
	uiFlag.u32 = 0;
	uiFlag.st.isDispQ = 1;
	for (i = 0; i < CN_NUM_GOIN; i++)
	{
		AppEventGoInSoe[i].BlPowerUpIni(ptGoInTab->byName, ptGoInTab->byPinName, AppEventGoInSoeGroup, uiFlag.u32);
		ptGoInTab++;
	}
}
void AppEventFlagSoePowerUpIni()
{
	WORD i;
	const tagFlagTab* ptFlagTab;
	SalStatus::Flags  uiFlag;
	AppEventFlagSoeGroup.PowerUpIni("����SOE", "AppEventFlagSoeGroup", CN_NUM_FLAG, CN_NUM_RPT_FLAG);
	ptFlagTab = &g_tFlagTab[0];
	uiFlag.u32 = 0;
	for (i = 0; i < CN_NUM_FLAG; i++)
	{
		AppEventFlagSoe[i].BlPowerUpIni(ptFlagTab->byName, ptFlagTab->byPinName, AppEventFlagSoeGroup, uiFlag.u32);
		ptFlagTab++;
	}
}
void AppEventDoSoePowerUpIni()
{
	WORD i;
	const tagDoTab* ptDoTab;
	SalStatus::Flags  uiFlag;
	AppEventDOSoeGroup.PowerUpIni("Ӳ����SOE", "AppEventDoSoeGroup", CN_NUM_DO, CN_NUM_RPT_DO);
	ptDoTab = &g_tDoTab[0];
	uiFlag.u32 = 0;
	for (i = 0; i < CN_NUM_DO; i++)
	{
		AppEventDOSoe[i].BlPowerUpIni(ptDoTab->byName, ptDoTab->byPinName, AppEventDOSoeGroup, uiFlag.u32);
		ptDoTab++;
	}
}
void AppEventGoOutSoePowerUpIni()
{
	WORD i;
	const tagGoOutTab* ptGoOutTab;
	SalStatus::Flags  uiFlag;
	uiFlag.u32 = 0;
	AppEventGoOutSoeGroup.PowerUpIni("GOOSE����SOE", "AppEventGoOutSoeGroup", CN_NUM_GOOUT, CN_NUM_RPT_GOOUT);
	ptGoOutTab = &g_tGoOutTab[0];
	for (i = 0; i < CN_NUM_GOOUT; i++)
	{
		AppEventGoOutSoe[i].BlPowerUpIni(ptGoOutTab->byName, ptGoOutTab->byPinName, AppEventGoOutSoeGroup, uiFlag.u32);
		ptGoOutTab++;
	}
}
void AppEventLedSoePowerUpIni()
{
	WORD i;
	const tagLedTab* ptLedTab;
	SalStatus::Flags  uiFlag;
	AppEventLedSoeGroup.PowerUpIni("LEDָʾ��SOE", "AppEventLedSoeGroup", CN_NUM_LED, CN_NUM_RPT_LED);
	ptLedTab = &g_tLedTab[0];
	uiFlag.u32 = 0;
	for (i = 0; i < CN_NUM_LED; i++)
	{
		AppEventLedSoe[i].BlPowerUpIni(ptLedTab->byName, ptLedTab->byPinName, AppEventLedSoeGroup, uiFlag.u32);
		ptLedTab++;
	}
}

void AppEventDpiSoePowerUpIni()
{
	WORD i;
	const tagDpiTab* ptDpiTab;
	SalStatus::Flags  uiFlag;
	// ˫�������ʼ��
	AppEventDpiSoeGroup.PowerUpIni("˫��SOE�ź�", "AppDEventSoeGroup", CN_NUM_DPI, CN_NUM_RPT_DPI);
	ptDpiTab = &g_tDpiTab[0];
	uiFlag.u32 = 0;
	uiFlag.st.isDispUs = 1;
	for (i = 0; i < CN_NUM_DPI; i++)
	{
		AppEventDpiSoe[i].DpPowerUpIni(ptDpiTab->byName, ptDpiTab->byPinName, AppEventDpiSoeGroup, uiFlag.u32);
		ptDpiTab++;
	}
}
void AppEventPrvtSoePowerUpIni()
{
	WORD i;
	const tagPrvtSoeTab* ptPrvtSoeTab;
	SalStatus::Flags  uiFlag;
	// ˫�������ʼ��
	AppEventPrvtSoeGroup.PowerUpIni("�ڲ�����", "AppEventPrvtSoeGroup", CN_NUM_PRVT_SOE, CN_NUM_RPT_PRVT_SOE);
	ptPrvtSoeTab = &g_tPrvtSoeTab[0];
	uiFlag.u32 = 0;
	for (i = 0; i < CN_NUM_PRVT_SOE; i++)
	{
		AppEventPrvtSoe[i].BlPowerUpIni(ptPrvtSoeTab->byName, ptPrvtSoeTab->byPinName, AppEventPrvtSoeGroup, uiFlag.u32);
		ptPrvtSoeTab++;
	}
}

void AppEventPrvtOptPowerUpIni()
{
	WORD i;
	const tagPrvtOptTab* ptPrvtOptTab;
	SalStatus::Flags  uiFlag;
	// ˫�������ʼ��
	AppEventPrvtOptGroup.PowerUpIni("�ڲ�����", "AppEventPrvtOptGroup", CN_NUM_PRVT_OPT, CN_NUM_RPT_PRVT_OPT);
	ptPrvtOptTab = &g_tPrvtOptTab[0];
	uiFlag.u32 = 0;
	for (i = 0; i < CN_NUM_PRVT_OPT; i++)
	{
		AppEventPrvtOpt[i].BlPowerUpIni(ptPrvtOptTab->byName, ptPrvtOptTab->byPinName, AppEventPrvtOptGroup, uiFlag.u32);
		ptPrvtOptTab++;
	}
}

// ״̬�������
// ע���Ƚ���״̬����,�ٽ��в�������
#define CN_ENA_CTRL_SJ    (1)    //��Ƽ�¼����
void AppEventActOutRef_S()
{
	// �����Ƽ�¼(ʹ��)
#if(CN_ENA_CTRL_SJ)
	if (g_tActQueue.wSjCtrl)
	{
		return;
	}
#endif
	// �澯����
	if ((g_tActQueue.wRptr != g_tActQueue.wWptr) || (g_tActQueue.wFlag == CN_RPT_FULL))
	{
		register WORD wRptr, wIndex;
		register tagCosEvent6* ptEvent;
		register tagSjEvent* ptSjEvent;
		register u32value* pu32value;
		SalDateStamp  cDateTemp;

		if (g_tActQueue.wFlag == CN_RPT_FULL)
		{
			g_tActQueue.wRptr = g_tActQueue.wWptr;
			g_tActQueue.wFlag = CN_RPT_NULL;
		}
		wRptr = g_tActQueue.wRptr;
		ptEvent = &g_tActQueue.tEvent[wRptr];
		wIndex = ptEvent->wIndex;
		if (wIndex < CN_NUM_ACT)
		{
			pu32value = (u32value*)ptEvent->iMeaValue;
			// ����
			AppEventAct[wIndex].UpdateStatus(pu32value[0], pu32value[1], pu32value[2], pu32value[3], pu32value[4], pu32value[5]);
			// ״̬+ʱ��
			cDateTemp.usL = ptEvent->tTime.dwUSecond_L;
			cDateTemp.usH = ptEvent->tTime.dwUSecond_H;
			cDateTemp.q.q = ptEvent->tTime.dwLeapSecFlg;
			AppEventAct[wIndex].Update(ptEvent->wState, cDateTemp);

#if(CN_ENA_CTRL_SJ)
			// ��Ƽ�¼����
			{
				ptSjEvent = &g_tActQueue.tSjEvent[g_tActQueue.wSjWptr];
				ptSjEvent->wIndex = ptEvent->iMeaValue[EN_VAILD_SRC_INDEX];
				ptSjEvent->wState = ptEvent->wState;
				ptSjEvent->wResult = ptEvent->iMeaValue[EN_VAILD_FAIL];
				ptSjEvent->tTime = ptEvent->tTime;
				if (++g_tActQueue.wSjWptr >= CN_NUM_RPT_ACT)
				{
					g_tActQueue.wSjWptr = 0;
				}
				if (g_tActQueue.wSjWptr == g_tActQueue.wSjRptr)
				{
					g_tActQueue.wSjFlag = CN_RPT_FULL;
				}
			}
#endif
		}
		if (++g_tActQueue.wRptr >= CN_NUM_RPT_ACT)
		{
			g_tActQueue.wRptr = 0;
		}
	}
}
// ��Ƽ�¼
void AppEventSjOutRef_Task()
{
#if(CN_ENA_CTRL_SJ)
	SalDateStamp cDateTemp;
	g_tActQueue.wSjCtrl = TRUE;
	// �ȴ�2ms
	MsSleep(2);
	if ((g_tActQueue.wSjRptr != g_tActQueue.wSjWptr) || (g_tActQueue.wSjFlag == CN_RPT_FULL))
	{
		register tagSjEvent* ptSjEvent;
		register WORD          wState, wIndex, wResult, i;

		if (g_tActQueue.wSjFlag == CN_RPT_FULL)
		{
			g_tActQueue.wSjRptr = g_tActQueue.wSjWptr;
			g_tActQueue.wSjFlag = CN_RPT_NULL;
		}

		for (i = 0; i < CN_NUM_RPT_ACT; i++)
		{
			ptSjEvent = &g_tActQueue.tSjEvent[g_tActQueue.wSjRptr];
			wIndex = ptSjEvent->wIndex;
			wResult = ptSjEvent->wResult;
			wState = ptSjEvent->wState;

			cDateTemp.usL = ptSjEvent->tTime.dwUSecond_L;
			cDateTemp.usH = ptSjEvent->tTime.dwUSecond_H;
			cDateTemp.q.q = ptSjEvent->tTime.dwLeapSecFlg;

			if ((wIndex < CN_NUM_GOIN) && (wResult < g_tCEnumTab[EN_CENUM_FAIL_RET - EN_CENUM_STR].byEnNum))
			{
				if (wState == 0)
				{
					SjContrlRecord.CreatRecord(cDateTemp, "GOOSE���", "APP", g_tGoInTab[wIndex].byName, "GOOSE���Ʒ�ָ�����", "���ڷ�����", g_tCEnumTab[EN_CENUM_FAIL_RET - EN_CENUM_STR].eEnumDes[wResult].des, 0);
				}
				else if (wState == 1)
				{
					SjContrlRecord.CreatRecord(cDateTemp, "GOOSE���", "APP", g_tGoInTab[wIndex].byName, "GOOSE���ƺ�ָ�����", "���ڷ�����", g_tCEnumTab[EN_CENUM_FAIL_RET - EN_CENUM_STR].eEnumDes[wResult].des, 0);
				}
				else if (wState == 2)
				{
					SjContrlRecord.CreatRecord(cDateTemp, "GOOSE���", "APP", g_tGoInTab[wIndex].byName, "GOOSE���Ʒ�ָ�����", "���ں�����", g_tCEnumTab[EN_CENUM_FAIL_RET - EN_CENUM_STR].eEnumDes[wResult].des, 0);
				}
				else if (wState == 3)
				{
					SjContrlRecord.CreatRecord(cDateTemp, "GOOSE���", "APP", g_tGoInTab[wIndex].byName, "GOOSE���ƺ�ָ�����", "���ں�����", g_tCEnumTab[EN_CENUM_FAIL_RET - EN_CENUM_STR].eEnumDes[wResult].des, 0);
				}
			}
			if (++g_tActQueue.wSjRptr >= CN_NUM_RPT_ACT)
			{
				g_tActQueue.wSjRptr = 0;
			}
			if (g_tActQueue.wSjRptr == g_tActQueue.wSjWptr)
			{
				break;
			}
		}
	}
	g_tActQueue.wSjCtrl = FALSE;
#endif
}
// �澯����
void AppEventAlmOutRef_S()
{
	if ((g_tAlmQueue.wRptr != g_tAlmQueue.wWptr) || (g_tAlmQueue.wFlag == CN_RPT_FULL))
	{
		register WORD wRptr, wIndex;
		register tagCosEvent* ptEvent;
		register u32value* pu32value;

		if (g_tAlmQueue.wFlag == CN_RPT_FULL)
		{
			g_tAlmQueue.wRptr = g_tAlmQueue.wWptr;
			g_tAlmQueue.wFlag = CN_RPT_NULL;
		}
		wRptr = g_tAlmQueue.wRptr;
		ptEvent = &g_tAlmQueue.tEvent[wRptr];
		wIndex = ptEvent->wIndex;
		if (wIndex < CN_NUM_ALM)
		{
			pu32value = (u32value*)ptEvent->iMeaValue;
			AppEventWarn[wIndex].UpdateStatus(pu32value[0], pu32value[1], pu32value[2]);
			AppEventWarn[wIndex].Update(ptEvent->wState);
		}
		if (++g_tAlmQueue.wRptr >= CN_NUM_RPT_ALM)
		{
			g_tAlmQueue.wRptr = 0;
		}
	}
}
// �Լ�����
void AppEventChkOutRef_S()
{
	if ((g_tChkQueue.wRptr != g_tChkQueue.wWptr) || (g_tChkQueue.wFlag == CN_RPT_FULL))
	{

		register WORD wRptr, wIndex;
		register tagCosEvent* ptEvent;
		register u32value* pu32value;

		if (g_tChkQueue.wFlag == CN_RPT_FULL)
		{
			g_tChkQueue.wRptr = g_tChkQueue.wWptr;
			g_tChkQueue.wFlag = CN_RPT_NULL;
		}
		wRptr = g_tChkQueue.wRptr;
		ptEvent = &g_tChkQueue.tEvent[wRptr];
		wIndex = ptEvent->wIndex;
		if (wIndex < CN_NUM_CHK)
		{
			pu32value = (u32value*)ptEvent->iMeaValue;
			AppEventChek[wIndex].UpdateStatus(pu32value[0], pu32value[1], pu32value[2]);
			AppEventChek[wIndex].Update(ptEvent->wState);
		}
		if (++g_tChkQueue.wRptr >= CN_NUM_RPT_CHK)
		{
			g_tChkQueue.wRptr = 0;
		}
	}
}
// Ӳ���������ϵ��ʼ״̬����
void AppEventDiOutRef_Init()
{
	if (g_tagIO.byDIFstToSoe)
	{
		SalDateStamp cDateTemp;
		StatusQ  StatusQTem;
		register UINT32 i;
		register BOOL* pbEvent;

		pbEvent = g_tagIO.bDIHldIn;
		cDateTemp.usL = g_tagPub.tSysTimeUTC.dwUSecond_L;
		cDateTemp.usH = g_tagPub.tSysTimeUTC.dwUSecond_H;
		cDateTemp.q.q = g_tagPub.tSysTimeUTC.dwLeapSecFlg;
		StatusQTem.u32 = 0;
		for (i = 0; i < CN_NUM_DI; i++)
		{
			AppEventDISoe[i].SetState((UINT32)pbEvent[i], cDateTemp, StatusQTem);
		}
		g_tagIO.byDIFstToSoe = FALSE;
	}
}

// Ӳ�����������
void AppEventDiOutRef_S()
{
	// Ӳ��������
	if ((g_tDiQueue.wRptr != g_tDiQueue.wWptr) || (g_tDiQueue.wFlag == CN_RPT_FULL))
	{
		SalDateStamp cDateTemp;
		register WORD  wRptr, wIndex;
		register tagSoeEvent* ptEvent;

		if (g_tDiQueue.wFlag == CN_RPT_FULL)
		{
			g_tDiQueue.wRptr = g_tDiQueue.wWptr;
			g_tDiQueue.wFlag = CN_RPT_NULL;
		}
		wRptr = g_tDiQueue.wRptr;
		ptEvent = &g_tDiQueue.tEvent[wRptr];
		wIndex = ptEvent->wIndex;
		if (wIndex < CN_NUM_DI)
		{
			cDateTemp.usL = ptEvent->tTime.dwUSecond_L;
			cDateTemp.usH = ptEvent->tTime.dwUSecond_H;
			cDateTemp.q.q = ptEvent->tTime.dwLeapSecFlg;
			AppEventDISoe[wIndex].Update((UINT32)ptEvent->wState, cDateTemp);
		}
		if (++g_tDiQueue.wRptr >= CN_NUM_RPT_DI)
		{
			g_tDiQueue.wRptr = 0;
		}
	}
}
// ˫�������ϵ��ʼ״̬����
void AppEventDpiOutRef_Init()
{
	if (g_tagIO.byDpiFstToSoe)
	{
		SalDateStamp cDateTemp;
		StatusQ  StatusQTem;
		register UINT32 i;
		register BOOL* pbEvent;
		pbEvent = g_tagIO.byDpiIn;
		cDateTemp.usL = g_tagPub.tSysTimeUTC.dwUSecond_L;
		cDateTemp.usH = g_tagPub.tSysTimeUTC.dwUSecond_H;
		cDateTemp.q.q = g_tagPub.tSysTimeUTC.dwLeapSecFlg;
		StatusQTem.u32 = 0;
		for (i = 0; i < CN_NUM_DPI; i++)
		{
			AppEventDpiSoe[i].SetState((UINT32)pbEvent[i], cDateTemp, StatusQTem);
		}
		g_tagIO.byDpiFstToSoe = FALSE;
	}
}

// ˫���������
void AppEventDpiOutRef_S()
{
	// ˫���������
	if ((g_tDpiQueue.wRptr != g_tDpiQueue.wWptr) || (g_tDpiQueue.wFlag == CN_RPT_FULL))
	{
		SalDateStamp cDateTemp;
		register WORD  wRptr, wIndex;
		register tagSoeEvent* ptEvent;

		if (g_tDpiQueue.wFlag == CN_RPT_FULL)
		{
			g_tDpiQueue.wRptr = g_tDpiQueue.wWptr;
			g_tDpiQueue.wFlag = CN_RPT_NULL;
		}
		wRptr = g_tDpiQueue.wRptr;
		ptEvent = &g_tDpiQueue.tEvent[wRptr];
		wIndex = ptEvent->wIndex;
		if (wIndex < CN_NUM_DPI)
		{
			cDateTemp.usL = ptEvent->tTime.dwUSecond_L;
			cDateTemp.usH = ptEvent->tTime.dwUSecond_H;
			cDateTemp.q.q = ptEvent->tTime.dwLeapSecFlg;
			AppEventDpiSoe[wIndex].Update((UINT32)ptEvent->wState, cDateTemp);
		}
		if (++g_tDpiQueue.wRptr >= CN_NUM_RPT_DPI)
		{
			g_tDpiQueue.wRptr = 0;
		}
	}
}
// GOOSE��������
void AppEventGoInOutRef_S()
{
	if ((g_tGoInQueue.wRptr != g_tGoInQueue.wWptr) || (g_tGoInQueue.wFlag == CN_RPT_FULL))
	{
		register WORD  wRptr, wIndex;
		register tagSoeEvent* ptEvent;
		SalDateStamp cDateTemp;
		StatusQ  StatusQTem;

		if (g_tGoInQueue.wFlag == CN_RPT_FULL)
		{
			g_tGoInQueue.wRptr = g_tGoInQueue.wWptr;
			g_tGoInQueue.wFlag = CN_RPT_NULL;
		}
		wRptr = g_tGoInQueue.wRptr;
		ptEvent = &g_tGoInQueue.tEvent[wRptr];
		wIndex = ptEvent->wIndex;
		if (wIndex < CN_NUM_GOIN)
		{
			cDateTemp.usL = ptEvent->tTime.dwUSecond_L;
			cDateTemp.usH = ptEvent->tTime.dwUSecond_H;
			cDateTemp.q.q = ptEvent->tTime.dwLeapSecFlg;

			StatusQTem.st.test = ((ptEvent->wQ) & CN_GOIN_Test) >> 2;
			StatusQTem.st.invalid = ((ptEvent->wQ) & CN_GOIN_Invalid);
			AppEventGoInSoe[wIndex].Update((UINT32)ptEvent->wState, cDateTemp, StatusQTem);
		}
		if (++g_tGoInQueue.wRptr >= CN_NUM_RPT_GOIN)
		{
			g_tGoInQueue.wRptr = 0;
		}
	}
}
// GOOSE��������
void AppEventGoOutOutRef_S()
{
	if ((g_tGoOutQueue.wRptr != g_tGoOutQueue.wWptr) || (g_tGoOutQueue.wFlag == CN_RPT_FULL))
	{
		register WORD  wRptr, wIndex;
		register tagSoeEvent* ptEvent;
		SalDateStamp cDateTemp;

		if (g_tGoOutQueue.wFlag == CN_RPT_FULL)
		{
			g_tGoOutQueue.wRptr = g_tGoOutQueue.wWptr;
			g_tGoOutQueue.wFlag = CN_RPT_NULL;
		}
		wRptr = g_tGoOutQueue.wRptr;
		ptEvent = &g_tGoOutQueue.tEvent[wRptr];
		wIndex = ptEvent->wIndex;
		if (wIndex < CN_NUM_GOOUT)
		{
			cDateTemp.usL = ptEvent->tTime.dwUSecond_L;
			cDateTemp.usH = ptEvent->tTime.dwUSecond_H;
			cDateTemp.q.q = ptEvent->tTime.dwLeapSecFlg;
			AppEventGoOutSoe[wIndex].Update((UINT32)ptEvent->wState, cDateTemp);
		}
		if (++g_tGoOutQueue.wRptr >= CN_NUM_RPT_GOOUT)
		{
			g_tGoOutQueue.wRptr = 0;
		}
	}
}
// ��������
void AppEventDoOutRef_S()
{
	if ((g_tDoQueue.wRptr != g_tDoQueue.wWptr) || (g_tDoQueue.wFlag == CN_RPT_FULL))
	{

		register WORD  wRptr, wIndex;
		register tagSoeEvent* ptEvent;
		SalDateStamp cDateTemp;

		if (g_tDoQueue.wFlag == CN_RPT_FULL)
		{
			g_tDoQueue.wRptr = g_tDoQueue.wWptr;
			g_tDoQueue.wFlag = CN_RPT_NULL;
		}
		wRptr = g_tDoQueue.wRptr;
		ptEvent = &g_tDoQueue.tEvent[wRptr];
		wIndex = ptEvent->wIndex;
		if (wIndex < CN_NUM_DO)
		{
			cDateTemp.usL = ptEvent->tTime.dwUSecond_L;
			cDateTemp.usH = ptEvent->tTime.dwUSecond_H;
			cDateTemp.q.q = ptEvent->tTime.dwLeapSecFlg;
			AppEventDOSoe[wIndex].Update((UINT32)ptEvent->wState, cDateTemp);
		}
		if (++g_tDoQueue.wRptr >= CN_NUM_RPT_DO)
		{
			g_tDoQueue.wRptr = 0;
		}
	}
}
// ָʾ��״̬����
void AppEventLedOutRef_S()
{
	BYTE byLedPtr = g_tagIO.byLedPtr;
	if (byLedPtr < CN_NUM_LED)
	{
		AppEventLedSoe[byLedPtr].Update(g_tagIO.bLedOut[byLedPtr]);
	}
}
#if 0
void AppEventActOutRef()
{
	register UINT32 i;
	register tagActQueue* ptActQueue;
	register tagActEvent* ptActEvent;
	register u32value* pu32value;

	SalDateStamp  cDateTemp;
	ptActQueue = g_tActQueue;
	// ʵʱ���µķ�ʽ,���޸�Ϊ��λ���µķ�ʽ

	register WORD wIndex, wResult;
	for (i = 0; i < CN_NUM_ACT; i++)
	{
		if (ptActQueue->byBakVaild)
		{
			ptActEvent = &ptActQueue->tActEventBak;
			pu32value = (u32value*)(&ptActEvent->tRecValue6.iMeaValue[0]);
			// ����
			AppEventAct[i].UpdateStatus(pu32value[0], pu32value[1], pu32value[2], pu32value[3], pu32value[4], pu32value[5]);
			// ״̬+ʱ��
			cDateTemp.usL = ptActEvent->tActT.dwUSecond_L;
			cDateTemp.usH = ptActEvent->tActT.dwUSecond_H;
			cDateTemp.q.q = ptActEvent->tActT.dwLeapSecFlg;
			AppEventAct[i].Update(ptActEvent->bActIn, cDateTemp);
			ptActQueue->byBakVaild = FALSE;
			// ������Ƽ�¼
			wIndex = ptActEvent->tRecValue6.iMeaValue[EN_VAILD_SRC_INDEX];
			wResult = ptActEvent->tRecValue6.iMeaValue[EN_VAILD_FAIL];
			if ((wIndex < CN_NUM_GOIN) && (wResult < g_tCEnumTab[EN_CENUM_FAIL_RET - EN_CENUM_STR].byEnNum))
			{
				if (ptActEvent->bActIn == 0)
				{
					SjContrlRecord.CreatRecord("GOOSE���", "APP", g_tGoInTab[wIndex].byName, "GOOSE���Ʒ�ָ�����", "���ڷ�����", g_tCEnumTab[EN_CENUM_FAIL_RET - EN_CENUM_STR].eEnumDes[wResult].des, 0);
				}
				else if (ptActEvent->bActIn == 1)
				{
					SjContrlRecord.CreatRecord("GOOSE���", "APP", g_tGoInTab[wIndex].byName, "GOOSE���ƺ�ָ�����", "���ڷ�����", g_tCEnumTab[EN_CENUM_FAIL_RET - EN_CENUM_STR].eEnumDes[wResult].des, 0);
				}
				else if (ptActEvent->bActIn == 2)
				{
					SjContrlRecord.CreatRecord("GOOSE���", "APP", g_tGoInTab[wIndex].byName, "GOOSE���Ʒ�ָ�����", "���ں�����", g_tCEnumTab[EN_CENUM_FAIL_RET - EN_CENUM_STR].eEnumDes[wResult].des, 0);
				}
				else if (ptActEvent->bActIn == 3)
				{
					SjContrlRecord.CreatRecord("GOOSE���", "APP", g_tGoInTab[wIndex].byName, "GOOSE���ƺ�ָ�����", "���ں�����", g_tCEnumTab[EN_CENUM_FAIL_RET - EN_CENUM_STR].eEnumDes[wResult].des, 0);
				}
			}
		}
		if (ptActQueue->byFlag == EN_ACTS_EVENT_STOP)
		{
			ptActEvent = &ptActQueue->tActEvent;
			pu32value = (u32value*)(&ptActEvent->tRecValue6.iMeaValue[0]);
			// ����
			AppEventAct[i].UpdateStatus(pu32value[0], pu32value[1], pu32value[2], pu32value[3], pu32value[4], pu32value[5]);
			// ״̬+ʱ��
			cDateTemp.usL = ptActEvent->tActT.dwUSecond_L;
			cDateTemp.usH = ptActEvent->tActT.dwUSecond_H;
			cDateTemp.q.q = ptActEvent->tActT.dwLeapSecFlg;
			AppEventAct[i].Update(ptActEvent->bActIn, cDateTemp);
			ptActQueue->byFlag = EN_ACTS_EVENT_NULL;
			// ������Ƽ�¼
			wIndex = ptActEvent->tRecValue6.iMeaValue[EN_VAILD_SRC_INDEX];
			wResult = ptActEvent->tRecValue6.iMeaValue[EN_VAILD_FAIL];
			if ((wIndex < CN_NUM_GOIN) && (wResult < g_tCEnumTab[EN_CENUM_FAIL_RET - EN_CENUM_STR].byEnNum))
			{
				if (ptActEvent->bActIn == 0)
				{
					SjContrlRecord.CreatRecord("GOOSE���", "APP", g_tGoInTab[wIndex].byName, "GOOSE���Ʒ�ָ�����", "���ڷ�����", g_tCEnumTab[EN_CENUM_FAIL_RET - EN_CENUM_STR].eEnumDes[wResult].des, 0);
				}
				else if (ptActEvent->bActIn == 1)
				{
					SjContrlRecord.CreatRecord("GOOSE���", "APP", g_tGoInTab[wIndex].byName, "GOOSE���ƺ�ָ�����", "���ڷ�����", g_tCEnumTab[EN_CENUM_FAIL_RET - EN_CENUM_STR].eEnumDes[wResult].des, 0);
				}
				else if (ptActEvent->bActIn == 2)
				{
					SjContrlRecord.CreatRecord("GOOSE���", "APP", g_tGoInTab[wIndex].byName, "GOOSE���Ʒ�ָ�����", "���ں�����", g_tCEnumTab[EN_CENUM_FAIL_RET - EN_CENUM_STR].eEnumDes[wResult].des, 0);
				}
				else if (ptActEvent->bActIn == 3)
				{
					SjContrlRecord.CreatRecord("GOOSE���", "APP", g_tGoInTab[wIndex].byName, "GOOSE���ƺ�ָ�����", "���ں�����", g_tCEnumTab[EN_CENUM_FAIL_RET - EN_CENUM_STR].eEnumDes[wResult].des, 0);
				}
			}
		}
		ptActQueue++;
	}
}
// ״̬�������
void AppEventCosOutRef()
{
	register UINT32    i;
	register BOOL* pbEvent, * pbEventXor;
	register u32value* pu32value;
	// ʵʱ���µķ�ʽ,���޸�Ϊ��λ���µķ�ʽ	
	//if(G_Sys_Div4_2)
	{
		pbEventXor = g_tAlmState.bAlmXor;
		pbEvent = g_tAlmState.bAlmOut;
		// ʵʱ���µķ�ʽ,���޸�Ϊ��λ���µķ�ʽ
		for (i = 0; i < CN_NUM_ALM; i++)
		{
			if (pbEventXor[i])
			{
				pu32value = (u32value*)g_tAlmState.tRecValue[i].iMeaValue;
				AppEventWarn[i].UpdateStatus(pu32value[0], pu32value[1], pu32value[2]);
				AppEventWarn[i].Update(pbEvent[i]);
			}
		}
	}
	if (G_Sys_Div4_3)
	{
		pbEventXor = g_tChkState.bChkXor;
		pbEvent = g_tChkState.bChkOut;
		// ʵʱ���µķ�ʽ,���޸�Ϊ��λ���µķ�ʽ
		for (i = 0; i < CN_NUM_CHK; i++)
		{
			if (pbEventXor[i])
			{
				pu32value = (u32value*)g_tChkState.tRecValue[i].iMeaValue;
				AppEventChek[i].UpdateStatus(pu32value[0], pu32value[1], pu32value[2]);
				AppEventChek[i].Update(pbEvent[i]);
			}
		}
	}
}
// ��λ�������
void AppEventSoeOutRef()
{
	register UINT32 i, j, k;
	register BOOL* pbEvent;
	register BOOL* pbEventXor;
	register WORD* pwEventQ;
	register DWORD* pdwHldXor;
	register DWORD dwHldXorTem;
	register tagTimeUTC* ptTimeUTC;

	SalDateStamp cDateTemp;
	StatusQ  StatusQTem;
	const tagBoardIoTab* ptBoardIoTab;

	ptBoardIoTab = &g_tBoardDITab[0];
	pdwHldXor = g_tagIO.dwDIHldXor32;
	pbEvent = g_tagIO.bDIHldIn;
	ptTimeUTC = g_tagIO.tDIHldUTC;
	if (g_tagIO.byDIFstToSoe)
	{
		cDateTemp.usL = g_tagPub.tSysTimeUTC.dwUSecond_L;
		cDateTemp.usH = g_tagPub.tSysTimeUTC.dwUSecond_H;
		cDateTemp.q.q = g_tagPub.tSysTimeUTC.dwLeapSecFlg;
		StatusQTem.u32 = 0;
		for (i = 0; i < CN_NUM_DI; i++)
		{
			AppEventDISoe[i].SetState((UINT32)pbEvent[i], cDateTemp, StatusQTem);
		}
		g_tagIO.byDIFstToSoe = FALSE;
	}
	else
	{
		for (i = 0; i < CN_NUM_BOARD_DI; i++, ptBoardIoTab++)
		{
			dwHldXorTem = pdwHldXor[i];
			if (dwHldXorTem != 0)
			{
				for (j = 0, k = ptBoardIoTab->wIndexStr; j < ptBoardIoTab->wSrcIndexNum; j++, k++)
				{
					if (dwHldXorTem & g_dwBit[j])
					{
						cDateTemp.usL = ptTimeUTC[k].dwUSecond_L;
						cDateTemp.usH = ptTimeUTC[k].dwUSecond_H;
						cDateTemp.q.q = ptTimeUTC[k].dwLeapSecFlg;
						AppEventDISoe[k].Update(pbEvent[k], cDateTemp);
					}
				}
			}
		}
	}
	// ��ˢ��״̬,���Ǳ�λ״̬����???
	pbEvent = g_tagIO.bGoIn;
	pbEventXor = g_tagIO.bGoInXor;
	pwEventQ = g_tagIO.wGoInQ;
	StatusQTem.u32 = 0;
	for (i = 0; i < CN_NUM_GOIN; i++)
	{
		if (pbEventXor[i])
		{
			StatusQTem.st.test = (pwEventQ[i] & CN_GOIN_Test) >> 2;
			StatusQTem.st.invalid = (pwEventQ[i] & CN_GOIN_Invalid);
			AppEventGoInSoe[i].Update(pbEvent[i], StatusQTem);
		}
	}
	// ��ң���ݲ�ʹ��
	//pbEvent=g_bFlag;
	//for(i=0;i<CN_NUM_FLAG;i++)
	//{
	//	AppEventFlagSoe[i].Update(*pbEvent++);
	//}
	// ��ˢ��״̬
	pbEvent = g_tagIO.bDOOut;
	pbEventXor = g_tagIO.bDOOutXor;
	for (i = 0; i < CN_NUM_DO; i++)
	{
		if (pbEventXor[i])
		{
			AppEventDOSoe[i].Update(pbEvent[i]);
		}
	}
	// ��ˢ��״̬
	pbEvent = g_tagIO.bGoOut;
	pbEventXor = g_tagIO.bGoOutXor;
	for (i = 0; i < CN_NUM_GOOUT; i++)
	{
		if (pbEventXor[i])
		{
			AppEventGoOutSoe[i].Update(pbEvent[i]);
		}
	}
	// ָʾ��״̬����
	BYTE byLedPtr = g_tagIO.byLedPtr;
	if (byLedPtr < CN_NUM_LED)
	{
		AppEventLedSoe[byLedPtr].Update(g_tagIO.bLedOut[byLedPtr]);
	}
	// ˫���������
	pbEvent = g_tagIO.byDpiIn;
	pbEventXor = g_tagIO.byDpiInXor;
	ptTimeUTC = g_tagIO.tDpiUTC;

	if (g_tagIO.byDpiFstToSoe)
	{
		cDateTemp.usL = g_tagPub.tSysTimeUTC.dwUSecond_L;
		cDateTemp.usH = g_tagPub.tSysTimeUTC.dwUSecond_H;
		cDateTemp.q.q = g_tagPub.tSysTimeUTC.dwLeapSecFlg;
		StatusQTem.u32 = 0;
		for (i = 0; i < CN_NUM_DPI; i++)
		{
			AppEventDpiSoe[i].SetState((UINT32)pbEvent[i], cDateTemp, StatusQTem);
		}
		g_tagIO.byDpiFstToSoe = FALSE;
	}
	else
	{
		for (i = 0; i < CN_NUM_DPI; i++, ptTimeUTC++)
		{
			if (pbEventXor[i])
			{
				cDateTemp.usL = ptTimeUTC->dwUSecond_L;
				cDateTemp.usH = ptTimeUTC->dwUSecond_H;
				cDateTemp.q.q = ptTimeUTC->dwLeapSecFlg;
				AppEventDpiSoe[i].Update(pbEvent[i], cDateTemp);
			}
		}
	}
}
#endif
void AppEventPowerUpIni()
{
	// ����
	AppEventActPowerUpIni();
	AppEventWarnPowerUpIni();
	AppEventChekPowerUpIni();
	AppEventRunPowerUpIni();
	AppEventOptPowerUpIni();
	// SOE
	AppEventDISoePowerUpIni();
	AppEventGoInSoePowerUpIni();
	AppEventFlagSoePowerUpIni();
	AppEventDoSoePowerUpIni();
	AppEventGoOutSoePowerUpIni();
	AppEventLedSoePowerUpIni();
	// ˫��SOE
	AppEventDpiSoePowerUpIni();
	// �ڲ�����
	AppEventPrvtSoePowerUpIni();
	AppEventPrvtOptPowerUpIni();

	HmiViewEventPool.PowerUpIni(CN_NUM_RPT_DI);
}
#if 0
// ����ˢ��
void AppEventOutRef()
{
	AppEventActOutRef();
	AppEventCosOutRef();
	AppEventSoeOutRef();
}
#endif
void AppEventOutRef_S()
{
	// �ϵ��һ֡��������
	AppEventDiOutRef_Init();
	AppEventDpiOutRef_Init();

	if (G_Sys_Div8_1)
	{
		AppEventActOutRef_S();
	}
	else if (G_Sys_Div8_2)
	{
		AppEventAlmOutRef_S();
	}
	else if (G_Sys_Div8_3)
	{
		AppEventChkOutRef_S();
	}
	else if (G_Sys_Div8_4)
	{
		AppEventDiOutRef_S();
	}
	else if (G_Sys_Div8_5)
	{
		AppEventDpiOutRef_S();
	}
	else if (G_Sys_Div8_6)
	{
		AppEventGoInOutRef_S();
	}
	else if (G_Sys_Div8_7)
	{
		AppEventGoOutOutRef_S();
	}
	else
	{
		AppEventDoOutRef_S();
	}
	AppEventLedOutRef_S();
}
// ��������ӿ�
void AppEventRunRef(WORD wRunIndex)
{
	if (wRunIndex < CN_NUM_RUN)
	{
		AppEventRun[wRunIndex].Update(TRUE);
	}
}
// ��������ӿ�
void AppEventOptRef(WORD wOptIndex)
{
	if (wOptIndex < CN_NUM_OPT)
	{
		AppEventOpt[wOptIndex].Update(TRUE);
	}
}
// ��������ӿڣ���������
void AppEventOptValueRef(WORD wOptIndex, DWORD iMeaValue1, DWORD iMeaValue2, DWORD iMeaValue3)
{
	u32value  u32value1, u32value2, u32value3;
	if (wOptIndex < CN_NUM_OPT)
	{
		u32value1.u32 = iMeaValue1;
		u32value2.u32 = iMeaValue2;
		u32value3.u32 = iMeaValue3;

		AppEventOpt[wOptIndex].UpdateStatus(u32value1, u32value2, u32value3);
		AppEventOpt[wOptIndex].Update(TRUE);
	}
}
// �ڲ�����ӿ�
void AppEventPrvtSoeRef(WORD wPrvtSoeIndex, BOOL bState)
{
	if (wPrvtSoeIndex < CN_NUM_PRVT_SOE)
	{
		AppEventPrvtSoe[wPrvtSoeIndex].Update(bState);
	}
}

// �ڲ������ӿ�
void AppEventPrvtOptRef(WORD wPrvtOptIndex)
{
	if (wPrvtOptIndex < CN_NUM_PRVT_OPT)
	{
		AppEventPrvtOpt[wPrvtOptIndex].Update(TRUE);
	}
}

// �������ӿ�
INT32 AppEventClear(WORD wIndex)
{
	static BOOL bFlag = 0;
	INT32 res = 0;
	if (bFlag)
	{
		return -2;
	}
	bFlag = TRUE;
	switch (wIndex)
	{
	case EN_DTYPE_ACT:
		AppEventActGroup.ClearEvent();
		AppEventOptRef(EN_OPT_ACT_DEl);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "GOOSE��������������", 0, 0, 0, 0);
		break;
	case EN_DTYPE_ALM:
		AppEventWarnGroup.ClearEvent();
		AppEventOptRef(EN_OPT_ALM_DEl);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "����澯�������", 0, 0, 0, 0);
		break;
	case EN_DTYPE_CHK:
		AppEventChekGroup.ClearEvent();
		AppEventOptRef(EN_OPT_CHK_DEl);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "����Լ��������", 0, 0, 0, 0);
		break;
	case EN_CFG_RUN:
		AppEventRunGroup.ClearEvent();
		AppEventPrvtOptRef(EN_PRVT_OPT_RUN_DEl);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "��������������", 0, 0, 0, 0);
		break;
	case EN_CFG_OPT:
		AppEventOptGroup.ClearEvent();
		AppEventPrvtOptRef(EN_PRVT_OPT_OPT_DEl);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "��������������", 0, 0, 0, 0);
		break;
	case EN_DTYPE_DI:
		AppEventDISoeGroup.ClearEvent();
		AppEventOptRef(EN_OPT_DI_SOE_DEl);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "���Ӳ����SOE�������", 0, 0, 0, 0);
		break;
	case EN_DTYPE_GOIN:
		AppEventGoInSoeGroup.ClearEvent();
		AppEventOptRef(EN_OPT_GOIN_SOE_DEl);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "���GOOSE����SOE�������", 0, 0, 0, 0);
		break;
	case EN_DTYPE_FLAG:
		AppEventFlagSoeGroup.ClearEvent();
		AppEventOptRef(EN_OPT_FLAG_SOE_DEl);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "�����ң���������", 0, 0, 0, 0);
		break;
	case EN_DTYPE_DO:
		AppEventDOSoeGroup.ClearEvent();
		AppEventOptRef(EN_OPT_DO_SOE_DEl);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "���Ӳ����SOE�������", 0, 0, 0, 0);
		break;
	case EN_DTYPE_GOOUT:
		AppEventGoOutSoeGroup.ClearEvent();
		AppEventOptRef(EN_OPT_GOOUT_SOE_DEl);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "���GOOSE����SOE�������", 0, 0, 0, 0);
		break;
	case EN_DTYPE_LED:
		AppEventLedSoeGroup.ClearEvent();
		AppEventOptRef(EN_OPT_LED_SOE_DEl);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "���ָʾ��SOE�������", 0, 0, 0, 0);
		break;
	case EN_DTYPE_DPI:
		AppEventDpiSoeGroup.ClearEvent();
		AppEventOptRef(EN_OPT_DPI_SOE_DEl);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "���˫��SOE�������", 0, 0, 0, 0);
		break;
	case EN_CFG_PRVT_SOE:
		AppEventPrvtSoeGroup.ClearEvent();
		AppEventPrvtOptRef(EN_PRVT_OPT_PRVT_SOE_DEl);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "����ڲ��������", 0, 0, 0, 0);
		break;
	case EN_CFG_PRVT_OPT:
		AppEventPrvtOptGroup.ClearEvent();
		AppEventPrvtOptRef(EN_PRVT_OPT_PRVT_OPT_DEl);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "����ڲ��������", 0, 0, 0, 0);
		break;
	case CN_NULL_PINNO:
		AppEventActGroup.ClearEvent();
		AppEventWarnGroup.ClearEvent();
		AppEventChekGroup.ClearEvent();
		AppEventRunGroup.ClearEvent();
		AppEventOptGroup.ClearEvent();
		AppEventDISoeGroup.ClearEvent();
		AppEventGoInSoeGroup.ClearEvent();
		AppEventFlagSoeGroup.ClearEvent();
		AppEventDOSoeGroup.ClearEvent();
		AppEventGoOutSoeGroup.ClearEvent();
		AppEventLedSoeGroup.ClearEvent();
		AppEventDpiSoeGroup.ClearEvent();
		AppEventPrvtSoeGroup.ClearEvent();
		AppEventPrvtOptGroup.ClearEvent();
		AppEventPrvtOptRef(EN_PRVT_OPT_EVENT_ALL_DEl);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "��������������", 0, 0, 0, 0);
		break;
	default:
		res = -1;
		break;
	}
	bFlag = FALSE;
	return res;
}

