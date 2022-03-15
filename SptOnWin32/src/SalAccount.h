#ifndef SalAccount_H
#define SalAccount_H
namespace spt
{
	class SalUserAccount
	{
	public:
		typedef struct
		{
			bool8 isValid;
			bool8 isEnable;
			uint8 type;
			bool8 pwtype;
			bool8 menuAllow[16];
			uint32 id;
			char account[16];
			char password[16];
			uint32 sum;
		}UserAccountSaveData;
		typedef struct
		{
			uint32 size;
			uint32 logErrCnt;//�������
			bool8 isLock;
			bool8 isDefaultPw;
			uint64 lastLogTime;
			uint64 firstErrTime;
			uint64 lastErrTime;
			uint64 lastPwChagneTime;
		}UserAccountStatus;
		struct Status
		{

		};
		struct Output
		{

		};
		enum UserPassType
		{
			E_UPT_Sample,//������Ҫ��
			E_UPT_Pc,//PC�˺�����Ҫ��
		};
		enum UserType
		{
			E_UT_Guest,//�ο�
			E_UT_Admin,//����Ա
			E_UT_Comptroller,//���Ա
			E_UT_Operator,//����Ա
			E_UT_Maintainer,//ά��Ա
			E_UT_OperAndMaintainer,//��ά��Ա
			E_UT_Debuger,//��ȱ��Ա
		};
	public:
		UserType Type()const;
		UserPassType PwType()const;
		const char* Name()const;
		int32 NewUser(const char* Account, uint8 AcType, uint32 Id, const char* Pw, uint8 PwType, bool8 IsDefault);
		uint32 UpdateSum();
		uint32 CalSum();
		bool8 IsSumOk();
		bool8 SetStaus(UserAccountStatus* Status);
		bool8 SetPassWord(const char* Pw);
		int32 LogOnce(const char* Pw);
		bool8 IsLocked();
		bool8 IsLocked()const;
		bool8 IsValid()const;
		//�����Ƿ�ΪĬ��ֵ
		bool8 IsDefaultPw()const;
		bool8 IsEnable()const;
		bool8 ResetLockStatus();
		int32 DeleteUser();
		int32 EnableUser(bool8 Enable);
		//ƽ̨���֧��16��������Ȩ��
		bool8 IsAllowEnter(uint32 MenuIndex)const;
		bool8 SetAllowEnter(uint32 MenuIndex, bool8 Enable);
	private:
		UserAccountSaveData data;
		UserAccountStatus status;
		friend class SalUserPool;
		friend class SalUserMng;
	};

	class SalUserPool
	{
	public:
		union Account
		{
			SalUserAccount::UserAccountSaveData data;
			uint32 buf[16];
		};
		static const uint32 MaxUserNum = 20;
		union AccountPool
		{
			struct Data
			{
				uint32 Num;
				uint32 ValidNum;
				Account account[MaxUserNum];
				uint32 crc;
			}data;
			uint8 buf[((sizeof(Data) / 16) + 1) * 16];
		};
		union AccountStatus
		{
			SalUserAccount::UserAccountStatus status[MaxUserNum];
		};
	public:
		void IniPool();
		bool8 IsUserExist(const char* Account);
		bool8 IsFull();
		const SalUserAccount* GetUser(const char* Account);
		const SalUserAccount* GetUser(uint32 Id);
		const AccountPool& Pool();
		const AccountStatus& Status();
		int32 AddNewUser(const char* Account, uint8 AcType, const char* Pw, uint8 PwType, bool8 IsDefault);
		int32 SetNewPassWord(const char* Account, const char* Pw);
		bool8 SetAllowEnter(const char* Account, uint16 MenuIndex, bool8 Enable);
		int32 ResetUserLockStatus(const char* Account);
		int32 DeleteUser(const char* Account);
		int32 EnableUser(const char* Account, bool8 Enable);
		//-4 ���벻��ȷ
		//-5 �����ѳ���
		int32 UserLog(const char* Account, const char* Pw);
		bool8 IsAccountLocked(const char* Account);
		uint32 CalcCrc();
		uint32 UpdateCrc();
		bool8 IsCrcOk();
		void SaveStatus();
		void LoadStatus();
		bool8 SavePool();
		int32 LoadPool();
	protected:
		AccountPool pool;
		AccountStatus status;
		SalUserAccount usr[MaxUserNum];
	};
	/// <summary>
	/// �˺ŵ�¼����
	/// </summary>
	class SalUsrCfg :public CfgFile
	{
	public:
		int32 PowerUpIni(int32 Para);
	public:
		/// <summary>
		/// �����˺�ϵͳ
		/// </summary>
		CfgBool EnableAccount;
		/// <summary>
		/// �Զ��˳�ʱ��
		/// </summary>
		CfgUint32 AutoExitTime;
		/// <summary>
		/// ��������������
		/// </summary>
		CfgUint32 PasswordErrCnt;
		/// <summary>
		/// �����������ʱ��
		/// </summary>
		CfgUint32 PasswordLockTime;
		/// <summary>
		/// ʹ�����볬�ڼ��
		/// </summary>
		CfgBool EnablePassWordOverTime;
		/// <summary>
		/// ���볬��ʱ��
		/// </summary>
		CfgUint32 PassWordOverTime;
	private:
		PCfgDataBase pool[20];
	protected:
		virtual PCfgDataBase* CfgPool() { return pool; };
		virtual uint32 CfgPoolSize() { return M_ArrLen(pool); };
	};
	/// <summary>
	/// �˺Ź���
	/// </summary>
	class SalUserMng
	{
	public:
		SalUsrCfg UsrCfg;
	public:
		M_Singleton(SalUserMng);
		int32 PowerUpIni();
		/// <summary>
		/// �½��˺�
		/// </summary>
		/// <param name="Account"></param>
		/// <param name="AcType"></param>
		/// <param name="Pw"></param>
		/// <param name="PwType"></param>
		/// <param name="IsDefault"></param>
		/// <returns>0 �ɹ�
		/// -1,Account��Pwһ�£�������˺�
		/// -2,Account�Ѵ���
		///-3�����볤�Ȳ�����Ҫ��
		///-4������ǿ�Ȳ�����Ҫ��
		///-5,�˺Ż���������
		///-6,Account�쳣
		/// </returns>
		int32 CreatNewUser(const char* Account, uint8 AcType, const char* Pw, uint8 PwType, bool8 IsDefault);
		///0 �ɹ�
		///-1,Account��Pwһ�£�������˺�
		///-2,Account������
		///-3�����볤�Ȳ�����Ҫ��
		///-4������ǿ�Ȳ�����Ҫ��
		int32 SetNewPassWord(const char* Account, const char* Pw);
		//0 �ɹ�
		//-1, Account������
		//-2��Account�ѱ�����
		//-3��Account��ͣ��
		//-4��Account���벻��ȷ
		//-5, �����ѳ���
		//-6��Account����������Ӧ�γ���Ƽ�¼
		int32 UserLog(const char* Account, const char* Pw);
		//�˺��Ƿ����
		bool8 IsAccountExist(const char* Account);
		bool8 IsAccountLocked(const char* Account);
		bool8 IsAllowEnter(const char* Account, const uint16 MenuIndex);
		bool8 SetAllowEnter(const char* Account, uint16 MenuIndex, bool8 Enable);
		const SalUserAccount* GetUser(const char* Account);
		int32 ResetUserLockStatus(const char* Account);
		/// <summary>
		/// ɾ���˺�
		/// </summary>
		/// <param name="Account"></param>
		/// <returns>
		/// 0��ɾ���ɹ�
		/// -1��ɾ��ʧ��
		/// </returns>
		int32 DeleteUser(const char* Account);
		int32 EnableUser(const char* Account, bool8 Enable);
		const SalUserAccount* GetUser(uint32 Id);
		int32 IniUserPool();
		int32 LoadPool();
	protected:
		SalUserMng();
		bool8 IsPassWordOk(const char* Pw, uint8 type);
		bool8 IsIdOk(const char* Id, uint8 type);
	protected:
		SalUserPool* pool;
	};
}
#endif
