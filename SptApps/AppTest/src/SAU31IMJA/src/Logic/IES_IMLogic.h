/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * ���ɵ��ӹɷ����޹�˾
 * Ԫ�����ƣ�����ɼ�ִ�е�Ԫ�߼�Ԫ��
 * Ԫ�����ܣ�����ɼ�ִ�е�Ԫ�߼�Ԫ��
 *     1.��ѹ�л�
 *     2.�����л�
 *     3.���಻һ��
 *     4.KKJ�Ϻ�״̬
 *     5.���ƻ�·����
 *     6.�¹���
 *     7.�����غ�բ����(����һ�ײɼ�ִ�е�Ԫ)
 *     8. �����غ�բGOOSE�ź�(�����ײɼ�ִ�е�Ԫ)
 * Ԫ���汾��V1.00
 * ����ʱ�䣺2020-9-7
 * �汾�޸ģ�
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
 * V1.00 2021-2-24 ��־��������
 *================================================================================*/
#ifndef _IES_IMLOGIC_H_
#define _IES_IMLOGIC_H_

#include "IES_IMSrc.h"

/*================================================================================*/
// �����л����
#define CN_MULink_BC     (0)       // �����л�����״̬
#define CN_MULink_A      (1)       // �����л�ѡ��A�ײɼ�ִ�е�Ԫ
#define CN_MULink_B      (2)       // �����л�ѡ��B�ײɼ�ִ�е�Ԫ
// ��ѹ�л����
#define CN_VolQH_BC      (0)       // ��ѹ�л�����״̬
#define CN_VolQH_1       (1)       // ��ѹ�л�ѡ���ĸ
#define CN_VolQH_2       (2)       // ��ѹ�л�ѡ���ĸ
#define CN_VolQH_NULL    (0xAA)    // ��ѹ��Ч

// Ԫ���ӿڽṹ��
typedef struct
{
	BYTE            byRamScan1;
	UINT32          dwInit; 		// ��������־
	UINT32          dwPWInit; 		// �ϵ��ʼ����־
// �ź�Դ�������
	BOOL            bDOpbEna; 		// ˫��Ȧ������
	BOOL            bDevEna; 		// ��װ��B��Ͷ��
	BOOL            bKKJEna; 		// KKJ�����֣�0-�ڲ�,1-���
	BOOL            bSHJEna; 		// SHJ�����֣�0-�ڲ�,1-���
	BOOL            bSTJEna; 		// STJ�����֣�0-�ڲ�,1-���
//	BOOL            bHWJEna; 		// HWJ�����֣�0-�ڲ�,1-���
//	BOOL            bTWJEna; 		// TWJ�����֣�0-�ڲ�,1-���
	BOOL            bTJFEna; 		// TJF�����֣�0-�ڲ�,1-���
// �л���ر���
	BOOL            bBusMuQhEna;	// �����л�����Ͷ��
	BOOL            bVolQhEna; 		// ��ѹ�л�����Ͷ��
	tagTimeRelay    tTimer_PTRet; 	// PTͬʱ����ȷ��ʱ��
	tagTimeRelay    tTimer_SvA;  	// ����A������ʱ��
	tagTimeRelay    tTimer_SvB;  	// ����B������ʱ��
	BOOL            bVolType; 		// ��ѹ�ɼ���ʽ
	BOOL            bVolTypeRef; 	// ��ѹ�ɼ���ʽ�仯
	BOOL            bBusMuQh; 		// �����л�ʹ��
	BOOL            bVolQh; 		// ��ѹ�л�ʹ��
	UINT32          dwUxPhase; 		// Uxѡ��
	BOOL            bUxPhaseRef; 	// Uxѡ��������±�־
	UINT32          dwSxbyz; 		// ���಻һ��ң�Ŷ���
// �����غ���ض�ֵ
	BOOL            bYTBschBcEna;	// ң��(����)�����غϱ��ֹ���Ͷ��
	tagTimeRelay    tTimer_BschInit;// װ���ϵ�����غϱ���ʱ��
	BOOL            bYTBschBc;		// ң��(����)�����غϱ���״̬
	BYTE            byRamScan2;
} tagIES_IMJA;
/*================================================================================*/
// Ԫ���ӿ�ȫ�ֺ���
/*================================================================================*/
extern  void    IES_IMLogic_Para_Init();
extern  void    IES_IMLogic_Init();
extern  void    IES_IMLogic();
/*================================================================================*/
#endif/*_IES_IMLOGIC_H_*/

