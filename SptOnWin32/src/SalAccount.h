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
			uint32 logErrCnt;//错误次数
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
			E_UPT_Sample,//简单密码要求
			E_UPT_Pc,//PC账号密码要求
		};
		enum UserType
		{
			E_UT_Guest,//游客
			E_UT_Admin,//管理员
			E_UT_Comptroller,//审计员
			E_UT_Operator,//操作员
			E_UT_Maintainer,//维护员
			E_UT_OperAndMaintainer,//运维人员
			E_UT_Debuger,//消缺人员
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
		//密码是否为默认值
		bool8 IsDefaultPw()const;
		bool8 IsEnable()const;
		bool8 ResetLockStatus();
		int32 DeleteUser();
		int32 EnableUser(bool8 Enable);
		//平台最大支持16个独立的权限
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
		//-4 密码不正确
		//-5 密码已超期
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
	/// 账号登录配置
	/// </summary>
	class SalUsrCfg :public CfgFile
	{
	public:
		int32 PowerUpIni(int32 Para);
	public:
		/// <summary>
		/// 启用账号系统
		/// </summary>
		CfgBool EnableAccount;
		/// <summary>
		/// 自动退出时间
		/// </summary>
		CfgUint32 AutoExitTime;
		/// <summary>
		/// 允许密码错误次数
		/// </summary>
		CfgUint32 PasswordErrCnt;
		/// <summary>
		/// 密码错误锁定时间
		/// </summary>
		CfgUint32 PasswordLockTime;
		/// <summary>
		/// 使能密码超期检测
		/// </summary>
		CfgBool EnablePassWordOverTime;
		/// <summary>
		/// 密码超期时间
		/// </summary>
		CfgUint32 PassWordOverTime;
	private:
		PCfgDataBase pool[20];
	protected:
		virtual PCfgDataBase* CfgPool() { return pool; };
		virtual uint32 CfgPoolSize() { return M_ArrLen(pool); };
	};
	/// <summary>
	/// 账号管理
	/// </summary>
	class SalUserMng
	{
	public:
		SalUsrCfg UsrCfg;
	public:
		M_Singleton(SalUserMng);
		int32 PowerUpIni();
		/// <summary>
		/// 新建账号
		/// </summary>
		/// <param name="Account"></param>
		/// <param name="AcType"></param>
		/// <param name="Pw"></param>
		/// <param name="PwType"></param>
		/// <param name="IsDefault"></param>
		/// <returns>0 成功
		/// -1,Account与Pw一致，或包含账号
		/// -2,Account已存在
		///-3，密码长度不符合要求
		///-4，密码强度不符合要求
		///-5,账号缓冲区已满
		///-6,Account异常
		/// </returns>
		int32 CreatNewUser(const char* Account, uint8 AcType, const char* Pw, uint8 PwType, bool8 IsDefault);
		///0 成功
		///-1,Account与Pw一致，或包含账号
		///-2,Account不存在
		///-3，密码长度不符合要求
		///-4，密码强度不符合要求
		int32 SetNewPassWord(const char* Account, const char* Pw);
		//0 成功
		//-1, Account不存在
		//-2，Account已被锁定
		//-3，Account已停用
		//-4，Account密码不正确
		//-5, 密码已超期
		//-6，Account初次锁定，应形成审计记录
		int32 UserLog(const char* Account, const char* Pw);
		//账号是否存在
		bool8 IsAccountExist(const char* Account);
		bool8 IsAccountLocked(const char* Account);
		bool8 IsAllowEnter(const char* Account, const uint16 MenuIndex);
		bool8 SetAllowEnter(const char* Account, uint16 MenuIndex, bool8 Enable);
		const SalUserAccount* GetUser(const char* Account);
		int32 ResetUserLockStatus(const char* Account);
		/// <summary>
		/// 删除账号
		/// </summary>
		/// <param name="Account"></param>
		/// <returns>
		/// 0，删除成功
		/// -1，删除失败
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
