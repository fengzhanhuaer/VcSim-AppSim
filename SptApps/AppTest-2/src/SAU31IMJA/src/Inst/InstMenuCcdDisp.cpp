#include"InstResource.h"

uint16 wPageTemp;

#if(CN_DEV_CPU1)
int32 UpdateCcdSvSubTextWnd(class HmiTextWnd& Wnd, uint16 Page, uint16 TotalPage, HmiKey key)
{
	if(Page>=CN_NUM_BOARD_SV)
	{
		return 0;
	}
	SVcbInfo *pSVcbInfo=VirSvBoard[Page].SvCbInfo();
	if(pSVcbInfo ==NULL)
	{
		return 0;
	}
	
	uint8* pbyMac;
	uint8 byCard = EN_CARD_CPU1;
	uint8  byPortMax=g_tCardTab[byCard].byPortNum;
	
	String500B str;
	str.Clear();
	str << "IEDName:" << pSVcbInfo->connect.iedName;
	pbyMac=pSVcbInfo->connect.addr.DstMac;
	str << "  MAC:";
	str.FormatHex(pbyMac[0]);
	str << "-";
	str.FormatHex(pbyMac[1]);
	str << "-";
	str.FormatHex(pbyMac[2]);
	str << "-";
	str.FormatHex(pbyMac[3]);
	str << "-";
	str.FormatHex(pbyMac[4]);
	str << "-";
	str.FormatHex(pbyMac[5]);
	str  <<"  APPID:";
	str.FormatHex(pSVcbInfo->connect.addr.appId);
	str << "\n";
	str <<"cbRef:"<<pSVcbInfo->control.cbRef<<"\n";
	str <<"smvID:"<<pSVcbInfo->control.smvID<<"\n";
	str <<"datSetRef:"<<pSVcbInfo->control.datSetRef<<"\n";
	str <<"通信状态字:";
	str.FormatHex(g_tagAna.dwSvCbStatus[Page]);
	str <<"\n";
	str << "订阅端口:";
	if(pSVcbInfo->connect.PortEnableNum<=sizeof(pSVcbInfo->connect.Card_Port))
	{
		for(uint8 i=0,j=0;i<pSVcbInfo->connect.PortEnableNum;i++)
		{
			if(pSVcbInfo->connect.PortEnable[i])
			{
				uint8 byCardTem =pSVcbInfo->connect.Card_Port[i]>>8;
				uint8 byPortTem =pSVcbInfo->connect.Card_Port[i]&0xff;
				if((byCardTem!=byCard)||(byPortTem>byPortMax))
				{
					continue;
				}
				str << g_tCardTab[byCard].pPortName[byPortTem]<<"/";
				if (j++ >= 7)
				{j = 0;	str << "\n";}
			}
		}
	}
	Wnd.SetPage(Page, str.Str());
	return 0;
}

bool8 DispCcdSvSub(ApiMenu* Menu)
{
	if(g_tagAna.bySvCbSubNum==0)
	{
		return 1;
	}

	ApiHmiTextWnd wnd(HmiTextWnd::E_SinglePage, UpdateCcdSvSubTextWnd);
	wnd.SetTitle(Menu->Name(), g_tagAna.bySvCbSubNum);
	wnd.Show();
	return 1;
}
#endif
int32 UpdateCcdSvPubDatWnd(class HmiTextWnd& Wnd, uint16 Page, uint16 TotalPage, HmiKey key)
{
	WORD       *pwSvPubSend,*pwSvPubCfg,i,j,k;
	WORD        wIndex1,wIndex2,wIndex3;
	BOOL        bPol,bCal;
	DWORD      *pdwAnaQ;
	tagVector  *ptAnaVectFst;
	
	pdwAnaQ      =&g_tagAna.dwAnaQ[0];
	ptAnaVectFst =&g_tagAna.tAnaVectFst[0];
	pwSvPubSend  =&g_tagAna.wSvPubSend[0];
	pwSvPubCfg   =&g_tagAna.wSvPubCfg[0];
	String500B str;
	uint32 pageEnd = Min(TotalPage, Page + 11);
	// 展示额定延时通道
	if(G_Get_Inter(EN_INTER_SVPUB_DLY))
	{
		j=0;
	}
	else
	{
		j=1;
	}
	
	str.Clear();
	str.Format("序号"   ,    5  ,1,' ');
	str.Format("名称"   ,    20 ,1,' ');
	str.Format("一次值" ,    8  ,1,' ');	
	str.Format("相位"   ,    8  ,1,' ');
	str.Format("品质"   ,    6  ,1,' ');
	str.Format("极性"   ,    6  ,1,' ');
	str<<"\n";
	for (i = Page; i < pageEnd; i++)
	{
		str.Format(i, 5, 0, 1, ' ');
		// 展示额定延时
		if((i==0)&&(j))
		{
			str.Format("额定延时",20,1,' ');
			#if(CN_DEV_CPU1)
				if(G_Get_Inter(EN_INTER_SVSUB_NOPUB))
				{
					str<<CN_SVPUB_TIME;
				}
				else
				{
					str<<CN_SVPUB_TIME_LINK;
				}
			#endif
			#if(CN_DEV_CPU2)
				if(!G_Get_Inter(EN_INTER_SVPUB_SUB))
				{
					str<<CN_SVPUB_TIME;
				}
				else
				{
					str<<CN_SVPUB_TIME_LINK;
				}
			#endif
		}
		else
		{
			k=i-j;
			if(k<g_tagAna.wSvPubDatNum)
			{
				wIndex1=(pwSvPubSend[k])&CN_SV_Pub_Index1;
				wIndex2=((pwSvPubSend[k])&CN_SV_Pub_Index2)>>7;
				bPol=(pwSvPubSend[k]&CN_SV_Pub_Pol)?TRUE:FALSE;
				bCal=(pwSvPubSend[k]&CN_SV_Pub_Cal)?TRUE:FALSE;
				// 计算通道
				if(bCal)
				{
					wIndex3=pwSvPubCfg[k]&CN_SV_Pub_Index1;
					if(wIndex3<CN_NUM_ANA)
					{
						str.Format(g_tAnaTab[wIndex3].byName,20,1,' ');
						str<<"合成通道1"<<wIndex1;
						str<<"   合成通道2"<<wIndex2;
					}
				}
				// 非计算通道
				else if(wIndex1<CN_NUM_ANA)
				{
					str.Format(g_tAnaTab[wIndex1].byName,20,1,' ');
					str.Format(ptAnaVectFst[wIndex1].dwAm, 8, 3,1, ' ');
					str.Format(ptAnaVectFst[wIndex1].dwAngleRel, 8, 3,1, ' ');
					str.FormatHex((UINT16)pdwAnaQ[wIndex1]);
				}
				// 极性
				if(bPol)
				{
					str.Format("   -",6,1,' ');
				}
				else
				{
					str.Format("   +",6,1,' ');
				}
			}
		}
		str<<"\n";
		Wnd.SetPage(i, str.Str());
		str.Clear();
	}
	return 0;
}


int32 UpdateCcdSvPubTextWnd(class HmiTextWnd& Wnd, uint16 Page, uint16 TotalPage, HmiKey key)
{
	if (Page >= CN_NUM_BOARD_SV)
	{
		return 0;
	}
	SVcbInfo* pSVcbInfo = virSvSendDateSet.SvCbInfo();
	if (pSVcbInfo == NULL)
	{
		return 0;
	}
	// 进入详细信息
	if ((key.Key1 == EK1_ASSIC) && (key.Key2 == ' '))
	{	
		ApiHmiTextWnd wnd1(HmiTextWnd::E_ScrollPage, UpdateCcdSvPubDatWnd);
		wnd1.SetTitle("DatSet", pSVcbInfo->dataElementNum);
		wnd1.Show();
	}
	uint8* pbyMac;
	uint8  byCard = CN_BOARD_CPU;
	uint8  byPortMax=g_tCardTab[byCard].byPortNum;
	String500B str;
	str.Clear();
	str << "IEDName:" << pSVcbInfo->connect.iedName;
	pbyMac = pSVcbInfo->connect.addr.DstMac;
	str << "  MAC:";
	str.FormatHex(pbyMac[0]);
	str << "-";
	str.FormatHex(pbyMac[1]);
	str << "-";
	str.FormatHex(pbyMac[2]);
	str << "-";
	str.FormatHex(pbyMac[3]);
	str << "-";
	str.FormatHex(pbyMac[4]);
	str << "-";
	str.FormatHex(pbyMac[5]);
	str << "  APPID:";
	str.FormatHex(pSVcbInfo->connect.addr.appId);
	str << "\n";
	str << "cbRef:" << pSVcbInfo->control.cbRef << "\n";
	str << "smvID:" << pSVcbInfo->control.smvID << "\n";
	str << "datSetRef:" << pSVcbInfo->control.datSetRef << "\n";
	str << "发布端口:"; 
	if (pSVcbInfo->connect.PortEnableNum <=sizeof(pSVcbInfo->connect.Card_Port))
	{
		for (uint8 i = 0,j=0;i <pSVcbInfo->connect.PortEnableNum;i++)
		{
			if (pSVcbInfo->connect.PortEnable[i])
			{
				uint8 byCardTem =pSVcbInfo->connect.Card_Port[i]>>8;
				uint8 byPortTem =pSVcbInfo->connect.Card_Port[i]&0xff;
				if((byCardTem!=byCard)||(byPortTem>byPortMax))
				{
					continue;
				}
				str << g_tCardTab[byCard].pPortName[byPortTem]<<"/";
				if (j++ >= 7)
				{j = 0;str << "\n";}
			}
		}
	}
	Wnd.SetPage(Page, str.Str());
	return 0;
}

bool8 DispCcdSvPub(ApiMenu* Menu)
{
	if(g_tagAna.bySvCbPubNum==0)
	{
		return 1;
	}

	ApiHmiTextWnd wnd(HmiTextWnd::E_SinglePage, UpdateCcdSvPubTextWnd);
	wnd.SetTitle(Menu->Name(), g_tagAna.bySvCbPubNum);
	wnd.Show();
	return 1;
}
int32 UpdateCcdGooseSubTextWnd(class HmiTextWnd& Wnd, uint16 Page, uint16 TotalPage, HmiKey key)
{
	
	if (Page >= CN_NUM_GOCB_SUB)
	{return 0;}
	GooseGocbInfo* pGoCbInfo = GoInCB[Page].GoCbInfo();
	if (pGoCbInfo == NULL)
	{return 0;}
	
	uint8* pbyMac;
	uint8 byCard = CN_BOARD_CPU;
	uint8  byPortMax=g_tCardTab[byCard].byPortNum;
	
	String500B str;
	str.Clear();
	str << "IEDName:" << pGoCbInfo->connect.iedName;
	pbyMac = pGoCbInfo->connect.addr.DstMac;
	str << " MAC:";
	str.FormatHex(pbyMac[0]);
	str << "-";
	str.FormatHex(pbyMac[1]);
	str << "-";
	str.FormatHex(pbyMac[2]);
	str << "-";
	str.FormatHex(pbyMac[3]);
	str << "-";
	str.FormatHex(pbyMac[4]);
	str << "-";
	str.FormatHex(pbyMac[5]);
	str << " APPID:";
	str.FormatHex(pGoCbInfo->connect.addr.appId);
	str << "\n";
	str << "cbRef:" << pGoCbInfo->control.cbRef << "\n";
	str << "appID:" << pGoCbInfo->control.appID << "\n";
	str << "datSetRef:" << pGoCbInfo->control.datSetRef << "\n";
	uint8 i = 0,j=0,byBnEna=FALSE;
	// 判断B网有没有使能
	if(pGoCbInfo->connect.PortEnableNum<=sizeof(pGoCbInfo->connect.BPortEnable))
	{
		for(i = 0;i < pGoCbInfo->connect.PortEnableNum;i++)
		{
			if(pGoCbInfo->connect.BPortEnable[i])
			{byBnEna=TRUE;break;}
		}
	}

	if(byBnEna)
	{
		str << "单双网模式:双网模式" << "\n";
		str << "A网通信状态字:";
		str.FormatHex(g_tagIO.dwGoInStatusA[Page]);
		str << "\n";
		str << "B网通信状态字:";
		str.FormatHex(g_tagIO.dwGoInStatusB[Page]);
		if (pGoCbInfo->connect.PortEnableNum <=sizeof(pGoCbInfo->connect.ACard_Port))
		{
			str << "A网订阅端口:";
			for (i = 0,j=0;i <pGoCbInfo->connect.PortEnableNum;i++)
			{
				if (pGoCbInfo->connect.APortEnable[i])
				{
					uint8 byCardTem =pGoCbInfo->connect.ACard_Port[i]>>8;
					uint8 byPortTem =pGoCbInfo->connect.ACard_Port[i]&0xff;
					if((byCardTem!=byCard)||(byPortTem>byPortMax))
					{
						continue;
					}
					
					str << g_tCardTab[byCard].pPortName[byPortTem]<<"/";
					if (j++ >= 7){j = 0;str << "\n";}
				}
			}
			str << "B网订阅端口:";
			for (i = 0,j=0;i <pGoCbInfo->connect.PortEnableNum;i++)
			{
				if (pGoCbInfo->connect.BPortEnable[i])
				{
					uint8 byCardTem =pGoCbInfo->connect.BCard_Port[i]>>8;
					uint8 byPortTem =pGoCbInfo->connect.BCard_Port[i]&0xff;
					if((byCardTem!=byCard)||(byPortTem>byPortMax))
					{
						continue;
					}
					str << g_tCardTab[byCard].pPortName[byPortTem]<<"/";
					if (j++ >= 7){j = 0;str << "\n";}
				}
			}
		}
	}
	else
	{
		str << "单双网模式:单网模式" << "\n";;
		str << "通信状态字:";
		str.FormatHex(g_tagIO.dwGoInStatusA[Page]);
		str << "\n";
		str << "订阅端口:";
		if (pGoCbInfo->connect.PortEnableNum <=sizeof(pGoCbInfo->connect.ACard_Port))
		{
			for (i = 0,j=0;i < pGoCbInfo->connect.PortEnableNum;i++)
			{
				if (pGoCbInfo->connect.APortEnable[i])
				{
					uint8 byCardTem =pGoCbInfo->connect.ACard_Port[i]>>8;
					uint8 byPortTem =pGoCbInfo->connect.ACard_Port[i]&0xff;
					if((byCardTem!=byCard)||(byPortTem>byPortMax))
					{
						continue;
					}
					
					str << g_tCardTab[byCard].pPortName[byPortTem]<<"/";
					if (j++ >= 7){j = 0;str << "\n";}
				}
			}
		}
	}
	Wnd.SetPage(Page, str.Str());
	return 0;
}

bool8 DispCcdGooseSub(ApiMenu* Menu)
{
	if(g_tagIO.byGoCbSubNum==0)
	{
		return 1;
	}

	ApiHmiTextWnd wnd(HmiTextWnd::E_SinglePage, UpdateCcdGooseSubTextWnd);
	wnd.SetTitle(Menu->Name(), g_tagIO.byGoCbSubNum);
	wnd.Show();
	return 1;
}
int32 UpdateCcdGoosePubDatWnd(class HmiTextWnd& Wnd, uint16 Page, uint16 TotalPage, HmiKey key)
{
	if (wPageTemp >= CN_NUM_GOCB_PUB)
	{return 0;}
	GooseGocbInfo* pGoCbInfo = GoDataSetOut[wPageTemp].GoCbInfo();
	if (pGoCbInfo == NULL)
	{return 0;}
	String500B str;
	uint32 pageEnd = Min(TotalPage, Page + 11);
	SptGooseFrameOut* input = (SptGooseFrameOut*)(&GoOutFrame[0]);
	HalIoCell* cell;
	SptGooseDataOut* scell;
	str.Clear();
	str.Format("序号"   ,    6  ,1,' ');
	str.Format("名称"   ,    20 ,1,' ');
	str.Format("类型" ,      5  ,1,' ');
	str.Format("数值"   ,    5  ,1,' ');
	str<<"\n";

	for (uint16 i = Page; i < pageEnd; i++)
	{
		str.Format(i, 4, 0, 1, ' ');
		if((pGoCbInfo->dataLinkedNum[i])&&(pGoCbInfo->dataInstId[i][0] != 0xffff)&&(input!=NULL))
		{
			cell = input->GetIoCell(pGoCbInfo->dataInstId[i][0]);
			scell=(SptGooseDataOut*)cell;
			if(scell!=NULL)
			{
				str.Format(scell->Name(),22,1,' ');
				
				SalDateStamp stampTemp=scell->Value().stamp;
				
				switch(pGoCbInfo->dataType[i])
				{
					case spt::GoSvDataType::E_GOSV_BOOL:
						str.Format("单点"  ,    5  ,1,' ');
						str<<scell->Value().value.bl;
						break;
					case spt::GoSvDataType::E_GOSV_DPOS:
						str.Format("双点"  ,    5  ,1,' ');
						str<<(bool8)(scell->Value().value.u8>>1)<<(bool8)(scell->Value().value.u8&1);
						break;
					case spt::GoSvDataType::E_GOSV_Q:
						str.Format("品质"  ,    5  ,1,' ');
						str.FormatHex(scell->Value().q);
						break;
					case spt::GoSvDataType::E_GOSV_INT32:
						str.Format("整形"  ,    5  ,1,' ');
						str<<scell->Value().value.i32;
						break;
					case spt::GoSvDataType::E_GOSV_UINT32:
						str.Format("整形"  ,    5  ,1,' ');
						str<<scell->Value().value.u32;
						break;
					case spt::GoSvDataType::E_GOSV_FLOAT32:
						str.Format("浮点"  ,    5  ,1,' ');
						str.Format(scell->Value().value.i32,3);
						break;
					case spt::GoSvDataType::E_GOSV_TIMSSTAMP:
						str.Format("时标"  ,    5  ,1,' ');
						stampTemp.ToStrHzFmt2(str);
						break;
					default:
						break;
				}
			}
		}
		str<<"\n";
		Wnd.SetPage(i, str.Str());
		str.Clear();
	}
	return 0;
}
int32 UpdateCcdGoosePubTextWnd(class HmiTextWnd& Wnd, uint16 Page, uint16 TotalPage, HmiKey key)
{
	if (Page >= CN_NUM_GOCB_PUB)
	{return 0;}
	GooseGocbInfo* pGoCbInfo = GoDataSetOut[Page].GoCbInfo();
	if (pGoCbInfo == NULL)
	{return 0;}
	// 进入详细信息
	if ((key.Key1 == EK1_ASSIC) && (key.Key2 == ' '))
	{	wPageTemp=Page;
		ApiHmiTextWnd wnd1(HmiTextWnd::E_ScrollPage, UpdateCcdGoosePubDatWnd);
		wnd1.SetTitle("DatSet", pGoCbInfo->dataElementNum);
		wnd1.Show();
	}
	uint8* pbyMac;
	uint8  byCard = CN_BOARD_CPU;
	uint8  byPortMax=g_tCardTab[byCard].byPortNum;
	String500B str;
	str.Clear();
	str << "IEDName:" << pGoCbInfo->connect.iedName;
	pbyMac = pGoCbInfo->connect.addr.DstMac;
	str << "  MAC:";
	str.FormatHex(pbyMac[0]);
	str << "-";
	str.FormatHex(pbyMac[1]);
	str << "-";
	str.FormatHex(pbyMac[2]);
	str << "-";
	str.FormatHex(pbyMac[3]);
	str << "-";
	str.FormatHex(pbyMac[4]);
	str << "-";
	str.FormatHex(pbyMac[5]);
	str << "  APPID:";
	str.FormatHex(pGoCbInfo->connect.addr.appId);
	str << "\n";
	str << "cbRef:" << pGoCbInfo->control.cbRef << "\n";
	str << "appID:" << pGoCbInfo->control.appID << "\n";
	str << "datSetRef:" << pGoCbInfo->control.datSetRef << "\n";
	str << "发布端口:";
	if (pGoCbInfo->connect.PortEnableNum<=sizeof(pGoCbInfo->connect.ACard_Port))
	{
		for (uint8 i = 0, j = 0;i < pGoCbInfo->connect.PortEnableNum;i++)
		{
			if (pGoCbInfo->connect.APortEnable[i])
			{
				uint8 byCardTem =pGoCbInfo->connect.ACard_Port[i]>>8;
				uint8 byPortTem =pGoCbInfo->connect.ACard_Port[i]&0xff;
				if((byCardTem!=byCard)||(byPortTem>byPortMax))
				{
					continue;
				}
				str << g_tCardTab[byCard].pPortName[byPortTem]<<"/";
				if (j++ >= 7){j = 0;str << "\n";}
			}
		}
	}
	Wnd.SetPage(Page, str.Str());
	
	return 0;
}

bool8 DispCcdGoosePub(ApiMenu* Menu)
{
	if(g_tagIO.byGoCbPubNum==0)
	{
		return 1;
	}
	ApiHmiTextWnd wnd(HmiTextWnd::E_SinglePage, UpdateCcdGoosePubTextWnd);
	wnd.SetTitle(Menu->Name(), g_tagIO.byGoCbPubNum);
	wnd.Show();
	return 1;
}
#if 0
// FPGA配置返校信号由平台维护
int32 UpdateCcdToFPGAWnd(class HmiTextWnd& Wnd, uint16 Page, uint16 TotalPage, HmiKey key)
{
	if(Page>=M_ArrLen(SmartBoard))
	{return 0;}
	
	ApiSmartBoardInfo   *pSmartBoard=&SmartBoard[Page];

	String500B str;
	str.Clear();
	str << "插件"<<Page<<"配置下装状态"<<"\n";
	str << "配置下装状态        :";
	str.FormatHex((uint16)(pSmartBoard->SvRecCfgRecState(0)));
	str <<"\n";
	str << "SVCB订阅下装状态    :";
	str.FormatHex((uint16)(pSmartBoard->SvRecCfgRecState(0)));
	str <<"\n";
	str << "SVCB发布下装状态    :";
	str.FormatHex((uint16)(pSmartBoard->SvRecCfgRecState(0)));
	str <<"\n";
	str << "GOCB订阅参数下装状态:";
	str.FormatHex((uint8)(pSmartBoard->GoRecCfgRecState(0,4)));
	str.FormatHex((uint32)(pSmartBoard->GoRecCfgRecState(0,0)));
	str <<"\n";
	str << "GOCB订阅类型下装状态:";
	str.FormatHex((uint8)(pSmartBoard->GoRecCfgRecState(0,4)));
	str.FormatHex((uint32)(pSmartBoard->GoRecCfgRecState(0,0)));
	str <<"\n";
	str << "GOCB订阅映射下装状态:";
	str.FormatHex((uint16)(pSmartBoard->GoRecCfgRecState(0,0)));
	str <<"\n";
	Wnd.SetPage(Page, str.Str());
	return 0;
}

bool8 DispCcdToFPGA(ApiMenu* Menu)
{
	if(M_ArrLen(SmartBoard)==0)
	{
		return 1;
	}
	ApiHmiTextWnd wnd(HmiTextWnd::E_SinglePage, UpdateCcdToFPGAWnd);
	wnd.SetTitle(Menu->Name(), M_ArrLen(SmartBoard));
	wnd.Show();
	return 1;
}
#endif

