#ifndef HMITEXTWND_H
#define HMITEXTWND_H
namespace spt
{
	class HmiTextWndCell :public HmiWidContextAreaMultiTextLine
	{
	public:
		virtual void ShowSelf(ShowType Type);
		uint16 DispPageNum();
		//���ñ�ҳ��ҳ��
		void SetDispPageNum(uint16 Page);
		uint16 FirstDispLine();
		uint16 SetFirstDispLine(uint16 FirstDispLine);
	protected:
		uint16 dispPageNum;
		uint16 firstDispLine;
	};
	typedef int32(*UpdateHmiTextWnd)(class HmiTextWnd& Wnd, uint16 Page, uint16 TotalPage, HmiKey key);
	class HmiTextWnd :public HmiWidSinglePage
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
		void Show();
		void IniAllPage();
		HmiTextWndCell* GetWndCell(uint32 Index);
		void SetFirstTextPage(uint16 Page);
		uint16 FirstTextPage();
	protected:
		void AutoLayerOut();
		void ShowSinglePage();
		void ShowScrollPage();
		void ShowContinuePage();
	protected:
		UpdateHmiTextWnd updateFunc;
		uint16 firstTextPage;
		uint16 curLine;
		uint16 totalLine;
		DispType mode;
		HmiTextWndCell scrollPage;
		static HmiTextWndCell text[CN_Max_WndCell];
	};
}

#endif // !HMITEXTWND_H

