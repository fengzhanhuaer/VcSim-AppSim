/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * ���ɵ��ӹɷ����޹�˾
 * Ԫ�����ƣ�����Ԫ��
 * Ԫ�����ܣ�����Ԫ��
 *     1.Ӳ���ڿ���
 *     2.GOOSE��������
 *     3.ָʾ�ƿ���
 * Ԫ���汾��V1.00
 * ����ʱ�䣺2020-9-7
 * �汾�޸ģ�
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
 * V1.00 2021-2-24 ��־��������
 *================================================================================*/
#ifndef _IES_IMDO_H_
#define _IES_IMDO_H_

#include "IES_IMSrc.h"
// �̵�����У��ʱ��
typedef struct
{
	BOOL            bStrEna;
	UINT32          dwTimeRtn;
} tagTimerRtn;
// Ԫ���ӿڽṹ��
typedef struct
{
	BYTE            byRamScan1;
	UINT32          dwInit;                      // ��������־
	UINT32          dwPWInit;                    // �ϵ��ʼ����־
	UINT32          dwDoRtnT;                    // ���ڷ�У��ʱ
	tagTimerRtn     tTimerRtn[CN_NUM_DO];        // ���ڷ�У��ʱ��
	BYTE            byRamScan2;
	UINT32          dwRtn1[CN_NUM_BOARD_DO];     // ���ڷ�У״̬
	BYTE            byRamScan3;
	UINT32          dwRtn0[CN_NUM_BOARD_DO];     // ���ڷ�У״̬
	BYTE            byRamScan4;
} tagIES_IMDO;
/*================================================================================*/
// Ԫ���ӿ�ȫ�ֺ���
/*================================================================================*/
extern  void    IES_IMDO_Para_Init();
extern  void    IES_IMDO_Init();
extern  void    IES_IMDO();
/*================================================================================*/
#endif

