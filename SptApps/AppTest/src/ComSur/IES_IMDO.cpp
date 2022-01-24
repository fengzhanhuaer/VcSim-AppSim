/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * 积成电子股份有限公司
 * 元件名称：开出元件
 * 元件功能：开出元件
 *     1.硬出口控制
 *     2.GOOSE开出控制
 *     3.指示灯控制
 * 元件版本：V1.00
 * 定版时间：2020-9-7
 * 版本修改：
 * <版本号> <修改日期>, <修改人员>: <修改功能概述>
 * V1.00 2021-2-24 刘志利：初版
 *================================================================================*/

#include "IES_IMDO.h"

// 元件接口结构体
tagIES_IMDO      gtagIES_IMDO;
// ============================================================================
// 函数功能：硬出口控制
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMDO_Out(tagIES_IMDO  *pgtagIES_IMDO)
{
	register UINT32 i,j;
	register WORD  wSrcType;
	register WORD  wSrcIndex,wRtn1Index,wRtn0Index,wDoStrIndex,wDoNum;
	tagTimerRtn   *ptTimerRtn;
	DWORD    *pdwRtn1,*pdwRtn0;
	BOOL     *pbDoDst,*pbDoXor;
	BOOL     bDoDst,bDoRtn=FALSE;
	BOOL     *pBoard;
	const tagBoardIoTab   *ptBoardDOTab;
	const tagDoTab *ptDoTab;
	ptBoardDOTab=&g_tBoardDOTab[0];
	pdwRtn1     =pgtagIES_IMDO->dwRtn1;
	pdwRtn0     =pgtagIES_IMDO->dwRtn0;
	// 出口闭锁(上电过程||装置总闭锁)
	if((!g_tagPub.bSysPower)||(g_tagPub.bSysBs))
	{
		pbDoDst =g_tagIO.bDOOut;
		pbDoXor =g_tagIO.bDOOutXor;
		ptTimerRtn=pgtagIES_IMDO->tTimerRtn;
		for(i=0;i<CN_NUM_DO_RTN;i++)
		{
			bDoDst=FALSE;
			pbDoXor[i]=pbDoDst[i]^bDoDst;
			pbDoDst[i]=bDoDst;
			ptTimerRtn[i].dwTimeRtn=0;
		}
		// 装置故障与运行异常
		bDoDst=CN_Get_Dat_Src(EN_DTYPE_FLAG,EN_FLAG_DO_ALM);
		pbDoXor[EN_DO_ALM]=pbDoDst[EN_DO_ALM]^bDoDst;
		pbDoDst[EN_DO_ALM]=bDoDst;
		bDoDst=CN_Get_Dat_Src(EN_DTYPE_FLAG,EN_FLAG_DO_CHK)
		pbDoXor[EN_DO_CHK]=pbDoDst[EN_DO_CHK]^bDoDst;
		pbDoDst[EN_DO_CHK]=bDoDst;
		if(g_tagPub.bSysBs)
		{
			G_Set_AlmIn(EN_ALM_BS_DO,TRUE);
		}
		return;
	}
	
	G_Set_AlmIn(EN_ALM_BS_DO,FALSE);
	
	// 出口状态
	for(i=0;i<CN_NUM_BOARD_DO;i++,ptBoardDOTab++)
	{
		wDoStrIndex=ptBoardDOTab->wIndexStr;
		wDoNum    =ptBoardDOTab->wSrcIndexNum;
		ptDoTab   =&g_tDoTab[wDoStrIndex];
		pbDoDst   =&g_tagIO.bDOOut[wDoStrIndex];
		pbDoXor   =&g_tagIO.bDOOutXor[wDoStrIndex];
		ptTimerRtn=&pgtagIES_IMDO->tTimerRtn[wDoStrIndex];
		for(j=0;j<wDoNum;j++)
		{
			wSrcType  = ptDoTab->wSrcType;
			wSrcIndex = ptDoTab->wSrcIndex;
			bDoDst=CN_Get_Dat_Src(wSrcType,wSrcIndex);
			// 有返校判断
			if(ptDoTab->wRtnIndex<CN_NUM_DI)
			{
				bDoRtn=TRUE;
			}
			else
			{
				bDoRtn=FALSE;
			}
			//	有变位
			*pbDoXor=*pbDoDst^bDoDst;
			if(*pbDoXor)
			{
				*pbDoDst=bDoDst;
				// 启动返校
				if(bDoRtn)
				{
					ptTimerRtn->bStrEna=TRUE;
					ptTimerRtn->dwTimeRtn=0;
				}
			}
			// 有返校判断，目前暂没有考虑自检自动返回的问题
			// 目前暂时没有考虑上电自检的逻辑
			if(bDoRtn)
			{
				if(ptTimerRtn->bStrEna)
				{
					if((ptTimerRtn->dwTimeRtn++)<pgtagIES_IMDO->dwDoRtnT)
					{
						if(*pbDoDst==G_Get_DI_P[ptDoTab->wRtnIndex])
						{
							ptTimerRtn->bStrEna=FALSE;
							ptTimerRtn->dwTimeRtn=0;
							if(*pbDoDst)
							{
								*pdwRtn1&=(~g_dwBit[j]);
							}
							else
							{
								*pdwRtn0&=(~g_dwBit[j]);
							}
						}
					}
					else
					{
						ptTimerRtn->bStrEna=FALSE;
						ptTimerRtn->dwTimeRtn=0;
						
						if(*pbDoDst)
						{
							*pdwRtn1|=g_dwBit[j];
						}
						else
						{
							*pdwRtn0|=g_dwBit[j];
						}
					}
				}
			}
			ptDoTab++;
			pbDoDst++;
			pbDoXor++;
			ptTimerRtn++;
		}
		pdwRtn1++;
		pdwRtn0++;
	}
	// 出口自检
	pdwRtn1     =pgtagIES_IMDO->dwRtn1;
	pdwRtn0     =pgtagIES_IMDO->dwRtn0;
	pBoard      =&g_tChkState.bChkIn[EN_CHK_BOARD_DO1];
	wRtn1Index  =EN_CHK_DO_RTN1_STR;
	wRtn0Index  =EN_CHK_DO_RTN0_STR;
	for(i=0;i<CN_NUM_BOARD_DO_RTN;i++)
	{
		if(pBoard[i])
		{
			G_Clr_ChkIn(wRtn0Index+i);
			G_Clr_ChkIn(wRtn1Index+i);
			*pdwRtn1=0;
			*pdwRtn0=0;
		}
		else
		{
			if(*pdwRtn1)
			{
				G_Set_ChkIn_All(wRtn1Index+i,*pdwRtn1,0,0);
			}
			else
			{
				G_Clr_ChkIn(wRtn1Index+i);
			}
			if(*pdwRtn0)
			{
				G_Set_ChkIn_All(wRtn0Index+i,*pdwRtn0,0,0);
			}
			else
			{
				G_Clr_ChkIn(wRtn0Index+i);
			}
		}
		pdwRtn1++;
		pdwRtn0++;
	}
	
}
// ============================================================================
// 函数功能：GOOSE出口置位
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMDO_GoOut()
{
	register UINT32 i;
	register WORD  wSrcType;
	register WORD  wSrcIndex;
	register tagTimeUTC  *ptTimeUTC;//,*ptTimeUTCSrc;
	register BOOL    *pbGoOutDst,*pbGoOutXor,*pbGoOutCom;
	register BOOL     bGoOutDst;
	register UINT32   *pdwGoOutQ;
	const tagGoOutTab *ptGoOutTab;
	ptGoOutTab  =&g_tGoOutTab[0];
	pbGoOutDst  =&g_tagIO.bGoOut[0];
	pbGoOutCom  =&g_tagIO.bGoOutCom[0];
	pbGoOutXor  =&g_tagIO.bGoOutXor[0];
	ptTimeUTC   =&g_tagIO.tGoOutT[0];
	
	for(i=0;i<CN_NUM_GOOUT;i++)
	{
		wSrcType    = ptGoOutTab->wSrcType;
		wSrcIndex   = ptGoOutTab->wSrcIndex;
		bGoOutDst=CN_Get_Dat_Src(wSrcType,wSrcIndex);
		bGoOutDst|=pbGoOutCom[i];
		*pbGoOutXor=((*pbGoOutDst)^bGoOutDst);
		*pbGoOutDst=bGoOutDst;
		// 时标更新
		if(*pbGoOutXor)
		{
			// 源时标(硬开入)
			if(wSrcType==EN_DTYPE_DI)
			{
				ptTimeUTC[i]=G_Get_DI_UTC_P[wSrcIndex];
			}
			// 接收时标
			//else if(i==EN_GOOUT_TIME_RECV)
			//{
			//	ptTimeUTC[i]=g_tagIO.tGoInUTCRev;
			//}
			// 本地时标
			else
			{
				ptTimeUTC[i]=G_Get_PUB_UTC[0];
			}
		}
		ptGoOutTab++;
		pbGoOutXor++;
		pbGoOutDst++;
	}
	// 暂时仅处理检修品质
	if(G_Get_Inter(EN_INTER_GOPUB_OUT_Q))
	{
		pdwGoOutQ   =&g_tagIO.dwGoOutQ[0];
		if(g_tagPub.bSysTestXor)
		{
			if(g_tagPub.bSysTest)
			{
				for(i=0;i<CN_NUM_GOOUT;i++)
				{
					pdwGoOutQ[i]|=CN_Go_Q_TEST;
				}
			}
			else
			{
				for(i=0;i<CN_NUM_GOOUT;i++)
				{
					pdwGoOutQ[i]&=(~CN_Go_Q_TEST);
				}
			}
		}
	}
}
// ============================================================================
// 函数功能：LED灯置位【暂不使用】
// 输入参数：
// 输出参数：
// 返回值：  无
// 暂时不使用32位型输出
// ============================================================================
void IES_IMDO_Led()
{
	register UINT32 i;
	register WORD  wSrcType;
	register WORD  wSrcIndex;
	BOOL    *pbLedDst;
	BOOL     bLedDst;
	const tagLedTab *ptLedTab;
	ptLedTab  =&g_tLedTab[0];
	pbLedDst  =&g_tagIO.bLedOut[0];
	for(i=0;i<CN_NUM_LED;i++)
	{
		wSrcType  = ptLedTab->wSrcType;
		wSrcIndex = ptLedTab->wSrcIndex;
		bLedDst=CN_Get_Dat_Src(wSrcType,wSrcIndex);
		*pbLedDst++=bLedDst;
		ptLedTab++;
	}
}
// ============================================================================
// 函数功能：LED灯置位
// 输入参数：
// 输出参数：
// 返回值：  无
// 减轻负载,每个中断只处理一个灯
// ============================================================================
void IES_IMDO_Led_S()
{
	register BYTE  byLedPtr;
	byLedPtr=g_tagIO.byLedPtr;
	// 累加放在前面,禁止后放！！
	if((++byLedPtr)>=CN_NUM_LED)
	{
		byLedPtr=0;
	}
	g_tagIO.bLedOut[byLedPtr]=CN_Get_Dat_Src(g_tLedTab[byLedPtr].wSrcType,g_tLedTab[byLedPtr].wSrcIndex);
	g_tagIO.bLedOut[byLedPtr]|=g_tagIO.bLedOutCom[byLedPtr];

	//  指示灯保持逻辑
	if(g_tLedTab[byLedPtr].bHld)
	{
		// 保持标志赋值
		if(g_tagIO.bLedOut[byLedPtr])
		{
			g_tagIO.bLedOutHld[byLedPtr]=g_tagIO.bLedOut[byLedPtr];
		}
		// 保持标志复归
		else if(g_tagPub.bSysReset)
		{
			g_tagIO.bLedOutHld[byLedPtr]=FALSE;
		}
		g_tagIO.bLedOut[byLedPtr]|=g_tagIO.bLedOutHld[byLedPtr];
	}
	g_tagIO.byLedPtr=byLedPtr;
}
// ============================================================================
// 函数功能：开出元件参数初始化
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMDO_Para_Init()
{
	tagIES_IMDO     *pgtagIES_IMDO;
	pgtagIES_IMDO = &gtagIES_IMDO;
	pgtagIES_IMDO->dwDoRtnT=T(G_Get_PARA_I(EN_PARA_T_DO_RTN));
}
// ============================================================================
// 函数功能：开出元件上电初始化
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMDO_Init()
{
	IES_memset(&gtagIES_IMDO,0x0,sizeof(gtagIES_IMDO));
	IES_RamScanAdd(&gtagIES_IMDO.byRamScan1);
	IES_RamScanAdd(&gtagIES_IMDO.byRamScan2);
	IES_RamScanAdd(&gtagIES_IMDO.byRamScan3);
	IES_RamScanAdd(&gtagIES_IMDO.byRamScan4);
}
// ============================================================================
// 函数功能：开出元件主函数
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMDO()
{
	tagIES_IMDO     *pgtagIES_IMDO;
	pgtagIES_IMDO = &gtagIES_IMDO;
	
	if(pgtagIES_IMDO->dwInit)
	{
		pgtagIES_IMDO->dwInit=FALSE;
		return;
	}
	// 硬出口数据处理
	IES_IMDO_Out(pgtagIES_IMDO);
	// GOOSE开出处理
	IES_IMDO_GoOut();
	// LED开出处理
	IES_IMDO_Led_S();
	// 上电初始化清位
	pgtagIES_IMDO->dwPWInit=TRUE;
}

