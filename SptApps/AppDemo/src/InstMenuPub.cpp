#include"InstResource.h"

static const SalUserAccount* LogInUsr;//登录的账号

const SalUserAccount* GetCurrentLogUsr()
{
	return LogInUsr;
}

bool8 UsrChangePasswordMenu(ApiMenu* Menu)
{
	ApiHmiStrEditDialog dig("账    号", "密    码", "确认密码", 0, 0, 20);
	if (LogInUsr)
	{
		dig.SetText(LogInUsr->Name(), 0, 0, 0, 0);
		dig.SetEditAble(0, 1, 1, 1, 1);
	}
	else
	{
		return 0;
	}
	while (1)
	{
		int32 res = dig.Show();
		if (res == 0)
		{
			const SalString* account = dig.GetText(0);
			const SalString* pw = dig.GetText(1);
			const SalString* spw = dig.GetText(2);
			if ((*pw) != (spw->Str()))
			{
				ApiWarnDialog awd("密码不一致", "请重新输入", 0, 0, 0);
				awd.Show();
				continue;
			}
			res = SalUserMng::Instance().SetNewPassWord(account->Str(), pw->Str());
			if (res == 0)
			{
				ApiWarnDialog awd("密码修改成功", 0, 0, 0, 0);
				awd.Show();
				//此处应生成审计记录
				return 1;
			}
			else if (res == -2)
			{
				ApiWarnDialog awd("帐号不存在", 0, 0, 0, 0);
				awd.Show();
				break;
			}
			else if ((res == -1) || (res == -3) || (res == -4))
			{
				ApiWarnDialog awd("密码不符合要求", 0, 0, 0, 0);
				awd.Show();
				break;
			}
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

bool8 LcdAskForAccountInfo(ApiMenu* Menu)
{
	ApiHmiStrEditDialog dig("账号", "密码", 0, 0, 0, 20);
	int32 res = dig.Show();
	if (res == 0)
	{
		const SalString* account = dig.GetText(0);
		const SalString* pw = dig.GetText(1);
		res = SalUserMng::Instance().UserLog(account->Str(), pw->Str());
		if (res == 0)
		{
			LogInUsr = SalUserMng::Instance().GetUser(account->Str());
			//密码为默认值，是否要求用户修改密码，应用层自行确定
			if (LogInUsr->IsDefaultPw())
			{
				//ApiWarnDialog wd("密码为默认值", "请修改密码", 0, 0, 0);
				//wd.Show();
				//res = UsrChangePasswordMenu(Menu);
			}

			return 1;
		}
		//登录失败，生成审计事项
		else if (res == -1)
		{
			ApiWarnDialog wd("账号不存在", 0, 0, 0, 0);
			wd.Show();
		}
	}
	return 0;
}
bool8 LcdExitAccount(ApiMenu* Menu)
{
	uint32 time = HmiKeyService::Instance().SinceLastKeyPutIn() / 1000;
	//登录超时判断
	if (time > SalUserMng::Instance().UsrCfg.AutoExitTime.Data())
	{
		ApiWarnDialog wd("登录超时", "账号退出中", 0, 0, 0);
		wd.Show();
		//登录超时，生成审计事项
		HmiMain::Instance().MsSleep(2000);
		return 1;
	}
	else
	{
		ApiSelectDialog sd("退出登录？", 0, 0, 0, 0);
		int32 res = sd.Show();
		if ((res == 0) || (res == -2))
		{
			return 1;
		}
	}
	return 0;
}
bool8 LcdOperationConfirmationAccountInfo(ApiMenu* Menu)
{
	if (!LogInUsr)
	{
		return 0;
	}
	ApiHmiStrEditDialog dig("账号", "密码", 0, 0, 0, 20);
	dig.SetText(LogInUsr->Name(), 0, 0, 0, 0);
	dig.SetEditAble(0, 1, 1, 1, 1);
	int32 res = dig.Show();
	if (res == 0)
	{
		const SalString* account = dig.GetText(0);
		const SalString* pw = dig.GetText(1);
		res = SalUserMng::Instance().UserLog(account->Str(), pw->Str());
		if (res == 0)
		{
			LogInUsr = SalUserMng::Instance().GetUser(account->Str());
			return 1;
		}
		//登录失败，生成审计事项
		else if (res == -1)
		{
			ApiWarnDialog wd("账号不存在", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -4)
		{
			ApiWarnDialog wd("密码错误", 0, 0, 0, 0);
			wd.Show();
		}
	}
	return 0;
}
bool8 LcdMngLogIn(ApiMenu* Menu)
{
	if (LcdAskForAccountInfo(Menu))
	{
		if (LogInUsr)
		{
			if ((LogInUsr->Type() == SalUserAccount::E_UT_Admin))
			{
				return 1;
			}
			//越权访问，应生成审计事项
			else
			{
				SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), "管理员功能", "拒绝访问", "用户没有管理员权限", 0, 0);
				ApiWarnDialog dig("您没有管理权限!", 0, 0, 0, 0);
				dig.Show();
			}
		}
	}
	return 0;
}

bool8 LcdComptrollerLogIn(ApiMenu* Menu)
{
	if (LcdAskForAccountInfo(Menu))
	{
		if (LogInUsr)
		{
			if ((LogInUsr->Type() == SalUserAccount::E_UT_Comptroller))
			{
				return 1;
			}
			//越权访问，应生成审计事项
			else
			{
				SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), "审计功能", "拒绝访问", "用户没有审计权限", 0, 0);
				ApiWarnDialog dig("您没有审计权限!", 0, 0, 0, 0);
				dig.Show();
			}
		}
	}
	return 0;
}

bool8 LcdOperType1LogIn(ApiMenu* Menu, uint16 Type)
{
	if (LcdAskForAccountInfo(Menu))
	{
		if (LogInUsr)
		{
			if ((LogInUsr->Type() == SalUserAccount::E_UT_Operator))
			{
				if ((LogInUsr->IsAllowEnter(Type)))
				{
					SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), "信息查看", "允许登录", 0, 0, 0);
					return 1;
				}
				//越权访问，应生成审计事项
				else if (Type == EAOT_InfoView)
				{
					SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), "信息查看功能", "拒绝访问", "用户没有信息查看权限", 0, 0);
					ApiWarnDialog dig("您没有信息查看权限!", 0, 0, 0, 0);
					dig.Show();
				}
			}
			else
			{
				SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), "信息查看功能", "拒绝访问", "用户不是操作员类型", 0, 0);
				ApiWarnDialog dig("您没有操作员权限!", 0, 0, 0, 0);
				dig.Show();
			}
		}
	}
	return 0;
}

bool8 LcdOperType1LogIn(ApiMenu* Menu)
{
	return LcdOperType1LogIn(Menu, EAOT_InfoView);
}
