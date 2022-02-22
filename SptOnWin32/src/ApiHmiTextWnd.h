#ifndef APIHMITEXTWND_H
#define APIHMITEXTWND_H

namespace spt
{
	/// <summary>
	/// 文本窗口
	/// </summary>
	class ApiHmiTextWnd :protected HmiTextWnd
	{
	public:
		/// <summary>
		/// 设置标题
		/// </summary>
		/// <param name="Title"></param>
		void SetTitle(const char* Title);
		/// <summary>
		/// 设置标题，总页数
		/// </summary>
		/// <param name="Title"></param>
		/// <param name="TotalPage"></param>
		void SetTitle(const char* Title, uint32 TotalPage);
		/// <summary>
		/// 设置标题，总页数
		/// </summary>
		/// <param name="Title"></param>
		/// <param name="TotalPage"></param>
		void SetTotalPage(uint32 TotalPage);
		/// <summary>
		/// 页缓冲区大小
		/// </summary>
		/// <returns></returns>
		uint32 MaxPageCache();
		/// <summary>
		/// 设置单页的字符串
		/// 以‘\n’换行
		/// </summary>
		/// <param name="Page"></param>
		/// <param name="Text"></param>
		void SetPage(uint32 Page, const char* Text);
		/// <summary>
		/// 显示
		/// </summary>
		int32 Show();
		/// <summary>
		/// 文本窗口
		/// </summary>
		/// <param name="Mode">E_SinglePage单页模式E_ScrollPage滚动模式 E_ContinuePage连续页模式</param>
		/// <param name="UpdateFunction">数据更新函数</param>
		ApiHmiTextWnd(DispType Mode, UpdateHmiTextWnd UpdateFunction);
	protected:

	};

}

#endif // !APIHMITEXTWND_H

