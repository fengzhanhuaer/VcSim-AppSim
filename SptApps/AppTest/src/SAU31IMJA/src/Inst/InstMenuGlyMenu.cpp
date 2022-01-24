#include"InstResource.h"
#include "InstMenuGlyMenu.h"
// 同步用户文件
bool8 GlyUsrFileSyn(ApiMenu* Menu)
{
	//传输账户文件
	String100B surstr;
	String100B dststr;
	surstr << CN_STATUS_FILE_ROOT << CN_FILE_DivFlag << "user.sta";//源文件
	dststr << CN_STATUS_FILE_ROOT << CN_FILE_DivFlag << "user.sta";//目的文件
	if(AppSendFile2SubBoard(surstr.Str(), dststr.Str(), 0)!=0)
	{
		return 0;
	}
	surstr.Clear();
	dststr.Clear();
	surstr << CN_PARA_FILE_ROOT << CN_FILE_DivFlag << "user.dat";//源文件
	dststr << CN_PARA_FILE_ROOT << CN_FILE_DivFlag << "user.dat";//目的文件
	if(AppSendFile2SubBoard(surstr.Str(), dststr.Str(), 0)!=0)
	{
		return 0;
	}
	//DispPressAnyKey();
	return 1;
}
bool8 GlyUsrSetFileSyn(ApiMenu* Menu)
{
	//传输账户文件
	String100B surstr;
	String100B dststr;
	surstr << CN_CFG_FILE_ROOT << CN_FILE_DivFlag << "AccountCfg.cfg";//源文件
	dststr << CN_CFG_FILE_ROOT << CN_FILE_DivFlag << "AccountCfg.cfg";//目的文件
	if(AppSendFile2SubBoard(surstr.Str(), dststr.Str(), 0)!=0)
	{
		return 0;
	}
	//DispPressAnyKey();
	return 1;
}

bool8 GlyChangeUsrPasswordMenu(ApiMenu* Menu)
{
	ApiHmiStrEditDialog dig("用    户", "密    码", "确认密码", 0, 0, 20);
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
			const SalUserAccount* usr = SalUserMng::Instance().GetUser(account->Str());
			if (!usr)
			{
				ApiWarnDialog awd("账号不存在", "请重新输入", 0, 0, 0);
				awd.Show();
				break;
			}
			if ((usr->Type() == usr->E_UT_Admin) || (usr->Type() == usr->E_UT_Operator))
			{

			}
			else
			{
				ApiWarnDialog awd("您无权修改该帐号密码", 0, 0, 0, 0);
				awd.Show();
				break;
			}
			res = SalUserMng::Instance().SetNewPassWord(account->Str(), pw->Str());
			if (res == 0)
			{
				//此处应生成审计记录
				if(LogInUsr)
				{
					SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(),  Menu->Name(), "修改用户信息", "密码修改成功", account->Str(), 0);
				}
				
				//此处应生成审计记录
				if(GlyUsrFileSyn(Menu))
				{
					ApiWarnDialog awd("密码修改成功", 0, 0, 0, 0);
					awd.Show();
				}
				else
				{
					ApiWarnDialog awd("用户文件同步失败", 0, 0, 0, 0);
					awd.Show();
				}
				break;
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
	return 1;
}

bool8 ViewAccountInfo(ApiMenu* Menu)
{
	String2000B Info;
	for (uint32 i = 0; i < 100; i++)
	{
		const SalUserAccount* Usr = SalUserMng::Instance().GetUser(i);
		if (Usr)
		{
			Info << Usr->Name();
			if (Usr->Type() == Usr->E_UT_Admin)
			{
				Info << "  管理员";
			}
			else if (Usr->Type() == Usr->E_UT_Comptroller)
			{
				Info << "  审计员";
			}
			else if (Usr->Type() == Usr->E_UT_Operator)
			{
				Info << "  操作员";
			}
			if (Usr->IsEnable())
			{
				Info << "  已启用";
			}
			else
			{
				Info << "  已停用";
			}
			if (Usr->IsLocked())
			{
				Info << "  已锁定";
			}
			else
			{
				Info << "  未锁定";
			}
			Info << "\n";
		}
	}
	ApiHmiTextWnd wnd(HmiTextWnd::E_ScrollPage, 0);
	wnd.SetTitle(Menu->Name(), 1);
	wnd.SetPage(0, Info.Str());
	wnd.Show();
	return 1;
}
bool8 GlyCreatUsr(ApiMenu* Menu, uint32 Type)
{
	ApiHmiStrEditDialog dig("用    户", "密    码", "确认密码", 0, 0, 20);
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
			res = SalUserMng::Instance().CreatNewUser(account->Str(), Type, pw->Str(), SalUserAccount::E_UPT_Pc, 1);
			if (res == 0)
			{
				if(LogInUsr)
				{
					if(Type== SalUserAccount::E_UT_Operator)
					{
						SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "新增用户", "操作用户创建成功", account->Str(), 0);
					}
					else if(Type== SalUserAccount::E_UT_Comptroller)
					{
						SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "新增用户", "审计用户创建成功", account->Str(), 0);
					}
					else if(Type== SalUserAccount::E_UT_Admin)
					{
						SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "新增用户", "管理用户创建成功", account->Str(), 0);
					}
				}
				//此处应生成审计记录
				if(GlyUsrFileSyn(Menu))
				{
					ApiWarnDialog awd("用户创建成功", 0, 0, 0, 0);
					awd.Show();
				}
				else
				{
					ApiWarnDialog awd("用户文件同步失败", 0, 0, 0, 0);
					awd.Show();
				}
				break;
			}
			else if (res == -2)
			{
				ApiWarnDialog awd("用户已存在", 0, 0, 0, 0);
				awd.Show();
				break;
			}
			else
			{
				ApiWarnDialog awd("用户创建失败", "请重新创建", 0, 0, 0);
				awd.Show();
				break;
			}
		}
		else
		{
			break;
		}
	}
	return 1;
}
bool8 GlyCreatUsr(ApiMenu* Menu)
{
	return GlyCreatUsr(Menu, SalUserAccount::E_UT_Operator);
}
bool8 GlyCreatSjy(ApiMenu* Menu)
{
	return GlyCreatUsr(Menu, SalUserAccount::E_UT_Comptroller);
}

bool8 GlyCreatGly(ApiMenu* Menu)
{
	return GlyCreatUsr(Menu, SalUserAccount::E_UT_Admin);
}

bool8 GlyDeleteUsr(ApiMenu* Menu)
{
	ApiHmiStrEditDialog dig("用    户", 0, 0, 0, 0, 20);
	int32 res = dig.Show();
	if (res == 0)
	{
		const SalString* account = dig.GetText(0);
		const SalUserAccount* Usr = SalUserMng::Instance().GetUser(account->Str());
		if (Usr)
		{
			if (Usr->Type() == Usr->E_UT_Comptroller)
			{
				ApiWarnDialog awd("该用户不能被删除", 0, 0, 0, 0);
				awd.Show();
				return 0;
			}
			else if (GetCurrentLogUsr())
			{
				if ((StrCmp(GetCurrentLogUsr()->Name(), account->Str())) == 0)
				{
					ApiWarnDialog awd("不能删除自身用户", 0, 0, 0, 0);
					awd.Show();
					return 0;
				}
			}
		}
		else
		{
			ApiWarnDialog awd("用户不存在", 0, 0, 0, 0);
			awd.Show();
			return 0;
		}
		res = SalUserMng::Instance().DeleteUser(account->Str());
		if (res == 0)
		{
			//此处应生成审计记录
			if(LogInUsr)
			{
				if(Usr->Type() == Usr->E_UT_Operator)
				{
					SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "删除用户", "操作用户删除成功", account->Str(), 0);
				}
				else if(Usr->Type() == Usr->E_UT_Comptroller)
				{
					SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "删除用户", "审计用户删除成功", account->Str(), 0);
				}
				else if(Usr->Type() == Usr->E_UT_Admin)
				{
					SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "删除用户", "管理用户删除成功", account->Str(), 0);
				}
			}
			//此处应生成审计记录
			if(GlyUsrFileSyn(Menu))
			{
				ApiWarnDialog awd("用户删除成功", 0, 0, 0, 0);
				awd.Show();
			}
			else
			{
				ApiWarnDialog awd("用户文件同步失败", 0, 0, 0, 0);
				awd.Show();
			}
		}
		else
		{
			ApiWarnDialog awd("用户删除失败", 0, 0, 0, 0);
			awd.Show();
		}
	}
	return 1;
}
bool8 GlyStopUsr(ApiMenu* Menu, bool8 Enable)
{
	ApiHmiStrEditDialog dig("用    户", 0, 0, 0, 0, 20);
	int32 res = dig.Show();
	if (res == 0)
	{
		const SalString* account = dig.GetText(0);
		const SalUserAccount* Usr = SalUserMng::Instance().GetUser(account->Str());
		if (Usr)
		{
			if (Usr->Type() == Usr->E_UT_Comptroller)
			{
				ApiWarnDialog awd("该用户不能被设置", 0, 0, 0, 0);
				awd.Show();
				return 0;
			}
			else if (GetCurrentLogUsr())
			{
				if ((StrCmp(GetCurrentLogUsr()->Name(), account->Str())) == 0)
				{
					ApiWarnDialog awd("不能设置自身用户", 0, 0, 0, 0);
					awd.Show();
					return 0;
				}
			}
		}
		else
		{
			ApiWarnDialog awd("用户不存在", 0, 0, 0, 0);
			awd.Show();
			return 0;
		}
		res = SalUserMng::Instance().EnableUser(account->Str(), Enable);
		if (res == 0)
		{
			//此处应生成审计记录
			
			if(LogInUsr)
			{
				if(Enable)
				{
					if(Usr->Type() == Usr->E_UT_Operator)
					{
					
						SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "修改用户信息", "操作用户启用", account->Str(), 0);
					}
					else if(Usr->Type() == Usr->E_UT_Comptroller)
					{
						SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "修改用户信息", "审计用户启用", account->Str(), 0);
					}
					else if(Usr->Type() == Usr->E_UT_Admin)
					{
						SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "修改用户信息", "管理用户启用", account->Str(), 0);
					}
				}
				else
				{
					if(Usr->Type() == Usr->E_UT_Operator)
					{
						SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "修改用户信息", "操作用户停用", account->Str(), 0);
					}
					else if(Usr->Type() == Usr->E_UT_Comptroller)
					{
						SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "修改用户信息", "审计用户停用", account->Str(), 0);
					}
					else if(Usr->Type() == Usr->E_UT_Admin)
					{
						SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "修改用户信息", "管理用户停用", account->Str(), 0);
					}
				}
				//此处应生成审计记录
				if(GlyUsrFileSyn(Menu))
				{
					ApiWarnDialog awd("用户设置成功", 0, 0, 0, 0);
					awd.Show();
				}
				else
				{
					ApiWarnDialog awd("用户文件同步失败", 0, 0, 0, 0);
					awd.Show();
				}
			}
		}
		else
		{
			ApiWarnDialog awd("用户设置失败", 0, 0, 0, 0);
			awd.Show();
		}
	}
	return 1;
}
bool8 GlyStopUsr(ApiMenu* Menu)
{
	GlyStopUsr(Menu, 0);
	return 1;
}

bool8 GlyEnableUsr(ApiMenu* Menu)
{
	GlyStopUsr(Menu, 1);
	return 1;
}
bool8 GlyUnLockUsr(ApiMenu* Menu)
{
	ApiHmiStrEditDialog dig("用    户", 0, 0, 0, 0, 20);
	int32 res = dig.Show();
	if (res == 0)
	{
		const SalString* account = dig.GetText(0);
		const SalUserAccount* Usr = SalUserMng::Instance().GetUser(account->Str());
		if (Usr)
		{
			if (Usr->Type() == Usr->E_UT_Comptroller)
			{
				ApiWarnDialog awd("该用户不能被设置", 0, 0, 0, 0);
				awd.Show();
				return 0;
			}
			else if (GetCurrentLogUsr())
			{
				if ((StrCmp(GetCurrentLogUsr()->Name(), account->Str())) == 0)
				{
					ApiWarnDialog awd("不能设置自身用户", 0, 0, 0, 0);
					awd.Show();
					return 0;
				}
			}
		}
		else
		{
			ApiWarnDialog awd("用户不存在", 0, 0, 0, 0);
			awd.Show();
			return 0;
		}
		res = SalUserMng::Instance().ResetUserLockStatus(account->Str());
		if (res == 1)
		{
			//此处应生成审计记录
			if(LogInUsr)
			{
				if(Usr->Type() == Usr->E_UT_Operator)
				{
					
					SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "修改用户信息", "操作用户解锁", account->Str(), 0);
				}
				else if(Usr->Type() == Usr->E_UT_Comptroller)
				{
					SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "修改用户信息", "审计用户解锁", account->Str(), 0);
				}
				else if(Usr->Type() == Usr->E_UT_Admin)
				{
					SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "修改用户信息", "管理用户解锁", account->Str(), 0);
				}
			}
			//此处应生成审计记录
			if(GlyUsrFileSyn(Menu))
			{
				ApiWarnDialog awd("用户解锁成功", 0, 0, 0, 0);
				awd.Show();
			}
			else
			{
				ApiWarnDialog awd("用户文件同步失败", 0, 0, 0, 0);
				awd.Show();
			}
		}
	}
	return 1;
}

bool8 GlyEditOperatorPrioUsr(ApiMenu* Menu, const SalUserAccount* Usr)
{
	ApiHmiGridWnd wnd(0);
	uint8 prio[16] = { 0 };
	for (uint16 i = 0; i < 16; i++)
	{
		prio[i] = Usr->IsAllowEnter(i);
	}
	wnd.SetInfo("用户权限", 0, 0);
	HmiGridWndDataMapRow* row;
	
	for(uint16 i=0;i<g_Num_Account;i++)
	{
		row = wnd.CreatRow();
		row->SetName(g_tagAccount[i].pChFun);
		row->SetColDataCfg(1, 1, E_SVT_U8 | E_SVT_PTR, 1, 0);
		row->SetColData(1, &prio[i]);
		row->SetColDataRange(1, 1, 0);
	}
	wnd.Edit();
	if (wnd.IsDataChange())
	{
		ApiSelectDialog dig("权限已修改是否保存?", 0, 0, 0, 0);
		if (dig.Show() == 0)
		{
			bool8 res = 1;
			for (uint16 i = 0; i < 16; i++)
			{
				res = res && SalUserMng::Instance().SetAllowEnter(Usr->Name(), i, prio[i]);
			}
			if (res)
			{
				if(Usr->Type() == Usr->E_UT_Operator)
				{
					SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "修改用户信息", "操作用户权限修改", Usr->Name(), 0);
				}
				else if(Usr->Type() == Usr->E_UT_Comptroller)
				{
					SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "修改用户信息", "审计用户权限修改", Usr->Name(), 0);
				}
				else if(Usr->Type() == Usr->E_UT_Admin)
				{
					SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "修改用户信息", "管理用户权限修改", Usr->Name(), 0);
				}
				//此处应生成审计记录
				if(GlyUsrFileSyn(Menu))
				{
					ApiWarnDialog dig1("权限保存成功!", 0, 0, 0, 0);
					dig1.Show();
				}
				else
				{
					ApiWarnDialog dig1("用户文件同步失败", 0, 0, 0, 0);
					dig1.Show();
				}
			}
			else
			{
				ApiWarnDialog dig1("权限保存失败!", 0, 0, 0, 0);
				dig1.Show();
			}
		}
	}
	return 1;

}

bool8 GlyEditPrioUsr(ApiMenu* Menu)
{
	ApiHmiStrEditDialog dig("用    户", 0, 0, 0, 0, 20);
	int32 res = dig.Show();
	if (res == 0)
	{
		const SalString* account = dig.GetText(0);
		const SalUserAccount* Usr = SalUserMng::Instance().GetUser(account->Str());
		if (Usr)
		{
			if (Usr->Type() == Usr->E_UT_Operator)
			{
				GlyEditOperatorPrioUsr(Menu, Usr);
				return 0;
			}
			else
			{
				ApiWarnDialog awd("该用户不能被设置", 0, 0, 0, 0);
				awd.Show();
			}
		}
		else
		{
			ApiWarnDialog awd("用户不存在", 0, 0, 0, 0);
			awd.Show();
			return 0;
		}
	}
	return 0;
}

bool8 GlyEditAccountPara(ApiMenu* Menu)
{
	SalUsrCfg& UsrCfg = SalUserMng::Instance().UsrCfg;
	ApiHmiGridWnd wnd(0);
	wnd.SetInfo("用户管理参数", 0, 0);
	HmiGridWndDataMapRow* row;
	UsrCfg.ValueToEditBuf();
	row = wnd.CreatRow();
	row->SetCfgData(&UsrCfg.AutoExitTime);
	row = wnd.CreatRow();
	row->SetCfgData(&UsrCfg.PasswordErrCnt);
	row = wnd.CreatRow();
	row->SetCfgData(&UsrCfg.PasswordLockTime);
	row = wnd.CreatRow();
	row->SetCfgData(&UsrCfg.EnablePassWordOverTime);
	row = wnd.CreatRow();
	row->SetCfgData(&UsrCfg.PassWordOverTime);
	wnd.Edit();
	if (wnd.IsDataChange())
	{
		ApiSelectDialog dig("参数已修改是否保存?", 0, 0, 0, 0);
		if (dig.Show() == 0)
		{
			UsrCfg.EditBufToValue();

			if (UsrCfg.SaveAll() > 0)
			{
				if(GlyUsrSetFileSyn(Menu))
				{
					ApiWarnDialog dig1("参数保存成功!", 0, 0, 0, 0);
					dig1.Show();
				}
				else
				{
					ApiWarnDialog dig1("同步用户设置文件失败!", 0, 0, 0, 0);
					dig1.Show();
				}
			}
			else
			{
				ApiWarnDialog dig1("参数保存失败!", 0, 0, 0, 0);
				dig1.Show();
			}
		}
	}
	return 1;
}
