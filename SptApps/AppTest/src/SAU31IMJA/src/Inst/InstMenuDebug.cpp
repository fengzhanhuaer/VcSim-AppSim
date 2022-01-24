#include "InstResource.h"

bool8 EnterDebugMode(ApiMenu* Menu)
{
	if (LcdOperUsrDbgLogIn(Menu) == 0)
	{
		return 0;
	}
	ApiIoGlobalFlag::Instance().SetUnitDebugState(1);
	AppEventOptRef(EN_OPT_DEBUG_IN);
	return 1;
}

bool8 ExitDebugMode(ApiMenu* Menu)
{
	ApiIoGlobalFlag::Instance().SetUnitDebugState(0);
	AppEventOptRef(EN_OPT_DEBUG_OUT);
	return 1;
}
bool8 EnterFactDebugMode(ApiMenu* Menu)
{
	AppEventOptRef(EN_OPT_FACT_DEBUG_IN);
	// 厂家调试密码验证
	int8 res = LcdDbgOperationAccountInfo(Menu);
	if (res == -1)
	{
		MenuDispDbgDisp = TRUE;
		return 1;
	}
	else if (res == 0)
	{
		return 0;
	}
	// 权限检查
	else  if (LcdOperFacInitLogIn(Menu) == 0)
	{
		return 0;
	}
	return 1;
}

bool8 ExitFactDebugMode(ApiMenu* Menu)
{
	AppEventOptRef(EN_OPT_FACT_DEBUG_OUT);
	MenuDispDbgDisp = FALSE;
	return 1;
}

bool8 Boot0Update(ApiMenu* Menu)
{
	String100B str;
	str << CN_UPDATE_FILE_ROOT;
	str << FilePath::DivFlag << "Sylix.Boot0.bin";
	if (UpdateBoot0ForLcd(str.Str(), DispProcess) == 0)
	{
		AppEventOptRef(EN_OPT_UPDATE_BOOT0_SUCC);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "升级成功", 0, 0, 0);
	}
	else
	{
		AppEventOptRef(EN_OPT_UPDATE_BOOT0_FAIL);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "升级失败", 0, 0, 0);
	}
	DispPressAnyKey();
	return 1;
}

bool8 UbootUpdate(ApiMenu* Menu)
{
	String100B str;
	str << CN_UPDATE_FILE_ROOT;
	str << FilePath::DivFlag << "Sylix.UBoot.bin";
	if (UpdateUBootForLcd(str.Str(), DispProcess) == 0)
	{
		AppEventOptRef(EN_OPT_UPDATE_UBOOT_SUCC);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "升级成功", 0, 0, 0);
	}
	else
	{
		AppEventOptRef(EN_OPT_UPDATE_UBOOT_FAIL);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "升级失败", 0, 0, 0);
	}
	DispPressAnyKey();
	return 1;
}
bool8 UpdateFpga1(ApiMenu* Menu)
{
	String100B str;
	str = CN_UPDATE_FILE_ROOT;
	str << FilePath::DivFlag << "CFPGA1.bin";
	GzkFpgaUpdate update(str.Str(), 5 * 1024 * 1024, 0x0001, 512, 3);
	if (update.Run(DispProcess) == 0)
	{
		AppEventOptRef(EN_OPT_UPDATE_FPGA1_SUCC);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "升级成功", 0, 0, 0);
	}
	else
	{
		AppEventOptRef(EN_OPT_UPDATE_FPGA1_FAIL);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "升级失败", 0, 0, 0);
	}
	DispPressAnyKey();
	return 1;
}

bool8 UpdateFpga2(ApiMenu* Menu)
{
	String100B str;
	str = CN_UPDATE_FILE_ROOT;
	str << FilePath::DivFlag << "CFPGA2.bin";
	GzkFpgaUpdate update(str.Str(), 5 * 1024 * 1024, 0x0002, 512, 3);
	if (update.Run(DispProcess) == 0)
	{
		AppEventOptRef(EN_OPT_UPDATE_FPGA2_SUCC);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "升级成功", 0, 0, 0);
	}
	else
	{
		AppEventOptRef(EN_OPT_UPDATE_FPGA2_FAIL);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "升级失败", 0, 0, 0);
	}
	DispPressAnyKey();
	return 1;
}

bool8 OsUpdate(ApiMenu* Menu)
{
	String100B str;
	str << CN_UPDATE_FILE_ROOT;
	str << FilePath::DivFlag << "Sylix.T3BSP.bin";

	if (UpdateOsForLcd(str.Str(), DispProcess) == 0)
	{
		AppEventOptRef(EN_OPT_UPDATE_SYSTEM_SUCC);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "升级成功", 0, 0, 0);
	}
	else
	{
		AppEventOptRef(EN_OPT_UPDATE_SYSTEM_FAIL);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "升级失败", 0, 0, 0);
	}
	DispPressAnyKey();
	return 1;
}
bool8 Boot0Update1(ApiMenu* Menu)
{
	String100B str;
	str << CN_UPDATE1_FILE_ROOT;
	str << FilePath::DivFlag << "Sylix.Boot0.bin";
	if (UpdateBoot0ForLcd(str.Str(), DispProcess) == 0)
	{
		AppEventOptRef(EN_OPT_UPDATE_BOOT0_SUCC);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "升级成功", 0, 0, 0);
	}
	else
	{
		AppEventOptRef(EN_OPT_UPDATE_BOOT0_FAIL);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "升级失败", 0, 0, 0);
	}
	DispPressAnyKey();
	return 1;
}

bool8 UbootUpdate1(ApiMenu* Menu)
{
	String100B str;
	str << CN_UPDATE1_FILE_ROOT;
	str << FilePath::DivFlag << "Sylix.UBoot.bin";
	if (UpdateUBootForLcd(str.Str(), DispProcess) == 0)
	{
		AppEventOptRef(EN_OPT_UPDATE_UBOOT_SUCC);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "升级成功", 0, 0, 0);
	}
	else
	{
		AppEventOptRef(EN_OPT_UPDATE_UBOOT_FAIL);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "升级失败", 0, 0, 0);
	}
	DispPressAnyKey();
	return 1;
}

bool8 OsUpdate1(ApiMenu* Menu)
{
	String100B str;
	str << CN_UPDATE1_FILE_ROOT;
	str << FilePath::DivFlag << "Sylix.T3BSP.bin";
	if (UpdateOsForLcd(str.Str(), DispProcess) == 0)
	{
		AppEventOptRef(EN_OPT_UPDATE_SYSTEM_SUCC);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "升级成功", 0, 0, 0);
	}
	else
	{
		AppEventOptRef(EN_OPT_UPDATE_SYSTEM_FAIL);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "升级失败", 0, 0, 0);
	}
	DispPressAnyKey();
	return 1;
}

bool8 FlashBak(ApiMenu* Menu)
{
	if (BakUpFlashForLcd(DispProcess))
	{
		AppEventOptRef(EN_OPT_FLASH_BAK_FAIL);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "备份失败", 0, 0, 0);
	}
	else
	{
		AppEventOptRef(EN_OPT_FLASH_BAK_SUCC);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "备份成功", 0, 0, 0);
	}
	DispPressAnyKey();
	return 1;
}
bool8 RestoreFlashPara(ApiMenu* Menu)
{
	if (RestoreFlashPara(DispProcess))
	{
		AppEventOptRef(EN_OPT_PARA_REST_FAIL);

		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "恢复失败", 0, 0, 0);
	}
	else
	{
		AppEventOptRef(EN_OPT_PARA_REST_SUCC);

		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "恢复成功", 0, 0, 0);
	}
	DispPressAnyKey();
	return 1;
}
bool8 FormatSysCard(ApiMenu* Menu)
{
	FormatSysCard(DispProcess);
	DispPressAnyKey();
	return 1;
}
bool8 FormatDataCard(ApiMenu* Menu)
{
	FormatDataCard(DispProcess);
	DispPressAnyKey();
	return 1;
}
bool8 DefaulParaMenu(ApiMenu* Menu, uint16 wIndex)
{
	if ((wIndex >= CN_NUM_BOARD_PARA) && (wIndex != CN_NULL_PINNO))
	{
		return 1;
	}
	ApiSelectDialog sd(Menu->Name(), 0, 0, 0, 0);
	int32 res = sd.Show();
	if (res == 0)
	{
		if (AppParaDefault(wIndex) == 0)
		{
			ApiSelectDialog sd1(Menu->Name(), "初始化本板成功", "是否初始化另一CPU板？", 0, 0);
			res = sd1.Show();
			if (res == 0)
			{
				if (AppSend2SubBoardMsgAndWaitAck(E_ASMT_PARA_INIT, wIndex, 0, 0, 0, 0))
				{
					ApiWarnDialog wd(Menu->Name(), "另一CPU板初始化失败", 0, 0, 0);
					wd.Show();
				}
				else
				{
					ApiWarnDialog wd(Menu->Name(), "另一CPU板初始化成功", 0, 0, 0);
					wd.Show();
				}
			}
		}
		else
		{
			ApiWarnDialog wd(Menu->Name(), "失败", 0, 0, 0);
			wd.Show();
			return 1;
		}
	}
	return 0;
}

bool8 DefaultAllPara(ApiMenu* Menu)
{
	DefaulParaMenu(Menu, CN_NULL_PINNO);
	return 1;
}
bool8 DefaultDiPara(ApiMenu* Menu)
{
	DefaulParaMenu(Menu, EN_BOARD_PARA_DI);
	return 1;
}
bool8 DefaultDcPara(ApiMenu* Menu)
{
	DefaulParaMenu(Menu, EN_BOARD_PARA_DC);
	return 1;
}
bool8 DefaultAnaPara(ApiMenu* Menu)
{
	DefaulParaMenu(Menu, EN_BOARD_PARA_SAM);
	return 1;
}
bool8 DefaultFunPara(ApiMenu* Menu)
{
	DefaulParaMenu(Menu, EN_BOARD_PARA_FUN);
	return 1;
}
bool8 DefaultDcCoePara(ApiMenu* Menu)
{
	DefaulParaMenu(Menu, EN_BOARD_PARA_DC_COE);
	return 1;
}
bool8 DefaultAmCoePara(ApiMenu* Menu)
{
	DefaulParaMenu(Menu, EN_BOARD_PARA_AM_COE);
	return 1;
}
bool8 DefaultDcBcCoePara(ApiMenu* Menu)
{
	DefaulParaMenu(Menu, EN_BOARD_PARA_DCBC_COE);
	return 1;
}
bool8 DefaultAngCoePara(ApiMenu* Menu)
{
	DefaulParaMenu(Menu, EN_BOARD_PARA_ANG_COE);
	return 1;
}
bool8 ClaerEvent(ApiMenu* Menu, WORD wIndex)
{
	ApiSelectDialog sd(Menu->Name(), 0, 0, 0, 0);
	int32 res = sd.Show();
	if (res == 0)
	{
		if (AppEventClear(wIndex) == 0)
		{
			ApiSelectDialog sd1(Menu->Name(), "本板成功", "是否清除另一CPU板？", 0, 0);
			res = sd1.Show();
			if (res == 0)
			{
				if (AppSend2SubBoardMsgAndWaitAck(E_ASMT_PARA_CLEAR, wIndex, 0, 0, 0, 0))
				{
					ApiWarnDialog wd("清除另一CPU板失败", 0, 0, 0, 0);
					wd.Show();
				}
				else
				{
					ApiWarnDialog wd("清除另一CPU板成功", 0, 0, 0, 0);
					wd.Show();
				}
			}
		}
		else
		{
			ApiWarnDialog wd(Menu->Name(), "失败", 0, 0, 0);
			wd.Show();
		}
	}
	return 1;
}

bool8 ClaerAllEvent(ApiMenu* Menu)
{
	ClaerEvent(Menu, CN_NULL_PINNO);
	return 1;
}

bool8 ClaerActEvent(ApiMenu* Menu)
{
	ClaerEvent(Menu, EN_DTYPE_ACT);
	return 1;
}
bool8 ClaerAlmEvent(ApiMenu* Menu)
{
	ClaerEvent(Menu, EN_DTYPE_ALM);
	return 1;
}
bool8 ClaerChkEvent(ApiMenu* Menu)
{
	ClaerEvent(Menu, EN_DTYPE_CHK);
	return 1;
}
bool8 ClaerRunEvent(ApiMenu* Menu)
{
	ClaerEvent(Menu, EN_CFG_RUN);
	return 1;
}

bool8 ClaerOptEvent(ApiMenu* Menu)
{
	ClaerEvent(Menu, EN_CFG_OPT);
	return 1;
}
bool8 ClaerDiSoe(ApiMenu* Menu)
{
	ClaerEvent(Menu, EN_DTYPE_DI);
	return 1;
}
bool8 ClaerDoSoe(ApiMenu* Menu)
{
	ClaerEvent(Menu, EN_DTYPE_DO);
	return 1;
}
bool8 ClaerGoInSoe(ApiMenu* Menu)
{
	ClaerEvent(Menu, EN_DTYPE_GOIN);
	return 1;
}
bool8 ClaerGoOutSoe(ApiMenu* Menu)
{
	ClaerEvent(Menu, EN_DTYPE_GOOUT);
	return 1;
}
bool8 ClaerLedSoe(ApiMenu* Menu)
{
	ClaerEvent(Menu, EN_DTYPE_LED);
	return 1;
}
bool8 ClaerDpiSoe(ApiMenu* Menu)
{
	ClaerEvent(Menu, EN_DTYPE_DPI);
	return 1;
}
bool8 ClaerFlagSoe(ApiMenu* Menu)
{
	ClaerEvent(Menu, EN_DTYPE_FLAG);
	return 1;
}
int32 HmiDoOutSim(bool8& isDataChange, struct HmiGridWndDataMapCell* Cell)
{
	HalIoCell* Obj = (HalIoCell*)Cell->dataSur.value.vptr;
	SptNormalStateOutCell* blOut = (SptNormalStateOutCell*)Obj;
	blOut->blSignalForce(1);
	bool8 value = blOut->Value().value.bl;
	blOut->ForceSetValue(!value, 0, 0);
	String100B str;
	str << Obj->Name() << "传动中";
	ApiWarnDialog wd(str.Str(), 0, 0, 0, 0);
	wd.Show();
	blOut->ForceSetValue(value, 0, 0);
	blOut->blSignalForce(0);
	uint16 wNo = blOut - (SptNormalStateOutCell*)NorDoOut;
	AppEventOptValueRef(EN_OPT_DEBUG_DO, wNo, 0, 0);
	//if((LogInUsr)&&(wNo<CN_NUM_DO))
	//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "开出传动", "开出传动完成",  blOut->Name(), 0, 0);
	return 0;
}
// 装置告警
int32 HmiDoOutSimAlm(bool8& isDataChange, struct HmiGridWndDataMapCell* Cell)
{
	g_iInter[EN_INTER_CPU2_CTRL_DBG] = TRUE;
	bool8 value = (!g_tagIO.bDOOut[EN_DO_ALM]);
	SptSetHwVal(E_HPT_RunErr, &value, 1);
	String100B str;
	str << g_tDoTab[EN_DO_ALM].byName << "传动中";
	ApiWarnDialog wd(str.Str(), 0, 0, 0, 0);
	wd.Show();
	SptSetHwVal(E_HPT_RunErr, &g_tagIO.bDOOut[EN_DO_ALM], 1);
	g_iInter[EN_INTER_CPU2_CTRL_DBG] = FALSE;
	AppEventOptValueRef(EN_OPT_DEBUG_DO, EN_DO_ALM, 0, 0);
	//if(LogInUsr)
	//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "开出传动", "开出传动完成", g_tDoTab[EN_DO_ALM].byName, 0, 0);
	return 0;
}
// 装置故障
int32 HmiDoOutSimChk(bool8& isDataChange, struct HmiGridWndDataMapCell* Cell)
{
	g_iInter[EN_INTER_CPU2_CTRL_DBG] = TRUE;
	bool8 value = (g_tagIO.bDOOut[EN_DO_CHK]);
	SptSetHwVal(E_HPT_UnitErr, &value, 1);
	String100B str;
	str << g_tDoTab[EN_DO_CHK].byName << "传动中";
	ApiWarnDialog wd(str.Str(), 0, 0, 0, 0);
	wd.Show();
	value = (!g_tagIO.bDOOut[EN_DO_CHK]);
	SptSetHwVal(E_HPT_UnitErr, &value, 1);
	g_iInter[EN_INTER_CPU2_CTRL_DBG] = FALSE;
	AppEventOptValueRef(EN_OPT_DEBUG_DO, EN_DO_CHK, 0, 0);
	//if(LogInUsr)
	//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "开出传动", "开出传动完成", g_tDoTab[EN_DO_CHK].byName, 0, 0);
	return 0;
}

bool8 HmiDoOutSim(ApiMenu* Menu)
{
	if (LcdOperationConfirmationAccountInfo(Menu) == 0)
	{
		return 0;
	}
	ApiHmiGridWnd wnd;
	wnd.SetInfo("常规出口调试", 0, 0);
	HmiGridWndDataMapRow* row;
	for (uint32 j = 0; j < M_ArrLen(NorDoBoard); j++)
	{
		SptNormalStateOutBoard* Board = (SptNormalStateOutBoard*)&NorDoBoard[j];
		uint32 num = Board->InstNum();
		for (uint32 i = 0; i < num; i++)
		{
			HalIoCell* Obj = Board->GetIoCell(i);
			if (Obj)
			{
				row = wnd.CreatRow();
				if (row)
				{
					row->SetName(Obj->Name(), HmiDoOutSim);
					st64value* value = row->GetDataSur(0);
					value->value.vptr = Obj;
				}
			}
		}
	}
	// 装置告警
	row = wnd.CreatRow();
	if (row)
	{
		row->SetName(g_tDoTab[EN_DO_ALM].byName, HmiDoOutSimAlm);
	}
	// 装置故障
	row = wnd.CreatRow();
	if (row)
	{
		row->SetName(g_tDoTab[EN_DO_CHK].byName, HmiDoOutSimChk);
	}
	wnd.Edit();
	return 1;
}
int32 HmiGooseOutSSim(bool8& isDataChange, struct HmiGridWndDataMapCell* Cell)
{
	HalIoCell* Obj = (HalIoCell*)Cell->dataSur.value.vptr;
	SptGooseDataOut* blOut = (SptGooseDataOut*)Obj;
	if (blOut->VNode().dataType == E_GOSV_BOOL)
	{
		blOut->blSignalForce(1);
		bool8 value = blOut->Value().value.bl;
		blOut->ForceSetValue(!value, 0, 0);
		String100B str;
		str << Obj->Name() << "传动中";
		ApiWarnDialog wd(str.Str(), 0, 0, 0, 0);
		wd.Show();
		blOut->ForceSetValue(value, 0, 0);
		blOut->blSignalForce(0);
		uint16 wNo = blOut - (SptGooseDataOut*)GoPosOutCell;
		AppEventOptValueRef(EN_OPT_DEBUG_GO_S, wNo, 0, 0);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "GOOSE单点传动", "GOOSE单点传动完成", blOut->Name(), 0, 0);
	}
	// 非发布信号不进行实质的传动
	else if (blOut->VNode().dataType == E_GOSV_NULL)
	{
		ApiWarnDialog wd(Obj->Name(), "信号未发布", 0, 0, 0);
		wd.Show();
	}
	// 发布类型错误
	else
	{
		ApiWarnDialog wd(Obj->Name(), "发布类型不匹配", 0, 0, 0);
		wd.Show();
	}
	return 0;
}
bool8 HmiGooseOutSSim(ApiMenu* Menu)
{
	if (LcdOperationConfirmationAccountInfo(Menu) == 0)
	{
		return 0;
	}
	ApiHmiGridWnd wnd;
	wnd.SetInfo("GOOSE单点出口调试", 0, 0);
	HmiGridWndDataMapRow* row;
	SptGooseFrameOut* Board = (SptGooseFrameOut*)&GoOutFrame[0];
	//uint32 num = Board->InstNum();
	for (uint32 i = 0; i < CN_NUM_DI_DI + CN_NUM_GOOUT; i++)
	{
		HalIoCell* Obj = Board->GetIoCell(i);
		// 暂不使用该方案
		//SptGooseDataOut* blOut = (SptGooseDataOut*)Obj;
		//if ((Obj)&&(blOut->GoType() == E_GOSV_BOOL))
		if (Obj)
		{
			row = wnd.CreatRow();
			if (row)
			{
				row->SetName(Obj->Name(), HmiGooseOutSSim);
				st64value* value = row->GetDataSur(0);
				value->value.vptr = Obj;
			}
		}
	}
	wnd.Edit();
	return 1;
}
int32 HmiGooseOutDSim(bool8& isDataChange, struct HmiGridWndDataMapCell* Cell)
{
	HalIoCell* Obj = (HalIoCell*)Cell->dataSur.value.vptr;
	SptGooseDataOut* blOut = (SptGooseDataOut*)Obj;
	if (blOut->VNode().dataType == E_GOSV_DPOS)
	{
		blOut->blSignalForce(1);
		uint8 value = blOut->Value().value.u8;
		blOut->ForceSetValue((~value & 0x3), 0, 0);
		String100B str;
		str << Obj->Name() << "传动中";
		ApiWarnDialog wd(str.Str(), 0, 0, 0, 0);
		wd.Show();
		blOut->ForceSetValue(value, 0, 0);
		blOut->blSignalForce(0);
		uint16 wNo = blOut - (SptGooseDataOut*)GoDpPosOutCell;
		AppEventOptValueRef(EN_OPT_DEBUG_GO_Dp, wNo, 0, 0);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "GOOSE双点传动", "GOOSE双点传动完成", blOut->Name(), 0, 0);
	}
	// 非发布信号不进行实质的传动
	else if (blOut->VNode().dataType == E_GOSV_NULL)
	{
		ApiWarnDialog wd(Obj->Name(), "信号未发布", 0, 0, 0);
		wd.Show();
	}
	// 发布类型错误
	else
	{
		ApiWarnDialog wd(Obj->Name(), "发布类型不匹配", 0, 0, 0);
		wd.Show();
	}
	return 0;
}

bool8 HmiGooseOutDSim(ApiMenu* Menu)
{
	if (LcdOperationConfirmationAccountInfo(Menu) == 0)
	{
		return 0;
	}
	ApiHmiGridWnd wnd;
	wnd.SetInfo("GOOSE双点出口调试", 0, 0);
	HmiGridWndDataMapRow* row;
	SptGooseFrameOut* Board = (SptGooseFrameOut*)&GoOutFrame[0];
	//uint32 num = Board->InstNum();
	for (uint32 i = 0; i < CN_NUM_DPI; i++)
	{
		HalIoCell* Obj = Board->GetIoCell(i + CN_NUM_DI_DI + CN_NUM_GOOUT);
		//SptGooseDataOut* blOut = (SptGooseDataOut*)Obj;
		//if ((Obj)&&(blOut->GoType() == E_GOSV_DPOS))
		if (Obj)
		{
			row = wnd.CreatRow();
			if (row)
			{
				row->SetName(Obj->Name(), HmiGooseOutDSim);
				st64value* value = row->GetDataSur(0);
				value->value.vptr = Obj;
			}
		}
	}
	wnd.Edit();
	return 1;
}
int32 HmiGooseOutDcSim(bool8& isDataChange, struct HmiGridWndDataMapCell* Cell)
{
	HalIoCell* Obj = (HalIoCell*)Cell->dataSur.value.vptr;
	SptGooseDataOut* blOut = (SptGooseDataOut*)Obj;
	if (blOut->VNode().dataType == E_GOSV_INT32)
	{
		blOut->blSignalForce(1);
		uint32 value = blOut->Value().value.u32;
		blOut->ForceSetValue(1000, 0, 0);
		String100B str;
		str << Obj->Name() << "传动中";
		ApiWarnDialog wd(str.Str(), 0, 0, 0, 0);
		wd.Show();
		blOut->ForceSetValue(value, 0, 0);
		blOut->blSignalForce(0);
		uint16 wNo = blOut - (SptGooseDataOut*)GoDcOutCell;
		AppEventOptValueRef(EN_OPT_DEBUG_GO_DC, wNo, 0, 0);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "GOOSE直流传动", "GOOSE直流传动完成", blOut->Name(), 0, 0);
	}
	else if (blOut->VNode().dataType == E_GOSV_FLOAT32)
	{
		blOut->blSignalForce(1);
		uint32 value = blOut->Value().value.u32;
		blOut->ForceSetValue(0x447A0000, 0, 0);
		String100B str;
		str << Obj->Name() << "传动中";
		ApiWarnDialog wd(str.Str(), 0, 0, 0, 0);
		wd.Show();
		blOut->ForceSetValue(value, 0, 0);
		blOut->blSignalForce(0);
		uint16 wNo = blOut - (SptGooseDataOut*)GoDcOutCell;
		AppEventOptValueRef(EN_OPT_DEBUG_GO_DC, wNo, 0, 0);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "GOOSE直流传动", "GOOSE直流传动完成", blOut->Name(), 0, 0);
	}
	// 非发布信号不进行实质的传动
	else if (blOut->VNode().dataType == E_GOSV_NULL)
	{
		ApiWarnDialog wd(Obj->Name(), "信号未发布", 0, 0, 0);
		wd.Show();
	}
	// 发布类型错误
	else
	{
		ApiWarnDialog wd(Obj->Name(), "发布类型不匹配", 0, 0, 0);
		wd.Show();
	}
	return 0;
}

bool8 HmiGooseOutDcSim(ApiMenu* Menu)
{
	if (LcdOperationConfirmationAccountInfo(Menu) == 0)
	{
		return 0;
	}

	ApiHmiGridWnd wnd;
	wnd.SetInfo("GOOSE模拟量出口调试", 0, 0);
	HmiGridWndDataMapRow* row;
	SptGooseFrameOut* Board = (SptGooseFrameOut*)&GoOutFrame[0];
	//uint32 num = Board->InstNum();
	for (uint32 i = 0; i < CN_NUM_DC; i++)
	{
		HalIoCell* Obj = Board->GetIoCell(i + CN_NUM_DI_DI + CN_NUM_GOOUT + CN_NUM_DPI);
		if (Obj)
		{
			row = wnd.CreatRow();
			if (row)
			{
				row->SetName(Obj->Name(), HmiGooseOutDcSim);
				st64value* value = row->GetDataSur(0);
				value->value.vptr = Obj;
			}
		}
	}
	wnd.Edit();
	return 1;
}

int32 HmiLedSim(bool8& isDataChange, struct HmiGridWndDataMapCell* Cell)
{
	HalIoCell* Obj = (HalIoCell*)Cell->dataSur.value.vptr;
	HmiLed* blOut = (HmiLed*)Obj;
	blOut->blSignalForce(1);
	bool8 value = blOut->Value();
	blOut->ForceSetValue(!value);
	String100B str;
	str << Obj->Name() << "传动中";
	ApiWarnDialog wd(str.Str(), 0, 0, 0, 0);
	wd.Show();
	blOut->ForceSetValue(value);
	blOut->blSignalForce(0);
	uint16 wNo = blOut - (HmiLed*)hmiLed;
	AppEventOptValueRef(EN_OPT_DEBUG_LED, wNo, 0, 0);

	//if(LogInUsr)
	//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), "指示灯传动", "指示灯传动完成", blOut->Name(), 0, 0);
	return 0;
}
bool8 HmiLedSim(ApiMenu* Menu)
{

	ApiHmiGridWnd wnd;
	wnd.SetInfo("指示灯调试", 0, 0);
	HmiGridWndDataMapRow* row;
	HmiLedGroup* Board = (HmiLedGroup*)&hmiLedGroup;
	uint32 num = Board->InstNum();
	for (uint16 i = 0; i < num; i++)
	{
		HmiLed* Obj = Board->GetObject(i);
		if (Obj)
		{
			row = wnd.CreatRow();
			row->SetName(Obj->Name(), HmiLedSim);
			st64value* value = row->GetDataSur(0);
			value->value.vptr = Obj;
		}
	}
	wnd.Edit();
	return 1;
}
bool8 HmiLedFlowWaterSim(ApiMenu* Menu)
{
	if (LcdOperationConfirmationAccountInfo(Menu) == 0)
	{
		return 0;
	}
	HmiLedGroup* Board = (HmiLedGroup*)&hmiLedGroup;
	uint32 num = Board->InstNum();
	ApiSelectDialog sel("进行自动流水传动?", 0, 0, 0, 0);
	bool8 res = (sel.Show() == 0);
	if (res)
	{
		for (uint16 i = 0; i < num; i++)
		{
			HmiLed* blOut = Board->GetObject(i);
			if (blOut)
			{
				blOut->blSignalForce(1);
				bool8 value = blOut->Value();
				blOut->ForceSetValue(!value);
				String100B str;
				str << blOut->Name() << "传动中";
				ApiInfoDialog wd(str.Str(), 0, 0, 0, 0);
				wd.Show();
				MsSleep(4000);
				blOut->ForceSetValue(value);
				blOut->blSignalForce(0);
			}
		}
		AppEventOptValueRef(EN_OPT_DEBUG_LED, 0xffff, 0, 0);
		//if(LogInUsr)
		//SjSystemRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "指示灯流水传动完成", 0, 0, 0);
		return 0;
	}
	else
	{
		HmiLedSim(Menu);
	}
	return 1;
}

bool8 HmiSendFile2SubBoard(ApiMenu* Menu)
{
	//传输账户文件
	String100B surstr;
	String100B dststr;
	surstr << CN_STATUS_FILE_ROOT << CN_FILE_DivFlag << "user.sta";//源文件
	dststr << CN_STATUS_FILE_ROOT << CN_FILE_DivFlag << "user.sta";//目的文件
	AppSendFile2SubBoard(surstr.Str(), dststr.Str(), DispProcess);
	surstr.Clear();
	dststr.Clear();
	surstr << CN_PARA_FILE_ROOT << CN_FILE_DivFlag << "user.dat";//源文件
	dststr << CN_PARA_FILE_ROOT << CN_FILE_DivFlag << "user.dat";//目的文件
	AppSendFile2SubBoard(surstr.Str(), dststr.Str(), DispProcess);
	DispPressAnyKey();
	return 1;
}
bool8 HmiSptCmmState(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd;
	wnd.SetInfo("进程间通信状态", 0, 0);
	uint8 col = 1;
	class FpgaMsgProc* fpgaProc = SptSampIntMsgProc::Instance().FpgaMsgProc();
	if (fpgaProc)
	{
		struct HmiGridWndDataMapRow* row = wnd.CreatRow();
		row->SetName("中断快速信息");

		row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
		row->SetColData(col, &fpgaProc->SampIntRecvMsg().RecvMsgNum);
		col++;
		row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
		row->SetColData(col, &fpgaProc->SampIntRecvMsg().SendMsgNum);
		col++;

		row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
		row->SetColData(col, &fpgaProc->SampIntSendMsg().RecvMsgNum);
		col++;
		row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
		row->SetColData(col, &fpgaProc->SampIntSendMsg().SendMsgNum);
		col++;

		row = wnd.CreatRow();
		col = 1;
		row->SetName("中断慢速信息");
		row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
		row->SetColData(col, &fpgaProc->SlowTaskRecvMsg().RecvMsgNum);
		col++;
		row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
		row->SetColData(col, &fpgaProc->SlowTaskRecvMsg().SendMsgNum);
		col++;
		row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
		row->SetColData(col, &fpgaProc->SlowTaskSendMsg().RecvMsgNum);
		col++;
		row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
		row->SetColData(col, &fpgaProc->SlowTaskSendMsg().SendMsgNum);
		col++;

		InstObjectRoot& introot = InstObjectRoot::Instance();
		InstObjectGroupParent* groupP = introot.GetGroupParent(EIOT_HalIo);

		if (groupP)
		{
			InstObjectGroup* g;
			HalBoard* Board;
			uint32 num = groupP->InstNum();
			for (uint32 i = 0; i < num; i++)
			{
				g = groupP->GetGroup(i);
				if (g && (g->InstObjectType() == EIOT_HalIo))
				{
					Board = (HalBoard*)g;
					const HalBoard::stOutStatus& st = Board->OutStatus();

					row = wnd.CreatRow();
					col = 1;
					row->SetName(Board->Name());
					row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
					row->SetColData(col, &st.recvFrameOkCnt);
					col++;
					row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
					row->SetColData(col, &st.recvFrameErrCnt);
					col++;
					row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
					row->SetColData(col, &st.sendFrameOkCnt);
					col++;
					row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
					row->SetColData(col, &st.sendFrameErrCnt);
					col++;
				}
			}
		}
		SalCmmChannel* cnn = (SalCmmChannel*)&HmiLcdCmm::Instance().Tcp();
		row = wnd.CreatRow();
		col = 1;
		row->SetName(cnn->Name());
		row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
		row->SetColData(col, &cnn->OutPut().recvCnt);
		col++;
		row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
		row->SetColData(col, &cnn->OutPut().recvErrCnt);
		col++;
		row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
		row->SetColData(col, &cnn->OutPut().sendCnt);
		col++;
		row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
		row->SetColData(col, &cnn->OutPut().sendErrCnt);
		col++;

		cnn = (SalCmmChannel*)&ApiAppFastCmm::Instance();
		row = wnd.CreatRow();
		col = 1;
		row->SetName(cnn->Name());
		row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
		row->SetColData(col, &cnn->OutPut().recvCnt);
		col++;
		row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
		row->SetColData(col, &cnn->OutPut().recvErrCnt);
		col++;
		row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
		row->SetColData(col, &cnn->OutPut().sendCnt);
		col++;
		row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
		row->SetColData(col, &cnn->OutPut().sendErrCnt);
		col++;

		int32 DrivNum = cnn->DriverNum();

		CmmMsgDriver* Driver;

		for (int32 i = 0; i < DrivNum; i++)
		{
			Driver = cnn->Driver(i);
			if (!Driver)
			{
				break;
			}
			row = wnd.CreatRow();
			col = 1;
			row->SetName(Driver->Name);
			row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
			row->SetColData(col, &Driver->RecvMsgCnt);
			col++;
			row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
			row->SetColData(col, &Driver->SendMsgCnt);
			col++;
		}

		int32 ChNum = SptAppCmmTask::Instance().CmmChannelNum();
		for (int32 i = 0; i < ChNum; i++)
		{
			cnn = SptAppCmmTask::Instance().CmmChannel(i);
			if (!cnn)
			{
				break;
			}
			row = wnd.CreatRow();
			col = 1;
			row->SetName(cnn->Name());
			row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
			row->SetColData(col, &cnn->OutPut().recvCnt);
			col++;
			row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
			row->SetColData(col, &cnn->OutPut().recvErrCnt);
			col++;
			row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
			row->SetColData(col, &cnn->OutPut().sendCnt);
			col++;
			row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
			row->SetColData(col, &cnn->OutPut().sendErrCnt);
			col++;

			DrivNum = cnn->DriverNum();

			for (int32 i = 0; i < DrivNum; i++)
			{
				Driver = cnn->Driver(i);
				if (!Driver)
				{
					break;
				}
				row = wnd.CreatRow();
				col = 1;
				row->SetName(Driver->Name);
				row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
				row->SetColData(col, &Driver->RecvMsgCnt);
				col++;
				row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
				row->SetColData(col, &Driver->SendMsgCnt);
				col++;
			}
		}
		ChNum = SptPublicCmmTask::Instance().CmmChannelNum();
		for (int32 i = 0; i < ChNum; i++)
		{
			cnn = SptPublicCmmTask::Instance().CmmChannel(i);
			if (!cnn)
			{
				break;
			}
			row = wnd.CreatRow();
			col = 1;
			row->SetName(cnn->Name());
			row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
			row->SetColData(col, &cnn->OutPut().recvCnt);
			col++;
			row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
			row->SetColData(col, &cnn->OutPut().recvErrCnt);
			col++;
			row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
			row->SetColData(col, &cnn->OutPut().sendCnt);
			col++;
			row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
			row->SetColData(col, &cnn->OutPut().sendErrCnt);
			col++;

			DrivNum = cnn->DriverNum();

			for (int32 i = 0; i < DrivNum; i++)
			{
				Driver = cnn->Driver(i);
				if (!Driver)
				{
					break;
				}
				row = wnd.CreatRow();
				col = 1;
				row->SetName(Driver->Name);
				row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
				row->SetColData(col, &Driver->RecvMsgCnt);
				col++;
				row->SetColDataCfg(col, 0, E_SVT_U32 | E_SVT_PTR, 10, 0);
				row->SetColData(col, &Driver->SendMsgCnt);
				col++;
			}
		}
	}
	wnd.Show();
	return 1;
}
