#include"SptProject.h"

using namespace spt;

#include"LcdMain.h"

GraphicDevice& spt::GraphicDevice::Instance()
{
	static GraphicDevice inst;
	return inst;
}
uint16 spt::GraphicDevice::FontHeight()
{
	return CN_FONT16_HEIGHT;
}
uint16 spt::GraphicDevice::FontWidth()
{
	return CN_FONT16_WIDTH;
}
uint16 spt::GraphicDevice::LcdHeight()
{
	return lcdheight;
}
uint16 spt::GraphicDevice::LcdWidth()
{
	return lcdwidth;
}
uint16 spt::GraphicDevice::LcdLineMaxFont()
{
	return lcdwidth / FontWidth();
}
uint16 spt::GraphicDevice::SpaceOfFont()
{
	return 2;
}
void spt::GraphicDevice::DrawAssic(int16 X, int16 Y, int16 Color, const char* str)
{
#ifdef GZK_LCD
	if (!str)
	{
		return;
	}
	uint32 cor = GetColor(Color);
	const uint8* bitmap;
	uint8 data;
	int16 x = X;
	int16 y = Y;
	while (data = *str)
	{
		if (data == '\r')
		{
			x = X;
			y += CN_FONT16_HEIGHT;
			str++;
			if (*str == '\n')
			{
				str++;
			}
		}
		else if (data == '\n')
		{
			x = X;
			y += CN_FONT16_HEIGHT;
			str++;
		}
		else
		{
			bitmap = gASSIC16[*str];
			for (uint8 i = 0; i < CN_FONT16_HEIGHT; i++)
			{
				for (uint8 j = 0; j < CN_FONT16_WIDTH; j++)
				{
					if (GetBit(*bitmap, 7 - j))
					{
						driver->SetPixel(x + j, y + i, cor);
					}
				}
				bitmap++;
			}
			x += CN_FONT16_WIDTH;
			str++;
		}
	}

#else 

	if (!str)
	{
		return;
	}
	LcdDrawAssicMsg msg;
	msg.type = E_DrawAssic;
	msg.x = (uint16)X;
	msg.y = (uint16)Y;
	msg.color = Color;
	msg.len = (uint16)(StrLen(str) + sizeof(msg) - sizeof(msg.msg) + 1);
	MemCpy(msg.msg, str, msg.len);
	HmiLcdCmm::Instance().Send((LcdMsgContext*)&msg);

#endif
}
void spt::GraphicDevice::DrawStr(int16 X, int16 Y, int16 Color, const char* Str)
{
#ifdef GZK_LCD
	if (!Str)
	{
		return;
	}
	uint32 cor = GetColor(Color);
	const uint8* bitmap;
	uint8 data;
	int16 x = X;
	int16 y = Y;
	uint8 sec;
	uint8 loc;
	uint32 seek;
	const uint8* str = (const uint8*)Str;
	while (data = *str)
	{
		if (data == '\r')
		{
			x = X;
			y += CN_FONT16_HEIGHT;
			str++;
			if (*str == '\n')
			{
				str++;
			}
		}
		else if (data == '\n')
		{
			x = X;
			y += CN_FONT16_HEIGHT;
			str++;
		}
		else if (data < 128)
		{
			bitmap = gASSIC16[*str];
			for (uint8 i = 0; i < CN_FONT16_HEIGHT; i++)
			{
				for (uint8 j = 0; j < sizeof(*bitmap) * 8; j++)
				{
					if (GetBit(*bitmap, 7 - j))
					{
						driver->SetPixel(x + j, y + i, cor);
					}
				}
				bitmap++;
			}
			x += CN_FONT16_WIDTH;
			str++;
		}
		else if (str[1] >= 128)
		{
			sec = str[0];
			sec -= 0xa1;
			loc = str[1];
			loc -= 0xa1;
			seek = (94 * sec + loc) * sizeof(g_HZK16[0]);
			if (seek > g_HZK16Len)
			{
				return;
			}
			seek = (94 * sec + loc);
			bitmap = &g_HZK16[seek][0];
			for (uint8 i = 0; i < CN_FONT16_HEIGHT; i++)
			{
				for (uint8 j = 0; j < sizeof(*bitmap) * 8; j++)
				{
					if (GetBit(*bitmap, 7 - j))
					{
						driver->SetPixel(x + j, y + i, cor);
					}
				}
				bitmap++;
			}
			x += CN_FONT16_WIDTH;
			bitmap = &g_HZK16[seek][CN_FONT16_HEIGHT];
			for (uint8 i = 0; i < CN_FONT16_HEIGHT; i++)
			{
				for (uint8 j = 0; j < sizeof(*bitmap) * 8; j++)
				{
					if (GetBit(*bitmap, 7 - j))
					{
						driver->SetPixel(x + j, y + i, cor);
					}
				}
				bitmap++;
			}
			x += CN_FONT16_WIDTH;
			str += 2;
		}
		else
		{
			break;
		}
	}

#else 

	if (!Str)
	{
		return;
	}
	LcdDrawAssicMsg msg;
	msg.type = E_DrawStr;
	msg.x = (uint16)X;
	msg.y = (uint16)Y;
	msg.color = Color;
	msg.len = (uint16)(StrLen(Str) + sizeof(msg) - sizeof(msg.msg) + 1);
	MemCpy(msg.msg, Str, msg.len);
	HmiLcdCmm::Instance().Send((LcdMsgContext*)&msg);

#endif
}
void spt::GraphicDevice::DrawLine(int16 x, int16 y, int16 Color, int16 w, int16 h)
{
#ifdef GZK_LCD
	uint32 cor = GetColor(Color);
	for (int16 i = 0; i < h; i++)
	{
		for (int16 j = 0; j < w; j++)
		{
			driver->SetPixel(x + j, y + i, cor);
		}
	}
#else 
	LcdDrawRect msg;
	msg.type = E_DrawLine;
	msg.x = (uint16)x;
	msg.y = (uint16)y;
	msg.color = Color;
	msg.w = (uint16)w;
	msg.h = (uint16)h;
	msg.len = (uint16)sizeof(msg);
	HmiLcdCmm::Instance().Send((LcdMsgContext*)&msg);
#endif
}
void spt::GraphicDevice::DrawRect(int16 x, int16 y, int16 Color, int16 w, int16 h)
{
#ifdef GZK_LCD
	DrawLine(x, y, Color, w, 1);
	DrawLine(x, y + h - 1, Color, w, 1);
	DrawLine(x, y, Color, 1, h);
	DrawLine(x + w - 1, y, Color, 1, h);
#else 
	LcdDrawRect msg;
	msg.type = E_DrawRect;
	msg.x = (uint16)x;
	msg.y = (uint16)y;
	msg.color = Color;
	msg.w = (uint16)w;
	msg.h = (uint16)h;
	msg.len = (uint16)sizeof(msg);
	HmiLcdCmm::Instance().Send((LcdMsgContext*)&msg);
#endif
}
void spt::GraphicDevice::DrawBitMap(int16 x, int16 y, int16 BitMapCode, int16 Color)
{
	if (BitMapCode >= E_BMT_TOTAL)
	{
		return;
	}
	uint32 cor = GetColor(Color);
	const struct BitMapDes* des = &BitMapInst[BitMapCode];
	const uint8* bitmap;
	for (int16 i = 0; i < des->height; i++)
	{
		for (int16 j = 0; j < des->widthOfByte; j++)
		{
			bitmap = des->buf + des->widthOfByte * i + j;
			for (int16 k = 0; k < 8; k++)
			{
				if (GetBit(*bitmap, 7 - k))
				{
					driver->SetPixel(x + j * 8 + k, y + i, cor);
				}
			}
		}
	}
}
void spt::GraphicDevice::ClearAll()
{
#ifdef GZK_LCD
	uint32 cor = GetColor(Color::E_White);
	for (int16 i = 0; i < lcdheight; i++)
	{
		for (int16 j = 0; j < lcdwidth; j++)
		{
			driver->SetPixel(j, i, cor);
		}
	}
#else 
	LcdDrawCmd msg;
	msg.type = E_ClearAll;
	msg.len = (uint16)sizeof(msg);
	HmiLcdCmm::Instance().Send((LcdMsgContext*)&msg);
#endif
}
void spt::GraphicDevice::ClearRect(int16 x, int16 y, int16 Color, int16 w, int16 h)
{
#ifdef GZK_LCD
	uint32 cor = GetColor(Color);

	for (int16 i = 0; i < h; i++)
	{
		for (int16 j = 0; j < w; j++)
		{
			driver->SetPixel(x + j, y + i, cor);
		}
	}
#else 
	LcdDrawRect msg;
	msg.type = E_ClearRect;
	msg.x = (uint16)x;
	msg.y = (uint16)y;
	msg.color = Color;
	msg.w = (uint16)w;
	msg.h = (uint16)h;
	msg.len = (uint16)sizeof(msg);
	HmiLcdCmm::Instance().Send((LcdMsgContext*)&msg);
#endif
}
void spt::GraphicDevice::DrawUint32(int16 x, int16 y, int16 Color, uint32 data, uint32 FraBit, bool8 FromRight)
{
#ifdef GZK_LCD
#ifdef WIN32_LCD_SIM
	char buf[100];
	sprintf(buf, "%u", data);
	if (FromRight)
	{
		DrawAssic(x - StrLen(buf), y, Color, buf);
	}
	else
	{
		DrawAssic(x, y, Color, buf);
	}
#endif
#else 
	LcdDrawData msg;
	msg.type = E_ClearRect;
	msg.x = (uint16)x;
	msg.y = (uint16)y;
	msg.color = Color;
	msg.data = data;
	msg.fraBit = FraBit;
	msg.isRight = (uint16)FromRight;
	msg.len = (uint16)sizeof(msg);
	HmiLcdCmm::Instance().Send((LcdMsgContext*)&msg);
#endif
}
void spt::GraphicDevice::Update(int16 x, int16 y, int16 w, int16 h)
{
#ifdef GZK_LCD
	driver->Update(x, y, w, h);
#else 
	LcdDrawRect msg;
	msg.type = E_UpdateRect;
	msg.x = (uint16)x;
	msg.y = (uint16)y;
	msg.color = 0;
	msg.w = (uint16)w;
	msg.h = (uint16)h;
	msg.len = (uint16)sizeof(msg);
	HmiLcdCmm::Instance().Send((LcdMsgContext*)&msg);
#endif
}
void spt::GraphicDevice::Update(const HmiRect& rect)
{
	Update(rect.x, rect.y, rect.w, rect.h);
}
void spt::GraphicDevice::Update()
{
#ifdef GZK_LCD
	driver->Update();
#else 
	LcdDrawCmd msg;
	msg.type = E_UpdateAll;
	msg.len = (uint16)sizeof(msg);
	HmiLcdCmm::Instance().Send((LcdMsgContext*)&msg);
#endif
}
uint32 spt::GraphicDevice::GetColor(int16 cor)
{

	switch (cor)
	{
	case spt::GraphicDevice::E_Null:
	{
		return 0;
		break;
	}
	case spt::GraphicDevice::E_Black:
	{
		return 1;
		break;
	}
	case spt::GraphicDevice::E_White:
	{
		return 0;
		break;
	}
	case spt::GraphicDevice::E_Red:
	{
		return 1;
		break;
	}
	case spt::GraphicDevice::E_Yellow:
	{
		return 1;
		break;
	}
	case spt::GraphicDevice::E_Green:
	{
		return 1;
		break;
	}
	default:
		break;
	}
	return 0;
}
int32 spt::GraphicDevice::PowerUpIni(int32 Para)
{
#ifdef GZK_LCD
	lcdheight = driver->PixelOfHeight();
	lcdwidth = driver->PixelOfWidth();
#else 
	const ApiAppCfg* appcfg = SptMain::Instance().AppCfg();
	if (appcfg)
	{
		E_HARDWARE hw = appcfg->platform.hardware;
		//	E_SOFTWARE sw = appcfg->platform.software;
		switch (hw)
		{
		case EH_GZK35KVP:
		{
			lcdheight = 272;
			lcdwidth = 480;

		}
		case EH_GZKCK:
		case EH_GZKSAU31:
		{
			lcdheight = 272;
			lcdwidth = 480;
			break;
		}
		default:
			break;
		}
	}
	else
	{
		lcdheight = 320;
		lcdwidth = 240;
	}
#endif
	return 0;
}
spt::GraphicDevice::GraphicDevice()
{
#ifdef GZK_LCD
	driver = &HalLcdDriver::Instance();
#else 
	hmidriver = &HmiLcdCmm::Instance();
#endif
}
