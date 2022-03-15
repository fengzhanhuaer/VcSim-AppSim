#include"ApiProject.h"
using namespace spt;

SalUserAccount::UserType spt::SalUserAccount::Type()const
{
	return (UserType)(data.type);
}

SalUserAccount::UserPassType spt::SalUserAccount::PwType() const
{
	return (UserPassType)(data.pwtype);
}

const char* spt::SalUserAccount::Name()const
{
	return data.account;
}

int32 spt::SalUserAccount::NewUser(const char* Account, uint8 AcType, uint32 Id, const char* Pw, uint8 PwType, bool8 IsDefault)
{
	SalDateStamp now = SptDateTask::Instance().Now();

	if (!data.isValid)
	{
		MemSet(&data, 0, sizeof(data));
		data.isValid = 1;
		data.isEnable = 1;
		data.type = AcType;
		data.pwtype = PwType;
		status.logErrCnt = 0;
		status.isDefaultPw = IsDefault;
		data.id = Id;
		status.lastLogTime = now.Us();
		status.lastPwChagneTime = now.Us();
		status.firstErrTime = now.Us();
		status.lastErrTime = now.Us();
		status.size = sizeof(status);
		StrNCpy(data.account, Account, sizeof(data.account));
		StrNCpy(data.password, Pw, sizeof(data.password));
		for (uint32 i = 0; i < sizeof(data.menuAllow); i++)
		{
			data.menuAllow[i] = 0;
		}
	}
	UpdateSum();
	return 0;
}

uint32 spt::SalUserAccount::UpdateSum()
{
	return data.sum = CalSum();
}

uint32 spt::SalUserAccount::CalSum()
{
	uint32 sum = 0;
	uint32 l = sizeof(data) - sizeof(sum);
	uint8* sur = (uint8*)&data;
	for (uint32 i = 0; i < l; i++)
	{
		sum += sur[i];
	}
	return  sum;
}

bool8 spt::SalUserAccount::IsSumOk()
{
	return CalSum() == data.sum;
}

bool8 spt::SalUserAccount::SetStaus(UserAccountStatus* Status)
{
	if (Status->size != sizeof(status))
	{
		MemSet(&status, 0, sizeof(status));
		Status->size = status.size = sizeof(status);
		return 0;
	}
	MemCpy(&status, Status, sizeof(status));
	return 1;
}

bool8 spt::SalUserAccount::SetPassWord(const char* Pw)
{
	SalDateStamp now = SptDateTask::Instance().Now();
	StrNCpy(data.password, Pw, sizeof(data.password));
	status.lastPwChagneTime = now.Us();
	status.logErrCnt = 0;
	status.lastLogTime = now.Us();
	status.isDefaultPw = 0;
	return 1;
}

int32 spt::SalUserAccount::LogOnce(const char* Pw)
{
	SalDateStamp now = SptDateTask::Instance().Now();
	if (!(data.isEnable && data.isValid))
	{
		return -3;
	}
	if (IsLocked())
	{
		return -2;
	}
	if (StrCmp(Pw, data.password) == 0)
	{
		status.logErrCnt = 0;
		status.lastLogTime = now.Us();
		if (SalUserMng::Instance().UsrCfg.EnablePassWordOverTime.Data())
		{
			uint64 delta = now.Us() - status.lastPwChagneTime;
			delta = delta / SalDateStamp::Dt1Minute;
			if (delta < SalUserMng::Instance().UsrCfg.PasswordLockTime.Data())
			{
				return -5;
			}
		}
		return 0;
	}
	else
	{
		if (status.logErrCnt == 0)
		{
			status.logErrCnt = 1;
			status.firstErrTime = now.Us();
			status.lastErrTime = now.Us();
		}
		else
		{
			status.logErrCnt++;
			status.lastErrTime = now.Us();
		}
		if (status.logErrCnt > SalUserMng::Instance().UsrCfg.PasswordErrCnt.Data())
		{
			status.isLock = 1;
			return -6;
		}
	}
	return -4;
}

bool8 spt::SalUserAccount::IsLocked()
{
	SalDateStamp now = SptDateTask::Instance().Now();
	if (status.isLock)
	{
		uint64 delta = now.Us() - status.lastErrTime;
		delta = delta / SalDateStamp::Dt1Minute;
		if (delta < SalUserMng::Instance().UsrCfg.PasswordLockTime.Data())
		{
			return 1;
		}
		status.isLock = 0;
		status.logErrCnt = 0;
	}
	return 0;
}

bool8 spt::SalUserAccount::IsLocked() const
{
	SalDateStamp now;
	now.Now();
	if (status.isLock)
	{
		uint64 delta = now.Us() - status.lastErrTime;
		delta = delta / SalDateStamp::Dt1Minute;
		if (delta < SalUserMng::Instance().UsrCfg.PasswordLockTime.Data())
		{
			return 1;
		}
	}
	return 0;
}

bool8 spt::SalUserAccount::IsValid()const
{
	return data.isValid;
}

bool8 spt::SalUserAccount::IsEnable()const
{
	return data.isEnable;
}
bool8 spt::SalUserAccount::IsDefaultPw() const
{
	return status.isDefaultPw;
}
bool8 spt::SalUserAccount::ResetLockStatus()
{
	status.isLock = 0;
	status.logErrCnt = 0;
	return 0;
}

int32 spt::SalUserAccount::DeleteUser()
{
	data.isValid = 0;
	data.isEnable = 0;
	return 0;
}

int32 spt::SalUserAccount::EnableUser(bool8 Enable)
{
	data.isValid = 1;
	data.isEnable = (Enable == 1);
	return 0;
}

bool8 spt::SalUserAccount::IsAllowEnter(uint32 MenuIndex)const
{
	if (MenuIndex < sizeof(data.menuAllow))
	{
		return data.menuAllow[MenuIndex];
	}
	return 0;
}

bool8 spt::SalUserAccount::SetAllowEnter(uint32 MenuIndex, bool8 Enable)
{
	if (MenuIndex < sizeof(data.menuAllow))
	{
		return data.menuAllow[MenuIndex] = Enable;
	}
	return 0;
}

int32 spt::SalUserMng::PowerUpIni()
{
	pool = (SalUserPool*)Calloc(1, sizeof(*pool));
	if (!pool)
	{
		LogErr << "PowerUpIni pool calloc err.\n";
	}
	UsrCfg.PowerUpIni(0);
	return LoadPool();
}

int32 spt::SalUserMng::CreatNewUser(const char* Account, uint8 AcType, const char* Pw, uint8 PwType, bool8 IsDefault)
{
	if (StrCmp(Account, Pw) == 0)
	{
		return -1;
	}
	String100B str;
	str = Pw;
	if (str.IsInclude(Account) >= 0)
	{
		return -1;
	}
	if (pool->IsUserExist(Account))
	{
		return -2;
	}
	int pwl = StrLen(Pw);
	if ((pwl < 4) || ((uint32)pwl >= sizeof(SalUserAccount::UserAccountSaveData::password)))
	{
		return -3;
	}
	if (IsIdOk(Account, PwType) == 0)
	{
		return -6;
	}
	if (IsPassWordOk(Pw, PwType) == 0)
	{
		return -4;
	}
	if (pool->IsFull())
	{
		return -5;
	}
	pool->AddNewUser(Account, AcType, Pw, PwType, IsDefault);
	pool->SavePool();
	pool->SaveStatus();
	return 0;
}

int32 spt::SalUserMng::SetNewPassWord(const char* Account, const char* Pw)
{
	const SalUserAccount* usr = pool->GetUser(Account);
	if (!usr)
	{
		return -2;
	}
	if (StrCmp(Account, Pw) == 0)
	{
		return -1;
	}
	int pwl = StrLen(Pw);
	if ((pwl < 4) || ((uint32)pwl >= sizeof(SalUserAccount::UserAccountSaveData::password)))
	{
		return -3;
	}
	if (IsPassWordOk(Pw, usr->PwType()) == 0)
	{
		return -4;
	}
	pool->SetNewPassWord(Account, Pw);
	pool->SavePool();
	pool->SaveStatus();
	return 0;
}

int32 spt::SalUserMng::UserLog(const char* Account, const char* Pw)
{
	const SalUserAccount* usr = pool->GetUser(Account);
	if (!usr)
	{
		return -1;
	}
	if (usr->data.isEnable == 0)
	{
		return -3;
	}
	int32 res = pool->UserLog(Account, Pw);
	pool->SavePool();
	pool->SaveStatus();
	return res;
}

bool8 spt::SalUserMng::IsAccountExist(const char* Account)
{
	if (pool->IsUserExist(Account))
	{
		return 1;
	}
	return 0;
}

bool8 spt::SalUserMng::IsAccountLocked(const char* Account)
{
	return pool->IsAccountLocked(Account);
}

bool8 spt::SalUserMng::IsAllowEnter(const char* Account, uint16 MenuIndex)
{
	const SalUserAccount* usr = pool->GetUser(Account);
	if (!usr)
	{
		return 0;
	}
	return usr->IsAllowEnter(MenuIndex);
}

bool8 spt::SalUserMng::SetAllowEnter(const char* Account, uint16 MenuIndex, bool8 Enable)
{
	bool8 res = pool->SetAllowEnter(Account, MenuIndex, Enable);
	pool->SavePool();
	pool->SaveStatus();
	return res;
}

const SalUserAccount* spt::SalUserMng::GetUser(const char* Account)
{
	return pool->GetUser(Account);
}

int32 spt::SalUserMng::ResetUserLockStatus(const char* Account)
{
	pool->ResetUserLockStatus(Account);
	pool->SaveStatus();
	return 0;
}

int32 spt::SalUserMng::DeleteUser(const char* Account)
{
	int32 res = pool->DeleteUser(Account);
	pool->SavePool();
	pool->SaveStatus();
	return res;
}

int32 spt::SalUserMng::EnableUser(const char* Account, bool8 Enable)
{
	int32 res = pool->EnableUser(Account, Enable);
	pool->SavePool();
	pool->SaveStatus();
	return res;
}

const SalUserAccount* spt::SalUserMng::GetUser(uint32 Id)
{
	const SalUserAccount* usr = pool->GetUser(Id);
	if (usr && usr->IsValid())
	{
		return usr;
	}
	return 0;
}

int32 spt::SalUserMng::IniUserPool()
{
	pool->IniPool();
	const struct ApiAppCfg* cfg = SptMain::Instance().AppCfg();
	const uint8 enacc[3][16] = { {0xC5,0xF1,0x4D,0xA4,0x8E,0x2A,0x53,0x39,0xC3,0xCD,0x0B,0x51,0x5A,0x86,0xED,0xDF,},
		{0xAD,0x84,0x98,0x4F,0x6C,0xAF,0xDA,0xD3,0x0E,0x07,0x6E,0x12,0x4A,0xF9,0xD9,0xD9,},
		{0x2B,0xD9,0x36,0x8E,0x2D,0x68,0x7C,0x54,0x59,0xEF,0x78,0x57,0x8D,0x73,0x67,0x3C,} };
	const uint8 enpw[3][16] = { {0x20,0xA6,0x5E,0x47,0x4D,0xE6,0x1B,0x18,0x76,0x95,0x28,0x48,0x9D,0x5F,0x3C,0x24,},
		{0x0A,0xB4,0xDA,0x82,0xCE,0x66,0x49,0x13,0x55,0x56,0x70,0x10,0x0F,0x39,0xB3,0x7C,},
		{0xBB,0x9A,0xFE,0x46,0xA6,0x0F,0xB9,0xBC,0x46,0xCE,0x85,0x95,0x88,0x9A,0xBF,0x21,} };
	if (cfg->platform.hardware == EH_GZKSAU)
	{
		//	SalGmSm4EncryData((uint8*)&acc[0], (uint8*)&enacc[0], sizeof(enacc));
		//	SalGmSm4EncryData((uint8*)&pw[0], (uint8*)&enpw[0], sizeof(enacc));
		//	String1000B str;
		//	str.FormatHex(enacc[0], 16) << ",\n";
		//	str.FormatHex(enacc[1], 16) << ",\n";
		//	str.FormatHex(enacc[2], 16) << "\n";
		//  LogErr << str;
		char deacc[3][16];
		char depw[3][16];
		SalGmSm4DecryData((uint8*)&enacc[0], (uint8*)&deacc[0], sizeof(enacc));
		SalGmSm4DecryData((uint8*)&enpw[0], (uint8*)&depw[0], sizeof(enacc));

		CreatNewUser(deacc[0], SalUserAccount::E_UT_Admin, depw[0], SalUserAccount::E_UPT_Pc, 1);
		CreatNewUser(deacc[1], SalUserAccount::E_UT_Operator, depw[1], SalUserAccount::E_UPT_Pc, 1);
		CreatNewUser(deacc[2], SalUserAccount::E_UT_Comptroller, depw[2], SalUserAccount::E_UPT_Pc, 1);
	}
	else
	{

	}
	return 0;
}

int32 spt::SalUserMng::LoadPool()
{
	pool->LoadStatus();
	int32 res = pool->LoadPool();
	if (res == -1)
	{
		IniUserPool();
		pool->SavePool();
		if (pool->LoadPool() != 0)
		{
			SptApiStatus[E_SAS_UserFileLoadAlarm].Update(1);
			IniUserPool();
		}
		else
		{
			SptApiStatus[E_SAS_UserFileLoadAlarm].Update(0);
		}
	}
	else if (res == -2)
	{
		SptApiStatus[E_SAS_UserFileLoadAlarm].Update(1);
		IniUserPool();
	}
	return 0;
}

bool8 spt::SalUserPool::SavePool()
{
	if (SptMain::Instance().StartMode() != SptMain::E_Normal)
	{
		return 0;
	}
	SalFile usrfile;
	usrfile.Path().Set(CN_PARA_FILE_ROOT);
	usrfile.Name().Set("user.dat");
	uint8 buf[16];
	uint32	num = sizeof(pool) / sizeof(buf);
	uint8* sur = (uint8*)&pool;
	usrfile.Creat();
	if (usrfile.IsOpened() == 0)
	{
		return 0;
	}
	for (uint32 i = 0; i < num; i++)
	{
		SalGmSm4EncryData(sur, buf, sizeof(buf));
		usrfile.Write(buf, sizeof(buf));
		sur += 16;
	}
	usrfile.Close();
	return 1;
}

int32 spt::SalUserPool::LoadPool()
{
	SalFile usrfile;
	usrfile.Path().Set(CN_PARA_FILE_ROOT);
	usrfile.Name().Set("user.dat");
	uint8 buf[16];
	uint32	num = sizeof(pool) / sizeof(buf);
	uint8* sur = (uint8*)&pool;
	usrfile.OpenReadOnly();
	if (usrfile.IsOpened() == 0)
	{
		LogErr << "SalUserPool LoadPool err1.\n";
		return -1;
	}
	for (uint32 i = 0; i < num; i++)
	{
		usrfile.Read(buf, sizeof(buf));
		SalGmSm4DecryData(buf, sur, sizeof(buf));
		sur += 16;
	}
	usrfile.Close();
	if (IsCrcOk() == 0)
	{
		LogErr << "SalUserPool LoadPool err2.\n";
		return -2;
	}
	for (uint32 i = 0; i < M_ArrLen(pool.data.account); i++)
	{
		MemCpy(&usr[i].data, &pool.data.account[i], sizeof(usr[i].data));
		MemCpy(&usr[i].status, &status.status[i], sizeof(usr[i].status));
	}
	UpdateCrc();
	return 0;
}

spt::SalUserMng::SalUserMng()
{

}

bool8 spt::SalUserMng::IsPassWordOk(const char* Pw, uint8 type)
{
	uint32 l = StrLen(Pw);
	if (type == 0)
	{
		if ((l < 4) || (l >= sizeof(SalUserAccount::UserAccountSaveData::password)))
		{
			return 0;
		}
	}
	else if (type == 1)
	{
		if ((l < 8) || (l >= sizeof(SalUserAccount::UserAccountSaveData::password)))
		{
			return 0;
		}
	}

	if (l > 3)
	{
		l -= 2;
	}
	else
	{
		return 0;
	}
	bool8 hasNum = 0, hasG = 0, hasA = 0;
	for (uint32 i = 0; i < l; i++)
	{
		if ((Pw[i] == Pw[i + 1]) && (Pw[i] == Pw[i + 2]))
		{
			return 0;
		}
		if ((Pw[i] == (Pw[i + 1] + 1)) && (Pw[i] == (Pw[i + 2]) + 2))
		{
			return 0;
		}
	}
	if (type == 0)
	{
		uint32 l = StrLen(Pw);
		for (uint32 i = 0; i < l; i++)
		{
			uint8 data;
			data = Pw[i];
			if (IsSpace(data))
			{
				return 0;
			}
		}
		return 1;
	}
	else if (type == 1)
	{
		uint32 l = StrLen(Pw);
		for (uint32 i = 0; i < l; i++)
		{
			uint8 data;
			data = Pw[i];
			if (IsSpace(data))
			{
				return 0;
			}
			if (1 != IsAscii(data))
			{
				return 0;
			}
			if (IsNember(data))
			{
				hasNum = 1;
			}
			if (IsPunct(data))
			{
				hasG = 1;
			}
			if (IsAlpha(data))
			{
				hasA = 1;
			}
		}
		if (hasA && hasG && hasNum)
		{
			return 1;
		}
	}
	return 0;
}

bool8 spt::SalUserMng::IsIdOk(const char* Id, uint8 type)
{
	uint32 l = StrLen(Id);
	if ((l < 3) || (l >= sizeof(SalUserAccount::UserAccountSaveData::password)))
	{
		return 0;
	}
	bool8 hasNum = 0, hasG = 0, hasA = 0;
	for (uint32 i = 0; i < l; i++)
	{
		uint8 data;
		data = Id[i];
		if (IsSpace(data))
		{
			return 0;
		}
		if (1 != IsAscii(data))
		{
			return 0;
		}
		if (IsNember(data))
		{
			hasNum = 1;
		}
		if (IsPunct(data))
		{
			hasG = 1;
		}
		if (IsAlpha(data))
		{
			hasA = 1;
		}
	}
	if (hasA || hasG || hasNum)
	{
		return 1;
	}
	return 0;
}

void spt::SalUserPool::IniPool()
{
	MemSet(&pool, 0, sizeof(pool));
	MemSet(&usr, 0, sizeof(usr));
	pool.data.Num = M_ArrLen(pool.data.account);
	pool.data.ValidNum = 0;
	UpdateCrc();
}

bool8 spt::SalUserPool::IsCrcOk()
{
	uint32 crc = CalcCrc();
	return  crc == pool.data.crc;
}

void spt::SalUserPool::SaveStatus()
{
	if (SptMain::Instance().StartMode() != SptMain::E_Normal)
	{
		return;
	}
	SalFile usrfile;
	usrfile.Path().Set(CN_STATUS_FILE_ROOT);
	usrfile.Name().Set("user.sta");
	usrfile.Creat();
	if (usrfile.IsOpened() == 0)
	{
		return;
	}
	usrfile.Write(&status, sizeof(status));
	usrfile.Close();
}

void spt::SalUserPool::LoadStatus()
{
	SalFile usrfile;
	usrfile.Path().Set(CN_STATUS_FILE_ROOT);
	usrfile.Name().Set("user.sta");
	usrfile.OpenReadOnly();
	if (usrfile.IsOpened() == 0)
	{
		return;
	}
	usrfile.Read(&status, sizeof(status));
	usrfile.Close();
	for (uint32 i = 0; i < M_ArrLen(pool.data.account); i++)
	{
		if (usr[i].data.isValid)
		{
			usr[i].SetStaus(&status.status[i]);
		}
	}
}
bool8 spt::SalUserPool::IsUserExist(const char* Account)
{
	for (uint32 i = 0; i < M_ArrLen(usr); i++)
	{
		if (usr[i].data.isValid && (StrCmp(Account, usr[i].data.account) == 0))
		{
			return 1;
		}
	}
	return 0;
}

bool8 spt::SalUserPool::IsFull()
{
	return pool.data.ValidNum == pool.data.Num;
}

const SalUserAccount* spt::SalUserPool::GetUser(const char* Account)
{
	for (uint32 i = 0; i < M_ArrLen(usr); i++)
	{
		if (usr[i].data.isValid && (StrCmp(Account, usr[i].data.account) == 0))
		{
			return &usr[i];
		}
	}
	return 0;
}

const SalUserAccount* spt::SalUserPool::GetUser(uint32 Id)
{
	if (Id >= M_ArrLen(usr))
	{
		return 0;
	}
	return &usr[Id];;
}

const SalUserPool::AccountPool& spt::SalUserPool::Pool()
{
	return pool;
}

const SalUserPool::AccountStatus& spt::SalUserPool::Status()
{
	return status;
}

int32 spt::SalUserPool::AddNewUser(const char* Account, uint8 AcType, const char* Pw, uint8 PwType, bool8 IsDefault)
{
	if (pool.data.ValidNum >= pool.data.Num)
	{
		return -1;
	}
	for (uint32 i = 0; i < M_ArrLen(pool.data.account); i++)
	{
		if (!usr[i].data.isValid)
		{
			usr[i].NewUser(Account, AcType, i, Pw, PwType, IsDefault);
			pool.data.ValidNum++;
			MemCpy(&pool.data.account[i], &usr[i].data, sizeof(usr[i].data));
			MemCpy(&status.status[i], &usr[i].status, sizeof(usr[i].status));
			break;
		}
	}
	UpdateCrc();
	return 0;
}

int32 spt::SalUserPool::SetNewPassWord(const char* Account, const char* Pw)
{
	for (uint32 i = 0; i < M_ArrLen(usr); i++)
	{
		if (usr[i].data.isValid && (StrCmp(Account, usr[i].data.account) == 0))
		{
			usr[i].SetPassWord(Pw);
			MemCpy(&status.status[i], &usr[i].status, sizeof(usr[i].status));
			MemCpy(&pool.data.account[i], &usr[i].data, sizeof(usr[i].data));
			UpdateCrc();
			return 0;
		}
	}
	UpdateCrc();
	return -1;
}

bool8 spt::SalUserPool::SetAllowEnter(const char* Account, uint16 MenuIndex, bool8 Enable)
{
	for (uint32 i = 0; i < M_ArrLen(usr); i++)
	{
		if (usr[i].data.isValid && (StrCmp(Account, usr[i].data.account) == 0))
		{
			usr[i].SetAllowEnter(MenuIndex, Enable);
			MemCpy(&pool.data.account[i], &usr[i].data, sizeof(usr[i].data));
			UpdateCrc();
			return 1;
		}
	}
	UpdateCrc();
	return 0;
}

int32 spt::SalUserPool::ResetUserLockStatus(const char* Account)
{
	for (uint32 i = 0; i < M_ArrLen(usr); i++)
	{
		if (usr[i].data.isValid && (StrCmp(Account, usr[i].data.account) == 0))
		{
			usr[i].ResetLockStatus();
			MemCpy(&status.status[i], &usr[i].status, sizeof(usr[i].status));
			return 1;
		}
	}
	return 0;
}

int32 spt::SalUserPool::DeleteUser(const char* Account)
{
	for (uint32 i = 0; i < M_ArrLen(usr); i++)
	{
		if (usr[i].data.isValid && (StrCmp(Account, usr[i].data.account) == 0))
		{
			usr[i].DeleteUser();
			MemCpy(&pool.data.account[i], &usr[i].data, sizeof(usr[i].data));
			UpdateCrc();
			return 0;
		}
	}
	UpdateCrc();
	return -1;
}

int32 spt::SalUserPool::EnableUser(const char* Account, bool8 Enable)
{
	for (uint32 i = 0; i < M_ArrLen(usr); i++)
	{
		if (usr[i].data.isValid && (StrCmp(Account, usr[i].data.account) == 0))
		{
			usr[i].EnableUser(Enable);
			MemCpy(&pool.data.account[i], &usr[i].data, sizeof(usr[i].data));
			UpdateCrc();
			return 0;
		}
	}
	UpdateCrc();
	return -1;
}

int32 spt::SalUserPool::UserLog(const char* Account, const char* Pw)
{
	for (uint32 i = 0; i < M_ArrLen(usr); i++)
	{
		if (usr[i].data.isValid && (StrCmp(Account, usr[i].data.account) == 0))
		{
			int32 res = usr[i].LogOnce(Pw);
			MemCpy(&status.status[i], &usr[i].status, sizeof(usr[i].status));
			return res;
		}
	}
	return -1;
}

bool8 spt::SalUserPool::IsAccountLocked(const char* Account)
{
	for (uint32 i = 0; i < M_ArrLen(usr); i++)
	{
		if (usr[i].data.isValid && (StrCmp(Account, usr[i].data.account) == 0))
		{
			bool8 res = usr[i].IsLocked();
			MemCpy(&status.status[i], &usr[i].status, sizeof(usr[i].status));
			return res;
		}
	}
	return 0;
}

uint32 spt::SalUserPool::CalcCrc()
{
	return StdCrc32Check.CalCrc(&pool.data, sizeof(pool.data) - sizeof(pool.data.crc));
}

uint32 spt::SalUserPool::UpdateCrc()
{
	return pool.data.crc = CalcCrc();
}

int32 spt::SalUsrCfg::PowerUpIni(int32 Para)
{
	EnableAccount.Set("启用账号系统", "", 1);
	EnableAccount.SetRange(0, 1);
	AddCfgData(&EnableAccount);
	AutoExitTime.Set("自动退出时间", "", 30);
	AutoExitTime.SetRange(1, 30);
	AutoExitTime.SetUnit(&Unit_Minute);
	AddCfgData(&AutoExitTime);
	PasswordErrCnt.Set("允许密码出错次数", "", 10);
	PasswordErrCnt.SetRange(1, 30);
	AddCfgData(&PasswordErrCnt);
	PasswordLockTime.Set("账号锁定时间", "", 10);
	PasswordLockTime.SetRange(2, 10);
	PasswordLockTime.SetUnit(&Unit_Minute);
	AddCfgData(&PasswordLockTime);
	EnablePassWordOverTime.Set("启用密码超期判断", "", 0);
	AddCfgData(&EnablePassWordOverTime);
	PassWordOverTime.Set("密码有效期", "", 7300);
	PassWordOverTime.SetRange(10, 7300);
	PassWordOverTime.SetUnit(&Unit_Day);
	AddCfgData(&PassWordOverTime);
	path.Set(CN_CFG_FILE_ROOT);
	name.Set("AccountCfg.cfg");
	if ((uint32)ReadAll() != CfgDataNum())
	{
		SaveAll();
	}
	return 0;
}
