#ifndef APIIEDTOOLS_H
#define APIIEDTOOLS_H

namespace spt
{
	/** @defgroup ApiIedTools
	* 装置配置工具接口
	* 本模块的接口必须在配置工具服务端任务中调用，禁止跨任务调用
	* @{
	*/
	class ApiIedToolsTextWnd :protected IedToolsTextWnd
	{
	public:
		ApiIedToolsTextWnd(const char* Name);

	};
	class ApiIedToolsGridWnd
	{

	};
	/// <summary>
	/// 配置工具级联窗口
	/// 必须在配置工具服务端任务中调用，禁止跨任务调用
	/// </summary>
	class ApiIedToolsCascadeWnd :protected IedToolsCascadeWnd
	{
	public:
		ApiIedToolsCascadeWnd(const char* Name);
		ApiIedToolsCascadeWnd(const char* Name, WndFunc EnterFunc, class ApiIedToolsCascadeWnd* ChildWnd, WndFunc ExitFunc, const uint32* pDisp);
		ApiIedToolsCascadeWnd(const char* Name, WndFunc EnterFunc, WndFunc WorkFunc, WndFunc ExitFunc, const uint32* pDisp);
	};
	/// <summary>
	/// 配置工具对话框模块
	/// 必须在配置工具服务端任务中调用，禁止跨任务调用
	/// </summary>
	class ApiIedToolsDialog :protected IedToolsDialog
	{
	public:
		/// <summary>
		/// 显示对话框
		/// </summary>
		/// <param name="Name">窗口名称</param>
		/// <param name="WaitTime">必须大于等于0，超时等待时间，超时时默认返回-1</param>
		ApiIedToolsDialog(const char* Name, int32 WaitTime);
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Name">窗口名称</param>
		/// <param name="WaitTime">必须大于等于0，超时等待时间，超时时默认返回-1</param>
		/// <returns></returns>
		int32 SetInfo(const char* Name, int32 WaitTime);
		/// <summary>
		/// 索要帐号密码
		/// </summary>
		/// <param name="DefId">默认帐号，允许有默认值</param>
		/// <param name="Id">用户输入账号</param>
		/// <param name="Pw">密码</param>
		/// <returns>成功返回0，-1等待超时,-2用户取消操作</returns>
		int32 ShowAskIdPw(SalString& DefId, SalString& Id, SalString& Pw);
	};

	/** @} */ // end of ApiIedTools
}


#endif // !APIIEDTOOLS_H

