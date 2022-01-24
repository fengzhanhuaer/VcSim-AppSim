#ifndef APISJRECORD_H
#define APISJRECORD_H

namespace spt
{
	/// <summary>
	/// ��Ƽ�¼����
	/// ��Ƽ�¼�����ڵ����߳��е��ã���ֹ�����ж����������̹���һ������
	/// </summary>
	class ApiSjRecordGroup :protected SalSjRecordGroup
	{
	public:
		int32 PowerUpIni(const char* Name, const char* DesName, uint32 PoolSize);
		int32 CreatRecord(const char* Process, const char* Usr, const char* Object, const char* Result, const char* exInfo1, const char* exInfo2, const char* exInfo3);
		void ClearEvent();
	};
	/// <summary>
	/// Hmi����鿴������
	/// </summary>
	struct ApiSjRecordViewPool
	{
		uint32 recordPoolLen;
		uint32 validRecordNum;
		SalSjRecordData* record;
		void GetValid(SalSjRecordGroup* Group, uint64 TimeStart, uint64 TimeEnd);
		void PowerUpIni(uint32 PoolSize);
		int32 ExportCsv(SalSjRecordGroup* Group, int32 Type);
	};
}

#endif