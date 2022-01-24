#ifndef APIDIALOG_H
#define APIDIALOG_H

namespace spt
{
	/** @defgroup ApiHmiDialog
	* 液晶显示对话框模块
	* @{
	*/
	/** @brief 异步调用液晶显示单行文本 */
	int32 DispProcess(int Step, const char* info);
	/// <summary>
	/// 等待任意键按下
	/// </summary>
	/// <param name="Ms"></param>
	/// <returns>按键值</returns>
	int32 DispPressAnyKey(int32 Ms = -1);
	/**
	 * @brief 信息框
	 * 显示完立即返回
	 */
	class ApiInfoDialog :protected HmiInfoDialog
	{
	public:
		/// <summary>
		/// 显示内容
		/// </summary>
		/// <param name="Str1"></param>
		/// <param name="Str2"></param>
		/// <param name="Str3"></param>
		/// <param name="Str4"></param>
		/// <param name="Str5"></param>
		ApiInfoDialog(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5);
		/// <summary>
		/// 显示内容
		/// </summary>
		/// <param name="Str1"></param>
		/// <param name="Str2"></param>
		/// <param name="Str3"></param>
		/// <param name="Str4"></param>
		/// <param name="Str5"></param>
		/// <param name="Warn"></param>
		ApiInfoDialog(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5, const char* Warn);
		/// <summary>
		/// 显示编辑框
		/// </summary>
		/// <returns>
		///  显示完立即返回
		/// </returns>
		int32 Show();
	};
	/// <summary>
	/// 告警框
	/// </summary>
	class ApiWarnDialog :protected HmiWarnDialog
	{
	public:
		//Str 显示内容
		ApiWarnDialog(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5);
		/// <summary>
		/// 显示编辑框
		/// </summary>
		/// <returns>
		///  0 编辑正常
		/// -1 ESC退出
		/// -2 强制退出
		/// </returns>
		int32 Show();
	};
	/// <summary>
	/// 选择框
	/// </summary>
	class ApiSelectDialog :protected HmiSelectDialog
	{
	public:
		//Str 显示内容
		ApiSelectDialog(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5);
		/// <summary>
		/// 显示编辑框
		/// </summary>
		/// <returns>
		///  0 编辑正常
		/// -1 ESC退出
		/// -2 强制退出
		/// </returns>
		int32 Show();
	};
	/// <summary>
	/// ASSIC码输入框
	/// </summary>
	class ApiAssicInputDiglog :protected HmiAssicInputDialog
	{
	public:
		ApiAssicInputDiglog(const char* Default, E_Mode Mode, uint32 MaxLen);
		/// <summary>
		/// 显示编辑框
		/// </summary>
		/// <returns>
		///  0 编辑正常
		/// -1 ESC退出
		/// -2 强制退出
		/// </returns>
		int32 Show();
		const char* Str();
	};
	/// <summary>
	/// 字符串编辑对话框
	/// </summary>
	class ApiHmiStrEditDialog : protected HmiStrEditDialog
	{
	public:
		//Str Title
		//MaxInputLen 最大输入长度
		ApiHmiStrEditDialog(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5, uint32 MaxInputLen);
		//设置默认值
		void SetText(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5);
		//设置是否可以编辑
		void SetEditAble(bool8 EditAble1, bool8 EditAble2, bool8 EditAble3, bool8 EditAble4, bool8 EditAble5);
		/// <summary>
		/// 显示编辑框
		/// </summary>
		/// <returns>
		///  0 编辑正常
		/// -1 ESC退出
		/// -2 强制退出
		/// </returns>
		int32 Show();
		const SalString* GetText(uint32 Index);
	protected:

	};
	/// <summary>
	/// 时间编辑对话框
	/// </summary>
	class ApiHmiDateEditDialog : protected HmiTimeEditDialog
	{
	public:
		//Str Title
		//MaxInputLen 最大输入长度
		ApiHmiDateEditDialog(const char* Title, SalDateStamp& Stamp);
		/// <summary>
		/// 显示编辑框
		/// </summary>
		/// <returns>
		///  0 编辑正常
		/// -1 ESC退出
		/// -2 强制退出
		/// </returns>
		int32 Show();
		SalDateStamp& Stamp();
		SalRtc& Rtc();
	protected:

	};
	/// <summary>
	/// Uint32 编辑框
	/// </summary>
	class ApiHmiUInt32EditDialog : protected HmiUInt32DataDialog
	{
	public:
		/// <summary>
		/// Uint32 编辑框
		/// </summary>
		/// <param name="Title">标题</param>
		/// <param name="Min"></param>
		/// <param name="Def">默认值</param>
		/// <param name="DotNum">小数点位数</param>
		/// <param name="Max"></param>
		ApiHmiUInt32EditDialog(const char* Title, uint32 Min, uint32 Def, uint32 DotNum, uint32 Max);
		/// <summary>
		/// 显示编辑框
		/// </summary>
		/// <returns>
		///  0 编辑正常
		/// -1 ESC退出
		/// -2 强制退出
		/// </returns>
		int32 Show();
		uint32 Value();
	};
	/// <summary>
	/// Int32 编辑框
	/// </summary>
	class ApiHmiInt32EditDialog : protected HmiInt32DataDialog
	{
	public:
		/// <summary>
		/// Int32 编辑框
		/// </summary>
		/// <param name="Title">标题</param>
		/// <param name="Min"></param>
		/// <param name="Def">默认值</param>
		/// <param name="DotNum">小数点位数</param>
		/// <param name="Max"></param>
		ApiHmiInt32EditDialog(const char* Title, int32 Min, int32 Def, int32 DotNum, int32 Max);
		/// <summary>
		/// 显示编辑框
		/// </summary>
		/// <returns>
		///  0 编辑正常
		/// -1 ESC退出
		/// -2 强制退出
		/// </returns>
		int32 Show();
		int32 Value();
	};
	/// <summary>
	/// Hex32 编辑框
	/// </summary>
	class ApiHmiHex32EditDialog : protected HmiHex32DataDialog
	{
	public:
		/// <summary>
		/// Hex32 编辑框
		/// </summary>
		/// <param name="Title">标题</param>
		/// <param name="Min"></param>
		/// <param name="Def">默认值</param>
		/// <param name="Max"></param>
		ApiHmiHex32EditDialog(const char* Title, int32 Min, int32 Def, int32 Max);
		/// <summary>
		/// 显示编辑框
		/// </summary>
		/// <returns>
		///  0 编辑正常
		/// -1 ESC退出
		/// -2 强制退出
		/// </returns>
		int32 Show();
		uint32 Value();
	};
	/// <summary>
	/// Bit32 编辑框
	/// </summary>
	class ApiHmiBit32EditDialog : protected HmiBit32DataDialog
	{
	public:
		/// <summary>
		/// Bit32 编辑框
		/// </summary>
		/// <param name="Title">标题</param>
		/// <param name="Min"></param>
		/// <param name="Def">默认值</param>
		/// <param name="Max"></param>
		///  <param name="Des"></param>
		///  <param name="BitLen">比特数目，必须是8的整数倍</param>
		ApiHmiBit32EditDialog(const char* Title, int32 Min, int32 Def, int32 Max, SalBitDes* Des, uint8 BitLen);
		/// <summary>
		/// 显示编辑框
		/// </summary>
		/// <returns>
		///  0 编辑正常
		/// -1 ESC退出
		/// -2 强制退出
		/// </returns>
		int32 Show();
		uint32 Value();
	};
	/// <summary>
	/// Enum32 编辑框
	/// </summary>
	class ApiHmiEnum32EditDialog : protected HmiEnum32DataDialog
	{
	public:
		/// <summary>
		/// Enum32 编辑框
		/// </summary>
		/// <param name="Title">标题</param>
		/// <param name="Min"></param>
		/// <param name="Def">默认值</param>
		/// <param name="Max"></param>
		///  <param name="Des"></param>
		ApiHmiEnum32EditDialog(const char* Title, int32 Min, int32 Def, int32 Max, SalEnumDes* Des);
		/// <summary>
		/// 显示编辑框
		/// </summary>
		/// <returns>
		///  0 编辑正常
		/// -1 ESC退出
		/// -2 强制退出
		/// </returns>
		int32 Show();
		uint32 Value();
	};
	/** @} */ // end of ApiHmiDialog
}


#endif // !APIDIALOG_H

