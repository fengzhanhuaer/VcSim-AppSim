#include "ApiProject.h"
using namespace spt;

void spt::ApiSmartBoardInfo::PowerUpIni(const char* Name, const char* DesName, uint32 CardNo, uint32 NetNum)
{
	SptGoSvStateBoard::PowerUpIni(Name, DesName, E_Board_GoSv_1, CardNo, NetNum);
}

uint32 spt::ApiSmartBoardInfo::StateNum()
{
	return stateNmb;
}

const SptGoSvStateBoard::NetState* spt::ApiSmartBoardInfo::NetState(uint16 Index)
{
	return &netState[Index];
}

uint16 spt::ApiSmartBoardInfo::RunState(uint32 Index)
{
	return progRunState;
}

uint32 spt::ApiSmartBoardInfo::SvRecCfgRecState(uint32 FPGAIndex)
{
	return svRecCfgState;
}

uint32 spt::ApiSmartBoardInfo::SvSendCfgRecState(uint32 FPGAIndex)
{
	return svSendCfgState;
}

uint32 spt::ApiSmartBoardInfo::GoRecParaCfgRecState(uint32 FPGAIndex, uint32 StateIndex)
{
	return goRecCfgState[StateIndex];
}

uint32 spt::ApiSmartBoardInfo::GoRecTypeCfgRecState(uint32 FPGAIndex, uint32 StateIndex)
{
	return goRecTypeCfgState[StateIndex];
}

uint32 spt::ApiSmartBoardInfo::GoRecMapCfgRecState(uint32 FPGAIndex, uint32 StateIndex)
{
	return goRecMapCfgState[StateIndex];
}

uint32 spt::ApiSmartBoardInfo::FpgaClkPps()
{
	return clkCntPps;
}

uint32 spt::ApiSmartBoardInfo::CfgRecState()
{
	return cfgState;
}
