#ifndef LCDHALLCDDRIVER_H
#define LCDHALLCDDRIVER_H

namespace spt
{
	class HalLcdDriver
	{
		//public service interface
	public:
		static constexpr uint16 MaxPixelOfWidth = 480;
		static constexpr uint16 MaxPixelOfHeight = 272;
		static constexpr uint16 BitsOfOnePixel = 1;
		int16 PixelOfWidth();
		int16 PixelOfHeight();
		bool8 SetPixel(int16 x, int16 y, uint32 Color);
		uint32 GetPixel(int16 x, int16 y);
		void Update();
		void Update(int16 x, int16 y, int16 w, int16 h);
		void OneLoop();
		bool8 IsOkPos(int16 x, int16 y);
		void* GetBuf(int16 x, int16 y);
		//platform function interface
	public:
		static HalLcdDriver& Instance();
		void PowerUpIni(int32 Para);
	protected:
		HalLcdDriver();
		~HalLcdDriver();
	private:
		bool8 update;
		bool8 first;
		MsTimer flush;
	};

}

#endif // !LCDHALLCDDRIVER_H
