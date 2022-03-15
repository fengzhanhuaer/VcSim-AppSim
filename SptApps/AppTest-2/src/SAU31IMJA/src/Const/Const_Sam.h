#ifndef _CONST_SAM_H_
#define _CONST_SAM_H_

#include "IES_IMtypes.h"
/*================================================================================*/
//ĸ�ߵ�ѹ����ö�٣����׼����һ��
/*================================================================================*/
enum _ANA_LINK_TYPE_
{
    EN_LINK_STR=0,           // ĸ�ߵ�ѹ��ʼ
    EN_LINK_UA1=EN_LINK_STR, // ĸ��A���ѹ AD1
    EN_LINK_UA2,             // ĸ��A���ѹ AD2
    EN_LINK_UB1,             // ĸ��B���ѹ AD1
    EN_LINK_UB2,             // ĸ��B���ѹ AD2
    EN_LINK_UC1,             // ĸ��C���ѹ AD1
    EN_LINK_UC2,             // ĸ��C���ѹ AD2
    EN_LINK_U01,             // ĸ�������ѹ AD1
    EN_LINK_U02,             // ĸ�������ѹ AD2
    EN_LINK_UAJ,             // ĸ��A�������ѹ
    EN_LINK_UBJ,             // ĸ��B�������ѹ
    EN_LINK_UCJ,             // ĸ��C�������ѹ
    EN_LINK_END              // ĸ�ߵ�ѹ����
};

/*================================================================================*/
//ģ�����ź�ö��
/*================================================================================*/
enum _ANA_INDEX_TYPE_
{
    EN_ANA_START,                              //
// 1.����ģ����ͨ��
    EN_ANA_SAM_STR=EN_ANA_START,               // ���ز�����ʼ
    EN_ANA_UA1=EN_ANA_SAM_STR,                 // �������Ua AD1
    EN_ANA_UA2,                                // �������UA AD2
    EN_ANA_UB1,                                // �������Ub AD1
    EN_ANA_UB2,                                // �������UB AD2
    EN_ANA_UC1,                                // �������Uc AD1
    EN_ANA_UC2,                                // �������UC AD2
    EN_ANA_U01,                                // ����3U0 AD1
    EN_ANA_U02,                                // ����3U0 AD2
    EN_ANA_UX1,                                // ͬ��Ux AD1
    EN_ANA_UX2,                                // ͬ��UX AD2
    EN_ANA_UAJ,                                // ����UAj
    EN_ANA_UBJ,                                // ����UBj
    EN_ANA_UCJ,                                // ����UCj
    EN_ANA_1_IA1,                              // ����IA1 AD1
    EN_ANA_1_IA2,                              // ����IA1 AD2
    EN_ANA_1_IB1,                              // ����IB1 AD1
    EN_ANA_1_IB2,                              // ����IB1 AD2
    EN_ANA_1_IC1,                              // ����IC1 AD1
    EN_ANA_1_IC2,                              // ����IC1 AD2
    EN_ANA_IAJ,                                // ��������IAj
    EN_ANA_IBJ,                                // ��������IBj
    EN_ANA_ICJ,                                // ��������ICj
    EN_ANA_2_IA1,                              // ����IA2 AD1
    EN_ANA_2_IA2,                              // ����IA2 AD2
    EN_ANA_2_IB1,                              // ����IB2 AD1
    EN_ANA_2_IB2,                              // ����IB2 AD2
    EN_ANA_2_IC1,                              // ����IC2 AD1
    EN_ANA_2_IC2,                              // ����IC2 AD2
    EN_ANA_SAM_END,
// 2.��׼ͨ��
    EN_ANA_JZ_STR=EN_ANA_SAM_END,
    EN_ANA_JZ1=EN_ANA_JZ_STR,                  // AD1��׼��ѹ
    EN_ANA_JZ2,                                // AD2��׼��ѹ
    EN_ANA_JZ3,                                // AD3��׼��ѹ
    EN_ANA_JZ4,                                // AD4��׼��ѹ
    EN_ANA_JZ5,                                // AD5��׼��ѹ
    EN_ANA_JZ_END,
// 3.SV����ͨ��
//  ע�⣺������ĸ�ߵ�ѹ˳�򲻿ɵ���--STR
    // A�׼�������
#if(CN_DEV_CPU1)
    EN_ANA_SV_STR  =EN_ANA_JZ_END,
    EN_ANA_SVA_STR =EN_ANA_SV_STR,
    EN_ANA_SVA1_STR=EN_ANA_SVA_STR,              // A�ע�ĸ��ѹ��ʼ
    EN_ANA_SVA1_UA1=EN_ANA_SVA1_STR+EN_LINK_UA1,// A�ע�ĸA���ѹ AD1
    EN_ANA_SVA1_UA2=EN_ANA_SVA1_STR+EN_LINK_UA2,// A�ע�ĸA���ѹ AD2
    EN_ANA_SVA1_UB1=EN_ANA_SVA1_STR+EN_LINK_UB1,// A�ע�ĸB���ѹ AD1
    EN_ANA_SVA1_UB2=EN_ANA_SVA1_STR+EN_LINK_UB2,// A�ע�ĸB���ѹ AD2
    EN_ANA_SVA1_UC1=EN_ANA_SVA1_STR+EN_LINK_UC1,// A�ע�ĸC���ѹ AD1
    EN_ANA_SVA1_UC2=EN_ANA_SVA1_STR+EN_LINK_UC2,// A�ע�ĸC���ѹ AD2
    EN_ANA_SVA1_U01=EN_ANA_SVA1_STR+EN_LINK_U01,// A�ע�ĸ�����ѹ AD1
    EN_ANA_SVA1_U02=EN_ANA_SVA1_STR+EN_LINK_U02,// A�ע�ĸ�����ѹ AD2
    EN_ANA_SVA1_UAJ=EN_ANA_SVA1_STR+EN_LINK_UAJ,// A�ע�ĸA�������ѹ
    EN_ANA_SVA1_UBJ=EN_ANA_SVA1_STR+EN_LINK_UBJ,// A�ע�ĸB�������ѹ
    EN_ANA_SVA1_UCJ=EN_ANA_SVA1_STR+EN_LINK_UCJ,// A�ע�ĸC�������ѹ
    EN_ANA_SVA2_STR=EN_ANA_SVA1_STR+EN_LINK_END,// A�ע�ĸ��ѹ��ʼ
    EN_ANA_SVA2_UA1=EN_ANA_SVA2_STR+EN_LINK_UA1,// A�ע�ĸA���ѹ AD1
    EN_ANA_SVA2_UA2=EN_ANA_SVA2_STR+EN_LINK_UA2,// A�ע�ĸA���ѹ AD2
    EN_ANA_SVA2_UB1=EN_ANA_SVA2_STR+EN_LINK_UB1,// A�ע�ĸB���ѹ AD1
    EN_ANA_SVA2_UB2=EN_ANA_SVA2_STR+EN_LINK_UB2,// A�ע�ĸB���ѹ AD2
    EN_ANA_SVA2_UC1=EN_ANA_SVA2_STR+EN_LINK_UC1,// A�ע�ĸC���ѹ AD1
    EN_ANA_SVA2_UC2=EN_ANA_SVA2_STR+EN_LINK_UC2,// A�ע�ĸC���ѹ AD2
    EN_ANA_SVA2_U01=EN_ANA_SVA2_STR+EN_LINK_U01,// A�ע�ĸ�����ѹ AD1
    EN_ANA_SVA2_U02=EN_ANA_SVA2_STR+EN_LINK_U02,// A�ע�ĸ�����ѹ AD2
    EN_ANA_SVA2_UAJ=EN_ANA_SVA2_STR+EN_LINK_UAJ,// A�ע�ĸA�������ѹ
    EN_ANA_SVA2_UBJ=EN_ANA_SVA2_STR+EN_LINK_UBJ,// A�ע�ĸB�������ѹ
    EN_ANA_SVA2_UCJ=EN_ANA_SVA2_STR+EN_LINK_UCJ,// A�ע�ĸC�������ѹ
    EN_ANA_SVA_END =EN_ANA_SVA2_STR+EN_LINK_END,
    // B �׼�������
    EN_ANA_SVB_STR=EN_ANA_SVA_END,
    EN_ANA_SVB1_STR=EN_ANA_SVA2_STR+EN_LINK_END,// B�ע�ĸ��ѹ��ʼ
    EN_ANA_SVB1_UA1=EN_ANA_SVB1_STR+EN_LINK_UA1,// B�ע�ĸA���ѹ AD1
    EN_ANA_SVB1_UA2=EN_ANA_SVB1_STR+EN_LINK_UA2,// B�ע�ĸA���ѹ AD2
    EN_ANA_SVB1_UB1=EN_ANA_SVB1_STR+EN_LINK_UB1,// B�ע�ĸB���ѹ AD1
    EN_ANA_SVB1_UB2=EN_ANA_SVB1_STR+EN_LINK_UB2,// B�ע�ĸB���ѹ AD2
    EN_ANA_SVB1_UC1=EN_ANA_SVB1_STR+EN_LINK_UC1,// B�ע�ĸC���ѹ AD1
    EN_ANA_SVB1_UC2=EN_ANA_SVB1_STR+EN_LINK_UC2,// B�ע�ĸC���ѹ AD2
    EN_ANA_SVB1_U01=EN_ANA_SVB1_STR+EN_LINK_U01,// B�ע�ĸ�����ѹ AD1
    EN_ANA_SVB1_U02=EN_ANA_SVB1_STR+EN_LINK_U02,// B�ע�ĸ�����ѹ AD2
    EN_ANA_SVB1_UAJ=EN_ANA_SVB1_STR+EN_LINK_UAJ,// B�ע�ĸA�������ѹ
    EN_ANA_SVB1_UBJ=EN_ANA_SVB1_STR+EN_LINK_UBJ,// B�ע�ĸB�������ѹ
    EN_ANA_SVB1_UCJ=EN_ANA_SVB1_STR+EN_LINK_UCJ,// B�ע�ĸC�������ѹ
    
    EN_ANA_SVB2_STR=EN_ANA_SVB1_STR+EN_LINK_END,// B�ע�ĸ��ѹ��ʼ
    EN_ANA_SVB2_UA1=EN_ANA_SVB2_STR+EN_LINK_UA1,// B�ע�ĸA���ѹ AD1
    EN_ANA_SVB2_UA2=EN_ANA_SVB2_STR+EN_LINK_UA2,// B�ע�ĸA���ѹ AD2
    EN_ANA_SVB2_UB1=EN_ANA_SVB2_STR+EN_LINK_UB1,// B�ע�ĸB���ѹ AD1
    EN_ANA_SVB2_UB2=EN_ANA_SVB2_STR+EN_LINK_UB2,// B�ע�ĸB���ѹ AD2
    EN_ANA_SVB2_UC1=EN_ANA_SVB2_STR+EN_LINK_UC1,// B�ע�ĸC���ѹ AD1
    EN_ANA_SVB2_UC2=EN_ANA_SVB2_STR+EN_LINK_UC2,// B�ע�ĸC���ѹ AD2
    EN_ANA_SVB2_U01=EN_ANA_SVB2_STR+EN_LINK_U01,// B�ע�ĸ�����ѹ AD1
    EN_ANA_SVB2_U02=EN_ANA_SVB2_STR+EN_LINK_U02,// B�ע�ĸ�����ѹ AD2
    EN_ANA_SVB2_UAJ=EN_ANA_SVB2_STR+EN_LINK_UAJ,// B�ע�ĸA�������ѹ
    EN_ANA_SVB2_UBJ=EN_ANA_SVB2_STR+EN_LINK_UBJ,// B�ע�ĸB�������ѹ
    EN_ANA_SVB2_UCJ=EN_ANA_SVB2_STR+EN_LINK_UCJ,// B�ע�ĸC�������ѹ
    EN_ANA_SVB_END=EN_ANA_SVB2_STR+EN_LINK_END,
    EN_ANA_SV_END=EN_ANA_SVB_END,
#elif(CN_DEV_CPU2)
    EN_ANA_SV_STR  =EN_ANA_JZ_END,
    EN_ANA_SVA_STR =EN_ANA_SV_STR,
    EN_ANA_SVA1_STR=EN_ANA_SVA_STR, 			 // A�ע�ĸ��ѹ��ʼ
    EN_ANA_SVA1_UA1=EN_ANA_SVA1_STR+EN_LINK_UA1,// A�ע�ĸA���ѹ AD1
    EN_ANA_SVA1_UA2=EN_ANA_SVA1_STR+EN_LINK_UA2,// A�ע�ĸA���ѹ AD2
    EN_ANA_SVA1_UB1=EN_ANA_SVA1_STR+EN_LINK_UB1,// A�ע�ĸB���ѹ AD1
    EN_ANA_SVA1_UB2=EN_ANA_SVA1_STR+EN_LINK_UB2,// A�ע�ĸB���ѹ AD2
    EN_ANA_SVA1_UC1=EN_ANA_SVA1_STR+EN_LINK_UC1,// A�ע�ĸC���ѹ AD1
    EN_ANA_SVA1_UC2=EN_ANA_SVA1_STR+EN_LINK_UC2,// A�ע�ĸC���ѹ AD2
    EN_ANA_SVA1_U01=EN_ANA_SVA1_STR+EN_LINK_U01,// A�ע�ĸ�����ѹ AD1
    EN_ANA_SVA1_U02=EN_ANA_SVA1_STR+EN_LINK_U02,// A�ע�ĸ�����ѹ AD2
    EN_ANA_SVA1_UAJ=EN_ANA_SVA1_STR+EN_LINK_UAJ,// A�ע�ĸA�������ѹ
    EN_ANA_SVA1_UBJ=EN_ANA_SVA1_STR+EN_LINK_UBJ,// A�ע�ĸB�������ѹ
    EN_ANA_SVA1_UCJ=EN_ANA_SVA1_STR+EN_LINK_UCJ,// A�ע�ĸC�������ѹ
    EN_ANA_SVA1_END=EN_ANA_SVA1_STR+EN_LINK_END,
    EN_ANA_SV_END  =EN_ANA_SVA1_END,
#endif
    //  ע�⣺������ĸ�ߵ�ѹ˳�򲻿ɵ���--end
    EN_ANA_END=EN_ANA_SV_END
};
/*================================================================================*/
//�����ź�ö��
/*================================================================================*/
enum _CAL_INDEX_TYPE_
{
//  ֱ��ģ����ͨ��
    EN_CAL_START=0,                           //
    EN_CAL_A1_F1=EN_CAL_START,                //
    EN_CAL_A1_F2,                             //
#if(CN_DEV_CPU1)
    EN_CAL_A2_F1,                             //
    EN_CAL_A2_F2,                             //
    EN_CAL_B1_F1,                             //
    EN_CAL_B1_F2,                             //
    EN_CAL_B2_F1,                             //
    EN_CAL_B2_F2,                             //
#endif
    EN_CAL_J1_F1,                             //
    EN_CAL_J1_F2,                             //
    EN_CAL_Ux_F1,                             //
    EN_CAL_Ux_F2,                             //
    EN_CAL_END
};
#define  CN_TCHG_ENA   (1)// �¶ȵ���ϵ������

#if(CN_TCHG_ENA)
// �¶ȵ���ϵ������
enum _TCHG_INDEX_TYPE_
{
    EN_TCHG_MOD1=0,
    EN_TCHG_MOD2,
    EN_TCHG_MOD3,
    EN_TCHG_END,
};
#endif
/*================================================================================*/
//ģ������ذ忨ö��
/*================================================================================*/
enum _BOARD_ANA_TYPE_
{
    EN_BOARD_SAM_PTCT1=0,
    EN_BOARD_SAM_PTCT2,
    EN_BOARD_SAM_CPU,     //��׼
    EN_BOARD_SAM_END,
    EN_BOARD_SV_SVA=0,
    EN_BOARD_SV_SVB,
    EN_BOARD_SV_END
};
/*================================================================================*/
//������ṹ��
/*================================================================================*/
// ģ����������Ϣ�����ݽṹ
typedef struct
{
	WORD            wIndex;                         // ģ����ö�ٺ�
	WORD            wChanType;                      // ģ������������
	WORD            wParaFst;                       // �����Ķһ��ֵ����
	WORD            wParaScd;                       // �����Ķ����ֵ����
	WORD            wFrmNo;                         // ����Դ--֡����
	WORD            wADNo;                          // ����Դ--ADоƬ����
	WORD            wADChn;                         // ����Դ--ADоƬͨ������
	DWORD           dwCfg;                          // ͨ����������
	INT8S           byName[CN_LEN_NAME];            // ģ��������
	INT8S           byPinName[CN_LEN_NAME];         // ģ�����̵�ַ
} tagAnaTab;
// ���㳣����ṹ��
typedef struct
{
	WORD            wIndex;                         // ������ö�ٺ�
	WORD            wChanType;                      // ����������
	WORD            wSrcDType;                      // ����Դ����
	WORD            wSrcIndex[3];                   // ����Դö��
	WORD            wParaIndex;                     // ��������������
	INT8S           byName[CN_LEN_NAME];            // ����������
	INT8S           byPinName[CN_LEN_NAME];         // �������̵�ַ
} tagCalTab;
// SV����
typedef struct
{
	WORD            wStdIndex;                         // SV������׼����ö��
	WORD            wAnaIndex;                         // SV����ȡģ����ĸ�ߵ�ѹö��
	WORD            wAnaIndex2;                        // SV������ĸ�ߵ�ѹö��
	
} tagSvPubTab;
// �忨���ó�����ṹ��
typedef struct
{
	WORD            wIndex;                         // �忨ö�ٺ�
	INT8S           byName[CN_LEN_NAME];            // �忨����
	INT8S           byPinName[CN_LEN_NAME];         // �忨�̵�ַ
	WORD            wIndexNum;                      // ͨ������
} tagBoardAnaTab;

/*================================================================================*/
// �궨��
/*================================================================================*/
// ͨ���������궨��
#define CN_NUM_SAM          (EN_ANA_SAM_END-EN_ANA_SAM_STR)   // ������ͨ����
#define CN_NUM_JZ           (EN_ANA_JZ_END-EN_ANA_JZ_STR)     // ��׼ͨ����
#define CN_NUM_AD           (CN_NUM_SAM+CN_NUM_JZ)            // ����ͨ������
#define CN_NUM_SV           (EN_ANA_SV_END-EN_ANA_SV_STR)     // SV����ͨ����
#define CN_NUM_ANA          (EN_ANA_END)                      // SV�������������ͨ��
#define CN_NUM_CAL          (EN_CAL_END)                      // ������ͨ����
#define CN_NUM_BOARD_SAM    (EN_BOARD_SAM_END)                // ���ģ�����忨����
#define CN_NUM_BOARD_SV     (EN_BOARD_SV_END)                 // ����������忨����
// AD��ʱ��׼ͨ��
#define CN_BASE_AD         (EN_ANA_UA1)                       // AD��׼ͨ��
// �������ú궨��
#define CN_SAM_RATE         (80)                              // �����ڲ�������
#define CN_SAM_NUM          (2)                               // ��������
#define CN_SAM_LEN          (CN_SAM_RATE*CN_SAM_NUM)          // ���泤��
// г����غ궨��
#define CN_HUM_ENA          (0)                               // г������Ͷ��
#define CN_HUM_NUM          (13)                              // г���������

#define CN_DFT_COE          (0.01767767f)                     // ȫ�ܸ�ʽ�̶�ϵ����2/80
#define CN_DFT_BIT          (20)                              // ȫ�ܸ�ʽ�̶�ϵ��ƽ��λ��
#define CN_SV_U_Unit        (0.01f)                           // SV��ѹ��С��λ(10mV)
#define CN_SV_I_Unit        (0.001f)                          // SV������С��λ(1mA)
// ģ������ʾ����
#define CN_SAM_DIV_U        (3)                               // ��ѹ��ʾ���ݱ���
#define CN_SAM_DIV_I        (3)                               // ������ʾ���ݱ���
#define CN_SAM_DIV_F        (2)                               // Ƶ����ʾ���ݱ���
#define CN_SAM_DIV_Ang      (3)                               // ��λ��ʾ���ݱ���
// ��Ƶ��غ궨��
#define CN_CAL_F_UMk        (1000)                            // ��ѹ��Ƶ�ż� 1V
#define CN_CAL_F_Coe        (g_dwMul[CN_SAM_DIV_F])           // ��Ƶ���㱶��
#define CN_CAL_F_QD         (3)                               // ��Ƶ�����ܲ���
#define CN_CAL_F_CNT        (50*CN_SAM_RATE)                  // ��׼����Ƶ��
// ��׼��ѹѡ���ż� 0.2V
#define CN_BASE_UMK          (200)                            // ��׼��ѹ�ż�0.2V
#define CN_BASE_IMK          (4)                              // ��׼�����ż�0.004A
#define CN_SV_IN_ENA         (TRUE)                           // SV���Ĺ���Ͷ��
#define CN_NUM_SVCB_SUB      (2)                              // SV���Ŀ��ƿ����
#define CN_NUM_SVCB_PUB      (2)                              // SV�������ƿ����
// SV���ʱ
#define CN_SVPUB_TIME_LINK   (1876)                           // SV���ʱ(���м�������)
#define CN_SVPUB_TIME        (876)                            // SV���ʱ(�޼�������)
// SV������
#define CN_SVCFG_CfgErr       (DB0)                             // bit0 ƽ̨�ṩ--�����쳣
#define CN_SVCFG_ParseErr     (DB1)                             // bit1 ƽ̨�ṩ--�����쳣��
#define CN_SVCFG_DataErr      (CN_SVCFG_CfgErr+CN_SVCFG_ParseErr)
// SVSUB���ƿ�״̬��
#define CN_SVCB_NO            (0xf)                           // bit0~bit3  ���ƿ����
#define CN_SVCB_NetPort       (0xf0)                          // bit4~bit7  ����˿�
#define CN_SVCB_LinkErr1      (DB8)                           // bit8 �����жϡ�1��������0��������
#define CN_SVCB_APPIDErr      (DB9)                           // bit9 APPID������ƥ�䡣1����ƥ�䣻0��������
#define CN_SVCB_SVIDErr       (DB10)                          // bit10 SVID������ƥ�䡣1����ƥ�䣻0��������
#define CN_SVCB_ConfRevErr    (DB11)                          // bit11 ConfRev������ƥ�䡣1����ƥ�䣻0��������
#define CN_SVCB_DataNumErr    (DB12)                          // bit12 DataNum������ƥ�䡣1����ƥ�䣻0��������
#define CN_SVCB_DataSetErr    (DB13)                          // bit13 DataSet������ƥ�䡣1����ƥ�䣻0��������
#define CN_SVCB_DtErr         (DB14)                          // bit14 ͨ�������쳣����(��20ms)��
#define CN_SVCB_SamCntErr     (DB15)                          // bit15 SamCnt����1������0��������
#define CN_SVCB_SynErr        (DB16)                          // bit16 ͬ����ʧָʾ��1��ͬ���쳣��0��������
#define CN_SVCB_Invalid       (DB17)                          // bit17 ������Ч��1��������Ч��0��������
#define CN_SVCB_Test          (DB18)                          // bit18 ���ݼ��ޡ�1�����ݼ��ޣ�0��������
#define CN_SVCB_DlyErr        (DB19)                          // bit19 ����ʱԽ�޻�һ�¡�1����һ�£�0��������
#define CN_SVCB_CommErr       (DB20)                          // bit20 ƽ̨�ṩ--ͨ���쳣
#define CN_SVCB_TypeErr       (DB21)                          // bit21 ƽ̨�ṩ--֡�����쳣��
#define CN_SVCB_CfgErr        (DB22)                          // bit22 ƽ̨�ṩ--�ϵ��ʼ�������쳣��
                                                              // bit23~bit30 ����
#define CN_SVCB_Ena           (DB31)                          // bit31 ���ƿ�ʹ��,1��ʹ�� 0��δʹ��

// SV���ƿ��쳣���� ������ʧ��������
#define CN_SVCB_DataErr      (CN_SVCB_APPIDErr+CN_SVCB_SVIDErr+CN_SVCB_ConfRevErr+   \
	CN_SVCB_DataNumErr+CN_SVCB_DataSetErr+CN_SVCB_DtErr+CN_SVCB_SamCntErr+CN_SVCB_Invalid+ \
    CN_SVCB_CommErr+CN_SVCB_TypeErr+CN_SVCB_CfgErr)
    
// SV���ƿ��쳣������SV����ͨ����Ч,������Ʒ����Ч�����ޡ�ʧ��
#define CN_SVCB_Link_QErr      (CN_SVCB_LinkErr1+CN_SVCB_APPIDErr+CN_SVCB_SVIDErr+CN_SVCB_ConfRevErr+   \
		CN_SVCB_DataNumErr+CN_SVCB_DataSetErr+CN_SVCB_DtErr+CN_SVCB_SamCntErr+ \
		CN_SVCB_CommErr+CN_SVCB_TypeErr+CN_SVCB_CfgErr)

// IEC61850-9-2Ʒ��ֵ���ݶ�λ
#define CN_SV_Q_VALIDL       (DB0)                           // ��Ч����λ(good/invalid/reserved/questionable) 00-���� 01-��Ч 10-���� 11-����
#define CN_SV_Q_VALIDH       (DB1)                           // ��Ч����λ(good/invalid/reserved/questionable) 00-���� 01-��Ч 10-���� 11-����
#define CN_SV_Q_DETAIL01     (DB2)                           // ϸ��Ʒ��01λ(overflow)0--  �������1--���
#define CN_SV_Q_DETAIL02     (DB3)                           // ϸ��Ʒ��02λ(outOfRange)0--  ������Χ��1--��ֵ��
#define CN_SV_Q_DETAIL03     (DB4)                           // ϸ��Ʒ��03λ(badReference)0--  ��׼������1--����׼ֵ
#define CN_SV_Q_DETAIL04     (DB5)                           // ϸ��Ʒ��04λ(oscillatory)0--  �޶�����1--����
#define CN_SV_Q_DETAIL05     (DB6)                           // ϸ��Ʒ��05λ(failure)0--  �޹��ϣ�1--����
#define CN_SV_Q_DETAIL06     (DB7)                           // ϸ��Ʒ��06λ(oldData)0--  �޳�ʱ��1--���ݳ�ʱ
#define CN_SV_Q_DETAIL07     (DB8)                           // ϸ��Ʒ��07λ(inconsistent)0--һ�£�1--��һ��
#define CN_SV_Q_DETAIL08     (DB9)                           // ϸ��Ʒ��08λ(inaccurate)0--  ��ȷ��1--����ȷ
#define CN_SV_Q_SOURCE       (DB10)                          // ����Դ(process/substituted)0--  ���̣�1--ȡ��
#define CN_SV_Q_TEST         (DB11)                          // ����λ0--  ���У�1--����
#define CN_SV_Q_OPBLK        (DB12)                          // ����Ա����
// ˽��Ʒ��
#define CN_SV_Q_VCLR         (DB15)                          // ˽��Ʒ��(����ͨ����������)

// ��������
#define CN_SV_Pub_Index1      (0x7f)                          // ����--ͨ��1(������) bit0-bit6
#define CN_SV_Pub_Index2      (0x3f10)                        // ����--ͨ��2(����) bit7-bit13
#define CN_SV_Pub_Pol         (DB14)                          // ����--��������
#define CN_SV_Pub_Cal         (DB15)                          // ����--��������
// ��������
#define CN_SV_OPT_NULL        (0)                             // ������������--�޲���
#define CN_SV_OPT_POL_S       (DB0)                           // ������������--���Ա仯�ɹ�
#define CN_SV_OPT_CHG1_S      (DB1)                           // ������������--�����л��ɹ�
#define CN_SV_OPT_CHG2_S      (DB2)                           // ������������--��ѹ�л��ɹ�
#define CN_SV_OPT_CAL_S       (DB3)                           // ������������--�ߵ�ѹ�����ɹ�
#define CN_SV_OPT_CHG1_F      (DB8)                           // ������������--�����л�ʧ��
#define CN_SV_OPT_CHG2_F      (DB9)                           // ������������--��ѹ�л�ʧ��
#define CN_SV_OPT_CAL_F       (DB10)                          // ������������--�ߵ�ѹ����ʧ��
// ���������ɹ�
#define CN_SV_OPT_S           (CN_SV_OPT_POL_S+CN_SV_OPT_CHG1_S+CN_SV_OPT_CHG2_S+CN_SV_OPT_CAL_S)
// ��������ʧ��
#define CN_SV_OPT_F           (CN_SV_OPT_CHG1_F+CN_SV_OPT_CHG2_F+CN_SV_OPT_CAL_F)
/*================================================================================*/
// ��������
/*================================================================================*/
extern const tagAnaTab    g_tAnaTab[];
extern const DWORD        g_NUM_ANA;

extern const tagCalTab    g_tCalTab[];
extern const DWORD        g_NUM_CAL;

extern const tagSvPubTab  g_tSvPubTab[];
extern const DWORD        g_NUM_SVPUB;

extern const tagBoardAnaTab  g_tBoardSamTab[];
extern const DWORD           g_NUM_BOARDSAM;
#if 0
extern const tagBoardAnaTab  g_tBoardSvTab[];
extern const DWORD           g_NUM_BOARDSV;
#endif
extern const INT64      g_iCos80[CN_SAM_RATE];
extern const INT64      g_iSin80[CN_SAM_RATE];

/*================================================================================*/
#endif /* _CONST_SAM_H_ */
