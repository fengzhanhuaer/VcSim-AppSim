#ifndef HMIWIDGETS_H
#define HMIWIDGETS_H

namespace spt
{
	class HmiWidObject
	{
	public:
		enum ShowType
		{
			E_AllFrame,
			E_Update,
		};
	public:
		virtual void UpdateCheck(ShowType Type);
		virtual void Show(ShowType Type);
		virtual void ShowSelf(ShowType Type);
		virtual void ShowChild(ShowType Type);
		virtual int32 Edit();
		virtual int32 EditSelf(HmiKeyMsg key);
		virtual int32 EditChild(HmiKeyMsg key);
	public:
		virtual void ResetStatus();
		virtual bool8 IsClass(const void* Addr);
		HmiRect& Rect();
		void SetRect(int16 x, int16 y, int16 w, int16 h);
		bool8& IsCanBeSelect() { return isCanBeSelect; };
		bool8& IsSelected() { return isSelected; };
		bool8& IsEnable() { return isEnable; };
		bool8& IsVisible() { return isVisible; };
		bool8& IsUpdate() { return isUpdate; };
		void SetUpdate();
		GraphicDevice::Color& Color();
		GraphicDevice::Color& BackColor();
		void SetVisible(bool8 En);
		void AddChild(HmiWidObject* Child);
		void DeleteAllChild();
		HmiWidObject* Last() { return last; };
		HmiWidObject* Next() { return next; };
		HmiWidObject* Parent() { return parent; }
		HmiWidObject* FirstChild() { return firstchild; }
		HmiWidObject* LastChild() { return lastchild; }
		HmiWidObject* SelectedChild() { return selectedChild; };
		HmiWidObject* SetSelectedChildAt(int32 Index);
		HmiWidObject* GoToNextCanBeSelected();
		HmiWidObject* GoToLastCanBeSelected();
	protected:
		HmiWidObject();
	protected:
		static GraphicDevice* gd;
		static HmiKeyService* key;
	protected:
		bool8 isCanBeSelect;
		bool8 isSelected;
		bool8 isUpdate;
		bool8 isFirst;
		bool8 isEnable;
		bool8 isVisible;
		HmiRect rect;
		E_SalValType valType;
		st32value value;
		uint32 childNum;
		GraphicDevice::Color color;
		GraphicDevice::Color backcolor;
		HmiWidObject* parent;
		HmiWidObject* firstchild;
		HmiWidObject* lastchild;
		HmiWidObject* last;
		HmiWidObject* next;
		HmiWidObject* selectedChild;
		friend  void HmiMainFramePowerUpIni();
	};
	class HmiWidLine :public HmiWidObject
	{
	public:
		HmiWidLine();
		virtual void ShowSelf(ShowType Type)override;

	};
	class HmiWidRect :public HmiWidObject
	{
	public:
		HmiWidRect();
		virtual void ShowSelf(ShowType Type)override;
		void UnShow();
	};
	class HmiWidTextLine :public HmiWidObject
	{
	public:
		void SetText(const char* Text);
		void SetRect(int16 x, int16 y, int16 StrLen, int16 h);
		void SetPos(int16 x, int16 y, int16 StrLen);
		virtual void ResetStatus();
		HmiWidTextLine();
		SalString& Text();
		bool8& IsFromRight();
	public:
		virtual void ShowSelf(ShowType Type)override;
	protected:
		bool8 isFromRight;
		String100B text;
	};
	class HmiWidDataLine :public HmiWidObject
	{
	public:
		void SetData(uint8 Type, u64value Value, bool8 IsFromRight, uint8 Len, uint8 DotLen, bool8 IsAddZero);
		virtual void ResetStatus();
		HmiWidDataLine();
		bool toStr(SalString& Str);
		bool8& IsFromRight();
		st64value& Data() { return data; }
	public:
		virtual void ShowSelf(ShowType Type)override;
	protected:
		bool8 isFromRight;
		bool8 isAddZero;
		st64value data;
	};
	class HmiWidCurseText :public HmiWidTextLine
	{
	public:
		HmiWidCurseText();
	public:
		uint16 Col;
		uint16 Row;
	};
	class HmiWidTextMultiLine :public HmiWidObject
	{
	public:
		void SetText(const char* Text);
		SalString& Text();
	public:
		virtual void ShowSelf(ShowType Type)override;
	protected:
		String2000B text;
	};
	class HmiWidTextRect :public HmiWidRect
	{
	public:
		void SetText(const char* Text);
		SalString& Text();
		void AppendText(const char* Text);
	public:
		virtual void ShowSelf(ShowType Type)override;
	protected:
		HmiWidTextMultiLine text;
	};
	class HmiWidContextArea :public HmiWidRect
	{
	public:
		virtual bool8 IsClass(const void* Addr);
		virtual void Show(ShowType Type);
		virtual void ShowSelf(ShowType Type);
		uint32 MaxDispColNum();
		uint32 MaxDispRowNum();
		HmiRect GetTextRect(uint32 Row, uint32 Col, uint32 Len);
		void SetText(uint32 Row, uint32 Col, const char* Text);
		HmiWidContextArea();
		static const void* ClassAddr();
		void AutoLayerOut();
	protected:
		static const uint32 CN_Max_Row = 20;
		static const uint32 CN_Max_Col = 60;
		uint32 maxRowNum;
		uint32 maxColNum;
		char rowUpdate[CN_Max_Row];
		char dispBuf[CN_Max_Row][CN_Max_Col + 1];

	};
	class HmiWidContextAreaCell :public HmiWidObject
	{
	public:
		virtual bool8 IsClass(const void* Addr);
		static const void* ClassAddr();
		virtual void ShowSelf(ShowType Type);
		bool8 IsHmiWidContextParent();
		HmiWidContextAreaCell();
		virtual void ResetStatus();
	public:
		uint16 Col;
		uint16 Row;
	};
	class HmiWidContextAreaTextLine : public HmiWidContextAreaCell
	{
	public:
		void SetText(const char* Str);
		SalString& Text();
		virtual void ShowSelf(ShowType Type);
		virtual void ResetStatus();
	public:
		uint16 Len;
		bool8 isFromRight;
	protected:
		String100B text;
	};
	class HmiWidContextAreaDataLine : public HmiWidContextAreaCell
	{
	public:
		void SetData(uint8 Type, u64value Value, bool8 IsFromRight, uint8 Len, uint8 DotLen, bool8 IsAddZero);
		virtual void ResetStatus();
		HmiWidContextAreaDataLine();
		bool toStr(SalString& Str);
		bool8& IsFromRight();
		st64value& Data() { return data; }
		virtual void ShowSelf(ShowType Type);
	public:
		uint16 Len;
	protected:
		bool8 isAddZero;
		bool8 isFromRight;
		st64value data;
	};
	class HmiWidContextAreaMultiTextLine : public HmiWidContextAreaCell
	{
	public:
		void SetText(const char* Str);
		SalString& Text();
		virtual void ShowSelf(ShowType Type);
		uint32 LineNum();
	protected:
		String5000B text;
	};
	class HmiWidTitleLine :public HmiWidTextRect
	{
	public:
		void SetInfo(const char* Title, uint32 crc, uint32 crcLen, uint32  page, uint32 TotalPage);
		void SetCrc(uint32 crc, uint32 crcLen);
		void SetTitle(const char* Title);
		void SetPage(uint32  page, uint32 TotalPage);
		void SetLine(uint32  Line, uint32 TotalLine);
		uint32 Page();
		uint32 LastPage();
		uint32 TotalPage();
		uint32 Crc();
		virtual void ShowSelf(ShowType Type);
	protected:
		String40B title;
		uint32 crc;
		uint32 crcLen;
		uint32 page;
		uint32 lastPage;
		uint32 totalPage;
		uint32 line;
		uint32 lastLine;
		uint32 totalLine;
	};
	class HmiWidSinglePage :public HmiWidRect
	{
	public:
		HmiWidSinglePage();
		HmiWidTitleLine& Title() { return title; };
		HmiWidContextArea& Context() { return context; };
		virtual void Show(ShowType Type);
		void AutoLayerOut();
	protected:
		HmiWidTitleLine title;
		HmiWidContextArea context;
	};
	void HmiMainFramePowerUpIni();
}

#endif // !HMIWIDGETS_H

