#include "Const_Pub.h"
/*================================================================================*/
/* 直流量常量表*/
/*================================================================================
	WORD			wIndex; 						// 直流量枚举号
	WORD			wType;							// 直流量类型
	WORD			wParaIndex1;					// 直流数据参数1
	WORD			wParaIndex2;					// 直流数据参数2
	WORD			wCfg;							// 直流数据其他属性
	INT8S			byName[CN_LEN_NAME]; 			// 直流名称
	INT8S			byPinName[CN_LEN_NAME];			// 直流短地址
*================================================================================*/
const tagDCTab g_tDCTab[ ] =
{
	{ EN_DC_SAM1          ,  EN_CTYPE_DC_ZL1,    EN_PARA_DC1_STR, EN_PARA_DC_TB,   0,  "直流测量1",            "DC_SAM1"},
	{ EN_DC_SAM2          ,  EN_CTYPE_DC_ZL2,    EN_PARA_DC2_STR, EN_PARA_DC_TB,   0,  "直流测量2",            "DC_SAM2"},
#if(!CN_FUN_DBUG1)
	{ EN_DC_SAM3          ,  EN_CTYPE_DC_ZL3,    EN_PARA_DC3_STR, EN_PARA_DC_TB,   0,  "直流测量3",            "DC_SAM3"},
	{ EN_DC_SAM4          ,  EN_CTYPE_DC_ZL4,    EN_PARA_DC4_STR, EN_PARA_DC_TB,   0,  "直流测量4",            "DC_SAM4"},
	{ EN_DC_SAM5          ,  EN_CTYPE_DC_ZL5,    EN_PARA_DC5_STR, EN_PARA_DC_TB,   0,  "直流测量5",            "DC_SAM5"},
	{ EN_DC_SAM6          ,  EN_CTYPE_DC_ZL6,    EN_PARA_DC6_STR, EN_PARA_DC_TB,   0,  "直流测量6",            "DC_SAM6"},
	{ EN_DC_SAM7          ,  EN_CTYPE_DC_ZL7,    EN_PARA_DC7_STR, EN_PARA_DC_TB,   0,  "直流测量7",            "DC_SAM7"},
#endif
	{ EN_DC_T1            ,  EN_CTYPE_DC_T,      CN_NULL_PINNO,   EN_PARA_T_TB,    0,  "装置内部温度1X",          "DC_T1"},
	{ EN_DC_V1            ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "装置内部工作电压1X-1",        "DC_V1"},
	{ EN_DC_V2            ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "装置内部工作电压1X-2",        "DC_V2"},
	{ EN_DC_V3            ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "装置内部工作电压1X-3",        "DC_V3"},
	{ EN_DC_V4            ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "装置内部工作电压1X-4",        "DC_V4"},
	{ EN_DC_V5            ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "装置内部工作电压1X-5",        "DC_V5"},
	{ EN_DC_CCD_CRC       ,  EN_CTYPE_DC_H,      CN_NULL_PINNO,   CN_NULL_PINNO,   0,  "装置配置文件的CRC 1X",        "DC_CCD_CRC"},

	{ EN_DC_T2            ,  EN_CTYPE_DC_T,      CN_NULL_PINNO,   EN_PARA_T_TB,    0,  "装置内部温度2X",            "DC_T2"},
	{ EN_DC_V6            ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "装置内部工作电压2X-1",        "DC_V6"},
	{ EN_DC_V7            ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "装置内部工作电压2X-2",        "DC_V7"},
	{ EN_DC_V8            ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "装置内部工作电压2X-3",        "DC_V8"},
	{ EN_DC_V9            ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "装置内部工作电压2X-4",        "DC_V9"},
	{ EN_DC_V10           ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "装置内部工作电压2X-5",       "DC_V10"},
	{ EN_DC_CCD_CRC2      ,  EN_CTYPE_DC_H,      CN_NULL_PINNO,   CN_NULL_PINNO,   0,  "装置配置文件的CRC 2X",       "DC_CCD_CRC2"},

	{ EN_DC_T3            ,  EN_CTYPE_DC_T,      CN_NULL_PINNO,   EN_PARA_T_TB,    0,  "装置内部温度5X",            "DC_T3"},
	{ EN_DC_V11           ,  EN_CTYPE_DC_V,      CN_NULL_PINNO,   EN_PARA_V_TB,    0,  "装置内部工作电压5X",          "DC_V11"},

	{ EN_DC_OPT11_RX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-1接收功率",   "DC_OPT11_RX"},
	{ EN_DC_OPT11_TX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-1发送功率",   "DC_OPT11_TX"},
	{ EN_DC_OPT11_T       ,  EN_CTYPE_DC_OPTT,   CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口1X-1温度",        "DC_OPT11_T"},
	{ EN_DC_OPT11_V       ,  EN_CTYPE_DC_OPTV,   CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口1X-1电压",        "DC_OPT11_V"},
	{ EN_DC_OPT12_RX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-2接收功率",   "DC_OPT12_RX"},
	{ EN_DC_OPT12_TX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-2发送功率",   "DC_OPT12_TX"},
	{ EN_DC_OPT12_T       ,  EN_CTYPE_DC_OPTT,   CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口1X-2温度",        "DC_OPT12_T"},
	{ EN_DC_OPT12_V       ,  EN_CTYPE_DC_OPTV,   CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口1X-2电压",        "DC_OPT12_V"},
	{ EN_DC_OPT13_RX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-3接收功率",   "DC_OPT13_RX"},
	{ EN_DC_OPT13_TX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-3发送功率",   "DC_OPT13_TX"},
	{ EN_DC_OPT13_T       ,  EN_CTYPE_DC_OPTT,   CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口1X-3温度",        "DC_OPT13_T"},
	{ EN_DC_OPT13_V       ,  EN_CTYPE_DC_OPTV,   CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口1X-3电压",        "DC_OPT13_V"},
	{ EN_DC_OPT14_RX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-4接收功率",   "DC_OPT14_RX"},
	{ EN_DC_OPT14_TX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-4发送功率",   "DC_OPT14_TX"},
	{ EN_DC_OPT14_T       ,  EN_CTYPE_DC_OPTT,   CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口1X-4温度",        "DC_OPT14_T"},
	{ EN_DC_OPT14_V       ,  EN_CTYPE_DC_OPTV,   CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口1X-4电压",        "DC_OPT14_V"},
	{ EN_DC_OPT15_RX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-5接收功率",   "DC_OPT15_RX"},
	{ EN_DC_OPT15_TX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-5发送功率",   "DC_OPT15_TX"},
	{ EN_DC_OPT15_T       ,  EN_CTYPE_DC_OPTT,   CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口1X-5温度",        "DC_OPT15_T"},
	{ EN_DC_OPT15_V       ,  EN_CTYPE_DC_OPTV,   CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口1X-5电压",        "DC_OPT15_V"},
	{ EN_DC_OPT16_RX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-6接收功率",   "DC_OPT16_RX"},
	{ EN_DC_OPT16_TX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-6发送功率",   "DC_OPT16_TX"},
	{ EN_DC_OPT16_T       ,  EN_CTYPE_DC_OPTT,   CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口1X-6温度",        "DC_OPT16_T"},
	{ EN_DC_OPT16_V       ,  EN_CTYPE_DC_OPTV,   CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口1X-6电压",        "DC_OPT16_V"},
	{ EN_DC_OPT1T_RX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-B码接收功率",   "DC_OPT1T_RX"},
	{ EN_DC_OPT1T_TX      ,  EN_CTYPE_DC_DBM,    CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-PPS发送功率",   "DC_OPT1T_TX"},
	{ EN_DC_OPT1T_T       ,  EN_CTYPE_DC_OPTT,   CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口1X-对时温度",      "DC_OPT1T_T"},
	{ EN_DC_OPT1T_V       ,  EN_CTYPE_DC_OPTV,   CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口1X-对时电压",      "DC_OPT1T_V"},
	
	{ EN_DC_OPT17_RX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-7接收功率",   "DC_OPT17_RX"},
	{ EN_DC_OPT17_TX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-7发送功率",   "DC_OPT17_TX"},
	{ EN_DC_OPT17_T       ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口1X-7温度",        "DC_OPT17_T"},
	{ EN_DC_OPT17_V       ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口1X-7电压",        "DC_OPT17_V"},
	{ EN_DC_OPT18_RX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-8接收功率",   "DC_OPT18_RX"},
	{ EN_DC_OPT18_TX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-8发送功率",   "DC_OPT18_TX"},
	{ EN_DC_OPT18_T       ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口1X-8温度",        "DC_OPT18_T"},
	{ EN_DC_OPT18_V       ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口1X-8电压",        "DC_OPT18_V"},
	{ EN_DC_OPT19_RX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-9接收功率",   "DC_OPT19_RX"},
	{ EN_DC_OPT19_TX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-9发送功率",   "DC_OPT19_TX"},
	{ EN_DC_OPT19_T       ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口1X-9温度",        "DC_OPT19_T"},
	{ EN_DC_OPT19_V       ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口1X-9电压",        "DC_OPT19_V"},
	{ EN_DC_OPT110_RX     ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-10接收功率",   "DC_OPT110_RX"},
	{ EN_DC_OPT110_TX     ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-10发送功率",   "DC_OPT110_TX"},
	{ EN_DC_OPT110_T      ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口1X-10温度",        "DC_OPT110_T"},
	{ EN_DC_OPT110_V      ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口1X-10电压",        "DC_OPT110_V"},
	{ EN_DC_OPT111_RX     ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-11接收功率",   "DC_OPT111_RX"},
	{ EN_DC_OPT111_TX     ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-11发送功率",   "DC_OPT111_TX"},
	{ EN_DC_OPT111_T      ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口1X-11温度",        "DC_OPT111_T"},
	{ EN_DC_OPT111_V      ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口1X-11电压",        "DC_OPT111_V"},
	{ EN_DC_OPT112_RX     ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-12接收功率",   "DC_OPT112_RX"},
	{ EN_DC_OPT112_TX     ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-12发送功率",   "DC_OPT112_TX"},
	{ EN_DC_OPT112_T      ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口1X-12温度",        "DC_OPT112_T"},
	{ EN_DC_OPT112_V      ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口1X-12电压",        "DC_OPT112_V"},
	{ EN_DC_OPT113_RX     ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-13接收功率",   "DC_OPT113_RX"},
	{ EN_DC_OPT113_TX     ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口1X-13发送功率",   "DC_OPT113_TX"},
	{ EN_DC_OPT113_T      ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口1X-13温度",        "DC_OPT113_T"},
	{ EN_DC_OPT113_V      ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口1X-13电压",        "DC_OPT113_V"},

	{ EN_DC_OPT21_RX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口2X-1接收功率",   "DC_OPT21_RX"},
	{ EN_DC_OPT21_TX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口2X-1发送功率",   "DC_OPT21_TX"},
	{ EN_DC_OPT21_T       ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口2X-1温度",        "DC_OPT21_T"},
	{ EN_DC_OPT21_V       ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口2X-1电压",        "DC_OPT21_V"},
	{ EN_DC_OPT22_RX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口2X-2接收功率",   "DC_OPT22_RX"},
	{ EN_DC_OPT22_TX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口2X-2发送功率",   "DC_OPT22_TX"},
	{ EN_DC_OPT22_T       ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口2X-2温度",        "DC_OPT22_T"},
	{ EN_DC_OPT22_V       ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口2X-2电压",        "DC_OPT22_V"},
	{ EN_DC_OPT23_RX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口2X-3接收功率",   "DC_OPT23_RX"},
	{ EN_DC_OPT23_TX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口2X-3发送功率",   "DC_OPT23_TX"},
	{ EN_DC_OPT23_T       ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口2X-3温度",        "DC_OPT23_T"},
	{ EN_DC_OPT23_V       ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口2X-3电压",        "DC_OPT23_V"},
	{ EN_DC_OPT24_RX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口2X-4接收功率",   "DC_OPT24_RX"},
	{ EN_DC_OPT24_TX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口2X-4发送功率",   "DC_OPT24_TX"},
	{ EN_DC_OPT24_T       ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口2X-4温度",        "DC_OPT24_T"},
	{ EN_DC_OPT24_V       ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口2X-4电压",        "DC_OPT24_V"},
	{ EN_DC_OPT25_RX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口2X-5接收功率",   "DC_OPT25_RX"},
	{ EN_DC_OPT25_TX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口2X-5发送功率",   "DC_OPT25_TX"},
	{ EN_DC_OPT25_T       ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口2X-5温度",        "DC_OPT25_T"},
	{ EN_DC_OPT25_V       ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口2X-5电压",        "DC_OPT25_V"},
	{ EN_DC_OPT26_RX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口2X-6接收功率",   "DC_OPT26_RX"},
	{ EN_DC_OPT26_TX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口2X-6发送功率",   "DC_OPT26_TX"},
	{ EN_DC_OPT26_T       ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口2X-6温度",        "DC_OPT26_T"},
	{ EN_DC_OPT26_V       ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口2X-6电压",        "DC_OPT26_V"},
	{ EN_DC_OPT27_RX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口2X-7接收功率",   "DC_OPT27_RX"},
	{ EN_DC_OPT27_TX      ,  EN_CTYPE_DC_DBM,   CN_NULL_PINNO,   EN_PARA_RT_TB,   0,  "光口2X-7发送功率",   "DC_OPT27_TX"},
	{ EN_DC_OPT27_T       ,  EN_CTYPE_DC_OPTT,  CN_NULL_PINNO,   EN_PARA_T_TB ,   0,  "光口2X-7温度",        "DC_OPT27_T"},
	{ EN_DC_OPT27_V       ,  EN_CTYPE_DC_OPTV,  CN_NULL_PINNO,   EN_PARA_V_TB ,   0,  "光口2X-7电压",        "DC_OPT27_V"},
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


