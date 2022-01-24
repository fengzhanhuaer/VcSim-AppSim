#ifndef _CONST_DC_H_
#define _CONST_DC_H_

#include "IES_IMtypes.h"
/*================================================================================*/
// 信号枚举
/*================================================================================*/
enum _DC_INDEX_TYPE_
{
//  直采模拟量通道
    EN_DC_SAM_STR=0,
    EN_DC_SAM1=EN_DC_SAM_STR,                  // 直采起始
    EN_DC_SAM2,                                // 直流采集2
#if(!CN_FUN_DBUG1)
    EN_DC_SAM3,                                // 直流采集3
    EN_DC_SAM4,                                // 直流采集4
    EN_DC_SAM5,                                // 直流采集5
    EN_DC_SAM6,                                // 直流采集6
    EN_DC_SAM7,                                // 直流采集7
#endif
    EN_DC_SAM_END,                             // 直采结束
//  在线监测数据
    EN_DC_DEV_STR=EN_DC_SAM_END,
    EN_DC_DEV1_STR=EN_DC_DEV_STR,
    EN_DC_T1=EN_DC_DEV1_STR,                   // 温度1
    EN_DC_V1,                                  // 内部电压1
    EN_DC_V2,                                  // 内部电压2
    EN_DC_V3,                                  // 内部电压3
    EN_DC_V4,                                  // 内部电压4
    EN_DC_V5,                                  // 内部电压5
    EN_DC_CCD_CRC,                             // CCD文件CRC
    EN_DC_DEV1_END,
    EN_DC_DEV2_STR=EN_DC_DEV1_END,
    EN_DC_T2=EN_DC_DEV2_STR,                   // 温度2
    EN_DC_V6,                                  // 内部电压6
    EN_DC_V7,                                  // 内部电压7
    EN_DC_V8,                                  // 内部电压8
    EN_DC_V9,                                  // 内部电压9
    EN_DC_V10,                                 // 内部电压10
    EN_DC_CCD_CRC2,                            // CCD文件CRC
    EN_DC_DEV2_END,
    EN_DC_DEV3_STR=EN_DC_DEV2_END,
	EN_DC_T3=EN_DC_DEV3_STR,                   // 温度3
	EN_DC_V11,                                 // 内部电压11
    EN_DC_DEV3_END,
    EN_DC_DEV_END=EN_DC_DEV3_END,
//  板卡1光功率
    EN_DC_OPT1_STR=EN_DC_DEV_END,              // 板卡1起始
    EN_DC_OPT1_1_STR=EN_DC_OPT1_STR,           // 板卡1-1起始
    EN_DC_OPT11_RX=EN_DC_OPT1_1_STR,           // 光口11接收功率
    EN_DC_OPT11_TX,                            // 光口11发送功率
    EN_DC_OPT11_T,                             // 光口11温度
    EN_DC_OPT11_V,                             // 光口11电压
    EN_DC_OPT12_RX,                            // 光口12接收功率
    EN_DC_OPT12_TX,                            // 光口12发送功率
    EN_DC_OPT12_T,                             // 光口12温度
    EN_DC_OPT12_V,                             // 光口12电压
    EN_DC_OPT13_RX,                            // 光口13接收功率
    EN_DC_OPT13_TX,                            // 光口13发送功率
    EN_DC_OPT13_T,                             // 光口13温度
    EN_DC_OPT13_V,                             // 光口13电压
    EN_DC_OPT14_RX,                            // 光口14接收功率
    EN_DC_OPT14_TX,                            // 光口14发送功率
    EN_DC_OPT14_T,                             // 光口14温度
    EN_DC_OPT14_V,                             // 光口14电压
    EN_DC_OPT15_RX,                            // 光口15接收功率
    EN_DC_OPT15_TX,                            // 光口15发送功率
    EN_DC_OPT15_T,                             // 光口15温度
    EN_DC_OPT15_V,                             // 光口15电压
    EN_DC_OPT16_RX,                            // 光口16接收功率
    EN_DC_OPT16_TX,                            // 光口16发送功率
    EN_DC_OPT16_T,                             // 光口16温度
    EN_DC_OPT16_V,                             // 光口16电压
    EN_DC_OPT1T_RX,
    EN_DC_OPT1T_TX,
    EN_DC_OPT1T_T,
    EN_DC_OPT1T_V,
    EN_DC_OPT1_1_END,                          // 板卡1-1结束
    //背板光功率
    EN_DC_OPT1_2_STR=EN_DC_OPT1_1_END,         // 板卡1-2起始
    EN_DC_OPT17_RX=EN_DC_OPT1_2_STR,           // 光口17接收功率
    EN_DC_OPT17_TX,                            // 光口17发送功率
    EN_DC_OPT17_T,                             // 光口17温度
    EN_DC_OPT17_V,                             // 光口17电压
    EN_DC_OPT18_RX,                            // 光口18接收功率
    EN_DC_OPT18_TX,                            // 光口18发送功率
    EN_DC_OPT18_T,                             // 光口18温度
    EN_DC_OPT18_V,                             // 光口18电压
    EN_DC_OPT19_RX,                            // 光口19接收功率
    EN_DC_OPT19_TX,                            // 光口19发送功率
    EN_DC_OPT19_T,                             // 光口19温度
    EN_DC_OPT19_V,                             // 光口19电压
    EN_DC_OPT110_RX,                           // 光口110接收功率
    EN_DC_OPT110_TX,                           // 光口110发送功率
    EN_DC_OPT110_T,                            // 光口110温度
    EN_DC_OPT110_V,                            // 光口110电压
    EN_DC_OPT111_RX,                           // 光口111接收功率
    EN_DC_OPT111_TX,                           // 光口111发送功率
    EN_DC_OPT111_T,                            // 光口111温度
    EN_DC_OPT111_V,                            // 光口111电压
    EN_DC_OPT112_RX,                           // 光口112接收功率
    EN_DC_OPT112_TX,                           // 光口112发送功率
    EN_DC_OPT112_T,                            // 光口112温度
    EN_DC_OPT112_V,                            // 光口112电压
    EN_DC_OPT113_RX,                           // 光口113接收功率
    EN_DC_OPT113_TX,                           // 光口113发送功率
    EN_DC_OPT113_T,                            // 光口113温度
    EN_DC_OPT113_V,                            // 光口113电压
    EN_DC_OPT1_2_END,                          // 板卡1-2结束
    EN_DC_OPT1_END=EN_DC_OPT1_2_END,           // 板卡1结束
//	板卡2光功率
    EN_DC_OPT2_STR=EN_DC_OPT1_END,             // 板卡2起始
    EN_DC_OPT21_RX=EN_DC_OPT2_STR,             // 光口21接收功率
    EN_DC_OPT21_TX,                            // 光口21发送功率
    EN_DC_OPT21_T,                             // 光口21温度
    EN_DC_OPT21_V,                             // 光口21电压
    EN_DC_OPT22_RX,                            // 光口22接收功率
    EN_DC_OPT22_TX,                            // 光口22发送功率
    EN_DC_OPT22_T,                             // 光口22温度
    EN_DC_OPT22_V,                             // 光口22电压
    EN_DC_OPT23_RX,                            // 光口23接收功率
    EN_DC_OPT23_TX,                            // 光口23发送功率
    EN_DC_OPT23_T,                             // 光口23温度
    EN_DC_OPT23_V,                             // 光口23电压
    EN_DC_OPT24_RX,                            // 光口24接收功率
    EN_DC_OPT24_TX,                            // 光口24发送功率
    EN_DC_OPT24_T,                             // 光口24温度
    EN_DC_OPT24_V,                             // 光口24电压
    EN_DC_OPT25_RX,                            // 光口25接收功率
    EN_DC_OPT25_TX,                            // 光口25发送功率
    EN_DC_OPT25_T,                             // 光口25温度
    EN_DC_OPT25_V,                             // 光口25电压
    EN_DC_OPT26_RX,                            // 光口26接收功率
    EN_DC_OPT26_TX,                            // 光口26发送功率
    EN_DC_OPT26_T,                             // 光口26温度
    EN_DC_OPT26_V,                             // 光口26电压
    EN_DC_OPT27_RX,                            // 光口27接收功率
    EN_DC_OPT27_TX,                            // 光口27发送功率
    EN_DC_OPT27_T,                             // 光口27温度
    EN_DC_OPT27_V,                             // 光口27电压
    EN_DC_OPT2_END,                            // 板卡2结束
// 板卡4光功率
    EN_DC_OPT3_STR=EN_DC_OPT2_END,             // 板卡3起始
    EN_DC_OPT3_END=EN_DC_OPT3_STR,             // 板卡3结束
//  板卡4光功率
    EN_DC_OPT4_STR=EN_DC_OPT3_END,             // 板卡4起始
    EN_DC_OPT4_END=EN_DC_OPT4_STR,             // 板卡4结束
    EN_DC_END=EN_DC_OPT4_END
};
/*================================================================================*/
//DC相关板卡枚举
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
// 常量表结构体
/*================================================================================*/
typedef struct
{
	WORD            wIndex;                         // 直流量枚举号
	WORD            wType;                          // 直流量类型
	WORD            wParaIndex1;                    // 直流数据参数1
	WORD            wParaIndex2;                    // 直流数据参数2
	WORD            wCfg;                           // 直流数据其他属性
	INT8S           byName[CN_LEN_NAME];            // 直流名称
	INT8S           byPinName[CN_LEN_NAME];         // 直流短地址
} tagDCTab;
/*================================================================================*/
// 板卡配置表结构体
/*================================================================================*/
typedef struct
{
	WORD            wIndex;                         // 板卡枚举号
	WORD            wIndexStr;                      // 关联信号源起始枚举
	WORD            wIndexEnd;                      // 关联信号源结束枚举
	WORD            wSrcIndexNum;                   // 关联信号个数
	WORD            wAddrBoard;                     // 板卡地址
	WORD            wAddrFrame;                     // 数据帧类型
	INT8S           byName[CN_LEN_NAME];            // 板卡名称
	INT8S           byPinName[CN_LEN_NAME];         // 板卡短地址
} tagBoardDCTab;

/*================================================================================*/
// 宏定义
/*================================================================================*/
#define CN_NUM_DC          (EN_DC_END)                          // 系统全部模拟量采集原始值通道数
#define CN_NUM_DC_SAM      (EN_DC_SAM_END-EN_DC_SAM_STR)        // 直流采样板数据
#define CN_NUM_DC_DEV      (EN_DC_DEV_END-EN_DC_DEV_STR)        // 在线监测数据
#define CN_NUM_DC_DEV_CPU1 (EN_DC_DEV1_END-EN_DC_DEV1_STR)      // 在线监测数据CPU1
#define CN_NUM_DC_DEV_CPU2 (EN_DC_DEV2_END-EN_DC_DEV2_STR)      // 在线监测数据CPU2
#define CN_NUM_DC_OPT1     (EN_DC_OPT1_END-EN_DC_OPT1_STR)      // 板卡1光功率
#define CN_NUM_DC_OPT1_1   (EN_DC_OPT1_1_END-EN_DC_OPT1_1_STR)  // 板卡1 CPU板光功率
#define CN_NUM_DC_OPT1_2   (EN_DC_OPT1_2_END-EN_DC_OPT1_2_STR)  // 板卡1 背光功率
#define CN_NUM_DC_OPT2     (EN_DC_OPT2_END-EN_DC_OPT2_STR)      // 板卡2光功率
#define CN_NUM_BOARD_DC    (EN_BOARD_DC_END)                    // 直流相关板卡个数
#define CN_DC_DSP_SAM      (3)                                  // 直采直流显示数据倍率
#define CN_DC_DIV_SAM      (3)                                  // 直采直流采集数据倍率
#define CN_DC_DSP_DEV      (3)                              // 装置直流显示数据倍率
#define CN_DC_DIV_DEV      (3)                              // 装置直流采集数据倍率
#if(CN_DEV_CPU1)
#define CN_DC_INDEX_T       (EN_DC_T1)                      // 直采直流显示数据倍率
#define CN_DC_INDEX_V       (EN_DC_V1)                      // 直采直流采集数据倍率
#define CN_DC_INDEX_CRC     (EN_DC_CCD_CRC)                 // 直采直流采集数据倍率
#else
#define CN_DC_INDEX_T       (EN_DC_T2)                      // 直采直流显示数据倍率
#define CN_DC_INDEX_V       (EN_DC_V6)                      // 直采直流采集数据倍率
#define CN_DC_INDEX_CRC     (EN_DC_CCD_CRC2)                // 直采直流采集数据倍率
#endif
/*================================================================================*/
// 常量表声明
/*================================================================================*/
extern const tagDCTab       g_tDCTab[];
extern const DWORD          g_NUM_DC;
extern const tagBoardDCTab  g_tBoardDCTab[];
extern const DWORD          g_NUM_BOARD_DC;

/*================================================================================*/
#endif /* _CONST_SAM_H_ */
