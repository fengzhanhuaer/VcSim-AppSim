#include"ApiProject.h"
using namespace spt;

SalUserAccount::UserType spt::SalUserAccount::Type()const
{
	return (UserType)(data.data.type);
}

SalUserAccount::UserPassType spt::SalUserAccount::PwType() const
{
	return (UserPassType)(data.data.pwtype);
}

const char* spt::SalUserAccount::Name()const
{
	return data.data.account;
}

int32 spt::SalUserAccount::NewUser(const char* Account, uint8 AcType, uint32 Id, const char* Pw, uint8 PwType, bool8 IsDefault)
{
	SalDateStamp now = SptDateTask::Instance().Now();

	if (!data.data.isValid)
	{
		MemSet(&data, 0, sizeof(data));
		data.data.size = sizeof(data);
		data.data.isValid = 1;
		data.data.isEnable = 1;
		data.data.type = AcType;
		data.data.pwtype = PwType;
		data.data.logErrCnt = 0;
		data.data.isDefaultPw = IsDefault;
		data.data.id = Id;
		data.data.lastLogTime = now.Us();
		data.data.lastPwChagneTime = now.Us();
		data.data.firstErrTime = now.Us();
		data.data.lastErrTime = now.Us();
		StrNCpy(data.data.account, Account, sizeof(data.data.account));
		StrNCpy(data.data.password, Pw, sizeof(data.data.password));
		for (uint32 i = 0; i < sizeof(data.data.menuAllow); i++)
		{
			data.data.menuAllow[i] = 0;
		}
	}
	UpdateSum();
	return 0;
}

uint32 spt::SalUserAccount::UpdateSum()
{
	return data.data.sum = CalSum();
}

uint32 spt::SalUserAccount::CalSum()
{
	uint32 sum = 0;
	uint32 l = (uint8*)&data.data.sum - (uint8*)&data;
	uint8* sur = (uint8*)&data;
	for (uint32 i = 0; i < l; i++)
	{
		sum += sur[i];
	}
	return  sum;
}

bool8 spt::SalUserAccount::IsSumOk()
{
	return CalSum() == data.data.sum;
}

bool8 spt::SalUserAccount::SetPassWord(const char* Pw)
{
	SalDateStamp now = SptDateTask::Instance().Now();
	StrNCpy(data.data.password, Pw, sizeof(data.data.password));
	data.data.lastPwChagneTime = now.Us();
	data.data.logErrCnt = 0;
	data.data.lastLogTime = now.Us();
	data.data.isDefaultPw = 0;
	return 1;
}

int32 spt::SalUserAccount::LogOnce(const char* Pw)
{
	SalDateStamp now = SptDateTask::Instance().Now();
	if (!(data.data.isEnable && data.data.isValid))
	{
		return -3;
	}
	if (IsLocked())
	{
		return -2;
	}
	if (StrCmp(Pw, data.data.password) == 0)
	{
		data.data.logErrCnt = 0;
		data.data.lastLogTime = now.Us();
		if (SalUserMng::Instance().UsrCfg.EnablePassWordOverTime.Data())
		{
			uint64 delta = now.Us() - data.data.lastPwChagneTime;
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
		if (data.data.logErrCnt == 0)
		{
			data.data.logErrCnt = 1;
			data.data.firstErrTime = now.Us();
			data.data.lastErrTime = now.Us();
		}
		else
		{
			data.data.logErrCnt++;
			data.data.lastErrTime = now.Us();
		}
		if (data.data.logErrCnt > SalUserMng::Instance().UsrCfg.PasswordErrCnt.Data())
		{
			data.data.isLock = 1;
			return -6;
		}
	}
	return -4;
}

bool8 spt::SalUserAccount::IsLocked()
{
	SalDateStamp now = SptDateTask::Instance().Now();
	if (data.data.isLock)
	{
		uint64 delta = now.Us() - data.data.lastErrTime;
		delta = delta / SalDateStamp::Dt1Minute;
		if (delta < SalUserMng::Instance().UsrCfg.PasswordLockTime.Data())
		{
			return 1;
		}
		data.data.isLock = 0;
		data.data.logErrCnt = 0;
	}
	return 0;
}

bool8 spt::SalUserAccount::IsLocked() const
{
	SalDateStamp now;
	now.Now();
	if (data.data.isLock)
	{
		uint64 delta = now.Us() - data.data.lastErrTime;
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
	return data.data.isValid;
}

bool8 spt::SalUserAccount::IsEnable()const
{
	return data.data.isEnable;
}
bool8 spt::SalUserAccount::IsDefaultPw() const
{
	return data.data.isDefaultPw;
}
bool8 spt::SalUserAccount::ResetLockStatus()
{
	data.data.isLock = 0;
	data.data.logErrCnt = 0;
	return 0;
}

int32 spt::SalUserAccount::DeleteUser()
{
	data.data.isValid = 0;
	data.data.isEnable = 0;
	return 0;
}

int32 spt::SalUserAccount::EnableUser(bool8 Enable)
{
	data.data.isValid = 1;
	data.data.isEnable = (Enable == 1);
	return 0;
}

bool8 spt::SalUserAccount::IsAllowEnter(uint32 MenuIndex)const
{
	if (MenuIndex < sizeof(data.data.menuAllow))
	{
		return data.data.menuAllow[MenuIndex];
	}
	return 0;
}

bool8 spt::SalUserAccount::SetAllowEnter(uint32 MenuIndex, bool8 Enable)
{
	if (MenuIndex < sizeof(data.data.menuAllow))
	{
		data.data.menuAllow[MenuIndex] = Enable;
		return 1;
	}
	return 0;
}

int32 spt::SalUserMng::PowerUpIni()
{
	pool = (UsrSaveData*)Calloc(1, sizeof(*pool));
	if (!pool)
	{
		LogErr << "PowerUpIni pool calloc err.\n";
	}
	IniPool();
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
	if (IsUserExist(Account))
	{
		return -2;
	}
	int pwl = StrLen(Pw);
	if ((pwl < 4) || ((uint32)pwl >= sizeof(SalUserAccount::SaveData::Data::password)))
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
	if (IsFull())
	{
		return -5;
	}
	if (AddNewUser(Account, AcType, Pw, PwType, IsDefault))
	{
		return -5;
	}
	SavePool();
	return 0;
}

int32 spt::SalUserMng::SetNewPassWord(const char* Account, const char* Pw)
{
	SalUserAccount* usr = (SalUserAccount*)GetUser(Account);
	if (!usr)
	{
		return -2;
	}
	if (StrCmp(Account, Pw) == 0)
	{
		return -1;
	}
	int pwl = StrLen(Pw);
	if ((pwl < 4) || ((uint32)pwl >= sizeof(SalUserAccount::SaveData::Data::password)))
	{
		return -3;
	}
	if (IsPassWordOk(Pw, usr->PwType()) == 0)
	{
		return -4;
	}
	usr->SetPassWord(Pw);
	SavePool();
	return 0;
}

int32 spt::SalUserMng::UserLog(const char* Account, const char* Pw)
{
	SalUserAccount* usr = (SalUserAccount*)GetUser(Account);
	if (!usr)
	{
		return -1;
	}
	if (usr->data.data.isEnable == 0)
	{
		return -3;
	}
	int32 res = usr->LogOnce(Pw);
	SavePool();
	return res;
}

bool8 spt::SalUserMng::IsAccountExist(const char* Account)
{
	return GetUser(Account) != 0;
}

bool8 spt::SalUserMng::IsAccountLocked(const char* Account)
{
	SalUserAccount* usr = (SalUserAccount*)GetUser(Account);
	if (!usr)
	{
		return 0;
	}
	if (usr->data.data.isEnable == 0)
	{
		return 0;
	}
	return usr->IsLocked();
}

bool8 spt::SalUserMng::IsAllowEnter(const char* Account, uint16 MenuIndex)
{
	const SalUserAccount* usr = GetUser(Account);
	if (!usr)
	{
		return 0;
	}
	return usr->IsAllowEnter(MenuIndex);
}

bool8 spt::SalUserMng::SetAllowEnter(const char* Account, uint16 MenuIndex, bool8 Enable)
{
	SalUserAccount* usr = (SalUserAccount*)GetUser(Account);
	if (!usr)
	{
		return 0;
	}
	bool8 res = usr->SetAllowEnter(MenuIndex, Enable);
	SavePool();
	return res;
}

const SalUserAccount* spt::SalUserMng::GetUser(const char* Account)
{
	for (uint32 i = 0; i < MaxUserNum; i++)
	{
		SalUserAccount& p = pool->usrdata.usr[i];
		if (p.data.data.isValid && (StrCmp(Account, p.data.data.account) == 0))
		{
			return &p;
		}
	}
	return 0;
}

int32 spt::SalUserMng::ResetUserLockStatus(const char* Account)
{
	SalUserAccount* usr = (SalUserAccount*)GetUser(Account);
	if (!usr)
	{
		return 0;
	}
	usr->ResetLockStatus();
	SavePool();
	return 0;
}

int32 spt::SalUserMng::DeleteUser(const char* Account)
{
	for (uint32 i = 0; i < MaxUserNum; i++)
	{
		SalUserAccount& p = pool->usrdata.usr[i];
		if (p.data.data.isValid && (StrCmp(Account, p.data.data.account) == 0))
		{
			p.DeleteUser();
			SavePool();
			return 0;
		}
	}
	return -1;
}

int32 spt::SalUserMng::EnableUser(const char* Account, bool8 Enable)
{
	for (uint32 i = 0; i < MaxUserNum; i++)
	{
		SalUserAccount& p = pool->usrdata.usr[i];
		if (p.data.data.isValid && (StrCmp(Account, p.data.data.account) == 0))
		{
			p.EnableUser(Enable);
			SavePool();
			return 0;
		}
	}
	return -1;
}

const SalUserAccount* spt::SalUserMng::GetUser(uint32 Id)
{
	for (uint32 i = 0; i < MaxUserNum; i++)
	{
		SalUserAccount& p = pool->usrdata.usr[i];
		if (p.data.data.isValid && (p.data.data.id == Id))
		{
			return &p;
		}
	}
	return 0;
}

int32 spt::SalUserMng::IniUser()
{
	IniPool();
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
		char deacc[3][16];
		char depw[3][16];
		SalGmSm4DecryData((uint8*)&enacc[0], (uint8*)&deacc[0], sizeof(enacc));
		SalGmSm4DecryData((uint8*)&enpw[0], (uint8*)&depw[0], sizeof(enacc));

		CreatNewUser(deacc[0], SalUserAccount::E_UT_Admin, depw[0], SalUserAccount::E_UPT_Pc, 1);
		CreatNewUser(deacc[1], SalUserAccount::E_UT_Operator, depw[1], SalUserAccount::E_UPT_Pc, 1);
		CreatNewUser(deacc[2], SalUserAccount::E_UT_Comptroller, depw[2], SalUserAccount::E_UPT_Pc, 1);
	}
	return 0;
}

int32 spt::SalUserMng::LoadPool()
{
	int32 res = LoadPool("user.dat");

	if (res)
	{
		res = LoadPool("user.dat.bak");
		if (res == -1)
		{
			IniUser();
		}
		else if (res)
		{
			IniUser();
			SptApiStatus[E_SAS_UserFileLoadAlarm].Update(1);
		}
		SavePool();
	}
	return 0;
}

bool8 spt::SalUserMng::SavePool()
{
	if (SptMain::Instance().StartMode() != SptMain::E_Normal)
	{
		return 0;
	}
	SalFile usrfile;
	usrfile.Path().Set(CN_PARA_FILE_ROOT);
	usrfile.Name().Set("user.dat");
	uint8 buf[16];
	UpdateCrc();
	if (IsCrcOk() == 0)
	{
		LogErr << "save err\n";
	}
	uint32	num = sizeof(*pool) / sizeof(buf);
	uint8* sur = (uint8*)pool->buf;
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
	usrfile.Name().Set("user.dat.bak");
	num = sizeof(*pool) / sizeof(buf);
	sur = (uint8*)pool->buf;
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

spt::SalUserMng::SalUserMng()
{

}

bool8 spt::SalUserMng::IsPassWordOk(const char* Pw, uint8 type)
{
	uint32 l = StrLen(Pw);
	if (type == 0)
	{
		if ((l < 4) || (l >= sizeof(SalUserAccount::SaveData::Data::password)))
		{
			return 0;
		}
	}
	else if (type == 1)
	{
		if ((l < 8) || (l >= sizeof(SalUserAccount::SaveData::Data::password)))
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
	if ((l < 3) || (l >= sizeof(SalUserAccount::SaveData::Data::account)))
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

void spt::SalUserMng::IniPool()
{
	MemSet(pool->buf, 0, sizeof(pool->buf));
	pool->usrdata.Num = MaxUserNum;
	pool->usrdata.ValidNum = 0;
}

int32 spt::SalUserMng::LoadPool(const char* Name)
{
	SalFile usrfile;
	usrfile.Path().Set(CN_PARA_FILE_ROOT);
	usrfile.Name().Set(Name);
	uint8 buf[16];
	uint32	num = sizeof(pool->buf) / sizeof(buf);
	uint8* sur = (uint8*)&pool->buf;
	usrfile.OpenReadOnly();
	if (usrfile.IsOpened() == 0)
	{
		LogErr << Name << " SalUserPool LoadPool err1.\n";
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
		LogErr << Name << " SalUserPool LoadPool err2.\n";
		return -2;
	}
	for (uint32 i = 0; i < MaxUserNum; i++)
	{
		if (pool->usrdata.usr[i].IsValid())
		{
			if (!pool->usrdata.usr[i].IsSumOk())
			{
				pool->usrdata.usr[i].data.data.isValid = 0;
				LogErr << Name << " SalUserPool LoadPool err3.\n";
				pool->usrdata.ValidNum++;
			}
		}
	}
	return 0;
}

bool8 spt::SalUserMng::IsCrcOk()
{
	uint32 crc = StdCrc32Check.CalCrc(&pool->buf, (uint8*)&pool->usrdata.crc - (uint8*)&pool->usrdata);
	return  crc == pool->usrdata.crc;
}

bool8 spt::SalUserMng::IsUserExist(const char* Account)
{
	for (uint32 i = 0; i < MaxUserNum; i++)
	{
		SalUserAccount::SaveData& p = pool->usrdata.usr[i].data;
		if (p.data.isValid && (StrCmp(Account, p.data.account) == 0))
		{
			return 1;
		}
	}
	return 0;
}

bool8 spt::SalUserMng::IsFull()
{
	return pool->usrdata.ValidNum >= MaxUserNum;
}
int32 spt::SalUserMng::AddNewUser(const char* Account, uint8 AcType, const char* Pw, uint8 PwType, bool8 IsDefault)
{
	if (pool->usrdata.ValidNum >= MaxUserNum)
	{
		return -1;
	}
	for (uint32 i = 0; i < MaxUserNum; i++)
	{
		if (!pool->usrdata.usr[i].data.data.isValid)
		{
			pool->usrdata.usr[i].NewUser(Account, AcType, i + 1, Pw, PwType, IsDefault);
			pool->usrdata.ValidNum++;
			return 0;
			break;
		}
	}
	return -1;
}
uint32 spt::SalUserMng::UpdateCrc()
{
	for (uint32 i = 0; i < MaxUserNum; i++)
	{
		pool->usrdata.usr[i].UpdateSum();
	}
	pool->usrdata.crc = StdCrc32Check.CalCrc(&pool->buf, (uint8*)&pool->usrdata.crc - (uint8*)&pool->usrdata);
	return pool->usrdata.crc;
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
