#ifndef _CONST_IO_H_
#define _CONST_IO_H_

/*================================================================================*/
// �����ź�ö��
/*================================================================================*/
// Ӳ�����ź�ö��
enum _DI_NUMBER
{
	EN_DI_STR = 0,
/*=============================*/
// DWORD1.�����1ö��
/*=============================*/
	EN_DI_BOARD1_STR = EN_DI_STR,
	EN_DI_TEST = EN_DI_BOARD1_STR,   // ����״̬Ӳѹ��
	EN_DI_RESET,                     // �źŸ���
	EN_DI_XCBR_OPN,
	EN_DI_XCBR_CLS,
	//��բλ��
	EN_DI_XSWI01_OPN,
	EN_DI_XSWI01_CLS,
	EN_DI_XSWI02_OPN,
	EN_DI_XSWI02_CLS,
	EN_DI_XSWI03_OPN,
	EN_DI_XSWI03_CLS,
	EN_DI_XSWI04_OPN,
	EN_DI_XSWI04_CLS,
	EN_DI_XSWI05_OPN,
	EN_DI_XSWI05_CLS,
	EN_DI_XSWI06_OPN,
	EN_DI_XSWI06_CLS,
	EN_DI_XSWI07_OPN,
	EN_DI_XSWI07_CLS,
	EN_DI_XSWI08_OPN,
	EN_DI_XSWI08_CLS,
	EN_DI_BC_YLD,     // ѹ���ͱ���
	EN_DI_BC_OTH,     // ��һ�ױ���
	EN_DI_TJF,        // TJF��բ�ź�
	EN_DI_STJ,        // ����
	EN_DI_SHJ,        // �ֺ�
	EN_DI_KKJ,        // �Ϻ�
	EN_DI_LNK_A,      // ȡA��
	EN_DI_LNK_B,      // ȡB��
	EN_DI_LNK_AUTO,   // �Զ�
	EN_DI_SHJ_SYN,    // �ֺ�ͬ�ڿ���
	EN_DI_POW1,       // �����1ң�ŵ�Դ����
	EN_DI_BOARD1_END,
/*==============================*/
// DWORD2.�����2ö��
/*=============================*/
	EN_DI_BOARD2_STR=EN_DI_BOARD1_END,
	//���ÿ���
	EN_DI_OTH_ALM=EN_DI_BOARD2_STR,    // ��һ�ײɼ�ִ�е�Ԫ�����쳣
	EN_DI_OTH_CHK,                     // ��һ�ײɼ�ִ�е�Ԫ����
	EN_DI_YX_BAK01,
	EN_DI_YX_BAK02,
	EN_DI_YX_BAK03,
	EN_DI_YX_BAK04,
	EN_DI_YX_BAK05,
	EN_DI_YX_BAK06,
	EN_DI_YX_BAK07,
	EN_DI_YX_BAK08,
	EN_DI_YX_BAK09,
	EN_DI_YX_BAK10,
	EN_DI_YX_BAK11,
	EN_DI_YX_BAK12,
	EN_DI_YX_BAK13,
	EN_DI_YX_BAK14,
	EN_DI_YX_BAK15,
	EN_DI_YX_BAK16,
	EN_DI_YX_BAK17,
	EN_DI_YX_BAK18,
	EN_DI_YX_BAK19,
	EN_DI_YX_BAK20,
	EN_DI_YX_BAK21,
	EN_DI_YX_BAK22,
	EN_DI_YX_BAK23,
	EN_DI_YX_BAK24,
	EN_DI_YX_BAK25,
	EN_DI_YX_BAK26,
	EN_DI_YX_BAK27,
	EN_DI_YX_BAK28,
	EN_DI_POW2,       // �����2ң�ŵ�Դ����
	EN_DI_BOARD2_END,
/*==============================*/
// DWORD3.�����3ö��
/*=============================*/
	EN_DI_BOARD3_STR=EN_DI_BOARD2_END,
	EN_DI_YX_BAK29=EN_DI_BOARD3_STR,
	EN_DI_YX_BAK30,
	EN_DI_YX_BAK31,
	EN_DI_YX_BAK32,
	EN_DI_YX_BAK33,
	EN_DI_YX_BAK34,
	EN_DI_YX_BAK35,
	EN_DI_YX_BAK36,
	EN_DI_YX_BAK37,
	EN_DI_YX_BAK38,
	EN_DI_YX_BAK39,
	EN_DI_YX_BAK40,
	EN_DI_YX_BAK41,
	EN_DI_YX_BAK42,
	EN_DI_YX_BAK43,
	EN_DI_YX_BAK44,
	EN_DI_YX_BAK45,
	EN_DI_YX_BAK46,
	EN_DI_YX_BAK47,
	EN_DI_YX_BAK48,
	EN_DI_YX_BAK49,
	EN_DI_YX_BAK50,
	EN_DI_YX_BAK51,
	EN_DI_YX_BAK52,
	EN_DI_YX_BAK53,
	EN_DI_YX_BAK54,
	EN_DI_YX_BAK55,
	EN_DI_YX_BAK56,
	EN_DI_YX_BAK57,
	EN_DI_YX_BAK58,
	EN_DI_POW3,       // �����3ң�ŵ�Դ����
	EN_DI_BOARD3_END,
/*==============================*/
// DWORD4.���뿪����ö��--���벿��
/*=============================*/
	EN_DI_BOARD4_STR=EN_DI_BOARD3_END,
	EN_DI_YX_BAK59=EN_DI_BOARD4_STR,
	EN_DI_YX_BAK60,
	EN_DI_YX_BAK61,
	EN_DI_YX_BAK62,
	EN_DI_YX_BAK63,
	EN_DI_YX_BAK64,
	EN_DI_YX_BAK65,
	EN_DI_YX_BAK66,
	EN_DI_YX_BAK67,
	EN_DI_YX_BAK68,
	EN_DI_YX_BAK69,
	EN_DI_YX_BAK70,
	EN_DI_YX_BAK71,
	EN_DI_POW4,        // ���뿪����ң�ŵ�Դ����
//	EN_DI_YX_BAK72,
//	EN_DI_YX_BAK73,
//	EN_DI_YX_BAK74,
//	EN_DI_YX_BAK75,
//	EN_DI_YX_BAK76,
//	EN_DI_YX_BAK77,
//	EN_DI_YX_BAK78,
//	EN_DI_YX_BAK79,
//	EN_DI_YX_BAK80,
//	EN_DI_YX_BAK81,
//	EN_DI_YX_BAK82,
//	EN_DI_YX_BAK83,
//	EN_DI_YX_BAK84,
//	EN_DI_YX_BAK85,
//	EN_DI_YX_BAK86,
//	EN_DI_YX_BAK87,
//	EN_DI_YX_BAK88,
	EN_DI_BOARD4_END,
/*==============================*/
//  DWORD5.OPB1��ö��-�ڲ��ɼ��ź�
/*==============================*/
	EN_DI_BOARD5_STR=EN_DI_BOARD4_END,
	EN_DI_OPB1_HWJ=EN_DI_BOARD5_STR,
	EN_DI_OPB1_TWJ,
	EN_DI_OPB1_POW,
	EN_DI_OPB1_KKJ,
	EN_DI_OPB1_TJF,
	EN_DI_OPB1_STJ,
	EN_DI_OPB1_SHJ,
	EN_DI_BOARD5_END,
#if 0
	EN_DI_BOARD9_STR=EN_DI_BOARD8_END,
	EN_DI_OPB2_HWJ=EN_DI_BOARD9_STR,
	EN_DI_OPB2_TWJ,
	EN_DI_OPB2_POW,
	EN_DI_OPB2_KKJ,
	EN_DI_OPB2_TJF,
	EN_DI_OPB2_STJ,
	EN_DI_OPB2_SHJ,
// ���ڻز�
	EN_DI_BOARD9_END,
#endif	
	EN_DI_DI_END=EN_DI_BOARD5_END,// DI�ɼ�����
	
/*==============================*/
// DWORD6.������1�ز�ö��
/*=============================*/
	EN_DI_BOARD6_STR=EN_DI_BOARD5_END,
	EN_DI_DO_BHTZ=EN_DI_BOARD6_STR,  // ��բ���ڻز�
	EN_DI_DO_BHHZ,                   // ��բ���ڻز�
	EN_DI_DO_BZTTZ,                  // ����Ͷ��բ���ڻز�
	EN_DI_DO_BZTHZ,                  // ����Ͷ��բ���ڻز�
	EN_DI_DO_BAK1,
	EN_DI_DO_BAK2,
	EN_DI_DO_BAK3,
	EN_DI_DO_BAK4,
	EN_DI_DO_XCBR_OPN,
	EN_DI_DO_XCBR_CLS,
	EN_DI_DO_BSCH,
	EN_DI_DO_XCBR_JBS,
	EN_DI_DO_XSWI01_JBS,
	EN_DI_DO_XSWI02_JBS,
	EN_DI_DO_XSWI03_JBS,
	EN_DI_DO_XSWI04_JBS,
	EN_DI_BOARD6_END,
/*==============================*/
//  DWORD7.������2�ز�ö��
/*=============================*/
	EN_DI_BOARD7_STR=EN_DI_BOARD6_END,
	EN_DI_DO_XSWI05_JBS=EN_DI_BOARD7_STR,
	EN_DI_DO_XSWI06_JBS,
	EN_DI_DO_XSWI07_JBS,
	EN_DI_DO_XSWI08_JBS,
	EN_DI_DO_XSWI01_OPN,
	EN_DI_DO_XSWI01_CLS,
	EN_DI_DO_XSWI02_OPN,
	EN_DI_DO_XSWI02_CLS,
	EN_DI_DO_XSWI03_OPN,
	EN_DI_DO_XSWI03_CLS,
	EN_DI_DO_XSWI04_OPN,
	EN_DI_DO_XSWI04_CLS,
	EN_DI_DO_XSWI05_OPN,
	EN_DI_DO_XSWI05_CLS,
	EN_DI_DO_XSWI06_OPN,
	EN_DI_DO_XSWI06_CLS,
	EN_DI_BOARD7_END,
/*=============================*/
//  DWORD7.���뿪����ö��--������У����
/*==============================*/
	EN_DI_BOARD8_STR=EN_DI_BOARD7_END,
	EN_DI_DO_XSWI07_OPN=EN_DI_BOARD8_STR,
	EN_DI_DO_XSWI07_CLS,
	EN_DI_DO_XSWI08_OPN,
	EN_DI_DO_XSWI08_CLS,
	EN_DI_DO_YK_BAK1,
	EN_DI_DO_YK_BAK2,
	EN_DI_DO_BHBAK5,
	EN_DI_BOARD8_END,

	EN_DI_END=EN_DI_BOARD8_END
};
// Ӳ����˫���ź�ö��
enum _DPI_NUMBER
{
	EN_DPI_STR=0,
	EN_DPI_XCBR=EN_DPI_STR,
	EN_DPI_XSWI01,
	EN_DPI_XSWI02,
	EN_DPI_XSWI03,
	EN_DPI_XSWI04,
	EN_DPI_XSWI05,
	EN_DPI_XSWI06,
	EN_DPI_XSWI07,
	EN_DPI_XSWI08,
	EN_DPI_END,
};
// GOOSE�����ź�ö��
enum _GOIN_NUMBER
{
	EN_GOIN_STR=0,
	// �����ź�
	EN_GOIN_S_STR=EN_GOIN_STR,
	EN_GOIN_RESET=EN_GOIN_S_STR,  // Զ������
	EN_GOIN_CKTZ,                 // �����բ
	EN_GOIN_CKHZ,                 // ��غ�բ
	EN_GOIN_JBS_XCBR,             // ��·�������
	EN_GOIN_BZTTZ1,               // ����Ͷ��բ1
	EN_GOIN_BZTTZ2,               // ����Ͷ��բ2
	EN_GOIN_BZTHZ1,               // ����Ͷ��բ1
	EN_GOIN_BZTHZ2,               // ����Ͷ��բ2
	EN_GOIN_BHTZ1,                // ������բ1
	EN_GOIN_BHTZ2,                // ������բ2
	EN_GOIN_BHTZ3,                // ������բ3
	EN_GOIN_BHTZ4,                // ������բ4
	EN_GOIN_BHTZ5,                // ������բ5
	EN_GOIN_BHHZ1,                // �����غ�բ1
	EN_GOIN_BHHZ2,                // �����غ�բ2
	EN_GOIN_BHHZ3,                // �����غ�բ3
	EN_GOIN_BHHZ4,                // �����غ�բ4
	EN_GOIN_BHHZ5,                // �����غ�բ5
	EN_GOIN_BSHZ1,                // �����غ�բ1
	EN_GOIN_BSHZ2,                // �����غ�բ2
	EN_GOIN_BSHZ3,                // �����غ�բ3
	EN_GOIN_BSHZ4,                // �����غ�բ4
	EN_GOIN_BSHZ5,                // �����غ�բ5
	EN_GOIN_BHYT1,                // ��������1
	EN_GOIN_BHYT2,                // ��������2
	EN_GOIN_BHYT3,                // ��������3
	EN_GOIN_BHYT4,                // ��������4
	EN_GOIN_BHYT5,                // ��������5
	EN_GOIN_BHYT6,                // ��������6
	EN_GOIN_BHYT7,                // ��������7
	EN_GOIN_BHYT8,                // ��������8
	EN_GOIN_BHYT9,                // ��������9
	EN_GOIN_BHYT10,               // ��������10
	EN_GOIN_CLS_XSWI01,
	EN_GOIN_OPN_XSWI01,
	EN_GOIN_JBS_XSWI01,
	EN_GOIN_CLS_XSWI02,
	EN_GOIN_OPN_XSWI02,
	EN_GOIN_JBS_XSWI02,
	EN_GOIN_CLS_XSWI03,
	EN_GOIN_OPN_XSWI03,
	EN_GOIN_JBS_XSWI03,
	EN_GOIN_CLS_XSWI04,
	EN_GOIN_OPN_XSWI04,
	EN_GOIN_JBS_XSWI04,
	EN_GOIN_CLS_XSWI05,
	EN_GOIN_OPN_XSWI05,
	EN_GOIN_JBS_XSWI05,
	EN_GOIN_CLS_XSWI06,
	EN_GOIN_OPN_XSWI06,
	EN_GOIN_JBS_XSWI06,
	EN_GOIN_CLS_XSWI07,
	EN_GOIN_OPN_XSWI07,
	EN_GOIN_JBS_XSWI07,
	EN_GOIN_CLS_XSWI08,
	EN_GOIN_OPN_XSWI08,
	EN_GOIN_JBS_XSWI08,
	// ����ң�� 1~2 
	EN_GOIN_BAK_01,
	EN_GOIN_BAK_02,
	// ʱ��������� 
	EN_GOIN_TIME_SYN,
	EN_GOIN_S_END,
	// ˫���ź�
	EN_GOIN_D_STR=EN_GOIN_S_END,
	EN_GOIN_D_END=EN_GOIN_D_STR,
	EN_GOIN_END=EN_GOIN_D_END,    // GOOSE�������
};
// Ӳ�����ź�ö��
enum _DO_NUMBER
{
    EN_DO_STR = 0,
// ������1
    EN_DO_BOARD1_STR=EN_DO_STR,
    EN_DO_BHTZ=EN_DO_BOARD1_STR,
    EN_DO_BHHZ,
    EN_DO_BZTTZ,
    EN_DO_BZTHZ,
    EN_DO_BHBAK1,
    EN_DO_BHBAK2,
    EN_DO_BHBAK3,
    EN_DO_BHBAK4,
    EN_DO_XCBR_OPN,
    EN_DO_XCBR_CLS,
    EN_DO_BSCH,
    EN_DO_XCBR_JBS,
    EN_DO_XSWI01_JBS,
    EN_DO_XSWI02_JBS,
    EN_DO_XSWI03_JBS,
    EN_DO_XSWI04_JBS,
    EN_DO_BOARD1_END,
// ������2
    EN_DO_BOARD2_STR=EN_DO_BOARD1_END,
    EN_DO_XSWI05_JBS=EN_DO_BOARD2_STR,
    EN_DO_XSWI06_JBS,
    EN_DO_XSWI07_JBS,
    EN_DO_XSWI08_JBS,
    EN_DO_XSWI01_OPN,
    EN_DO_XSWI01_CLS,
    EN_DO_XSWI02_OPN,
    EN_DO_XSWI02_CLS,
    EN_DO_XSWI03_OPN,
    EN_DO_XSWI03_CLS,
    EN_DO_XSWI04_OPN,
    EN_DO_XSWI04_CLS,
    EN_DO_XSWI05_OPN,
    EN_DO_XSWI05_CLS,
    EN_DO_XSWI06_OPN,
    EN_DO_XSWI06_CLS,
    EN_DO_BOARD2_END,
// ���뿪����
    EN_DO_BOARD3_STR=EN_DO_BOARD2_END,
    EN_DO_XSWI07_OPN=EN_DO_BOARD3_STR,
    EN_DO_XSWI07_CLS,
    EN_DO_XSWI08_OPN,
    EN_DO_XSWI08_CLS,
    EN_DO_YK_BAK1,
    EN_DO_YK_BAK2,
    EN_DO_BHBAK5,
    EN_DO_BOARD3_END,
    
    EN_DO_RTN_END=EN_DO_BOARD3_END,
// ֱ�س���
    EN_DO_BOARD4_STR=EN_DO_BOARD3_END,
    EN_DO_ALM=EN_DO_BOARD4_STR,
    EN_DO_CHK,
    EN_DO_BOARD4_END,
    EN_DO_END=EN_DO_BOARD4_END,            // �������ڿ���ͨ�� END
};
// GOOSE��������
enum _GOOUT_NUMBER
{
    EN_GOOUT_START=0,
    EN_GOOUT_CHK=EN_GOOUT_START,
    EN_GOOUT_ALM,
    EN_GOOUT_ALM_SYN,
    EN_GOOUT_ALM_KI,
    EN_GOOUT_ALM_SV,
    EN_GOOUT_ALM_GOOSE,
    EN_GOOUT_ALM_GOCB01,
    EN_GOOUT_ALM_GOCB02,
    EN_GOOUT_ALM_GOCB03,
    EN_GOOUT_ALM_GOCB04,
    EN_GOOUT_ALM_GOCB05,
    EN_GOOUT_ALM_GOCB06,
    EN_GOOUT_ALM_GOCB07,
    EN_GOOUT_ALM_GOCB08,
    EN_GOOUT_ALM_GOCB09,
    EN_GOOUT_ALM_GOCB10,
    EN_GOOUT_ALM_GOCB11,
    EN_GOOUT_ALM_GOCB12,
    EN_GOOUT_ALM_GOCB13,
    EN_GOOUT_ALM_GOCB14,
    EN_GOOUT_ALM_GOCB15,
    EN_GOOUT_ALM_GOCB16,
    EN_GOOUT_ALM_GOCB17,
    EN_GOOUT_ALM_GOCB18,
    EN_GOOUT_ALM_GOCB19,
    EN_GOOUT_ALM_GOCB20,
    EN_GOOUT_ALM_GOCB21,
    EN_GOOUT_ALM_GOCB22,
    EN_GOOUT_ALM_GOCB23,
    EN_GOOUT_ALM_GOCB24,
    EN_GOOUT_TEST_ERR,
    EN_GOOUT_ALM_BSCH,   // �����غ�բ 
    EN_GOOUT_FLAG_TJF,   // ����ֱ���ź� TJF
    EN_GOOUT_FLAG_KKJ,   // KKJ �Ϻ� 
    EN_GOOUT_FLAG_STJ,   // STJ �ź� 
    EN_GOOUT_FLAG_SHJ,   // SHJ �ź� 
    EN_GOOUT_ALM_KHDX,   // ���ƻ�·����
    EN_GOOUT_ALM_XSWI,   // ��բλ���쳣 
    EN_GOOUT_ALM_VCHG,   // ѡ�����״̬�쳣 
    EN_GOOUT_ALM_PTACT,  // PT �л�ͬʱ���� 
    EN_GOOUT_ALM_PTRET,  // PT �л�ͬʱ���� 
    EN_GOOUT_ALM_LNK,    // SV���������쳣
    EN_GOOUT_ALM_OPBP1,  // ������Դ��������ź�
    EN_GOOUT_ALM_SGZ,    // �¹����ź� 
    EN_GOOUT_ALM_SXBYZ,  // ���಻һ�� 
    EN_GOOUT_IN_BHTZ,    // �յ�������բ���� 
    EN_GOOUT_IN_BHYT,    // �յ������������� 
    EN_GOOUT_IN_BHHZ,    // �յ������������� 
    EN_GOOUT_IN_CKTZ,    // �յ������բ���� 
    EN_GOOUT_IN_CKHZ,    // �յ���غ�բ���� 
    EN_GOOUT_IN_BZTTZ,   // �յ�����Ͷ��բ���� 
    EN_GOOUT_IN_BZTHZ,   // �յ�����Ͷ��բ���� 
    EN_GOOUT_DO_BHTZ,    // ��բ���ڻز� 
    EN_GOOUT_DO_BHHZ,    // ��բ���ڻز� 
    EN_GOOUT_DO_BZTTZ,   // ����Ͷ��բ���ڻز� 
    EN_GOOUT_DO_BZTHZ,   // ����Ͷ��բ���ڻز� 
    EN_GOOUT_V_I,        // ѹ��ȡ��ĸ 
    EN_GOOUT_V_II,       // ѹ��ȡ��ĸ 
    EN_GOOUT_SV_A,       // A ���������� 
    EN_GOOUT_SV_B,       // B ���������� 
    EN_GOOUT_LNK_A,      // ����ȡ A �� 
    EN_GOOUT_LNK_B,      // ����ȡ B �� 
    EN_GOOUT_PARACHG,
    EN_GOOUT_TIME_RECV,
    EN_GOOUT_TIME_SEND,
    EN_GOOUT_TIME_SINGLE,
    EN_GOOUT_TIME_SERVIC,
    EN_GOOUT_TIME_CHKERR,
    EN_GOOUT_END
};
//ָʾ��ö��
enum _LED_NUMBER
{
    EN_LED_STR=0,
// ��1��ָʾ��
    EN_LED_RUN=EN_LED_STR,
    EN_LED_ALM,
    EN_LED_TEST,
    EN_LED_GO_ERR,
    EN_LED_TEST_ERR,
    EN_LED_SYN_ERR,
    EN_LED_SAM_ERR,
    EN_LED_KHDX,
// ��2��ָʾ��
    EN_LED_BHTZ,
    EN_LED_BHHZ,
    EN_LED_ZTF,
    EN_LED_BAK21,
    EN_LED_BAK22,
    EN_LED_BAK23,
    EN_LED_BAK24,
    EN_LED_HWJ,
// ��3��ָʾ��
    EN_LED_WAR_LNK,    // �����쳣
    EN_LED_VCHG_I,     // ѹ��ȡ��ĸ
    EN_LED_VCHG_II,    // ѹ��ȡ��ĸ
    EN_LED_LNK_A,      // ����ȡA��
    EN_LED_LNK_B,      // ����ȡB��
    EN_LED_BAK31,
    EN_LED_BAK32,
    EN_LED_TWJ,
// ��4��ָʾ��
    EN_LED_XSWI01_CLS,    // ��բ1��λ
    EN_LED_XSWI02_CLS,    // ��բ2��λ
    EN_LED_XSWI03_CLS,    // ��բ3��λ
    EN_LED_XSWI04_CLS,    // ��բ4��λ
    EN_LED_XSWI05_CLS,    // ��բ5��λ
    EN_LED_XSWI06_CLS,    // ��բ6��λ
    EN_LED_XSWI07_CLS,    // ��բ7��λ
    EN_LED_XSWI08_CLS,    // ��բ8��λ
// ��5��ָʾ��
    EN_LED_XSWI01_OPN,    // ��բ1��λ
    EN_LED_XSWI02_OPN,    // ��բ2��λ
    EN_LED_XSWI03_OPN,    // ��բ3��λ
    EN_LED_XSWI04_OPN,    // ��բ4��λ
    EN_LED_XSWI05_OPN,    // ��բ5��λ
    EN_LED_XSWI06_OPN,    // ��բ6��λ
    EN_LED_XSWI07_OPN,    // ��բ7��λ
    EN_LED_XSWI08_OPN,    // ��բ8��λ
    EN_LED_END
};
/*================================================================================*/
//IO��ذ忨ö��
/*================================================================================*/
enum _BOARD_IO_TYPE_
{
    EN_BOARD_DO1=0,
    EN_BOARD_DO2,
    EN_BOARD_DO3,
    EN_BOARD_DIO_DO=EN_BOARD_DO3,      // DIO�忨��ʶ
    EN_BOARD_DO_RTN_END,               // �з�У�Ŀ����ź�
    EN_BOARD_DO4=EN_BOARD_DO_RTN_END,  
    EN_BOARD_DO_END,
    
    EN_BOARD_DI1=0,
    EN_BOARD_DI2,
    EN_BOARD_DI3,
    EN_BOARD_DI4,
    EN_BOARD_DIO_DI=EN_BOARD_DI4,     // DIO�忨��ʶ
    EN_BOARD_DI5,
    EN_BOARD_OPB=EN_BOARD_DI5,        // OPB�忨��ʶ
    EN_BOARD_DI_DI_END,               // DI�Ƿ�У����
    EN_BOARD_DI_DO_STR=EN_BOARD_DI_DI_END,// DI�Ƿ�У����
    EN_BOARD_DI6=EN_BOARD_DI_DO_STR+EN_BOARD_DO1,
    EN_BOARD_DI7=EN_BOARD_DI_DO_STR+EN_BOARD_DO2,
    EN_BOARD_DI8=EN_BOARD_DI_DO_STR+EN_BOARD_DO3,
    EN_BOARD_DI_DO_END=EN_BOARD_DI_DO_STR+EN_BOARD_DO_RTN_END,
    EN_BOARD_DI_END=EN_BOARD_DI_DO_END,
};
// GOOSE�ź���Чԭ��
enum _TYPE_GOIN_INVAILD_
{
	EN_INVAILD_STR=0,              // ��Чԭ��
	EN_INVAILD_NO=EN_INVAILD_STR,  // �ɹ�
	EN_INVAILD_TEST,               // ʧ��:���޲�һ��
	EN_INVAILD_LINK,               // ʧ��:����
	EN_INVAILD_Q,                  // ʧ��:Ʒ����Ч
	EN_INVAILD_DATA,               // ʧ��:�����쳣
	EN_INVAILD_END,                // 
};

/*================================================================================*/
// ������ṹ��
/*================================================================================*/
// Ӳ���뵥�㿪�볣����ṹ��
typedef struct
{
	WORD            wIndex;                         // Ӳ����ö�ٺ�
	WORD            wCfg;                           // Ӳ����������������
	INT8S           byName[CN_LEN_NAME];            // Ӳ��������
	INT8S           byPinName[CN_LEN_NAME];         // Ӳ����̵�ַ	
} tagDiTab;
// Ӳ����˫��ϳɳ�����ṹ��
typedef struct
{
	WORD            wIndex;                         // ģ����ö�ٺ�
	WORD            wSrcType;                       // �����ź�Դ
	WORD            wSrcOpn;                        // ������λ�ź�
	WORD            wSrcCls;                        // ������λ�ź�
	WORD            wParaIndex;                     // ��������1
	WORD            wCfg;                           // ������������
	INT8S           byName[CN_LEN_NAME];            // ģ��������
	INT8S           byPinName[CN_LEN_NAME];         // ģ�����̵�ַ
}tagDpiTab;
// GOOSE����ң�ų�����ṹ��
typedef struct
{
	WORD            wIndex;                         // GOOSE����ö�ٺ�
	WORD            wChnType;                       // �ź�����
	WORD            wParaIndex;                     // ��������
	WORD            wCfg;                           // GOOSE����������������
	INT8S           byName[CN_LEN_NAME];            // GOOSE��������
	INT8S           byPinName[CN_LEN_NAME];         // GOOSE����̵�ַ	
} tagGoInTab;
// ��������Ϣ���������ݽṹ
typedef struct
{
	WORD            wIndex;                         // ������ö��
	WORD            wSrcType;                       // �����ź�Դ
	WORD            wSrcIndex;                      // �����ź�Դö��
	WORD            wParaIndex;                     // ��������1
	WORD            wRtnIndex;                      // ������Уң��
	WORD            wCfg;                           // ����������������
	INT8S           byName[CN_LEN_NAME];            // ����������
	INT8S           byPinName[CN_LEN_NAME];         // �������̵�ַ
} tagDoTab;
// GOOSE������Ϣ���������ݽṹ
typedef struct
{
	WORD            wIndex;                         // GOOSE������ö��
	WORD            wChnType;                       // ��������
	WORD            wSrcType;                       // �����ź�Դ
	WORD            wSrcIndex;                      // �����ź�Դö��
	WORD            wParaIndex;                     // ��������1
	WORD            wCfg;                           // GOOSE���������������� NULL:����Ʒ��\����ʱ��
	INT8S           byName[CN_LEN_NAME];            // GOOSE����������
	INT8S           byPinName[CN_LEN_NAME];         // GOOSE�������̵�ַ
} tagGoOutTab;
// ָʾ��Ϣ���������ݽṹ
typedef struct
{
	WORD            wIndex;                         // ָʾ��ö��
	WORD            wSrcType;                       // �����ź�Դ
	WORD            wSrcIndex;                      // �����ź�Դö��
	WORD            wParaIndex;                     // ��������
	BYTE            byCol;                          // ��λ��
	BYTE            byRow;                          // ��λ��
	BYTE            bycolor;                        // ָʾ����ɫ
	BOOL            bHld;                           // ָʾ�Ʊ��ֹ���
	INT8S           byName[CN_LEN_NAME];            // ָʾ������
	INT8S           byPinName[CN_LEN_NAME];         // ָʾ�ƶ̵�ַ
} tagLedTab;

// �忨���ó�����ṹ��
typedef struct
{
	WORD            wIndex;                         // �忨ö�ٺ�
	WORD            wIndexStr;                      // �����ź�Դ��ʼö��
	WORD            wIndexEnd;                      // �����ź�Դ����ö��
	WORD            wSrcIndexNum;                   // �����źŸ���
	WORD            wPowBitNum;                     // ����ʧ���ź�λ��
	WORD            wParaIndex;                     // ����ʧ��Ͷ�˲���
	WORD            wAddrBoard;                     // �忨��ַ
	WORD            wAddrFrame;                     // ֡��ַ
	INT8S           byName[CN_LEN_NAME];            // �忨����
	INT8S           byPinName[CN_LEN_NAME];         // �忨�̵�ַ
} tagBoardIoTab;

/*================================================================================*/
// �궨��
/*================================================================================*/
#define CN_NUM_DI_DI         (EN_DI_DI_END)
#define CN_NUM_DI            (EN_DI_END)
#define CN_NUM_GOIN_S        (EN_GOIN_S_END-EN_GOIN_S_STR)     // �����ź�
#define CN_NUM_GOIN_D        (EN_GOIN_D_END-EN_GOIN_D_STR)     // ˫���ź�
#define CN_NUM_GOIN          (EN_GOIN_END)
#define CN_NUM_DPI           (EN_DPI_END)
#define CN_NUM_DO_RTN        (EN_DO_RTN_END)
#define CN_NUM_DO            (EN_DO_END)
#define CN_NUM_GOOUT         (EN_GOOUT_END)
#define CN_NUM_LED           (EN_LED_END)
// �忨����
#define CN_NUM_BOARD_DI_DI   (EN_BOARD_DI_DI_END)
#define CN_NUM_BOARD_DI_DO   (EN_BOARD_DI_DO_STR)
#define CN_NUM_BOARD_DI      (EN_BOARD_DI_END)
#define CN_NUM_BOARD_DO_RTN  (EN_BOARD_DO_RTN_END)
#define CN_NUM_BOARD_DO      (EN_BOARD_DO_END)
// ˫��λ��
#define CN_DPI_OPN        (0x1)                               // ��λ
#define CN_DPI_CLS        (0x2)                               // ��λ
#define CN_DPI_STP        (0x0)                               // ͣ��
#define CN_DPI_CHK        (0x3)                               // �쳣

// ��������
#define CN_DI_HLD_CPU        (1)                               // 0--FPGA����,1--CPU����
// GOOSE���ƿ�������
#define CN_NUM_GOCB_SUB       (12)
#define CN_NUM_GOCB_PUB       (8)
// GOOSEƷ��(��������ƽ��)
//#define CN_GOIN_St          (DB0+DB1)                       // bit0~bit1 ״̬��Ϣ 
#define CN_GOIN_Invalid       (DB0+DB1)                       // bit2~bit3 Ʒ����Ч
#define CN_GOIN_Test          (DB2)                           // bit4 ����״̬(����Q,ȡQ�м���;δ����Q,ȡ���ƿ����):0--δ���� 1--����
#define CN_GOIN_Link          (DB3)                           // bit5 ��·״̬:0--δ���� 1--���� 
#define CN_GOIN_TimeToLive0   (DB4)                           // bit6 TimeToLive�Ƿ�Ϊ0��־:0--TimeToLive��Ϊ0 1--TimeToLiveΪ0 
#define CN_GOIN_DataErr       (DB5)                           // bit7 �����쳣
#define CN_GOIN_Bak08         (DB6)                           // bit8 ����
#define CN_GOIN_NoSub         (DB7)                           // bit9 δ����
#define CN_GOIN_Bak10         (DB8)                           // bit10 ����
#define CN_GOIN_Bak11         (DB9)                           // bit11 ����
#define CN_GOIN_Bak12         (DB10)                          // bit12 ����
#define CN_GOIN_Bak13         (DB11)                          // bit13 ����
#define CN_GOIN_Bak14         (DB12)                          // bit14 ����
#define CN_GOIN_Bak15         (DB13)                          // bit15 ����

// GOOSE���ƿ�״̬��
#define CN_GOCB_NO            (0xff)                          // bit0~bit7  ���ƿ����
#define CN_GOCB_NetPort       (0xff00)                        // bit8~bit15 ����˿�
#define CN_GOCB_LinkErr1      (DB16)                          // bit16 �����жϡ�1��������0��������
#define CN_GOCB_APPIDErr      (DB17)                          // bit17 APPID������ƥ�䡣1����ƥ�䣻0��������
#define CN_GOCB_GoCbErr       (DB18)                          // bit18 GoCB������ƥ�䡣1����ƥ�䣻0��������
#define CN_GOCB_DateSetErr    (DB19)                          // bit19 DatSet������ƥ�䡣1����ƥ�䣻0��������
#define CN_GOCB_GoIDErr       (DB20)                          // bit20 GoID������ƥ�䡣1����ƥ�䣻0��������
#define CN_GOCB_ConfRevErr    (DB21)                          // bit21 ConfRev������ƥ�䡣1����ƥ�䣻0��������
#define CN_GOCB_DataNumErr    (DB22)                          // bit22 DataNum������ƥ�䡣1����ƥ�䣻0��������
#define CN_GOCB_DataTypeErr   (DB23)                          // bit23 DataType������ƥ�䡣1����ƥ�䣻0��������
#define CN_GOCB_DataChangeErr (DB24)                          // bit24 DataChangeErr��1���쳣��0������,�ݲ����ǣ�������
#define CN_GOCB_Test          (DB25)                          // bit25 ����λ��1������ 0���Ǽ���
#define CN_GOCB_Ndscom        (DB26)                          // bit26 Ndscomֵ
#define CN_GOCB_FrameErr      (DB27)                          // bit27 ƽ̨�ṩ--֡ͨ���쳣��֡�����쳣
#define CN_GOCB_Storm         (DB28)                          // bit28 ����籩��ʶ,20ms�ڽ�������֡��22֡����Ϊ�籩
#define CN_GOCB_LinkErr2      (DB29)                          // bit29 ����״̬ ��bit16��bit30�ϳɣ���λ��
#define CN_GOCB_TimeToLive0   (DB30)                          // bit30 TimeToLive�Ƿ�Ϊ0, 0���� 1:��
#define CN_GOCB_Ena           (DB31)                          // bit31 ���ƿ�ʹ��,1��ʹ�� 0��δʹ��

#define CN_GOCB_LinkErr      (CN_GOCB_LinkErr1+CN_GOCB_LinkErr2)                          // ����
#define CN_GOCB_DataErr      (CN_GOCB_APPIDErr+CN_GOCB_GoCbErr+CN_GOCB_DateSetErr+CN_GOCB_GoIDErr+CN_GOCB_ConfRevErr+ \
        CN_GOCB_DataNumErr+CN_GOCB_DataTypeErr+CN_GOCB_FrameErr)    // �����쳣

#define CN_GOCB_DataAlm      (CN_GOCB_LinkErr+CN_GOCB_DataErr+CN_GOCB_TimeToLive0)

#define CN_GOCFG_CfgErr     (DB0)                             // bit0 ƽ̨�ṩ--�����쳣
#define CN_GOCFG_ParseErr   (DB1)                             // bit1 ƽ̨�ṩ--�����쳣��
#define CN_GOCFG_DataErr    (CN_GOCFG_CfgErr+CN_GOCFG_ParseErr)
// ���ڰ��Լ�״̬��
#define CN_DO_CHK_CHN1       (DB0)                          // bit0 ͨ��1�ж�(CPU1->���ڰ�),Do��5S�ղ���������λ,�յ�����200ms����
#define CN_DO_CHK_CHN2       (DB1)                          // bit1 ͨ��2�ж�(CPU2->���ڰ壬ĸ�߲�ִ��ʹ��)
#define CN_DO_CHK_FPOW       (DB2)                          // bit2 ���ٳ���30V��ѹ���ڹ��磬���ڰ嵥Ƭ��ɨ��30V����״̬����30kV�����ҹ���״̬���ڳ���5S����λ,���Զ����ء�
#define CN_DO_CHK_PARA       (DB3)                          // bit3 ���ڰ������,���ڰ嵥Ƭ������SRAM,��һ����ʳ���bit��ת,��Ƭ���洢3�ݲ��������ڱȶԣ����ݾ���һ�£���λ��
#if(CN_HARDWARE_DO==CN_HARDWARE_DO_V1)
#define CN_DO_CHK_POW24      (0)
#define CN_DO_CHK_POW30      (0)
#else
#define CN_DO_CHK_POW24      (DB4)                          // bit4 ���ڰ�24V��ѹ��,50ms����һ�Ρ�
#define CN_DO_CHK_POW30      (DB5)                          // bit5 ���ڰ�30V��ѹ��,3min����һ�Ρ�
#endif
/*================================================================================*/
// ȫ�ֳ���������
/*================================================================================*/
extern const tagDiTab     g_tDiTab[];
extern const DWORD        g_NUM_DI;
extern const tagDpiTab    g_tDpiTab[];
extern const DWORD        g_NUM_DPI;
extern const tagGoInTab   g_tGoInTab[];
extern const DWORD        g_NUM_GOIN;
extern const tagDoTab     g_tDoTab[];
extern const DWORD        g_NUM_DO;
extern const tagGoOutTab  g_tGoOutTab[];
extern const DWORD        g_NUM_GOOUT;
extern const tagLedTab    g_tLedTab[];
extern const DWORD        g_NUM_LED;
extern const tagBoardIoTab    g_tBoardDITab[];
extern const DWORD            g_NUM_BOARD_DI;
extern const tagBoardIoTab    g_tBoardDOTab[];
extern const DWORD            g_NUM_BOARD_DO;

/*================================================================================*/
#endif  /* _CONST_IO_H_ */
