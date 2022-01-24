#include"ApiProject.h"
#include "tinyxml2/tinyxml2.h"
using namespace spt;
using namespace tinyxml2;

void spt::InstObject::PowerUpIni(const char* Name, const char* DesName, class  InstObjectGroup* Group, uint32 IOTYPE, uint32 GroupId, uint32 InstId)
{
	PowerUpIni(Name, DesName, Group, 0, IOTYPE, GroupId, InstId);
}

void spt::InstObject::PowerUpIni(const char* Name, const char* DesName, InstObjectGroup* Group, InstObjectGroup* NoDirGroup, uint32 IOTYPE, uint32 GroupId, uint32 InstId)
{
	StrNCpy(name, Name, sizeof(name));
	StrNCpy(desName, DesName, sizeof(desName));
	ioType = IOTYPE;
	groupId = GroupId;
	instId = InstId;
	group = Group;
	if (group)
	{
		group->RgsObject(this);
	}
	if (NoDirGroup)
	{
		NoDirGroup->RgsSignleDirObject(this);
	}
}

uint32 spt::InstObject::InstObjectType()const
{
	return ioType;
}

uint32 spt::InstObject::GroupId()const
{
	return groupId;
}

uint32 spt::InstObject::InstId()const
{
	return instId;
}

const char* spt::InstObject::Name()const
{
	return name;
}

const char* spt::InstObject::DesName()const
{
	return desName;
}

void spt::InstObject::SaveIds(void* Doc)
{
	XMLElement* ele = (XMLElement*)Doc;
	ele->SetAttribute("InstId", instId);
	ele->SetAttribute("GroupId", groupId);
	ele->SetAttribute("Name", name);
	ele->SetAttribute("DesName", desName);
	String100B info;
	info = group->DesName();
	info << "." << desName;
	ele->SetAttribute("sAddr", info.Str());
}

void spt::InstObjectGroup::PowerUpIni(const char* Name, const char* DesName, uint32 IOTYPE, uint32 ElementNum)
{
	instNum = 0;
	InstObjectGroupParent* g = InstObjectRoot::Instance().GetGroupParent(IOTYPE);
	if (!g)
	{
		LogErr.Stamp() << name << " InstObjectGroup IOTYPE base is null  failed.\n";
		return;
	}
	instId = g->InstNum();
	InstObject::PowerUpIni(Name, DesName, g, IOTYPE, g->InstId(), instId);
	elementNum = ElementNum;
	AllocBuf buf(0);
	if (elementNum)
	{
		void* b = buf.Alloc(sizeof(void*), elementNum);
		if (b)
		{
			desBuf.SetBuf(&buf);
		}
		else
		{
			elementNum = 0;
			LogErr.Stamp() << name << " InstObjectGroup Alloc buf failed.\n";
		}
	}
}
void spt::InstObjectGroup::RgsObject(InstObject* Object)
{
	if (!Object)
	{
		return;
	}
	if (InstObjectRoot::Instance().IsPowerUpOver())
	{
		LogErr.Stamp() << Object->Name() << "RgsObject after root power up over .\n";
		return;
	}
	if ((Object->GroupId() != InstId()))
	{
		LogErr.Stamp() << Object->Name() << " GroupId is " << Object->GroupId() << ",is not equal " << name << " Group Id " << InstId() << "\n.";
		return;
	}
	if (Object->InstId() < elementNum)
	{
		instNum++;
		desBuf.SetAddrElement(Object->InstId(), Object);
		InstObject* obj = (InstObject*)desBuf.GetAddrElement(Object->InstId());
		if (obj != Object)
		{
			LogErr.Stamp() << Object->Name() << "InstObjectGroup.Rgsobject wrong!\n.";
		}
	}
	else
	{
		LogErr.Stamp() << Object->Name() << " InstId is " << Object->InstId() << ",is biger than" << name << " buf size " << desBuf.ElementNum() << "\n.";
	}
}

void spt::InstObjectGroup::RgsSignleDirObject(InstObject* Object)
{
	if (!Object)
	{
		return;
	}
	if (InstObjectRoot::Instance().IsPowerUpOver())
	{
		LogErr.Stamp() << Object->Name() << "RgsObject after root power up over .\n";
		return;
	}
	if (instNum < elementNum)
	{
		desBuf.SetAddrElement(instNum, Object);
		InstObject* obj = (InstObject*)desBuf.GetAddrElement(instNum);
		if (obj != Object)
		{
			LogErr.Stamp() << Object->Name() << "InstObjectGroup.RgsSignleDirObject wrong!\n.";
		}
		else
		{
			instNum++;
		}
	}
	else
	{
		LogErr.Stamp() << Object->Name() << " instNum is " << instNum << ",is biger than" << name << " buf size " << desBuf.ElementNum() << "\n.";
	}
}

InstObject* spt::InstObjectGroup::GetObject(uint32 InstId)
{
	if (InstId >= elementNum)
	{
		return 0;
	}
	return (InstObject*)desBuf.GetAddrElement(InstId);
}

InstObject* spt::InstObjectGroup::GetObject(const char* sAddr)
{
	String100B str;

	TransString ts;
	ts.SetBuf(sAddr);
	String100B sdr;
	sdr = sAddr;
	if (sdr.IsInclude(".") >= 0)
	{
		ts.GetLine(str, '.');
		str.Clear();
	}
	ts.GetLine(str, '.');
	InstObject* ret = 0, * obj;
	for (uint32 i = 0; i < instNum; i++)
	{
		obj = GetObject(i);
		if (obj && (str == obj->DesName()))
		{
			return obj;
		}
	}
	return ret;
}

uint32 spt::InstObjectGroup::InstNum()
{
	return instNum;
}

uint32 spt::InstObjectGroup::DesBufNum()
{
	return elementNum;
}

void spt::InstObjectGroup::SaveIds(void* Doc)
{
	XMLElement* ele = (XMLElement*)Doc;

	ele->SetAttribute("InstId", instId);
	ele->SetAttribute("GroupId", groupId);
	ele->SetAttribute("Name", name);
	ele->SetAttribute("DesName", desName);
	ele->SetAttribute("IoType", InstObjectRoot::Instance().IoTypeName(ioType));
	ele->SetAttribute("IoTypeIndex", ioType);
	String100B info;
	info << instNum;
	ele->SetAttribute("InstNum", instNum);
	XMLElement* child;
	InstObject* object;
	for (uint32 i = 0; i < instNum; i++)
	{
		child = ele->GetDocument()->NewElement("Inst");
		object = GetObject(i);
		if (object)
		{
			object->SaveIds(child);
		}
		ele->LinkEndChild(child);
	}
}

void spt::InstObjectRoot::PowerUpOver(int32 Para)
{
	powerUpOver = 1;

	if (!powerUpOver)
	{
		return;
	}
	UpdateIds();
}

bool8 spt::InstObjectRoot::IsPowerUpOver()
{
	return	powerUpOver;
}

InstObjectRoot& spt::InstObjectRoot::Instance()
{
	static InstObjectRoot inst;
	return inst;
}

uint32 spt::InstObjectRoot::GetGroupParentNum()
{
	return instNum;
}

uint32 spt::InstObjectRoot::GetGroupNum(uint32 IOTYPE)
{
	uint32 num = 0;
	InstObjectGroupParent* obj = GetGroupParent(IOTYPE);

	if (obj)
	{
		return obj->InstNum();
	}
	else
	{
		LogErr.Stamp() << "InstObjectRoot::GetGroupNum obj is null" << "\n.";
	}

	return num;
}

InstObjectGroup* spt::InstObjectRoot::GetGroup(uint32 IOTYPE)
{
	return GetGroup(IOTYPE, (uint32)0);
}

InstObjectGroup* spt::InstObjectRoot::GetGroup(uint32 IOTYPE, uint32 Num)
{
	InstObjectGroupParent* obj = GetGroupParent(IOTYPE);
	if (obj)
	{
		InstObjectGroup* b = obj->GetGroup(Num);
		if (b)
		{
			return b;
		}
	}
	return 0;
}

InstObjectGroup* spt::InstObjectRoot::GetGroup(uint32 IOTYPE, const char* sAddr)
{
	InstObjectGroupParent* obj = GetGroupParent(IOTYPE);
	if (obj)
	{
		InstObjectGroup* b = obj->GetGroup(sAddr);
		if (b)
		{
			return b;
		}
	}
	return 0;
}

InstObjectGroupParent* spt::InstObjectRoot::GetGroupParent(uint32 IOTYPE)
{
	InstObject* obj = (InstObject*)desBuf.GetAddrElement(IOTYPE);
	if (obj)
	{
		return (InstObjectGroupParent*)obj;
	}
	return 0;
}

const char* spt::InstObjectRoot::IoTypeName(uint32 IOTYPE)
{
	enum InstObjectType type = (enum InstObjectType)IOTYPE;
	switch (type)
	{
	case spt::EIOT_NULL:
		return "EIOT_NULL";
		break;
	case spt::EIOT_STATUS:
		return "EIOT_STATUS";
		break;
	case spt::EIOT_EVENT:
		return "EIOT_EVENT";
		break;
	case spt::EIOT_PARA:
		return "EIOT_PARA";
		break;
	case spt::EIOT_HMILED:
		return "EIOT_HMILED";
		break;
	case spt::EIOT_TASK:
		return "EIOT_TASK";
		break;
	case spt::EIOT_LOG:
		return "EIOT_LOG";
		break;
	case spt::EIOT_HalIo:
		return "EIOT_HalIo";
		break;
	case spt::EIOT_AngRms:
		return "EIOT_AngRms";
		break;
	case spt::EIOT_SJRecord:
		return "EIOT_SJRecord";
		break;
	case spt::EIOT_FrRecord:
		return "EIOT_FrRecord";
		break;
	case spt::EIOT_Total:
		return "EIOT_Total";
		break;
	default:
		break;
	}

	return "type";
}

int32 spt::InstObjectRoot::UpdateIds()
{
	if (SptMain::Instance().StartMode() != SptMain::E_Normal)
	{
		return -1;
	}
	String100B str;
	str = CN_INFO_FILE_ROOT;

	str << CN_FILE_DivFlag << "Ied.Des";

	XMLDocument odoc;
	XMLError err = odoc.LoadFile(str.Str());

	if (err == XML_SUCCESS)
	{
		XMLElement* root = odoc.FirstChildElement("Ied");
		if (root)
		{
			const XMLAttribute* Ser = root->FindAttribute("Ser");
			const XMLAttribute* Stamp = root->FindAttribute("Stamp");
			if (Ser && Stamp)
			{
				String100B info;
				info << ApiVersionInfo::Instance().AppVersion().crc;
				if (info == Ser->Value())
				{
					String100B info;
					info << (uint64)ApiVersionInfo::Instance().AppVersion().datetimeus;
					if (info == Stamp->Value())
					{
						return 0;
					}
				}
			}
		}
	}
	if (Access(CN_INFO_FILE_ROOT, 0) < 0)
	{
		FilePath path;
		path.Set(CN_INFO_FILE_ROOT);
		path.Creat();
	}
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
	InstObjectGroupParent* groupP;
	for (uint32 i = 0; i < EIOT_Total; i++)
	{
		groupP = GetGroupParent(i);

		if (groupP)
		{
			uint32 Len;
			Len = groupP->InstNum();
			InstObjectGroup* group;
			for (uint32 i = 0; i < Len; i++)
			{
				group = groupP->GetGroup(i);
				if (group)
				{
					XMLElement* ele;
					ele = doc.NewElement("Group");
					group->SaveIds(ele);
					root->LinkEndChild(ele);
				}
			}

		}

	}
	doc.SaveFile(str.Str());
	return 1;
}

spt::InstObjectRoot::InstObjectRoot()
{
	instId = 0;
	InstObject::PowerUpIni("InstRoot", "InstObjectRoot", 0, EIOT_NULL, 0, 0);
	elementNum = EIOT_Total;
	AllocBuf buf(0);
	if (elementNum)
	{
		void* b = buf.Alloc(sizeof(void*), elementNum);
		if (b)
		{
			desBuf.SetBuf(&buf);
			InstObjectGroupParent* g = new InstObjectGroupParent;
			g->PowerUpIni("EIOT_STATUS", "EIOT_STATUS", this, EIOT_STATUS, 100);
			desBuf.SetAddrElement(EIOT_STATUS, (InstObject*)g);

			g = new InstObjectGroupParent;
			g->PowerUpIni("EIOT_EVENT", "EIOT_EVENT", this, EIOT_EVENT, 50);
			desBuf.SetAddrElement(EIOT_EVENT, (InstObject*)g);

			g = new InstObjectGroupParent;
			g->PowerUpIni("EIOT_PARA", "EIOT_PARA", this, EIOT_PARA, 50);
			desBuf.SetAddrElement(EIOT_PARA, (InstObject*)g);

			g = new InstObjectGroupParent;
			g->PowerUpIni("EIOT_HMILED", "EIOT_HMILED", this, EIOT_HMILED, 5);
			desBuf.SetAddrElement(EIOT_HMILED, (InstObject*)g);

			g = new InstObjectGroupParent;
			g->PowerUpIni("EIOT_TASK", "EIOT_TASK", this, EIOT_TASK, 5);
			desBuf.SetAddrElement(EIOT_TASK, (InstObject*)g);

			g = new InstObjectGroupParent;
			g->PowerUpIni("EIOT_LOG", "EIOT_LOG", this, EIOT_LOG, 5);
			desBuf.SetAddrElement(EIOT_LOG, (InstObject*)g);

			g = new InstObjectGroupParent;
			g->PowerUpIni("EIOT_HalIo", "EIOT_HalIo", this, EIOT_HalIo, 200);
			desBuf.SetAddrElement(EIOT_HalIo, (InstObject*)g);

			g = new InstObjectGroupParent;
			g->PowerUpIni("EIOT_AngRms", "EIOT_AngRms", this, EIOT_AngRms, 20);
			desBuf.SetAddrElement(EIOT_AngRms, (InstObject*)g);

			g = new InstObjectGroupParent;
			g->PowerUpIni("EIOT_SJRecord", "EIOT_SJRecord", this, EIOT_SJRecord, 20);
			desBuf.SetAddrElement(EIOT_SJRecord, (InstObject*)g);

			g = new InstObjectGroupParent;
			g->PowerUpIni("EIOT_FrRecord", "EIOT_FrRecord", this, EIOT_FrRecord, 20);
			desBuf.SetAddrElement(EIOT_FrRecord, (InstObject*)g);

			instNum = elementNum;
		}
		else
		{
			elementNum = 0;
		}
	}
	powerUpOver = 0;
}

void spt::InstObjectGroupParent::PowerUpIni(const char* Name, const char* DesName, class  InstObjectGroup* g, uint32 IOTYPE, uint32 ElementNum)
{
	instNum = 0;
	StrNCpy(name, Name, sizeof(name));
	StrNCpy(desName, DesName, sizeof(desName));
	ioType = IOTYPE;
	groupId = 0;
	instId = IOTYPE;
	group = g;
	elementNum = ElementNum;
	AllocBuf buf(0);
	if (elementNum)
	{
		void* b = buf.Alloc(sizeof(void*), elementNum);
		if (b)
		{
			desBuf.SetBuf(&buf);
		}
		else
		{
			elementNum = 0;
			LogErr.Stamp() << name << " InstObjectGroupParent Alloc buf failed.\n";
		}
	}
}

InstObjectGroup* spt::InstObjectGroupParent::GetGroup(uint32 InstId)
{
	InstObject* obj = InstObjectGroup::GetObject(InstId);
	if (obj)
	{
		InstObjectGroup* g = (InstObjectGroup*)obj;
		return g;
	}
	return 0;
}

InstObjectGroup* spt::InstObjectGroupParent::GetGroup(const char* sAddr)
{
	InstObjectGroup* g;
	String100B str;
	TransString ts;
	ts.SetBuf(sAddr);
	ts.GetLine(str, '.');
	InstObjectGroup* group = 0;
	for (uint32 i = 0; i < instNum; i++)
	{
		g = GetGroup(i);
		if (g && (str == g->DesName()))
		{
			group = g;
			break;
		}
	}
	return group;
}

InstObject* spt::InstObjectGroupParent::GetObject(const char* sAddr)
{
	InstObjectGroup* group = GetGroup(sAddr);
	if (group == 0)
	{
		return 0;
	}
	return group->GetObject(sAddr);
}

