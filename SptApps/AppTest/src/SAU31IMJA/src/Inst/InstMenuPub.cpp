#include"InstResource.h"

const SalUserAccount* LogInUsr;//登录的用户

// 用户权限常量表
const tagAccount g_tagAccount[]=
{
	{EAOT_OPER_USR_InfoView  ,  "信息查看功能",        "信息查看登录",       "用户没有信息查看权限",    "您没有信息查看权限!"},
	{EAOT_OPER_USR_ParaEdit  ,  "用户设置功能",        "用户设置登录",       "用户没有用户设置权限",    "您没有用户设置权限!"},
	{EAOT_OPER_USR_DevSet    ,  "装置设置功能",        "装置设置登录",       "用户没有装置设置权限",    "您没有装置设置权限!"},
	{EAOT_OPER_USR_Dbg       ,  "装置调试功能",        "装置调试登录",       "用户没有装置调试权限",    "您没有装置调试权限!"},
	{EAOT_OPER_FAC_Init      ,  "厂家调试功能",        "厂家调试登录",       "用户没有厂家调试权限",    "您没有厂家调试权限!"}
};
const uint16 g_Num_Account=sizeof(g_tagAccount)/sizeof(tagAccount);

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
				SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "修改用户信息", "审计员密码修改成功", 0, 0);
				return 1;
			}
			else if (res == -2)
			{
				ApiWarnDialog awd("用户不存在", 0, 0, 0, 0);
				awd.Show();
				break;
			}
			else if ((res == -1) || (res == -3) || (res == -4))
			{
				ApiWarnDialog awd("密码不符合要求", 0, 0, 0, 0);
				awd.Show();
				break;
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
	return 0;
}

bool8 LcdAskForAccountInfo(ApiMenu* Menu)
{
	ApiHmiStrEditDialog dig("用户", "密码", 0, 0, 0, 20);
	int32 res = dig.Show();
	if (res == 0)
	{
		const SalString* account = dig.GetText(0);
		const SalString* pw = dig.GetText(1);
#if(CN_SOFT_CPU_TEST_GET(CN_TEST_MENUDBG))
		// 调试用户登录检测
		if(MenuDispDbgDisp)
		{
			const SalUserAccount* LogInUsrTem= SalUserMng::Instance().GetUser(account->Str());
			if(LogInUsrTem!=0)
			{
				if((LogInUsrTem->Type() == SalUserAccount::E_UT_Operator))
				{
					LogInUsr = LogInUsrTem;
					return 2;
				}
			}
		}
	#endif
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
			SjUsrLogRecord.CreatRecord("Hmi", account->Str(), Menu->Name(), "登录失败", "用户不存在", 0, 0);
			ApiWarnDialog wd("用户不存在", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -2)
		{
			SjUsrLogRecord.CreatRecord("Hmi", account->Str(), Menu->Name(), "登录失败", "用户被锁定", 0, 0);
			ApiWarnDialog wd("用户被锁定", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -3)
		{
			SjUsrLogRecord.CreatRecord("Hmi", account->Str(), Menu->Name(), "登录失败", "用户未启用", 0, 0);
			ApiWarnDialog wd("用户未启用", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -4)
		{
			SjUsrLogRecord.CreatRecord("Hmi", account->Str(), Menu->Name(), "登录失败", "密码错误", 0, 0);
			ApiWarnDialog wd("密码错误", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -5)
		{
			SjUsrLogRecord.CreatRecord("Hmi", account->Str(), Menu->Name(), "登录失败", "登录超时", 0, 0);
			ApiWarnDialog wd("登录超时", 0, 0, 0, 0);
			wd.Show();
		}
		//登录失败，生成审计事项
		else if (res == -6)
		{
			SjUsrLogRecord.CreatRecord("Hmi", account->Str(), Menu->Name(), "登录失败", "密码输入次数越限", 0, 0);
			ApiWarnDialog wd("密码输入次数越限", 0, 0, 0, 0);
			wd.Show();
		}
	}
	return 0;
}
bool8 LcdExitAccount(ApiMenu* Menu)
{
	if(!(SalUserMng::Instance().UsrCfg.EnableAccount.Data()))
	{
		MenuDispDbgDisp=FALSE;
		MenuDispDbgIn=FALSE;
		return 1;
	}
	uint32 time = HmiKeyService::Instance().SinceLastKeyPutIn() / 1000;
	//登录超时判断
	if (time > SalUserMng::Instance().UsrCfg.AutoExitTime.Data())
	{
		//登录超时，生成审计事项
		if(LogInUsr)
		SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "用户注销", "登录超时", 0, 0);
		HmiMain::Instance().MsSleep(2000);
		ApiWarnDialog wd("登录超时", "用户注销", 0, 0, 0);
		wd.Show();
		MenuDispDbgIn=FALSE;
		return 1;
	}
	else
	{
		ApiSelectDialog sd("退出登录？", 0, 0, 0, 0);
		int32 res = sd.Show();
		if ((res == 0) || (res == -2))
		{
		    if(LogInUsr)
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "用户注销", "退出登录", 0, 0);
			MenuDispDbgIn=FALSE;
			return 1;
		}
	}
	return 0;
}
bool8 LcdOperationConfirmationAccountInfo(ApiMenu* Menu)
{
	if(!(SalUserMng::Instance().UsrCfg.EnableAccount.Data()))
	{
		return 1;
	}
	if (!LogInUsr)
	{
		return 0;
	}
	ApiHmiStrEditDialog dig("用户", "密码", 0, 0, 0, 20);
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
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录成功", 0, 0, 0);
			LogInUsr = SalUserMng::Instance().GetUser(account->Str());
			return 1;
		}
		//登录失败，生成审计事项
		else if (res == -1)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录失败", "用户不存在", 0, 0);
			ApiWarnDialog wd("用户不存在", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -2)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录失败", "用户被锁定", 0, 0);
			ApiWarnDialog wd("用户被锁定", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -3)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录失败", "用户未启用", 0, 0);
			ApiWarnDialog wd("用户未启用", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -4)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录失败", "密码错误", 0, 0);
			ApiWarnDialog wd("密码错误", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -5)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录失败", "登录超时", 0, 0);
			ApiWarnDialog wd("登录超时", 0, 0, 0, 0);
			wd.Show();
		}

		else if (res == -6)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录失败", "密码输入次数越限", 0, 0);
			ApiWarnDialog wd("密码输入次数越限", 0, 0, 0, 0);
			wd.Show();
		}
	}
	return 0;
}

int8 LcdDbgOperationAccountInfo(ApiMenu* Menu)
{
	if(!(SalUserMng::Instance().UsrCfg.EnableAccount.Data()))
	{
		return -1;
	}
	if (!LogInUsr)
	{
		return 0;
	}
	ApiHmiStrEditDialog dig("用户", "密码", 0, 0, 0, 20);
	dig.SetText(LogInUsr->Name(), 0, 0, 0, 0);
	dig.SetEditAble(0, 1, 1, 1, 1);
	int32 res = dig.Show();
	if (res == 0)
	{
		const SalString* account = dig.GetText(0);
		const SalString* pw = dig.GetText(1);
	#if(CN_SOFT_CPU_TEST_GET(CN_TEST_MENUDBG))
		if(MenuDispDbgDisp)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录成功", "调试登录", 0, 0);
			LogInUsr = SalUserMng::Instance().GetUser(account->Str());
			return -1;
		}
	#endif
		res = SalUserMng::Instance().UserLog(account->Str(), pw->Str());
		if (res == 0)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录成功", 0, 0, 0);
			LogInUsr = SalUserMng::Instance().GetUser(account->Str());
			return 1;
		}
		//登录失败，生成审计事项
		else if (res == -1)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录失败", "用户不存在", 0, 0);
			ApiWarnDialog wd("用户不存在", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -2)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录失败", "用户被锁定", 0, 0);
			ApiWarnDialog wd("用户被锁定", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -3)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录失败", "用户未启用", 0, 0);
			ApiWarnDialog wd("用户未启用", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -4)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录失败", "密码错误", 0, 0);
			ApiWarnDialog wd("密码错误", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -5)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录失败", "登录超时", 0, 0);
			ApiWarnDialog wd("登录超时", 0, 0, 0, 0);
			wd.Show();
		}

		else if (res == -6)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录失败", "密码输入次数越限", 0, 0);
			ApiWarnDialog wd("密码输入次数越限", 0, 0, 0, 0);
			wd.Show();
		}
	}
	return 0;
}
bool8 LcdMngLogIn(ApiMenu* Menu)
{
	if(!(SalUserMng::Instance().UsrCfg.EnableAccount.Data()))
	{
		return 1;
	}
	uint8 res=LcdAskForAccountInfo(Menu);
	if (res==1)
	{
		if (LogInUsr)
		{
			if ((LogInUsr->Type() == SalUserAccount::E_UT_Admin))
			{
				SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录成功", 0, 0, 0);
				return 1;
			}
			//越权访问，应生成审计事项
			else
			{
				SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录失败", "用户没有管理员权限", 0, 0);
				ApiWarnDialog dig("您没有管理员权限!", 0, 0, 0, 0);
				dig.Show();
			}
		}
	}
	return 0;
}

bool8 LcdComptrollerLogIn(ApiMenu* Menu)
{
	if(!(SalUserMng::Instance().UsrCfg.EnableAccount.Data()))
	{
		return 1;
	}
	uint8 res=LcdAskForAccountInfo(Menu);
	if (res==1)
	{
		if (LogInUsr)
		{
			if ((LogInUsr->Type() == SalUserAccount::E_UT_Comptroller))
			{
				SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录成功", 0, 0, 0);
				return 1;
			}
			//越权访问，应生成审计事项
			else
			{
			
				SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录失败", "用户没有审计员权限", 0, 0);
				ApiWarnDialog dig("您没有审计员权限!", 0, 0, 0, 0);
				dig.Show();
			}
		}
	}
	return 0;
}
bool8 LcdOperLogIn(ApiMenu* Menu)
{
	if(!(SalUserMng::Instance().UsrCfg.EnableAccount.Data()))
	{
		MenuDispDbgDisp=TRUE;
		MenuDispDbgIn=TRUE;
		return 1;
	}
	uint8 res=LcdAskForAccountInfo(Menu);
	if (res)
	{
		if (LogInUsr)
		{
			if ((LogInUsr->Type() == SalUserAccount::E_UT_Operator))
			{
				if(res==1)
				{
					SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录成功", 0, 0, 0);
				}
			#if(CN_SOFT_CPU_TEST_GET(CN_TEST_MENUDBG))
				else if(res==2)
				{
					SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "厂家登录", 0, 0, 0);
				}
			#endif
				MenuDispDbgIn=TRUE;
				return 1;
			}
			//越权访问，应生成审计事项
			else
			{
				SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录失败", "用户没有操作员权限", 0, 0);
				ApiWarnDialog dig("您没有操作员权限!", 0, 0, 0, 0);
				dig.Show();
			}
		}
	}
	return 0;
}

bool8 LcdOperAccount(ApiMenu* Menu, uint16 Type)
{
	if(!(SalUserMng::Instance().UsrCfg.EnableAccount.Data()))
	{
		return 1;
	}
	if (LogInUsr)
	{
		if ((LogInUsr->Type() == SalUserAccount::E_UT_Operator))
		{
		
			if(Type<g_Num_Account)
			{
				if ((LogInUsr->IsAllowEnter(Type)))
				{
					SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录成功", g_tagAccount[Type].pChLogSucc, 0, 0);
					return 1;
				}
				//越权访问，应生成审计事项
				else
				{
					SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "登录失败", g_tagAccount[Type].pChLogFail , 0, 0);
					ApiWarnDialog dig(g_tagAccount[Type].pChWar, 0, 0, 0, 0);
					dig.Show();
				}
			}
		}
		else
		{
			ApiWarnDialog dig("权限不存在", 0, 0, 0, 0);
			dig.Show();
		}
	}
	else
	{
		ApiWarnDialog dig("用户不存在", 0, 0, 0, 0);
		dig.Show();
	}
	return 0;
}
// 用户权限-信息查看
bool8 LcdOperUsrInfoViewLogIn(ApiMenu* Menu)
{
	return LcdOperAccount(Menu, EAOT_OPER_USR_InfoView);
}
// 用户权限-参数修改
bool8 LcdOperUsrParaLogIn(ApiMenu* Menu)
{
	return LcdOperAccount(Menu, EAOT_OPER_USR_ParaEdit);
}
// 用户权限-装置设置
bool8 LcdOperUsrDevSetLogIn(ApiMenu* Menu)
{
	return LcdOperAccount(Menu, EAOT_OPER_USR_DevSet);
}
// 用户权限-装置调试

bool8 LcdOperUsrDbgLogIn(ApiMenu* Menu)
{
	return LcdOperAccount(Menu, EAOT_OPER_USR_Dbg);
}

// 厂家权限-装置初始化
bool8 LcdOperFacInitLogIn(ApiMenu* Menu)
{
	return LcdOperAccount(Menu, EAOT_OPER_FAC_Init);
}


