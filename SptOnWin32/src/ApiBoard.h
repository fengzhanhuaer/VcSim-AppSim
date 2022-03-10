#ifndef APIBOARD_H
#define APIBOARD_H

namespace spt
{
	/// <summary>
	/// ���ܰ忨��Ϣ
	/// </summary>
	class ApiSmartBoardInfo :protected SptGoSvStateBoard
	{
	public:
		/**
		 * @brief ��ʼ���忨��Ϣ.
		 *
		 * \param Name
		 * \param DesName
		 * \param CardNo �忨��ţ���FPGA�����壬��ʵ�ʵİ忨��
		 * \param NetNum  ������Ŀ
		 */
		void PowerUpIni(const char* Name, const char* DesName, uint32 CardNo, uint32 NetNum);
		uint32 StateNum();
		//Index ���ں�
		//
		/**
		 * @brief ��ȡ����״̬.
		 *
		 * \param Index	���ں�
		 * \return
		 */
		const SptGoSvStateBoard::NetState* NetState(uint16 Index);
		/**
		 * @brief  FPGA����״̬
		 *
		 * \param FPGAIndex FPGA��ţ�����һ��FPGAʱ����Ϊ0��
		 * \return 0x5555ΪBOOTģʽ��0xAAAAΪ����ģʽ
		 */
		uint16 RunState(uint32 FPGAIndex);
		/// <summary>
		/// �Լ�״̬
		/// </summary>
		const struct stOutStatus* CheckStatus() { return &ostatus; };
		/// <summary>
		/// SV���ý���״̬
		/// </summary>
		/// <param name="FPGAIndex"></param>
		/// <returns></returns>
		uint32 SvRecCfgRecState(uint32 FPGAIndex);
		/// <summary>
		/// GOOSE���ý���״̬
		/// </summary>
		/// <param name="FPGAIndex"></param>
		/// <returns></returns>
		uint32 GoRecCfgRecState(uint32 FPGAIndex, uint32 StateIndex);
		/// <summary>
		/// FPGAÿ����ʱ�Ӽ���
		/// </summary>
		/// <returns></returns>
		uint32 FpgaClkPps();
		/// <summary>
		/// ����֡����״̬
		/// Bit1:���ý���֡���ճɹ�
		///	Bit0:���ÿ�ʼ֡���ճɹ�
		/// </summary>
		/// <returns></returns>
		uint32 CfgRecState();
	private:

	};





}

#endif
