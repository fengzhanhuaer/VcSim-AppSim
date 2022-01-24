#include "SptProject.h"
#include "SalAnglogRms.h"
using namespace spt;

const SalEnumDes spt::EPhaseStr[EAP_Phase_Total] =
{
	{EAP_Null,""},
	{EAP_A,"A"},
	{EAP_B,"B"},
	{EAP_C,"C"},
	{EAP_Z,"Z"},
	{EAP_AB,"AB"},
	{EAP_BC,"BC"},
	{EAP_CA,"CA"},
	{EAP_ABC,"ABC"},
	{EAP_AZ,"AZ"},
	{EAP_BZ,"BZ"},
	{EAP_CZ,"CZ"},
	{EAP_ABZ,"ABZ"},
	{EAP_BCZ,"BCZ"},
	{EAP_CAZ,"CAZ"},
	{EAP_ABCZ,"ABCZ"},
};

void spt::SalAngRms::PowerUpIni(const char* Name, const char* DesName, SalAngRmsGroup* Group, bool8 IsBase, uint16 Data1DotNum, const VarUnits* Units1, uint16 Data2DotNum, const VarUnits* Units2, uint16 QLen)
{
	stateNum = 0;
	data1DotNum = (uint8)Data1DotNum;
	data2DotNum = (uint8)Data2DotNum;
	data3Len = (uint8)QLen;
	oriunits1 = Units1;
	oriunits2 = Units2;
	isBase = IsBase;
	InstObject::PowerUpIni(Name, DesName, Group, EIOT_AngRms, Group->InstId(), Group->InstNum());
	if (transunits1)
	{
		transunits1 = oriunits1;
	}
	if (transunits2)
	{
		transunits2 = oriunits2;
	}
	isDisp = 1;
}

bool8 spt::SalAngRms::PushData(int32 Data1, int32 Data2, uint32 Q)
{
	angRms.data1 = Data1;
	angRms.data2 = Data2;
	angRms.q = Q;
	SalAngRmsGroup* Group = (SalAngRmsGroup*)group;
	Group->Set(instId, angRms);
	return 1;
}

uint32 spt::SalAngRms::DataNum()
{
	return dataNum;
}
const i32AngRms& spt::SalAngRms::RealData()
{
	return angRms;
}
const VarUnits* spt::SalAngRms::Units1()
{
	return oriunits1;
}
const VarUnits* spt::SalAngRms::Units2()
{
	return oriunits2;
}
const VarUnits* spt::SalAngRms::TransUnits1()
{
	return transunits1;
}
const VarUnits* spt::SalAngRms::TransUnits2()
{
	return transunits2;
}
bool8 spt::SalAngRms::IsDisp()
{
	return isDisp;
}

void spt::SalAngRmsGroup::PowerUpIni(const char* Name, const char* DesName, uint16 EventNum, uint32 BufLen)
{
	InstObjectGroup::PowerUpIni(Name, DesName, EIOT_AngRms, EventNum);
	AllocBuf buf(0);
	buf.Alloc(sizeof(i32AngRms) * EventNum, BufLen);
	ringBuf.SetBuf(&buf);
	startStore = 0;
}

void spt::SalAngRmsGroup::Set(uint32 Index, const i32AngRms& Rms)
{
	if (Index < instNum)
	{
		i32AngRms* buf = (i32AngRms*)ringBuf.GetNextWriteBuf();
		buf[Index] = Rms;
	}
}

void spt::SalAngRmsGroup::Update(bool8 AdJustAngle)
{
	ringBuf.Writer();
	i32AngRms* buf = (i32AngRms*)ringBuf.GetNextWriteBuf();
	if (AdJustAngle)
	{
		SalAngRms* c;
		int32 Base = 0;
		int32 full = 360;
		for (uint32 i = 0; i < instNum; i++)
		{
			c = Cell(i);
			if (c->IsBase())
			{
				Base = buf[c->InstId()].data2;
				full = 360 * MinUint32DecData(c->Data2DotNum() + 1);
				buf[c->InstId()].data2 = 0;
			}
			else if (c->Units2() == &Unit_ANGLE)
			{
				buf[c->InstId()].data2 = (buf[c->InstId()].data2 + full - Base) % full;
			}
		}
	}
	ringBuf.WriterAdd(1);
	if (startStore)
	{
		ringBuf.ReaderAdd(1);
	}
	startStore = 1;
}

uint32 spt::SalAngRmsGroup::GetNewestDataIndex()
{
	return ringBuf.Reader() % ringBuf.ElementNum();
}

SalAngRms* spt::SalAngRmsGroup::Cell(uint32 InstId)
{
	InstObject* b = GetObject(InstId);
	if (b)
	{
		return (SalAngRms*)b;
	}
	return 0;
}

const i32AngRms* spt::SalAngRmsGroup::GetRealData(uint32 BufIndex, uint32 InstId)
{
	if (InstId < instNum)
	{
		i32AngRms* buf = (i32AngRms*)ringBuf.Get(BufIndex);
		return &buf[InstId];
	}
	return 0;
}

const char* spt::GetPhaseStr(uint32 Phase)
{
	if (Phase< EAP_Phase_Total)
	{
		return EPhaseStr[Phase].des;
	}
	return EPhaseStr[EAP_Null].des;
}

uint32 spt::ConvertAngBitPhase2AngPhase(uint32 BitPhase)
{
	if (BitPhase < EABP_Phase_Total)
	{
		const uint8 phase[EABP_Phase_Total] = { EAP_A ,EAP_B,EAP_AB,EAP_C,EABP_CA,EABP_BC,EABP_ABC,EABP_Z,EABP_AZ,EABP_BZ,EABP_ABZ,EABP_CZ,EABP_CAZ,EABP_BCZ,EABP_ABCZ };
		return phase[BitPhase];
	}
	return 0;
}
