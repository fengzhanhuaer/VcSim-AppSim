/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * ���ɵ��ӹɷ����޹�˾
 * Ԫ�����ƣ��м��־Ԫ��
 * Ԫ�����ܣ��м��־Ԫ��
 *     1.�м��־�ϳ�
 *     2.�м��־ת��
 * Ԫ���汾��V1.00
 * ����ʱ�䣺2020-9-7
 * �汾�޸ģ�
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
 * V1.00 2021-2-24 ��־��������
 *================================================================================*/

#ifndef _IES_IMFLAG_H_
#define _IES_IMFLAG_H_

#include "IES_IMSrc.h"
// Ԫ���ӿڽṹ��
typedef struct
{
	BYTE            byRamScan1;
	UINT32          dwInit;         // ��������־
	UINT32          dwPWInit;       // �ϵ��ʼ����־
	UINT32          dwResetCnt;     // ���鷵�ؼ���
	BYTE            byRamScan2;
} tagIES_IMFlag;

/*================================================================================*/
// Ԫ���ӿ�ȫ�ֺ���
/*================================================================================*/
extern  void    IES_IMFlag_Para_Init();
extern  void    IES_IMFlag_Init();
extern  void    IES_IMFlag();
/*================================================================================*/
#endif/*_IES_IMFLAG_H_*/
