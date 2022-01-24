#ifndef INSTMENUPUB_H
#define INSTMENUPUB_H
/// <summary>
/// 操作权限种类，应用按需定制,最大支持16种
/// </summary>
enum AccountOperateType
{
	EAOT_OPER_STR=0,   // 用户权限-信息查看
	EAOT_OPER_USR_InfoView=EAOT_OPER_STR,   // 用户权限-信息查看
	EAOT_OPER_USR_ParaEdit,                 // 用户权限-参数修改
	EAOT_OPER_USR_DevSet,                   // 用户权限-装置设置
	EAOT_OPER_USR_Dbg,                      // 用户权限-装置调试
	EAOT_OPER_FAC_Init,                     // 厂家权限-厂家调试
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

extern const SalUserAccount* LogInUsr;//登录的用户
extern const tagAccount g_tagAccount[ ];
extern const uint16  g_Num_Account;

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
/// 当前登录账号操作确认
/// </summary>
/// <param name="Menu"></param>
/// <returns>-1 ,Dbg logIn Ok,1,Usr logIn Ok,0 ,logIn err</returns>
int8  LcdDbgOperationAccountInfo(ApiMenu* Menu);
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
/// 操作员员登录
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdOperLogIn(ApiMenu* Menu);
/// <summary>
/// 审计员登录
bool8 LcdOperUsrInfoViewLogIn(ApiMenu* Menu);
/// <summary>
/// 操作员-参数修改
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdOperUsrParaLogIn(ApiMenu* Menu);
/// <summary>
/// 操作员-装置设置
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdOperUsrDevSetLogIn(ApiMenu* Menu);
/// <summary>
/// 操作员-用户调试
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdOperUsrDbgLogIn(ApiMenu* Menu);
/// <summary>
/// 操作员-厂家调试
/// </summary>
/// <param name="Menu"></param>
/// <returns>1,logIn Ok,0 ,logIn err</returns>
bool8 LcdOperFacInitLogIn(ApiMenu* Menu);

#endif // !INSTMENUPUB_H
