#include"InstResource.h"

static const SalUserAccount* LogInUsr;//��¼���˺�

const SalUserAccount* GetCurrentLogUsr()
{
	return LogInUsr;
}

bool8 UsrChangePasswordMenu(ApiMenu* Menu)
{
	ApiHmiStrEditDialog dig("��    ��", "��    ��", "ȷ������", 0, 0, 20);
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
				ApiWarnDialog awd("���벻һ��", "����������", 0, 0, 0);
				awd.Show();
				continue;
			}
			res = SalUserMng::Instance().SetNewPassWord(account->Str(), pw->Str());
			if (res == 0)
			{
				ApiWarnDialog awd("�����޸ĳɹ�", 0, 0, 0, 0);
				awd.Show();
				//�˴�Ӧ������Ƽ�¼
				return 1;
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
			return 0;
		}
	}
	return 0;
}

bool8 LcdAskForAccountInfo(ApiMenu* Menu)
{
	ApiHmiStrEditDialog dig("�˺�", "����", 0, 0, 0, 20);
	int32 res = dig.Show();
	if (res == 0)
	{
		const SalString* account = dig.GetText(0);
		const SalString* pw = dig.GetText(1);
		res = SalUserMng::Instance().UserLog(account->Str(), pw->Str());
		if (res == 0)
		{
			LogInUsr = SalUserMng::Instance().GetUser(account->Str());
			//����ΪĬ��ֵ���Ƿ�Ҫ���û��޸����룬Ӧ�ò�����ȷ��
			if (LogInUsr->IsDefaultPw())
			{
				//ApiWarnDialog wd("����ΪĬ��ֵ", "���޸�����", 0, 0, 0);
				//wd.Show();
				//res = UsrChangePasswordMenu(Menu);
			}

			return 1;
		}
		//��¼ʧ�ܣ������������
		else if (res == -1)
		{
			ApiWarnDialog wd("�˺Ų�����", 0, 0, 0, 0);
			wd.Show();
		}
	}
	return 0;
}
bool8 LcdExitAccount(ApiMenu* Menu)
{
	uint32 time = HmiKeyService::Instance().SinceLastKeyPutIn() / 1000;
	//��¼��ʱ�ж�
	if (time > SalUserMng::Instance().UsrCfg.AutoExitTime.Data())
	{
		ApiWarnDialog wd("��¼��ʱ", "�˺��˳���", 0, 0, 0);
		wd.Show();
		//��¼��ʱ�������������
		HmiMain::Instance().MsSleep(2000);
		return 1;
	}
	else
	{
		ApiSelectDialog sd("�˳���¼��", 0, 0, 0, 0);
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
	ApiHmiStrEditDialog dig("�˺�", "����", 0, 0, 0, 20);
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
		//��¼ʧ�ܣ������������
		else if (res == -1)
		{
			ApiWarnDialog wd("�˺Ų�����", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -4)
		{
			ApiWarnDialog wd("�������", 0, 0, 0, 0);
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
			//ԽȨ���ʣ�Ӧ�����������
			else
			{
				SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), "����Ա����", "�ܾ�����", "�û�û�й���ԱȨ��", 0, 0);
				ApiWarnDialog dig("��û�й���Ȩ��!", 0, 0, 0, 0);
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
			//ԽȨ���ʣ�Ӧ�����������
			else
			{
				SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), "��ƹ���", "�ܾ�����", "�û�û�����Ȩ��", 0, 0);
				ApiWarnDialog dig("��û�����Ȩ��!", 0, 0, 0, 0);
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
					SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), "��Ϣ�鿴", "�����¼", 0, 0, 0);
					return 1;
				}
				//ԽȨ���ʣ�Ӧ�����������
				else if (Type == EAOT_InfoView)
				{
					SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), "��Ϣ�鿴����", "�ܾ�����", "�û�û����Ϣ�鿴Ȩ��", 0, 0);
					ApiWarnDialog dig("��û����Ϣ�鿴Ȩ��!", 0, 0, 0, 0);
					dig.Show();
				}
			}
			else
			{
				SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), "��Ϣ�鿴����", "�ܾ�����", "�û����ǲ���Ա����", 0, 0);
				ApiWarnDialog dig("��û�в���ԱȨ��!", 0, 0, 0, 0);
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
