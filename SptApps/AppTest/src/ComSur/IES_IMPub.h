/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * 积成电子股份有限公司
 * 元件名称：采集执行单元公共元件
 * 元件功能：采集执行单元公共元件
 * 元件版本：V1.00
 * 定版时间：2020-9-7
 * 版本修改：
 * <版本号> <修改日期>, <修改人员>: <修改功能概述>
 * V1.00 2021-2-24,刘志利:初版
 *================================================================================*/
#ifndef _IES_IMPUB_H_
#define _IES_IMPUB_H_

#include "Const_Pub.h"

// 定时器结构体
typedef struct
{
	UINT32		dwTimeActSet;		// 动作(1)延时定值(中断点数)
	UINT32		dwTimeRetSet;		// 返回(0)延时定值(中断点数)
	UINT32		dwActSCnt; 			// 动作(1)计数器
	UINT32		dwRetSCnt; 			// 返回(0)计数器
	BOOL		bStatusOut; 		// 输出状态
} tagTimeRelay;
/*================================================================================*/
// 元件接口全局函数
/*================================================================================*/
extern  BOOL  IES_memset(void *pDst,BYTE byDate,DWORD dwLen);
extern  BOOL  IES_memcpy(void *pDst,DWORD dwDstLen,void *pSrc,DWORD dwSrcLen);
#ifdef __cplusplus
extern  inline void  IES_TimeRelaySet(tagTimeRelay *ptTR, UINT32 dwTimeActSet, UINT32 dwTimeRetSet)
{
	ptTR->dwTimeActSet = dwTimeActSet;
	ptTR->dwTimeRetSet = dwTimeRetSet;
}
#else
#define IES_TimeRelaySet(ptTR, dwTimeActSet, dwTimeRetSet)  \
{                                      \
	ptTR->dwTimeActSet = dwTimeActSet; \
	ptTR->dwTimeRetSet = dwTimeRetSet; \
}
#endif
extern  BOOL  IES_TimeRelayRun(tagTimeRelay *ptTR, BOOL bStatus);
#ifdef __cplusplus
extern  inline void IES_TimeRelayStop(tagTimeRelay *ptTR)
{
	ptTR->dwActSCnt = 0;
	ptTR->dwRetSCnt = 0;
	ptTR->bStatusOut = FALSE;
}
#else
#define IES_TimeRelayStop(tagTimeRelay *ptTR)\
{                             \
	ptTR->dwActSCnt = 0;      \
	ptTR->dwRetSCnt = 0;      \
	ptTR->bStatusOut = FALSE; \
}
#endif
extern  void  IES_RamScanAdd(BYTE *pdwRamPtr);
extern  void  IES_RamScanChk();
/*================================================================================*/
#endif/*_IES_IMPUB_H_*/

