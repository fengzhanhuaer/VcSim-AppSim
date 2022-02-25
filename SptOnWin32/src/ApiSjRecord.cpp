#include"ApiProject.h"
using namespace spt;

int32 spt::ApiSjRecordGroup::PowerUpIni(const char* Name, const char* DesName, uint32 PoolSize)
{
	SalSjRecordGroup::PowerUpIni(Name, DesName, 10, PoolSize);
	return 0;
}

int32 spt::ApiSjRecordGroup::CreatRecord(const char* Process, const char* Usr, const char* Object, const char* Result, const char* exInfo1, const char* exInfo2, const char* exInfo3)
{
	SalSjRecordData re;
	re.StampNow();
	re.SetRecord(Process, Usr, Object, Result, exInfo1, exInfo2, exInfo3);
	SalSjRecordGroup::CreatEvent(re);
	return 0;
}
int32 spt::ApiSjRecordGroup::CreatRecord(SalDateStamp& Stamp, const char* Process, const char* Usr, const char* Object, const char* Result, const char* exInfo1, const char* exInfo2, const char* exInfo3)
{
	SalSjRecordData re;
	re.SetStamp(Stamp);
	re.SetRecord(Process, Usr, Object, Result, exInfo1, exInfo2, exInfo3);
	SalSjRecordGroup::CreatEvent(re);
	return 0;
}
void spt::ApiSjRecordGroup::ClearEvent()
{
	SalSjRecordGroup::ClearEvent();
}
void spt::ApiSjRecordViewPool::GetValid(SalSjRecordGroup* Group, uint64 TimeStart, uint64 TimeEnd)
{
	uint32 Num = Group->ValidNum();
	if (Num >= recordPoolLen)
	{
		Num = recordPoolLen;
	}
	uint32 valiNum = 0;
	SalDateStamp temp;
	int32 base = Group->OldestRecordIndex();
	for (uint32 i = 0; i < Num; i++)
	{
		base = Group->GetNextValidEvent(base, 0, record[valiNum]);
		if (base < 0)
		{
			break;
		}
		base++;
		if (0 == record[valiNum].IsRecordOk())
		{
			continue;
		}
		record[valiNum].GetStamp(temp);
		if (((uint64)temp.Us() >= TimeStart && ((uint64)temp.Us() <= TimeEnd)))
		{
			valiNum++;
		}
	}
	validRecordNum = valiNum;
}
void spt::ApiSjRecordViewPool::PowerUpIni(uint32 PoolSize)
{
	recordPoolLen = PoolSize;
	validRecordNum = 0;
	record = (SalSjRecordData*)Calloc(sizeof(SalSjRecordData), recordPoolLen);
	if (record == 0)
	{
		LogErr.Stamp() << "HmiSjRecordViewPool Calloc err.\n";
	}
}

int32 spt::ApiSjRecordViewPool::ExportCsv(SalSjRecordGroup* Group, int32 Type)
{
	const SalSjRecordHdr& hdr = Group->Header();
	SalFile file;
	file.Path().Set(CN_SJRECORD_FILE_ROOT);
	String500B str;
	str = hdr.fileName;
	str << ".csv";
	file.Name().Set(str.Str());
	file.Creat();
	str = "时间,组件,主体,客体,结果,信息1,信息2,信息3\n";
	file.Write(str.Str());
	for (uint32 i = 0; i < validRecordNum; i++)
	{
		str = record[i].stamp; str << ",";
		str << record[i].process; str << ",";
		str << record[i].usr; str << ",";
		str << record[i].object; str << ",";
		str << record[i].result; str << ",";
		str << record[i].exInfo1; str << ",";
		str << record[i].exInfo2; str << ",";
		str << record[i].exInfo3; str << "\n";
		file.Write(str.Str());
	}
	return 0;
}
