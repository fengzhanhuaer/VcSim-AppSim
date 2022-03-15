/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * ���ɵ��ӹɷ����޹�˾
 * Ԫ�����ƣ��������Ԫ��
 * Ԫ�����ܣ��������Ԫ��
 * Ԫ���汾��V1.00
 * ����ʱ�䣺2021-9-7
 * �汾�޸ģ�
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
 * V1.00 2021-2-24 ��־��������
 *================================================================================*/
#ifndef _IES_IMCOM_H_
#define _IES_IMCOM_H_

#include "IES_IMSrc.h"
/*================================================================================*/
// �ⲿ��������
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
