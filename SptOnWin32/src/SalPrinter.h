#ifndef SALPRINTER_H
#define SALPRINTER_H

namespace spt
{
	/// <summary>
	/// GBK���볣�÷���
	/// </summary>
	struct GBK_SYMBOL
	{
	public:
		/// <summary>
		/// "��"
		/// </summary>
		static const uint16 TableTopLeft = 0xB0A9;
		/// <summary>
		/// "��"
		/// </summary>
		static const uint16 TableTopRight = 0xB4A9;
		/// <summary>
		/// "��"
		/// </summary>
		static const uint16 TableBottomLeft = 0xB8A9;
		/// <summary>
		/// "��"
		/// </summary>
		static const uint16 TableBottomRight = 0xBCA9;
		/// <summary>
		/// "��"
		/// </summary>
		static const uint16 TableLeftMiddle = 0xC0A9;
		/// <summary>
		/// "��"
		/// </summary>
		static const uint16 TableRightMiddle = 0xC8A9;
		/// <summary>
		/// "��"
		/// </summary>
		static const uint16 TableTopMiddle = 0xD0A9;
		/// <summary>
		/// "��"
		/// </summary>
		static const uint16 TableBottomMiddle = 0xD8A9;
		/// <summary>
		/// "��"
		/// </summary>
		static const uint16 TableMiddleMiddle = 0xE0A9;
		/// <summary>
		/// "��"
		/// </summary>
		static const uint16 TableVerticalLine = 0xA6A9;
		/// <summary>
		/// "��"
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
	class SalEscPk2Printer
	{
	public:
		SalEscPk2Printer(void* buf, uint32 BufLen);
	protected:
	private:
		uint8* buf;
		uint32 bufLen;
		uint32 writer;
	};

	class SalVirPrinter
	{
	public:
		int32 PowerUpIni();
	protected:

	};

}

#endif // !SALPRINTER_H

