#ifndef APIEVENT_H
#define APIEVENT_H

namespace spt
{
	/// <summary>
	/// ״̬��
	/// </summary>
	class ApiStatus :protected SalStatus
	{
	public:
		//����б�λ�����Ĭ�ϵ�ʱ���������
		bool8 Update(uint32 Status);
		//����б�λ�����ָ����ʱ���������
		bool8 Update(uint32 Status, SalDateStamp& stamp);
		//����б�λ�����ָ����ʱ���������,ʹ��ָ����Ʒ��λ
		bool8 Update(uint32 Status, SalDateStamp& stamp, StatusQ& Q);
		/// <summary>
		/// ����״̬
		/// </summary>
		/// <param name="Status"></param>
		/// <param name="stamp"></param>
		/// <param name="Q"></param>
		/// <returns></returns>
		bool8 SetState(uint32 Status, SalDateStamp& stamp, StatusQ& Q);
		//״̬��
		const u32value& Value()const;
		//״̬��
		const u32value& OldValue()const;
		void SetDisp(bool8 Disp);//�����Ƿ����չʾ
		//����������
		//HoldOn �Ƿ���籣��
		//flags bit����μ�SalStatus::Flags
		void BlPowerUpIni(const char* Name, const char* DesName, class ApiStatusGroup& Group, uint32 flags);
		//HoldOn �Ƿ���籣��
		//flags bit����μ�SalStatus::Flags
		void DpPowerUpIni(const char* Name, const char* DesName, class ApiStatusGroup& Group, uint32 flags);
		//������Ϣ��ʼ��
		void ExInfoPowerUpIni(StatusExInfoDesItem* Inf1, StatusExInfoDesItem* Inf2, StatusExInfoDesItem* Inf3);
		void ExInfoPowerUpIni(StatusExInfoDesItem* Inf1, StatusExInfoDesItem* Inf2, StatusExInfoDesItem* Inf3, StatusExInfoDesItem* Inf4, StatusExInfoDesItem* Inf5, StatusExInfoDesItem* Inf6);
		void ExInfoPowerUpIni(StatusExInfoDesItem* Inf1, StatusExInfoDesItem* Inf2, StatusExInfoDesItem* Inf3, StatusExInfoDesItem* Inf4, StatusExInfoDesItem* Inf5, StatusExInfoDesItem* Inf6, StatusExInfoDesItem* Inf7, StatusExInfoDesItem* Inf8, StatusExInfoDesItem* Inf9);	//˫��������
		/// <summary>
		/// ����״̬��
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
	/// �¼�
	/// �¼���״̬����˲ʱ״̬�Ŀ���
	/// </summary>
	class ApiEvent :protected SalEvent
	{
	public:
		//����б�λ�����Ĭ�ϵ�ʱ���������
		bool8 Update(uint32 Status);
		//����б�λ�����ָ����ʱ���������
		bool8 Update(uint32 Status, SalDateStamp& stamp);
		//���ʹ��ָ����Ʒ��λ��������
		bool8 Update(uint32 Status, StatusQ& Q);
		//����б�λ�����ָ����ʱ���������,ʹ��ָ����Ʒ��λ
		bool8 Update(uint32 Status, SalDateStamp& stamp, StatusQ& Q);
		/// <summary>
		/// ��������״̬
		/// ����һ������������������״̬���������뻺������������������̨ͨѶ��������ʾ״̬�ĳ�ʼֵ
		/// </summary>
		/// <param name="Status"></param>
		/// <param name="stamp"></param>
		/// <param name="Q"></param>
		/// <returns></returns>
		bool8 SetState(uint32 Status, SalDateStamp& stamp, StatusQ& Q);
		const u32value& Value()const;
		const u32value& OldValue()const;
		void SetDisp(bool8 Disp);//�����Ƿ����չʾ
		//����������
		//flags bit����μ�SalStatus::Flags
		void BlPowerUpIni(const char* Name, const char* DesName, class ApiEventGroup& Group, uint32 flag);
		//˫��������
		//flags bit����μ�SalStatus::Flags
		void DpPowerUpIni(const char* Name, const char* DesName, class ApiEventGroup& Group, uint32 flag);
		//Hex8����
		//flags bit����μ�SalStatus::Flags
		void Hex8PowerUpIni(const char* Name, const char* DesName, class ApiEventGroup& Group, uint32 flag);
		//Hex16����
		//flags bit����μ�SalStatus::Flags
		void Hex16PowerUpIni(const char* Name, const char* DesName, class ApiEventGroup& Group, uint32 flag);
		//������Ϣ��ʼ��
		void ExInfoPowerUpIni(StatusExInfoDesItem* Inf1, StatusExInfoDesItem* Inf2, StatusExInfoDesItem* Inf3);
		void ExInfoPowerUpIni(StatusExInfoDesItem* Inf1, StatusExInfoDesItem* Inf2, StatusExInfoDesItem* Inf3, StatusExInfoDesItem* Inf4, StatusExInfoDesItem* Inf5, StatusExInfoDesItem* Inf6);
		void ExInfoPowerUpIni(StatusExInfoDesItem* Inf1, StatusExInfoDesItem* Inf2, StatusExInfoDesItem* Inf3, StatusExInfoDesItem* Inf4, StatusExInfoDesItem* Inf5, StatusExInfoDesItem* Inf6, StatusExInfoDesItem* Inf7, StatusExInfoDesItem* Inf8, StatusExInfoDesItem* Inf9);
		/// <summary>
		/// ����״̬��
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
		/// ����������
		/// </summary>
		void ClearEvent();
	};
	/// <summary>
	/// Hmi����鿴������
	/// </summary>
	struct ApiEventViewPool
	{
		uint32 recordPoolLen;
		uint32 validRecordNum;
		StatusData* record;
		/// <summary>
		/// ��ȡ��Ч���������
		/// </summary>
		/// <param name="Group"></param>
		/// <param name="TimeStart"></param>
		/// <param name="TimeEnd"></param>
		/// <param name="isDisp">�Ƿ�������ʾ</param>
		void GetValid(SalEventGroup* Group, uint64 TimeStart, uint64 TimeEnd, bool8 isDisp);
		void PowerUpIni(uint32 PoolSize);
	};

}

#endif // !APIEVENT_H

