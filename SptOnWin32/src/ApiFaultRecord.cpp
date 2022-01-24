#include"ApiProject.h"
using namespace spt;

void spt::ApiFwDigital::PowerUpIni(const char* Name, const char* DesName, ApiFwRecordGroup& Group, E_Ang_Phase Phase, const char* Ccbm, bool8 SteadyState, uint32 Flag, uint16 UpBeforeSetCnt, uint16 UpAfterSetCnt, uint16 DownBeforeSetCnt, uint16 DownAfterSetCnt, bool8 IsDisp)
{
	SalFwDigitalCfgSignal::PowerUpIni(Name, DesName, (SalFwRecordGroup*)&Group, Phase, Ccbm, SteadyState, Flag, UpBeforeSetCnt, UpAfterSetCnt, DownBeforeSetCnt, DownAfterSetCnt, IsDisp);
}

void spt::ApiFwDigital::Update(uint32 Value)
{
	SalFwDigitalCfgSignal::SetValue(Value == 1);
}

void spt::ApiFwDigital::SetDisp(bool8 Disp)
{
	SalFwWaveCfgCell::SetDisp(Disp);
}

void spt::ApiFwAnalog::PowerUpIni(const char* Name, const char* DesName, ApiFwRecordGroup& Group, E_Ang_Phase Phase, const char* Ccbm, const VarUnits& Units, float32 Skew, float32 CoeA, float32 CoeB, float32 Primary, float32 Secondary, bool8 IsPrimary, uint32 Flag, bool8 IsDisp)
{
	SalFwAnalogCfgSignal::PowerUpIni(Name, DesName, (SalFwRecordGroup*)&Group, Phase, Ccbm, Units, Skew, CoeA, CoeB, Primary, Secondary, IsPrimary, Flag, IsDisp);
}

void spt::ApiFwAnalog::Update(float32 Value)
{
	SetValue(Value);
}

void spt::ApiFwAnalog::SetCoePS(float32 Primary, float32 Secondary)
{
	SalFwAnalogCfgSignal::SetCoePS(Primary, Secondary);
}

void spt::ApiFwAnalog::SetDisp(bool8 Disp)
{
	SalFwWaveCfgCell::SetDisp(Disp);
}

void spt::ApiFwEvent::PowerUpIni(const char* Name, const char* DesName, ApiEvent& Event, ApiFwRecordGroup& Group, E_Ang_Phase Phase, const char* Ccbm, bool8 SteadyState, uint32 Flag, uint16 UpBeforeSetCnt, uint16 UpAfterSetCnt, uint16 DownBeforeSetCnt, uint16 DownAfterSetCnt, bool8 IsDisp)
{
	SalFwEventCfgSignal::PowerUpIni(Name, DesName, (SalEvent*)&Event, (SalFwRecordGroup*)&Group, Phase, Ccbm, SteadyState, Flag, UpBeforeSetCnt, UpAfterSetCnt, DownBeforeSetCnt, DownAfterSetCnt, IsDisp);
}

void spt::ApiFwEvent::SetDisp(bool8 Disp)
{
	SalFwWaveCfgCell::SetDisp(Disp);
	if (pEvent)
	{
		pEvent->SetDisp(Disp);
	}
}

void spt::ApiFwRecordGroup::PowerUpIni(const char* Name, const char* DesName, uint32 SysFreq, uint32 SampPerCircle, int32 MaxRecordPoint, uint16 UpBeforeSetCnt, uint16 UpAfterSetCnt, uint16 FwAngMaxNum, uint16 FwDigMaxNum, uint16 FwEventMaxNum, uint32 Flag)
{
	SalFwRecordGroup::PowerUpIni(Name, DesName, SysFreq, SampPerCircle, MaxRecordPoint, UpBeforeSetCnt, UpAfterSetCnt, FwAngMaxNum, FwDigMaxNum, FwEventMaxNum, 1, 1, 1, 1, Flag);
}

void spt::ApiFwRecordGroup::RecordOnePoint(SalDateStamp& stamp, uint64 SampStamp)
{
	SalFwRecordGroup::RecordOnePoint(stamp, SampStamp);
}

int32 spt::ApiFwRecordGroup::SetParaGroup(int32 Index, ApiParaGroup* Group)
{
	return SalFwRecordGroup::SetParaGroup(Index, (SalParaGroup*)Group);
}

int32 spt::ApiFwRecordGroup::SetActType(uint32 Type)
{
	SalFwRecordGroup::SetActType(Type);
	return 0;
}

void spt::ApiFwRecordGroup::ClearRecord()
{
	SalFwRecordGroup::ClearRecord();
	return;
}

void spt::ApiFwRecordGroup::StartRecord(bool8 isStart)
{
	SalFwRecordGroup::StartRecord(isStart);
}
