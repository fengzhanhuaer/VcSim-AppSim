#include "ApiProject.h"
using namespace spt;

uint32 spt::ApiParaGroup::GetCrc(uint16 Zone)
{
	if (Zone >= maxZone)
	{
		return 0;
	}
	return usingData.Group(Zone)->GetCrc();
}

uint16 spt::ApiParaGroup::CurZone()
{
	return UsingZone();
}

void spt::ApiParaGroup::PowerUpIni(const char* Name, const char* DesName, uint16 CurZone, uint16 MaxZone, uint16 ElementNum)
{
	if (MaxZone > 30)
	{
		MaxZone = 30;
	}
	if (MaxZone < 1)
	{
		MaxZone = 1;
	}
	appFlags = &ApiIoGlobalFlag::Instance().AppFlags();
	SalParaGroup::PowerUpIni(Name, DesName, CurZone, MaxZone, ElementNum);
}

void spt::ApiParaGroup::PowerUpIni(const char* Name, const char* DesName, uint16 ElementNum)
{
	appFlags = &ApiIoGlobalFlag::Instance().AppFlags();
	SalParaGroup::PowerUpIni(Name, DesName, 0, 1, ElementNum);
}

int32 spt::ApiParaGroup::CheckStatus()
{
	return SalParaGroup::CheckStatus();
}

int32 spt::ApiParaGroup::CheckStatus(uint16 Zone)
{
	return DataGroup().Group(Zone)->header.status;
}

int32 spt::ApiParaGroup::DefaultData()
{
	return SalParaGroup::DefaultData();
}

uint16 spt::ApiParaGroup::DataChangeCnt()
{
	return DataChanCnt();
}

uint16 spt::ApiParaGroup::DataChangeCnt(uint16 Zone)
{
	return DataGroup().Group(Zone)->header.dataChanCnt;
}

bool8 spt::ApiParaGroup::UpdateForUse()
{
	return SalParaGroup::UpdateForUse();
}

const stAppFlags* spt::ApiParaGroup::AppFlags()const
{
	return SalParaGroup::AppFlags();
}

int32 spt::ApiParaGroup::GetSaveStepFlag(uint32 Zone)
{
	return getSaveStepFlag(Zone);
}

int32 spt::ApiParaGroup::LoadBakParaForUse(int32 ZoneNum)
{
	return loadBakParaForUse(ZoneNum);
}


void spt::ApiPara::PowerUpIni(const char* Name, const char* DesName, ApiParaGroup& Group, int32 Min, int32 Def, int32 Max, uint8 DotNum, const VarUnits& Units)
{
	ApiPara::PowerUpIni(Name, DesName, Group, Min, Def, Max, DotNum, Units, -1);
}

void spt::ApiPara::PowerUpIni(const char* Name, const char* DesName, ApiParaGroup& Group, int32 Min, int32 Def, int32 Max, uint8 DotNum, const VarUnits& Units, int32 ExInfo)
{
	SalPara::PowerUpIni(Name, DesName, (SalParaGroup*)&Group, Min, Def, Max, DotNum, E_PT_Int32, Units);
	exInfo1.valueType = E_SVT_I32;
	exInfo1.value.i32 = ExInfo;
}

void spt::ApiPara::SetRange(int32 Max, int32 Min)
{
	SalPara::SetRange(Max, Min);
}

void spt::ApiPara::SetDisp(bool8 Disp)
{
	SalPara::SetDisp(Disp);
}

int32 spt::ApiPara::Int32()
{
	return SalPara::Int32();
}

float32 spt::ApiPara::Float32()
{
	return SalPara::Float32();
}

void spt::ApiPara::BlPowerUpIni(const char* Name, const char* DesName, ApiParaGroup& Group, int32 Def)
{
	SalPara::PowerUpIni(Name, DesName, (SalParaGroup*)&Group, 0, Def, 1, 0, E_PT_Int32, Unit_NULL);
}

bool8 spt::ApiPara::Bool()
{
	return SalPara::Int32();
}

void spt::ApiPara::StrPowerUpIni(const char* Name, const char* DesName, ApiParaGroup& Group, const char* DefName)
{
	SalPara::PowerUpIni(Name, DesName, (SalParaGroup*)&Group, 0, (int32)DefName, 32, 0, E_PT_Str, Unit_NULL);
}

const char* spt::ApiPara::StrData()
{
	return usingValue.value.cstr;
}

void spt::ApiPara::ZonePowerUpIni(const char* Name, const char* DesName, ApiParaGroup& Group, int32 Min, int32 Def, int32 Max, uint8 DotNum, const VarUnits& Units)
{
	SalPara::PowerUpIni(Name, DesName, (SalParaGroup*)&Group, Min, Def, Max, DotNum, E_PT_Zone, Units);
	flags.st.isReadOnly = 1;
}

void spt::ApiPara::EnumPowerUpIni(const char* Name, const char* DesName, ApiParaGroup& Group, int32 Def, SalEnumDes* Enum, uint8 EnumNum, const VarUnits& Units)
{
	SalPara::PowerUpIni(Name, DesName, (SalParaGroup*)&Group, 0, Def, EnumNum - 1, 0, E_PT_Enum, Units);
	exInfo1.valueType = E_SVT_ENUMDES | E_SVT_PTR;
	exInfo1.valueInfo1 = EnumNum;
	exInfo1.value.vptr = Enum;
}

int32 spt::ApiPara::EnumIndex()
{
	return SalPara::Int32();
}
int32 spt::ApiPara::EnumVal()
{
	return SalPara::EnumVal();
}
static SalEnumDes CtSecondEnum[2] =
{
	{1,"1"},
	{5,"5"}
};
void spt::ApiPara::CTEnumPowerUpIni(const char* Name, const char* DesName, ApiParaGroup& Group, int32 Def)
{
	if (Def == 5)
	{
		Def = 1;
	}
	else
	{
		Def = 0;
	}
	SalPara::PowerUpIni(Name, DesName, (SalParaGroup*)&Group, 0, Def, 1, 0, E_PT_Ct_Second, Unit_A);
	exInfo1.valueType = E_SVT_ENUMDES | E_SVT_PTR;
	exInfo1.valueInfo1 = 2;
	exInfo1.value.vptr = CtSecondEnum;
}

int32 spt::ApiPara::CtValue()
{
	return EnumVal();
}

void spt::ApiPara::RelatedCTPowerUpIni(const char* Name, const char* DesName, ApiParaGroup& Group, int32 Min, int32 Default, int32 Max, uint8 DotNum, const VarUnits& Units, ApiPara& SecondCt)
{
	SalPara::PowerUpIni(Name, DesName, (SalParaGroup*)&Group, Min, Default, Max, DotNum, E_PT_Int32, Units);
	flags.st.isRelatedOthoers = 1;
	exInfo1.valueType = E_SVT_INSTOBJECT | E_SVT_PTR;
	exInfo1.value.vptr = (SalPara*)&SecondCt;
}

void spt::ApiPara::UnitOnOffPowerUpIni(const char* Name, const char* DesName, ApiParaGroup& Group, int32 Default)
{
	SalPara::PowerUpIni(Name, DesName, (SalParaGroup*)&Group, 0, Default, 1, 0, E_PT_UnitSet, Unit_NULL);
}

void spt::ApiPara::BitOnOffPowerUpIni(const char* Name, const char* DesName, ApiParaGroup& Group, uint32 Min, uint32 Default, uint32 Max, uint32 ByteNum, SalBitDes* Des)
{
	if (ByteNum == 1)
	{
		SalPara::PowerUpIni(Name, DesName, (SalParaGroup*)&Group, 0, Default, Max, 0, E_PT_BIT8, Unit_NULL);
		exInfo1.valueType = E_SVT_BITDES | E_SVT_PTR;
		exInfo1.value.vptr = Des;
		exInfo1.valueInfo1 = 8;
	}
	else if (ByteNum == 2)
	{
		SalPara::PowerUpIni(Name, DesName, (SalParaGroup*)&Group, 0, Default, Max, 0, E_PT_BIT16, Unit_NULL);
		exInfo1.valueType = E_SVT_BITDES | E_SVT_PTR;
		exInfo1.value.vptr = Des;
		exInfo1.valueInfo1 = 16;
	}
	else if (ByteNum == 4)
	{
		SalPara::PowerUpIni(Name, DesName, (SalParaGroup*)&Group, 0, Default, Max, 0, E_PT_BIT32, Unit_NULL);
		exInfo1.valueType = E_SVT_BITDES | E_SVT_PTR;
		exInfo1.value.vptr = Des;
		exInfo1.valueInfo1 = 32;
	}
}

uint32 spt::ApiPara::Uint32()
{
	return SalPara::Uint32();
}

void spt::ApiPara::HexPowerUpIni(const char* Name, const char* DesName, ApiParaGroup& Group, uint32 Min, uint32 Default, uint32 Max, uint32 ByteNum)
{
	if (ByteNum == 1)
	{
		SalPara::PowerUpIni(Name, DesName, (SalParaGroup*)&Group, Min, Default, Max, 0, E_PT_HEX8, Unit_NULL);
	}
	else if (ByteNum == 2)
	{
		SalPara::PowerUpIni(Name, DesName, (SalParaGroup*)&Group, Min, Default, Max, 0, E_PT_HEX16, Unit_NULL);
	}
	else if (ByteNum == 4)
	{
		SalPara::PowerUpIni(Name, DesName, (SalParaGroup*)&Group, Min, Default, Max, 0, E_PT_HEX32, Unit_NULL);
	}
}
void spt::ApiPara::UInt32PowerUpIni(const char* Name, const char* DesName, ApiParaGroup& Group, uint32 Min, uint32 Default, uint32 Max, uint8 DotNum, const VarUnits& Units, int32 ExInfo)
{
	SalPara::PowerUpIni(Name, DesName, (SalParaGroup*)&Group, Min, Default, Max, DotNum, E_PT_UInt32, Units);
	exInfo1.valueType = E_SVT_I32;
	exInfo1.value.i32 = ExInfo;
}
