#include "LcdMain.h"
using namespace spt;

uint8 lcdBufbits[HalLcdDriver::MaxPixelOfHeight][(HalLcdDriver::MaxPixelOfWidth * HalLcdDriver::BitsOfOnePixel + 7) / 8];

int16 spt::HalLcdDriver::PixelOfWidth()
{
	return 480;
}

int16 spt::HalLcdDriver::PixelOfHeight()
{
	return 272;
}
bool8 spt::HalLcdDriver::SetPixel(int16 x, int16 y, uint32 Color)
{
	if (!IsOkPos(x, y))
	{
		return 0;
	}
	if (Color)
	{
		SetBit(lcdBufbits[y][x / 8], 7 - x % 8, 1);
	}
	else
	{
		SetBit(lcdBufbits[y][x / 8], 7 - x % 8, 0);
	}

	return 1;
}
uint32 spt::HalLcdDriver::GetPixel(int16 x, int16 y)
{
	return GetBit(lcdBufbits[y][x / 8], 7 - x % 8);
}
void spt::HalLcdDriver::Update()
{
	LcdWriteDispBuf(0, 0, MaxPixelOfWidth, MaxPixelOfHeight, lcdBufbits, M_ArrLen(lcdBufbits[0]), M_ArrLen(lcdBufbits));
	update = 1;
}
void spt::HalLcdDriver::Update(int16 x, int16 y, int16 w, int16 h)
{
	if (!IsOkPos(x, y))
	{
		return;
	}
	if (!IsOkPos(x + w - 1, y + h - 1))
	{
		return;
	}
	LcdWriteDispBuf(x, y, w, h, lcdBufbits, M_ArrLen(lcdBufbits[0]), M_ArrLen(lcdBufbits));
	update = 1;
}
void spt::HalLcdDriver::OneLoop()
{
	if (!update)
	{
		if (!flush.IsEnable())
		{
			flush.UpCnt(500);
			flush.Enable(1);
		}
		if (!flush.Status())
		{
			return;
		}
	}
	else
	{
		flush.Restart();
		update = 0;
		return;
	}
	update = 0;
	flush.Restart();
	LcdWriteDispBuf(0, 0, PixelOfWidth(), PixelOfHeight(), lcdBufbits, M_ArrLen(lcdBufbits[0]), M_ArrLen(lcdBufbits));

}
bool8 spt::HalLcdDriver::IsOkPos(int16 x, int16 y)
{
	if ((x >= PixelOfWidth()) || (y >= PixelOfHeight()))
	{
		return 0;
	}
	return 1;
}
void spt::HalLcdDriver::SetBuf(int16 x, int16 y, void* Buf, int16 W)
{
	if ((x >= PixelOfWidth()) || (y >= PixelOfHeight()))
	{
		return;
	}
	MemCpy(&lcdBufbits[y][x / 8], Buf,W );
}
void* spt::HalLcdDriver::GetBuf(int16 x, int16 y)
{
	return nullptr;
}
void spt::HalLcdDriver::PowerUpIni(int32 Para)
{


}
spt::HalLcdDriver::~HalLcdDriver()
{

}


HalLcdDriver& spt::HalLcdDriver::Instance()
{
	static HalLcdDriver inst;
	return inst;
}
spt::HalLcdDriver::HalLcdDriver()
{


}


