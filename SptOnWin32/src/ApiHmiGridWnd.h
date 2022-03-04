#ifndef APIHMIGRIDWND_H
#define APIHMIGRIDWND_H

namespace spt
{
	/** @defgroup ApiHmiDisp
	* 液晶显示模块
	* @{
	*/

	/// <summary>
	/// 表格窗口
	/// </summary>
	class ApiHmiGridWnd :protected HmiGridWnd
	{
	public:
		ApiHmiGridWnd();
		/// <summary>
		/// 构造用户可以自行更新的界面
		/// </summary>
		/// <param name="UpdateData">数据更新函数</param>
		ApiHmiGridWnd(HmiGridWndUpdateData UpdateData);
		/**
		 * @brief 设置窗口信息
		 *
		 * \param Title 窗口名称
		 * \param Crc 数据的CRC， 无CRC则设置为0，并将CrcLen设置为0
		 * \param CrcLen 的字节宽度，无CRC则设置为0
		 */
		void SetInfo(const char* Title, uint32 Crc, uint32 CrcLen);
		//设置行标题
		void SetColTitle(const char* Title1, const char* Title2, const char* Title3, const char* Title4, const char* Title5, const char* Title6, const char* Title7, const char* Title8, const char* Title9, const char* Title10);
		/// <summary>
		/// 建立新行，用于显示
		/// </summary>
		/// <returns></returns>
		struct HmiGridWndDataMapRow* CreatRow();
		/** @brief 展示数据 */
		int32 Show();
		/** @brief 编辑数据 */
		int32 Edit();
		/**
		 * @brief 是否发生了数据编辑，数据不一定改变
		 *
		 * \return
		 */
		bool8 IsEditData();
		/**
		 * @brief 是否编辑了数据，数据发生了变化
		 *
		 * \return
		 */
		bool8 IsDataChange();
		/// <summary>
		/// 强制重新刷新窗口
		/// </summary>
		void ReDraw();
	};
	/** @} */ // end of ApiHmiDisp
}


#endif // !APIHMIGRIDWND_H

