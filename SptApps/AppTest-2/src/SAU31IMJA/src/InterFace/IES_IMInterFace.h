/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * 积成电子股份有限公司
 * 元件名称：接口元件
 * 元件功能：接口元件
 *     1.应用上电初始化
 *     2.应用任务调用部分
 *     3.应用平台调用部分
 * 元件版本：V1.00
 * 定版时间：2020-9-7
 * 版本修改：
 * <版本号> <修改日期>, <修改人员>: <修改功能概述>
 * V1.00 2021-2-24 刘志利：初版
 *================================================================================*/
#ifndef _IES_IMINTERFACE_H_
#define _IES_IMINTERFACE_H_

#include "IES_IMInit.h"
#include "IES_IMSam.h"
#include "IES_IMDI.h"
#include "IES_IMFlag.h"
#include "IES_IMDO.h"
#include "IES_IMDC.h"
#include "IES_IMPub.h"
#include "IES_IMLogic.h"
#include "IES_IMRec.h"
#include "IES_IMCom.h"
/*================================================================================*/
// 外部函数声明
/*================================================================================*/
extern void IES_IM_Init(void);
extern void IES_IM_Para_Init(void);
extern void IES_IM_Cfg_Init();
extern void IES_IM_Main(void);
extern void IES_IM_Interrupt(void);
/*================================================================================*/
#endif /* _IES_IMINTERFACE_H_ */
