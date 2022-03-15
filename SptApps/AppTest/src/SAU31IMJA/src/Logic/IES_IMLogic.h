/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * 积成电子股份有限公司
 * 元件名称：间隔采集执行单元逻辑元件
 * 元件功能：间隔采集执行单元逻辑元件
 *     1.电压切换
 *     2.级联切换
 *     3.三相不一致
 *     4.KKJ合后状态
 *     5.控制回路断线
 *     6.事故总
 *     7.闭锁重合闸开出(至另一套采集执行单元)
 *     8. 闭锁重合闸GOOSE信号(本套套采集执行单元)
 * 元件版本：V1.00
 * 定版时间：2020-9-7
 * 版本修改：
 * <版本号> <修改日期>, <修改人员>: <修改功能概述>
 * V1.00 2021-2-24 刘志利：初版
 *================================================================================*/
#ifndef _IES_IMLOGIC_H_
#define _IES_IMLOGIC_H_

#include "IES_IMSrc.h"

/*================================================================================*/
// 级联切换相关
#define CN_MULink_BC     (0)       // 级联切换保持状态
#define CN_MULink_A      (1)       // 级联切换选择A套采集执行单元
#define CN_MULink_B      (2)       // 级联切换选择B套采集执行单元
// 电压切换相关
#define CN_VolQH_BC      (0)       // 电压切换保持状态
#define CN_VolQH_1       (1)       // 电压切换选择Ⅰ母
#define CN_VolQH_2       (2)       // 电压切换选择Ⅱ母
#define CN_VolQH_NULL    (0xAA)    // 电压无效

// 元件接口结构体
typedef struct
{
	BYTE            byRamScan1;
	UINT32          dwInit; 		// 组件复归标志
	UINT32          dwPWInit; 		// 上电初始化标志
// 信号源相关设置
	BOOL            bDOpbEna; 		// 双线圈控制字
	BOOL            bDevEna; 		// 本装置B套投退
	BOOL            bKKJEna; 		// KKJ控制字：0-内采,1-外采
	BOOL            bSHJEna; 		// SHJ控制字：0-内采,1-外采
	BOOL            bSTJEna; 		// STJ控制字：0-内采,1-外采
//	BOOL            bHWJEna; 		// HWJ控制字：0-内采,1-外采
//	BOOL            bTWJEna; 		// TWJ控制字：0-内采,1-外采
	BOOL            bTJFEna; 		// TJF控制字：0-内采,1-外采
// 切换相关变量
	BOOL            bBusMuQhEna;	// 级联切换功能投退
	BOOL            bVolQhEna; 		// 电压切换功能投退
	tagTimeRelay    tTimer_PTRet; 	// PT同时返回确认时间
	tagTimeRelay    tTimer_SvA;  	// 级联A正常定时器
	tagTimeRelay    tTimer_SvB;  	// 级联B正常定时器
	BOOL            bVolType; 		// 电压采集方式
	BOOL            bVolTypeRef; 	// 电压采集方式变化
	BOOL            bBusMuQh; 		// 级联切换使能
	BOOL            bVolQh; 		// 电压切换使能
	UINT32          dwUxPhase; 		// Ux选相
	BOOL            bUxPhaseRef; 	// Ux选相参数更新标志
	UINT32          dwSxbyz; 		// 三相不一致遥信定义
// 闭锁重合相关定值
	BOOL            bYTBschBcEna;	// 遥跳(手跳)闭锁重合保持功能投退
	tagTimeRelay    tTimer_BschInit;// 装置上电闭锁重合保持时间
	BOOL            bYTBschBc;		// 遥跳(手跳)闭锁重合保持状态
	BYTE            byRamScan2;
} tagIES_IMJA;
/*================================================================================*/
// 元件接口全局函数
/*================================================================================*/
extern  void    IES_IMLogic_Para_Init();
extern  void    IES_IMLogic_Init();
extern  void    IES_IMLogic();
/*================================================================================*/
#endif/*_IES_IMLOGIC_H_*/

