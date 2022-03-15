#include "InstResource.h"
bool8 DispEthnetPara(ApiMenu* Menu)
{
	ApiHmiTextWnd wnd(HmiTextWnd::E_SinglePage, 0);
	String1000B str;
	str.Clear();
	tagDevEthnet  *ptDevEthnet;
	u4bytes  u4bytesTem;
	// ��ϸ��Ϣ
	str << "��CPU���������"<<"\n";
	ptDevEthnet=  &g_tDevInfor.tDevEthnet;
	u4bytesTem.u32=ptDevEthnet->dwIp;
	str << "IP��ַ  :"<<u4bytesTem.u8[0]<<"."<<u4bytesTem.u8[1]<<"."<<u4bytesTem.u8[2]<<"."<<u4bytesTem.u8[3]<<"\n";
	u4bytesTem.u32=ptDevEthnet->dwMask;
	str << "��������:"<<u4bytesTem.u8[0]<<"."<<u4bytesTem.u8[1]<<"."<<u4bytesTem.u8[2]<<"."<<u4bytesTem.u8[3]<<"\n";
	u4bytesTem.u32=ptDevEthnet->dwGate;
	str << "����    :"<<u4bytesTem.u8[0]<<"."<<u4bytesTem.u8[1]<<"."<<u4bytesTem.u8[2]<<"."<<u4bytesTem.u8[3]<<"\n";
	str << "��־��  :";
	str.FormatHex(ptDevEthnet->dwFlag);
	str <<"\n";

	str << "��һCPU���������"<<"\n";
	ptDevEthnet=  &g_tDevInfor.tDevEthnetOth;
	u4bytesTem.u32=ptDevEthnet->dwIp;
	str << "IP��ַ  :"<<u4bytesTem.u8[0]<<"."<<u4bytesTem.u8[1]<<"."<<u4bytesTem.u8[2]<<"."<<u4bytesTem.u8[3]<<"\n";
	u4bytesTem.u32=ptDevEthnet->dwMask;
	str << "��������:"<<u4bytesTem.u8[0]<<"."<<u4bytesTem.u8[1]<<"."<<u4bytesTem.u8[2]<<"."<<u4bytesTem.u8[3]<<"\n";
	u4bytesTem.u32=ptDevEthnet->dwGate;
	str << "����    :"<<u4bytesTem.u8[0]<<"."<<u4bytesTem.u8[1]<<"."<<u4bytesTem.u8[2]<<"."<<u4bytesTem.u8[3]<<"\n";
	str << "��־��  :";
	str.FormatHex(ptDevEthnet->dwFlag);
	str <<"\n";
	wnd.SetPage(0, str.Str());
	wnd.SetTitle("�������", 1);
	wnd.Show();
	return 1;
}

bool8 EditEthnetPara(ApiMenu* Menu)
{
	ApiSysEthNetCfg& UsrCfg = ApiSysEthNetCfg::Instance();
	ApiHmiGridWnd wnd(0);
	wnd.SetInfo("���Կڲ���(Flag:Bit0-Ftp Bit1-Telnet)", 0, 0);
	HmiGridWndDataMapRow* row;
	UsrCfg.ValueToEditBuf();
	row = wnd.CreatRow();
	row->SetCfgData(&UsrCfg.EthNet[0].ip);
	row = wnd.CreatRow();
	row->SetCfgData(&UsrCfg.EthNet[0].musk);
	row = wnd.CreatRow();
	row->SetCfgData(&UsrCfg.EthNet[0].gate);
	row = wnd.CreatRow();
	row->SetCfgData(&UsrCfg.EthNet[0].mac);
	row = wnd.CreatRow();
	row->SetCfgData(&UsrCfg.EthNet[0].exInfo);
	wnd.Edit();
	if (wnd.IsDataChange())
	{
		ApiSelectDialog dig("�������޸��Ƿ񱣴�?", 0, 0, 0, 0);
		if (dig.Show() == 0)
		{
			if(LcdOperationConfirmationAccountInfo(Menu)==0)
			{
				return 0;
			}
			UsrCfg.EditBufToValue();

			if (UsrCfg.SaveAll() > 0)
			{
				ApiWarnDialog dig1("��������ɹ�!", 0, 0, 0, 0);
				dig1.Show();
				
				AppEventPrvtOptRef(EN_PRVT_OPT_ETH_W_SUCC);
				// �����������
				AppEthNetParaRef();
				//if(LogInUsr)
				//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "�����洢�ɹ�", 0, 0, 0);
			}
			else
			{
				ApiWarnDialog dig1("��������ʧ��!", 0, 0, 0, 0);
				dig1.Show();
				
				AppEventPrvtOptRef(EN_PRVT_OPT_ETH_W_FAIL);
				
				//if(LogInUsr)
				//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "�����洢ʧ��", 0, 0, 0);
			}
		}
	}
	return 1;
}
bool8 MakeParaSetMenu(ApiMenu* Menu, ApiHmiGridWnd& wnd, SalParaEditGroup* ParaGroup, bool8 Edit)
{
	uint32 dataNum = ParaGroup->CurEditCellNum();
	st64value* pvalue;
	uint8 col = 1;
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalParaEditCell* para = ParaGroup->EditCell(i);
		if (para)
		{
			SalPara* des = para->Des();
			if (!des->Disp())
			{
				continue;
			}
			col = 1;
			struct HmiGridWndDataMapRow* row = wnd.CreatRow();
			row->SetName(des->Name());
			//��ֵ
			pvalue = row->GetDataSur(col);
			pvalue->value.vptr = para;
			row->SetColData(col, Edit, para, 16);
			col++;
			row->SetColDataCfg(col, 0, E_SVT_STR | E_SVT_PTR, 5, 0);
			row->SetColStrData(col, des->Unit(), 0);
			col++;
		}
		else
		{
			break;
		}
	}
	return 1;
}
// �Լ����
bool8 ChkProtSet(ApiMenu* Menu,uint16 wIndex,uint16 wFlag)
{
	if(G_Get_ChkOut(EN_CHK_PARA_STR+wIndex))
	{
		ApiSelectDialog sd("�����쳣","�Ƿ��ʼ���ò�����", 0, 0, 0);
		int32 res = sd.Show();
		if (res == 0)
		{
			if(wFlag==1)
			{
				if(LcdOperationConfirmationAccountInfo(Menu)==0)
				{
					return 0;
				}
			}
			if(AppParaDefault(wIndex)!=0)
			{
				ApiWarnDialog dig2("������ʼ��ʧ��!",0, 0, 0, 0);
				dig2.Show();
				return 0;
			}
			ApiWarnDialog dig2("������ʼ���ɹ�!",0, 0, 0, 0);
			dig2.Show();
		}
		else
		{
			return 0;
		}
	}
	return 1;
}


bool8 DispProtSet(ApiMenu* Menu,uint16 wIndex)
{
	if(wIndex>=CN_NUM_BOARD_PARA)
	{
		return 0;
	}
	//if(ChkProtSet(Menu,wIndex,1)==0)
	//{
	//	return 0;
	//}
	ApiHmiGridWnd wnd(0);
	HmiParaEditGroup.Set((SalParaGroup*)&ProtParaGroup[wIndex], 0);
	wnd.SetInfo(g_tBoardParaTab[wIndex].byName, ProtParaGroup[wIndex].GetCrc(0), 2);
	MakeParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
	wnd.Show();
	return 1;
}

bool8 DispProtSetDI(ApiMenu* Menu)
{
	DispProtSet(Menu,EN_BOARD_PARA_DI);
	return 1;
}
bool8 DispProtSetDC(ApiMenu* Menu)
{
	DispProtSet(Menu,EN_BOARD_PARA_DC);
	return 1;
}
bool8 DispProtSetSam(ApiMenu* Menu)
{
	DispProtSet(Menu,EN_BOARD_PARA_SAM);
	return 1;
}
bool8 DispProtSetFun(ApiMenu* Menu)
{
	DispProtSet(Menu,EN_BOARD_PARA_FUN);
	return 1;
}
bool8 DispProtSetDcCoe(ApiMenu* Menu)
{
	DispProtSet(Menu,EN_BOARD_PARA_DC_COE);
	return 1;
}

bool8 DispProtSetAmCoe(ApiMenu* Menu)
{
	DispProtSet(Menu,EN_BOARD_PARA_AM_COE);
	return 1;
}
bool8 DispProtSetDcBcCoe(ApiMenu* Menu)
{
	DispProtSet(Menu,EN_BOARD_PARA_DCBC_COE);
	return 1;
}
bool8 DispProtSetAngCoe(ApiMenu* Menu)
{
	DispProtSet(Menu,EN_BOARD_PARA_ANG_COE);
	return 1;
}
bool8 EditProtSet(ApiMenu* Menu,uint16 wIndex)
{
	BYTE byPowOff=FALSE;
	if(wIndex>=CN_NUM_BOARD_PARA)
	{
		return 0;
	}
	if(ChkProtSet(Menu,wIndex,1)==0)
	{
		return 0;
	}
	ApiHmiGridWnd wnd(0);
	wnd.SetInfo(g_tBoardParaTab[wIndex].byName, 0, 0);
	HmiParaEditGroup.Set((SalParaGroup*)&ProtParaGroup[wIndex], 0);
	MakeParaSetMenu(Menu, wnd, &HmiParaEditGroup, 1);
	wnd.Edit();
	if (wnd.IsDataChange())
	{
		ApiSelectDialog dig("�������޸��Ƿ񱣴�?", 0, 0, 0, 0);

		if (dig.Show() == 0)
		{
			if(LcdOperationConfirmationAccountInfo(Menu)==0)
			{
				return 1;
			}
			// �ϵ��������
			WORD *pCfg=g_tagPara.wParaCfg;
			for(WORD i=g_tBoardParaTab[wIndex].wIndexStr;i<g_tBoardParaTab[wIndex].wIndexEnd;i++)
			{
				if(pCfg[i]&DB0)
				{
					SalPara*para          = (SalPara*)&ProtPara[i];
					SalParaEditCell*epara = HmiParaEditGroup.EditCell(para->InstId());
					if(epara&& epara->Des() &&( *epara->Buf()!=epara->Des()->Int32()))
					{
						byPowOff=TRUE;
					}
				}
			}
			
			if (HmiParaEditGroup.SavePara() == 0)
			{
				if (AppSendPara2SubBoard(&ProtParaGroup[wIndex], 0) == 0)
				{
					if(byPowOff)
					{
						ApiWarnDialog dig1("��������ɹ�!","����װ����Ч!", 0, 0, 0);
	                    dig1.Show();
					}
					else
					{
						ApiWarnDialog dig1("��������ɹ�!",0, 0, 0, 0);
	                    dig1.Show();
					}

					AppEventOptRef(EN_OPT_PARA_W_SUCC_STR+wIndex);
					//if(LogInUsr)
					//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "�û����ù���", "���óɹ�",g_tBoardParaTab[wIndex].byName, 0, 0);
				}
				else
				{
					if(byPowOff)
					{
						ApiWarnDialog dig1("�����������ɹ�!", "����װ����Ч!", "��һ���������ʧ��!", 0, 0);
	                    dig1.Show();
					}
					else
					{
						ApiWarnDialog dig1("�����������ɹ�!", "��һ���������ʧ��!", 0, 0, 0);
	                    dig1.Show();
					}
					AppEventOptRef(EN_OPT_PARA_W_FAIL_STR+wIndex);
					//if(LogInUsr)
					//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "�û����ù���", "����ʧ��",g_tBoardParaTab[wIndex].byName, 0, 0);
					
				}
			}
			else
			{
				ApiWarnDialog dig1("��������ʧ��!", 0, 0, 0, 0);
				dig1.Show();
				AppEventOptRef(EN_OPT_PARA_W_FAIL_STR+wIndex);
				//if(LogInUsr)
				//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "�û����ù���", "����ʧ��", g_tBoardParaTab[wIndex].byName, 0, 0);
			}
		}
	}
	return 1;
}

bool8 EditProtSetDI(ApiMenu* Menu)
{
	EditProtSet(Menu,EN_BOARD_PARA_DI);
	return 1;
}
bool8 EditProtSetDC(ApiMenu* Menu)
{
	EditProtSet(Menu,EN_BOARD_PARA_DC);
	return 1;
}
bool8 EditProtSetSam(ApiMenu* Menu)
{
	EditProtSet(Menu,EN_BOARD_PARA_SAM);
	return 1;
}
bool8 EditProtSetFun(ApiMenu* Menu)
{
	EditProtSet(Menu,EN_BOARD_PARA_FUN);
	return 1;
}

bool8 EditProtSetDcCoe(ApiMenu* Menu)
{
	EditProtSet(Menu,EN_BOARD_PARA_DC_COE);
	return 1;
}


bool8 EditProtSetAmCoe(ApiMenu* Menu)
{
	EditProtSet(Menu,EN_BOARD_PARA_AM_COE);
	return 1;
}

bool8 EditProtSetDcBcCoe(ApiMenu* Menu)
{
	EditProtSet(Menu,EN_BOARD_PARA_DCBC_COE);
	return 1;
}

bool8 EditProtSetAngCoe(ApiMenu* Menu)
{
	EditProtSet(Menu,EN_BOARD_PARA_ANG_COE);
	return 1;
}


static int32 HmiViewAnaUpdate(class HmiGridWnd* Wnd, struct HmiGridWndDataMap* Map, HmiKey Key)
{
	// ��������
	if(g_iInter[EN_INTER_OPT_ANA])
	{
		if(AppDispAnaAmRef())
		{
			return 0;
		}
	}
	if(g_iInter[EN_INTER_OPT_ANA_J])
	{
		if(AppDispAnaAmjRef())
		{
			return 0;
		}
	}

	uint32 dataNum = HmiParaEditGroup.CurEditCellNum();
	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiDispAnaGroup;
	st64value* pvalue;
	uint8 col = 1;
	uint32 rown = 0;
	uint32 bufIndex = anmsGroup->GetNewestDataIndex();
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalParaEditCell* para = HmiParaEditGroup.EditCell(i);
		if (para)
		{
			SalPara* des = para->Des();
			if (!des->Disp())
			{
				continue;
			}
			col = 1;
			SalAngRms* rms = anmsGroup->Cell((uint32)des->ExInfo1().value.i32);
			if (rms)
			{
				if (!rms->IsDisp())
				{
					continue;
				}
				col = 1;
				struct HmiGridWndDataMapRow* row = &Map->row[rown++];
				const i32AngRms* rmsValue = anmsGroup->GetRealData(bufIndex, rms->InstId());
				pvalue = row->GetDataEdit(col);
				pvalue->value.i32 = rmsValue->data1;//����ֵ
				col++;
				col++;
				pvalue = row->GetDataEdit(col);
				pvalue->value.i32 = rmsValue->data2;//�Ƕ�
				col++;
				//�����ڴ˴�����У׼���㣬ͨ��������ʽ�޸�У׼���ֵ	
				//HmiParaEditGroup.EditCell(0)->Buf()[0] = 0.01;
				//HmiParaEditGroup.EditCell(1)->Buf()[0] = 0.01;
				//HmiParaEditGroup.EditCell(2)->Buf()[0] = 0.01;
			}
			else
			{
				break;
			}
		}
	}
	return 0;
}
bool8 MakeAnaParaSetMenu(ApiMenu* Menu, ApiHmiGridWnd& wnd, SalParaEditGroup* ParaGroup, bool8 Edit)
{
	uint32 dataNum = ParaGroup->CurEditCellNum();
	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiDispAnaGroup;
	st64value* pvalue;
	uint8 col = 1;
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalParaEditCell* para = ParaGroup->EditCell(i);
		if (para)
		{
			SalPara* des = para->Des();
			if (!des->Disp())
			{
				continue;
			}
			col = 1;
			struct HmiGridWndDataMapRow* row = wnd.CreatRow();
			row->SetName(des->Name());
			SalAngRms* rms = anmsGroup->Cell((uint32)des->ExInfo1().value.i32);
			if (rms)
			{
				//����ֵ
				row->SetColDataCfg(col, 0, E_SVT_I32 | E_SVT_PTR, 9, rms->Data1DotNum());
				pvalue = row->GetDataSur(col);
				pvalue->value.vptr = rms;
				pvalue = row->GetDataEdit(col);
				row->SetColData(col, &pvalue->value.i32);
				col++;
				row->SetColDataCfg(col, 0, E_SVT_STR | E_SVT_PTR, 2, 0);
				row->SetColStrData(col, rms->Units1() == 0 ? Unit_NULL.toString() : rms->Units1()->toString(), 0);
				col++;
				if (rms->DataNum() == 2)
				{
					//�Ƕ�
					row->SetColDataCfg(col, 0, E_SVT_I32 | E_SVT_PTR, 7, rms->Data2DotNum());
					pvalue = row->GetDataSur(col);
					pvalue->value.vptr = rms;
					pvalue = row->GetDataEdit(col);
					row->SetColData(col, &pvalue->value.i32);
					col++;
					row->SetColDataCfg(col, 0, E_SVT_STR | E_SVT_PTR, 2, 0);
					row->SetColStrData(col, rms->Units2() == 0 ? Unit_NULL.toString() : rms->Units2()->toString(), 0);
					col++;
				}
				else
				{
					col++;
					col++;
				}
			}
			else
			{
				col++;
				col++;
				col++;
				col++;
			}

			//��ֵ
			pvalue = row->GetDataSur(col);
			pvalue->value.vptr = para;
			row->SetColData(col, Edit, para, 16);
			col++;
		}
		else
		{
			break;
		}
	}
	return 1;
}
bool8 EditAnaAmParaSet(ApiMenu* Menu)
{
	if(ChkProtSet(Menu,EN_BOARD_PARA_AM_COE,0)==0)
	{
		return 0;
	}
	
	ApiHmiGridWnd wnd(HmiViewAnaUpdate);
	wnd.SetInfo("��ֵУ׼ϵ��", 0, 0);
	HmiParaEditGroup.Set((SalParaGroup*)&ProtParaGroup[EN_BOARD_PARA_AM_COE], 0);
	MakeAnaParaSetMenu(Menu, wnd, &HmiParaEditGroup, 1);
	wnd.Edit();
	if (wnd.IsDataChange())
	{
		ApiSelectDialog dig("�������޸��Ƿ񱣴�?", 0, 0, 0, 0);
		if (dig.Show() == 0)
		{
			if (HmiParaEditGroup.SavePara() == 0)
			{
				ApiWarnDialog dig1("��������ɹ�!", 0, 0, 0, 0);
				dig1.Show();
				AppEventOptRef(EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_AM_COE);
				//if(LogInUsr)
				//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼�ɹ�", "��ֵУ׼ϵ��", 0, 0);
			}
			else
			{
				ApiWarnDialog dig1("��������ʧ��!", 0, 0, 0, 0);
				dig1.Show();
				AppEventOptRef(EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_AM_COE);
				//if(LogInUsr)
				//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "��ֵУ׼ϵ��", 0, 0);
			}
		}
	}
	return 1;
}
bool8 DispAnaAmParaSet(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd(HmiViewAnaUpdate);
	wnd.SetInfo("��ֵУ׼ϵ��", 0, 0);
	HmiParaEditGroup.Set((SalParaGroup*)&ProtParaGroup[EN_BOARD_PARA_AM_COE], 0);
	MakeAnaParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
	wnd.Show();
	return 1;
}
BOOL bChnAna[CN_NUM_AD];
bool8 AutoAnaAmParaSet(ApiMenu* Menu)
{
	if(ChkProtSet(Menu,EN_BOARD_PARA_AM_COE,0)==0)
	{
		return 0;
	}
	BOOL *pChn=NULL;
	ApiSelectDialog sd("����U=100V I=In f=50Hz","��ֵ�Զ�У׼��", 0, 0, 0);
	int32 res = sd.Show();
	if (res == 0)
	{
		ApiHmiGridWnd wnd(HmiViewAnaUpdate);
		HmiParaEditGroup.Set((SalParaGroup*)&ProtParaGroup[EN_BOARD_PARA_AM_COE], 0);
		wnd.SetInfo("��ֵУ׼ϵ��", 0, 0);
		// �ݶ�100�ܲ�
		if(IES_IMSam_AdJAm_Str(100))
		{
			ApiWarnDialog wd("�Զ�У׼ʧ��", 0, 0, 0, 0);
			wd.Show();
			AppEventOptRef(EN_OPT_ADJ_AM_FAIL);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "��ֵУ׼ϵ��", 0, 0);
			MakeAnaParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
			wnd.Show();
			return 1;
		}
		MsSleep(5000);
		uint32 dwNo =IES_IMSam_AdJAm(bChnAna);
		if (dwNo==0)
		{
			ApiWarnDialog wd("�Զ�У׼ʧ��", 0, 0, 0, 0);
			wd.Show();
			AppEventOptRef(EN_OPT_ADJ_AM_FAIL);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "��ֵУ׼ϵ��", 0, 0);
			MakeAnaParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
			wnd.Show();
			return 1;
		}
		else if(dwNo!=CN_NUM_SAM)
		{
			ApiSelectDialog sd1("������ͨ��У׼�ɹ�","�Ƿ�洢��", 0, 0, 0);
			if (sd1.Show() != 0)
			{
				ApiWarnDialog wd("�Զ�У׼ʧ��", 0, 0, 0, 0);
				wd.Show();
				AppEventOptRef(EN_OPT_ADJ_AM_FAIL);
				//if(LogInUsr)
				//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "��ֵУ׼ϵ��", 0, 0);

				MakeAnaParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
				wnd.Show();
				return 1;
			}
			pChn=bChnAna;
		}
		// ���²���
		if(AppParaCoeEditUpdate(&HmiParaEditGroup,EN_PARA_AM_COE_STR,EN_PARA_AM_COE_STR+CN_NUM_SAM,EN_BOARD_PARA_AM_COE,pChn))
		{
			ApiWarnDialog dig1("��������ʧ��!", 0, 0, 0, 0);
			dig1.Show();
			AppEventOptRef(EN_OPT_ADJ_AM_FAIL);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "��ֵУ׼ϵ��", 0, 0);
		}
		else if (HmiParaEditGroup.SavePara() == 0)
		{
			ApiWarnDialog dig1("�Զ�У׼�ɹ�!", 0, 0, 0, 0);
			dig1.Show();
			AppEventOptRef(EN_OPT_ADJ_AM_SUCC);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼�ɹ�", "��ֵУ׼ϵ��", 0, 0);
		}
		else
		{
			ApiWarnDialog dig1("��������ʧ��!", 0, 0, 0, 0);
			dig1.Show();
			AppEventOptRef(EN_OPT_ADJ_AM_FAIL);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "��ֵУ׼ϵ��", 0, 0);
		}
		MakeAnaParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
		wnd.Show();
	}
	return 1;
}

bool8 EditAnaDcParaSet(ApiMenu* Menu)
{
	if(ChkProtSet(Menu,EN_BOARD_PARA_DCBC_COE,0)==0)
	{
		return 0;
	}

	ApiHmiGridWnd wnd(HmiViewAnaUpdate);
	wnd.SetInfo("ֱ����������", 0, 0);
	HmiParaEditGroup.Set((SalParaGroup*)&ProtParaGroup[EN_BOARD_PARA_DCBC_COE], 0);
	MakeAnaParaSetMenu(Menu, wnd, &HmiParaEditGroup, 1);
	wnd.Edit();
	if (wnd.IsDataChange())
	{
		ApiSelectDialog dig("�������޸��Ƿ񱣴�?", 0, 0, 0, 0);
		if (dig.Show() == 0)
		{
			if (HmiParaEditGroup.SavePara() == 0)
			{
				ApiWarnDialog dig1("��������ɹ�!", 0, 0, 0, 0);
				
				AppEventOptRef(EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_DCBC_COE);
				//if(LogInUsr)
				//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼�ɹ�", "��ֵУ׼ϵ��", 0, 0);
				dig1.Show();
			}
			else
			{
				ApiWarnDialog dig1("��������ʧ��!", 0, 0, 0, 0);
				
				AppEventOptRef(EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_DCBC_COE);
				//if(LogInUsr)
				//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "��ֵУ׼ϵ��", 0, 0);
				dig1.Show();
			}
		}
	}
	return 1;
}

bool8 DispAnaDcParaSet(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd(HmiViewAnaUpdate);
	wnd.SetInfo("ֱ������ϵ��", 0, 0);
	HmiParaEditGroup.Set((SalParaGroup*)&ProtParaGroup[EN_BOARD_PARA_DCBC_COE], 0);
	MakeAnaParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
	wnd.Show();
	return 1;
}
bool8 AutoAnaDcParaSet(ApiMenu* Menu)
{
	if(ChkProtSet(Menu,EN_BOARD_PARA_DCBC_COE,0)==0)
	{
		return 0;
	}

	BOOL *pChn=NULL;
	ApiSelectDialog sd("����U=0V I=0A","ֱ������У׼��", 0, 0, 0);
	int32 res = sd.Show();
	if (res == 0)
	{
		ApiHmiGridWnd wnd(HmiViewAnaUpdate);
		HmiParaEditGroup.Set((SalParaGroup*)&ProtParaGroup[EN_BOARD_PARA_DCBC_COE], 0);
		wnd.SetInfo("ֱ����������", 0, 0);
		// �ݶ�100�ܲ�
		
		if(IES_IMSam_AdJDc_Str(10))
		{
			ApiWarnDialog wd("�Զ�У׼ʧ��", 0, 0, 0, 0);
			wd.Show();
			AppEventOptRef(EN_OPT_ADJ_DCBC_FAIL);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "ֱ����������", 0, 0);
			MakeAnaParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
			wnd.Show();
			return 1;
		}
		MsSleep(5000);
		uint32 dwNo =IES_IMSam_AdJDc(bChnAna);
		if(dwNo==0)
		{
			ApiWarnDialog wd("�Զ�У׼ʧ��", 0, 0, 0, 0);
			wd.Show();
			AppEventOptRef(EN_OPT_ADJ_DCBC_FAIL);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "ֱ����������", 0, 0);
			MakeAnaParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
			wnd.Show();
			return 1;
		}
		else if(dwNo!=CN_NUM_SAM)
		{
			ApiSelectDialog sd1("������ͨ��У׼�ɹ�","�Ƿ�洢��", 0, 0, 0);
			if (sd1.Show() != 0)
			{
				ApiWarnDialog wd("�Զ�У׼ʧ��", 0, 0, 0, 0);
				wd.Show();
				AppEventOptRef(EN_OPT_ADJ_DCBC_FAIL);
				//if(LogInUsr)
				//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "ֱ����������", 0, 0);
				MakeAnaParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
				wnd.Show();
				return 1;
			}
			pChn=bChnAna;
		}
		// ���²���
		if(AppParaCoeEditUpdate(&HmiParaEditGroup,EN_PARA_DCBC_COE_STR,EN_PARA_DCBC_COE_STR+CN_NUM_SAM,EN_BOARD_PARA_DCBC_COE,pChn))
		{
			ApiWarnDialog dig1("��������ʧ��!", 0, 0, 0, 0);
			dig1.Show();
			AppEventOptRef(EN_OPT_ADJ_DCBC_FAIL);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "ֱ����������", 0, 0);
		}
		else if (HmiParaEditGroup.SavePara() == 0)
		{
			ApiWarnDialog dig1("�Զ�У׼�ɹ�!", 0, 0, 0, 0);
			dig1.Show();
			AppEventOptRef(EN_OPT_ADJ_DCBC_SUCC);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼�ɹ�", "ֱ����������", 0, 0);
		}
		else
		{
			ApiWarnDialog dig1("��������ʧ��!", 0, 0, 0, 0);
			dig1.Show();
			AppEventOptRef(EN_OPT_ADJ_DCBC_FAIL);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "ֱ����������", 0, 0);
		}
		MakeAnaParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
		wnd.Show();
	}
	return 1;
}


bool8 EditAnaAngParaSet(ApiMenu* Menu)
{
	if(ChkProtSet(Menu,EN_BOARD_PARA_ANG_COE,0)==0)
	{
		return 0;
	}

	ApiHmiGridWnd wnd(HmiViewAnaUpdate);
	wnd.SetInfo("��λ����ϵ��", 0, 0);
	HmiParaEditGroup.Set((SalParaGroup*)&ProtParaGroup[EN_BOARD_PARA_ANG_COE], 0);
	MakeAnaParaSetMenu(Menu, wnd, &HmiParaEditGroup, 1);
	wnd.Edit();
	if (wnd.IsDataChange())
	{
		ApiSelectDialog dig("�������޸��Ƿ񱣴�?", 0, 0, 0, 0);
		if (dig.Show() == 0)
		{
			if (HmiParaEditGroup.SavePara() == 0)
			{
				ApiWarnDialog dig1("��������ɹ�!", 0, 0, 0, 0);
				dig1.Show();
				AppEventOptRef(EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_ANG_COE);
				//if(LogInUsr)
				//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼�ɹ�", "��λ����ϵ��", 0, 0);
			}
			else
			{
				ApiWarnDialog dig1("��������ʧ��!", 0, 0, 0, 0);
				dig1.Show();
				AppEventOptRef(EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_ANG_COE);
				//if(LogInUsr)
				//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "��λ����ϵ��", 0, 0);
			}
		}
	}
	return 1;
}

bool8 DispAnaAngParaSet(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd(HmiViewAnaUpdate);
	wnd.SetInfo("��λ����ϵ��", 0, 0);
	HmiParaEditGroup.Set((SalParaGroup*)&ProtParaGroup[EN_BOARD_PARA_ANG_COE], 0);
	MakeAnaParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
	wnd.Show();
	return 1;
}
bool8 AutoAnaAngParaSet(ApiMenu* Menu)
{
	if(ChkProtSet(Menu,EN_BOARD_PARA_ANG_COE,0)==0)
	{
		return 0;
	}

	BOOL *pChn=NULL;
	ApiSelectDialog sd("����U=100V I=In f=50Hz Ang=0��","��λ�Զ�У׼��", 0, 0, 0);
	int32 res = sd.Show();
	if (res == 0)
	{
		ApiHmiGridWnd wnd(HmiViewAnaUpdate);
		HmiParaEditGroup.Set((SalParaGroup*)&ProtParaGroup[EN_BOARD_PARA_ANG_COE], 0);
		wnd.SetInfo("��λ��������", 0, 0);
		// �ݶ�100�ܲ�
		
		if(IES_IMSam_AdJAng_Str(100))
		{
			ApiWarnDialog wd("�Զ�У׼ʧ��", 0, 0, 0, 0);
			wd.Show();
			AppEventOptRef(EN_OPT_ADJ_ANG_FAIL);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "��λ����ϵ��", 0, 0);
			MakeAnaParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
			wnd.Show();
			return 1;
		}
		MsSleep(5000);
		uint32 dwNo =IES_IMSam_AdJAng(bChnAna);
		if (dwNo==0)
		{
			ApiWarnDialog wd("�Զ�У׼ʧ��", 0, 0, 0, 0);
			wd.Show();
			AppEventOptRef(EN_OPT_ADJ_ANG_FAIL);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "��λ����ϵ��", 0, 0);
			MakeAnaParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
			wnd.Show();
			return 1;
		}
		if (dwNo!=(CN_NUM_JZ+ CN_NUM_JZ))
		{
			ApiSelectDialog sd1("������ͨ��У׼�ɹ�","�Ƿ�洢��", 0, 0, 0);
			if (sd1.Show() != 0)
			{
				ApiWarnDialog wd("�Զ�У׼ʧ��", 0, 0, 0, 0);
				wd.Show();
				AppEventOptRef(EN_OPT_ADJ_ANG_FAIL);
				//if(LogInUsr)
				//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "��λ����ϵ��", 0, 0);
				MakeAnaParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
				wnd.Show();
				return 1;
			}
			pChn=bChnAna;
		}
		// ���²���
		if(AppParaCoeEditUpdate(&HmiParaEditGroup,EN_PARA_ANG_COE_STR,EN_PARA_ANG_COE_END,EN_BOARD_PARA_ANG_COE,pChn))
		{
			ApiWarnDialog dig1("��������ʧ��!", 0, 0, 0, 0);
			dig1.Show();
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "��λ����ϵ��", 0, 0);
			AppEventOptRef(EN_OPT_ADJ_ANG_FAIL);
		}
		else if (HmiParaEditGroup.SavePara() == 0)
		{
			ApiWarnDialog dig1("�Զ�У׼�ɹ�!", 0, 0, 0, 0);
			dig1.Show();
			AppEventOptRef(EN_OPT_ADJ_ANG_SUCC);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼�ɹ�", "��λ����ϵ��", 0, 0);
		}
		else
		{
			ApiWarnDialog dig1("��������ʧ��!", 0, 0, 0, 0);
			dig1.Show();
			AppEventOptRef(EN_OPT_ADJ_ANG_FAIL);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "��λ����ϵ��", 0, 0);
		}
		MakeAnaParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
		wnd.Show();
	}
	return 1;
}
static int32 HmiViewDcUpdate(class HmiGridWnd* Wnd, struct HmiGridWndDataMap* Map, HmiKey Key)
{
	// ��������
	if(AppDispDcRef())
	{
		return 0;
	}
	uint32 dataNum = HmiParaEditGroup.CurEditCellNum();
	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiDispDcGroup;
	st64value* pvalue;
	uint8 col = 1;
	uint32 rown = 0;
	uint32 bufIndex = anmsGroup->GetNewestDataIndex();
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalParaEditCell* para = HmiParaEditGroup.EditCell(i);
		if (para)
		{
			SalPara* des = para->Des();
			if (!des->Disp())
			{
				continue;
			}
			col = 1;
			SalAngRms* rms = anmsGroup->Cell((uint32)des->ExInfo1().value.i32);
			if (rms)
			{
				if (!rms->IsDisp())
				{
					continue;
				}
				col = 1;
				struct HmiGridWndDataMapRow* row = &Map->row[rown++];
				const i32AngRms* rmsValue = anmsGroup->GetRealData(bufIndex, rms->InstId());
				pvalue = row->GetDataEdit(col);
				pvalue->value.i32 = rmsValue->data1;//ֱ��ֵ
				col++;
				col++;
				pvalue = row->GetDataEdit(col);
				pvalue->value.i32 = rmsValue->data2;//ת��ֵ
				col++;
			}
			else
			{
				break;
			}
		}
	}
	return 0;
}
bool8 MakeDcParaSetMenu(ApiMenu* Menu, ApiHmiGridWnd& wnd, SalParaEditGroup* ParaGroup, bool8 Edit)
{
	uint32 dataNum = ParaGroup->CurEditCellNum();
	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiDispDcGroup;
	st64value* pvalue;
	uint8 col = 1;
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalParaEditCell* para = ParaGroup->EditCell(i);
		if (para)
		{
			SalPara* des = para->Des();
			if (!des->Disp())
			{
				continue;
			}
			col = 1;
			struct HmiGridWndDataMapRow* row = wnd.CreatRow();
			row->SetName(des->Name());
			SalAngRms* rms = anmsGroup->Cell((uint32)des->ExInfo1().value.i32);
			if (rms)
			{
				//ֱ��ֵ
				row->SetColDataCfg(col, 0, E_SVT_I32 | E_SVT_PTR, 9, rms->Data1DotNum());
				pvalue = row->GetDataSur(col);
				pvalue->value.vptr = rms;
				pvalue = row->GetDataEdit(col);
				row->SetColData(col, &pvalue->value.i32);
				col++;
				row->SetColDataCfg(col, 0, E_SVT_STR | E_SVT_PTR, 2, 0);
				row->SetColStrData(col, rms->Units1() == 0 ? Unit_NULL.toString() : rms->Units1()->toString(), 0);
				col++;
				if (rms->DataNum() == 2)
				{
					//ת��
					row->SetColDataCfg(col, 0, E_SVT_I32 | E_SVT_PTR, 7, rms->Data2DotNum());
					pvalue = row->GetDataSur(col);
					pvalue->value.vptr = rms;
					pvalue = row->GetDataEdit(col);
					row->SetColData(col, &pvalue->value.i32);
					col++;
					row->SetColDataCfg(col, 0, E_SVT_STR | E_SVT_PTR, 2, 0);
					row->SetColStrData(col, rms->Units2() == 0 ? Unit_NULL.toString() : rms->Units2()->toString(), 0);
					col++;
				}
				else
				{
					col++;
					col++;
				}
			}
			else
			{
				col++;
				col++;
				col++;
				col++;
			}

			//��ֵ
			pvalue = row->GetDataSur(col);
			pvalue->value.vptr = para;
			row->SetColData(col, Edit, para, 16);
			col++;
		}
		else
		{
			break;
		}
	}
	return 1;
}

bool8 EditDcParaSet(ApiMenu* Menu)
{
	if(ChkProtSet(Menu,EN_BOARD_PARA_DC_COE,0)==0)
	{
		return 0;
	}

	ApiHmiGridWnd wnd(HmiViewDcUpdate);
	wnd.SetInfo("ֱ��У׼ϵ��", 0, 0);
	HmiParaEditGroup.Set((SalParaGroup*)&ProtParaGroup[EN_BOARD_PARA_DC_COE], 0);
	MakeDcParaSetMenu(Menu, wnd, &HmiParaEditGroup, 1);
	wnd.Edit();
	if (wnd.IsDataChange())
	{
		ApiSelectDialog dig("�������޸��Ƿ񱣴�?", 0, 0, 0, 0);
		if (dig.Show() == 0)
		{
			if (HmiParaEditGroup.SavePara() == 0)
			{
				if (AppSendPara2SubBoard(&ProtParaGroup[EN_BOARD_PARA_DC_COE], 0) == 0)
				{
					ApiWarnDialog dig1("��������ɹ�!", 0, 0, 0, 0);
					AppEventOptRef(EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_DC_COE);
					//if(LogInUsr)
					//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼�ɹ�", "ֱ��У׼ϵ��", 0, 0);
					dig1.Show();
				}
				else
				{
					ApiWarnDialog dig1("���������������ɹ�!", "��һ���������ʧ��", 0, 0, 0);
					AppEventOptRef(EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_DC_COE);
					//if(LogInUsr)
					//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼�ɹ�", "����ֱ��У׼ϵ��", 0, 0);
					dig1.Show();
				}
			}
			else
			{
				ApiWarnDialog dig1("��������ʧ��!", 0, 0, 0, 0);
				AppEventOptRef(EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_DC_COE);
				//if(LogInUsr)
				//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "ֱ��У׼ϵ��", 0, 0);
				dig1.Show();
			}
		}
	}
	return 1;
}

bool8 DispDcParaSet(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd(HmiViewDcUpdate);
	wnd.SetInfo("ֱ��У׼ϵ��", 0, 0);
	HmiParaEditGroup.Set((SalParaGroup*)&ProtParaGroup[EN_BOARD_PARA_DC_COE], 0);
	MakeDcParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
	wnd.Show();
	return 1;
}
bool8 AutoDcParaSet(ApiMenu* Menu)
{
	if(ChkProtSet(Menu,EN_BOARD_PARA_DC_COE,0)==0)
	{
		return 0;
	}
	BOOL *pChn=NULL;
	ApiSelectDialog sd("DC���뷽ʽ0~5V   ����DC=5V","ֱ���Զ�У׼��", 0, 0, 0);
	int32 res = sd.Show();
	if (res == 0)
	{
		ApiHmiGridWnd wnd(HmiViewDcUpdate);
		HmiParaEditGroup.Set((SalParaGroup*)&ProtParaGroup[EN_BOARD_PARA_DC_COE], 0);
		wnd.SetInfo("ֱ��У׼ϵ��", 0, 0);
		// �ݶ�100�ܲ�
		if(IES_IMDC_AdJ_Str(20))
		{
			ApiWarnDialog wd("�Զ�У׼ʧ��", 0, 0, 0, 0);
			wd.Show();
			AppEventOptRef(EN_OPT_ADJ_DC_FAIL);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "ֱ��У׼ϵ��", 0, 0);
			MakeDcParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
			wnd.Show();
			return 1;
		}
		MsSleep(10000);
		uint32 dwNo =IES_IMDC_AdJ(bChnAna);
		if (dwNo==0)
		{
			ApiWarnDialog wd("�Զ�У׼ʧ��", 0, 0, 0, 0);
			wd.Show();
			AppEventOptRef(EN_OPT_ADJ_DC_FAIL);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "ֱ��У׼ϵ��", 0, 0);
			MakeDcParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
			wnd.Show();
			return 1;
		}
		else if(dwNo!=CN_NUM_DC_SAM)
		{
			ApiSelectDialog sd1("������ͨ��У׼�ɹ�","�Ƿ�洢��", 0, 0, 0);
			if (sd1.Show() != 0)
			{
				ApiWarnDialog wd("�Զ�У׼ʧ��", 0, 0, 0, 0);
				wd.Show();
				AppEventOptRef(EN_OPT_ADJ_DC_FAIL);
				//if(LogInUsr)
				//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "ֱ��У׼ϵ��", 0, 0);
				MakeDcParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
				wnd.Show();
				return 1;
			}
			pChn=bChnAna;
		}
		// ���²���
		if(AppParaCoeEditUpdate(&HmiParaEditGroup,EN_PARA_DC_COE_STR,EN_PARA_DC_COE_END,EN_BOARD_PARA_DC_COE,pChn))
		{
			ApiWarnDialog dig1("��������ʧ��!", 0, 0, 0, 0);
			dig1.Show();
			AppEventOptRef(EN_OPT_ADJ_DC_FAIL);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "ֱ��У׼ϵ��", 0, 0);
		}
		else if (HmiParaEditGroup.SavePara() == 0)
		{
			if (AppSendPara2SubBoard(&ProtParaGroup[EN_BOARD_PARA_DC_COE], 0) == 0)
			{
				ApiWarnDialog dig1("�Զ�У׼�ɹ�!", 0, 0, 0, 0);
				dig1.Show();
				AppEventOptRef(EN_OPT_ADJ_DC_SUCC);
				//if(LogInUsr)
				//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼�ɹ�", "ֱ��У׼ϵ��", 0, 0);
			}
			else
			{
				ApiWarnDialog dig1("��������ʧ��!", 0, 0, 0, 0);
				dig1.Show();
				AppEventOptRef(EN_OPT_ADJ_DC_FAIL);
				//if(LogInUsr)
				//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "ֱ��У׼ϵ��", 0, 0);
			}
		}
		else
		{
			ApiWarnDialog dig1("��������ʧ��!", 0, 0, 0, 0);
			dig1.Show();
			AppEventOptRef(EN_OPT_ADJ_DC_FAIL);
			//if(LogInUsr)
			//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "У׼ʧ��", "ֱ��У׼ϵ��", 0, 0);
		}
		MakeDcParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
		wnd.Show();
	}
	return 1;
}


