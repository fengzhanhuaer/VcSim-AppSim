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
		/// <summary>
		/// ������Ƽ�¼
		/// </summary>
		/// <param name="Process">����</param>
		/// <param name="Usr">�û�</param>
		/// <param name="Object">����</param>
		/// <param name="Result">���</param>
		/// <param name="exInfo1">������Ϣ1</param>
		/// <param name="exInfo2">������Ϣ2</param>
		/// <param name="exInfo3">������Ϣ3</param>
		/// <returns></returns>
		int32 CreatRecord(const char* Process, const char* Usr, const char* Object, const char* Result, const char* exInfo1, const char* exInfo2, const char* exInfo3);
		/// <summary>
		/// ������Ƽ�¼
		/// </summary>
		/// <param name="Stamp">ʱ���</param>
		/// <param name="Process">����</param>
		/// <param name="Usr">����</param>
		/// <param name="Object">����</param>
		/// <param name="Result">���</param>
		/// <param name="exInfo1">������Ϣ1</param>
		/// <param name="exInfo2">������Ϣ2</param>
		/// <param name="exInfo3">������Ϣ3</param>
		/// <returns></returns>
		int32 CreatRecord(SalDateStamp& Stamp, const char* Process, const char* Usr, const char* Object, const char* Result, const char* exInfo1, const char* exInfo2, const char* exInfo3);
		/// <summary>
		/// �����Ƽ�¼
		/// </summary>
		void ClearEvent();
		/// <summary>
		/// ��Ч��¼����
		/// </summary>
		/// <returns></returns>
		uint16 ValidNum();
		/// <summary>
		/// ��Ƽ�¼�����ܸ���
		/// </summary>
		/// <returns></returns>
		uint16 CreatNum();
		/// <summary>
		/// ��������С
		/// </summary>
		/// <returns></returns>
		uint16 PoolSize();
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