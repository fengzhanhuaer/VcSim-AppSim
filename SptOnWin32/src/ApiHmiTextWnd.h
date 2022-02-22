#ifndef APIHMITEXTWND_H
#define APIHMITEXTWND_H

namespace spt
{
	/// <summary>
	/// �ı�����
	/// </summary>
	class ApiHmiTextWnd :protected HmiTextWnd
	{
	public:
		/// <summary>
		/// ���ñ���
		/// </summary>
		/// <param name="Title"></param>
		void SetTitle(const char* Title);
		/// <summary>
		/// ���ñ��⣬��ҳ��
		/// </summary>
		/// <param name="Title"></param>
		/// <param name="TotalPage"></param>
		void SetTitle(const char* Title, uint32 TotalPage);
		/// <summary>
		/// ���ñ��⣬��ҳ��
		/// </summary>
		/// <param name="Title"></param>
		/// <param name="TotalPage"></param>
		void SetTotalPage(uint32 TotalPage);
		/// <summary>
		/// ҳ��������С
		/// </summary>
		/// <returns></returns>
		uint32 MaxPageCache();
		/// <summary>
		/// ���õ�ҳ���ַ���
		/// �ԡ�\n������
		/// </summary>
		/// <param name="Page"></param>
		/// <param name="Text"></param>
		void SetPage(uint32 Page, const char* Text);
		/// <summary>
		/// ��ʾ
		/// </summary>
		int32 Show();
		/// <summary>
		/// �ı�����
		/// </summary>
		/// <param name="Mode">E_SinglePage��ҳģʽE_ScrollPage����ģʽ E_ContinuePage����ҳģʽ</param>
		/// <param name="UpdateFunction">���ݸ��º���</param>
		ApiHmiTextWnd(DispType Mode, UpdateHmiTextWnd UpdateFunction);
	protected:

	};

}

#endif // !APIHMITEXTWND_H

