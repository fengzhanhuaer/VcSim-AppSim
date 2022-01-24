#ifndef SALCLASICFUNC_H
#define SALCLASICFUNC_H

namespace spt
{
	typedef void(*vFunction)();
	typedef bool8(*IsOkFunction)();
	extern const uint8 U8OneBitIsTrue[8];
	extern const uint8 U8OneBitIsFalse[8];
	extern const uint16 U16OneBitIsTrue[16];
	extern const uint16 U16OneBitIsFalse[16];
	extern const uint32 U32OneBitIsTrue[32];
	extern const uint32 U32OneBitIsFalse[32];
	void SetBit(uint8& Data, uint8 Bit, uint8 flag);
	void SetBit(uint16& Data, uint8 Bit, uint8 flag);
	void SetBit(uint32& Data, uint8 Bit, uint8 flag);
	bool8 GetBit(const uint8& Data, uint8 Bit);
	bool8 GetBit(const uint16& Data, uint8 Bit);
	bool8 GetBit(const uint32& Data, uint8 Bit);
	void EncryptData(void* Sur, uint32 Len, uint8 Key);
	void DecryptData(void* Sur, uint32 Len, uint8 Key);

	uint8 BitsInvertUint(uint8 data);
	uint16 BitsInvertUint(uint16 data);
	uint32 BitsInvertUint(uint32 data);
	uint16 ByteInvertUint(uint16 data);
	uint32 ByteInvertUint(uint32 data);
	uint32 MinUint32DecData(uint8 DecBit);

	uint16 GetLittleEndian16Bit(void* Sur);
	uint32 GetLittleEndian32Bit(void* Sur);
	uint16 GetBigEndian16Bit(void* Sur);
	uint32 GetBigEndian32Bit(void* Sur);
	uint32 ChangeEndian(void* Dst, void* Sur, uint32 Len);
	float32 Int32FixDot2Float32(int32 data, uint8 Dot);
	uint32 Bcd4BitToDec(uint8 BcdCode);


	class SumCheck
	{
	public:
		static uint8 CalcSum8(uint8* data, uint32 ByteLen);
		static uint16 CalcSum16(uint8* data, uint32 ByteLen);
		static uint16 CalcSum16(uint16* data, uint32 ByteLen);
		static uint32 CalcSum32(uint8* data, uint32 ByteLen);
		static uint32 CalcSum32(uint16* data, uint32 ByteLen);
		static uint32 CalcSum32(uint32* data, uint32 ByteLen);
	public:
		static bool8 IsOkCalcSum8(uint8* data, uint32 ByteLen);
		static bool8 IsOkCalcSum16(uint8* data, uint32 ByteLen);
		static bool8 IsOkCalcSum16(uint16* data, uint32 ByteLen);
		static bool8 IsOkCalcSum32(uint8* data, uint32 ByteLen);
		static bool8 IsOkCalcSum32(uint16* data, uint32 ByteLen);
		static bool8 IsOkCalcSum32(uint32* data, uint32 ByteLen);
	};
	class Crc8Check
	{
	public:
		Crc8Check(uint8 IniValue, uint8 Xorvalue, uint8 Outxorvalue, bool8 RightFirst);
		//ByteLen不含校验码
		uint8 CalCrc(const void* data, uint32 ByteLen);
		//ByteLen含校验码
		bool8 IsCrcOk(const void* data, uint32 ByteLen);
	private:
		uint8 table[256];
		uint8 iniValue;
		uint8 xorValue;
		uint8 outxorvalue;
		bool8 rightFirst;
	};
	class Crc16Check
	{
	public:
		Crc16Check(uint16 IniValue, uint16 Xorvalue, uint16 Outxorvalue, bool8 RightFirst);
		Crc16Check(uint16(*table)[256], uint16 IniValue, uint16 Xorvalue, uint16 Outxorvalue, bool8 RightFirst);
	public:
		//BufLen不含CRC
		uint16 CalCrc(const void* data, uint32 ByteLen);
		//BufLen不含CRC
		uint16 CalCrc(uint16 Crc, const void* data, uint32 ByteLen);
		//BufLen含CRC
		uint16 AddCrc(void* data, uint32 BufLen);
		//BufLen含CRC
		bool8 IsCrcOk(const void* data, uint32 ByteLen);
	private:
		uint16 table[256];
		uint16 iniValue;
		uint16 xorValue;
		uint16 outxorvalue;
		bool8 rightFirst;
	};

	class Crc32Check
	{
	public:
		Crc32Check(uint32 IniValue, uint32 Xorvalue, uint32 Outxorvalue, bool8 RightFirst);
		uint32 CalCrc(const void* data, uint32 ByteLen);
		uint32 CalCrc(uint32 Crc, const void* data, uint32 ByteLen);
	private:
		uint32 table[256];
		uint32 iniValue;
		uint32 xorValue;
		uint32 outxorvalue;
		bool8 rightFirst;
	};

	class Bit1Num
	{
	public:
		static uint16 Num(uint8 data);
		static uint16 Num(uint16 data);
		static uint16 Num(uint32 data);
	};

	extern Crc16Check Crc16ModBus;
	extern Crc16Check Crc16IBM;
	extern Crc8Check Crc8;
	extern Crc8Check Crc8MAXIM;
	extern Crc32Check StdCrc32Check;//用于CCD的crc校验
	/// <summary>
	/// 计算CRC校验码
	/// </summary>
	/// <param name="data"></param>
	/// <param name="Len">不含CRC</param>
	/// <returns></returns>
	uint8 Crc8MAXIM_CalCrc(const void* data, uint32 Len);
	/// <summary>
	/// 验证CRC校验码
	/// </summary>
	/// <param name="data"></param>
	/// <param name="Len">含CRC</param>
	/// <returns></returns>
	bool8 Crc8MAXIM_IsCrcOk(const void* data, uint32 Len);

}

#endif // !SALCLASICFUNC_H

