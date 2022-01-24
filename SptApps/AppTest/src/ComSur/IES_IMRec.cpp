/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * 积成电子股份有限公司
 * 元件名称：事项元件
 * 元件功能：事项元件
 *     1.告警事项生成
 *     2.越限事项生成
 * 元件版本：V1.00
 * 定版时间：2020-9-7
 * 版本修改：
 * <版本号> <修改日期>, <修改人员>: <修改功能概述>
 * V1.00 2021-2-24 刘志利：初版
 *================================================================================*/

#include "IES_IMRec.h"

// 元件接口结构体
tagIES_IMRec      gtagIES_IMRec;
// ============================================================================
// 函数功能：相对时间计算(小端模式)
// 输入参数：UTC时间
// 输出参数：32位us,最大4294967295us=4294967.295ms=4294.967295s=
// 返回值：  无
// ============================================================================
UINT32 IES_IMRec_Rela_Time(tagTimeUTC tUTCA,tagTimeUTC tUTCB)
{
	UINT64  *u64A,*u64B;
	u64A=(UINT64*)(&tUTCA.dwUSecond_L);
	u64B=(UINT64*)(&tUTCB.dwUSecond_L);
	return (UINT32)(*u64A-*u64B);
}
// ============================================================================
// 函数功能：GOOSE命令事项生成
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMRec_Act(tagIES_IMRec  *pgtagIES_IMRec)
{
	register UINT32 i,j;
	const    WORD   *pwSrcIndexIn, *pwSrcIndexOut,*pwAppId;
	WORD     *pwActInIndex,*pwActOutIndex;

	BOOL    *pbActIn,*pbActOut,*pbActOutRet;
	BOOL    *pbSrcIn,*pbSrcOut,*pbSrcOutRet;
	BOOL     bActInXor,bActOutXor,bActOutRetXor;
	BOOL     bDstIn=FALSE,bDstOut=FALSE,bDstOutRet=FALSE;
	BOOL    *pbyInvaild;
	tagActQueue      *ptagActQueue;
	tagActEvent      *ptagActEvent;
	tagMsgValue6     *ptRecValue;
	
	const tagActTab  *ptActTab;
	
	ptActTab      = &g_tActTab[0];
	pbActIn       = g_tActState.bActIn;
	pbActOut      = g_tActState.bActOut;
	pbActOutRet   = g_tActState.bActOutRet;
	pwActInIndex  = g_tActState.wActInIndex;
	pwActOutIndex = g_tActState.wActOutIndex;
	
	pbSrcOut     = G_Get_GOIN_V_P;
	pbSrcIn      = G_Get_GOIN_P;
	pbyInvaild   = G_Get_GOIN_InV_P;
	pbSrcOutRet  = G_Get_DI_P;
	pwAppId      = g_tagIO.wGoInAppId;
	// 暂时封掉硬开入的判断
	for(i=0;i<CN_NUM_ACT;i++)
	{
		// 实时数据刷新
		pwSrcIndexOut=pwSrcIndexIn=&ptActTab->wSrcIndex[0];
		for(j=0;j<CN_ACT_SNUM;j++)
		{
			if(*pwSrcIndexIn==CN_NULL_PINNO)
			{
				bDstIn=FALSE;
				break;
			}
			if(pbSrcIn[*pwSrcIndexIn])
			{
				bDstIn=TRUE;
				break;
			}
			pwSrcIndexIn++;
		}
		bActInXor=bDstIn^(*pbActIn);
		
		if(bActInXor)
		{
			*pbActIn=bDstIn;
		}

		for(j=0;j<CN_ACT_SNUM;j++)
		{
			if(*pwSrcIndexOut==CN_NULL_PINNO)
			{
				bDstOut=FALSE;
				break;
			}
			if(pbSrcOut[*pwSrcIndexOut])
			{
				bDstOut=TRUE;
				break;
			}
			pwSrcIndexOut++;
		}
		bActOutXor    =bDstOut^(*pbActOut);
		
		if(bActOutXor)
		{
			*pbActOut=bDstOut;
		}

		bDstOutRet=pbSrcOutRet[ptActTab->wDoRetIndex];
		
		bActOutRetXor =*pbActOutRet^(bDstOutRet);
		if(bActOutRetXor)
		{
			*pbActOutRet=bDstOutRet;
		}
		// 返校等待
		ptagActQueue=&g_tActQueue[i];
		ptagActEvent=&ptagActQueue->tActEvent;
		ptRecValue  =&ptagActEvent->tRecValue6;
		
		if(ptagActQueue->byFlag==EN_ACTS_EVENT_WAIT)
		{
			if(ptagActEvent->bActOut==bDstOutRet)
			{
				ptagActEvent->bActOutRet=bDstOutRet;// 返校成功
				ptRecValue->iMeaValue[EN_VAILD_FAIL]  =EN_INVAILD_NO;
				ptRecValue->iMeaValue[EN_VAILD_RET_T] =IES_IMRec_Rela_Time(g_tagPub.tSysTimeUTC,ptagActQueue->tActEvent.tActT);//
				ptagActQueue->byFlag                  =EN_ACTS_EVENT_STOP;
			}
			else if((++ptagActQueue->dwTimeCnt)>=CN_T7MS)
			{
				ptagActEvent->bActOutRet=bDstOutRet;
				ptRecValue->iMeaValue[EN_VAILD_FAIL]  =EN_RET_OVER;
				ptRecValue->iMeaValue[EN_VAILD_RET_T] =IES_IMRec_Rela_Time(g_tagPub.tSysTimeUTC,ptagActQueue->tActEvent.tActT);;//
				ptagActQueue->byFlag                  =EN_ACTS_EVENT_STOP;
			}
		}
		// 新事项生成
		if((bActInXor)||(bActOutXor))
		{
			if(ptagActQueue->byFlag!=EN_ACTS_EVENT_NULL)
			{
				ptRecValue->iMeaValue[EN_VAILD_FAIL]  =EN_RET_COVER;
				ptRecValue->iMeaValue[EN_VAILD_RET_T] =IES_IMRec_Rela_Time(g_tagPub.tSysTimeUTC,ptagActQueue->tActEvent.tActT);
				ptagActQueue->tActEventBak=ptagActQueue->tActEvent;
				ptagActQueue->byBakVaild=TRUE;
			}
			// 保证两次合命令可以检测到变化,从而生成事项
			if(bDstOut)
			{
				ptagActEvent->bActIn  = bDstIn+2;
			}
			else
			{
				ptagActEvent->bActIn  = bDstIn;
			}
			ptagActEvent->bActOut = bDstOut;
			ptRecValue->iMeaValue[EN_VAILD_GOOSE] =bDstIn;
			ptRecValue->iMeaValue[EN_VAILD_DO] =bDstOut;
			ptagActEvent->tActT=g_tagPub.tSysTimeUTC;
			// 记录GOOSE命令AppID,返回命令不做记录
			if(bDstOut)
			{
				ptRecValue->iMeaValue[EN_VAILD_SRC_INDEX]=*pwSrcIndexOut;
				ptRecValue->iMeaValue[EN_VAILD_SRC_APPID]=pwAppId[*pwSrcIndexOut];
			}
			else if(bDstIn)
			{
				ptRecValue->iMeaValue[EN_VAILD_SRC_INDEX]=*pwSrcIndexIn;
				ptRecValue->iMeaValue[EN_VAILD_SRC_APPID]=pwAppId[*pwSrcIndexIn];
			}
			else if((bActInXor)&&(*pwActInIndex!=CN_NULL_PINNO))
			{
				ptRecValue->iMeaValue[EN_VAILD_SRC_INDEX]=*pwActInIndex;
				ptRecValue->iMeaValue[EN_VAILD_SRC_APPID]=pwAppId[*pwActInIndex];
			}
			else if((bActOutXor)&&(*pwActOutIndex!=CN_NULL_PINNO))
			{
				ptRecValue->iMeaValue[EN_VAILD_SRC_INDEX]=*pwActOutIndex;
				ptRecValue->iMeaValue[EN_VAILD_SRC_APPID]=pwAppId[*pwActOutIndex];
			}
			else
			{
				ptRecValue->iMeaValue[EN_VAILD_SRC_INDEX]=CN_NULL_PINNO;
				ptRecValue->iMeaValue[EN_VAILD_SRC_APPID]=0;
			}
			// 事项直接停止处理
			if(bDstIn^bDstOut)
			{
				if(*pwSrcIndexIn<CN_NUM_GOIN)
				{
					ptRecValue->iMeaValue[EN_VAILD_FAIL]=(UINT32)pbyInvaild[*pwSrcIndexIn];
				}
				else
				{
					ptRecValue->iMeaValue[EN_VAILD_FAIL]=EN_RET_DIF;
				}
				ptRecValue->iMeaValue[EN_VAILD_RET_T]=0;
				ptagActQueue->byFlag=EN_ACTS_EVENT_STOP;
			}
			else if(bDstOut==bDstOutRet)
			{
				ptRecValue->iMeaValue[EN_VAILD_FAIL]=EN_RET_ELSE;
				ptRecValue->iMeaValue[EN_VAILD_RET_T]=0;
				ptagActQueue->byFlag=EN_ACTS_EVENT_STOP;
			}
			else
			{
			
				ptRecValue->iMeaValue[EN_VAILD_FAIL]=EN_INVAILD_NO;
				ptagActQueue->byFlag   =EN_ACTS_EVENT_WAIT;
				ptagActQueue->dwTimeCnt=0;
			}
		}
		// 记录枚举
		*pwActInIndex++  =*pwSrcIndexIn;
		*pwActOutIndex++ =*pwSrcIndexOut;
		ptActTab++;
		pbActIn++;
		pbActOut++;
		pbActOutRet++;
	}
}

// ============================================================================
// 函数功能：告警事项生成
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMRec_Alm(tagIES_IMRec  *pgtagIES_IMRec)
{
	register UINT32  i;
	register BOOL *pbAlmIn,*pbAlmEna, *pbAlmOut,*pbAlmXor,*pbAlmTimerEna;
	register BOOL  bAlmOut;
	register BOOL  bAlmDo=FALSE;
	register tagTimeRelay *ptTimer;
	const    tagAlmTab    *ptAlmTab;
	
	ptAlmTab = &g_tAlmTab[0];
	pbAlmIn  = G_Get_AlmIn_P;
	pbAlmOut = G_Get_AlmOut_P;
	pbAlmXor = G_Get_AlmXor_P;
	
	pbAlmEna = pgtagIES_IMRec->bAlmEna;
	ptTimer  = pgtagIES_IMRec->tTimer_Alm;
	pbAlmTimerEna= pgtagIES_IMRec->bAlmTimerEna;
	
	for(i=0;i<CN_NUM_ALM;i++)
	{
		if(!pbAlmEna[i])
		{
			IES_TimeRelayStop(ptTimer);
			bAlmOut=FALSE;
		}
		else if(pbAlmTimerEna[i])
		{
			bAlmOut=pbAlmIn[i];
		}
		else
		{
			bAlmOut=IES_TimeRelayRun(ptTimer, pbAlmIn[i]);
		}
		pbAlmXor[i]=pbAlmOut[i]^bAlmOut;
		// 有变位
		if(pbAlmXor[i])
		{
			pbAlmOut[i]=bAlmOut;
		}
		// 出口标志合成
		if(bAlmOut)
		{
			if(ptAlmTab->wCfg&DB0)
			{
				bAlmDo=TRUE;
			}
		}
		ptTimer++;
		ptAlmTab++;
	}
	// 告警出口输出
	G_Set_Flag(EN_FLAG_ALM, bAlmDo);
}
// ============================================================================
// 函数功能：自检事项生成
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMRec_Chk(tagIES_IMRec  *pgtagIES_IMRec)
{
	register UINT32  i;
	register UINT32  *pdwActCnt,*pdwRetCnt;
	register BOOL    *pbChkOut,*pbChkIn,*pbChkXor;
	register BOOL     bChkIn,bChkOut,bChkDo=FALSE,bChkBs=FALSE;
	const tagChkTab  *ptChkTab;
	
	ptChkTab = &g_tChkTab[0];
	pbChkIn  = G_Get_ChkIn_P;
	pbChkOut = G_Get_ChkOut_P;
	pbChkXor = G_Get_ChkXor_P;
	pdwActCnt= g_tChkState.dwChkActCnt;
	pdwRetCnt= g_tChkState.dwChkRetCnt;

	for(i=0;i<CN_NUM_CHK;i++)
	{
		bChkIn =pbChkIn[i];
		if(bChkIn!=pbChkOut[i])
		{
			if((bChkIn)&&(pdwActCnt[i]>=ptChkTab[i].dwActCnt))
			{
				bChkOut=TRUE;
				pbChkXor[i]=pbChkOut[i]^bChkOut;
				pbChkOut[i]=TRUE;
			}
			else if((!bChkIn)&&(pdwRetCnt[i]>=ptChkTab[i].dwRetCnt))
			{
				bChkOut=FALSE;
				pbChkXor[i]=pbChkOut[i]^bChkOut;
				pbChkOut[i]=FALSE;
			}
		}
		if(pbChkOut[i])
		{
			if(ptChkTab[i].wCfg&DB0)
			{
				bChkDo=TRUE;
			}
			if(ptChkTab[i].wCfg&DB1)
			{
				bChkBs=TRUE;
			}
		}
	}
	G_Set_Flag(EN_FLAG_CHK, bChkDo);
	
	g_tagPub.bSysBs=bChkBs;
}
// ============================================================================
// 函数功能：参数初始化
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMRec_Para_Init()
{
	tagIES_IMRec     *pgtagIES_IMRec;
	register UINT32  i;
	const tagAlmTab *ptAlmTab;
	tagTimeRelay    *ptTimer;
	BOOL            *pbEna,*pbTimerEna;
	DWORD            dwActTime,dwRetTime;
	DWORD           *pdwPara;
	
	pgtagIES_IMRec = &gtagIES_IMRec;
	ptAlmTab=&g_tAlmTab[0];
	pdwPara =g_tagPara.dwPara;
	ptTimer =pgtagIES_IMRec->tTimer_Alm;
	pbEna   =pgtagIES_IMRec->bAlmEna;
	pbTimerEna=pgtagIES_IMRec->bAlmTimerEna;
	pgtagIES_IMRec->dwInit=TRUE;
	for(i=0;i<CN_NUM_ALM;i++)
	{
		if(ptAlmTab->wParaEna<CN_NUM_PARA)
		{
			*pbEna=pdwPara[ptAlmTab->wParaEna];
		}
		else
		{
			*pbEna=TRUE;
		}
		if(ptAlmTab->wParaTime<CN_NUM_PARA)
		{
			dwActTime=T(pdwPara[ptAlmTab->wParaTime]);
		}
		else if((ptAlmTab->dwDefTime==0)&&(ptAlmTab->dwRetTime==0))
		{
			pbTimerEna[i]=TRUE;
			dwActTime=0;
		}
		else
		{
			dwActTime=ptAlmTab->dwDefTime;
		}
		dwRetTime=ptAlmTab->dwRetTime;
		IES_TimeRelaySet(ptTimer, dwActTime, dwRetTime);
		ptAlmTab++;
		ptTimer++;
		pbEna++;
	}
#if 0
	ptChkTab=&g_tChkTab[0];
	pdwPara =g_tagPara.dwPara;
	ptTimer =pgtagIES_IMRec->tTimer_Chk;
	pbEna   =pgtagIES_IMRec->bChkEna;
	pgtagIES_IMRec->dwInit=TRUE;
	for(i=0;i<CN_NUM_CHK;i++)
	{
		if(ptChkTab->wParaEna<CN_NUM_PARA)
		{
			*pbEna=pdwPara[ptChkTab->wParaEna];
		}
		else
		{
			*pbEna=TRUE;
		}
		if(ptChkTab->wParaTime<CN_NUM_PARA)
		{
			dwActTime=pdwPara[ptChkTab->wParaTime];
		}
		else
		{
			dwActTime=ptChkTab->wDefTime;
		}
		dwRetTime=ptChkTab->wRetTime;
		IES_TimeRelaySet(ptTimer, dwActTime, dwRetTime);
		ptChkTab++;
		ptTimer++;
		pbEna++;
	}
#endif
	pgtagIES_IMRec->dwInit=FALSE;
}
// ============================================================================
// 函数功能：开出元件上电初始化
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMRec_Init()
{
	IES_memset(&gtagIES_IMRec,0x0,sizeof(gtagIES_IMRec));
	IES_RamScanAdd(&gtagIES_IMRec.byRamScan1);
	IES_RamScanAdd(&gtagIES_IMRec.byRamScan2);
	IES_RamScanAdd(&gtagIES_IMRec.byRamScan3);
	IES_RamScanAdd(&gtagIES_IMRec.byRamScan4);
	IES_RamScanAdd(&gtagIES_IMRec.byRamScan5);
}

// ============================================================================
// 函数功能：开出元件主函数
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMRec()
{
	tagIES_IMRec     *pgtagIES_IMRec;
	pgtagIES_IMRec =  &gtagIES_IMRec;
	
	if(pgtagIES_IMRec->dwInit)
	{
		return;
	}
	// GOOSE命令事项生成
	IES_IMRec_Act(pgtagIES_IMRec);
	// 告警事项生成
	IES_IMRec_Alm(pgtagIES_IMRec);
	// 自检事项生成
	if(G_Sys_Div4_3)
	{
		IES_IMRec_Chk(pgtagIES_IMRec);
	}
	// 上电初始化清位
	pgtagIES_IMRec->dwPWInit=TRUE;
}

