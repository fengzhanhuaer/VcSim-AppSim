#ifndef SALPRINTER_H
#define SALPRINTER_H

namespace spt
{
	/// <summary>
	/// GBK编码常用符号
	/// </summary>
	struct GBK_SYMBOL
	{
	public:
		/// <summary>
		/// "┌"
		/// </summary>
		static const uint16 TableTopLeft = 0xB0A9;
		/// <summary>
		/// "┐"
		/// </summary>
		static const uint16 TableTopRight = 0xB4A9;
		/// <summary>
		/// "└"
		/// </summary>
		static const uint16 TableBottomLeft = 0xB8A9;
		/// <summary>
		/// "┘"
		/// </summary>
		static const uint16 TableBottomRight = 0xBCA9;
		/// <summary>
		/// "├"
		/// </summary>
		static const uint16 TableLeftMiddle = 0xC0A9;
		/// <summary>
		/// "┤"
		/// </summary>
		static const uint16 TableRightMiddle = 0xC8A9;
		/// <summary>
		/// "┬"
		/// </summary>
		static const uint16 TableTopMiddle = 0xD0A9;
		/// <summary>
		/// "┴"
		/// </summary>
		static const uint16 TableBottomMiddle = 0xD8A9;
		/// <summary>
		/// "┼"
		/// </summary>
		static const uint16 TableMiddleMiddle = 0xE0A9;
		/// <summary>
		/// "│"
		/// </summary>
		static const uint16 TableVerticalLine = 0xA6A9;
		/// <summary>
		/// "─"
		/// </summary>
		static const uint16 TableHorizontalLine = 0xA4A9;
		/// <summary>
		/// " "
		/// </summary>
		static const uint8 Space = 0x20;
		/// <summary>
		/// "  "
		/// </summary>
		static const uint16 HzSpace = 0x2020;
		/// <summary>
		/// "\r\n"
		/// </summary>
		static const uint16 Enter = 0x0D0A;
	public:
		static GBK_SYMBOL& Instance();
	private:
		GBK_SYMBOL();
	};

	class SalPrinter :protected RingCharBuf
	{
	public:
		int32 SetCharBuf(void* Buf, uint32 BufSize);
		void ClearContext();
		int32 Print2(SalFile& File);
	private:
	};
	class SalTextPrinter :public SalPrinter
	{
	public:

	public:
		int32 Print2(SalString& Str);
	};
	class SalTablePrinter :public SalPrinter
	{
	public:

	public:
		enum TableFmt
		{
			TF_Null,
			TF_TopLeft,
			TF_TopMiddle,
			TF_TopRight,
			TF_MiddleLeft,
			TF_MiddleMiddle,
			TF_MiddleRight,
			TF_BottomLeft,
			TF_BottomMiddle,
			TF_BottomRight,
		};
		/// <summary>
		/// 初级打印接口
		/// </summary>
	public:
		SalTablePrinter();
		int32 PrintTableTopLeft();
		int32 PrintTableTopMidle();
		int32 PrintTableTopRight();
		int32 PrintTableMiddleLeft();
		int32 PrintTableMiddleMidle();
		int32 PrintTableMiddleRight();
		int32 PrintTableBottomLeft();
		int32 PrintTableBottomMidle();
		int32 PrintTableBottomRight();
		int32 PrintTextSpace(uint32 Width);
		int32 PrintTableVerticalLine(uint32 Width);
		int32 PrintTableHorizontalLine(uint32 Height);
		int32 PrintHorizontalText(const char* Txt, uint32 Width = 0, TableFmt Fmt = TF_TopLeft);
		int32 Print2(SalString& Str);
		/// <summary>
		/// 中级打印接口
		/// </summary>
	public:
		int32 SetGridLineWidth(uint32 Width);
		int32 AddTableCell(const char* Txt, uint32 Row, uint32 Col, uint32 RowSpan, uint32 ColSpan, bool8 IsDrawBottomRight, bool8 IsVerticalLine, TableFmt Fmt);
	protected:
		int32 Write(const void* Buf, uint32 Len);
		int32 ReWrite(uint32 Row, uint32 Col, uint8 Txt);
		int32 ReWrite(uint32 Row, uint32 Col, uint16 Txt);
		int32 ReWrite(uint32 Row, uint32 Col, const char* Txt);
		int32 GetHzCode(uint32 Row, uint32 Col);
	protected:
		uint32 gridLineWidth;
		uint32 gridRowPos;
		uint32 gridColPos;
	};

}

#endif // !SALPRINTER_H

