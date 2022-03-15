#include "InstResource.h"
#define  CN_CHEK_TASKDLY  (1500)
#define  CN_CHEK_IO_CNT   (CN_MS_T_120S/CN_CHEK_TASKDLY)
#define  CN_CHEK_DBG_CNT  (CN_MS_T_300S/CN_CHEK_TASKDLY)
int32 AppCheckFunction1(SptCheckTask::CheckAppInst* Inst)
{

	static  uint8   byPowInit=FALSE;
	static  uint32   dwIoResetCnt=0;
	static  uint32   dwParaSyn=0;
	static  uint32   dwMenuDbg=0;
	uint16  i,wFlag=FALSE;
	// 传输初始化信息 仅传输一次
	if(!g_tagPub.bSysPower)
	{
		if(!byPowInit)
		{
			IES_IMCom_Init_Tx();
			byPowInit=TRUE;
		}
		IES_IMCom_Init_Rx(&dwParaSyn);
	#if(CN_DEV_CPU1)
		// 参数上电同步
		if(dwParaSyn!=0)
		{
			for(i=0;i<CN_NUM_BOARD_PARA_COM;i++)
			{
				if((dwParaSyn&g_dwBit[i])&&(!g_tChkState.bChkIn[EN_CHK_PARA_STR+i]))
				{
					if (AppSendPara2SubBoard(&ProtParaGroup[i], 0) == 0)
					{
						AppEventRunRef(EN_RUN_PARASYN_S_STR+i);
					}
					else
					{
						AppEventRunRef(EN_RUN_PARASYN_F_STR+i);
					}
					dwParaSyn&=(~g_dwBit[i]);
					break;
				}
			}
		}
	#endif
	}
	
	SptGetHwVal(E_HPT_Temperature, &g_tagDC.iDCIn[CN_DC_INDEX_T], 4);
	
	IES_IMCom_Slow_Tx();
	if(g_tComSlowTx.wFlag)
	{
		if(!g_tComSlowTx.wSendFlag)
		{
			StartSend2SubBoardMsg(E_ASMT_SLOW_1);
			g_tComSlowTx.wFlag=FALSE;
			g_tComSlowTx.wSendFlag=TRUE;
		}
	}
	IES_IMCom_Slow_Rx();
	// IO板卡自检,下发配置帧
	for(i=0;i<CN_NUM_BOARD_DI;i++)
	{
		if(g_tChkState.bChkOut[EN_CHK_BOARD_DI_STR+i])
		{
			wFlag=TRUE;
		}
	}
	if(wFlag)
	{
	    dwIoResetCnt++;
	}
	else
	{
	    dwIoResetCnt=0;
	}
	if(dwIoResetCnt>=CN_CHEK_IO_CNT)
	{
		ApiIoGlobalFlag::Instance().ResetSubBoardState();
		dwIoResetCnt=0;
	}
	// 控制类审计记录更新
	AppEventSjOutRef_Task();
	// 界面调试状态计时
	if(!MenuDispDbgIn)
	{
		if(MenuDispDbgDisp)
		{
			if(++dwMenuDbg>=CN_CHEK_DBG_CNT)
			{
				MenuDispDbgDisp=FALSE;
				dwMenuDbg=0;
			}
		}
	}
	else
	{
		dwMenuDbg=0;
	}
	return 0;
}

SptCheckTask::CheckAppInst appCheckInst[] =
{
	{1,CN_CHEK_TASKDLY,0,AppCheckFunction1}
};

void AppCheckPowerUpIni()
{
	for (uint32 i = 0; i < M_ArrLen(appCheckInst); i++)
	{
		SptCheckTask::Instance().AddAppCheckInst(&appCheckInst[i]);
	}
}
