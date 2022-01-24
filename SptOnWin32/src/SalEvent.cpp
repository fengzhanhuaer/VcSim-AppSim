#include "SptProject.h"
using namespace spt;
#include "SptProject.h"
using namespace spt;
const SalEnumDes spt::DpEnumDes[4] =
{
	{0,"00"},
	{1,"01"},
	{2,"10"},
	{3,"11"},
};

void spt::SalStatus::PowerUpIni(const char* Name, const char* DesName, SalStatusGroup* Group, uint32 type, uint32 flag)
{
	InstObjectGroup* g = (InstObjectGroup*)Group;
	InstObject::PowerUpIni(Name, DesName, g, (uint16)EIOT_STATUS, g->InstId(), g->InstNum());
	exInfoDes.infoNum = 0;
	flags.u32 = flag;
	data.eventId = instId;
	data.typeId = g->InstId();
	disp = 1;
	data.eType = type;
	q.u32 = 0;
}

void spt::SalStatus::ExInfoPowerUpIni(StatusExInfoDesItem* Inf1, StatusExInfoDesItem* Inf2, StatusExInfoDesItem* Inf3, StatusExInfoDesItem* Inf4, StatusExInfoDesItem* Inf5, StatusExInfoDesItem* Inf6, StatusExInfoDesItem* Inf7, StatusExInfoDesItem* Inf8, StatusExInfoDesItem* Inf9)
{
	exInfoDes.infoNum = 0;
	if (!Inf1)
	{
		return;
	}
	exInfoDes.infoNum = 1;
	StrNCpy(exInfoDes.exInfoDes[0].name, Inf1->name, sizeof(exInfoDes.exInfoDes[0].name));
	exInfoDes.exInfoDes[0].dotNum = Inf1->dotNum;
	exInfoDes.exInfoDes[0].valueType = Inf1->valueType;
	exInfoDes.exInfoDes[0].units = Inf1->units;
	exInfoDes.exInfoDes[0].dataWidth = Inf1->dataWidth;
	exInfoDes.exInfoDes[0].pEnum = Inf1->pEnum;
	exInfoDes.exInfoDes[0].EnumNum = Inf1->EnumNum;
	if (!Inf2)
	{
		return;
	}
	exInfoDes.infoNum = 2;
	StrNCpy(exInfoDes.exInfoDes[1].name, Inf2->name, sizeof(exInfoDes.exInfoDes[0].name));
	exInfoDes.exInfoDes[1].dotNum = Inf2->dotNum;
	exInfoDes.exInfoDes[1].valueType = Inf2->valueType;
	exInfoDes.exInfoDes[1].units = Inf2->units;
	exInfoDes.exInfoDes[1].dataWidth = Inf2->dataWidth;
	exInfoDes.exInfoDes[1].pEnum = Inf2->pEnum;
	exInfoDes.exInfoDes[1].EnumNum = Inf2->EnumNum;
	if (!Inf3)
	{
		return;
	}
	exInfoDes.infoNum = 3;
	StrNCpy(exInfoDes.exInfoDes[2].name, Inf3->name, sizeof(exInfoDes.exInfoDes[0].name));
	exInfoDes.exInfoDes[2].dotNum = Inf3->dotNum;
	exInfoDes.exInfoDes[2].valueType = Inf3->valueType;
	exInfoDes.exInfoDes[2].units = Inf3->units;
	exInfoDes.exInfoDes[2].dataWidth = Inf3->dataWidth;
	exInfoDes.exInfoDes[2].pEnum = Inf3->pEnum;
	exInfoDes.exInfoDes[2].EnumNum = Inf3->EnumNum;
	if (!Inf4)
	{
		return;
	}
	exInfoDes.infoNum = 4;
	StrNCpy(exInfoDes.exInfoDes[3].name, Inf4->name, sizeof(exInfoDes.exInfoDes[0].name));
	exInfoDes.exInfoDes[3].dotNum = Inf4->dotNum;
	exInfoDes.exInfoDes[3].valueType = Inf4->valueType;
	exInfoDes.exInfoDes[3].units = Inf4->units;
	exInfoDes.exInfoDes[3].dataWidth = Inf4->dataWidth;
	exInfoDes.exInfoDes[3].pEnum = Inf4->pEnum;
	exInfoDes.exInfoDes[3].EnumNum = Inf4->EnumNum;
	if (!Inf5)
	{
		return;
	}
	exInfoDes.infoNum = 5;
	StrNCpy(exInfoDes.exInfoDes[4].name, Inf5->name, sizeof(exInfoDes.exInfoDes[0].name));
	exInfoDes.exInfoDes[4].dotNum = Inf5->dotNum;
	exInfoDes.exInfoDes[4].valueType = Inf5->valueType;
	exInfoDes.exInfoDes[4].units = Inf5->units;
	exInfoDes.exInfoDes[4].dataWidth = Inf5->dataWidth;
	exInfoDes.exInfoDes[4].pEnum = Inf5->pEnum;
	exInfoDes.exInfoDes[4].EnumNum = Inf5->EnumNum;
	if (!Inf6)
	{
		return;
	}
	exInfoDes.infoNum = 6;
	StrNCpy(exInfoDes.exInfoDes[5].name, Inf6->name, sizeof(exInfoDes.exInfoDes[0].name));
	exInfoDes.exInfoDes[5].dotNum = Inf6->dotNum;
	exInfoDes.exInfoDes[5].valueType = Inf6->valueType;
	exInfoDes.exInfoDes[5].units = Inf6->units;
	exInfoDes.exInfoDes[5].dataWidth = Inf6->dataWidth;
	exInfoDes.exInfoDes[5].pEnum = Inf6->pEnum;
	exInfoDes.exInfoDes[5].EnumNum = Inf6->EnumNum;
	if (!Inf7)
	{
		return;
	}
	exInfoDes.infoNum = 7;
	StrNCpy(exInfoDes.exInfoDes[6].name, Inf7->name, sizeof(exInfoDes.exInfoDes[0].name));
	exInfoDes.exInfoDes[6].dotNum = Inf7->dotNum;
	exInfoDes.exInfoDes[6].valueType = Inf7->valueType;
	exInfoDes.exInfoDes[6].units = Inf7->units;
	exInfoDes.exInfoDes[6].dataWidth = Inf7->dataWidth;
	exInfoDes.exInfoDes[6].pEnum = Inf7->pEnum;
	exInfoDes.exInfoDes[6].EnumNum = Inf7->EnumNum;
	if (!Inf8)
	{
		return;
	}
	exInfoDes.infoNum = 8;
	StrNCpy(exInfoDes.exInfoDes[7].name, Inf8->name, sizeof(exInfoDes.exInfoDes[0].name));
	exInfoDes.exInfoDes[7].dotNum = Inf8->dotNum;
	exInfoDes.exInfoDes[7].valueType = Inf8->valueType;
	exInfoDes.exInfoDes[7].units = Inf8->units;
	exInfoDes.exInfoDes[7].dataWidth = Inf8->dataWidth;
	exInfoDes.exInfoDes[7].pEnum = Inf8->pEnum;
	exInfoDes.exInfoDes[7].EnumNum = Inf8->EnumNum;
	if (!Inf9)
	{
		return;
	}
	exInfoDes.infoNum = 9;
	StrNCpy(exInfoDes.exInfoDes[8].name, Inf9->name, sizeof(exInfoDes.exInfoDes[0].name));
	exInfoDes.exInfoDes[8].dotNum = Inf9->dotNum;
	exInfoDes.exInfoDes[8].valueType = Inf9->valueType;
	exInfoDes.exInfoDes[8].units = Inf9->units;
	exInfoDes.exInfoDes[8].dataWidth = Inf9->dataWidth;
	exInfoDes.exInfoDes[8].pEnum = Inf9->pEnum;
	exInfoDes.exInfoDes[8].EnumNum = Inf9->EnumNum;
}

bool8 spt::SalStatus::SetDisp(bool8 blDisp)
{
	return disp = blDisp;
}

bool8 spt::SalStatus::IsDisp()const
{
	return disp;
}

uint8 spt::SalStatus::ValueType()
{
	return data.eType;
}

const u32value& spt::SalStatus::Value()const
{
	return data.status;
}

const u32value& spt::SalStatus::OldValue() const
{
	return data.oldStatus;
}

void spt::SalStatus::UpdateStatus(u32value S1, u32value S2, u32value S3)
{
	data.exInfo[0] = S1;
	data.exInfo[1] = S2;
	data.exInfo[2] = S3;
}

void spt::SalStatus::UpdateStatus(u32value S1, u32value S2, u32value S3, u32value S4, u32value S5, u32value S6)
{
	UpdateStatus(S1, S2, S3);
	data.exInfo[3] = S4;
	data.exInfo[4] = S5;
	data.exInfo[5] = S6;
}

void spt::SalStatus::UpdateStatus(u32value S1, u32value S2, u32value S3, u32value S4, u32value S5, u32value S6, u32value S7, u32value S8, u32value S9)
{
	UpdateStatus(S1, S2, S3, S4, S5, S6);
	data.exInfo[6] = S7;
	data.exInfo[7] = S8;
	data.exInfo[8] = S9;
}

bool8 spt::SalStatus::UtcTimeToStr(const StatusData& Data, SalString& Str, uint16 LineW) const
{
	SalDateStamp stp;
	Data.GetStamp(stp);
	const SalStatus::Flags& f = Flag();
	if (f.st.isDispUs)
	{
		stp.ToStrHzFmt3(Str);
	}
	else
	{
		stp.ToStrHzFmt2(Str);
	}
	return 1;
}

bool8 spt::SalStatus::ActStr(const StatusData& Data, SalString& Str, uint16 LineW) const
{
	const SalStatus::Flags& f = Flag();
	uint32 NameL = 0;
	if (LineW == 40)
	{
		NameL = 37;
	}
	else
	{
		NameL = LineW - 3;
	}
	if (f.st.isUnDispValueChange)
	{
		Str.Format(Name(), NameL, 1, ' ');
	}
	else
	{
		if (Data.eType == SalStatus::E_BOOL)
		{
			Str.Format(Name(), NameL - 1, 1, ' ');
			Data.ValueStr(Data.status, Str, LineW);
		}
		else if ((Data.eType == SalStatus::E_DPOS) || (Data.eType == SalStatus::E_Hex8))
		{
			Str.Format(Name(), NameL - 6, 1, ' ');
			Data.ValueStr(Data.oldStatus, Str, LineW);
			Str << "→";
			Data.ValueStr(Data.status, Str, LineW);

		}
		else if (Data.eType == SalStatus::E_Hex16)
		{
			Str.Format(Name(), NameL - 4, 1, ' ');
			Data.ValueStr(Data.status, Str, LineW);
		}
	}
	return 1;
}

bool8 spt::SalStatus::BoardStr(const StatusData& Data, SalString& Str, uint16 LineW) const
{
	if (Data.BoardName())
	{
		Str << "板卡:" << Data.BoardName();
		return 1;
	}
	return 0;
}

bool8 spt::SalStatus::QStr(const StatusData& Data, SalString& Str, uint16 LineW) const
{
	Str << "检修:" << Data.q.st.test << " 无效:" << DpEnumDes[Data.q.st.invalid].des << " 调试:" << Data.q.st.debug << " 强制:" << Data.q.st.isForce;
	return 1;
}

bool8 spt::SalStatus::ExternInfoStr(const StatusData& Data, SalString& Str, uint16 LineW) const
{
	if (exInfoDes.infoNum == 0)
	{
		return 0;
	}
	uint32 NameLen = 0;
	uint32 DataLen = 0;
	uint32 UnitLen = 0;
	for (uint32 i = 0; i < exInfoDes.infoNum; i++)
	{
		if (exInfoDes.exInfoDes[i].name[0])
		{
			uint32 l = StrLen(exInfoDes.exInfoDes[i].name);
			if (l > NameLen)
			{
				NameLen = l;
			}
			if (exInfoDes.exInfoDes[i].dataWidth > DataLen)
			{
				DataLen = exInfoDes.exInfoDes[i].dataWidth;
			}
			if (exInfoDes.exInfoDes[i].units)
			{
				l = StrLen(exInfoDes.exInfoDes[i].units->toString());
				if (l > UnitLen)
				{
					UnitLen = l;
				}
			}
		}
	}
	uint32 CellTotalLen = NameLen + 1 + DataLen + 1;
	if (UnitLen)
	{
		CellTotalLen += UnitLen;
	}
	uint32 Row = 0;
	uint32 Col = 0;
	if (LineW == 40)
	{
		LineW = 36;
	}
	else if (LineW == 60)
	{
		LineW = 56;
	}
	Col = LineW / (CellTotalLen + 1);
	if (Col == 0)
	{
		Col = 1;
	}
	uint32 Space = (LineW - (CellTotalLen + 1) * Col);
	if (Col > 1)
	{
		Space = Space / (Col - 1);
	}
	Row = (exInfoDes.infoNum / Col);
	if (Row == 0)
	{
		Row = 1;
	}
	String100B name, unit, data;
	for (uint32 r = 0; r < Row; r++)
	{
		if (r)
		{
			Str << "\n";
		}
		for (uint32 c = 0; c < Col; c++)
		{
			uint32 i = r * Col + c;
			if (i >= exInfoDes.infoNum)
			{
				break;
			}
			ExternInfoStr(Data, i, name, data, unit);
			if (c)
			{
				Str.Format(" ", Space, 1, ' ');
			}
			Str.Format(name.Str(), NameLen, 1, ' ');
			Str << " ";
			Str.Format(data.Str(), DataLen, 0, ' ');
			Str.Format(unit.Str(), UnitLen, 1, ' ');
		}
	}
	return 1;
}

bool8 spt::SalStatus::ExternInfoStr(const StatusData& Data, uint16 Index, SalString& NameStr, SalString& DataStr, SalString& UnitStr) const
{
	if (Index >= exInfoDes.infoNum)
	{
		return 0;
	}
	String100B  dataStr;
	uint32 dt = 0;
	NameStr = exInfoDes.exInfoDes[Index].name;
	E_SalValType tye = (E_SalValType)exInfoDes.exInfoDes[Index].valueType;
	switch (tye)
	{
	case spt::E_SVT_NULL:
		break;
	case spt::E_SVT_BOOL:
		dataStr << (Data.exInfo[Index].u8 & 0X01);
		break;
	case spt::E_SVT_DP:
		dataStr << DpEnumDes[Data.exInfo[Index].u8 & 0X03].des;
		break;
	case spt::E_SVT_U8:
		dataStr.Format(Data.exInfo[Index].u8, exInfoDes.exInfoDes[Index].dotNum);
		break;
	case spt::E_SVT_I8:
		dataStr.Format(Data.exInfo[Index].i8, exInfoDes.exInfoDes[Index].dotNum);
		break;
	case spt::E_SVT_BIT8:
		dataStr.FormatBin(Data.exInfo[Index].u8);
		break;
	case spt::E_SVT_8421_4_8:
		break;
	case spt::E_SVT_ENUM8:
		dt = Data.exInfo[Index].u8;
		if (dt < exInfoDes.exInfoDes[Index].EnumNum)
		{
			dataStr << exInfoDes.exInfoDes[Index].pEnum[dt].des;
		}
		break;
	case spt::E_SVT_HEX8:
		dataStr.FormatHex(Data.exInfo[Index].u8);
		break;
	case spt::E_SVT_U16:
		dataStr.Format(Data.exInfo[Index].u16, exInfoDes.exInfoDes[Index].dotNum);
		break;
	case spt::E_SVT_I16:
		dataStr.Format(Data.exInfo[Index].i16, exInfoDes.exInfoDes[Index].dotNum);
		break;
	case spt::E_SVT_BIT16:
		dataStr.FormatBin(Data.exInfo[Index].u16);
		break;
	case spt::E_SVT_8421_4_16:
		break;
	case spt::E_SVT_HEX16:
		dataStr.FormatHex(Data.exInfo[Index].u16);
		break;
	case spt::E_SVT_ENUM16:
		dt = Data.exInfo[Index].u16;
		if (dt < exInfoDes.exInfoDes[Index].EnumNum)
		{
			dataStr << exInfoDes.exInfoDes[Index].pEnum[dt].des;
		}
		break;
	case spt::E_SVT_U32:
		dataStr.Format(Data.exInfo[Index].u32, exInfoDes.exInfoDes[Index].dotNum);
		break;
	case spt::E_SVT_I32:
		dataStr.Format(Data.exInfo[Index].i32, exInfoDes.exInfoDes[Index].dotNum);
		break;
	case spt::E_SVT_BIT32:
		dataStr.FormatBin(Data.exInfo[Index].u32);
		break;
	case spt::E_SVT_8421_4_32:
		break;
	case spt::E_SVT_HEX32:
		dataStr.FormatHex(Data.exInfo[Index].u32);
		break;
	case spt::E_SVT_ENUM32:
		dt = Data.exInfo[Index].u32;
		if (dt < exInfoDes.exInfoDes[Index].EnumNum)
		{
			dataStr << exInfoDes.exInfoDes[Index].pEnum[dt].des;
		}
		break;
	case spt::E_SVT_FLOAT32:
		break;
	case spt::E_SVT_U64:
		break;
	case spt::E_SVT_I64:
		break;
	case spt::E_SVT_HEX64:
		break;
	case spt::E_SVT_FLOAT64:
		break;
	case spt::E_SVT_INSTOBJECT:
		break;
	case spt::E_SVT_I16CPX:
		break;
	case spt::E_SVT_I32CPX:
		break;
	case spt::E_SVT_F32CPX:
		break;
	case spt::E_SVT_I16POSCPX:
		break;
	case spt::E_SVT_I32POSCPX:
		break;
	case spt::E_SVT_F32POSCPX:
		break;
	case spt::E_SVT_STR:
		break;
	case spt::E_SVT_ST32VAL:
		break;
	case spt::E_SVT_ST64VAL:
		break;
	case spt::E_SVT_ENUMDES:
		break;
	case spt::E_SVT_BITDES:
		break;
	default:
		break;
	}
	DataStr = dataStr.Str();
	if (exInfoDes.exInfoDes[Index].units)
	{
		UnitStr = exInfoDes.exInfoDes[Index].units->toString();
	}
	else
	{
		UnitStr = "";
	}
	return 1;

}

uint8 spt::SalStatus::ExternInfoNum() const
{
	return  exInfoDes.infoNum;
}

bool8 spt::SalStatus::toLcdStr(const StatusData& Data, SalString& Str, uint16 LineW)const
{
	UtcTimeToStr(Data, Str, LineW);
	Str << "\n";
	ActStr(Data, Str, LineW);
	Str << "\n";
	if (BoardStr(Data, Str, LineW))
	{
		Str << "\n";
	}
	if (flags.st.isDispQ && QStr(Data, Str, LineW))
	{
		Str << "\n";
	}
	if ((flags.st.isUnDispRrnExInfo && (Data.status.u32 != 0)) || (!flags.st.isUnDispRrnExInfo))
	{
		if (ExternInfoStr(Data, Str, LineW))
		{
			Str << "\n";
		}
	}
	return 1;
}

const char* spt::SalStatus::BoardName()const
{
	SalStatusGroup* g = (SalStatusGroup*)group;
	return g->BoardName(data.boardId);
}

bool8 spt::SalStatus::Update(uint32 Status, SalDateStamp* stamp, StatusQ* Q)
{
	if (blsignalForce)
	{
		return 0;
	}
	return update(Status, stamp, Q);
}

bool8 spt::SalStatus::ForceUpdate(uint32 Status, SalDateStamp* stamp, StatusQ* Q)
{
	if (!blsignalForce)
	{
		return 0;
	}
	return update(Status, stamp, Q);
}

bool8 spt::SalStatus::Update(StatusData& Data)
{
	SalStatusGroup* g = (SalStatusGroup*)group;
	data = Data;
	Crc16ModBus.AddCrc(&data, sizeof(data));
	g->SaveStatus(instId, data);
	return 1;
}

void spt::SalStatus::afterSave()
{
	if (flags.st.isAutoRtn)
	{
		if (data.status.u32)
		{
			data.oldStatus = data.status;
			data.status.u32 = 0;
		}
	}
}

bool8 spt::SalStatus::update(uint32 Status, SalDateStamp* stamp, StatusQ* Q)
{
	if (data.status.u32 == Status)
	{
		return 0;
	}
	else
	{
		data.oldStatus.u32 = data.status.u32;
		data.status.u32 = Status;
	}
	if (Status)
	{
		data.eventActTimes++;
		if (data.eventActTimes == 0)
		{
			data.eventActTimes++;
		}
	}
	blIni = 1;
	data.q.u32 = this->q.u32;
	if (stamp)
	{
		data.stamp = stamp->Us();
		data.q.byte.tq = stamp->q.q;
	}
	else
	{
		SalDateStamp stamp;
		stamp.Now();
		data.stamp = stamp.Us();
		data.q.byte.tq = (uint8)stamp.q.q;
	}
	SalStatusGroup* g = (SalStatusGroup*)group;
	if (Q)
	{
		data.q.byte.appState = Q->byte.appState;
	}
	else if (g->AppFlags())
	{
		data.q.st.test = g->AppFlags()->unitTestState;
		data.q.st.debug = g->AppFlags()->unitDebugState;
	}
	data.q.st.isForce = blsignalForce;
	if (flags.st.isAutoRtn || flags.st.isUnDispRtn)
	{
		if (data.status.u32 == 0)
		{
			data.q.st.isUnDisp = 1;
		}
	}
	Crc16ModBus.AddCrc(&data, sizeof(data));
	g->SaveStatus(instId, data);
	return 1;
}
bool8 spt::SalStatus::setValue(uint32 Status, SalDateStamp* stamp, StatusQ* Q)
{
	data.oldStatus.u32 = 0;
	data.status.u32 = Status;
	if (Status)
	{
		data.eventActTimes++;
		if (data.eventActTimes == 0)
		{
			data.eventActTimes++;
		}
	}
	blIni = 1;
	data.q.u32 = this->q.u32;
	if (stamp)
	{
		data.stamp = stamp->Us();
		data.q.byte.tq = stamp->q.q;
	}
	else
	{
		SalDateStamp stamp;
		stamp.Now();
		data.stamp = stamp.Us();
		data.q.byte.tq = (uint8)stamp.q.q;
	}
	SalStatusGroup* g = (SalStatusGroup*)group;
	if (Q)
	{
		data.q.byte.appState = Q->byte.appState;
	}
	else if (g->AppFlags())
	{
		data.q.st.test = g->AppFlags()->unitTestState;
		data.q.st.debug = g->AppFlags()->unitDebugState;
	}
	data.q.st.isForce = blsignalForce;
	data.q.st.powerUpIni = 1;
	data.q.st.isUnDisp = 1;
	Crc16ModBus.AddCrc(&data, sizeof(data));
	g->SaveStatus(instId, data);
	return 1;
}

bool8 spt::SalStatus::ifNeedUpdate(uint32 Status)
{
	return ((data.status.u32 != Status) && (!blsignalForce));
}


void spt::SalStatusGroup::PowerUpIni(const char* Name, const char* DesName, uint16 EventNum, SalEnumDes* BoardDes, uint8 BoardTypeNum, uint8 BoardIndex)
{
	InstObjectGroup::PowerUpIni(Name, DesName, (uint16)EIOT_STATUS, EventNum);
	stdheader.eventVer = 1;
	stdheader.eventNum = EventNum;
	stdheader.eventSize = sizeof(StatusData);
	stdheader.eventPoolSize = 0;
	stdheader.eventSaveReader = stdheader.eventSaveWriter = stdheader.eventSaveNum = stdheader.eventValidNum = 0;
	allocBuf();
	boardDes = BoardDes;
	boardTypeNum = BoardTypeNum;
	boardIndex = BoardIndex;
}

const stAppFlags* spt::SalStatusGroup::AppFlags() const
{
	return appFlags;
}

int32 spt::SalStatusGroup::SaveStatus(uint16 eventId, StatusData& status)
{
	if (!statusBuf)
	{
		return -1;
	}

	if (eventId != status.eventId)
	{
		return -1;
	}
	if (eventId >= stdheader.eventNum)
	{
		return -1;
	}
	statusBuf->data[eventId] = status;
	statusIsUpdate = 1;
	return 0;
}

const StatusData* spt::SalStatusGroup::GetStatus(uint16 eventId)
{
	if (eventId >= stdheader.eventNum)
	{
		return 0;
	}
	return (const StatusData*)&statusBuf->data[eventId];
}

SalStatus* spt::SalStatusGroup::GetDes(uint16 eventId)
{
	if (eventId >= InstNum())
	{
		return 0;
	}
	return  (SalStatus*)GetObject(eventId);
}

int32 spt::SalStatusGroup::SaveFile()
{
	return 0;
}

int32 spt::SalStatusGroup::SaveText()
{
	return 0;
}

const char* spt::SalStatusGroup::BoardName(uint16 Index)const
{
	if (boardDes)
	{
		if (Index < boardTypeNum)
		{
			return boardDes[Index].des;
		}
	}
	return 0;
}

void spt::SalStatusGroup::allocBuf()
{
	AllocBuf buf(0);
	void* bf = Calloc(1, sizeof(StatusData) * stdheader.eventNum + sizeof(stdheader));
	if (!bf)
	{
		LogErr.Stamp() << "StatusGroup alloc buf is null.\n";
		return;
	}
	statusBuf = (struct EventGroupDataPool*)bf;
	statusBuf->header = stdheader;
	statusBuf->header.eventPoolSize = stdheader.eventNum;
}

bool8 spt::StatusData::toLcdStr(SalString& Str, uint16 LineW)const
{
	if (IsCrcOk())
	{
		InstObjectGroup* Group = 0;
		if (q.st.isEvent)
		{
			Group = InstObjectRoot::Instance().GetGroup(EIOT_EVENT, typeId);
		}
		else
		{
			Group = InstObjectRoot::Instance().GetGroup(EIOT_STATUS, typeId);
		}
		if (Group)
		{
			InstObject* obj = Group->GetObject(eventId);
			if (obj)
			{
				SalStatus* status = (SalStatus*)obj;
				return status->toLcdStr(*this, Str, LineW);
			}
		}
	}
	return 0;
}

bool8 spt::StatusData::UtcTimeToStr(SalString& Str, uint16 LineW) const
{
	InstObjectGroup* Group = 0;
	if (q.st.isEvent)
	{
		Group = InstObjectRoot::Instance().GetGroup(EIOT_EVENT, typeId);
	}
	else
	{
		Group = InstObjectRoot::Instance().GetGroup(EIOT_STATUS, typeId);
	}
	if (Group)
	{
		InstObject* obj = Group->GetObject(eventId);
		if (obj)
		{
			SalStatus* status = (SalStatus*)obj;
			return status->UtcTimeToStr(*this, Str, LineW);
		}
	}
	return 0;
}

bool8 spt::StatusData::QStr(SalString& Str, uint16 LineW) const
{
	InstObjectGroup* Group = 0;
	if (q.st.isEvent)
	{
		Group = InstObjectRoot::Instance().GetGroup(EIOT_EVENT, typeId);
	}
	else
	{
		Group = InstObjectRoot::Instance().GetGroup(EIOT_STATUS, typeId);
	}
	if (Group)
	{
		InstObject* obj = Group->GetObject(eventId);
		if (obj)
		{
			SalStatus* status = (SalStatus*)obj;
			return status->QStr(*this, Str, LineW);
		}
	}
	return 0;
}

bool8 spt::StatusData::ActStr(SalString& Str, uint16 LineW) const
{
	InstObjectGroup* Group = 0;
	if (q.st.isEvent)
	{
		Group = InstObjectRoot::Instance().GetGroup(EIOT_EVENT, typeId);
	}
	else
	{
		Group = InstObjectRoot::Instance().GetGroup(EIOT_STATUS, typeId);
	}
	if (Group)
	{
		InstObject* obj = Group->GetObject(eventId);
		if (obj)
		{
			SalStatus* status = (SalStatus*)obj;
			return status->ActStr(*this, Str, LineW);
		}
	}
	return 0;
}

bool8 spt::StatusData::ExternInfoStr(SalString& Str, uint16 LineW) const
{
	InstObjectGroup* Group = 0;
	if (q.st.isEvent)
	{
		Group = InstObjectRoot::Instance().GetGroup(EIOT_EVENT, typeId);
	}
	else
	{
		Group = InstObjectRoot::Instance().GetGroup(EIOT_STATUS, typeId);
	}
	if (Group)
	{
		InstObject* obj = Group->GetObject(eventId);
		if (obj)
		{
			SalStatus* status = (SalStatus*)obj;
			return status->ExternInfoStr(*this, Str, LineW);
		}
	}
	return 0;
}

bool8 spt::StatusData::ExternInfoStr(uint16 Index, SalString& NameStr, SalString& DataStr, SalString& UnitStr) const
{
	InstObjectGroup* Group = 0;
	if (q.st.isEvent)
	{
		Group = InstObjectRoot::Instance().GetGroup(EIOT_EVENT, typeId);
	}
	else
	{
		Group = InstObjectRoot::Instance().GetGroup(EIOT_STATUS, typeId);
	}
	if (Group)
	{
		InstObject* obj = Group->GetObject(eventId);
		if (obj)
		{
			SalStatus* status = (SalStatus*)obj;
			return status->ExternInfoStr(*this, Index, NameStr, DataStr, UnitStr);
		}
	}
	return 0;
}

uint8 spt::StatusData::ExternInfoNum() const
{
	InstObjectGroup* Group = 0;
	if (q.st.isEvent)
	{
		Group = InstObjectRoot::Instance().GetGroup(EIOT_EVENT, typeId);
	}
	else
	{
		Group = InstObjectRoot::Instance().GetGroup(EIOT_STATUS, typeId);
	}
	if (Group)
	{
		InstObject* obj = Group->GetObject(eventId);
		if (obj)
		{
			SalStatus* status = (SalStatus*)obj;
			return status->ExternInfoNum();
		}
	}
	return 0;
}

const char* spt::StatusData::BoardName() const
{
	InstObjectGroup* Group = 0;
	if (q.st.isEvent)
	{
		Group = InstObjectRoot::Instance().GetGroup(EIOT_EVENT, typeId);
	}
	else
	{
		Group = InstObjectRoot::Instance().GetGroup(EIOT_STATUS, typeId);
	}
	if (Group)
	{
		SalStatusGroup* g = (SalStatusGroup*)Group;
		return g->BoardName(boardId);
	}
	return 0;
}

const char* spt::StatusData::Name() const
{
	InstObjectGroup* Group = 0;
	if (q.st.isEvent)
	{
		Group = InstObjectRoot::Instance().GetGroup(EIOT_EVENT, typeId);
	}
	else
	{
		Group = InstObjectRoot::Instance().GetGroup(EIOT_STATUS, typeId);
	}
	if (Group)
	{
		InstObject* obj = Group->GetObject(eventId);
		if (obj)
		{
			SalStatus* status = (SalStatus*)obj;
			return status->Name();
		}
	}
	return 0;
}

bool8 spt::StatusData::ValueStr(SalString& Str, uint16 LineW) const
{
	return ValueStr(status, Str, LineW);
}

bool8 spt::StatusData::OldValueStr(SalString& Str, uint16 LineW) const
{
	return ValueStr(oldStatus, Str, LineW);
}

bool8 spt::StatusData::ValueStr(u32value Status, SalString& Str, uint16 LineW) const
{
	if (eType == SalStatus::E_BOOL)
	{
		Str << (Status.bl & 0x01);
		return 1;
	}
	else if (eType == SalStatus::E_DPOS)
	{
		Str << DpEnumDes[Status.u8 & 0x03].des;
		return 1;
	}
	else if (eType == SalStatus::E_Hex8)
	{
		Str.FormatHex(Status.u8);
		return 1;
	}
	else if (eType == SalStatus::E_Hex16)
	{
		Str.FormatHex(Status.u16);
		return 1;
	}
	return 0;
}

bool8 spt::StatusData::AddCrc()
{
	Crc16ModBus.AddCrc(this, sizeof(*this));
	return 1;
}

bool8 spt::StatusData::IsCrcOk()const
{
	return Crc16ModBus.IsCrcOk(this, sizeof(*this));
}

bool8 spt::StatusData::GetStamp(SalDateStamp& Stamp)const
{
	Stamp.Set(stamp);
	Stamp.q.q = q.byte.tq;
	return 1;
}
const SalStatus* spt::StatusData::StatusDes()const
{
	InstObjectGroup* Group = 0;
	if (q.st.isEvent)
	{
		Group = InstObjectRoot::Instance().GetGroup(EIOT_EVENT, typeId);
	}
	else
	{
		Group = InstObjectRoot::Instance().GetGroup(EIOT_STATUS, typeId);
	}
	if (Group)
	{
		InstObject* obj = Group->GetObject(eventId);
		if (obj)
		{
			SalStatus* status = (SalStatus*)obj;
			return status;
		}
	}
	return 0;
}


void spt::SalEvent::PowerUpIni(const char* Name, const char* DesName, class SalEventGroup* Group, uint32 type, uint32 flag)
{
	InstObjectGroup* g = (InstObjectGroup*)Group;
	InstObject::PowerUpIni(Name, DesName, g, (uint16)EIOT_EVENT, g->InstId(), g->InstNum());
	exInfoDes.infoNum = 0;
	flags.u32 = flag;
	data.eventId = instId;
	data.typeId = g->InstId();
	disp = 1;
	data.eType = type;
	q.st.isEvent = 1;
}

bool8 spt::SalEvent::Update(uint32 Status, SalDateStamp* stamp, StatusQ* Q)
{
	bool8 res = SalStatus::Update(Status, stamp, Q);
	if (res)
	{
		SalEventGroup* g = (SalEventGroup*)group;
		g->SaveEvent(instId, data);
	}
	return res;
}

bool8 spt::SalEvent::SetValue(uint32 Status, SalDateStamp* stamp, StatusQ* Q)
{
	bool8 res = SalStatus::setValue(Status, stamp, Q);
	if (res)
	{
		SalEventGroup* g = (SalEventGroup*)group;
		g->SaveEvent(instId, data);
	}
	return res;
}

bool8 spt::SalEvent::ForceUpdate(uint32 Status, SalDateStamp* stamp, StatusQ* Q)
{
	bool8 res = SalStatus::ForceUpdate(Status, stamp, Q);
	if (res)
	{
		SalEventGroup* g = (SalEventGroup*)group;
		g->SaveEvent(instId, data);
	}
	return res;
}

bool8 spt::SalEvent::Update(StatusData& Data)
{
	bool8 res = SalStatus::Update(Data);
	if (res)
	{
		SalEventGroup* g = (SalEventGroup*)group;
		g->SaveEvent(instId, data);
		afterSave();
	}
	return res;
}

void spt::SalEventGroup::PowerUpIni(const char* Name, const char* DesName, uint16 EventNum, uint32 EventPoolSize, const stAppFlags* Flags, SalEnumDes* BoardDes, uint8 BoardTypeNum, uint8 BoardIndex)
{
	InstObjectGroup::PowerUpIni(Name, DesName, (uint16)EIOT_EVENT, EventNum);
	stdheader.eventVer = 1;
	stdheader.eventNum = EventNum;
	stdheader.eventSize = sizeof(StatusData);
	stdheader.eventPoolSize = EventPoolSize + 1;
	stdheader.eventSaveReader = stdheader.eventSaveWriter = stdheader.eventSaveNum = stdheader.eventValidNum = 0;
	appFlags = Flags;
	allocBuf();
	SalStatusGroup::allocBuf();
	if (LoadFile() < 0)
	{
		save2File();
	}
	eventIsUpdate = 0;
	boardDes = BoardDes;
	boardTypeNum = BoardTypeNum;
	boardIndex = BoardIndex;
}

int32 spt::SalEventGroup::SaveEvent(uint16 eventId, StatusData& status)
{
	if (!eventTempBuf)
	{
		return -1;
	}

	if (eventId != status.eventId)
	{
		return -1;
	}
	if (eventId >= stdheader.eventNum)
	{
		return -1;
	}
	EventGroupDataHeader* ph = (EventGroupDataHeader*)&eventTempBuf->header;
	if (!ph->eventPoolSize)
	{
		return 0;
	}
	uint16 w = ph->eventSaveWriter % ph->eventPoolSize;
	eventTempBuf->data[w] = status;
	ph->eventSaveWriter = (w + 1) % ph->eventPoolSize;
	uint32 temp = (ph->eventSaveNum + 1);
	if (temp >= ph->eventPoolSize)
	{
		temp = ph->eventPoolSize - 1;
	}
	ph->eventSaveNum = temp;
	temp = ph->eventValidNum + 1;
	if (temp > ph->eventSaveNum)
	{
		temp = ph->eventSaveNum;
	}
	ph->eventValidNum = temp;
	if (eventIsUpdate < 2)
	{
		SptEventPublishTask::Instance().SaveEvent(this);
	}
	eventIsUpdate++;
	return 0;
}

uint32 spt::SalEventGroup::EventPoolSize()
{
	EventGroupDataHeader* ph = (EventGroupDataHeader*)&stdheader;
	if (!ph->eventPoolSize)
	{
		return 0;
	}
	return ph->eventPoolSize;
}

uint32 spt::SalEventGroup::NewestEventIndex()
{
	if (!eventSaveBuf)
	{
		return 0;
	}
	return (eventSaveBuf->header.eventSaveWriter + eventSaveBuf->header.eventPoolSize - 1) % eventSaveBuf->header.eventPoolSize;
}

uint32 spt::SalEventGroup::OldestEventIndex()
{
	if (!eventSaveBuf)
	{
		return 0;
	}
	return (eventSaveBuf->header.eventSaveWriter + eventSaveBuf->header.eventPoolSize + 1) % eventSaveBuf->header.eventPoolSize;
}


uint32 spt::SalEventGroup::ValidNum()
{
	EventGroupDataHeader* ph = (EventGroupDataHeader*)&eventSaveBuf->header;;
	if (!ph->eventPoolSize)
	{
		return 0;
	}
	return ph->eventValidNum;
}

int32 spt::SalEventGroup::GetNextValidEvent(uint32 Base, uint32 Num, StatusData& Record, bool8 isForDisp)
{
	uint32 valid = 0;
	uint32 reader = (Base) % eventSaveBuf->header.eventPoolSize;
	uint32 w = eventSaveBuf->header.eventSaveWriter % eventSaveBuf->header.eventPoolSize;
	StatusData* record = (StatusData*)eventSaveBuf->data;
	if (isForDisp)
	{
		while (reader != w)
		{
			if (record[reader].IsCrcOk())
			{
				if (!record[reader].q.st.isUnDisp)
				{
					if (valid == Num)
					{
						MemCpy(&Record, &record[reader], sizeof(Record));
						return reader;
					}
					valid++;
				}
				else
				{
					//	LogMsg.Stamp() << "GetNextValidEvent isUnDisp" << reader;
				}
			}
			else
			{
				//	LogMsg.Stamp() << "GetNextValidEvent Crc err" << reader;
			}
			reader = (reader + 1) % eventSaveBuf->header.eventPoolSize;
		}
	}
	else
	{
		while (reader != w)
		{
			if (record[reader].IsCrcOk())
			{
				if (valid == Num)
				{
					MemCpy(&Record, &record[reader], sizeof(Record));
					return reader;
				}
				valid++;
			}
			else
			{
				//LogMsg.Stamp() << "GetNextValidEvent Crc err" << reader;
			}
			reader = (reader + 1) % eventSaveBuf->header.eventPoolSize;
		}
	}
	return -1;
}

SalEvent* spt::SalEventGroup::GetEventDes(uint32 InstId)
{
	InstObject* des;
	des = GetObject(InstId);
	if (des)
	{
		return (SalEvent*)des;
	}
	return 0;
}

int32 spt::SalEventGroup::SaveFile()
{
	EventGroupDataHeader* dstph = (EventGroupDataHeader*)&eventSaveBuf->header;
	EventGroupDataHeader* surph = (EventGroupDataHeader*)&eventTempBuf->header;
	uint32 sw = surph->eventSaveWriter % surph->eventPoolSize;
	uint32 sr = surph->eventSaveReader % surph->eventPoolSize;
	if (sw == sr)
	{
		return 0;
	}
	uint32 dw = dstph->eventSaveWriter % dstph->eventPoolSize;;
	while (sr != sw)
	{
		//fixme 应在此处进行事项的分发

		//事项存储
		if (eventTempBuf->data[sr].q.st.powerUpIni || eventTempBuf->data[sr].q.st.isUnDisp)
		{
			sr = (sr + 1) % surph->eventPoolSize;
			//	LogMsg << "unsave " << sr << " " << eventTempBuf->data[sr].q.st.powerUpIni << " " << eventTempBuf->data[sr].q.st.isUnDisp << "\n";
		}
		else
		{
			//	LogMsg << "save " << sr << " " << dw << "\n";
			eventSaveBuf->data[dw] = eventTempBuf->data[sr];
			dw = (dw + 1) % dstph->eventPoolSize;
			sr = (sr + 1) % surph->eventPoolSize;
			uint32 temp = (dstph->eventSaveNum + 1);
			if (temp >= dstph->eventPoolSize)
			{
				temp = dstph->eventPoolSize - 1;
			}
			dstph->eventSaveNum = temp;
			temp = dstph->eventValidNum + 1;
			if (temp > dstph->eventSaveNum)
			{
				temp = dstph->eventSaveNum;
			}
			dstph->eventValidNum = temp;
		}
	}
	// LogMsg << "save over " << dstph->eventSaveNum << " " << dstph->eventValidNum << "\n";
	surph->eventSaveReader = sr;
	dstph->eventSaveWriter = dw;
	eventIsUpdate = 0;
	return save2File();
}

int32 spt::SalEventGroup::LoadFile()
{
	if (loadFile("event1") < 0)
	{
		bak2File("event1");
		SalFile ofile, nfile;
		ofile.Path().Set(CN_EVENT_FILE_ROOT);
		String100B str;
		str = desName;
		str << ".event2";
		ofile.Name().Set(str.Str());
		ofile.OpenReadOnly();
		str = desName;
		str << ".event1";
		nfile.Path().Set(CN_EVENT_FILE_ROOT);
		nfile.Name().Set(str.Str());
		nfile.Creat();
		nfile.Copy(ofile);
		nfile.Close();
		LogErr.Stamp() << desName << "event1 load err.\n";
		if (loadFile("event1") < 0)
		{
			LogErr.Stamp() << desName << "event2 load err.\n";
			bak2File("event2");
			return -1;
		}
	}
	return 0;
}

void spt::SalEventGroup::ClearEvent()
{
	for (uint32 i = 0; i < eventSaveBuf->header.eventPoolSize; i++)
	{
		StatusData* d = (StatusData*)&eventSaveBuf->data[i];
		d->stamp = 0;
	}
	eventSaveBuf->header.eventSaveReader = eventSaveBuf->header.eventSaveWriter = eventSaveBuf->header.eventSaveNum = eventSaveBuf->header.eventValidNum = 0;
	save2File();
}

void spt::SalEventGroup::allocBuf()
{
	void* bf = Calloc(1, sizeof(StatusData) * stdheader.eventNum * 4 + sizeof(stdheader));
	if (!bf)
	{
		LogErr.Stamp() << "EventGroup alloc buf is null.\n";
		return;
	}
	eventTempBuf = (struct EventGroupDataPool*)bf;
	eventTempBuf->header = stdheader;
	eventTempBuf->header.eventPoolSize = stdheader.eventNum * 4;
	bf = Calloc(1, sizeof(StatusData) * stdheader.eventPoolSize + sizeof(stdheader));
	if (!bf)
	{
		LogErr.Stamp() << "EventGroup alloc buf2 is null.\n";
		return;
	}
	eventSaveBuf = (struct EventGroupDataPool*)bf;
	eventSaveBuf->header = stdheader;
	eventSaveBuf->header.eventPoolSize = stdheader.eventPoolSize;
}

int32 spt::SalEventGroup::save2File()
{
	save2File("event1");
	save2File("event2");
	return 0;
}

int32 spt::SalEventGroup::save2File(const char* FileExtName)
{
	EventGroupDataHeader* dstph = (EventGroupDataHeader*)&eventSaveBuf->header;
	String100B str;
	str = desName;
	str << "." << FileExtName;
	SalFile file;
	file.Name().Set(str.Str());
	file.Path().Set(CN_EVENT_FILE_ROOT);
	file.Creat();
	if (!file.IsOpened())
	{
		LogErr << desName << "event save err.\n";
		return -1;
	}
	Crc16ModBus.AddCrc(dstph, sizeof(*dstph));
	file.Write(eventSaveBuf, eventSaveBuf->SizeOfEventPool());
	file.Close();
	SalStatusGroup::SaveFile();
	return 0;
}

int32 spt::SalEventGroup::loadFile(const char* FileName)
{
	eventSaveBuf->header.eventSaveReader = eventSaveBuf->header.eventSaveWriter = eventSaveBuf->header.eventSaveNum = eventSaveBuf->header.eventValidNum = 0;
	EventGroupDataHeader hd;
	String100B str;
	str = desName;
	str << "." << FileName;
	SalFile file;
	file.Name().Set(str.Str());
	file.Path().Set(CN_EVENT_FILE_ROOT);
	file.OpenReadOnly();
	if (!file.IsOpened())
	{
		if (SptMain::Instance().StartMode() != SptMain::E_Normal)
		{
			return 0;
		}
		file.Creat();
		if (!file.IsOpened())
		{
			LogErr << desName << "event load err.\n";
			return -1;
		}
		if (!eventSaveBuf)
		{
			return -1;
		}
		eventSaveBuf->header.eventSaveReader = (eventSaveBuf->header.eventSaveWriter) % stdheader.eventPoolSize;
		Crc16ModBus.AddCrc(&eventSaveBuf, sizeof(eventSaveBuf->header));
		file.Write(eventSaveBuf, eventSaveBuf->SizeOfEventPool());
		file.Close();
		LogErr << "EventGroup::LoadFile " << desName << " header load err.\n";
		return -1;
	}
	file.Read(&hd, sizeof(eventSaveBuf->header));
	bool8 crcok = Crc16ModBus.IsCrcOk(&hd, sizeof(hd));
	EventGroupDataHeader* ph = &eventSaveBuf->header;
	if ((!crcok) || (hd.eventNum != ph->eventNum) || (hd.eventSize != ph->eventSize) || (hd.eventPoolSize != ph->eventPoolSize) || (hd.eventVer != ph->eventVer))
	{
		LogErr << "EventGroup::LoadFile " << desName;
		LogErr.NotEqual("crcok", crcok, 1);
		LogErr.NotEqual("eventNum", hd.eventNum, ph->eventNum);
		LogErr.NotEqual("eventSize", hd.eventSize, ph->eventSize);
		LogErr.NotEqual("eventPoolSize", hd.eventPoolSize, ph->eventPoolSize);
		LogErr.NotEqual("eventVer", hd.eventVer, ph->eventVer);
		LogErr << " header crc err.\n";
		file.Close();
		return -1;
	}
	file.Seek(file.E_SET, 0);
	file.Read(eventSaveBuf, eventSaveBuf->SizeOfEventPool());
	ph->eventPoolSize = hd.eventPoolSize;
	file.Close();
	hd.eventSaveNum = hd.eventSaveNum % hd.eventPoolSize;
	uint32 num = eventSaveBuf->header.eventPoolSize;
	uint32 oknum = 0;
	for (uint32 i = 0; i < num; i++)
	{
		if (Crc16ModBus.IsCrcOk(&eventSaveBuf->data[i], sizeof(eventSaveBuf->data[0])))
		{
			oknum++;
		}
	}
	hd.eventValidNum = oknum;
	if (ph->eventValidNum >= ph->eventSaveNum)
	{
		ph->eventValidNum = ph->eventSaveNum;
	}
	return 0;
}

int32 spt::SalEventGroup::bak2File(const char* FileName)
{
	String100B str;
	str = desName;
	str << "." << FileName;
	SalFile nfile, ofile;
	ofile.Name().Set(str.Str());
	ofile.Path().Set(CN_EVENT_FILE_ROOT);
	ofile.OpenReadOnly();
	nfile.Name().Set(str.Str());
	nfile.Path().Set(CN_BAK_FILE_ROOT CN_FILE_DivFlag CN_EVENT_FILE_ROOT);
	nfile.Creat();
	nfile.Copy(ofile);
	ofile.Close();
	nfile.Close();
	return 0;
}

int32 spt::SptEventPublishTask::PowerUpIni(int32 Para)
{
	if (SptMain::Instance().StartMode() != SptMain::E_Normal)
	{
		return -1;
	}
	SetSaveBlockPara();
	saveSem.Creat(0);
	Task::PowerUpIni(0);
	Start();
	return 0;
}

int32 spt::SptEventPublishTask::OneLoop()
{
	switch (taskStep)
	{
	case E_PowerUpIni:
	{
		taskStep = E_WaitCmd;
		break;
	}
	case E_WaitCmd:
	{
		CheckLoadEnd();
		int32 res = saveSem.Wait(10000);
		CheckLoadStart();
		saveSemCnt = 0;
		MsSleep(2);
		if ((saveStep == E_BeginSave) || (res == 0))
		{
			SaveAllEvent();
			saveStep = E_EndSave;
		}
		break;
	}
	default:
		taskStep = E_PowerUpIni;
		break;
	}
	return 0;
}

int32 spt::SptEventPublishTask::SaveEvent(SalStatusGroup* EventGroup)
{
	if (saveSemCnt < 2)
	{
		saveStep = E_BeginSave;
		saveSem.Post();
		saveSemCnt++;
	}
	return 0;
}

int32 spt::SptEventPublishTask::SaveEventText(uint32 LineWidth)
{
	{
		InstObjectGroupParent* gp = InstObjectRoot::Instance().GetGroupParent(EIOT_EVENT);

		if (!gp)
		{
			return -1;
		}
		uint32 num = gp->InstNum();
		InstObjectGroup* g;
		SalEventGroup* e;
		for (uint32 i = 0; i < num; i++)
		{
			g = gp->GetGroup(i);
			if (g)
			{
				e = (SalEventGroup*)g;
				e->SaveText();
			}
		}
	}
	{
		InstObjectGroupParent* gp = InstObjectRoot::Instance().GetGroupParent(EIOT_STATUS);
		if (!gp)
		{
			return -1;
		}
		uint32 num = gp->InstNum();
		InstObjectGroup* g;
		SalStatusGroup* e;
		for (uint32 i = 0; i < num; i++)
		{
			g = gp->GetGroup(i);
			if (g)
			{
				e = (SalEventGroup*)g;
				e->SaveText();
			}
		}
	}
	return 0;
}

spt::SptEventPublishTask::SptEventPublishTask()
	:Task("tEventSave", TaskBasePriority - 90, 1024 * 1024, E_T_FLOAT, E_ServiceCore)
{

}

int32 spt::SptEventPublishTask::SaveAllEvent()
{
	if (SptIoProcess::Instance().SptFlag().IsPowerDownAtRange(saveLowLimit, saveHighLimit))
	{
		return 0;
	}
	{
		InstObjectGroupParent* gp = InstObjectRoot::Instance().GetGroupParent(EIOT_EVENT);

		if (!gp)
		{
			return -1;
		}
		uint32 num = gp->InstNum();
		InstObjectGroup* g;
		SalEventGroup* e;
		for (uint32 i = 0; i < num; i++)
		{
			g = gp->GetGroup(i);
			if (g)
			{
				e = (SalEventGroup*)g;
				e->SaveFile();
			}
		}
	}
	{
		InstObjectGroupParent* gp = InstObjectRoot::Instance().GetGroupParent(EIOT_STATUS);

		if (!gp)
		{
			return -1;
		}
		uint32 num = gp->InstNum();
		InstObjectGroup* g;
		SalStatusGroup* e;
		for (uint32 i = 0; i < num; i++)
		{
			g = gp->GetGroup(i);
			if (g)
			{
				e = (SalEventGroup*)g;
				e->SaveFile();
			}
		}
	}
	return 0;
}

