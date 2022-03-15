#ifndef _CONST_REC_H_
#define _CONST_REC_H_

/*================================================================================*/
//GOOSE�����ź�ö��
/*================================================================================*/
enum _TYPE_REC_ACT_
{
	EN_ACT_STR = 0,
	EN_ACT_BHTZ=EN_ACT_STR,
	EN_ACT_BHHZ,
	EN_ACT_BHYT,
	EN_ACT_CKTZ,
	EN_ACT_CKHZ,
	EN_ACT_JBS_XCBR,
	EN_ACT_BZTTZ,
	EN_ACT_BZTHZ,
	EN_ACT_CLS_XSWI01,
	EN_ACT_OPN_XSWI01,
	EN_ACT_JBS_XSWI01,
	EN_ACT_CLS_XSWI02,
	EN_ACT_OPN_XSWI02,
	EN_ACT_JBS_XSWI02,
	EN_ACT_CLS_XSWI03,
	EN_ACT_OPN_XSWI03,
	EN_ACT_JBS_XSWI03,
	EN_ACT_CLS_XSWI04,
	EN_ACT_OPN_XSWI04,
	EN_ACT_JBS_XSWI04,
	EN_ACT_CLS_XSWI05,
	EN_ACT_OPN_XSWI05,
	EN_ACT_JBS_XSWI05,
	EN_ACT_CLS_XSWI06,
	EN_ACT_OPN_XSWI06,
	EN_ACT_JBS_XSWI06,
	EN_ACT_CLS_XSWI07,
	EN_ACT_OPN_XSWI07,
	EN_ACT_JBS_XSWI07,
	EN_ACT_CLS_XSWI08,
	EN_ACT_OPN_XSWI08,
	EN_ACT_JBS_XSWI08,
	EN_ACT_BAK_01,
	EN_ACT_BAK_02,
	EN_ACT_END
};
/*================================================================================*/
//�澯�ź�ö��
/*================================================================================*/
enum _TYPE_REC_ALM_
{
	EN_ALM_STR = 0,
	EN_ALM_SYN=EN_ALM_STR, // ͬ���쳣
	EN_ALM_SAM,            // �����쳣
	EN_ALM_DIPOW,          // ����ʧ��
	EN_ALM_TIME_SINGLE,    // ��ʱ�ź�״̬
	EN_ALM_TIME_SERVICE,   // ��ʱ����״̬
	EN_ALM_TIME_CHKERR,    // ʱ���������״̬
	EN_ALM_TEST,           // ���޲�һ��
	EN_ALM_SV,             // SV�ܸ澯
	EN_ALM_SVPUB_INVALID,  // SV����������Ч
	EN_ALM_LINK,           // �����쳣 
	EN_ALM_SVSUB,          // SV���������쳣
	
	EN_ALM_SVSUB_COM01,   // SVCB01����
	EN_ALM_SVSUB_COM02,   // SVCB02����
	EN_ALM_SVSUB_DAT01,   // SVCB01�����쳣
	EN_ALM_SVSUB_DAT02,   // SVCB02�����쳣
	EN_ALM_SVSUB_TEST01,  // SVCB01���޲�һ��
	EN_ALM_SVSUB_TEST02,  // SVCB02���޲�һ��
	EN_ALM_SVSUB_SYN01,   // SVCB01ͬ���쳣
	EN_ALM_SVSUB_SYN02,   // SVCB02ͬ���쳣
	EN_ALM_SVSUB_CFG01,   // SVCB01�����쳣
	EN_ALM_SVSUB_CFG02,   // SVCB02�����쳣

	EN_ALM_SVLINK_QA,     // A�׼���SV�����쳣
	EN_ALM_SVLINK_QB,     // B�׼���SV�����쳣
	EN_ALM_SVLINK_CFGA,   // A�׼���SV�����쳣
	EN_ALM_SVLINK_CFGB,   // B�׼���SV�����쳣
	EN_ALM_SVLINK_NOCFGA, // A�׼���SVδ����
	EN_ALM_SVLINK_NOCFGB, // B�׼���SVδ����
	EN_ALM_SVLINK_TESTA,  // A�׼���SV����
	EN_ALM_SVLINK_TESTB,  // B�׼���SV����

	EN_ALM_KHDX,         // ���ƻ�·����
	EN_ALM_XZBS,         // ѡ�����״̬�쳣
	EN_ALM_XSWI,         // ��բλ���쳣
	EN_ALM_PTACT,        // PT�л�ͬʱ����
	EN_ALM_PTRET,        // PT�л�ͬʱ����
	EN_ALM_OPBP1,        // ������Դ1��������ź�
//	EN_ALM_OPBP2,        // ������Դ2��������ź�
	EN_ALM_SGZ,          // �¹���
	EN_ALM_SXBYZ,        // ���಻һ�� 
	EN_ALM_BSCH_OTH,     // ����һ�ײɼ�ִ�е�Ԫ�����غ�բ
	EN_ALM_BSCH,         // �������ױ����غ�բ
	EN_ALM_BS_LINKQH,    // �����л����ܱ���
	EN_ALM_BS_VQH,       // ��ѹ�л����ܱ���
	EN_ALM_BS_DO,        // ���ڹ��ܱ���
	EN_ALM_GOOSE,                            // GOOSE�ܸ澯
	EN_ALM_GOOSE_TEST,                       // GOOSE���޲�һ��
	EN_ALM_GOCB_DATA_STR,                    // GOCB�����쳣��ʼ
	EN_ALM_GOCB01_DATA=EN_ALM_GOCB_DATA_STR, // GOCB01�����쳣
	EN_ALM_GOCB02_DATA,                      // GOCB02�����쳣
	EN_ALM_GOCB03_DATA,                      // GOCB03�����쳣
	EN_ALM_GOCB04_DATA,                      // GOCB04�����쳣
	EN_ALM_GOCB05_DATA,                      // GOCB05�����쳣
	EN_ALM_GOCB06_DATA,                      // GOCB06�����쳣
	EN_ALM_GOCB07_DATA,                      // GOCB07�����쳣
	EN_ALM_GOCB08_DATA,                      // GOCB08�����쳣
	EN_ALM_GOCB09_DATA,                      // GOCB09�����쳣
	EN_ALM_GOCB10_DATA,                      // GOCB10�����쳣
	EN_ALM_GOCB11_DATA,                      // GOCB11�����쳣
	EN_ALM_GOCB12_DATA,                      // GOCB12�����쳣
	EN_ALM_GOCB_DATA_END,                    // GOCB�����쳣����
	
	EN_ALM_GOCB_TEST_STR=EN_ALM_GOCB_DATA_END,// GOCB���޲�һ����ʼ
	EN_ALM_GOCB01_TEST=EN_ALM_GOCB_TEST_STR, // GOCB01���޲�һ��
	EN_ALM_GOCB02_TEST,                      // GOCB02���޲�һ��
	EN_ALM_GOCB03_TEST,                      // GOCB03���޲�һ��
	EN_ALM_GOCB04_TEST,                      // GOCB04���޲�һ��
	EN_ALM_GOCB05_TEST,                      // GOCB05���޲�һ��
	EN_ALM_GOCB06_TEST,                      // GOCB06���޲�һ��
	EN_ALM_GOCB07_TEST,                      // GOCB07���޲�һ��
	EN_ALM_GOCB08_TEST,                      // GOCB08���޲�һ��
	EN_ALM_GOCB09_TEST,                      // GOCB09���޲�һ��
	EN_ALM_GOCB10_TEST,                      // GOCB10���޲�һ��
	EN_ALM_GOCB11_TEST,                      // GOCB11���޲�һ��
	EN_ALM_GOCB12_TEST,                      // GOCB12���޲�һ��
	EN_ALM_GOCB_TEST_END,                    // GOCB���޲�һ�½���
	EN_ALM_GOCB_STORM_STR=EN_ALM_GOCB_TEST_END,// GOCB����籩
	EN_ALM_GOCB01_STORM=EN_ALM_GOCB_STORM_STR,// GOCB01����籩
	EN_ALM_GOCB02_STORM,                     // GOCB02����籩
	EN_ALM_GOCB03_STORM,                     // GOCB03����籩
	EN_ALM_GOCB04_STORM,                     // GOCB04����籩
	EN_ALM_GOCB05_STORM,                     // GOCB05����籩
	EN_ALM_GOCB06_STORM,                     // GOCB06����籩
	EN_ALM_GOCB07_STORM,                     // GOCB07����籩
	EN_ALM_GOCB08_STORM,                     // GOCB08����籩
	EN_ALM_GOCB09_STORM,                     // GOCB09����籩
	EN_ALM_GOCB10_STORM,                     // GOCB10����籩
	EN_ALM_GOCB11_STORM,                     // GOCB11����籩
	EN_ALM_GOCB12_STORM,                     // GOCB12����籩
	EN_ALM_GOCB_STORM_END,                   // GOCB���޲�һ�½���
	EN_ALM_CCD_SVSUB=EN_ALM_GOCB_STORM_END,
	EN_ALM_CCD_SVPUB,
	EN_ALM_CCD_GOSUB,
	EN_ALM_CCD_GOPUB,
	EN_ALM_BOARD_CPU2,
	EN_ALM_BAK01,
	EN_ALM_BAK02,
	EN_ALM_BAK03,
	EN_ALM_BAK04,
	EN_ALM_BAK05,
	EN_ALM_BAK06,
	EN_ALM_BAK07,
	EN_ALM_BAK08,
	EN_ALM_BAK09,
	EN_ALM_BAK10,
	EN_ALM_END          // �澯����
};
/*================================================================================*/
//�Լ��ź�ö��
/*================================================================================*/
enum _TYPE_REC_CHK_
{
// װ��ȫ���Լ�(����װ��ȫ������)
	EN_CHK_STR=0,               // �Լ쿪ʼ
	EN_CHK_CONST=EN_CHK_STR,
	EN_CHK_RAM_ERR,
	EN_CHK_RAM_ALLOC,
	EN_CHK_RAM_CHK,
	EN_CHK_CCD_NO,
	EN_CHK_CCD_ERR,
	EN_CHK_CCD_PARALOSE,
	EN_CHK_CCD_PARAERR,
	EN_CHK_CCD_CRC,
	EN_CHK_CCD_FRAME,
	EN_CHK_CCD_ADDRERR,
	EN_CHK_CCD_NUMERR,
	EN_CHK_CCD_CFGERR,
//	EN_CHK_CCD_SVSUB,
//	EN_CHK_CCD_SVPUB,
//	EN_CHK_CCD_GOSUB,
//	EN_CHK_CCD_GOPUB,
// DO��У�Լ�(������)
	EN_CHK_DO_RTN0_STR,
	EN_CHK_DO1_RTN0=EN_CHK_DO_RTN0_STR+EN_BOARD_DO1,
	EN_CHK_DO2_RTN0=EN_CHK_DO_RTN0_STR+EN_BOARD_DO2,
	EN_CHK_DIO_RTN0=EN_CHK_DO_RTN0_STR+EN_BOARD_DO3,
	EN_CHK_DO_RTN1_STR=EN_CHK_DO_RTN0_STR+CN_NUM_BOARD_DO_RTN,
	EN_CHK_DO1_RTN1=EN_CHK_DO_RTN1_STR+EN_BOARD_DO1,
	EN_CHK_DO2_RTN1=EN_CHK_DO_RTN1_STR+EN_BOARD_DO2,
	EN_CHK_DIO_RTN1=EN_CHK_DO_RTN1_STR+EN_BOARD_DO3,
// DO����ͨ���Լ�(������)
	//EN_CHK_BOARD_DO_CHN1_STR=EN_CHK_DO_RTN1_STR+CN_NUM_BOARD_DO_RTN,
	//EN_CHK_BOARD_DO1_CHN1=EN_CHK_BOARD_DO_CHN1_STR+EN_BOARD_DO1,
	//EN_CHK_BOARD_DO2_CHN1=EN_CHK_BOARD_DO_CHN1_STR+EN_BOARD_DO2,
	//EN_CHK_BOARD_DIO_CHN1=EN_CHK_BOARD_DO_CHN1_STR+EN_BOARD_DO3,
	//EN_CHK_BOARD_DO_CHN2_STR=EN_CHK_BOARD_DO_CHN1_STR+CN_NUM_BOARD_DO_RTN,
	//EN_CHK_BOARD_DO1_CHN2=EN_CHK_BOARD_DO_CHN2_STR+EN_BOARD_DO1,
	//EN_CHK_BOARD_DO2_CHN2=EN_CHK_BOARD_DO_CHN2_STR+EN_BOARD_DO2,
	//EN_CHK_BOARD_DIO_CHN2=EN_CHK_BOARD_DO_CHN2_STR+EN_BOARD_DO3,
	//EN_CHK_BOARD_DO_POW24_STR=EN_CHK_BOARD_DO_CHN2_STR+CN_NUM_BOARD_DO_RTN,
	//EN_CHK_BOARD_DO1_POW24=EN_CHK_BOARD_DO_POW24_STR+EN_BOARD_DO1,
	//EN_CHK_BOARD_DO2_POW24=EN_CHK_BOARD_DO_POW24_STR+EN_BOARD_DO2,
	//EN_CHK_BOARD_DIO_POW24=EN_CHK_BOARD_DO_POW24_STR+EN_BOARD_DO3,
	EN_CHK_BOARD_DO_POW30_STR=EN_CHK_DO_RTN1_STR+CN_NUM_BOARD_DO_RTN,
	EN_CHK_BOARD_DO1_POW30=EN_CHK_BOARD_DO_POW30_STR+EN_BOARD_DO1,
	EN_CHK_BOARD_DO2_POW30=EN_CHK_BOARD_DO_POW30_STR+EN_BOARD_DO2,
	EN_CHK_BOARD_DIO_POW30=EN_CHK_BOARD_DO_POW30_STR+EN_BOARD_DO3,
	//EN_CHK_BOARD_DO_PARA_STR=EN_CHK_BOARD_DO_POW30_STR+CN_NUM_BOARD_DO_RTN,
	//EN_CHK_BOARD_DO1_PARA=EN_CHK_BOARD_DO_PARA_STR+EN_BOARD_DO1,
	//EN_CHK_BOARD_DO2_PARA=EN_CHK_BOARD_DO_PARA_STR+EN_BOARD_DO2,
	//EN_CHK_BOARD_DIO_PARA=EN_CHK_BOARD_DO_PARA_STR+EN_BOARD_DO3,
// �����Լ�(������Ӧ����)
	EN_CHK_PARA_STR,
	EN_CHK_PARA_DI       =EN_CHK_PARA_STR+EN_BOARD_PARA_DI,
	EN_CHK_PARA_DC       =EN_CHK_PARA_STR+EN_BOARD_PARA_DC,
	EN_CHK_PARA_SAM      =EN_CHK_PARA_STR+EN_BOARD_PARA_SAM,
	EN_CHK_PARA_FUN      =EN_CHK_PARA_STR+EN_BOARD_PARA_FUN,
	EN_CHK_PARA_DC_COE   =EN_CHK_PARA_STR+EN_BOARD_PARA_DC_COE,
	EN_CHK_PARA_AM_COE   =EN_CHK_PARA_STR+EN_BOARD_PARA_AM_COE,
	EN_CHK_PARA_DCBC_COE =EN_CHK_PARA_STR+EN_BOARD_PARA_DCBC_COE,
	EN_CHK_PARA_ANG_COE  =EN_CHK_PARA_STR+EN_BOARD_PARA_ANG_COE,
	EN_CHK_PARA_END      =EN_CHK_PARA_STR+EN_BOARD_PARA_END,
	EN_CHK_PARA_DI_HLD   =EN_CHK_PARA_END,
// �忨�Լ�(��Ӧ������Ч)
	EN_CHK_BOARD_DI_STR,// 
	EN_CHK_BOARD_DI1      =EN_CHK_BOARD_DI_STR+EN_BOARD_DI1,
	EN_CHK_BOARD_DI2      =EN_CHK_BOARD_DI_STR+EN_BOARD_DI2,
	EN_CHK_BOARD_DI3      =EN_CHK_BOARD_DI_STR+EN_BOARD_DI3,
	EN_CHK_BOARD_DIO_DI   =EN_CHK_BOARD_DI_STR+EN_BOARD_DI4,
	EN_CHK_BOARD_OPB1     =EN_CHK_BOARD_DI_STR+EN_BOARD_DI5,
	
	EN_CHK_BOARD_DO_STR   =EN_CHK_BOARD_DI_STR+EN_BOARD_DI_DO_STR,// 
	EN_CHK_BOARD_DO1      =EN_CHK_BOARD_DO_STR+EN_BOARD_DO1,
	EN_CHK_BOARD_DO2      =EN_CHK_BOARD_DO_STR+EN_BOARD_DO2,
	EN_CHK_BOARD_DIO_DO   =EN_CHK_BOARD_DO_STR+EN_BOARD_DO3,
	EN_CHK_BOARD_DI_END   =EN_CHK_BOARD_DI_STR+EN_BOARD_DI_END,
	EN_CHK_BOARD_DC_STR   =EN_CHK_BOARD_DI_END,
	EN_CHK_BOARD_DC_SAM   =EN_CHK_BOARD_DC_STR+EN_BOARD_DC_SAM,
	EN_CHK_BOARD_DC_DEV   =EN_CHK_BOARD_DC_STR+EN_BOARD_DC_DEV,
	EN_CHK_BOARD_DC_OPT1_1=EN_CHK_BOARD_DC_STR+EN_BOARD_DC_OPT1_1,
	EN_CHK_BOARD_DC_OPT1_2=EN_CHK_BOARD_DC_STR+EN_BOARD_DC_OPT1_2,
	EN_CHK_BOARD_DC_OPT2  =EN_CHK_BOARD_DC_STR+EN_BOARD_DC_OPT2,
	EN_CHK_BOARD_DC_END   =EN_CHK_BOARD_DC_STR+EN_BOARD_DC_END,
	EN_CHK_BOARD_SAM_STR  =EN_CHK_BOARD_DC_END,
	EN_CHK_BOARD_PTCT1    =EN_CHK_BOARD_SAM_STR+EN_BOARD_SAM_PTCT1,
	EN_CHK_BOARD_PTCT2    =EN_CHK_BOARD_SAM_STR+EN_BOARD_SAM_PTCT2,
	EN_CHK_BOARD_CPU      =EN_CHK_BOARD_SAM_STR+EN_BOARD_SAM_CPU,
	EN_CHK_BOARD_SAM_END  =EN_CHK_BOARD_SAM_STR+CN_NUM_BOARD_SAM,
	EN_CHK_BOARD_CPU_AUX  =EN_CHK_BOARD_SAM_END,
	EN_CHK_BOARD_POW,
	EN_CHK_BOARD_CPU2,
	EN_CHK_BOARD_LED,
	EN_CHK_FRAME_ANA,    // ģ����֡���쳣
// ��佻���Լ�(�ޱ���)
	EN_CHK_CPUCOM_FAST,
	EN_CHK_CPUCOM_PARA,
	EN_CHK_CPUCOM_VER,
	EN_CHK_CPUCOM_CCD,
// �����Լ�
	EN_CHK_BAK01,
	EN_CHK_BAK02,
	EN_CHK_BAK03,
	EN_CHK_BAK04,
	EN_CHK_BAK05,
	EN_CHK_BAK06,
	EN_CHK_BAK07,
	EN_CHK_BAK08,
	EN_CHK_BAK09,
	EN_CHK_BAK10,
	EN_CHK_END                  // �Լ����
};
/*================================================================================*/
//�����ź�ö��
/*================================================================================*/
enum _TYPE_RUN_OPT_
{
	EN_RUN_STR=0,
	EN_RUN_POW_ON=EN_RUN_STR,
	EN_RUN_POW_OFF,
	EN_RUN_SVPUB_ENA,
	EN_RUN_GOPUB_ENA,
	EN_RUN_SVPUB_BS,
	EN_RUN_GOPUB_BS,
	EN_RUN_POL,
	EN_RUN_LNKQH_S,
	EN_RUN_VQH_S,
	EN_RUN_UX_S,
	EN_RUN_COM_S,
	EN_RUN_AM_COE_S,
	EN_RUN_DCBC_COE_S,
	EN_RUN_ANG_COE_S,
	EN_RUN_PARASYN_S_STR,
	EN_RUN_PARASYN_S_END=EN_RUN_PARASYN_S_STR+CN_NUM_BOARD_PARA_COM,
	EN_RUN_PARASYN_F_STR=EN_RUN_PARASYN_S_END,
	EN_RUN_PARASYN_F_END=EN_RUN_PARASYN_F_STR+CN_NUM_BOARD_PARA_COM,
	// ��������
	EN_RUN_BAK01=EN_RUN_PARASYN_F_END,
	EN_RUN_BAK02,
	EN_RUN_BAK03,
	EN_RUN_BAK04,
	EN_RUN_BAK05,
	EN_RUN_BAK06,
	EN_RUN_BAK07,
	EN_RUN_BAK08,
	EN_RUN_BAK09,
	EN_RUN_BAK10,
	EN_RUN_END,
};
/*================================================================================*/
//�����ź�ö��
/*================================================================================*/
enum _TYPE_REC_OPT_
{
	EN_OPT_STR=0,                   // �����źſ�ʼ
	// ������ز���
	EN_OPT_PARA_W_SUCC_STR=EN_OPT_STR,
	EN_OPT_PARA_W_SUCC_END=EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_END,
	EN_OPT_PARA_W_FAIL_STR=EN_OPT_PARA_W_SUCC_END,
	EN_OPT_PARA_W_FAIL_END=EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_END,
	EN_OPT_PARA_INIT_SUCC_STR=EN_OPT_PARA_W_FAIL_END,      // ������������ʼ���ɹ�
	EN_OPT_PARA_INIT_SUCC_END=EN_OPT_PARA_INIT_SUCC_STR+EN_BOARD_PARA_END,      // ������������ʼ���ɹ�
	
	EN_OPT_PARA_INIT_FAIL_STR=EN_OPT_PARA_INIT_SUCC_END,      // ������������ʼ���ɹ�
	EN_OPT_PARA_INIT_FAIL_END=EN_OPT_PARA_INIT_FAIL_STR+EN_BOARD_PARA_END,      // ������������ʼ���ɹ�

	EN_OPT_ADJ_DCBC_SUCC  =EN_OPT_PARA_INIT_FAIL_END,           // ������ֱ������У׼�ɹ�
	EN_OPT_ADJ_DCBC_FAIL,           // ������ֱ������У׼ʧ��
	EN_OPT_ADJ_AM_SUCC,             // ��������ֵУ׼�ɹ�
	EN_OPT_ADJ_AM_FAIL,             // ��������ֵУ׼ʧ��
	EN_OPT_ADJ_ANG_SUCC,            // ��������λУ׼�ɹ�
	EN_OPT_ADJ_ANG_FAIL,            // ��������λУ׼ʧ��
	EN_OPT_ADJ_DC_SUCC,             // ֱ�����Զ�У׼�ɹ�
	EN_OPT_ADJ_DC_FAIL,             // ֱ�����Զ�У׼ʧ��
	// �������
	EN_OPT_DEBUG_IN,                // װ�õ���̬����
	EN_OPT_DEBUG_OUT,               // װ�õ���̬�˳�
	EN_OPT_FACT_DEBUG_IN,           // ���ҵ���̬����
	EN_OPT_FACT_DEBUG_OUT,          // ���ҵ���̬�˳�
	
	EN_OPT_DEBUG_LED,               // ָʾ�Ƶ���
	EN_OPT_DEBUG_DO,                // ���ڴ�������
	EN_OPT_DEBUG_GO_S,              // GOOSEͨ�ŵ������
	EN_OPT_DEBUG_GO_Dp,             // GOOSEͨ��˫�����
	EN_OPT_DEBUG_GO_DC,             // GOOSE��������
	EN_OPT_ACT_DEl,                 // ���GOOSE��������
	EN_OPT_ALM_DEl,                 // ����澯����
	EN_OPT_CHK_DEl,                 // ����Լ�����
	EN_OPT_DI_SOE_DEl,              // ���Ӳ����SOE����
	EN_OPT_DO_SOE_DEl,              // ���Ӳ����SOE����
	EN_OPT_GOIN_SOE_DEl,            // ���ӲGOOSE����SOE����
	EN_OPT_GOOUT_SOE_DEl,           // ���ӲGOOSE����SOE����
	EN_OPT_LED_SOE_DEl,             // ���Ӳָʾ��SOE����
	EN_OPT_DPI_SOE_DEl,             // ���˫��ң��SOE����
	EN_OPT_FLAG_SOE_DEl,            // �����ң��SOE����
	EN_OPT_TIME_W_SUCC,             // ʱ���޸ĳɹ�
	EN_OPT_TIME_W_FAIL,             // ʱ���޸�ʧ��
	EN_OPT_BAK01,
	EN_OPT_BAK02,
	EN_OPT_BAK03,
	EN_OPT_BAK04,
	EN_OPT_BAK05,
	EN_OPT_BAK06,
	EN_OPT_BAK07,
	EN_OPT_BAK08,
	EN_OPT_BAK09,
	EN_OPT_BAK10,
	EN_OPT_END,                     // �����źŽ���
};
enum _TYPE_REC_PRVT_
{
	
	EN_PRVT_SOE_STR=0,                     // �ڲ������źſ�ʼ
	EN_PRVT_SOE_BAK0=EN_PRVT_SOE_STR,      // �ڲ������źű���
	EN_PRVT_SOE_END,                       // �ڲ������źŽ���
	
	EN_PRVT_OPT_STR=0,                     // �����źſ�ʼ
	EN_PRVT_OPT_DEV_LINK=EN_PRVT_OPT_STR,  // ���Թ������ӳɹ�
	EN_PRVT_OPT_DEV_BREAK,                 // ���Թ��������ж�
	EN_PRVT_OPT_DATA_R_SUCC,               // �ٻ����ݳɹ�
	EN_PRVT_OPT_DATA_R_FAIL,               // �ٻ�����ʧ��
	EN_PRVT_OPT_FILE_UP_SUCC,              // �ļ��ϴ��ɹ�
	EN_PRVT_OPT_FILE_UP_FAIL,              // �ļ��ϴ�ʧ��
	EN_PRVT_OPT_FILE_DN_SUCC,              // �ļ����سɹ�
	EN_PRVT_OPT_FILE_DN_FAIL,              // �ļ�����ʧ��
	EN_PRVT_OPT_FLASH_BAK_SUCC,            // �������ݳɹ�
	EN_PRVT_OPT_FLASH_BAK_FAIL,            // ��������ʧ��
	EN_PRVT_OPT_PARA_REST_SUCC,            // ������ԭ�ɹ�
	EN_PRVT_OPT_PARA_REST_FAIL,            // ������ԭʧ��
	EN_PRVT_OPT_UPDATE_BOOT0_SUCC,         // BOOT0�����ɹ�
	EN_PRVT_OPT_UPDATE_BOOT0_FAIL,         // BOOT0����ʧ��
	EN_PRVT_OPT_UPDATE_UBOOT_SUCC,         // UBOOT�����ɹ�
	EN_PRVT_OPT_UPDATE_UBOOT_FAIL,         // UBOOT����ʧ��
	EN_PRVT_OPT_UPDATE_SYSTEM_SUCC,        // SYSTEM�����ɹ�
	EN_PRVT_OPT_UPDATE_SYSTEM_FAIL,        // SYSTEM����ʧ��
	EN_PRVT_OPT_UPDATE_FPGA1_SUCC,         // FPGA1�����ɹ�
	EN_PRVT_OPT_UPDATE_FPGA1_FAIL,         // FPGA1����ʧ��
	EN_PRVT_OPT_UPDATE_FPGA2_SUCC,         // FPGA2�����ɹ�
	EN_PRVT_OPT_UPDATE_FPGA2_FAIL,         // FPGA2����ʧ��
	EN_PRVT_OPT_EVENT_ALL_DEl,             // �����������
	EN_PRVT_OPT_RUN_DEl,                   // �����������
	EN_PRVT_OPT_OPT_DEl,                   // �����������
	EN_PRVT_OPT_PRVT_SOE_DEl,              // ����ڲ�����
	EN_PRVT_OPT_PRVT_OPT_DEl,              // �����������
	EN_PRVT_OPT_ETH_W_SUCC,                // ��������޸ĳɹ�
	EN_PRVT_OPT_ETH_W_FAIL,                // ��������޸�ʧ��
	EN_PRVT_OPT_END,                       // �����źŽ���
};

/*================================================================================*/
//������ṹ��
/*================================================================================*/
// GOOSE�����������Դö�ٸ���
#define CN_ACT_SNUM (32)
typedef struct
{
	WORD			wIndex; 						// ��¼ö��
	WORD			wSrcType;						// ����Դ����
	WORD			wSrcIndex[CN_ACT_SNUM];			// ����Դö��
	WORD			wDoIndex;						// ����ö��
	WORD			wDoRetIndex;					// ���ڷ�У
	WORD			wCfg; 							// ��������
	WORD			wValType1; 						// �����¼��������1
	WORD			wValType2; 						// �����¼��������2
	WORD			wValType3; 						// �����¼��������3
	WORD			wValType4; 						// �����¼��������4
	WORD			wValType5; 						// �����¼��������5
	WORD			wValType6; 						// �����¼��������6
	INT8S			byName[CN_LEN_NAME]; 			// ��¼����
	INT8S			byPinName[CN_LEN_NAME];			// ���������
} tagActTab;
/*================================================================================*/
//������ṹ��
/*================================================================================*/
typedef struct
{
	WORD			wIndex; 						// ��¼ö��
	WORD			wParaEna; 						// Ͷ�˲���ö��
	WORD			wParaTime; 						// ʱ�����ö��
	DWORD			dwDefTime; 						// Ĭ��ʱ�����
	DWORD			dwRetTime; 						// Ĭ�Ϸ���ʱ�����
	WORD			wCfg; 							// ��������
	WORD			wValType1; 						// �����¼��������1
	WORD			wValType2; 						// �����¼��������2
	WORD			wValType3; 						// �����¼��������3
	INT8S			byName[CN_LEN_NAME]; 			// ��¼����
	INT8S			byPinName[CN_LEN_NAME];			// ���������
} tagAlmTab;
typedef struct
{
	WORD			wIndex; 						// ��¼ö��
	//WORD			wParaEna; 						// Ͷ�˲���ö��
	//WORD			wParaTime; 						// ʱ�����ö��
	DWORD			dwActCnt; 						// Ĭ��ʱ�����
	DWORD			dwRetCnt; 						// Ĭ�Ϸ���ʱ�����
	WORD			wCfg; 							// ��������
	WORD			wValType1; 						// �����¼��������1
	WORD			wValType2; 						// �����¼��������2
	WORD			wValType3; 						// �����¼��������3
	INT8S			byName[CN_LEN_NAME]; 			// ��¼����
	INT8S			byPinName[CN_LEN_NAME]; 		// ���������
} tagChkTab;

typedef struct
{
	WORD			wIndex; 						// ��¼ö��
	WORD			wCfg; 							// ��������
	INT8S			byName[CN_LEN_NAME]; 			// ��¼����
	INT8S			byPinName[CN_LEN_NAME]; 		// ���������
} tagRunTab;

typedef struct
{
	WORD			wIndex; 						// ��¼ö��
	WORD			wCfg; 							// ��������
	WORD			wValType1; 						// �����¼��������1
	WORD			wValType2; 						// �����¼��������2
	WORD			wValType3; 						// �����¼��������3
	INT8S			byName[CN_LEN_NAME]; 			// ��¼����
	INT8S			byPinName[CN_LEN_NAME]; 		// ���������
} tagOptTab;

typedef struct
{
	WORD			wIndex; 						// ��¼ö��
	WORD			wCfg; 							// ��������
	INT8S			byName[CN_LEN_NAME]; 			// ��¼����
	INT8S			byPinName[CN_LEN_NAME]; 		// ���������
} tagPrvtSoeTab;

typedef struct
{
	WORD			wIndex; 						// ��¼ö��
	WORD			wCfg; 							// ��������
	INT8S			byName[CN_LEN_NAME]; 			// ��¼����
	INT8S			byPinName[CN_LEN_NAME]; 		// ���������
} tagPrvtOptTab;

/*================================================================================*/
// �궨��
/*================================================================================*/
#define CN_NUM_ACT    (EN_ACT_END)
#define CN_NUM_ALM    (EN_ALM_END)
#define CN_NUM_CHK    (EN_CHK_END)
#define CN_NUM_RUN    (EN_RUN_END)
#define CN_NUM_OPT    (EN_OPT_END)
#define CN_NUM_PRVT_SOE    (EN_PRVT_SOE_END)
#define CN_NUM_PRVT_OPT    (EN_PRVT_OPT_END)


#define CN_NUM_ALM_GOCB_DATA  (EN_ALM_GOCB_DATA_END-EN_ALM_GOCB_DATA_STR)
#define CN_NUM_ALM_GOCB_TEST  (EN_ALM_GOCB_TEST_END-EN_ALM_GOCB_TEST_STR)

/*================================================================================*/
// ����������
/*================================================================================*/
extern const tagActTab g_tActTab[];
extern const DWORD     g_NUM_ACT;
extern const tagAlmTab g_tAlmTab[];
extern const DWORD     g_NUM_ALM;
extern const tagChkTab g_tChkTab[];
extern const DWORD     g_NUM_CHK;
extern const tagOptTab g_tOptTab[];
extern const DWORD     g_NUM_OPT;
extern const tagRunTab g_tRunTab[];
extern const DWORD     g_NUM_RUN;

extern const tagPrvtSoeTab g_tPrvtSoeTab[];
extern const DWORD         g_NUM_PRVT_SOE;
extern const tagPrvtOptTab g_tPrvtOptTab[];
extern const DWORD         g_NUM_PRVT_OPT;

#endif  // _CONST_REC_H_

