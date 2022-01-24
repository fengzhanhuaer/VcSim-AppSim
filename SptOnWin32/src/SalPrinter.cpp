#include "ApiProject.h"
using namespace spt;

GBK_SYMBOL& spt::GBK_SYMBOL::Instance()
{
	static GBK_SYMBOL inst;
	return inst;
}

spt::GBK_SYMBOL::GBK_SYMBOL()
{

}

int32 spt::SalPrinter::SetCharBuf(void* Buf, uint32 BufSize)
{
	Clear();
	SetBuf(Buf, 1, BufSize);
	bottom = top = 0;
	return 0;
}

void spt::SalPrinter::ClearContext()
{
	if (!bufBase)
	{
		return;
	}
	bufBase[0] = 0;
	bottom = top = 0;
}

int32 spt::SalPrinter::Print2(SalFile& File)
{
	if (!bufBase)
	{
		return -1;
	}
	uint32 s = BufSize();
	if (!s)
	{
		return -1;
	}
	uint32 r = bottom;
	uint32 w = top;
	if (r > w)
	{
		File.Write(&bufBase[r], s - r);
		r = 0;
	}
	if (r < w)
	{
		File.Write(&bufBase[r], w - r);
		r = w;
	}
	bottom = r % s;
	return 0;
}

int32 spt::SalTextPrinter::Print2(SalString& Str)
{
	if (!bufBase)
	{
		return -1;
	}
	uint32 s = BufSize();
	if (!s)
	{
		return -1;
	}
	uint32 r = bottom;
	uint32 w = top;
	if (r > w)
	{
		while (r < s)
		{
			Str << bufBase[r];
			r++;
		}
		r = 0;
	}
	while (r < w)
	{
		Str << bufBase[r];
		r++;
	}
	bottom = r % s;
	return 0;
}

spt::SalTablePrinter::SalTablePrinter()
{
	gridRowPos = gridColPos = gridLineWidth = 0;
}

int32 spt::SalTablePrinter::PrintTableTopLeft()
{
	Write(&GBK_SYMBOL::TableTopLeft, 2);
	return 0;
}

int32 spt::SalTablePrinter::PrintTableTopMidle()
{
	Write(&GBK_SYMBOL::TableTopMiddle, 2);
	return 0;
}

int32 spt::SalTablePrinter::PrintTableTopRight()
{
	Write(&GBK_SYMBOL::TableTopRight, 2);
	return 0;
}

int32 spt::SalTablePrinter::PrintTableMiddleLeft()
{
	Write(&GBK_SYMBOL::TableRightMiddle, 2);
	return 0;
}

int32 spt::SalTablePrinter::PrintTableMiddleMidle()
{
	Write(&GBK_SYMBOL::TableMiddleMiddle, 2);
	return 0;
}

int32 spt::SalTablePrinter::PrintTableMiddleRight()
{
	Write(&GBK_SYMBOL::TableLeftMiddle, 2);
	return 0;
}

int32 spt::SalTablePrinter::PrintTableBottomLeft()
{
	Write(&GBK_SYMBOL::TableBottomLeft, 2);
	return 0;
}

int32 spt::SalTablePrinter::PrintTableBottomMidle()
{
	Write(&GBK_SYMBOL::TableBottomMiddle, 2);
	return 0;
}

int32 spt::SalTablePrinter::PrintTableBottomRight()
{
	Write(&GBK_SYMBOL::TableBottomRight, 2);
	return 0;
}

int32 spt::SalTablePrinter::PrintHorizontalText(const char* Txt, uint32 Width, TableFmt Fmt)
{
	uint32 Len = StrLen(Txt);
	if (!Width)
	{
		Width = Len;
	}
	switch (Fmt)
	{
	case spt::SalTablePrinter::TF_Null:
		break;
	case spt::SalTablePrinter::TF_TopLeft:
	{
		Write((void*)Txt, Len);
		if (Len < Width)
		{
			PrintTextSpace(Width - Len);
		}
		break;
	}
	case spt::SalTablePrinter::TF_TopMiddle:
		if (Len < Width)
		{
			PrintTextSpace((Width - Len) / 2);
		}
		Write((void*)Txt, Len);
		if (Len < Width)
		{
			PrintTextSpace((Width - Len) / 2);
		}
		break;
	case spt::SalTablePrinter::TF_TopRight:
	{
		if (Len < Width)
		{
			PrintTextSpace(Width - Len);
		}
		Write((void*)Txt, Len);
		break;
	}
	case spt::SalTablePrinter::TF_MiddleLeft:
		break;
	case spt::SalTablePrinter::TF_MiddleMiddle:
		break;
	case spt::SalTablePrinter::TF_MiddleRight:
		break;
	case spt::SalTablePrinter::TF_BottomLeft:
		break;
	case spt::SalTablePrinter::TF_BottomMiddle:
		break;
	case spt::SalTablePrinter::TF_BottomRight:
		break;
	default:
		break;
	}
	bufBase[top] = 0;
	return 0;
}

int32 spt::SalTablePrinter::Print2(SalString& Str)
{
	if (!bufBase)
	{
		return -1;
	}
	uint32 s = BufSize();
	if (!s)
	{
		return -1;
	}
	uint32 r = bottom;
	uint32 w = top;
	while (r < w)
	{
		Str << bufBase[r];
		r++;
	}
	bottom = r % s;
	return 0;
}

int32 spt::SalTablePrinter::SetGridLineWidth(uint32 Width)
{
	ClearContext();
	gridLineWidth = Width;
	gridRowPos = 0;
	gridColPos = 0;
	return 0;
}

int32 spt::SalTablePrinter::AddTableCell(const char* Txt, uint32 Row, uint32 Col, uint32 RowSpan, uint32 ColSpan, bool8 IsDrawBottomRight, bool8 IsVerticalLine, TableFmt Fmt)
{
	if (RowSpan < 2)
	{
		LogErr.Stamp() << "SalTablePrinter::AddTableCell RowSpan is less than 2.\n";
		return -1;
	}
	if (ColSpan < 2)
	{
		LogErr.Stamp() << "SalTablePrinter::AddTableCell ColSpan is less than 2.\n";
		return -1;
	}
	uint32 EndRowLoop = Row + RowSpan;
	uint32 EndColLoop = Col + ColSpan;
	if (gridRowPos <= EndRowLoop)
	{
		for (uint32 i = gridRowPos; i < EndRowLoop; i++)
		{
			uint32 EndLoop2 = gridLineWidth;
			for (uint32 j = 0; j < EndLoop2; j++)
			{
				ReWrite(i, j, GBK_SYMBOL::HzSpace);
			}
			ReWrite(i, gridRowPos, GBK_SYMBOL::Enter);
		}
		gridRowPos = EndRowLoop;
	}
	//左上角
	int32 code = GetHzCode(Row, Col);
	uint8 first = ((uint8)code);
	if (first == 0xa9)
	{
		if (code == GBK_SYMBOL::TableVerticalLine)
		{
			ReWrite(Row, Col, GBK_SYMBOL::TableLeftMiddle);
		}
		else if (code == GBK_SYMBOL::TableHorizontalLine)
		{
			ReWrite(Row, Col, GBK_SYMBOL::TableTopMiddle);
		}
		else if (code == GBK_SYMBOL::TableBottomLeft)
		{
			ReWrite(Row, Col, GBK_SYMBOL::TableLeftMiddle);
		}
		else if (code == GBK_SYMBOL::TableBottomRight)
		{
			ReWrite(Row, Col, GBK_SYMBOL::TableMiddleMiddle);
		}
		else
		{
			ReWrite(Row, Col, GBK_SYMBOL::TableTopLeft);
		}
	}
	else
	{
		ReWrite(Row, Col, GBK_SYMBOL::TableTopLeft);
	}
	//右上角
	code = GetHzCode(Row, EndColLoop - 1);
	first = ((uint8)code);
	if (first == 0xa9)
	{
		if (code == GBK_SYMBOL::TableVerticalLine)
		{
			ReWrite(Row, EndColLoop - 1, GBK_SYMBOL::TableRightMiddle);
		}
		else if (code == GBK_SYMBOL::TableHorizontalLine)
		{
			ReWrite(Row, EndColLoop - 1, GBK_SYMBOL::TableTopMiddle);
		}
		else if (code == GBK_SYMBOL::TableBottomRight)
		{
			ReWrite(Row, EndColLoop - 1, GBK_SYMBOL::TableMiddleMiddle);
		}
		else
		{
			ReWrite(Row, EndColLoop - 1, GBK_SYMBOL::TableTopRight);
		}
	}
	else
	{
		ReWrite(Row, EndColLoop - 1, GBK_SYMBOL::TableTopRight);
	}
	if (IsDrawBottomRight)
	{
		//左下角
		int32 code = GetHzCode(EndRowLoop - 1, Col);
		uint8 first = ((uint8)code);
		if (first == 0xa9)
		{
			if (code == GBK_SYMBOL::TableVerticalLine)
			{
				ReWrite(EndRowLoop - 1, Col, GBK_SYMBOL::TableRightMiddle);
			}
			else if (code == GBK_SYMBOL::TableHorizontalLine)
			{
				ReWrite(EndRowLoop - 1, Col, GBK_SYMBOL::TableBottomMiddle);
			}
			else if (code == GBK_SYMBOL::TableBottomRight)
			{
				ReWrite(EndRowLoop - 1, Col, GBK_SYMBOL::TableMiddleMiddle);
			}
			else
			{
				ReWrite(EndRowLoop - 1, Col, GBK_SYMBOL::TableBottomLeft);
			}
		}
		else
		{
			ReWrite(EndRowLoop - 1, Col, GBK_SYMBOL::TableBottomLeft);
		}
		//右下角
		code = GetHzCode(EndRowLoop - 1, Col);
		first = ((uint8)code);
		if (first == 0xa9)
		{
			if (code == GBK_SYMBOL::TableVerticalLine)
			{
				ReWrite(EndRowLoop - 1, EndColLoop - 1, GBK_SYMBOL::TableLeftMiddle);
			}
			else if (code == GBK_SYMBOL::TableHorizontalLine)
			{
				ReWrite(EndRowLoop - 1, EndColLoop - 1, GBK_SYMBOL::TableTopMiddle);
			}
			else if (code == GBK_SYMBOL::TableBottomRight)
			{
				ReWrite(EndRowLoop - 1, EndColLoop - 1, GBK_SYMBOL::TableMiddleMiddle);
			}
			else
			{
				ReWrite(EndRowLoop - 1, EndColLoop - 1, GBK_SYMBOL::TableBottomRight);
			}
		}
		else
		{
			ReWrite(EndRowLoop - 1, EndColLoop - 1, GBK_SYMBOL::TableBottomRight);
		}
	}
	//左边线
	for (uint32 i = Row + 1; i < EndRowLoop; i++)
	{
		code = GetHzCode(i, Col);
		first = ((uint8)code);
		if (first == 0xa9)
		{
			if (code == GBK_SYMBOL::TableLeftMiddle)
			{
				ReWrite(i, Col, GBK_SYMBOL::TableVerticalLine);
			}
			else if (code == GBK_SYMBOL::TableMiddleMiddle)
			{
				ReWrite(i, Col, GBK_SYMBOL::TableRightMiddle);
			}
			else
			{
				ReWrite(i, Col, GBK_SYMBOL::TableVerticalLine);
			}
		}
		else
		{
			ReWrite(i, Col, GBK_SYMBOL::TableVerticalLine);
		}
	}
	//上边线
	for (uint32 i = Col + 1; i < EndColLoop; i++)
	{
		int32 code = GetHzCode(Row, i);
		uint8 first = ((uint8)code);
		if (first == 0xa9)
		{
			if (code == GBK_SYMBOL::TableMiddleMiddle)
			{
				ReWrite(Row, i, GBK_SYMBOL::TableBottomMiddle);
			}
			else
			{
				ReWrite(Row, i, GBK_SYMBOL::TableHorizontalLine);
			}
		}
		else
		{
			ReWrite(Row, i, GBK_SYMBOL::TableHorizontalLine);
		}
	}
	if (ColSpan > 2)
	{
		//右边线
		for (uint32 i = Row + 1; i < EndRowLoop; i++)
		{
			code = GetHzCode(i, EndColLoop - 1);
			first = ((uint8)code);
			if (first == 0xa9)
			{
				if (code == GBK_SYMBOL::TableLeftMiddle)
				{
					ReWrite(i, EndColLoop - 1, GBK_SYMBOL::TableVerticalLine);
				}
				else if (code == GBK_SYMBOL::TableMiddleMiddle)
				{
					ReWrite(i, EndColLoop - 1, GBK_SYMBOL::TableLeftMiddle);
				}
				else
				{
					ReWrite(i, EndColLoop - 1, GBK_SYMBOL::TableVerticalLine);
				}
			}
			else
			{
				ReWrite(i, EndColLoop - 1, GBK_SYMBOL::TableVerticalLine);
			}
		}
		//下边线
		for (uint32 i = Col + 1; i < EndColLoop; i++)
		{
			int32 code = GetHzCode(EndRowLoop - 1, i);
			uint8 first = ((uint8)code);
			if (first == 0xa9)
			{
				if (code == GBK_SYMBOL::TableMiddleMiddle)
				{
					ReWrite(EndRowLoop - 1, i, GBK_SYMBOL::TableBottomMiddle);
				}
				else
				{
					ReWrite(EndRowLoop - 1, i, GBK_SYMBOL::TableHorizontalLine);
				}
			}
			else
			{
				ReWrite(EndRowLoop - 1, i, GBK_SYMBOL::TableHorizontalLine);
			}
		}
	}
	if (IsVerticalLine)
	{
		String1000B str;
		TransString ts;
		ts.SetBuf(Txt);
		uint32 cols = Col + 1;
		while (ts.GetLine(str))
		{
			uint32 rows = Row + 1;
			const unsigned char* s = (const unsigned char*)str.Str();
			while (*s)
			{
				if ((s[0] > 127) && (s[1] > 127))
				{
					uint16 u16 = (s[1] << 8) | s[0];
					ReWrite(rows, cols, u16);
					s += 2;
				}
				else
				{
					uint8 u8 = s[0];
					ReWrite(rows, cols, u8);
					s += 1;
				}
				rows++;
			}
			cols++;
		}
	}
	else
	{
		String1000B str;
		TransString ts;
		ts.SetBuf(Txt);
		uint32 col = Col + 1;
		uint32 row = Row + 1;
		while (ts.GetLine(str))
		{
			switch (Fmt)
			{
			case spt::SalTablePrinter::TF_Null:
				break;
			case spt::SalTablePrinter::TF_TopLeft:
				ReWrite(row, col, str.Str());
				break;
			case spt::SalTablePrinter::TF_TopMiddle:
				ReWrite(row, col + (ColSpan - 2 - str.StrLen()) / 2, str.Str());
				break;
			case spt::SalTablePrinter::TF_TopRight:
				ReWrite(row, col + (ColSpan - 2 - str.StrLen()), str.Str());
				break;
			case spt::SalTablePrinter::TF_MiddleLeft:
				break;
			case spt::SalTablePrinter::TF_MiddleMiddle:
				break;
			case spt::SalTablePrinter::TF_MiddleRight:
				break;
			case spt::SalTablePrinter::TF_BottomLeft:
				break;
			case spt::SalTablePrinter::TF_BottomMiddle:
				break;
			case spt::SalTablePrinter::TF_BottomRight:
				break;
			default:
				break;
			}
			row++;
		}
	}
	return 0;
}

int32 spt::SalTablePrinter::Write(const void* Buf, uint32 Len)
{
	uint32 EndLen = Len + top;
	if (EndLen < elementNum)
	{
		uint8* buf = (uint8*)Buf;
		for (uint32 i = 0; i < Len; i++)
		{
			bufBase[top++] = *buf++;
		}
		bufBase[top] = 0;
		return 0;
	}
	return -1;
}

int32 spt::SalTablePrinter::ReWrite(uint32 Row, uint32 Col, uint8 Txt)
{
	uint32 pos = (Row * (gridLineWidth * 2 + 2)) + Col;
	if (pos < elementNum)
	{
		bufBase[pos] = Txt;
		if (pos > top)
		{
			top = pos + 1;
			if (top >= elementNum)
			{
				top = elementNum - 1;
			}
			bufBase[top] = 0;
		}
	}
	return -1;
}

int32 spt::SalTablePrinter::ReWrite(uint32 Row, uint32 Col, uint16 Txt)
{
	uint32 pos = (Row * (gridLineWidth * 2 + 2)) + Col * 2;
	if (pos < elementNum)
	{
		bufBase[pos] = (uint8)(Txt);
		bufBase[pos + 1] = (uint8)(Txt >> 8);
		if (pos > top)
		{
			top = pos + 2;
			if (top < elementNum)
			{
				bufBase[top] = 0;
			}
		}
	}
	return -1;
}

int32 spt::SalTablePrinter::ReWrite(uint32 Row, uint32 Col, const char* Txt)
{
	Col = Col * 2;
	while (*Txt)
	{
		ReWrite(Row, Col, (uint8)*Txt);
		Txt++;
	}
	return 0;
}

int32 spt::SalTablePrinter::GetHzCode(uint32 Row, uint32 Col)
{
	uint32 pos = (Row * (gridLineWidth * 2 + 2)) + Col * 2;
	if (pos < elementNum)
	{
		return ((uint16)bufBase[pos + 1] << 8) | (bufBase[pos]);
	}
	return -1;
}

int32 spt::SalTablePrinter::PrintTextSpace(uint32 Width)
{
	uint32 EndLen = Width + top;
	if (EndLen < elementNum)
	{
		for (uint32 i = 0; i < Width; i++)
		{
			bufBase[top++] = GBK_SYMBOL::Instance().Space;
		}
		bufBase[top] = 0;
	}
	return -1;
}

int32 spt::SalTablePrinter::PrintTableVerticalLine(uint32 Width)
{
	Width = Width / 2;
	for (uint32 i = 0; i < Width; i++)
	{
		Write(&GBK_SYMBOL::TableVerticalLine, 2);
	}
	return 0;
}

int32 spt::SalTablePrinter::PrintTableHorizontalLine(uint32 Height)
{
	for (uint32 i = 0; i < Height; i++)
	{
		Write(&GBK_SYMBOL::TableHorizontalLine, 2);
	}
	return 0;
}
