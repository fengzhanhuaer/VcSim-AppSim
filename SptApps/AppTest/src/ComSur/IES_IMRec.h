/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * ���ɵ��ӹɷ����޹�˾
 * Ԫ�����ƣ�����Ԫ��
 * Ԫ�����ܣ�����Ԫ��
 *     1.�澯��������
 *     2.Խ������ϳ�
 * Ԫ���汾��V1.00
 * ����ʱ�䣺2020-9-7
 * �汾�޸ģ�
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
 * V1.00 2021-2-24 ��־��������
 *================================================================================*/

#ifndef _IES_IMRec_H_
#define _IES_IMRec_H_

#include "IES_IMSrc.h"
#include "IES_IMPub.h"
// GOOSE���������ö��1
enum _TYPE_ACT_REC_
{
	EN_ACTS_EVENT_NULL=0,  // �������
	EN_ACTS_EVENT_WAIT,    // �ȴ����ڷ�У
	EN_ACTS_EVENT_STOP,    // �����¼ֹͣ
};
enum _TYPE_ACT_VAILD_
{
	EN_VAILD_STR=0,               // �����źſ�ʼ
	EN_VAILD_GOOSE  =EN_VAILD_STR,// GOOSE����
	EN_VAILD_DO,                  // ��������
	EN_VAILD_RET_T,               // ���ڷ�Уʱ��
	EN_VAILD_FAIL,                // ����ʧ��ԭ��
	EN_VAILD_SRC_APPID,           // ����ԴAPPID
	EN_VAILD_SRC_INDEX,           // ����ԴIndex
	EN_VAILD_END,                 // 
};
enum _TYPE_ACT_RET_
{
	EN_RET_STR=EN_INVAILD_END,   // ��У��ʼ
	EN_RET_OVER  =EN_RET_STR,    // ��У��ʱ
	EN_RET_ELSE,                 // �ѷ�У
	EN_RET_COVER,                // �����
	EN_RET_DIF,                  // ���һ��
	EN_RET_END,                  // 
};

// Ԫ���ӿڽṹ��
typedef struct
{
	BYTE            byRamScan1;
	UINT32          dwInit;                       // ��������־
	UINT32          dwPWInit;                     // �ϵ��ʼ����־
	BOOL            bAlmEna[CN_NUM_ALM];          // ����Ͷ��
	BYTE            byRamScan2;
	BOOL            bChkEna[CN_NUM_CHK];          // ����Ͷ��
	BYTE            byRamScan3;
	BOOL            bAlmTimerEna[CN_NUM_ALM];     // �澯ʱ��̵���ʹ��
	BYTE            byRamScan4;
	tagTimeRelay    tTimer_Alm[CN_NUM_ALM];       // �澯ʱ��̵���
	BYTE            byRamScan5;
} tagIES_IMRec;
/*================================================================================*/
// Ԫ���ӿ�ȫ�ֺ���
/*================================================================================*/
extern  void    IES_IMRec_Para_Init();
extern  void    IES_IMRec_Init();
extern  void    IES_IMRec();
/*================================================================================*/
#endif

