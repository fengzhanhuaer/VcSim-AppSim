#ifndef APIBOARD_H
#define APIBOARD_H

namespace spt
{
	/// <summary>
	/// 智能板卡信息
	/// </summary>
	class ApiSmartBoardInfo :protected SptGoSvStateBoard
	{
	public:
		/**
		 * @brief 初始化板卡信息.
		 *
		 * \param Name
		 * \param DesName
		 * \param CardNo 板卡序号，由FPGA程序定义，非实际的板卡号
		 * \param NetNum  网口数目
		 */
		void PowerUpIni(const char* Name, const char* DesName, uint32 CardNo, uint32 NetNum);
		uint32 StateNum();
		//Index 网口号
		//
		/**
		 * @brief 获取网口状态.
		 *
		 * \param Index	网口号
		 * \return
		 */
		const SptGoSvStateBoard::NetState* NetState(uint16 Index);
		/**
		 * @brief  FPGA运行状态
		 *
		 * \param FPGAIndex FPGA序号（仅有一个FPGA时，则为0）
		 * \return 0x5555为BOOT模式，0xAAAA为正常模式
		 */
		uint16 RunState(uint32 FPGAIndex);
		/// <summary>
		/// 自检状态
		/// </summary>
		const struct stOutStatus* CheckStatus() { return &ostatus; };
		/// <summary>
		/// SV配置接收状态
		/// </summary>
		/// <param name="FPGAIndex"></param>
		/// <returns></returns>
		uint32 SvRecCfgRecState(uint32 FPGAIndex);
		/// <summary>
		/// GOOSE配置接收状态
		/// </summary>
		/// <param name="FPGAIndex"></param>
		/// <returns></returns>
		uint32 GoRecCfgRecState(uint32 FPGAIndex, uint32 StateIndex);
		/// <summary>
		/// FPGA每秒钟时钟计数
		/// </summary>
		/// <returns></returns>
		uint32 FpgaClkPps();
		/// <summary>
		/// 配置帧接收状态
		/// Bit1:配置结束帧接收成功
		///	Bit0:配置开始帧接收成功
		/// </summary>
		/// <returns></returns>
		uint32 CfgRecState();
	private:

	};





}

#endif
