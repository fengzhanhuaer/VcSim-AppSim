/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * 积成电子股份有限公司
 * 元件名称：DI元件
 * 元件功能：DI元件
 *     1.硬开入处理逻辑
 *     2.硬开入双点合成
 *     3.GOOSE开入处理
 *     4.合成开入处理
 * 元件版本：V1.00
 * 定版时间：2021-2-24
 * 版本修改：
 * <版本号> <修改日期>, <修改人员>: <修改功能概述>
 * V1.00 2021-2-24 刘志利：初版
 *================================================================================*/
#ifndef _IES_IMDI_H_
#define _IES_IMDI_H_

#include "IES_IMSrc.h"
// 元件接口结构体
typedef struct
{
// 初始化标志
	BYTE            byRamScan1;
	UINT32          dwInit;                                    // 组件复归标志
	UINT32          dwBs;                                      // 组件闭锁标志
	UINT32          dwPWInit;                                  // 上电初始化标志
	UINT32          dwDIPWErr;                                 // 遥信电源异常标志
// 硬开入输入数据
	DWORD           dwDIBuf[CN_NUM_BOARD_DI];                  // 硬开入量缓存
	BYTE            byRamScan2;
	DWORD           dwDIXor[CN_NUM_BOARD_DI];                  // 硬开入量异或
	BYTE            byRamScan3;
// 硬开入防抖时间
	DWORD           dwDIFdTime[CN_NUM_DI];                     // 开入量去颤时间
	BYTE            byRamScan4;
	DWORD           dwDIQrTime[CN_NUM_DI];                     // 开入量确认时间
	BYTE            byRamScan5;
	BOOL            bYXPowEnaRef[CN_NUM_BOARD_DI];             // 遥信电源监视更新
	BYTE            byRamScan6;
	BOOL            bYXPowEna[CN_NUM_BOARD_DI];                // 遥信电源监视处理逻辑投退
	BYTE            byRamScan7;
// CPU侧防抖中间变量
	DWORD           dwDIHldCnt[CN_NUM_DI];                     // 开入量防抖计数
	BYTE            byRamScan8;
	DWORD           dwDIHldFlg[CN_NUM_DI];                     // 开入量防抖过程标志
	BYTE            byRamScan9;
	tagTimeUTC      tDITimeUTCB[CN_NUM_DI];                    // 开入变位前时间
	BYTE            byRamScan10;
	tagTimeUTC      tDITimeUTCF[CN_NUM_DI];                    // 开入变位后时间
	BYTE            byRamScan11;
// GOOSE输入数据
	BOOL            bTestErrA[CN_NUM_GOCB_SUB];                // 检修不一致保存
	BYTE            byRamScan12;
	BOOL            bTestErrB[CN_NUM_GOCB_SUB];                // 检修不一致保存
	BYTE            byRamScan13;
} tagIES_IMDI;
/*================================================================================*/
// 宏定义
/*================================================================================*/
// 去颤过程宏定义
#define  CN_HLD_FD   (0x55) // 去颤过程
#define  CN_HLD_QR   (0xAA) // 确认过程
#define  CN_HLD_RD   (0x0)  // 去颤完成
/*================================================================================*/
// 元件接口全局函数
/*================================================================================*/
extern  void    IES_IMDI_Para_Init();
extern  void    IES_IMDI_Init();
extern  void    IES_IMDI();
/*================================================================================*/
#endif

