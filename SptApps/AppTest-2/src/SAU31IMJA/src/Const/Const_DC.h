#ifndef _CONST_DC_H_
#define _CONST_DC_H_

#include "IES_IMtypes.h"
/*================================================================================*/
// �ź�ö��
/*================================================================================*/
enum _DC_INDEX_TYPE_
{
//  ֱ��ģ����ͨ��
    EN_DC_SAM_STR=0,
    EN_DC_SAM1=EN_DC_SAM_STR,                  // ֱ����ʼ
    EN_DC_SAM2,                                // ֱ���ɼ�2
#if(!CN_FUN_DBUG1)
    EN_DC_SAM3,                                // ֱ���ɼ�3
    EN_DC_SAM4,                                // ֱ���ɼ�4
    EN_DC_SAM5,                                // ֱ���ɼ�5
    EN_DC_SAM6,                                // ֱ���ɼ�6
    EN_DC_SAM7,                                // ֱ���ɼ�7
#endif
    EN_DC_SAM_END,                             // ֱ�ɽ���
//  ���߼������
    EN_DC_DEV_STR=EN_DC_SAM_END,
    EN_DC_DEV1_STR=EN_DC_DEV_STR,
    EN_DC_T1=EN_DC_DEV1_STR,                   // �¶�1
    EN_DC_V1,                                  // �ڲ���ѹ1
    EN_DC_V2,                                  // �ڲ���ѹ2
    EN_DC_V3,                                  // �ڲ���ѹ3
    EN_DC_V4,                                  // �ڲ���ѹ4
    EN_DC_V5,                                  // �ڲ���ѹ5
    EN_DC_CCD_CRC,                             // CCD�ļ�CRC
    EN_DC_DEV1_END,
    EN_DC_DEV2_STR=EN_DC_DEV1_END,
    EN_DC_T2=EN_DC_DEV2_STR,                   // �¶�2
    EN_DC_V6,                                  // �ڲ���ѹ6
    EN_DC_V7,                                  // �ڲ���ѹ7
    EN_DC_V8,                                  // �ڲ���ѹ8
    EN_DC_V9,                                  // �ڲ���ѹ9
    EN_DC_V10,                                 // �ڲ���ѹ10
    EN_DC_CCD_CRC2,                            // CCD�ļ�CRC
    EN_DC_DEV2_END,
    EN_DC_DEV3_STR=EN_DC_DEV2_END,
	EN_DC_T3=EN_DC_DEV3_STR,                   // �¶�3
	EN_DC_V11,                                 // �ڲ���ѹ11
    EN_DC_DEV3_END,
    EN_DC_DEV_END=EN_DC_DEV3_END,
//  �忨1�⹦��
    EN_DC_OPT1_STR=EN_DC_DEV_END,              // �忨1��ʼ
    EN_DC_OPT1_1_STR=EN_DC_OPT1_STR,           // �忨1-1��ʼ
    EN_DC_OPT11_RX=EN_DC_OPT1_1_STR,           // ���11���չ���
    EN_DC_OPT11_TX,                            // ���11���͹���
    EN_DC_OPT11_T,                             // ���11�¶�
    EN_DC_OPT11_V,                             // ���11��ѹ
    EN_DC_OPT12_RX,                            // ���12���չ���
    EN_DC_OPT12_TX,                            // ���12���͹���
    EN_DC_OPT12_T,                             // ���12�¶�
    EN_DC_OPT12_V,                             // ���12��ѹ
    EN_DC_OPT13_RX,                            // ���13���չ���
    EN_DC_OPT13_TX,                            // ���13���͹���
    EN_DC_OPT13_T,                             // ���13�¶�
    EN_DC_OPT13_V,                             // ���13��ѹ
    EN_DC_OPT14_RX,                            // ���14���չ���
    EN_DC_OPT14_TX,                            // ���14���͹���
    EN_DC_OPT14_T,                             // ���14�¶�
    EN_DC_OPT14_V,                             // ���14��ѹ
    EN_DC_OPT15_RX,                            // ���15���չ���
    EN_DC_OPT15_TX,                            // ���15���͹���
    EN_DC_OPT15_T,                             // ���15�¶�
    EN_DC_OPT15_V,                             // ���15��ѹ
    EN_DC_OPT16_RX,                            // ���16���չ���
    EN_DC_OPT16_TX,                            // ���16���͹���
    EN_DC_OPT16_T,                             // ���16�¶�
    EN_DC_OPT16_V,                             // ���16��ѹ
    EN_DC_OPT1T_RX,
    EN_DC_OPT1T_TX,
    EN_DC_OPT1T_T,
    EN_DC_OPT1T_V,
    EN_DC_OPT1_1_END,                          // �忨1-1����
    //����⹦��
    EN_DC_OPT1_2_STR=EN_DC_OPT1_1_END,         // �忨1-2��ʼ
    EN_DC_OPT17_RX=EN_DC_OPT1_2_STR,           // ���17���չ���
    EN_DC_OPT17_TX,                            // ���17���͹���
    EN_DC_OPT17_T,                             // ���17�¶�
    EN_DC_OPT17_V,                             // ���17��ѹ
    EN_DC_OPT18_RX,                            // ���18���չ���
    EN_DC_OPT18_TX,                            // ���18���͹���
    EN_DC_OPT18_T,                             // ���18�¶�
    EN_DC_OPT18_V,                             // ���18��ѹ
    EN_DC_OPT19_RX,                            // ���19���չ���
    EN_DC_OPT19_TX,                            // ���19���͹���
    EN_DC_OPT19_T,                             // ���19�¶�
    EN_DC_OPT19_V,                             // ���19��ѹ
    EN_DC_OPT110_RX,                           // ���110���չ���
    EN_DC_OPT110_TX,                           // ���110���͹���
    EN_DC_OPT110_T,                            // ���110�¶�
    EN_DC_OPT110_V,                            // ���110��ѹ
    EN_DC_OPT111_RX,                           // ���111���չ���
    EN_DC_OPT111_TX,                           // ���111���͹���
    EN_DC_OPT111_T,                            // ���111�¶�
    EN_DC_OPT111_V,                            // ���111��ѹ
    EN_DC_OPT112_RX,                           // ���112���չ���
    EN_DC_OPT112_TX,                           // ���112���͹���
    EN_DC_OPT112_T,                            // ���112�¶�
    EN_DC_OPT112_V,                            // ���112��ѹ
    EN_DC_OPT113_RX,                           // ���113���չ���
    EN_DC_OPT113_TX,                           // ���113���͹���
    EN_DC_OPT113_T,                            // ���113�¶�
    EN_DC_OPT113_V,                            // ���113��ѹ
    EN_DC_OPT1_2_END,                          // �忨1-2����
    EN_DC_OPT1_END=EN_DC_OPT1_2_END,           // �忨1����
//	�忨2�⹦��
    EN_DC_OPT2_STR=EN_DC_OPT1_END,             // �忨2��ʼ
    EN_DC_OPT21_RX=EN_DC_OPT2_STR,             // ���21���չ���
    EN_DC_OPT21_TX,                            // ���21���͹���
    EN_DC_OPT21_T,                             // ���21�¶�
    EN_DC_OPT21_V,                             // ���21��ѹ
    EN_DC_OPT22_RX,                            // ���22���չ���
    EN_DC_OPT22_TX,                            // ���22���͹���
    EN_DC_OPT22_T,                             // ���22�¶�
    EN_DC_OPT22_V,                             // ���22��ѹ
    EN_DC_OPT23_RX,                            // ���23���չ���
    EN_DC_OPT23_TX,                            // ���23���͹���
    EN_DC_OPT23_T,                             // ���23�¶�
    EN_DC_OPT23_V,                             // ���23��ѹ
    EN_DC_OPT24_RX,                            // ���24���չ���
    EN_DC_OPT24_TX,                            // ���24���͹���
    EN_DC_OPT24_T,                             // ���24�¶�
    EN_DC_OPT24_V,                             // ���24��ѹ
    EN_DC_OPT25_RX,                            // ���25���չ���
    EN_DC_OPT25_TX,                            // ���25���͹���
    EN_DC_OPT25_T,                             // ���25�¶�
    EN_DC_OPT25_V,                             // ���25��ѹ
    EN_DC_OPT26_RX,                            // ���26���չ���
    EN_DC_OPT26_TX,                            // ���26���͹���
    EN_DC_OPT26_T,                             // ���26�¶�
    EN_DC_OPT26_V,                             // ���26��ѹ
    EN_DC_OPT27_RX,                            // ���27���չ���
    EN_DC_OPT27_TX,                            // ���27���͹���
    EN_DC_OPT27_T,                             // ���27�¶�
    EN_DC_OPT27_V,                             // ���27��ѹ
    EN_DC_OPT2_END,                            // �忨2����
// �忨4�⹦��
    EN_DC_OPT3_STR=EN_DC_OPT2_END,             // �忨3��ʼ
    EN_DC_OPT3_END=EN_DC_OPT3_STR,             // �忨3����
//  �忨4�⹦��
    EN_DC_OPT4_STR=EN_DC_OPT3_END,             // �忨4��ʼ
    EN_DC_OPT4_END=EN_DC_OPT4_STR,             // �忨4����
    EN_DC_END=EN_DC_OPT4_END
};
/*================================================================================*/
//DC��ذ忨ö��
/*================================================================================*/
enum _BOARD_DC_TYPE_
{
    EN_BOARD_DC_STR=0,
    EN_BOARD_DC_SAM=EN_BOARD_DC_STR,
    EN_BOARD_DC_DEV,
    EN_BOARD_DC_OPT_STR,
    EN_BOARD_DC_OPT1_1=EN_BOARD_DC_OPT_STR,
    EN_BOARD_DC_OPT1_2,
    EN_BOARD_DC_OPT2,
    EN_BOARD_DC_OPT_END,
    EN_BOARD_DC_END=EN_BOARD_DC_OPT_END
};

/*================================================================================*/
// ������ṹ��
/*================================================================================*/
typedef struct
{
	WORD            wIndex;                         // ֱ����ö�ٺ�
	WORD            wType;                          // ֱ��������
	WORD            wParaIndex1;                    // ֱ�����ݲ���1
	WORD            wParaIndex2;                    // ֱ�����ݲ���2
	WORD            wCfg;                           // ֱ��������������
	INT8S           byName[CN_LEN_NAME];            // ֱ������
	INT8S           byPinName[CN_LEN_NAME];         // ֱ���̵�ַ
} tagDCTab;
/*================================================================================*/
// �忨���ñ�ṹ��
/*================================================================================*/
typedef struct
{
	WORD            wIndex;                         // �忨ö�ٺ�
	WORD            wIndexStr;                      // �����ź�Դ��ʼö��
	WORD            wIndexEnd;                      // �����ź�Դ����ö��
	WORD            wSrcIndexNum;                   // �����źŸ���
	WORD            wAddrBoard;                     // �忨��ַ
	WORD            wAddrFrame;                     // ����֡����
	INT8S           byName[CN_LEN_NAME];            // �忨����
	INT8S           byPinName[CN_LEN_NAME];         // �忨�̵�ַ
} tagBoardDCTab;

/*================================================================================*/
// �궨��
/*================================================================================*/
#define CN_NUM_DC          (EN_DC_END)                          // ϵͳȫ��ģ�����ɼ�ԭʼֵͨ����
#define CN_NUM_DC_SAM      (EN_DC_SAM_END-EN_DC_SAM_STR)        // ֱ������������
#define CN_NUM_DC_DEV      (EN_DC_DEV_END-EN_DC_DEV_STR)        // ���߼������
#define CN_NUM_DC_DEV_CPU1 (EN_DC_DEV1_END-EN_DC_DEV1_STR)      // ���߼������CPU1
#define CN_NUM_DC_DEV_CPU2 (EN_DC_DEV2_END-EN_DC_DEV2_STR)      // ���߼������CPU2
#define CN_NUM_DC_OPT1     (EN_DC_OPT1_END-EN_DC_OPT1_STR)      // �忨1�⹦��
#define CN_NUM_DC_OPT1_1   (EN_DC_OPT1_1_END-EN_DC_OPT1_1_STR)  // �忨1 CPU��⹦��
#define CN_NUM_DC_OPT1_2   (EN_DC_OPT1_2_END-EN_DC_OPT1_2_STR)  // �忨1 ���⹦��
#define CN_NUM_DC_OPT2     (EN_DC_OPT2_END-EN_DC_OPT2_STR)      // �忨2�⹦��
#define CN_NUM_BOARD_DC    (EN_BOARD_DC_END)                    // ֱ����ذ忨����
#define CN_DC_DSP_SAM      (3)                                  // ֱ��ֱ����ʾ���ݱ���
#define CN_DC_DIV_SAM      (3)                                  // ֱ��ֱ���ɼ����ݱ���
#define CN_DC_DSP_DEV      (3)                              // װ��ֱ����ʾ���ݱ���
#define CN_DC_DIV_DEV      (3)                              // װ��ֱ���ɼ����ݱ���
#if(CN_DEV_CPU1)
#define CN_DC_INDEX_T       (EN_DC_T1)                      // ֱ��ֱ����ʾ���ݱ���
#define CN_DC_INDEX_V       (EN_DC_V1)                      // ֱ��ֱ���ɼ����ݱ���
#define CN_DC_INDEX_CRC     (EN_DC_CCD_CRC)                 // ֱ��ֱ���ɼ����ݱ���
#else
#define CN_DC_INDEX_T       (EN_DC_T2)                      // ֱ��ֱ����ʾ���ݱ���
#define CN_DC_INDEX_V       (EN_DC_V6)                      // ֱ��ֱ���ɼ����ݱ���
#define CN_DC_INDEX_CRC     (EN_DC_CCD_CRC2)                // ֱ��ֱ���ɼ����ݱ���
#endif
/*================================================================================*/
// ����������
/*================================================================================*/
extern const tagDCTab       g_tDCTab[];
extern const DWORD          g_NUM_DC;
extern const tagBoardDCTab  g_tBoardDCTab[];
extern const DWORD          g_NUM_BOARD_DC;

/*================================================================================*/
#endif /* _CONST_SAM_H_ */
