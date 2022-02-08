#include "ApiProject.h"
using namespace spt;
#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;

void spt::SptIoCell::PowerUpIni(const char* Name, const char* DesName, HalBoard* Group, uint32 IoType, uint32 Node)
{
	SptIoCell::PowerUpIni(Name, DesName, Group, (HalBoard*)0, IoType, Node);
}

void spt::SptIoCell::PowerUpIni(const char* Name, const char* DesName, HalBoard* Group, HalBoard* VirGroup, uint32 IoType, uint32 Node)
{
	HalIoCell::PowerUpIni(Name, DesName, Group, VirGroup, IoType, Node);
}
void spt::SptAngBoard::PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum)
{
	HalBoard::PowerUpIni(Name, DesName, IoType, ElementNum);
}
void spt::SptAngVirInputBoard::PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum, uint32 AdNum, uint8 AdNodeNum)
{
	if (ElementNum < (AdNum * AdNodeNum))
	{
		ElementNum = AdNum * AdNodeNum;
	}
	HalBoard::PowerUpIni(Name, DesName, IoType, ElementNum);
	realDataMap.Alloc(sizeof(ElmentInfo), ElementNum);
	adNum = AdNum;
	adNodeNum = AdNodeNum;
	ProcInBuf.Alloc(sizeof(void*), ElementNum);
}

void spt::SptAngVirInputBoard::RecMsg(void* Buf, uint32 BufLen)
{
	ostatus.recvFrameOkCnt++;
	uint32 MaxLen = elementNum * 6 + 4;
	BufLen -= 2;
	if (MaxLen < BufLen)
	{
		BufLen = MaxLen;
	}
	uint8* b = (uint8*)Buf;
	uint16 frameno = GetLittleEndian16Bit(b);
	b += sizeof(frameno);
	lastSampCnt += 1;
	if (lastSampCnt != frameno)
	{
		SptApiStatus[E_SAS_SampCntJump].Update(1);
		sampCntJumpCnt = 4;
	}
	else
	{
		if (sampCntJumpCnt > 0)
		{
			sampCntJumpCnt--;
		}
		else
		{
			SptApiStatus[E_SAS_SampCntJump].Update(0);
		}
	}
	lastSampCnt = frameno;
	uint16 frameNum = GetLittleEndian16Bit(b);
	b += sizeof(frameNum);
	AngSampValueCell cell;
	frameNum = Min(dataNumOfRealFrm, frameNum);
	ElmentInfo* para = (ElmentInfo*)realDataMap.GetElement(0);
	for (uint32 i = 0; i < frameNum; i++)
	{
		cell.value.u32 = GetLittleEndian32Bit(b);
		b += sizeof(cell.value.u32);
		cell.q = GetLittleEndian16Bit(b);
		b += 2;
		((SptAngSampCell*)para->cellPtr)->PushValue(cell);
		para++;
	}
	stateNmb++;
}

void spt::SptAngVirInputBoard::RecSvInCbCheckStateMsg(void* Buf, uint32 BufLen)
{
	ostatus.recvFrameOkCnt++;
	uint8* b = (uint8*)Buf;
	uint16 frameno = GetLittleEndian16Bit(b);
	b += sizeof(frameno);
	uint16 frameNum = GetLittleEndian16Bit(b);
	b += sizeof(frameNum);
	if (frameNum <= ProcInBuf.Top())
	{
		SptSvInDataSet* Board;
		for (uint32 i = 0; i < frameNum; i++)
		{
			Board = (SptSvInDataSet*)ProcInBuf.GetAddrElement(i);
			Board->SetRecvStatus(b, 4);
			b += 4;
		}
	}
}

int32 spt::SptAngVirInputBoard::ProcIni()
{
	dataNumOfRealFrm = 0;
	uint16 frameBuf[200];
	uint16 index = 0;
	frameBuf[index++] = 0;
	frameBuf[index++] = 0;
	uint16 temp = 0;
	for (uint16 i = 0; i < (uint16)instNum; i++)
	{
		ElmentInfo* para;
		para = (ElmentInfo*)realDataMap.GetElement(dataNumOfRealFrm);
		HalIoCell* cell;
		SptAngSampCell* scell;
		cell = GetIoCell(i);
		if (cell)
		{
			scell = (SptAngSampCell*)cell;
			if (cell->IoType() == cell->E_Normal_Ang)
			{
				para->instNode = i;
				para->frmNode = dataNumOfRealFrm;
				para->cellPtr = scell;
				cell->SetFrameIndex(dataNumOfRealFrm);
				dataNumOfRealFrm++;
				temp = 0;
				if (scell->IsReversal())
				{
					temp |= 0x2000;
				}
				if (scell->IsSingleAd())
				{
					temp |= 0x0080;
				}
				temp = temp | scell->AdIndex() << 10;
				temp = temp | scell->AdNode();
				frameBuf[index++] = temp;
			}
			else if (cell->IoType() == cell->E_9_2_Ang_In)
			{
				SptSampAng_9_2SampCell* scell = (SptSampAng_9_2SampCell*)cell;
				para->instNode = i;
				para->frmNode = dataNumOfRealFrm;
				para->cellPtr = scell;
				cell->SetFrameIndex(dataNumOfRealFrm);
				dataNumOfRealFrm++;
				temp = 0x4000;
				if (scell->IsReversal())
				{
					temp |= 0x2000;
				}
				if (scell->NodeLinkFlag())
				{
					temp = temp | scell->AdIndex() << 10;
					temp = temp | scell->AdNode();
				}
				else
				{
					temp = 0xffff;
				}
				frameBuf[index++] = temp;
			}
			else if (cell->IoType() == cell->E_Local_9_2_Ang_In)
			{
				SptSampAng_9_2SampCell* scell = (SptSampAng_9_2SampCell*)cell;
				para->instNode = i;
				para->frmNode = dataNumOfRealFrm;
				para->cellPtr = scell;
				cell->SetFrameIndex(dataNumOfRealFrm);
				dataNumOfRealFrm++;
				temp = 0x4000;
				if (scell->IsReversal())
				{
					temp |= 0x2000;
				}
				if (scell->NodeLinkFlag())
				{
					temp = temp | scell->AdIndex() << 10;
					temp = temp | scell->AdNode();
				}
				else
				{
					temp = 0xffff;
				}
				frameBuf[index++] = temp;
			}
			else
			{
				LogMsg.Stamp() << "SptAngVirInputBoard ProcIni type err.\n";
			}
		}
		else
		{
			LogMsg.Stamp() << "SptAngVirInputBoard ProcIni cell is null.\n";
		}
	}
	frameBuf[1] = dataNumOfRealFrm;
	CpuFpgaCmmMsgBuf msg;
	msg.Write(&frameBuf, sizeof(frameBuf[0]) * (dataNumOfRealFrm + 2));
	msg.IntSend(0, FpgaMsgProc::E_CPU_FPGA_SVSELECT);
	return 0;
}

int32 spt::SptAngVirInputBoard::ProcIn()
{
	return 0;
}

int32 spt::SptAngVirInputBoard::ProcOut()
{
	if (qUpdate)
	{
		qUpdate = 0;
		qDownPara.frmNO++;
		qDownPara.frmNum = dataNumOfRealFrm;
		CpuFpgaCmmMsgBuf msg;
		msg.Write(&qDownPara, sizeof(qDownPara));
		uint16 q;
		for (uint32 i = 0; i < dataNumOfRealFrm; i++)
		{
			q = (uint16)((ElmentInfo*)realDataMap.GetElement(i))->q;
			msg.Write(&q, sizeof(q));
		}
		msg.IntSend(0, FpgaMsgProc::E_CPU_FPGA_AngQ);
		LogMsg.Stamp() << "Fpga anglog q download.\n";
	}
	if (adCoeUpdate)
	{
		adCoeUpdate = 0;
		coeDownPara.frmNO++;
		uint32 endLoop = adNum * adNodeNum;
		coeDownPara.frmNum = adNum;
		CpuFpgaCmmMsgBuf msg;
		msg.Write(&coeDownPara, sizeof(coeDownPara));
		uint32 q;
		for (uint32 i = 0; i < endLoop; i++)
		{
			q = (uint32)((ElmentInfo*)realDataMap.GetElement(i))->adcoe;
			msg.Write(&q, sizeof(q));
		}
		msg.IntSend(0, FpgaMsgProc::E_CPU_FPGA_ADCOE);
		LogMsg.Stamp() << "Fpga AD coe download.\n";
	}
	if (adadjustUpdate)
	{
		adadjustUpdate = 0;
		adAdjustDownPara.frmNO++;
		adAdjustDownPara.frmNum = adNum;
		CpuFpgaCmmMsgBuf msg;
		msg.Write(&adAdjustDownPara, sizeof(adAdjustDownPara));
		uint16 q;
		uint32 endLoop = adNum * 2;
		for (uint32 i = 0; i < endLoop; i++)
		{
			q = (uint16)((ElmentInfo*)realDataMap.GetElement(i))->adadjust;
			msg.Write(&q, sizeof(q));
		}
		msg.IntSend(0, FpgaMsgProc::E_CPU_FPGA_ADADJUST);
		LogMsg.Stamp() << "Fpga AD adjust download.\n";
	}
	if (addcadjustUpdate)
	{
		addcadjustUpdate = 0;
		addcAdjustDownPara.frmNO++;
		addcAdjustDownPara.frmNum = adNum;
		CpuFpgaCmmMsgBuf msg;
		msg.Write(&adAdjustDownPara, sizeof(adAdjustDownPara));
		uint32 q;
		uint32 endLoop = adNum * adNodeNum;
		for (uint32 i = 0; i < endLoop; i++)
		{
			q = (uint32)((ElmentInfo*)realDataMap.GetElement(i))->addcadjust;
			msg.Write(&q, sizeof(q));
		}
		msg.IntSend(0, FpgaMsgProc::E_CPU_FPGA_ADDCADJUST);
		LogMsg.Stamp() << "Fpga AD adjust download.\n";
	}
	return 0;
}

const SptAngVirInputBoard::ElmentInfo* spt::SptAngVirInputBoard::CellPara(uint32 Index)
{
	if (Index < elementNum)
	{
		const SptAngVirInputBoard::ElmentInfo* para = (const SptAngVirInputBoard::ElmentInfo*)realDataMap.GetElement(Index);
		return para;
	}
	return 0;
}

void spt::SptAngVirInputBoard::SetOutCoe(uint32 Index, uint32 Value)
{
	if (Index < elementNum)
	{
		ElmentInfo* para = (ElmentInfo*)realDataMap.GetElement(Index);
		para->adcoe = Value;
		adCoeUpdate = 1;
	}
}

void spt::SptAngVirInputBoard::SetOutADAdjust(uint32 Index, uint32 Value)
{
	if (Index < AdNum() * adNodeNum)
	{
		ElmentInfo* para = (ElmentInfo*)realDataMap.GetElement(Index);
		para->adadjust = Value;
		adadjustUpdate = 1;
	}
}

void spt::SptAngVirInputBoard::SetAdDcAdJust(uint32 Index, int32 Value)
{
	if (Index < AdNum() * adNodeNum)
	{
		ElmentInfo* para = (ElmentInfo*)realDataMap.GetElement(Index);
		para->addcadjust = Value;
		addcadjustUpdate = 1;
	}
}

uint32 spt::SptAngVirInputBoard::AdNum()
{
	return adNum;
}

void spt::SptAngVirInputBoard::RgsProcIn(SptSvInDataSet* Board)
{
	if (ProcInBuf.Top() < ProcInBuf.ElementNum())
	{
		ProcInBuf.Push(&Board);
	}
	else
	{
		LogErr.Stamp() << "SptAngVirInputBoard Buf is full.\n";
	}
}


void spt::SptAngVirOutputBoard::PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum)
{
	HalBoard::PowerUpIni(Name, DesName, IoType, ElementNum);
}

void spt::SptNormalAngInBoard::PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum)
{
	SptAngBoard::PowerUpIni(Name, DesName, IoType, ElementNum);
}

void spt::SptAngSampCell::PowerUpIni(const char* Name, const char* DesName, HalBoard* Group, HalBoard* VirGroup, uint32 IoType, uint32 Node, uint32 FrameNo, const VarUnits& Units)
{
	singleAd = 0;
	units = &Units;
	frameIndex = FrameNo;
	SptIoCell::PowerUpIni(Name, DesName, Group, VirGroup, IoType, Node);
	ringBuf = ringBuf->Alloc();
	if (!ringBuf)
	{
		LogErr.Stamp() << "SptAngSampCell ringBuf Alloc Err\n";
	}
}

void spt::SptAngSampCell::PushValue(const AngSampValueCell& Value)
{
	stateNmb++;
	value = Value;
	ringBuf->Push(&value);
}
const AngSampValueCell& spt::SptAngSampCell::Value()
{
	return value;
}

const VarUnits* spt::SptAngSampCell::Units()
{
	return units;
}

bool8 spt::SptAngSampCell::IsReversal()
{
	return reverse;
}
void spt::SptAngSampCell::SaveIds(void* Ele)
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
uint16 spt::SptAngSampCell::AdIndex()
{
	return adIndex;
}

uint16 spt::SptAngSampCell::AdNode()
{
	return adNode;
}

bool8 spt::SptAngSampCell::IsSingleAd()
{
	return singleAd;
}


void spt::SptSampAng_9_2SampCell::PowerUpIni(const char* Name, const char* DesName, HalBoard* Group, HalBoard* VirGroup, uint32 IoType, uint32 Node, uint32 FrameNo, const VarUnits& Units)
{
	SptAngSampCell::PowerUpIni(Name, DesName, Group, VirGroup, IoType, Node, FrameNo, Units);
}

void spt::SptSampAng_9_2SampCell::SetNodeLinkFlag(SVcbInfo* SvcbSub, bool8 Flag, uint16 Node)
{
	isNodeLinkOk = Flag;
	node = Node;
	svcbInfo = SvcbSub;
	adIndex = svcbInfo->fpgaCmmIndex;
	adNode = Node;
}

void spt::SptSampAng_9_2SampCell::SetNodeLinkFlag(bool8 Flag, uint16 SvCbIndex, uint16 Node)
{
	isNodeLinkOk = Flag;
	node = Node;
	svcbInfo = 0;
	adIndex = SvCbIndex;
	adNode = Node;
}

bool8 spt::SptSampAng_9_2SampCell::NodeLinkFlag()
{
	return isNodeLinkOk;
}

SVcbInfo* spt::SptSampAng_9_2SampCell::SvcbInfo()
{
	return svcbInfo;
}

void spt::SptSvInDataSet::PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum)
{
	AllocBuf buf(0);
	svcbSub = (struct SVcbInfo*)buf.Alloc(sizeof(*svcbSub), 1);
	if (!svcbSub)
	{
		LogErr.Stamp() << "SptSvOutDataSet svcbPub Alloc buf failed.\n";
	}
	SptAngBoard::PowerUpIni(Name, DesName, IoType, ElementNum);
	isEnable = 0;
}

bool8 spt::SptSvInDataSet::SetSvCbCfg(SVcbInfo* SvcbSub, uint32 PortIndex, uint16 FpgaFrameIndex)
{
	if (isLinked)
	{
		svcbSub->cfgErr = 1;
		LogErr.Stamp() << "SetSvCbCfg isLinked Cfg Err.\n";
		return 0;
	}
	MemCpy(svcbSub, SvcbSub, sizeof(*SvcbSub));
	if (svcbSub && SvcbSub)
	{
		if (SvcbSub->linked)
		{
			svcbSub->cfgErr = 1;
			LogErr.Stamp() << "SetSvCbCfg is isLinked.\n";
			return 0;
		}
		if (PortIndex >= SvcbSub->connect.PortEnableNum)
		{
			svcbSub->cfgErr = 1;
			LogErr.Stamp() << "SetSvCbCfg PortIndex is err.\n";
			return 0;
		}
		cardPort = SvcbSub->connect.Card_Port[PortIndex];
		innerCardPort = SvcbSub->connect.InnerPortIndex[PortIndex];
		if (SvcbSub->connect.PortEnableNum && SvcbSub->connect.PortEnable[PortIndex])
		{

			isLinked = svcbSub->linked = 1;
			HalIoCell* cell;
			SptSampAng_9_2SampCell* scell;
			uint32 tt = svcbSub->dataElementNum;
			SptAngVirInputBoard* input = (SptAngVirInputBoard*)virBoard;
			frameIndex = svcbSub->fpgaCmmIndex = SvcbSub->fpgaCmmIndex = FpgaFrameIndex;
			for (uint32 i = 0; i < tt; i++)
			{
				uint32 ll = svcbSub->dataLinkedNum[i];
				for (uint32 j = 0; j < ll; j++)
				{
					if ((svcbSub->dataInstId[i][j] != 0xffff) && svcbSub->dataCardPort[i][j] == cardPort)
					{
						cell = input->GetIoCell(svcbSub->dataInstId[i][j]);
						if (cell)
						{
							scell = (SptSampAng_9_2SampCell*)cell;
							scell->SetNodeLinkFlag(svcbSub, 1, i);
							scell->SetVirBoard(this);
						}
					}
				}
			}
			isEnable = 1;
			SptAngVirInputBoard* b = (SptAngVirInputBoard*)virBoard;
			b->RgsProcIn(this);
			return 1;
		}
		else
		{
			svcbSub->cfgErr = 1;
			LogErr.Stamp() << "SetSvCbCfg is not Enable.\n";
		}
	}
	return 0;
}

int32 spt::SptSvInDataSet::ProcIni()
{
	if (!isEnable)
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
		CpuFpgaCmmMsgBuf msg;
		msg.Write(&num, sizeof(num));
		num++;
		uint8 u8temp;
		u8temp = (uint8)svcbSub->fpgaCmmIndex;
		msg.Write(&u8temp, sizeof(u8temp));
		u8temp = (uint8)innerCardPort;
		msg.Write(&u8temp, sizeof(u8temp));
		msg.Write(&svcbSub->connect.addr.DstMac[4], sizeof(u8temp));
		msg.Write(&svcbSub->connect.addr.DstMac[5], sizeof(u8temp));
		uint16 u16temp;
		u16temp = svcbSub->connect.addr.appId;
		msg.Write(&u16temp, sizeof(u16temp));
		u16temp = svcbSub->control.smvIDLen;
		msg.Write(&u16temp, sizeof(u16temp));
		msg.Write(&svcbSub->control.smvID, 150);

		u16temp = svcbSub->control.datSetRefLen;
		msg.Write(&u16temp, sizeof(u16temp));
		msg.Write(&svcbSub->control.datSetRef, 150);

		msg.Write(&svcbSub->control.confRev, sizeof(svcbSub->control.confRev));
		msg.Write(&svcbSub->dataElementNum, sizeof(svcbSub->dataElementNum));
		msg.SlowSend(0, FpgaMsgProc::E_CPU_FPGA_SVSUB);
		MsSleep(1);
		LogMsg.Stamp() << "SptSvInDataSet Cfg download.\n";
	}
	return 0;
}

void spt::SptSvInDataSet::SetRecvStatus(uint8* Buf, uint32 Len)
{
	if (Len < sizeof(struct stOutStatus))
	{
		MemCpy(&ostatus.checkStatus1, Buf, Len);
	}

}

void spt::SptSvOutDataSet::PowerUpIni(const char* Name, const char* DesName, uint32 Delay, uint32 IoType, uint32 ElementNum)
{
	AllocBuf buf(0);
	svcbPub = (struct SVcbInfo*)buf.Alloc(sizeof(*svcbPub), 1);
	if (!svcbPub)
	{
		LogErr.Stamp() << "SptSvOutDataSet svcbPub Alloc buf failed.\n";
	}
	SptAngBoard::PowerUpIni(Name, DesName, IoType, ElementNum);
	if (outCellPtrBuf.Alloc(sizeof(void*), ElementNum) == 0)
	{
		LogErr.Stamp() << "SptSvOutDataSet Alloc buf failed.\n";
	}
	dataSetCellOutNum = 0;
	delayUs = Delay;
	realDownPara.Alloc(sizeof(ElmentInfo), ElementNum);
	isEnable = 0;
}

void spt::SptSvOutDataSet::SetOuterName(const char* Str)
{
	outerName = Str;
}

SalString& spt::SptSvOutDataSet::OuterName()
{
	return	outerName;
}

bool8 spt::SptSvOutDataSet::SetSvCbCfg(SVcbInfo* SvcbPub, uint16 FpgaFrameIndex)
{
	if (svcbPub && SvcbPub)
	{
		MemCpy(svcbPub, SvcbPub, sizeof(*SvcbPub));
		if (SvcbPub->parseErr)
		{
			return 0;
		}
		if (SvcbPub->connect.PortEnableNum && SvcbPub->connect.PortEnable[0])
		{
			for (uint32 i = 0; i < SvcbPub->connect.PortEnableNum; i++)
			{
				uint8 net;
				net = (uint8)SvcbPub->connect.InnerPortIndex[i];
				if (net < sizeof(svSendNet) * 8)
				{
					svSendNet[net / 8] |= U8OneBitIsTrue[net % 8];
				}
			}
		}
		else
		{
			svcbPub->cfgErr = 1;
			LogErr.Stamp() << "SetSvCbCfg Card Cfg Err.\n";
			return 0;
		}
		dataSetCellOutNum = svcbPub->dataElementNum;
		frameIndex = SvcbPub->fpgaCmmIndex = svcbPub->fpgaCmmIndex = FpgaFrameIndex;
		SptAngVirOutputBoard* input = (SptAngVirOutputBoard*)virBoard;
		//	uint32 tt = input->InstNum();
		HalIoCell* cell;
		SptSampAng_9_2SampCell* scell;
		for (uint32 i = 0; i < dataSetCellOutNum; i++)
		{
			if (svcbPub->dataInstId[i][0] != 0xffff)
			{
				cell = input->GetIoCell(svcbPub->dataInstId[i][0]);
				if (cell)
				{
					scell = (SptSampAng_9_2SampCell*)cell;
					scell->SetNodeLinkFlag(svcbPub, 1, i);
					scell->SetVirBoard(this);
				}
			}
		}
		isEnable = 1;
		return  1;
	}
	return 0;
}

int32 spt::SptSvOutDataSet::ProcOut()
{
	if (!isEnable)
	{
		return -1;
	}
	if (!selUpdate)
	{

	}
	else if (ioType == E_Vir_Board_SV_DataSetOut1)
	{
		if (!svcbPub)
		{
			return -1;
		}
		if (!svcbPub->frame.frameOk)
		{
			return -1;
		}
		selUpdate = 0;
		selIndex.frmNO++;
		selIndex.frmNum = dataSetCellOutNum;
		CpuFpgaCmmMsgBuf msg;
		msg.Write(&selIndex, sizeof(selIndex));
		uint16 q;
		for (uint32 i = 0; i < dataSetCellOutNum; i++)
		{
			ElmentInfo* para = (ElmentInfo*)realDownPara.GetElement(i);
			q = (uint16)para->frmNode;
			msg.Write(&q, sizeof(q));
		}
		msg.IntSend(0, FpgaMsgProc::E_CPU_FPGA_SVPUB2);
		LogMsg.Stamp() << "Fpga anglog out select download.\n";
	}
	else if (ioType == E_Vir_BoardCMM_SV_DataSetOut1)
	{
		selUpdate = 0;
		selIndex.frmNO++;
		selIndex.frmNum = dataSetCellOutNum;
		CpuFpgaCmmMsgBuf msg;
		msg.Write(&selIndex, sizeof(selIndex));
		uint16 q;
		for (uint32 i = 0; i < dataSetCellOutNum; i++)
		{
			ElmentInfo* para = (ElmentInfo*)realDownPara.GetElement(i);
			q = (uint16)para->frmNode;
			msg.Write(&q, sizeof(q));
		}
		msg.IntSend(0, FpgaMsgProc::E_CPU_FPGA_SVPUB3);
		LogMsg.Stamp() << "Fpga anglog  out select download.\n";
	}
	return 0;
}

int32 spt::SptSvOutDataSet::ProcIni()
{
	if (!isEnable)
	{
		return -1;
	}
	if (ioType == E_Vir_BoardCMM_SV_DataSetOut1)
	{
		return 0;
	}
	const struct ApiAppCfg* cfg = SptMain::Instance().AppCfg();
	if (!cfg)
	{
		return -1;
	}
	if (cfg->platform.software == ES_GZKSAU)
	{
		CpuFpgaCmmMsgBuf msg;
		uint16 u16 = 0;
		msg.Write(&u16, sizeof(u16));
		u16 = 0;
		msg.Write(&u16, sizeof(u16));
		msg.Write(&svSendNet, 6);
		u16 = 0;
		if (svcbPub->control.SmvOpts_security)
		{

			u16 |= 0x08;
		}
		if (svcbPub->control.SmvOpts_refreshTime)
		{
			u16 |= 0x04;
		}
		if (svcbPub->control.SmvOpts_sampleRate)
		{
			u16 |= 0x02;
		}
		msg.Write(&u16, sizeof(u16));
		msg.Write(&svcbPub->connect.addr.DstMac[4], 1);
		msg.Write(&svcbPub->connect.addr.DstMac[5], 1);
		msg.Write(&svcbPub->frame.templete[6], 6);
		msg.Write(&svcbPub->connect.addr.Vlan, 2);
		msg.Write(&svcbPub->connect.addr.appId, 2);
		u16 = (uint16)svcbPub->control.smpRate;
		msg.Write(&u16, 2);
		u16 = (uint16)svcbPub->control.smvIDLen;
		msg.Write(&u16, 2);
		msg.Write(&svcbPub->control.smvID, 150);
		u16 = (uint16)svcbPub->control.datSetRefLen;
		msg.Write(&u16, 2);
		msg.Write(&svcbPub->control.datSetRef, 150);
		msg.Write(&svcbPub->control.confRev, 4);
		msg.Write(&delayUs, 2);
		msg.Write(&svcbPub->dataElementNum, 2);
		msg.SlowSend(0, FpgaMsgProc::E_CPU_FPGA_SVPUB1);
	}
	return 0;
}

void spt::SptSvOutDataSet::SetDelay(uint32 DelayUs)
{
	delayUs = DelayUs;
}

void spt::SptSvOutDataSet::SetSelIndex(uint16 Index, uint16 SelIndex)
{
	if (Index < dataSetCellOutNum)
	{
		ElmentInfo* para = (ElmentInfo*)realDownPara.GetElement(Index);
		para->frmNode = SelIndex;
		selUpdate = 1;
	}
}

uint32 spt::SptSvOutDataSet::GetOutSelIndex(uint32 Index)
{
	if (!svcbPub)
	{
		return -1;
	}
	if (!svcbPub->frame.frameOk)
	{
		return -1;
	}
	if (Index < dataSetCellOutNum)
	{
		HalIoCell* cell;
		SptSampAng_9_2SampCell* scell;
		if (svcbPub->dataInstId[Index][0] != 0xffff)
		{
			SptAngVirOutputBoard* input = (SptAngVirOutputBoard*)virBoard;
			cell = input->GetIoCell(svcbPub->dataInstId[Index][0]);
			if (cell)
			{
				scell = (SptSampAng_9_2SampCell*)cell;
				return scell->FrameIndex();
			}
		}
	}
	return -1;
}









