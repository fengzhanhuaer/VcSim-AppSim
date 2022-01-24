#include"InstResource.h"
#include "InstMenuGlyMenu.h"

bool8 GlyChangeUsrPasswordMenu(ApiMenu* Menu)
{
	ApiHmiStrEditDialog dig("��    ��", "��    ��", "ȷ������", 0, 0, 20);
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
				ApiWarnDialog awd("���벻һ��", "����������", 0, 0, 0);
				awd.Show();
				continue;
			}
			const SalUserAccount* usr = SalUserMng::Instance().GetUser(account->Str());
			if (!usr)
			{
				ApiWarnDialog awd("�˺Ų�����", "����������", 0, 0, 0);
				awd.Show();
				break;
			}
			if ((usr->Type() == usr->E_UT_Admin) || (usr->Type() == usr->E_UT_Operator))
			{

			}
			else
			{
				ApiWarnDialog awd("����Ȩ�޸ĸ��ʺ�����", 0, 0, 0, 0);
				awd.Show();
				break;
			}
			res = SalUserMng::Instance().SetNewPassWord(account->Str(), pw->Str());
			if (res == 0)
			{
				ApiWarnDialog awd("�����޸ĳɹ�", 0, 0, 0, 0);
				awd.Show();
				//�˴�Ӧ������Ƽ�¼
				break;
			}
			else if (res == -2)
			{
				ApiWarnDialog awd("�ʺŲ�����", 0, 0, 0, 0);
				awd.Show();
				break;
			}
			else if ((res == -1) || (res == -3) || (res == -4))
			{
				ApiWarnDialog awd("���벻����Ҫ��", 0, 0, 0, 0);
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
				Info << "  ����Ա";
			}
			else if (Usr->Type() == Usr->E_UT_Comptroller)
			{
				Info << "  ���Ա";
			}
			else if (Usr->Type() == Usr->E_UT_Operator)
			{
				Info << "  ����Ա";
			}
			if (Usr->IsEnable())
			{
				Info << "  ������";
			}
			else
			{
				Info << "  ��ͣ��";
			}
			if (Usr->IsLocked())
			{
				Info << "  ������";
			}
			else
			{
				Info << "  δ����";
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
	ApiHmiStrEditDialog dig("��    ��", "��    ��", "ȷ������", 0, 0, 20);
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
				ApiWarnDialog awd("���벻һ��", "����������", 0, 0, 0);
				awd.Show();
				continue;
			}
			res = SalUserMng::Instance().CreatNewUser(account->Str(), Type, pw->Str(), SalUserAccount::E_UPT_Pc, 1);
			if (res == 0)
			{
				ApiWarnDialog awd("�ʺŴ����ɹ�", 0, 0, 0, 0);
				awd.Show();
				//�˴�Ӧ������Ƽ�¼
				break;
			}
			else if (res == -2)
			{
				ApiWarnDialog awd("�ʺ��Ѵ���", 0, 0, 0, 0);
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
	ApiHmiStrEditDialog dig("��    ��", 0, 0, 0, 0, 20);
	int32 res = dig.Show();
	if (res == 0)
	{
		const SalString* account = dig.GetText(0);
		const SalUserAccount* Usr = SalUserMng::Instance().GetUser(account->Str());
		if (Usr)
		{
			if (Usr->Type() == Usr->E_UT_Comptroller)
			{
				ApiWarnDialog awd("���ʺŲ��ܱ�ɾ��", 0, 0, 0, 0);
				awd.Show();
				return 0;
			}
			else if (GetCurrentLogUsr())
			{
				if ((StrCmp(GetCurrentLogUsr()->Name(), account->Str())) == 0)
				{
					ApiWarnDialog awd("����ɾ�������˺�", 0, 0, 0, 0);
					awd.Show();
					return 0;
				}
			}
		}
		else
		{
			ApiWarnDialog awd("�ʺŲ�����", 0, 0, 0, 0);
			awd.Show();
			return 0;
		}
		res = SalUserMng::Instance().DeleteUser(account->Str());
		if (res == 0)
		{
			ApiWarnDialog awd("�ʺ�ɾ���ɹ�", 0, 0, 0, 0);
			awd.Show();
			//�˴�Ӧ������Ƽ�¼
		}
		else
		{

		}
	}
	return 1;
}
bool8 GlyStopUsr(ApiMenu* Menu, bool8 Enable)
{
	ApiHmiStrEditDialog dig("��    ��", 0, 0, 0, 0, 20);
	int32 res = dig.Show();
	if (res == 0)
	{
		const SalString* account = dig.GetText(0);
		const SalUserAccount* Usr = SalUserMng::Instance().GetUser(account->Str());
		if (Usr)
		{
			if (Usr->Type() == Usr->E_UT_Comptroller)
			{
				ApiWarnDialog awd("���ʺŲ��ܱ�����", 0, 0, 0, 0);
				awd.Show();
				return 0;
			}
			else if (GetCurrentLogUsr())
			{
				if ((StrCmp(GetCurrentLogUsr()->Name(), account->Str())) == 0)
				{
					ApiWarnDialog awd("�������������˺�", 0, 0, 0, 0);
					awd.Show();
					return 0;
				}
			}
		}
		else
		{
			ApiWarnDialog awd("�ʺŲ�����", 0, 0, 0, 0);
			awd.Show();
			return 0;
		}
		res = SalUserMng::Instance().EnableUser(account->Str(), Enable);
		if (res == 0)
		{
			ApiWarnDialog awd("�ʺ����óɹ�", 0, 0, 0, 0);
			awd.Show();
			//�˴�Ӧ������Ƽ�¼
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
	wnd.SetInfo("�˺�Ȩ��", 0, 0);
	HmiGridWndDataMapRow* row;

	row = wnd.CreatRow();
	row->SetName("��Ϣ�鿴");
	row->SetColDataCfg(1, 1, E_SVT_U8 | E_SVT_PTR, 1, 0);
	row->SetColData(1, &prio[EAOT_InfoView]);
	row->SetColDataRange(1, 1, 0);

	row = wnd.CreatRow();
	row->SetName("�����༭");
	row->SetColDataCfg(1, 1, E_SVT_U8 | E_SVT_PTR, 1, 0);
	row->SetColData(1, &prio[EAOT_ParaEdit]);
	row->SetColDataRange(1, 1, 0);

	wnd.Edit();
	if (wnd.IsDataChange())
	{
		ApiSelectDialog dig("Ȩ�����޸��Ƿ񱣴�?", 0, 0, 0, 0);
		if (dig.Show() == 0)
		{
			bool8 res = 1;
			for (uint16 i = 0; i < 16; i++)
			{
				res = res && SalUserMng::Instance().SetAllowEnter(Usr->Name(), i, prio[i]);
			}
			if (res)
			{
				ApiWarnDialog dig1("Ȩ�ޱ���ɹ�!", 0, 0, 0, 0);
				dig1.Show();
			}
			else
			{
				ApiWarnDialog dig1("Ȩ�ޱ���ʧ��!", 0, 0, 0, 0);
				dig1.Show();
			}
		}
	}
	return 1;

}

bool8 GlyEditPrioUsr(ApiMenu* Menu)
{
	ApiHmiStrEditDialog dig("��    ��", 0, 0, 0, 0, 20);
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
				ApiWarnDialog awd("���ʺŲ��ܱ�����", 0, 0, 0, 0);
				awd.Show();
			}
		}
		else
		{
			ApiWarnDialog awd("�ʺŲ�����", 0, 0, 0, 0);
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
	wnd.SetInfo("�˺Ź������", 0, 0);
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
		ApiSelectDialog dig("�������޸��Ƿ񱣴�?", 0, 0, 0, 0);
		if (dig.Show() == 0)
		{
			UsrCfg.EditBufToValue();

			if (UsrCfg.SaveAll() > 0)
			{
				ApiWarnDialog dig1("��������ɹ�!", 0, 0, 0, 0);
				dig1.Show();
			}
			else
			{
				ApiWarnDialog dig1("��������ʧ��!", 0, 0, 0, 0);
				dig1.Show();
			}
		}
	}
	return 1;
}
