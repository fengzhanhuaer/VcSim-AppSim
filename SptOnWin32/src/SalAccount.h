#ifndef SalAccount_H
#define SalAccount_H
namespace spt
{
	class SalUserAccount
	{
	public:
		typedef union
		{
			struct Data
			{
				uint16 size;
				bool8 isValid;
				bool8 isEnable;
				uint8 type;
				bool8 pwtype;//UserPassType
				bool8 isLock;
				bool8 isDefaultPw;
				bool8 menuAllow[16];
				uint32 id;
				char account[16];
				char password[16];
				uint32 logErrCnt;//错误次数
				uint64 lastLogTime;
				uint64 firstErrTime;
				uint64 lastErrTime;
				uint64 lastPwChagneTime;
				uint32 sum;
			}data;
			uint8 buf[512];
		}SaveData;
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
		SaveData data;
		friend class SalUserMng;
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
		static const uint32 MaxUserNum = 20;
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
		///-1,Account与Pw一致，或包含账号
		///-2,Account已存在
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
		/// <summary>
		/// 账号是否存在
		/// </summary>
		/// <param name="Account"></param>
		/// <returns></returns>
		bool8 IsAccountExist(const char* Account);
		/// <summary>
		/// 帐号是否锁定
		/// </summary>
		/// <param name="Account"></param>
		/// <returns>帐号不存在时返回零</returns>
		bool8 IsAccountLocked(const char* Account);
		/// <summary>
		/// 获取帐号权限
		/// </summary>
		/// <param name="Account"></param>
		/// <param name="MenuIndex"></param>
		/// <returns></returns>
		bool8 IsAllowEnter(const char* Account, const uint16 MenuIndex);
		/// <summary>
		/// 设置帐号权限
		/// </summary>
		/// <param name="Account"></param>
		/// <param name="MenuIndex"></param>
		/// <param name="Enable"></param>
		/// <returns></returns>
		bool8 SetAllowEnter(const char* Account, uint16 MenuIndex, bool8 Enable);
		/// <summary>
		/// 获取用户
		/// </summary>
		/// <param name="Account"></param>
		/// <returns></returns>
		const SalUserAccount* GetUser(const char* Account);
		/// <summary>
		/// 获取帐号
		/// </summary>
		/// <param name="Id"></param>
		/// <returns></returns>
		const SalUserAccount* GetUser(uint32 Id);
		/// <summary>
		/// 复位帐号锁定状态
		/// </summary>
		/// <param name="Account"></param>
		/// <returns></returns>
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
		/// <summary>
		/// 使能帐号
		/// </summary>
		/// <param name="Account"></param>
		/// <param name="Enable"></param>
		/// <returns></returns>
		int32 EnableUser(const char* Account, bool8 Enable);
		/// <summary>
		/// 重新加载用户数据
		/// </summary>
		/// <returns></returns>
		int32 LoadPool();
		/// <summary>
		/// 是否存在帐号
		/// </summary>
		/// <param name="Account"></param>
		/// <returns></returns>
		bool8 IsUserExist(const char* Account);
		/// <summary>
		/// 帐号池是否满
		/// </summary>
		bool8 IsFull();
	protected:
		int32 IniUser();
		void IniPool();
		int32 LoadPool(const char* Name);
		uint32 UpdateCrc();
		SalUserMng();
		bool8 IsPassWordOk(const char* Pw, uint8 type);
		bool8 IsIdOk(const char* Id, uint8 type);
		bool8 IsCrcOk();
		bool8 SavePool();
		int32 AddNewUser(const char* Account, uint8 AcType, const char* Pw, uint8 PwType, bool8 IsDefault);
	protected:
		union UsrSaveData
		{
			struct Data
			{
				uint32 Num;
				uint32 ValidNum;
				SalUserAccount usr[MaxUserNum];
				uint32 crc;
			}usrdata;
			uint8 buf[(sizeof(usrdata) / 16 + 1) * 16];
		};
		UsrSaveData* pool;
	};
}
#endif
