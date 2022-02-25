#ifndef HMIWIDGETS_H
#define HMIWIDGETS_H

namespace spt
{
	class HmiWidObject
	{
	public:
		HmiWidObject();
	public:
		virtual int32 Show();
		const HmiRect& Rect() { return rect; };
		bool8 SetRect(const HmiRect& Rect);
		bool8 SetRect(int16 x, int16 y, int16 w, int16 h);
		bool8 SetPos(int16 x, int16 y);
		bool8 SetPosX(int16 x);
		bool8 SetPosY(int16 y);
		bool8 IsInied() { return isInied; }
		bool8 IsUpdate() { return isUpdate; }
		bool8 IsUpdateSelf() { return isUpdateSelf; }
		bool8 IsUpdateChild() { return isUpdateChild; }
		bool8 IsCanBeSelect() { return isCanBeSelect; }
		bool8 IsSelected() { return isSelected; }
		bool8 IsEnable() { return isEnable; };
		bool8 SetInied(bool8 is);
		bool8 SetEnable(bool8 is);
		bool8 SetUpdate(bool8 is);
		bool8 SetUpdateSelf(bool8 is);
		bool8 SetUpdateChild(bool8 is);
		bool8 SetUpdateParent(bool8 is);
		bool8 SetPeriodUpdate(bool8 isEnable, uint32 Period);
		bool8 SetCanBeSelect(bool8 is);
		bool8 SetSelected(bool8 is);
		bool8 SetReDraw(bool8 is);
		GraphicDevice::Color& Color() { return color; };
		GraphicDevice::Color& Backcolor() { return backcolor; };
		void*& ClientData() { return clientData; };
		bool8 AddChild(class HmiWidObject* Object);
		void ClearRect();
		bool8 Update();
	protected:
		virtual int32 ShowSelf();
		virtual int32 ShowChild();
		virtual int32 ShowPeriod();
		HmiWidObject* FindFirstSelChild();
		HmiWidObject* FindLastSelChild();
		HmiWidObject* Go2LastSelChild();
		HmiWidObject* Go2NextSelChild();
	protected:
		static GraphicDevice* gd;
		static HmiKeyService* key;
		HmiRect rect;
		bool8 isInied;
		bool8 isReDraw;
		bool8 isUpdate;
		bool8 isUpdateSelf;
		bool8 isUpdateChild;
		bool8 isCanBeSelect;
		bool8 isSelected;
		bool8 isEnable;
		uint16 page;
		uint16 row;
		uint16 col;
		GraphicDevice::Color color;
		GraphicDevice::Color backcolor;
		MsPeriodTimer periodUpdateTimer;
		class HmiWidObject* childList;
		class HmiWidObject* childListEnd;
		class HmiWidObject* lastObject;
		class HmiWidObject* nextObject;
		class HmiWidObject* parent;
		class HmiWidObject* cursepos;
		void* clientData;
		friend  void HmiMainFramePowerUpIni();
	};
	class HmiWidLine :public HmiWidObject
	{
	public:
		void SetStartPos(int16 x, int16 y);
		void SetEndPos(int16 x, int16 y);
		void SetWidth(int16 Width);
		const HmiPos& StartPos() { return startPos; };
		const HmiPos& EndPos() { return endPos; };
	protected:
		virtual int32 ShowSelf();
	protected:
		HmiPos startPos;
		HmiPos endPos;
		int16 w;
	};
	class HmiWidRect :public HmiWidObject
	{
	public:

	protected:
		virtual int32 ShowSelf();
	protected:

	};
	class HmiWidTextLine :public HmiWidObject
	{
	public:
		HmiWidTextLine();
		bool8 SetText(const char* Text);
		const SalString& Text() { return text; };
		bool8 SetText(uint16 Index, char Data);
	protected:
		virtual int32 ShowSelf();
	protected:
		String100B text;
	};
	class HmiWidDataLine :public HmiWidObject
	{
	public:
		HmiWidDataLine();
		void SetData(uint8 Type, u64value Value, bool8 IsFromRight, uint8 Len, uint8 DotLen, bool8 IsAddZero);
		void SetData(u64value Value);
		const SalString& Text() { return text; };
		const st64value& Data() { return data; }
	protected:
		virtual int32 ShowSelf();
	protected:
		String40B text;
		st64value data;
	};
	class HmiWidCurseTextLine :public HmiWidTextLine
	{
	public:
		HmiWidCurseTextLine();
		uint16 SetRow(uint16 Row);
		uint16 SetCol(uint16 Col);
		uint16 Col() { return col; };
		uint16 Row() { return row; };
		void ClearRect();
	protected:
		virtual int32 ShowSelf();
	protected:
		uint16 row;
		uint16 col;
	};
	class HmiWidTextLineRect :public HmiWidObject
	{
	public:
		bool8 SetText(const char* Text);
		const SalString& Text() { return text; };
	protected:
		virtual int32 ShowSelf();
	protected:
		String100B text;
	};
	class HmiWidTextWnd :public HmiWidObject
	{
	public:
		HmiWidTextWnd();
		void SetInfo(const char* Title, uint32 crc, uint32 crcLen, uint32  page, uint32 TotalPage);
		void SetPage(uint16 page);
		void SetLine(uint16 line);
		void SetCrc(uint32 crc, uint32 crcLen);
		void SetTitle(const char* Title);
		void SetTotalPage(uint16 page);
		void SetTotalLine(uint16 line);
		const HmiRect GetRect(uint16 StartRow, uint16 StartCol, uint16 W, uint16 H);
		uint16 DispMaxCtxLine();
		uint16 DispMaxCtxWidth();
		uint16 Page() { return page; };
		uint16 TotalPage() { return totalPage; };
		void SetText(uint32 Row, uint32 Col, const char* Text);
		void ClearCtx();
		void ClearCtxLine(uint32 LineNum);
	protected:
		virtual int32 ShowSelf();
		virtual int32 ShowChild();
	protected:
		char title[30];
		char ctx[20][60];
		char ctxUpdate[40];
		HmiRect titleRect;
		HmiRect ctxRect;
		HmiWidCurseTextLine curse;
		bool8 isUpdateTitle;
		bool8 isUpdateCtx;
		uint8 crcLen;
		uint16 maxCtxLine;
		uint16 maxCtxW;
		uint32 crc;
		uint16 line;
		uint16 totalLine;
		uint16 lastLine;
		uint16 page;
		uint16 totalPage;
		uint16 lastPage;
	};
	void HmiMainFramePowerUpIni();
}

#endif // !HMIWIDGETS_H

