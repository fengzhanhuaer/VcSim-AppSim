#ifndef INSTMENUPUB_H
#define INSTMENUPUB_H
/// <summary>
/// ����Ȩ�����࣬Ӧ�ð��趨��,���֧��16��
/// </summary>
enum AccountOperateType
{
	EAOT_OPER_STR=0,   // �û�Ȩ��-��Ϣ�鿴
	EAOT_OPER_USR_InfoView=EAOT_OPER_STR,   // �û�Ȩ��-��Ϣ�鿴
	EAOT_OPER_USR_ParaEdit,                 // �û�Ȩ��-�����޸�
	EAOT_OPER_USR_DevSet,                   // �û�Ȩ��-װ������
	EAOT_OPER_USR_Dbg,                      // �û�Ȩ��-װ�õ���
	EAOT_OPER_FAC_Init,                     // ����Ȩ��-���ҵ���
	EAOT_OPER_END
};
typedef  struct
{
	uint16 wIndex;
	const char *pChFun;
	const char *pChLogSucc;
	const char *pChLogFail;
	const char *pChWar;
}tagAccount;

extern const SalUserAccount* LogInUsr;//��¼���û�
extern const tagAccount g_tagAccount[ ];
extern const uint16  g_Num_Account;

const SalUserAccount* GetCurrentLogUsr();
/// <summary>
/// �޸��û��������루�޸ĵ�ǰ��¼�ʺŵ����룩
/// </summary>
/// <param name="Menu"></param>
/// <returns></returns>
bool8 UsrChangePasswordMenu(ApiMenu* Menu);
/// <summary>
/// �˺ŵ�¼
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdAskForAccountInfo(ApiMenu* Menu);
/// <summary>
/// �˺ŵ�¼
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdExitAccount(ApiMenu* Menu);
/// <summary>
/// ��ǰ��¼�˺Ų���ȷ��
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdOperationConfirmationAccountInfo(ApiMenu* Menu);
/// <summary>
/// ��ǰ��¼�˺Ų���ȷ��
/// </summary>
/// <param name="Menu"></param>
/// <returns>-1 ,Dbg logIn Ok,1,Usr logIn Ok,0 ,logIn err</returns>
int8  LcdDbgOperationAccountInfo(ApiMenu* Menu);
/// <summary>
/// ����Ա��¼
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdMngLogIn(ApiMenu* Menu);
/// <summary>
/// ���Ա��¼
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdComptrollerLogIn(ApiMenu* Menu);
/// <summary>
/// ����ԱԱ��¼
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdOperLogIn(ApiMenu* Menu);
/// <summary>
/// ���Ա��¼
bool8 LcdOperUsrInfoViewLogIn(ApiMenu* Menu);
/// <summary>
/// ����Ա-�����޸�
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdOperUsrParaLogIn(ApiMenu* Menu);
/// <summary>
/// ����Ա-װ������
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdOperUsrDevSetLogIn(ApiMenu* Menu);
/// <summary>
/// ����Ա-�û�����
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdOperUsrDbgLogIn(ApiMenu* Menu);
/// <summary>
/// ����Ա-���ҵ���
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdOperFacInitLogIn(ApiMenu* Menu);

#endif // !INSTMENUPUB_H
