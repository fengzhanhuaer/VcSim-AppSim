#ifndef _CONST_PARA_H_
#define _CONST_PARA_H_

#include "IES_IMtypes.h"
// ֱ��������
enum _GROUP_PARA_DC
{
	EN_GROUP_DC_STR= 0,
	EN_GROUP_DC_IN   =EN_GROUP_DC_STR,        // DC���뷽ʽ
	EN_GROUP_DC_OUT ,        // DC���ģʽ 
	EN_GROUP_DC_MIN ,        // DC�����Сֵ
	EN_GROUP_DC_MAX ,        // DC������ֵ
	EN_GROUP_DC_OFST,        // DC�����ƫ����
	EN_GROUP_DC_END,
};
//
/*================================================================================*/
// �����ź�ö��
/*================================================================================*/
enum _PARA_NUMBER
{
// ����ʱ������ǰλ��
	EN_PARA_STR       = 0,
	EN_PARA_DI_STR    = EN_PARA_STR,
	EN_PARA_ENA_YXPOW1= EN_DI_END,
	EN_PARA_ENA_YXPOW2,
	EN_PARA_ENA_YXPOW3,
	EN_PARA_ENA_YXPOW4,
	
	EN_PARA_IO_BAK01,
	EN_PARA_IO_BAK02,
	EN_PARA_IO_BAK03,
	EN_PARA_IO_BAK04,
	EN_PARA_IO_BAK05,
	EN_PARA_IO_BAK06,
	EN_PARA_IO_BAK07,
	EN_PARA_IO_BAK08,
	EN_PARA_IO_BAK09,
	EN_PARA_IO_BAK10,
	EN_PARA_DI_END,
// ���ӱ��ò���
// ֱ������
	EN_PARA_DC_STR  =EN_PARA_DI_END,
	EN_PARA_DC1_STR =EN_PARA_DC_STR,                         // DC1��ʼ
	EN_PARA_DC1_IN  =EN_PARA_DC1_STR,                        // DC1����ģʽ
	EN_PARA_DC1_OUT =EN_PARA_DC1_STR+EN_GROUP_DC_OUT,        // DC1���ģʽ
	EN_PARA_DC1_MIN =EN_PARA_DC1_STR+EN_GROUP_DC_MIN,        // DC1�����Сֵ
	EN_PARA_DC1_MAX =EN_PARA_DC1_STR+EN_GROUP_DC_MAX,        // DC1������ֵ
	EN_PARA_DC1_OFST=EN_PARA_DC1_STR+EN_GROUP_DC_OFST,       // DC1�����ƫ����

	EN_PARA_DC2_STR =EN_PARA_DC1_STR+EN_GROUP_DC_END,        // DC2��ʼ 
	EN_PARA_DC2_IN  =EN_PARA_DC2_STR,                        // DC2����ģʽ
	EN_PARA_DC2_OUT =EN_PARA_DC2_STR+EN_GROUP_DC_OUT,        // DC2���ģʽ
	EN_PARA_DC2_MIN =EN_PARA_DC2_STR+EN_GROUP_DC_MIN,        // DC2�����Сֵ
	EN_PARA_DC2_MAX =EN_PARA_DC2_STR+EN_GROUP_DC_MAX,        // DC2������ֵ
	EN_PARA_DC2_OFST=EN_PARA_DC2_STR+EN_GROUP_DC_OFST,       // DC2�����ƫ����
#if(!CN_FUN_DBUG1)
	EN_PARA_DC3_STR =EN_PARA_DC2_STR+EN_GROUP_DC_END,        // DC3��ʼ 
	EN_PARA_DC3_IN  =EN_PARA_DC3_STR,                        // DC3����ģʽ
	EN_PARA_DC3_OUT =EN_PARA_DC3_STR+EN_GROUP_DC_OUT,        // DC3���ģʽ
	EN_PARA_DC3_MIN =EN_PARA_DC3_STR+EN_GROUP_DC_MIN,        // DC3�����Сֵ
	EN_PARA_DC3_MAX =EN_PARA_DC3_STR+EN_GROUP_DC_MAX,        // DC3������ֵ
	EN_PARA_DC3_OFST=EN_PARA_DC3_STR+EN_GROUP_DC_OFST,       // DC3�����ƫ����

	EN_PARA_DC4_STR =EN_PARA_DC3_STR+EN_GROUP_DC_END,        // DC4��ʼ 
	EN_PARA_DC4_IN  =EN_PARA_DC4_STR,                        // DC4����ģʽ
	EN_PARA_DC4_OUT =EN_PARA_DC4_STR+EN_GROUP_DC_OUT,        // DC4���ģʽ
	EN_PARA_DC4_MIN =EN_PARA_DC4_STR+EN_GROUP_DC_MIN,        // DC4�����Сֵ
	EN_PARA_DC4_MAX =EN_PARA_DC4_STR+EN_GROUP_DC_MAX,        // DC4������ֵ
	EN_PARA_DC4_OFST=EN_PARA_DC4_STR+EN_GROUP_DC_OFST,       // DC4�����ƫ����

	EN_PARA_DC5_STR =EN_PARA_DC4_STR+EN_GROUP_DC_END,        // DC5��ʼ 
	EN_PARA_DC5_IN  =EN_PARA_DC5_STR,                        // DC5����ģʽ
	EN_PARA_DC5_OUT =EN_PARA_DC5_STR+EN_GROUP_DC_OUT,        // DC5���ģʽ
	EN_PARA_DC5_MIN =EN_PARA_DC5_STR+EN_GROUP_DC_MIN,        // DC5�����Сֵ
	EN_PARA_DC5_MAX =EN_PARA_DC5_STR+EN_GROUP_DC_MAX,        // DC5������ֵ
	EN_PARA_DC5_OFST=EN_PARA_DC5_STR+EN_GROUP_DC_OFST,       // DC5�����ƫ����

	EN_PARA_DC6_STR =EN_PARA_DC5_STR+EN_GROUP_DC_END,        // DC6��ʼ 
	EN_PARA_DC6_IN  =EN_PARA_DC6_STR,                        // DC6����ģʽ
	EN_PARA_DC6_OUT =EN_PARA_DC6_STR+EN_GROUP_DC_OUT,        // DC6���ģʽ
	EN_PARA_DC6_MIN =EN_PARA_DC6_STR+EN_GROUP_DC_MIN,        // DC6�����Сֵ
	EN_PARA_DC6_MAX =EN_PARA_DC6_STR+EN_GROUP_DC_MAX,        // DC6������ֵ
	EN_PARA_DC6_OFST=EN_PARA_DC6_STR+EN_GROUP_DC_OFST,       // DC6�����ƫ����
	
	EN_PARA_DC7_STR =EN_PARA_DC6_STR+EN_GROUP_DC_END,        // DC7��ʼ 
	EN_PARA_DC7_IN  =EN_PARA_DC7_STR,                        // DC7����ģʽ
	EN_PARA_DC7_OUT =EN_PARA_DC7_STR+EN_GROUP_DC_OUT,        // DC7���ģʽ
	EN_PARA_DC7_MIN =EN_PARA_DC7_STR+EN_GROUP_DC_MIN,        // DC7�����Сֵ
	EN_PARA_DC7_MAX =EN_PARA_DC7_STR+EN_GROUP_DC_MAX,        // DC7������ֵ
	EN_PARA_DC7_OFST=EN_PARA_DC7_STR+EN_GROUP_DC_OFST,       // DC7�����ƫ����
#endif
	EN_PARA_DC_V_MA,
	EN_PARA_DC_TB,          // ֱ��ͻ��
	EN_PARA_T_TB,           // �¶�ͻ�����
	EN_PARA_V_TB,           // ��ѹͻ�����
	EN_PARA_RT_TB,          // �շ�����ͻ��
	EN_PARA_DC_BAK01,       // ֱ�������ò���01
	EN_PARA_DC_BAK02,       // ֱ�������ò���02
	EN_PARA_DC_BAK03,       // ֱ�������ò���03
	EN_PARA_DC_BAK04,       // ֱ�������ò���04
	EN_PARA_DC_BAK05,       // ֱ�������ò���05
	EN_PARA_DC_BAK06,       // ֱ�������ò���06
	EN_PARA_DC_BAK07,       // ֱ�������ò���07
	EN_PARA_DC_BAK08,       // ֱ�������ò���08
	EN_PARA_DC_BAK09,       // ֱ�������ò���09
	EN_PARA_DC_BAK10,       // ֱ�������ò���10
	EN_PARA_DC_END,
//  ��������
	EN_PARA_SAM_STR=EN_PARA_DC_END,
	EN_PARA_BHPT=EN_PARA_SAM_STR,    // ��������PTһ��ֵ
	EN_PARA_BHPT2,   // ��������PT����ֵ
	EN_PARA_JLPT,    // ����PTһ��ֵ
	EN_PARA_JLPT2,   // ����PT����ֵ
	EN_PARA_LXPT,    // ����PTһ��ֵ
	EN_PARA_LXPT2,   // ����PT����ֵ
	EN_PARA_XLPT,    // ��·PTһ��ֵ
	EN_PARA_XLPT2,   // ��·PT����ֵ
	EN_PARA_SVBHPT,  // ����SV��������PTһ��ֵ
	EN_PARA_SVBHPT2, // ����SV��������PT����ֵ
	EN_PARA_SVLXPT,  // ����SV����PTһ��ֵ
	EN_PARA_SVLXPT2, // ����SV����PT����ֵ
	EN_PARA_SVJLPT,  // ����SV����PTһ��ֵ
	EN_PARA_SVJLPT2, // ����SV����PT����ֵ
	EN_PARA_CT1_1,   // ����CTһ��ֵ
	EN_PARA_CT1_2,   // ����CT����ֵ
	EN_PARA_CT2_A1,  // ����CT2 A��һ��ֵ
	EN_PARA_CT2_A2,  // ����CT2 A�����ֵ
	EN_PARA_CT2_B1,  // ����CT2 B��һ��ֵ
	EN_PARA_CT2_B2,  // ����CT2 B�����ֵ
	EN_PARA_CT2_C1,  // ����CT2 C��һ��ֵ
	EN_PARA_CT2_C2,  // ����CT2 C�����ֵ
	EN_PARA_CT_JL1,  // ����������CTһ��ֵ
	EN_PARA_CT_JL2,  // ����������CT����ֵ
	EN_PARA_MAT_POL_SVA,// ����A�׷����Ծ���
	EN_PARA_MAT_POL_SVB,// ����B�׷����Ծ���
	EN_PARA_MAT_POL_L1, // ���ز�ģ����������1����
	EN_PARA_MAT_POL_L2, // ���ز�ģ����������2����
	EN_PARA_ENA_JZ,     // AD��׼����Ͷ��
	EN_PARA_V_JZ1MIN,   // AD��׼1�Լ��ż�����
	EN_PARA_V_JZ1MAX,   // AD��׼1�Լ��ż�����
	EN_PARA_V_JZ2MIN,   // AD��׼2�Լ��ż�����
	EN_PARA_V_JZ2MAX,   // AD��׼2�Լ��ż�����
	EN_PARA_JF_TYPE,
	EN_PARA_MF_TYPE,
	EN_PARA_SAM_BAK01,       // ���������ò���01
	EN_PARA_SAM_BAK02,       // ���������ò���02
	EN_PARA_SAM_BAK03,       // ���������ò���03
	EN_PARA_SAM_BAK04,       // ���������ò���04
	EN_PARA_SAM_BAK05,       // ���������ò���05
	EN_PARA_SAM_BAK06,       // ���������ò���06
	EN_PARA_SAM_BAK07,       // ���������ò���07
	EN_PARA_SAM_BAK08,       // ���������ò���08
	EN_PARA_SAM_BAK09,       // ���������ò���09
	EN_PARA_SAM_BAK10,       // ���������ò���10
	EN_PARA_SAM_END,
	
	EN_PARA_FUN_STR=EN_PARA_SAM_END,//���ܲ���
	EN_PARA_T_SYNCHK=EN_PARA_FUN_STR,      // ͬ���쳣�澯ʱ��
	EN_PARA_T_SAMCHK,      // �����쳣�澯ʱ��
	EN_PARA_T_DICHK,       // ����ʧ��澯ʱ��
	EN_PARA_T_PARA,        // �����仯�Զ�����ʱ��
	EN_PARA_T_SVOK,           // ����������ʱ
	EN_PARA_ENA_VQH,          // ��ѹ�л�����Ͷ��
//	EN_PARA_TYPE_BUS,         // ĸ�����ӷ�ʽ
	EN_PARA_T_VQH_ACT,        // PT�л�ͬʱ�����澯ʱ��
	EN_PARA_T_VQH_RET,        // PT�л�ͬʱ���ظ澯ʱ��
	EN_PARA_T_VQH_RET_RLY,    // PT�л�ͬʱ����ȷ��ʱ��
	EN_PARA_T_XSWI,           // ��բλ���쳣�澯ʱ��
//	EN_PARA_TYPE_MSAM,        // ĸ�ߵ�ѹ�ɼ���ʽ
	EN_PARA_TYPE_UxSAM,       // ͬ�ڵ�ѹ�ɼ���ʽ
	EN_PARA_ENA_LNK,          // �����л�����Ͷ��
	EN_PARA_T_BS_CHK,         // ѡ�����״̬�쳣�澯ʱ��
	EN_PARA_T_LNK_CHK,        // �����쳣�澯ʱ��
	EN_PARA_ENA_KHDX,         // ���ƻ�·���߸澯Ͷ��
	EN_PARA_T_KHDX,           // ���ƻ�·���߸澯ʱ��
	EN_PARA_ENA_OPB1,         // ������Դ������Ӹ澯Ͷ��
	EN_PARA_T_OPB1,           // ������Դ������Ӹ澯ʱ��
//	EN_PARA_TYPE_XCBR,        // ���ؽ���ģʽ
	EN_PARA_SXBYZ_YX,         // ���಻һ��ң�Ŷ���
	EN_PARA_T_SXBYZ,          // ���಻һ�¸澯ʱ��
	EN_PARA_TYPE_DEV,         // �Ƿ�Ϊ B �� 
	EN_PARA_TYPE_KKJ,         // KKJ���뷽ʽ
	EN_PARA_TYPE_SHJ,         // SHJ���뷽ʽ
	EN_PARA_TYPE_STJ,         // STJ���뷽ʽ
	EN_PARA_TYPE_TJF,         // TJF���뷽ʽ
//	EN_PARA_T_KKJ,            // KKJ�߼����ɷ���ʱ��
	EN_PARA_ENA_SGZ,          // �¹��ܹ���Ͷ��
	EN_PARA_T_SGZ,            // �¹���ʱ��
	EN_PARA_ENA_BSBC,         // ң��(STJ)�����غ�բ����Ͷ��
	EN_PARA_T_BSCH_INIT,      // װ���ϵ�����غ�բ����ʱ��
	EN_PARA_T_DO_RTN,
	EN_PARA_ENA_POW,          // װ�õ�Դ����Ͷ��
	EN_PARA_MAT_OUT1,         // ���ñ�������1��բ����
	EN_PARA_MAT_OUT2,         // ���ñ�������2��բ����
	EN_PARA_MAT_OUT3,         // ���ñ�������3��բ����
	EN_PARA_MAT_OUT4,         // ���ñ�������4��բ����
	EN_PARA_MAT_OUT5,         // ���ñ�������5��բ����(����)

	EN_PARA_MAT_LED1,        // ����ָʾ��1��������
	EN_PARA_MAT_LED2,        // ����ָʾ��2��������
	EN_PARA_MAT_LED3,        // ����ָʾ��3��������
	EN_PARA_MAT_LED4,        // ����ָʾ��4��������
	EN_PARA_MAT_LED5,        // ����ָʾ��5��������
	EN_PARA_MAT_LED6,        // ����ָʾ��6��������
	EN_PARA_FUN_BAK01,       // ���ܱ��ò���01
	EN_PARA_FUN_BAK02,       // ���ܱ��ò���02
	EN_PARA_FUN_BAK03,       // ���ܱ��ò���03
	EN_PARA_FUN_BAK04,       // ���ܱ��ò���04
	EN_PARA_FUN_BAK05,       // ���ܱ��ò���05
	EN_PARA_FUN_BAK06,       // ���ܱ��ò���06
	EN_PARA_FUN_BAK07,       // ���ܱ��ò���07
	EN_PARA_FUN_BAK08,       // ���ܱ��ò���08
	EN_PARA_FUN_BAK09,       // ���ܱ��ò���09
	EN_PARA_FUN_BAK10,       // ���ܱ��ò���10
	EN_PARA_FUN_BAK11,       // ���ܱ��ò���11
	EN_PARA_FUN_BAK12,       // ���ܱ��ò���12
	EN_PARA_FUN_BAK13,       // ���ܱ��ò���13
	EN_PARA_FUN_BAK14,       // ���ܱ��ò���14
	EN_PARA_FUN_BAK15,       // ���ܱ��ò���15
	EN_PARA_FUN_BAK16,       // ���ܱ��ò���16
	EN_PARA_FUN_BAK17,       // ���ܱ��ò���17
	EN_PARA_FUN_BAK18,       // ���ܱ��ò���18
	EN_PARA_FUN_BAK19,       // ���ܱ��ò���19
	EN_PARA_FUN_BAK20,       // ���ܱ��ò���20

	EN_PARA_FUN_END,
	
	EN_PARA_DC_COE_STR=EN_PARA_FUN_END,
	EN_PARA_DC_COE_END=EN_PARA_DC_COE_STR+CN_NUM_DC_SAM,
	
	EN_PARA_AM_COE_STR=EN_PARA_DC_COE_END,
	EN_PARA_AM_COE_END=EN_PARA_AM_COE_STR+CN_NUM_AD,
	
	EN_PARA_DCBC_COE_STR=EN_PARA_AM_COE_END,
	EN_PARA_DCBC_COE_END=EN_PARA_DCBC_COE_STR+CN_NUM_AD,
	
	EN_PARA_ANG_COE_STR=EN_PARA_DCBC_COE_END,
	EN_PARA_ANG_COE_END=EN_PARA_ANG_COE_STR+CN_NUM_JZ+CN_NUM_JZ,


	EN_PARA_END= EN_PARA_ANG_COE_END
};
// ��������
enum _BOARD_PARA_TYPE_
{
	EN_BOARD_PARA_STR=0,
	EN_BOARD_PARA_DI=EN_BOARD_PARA_STR,
	EN_BOARD_PARA_DC,
	EN_BOARD_PARA_SAM,
	EN_BOARD_PARA_FUN,
	// ֱ��У׼ϵ������һ��
	EN_BOARD_PARA_DC_COE,
	EN_BOARD_PARA_COM_END,
	// ģ����У׼ϵ������Ϊ����,�ڻָ�Ĭ��ʱ���໥Ӱ��
	EN_BOARD_PARA_AM_COE=EN_BOARD_PARA_COM_END,
	EN_BOARD_PARA_DCBC_COE,
	EN_BOARD_PARA_ANG_COE,
	EN_BOARD_PARA_END,
};
/*================================================================================*/
// ������ṹ��
/*================================================================================*/
typedef struct
{
	WORD            wIndex;                         // ��ֵ�����
	WORD            wType;                          // ��ֵ����
	INT32           iValMin;                        // ��Сֵ
	INT32           iValMax;                        // ���ֵ
	INT32           iValDft;                        // ȱʡֵ
//	WORD            wCoeRet;                        // ����ϵ����100��
	INT8S           byName[CN_LEN_NAME];            // ��ֵ����
	INT8S           byPinName[CN_LEN_NAME];         // ���������
}tagParaTab;
/*================================================================================*/
// ��������ṹ��
/*================================================================================*/
typedef struct
{
	WORD            wIndex;                         // ����ö�ٺ�
	WORD            wIndexStr;                      // ��������Դ��ʼö��
	WORD            wIndexEnd;                      // ��������Դ����ö��
	WORD            wIndexNum;                      // ������������
	WORD            wGroupNum;                      // ������������
	INT8S           byName[CN_LEN_NAME];            // ��������
	INT8S           byPinName[CN_LEN_NAME];         // ����̵�ַ
}tagBoardParaTab;

/*================================================================================*/
// �궨��
/*================================================================================*/
#define CN_NUM_PARA            (EN_PARA_END)
#define CN_NUM_BOARD_PARA_COM  (EN_BOARD_PARA_COM_END)// ��佻������
#define CN_NUM_BOARD_PARA      (EN_BOARD_PARA_END)
/*================================================================================*/
// ����������
/*================================================================================*/
extern  const tagParaTab         g_tParaTab[];
extern  const DWORD              g_NUM_PARA;
extern  const tagBoardParaTab    g_tBoardParaTab[];
extern  const DWORD              g_NUM_BOARD_PARA;



/*================================================================================*/
#endif  /* _CONST_PARA_H_ */
