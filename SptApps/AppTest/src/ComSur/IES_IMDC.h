/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * 积成电子股份有限公司
 * 元件名称：直流元件
 * 元件功能：直流元件
 *     1.直流数据处理
 *     2.直流换算
 *     3.直流输出
 * 元件版本：V1.00
 * 定版时间：2021-2-24
 * 版本修改：
 * <版本号> <修改日期>, <修改人员>: <修改功能概述>
 * V1.00 2021-2-24 刘志利：初版
 *================================================================================*/
#ifndef _IES_IMDC_H_
#define _IES_IMDC_H_
#include "IES_IMSrc.h"
// 直流参数定值结构
typedef struct
{
   BOOL     bDcOutType;                          // GO输出方式
   FLOAT32  fDcK;                                // 直流线性斜率
   INT32    iDcOfst;                             // 直流线性截距
}tagSamDcSet;
// 元件接口结构体
typedef struct
{
	BYTE            byRamScan1;
	UINT32          dwInit;                      // 组件复归标志
	UINT32          dwPWInit;                    // 上电初始化标志
	UINT32          dwDevCnt;                    // 固定延时使能
	tagSamDcSet     tSamDcSet[CN_NUM_DC_SAM];
	BYTE            byRamScan2;
	UINT32          dwDcTb[CN_NUM_DC_SAM];
	BYTE            byRamScan3;
	FLOAT32         fDcCoe[CN_NUM_DC];           // 校准系数
	BYTE            byRamScan4;
	FLOAT32         fDcVtomACoe;                 // 电流与电压系数的转换比例
	INT32           iDCOutBak[CN_NUM_DC];        // DC二次值变化备份
	BYTE            byRamScan5;
// 自动校准缓存
	BYTE            bAdjStr;                  // 自动校准启动
	BYTE            bAdjEnd;                  // 自动校准结束
	WORD            wAdjPtr;                  // 自动校准计数
	WORD            wAdjNum;                  // 自动校准周期数
	INT32           iAdjMin[CN_NUM_DC_SAM];   // 自动校准数据最小值缓存
	BYTE            byRamScan6;
	INT32           iAdjMax[CN_NUM_DC_SAM];   // 自动校准数据最大值缓存
	BYTE            byRamScan7;
	INT32           iAdjBuf[CN_NUM_DC_SAM];   // 自动校准数据缓存
	BYTE            byRamScan8;
} tagIES_IMDC;
/*================================================================================*/
// 元件接口全局函数
/*================================================================================*/
extern  BOOL    IES_IMDC_AdJ_Str(WORD wAdjNum);        // 自动校准启动
extern  UINT32  IES_IMDC_AdJ(BOOL *bChn);              // 自动校准接口
extern  void    IES_IMDC_Para_Init();                  // 参数更新接口
extern  void    IES_IMDC_Init();                       // 元件初始化接口
extern  void    IES_IMDC();                            // 元件接口
/*================================================================================*/
#endif

