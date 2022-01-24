/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * ���ɵ��ӹɷ����޹�˾
 * Ԫ�����ƣ�����Ԫ��
 * Ԫ������������Ԫ��
 * Ԫ�����ܣ����������������㼰���
 * Ԫ���汾��V1.00
 * ����ʱ�䣺2020-2-24
 * �汾�޸ģ�
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���> 
 * V1.00 2021-2-24 ��־��������
 *================================================================================*/
#ifndef _IES_IMSAM_H_
#define _IES_IMSAM_H_

#include "IES_IMSrc.h"
// Ԫ���ӿڽṹ��
typedef struct
{
// ��ʼ����־
	BYTE            byRamScan1;                  // ɨ���ڴ�Ƭ
	UINT32          dwInit;                      // ��������־
	UINT32          dwBs;                        // ���������־
	UINT32          dwPWInit;                    // �ϵ��ʼ����־
	UINT32          dwMenuInit;                  // �����˳�������־
	UINT32          dwJumpCnt;                   // ֡�������ͳ��
	UINT32          dwLostCnt;                   // ��֡ͳ��
// ��������
	UINT32          dwWaveFlag;                  // ģ���������־
	UINT32          dwAnaPtr;                    // ��������ָ��
// ����ʵ�鲿
	INT64           iAnaReal[CN_NUM_ANA];        // ʵ��
	BYTE            byRamScan2;                  // ɨ���ڴ�Ƭ
	INT64           iAnaImag[CN_NUM_ANA];        // �鲿
	BYTE            byRamScan3;                  // ɨ���ڴ�Ƭ
#if(CN_HUM_ENA)	
// 13��г��ʵ�鲿
	INT64           iAnaHumReal[CN_NUM_ANA][CN_HUM_NUM];        // г��ʵ��
	BYTE            byRamScan4;                                 // ɨ���ڴ�Ƭ
	INT64           iAnaHumImag[CN_NUM_ANA][CN_HUM_NUM];        // г���鲿
	BYTE            byRamScan5;                                 // ɨ���ڴ�Ƭ
#endif	
// ���ַ�ֵ
	UINT64          dwAnaAm[CN_NUM_ANA];         // ��ֵ
	BYTE            byRamScan6;                  // ɨ���ڴ�Ƭ
// һ����ת��ϵ��
	FLOAT32         fAnaBb[CN_NUM_ANA];           // һ����ת��ϵ��
	BYTE            byRamScan7;                  // ɨ���ڴ�Ƭ
// ��׼��ѹ�ż�
	BOOL            bJzChkEna;                    // ��׼��ѹ�Լ������
	UINT32          dwJz1MkMin;                    // ��׼��ѹ1���޶�ֵ
	UINT32          dwJz1MkMax;                    // ��׼��ѹ1���޶�ֵ
	UINT32          dwJz2MkMin;                    // ��׼��ѹ2���޶�ֵ
	UINT32          dwJz2MkMax;                    // ��׼��ѹ2���޶�ֵ
	BOOL            bJzChk[CN_NUM_JZ];            // ��׼��ѹԽ��
	BYTE            byRamScan8;                  // ɨ���ڴ�Ƭ
// ��Ƶ�������
	UINT32          dwFBc[CN_NUM_CAL];            // ��Ƶ�Ʋ���
	BYTE            byRamScan9;                  // ɨ���ڴ�Ƭ
	UINT32          dwFDly[CN_NUM_CAL];           // ��Ƶ������
	BYTE            byRamScan10;                  // ɨ���ڴ�Ƭ
	UINT32          dwFCal[CN_NUM_CAL];           // ��Ƶ���
	BYTE            byRamScan11;                  // ɨ���ڴ�Ƭ
	UINT32          dwFCnt[CN_NUM_CAL];           // ��������
	BYTE            byRamScan12;                  // ɨ���ڴ�Ƭ
// ��ֵ�Զ�У׼����
	BYTE            bAdjAmStr;                    // �Զ�У׼����
	BYTE            bAdjAmEnd;                    // �Զ�У׼����
	WORD            wAdjAmPtr;                    // �Զ�У׼����
	WORD            wAdjAmNum;                    // �Զ�У׼�ܲ���
	DWORD           dwAdjAmMin[CN_NUM_SAM];       // �Զ�У׼ʱ�������Сֵ
	BYTE            byRamScan13;                  // ɨ���ڴ�Ƭ
	DWORD           dwAdjAmMax[CN_NUM_SAM];       // �Զ�У׼ʱ��������ֵ
	BYTE            byRamScan14;                  // ɨ���ڴ�Ƭ
	DWORD           dwAdjAmBuf[CN_NUM_SAM];       // �Զ�У׼���ݻ���
	BYTE            byRamScan15;                  // ɨ���ڴ�Ƭ
// ֱ�������Զ�У׼����
	BYTE           bAdjDcStr;                      // �Զ�У׼����
	BYTE           bAdjDcEnd;                      // �Զ�У׼����
	WORD           wAdjDcPtr;                      // �Զ�У׼����
	WORD           wAdjDcNum;                      // �Զ�У׼�ܲ���
	INT32          iAdjDcMin[CN_NUM_SAM];          // �Զ�У׼ʱ�������Сֵ
	BYTE           byRamScan16;                    // ɨ���ڴ�Ƭ
	INT32          iAdjDcMax[CN_NUM_SAM];          // �Զ�У׼ʱ��������ֵ
	BYTE           byRamScan17;                    // ɨ���ڴ�Ƭ
	INT32          iAdjDcBuf[CN_NUM_SAM];          // �Զ�У׼���ݻ���
	BYTE           byRamScan18;                    // ɨ���ڴ�Ƭ
// ��λ�����Զ�У׼����
	BYTE           bAdjAngStr;                    // �Զ�У׼����
	BYTE           bAdjAngEnd;                    // �Զ�У׼����
	WORD           wAdjAngPtr;                    // �Զ�У׼����
	WORD           wAdjAngNum;                    // �Զ�У׼�ܲ���
	DWORD          dwAdjAngAmMin[CN_NUM_SAM];     // �Զ�У׼ʱ����ڷ�ֵ��Сֵ
	BYTE           byRamScan19;                   // ɨ���ڴ�Ƭ
	DWORD          dwAdjAngAmMax[CN_NUM_SAM];     // �Զ�У׼ʱ����ڷ�ֵ���ֵ
	BYTE           byRamScan20;                   // ɨ���ڴ�Ƭ
	INT32          iAdjAngMin[CN_NUM_SAM];        // �Զ�У׼ʱ�������λ��Сֵ
	BYTE           byRamScan21;                   // ɨ���ڴ�Ƭ
	INT32          iAdjAngMax[CN_NUM_SAM];        // �Զ�У׼ʱ�������λ���ֵ
	BYTE           byRamScan22;                   // ɨ���ڴ�Ƭ
	INT32          iAdjAngBuf[CN_NUM_SAM];        // �Զ�У׼���ݻ���
	BYTE           byRamScan23;                   // ɨ���ڴ�Ƭ
#if(CN_TCHG_ENA)	
	// �¶Ȳ���
	UINT32          dwCoeTMod;                     // �¶ȵ���ģʽ
	UINT32          dwCoeTModStr;                  // �¶ȵ���ģʽ����
	UINT32          dwCoeTCnt;                     // �¶ȵ���ģʽ��ʱ��
#endif
// ����������
#if(CN_SV_IN_ENA)
	UINT32          dwPolSvAMat;                  // A��SV�����Է��������þ���
	UINT32          dwPolSvBMat;                  // B��SV�����Է��������þ���
#endif	
	UINT32          dwPolSamMat1;                 // ����ģ�������������þ���1
	UINT32          dwPolSamMat2;                 // ����ģ�������������þ���2
	BYTE            byRamScan24;                  // ɨ���ڴ�Ƭ
} tag_IMSam;

/*================================================================================*/
// Ԫ���ӿ�ȫ�ֺ���
/*================================================================================*/
#if(CN_SV_IN_ENA)
extern  void    IES_IMSam_SvSub_Init();          // ����Ԫ��������ʼ������
#endif
extern  void    IES_IMSam_SvPub_Init();          // ����Ԫ��������ʼ������
extern  void    IES_IMSam_Para_Init();           // ����Ԫ��������ʼ������
extern  void    IES_IMSam_Init();                // ����Ԫ���ϵ��ʼ������
extern  void    IES_IMSam_Q();                   // ����Ԫ��ִ�к���
extern  void    IES_IMSam();                     // ����Ԫ��ִ�к���
 // ����ӿ�
 
extern  BOOL    IES_IMSam_AdJAm_Str(WORD wAdjNum);    // ��ֵ�Զ�У׼����
extern  UINT32  IES_IMSam_AdJAm(BOOL *pbChn);         // ��ֵ�Զ�У׼
extern  BOOL    IES_IMSam_AdJDc_Str(WORD wAdjNum);    // ֱ�������Զ�У׼����
extern  UINT32  IES_IMSam_AdJDc(BOOL *pbChn);         // ֱ�������Զ�У׼
extern  BOOL    IES_IMSam_AdJAng_Str(WORD wAdjNum);   // ��λ�Զ�У׼����
extern  UINT32  IES_IMSam_AdJAng(BOOL *pbChn);        // ��λ�Զ�У׼
extern  void    IES_IMSam_SvPub_Chg(WORD wIndexSrc,WORD wIndexDst,WORD wAddNum,DWORD dwChg1,DWORD dwChg2);      // SVPUB������̬�޸Ľӿ�
extern  BOOL    IES_IMSam_SvPub_Cal(WORD wIndexSrc1,WORD wIndexSrc2,WORD wIndexDst);  // SVPUB����ͨ������ӿ�
/*================================================================================*/
#endif  /* _IES_IMSAM_H_ */
