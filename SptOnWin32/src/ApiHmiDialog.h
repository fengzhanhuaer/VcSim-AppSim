#ifndef APIDIALOG_H
#define APIDIALOG_H

namespace spt
{
	/** @defgroup ApiHmiDialog
	* Һ����ʾ�Ի���ģ��
	* @{
	*/
	/** @brief �첽����Һ����ʾ�����ı� */
	int32 DispProcess(int Step, const char* info);
	/// <summary>
	/// �ȴ����������
	/// </summary>
	/// <param name="Ms"></param>
	/// <returns>����ֵ</returns>
	int32 DispPressAnyKey(int32 Ms = -1);
	/**
	 * @brief ��Ϣ��
	 * ��ʾ����������
	 */
	class ApiInfoDialog :protected HmiInfoDialog
	{
	public:
		/// <summary>
		/// ��ʾ����
		/// </summary>
		/// <param name="Str1"></param>
		/// <param name="Str2"></param>
		/// <param name="Str3"></param>
		/// <param name="Str4"></param>
		/// <param name="Str5"></param>
		ApiInfoDialog(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5);
		/// <summary>
		/// ��ʾ����
		/// </summary>
		/// <param name="Str1"></param>
		/// <param name="Str2"></param>
		/// <param name="Str3"></param>
		/// <param name="Str4"></param>
		/// <param name="Str5"></param>
		/// <param name="Warn"></param>
		ApiInfoDialog(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5, const char* Warn);
		/// <summary>
		/// ��ʾ�༭��
		/// </summary>
		/// <returns>
		///  ��ʾ����������
		/// </returns>
		int32 Show();
	};
	/// <summary>
	/// �澯��
	/// </summary>
	class ApiWarnDialog :protected HmiWarnDialog
	{
	public:
		//Str ��ʾ����
		ApiWarnDialog(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5);
		/// <summary>
		/// ��ʾ�༭��
		/// </summary>
		/// <returns>
		///  0 �༭����
		/// -1 ESC�˳�
		/// -2 ǿ���˳�
		/// </returns>
		int32 Show();
	};
	/// <summary>
	/// ѡ���
	/// </summary>
	class ApiSelectDialog :protected HmiSelectDialog
	{
	public:
		//Str ��ʾ����
		ApiSelectDialog(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5);
		/// <summary>
		/// ��ʾ�༭��
		/// </summary>
		/// <returns>
		///  0 �༭����
		/// -1 ESC�˳�
		/// -2 ǿ���˳�
		/// </returns>
		int32 Show();
	};
	/// <summary>
	/// ASSIC�������
	/// </summary>
	class ApiAssicInputDiglog :protected HmiAssicInputDialog
	{
	public:
		ApiAssicInputDiglog(const char* Default, E_Mode Mode, uint32 MaxLen);
		/// <summary>
		/// ��ʾ�༭��
		/// </summary>
		/// <returns>
		///  0 �༭����
		/// -1 ESC�˳�
		/// -2 ǿ���˳�
		/// </returns>
		int32 Show();
		const char* Str();
	};
	/// <summary>
	/// �ַ����༭�Ի���
	/// </summary>
	class ApiHmiStrEditDialog : protected HmiStrEditDialog
	{
	public:
		//Str Title
		//MaxInputLen ������볤��
		ApiHmiStrEditDialog(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5, uint32 MaxInputLen);
		//����Ĭ��ֵ
		void SetText(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5);
		//�����Ƿ���Ա༭
		void SetEditAble(bool8 EditAble1, bool8 EditAble2, bool8 EditAble3, bool8 EditAble4, bool8 EditAble5);
		/// <summary>
		/// ��ʾ�༭��
		/// </summary>
		/// <returns>
		///  0 �༭����
		/// -1 ESC�˳�
		/// -2 ǿ���˳�
		/// </returns>
		int32 Show();
		const SalString* GetText(uint32 Index);
	protected:

	};
	/// <summary>
	/// ʱ��༭�Ի���
	/// </summary>
	class ApiHmiDateEditDialog : protected HmiTimeEditDialog
	{
	public:
		//Str Title
		//MaxInputLen ������볤��
		ApiHmiDateEditDialog(const char* Title, SalDateStamp& Stamp);
		/// <summary>
		/// ��ʾ�༭��
		/// </summary>
		/// <returns>
		///  0 �༭����
		/// -1 ESC�˳�
		/// -2 ǿ���˳�
		/// </returns>
		int32 Show();
		SalDateStamp& Stamp();
		SalRtc& Rtc();
	protected:

	};
	/// <summary>
	/// Uint32 �༭��
	/// </summary>
	class ApiHmiUInt32EditDialog : protected HmiUInt32DataDialog
	{
	public:
		/// <summary>
		/// Uint32 �༭��
		/// </summary>
		/// <param name="Title">����</param>
		/// <param name="Min"></param>
		/// <param name="Def">Ĭ��ֵ</param>
		/// <param name="DotNum">С����λ��</param>
		/// <param name="Max"></param>
		ApiHmiUInt32EditDialog(const char* Title, uint32 Min, uint32 Def, uint32 DotNum, uint32 Max);
		/// <summary>
		/// ��ʾ�༭��
		/// </summary>
		/// <returns>
		///  0 �༭����
		/// -1 ESC�˳�
		/// -2 ǿ���˳�
		/// </returns>
		int32 Show();
		uint32 Value();
	};
	/// <summary>
	/// Int32 �༭��
	/// </summary>
	class ApiHmiInt32EditDialog : protected HmiInt32DataDialog
	{
	public:
		/// <summary>
		/// Int32 �༭��
		/// </summary>
		/// <param name="Title">����</param>
		/// <param name="Min"></param>
		/// <param name="Def">Ĭ��ֵ</param>
		/// <param name="DotNum">С����λ��</param>
		/// <param name="Max"></param>
		ApiHmiInt32EditDialog(const char* Title, int32 Min, int32 Def, int32 DotNum, int32 Max);
		/// <summary>
		/// ��ʾ�༭��
		/// </summary>
		/// <returns>
		///  0 �༭����
		/// -1 ESC�˳�
		/// -2 ǿ���˳�
		/// </returns>
		int32 Show();
		int32 Value();
	};
	/// <summary>
	/// Hex32 �༭��
	/// </summary>
	class ApiHmiHex32EditDialog : protected HmiHex32DataDialog
	{
	public:
		/// <summary>
		/// Hex32 �༭��
		/// </summary>
		/// <param name="Title">����</param>
		/// <param name="Min"></param>
		/// <param name="Def">Ĭ��ֵ</param>
		/// <param name="Max"></param>
		ApiHmiHex32EditDialog(const char* Title, int32 Min, int32 Def, int32 Max);
		/// <summary>
		/// ��ʾ�༭��
		/// </summary>
		/// <returns>
		///  0 �༭����
		/// -1 ESC�˳�
		/// -2 ǿ���˳�
		/// </returns>
		int32 Show();
		uint32 Value();
	};
	/// <summary>
	/// Bit32 �༭��
	/// </summary>
	class ApiHmiBit32EditDialog : protected HmiBit32DataDialog
	{
	public:
		/// <summary>
		/// Bit32 �༭��
		/// </summary>
		/// <param name="Title">����</param>
		/// <param name="Min"></param>
		/// <param name="Def">Ĭ��ֵ</param>
		/// <param name="Max"></param>
		///  <param name="Des"></param>
		///  <param name="BitLen">������Ŀ��������8��������</param>
		ApiHmiBit32EditDialog(const char* Title, int32 Min, int32 Def, int32 Max, SalBitDes* Des, uint8 BitLen);
		/// <summary>
		/// ��ʾ�༭��
		/// </summary>
		/// <returns>
		///  0 �༭����
		/// -1 ESC�˳�
		/// -2 ǿ���˳�
		/// </returns>
		int32 Show();
		uint32 Value();
	};
	/// <summary>
	/// Enum32 �༭��
	/// </summary>
	class ApiHmiEnum32EditDialog : protected HmiEnum32DataDialog
	{
	public:
		/// <summary>
		/// Enum32 �༭��
		/// </summary>
		/// <param name="Title">����</param>
		/// <param name="Min"></param>
		/// <param name="Def">Ĭ��ֵ</param>
		/// <param name="Max"></param>
		///  <param name="Des"></param>
		ApiHmiEnum32EditDialog(const char* Title, int32 Min, int32 Def, int32 Max, SalEnumDes* Des);
		/// <summary>
		/// ��ʾ�༭��
		/// </summary>
		/// <returns>
		///  0 �༭����
		/// -1 ESC�˳�
		/// -2 ǿ���˳�
		/// </returns>
		int32 Show();
		uint32 Value();
	};
	/** @} */ // end of ApiHmiDialog
}


#endif // !APIDIALOG_H

