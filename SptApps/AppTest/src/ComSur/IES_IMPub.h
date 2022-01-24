/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * ���ɵ��ӹɷ����޹�˾
 * Ԫ�����ƣ��ɼ�ִ�е�Ԫ����Ԫ��
 * Ԫ�����ܣ��ɼ�ִ�е�Ԫ����Ԫ��
 * Ԫ���汾��V1.00
 * ����ʱ�䣺2020-9-7
 * �汾�޸ģ�
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
 * V1.00 2021-2-24,��־��:����
 *================================================================================*/
#ifndef _IES_IMPUB_H_
#define _IES_IMPUB_H_

#include "Const_Pub.h"

// ��ʱ���ṹ��
typedef struct
{
	UINT32		dwTimeActSet;		// ����(1)��ʱ��ֵ(�жϵ���)
	UINT32		dwTimeRetSet;		// ����(0)��ʱ��ֵ(�жϵ���)
	UINT32		dwActSCnt; 			// ����(1)������
	UINT32		dwRetSCnt; 			// ����(0)������
	BOOL		bStatusOut; 		// ���״̬
} tagTimeRelay;
/*================================================================================*/
// Ԫ���ӿ�ȫ�ֺ���
/*================================================================================*/
extern  BOOL  IES_memset(void *pDst,BYTE byDate,DWORD dwLen);
extern  BOOL  IES_memcpy(void *pDst,DWORD dwDstLen,void *pSrc,DWORD dwSrcLen);
extern  void  IES_TimeRelaySet(tagTimeRelay *ptTR, UINT32 dwTimeActSet, UINT32 dwTimeRetSet);
extern  BOOL  IES_TimeRelayRun(tagTimeRelay *ptTR, BOOL bStatus);
extern  void  IES_TimeRelayStop(tagTimeRelay *ptTR);

extern  void  IES_RamScanAdd(BYTE *pdwRamPtr);
extern  void  IES_RamScanChk();
/*================================================================================*/
#endif/*_IES_IMPUB_H_*/

