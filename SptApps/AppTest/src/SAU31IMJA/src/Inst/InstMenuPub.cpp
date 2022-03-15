#include"InstResource.h"

const SalUserAccount* LogInUsr;//��¼���û�

// �û�Ȩ�޳�����
const tagAccount g_tagAccount[]=
{
	{EAOT_OPER_USR_InfoView  ,  "��Ϣ�鿴����",        "��Ϣ�鿴��¼",       "�û�û����Ϣ�鿴Ȩ��",    "��û����Ϣ�鿴Ȩ��!"},
	{EAOT_OPER_USR_ParaEdit  ,  "�û����ù���",        "�û����õ�¼",       "�û�û���û�����Ȩ��",    "��û���û�����Ȩ��!"},
	{EAOT_OPER_USR_DevSet    ,  "װ�����ù���",        "װ�����õ�¼",       "�û�û��װ������Ȩ��",    "��û��װ������Ȩ��!"},
	{EAOT_OPER_USR_Dbg       ,  "װ�õ��Թ���",        "װ�õ��Ե�¼",       "�û�û��װ�õ���Ȩ��",    "��û��װ�õ���Ȩ��!"},
	{EAOT_OPER_FAC_Init      ,  "���ҵ��Թ���",        "���ҵ��Ե�¼",       "�û�û�г��ҵ���Ȩ��",    "��û�г��ҵ���Ȩ��!"}
};
const uint16 g_Num_Account=sizeof(g_tagAccount)/sizeof(tagAccount);

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
				SjUsrAdmRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "�޸��û���Ϣ", "���Ա�����޸ĳɹ�", 0, 0);
				return 1;
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
	return 0;
}

bool8 LcdAskForAccountInfo(ApiMenu* Menu)
{
	ApiHmiStrEditDialog dig("�û�", "����", 0, 0, 0, 20);
	int32 res = dig.Show();
	if (res == 0)
	{
		const SalString* account = dig.GetText(0);
		const SalString* pw = dig.GetText(1);
#if(CN_SOFT_CPU_TEST_GET(CN_TEST_MENUDBG))
		// �����û���¼���
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
			SjUsrLogRecord.CreatRecord("Hmi", account->Str(), Menu->Name(), "��¼ʧ��", "�û�������", 0, 0);
			ApiWarnDialog wd("�û�������", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -2)
		{
			SjUsrLogRecord.CreatRecord("Hmi", account->Str(), Menu->Name(), "��¼ʧ��", "�û�������", 0, 0);
			ApiWarnDialog wd("�û�������", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -3)
		{
			SjUsrLogRecord.CreatRecord("Hmi", account->Str(), Menu->Name(), "��¼ʧ��", "�û�δ����", 0, 0);
			ApiWarnDialog wd("�û�δ����", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -4)
		{
			SjUsrLogRecord.CreatRecord("Hmi", account->Str(), Menu->Name(), "��¼ʧ��", "�������", 0, 0);
			ApiWarnDialog wd("�������", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -5)
		{
			SjUsrLogRecord.CreatRecord("Hmi", account->Str(), Menu->Name(), "��¼ʧ��", "��¼��ʱ", 0, 0);
			ApiWarnDialog wd("��¼��ʱ", 0, 0, 0, 0);
			wd.Show();
		}
		//��¼ʧ�ܣ������������
		else if (res == -6)
		{
			SjUsrLogRecord.CreatRecord("Hmi", account->Str(), Menu->Name(), "��¼ʧ��", "�����������Խ��", 0, 0);
			ApiWarnDialog wd("�����������Խ��", 0, 0, 0, 0);
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
	//��¼��ʱ�ж�
	if (time > SalUserMng::Instance().UsrCfg.AutoExitTime.Data())
	{
		//��¼��ʱ�������������
		if(LogInUsr)
		SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "�û�ע��", "��¼��ʱ", 0, 0);
		HmiMain::Instance().MsSleep(2000);
		ApiWarnDialog wd("��¼��ʱ", "�û�ע��", 0, 0, 0);
		wd.Show();
		MenuDispDbgIn=FALSE;
		return 1;
	}
	else
	{
		ApiSelectDialog sd("�˳���¼��", 0, 0, 0, 0);
		int32 res = sd.Show();
		if ((res == 0) || (res == -2))
		{
		    if(LogInUsr)
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "�û�ע��", "�˳���¼", 0, 0);
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
	ApiHmiStrEditDialog dig("�û�", "����", 0, 0, 0, 20);
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
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼�ɹ�", 0, 0, 0);
			LogInUsr = SalUserMng::Instance().GetUser(account->Str());
			return 1;
		}
		//��¼ʧ�ܣ������������
		else if (res == -1)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼ʧ��", "�û�������", 0, 0);
			ApiWarnDialog wd("�û�������", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -2)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼ʧ��", "�û�������", 0, 0);
			ApiWarnDialog wd("�û�������", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -3)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼ʧ��", "�û�δ����", 0, 0);
			ApiWarnDialog wd("�û�δ����", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -4)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼ʧ��", "�������", 0, 0);
			ApiWarnDialog wd("�������", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -5)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼ʧ��", "��¼��ʱ", 0, 0);
			ApiWarnDialog wd("��¼��ʱ", 0, 0, 0, 0);
			wd.Show();
		}

		else if (res == -6)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼ʧ��", "�����������Խ��", 0, 0);
			ApiWarnDialog wd("�����������Խ��", 0, 0, 0, 0);
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
	ApiHmiStrEditDialog dig("�û�", "����", 0, 0, 0, 20);
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
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼�ɹ�", "���Ե�¼", 0, 0);
			LogInUsr = SalUserMng::Instance().GetUser(account->Str());
			return -1;
		}
	#endif
		res = SalUserMng::Instance().UserLog(account->Str(), pw->Str());
		if (res == 0)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼�ɹ�", 0, 0, 0);
			LogInUsr = SalUserMng::Instance().GetUser(account->Str());
			return 1;
		}
		//��¼ʧ�ܣ������������
		else if (res == -1)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼ʧ��", "�û�������", 0, 0);
			ApiWarnDialog wd("�û�������", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -2)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼ʧ��", "�û�������", 0, 0);
			ApiWarnDialog wd("�û�������", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -3)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼ʧ��", "�û�δ����", 0, 0);
			ApiWarnDialog wd("�û�δ����", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -4)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼ʧ��", "�������", 0, 0);
			ApiWarnDialog wd("�������", 0, 0, 0, 0);
			wd.Show();
		}
		else if (res == -5)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼ʧ��", "��¼��ʱ", 0, 0);
			ApiWarnDialog wd("��¼��ʱ", 0, 0, 0, 0);
			wd.Show();
		}

		else if (res == -6)
		{
			SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼ʧ��", "�����������Խ��", 0, 0);
			ApiWarnDialog wd("�����������Խ��", 0, 0, 0, 0);
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
				SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼�ɹ�", 0, 0, 0);
				return 1;
			}
			//ԽȨ���ʣ�Ӧ�����������
			else
			{
				SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼ʧ��", "�û�û�й���ԱȨ��", 0, 0);
				ApiWarnDialog dig("��û�й���ԱȨ��!", 0, 0, 0, 0);
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
				SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼�ɹ�", 0, 0, 0);
				return 1;
			}
			//ԽȨ���ʣ�Ӧ�����������
			else
			{
			
				SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼ʧ��", "�û�û�����ԱȨ��", 0, 0);
				ApiWarnDialog dig("��û�����ԱȨ��!", 0, 0, 0, 0);
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
					SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼�ɹ�", 0, 0, 0);
				}
			#if(CN_SOFT_CPU_TEST_GET(CN_TEST_MENUDBG))
				else if(res==2)
				{
					SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "���ҵ�¼", 0, 0, 0);
				}
			#endif
				MenuDispDbgIn=TRUE;
				return 1;
			}
			//ԽȨ���ʣ�Ӧ�����������
			else
			{
				SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼ʧ��", "�û�û�в���ԱȨ��", 0, 0);
				ApiWarnDialog dig("��û�в���ԱȨ��!", 0, 0, 0, 0);
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
					SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼�ɹ�", g_tagAccount[Type].pChLogSucc, 0, 0);
					return 1;
				}
				//ԽȨ���ʣ�Ӧ�����������
				else
				{
					SjUsrLogRecord.CreatRecord("Hmi", LogInUsr->Name(), Menu->Name(), "��¼ʧ��", g_tagAccount[Type].pChLogFail , 0, 0);
					ApiWarnDialog dig(g_tagAccount[Type].pChWar, 0, 0, 0, 0);
					dig.Show();
				}
			}
		}
		else
		{
			ApiWarnDialog dig("Ȩ�޲�����", 0, 0, 0, 0);
			dig.Show();
		}
	}
	else
	{
		ApiWarnDialog dig("�û�������", 0, 0, 0, 0);
		dig.Show();
	}
	return 0;
}
// �û�Ȩ��-��Ϣ�鿴
bool8 LcdOperUsrInfoViewLogIn(ApiMenu* Menu)
{
	return LcdOperAccount(Menu, EAOT_OPER_USR_InfoView);
}
// �û�Ȩ��-�����޸�
bool8 LcdOperUsrParaLogIn(ApiMenu* Menu)
{
	return LcdOperAccount(Menu, EAOT_OPER_USR_ParaEdit);
}
// �û�Ȩ��-װ������
bool8 LcdOperUsrDevSetLogIn(ApiMenu* Menu)
{
	return LcdOperAccount(Menu, EAOT_OPER_USR_DevSet);
}
// �û�Ȩ��-װ�õ���

bool8 LcdOperUsrDbgLogIn(ApiMenu* Menu)
{
	return LcdOperAccount(Menu, EAOT_OPER_USR_Dbg);
}

// ����Ȩ��-װ�ó�ʼ��
bool8 LcdOperFacInitLogIn(ApiMenu* Menu)
{
	return LcdOperAccount(Menu, EAOT_OPER_FAC_Init);
}


