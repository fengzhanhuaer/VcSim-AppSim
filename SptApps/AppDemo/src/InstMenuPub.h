#ifndef INSTMENUPUB_H
#define INSTMENUPUB_H
/// <summary>
/// ����Ȩ�����࣬Ӧ�ð��趨��,���֧��16��
/// </summary>
enum AccountOperateType
{
	EAOT_InfoView,//��Ϣ�鿴
	EAOT_ParaEdit,//�����༭
	EAOT_OperateTypeTotal,
};
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
/// ������1�͹��ܵ�¼
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdOperType1LogIn(ApiMenu* Menu);

#endif // !INSTMENUPUB_H
