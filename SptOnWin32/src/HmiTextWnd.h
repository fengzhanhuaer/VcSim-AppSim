#ifndef HMITEXTWND_H
#define HMITEXTWND_H
namespace spt
{
	class HmiTextWndPage
	{
	public:
		uint16 Page();
		void SetPage(uint32 Page, const char* Text);
		void Clear();
		void SetUpdate();
		SalString& String() { return ctx; };
	protected:
		String5000B ctx;
		uint16 dispPageNum;
		uint16 firstDispLine;
		bool8 isctxupdate;
	};
	typedef int32(*UpdateHmiTextWnd)(class HmiTextWnd& Wnd, uint16 Page, uint16 TotalPage, HmiKey key);
	class HmiTextWnd :public HmiWidTextWnd
	{
	public:
		static const uint32 CN_Max_WndCell = 20;
		enum DispType
		{
			E_SinglePage,//��ҳģʽ
			E_ScrollPage,//����ҳģʽ,����һҳ��ʾ�������
			E_ContinuePage,//����ҳģʽ,����Ϊ��λ������ʾ�����綯������
		};
	public:
		HmiTextWnd(DispType Mode);
		void SetPage(uint32 Page, const char* Text);
		int32 Show();
		void IniAllPage();
		HmiTextWndPage* GetWndCell(uint32 Index);
		HmiTextWndPage* GetWndPage(uint32 Page);
	protected:
		virtual int32 ShowSelf();
		void ShowSinglePage();
		void ShowScrollPage();
		void ShowContinuePage();
	protected:
		UpdateHmiTextWnd updateFunc;
		DispType mode;
		static HmiTextWndPage text[CN_Max_WndCell];
	};
}

#endif // !HMITEXTWND_H

