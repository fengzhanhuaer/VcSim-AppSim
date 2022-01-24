#include "InstResource.h"
void ApiFlagsInit()
{
// 电源掉电控制功能平台部分投退
    spt::HmiStatusBar::Instance().SetSaveBlockPara(10, 10);
    spt::SptEventPublishTask::Instance().SetSaveBlockPara(10, 10);
    spt::SalParaGroupSaveTask::Instance().SetSaveBlockPara(10, 10);
    spt::SptLogTask::Instance().SetSaveBlockPara(10, 10);
    spt::SalSjRecordDispachTask::Instance().SetSaveBlockPara(10, 10);
}
void ApiFlagsIn()
{
// 平台告警标志
	// 虚拟LCD标志
	g_iInter[EN_INTER_LCD_VIR]              =(SptApiStatus[E_SAS_VirLcdCmmErr].Value().bl)?TRUE:FALSE;
	// LED自检
	g_tChkState.bChkIn[EN_CHK_BOARD_LED]    =(SptApiStatus[E_SAS_LcdCmmErr].Value().bl)?TRUE:FALSE;
	// SV同步
	g_tAlmState.bAlmIn[EN_ALM_SYN]          =(SptApiStatus[E_SAS_HostSvSynState].Value().bl)?FALSE:TRUE;
	// 时间帧跳变异常
	g_tAlmState.bAlmIn[EN_ALM_TIME_SINGLE]  =(SptApiStatus[E_SAS_HostTPortAlarm].Value().bl)?TRUE:FALSE;
	g_tAlmState.bAlmIn[EN_ALM_TIME_SERVICE] =(SptApiStatus[E_SAS_HostTSrvAlarm].Value().bl)?TRUE:FALSE;
	g_tAlmState.bAlmIn[EN_ALM_TIME_CHKERR]  =(SptApiStatus[E_SAS_HostContAlarm].Value().bl)?TRUE:FALSE;

// 系统标志
	const tsAppFlags& pAppFlags=ApiIoGlobalFlag::Instance().AppFlags();
	// 调试标志
	g_bFlag[EN_FLAG_DBG]=(pAppFlags.unitDebugState)?TRUE:FALSE;
	// 界面复归
	g_bFlag[EN_FLAG_RESET_DBG]=(pAppFlags.blFaceRevert)?TRUE:FALSE;
	// 增加电源监视控制字
	if(G_Get_PARA_I(EN_PARA_ENA_POW)==1)
	{
		// 装置掉电瞬时信号
		SptGetHwVal(E_HPT_PowerUp, &g_iInter[EN_INTER_POW_LOS], 1);
		// 此处获取并防抖
		const SptFlags& pSptFlag=ApiIoGlobalFlag::Instance().SptFlag();
		g_iInter[EN_INTER_POW_LOS_RLY]=pSptFlag.IsPowerDownAtRange(200,20000);
	
		if(g_iInter[EN_INTER_POW_LOS_RLY])
		{
			G_Set_ChkIn(EN_CHK_BOARD_POW);
			if(!g_iInter[EN_INTER_POW_LOS_EVT])
			{
				//AppEventRunRef(EN_RUN_POW_OFF);
				g_iInter[EN_INTER_POW_LOS_EVT]=TRUE;
			}
		}
		else
		{
			G_Clr_ChkIn(EN_CHK_BOARD_POW);
			g_iInter[EN_INTER_POW_LOS_EVT]=FALSE;
		}
	}
#if(CN_DEV_CPU2)
	g_iInter[EN_INTER_CPU2_CTRL]=ApiIoGlobalFlag::Instance().GetFpagSlowFlags(1);
#endif
// 板卡状态标志
	WORD wboard=ApiIoGlobalFlag::Instance().BoardOnLineState();
	if(wboard&DB0)
	{
		G_Set_ChkIn(EN_CHK_BOARD_PTCT1);
	}
	else
	{
		G_Clr_ChkIn(EN_CHK_BOARD_PTCT1);
	}
		
	if(wboard&DB1)
	{
		G_Set_ChkIn(EN_CHK_BOARD_PTCT2);
	}
	else
	{
		G_Clr_ChkIn(EN_CHK_BOARD_PTCT2);
	}
#if(CN_DEV_CPU1)
	// 背板每隔4S进行一次更新
	// 暂时封掉,后续根据FPGA改动开放
	#if 0	
	if(G_Sys_Div16284_000)
	{
		if(wboard&DB2)
		{
			G_Set_ChkIn(EN_CHK_BOARD_CPU_AUX);
		}
		else
		{
			G_Clr_ChkIn(EN_CHK_BOARD_CPU_AUX);
		}
	}
	#endif
#endif
}
void ApiFlagsOut()
{
	//	检修标志
	ApiIoGlobalFlag::Instance().SetUnitTestState(g_tagPub.bSysTest);
	// 复归标志
	ApiIoGlobalFlag::Instance().SetUnitRevert(g_tagPub.bSysReset);
	// 启动SV、GOOSE发布
	if(g_tagPub.bSysPower)
	{
		// SV使能与闭锁
		if(g_iInter[EN_INTER_RUN_SV_BS]||g_iInter[EN_INTER_POW_LOS_RLY]||g_tagPub.bSysBs)
		{
			if(g_iInter[EN_INTER_RUN_SV_ENA_ELSE])
			{
				ApiIoGlobalFlag::Instance().EnableSVSend(0);
				if(g_iInter[EN_INTER_RUN_SV_ENA])
				{
					AppEventRunRef(EN_RUN_SVPUB_BS);
					g_iInter[EN_INTER_RUN_SV_ENA]=FALSE;
				}
			}
		}
		else if(!g_iInter[EN_INTER_RUN_SV_ENA_ELSE])
		{
			ApiIoGlobalFlag::Instance().EnableSVSend(1);
			AppEventRunRef(EN_RUN_SVPUB_ENA);
			g_iInter[EN_INTER_RUN_SV_ENA]=TRUE;
			g_iInter[EN_INTER_RUN_SV_ENA_ELSE]=TRUE;
		}
		// GOOSE使能与闭锁
		if(g_iInter[EN_INTER_RUN_GO_BS]||g_iInter[EN_INTER_POW_LOS_RLY]||g_tagPub.bSysBs)
		{
			if(g_iInter[EN_INTER_RUN_GO_ENA_ELSE])
			{
				ApiIoGlobalFlag::Instance().EnableGoSend(0);
				if(g_iInter[EN_INTER_RUN_GO_ENA])
				{
					AppEventRunRef(EN_RUN_GOPUB_BS);
					g_iInter[EN_INTER_RUN_GO_ENA]=FALSE;
				}
			}
		}
		else if(!g_iInter[EN_INTER_RUN_GO_ENA_ELSE])
		{
			ApiIoGlobalFlag::Instance().EnableGoSend(1);
			AppEventRunRef(EN_RUN_GOPUB_ENA);
			g_iInter[EN_INTER_RUN_GO_ENA]=TRUE;
			g_iInter[EN_INTER_RUN_GO_ENA_ELSE]=TRUE;
		}
	}
#if(CN_DEV_CPU1)
	if(!g_iInter[EN_INTER_CPU2_CTRL_DBG])
	{
		
		if(g_tagIO.bDOOutXor[EN_DO_ALM])
		{
			SptSetHwVal(E_HPT_RunErr, &g_tagIO.bDOOut[EN_DO_ALM], 1);
		}
		if(g_tagIO.bDOOutXor[EN_DO_CHK])
		{
			BYTE   bDOOutNor=!g_tagIO.bDOOut[EN_DO_CHK];
			SptSetHwVal(E_HPT_UnitErr,  &bDOOutNor, 1);
		}
	}
#endif

#if(CN_DEV_CPU2)
	if(g_iInter[EN_INTER_CPU2_CTRL])
	{
		if(!g_iInter[EN_INTER_CPU2_CTRL_DBG])
		{
			if(g_tagIO.bDOOutXor[EN_DO_ALM])
			{
				SptSetHwVal(E_HPT_RunErr, &g_tagIO.bDOOut[EN_DO_ALM], 1);
			}
			
			if(g_tagIO.bDOOutXor[EN_DO_CHK])
			{
				BYTE   bDOOutNor=!g_tagIO.bDOOut[EN_DO_CHK];
				SptSetHwVal(E_HPT_UnitErr,  &bDOOutNor, 1);
			}
		}
	}
	else
	{
		if(!g_iInter[EN_INTER_CPU2_CTRL_ZK])
		{
			UINT8 byPowDo=0xA5;
			SptSetHwVal(E_HPT_UnitErr, &byPowDo, 1);
			SptSetHwVal(E_HPT_RunErr,  &byPowDo, 1);
			g_iInter[EN_INTER_CPU2_CTRL_ZK]=TRUE;
		}

	}
	
#endif
	
}

