#ifndef APISJRECORD_H
#define APISJRECORD_H

namespace spt
{
	/// <summary>
	/// 审计记录队列
	/// 审计记录必须在单个线程中调用，禁止保护中断与其他进程公用一个队列
	/// </summary>
	class ApiSjRecordGroup :protected SalSjRecordGroup
	{
	public:
		int32 PowerUpIni(const char* Name, const char* DesName, uint32 PoolSize);
		/// <summary>
		/// 生成审计记录
		/// </summary>
		/// <param name="Process">进程</param>
		/// <param name="Usr">用户</param>
		/// <param name="Object">客体</param>
		/// <param name="Result">结果</param>
		/// <param name="exInfo1">附加信息1</param>
		/// <param name="exInfo2">附加信息2</param>
		/// <param name="exInfo3">附加信息3</param>
		/// <returns></returns>
		int32 CreatRecord(const char* Process, const char* Usr, const char* Object, const char* Result, const char* exInfo1, const char* exInfo2, const char* exInfo3);
		/// <summary>
		/// 生成审计记录
		/// </summary>
		/// <param name="Stamp">时间戳</param>
		/// <param name="Process">进程</param>
		/// <param name="Usr">主体</param>
		/// <param name="Object">客体</param>
		/// <param name="Result">结果</param>
		/// <param name="exInfo1">附加信息1</param>
		/// <param name="exInfo2">附加信息2</param>
		/// <param name="exInfo3">附加信息3</param>
		/// <returns></returns>
		int32 CreatRecord(SalDateStamp& Stamp, const char* Process, const char* Usr, const char* Object, const char* Result, const char* exInfo1, const char* exInfo2, const char* exInfo3);
		/// <summary>
		/// 清空审计记录
		/// </summary>
		void ClearEvent();
		/// <summary>
		/// 有效记录个数
		/// </summary>
		/// <returns></returns>
		uint16 ValidNum();
		/// <summary>
		/// 审计记录生成总个数
		/// </summary>
		/// <returns></returns>
		uint16 CreatNum();
		/// <summary>
		/// 缓冲区大小
		/// </summary>
		/// <returns></returns>
		uint16 PoolSize();
	};
	/// <summary>
	/// Hmi事项查看缓冲区
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