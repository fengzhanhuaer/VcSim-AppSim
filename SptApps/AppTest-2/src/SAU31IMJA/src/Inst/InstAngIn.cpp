#include "InstResource.h"
using namespace spt;
// 帧配置
ApiBoardAngFrameIn  AngFrameIn[1];
// 常规模拟量配置
ApiBoardNormalAngIn AngNorAngIn[CN_NUM_BOARD_SAM];
ApiNormalAngIn      AngNorAngSampIn[CN_NUM_AD];
#if(CN_DEV_CPU1)
ApiSvInVirBoard     VirSvBoard[CN_NUM_BOARD_SV];
ApiSvIn             SvAngInDelayA;// A套SV额定延时
ApiSvIn             SvAngInDelayB;// B套SV额定延时
ApiSvIn             SvAngIn[CN_NUM_SV];
#elif(CN_DEV_CPU2)
ApiBoardCmmSvIn     CmmSvIn[CN_NUM_SV];
#endif
// 模拟量帧初始化
void AppAngInPowerUpIni()
{
	WORD i,j;
	const VarUnits  *pUnitTem;
	const tagAnaTab *ptAnaTab;
	#if(CN_FUN_DBUG1)
	const tagAnaTab *ptAnaTabBak;
	#endif
	const tagBoardAnaTab *ptBoardTab;
	const tagCTypeTab  *ptCTypeTab;
	
	ptCTypeTab =&g_tCTypeTab[0];
	ptBoardTab =&g_tBoardSamTab[0];
	// 注：涉及模拟量采样,模拟量部分通道个数设置为AD总通道数
#if(CN_DEV_CPU1)
	AngFrameIn[0].PowerUpIni("模拟量输入帧", "SVSUB",  0, CN_NUM_JZ*8+CN_NUM_SV+2,CN_NUM_JZ,8);
#elif(CN_DEV_CPU2)
	AngFrameIn[0].PowerUpIni("模拟量输入帧", "SVSUB",  0, CN_NUM_JZ*8+CN_NUM_SV,CN_NUM_JZ,8);
#endif
	// 模拟量板卡初始化
	for(i=0;i<CN_NUM_BOARD_SAM;i++)
	{
		AngNorAngIn[i].PowerUpIni(ptBoardTab->byName,ptBoardTab->byPinName, AngFrameIn[0], HalBoard::E_Board_Ang24Pin_1, i);
		ptBoardTab++;
	}
	// 模拟量通道初始化
	ptAnaTab   =&g_tAnaTab[0];
#if(CN_FUN_DBUG1)
	ptAnaTabBak =&g_tAnaTab[0];
#endif
	for(i=0;i<CN_NUM_AD;i++)
	{
		pUnitTem=ptCTypeTab[ptAnaTab->wChanType].pUnit1;
		#if(CN_FUN_DBUG1)
		if(ptAnaTab->dwCfg&DB0)
		{
			AngNorAngSampIn[i].PowerUpIni(AngNorAngIn[ptAnaTab->wFrmNo], ptAnaTab->byName,ptAnaTab->byPinName,i, ptAnaTabBak->wADNo,ptAnaTabBak->wADChn, *pUnitTem); 
			AngNorAngSampIn[i].SetSingleAdFlag(1);
		}
		else
		{
			AngNorAngSampIn[i].PowerUpIni(AngNorAngIn[ptAnaTab->wFrmNo], ptAnaTab->byName,ptAnaTab->byPinName,i, ptAnaTab->wADNo,ptAnaTab->wADChn, *pUnitTem); 
		}
		ptAnaTabBak=ptAnaTab;
		#else
		AngNorAngSampIn[i].PowerUpIni(AngNorAngIn[ptAnaTab->wFrmNo], ptAnaTab->byName,ptAnaTab->byPinName,i, ptAnaTab->wADNo,ptAnaTab->wADChn, *pUnitTem); 
		#endif
		ptAnaTab++;
	}
	// CPU1
#if(CN_DEV_CPU1)
	// SV虚拟板卡初始化,此处仅进行初始化,不要和板卡数据关联
	VirSvBoard[0].PowerUpIni("SVCB01","dsSVCB01", AngFrameIn[0], 255);
	VirSvBoard[1].PowerUpIni("SVCB02","dsSVCB02", AngFrameIn[0], 255);
	// SV通道初始化
	ptAnaTab   =&g_tAnaTab[EN_ANA_SV_STR];
	for(j=EN_ANA_SV_STR,i=0;j<EN_ANA_SV_END;j++,i++)
	{
		pUnitTem=ptCTypeTab[ptAnaTab->wChanType].pUnit1;
		SvAngIn[i].PowerUpIni(AngFrameIn[0],ptAnaTab->byName,ptAnaTab->byPinName,j,*pUnitTem);
		ptAnaTab++;
	}
	// 额定延时初始化
	SvAngInDelayA.PowerUpIni(AngFrameIn[0],"A套额定延时","ANA_SVA_DLY",EN_BOARD_SV_SVA,Unit_uS);
	SvAngInDelayB.PowerUpIni(AngFrameIn[0],"B套额定延时","ANA_SVB_DLY",EN_BOARD_SV_SVB,Unit_uS);
	// CPU2
#elif(CN_DEV_CPU2)
	// SV通道初始化
	ptAnaTab   =&g_tAnaTab[EN_ANA_SV_STR];
	for(j=EN_ANA_SV_STR,i=0;j<EN_ANA_SV_END;j++,i++)
	{
		pUnitTem=ptCTypeTab[ptAnaTab->wChanType].pUnit1;
		CmmSvIn[i].PowerUpIni(AngFrameIn[0],ptAnaTab->byName,ptAnaTab->byPinName,i,*pUnitTem);
		ptAnaTab++;
	}
#endif
}
// 仅CPU1 配置参数更新
void  AppAngInCfgRef()
{
#if(CN_DEV_CPU1)
	WORD     i;
	BYTE     j,byPubFlag=FALSE;
	DWORD  *pdwSvCbCfg;
	BOOL   *pbSvSub;
	BOOL   *pbySvCb;
	// 解析自检
	pdwSvCbCfg=g_tagAna.dwSvCbSubCfg;
	for(i=0;i<CN_NUM_BOARD_SV;i++)
	{
		if(VirSvBoard[i].CfgErr())
		{
			pdwSvCbCfg[i]|=CN_SVCFG_CfgErr;
		}
		if(VirSvBoard[i].ParseErr())
		{
			pdwSvCbCfg[i]|=CN_SVCFG_ParseErr;
		}
	}
	// 解析标志
	pbSvSub=g_tagAna.bSvSub;
	pbySvCb=g_tagAna.bySvCb;
	for(i=0;i<CN_NUM_SV;i++)
	{
		pbSvSub[i]=(SvAngIn[i].IsLinked())?TRUE:FALSE;
		
		pbySvCb[i]=0xff;
		if(SvAngIn[i].DataSet()!=NULL)
		{
			for(j=0;j<CN_NUM_BOARD_SV;j++)
			{
				if(SvAngIn[i].DataSet()==&VirSvBoard[j])
				{
					pbySvCb[i]=j;
				}
			}
		}
		// 有订阅判断
		if((pbSvSub[i])&&(pbySvCb[i]!=0xff))
		{
			byPubFlag=TRUE;
		}
	}
	// 无订阅 修正额定延时
	if(byPubFlag==FALSE)
	{
		G_Set_Inter(EN_INTER_SVSUB_NOPUB,TRUE);
		
	}
#endif
}
// 刷新模拟量数据
void AppAngInRef()
{
	register UINT32   i;
	register INT32   *piAnaSam,*piAnaSamBak;
	register UINT32  *pdwAnaQ;
	// 板卡自检状态
	if((AngFrameIn[0].StateNum()-g_tagAna.dwAnaFramNum)!=1)
	{
		G_Set_ChkIn_All(EN_CHK_FRAME_ANA,AngFrameIn[0].StateNum(),g_tagAna.dwAnaFramNum,0);
	}
	else 
	{
		G_Clr_ChkIn(EN_CHK_FRAME_ANA);
	}
	g_tagAna.dwAnaFramNum=AngFrameIn[0].StateNum();
	// 模拟量更新
	// 更新标志控制
	piAnaSam   =&g_tagAna.iAnaSam[0];
	piAnaSamBak=&g_tagAna.iAnaSamBak[0];
	if(G_Get_Inter(EN_INTER_OPT_ANA)
	||G_Get_Inter(EN_INTER_OPT_ANA_J)
	||G_Get_Inter(EN_INTER_OPT_ANA_FR))
	{
		for(i=0;i<CN_NUM_SAM;i++)
		{
			piAnaSamBak[i]=piAnaSam[i];
			piAnaSam[i]=AngNorAngSampIn[i].Value();
		}
	}
    for(i=EN_ANA_JZ_STR;i<EN_ANA_JZ_END;i++)
    {
        piAnaSamBak[i]=piAnaSam[i];
        piAnaSam[i]= AngNorAngSampIn[i].Value();
    }
	// CPU1 SV交流量+品质更新
#if(CN_DEV_CPU1)
	{
		UINT32* pdwSvCbStatus;
		// 交流量更新
		if(G_Get_Inter(EN_INTER_OPT_ANA)
		||G_Get_Inter(EN_INTER_OPT_ANA_J)
		||G_Get_Inter(EN_INTER_OPT_ANA_FR))
		{
			piAnaSam    =&g_tagAna.iAnaSam[EN_ANA_SV_STR];
			piAnaSamBak =&g_tagAna.iAnaSamBak[EN_ANA_SV_STR];
			for(i=0;i<CN_NUM_SV;i++)
			{
				piAnaSamBak[i]=piAnaSam[i];
				piAnaSam[i]=SvAngIn[i].Value();
			}
		}
		// 品质更新
		pdwAnaQ = &g_tagAna.dwSvQ[0];
		for (i = 0;i< CN_NUM_SV; i++)
		{
			pdwAnaQ[i]= SvAngIn[i].Q();
		}
		// 控制块状态字更新
		pdwSvCbStatus=g_tagAna.dwSvCbStatus;
		for(i=0;i<CN_NUM_BOARD_SV;i++)
		{
			pdwSvCbStatus[i]=VirSvBoard[i].CheckStatus()->checkStatus1;
		}
	}
#elif(CN_DEV_CPU2)
	if(G_Get_Inter(EN_INTER_OPT_ANA)
	||G_Get_Inter(EN_INTER_OPT_ANA_J)
	||G_Get_Inter(EN_INTER_OPT_ANA_FR))
	{
		// CPU2 SV交流量+品质更新
		piAnaSam    =&g_tagAna.iAnaSam[EN_ANA_SV_STR];
		piAnaSamBak =&g_tagAna.iAnaSamBak[EN_ANA_SV_STR];
		for(i=0;i<CN_NUM_SV;i++)
		{
			piAnaSamBak[i]=piAnaSam[i];
			piAnaSam[i]=CmmSvIn[i].Value();
		}
	}
	// 品质更新
	pdwAnaQ = &g_tagAna.dwSvQ[0];
	for (i = 0;i<CN_NUM_SV;i++)
	{
		pdwAnaQ[i]= CmmSvIn[i].Q();
	}
#endif
}
// 品质输出
void AppAngQRef()
{
	if(!g_tagAna.byAnaQChg)
	{
		return;
	}
	register UINT32  i;
	register UINT32  *pdwAnaQ;
	// 常规量品质
	pdwAnaQ =&g_tagAna.dwAnaQ[0];
	for(i=0;i<CN_NUM_SAM;i++)
	{
		AngFrameIn[0].SetOutQ(i, pdwAnaQ[i]);
	}
#if(CN_SV_IN_ENA)
	for(i=EN_ANA_SV_STR;i<EN_ANA_SV_END;i++)
	{
		AngFrameIn[0].SetOutQ(i, pdwAnaQ[i]);
	}
#endif
}
// 系数输出
void AppAngParaRef()
{
	register UINT32   i;
	register WORD    *pwAnaCoe;
	register UINT32  *pdwAnaCoe;
	const tagAnaTab  *ptAnaTab;
	// 幅值校准系数下发标志
	if(g_tagAna.byAnaAmCoeChg)
	{
		//LogMsg.Stamp()<<"校准系数下发"<<"\n";
		ptAnaTab   =&g_tAnaTab[0];
		pdwAnaCoe  =g_tagAna.dwAnaAmCoe;
		for(i=0;i<CN_NUM_AD;i++,ptAnaTab++)
		{
			AngFrameIn[0].SetOutCoe(ptAnaTab->wADNo,ptAnaTab->wADChn,pdwAnaCoe[i]);
			//LogMsg.Stamp()<<"AD:"<<ptAnaTab->wADNo<<"-"<<ptAnaTab->wADChn<<"Coe"<<pdwAnaCoe[i]<<"\n";
		}
		AppEventRunRef(EN_RUN_AM_COE_S);
		g_tagAna.byAnaAmCoeChg=FALSE;

	}
	else if(g_tagAna.byAnaAngCoeChg)
	{
		//LogMsg.Stamp()<<"相位补偿系数下发"<<"\n";
		pwAnaCoe  =g_tagAna.wAnaAngCoe;
		for(i=0;i<CN_NUM_JZ;i++)
		{
			//LogMsg.Stamp()<<"AD:"<<i<<"-0"<<"Coe"<<pwAnaCoe[0]<<"\n";
			//LogMsg.Stamp()<<"AD:"<<i<<"-1"<<"Coe"<<pwAnaCoe[1]<<"\n";
			AngFrameIn[0].SetADAdJust(i,0,(uint32)(*pwAnaCoe++));
			AngFrameIn[0].SetADAdJust(i,1,(uint32)(*pwAnaCoe++));
		}
		AppEventRunRef(EN_RUN_ANG_COE_S);
		g_tagAna.byAnaAngCoeChg=FALSE;

	}
#if 0	
	else if(g_tagAna.byAnaDcCoeChg)
	{
		ptAnaTab   =&g_tAnaTab[0];
		pwAnaCoe  =g_tagAna.wAnaDcCoe;
		//LogMsg.Stamp()<<"直流补偿系数下发"<<"\n";
		for(i=0;i<CN_NUM_AD;i++,ptAnaTab++)
		{
			//AngFrameIn[0].SetOutDc(ptAnaTab->wADNo,ptAnaTab->wADChn,pwAnaCoe[i]);
			//LogMsg.Stamp()<<"AD"<<ptAnaTab->wADNo<<"-"<<ptAnaTab->wADChn<<"COE"<<pwAnaCoe[i]<<"\n";
		}
		AppEventRunRef(EN_RUN_DCBC_COE_S);
		g_tagAna.byAnaDcCoeChg=FALSE;
	}
#endif
}


