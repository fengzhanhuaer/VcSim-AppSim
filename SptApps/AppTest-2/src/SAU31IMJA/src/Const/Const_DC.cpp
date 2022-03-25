#include "Const_Pub.h"
/*================================================================================*/
/* ֱ����������*/
/*================================================================================
	WORD			wIndex; 						// ֱ����ö�ٺ�
	WORD			wType;							// ֱ��������
	WORD			wParaIndex1;					// ֱ�����ݲ���1
	WORD			wParaIndex2;					// ֱ�����ݲ���2
	WORD			wCfg;							// ֱ��������������
	INT8S			byName[CN_LEN_NAME]; 			// ֱ������
	INT8S			byPinName[CN_LEN_NAME];			// ֱ���̵�ַ
*================================================================================*/
const tagDCTab g_tDCTab[ ] =
{
	{ EN_DC_SAM1          ,  EN_CTYPE_DC_ZL1,    EN_PARA_DC1_STR, EN_PARA_DC_TB,   0,  "ֱ������1",            "DC_SAM1"},
	{ EN_DC_SAM2          ,  EN_CTYPE_DC_ZL2,    EN_PARA_DC2_STR, EN_PARA_DC_TB,   0,  "ֱ������2",            "DC_SAM2"},
#if(!CN_FUN_DBUG1)
	{ EN_DC_SAM3          ,  EN_CTYPE_DC_ZL3,    EN_PARA_DC3_STR, EN_PARA_DC_TB,   0,  "ֱ������3",            "DC_SAM3"},
	{ EN_DC_SAM4          ,  EN_CTYPE_DC_ZL4,    EN_PARA_DC4_STR, EN_PARA_DC_TB,   0,  "ֱ������4",            "DC_SAM4"},
	{ EN_DC_SAM5          ,  EN_CTYPE_DC_ZL5,    EN_PARA_DC5_STR, EN_PARA_DC_TB,   0,  "ֱ������5",            "DC_SAM5"},
	{ EN_DC_SAM6          ,  EN_CTYPE_DC_ZL6,    EN_PARA_DC6_STR, EN_PARA_DC_TB,   0,  "ֱ������6",            "DC_SAM6"},
	{ EN_DC_SAM7          ,  EN_CTYPE_DC_ZL7,    EN_PARA_DC7_STR, EN_PARA_DC_TB,   0,  "ֱ������7",            "DC_SAM7"},
#endif
	{ EN_DC_T1            ,  EN_CTYPE_DC_T,      CN_NULL_PINNO,   EN_PARA_T_TB,    0,  "װ���ڲ��¶�1X",          "DC_T1"},
	{ EN_DC_V1            ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "װ���ڲ�������ѹ1X-1",        "DC_V1"},
	{ EN_DC_V2            ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "װ���ڲ�������ѹ1X-2",        "DC_V2"},
	{ EN_DC_V3            ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "װ���ڲ�������ѹ1X-3",        "DC_V3"},
	{ EN_DC_V4            ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "װ���ڲ�������ѹ1X-4",        "DC_V4"},
	{ EN_DC_V5            ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "װ���ڲ�������ѹ1X-5",        "DC_V5"},
	{ EN_DC_CCD_CRC       ,  EN_CTYPE_DC_H,      CN_NULL_PINNO,   CN_NULL_PINNO,   0,  "װ�������ļ���CRC 1X",        "DC_CCD_CRC"},

	{ EN_DC_T2            ,  EN_CTYPE_DC_T,      CN_NULL_PINNO,   EN_PARA_T_TB,    0,  "װ���ڲ��¶�2X",            "DC_T2"},
	{ EN_DC_V6            ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "װ���ڲ�������ѹ2X-1",        "DC_V6"},
	{ EN_DC_V7            ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "װ���ڲ�������ѹ2X-2",        "DC_V7"},
	{ EN_DC_V8            ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "װ���ڲ�������ѹ2X-3",        "DC_V8"},
	{ EN_DC_V9            ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "װ���ڲ�������ѹ2X-4",        "DC_V9"},
	{ EN_DC_V10           ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "װ���ڲ�������ѹ2X-5",       "DC_V10"},
	{ EN_DC_CCD_CRC2      ,  EN_CTYPE_DC_H,      CN_NULL_PINNO,   CN_NULL_PINNO,   0,  "װ�������ļ���CRC 2X",       "DC_CCD_CRC2"},

	{ EN_DC_T3            ,  EN_CTYPE_DC_T,      CN_NULL_PINNO,   EN_PARA_T_TB,    0,  "װ���ڲ��¶�5X",            "DC_T3"},
	{ EN_DC_V11           ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "װ���ڲ�������ѹ5X",          "DC_V11"},

	{ EN_DC_OPT11_RX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-1���չ���",   "DC_OPT11_RX"},
	{ EN_DC_OPT11_TX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-1���͹���",   "DC_OPT11_TX"},
	{ EN_DC_OPT11_T       ,  EN_CTYPE_DC_OPTT,   CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���1X-1�¶�",        "DC_OPT11_T"},
	{ EN_DC_OPT11_V       ,  EN_CTYPE_DC_OPTV,   CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���1X-1��ѹ",        "DC_OPT11_V"},
	{ EN_DC_OPT12_RX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-2���չ���",   "DC_OPT12_RX"},
	{ EN_DC_OPT12_TX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-2���͹���",   "DC_OPT12_TX"},
	{ EN_DC_OPT12_T       ,  EN_CTYPE_DC_OPTT,   CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���1X-2�¶�",        "DC_OPT12_T"},
	{ EN_DC_OPT12_V       ,  EN_CTYPE_DC_OPTV,   CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���1X-2��ѹ",        "DC_OPT12_V"},
	{ EN_DC_OPT13_RX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-3���չ���",   "DC_OPT13_RX"},
	{ EN_DC_OPT13_TX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-3���͹���",   "DC_OPT13_TX"},
	{ EN_DC_OPT13_T       ,  EN_CTYPE_DC_OPTT,   CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���1X-3�¶�",        "DC_OPT13_T"},
	{ EN_DC_OPT13_V       ,  EN_CTYPE_DC_OPTV,   CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���1X-3��ѹ",        "DC_OPT13_V"},
	{ EN_DC_OPT14_RX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-4���չ���",   "DC_OPT14_RX"},
	{ EN_DC_OPT14_TX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-4���͹���",   "DC_OPT14_TX"},
	{ EN_DC_OPT14_T       ,  EN_CTYPE_DC_OPTT,   CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���1X-4�¶�",        "DC_OPT14_T"},
	{ EN_DC_OPT14_V       ,  EN_CTYPE_DC_OPTV,   CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���1X-4��ѹ",        "DC_OPT14_V"},
	{ EN_DC_OPT15_RX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-5���չ���",   "DC_OPT15_RX"},
	{ EN_DC_OPT15_TX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-5���͹���",   "DC_OPT15_TX"},
	{ EN_DC_OPT15_T       ,  EN_CTYPE_DC_OPTT,   CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���1X-5�¶�",        "DC_OPT15_T"},
	{ EN_DC_OPT15_V       ,  EN_CTYPE_DC_OPTV,   CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���1X-5��ѹ",        "DC_OPT15_V"},
	{ EN_DC_OPT16_RX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-6���չ���",   "DC_OPT16_RX"},
	{ EN_DC_OPT16_TX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-6���͹���",   "DC_OPT16_TX"},
	{ EN_DC_OPT16_T       ,  EN_CTYPE_DC_OPTT,   CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���1X-6�¶�",        "DC_OPT16_T"},
	{ EN_DC_OPT16_V       ,  EN_CTYPE_DC_OPTV,   CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���1X-6��ѹ",        "DC_OPT16_V"},
	{ EN_DC_OPT1T_RX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-B����չ���",   "DC_OPT1T_RX"},
	{ EN_DC_OPT1T_TX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-PPS���͹���",   "DC_OPT1T_TX"},
	{ EN_DC_OPT1T_T       ,  EN_CTYPE_DC_OPTT,   CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���1X-��ʱ�¶�",      "DC_OPT1T_T"},
	{ EN_DC_OPT1T_V       ,  EN_CTYPE_DC_OPTV,   CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���1X-��ʱ��ѹ",      "DC_OPT1T_V"},
	
	{ EN_DC_OPT17_RX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-7���չ���",   "DC_OPT17_RX"},
	{ EN_DC_OPT17_TX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-7���͹���",   "DC_OPT17_TX"},
	{ EN_DC_OPT17_T       ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���1X-7�¶�",        "DC_OPT17_T"},
	{ EN_DC_OPT17_V       ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���1X-7��ѹ",        "DC_OPT17_V"},
	{ EN_DC_OPT18_RX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-8���չ���",   "DC_OPT18_RX"},
	{ EN_DC_OPT18_TX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-8���͹���",   "DC_OPT18_TX"},
	{ EN_DC_OPT18_T       ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���1X-8�¶�",        "DC_OPT18_T"},
	{ EN_DC_OPT18_V       ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���1X-8��ѹ",        "DC_OPT18_V"},
	{ EN_DC_OPT19_RX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-9���չ���",   "DC_OPT19_RX"},
	{ EN_DC_OPT19_TX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-9���͹���",   "DC_OPT19_TX"},
	{ EN_DC_OPT19_T       ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���1X-9�¶�",        "DC_OPT19_T"},
	{ EN_DC_OPT19_V       ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���1X-9��ѹ",        "DC_OPT19_V"},
	{ EN_DC_OPT110_RX     ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-10���չ���",   "DC_OPT110_RX"},
	{ EN_DC_OPT110_TX     ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-10���͹���",   "DC_OPT110_TX"},
	{ EN_DC_OPT110_T      ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���1X-10�¶�",        "DC_OPT110_T"},
	{ EN_DC_OPT110_V      ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���1X-10��ѹ",        "DC_OPT110_V"},
	{ EN_DC_OPT111_RX     ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-11���չ���",   "DC_OPT111_RX"},
	{ EN_DC_OPT111_TX     ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-11���͹���",   "DC_OPT111_TX"},
	{ EN_DC_OPT111_T      ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���1X-11�¶�",        "DC_OPT111_T"},
	{ EN_DC_OPT111_V      ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���1X-11��ѹ",        "DC_OPT111_V"},
	{ EN_DC_OPT112_RX     ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-12���չ���",   "DC_OPT112_RX"},
	{ EN_DC_OPT112_TX     ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-12���͹���",   "DC_OPT112_TX"},
	{ EN_DC_OPT112_T      ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���1X-12�¶�",        "DC_OPT112_T"},
	{ EN_DC_OPT112_V      ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���1X-12��ѹ",        "DC_OPT112_V"},
	{ EN_DC_OPT113_RX     ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-13���չ���",   "DC_OPT113_RX"},
	{ EN_DC_OPT113_TX     ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���1X-13���͹���",   "DC_OPT113_TX"},
	{ EN_DC_OPT113_T      ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���1X-13�¶�",        "DC_OPT113_T"},
	{ EN_DC_OPT113_V      ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���1X-13��ѹ",        "DC_OPT113_V"},

	{ EN_DC_OPT21_RX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���2X-1���չ���",   "DC_OPT21_RX"},
	{ EN_DC_OPT21_TX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���2X-1���͹���",   "DC_OPT21_TX"},
	{ EN_DC_OPT21_T       ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���2X-1�¶�",        "DC_OPT21_T"},
	{ EN_DC_OPT21_V       ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���2X-1��ѹ",        "DC_OPT21_V"},
	{ EN_DC_OPT22_RX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���2X-2���չ���",   "DC_OPT22_RX"},
	{ EN_DC_OPT22_TX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���2X-2���͹���",   "DC_OPT22_TX"},
	{ EN_DC_OPT22_T       ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���2X-2�¶�",        "DC_OPT22_T"},
	{ EN_DC_OPT22_V       ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���2X-2��ѹ",        "DC_OPT22_V"},
	{ EN_DC_OPT23_RX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���2X-3���չ���",   "DC_OPT23_RX"},
	{ EN_DC_OPT23_TX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���2X-3���͹���",   "DC_OPT23_TX"},
	{ EN_DC_OPT23_T       ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���2X-3�¶�",        "DC_OPT23_T"},
	{ EN_DC_OPT23_V       ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���2X-3��ѹ",        "DC_OPT23_V"},
	{ EN_DC_OPT24_RX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���2X-4���չ���",   "DC_OPT24_RX"},
	{ EN_DC_OPT24_TX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���2X-4���͹���",   "DC_OPT24_TX"},
	{ EN_DC_OPT24_T       ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���2X-4�¶�",        "DC_OPT24_T"},
	{ EN_DC_OPT24_V       ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���2X-4��ѹ",        "DC_OPT24_V"},
	{ EN_DC_OPT25_RX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���2X-5���չ���",   "DC_OPT25_RX"},
	{ EN_DC_OPT25_TX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���2X-5���͹���",   "DC_OPT25_TX"},
	{ EN_DC_OPT25_T       ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���2X-5�¶�",        "DC_OPT25_T"},
	{ EN_DC_OPT25_V       ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���2X-5��ѹ",        "DC_OPT25_V"},
	{ EN_DC_OPT26_RX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���2X-6���չ���",   "DC_OPT26_RX"},
	{ EN_DC_OPT26_TX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���2X-6���͹���",   "DC_OPT26_TX"},
	{ EN_DC_OPT26_T       ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���2X-6�¶�",        "DC_OPT26_T"},
	{ EN_DC_OPT26_V       ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���2X-6��ѹ",        "DC_OPT26_V"},
	{ EN_DC_OPT27_RX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���2X-7���չ���",   "DC_OPT27_RX"},
	{ EN_DC_OPT27_TX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "���2X-7���͹���",   "DC_OPT27_TX"},
	{ EN_DC_OPT27_T       ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "���2X-7�¶�",        "DC_OPT27_T"},
	{ EN_DC_OPT27_V       ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "���2X-7��ѹ",        "DC_OPT27_V"},
};
const DWORD g_NUM_DC = sizeof(g_tDCTab)/sizeof(tagDCTab);

const tagBoardDCTab    g_tBoardDCTab[]=
{
    { EN_BOARD_DC_SAM ,    EN_DC_SAM_STR ,   EN_DC_SAM_END ,    CN_NUM_DC_SAM ,    0            ,   0            ,  "DC_SAM" ,   "AppDCGroup1"},
    { EN_BOARD_DC_DEV ,    EN_DC_DEV_STR ,   EN_DC_DEV_END ,    CN_NUM_DC_DEV ,    CN_NULL_PINNO,   CN_NULL_PINNO,  "DC_DEV" ,   "AppDCGroup2"},
    { EN_BOARD_DC_OPT1_1,  EN_DC_OPT1_1_STR, EN_DC_OPT1_1_END,  CN_NUM_DC_OPT1_1,  0            ,   CN_NULL_PINNO,  "DC_OPT11",  "AppDCGroup3"},
    { EN_BOARD_DC_OPT1_2,  EN_DC_OPT1_2_STR, EN_DC_OPT1_2_END,  CN_NUM_DC_OPT1_2,  2            ,   CN_NULL_PINNO,  "DC_OPT12",  "AppDCGroup4"},
    { EN_BOARD_DC_OPT2,    EN_DC_OPT2_STR,   EN_DC_OPT2_END,    CN_NUM_DC_OPT2,    1            ,   CN_NULL_PINNO,  "DC_OPT2",   "AppDCGroup5"},

};
const DWORD g_NUM_BOARD_DC= sizeof(g_tBoardDCTab) / sizeof(tagBoardDCTab);

