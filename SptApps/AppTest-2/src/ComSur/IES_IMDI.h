/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * ���ɵ��ӹɷ����޹�˾
 * Ԫ�����ƣ�DIԪ��
 * Ԫ�����ܣ�DIԪ��
 *     1.Ӳ���봦���߼�
 *     2.Ӳ����˫��ϳ�
 *     3.GOOSE���봦��
 *     4.�ϳɿ��봦��
 * Ԫ���汾��V1.00
 * ����ʱ�䣺2021-2-24
 * �汾�޸ģ�
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
 * V1.00 2021-2-24 ��־��������
 *================================================================================*/
#ifndef _IES_IMDI_H_
#define _IES_IMDI_H_

#include "IES_IMSrc.h"
// Ԫ���ӿڽṹ��
typedef struct
{
// ��ʼ����־
	BYTE            byRamScan1;
	UINT32          dwInit;                                    // ��������־
	UINT32          dwBs;                                      // ���������־
	UINT32          dwPWInit;                                  // �ϵ��ʼ����־
	UINT32          dwDIPWErr;                                 // ң�ŵ�Դ�쳣��־
// Ӳ������������
	DWORD           dwDIBuf[CN_NUM_BOARD_DI];                  // Ӳ����������
	BYTE            byRamScan2;
	DWORD           dwDIXor[CN_NUM_BOARD_DI];                  // Ӳ���������
	BYTE            byRamScan3;
// Ӳ�������ʱ��
	DWORD           dwDIFdTime[CN_NUM_DI];                     // ������ȥ��ʱ��
	BYTE            byRamScan4;
	DWORD           dwDIQrTime[CN_NUM_DI];                     // ������ȷ��ʱ��
	BYTE            byRamScan5;
	BOOL            bYXPowEnaRef[CN_NUM_BOARD_DI];             // ң�ŵ�Դ���Ӹ���
	BYTE            byRamScan6;
	BOOL            bYXPowEna[CN_NUM_BOARD_DI];                // ң�ŵ�Դ���Ӵ����߼�Ͷ��
	BYTE            byRamScan7;
// CPU������м����
	DWORD           dwDIHldCnt[CN_NUM_DI];                     // ��������������
	BYTE            byRamScan8;
	DWORD           dwDIHldFlg[CN_NUM_DI];                     // �������������̱�־
	BYTE            byRamScan9;
	tagTimeUTC      tDITimeUTCB[CN_NUM_DI];                    // �����λǰʱ��
	BYTE            byRamScan10;
	tagTimeUTC      tDITimeUTCF[CN_NUM_DI];                    // �����λ��ʱ��
	BYTE            byRamScan11;
// GOOSE��������
	BOOL            bTestErrA[CN_NUM_GOCB_SUB];                // ���޲�һ�±���
	BYTE            byRamScan12;
	BOOL            bTestErrB[CN_NUM_GOCB_SUB];                // ���޲�һ�±���
	BYTE            byRamScan13;
} tagIES_IMDI;
/*================================================================================*/
// �궨��
/*================================================================================*/
// ȥ�����̺궨��
#define  CN_HLD_FD   (0x55) // ȥ������
#define  CN_HLD_QR   (0xAA) // ȷ�Ϲ���
#define  CN_HLD_RD   (0x0)  // ȥ�����
/*================================================================================*/
// Ԫ���ӿ�ȫ�ֺ���
/*================================================================================*/
extern  void    IES_IMDI_Para_Init();
extern  void    IES_IMDI_Init();
extern  void    IES_IMDI();
/*================================================================================*/
#endif

