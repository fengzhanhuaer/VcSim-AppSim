/*================================================================================
 * �ļ�������ϵͳ��Դ��������
 * �ļ��汾: V1.00
 * ����ʱ��:
 * �汾�޶�:
 * �޶���Ա:
 *================================================================================*/
#ifndef _IES_IMSRC_H_
#define _IES_IMSRC_H_

#include "IES_IMPub.h"

/*================================================================================*/
// �ṹ�嶨��
/*================================================================================*/
// ����汾��Ϣ
typedef struct
{
	UINT32        dwVerSion;                   // ����汾��
	UINT32        dwCrc;                       // ����CRCУ����
	UINT32        dwTime;                      // ����汾ʱ��
}tagSoftVer;
// �������
typedef struct
{
	DWORD          dwIp;
	DWORD          dwMask;
	DWORD          dwGate;
	DWORD          dwFlag;
}tagDevEthnet;

// װ�ð汾��Ϣ
typedef struct
{
	BYTE          byRamScan1;
	UINT32        dwCrc;                       // CCD�ļ�CRC
	UINT32        dwCrcOth;                    // ��һ�忨CCD�ļ�CRC
	char          byID[64];                    // Ψһ�Ա���
	BYTE          byRamScan2;
	char          byVerName[48];               // �汾��Ϣ
	BYTE          byRamScan3;
	char          byVerOthName[48];            // �Բ�CPU�汾��Ϣ
	BYTE          byRamScan4;
	BYTE          byDevEthnet;
	tagDevEthnet  tDevEthnet;
	BYTE          byRamScan5;
	tagDevEthnet  tDevEthnetOth;
	BYTE          byRamScan6;
}tagDevInfor;
// ģ��������(����)
typedef struct
{
	//INT32         iRe;                                // ʵ��
	//INT32         iIm;                                // �鲿
	UINT32        dwAm;                               // ��ֵ(����)
	UINT32        dwAmJ;                              // ��ֵ(����)
	UINT32        dwAngle;                            // ������λ
	UINT32        dwAngleRel;                         // �����λ
} tagVector;
// ��1970��1��1��0ʱ0��0��0����Ϊʱ�ӻ�׼��ʼ��UTCʱ�����ݽṹ
typedef struct
{
// �̶�������ǰ,����ȡ64λ����
    DWORD           dwUSecond_L;                    // us_L ΢���32λ
    DWORD           dwUSecond_H;                    // us_H ΢���32λ
    DWORD           dwLeapSecFlg;                   // ʱ��Ʒ��
} tagTimeUTC;
// ģ�������ݽṹ��
typedef struct
{
	//  ������Ϣ
	BYTE      byRamScan1;
	WORD      wSvPubNum;                            // SV������SV����ͨ���ܸ��� �������ʱ
	WORD      wSvPubDatNum;                         // SV������SV����ͨ��ģ�������ݸ���
	WORD      wSvPubChg;                            // SV������SV�������ö�̬����
	WORD      wSvPubCfg[CN_NUM_ANA];                // SV������SVͨ���뱾��ͨ��ӳ���,��ӳ��Ϊ0xffff
	BYTE      byRamScan2;
	WORD      wSvPubChn[CN_NUM_ANA];                // SV����������ͨ����SVͨ��ӳ���,��ӳ��Ϊ0xffff
	BYTE      byRamScan3;
	WORD      wSvPubSend[CN_NUM_ANA];               // SV������SVͨ���뱾��ͨ��ӳ�����������
	BYTE      byRamScan4;
	BOOL      bSvPubPol[CN_NUM_ANA];                // SV��������������
	BYTE      byRamScan5;
	// ��������
	DWORD     dwAnaFramNum;                         // ����֡���
	DWORD     dwAnaFramDNum;                        // ����֡��Ų�
	INT32     iAnaSam[CN_NUM_ANA];                  // ģ����ԭʼ����ֵ
	BYTE      byRamScan6;
	INT32     iAnaSamBak[CN_NUM_ANA];               // ģ����ԭʼ����ֵ����
	BYTE      byRamScan7;
	BYTE      bySvCbPubNum;                         // SV�������ƿ����
	DWORD     dwSvCbPubCfg;                         // SV�������ƿ����ñ�־��
#if(CN_SV_IN_ENA)
	// ��α�֤A��B�׶�Ӧ���ƿ�
	BYTE      bySvCbSubNum;                         // SV���Ŀ��ƿ����
	DWORD     dwSvCbSubCfg[CN_NUM_BOARD_SV];        // SV���Ŀ��ƿ����ñ�־��
	BYTE      byRamScan71;
	DWORD     dwSvCbStatus[CN_NUM_BOARD_SV];        // SV���Ŀ��ƿ�״̬��־��
	BYTE      byRamScan72;
	// ��������
	DWORD     dwSvQ[CN_NUM_SV];                     // SV����Ʒ��
	BYTE      byRamScan73;
	BOOL      bSvSub[CN_NUM_SV];                    // SV��������������־
	BYTE      byRamScan74;
	BYTE      bySvCb[CN_NUM_SV];                    // SV���Ŀ��ƿ�ӳ��(��Ҫ�Լ�)
	BYTE      byRamScan75;
#endif
	// �Լ�״̬
	BOOL      bFrameErr;                            // ģ����֡�쳣
	// �������
	BYTE      byAnaVecChg;                          // �������ݸ��±�־
	tagVector tAnaVectFst[CN_NUM_ANA];              // ģ����һ��ֵ����
	BYTE      byRamScan8;
	tagVector tAnaVect[CN_NUM_ANA];                 // ģ��������ֵ����
	BYTE      byRamScan9;
	tagVector tAnaVectHum[CN_NUM_ANA][CN_HUM_NUM];  // ģ����г��
	BYTE      byRamScan10;
	BYTE      byFrChg;                              // Ƶ�ʸ��±�־
	DWORD     dwFrCal[CN_NUM_CAL];                  // ģ����Ƶ��
	BYTE      byRamScan11;
	DWORD     dwAnaQ[CN_NUM_ANA];                   // ģ����Ʒ��
	BYTE      byRamScan12;
	BYTE      byAnaQChg;                            // Ʒ�ʸ���
	// ��FPGA�·�ϵ��
	BYTE      byAnaAmCoeChg;                        // ��ֵУ׼ϵ���·���־
	DWORD     dwAnaAmCoe[CN_NUM_AD];               // ��ֵУ׼ϵ��
	BYTE      byRamScan13;
	BYTE      byAnaAngCoeChg;                       // AD΢��ϵ���·���־
	WORD      wAnaAngCoe[CN_NUM_JZ*2];              // AD΢��ϵ��
	BYTE      byRamScan14;
	BYTE      byAnaDcCoeChg;                        // ֱ������ϵ���·���־
	INT32     iAnaDcCoe[CN_NUM_AD];                 // ֱ������ϵ��
	BYTE      byRamScan15;
	// �������ʾ�·�ϵ��
	BYTE      byAnaPtCtChg;                         // ����·���־
	FLOAT32   fAnaPtCt[CN_NUM_ANA];                 // ���
	BYTE      byRamScan16;
} tagAna;
// IO���ݽṹ��
typedef struct
{
	//1.1 DI��������
	BYTE       byRamScan1;
	DWORD      dwDICnt[CN_NUM_BOARD_DI];          // DI������λ���
	BYTE       byRamScan2;
	DWORD      dwDIIn[CN_NUM_BOARD_DI];           // DIԭʼ����ֵ32λ��
	BYTE       byRamScan3;
	tagTimeUTC tDIInUTC[CN_NUM_BOARD_DI];         // DIԭʼʱ��
	BYTE       byRamScan4;
	//1.2 DI�������
	BOOL       bDIHldIn[CN_NUM_DI];               // DI������״̬������
	BYTE       byRamScan5;
	DWORD      dwDIHldIn32[CN_NUM_BOARD_DI];      // DI������״̬32λ��
	BYTE       byRamScan6;
	DWORD      dwDIHldXor32[CN_NUM_BOARD_DI];     // DI������״̬��λ��־
	BYTE       byRamScan7;
	tagTimeUTC tDIHldUTC[CN_NUM_DI];              // DI����ǰʱ��
	BYTE       byRamScan8;
//	DWORD      dwBoardDIQ[CN_NUM_BOARD_DI];       // DIƷ��
	DWORD      dwDIQ[CN_NUM_DI];                  // DIƷ��
	BYTE       byRamScan9;
	DWORD      dwDIQChg;                          // DIƷ�ʸ���
	BYTE       byDIFstToSoe;                      // DI��һ֡��������
	BYTE       byDIFstToGoose;                    // DI��һ֡����GOOSE
	//2.1 GOOSE����������Ϣ
	BYTE       byGoCbSubNum;                      // GO������ƿ����(���忨)
	BYTE       byGoCbSubNumCom;                   // GO������ƿ����(��һ�忨)
	BYTE       byGoInSub[CN_NUM_GOIN];            // GO����״̬
	BYTE       byRamScan10;
	BYTE       byGoInGoCb[CN_NUM_GOIN];           // GO���������ƿ�ӳ��(��Ҫ�Լ�)
	BYTE       byRamScan11;
	WORD       wGoInAppId[CN_NUM_GOIN];           // GO����APPID
	BYTE       byRamScan12;
	DWORD      dwGoInSubStatus[CN_NUM_GOCB_SUB];  // GO������ƿ��쳣����
	BYTE       byRamScan13;
	//2.2 GOOSE������������
	DWORD      dwGoInCnt;                         // GO���ļ�����
	WORD       wGoInQ[CN_NUM_GOIN];               // GO����ֵ����(Ʒ��)
	BYTE       byRamScan14;
	tagTimeUTC tGoInUTC[CN_NUM_GOIN];             // GO��������ʱ��
	BYTE       byRamScan15;
	tagTimeUTC tGoInUTCRev;                       // GO�������ݽ���ʱ��
	//2.3 GOOSE����״̬��
	DWORD      dwGoInStatusA[CN_NUM_GOCB_SUB];    // GO������ƿ�A��״̬��
	BYTE       byRamScan16;
	DWORD      dwGoInStatusB[CN_NUM_GOCB_SUB];    // GO������ƿ�B��״̬��
	BYTE       byRamScan17;
	//2.4 GOOSE����״̬�ֽ���
//	BOOL       bGoInLink[CN_NUM_GOCB_SUB];        // GO������ƿ����
	BYTE       byRamScan18;
//	BOOL       bGoInDatErr[CN_NUM_GOCB_SUB];      // GO������ƿ������쳣
	BYTE       byRamScan19;
//	BOOL       bGoInTestErr[CN_NUM_GOCB_SUB];     // GO������ƿ���޲�һ��
	BYTE       byRamScan20;
//	BOOL       bTimeLive0[CN_NUM_GOCB_SUB];       // GO������ƿ���������Ϊ0
	BYTE       byRamScan21;
	//2.5 GOOSE�����������
	BOOL       bGoIn[CN_NUM_GOIN];                // GO����״̬
	BYTE       byRamScan22;
	BOOL       bGoInXor[CN_NUM_GOIN];             // GO����״̬��λ
	BYTE       byRamScan23;
	BOOL       bGoInValid[CN_NUM_GOIN];           // GO������Ч״̬
	BYTE       byRamScan24;
	BOOL       bGoInValidXor[CN_NUM_GOIN];        // GO������Ч״̬��λ
	BYTE       byRamScan25;
	BYTE       byGoInInValid[CN_NUM_GOIN];        // GO������Ч״̬ԭ��
	BYTE       byRamScan26;
	tagTimeUTC dwGoInValidT[CN_NUM_GOIN];         // GO��������ʱ��(��δʹ��)
	BYTE       byRamScan27;
	//3.1 ˫���������
	BYTE       byDpiIn[CN_NUM_DPI];               // ˫��λ����Ϣ
	BYTE       byRamScan28;
	BYTE       byDpiInXor[CN_NUM_DPI];            // ˫��λ����Ϣ��λ
	BYTE       byRamScan29;
	tagTimeUTC tDpiUTC[CN_NUM_DPI];               // ˫���λʱ��
	BYTE       byRamScan30;
	DWORD      dwDpiQ[CN_NUM_DPI];                // ˫��Ʒ��
	BYTE       byRamScan31;
	BYTE       byDpiFstToSoe;                     // ˫���һ֡����SOE
	BYTE       byDpiFstToGoose;                   // ˫���һ֡����GOOSE
	//4.1 DO�ϳ�����
	BOOL       bDOOut[CN_NUM_DO];                 // DO�������ݲ�����
	BYTE       byRamScan32;
	BOOL       bDOOutXor[CN_NUM_DO];              // DO�������ݲ�����
	BYTE       byRamScan33;
	//5.1 GOOSE����������Ϣ
	BYTE       byGoCbPubNum;                      // GO�������ƿ����
	BYTE       byGoPub[CN_NUM_GOOUT];             // GO�����̵�ַ���ñ�־
	BYTE       byRamScan34;
	BYTE       byGoPubCb[CN_NUM_GOOUT];           // GO�������ƿ�
	BYTE       byRamScan35;
	DWORD      dwGoPubStatus[CN_NUM_GOCB_PUB];        // GO�����쳣����
	BYTE       byRamScan36;
	//5.2 GOOSE�����ϳ�����
	BOOL       bGoOut[CN_NUM_GOOUT];              // GO����ֵ������
	BYTE       byRamScan37;
	BOOL       bGoOutCom[CN_NUM_GOOUT];           // GO����ֵ������
	BYTE       byRamScan38;
	BOOL       bGoOutXor[CN_NUM_GOOUT];           // GO����ֵ�仯��־
	BYTE       byRamScan39;
	DWORD      dwGoOutQ[CN_NUM_GOOUT];            // GO����Ʒ��
	BYTE       byRamScan40;
	tagTimeUTC tGoOutT[CN_NUM_GOOUT];             // GO��������ʱ��
	BYTE       byRamScan41;
	//6.1 ָʾ�ƺϳ�����
	BOOL       bLedOut[CN_NUM_LED];               // LED����ֵ������
	
	BYTE       byRamScan42;
	BOOL       bLedOutCom[CN_NUM_LED];            // LED����ֵ������
	
	BYTE       byRamScan43;
	BOOL       bLedOutHld[CN_NUM_LED];            // LED����ֵ���ֱ�־
	BYTE       byRamScan44;
	BYTE       byLedPtr;                          // LEDָʾ��ָ��
	BYTE       byRamScan45;
// �忨״̬
	DWORD      dwDIBoardCnt[CN_NUM_BOARD_DI];
	BYTE       byRamScan46;
} tagIO;
// ֱ�����ݻ��崰
typedef struct
{
	INT32   iDCBuf;            // DCֱ�������������ֵ
	INT16   iDCMax;            // DCֱ�������������ֵ
	INT16   iDCMin;            // DCֱ������������Сֵ
	WORD    wDCPtr;            // DCֱ�������������
	WORD    wDCCnt;            // DCֱ������������Ч����
}tagDCSamIn;
// ֱ�����ݽṹ��
typedef struct
{
	// ��������
	BYTE    byRamScan1;
	DWORD   dwDCRefCnt[CN_NUM_BOARD_DC];     // ֱ��DC����ˢ�¼�����
	BYTE    byRamScan2;
	BOOL    bDCFresh[CN_NUM_BOARD_DC];       // ֱ��DC����ˢ�±�־
	BYTE    byRamScan3;
	BOOL    bDCDispFresh[CN_NUM_BOARD_DC];   // ֱ��DC���ݽ���ˢ�±�־
	BYTE    byRamScan4;
	BOOL    bDCGoOutFresh[CN_NUM_BOARD_DC];  // ֱ��DC���ݰ������ˢ�±�־
	BYTE    byRamScan5;
	BOOL    bDCCommFresh[CN_NUM_BOARD_DC];   // ֱ��DC����GOOSEˢ�±�־
	BYTE    byRamScan6;
	DWORD   dwDCBoardCnt[CN_NUM_BOARD_DC];   // DC�忨״̬������
	BYTE    byRamScan7;
	WORD    wDCRefPtr[CN_NUM_BOARD_DC];     // ֱ��DC����ˢ��ָ��
	BYTE    byRamScan8;
	// ԭʼ����
	INT32   iDCIn[CN_NUM_DC];            // DC��������
	BYTE    byRamScan9;
	INT32   iDCOut[CN_NUM_DC];           // DC����ֵ�������
	BYTE    byRamScan10;
	FLOAT32 fDCOut[CN_NUM_DC];           // DC����ֵ�������
	BYTE    byRamScan11;
	// ���ݴ�(�׶����ݴ�)
	tagDCSamIn tDCSamIn[CN_NUM_DC_SAM];
	// һ��ֵ����
	INT32   iDCOutFst[CN_NUM_DC_SAM];    // DCһ��ֵ�������
	BYTE    byRamScan12;
	FLOAT32 fDCOutFst[CN_NUM_DC_SAM];    // DCһ��ֵ�������
	BYTE    byRamScan13;
	// ͨ������
	BOOL    bDCChg[CN_NUM_DC];           // DC�仯��־
	BYTE    byRamScan14;
	INT32   iDCOutCom[CN_NUM_DC];        // DC�������(GOOSE���)
	BYTE    byRamScan15;
	FLOAT32 fDCOutCom[CN_NUM_DC];        // DC�������(GOOSE���)
	BYTE    byRamScan16;
	UINT32  dwDCOutQ[CN_NUM_BOARD_DC];   // DCƷ��
	BOOL    bDCOutQChg[CN_NUM_BOARD_DC]; // DCƷ�ʱ仯
	BYTE    byRamScan17;
	tagTimeUTC tDCOut[CN_NUM_DC];        // DCʱ��
	BYTE    byRamScan18;
} tagDC;

// �����ṹ��
typedef struct
{
	BYTE    byRamScan1;
	DWORD   dwChgCnt[CN_NUM_BOARD_PARA];   // �����仯����
	BYTE    byRamScan2;
	//DWORD   dwChgWRef[CN_NUM_BOARD_PARA];  // �����洢ˢ�±�־
	BYTE    byRamScan3;
	BOOL    bCrcCom;                       // ����Crc�����־
	BOOL    bCrcOthChg;                    // ��һ�忨����Crc�仯��־
	DWORD   dwCrc[CN_NUM_BOARD_PARA];      // ����CrcУ����
	BYTE    byRamScan4;
	DWORD   dwCrcOth[CN_NUM_BOARD_PARA];   // ��һ�忨����CrcУ����
	BYTE    byRamScan5;
	DWORD   dwPara[CN_NUM_PARA];           // 
	BYTE    byRamScan6;
	DWORD   dwCoe[CN_NUM_PARA];            // 
	BYTE    byRamScan7;
	FLOAT32 fPara[CN_NUM_PARA];
	BYTE    byRamScan8;
	DWORD   dwParaBak[CN_NUM_PARA];        // ����д����
	BYTE    byRamScan9;
	WORD    wParaCfg[CN_NUM_PARA];         // ����������
	BYTE    byRamScan10;
} tagPara;
// �ڴ�ɨ�����ݽṹ��
typedef struct
{
	BYTE *pbyRamPtr;    // �ڴ�ɨ����ַ 
	//DWORD dwRamValue;
	DWORD dwRamNo;      // �ڴ�ɨ������
} tagRamDot;

typedef struct
{
	BYTE  byRamScan1;
	tagRamDot tRamDot[CN_RAMSCAN_MAX];
	BYTE  byRamScan2;
	DWORD dwRamPtr;       // �ڴ�ɨ�������� 
	DWORD dwRamChkPtr;    // �ڴ�ɨ����Լ���� 
	BYTE  byRamScan3;
} tagRamScan;

// �������ݽṹ��
typedef struct
{
	BYTE  byRamScan1;
	// ϵͳʱ��
	tagTimeUTC   tSysTimeUTC;    // ϵͳʱ��
	// ϵͳ����ȫ�ֱ�־
	BOOL    bSysLockBH;          // ϵͳ����������־
	BOOL    bSysLockCK;          // ϵͳ������ر�־
	BOOL    bSysTest;            // ϵͳ���м��ޱ�־
	BOOL    bSysTestXor;         // ϵͳ���м��ޱ仯��־
	BOOL    bSysReset;           // �͵���������
	BOOL    bSysPower;           // �ϵ���ɱ�־
	BOOL    bSysBs;              // װ���ܱ���
	// ȫ�ּ�����
	UINT32  dwSysTimer;          // ʱ��̵���ʱ��
	// �ϵ������
	DWORD   dwSysPowCnt;         // �ϵ������
	// ���ɼ�����
	DWORD   dwSysCnt;            // ���ɼ�����
	// �������Լ��־
	BOOL    bConstChk[CN_NUM_DTYPE+CN_NUM_CFG];
	BYTE    byRamScan2;
} tagPub;

// �������(3��)
typedef struct
{
	WORD    wMeaType[3];         // ��������1~3
	UINT32  iMeaValue[3];        // ����ֵ1~3
}tagMsgValue;
// Act�м�����
typedef struct
{
	BOOL           bActState;         // GOOSE����״̬
	BYTE           byFlag;            // �����¼��־
	WORD           wActInIndex;       // GOOSE����ö�ټ�¼
	WORD           wActOutIndex;      // ��������ö�ټ�¼
	DWORD          dwTimeCnt;         // ʱ��̵���
	UINT32         iMeaValue[6];      // ����ֵ1~6
	tagTimeUTC     tActT;             // GOOSE����ʱ��
}tagActEvent;
// Act״̬
typedef struct
{
	BYTE           byRamScan1;
	BOOL           bActIn[CN_NUM_ACT];            // GOOSE����״̬
	BYTE           byRamScan2;
	BOOL           bActOut[CN_NUM_ACT];           // ����״̬
	BYTE           byRamScan3;
	BOOL           bActOutRet[CN_NUM_ACT];        // ���ڷ�У״̬
	BYTE           byRamScan4;
	tagActEvent    tActEvent[CN_NUM_ACT];
	BYTE           byRamScan5;
}tagActState;
// Alm״̬
typedef struct
{
	BYTE           byRamScan1;
	BOOL           bAlmIn[CN_NUM_ALM];             // �澯�¼�״̬������
	BYTE           byRamScan2;
	BOOL           bAlmOut[CN_NUM_ALM];            // �澯�¼�״̬�����
	BYTE           byRamScan3;
	BOOL           bAlmXor[CN_NUM_ALM];            // �澯�¼���λ״̬
	BYTE           byRamScan4;
	tagMsgValue    tRecValue[CN_NUM_ALM];          // ���������¼
	BYTE           byRamScan5;
}tagAlmState;
// Chk״̬
typedef struct
{
	BYTE           byRamScan1;
	BOOL           bChkIn[CN_NUM_CHK];             // �Լ��¼�״̬��־��
	BYTE           byRamScan2;
	BOOL           bChkOut[CN_NUM_CHK];            // �Լ��¼�״̬�����
	BYTE           byRamScan3;
	BOOL           bChkXor[CN_NUM_CHK];            // �Լ��¼���λ״̬
	BYTE           byRamScan4;
	tagMsgValue    tRecValue[CN_NUM_CHK];          // ���������¼
	BYTE           byRamScan5;
	UINT32         dwChkActCnt[CN_NUM_CHK];
	BYTE           byRamScan6;
	UINT32         dwChkRetCnt[CN_NUM_CHK];
	BYTE           byRamScan7;
}tagChkState;

// SOE����
typedef struct
{
	WORD           wIndex;             // ����ö��
	WORD           wState;             // ����״̬
	WORD           wQ;                 // Ʒ��
	tagTimeUTC     tTime;              // ʱ��
}tagSoeEvent;

typedef struct
{
	WORD           wIndex;             // ����ö��
	WORD           wState;             // ����״̬
	tagTimeUTC     tTime;              // ʱ��
	UINT32         iMeaValue[3];       // ����ֵ1~3
}tagCosEvent;

typedef struct
{
	WORD           wIndex;             // ����ö��
	WORD           wState;             // ����״̬
	tagTimeUTC     tTime;              // ʱ��
	UINT32         iMeaValue[6];       // ����ֵ1~6
}tagCosEvent6;

typedef struct
{
	WORD           wIndex;             // ö��
	WORD           wState;             // ״̬
	WORD           wResult;            // ���
	tagTimeUTC     tTime;              // ʱ��
}tagSjEvent;

typedef struct
{
	BYTE           byRamScan1;
	WORD           wWptr;              // дָ��
	WORD           wRptr;              // ��ָ��
	WORD           wFlag;              // ���б�־
	BYTE           byRamScan2;
	tagCosEvent6   tEvent[CN_NUM_RPT_ACT];
	BYTE           byRamScan3;
	// ��Ƽ�¼
	WORD           wSjWptr;           // дָ��
	WORD           wSjRptr;           // дָ��
	WORD           wSjFlag;           // ���б�־
	WORD           wSjCtrl;           // ���Ʊ�־
	BYTE           byRamScan4;
	tagSjEvent     tSjEvent[CN_NUM_RPT_ACT];
	BYTE           byRamScan5;
	
}tagActQueue;

typedef struct
{
	BYTE           byRamScan1;
	WORD           wWptr;              // дָ��
	WORD           wRptr;              // ��ָ��
	WORD           wFlag;              // ���б�־
	WORD           wBak;               // ���ñ�־
	BYTE           byRamScan2;
	tagCosEvent    tEvent[CN_NUM_RPT_ALM];
	BYTE           byRamScan3;
}tagAlmQueue;

typedef struct
{
	BYTE           byRamScan1;
	WORD           wWptr;              // дָ��
	WORD           wRptr;              // ��ָ��
	WORD           wFlag;              // ���б�־
	WORD           wBak;               // ���ñ�־
	BYTE           byRamScan2;
	tagCosEvent    tEvent[CN_NUM_RPT_CHK];
	BYTE           byRamScan3;
}tagChkQueue;

typedef struct
{
	BYTE           byRamScan1;
	WORD           wWptr;              // дָ��
	WORD           wRptr;              // ��ָ��
	WORD           wFlag;              // ���б�־
	WORD           wBak;               // ���ñ�־
	BYTE           byRamScan2;
	tagCosEvent    tEvent[CN_NUM_RPT_RUN];
	BYTE           byRamScan3;
}tagRunQueue;

typedef struct
{
	BYTE           byRamScan1;
	WORD           wWptr;              // дָ��
	WORD           wRptr;              // ��ָ��
	WORD           wFlag;              // ���б�־
	WORD           wBak;               // ���ñ�־
	BYTE           byRamScan2;
	tagCosEvent    tEvent[CN_NUM_RPT_OPT];
	BYTE           byRamScan3;
}tagOptQueue;


typedef struct
{
	BYTE           byRamScan1;
	WORD           wWptr;              // дָ��
	WORD           wRptr;              // �����ָ��
	WORD           wGoRptr;            // GOOSE��ָ��
	WORD           wFlag;              // ���б�־
	BYTE           byRamScan2;
	tagSoeEvent    tEvent[CN_NUM_RPT_DI];
	BYTE           byRamScan3;
}tagDiQueue;

typedef struct
{
	BYTE           byRamScan1;
	WORD           wWptr;              // дָ��
	WORD           wRptr;              // ��ָ��
	WORD           wGoRptr;            // GOOSE��ָ��
	WORD           wFlag;              // ���б�־
	BYTE           byRamScan2;
	tagSoeEvent    tEvent[CN_NUM_RPT_DPI];
	BYTE           byRamScan3;
}tagDpiQueue;

typedef struct
{
	BYTE           byRamScan1;
	WORD           wWptr;              // дָ��
	WORD           wRptr;              // ��ָ��
	WORD           wGoRptr;            // GOOSE��ָ��
	WORD           wFlag;              // ���б�־
	BYTE           byRamScan2;
	tagSoeEvent    tEvent[CN_NUM_RPT_DO];
	BYTE           byRamScan3;
}tagDoQueue;

typedef struct
{
	BYTE           byRamScan1;
	WORD           wWptr;              // дָ��
	WORD           wRptr;              // ��ָ��
	WORD           wGoRptr;            // GOOSE��ָ��
	WORD           wFlag;              // ���б�־
	BYTE           byRamScan2;
	tagSoeEvent    tEvent[CN_NUM_RPT_GOIN];
	BYTE           byRamScan3;
}tagGoInQueue;

typedef struct
{
	BYTE           byRamScan1;
	WORD           wWptr;              // дָ��
	WORD           wRptr;              // ��ָ��
	WORD           wGoRptr;            // GOOSE��ָ��
	WORD           wFlag;              // ���б�־
	BYTE           byRamScan2;
	tagSoeEvent    tEvent[CN_NUM_RPT_GOOUT];
	BYTE           byRamScan3;
}tagGoOutQueue;

typedef struct
{
	BYTE           byRamScan1;
	WORD           wWptr;              // дָ��
	WORD           wRptr;              // ��ָ��
	WORD           wFlag;              // ���б�־
	WORD           wBak;               // ���ñ�־
	BYTE           byRamScan2;
	tagSoeEvent    tEvent[CN_NUM_RPT_LED];
	BYTE           byRamScan3;
}tagLedQueue;

typedef struct
{
	BYTE           byRamScan1;
	WORD           wWptr;              // дָ��
	WORD           wRptr;              // ��ָ��
	WORD           wFlag;              // ���б�־
	WORD           wBak;               // ���ñ�־
	BYTE           byRamScan2;
	tagSoeEvent    tEvent[CN_NUM_RPT_FLAG];
	BYTE           byRamScan3;
}tagFlagQueue;
/*================================================================================*/
// Ӧ�ò�ȫ��������
/*================================================================================*/
// �汾��Ϣ
extern tagDevInfor  g_tDevInfor;              // �汾��Ϣ
// ���ݽ�����
extern tagAna       g_tagAna;                 // ģ��������
extern tagIO        g_tagIO;                  // IO����
extern tagDC        g_tagDC;                  // ֱ������
extern tagPara      g_tagPara;                // ����
extern tagRamScan   g_tagRamScan;             // �ڴ�ɨ��ṹ��
extern tagPub       g_tagPub;                 // ƽ̨��������
// Ӧ���м��־
extern BOOL         g_bFlag[CN_NUM_FLAG+1];   // ȫ�ֲ���������־����
extern INT32        g_iInter[CN_NUM_INTER+1]; // ȫ���ڲ����ݶ���
// ����ʵʱ״̬
extern tagActState     g_tActState;           // �澯�¼�ʵʱ״̬
extern tagAlmState     g_tAlmState;           // �澯�¼�ʵʱ״̬
extern tagChkState     g_tChkState;           // �Լ��¼�ʵʱ״̬
// �������
extern tagActQueue     g_tActQueue;            // GOOSE�����¼��������
extern tagAlmQueue     g_tAlmQueue;            // �澯�¼��������
extern tagChkQueue     g_tChkQueue;            // �Լ��¼��������
extern tagDiQueue      g_tDiQueue;             // Ӳ���뵥��SOE�������
extern tagDpiQueue     g_tDpiQueue;            // Ӳ����˫��SOE�������
extern tagDoQueue      g_tDoQueue;             // Ӳ����SOE�������
extern tagGoInQueue    g_tGoInQueue;           // GOOSE����SOE�������
extern tagGoOutQueue   g_tGoOutQueue;          // GOOSE����SOE�������
extern tagLedQueue     g_tLedQueue;            // ָʾ��SOE�������

/*================================================================================*/
// Ӧ�ò�ȫ�����ݽӿ�(�����±�Ϊ����ʱʹ�÷���ӿ�ȡ����)
/*================================================================================*/
// Դ���ݻ�ȡ
#define CN_Get_Dat_Src_P(wTypeIndex)            (((wTypeIndex)<CN_NUM_DTYPE)?g_tDTypeTab[(wTypeIndex)].bDatAtr:0);
#define CN_Get_Dat_Src_NUM(wTypeIndex)          (((wTypeIndex)<CN_NUM_DTYPE)?g_tDTypeTab[(wTypeIndex)].wDatNum:0);
#define CN_Get_Dat_Src(wTypeIndex,wDatIndex)    (((wTypeIndex)<CN_NUM_DTYPE)?(((wDatIndex)<g_tDTypeTab[(wTypeIndex)].wDatNum)?g_tDTypeTab[(wTypeIndex)].bDatAtr[(wDatIndex)]:0):0);
// ģ��������--����ֵ
#define CN_Get_Ana_Am(wIndex)         (((wIndex)<CN_NUM_ANA)?g_tagAna.tAnaVect[(wIndex)].dwAm:0);
#define CN_Get_Ana_AmJ(wIndex)        (((wIndex)<CN_NUM_ANA)?g_tagAna.tAnaVect[(wIndex)].dwAmJ:0);
#define CN_Get_Ana_Ang(wIndex)        (((wIndex)<CN_NUM_ANA)?g_tagAna.tAnaVect[(wIndex)].dwAngle:0);
// ģ��������--����ֵ
#define CN_Get_Ana_FAm(wIndex)        (((wIndex)<CN_NUM_ANA)?g_tagAna.tAnaVectFst[(wIndex)].dwAm:0);
#define CN_Get_Ana_FAmJ(wIndex)       (((wIndex)<CN_NUM_ANA)?g_tagAna.tAnaVectFst[(wIndex)].dwAmJ:0);
#define CN_Get_Ana_FAng(wIndex)       (((wIndex)<CN_NUM_ANA)?g_tagAna.tAnaVectFst[(wIndex)].dwAngle:0);
// ģ��������--г��
#define CN_Get_Ana_HAm(wNum,wIndex)   (((wIndex)<CN_NUM_ANA)?g_tagAna.tAnaVectHum[(wIndex)][(wNum)].dwAm:0);
#define CN_Get_Ana_HAmJ(wNum,wIndex)  (((wIndex)<CN_NUM_ANA)?g_tagAna.tAnaVectHum[(wIndex)][(wNum)].dwAmJ:0);
#define CN_Get_Ana_HAng(wNum,wIndex)  (((wIndex)<CN_NUM_ANA)?g_tagAna.tAnaVectHum[(wIndex)][(wNum)].dwAngle:0);
// ģ��������--Ƶ��
#define CN_Get_Cal_F(wIndex)          (((wIndex)<CN_NUM_CAL)?g_tagAna.dwFrCal[(wIndex)]:0);
// IO����
#define G_Get_DI(wIndex)            (((wIndex)<CN_NUM_DI)?g_tagIO.bDIHldIn[(wIndex)]:0)
#define G_Get_DI_Q(wIndex)          (((wIndex)<CN_NUM_DI)?g_tagIO.dwDIQ[(wIndex)]:0)
#define G_Get_DI_UTC(wIndex)        (((wIndex)<CN_NUM_DI)?g_tagIO.tDIHldUTC[(wIndex)]:g_tagPub.tSysTimeUTC)
#define G_Get_DPI(wIndex)           (((wIndex)<CN_NUM_DPI)?g_tagIO.byDpiIn[(wIndex)]:0)
#define G_Get_GOIN(wIndex)          (((wIndex)<CN_NUM_GOIN)?g_tagIO.bGoInValid[(wIndex)]:0)
// ֱ������
#define G_Get_DC_I(wIndex)           (((wIndex)<CN_NUM_DC)?g_tagDC.iDCOut[(wIndex)]:0)
#define G_Get_DC_F(wIndex)           (((wIndex)<CN_NUM_DC)?g_tagDC.fDCOut[(wIndex)]:0)
// ��������
#define G_Get_PARA_I(wIndex)         (((wIndex)<CN_NUM_PARA)?g_tagPara.dwPara[(wIndex)]:0)
#define G_Get_PARA_F(wIndex)         (((wIndex)<CN_NUM_PARA)?g_tagPara.fPara[(wIndex)]:0)
#define G_Get_PARA_COE(wIndex)       (((wIndex)<CN_NUM_PARA)?g_tagPara.dwCoe[(wIndex)]:0)
// ��������
#define G_Get_Const_Chk(wIndex)        (g_tagPub.bConstChk[(wIndex)])
#define G_Set_Const_Chk(wIndex,wState) (((wIndex)<CN_NUM_PUB)?(g_tagPub.bConstChk[(wIndex)]=(wState)):0)
// ȫ�ֱ�־
#define G_Get_Flag(wIndex)          (((wIndex)<CN_NUM_FLAG)?g_bFlag[(wIndex)]:0)
#define G_Set_Flag(wIndex,wState)   (((wIndex)<CN_NUM_FLAG)?g_bFlag[(wIndex)]=(wState):0)
// ȫ�ֱ�־(�ڲ�ʹ��)
#define G_Get_Inter(wIndex)          (((wIndex)<CN_NUM_INTER)?g_iInter[(wIndex)]:0)
#define G_Set_Inter(wIndex,iState)   (((wIndex)<CN_NUM_INTER)?g_iInter[(wIndex)]=(iState):0)
// ��������
#define G_Set_ActIn(wIndex,wState)  (((wIndex)<CN_NUM_ACT)?g_tActState.bActIn[(wIndex)]=(wState):0)
#define G_Set_AlmIn(wIndex,wState)  (((wIndex)<CN_NUM_ALM)?g_tAlmState.bAlmIn[(wIndex)]=(wState):0)
// GOOSE��������״̬���
#define G_Get_ActOut(wIndex)        (((wIndex)<CN_NUM_ACT)?g_tActState.bActOut[(wIndex)]:0)
// �澯����״̬���
#define G_Get_AlmOut(wIndex)        (((wIndex)<CN_NUM_ALM)?g_tAlmState.bAlmOut[(wIndex)]:0)
// �Լ�����״̬���
#define G_Get_ChkIn(wIndex)         (((wIndex)<CN_NUM_CHK)?g_tChkState.bChkIn[(wIndex)]:0)
#define G_Get_ChkOut(wIndex)        (((wIndex)<CN_NUM_CHK)?g_tChkState.bChkOut[(wIndex)]:0)
// ����������ӿ�
#define G_Set_AlmIn_All(wIndex,wState,iValue1,iValue2,iValue3)    \
	if((wIndex)<CN_NUM_ALM)                                       \
	{                                                             \
		g_tAlmState.bAlmIn[(wIndex)]=(wState);                    \
		g_tAlmState.tRecValue[(wIndex)].iMeaValue[0]=(iValue1);   \
		g_tAlmState.tRecValue[(wIndex)].iMeaValue[1]=(iValue2);   \
		g_tAlmState.tRecValue[(wIndex)].iMeaValue[2]=(iValue3);   \
	}
// �Լ������������λ
#define G_Set_ChkIn_All(wIndex,iValue1,iValue2,iValue3)           \
	if((wIndex)<CN_NUM_CHK)                                       \
	{                                                             \
		g_tChkState.tRecValue[(wIndex)].iMeaValue[0]=(iValue1);   \
		g_tChkState.tRecValue[(wIndex)].iMeaValue[1]=(iValue2);   \
		g_tChkState.tRecValue[(wIndex)].iMeaValue[2]=(iValue3);   \
		g_tChkState.dwChkActCnt[(wIndex)]++;                      \
		g_tChkState.dwChkRetCnt[(wIndex)]=0;                      \
		g_tChkState.bChkIn[(wIndex)]=TRUE;                        \
	}
// �Լ������޲�����λ
#define G_Set_ChkIn(wIndex)                                       \
	if((wIndex)<CN_NUM_CHK)                                       \
	{                                                             \
		g_tChkState.dwChkActCnt[(wIndex)]++;                      \
		g_tChkState.dwChkRetCnt[(wIndex)]=0;                      \
		g_tChkState.bChkIn[(wIndex)]=TRUE;                        \
	}
// �Լ������޲�����λ
#define G_Clr_ChkIn(wIndex)                                      \
	if((wIndex)<CN_NUM_CHK)                                      \
	{                                                            \
		g_tChkState.dwChkActCnt[(wIndex)]=0;                     \
		g_tChkState.dwChkRetCnt[(wIndex)]++;                     \
		g_tChkState.bChkIn[(wIndex)]=FALSE;                      \
	}
		
// 0.5ms��ʱ���ú궨��
#define G_Sys_Div2_1   (!(g_tagPub.dwSysCnt&DB0))
#define G_Sys_Div2_2   (g_tagPub.dwSysCnt&DB0)
// 1ms��ʱ���ú궨��
#define G_Sys_Div4_1   ((g_tagPub.dwSysCnt&0x3)==0x0)
#define G_Sys_Div4_2   ((g_tagPub.dwSysCnt&0x3)==0x1)
#define G_Sys_Div4_3   ((g_tagPub.dwSysCnt&0x3)==0x2)
#define G_Sys_Div4_4   ((g_tagPub.dwSysCnt&0x3)==0x3)
// 2ms��ʱ���ú궨��
#define G_Sys_Div8_1   ((g_tagPub.dwSysCnt&0x7)==0x0)
#define G_Sys_Div8_2   ((g_tagPub.dwSysCnt&0x7)==0x1)
#define G_Sys_Div8_3   ((g_tagPub.dwSysCnt&0x7)==0x2)
#define G_Sys_Div8_4   ((g_tagPub.dwSysCnt&0x7)==0x3)
#define G_Sys_Div8_5   ((g_tagPub.dwSysCnt&0x7)==0x4)
#define G_Sys_Div8_6   ((g_tagPub.dwSysCnt&0x7)==0x5)
#define G_Sys_Div8_7   ((g_tagPub.dwSysCnt&0x7)==0x6)
#define G_Sys_Div8_8   ((g_tagPub.dwSysCnt&0x7)==0x7)
// 1024��ʱ���ú궨��
#define G_Sys_Div1024_000   ((g_tagPub.dwSysCnt&0x3ff)==0x1)
#define G_Sys_Div1024_256   ((g_tagPub.dwSysCnt&0x3ff)==0x101)
#define G_Sys_Div1024_512   ((g_tagPub.dwSysCnt&0x3ff)==0x201)
#define G_Sys_Div1024_768   ((g_tagPub.dwSysCnt&0x3ff)==0x301)
// 2048��ʱ���ú궨��
#define G_Sys_Div2048_000   ((g_tagPub.dwSysCnt&0x7ff)==0x2)
#define G_Sys_Div2048_256   ((g_tagPub.dwSysCnt&0x7ff)==0x102)
#define G_Sys_Div2048_512   ((g_tagPub.dwSysCnt&0x7ff)==0x202)
#define G_Sys_Div2048_768   ((g_tagPub.dwSysCnt&0x7ff)==0x302)
#define G_Sys_Div2048_1024  ((g_tagPub.dwSysCnt&0x7ff)==0x402)
// 4096��ʱ���ú궨��
#define G_Sys_Div4096_000    ((g_tagPub.dwSysCnt&0xfff)==0x3)
#define G_Sys_Div4096_256    ((g_tagPub.dwSysCnt&0xfff)==0x103)
#define G_Sys_Div4096_512    ((g_tagPub.dwSysCnt&0xfff)==0x203)
#define G_Sys_Div4096_768    ((g_tagPub.dwSysCnt&0xfff)==0x303)
#define G_Sys_Div4096_1024   ((g_tagPub.dwSysCnt&0xfff)==0x403)
// 8192��ʱ���ú궨��
#define G_Sys_Div8192_000    ((g_tagPub.dwSysCnt&0x1fff)==0x3)
#define G_Sys_Div8192_256    ((g_tagPub.dwSysCnt&0x1fff)==0x103)
#define G_Sys_Div8192_512    ((g_tagPub.dwSysCnt&0x1fff)==0x203)
#define G_Sys_Div8192_768    ((g_tagPub.dwSysCnt&0x1fff)==0x303)
#define G_Sys_Div8192_1024   ((g_tagPub.dwSysCnt&0x1fff)==0x403)
// 0x4000��ʱ���ú궨��
#define G_Sys_Div16284_000   ((g_tagPub.dwSysCnt&0x3fff)==0x3)
#define G_Sys_Div16284_256   ((g_tagPub.dwSysCnt&0x3fff)==0x103)
#define G_Sys_Div16284_512   ((g_tagPub.dwSysCnt&0x3fff)==0x203)
#define G_Sys_Div16284_768   ((g_tagPub.dwSysCnt&0x3fff)==0x303)
// �Զ����ʱ����(������2��n�η�)
#define G_Sys_Div(DivCnt,DivNum)          ((g_tagPub.dwSysCnt%(DivCnt))==(DivNum))

#endif /* _IES_IMSRC_H_ */
