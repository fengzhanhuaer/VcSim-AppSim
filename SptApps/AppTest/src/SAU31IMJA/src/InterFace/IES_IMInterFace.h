/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * ���ɵ��ӹɷ����޹�˾
 * Ԫ�����ƣ��ӿ�Ԫ��
 * Ԫ�����ܣ��ӿ�Ԫ��
 *     1.Ӧ���ϵ��ʼ��
 *     2.Ӧ��������ò���
 *     3.Ӧ��ƽ̨���ò���
 * Ԫ���汾��V1.00
 * ����ʱ�䣺2020-9-7
 * �汾�޸ģ�
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
 * V1.00 2021-2-24 ��־��������
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
// �ⲿ��������
/*================================================================================*/
extern void IES_IM_Init(void);
extern void IES_IM_Para_Init(void);
extern void IES_IM_Cfg_Init();
extern void IES_IM_Main(void);
extern void IES_IM_Interrupt(void);
/*================================================================================*/
#endif /* _IES_IMINTERFACE_H_ */
