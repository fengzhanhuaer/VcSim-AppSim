#include"ApiProject.h"
using namespace spt;

void spt::SalFwWaveCfgCell::PowerUpIni(const char* Name, const char* DesName, class SalFwRecordGroup* Group, uint32 CfgType, uint32 Flag)
{
	InstObject::PowerUpIni(Name, DesName, Group, EIOT_FrRecord, Group->InstId(), Group->InstNum());
	cfgType = CfgType;
	flags.u32 = Flag;
	fwGroup = Group;
	groupSampWriter = &Group->RtData().SampWriter;
	groupSampBufLen = &Group->RtData().MaxSampPoint;
	Group->RgsCfgCell(this);
}
void spt::SalFwWaveCfgCell::SetDisp(bool8 Disp)
{
	isDisp = Disp;
}
bool8 spt::SalFwWaveCfgCell::IsDisp()
{
	return isDisp;
}
void spt::SalFaultInfo::PowerUpIni(const char* Name, const char* DesName, class SalFwRecordGroup* Group, const VarUnits& Units)
{
	SalFwWaveCfgCell::PowerUpIni(Name, DesName, Group, E_FaultInfo, 0);
	units = &Units;
}

void spt::SalFaultInfo::Update(uint8 Act, int32 Value)
{
	if (Act != isAct)
	{
		isAct = Act;
		value.value.i32 = Value;
	}
}
void spt::SalFwAnalogCfgSignal::PowerUpIni(const char* Name, const char* DesName, class SalFwRecordGroup* Group, E_Ang_Phase Phase, const char* Ccbm, const VarUnits& Units, float32 Skew, float32 CoeA, float32 CoeB, float32 Primary, float32 Secondary, bool8 IsPrimary, uint32 Flag, bool8 IsDisp)
{
	SalFwWaveCfgCell::PowerUpIni(Name, DesName, Group, E_Analog, Flag);
	units = &Units;
	phase = Phase;
	ccbm = Ccbm;
	units = &Units;
	skew = Skew;
	coeA = CoeA;
	coeB = CoeB;
	primary = Primary;
	secondary = Secondary;
	isPrimary = IsPrimary;
	isDisp = IsDisp;
	sampBuf = Group->RtData().GetU32Buf(angId);
	if (!sampBuf)
	{
		LogErr.Stamp() << "SalFwAnalogCfgSignal::PowerUpIni  Alloc Err.\n";
		SptApiStatus[E_SAS_RamAllocErr].Update(1);
	}
}

void spt::SalFwAnalogCfgSignal::SetCoePS(float32 Primary, float32 Secondary)
{
	primary = Primary;
	secondary = Secondary;
}

void spt::SalFwAnalogCfgSignal::SetCoeAB(float32 CoeA, float32 CoeB)
{
	coeA = CoeA;
	coeB = CoeB;
}

void spt::SalFwAnalogCfgSignal::SetValue(float32 Value)
{
	value.value.f32 = sampBuf[*groupSampWriter].f32 = Value;
}

void spt::SalFwAnalogCfgSignal::Update2Buf()
{
	sampBuf[*groupSampWriter].f32 = value.value.f32;
}

void spt::SalFwDigitalCfgSignal::PowerUpIni(const char* Name, const char* DesName, class SalFwRecordGroup* Group, E_Ang_Phase Phase, const char* Ccbm, bool8 SteadyState, uint32 Flag, uint16 UpBeforeSetCnt, uint16 UpAfterSetCnt, uint16 DownBeforeSetCnt, uint16 DownAfterSetCnt, bool8 IsDisp)
{
	SalFwWaveCfgCell::PowerUpIni(Name, DesName, Group, E_Digital, Flag);
	phase = Phase;
	ccbm = Ccbm;
	steadyState = SteadyState;
	isDisp = IsDisp;
	if (Group->UpBeforeSetCnt() < UpBeforeSetCnt)
	{
		UpBeforeSetCnt = Group->UpBeforeSetCnt();
	}
	if (Group->UpBeforeSetCnt() < DownBeforeSetCnt)
	{
		DownBeforeSetCnt = Group->UpBeforeSetCnt();
	}
	upBeforeSetCnt = UpBeforeSetCnt;
	upAfterSetCnt = UpAfterSetCnt;
	downBeforeSetCnt = DownBeforeSetCnt;
	downAfterSetCnt = DownAfterSetCnt;
	sampBuf = Group->RtData().GetDigBuf(digId);
	if (!sampBuf)
	{
		LogErr.Stamp() << "SalFwDigitalCfgSignal::PowerUpIni  Alloc Err.\n";
		SptApiStatus[E_SAS_RamAllocErr].Update(1);
	}
}

void spt::SalFwDigitalCfgSignal::SetValue(uint32 Value)
{
	value.value.u32 = (Value & 1);
}

void spt::SalFwDigitalCfgSignal::Update2Buf()
{
	sampBuf[*groupSampWriter] = value.value.u32;
}

void spt::SalFwEventCfgSignal::PowerUpIni(const char* Name, const char* DesName, SalEvent* Event, class SalFwRecordGroup* Group, E_Ang_Phase Phase, const char* Ccbm, bool8 SteadyState, uint32 Flag, uint16 UpBeforeSetCnt, uint16 UpAfterSetCnt, uint16 DownBeforeSetCnt, uint16 DownAfterSetCnt, bool8 IsDisp)
{
	SalFwWaveCfgCell::PowerUpIni(Name, DesName, Group, E_Event, Flag);
	phase = Phase;
	ccbm = Ccbm;
	steadyState = SteadyState;
	isDisp = IsDisp;
	pEvent = Event;
	if (Group->UpBeforeSetCnt() < UpBeforeSetCnt)
	{
		UpBeforeSetCnt = Group->UpBeforeSetCnt();
	}
	if (Group->UpBeforeSetCnt() < DownBeforeSetCnt)
	{
		DownBeforeSetCnt = Group->UpBeforeSetCnt();
	}
	upBeforeSetCnt = UpBeforeSetCnt;
	upAfterSetCnt = UpAfterSetCnt;
	downBeforeSetCnt = DownBeforeSetCnt;
	downAfterSetCnt = DownAfterSetCnt;
	sampBuf = Group->RtData().GetDigBuf(digId);
	if (!sampBuf)
	{
		LogErr.Stamp() << "SalFwDigitalCfgSignal::PowerUpIni  Alloc Err.\n";
		SptApiStatus[E_SAS_RamAllocErr].Update(1);
	}
}
void spt::SalFwEventCfgSignal::SetValue(uint32 Value)
{
	SalFwDigitalCfgSignal::SetValue(Value);
}
bool8 spt::SalFwEventCfgSignal::UpdateFromEvent()
{
	uint8 v = ((uint8)(pEvent->Data().status.u32) == 1);
	if (v != value.value.u32)
	{
		value.value.u32 = v;
		return flags.st.isEvent;
	}
	return 0;
}
void spt::SalFwRecordGroup::PowerUpIni(const char* Name, const char* DesName, uint32 SysFreq, uint32 SampPerCircle, int32 MaxRecordPoint, uint16 UpBeforeSetCnt, uint16 UpAfterSetCnt, uint16 FwAngMaxNum, uint16 FwDigMaxNum, uint16 FwProtMaxNum, uint16 HdrFaultInfoMaxNum, uint16 HdrDigMaxNum, uint16 MidAngMaxNum, uint16 MidDigMaxNum, uint32 Flag)
{
	if (!SptMain::Instance().AppCfg())
	{
		return;
	}
	sysFreq = SysFreq;
	sampPerCircle = SampPerCircle;
	MaxRecordPoint = (MaxRecordPoint == 0 ? 1 : MaxRecordPoint);
	MaxRecordPoint = (MaxRecordPoint + 3) / 4;
	MaxRecordPoint = (MaxRecordPoint) * 4;
	maxRecSampPoint = MaxRecordPoint;
	rtData.SampWriter = 0;
#ifdef WIN32_SIM
	rtData.MaxSampPoint = sysFreq * sampPerCircle * 10;
#else
	rtData.MaxSampPoint = sysFreq * sampPerCircle;
#endif // !WIN32_SIM
	FwAngMaxNum = (FwAngMaxNum == 0 ? 1 : FwAngMaxNum);
	FwDigMaxNum = (FwDigMaxNum == 0 ? 1 : FwDigMaxNum);
	rtData.MaxSampPoint = (rtData.MaxSampPoint == 0 ? 1 : rtData.MaxSampPoint);
	rtData.AngCellNum = FwAngMaxNum;
	rtData.DigCellNum = FwDigMaxNum;
	upBeforeSetCnt = UpBeforeSetCnt;
	upAfterSetCnt = UpAfterSetCnt;
	flags.u32 = Flag;
	isStartRecord = isStartRecordLast = allocErr = 0;
	rtIntFwData = 0;
	InstObjectGroup::PowerUpIni(Name, DesName, (uint16)EIOT_FrRecord, FwAngMaxNum + FwDigMaxNum);
	fwCfg.PowerUpIni(FwAngMaxNum, FwDigMaxNum, FwProtMaxNum, HdrFaultInfoMaxNum, HdrDigMaxNum, MidAngMaxNum, MidDigMaxNum);
	rtData.Header = (SalFwSampData1PointHeader*)Calloc(1, sizeof(SalFwSampData1PointHeader) * rtData.MaxSampPoint);
	rtData.U32SampBuf = (u32value*)Calloc(1, sizeof(u32value) * rtData.MaxSampPoint * FwAngMaxNum);
	rtData.DigSampBuf = (bool8*)Calloc(1, sizeof(bool8) * rtData.MaxSampPoint * FwDigMaxNum);
	if ((!rtData.Header) || (!rtData.U32SampBuf) || (!rtData.DigSampBuf))
	{
		allocErr = 1;
		LogErr.Stamp() << "SalFwRecordGroup::MallocDataBuf fwData Alloc Err.\n";
		SptApiStatus[E_SAS_RamAllocErr].Update(1);
	}
	for (uint32 i = 0; i < MaxRecordFwRamData; i++)
	{
		fwData[i] = MallocDataBuf();
	}
	hmiViewData = MallocDataBuf();
	cmmViewData = MallocDataBuf();
	printViewData = MallocDataBuf();
	LoadHdrData();
	LoadFwData();
	if (Access(CN_T860_COMTRADE_FILE_ROOT, 0) < 0)
	{
		MkDir(CN_T860_COMTRADE_FILE_ROOT);
	}
}

int32 spt::SalFwRecordGroup::RgsCfgCell(SalFwWaveCfgCell* Cfg)
{
	return fwCfg.RgsCfgCell(Cfg);
}

void spt::SalFwRecordGroup::RecordOnePoint(SalDateStamp& stamp, uint64 SampStamp)
{
	if (allocErr)
	{
		return;
	}
	rtData.SampUtc = stamp;
	uint32 nowms = SptMsInt::Instance().MsCnt32();
	rtData.SampStamp = SampStamp;
	bool8 isrecord = isStartRecord || isStartRecordLast;
	if (isStartRecord)
	{
		if (isStartRecordLast)
		{
			rtIntFwData->RecordContinueCnt++;
		}
		else
		{
			uint8 w = savedFlag.fwWriter % MaxRecordFwRamData;
			rtIntFwData = fwData[w];
			rtIntFwData->StatusClear();
			rtIntFwData->RecordStartWriter = rtData.SampWriter;
			rtIntFwData->TrigT = stamp;
			rtIntFwData->ActStartTimeMs = nowms;
			rtIntFwData->RecordState = rtIntFwData->E_StartRec;
			rtIntFwData->SaveState = 0;
			rtIntFwData->RecordContinueCnt = 1;
			rtIntFwData->CheckContinueCnt = 0;
			savedFlag.fwWriter = (w + 1) % MaxRecordFwRamData;
		}
	}
	else
	{
		if (isStartRecordLast)
		{
			rtIntFwData->RecordEndWriter = rtData.SampWriter;
			rtIntFwData->RecordState |= rtIntFwData->E_EndRec;
		}
	}
	uint32 w = (rtData.SampWriter) % rtData.MaxSampPoint;
	SalFwSampData1PointHeader& point = rtData.Header[w];
	point.SampSerNo = rtData.SampSerNo;
	point.SampUtc = rtData.SampUtc;
	point.SampStamp = rtData.SampStamp;
	point.RecContinueCnt = 0;
	SalFwActCfgArray& actCfg = fwCfg.ActEvent();
	uint32 actNum = actCfg.InstNum();
	if (rtIntFwData && isrecord)
	{
		for (uint32 i = 0; i < actNum; i++)
		{
			if (actCfg.GetCfg(i)->UpdateFromEvent())
			{
				if ((rtIntFwData->EventWriter) < MaxEventRamData)
				{
					rtIntFwData->Event[rtIntFwData->EventWriter].EverntSerNo = rtIntFwData->EventWriter;
					rtIntFwData->Event[rtIntFwData->EventWriter].EventData = actCfg.GetCfg(i)->Event().Data();
					rtIntFwData->Event[rtIntFwData->EventWriter].ActTimeMs = nowms - rtIntFwData->ActStartTimeMs;
					rtIntFwData->EventWriter++;
				}
			}
		}
	}
	else
	{
		for (uint32 i = 0; i < actNum; i++)
		{
			actCfg.GetCfg(i)->UpdateFromEvent();
		}
	}
	SalFwAnalogCfgArray& angcfg = fwCfg.AngCfg();
	uint32 angnum = angcfg.InstNum();
	for (uint32 i = 0; i < angnum; i++)
	{
		angcfg.GetCfg(i)->Update2Buf();
	}
	SalFwDigitalCfgArray& digcfg = fwCfg.DigCfg();
	uint32 dignum = digcfg.InstNum();
	for (uint32 i = 0; i < dignum; i++)
	{
		digcfg.GetCfg(i)->Update2Buf();
	}
	rtData.SampSerNo++;
	rtData.SampWriter = (w + 1) % rtData.MaxSampPoint;
	isStartRecordLast = isStartRecord;
}

void spt::SalFwRecordGroup::SetActType(uint32 Type)
{
	if (rtIntFwData)
	{
		rtIntFwData->ActType = (uint8)Type;
	}
}

int32 spt::SalFwRecordGroup::LoadHdrData()
{
	SalFile file;
	file.Path().Set(CN_FWRECORD_FILE_ROOT);
	String100B str;
	str = desName;
	str << ".fwhdr";
	file.Name().Set(str.Str());
	file.OpenReadOnly();
	if (!file.IsOpened())
	{
		LogErr.Stamp() << str << " not exist\n";
		return -1;
	}
	stNeedSave needSave;
	file.Read(&needSave, sizeof(needSave));
	savedFlag.recordOverSerNo = needSave.recordOverSerNo % MaxRecordSerNo;
	savedFlag.fwWriter = needSave.fwWriter % MaxRecordSerNo;
	savedFlag.fwReader = needSave.fwWriter % MaxRecordSerNo;//未录波完成的波形不再继续生成
	return 0;
}

int32 spt::SalFwRecordGroup::SaveHdrData()
{
	savedFlag.version = 1;
	SalFile file;
	file.Path().Set(CN_FWRECORD_FILE_ROOT);
	String100B str;
	str = desName;
	str << ".fwhdr";
	file.Name().Set(str.Str());
	file.Creat();
	if (!file.IsOpened())
	{
		LogErr.Stamp() << str << "Creat Failed not\n";
		return -1;
	}
	file.Write(&savedFlag, sizeof(savedFlag));
	file.Close();
	return 0;
}

int32 spt::SalFwRecordGroup::LoadFwData()
{

	for (uint32 i = 0; i < MaxRecordFwRamData; i++)
	{
		if (fwData[i])
		{
			String500B str;
			str = CN_FWRECORD_FILE_ROOT;
			str << CN_FILE_DivFlag << desName;
			str.Format(i, 2, '0') << ".fwr";
			fwData[i]->LoadPriFile(str.Str());
		}
	}
	return 0;
}

void spt::SalFwRecordGroup::StartRecord(bool8 isStart)
{
	isStartRecord = isStart;
}

SalFwData* spt::SalFwRecordGroup::FwData(uint16 Index)
{
	if (Index >= MaxRecordFwRamData)
	{
		return 0;
	}
	return fwData[Index];
}

uint8 spt::SalFwRecordGroup::FwSerialNo()
{
	return savedFlag.recordOverSerNo;
}

uint8 spt::SalFwRecordGroup::FwSerialWriter()
{
	return savedFlag.fwWriter;
}

SalFwData* spt::SalFwRecordGroup::MallocDataBuf()
{
	SalFwData* pData = (SalFwData*)Calloc(1, sizeof(SalFwData));
	if (pData)
	{
		pData->MaxEventNum = MaxEventRamData;
		pData->MaxSampPoint = maxRecSampPoint;
		pData->CellPerSamp = rtData.AngCellNum + (rtData.DigCellNum + 31) / 32;
		pData->AngCellPerSamp = rtData.AngCellNum;
		pData->DigCellPerSamp = rtData.DigCellNum;
		pData->SaveRtReader = 0;
		pData->SaveRtCheckReader = 0;
		pData->SampWriter = 0;
		pData->EventWriter = 0;
#ifdef WIN32_SIM
		pData->DatFileType = pData->EFT_ASCII;
#else
		pData->DatFileType = pData->EFT_ASCII;
#endif
		if (pData->Malloc() < 0)
		{
			allocErr = 1;
			LogErr.Stamp() << "SalFwRecordGroup::MallocDataBuf pData->Malloc fwData Alloc Err.\n";
			SptApiStatus[E_SAS_RamAllocErr].Update(1);
		}
	}
	else
	{
		allocErr = 1;
		LogErr.Stamp() << "SalFwRecordGroup::MallocDataBuf fwData Alloc Err.\n";
		SptApiStatus[E_SAS_RamAllocErr].Update(1);
	}
	return pData;
}

const SalFwData* spt::SalFwRecordGroup::GetHmiViewDataByNo(uint32 SerialNo)
{
	if (!hmiViewData)
	{
		return 0;
	}
	for (uint32 i = 0; i < MaxRecordFwRamData; i++)
	{
		if (fwData[i]->RecordSerNo == SerialNo)
		{
			if (Copy(hmiViewData, fwData[i]))
			{
				return hmiViewData;
			}
		}
	}
	return 0;
}

const SalFwData* spt::SalFwRecordGroup::GetCmmViewDataByNo(uint32 SerialNo)
{
	if (!cmmViewData)
	{
		return 0;
	}
	for (uint32 i = 0; i < MaxRecordFwRamData; i++)
	{
		if (fwData[i]->RecordSerNo == SerialNo)
		{
			if (Copy(cmmViewData, fwData[i]))
			{
				return cmmViewData;
			}
		}
	}
	return 0;
}

const SalFwData* spt::SalFwRecordGroup::GetPrinterViewDataByNo(uint32 SerialNo)
{
	if (!printViewData)
	{
		return 0;
	}
	for (uint32 i = 0; i < MaxRecordFwRamData; i++)
	{
		if (fwData[i]->RecordSerNo == SerialNo)
		{
			if (Copy(printViewData, fwData[i]))
			{
				return printViewData;
			}
		}
	}
	return 0;
}

const SalFwData* spt::SalFwRecordGroup::GetHmiViewDataByIndex(uint32 Index)
{
	Index = (savedFlag.fwWriter + MaxRecordFwRamData - Index - 1) % MaxRecordFwRamData;
	if (Copy(hmiViewData, fwData[Index]))
	{
		return hmiViewData;
	}
	return 0;
}

const SalFwData* spt::SalFwRecordGroup::GetCmmViewDataByIndex(uint32 Index)
{
	Index = (savedFlag.fwWriter + MaxRecordFwRamData - Index - 1) % MaxRecordFwRamData;
	if (Copy(cmmViewData, fwData[Index]))
	{
		return cmmViewData;
	}
	return 0;
}

const SalFwData* spt::SalFwRecordGroup::GetPrinterViewDataByIndex(uint32 Index)
{
	Index = (savedFlag.fwWriter + MaxRecordFwRamData - Index - 1) % MaxRecordFwRamData;
	if (Copy(printViewData, fwData[Index]))
	{
		return printViewData;
	}
	return 0;
}

void spt::SalFwRecordGroup::Save2File()
{
	uint8 w = savedFlag.fwWriter;
	uint8 r = savedFlag.fwReader;
	if (w == r)
	{
		return;
	}
	r = (r) % MaxRecordFwRamData;
	SalFwData* dstData = fwData[r];
	if (!(dstData->RecordState & dstData->E_StartRec))
	{
		return;
	}
	if (dstData->SaveState & dstData->E_StartSave)
	{
		if (dstData->SaveState & dstData->E_EndSave)
		{
			if (dstData->SaveState & dstData->E_PriFileSaved)
			{
				if (dstData->SaveState & dstData->E_AllFileSaved)
				{
					savedFlag.recordOverSerNo = (savedFlag.recordOverSerNo + 1) % MaxRecordSerNo;
					savedFlag.fwReader = (savedFlag.fwReader + 1) % MaxRecordFwRamData;
					SaveHdrData();
				}
				else
				{
					SavePubFile(dstData);
				}
			}
			else
			{
				SavePrivateFile(dstData);
			}
		}
		else
		{
			uint32 cnt = sampPerCircle * 5;
			for (uint32 i = 0; i < cnt; i++)
			{
				if (CheckAndSave(dstData) < 0)
				{
					break;
				}
			}
		}
	}
	else
	{
		StartSaveData(dstData);
	}
}

void spt::SalFwRecordGroup::SavePrivateFile(SalFwData* Data)
{
	Data->Save2PriFile(desName, &fwCfg);
	Data->SaveState |= Data->E_PriFileSaved;
}

void spt::SalFwRecordGroup::SavePubFile(SalFwData* Data)
{
	if (!flags.st.isPrivate)
	{
		Data->Save2PubFile(desName, &fwCfg);
	}
	Data->SaveState |= Data->E_AllFileSaved;
}

int32 spt::SalFwRecordGroup::StartSaveData(SalFwData* DstData)
{
	if (DstData->RecordStartWriter == rtData.SampWriter)
	{
		return 0;
	}
	DstData->DeleteAllFile();
	DstData->SaveState = DstData->E_StartSave;
	DstData->SampWriter = 0;
	DstData->SaveRtCheckReader = DstData->RecordStartWriter % rtData.MaxSampPoint;
	DstData->SaveRtReader = (DstData->RecordStartWriter + rtData.MaxSampPoint - upBeforeSetCnt) % rtData.MaxSampPoint;
	DstData->ContinueSamp = upAfterSetCnt + upBeforeSetCnt;
	uint32 endLoop = DstData->MaxSampPoint;
	for (uint32 i = 0; i < endLoop; i++)
	{
		SalFwSampData1Point* p = DstData->PointAt(i);
		MemSet(p, 0, DstData->LenPerSamp);
	}
	DstData->CheckContinueCnt = 0;
	DstData->SysFreq = sysFreq;
	DstData->SampPerCircle = sampPerCircle;
	DstData->RecordSerNo = savedFlag.recordOverSerNo % MaxRecordSerNo;
	DstData->BufSerNo = savedFlag.fwReader % MaxRecordFwRamData;
	DstData->DatFileType = DstData->EFT_ASCII;
	return 0;
}

int32 spt::SalFwRecordGroup::CheckAndSave(SalFwData* DstData)
{
	if (DstData->SaveRtCheckReader == rtData.SampWriter)
	{
		return -1;
	}
	if (DstData->SaveState & DstData->E_CheckEnd)
	{
		uint32 r = (DstData->SaveRtReader) % rtData.MaxSampPoint;
		uint32 rbef = (DstData->SaveRtReader + rtData.MaxSampPoint - 1) % rtData.MaxSampPoint;
		uint32 raft = (DstData->SaveRtReader + 1) % rtData.MaxSampPoint;
		if (rtData.Header[r].SampSerNo != (rtData.Header[rbef].SampSerNo + 1))
		{
			return -1;
		}
		if (rtData.Header[raft].SampSerNo != (rtData.Header[r].SampSerNo + 1))
		{
			return -1;
		}
	}
	else
	{
		uint32 r = (DstData->SaveRtCheckReader) % rtData.MaxSampPoint;
		uint32 rbef = (DstData->SaveRtCheckReader + rtData.MaxSampPoint - 1) % rtData.MaxSampPoint;
		uint32 raft = (DstData->SaveRtCheckReader + 1) % rtData.MaxSampPoint;
		if (rtData.Header[r].SampSerNo != (rtData.Header[rbef].SampSerNo + 1))
		{
			return -1;
		}
		if (rtData.Header[raft].SampSerNo != (rtData.Header[r].SampSerNo + 1))
		{
			return -1;
		}
		//检测变位
		SalFwDigitalCfgArray& digcfg = fwCfg.DigCfg();
		uint32 dignum = digcfg.InstNum();
		for (uint32 i = 0; i < dignum; i++)
		{
			bool8* pdata = rtData.GetDigBuf(i);
			if (!pdata[r] && (pdata[rbef]))
			{
				SetContinueSaveCnt(r, digcfg.GetCfg(i)->DownBeforeSetCnt(), digcfg.GetCfg(i)->DownAfterSetCnt());
			}
			else if (pdata[r] && (!pdata[rbef]))
			{
				SetContinueSaveCnt(r, digcfg.GetCfg(i)->UpBeforeSetCnt(), digcfg.GetCfg(i)->UpAfterSetCnt());
			}
		}
		DstData->CheckContinueCnt++;
		if (DstData->RecordState & DstData->E_EndRec)
		{
			if (DstData->SaveRtCheckReader == DstData->RecordEndWriter)
			{
				DstData->SaveState |= DstData->E_CheckEnd;
			}
			else if (DstData->CheckContinueCnt >= DstData->RecordContinueCnt)
			{
				DstData->SaveState |= DstData->E_CheckEnd;
				DstData->RecordEndWriter = r;
			}
		}
		DstData->SaveRtCheckReader = raft;
	}
	if (DstData->SampWriter >= DstData->MaxSampPoint)
	{
		DstData->SaveState |= DstData->E_EndSave;
		return -1;
	}
	uint32 rd = (DstData->SaveRtReader) % rtData.MaxSampPoint;
	SalFwSampData1PointHeader& SurP = rtData.Header[rd];
	uint32 wt = DstData->SampWriter;
	if (SurP.RecContinueCnt > DstData->ContinueSamp)
	{
		if ((DstData->SaveState & DstData->E_EndAddCnt) == 0)
		{
			DstData->ContinueSamp = SurP.RecContinueCnt;
		}
	}
	if (DstData->SaveState & DstData->E_CheckEnd)
	{
		if (rd == DstData->RecordEndWriter)
		{
			DstData->SaveState |= DstData->E_EndAddCnt;
		}
	}
	SalFwSampData1Point& DstP = *DstData->PointAt(wt);
	//存储连续点
	if (DstData->ContinueSamp)
	{
		DstP.SampUtc = SurP.SampUtc;
		DstP.SampStamp = SurP.SampStamp;
		DstP.SampSerNo = SurP.SampSerNo;
		SalFwAnalogCfgArray& angcfg = fwCfg.AngCfg();
		uint32 angnum = angcfg.InstNum();
		u32value* pdata = &DstP.Data[0];
		for (uint32 i = 0; i < angnum; i++)
		{
			*pdata++ = rtData.GetU32(i, rd);
		}
		SalFwDigitalCfgArray& digcfg = fwCfg.DigCfg();
		uint32 dignum = digcfg.InstNum();
		uint32 digdwNum = (dignum + 31) / 32;
		pdata = &DstP.Data[angnum];
		for (uint32 i = 0; i < digdwNum; i++)
		{
			uint32 u32 = 0;
			uint32 loopend = Min(dignum, (i + 1) * 32);
			for (uint32 j = i * 32; j < loopend; j++)
			{
				u32 |= ((uint32)rtData.GetDig(j, rd)) << j;
			}
			pdata->u32 = u32;
			pdata++;
		}
		DstData->SaveRtReader = (rd + 1) % rtData.MaxSampPoint;
		DstData->SampWriter = wt + 1;
		DstData->CircleSampCnt = 0;
		DstData->CircleLimitIndex = 0;
		DstData->ContinueSamp--;
		return 0;
	}
	//存储间断点
	else if ((DstData->SaveState & DstData->E_EndAddCnt) == 0)
	{
		SalFwSampData1Point* LastDstP;
		if (wt)
		{
			LastDstP = DstData->PointAt(wt - 1);
		}
		else
		{
			LastDstP = DstData->PointAt(0);
			LastDstP->SampSerNo = 0;
		}
		uint32 dif = SurP.SampSerNo - LastDstP->SampSerNo;
		const uint16 fwZipLimit[] = { 1, 5, 25, 50, 250 };
		uint32 cirCle = 0xffffffff;
		if (DstData->CircleLimitIndex < M_ArrLen(fwZipLimit))
		{
			cirCle = fwZipLimit[DstData->CircleLimitIndex];
		}
		if (dif >= (sampPerCircle * cirCle))
		{
			DstP.SampUtc = SurP.SampUtc;
			DstP.SampStamp = SurP.SampStamp;
			DstP.SampSerNo = SurP.SampSerNo;
			SalFwAnalogCfgArray& angcfg = fwCfg.AngCfg();
			uint32 angnum = angcfg.InstNum();
			u32value* pdata = &DstP.Data[0];
			for (uint32 i = 0; i < angnum; i++)
			{
				float32 f32 = rtData.GetU32(i, rd).f32;
				if (pdata->f32 < f32)
				{
					pdata->f32 = f32;
				}
				pdata++;
			}
			SalFwDigitalCfgArray& digcfg = fwCfg.DigCfg();
			uint32 dignum = digcfg.InstNum();
			uint32 digdwNum = (dignum + 31) / 32;
			pdata = &DstP.Data[angnum];
			for (uint32 i = 0; i < digdwNum; i++)
			{
				uint32 u32 = 0;
				uint32 loopend = Min(dignum, (i + 1) * 32);
				for (uint32 j = i * 32; j < loopend; j++)
				{
					u32 |= ((uint32)rtData.GetDig(j, rd)) << j;
				}
				pdata->u32 = u32;
				pdata++;
			}
			DstData->SampWriter = wt + 1;
			if (DstData->CircleSampCnt < 10)
			{
				DstData->CircleSampCnt++;
			}
			else
			{
				DstData->CircleSampCnt = 0;
				DstData->CircleLimitIndex++;
				if (DstData->CircleLimitIndex > M_ArrLen(fwZipLimit))
				{
					DstData->CircleLimitIndex = M_ArrLen(fwZipLimit);
				}
			}
		}
		else
		{
			SalFwAnalogCfgArray& angcfg = fwCfg.AngCfg();
			uint32 angnum = angcfg.InstNum();
			u32value* pdata = &DstP.Data[0];
			for (uint32 i = 0; i < angnum; i++)
			{
				float32 f32 = rtData.GetU32(i, rd).f32;
				if (pdata->f32 < f32)
				{
					pdata->f32 = f32;
				}
				pdata++;
			}
		}
		DstData->SaveRtReader = (rd + 1) % rtData.MaxSampPoint;
		return 0;
	}
	else
	{
		DstData->SaveState |= DstData->E_EndSave;
		return -1;
	}
	return -1;
}

void spt::SalFwRecordGroup::SetContinueSaveCnt(uint32 Now, uint32 Before, uint32 After)
{
	uint32 rbf = (Now + rtData.MaxSampPoint - Before) % rtData.MaxSampPoint;
	uint32 total = Before + After;
	if (rtData.Header[rbf].RecContinueCnt < total)
	{
		rtData.Header[rbf].RecContinueCnt = total;
	}
}

int32 spt::SalFwRecordGroup::SetParaGroup(int32 Index, SalParaGroup* Group)
{
	return fwCfg.SetParaGroup(Index, Group);
}

bool8 spt::SalFwRecordGroup::Copy(SalFwData* Dst, SalFwData* Sur)
{
	if ((!Dst) || !(Sur))
	{
		return 0;
	}
	if (!(Sur->RecordState & Dst->E_EndRec))
	{
		return 0;
	}
	if (!(Sur->SaveState & Dst->E_AllFileSaved))
	{
		return 0;
	}
	StrNCpy(Dst->fileName, Sur->fileName, sizeof(Dst->fileName));
	if (Dst->AngCellPerSamp < Sur->AngCfgNum)
	{
		return 0;
	}
	Dst->AngCfgNum = Sur->AngCfgNum;
	if (Dst->DigCellPerSamp < Sur->DigCfgNum)
	{
		return 0;
	}
	Dst->DigCfgNum = Sur->DigCfgNum;
	uint32 swriter = Dst->SampWriter = Min(Dst->MaxSampPoint, Sur->SampWriter);
	Dst->BufSerNo = Sur->BufSerNo;
	Dst->RecordSerNo = Sur->RecordSerNo;
	Dst->RecordState = Sur->RecordState;
	Dst->SaveState = Sur->SaveState;
	Dst->ActType = Sur->ActType;
	Dst->EventWriter = Min((uint32)Sur->EventWriter, Dst->MaxEventNum);
	Dst->TrigT = Sur->TrigT;
	Dst->FirstSampT = Sur->FirstSampT;
	Dst->RecSampStampDif = Sur->RecSampStampDif;
	MemCpy(Dst->Event, Sur->Event, sizeof(Dst->Event[0]) * Dst->EventWriter);
	MemCpy(Dst->DataCfg, Sur->DataCfg, sizeof(Dst->DataCfg[0]) * (Dst->AngCfgNum + Dst->DigCfgNum));
	uint32 bufLen = Min(Dst->LenPerSamp, Sur->LenPerSamp);
	for (uint32 i = 0; i < swriter; i++)
	{
		MemCpy(Dst->PointAt(i), Sur->PointAt(i), bufLen);
	}
	return 1;
}

void spt::SalFwRecordGroup::ClearRecord()
{
	for (uint32 i = 0; i < MaxRecordFwRamData; i++)
	{
		if (fwData[i])
		{
			fwData[i]->SaveState = 0;
			fwData[i]->RecordState = 0;
		}
	}
	savedFlag.recordOverSerNo = savedFlag.fwWriter = savedFlag.fwReader = 0;
	RemoveDir(CN_FWRECORD_FILE_ROOT);
	RemoveDir(CN_T860_COMTRADE_FILE_ROOT);
	MkDir(CN_T860_COMTRADE_FILE_ROOT);
	SaveHdrData();
	return;
}

void spt::SalFwRecordCfg::PowerUpIni(uint16 FwAngMaxNum, uint16 FwDigMaxNum, uint16 FwProtMaxNum, uint16 HdrFaultInfoMaxNum, uint16 HdrDigMaxNum, uint16 MidAngMaxNum, uint16 MidDigMaxNum)
{
	digCfg.Alloc(sizeof(void*), FwDigMaxNum == 0 ? 1 : FwDigMaxNum);
	angCfg.Alloc(sizeof(void*), FwAngMaxNum == 0 ? 1 : FwAngMaxNum);
	digDatCfg.Alloc(sizeof(void*), FwDigMaxNum == 0 ? 1 : FwDigMaxNum);
	angDatCfg.Alloc(sizeof(void*), FwAngMaxNum == 0 ? 1 : FwAngMaxNum);
	actCfg.Alloc(sizeof(void*), FwProtMaxNum == 0 ? 1 : FwProtMaxNum);
	digHdrCfg.Alloc(sizeof(void*), HdrDigMaxNum == 0 ? 1 : HdrDigMaxNum);
	faultInfoHdrCfg.Alloc(sizeof(void*), HdrFaultInfoMaxNum == 0 ? 1 : HdrFaultInfoMaxNum);
	angMidCfg.Alloc(sizeof(void*), MidAngMaxNum == 0 ? 1 : MidAngMaxNum);
	digMidCfg.Alloc(sizeof(void*), MidDigMaxNum == 0 ? 1 : MidDigMaxNum);
}

int32 spt::SalFwRecordCfg::RgsCfgCell(SalFwWaveCfgCell* Cfg)
{
	SalFwWaveCfgCell::CfgType type = (SalFwWaveCfgCell::CfgType)Cfg->Type();
	switch (type)
	{
	case SalFwWaveCfgCell::E_Digital:
	{
		Cfg->SetDigId((uint16)digCfg.InstNum());
		digCfg.RgsCfgCell((SalFwDigitalCfgSignal*)Cfg);
		if (Cfg->Flags().st.isDatDigCfg)
		{
			digDatCfg.RgsCfgCell((SalFwDigitalCfgSignal*)Cfg);
		}
		if (Cfg->Flags().st.isHdrDig)
		{
			digHdrCfg.RgsCfgCell((SalFwDigitalCfgSignal*)Cfg);
		}
		if (Cfg->Flags().st.isMidDig)
		{
			digMidCfg.RgsCfgCell((SalFwDigitalCfgSignal*)Cfg);
		}
		break;
	}
	case SalFwWaveCfgCell::E_Analog:
	{
		Cfg->SetAngId((uint16)angCfg.InstNum());
		angCfg.RgsCfgCell((SalFwAnalogCfgSignal*)Cfg);
		if (Cfg->Flags().st.isDatAngCfg)
		{
			angDatCfg.RgsCfgCell((SalFwAnalogCfgSignal*)Cfg);
		}
		if (Cfg->Flags().st.isMidAng)
		{
			angMidCfg.RgsCfgCell((SalFwAnalogCfgSignal*)Cfg);
		}
		break;
	}
	case SalFwWaveCfgCell::E_Event:
	{
		Cfg->SetDigId((uint16)digCfg.InstNum());
		digCfg.RgsCfgCell((SalFwDigitalCfgSignal*)Cfg);
		if (Cfg->Flags().st.isDatDigCfg)
		{
			digDatCfg.RgsCfgCell((SalFwDigitalCfgSignal*)Cfg);
		}
		if (Cfg->Flags().st.isEvent)
		{
			Cfg->SetEventId((uint16)actCfg.InstNum());
			actCfg.RgsCfgCell((SalFwProtEventCfgSignal*)Cfg);
		}
		if (Cfg->Flags().st.isMidDig)
		{
			digMidCfg.RgsCfgCell((SalFwDigitalCfgSignal*)Cfg);
		}
		break;
	}
	case SalFwWaveCfgCell::E_FaultInfo:
	{
		if (Cfg->Flags().st.isHdrFaultInfo)
		{
			faultInfoHdrCfg.RgsCfgCell((SalFaultInfo*)Cfg);
		}
		break;
	}
	default:
		break;
	}
	return 0;
}

int32 spt::SalFwRecordCfg::SetParaGroup(int32 Index, SalParaGroup* Group)
{
	if ((uint32)Index < M_ArrLen(paraGroup))
	{
		paraGroup[Index] = Group;
		return 0;
	}
	return -1;
}

SalParaGroup* spt::SalFwRecordCfg::GetParaGroup(int32 Index)
{
	if ((uint32)Index < M_ArrLen(paraGroup))
	{
		return paraGroup[Index];
	}
	return 0;
}

SalFaultInfo* spt::SalFwFaultInfoCfgArray::GetCfg(uint32 No)
{
	return (SalFaultInfo*)GetAddrElement(No);
}

int32 spt::SalFwFaultInfoCfgArray::RgsCfgCell(SalFaultInfo* Cfg)
{
	if (Push(Cfg))
	{
		return 0;
	}
	return -1;
}

int32 spt::SalFwFaultInfoCfgArray::InstNum()
{
	return Top();
}

SalFwEventCfgSignal* spt::SalFwActCfgArray::GetCfg(uint32 No)
{
	return (SalFwEventCfgSignal*)GetAddrElement(No);
}

int32 spt::SalFwActCfgArray::RgsCfgCell(SalFwProtEventCfgSignal* Cfg)
{
	if (Push(&Cfg))
	{
		return 0;
	}
	return -1;
}

int32 spt::SalFwActCfgArray::InstNum()
{
	return Top();
}

SalFwDigitalCfgSignal* spt::SalFwDigitalCfgArray::GetCfg(uint32 No)
{
	return (SalFwDigitalCfgSignal*)GetAddrElement(No);
}

int32 spt::SalFwDigitalCfgArray::RgsCfgCell(SalFwDigitalCfgSignal* Cfg)
{
	if (Push(&Cfg))
	{
		return 0;
	}
	return -1;
}

int32 spt::SalFwDigitalCfgArray::InstNum()
{
	return Top();
}

SalFwAnalogCfgSignal* spt::SalFwAnalogCfgArray::GetCfg(uint32 No)
{
	return (SalFwAnalogCfgSignal*)GetAddrElement(No);
}

int32 spt::SalFwAnalogCfgArray::RgsCfgCell(SalFwAnalogCfgSignal* Cfg)
{
	if (Push(&Cfg))
	{
		return 0;
	}
	return -1;
}

int32 spt::SalFwAnalogCfgArray::InstNum()
{
	return Top();
}

int32 spt::SalFwRecordTask::PowerUpIni(int32 Para)
{
	if (SptMain::Instance().StartMode() != SptMain::E_Normal)
	{
		return -1;
	}
	if (!SptMain::Instance().AppCfg())
	{
		return -1;
	}
	Task::PowerUpIni(Para);
	Start();
	return 0;
}

int32 spt::SalFwRecordTask::OneLoop()
{
	MsSleep(20);
	InstObjectGroupParent* parent = InstObjectRoot::Instance().GetGroupParent(EIOT_FrRecord);
	if (parent == 0)
	{
		return 0;
	}
	uint32 loopend = parent->InstNum();
	InstObjectGroup* group;
	for (uint32 i = 0; i < loopend; i++)
	{
		group = parent->GetGroup(i);
		if (group)
		{
			SalFwRecordGroup* fw = (SalFwRecordGroup*)group;
			fw->Save2File();
		}
		else
		{
			break;
		}
	}
	return 0;
}

spt::SalFwRecordTask::SalFwRecordTask()
	:Task("tFwSave", TaskBasePriority - 90, 2 * 1024 * 1024, E_T_FLOAT, E_ServiceCore)
{




}

int32 spt::SalFwData::Malloc()
{
	MaxEventNum = (MaxEventNum == 0 ? 1 : MaxEventNum);
	Event = (FwEventData*)Calloc(1, sizeof(FwEventData) * MaxEventNum);
	if (!Event)
	{
		return -1;
	}
	LenPerSamp = sizeof(SalFwSampData1PointHeader) + sizeof(u32value) * (CellPerSamp / 2 + 1) * 2;
	MaxSampPoint = (MaxSampPoint == 0 ? 1 : MaxSampPoint);
	DataBuf = Calloc(1, LenPerSamp * MaxSampPoint);
	DataCfg = (SalFileChannelDataCfg*)Calloc(1, sizeof(SalFileChannelDataCfg) * (AngCellPerSamp + DigCellPerSamp));
	if ((!DataBuf) || (!DataCfg))
	{
		return -1;
	}
	return 0;
}

void spt::SalFwData::StatusClear()
{
	SampWriter = 0;
	SaveRtReader = 0;
	SaveRtCheckReader = 0;
	ContinueSamp = 0;
	RecordStartWriter = 0;
	RecordEndWriter = 0;
	RecordSerNo = 0;
	RecordState = E_Null;
	SaveState = E_Null2;
	EventWriter = 0;
	TrigT.Set((int64)0);
}

SalFwSampData1Point* spt::SalFwData::PointAt(uint32 Index)
{
	char* p = (char*)DataBuf;
	return (SalFwSampData1Point*)(p + LenPerSamp * (Index % MaxSampPoint));
}
bool8 spt::SalFwData::ToLcdStr(SalString& Str, bool8 DispExInfo, bool8 UnDispReturn, uint32 LineW) const
{
	TrigT.ToStrHzFmt2(Str);
	Str << "\n";
	uint32 MsLen = 0;
	if (RecSampStampDif < 10000)
	{
		MsLen = 4;
	}
	else
	{
		MsLen = 7;
	}
	String1000B temp;
	for (uint32 i = 0; i < EventWriter; i++)
	{
		if (UnDispReturn && (Event[i].EventData.status.bl == 0))
		{
			continue;
		}
		Str.Format(Event[i].ActTimeMs, MsLen, 0, 0, ' ') << "ms ";
		Event[i].EventData.ActStr(Str, LineW - MsLen - 4);
		Str << "\n";
		if (DispExInfo)
		{
			temp.Clear();
			if (Event[i].EventData.ExternInfoStr(temp, LineW - MsLen - 4))
			{
				if (temp.StrLen())
				{
					TransString ts;
					ts.SetBuf(temp.Str());
					String200B st;
					while (ts.GetLine(st))
					{
						Str.Format(" ", MsLen + 3, 1, ' ');
						Str << st << "\n";
						st.Clear();
					}
				}

			}
		}
	}
	return 1;
}
int32 spt::SalFwData::Save2PriFile(const char* FileName, SalFwRecordCfg* FwCfg)
{
	//数据准备
	PrepareSaveData(FwCfg);
	SalFile file;
	file.Path().Set(CN_FWRECORD_FILE_ROOT);
	String500B str;
	str = FileName;
	StrNCpy(filePriName, FileName, sizeof(filePriName));
	str.Format(BufSerNo, 2, '0') << ".fwr";
	file.Name().Set(str.Str());
	file.Creat();
	SavePriPub(file);
	SavePriEvent(file);
	SavePriCfg(file);
	SavePriSet(file, FwCfg);
	SavePriEventBin(file);
	SavePriDatBin(file);
	file.Close();
	return 0;
}

int32 spt::SalFwData::Save2PubFile(const char* FileName, SalFwRecordCfg* FwCfg)
{
	SavePubCfg1999File(fileName);
	switch (DatFileType)
	{
	case EFT_ASCII:
	{
		SavePubDatAssic1999File(fileName);
		break;
	}
	case EFT_BIN16:
	{
		break;
	}
	case EFT_BIN32:
	{
		break;
	}
	case EFT_FLOAT32:
	{
		break;
	}
	default:
		break;
	}
	SavePubHdrFile(fileName, FwCfg);
	SavePubDesFile(fileName);
	SavePubMidFile(fileName);
	return 0;
}

int32 spt::SalFwData::LoadPriFile(const char* FileName)
{
	SalFile file;
	file.Path().Set(CN_FWRECORD_FILE_ROOT);
	String5000B str;
	file.SetFullName(FileName);
	file.OpenReadOnly();
	if (file.IsOpened() == 0)
	{
		return 0;
	}
	LoadPriPub(file);
	LoadPriCfg(file);
	LoadPriEventBin(file);
	LoadPriDatBin(file);
	file.Close();
	return 0;
}

int32 spt::SalFwData::SeekPriSet(SalFile& File)
{
	return int32();
}

int32 spt::SalFwData::GetNextPriSet(SalFile& File, SalString& Str)
{
	return int32();
}

int32 spt::SalFwData::DeleteAllFile()
{
	String500B str;
	str = CN_FWRECORD_FILE_ROOT;
	str << CN_FILE_DivFlag << filePriName;
	str.Format(BufSerNo, 2, '0') << ".fwr";
	RemoveFile(str.Str());
	str = CN_FWRECORD_FILE_ROOT;
	str << CN_FILE_DivFlag << fileName << ".cfg";
	RemoveFile(str.Str());
	str = CN_FWRECORD_FILE_ROOT;
	str << CN_FILE_DivFlag << fileName << ".dat";
	RemoveFile(str.Str());
	str = CN_FWRECORD_FILE_ROOT;
	str << CN_FILE_DivFlag << fileName << ".hdr";
	RemoveFile(str.Str());
	str = CN_FWRECORD_FILE_ROOT;
	str << CN_FILE_DivFlag << fileName << ".mid";
	RemoveFile(str.Str());
	str = CN_FWRECORD_FILE_ROOT;
	str << CN_FILE_DivFlag << fileName << ".des";
	RemoveFile(str.Str());
	SaveState = 0;
	return 0;
}

int32 spt::SalFwData::SavePriPub(SalFile& file)
{
	String500B str;
	file.WriteLine("---PubFileInf---");
	str = filePriName;
	file.WriteLine(str.Str());
	str = "Name,BufNo,RecNo,RecSta,SaveSta,ActType";
	file.WriteLine(str.Str());
	str.Clear();
	str = fileName;
	str << "," << BufSerNo << "," << RecordSerNo;
	str << ",";
	str.FormatHex(RecordState) << ",";
	str.FormatHex(SaveState) << ",";
	str << ActType;
	file.WriteLine(str.Str());
	str.Clear();
	return 0;
}

int32 spt::SalFwData::SavePriEvent(SalFile& File)
{
	String5000B str;
	if (EventWriter > MaxEventNum)
	{
		EventWriter = MaxEventNum;

	}
	File.WriteLine("---EventFile---");
	str = "";
	str << EventWriter;
	str << ",";
	TrigT.ToStrFmt10(str);
	TrigT.ToStrFmt12(str);
	File.WriteLine(str.Str());
	str.Clear();
	str << "序号,相对时间,动作时间,事项,变位前,变位后,IsDisp,Flags,品质,板卡,动作信息个数,动作信息,";
	File.WriteLine(str.Str());
	str.Clear();
	for (uint32 i = 0; i < EventWriter; i++)
	{
		Event[i].ToStr(str);
		File.WriteLine(str.Str());
		str.Clear();
	}
	return 0;
}

int32 spt::SalFwData::SavePriCfg(SalFile& File)
{
	File.WriteLine("---CfgFile---");
	String1000B strtemp;
	strtemp << (AngCfgNum + DigCfgNum) << "," << AngCfgNum << "," << DigCfgNum;
	File.WriteLine(strtemp.Str());
	strtemp.Clear();
	uint32 anggnum = AngCfgNum;
	strtemp << "序号,类型,标志,名称,相别,单位,CCBM,Skew,CoeA,CoeB,Max,Min,Primary,Secondary,IsPrimary,Y,IsDisp";
	File.WriteLine(strtemp.Str());
	strtemp.Clear();
	for (uint32 i = 0; i < anggnum; i++)
	{
		SalFileChannelDataCfg* dcfg = &DataCfg[i];
		strtemp << (dcfg->Cn) << ",";
		strtemp << dcfg->ChanType << ",";
		strtemp.FormatHex(dcfg->Flag.u32) << ",";
		strtemp << dcfg->Name << ",";
		strtemp << dcfg->Phase << ",";
		strtemp << dcfg->Unit << ",";
		strtemp << dcfg->Ccbm << ",";
		strtemp.FormatFloat(dcfg->CoeA.f32, 7) << ",";
		strtemp.FormatFloat(dcfg->CoeB.f32, 7) << ",";
		strtemp.FormatFloat(dcfg->Skew.f32, 7) << ",";
		strtemp.FormatFloat(dcfg->Min.f32, 7) << ",";
		strtemp.FormatFloat(dcfg->Max.f32, 7) << ",";
		strtemp.FormatFloat(dcfg->Primary.f32, 7) << ",";
		strtemp.FormatFloat(dcfg->Secondary.f32, 7) << ",";
		strtemp << dcfg->IsPrimary << ",";
		strtemp << dcfg->Y << ",";
		strtemp << dcfg->IsDisp << ",";
		File.WriteLine(strtemp.Str());
		strtemp.Clear();
	}
	uint32 dignum = DigCfgNum;
	for (uint32 i = 0; i < dignum; i++)
	{
		SalFileChannelDataCfg* dcfg = &DataCfg[i + anggnum];
		strtemp << (dcfg->Cn) << ",";
		strtemp << dcfg->ChanType << ",";
		strtemp.FormatHex(dcfg->Flag.u32) << ",";
		strtemp << dcfg->Name << ",";
		strtemp << dcfg->Phase << ",";
		strtemp << dcfg->Unit << ",";
		strtemp << dcfg->Ccbm << ",";
		strtemp << ",";
		strtemp << ",";
		strtemp << ",";
		strtemp << ",";
		strtemp << ",";
		strtemp << ",";
		strtemp << ",";
		strtemp << dcfg->IsPrimary << ",";
		strtemp << dcfg->Y << ",";
		strtemp << dcfg->IsDisp << ",";
		File.WriteLine(strtemp.Str());
		strtemp.Clear();
	}
	strtemp << SysFreq << "," << SampPerCircle;
	File.WriteLine(strtemp.Str());
	strtemp.Clear();
	strtemp << 0;
	File.WriteLine(strtemp.Str());
	strtemp.Clear();
	strtemp << 0 << "," << (SampWriter + 1) << "," << (RecSampStampDif);
	File.WriteLine(strtemp.Str());
	strtemp.Clear();
	FirstSampT.ToStrFmt5(strtemp);
	File.WriteLine(strtemp.Str());
	strtemp.Clear();
	TrigT.ToStrFmt5(strtemp);
	File.WriteLine(strtemp.Str());
	strtemp.Clear();
	strtemp << "float32," << DatFileType;
	File.WriteLine(strtemp.Str());
	strtemp.Clear();
	strtemp << "1";
	File.WriteLine(strtemp.Str());
	strtemp.Clear();
	strtemp << "0,+8";
	File.WriteLine(strtemp.Str());
	strtemp.Clear();
	strtemp << "A,3";
	File.WriteLine(strtemp.Str());
	strtemp.Clear();
	return 0;
}

int32 spt::SalFwData::SavePriSet(SalFile& File, SalFwRecordCfg* FwCfg)
{
	File.WriteLine("---SetFile---");
	uint32 Loop = 0;
	for (uint32 i = 0; i < 5; i++)
	{
		SalParaGroup* g = FwCfg->GetParaGroup(i);
		if (g)
		{
			Loop++;
		}
	}
	String100B str;
	str << Loop << ",";
	File.WriteLine(str.Str());
	str.Clear();
	for (uint32 i = 0; i < Loop; i++)
	{
		SalParaGroup* g = FwCfg->GetParaGroup(i);
		if (!g)
		{
			break;
		}
		str << i << "," << g->Name() << "," << g->InstNum();
		File.WriteLine(str.Str());
		str.Clear();
		uint32 le = g->InstNum();
		const int32* data = g->UsingData(g->UsingZone());
		if (!data)
		{
			break;
		}
		for (uint32 j = 0; j < le; j++)
		{
			SalPara* p = g->GetDes(j);
			if (!p)
			{
				break;
			}
			str << j << "," << p->Name() << ",";
			p->Value2Str(str);
			str << "," << p->Unit();
			str << "," << p->Disp();
			File.WriteLine(str.Str());
			str.Clear();
		}
	}
	return 0;
}

int32 spt::SalFwData::SavePriEventBin(SalFile& File)
{
	File.WriteLine("---EventBinFile---");
	uint32 s = EDT_Event;
	File.Write(&s, sizeof(uint32));
	s = EventWriter;
	File.Write(&s, sizeof(uint32));
	s = sizeof(Event[0]);
	File.Write(&s, sizeof(uint32));
	File.Write(&Event[0], sizeof(Event[0]) * EventWriter);
	File.WriteLine("");
	return 0;
}

int32 spt::SalFwData::SavePriDatBin(SalFile& File)
{
	File.WriteLine("---SampBinFile---");
	uint32 s = EDT_Dat;
	File.Write(&s, sizeof(uint32));
	s = SampWriter;
	File.Write(&s, sizeof(uint32));
	s = AngCfgNum + DigCfgNum;
	File.Write(&s, sizeof(uint32));
	s = AngCfgNum;
	File.Write(&s, sizeof(uint32));
	s = DigCfgNum;
	File.Write(&s, sizeof(uint32));
	s = sizeof(SalFwSampData1PointHeader);
	File.Write(&s, sizeof(uint32));
	uint32 bufLen = s = sizeof(SalFwSampData1PointHeader) + sizeof(uint32) * (AngCfgNum + (DigCfgNum + 31) / 32);
	File.Write(&s, sizeof(uint32));
	for (uint32 i = 0; i < SampWriter; i++)
	{
		File.Write(PointAt(i), bufLen);
	}
	File.WriteLine("");
	return 0;
}

int32 spt::SalFwData::LoadPriPub(SalFile& File)
{
	if (File.SeekLineNext("---PubFileInf---") < 0)
	{
		return -1;
	}
	String500B str, temp;
	TransString ts1;
	File.ReadLine(str);
	StrNCmp(filePriName, str.Str(), sizeof(filePriName));
	File.ReadLine(str);
	str.Clear();
	File.ReadLine(str);
	ts1.SetBuf(str.Str());
	ts1.GetLine(temp, ',');
	StrNCmp(fileName, str.Str(), sizeof(fileName));
	BufSerNo = (uint8)ts1.GetUInt64(',');
	RecordSerNo = (uint8)ts1.GetUInt64(',');
	RecordState = (uint8)ts1.GetUInt64(',');
	SaveState = (uint8)ts1.GetUInt64(',');
	ActType = (uint8)ts1.GetUInt64(',');
	str.Clear();
	return 0;
}

int32 spt::SalFwData::LoadPriCfg(SalFile& File)
{
	if (File.SeekLineNext("---CfgFile---") < 0)
	{
		return -1;
	}
	String5000B str, temp;
	TransString ts1;
	File.ReadLine(str);
	ts1.SetBuf(str.Str());
	uint32 total = (uint32)ts1.GetUInt64(',');
	AngCfgNum = (uint8)ts1.GetUInt64(',');
	DigCfgNum = (uint8)ts1.GetUInt64(',');
	if (((uint32)(AngCfgNum + DigCfgNum) > (AngCellPerSamp + DigCellPerSamp)) || (total != (uint32)(AngCfgNum + DigCfgNum)))
	{
		LogErr.Stamp() << "LoadPriCfg" << total << AngCfgNum << DigCfgNum << (AngCellPerSamp + DigCellPerSamp) << EndOfInst;
		return -1;
	}
	for (uint32 i = 0; i < total; i++)
	{
		str.Clear();
		File.ReadLine(str);
		SalFileChannelDataCfg* cfg = &DataCfg[i];
		ts1.SetBuf(str.Str());
		cfg->Cn = (uint32)ts1.GetUInt64(',');
		cfg->ChanType = (uint8)ts1.GetUInt64(',');
		cfg->Flag.u32 = (uint8)ts1.GetUInt64(',');
		ts1.GetLine(temp, ',');
		StrNCpy(cfg->Name, temp.Str(), sizeof(cfg->Name));
		ts1.GetLine(temp, ',');
		StrNCpy(cfg->Phase, temp.Str(), sizeof(cfg->Phase));
		ts1.GetLine(temp, ',');
		StrNCpy(cfg->Ccbm, temp.Str(), sizeof(cfg->Ccbm));
		ts1.GetLine(temp, ',');
		StrNCpy(cfg->Unit, temp.Str(), sizeof(cfg->Unit));
		cfg->CoeA.f32 = ts1.GetFloat32(',');
		cfg->CoeB.f32 = ts1.GetFloat32(',');
		cfg->Min.f32 = ts1.GetFloat32(',');
		cfg->Max.f32 = ts1.GetFloat32(',');
		cfg->Skew.f32 = ts1.GetFloat32(',');
		cfg->Primary.f32 = ts1.GetFloat32(',');
		cfg->Secondary.f32 = ts1.GetFloat32(',');
		ts1.GetLine(temp, ',');
		if ((temp.Str()[0] == 'P' || temp.Str()[0] == 'p'))
		{
			cfg->IsPrimary = 1;
		}
		else
		{
			cfg->IsPrimary = 1;
		}
		cfg->Y = (uint8)ts1.GetUInt64(',');
		cfg->IsDisp = (uint8)ts1.GetUInt64(',');
	}
	str.Clear();
	File.ReadLine(str);
	SysFreq = (uint16)ts1.GetUInt64(',');
	SampPerCircle = (uint16)ts1.GetUInt64(',');
	str.Clear();
	File.ReadLine(str);
	ts1.GetUInt64(',');
	SampWriter = (uint32)ts1.GetUInt64(',');
	RecSampStampDif = (uint32)ts1.GetUInt64(',');
	str.Clear();
	File.ReadLine(str);
	FirstSampT.FromStrFmt5(str.Str());
	str.Clear();
	File.ReadLine(str);
	TrigT.FromStrFmt5(str.Str());
	str.Clear();
	File.ReadLine(str);
	ts1.GetLine(temp, ',');
	DatFileType = (uint8)ts1.GetUInt64(',');
	return 0;
}

int32 spt::SalFwData::LoadPriEventBin(SalFile& File)
{
	if (File.SeekLineNext("---EventBinFile---") < 0)
	{
		return -1;
	}
	uint32 temp32;
	File.Read(&temp32, sizeof(uint32));
	if (temp32 != EDT_Event)
	{
		return -1;
	}
	File.Read(&temp32, sizeof(uint32));
	if (temp32 > MaxEventNum)
	{
		return -1;
	}
	EventWriter = temp32;
	File.Read(&temp32, sizeof(uint32));
	if (temp32 != sizeof(Event[0]))
	{
		return -1;
	}
	File.Read(&Event[0], sizeof(Event[0]) * EventWriter);
	return 0;
}

int32 spt::SalFwData::LoadPriDatBin(SalFile& File)
{
	if (File.SeekLineNext("---SampBinFile---") < 0)
	{
		return -1;
	}
	uint32 temp32;
	File.Read(&temp32, sizeof(uint32));
	if (temp32 != EDT_Dat)
	{
		return -1;
	}
	File.Read(&temp32, sizeof(uint32));
	if (temp32 >= MaxSampPoint)
	{
		temp32 = MaxSampPoint;
	}
	File.Read(&temp32, sizeof(uint32));
	File.Read(&temp32, sizeof(uint32));
	if (temp32 != AngCfgNum)
	{
		return -1;
	}
	File.Read(&temp32, sizeof(uint32));
	if (temp32 != DigCfgNum)
	{
		return -1;
	}
	File.Read(&temp32, sizeof(uint32));
	if (temp32 != sizeof(SalFwSampData1PointHeader))
	{
		return -1;
	}
	File.Read(&temp32, sizeof(uint32));
	if (temp32 > LenPerSamp)
	{
		return -1;
	}
	uint32 bufLen = temp32;
	for (uint32 i = 0; i < SampWriter; i++)
	{
		File.Read(PointAt(i), bufLen);
	}
	return 0;
}

int32 spt::SalFwData::SavePubCfg1999File(const char* FileName)
{
	SalFile file;
	file.Path().Set(CN_FWRECORD_FILE_ROOT);
	String5000B str;
	str = FileName;
	str << ".cfg";
	file.Name().Set(str.Str());
	file.Creat();
	str.Clear();
	str << ApiUnitCfg::Instance().StationId.StrData() << ",";
	str << ApiUnitCfg::Instance().FwRecId.StrData() << ",";
	str << "1999";
	file.WriteLine(str.Str());
	str.Clear();

	uint32 dispAng = 0;
	uint32 dispDig = 0;
	for (uint32 i = 0; i < AngCfgNum; i++)
	{
		SalFileChannelDataCfg* cfg = &DataCfg[i];
		if (cfg->IsDisp && (cfg->Flag.st.isDatAngCfg))
		{
			dispAng++;
		}
	}
	for (uint32 i = 0; i < DigCfgNum; i++)
	{
		SalFileChannelDataCfg* cfg = &DataCfg[i + AngCfgNum];
		if (cfg->IsDisp && (cfg->Flag.st.isDatDigCfg))
		{
			dispDig++;
		}
	}
	str << (dispAng + dispDig) << "," << dispAng << "A," << dispDig << "D";
	file.WriteLine(str.Str());
	str.Clear();
	uint32 id = 1;
	for (uint32 i = 0; i < AngCfgNum; i++)
	{
		SalFileChannelDataCfg* cfg = &DataCfg[i];
		if (cfg->IsDisp && (cfg->Flag.st.isDatAngCfg))
		{
			str << (id++) << ",";
			str << cfg->Name << ",";
			str << cfg->Phase << ",";
			str << cfg->Ccbm << ",";
			str << cfg->Unit << ",";
			str.FormatFloat(cfg->CoeA.f32, 7) << ",";
			str.FormatFloat(cfg->CoeB.f32, 7) << ",";
			str.FormatFloat(cfg->Skew.f32, 7) << ",";
			str.FormatFloat(cfg->Min.f32, 7) << ",";
			str.FormatFloat(cfg->Max.f32, 7) << ",";
			str.FormatFloat(cfg->Primary.f32, 7) << ",";
			str.FormatFloat(cfg->Secondary.f32, 7) << ",";
			if (cfg->IsPrimary)
			{
				str << 'P';
			}
			else
			{
				str << 'S';
			}
			file.WriteLine(str.Str());
			str.Clear();
		}
	}
	id = 1;
	for (uint32 i = 0; i < DigCfgNum; i++)
	{
		SalFileChannelDataCfg* cfg = &DataCfg[i + AngCfgNum];
		if (cfg->IsDisp && (cfg->Flag.st.isDatDigCfg))
		{
			str << (id++) << ",";
			str << cfg->Name << ",";
			str << cfg->Phase << ",";
			str << cfg->Ccbm << ",";
			if (cfg->Y)
			{
				str << '1';
			}
			else
			{
				str << '0';
			}
			file.WriteLine(str.Str());
			str.Clear();
		}
	}
	str << SysFreq;
	file.WriteLine(str.Str());
	str.Clear();
	str << 0;
	file.WriteLine(str.Str());
	str.Clear();
	str << "0," << SampWriter;
	file.WriteLine(str.Str());
	str.Clear();
	FirstSampT.ToStrFmt14(str);
	str << ",";
	FirstSampT.ToStrFmt13(str);
	file.WriteLine(str.Str());
	str.Clear();
	TrigT.ToStrFmt14(str);
	str << ",";
	TrigT.ToStrFmt13(str);
	file.WriteLine(str.Str());
	str.Clear();
	if (DatFileType == EFT_ASCII)
	{
		str << "ASSIC";
		timeMult = 1;
	}
	else if (DatFileType == EFT_BIN16)
	{
		str << "binary";
		if (RecSampStampDif < (uint32)0xffffffff)
		{
			timeMult = 1;
		}
		else
		{
			timeMult = 100;
		}
	}
	else if (DatFileType == EFT_BIN32)
	{
		str << "binary32";
		if (RecSampStampDif < (uint32)0xffffffff)
		{
			timeMult = 1;
		}
		else
		{
			timeMult = 100;
		}
	}
	else if (DatFileType == EFT_FLOAT32)
	{
		str << "float32";
		if (RecSampStampDif < (uint32)0xffffffff)
		{
			timeMult = 1;
		}
		else
		{
			timeMult = 100;
		}
	}
	file.WriteLine(str.Str());
	str.Clear();
	str << timeMult;
	file.WriteLine(str.Str());
	str.Clear();
	file.Close();
	return 0;
}

int32 spt::SalFwData::SavePubDatAssic1999File(const char* FileName)
{
	SalFile file;
	file.Path().Set(CN_FWRECORD_FILE_ROOT);
	String5000B str;
	str = FileName;
	str << ".dat";
	file.Name().Set(str.Str());
	file.Creat();
	str.Clear();
	for (uint32 j = 0; j < SampWriter; j++)
	{
		SalFwSampData1Point* p = PointAt(j);
		str << (uint32)(p->SampSerNo + 1) << "," << (p->SampStamp);
		file.Write(str.Str());
		str.Clear();
		for (uint32 i = 0; i < AngCfgNum; i++)
		{
			SalFileChannelDataCfg* cfg = &DataCfg[i];
			if (cfg->IsDisp && (cfg->Flag.st.isDatAngCfg))
			{
				str << ",";
				str.FormatFloat(p->Data[i].f32, 7);
			}
		}
		file.Write(str.Str());
		str.Clear();
		uint32* pdata = &p->Data[AngCfgNum].u32;
		char d;
		for (uint32 i = 0; i < DigCfgNum; i++)
		{
			SalFileChannelDataCfg* cfg = &DataCfg[i + AngCfgNum];
			if (cfg->IsDisp && (cfg->Flag.st.isDatDigCfg))
			{
				str << ",";
				d = GetBit(pdata[i / 32], i % 32) ? '1' : '0';
				str << d;
			}
		}
		file.WriteLine(str.Str());
		str.Clear();
	}
	file.Close();
	return 0;
}

int32 spt::SalFwData::SavePubHdrFile(const char* FileName, SalFwRecordCfg* FwCfg)
{
	SalFile file;
	file.Path().Set(CN_FWRECORD_FILE_ROOT);
	String1000B str;
	str = FileName;
	str << ".hdr";
	file.Name().Set(str.Str());
	file.Creat();
	str.Clear();
	char buf[2000];
	str.Clear();
	str << "<?xml version=\"1.1\" encoding=\"UTF-8\"?>\n<FaultReport>\n";
	StrGBK2UTF8(buf, str.Str(), sizeof(buf));
	file.Write(buf);
	str.Clear();
	str << "<FaultStartTime>";
	SalRtc rtc;
	rtc.FromStamp(&TrigT);
	rtc.ToStrFmt22(str);
	str << "</FaultStartTime>\n";
	StrGBK2UTF8(buf, str.Str(), sizeof(buf));
	file.Write(buf);
	str.Clear();
	for (uint32 i = 0; i < EventWriter; i++)
	{
		str << "<TripInfo>\n";
		str << "<time>";
		str << (Event[i].ActTimeMs);
		str << "ms</time>\n";
		str << "<name>" << Event[i].EventData.Name() << "</name>\n";
		const SalStatus* des = Event[i].EventData.StatusDes();
		if (des&&des->Flag().st.isFirstInfoIsPhase)
		{
			str << "<phase>" << GetPhaseStr (Event[i].EventData.exInfo[0].u32)<< " </phase>\n";
		}
		else
		{
			str << "<phase>" << " </phase>\n";
		}
		str << "<value>";
		Event[i].EventData.ValueStr(Event[i].EventData.status, str,10);
		str<< "</value>\n";
		String40B name, data, unit;
		for (uint32 j = 0; j < Event[i].EventData.ExternInfoNum(); j++)
		{
			if (des && des->Flag().st.isFirstInfoIsPhase)
			{
				continue;
			}
			name.Clear();
			data.Clear();
			unit.Clear();
			Event[i].EventData.ExternInfoStr(j,name,data,unit);
			str << "<FaultInfo>\n";
			str << "<name>" << name<< "</name>\n";
			str << "<value>" << data <<unit<< "</value>\n";
			str << "</FaultInfo>\n";
		}
		str << "</TripInfo>\n";
		StrGBK2UTF8(buf, str.Str(), sizeof(buf));
		file.Write(buf);
		str.Clear();
	}

	for (uint32 j = 0; j < 1; j++)
	{
		SalFwSampData1Point* p = PointAt(j);
		bool8 rec = 0;
		uint32* pdata = &p->Data[AngCfgNum].u32;
		for (uint32 i = 0; i < DigCfgNum; i++)
		{
			SalFileChannelDataCfg* cfg = &DataCfg[i + AngCfgNum];
			if (cfg->IsDisp && (cfg->Flag.st.isHdrDig))
			{
				str << "<DigitalStatus>\n<name>" << cfg->Name << "</name>\n";
				str << "<value>";
				str << GetBit(pdata[i / 32], i % 32);
				str << "</value>\n</DigitalStatus>\n";
				StrGBK2UTF8(buf, str.Str(), sizeof(buf));
				file.Write(buf);
				str.Clear();
			}
		}

		str.Clear();
	}
	for (uint32 j = 1; j < SampWriter; j++)
	{
		SalFwSampData1Point* p = PointAt(j);
		bool8 rec = 0;
		uint32* pdata = &p->Data[AngCfgNum].u32;
		uint32* pbfdata = &PointAt(j - 1)->Data[AngCfgNum].u32;
		for (uint32 i = 0; i < DigCfgNum; i++)
		{
			SalFileChannelDataCfg* cfg = &DataCfg[i + AngCfgNum];
			if (cfg->IsDisp && (cfg->Flag.st.isHdrDig))
			{
				if (GetBit(pdata[i / 32], i % 32) != GetBit(pbfdata[i / 32], i % 32))
				{
					str << "<DigitalEvent>\n<name>" << cfg->Name << "</name>\n";
					str << "<time>";
					str << (p->SampStamp / 1000);
					str << "ms</time>\n";
					str << "<value>";
					str << GetBit(pdata[i / 32], i % 32);
					str << "</value>\n</DigitalEvent>\n";
					StrGBK2UTF8(buf, str.Str(), sizeof(buf));
					file.Write(buf);
					str.Clear();
				}
			}
		}
		str.Clear();
	}
	uint32 Loop = 0;
	for (uint32 i = 0; i < 5; i++)
	{
		SalParaGroup* g = FwCfg->GetParaGroup(i);
		if (g)
		{
			Loop++;
		}
	}
	str.Clear();
	for (uint32 i = 0; i < Loop; i++)
	{
		SalParaGroup* g = FwCfg->GetParaGroup(i);
		if (!g)
		{
			break;
		}
		uint32 le = g->InstNum();
		const int32* data = g->UsingData(g->UsingZone());
		if (!data)
		{
			break;
		}
		for (uint32 j = 0; j < le; j++)
		{
			SalPara* p = g->GetDes(j);
			if (!p)
			{
				break;
			}
			if (p->Disp() == 0)
			{
				continue;
			}
			str << "<SettingValue>\n<name>" << p->Name() << "</name>\n";
			str << "<value>";
			p->Value2Str(str);
			str << "</value>\n";
			str << "<unit>";
			str << p->Unit();
			str << "</unit>\n</SettingValue>\n";
			StrGBK2UTF8(buf, str.Str(), sizeof(buf));
			file.Write(buf);
			str.Clear();
		}
	}
	str.Clear();
	str << "</FaultReport>\n";
	StrGBK2UTF8(buf, str.Str(), sizeof(buf));
	file.Write(buf);
	file.Close();
	return 0;
}

int32 spt::SalFwData::SavePubMidFile(const char* FileName)
{
	SalFile file;
	file.Path().Set(CN_FWRECORD_FILE_ROOT);
	String5000B str;
	str = FileName;
	str << ".mid";
	file.Name().Set(str.Str());
	file.Creat();
	str.Clear();
	for (uint32 j = 0; j < SampWriter; j++)
	{
		SalFwSampData1Point* p = PointAt(j);
		if (j == 0)
		{

		}
		else
		{
			bool8 rec = 0;
			uint32* pdata = &p->Data[AngCfgNum].u32;
			uint32* pbfdata = &PointAt(j - 1)->Data[AngCfgNum].u32;
			for (uint32 i = 0; i < DigCfgNum; i++)
			{
				SalFileChannelDataCfg* cfg = &DataCfg[i + AngCfgNum];
				if (cfg->IsDisp && (cfg->Flag.st.isMidDig))
				{
					if (GetBit(pdata[i / 32], i % 32) != GetBit(pbfdata[i / 32], i % 32))
					{
						rec = 1;
						break;
					}
				}
			}
			if (!rec)
			{
				continue;
			}
		}
		str << (uint32)(p->SampSerNo + 1) << "," << (p->SampStamp / 1000) << "ms";
		file.Write(str.Str());
		str.Clear();
		for (uint32 i = 0; i < AngCfgNum; i++)
		{
			SalFileChannelDataCfg* cfg = &DataCfg[i];
			if (cfg->IsDisp && (cfg->Flag.st.isMidAng))
			{
				str << ",";
				str.FormatFloat(p->Data[i].f32, 7);
			}
		}
		file.Write(str.Str());
		str.Clear();
		uint32* pdata = &p->Data[AngCfgNum].u32;
		char d;
		for (uint32 i = 0; i < DigCfgNum; i++)
		{
			SalFileChannelDataCfg* cfg = &DataCfg[i + AngCfgNum];
			if (cfg->IsDisp && (cfg->Flag.st.isMidDig))
			{
				str << ",";
				d = GetBit(pdata[i / 32], i % 32) ? '1' : '0';
				str << d;
			}
		}
		file.WriteLine(str.Str());
		str.Clear();
	}
	file.Close();
	return 0;
}

int32 spt::SalFwData::SavePubDesFile(const char* FileName)
{
	SalFile file;
	file.Path().Set(CN_FWRECORD_FILE_ROOT);
	String5000B str;
	str = FileName;
	str << ".des";
	file.Name().Set(str.Str());
	file.Creat();
	str.Clear();
	str << ApiUnitCfg::Instance().FwRecId.StrData() << ",";
	str << "0";
	file.WriteLine(str.Str());
	str.Clear();

	uint32 dispAng = 0;
	uint32 dispDig = 0;
	for (uint32 i = 0; i < AngCfgNum; i++)
	{
		SalFileChannelDataCfg* cfg = &DataCfg[i];
		if (cfg->IsDisp && (cfg->Flag.st.isMidAng))
		{
			dispAng++;
		}
	}
	for (uint32 i = 0; i < DigCfgNum; i++)
	{
		SalFileChannelDataCfg* cfg = &DataCfg[i + AngCfgNum];
		if (cfg->IsDisp && (cfg->Flag.st.isMidDig))
		{
			dispDig++;
		}
	}
	str << (dispAng + dispDig) << "," << dispAng << "A," << dispDig << "D";
	file.WriteLine(str.Str());
	str.Clear();
	uint32 id = 1;
	for (uint32 i = 0; i < AngCfgNum; i++)
	{
		SalFileChannelDataCfg* cfg = &DataCfg[i];
		if (cfg->IsDisp && (cfg->Flag.st.isMidAng))
		{
			str << (id++) << ",";
			str << cfg->Name << ",FLOAT,";
			str << cfg->Unit << ",";
			str.FormatFloat(cfg->Primary.f32, 7) << ",";
			str.FormatFloat(cfg->Secondary.f32, 7) << ",";
			if (cfg->IsPrimary)
			{
				if (cfg->Primary.f32 != 0)
				{
					str.FormatFloat(cfg->Secondary.f32, 7) << ",";
				}
				else
				{
					str.FormatFloat(cfg->Secondary.f32 / cfg->Primary.f32, 7) << ",";
				}
			}
			else
			{
				str.FormatFloat(1, 3) << ",";
			}
			str << "1";
			file.WriteLine(str.Str());
			str.Clear();
		}
	}
	id = 1;
	for (uint32 i = 0; i < DigCfgNum; i++)
	{
		SalFileChannelDataCfg* cfg = &DataCfg[i + AngCfgNum];
		if (cfg->IsDisp && (cfg->Flag.st.isMidDig))
		{
			str << (id++) << ",";
			str << cfg->Name << ",";
			if (cfg->Y)
			{
				str << '1';
			}
			else
			{
				str << '0';
			}
			str << "1";
			file.WriteLine(str.Str());
			str.Clear();
		}
	}
	file.Close();
	return 0;
}

int32 spt::SalFwData::PrepareSaveData(SalFwRecordCfg* FwCfg)
{
	SalFwAnalogCfgArray& angcfg = FwCfg->AngCfg();
	uint32 anggnum = angcfg.InstNum();
	AngCfgNum = anggnum;
	for (uint32 i = 0; i < anggnum; i++)
	{
		SalFileChannelDataCfg* dcfg = &DataCfg[i];
		dcfg->Cn = i;
		SalFwAnalogCfgSignal* cfg = angcfg.GetCfg(i);
		dcfg->ChanType = cfg->Type();
		dcfg->Flag = cfg->Flags();
		StrNCpy(dcfg->Name, cfg->Name(), sizeof(DataCfg[i].Name));
		StrNCpy(dcfg->Unit, cfg->Units()->toString(), sizeof(DataCfg[i].Unit));
		if (EAP_Phase_Total > cfg->Phase())
		{
			StrNCpy(dcfg->Phase, EPhaseStr[cfg->Phase()].des, sizeof(DataCfg[i].Phase));
		}
		else
		{
			StrNCpy(dcfg->Phase, "", sizeof(DataCfg[i].Phase));
		}
		StrNCpy(dcfg->Ccbm, cfg->Ccbm().Str(), sizeof(DataCfg[i].Ccbm));
		dcfg->CoeA.f32 = cfg->CoeA();
		dcfg->CoeB.f32 = cfg->CoeB();
		dcfg->Skew.f32 = cfg->Skew();
		dcfg->Min.f32 = 1e37f;
		dcfg->Max.f32 = -1e37f;
		uint32 loop = SampWriter;
		for (uint32 j = 0; j < loop; j++)
		{
			float32 f32 = PointAt(i)->Data[j].f32;
			if (dcfg->Max.f32 < f32)
			{
				dcfg->Max.f32 = f32;
			}
			if (dcfg->Min.f32 > f32)
			{
				dcfg->Min.f32 = f32;
			}
		}
		dcfg->Primary.f32 = cfg->Primary();
		dcfg->Secondary.f32 = cfg->Secondary();
		dcfg->IsPrimary = cfg->IsPrimary();
		dcfg->Y = 0;
		dcfg->IsDisp = cfg->IsDisp();
	}
	SalFwDigitalCfgArray& digcfg = FwCfg->DigCfg();
	uint32 dignum = digcfg.InstNum();
	DigCfgNum = dignum;
	for (uint32 i = 0; i < dignum; i++)
	{
		SalFileChannelDataCfg* dcfg = &DataCfg[i + anggnum];
		dcfg->Cn = i;
		SalFwDigitalCfgSignal* cfg = digcfg.GetCfg(i);
		dcfg->ChanType = cfg->Type();
		dcfg->Flag = cfg->Flags();
		StrNCpy(dcfg->Name, cfg->Name(), sizeof(DataCfg[i].Name));
		StrNCpy(dcfg->Phase, cfg->Name(), sizeof(DataCfg[i].Phase));
		if (EAP_Phase_Total > cfg->Phase())
		{
			StrNCpy(dcfg->Phase, EPhaseStr[cfg->Phase()].des, sizeof(DataCfg[i].Phase));
		}
		else
		{
			StrNCpy(dcfg->Phase, "", sizeof(DataCfg[i].Phase));
		}
		dcfg->Unit[0] = 0;
		StrNCpy(dcfg->Ccbm, cfg->Ccbm().Str(), sizeof(DataCfg[i].Ccbm));
		dcfg->CoeA.f32 = 0;
		dcfg->CoeB.f32 = 0;
		dcfg->Skew.f32 = 0;
		dcfg->Min.f32 = 0;
		dcfg->Max.f32 = 0;
		dcfg->Primary.f32 = 0;
		dcfg->Secondary.f32 = 0;
		dcfg->IsPrimary = 0;
		dcfg->Y = cfg->SteadyState();
		dcfg->IsDisp = cfg->IsDisp();
	}
	uint32 loop = SampWriter;
	uint32 startSer = PointAt(0)->SampSerNo;
	uint64 FirstTime = PointAt(0)->SampStamp;
	for (uint32 i = 0; i < loop; i++)
	{
		PointAt(i)->SampSerNo -= startSer;
		PointAt(i)->SampStamp -= FirstTime;
	}
	if (SampWriter)
	{
		RecSampStampDif = PointAt(SampWriter - 1)->SampStamp - FirstTime;
		FirstSampT = PointAt(0)->SampUtc;
	}
	else
	{
		FirstSampT.Set((int64)0);
		FirstSampT.q.q = 0;
		RecSampStampDif = 0;
	}

	String1kB str;
	str = ApiUnitCfg::Instance().UnitRcdId.StrData();
	str << "_";
	str.Format(RecordSerNo, 2, '0');
	str << "_";
	TrigT.ToStrFmt43(str);
	str << "_";
	if (ActType == 1)
	{
		str << "f";
	}
	else
	{
		str << "s";
	}
	StrNCpy(fileName, str.Str(), sizeof(fileName));
	return 0;
}

bool8* spt::SalFwRtData::GetDigBuf(uint32 Index)
{
	if (Index < DigCellNum)
	{
		return &DigSampBuf[MaxSampPoint * Index];
	}
	return DigSampBuf;
}

bool8 spt::SalFwRtData::GetDig(uint32 DigIndex, uint32 Reader)
{
	return DigSampBuf[MaxSampPoint * DigIndex + Reader];
}

u32value* spt::SalFwRtData::GetU32Buf(uint32 AngIndex)
{
	if (AngIndex < AngCellNum)
	{
		return &U32SampBuf[MaxSampPoint * AngIndex];
	}
	return U32SampBuf;
}

u32value spt::SalFwRtData::GetU32(uint32 AngIndex, uint32 Reader)
{
	return U32SampBuf[MaxSampPoint * AngIndex + Reader];
}

bool8 spt::FwEventData::ToStr(SalString& Str)const
{
	SerNoToStr(Str);
	Str << ",";
	ActTimeToStr(Str);
	Str << ",";
	UtcTimeToStr(Str);
	Str << ",";
	Str << EventData.Name();
	Str << ",";
	EventData.ValueStr(EventData.oldStatus, Str, 40);
	Str << ",";
	EventData.ValueStr(EventData.status, Str, 40);
	Str << ",";
	const class SalStatus* s = EventData.StatusDes();
	if (s)
	{
		Str << s->IsDisp();
		Str << ",";
		Str.FormatHex(s->Flag().u32);
		Str << ",";
	}
	else
	{
		Str << ",,";
	}
	QStr(Str, 60);
	Str << ",";
	Str << BoardName() << ",";
	ExternInfoStr(Str, 500);
	return 1;
}
bool8 spt::FwEventData::SerNoToStr(SalString& Str)const
{
	Str.Format(EverntSerNo + 1, 4, 0, 1, ' ');
	return 1;
}

bool8 spt::FwEventData::ActTimeToStr(SalString& Str)const
{
	if (ActTimeMs < 10000)
	{
		Str.Format(ActTimeMs, 4, 0, 0, ' ') << "ms";
	}
	else if (ActTimeMs < 10000000)
	{
		Str.Format(ActTimeMs, 7, 0, 0, ' ') << "ms";
	}
	return 1;
}

bool8 spt::FwEventData::UtcTimeToStr(SalString& Str)const
{
	return EventData.UtcTimeToStr(Str, 40);
}

bool8 spt::FwEventData::ActStr(SalString& Str)const
{
	return EventData.ActStr(Str, 40);
}

bool8 spt::FwEventData::ExternInfoStr(SalString& Str, uint32 LineW)const
{
	uint32 Loop = EventData.ExternInfoNum();
	Str << Loop << ",";
	String100B name, data, unit;
	for (uint32 i = 0; i < Loop; i++)
	{
		EventData.ExternInfoStr(i, name, data, unit);
		Str << name << "," << data << "," << unit << ",";
	}
	return 1;
}

bool8 spt::FwEventData::QStr(SalString& Str, uint16 LineW) const
{
	return  EventData.QStr(Str, LineW);
}

const char* spt::FwEventData::BoardName() const
{
	return EventData.BoardName();
}
