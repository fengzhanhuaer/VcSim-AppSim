#ifndef APICMM_H
#define APICMM_H

namespace spt
{
	/** @defgroup ApiCpuCmm
	* CPU交互模块
	* @{
	*/
	/// <summary>
	/// 快速交互(中断内的交互)
	/// 国产化平台/新一代装置(限制在中断间隔微秒数-100字节以内，例如中断间隔250us，则限制每个中断发送150字节)
	/// </summary>
	class ApiAppFastCmm :protected SptAppFastCmm
	{
	public:
		/// <summary>
		/// 应用快速数据交互
		/// </summary>
		/// <param name="Sur"></param>
		/// <param name="Dst"></param>
		/// <param name="BufLen">含20字节的帧头</param>
		int32 PowerUpIni(CmmMsgDriver* Driver, uint32 DriverNum, uint16 Sur, uint16 Dst, uint16 BufNum, uint16 BufLen);
		int32 SendMsg(uint32 UnPackIndex, uint16 Type, uint16 DataLen, void* Data);
		int32 SendMsgTo(uint16 Dst, uint32 UnPackIndex, uint16 Type, uint16 DataLen, void* Data);
		static ApiAppFastCmm& Instance();
	private:
		ApiAppFastCmm(const char* Name);
	};
	/// <summary>
	/// 慢速交互(CmmTask的交互)
	/// 国产化平台/新一代装置(限制在中断间隔微秒数800字节以内)
	/// </summary>
	class ApiAppSlowCmm :protected SptAppSlowCmm
	{
	public:
		ApiAppSlowCmm(const char* Name);
		/// <summary>
		/// 应用慢速数据交互
		/// </summary>
		/// <param name="Sur"></param>
		/// <param name="Dst"></param>
		/// <param name="BufLen">含20字节的帧头</param>
		int32 PowerUpIni(CmmMsgDriver* Driver, uint32 DriverNum, uint16 Sur, uint16 Dst, uint16 BufNum, uint16 BufLen);
		int32 SendMsg(uint32 UnPackIndex, uint16 Type, uint16 DataLen, void* Data);
		int32 SendMsgTo(uint16 Dst, uint32 UnPackIndex, uint16 Type, uint16 DataLen, void* Data);
	private:

	};


	/** @} */ // end of ApiCpuCmm
}


#endif
