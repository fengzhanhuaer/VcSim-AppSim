#include"InstResource.h"
#include "InstMenuGlyMenu.h"

bool8 GlyChangeUsrPasswordMenu(ApiMenu* Menu)
{
	ApiHmiStrEditDialog dig("账    号", "密    码", "确认密码", 0, 0, 20);
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
				ApiWarnDialog awd("密码修改成功", 0, 0, 0, 0);
				awd.Show();
				//此处应生成审计记录
				break;
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
	ApiHmiStrEditDialog dig("账    号", "密    码", "确认密码", 0, 0, 20);
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
				ApiWarnDialog awd("帐号创建成功", 0, 0, 0, 0);
				awd.Show();
				//此处应生成审计记录
				break;
			}
			else if (res == -2)
			{
				ApiWarnDialog awd("帐号已存在", 0, 0, 0, 0);
				awd.Show();
				break;
			}
		}
	}
	return 1;
}
bool8 GlyCreatUsr(ApiMenu* Menu)
{
	return GlyCreatUsr(Menu, SalUserAccount::E_UT_Operator);
}

bool8 GlyCreatGly(ApiMenu* Menu)
{
	return GlyCreatUsr(Menu, SalUserAccount::E_UT_Admin);
}

bool8 GlyDeleteUsr(ApiMenu* Menu)
{
	ApiHmiStrEditDialog dig("账    号", 0, 0, 0, 0, 20);
	int32 res = dig.Show();
	if (res == 0)
	{
		const SalString* account = dig.GetText(0);
		const SalUserAccount* Usr = SalUserMng::Instance().GetUser(account->Str());
		if (Usr)
		{
			if (Usr->Type() == Usr->E_UT_Comptroller)
			{
				ApiWarnDialog awd("该帐号不能被删除", 0, 0, 0, 0);
				awd.Show();
				return 0;
			}
			else if (GetCurrentLogUsr())
			{
				if ((StrCmp(GetCurrentLogUsr()->Name(), account->Str())) == 0)
				{
					ApiWarnDialog awd("不能删除自身账号", 0, 0, 0, 0);
					awd.Show();
					return 0;
				}
			}
		}
		else
		{
			ApiWarnDialog awd("帐号不存在", 0, 0, 0, 0);
			awd.Show();
			return 0;
		}
		res = SalUserMng::Instance().DeleteUser(account->Str());
		if (res == 0)
		{
			ApiWarnDialog awd("帐号删除成功", 0, 0, 0, 0);
			awd.Show();
			//此处应生成审计记录
		}
		else
		{

		}
	}
	return 1;
}
bool8 GlyStopUsr(ApiMenu* Menu, bool8 Enable)
{
	ApiHmiStrEditDialog dig("账    号", 0, 0, 0, 0, 20);
	int32 res = dig.Show();
	if (res == 0)
	{
		const SalString* account = dig.GetText(0);
		const SalUserAccount* Usr = SalUserMng::Instance().GetUser(account->Str());
		if (Usr)
		{
			if (Usr->Type() == Usr->E_UT_Comptroller)
			{
				ApiWarnDialog awd("该帐号不能被设置", 0, 0, 0, 0);
				awd.Show();
				return 0;
			}
			else if (GetCurrentLogUsr())
			{
				if ((StrCmp(GetCurrentLogUsr()->Name(), account->Str())) == 0)
				{
					ApiWarnDialog awd("不能设置自身账号", 0, 0, 0, 0);
					awd.Show();
					return 0;
				}
			}
		}
		else
		{
			ApiWarnDialog awd("帐号不存在", 0, 0, 0, 0);
			awd.Show();
			return 0;
		}
		res = SalUserMng::Instance().EnableUser(account->Str(), Enable);
		if (res == 0)
		{
			ApiWarnDialog awd("帐号设置成功", 0, 0, 0, 0);
			awd.Show();
			//此处应生成审计记录
		}
		else
		{

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
bool8 GlyEditOperatorPrioUsr(ApiMenu* Menu, const SalUserAccount* Usr)
{
	ApiHmiGridWnd wnd(0);
	uint8 prio[16] = { 0 };
	for (uint16 i = 0; i < 16; i++)
	{
		prio[i] = Usr->IsAllowEnter(i);
	}
	wnd.SetInfo("账号权限", 0, 0);
	HmiGridWndDataMapRow* row;

	row = wnd.CreatRow();
	row->SetName("信息查看");
	row->SetColDataCfg(1, 1, E_SVT_U8 | E_SVT_PTR, 1, 0);
	row->SetColData(1, &prio[EAOT_InfoView]);
	row->SetColDataRange(1, 1, 0);

	row = wnd.CreatRow();
	row->SetName("参数编辑");
	row->SetColDataCfg(1, 1, E_SVT_U8 | E_SVT_PTR, 1, 0);
	row->SetColData(1, &prio[EAOT_ParaEdit]);
	row->SetColDataRange(1, 1, 0);

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
				ApiWarnDialog dig1("权限保存成功!", 0, 0, 0, 0);
				dig1.Show();
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
	ApiHmiStrEditDialog dig("账    号", 0, 0, 0, 0, 20);
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
				ApiWarnDialog awd("该帐号不能被设置", 0, 0, 0, 0);
				awd.Show();
			}
		}
		else
		{
			ApiWarnDialog awd("帐号不存在", 0, 0, 0, 0);
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
	wnd.SetInfo("账号管理参数", 0, 0);
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
				ApiWarnDialog dig1("参数保存成功!", 0, 0, 0, 0);
				dig1.Show();
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
