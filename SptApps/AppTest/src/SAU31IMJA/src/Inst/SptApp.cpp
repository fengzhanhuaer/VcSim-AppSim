#include "InstResource.h"
// �ϵ����ʱ��
void AppPowCCDInit()
{
	// ������Ϣ��ȡ
	SptCcdFile::OutStatus& tCcdFlag = SptCcdFile::Instance().CcdParseStatus();
	// CRC����
	g_tDevInfor.dwCrc = tCcdFlag.fileCrc;
	g_tagDC.iDCIn[CN_DC_INDEX_CRC] = (INT32)g_tDevInfor.dwCrc;
	if (tCcdFlag.fileNoExist) { G_Set_ChkIn(EN_CHK_CCD_NO); }
	if (tCcdFlag.parseErr) { G_Set_ChkIn(EN_CHK_CCD_ERR); }
	if (tCcdFlag.attLost) { G_Set_ChkIn(EN_CHK_CCD_PARALOSE); }
	if (tCcdFlag.attErr) { G_Set_ChkIn(EN_CHK_CCD_PARAERR); }
	if (tCcdFlag.crcErr) { G_Set_ChkIn(EN_CHK_CCD_CRC); }
	if (tCcdFlag.frameLenOverFlow) { G_Set_ChkIn(EN_CHK_CCD_FRAME); }
	// CCD���ƿ�̵�ַ�Լ�
	if (G_Get_Inter(EN_INTER_SVPUB_ADRERR)
		|| G_Get_Inter(EN_INTER_GOSUB_ADRERR)
		|| G_Get_Inter(EN_INTER_GOPUB_ADRERR)
#if(CN_DEV_CPU1)
		|| G_Get_Inter(EN_INTER_SVSUB_ADRERR)
#endif
		)
	{
		G_Set_ChkIn(EN_CHK_CCD_ADDRERR);
	}
	// CCD���ƿ����Խ��
	if (G_Get_Inter(EN_INTER_SVPUB_NUMERR)
		|| G_Get_Inter(EN_INTER_GOSUB_NUMERR)
		|| G_Get_Inter(EN_INTER_GOPUB_NUMERR)
#if(CN_DEV_CPU1)
		|| G_Get_Inter(EN_INTER_SVSUB_NUMERR)
#endif
		)
	{
		G_Set_ChkIn(EN_CHK_CCD_NUMERR);
	}
	// CCD���ƿ��������
	//	if(G_Get_Inter(EN_INTER_SVPUB_PARAERR)
	//	||G_Get_Inter(EN_INTER_GOSUB_PARAERR)
	//	||G_Get_Inter(EN_INTER_GOPUB_PARAERR)
	//#if(CN_DEV_CPU1)
	//	||G_Get_Inter(EN_INTER_SVSUB_PARAERR)
	//#endif
	//	)
	//	{
	//		G_Set_ChkIn(EN_CHK_CCD_PARAERR);
	//	}
		// CCD���ƿ������Լ�
	if (G_Get_Inter(EN_INTER_SVPUB_CFGERR)
		|| G_Get_Inter(EN_INTER_GOSUB_CFGERR)
		|| G_Get_Inter(EN_INTER_GOPUB_CFGERR)
#if(CN_DEV_CPU1)
		|| G_Get_Inter(EN_INTER_SVSUB_CFGERR)
#endif
		)
	{
		G_Set_ChkIn(EN_CHK_CCD_CFGERR);
	}
#if(CN_DEV_CPU1)
	// SV�����������쳣
	if (G_Get_Inter(EN_INTER_SVSUB_A_CHK)
		|| G_Get_Inter(EN_INTER_SVSUB_B_CHK)
		|| G_Get_Inter(EN_INTER_SVSUB_PORT)
		|| G_Get_Inter(EN_INTER_SVSUB_NUMERR)
		|| G_Get_Inter(EN_INTER_SVSUB_PARAERR)
		|| G_Get_Inter(EN_INTER_SVSUB_CFGERR)
		|| G_Get_Inter(EN_INTER_SVSUB_ADRERR)
		)
	{
		G_Set_Inter(EN_INTER_SVSUB_CFG, TRUE);
		G_Set_AlmIn(EN_ALM_CCD_SVSUB, TRUE);
	}
#endif
	// SV�������ø澯
	if (G_Get_Inter(EN_INTER_SVPUB_PORT)
		|| G_Get_Inter(EN_INTER_SVPUB_NUMERR)
		|| G_Get_Inter(EN_INTER_SVPUB_PARAERR)
		|| G_Get_Inter(EN_INTER_SVPUB_CFGERR)
		|| G_Get_Inter(EN_INTER_SVPUB_ADRERR)
		|| G_Get_Inter(EN_INTER_SVPUB_CHN_NUM)
		|| G_Get_Inter(EN_INTER_SVPUB_CHN_NO)
		|| G_Get_Inter(EN_INTER_SVPUB_DLY)
		)
	{
		G_Set_Inter(EN_INTER_SVPUB_CFG, TRUE);
		G_Set_AlmIn(EN_ALM_CCD_SVPUB, TRUE);
	}
	// GOOSE�������ø澯
	if (G_Get_Inter(EN_INTER_GOSUB_PORT)
		|| G_Get_Inter(EN_INTER_GOSUB_NUMERR)
		|| G_Get_Inter(EN_INTER_GOSUB_PARAERR)
		|| G_Get_Inter(EN_INTER_GOSUB_CFGERR)
		|| G_Get_Inter(EN_INTER_GOSUB_ADRERR)
		|| G_Get_Inter(EN_INTER_GOSUB_Dif)
		|| G_Get_Inter(EN_INTER_GOSUB_GOCB))
	{
		G_Set_Inter(EN_INTER_GOSUB_CFG, TRUE);
		G_Set_AlmIn(EN_ALM_CCD_GOSUB, TRUE);
	}
	// GOOSE�������ø澯
	if (G_Get_Inter(EN_INTER_GOPUB_PORT)
		|| G_Get_Inter(EN_INTER_GOPUB_NUMERR)
		|| G_Get_Inter(EN_INTER_GOPUB_PARAERR)
		|| G_Get_Inter(EN_INTER_GOPUB_CFGERR)
		|| G_Get_Inter(EN_INTER_GOPUB_ADRERR)
		|| G_Get_Inter(EN_INTER_GOPUB_DI_Dif)
		|| G_Get_Inter(EN_INTER_GOPUB_DPI_Dif)
		|| G_Get_Inter(EN_INTER_GOPUB_DC_Dif)
		|| G_Get_Inter(EN_INTER_GOPUB_OUT_Dif)
		)
	{
		G_Set_Inter(EN_INTER_GOPUB_CFG, TRUE);
		G_Set_AlmIn(EN_ALM_CCD_GOPUB, TRUE);
	}
}
void AppTimeInRef()
{
	// ��ȡ����ʱ��
	SalDateStamp tSysDate;
	tSysDate.Now();
	g_tagPub.tSysTimeUTC.dwUSecond_L = tSysDate.usL;
	g_tagPub.tSysTimeUTC.dwUSecond_H = tSysDate.usH;
	g_tagPub.tSysTimeUTC.dwLeapSecFlg = tSysDate.q.q;
}
// �ϵ����ʱ��
void AppPowBlock()
{
	// �ж����ɼ�����
	g_tagPub.dwSysCnt++;

	if (g_tagPub.dwSysPowCnt < 0x7fffffff)
	{
		g_tagPub.dwSysPowCnt++;

		if (!g_tagPub.bSysPower)
		{
			if (g_tagPub.dwSysPowCnt > CN_T30S)
			{
				g_tagPub.bSysPower = TRUE;
				g_bFlag[EN_FLAG_INIT] = FALSE;
			}
			else
			{
				g_bFlag[EN_FLAG_INIT] = TRUE;
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
//��ʱƽ̨�Ѿ���ɳ�ʼ�������ǲ����жϻ�δ��������ʱ���Խ���һЩ����ֵ��Ӧ�ò�IO��ʼ���������������ɵȹ���
//61850�Ѿ���ʼ����ϣ����Զ�ȡһЩ������Ϣ
//�˺����в��ܽ�����Ҫ������Դ����Ļ�����ж�ƽ̨������Դ�����þ�Ӧ��Setp0��Step1�����
void AppPowerUpStep2()
{
	ApiFlagsInit();
	UINT8 byPowDo = TRUE;
	// ��ʼ����Ϣ
	AppEventRunRef(EN_RUN_POW_ON);
	SptSetHwVal(E_HPT_RelayPower, &byPowDo, 1);
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
	AppEventOutRef();
	AppHmiLedOutRef();
	AppStateOutRef();
	ApiFlagsOut();
	if (G_Sys_Div4_2)
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
