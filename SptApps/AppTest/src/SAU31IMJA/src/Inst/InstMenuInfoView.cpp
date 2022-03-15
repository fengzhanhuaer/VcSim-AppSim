#include"InstResource.h"

// �������� �����������һس�
bool8 ViewPrivateKey(HmiKey key,uint8 byKeyType)
{
	static uint8 KeyCnt[EN_KEY_END];
	if((byKeyType>=g_NUM_KEY)||(byKeyType>=EN_KEY_END))
	{
		return 1;
	}
	
	const uint8 *pbyKey;
	uint8  bykeyNum=g_tKeyTab[byKeyType].byKeyNum;
	pbyKey = &g_tKeyTab[byKeyType].byKey[0];
	if(bykeyNum==0)
	{
		KeyCnt[byKeyType]=0;
		return 0;
	}
	else if((pbyKey==NULL)||(bykeyNum>=CN_KEY_MAX))
	{
		KeyCnt[byKeyType]=0;
		return 1;
	}
	
	if (KeyCnt[byKeyType] == 0)
	{
		if ((key.Key1 == EK1_KEYVALUE) && (key.Key2 == pbyKey[0]))
		{
			KeyCnt[byKeyType]++;
		}
		return 1;
	}
	else if ((key.Key1 == EK1_KEYVALUE)
		&& (key.Key2 == pbyKey[KeyCnt[byKeyType]]))
	{
		KeyCnt[byKeyType]++;
		if(KeyCnt[byKeyType]<bykeyNum)
		{
			return 1;
		}
	}
	else
	{
		KeyCnt[byKeyType] = 0;
		return 1;
	}
	KeyCnt[byKeyType] = 0;
	return 0;
}
bool8 EnterAnaMenu(ApiMenu* Menu)
{
	g_iInter[EN_INTER_OPT_ANA]=TRUE;
	//MsSleep(CN_FACE_TIME);
	return 1;
}

bool8 ExitAnaMenu(ApiMenu* Menu)
{
	g_iInter[EN_INTER_OPT_ANA]=FALSE;
	//MsSleep(CN_FACE_TIME);
	return 1;
}
bool8 EnterAnaJMenu(ApiMenu* Menu)
{
	g_iInter[EN_INTER_OPT_ANA_J]=TRUE;
	//MsSleep(CN_FACE_TIME);
	return 1;
}

bool8 ExitAnaJMenu(ApiMenu* Menu)
{
	g_iInter[EN_INTER_OPT_ANA_J]=FALSE;
	//MsSleep(CN_FACE_TIME);
	return 1;
}
bool8 EnterAnaFrMenu(ApiMenu* Menu)
{
	g_iInter[EN_INTER_OPT_ANA_FR]=TRUE;
	//MsSleep(CN_FACE_TIME);
	return 1;
}

bool8 ExitAnaFrMenu(ApiMenu* Menu)
{
	g_iInter[EN_INTER_OPT_ANA_FR]=FALSE;
	//MsSleep(CN_FACE_TIME);
	return 1;
}
bool8 EnterAnaHumMenu(ApiMenu* Menu)
{
	g_iInter[EN_INTER_OPT_ANA_HUM]=TRUE;
	//MsSleep(CN_FACE_TIME);
	return 1;
}

bool8 ExitAnaHumMenu(ApiMenu* Menu)
{
	g_iInter[EN_INTER_OPT_ANA_HUM]=FALSE;
	//MsSleep(CN_FACE_TIME);
	return 1;
}
bool8 MakeActStatusDispMenu(ApiMenu* Menu, ApiHmiGridWnd& wnd, SalStatusGroup* Group, int32 From, int32 To)
{
	uint32 dataNum = To;
	SalStatus* cell;
	bool8  *pbGoose,*pbDo,*pbDoRet;
	InstObject* obj;
	uint8 col = 1;
	wnd.SetColTitle("GOOSE����", "״̬", "����","��У", "ʱ��", 0, 0, 0, 0, 0);
	pbGoose=g_tActState.bActIn;
	pbDo   =g_tActState.bActOut;
	pbDoRet=g_tActState.bActOutRet;
	for (uint16 i = From; i < dataNum; i++)
	{
		obj = Group->GetObject(i);
		if (obj)
		{
			cell = (SalStatus*)(obj);
			if (!cell->IsDisp())
			{
				continue;
			}
			col = 1;
			struct HmiGridWndDataMapRow* row = wnd.CreatRow();
			row->SetName(cell->Name());
			//GOOSE����״̬��
			row->SetColDataCfg(col, 0, E_SVT_U8 | E_SVT_PTR, 1, 0);
			row->SetColData(col, &pbGoose[i]);
			//����״̬��
			col++;
			row->SetColDataCfg(col, 0, E_SVT_U8 | E_SVT_PTR, 1, 0);
			row->SetColData(col, &pbDo[i]);
			//��У״̬��
			col++;
			row->SetColDataCfg(col, 0, E_SVT_U8 | E_SVT_PTR, 1, 0);
			row->SetColData(col, &pbDoRet[i]);
			col++;
			//״̬����ʱ��
			row->SetColStatusTime(col, cell, 27, 2);
			col++;
		}
		else
		{
			break;
		}
	}
	return 1;
}
bool8 MakeActStatusDispMenu(ApiMenu* Menu, ApiHmiGridWnd& wnd, SalStatusGroup* Group)
{
	return MakeActStatusDispMenu(Menu, wnd, Group, 0, Group->InstNum());
}
bool8 MakeStatusDispMenu(ApiMenu* Menu, ApiHmiGridWnd& wnd, SalStatusGroup* Group, int32 From, int32 To)
{
	uint32 dataNum = To;
	SalStatus* cell;
	InstObject* obj;
	uint8 col = 1;
	for (uint16 i = From; i < dataNum; i++)
	{
		obj = Group->GetObject(i);
		if (obj)
		{
			cell = (SalStatus*)(obj);
			if (!cell->IsDisp())
			{
				continue;
			}
			col = 1;
			struct HmiGridWndDataMapRow* row = wnd.CreatRow();
			row->SetName(cell->Name());
			//״̬��
			row->SetColData(col, cell, 4);
			col++;
			if(cell->Flag().st.isDispUs)
			{
				row->SetColStatusTime(col, cell, 31, 3);
			}
			else
			{
				row->SetColStatusTime(col, cell, 27, 2);
			}
			col++;
			if(cell->Flag().st.isDispQ)
			{
				// ���GOOSE�������⴦��
				row->SetColDataCfg(col, 0, E_SVT_HEX8 | E_SVT_PTR, 2, 0);
				if(Group==(SalStatusGroup*)&AppEventGoInSoeGroup)
				{
					row->SetColData(col, (uint8*)(&g_tagIO.wGoInQ[i]));
				}
				else
				{
					row->SetColData(col, (uint8*)(&cell->Data().q.u32));
				}
				col++;
			}
		}
		else
		{
			break;
		}
	}
	return 1;
}
bool8 MakeStatusDispMenu(ApiMenu* Menu, ApiHmiGridWnd& wnd, SalStatusGroup* Group)
{
	return MakeStatusDispMenu(Menu, wnd, Group, 0, Group->InstNum());
}

bool8 ViewSptWarnStatus(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd;
	wnd.SetInfo(Menu->Name(), 0, 0);
	MakeStatusDispMenu(Menu, wnd, (SalStatusGroup*)&SptStatusGroup);
	wnd.Show();
	return 1;
}

bool8 ViewActStatus(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd;
	wnd.SetInfo(Menu->Name(), 0, 0);
	MakeActStatusDispMenu(Menu, wnd, (SalStatusGroup*)&AppEventActGroup);
	wnd.Show();
	return 1;
}
bool8 ViewWarnStatus(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd;
	wnd.SetInfo(Menu->Name(), 0, 0);
	MakeStatusDispMenu(Menu, wnd, (SalStatusGroup*)&AppEventWarnGroup);
	wnd.Show();
	return 1;

	return 1;
}
bool8 ViewChekStatus(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd;
	wnd.SetInfo(Menu->Name(), 0, 0);
	MakeStatusDispMenu(Menu, wnd, (SalStatusGroup*)&AppEventChekGroup);
	wnd.Show();
	return 1;
}

bool8 ViewDiStatus(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd;
	wnd.SetInfo(Menu->Name(), 0, 0);
	MakeStatusDispMenu(Menu, wnd, (SalStatusGroup*)&AppEventDISoeGroup);
	wnd.Show();
	return 1;
}
bool8 ViewDoStatus(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd;
	wnd.SetInfo(Menu->Name(), 0, 0);
	MakeStatusDispMenu(Menu, wnd, (SalStatusGroup*)&AppEventDOSoeGroup);
	wnd.Show();
	return 1;
}

bool8 ViewGoInStatus(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd;
	wnd.SetInfo(Menu->Name(), 0, 0);
	MakeStatusDispMenu(Menu, wnd, (SalStatusGroup*)&AppEventGoInSoeGroup);
	wnd.Show();
	return 1;
}
bool8 ViewGoOutStatus(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd;
	wnd.SetInfo(Menu->Name(), 0, 0);
	MakeStatusDispMenu(Menu, wnd, (SalStatusGroup*)&AppEventGoOutSoeGroup);
	wnd.Show();
	return 1;
}
bool8 ViewLedStatus(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd;
	wnd.SetInfo(Menu->Name(), 0, 0);
	MakeStatusDispMenu(Menu, wnd, (SalStatusGroup*)&AppEventLedSoeGroup);
	wnd.Show();
	return 1;
}

bool8 ViewFlagStatus(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd;
	wnd.SetInfo(Menu->Name(), 0, 0);
	MakeStatusDispMenu(Menu, wnd, (SalStatusGroup*)&AppEventFlagSoeGroup);
	wnd.Show();
	return 1;
}
bool8 ViewDpiStatus(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd;
	wnd.SetInfo(Menu->Name(), 0, 0);
	MakeStatusDispMenu(Menu, wnd, (SalStatusGroup*)&AppEventDpiSoeGroup);
	wnd.Show();
	return 1;
}
bool8 ViewWarnDetailedStatus(ApiMenu* Menu)
{
	return 1;
}
//void UpdateOtherChipVersion()
//{
//	ApiVersionInfo::Instance().OtherChipVersion(0).SetName("Fpga1");
//	ApiVersionInfo::Instance().OtherChipVersion(0).ProgVersion = 100;
//	ApiVersionInfo::Instance().OtherChipVersion(0).ProgDate = 0x20210112;
//	ApiVersionInfo::Instance().OtherChipVersion(0).ProgCrc = 0x32164589;
//}
int32 ViewPrivateVersion(class HmiTextWnd& Wnd, uint16 Page1, uint16 TotalPage, HmiKey key)
{
	if (!ViewPrivateKey(key,EN_KEY_DBG))
	{
		int32 res;
		if(MenuDispDbgDisp)
		{
		    ApiSelectDialog sd("����ģʽ�˳�?", 0, 0, 0,0);
			res = sd.Show();
		}
		else
		{
		    ApiSelectDialog sd("����ģʽʹ��?", 0, 0, 0,0);
			res = sd.Show();
		}
		if (res == 0)
		{
			MenuDispDbgDisp=!MenuDispDbgDisp;
			MenuDispDbgIn=FALSE;
		}
	}
	if (ViewPrivateKey(key,EN_KEY_VER))
	{
		return 0;
	}
	//UpdateOtherChipVersion();
	ApiVersionInfo::Instance().Print();
	ApiHmiTextWnd wnd(HmiTextWnd::E_SinglePage, 0);
	uint32 page = 0;
	String1000B str;
	str.Clear();
    uint8 monthH,monthL,dayH,dayL;
    SalRtc date;
	// ��ϸ��Ϣ
	str << "CPU��Ӧ�ó���汾 :"<<CN_SOFT_VER_CPU_NAME<<"\n";
#if(CN_SOFT_VER_CPU==CN_SOFT_CPU_TEST)
	str << "���԰汾״̬�� :";
	str.FormatHex((UINT16)CN_SOFT_CPU_TEST_CFG);
	str <<"\n";
#endif
	str << "CPU��Ӳ���汾     :"<<CN_HARDWARE_MCPU_NAME<<"\n";
	str << "CPU����Ӳ���汾   :"<<CN_HARDWARE_MCPU_AUX_NAME<<"\n";
	str << "PTCT1��Ӳ���汾   :"<<CN_HARDWARE_PTCT1_NAME<<"\n";
	str << "PTCT2��Ӳ���汾   :"<<CN_HARDWARE_PTCT2_NAME<<"\n";
	str << "DC��Ӳ���汾      :"<<CN_HARDWARE_DC_NAME<<"\n";
	str << "DO��Ӳ���汾      :"<<CN_HARDWARE_DO_NAME<<"\n";
	str << "DIO��Ӳ���汾     :"<<CN_HARDWARE_DIO_NAME<<"\n";
	str << "OPB��Ӳ���汾     :"<<CN_HARDWARE_OPB_NAME<<"\n";
	str << "DI��Ӳ���汾      :"<<CN_HARDWARE_DI_NAME<<"\n";
	str << "MB��Ӳ���汾      :"<<CN_HARDWARE_MB_NAME<<"\n";
	wnd.SetPage(page++, str.Str());
	// APP�汾��Ϣ
	str.Clear();
	SptVersion* SptVersionTem=&(ApiVersionInfo::Instance().AppVersion());
	str << "APP      VER:"<<SptVersionTem->major<<"."<<SptVersionTem->minor<<SptVersionTem->reversion;
	date.FromStamp(SptVersionTem->datetimeus);
	monthH=date.month/10;
	monthL=date.month%10;
	dayH  =date.day/10;
	dayL  =date.day%10;
	str << " DAT:"<<date.year<<monthH<<monthL<<dayH<<dayL;
	str << " CRC:";
	str.FormatHex((UINT16)SptVersionTem->crc);
	str << "\n";
	// API�汾��Ϣ
	const SptVersion* SptApiVersionTem=&(ApiVersionInfo::Instance().ApiVersion());
	str << "API      VER:"<<SptApiVersionTem->major<<"."<<SptApiVersionTem->minor<<"."<<SptApiVersionTem->reversion;
	date.FromStamp(SptApiVersionTem->datetimeus);
	monthH=date.month/10;
	monthL=date.month%10;
	dayH  =date.day/10;
	dayL  =date.day%10;
	str << " DAT:"<<date.year<<monthH<<monthL<<dayH<<dayL<<".";
	str.Format((uint32)date.hour,2,0,0,'0');
	str.Format((uint32)date.minute,2,0,0,'0');
	str.Format((uint32)date.second,2,0,0,'0');
	str << "\n";
#if defined(SYLIX_GZK)
	// Boot0�汾��Ϣ
	SptVersionTem=&(ApiVersionInfo::Instance().Boot0Version());
	str << "Boot0    VER:"<<SptVersionTem->major<<"."<<SptVersionTem->minor<<SptVersionTem->reversion;
    date.FromStamp(SptVersionTem->datetimeus);
    monthH=date.month/10;
    monthL=date.month%10;
    dayH  =date.day/10;
    dayL  =date.day%10;
    str << " DAT:"<<date.year<<monthH<<monthL<<dayH<<dayL;
    str << " CRC:";
    str.FormatHex((UINT16)SptVersionTem->crc);
	str << "\n";
	// UBoot�汾��Ϣ
	SptVersionTem=&(ApiVersionInfo::Instance().UbootVersion());
	str << "Uboot    VER:"<<SptVersionTem->major<<"."<<SptVersionTem->minor<<SptVersionTem->reversion;
    date.FromStamp(SptVersionTem->datetimeus);
    monthH=date.month/10;
    monthL=date.month%10;
    dayH  =date.day/10;
    dayL  =date.day%10;
    str << " DAT:"<<date.year<<monthH<<monthL<<dayH<<dayL;
    str << " CRC:";
    str.FormatHex((UINT16)SptVersionTem->crc);
	str << "\n";
	// ϵͳ�汾��Ϣ
	SptVersionTem=&(ApiVersionInfo::Instance().MainSysVersion());
	str << "Sys      VER:"<<SptVersionTem->major<<"."<<SptVersionTem->minor<<SptVersionTem->reversion;
    date.FromStamp(SptVersionTem->datetimeus);
    monthH=date.month/10;
    monthL=date.month%10;
    dayH  =date.day/10;
    dayL  =date.day%10;
    str << " DAT:"<<date.year<<monthH<<monthL<<dayH<<dayL;
    str << " CRC:";
    str.FormatHex((UINT16)SptVersionTem->crc);
	str << "\n";
	// ϵͳ���ݰ汾��Ϣ
	SptVersionTem=&(ApiVersionInfo::Instance().BakSysVersion());
	str << "SysBak   VER:"<<SptVersionTem->major<<"."<<SptVersionTem->minor<<SptVersionTem->reversion;
    date.FromStamp(SptVersionTem->datetimeus);
    monthH=date.month/10;
    monthL=date.month%10;
    dayH  =date.day/10;
    dayL  =date.day%10;
    str << " DAT:"<<date.year<<monthH<<monthL<<dayH<<dayL;
    str << " CRC:";
    str.FormatHex((UINT16)SptVersionTem->crc);
	str << "\n";
	// FPGA1�汾��Ϣ
	str << "FPGA1:";
	if(SmartBoard[0].RunState(0)==0xAAAA)
	{
		str << "OK";
	}
	else if(SmartBoard[0].RunState(0)==0x5555)
	{
		str << "BOOT";
	}
	else
	{
		str << "ERR";
	}
	const SalComVersion* pComVersionTemp=&(SmartBoard[0].CheckStatus()->Version1);
	str << " VER:"<<(pComVersionTemp->ProgVersion/100)<<"."<<((pComVersionTemp->ProgVersion/10)%10)<<(pComVersionTemp->ProgVersion%10);
	uint32 FpgaDate = 0;
	FpgaDate=pComVersionTemp->ProgDate;
#if(CN_SOFT_VER_FPGA1<CN_SOFT_FPGA1_V3)
	FpgaDate=20000000+((FpgaDate>>10)&0x3f)*10000+((FpgaDate>>6)&0xf)*100+((FpgaDate)&0x3f);
#endif
	str << " DAT:";
	str.FormatHex(FpgaDate);
	str << " CRC:" ;
	str.FormatHex(pComVersionTemp->ProgCrc);
	str << " BtCRC:" ;
	pComVersionTemp=&(SmartBoard[0].CheckStatus()->Version2);
    str.FormatHex(pComVersionTemp->ProgCrc);
	str << "\n";
#if(CN_DEV_CPU1)
	// FPGA2�汾��Ϣ
		str << "FPGA2:";
	if(SmartBoard[1].RunState(0)==0xAAAA)
	{
		str <<"OK";
	}
	else if(SmartBoard[1].RunState(0)==0x5555)
	{
		str << "BOOT";
	}
	else
	{
		str << "ERR";
	}
	pComVersionTemp=&(SmartBoard[1].CheckStatus()->Version1);
	str << " VER:"<<(pComVersionTemp->ProgVersion/100)<<"."<<((pComVersionTemp->ProgVersion/10)%10)<<(pComVersionTemp->ProgVersion%10);
	FpgaDate = 0;
	FpgaDate=pComVersionTemp->ProgDate;
#if(CN_SOFT_VER_FPGA1<CN_SOFT_FPGA1_V3)
	FpgaDate=20000000+((FpgaDate>>10)&0x3f)*10000+((FpgaDate>>6)&0xf)*100+((FpgaDate)&0x3f);
#endif
	str << " DAT:";
	str.FormatHex(FpgaDate);
	str << " CRC:" ;
	str.FormatHex(pComVersionTemp->ProgCrc);
	str << " BtCRC:" ;
	pComVersionTemp=&(SmartBoard[1].CheckStatus()->Version2);
	str.FormatHex(pComVersionTemp->ProgCrc);
	str << "\n";
#endif
	// LED�汾��Ϣ
	SalComVersion* LcdVersionTemp=&(ApiVersionInfo::Instance().LcdVersion());
	str << "LED      VER:"<<(UINT16)(LcdVersionTemp->ProgVersion/100)<<"."<<(UINT16)(LcdVersionTemp->ProgVersion%100);
	str << " DAT:";
	str.FormatHex((UINT32)LcdVersionTemp->ProgDate);
	str << " CRC:";
	str.FormatHex((UINT16)LcdVersionTemp->ProgCrc);

	str << " RtCRC:";
	str.FormatHex((UINT16)LcdVersionTemp->RtCrc);
	str <<"\n";
	// ����LCD�汾��Ϣ
	LcdVersionTemp=&(ApiVersionInfo::Instance().VirLcdVersion());
	str << "Tool     VER:"<<(UINT16)(LcdVersionTemp->ProgVersion/100)<<"."<<(UINT16)(LcdVersionTemp->ProgVersion%100);
	str << " DAT:";
	str.FormatHex((UINT32)LcdVersionTemp->ProgDate);
	str << " CRC:";
	str.FormatHex((UINT16)LcdVersionTemp->ProgCrc);
	str << " RtCRC:";
	str.FormatHex((UINT16)LcdVersionTemp->RtCrc);
	str <<"\n";
	wnd.SetPage(page++,  str.Str());
	str.Clear();
	// DC�汾��Ϣ
	pComVersionTemp=&(AppDcInBoard.CheckStatus()->Version1);
	str << "DC  VER:"<<(pComVersionTemp->ProgVersion>>8)<< ".";
	str.FormatHex((UINT8)pComVersionTemp->ProgVersion);
	str << "  DAT:";
	str.FormatHex(pComVersionTemp->ProgDate);
	str << "  CRC:";
	str.FormatHex((UINT16)pComVersionTemp->ProgCrc);
	str << "  RtCRC:";
	str.FormatHex((UINT16)pComVersionTemp->RtCrc);
	str <<"\n";
	// DO�汾��Ϣ
	uint8 i;
	for(i=0;i<CN_NUM_BOARD_DO_RTN;i++)
	{
	    pComVersionTemp=&(NorDoBoard[i].CheckStatus()->Version1);
		str <<g_tBoardDOTab[i].byName<<" VER:"<<(pComVersionTemp->ProgVersion>>8)<< ".";
		str.FormatHex((UINT8)pComVersionTemp->ProgVersion);
		str << "  DAT:";
		str.FormatHex(pComVersionTemp->ProgDate);
		str << "  CRC:";
		str.FormatHex((UINT16)pComVersionTemp->ProgCrc);
		str << "  RtCRC:";
		str.FormatHex((UINT16)pComVersionTemp->RtCrc);
		str <<"\n";
	}
	// DI�汾��Ϣ
	for(i=0;i<CN_NUM_BOARD_DI_DI;i++)
	{
		pComVersionTemp=&(NormalStateBoardIn[i].CheckStatus()->Version1);
		str <<g_tBoardDITab[i].byName<<" VER:"<<(pComVersionTemp->ProgVersion>>8)<< ".";
		str.FormatHex((UINT8)pComVersionTemp->ProgVersion);
		str << "  DAT:";
		str.FormatHex(pComVersionTemp->ProgDate);
		str << "  CRC:";
		str.FormatHex((UINT16)pComVersionTemp->ProgCrc);
		str << "  RtCRC:";
		str.FormatHex((UINT16)pComVersionTemp->RtCrc);
		str <<"\n";
	}
	wnd.SetPage(page++,  str.Str());
	// ��ϸ��Ϣ
	str.Clear();
	ApiVersionInfo::Instance().AppVersion().ToStr(str);
	wnd.SetPage(page++, str.Str());
	
	str.Clear();
	ApiVersionInfo::Instance().ApiVersion().ToStr(str);
	wnd.SetPage(page++, str.Str());

	str.Clear();
	ApiVersionInfo::Instance().Boot0Version().ToStr(str);
	wnd.SetPage(page++, str.Str());
	str.Clear();
	ApiVersionInfo::Instance().UbootVersion().ToStr(str);
	wnd.SetPage(page++,  str.Str());
	str.Clear();
	ApiVersionInfo::Instance().MainSysVersion().ToStr(str);
	wnd.SetPage(page++,  str.Str());
	str.Clear();
	ApiVersionInfo::Instance().BakSysVersion().ToStr(str);
	wnd.SetPage(page++,  str.Str());
	str.Clear();
	//str << "����Һ�� :"; ApiVersionInfo::Instance().VirLcdVersion().RtInfoStrFmt1(str); str << "\n";
	//str << "Һ������ :"; ApiVersionInfo::Instance().LcdVersion().RtInfoStrFmt1(str); str << "\n";
	//wnd.SetPage(page++, str.Str());
	//str.Clear();
#endif
	wnd.SetTitle("�汾��Ϣ", page);
	wnd.Show();
//	ApiVersionInfo::Instance().Print();
	str.Clear();
	str << "��������:" << "���ɵ��ӹɷ����޹�˾" << "\n";
	str << "װ���ͺ�:" << CN_DEV_TITLE_NAME << "\n";
	str << CN_CPU_PUBLIC_SOFT << "\n";
	str << g_tDevInfor.byVerOthName << "\n";
	str << "CCD�ļ�CRC:";
	str.FormatHex(g_tDevInfor.dwCrc);
	str << "\n";
	str << "װ��Ψһ�Ա���:" << ApiUnitCfg::Instance().DeviceID.StrData() << "\n";
	Wnd.SetPage(0, str.Str());
	Wnd.SetReDraw(1);
	return 1;
}
bool8 ViewPublicVersion(ApiMenu* Menu)
{
	ApiHmiTextWnd wnd(HmiTextWnd::E_SinglePage, ViewPrivateVersion);
	String1000B str;
	str.Clear();
	str << "��������:" << "���ɵ��ӹɷ����޹�˾" << "\n";
	str << "װ���ͺ�:" << CN_DEV_TITLE_NAME << "\n";
	str << CN_CPU_PUBLIC_SOFT << "\n";
	str << g_tDevInfor.byVerOthName << "\n";
	str << "CCD�ļ�CRC:";
	str.FormatHex(g_tDevInfor.dwCrc);
	str << "\n";
	str << "װ��Ψһ�Ա���:" << ApiUnitCfg::Instance().DeviceID.StrData() << "\n";
	wnd.SetPage(0, str.Str());
	wnd.SetTitle("�汾��Ϣ", 1);
	wnd.Show();
	return 1;
}
bool8 DispTaskLoadInfo(ApiMenu* Menu)
{
    ApiHmiGridWnd gwnd;
    uint32 lcdw = GraphicDevice::Instance().LcdWidth();
    gwnd.SetInfo("���ؼ���(��λus)", 0, 0);
    const TaskMonitor::RunInfo& Info = TaskMonitor::Instance().TaskRunInfo();
    if (lcdw == 480)
    {
       gwnd.SetColTitle("����", "    ʵʱ", "   Max(H)", "   Min(H)", "   Max(D)", "   Min(D)", 0, 0, 0, 0);
        if (Info.isInfoOk)
        {
          for (uint16 i = 0; i < Info.taskNum; i++)
          {
              struct HmiGridWndDataMapRow* row = gwnd.CreatRow();
               row->SetName(Info.info[i].taskRunInfo->Name());
                    row->SetColDataCfg(1, 0, E_SVT_U32 | E_SVT_PTR, 8, 0);
                    row->SetColData(1, &Info.info[i].taskRunInfo->realTimeLoad);
                    row->SetColDataCfg(2, 0, E_SVT_U32 | E_SVT_PTR, 8, 0);
                    row->SetColData(2, &Info.info[i].taskRunInfo->maxHourLoad);
                    row->SetColDataCfg(3, 0, E_SVT_U32 | E_SVT_PTR, 8, 0);
                    row->SetColData(3, &Info.info[i].taskRunInfo->minHourLoad);
                    row->SetColDataCfg(4, 0, E_SVT_U32 | E_SVT_PTR, 8, 0);
                    row->SetColData(4, &Info.info[i].taskRunInfo->maxDayLoad);
                    row->SetColDataCfg(5, 0, E_SVT_U32 | E_SVT_PTR, 8, 0);
                    row->SetColData(5, &Info.info[i].taskRunInfo->minDayLoad);
                }
            }
        }
        else if (lcdw == 320)
        {

        }
        gwnd.Show();
        return 1;
 }
 bool8 DispTaskPeriodInfo(ApiMenu* Menu)
 {
        ApiHmiGridWnd gwnd;
        uint32 lcdw = GraphicDevice::Instance().LcdWidth();
        gwnd.SetInfo("���ڼ���(��λus)", 0, 0);
        const TaskMonitor::RunInfo& Info = TaskMonitor::Instance().TaskRunInfo();
        if (lcdw == 480)
        {
            gwnd.SetColTitle("����", "    ʵʱ", "   Max(H)", "   Min(H)", "   Max(D)", "   Min(D)", 0, 0, 0, 0);
            if (Info.isInfoOk)
            {
                for (uint16 i = 0; i < Info.taskNum; i++)
                {
                    struct HmiGridWndDataMapRow* row = gwnd.CreatRow();
                    row->SetName(Info.info[i].taskRunInfo->Name());
                    row->SetColDataCfg(1, 0, E_SVT_U32 | E_SVT_PTR, 8, 0);
                    row->SetColData(1, &Info.info[i].taskRunInfo->realTimePeriod);
                    row->SetColDataCfg(2, 0, E_SVT_U32 | E_SVT_PTR, 8, 0);
                    row->SetColData(2, &Info.info[i].taskRunInfo->maxHourPeriod);
                    row->SetColDataCfg(3, 0, E_SVT_U32 | E_SVT_PTR, 8, 0);
                    row->SetColData(3, &Info.info[i].taskRunInfo->minHourPeriod);
                    row->SetColDataCfg(4, 0, E_SVT_U32 | E_SVT_PTR, 8, 0);
                    row->SetColData(4, &Info.info[i].taskRunInfo->maxDayPeriod);
                    row->SetColDataCfg(5, 0, E_SVT_U32 | E_SVT_PTR, 8, 0);
                    row->SetColData(5, &Info.info[i].taskRunInfo->minDayPeriod);
                }
            }
        }
	else if (lcdw == 320)
	{

	}
	gwnd.Show();
	return 1;
}

bool8 ClearTaskRunCalInfo(ApiMenu* Menu)
{
	ApiSelectDialog sd("�������ͳ����Ϣ��", 0, 0, 0, 0);
	if (sd.Show() == 0)
	{
		TaskMonitor::Instance().ClearCalRunInfo();
		for (uint16 i = 0; i < AppRunTimeCfg.sampAppCfg.AppArrLen; i++)
		{
			AppRunTimeCfg.sampAppCfg.AppArrBase[i].ClearLoadInfo();
		}
		ApiWarnDialog wd("������", 0, 0, 0, 0);
		wd.Show();
	}
	return 1;
}

bool8 UpdateLogCfg(ApiMenu* Menu)
{
	ApiSelectDialog sd("������־�����ļ���", 0, 0, 0, 0);
	if (sd.Show() == 0)
	{
		SptLogTask::Instance().LoadCfg();
		ApiWarnDialog wd("�������", 0, 0, 0, 0);
		wd.Show();
	}
	return 1;
}

bool8 AppEthnetPara(ApiMenu* Menu)
{
	ApiSelectDialog sd(Menu->Name(),0, 0, 0, 0);
	int32 res = sd.Show();
	if (res == 0)
	{
		if((ApiSysEthNetCfg::Instance().ReadAll())>0)
		{
			ApiSysEthNetCfg::Instance().AppEthnetPara();
			ApiWarnDialog wd(Menu->Name(), "�ɹ�", 0, 0, 0);
			wd.Show();
			AppEthNetParaRef();
		}
		else
		{
			ApiWarnDialog wd(Menu->Name(), "ʧ��", 0, 0, 0);
			wd.Show();
		}
	}
	return 1;
}

static int32 HmiViewAnglogUpdateData(class HmiGridWnd* Wnd, struct HmiGridWndDataMap* Map, HmiKey Key)
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

	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiDispAnaGroup;
	uint32 dataNum = anmsGroup->InstNum();
	st64value* pvalue;
	uint8 col = 1;
	uint32 rown = 0;
	uint32 bufIndex = anmsGroup->GetNewestDataIndex();

	for (uint16 i = 0; i < dataNum; i++)
	{
		SalAngRms* rms = anmsGroup->Cell(i);
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
			pvalue->value.i32 = (int32)(rmsValue->data1 * rms->Data1Coe());//һ��ֵ
			col++;
			col++;
			pvalue = row->GetDataEdit(col);
			pvalue->value.i32 = rmsValue->data1;//����ֵ
			col++;
			col++;
			pvalue = row->GetDataEdit(col);
			pvalue->value.i32 = rmsValue->data2;//�Ƕ�
			col++;
			col++;
			pvalue = row->GetDataEdit(col);
			pvalue->value.u16 = rmsValue->q;//Ʒ��
		}
		else
		{
			break;
		}
	}
	return 0;
}

bool8 ViewAnglog(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd(HmiViewAnglogUpdateData);
	wnd.SetInfo("�鿴ģ����", 0, 0);
	wnd.SetColTitle("����", "һ��ֵ", 0, "����ֵ", 0, 0, 0, "Ʒ��", 0, 0);
	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiDispAnaGroup;
	uint32 dataNum = anmsGroup->InstNum();
	st64value* pvalue;
	uint8 col = 1;
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalAngRms* rms = anmsGroup->Cell(i);
		if (rms)
		{
			if (!rms->IsDisp())
			{
				continue;
			}
			col = 1;
			struct HmiGridWndDataMapRow* row = wnd.CreatRow();
			row->SetName(rms->Name());
			//һ��ֵ
			row->SetColDataCfg(col, 0, E_SVT_I32 | E_SVT_PTR, 9, rms->Data1DotNum());
			pvalue = row->GetDataSur(col);
			pvalue->value.vptr = rms;
			pvalue = row->GetDataEdit(col);
			row->SetColData(col, &pvalue->value.i32);
			col++;
			row->SetColDataCfg(col, 0, E_SVT_STR | E_SVT_PTR, 2, 0);
			row->SetColStrData(col, rms->TransUnits1() == 0 ? Unit_NULL.toString() : rms->TransUnits1()->toString(), 0);
			col++;
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
			//Ʒ��
			if (rms->Data3Len() == 2)
			{
				row->SetColDataCfg(col, 0, E_SVT_HEX16 | E_SVT_PTR, 4, 0);
				pvalue = row->GetDataSur(col);
				pvalue->value.vptr = rms;
				pvalue = row->GetDataEdit(col);
				row->SetColData(col, &pvalue->value.u16);
				col++;
			}
			else
			{
				col++;
			}
		}
		else
		{
			break;
		}
	}
	wnd.Show();
	return 1;
}
static int32 HmiViewFrlogUpdateData(class HmiGridWnd* Wnd, struct HmiGridWndDataMap* Map, HmiKey Key)
{
	if(AppDispFrRef())
	{
		return 0;
	}

	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiDispFrGroup;
	uint32 dataNum = anmsGroup->InstNum();
	st64value* pvalue;
	uint8 col = 1;
	uint32 rown = 0;
	uint32 bufIndex = anmsGroup->GetNewestDataIndex();
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalAngRms* rms = anmsGroup->Cell(i);
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
			pvalue->value.i32 = rmsValue->data1;
			col++;
			col++;
			col++;
			col++;
			col++;
			col++;
		}
		else
		{
			break;
		}
	}
	return 0;
}

bool8 ViewFrlog(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd(HmiViewFrlogUpdateData);
	wnd.SetInfo("�鿴Ƶ��", 0, 0);
	wnd.SetColTitle("����", "Ƶ��", 0, 0, 0, 0, 0, 0, 0, 0);
	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiDispFrGroup;
	uint32 dataNum = anmsGroup->InstNum();
	st64value* pvalue;
	uint8 col = 1;
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalAngRms* rms = anmsGroup->Cell(i);
		if (rms)
		{
			if (!rms->IsDisp())
			{
				continue;
			}
			col = 1;
			struct HmiGridWndDataMapRow* row = wnd.CreatRow();
			row->SetName(rms->Name());
			// Ƶ��
			row->SetColDataCfg(col, 0, E_SVT_I32 | E_SVT_PTR, 8, rms->Data1DotNum());
			pvalue = row->GetDataSur(col);
			pvalue->value.vptr = rms;
			pvalue = row->GetDataEdit(col);
			row->SetColData(col, &pvalue->value.i32);
			col++;
			row->SetColDataCfg(col, 0, E_SVT_STR | E_SVT_PTR, 2, 0);
			row->SetColStrData(col, rms->Units1() == 0 ? Unit_NULL.toString() : rms->Units1()->toString(), 0);
			col++;
			
			col++;
			col++;
			col++;
			col++;
			col++;
		}
		else
		{
			break;
		}
	}
	wnd.Show();
	return 1;
}
static int32 HmiViewDclogUpdateData(class HmiGridWnd* Wnd, struct HmiGridWndDataMap* Map, HmiKey Key)
{
	if(AppDispDcRef())
	{
		return 0;
	}
	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiDispDcGroup;
	uint32 dataNum = anmsGroup->InstNum();
	st64value* pvalue;
	uint8 col = 1;
	uint32 rown = 0;
	uint32 bufIndex = anmsGroup->GetNewestDataIndex();
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalAngRms* rms = anmsGroup->Cell(i);
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
			pvalue->value.i32 = rmsValue->data1;
			col++;
			col++;
			pvalue = row->GetDataEdit(col);
			pvalue->value.i32 = rmsValue->data2;
			col++;
			pvalue = row->GetDataEdit(col);
			pvalue->value.i32 = GoDcOutCell[i].Value().i32;
			col++;
			col++;
			col++;
		}
		else
		{
			break;
		}
	}
	return 0;
}

bool8 ViewDclog(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd(HmiViewDclogUpdateData);
	wnd.SetInfo("�鿴ֱ����Ϣ", 0, 0);
	wnd.SetColTitle("����", "����ֵ",0,"һ��ֵ", "GOOSE����", 0, 0,  0, 0, 0);
	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiDispDcGroup;
	uint32 dataNum = anmsGroup->InstNum();
	st64value* pvalue;
	uint8 col = 1;
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalAngRms* rms = anmsGroup->Cell(i);
		if (rms)
		{
			if (!rms->IsDisp())
			{
				continue;
			}
			col = 1;
			struct HmiGridWndDataMapRow* row = wnd.CreatRow();
			row->SetName(rms->Name());
			// ֱ��ֵ
			row->SetColDataCfg(col, 0, E_SVT_I32 | E_SVT_PTR, 8, rms->Data1DotNum());
			pvalue = row->GetDataSur(col);
			pvalue->value.vptr = rms;
			pvalue = row->GetDataEdit(col);
			row->SetColData(col, &pvalue->value.i32);
			col++;
			row->SetColDataCfg(col, 0, E_SVT_STR | E_SVT_PTR, 2, 0);
			row->SetColStrData(col, rms->Units1() == 0 ? Unit_NULL.toString() : rms->Units1()->toString(), 0);
			col++;
			// ת��ֵ
			row->SetColDataCfg(col, 0, E_SVT_I32 | E_SVT_PTR, 8, rms->Data2DotNum());
			pvalue = row->GetDataSur(col);
			pvalue->value.vptr = rms;
			pvalue = row->GetDataEdit(col);
			row->SetColData(col, &pvalue->value.i32);
			col++;
			// ����ֵ
			row->SetColDataCfg(col, 0, E_SVT_I32 | E_SVT_PTR, 8, rms->Data1DotNum());
			pvalue = row->GetDataSur(col);
			pvalue->value.vptr = &GoDcOutCell[i];
			pvalue = row->GetDataEdit(col);
			row->SetColData(col, &g_tagDC.iDCOutCom[i]);
			
			col++;
			col++;
			col++;
			col++;
		}
		else
		{
			break;
		}
	}
	wnd.Show();
	return 1;
}

static int32 HmiViewDevlogUpdateData(class HmiGridWnd* Wnd, struct HmiGridWndDataMap* Map, HmiKey Key)
{
	if(AppDispDevRef())
	{
		return 0;
	}

	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiDispDevGroup;
	uint32 dataNum = anmsGroup->InstNum();
	st64value* pvalue;
	uint8 col = 1;
	uint32 rown = 0;
	uint32 bufIndex = anmsGroup->GetNewestDataIndex();
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalAngRms* rms = anmsGroup->Cell(i);
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
			pvalue->value.i32 = rmsValue->data1;
			col++;
			col++;
			col++;
			col++;
			col++;
			col++;
		}
		else
		{
			break;
		}
	}
	return 0;
}

bool8 ViewDevlog(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd(HmiViewDevlogUpdateData);
	wnd.SetInfo("�鿴״̬����", 0, 0);
	//wnd.SetColTitle("����", "Ƶ��", 0, 0, 0, 0, 0, 0, 0, 0);
	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiDispDevGroup;
	uint32 dataNum = anmsGroup->InstNum();
	st64value* pvalue;
	uint8 col = 1;
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalAngRms* rms = anmsGroup->Cell(i);
		if (rms)
		{
			if (!rms->IsDisp())
			{
				continue;
			}
			col = 1;
			struct HmiGridWndDataMapRow* row = wnd.CreatRow();
			row->SetName(rms->Name());
			// 16����չʾ
			if (g_tDCTab[i+EN_DC_DEV_STR].wType==EN_CTYPE_DC_H)
			{
				row->SetColDataCfg(col, 0, E_SVT_HEX32 | E_SVT_PTR, 8, rms->Data1DotNum());
				pvalue = row->GetDataSur(col);
				pvalue->value.vptr = rms;
				pvalue = row->GetDataEdit(col);
				row->SetColData(col, &pvalue->value.u32);
			}
			else
			{
				row->SetColDataCfg(col, 0, E_SVT_I32 | E_SVT_PTR, 8, rms->Data1DotNum());
				pvalue = row->GetDataSur(col);
				pvalue->value.vptr = rms;
				pvalue = row->GetDataEdit(col);
				row->SetColData(col, &pvalue->value.i32);
			}

			col++;
			row->SetColDataCfg(col, 0, E_SVT_STR | E_SVT_PTR, 2, 0);
			row->SetColStrData(col, rms->Units1() == 0 ? Unit_NULL.toString() : rms->Units1()->toString(), 0);
			col++;
			
			col++;
			col++;
			col++;
			col++;
			col++;
		}
		else
		{
			break;
		}
	}
	wnd.Show();
	return 1;
}
static int32 HmiViewOpt1logUpdateData(class HmiGridWnd* Wnd, struct HmiGridWndDataMap* Map, HmiKey Key)
{
	if(AppDispOpt1Ref())
	{
		return 0;
	}

	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiDispOptGroup[0];
	uint32 dataNum = anmsGroup->InstNum();
	st64value* pvalue;
	uint8 col = 1;
	uint32 rown = 0;
	uint32 bufIndex = anmsGroup->GetNewestDataIndex();
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalAngRms* rms = anmsGroup->Cell(i);
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
			pvalue->value.i32 = rmsValue->data1;
			col++;
			col++;
			col++;
			col++;
			col++;
			col++;
		}
		else
		{
			break;
		}
	}
	return 0;
}

bool8 ViewOpt1log(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd(HmiViewOpt1logUpdateData);
	wnd.SetInfo("�鿴���CPU��⹦��", 0, 0);
	//wnd.SetColTitle("����", "Ƶ��", 0, 0, 0, 0, 0, 0, 0, 0);
	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiDispOptGroup[0];
	uint32 dataNum = anmsGroup->InstNum();
	st64value* pvalue;
	uint8 col = 1;
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalAngRms* rms = anmsGroup->Cell(i);
		if (rms)
		{
			if (!rms->IsDisp())
			{
				continue;
			}
			col = 1;
			struct HmiGridWndDataMapRow* row = wnd.CreatRow();
			row->SetName(rms->Name());
			// 
			row->SetColDataCfg(col, 0, E_SVT_I32 | E_SVT_PTR, 8, rms->Data1DotNum());
			pvalue = row->GetDataSur(col);
			pvalue->value.vptr = rms;
			pvalue = row->GetDataEdit(col);
			row->SetColData(col, &pvalue->value.i32);
			col++;
			row->SetColDataCfg(col, 0, E_SVT_STR | E_SVT_PTR, 2, 0);
			row->SetColStrData(col, rms->Units1() == 0 ? Unit_NULL.toString() : rms->Units1()->toString(), 0);
			col++;
			
			col++;
			col++;
			col++;
			col++;
			col++;
		}
		else
		{
			break;
		}
	}
	wnd.Show();
	return 1;
}
static int32 HmiViewOpt2logUpdateData(class HmiGridWnd* Wnd, struct HmiGridWndDataMap* Map, HmiKey Key)
{
	if(AppDispOpt2Ref())
	{
		return 0;
	}

	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiDispOptGroup[1];
	uint32 dataNum = anmsGroup->InstNum();
	st64value* pvalue;
	uint8 col = 1;
	uint32 rown = 0;
	uint32 bufIndex = anmsGroup->GetNewestDataIndex();
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalAngRms* rms = anmsGroup->Cell(i);
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
			pvalue->value.i32 = rmsValue->data1;
			col++;
			col++;
			col++;
			col++;
			col++;
			col++;
		}
		else
		{
			break;
		}
	}
	return 0;
}

bool8 ViewOpt2log(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd(HmiViewOpt2logUpdateData);
	wnd.SetInfo("�鿴ĸ��CPU�⹦��", 0, 0);
	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiDispOptGroup[1];
	uint32 dataNum = anmsGroup->InstNum();
	st64value* pvalue;
	uint8 col = 1;
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalAngRms* rms = anmsGroup->Cell(i);
		if (rms)
		{
			if (!rms->IsDisp())
			{
				continue;
			}
			col = 1;
			struct HmiGridWndDataMapRow* row = wnd.CreatRow();
			row->SetName(rms->Name());
			// Ƶ��
			row->SetColDataCfg(col, 0, E_SVT_I32 | E_SVT_PTR, 8, rms->Data1DotNum());
			pvalue = row->GetDataSur(col);
			pvalue->value.vptr = rms;
			pvalue = row->GetDataEdit(col);
			row->SetColData(col, &pvalue->value.i32);
			col++;
			row->SetColDataCfg(col, 0, E_SVT_STR | E_SVT_PTR, 2, 0);
			row->SetColStrData(col, rms->Units1() == 0 ? Unit_NULL.toString() : rms->Units1()->toString(), 0);
			col++;
			
			col++;
			col++;
			col++;
			col++;
			col++;
		}
		else
		{
			break;
		}
	}
	wnd.Show();
	return 1;
}

static int32 HmiViewInterlogUpdateData(class HmiGridWnd* Wnd, struct HmiGridWndDataMap* Map, HmiKey Key)
{
	if(AppDispInterRef())
	{
		return 0;
	}

	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiDispInterGroup;
	uint32 dataNum = anmsGroup->InstNum();
	st64value* pvalue;
	uint8 col = 1;
	uint32 rown = 0;
	uint32 bufIndex = anmsGroup->GetNewestDataIndex();
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalAngRms* rms = anmsGroup->Cell(i);
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
			pvalue->value.i32 = rmsValue->data1;
			col++;
			col++;
			col++;
			col++;
			col++;
			col++;
		}
		else
		{
			break;
		}
	}
	return 0;
}

bool8 ViewInterlog(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd(HmiViewInterlogUpdateData);
	wnd.SetInfo("�鿴�ڲ���Ϣ", 0, 0);
	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiDispInterGroup;
	uint32 dataNum = anmsGroup->InstNum();
	st64value* pvalue;
	uint8 col = 1;
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalAngRms* rms = anmsGroup->Cell(i);
		if (rms)
		{
			if (!rms->IsDisp())
			{
				continue;
			}
			col = 1;
			struct HmiGridWndDataMapRow* row = wnd.CreatRow();
			row->SetName(rms->Name());
			// Ƶ��
			row->SetColDataCfg(col, 0, E_SVT_I32 | E_SVT_PTR, 8, rms->Data1DotNum());
			pvalue = row->GetDataSur(col);
			pvalue->value.vptr = rms;
			pvalue = row->GetDataEdit(col);
			row->SetColData(col, &pvalue->value.i32);
			col++;
			row->SetColDataCfg(col, 0, E_SVT_STR | E_SVT_PTR, 2, 0);
			row->SetColStrData(col, rms->Units1() == 0 ? Unit_NULL.toString() : rms->Units1()->toString(), 0);
			col++;
			
			col++;
			col++;
			col++;
			col++;
			col++;
		}
		else
		{
			break;
		}
	}
	wnd.Show();
	return 1;
}

