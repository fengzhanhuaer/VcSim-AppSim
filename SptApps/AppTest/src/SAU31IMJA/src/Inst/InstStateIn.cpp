#include "InstResource.h"

//Ӳ����
ApiBoardNormalStateIn NormalStateBoardIn[CN_NUM_BOARD_DI_DI];
ApiNormalBoolIn NormalBoolIn[CN_NUM_DI_DI];
//ֱ����
ApiBoardNormalDcIn AppDcInBoard;
ApiNormalDcIn      AppNormalDcIn[CN_NUM_DC_SAM];
ApiNormalDcIn      AppNormalDcJZ;
// GOOSE����
ApiGoInFrame       GoInFrame;
ApiGoInCb          GoInCB[CN_NUM_GOCB_SUB];
ApiGoPosIn         GoPosIn[CN_NUM_GOIN_S];
// �⹦����Ϣ
ApiSmartBoardInfo      SmartBoard[2];

void AppStateInPowerUpIni()
{
	WORD i,j,k,wStr,wEnd;
	const tagBoardIoTab *ptBoardIoTab;
	const tagDiTab      *ptDiTab;
	
	const tagBoardDCTab *ptBoardDcTab;
	const tagDCTab      *ptDcTab;

	const tagGoInTab    *ptGoInTab;
	
	const VarUnits     *pUnitTem;
	const tagCTypeTab  *ptCTypeTab;
	
	ptCTypeTab   =&g_tCTypeTab[0];
	
	ptBoardIoTab =&g_tBoardDITab[0];
	

	// 1.Ӳ�����ʼ��
	for(i=0;i<CN_NUM_BOARD_DI_DI;i++)
	{
		if(i==EN_BOARD_DIO_DI)
		{
			NormalStateBoardIn[i].PowerUpIni(ptBoardIoTab->byName,ptBoardIoTab->byPinName,HalBoard::E_Board_DIO_YX14_1,ptBoardIoTab->wAddrBoard,ptBoardIoTab->wAddrFrame);
		}
		else if(i==EN_BOARD_OPB)
		{
			NormalStateBoardIn[i].PowerUpIni(ptBoardIoTab->byName,ptBoardIoTab->byPinName,HalBoard::E_Board_OPB_YX_1,ptBoardIoTab->wAddrBoard,ptBoardIoTab->wAddrFrame);
		}
		else
		{
			NormalStateBoardIn[i].PowerUpIni(ptBoardIoTab->byName,ptBoardIoTab->byPinName,HalBoard::E_Board_YX32Pin_1,ptBoardIoTab->wAddrBoard,ptBoardIoTab->wAddrFrame);
		}
		// �����о�
		wStr=ptBoardIoTab->wIndexStr;
		wEnd=ptBoardIoTab->wIndexEnd;
		if((wStr>=CN_NUM_DI_DI)||(wEnd>CN_NUM_DI_DI)||(wStr>wEnd))
		{
			LogErr.Stamp()<<"DI�忨"<<i<<"���ô���"<<"\n";
			ptBoardIoTab++;
			continue;
		}
		ptDiTab  =&g_tDiTab[wStr];
		for(j=wStr,k=0;j<wEnd;j++,k++)
		{
			NormalBoolIn[j].PowerUpIni(NormalStateBoardIn[i], ptDiTab->byName, ptDiTab->byPinName, k);
			ptDiTab++;
		}
		ptBoardIoTab++;
	}


	// 2.1ֱ���忨��ʼ��(������ֱ������)
	ptBoardDcTab =&g_tBoardDCTab[EN_BOARD_DC_SAM];
	ptDcTab      =&g_tDCTab[EN_DC_SAM_STR];
	AppDcInBoard.PowerUpIni(ptBoardDcTab->byName,ptBoardDcTab->byPinName,HalBoard::E_Board_Dc32Pin_1,ptBoardDcTab->wAddrBoard,ptBoardDcTab->wAddrFrame,ptBoardDcTab->wSrcIndexNum+1);
	for(i=EN_DC_SAM_STR;i<EN_DC_SAM_END;i++)
	{
		pUnitTem=(G_Get_PARA_I(ptCTypeTab[ptDcTab->wType].wParaIndex)==1)?ptCTypeTab[ptDcTab->wType].pUnit2:ptCTypeTab[ptDcTab->wType].pUnit1;
		AppNormalDcIn[i].PowerUpIni(AppDcInBoard,ptDcTab->byName,ptDcTab->byPinName,i,*pUnitTem);
		ptDcTab++;
	}
	AppNormalDcJZ.PowerUpIni(AppDcInBoard,g_tDCTab[EN_DC_V11].byName,g_tDCTab[EN_DC_V11].byPinName,i,*(ptCTypeTab[g_tDCTab[EN_DC_V11].wType].pUnit1));
	// 2.2�⹦������忨��ʼ��
#if(CN_DEV_CPU1)
	// �˴����⴦��:����⹦������FPGA�ɼ�����
	ptBoardDcTab =&g_tBoardDCTab[EN_BOARD_DC_OPT1_1];
	SmartBoard[0].PowerUpIni(ptBoardDcTab->byName,ptBoardDcTab->byPinName,ptBoardDcTab->wAddrBoard,(CN_NUM_DC_OPT1)>>2);
	ptBoardDcTab =&g_tBoardDCTab[EN_BOARD_DC_OPT1_2];
	SmartBoard[1].PowerUpIni(ptBoardDcTab->byName,ptBoardDcTab->byPinName,ptBoardDcTab->wAddrBoard,0);
#elif(CN_DEV_CPU2)
	ptBoardDcTab =&g_tBoardDCTab[EN_BOARD_DC_OPT2];
	SmartBoard[0].PowerUpIni(ptBoardDcTab->byName,ptBoardDcTab->byPinName,ptBoardDcTab->wAddrBoard,(ptBoardDcTab->wSrcIndexNum)>>2);
#endif
	// 3.GOOSE�����źų�ʼ��
	// 3.1GOOSE֡
	GoInFrame.PowerUpIni("GOOSE����֡", "GOOSESUB", 0, 255);
	// 3.2GOOSE���ƿ�
	GoInCB[0].PowerUpIni("GOOSE���Ŀ��ƿ�0", "GOCBPUB0", GoInFrame, 255);
	GoInCB[1].PowerUpIni("GOOSE���Ŀ��ƿ�1", "GOCBPUB1", GoInFrame, 255);
	GoInCB[2].PowerUpIni("GOOSE���Ŀ��ƿ�2", "GOCBPUB2", GoInFrame, 255);
	GoInCB[3].PowerUpIni("GOOSE���Ŀ��ƿ�3", "GOCBPUB3", GoInFrame, 255);
	GoInCB[4].PowerUpIni("GOOSE���Ŀ��ƿ�4", "GOCBPUB4", GoInFrame, 255);
	GoInCB[5].PowerUpIni("GOOSE���Ŀ��ƿ�5", "GOCBPUB5", GoInFrame, 255);
	GoInCB[6].PowerUpIni("GOOSE���Ŀ��ƿ�6", "GOCBPUB6", GoInFrame, 255);
	GoInCB[7].PowerUpIni("GOOSE���Ŀ��ƿ�7", "GOCBPUB7", GoInFrame, 255);
	GoInCB[8].PowerUpIni("GOOSE���Ŀ��ƿ�8", "GOCBPUB8", GoInFrame, 255);
	GoInCB[9].PowerUpIni("GOOSE���Ŀ��ƿ�9", "GOCBPUB9", GoInFrame, 255);
	GoInCB[10].PowerUpIni("GOOSE���Ŀ��ƿ�10", "GOCBPUB10", GoInFrame, 255);
	GoInCB[11].PowerUpIni("GOOSE���Ŀ��ƿ�11", "GOCBPUB11", GoInFrame, 255);
	// 3.3GOOSE�����ź�
	ptGoInTab	 =&g_tGoInTab[EN_GOIN_S_STR];
	for(i=0,j=EN_GOIN_S_STR;i<CN_NUM_GOIN_S;i++,j++)
	{
		GoPosIn[i].PowerUpIni(ptGoInTab->byName,  ptGoInTab->byPinName,  GoInFrame,  j);
		ptGoInTab++;
	}
}
void AppStateInCfgRef()
{
	WORD  i;
	BYTE  j;
	BYTE  *pbyGoInSub,*pbyGoInGoCb;
	WORD  *pwAppId,*pwGoInQ;
	DWORD *pdwGoInSubStatus;
	// ���ƿ������־����
	pdwGoInSubStatus= g_tagIO.dwGoInSubStatus;
	for(i=0;i<CN_NUM_GOCB_SUB;i++)
	{
		if(GoInCB[i].CfgErr())
		{
			pdwGoInSubStatus[i]|=CN_SVCFG_CfgErr;
		}
		if(GoInCB[i].ParseErr())
		{
			pdwGoInSubStatus[i]|=CN_SVCFG_ParseErr;
		}
	}
	pbyGoInSub  = &g_tagIO.byGoInSub[EN_GOIN_S_STR];
	pbyGoInGoCb = &g_tagIO.byGoInGoCb[EN_GOIN_S_STR];
	pwAppId     = &g_tagIO.wGoInAppId[EN_GOIN_S_STR];
	pwGoInQ     = &g_tagIO.wGoInQ[EN_GOIN_S_STR];

	for(i=0;i<CN_NUM_GOIN_S;i++)
	{
		// ����GOOSE���ƿ���
		*pbyGoInGoCb=0xFF;
		if(GoPosIn[i].GoCb()!=NULL)
		{
			for(j=0;j<CN_NUM_GOCB_SUB;j++)
			{
				if(GoPosIn[i].GoCb()==&GoInCB[j])
				{
					*pbyGoInGoCb=j;
					// APPID ��ȡ
					if (GoInCB[j].GoCbInfo() != NULL)
					{
						*pwAppId = GoInCB[j].GoCbInfo()->connect.addr.appId;
					}
					break;
				}
			}
		}
		if(GoPosIn[i].IsVLinked()&&(*pbyGoInGoCb==0xFF))
		{
			g_iInter[EN_INTER_GOSUB_GOCB]=TRUE;
		}
		if(GoPosIn[i].IsVLinked())
		{
			*pbyGoInSub=TRUE;
			g_iInter[EN_INTER_GOSUB_V]=TRUE;
		}
		else
		{
			pwGoInQ[i]|=CN_GOIN_NoSub;
		}
		if(GoPosIn[i].IsTLinked())
		{
			g_iInter[EN_INTER_GOSUB_T]=TRUE;
		}
		if(GoPosIn[i].IsQLinked())
		{
			g_iInter[EN_INTER_GOSUB_Q]=TRUE;
		}
		if((!GoPosIn[i].IsVLinked())&&(GoPosIn[i].IsQLinked()||(GoPosIn[i].IsTLinked())))
		{
			g_iInter[EN_INTER_GOSUB_Dif]=TRUE;
		}
		pbyGoInGoCb++;
		pbyGoInSub++;
		pwAppId++;
		// ����GOOSE��������
	}
}
void AppStateInDiRef()
{
	register UINT32 i;
	// Ӳ������ؾֲ�����
	register ApiBoardNormalStateIn *pStateBoardIn;
	register DWORD       *pdwDIIn,*pdwBoardCnt;
	register tagTimeUTC  *ptDIInUTC;
	static  uint32 Temp=0;
	
	SalDateStamp  tStamp;
	// Ӳ����״̬��ʱ��ˢ��
	pdwDIIn 	 =g_tagIO.dwDIIn;
	ptDIInUTC	 =g_tagIO.tDIInUTC;
	pdwBoardCnt  =g_tagIO.dwDIBoardCnt;
	pStateBoardIn=NormalStateBoardIn;

	for(i=0;i<CN_NUM_BOARD_DI_DI;i++,ptDIInUTC++,pStateBoardIn++,pdwBoardCnt++)
	{
		if(G_Sys_Div(CN_NUM_BOARD_DI,i))
		{
			// ��ʱ���� 4�ж�У��һ��
			if((pStateBoardIn->CheckStatus()->recvFrameOkCnt==*pdwBoardCnt)
			||(pStateBoardIn->CheckStatus()->checkStatus1&CN_DO_CHK_PARA))
			{
				G_Set_ChkIn(EN_CHK_BOARD_DI_STR+i);
				*pdwBoardCnt=pStateBoardIn->CheckStatus()->recvFrameOkCnt;
			}
			else
			{
				G_Clr_ChkIn(EN_CHK_BOARD_DI_STR+i);
				*pdwBoardCnt=pStateBoardIn->CheckStatus()->recvFrameOkCnt;
			}
		}
		
		if(pStateBoardIn->StateNum()!=g_tagIO.dwDICnt[i])
		{
			pdwDIIn[i]=pStateBoardIn->Bit32(0);
			tStamp=pStateBoardIn->Stamp();
			ptDIInUTC->dwUSecond_L  =tStamp.usL;
			ptDIInUTC->dwUSecond_H  =tStamp.usH;
			ptDIInUTC->dwLeapSecFlg =tStamp.q.q;
			g_tagIO.dwDICnt[i]=pStateBoardIn->StateNum();
		}
	}
	if (++Temp >= 10000)
	{
		g_tagIO.dwDIIn[0] = ~g_tagIO.dwDIIn[0];
		Temp = 0;
	}
	
}

void AppStateInGoRef()
{
	register UINT32 i;
	// GOOSE������ؾֲ�����
	register ApiGoInCb     *pApiGoInCb;
	register ApiGoPosIn    *pGoPosIn;
	register tagTimeUTC    *ptGoInUTC;
	register BOOL          *pbGoIn,*pbGoInXor,bTemp;
	register WORD          *pwGoInQ;
	register UINT32        *pdwGoInStatusA, *pdwGoInStatusB;
	SalDateStamp  tStamp;
		
	if(g_tagIO.dwGoInCnt!=GoInFrame.PosFrameNum())
	{
		// FPGA�ṩ��GOOSE����ʱ�̵�ʱ�꣬��ʱ��ͬ������ʹ�ã��˴���ʱ��ʹ�ã�ʱ��ͬ������ʹ�ñ���ʱ���׼ȷ
		// liuzhili �޸� 2022-1-11
		//ptGoInUTC   = &g_tagIO.tGoInUTCRev;
		//tStamp      = GoInFrame.FrameStamp();
		//ptGoInUTC->dwUSecond_L =tStamp.usL;
		//ptGoInUTC->dwUSecond_H =tStamp.usH;
		//ptGoInUTC->dwLeapSecFlg=tStamp.q.q;
		
		pGoPosIn    = GoPosIn;
		pbGoIn      = g_tagIO.bGoIn;
		pbGoInXor   = g_tagIO.bGoInXor;
		pwGoInQ     = g_tagIO.wGoInQ;
		ptGoInUTC	= g_tagIO.tGoInUTC;
		for(i=0;i<CN_NUM_GOIN_S;i++,pGoPosIn++)
		{
			if(pGoPosIn->IsVLinked())
			{
				bTemp=pGoPosIn->Value();
				pbGoInXor[i]=pbGoIn[i]^bTemp;
				pbGoIn[i]   = bTemp;
				pwGoInQ[i]  = pGoPosIn->Q();
				if (pGoPosIn->IsTLinked())
				{
					tStamp = pGoPosIn->Stamp();
					ptGoInUTC[i].dwUSecond_L = tStamp.usL;
					ptGoInUTC[i].dwUSecond_H = tStamp.usH;
					ptGoInUTC[i].dwLeapSecFlg= tStamp.q.q;
				}
			}
		}
		g_tagIO.dwGoInCnt=GoInFrame.PosFrameNum();
	}
	// ����GOOSE����״̬
	pdwGoInStatusA = g_tagIO.dwGoInStatusA;
	pdwGoInStatusB = g_tagIO.dwGoInStatusB;
	pApiGoInCb     = GoInCB;
	for(i=0;i<CN_NUM_GOCB_SUB;i++,pApiGoInCb++)
	{
		pdwGoInStatusA[i]=pApiGoInCb->StateA();
		pdwGoInStatusB[i]=pApiGoInCb->StateB();
	}
}
// ��ֵ����0.5%�����̣����ݶ���������32767*0.005=163
// liuzhili add 20220305
#define   CN_DC_SAM_MK   (-163)

void AppStateInDcRef()
{
	register UINT32          i,dwChgFlag=0;
	register INT16           iDcSam;
	register ApiNormalDcIn   *pAppNormalDcIn;
	register INT32           *piDCIn;
	register tagDCSamIn      *ptDCSamIn;
	// ֱ������ˢ��
	if((AppDcInBoard.CheckStatus()->recvFrameOkCnt==g_tagDC.dwDCBoardCnt[EN_BOARD_DC_SAM])
	||(AppDcInBoard.CheckStatus()->checkStatus1&CN_DO_CHK_PARA))
	{
		G_Set_ChkIn(EN_CHK_BOARD_DC_SAM);
#if 0		
		LogMsg<<"DCCnt"<<AppDcInBoard.CheckStatus()->recvFrameCnt
		<<"   "<<g_tagDC.dwDCBoardCnt[EN_BOARD_DC_SAM] \
		<<"   "<<AppDcInBoard.CheckStatus()->cmmOk \
		<<"   "<<AppDcInBoard.CheckStatus()->cmmRecvTypeOk \
		<<"   "<<AppDcInBoard.CheckStatus()->powerCmmCfgIniOk \
		<<"\n";
#endif
		g_tagDC.dwDCBoardCnt[EN_BOARD_DC_SAM]=AppDcInBoard.CheckStatus()->recvFrameOkCnt;
	}
	else
	{
		G_Clr_ChkIn(EN_CHK_BOARD_DC_SAM);
		g_tagDC.dwDCBoardCnt[EN_BOARD_DC_SAM]=AppDcInBoard.CheckStatus()->recvFrameOkCnt;
	}
	
	if(AppDcInBoard.StateNum()!=g_tagDC.dwDCRefCnt[EN_BOARD_DC_SAM])
	{
		pAppNormalDcIn=&AppNormalDcIn[0];
		piDCIn        =&g_tagDC.iDCIn[0];
		ptDCSamIn     =&g_tagDC.tDCSamIn[0];
		for(i=EN_DC_SAM_STR;i<EN_DC_SAM_END;i++,ptDCSamIn++)
		{
			if(ptDCSamIn->wDCPtr>=10)
			{
				if(ptDCSamIn->wDCCnt>2)
				{
					piDCIn[i]=(ptDCSamIn->iDCBuf-ptDCSamIn->iDCMax-ptDCSamIn->iDCMin)/(ptDCSamIn->wDCCnt-2);
					dwChgFlag=1;
				}
				ptDCSamIn->iDCBuf=0;
				ptDCSamIn->iDCMax=CN_DC_SAM_MK;
				ptDCSamIn->iDCMin=32767;
				ptDCSamIn->wDCPtr=0;
				ptDCSamIn->wDCCnt=0;
				piDCIn[EN_DC_V11] = (INT32)(AppNormalDcJZ.Value()*0.1526);
				piDCIn[EN_DC_T3]  = AppDcInBoard.Temperature()*10;
			}
			else
			{
				iDcSam=(INT16)pAppNormalDcIn[i].Value();
				if(iDcSam>=CN_DC_SAM_MK)
				{
					if(iDcSam>ptDCSamIn->iDCMax){ptDCSamIn->iDCMax=iDcSam;}
					if(iDcSam<ptDCSamIn->iDCMin){ptDCSamIn->iDCMin=iDcSam;}
					ptDCSamIn->wDCCnt++;
					ptDCSamIn->iDCBuf+=iDcSam;
				}
				ptDCSamIn->wDCPtr++;
			}
		}
		g_tagDC.dwDCRefCnt[EN_BOARD_DC_SAM]=AppDcInBoard.StateNum();
		// ������ˢ�±�־
		if(dwChgFlag)
		{
			g_tagDC.wDCRefPtr[EN_BOARD_DC_SAM]=0;
			g_tagDC.bDCFresh[EN_BOARD_DC_SAM]=TRUE;
		}
	}

}
void AppStateInOpt1Ref()
{
	register UINT32 i;
	register INT32  *piDCIn;
		// �⹦��
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
	
	ApiSmartBoardInfo  *pSmartBoard=&SmartBoard[0];
#if(CN_DEV_CPU1)
	if(pSmartBoard->StateNum()!=g_tagDC.dwDCRefCnt[EN_BOARD_DC_OPT1_1])
	{
		piDCIn=&g_tagDC.iDCIn[EN_DC_OPT1_1_STR];
		for(i=0;i<(CN_NUM_DC_OPT1_1>>2);i++)
		{
			*piDCIn++=pSmartBoard->NetState(i)->LightR.i16;
			*piDCIn++=pSmartBoard->NetState(i)->LightT.i16;
			*piDCIn++=pSmartBoard->NetState(i)->Temperature.i16;
			*piDCIn++=pSmartBoard->NetState(i)->Voltage.i16;
		}
		g_tagDC.iDCIn[EN_DC_FPGA_CLK1_1]=pSmartBoard->FpgaClkPps();
		g_tagDC.wDCRefPtr[EN_BOARD_DC_OPT1_1]=0;
		g_tagDC.dwDCRefCnt[EN_BOARD_DC_OPT1_1]=pSmartBoard->StateNum();
		// ������ˢ�±�־
		g_tagDC.bDCFresh[EN_BOARD_DC_OPT1_1]=TRUE;
	}
#elif(CN_DEV_CPU2)
	if(pSmartBoard->StateNum()!=g_tagDC.dwDCRefCnt[EN_BOARD_DC_OPT2])
	{
		piDCIn=&g_tagDC.iDCIn[EN_DC_OPT2_STR];
		for(i=0;i<(CN_NUM_DC_OPT2>>2);i++)
		{
            *piDCIn++=pSmartBoard->NetState(i)->LightR.i16;
            *piDCIn++=pSmartBoard->NetState(i)->LightT.i16;
            *piDCIn++=pSmartBoard->NetState(i)->Temperature.i16;
            *piDCIn++=pSmartBoard->NetState(i)->Voltage.i16;
		}
		g_tagDC.iDCIn[EN_DC_FPGA_CLK2]=pSmartBoard->FpgaClkPps();
		g_tagDC.wDCRefPtr[EN_BOARD_DC_OPT2]=0;
		g_tagDC.dwDCRefCnt[EN_BOARD_DC_OPT2]=pSmartBoard->StateNum();
		// ������ˢ�±�־
		g_tagDC.bDCFresh[EN_BOARD_DC_OPT2]=TRUE;
		g_tagDC.bDCCommFresh[EN_BOARD_DC_OPT2]=TRUE;
	}
#endif
}	
void AppStateInOpt1_2Ref()
{
#if(CN_DEV_CPU1)
	register UINT32 i,j;
	register INT32  *piDCIn;
	register ApiSmartBoardInfo  *pSmartBoard=&SmartBoard[0];
	static   uint32 recvFrameOkCnt=0;

	if(recvFrameOkCnt!=pSmartBoard->CheckStatus()->recvFrameOkCnt)
	{
		recvFrameOkCnt=pSmartBoard->CheckStatus()->recvFrameOkCnt;
		G_Clr_ChkIn(EN_CHK_BOARD_CPU_AUX);
	}
	else
	{
		G_Set_ChkIn(EN_CHK_BOARD_CPU_AUX);
	}
	
	if(pSmartBoard->StateNum()!=g_tagDC.dwDCRefCnt[EN_BOARD_DC_OPT1_2])
	{
		piDCIn=&g_tagDC.iDCIn[EN_DC_OPT1_2_STR];
		j=(CN_NUM_DC_OPT1_1>>2);
		for(i=0;i<(CN_NUM_DC_OPT1_2>>2);j++,i++)
		{
			*piDCIn++=pSmartBoard->NetState(j)->LightR.i16;
			*piDCIn++=pSmartBoard->NetState(j)->LightT.i16;
			*piDCIn++=pSmartBoard->NetState(j)->Temperature.i16;
			*piDCIn++=pSmartBoard->NetState(j)->Voltage.i16;
		}
		g_tagDC.iDCIn[EN_DC_FPGA_CLK1_2]=pSmartBoard->FpgaClkPps();
		g_tagDC.wDCRefPtr[EN_BOARD_DC_OPT1_2]=0;
		g_tagDC.dwDCRefCnt[EN_BOARD_DC_OPT1_2]=pSmartBoard->StateNum();
		// ������ˢ�±�־
		g_tagDC.bDCFresh[EN_BOARD_DC_OPT1_2]=TRUE;
	}
#endif
}
void AppStateInRef()
{
	AppStateInDiRef();
	AppStateInGoRef();
	// 32us
	if(G_Sys_Div(128,4))
	AppStateInDcRef();
	// 1024usˢ��һ��
	else if(G_Sys_Div8192_000)
	AppStateInOpt1Ref();
	// 1024usˢ��һ��
	else if(G_Sys_Div8192_256)
	AppStateInOpt1_2Ref();
}

