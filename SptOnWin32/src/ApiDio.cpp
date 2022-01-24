#include "ApiProject.h"
using namespace spt;

uint32 spt::ApiBoardNormalStateIn::Bit32(uint32 InNo)
{
	return rtValue[InNo];
}

const SalDateStamp& spt::ApiBoardNormalStateIn::Stamp()
{
	return stamp;
}

uint32 spt::ApiBoardNormalStateIn::Bit32(uint32 Index, uint32 InNo)
{
	return ringBuf->GetNewWrited(Index)->value[InNo].u32;
}

const SalDateStamp& spt::ApiBoardNormalStateIn::Stamp(uint32 Index)
{
	return ringBuf->GetNewWrited(Index)->stamp;
}

void spt::ApiNormalBoolIn::PowerUpIni(ApiBoardNormalStateIn& Board, const char* Name, const char* DesName, uint16 InNo)
{
	SptNormalStateInCell::PowerUpIni(Name, DesName, (HalBoard*)&Board, E_Normal_YX, InNo);
}

uint32 spt::ApiNormalBoolIn::StateNum()
{
	return stateNmb;
}

bool8 spt::ApiNormalBoolIn::Value()
{
	return value.value.bl;
}
bool8 spt::ApiNormalBoolIn::Value(uint32 Index)
{
	return ringBuf->GetNewWrited(Index)->value.bl;
}
const SalDateStamp& spt::ApiNormalBoolIn::Stamp()
{
	return value.stamp;
}

const SalDateStamp& spt::ApiNormalBoolIn::Stamp(uint32 Index)
{
	return ringBuf->GetNewWrited(Index)->stamp;
}

void spt::ApiBoardNormalStateIn::PowerUpIni(const char* Name, const char* DesName, uint16 CardType, uint16 CardAddr, uint16 FrameIndex)
{
	if (CardType == E_Board_YX32Pin_1)
	{
		SptNormalStateInBoard::PowerUpIni(Name, DesName, CardType, 32);
		SetCardAddr(CardAddr);
		frameIndex = FrameIndex;
	}
	else if (CardType == E_Board_DIO_YX14_1)
	{
		SptNormalStateInBoard::PowerUpIni(Name, DesName, CardType, 32);
		SetCardAddr(CardAddr);
		frameIndex = FrameIndex;
	}
	else if (CardType == E_Board_OPB_YX_1)
	{
		SptNormalStateInBoard::PowerUpIni(Name, DesName, CardType, 32);
		SetCardAddr(CardAddr);
		frameIndex = FrameIndex;
	}
	else
	{
		LogErr.Stamp() << Name << "PowerUpIni Err.\n";
	}
}

uint32 spt::ApiBoardNormalStateIn::StateNum()
{
	return stateNmb;
}

void spt::ApiBoardNormalStateOut::PowerUpIni(const char* Name, const char* DesName, uint16 CardType, uint16 CardAddr, uint16 FrameIndex)
{
	if (CardType == E_Board_Do32Pin_1)
	{
		//const struct ApiAppCfg* cfg = SptMain::Instance().AppCfg();
		frameIndex = FrameIndex;
		SetCardAddr(CardAddr);
		SptNormalStateOutBoard::PowerUpIni(Name, DesName, CardType, 32);
	}
	else if (CardType == E_Board_DIO_DO7_1)
	{
		//const struct ApiAppCfg* cfg = SptMain::Instance().AppCfg();
		frameIndex = FrameIndex;
		SetCardAddr(CardAddr);
		SptNormalStateOutBoard::PowerUpIni(Name, DesName, CardType, 32);
	}
	else
	{
		LogErr.Stamp() << Name << "PowerUpIni Err.\n";
	}
}

const SalDateStamp& spt::ApiBoardNormalStateOut::Stamp()
{
	return stamp;
}

const SalDateStamp& spt::ApiBoardNormalStateOut::StateStamp()
{
	return stateStamp;
}

uint32 spt::ApiBoardNormalStateOut::VerfyCode(uint32 InNo)
{
	return rtOutState[0];
}

uint32 spt::ApiBoardNormalStateOut::VerfyCodeNum()
{
	return rtOutStateNum;
}

void spt::ApiNormalBoolOut::ProtOutPowerUpIni(ApiBoardNormalStateOut& Board, const char* Name, const char* DesName, uint16 InNo)
{
	SptNormalStateOutCell::PowerUpIni(Name, DesName, (HalBoard*)&Board, E_Normal_Prot_Do, InNo);
}

void spt::ApiNormalBoolOut::ProtStartPowerUpIni(ApiBoardNormalStateOut& Board, const char* Name, const char* DesName)
{
	SptNormalStateOutCell::PowerUpIni(Name, DesName, (HalBoard*)&Board, E_Normal_Prot_Start, 1000);
}

void spt::ApiNormalBoolOut::SignalPowerUpIni(ApiBoardNormalStateOut& Board, const char* Name, const char* DesName, uint16 InNo)
{
	SptNormalStateOutCell::PowerUpIni(Name, DesName, (HalBoard*)&Board, E_Normal_Sinal_Do, InNo);
}

void spt::ApiNormalBoolOut::SetValue(bool8 Val)
{
	SptNormalStateOutCell::SetValue(Val == 1, 0, 0);
}

bool8 spt::ApiNormalBoolOut::Value()
{
	return value.value.u32 == 1;
}

uint32 spt::ApiNormalBoolOut::VerfyCode()
{
	return outValue;
}

const SalDateStamp& spt::ApiNormalBoolOut::Stamp()
{
	return value.stamp;
}

void spt::ApiGoOutFrame::PowerUpIni(const char* Name, const char* DesName, uint16 InNo, uint16 ElementNum)
{
	SptGooseFrameOut::PowerUpIni(Name, DesName, E_Vir_Board_FrameGoIn_1, ElementNum);
	frameIndex = InNo;
}

void spt::ApiGoPosOut::PowerUpIni(const char* Name, const char* DesName, ApiGoOutFrame& Board, uint16 OutNo)
{
	ApiGoOut::PowerUpIni(Name, DesName, (SptGooseFrameOut*)&Board, E_Go_BOOL_Out1, OutNo);
}

void spt::ApiGoPosOut::SetValue(uint32 Val)
{
	if (value.value.u32 != Val)
	{
		u32value v;
		v.u32 = Val;
		ApiGoOut::SetValue(v);
	}
}

uint32 spt::ApiGoPosOut::Value()
{
	return value.value.u32;
}

void spt::ApiGoDpPosOut::PowerUpIni(const char* Name, const char* DesName, ApiGoOutFrame& Board, uint16 OutNo)
{
	ApiGoOut::PowerUpIni(Name, DesName, (SptGooseFrameOut*)&Board, E_Go_Dp_Out1, OutNo);
}

void spt::ApiGoDpPosOut::SetValue(uint32 Val)
{
	if (value.value.u32 != Val)
	{
		u32value v;
		v.u32 = Val;
		ApiGoOut::SetValue(v);
	}
}

uint32 spt::ApiGoDpPosOut::Value()
{
	return value.value.u32;
}

void spt::ApiGoFloatOut::PowerUpIni(const char* Name, const char* DesName, ApiGoOutFrame& Board, uint16 OutNo)
{
	ApiGoOut::PowerUpIni(Name, DesName, (SptGooseFrameOut*)&Board, E_Go_Float32_Out1, OutNo);
}

void spt::ApiGoFloatOut::SetValue(float32 Val)
{
	if (value.value.f32 != Val)
	{
		u32value v;
		v.f32 = Val;
		ApiGoOut::SetValue(v);
	}
}

float32 spt::ApiGoFloatOut::Value()
{
	return value.value.f32;
}

void spt::ApiGoInt32Out::PowerUpIni(const char* Name, const char* DesName, ApiGoOutFrame& Board, uint16 OutNo)
{
	ApiGoOut::PowerUpIni(Name, DesName, (SptGooseFrameOut*)&Board, E_Go_Int32_Out1, OutNo);
}

void spt::ApiGoInt32Out::SetValue(int32 Val)
{
	if (value.value.i32 != Val)
	{
		u32value v;
		v.i32 = Val;
		ApiGoOut::SetValue(v);
	}
}

int32 spt::ApiGoInt32Out::Value()
{
	return value.value.i32;
}

void spt::ApiGoUInt32Out::PowerUpIni(const char* Name, const char* DesName, ApiGoOutFrame& Board, uint16 OutNo)
{
	ApiGoOut::PowerUpIni(Name, DesName, (SptGooseFrameOut*)&Board, E_Go_UInt32_Out1, OutNo);
}

void spt::ApiGoUInt32Out::SetValue(uint32 Val)
{
	if (value.value.u32 != Val)
	{
		u32value v;
		v.u32 = Val;
		ApiGoOut::SetValue(v);
	}
}

uint32 spt::ApiGoUInt32Out::Value()
{
	return value.value.u32;
}

GoSvDataType spt::ApiGoOut::GoValueType()
{
	return (GoSvDataType)vNode.dataType;
}

bool8 spt::ApiGoOut::IsQLinked()
{
	return qNode.isLinked;
}

bool8 spt::ApiGoOut::IsTLinked()
{
	return tNode.isLinked;
}

bool8 spt::ApiGoOut::IsVLinked()
{
	return vNode.isLinked;
}

const ApiGoOutDataSet* spt::ApiGoOut::GoCb()
{
	return (ApiGoOutDataSet*)virBoard;
}

void spt::ApiGoOut::SetQ(uint32 Q)
{
	if (blsignalForce)
	{
		return;
	}
	if (value.q != Q)
	{
		value.q = Q;
		if (virBoard)
		{
			SptGooseDataSetOut* out = (SptGooseDataSetOut*)virBoard;
			out->UpdateData(node);
		}
	}
}

void spt::ApiGoOut::SetStamp(SalDateStamp& stamp)
{
	if (blsignalForce)
	{
		return;
	}
	if (value.stamp.Us() != stamp.Us())
	{
		value.stamp = stamp;
		uint32 sec, fraq;
		value.stamp.toUtcCode(sec, fraq);
		ChangeEndian(&utcStamp.uSec, &sec, sizeof(sec));
		ChangeEndian(&utcStamp.u_Fra_Q, &fraq, sizeof(fraq));
		if (virBoard)
		{
			SptGooseDataSetOut* out = (SptGooseDataSetOut*)virBoard;
			out->UpdateData(node);
		}
	}
}

void spt::ApiGoOut::SetValue(u32value Val)
{
	if (blsignalForce)
	{
		return;
	}
	SptGooseDataOut::GoSetValue(Val.u32);
}

const SalDateStamp& spt::ApiGoOut::Stamp()
{
	return value.stamp;
}

uint32 spt::ApiGoOut::Q()
{
	return value.q;
}

void spt::ApiGoOut::PowerUpIni(const char* Name, const char* DesName, SptGooseFrameOut* Board, uint32 Type, uint16 OutNo)
{
	value.stamp.Set((int64)0);
	SptGooseData::PowerUpIni(Name, DesName, (HalBoard*)Board, Type, 0, OutNo);
}

void spt::ApiGoOutDataSet::PowerUpIni(const char* Name, const char* OutName, const char* DesName, ApiGoOutFrame& Frame, uint16 ElementNum)
{
	SptGooseDataSetOut::PowerUpIni(Name, DesName, (SptGooseFrameOut*)&Frame, E_Vir_Board_GoOut_1, ElementNum);
	frameIndex = 0;
	outerName = OutName;
}

bool8 spt::ApiGoOutDataSet::CfgErr()
{
	return gocbPub->cfgErr;
}

bool8 spt::ApiGoOutDataSet::ParseErr()
{
	return gocbPub->parseErr;
}

GooseGocbInfo* spt::ApiGoOutDataSet::GoCbInfo()
{
	return gocbPub;
}

void spt::ApiGoInFrame::PowerUpIni(const char* Name, const char* DesName, uint16 InNo, uint16 ElementNum)
{
	SptGooseFrameIn::PowerUpIni(Name, DesName, E_Vir_Board_FrameGoIn_1, ElementNum);
	frameIndex = InNo;
}

uint32 spt::ApiGoInFrame::PosFrameNum()
{
	return posFrameNum;
}

uint32 spt::ApiGoInFrame::AngFrameNum()
{
	return angFrameNum;
}

const SalDateStamp& spt::ApiGoInFrame::FrameStamp()
{
	return stamp;
}

void spt::ApiGoInCb::PowerUpIni(const char* Name, const char* DesName, ApiGoInFrame& Frame, uint16 ElementNum)
{
	SptGooseDataSetIn::PowerUpIni(Name, DesName, (SptGooseFrameIn*)&Frame, E_Vir_Board_GoIn_1, ElementNum);
	frameIndex = 0;
}

uint32 spt::ApiGoInCb::StateA()
{
	return ostatus.checkStatus1;
}

uint32 spt::ApiGoInCb::StateB()
{
	return ostatus.checkStatus2;
}

bool8 spt::ApiGoInCb::CfgErr()
{
	return gocbSub->cfgErr;
}

bool8 spt::ApiGoInCb::ParseErr()
{
	return gocbSub->parseErr;
}

GooseGocbInfo* spt::ApiGoInCb::GoCbInfo()
{
	return gocbSub;
}

bool8 spt::ApiGoIn::IsQLinked()
{
	return qNode.isLinked;
}

bool8 spt::ApiGoIn::IsTLinked()
{
	return tNode.isLinked;
}

bool8 spt::ApiGoIn::IsVLinked()
{
	return vNode.isLinked;
}

const SalDateStamp& spt::ApiGoIn::Stamp()
{
	return value.stamp;
}

uint32 spt::ApiGoIn::Q()
{
	return value.q;
}

uint32 spt::ApiGoIn::StateNum()
{
	return stateNmb;
}

const ApiGoInCb* spt::ApiGoIn::GoCb()
{
	return (ApiGoInCb*)virBoard;
}

void spt::ApiGoIn::PowerUpIni(const char* Name, const char* DesName, SptGooseFrameIn* Board, uint32 Type, uint16 InNo)
{
	value.stamp.Set((int64)0);
	SptGooseData::PowerUpIni(Name, DesName, (HalBoard*)Board, Type, 0, InNo);
}

void spt::ApiGoPosIn::PowerUpIni(const char* Name, const char* DesName, ApiGoInFrame& Frame, uint16 InNo)
{
	ApiGoIn::PowerUpIni(Name, DesName, (SptGooseFrameIn*)&Frame, E_Go_BOOL_In1, InNo);
}

bool8 spt::ApiGoPosIn::Value()
{
	return value.value.bl;
}

void spt::ApiGoDpPosIn::PowerUpIni(const char* Name, const char* DesName, ApiGoInFrame& Frame, uint16 InNo)
{
	ApiGoIn::PowerUpIni(Name, DesName, (SptGooseFrameIn*)&Frame, E_Go_Dp_In1, InNo);
}

uint32 spt::ApiGoDpPosIn::Value()
{
	return value.value.u32;
}

void spt::ApiDigFloatIn::PowerUpIni(const char* Name, const char* DesName, ApiGoInFrame& Frame, uint16 InNo)
{
	ApiGoIn::PowerUpIni(Name, DesName, (SptGooseFrameIn*)&Frame, E_Go_Float32_In1, InNo);
}

float32 spt::ApiDigFloatIn::Value()
{
	return value.value.f32;
}

void spt::ApiDigInt32In::PowerUpIni(const char* Name, const char* DesName, ApiGoInFrame& Frame, uint16 InNo)
{
	ApiGoIn::PowerUpIni(Name, DesName, (SptGooseFrameIn*)&Frame, E_Go_Int32_In1, InNo);
}

int32 spt::ApiDigInt32In::Value()
{
	return value.value.i32;
}

void spt::ApiDigUInt32In::PowerUpIni(const char* Name, const char* DesName, ApiGoInFrame& Frame, uint16 InNo)
{
	ApiGoIn::PowerUpIni(Name, DesName, (SptGooseFrameIn*)&Frame, E_Go_UInt32_In1, InNo);
}

uint32 spt::ApiDigUInt32In::Value()
{
	return value.value.u32;
}

void spt::ApiNormalDcIn::PowerUpIni(ApiBoardNormalDcIn& Board, const char* Name, const char* DesName, uint16 InNo, const VarUnits& Units)
{
	SptNormalDcIn::PowerUpIni(Name, DesName, (HalBoard*)&Board, 0, E_Normal_DC, InNo, InNo, Units);
}

int32 spt::ApiNormalDcIn::Value()
{
	return value.value.i32;
}


void spt::ApiBoardNormalDcIn::PowerUpIni(const char* Name, const char* DesName, uint16 CardType, uint16 CardAddr, uint16 FrameIndex, uint32 ElementNum)
{
	SptNormalDcInBoard::PowerUpIni(Name, DesName, CardType, CardAddr, FrameIndex, ElementNum);
}

const SalDateStamp& spt::ApiBoardNormalDcIn::Stamp()
{
	return stamp;
}

uint32 spt::ApiBoardNormalDcIn::StateNum()
{
	return stateNmb;
}

uint16 spt::ApiBoardNormalDcIn::Temperature()
{
	return temprature;
}

void spt::ApiGoUnion32Out::PowerUpIni(const char* Name, const char* DesName, ApiGoOutFrame& Board, uint16 OutNo)
{
	ApiGoOut::PowerUpIni(Name, DesName, (SptGooseFrameOut*)&Board, E_Go_Union32_Out1, OutNo);
}

void spt::ApiGoUnion32Out::SetValue(u32value Val)
{
	ApiGoOut::SetValue(Val);
}

u32value spt::ApiGoUnion32Out::Value()
{
	return value.value;
}
