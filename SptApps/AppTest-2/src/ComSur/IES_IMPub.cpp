/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * 积成电子股份有限公司
 * 元件名称：公用部分元件
 * 元件功能：公用部分元件
 * 元件版本：V1.00
 * 定版时间：2020-9-7
 * 版本修改：
 * <版本号> <修改日期>, <修改人员>: <修改功能概述>
 * V1.00 2021-2-24,刘志利:初版
 *================================================================================*/

#include "IES_IMSrc.h"
// ============================================================================
// 函数功能：数据初始化
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
BOOL IES_memset(void *pDst,BYTE byDate,DWORD dwLen)
{
	register BYTE *pDstTem;
	register DWORD i;
	if(pDst!= NULL)
	{
		pDstTem=(BYTE*)pDst;
		for(i=0;i<dwLen;i++)
		{
			pDstTem[i]=byDate;
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
// ============================================================================
// 函数功能：数据拷贝
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
BOOL IES_memcpy(void *pDst,DWORD dwDstLen,void *pSrc,DWORD dwSrcLen)
{
	register BYTE *pDstTem,*pSrcTem;
	register DWORD i;
	if((pDst != NULL)&&(pSrc != NULL)&&(dwSrcLen <= dwDstLen))
	{
		pDstTem=(BYTE*)pDst;
		pSrcTem=(BYTE*)pSrc;
		for(i=0;i<dwSrcLen;i++)
		{
			pDstTem[i]=pSrcTem[i];
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

// ============================================================================
// 函数功能：时间继电器定值赋值
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_TimeRelaySet(tagTimeRelay *ptTR, UINT32 dwTimeActSet, UINT32 dwTimeRetSet)
{
	ptTR->dwTimeActSet = dwTimeActSet;
	ptTR->dwTimeRetSet = dwTimeRetSet;
}
// ============================================================================
// 函数功能：时间继电器
//           延时T1动作,延时T2返回
// 输入参数：
// 输出参数：
// 返回值：  经延时后的状态
// ============================================================================
BOOL IES_TimeRelayRun(tagTimeRelay *ptTR, BOOL bStatus)
{
	if (bStatus!=ptTR->bStatusOut)
	{
		if(bStatus)
		{
			ptTR->bStatusOut=(ptTR->dwActSCnt++)>=ptTR->dwTimeActSet?TRUE:FALSE;
		}
		else
		{
			ptTR->bStatusOut=(ptTR->dwRetSCnt++)>=ptTR->dwTimeRetSet?FALSE:TRUE;
		}
	}
	else
	{
		ptTR->dwActSCnt = 0;
		ptTR->dwRetSCnt = 0;
	}
	return ptTR->bStatusOut;
}
// ============================================================================
// 函数功能：时间继电器停止
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_TimeRelayStop(tagTimeRelay *ptTR)
{
	ptTR->dwActSCnt = 0;
	ptTR->dwRetSCnt = 0;
	ptTR->bStatusOut = FALSE;
}
void IES_RamScanAdd(BYTE *pbyRamPtr)
{
	tagRamDot *ptRamDot;
	if(g_tagRamScan.dwRamPtr<CN_RAMSCAN_MAX)
	{
		ptRamDot=&g_tagRamScan.tRamDot[g_tagRamScan.dwRamPtr];
		ptRamDot->pbyRamPtr  =pbyRamPtr;
		*pbyRamPtr=CN_RAMSCAN_VALUE;
		ptRamDot->dwRamNo    =g_tagRamScan.dwRamPtr;
		g_tagRamScan.dwRamPtr++;
	}
}
void IES_RamScanChk()
{
	tagRamDot *ptRamDot;
	ptRamDot=&g_tagRamScan.tRamDot[g_tagRamScan.dwRamChkPtr];
	if((*ptRamDot->pbyRamPtr)!=CN_RAMSCAN_VALUE)
	{
		G_Set_ChkIn_All(EN_CHK_RAMERR,(UINT32)ptRamDot->pbyRamPtr, (UINT32)g_tagRamScan.dwRamChkPtr,0);
	}
	if(++g_tagRamScan.dwRamChkPtr>=g_tagRamScan.dwRamPtr)
	{
		g_tagRamScan.dwRamChkPtr=0;
	}
}
#if 0
void IES_ConstScanChk()
{
	switch(g_tagRamScan.dwConstType)
	{
		case EN_DTYPE_ANA:
			break;
		case EN_DTYPE_CAL:
			break;
		case EN_DTYPE_DC:
			break;
	}
	
}
#endif

