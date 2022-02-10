#include "tinyxml2/tinyxml2.h"
#include "ApiProject.h"
using namespace spt;
using namespace tinyxml2;
const char* ccdFileName = "configured.ccd";

spt::SptCcdFile::SptCcdFile()
{



}

int32 spt::SptCcdFile::ParseCCD(const char* FileName)
{
	MemSet(&outputstatus, 0, sizeof(outputstatus));

	XMLDocument doc;
	String100B file;
	file = CN_T860_CFG_FILE_ROOT;
	file << CN_FILE_DivFlag << FileName;
	XMLError err = doc.LoadFile(file.Str());
	if (XMLError::XML_SUCCESS != err)
	{
		outputstatus.parseErr = 1;
		outputstatus.fileNoExist = 1;
		LogErr.Stamp() << file << " open err" << err << "\n";
		return -1;
	}
	CalCcdCrc();
	const XMLDeclaration* declaration = doc.FirstChild()->ToDeclaration();
	if (!declaration)
	{
		outputstatus.parseErr = 1;
		LogErr.Stamp() << file << " declaration err\n";
		return -1;
	}
	const XMLElement* rootNode = doc.RootElement();
	if (!rootNode)
	{
		outputstatus.parseErr = 1;
		LogErr.Stamp() << file << " declaration err\n";
		return -1;
	}
	if (StrCmp(rootNode->Name(), "IED") != 0)
	{
		outputstatus.parseErr = 1;
		LogErr.Stamp() << file << " rootNode->Name() err " << rootNode->Name() << "\n";
		return -1;
	}

	const XMLElement* element = rootNode->FirstChildElement();

	if (!element)
	{
		outputstatus.parseErr = 1;
		LogErr.Stamp() << file << "element ptr err. ccd parse line" << __LINE__ << "\n";
		return -1;
	}

	while (element)
	{
		if (StrCmp(element->Name(), "GOOSEPUB") == 0)
		{
			gosvInfo.ParseInfo.goPubNum = 0;
			ParseGoosePub(element);
		}
		else if (StrCmp(element->Name(), "SVPUB") == 0)
		{
			gosvInfo.ParseInfo.svPubNum = 0;
			ParseSVPub(element);
		}
		else if (StrCmp(element->Name(), "SVSUB") == 0)
		{
			gosvInfo.ParseInfo.svSubNum = 0;
			ParseSVSub(element);
		}
		else if (StrCmp(element->Name(), "GOOSESUB") == 0)
		{
			gosvInfo.ParseInfo.goSubNum = 0;
			ParseGooseSub(element);
		}
		element = element->NextSiblingElement();
	}
	return 0;
}

int32 spt::SptCcdFile::ParseGoosePub(const XMLElement* goosePub)
{
	if (StrCmp(goosePub->Name(), "GOOSEPUB") != 0)
	{
		LogErr.Stamp() << "GOOSEPUB Name err. ccd parse line" << __LINE__ << "\n";
		outputstatus.goosePubParseErr = 1;
		return -1;
	}
	const XMLElement* element = goosePub->FirstChildElement();
	while (element)
	{
		if ((StrCmp(element->Name(), "GOCBref") == 0) && (gosvInfo.ParseInfo.goPubNum < gosvInfo.ParseInfo.goPubBufNum))
		{
			ParseGoosePubGoCb(element, &gosvInfo.ParseInfo.gocbPub[gosvInfo.ParseInfo.goPubNum]);
			if (gosvInfo.ParseInfo.gocbPub[gosvInfo.ParseInfo.goPubNum].parseErr)
			{
				outputstatus.parseErr = 1;
				outputstatus.goosePubParseErr = 1;
			}
			gosvInfo.ParseInfo.goPubNum++;
		}
		element = element->NextSiblingElement();
	}
	return 0;
}

int32 spt::SptCcdFile::ParseGooseSub(const tinyxml2::XMLElement* node)
{
	if (StrCmp(node->Name(), "GOOSESUB") != 0)
	{
		LogErr.Stamp() << "GOOSESUB Name err. ccd parse line" << __LINE__ << "\n";
		outputstatus.gooseSubParseErr = 1;
		return -1;
	}
	const XMLElement* element = node->FirstChildElement();
	while (element)
	{
		if ((StrCmp(element->Name(), "GOCBref") == 0) && (gosvInfo.ParseInfo.goSubNum < gosvInfo.ParseInfo.goSubBufNum))
		{
			gosvInfo.ParseInfo.gocbSub[gosvInfo.ParseInfo.goSubNum].index = gosvInfo.ParseInfo.goSubNum;
			ParseGooseSubGoCb(element, &gosvInfo.ParseInfo.gocbSub[gosvInfo.ParseInfo.goSubNum]);
			if (gosvInfo.ParseInfo.gocbSub[gosvInfo.ParseInfo.goSubNum].parseErr)
			{
				outputstatus.parseErr = 1;
				outputstatus.gooseSubParseErr = 1;
			}
			gosvInfo.ParseInfo.goSubNum++;
		}
		element = element->NextSiblingElement();
	}
	return 0;
}

int32 spt::SptCcdFile::ParseGoosePubGoCb(const tinyxml2::XMLElement* node, GooseGocbInfo* Info)
{
	if (StrCmp(node->Name(), "GOCBref") != 0)
	{
		LogErr.Stamp() << "ParseGoosePubGoCb Name err. ccd parse line" << __LINE__ << "\n";
		Info->parseErr = 1;
		return -1;
	}
	const XMLAttribute* att = node->FindAttribute("name");
	if (att)
	{
		StrNCpy(Info->control.cbRef, att->Value(), sizeof(Info->control.cbRef));
	}
	else
	{
		LogErr.Stamp() << "ParseGoosePubGoCb cant find name att\n";
	}
	const XMLElement* element = node->FirstChildElement();

	while (element)
	{
		if (StrCmp(element->Name(), "DataSet") == 0)
		{
			ParseGoosePubGoCbDataSet(element, Info);
		}
		else if (StrCmp(element->Name(), "GSEControl") == 0)
		{
			ParseGoosePubGoCbControl(element, Info);
		}
		else if (StrCmp(element->Name(), "ConnectedAP") == 0)
		{
			ParseGoosePubGoCbConnectedAP(element, Info);
		}
		element = element->NextSiblingElement();
	}
	if (!Info->parseErr)
	{
		CreatFrameTemplete(Info);
	}
	return 0;
}

int32 spt::SptCcdFile::ParseGooseSubGoCb(const tinyxml2::XMLElement* node, GooseGocbInfo* Info)
{
	if (StrCmp(node->Name(), "GOCBref") != 0)
	{
		LogErr.Stamp() << "ParseGooseSubGoCb Name err. ccd parse line" << __LINE__ << "\n";
		Info->parseErr = 1;
		return -1;
	}
	const XMLAttribute* att = node->FindAttribute("name");
	if (att)
	{
		StrNCpy(Info->control.cbRef, att->Value(), sizeof(Info->control.cbRef));
	}
	else
	{
		LogErr.Stamp() << "ParseGooseSubGoCb cant find name att\n";
	}
	const XMLElement* element = node->FirstChildElement();

	while (element)
	{
		if (StrCmp(element->Name(), "DataSet") == 0)
		{
			ParseGooseSubGoCbDataSet(element, Info);
		}
		else if (StrCmp(element->Name(), "GSEControl") == 0)
		{
			ParseGooseSubGoCbControl(element, Info);
		}
		else if (StrCmp(element->Name(), "ConnectedAP") == 0)
		{
			ParseGooseSubGoCbConnectedAP(element, Info);
		}
		element = element->NextSiblingElement();
	}
	return 0;
}

int32 spt::SptCcdFile::ParseGoosePubGoCbControl(const tinyxml2::XMLElement* node, GooseGocbInfo* Info)
{
	if (StrCmp(node->Name(), "GSEControl") != 0)
	{
		LogErr.Stamp() << "ParseGoosePubGoCbControl Name err. ccd parse line" << __LINE__ << "\n";
		Info->parseErr = 1;
		return -1;
	}
	if (!node->FindAttribute("confRev"))
	{
		Info->parseErr = 1;
		outputstatus.attLost = 1;
		LogErr.Stamp() << " FindAttribute(\"confRev\")" << __LINE__;
	}
	if (!node->FindAttribute("datSet"))
	{
		Info->parseErr = 1;
		outputstatus.attLost = 1;
		LogErr.Stamp() << " FindAttribute(\"datSet\")" << __LINE__;
	}
	Info->control.confRev = node->UnsignedAttribute("confRev");
	const char* sur = node->Attribute("datSet");
	String200B str;
	str = Info->control.cbRef;
	Info->control.cbRefLen = StrLen(Info->control.cbRef);
	if (str.IsInclude("$") >= 0)
	{
		str.Replace('$', 0);
		str << '$';
	}
	else if (str.IsInclude(".") >= 0)
	{
		str.Replace('.', 0);
		str << '.';
	}
	else
	{
		Info->parseErr = 1;
		LogErr.Stamp() << "ParseGoosePubGoCbControl Name format is not standard.\n";
	}
	str << sur;
	StrNCpy(Info->control.datSet, sur, sizeof(Info->control.datSet));
	Info->control.datSetLen = StrLen(sur);
	StrNCpy(Info->control.datSetRef, str.Str(), sizeof(Info->control.datSet));
	Info->control.datSetRefLen = StrLen(str.Str());

	sur = node->Attribute("name");
	StrNCat(Info->control.name, sur, sizeof(Info->control.name));
	Info->control.nameLen = StrLen(sur);
	if (!node->FindAttribute("appID"))
	{
		Info->parseErr = 1;
		outputstatus.attLost = 1;
		LogErr.Stamp() << " FindAttribute(\"appID\")" << __LINE__;
	}
	sur = node->Attribute("appID");
	StrNCpy(Info->control.appID, sur, sizeof(Info->control.appID));
	Info->control.appIDLen = StrLen(sur);
	return 0;
}

int32 spt::SptCcdFile::ParseGooseSubGoCbControl(const tinyxml2::XMLElement* node, GooseGocbInfo* Info)
{
	if (StrCmp(node->Name(), "GSEControl") != 0)
	{
		LogErr.Stamp() << "ParseGoosePubGoCbControl Name err. ccd parse line" << __LINE__ << "\n";
		Info->parseErr = 1;
		return -1;
	}
	if (!node->FindAttribute("confRev"))
	{
		Info->parseErr = 1;
		outputstatus.attLost = 1;
		LogErr.Stamp() << " FindAttribute(\"confRev\")" << __LINE__;
	}
	if (!node->FindAttribute("datSet"))
	{
		Info->parseErr = 1;
		outputstatus.attLost = 1;
		LogErr.Stamp() << " FindAttribute(\"datSet\")" << __LINE__;
	}
	Info->control.confRev = node->UnsignedAttribute("confRev");
	const char* sur = node->Attribute("datSet");
	String200B str;
	str = Info->control.cbRef;
	Info->control.cbRefLen = StrLen(Info->control.cbRef);
	if (str.IsInclude("$") >= 0)
	{
		str.Replace('$', 0);
		str << '$';
	}
	else if (str.IsInclude(".") >= 0)
	{
		str.Replace('.', 0);
		str << '.';
	}
	else
	{
		Info->parseErr = 1;
		LogErr.Stamp() << "ParseGoosePubGoCbControl Name format is not standard.\n";
	}
	str << sur;
	StrNCpy(Info->control.datSet, sur, sizeof(Info->control.datSet));
	Info->control.datSetLen = StrLen(sur);
	StrNCpy(Info->control.datSetRef, str.Str(), sizeof(Info->control.datSet));
	Info->control.datSetRefLen = StrLen(str.Str());

	sur = node->Attribute("name");
	StrNCat(Info->control.name, sur, sizeof(Info->control.name));
	Info->control.nameLen = StrLen(sur);
	if (!node->FindAttribute("appID"))
	{
		Info->parseErr = 1;
		outputstatus.attLost = 1;
		LogErr.Stamp() << " FindAttribute(\"appID\")" << __LINE__;
	}
	sur = node->Attribute("appID");
	StrNCpy(Info->control.appID, sur, sizeof(Info->control.appID));
	Info->control.appIDLen = StrLen(sur);
	return 0;
}

int32 spt::SptCcdFile::ParseGoosePubGoCbConnectedAP(const tinyxml2::XMLElement* node, GooseGocbInfo* Info)
{
	if (StrCmp(node->Name(), "ConnectedAP") != 0)
	{
		LogErr.Stamp() << "ParseGoosePubGoCbConnectedAP Name err. ccd parse line" << __LINE__ << "\n";
		Info->parseErr = 1;
		return -1;
	}
	const char* sur = node->Attribute("apName");
	StrNCpy(Info->connect.apName, sur, sizeof(Info->connect.apName));
	Info->connect.apNameLen = StrLen(sur);
	sur = node->Attribute("iedName");
	StrNCpy(Info->connect.iedName, sur, sizeof(Info->connect.iedName));
	Info->connect.iedNameLen = StrLen(sur);
	const XMLElement* element = node->FirstChildElement();
	Info->connect.PortEnableNum = 0;
	while (element)
	{
		if (StrCmp(element->Name(), "GSE") == 0)
		{
			const XMLElement* Address;
			Address = element->FirstChildElement("Address");
			if (Address)
			{
				ParseAddress(Address, &Info->connect.addr);
				if (Info->connect.addr.parseErr)
				{
					Info->parseErr = 1;
					element = element->NextSiblingElement();
					continue;
				}
				if ((Info->connect.addr.DstMac[0] != 0x01)
					|| (Info->connect.addr.DstMac[1] != 0x0C)
					|| (Info->connect.addr.DstMac[2] != 0xCD)
					|| (Info->connect.addr.DstMac[3] != 0x01)
					)

				{
					outputstatus.attErr = 1;
					Info->parseErr = 1;
					LogErr.Stamp() << "ParseGoosePubGoCbConnectedAP DstMac err. ccd parse line" << __LINE__ << "\n";
				}
				if (((Info->connect.addr.appId) > (0x3fff)))
				{
					Info->parseErr = 1;
					outputstatus.attErr = 1;
					LogErr.Stamp() << "ParseGoosePubGoCbConnectedAP svPubParseErr err. ccd parse line" << __LINE__ << "\n";
				}
				if (Info->connect.addr.Vlan_Id >= (4096))
				{
					Info->parseErr = 1;
					outputstatus.attErr = 1;
					LogErr.Stamp() << "ParseGoosePubGoCbConnectedAP Vlan_Id err. ccd parse line" << __LINE__ << "\n";
				}
				if (Info->connect.addr.Vlan_PRIORITY > (7))
				{
					Info->parseErr = 1;
					outputstatus.attErr = 1;
					LogErr.Stamp() << "ParseGoosePubGoCbConnectedAP Vlan_PRIORITY err. ccd parse line" << __LINE__ << "\n";
				}
				const XMLElement* maxTime = element->FirstChildElement("MaxTime");
				if (maxTime)
				{
					Info->connect.maxTimeMs = (uint32)maxTime->Unsigned64Text();;
				}
				else
				{
					Info->parseErr = 1;
				}
				const XMLElement* minTime = element->FirstChildElement("MinTime");
				if (minTime)
				{
					Info->connect.minTimeMs = (uint32)minTime->Unsigned64Text();;
				}
				else
				{
					Info->parseErr = 1;
				}
			}
			else
			{
				Info->parseErr = 1;
				outputstatus.attLost = 1;
				LogErr.Stamp() << " ParseGoosePubGoCbConnectedAP FindAttribute(\"Address\")";
			}
		}
		else if (StrCmp(element->Name(), "PhysConn") == 0)
		{
			const XMLElement* type = element->FirstChildElement();
			while (type)
			{
				if (StrCmp(type->Attribute("type"), "Port") == 0)
				{
					if (Info->connect.PortEnableNum >= M_ArrLen(Info->connect.APortEnable))
					{
						break;
					}
					const XMLNode* child = type->FirstChild();
					if (child)
					{
						const XMLText* info = child->ToText();
						const uint8* sur = (const uint8*)info->Value();
						uint16 Card = sur[0];
						Info->connect.APortEnable[Info->connect.PortEnableNum] = 1;
						if ((sur[0]) >= 'A' && (sur[0] <= 'Z'))
						{
							Card -= 'A';
						}
						else if ((sur[0]) >= 'a' && (sur[0] <= 'z'))
						{
							Card -= 'a';
						}
						else if ((sur[0]) >= '1' && (sur[0] <= '9'))
						{
							TransString ts;
							ts.SetBuf((const char*)sur);
							uint32 card = 0;
							ts.Get(card, 0);
							Card = card;
						}
						else
						{
							LogErr.Stamp() << "ParseSVConnectedAP Port err. ccd parse line" << __LINE__ << "\n";
							Info->parseErr = 1;
							Info->connect.APortEnable[Info->connect.PortEnableNum] = 0;
						}
						TransString ts;
						ts.SetBuf((const char*)sur + 2);
						uint32 port = 0;
						ts.Get(port, 0);
						Info->connect.ACard_Port[Info->connect.PortEnableNum] = (Card << 8) + (port & 0x3f);
						Info->connect.PortEnableNum++;
					}
				}
				type = type->NextSiblingElement();
			}
		}
		element = element->NextSiblingElement();
	}
	return 0;
}

int32 spt::SptCcdFile::ParseGooseSubGoCbConnectedAP(const tinyxml2::XMLElement* node, GooseGocbInfo* Info)
{
	if (StrCmp(node->Name(), "ConnectedAP") != 0)
	{
		LogErr.Stamp() << "ParseGoosePubGoCbConnectedAP Name err. ccd parse line" << __LINE__ << "\n";
		Info->parseErr = 1;
		return -1;
	}
	const char* sur = node->Attribute("apName");
	StrNCpy(Info->connect.apName, sur, sizeof(Info->connect.apName));
	Info->connect.apNameLen = StrLen(sur);
	sur = node->Attribute("iedName");
	StrNCpy(Info->connect.iedName, sur, sizeof(Info->connect.iedName));
	Info->connect.iedNameLen = StrLen(sur);
	const XMLElement* element = node->FirstChildElement();
	Info->connect.PortEnableNum = 0;
	while (element)
	{
		if (StrCmp(element->Name(), "GSE") == 0)
		{
			const XMLElement* Address;
			Address = element->FirstChildElement("Address");
			if (Address)
			{
				ParseAddress(Address, &Info->connect.addr);
				if (Info->connect.addr.parseErr)
				{
					Info->parseErr = 1;
					element = element->NextSiblingElement();
					continue;
				}
				if ((Info->connect.addr.DstMac[0] != 0x01)
					|| (Info->connect.addr.DstMac[1] != 0x0C)
					|| (Info->connect.addr.DstMac[2] != 0xCD)
					|| (Info->connect.addr.DstMac[3] != 0x01)
					)

				{
					Info->parseErr = 1;
					outputstatus.attErr = 1;
					LogErr.Stamp() << "ParseGoosePubGoCbConnectedAP DstMac err. ccd parse line" << __LINE__ << "\n";
				}
				if (((Info->connect.addr.appId) > (0x3fff)))
				{
					Info->parseErr = 1;
					outputstatus.attErr = 1;
					LogErr.Stamp() << "ParseGoosePubGoCbConnectedAP svPubParseErr err. ccd parse line" << __LINE__ << "\n";
				}
				if (Info->connect.addr.Vlan_Id >= (4096))
				{
					Info->parseErr = 1;
					outputstatus.attErr = 1;
					LogErr.Stamp() << "ParseGoosePubGoCbConnectedAP Vlan_Id err. ccd parse line" << __LINE__ << "\n";
				}
				if (Info->connect.addr.Vlan_PRIORITY > (7))
				{
					Info->parseErr = 1;
					outputstatus.attErr = 1;
					LogErr.Stamp() << "ParseGoosePubGoCbConnectedAP Vlan_PRIORITY err. ccd parse line" << __LINE__ << "\n";
				}
				const XMLElement* maxTime = element->FirstChildElement("MaxTime");
				if (maxTime)
				{
					Info->connect.maxTimeMs = (uint32)maxTime->Unsigned64Text();;
				}
				else
				{
					Info->parseErr = 1;
				}
				const XMLElement* minTime = element->FirstChildElement("MinTime");
				if (minTime)
				{
					Info->connect.minTimeMs = (uint32)minTime->Unsigned64Text();;
				}
				else
				{
					Info->parseErr = 1;
				}
			}
			else
			{
				Info->parseErr = 1;
				outputstatus.attLost = 1;
				LogErr.Stamp() << " ParseGooseSubGoCbConnectedAP FindAttribute(\"Address\")";
			}
		}
		element = element->NextSiblingElement();
	}
	return 0;
}

int32 spt::SptCcdFile::ParseGoosePubGoCbDataSet(const tinyxml2::XMLElement* node, GooseGocbInfo* Info)
{
	if (StrCmp(node->Name(), "DataSet") != 0)
	{
		LogErr.Stamp() << "ParseGoosePubGoCbDataSet Name err. ccd parse line" << __LINE__ << "\n";
		Info->parseErr = 1;
		return -1;
	}
	const XMLElement* element = node->FirstChildElement();
	const XMLAttribute* att;
	uint16 num = Info->dataElementNum = 0;
	uint16 offset = Info->frame.dataSetLen = 0;
	uint8 l1, l2, l3;
	InstObjectRoot& root = InstObjectRoot::Instance();
	InstObjectGroupParent* groupP = root.GetGroupParent(EIOT_HalIo);
	InstObject* obj;
	while (element)
	{
		if ((StrCmp(element->Name(), "FCDA") == 0) && (num < M_ArrLen(Info->dataType)))
		{
			att = element->FindAttribute("bType");
			int32 type;
			if (!att)
			{
				Info->parseErr = 1;
				LogErr << "ParseGoosePubGoCbDataSet FCDA not include bType unkown \n";
				break;
			}
			type = ParseGoSvDataType(att);
			if (type != -1)
			{
				Info->dataType[num] = (uint8)type;
				Info->dataInstId[num][0] = 0xffff;
				if (GetGoSvDataTypeInfo(type, l1, l2, l3) == 0)
				{
					Info->frame.dataLen[num] = (uint8)l3;
					Info->frame.dataSetTagOffSet[num] = offset;
					Info->frame.dataSetDataOffSet[num] = offset + 1 + l2;
					offset += l1;
					const XMLElement* addr;
					addr = element->FirstChildElement();
					if (addr)
					{
						const XMLAttribute* saddr;
						saddr = addr->FindAttribute("sAddr");
						if (saddr)
						{
							obj = groupP->GetObject(saddr->Value());
							if (obj)
							{
								SptGooseData* o;
								o = (SptGooseData*)obj;
								Info->dataLinkedNum[num] = 1;
								Info->dataGroupId[num][0] = o->GroupId();
								Info->dataInstId[num][0] = o->InstId();
							}
							else
							{
								Info->dataLinkedNum[num] = 0;
								Info->dataGroupId[num][0] = 0xffff;
								Info->dataInstId[num][0] = 0xffff;
								Info->sAddrErr = 1;
								LogErr << "ParseGoosePubGoCbDataSet element not find inst sAddr is " << saddr->Value() << "\n";
							}
						}
						else
						{
							Info->parseErr = 1;
							LogErr << "ParseGoosePubGoCbDataSet element initial err " << att->Value() << "\n";
						}
					}
				}
				else
				{
					Info->parseErr = 1;
					LogErr << "ParseGoosePubGoCbDataSet type unkown " << att->Value() << "\n";
				}
			}
			else
			{
				Info->parseErr = 1;
				LogErr << "ParseGoosePubGoCbDataSet type unkown " << att->Value() << "\n";
				num = 0;
				offset = 0;
				break;
			}
			num++;
		}
		element = element->NextSiblingElement();
	}
	Info->dataElementNum = num;
	Info->frame.dataSetLen = offset;
	return 0;
}

int32 spt::SptCcdFile::ParseGooseSubGoCbDataSet(const tinyxml2::XMLElement* node, GooseGocbInfo* Info)
{
	if (StrCmp(node->Name(), "DataSet") != 0)
	{
		LogErr.Stamp() << "ParseGoosePubGoCbDataSet Name err. ccd parse line" << __LINE__ << "\n";
		Info->parseErr = 1;
		return -1;
	}
	const XMLElement* element = node->FirstChildElement();
	const XMLAttribute* att;
	uint16 num = Info->dataElementNum = 0;
	uint16 sub = Info->dataNumSub = 0;
	uint16 offset = Info->frame.dataSetLen = 0;
	uint8 l1, l2, l3;
	InstObjectRoot& root = InstObjectRoot::Instance();
	InstObjectGroupParent* groupP = root.GetGroupParent(EIOT_HalIo);
	InstObject* obj;
	Info->connect.PortEnableNum = 0;
	while (element)
	{
		if ((StrCmp(element->Name(), "FCDA") == 0) && (num < M_ArrLen(Info->dataType)))
		{
			att = element->FindAttribute("bType");
			int32 type;
			if (!att)
			{
				Info->parseErr = 1;
				LogErr << "ParseGoosePubGoCbDataSet FCDA not include bType unkown \n";
				break;
			}
			type = ParseGoSvDataType(att);

			if (type != -1)
			{
				Info->dataType[num] = (uint8)type;
				Info->dataLinkedNum[num] = 0;
				if (GetGoSvDataTypeInfo(type, l1, l2, l3) == 0)
				{
					Info->frame.dataLen[num] = (uint8)l3;
					Info->frame.dataSetTagOffSet[num] = offset;
					Info->frame.dataSetDataOffSet[num] = offset + 1 + l2;
					offset += l1;
					const XMLElement* intAddr;

					intAddr = element->FirstChildElement("intAddr");

					while (intAddr && (StrCmp(intAddr->Name(), "intAddr") == 0))
					{
						if (Info->dataLinkedNum[num] >= CN_OneGooseLinkMax)
						{
							Info->parseErr = 1;
							LogErr << "ParseGoosePubGoCbDataSet intAddr too many. \n";
							break;
						}
						Info->dataInstId[num][Info->dataLinkedNum[num]] = 0xffff;
						const char* name = intAddr->Attribute("name");
						if (name)
						{
							uint16 APortCfg = 0xffff;
							uint16 BPortCfg = 0xffff;
							if (StrCmp(name, "NULL") != 0)
							{
								if (Info->connect.PortEnableNum < M_ArrLen(Info->connect.APortEnable))
								{
									TransString ts;
									ts.SetBuf(name);
									String100B newaddr;
									ts.Get(newaddr, ':');
									ts.SetBuf(name);
									uint32 loopend = 1;
									if (newaddr.IsInclude("/") >= 0)
									{
										loopend = 2;
									}
									for (uint32 i = 0; i < loopend; i++)
									{
										uint8 Card = 0;
										uint8 Port = 0;
										if ((name[0]) >= 'A' && (name[0] <= 'Z'))
										{
											String100B str;
											ts.Get(str, '-');
											Card = str.Str()[0] - 'A';
										}
										else if ((name[0]) >= 'a' && (name[0] <= 'a'))
										{
											String100B str;
											ts.Get(str, '-');
											Card = str.Str()[0] - 'a';
										}
										else if ((name[0]) >= '1' && (name[0] <= '9'))
										{
											uint32 card = 0;
											String100B str;
											ts.Get(card, '-');
											Card = (uint8)card;
										}
										uint32 port = 0;
										if ((loopend == 2) && (i == 0))
										{
											ts.Get(port, '/');
										}
										else
										{
											ts.Get(port, ':');
										}
										Port = (uint8)port;

										if (loopend == 2)
										{
											if (i == 0)
											{
												APortCfg = (((uint16)Card) << 8) | Port;
											}
											else
											{
												BPortCfg = (((uint16)Card) << 8) | Port;
											}
										}
										else
										{
											APortCfg = (((uint16)Card) << 8) | Port;
											BPortCfg = 0;
										}
									}
									bool8 linked = 0;
									for (uint32 i = 0; i < Info->connect.PortEnableNum; i++)
									{
										if ((APortCfg == Info->connect.ACard_Port[i]) && Info->connect.APortEnable[i])
										{
											linked = 1;
											if ((!Info->connect.BPortEnable[i]) && (loopend == 2))
											{
												Info->connect.BPortEnable[i] = 1;
												Info->connect.BCard_Port[i] = BPortCfg;
											}
											break;
										}
									}
									if (!linked)
									{
										if (loopend == 2)
										{
											Info->connect.APortEnable[Info->connect.PortEnableNum] = 1;
											Info->connect.ACard_Port[Info->connect.PortEnableNum] = APortCfg;
											Info->connect.BPortEnable[Info->connect.PortEnableNum] = 1;
											Info->connect.BCard_Port[Info->connect.PortEnableNum] = BPortCfg;
										}
										else
										{
											Info->connect.APortEnable[Info->connect.PortEnableNum] = 1;
											Info->connect.ACard_Port[Info->connect.PortEnableNum] = APortCfg;
											Info->connect.BPortEnable[Info->connect.PortEnableNum] = 0;
											Info->connect.BCard_Port[Info->connect.PortEnableNum] = 0;
										}
										Info->connect.PortEnableNum++;
									}
								}
								const XMLElement* addr;
								addr = intAddr->FirstChildElement("DAI");
								if (addr)
								{
									const XMLAttribute* saddr;
									saddr = addr->FindAttribute("sAddr");
									if (saddr)
									{
										obj = groupP->GetObject(saddr->Value());
										if (obj)
										{
											SptGooseData* o;
											o = (SptGooseData*)obj;
											Info->dataInstId[num][Info->dataLinkedNum[num]] = o->InstId();
											Info->dataGroupId[num][Info->dataLinkedNum[num]] = o->GroupId();
											Info->dataCardPort[num][Info->dataLinkedNum[num]] = APortCfg;
											Info->dataLinkedNum[num]++;
											sub++;
										}
										else
										{
											Info->dataInstId[num][Info->dataLinkedNum[num]] = 0xffff;
											Info->sAddrErr = 1;
											LogErr << "ParseGoosePubGoCbDataSet element not find inst sAddr is " << saddr->Value() << "\n";
										}
									}
								}
								else
								{
									Info->parseErr = 1;
									LogErr << "ParseGoosePubGoCbDataSet element initial err" << att->Value() << "\n";
								}

							}
						}
						intAddr = intAddr->NextSiblingElement();
					}
				}
				else
				{
					Info->parseErr = 1;
					LogErr << "ParseGoosePubGoCbDataSet type unkown " << att->Value() << "\n";
					num = 0;
					offset = 0;
					break;
				}
			}
			num++;
		}
		element = element->NextSiblingElement();
	}
	Info->dataElementNum = num;
	Info->dataNumSub = sub;
	Info->frame.dataSetLen = offset;
	return 0;
}
int32 spt::SptCcdFile::ParseGoSvDataType(const tinyxml2::XMLAttribute* att)
{
	if (att && StrCmp(att->Value(), "BOOLEAN") == 0)
	{
		return E_GOSV_BOOL;
	}
	else if (att && StrCmp(att->Value(), "Dbpos") == 0)
	{
		return E_GOSV_DPOS;
	}
	else if (att && StrCmp(att->Value(), "Timestamp") == 0)
	{
		return  E_GOSV_TIMSSTAMP;
	}
	else if (att && StrCmp(att->Value(), "Quality") == 0)
	{
		return E_GOSV_Q;
	}
	else if (att && StrCmp(att->Value(), "FLOAT32") == 0)
	{
		return E_GOSV_FLOAT32;
	}
	else if (att && StrCmp(att->Value(), "INT32") == 0)
	{
		return E_GOSV_INT32;
	}
	else if (att && StrCmp(att->Value(), "INT16") == 0)
	{
		return E_GOSV_INT16;
	}
	else if (att && StrCmp(att->Value(), "INT8") == 0)
	{
		return E_GOSV_INT8;
	}
	else if (att && StrCmp(att->Value(), "INT32U") == 0)
	{
		return E_GOSV_UINT32;
	}
	else if (att && StrCmp(att->Value(), "INT16U") == 0)
	{
		return E_GOSV_UINT16;
	}
	else if (att && StrCmp(att->Value(), "INT8U") == 0)
	{
		return E_GOSV_UINT8;
	}
	else if (att)
	{
		LogErr.Stamp() << "GOSV parse unkown type " << att->Value() << "\n";
		return -1;
	}
	return -1;
}

int32 spt::SptCcdFile::ParseSVPub(const tinyxml2::XMLElement* svPub)
{
	if (StrCmp(svPub->Name(), "SVPUB") != 0)
	{
		LogErr.Stamp() << "SVPUB Name err. ccd parse line" << __LINE__ << "\n";
		outputstatus.svPubParseErr = 1;
		return -1;
	}
	const XMLElement* element = svPub->FirstChildElement();
	while (element)
	{
		if ((StrCmp(element->Name(), "SMVCBref") == 0) && (gosvInfo.ParseInfo.svPubNum < gosvInfo.ParseInfo.svPubBufNum))
		{
			ParseSVPubCb(element, &gosvInfo.ParseInfo.svcbPub[gosvInfo.ParseInfo.svPubNum]);
			if (gosvInfo.ParseInfo.svcbPub[gosvInfo.ParseInfo.svPubNum].parseErr)
			{
				outputstatus.parseErr = 1;
				outputstatus.svPubParseErr = 1;
			}
			gosvInfo.ParseInfo.svPubNum++;
		}
		element = element->NextSiblingElement();
	}

	return 0;
}

int32 spt::SptCcdFile::ParseSVSub(const tinyxml2::XMLElement* node)
{
	if (StrCmp(node->Name(), "SVSUB") != 0)
	{
		LogErr.Stamp() << "SVPUB Name err. ccd parse line" << __LINE__ << "\n";
		outputstatus.svSubParseErr = 1;
		return -1;
	}
	const XMLElement* element = node->FirstChildElement();
	while (element)
	{
		if ((StrCmp(element->Name(), "SMVCBref") == 0) && (gosvInfo.ParseInfo.svSubNum < gosvInfo.ParseInfo.svSubBufNum))
		{
			gosvInfo.ParseInfo.svcbSub[gosvInfo.ParseInfo.svSubNum].index = gosvInfo.ParseInfo.svSubNum;
			ParseSVSubCb(element, &gosvInfo.ParseInfo.svcbSub[gosvInfo.ParseInfo.svSubNum]);
			if (gosvInfo.ParseInfo.svcbSub[gosvInfo.ParseInfo.svSubNum].parseErr)
			{
				outputstatus.parseErr = 1;
				outputstatus.svSubParseErr = 1;
			}
			gosvInfo.ParseInfo.svSubNum++;
		}
		element = element->NextSiblingElement();
	}

	return 0;
}

int32 spt::SptCcdFile::ParseSVPubCb(const tinyxml2::XMLElement* node, SVcbInfo* Info)
{
	if (StrCmp(node->Name(), "SMVCBref") != 0)
	{
		LogErr.Stamp() << "ParseSVPubCb Name err. ccd parse line" << __LINE__ << "\n";
		Info->parseErr = 1;
		return -1;
	}
	const XMLAttribute* att = node->FindAttribute("name");
	if (att)
	{
		StrNCpy(Info->control.cbRef, att->Value(), sizeof(Info->control.cbRef));
	}
	else
	{
		Info->parseErr = 1;
		LogErr.Stamp() << "ParseSVPubCb cant find name att\n";
	}
	const XMLElement* element = node->FirstChildElement();
	while (element)
	{
		if (StrCmp(element->Name(), "DataSet") == 0)
		{
			ParseSVPubCbDataSet(element, Info);
		}
		else if (StrCmp(element->Name(), "SampledValueControl") == 0)
		{
			ParseSVPubCbControl(element, Info);
		}
		else if (StrCmp(element->Name(), "ConnectedAP") == 0)
		{
			ParseSVPubConnectedAP(element, Info);
		}

		element = element->NextSiblingElement();
	}
	if (!Info->parseErr)
	{
		CreatFrameTemplete(Info);
	}
	return 0;
}

int32 spt::SptCcdFile::ParseSVSubCb(const tinyxml2::XMLElement* node, SVcbInfo* Info)
{
	if (StrCmp(node->Name(), "SMVCBref") != 0)
	{
		LogErr.Stamp() << "ParseSVSubCb Name err. ccd parse line" << __LINE__ << "\n";
		Info->parseErr = 1;
		return -1;
	}
	const XMLAttribute* att = node->FindAttribute("name");
	if (att)
	{
		StrNCpy(Info->control.cbRef, att->Value(), sizeof(Info->control.cbRef));
	}
	else
	{
		Info->parseErr = 1;
		LogErr.Stamp() << "ParseSVSubCb cant find name att\n";
	}
	const XMLElement* element = node->FirstChildElement();
	while (element)
	{
		if (StrCmp(element->Name(), "DataSet") == 0)
		{
			ParseSVSubCbDataSet(element, Info);
		}
		else if (StrCmp(element->Name(), "SampledValueControl") == 0)
		{
			ParseSVSubCbControl(element, Info);
		}
		else if (StrCmp(element->Name(), "ConnectedAP") == 0)
		{
			ParseSVSubConnectedAP(element, Info);
		}
		element = element->NextSiblingElement();
	}
	return 0;
}

void spt::SptCcdFile::CreatFrameTemplete(SVcbInfo* Info)
{
	if (Info->parseErr)
	{
		Info->frame.frameOk = 0;
		return;
	}
	Info->frame.frameLen = 0;
	Info->frame.frameOk = 1;
	//目的MAC
	MemCpy(Info->frame.templete + Info->frame.frameLen, &Info->connect.addr.DstMac, sizeof(Info->connect.addr.DstMac));
	Info->frame.frameLen += sizeof(Info->connect.addr.DstMac);
	uint8 SurMac[6];
	ApiSysEthNetCfg::Instance().EthNet[1].mac.Data(SurMac[0], SurMac[1], SurMac[2], SurMac[3], SurMac[4], SurMac[5]);
	//源MAC
	MemCpy(Info->frame.templete + Info->frame.frameLen, &SurMac, sizeof(Info->connect.addr.DstMac));
	Info->frame.frameLen += sizeof(Info->connect.addr.DstMac);
	Info->frame.templete[Info->frame.frameLen++] = 0x81;
	Info->frame.templete[Info->frame.frameLen++] = 0x00;
	//VLAN
	Info->frame.templete[Info->frame.frameLen++] = (uint8)(Info->connect.addr.Vlan >> 8);
	Info->frame.templete[Info->frame.frameLen++] = (uint8)(Info->connect.addr.Vlan);
	//TYPE
	Info->frame.templete[Info->frame.frameLen++] = 0x88;
	Info->frame.templete[Info->frame.frameLen++] = 0xBA;
	//APPID
	Info->frame.templete[Info->frame.frameLen++] = (uint8)(Info->connect.addr.appId >> 8);
	Info->frame.templete[Info->frame.frameLen++] = (uint8)(Info->connect.addr.appId);
	//asdu
	uint16 dataSetLen = Info->frame.dataSetLen = Info->dataElementNum * 8;
	uint8 tagSeqOfData[4] = { 0x87,0 };
	uint16 tagSeqOfDataLen = 1 + TagChanLenEncode(tagSeqOfData + 1, dataSetLen);
	uint8 tagSync[3] = { 0x85, 0x01,0x01 };
	uint8 tagSyncLen = 3;
	uint8 tagConfigVer[6] = { 0x83, 0x04 };
	tagConfigVer[2] = (uint8)(Info->control.confRev >> 24);
	tagConfigVer[3] = (uint8)(Info->control.confRev >> 16);
	tagConfigVer[4] = (uint8)(Info->control.confRev >> 8);
	tagConfigVer[5] = (uint8)(Info->control.confRev >> 0);
	uint8 tagConfigVerLen = 6;
	uint8 tagSampCount[4] = { 0x82, 0x02,0x00,0x00 };
	uint8 tagSampCountLen = 4;
	uint8 tagSvId[4] = { 0x80,0x00 };
	uint8 svIdLen = StrLen(Info->control.smvID);
	uint8 tagSvIdLen = 1 + TagChanLenEncode(tagSvId + 1, svIdLen);
	uint8 tagASDU[4] = { 0x30,0x00 };
	uint16 ASDULen = tagSvIdLen + svIdLen + tagSampCountLen + tagConfigVerLen + tagSyncLen + tagSeqOfDataLen + dataSetLen;
	uint8 tagASDULen = 1 + TagChanLenEncode(tagASDU + 1, ASDULen);
	//pdu
	uint8 tagSeqOfASDU[4] = { 0xA2,0 };
	uint16 SeqOfASDULen = tagASDULen + ASDULen;
	uint16 tagSeqOfASDULen = 1 + TagChanLenEncode(tagSeqOfASDU + 1, SeqOfASDULen);
	uint8 tagNumOfASDU[4] = { 0x80,0x01,0x01 };
	uint8 tagNumOfASDULen = 3;
	uint8 tagPduLen[4] = { 0x60,0x00 };
	uint16 PduLen = SeqOfASDULen + tagSeqOfASDULen + tagNumOfASDULen;
	uint8 tagPduLenLen = 1 + TagChanLenEncode(tagPduLen + 1, PduLen);
	//APPLEN
	uint16 AppLen = PduLen + tagPduLenLen + 8;
	Info->frame.templete[Info->frame.frameLen++] = (uint8)(AppLen >> 8);
	Info->frame.templete[Info->frame.frameLen++] = (uint8)(AppLen);
	//reserved
	Info->frame.templete[Info->frame.frameLen++] = 0;
	Info->frame.templete[Info->frame.frameLen++] = 0;
	Info->frame.templete[Info->frame.frameLen++] = 0;
	Info->frame.templete[Info->frame.frameLen++] = 0;
	//pdu
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagPduLen, tagPduLenLen);
	Info->frame.frameLen += tagPduLenLen;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagNumOfASDU, tagNumOfASDULen);
	Info->frame.frameLen += tagNumOfASDULen;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagSeqOfASDU, tagSeqOfASDULen);
	Info->frame.frameLen += tagSeqOfASDULen;
	//asdu
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagASDU, tagASDULen);
	Info->frame.frameLen += tagASDULen;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagSvId, tagSvIdLen);
	Info->frame.frameLen += tagSvIdLen;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], Info->control.smvID, svIdLen);
	Info->frame.frameLen += svIdLen;
	Info->frame.sampCountOffSet = Info->frame.frameLen;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagSampCount, tagSampCountLen);
	Info->frame.frameLen += tagSampCountLen;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagConfigVer, tagConfigVerLen);
	Info->frame.frameLen += tagConfigVerLen;
	Info->frame.syncOffSet = Info->frame.frameLen;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagSync, tagSyncLen);
	Info->frame.frameLen += tagSyncLen;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagSeqOfData, tagSeqOfDataLen);
	Info->frame.frameLen += tagSeqOfDataLen;
	Info->frame.dataSetOffSet = Info->frame.frameLen;
	uint32 len = Info->frame.frameLen + Info->frame.dataSetLen;
	if (len < CN_MaxEhtFrameLen)
	{
		Info->frame.frameLen += Info->frame.dataSetLen;
		Info->frame.frameOk = 1;
	}
	else
	{
		Info->frame.frameOk = 0;
		LogMsg.Stamp() << Info->control.smvID << "LenOverFlow " << len << ">" << CN_MaxEhtFrameLen << "\n";
		outputstatus.frameLenOverFlow = 1;
	}
}

void spt::SptCcdFile::CreatFrameTemplete(GooseGocbInfo* Info)
{
	if (Info->parseErr)
	{
		Info->frame.frameOk = 0;
		return;
	}
	Info->frame.frameLen = 0;
	Info->frame.frameOk = 1;
	//目的MAC
	MemCpy(Info->frame.templete + Info->frame.frameLen, &Info->connect.addr.DstMac, sizeof(Info->connect.addr.DstMac));
	Info->frame.frameLen += sizeof(Info->connect.addr.DstMac);
	uint8 SurMac[6];
	ApiSysEthNetCfg::Instance().EthNet[1].mac.Data(SurMac[0], SurMac[1], SurMac[2], SurMac[3], SurMac[4], SurMac[5]);
	//源MAC
	MemCpy(Info->frame.templete + Info->frame.frameLen, &SurMac, sizeof(Info->connect.addr.DstMac));
	Info->frame.frameLen += sizeof(Info->connect.addr.DstMac);
	Info->frame.templete[Info->frame.frameLen++] = 0x81;
	Info->frame.templete[Info->frame.frameLen++] = 0x00;
	//VLAN
	Info->frame.templete[Info->frame.frameLen++] = (uint8)(Info->connect.addr.Vlan >> 8);
	Info->frame.templete[Info->frame.frameLen++] = (uint8)(Info->connect.addr.Vlan);
	//TYPE
	Info->frame.templete[Info->frame.frameLen++] = 0x88;
	Info->frame.templete[Info->frame.frameLen++] = 0xB8;
	//APPID
	Info->frame.templete[Info->frame.frameLen++] = (uint8)(Info->connect.addr.appId >> 8);
	Info->frame.templete[Info->frame.frameLen++] = (uint8)(Info->connect.addr.appId);
	//data
	uint16 dataSetLen = Info->frame.dataSetLen;
	uint8 tagSeqOfData[4] = { 0xab,0 };
	uint16 tagSeqOfDataLen = 1 + TagChanLenEncode(tagSeqOfData + 1, dataSetLen);
	uint8 tagNumOfData[4] = { 0x8a,0x01,(uint8)Info->dataElementNum };
	uint16 tagNumOfDataLen = 3;

	if (Info->dataElementNum > 256)
	{
		tagNumOfDataLen = 4;
		tagNumOfData[1] = 2;
		tagNumOfData[2] = (uint8)(Info->dataElementNum >> 8);
		tagNumOfData[3] = (uint8)Info->dataElementNum;
	}
	uint8 tagndsCom[3] = { 0x89, 0x01,0x00 };
	uint8 tagndsComLen = 3;
	uint8 tagConfigVer[6] = { 0x88, 0x01 };
	uint8 tagConfigVerLen = 6;
	if (Info->control.confRev > 0xffff)
	{
		tagConfigVerLen = 6;
		tagConfigVer[1] = 4;
		tagConfigVer[2] = (uint8)(Info->control.confRev >> 24);
		tagConfigVer[3] = (uint8)(Info->control.confRev >> 16);
		tagConfigVer[4] = (uint8)(Info->control.confRev >> 8);
		tagConfigVer[5] = (uint8)(Info->control.confRev >> 0);
	}
	else if (Info->control.confRev > 0xff)
	{
		tagConfigVerLen = 4;
		tagConfigVer[1] = 2;
		tagConfigVer[2] = (uint8)(Info->control.confRev >> 8);
		tagConfigVer[3] = (uint8)(Info->control.confRev >> 0);
	}
	else
	{
		tagConfigVerLen = 3;
		tagConfigVer[1] = 1;
		tagConfigVer[2] = (uint8)(Info->control.confRev >> 0);
	}
	//检修
	uint8 tagtest[4] = { 0x87, 0x01,0x00 };
	uint8 tagtestLen = 3;
	uint8 tagstNum[6] = { 0x85,0x04,0x01 };
	uint8 tagstNumLen = 6;
	uint8 tagsqNum[6] = { 0x86,0x04,0x01 };
	uint8 tagsqNumLen = 6;
	uint8 tagtime[10] = { 0x84,0x08,0x0 };
	uint8 tagtimeLen = 10;
	uint8 tagGoId[4] = { 0x83,0x00,0x0 };
	uint8 GoIdLen = StrLen(Info->control.appID);
	uint8 tagGoIdLen = 1 + TagChanLenEncode(tagGoId + 1, GoIdLen);
	uint8 tagDataSet[4] = { 0x82,0x00,0x0 };
	uint8 DataSetLen = StrLen(Info->control.datSetRef);
	uint8 tagDataSetLen = 1 + TagChanLenEncode(tagDataSet + 1, DataSetLen);
	uint8 tagTtl[6] = { 0x81,0x00,0x0 };
	uint8 tagTtlLen = 0;
	Info->control.timetolive = Info->connect.maxTimeMs * 2;
	if (Info->control.timetolive > 0xffff)
	{
		tagTtlLen = 6;
		tagTtl[1] = 4;
		tagTtl[2] = (uint8)(Info->control.timetolive >> 24);
		tagTtl[3] = (uint8)(Info->control.timetolive >> 16);
		tagTtl[4] = (uint8)(Info->control.timetolive >> 8);
		tagTtl[5] = (uint8)(Info->control.timetolive >> 0);
	}
	else if (Info->control.timetolive > 0xff)
	{
		tagTtlLen = 4;
		tagTtl[1] = 2;
		tagTtl[2] = (uint8)(Info->control.timetolive >> 8);
		tagTtl[3] = (uint8)(Info->control.timetolive >> 0);
	}
	else
	{
		tagTtlLen = 3;
		tagTtl[1] = 1;
		tagTtl[2] = (uint8)(Info->control.timetolive >> 0);
	}
	uint8 tagGoCBref[4] = { 0x80,0x00,0x0 };
	uint8 GoCBrefLen = StrLen(Info->control.cbRef);
	uint8 tagGoCBrefLen = 1 + TagChanLenEncode(tagGoCBref + 1, GoCBrefLen);
	//pdu
	uint8 tagPduLen[4] = { 0x61,0x00,0x0 };
	uint16 PduLen = tagGoCBrefLen + GoCBrefLen + tagTtlLen + tagDataSetLen + DataSetLen + tagGoIdLen + GoIdLen + tagtimeLen + tagsqNumLen + tagstNumLen + tagtestLen + tagConfigVerLen + tagndsComLen + tagNumOfDataLen + tagSeqOfDataLen + dataSetLen;
	uint8 tagPduLenLen = 1 + TagChanLenEncode(tagPduLen + 1, PduLen);
	//APPLEN
	uint16 AppLen = PduLen + tagPduLenLen + 8;
	Info->frame.templete[Info->frame.frameLen++] = (uint8)(AppLen >> 8);
	Info->frame.templete[Info->frame.frameLen++] = (uint8)(AppLen);
	//reserved
	Info->frame.templete[Info->frame.frameLen++] = 0;
	Info->frame.templete[Info->frame.frameLen++] = 0;
	Info->frame.templete[Info->frame.frameLen++] = 0;
	Info->frame.templete[Info->frame.frameLen++] = 0;
	//pdu
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagPduLen, tagPduLenLen);
	Info->frame.frameLen += tagPduLenLen;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagGoCBref, tagGoCBrefLen);
	Info->frame.frameLen += tagGoCBrefLen;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], Info->control.cbRef, GoCBrefLen);
	Info->frame.frameLen += GoCBrefLen;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagTtl, tagTtlLen);
	Info->frame.frameLen += tagTtlLen;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagDataSet, tagDataSetLen);
	Info->frame.frameLen += tagDataSetLen;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], Info->control.datSetRef, DataSetLen);
	Info->frame.frameLen += DataSetLen;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagGoId, tagGoIdLen);
	Info->frame.frameLen += tagGoIdLen;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], Info->control.appID, GoIdLen);
	Info->frame.frameLen += GoIdLen;
	Info->frame.utcOffSet = Info->frame.frameLen + 2;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagtime, tagtimeLen);
	Info->frame.frameLen += tagtimeLen;
	Info->frame.stOffSet = Info->frame.frameLen + 2;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagstNum, tagstNumLen);
	Info->frame.frameLen += tagstNumLen;
	Info->frame.sqOffSet = Info->frame.frameLen + 2;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagsqNum, tagsqNumLen);
	Info->frame.frameLen += tagsqNumLen;
	Info->frame.testOffSet = Info->frame.frameLen + 2;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagtest, tagtestLen);
	Info->frame.frameLen += tagtestLen;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagConfigVer, tagConfigVerLen);
	Info->frame.frameLen += tagConfigVerLen;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagndsCom, tagndsComLen);
	Info->frame.frameLen += tagndsComLen;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagNumOfData, tagNumOfDataLen);
	Info->frame.frameLen += tagNumOfDataLen;
	MemCpy(&Info->frame.templete[Info->frame.frameLen], tagSeqOfData, tagSeqOfDataLen);
	Info->frame.frameLen += tagSeqOfDataLen;
	Info->frame.dataSetOffSet = Info->frame.frameLen;
	uint8* buf = &Info->frame.templete[Info->frame.frameLen];

	uint32 len = Info->frame.frameLen + dataSetLen;
	if (len < CN_MaxEhtFrameLen)
	{
		for (uint32 i = 0; i < Info->dataElementNum; i++)
		{
			EncodeGoSvDataTypeInfo(buf + Info->frame.dataSetTagOffSet[i], Info->dataType[i]);
		}
		Info->frame.frameLen += dataSetLen;
		Info->frame.frameOk = 1;
	}
	else
	{
		Info->frame.frameOk = 0;
		LogMsg.Stamp() << Info->control.appID << "LenOverFlow " << len << ">" << CN_MaxEhtFrameLen << "\n";
		outputstatus.frameLenOverFlow = 1;
	}
}

int32 spt::SptCcdFile::TagChanLenEncode(uint8* pLen, uint16 Len)
{
	if (Len > 256)
	{
		pLen[0] = 0x82;
		pLen[1] = (uint8)(Len >> 8);
		pLen[2] = (uint8)(Len >> 0);
		return 3;
	}
	else if (Len > 127)
	{
		pLen[0] = 0x81;
		pLen[1] = (uint8)(Len >> 0);
		return 2;
	}
	else
	{
		pLen[0] = (uint8)(Len >> 0);
		return 1;
	}
	return 0;
}

int32 spt::SptCcdFile::ParseSVPubCbDataSet(const tinyxml2::XMLElement* node, SVcbInfo* Info)
{
	if (StrCmp(node->Name(), "DataSet") != 0)
	{
		LogErr.Stamp() << "ParseSVPubCbDataSet Name err. ccd parse line" << __LINE__ << "\n";
		Info->parseErr = 1;
		return -1;
	}
	const XMLElement* element = node->FirstChildElement();
	const XMLAttribute* att;
	uint16 num = Info->dataElementNum = 0;
	bool8 ok = 0;

	InstObjectRoot& root = InstObjectRoot::Instance();
	InstObjectGroupParent* groupP = root.GetGroupParent(EIOT_HalIo);
	while (element)
	{
		if ((StrCmp(element->Name(), "FCDA") == 0) && (num < M_ArrLen(Info->dataInstId)))
		{
			const XMLElement* DOI;
			Info->dataLinkedNum[num] = 0;
			Info->dataGroupId[num][0] = 0xffff;
			Info->dataInstId[num][0] = 0xffff;
			DOI = element->FirstChildElement("DOI");
			if (DOI)
			{
				const XMLElement* SDI;
				SDI = DOI->FirstChildElement("SDI");
				if (SDI)
				{
					const XMLElement* DAI;
					DAI = SDI->FirstChildElement("DAI");
					if (DAI)
					{
						att = DAI->FindAttribute("sAddr");
						if (att)
						{
							ok = 1;
						}
					}
				}
			}

			if (ok)
			{
				if (num == 0)
				{
					Info->dataInstId[0][0] = 0xffff;
					Info->dataLinkedNum[num] = 1;
				}
				else
				{
					InstObject* obj;
					obj = groupP->GetObject(att->Value());
					if (obj && (obj->InstObjectType() == EIOT_HalIo))
					{
						HalIoCell* cell = (HalIoCell*)obj;
						if ((cell->IoType() == cell->E_9_2_Ang_Out)
							)
						{
							Info->dataGroupId[num][0] = cell->GroupId();
							Info->dataInstId[num][0] = (uint8)cell->InstId();
							Info->dataLinkedNum[num] = 1;
						}
						else
						{
							Info->dataGroupId[num][0] = 0xffff;
							Info->dataInstId[num][0] = 0xffff;
							LogErr.Stamp() << "VirNode " << att->Value() << " Type Err\n";;
							Info->sAddrErr = 1;
							Info->parseErr = 1;
							break;
						}
					}
					else
					{
						Info->dataGroupId[num][0] = 0xffff;
						Info->dataInstId[num][0] = 0xffff;
						LogErr.Stamp() << "VirNode " << att->Value() << " Not Found\n";;
						Info->sAddrErr = 1;
					}
				}
				num++;
			}
			else
			{
				num = 0;
				Info->parseErr = 1;
				break;
			}
			ok = 0;
		}
		element = element->NextSiblingElement();
	}
	Info->dataElementNum = num;
	return 0;
}

int32 spt::SptCcdFile::ParseSVSubCbDataSet(const tinyxml2::XMLElement* node, SVcbInfo* Info)
{
	if (StrCmp(node->Name(), "DataSet") != 0)
	{
		LogErr.Stamp() << "ParseSVPubCbDataSet Name err. ccd parse line" << __LINE__ << "\n";
		Info->parseErr = 1;
		return -1;
	}
	const XMLElement* element = node->FirstChildElement();
	const XMLAttribute* att;
	uint16 num = Info->dataElementNum = 0;
	uint16 sub = Info->dataElementSub = 0;

	InstObjectRoot& root = InstObjectRoot::Instance();
	InstObjectGroupParent* groupP = root.GetGroupParent(EIOT_HalIo);
	Info->connect.PortEnableNum = 0;
	while (element)
	{
		if ((StrCmp(element->Name(), "FCDA") == 0) && (num < M_ArrLen(Info->dataInstId)))
		{
			const XMLElement* intAddr;
			Info->dataLinkedNum[num] = 0;
			Info->dataGroupId[num][0] = 0xffff;
			Info->dataInstId[num][0] = 0xffff;
			intAddr = element->FirstChildElement("intAddr");
			if (intAddr)
			{
				while (intAddr && (StrCmp(intAddr->Name(), "intAddr") == 0))
				{
					if (Info->dataLinkedNum[num] >= CN_OneSVLinkMax)
					{
						Info->parseErr = 1;
						LogErr << "ParseSVSubCbDataSet intAddr too many. \n";
						break;
					}
					const char* name = intAddr->Attribute("name");
					if (name)
					{
						if (StrCmp(name, "NULL") != 0)
						{
							TransString ts;
							ts.SetBuf(name);
							uint8 Card = 0;
							uint8 Port = 0;
							if ((name[0]) >= 'A' && (name[0] <= 'Z'))
							{
								String100B str;
								ts.Get(str, '-');
								Card = str.Str()[0] - 'A';
							}
							else if ((name[0]) >= 'a' && (name[0] <= 'a'))
							{
								String100B str;
								ts.Get(str, '-');
								Card = str.Str()[0] - 'a';
							}
							else if ((name[0]) >= '1' && (name[0] <= '9'))
							{
								uint32 card = 0;
								String100B str;
								ts.Get(card, '-');
								Card = (uint8)card;
							}
							uint32 port = 0;
							ts.Get(port, ':');
							Port = (uint8)port;
							uint16 PortCfg = (((uint16)Card) << 8) | Port;

							bool8 linked = 0;
							for (uint32 i = 0; i < Info->connect.PortEnableNum; i++)
							{
								if (PortCfg == Info->connect.Card_Port[i])
								{
									linked = 1;
									break;
								}
							}
							if (!linked)
							{
								if (Info->connect.PortEnableNum < M_ArrLen(Info->connect.PortEnable))
								{
									Info->connect.PortEnable[Info->connect.PortEnableNum] = 1;
									Info->connect.Card_Port[Info->connect.PortEnableNum] = (((uint16)Card) << 8) | Port;
									Info->connect.PortEnableNum++;
								}
							}
							const XMLElement* DOI = intAddr->FirstChildElement("DOI");
							if (DOI)
							{
								const XMLElement* SDI;
								SDI = DOI->FirstChildElement("SDI");
								if (SDI)
								{
									const XMLElement* DAI;
									DAI = SDI->FirstChildElement("DAI");
									if (DAI)
									{
										att = DAI->FindAttribute("sAddr");
										if (att)
										{
											InstObject* obj;
											obj = groupP->GetObject(att->Value());
											if (obj && (obj->InstObjectType() == EIOT_HalIo))
											{
												SptSampAng_9_2SampCell* cell = (SptSampAng_9_2SampCell*)obj;
												if ((cell->IoType() == cell->E_Normal_Ang)
													|| (cell->IoType() == cell->E_9_2_Ang_In)
													|| (cell->IoType() == cell->E_Local_9_2_Ang_In)
													)
												{
													if (Info->dataLinkedNum[num] < CN_OneSVLinkMax)
													{
														Info->dataInstId[num][Info->dataLinkedNum[num]] = (uint8)cell->InstId();
														Info->dataGroupId[num][Info->dataLinkedNum[num]] = (uint8)cell->GroupId();
														Info->dataCardPort[num][Info->dataLinkedNum[num]] = PortCfg;
														Info->dataLinkedNum[num]++;
														sub++;
													}
												}
												else
												{
													Info->dataGroupId[num][0] = 0xffff;
													Info->dataInstId[num][0] = 0xffff;
													LogErr.Stamp() << "VirNode " << att->Value() << " Type Err\n";;
													Info->sAddrErr = 1;
													Info->parseErr = 1;
													break;
												}
											}
											else
											{
												LogErr.Stamp() << "VirNode " << att->Value() << " Not Found\n";;
												Info->sAddrErr = 1;
											}
										}
									}
								}
							}
						}
					}
					intAddr = intAddr->NextSiblingElement();
				}
			}
			num++;
		}
		element = element->NextSiblingElement();
	}
	Info->dataElementNum = num;
	Info->dataElementSub = sub;
	return 0;
}
int32 spt::SptCcdFile::ParseSVPubCbControl(const tinyxml2::XMLElement* node, SVcbInfo* Info)
{
	if (StrCmp(node->Name(), "SampledValueControl") != 0)
	{
		LogErr.Stamp() << "ParseSVPubCbControl Name err. ccd parse line" << __LINE__ << "\n";
		outputstatus.svPubParseErr = 1;
		Info->parseErr = 1;
		return -1;
	}
	if (!node->FindAttribute("confRev"))
	{
		Info->parseErr = 1;
		outputstatus.attLost = 1;
		LogErr.Stamp() << " FindAttribute(\"confRev\")" << __LINE__;
	}
	if (!node->FindAttribute("datSet"))
	{
		Info->parseErr = 1;
		outputstatus.attLost = 1;
		LogErr.Stamp() << " FindAttribute(\"datSet\")" << __LINE__;
	}
	Info->control.confRev = node->UnsignedAttribute("confRev");
	Info->control.nofASDU = node->UnsignedAttribute("nofASDU");
	Info->control.smpRate = node->UnsignedAttribute("smpRate");
	const char* sur = node->Attribute("datSet");
	String200B str;
	str = Info->control.cbRef;
	if (str.IsInclude("$") >= 0)
	{
		str.Replace('$', 0);
		str << '$';
	}
	else if (str.IsInclude(".") >= 0)
	{
		str.Replace('.', 0);
		str << '.';
	}
	else
	{
		Info->parseErr = 1;
		LogErr.Stamp() << "ParseSVPubCbControl Name format is not standard.\n";
	}
	str << sur;
	StrNCpy(Info->control.datSet, sur, sizeof(Info->control.datSet));
	Info->control.datSetLen = StrLen(sur);

	StrNCpy(Info->control.datSetRef, str.Str(), sizeof(Info->control.datSet));
	Info->control.datSetRefLen = StrLen(str.Str());
	sur = node->Attribute("name");
	StrNCpy(Info->control.name, sur, sizeof(Info->control.name));
	Info->control.nameLen = StrLen(sur);
	if (!node->FindAttribute("smvID"))
	{
		Info->parseErr = 1;
		outputstatus.attLost = 1;
		LogErr.Stamp() << " FindAttribute(\"smvID\")" << __LINE__;
	}
	sur = node->Attribute("smvID");
	StrNCpy(Info->control.smvID, sur, sizeof(Info->control.smvID));
	Info->control.smvIDLen = StrLen(sur);
	const XMLElement* element = node->FirstChildElement("SmvOpts");
	if (!element)
	{
		LogErr.Stamp() << "ParseSVPubCbControl Name err. ccd parse line" << __LINE__ << "\n";
		outputstatus.svPubParseErr = 1;
		Info->parseErr = 1;
		return -1;
	}
	Info->control.SmvOpts_refreshTime = node->BoolAttribute("refreshTime");
	Info->control.SmvOpts_sampleRate = node->BoolAttribute("sampleRate");
	Info->control.SmvOpts_sampleSynchronized = node->BoolAttribute("sampleSynchronized");
	Info->control.SmvOpts_security = node->BoolAttribute("security");
	return 0;
}

int32 spt::SptCcdFile::ParseSVSubCbControl(const tinyxml2::XMLElement* node, SVcbInfo* Info)
{
	if (StrCmp(node->Name(), "SampledValueControl") != 0)
	{
		LogErr.Stamp() << "ParseSVSubCbControl Name err. ccd parse line" << __LINE__ << "\n";
		outputstatus.svSubParseErr = 1;
		Info->parseErr = 1;
		return -1;
	}
	if (!node->FindAttribute("confRev"))
	{
		Info->parseErr = 1;
		outputstatus.attLost = 1;
		LogErr.Stamp() << " FindAttribute(\"confRev\")" << __LINE__;
	}
	if (!node->FindAttribute("datSet"))
	{
		Info->parseErr = 1;
		outputstatus.attLost = 1;
		LogErr.Stamp() << " FindAttribute(\"datSet\")" << __LINE__;
	}
	Info->control.confRev = node->UnsignedAttribute("confRev");
	Info->control.nofASDU = node->UnsignedAttribute("nofASDU");
	Info->control.smpRate = node->UnsignedAttribute("smpRate");
	const char* sur = node->Attribute("datSet");
	String200B str;
	str = Info->control.cbRef;
	if (str.IsInclude("$") >= 0)
	{
		str.Replace('$', 0);
		str << '$';
	}
	else if (str.IsInclude(".") >= 0)
	{
		str.Replace('.', 0);
		str << '.';
	}
	else
	{
		Info->parseErr = 1;
		LogErr.Stamp() << "ParseSVSubCbControl Name format is not standard.\n";
	}
	str << sur;
	StrNCpy(Info->control.datSet, sur, sizeof(Info->control.datSet));
	Info->control.datSetLen = StrLen(sur);

	StrNCpy(Info->control.datSetRef, str.Str(), sizeof(Info->control.datSet));
	Info->control.datSetRefLen = StrLen(str.Str());
	sur = node->Attribute("name");
	StrNCpy(Info->control.name, sur, sizeof(Info->control.name));
	Info->control.nameLen = StrLen(sur);
	if (!node->FindAttribute("smvID"))
	{
		Info->parseErr = 1;
		outputstatus.attLost = 1;
		LogErr.Stamp() << " FindAttribute(\"smvID\")" << __LINE__;
	}
	sur = node->Attribute("smvID");
	StrNCpy(Info->control.smvID, sur, sizeof(Info->control.smvID));
	Info->control.smvIDLen = StrLen(sur);
	const XMLElement* element = node->FirstChildElement("SmvOpts");
	if (!element)
	{
		LogErr.Stamp() << "ParseSVSubCbControl Name err. ccd parse line" << __LINE__ << "\n";
		outputstatus.svSubParseErr = 1;
		Info->parseErr = 1;
		return -1;
	}
	Info->control.SmvOpts_refreshTime = node->BoolAttribute("refreshTime");
	Info->control.SmvOpts_sampleRate = node->BoolAttribute("sampleRate");
	Info->control.SmvOpts_sampleSynchronized = node->BoolAttribute("sampleSynchronized");
	Info->control.SmvOpts_security = node->BoolAttribute("security");
	return 0;
}

int32 spt::SptCcdFile::ParseSVPubConnectedAP(const tinyxml2::XMLElement* node, SVcbInfo* Info)
{
	if (StrCmp(node->Name(), "ConnectedAP") != 0)
	{
		LogErr.Stamp() << "ParseSVConnectedAP Name err. ccd parse line" << __LINE__ << "\n";
		Info->parseErr = 1;
		return -1;
	}
	const char* sur = node->Attribute("apName");
	StrNCpy(Info->connect.apName, sur, sizeof(Info->connect.apName));
	Info->connect.apNameLen = StrLen(sur);
	sur = node->Attribute("iedName");
	StrNCpy(Info->connect.iedName, sur, sizeof(Info->connect.iedName));
	Info->connect.iedNameLen = StrLen(sur);
	const XMLElement* element = node->FirstChildElement();
	Info->connect.PortEnableNum = 0;
	while (element)
	{
		if (StrCmp(element->Name(), "SMV") == 0)
		{
			const XMLElement* Address;
			Address = element->FirstChildElement("Address");
			if (Address)
			{
				ParseAddress(Address, &Info->connect.addr);
				if (Info->connect.addr.parseErr)
				{
					Info->parseErr = 1;
					element = element->NextSiblingElement();
					continue;
				}
				if ((Info->connect.addr.DstMac[0] != 0x01)
					|| (Info->connect.addr.DstMac[1] != 0x0C)
					|| (Info->connect.addr.DstMac[2] != 0xCD)
					|| (Info->connect.addr.DstMac[3] != 0x04)
					)

				{
					Info->parseErr = 1;
					outputstatus.attErr = 1;
					LogErr.Stamp() << "ParseSVConnectedAP DstMac err. ccd parse line" << __LINE__ << "\n";
				}
				if (((Info->connect.addr.appId) < (0x4000)) || ((Info->connect.addr.appId) > (0x7fff)))
				{
					Info->parseErr = 1;
					outputstatus.attErr = 1;
					LogErr.Stamp() << "ParseSVConnectedAP svPubParseErr err. ccd parse line" << __LINE__ << "\n";
				}
				if (Info->connect.addr.Vlan_Id >= (4096))
				{
					Info->parseErr = 1;
					outputstatus.attErr = 1;
					LogErr.Stamp() << "ParseSVConnectedAP Vlan_Id err. ccd parse line" << __LINE__ << "\n";
				}
				if (Info->connect.addr.Vlan_PRIORITY > (7))
				{
					Info->parseErr = 1;
					outputstatus.attErr = 1;
					LogErr.Stamp() << "ParseSVConnectedAP Vlan_PRIORITY err. ccd parse line" << __LINE__ << "\n";
				}
			}
			else
			{
				Info->parseErr = 1;
				outputstatus.attLost = 1;
				LogErr.Stamp() << " ParseSVPubConnectedAP FindAttribute(\"Address\")";
			}
		}
		else if (StrCmp(element->Name(), "PhysConn") == 0)
		{
			const XMLElement* type = element->FirstChildElement();
			while (type)
			{
				if (StrCmp(type->Attribute("type"), "Port") == 0)
				{
					if (Info->connect.PortEnableNum >= M_ArrLen(Info->connect.PortEnable))
					{
						break;
					}
					const XMLNode* child = type->FirstChild();
					if (child)
					{
						const XMLText* info = child->ToText();
						const uint8* sur = (const uint8*)info->Value();
						uint16 Card = sur[0];
						Info->connect.PortEnable[Info->connect.PortEnableNum] = 1;
						if ((sur[0]) >= 'A' && (sur[0] <= 'Z'))
						{
							Card -= 'A';
						}
						else if ((sur[0]) >= 'a' && (sur[0] <= 'a'))
						{
							Card -= 'a';
						}
						else if ((sur[0]) >= '1' && (sur[0] <= '9'))
						{
							TransString ts;
							ts.SetBuf((const char*)sur);
							uint32 card = 0;
							ts.Get(card, '-');
							Card = card;
						}
						else
						{
							LogErr.Stamp() << "ParseSVConnectedAP Port err. ccd parse line" << __LINE__ << "\n";
							Info->parseErr = 1;
							Info->connect.PortEnable[Info->connect.PortEnableNum] = 0;
						}
						TransString ts;
						ts.SetBuf((const char*)sur + 2);
						uint32 port = 0;
						ts.Get(port, 0);
						Info->connect.Card_Port[Info->connect.PortEnableNum] = (Card << 8) + (port & 0x3f);
						Info->connect.PortEnableNum++;
					}
				}
				type = type->NextSiblingElement();
			}
		}
		element = element->NextSiblingElement();
	}
	return 0;
}

int32 spt::SptCcdFile::ParseSVSubConnectedAP(const tinyxml2::XMLElement* node, SVcbInfo* Info)
{
	if (StrCmp(node->Name(), "ConnectedAP") != 0)
	{
		LogErr.Stamp() << "ParseSVSubConnectedAP Name err. ccd parse line" << __LINE__ << "\n";
		Info->parseErr = 1;
		return -1;
	}
	const char* sur = node->Attribute("apName");
	StrNCpy(Info->connect.apName, sur, sizeof(Info->connect.apName));
	Info->connect.apNameLen = StrLen(sur);
	sur = node->Attribute("iedName");
	StrNCpy(Info->connect.iedName, sur, sizeof(Info->connect.iedName));
	Info->connect.iedNameLen = StrLen(sur);
	const XMLElement* element = node->FirstChildElement();
	Info->connect.PortEnableNum = 0;
	while (element)
	{
		if (StrCmp(element->Name(), "SMV") == 0)
		{
			const XMLElement* Address;
			Address = element->FirstChildElement("Address");
			if (Address)
			{
				ParseAddress(Address, &Info->connect.addr);
				if (Info->connect.addr.parseErr)
				{
					Info->parseErr = 1;
					element = element->NextSiblingElement();
					continue;
				}
				if ((Info->connect.addr.DstMac[0] != 0x01)
					|| (Info->connect.addr.DstMac[1] != 0x0C)
					|| (Info->connect.addr.DstMac[2] != 0xCD)
					|| (Info->connect.addr.DstMac[3] != 0x04)
					)

				{
					outputstatus.attErr = 1;
					Info->parseErr = 1;
					LogErr.Stamp() << "ParseSVSubConnectedAP DstMac err. ccd parse line" << __LINE__ << "\n";
				}
				if (((Info->connect.addr.appId) < (0x4000)) || ((Info->connect.addr.appId) > (0x7fff)))
				{
					Info->parseErr = 1;
					outputstatus.attErr = 1;
					LogErr.Stamp() << "ParseSVSubConnectedAP svSubParseErr err. ccd parse line" << __LINE__ << "\n";
				}
				if (Info->connect.addr.Vlan_Id >= (4096))
				{
					Info->parseErr = 1;
					outputstatus.attErr = 1;
					LogErr.Stamp() << "ParseSVConnectedAP Vlan_Id err. ccd parse line" << __LINE__ << "\n";
				}
				if (Info->connect.addr.Vlan_PRIORITY > (7))
				{
					Info->parseErr = 1;
					outputstatus.attErr = 1;
					LogErr.Stamp() << "ParseSVSubConnectedAP Vlan_PRIORITY err. ccd parse line" << __LINE__ << "\n";
				}
			}
			else
			{
				Info->parseErr = 1;
				outputstatus.attLost = 1;
				LogErr.Stamp() << " ParseSVSubConnectedAP FindAttribute(\"Address\")";
			}
		}
		element = element->NextSiblingElement();
	}
	return 0;
}

int32 spt::SptCcdFile::ParseAddress(const tinyxml2::XMLElement* node, GoSvAddressInfo* Info)
{
	if (StrCmp(node->Name(), "Address") != 0)
	{
		LogErr.Stamp() << "ParseAddress Name err. ccd parse line" << __LINE__ << "\n";
		Info->parseErr = 1;
		outputstatus.attLost = 1;
		return -1;
	}
	const XMLElement* element = node->FirstChildElement();
	bool8 maclost = 1;
	bool8 appidlost = 1;
	bool8 vlanplost = 1;
	bool8 vlanidlost = 1;
	while (element)
	{
		if (StrCmp(element->Attribute("type"), "MAC-Address") == 0)
		{
			const XMLNode* child = element->FirstChild();
			if (child)
			{
				const XMLText* info = child->ToText();
				const uint8* sur = (const uint8*)info->Value();
				if (StrLen((const char*)sur) == 17)
				{
					TransString ts;
					ts.SetBuf((const char*)sur);

					Info->DstMac[0] = (uint8)ts.GetHex('-', 2);
					Info->DstMac[1] = (uint8)ts.GetHex('-', 2);
					Info->DstMac[2] = (uint8)ts.GetHex('-', 2);
					Info->DstMac[3] = (uint8)ts.GetHex('-', 2);
					Info->DstMac[4] = (uint8)ts.GetHex('-', 2);
					Info->DstMac[5] = (uint8)ts.GetHex('-', 2);
					maclost = 0;
				}
				else
				{
					Info->DstMac[0] = 0x01;
					Info->DstMac[1] = 0x0C;
					Info->DstMac[2] = 0xCD;
					Info->DstMac[3] = 0x04;
					Info->DstMac[4] = 0x00;
					Info->DstMac[5] = 0x01;
					Info->parseErr = 1;
				}
			}
		}
		else if (StrCmp(element->Attribute("type"), "APPID") == 0)
		{
			const XMLNode* child = element->FirstChild();
			if (child)
			{
				const XMLText* info = child->ToText();
				const uint8* sur = (const uint8*)info->Value();
				if (StrLen((const char*)sur) > 0)
				{
					TransString ts;
					ts.SetBuf((const char*)sur);
					Info->appId = (uint16)ts.GetHex('-', 4);
					appidlost = 0;
				}
				else
				{
					Info->appId = 0;
				}
			}
		}
		else if (StrCmp(element->Attribute("type"), "VLAN-PRIORITY") == 0)
		{
			const XMLNode* child = element->FirstChild();
			if (child)
			{
				const XMLText* info = child->ToText();
				const uint8* sur = (const uint8*)info->Value();
				if (StrLen((const char*)sur) > 0)
				{
					TransString ts;
					ts.SetBuf((const char*)sur);
					Info->Vlan_PRIORITY = (uint8)ts.GetHex('-', 4);
					vlanplost = 0;
				}
				else
				{
					Info->Vlan_PRIORITY = 0;
				}
			}
		}
		else if (StrCmp(element->Attribute("type"), "VLAN-ID") == 0)
		{
			const XMLNode* child = element->FirstChild();
			if (child)
			{
				const	XMLText* info = child->ToText();
				const uint8* sur = (const uint8*)info->Value();
				if (StrLen((const char*)sur) > 0)
				{
					TransString ts;
					ts.SetBuf((const char*)sur);
					Info->Vlan_Id = (uint16)ts.GetHex('-', 4);
					vlanidlost = 0;
				}
				else
				{
					Info->Vlan_Id = 0;
				}
			}
		}
		element = element->NextSiblingElement();
	}
	Info->Vlan = Info->Vlan_PRIORITY & 0x07;
	Info->Vlan = (Info->Vlan << 13) | (Info->Vlan_Id & 0x0fff);
	if (maclost || appidlost || vlanplost || vlanidlost)
	{
		LogErr.Stamp() << "ParseAddress ccd parse line" << __LINE__ << "\n";
		Info->parseErr = 1;
		outputstatus.attLost = 1;
	}
	return 0;
}
/*==============================================================================
 * 函数功能: 提取计算二次回路文件CRC的纯净字节流（去除desc、空格、换行符、回车符、列表符）
 * 输入参数: 目的指针
 *           源指针
 *           文件中CRC字段指针
 * 输出参数: 目的字节流\CRC id
 * 返回值:   字节流长度
 *============================================================================*/
static unsigned int Parse_ByteStreamExtract(char* pDestBuf, char* pSrcBuf, char* pCrcid)
{
	static int g_uiFlag = 0;   //删选ccd文件中的:和" "使用
	char* pTemp = NULL;
	char         c;
	int          i = 0;
	int          flag = 0;
	char* pTemp2 = NULL;                              // 考虑保留元素中的空格符号，增加指针变量。
	unsigned int len = 0;
	pTemp = pSrcBuf;

	//用pTemp指向pSrcBuf的第一个字符，后面靠pTemp+1后移
	// 目的字节流跳过CRC, pCrcid缓存
	if ((pTemp = (char*)StrStr(pSrcBuf, "<CRC id=\"")) != NULL)      // \"代表双引号
	{
		MemCpy(pCrcid, pTemp + 9, 8);                     //将后面的8个字符拷贝到pCrcid中 <CRC id=",是9个字符
		pCrcid[8] = '\0';                                 //0-7存crc，8存截止符
		return 0;
	}

	pTemp = pSrcBuf;

	if ((pTemp = (char*)StrStr(pTemp, " configVersion=")) != NULL)      //清除头configVersion
	{
		while ((*pTemp != '"') && (*pTemp != '\0'))
		{
			*pTemp = ' ';
			pTemp++;
		}

		*pTemp = ' ';

		while ((*pTemp != '"') && (*pTemp != '\0'))
		{
			*pTemp = ' ';
			pTemp++;
		}

		*pTemp = ' ';
	}

	//删除所有的desc
	pTemp = pSrcBuf;

	if ((pTemp = (char*)StrStr(pTemp, " desc=\"")) != NULL)
	{
		while ((*pTemp != '"') && (*pTemp != '\0'))
		{
			*pTemp = ' ';
			pTemp++;
		}

		*pTemp = ' ';

		while ((*pTemp != '"') && (*pTemp != '\0'))
		{
			*pTemp = ' ';
			pTemp++;
		}

		*pTemp = ' ';
	}

	pTemp = pSrcBuf;

	if ((pTemp = (char*)StrStr(pTemp, " manufacturer=\"")) != NULL)
	{
		if ((pTemp2 = (char*)StrStr(pTemp, " type=\"")) != NULL)
		{
			while ((*pTemp2 != '"') && (*pTemp != '\0'))
			{
				*pTemp2 = ' ';
				pTemp2++;
			}

			*pTemp2 = ' ';

			while ((*pTemp2 != '"') && (*pTemp != '\0'))
			{
				*pTemp2 = ' ';
				pTemp2++;
			}

			*pTemp2 = ' ';
		}

		while ((*pTemp != '"') && (*pTemp != '\0'))
		{
			*pTemp = ' ';
			pTemp++;
		}

		*pTemp = ' ';

		while ((*pTemp != '"') && (*pTemp != '\0'))
		{
			*pTemp = ' ';
			pTemp++;
		}

		*pTemp = ' ';
	}


	pTemp = pSrcBuf;

	if ((pTemp = (char*)StrStr(pTemp, "<GOOSEPUB>")) != NULL)
	{
		g_uiFlag = 0;
	}

	pTemp = pSrcBuf;

	if ((pTemp = (char*)StrStr(pTemp, "<GOOSESUB>")) != NULL)
	{
		g_uiFlag = 1;
	}

	pTemp = pSrcBuf;

	if ((pTemp = (char*)StrStr(pTemp, "<SVPUB>")) != NULL)
	{
		g_uiFlag = 0;
	}

	pTemp = pSrcBuf;

	if ((pTemp = (char*)StrStr(pTemp, "<SVSUB>")) != NULL)
	{
		g_uiFlag = 1;
	}

	flag = g_uiFlag;

	pTemp = pSrcBuf;

	if (((pTemp = (char*)StrStr(pTemp, "daName=\"")) != NULL) && flag)
	{
		while ((*pTemp != '"') && (*pTemp != '\0'))
		{
			*pTemp = ' ';
			pTemp++;
		}

		*pTemp = ' ';

		while ((*pTemp != '"') && (*pTemp != '\0'))
		{
			*pTemp = ' ';
			pTemp++;
		}

		*pTemp = ' ';
	}

	pTemp = pSrcBuf;

	if (((pTemp = (char*)StrStr(pTemp, "doName=\"")) != NULL) && flag)
	{
		while ((*pTemp != '"') && (*pTemp != '\0'))
		{
			*pTemp = ' ';
			pTemp++;
		}

		*pTemp = ' ';

		while ((*pTemp != '"') && (*pTemp != '\0'))
		{
			*pTemp = ' ';
			pTemp++;
		}

		*pTemp = ' ';
	}

	pTemp = pSrcBuf;

	if (((pTemp = (char*)StrStr(pTemp, " fc=\"")) != NULL) && flag)
	{
		while ((*pTemp != '"') && (*pTemp != '\0'))
		{
			*pTemp = ' ';
			pTemp++;
		}

		*pTemp = ' ';

		while ((*pTemp != '"') && (*pTemp != '\0'))
		{
			*pTemp = ' ';
			pTemp++;
		}

		*pTemp = ' ';
	}

	pTemp = pSrcBuf;

	if (((pTemp2 = (char*)StrStr(pTemp, "<GSE ")) == NULL) && ((pTemp2 = (char*)StrStr(pTemp, "<SMV ")) == NULL))
	{
		if (((pTemp = (char*)StrStr(pTemp, "ldInst=\"")) != NULL) && flag)
		{
			while ((*pTemp != '"') && (*pTemp != '\0'))
			{
				*pTemp = ' ';
				pTemp++;
			}

			*pTemp = ' ';

			while ((*pTemp != '"') && (*pTemp != '\0'))
			{
				*pTemp = ' ';
				pTemp++;
			}

			*pTemp = ' ';
		}
	}

	pTemp = pSrcBuf;

	if (((pTemp = (char*)StrStr(pTemp, "lnClass=\"")) != NULL) && flag)
	{
		while ((*pTemp != '"') && (*pTemp != '\0'))
		{
			*pTemp = ' ';
			pTemp++;
		}

		*pTemp = ' ';

		while ((*pTemp != '"') && (*pTemp != '\0'))
		{
			*pTemp = ' ';
			pTemp++;
		}

		*pTemp = ' ';
	}

	pTemp = pSrcBuf;

	if (((pTemp = (char*)StrStr(pTemp, "lnInst=\"")) != NULL) && flag)
	{
		while ((*pTemp != '"') && (*pTemp != '\0'))
		{
			*pTemp = ' ';
			pTemp++;
		}

		*pTemp = ' ';

		while ((*pTemp != '"') && (*pTemp != '\0'))
		{
			*pTemp = ' ';
			pTemp++;
		}

		*pTemp = ' ';
	}

	pTemp = pSrcBuf;

	if (((pTemp = (char*)StrStr(pTemp, "prefix=\"")) != NULL) && flag)
	{
		while ((*pTemp != '"') && (*pTemp != '\0'))
		{
			*pTemp = ' ';
			pTemp++;
		}

		*pTemp = ' ';

		while ((*pTemp != '"') && (*pTemp != '\0'))
		{
			*pTemp = ' ';
			pTemp++;
		}

		*pTemp = ' ';
	}

	//后面记录有效字符
	while ((c = *pSrcBuf++) != '\0')
	{
		pTemp2 = pSrcBuf;

		//        printf( "%c", c );//直接打印没有过滤的c
		if ((c == '=') && ((*(++pTemp2)) == '"'))
		{
			i = 1;
		}

		pTemp2 = pSrcBuf;

		if ((c == 'V') && ((*pTemp2) == 'a') && ((*(++pTemp2)) == 'l') && ((*(++pTemp2)) == '>'))
		{
			i = 1;
		}

		if (i == 1)
		{
			if (c != 9 && c != 10 && c != 13)  // 跳过换行符、回车符、列表符
			{
				*pDestBuf = c;

				len++;
				pDestBuf++;

				pTemp2 = pSrcBuf;

				if ((*pTemp2 == '"') || ((*(++pTemp2)) == '<'))
				{
					i = 0;
				}
			}
		}
		else
		{
			if (c != 9 && c != 10 && c != 13 && c != 32)
				// 跳过空格、换行符、回车符、列表符
			{
				*pDestBuf = c;

				len++;
				pDestBuf++;
			}
		}
	}

	return len; //字符数量s
}
bool8 spt::SptCcdFile::CalCcdCrc()
{
	char         Crcid[9];
	char* pDataBuf = 0;
	char         Buf[1024];
	unsigned int bytewrite;
	uint32        dwFileCalCRC = 0;
	SalFile file;
	file.Path().Set(CN_T860_CFG_FILE_ROOT);
	file.Name().Set("configured.ccd");
	if (file.IsExist() == 0)
	{
		outputstatus.fileNoExist = 1;
		return 0;
	}
	// allocate a buffer and read all into memory
	pDataBuf = (char*)Calloc(1, file.Size() + 1);

	if (0 == pDataBuf)
	{
		outputstatus.parseErr = 1;
		return 0;
	}
	file.OpenReadOnly();
	// 获取pro并跳过特殊字符
	bytewrite = 0;
	MemSet(Buf, 0, sizeof(Buf));
	while (file.ReadLine(Buf, sizeof(Buf)) >= 0)    //一次读一行，读不到时，返回NULL (会读入前面的空格)
	{
		bytewrite += Parse_ByteStreamExtract(pDataBuf + bytewrite, Buf, Crcid);
		MemSet(Buf, 0, sizeof(Buf));
	} //bytewrite是字符总数目

	*(pDataBuf + bytewrite) = 0;
	dwFileCalCRC = StdCrc32Check.CalCrc(pDataBuf, bytewrite);
	Free(pDataBuf);
	// 文件内部CRC值
	outputstatus.fileCrc = 0;
	TransString ts;
	ts.SetBuf(Crcid);
	ts.GetHex(outputstatus.fileCrc, 0);
	if (dwFileCalCRC != outputstatus.fileCrc)
	{
		outputstatus.crcErr = 1;
	}
	return outputstatus.crcErr == 0;
}

int32 spt::SptCcdFile::PowerUpIni(int32 GoCbInMaxNum, int32 GoCbOutMaxNum, int32 SvCbInMaxNum, int32 SvCbOutMaxNum)
{
	gosvInfo.ParseInfo.goEnablePubNum = 0;
	gosvInfo.ParseInfo.goEnableSubNum = 0;
	gosvInfo.ParseInfo.svEnablePubNum = 0;
	gosvInfo.ParseInfo.svEnableSubNum = 0;
	gosvInfo.ParseInfo.goPubBufNum = GoCbOutMaxNum;
	gosvInfo.ParseInfo.goPubNum = 0;
	if (GoCbOutMaxNum)
	{
		AllocBuf buf(0);
		gosvInfo.ParseInfo.gocbPub = (GooseGocbInfo*)buf.Alloc(sizeof(GooseGocbInfo), GoCbOutMaxNum);
		if (!gosvInfo.ParseInfo.gocbPub)
		{
			outputstatus.parseErr = 1;
			LogErr.Stamp() << " GOSV Info Buf Alloc err" << "\n";
			return -1;
		}
	}
	else
	{
		gosvInfo.ParseInfo.gocbPub = 0;
	}
	gosvInfo.ParseInfo.goSubBufNum = GoCbInMaxNum;
	gosvInfo.ParseInfo.goSubNum = 0;
	if (GoCbInMaxNum)
	{
		AllocBuf buf(0);
		gosvInfo.ParseInfo.gocbSub = (GooseGocbInfo*)buf.Alloc(sizeof(GooseGocbInfo), GoCbInMaxNum);
		if (!gosvInfo.ParseInfo.gocbSub)
		{
			outputstatus.parseErr = 1;
			LogErr.Stamp() << " GOSV Info Buf Alloc err" << "\n";
			return -1;
		}
	}
	else
	{
		gosvInfo.ParseInfo.gocbSub = 0;
	}
	gosvInfo.ParseInfo.svPubBufNum = SvCbOutMaxNum;
	gosvInfo.ParseInfo.svPubNum = 0;
	if (SvCbOutMaxNum)
	{
		AllocBuf buf(0);
		gosvInfo.ParseInfo.svcbPub = (SVcbInfo*)buf.Alloc(sizeof(SVcbInfo), SvCbOutMaxNum);
		if (!gosvInfo.ParseInfo.svcbPub)
		{
			outputstatus.parseErr = 1;
			LogErr.Stamp() << " GOSV Info Buf Alloc err" << "\n";
			return -1;
		}
	}
	else
	{
		gosvInfo.ParseInfo.svcbPub = 0;
	}
	gosvInfo.ParseInfo.svSubBufNum = SvCbInMaxNum;
	gosvInfo.ParseInfo.svSubNum = 0;
	if (SvCbInMaxNum)
	{
		AllocBuf buf(0);
		gosvInfo.ParseInfo.svcbSub = (SVcbInfo*)buf.Alloc(sizeof(SVcbInfo), SvCbInMaxNum);
		if (!gosvInfo.ParseInfo.svcbSub)
		{
			outputstatus.parseErr = 1;
			LogErr.Stamp() << " GOSV Info Buf Alloc err" << "\n";
			return -1;
		}
	}
	else
	{
		gosvInfo.ParseInfo.svcbSub = 0;
	}

	ParseCCD(ccdFileName);
	if (outputstatus.parseErr || outputstatus.fileNoExist)
	{
		SptApiStatus[E_SAS_CCDFileParseAlarm].Update(1);
	}
	if (outputstatus.crcErr)
	{
		SptApiStatus[E_SAS_CCDFileCrcAlarm].Update(1);
	}

	return 0;
}

uint8 spt::SptCcdFile::GetGoSvDataTypeId(uint8 Id)
{
	enum GoSvDataType type;
	type = (enum GoSvDataType)Id;
	switch (type)
	{
	case spt::E_GOSV_NULL:
		return 0xff;
		break;
	case spt::E_GOSV_BOOL:
		return  0x83;
		break;
	case spt::E_GOSV_BITSTR:
		return  0x84;
		break;
	case spt::E_GOSV_DPOS:
		return  0x84;
		break;
	case spt::E_GOSV_Q:
		return  0x84;
		break;
	case spt::E_GOSV_INT32:
	case spt::E_GOSV_INT16:
	case spt::E_GOSV_INT8:
		return  0x85;
		break;
	case spt::E_GOSV_UINT32:
	case spt::E_GOSV_UINT16:
	case spt::E_GOSV_UINT8:
		return  0x86;
		break;
	case spt::E_GOSV_FLOAT32:
		return 0x87;
		break;
	case spt::E_GOSV_TIMSSTAMP:
		return 0x91;
		break;
	default:
		break;
	}
	return 0xff;
}

uint16 spt::SptCcdFile::GetGoSvDataTypeLen(uint8 Id)
{
	enum GoSvDataType type;
	type = (enum GoSvDataType)Id;
	switch (type)
	{
	case spt::E_GOSV_NULL:
		return 0xff;
		break;
	case spt::E_GOSV_BOOL:
		return  0x8301;
		break;
	case spt::E_GOSV_BITSTR:
		return  0x8400;
		break;
	case spt::E_GOSV_DPOS:
		return  0x8402;
		break;
	case spt::E_GOSV_Q:
		return  0x8403;
		break;
	case spt::E_GOSV_INT32:
		return  0x8504;
		break;
	case spt::E_GOSV_INT16:
		return  0x8502;
		break;
	case spt::E_GOSV_INT8:
		return  0x8501;
		break;
	case spt::E_GOSV_UINT32:
		return  0x8604;
		break;
	case spt::E_GOSV_UINT16:
		return  0x8602;
		break;
	case spt::E_GOSV_UINT8:
		return  0x8601;
		break;
	case spt::E_GOSV_FLOAT32:
		return 0x8705;
		break;
	case spt::E_GOSV_TIMSSTAMP:
		return 0x9108;
		break;
	default:
		break;
	}
	return 0xff;
}

int32 spt::SptCcdFile::GetGoSvDataTypeInfo(uint8 Id, uint8& FullLen, uint8& LenLen, uint8& DataLen)
{
	enum GoSvDataType type;
	type = (enum GoSvDataType)Id;
	switch (type)
	{
	case spt::E_GOSV_BOOL:
		FullLen = 3; LenLen = 1; DataLen = 1;
		return  0;
		break;
	case spt::E_GOSV_DPOS:
		FullLen = 4; LenLen = 2; DataLen = 1;
		return  0;
		break;
	case spt::E_GOSV_Q:
		FullLen = 5; LenLen = 2; DataLen = 2;
		return  0;
		break;
	case spt::E_GOSV_INT32:
		FullLen = 6; LenLen = 1; DataLen = 4;
		return  0;
		break;
	case spt::E_GOSV_INT16:
		FullLen = 4; LenLen = 1; DataLen = 2;
		return  0;
	case spt::E_GOSV_INT8:
		FullLen = 3; LenLen = 1; DataLen = 1;
		return  0;
	case spt::E_GOSV_UINT32:
		FullLen = 6; LenLen = 1; DataLen = 4;
		return  0;
	case spt::E_GOSV_UINT16:
		FullLen = 4; LenLen = 1; DataLen = 2;
		return  0;
	case spt::E_GOSV_UINT8:
		FullLen = 3; LenLen = 1; DataLen = 1;
		return  0;
	case spt::E_GOSV_FLOAT32:
		FullLen = 7; LenLen = 2; DataLen = 4;
		return  0;
	case spt::E_GOSV_TIMSSTAMP:
		FullLen = 10; LenLen = 1; DataLen = 8;
		return  0;
	default:
		break;
	}
	FullLen = 0; LenLen = 0; DataLen = 0;
	return -1;
}

int32 spt::SptCcdFile::EncodeGoSvDataTypeInfo(uint8* Buf, uint8 Id)
{
	enum GoSvDataType type;
	type = (enum GoSvDataType)Id;
	switch (type)
	{
	case spt::E_GOSV_BOOL:
		Buf[0] = 0x83;
		Buf[1] = 0x01;
		return  0;
		break;
	case spt::E_GOSV_DPOS:
		Buf[0] = 0x84;
		Buf[1] = 0x02;
		Buf[2] = 0x06;
		return  0;
		break;
	case spt::E_GOSV_Q:
		Buf[0] = 0x84;
		Buf[1] = 0x03;
		Buf[2] = 0x00;
		return  0;
		break;
	case spt::E_GOSV_INT32:
		Buf[0] = 0x85;
		Buf[1] = 0x04;
		return  0;
		break;
	case spt::E_GOSV_INT16:
		Buf[0] = 0x85;
		Buf[1] = 0x02;
		return  0;
	case spt::E_GOSV_INT8:
		Buf[0] = 0x85;
		Buf[1] = 0x01;
		return  0;
	case spt::E_GOSV_UINT32:
		Buf[0] = 0x86;
		Buf[1] = 0x04;
		return  0;
	case spt::E_GOSV_UINT16:
		Buf[0] = 0x86;
		Buf[1] = 0x02;
		return  0;
	case spt::E_GOSV_UINT8:
		Buf[0] = 0x86;
		Buf[1] = 0x01;
		return  0;
	case spt::E_GOSV_FLOAT32:
		Buf[0] = 0x87;
		Buf[1] = 0x05;
		Buf[2] = 0x08;
		return  0;
	case spt::E_GOSV_TIMSSTAMP:
		Buf[0] = 0x91;
		Buf[1] = 0x08;
		return  0;
	default:
		Buf[0] = 0x00;
		Buf[1] = 0x00;
		return -1;
		break;
	}
	return -1;
}

int32 spt::SptT860Info::PowerUpIni(int32 Para)
{
	if (Access(CN_T860_CFG_FILE_ROOT, 0) < 0)
	{
		if (SptMain::Instance().StartMode() == SptMain::E_Normal)
		{
			FilePath path;
			path.Set(CN_T860_CFG_FILE_ROOT);
			path.Creat();
		}
	}
	CheckOutputDataSet();

	return 0;
}

spt::SptT860Info::SptT860Info()
{

}

int32 spt::SptT860Info::CheckOutputDataSet()
{
	XMLDocument olddoc;
	String100B file;
	file = CN_T860_FILE_ROOT;
	file << CN_FILE_DivFlag << "Private" << CN_FILE_DivFlag << "ied.cfg";
	XMLError err = olddoc.LoadFile(file.Str());
	if (XMLError::XML_SUCCESS == err)
	{
		const XMLElement* rootNode = olddoc.RootElement();

		if (!rootNode)
		{
			LogErr.Stamp() << "SptT860Info rootNode is Err.\n";
			return -1;
		}

		InstObjectRoot& introot = InstObjectRoot::Instance();
		InstObjectGroupParent* groupP = introot.GetGroupParent(EIOT_HalIo);

		const XMLElement* svpub = rootNode->FirstChildElement("SVPUB");
		const XMLElement* gopub = rootNode->FirstChildElement("GOPUB");

		if (groupP)
		{
			InstObjectGroup* g;
			HalBoard* Board;
			uint32 num = groupP->InstNum();
			for (uint32 i = 0; i < num; i++)
			{
				g = groupP->GetGroup(i);
				if (g->InstObjectType() != EIOT_HalIo)
				{
					LogErr.Stamp() << "SptT860Info GroupType is Err.\n";
					break;
				}
				Board = (HalBoard*)g;
				if ((Board->IoType() == Board->E_Board_YX32Pin_1))
				{
					;
				}
				else if ((Board->IoType() == Board->E_Board_Do32Pin_1))
				{

				}
				else if ((Board->IoType() == Board->E_Vir_Board_AngIn_1))
				{

				}
				else if ((Board->IoType() == Board->E_Vir_Board_SV_DataSetIn1))
				{

				}
				else if ((Board->IoType() == Board->E_Vir_Board_SV_DataSetOut1))
				{
					SptSvOutDataSet* dataset;
					dataset = (SptSvOutDataSet*)Board;
					const XMLElement* xdataset;
					xdataset = svpub->FirstChildElement("DataSet");
					bool8 ok;
					ok = 0;
					while (xdataset)
					{
						const XMLAttribute* att;
						att = xdataset->FindAttribute("sAddr");
						if (att && (StrCmp(att->Value(), dataset->DesName()) == 0))
						{
							att = xdataset->FindAttribute("datSet");
							if (att)
							{
								dataset->SetOuterName(att->Value());
								ok = 1;
								break;
							}
							else
							{
								break;
							}
						}
						xdataset = xdataset->NextSiblingElement();
					}
					if (!ok)
					{
						LogErr.Stamp() << "SptT860Info ied.cfg " << dataset->Name() << " not find datSet\n";
					}
				}
				else if ((Board->IoType() == Board->E_Vir_Board_GoOut_1))
				{
					SptGooseDataSetOut* dataset;
					dataset = (SptGooseDataSetOut*)Board;
					const XMLElement* xdataset;
					xdataset = gopub->FirstChildElement("DataSet");
					bool8 ok;
					ok = 0;
					while (xdataset)
					{
						const XMLAttribute* att;
						att = xdataset->FindAttribute("sAddr");
						if (att && (StrCmp(att->Value(), dataset->DesName()) == 0))
						{
							att = xdataset->FindAttribute("datSet");
							if (att)
							{
								dataset->OuterName() = att->Value();
								ok = 1;
								break;
							}
							else
							{
								break;
							}
						}
						xdataset = xdataset->NextSiblingElement();
					}
					if (!ok)
					{
						LogErr.Stamp() << "SptT860Info ied.cfg " << dataset->Name() << " not find datSet\n";
					}
				}
			}
		}

		LinkOutputDataSet();
		return 0;
	}
	else
	{
		XMLDocument doc;
		XMLDeclaration* del = doc.NewDeclaration("xml version=\"1.0\" encoding=\"GB2312\"");
		doc.LinkEndChild(del);
		XMLElement* root = doc.NewElement("Ied");
		String100B info;
		info << ApiVersionInfo::Instance().AppVersion().crc;
		root->SetAttribute("Ser", info.Str());
		info << (uint64)ApiVersionInfo::Instance().AppVersion().datetimeus;
		root->SetAttribute("Stamp", info.Str());
		doc.LinkEndChild(root);
		XMLElement* svpub;
		svpub = doc.NewElement("SVPUB");
		root->LinkEndChild(svpub);
		XMLElement* gopub;
		gopub = doc.NewElement("GOPUB");
		root->LinkEndChild(gopub);
		InstObjectRoot& introot = InstObjectRoot::Instance();
		InstObjectGroupParent* groupP = introot.GetGroupParent(EIOT_HalIo);
		if (groupP)
		{
			InstObjectGroup* g;
			HalBoard* Board;
			uint32 num = groupP->InstNum();
			XMLElement* ele;
			for (uint32 i = 0; i < num; i++)
			{
				g = groupP->GetGroup(i);
				if (g->InstObjectType() != EIOT_HalIo)
				{
					LogErr.Stamp() << "SptT860Info GroupType is Err.\n";
					break;
				}
				Board = (HalBoard*)g;
				if ((Board->IoType() == Board->E_Board_YX32Pin_1))
				{
					;
				}
				else if ((Board->IoType() == Board->E_Board_Do32Pin_1))
				{

				}
				else if ((Board->IoType() == Board->E_Vir_Board_AngIn_1))
				{

				}
				else if ((Board->IoType() == Board->E_Vir_Board_SV_DataSetIn1))
				{

				}
				else if ((Board->IoType() == Board->E_Vir_Board_SV_DataSetOut1))
				{
					SptSvOutDataSet* dataset;
					dataset = (SptSvOutDataSet*)Board;
					ele = doc.NewElement("DataSet");
					ele->SetAttribute("sAddr", dataset->DesName());
					ele->SetAttribute("datSet", dataset->OuterName().Str());
					svpub->LinkEndChild(ele);
				}
				else if ((Board->IoType() == Board->E_Vir_Board_GoOut_1))
				{
					SptGooseDataSetOut* dataset;
					dataset = (SptGooseDataSetOut*)Board;
					ele = doc.NewElement("DataSet");
					ele->SetAttribute("sAddr", dataset->DesName());
					ele->SetAttribute("datSet", dataset->OuterName().Str());
					gopub->LinkEndChild(ele);
				}
			}
		}
		LinkOutputDataSet();
		if (SptMain::Instance().StartMode() == SptMain::E_Normal)
		{
			SalFile mkdir;
			mkdir.SetFullName(file.Str());
			if (!mkdir.IsExist())
			{
				mkdir.Creat();
				mkdir.Close();
			}
			doc.SaveFile(file.Str());
		}

	}
	return 0;
}

int32 spt::SptT860Info::LinkOutputDataSet()
{
	return 0;
}
