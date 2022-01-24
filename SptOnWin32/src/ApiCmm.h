#ifndef APICMM_H
#define APICMM_H

namespace spt
{
	/** @defgroup ApiCpuCmm
	* CPU����ģ��
	* @{
	*/
	/// <summary>
	/// ���ٽ���(�ж��ڵĽ���)
	/// ������ƽ̨/��һ��װ��(�������жϼ��΢����-100�ֽ����ڣ������жϼ��250us��������ÿ���жϷ���150�ֽ�)
	/// </summary>
	class ApiAppFastCmm :protected SptAppFastCmm
	{
	public:
		/// <summary>
		/// Ӧ�ÿ������ݽ���
		/// </summary>
		/// <param name="Sur"></param>
		/// <param name="Dst"></param>
		/// <param name="BufLen">��20�ֽڵ�֡ͷ</param>
		int32 PowerUpIni(CmmMsgDriver* Driver, uint32 DriverNum, uint16 Sur, uint16 Dst, uint16 BufNum, uint16 BufLen);
		int32 SendMsg(uint32 UnPackIndex, uint16 Type, uint16 DataLen, void* Data);
		int32 SendMsgTo(uint16 Dst, uint32 UnPackIndex, uint16 Type, uint16 DataLen, void* Data);
		static ApiAppFastCmm& Instance();
	private:
		ApiAppFastCmm(const char* Name);
	};
	/// <summary>
	/// ���ٽ���(CmmTask�Ľ���)
	/// ������ƽ̨/��һ��װ��(�������жϼ��΢����800�ֽ�����)
	/// </summary>
	class ApiAppSlowCmm :protected SptAppSlowCmm
	{
	public:
		ApiAppSlowCmm(const char* Name);
		/// <summary>
		/// Ӧ���������ݽ���
		/// </summary>
		/// <param name="Sur"></param>
		/// <param name="Dst"></param>
		/// <param name="BufLen">��20�ֽڵ�֡ͷ</param>
		int32 PowerUpIni(CmmMsgDriver* Driver, uint32 DriverNum, uint16 Sur, uint16 Dst, uint16 BufNum, uint16 BufLen);
		int32 SendMsg(uint32 UnPackIndex, uint16 Type, uint16 DataLen, void* Data);
		int32 SendMsgTo(uint16 Dst, uint32 UnPackIndex, uint16 Type, uint16 DataLen, void* Data);
	private:

	};


	/** @} */ // end of ApiCpuCmm
}


#endif
