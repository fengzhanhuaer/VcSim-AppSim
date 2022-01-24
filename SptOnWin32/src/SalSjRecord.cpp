#include"ApiProject.h"
using namespace spt;

void spt::SalSjRecordData::SetStamp(SalDateStamp& stamp)
{
	SalRtc rtc;
	rtc.FromStamp(&stamp);
	String100B str;
	rtc.ToStrHzFmt2(str);
	StrNCpy(this->stamp, str.Str(), sizeof(this->stamp));
}
void spt::SalSjRecordData::GetStamp(SalDateStamp& stamp)
{
	stamp.Set((int64)0);
	stamp.FromStrHzFmt2(this->stamp);
}
void spt::SalSjRecordData::StampNow()
{
	SalDateStamp stamp;
	stamp.Now();
	SetStamp(stamp);
}

void spt::SalSjRecordData::SetProcess(const char* Process)
{
	StrNCpy(process, Process, sizeof(process));
}

void spt::SalSjRecordData::SetUsr(const char* Usr)
{
	StrNCpy(usr, Usr, sizeof(usr));
}

void spt::SalSjRecordData::SetObject(const char* Object)
{
	StrNCpy(object, Object, sizeof(object));
}

void spt::SalSjRecordData::SetResult(const char* Result)
{
	StrNCpy(result, Result, sizeof(result));
}

void spt::SalSjRecordData::SetExInfo(const char* ExInfo1, const char* ExInfo2, const char* ExInfo3)
{
	StrNCpy(exInfo1, ExInfo1, sizeof(exInfo1));
	StrNCpy(exInfo2, ExInfo2, sizeof(exInfo2));
	StrNCpy(exInfo3, ExInfo3, sizeof(exInfo3));
}

void spt::SalSjRecordData::SetRecord(const char* Process, const char* Usr, const char* Object, const char* Result, const char* exInfo1, const char* exInfo2, const char* exInfo3)
{
	SetProcess(Process);
	SetProcess(Process);
	SetUsr(Usr);
	SetObject(Object);
	SetResult(Result);
	SetExInfo(exInfo1, exInfo2, exInfo3);
}

uint32 spt::SalSjRecordData::CalcSum()
{
	uint8* sur = (uint8*)this;
	uint8* end = (uint8*)&this->sum;
	uint32 Sum = 0;
	while (sur < end)
	{
		Sum += *sur++;
	}
	return Sum;
}

bool8 spt::SalSjRecordData::IsSumOk()
{
	return sum == CalcSum();
}

bool8 spt::SalSjRecordData::IsRecordOk()
{
	return IsSumOk() && stamp[0] && stamp[1];
}

uint32 spt::SalSjRecordData::AddSum()
{
	return sum = CalcSum();
}

int32 spt::SalSjRecordGroup::PowerUpIni(const char* Name, const char* DesName, uint32 ElementNum, uint32 PoolSize)
{
	InstObjectGroup::PowerUpIni(Name, DesName, EIOT_SJRecord, ElementNum);
	hdr.elementPoolSize = PoolSize + 1;
	hdr.version = 1;
	hdr.hdrSize = sizeof(hdr);
	hdr.elementSize = sizeof(SalSjRecordData);
	hdr.validNum = hdr.writer = hdr.reader = hdr.usdNum = 0;
	StrNCpy(hdr.eventType, Name, sizeof(hdr.eventType));
	StrNCpy(hdr.fileName, DesName, sizeof(hdr.fileName));
	buf.Alloc(sizeof(SalSjRecordData), hdr.elementPoolSize + 1);
	savehdr = hdr;
	if (!buf.BufBase())
	{
		LogErr.Stamp() << "SalSjRocordGroup" << Name << "buf ini err.\n";
		return -1;
	}
	if (LoadRecord() < 0)
	{
		save2File("srecord");
	}
	return 0;
}

int32 spt::SalSjRecordGroup::LoadRecord()
{
	if (loadFile() != 0)
	{
		bak2File();
		SalFile ofile, nfile;
		ofile.Path().Set(CN_SJRECORD_FILE_ROOT);
		String100B str;
		str = hdr.fileName;
		str << ".srbak";
		ofile.Name().Set(str.Str());
		ofile.OpenReadOnly();
		if (!ofile.IsOpened())
		{
			return -1;
		}
		str = hdr.fileName;
		str << ".srecord";
		nfile.Path().Set(CN_SJRECORD_FILE_ROOT);
		nfile.Name().Set(str.Str());
		nfile.Creat();
		nfile.Copy(ofile);
		nfile.Close();
		ofile.Close();
		if (loadFile() != 0)
		{
			return -1;
		}
	}
	return 0;
}

int32 spt::SalSjRecordGroup::DeleteAll()
{
	hdr.reader = 0;
	hdr.writer = 0;
	hdr.usdNum = 0;
	hdr.validNum = 0;
	SaveAll();
	return 0;
}

uint32 spt::SalSjRecordGroup::NewestRecordIndex()
{
	return (hdr.writer + hdr.elementPoolSize - 1) % hdr.elementPoolSize;
}

uint32 spt::SalSjRecordGroup::OldestRecordIndex()
{
	return (hdr.writer + hdr.elementPoolSize + 1) % hdr.elementPoolSize;
}

uint32 spt::SalSjRecordGroup::ValidNum()
{
	return hdr.validNum;
}

uint32 spt::SalSjRecordGroup::PoolSize()
{
	return hdr.elementPoolSize;
}

int32 spt::SalSjRecordGroup::GetNextValidEvent(uint32 Base, uint32 Num, SalSjRecordData& Record)
{
	uint32 valid = 0;
	uint32 reader = (Base) % hdr.elementPoolSize;
	uint32 w = hdr.writer % hdr.elementPoolSize;
	SalSjRecordData* record = (SalSjRecordData*)buf.BufBase();
	while (reader != w)
	{
		if (record[reader].IsRecordOk())
		{
			if (valid == Num)
			{
				MemCpy(&Record, &record[reader], sizeof(Record));
				return reader;
			}
			valid++;
		}
		reader = (reader + 1) % hdr.elementPoolSize;
	}
	return -1;
}

int32 spt::SalSjRecordGroup::CreatEvent(SalSjRecordData& Record)
{
	uint32 writer = hdr.writer % hdr.elementPoolSize;
	SalSjRecordData* record = (SalSjRecordData*)buf.BufBase();
	Record.AddSum();
	MemCpy(&record[writer], &Record, sizeof(SalSjRecordData));
	uint32 temp = hdr.usdNum + 1;
	if (temp >= hdr.elementPoolSize)
	{
		temp = hdr.elementPoolSize - 1;
	}
	hdr.usdNum = temp;

	temp = hdr.validNum + 1;
	if (temp >= hdr.elementPoolSize)
	{
		temp = hdr.elementPoolSize - 1;
	}
	hdr.validNum = temp;
	hdr.writer = (writer + 1) % hdr.elementPoolSize;
	SalSjRecordDispachTask::Instance().SaveEvent(this);
	return 0;
}

int32 spt::SalSjRecordGroup::SaveAll()
{
	return save2File("srecord");
}

int32 spt::SalSjRecordGroup::SaveAppend()
{
	uint32 reader = hdr.reader % hdr.elementPoolSize;
	uint32 writer = hdr.writer % hdr.elementPoolSize;
	if (isUpdate == 0)
	{
		if (writer == reader)
		{
			return 0;
		}
	}
	isUpdate = 0;
	//存储为文件
	hdr.reader = hdr.writer % hdr.elementPoolSize;
	savehdr.reader = reader;
	savehdr.writer = writer;
	savehdr.validNum = hdr.validNum;
	savehdr.usdNum = hdr.usdNum;
	save2File("srecord");
	save2File("srbak");
	//可以在此处进行事项的分发
	return 0;
}

bool8 spt::SalSjRecordGroup::HasNew()
{
	return (hdr.reader != hdr.writer) || isUpdate;
}

const SalSjRecordHdr& spt::SalSjRecordGroup::Header()
{
	return hdr;
}

void spt::SalSjRecordGroup::ClearEvent()
{
	for (uint32 i = 0; i < hdr.elementPoolSize; i++)
	{
		SalSjRecordData* record = (SalSjRecordData*)buf.BufBase();
		record[i].stamp[0] = 0;
	}
	hdr.writer = hdr.reader = hdr.validNum = hdr.usdNum = 0;
	save2File("srecord");
	save2File("srbak");
}

int32 spt::SalSjRecordGroup::save2File(const char* exName)
{
	savehdr.reader = savehdr.writer % savehdr.elementPoolSize;
	SalFile file;
	file.Path().Set(CN_SJRECORD_FILE_ROOT);
	String100B str;
	str = savehdr.fileName;
	str << "." << exName;
	file.Name().Set(str.Str());
	file.Creat();
	savehdr.AddSum();
	file.Write(&savehdr, sizeof(savehdr));
	SalSjRecordData* record = (SalSjRecordData*)buf.BufBase();
	if (!record)
	{
		LogErr.Stamp() << str << "buf err.\n";
		return -1;
	}
	file.Write(record, savehdr.elementPoolSize * savehdr.elementSize);
	file.Close();
	return 0;
}

int32 spt::SalSjRecordGroup::bak2File()
{
	SalFile ofile, nfile;
	ofile.Path().Set(CN_SJRECORD_FILE_ROOT);
	String100B str;
	str = hdr.fileName;
	str << ".srecord";
	ofile.Name().Set(str.Str());
	ofile.OpenReadOnly();
	nfile.Path().Set(CN_BAK_FILE_ROOT CN_FILE_DivFlag CN_SJRECORD_FILE_ROOT);
	nfile.Name().Set(str.Str());
	nfile.Creat();
	nfile.Copy(ofile);
	return 0;
}

int32 spt::SalSjRecordGroup::loadFile()
{
	SalFile file;
	file.Path().Set(CN_SJRECORD_FILE_ROOT);
	String100B str;
	str = hdr.fileName;
	str << ".srecord";
	file.Name().Set(str.Str());

	if (!file.IsExist())
	{
		LogErr.Stamp() << str << " not exist.\n";
		return -1;
	}

	file.OpenReadOnly();

	SalSjRecordHdr hd;

	file.Read(&hd, sizeof(hd));

	if (!hd.IsSumOk())
	{
		hd.IsSumOk();
		LogErr.Stamp() << str << hd.sum << hd.CalcSum() << " sum err.\n";
		return -1;
	}
	if (hd.elementSize != hdr.elementSize)
	{
		LogErr.Stamp() << str << " elementSize err.\n";
		return -1;
	}
	hdr.reader = hd.reader % hd.elementPoolSize;
	hdr.writer = hd.writer % hd.elementPoolSize;
	hdr.usdNum = hd.usdNum % hd.elementPoolSize;
	hdr.validNum = 0;
	SalSjRecordData* record = (SalSjRecordData*)buf.BufBase();
	if (!record)
	{
		LogErr.Stamp() << str << " buf err.\n";
		return -1;
	}
	file.Read(record, hdr.elementPoolSize * hdr.elementSize);
	for (uint32 i = 0; i < hdr.elementPoolSize; i++)
	{
		if (record[i].IsRecordOk())
		{
			hdr.validNum++;
		}
	}
	if (hdr.validNum > hdr.usdNum)
	{
		hdr.validNum = hdr.usdNum;
	}
	return 0;
}

uint32 spt::SalSjRecordHdr::CalcSum()
{
	uint8* sur = (uint8*)this;
	uint8* end = (uint8*)&this->sum;
	uint32 Sum = 0;
	while (sur < end)
	{
		Sum += *sur++;
	}
	return Sum;
}

bool8 spt::SalSjRecordHdr::IsSumOk()
{
	return sum == CalcSum();
}

uint32 spt::SalSjRecordHdr::AddSum()
{
	return sum = CalcSum();
}

int32 spt::SalSjRecordDispachTask::PowerUpIni(int32 Para)
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

int32 spt::SalSjRecordDispachTask::OneLoop()
{
	TaskStep task = (TaskStep)taskStep;
	switch (task)
	{
	case spt::SalSjRecordDispachTask::E_PowerUpIni:
	{
		taskStep = E_Work;
	}
	break;
	case spt::SalSjRecordDispachTask::E_Work:
	{
		CheckLoadEnd();
		int32 res = saveSem.Wait(10000);
		CheckLoadStart();
		saveSemCnt = 0;
		MsSleep(2);
		if ((saveStep == E_BeginSave) || (res == 0))
		{
			SalSjRecordGroup* group;
			InstObjectGroupParent* gp = InstObjectRoot::Instance().GetGroupParent(EIOT_SJRecord);
			uint32 num = gp->InstNum();
			for (uint32 i = 0; i < num; i++)
			{
				InstObjectGroup* g = gp->GetGroup(i);
				if (g)
				{
					group = (SalSjRecordGroup*)g;
					if (group->HasNew())
					{
						if (SptIoProcess::Instance().SptFlag().IsPowerDownAtRange(saveLowLimit, saveHighLimit))
						{
							return 0;
						}
						group->SaveAppend();
						MsSleep(20);
					}
				}
			}
		}
	}
	break;
	default:
		break;
	}
	MsSleep(20);
	return 0;
}

int32 spt::SalSjRecordDispachTask::SaveEvent(SalSjRecordGroup* EventGroup)
{
	if (saveSemCnt < 2)
	{
		saveStep = E_BeginSave;
		saveSem.Post();
		saveSemCnt++;
	}
	return 0;
}

spt::SalSjRecordDispachTask::SalSjRecordDispachTask()
	:Task("tSjRecord", TaskBasePriority - 60, 1024 * 1024, E_T_FLOAT, E_ServiceCore)
{

}
