#include "InstResource.h"
// �ϵ����ʱ��
void AppPowCCDInit()
{
	// ������Ϣ��ȡ
	SptCcdFile::OutStatus& tCcdFlag = SptCcdFile::Instance().CcdParseStatus();
	// CPU�汾��Ϣ����
	//g_tDevInfor.byVerName=CN_CPU_PUBLIC_SOFT;
	IES_memcpy(g_tDevInfor.byVerName, sizeof(g_tDevInfor.byVerName), (char*)(CN_CPU_PUBLIC_SOFT), sizeof(CN_CPU_PUBLIC_SOFT));
	// CRC����
	g_tDevInfor.dwCrc=tCcdFlag.fileCrc;
	g_tagDC.iDCIn[CN_DC_INDEX_CRC] =(INT32)g_tDevInfor.dwCrc;
	if(tCcdFlag.fileNoExist)      {G_Set_ChkIn(EN_CHK_CCD_NO);}
	if(tCcdFlag.parseErr)         {G_Set_ChkIn(EN_CHK_CCD_ERR);}
	if(tCcdFlag.attLost)          {G_Set_ChkIn(EN_CHK_CCD_PARALOSE);}
	if(tCcdFlag.attErr)           {G_Set_ChkIn(EN_CHK_CCD_PARAERR);}
	if(tCcdFlag.crcErr)           {G_Set_ChkIn(EN_CHK_CCD_CRC);}
	if(tCcdFlag.frameLenOverFlow) {G_Set_ChkIn(EN_CHK_CCD_FRAME);}
	// CCD���ƿ�̵�ַ�Լ�
	if(g_iInter[EN_INTER_SVPUB_ADRERR]
	||g_iInter[EN_INTER_GOSUB_ADRERR]
	||g_iInter[EN_INTER_GOPUB_ADRERR]
#if(CN_DEV_CPU1)
	||g_iInter[EN_INTER_SVSUB_ADRERR]
#endif
	)
	{
		G_Set_ChkIn(EN_CHK_CCD_ADDRERR);
	}
	// CCD���ƿ����Խ��
	if(g_iInter[EN_INTER_SVPUB_NUMERR]
	||g_iInter[EN_INTER_GOSUB_NUMERR]
	||g_iInter[EN_INTER_GOPUB_NUMERR]
#if(CN_DEV_CPU1)
	||g_iInter[EN_INTER_SVSUB_NUMERR]
#endif
	)
	{
		G_Set_ChkIn(EN_CHK_CCD_NUMERR);
	}
// CCD���ƿ��������
//	if(g_iInter[EN_INTER_SVPUB_PARAERR]
//	||g_iInter[EN_INTER_GOSUB_PARAERR]
//	||g_iInter[EN_INTER_GOPUB_PARAERR]
//#if(CN_DEV_CPU1)
//	||g_iInter[EN_INTER_SVSUB_PARAERR]
//#endif
//	)
//	{
//		G_Set_ChkIn(EN_CHK_CCD_PARAERR);
//	}
	// CCD���ƿ������Լ�
	if(g_iInter[EN_INTER_SVPUB_CFGERR]
	||g_iInter[EN_INTER_GOSUB_CFGERR]
	||g_iInter[EN_INTER_GOPUB_CFGERR]
#if(CN_DEV_CPU1)
	||g_iInter[EN_INTER_SVSUB_CFGERR]
#endif
	)
	{
		G_Set_ChkIn(EN_CHK_CCD_CFGERR);
	}
#if(CN_DEV_CPU1)
	// SV�����������쳣
	if(g_iInter[EN_INTER_SVSUB_A_CHK]
	||g_iInter[EN_INTER_SVSUB_B_CHK]
	||g_iInter[EN_INTER_SVSUB_PORT]
	||g_iInter[EN_INTER_SVSUB_NUMERR]
	||g_iInter[EN_INTER_SVSUB_PARAERR]
	||g_iInter[EN_INTER_SVSUB_CFGERR]
	||g_iInter[EN_INTER_SVSUB_ADRERR]
	)
	{
		g_iInter[EN_INTER_SVSUB_CFG]=TRUE;
		g_tAlmState.bAlmIn[EN_ALM_CCD_SVSUB]=TRUE;
	}
#endif
	// SV�������ø澯
	if(g_iInter[EN_INTER_SVPUB_PORT]
	||g_iInter[EN_INTER_SVPUB_NUMERR]
	||g_iInter[EN_INTER_SVPUB_PARAERR]
	||g_iInter[EN_INTER_SVPUB_CFGERR]
	||g_iInter[EN_INTER_SVPUB_ADRERR]
	||g_iInter[EN_INTER_SVPUB_CHN_NUM]
	||g_iInter[EN_INTER_SVPUB_CHN_NO]
	||g_iInter[EN_INTER_SVPUB_DLY]
	)
	{
		g_iInter[EN_INTER_SVPUB_CFG]=TRUE;
		g_tAlmState.bAlmIn[EN_ALM_CCD_SVPUB]=TRUE;
	}
	// GOOSE�������ø澯
	if(g_iInter[EN_INTER_GOSUB_PORT]
	||g_iInter[EN_INTER_GOSUB_NUMERR]
	||g_iInter[EN_INTER_GOSUB_PARAERR]
	||g_iInter[EN_INTER_GOSUB_CFGERR]
	||g_iInter[EN_INTER_GOSUB_ADRERR]
	||g_iInter[EN_INTER_GOSUB_Dif]
	||g_iInter[EN_INTER_GOSUB_GOCB])
	{
		g_iInter[EN_INTER_GOSUB_CFG]=TRUE;
		g_tAlmState.bAlmIn[EN_ALM_CCD_GOSUB]=TRUE;
	}
	// GOOSE�������ø澯
	if(g_iInter[EN_INTER_GOPUB_PORT]
	||g_iInter[EN_INTER_GOPUB_NUMERR]
	||g_iInter[EN_INTER_GOPUB_PARAERR]
	||g_iInter[EN_INTER_GOPUB_CFGERR]
	||g_iInter[EN_INTER_GOPUB_ADRERR]
	||g_iInter[EN_INTER_GOPUB_DI_Dif]
	||g_iInter[EN_INTER_GOPUB_DPI_Dif]
	||g_iInter[EN_INTER_GOPUB_DC_Dif]
	||g_iInter[EN_INTER_GOPUB_OUT_Dif]
	)
	{
		g_iInter[EN_INTER_GOPUB_CFG]=TRUE;
		g_tAlmState.bAlmIn[EN_ALM_CCD_GOPUB]=TRUE;
	}
}
void AppTimeInRef()
{
	// ��ȡ����ʱ��
	SalDateStamp tSysDate;
	tSysDate.Now();
	g_tagPub.tSysTimeUTC.dwUSecond_L  =tSysDate.usL;
	g_tagPub.tSysTimeUTC.dwUSecond_H  =tSysDate.usH;
	g_tagPub.tSysTimeUTC.dwLeapSecFlg =tSysDate.q.q;
}
// �ϵ����ʱ��
void AppPowBlock()
{
	// �ж����ɼ�����
	g_tagPub.dwSysCnt++;

	if(g_tagPub.dwSysPowCnt<0x7fffffff)
	{
		g_tagPub.dwSysPowCnt++;
		
		if(!g_tagPub.bSysPower)
		{
			if(g_tagPub.dwSysPowCnt>CN_T30S)
			{
				g_tagPub.bSysPower=TRUE;
				g_bFlag[EN_FLAG_INIT]=FALSE;
			}
			else
			{
				g_bFlag[EN_FLAG_INIT]=TRUE;
			}
		}
	}
}

//��ʼ���������ã���ʱ������δ���أ�����������
void AppPowerUpStep0()
{
	IES_IM_Init();
	AppInterFaceChk();
	AppParaPowerUpIni();
	AppCmmPowerUpIni();
}
//��ʼ��һ����IO���ã���ʱ�����Ѿ�������ɣ����Ը��ݲ������Ի��ĳ�ʼ��IO����ʱƽ̨���ܻ�δ���أ����ɽ���������ƽ̨���е���Ϊ��
//���е�������ƽ̨����Դ��Ӧ�ڴ�Step0��Step1�н���
//Step0��Step1��������Step0�У����еĲ�����δ��ʼ����ɣ���˲����ǲ����õġ�Step1�в����Ѿ���ʼ����������ɣ�Step1�п���ʹ�ò�������ֵ����Ϣ

void AppPowerUpStep1()
{
	AppEventPowerUpIni();
	AppAngInPowerUpIni();
	AppAngOutPowerUpIni();
	AppDispPowerUpIni();
	AppHmiLedPowerUpIni();
	// ������ʱ�ȴ�IO���DC��ȷ�ϵ�ַ
	MsSleep(CN_IO_ADDR_DLY);
	
	AppStateInPowerUpIni();
	AppStateOutPowerUpIni();
	AppSjRecordPowerUpIni();
	T860PowerUpIni();
	AppCheckPowerUpIni();
	// �˴���������T860PowerUpIni()������
	AppAngInCfgRef();
	AppAngOutCfgRef();
	AppStateInCfgRef();
	AppStateOutCfgRef();
	IES_IM_Cfg_Init();
	AppPowCCDInit();
}
#if(CN_SOFT_CPU_TEST_GET(CN_TEST_TIME))
#define  CN_APP_DLY    (32)
struct TaskRunInfo sampLoadnfo[CN_APP_DLY];//���ؼ���
char    g_cSampDly[10];
#endif
//��ʱƽ̨�Ѿ���ɳ�ʼ�������ǲ����жϻ�δ��������ʱ���Խ���һЩ����ֵ��Ӧ�ò�IO��ʼ���������������ɵȹ���
//61850�Ѿ���ʼ����ϣ����Զ�ȡһЩ������Ϣ
//�˺����в��ܽ�����Ҫ������Դ����Ļ�����ж�ƽ̨������Դ�����þ�Ӧ��Setp0��Step1�����
void AppPowerUpStep2()
{
    ApiFlagsInit();
	UINT8 byPowDo=TRUE;
	// ��ʼ����Ϣ
	AppEventRunRef(EN_RUN_POW_ON);
	SptSetHwVal(E_HPT_RelayPower   , &byPowDo, 1);
	SptSetHwVal(E_HPT_RelayPower30V, &byPowDo, 1);
#ifdef WIN32_SIM

#elif defined(SYLIX_GZK)
	//������ϵͳУ���־
	if (!ApiVersionInfo::Instance().MainSysVersion().IsProgOk())
	{
		LogErr.Stamp() << "MainSysVersion PowerUp Check err.\n";
	}
	if (!ApiVersionInfo::Instance().BakSysVersion().IsProgOk())
	{
		LogErr.Stamp() << "BakSysVersion PowerUp Check err.\n";
	}
#endif // WIN32_SIM
#if(CN_SOFT_CPU_TEST_GET(CN_TEST_TIME))
	UINT32 i;
	for(i=0;i<CN_APP_DLY;i++)
	{
		sprintf(g_cSampDly,"AppSamp%d",i);
		
		sampLoadnfo[i].SetName(g_cSampDly);
		sampLoadnfo[i].ClearLoadInfo();
		sampLoadnfo[i].Rgs2TaskMonitorRunInfo();
	}
#endif
}
void AppInterFaceIn()
{
	AppTimeInRef();
	AppAngInRef();
	AppStateInRef();
	AppStateOutRtnRef();
	AppParaInRef();
	ApiFlagsIn();
}
void AppInterFaceOut()
{
	AppAngQRef();
	AppAngParaRef();
	AppAngListRef();
	AppEventOutRef_S();
	AppHmiLedOutRef();
	AppStateOutRef();
	ApiFlagsOut();
	if(G_Sys_Div4_2)
	AppCmmSend();
}
//����ж�
void App1SampPointInt()
{
	// �ϵ����ʱ��
	AppPowBlock();
	AppInterFaceIn();
	IES_IM_Interrupt();
	AppInterFaceOut();
}
void App2SampPointInt()
{


}
void App3SampPointInt()
{


}
extern "C" int main(int argc, char** argv)
{

#if(CN_SOFT_VER_CPU!=CN_SOFT_CPU_NANJING)
	// CPU1ʹ��Һ��
	#if(CN_DEV_CPU1)
	SptSetSerialPara(E_HSPN_LCD_CMM,E_HSPT_EnableTxRx,1);
	// CPU2��ֹҺ��
	#elif(CN_DEV_CPU2)
	SptSetSerialPara(E_HSPN_LCD_CMM,E_HSPT_EnableTxRx,0);
	#endif
#endif
	// ��ֹ�ж�
	sampAppArr[0].Enable(0);
	LogApp.Stamp() << "Program run into app main.\n";
	// �汾��Ϣ
	ApiVersionInfo::Instance().AppVersion().FillInfo(CN_CPU_SOFT_VER_P, CN_CPU_SOFT_VER_A, CN_CPU_SOFT_VER_M, "JCDZ", __DATE__, __TIME__);
	//��ƽ̨����Ӧ����Ϣ��ƽ̨�������������������FactoryMode�����ģ�ƽ̨�����FactoryMode.cfg��ִ����Ӧ�Ĳ���
	SptMain::Instance().SetAppCfg(&AppRunTimeCfg, argc, argv);
	//��ʼ����������
	AppPowerUpStep0();
	//��ʼ��IO��Ϣ
	AppPowerUpStep1();
	//ƽ̨���ܳ�ʼ��������ƽ̨�����е������
	SptMain::Instance().PowerUpIni(0);
	// �˴�֮�����õ�ԴͶ�˹���
	//��ʼ��Ӧ�ò�IO��Ϣ���������������
	AppPowerUpStep2();
	//���г�ʼ���Ѿ���ɣ�ʹ���ж�
	sampAppArr[0].Enable(1);
	//���г�ʼ���Ѿ���ɣ�����ƽ̨����ѭ�����˺���������
	SptMain::Instance().Run();
	return  (0);
}
