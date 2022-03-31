#ifndef APIMENU_H
#define APIMENU_H

namespace spt
{
	/// <summary>
	/// Hmi
	/// </summary>
	class ApiMenu :protected HmiMenu
	{
	public:
		ApiMenu(const char* Name);
		ApiMenu(const char* Name, ApiMenu* ChildMenu);
		ApiMenu(const char* Name, IsOkMenuFunction AllowFunction, ApiMenu* ChildMenu, IsOkMenuFunction ExitFunction);
		ApiMenu(const char* Name, ApiMenu* ChildMenu, const uint32* PDisp);
		/// <summary>
		/// 级联菜单
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="AllowFunction">进入允许函数</param>
		/// <param name="ChildMenu"></param>
		/// <param name="ExitFunction">退出允许函数</param>
		/// <param name="PDisp">不能是临时变量</param>
		ApiMenu(const char* Name, IsOkMenuFunction AllowFunction, ApiMenu* ChildMenu, IsOkMenuFunction ExitFunction, const uint32* PDisp);
		ApiMenu(const char* Name, IsOkMenuFunction Function);
		ApiMenu(const char* Name, IsOkMenuFunction AllowFunction, IsOkMenuFunction Function, IsOkMenuFunction ExitFunction);
		ApiMenu(const char* Name, IsOkMenuFunction Function, const uint32* PDisp);
		/// <summary>
		/// 功能菜单
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="AllowFunction">进入允许函数</param>
		/// <param name="Function"></param>
		/// <param name="ExitFunction">退出允许函数</param>
		/// <param name="PDisp">不能是临时变量</param>
		ApiMenu(const char* Name, IsOkMenuFunction AllowFunction, IsOkMenuFunction Function, IsOkMenuFunction ExitFunction, const uint32* PDisp);
	public:
		const char* Name();
	};
}

#endif // !APIMENU_H

