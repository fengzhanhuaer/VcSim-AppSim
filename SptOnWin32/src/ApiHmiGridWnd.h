#ifndef APIHMIGRIDWND_H
#define APIHMIGRIDWND_H

namespace spt
{
	/** @defgroup ApiHmiDisp
	* Һ����ʾģ��
	* @{
	*/

	/// <summary>
	/// ��񴰿�
	/// </summary>
	class ApiHmiGridWnd :protected HmiGridWnd
	{
	public:
		ApiHmiGridWnd();
		/// <summary>
		/// �����û��������и��µĽ���
		/// </summary>
		/// <param name="UpdateData">���ݸ��º���</param>
		ApiHmiGridWnd(HmiGridWndUpdateData UpdateData);
		/**
		 * @brief ���ô�����Ϣ
		 *
		 * \param Title ��������
		 * \param Crc ���ݵ�CRC�� ��CRC������Ϊ0������CrcLen����Ϊ0
		 * \param CrcLen ���ֽڿ�ȣ���CRC������Ϊ0
		 */
		void SetInfo(const char* Title, uint32 Crc, uint32 CrcLen);
		//�����б���
		void SetColTitle(const char* Title1, const char* Title2, const char* Title3, const char* Title4, const char* Title5, const char* Title6, const char* Title7, const char* Title8, const char* Title9, const char* Title10);
		/// <summary>
		/// �������У�������ʾ
		/// </summary>
		/// <returns></returns>
		struct HmiGridWndDataMapRow* CreatRow();
		/** @brief չʾ���� */
		int32 Show();
		/** @brief �༭���� */
		int32 Edit();
		/**
		 * @brief �Ƿ��������ݱ༭�����ݲ�һ���ı�
		 *
		 * \return
		 */
		bool8 IsEditData();
		/**
		 * @brief �Ƿ�༭�����ݣ����ݷ����˱仯
		 *
		 * \return
		 */
		bool8 IsDataChange();
		/// <summary>
		/// ǿ������ˢ�´���
		/// </summary>
		void ReDraw();
	};
	/** @} */ // end of ApiHmiDisp
}


#endif // !APIHMIGRIDWND_H

