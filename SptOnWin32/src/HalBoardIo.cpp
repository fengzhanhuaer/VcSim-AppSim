#include "SptProject.h"
using namespace spt;

void spt::HalBoard::PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum)
{
	ioType = IoType;
	virBoard = 0;
	InstObjectGroup::PowerUpIni(Name, DesName, EIOT_HalIo, ElementNum);
	ostatus.runInfo.ClearLoadInfo();
	ostatus.runInfo.SetName(DesName);
	//ostatus.runInfo.Rgs2TaskMonitorRunInfo();
}

HalIoCell* spt::HalBoard::GetIoCell(uint32 Index)
{
	if (Index >= InstNum())
	{
		return  0;
	}
	InstObject* obj = GetObject(Index);
	if (obj)
	{
		return (HalIoCell*)obj;
	}
	return 0;
}

uint32 spt::HalBoard::StateNumb()
{
	return stateNmb;
}

uint32 spt::HalBoard::SequenceNumb()
{
	return sequenceNmb;
}

const SalDateStamp& spt::HalBoard::Stamp()
{
	return stamp;
}

uint32 spt::HalBoard::CardAddr()
{
	return cardAddr;
}

uint32 spt::HalBoard::SetCardAddr(uint32 CardAddr)
{
	return cardAddr = CardAddr;
}

uint32 spt::HalBoard::IoType()
{
	return ioType;
}
bool8 spt::HalBoard::IsIoType(int32 IoType)
{
	return ioType == (uint32)IoType;
}
int32 spt::HalBoard::ProcIni()
{
	return -1;
}
int32 spt::HalBoard::ProcIn()
{
	return -1;
}

int32 spt::HalBoard::ProcOut()
{
	return -1;
}

uint32 spt::HalBoard::FrameIndex()
{
	return frameIndex;
}

HalBoard* spt::HalBoard::VirBoard()
{
	return virBoard;
}

void spt::HalBoard::SetVirBoard(HalBoard* VirBoard)
{
	virBoard = VirBoard;
}
uint32 spt::HalBoard::CmmType()
{
	return cmmType;
}

bool8 spt::HalBoard::IsCmmType(int32 IoType)
{
	return cmmType == (uint32)IoType;
}

uint32 spt::HalBoard::SetFrameIndex(uint32 FrameIndex)
{
	return frameIndex = FrameIndex;
}

void spt::HalIoCell::PowerUpIni(const char* Name, const char* DesName, HalBoard* Group, HalBoard* VirBoard, uint32 IoType, uint32 Node)
{
	ioType = IoType;
	node = Node;
	virBoard = VirBoard;
	if (VirBoard)
	{
		InstObject::PowerUpIni(Name, DesName, Group, virBoard, EIOT_HalIo, Group->InstId(), Group->InstNum());
	}
	else
	{
		InstObject::PowerUpIni(Name, DesName, Group, 0, EIOT_HalIo, Group->InstId(), Group->InstNum());
	}
}

uint32 spt::HalIoCell::StateNumb()
{
	return stateNmb;
}

uint32 spt::HalIoCell::SequenceNumb()
{
	return sequenceNmb;
}
uint32 spt::HalIoCell::Node()
{
	return node;
}

HalBoard* spt::HalIoCell::VirBoard()
{
	return virBoard;
}

uint32 spt::HalIoCell::FrameIndex()
{
	return frameIndex;
}

uint32 spt::HalIoCell::IoType()
{
	return ioType;
}

void spt::HalIoCell::SetVirBoard(HalBoard* VirBoard)
{
	virBoard = VirBoard;
}

uint32 spt::HalIoCell::SetFrameIndex(uint32 FrameIndex)
{
	return frameIndex;
}
