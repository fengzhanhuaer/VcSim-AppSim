#include"InstResource.h"
#include "InstMenuGlyMenu.h"
// ͬ���û��ļ�
bool8 GlyUsrFileSyn(ApiMenu* Menu)
{
	//�����˻��ļ�
	String100B surstr;
	String100B dststr;
	surstr << CN_STATUS_FILE_ROOT << CN_FILE_DivFlag << "user.sta";//Դ�ļ�
	dststr << CN_STATUS_FILE_ROOT << CN_FILE_DivFlag << "user.sta";//Ŀ���ļ�
	if(AppSendFile2SubBoard(surstr.Str(), dststr.Str(), 0)!=0)
	{
		return 0;
	}
	surstr.Clear();
	dststr.Clear();
	surstr << CN_PARA_FILE_ROOT << CN_FILE_DivFlag << "user.dat";//Դ�ļ�
	dststr << CN_PARA_FILE_ROOT << CN_FILE_DivFlag << "user.dat";//Ŀ���ļ�
	if(AppSendFile2SubBoard(surstr.Str(), dststr.Str(), 0)!=0)
	{
		return 0;
	}
	//DispPressAnyKey();
	return 1;
}
bool8 GlyUsrSetFileSyn(ApiMenu* Menu)
{
	//�����˻��ļ�
	String100B surstr;
	String100B dststr;
	surstr << CN_CFG_FILE_ROOT << CN_FILE_DivFlag << "AccountCfg.cfg";//Դ�ļ�
	dststr << CN_CFG_FILE_ROOT << CN_FILE_DivFlag << "AccountCfg.cfg";//Ŀ���ļ�
	if(AppSendFile2SubBoard(surstr.Str(), dststr.Str(), 0)!=0)
	{
		return 0;
	}
	//DispPressAnyKey();
	return 1;
}

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
				//�˴�Ӧ������Ƽ�¼
				if(LogInUsr)
				{
					SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(),  Menu->Name(), "�޸��û���Ϣ", "�����޸ĳɹ�", account->Str(), 0);
				}
				
				//�˴�Ӧ������Ƽ�¼
				if(GlyUsrFileSyn(Menu))
				{
					ApiWarnDialog awd("�����޸ĳɹ�", 0, 0, 0, 0);
					awd.Show();
				}
				else
				{
					ApiWarnDialog awd("�û��ļ�ͬ��ʧ��", 0, 0, 0, 0);
					awd.Show();
				}
				break;
			}
			else if (res == -2)
			{
				ApiWarnDialog awd("�û�������", 0, 0, 0, 0);
				awd.Show();
				break;
			}
			else if ((res == -1) || (res == -3) || (res == -4))
			{
				ApiWarnDialog awd("���벻����Ҫ��", 0, 0, 0, 0);
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
				if(LogInUsr)
				{
					if(Type== SalUserAccount::E_UT_Operator)
					{
						SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "�����û�", "�����û������ɹ�", account->Str(), 0);
					}
					else if(Type== SalUserAccount::E_UT_Comptroller)
					{
						SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "�����û�", "����û������ɹ�", account->Str(), 0);
					}
					else if(Type== SalUserAccount::E_UT_Admin)
					{
						SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "�����û�", "�����û������ɹ�", account->Str(), 0);
					}
				}
				//�˴�Ӧ������Ƽ�¼
				if(GlyUsrFileSyn(Menu))
				{
					ApiWarnDialog awd("�û������ɹ�", 0, 0, 0, 0);
					awd.Show();
				}
				else
				{
					ApiWarnDialog awd("�û��ļ�ͬ��ʧ��", 0, 0, 0, 0);
					awd.Show();
				}
				break;
			}
			else if (res == -2)
			{
				ApiWarnDialog awd("�û��Ѵ���", 0, 0, 0, 0);
				awd.Show();
				break;
			}
			else
			{
				ApiWarnDialog awd("�û�����ʧ��", "�����´���", 0, 0, 0);
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
				ApiWarnDialog awd("���û����ܱ�ɾ��", 0, 0, 0, 0);
				awd.Show();
				return 0;
			}
			else if (GetCurrentLogUsr())
			{
				if ((StrCmp(GetCurrentLogUsr()->Name(), account->Str())) == 0)
				{
					ApiWarnDialog awd("����ɾ�������û�", 0, 0, 0, 0);
					awd.Show();
					return 0;
				}
			}
		}
		else
		{
			ApiWarnDialog awd("�û�������", 0, 0, 0, 0);
			awd.Show();
			return 0;
		}
		res = SalUserMng::Instance().DeleteUser(account->Str());
		if (res == 0)
		{
			//�˴�Ӧ������Ƽ�¼
			if(LogInUsr)
			{
				if(Usr->Type() == Usr->E_UT_Operator)
				{
					SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "ɾ���û�", "�����û�ɾ���ɹ�", account->Str(), 0);
				}
				else if(Usr->Type() == Usr->E_UT_Comptroller)
				{
					SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "ɾ���û�", "����û�ɾ���ɹ�", account->Str(), 0);
				}
				else if(Usr->Type() == Usr->E_UT_Admin)
				{
					SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "ɾ���û�", "�����û�ɾ���ɹ�", account->Str(), 0);
				}
			}
			//�˴�Ӧ������Ƽ�¼
			if(GlyUsrFileSyn(Menu))
			{
				ApiWarnDialog awd("�û�ɾ���ɹ�", 0, 0, 0, 0);
				awd.Show();
			}
			else
			{
				ApiWarnDialog awd("�û��ļ�ͬ��ʧ��", 0, 0, 0, 0);
				awd.Show();
			}
		}
		else
		{
			ApiWarnDialog awd("�û�ɾ��ʧ��", 0, 0, 0, 0);
			awd.Show();
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
				ApiWarnDialog awd("���û����ܱ�����", 0, 0, 0, 0);
				awd.Show();
				return 0;
			}
			else if (GetCurrentLogUsr())
			{
				if ((StrCmp(GetCurrentLogUsr()->Name(), account->Str())) == 0)
				{
					ApiWarnDialog awd("�������������û�", 0, 0, 0, 0);
					awd.Show();
					return 0;
				}
			}
		}
		else
		{
			ApiWarnDialog awd("�û�������", 0, 0, 0, 0);
			awd.Show();
			return 0;
		}
		res = SalUserMng::Instance().EnableUser(account->Str(), Enable);
		if (res == 0)
		{
			//�˴�Ӧ������Ƽ�¼
			
			if(LogInUsr)
			{
				if(Enable)
				{
					if(Usr->Type() == Usr->E_UT_Operator)
					{
					
						SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "�޸��û���Ϣ", "�����û�����", account->Str(), 0);
					}
					else if(Usr->Type() == Usr->E_UT_Comptroller)
					{
						SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "�޸��û���Ϣ", "����û�����", account->Str(), 0);
					}
					else if(Usr->Type() == Usr->E_UT_Admin)
					{
						SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "�޸��û���Ϣ", "�����û�����", account->Str(), 0);
					}
				}
				else
				{
					if(Usr->Type() == Usr->E_UT_Operator)
					{
						SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "�޸��û���Ϣ", "�����û�ͣ��", account->Str(), 0);
					}
					else if(Usr->Type() == Usr->E_UT_Comptroller)
					{
						SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "�޸��û���Ϣ", "����û�ͣ��", account->Str(), 0);
					}
					else if(Usr->Type() == Usr->E_UT_Admin)
					{
						SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "�޸��û���Ϣ", "�����û�ͣ��", account->Str(), 0);
					}
				}
				//�˴�Ӧ������Ƽ�¼
				if(GlyUsrFileSyn(Menu))
				{
					ApiWarnDialog awd("�û����óɹ�", 0, 0, 0, 0);
					awd.Show();
				}
				else
				{
					ApiWarnDialog awd("�û��ļ�ͬ��ʧ��", 0, 0, 0, 0);
					awd.Show();
				}
			}
		}
		else
		{
			ApiWarnDialog awd("�û�����ʧ��", 0, 0, 0, 0);
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
				ApiWarnDialog awd("���û����ܱ�����", 0, 0, 0, 0);
				awd.Show();
				return 0;
			}
			else if (GetCurrentLogUsr())
			{
				if ((StrCmp(GetCurrentLogUsr()->Name(), account->Str())) == 0)
				{
					ApiWarnDialog awd("�������������û�", 0, 0, 0, 0);
					awd.Show();
					return 0;
				}
			}
		}
		else
		{
			ApiWarnDialog awd("�û�������", 0, 0, 0, 0);
			awd.Show();
			return 0;
		}
		res = SalUserMng::Instance().ResetUserLockStatus(account->Str());
		if (res == 1)
		{
			//�˴�Ӧ������Ƽ�¼
			if(LogInUsr)
			{
				if(Usr->Type() == Usr->E_UT_Operator)
				{
					
					SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "�޸��û���Ϣ", "�����û�����", account->Str(), 0);
				}
				else if(Usr->Type() == Usr->E_UT_Comptroller)
				{
					SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "�޸��û���Ϣ", "����û�����", account->Str(), 0);
				}
				else if(Usr->Type() == Usr->E_UT_Admin)
				{
					SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "�޸��û���Ϣ", "�����û�����", account->Str(), 0);
				}
			}
			//�˴�Ӧ������Ƽ�¼
			if(GlyUsrFileSyn(Menu))
			{
				ApiWarnDialog awd("�û������ɹ�", 0, 0, 0, 0);
				awd.Show();
			}
			else
			{
				ApiWarnDialog awd("�û��ļ�ͬ��ʧ��", 0, 0, 0, 0);
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
	wnd.SetInfo("�û�Ȩ��", 0, 0);
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
				if(Usr->Type() == Usr->E_UT_Operator)
				{
					SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "�޸��û���Ϣ", "�����û�Ȩ���޸�", Usr->Name(), 0);
				}
				else if(Usr->Type() == Usr->E_UT_Comptroller)
				{
					SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "�޸��û���Ϣ", "����û�Ȩ���޸�", Usr->Name(), 0);
				}
				else if(Usr->Type() == Usr->E_UT_Admin)
				{
					SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "�޸��û���Ϣ", "�����û�Ȩ���޸�", Usr->Name(), 0);
				}
				//�˴�Ӧ������Ƽ�¼
				if(GlyUsrFileSyn(Menu))
				{
					ApiWarnDialog dig1("Ȩ�ޱ���ɹ�!", 0, 0, 0, 0);
					dig1.Show();
				}
				else
				{
					ApiWarnDialog dig1("�û��ļ�ͬ��ʧ��", 0, 0, 0, 0);
					dig1.Show();
				}
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
				ApiWarnDialog awd("���û����ܱ�����", 0, 0, 0, 0);
				awd.Show();
			}
		}
		else
		{
			ApiWarnDialog awd("�û�������", 0, 0, 0, 0);
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
	wnd.SetInfo("�û��������", 0, 0);
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
				if(GlyUsrSetFileSyn(Menu))
				{
					ApiWarnDialog dig1("��������ɹ�!", 0, 0, 0, 0);
					dig1.Show();
				}
				else
				{
					ApiWarnDialog dig1("ͬ���û������ļ�ʧ��!", 0, 0, 0, 0);
					dig1.Show();
				}
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
