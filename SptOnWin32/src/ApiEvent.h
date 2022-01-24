#ifndef APIEVENT_H
#define APIEVENT_H

namespace spt
{
	/// <summary>
	/// 状态量
	/// </summary>
	class ApiStatus :protected SalStatus
	{
	public:
		//如果有变位则产生默认的时标更新事项
		bool8 Update(uint32 Status);
		//如果有变位则产生指定的时标更新事项
		bool8 Update(uint32 Status, SalDateStamp& stamp);
		//如果有变位则产生指定的时标更新事项,使用指定的品质位
		bool8 Update(uint32 Status, SalDateStamp& stamp, StatusQ& Q);
		/// <summary>
		/// 设置状态
		/// </summary>
		/// <param name="Status"></param>
		/// <param name="stamp"></param>
		/// <param name="Q"></param>
		/// <returns></returns>
		bool8 SetState(uint32 Status, SalDateStamp& stamp, StatusQ& Q);
		//状态量
		const u32value& Value()const;
		//状态量
		const u32value& OldValue()const;
		void SetDisp(bool8 Disp);//设置是否对外展示
		//布尔型事项
		//HoldOn 是否掉电保持
		//flags bit定义参见SalStatus::Flags
		void BlPowerUpIni(const char* Name, const char* DesName, class ApiStatusGroup& Group, uint32 flags);
		//HoldOn 是否掉电保持
		//flags bit定义参见SalStatus::Flags
		void DpPowerUpIni(const char* Name, const char* DesName, class ApiStatusGroup& Group, uint32 flags);
		//附加信息初始化
		void ExInfoPowerUpIni(StatusExInfoDesItem* Inf1, StatusExInfoDesItem* Inf2, StatusExInfoDesItem* Inf3);
		void ExInfoPowerUpIni(StatusExInfoDesItem* Inf1, StatusExInfoDesItem* Inf2, StatusExInfoDesItem* Inf3, StatusExInfoDesItem* Inf4, StatusExInfoDesItem* Inf5, StatusExInfoDesItem* Inf6);
		void ExInfoPowerUpIni(StatusExInfoDesItem* Inf1, StatusExInfoDesItem* Inf2, StatusExInfoDesItem* Inf3, StatusExInfoDesItem* Inf4, StatusExInfoDesItem* Inf5, StatusExInfoDesItem* Inf6, StatusExInfoDesItem* Inf7, StatusExInfoDesItem* Inf8, StatusExInfoDesItem* Inf9);	//双点型事项
		/// <summary>
		/// 更新状态量
		/// </summary>
		/// <param name="S1"></param>
		/// <param name="S2"></param>
		/// <param name="S3"></param>
		void UpdateStatus(u32value S1, u32value S2, u32value S3);
		void UpdateStatus(u32value S1, u32value S2, u32value S3, u32value S4, u32value S5, u32value S6);
		void UpdateStatus(u32value S1, u32value S2, u32value S3, u32value S4, u32value S5, u32value S6, u32value S7, u32value S8, u32value S9);
	protected:
	};
	class ApiStatusGroup :protected SalStatusGroup
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint16 EventNum);
		void PowerUpIni(const char* Name, const char* DesName, uint16 EventNum, SalEnumDes* BoardDes, uint8 BoardTypeNum, uint8 BoardIndex);
	};
	/// <summary>
	/// 事件
	/// 事件是状态量的瞬时状态的快照
	/// </summary>
	class ApiEvent :protected SalEvent
	{
	public:
		//如果有变位则产生默认的时标更新事项
		bool8 Update(uint32 Status);
		//如果有变位则产生指定的时标更新事项
		bool8 Update(uint32 Status, SalDateStamp& stamp);
		//如果使用指定的品质位更新事项
		bool8 Update(uint32 Status, StatusQ& Q);
		//如果有变位则产生指定的时标更新事项,使用指定的品质位
		bool8 Update(uint32 Status, SalDateStamp& stamp, StatusQ& Q);
		/// <summary>
		/// 设置事项状态
		/// 产生一条事项，用于设置事项的状态，但不存入缓冲区，仅用于驱动后台通讯、界面显示状态的初始值
		/// </summary>
		/// <param name="Status"></param>
		/// <param name="stamp"></param>
		/// <param name="Q"></param>
		/// <returns></returns>
		bool8 SetState(uint32 Status, SalDateStamp& stamp, StatusQ& Q);
		const u32value& Value()const;
		const u32value& OldValue()const;
		void SetDisp(bool8 Disp);//设置是否对外展示
		//布尔型事项
		//flags bit定义参见SalStatus::Flags
		void BlPowerUpIni(const char* Name, const char* DesName, class ApiEventGroup& Group, uint32 flag);
		//双点型事项
		//flags bit定义参见SalStatus::Flags
		void DpPowerUpIni(const char* Name, const char* DesName, class ApiEventGroup& Group, uint32 flag);
		//Hex8事项
		//flags bit定义参见SalStatus::Flags
		void Hex8PowerUpIni(const char* Name, const char* DesName, class ApiEventGroup& Group, uint32 flag);
		//Hex16事项
		//flags bit定义参见SalStatus::Flags
		void Hex16PowerUpIni(const char* Name, const char* DesName, class ApiEventGroup& Group, uint32 flag);
		//附加信息初始化
		void ExInfoPowerUpIni(StatusExInfoDesItem* Inf1, StatusExInfoDesItem* Inf2, StatusExInfoDesItem* Inf3);
		void ExInfoPowerUpIni(StatusExInfoDesItem* Inf1, StatusExInfoDesItem* Inf2, StatusExInfoDesItem* Inf3, StatusExInfoDesItem* Inf4, StatusExInfoDesItem* Inf5, StatusExInfoDesItem* Inf6);
		void ExInfoPowerUpIni(StatusExInfoDesItem* Inf1, StatusExInfoDesItem* Inf2, StatusExInfoDesItem* Inf3, StatusExInfoDesItem* Inf4, StatusExInfoDesItem* Inf5, StatusExInfoDesItem* Inf6, StatusExInfoDesItem* Inf7, StatusExInfoDesItem* Inf8, StatusExInfoDesItem* Inf9);
		/// <summary>
		/// 更新状态量
		/// </summary>
		/// <param name="S1"></param>
		/// <param name="S2"></param>
		/// <param name="S3"></param>
		void UpdateStatus(u32value S1, u32value S2, u32value S3);
		void UpdateStatus(u32value S1, u32value S2, u32value S3, u32value S4, u32value S5, u32value S6);
		void UpdateStatus(u32value S1, u32value S2, u32value S3, u32value S4, u32value S5, u32value S6, u32value S7, u32value S8, u32value S9);
	protected:

	};

	class ApiEventGroup :protected SalEventGroup
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint16 EventNum, uint32 EventPoolSize);
		void PowerUpIni(const char* Name, const char* DesName, uint16 EventNum, uint32 EventPoolSize, SalEnumDes* BoardDes, uint8 BoardTypeNum, uint8 BoardIndex);
		/// <summary>
		/// 清空事项队列
		/// </summary>
		void ClearEvent();
	};
	/// <summary>
	/// Hmi事项查看缓冲区
	/// </summary>
	struct ApiEventViewPool
	{
		uint32 recordPoolLen;
		uint32 validRecordNum;
		StatusData* record;
		/// <summary>
		/// 获取有效的事项个数
		/// </summary>
		/// <param name="Group"></param>
		/// <param name="TimeStart"></param>
		/// <param name="TimeEnd"></param>
		/// <param name="isDisp">是否用于显示</param>
		void GetValid(SalEventGroup* Group, uint64 TimeStart, uint64 TimeEnd, bool8 isDisp);
		void PowerUpIni(uint32 PoolSize);
	};

}

#endif // !APIEVENT_H

