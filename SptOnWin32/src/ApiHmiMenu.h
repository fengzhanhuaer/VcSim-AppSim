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
		/// �����˵�
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="AllowFunction">����������</param>
		/// <param name="ChildMenu"></param>
		/// <param name="ExitFunction">�˳�������</param>
		/// <param name="PDisp">��������ʱ����</param>
		ApiMenu(const char* Name, IsOkMenuFunction AllowFunction, ApiMenu* ChildMenu, IsOkMenuFunction ExitFunction, const uint32* PDisp);
		ApiMenu(const char* Name, IsOkMenuFunction Function);
		ApiMenu(const char* Name, IsOkMenuFunction AllowFunction, IsOkMenuFunction Function, IsOkMenuFunction ExitFunction);
		ApiMenu(const char* Name, IsOkMenuFunction Function, const uint32* PDisp);
		/// <summary>
		/// ���ܲ˵�
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="AllowFunction">����������</param>
		/// <param name="Function"></param>
		/// <param name="ExitFunction">�˳�������</param>
		/// <param name="PDisp">��������ʱ����</param>
		ApiMenu(const char* Name, IsOkMenuFunction AllowFunction, IsOkMenuFunction Function, IsOkMenuFunction ExitFunction, const uint32* PDisp);
	public:
		const char* Name();
	};
}

#endif // !APIMENU_H

