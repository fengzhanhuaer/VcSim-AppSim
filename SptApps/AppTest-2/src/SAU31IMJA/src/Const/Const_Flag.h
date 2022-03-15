#ifndef _CONST_FLAG_H_
#define _CONST_FLAG_H_

#include "IES_IMtypes.h"
/*================================================================================*/
// �ź�ö��
/*================================================================================*/
enum _FLAG_NUMBER
{
    EN_FLAG_STR= 0,
    // �ϵ��־
    EN_FLAG_INIT=EN_FLAG_STR,
    //  �����־
    EN_FLAG_RESET_DI,
    EN_FLAG_RESET_GOIN,
    EN_FLAG_RESET_DBG,
	EN_FLAG_RESET_COM,
    EN_FLAG_RESET,

    EN_FLAG_ALM_COM,
    EN_FLAG_CHK_COM,
    EN_FLAG_DBG_COM,

    EN_FLAG_ALM,
    EN_FLAG_CHK,
    EN_FLAG_DBG,
    EN_FLAG_DO_ALM,
    EN_FLAG_DO_CHK,
    EN_FLAG_LED_RUN,
    EN_FLAG_LED_ALM,
    EN_FLAG_PARACHG,
    EN_FLAG_GOIN_BHBC,
    EN_FLAG_DI_KKJ,
    EN_FLAG_DI_STJ,
    EN_FLAG_DI_SHJ,
    EN_FLAG_BHTZ_DO,
/*****��������բ����ָʾ�ƺϲ�--STR*******/
    EN_FLAG_DI_TJF,
    EN_FLAG_BHTZ,
    EN_FLAG_BHHZ,
/*****��������բ����ָʾ�ƺϲ�--END*******/
    EN_FLAG_DO_BHBAK1,
    EN_FLAG_DO_BHBAK2,
    EN_FLAG_DO_BHBAK3,
    EN_FLAG_DO_BHBAK4,
    EN_FLAG_DO_BHBAK5_0,
//    EN_FLAG_DO_BHBAK5_1,
    
    EN_FLAG_LED_BAK21,
    EN_FLAG_LED_BAK22,
    EN_FLAG_LED_BAK23,
    EN_FLAG_LED_BAK24,
    EN_FLAG_LED_BAK31,
    EN_FLAG_LED_BAK32,
//  ����Ͷ��
    EN_FLAG_LNK_ENA,
    EN_FLAG_V_ENA,
    EN_FLAG_V_NULL,
    EN_FLAG_V_BC_INIT,
    EN_FLAG_V_BC,
    EN_FLAG_V_I,
    EN_FLAG_V_II,
    EN_FLAG_SV_A,
    EN_FLAG_SV_B,
    EN_FLAG_LNK_BC,
    EN_FLAG_LNK_A,
    EN_FLAG_LNK_B,
    EN_FLAG_END
};
enum _INTER_NUMBER
{
// �����ڲ���־����,����״̬�洢,������ͨ��
    EN_INTER_STR= 0,
    EN_INTER_SVSUB_CFG=EN_INTER_STR, // SV���������쳣
    EN_INTER_SVSUB_A_CHK,            // A��SV�����쳣
    EN_INTER_SVSUB_B_CHK,            // B��SV�����쳣
    EN_INTER_SVSUB_NOPUB,            // SV�޶���
    EN_INTER_SVSUB_PORT,             // SV���Ķ˿����ô�
    EN_INTER_SVSUB_NUMERR,           // SV���Ŀ��ƿ����Խ��
    EN_INTER_SVSUB_PARAERR,          // SV���Ŀ��ƿ�����쳣
    EN_INTER_SVSUB_ADRERR,           // SV���Ŀ��ƿ�̵�ַ��
    EN_INTER_SVSUB_CFGERR,           // SV���Ŀ��ƿ����ô�
    EN_INTER_SVSUB_1M_1LINKA,        // ��ĸ�߽�A�׶���
    EN_INTER_SVSUB_1M_1LINKB,        // ��ĸ�߽�B�׶���
    EN_INTER_SVSUB_1M_2LINK,         // ��ĸ��˫�׶���
    EN_INTER_SVSUB_2M_1LINKA,        // ˫ĸ�߽�A�׶���
    EN_INTER_SVSUB_2M_1LINKB,        // ˫ĸ�߽�B�׶���
    EN_INTER_SVSUB_2M_2LINK,         // ˫ĸ��˫�׶���
    EN_INTER_SVSUB_A_DIS,            // A��I/IIĸ���Ĳ�һ��
    EN_INTER_SVSUB_A_MULT,           // A��I/IIĸ����ƿ鶩��
    EN_INTER_SVSUB_B_DIS,            // B��I/IIĸ���Ĳ�һ��
    EN_INTER_SVSUB_B_MULT,           // B��I/IIĸ����ƿ鶩��
    EN_INTER_SVSUB_1M_DIS,           // IĸA/B�׶��Ĳ�һ��
    EN_INTER_SVSUB_2M_DIS,           // IIĸA/B�׶��Ĳ�һ��
    EN_INTER_SVSUB_A1_VALID,         // A��Iĸ��ѹ����������Ч
    EN_INTER_SVSUB_A1_CFG,           // A��Iĸ��ѹ�ж���
    EN_INTER_SVSUB_A1_LOSE,          // A��Iĸ��ѹδȫ����
    EN_INTER_SVSUB_A1_MULT,          // A��Iĸ��ѹ����ƿ鶩��
    EN_INTER_SVSUB_A2_VALID,         // A��IIĸ��ѹ����������Ч
    EN_INTER_SVSUB_A2_CFG,           // A��IIĸ��ѹ�ж���
    EN_INTER_SVSUB_A2_LOSE,          // A��IIĸ��ѹδȫ����
    EN_INTER_SVSUB_A2_MULT,          // A��IIĸ��ѹ����ƿ鶩��
    EN_INTER_SVSUB_B1_VALID,         // B��Iĸ��ѹ����������Ч
    EN_INTER_SVSUB_B1_CFG,           // B��Iĸ��ѹ�ж���
    EN_INTER_SVSUB_B1_LOSE,          // B��Iĸ��ѹδȫ����
    EN_INTER_SVSUB_B1_MULT,          // B��Iĸ��ѹ����ƿ鶩��
    EN_INTER_SVSUB_B2_VALID,         // B��IIĸ��ѹ����������Ч
    EN_INTER_SVSUB_B2_CFG,           // B��IIĸ��ѹ�ж���
    EN_INTER_SVSUB_B2_LOSE,          // B��IIĸ��ѹδȫ����
    EN_INTER_SVSUB_B2_MULT,          // B��IIĸ��ѹ����ƿ鶩��
    
    EN_INTER_SVPUB_CFG,              // SV���������쳣
    EN_INTER_SVPUB_PORT,             // SV�����˿����ô�
    EN_INTER_SVPUB_NUMERR,           // SV���Ŀ��ƿ����Խ��
    EN_INTER_SVPUB_PARAERR,          // SV���Ŀ��ƿ�����쳣
    EN_INTER_SVPUB_ADRERR,           // SV���Ŀ��ƿ�̵�ַ��
    EN_INTER_SVPUB_CFGERR,           // SV���Ŀ��ƿ����ô�
    EN_INTER_SVPUB_CHN_NUM,          // ������ͨ����Խ��
    EN_INTER_SVPUB_CHN_NO,           // ������ͨ����Խ��
    EN_INTER_SVPUB_DLY,              // ����ȱ��ͨ����ʱ
    EN_INTER_SVPUB_SUB,              // �����м���ͨ��
    EN_INTER_SVPUB_STD,              // ��׼SV(ĸ�ߵ�ѹ����)����
    EN_INTER_SVPUB_ANA,              // ��׼SV(ĸ�ߵ�ѹֱ��)����
    EN_INTER_SVPUB_M,                // ��׼SV(ĸ�߰��޵�ѹ����)����
    EN_INTER_SVPUB_CHK,              // �Ǳ�׼SV����
    
    EN_INTER_GOSUB_CFG,              // GOOSE�����쳣
    EN_INTER_GOSUB_PORT,             // GOOSE���Ķ˿����ô�
    EN_INTER_GOSUB_NUMERR,           // GOOSE���Ŀ��ƿ����Խ��
    EN_INTER_GOSUB_PARAERR,          // GOOSE���Ŀ��ƿ�����쳣
    EN_INTER_GOSUB_ADRERR,           // GOOSE���Ŀ��ƿ�̵�ַ��
    EN_INTER_GOSUB_CFGERR,           // GOOSE���Ŀ��ƿ����ô�
    EN_INTER_GOSUB_Dif,              // GOOSE���Ĳ�һ��
    EN_INTER_GOSUB_GOCB,             // GOOSE���Ŀ��ƿ����
    EN_INTER_GOSUB_V,                // GOOSE�����ж���
    EN_INTER_GOSUB_T,                // GOOSEʱ���ж���
    EN_INTER_GOSUB_Q,                // GOOSEƷ���ж���
    
    EN_INTER_GOPUB_CFG,              // GOOSE�����쳣
    EN_INTER_GOPUB_PORT,             // GOOSE�����˿����ô�
    EN_INTER_GOPUB_NUMERR,           // GOOSE���Ŀ��ƿ����Խ��
    EN_INTER_GOPUB_PARAERR,          // GOOSE���Ŀ��ƿ�����쳣
    EN_INTER_GOPUB_ADRERR,           // GOOSE���Ŀ��ƿ�̵�ַ��
    EN_INTER_GOPUB_CFGERR,           // GOOSE���Ŀ��ƿ����ô�
    EN_INTER_GOPUB_DI_LOSE,          // ����Ӳң��δȫ����
    EN_INTER_GOPUB_DI_T,             // ����Ӳң��ʱ��δȫ����
    EN_INTER_GOPUB_DI_Q,             // ����Ӳң����Ʒ�ʷ���
    EN_INTER_GOPUB_DI_Dif,           // ����Ӳң�ŷ�����һ��
    EN_INTER_GOPUB_DPI_LOSE,         // ˫��Ӳң��δȫ����
    EN_INTER_GOPUB_DPI_T,            // ˫��Ӳң��ʱ��δȫ����
    EN_INTER_GOPUB_DPI_Q,            // ˫��Ӳң����Ʒ�ʷ���
    EN_INTER_GOPUB_DPI_Dif,          // ˫��Ӳң�ŷ�����һ��
    EN_INTER_GOPUB_OUT_LOSE,         // ��ң��δȫ����
    EN_INTER_GOPUB_OUT_Q,            // ��ң����Ʒ�ʷ���
    EN_INTER_GOPUB_OUT_Dif,          // ��ң�ŷ�����һ��
    EN_INTER_GOPUB_DC_LOSE,          // ֱ��δȫ����
    EN_INTER_GOPUB_DC_Q,             // ֱ����Ʒ�ʷ���
    EN_INTER_GOPUB_DC_Dif,           // ֱ��������һ��
  
    EN_INTER_RUN_SV_BS,              // SV����
	EN_INTER_RUN_SV_ENA,             // SV����ʹ��
	EN_INTER_RUN_SV_ENA_ELSE,        // SV����ʹ�ܹ�
    EN_INTER_RUN_GO_BS,              // GOOSE����
    EN_INTER_RUN_GO_ENA,              // GOOSE����ʹ��
    EN_INTER_RUN_GO_ENA_ELSE,         // GOOSE����ʹ�ܹ�

	//	������־(���ڽ����޸�,�ж��в�����д����)
	
    EN_INTER_OPT_ANA,                 // ���ַ�ֵ�鿴
    EN_INTER_OPT_ANA_J,               // �����鿴
    EN_INTER_OPT_ANA_HUM,             // г���鿴
    EN_INTER_OPT_ANA_FR,              // Ƶ�ʲ鿴
    EN_INTER_POW_LOS,                 // װ�õ����־(˲ʱ)
    EN_INTER_POW_LOS_RLY,             // װ�õ����־(ȥ����)
    EN_INTER_POW_LOS_EVT,             // װ�õ�������

    EN_INTER_CPU2_CTRL,               // CPU�ӹܱ�־
    EN_INTER_CPU2_CTRL_ZK,            // �ǽӹ�״̬ZK��־����
    EN_INTER_CPU2_CTRL_DBG,
    EN_INTER_LCD_VIR,
    EN_INTER_END
};

/*================================================================================*/
// ������ṹ��
/*================================================================================*/
// ����Դö��������
#define CN_FLAG_SNUM  (32)   //
typedef struct
{
	WORD			wIndex; 					// ��־ö�ٺ�
	WORD			wSrcType;					// ����Դ����
	WORD			wSrcIndex[CN_FLAG_SNUM];	// ����Դö��
	WORD			wCalCfg;					// ��������
	WORD			wPara;						// ����ö��
	WORD			wCfg;						// ��־����
	INT8S			byName[CN_LEN_NAME];		// ��־��������
	INT8S			byPinName[CN_LEN_NAME];		// ��־�̵�ַ
} tagFlagTab;

typedef struct
{
	WORD			wIndex; 					// ��־ö�ٺ�
	WORD			wType; 						// ��������
	INT8S			byName[CN_LEN_NAME];		// ��־��������
	INT8S			byPinName[CN_LEN_NAME];		// ��־�̵�ַ
} tagInterTab;

/*================================================================================*/
// �궨��
/*================================================================================*/
#define CN_NUM_FLAG         (EN_FLAG_END)
#define CN_NUM_INTER        (EN_INTER_END)
// ��־�ϳɷ�ʽ
#define CN_FLAG_NULL (0)     // ������
#define CN_FLAG_OR   (DB0)   // ������
#define CN_FLAG_NO   (DB1)   // ������
#define CN_FLAG_BC   (DB2)   // ��������
#define CN_FLAG_MAT  (DB3)   // ��բ����
#define CN_FLAG_EQL  (DB4)   // ����
#define CN_FLAG_WID  (DB5)   // չ��

/*================================================================================*/
// ����������
/*================================================================================*/
extern const tagFlagTab   g_tFlagTab[];
extern const DWORD        g_NUM_FLAG;
extern const tagInterTab  g_tInterTab[];
extern const DWORD        g_NUM_INTER;
#endif/*_CONST_FLAG_H_*/

