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
#ifndef _IES_IMDO_H_
#define _IES_IMDO_H_

#include "IES_IMSrc.h"
// 继电器返校计时器
typedef struct
{
	BOOL            bStrEna;
	UINT32          dwTimeRtn;
} tagTimerRtn;
// 元件接口结构体
typedef struct
{
	BYTE            byRamScan1;
	UINT32          dwInit;                      // 组件复归标志
	UINT32          dwPWInit;                    // 上电初始化标志
	UINT32          dwDoRtnT;                    // 出口返校延时
	tagTimerRtn     tTimerRtn[CN_NUM_DO];        // 出口返校定时器
	BYTE            byRamScan2;
	UINT32          dwRtn1[CN_NUM_BOARD_DO];     // 出口返校状态
	BYTE            byRamScan3;
	UINT32          dwRtn0[CN_NUM_BOARD_DO];     // 出口返校状态
	BYTE            byRamScan4;
} tagIES_IMDO;
/*================================================================================*/
// 元件接口全局函数
/*================================================================================*/
extern  void    IES_IMDO_Para_Init();
extern  void    IES_IMDO_Init();
extern  void    IES_IMDO();
/*================================================================================*/
#endif

