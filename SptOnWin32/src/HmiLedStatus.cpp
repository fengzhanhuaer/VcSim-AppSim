#include"SptProject.h"
#include "tinyxml2/tinyxml2.h"
using namespace spt;
using namespace tinyxml2;

void spt::HmiLedGroup::PowerUpIni(const char* Name, const char* DesName, uint16 ElementNum)
{
	InstObjectGroup::PowerUpIni(Name, DesName, (uint16)EIOT_HMILED, ElementNum);
	buf.Alloc(1, ElementNum + 8);
	uint8* b = (uint8*)buf.BufBase();
	if (!b)
	{
		LogErr << "HmiLedGroup PowerUp Ini Err.\n";
	}
	else
	{
		SalFile file;
		file.Path().Set(CN_STATUS_FILE_ROOT);
		String100B str;
		str << desName << ".ledstate";
		file.Name().Set(str.Str());
		file.OpenReadOnly();
		file.Read(buf.BufBase(), buf.BufSize());
	}
}

void spt::HmiLedGroup::SaveFile()
{
	if (isChange)
	{
		isChange = 0;
		SalFile file;
		file.Path().Set(CN_STATUS_FILE_ROOT);
		String100B str;
		str << desName << ".ledstate";
		file.Name().Set(str.Str());
		file.Creat();
		file.Write(buf.BufBase(), buf.BufSize());
	}
}

bool8 spt::HmiLedGroup::GetValue(uint8* Buf, uint16 BufLen)
{
	uint16 len = Min((int32)instNum, (int32)BufLen);
	uint8* b = (uint8*)buf.BufBase();
	if (!b)
	{
		return 0;
	}
	bool8 res = 0;
	for (uint16 i = 0; i < len; i++)
	{
		if (Buf[i] != b[i])
		{
			Buf[i] = b[i];
			res = 1;
		}
	}
	return res;
}

void spt::HmiLedGroup::SetValue(uint16 Index, bool8 HoldOn, uint8 Val)
{
	uint8* b = (uint8*)buf.BufBase();

	if (Val != b[Index])
	{
		b[Index] = Val;
		if (HoldOn)
		{
			isChange = 1;
		}
	}
}

HmiLed* spt::HmiLedGroup::GetObject(uint16 InstId)
{
	InstObject* obj = InstObjectGroup::GetObject(InstId);
	if (!obj)
	{
		return 0;
	}
	HmiLed* inst = (HmiLed*)obj;
	if (inst && (inst->InstObjectType() != EIOT_HMILED))
	{
		LogErr.Stamp() << "HmiLedGroup.GetObject err.\n";
		return 0;
	}
	return inst;
}


void spt::HmiLed::PowerUpIni(const char* Name, const char* DesName, HmiLedGroup* Group, Color color, uint8 Col, uint8 Row, bool8 HoldOn)
{
	InstObjectGroup* g = (InstObjectGroup*)Group;
	InstObject::PowerUpIni(Name, DesName, g, (uint16)EIOT_HMILED, g->InstId(), g->InstNum());
	val = 0;
	this->cor = color;
	col = Col;
	row = Row;
	holdOn = HoldOn;
	if (HoldOn)
	{
		uint8 buf[1000];
		Group->GetValue(buf, sizeof(buf));
		val = buf[instId];
	}
	else
	{
		HmiLedGroup* g = (HmiLedGroup*)group;
		g->SetValue(instId, 1, val);
	}
}

void spt::HmiLed::SetValue(uint8 Val)
{
	if (Val != (0 != val))
	{
		if (blsignalForce)
		{
			return;
		}
		if (Val)
		{
			val = cor;
		}
		else
		{
			val = Color::E_NULL;
		}
		HmiLedGroup* g = (HmiLedGroup*)group;
		g->SetValue(instId, holdOn, val);
	}
}

void spt::HmiLed::ForceSetValue(uint8 Val)
{
	if (Val != (0 != val))
	{
		if (!blsignalForce)
		{
			return;
		}
		if (Val)
		{
			val = cor;
		}
		else
		{
			val = Color::E_NULL;
		}
		HmiLedGroup* g = (HmiLedGroup*)group;
		g->SetValue(instId, 0, val);
	}
}

uint8 spt::HmiLed::Value()
{
	return val != 0;
}

void spt::HmiLed::SaveIds(void* Ele)
{
	XMLElement* ele = (XMLElement*)Ele;
	ele->SetAttribute("InstId", instId);
	ele->SetAttribute("GroupId", groupId);
	ele->SetAttribute("Name", name);
	ele->SetAttribute("DesName", desName);
	ele->SetAttribute("Row", row);
	ele->SetAttribute("Col", col);
	if (cor == E_RED)
	{
		ele->SetAttribute("Color", "E_RED");
	}
	else if (cor == E_GREEN)
	{
		ele->SetAttribute("Color", "E_GREEN");
	}
	else if (cor == E_YELLOW)
	{
		ele->SetAttribute("Color", "E_YELLOW");
	}
	else
	{
		ele->SetAttribute("Color", cor);
	}
	ele->SetAttribute("HoldOn", holdOn);
	String100B info;
	info = group->DesName();
	info << "." << desName;
	ele->SetAttribute("sAddr1", info.Str());
}
