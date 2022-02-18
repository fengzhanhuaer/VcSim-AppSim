#ifndef LCDVIRLACDLAYER_H
#define LCDVIRLACDLAYER_H

#include "LcdFontPixel.h"
#include "LcdBitmap.h"
#include "LcdHalDriver.h"
namespace spt
{
	struct HmiPos
	{
		int16 x;
		int16 y;
	};
	struct HmiRect
	{
		bool8 SetRect(int16 x, int16 y, int16 w, int16 h);
		void Set(const HmiPos pos) { x = pos.x; y = pos.y; };
		int16 XStart() { return x; }
		int16 XEnd() { return x + w; }//²»º¬
		int16 YStart() { return y; }
		int16 YEnd() { return y + h; }//²»º¬
		HmiPos Pos() const { return HmiPos{ x,y }; }
		int16 x;
		int16 y;
		int16 w;
		int16 h;
	};
	class GraphicDevice
	{
	public:
		enum Mode
		{
			E_Protocol = 0x01,
			E_PicMode = 0x02,
		};
		enum  Color
		{
			E_Null,
			E_Black,
			E_White,
			E_Red,
			E_Yellow,
			E_Green
		};
	public:
		uint16 FontHeight();
		uint16 FontWidth();
		uint16 LcdHeight();
		uint16 LcdWidth();
		uint16 LcdLineMaxFont();
		uint16 SpaceOfFont();
		uint32 DrawMode() { return drawMode; };
	public:
		static GraphicDevice& Instance();
		void SetDrawMode(Mode mode);
		void DrawAssic(int16 x, int16 y, int16 Color, const char* str);
		void DrawStr(int16 x, int16 y, int16 Color, const char* str);
		void DrawLine(int16 x, int16 y, int16 Color, int16 w, int16 h);
		void DrawLine(int16 sx, int16 sy, int16 ex, int16 ey, int16 Color, int16 w);
		void DrawRect(int16 x, int16 y, int16 Color, int16 w, int16 h);
		void DrawBitMap(int16 x, int16 y, int16 BitMapCode, int16 Color);
		void ClearAll();
		void ClearRect(int16 x, int16 y, int16 Color, int16 w, int16 h);
		void DrawUint32(int16 x, int16 y, int16 Color, uint32 data, uint32 FraBit, bool8 FromRight);
		void Update(int16 x, int16 y, int16 w, int16 h);
		void Update(const HmiRect& rect);
		void Update();
	public:
		void UpdateLcd();
		uint32 GetColor(int16 cor);
		int32 PowerUpIni(int32 Para);
	protected:
		GraphicDevice();
	private:
		MsTimer lcdPeriodUpdateTimer;
		MsTimer lcdForceUpdateTimer;
		uint32 drawMode;
		class HalLcdDriver* lcddriver;
		class HmiLcdCmm* hmidriver;
		uint16 lcdheight;
		uint16 lcdwidth;
		bool8 isupdate;
		bool8 isRowUpdate[HalLcdDriver::MaxPixelOfHeight];
		bool8 isCowUpdate[HalLcdDriver::MaxPixelOfWidth];
	};
}



#endif // !LCDHALVIRLACDLAYER_H

