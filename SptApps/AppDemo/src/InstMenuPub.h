#ifndef INSTMENUPUB_H
#define INSTMENUPUB_H
/// <summary>
/// 操作权限种类，应用按需定制,最大支持16种
/// </summary>
enum AccountOperateType
{
	EAOT_InfoView,//信息查看
	EAOT_ParaEdit,//参数编辑
	EAOT_OperateTypeTotal,
};
const SalUserAccount* GetCurrentLogUsr();
/// <summary>
/// 修改用户自身密码（修改当前登录帐号的密码）
/// </summary>
/// <param name="Menu"></param>
/// <returns></returns>
bool8 UsrChangePasswordMenu(ApiMenu* Menu);
/// <summary>
/// 账号登录
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdAskForAccountInfo(ApiMenu* Menu);
/// <summary>
/// 账号登录
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdExitAccount(ApiMenu* Menu);
/// <summary>
/// 当前登录账号操作确认
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdOperationConfirmationAccountInfo(ApiMenu* Menu);
/// <summary>
/// 管理员登录
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdMngLogIn(ApiMenu* Menu);
/// <summary>
/// 审计员登录
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdComptrollerLogIn(ApiMenu* Menu);
/// <summary>
/// 操作类1型功能登录
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdOperType1LogIn(ApiMenu* Menu);

#endif // !INSTMENUPUB_H
