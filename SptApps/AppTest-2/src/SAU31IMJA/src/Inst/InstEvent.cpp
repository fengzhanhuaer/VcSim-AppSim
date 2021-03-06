#include "InstResource.h"
// 事项队列
ApiEvent AppEventAct[CN_NUM_ACT];
ApiEvent AppEventWarn[CN_NUM_ALM];
ApiEvent AppEventChek[CN_NUM_CHK];
ApiEvent AppEventRun[CN_NUM_RUN];
ApiEvent AppEventOpt[CN_NUM_OPT];
// SOE队列
ApiEvent AppEventDISoe[CN_NUM_DI];
ApiEvent AppEventGoInSoe[CN_NUM_GOIN];
ApiEvent AppEventFlagSoe[CN_NUM_FLAG];
ApiEvent AppEventDOSoe[CN_NUM_DO];
ApiEvent AppEventGoOutSoe[CN_NUM_GOOUT];
ApiEvent AppEventLedSoe[CN_NUM_LED];
// 双点SOE队列
ApiEvent AppEventDpiSoe[CN_NUM_DPI];

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

ApiEventViewPool HmiViewEventPool;

void AppEventActPowerUpIni()
{
	WORD i;
	const tagActTab  *ptActTab;
	tagMEATab        *ptMEATab;
	StatusExInfoDesItem *peventData0,*peventData1,*peventData2,*peventData3,*peventData4,*peventData5;
	SalStatus::Flags  uiFlag;
	// 告警事项初始化
	AppEventActGroup.PowerUpIni("GOOSE命令事项",        "AppEventActGroup", CN_NUM_ACT,CN_NUM_RPT_ACT);
	ptMEATab =&g_tMEATab[0];
	ptActTab =&g_tActTab[0];
	uiFlag.u32=0;
	uiFlag.st.isUnDispValueChange=1;
	uiFlag.st.isDispQ=1;
	for(i=0;i<CN_NUM_ACT;i++)
	{
		AppEventAct[i].BlPowerUpIni(ptActTab->byName, ptActTab->byPinName, AppEventActGroup,uiFlag.u32);
		// 事项记录量初始化
		peventData0=(ptActTab->wValType1<EN_MEA_END)?&ptMEATab[ptActTab->wValType1].eventData:NULL;
		peventData1=(ptActTab->wValType2<EN_MEA_END)?&ptMEATab[ptActTab->wValType2].eventData:NULL;
		peventData2=(ptActTab->wValType3<EN_MEA_END)?&ptMEATab[ptActTab->wValType3].eventData:NULL;
		peventData3=(ptActTab->wValType4<EN_MEA_END)?&ptMEATab[ptActTab->wValType4].eventData:NULL;
		peventData4=(ptActTab->wValType5<EN_MEA_END)?&ptMEATab[ptActTab->wValType5].eventData:NULL;
		peventData5=(ptActTab->wValType6<EN_MEA_END)?&ptMEATab[ptActTab->wValType6].eventData:NULL;
		AppEventAct[i].ExInfoPowerUpIni(peventData0, peventData1, peventData2,peventData3, peventData4, peventData5);
		ptActTab++;
	}
}
void AppEventWarnPowerUpIni()
{
	WORD i;
	const tagAlmTab  *ptAlmTab;
	tagMEATab        *ptMEATab;
	StatusExInfoDesItem *peventData0,*peventData1,*peventData2;
	SalStatus::Flags  uiFlag;

	// 告警事项队列初始化
	AppEventWarnGroup.PowerUpIni("告警事项",        "AppEventWarnGroup", CN_NUM_ALM,CN_NUM_RPT_ALM);
	// 告警事项初始化
	ptAlmTab =&g_tAlmTab[0];
	ptMEATab =&g_tMEATab[0];
	uiFlag.u32=0;
	uiFlag.st.isDispQ=1;
	for(i=0;i<CN_NUM_ALM;i++)
	{
		AppEventWarn[i].BlPowerUpIni(ptAlmTab->byName, ptAlmTab->byPinName, AppEventWarnGroup,uiFlag.u32);
		// 事项记录量初始化
		peventData0=(ptAlmTab->wValType1<EN_MEA_END)?&ptMEATab[ptAlmTab->wValType1].eventData:NULL;
		peventData1=(ptAlmTab->wValType2<EN_MEA_END)?&ptMEATab[ptAlmTab->wValType2].eventData:NULL;
		peventData2=(ptAlmTab->wValType3<EN_MEA_END)?&ptMEATab[ptAlmTab->wValType3].eventData:NULL;
		AppEventWarn[i].ExInfoPowerUpIni(peventData0, peventData1, peventData2);
		ptAlmTab++;
	}
}

void AppEventChekPowerUpIni()
{
	WORD i;
	const tagChkTab  *ptChkTab;
	tagMEATab        *ptMEATab;
	StatusExInfoDesItem *peventData0,*peventData1,*peventData2;
	SalStatus::Flags  uiFlag;
	// 自检事项初始化
	AppEventChekGroup.PowerUpIni("自检事项",        "AppEventChekGroup", CN_NUM_CHK,CN_NUM_RPT_CHK);
	ptChkTab =&g_tChkTab[0];
	ptMEATab =&g_tMEATab[0];
	uiFlag.u32=0;
	uiFlag.st.isDispQ=1;
	for(i=0;i<CN_NUM_CHK;i++)
	{
		AppEventChek[i].BlPowerUpIni(ptChkTab->byName, ptChkTab->byPinName, AppEventChekGroup,uiFlag.u32);
		peventData0=(ptChkTab->wValType1<EN_MEA_END)?&ptMEATab[ptChkTab->wValType1].eventData:NULL;
		peventData1=(ptChkTab->wValType2<EN_MEA_END)?&ptMEATab[ptChkTab->wValType2].eventData:NULL;
		peventData2=(ptChkTab->wValType3<EN_MEA_END)?&ptMEATab[ptChkTab->wValType3].eventData:NULL;
		AppEventChek[i].ExInfoPowerUpIni(peventData0, peventData1, peventData2);
		ptChkTab++;
	}
}
void AppEventRunPowerUpIni()
{
	WORD i;
	const tagRunTab  *ptRunTab;
	SalStatus::Flags  uiFlag;
	
	AppEventRunGroup.PowerUpIni("运行事项",        "AppEventRunGroup", CN_NUM_RUN,CN_NUM_RPT_RUN);
	ptRunTab =&g_tRunTab[0];
	// 操作事项初始化
	uiFlag.u32=0;
	uiFlag.st.isUnDispRtn=1;
	uiFlag.st.isUnDispValueChange=1;
	uiFlag.st.isAutoRtn=1;
	uiFlag.st.isDispQ=1;
	for(i=0;i<CN_NUM_RUN;i++)
	{
		AppEventRun[i].BlPowerUpIni(ptRunTab->byName, ptRunTab->byPinName, AppEventRunGroup,uiFlag.u32);
		ptRunTab++;
	}
}

void AppEventOptPowerUpIni()
{
	WORD i;
	const tagOptTab  *ptOptTab;
	tagMEATab        *ptMEATab;
	StatusExInfoDesItem *peventData0,*peventData1,*peventData2;
	SalStatus::Flags  uiFlag;
	
	AppEventOptGroup.PowerUpIni("操作事项",        "AppEventOptGroup", CN_NUM_OPT,CN_NUM_RPT_OPT);
	// 操作事项初始化
	ptOptTab =&g_tOptTab[0];
	ptMEATab =&g_tMEATab[0];
	uiFlag.u32=0;
	uiFlag.st.isUnDispRtn=1;
	uiFlag.st.isUnDispValueChange=1;
	uiFlag.st.isAutoRtn=1;
	uiFlag.st.isDispQ=1;
	for(i=0;i<CN_NUM_OPT;i++)
	{
		AppEventOpt[i].BlPowerUpIni(ptOptTab->byName, ptOptTab->byPinName, AppEventOptGroup,uiFlag.u32);
		peventData0=(ptOptTab->wValType1<EN_MEA_END)?&ptMEATab[ptOptTab->wValType1].eventData:NULL;
		peventData1=(ptOptTab->wValType2<EN_MEA_END)?&ptMEATab[ptOptTab->wValType2].eventData:NULL;
		peventData2=(ptOptTab->wValType3<EN_MEA_END)?&ptMEATab[ptOptTab->wValType3].eventData:NULL;
		AppEventOpt[i].ExInfoPowerUpIni(peventData0, peventData1, peventData2);
		ptOptTab++;
	}
}

void AppEventDISoePowerUpIni()
{
	WORD i;
	const tagDiTab   *ptDiTab;
	SalStatus::Flags  uiFlag;
	AppEventDISoeGroup.PowerUpIni("硬开入SOE",        "AppEventDISoeGroup", CN_NUM_DI,CN_NUM_RPT_DI);
	uiFlag.u32=0;
	uiFlag.st.isDispQ=1;
	uiFlag.st.isDispUs=1;
	ptDiTab  =&g_tDiTab[0];
	for(i=0;i<CN_NUM_DI;i++)
	{
		AppEventDISoe[i].BlPowerUpIni(ptDiTab->byName, ptDiTab->byPinName, AppEventDISoeGroup,uiFlag.u32);
		ptDiTab++;
	}
}

void AppEventGoInSoePowerUpIni()
{
	WORD i;
	const tagGoInTab *ptGoInTab;
	SalStatus::Flags  uiFlag;
	AppEventGoInSoeGroup.PowerUpIni("GOOSE开入SOE","AppEventGoInSoeGroup", CN_NUM_GOIN,CN_NUM_RPT_GOIN);
	ptGoInTab=&g_tGoInTab[0];
	uiFlag.u32=0;
	for(i=0;i<CN_NUM_GOIN;i++)
	{
		AppEventGoInSoe[i].BlPowerUpIni(ptGoInTab->byName, ptGoInTab->byPinName, AppEventGoInSoeGroup,uiFlag.u32);
		ptGoInTab++;
	}
}
void AppEventFlagSoePowerUpIni()
{
	WORD i;
	const tagFlagTab *ptFlagTab;
	SalStatus::Flags  uiFlag;
	AppEventFlagSoeGroup.PowerUpIni("虚拟SOE",        "AppEventFlagSoeGroup", CN_NUM_FLAG, CN_NUM_RPT_FLAG);
	ptFlagTab=&g_tFlagTab[0];
	uiFlag.u32=0;
	uiFlag.st.isDispQ=1;
	for(i=0;i<CN_NUM_FLAG;i++)
	{
		AppEventFlagSoe[i].BlPowerUpIni(ptFlagTab->byName, ptFlagTab->byPinName, AppEventFlagSoeGroup,uiFlag.u32);
		ptFlagTab++;
	}
}
void AppEventDoSoePowerUpIni()
{
	WORD i;
	const tagDoTab *ptDoTab;
	SalStatus::Flags  uiFlag;
	AppEventDOSoeGroup.PowerUpIni("硬开出SOE",        "AppEventDoSoeGroup", CN_NUM_DO, CN_NUM_RPT_DO);
	ptDoTab=&g_tDoTab[0];
	uiFlag.u32=0;
	uiFlag.st.isDispQ=1;
	for(i=0;i<CN_NUM_DO;i++)
	{
		AppEventDOSoe[i].BlPowerUpIni(ptDoTab->byName, ptDoTab->byPinName, AppEventDOSoeGroup,uiFlag.u32);
		ptDoTab++;
	}
}
void AppEventGoOutSoePowerUpIni()
{
	WORD i;
	const tagGoOutTab *ptGoOutTab;
	SalStatus::Flags  uiFlag;
	uiFlag.u32=0;
	uiFlag.st.isDispQ=1;
	AppEventGoOutSoeGroup.PowerUpIni("GOOSE开出SOE",        "AppEventGoOutSoeGroup", CN_NUM_GOOUT, CN_NUM_RPT_GOOUT);
	ptGoOutTab=&g_tGoOutTab[0];
	for(i=0;i<CN_NUM_GOOUT;i++)
	{
		AppEventGoOutSoe[i].BlPowerUpIni(ptGoOutTab->byName, ptGoOutTab->byPinName, AppEventGoOutSoeGroup,uiFlag.u32);
		ptGoOutTab++;
	}
}
void AppEventLedSoePowerUpIni()
{
	WORD i;
	const tagLedTab *ptLedTab;
	SalStatus::Flags  uiFlag;
	AppEventLedSoeGroup.PowerUpIni("LED指示灯SOE",        "AppEventLedSoeGroup", CN_NUM_LED, CN_NUM_RPT_LED);
	ptLedTab=&g_tLedTab[0];
	uiFlag.u32=0;
	uiFlag.st.isDispQ=1;
	for(i=0;i<CN_NUM_LED;i++)
	{
		AppEventLedSoe[i].BlPowerUpIni(ptLedTab->byName, ptLedTab->byPinName, AppEventLedSoeGroup,uiFlag.u32);
		ptLedTab++;
	}
}

void AppEventDpiSoePowerUpIni()
{
	WORD i;
	const tagDpiTab   *ptDpiTab;
	SalStatus::Flags  uiFlag;
	// 双点事项初始化
	AppEventDpiSoeGroup.PowerUpIni("双点SOE信号", "AppDEventSoeGroup", CN_NUM_DPI, CN_NUM_RPT_DPI);
	ptDpiTab =&g_tDpiTab[0];
	uiFlag.u32=0;
	uiFlag.st.isDispQ=1;
	uiFlag.st.isDispUs=1;
	for(i=0;i<CN_NUM_DPI;i++)
	{
		AppEventDpiSoe[i].DpPowerUpIni(ptDpiTab->byName, ptDpiTab->byPinName, AppEventDpiSoeGroup,uiFlag.u32);
		ptDpiTab++;
	}
}
// 状态事项更新
// 注：先进行状态更新,再进行参数更新
void AppEventActOutRef()
{
	register UINT32 i;
	register tagActQueue  *ptActQueue;
	register tagActEvent  *ptActEvent;
	register u32value     *pu32value;
	
	SalDateStamp  cDateTemp;
	ptActQueue    =g_tActQueue;
	// 实时更新的方式,可修改为变位更新的方式
	
	register WORD wIndex,wResult;
	for(i=0;i<CN_NUM_ACT;i++)
	{
		if(ptActQueue->byBakVaild)
		{
			ptActEvent =&ptActQueue->tActEventBak;
			pu32value  =(u32value*)(&ptActEvent->tRecValue6.iMeaValue[0]);
			// 参数
			AppEventAct[i].UpdateStatus(pu32value[0], pu32value[1], pu32value[2], pu32value[3], pu32value[4], pu32value[5]);
			// 状态+时间
			cDateTemp.usL = ptActEvent->tActT.dwUSecond_L;
			cDateTemp.usH = ptActEvent->tActT.dwUSecond_H;
			cDateTemp.q.q = ptActEvent->tActT.dwLeapSecFlg;
			AppEventAct[i].Update(ptActEvent->bActIn,cDateTemp);
			ptActQueue->byBakVaild=FALSE;
			// 增加审计记录
			wIndex   =ptActEvent->tRecValue6.iMeaValue[EN_VAILD_SRC_INDEX];
			wResult  =ptActEvent->tRecValue6.iMeaValue[EN_VAILD_FAIL];
			if((wIndex<CN_NUM_GOIN)&&(wResult<g_tCEnumTab[EN_CENUM_FAIL_RET-EN_CENUM_STR].byEnNum))
			{
				if(ptActEvent->bActIn==0)
				{
					SjContrlRecord.CreatRecord("GOOSE组件", "APP", g_tGoInTab[wIndex].byName,"GOOSE控制分指令接收","出口分命令",g_tCEnumTab[EN_CENUM_FAIL_RET-EN_CENUM_STR].eEnumDes[wResult].des,0);
				}
				else if(ptActEvent->bActIn==1)
				{
					SjContrlRecord.CreatRecord("GOOSE组件", "APP", g_tGoInTab[wIndex].byName,"GOOSE控制合指令接收","出口分命令",g_tCEnumTab[EN_CENUM_FAIL_RET-EN_CENUM_STR].eEnumDes[wResult].des,0);
				}
				else if(ptActEvent->bActIn==2)
				{
					SjContrlRecord.CreatRecord("GOOSE组件", "APP", g_tGoInTab[wIndex].byName,"GOOSE控制分指令接收","出口合命令",g_tCEnumTab[EN_CENUM_FAIL_RET-EN_CENUM_STR].eEnumDes[wResult].des,0);
				}
				else if(ptActEvent->bActIn==3)
				{
					SjContrlRecord.CreatRecord("GOOSE组件", "APP", g_tGoInTab[wIndex].byName,"GOOSE控制合指令接收","出口合命令",g_tCEnumTab[EN_CENUM_FAIL_RET-EN_CENUM_STR].eEnumDes[wResult].des,0);
				}
			}
		}
		if(ptActQueue->byFlag==EN_ACTS_EVENT_STOP)
		{
			ptActEvent =&ptActQueue->tActEvent;
			pu32value = (u32value*)(&ptActEvent->tRecValue6.iMeaValue[0]);
			// 参数
			AppEventAct[i].UpdateStatus(pu32value[0], pu32value[1], pu32value[2], pu32value[3], pu32value[4], pu32value[5]);
			// 状态+时间
			cDateTemp.usL = ptActEvent->tActT.dwUSecond_L;
			cDateTemp.usH = ptActEvent->tActT.dwUSecond_H;
			cDateTemp.q.q = ptActEvent->tActT.dwLeapSecFlg;
			AppEventAct[i].Update(ptActEvent->bActIn,cDateTemp);
			ptActQueue->byFlag = EN_ACTS_EVENT_NULL;
			// 增加审计记录
			wIndex=ptActEvent->tRecValue6.iMeaValue[EN_VAILD_SRC_INDEX];
			wResult=ptActEvent->tRecValue6.iMeaValue[EN_VAILD_FAIL];
			if((wIndex<CN_NUM_GOIN)&&(wResult<g_tCEnumTab[EN_CENUM_FAIL_RET-EN_CENUM_STR].byEnNum))
			{
				if(ptActEvent->bActIn==0)
				{
					SjContrlRecord.CreatRecord("GOOSE组件", "APP", g_tGoInTab[wIndex].byName,"GOOSE控制分指令接收","出口分命令",g_tCEnumTab[EN_CENUM_FAIL_RET-EN_CENUM_STR].eEnumDes[wResult].des,0);
				}
				else if(ptActEvent->bActIn==1)
				{
					SjContrlRecord.CreatRecord("GOOSE组件", "APP", g_tGoInTab[wIndex].byName,"GOOSE控制合指令接收","出口分命令",g_tCEnumTab[EN_CENUM_FAIL_RET-EN_CENUM_STR].eEnumDes[wResult].des,0);
				}
				else if(ptActEvent->bActIn==2)
				{
					SjContrlRecord.CreatRecord("GOOSE组件", "APP", g_tGoInTab[wIndex].byName,"GOOSE控制分指令接收","出口合命令",g_tCEnumTab[EN_CENUM_FAIL_RET-EN_CENUM_STR].eEnumDes[wResult].des,0);
				}
				else if(ptActEvent->bActIn==3)
				{
					SjContrlRecord.CreatRecord("GOOSE组件", "APP", g_tGoInTab[wIndex].byName,"GOOSE控制合指令接收","出口合命令",g_tCEnumTab[EN_CENUM_FAIL_RET-EN_CENUM_STR].eEnumDes[wResult].des,0);
				}
			}
		}
		ptActQueue++;
	}
}
// 状态事项更新
void AppEventCosOutRef()
{
	register UINT32    i;
	register BOOL      *pbEvent,*pbEventXor;
	register u32value  *pu32value;
	// 实时更新的方式,可修改为变位更新的方式	
	//if(G_Sys_Div4_2)
	{
		pbEventXor =g_tAlmState.bAlmXor;
		pbEvent    =g_tAlmState.bAlmOut;
		// 实时更新的方式,可修改为变位更新的方式
		for(i=0;i<CN_NUM_ALM;i++)
		{
			if(pbEventXor[i])
			{
				pu32value = (u32value*)g_tAlmState.tRecValue[i].iMeaValue;
				AppEventWarn[i].UpdateStatus(pu32value[0], pu32value[1], pu32value[2]);
				AppEventWarn[i].Update(pbEvent[i]);
			}
		}
	}
	if(G_Sys_Div4_3)
	{
		pbEventXor =g_tChkState.bChkXor;
		pbEvent    =g_tChkState.bChkOut;
		// 实时更新的方式,可修改为变位更新的方式
		for(i=0;i<CN_NUM_CHK;i++)
		{
			if(pbEventXor[i])
			{
				pu32value = (u32value*)g_tChkState.tRecValue[i].iMeaValue;
				AppEventChek[i].UpdateStatus(pu32value[0], pu32value[1], pu32value[2]);
				AppEventChek[i].Update(pbEvent[i]);
			}
		}
	}
}
// 变位事项更新
void AppEventSoeOutRef()
{
	register UINT32 i,j,k;
	register BOOL  *pbEvent;
	register BOOL  *pbEventXor;
	register WORD  *pwSrcQ;
	register DWORD *pdwHldXor;
	register DWORD dwHldXorTem;
	register tagTimeUTC  *ptTimeUTC;
	
	SalDateStamp cDateTemp;
	StatusQ  StatusQTem;
	const tagBoardIoTab *ptBoardIoTab;
	
	ptBoardIoTab =&g_tBoardDITab[0];
	pdwHldXor   = g_tagIO.dwDIHldXor32;
	pbEvent     = g_tagIO.bDIHldIn;
	ptTimeUTC   = g_tagIO.tDIHldUTC;
	if(g_tagIO.byDIFstToSoe)
	{
		cDateTemp.usL = g_tagPub.tSysTimeUTC.dwUSecond_L;
		cDateTemp.usH = g_tagPub.tSysTimeUTC.dwUSecond_H;
		cDateTemp.q.q = g_tagPub.tSysTimeUTC.dwLeapSecFlg;
		StatusQTem.u32=0;
		for(i=0;i<CN_NUM_DI;i++)
		{
			AppEventDISoe[i].SetState((UINT32)pbEvent[i],cDateTemp,StatusQTem);
		}
		g_tagIO.byDIFstToSoe=FALSE;
	}
	else
	{
		for(i=0;i<CN_NUM_BOARD_DI;i++,ptBoardIoTab++)
		{
			dwHldXorTem=pdwHldXor[i];
			if(dwHldXorTem!=0)
			{
				for(j=0,k=ptBoardIoTab->wIndexStr;j<ptBoardIoTab->wSrcIndexNum;j++,k++)
				{
					if(dwHldXorTem&g_dwBit[j])
					{
						cDateTemp.usL = ptTimeUTC[k].dwUSecond_L;
						cDateTemp.usH = ptTimeUTC[k].dwUSecond_H;
						cDateTemp.q.q = ptTimeUTC[k].dwLeapSecFlg;
						AppEventDISoe[k].Update(pbEvent[k],cDateTemp);
					}
				}
			}
		}
	}
	// 仅刷新状态,还是变位状态合适???
	pbEvent    = g_tagIO.bGoIn;
	pbEventXor = g_tagIO.bGoInXor;
	pwSrcQ     = g_tagIO.wGoQSrc;
	for(i=0;i<CN_NUM_GOIN;i++)
	{
		if(pbEventXor[i])
		{
			StatusQTem.st.test    =(pwSrcQ[i]&CN_GOIN_Test)>>2;
			StatusQTem.st.invalid =(pwSrcQ[i]&CN_GOIN_Invalid);
			AppEventGoInSoe[i].Update(pbEvent[i],StatusQTem);
		}
	}
	// 虚遥信暂不使用
	//pbEvent=g_bFlag;
	//for(i=0;i<CN_NUM_FLAG;i++)
	//{
	//	AppEventFlagSoe[i].Update(*pbEvent++);
	//}
	// 仅刷新状态
	pbEvent    =g_tagIO.bDOOut;
	pbEventXor =g_tagIO.bDOOutXor;
	for(i=0;i<CN_NUM_DO;i++)
	{
		if(pbEventXor[i])
		{
			AppEventDOSoe[i].Update(pbEvent[i]);
		}
	}
	// 仅刷新状态
	pbEvent=g_tagIO.bGoOut;
	pbEventXor=g_tagIO.bGoOutXor;
	for(i=0;i<CN_NUM_GOOUT;i++)
	{
		if(pbEventXor[i])
		{
			AppEventGoOutSoe[i].Update(pbEvent[i]);
		}
	}
	// 指示灯状态更新
	BYTE byLedPtr=g_tagIO.byLedPtr;
	if(byLedPtr<CN_NUM_LED)
	{
		AppEventLedSoe[byLedPtr].Update(g_tagIO.bLedOut[byLedPtr]);
	}
	// 双点事项更新
	pbEvent   = g_tagIO.byDpiIn;
	pbEventXor= g_tagIO.byDpiInXor;
	ptTimeUTC = g_tagIO.tDpiUTC;

	if(g_tagIO.byDpiFstToSoe)
	{
		cDateTemp.usL = g_tagPub.tSysTimeUTC.dwUSecond_L;
		cDateTemp.usH = g_tagPub.tSysTimeUTC.dwUSecond_H;
		cDateTemp.q.q = g_tagPub.tSysTimeUTC.dwLeapSecFlg;
		StatusQ  StatusQTem;
		StatusQTem.u32=0;
		for(i=0;i<CN_NUM_DPI;i++)
		{
			AppEventDpiSoe[i].SetState((UINT32)pbEvent[i],cDateTemp,StatusQTem);
		}
		g_tagIO.byDpiFstToSoe=FALSE;
	}
	else
	{
		for(i=0;i<CN_NUM_DPI;i++,ptTimeUTC++)
		{
			if(pbEventXor[i])
			{
				cDateTemp.usL = ptTimeUTC->dwUSecond_L;
				cDateTemp.usH = ptTimeUTC->dwUSecond_H;
				cDateTemp.q.q = ptTimeUTC->dwLeapSecFlg;
				AppEventDpiSoe[i].Update(pbEvent[i],cDateTemp);
			}
		}
	}
}

void AppEventPowerUpIni()
{
	// 事项
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
	// 双点SOE
	AppEventDpiSoePowerUpIni();

	HmiViewEventPool.PowerUpIni(CN_NUM_RPT_DI);
}
// 事项刷新
void AppEventOutRef()
{
	AppEventActOutRef();
	AppEventCosOutRef();
	AppEventSoeOutRef();
}
// 运行事项接口
void AppEventRunRef(WORD wRunIndex)
{
	if(wRunIndex<CN_NUM_RUN)
	{
		AppEventRun[wRunIndex].Update(TRUE);
	}
}
// 操作事项接口
void AppEventOptRef(WORD wOptIndex)
{
	if(wOptIndex<CN_NUM_OPT)
	{
		AppEventOpt[wOptIndex].Update(TRUE);
	}
}
// 操作事项接口（带参数）
void AppEventOptValueRef(WORD wOptIndex,DWORD iMeaValue1,DWORD iMeaValue2,DWORD iMeaValue3)
{
    u32value  u32value1,u32value2,u32value3;
	if(wOptIndex<CN_NUM_OPT)
	{
	    u32value1.u32=iMeaValue1;
	    u32value2.u32=iMeaValue2;
	    u32value3.u32=iMeaValue3;

		AppEventOpt[wOptIndex].UpdateStatus(u32value1,u32value2,u32value3);
		AppEventOpt[wOptIndex].Update(TRUE);
	}
}
// 操作事项接口（带参数）
INT32 AppEventClear(WORD wIndex)
{
	static BOOL bFlag=0;
	INT32 res=0;
	if(bFlag)
	{
		return -2;
	}
	bFlag=TRUE;
	switch(wIndex)
	{
		case EN_DTYPE_ACT:
			AppEventActGroup.ClearEvent();
			AppEventOptRef(EN_OPT_ACT_DEl);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "GOOSE命令事项清除完成", 0, 0, 0, 0);
			break;
		case EN_DTYPE_ALM:
			AppEventWarnGroup.ClearEvent();
			AppEventOptRef(EN_OPT_ALM_DEl);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "清除告警事项完成", 0, 0, 0, 0);
			break;
		case EN_DTYPE_CHK:
			AppEventChekGroup.ClearEvent();
			AppEventOptRef(EN_OPT_CHK_DEl);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "清除自检事项完成", 0, 0, 0, 0);
			break;
		case EN_CFG_RUN:
			AppEventRunGroup.ClearEvent();
			AppEventOptRef(EN_OPT_RUN_DEl);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "清除运行事项完成", 0, 0, 0, 0);
			break;
		case EN_CFG_OPT:
			AppEventOptGroup.ClearEvent();
			AppEventOptRef(EN_OPT_OPT_DEl);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "清除操作事项完成", 0, 0, 0, 0);
			break;
		case EN_DTYPE_DI:
			AppEventDISoeGroup.ClearEvent();
			AppEventOptRef(EN_OPT_DI_SOE_DEl);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "清除硬开入SOE事项完成", 0, 0, 0, 0);
			break;
		case EN_DTYPE_GOIN:
			AppEventGoInSoeGroup.ClearEvent();
			AppEventOptRef(EN_OPT_GOIN_SOE_DEl);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "清除GOOSE开入SOE事项完成", 0, 0, 0, 0);
			break;
		case EN_DTYPE_FLAG:
			AppEventFlagSoeGroup.ClearEvent();
			AppEventOptRef(EN_OPT_FLAG_SOE_DEl);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "清除虚遥信事项完成", 0, 0, 0, 0);
			break;
		case EN_DTYPE_DO:
			AppEventDOSoeGroup.ClearEvent();
			AppEventOptRef(EN_OPT_DO_SOE_DEl);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "清除硬开出SOE事项完成", 0, 0, 0, 0);
			break;
		case EN_DTYPE_GOOUT:
			AppEventGoOutSoeGroup.ClearEvent();
			AppEventOptRef(EN_OPT_GOOUT_SOE_DEl);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "清除GOOSE开出SOE事项完成", 0, 0, 0, 0);
			break;
		case EN_DTYPE_LED:
			AppEventLedSoeGroup.ClearEvent();
			AppEventOptRef(EN_OPT_LED_SOE_DEl);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "清除指示灯SOE事项完成", 0, 0, 0, 0);
			break;
		case EN_DTYPE_DPI:
			AppEventDpiSoeGroup.ClearEvent();
			AppEventOptRef(EN_OPT_DPI_SOE_DEl);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "清除双点SOE事项完成", 0, 0, 0, 0);
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
			AppEventOptRef(EN_OPT_EVENT_ALL_DEl);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "清除所有事项完成", 0, 0, 0, 0);
			break;
		default:
			res=-1;
			break;
	}
	bFlag=FALSE;
	return res;
}

