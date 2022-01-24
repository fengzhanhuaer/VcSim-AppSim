#ifndef SALSTRING_H
#define SALSTRING_H

namespace spt
{
	class SalString :protected SingleStackBuf
	{
	public:
		char* Str();
		const char* Str()const;
		bool8 operator==(const char* Buf)const;
		bool8 operator!=(const char* Buf)const;
		SalString& operator=(const char* Buf);
		SalString& operator<<(const char* Buf);
		SalString& operator<<(SalString& String);
		SalString& operator<<(const char Flag);
		SalString& operator<<(int32 Data);
		SalString& operator<<(int64 Data);
		SalString& operator<<(uint32 Data);
		SalString& operator<<(uint64 Data);
		SalString& FormatHex(uint8 Hex);
		SalString& FormatHex(uint16 Hex);
		SalString& FormatHex(uint32 Hex);
		SalString& FormatBin(uint8 Hex);
		SalString& FormatBin(uint16 Hex);
		SalString& FormatBin(uint32 Hex);
		SalString& FormatHex(uint64 Hex);
		SalString& FormatHex(uint8* Hex, uint32 Count);
		SalString& FormatHex(uint16* Hex, uint32 Count);
		SalString& FormatHex(uint32* Hex, uint32 Count);
		SalString& FormatMs(uint64 Data);
		//定点数转浮点显示，DotNum小数位数
		SalString& Format(int32 Data, uint8 DotNum);
		SalString& Format(uint32 Data, uint8 DotNum);
		SalString& Format(int64 Data, uint8 DotNum);
		SalString& Format(uint64 Data, uint8 DotNum);
		SalString& Format(int32 Data, uint16 Len, uint8 DotNum, char FromLeft, char AddFlag);
		SalString& Format(uint32 Data, uint16 Len, uint8 DotNum, char FromLeft, char AddFlag);
		SalString& Format(int64 Data, uint16 Len, uint8 DotNum, char FromLeft, char AddFlag);
		SalString& Format(uint64 Data, uint16 Len, uint8 DotNum, char FromLeft, char AddFlag);
		SalString& Format(uint16 Data, uint8 Len, char AddFlag);
		SalString& Format(int16 Data, uint8 Len, char AddFlag);
		SalString& Format(uint32 Data, uint8 Len, char AddFlag);
		SalString& Format(int32 Data, uint8 Len, char AddFlag);
		SalString& Format(uint64 Data, uint8 Len, char AddFlag);
		SalString& Format(int64 Data, uint8 Len, char AddFlag);
		SalString& Format(const char* Msg, uint16 Len, char FromLeft, char AddFlag);
		SalString& FillToLen(uint32 Len, char AddFlag);
		int32 IsInclude(const char* SubStr);
		int32 CharNum(char Flag);
		void Replace(char oldchar, char newchar);
		void Reverse();
		void Clear();
		int32 StrLen();
		int32 StrBufLen();
	protected:
		void SetBuf(char* Buf, uint32 BufSize);
	private:

	};

	template<const uint32 BufLen>
	class StaticString :public SalString
	{
	public:
		StaticString() { buf[0] = 0; SetBuf(buf, BufLen); }
		SalString& operator=(const char* Buf) { (*(SalString*)(this)) = Buf; return *this; };
	private:
		char buf[BufLen + 1];
	};

	typedef StaticString<10> String10B;
	typedef StaticString<20> String20B;
	typedef StaticString<30> String30B;
	typedef StaticString<40> String40B;
	typedef StaticString<100> String100B;
	typedef StaticString<200> String200B;
	typedef StaticString<500> String500B;
	typedef StaticString<1000> String1000B;
	typedef StaticString<2000> String2000B;
	typedef StaticString<5000> String5000B;
	typedef StaticString<1 * 1024> String1kB;
	typedef StaticString<50 * 1024> String50kB;
	typedef StaticString<100 * 1024> String100kB;
	typedef StaticString<500 * 1024> String500kB;
	typedef StaticString<1024 * 1024> String1MB;
	class TransString
	{
	public:
		void SetBuf(const char* Buf);
		void GetHex(uint32& data, uint8 StopFlag);
		uint64 GetHex(uint8 StopFlag, uint32 DataLen);
		bool8 Get(char& data);
		void Get(uint32& data, uint8 StopFlag);
		void Get(int32& data, uint8 StopFlag);
		void GetFixedInt(int32& data, uint8 StopFlag, uint8& DotNum);//获取定点数据,DotNum为输出值，表示字符串实际解析到的小数位数
		void GetFixedInt(uint32& data, uint8 StopFlag, uint8& DotNum);//获取定点数据,DotNum为输出值，表示字符串实际解析到的小数位数
		void Get(SalString& data, uint8 StopFlag);
		bool8 GetLine(SalString& data);
		bool8 GetLine(SalString& data, uint8 StopFlag);
		bool8 IsEnd();
	protected:

	private:
		int len;
		int pos;
		const char* sur;
	};

}




#endif // !SALSTRING_H
