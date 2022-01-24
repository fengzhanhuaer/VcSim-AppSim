#include "ApiProject.h"
using namespace spt;
#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;
static int32 RecNorBoardSlowMsg(uint8* Frame, HalBoard::stOutStatus& ostatus)
{
	if (Frame[0] == SptIedIoProcess::E_UP_VERSION)
	{
		ostatus.Version1.ProgVersion = Frame[1] | ((uint16)Frame[2] << 8);
		return 0;
	}
	if (Frame[0] == SptIedIoProcess::E_UP_DATE1)
	{
		ostatus.Version1.ProgDate = (ostatus.Version1.ProgDate & 0xFFFF0000) | (Frame[1] | ((uint16)Frame[2] << 8));
		return 0;
	}
	if (Frame[0] == SptIedIoProcess::E_UP_DATE2)
	{
		ostatus.Version1.ProgDate = (ostatus.Version1.ProgDate & 0x0000FFFF) | ((uint32)Frame[1] << 16) | ((uint32)Frame[2] << 24);
		return 0;
	}
	if (Frame[0] == SptIedIoProcess::E_UP_CRC16)
	{
		ostatus.Version1.RtCrc = Frame[1] | ((uint16)Frame[2] << 8);
		return 0;
	}
	if (Frame[0] == SptIedIoProcess::E_UP_CheckStatus_1)
	{
		ostatus.checkStatus1 = Frame[1] | ((uint16)Frame[2] << 8);
		return 0;
	}
	return 0;
}
void spt::SptNormalDcInBoard::PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 CardAddr, uint16 FrameIndex, uint32 ElementNum)
{
	HalBoard::PowerUpIni(Name, DesName, IoType, ElementNum);
	SetCardAddr(CardAddr);
	frameIndex = FrameIndex;
	cmmType = E_Board_Dc_1;
}
void spt::SptNormalDcInBoard::RecvMsg(SalDateStamp& Utc, uint8* Frame)
{
	if (Frame[0] != 0x5d)
	{
		ostatus.recvFrameErrCnt++;
		return;
	}
	{
		RecNorBoardSlowMsg(&Frame[4], ostatus);
	}
	uint8 Len = Frame[1];
	stateNmb++;
	uint16 dc[10] = { 0 };
	temprature = GetLittleEndian16Bit(&Frame[7]);
	uint32 endloop = 0;
	if (Len == 25)
	{
		endloop = 8;
	}
	MemCpy(dc, &Frame[9], endloop * 2);
	for (uint32 i = 0; i < instNum; i++)
	{
		SptNormalDcIn* dccell = (SptNormalDcIn*)GetObject(i);
		dccell->SetValue(dc[dccell->Node()]);
	}
	stamp = Utc;
	ostatus.recvFrameOkCnt++;
}


void spt::SptNormalDcIn::PowerUpIni(const char* Name, const char* DesName, HalBoard* Group, HalBoard* VirGroup, uint32 IoType, uint32 Node, uint32 FrameNo, const VarUnits& Units)
{
	units = &Units;
	frameIndex = FrameNo;
	SptIoCell::PowerUpIni(Name, DesName, Group, VirGroup, IoType, Node);
}

void spt::SptNormalDcIn::SetValue(int32 Value)
{
	if (blsignalForce)
	{
		return;
	}
	value.value.i32 = Value;
}

void spt::SptNormalDcIn::ForceSetValue(int32 Value)
{
	if (!blsignalForce)
	{
		return;
	}
	value.value.i32 = Value;
}
void spt::SptStateBoard::PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum)
{
	ElementBuf.Alloc(sizeof(void*), ElementNum);
	ioType = IoType;
	HalBoard::PowerUpIni(Name, DesName, IoType, ElementNum);
	ringBuf = ringBuf->Alloc();
	if (!ringBuf)
	{
		LogErr.Stamp() << "SptStateBoard ringBuf Alloc Err\n";
	}
}

void spt::SptNormalStateInBoard::PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum)
{
	SptStateBoard::PowerUpIni(Name, DesName, IoType, ElementNum);
	if (IoType == E_Board_DIO_YX14_1)
	{
		cmmType = E_Board_DIO_1;
	}
	else if (IoType == E_Board_YX32Pin_1)
	{
		cmmType = E_Board_YX_1;
	}
	else if (IoType == E_Board_OPB_YX_1)
	{
		cmmType = E_Board_OPB_YX_1;
	}
}

void spt::SptNormalStateInBoard::RecvMsg(SalDateStamp& Utc, GzkBoardCmmIoNorDIFrame* Frame)
{
	uint8* fr = (uint8*)Frame;
	if (fr[0] != 0x5d)
	{
		ostatus.recvFrameErrCnt++;
		return;
	}
	RecNorBoardSlowMsg(&Frame->frm_status_type, ostatus);
	uint32 Value;
	MemCpy(&Value, &Frame->DigitalInput1, sizeof(uint32));
	sequenceNmb++;
	ostatus.recvFrameOkCnt++;
	if (Value == rtValue[0])
	{
		return;
	}
	stateNmb++;
	sequenceNmb = 0;
	StateBoardValueCell* frame = ringBuf->GetNextWriteBuf();
#ifdef WIN32_SIM
	uint64 time = Utc.Us();
	frame->stamp.Set(time);
#else
	frame->stamp = Utc;
#endif
	rtValue[0] = Value;
	stamp = frame->stamp;
	ringBuf->WriterAdd(1);
	SptNormalStateInCell* cell;
	for (uint32 i = 0; i < instNum; i++)
	{
		cell = (SptNormalStateInCell*)GetObject(i);
		cell->SetValue(GetBit(Value, cell->Node()), 0, &stamp);
	}
	if (0)
	{
		String100B str;
		str << "SptNormalStateInBoard " << name << " ";
		(str.FormatDate(stamp.Us()) << " ").FormatHex(Value) << "\n";
		LogAct.Stamp() << str;
	}
}

int32 spt::SptNormalStateInBoard::ProcIn()
{
	return 0;
}

uint32 spt::SptNormalStateInBoard::GetValue(uint32 Index)
{
	return rtValue[0];
}

void spt::SptNormalStateOutBoard::PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum)
{
	SptStateBoard::PowerUpIni(Name, DesName, IoType, ElementNum);
	if (IoType == E_Board_DIO_DO7_1)
	{
		cmmType = E_Board_DIO_1;
	}
	else
	{
		cmmType = E_Board_Do_1;
	}
}
int32 spt::SptNormalStateOutBoard::ProcOut()
{
	if (rtDoValueUpdate > 0)
	{
		rtDoValueUpdate--;
		if (rtDoValueUpdate == 0)
		{
			stateNmb++;
			sequenceNmb = 0;
		}
		rtValue[0] = 0;
		for (size_t i = 0; i < (sizeof(rtValue[0]) * 8); i++)
		{
			rtValue[0] |= ((uint32)rtDoValue[i]) << i;
		}
	}
	else
	{
		sequenceNmb++;
	}
	return 0;
}

uint32 spt::SptNormalStateOutBoard::FrameIndex()
{
	return frameIndex;
}

void spt::SptNormalStateOutBoard::RecvMsg(SalDateStamp& Utc, uint8* Frame)
{
	if (Frame[0] != 0x5d)
	{
		ostatus.recvFrameErrCnt++;
		return;
	}
	RecNorBoardSlowMsg(&Frame[4], ostatus);
	//uint8 Len = Frame[1];
	stateStamp = Utc;
	uint16 state = GetLittleEndian16Bit(&Frame[7]);
	if (state != rtOutState[0])
	{
		rtOutState[0] = state;
		rtOutStateNum++;
		SptNormalStateOutCell* cell;
		for (uint32 i = 0; i < instNum; i++)
		{
			cell = (SptNormalStateOutCell*)GetObject(i);
			cell->SetOutState(GetBit(state, cell->Node()));
		}
	}
	ostatus.recvFrameOkCnt++;
}

void spt::SptNormalStateOutBoard::RecvMsg(SalDateStamp& Utc, GzkBoardCmmIoNorDIFrame* Frame)
{
	uint8* frame = (uint8*)Frame;
	if (frame[0] != 0x5d)
	{
		ostatus.recvFrameErrCnt++;
		return;
	}
	RecNorBoardSlowMsg(&Frame->frm_status_type, ostatus);
	if (Frame->frm_status_type != SptIedIoProcess::E_UP_DIO_Status_1)
	{
		return;
	}
	//uint8 Len = Frame[1];
	stateStamp = Utc;
	uint16 state = GetLittleEndian16Bit(&Frame->frm_status1);
	if (state != rtOutState[0])
	{
		rtOutState[0] = state;
		rtOutStateNum++;
		SptNormalStateOutCell* cell = 0;
		for (uint32 i = 0; i < instNum; i++)
		{
			cell = (SptNormalStateOutCell*)GetObject(i);
			cell->SetOutState(GetBit(state, cell->Node()));
		}
	}
	ostatus.recvFrameOkCnt++;
}

void spt::SptNormalStateOutBoard::SetOutValue(uint32 Index, uint32 Value)
{
	stamp.Now();
	rtDoValue[Index] = (Value == 1);
	rtDoValueUpdate++;
}

void spt::SptNormalStateOutBoard::SetStartValue(uint32 Value)
{
	rtStart = Value;
}

uint32 spt::SptNormalStateOutBoard::GetValue(uint32 Index)
{
	return rtValue[Index];
}

uint32 spt::SptNormalStateOutBoard::RtStartValue()
{
	return rtStart;
}

void spt::SptStateCell::PowerUpIni(const char* Name, const char* DesName, HalBoard* Group, HalBoard* VirGroup, uint32 IoType, uint32 Node)
{
	SptIoCell::PowerUpIni(Name, DesName, Group, VirGroup, IoType, Node);
	ringBuf = ringBuf->Alloc();
	if (!ringBuf)
	{
		LogErr.Stamp() << "SptStateCell ringBuf Alloc Err\n";
	}
}

void spt::SptStateCell::PowerUpIni(const char* Name, const char* DesName, HalBoard* Group, uint32 IoType, uint32 Node)
{
	SptIoCell::PowerUpIni(Name, DesName, Group, 0, IoType, Node);
	ringBuf = ringBuf->Alloc();
	if (!ringBuf)
	{
		LogErr.Stamp() << "SptStateCell ringBuf Alloc Err\n";
	}
}

void spt::SptStateCell::SetValue(uint32 Value, uint32* Q, SalDateStamp* stamp)
{
	if (blsignalForce)
	{
		return;
	}
	if ((Value != value.value.u32) || (Q && (value.q != *Q)))
	{
		value.value.u32 = Value;

		if (stamp)
		{
			value.stamp = *stamp;
		}
		else
		{
			SalDateStamp stamp;
			stamp.Now();
			value.stamp = stamp;
		}
		if (Q)
		{
			value.q = *Q;
		}
		ringBuf->Push(&value);
		stateNmb++;
		sequenceNmb = 0;
	}
	else
	{
		sequenceNmb++;
	}
}

void spt::SptStateCell::ForceSetValue(uint32 Value, uint32* Q, SalDateStamp* stamp)
{
	if (!blsignalForce)
	{
		return;
	}
	if ((Value != value.value.u32) || (Q && (value.q != *Q)))
	{
		value.value.u32 = Value;
		if (stamp)
		{
			value.stamp = *stamp;
		}
		else
		{
			SalDateStamp stamp;
			stamp.Now();
			value.stamp = stamp;
		}
		if (Q)
		{
			value.q = *Q;
		}
		if (0)
		{
			String100B str;
			str << "ForceSetValue " << name << " ";
			str.FormatDate(value.stamp.Us()) << " " << Value << "\n";
			LogAct.Stamp() << str;
		}
		ringBuf->Push(&value);
		stateNmb++;
		sequenceNmb = 0;
	}
	else
	{
		sequenceNmb++;
	}
}

const StateValueCell& spt::SptStateCell::Value()
{
	return value;
}

void spt::SptStateCell::SaveIds(void* Ele)
{
	XMLElement* ele = (XMLElement*)Ele;
	ele->SetAttribute("InstId", instId);
	ele->SetAttribute("GroupId", groupId);
	ele->SetAttribute("Name", name);
	ele->SetAttribute("DesName", desName);
	ele->SetAttribute("Node", node);
	String100B info;
	info = group->DesName();
	info << "." << desName;
	ele->SetAttribute("sAddr1", info.Str());
	ele->SetAttribute("FrameIndex", frameIndex);
	if (virBoard)
	{
		String100B info;
		info = virBoard->DesName();
		info << "." << desName;
		ele->SetAttribute("sAddr2", info.Str());
	}
}

void spt::SptNormalStateInCell::SetValue(uint32 Value, uint32* Q, SalDateStamp* stamp)
{
	if (blsignalForce)
	{
		return;
	}
	if (value.value.u32 != Value)
	{
		value.value.u32 = Value;
		if (stamp)
		{
			value.stamp = *stamp;
		}
		else
		{
			SalDateStamp stamp;
			stamp.Now();
			value.stamp = stamp;
		}
		if (0)
		{
			String100B str;
			str << "SptNormalStateInCell SetValue" << name << " ";
			str.FormatDate(value.stamp.Us()) << " " << Value << "\n";
			LogAct.Stamp() << str;
		}
		ringBuf->Push(&value);
		stateNmb++;
		sequenceNmb = 0;
	}
	else
	{
		sequenceNmb++;
	}
}

void spt::SptNormalStateOutCell::SetValue(uint32 Value, uint32* Q, SalDateStamp* stamp)
{
	if (blsignalForce)
	{
		return;
	}
	if (Value != value.value.u32)
	{
		value.value.u32 = (Value == 1);
		value.stamp.Now();
		if (0)
		{
			String100B str;
			str << "StateOut " << name << " ";
			str.FormatDate(value.stamp.Us()) << " " << Value << "\n";
			LogAct.Stamp() << str;
		}
		SptNormalStateOutBoard* b = (SptNormalStateOutBoard*)group;
		b->SetOutValue(node, value.value.u32);
		stateNmb++;
		sequenceNmb = 0;
	}
	else
	{
		sequenceNmb++;
	}
}

void spt::SptNormalStateOutCell::ForceSetValue(uint32 Value, uint32* Q, SalDateStamp* stamp)
{
	if (!blsignalForce)
	{
		return;
	}
	if (Value != value.value.u32)
	{
		value.value.u32 = (Value == 1);
		{
			SalDateStamp stamp;
			stamp.Now();
			value.stamp = stamp;
		}
		if (1)
		{
			String100B str;
			str << "ForceSetValue " << name << " ";
			str.FormatDate(value.stamp.Us()) << " " << Value << "\n";
			LogAct.Stamp() << str;
		}
		SptNormalStateOutBoard* b = (SptNormalStateOutBoard*)group;
		b->SetOutValue(node, value.value.u32);
		stateNmb++;
		sequenceNmb = 0;
	}
	else
	{
		sequenceNmb++;
	}
}

void spt::SptNormalStateOutCell::SetOutState(uint32 Value)
{
	outValue = (Value == 1);
}


void spt::SptGooseFrameIn::PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum)
{
	ElementBuf.Alloc(sizeof(void*), ElementNum);
	ioType = IoType;
	InstObjectGroup::PowerUpIni(Name, DesName, EIOT_HalIo, ElementNum);
	HalBoard::PowerUpIni(Name, DesName, IoType, ElementNum);
	virBoard = 0;
	PosElementBuf.Alloc(sizeof(void*), ElementNum);
	U32ElementBuf.Alloc(sizeof(void*), ElementNum);
	ProcInBuf.Alloc(sizeof(void*), ElementNum);
}

int32 spt::SptGooseFrameIn::ProcIni()
{
	HalIoCell* inst;
	PosElementBuf.Clear();
	U32ElementBuf.Clear();
	for (uint32 i = 0; i < instNum; i++)
	{
		inst = GetIoCell(i);
		if (inst)
		{
			SptGooseData* gcell;
			gcell = (SptGooseData*)inst;
			if (gcell->QNode().isLinked || gcell->TNode().isLinked || gcell->VNode().isLinked)
			{
				if (gcell->IsPos())
				{
					PosElementBuf.Push(&gcell);
				}
				else
				{
					U32ElementBuf.Push(&gcell);
				}
			}
		}
	}
	static uint16 num = 0;
	{
		CpuFpgaCmmMsgBuf msg;

		msg.Write(&num, sizeof(num));
		num++;
		uint16 u16temp;
		u16temp = 0xff11;
		msg.Write(&u16temp, sizeof(u16temp));
		u16temp = (uint16)PosElementBuf.Top();
		msg.Write(&u16temp, sizeof(u16temp));

		uint16 endloop = (uint16)PosElementBuf.Top();
		SptGooseData* gcell;
		for (uint32 i = 0; i < endloop; i++)
		{
			gcell = (SptGooseData*)PosElementBuf.GetAddrElement(i);
			if (gcell->VNode().isLinked)
			{
				if (gcell->IoType() == gcell->E_Go_BOOL_In1)
				{
					u16temp = 0;
				}
				else
				{
					u16temp = 0x4000;
				}
				u16temp |= (gcell->GocbInfo()->fpgaCmmIndex & 0x3f) << 8;
				u16temp |= gcell->VNode().dataSetIndex & 0x007f;
			}
			else
			{
				u16temp = 0xffff;
			}
			msg.Write(&u16temp, sizeof(u16temp));
		}
		endloop = (uint16)U32ElementBuf.Top();
		if (endloop)
		{
			u16temp = 0xff44;
			msg.Write(&u16temp, sizeof(u16temp));
			u16temp = (uint16)U32ElementBuf.Top();
			msg.Write(&u16temp, sizeof(u16temp));
			for (uint32 i = 0; i < endloop; i++)
			{
				gcell = (SptGooseData*)U32ElementBuf.GetAddrElement(i);
				if (gcell->VNode().isLinked)
				{
					u16temp = 0x8000;
					u16temp |= (gcell->GocbInfo()->fpgaCmmIndex & 0x3f) << 8;
					u16temp |= gcell->VNode().dataSetIndex & 0x007f;
				}
				else
				{
					u16temp = 0xffff;
				}
				msg.Write(&u16temp, sizeof(u16temp));
			}
		}
		u16temp = 0xAAAA;
		msg.Write(&u16temp, sizeof(u16temp));
		msg.SlowSend(0, FpgaMsgProc::E_CPU_FPGA_GOSELECT1);
		MsSleep(1);
		LogMsg.Stamp() << "FpgaMsgProc::E_CPU_FPGA_GOSELECT1 download.\n";
	}
	{
		CpuFpgaCmmMsgBuf msg;

		msg.Write(&num, sizeof(num));
		num++;
		uint16 u16temp;
		u16temp = 0xff11;
		msg.Write(&u16temp, sizeof(u16temp));
		u16temp = (uint16)PosElementBuf.Top();
		msg.Write(&u16temp, sizeof(u16temp));

		uint16 endloop = (uint16)PosElementBuf.Top();
		SptGooseData* gcell;
		for (uint32 i = 0; i < endloop; i++)
		{
			gcell = (SptGooseData*)PosElementBuf.GetAddrElement(i);
			if (gcell->QNode().isLinked)
			{
				u16temp = 0;
				u16temp |= (gcell->GocbInfo()->fpgaCmmIndex & 0x3f) << 8;
				u16temp |= gcell->QNode().dataSetIndex & 0x007f;
			}
			else
			{
				u16temp = 0xffff;
			}
			msg.Write(&u16temp, sizeof(u16temp));
		}
		endloop = (uint16)U32ElementBuf.Top();
		if (endloop)
		{

			u16temp = 0xff44;
			msg.Write(&u16temp, sizeof(u16temp));
			u16temp = (uint16)U32ElementBuf.Top();
			msg.Write(&u16temp, sizeof(u16temp));
			endloop = (uint16)U32ElementBuf.Top();
			for (uint32 i = 0; i < endloop; i++)
			{
				gcell = (SptGooseData*)U32ElementBuf.GetAddrElement(i);
				if (gcell->QNode().isLinked)
				{
					u16temp = 0x0000;
					u16temp |= (gcell->GocbInfo()->fpgaCmmIndex & 0x3f) << 8;
					u16temp |= gcell->QNode().dataSetIndex & 0x007f;
				}
				else
				{
					u16temp = 0xffff;
				}
				msg.Write(&u16temp, sizeof(u16temp));
			}
		}
		u16temp = 0xAAAA;
		msg.Write(&u16temp, sizeof(u16temp));
		msg.SlowSend(0, FpgaMsgProc::E_CPU_FPGA_GOSELECT2);
		MsSleep(1);
		LogMsg.Stamp() << "FpgaMsgProc::E_CPU_FPGA_GOSELECT2 download.\n";
	}
	{
		CpuFpgaCmmMsgBuf msg;

		msg.Write(&num, sizeof(num));
		num++;
		uint16 u16temp;
		u16temp = 0xff11;
		msg.Write(&u16temp, sizeof(u16temp));
		u16temp = (uint16)PosElementBuf.Top();
		msg.Write(&u16temp, sizeof(u16temp));

		uint16 endloop = (uint16)PosElementBuf.Top();
		SptGooseData* gcell;
		for (uint32 i = 0; i < endloop; i++)
		{
			gcell = (SptGooseData*)PosElementBuf.GetAddrElement(i);
			if (gcell->TNode().isLinked)
			{
				u16temp = 0x8000;
				u16temp |= (gcell->GocbInfo()->fpgaCmmIndex & 0x3f) << 8;
				u16temp |= gcell->TNode().dataSetIndex & 0x007f;
			}
			else
			{
				u16temp = 0x4000;
				u16temp |= (gcell->GocbInfo()->fpgaCmmIndex & 0x3f) << 8;
			}
			msg.Write(&u16temp, sizeof(u16temp));
		}
		endloop = (uint16)U32ElementBuf.Top();
		if (endloop)
		{
			u16temp = 0xff44;
			msg.Write(&u16temp, sizeof(u16temp));
			u16temp = (uint16)U32ElementBuf.Top();
			msg.Write(&u16temp, sizeof(u16temp));
			endloop = (uint16)U32ElementBuf.Top();
			for (uint32 i = 0; i < endloop; i++)
			{
				gcell = (SptGooseData*)U32ElementBuf.GetAddrElement(i);
				if (gcell->TNode().isLinked)
				{
					u16temp = 0x0000;
					u16temp |= (gcell->GocbInfo()->fpgaCmmIndex & 0x3f) << 8;
					u16temp |= gcell->TNode().dataSetIndex & 0x007f;
				}
				else
				{
					u16temp = 0x4000;
					u16temp |= (gcell->GocbInfo()->fpgaCmmIndex & 0x3f) << 8;
				}
				msg.Write(&u16temp, sizeof(u16temp));
			}
		}
		u16temp = 0xAAAA;
		msg.Write(&u16temp, sizeof(u16temp));
		msg.SlowSend(0, FpgaMsgProc::E_CPU_FPGA_GOSELECT3);
		MsSleep(1);
		LogMsg.Stamp() << " FpgaMsgProc::E_CPU_FPGA_GOSELECT3  download.\n";
	}
	MsSleep(1);
	return 0;
}

void spt::SptGooseFrameIn::RgsProcIn(SptGooseDataSetIn* Board)
{
	if (ProcInBuf.Top() < ProcInBuf.ElementNum())
	{
		ProcInBuf.Push(&Board);
	}
	else
	{
		LogErr.Stamp() << "SptGooseFrameIn Buf is full.\n";
	}
}

void spt::SptGooseFrameIn::RecGoInCbCheckStateMsg(void* Buf, uint32 BufLen)
{
	ostatus.recvFrameOkCnt++;
	uint32 reader = 0;
	uint8* b = (uint8*)Buf;
	uint16 frameno = GetLittleEndian16Bit(b + reader);
	reader += sizeof(frameno);
	uint16 cellNum = GetLittleEndian16Bit(b + reader);
	reader += sizeof(cellNum);
	SptGooseDataSetIn* Board;
	uint8* bb = (uint8*)b + sizeof(uint32) * cellNum;
	if (ProcInBuf.Top() >= cellNum)
	{
		for (uint32 i = 0; i < cellNum; i++)
		{
			Board = (SptGooseDataSetIn*)ProcInBuf.GetAddrElement(i);
			Board->SetRecvStatus(b + reader, bb + reader, sizeof(uint32));
			reader += sizeof(uint32);
		}
	}
}

void spt::SptGooseFrameIn::RecPosMsg(void* Buf, uint32 BufLen)
{
	ostatus.recvFrameOkCnt++;
	posFrameNum++;
	uint32 MaxLen = PosElementBuf.Top() * 10 + 4;
	if (MaxLen < BufLen)
	{
		BufLen = MaxLen;
	}
	uint8* b = (uint8*)Buf;
	uint16 frameno = GetLittleEndian16Bit(b);
	b += sizeof(frameno);
	uint16 cellNum = GetLittleEndian16Bit(b);
	b += sizeof(cellNum);
	uint32 sec, fraq;
	sec = GetLittleEndian32Bit(b);
	b += sizeof(sec);
	fraq = GetLittleEndian32Bit(b);
	b += sizeof(fraq);
	stamp.fromPriUtcCode(sec, fraq);
	uint16 state;
	SalDateStamp date;
	uint32 q;
	for (uint32 i = 0; i < cellNum; i++)
	{
		state = GetLittleEndian16Bit(b);
		b += sizeof(state);
		sec = GetLittleEndian32Bit(b);
		b += sizeof(sec);
		fraq = GetLittleEndian32Bit(b);
		b += sizeof(fraq);
		q = state >> 2;
		date.fromUtcCode(sec, fraq);
		((SptGooseData*)PosElementBuf.GetAddrElement(i))->SetValue(state & 0x03, &q, &date);
	}
}

void spt::SptGooseFrameIn::RecAngMsg(void* Buf, uint32 BufLen)
{
	ostatus.recvFrameOkCnt++;
	angFrameNum++;
	uint32 MaxLen = U32ElementBuf.Top() * 13 + 4;
	if (MaxLen < BufLen)
	{
		BufLen = MaxLen;
	}
	uint8* b = (uint8*)Buf;
	uint16 frameno = GetLittleEndian16Bit(b);
	b += sizeof(frameno);
	uint16 cellNum = GetLittleEndian16Bit(b);
	b += sizeof(cellNum);
	uint32 sec, fraq;
	b += sizeof(sec);
	b += sizeof(fraq);
	uint32 state;
	SalDateStamp date;
	uint32 q;
	for (uint32 i = 0; i < cellNum; i++)
	{
		state = GetLittleEndian32Bit(b);
		b += sizeof(state);
		sec = GetLittleEndian32Bit(b);
		b += sizeof(sec);
		fraq = GetLittleEndian32Bit(b);
		b += sizeof(fraq);
		q = b[0];
		b += sizeof(uint8);
		date.fromUtcCode(sec, fraq);
		((SptGooseData*)U32ElementBuf.GetAddrElement(i))->SetValue(state, &q, &date);
	}
}
void spt::SptGooseFrameOut::PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum)
{
	SptStateBoard::PowerUpIni(Name, DesName, IoType, ElementNum);
	virBoard = 0;
}
void spt::SptGooseData::PowerUpIni(const char* Name, const char* DesName, HalBoard* Group, uint32 IoType, uint32 Node, uint32 FrameIndex)
{
	SptStateCell::PowerUpIni(Name, DesName, Group, 0, IoType, Node);
	frameIndex = FrameIndex;
}

void spt::SptGooseData::SetVLinked(bool8 Ok, uint32 Node, uint32 Index, uint32 OffSet, uint32 GoType)
{
	vNode.cell = this;
	vNode.isLinked = Ok;
	vNode.dataSetIndex = Node;
	vNode.dataLinkIndex = Index;
	vNode.dataSetoffSet = OffSet;
	vNode.dataType = GoType;
}

void spt::SptGooseData::SetQLinked(bool8 Ok, uint32 Node, uint32 Index, uint32 OffSet)
{
	qNode.cell = this;
	qNode.isLinked = Ok;
	qNode.dataSetIndex = Node;
	qNode.dataLinkIndex = Index;
	qNode.dataSetoffSet = OffSet;
	qNode.dataType = E_GOSV_Q;
}

void spt::SptGooseData::SetTLinked(bool8 Ok, uint32 Node, uint32 Index, uint32 OffSet)
{
	tNode.cell = this;
	tNode.isLinked = Ok;
	tNode.dataSetIndex = Node;
	tNode.dataLinkIndex = Index;
	tNode.dataSetoffSet = OffSet;
	tNode.dataType = E_GOSV_TIMSSTAMP;
}

void spt::SptGooseData::SetValue(uint32 Value, uint32* Q, SalDateStamp* stamp)
{
	if (blsignalForce)
	{
		return;
	}
	if ((Value != value.value.u32) || (Q && (value.q != *Q)))
	{
		value.value.u32 = Value;

		if (stamp)
		{
			value.stamp = *stamp;
		}
		else
		{
			SalDateStamp stamp;
			stamp.Now();
			value.stamp = stamp;
		}
		uint32 sec, fraq;
		value.stamp.toUtcCode(sec, fraq);
		ChangeEndian(&utcStamp.uSec, &sec, sizeof(sec));
		ChangeEndian(&utcStamp.u_Fra_Q, &fraq, sizeof(fraq));
		if (Q)
		{
			value.q = *Q;
		}
		stateNmb++;
		sequenceNmb = 0;
	}
	else
	{
		sequenceNmb++;
	}
}

const struct spt::SptGooseData::NodeInfo& spt::SptGooseData::QNode()
{
	return qNode;
}

const struct spt::SptGooseData::NodeInfo& spt::SptGooseData::TNode()
{
	return tNode;
}

const struct spt::SptGooseData::NodeInfo& spt::SptGooseData::VNode()
{
	return vNode;
}

bool8 spt::SptGooseData::IsPos()
{
	if ((ioType == E_Go_BOOL_In1) ||
		(ioType == E_Go_Dp_In1) ||
		(ioType == E_Go_Dp_Out1) ||
		(ioType == E_Go_BOOL_Out1)
		)
	{
		return 1;
	}
	return 0;
}

bool8 spt::SptGooseData::SetGoCbCfg(GooseGocbInfo* GocbInfo)
{
	gocbInfo = GocbInfo;
	return 1;
}

const GooseGocbInfo* spt::SptGooseData::GocbInfo()
{
	return gocbInfo;
}

void spt::SptGooseData::GoEnCode(uint32 type, uint8* Buf)
{
	switch (type)
	{
	case E_GOSV_BOOL:
	{
		Buf[0] = (uint8)(value.value.u32 & 0x01);
		break;
	}
	case E_GOSV_DPOS:
	{
		Buf[0] = (uint8)((value.value.u32 & 0x03) << 6);
		break;
	}
	case E_GOSV_Q:
	{
		Buf[0] = (uint8)(value.q >> 8);
		Buf[1] = (uint8)(value.q >> 0);
		break;
	}
	case E_GOSV_FLOAT32:
	case E_GOSV_UINT32:
	case E_GOSV_INT32:
	{
		Buf[0] = (uint8)(value.value.u32 >> 24);
		Buf[1] = (uint8)(value.value.u32 >> 16);
		Buf[2] = (uint8)(value.value.u32 >> 8);
		Buf[3] = (uint8)(value.value.u32 >> 0);
		break;
	}
	case E_GOSV_TIMSSTAMP:
	{
		MemCpy(Buf, &utcStamp, sizeof(utcStamp));
		break;
	}
	default:
		break;
	}
}

void spt::SptGooseDataOut::GoSetValue(uint32 Value)
{
	if (blsignalForce)
	{
		return;
	}
	if (value.value.u32 != Value)
	{
		value.value.u32 = Value;
		if (virBoard)
		{
			SptGooseDataSetOut* out = (SptGooseDataSetOut*)virBoard;
			out->UpdateData(node);
		}
	}
}

void spt::SptGooseDataOut::ForceSetValue(uint32 Value, uint32* Q, SalDateStamp* stamp)
{
	if (!blsignalForce)
	{
		return;
	}
	SptStateCell::ForceSetValue(Value, Q, stamp);
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


void spt::SptGooseDataSetIn::PowerUpIni(const char* Name, const char* DesName, SptGooseFrameIn* VirBoard, uint32 IoType, uint32 ElementNum)
{
	SptStateBoard::PowerUpIni(Name, DesName, IoType, ElementNum);
	virBoard = VirBoard;
	AllocBuf buf(0);
	gocbSub = (struct GooseGocbInfo*)buf.Alloc(sizeof(*gocbSub), 1);
}

bool8 spt::SptGooseDataSetIn::SetGoCbCfg(GooseGocbInfo* GocbSub, uint32 PortIndex, uint16 FpgaFrameIndex)
{
	if (isLinked)
	{
		gocbSub->cfgErr = 1;
		LogErr.Stamp() << "SetGoCbCfg isLinked err.\n";
		return 0;
	}
	if (gocbSub && GocbSub)
	{
		MemCpy(gocbSub, GocbSub, sizeof(*GocbSub));
		if (gocbSub->linked || GocbSub->linked || GocbSub->sAddrErr)
		{
			gocbSub->cfgErr = 1;
			LogErr.Stamp() << "SetGoCbCfg isLinked  already setted, err.\n";
			return 0;
		}
		if (PortIndex > GocbSub->connect.PortEnableNum)
		{
			gocbSub->cfgErr = 1;
			LogErr.Stamp() << "SetGoCbCfg PortIndex err.\n";
			return 0;
		}
		AcardPort = GocbSub->connect.ACard_Port[PortIndex];
		AinnerCardPort = GocbSub->connect.AInnerPortIndex[PortIndex];
		if (GocbSub->connect.BPortEnable[PortIndex])
		{
			isEnableB = 1;
			BcardPort = GocbSub->connect.BCard_Port[PortIndex];
			BinnerCardPort = GocbSub->connect.BInnerPortIndex[PortIndex];
		}
		if (GocbSub->connect.PortEnableNum && GocbSub->connect.APortEnable[0])
		{
			isLinked = gocbSub->linked = 1;
			HalIoCell* cell;
			SptGooseData* scell;
			uint32 tt = gocbSub->dataElementNum;
			ElementBuf.Clear();
			frameIndex = GocbSub->fpgaCmmIndex = gocbSub->fpgaCmmIndex = FpgaFrameIndex;
			SptGooseFrameIn* input = (SptGooseFrameIn*)virBoard;
			for (uint32 i = 0; i < tt; i++)
			{
				uint32 ll = gocbSub->dataLinkedNum[i];
				for (uint32 j = 0; j < ll; j++)
				{
					if ((gocbSub->dataInstId[i][j] != 0xffff) && (gocbSub->dataCardPort[i][j]) == AcardPort)
					{
						cell = input->GetIoCell(gocbSub->dataInstId[i][j]);
						scell = (SptGooseData*)cell;
						if (cell)
						{
							ElementBuf.Push(&scell);
						}
						else
						{
							scell = 0;
							ElementBuf.Push(&scell);
						}
						if (cell)
						{
							scell = (SptGooseData*)cell;
							if (gocbSub->dataType[i] == E_GOSV_Q)
							{
								scell->SetQLinked(1, i, j, gocbSub->frame.dataSetDataOffSet[i]);
							}
							else if (gocbSub->dataType[i] == E_GOSV_TIMSSTAMP)
							{
								scell->SetTLinked(1, i, j, gocbSub->frame.dataSetDataOffSet[i]);
							}
							else
							{
								scell->SetVLinked(1, i, j, gocbSub->frame.dataSetDataOffSet[i], gocbSub->dataType[i]);
							}
							scell->SetGoCbCfg(gocbSub);
							scell->SetVirBoard(this);
						}
					}
				}
			}
			isEnabled = 1;
			SptGooseFrameIn* b = (SptGooseFrameIn*)virBoard;
			b->RgsProcIn(this);
			return 1;
		}
		else
		{
			gocbSub->cfgErr = 1;
			LogErr.Stamp() << "SetGoCbCfg is not enable  err.\n";
		}
	}
	return 0;
}

int32 spt::SptGooseDataSetIn::ProcIni()
{
	if (!isEnabled)
	{
		return -1;
	}
	const struct ApiAppCfg* cfg = SptMain::Instance().AppCfg();
	if (!cfg)
	{
		return -1;
	}
	static uint16 num = 0;
	if (cfg->platform.software == ES_GZKSAU)
	{
		{
			CpuFpgaCmmMsgBuf msg;

			msg.Write(&num, sizeof(num));
			num++;
			uint16 u16temp;
			u16temp = 0x8000;
			if (isEnableB)
			{
				u16temp |= 0x4000;
				u16temp |= (BinnerCardPort & 0x000f) << 10;
			}
			u16temp |= (AinnerCardPort & 0x000f) << 6;
			u16temp |= (gocbSub->fpgaCmmIndex & 0x003f);
			msg.Write(&u16temp, sizeof(u16temp));
			msg.Write(&gocbSub->connect.addr.DstMac[4], sizeof(gocbSub->connect.addr.DstMac[5]));
			msg.Write(&gocbSub->connect.addr.DstMac[5], sizeof(gocbSub->connect.addr.DstMac[5]));
			msg.Write(&gocbSub->connect.addr.appId, sizeof(gocbSub->connect.addr.appId));


			u16temp = gocbSub->control.cbRefLen;
			msg.Write(&u16temp, sizeof(u16temp));
			msg.Write(&gocbSub->control.cbRef, 150);

			u16temp = gocbSub->control.datSetRefLen;
			msg.Write(&u16temp, sizeof(u16temp));
			msg.Write(&gocbSub->control.datSetRef, 150);

			u16temp = gocbSub->control.appIDLen;
			msg.Write(&u16temp, sizeof(u16temp));
			msg.Write(&gocbSub->control.appID, 150);

			msg.Write(&gocbSub->control.confRev, sizeof(gocbSub->control.confRev));
			msg.Write(&gocbSub->dataElementNum, sizeof(gocbSub->dataElementNum));
			msg.SlowSend(0, FpgaMsgProc::E_CPU_FPGA_GOSUB1);
			MsSleep(1);
			LogMsg.Stamp() << gocbSub->control.cbRef << "  FpgaMsgProc::E_CPU_FPGA_GOSUB1 download.\n";
		}
		{
			CpuFpgaCmmMsgBuf msg;
			msg.Write(&num, sizeof(num));
			num++;
			uint16 u16temp;
			u16temp = 0x8000;
			if (isEnableB)
			{
				u16temp |= 0x4000;
				u16temp |= (BinnerCardPort & 0x000f) << 10;
			}
			u16temp |= (AinnerCardPort & 0x000f) << 6;
			u16temp |= (gocbSub->fpgaCmmIndex & 0x003f);
			u16temp |= (gocbSub->fpgaCmmIndex & 0x003f);
			msg.Write(&u16temp, sizeof(u16temp));
			u16temp = gocbSub->dataElementNum;
			msg.Write(&u16temp, sizeof(u16temp));
			uint16 loopend = u16temp;
			for (uint32 i = 0; i < loopend; i++)
			{
				u16temp = SptCcdFile::GetGoSvDataTypeLen(gocbSub->dataType[i]);
				msg.Write(&u16temp, sizeof(u16temp));
			}
			msg.SlowSend(0, FpgaMsgProc::E_CPU_FPGA_GOSUB2);
			MsSleep(1);
			LogMsg.Stamp() << gocbSub->control.cbRef << "  FpgaMsgProc::E_CPU_FPGA_GOSUB2 download.\n";
		}
	}
	MsSleep(1);
	return 0;
}

void spt::SptGooseDataSetIn::SetRecvStatus(uint8* BufA, uint8* BufB, uint32 Len)
{
	MemCpy(&ostatus.checkStatus1, BufA, Len);
	MemCpy(&ostatus.checkStatus2, BufB, Len);
}



void spt::SptGooseDataSetOut::PowerUpIni(const char* Name, const char* DesName, SptGooseFrameOut* VirBoard, uint32 IoType, uint32 ElementNum)
{
	AllocBuf buf(0);
	gocbPub = (struct GooseGocbInfo*)buf.Alloc(sizeof(*gocbPub), 1);
	if (!gocbPub)
	{
		LogErr.Stamp() << "SptGooseDataSetOut gocbPub Alloc buf failed.\n";
	}
	SptStateBoard::PowerUpIni(Name, DesName, IoType, ElementNum);
	virBoard = VirBoard;
	isEnable = 0;
	dataSetElementBuf.Alloc(sizeof(void*), ElementNum * 3);
}

SalString& spt::SptGooseDataSetOut::OuterName()
{
	return outerName;
}

bool8 spt::SptGooseDataSetOut::SetGoCbCfg(GooseGocbInfo* GocbPub, uint16 FpgaFrameIndex)
{
	if (GocbPub && gocbPub)
	{
		MemCpy(gocbPub, GocbPub, sizeof(*gocbPub));
		if (GocbPub->parseErr || GocbPub->sAddrErr)
		{
			return 0;
		}
		if ((GocbPub->connect.PortEnableNum && GocbPub->connect.APortEnable[0]))
		{
			for (uint16 i = 0; i < GocbPub->connect.PortEnableNum; i++)
			{
				uint8 net;
				net = (uint8)GocbPub->connect.AInnerPortIndex[i];
				if (net < sizeof(goNetEnable) * 8)
				{
					goNetEnable[net / 8] |= U8OneBitIsTrue[net % 8];
				}
			}
		}
		else
		{
			gocbPub->cfgErr = 1;
			LogErr.Stamp() << "SetGoCbCfg is not enable err.\n";
			return 0;
		}
		ElementBuf.Clear();
		dataSetElementBuf.Clear();
		HalIoCell* cell;
		SptGooseData* scell;
		uint32 tt = gocbPub->dataElementNum;
		frameIndex = gocbPub->fpgaCmmIndex = FpgaFrameIndex;
		SptGooseFrameIn* input = (SptGooseFrameIn*)virBoard;
		sendstamp.Now();
		for (uint32 i = 0; i < tt; i++)
		{
			if (gocbPub->dataInstId[i][0] != 0xffff)
			{
				cell = input->GetIoCell(gocbPub->dataInstId[i][0]);
				scell = (SptGooseData*)cell;
				if (cell)
				{
					scell = (SptGooseData*)cell;
					scell->SetGoCbCfg(gocbPub);
					scell->SetVirBoard(this);
					if (gocbPub->dataType[i] == E_GOSV_Q)
					{
						scell->SetQLinked(1, i, 0, gocbPub->frame.dataSetDataOffSet[i]);
						void* ptr = (void*)&scell->QNode();
						dataSetElementBuf.Push((void*)&ptr);
					}
					else if (gocbPub->dataType[i] == E_GOSV_TIMSSTAMP)
					{
						scell->SetTLinked(1, i, 0, gocbPub->frame.dataSetDataOffSet[i]);
						void* ptr = (void*)&scell->TNode();
						dataSetElementBuf.Push((void*)&ptr);
					}
					else
					{
						scell->SetVLinked(1, i, 0, gocbPub->frame.dataSetDataOffSet[i], gocbPub->dataType[i]);
						void* ptr = (void*)&scell->VNode();
						dataSetElementBuf.Push((void*)&ptr);
					}
				}
			}
		}
		stNum = 1;
		sqNum = 1;
		isEnable = 1;
		IniGoFrame();
		return 1;
	}
	return 0;
}

void spt::SptGooseDataSetOut::UpdateData(uint32 Node)
{
	if (!isDataUpdate)
	{
		sendstamp.Now();
		isDataUpdate = 1;
	}
}

int32 spt::SptGooseDataSetOut::ProcOut()
{
	if (!(gocbPub && gocbPub->frame.frameOk))
	{
		return -1;
	}
	uint32 now = SptSampInt::Instance().Cnt32();
	if (now == lastSendStamp)
	{
		return -1;
	}
	if (!isDataUpdate)
	{
		uint32 delta = now - lastSendStamp;
		if (delta < 5000)
		{
			return -1;
		}
	}
	//流量控制，一个中断仅发送一个有效数据包
	if (SptMain::Instance().IsHardWare(EH_GZKSAU))
	{
		static uint32 lastsamp;
		uint32 nowsamp = SptSampInt::Instance().Cnt32();
		if (nowsamp == lastsamp)
		{
			return 0;
		}
		lastsamp = nowsamp;
		rtSendMsg.writer = 0;
		static uint16 num = 0;
		rtSendMsg.Write(&num, sizeof(num));
		num++;
		//uint16 temp = gocbPub->fpgaCmmIndex;
		//rtSendMsg.Write(&temp, sizeof(temp));
		//rtSendMsg.Write(&goNetEnable, 2);
		rtSendMsg.writer += 4;
		uint8 u8 = (uint8)stNum;
		rtSendMsg.Write(&u8, 1);
		u8 = (uint8)sqNum;
		rtSendMsg.Write(&u8, 1);
		//temp = (uint16)gocbPub->connect.maxTimeMs;
		//rtSendMsg.Write(&temp, sizeof(temp));
		//temp = (uint16)gocbPub->connect.minTimeMs;
		//rtSendMsg.Write(&temp, sizeof(temp));
		//temp = (uint16)gocbPub->frame.stOffSet;
		//rtSendMsg.Write(&temp, sizeof(temp));
		//temp = (uint16)gocbPub->frame.sqOffSet;
		//rtSendMsg.Write(&temp, sizeof(temp));
		//temp = (uint16)gocbPub->frame.frameLen;
		//rtSendMsg.Write(&temp, sizeof(temp));
		rtSendMsg.writer += 10;
		UpdateFrame(rtSendMsg.msg.BoardCmm.data1 + frameOffSetInRtFrame, sizeof(rtSendMsg.msg.msg.buf) - frameOffSetInRtFrame);
		rtSendMsg.writer += gocbPub->frame.frameLen;
		rtSendMsg.RtSend(0, FpgaMsgProc::E_CPU_FPGA_GOPUB1);
	}
	else
	{

	}
	lastSendStamp = now;
	return 0;
}

int32 spt::SptGooseDataSetOut::ProcIni()
{
	if (!(gocbPub && gocbPub->frame.frameOk))
	{
		return -1;
	}
	return 0;
}
void spt::SptGooseDataSetOut::IniGoFrame()
{
	rtSendMsg.writer = 0;
	static uint16 num = 0;
	rtSendMsg.Write(&num, sizeof(num));
	num++;
	uint16 temp = gocbPub->fpgaCmmIndex;
	rtSendMsg.Write(&temp, sizeof(temp));
	rtSendMsg.Write(&goNetEnable, 2);
	uint8 u8 = (uint8)stNum;
	rtSendMsg.Write(&u8, 1);
	u8 = (uint8)sqNum;
	rtSendMsg.Write(&u8, 1);
	temp = (uint16)gocbPub->connect.maxTimeMs;
	rtSendMsg.Write(&temp, sizeof(temp));
	temp = (uint16)gocbPub->connect.minTimeMs;
	rtSendMsg.Write(&temp, sizeof(temp));
	temp = (uint16)gocbPub->frame.stOffSet;
	rtSendMsg.Write(&temp, sizeof(temp));
	temp = (uint16)gocbPub->frame.sqOffSet;
	rtSendMsg.Write(&temp, sizeof(temp));
	temp = (uint16)gocbPub->frame.frameLen;
	rtSendMsg.Write(&temp, sizeof(temp));
	uint8* buf = rtSendMsg.msg.BoardCmm.data1 + frameOffSetInRtFrame;
	MemCpy(buf, gocbPub->frame.templete, gocbPub->frame.frameLen);
	uint8* dbuf = buf + gocbPub->frame.utcOffSet;
	uint32 sec, fra;
	sendstamp.toUtcCode(sec, fra);
	ChangeEndian(dbuf, &sec, sizeof(sec));
	ChangeEndian(dbuf + 4, &fra, sizeof(fra));
	stNum = 1;
	sqNum = 1;
	isDataUpdate = 0;
	dbuf = buf + gocbPub->frame.stOffSet;
	ChangeEndian(dbuf, &stNum, sizeof(stNum));
	dbuf = buf + gocbPub->frame.sqOffSet;
	ChangeEndian(dbuf, &sqNum, sizeof(sqNum));
	dbuf = buf + gocbPub->frame.testOffSet;
	dbuf[0] = (SptIoProcess::Instance().AppFlags().unitTestState == 1);
	dbuf = buf + gocbPub->frame.dataSetOffSet;
	uint32 loopend = dataSetElementBuf.Top();
	for (uint32 i = 0; i < loopend; i++)
	{
		SptGooseData::NodeInfo* data = (SptGooseData::NodeInfo*)dataSetElementBuf.GetAddrElement(i);
		data->cell->GoEnCode(data->dataType, dbuf + data->dataSetoffSet);
	}
}

void spt::SptGooseDataSetOut::UpdateFrame(uint8* buf, uint32 BufLen)
{
	uint8* dbuf = buf + gocbPub->frame.utcOffSet;
	uint32 sec, fra;
	sendstamp.toUtcCode(sec, fra);
	ChangeEndian(dbuf, &sec, sizeof(sec));
	ChangeEndian(dbuf + 4, &fra, sizeof(fra));
	if (isDataUpdate)
	{
		stNum++;
		sqNum = 1;
	}
	else
	{
		sqNum++;
	}
	isDataUpdate = 0;
	dbuf = buf + gocbPub->frame.stOffSet;
	ChangeEndian(dbuf, &stNum, sizeof(stNum));
	dbuf = buf + gocbPub->frame.sqOffSet;
	ChangeEndian(dbuf, &sqNum, sizeof(sqNum));
	dbuf = buf + gocbPub->frame.testOffSet;
	dbuf[0] = (SptIoProcess::Instance().AppFlags().unitTestState == 1);
	dbuf = buf + gocbPub->frame.dataSetOffSet;
	uint32 loopend = dataSetElementBuf.Top();
	for (uint32 i = 0; i < loopend; i++)
	{
		SptGooseData::NodeInfo* data = (SptGooseData::NodeInfo*)dataSetElementBuf.GetAddrElement(i);
		data->cell->GoEnCode(data->dataType, dbuf + data->dataSetoffSet);
	}
}

void spt::SptGoSvStateBoard::PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 CardNo, uint32 ElementNum)
{
	HalBoard::PowerUpIni(Name, DesName, IoType, ElementNum);
	frameIndex = CardNo;
}

void spt::SptGoSvStateBoard::RecBoardState(uint8* Buf, uint32 Len)
{
	ostatus.recvFrameOkCnt++;
	uint8* b = (uint8*)Buf;
	uint16 frameno = GetLittleEndian16Bit(b);
	b += sizeof(frameno);
	uint16 BoardNo = GetLittleEndian16Bit(b);
	b += sizeof(BoardNo);
	if (frameIndex != BoardNo)
	{
		return;
	}
	progRunState = GetLittleEndian16Bit(b);
	b += sizeof(uint16);
	ostatus.Version1.ProgDate = GetLittleEndian16Bit(b);
	b += sizeof(uint16);
	ostatus.Version1.ProgVersion = GetLittleEndian16Bit(b);
	b += sizeof(uint16);
	ostatus.Version1.ProgCrc = GetLittleEndian32Bit(b);
	b += sizeof(uint32);
	ostatus.Version2.ProgCrc = GetLittleEndian32Bit(b);
	b += sizeof(uint32);
	cfgState = GetLittleEndian16Bit(b);
	b += sizeof(uint16);
	svRecCfgState = GetLittleEndian16Bit(b);
	b += sizeof(uint16);
	svSendCfgState = GetLittleEndian16Bit(b);
	b += sizeof(uint16);
	MemCpy(goRecCfgState, b, sizeof(goRecCfgState));
	b += sizeof(goRecCfgState);
	MemCpy(goRecTypeCfgState, b, sizeof(goRecTypeCfgState));
	b += sizeof(goRecTypeCfgState);
	MemCpy(goRecMapCfgState, b, sizeof(goRecMapCfgState));
	b += sizeof(goRecMapCfgState);
	infoOk = 1;
}

void spt::SptGoSvStateBoard::RecNetState(uint8* Buf, uint32 Len)
{
	ostatus.recvFrameOkCnt++;
	uint8* b = (uint8*)Buf;
	uint16 frameno = GetLittleEndian16Bit(b);
	b += sizeof(frameno);
	uint16 BoardNo = GetLittleEndian16Bit(b);
	b += sizeof(BoardNo);
	uint16 cellNum = GetLittleEndian16Bit(b);
	b += sizeof(cellNum);
	if (frameIndex != BoardNo)
	{
		return;
	}
	if (cellNum > elementNum)
	{
		return;
	}
	uint16 value;
	cellNum = cellNum * E_StateNumPerNet;
	u32value* pv = &netState[0].LightT;
	for (uint32 i = 0; i < cellNum; i++)
	{
		pv->u32 = GetLittleEndian16Bit(b);
		b += sizeof(value);
		pv++;
	}
	stateNmb++;
}



