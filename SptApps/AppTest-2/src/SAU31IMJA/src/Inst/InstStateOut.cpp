#include "InstResource.h"
// 硬开出
ApiBoardNormalStateOut NorDoBoard[CN_NUM_BOARD_DO_RTN];
ApiNormalBoolOut NorDoOut[CN_NUM_DO_RTN];
// GOOSE开出
ApiGoOutFrame   GoOutFrame[1];
ApiGoOutDataSet GoDataSetOut[CN_NUM_GOCB_PUB];
ApiGoPosOut     GoPosOutCell[CN_NUM_DI_DI+CN_NUM_GOOUT];   // 硬开入转GOOSE开出
ApiGoDpPosOut   GoDpPosOutCell[CN_NUM_DPI];                   // 双点开入转GOOSE开出
ApiGoUnion32Out GoDcOutCell[CN_NUM_DC];                       // 直流信息

void AppStateOutPowerUpIni()
{

	WORD i,j,k,wStr,wEnd;
	
	const tagBoardIoTab *ptBoardTab;
	const tagDoTab      *ptDoTab;
	
	const tagGoOutTab   *ptGoOutTab;
	
	const tagDiTab      *ptDiTab;
	
	const tagDpiTab     *ptDpiTab;
	
	const tagDCTab      *ptDcTab;

	ptBoardTab =&g_tBoardDOTab[0];
	// 出口板卡初始化
	for(i=0;i<CN_NUM_BOARD_DO_RTN;i++,ptBoardTab++)
	{
		if(i==EN_BOARD_DIO_DO)
		{
			NorDoBoard[i].PowerUpIni(ptBoardTab->byName,ptBoardTab->byPinName,HalBoard::E_Board_DIO_DO7_1,ptBoardTab->wAddrBoard,ptBoardTab->wAddrFrame);
		}
		else
		{
			NorDoBoard[i].PowerUpIni(ptBoardTab->byName,ptBoardTab->byPinName,HalBoard::E_Board_Do32Pin_1,ptBoardTab->wAddrBoard,ptBoardTab->wAddrFrame);
		}
		wStr=ptBoardTab->wIndexStr;
		wEnd=ptBoardTab->wIndexEnd;
		if((wStr>CN_NUM_DO_RTN)||(wEnd>CN_NUM_DO_RTN)||(wStr>wEnd))
		{
			LogErr.Stamp()<<"DO板卡"<<i<<"配置错误"<<"\n";
			continue;
		}
		ptDoTab    =&g_tDoTab[wStr];
		for(j=wStr,k=0;j<wEnd;j++,k++)
		{
			NorDoOut[j].ProtOutPowerUpIni(NorDoBoard[i], ptDoTab->byName, ptDoTab->byPinName, k);
			ptDoTab++;
		}
	}
	GoOutFrame[0].PowerUpIni("GOOSE输出帧", "GOOSEPUB", 0, CN_NUM_DI_DI+CN_NUM_GOOUT+CN_NUM_DPI+CN_NUM_DC);
// GOOSE 最大支持256路数据
	GoDataSetOut[0].PowerUpIni("Go数据集0", "dsGOOSE1", "dsGOOSE1", GoOutFrame[0], 255);
	GoDataSetOut[1].PowerUpIni("Go数据集1", "dsGOOSE2", "dsGOOSE2", GoOutFrame[0], 255);
	GoDataSetOut[2].PowerUpIni("Go数据集2", "dsGOOSE3", "dsGOOSE3", GoOutFrame[0], 255);
	GoDataSetOut[3].PowerUpIni("Go数据集3", "dsGOOSE4", "dsGOOSE4", GoOutFrame[0], 255);
	GoDataSetOut[4].PowerUpIni("Go数据集4", "dsGOOSE5", "dsGOOSE5", GoOutFrame[0], 255);
	GoDataSetOut[5].PowerUpIni("Go数据集5", "dsGOOSE6", "dsGOOSE6", GoOutFrame[0], 255);
	GoDataSetOut[6].PowerUpIni("Go数据集6", "dsGOOSE7", "dsGOOSE7", GoOutFrame[0], 255);
	GoDataSetOut[7].PowerUpIni("Go数据集7", "dsGOOSE8", "dsGOOSE8", GoOutFrame[0], 255);
	j=0;
	ptDiTab    =&g_tDiTab[0];
	for(i=0;i<CN_NUM_DI_DI;i++,j++)
	{
		GoPosOutCell[i].PowerUpIni(ptDiTab->byName, ptDiTab->byPinName, GoOutFrame[0], j);
		ptDiTab++;
	}
	ptGoOutTab =&g_tGoOutTab[0];
	for(i=CN_NUM_DI_DI;i<(CN_NUM_DI_DI+CN_NUM_GOOUT);i++,j++)
	{
		GoPosOutCell[i].PowerUpIni(ptGoOutTab->byName, ptGoOutTab->byPinName, GoOutFrame[0], j);
		ptGoOutTab++;
	}
	// GOOSE双点信息
	ptDpiTab   =&g_tDpiTab[0];
	for(i=0;i<CN_NUM_DPI;i++,j++)
	{
		GoDpPosOutCell[i].PowerUpIni(ptDpiTab->byName, ptDpiTab->byPinName, GoOutFrame[0], j);
		ptDpiTab++;
	}
	// GOOSE直流信息
	ptDcTab    =&g_tDCTab[0];
	for(i=0;i<CN_NUM_DC;i++,j++)
	{
		GoDcOutCell[i].PowerUpIni(ptDcTab->byName, ptDcTab->byPinName, GoOutFrame[0], j);
		ptDcTab++;
	}
}
// 配置文件刷新
void AppStateOutCfgRef()
{
	WORD i;
	DWORD *pdwGoPubStatus;
	// 控制块解析标志更新
	pdwGoPubStatus= g_tagIO.dwGoPubStatus;
	for(i=0;i<CN_NUM_GOCB_PUB;i++)
	{
		if(GoDataSetOut[i].CfgErr())
		{
			pdwGoPubStatus[i]|=CN_SVCFG_CfgErr;
		}
		if(GoDataSetOut[i].ParseErr())
		{
			pdwGoPubStatus[i]|=CN_SVCFG_ParseErr;
		}
	}
	// 发布标志刷新
	for(i=0;i<CN_NUM_DI_DI;i++)
	{
		if(!GoPosOutCell[i].IsVLinked())
		{
			G_Set_Inter(EN_INTER_GOPUB_DI_LOSE,TRUE);
		}
		if((GoPosOutCell[i].IsVLinked())&&(!GoPosOutCell[i].IsTLinked()))
		{
			G_Set_Inter(EN_INTER_GOPUB_DI_T,TRUE);
		}
		if(GoPosOutCell[i].IsQLinked())
		{
			G_Set_Inter(EN_INTER_GOPUB_DI_Q,TRUE);
		}
		if((!GoPosOutCell[i].IsVLinked())&&(GoPosOutCell[i].IsTLinked()||GoPosOutCell[i].IsQLinked()))
		{
			G_Set_Inter(EN_INTER_GOPUB_DI_Dif,TRUE);
		}
	}
	for(i=CN_NUM_DI_DI;i<(CN_NUM_DI_DI+CN_NUM_GOOUT);i++)
	{
		if(!GoPosOutCell[i].IsVLinked())
		{
			G_Set_Inter(EN_INTER_GOPUB_OUT_LOSE,TRUE);
		}
		if(GoPosOutCell[i].IsQLinked())
		{
			G_Set_Inter(EN_INTER_GOPUB_OUT_Q,TRUE);
		}
		if((!GoPosOutCell[i].IsVLinked())&&(GoPosOutCell[i].IsTLinked()||GoPosOutCell[i].IsQLinked()))
		{
			G_Set_Inter(EN_INTER_GOPUB_OUT_Dif,TRUE);
		}
	}
	for(i=0;i<CN_NUM_DPI;i++)
	{
		if(!GoDpPosOutCell[i].IsVLinked())
		{
			G_Set_Inter(EN_INTER_GOPUB_DPI_LOSE,TRUE);
		}
		if((GoDpPosOutCell[i].IsVLinked())&&(!GoDpPosOutCell[i].IsTLinked()))
		{
			G_Set_Inter(EN_INTER_GOPUB_DPI_T,TRUE);
		}
		if(GoDpPosOutCell[i].IsQLinked())
		{
			G_Set_Inter(EN_INTER_GOPUB_DPI_Q,TRUE);
		}
		if((!GoDpPosOutCell[i].IsVLinked())&&(GoPosOutCell[i].IsTLinked()||GoPosOutCell[i].IsQLinked()))
		{
			G_Set_Inter(EN_INTER_GOPUB_DPI_Dif,TRUE);
		}
	}
	for(i=0;i<CN_NUM_DC;i++)
	{
		if(!GoDcOutCell[i].IsVLinked())
		{
			G_Set_Inter(EN_INTER_GOPUB_DC_LOSE,TRUE);
		}
		if(GoDcOutCell[i].IsQLinked())
		{
			G_Set_Inter(EN_INTER_GOPUB_DC_Q,TRUE);
		}
		if((!GoDcOutCell[i].IsVLinked())&&(GoDcOutCell[i].IsTLinked()||GoDcOutCell[i].IsQLinked()))
		{
			G_Set_Inter(EN_INTER_GOPUB_DC_Dif,TRUE);
		}
	}
}
// GOOSE开出返校数据刷新
void AppStateOutRtnRef()
{
	WORD i;
	DWORD       *pdwBoardCnt,*pdwDIIn;
	tagTimeUTC  *ptDIInUTC;
	SalDateStamp  tStamp;
	ApiBoardNormalStateOut *pNorDoBoard;
	// 硬开入状态及时标刷新
	pdwDIIn 	 =&g_tagIO.dwDIIn[0];
	ptDIInUTC	 =&g_tagIO.tDIInUTC[CN_NUM_BOARD_DI_DI];
	pdwBoardCnt  =&g_tagIO.dwDIBoardCnt[CN_NUM_BOARD_DI_DI];
	pNorDoBoard  =&NorDoBoard[0];

	for(i=EN_BOARD_DI_DI_END;i<EN_BOARD_DI_END;i++,ptDIInUTC++,pdwBoardCnt++,pNorDoBoard++)
	{	
		if(G_Sys_Div4_4)
		{
			if((pNorDoBoard->CheckStatus()->recvFrameOkCnt==*pdwBoardCnt)
			||(pNorDoBoard->CheckStatus()->checkStatus1&(DB2+DB3)))
			{
				G_Set_ChkIn(EN_CHK_BOARD_DI_STR+i);
				#if 0
			LogMsg<<"DOCnt"<<pNorDoBoard->CheckStatus()->recvFrameOkCnt
				<<"   "<<*pdwBoardCnt \
				<<"   "<<pNorDoBoard->CheckStatus()->checkStatus1 \
				<<"   "<<pNorDoBoard->CheckStatus()->checkStatus2 \
			    <<"   "<<pNorDoBoard->CheckStatus()->recvFrameErrCnt \
			    <<"   "<<pNorDoBoard->CheckStatus()->sendFrameOkCnt \
				<<"   "<<pNorDoBoard->CheckStatus()->sendFrameErrCnt \
				<<"\n";
			#endif
				*pdwBoardCnt=pNorDoBoard->CheckStatus()->recvFrameOkCnt;
				//*pbBoard=TRUE;
			}
			else
			{
				G_Clr_ChkIn(EN_CHK_BOARD_DI_STR+i);
				*pdwBoardCnt=pNorDoBoard->CheckStatus()->recvFrameOkCnt;
				//*pbBoard=FALSE;
			}
			// 自检2
			if(pNorDoBoard->CheckStatus()->checkStatus1&(DB0))
			{
				G_Set_ChkIn(EN_CHK_BOARD_DO_CHN1_STR+i);
			}
			else
			{
				G_Clr_ChkIn(EN_CHK_BOARD_DO_CHN1_STR+i);
			}
			// 自检3
			if(pNorDoBoard->CheckStatus()->checkStatus1&(DB1))
			{
				G_Set_ChkIn(EN_CHK_BOARD_DO_CHN2_STR+i);
			}
			else
			{
				G_Clr_ChkIn(EN_CHK_BOARD_DO_CHN2_STR+i);
			}
		}
		if(pNorDoBoard->VerfyCodeNum()!=g_tagIO.dwDICnt[i])
		{
			pdwDIIn[i]=pNorDoBoard->VerfyCode(0);
			tStamp=pNorDoBoard->Stamp();
			ptDIInUTC->dwUSecond_L  =tStamp.usL;
			ptDIInUTC->dwUSecond_H  =tStamp.usH;
			ptDIInUTC->dwLeapSecFlg =tStamp.q.q;
			g_tagIO.dwDICnt[i]=pNorDoBoard->VerfyCodeNum();
		}
	}
}

// GOOSE开出数据刷新
void AppStateOutRef()
{
	register BOOL   *pbDIHldIn,*pbDCChg,*bDCGoOutFresh,*pbGoOut,*pbGoOutXor;
	register BYTE   *pbyDpiIn,*pbyDpiInXor;
	register WORD   i,j,k,wStr,wEnd;
	register DWORD  dwDIHldXor32;
	register INT32      *piDc;
	register FLOAT32    *pfDc;
	register tagTimeUTC *ptagTimeUTC;
	register DWORD      *pdwQ;

	u32value   uVal;
	const tagBoardIoTab *ptBoardTab;
	SalDateStamp  tStamp;
	
	ptBoardTab  =&g_tBoardDITab[0];
	pbDIHldIn   =g_tagIO.bDIHldIn;
	pdwQ        =g_tagIO.dwDIQ;
	ptagTimeUTC =g_tagIO.tDIHldUTC;
	// 更新第一帧数据
	if(g_tagIO.byDIFstToGoose)
	{
		tStamp.usL = g_tagPub.tSysTimeUTC.dwUSecond_L;
		tStamp.usH = g_tagPub.tSysTimeUTC.dwUSecond_H;
		tStamp.q.q = g_tagPub.tSysTimeUTC.dwLeapSecFlg;
		ApiGoPosOut *pGoPosOutCell=&GoPosOutCell[0];

		for(i=0;i<CN_NUM_DI_DI;i++,pGoPosOutCell++)
		{
			// 更新状态
			pGoPosOutCell->SetValue(pbDIHldIn[i]);
			pGoPosOutCell->SetStamp(tStamp);
			// 更新品质
			if(pGoPosOutCell->IsQLinked())
			{
				pGoPosOutCell->SetQ(pdwQ[i]);
			}
		}
		g_tagIO.byDIFstToGoose=FALSE;
	}
	else
	{
		for(i=0;i<CN_NUM_BOARD_DI_DI;i++,ptBoardTab++)
		{
			// 暂定方案,通过变位判断是否需要更新数据
			dwDIHldXor32=g_tagIO.dwDIHldXor32[i];
			if(dwDIHldXor32!=0)
			{
				wStr=ptBoardTab->wIndexStr;
				wEnd=ptBoardTab->wIndexEnd;
				for(j=wStr,k=0;j<wEnd;j++,k++)
				{
					if(dwDIHldXor32&g_dwBit[k])
					{
						// 更新状态
						GoPosOutCell[j].SetValue(pbDIHldIn[j]);
						// 更新时间
						tStamp.usL=ptagTimeUTC[j].dwUSecond_L;
						tStamp.usH=ptagTimeUTC[j].dwUSecond_H;
						tStamp.q.q=ptagTimeUTC[j].dwLeapSecFlg;
					
						GoPosOutCell[j].SetStamp(tStamp);
						// 更新品质
						if(GoPosOutCell[j].IsQLinked())
						{
							GoPosOutCell[j].SetQ(pdwQ[j]);
						}
					}
				}
			}
		}
	}
	// 中间信息
	pbGoOut      =g_tagIO.bGoOut;              // GO发布值布尔型
	pbGoOutXor   =g_tagIO.bGoOutXor;           // GO发布值变化标志
	pdwQ         =g_tagIO.dwGoOutQ;            // GO发布品质
	ptagTimeUTC  =g_tagIO.tGoOutT;             // GO订阅数据时标
	for(i=CN_NUM_DI_DI,j=0;i<(CN_NUM_DI_DI+CN_NUM_GOOUT);i++,j++)
	{
		if(pbGoOutXor[j])
		{
			GoPosOutCell[i].SetValue(pbGoOut[j]);
			tStamp.usL=ptagTimeUTC[j].dwUSecond_L;
			tStamp.usH=ptagTimeUTC[j].dwUSecond_H;
			tStamp.q.q=ptagTimeUTC[j].dwLeapSecFlg;
			GoPosOutCell[i].SetStamp(tStamp);
		}
	}
	// GOOSE双点信息
	ptagTimeUTC  =g_tagIO.tDpiUTC;
	pbyDpiIn     =g_tagIO.byDpiIn;
	pbyDpiInXor  =g_tagIO.byDpiInXor;
	pdwQ         =g_tagIO.dwDpiQ;
	// 更新第一帧数据
	if(g_tagIO.byDpiFstToGoose)
	{
		tStamp.usL=g_tagPub.tSysTimeUTC.dwUSecond_L;
		tStamp.usH=g_tagPub.tSysTimeUTC.dwUSecond_H;
		tStamp.q.q=g_tagPub.tSysTimeUTC.dwLeapSecFlg;
		ApiGoDpPosOut *pGoDpPosOutCell=&GoDpPosOutCell[0];
		for(i=0;i<CN_NUM_DPI;i++,pGoDpPosOutCell++)
		{
			pGoDpPosOutCell->SetValue(pbyDpiIn[i]);
			pGoDpPosOutCell->SetStamp(tStamp);
						// 更新品质
			if(pGoDpPosOutCell->IsQLinked())
			{
				pGoDpPosOutCell->SetQ(pdwQ[i]);
			}
		}
		g_tagIO.byDpiFstToGoose=FALSE;
	}
	else
	{
		for(i=0;i<CN_NUM_DPI;i++)
		{
			if(pbyDpiInXor[i])
			{
				GoDpPosOutCell[i].SetValue(pbyDpiIn[i]);
				tStamp.usL=ptagTimeUTC[i].dwUSecond_L;
				tStamp.usH=ptagTimeUTC[i].dwUSecond_H;
				tStamp.q.q=ptagTimeUTC[i].dwLeapSecFlg;
				GoDpPosOutCell[i].SetStamp(tStamp);
			}
			// 品质更新
		}
	}
	// GOOSE直流信息
	bDCGoOutFresh=g_tagDC.bDCGoOutFresh;
	pbDCChg      =g_tagDC.bDCChg;
	piDc         =g_tagDC.iDCOutCom;
	pfDc         =g_tagDC.fDCOutCom;
	ptagTimeUTC  =g_tagDC.tDCOut;
	
	for(j=0;j<CN_NUM_BOARD_DC;j++)
	{
		if(bDCGoOutFresh[j])
		{
			for(i=g_tBoardDCTab[j].wIndexStr;i<g_tBoardDCTab[j].wIndexEnd;i++)
			{
				if(!pbDCChg[i])
				{
					continue;
				}
				if(!GoDcOutCell[i].IsVLinked())
				{
					continue;
				}
				if(GoDcOutCell[i].GoValueType()==spt::GoSvDataType::E_GOSV_INT32)
				{
					uVal.i32 =piDc[i];
				}
				else if(GoDcOutCell[i].GoValueType()==spt::GoSvDataType::E_GOSV_FLOAT32)
				{
					uVal.f32 =pfDc[i];
				}
				else
				{
					uVal.u32 = (UINT32)piDc[i];
				}

				GoDcOutCell[i].SetValue(uVal);

				if(GoDcOutCell[i].IsTLinked())
				{
					tStamp.usL=(G_Get_PUB_UTC)->dwUSecond_L;
					tStamp.usH=(G_Get_PUB_UTC)->dwUSecond_H;
					tStamp.q.q=(G_Get_PUB_UTC)->dwLeapSecFlg;
					GoDcOutCell[i].SetStamp(tStamp);
				}
				pbDCChg[i]=FALSE;
			}
			bDCGoOutFresh[j]=FALSE;
			break;
		}
	}
	// 品质变化
	if(G_Get_Inter(EN_INTER_GOPUB_DC_Q))
	{
		pdwQ =g_tagDC.dwDCOutQ;
		for(j=0;j<CN_NUM_BOARD_DC;j++)
		{
			if(g_tagDC.bDCOutQChg[j])
			{
				for(i=g_tBoardDCTab[j].wIndexStr;i<g_tBoardDCTab[j].wIndexEnd;i++)
				{
					//if(GoDcOutCell[i].IsTLinked())
					//{
					//	tStamp.usL=(G_Get_PUB_UTC)->dwUSecond_L;
					//	tStamp.usH=(G_Get_PUB_UTC)->dwUSecond_H;
					//	tStamp.q.q=(G_Get_PUB_UTC)->dwLeapSecFlg;
					//	GoDcOutCell[i].SetStamp(tStamp);
					//}
					if(GoDcOutCell[i].IsQLinked())
					{
						GoDcOutCell[i].SetQ(pdwQ[j]);
					}

				}
				g_tagDC.bDCOutQChg[j]=FALSE;
				break;
			}
		}
	}
// 装置硬开出
	BOOL *pbDoOut,*pbDoOutXor;
	pbDoOut     =&g_tagIO.bDOOut[0];
	pbDoOutXor  =&g_tagIO.bDOOutXor[0];
	for(i=0;i<CN_NUM_DO_RTN;i++)
	{
		if(pbDoOutXor[i])
		{
			NorDoOut[i].SetValue(pbDoOut[i]);
		}
	}
}

