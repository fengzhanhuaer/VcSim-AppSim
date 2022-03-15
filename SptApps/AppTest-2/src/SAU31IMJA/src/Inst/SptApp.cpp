#include "InstResource.h"
// 上电闭锁时间
void AppPowCCDInit()
{
	// 配置信息获取
	SptCcdFile::OutStatus& tCcdFlag = SptCcdFile::Instance().CcdParseStatus();
	// CRC更新
	g_tDevInfor.dwCrc = tCcdFlag.fileCrc;
	g_tagDC.iDCIn[CN_DC_INDEX_CRC] = (INT32)g_tDevInfor.dwCrc;
	if (tCcdFlag.fileNoExist) { G_Set_ChkIn(EN_CHK_CCD_NO); }
	if (tCcdFlag.parseErr) { G_Set_ChkIn(EN_CHK_CCD_ERR); }
	if (tCcdFlag.attLost) { G_Set_ChkIn(EN_CHK_CCD_PARALOSE); }
	if (tCcdFlag.attErr) { G_Set_ChkIn(EN_CHK_CCD_PARAERR); }
	if (tCcdFlag.crcErr) { G_Set_ChkIn(EN_CHK_CCD_CRC); }
	if (tCcdFlag.frameLenOverFlow) { G_Set_ChkIn(EN_CHK_CCD_FRAME); }
	// CCD控制块短地址自检
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
	// CCD控制块个数越限
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
	// CCD控制块参数错误
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
		// CCD控制块配置自检
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
	// SV订阅配置总异常
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
	// SV发布配置告警
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
	// GOOSE订阅配置告警
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
	// GOOSE发布配置告警
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
	// 获取本地时间
	SalDateStamp tSysDate;
	tSysDate.Now();
	g_tagPub.tSysTimeUTC.dwUSecond_L = tSysDate.usL;
	g_tagPub.tSysTimeUTC.dwUSecond_H = tSysDate.usH;
	g_tagPub.tSysTimeUTC.dwLeapSecFlg = tSysDate.q.q;
}
// 上电闭锁时间
void AppPowBlock()
{
	// 中断自由计数器
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

//初始化参数配置，此时参数还未加载，参数不可用
void AppPowerUpStep0()
{
	IES_IM_Init();
	AppInterFaceChk();
	AppParaPowerUpIni();
	AppCmmPowerUpIni();
}
//初始化一般性IO配置，此时参数已经加载完成，可以根据参数个性化的初始化IO（此时平台功能还未加载，不可进行依赖于平台运行的行为）
//所有的依赖于平台的资源均应在此Step0与Step1中进行
//Step0与Step1的区别是Step0中，所有的参数还未初始化完成，因此参数是不可用的。Step1中参数已经初始化并加载完成，Step1中可以使用参数、定值等信息

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
	// 此处解析放置T860PowerUpIni()函数后
	AppAngInCfgRef();
	AppAngOutCfgRef();
	AppStateInCfgRef();
	AppStateOutCfgRef();
	IES_IM_Cfg_Init();
	AppPowCCDInit();
}
//此时平台已经完成初始化，但是采样中断还未开启，此时可以进行一些采样值，应用层IO初始化、重启事项生成等工作
//61850已经初始化完毕，可以读取一些配置信息
//此函数中不能进行需要进行资源分配的活动，所有对平台依赖资源的配置均应在Setp0与Step1中完成
void AppPowerUpStep2()
{
	ApiFlagsInit();
	UINT8 byPowDo = TRUE;
	// 初始化信息
	AppEventRunRef(EN_RUN_POW_ON);
	SptSetHwVal(E_HPT_RelayPower, &byPowDo, 1);
	SptSetHwVal(E_HPT_RelayPower30V, &byPowDo, 1);
#ifdef WIN32_SIM

#elif defined(SYLIX_GZK)
	//检查操作系统校验标志
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
//逐点中断
void App1SampPointInt()
{
	// 上电闭锁时间
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
	// 禁止中断
	sampAppArr[0].Enable(0);
	LogApp.Stamp() << "Program run into app main.\n";
	// 版本信息
	ApiVersionInfo::Instance().AppVersion().FillInfo(CN_CPU_SOFT_VER_P, CN_CPU_SOFT_VER_A, CN_CPU_SOFT_VER_M, "JCDZ", __DATE__, __TIME__);
	//向平台配置应用信息，平台解析启动参数，如果是FactoryMode启动的，平台会解析FactoryMode.cfg并执行相应的操作
	SptMain::Instance().SetAppCfg(&AppRunTimeCfg, argc, argv);
	//初始化参试配置
	AppPowerUpStep0();
	//初始化IO信息
	AppPowerUpStep1();
	//平台功能初始化、启动平台内自有的任务等
	SptMain::Instance().PowerUpIni(0);
	// 此处之后设置电源投退功能
	//初始化应用层IO信息，产生重启事项等
	AppPowerUpStep2();
	//所有初始化已经完成，使能中断
	sampAppArr[0].Enable(1);
	//所有初始化已经完成，进入平台运行循环，此函数不返回
	SptMain::Instance().Run();
	return  (0);
}
