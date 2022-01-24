#include "Const_Pub.h"

//================================================================================
// 模拟量常量表(与模拟量通道枚举量表一一对应)
/*================================================================================
WORD			wIndex; 						// 模拟量枚举号
WORD			wChanType;						// 模拟量向量类型
WORD			wParaFst;						// 关联的额定一次值参数
WORD			wParaScd;						// 关联的额定二次值参数
WORD			wFrmNo;							// 数据源--帧类型
WORD			wFrmNum;						// 数据源--帧序号
WORD			wADNo; 							// 数据源--数据块编码
WORD			wADChn;							// 数据源--数据通道编码
WORD			wCfg;							// 通道其他属性
INT8S			byName[CN_LEN_NAME]; 			// 模拟量名称
INT8S			byPinName[CN_LEN_NAME];			// 模拟量短地址
================================================================================*/
const tagAnaTab g_tAnaTab[ ] =
{
//  wIndex             wChanType        wParaFst        wParaScd             wFrmNo                  wADNo                wADChn     dwCfg    byName       byPinName
	{ EN_ANA_UA1   ,  EN_CTYPE_ANA_U,  EN_PARA_BHPT,    EN_PARA_BHPT2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ4-EN_ANA_JZ_STR,      0,        0,    "保护测量Ua1",    "ANA_UA1"},
	{ EN_ANA_UA2   ,  EN_CTYPE_ANA_U,  EN_PARA_BHPT,    EN_PARA_BHPT2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ5-EN_ANA_JZ_STR,      0,        0,    "保护测量Ua2",    "ANA_UA2"},
	{ EN_ANA_UB1   ,  EN_CTYPE_ANA_U,  EN_PARA_BHPT,    EN_PARA_BHPT2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ4-EN_ANA_JZ_STR,      1,        0,    "保护测量Ub1",    "ANA_UB1"},
	{ EN_ANA_UB2   ,  EN_CTYPE_ANA_U,  EN_PARA_BHPT,    EN_PARA_BHPT2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ5-EN_ANA_JZ_STR,      1,        0,    "保护测量Ub2",    "ANA_UB2"},
	{ EN_ANA_UC1   ,  EN_CTYPE_ANA_U,  EN_PARA_BHPT,    EN_PARA_BHPT2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ4-EN_ANA_JZ_STR,      2,        0,    "保护测量Uc1",    "ANA_UC1"},
	{ EN_ANA_UC2   ,  EN_CTYPE_ANA_U,  EN_PARA_BHPT,    EN_PARA_BHPT2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ5-EN_ANA_JZ_STR,      2,        0,    "保护测量Uc2",    "ANA_UC2"},
	{ EN_ANA_U01   ,  EN_CTYPE_ANA_U,  EN_PARA_LXPT,    EN_PARA_LXPT2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ4-EN_ANA_JZ_STR,      4,        0,    "保护测量3U01",   "ANA_U01"},
	{ EN_ANA_U02   ,  EN_CTYPE_ANA_U,  EN_PARA_LXPT,    EN_PARA_LXPT2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ5-EN_ANA_JZ_STR,      4,        0,    "保护测量3U02",   "ANA_U02"},
	{ EN_ANA_UX1   ,  EN_CTYPE_ANA_U,  EN_PARA_XLPT,    EN_PARA_XLPT2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ4-EN_ANA_JZ_STR,      3,        0,    "保护测量Ux1",    "ANA_UX1"},
	{ EN_ANA_UX2   ,  EN_CTYPE_ANA_U,  EN_PARA_XLPT,    EN_PARA_XLPT2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ5-EN_ANA_JZ_STR,      3,        0,    "保护测量Ux2",    "ANA_UX2"},
// 系统测试临时修改
#if (CN_FUN_DBUG1)
	{ EN_ANA_UAJ   ,  EN_CTYPE_ANA_U,  EN_PARA_JLPT,    EN_PARA_JLPT2,     EN_BOARD_SAM_PTCT2,   EN_ANA_JZ1-EN_ANA_JZ_STR,      0,        0,    "计量Uaj",       "ANA_UAJ"},
	{ EN_ANA_UBJ   ,  EN_CTYPE_ANA_U,  EN_PARA_JLPT,    EN_PARA_JLPT2,     EN_BOARD_SAM_PTCT2,   EN_ANA_JZ1-EN_ANA_JZ_STR,      1,        0,    "计量Ubj",       "ANA_UBJ"},
	{ EN_ANA_UCJ   ,  EN_CTYPE_ANA_U,  EN_PARA_JLPT,    EN_PARA_JLPT2,     EN_BOARD_SAM_PTCT2,   EN_ANA_JZ1-EN_ANA_JZ_STR,      2,        0,    "计量Ucj",       "ANA_UCJ"},
	{ EN_ANA_1_IA1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ3-EN_ANA_JZ_STR,      0,        0,    "保护CT1 I1a1",   "ANA_1_IA1"},
	{ EN_ANA_1_IA2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ2-EN_ANA_JZ_STR,      0,        DB0,  "保护CT1 I1a2",   "ANA_1_IA2"},
	{ EN_ANA_1_IB1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ3-EN_ANA_JZ_STR,      1,        0,    "保护CT1 I1b1",   "ANA_1_IB1"},
	{ EN_ANA_1_IB2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ2-EN_ANA_JZ_STR,      1,        DB0,  "保护CT1 I1b2",   "ANA_1_IB2"},
	{ EN_ANA_1_IC1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ3-EN_ANA_JZ_STR,      2,        0,    "保护CT1 I1c1",   "ANA_1_IC1"},
	{ EN_ANA_1_IC2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ2-EN_ANA_JZ_STR,      2,        DB0,  "保护CT1 I1c2",   "ANA_1_IC2"},
	{ EN_ANA_IAJ   ,  EN_CTYPE_ANA_I,  EN_PARA_CT_JL1,  EN_PARA_CT_JL2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ1-EN_ANA_JZ_STR,      4,        0,    "测量计量Iac",     "ANA_IAJ"},
	{ EN_ANA_IBJ   ,  EN_CTYPE_ANA_I,  EN_PARA_CT_JL1,  EN_PARA_CT_JL2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ1-EN_ANA_JZ_STR,      5,        0,    "测量计量Ibc",     "ANA_IBJ"},
	{ EN_ANA_ICJ   ,  EN_CTYPE_ANA_I,  EN_PARA_CT_JL1,  EN_PARA_CT_JL2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ1-EN_ANA_JZ_STR,      6,        0,    "测量计量Icc",     "ANA_ICJ"},
	{ EN_ANA_2_IA1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_A1,  EN_PARA_CT2_A2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ3-EN_ANA_JZ_STR,      4,        0,    "保护CT2 I2a1",   "ANA_2_IA1"},
	{ EN_ANA_2_IA2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_A1,  EN_PARA_CT2_A2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ2-EN_ANA_JZ_STR,      4,        DB0,  "保护CT2 I2a2",   "ANA_2_IA2"},
	{ EN_ANA_2_IB1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_B1,  EN_PARA_CT2_B2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ3-EN_ANA_JZ_STR,      5,        0,    "保护CT2 I2b1",   "ANA_2_IB1"},
	{ EN_ANA_2_IB2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_B1,  EN_PARA_CT2_B2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ2-EN_ANA_JZ_STR,      5,        DB0,  "保护CT2 I2b2",   "ANA_2_IB2"},
	{ EN_ANA_2_IC1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_C1,  EN_PARA_CT2_C2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ3-EN_ANA_JZ_STR,      6,        0,    "保护CT2 I2c1",   "ANA_2_IC1"},
	{ EN_ANA_2_IC2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_C1,  EN_PARA_CT2_C2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ2-EN_ANA_JZ_STR,      6,        DB0,  "保护CT2 I2c2",   "ANA_2_IC2"},
#else
	{ EN_ANA_UAJ   ,  EN_CTYPE_ANA_U,  EN_PARA_JLPT,    EN_PARA_JLPT2,     EN_BOARD_SAM_PTCT2,   EN_ANA_JZ3-EN_ANA_JZ_STR,      0,        0,    "计量Uaj",       "ANA_UAJ"},
	{ EN_ANA_UBJ   ,  EN_CTYPE_ANA_U,  EN_PARA_JLPT,    EN_PARA_JLPT2,     EN_BOARD_SAM_PTCT2,   EN_ANA_JZ3-EN_ANA_JZ_STR,      1,        0,    "计量Ubj",       "ANA_UBJ"},
	{ EN_ANA_UCJ   ,  EN_CTYPE_ANA_U,  EN_PARA_JLPT,    EN_PARA_JLPT2,     EN_BOARD_SAM_PTCT2,   EN_ANA_JZ3-EN_ANA_JZ_STR,      2,        0,    "计量Ucj",       "ANA_UCJ"},
	{ EN_ANA_1_IA1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ1-EN_ANA_JZ_STR,      0,        0,    "保护CT1 I1a1",   "ANA_1_IA1"},
	{ EN_ANA_1_IA2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ2-EN_ANA_JZ_STR,      0,        0,    "保护CT1 I1a2",   "ANA_1_IA2"},
	{ EN_ANA_1_IB1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ1-EN_ANA_JZ_STR,      1,        0,    "保护CT1 I1b1",   "ANA_1_IB1"},
	{ EN_ANA_1_IB2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ2-EN_ANA_JZ_STR,      1,        0,    "保护CT1 I1b2",   "ANA_1_IB2"},
	{ EN_ANA_1_IC1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ1-EN_ANA_JZ_STR,      2,        0,    "保护CT1 I1c1",   "ANA_1_IC1"},
	{ EN_ANA_1_IC2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ2-EN_ANA_JZ_STR,      2,        0,    "保护CT1 I1c2",   "ANA_1_IC2"},
	{ EN_ANA_IAJ   ,  EN_CTYPE_ANA_I,  EN_PARA_CT_JL1,  EN_PARA_CT_JL2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ3-EN_ANA_JZ_STR,      4,        0,    "测量计量Iac",     "ANA_IAJ"},
	{ EN_ANA_IBJ   ,  EN_CTYPE_ANA_I,  EN_PARA_CT_JL1,  EN_PARA_CT_JL2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ3-EN_ANA_JZ_STR,      5,        0,    "测量计量Ibc",     "ANA_IBJ"},
	{ EN_ANA_ICJ   ,  EN_CTYPE_ANA_I,  EN_PARA_CT_JL1,  EN_PARA_CT_JL2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ3-EN_ANA_JZ_STR,      6,        0,    "测量计量Icc",     "ANA_ICJ"},
	{ EN_ANA_2_IA1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_A1,  EN_PARA_CT2_A2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ1-EN_ANA_JZ_STR,      4,        0,    "保护CT2 I2a1",   "ANA_2_IA1"},
	{ EN_ANA_2_IA2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_A1,  EN_PARA_CT2_A2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ2-EN_ANA_JZ_STR,      4,        0,    "保护CT2 I2a2",   "ANA_2_IA2"},
	{ EN_ANA_2_IB1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_B1,  EN_PARA_CT2_B2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ1-EN_ANA_JZ_STR,      5,        0,    "保护CT2 I2b1",   "ANA_2_IB1"},
	{ EN_ANA_2_IB2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_B1,  EN_PARA_CT2_B2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ2-EN_ANA_JZ_STR,      5,        0,    "保护CT2 I2b2",   "ANA_2_IB2"},
	{ EN_ANA_2_IC1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_C1,  EN_PARA_CT2_C2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ1-EN_ANA_JZ_STR,      6,        0,    "保护CT2 I2c1",   "ANA_2_IC1"},
	{ EN_ANA_2_IC2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_C1,  EN_PARA_CT2_C2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ2-EN_ANA_JZ_STR,      6,        0,    "保护CT2 I2c2",   "ANA_2_IC2"},
#endif
// 暂时借用AD电压一、二次值参数配置AD芯片延时
	{ EN_ANA_JZ1     ,  EN_CTYPE_ANA_J,  CN_NULL_PINNO,    CN_NULL_PINNO,  EN_BOARD_SAM_CPU,     EN_ANA_JZ1-EN_ANA_JZ_STR,      7,      0,  "AD1基准电压",        "ANA_JZ1"},
	{ EN_ANA_JZ2     ,  EN_CTYPE_ANA_J,  CN_NULL_PINNO,    CN_NULL_PINNO,  EN_BOARD_SAM_CPU,     EN_ANA_JZ2-EN_ANA_JZ_STR,      7,      0,  "AD2基准电压",        "ANA_JZ2"},
	{ EN_ANA_JZ3     ,  EN_CTYPE_ANA_J,  CN_NULL_PINNO,    CN_NULL_PINNO,  EN_BOARD_SAM_CPU,     EN_ANA_JZ3-EN_ANA_JZ_STR,      7,      0,  "AD3基准电压",        "ANA_JZ3"},
	{ EN_ANA_JZ4     ,  EN_CTYPE_ANA_J,  CN_NULL_PINNO,    CN_NULL_PINNO,  EN_BOARD_SAM_CPU,     EN_ANA_JZ4-EN_ANA_JZ_STR,      7,      0,  "AD4基准电压",        "ANA_JZ4"},
	{ EN_ANA_JZ5     ,  EN_CTYPE_ANA_J,  CN_NULL_PINNO,    CN_NULL_PINNO,  EN_BOARD_SAM_CPU,     EN_ANA_JZ5-EN_ANA_JZ_STR,      7,      0,  "AD5基准电压",        "ANA_JZ5"},
#if(CN_DEV_CPU1)
	{ EN_ANA_SVA1_UA1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅰ母保测Ua1",       "ANA_SVA1_UA1"},
	{ EN_ANA_SVA1_UA2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅰ母保测Ua2",       "ANA_SVA1_UA2"},
	{ EN_ANA_SVA1_UB1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅰ母保测Ub1",       "ANA_SVA1_UB1"},
	{ EN_ANA_SVA1_UB2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅰ母保测Ub2",       "ANA_SVA1_UB2"},
	{ EN_ANA_SVA1_UC1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅰ母保测Uc1",       "ANA_SVA1_UC1"},
	{ EN_ANA_SVA1_UC2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅰ母保测Uc2",       "ANA_SVA1_UC2"},
	{ EN_ANA_SVA1_U01,  EN_CTYPE_SV_U,  EN_PARA_SVLXPT,  EN_PARA_SVLXPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅰ母保测3U01",      "ANA_SVA1_U01"},
	{ EN_ANA_SVA1_U02,  EN_CTYPE_SV_U,  EN_PARA_SVLXPT,  EN_PARA_SVLXPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅰ母保测3U02",      "ANA_SVA1_U02"},
	{ EN_ANA_SVA1_UAJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅰ母计量Uaj",       "ANA_SVA1_UAJ"},
	{ EN_ANA_SVA1_UBJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅰ母计量Ubj",       "ANA_SVA1_UBJ"},
	{ EN_ANA_SVA1_UCJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅰ母计量Ucj",       "ANA_SVA1_UCJ"},
	{ EN_ANA_SVA2_UA1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅱ母保测Ua1",       "ANA_SVA2_UA1"},
	{ EN_ANA_SVA2_UA2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅱ母保测Ua2",       "ANA_SVA2_UA2"},
	{ EN_ANA_SVA2_UB1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅱ母保测Ub1",       "ANA_SVA2_UB1"},
	{ EN_ANA_SVA2_UB2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅱ母保测Ub2",       "ANA_SVA2_UB2"},
	{ EN_ANA_SVA2_UC1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅱ母保测Uc1",       "ANA_SVA2_UC1"},
	{ EN_ANA_SVA2_UC2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅱ母保测Uc2",       "ANA_SVA2_UC2"},
	{ EN_ANA_SVA2_U01,  EN_CTYPE_SV_U,  EN_PARA_SVLXPT,  EN_PARA_SVLXPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅱ母保测3U01",      "ANA_SVA2_U01"},
	{ EN_ANA_SVA2_U02,  EN_CTYPE_SV_U,  EN_PARA_SVLXPT,  EN_PARA_SVLXPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅱ母保测3U02",      "ANA_SVA2_U02"},
	{ EN_ANA_SVA2_UAJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅱ母计量Uaj",       "ANA_SVA2_UAJ"},
	{ EN_ANA_SVA2_UBJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅱ母计量Ubj",       "ANA_SVA2_UBJ"},
	{ EN_ANA_SVA2_UCJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A套Ⅱ母计量Ucj",       "ANA_SVA2_UCJ"},
	{ EN_ANA_SVB1_UA1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅰ母保测Ua1",       "ANA_SVB1_UA1"},
	{ EN_ANA_SVB1_UA2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅰ母保测Ua2",       "ANA_SVB1_UA2"},
	{ EN_ANA_SVB1_UB1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅰ母保测Ub1",       "ANA_SVB1_UB1"},
	{ EN_ANA_SVB1_UB2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅰ母保测Ub2",       "ANA_SVB1_UB2"},
	{ EN_ANA_SVB1_UC1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅰ母保测Uc1",       "ANA_SVB1_UC1"},
	{ EN_ANA_SVB1_UC2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅰ母保测Uc2",       "ANA_SVB1_UC2"},
	{ EN_ANA_SVB1_U01,  EN_CTYPE_SV_U,  EN_PARA_SVLXPT,  EN_PARA_SVLXPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅰ母保测3U01",      "ANA_SVB1_U01"},
	{ EN_ANA_SVB1_U02,  EN_CTYPE_SV_U,  EN_PARA_SVLXPT,  EN_PARA_SVLXPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅰ母保测3U02",      "ANA_SVB1_U02"},
	{ EN_ANA_SVB1_UAJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅰ母计量Uaj",       "ANA_SVB1_UAJ"},
	{ EN_ANA_SVB1_UBJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅰ母计量Ubj",       "ANA_SVB1_UBJ"},
	{ EN_ANA_SVB1_UCJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅰ母计量Ucj",       "ANA_SVB1_UCJ"},
	{ EN_ANA_SVB2_UA1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅱ母保测Ua1",       "ANA_SVB2_UA1"},
	{ EN_ANA_SVB2_UA2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅱ母保测Ua2",       "ANA_SVB2_UA2"},
	{ EN_ANA_SVB2_UB1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅱ母保测Ub1",       "ANA_SVB2_UB1"},
	{ EN_ANA_SVB2_UB2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅱ母保测Ub2",       "ANA_SVB2_UB2"},
	{ EN_ANA_SVB2_UC1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅱ母保测Uc1",       "ANA_SVB2_UC1"},
	{ EN_ANA_SVB2_UC2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅱ母保测Uc2",       "ANA_SVB2_UC2"},
	{ EN_ANA_SVB2_U01,  EN_CTYPE_SV_U,  EN_PARA_SVLXPT,  EN_PARA_SVLXPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅱ母保测3U01",      "ANA_SVB2_U01"},
	{ EN_ANA_SVB2_U02,  EN_CTYPE_SV_U,  EN_PARA_SVLXPT,  EN_PARA_SVLXPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅱ母保测3U02",      "ANA_SVB2_U02"},
	{ EN_ANA_SVB2_UAJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅱ母计量Uaj",       "ANA_SVB2_UAJ"},
	{ EN_ANA_SVB2_UBJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅱ母计量Ubj",       "ANA_SVB2_UBJ"},
	{ EN_ANA_SVB2_UCJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B套Ⅱ母计量Ucj",       "ANA_SVB2_UCJ"},
#elif(CN_DEV_CPU2)
	{ EN_ANA_SVA1_UA1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "级联母线保测Ua1",       "ANA_SVA1_UA1"},
	{ EN_ANA_SVA1_UA2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "级联母线保测Ua2",       "ANA_SVA1_UA2"},
	{ EN_ANA_SVA1_UB1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "级联母线保测Ub1",       "ANA_SVA1_UB1"},
	{ EN_ANA_SVA1_UB2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "级联母线保测Ub2",       "ANA_SVA1_UB2"},
	{ EN_ANA_SVA1_UC1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "级联母线保测Uc1",       "ANA_SVA1_UC1"},
	{ EN_ANA_SVA1_UC2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "级联母线保测Uc2",       "ANA_SVA1_UC2"},
	{ EN_ANA_SVA1_U01,  EN_CTYPE_SV_U,  EN_PARA_SVLXPT,  EN_PARA_SVLXPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "级联母线保测3U01",      "ANA_SVA1_U01"},
	{ EN_ANA_SVA1_U02,  EN_CTYPE_SV_U,  EN_PARA_SVLXPT,  EN_PARA_SVLXPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "级联母线保测3U02",      "ANA_SVA1_U02"},
	{ EN_ANA_SVA1_UAJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "级联母线计量Uaj",         "ANA_SVA1_UAJ"},
	{ EN_ANA_SVA1_UBJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "级联母线计量Ubj",         "ANA_SVA1_UBJ"},
	{ EN_ANA_SVA1_UCJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "级联母线计量Ucj",         "ANA_SVA1_UCJ"},
#endif
};
const DWORD g_NUM_ANA = sizeof(g_tAnaTab) / sizeof(tagAnaTab);
//================================================================================
// 计算量常量表
/*================================================================================
	WORD            wIndex;                         // 计算量枚举号
	WORD            wChanType;                      // 计算量类型
	WORD            wSrcDType;                      // 计算源类型
	WORD            wSrcIndex[3];                   // 计算源枚举
	WORD            wParaIndex;                     // 计算量参数设置
	INT8S           byName[CN_LEN_NAME];            // 计算量名称
	INT8S           byPinName[CN_LEN_NAME];         // 计算量短地址
================================================================================*/
const tagCalTab g_tCalTab[ ] =
{
	//wIndex          wChanType         wSrcDType           wSrcIndex[3]                           wParaIndex    byName   byPinName
#if(CN_DEV_CPU1)
	{ EN_CAL_A1_F1,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_SVA1_UA1,EN_ANA_SVA1_UB1,EN_ANA_SVA1_UC1},  EN_PARA_MF_TYPE, "级联A套Ⅰ母频率AD1",  "CAL_1_F1"},
	{ EN_CAL_A1_F2,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_SVA1_UA2,EN_ANA_SVA1_UB2,EN_ANA_SVA1_UC2},  EN_PARA_MF_TYPE, "级联A套Ⅰ母频率AD2",  "CAL_1_F2"},
	{ EN_CAL_A2_F1,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_SVA2_UA1,EN_ANA_SVA2_UB1,EN_ANA_SVA2_UC1},  EN_PARA_MF_TYPE, "级联A套Ⅱ母频率AD1",  "CAL_2_F1"},
	{ EN_CAL_A2_F2,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_SVA2_UA2,EN_ANA_SVA2_UB2,EN_ANA_SVA2_UC2},  EN_PARA_MF_TYPE, "级联A套Ⅱ母频率AD2",  "CAL_2_F2"},
	{ EN_CAL_B1_F1,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_SVB1_UA1,EN_ANA_SVB1_UB1,EN_ANA_SVB1_UC1},  EN_PARA_MF_TYPE, "级联B套Ⅰ母频率AD1",   "CAL_1_F1"},
	{ EN_CAL_B1_F2,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_SVB1_UA2,EN_ANA_SVB1_UB2,EN_ANA_SVB1_UC2},  EN_PARA_MF_TYPE, "级联B套Ⅰ母频率AD2",   "CAL_1_F2"},
	{ EN_CAL_B2_F1,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_SVB2_UA1,EN_ANA_SVB2_UB1,EN_ANA_SVB2_UC1},  EN_PARA_MF_TYPE, "级联B套Ⅱ母频率AD1",   "CAL_2_F1"},
	{ EN_CAL_B2_F2,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_SVB2_UA2,EN_ANA_SVB2_UB2,EN_ANA_SVB2_UC2},  EN_PARA_MF_TYPE, "级联B套Ⅱ母频率AD2",   "CAL_2_F2"},
#elif(CN_DEV_CPU2)
	{ EN_CAL_A1_F1,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_SVA1_UA1,EN_ANA_SVA1_UB1,EN_ANA_SVA1_UC1},  EN_PARA_MF_TYPE, "级联母线频率AD1","CAL_1_F1"},
	{ EN_CAL_A1_F2,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_SVA1_UA2,EN_ANA_SVA1_UB2,EN_ANA_SVA1_UC2},  EN_PARA_MF_TYPE, "级联母线频率AD2",  "CAL_1_F2"},
#endif
	{ EN_CAL_J1_F1,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_UA1,     EN_ANA_UB1,     EN_ANA_UC1},       EN_PARA_JF_TYPE, "间隔频率AD1",           "CAL_J1_F1"},
	{ EN_CAL_J1_F2,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_UA2,     EN_ANA_UA2,     EN_ANA_UC2},       EN_PARA_JF_TYPE, "间隔频率AD2",           "CAL_J1_F2"},
	{ EN_CAL_Ux_F1,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_UX1,     CN_NULL_PINNO,  CN_NULL_PINNO},    CN_NULL_PINNO,   "Ux频率AD1",           "CAL_Ux_F1"},
	{ EN_CAL_Ux_F2,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_UX2,     CN_NULL_PINNO,  CN_NULL_PINNO},    CN_NULL_PINNO,   "Ux频率AD2",           "CAL_Ux_F2"},
};
const DWORD g_NUM_CAL = sizeof(g_tCalTab) / sizeof(tagCalTab);
/*================================================================================*/
// SV发布标准配置
/*================================================================================*/
const tagSvPubTab g_tSvPubTab[] =
{
	{EN_ANA_1_IA1,  EN_ANA_1_IA1,  EN_ANA_1_IA1},
	{EN_ANA_1_IA2,  EN_ANA_1_IA2,  EN_ANA_1_IA2},
	{EN_ANA_1_IB1,  EN_ANA_1_IB1,  EN_ANA_1_IB1},
	{EN_ANA_1_IB2,  EN_ANA_1_IB2,  EN_ANA_1_IB2},
	{EN_ANA_1_IC1,  EN_ANA_1_IC1,  EN_ANA_1_IC1},
	{EN_ANA_1_IC2,  EN_ANA_1_IC2,  EN_ANA_1_IC2},
	{EN_ANA_IAJ  ,  EN_ANA_IAJ  ,  EN_ANA_IAJ  },
	{EN_ANA_IBJ  ,  EN_ANA_IBJ  ,  EN_ANA_IBJ  },
	{EN_ANA_ICJ  ,  EN_ANA_ICJ  ,  EN_ANA_ICJ  },
	{EN_ANA_2_IA1,  EN_ANA_2_IA1,  EN_ANA_2_IA1},
	{EN_ANA_2_IA2,  EN_ANA_2_IA2,  EN_ANA_2_IA2},
	{EN_ANA_2_IB1,  EN_ANA_2_IB1,  EN_ANA_2_IB1},
	{EN_ANA_2_IB2,  EN_ANA_2_IB2,  EN_ANA_2_IB2},
	{EN_ANA_2_IC1,  EN_ANA_2_IC1,  EN_ANA_2_IC1},
	{EN_ANA_2_IC2,  EN_ANA_2_IC2,  EN_ANA_2_IC2},
	
	{EN_ANA_SVA1_UA1,  EN_ANA_UA1,  CN_NULL_PINNO},
	{EN_ANA_SVA1_UA2,  EN_ANA_UA2,  CN_NULL_PINNO},
	{EN_ANA_SVA1_UB1,  EN_ANA_UB1,  CN_NULL_PINNO},
	{EN_ANA_SVA1_UB2,  EN_ANA_UB2,  CN_NULL_PINNO},
	{EN_ANA_SVA1_UC1,  EN_ANA_UC1,  CN_NULL_PINNO},
	{EN_ANA_SVA1_UC2,  EN_ANA_UC2,  CN_NULL_PINNO},
	{EN_ANA_SVA1_U01,  EN_ANA_U01,  CN_NULL_PINNO},
	{EN_ANA_SVA1_U02,  EN_ANA_U02,  CN_NULL_PINNO},
	{EN_ANA_UX1     ,  EN_ANA_UX1,  CN_NULL_PINNO},
	{EN_ANA_UX2     ,  EN_ANA_UX2,  CN_NULL_PINNO},
	{EN_ANA_SVA1_UAJ,  EN_ANA_UAJ,  CN_NULL_PINNO},
	{EN_ANA_SVA1_UBJ,  EN_ANA_UBJ,  CN_NULL_PINNO},
	{EN_ANA_SVA1_UCJ,  EN_ANA_UCJ,  CN_NULL_PINNO}
};
const DWORD g_NUM_SVPUB = sizeof(g_tSvPubTab)/sizeof(tagSvPubTab);
/*================================================================================*/
// SV发布取模拟量母线电压
/*================================================================================*/

/*================================================================================*/
// 模拟量板卡设置常量表
/*================================================================================*/
const tagBoardAnaTab g_tBoardSamTab[] =
{
	{ EN_BOARD_SAM_PTCT1, "PTCT1",    "AngBoardSamA",16},
	{ EN_BOARD_SAM_PTCT2, "PTCT2",    "AngBoardSamB",12},
	{ EN_BOARD_SAM_CPU,   "CPU",      "AngBoardSamC",5},
	
};
const DWORD g_NUM_BOARDSAM = sizeof(g_tBoardSamTab) / sizeof(tagBoardAnaTab);
#if 0
/*================================================================================*/
// 数字量虚拟板卡设置常量表
/*================================================================================*/
const tagBoardAnaTab g_tBoardSvTab[] =
{
	{ EN_BOARD_SV_SVA,   "SvSubA",   "AngBoardSvA",EN_ANA_SVA_END-EN_ANA_SVA_STR},
	{ EN_BOARD_SV_SVB,   "SvSubB",   "AngBoardSvB",EN_ANA_SVB_END-EN_ANA_SVB_STR},
};
const DWORD g_NUM_BOARDSV = sizeof(g_tBoardSvTab) / sizeof(tagBoardAnaTab);
#endif
/*================================================================================*/
// 付氏算法系数表，放大((2^20)*√2/80)倍.
/*================================================================================*/
//80点付氏算法系数表cos(i*360/80)

const INT64 g_iCos80[CN_SAM_RATE] =
{
	18536, 18479, 18308, 18024, 17629, 17125, 16516, 15805, 14996, 14095,
	13107, 12038, 10895, 9685,  8415,  7094,  5728,  4327,  2900,  1454,
	0,     -1454, -2900, -4327, -5728, -7094, -8415, -9685, -10895,-12038,
	-13107,-14095,-14996,-15805,-16516,-17125,-17629,-18024,-18308,-18479,
	-18536,-18479,-18308,-18024,-17629,-17125,-16516,-15805,-14996,-14095,
	-13107,-12038,-10895,-9685, -8415, -7094, -5728, -4327, -2900, -1454,
	0,     1454,  2900,  4327,  5728,  7094,  8415,  9685,  10895, 12038,
	13107, 14095, 14996, 15805, 16516, 17125, 17629, 18024, 18308, 18479
};
//80点付氏算法系数表sin(i*360/80)
const INT64 g_iSin80[CN_SAM_RATE] =
{
	0,     1454,  2899,  4327,  5728,  7093,  8415,  9685,  10895, 12038,
	13107, 14095, 14996, 15804, 16516, 17125, 17629, 18024, 18308, 18479,
	18536, 18479, 18308, 18024, 17629, 17125, 16516, 15804, 14996, 14095,
	13107, 12038, 10895, 9685,  8415,  7093,  5728,  4327,  2899,  1454,
	0,     -1454, -2899, -4327, -5728, -7093, -8415, -9685, -10895,-12038,
	-13107,-14095,-14996,-15804,-16516,-17125,-17629,-18024,-18308,-18479,
	-18536,-18479,-18308,-18024,-17629,-17125,-16516,-15804,-14996,-14095,
	-13107,-12038,-10895,-9685, -8415, -7093, -5728, -4327, -2899, -1454
};
