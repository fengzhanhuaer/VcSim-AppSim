/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * 积成电子股份有限公司
 * 元件名称：事项元件
 * 元件功能：事项元件
 *     1.告警事项生成
 *     2.越限事项合成
 * 元件版本：V1.00
 * 定版时间：2020-9-7
 * 版本修改：
 * <版本号> <修改日期>, <修改人员>: <修改功能概述>
 * V1.00 2021-2-24 刘志利：初版
 *================================================================================*/

#ifndef _IES_IMRec_H_
#define _IES_IMRec_H_

#include "IES_IMSrc.h"
#include "IES_IMPub.h"
// GOOSE命令事项辅助枚举1
enum _TYPE_ACT_REC_
{
	EN_ACTS_EVENT_NULL=0,  // 事项空闲
	EN_ACTS_EVENT_WAIT,    // 等待出口返校
	EN_ACTS_EVENT_STOP,    // 事项记录停止
};
enum _TYPE_ACT_VAILD_
{
	EN_VAILD_STR=0,               // 操作信号开始
	EN_VAILD_GOOSE  =EN_VAILD_STR,// GOOSE命令
	EN_VAILD_DO,                  // 出口命令
	EN_VAILD_RET_T,               // 出口返校时间
	EN_VAILD_FAIL,                // 出口失败原因
	EN_VAILD_SRC_APPID,           // 命令源APPID
	EN_VAILD_SRC_INDEX,           // 命令源Index
	EN_VAILD_END,                 // 
};
enum _TYPE_ACT_RET_
{
	EN_RET_STR=EN_INVAILD_END,   // 返校开始
	EN_RET_OVER  =EN_RET_STR,    // 返校超时
	EN_RET_ELSE,                 // 已返校
	EN_RET_COVER,                // 命令覆盖
	EN_RET_DIF,                  // 命令不一致
	EN_RET_END,                  // 
};

// 元件接口结构体
typedef struct
{
	BYTE            byRamScan1;
	UINT32          dwInit;                       // 组件复归标志
	UINT32          dwPWInit;                     // 上电初始化标志
	BOOL            bAlmEna[CN_NUM_ALM];          // 功能投退
	BYTE            byRamScan2;
	BOOL            bChkEna[CN_NUM_CHK];          // 功能投退
	BYTE            byRamScan3;
	BOOL            bAlmTimerEna[CN_NUM_ALM];     // 告警时间继电器使能
	BYTE            byRamScan4;
	tagTimeRelay    tTimer_Alm[CN_NUM_ALM];       // 告警时间继电器
	BYTE            byRamScan5;
} tagIES_IMRec;
/*================================================================================*/
// 元件接口全局函数
/*================================================================================*/
extern  void    IES_IMRec_Para_Init();
extern  void    IES_IMRec_Init();
extern  void    IES_IMRec();
/*================================================================================*/
#endif

