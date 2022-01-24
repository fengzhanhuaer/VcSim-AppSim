/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * ���ɵ��ӹɷ����޹�˾
 * Ԫ�����ƣ����ò���Ԫ��
 * Ԫ�����ܣ����ò���Ԫ��
 * Ԫ���汾��V1.00
 * ����ʱ�䣺2020-9-7
 * �汾�޸ģ�
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
 * V1.00 2021-2-24,��־��:����
 *================================================================================*/

#include "IES_IMSrc.h"
// ============================================================================
// �������ܣ����ݳ�ʼ��
// ���������
// ���������
// ����ֵ��  ��
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
// �������ܣ����ݿ���
// ���������
// ���������
// ����ֵ��  ��
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
// �������ܣ�ʱ��̵�����ֵ��ֵ
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_TimeRelaySet(tagTimeRelay *ptTR, UINT32 dwTimeActSet, UINT32 dwTimeRetSet)
{
	ptTR->dwTimeActSet = dwTimeActSet;
	ptTR->dwTimeRetSet = dwTimeRetSet;
}
// ============================================================================
// �������ܣ�ʱ��̵���
//           ��ʱT1����,��ʱT2����
// ���������
// ���������
// ����ֵ��  ����ʱ���״̬
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
// �������ܣ�ʱ��̵���ֹͣ
// ���������
// ���������
// ����ֵ��  ��
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

