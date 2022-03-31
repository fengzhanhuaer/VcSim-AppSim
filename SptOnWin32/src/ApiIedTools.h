#ifndef APIIEDTOOLS_H
#define APIIEDTOOLS_H

namespace spt
{
	/** @defgroup ApiIedTools
	* װ�����ù��߽ӿ�
	* ��ģ��Ľӿڱ��������ù��߷���������е��ã���ֹ���������
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
	/// ���ù��߼�������
	/// ���������ù��߷���������е��ã���ֹ���������
	/// </summary>
	class ApiIedToolsCascadeWnd :protected IedToolsCascadeWnd
	{
	public:
		ApiIedToolsCascadeWnd(const char* Name);
		ApiIedToolsCascadeWnd(const char* Name, WndFunc EnterFunc, class ApiIedToolsCascadeWnd* ChildWnd, WndFunc ExitFunc, const uint32* pDisp);
		ApiIedToolsCascadeWnd(const char* Name, WndFunc EnterFunc, WndFunc WorkFunc, WndFunc ExitFunc, const uint32* pDisp);
	};
	/// <summary>
	/// ���ù��߶Ի���ģ��
	/// ���������ù��߷���������е��ã���ֹ���������
	/// </summary>
	class ApiIedToolsDialog :protected IedToolsDialog
	{
	public:
		/// <summary>
		/// ��ʾ�Ի���
		/// </summary>
		/// <param name="Name">��������</param>
		/// <param name="WaitTime">������ڵ���0����ʱ�ȴ�ʱ�䣬��ʱʱĬ�Ϸ���-1</param>
		ApiIedToolsDialog(const char* Name, int32 WaitTime);
		/// <summary>
		/// 
		/// </summary>
		/// <param name="Name">��������</param>
		/// <param name="WaitTime">������ڵ���0����ʱ�ȴ�ʱ�䣬��ʱʱĬ�Ϸ���-1</param>
		/// <returns></returns>
		int32 SetInfo(const char* Name, int32 WaitTime);
		/// <summary>
		/// ��Ҫ�ʺ�����
		/// </summary>
		/// <param name="DefId">Ĭ���ʺţ�������Ĭ��ֵ</param>
		/// <param name="Id">�û������˺�</param>
		/// <param name="Pw">����</param>
		/// <returns>�ɹ�����0��-1�ȴ���ʱ,-2�û�ȡ������</returns>
		int32 ShowAskIdPw(SalString& DefId, SalString& Id, SalString& Pw);
	};

	/** @} */ // end of ApiIedTools
}


#endif // !APIIEDTOOLS_H

