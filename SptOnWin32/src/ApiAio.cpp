#include "ApiProject.h"
using namespace spt;

void spt::ApiBoardNormalAngIn::PowerUpIni(const char* Name, const char* DesName, ApiBoardAngFrameIn& Frame, uint16 CardType, uint16 CardAddr)
{
	if (CardType == E_Board_Ang24Pin_1)
	{
		//const struct ApiAppCfg* cfg = SptMain::Instance().AppCfg();
		SetCardAddr(CardAddr);
		SptNormalAngInBoard::PowerUpIni(Name, DesName, CardType, 26);
	}
	virBoard = (HalBoard*)&Frame;
}


void spt::ApiBoardAngFrameIn::PowerUpIni(const char* Name, const char* DesName, uint16 FrameNo, uint16 ElementNum, uint32 AdNum, uint8 AdNodeNum)
{
	//const struct ApiAppCfg* cfg = SptMain::Instance().AppCfg();
	SptAngVirInputBoard::PowerUpIni(Name, DesName, HalBoard::E_Vir_Board_AngIn_1, ElementNum, AdNum, AdNodeNum);
	SetCardAddr(FrameNo);
	frameIndex = FrameNo;
	virBoard = 0;
}

uint32 spt::ApiBoardAngFrameIn::StateNum()
{
	return stateNmb;
}

void spt::ApiBoardAngFrameIn::SetOutValue(uint32 Index, int32 Value)
{
	if (Index < elementNum)
	{
		ElmentInfo* para = (ElmentInfo*)realDataMap.GetElement(Index);
		para->value = Value;
	}
}

void spt::ApiBoardAngFrameIn::SetOutCoe(uint32 Index, uint32 Value)
{
	SptAngVirInputBoard::SetOutCoe(Index, Value);
}

void spt::ApiBoardAngFrameIn::SetOutCoe(uint32 ADIndex, uint32 AdNode, uint32 Value)
{
	SptAngVirInputBoard::SetOutCoe(ADIndex * 8 + AdNode, Value);
}

void spt::ApiBoardAngFrameIn::SetADAdJust(uint32 AdNo, uint32 Index, uint32 Value)
{
	SptAngVirInputBoard::SetOutADAdjust(AdNo * 2 + Index, Value);
}

void spt::ApiBoardAngFrameIn::SetOutQ(uint32 Index, uint32 Value)
{
	if (Index < elementNum)
	{
		ElmentInfo* para = (ElmentInfo*)realDataMap.GetElement(Index);
		if (para->q != Value)
		{
			para->q = Value;
			qUpdate = 1;
		}
	}
}

void spt::ApiNormalAngIn::PowerUpIni(ApiBoardNormalAngIn& Board, const char* Name, const char* DesName, uint16 Node, uint16 AdIndex, uint16 AdNode, const VarUnits& Units)
{
	HalBoard* board = (HalBoard*)&Board;
	SptNormalAngSampCell::PowerUpIni(Name, DesName, board->VirBoard(), (HalBoard*)&Board, E_Normal_Ang, Node, Node, Units);
	adIndex = AdIndex;
	adNode = AdNode;

}

int32 spt::ApiNormalAngIn::Value()
{
	return value.value.i32;
}

int32 spt::ApiNormalAngIn::Value(uint32 Index)
{
	return ringBuf->GetNewWrited(Index)->value.i32;
}
void spt::ApiNormalAngIn::SetAdCoe(uint32 Value)
{
	SptAngVirInputBoard* virb = (SptAngVirInputBoard*)virBoard;
	virb->SetOutCoe(adIndex * 8 + adNode, Value);
}
uint32 spt::ApiNormalAngIn::StateNum()
{
	return stateNmb;
}
bool8 spt::ApiNormalAngIn::SetReversal(bool8 Flag)
{
	return reverse = (Flag == 1);
}
bool8 spt::ApiNormalAngIn::SetSingleAdFlag(bool8 IsSingle)
{
	return singleAd = (IsSingle == 1);
}
void spt::ApiAngRmsGroup::PowerUpIni(const char* Name, const char* DesName, uint16 EventNum, uint32 BufLen)
{
	SalAngRmsGroup::PowerUpIni(Name, DesName, EventNum, BufLen);
}

void spt::ApiAngRmsGroup::Update(bool8 AdJustAngle)
{
	SalAngRmsGroup::Update(AdJustAngle);
}

void spt::ApiAngRms::PowerUpIni(const char* Name, const char* DesName, ApiAngRmsGroup& Group, bool8 IsBase, uint16 Data1DotNum, const VarUnits& Units1, uint16 Data2DotNum, const VarUnits& Units2, uint8 QLen)
{
	SalAngRms::PowerUpIni(Name, DesName, (SalAngRmsGroup*)&Group, IsBase, Data1DotNum, &Units1, Data2DotNum, &Units2, QLen);
	dataNum = 2;
}

void spt::ApiAngRms::PowerUpIni(const char* Name, const char* DesName, ApiAngRmsGroup& Group, uint16 Data1DotNum, const VarUnits& Units1, uint8 QLen)
{
	SalAngRms::PowerUpIni(Name, DesName, (SalAngRmsGroup*)&Group, 0, Data1DotNum, &Units1, 0, &Unit_NULL, QLen);
	dataNum = 1;
}

void spt::ApiAngRms::SetDataUnit(const VarUnits& Units1, const VarUnits& Units2)
{
	transunits1 = &Units1;
	transunits2 = &Units2;
}

void spt::ApiAngRms::SetDisp(bool8 Disp)
{
	isDisp = Disp;
}

void spt::ApiAngRms::SetDataCoe(float32 Data1Coe1, float32 Data2Coe1)
{
	data1Coe = Data1Coe1;
	data2Coe = Data2Coe1;
}

bool8 spt::ApiAngRms::PushData(int32 Data1, int32 Data2, uint32 Q)
{
	return SalAngRms::PushData(Data1, Data2, Q);
}

bool8 spt::ApiAngRms::PushVectData(int32 Real, int32 Img, uint32 Q)
{
	int32 d1 = (int32)(Sqrt((float32)(Real * Real + Img * Img)) * 0.707106f);
	int32 d2 = (int32)(ATan2(Img, Real) + 0.5) * MinUint32DecData(data2DotNum + 1);
	return PushData(d1, d2, Q);
}

bool8 spt::ApiAngRms::PushData(int32 Data1, int32 Data2)
{
	return PushData(Data1, Data2, 0);
}

bool8 spt::ApiAngRms::PushVectData(int32 Real, int32 Img)
{
	return PushVectData(Real, Img, 0);
}

void spt::ApiSvIn::PowerUpIni(ApiBoardAngFrameIn& Board, const char* Name, const char* DesName, uint16 Node, const VarUnits& Units)
{
	HalBoard* board = (HalBoard*)&Board;
	SptSampAng_9_2SampCell::PowerUpIni(Name, DesName, (HalBoard*)board, 0, E_9_2_Ang_In, Node, Node, Units);
}
bool8 spt::ApiSvIn::IsLinked()
{
	return isNodeLinkOk;
}
uint16 spt::ApiSvIn::FrameIndex()
{
	return frameIndex;
}

uint16 spt::ApiSvIn::Node()
{
	return node;
}

int32 spt::ApiSvIn::Value()
{
	return value.value.i32;
}

int32 spt::ApiSvIn::Value(uint32 Index)
{
	return ringBuf->GetNewWrited(Index)->value.i32;
}

uint32 spt::ApiSvIn::Q()
{
	return value.q;
}

uint32 spt::ApiSvIn::Q(uint32 Index)
{
	return ringBuf->GetNewWrited(Index)->q;
}

uint32 spt::ApiSvIn::StateNum()
{
	return stateNmb;
}

bool8 spt::ApiSvIn::SetReversal(bool8 Flag)
{
	return reverse = (Flag == 1);
}

ApiSvInVirBoard* spt::ApiSvIn::DataSet()
{
	if (virBoard)
	{
		return (ApiSvInVirBoard*)virBoard;
	}
	return 0;
}

void spt::ApiSvInVirBoard::PowerUpIni(const char* Name, const char* DesName, ApiBoardAngFrameIn& Frame, uint16 ElementNum)
{
	SptSvInDataSet::PowerUpIni(Name, DesName, HalBoard::E_Vir_Board_SV_DataSetIn1, ElementNum);
	frameIndex = 0;
	virBoard = (HalBoard*)&Frame;
}

bool8 spt::ApiSvInVirBoard::IsEnable()
{
	return isLinked;
}

bool8 spt::ApiSvInVirBoard::CfgErr()
{
	return svcbSub->cfgErr;
}

bool8 spt::ApiSvInVirBoard::ParseErr()
{
	return svcbSub->parseErr;
}

SVcbInfo* spt::ApiSvInVirBoard::SvCbInfo()
{
	return svcbSub;
}

uint16 spt::ApiSvOut::Node()
{
	return node;
}

void spt::ApiSvOut::PowerUpIni(ApiBoardAngFrameOut& Board, const char* Name, const char* DesName, const VarUnits& Units)
{
	SptSampAng_9_2SampCell::PowerUpIni(Name, DesName, (HalBoard*)&Board, 0, E_9_2_Ang_Out, 0, 0, Units);
	frameIndex = instId;
}

bool8 spt::ApiSvOut::IsNodeLinkOk()
{
	return isNodeLinkOk;
}


void spt::ApiSvOutVirDataSet::PowerUpIni(const char* Name, const char* OutName, const char* DesName, ApiBoardAngFrameOut& Frame, uint32 Delay, uint16 FrameIndex, uint16 ElementNum)
{
	SptSvOutDataSet::PowerUpIni(Name, DesName, Delay, HalBoard::E_Vir_Board_SV_DataSetOut1, ElementNum);
	delayUs = Delay;
	frameIndex = FrameIndex;
	virBoard = (HalBoard*)&Frame;
	outerName = OutName;
}

uint32 spt::ApiSvOutVirDataSet::DataSetCellNum()
{
	return dataSetCellOutNum;
}

void spt::ApiSvOutVirDataSet::SetOutSelIndex(uint32 Index, uint32 SelIndex)
{
	SptSvOutDataSet::SetSelIndex(Index, SelIndex);
}

uint32 spt::ApiSvOutVirDataSet::GetOutSelIndex(uint32 Index)
{
	return SptSvOutDataSet::GetOutSelIndex(Index);
}

bool8 spt::ApiSvOutVirDataSet::CfgErr()
{
	return svcbPub->cfgErr;
}

bool8 spt::ApiSvOutVirDataSet::ParseErr()
{
	return svcbPub->parseErr;
}

SVcbInfo* spt::ApiSvOutVirDataSet::SvCbInfo()
{
	return svcbPub;
}

void spt::ApiSvOutVirDataSet::SetDealy(uint16 DealyUs)
{
	SptSvOutDataSet::SetDelay(DealyUs);
}

void spt::ApiIoGlobalFlag::ResetSubBoardState()
{
	sptIoProcess.ResetSubBoardState();
}

void spt::ApiIoGlobalFlag::EnableSVSend(bool8 Enable)
{
	sptIoProcess.EnableSVSend(Enable);
}

void spt::ApiIoGlobalFlag::EnableAngErrPointDeal(bool8 Enable)
{
	sptIoProcess.EnableAngErrPointDeal(Enable);
}

void spt::ApiIoGlobalFlag::EnableGoSend(bool8 Enable)
{
	sptIoProcess.EnableGoSend(Enable);
}

bool8 spt::ApiIoGlobalFlag::SetCkRemoteState(bool8 Flag)
{
	return appFlags->ckRemoteState = Flag;
}

bool8 spt::ApiIoGlobalFlag::SetProtRemoteState(bool8 Flag)
{
	return appFlags->protRemoteState = Flag;
}

bool8 spt::ApiIoGlobalFlag::SetUnitTestState(bool8 Flag)
{
	return appFlags->unitTestState = Flag;
}

bool8 spt::ApiIoGlobalFlag::SetUnitDebugState(bool8 Flag)
{
	return appFlags->unitDebugState = Flag;
}

bool8 spt::ApiIoGlobalFlag::SetAppPowerUpIniOver(bool8 Flag)
{
	return appFlags->blAppPowerUpIniOver = Flag;
}

bool8 spt::ApiIoGlobalFlag::SetUnitRevert(bool8 Flag)
{
	return appFlags->blUnitRevert = Flag;
}

uint8 spt::ApiIoGlobalFlag::GetFpagSlowFlags(uint16 Index)
{
	return sptIoProcess.GetFpagSlowFlags(Index);
}

uint32 spt::ApiIoGlobalFlag::BoardOnLineState()
{
	return sptIoProcess.BoardOnLineState();
}

const SptFlags& spt::ApiIoGlobalFlag::SptFlag()
{
	return sptIoProcess.SptFlag();
}

ApiIoGlobalFlag& spt::ApiIoGlobalFlag::Instance()
{
	static ApiIoGlobalFlag inst;
	return inst;
}

spt::ApiIoGlobalFlag::ApiIoGlobalFlag()
	:sptIoProcess(SptIoProcess::Instance())
{
	appFlags = &sptIoProcess.AppFlags();
}

void spt::ApiBoardAngFrameOut::PowerUpIni(const char* Name, const char* DesName, uint16 FrameNo, uint16 ElementNum)
{
	SptAngVirOutputBoard::PowerUpIni(Name, DesName, E_Vir_Board_AngOut_1, ElementNum);
	SetCardAddr(FrameNo);
	frameIndex = FrameNo;
	virBoard = 0;
}

void spt::ApiBoardCmmSv::PowerUpIni(ApiBoardCmmSvOutVirDataSet& Board, const char* Name, const char* DesName, const VarUnits& Units)
{
	SptSampAng_9_2SampCell::PowerUpIni(Name, DesName, (HalBoard*)&Board, 0, E_Local_9_2_Ang_Out, 0, 0, Units);
}


void spt::ApiBoardCmmSvOutVirDataSet::PowerUpIni(const char* Name, const char* OutName, const char* DesName, ApiBoardAngFrameOut& Frame, uint16 FrameIndex, uint16 ElementNum)
{
	SptSvOutDataSet::PowerUpIni(Name, DesName, 0, HalBoard::E_Vir_BoardCMM_SV_DataSetOut1, ElementNum);
	frameIndex = FrameIndex;
	virBoard = (HalBoard*)&Frame;
	outerName = OutName;
	isEnable = 1;
	dataSetCellOutNum = ElementNum;
}

uint32 spt::ApiBoardCmmSvOutVirDataSet::DataSetCellNum()
{
	return instNum;
}

void spt::ApiBoardCmmSvOutVirDataSet::SetOutSelIndex(uint32 Index, uint32 SelIndex)
{
	SptSvOutDataSet::SetSelIndex(Index, SelIndex);
}

void spt::ApiBoardCmmSvIn::PowerUpIni(ApiBoardAngFrameIn& Board, const char* Name, const char* DesName, uint16 Node, const VarUnits& Units)
{
	HalBoard* board = (HalBoard*)&Board;
	SptSampAng_9_2SampCell::PowerUpIni(Name, DesName, (HalBoard*)board, 0, E_Local_9_2_Ang_In, Node, Node, Units);
	adIndex = 0;
	adNode = Node;
	SetNodeLinkFlag(1, adIndex, adNode);
}

int32 spt::ApiBoardCmmSvIn::Value()
{
	return value.value.i32;
}

int32 spt::ApiBoardCmmSvIn::Value(uint32 Index)
{
	return ringBuf->GetNewWrited(Index)->value.i32;
}

uint32 spt::ApiBoardCmmSvIn::Q()
{
	return value.q;
}

uint32 spt::ApiBoardCmmSvIn::Q(uint32 Index)
{
	return ringBuf->GetNewWrited(Index)->q;
}

uint32 spt::ApiBoardCmmSvIn::StateNum()
{
	return stateNmb;
}

bool8 spt::ApiBoardCmmSvIn::SetReversal(bool8 Flag)
{
	return reverse = (Flag == 1);
}

void spt::ApiBoardCmmSvIn::SetNodeLinkFlag(bool8 Flag, uint16 SvCbIndex, uint16 Node)
{
	SptSampAng_9_2SampCell::SetNodeLinkFlag(Flag, SvCbIndex, Node);
}
