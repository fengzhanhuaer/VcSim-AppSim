/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * 积成电子股份有限公司
 * 元件名称：板件交互元件
 * 元件功能：板件交互元件
 * 元件版本：V1.00
 * 定版时间：2021-9-7
 * 版本修改：
 * <版本号> <修改日期>, <修改人员>: <修改功能概述>
 * V1.00 2021-2-24 刘志利：初版
 *================================================================================*/
#ifndef _IES_IMCOM_H_
#define _IES_IMCOM_H_

#include "IES_IMSrc.h"
/*================================================================================*/
// 外部函数声明
/*================================================================================*/
extern void IES_IMCom_Init_Tx();
extern void IES_IMCom_Fast_Tx();
extern void IES_IMCom_Slow_Tx();

extern BOOL IES_IMCom_Fast_Rx_Buf(BYTE *pbyData,WORD wLen,WORD wType);
extern BOOL IES_IMCom_Slow_Rx_Buf(BYTE *pbyData,WORD wLen,WORD wType);

extern void IES_IMCom_Init_Rx(UINT32 *pCfg);
extern void IES_IMCom_Fast_Rx();
extern void IES_IMCom_Slow_Rx();

extern void IES_IMCom_Init();
/*================================================================================*/
#endif /* _IES_IMCOM_H_ */
