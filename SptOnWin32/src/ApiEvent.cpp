#include "ApiProject.h"
using namespace spt;

void spt::ApiStatus::BlPowerUpIni(const char* Name, const char* DesName, ApiStatusGroup& Group, uint32 flag)
{
	SalStatus::PowerUpIni(Name, DesName, (SalStatusGroup*)&Group, flag, E_BOOL);
}

void spt::ApiStatus::ExInfoPowerUpIni(StatusExInfoDesItem* Inf1, StatusExInfoDesItem* Inf2, StatusExInfoDesItem* Inf3)
{
	SalStatus::ExInfoPowerUpIni(Inf1, Inf2, Inf3, 0, 0, 0, 0, 0, 0);
}

void spt::ApiStatus::ExInfoPowerUpIni(StatusExInfoDesItem* Inf1, StatusExInfoDesItem* Inf2, StatusExInfoDesItem* Inf3, StatusExInfoDesItem* Inf4, StatusExInfoDesItem* Inf5, StatusExInfoDesItem* Inf6)
{
	SalStatus::ExInfoPowerUpIni(Inf1, Inf2, Inf3, Inf4, Inf5, Inf6, 0, 0, 0);
}

void spt::ApiStatus::ExInfoPowerUpIni(StatusExInfoDesItem* Inf1, StatusExInfoDesItem* Inf2, StatusExInfoDesItem* Inf3, StatusExInfoDesItem* Inf4, StatusExInfoDesItem* Inf5, StatusExInfoDesItem* Inf6, StatusExInfoDesItem* Inf7, StatusExInfoDesItem* Inf8, StatusExInfoDesItem* Inf9)
{
	SalStatus::ExInfoPowerUpIni(Inf1, Inf2, Inf3, Inf4, Inf5, Inf6, Inf7, Inf8, Inf9);
}

void spt::ApiStatus::UpdateStatus(u32value S1, u32value S2, u32value S3)
{
	SalStatus::UpdateStatus(S1, S2, S3);
}

void spt::ApiStatus::UpdateStatus(u32value S1, u32value S2, u32value S3, u32value S4, u32value S5, u32value S6)
{
	SalStatus::UpdateStatus(S1, S2, S3, S4, S5, S6);
}

void spt::ApiStatus::UpdateStatus(u32value S1, u32value S2, u32value S3, u32value S4, u32value S5, u32value S6, u32value S7, u32value S8, u32value S9)
{
	SalStatus::UpdateStatus(S1, S2, S3, S4, S5, S6, S7, S8, S9);
}
void spt::ApiEvent::UpdateStatus(u32value S1, u32value S2, u32value S3)
{
	SalStatus::UpdateStatus(S1, S2, S3);
}

void spt::ApiEvent::UpdateStatus(u32value S1, u32value S2, u32value S3, u32value S4, u32value S5, u32value S6)
{
	SalStatus::UpdateStatus(S1, S2, S3, S4, S5, S6);
}

void spt::ApiEvent::UpdateStatus(u32value S1, u32value S2, u32value S3, u32value S4, u32value S5, u32value S6, u32value S7, u32value S8, u32value S9)
{
	SalStatus::UpdateStatus(S1, S2, S3, S4, S5, S6, S7, S8, S9);
}

void spt::ApiStatus::DpPowerUpIni(const char* Name, const char* DesName, ApiStatusGroup& Group, uint32 flag)
{
	SalStatus::PowerUpIni(Name, DesName, (SalStatusGroup*)&Group, flag, E_DPOS);
}

bool8 spt::ApiStatus::Update(uint32 Status)
{
	if (ifNeedUpdate(Status) && SalStatus::Update(Status, 0, 0))
	{
		afterSave();
		return 1;
	}
	return 0;
}

bool8 spt::ApiStatus::Update(uint32 Status, SalDateStamp& stamp)
{
	if (ifNeedUpdate(Status) && SalStatus::Update(Status, &stamp, 0))
	{
		afterSave();
		return 1;
	}
	return 0;
}

bool8 spt::ApiStatus::Update(uint32 Status, SalDateStamp& stamp, StatusQ& Q)
{
	if (ifNeedUpdate(Status) && SalStatus::Update(Status, &stamp, &Q))
	{
		afterSave();
		return 1;
	}
	return 0;
}

bool8 spt::ApiStatus::SetState(uint32 Status, SalDateStamp& stamp, StatusQ& Q)
{
	if (SalStatus::setValue(Status, &stamp, &Q))
	{
		afterSave();
		return 1;
	}
	return 0;
}

const u32value& spt::ApiStatus::Value() const
{
	return SalStatus::Value();
}

const u32value& spt::ApiStatus::OldValue() const
{
	return SalStatus::OldValue();
}

void spt::ApiStatus::SetDisp(bool8 Disp)
{
	SalStatus::SetDisp(Disp);
}

void spt::ApiStatusGroup::PowerUpIni(const char* Name, const char* DesName, uint16 EventNum)
{
	PowerUpIni(Name, DesName, EventNum, 0, 0, 0);
}

void spt::ApiStatusGroup::PowerUpIni(const char* Name, const char* DesName, uint16 EventNum, SalEnumDes* BoardDes, uint8 BoardTypeNum, uint8 BoardIndex)
{
	SalStatusGroup::PowerUpIni(Name, DesName, EventNum, BoardDes, BoardTypeNum, BoardIndex);
	appFlags = &ApiIoGlobalFlag::Instance().AppFlags();
}

void spt::ApiEventGroup::PowerUpIni(const char* Name, const char* DesName, uint16 EventNum, uint32 EventPoolSize)
{
	PowerUpIni(Name, DesName, EventNum, EventPoolSize, 0, 0, 0);
}

void spt::ApiEventGroup::PowerUpIni(const char* Name, const char* DesName, uint16 EventNum, uint32 EventPoolSize, SalEnumDes* BoardDes, uint8 BoardTypeNum, uint8 BoardIndex)
{
	SalEventGroup::PowerUpIni(Name, DesName, EventNum, EventPoolSize, &ApiIoGlobalFlag::Instance().AppFlags(), BoardDes, BoardTypeNum, BoardIndex);
}

void spt::ApiEventGroup::ClearEvent()
{
	SalEventGroup::ClearEvent();
}

void spt::ApiEvent::BlPowerUpIni(const char* Name, const char* DesName, ApiEventGroup& Group, uint32 flag)
{
	SalEvent::PowerUpIni(Name, DesName, (SalEventGroup*)&Group, E_BOOL, flag);
}

void spt::ApiEvent::Hex8PowerUpIni(const char* Name, const char* DesName, ApiEventGroup& Group, uint32 flag)
{
	SalEvent::PowerUpIni(Name, DesName, (SalEventGroup*)&Group, E_Hex8, flag);
}

void spt::ApiEvent::Hex16PowerUpIni(const char* Name, const char* DesName, ApiEventGroup& Group, uint32 flag)
{
	SalEvent::PowerUpIni(Name, DesName, (SalEventGroup*)&Group, E_Hex16, flag);
}

void spt::ApiEvent::ExInfoPowerUpIni(StatusExInfoDesItem* Inf1, StatusExInfoDesItem* Inf2, StatusExInfoDesItem* Inf3)
{
	SalEvent::ExInfoPowerUpIni(Inf1, Inf2, Inf3, 0, 0, 0, 0, 0, 0);
}

void spt::ApiEvent::ExInfoPowerUpIni(StatusExInfoDesItem* Inf1, StatusExInfoDesItem* Inf2, StatusExInfoDesItem* Inf3, StatusExInfoDesItem* Inf4, StatusExInfoDesItem* Inf5, StatusExInfoDesItem* Inf6)
{
	SalEvent::ExInfoPowerUpIni(Inf1, Inf2, Inf3, Inf4, Inf5, Inf6, 0, 0, 0);
}

void spt::ApiEvent::ExInfoPowerUpIni(StatusExInfoDesItem* Inf1, StatusExInfoDesItem* Inf2, StatusExInfoDesItem* Inf3, StatusExInfoDesItem* Inf4, StatusExInfoDesItem* Inf5, StatusExInfoDesItem* Inf6, StatusExInfoDesItem* Inf7, StatusExInfoDesItem* Inf8, StatusExInfoDesItem* Inf9)
{
	SalEvent::ExInfoPowerUpIni(Inf1, Inf2, Inf3, Inf4, Inf5, Inf6, Inf7, Inf8, Inf9);
}

void spt::ApiEvent::DpPowerUpIni(const char* Name, const char* DesName, ApiEventGroup& Group, uint32 flag)
{
	SalEvent::PowerUpIni(Name, DesName, (SalEventGroup*)&Group, E_DPOS, flag);
}

void spt::ApiEvent::SetDisp(bool8 Disp)
{
	SalEvent::SetDisp(Disp);
}

bool8 spt::ApiEvent::Update(uint32 Status)
{
	if (ifNeedUpdate(Status) && SalEvent::Update(Status, 0, 0))
	{
		//	LogMsg.Stamp() << name << " change " << Status << "\n";
		afterSave();
		return 1;
	}
	return 0;
}

bool8 spt::ApiEvent::Update(uint32 Status, SalDateStamp& stamp)
{
	if (ifNeedUpdate(Status) && SalEvent::Update(Status, &stamp, 0))
	{
		afterSave();
		return 1;
	}
	return 0;
}

bool8 spt::ApiEvent::Update(uint32 Status, StatusQ& Q)
{
	if (ifNeedUpdate(Status) && SalEvent::Update(Status, 0, &Q))
	{
		afterSave();
		return 1;
	}
	return 0;
}

bool8 spt::ApiEvent::Update(uint32 Status, SalDateStamp& stamp, StatusQ& Q)
{
	if (ifNeedUpdate(Status) && SalEvent::Update(Status, &stamp, &Q))
	{
		afterSave();
		return 1;
	}
	return 0;
}

bool8 spt::ApiEvent::SetState(uint32 Status, SalDateStamp& stamp, StatusQ& Q)
{
	if (SalEvent::SetValue(Status, &stamp, &Q))
	{
		afterSave();
		return 1;
	}
	return 0;
}

const u32value& spt::ApiEvent::Value() const
{
	return SalEvent::Value();
}

const u32value& spt::ApiEvent::OldValue() const
{
	return SalEvent::OldValue();
}
void spt::ApiEventViewPool::GetValid(SalEventGroup* Group, uint64 TimeStart, uint64 TimeEnd, bool8 isDisp)
{
	uint32 Num = Group->ValidNum();
	if (Num >= recordPoolLen)
	{
		Num = recordPoolLen;
	}
	//LogMsg << Group->Name() << Num << "\n";
	uint32 valiNum = 0;
	int32 reader = Group->OldestEventIndex();
	for (uint32 i = 0; i < Num; i++)
	{
		reader = Group->GetNextValidEvent(reader, 0, record[valiNum], isDisp);
		if (reader < 0)
		{
			break;
		}
		reader++;
		if (record[valiNum].IsCrcOk() == 0)
		{
			continue;
		}
		if (((uint64)record[valiNum].stamp >= TimeStart && ((uint64)record[valiNum].stamp <= TimeEnd)))
		{
			valiNum++;
		}
	}
	validRecordNum = valiNum;
}

void spt::ApiEventViewPool::PowerUpIni(uint32 PoolSize)
{
	recordPoolLen = PoolSize;
	validRecordNum = 0;
	record = (StatusData*)Calloc(sizeof(StatusData), recordPoolLen);
	if (record == 0)
	{
		LogErr.Stamp() << "ApiEventViewPool Calloc err.\n";
	}
}
