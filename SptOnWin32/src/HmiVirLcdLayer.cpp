#include"SptProject.h"

using namespace spt;

#include"ApiProject.h"

GraphicDevice& spt::GraphicDevice::Instance()
{
	static GraphicDevice inst;
	return inst;
}
void spt::GraphicDevice::SetDrawMode(GraphicDevice::Mode mode)
{
	drawMode = mode;
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
	if (!str)
	{
		return;
	}
	if (drawMode & E_PicMode)
	{
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
					if (*bitmap)
					{
						for (uint8 j = 0; j < CN_FONT16_WIDTH; j++)
						{
							if (GetBit(*bitmap, 7 - j))
							{
								lcddriver->SetPixel(x + j, y + i, cor);
							}
						}
					}
					bitmap++;
				}
				x += CN_FONT16_WIDTH;
				str++;
			}
		}
	}
	if (drawMode & E_Protocol)
	{
		LcdDrawAssicMsg msg;
		msg.type = E_DrawAssic;
		msg.x = (uint16)X;
		msg.y = (uint16)Y;
		msg.color = Color;
		msg.len = (uint16)(StrLen(str) + sizeof(msg) - sizeof(msg.msg) + 1);
		MemCpy(msg.msg, str, msg.len);
		HmiLcdCmm::Instance().Send((LcdMsgContext*)&msg);
	}

}
void spt::GraphicDevice::DrawStr(int16 X, int16 Y, int16 Color, const char* Str)
{
	if (drawMode & E_PicMode)
	{
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
					if (*bitmap)
					{
						for (uint8 j = 0; j < sizeof(*bitmap) * 8; j++)
						{
							if (GetBit(*bitmap, 7 - j))
							{
								lcddriver->SetPixel(x + j, y + i, cor);
							}
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
					if (*bitmap)
					{
						for (uint8 j = 0; j < sizeof(*bitmap) * 8; j++)
						{
							if (GetBit(*bitmap, 7 - j))
							{
								lcddriver->SetPixel(x + j, y + i, cor);
							}
						}
					}
					bitmap++;
				}
				x += CN_FONT16_WIDTH;
				bitmap = &g_HZK16[seek][CN_FONT16_HEIGHT];
				for (uint8 i = 0; i < CN_FONT16_HEIGHT; i++)
				{
					if (*bitmap)
					{
						for (uint8 j = 0; j < sizeof(*bitmap) * 8; j++)
						{
							if (GetBit(*bitmap, 7 - j))
							{
								lcddriver->SetPixel(x + j, y + i, cor);
							}
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
	}
	if (drawMode & E_Protocol)
	{

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
	}
}
void spt::GraphicDevice::DrawLine(int16 x, int16 y, int16 Color, int16 w, int16 h)
{
	if (drawMode & E_PicMode)
	{
		uint32 cor = GetColor(Color);
		for (int16 i = 0; i < h; i++)
		{
			for (int16 j = 0; j < w; j++)
			{
				lcddriver->SetPixel(x + j, y + i, cor);
			}
		}
	}
	if (drawMode & E_Protocol)
	{
		LcdDrawRect msg;
		msg.type = E_DrawLine;
		msg.x = (uint16)x;
		msg.y = (uint16)y;
		msg.color = Color;
		msg.w = (uint16)w;
		msg.h = (uint16)h;
		msg.len = (uint16)sizeof(msg);
		HmiLcdCmm::Instance().Send((LcdMsgContext*)&msg);
	}
}
void spt::GraphicDevice::DrawLine(int16 sx, int16 sy, int16 ex, int16 ey, int16 Color, int16 w)
{
	if (drawMode & E_PicMode)
	{
		uint32 cor = GetColor(Color);
		if (sx == ex)
		{
			for (int16 i = sy; i < ey; i++)
			{
				for (int16 j = 0; j < w; j++)
				{
					lcddriver->SetPixel(sx + j, i, cor);
				}
			}
		}
		else if (sy == ey)
		{
			for (int16 i = sx; i < ex; i++)
			{
				for (int16 j = 0; j < w; j++)
				{
					lcddriver->SetPixel(i, sy + j, cor);
				}
			}
		}
		else
		{
			float32 dydx = (float32)(ey - sy) / (ex - sx);
			for (int32 i = sx; i < ex; i++)
			{
				int16 y = (int16)(sy + (sx - i) * dydx + 0.5);
				for (int16 k = 0; k < w; k++)
				{
					lcddriver->SetPixel(i + k, y, cor);
				}
			}
		}
	}
	if (drawMode & E_Protocol)
	{
		LcdDrawLine2 msg;
		msg.type = E_DrawLine2;
		msg.sx = (uint16)sx;
		msg.sy = (uint16)sy;
		msg.ex = (uint16)ex;
		msg.ey = (uint16)ey;
		msg.color = Color;
		msg.w = (uint16)w;
		msg.len = (uint16)sizeof(msg);
		HmiLcdCmm::Instance().Send((LcdMsgContext*)&msg);
	}
}
void spt::GraphicDevice::DrawRect(int16 x, int16 y, int16 Color, int16 w, int16 h)
{
	if (drawMode & E_PicMode)
	{
		DrawLine(x, y, Color, w, 1);
		DrawLine(x, y + h - 1, Color, w, 1);
		DrawLine(x, y, Color, 1, h);
		DrawLine(x + w - 1, y, Color, 1, h);
	}
	if (drawMode & E_Protocol)
	{
		LcdDrawRect msg;
		msg.type = E_DrawRect;
		msg.x = (uint16)x;
		msg.y = (uint16)y;
		msg.color = Color;
		msg.w = (uint16)w;
		msg.h = (uint16)h;
		msg.len = (uint16)sizeof(msg);
		HmiLcdCmm::Instance().Send((LcdMsgContext*)&msg);
	}
}
void spt::GraphicDevice::DrawBitMap(int16 x, int16 y, int16 BitMapCode, int16 Color)
{
	if (BitMapCode >= E_BMT_TOTAL)
	{
		return;
	}
	if (drawMode == E_PicMode)
	{
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
						lcddriver->SetPixel(x + j * 8 + k, y + i, cor);
					}
				}
			}
		}
	}
	else if (drawMode == E_Protocol)
	{
		LcdDrawBitMap msg;
		msg.type = E_DrawBitMap;
		msg.x = (uint16)x;
		msg.y = (uint16)y;
		msg.color = Color;
		msg.code = BitMapCode;
		msg.len = (uint16)sizeof(msg);
		HmiLcdCmm::Instance().Send((LcdMsgContext*)&msg);
	}
}
void spt::GraphicDevice::ClearAll()
{
	if (drawMode & E_PicMode)
	{
		uint32 cor = GetColor(Color::E_Yellow);
		for (int16 i = 0; i < lcdheight; i++)
		{
			for (int16 j = 0; j < lcdwidth; j++)
			{
				lcddriver->SetPixel(j, i, cor);
			}
		}
	}
	if (drawMode & E_Protocol)
	{
		LcdDrawCmd msg;
		msg.type = E_ClearAll;
		msg.len = (uint16)sizeof(msg);
		HmiLcdCmm::Instance().Send((LcdMsgContext*)&msg);
	}
}
void spt::GraphicDevice::ClearRect(int16 x, int16 y, int16 Color, int16 w, int16 h)
{
	if (drawMode & E_PicMode)
	{
		uint32 cor = GetColor(Color);

		for (int16 i = 0; i < h; i++)
		{
			for (int16 j = 0; j < w; j++)
			{
				lcddriver->SetPixel(x + j, y + i, cor);
			}
		}
	}
	if (drawMode & E_Protocol)
	{
		LcdDrawRect msg;
		msg.type = E_ClearRect;
		msg.x = (uint16)x;
		msg.y = (uint16)y;
		msg.color = Color;
		msg.w = (uint16)w;
		msg.h = (uint16)h;
		msg.len = (uint16)sizeof(msg);
		HmiLcdCmm::Instance().Send((LcdMsgContext*)&msg);
	}
}
void spt::GraphicDevice::DrawUint32(int16 x, int16 y, int16 Color, uint32 data, uint32 FraBit, bool8 FromRight)
{
	if (drawMode & E_PicMode)
	{
		String100B str;
		str.Format(data, FraBit);
		if (FromRight)
		{
			DrawAssic(x - StrLen(str.Str()), y, Color, str.Str());
		}
		else
		{
			DrawAssic(x, y, Color, str.Str());
		}
	}
	if (drawMode & E_Protocol)
	{
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
	}
}
void spt::GraphicDevice::Update(int16 x, int16 y, int16 w, int16 h)
{
	if (drawMode & E_PicMode)
	{
		lcddriver->Update(x, y, w, h);
	}
	if (drawMode & E_Protocol)
	{
		LcdDrawRect msg;
		msg.type = E_UpdateRect;
		msg.x = (uint16)x;
		msg.y = (uint16)y;
		msg.color = 0;
		msg.w = (uint16)w;
		msg.h = (uint16)h;
		msg.len = (uint16)sizeof(msg);
		HmiLcdCmm::Instance().Send((LcdMsgContext*)&msg);
	}
}
void spt::GraphicDevice::Update(const HmiRect& rect)
{
	Update(rect.x, rect.y, rect.w, rect.h);
}
void spt::GraphicDevice::Update()
{
	if (drawMode & E_PicMode)
	{
		lcddriver->Update();
	}
	if (drawMode & E_Protocol)
	{
		LcdDrawCmd msg;
		msg.type = E_UpdateAll;
		msg.len = (uint16)sizeof(msg);
		HmiLcdCmm::Instance().Send((LcdMsgContext*)&msg);
	}
}
void spt::GraphicDevice::UpdateLcd()
{
	if (drawMode & E_PicMode)
	{
		if (!lcdUpdateTimer.Status())
		{
			if (!lcdUpdateTimer.IsEnable())
			{
				lcdUpdateTimer.UpCnt(200);
				lcdUpdateTimer.Enable(1);
			}
			return;
		}
		LcdPicMode msg;
		uint16 w = lcdwidth / 8;
		uint16 linn = 8;
		for (uint16 i = 0; i < lcdheight; i += linn)
		{
			msg.type = E_DrawPicLine;
			msg.len = sizeof(msg) - sizeof(msg.data) + linn * w;
			msg.x = 0;
			msg.y = i;
			msg.w = w;
			msg.h = linn;
			for (uint16 j = 0; j < linn; j++)
			{
				MemCpy(msg.data + j * w, lcddriver->GetBuf(0, i + j), w);
			}
			HmiLcdCmm::Instance().Send((LcdPicMode*)&msg);
		}
		msg.type = E_DrawPicUpdate;
		msg.len = sizeof(msg) - sizeof(msg.data);
		msg.x = 0;
		msg.y = 0;
		msg.w = w;
		msg.h = lcdheight;
		HmiLcdCmm::Instance().Send((LcdPicMode*)&msg);
	}
	else
	{
		return;
	}
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
	const ApiAppCfg* appcfg = SptMain::Instance().AppCfg();
	if (appcfg)
	{
		E_HARDWARE hw = appcfg->platform.hardware;
		//	E_SOFTWARE sw = appcfg->platform.software;
		switch (hw)
		{
		case EH_GZK35KVP:
		case EH_GZK35KVSMART:
		{
			lcdheight = 240;
			lcdwidth = 320;
			SetDrawMode(E_PicMode);
			break;
		}
		case EH_GZKCK:
		case EH_GZKSAU:
		{
			lcdheight = 272;
			lcdwidth = 480;
			SetDrawMode(E_PicMode);
			break;
		}
		default:
			lcdheight = 240;
			lcdwidth = 320;
			SetDrawMode(E_PicMode);
			break;
		}
	}
	else
	{
		SetDrawMode(E_PicMode);
		lcdheight = 240;
		lcdwidth = 320;
	}
	return 0;
}
spt::GraphicDevice::GraphicDevice()
{
	lcddriver = &HalLcdDriver::Instance();
	hmidriver = &HmiLcdCmm::Instance();
}

bool8 spt::HmiRect::SetRect(int16 x, int16 y, int16 w, int16 h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	return 1;
}
