#include "InstResource.h"

bool8 EnterDebugMode(ApiMenu* Menu)
{
	ApiIoGlobalFlag::Instance().SetUnitDebugState(1);
	return 1;
}

bool8 ExitDebugMode(ApiMenu* Menu)
{
	ApiIoGlobalFlag::Instance().SetUnitDebugState(0);
	return 1;
}

bool8 Boot0Update(ApiMenu* Menu)
{
	String100B str;
	str << CN_UPDATE_FILE_ROOT;
	str << FilePath::DivFlag << "Sylix.Boot0.bin";
	UpdateBoot0ForLcd(str.Str(), DispProcess);
	DispPressAnyKey();
	return 1;
}

bool8 UbootUpdate(ApiMenu* Menu)
{
	String100B str;
	str << CN_UPDATE_FILE_ROOT;
	str << FilePath::DivFlag << "Sylix.UBoot.bin";
	UpdateUBootForLcd(str.Str(), DispProcess);
	DispPressAnyKey();
	return 1;
}

bool8 OsUpdate(ApiMenu* Menu)
{
	String100B str;
	str << CN_UPDATE_FILE_ROOT;
	str << FilePath::DivFlag << "Sylix.T3BSP.bin";
	UpdateOsForLcd(str.Str(), DispProcess);
	DispPressAnyKey();
	return 1;
}
bool8 Boot0Update1(ApiMenu* Menu)
{
	String100B str;
	str << CN_UPDATE1_FILE_ROOT;
	str << FilePath::DivFlag << "Sylix.Boot0.bin";
	UpdateBoot0ForLcd(str.Str(), DispProcess);
	DispPressAnyKey();
	return 1;
}

bool8 UbootUpdate1(ApiMenu* Menu)
{
	String100B str;
	str << CN_UPDATE1_FILE_ROOT;
	str << FilePath::DivFlag << "Sylix.UBoot.bin";
	UpdateUBootForLcd(str.Str(), DispProcess);
	DispPressAnyKey();
	return 1;
}

bool8 OsUpdate1(ApiMenu* Menu)
{
	String100B str;
	str << CN_UPDATE1_FILE_ROOT;
	str << FilePath::DivFlag << "Sylix.T3BSP.bin";
	UpdateOsForLcd(str.Str(), DispProcess);
	DispPressAnyKey();
	return 1;
}

bool8 FlashBak(ApiMenu* Menu)
{
	BakUpFlashForLcd(DispProcess);
	DispPressAnyKey();
	return 1;
}
bool8 RestoreFlashPara(ApiMenu* Menu)
{
	RestoreFlashPara(DispProcess);
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

bool8 DefaultProtSetPara(ApiMenu* Menu)
{
	ApiSelectDialog sd("默认保护定值？", 0, 0, 0, 0);
	int32 res = sd.Show();
	if (res == 0)
	{
		int32 res = ProtParaGroup.DefaultData();
		res = ProtParaGroup.CheckStatus();
		if (res != SalParaGroup::E_OK)
		{
			ApiWarnDialog wd("默认失败", 0, 0, 0, 0);
			wd.Show();
		}
		else
		{
			ApiWarnDialog wd("默认完成", 0, 0, 0, 0);
			wd.Show();
		}
	}
	return 1;
}

bool8 UpdateFpga1(ApiMenu* Menu)
{
	String100B str;
	str = CN_UPDATE_FILE_ROOT;
	str << FilePath::DivFlag << "FPGA1.bin";
	GzkFpgaUpdate update(str.Str(), 5 * 1024 * 1024, 0x0001, 512, 0);
	update.Run(DispProcess);
	DispPressAnyKey();
	return 1;
}

bool8 UpdateFpga2(ApiMenu* Menu)
{
	String100B str;
	str = CN_UPDATE_FILE_ROOT;
	str << FilePath::DivFlag << "FPGA2.bin";
	GzkFpgaUpdate update(str.Str(), 5 * 1024 * 1024, 0x0002, 512, 0);
	update.Run(DispProcess);
	DispPressAnyKey();
	return 1;
}

bool8 UpdateFpga3(ApiMenu* Menu)
{
	String100B str;
	str = CN_UPDATE_FILE_ROOT;
	str << FilePath::DivFlag << "FPGA3.bin";
	GzkFpgaUpdate update(str.Str(), 5 * 1024 * 1024, 0x0004, 512, 0);
	update.Run(DispProcess);
	DispPressAnyKey();
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
	return 0;
}
bool8 HmiDoOutSim(ApiMenu* Menu)
{
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
				row->SetName(Obj->Name(), HmiDoOutSim);
				st64value* value = row->GetDataSur(0);
				value->value.vptr = Obj;
			}
		}
	}
	wnd.Edit();
	return 1;
}
int32 HmiGooseOutSim(bool8& isDataChange, struct HmiGridWndDataMapCell* Cell)
{
	HalIoCell* Obj = (HalIoCell*)Cell->dataSur.value.vptr;
	SptGooseDataOut* blOut = (SptGooseDataOut*)Obj;
	blOut->blSignalForce(1);
	bool8 value = blOut->Value().value.bl;
	if (blOut->VNode().dataType == E_GOSV_BOOL)
	{
		blOut->ForceSetValue(!value, 0, 0);
		String100B str;
		str << Obj->Name() << "传动中";
		ApiWarnDialog wd(str.Str(), 0, 0, 0, 0);
		wd.Show();
		blOut->ForceSetValue(value, 0, 0);
	}

	blOut->blSignalForce(0);
	return 0;
}
bool8 HmiGooseOutSim(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd;
	wnd.SetInfo("GOOSE出口调试", 0, 0);
	HmiGridWndDataMapRow* row;
	for (uint32 j = 0; j < M_ArrLen(GoOutFrame); j++)
	{
		SptGooseFrameOut* Board = (SptGooseFrameOut*)&GoOutFrame[j];
		uint32 num = Board->InstNum();
		for (uint32 i = 0; i < num; i++)
		{
			HalIoCell* Obj = Board->GetIoCell(i);
			if (Obj)
			{
				row = wnd.CreatRow();
				row->SetName(Obj->Name(), HmiGooseOutSim);
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
	return 0;
}
bool8 HmiLedSim(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd;
	wnd.SetInfo("Led调试", 0, 0);
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
				MsSleep(2000);
				blOut->ForceSetValue(value);
				blOut->blSignalForce(0);
			}
		}
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
