#include "Const_Pub.h"

//================================================================================
// ģ����������(��ģ����ͨ��ö������һһ��Ӧ)
/*================================================================================
WORD			wIndex; 						// ģ����ö�ٺ�
WORD			wChanType;						// ģ������������
WORD			wParaFst;						// �����Ķһ��ֵ����
WORD			wParaScd;						// �����Ķ����ֵ����
WORD			wFrmNo;							// ����Դ--֡����
WORD			wFrmNum;						// ����Դ--֡���
WORD			wADNo; 							// ����Դ--���ݿ����
WORD			wADChn;							// ����Դ--����ͨ������
WORD			wCfg;							// ͨ����������
INT8S			byName[CN_LEN_NAME]; 			// ģ��������
INT8S			byPinName[CN_LEN_NAME];			// ģ�����̵�ַ
================================================================================*/
const tagAnaTab g_tAnaTab[ ] =
{
//  wIndex             wChanType        wParaFst        wParaScd             wFrmNo                  wADNo                wADChn     dwCfg    byName       byPinName
	{ EN_ANA_UA1   ,  EN_CTYPE_ANA_U,  EN_PARA_BHPT,    EN_PARA_BHPT2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ4-EN_ANA_JZ_STR,      0,        0,    "��������Ua1",    "ANA_UA1"},
	{ EN_ANA_UA2   ,  EN_CTYPE_ANA_U,  EN_PARA_BHPT,    EN_PARA_BHPT2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ5-EN_ANA_JZ_STR,      0,        0,    "��������Ua2",    "ANA_UA2"},
	{ EN_ANA_UB1   ,  EN_CTYPE_ANA_U,  EN_PARA_BHPT,    EN_PARA_BHPT2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ4-EN_ANA_JZ_STR,      1,        0,    "��������Ub1",    "ANA_UB1"},
	{ EN_ANA_UB2   ,  EN_CTYPE_ANA_U,  EN_PARA_BHPT,    EN_PARA_BHPT2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ5-EN_ANA_JZ_STR,      1,        0,    "��������Ub2",    "ANA_UB2"},
	{ EN_ANA_UC1   ,  EN_CTYPE_ANA_U,  EN_PARA_BHPT,    EN_PARA_BHPT2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ4-EN_ANA_JZ_STR,      2,        0,    "��������Uc1",    "ANA_UC1"},
	{ EN_ANA_UC2   ,  EN_CTYPE_ANA_U,  EN_PARA_BHPT,    EN_PARA_BHPT2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ5-EN_ANA_JZ_STR,      2,        0,    "��������Uc2",    "ANA_UC2"},
	{ EN_ANA_U01   ,  EN_CTYPE_ANA_U,  EN_PARA_LXPT,    EN_PARA_LXPT2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ4-EN_ANA_JZ_STR,      4,        0,    "��������3U01",   "ANA_U01"},
	{ EN_ANA_U02   ,  EN_CTYPE_ANA_U,  EN_PARA_LXPT,    EN_PARA_LXPT2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ5-EN_ANA_JZ_STR,      4,        0,    "��������3U02",   "ANA_U02"},
	{ EN_ANA_UX1   ,  EN_CTYPE_ANA_U,  EN_PARA_XLPT,    EN_PARA_XLPT2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ4-EN_ANA_JZ_STR,      3,        0,    "��������Ux1",    "ANA_UX1"},
	{ EN_ANA_UX2   ,  EN_CTYPE_ANA_U,  EN_PARA_XLPT,    EN_PARA_XLPT2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ5-EN_ANA_JZ_STR,      3,        0,    "��������Ux2",    "ANA_UX2"},
// ϵͳ������ʱ�޸�
#if (CN_FUN_DBUG1)
	{ EN_ANA_UAJ   ,  EN_CTYPE_ANA_U,  EN_PARA_JLPT,    EN_PARA_JLPT2,     EN_BOARD_SAM_PTCT2,   EN_ANA_JZ1-EN_ANA_JZ_STR,      0,        0,    "����Uaj",       "ANA_UAJ"},
	{ EN_ANA_UBJ   ,  EN_CTYPE_ANA_U,  EN_PARA_JLPT,    EN_PARA_JLPT2,     EN_BOARD_SAM_PTCT2,   EN_ANA_JZ1-EN_ANA_JZ_STR,      1,        0,    "����Ubj",       "ANA_UBJ"},
	{ EN_ANA_UCJ   ,  EN_CTYPE_ANA_U,  EN_PARA_JLPT,    EN_PARA_JLPT2,     EN_BOARD_SAM_PTCT2,   EN_ANA_JZ1-EN_ANA_JZ_STR,      2,        0,    "����Ucj",       "ANA_UCJ"},
	{ EN_ANA_1_IA1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ3-EN_ANA_JZ_STR,      0,        0,    "����CT1 I1a1",   "ANA_1_IA1"},
	{ EN_ANA_1_IA2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ2-EN_ANA_JZ_STR,      0,        DB0,  "����CT1 I1a2",   "ANA_1_IA2"},
	{ EN_ANA_1_IB1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ3-EN_ANA_JZ_STR,      1,        0,    "����CT1 I1b1",   "ANA_1_IB1"},
	{ EN_ANA_1_IB2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ2-EN_ANA_JZ_STR,      1,        DB0,  "����CT1 I1b2",   "ANA_1_IB2"},
	{ EN_ANA_1_IC1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ3-EN_ANA_JZ_STR,      2,        0,    "����CT1 I1c1",   "ANA_1_IC1"},
	{ EN_ANA_1_IC2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ2-EN_ANA_JZ_STR,      2,        DB0,  "����CT1 I1c2",   "ANA_1_IC2"},
	{ EN_ANA_IAJ   ,  EN_CTYPE_ANA_I,  EN_PARA_CT_JL1,  EN_PARA_CT_JL2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ1-EN_ANA_JZ_STR,      4,        0,    "��������Iac",     "ANA_IAJ"},
	{ EN_ANA_IBJ   ,  EN_CTYPE_ANA_I,  EN_PARA_CT_JL1,  EN_PARA_CT_JL2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ1-EN_ANA_JZ_STR,      5,        0,    "��������Ibc",     "ANA_IBJ"},
	{ EN_ANA_ICJ   ,  EN_CTYPE_ANA_I,  EN_PARA_CT_JL1,  EN_PARA_CT_JL2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ1-EN_ANA_JZ_STR,      6,        0,    "��������Icc",     "ANA_ICJ"},
	{ EN_ANA_2_IA1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_A1,  EN_PARA_CT2_A2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ3-EN_ANA_JZ_STR,      4,        0,    "����CT2 I2a1",   "ANA_2_IA1"},
	{ EN_ANA_2_IA2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_A1,  EN_PARA_CT2_A2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ2-EN_ANA_JZ_STR,      4,        DB0,  "����CT2 I2a2",   "ANA_2_IA2"},
	{ EN_ANA_2_IB1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_B1,  EN_PARA_CT2_B2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ3-EN_ANA_JZ_STR,      5,        0,    "����CT2 I2b1",   "ANA_2_IB1"},
	{ EN_ANA_2_IB2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_B1,  EN_PARA_CT2_B2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ2-EN_ANA_JZ_STR,      5,        DB0,  "����CT2 I2b2",   "ANA_2_IB2"},
	{ EN_ANA_2_IC1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_C1,  EN_PARA_CT2_C2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ3-EN_ANA_JZ_STR,      6,        0,    "����CT2 I2c1",   "ANA_2_IC1"},
	{ EN_ANA_2_IC2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_C1,  EN_PARA_CT2_C2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ2-EN_ANA_JZ_STR,      6,        DB0,  "����CT2 I2c2",   "ANA_2_IC2"},
#else
	{ EN_ANA_UAJ   ,  EN_CTYPE_ANA_U,  EN_PARA_JLPT,    EN_PARA_JLPT2,     EN_BOARD_SAM_PTCT2,   EN_ANA_JZ3-EN_ANA_JZ_STR,      0,        0,    "����Uaj",       "ANA_UAJ"},
	{ EN_ANA_UBJ   ,  EN_CTYPE_ANA_U,  EN_PARA_JLPT,    EN_PARA_JLPT2,     EN_BOARD_SAM_PTCT2,   EN_ANA_JZ3-EN_ANA_JZ_STR,      1,        0,    "����Ubj",       "ANA_UBJ"},
	{ EN_ANA_UCJ   ,  EN_CTYPE_ANA_U,  EN_PARA_JLPT,    EN_PARA_JLPT2,     EN_BOARD_SAM_PTCT2,   EN_ANA_JZ3-EN_ANA_JZ_STR,      2,        0,    "����Ucj",       "ANA_UCJ"},
	{ EN_ANA_1_IA1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ1-EN_ANA_JZ_STR,      0,        0,    "����CT1 I1a1",   "ANA_1_IA1"},
	{ EN_ANA_1_IA2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ2-EN_ANA_JZ_STR,      0,        0,    "����CT1 I1a2",   "ANA_1_IA2"},
	{ EN_ANA_1_IB1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ1-EN_ANA_JZ_STR,      1,        0,    "����CT1 I1b1",   "ANA_1_IB1"},
	{ EN_ANA_1_IB2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ2-EN_ANA_JZ_STR,      1,        0,    "����CT1 I1b2",   "ANA_1_IB2"},
	{ EN_ANA_1_IC1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ1-EN_ANA_JZ_STR,      2,        0,    "����CT1 I1c1",   "ANA_1_IC1"},
	{ EN_ANA_1_IC2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT1_1,   EN_PARA_CT1_2,     EN_BOARD_SAM_PTCT1,   EN_ANA_JZ2-EN_ANA_JZ_STR,      2,        0,    "����CT1 I1c2",   "ANA_1_IC2"},
	{ EN_ANA_IAJ   ,  EN_CTYPE_ANA_I,  EN_PARA_CT_JL1,  EN_PARA_CT_JL2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ3-EN_ANA_JZ_STR,      4,        0,    "��������Iac",     "ANA_IAJ"},
	{ EN_ANA_IBJ   ,  EN_CTYPE_ANA_I,  EN_PARA_CT_JL1,  EN_PARA_CT_JL2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ3-EN_ANA_JZ_STR,      5,        0,    "��������Ibc",     "ANA_IBJ"},
	{ EN_ANA_ICJ   ,  EN_CTYPE_ANA_I,  EN_PARA_CT_JL1,  EN_PARA_CT_JL2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ3-EN_ANA_JZ_STR,      6,        0,    "��������Icc",     "ANA_ICJ"},
	{ EN_ANA_2_IA1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_A1,  EN_PARA_CT2_A2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ1-EN_ANA_JZ_STR,      4,        0,    "����CT2 I2a1",   "ANA_2_IA1"},
	{ EN_ANA_2_IA2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_A1,  EN_PARA_CT2_A2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ2-EN_ANA_JZ_STR,      4,        0,    "����CT2 I2a2",   "ANA_2_IA2"},
	{ EN_ANA_2_IB1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_B1,  EN_PARA_CT2_B2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ1-EN_ANA_JZ_STR,      5,        0,    "����CT2 I2b1",   "ANA_2_IB1"},
	{ EN_ANA_2_IB2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_B1,  EN_PARA_CT2_B2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ2-EN_ANA_JZ_STR,      5,        0,    "����CT2 I2b2",   "ANA_2_IB2"},
	{ EN_ANA_2_IC1 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_C1,  EN_PARA_CT2_C2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ1-EN_ANA_JZ_STR,      6,        0,    "����CT2 I2c1",   "ANA_2_IC1"},
	{ EN_ANA_2_IC2 ,  EN_CTYPE_ANA_I,  EN_PARA_CT2_C1,  EN_PARA_CT2_C2,    EN_BOARD_SAM_PTCT2,   EN_ANA_JZ2-EN_ANA_JZ_STR,      6,        0,    "����CT2 I2c2",   "ANA_2_IC2"},
#endif
// ��ʱ����AD��ѹһ������ֵ��������ADоƬ��ʱ
	{ EN_ANA_JZ1     ,  EN_CTYPE_ANA_J,  CN_NULL_PINNO,    CN_NULL_PINNO,  EN_BOARD_SAM_CPU,     EN_ANA_JZ1-EN_ANA_JZ_STR,      7,      0,  "AD1��׼��ѹ",        "ANA_JZ1"},
	{ EN_ANA_JZ2     ,  EN_CTYPE_ANA_J,  CN_NULL_PINNO,    CN_NULL_PINNO,  EN_BOARD_SAM_CPU,     EN_ANA_JZ2-EN_ANA_JZ_STR,      7,      0,  "AD2��׼��ѹ",        "ANA_JZ2"},
	{ EN_ANA_JZ3     ,  EN_CTYPE_ANA_J,  CN_NULL_PINNO,    CN_NULL_PINNO,  EN_BOARD_SAM_CPU,     EN_ANA_JZ3-EN_ANA_JZ_STR,      7,      0,  "AD3��׼��ѹ",        "ANA_JZ3"},
	{ EN_ANA_JZ4     ,  EN_CTYPE_ANA_J,  CN_NULL_PINNO,    CN_NULL_PINNO,  EN_BOARD_SAM_CPU,     EN_ANA_JZ4-EN_ANA_JZ_STR,      7,      0,  "AD4��׼��ѹ",        "ANA_JZ4"},
	{ EN_ANA_JZ5     ,  EN_CTYPE_ANA_J,  CN_NULL_PINNO,    CN_NULL_PINNO,  EN_BOARD_SAM_CPU,     EN_ANA_JZ5-EN_ANA_JZ_STR,      7,      0,  "AD5��׼��ѹ",        "ANA_JZ5"},
#if(CN_DEV_CPU1)
	{ EN_ANA_SVA1_UA1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����Ua1",       "ANA_SVA1_UA1"},
	{ EN_ANA_SVA1_UA2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����Ua2",       "ANA_SVA1_UA2"},
	{ EN_ANA_SVA1_UB1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����Ub1",       "ANA_SVA1_UB1"},
	{ EN_ANA_SVA1_UB2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����Ub2",       "ANA_SVA1_UB2"},
	{ EN_ANA_SVA1_UC1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����Uc1",       "ANA_SVA1_UC1"},
	{ EN_ANA_SVA1_UC2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����Uc2",       "ANA_SVA1_UC2"},
	{ EN_ANA_SVA1_U01,  EN_CTYPE_SV_U,  EN_PARA_SVLXPT,  EN_PARA_SVLXPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����3U01",      "ANA_SVA1_U01"},
	{ EN_ANA_SVA1_U02,  EN_CTYPE_SV_U,  EN_PARA_SVLXPT,  EN_PARA_SVLXPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����3U02",      "ANA_SVA1_U02"},
	{ EN_ANA_SVA1_UAJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����Uaj",       "ANA_SVA1_UAJ"},
	{ EN_ANA_SVA1_UBJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����Ubj",       "ANA_SVA1_UBJ"},
	{ EN_ANA_SVA1_UCJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����Ucj",       "ANA_SVA1_UCJ"},
	{ EN_ANA_SVA2_UA1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����Ua1",       "ANA_SVA2_UA1"},
	{ EN_ANA_SVA2_UA2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����Ua2",       "ANA_SVA2_UA2"},
	{ EN_ANA_SVA2_UB1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����Ub1",       "ANA_SVA2_UB1"},
	{ EN_ANA_SVA2_UB2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����Ub2",       "ANA_SVA2_UB2"},
	{ EN_ANA_SVA2_UC1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����Uc1",       "ANA_SVA2_UC1"},
	{ EN_ANA_SVA2_UC2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����Uc2",       "ANA_SVA2_UC2"},
	{ EN_ANA_SVA2_U01,  EN_CTYPE_SV_U,  EN_PARA_SVLXPT,  EN_PARA_SVLXPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����3U01",      "ANA_SVA2_U01"},
	{ EN_ANA_SVA2_U02,  EN_CTYPE_SV_U,  EN_PARA_SVLXPT,  EN_PARA_SVLXPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����3U02",      "ANA_SVA2_U02"},
	{ EN_ANA_SVA2_UAJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����Uaj",       "ANA_SVA2_UAJ"},
	{ EN_ANA_SVA2_UBJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����Ubj",       "ANA_SVA2_UBJ"},
	{ EN_ANA_SVA2_UCJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "A�ע�ĸ����Ucj",       "ANA_SVA2_UCJ"},
	{ EN_ANA_SVB1_UA1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����Ua1",       "ANA_SVB1_UA1"},
	{ EN_ANA_SVB1_UA2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����Ua2",       "ANA_SVB1_UA2"},
	{ EN_ANA_SVB1_UB1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����Ub1",       "ANA_SVB1_UB1"},
	{ EN_ANA_SVB1_UB2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����Ub2",       "ANA_SVB1_UB2"},
	{ EN_ANA_SVB1_UC1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����Uc1",       "ANA_SVB1_UC1"},
	{ EN_ANA_SVB1_UC2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����Uc2",       "ANA_SVB1_UC2"},
	{ EN_ANA_SVB1_U01,  EN_CTYPE_SV_U,  EN_PARA_SVLXPT,  EN_PARA_SVLXPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����3U01",      "ANA_SVB1_U01"},
	{ EN_ANA_SVB1_U02,  EN_CTYPE_SV_U,  EN_PARA_SVLXPT,  EN_PARA_SVLXPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����3U02",      "ANA_SVB1_U02"},
	{ EN_ANA_SVB1_UAJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����Uaj",       "ANA_SVB1_UAJ"},
	{ EN_ANA_SVB1_UBJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����Ubj",       "ANA_SVB1_UBJ"},
	{ EN_ANA_SVB1_UCJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����Ucj",       "ANA_SVB1_UCJ"},
	{ EN_ANA_SVB2_UA1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����Ua1",       "ANA_SVB2_UA1"},
	{ EN_ANA_SVB2_UA2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����Ua2",       "ANA_SVB2_UA2"},
	{ EN_ANA_SVB2_UB1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����Ub1",       "ANA_SVB2_UB1"},
	{ EN_ANA_SVB2_UB2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����Ub2",       "ANA_SVB2_UB2"},
	{ EN_ANA_SVB2_UC1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����Uc1",       "ANA_SVB2_UC1"},
	{ EN_ANA_SVB2_UC2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����Uc2",       "ANA_SVB2_UC2"},
	{ EN_ANA_SVB2_U01,  EN_CTYPE_SV_U,  EN_PARA_SVLXPT,  EN_PARA_SVLXPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����3U01",      "ANA_SVB2_U01"},
	{ EN_ANA_SVB2_U02,  EN_CTYPE_SV_U,  EN_PARA_SVLXPT,  EN_PARA_SVLXPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����3U02",      "ANA_SVB2_U02"},
	{ EN_ANA_SVB2_UAJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����Uaj",       "ANA_SVB2_UAJ"},
	{ EN_ANA_SVB2_UBJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����Ubj",       "ANA_SVB2_UBJ"},
	{ EN_ANA_SVB2_UCJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVB,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "B�ע�ĸ����Ucj",       "ANA_SVB2_UCJ"},
#elif(CN_DEV_CPU2)
	{ EN_ANA_SVA1_UA1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "����ĸ�߱���Ua1",       "ANA_SVA1_UA1"},
	{ EN_ANA_SVA1_UA2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "����ĸ�߱���Ua2",       "ANA_SVA1_UA2"},
	{ EN_ANA_SVA1_UB1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "����ĸ�߱���Ub1",       "ANA_SVA1_UB1"},
	{ EN_ANA_SVA1_UB2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "����ĸ�߱���Ub2",       "ANA_SVA1_UB2"},
	{ EN_ANA_SVA1_UC1,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "����ĸ�߱���Uc1",       "ANA_SVA1_UC1"},
	{ EN_ANA_SVA1_UC2,  EN_CTYPE_SV_U,  EN_PARA_SVBHPT,  EN_PARA_SVBHPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "����ĸ�߱���Uc2",       "ANA_SVA1_UC2"},
	{ EN_ANA_SVA1_U01,  EN_CTYPE_SV_U,  EN_PARA_SVLXPT,  EN_PARA_SVLXPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "����ĸ�߱���3U01",      "ANA_SVA1_U01"},
	{ EN_ANA_SVA1_U02,  EN_CTYPE_SV_U,  EN_PARA_SVLXPT,  EN_PARA_SVLXPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "����ĸ�߱���3U02",      "ANA_SVA1_U02"},
	{ EN_ANA_SVA1_UAJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "����ĸ�߼���Uaj",         "ANA_SVA1_UAJ"},
	{ EN_ANA_SVA1_UBJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "����ĸ�߼���Ubj",         "ANA_SVA1_UBJ"},
	{ EN_ANA_SVA1_UCJ,  EN_CTYPE_SV_U,  EN_PARA_SVJLPT,  EN_PARA_SVJLPT2,  EN_BOARD_SV_SVA,      CN_NULL_PINNO,    CN_NULL_PINNO,    0,  "����ĸ�߼���Ucj",         "ANA_SVA1_UCJ"},
#endif
};
const DWORD g_NUM_ANA = sizeof(g_tAnaTab) / sizeof(tagAnaTab);
//================================================================================
// ������������
/*================================================================================
	WORD            wIndex;                         // ������ö�ٺ�
	WORD            wChanType;                      // ����������
	WORD            wSrcDType;                      // ����Դ����
	WORD            wSrcIndex[3];                   // ����Դö��
	WORD            wParaIndex;                     // ��������������
	INT8S           byName[CN_LEN_NAME];            // ����������
	INT8S           byPinName[CN_LEN_NAME];         // �������̵�ַ
================================================================================*/
const tagCalTab g_tCalTab[ ] =
{
	//wIndex          wChanType         wSrcDType           wSrcIndex[3]                           wParaIndex    byName   byPinName
#if(CN_DEV_CPU1)
	{ EN_CAL_A1_F1,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_SVA1_UA1,EN_ANA_SVA1_UB1,EN_ANA_SVA1_UC1},  EN_PARA_MF_TYPE, "����A�ע�ĸƵ��AD1",  "CAL_1_F1"},
	{ EN_CAL_A1_F2,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_SVA1_UA2,EN_ANA_SVA1_UB2,EN_ANA_SVA1_UC2},  EN_PARA_MF_TYPE, "����A�ע�ĸƵ��AD2",  "CAL_1_F2"},
	{ EN_CAL_A2_F1,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_SVA2_UA1,EN_ANA_SVA2_UB1,EN_ANA_SVA2_UC1},  EN_PARA_MF_TYPE, "����A�ע�ĸƵ��AD1",  "CAL_2_F1"},
	{ EN_CAL_A2_F2,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_SVA2_UA2,EN_ANA_SVA2_UB2,EN_ANA_SVA2_UC2},  EN_PARA_MF_TYPE, "����A�ע�ĸƵ��AD2",  "CAL_2_F2"},
	{ EN_CAL_B1_F1,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_SVB1_UA1,EN_ANA_SVB1_UB1,EN_ANA_SVB1_UC1},  EN_PARA_MF_TYPE, "����B�ע�ĸƵ��AD1",   "CAL_1_F1"},
	{ EN_CAL_B1_F2,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_SVB1_UA2,EN_ANA_SVB1_UB2,EN_ANA_SVB1_UC2},  EN_PARA_MF_TYPE, "����B�ע�ĸƵ��AD2",   "CAL_1_F2"},
	{ EN_CAL_B2_F1,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_SVB2_UA1,EN_ANA_SVB2_UB1,EN_ANA_SVB2_UC1},  EN_PARA_MF_TYPE, "����B�ע�ĸƵ��AD1",   "CAL_2_F1"},
	{ EN_CAL_B2_F2,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_SVB2_UA2,EN_ANA_SVB2_UB2,EN_ANA_SVB2_UC2},  EN_PARA_MF_TYPE, "����B�ע�ĸƵ��AD2",   "CAL_2_F2"},
#elif(CN_DEV_CPU2)
	{ EN_CAL_A1_F1,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_SVA1_UA1,EN_ANA_SVA1_UB1,EN_ANA_SVA1_UC1},  EN_PARA_MF_TYPE, "����ĸ��Ƶ��AD1","CAL_1_F1"},
	{ EN_CAL_A1_F2,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_SVA1_UA2,EN_ANA_SVA1_UB2,EN_ANA_SVA1_UC2},  EN_PARA_MF_TYPE, "����ĸ��Ƶ��AD2",  "CAL_1_F2"},
#endif
	{ EN_CAL_J1_F1,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_UA1,     EN_ANA_UB1,     EN_ANA_UC1},       EN_PARA_JF_TYPE, "���Ƶ��AD1",           "CAL_J1_F1"},
	{ EN_CAL_J1_F2,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_UA2,     EN_ANA_UA2,     EN_ANA_UC2},       EN_PARA_JF_TYPE, "���Ƶ��AD2",           "CAL_J1_F2"},
	{ EN_CAL_Ux_F1,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_UX1,     CN_NULL_PINNO,  CN_NULL_PINNO},    CN_NULL_PINNO,   "UxƵ��AD1",           "CAL_Ux_F1"},
	{ EN_CAL_Ux_F2,  EN_CTYPE_CAL_F,  EN_DTYPE_ANA,  {EN_ANA_UX2,     CN_NULL_PINNO,  CN_NULL_PINNO},    CN_NULL_PINNO,   "UxƵ��AD2",           "CAL_Ux_F2"},
};
const DWORD g_NUM_CAL = sizeof(g_tCalTab) / sizeof(tagCalTab);
/*================================================================================*/
// SV������׼����
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
// SV����ȡģ����ĸ�ߵ�ѹ
/*================================================================================*/

/*================================================================================*/
// ģ�����忨���ó�����
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
// ����������忨���ó�����
/*================================================================================*/
const tagBoardAnaTab g_tBoardSvTab[] =
{
	{ EN_BOARD_SV_SVA,   "SvSubA",   "AngBoardSvA",EN_ANA_SVA_END-EN_ANA_SVA_STR},
	{ EN_BOARD_SV_SVB,   "SvSubB",   "AngBoardSvB",EN_ANA_SVB_END-EN_ANA_SVB_STR},
};
const DWORD g_NUM_BOARDSV = sizeof(g_tBoardSvTab) / sizeof(tagBoardAnaTab);
#endif
/*================================================================================*/
// �����㷨ϵ�����Ŵ�((2^20)*��2/80)��.
/*================================================================================*/
//80�㸶���㷨ϵ����cos(i*360/80)

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
//80�㸶���㷨ϵ����sin(i*360/80)
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
