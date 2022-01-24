#include "InstResource.h"

//硬开入
ApiBoardNormalStateIn NormalStateBoardIn[CN_NUM_BOARD_DI_DI];
ApiNormalBoolIn NormalBoolIn[CN_NUM_DI_DI];
//直流量
ApiBoardNormalDcIn AppDcInBoard;
ApiNormalDcIn      AppNormalDcIn[CN_NUM_DC_SAM];
ApiNormalDcIn      AppNormalDcJZ;
// GOOSE开入
ApiGoInFrame       GoInFrame[1];
ApiGoInCb          GoInCB[CN_NUM_GOCB_SUB];
ApiGoPosIn         GoPosIn[CN_NUM_GOIN_S];
// 光功率信息
ApiSmartBoardInfo      SmartBoard[2];

void AppStateInPowerUpIni()
{
	WORD i, j, k, wStr, wEnd;
	const tagBoardIoTab* ptBoardIoTab;
	const tagDiTab* ptDiTab;

	const tagBoardDCTab* ptBoardDcTab;
	const tagDCTab* ptDcTab;

	const tagGoInTab* ptGoInTab;

	const VarUnits* pUnitTem;
	const tagCTypeTab* ptCTypeTab;

	ptCTypeTab = &g_tCTypeTab[0];

	ptBoardIoTab = &g_tBoardDITab[0];


	// 1.硬开入初始化
	for (i = 0; i < CN_NUM_BOARD_DI_DI; i++)
	{
		if (i == EN_BOARD_DIO_DI)
		{
			NormalStateBoardIn[i].PowerUpIni(ptBoardIoTab->byName, ptBoardIoTab->byPinName, HalBoard::E_Board_DIO_YX14_1, ptBoardIoTab->wAddrBoard, ptBoardIoTab->wAddrFrame);
		}
		else if (i == EN_BOARD_OPB)
		{
			NormalStateBoardIn[i].PowerUpIni(ptBoardIoTab->byName, ptBoardIoTab->byPinName, HalBoard::E_Board_OPB_YX_1, ptBoardIoTab->wAddrBoard, ptBoardIoTab->wAddrFrame);
		}
		else
		{
			NormalStateBoardIn[i].PowerUpIni(ptBoardIoTab->byName, ptBoardIoTab->byPinName, HalBoard::E_Board_YX32Pin_1, ptBoardIoTab->wAddrBoard, ptBoardIoTab->wAddrFrame);
		}
		// 增加判据
		wStr = ptBoardIoTab->wIndexStr;
		wEnd = ptBoardIoTab->wIndexEnd;
		if ((wStr >= CN_NUM_DI_DI) || (wEnd > CN_NUM_DI_DI) || (wStr > wEnd))
		{
			LogErr.Stamp() << "DI板卡" << i << "配置错误" << "\n";
			ptBoardIoTab++;
			continue;
		}
		ptDiTab = &g_tDiTab[wStr];
		for (j = wStr, k = 0; j < wEnd; j++, k++)
		{
			NormalBoolIn[j].PowerUpIni(NormalStateBoardIn[i], ptDiTab->byName, ptDiTab->byPinName, k);
			ptDiTab++;
		}
		ptBoardIoTab++;
	}
	// 2.1直流板卡初始化(仅包含直流数据)
	ptBoardDcTab = &g_tBoardDCTab[EN_BOARD_DC_SAM];
	ptDcTab = &g_tDCTab[EN_DC_SAM_STR];
	AppDcInBoard.PowerUpIni(ptBoardDcTab->byName, ptBoardDcTab->byPinName, HalBoard::E_Board_Dc32Pin_1, ptBoardDcTab->wAddrBoard, ptBoardDcTab->wAddrFrame, ptBoardDcTab->wSrcIndexNum + 1);
	for (i = EN_DC_SAM_STR; i < EN_DC_SAM_END; i++)
	{
		pUnitTem = (G_Get_PARA_I(ptCTypeTab[ptDcTab->wType].wParaIndex) == 1) ? ptCTypeTab[ptDcTab->wType].pUnit2 : ptCTypeTab[ptDcTab->wType].pUnit1;
		AppNormalDcIn[i].PowerUpIni(AppDcInBoard, ptDcTab->byName, ptDcTab->byPinName, i, *pUnitTem);
		ptDcTab++;
	}
	AppNormalDcJZ.PowerUpIni(AppDcInBoard, g_tDCTab[EN_DC_V11].byName, g_tDCTab[EN_DC_V11].byPinName, i, *(ptCTypeTab[g_tDCTab[EN_DC_V11].wType].pUnit1));
	// 2.2光功率虚拟板卡初始化
#if(CN_DEV_CPU1)
	// 此处特殊处理:背板光功率由主FPGA采集上送
	ptBoardDcTab = &g_tBoardDCTab[EN_BOARD_DC_OPT1_1];
	SmartBoard[0].PowerUpIni(ptBoardDcTab->byName, ptBoardDcTab->byPinName, ptBoardDcTab->wAddrBoard, (CN_NUM_DC_OPT1) >> 2);
	ptBoardDcTab = &g_tBoardDCTab[EN_BOARD_DC_OPT1_2];
	SmartBoard[1].PowerUpIni(ptBoardDcTab->byName, ptBoardDcTab->byPinName, ptBoardDcTab->wAddrBoard, 0);
#elif(CN_DEV_CPU2)
	ptBoardDcTab = &g_tBoardDCTab[EN_BOARD_DC_OPT2];
	SmartBoard[0].PowerUpIni(ptBoardDcTab->byName, ptBoardDcTab->byPinName, ptBoardDcTab->wAddrBoard, (ptBoardDcTab->wSrcIndexNum) >> 2);
#endif
	// 3.GOOSE开入信号初始化
	// 3.1GOOSE帧
	GoInFrame[0].PowerUpIni("GOOSE订阅帧", "GOOSESUB", 0, 255);
	// 3.2GOOSE控制块
	GoInCB[0].PowerUpIni("GOOSE订阅控制块0", "GOCBPUB0", GoInFrame[0], 255);
	GoInCB[1].PowerUpIni("GOOSE订阅控制块1", "GOCBPUB1", GoInFrame[0], 255);
	GoInCB[2].PowerUpIni("GOOSE订阅控制块2", "GOCBPUB2", GoInFrame[0], 255);
	GoInCB[3].PowerUpIni("GOOSE订阅控制块3", "GOCBPUB3", GoInFrame[0], 255);
	GoInCB[4].PowerUpIni("GOOSE订阅控制块4", "GOCBPUB4", GoInFrame[0], 255);
	GoInCB[5].PowerUpIni("GOOSE订阅控制块5", "GOCBPUB5", GoInFrame[0], 255);
	GoInCB[6].PowerUpIni("GOOSE订阅控制块6", "GOCBPUB6", GoInFrame[0], 255);
	GoInCB[7].PowerUpIni("GOOSE订阅控制块7", "GOCBPUB7", GoInFrame[0], 255);
	GoInCB[8].PowerUpIni("GOOSE订阅控制块8", "GOCBPUB8", GoInFrame[0], 255);
	GoInCB[9].PowerUpIni("GOOSE订阅控制块9", "GOCBPUB9", GoInFrame[0], 255);
	GoInCB[10].PowerUpIni("GOOSE订阅控制块10", "GOCBPUB10", GoInFrame[0], 255);
	GoInCB[11].PowerUpIni("GOOSE订阅控制块11", "GOCBPUB11", GoInFrame[0], 255);
	// 3.3GOOSE单点信号
	ptGoInTab = &g_tGoInTab[EN_GOIN_S_STR];
	for (i = 0, j = EN_GOIN_S_STR; i < CN_NUM_GOIN_S; i++, j++)
	{
		GoPosIn[i].PowerUpIni(ptGoInTab->byName, ptGoInTab->byPinName, GoInFrame[0], j);
		ptGoInTab++;
	}
}
void AppStateInCfgRef()
{
	WORD  i;
	BYTE  j;
	BYTE* pbyGoInSub, * pbyGoInGoCb;
	WORD* pwAppId;
	DWORD* pdwGoInSubStatus;
	// 控制块解析标志更新
	pdwGoInSubStatus = g_tagIO.dwGoInSubStatus;
	for (i = 0; i < CN_NUM_GOCB_SUB; i++)
	{
		if (GoInCB[i].CfgErr())
		{
			pdwGoInSubStatus[i] |= CN_SVCFG_CfgErr;
		}
		if (GoInCB[i].ParseErr())
		{
			pdwGoInSubStatus[i] |= CN_SVCFG_ParseErr;
		}
	}
	pbyGoInSub = &g_tagIO.byGoInSub[EN_GOIN_S_STR];
	pbyGoInGoCb = &g_tagIO.byGoInGoCb[EN_GOIN_S_STR];
	pwAppId = &g_tagIO.wGoInAppId[EN_GOIN_S_STR];

	for (i = 0; i < CN_NUM_GOIN_S; i++)
	{
		// 更新GOOSE控制块编号
		*pbyGoInGoCb = 0xFF;
		if (GoPosIn[i].GoCb() != NULL)
		{
			for (j = 0; j < CN_NUM_GOCB_SUB; j++)
			{
				if (GoPosIn[i].GoCb() == &GoInCB[j])
				{
					*pbyGoInGoCb = j;
					// APPID 获取
					if (GoInCB[j].GoCbInfo() != NULL)
					{
						*pwAppId = GoInCB[j].GoCbInfo()->connect.addr.appId;
					}
					break;
				}
			}
		}
		if (GoPosIn[i].IsVLinked() && (*pbyGoInGoCb == 0xFF))
		{
			G_Set_Inter(EN_INTER_GOSUB_GOCB, TRUE);
		}
		if (GoPosIn[i].IsVLinked())
		{
			*pbyGoInSub = TRUE;
			G_Set_Inter(EN_INTER_GOSUB_V, TRUE);
		}
		if (GoPosIn[i].IsTLinked())
		{
			G_Set_Inter(EN_INTER_GOSUB_T, TRUE);
		}
		if (GoPosIn[i].IsQLinked())
		{
			G_Set_Inter(EN_INTER_GOSUB_Q, TRUE);
		}
		if ((!GoPosIn[i].IsVLinked()) && (GoPosIn[i].IsQLinked() || (GoPosIn[i].IsTLinked())))
		{
			G_Set_Inter(EN_INTER_GOSUB_Dif, TRUE);
		}
		pbyGoInGoCb++;
		pbyGoInSub++;
		pwAppId++;
		// 更新GOOSE数据类型
	}
}
void AppStateInDiRef()
{
	register UINT32 i;
	// 硬开入相关局部变量
	register ApiBoardNormalStateIn* pStateBoardIn;
	register DWORD* pdwDIIn, * pdwBoardCnt;
	register tagTimeUTC* ptDIInUTC;

	SalDateStamp  tStamp;
	// 硬开入状态及时标刷新
	pdwDIIn = g_tagIO.dwDIIn;
	ptDIInUTC = g_tagIO.tDIInUTC;
	pdwBoardCnt = g_tagIO.dwDIBoardCnt;
	pStateBoardIn = &NormalStateBoardIn[0];

	for (i = 0; i < CN_NUM_BOARD_DI_DI; i++, ptDIInUTC++, pStateBoardIn++, pdwBoardCnt++)
	{
		if (G_Sys_Div4_2)
		{
			// 分时复用 4中断校验一次
			if ((pStateBoardIn->CheckStatus()->recvFrameOkCnt == *pdwBoardCnt)
				|| (pStateBoardIn->CheckStatus()->checkStatus1 & (DB2 + DB3)))
			{
				G_Set_ChkIn(EN_CHK_BOARD_DI_STR + i);
				*pdwBoardCnt = pStateBoardIn->CheckStatus()->recvFrameOkCnt;
			}
			else
			{
				G_Clr_ChkIn(EN_CHK_BOARD_DI_STR + i);
				*pdwBoardCnt = pStateBoardIn->CheckStatus()->recvFrameOkCnt;
			}
		}

		if (pStateBoardIn->StateNum() != g_tagIO.dwDICnt[i])
		{
			pdwDIIn[i] = pStateBoardIn->Bit32(0);
			tStamp = pStateBoardIn->Stamp();
			ptDIInUTC->dwUSecond_L = tStamp.usL;
			ptDIInUTC->dwUSecond_H = tStamp.usH;
			ptDIInUTC->dwLeapSecFlg = tStamp.q.q;
			g_tagIO.dwDICnt[i] = pStateBoardIn->StateNum();
		}
	}

}

void AppStateInGoRef()
{
	register UINT32 i;
	// GOOSE开入相关局部变量
	register ApiGoInCb* pApiGoInCb;
	register ApiGoPosIn* pGoPosIn;
	register tagTimeUTC* ptGoInUTC;
	register BOOL* pbGoIn, * pbGoInXor;
	register WORD* pwGoInQ;
	register UINT32* pdwGoInStatusA, * pdwGoInStatusB;

	SalDateStamp  tStamp;

	if (g_tagIO.dwGoInCnt != GoInFrame[0].PosFrameNum())
	{
		ptGoInUTC = &g_tagIO.tGoInUTCRev;
		tStamp = GoInFrame[0].FrameStamp();
		ptGoInUTC->dwUSecond_L = tStamp.usL;
		ptGoInUTC->dwUSecond_H = tStamp.usH;
		ptGoInUTC->dwLeapSecFlg = tStamp.q.q;

		pGoPosIn = GoPosIn;
		pbGoIn = &g_tagIO.bGoIn[EN_GOIN_S_STR];
		pbGoInXor = &g_tagIO.bGoInXor[EN_GOIN_S_STR];
		pwGoInQ = &g_tagIO.wGoQSrc[EN_GOIN_S_STR];
		ptGoInUTC = &g_tagIO.tGoInUTC[EN_GOIN_S_STR];
		for (i = 0; i < CN_NUM_GOIN_S; i++, pGoPosIn++)
		{
			if (pGoPosIn->IsVLinked())
			{
				pbGoInXor[i] = pbGoIn[i] ^ (pGoPosIn->Value());
				pbGoIn[i] = pGoPosIn->Value();
				pwGoInQ[i] = pGoPosIn->Q();
				if (pGoPosIn->IsTLinked())
				{
					tStamp = pGoPosIn->Stamp();
					ptGoInUTC[i].dwUSecond_L = tStamp.usL;
					ptGoInUTC[i].dwUSecond_H = tStamp.usH;
					ptGoInUTC[i].dwLeapSecFlg = tStamp.q.q;
				}
			}
		}
		g_tagIO.dwGoInCnt = GoInFrame[0].PosFrameNum();
	}
	// 更新GOOSE订阅状态
	pdwGoInStatusA = g_tagIO.dwGoInStatusA;
	pdwGoInStatusB = g_tagIO.dwGoInStatusB;
	pApiGoInCb = GoInCB;
	for (i = 0; i < CN_NUM_GOCB_SUB; i++, pApiGoInCb++)
	{
		pdwGoInStatusA[i] = pApiGoInCb->StateA();
		pdwGoInStatusB[i] = pApiGoInCb->StateB();
	}
}

void AppStateInDcRef()
{
	register UINT32          i, dwChgFlag = 0;
	register INT16           iDcSam;
	register ApiNormalDcIn* pAppNormalDcIn;
	register INT32* piDCIn;
	register tagDCSamIn* ptDCSamIn;
	// 直流数据刷新
	if ((AppDcInBoard.CheckStatus()->recvFrameOkCnt == g_tagDC.dwDCBoardCnt[EN_BOARD_DC_SAM])
		|| (AppDcInBoard.CheckStatus()->checkStatus1 & (DB2 + DB3)))
	{
		G_Set_ChkIn(EN_CHK_BOARD_DC_SAM);
#if 0		
		LogMsg << "DCCnt" << AppDcInBoard.CheckStatus()->recvFrameCnt
			<< "   " << g_tagDC.dwDCBoardCnt[EN_BOARD_DC_SAM] \
			<< "   " << AppDcInBoard.CheckStatus()->cmmOk \
			<< "   " << AppDcInBoard.CheckStatus()->cmmRecvTypeOk \
			<< "   " << AppDcInBoard.CheckStatus()->powerCmmCfgIniOk \
			<< "\n";
#endif
		g_tagDC.dwDCBoardCnt[EN_BOARD_DC_SAM] = AppDcInBoard.CheckStatus()->recvFrameOkCnt;
	}
	else
	{
		G_Clr_ChkIn(EN_CHK_BOARD_DC_SAM);
		g_tagDC.dwDCBoardCnt[EN_BOARD_DC_SAM] = AppDcInBoard.CheckStatus()->recvFrameOkCnt;
	}

	if (AppDcInBoard.StateNum() != g_tagDC.dwDCRefCnt[EN_BOARD_DC_SAM])
	{
		pAppNormalDcIn = &AppNormalDcIn[0];
		piDCIn = &g_tagDC.iDCIn[0];
		ptDCSamIn = &g_tagDC.tDCSamIn[0];
		for (i = EN_DC_SAM_STR; i < EN_DC_SAM_END; i++, ptDCSamIn++)
		{
			if (ptDCSamIn->wDCPtr >= 10)
			{
				if (ptDCSamIn->wDCCnt > 2)
				{
					piDCIn[i] = (ptDCSamIn->iDCBuf - ptDCSamIn->iDCMax - ptDCSamIn->iDCMin) / (ptDCSamIn->wDCCnt - 2);
					dwChgFlag = 1;
				}
				ptDCSamIn->iDCBuf = 0;
				ptDCSamIn->iDCMax = 0;
				ptDCSamIn->iDCMin = 32767;
				ptDCSamIn->wDCPtr = 0;
				ptDCSamIn->wDCCnt = 0;
				piDCIn[EN_DC_V11] = (INT32)(AppNormalDcJZ.Value() * 0.1526);
				piDCIn[EN_DC_T3] = AppDcInBoard.Temperature();
			}
			else
			{
				iDcSam = (INT16)pAppNormalDcIn[i].Value();
				if (iDcSam >= 0)
				{
					if (iDcSam > ptDCSamIn->iDCMax) { ptDCSamIn->iDCMax = iDcSam; }
					if (iDcSam < ptDCSamIn->iDCMin) { ptDCSamIn->iDCMin = iDcSam; }
					ptDCSamIn->wDCCnt++;
					ptDCSamIn->iDCBuf += iDcSam;
				}
				ptDCSamIn->wDCPtr++;
			}
		}
		g_tagDC.dwDCRefCnt[EN_BOARD_DC_SAM] = AppDcInBoard.StateNum();
		// 最后更新刷新标志
		if (dwChgFlag)
		{
			g_tagDC.wDCRefPtr[EN_BOARD_DC_SAM] = 0;
			g_tagDC.bDCFresh[EN_BOARD_DC_SAM] = TRUE;
		}
	}

}
void AppStateInOpt1Ref()
{
	register UINT32 i;
	register INT32* piDCIn;
	// 光功率
//pCheckStatus=SmartBoard.CheckStatus();
//if((SmartBoard.CheckStatus()->cmmOk==0)||(SmartBoard.CheckStatus()->cmmRecvTypeOk==0)||(SmartBoard.CheckStatus()->powerCmmCfgIniOk==0))
//{
//	G_Set_ChkIn(EN_CHK_FRAME_OPT);
//	pbBoard[EN_BOARD_DC_SAM]=TRUE;
//}
//else
//{
//	G_Clr_ChkIn(EN_CHK_FRAME_OPT);
//	pbBoard[EN_BOARD_DC_SAM]=FALSE;
//}

	ApiSmartBoardInfo* pSmartBoard = &SmartBoard[0];
#if(CN_DEV_CPU1)
	if (pSmartBoard->StateNum() != g_tagDC.dwDCRefCnt[EN_BOARD_DC_OPT1_1])
	{
		piDCIn = &g_tagDC.iDCIn[EN_DC_OPT1_1_STR];
		for (i = 0; i < (CN_NUM_DC_OPT1_1 >> 2); i++)
		{

		}
		g_tagDC.wDCRefPtr[EN_BOARD_DC_OPT1_1] = 0;
		g_tagDC.dwDCRefCnt[EN_BOARD_DC_OPT1_1] = pSmartBoard->StateNum();
		// 最后更新刷新标志
		g_tagDC.bDCFresh[EN_BOARD_DC_OPT1_1] = TRUE;
	}
#elif(CN_DEV_CPU2)
	if (pSmartBoard->StateNum() != g_tagDC.dwDCRefCnt[EN_BOARD_DC_OPT2])
	{
		piDCIn = &g_tagDC.iDCIn[EN_DC_OPT2_STR];
		for (i = 0; i < (CN_NUM_DC_OPT2 >> 2); i++)
		{
			*piDCIn++ = pSmartBoard->NetState(i, SptGoSvStateBoard::E_Light_R);
			*piDCIn++ = pSmartBoard->NetState(i, SptGoSvStateBoard::E_Light_T);
			*piDCIn++ = pSmartBoard->NetState(i, SptGoSvStateBoard::E_Temperature);
			*piDCIn++ = pSmartBoard->NetState(i, SptGoSvStateBoard::E_Voltage);
		}
		g_tagDC.wDCRefPtr[EN_BOARD_DC_OPT2] = 0;
		g_tagDC.dwDCRefCnt[EN_BOARD_DC_OPT2] = pSmartBoard->StateNum();
		// 最后更新刷新标志
		g_tagDC.bDCFresh[EN_BOARD_DC_OPT2] = TRUE;
		g_tagDC.bDCCommFresh[EN_BOARD_DC_OPT2] = TRUE;
	}
#endif
}
void AppStateInOpt1_2Ref()
{
#if(CN_DEV_CPU1)
	register UINT32 i, j;
	register INT32* piDCIn;
	register ApiSmartBoardInfo* pSmartBoard = &SmartBoard[0];

	if (pSmartBoard->StateNum() != g_tagDC.dwDCRefCnt[EN_BOARD_DC_OPT1_2])
	{
		piDCIn = &g_tagDC.iDCIn[EN_DC_OPT1_2_STR];
		j = (CN_NUM_DC_OPT1_1 >> 2);
		for (i = 0; i < (CN_NUM_DC_OPT1_2 >> 2); j++, i++)
		{

		}
		g_tagDC.wDCRefPtr[EN_BOARD_DC_OPT1_2] = 0;
		g_tagDC.dwDCRefCnt[EN_BOARD_DC_OPT1_2] = pSmartBoard->StateNum();
		// 最后更新刷新标志
		g_tagDC.bDCFresh[EN_BOARD_DC_OPT1_2] = TRUE;
	}
#endif
}
void AppStateInRef()
{
	AppStateInDiRef();
	AppStateInGoRef();
	// 32us
	if (G_Sys_Div(128, 4))
		AppStateInDcRef();
	if (G_Sys_Div1024_256)
		AppStateInOpt1Ref();
	if (G_Sys_Div1024_512)
		AppStateInOpt1_2Ref();
}

