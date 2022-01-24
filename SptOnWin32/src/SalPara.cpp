#include "SptProject.h"
#include "tinyxml2/tinyxml2.h"
using namespace spt;
using namespace tinyxml2;

uint32 spt::SalParaGroup::GetCrc(uint8 Zone)
{
	if (Zone >= maxZone)
	{
		return 0;
	}
	return usingData.Group(Zone)->GetCrc();
}

bool8 spt::SalParaGroup::UpdateForUse()
{
	InstObject* inst;
	SalPara* para;
	uint32 num = InstNum();
	bool8 res = 1;
	for (uint32 j = 0; j < num; j++)
	{
		inst = GetObject(j);
		if (!inst)
		{
			status = E_NonIni;
			LogErr << Name() << "DefaultData inst is null\n";
			return -1;
		}
		para = (SalPara*)inst;
		res = res && para->UpdateForUse();
	}
	return res;
}

int32 spt::SalParaGroup::PowerUpIni(const char* Name, const char* DesName, uint16 CurZone, uint16 MaxZone, uint16 ElementNum)
{
	dataChanCnt = 1;
	dataElementNum = ElementNum;
	maxZone = MaxZone;
	curZone = CurZone;
	dataOffSet = 0;
	int32 res = 0;
	InstObjectGroup::PowerUpIni(Name, DesName, (uint16)EIOT_PARA, ElementNum);
	usingData.SetElement(MaxZone, ElementNum);
	editData.SetElement(MaxZone, ElementNum);
	res = LoadPara(E_LoadAll, 0);
	return res;
}

int32 spt::SalParaGroup::DefaultData()
{
	int32 res = 0;
	status = E_NonIni;
	for (uint32 i = 0; i < maxZone; i++)
	{
		ParaGroupData* data;
		data = editData.Group(i);
		if (!data)
		{
			status = E_DataCrcIsErr;
			LogErr << Name() << "DefaultData data is null\n";
			res = -1;
			break;
		}
		data->header.dataChanCnt = 1;
		data->header.status = E_OK;
		int32* cell;
		InstObject* inst;
		SalPara* para;
		uint32 num = InstNum();
		for (uint32 j = 0; j < num; j++)
		{
			inst = GetObject(j);
			if (!inst)
			{
				data->header.status = status = E_DataCrcIsErr;
				LogErr << Name() << "DefaultData inst is null\n";
				return -1;
			}
			para = (SalPara*)inst;
			cell = (int32*)data->AddrOf(para->DataOffSet());
			if (!cell)
			{
				data->header.status = status = E_DataCrcIsErr;
				LogErr << Name() << "DefaultData cell is null\n";
				return -1;
			}
			if (para->ValueType() == SalPara::E_PT_Str)
			{
				StrNCpy((char*)cell, (const char*)para->Default(), para->Max());
			}
			else
			{
				cell[0] = para->Default();
			}
			if (res)
			{
				data->header.status = status = E_DataCrcIsErr;
				LogErr << Name() << "DefaultData default err" << j << "\n";
				return -1;
			}
		}
		data->AddCrc();
	}
	if (!res)
	{
		res = SalParaGroupSaveTask::Instance().SavePara(this, E_SaveDataAll, 0);
	}
	return res;
}

int32 spt::SalParaGroup::CheckStatus()
{
	return status;
}

int32 spt::SalParaGroup::ElementSize()
{
	ParaGroupData* p = 0;
	return sizeof(*p->data);
}

ParaGroupDataAll& spt::SalParaGroup::DataGroup()
{
	return usingData;
}

int32 spt::SalParaGroup::SavePara(SalParaGroup* Group, int32 Para, int32 ZoneNum)
{
	LogMsg.Stamp() << name << "Saving Para" << " " << Para << " " << ZoneNum << "\n";
	if (Para == E_ChangeZone)
	{
		if (ZoneNum >= maxZone)
		{
			LogErr << desName << "data  save ZoneNum err." << ZoneNum << "\n";
			return -1;
		}
		curZone = ZoneNum;
	}
	uint32 es = 0;
	uint32 ed = maxZone;
	if (Para == E_SaveDataAll)
	{

	}
	else if (Para == E_SaveSingleZone)
	{
		es = ZoneNum;
		ed = ZoneNum + 1;
	}
	else
	{
		LogErr << desName << "data save Para Err " << Para << "\n";
		return -1;
	}
	SalFile file;
	file.Path().Set(CN_PARA_FILE_ROOT);
	String100B str;
	ParaGroupData* data;
	for (uint32 i = es; i < ed; i++)
	{
		data = editData.Group(i);
		if (!data->IsCrcOk())
		{
			LogMsg << desName << "SavePara Crc err.\n";
			return -1;
		}
		if (CheckEditZoneRange((int32*)data->AddrOf(0)) < 0)
		{
			LogMsg << desName << "SavePara CheckEditZoneRange err.\n";
			return -1;
		}
		data->header.status = E_OK;
		str = desName;
		str << ".dat";
		str << i;
		file.Name().Set(str.Str());
		file.Creat();
		file.Write(&data->header, sizeof(data->header));
		file.Write(data->AddrOf(0), data->SizeOfDataWithCrc());
		file.Close();
		str = desName;
		str << ".bak";
		str << i;
		file.Name().Set(str.Str());
		file.Creat();
		file.Write(&data->header, sizeof(data->header));
		file.Write(data->AddrOf(0), data->SizeOfDataWithCrc());
		file.Close();
		{
			String100B str;
			str = desName;
			str << ".sta";
			str << i;
			file.Name().Set(str.Str());
			file.Creat();
			int32 sta = E_SaveOver;
			file.Write(&sta, sizeof(sta));
			file.Close();
		}
		if (!file.IsExist())
		{
			LogMsg << desName << "SavePara save err1.\n";
			data->header.status = status = E_DataCrcIsErr;
			return -1;
		}
	}
	if (Para == E_SaveDataAll)
	{
		LoadPara(E_LoadAll, ZoneNum);
	}
	else if (Para == E_SaveSingleZone)
	{
		LoadPara(E_LoadZone, ZoneNum);
	}
	int32 res = 0;
	if (status != E_OK)
	{
		res = -1;
	}
	dataChanCnt++;
	if (!dataChanCnt)
	{
		dataChanCnt++;
	}
	return res;
}

int32 spt::SalParaGroup::loadBakParaForUse(int32 ZoneNum)
{
	SalFile file;
	file.Path().Set(CN_PARA_FILE_ROOT);
	String100B str;
	str = desName;
	str << ".dat";
	str << ZoneNum;
	file.Name().Set(str.Str());
	file.Creat();
	String1000B ostr;
	ostr << CN_PARA_FILE_ROOT  CN_FILE_DivFlag << desName << ".bak" << ZoneNum;
	file.Copy(ostr.Str());
	file.Close();
	return LoadPara(E_LoadZone, ZoneNum);
}

int32 spt::SalParaGroup::getSaveStepFlag(uint32 Zone)
{
	SalFile file;
	file.Path().Set(CN_PARA_FILE_ROOT);
	String100B str;
	str = desName;
	str << ".sta";
	str << Zone;
	file.Name().Set(str.Str());
	file.OpenReadOnly();
	int32 sta = E_SaveNull;
	file.Read(&sta, sizeof(sta));
	file.Close();
	return sta;
}


int32 spt::SalParaGroup::SavePara(void* Buf, int32 BufLen, int32 Zone)
{
	SalFile file;
	file.Path().Set(CN_PARA_FILE_ROOT);
	String100B str;
	str = desName;
	str << ".sta";
	str << Zone;
	file.Name().Set(str.Str());
	file.Creat();
	int32 sta = E_SaveStart;
	file.Write(&sta, sizeof(sta));
	file.Close();
	if (!Buf)
	{
		return -1;
	}
	uint32 dataLen = editData.Group(0)->SizeOfDataWithCrc() - sizeof(*editData.Group(0)->data);
	if ((uint32)(BufLen) < dataLen)
	{
		return -1;
	}
	if (Zone >= maxZone)
	{
		return -1;
	}
	MemCpy(editData.Group(Zone)->AddrOf(0), Buf, dataLen);
	editData.Group(Zone)->header.dataChanCnt = usingData.Group(Zone)->header.dataChanCnt + 1;
	if (!editData.Group(Zone)->header.dataChanCnt)
	{
		editData.Group(Zone)->header.dataChanCnt++;
	}
	editData.Group(Zone)->AddCrc();
	return  SalParaGroupSaveTask::Instance().SavePara(this, E_SaveSingleZone, Zone);
}

int32 spt::SalParaGroup::ChangeZone(int32 Zone)
{
	return  SalParaGroupSaveTask::Instance().SavePara(this, E_ChangeZone, Zone);
}

int32 spt::SalParaGroup::LoadPara(int32 Para, int32 ZoneNum)
{
	int32 res = 0;
	SalFile file;
	file.Path().Set(CN_PARA_FILE_ROOT);
	String100B str;
	ParaGroupData* data;
	status = E_NonIni;
	for (uint32 i = 0; i < maxZone; i++)
	{
		data = usingData.Group(i);
		if (Para == E_LoadZone)
		{
			if ((uint32)ZoneNum != i)
			{
				continue;
			}
		}
		str = desName;
		str << ".dat";
		str << i;
		file.Name().Set(str.Str());
		if (file.IsExist())
		{
			file.Open("rb");

			if (!data)
			{
				res = -1;
				LogErr << desName << "数据指针为空\n";
				break;
			}
			ParaGroupDataHeader header;
			file.Read(&header, sizeof(header));

			if ((header.headerSize) == sizeof(header) && (header.elementNum == data->header.elementNum) && (header.headerSize == data->header.headerSize))
			{
				data->header.dataChanCnt = header.dataChanCnt;
				file.Read(data->AddrOf(0), data->SizeOfDataWithCrc());
				if (!data->IsCrcOk())
				{
					data->header.status = E_DataCrcIsErr;
					status = E_DataCrcIsErr;
					//fixme 添加自动恢复措施
					res = -1;
					LogErr << file.Name().Name() << "校验异常\n";
					break;
				}
				else
				{
					data->header.status = E_OK;
				}
			}
			else
			{
				res = -1;
				data->header.status = E_HeaderNotMatch;
				status = E_HeaderNotMatch;
			}
			file.Close();

		}
		else
		{
			LogWarn << str << " 数据文件不存在。\n";
			data->header.status = E_DataNotExist;
			status = E_DataNotExist;
			res = -1;
			break;
		}
	}
	if (E_NonIni == status)
	{
		bool8 ok = 1;
		for (uint32 i = 0; i < maxZone; i++)
		{
			data = usingData.Group(i);
			if (Para == E_LoadZone)
			{
				if ((uint32)ZoneNum != i)
				{
					if (data->header.status != E_OK)
					{
						ok = 0;
						status = (E_ParaStatus)data->header.status;
					}
				}
			}
		}
		if (ok)
		{
			status = E_OK;
		}
	}
	return res;
}

uint16 spt::SalParaGroup::DataChanCnt()
{
	return dataChanCnt;
}

const int32* spt::SalParaGroup::UsingData(uint32 Zone)
{
	if (Zone >= maxZone)
	{
		return 0;
	}
	return (const int32*)usingData.Group(Zone)->AddrOf(0);
}

uint16 spt::SalParaGroup::UsingZone()
{
	return curZone;
}

uint32 spt::SalParaGroup::MaxZone()
{
	return maxZone;
}

SalPara* spt::SalParaGroup::GetDes(uint32 No)
{
	InstObject* inst = GetObject(No);
	if (!inst)
	{
		status = E_DataCrcIsErr;
		LogErr.Stamp() << Name() << "ParaGroup GetDes inst is null\n";
		return 0;
	}
	SalPara* para = (SalPara*)inst;
	return para;
}

uint32 spt::SalParaGroup::GetDataOffSet(uint32 size)
{
	uint32 res = dataOffSet;
	if (dataOffSet < dataElementNum)
	{
		dataOffSet += size;
	}
	else
	{
		LogErr.Stamp() << Name() << "ParaGroup data over flow\n";
	}
	return res;
}

int32 spt::SalParaGroup::CheckEditZoneRange(int32* AddrBase)
{
	int32* cell = AddrBase;
	InstObject* inst;
	SalPara* para;
	uint32 num = InstNum();
	for (uint32 j = 0; j < num; j++)
	{
		inst = GetObject(j);
		if (!inst)
		{
			LogErr << Name() << "CheckEditZoneRange inst is null\n";
			return -1;
		}
		para = (SalPara*)inst;
		cell = AddrBase + para->DataOffSet();
		if (para->ValueType() == SalPara::E_PT_Str)
		{
			if (StrLen((const char*)cell) > para->Max())
			{
				return -1;
			}
		}
		else if ((para->ValueType() == SalPara::E_PT_HEX8) ||
			(para->ValueType() == SalPara::E_PT_HEX16) ||
			(para->ValueType() == SalPara::E_PT_HEX32) ||
			(para->ValueType() == SalPara::E_PT_BIT8) ||
			(para->ValueType() == SalPara::E_PT_BIT16) ||
			(para->ValueType() == SalPara::E_PT_BIT32) ||
			(para->ValueType() == SalPara::E_PT_UInt32)
			)
		{
			if (((uint32)*cell > (uint32)para->Max()) || (((uint32)*cell < (uint32)para->Min())))
			{
				return -1;
			}
		}
		else
		{
			if ((*cell > para->Max()) || ((*cell < para->Min())))
			{
				return -1;
			}
		}
	}
	return 0;
}

const struct stAppFlags* spt::SalParaGroup::AppFlags()const
{
	return appFlags;
}

void spt::SalPara::PowerUpIni(const char* Name, const char* DesName, SalParaGroup* Group, int32 Min, int32 Def, int32 Max, uint8 DotNum, uint8 ValueType, const VarUnits& Units)
{
	flags.u32 = 0;
	InstObjectGroup* g = (InstObjectGroup*)Group;
	InstObject::PowerUpIni(Name, DesName, Group, (uint16)EIOT_EVENT, g->InstId(), g->InstNum());
	SetRange(Max, Min);
	def = Def;
	dotNum = DotNum;
	units = &Units;
	usingValue.valueInfo1 = dotNum;
	usingValue.valueInfo2 = Units.Type();
	disp = 1;
	valueType = ValueType;
	if (E_PT_Str == valueType)
	{
		dataOffSet = Group->GetDataOffSet(Max / sizeof(int32));
	}
	else
	{
		dataOffSet = Group->GetDataOffSet(sizeof(int32) / sizeof(int32));
	}
	switch (valueType)
	{
	case E_PT_Int32:
	{
		editValue.valueType = usingValue.valueType = E_SVT_I32;
		break;
	}
	case E_PT_Ct_Second:
	{
		editValue.valueType = usingValue.valueType = E_SVT_ENUM32;
		break;
	}
	case E_PT_Str:
	{
		editValue.valueType = usingValue.valueType = E_SVT_STR;
		editValue.value.cstr = (const char*)Def;
		break;
	}
	case E_PT_Enum:
	{
		editValue.valueType = usingValue.valueType = E_SVT_ENUMDES | E_SVT_PTR;
		editValue.value.vptr = 0;
		break;
	}
	case E_PT_HEX8:
	case E_PT_HEX16:
	case E_PT_HEX32:
	{
		editValue.valueType = usingValue.valueType = E_SVT_HEX32;
		break;
	}
	case E_PT_BIT8:
	case E_PT_BIT16:
	case E_PT_BIT32:
	{
		editValue.valueType = usingValue.valueType = E_SVT_BIT16;
		break;
	}
	case E_PT_Zone:
	{
		editValue.valueType = usingValue.valueType = E_SVT_I32;
		break;
	}
	default:
		break;
	}
}

void spt::SalPara::SetRange(int32 Max, int32 Min)
{
	max = Max;
	min = Min;
}

uint8 spt::SalPara::ValueType()
{
	return valueType;
}

uint8 spt::SalPara::DotNum()
{
	return dotNum;
}

uint8 spt::SalPara::UnitType()
{
	if (units)
	{
		return units->Type();
	}
	return 0;
}

const char* spt::SalPara::Unit()
{
	return units->toString();
}

int32 spt::SalPara::Max()
{
	if (flags.st.isRelatedOthoers)
	{
		SalPara* para = (SalPara*)exInfo1.value.vptr;
		if (para)
		{
			return max * para->EnumVal();
		}
	}
	return max;
}

int32 spt::SalPara::Min()
{
	if (flags.st.isRelatedOthoers)
	{
		SalPara* para = (SalPara*)exInfo1.value.vptr;
		if (para)
		{
			return min * para->EnumVal();
		}
	}
	return min;
}

int32 spt::SalPara::Default()
{
	return def;
}

bool8 spt::SalPara::Disp()
{
	return disp;
}

bool8 spt::SalPara::SetDisp(bool8 Disp)
{
	return disp = Disp;
}

bool8 spt::SalPara::ReadOnly()
{
	return flags.st.isReadOnly;
}

int32 spt::SalPara::DataOffSet()
{
	return dataOffSet;
}

const st32value& spt::SalPara::UsingValue()
{
	return  usingValue;
}

const st32value& spt::SalPara::ExInfo1()
{
	return exInfo1;
}
using namespace tinyxml2;
void spt::SalPara::SaveIds(void* Ele)
{
	XMLElement* ele = (XMLElement*)Ele;
	ele->SetAttribute("InstId", instId);
	ele->SetAttribute("GroupId", groupId);
	ele->SetAttribute("Name", name);
	ele->SetAttribute("DesName", desName);
	ele->SetAttribute("Max", max);
	ele->SetAttribute("Def", def);
	ele->SetAttribute("Min", min);
	ele->SetAttribute("DotNum", dotNum);
	ele->SetAttribute("DataOffSet", dataOffSet);
	ele->SetAttribute("ValueType", valueType);
	ele->SetAttribute("Units", units->toString());
	String100B info;
	info = group->DesName();
	info << "." << desName;
	ele->SetAttribute("sAddr", info.Str());
}

int32 spt::SalPara::Int32()
{
	return usingValue.value.i32;
}

int32 spt::SalPara::EnumVal()
{
	SalEnumDes* des = (SalEnumDes*)exInfo1.value.vptr;
	return des[usingValue.value.u32].val;
}

float32 spt::SalPara::Float32()
{
	return Int32FixDot2Float32(usingValue.value.i32, dotNum);
}

uint32 spt::SalPara::Uint32()
{
	return usingValue.value.u32;
}

bool8 spt::SalPara::UpdateForUse()
{
	SalParaGroup* g = (SalParaGroup*)group;
	const int32* p = g->UsingData(g->UsingZone());
	if (!p)
	{
		return 0;
	}
	p = p + dataOffSet;
	if (E_PT_Str == valueType)
	{
		usingValue.value.vptr = (void*)p;
	}
	else
	{
		usingValue.value.i32 = *p;
	}
	return 1;
}

bool8 spt::SalPara::Value2Str(SalString& str)
{
	return Value2Str(usingValue.value, str);
}

bool8 spt::SalPara::Value2Str(u32value Value, SalString& str)
{
	switch (ValueType())
	{
	case E_PT_Int32:
	{
		str.Format((int32)Value.i32, DotNum());
		break;
	}
	case E_PT_Zone:
	case E_PT_UnitSet:
	case E_PT_UInt32:
	{
		str.Format((uint32)Value.u32, DotNum());
		break;
	}
	case E_PT_Ct_Second:
	case E_PT_Enum:
	{
		SalEnumDes* des = (SalEnumDes*)ExInfo1().value.vptr;
		if (Value.u32 < ExInfo1().valueInfo1)
		{
			str << des[Value.u32].des;
		}
		break;
	}
	case E_PT_Str:
	{
		str << (const char*)Value.vptr;
		break;
	}
	case E_PT_HEX8:
	case E_PT_BIT8:
	{
		str << "0x";
		str.FormatHex((uint8)Value.u32);
		break;
	}
	case E_PT_HEX16:
	case E_PT_BIT16:
	{
		str << "0x";
		str.FormatHex((uint16)Value.u32);
		break;
	}
	case E_PT_HEX32:
	case E_PT_BIT32:
	{
		str << "0x";
		str.FormatHex((uint32)Value.u32);
		break;
	}
	default:
		break;
	}
	return 1;
}

void spt::ParaGroupDataAll::SetElement(uint32 ZoneNum, uint32 ElementNum)
{
	if (bufBase)
	{
		spt::Free(bufBase);
		bufBase = 0;
	}
	if (ZoneNum >= CN_MaxParaZone)
	{
		ZoneNum = CN_MaxParaZone;
		LogErr.Stamp() << "ParaGroupDataAll ElementNum is " << ElementNum << " too big\n";
	}
	if (ZoneNum == 0)
	{
		ZoneNum = 1;
		LogErr.Stamp() << "ParaGroupDataAll ElementNum is " << ElementNum << " too small\n";
	}
	AllocBuf buf(0);
	buf.Alloc(sizeof(ParaGroupData), ZoneNum);
	SetBuf(&buf);
	if (!bufBase)
	{
		LogErr.Stamp() << "ParaGroupDataAll Buf alloc failed.\n";
		return;
	}
	ParaGroupData* pData;
	for (uint32 i = 0; i < ZoneNum; i++)
	{
		pData = (ParaGroupData*)GetElement(i);
		pData->PowerUpIni(ElementNum, i);
	}
}

ParaGroupData* spt::ParaGroupDataAll::Group(uint32 Zone)
{
	if (bufBase)
	{
		return (ParaGroupData*)GetElement(Zone);
	}
	return 0;
}

int32 spt::SalParaGroupSaveTask::PowerUpIni(int32 Para)
{
	if (SptMain::Instance().StartMode() != SptMain::E_Normal)
	{
		return -1;
	}
	SetSaveBlockPara();
	Task::PowerUpIni(0);
	Start();
	return 0;
}

int32 spt::SalParaGroupSaveTask::OneLoop()
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
		saveSem.Wait(10000);
		CheckLoadStart();
		if (saveStep == E_BeginSave)
		{
			if (group)
			{
				saveRes = group->SavePara(group, savePara, saveZone);
			}
			saveStep = E_EndSave;
		}
		else
		{
			MsSleep(20);
		}
		break;
	}
	default:
		taskStep = E_PowerUpIni;
		break;
	}
	return 0;
}

int32 spt::SalParaGroupSaveTask::SavePara(SalParaGroup* Group, int32 Para, int32 ZoneNum)
{
	if (saveStep != E_Wait)
	{
		LogErr.Stamp() << Group->Name() << "SavePata saveStep is not E_Wait\n";
		return -1;
	}
	if (SptIoProcess::Instance().SptFlag().IsPowerDownAtRange(saveLowLimit, saveHighLimit))
	{
		return 0;
	}
	group = Group;
	savePara = Para;
	saveStep = E_BeginSave;
	saveZone = ZoneNum;
	MsTimer update;
	update.UpCnt(5000);
	update.Enable(1);
	update.Restart();
	saveRes = -1;
	saveSem.Post();
	while (!update.Status())
	{
		if (saveStep == E_EndSave)
		{
			break;
		}
		MsSleep(20);
	}
	saveStep = E_Wait;
	return saveRes;
}

spt::SalParaGroupSaveTask::SalParaGroupSaveTask()
	:Task("tParaSave", TaskBasePriority - 50, 1024 * 1024, E_T_FLOAT, E_ServiceCore)
{
	saveSem.Creat(0);
}

void spt::SalParaEditGroup::PowerUpIni(uint32 ElementNum)
{
	if (ElementNum)
	{
		editCellBuf = new SalParaEditCell[ElementNum];
		if (!editCellBuf)
		{
			LogErr.Stamp() << "SalParaEditGroup PowerUpIni err.\n";
			return;
		}
		AllocBuf buf1(0);

		void* b = buf1.Alloc(sizeof(int32), ElementNum);
		if (!b)
		{
			LogErr.Stamp() << "SalParaEditGroup PowerUpIni err1.\n";
			return;
		}
		editBuf.SetBuf(&buf1);
		elementNum = ElementNum;
	}
}

uint32 spt::SalParaEditGroup::EditCellNum()
{
	return elementNum;
}

uint32 spt::SalParaEditGroup::CurEditCellNum()
{
	return curEditCellNum;
}

SalParaEditCell* spt::SalParaEditGroup::EditCell(uint32 No)
{
	if (No >= elementNum)
	{
		return 0;
	}
	return  (SalParaEditCell*)editCellBuf + No;
}

int32 spt::SalParaEditGroup::Set(SalParaGroup* Group, uint32 Zone)
{
	group = Group;
	zoneNum = 0;
	if (!group)
	{
		LogErr.Stamp() << "SalParaEditGroup SetZone group is null\n";
		return -1;
	}
	if (Zone >= group->MaxZone())
	{
		LogErr.Stamp() << "SalParaEditGroup SetZone Zone is too bigger\n";
		return -1;
	}
	uint32 end = group->InstNum();
	if (end > elementNum)
	{
		LogErr.Stamp() << "SalParaEditGroup UpdateEditValue end is small\n";
		return -1;
	}

	zoneNum = Zone;
	curEditCellNum = group->InstNum();
	SalPara* para;
	int32* databuf = (int32*)editBuf.BufBase();
	for (uint32 i = 0; i < curEditCellNum; i++)
	{
		para = group->GetDes(i);
		if (!para)
		{
			LogErr.Stamp() << "SalParaEditGroup UpdateEditValue para is null\n";
		}
		EditCell(i)->SetDes(para, databuf + para->DataOffSet());
	}
	UpdateEditValue();
	return 0;
}

const SalParaGroup* spt::SalParaEditGroup::Group()
{
	return group;
}

int32 spt::SalParaEditGroup::UpdateEditValue()
{
	if (!group)
	{
		LogErr.Stamp() << "SalParaEditGroup UpdateEditValue group is null\n";
		return -1;
	}
	if (zoneNum >= group->MaxZone())
	{
		LogErr.Stamp() << "SalParaEditGroup UpdateEditValue Zone is too bigger\n";
		return -1;
	}
	if (!editCellBuf)
	{
		LogErr.Stamp() << "SalParaEditGroup UpdateEditValue bufBase is null\n";
		return -1;
	}
	const ParaGroupData* databuf = group->DataGroup().Group(zoneNum);
	uint32 end = group->InstNum();
	if (end > elementNum)
	{
		LogErr.Stamp() << "SalParaEditGroup UpdateEditValue end is small\n";
		return -1;
	}
	MemCpy(editBuf.BufBase(), databuf->data, databuf->SizeOfData());
	return 0;
}

int32 spt::SalParaEditGroup::SavePara()
{
	if (group)
	{
		return group->SavePara(editBuf.BufBase(), editBuf.BufSize(), zoneNum);
	}
	return -1;
}

int32 spt::SalParaEditCell::SetDes(SalPara* Des, int32* Buf)
{
	if (Des)
	{
		des = Des;
		buf = Buf;
		return 0;
	}
	return 0;
}

bool8 spt::SalParaEditCell::SetValue(uint32 Val)
{
	buf[0] = (int32)Val;
	return 1;
}

bool8 spt::SalParaEditCell::SetValue(const char* Val)
{
	if (des->ValueType() == SalPara::E_PT_Str)
	{
		StrNCpy((char*)buf, Val, des->Max());
		return 1;
	}
	return 0;
}

uint32 spt::ParaGroupData::AddCrc()
{
	return  data[header.elementNum] = CalCrc();
}

bool8 spt::ParaGroupData::IsCrcOk()const
{
	return (uint32)data[header.elementNum] == CalCrc();
}

uint32 spt::ParaGroupData::CalCrc()const
{
	return Crc16ModBus.CalCrc(data, sizeof(*data) * header.elementNum);
}

uint32 spt::ParaGroupData::GetCrc()const
{
	return (uint32)data[header.elementNum];
}

uint32 spt::ParaGroupData::SizeOfDataWithCrc()const
{
	return sizeof(*data) * (header.elementNum + 1);
}

uint32 spt::ParaGroupData::SizeOfData() const
{
	return sizeof(*data) * (header.elementNum);
}

int32 spt::ParaGroupData::PowerUpIni(uint32 ElementNum, uint32 Zone)
{
	data = (int32*)Calloc(1, (ElementNum) * sizeof(*data) + sizeof(*data));
	if (!data)
	{
		LogErr.Stamp() << "ParaGroupDataMng data buf calloc err.\n";
	}
	header.status = 0;
	header.version = 1;
	header.headerSize = sizeof(header);
	header.elementSize = sizeof(*data);
	header.dataChanCnt = 0;
	header.elementNum = (uint16)ElementNum;
	header.zoneIndex = Zone;
	return 0;
}
void* spt::ParaGroupData::AddrOf(uint32 No)
{
	return &data[No];
}
