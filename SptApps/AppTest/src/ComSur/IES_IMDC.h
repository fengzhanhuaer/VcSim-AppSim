/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * ���ɵ��ӹɷ����޹�˾
 * Ԫ�����ƣ�ֱ��Ԫ��
 * Ԫ�����ܣ�ֱ��Ԫ��
 *     1.ֱ�����ݴ���
 *     2.ֱ������
 *     3.ֱ�����
 * Ԫ���汾��V1.00
 * ����ʱ�䣺2021-2-24
 * �汾�޸ģ�
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
 * V1.00 2021-2-24 ��־��������
 *================================================================================*/
#ifndef _IES_IMDC_H_
#define _IES_IMDC_H_
#include "IES_IMSrc.h"
// ֱ��������ֵ�ṹ
typedef struct
{
   BOOL     bDcOutType;                          // GO�����ʽ
   FLOAT32  fDcK;                                // ֱ������б��
   INT32    iDcOfst;                             // ֱ�����Խؾ�
}tagSamDcSet;
// Ԫ���ӿڽṹ��
typedef struct
{
	BYTE            byRamScan1;
	UINT32          dwInit;                      // ��������־
	UINT32          dwPWInit;                    // �ϵ��ʼ����־
	UINT32          dwDevCnt;                    // �̶���ʱʹ��
	tagSamDcSet     tSamDcSet[CN_NUM_DC_SAM];
	BYTE            byRamScan2;
	UINT32          dwDcTb[CN_NUM_DC_SAM];
	BYTE            byRamScan3;
	FLOAT32         fDcCoe[CN_NUM_DC];           // У׼ϵ��
	BYTE            byRamScan4;
	FLOAT32         fDcVtomACoe;                 // �������ѹϵ����ת������
	INT32           iDCOutBak[CN_NUM_DC];        // DC����ֵ�仯����
	BYTE            byRamScan5;
// �Զ�У׼����
	BYTE            bAdjStr;                  // �Զ�У׼����
	BYTE            bAdjEnd;                  // �Զ�У׼����
	WORD            wAdjPtr;                  // �Զ�У׼����
	WORD            wAdjNum;                  // �Զ�У׼������
	INT32           iAdjMin[CN_NUM_DC_SAM];   // �Զ�У׼������Сֵ����
	BYTE            byRamScan6;
	INT32           iAdjMax[CN_NUM_DC_SAM];   // �Զ�У׼�������ֵ����
	BYTE            byRamScan7;
	INT32           iAdjBuf[CN_NUM_DC_SAM];   // �Զ�У׼���ݻ���
	BYTE            byRamScan8;
} tagIES_IMDC;
/*================================================================================*/
// Ԫ���ӿ�ȫ�ֺ���
/*================================================================================*/
extern  BOOL    IES_IMDC_AdJ_Str(WORD wAdjNum);        // �Զ�У׼����
extern  UINT32  IES_IMDC_AdJ(BOOL *bChn);              // �Զ�У׼�ӿ�
extern  void    IES_IMDC_Para_Init();                  // �������½ӿ�
extern  void    IES_IMDC_Init();                       // Ԫ����ʼ���ӿ�
extern  void    IES_IMDC();                            // Ԫ���ӿ�
/*================================================================================*/
#endif

