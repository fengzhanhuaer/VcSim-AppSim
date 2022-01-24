#include "SptProject.h"
using namespace spt;

const uint8 spt::U8OneBitIsTrue[8] = { 0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80 };
const uint8 spt::U8OneBitIsFalse[8] = { 0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F };
const uint16 spt::U16OneBitIsTrue[16] = { 0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80, 0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000 };
const uint16 spt::U16OneBitIsFalse[16] = { 0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F, 0xFEFF,0xFDFF,0xFBFF,0xF7FF,0xEFFF,0xDFFF,0xBFFF,0x7FFF };
const uint32 spt::U32OneBitIsTrue[32] = { 0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80, 0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000, 0x010000,0x020000,0x040000,0x080000,0x100000,0x200000,0x400000,0x800000, 0x01000000,0x02000000,0x04000000,0x08000000,0x10000000,0x20000000,0x40000000,0x80000000 };
const uint32 spt::U32OneBitIsFalse[32] = { 0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F, 0xFEFF,0xFDFF,0xFBFF,0xF7FF,0xEFFF,0xDFFF,0xBFFF,0x7FFF, 0xFEFFFF,0xFDFFFF,0xFBFFFF,0xF7FFFF,0xEFFFFF,0xDFFFFF,0xBFFFFF,0x7FFFFF, 0xFEFFFFFF,0xFDFFFFFF,0xFBFFFFFF,0xF7FFFFFF,0xEFFFFFFF,0xDFFFFFFF,0xBFFFFFFF,0x7FFFFFFF };

void spt::SetBit(uint8& Data, uint8 Bit, uint8 flag)
{
	if (flag)
	{
		Data |= U8OneBitIsTrue[Bit & 0X7];
	}
	else
	{
		Data &= U8OneBitIsFalse[Bit & 0X7];
	}
}

void spt::SetBit(uint16& Data, uint8 Bit, uint8 flag)
{
	if (flag)
	{
		Data |= U16OneBitIsTrue[Bit & 0XF];
	}
	else
	{
		Data &= U16OneBitIsFalse[Bit & 0XF];
	}
}

void spt::SetBit(uint32& Data, uint8 Bit, uint8 flag)
{
	if (flag)
	{
		Data |= U32OneBitIsTrue[Bit & 0X1F];
	}
	else
	{
		Data &= U32OneBitIsFalse[Bit & 0X1F];
	}
}

bool8 spt::GetBit(const uint8& Data, uint8 Bit)
{
	if (Data & U8OneBitIsTrue[Bit & 0X7])
	{
		return 1;
	}
	return 0;
}

bool8 spt::GetBit(const uint16& Data, uint8 Bit)
{
	if (Data & U16OneBitIsTrue[Bit & 0Xf])
	{
		return 1;
	}
	return 0;
}

bool8 spt::GetBit(const uint32& Data, uint8 Bit)
{
	if (Data & U32OneBitIsTrue[Bit & 0X1f])
	{
		return 1;
	}
	return 0;
}

void spt::EncryptData(void* Sur, uint32 Len, uint8 Key)
{
	uint8* sur = (uint8*)Sur;
	uint8 data;
	while (Len--)
	{
		data = *sur;
		data = BitsInvertUint(data);
		data = data + Key;
		data = ~data;
		*sur++ = data;
	}
}

void spt::DecryptData(void* Sur, uint32 Len, uint8 Key)
{
	uint8* sur = (uint8*)Sur;
	uint8 data;
	while (Len--)
	{
		data = ~*sur;
		data = data - Key;
		data = BitsInvertUint(data);
		*sur++ = data;
	}
}

static const uint8 invertuint8[256] =
{
	0x00,0x80,0x40,0xc0,0x20,0xa0,0x60,0xe0,0x10,0x90,0x50,0xd0,0x30,0xb0,0x70,0xf0,
	0x08,0x88,0x48,0xc8,0x28,0xa8,0x68,0xe8,0x18,0x98,0x58,0xd8,0x38,0xb8,0x78,0xf8,
	0x04,0x84,0x44,0xc4,0x24,0xa4,0x64,0xe4,0x14,0x94,0x54,0xd4,0x34,0xb4,0x74,0xf4,
	0x0c,0x8c,0x4c,0xcc,0x2c,0xac,0x6c,0xec,0x1c,0x9c,0x5c,0xdc,0x3c,0xbc,0x7c,0xfc,
	0x02,0x82,0x42,0xc2,0x22,0xa2,0x62,0xe2,0x12,0x92,0x52,0xd2,0x32,0xb2,0x72,0xf2,
	0x0a,0x8a,0x4a,0xca,0x2a,0xaa,0x6a,0xea,0x1a,0x9a,0x5a,0xda,0x3a,0xba,0x7a,0xfa,
	0x06,0x86,0x46,0xc6,0x26,0xa6,0x66,0xe6,0x16,0x96,0x56,0xd6,0x36,0xb6,0x76,0xf6,
	0x0e,0x8e,0x4e,0xce,0x2e,0xae,0x6e,0xee,0x1e,0x9e,0x5e,0xde,0x3e,0xbe,0x7e,0xfe,
	0x01,0x81,0x41,0xc1,0x21,0xa1,0x61,0xe1,0x11,0x91,0x51,0xd1,0x31,0xb1,0x71,0xf1,
	0x09,0x89,0x49,0xc9,0x29,0xa9,0x69,0xe9,0x19,0x99,0x59,0xd9,0x39,0xb9,0x79,0xf9,
	0x05,0x85,0x45,0xc5,0x25,0xa5,0x65,0xe5,0x15,0x95,0x55,0xd5,0x35,0xb5,0x75,0xf5,
	0x0d,0x8d,0x4d,0xcd,0x2d,0xad,0x6d,0xed,0x1d,0x9d,0x5d,0xdd,0x3d,0xbd,0x7d,0xfd,
	0x03,0x83,0x43,0xc3,0x23,0xa3,0x63,0xe3,0x13,0x93,0x53,0xd3,0x33,0xb3,0x73,0xf3,
	0x0b,0x8b,0x4b,0xcb,0x2b,0xab,0x6b,0xeb,0x1b,0x9b,0x5b,0xdb,0x3b,0xbb,0x7b,0xfb,
	0x07,0x87,0x47,0xc7,0x27,0xa7,0x67,0xe7,0x17,0x97,0x57,0xd7,0x37,0xb7,0x77,0xf7,
	0x0f,0x8f,0x4f,0xcf,0x2f,0xaf,0x6f,0xef,0x1f,0x9f,0x5f,0xdf,0x3f,0xbf,0x7f,0xff,
};

uint8 spt::BitsInvertUint(uint8 data)
{
	return uint8(invertuint8[data]);
}

uint16 spt::BitsInvertUint(uint16 data)
{
	u2bytes sur;
	u2bytes dst;

	sur.u16 = data;

	dst.sbyte.b1 = BitsInvertUint(sur.sbyte.b2);
	dst.sbyte.b2 = BitsInvertUint(sur.sbyte.b1);
	return uint16(dst.u16);
}

uint32 spt::BitsInvertUint(uint32 data)
{
	u4bytes sur;
	u4bytes dst;

	sur.u32 = data;

	dst.sbyte.b1 = BitsInvertUint(sur.sbyte.b4);
	dst.sbyte.b2 = BitsInvertUint(sur.sbyte.b3);
	dst.sbyte.b3 = BitsInvertUint(sur.sbyte.b2);
	dst.sbyte.b4 = BitsInvertUint(sur.sbyte.b1);

	return uint32(dst.u32);
}

uint16 spt::ByteInvertUint(uint16 data)
{
	u2bytes s;
	s.u8[1] = (uint8)(data);
	s.u8[0] = (uint8)(data >> 8);
	return uint16(s.u16);
}

uint32 spt::ByteInvertUint(uint32 data)
{
	u4bytes s;
	s.u8[3] = (uint8)(data);
	s.u8[2] = (uint8)(data >> 8);
	s.u8[1] = (uint8)(data >> 16);
	s.u8[0] = (uint8)(data >> 24);
	return uint16(s.u32);
}
static const uint32 u32decmin[] = { 0,(uint32)1e0,(uint32)1e1,(uint32)1e2,(uint32)1e3,(uint32)1e4,(uint32)1e5,(uint32)1e6,(uint32)1e7,(uint32)1e8,(uint32)1e9 };
uint32 spt::MinUint32DecData(uint8 DecBit)
{
	if (DecBit < M_ArrLen(u32decmin))
	{
		return u32decmin[DecBit];
	}
	return 0;
}
uint16 spt::GetLittleEndian16Bit(void* Sur)
{
	uint16 Dst;
	uint8* dst = (uint8*)&Dst;
	uint8* sur = (uint8*)Sur;
	dst[0] = sur[0];
	dst[1] = sur[1];
	return Dst;
}
uint32 spt::GetLittleEndian32Bit(void* Sur)
{
	uint32 Dst;
	uint8* dst = (uint8*)&Dst;
	uint8* sur = (uint8*)Sur;
	dst[0] = sur[0];
	dst[1] = sur[1];
	dst[2] = sur[2];
	dst[3] = sur[3];
	return Dst;
}
uint16 spt::GetBigEndian16Bit(void* Sur)
{
	uint16 Dst;
	uint8* dst = (uint8*)&Dst;
	uint8* sur = (uint8*)Sur;
	dst[0] = sur[1];
	dst[1] = sur[0];
	return Dst;
}
uint32 spt::GetBigEndian32Bit(void* Sur)
{
	uint32 Dst;
	uint8* dst = (uint8*)&Dst;
	uint8* sur = (uint8*)Sur;
	dst[0] = sur[3];
	dst[1] = sur[2];
	dst[2] = sur[1];
	dst[3] = sur[0];
	return Dst;
}
uint32 spt::ChangeEndian(void* Dst, void* Sur, uint32 Len)
{
	uint8* dst = (uint8*)Dst;
	uint8* sur = (uint8*)Sur + Len - 1;
	if (Dst == Sur)
	{
		uint8 data;
		Len = Len / 2;
		for (uint32 i = 0; i < Len; i++)
		{
			data = *dst;
			*dst++ = *sur;
			*sur-- = data;
		}
	}
	else
	{
		for (uint32 i = 0; i < Len; i++)
		{
			*dst++ = *sur--;
		}
	}
	return Len;
}
static const float32 i322f32coe[] = { (float32)1.0e0,(float32)1.0e-1,(float32)1.0e-2,(float32)1.0e-3,(float32)1.0e-4,(float32)1.0e-5,(float32)1.0e-6,(float32)1.0e-7,(float32)1.0e-8,(float32)1.0e-9,(float32)1.0e-10,(float32)1.0e-11,(float32)1.0e-12,(float32)1.0e-13,(float32)1.0e-14,(float32)1.0e-15,(float32)1.0e-16 };
float32 spt::Int32FixDot2Float32(int32 data, uint8 Dot)
{
	return data * i322f32coe[Dot & 0X0F];
}

uint32 spt::Bcd4BitToDec(uint8 BcdCode)
{
	uint32 dec = (BcdCode & 0x0f) + ((BcdCode >> 4) * 10);
	return dec;
}



template<typename T1, typename T2>
T1 CalSum(T2* data, uint32 Len)
{
	T1 sum = 0;
	Len = Len / sizeof(T2);
	while (Len--)
	{
		sum += *data++;
	}
	return sum;
}

uint8 spt::SumCheck::CalcSum8(uint8* data, uint32 Len)
{
	return CalSum<uint8, uint8>(data, Len);
}

uint16 spt::SumCheck::CalcSum16(uint8* data, uint32 Len)
{
	return CalSum<uint16, uint8>(data, Len);
}
uint16 spt::SumCheck::CalcSum16(uint16* data, uint32 Len)
{
	return CalSum<uint16, uint16>(data, Len);
}

uint32 spt::SumCheck::CalcSum32(uint8* data, uint32 Len)
{
	return CalSum<uint32, uint8>(data, Len);
}
uint32 spt::SumCheck::CalcSum32(uint16* data, uint32 Len)
{
	return CalSum<uint32, uint16>(data, Len);
}
uint32 spt::SumCheck::CalcSum32(uint32* data, uint32 Len)
{
	return CalSum<uint32, uint32>(data, Len);
}

template<typename T1, typename T2>
bool8 IsOkCalSum(T2* data, uint32 Len)
{
	T1 sum = CalSum<T1, T2>(data, Len - sizeof(T1));
	T1* psum = (T1*)((char*)(data)+Len - sizeof(*psum));
	return sum == *psum;
}

bool8 spt::SumCheck::IsOkCalcSum8(uint8* data, uint32 Len)
{
	return IsOkCalSum<uint8, uint8>(data, Len);
}

bool8 spt::SumCheck::IsOkCalcSum16(uint8* data, uint32 Len)
{
	return IsOkCalSum<uint16, uint8>(data, Len);
}

bool8 spt::SumCheck::IsOkCalcSum16(uint16* data, uint32 Len)
{
	return IsOkCalSum<uint16, uint16>(data, Len);
}

bool8 spt::SumCheck::IsOkCalcSum32(uint8* data, uint32 Len)
{
	return IsOkCalSum<uint32, uint8>(data, Len);
}

bool8 spt::SumCheck::IsOkCalcSum32(uint16* data, uint32 Len)
{
	return IsOkCalSum<uint32, uint16>(data, Len);
}

bool8 spt::SumCheck::IsOkCalcSum32(uint32* data, uint32 Len)
{
	return IsOkCalSum<uint32, uint32>(data, Len);
}
static uint16 Crc8005_16Table[256] =
{ 0, 49345, 49537, 320, 49921, 960, 640, 49729, 50689, 1728, 1920, 51009, 1280, 50625, 50305, 1088,
52225, 3264, 3456, 52545, 3840, 53185, 52865, 3648, 2560, 51905, 52097, 2880, 51457, 2496, 2176, 51265,
55297, 6336, 6528, 55617, 6912, 56257, 55937, 6720, 7680, 57025, 57217, 8000, 56577, 7616, 7296, 56385,
5120, 54465, 54657, 5440, 55041, 6080, 5760, 54849, 53761, 4800, 4992, 54081, 4352, 53697, 53377, 4160,
61441, 12480, 12672, 61761, 13056, 62401, 62081, 12864, 13824, 63169, 63361, 14144, 62721, 13760, 13440, 62529,
15360, 64705, 64897, 15680, 65281, 16320, 16000, 65089, 64001, 15040, 15232, 64321, 14592, 63937, 63617, 14400,
10240, 59585, 59777, 10560, 60161, 11200, 10880, 59969, 60929, 11968, 12160, 61249, 11520, 60865, 60545, 11328,
58369, 9408, 9600, 58689, 9984, 59329, 59009, 9792, 8704, 58049, 58241, 9024, 57601, 8640, 8320, 57409,
40961, 24768, 24960, 41281, 25344, 41921, 41601, 25152, 26112, 42689, 42881, 26432, 42241, 26048, 25728, 42049,
27648, 44225, 44417, 27968, 44801, 28608, 28288, 44609, 43521, 27328, 27520, 43841, 26880, 43457, 43137, 26688,
30720, 47297, 47489, 31040, 47873, 31680, 31360, 47681, 48641, 32448, 32640, 48961, 32000, 48577, 48257, 31808,
46081, 29888, 30080, 46401, 30464, 47041, 46721, 30272, 29184, 45761, 45953, 29504, 45313, 29120, 28800, 45121,
20480, 37057, 37249, 20800, 37633, 21440, 21120, 37441, 38401, 22208, 22400, 38721, 21760, 38337, 38017, 21568,
39937, 23744, 23936, 40257, 24320, 40897, 40577, 24128, 23040, 39617, 39809, 23360, 39169, 22976, 22656, 38977,
34817, 18624, 18816, 35137, 19200, 35777, 35457, 19008, 19968, 36545, 36737, 20288, 36097, 19904, 19584, 35905,
17408, 33985, 34177, 17728, 34561, 18368, 18048, 34369, 33281, 17088, 17280, 33601, 16640, 33217, 32897, 16448,
};
Crc16Check spt::Crc16ModBus(&Crc8005_16Table, 0xffff, 0x8005, 0x0000, 1);
Crc16Check spt::Crc16IBM(&Crc8005_16Table, 0x0000, 0x8005, 0x0000, 1);

spt::Crc16Check::Crc16Check(uint16 IniValue, uint16 Xorvalue, uint16 Outxorvalue, bool8 RightFirst)
{
	iniValue = IniValue;
	xorValue = Xorvalue;
	outxorvalue = Outxorvalue;

	uint16 j, crc_16 = 0;
	uint16 i;
	rightFirst = 0;
	uint16 key = Xorvalue;

	//DbgReal << "mkCrc16Table key is " << key << endl;

	if (RightFirst == 1)
	{
		rightFirst = RightFirst;
		key = BitsInvertUint(key);
	}

	//DbgReal << "{";
	for (i = 0; i < 256; i++)
	{
		if ((i & 0x0f) == 0)
		{
			;//	DbgReal << "\n";
		}

		crc_16 = (uint8)i;
		if (rightFirst)
		{
			for (j = 8; j > 0; j--)
			{
				if (crc_16 & 0x0001)
				{
					crc_16 = (crc_16 >> 1) ^ key;
				}
				else
				{
					crc_16 = (crc_16 >> 1);
				}
			}
		}
		else
		{
			crc_16 <<= 8;
			for (j = 8; j > 0; j--)
			{
				if (crc_16 & 0x8000)
				{
					crc_16 = (crc_16 << 1) ^ key;
				}
				else
				{
					crc_16 = (crc_16 << 1);
				}
			}
		}
		table[i] = crc_16;
		//DbgReal << crc_16 << ",";
	}
	//DbgReal << "\n};\n";
}

spt::Crc16Check::Crc16Check(uint16(*table)[256], uint16 IniValue, uint16 Xorvalue, uint16 Outxorvalue, bool8 RightFirst)
{
	iniValue = IniValue;
	xorValue = Xorvalue;
	outxorvalue = Outxorvalue;
	rightFirst = RightFirst;
	for (uint32 i = 0; i < M_ArrLen(this->table); i++)
	{
		this->table[i] = (*table)[i];
	}
}


uint16 spt::Crc16Check::CalCrc(const void* data, uint32 Len)
{
	uint16 crc;
	if (data == 0)
	{
		return 0;
	}
	crc = iniValue;
	const uint8* sur = (const uint8*)data;
	while (Len--)
	{
		crc = table[((crc) ^ *sur++) & 0xff] ^ (crc >> 8);
	}
	return crc ^ outxorvalue;
}

uint16 spt::Crc16Check::CalCrc(uint16 Crc, const void* data, uint32 Len)
{
	uint16 crc;
	if (data == 0)
	{
		return 0;
	}
	crc = Crc ^ outxorvalue;
	const uint8* sur = (const uint8*)data;
	while (Len--)
	{
		crc = table[((crc) ^ *sur++) & 0xff] ^ (crc >> 8);
	}
	return crc ^ outxorvalue;
}

uint16 spt::Crc16Check::AddCrc(void* data, uint32 BufLen)
{
	uint8* buf = (uint8*)data;
	if (BufLen <= 2)
	{
		while (BufLen--)
		{
			*buf++ = 0;
		}
		return 0;
	}
	uint16 crc = CalCrc(data, BufLen - 2);
	buf[BufLen - 2] = (uint8)crc;
	buf[BufLen - 1] = (uint8)(crc >> 8);
	return crc;
}

bool8 spt::Crc16Check::IsCrcOk(const void* data, uint32 Len)
{
	return CalCrc(data, Len) == 0;
}

Crc8Check spt::Crc8(0x00, 0x07, 0x00, 0);
Crc8Check spt::Crc8MAXIM(0x00, 0x31, 0x00, 1);

spt::Crc8Check::Crc8Check(uint8 IniValue, uint8 Xorvalue, uint8 Outxorvalue, bool8 RightFirst)
{
	uint8 j, crc_8;
	uint16 i;

	iniValue = IniValue;
	xorValue = Xorvalue;
	outxorvalue = Outxorvalue;
	rightFirst = RightFirst;

	//LogReal << "mkCrc8Table key is " << "\n";
	//LogReal << "{";
	uint8 key = Xorvalue;

	if (RightFirst)
	{
		key = BitsInvertUint(key);
	}


	for (i = 0; i < 256; i++)
	{
		if ((i & 0x0f) == 0)
		{
			//	LogReal << "\n";
		}
		crc_8 = (uint8)i;
		if (rightFirst)
		{
			for (j = 8; j > 0; j--)
			{
				if (crc_8 & 0x01)
				{
					crc_8 = (crc_8 >> 1) ^ key;
				}
				else
				{
					crc_8 = (crc_8 >> 1);
				}
			}
		}
		else
		{
			for (j = 8; j > 0; j--)
			{
				if (crc_8 & 0x80)
				{
					crc_8 = (crc_8 << 1) ^ key;
				}
				else
				{
					crc_8 = (crc_8 << 1);
				}
			}
		}
		//	LogReal << crc_8 << ",";
		table[i] = crc_8;
	}
	//LogReal << "\n};\n";
}

uint8 spt::Crc8Check::CalCrc(const void* data, uint32 Len)
{
	uint8 crc;
	if (data == 0)
	{
		return 0;
	}
	crc = iniValue;
	uint8* sur = (uint8*)data;
	while (Len--)
	{
		crc = table[crc ^ *sur++];
	}
	return crc ^ outxorvalue;
}

bool8 spt::Crc8Check::IsCrcOk(const void* data, uint32 Len)
{
	return CalCrc(data, Len) == 0;
}

static uint8 bit1Num[256] =
{
0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,
1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
};

uint16 spt::Bit1Num::Num(uint8 data)
{
	/*
	int cnt = 0;
	for (size_t i = 0; i < 256; i++)
	{
		if (!(i % 16))
		{
			DbgApp << "\n";
		}
		cnt = 0;
		for (size_t j = 0; j < 8; j++)
		{
			if (i & (1 << j))
			{
				cnt++;
			}
		}
		DbgApp << cnt << ",";

	}*/
	return uint16(bit1Num[data]);
}

uint16 spt::Bit1Num::Num(uint16 data)
{
	uint16 num = 0;
	u2bytes u;
	u.u16 = data;
	num = bit1Num[u.u8[0]];
	num += bit1Num[u.u8[1]];
	return num;
}

uint16 spt::Bit1Num::Num(uint32 data)
{
	uint16 num = 0;
	u4bytes u;
	u.u32 = data;
	num = bit1Num[u.u8[0]];
	num += bit1Num[u.u8[1]];
	num += bit1Num[u.u8[2]];
	num += bit1Num[u.u8[3]];
	return num;
}

const uint8 Crc8CheckTable[256] =
{
	0, 94, 188, 226, 97, 63, 221, 131, 194, 156, 126, 32, 163, 253, 31, 65,
	157, 195, 33, 127, 252, 162, 64, 30, 95, 1, 227, 189, 62, 96, 130, 220,
	35, 125, 159, 193, 66, 28, 254, 160, 225, 191, 93, 3, 128, 222, 60, 98,
	190, 224, 2, 92, 223, 129, 99, 61, 124, 34, 192, 158, 29, 67, 161, 255,
	70, 24, 250, 164, 39, 121, 155, 197, 132, 218, 56, 102, 229, 187, 89, 7,
	219, 133, 103, 57, 186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154,
	101, 59, 217, 135, 4, 90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36,
	248, 166, 68, 26, 153, 199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185,
	140, 210, 48, 110, 237, 179, 81, 15, 78, 16, 242, 172, 47, 113, 147, 205,
	17, 79, 173, 243, 112, 46, 204, 146, 211, 141, 111, 49, 178, 236, 14, 80,
	175, 241, 19, 77, 206, 144, 114, 44, 109, 51, 209, 143, 12, 82, 176, 238,
	50, 108, 142, 208, 83, 13, 239, 177, 240, 174, 76, 18, 145, 207, 45, 115,
	202, 148, 118, 40, 171, 245, 23, 73, 8, 86, 180, 234, 105, 55, 213, 139,
	87, 9, 235, 181, 54, 104, 138, 212, 149, 203, 41, 119, 244, 170, 72, 22,
	233, 183, 85, 11, 136, 214, 52, 106, 43, 117, 151, 201, 74, 20, 246, 168,
	116, 42, 200, 150, 21, 75, 169, 247, 182, 232, 10, 84, 215, 137, 107, 53,
};

uint8 spt::Crc8MAXIM_CalCrc(const void* data, uint32 Len)
{
	uint8 crc;
	if (data == 0)
	{
		return 0;
	}
	crc = 0;
	uint8* sur = (uint8*)data;
	while (Len--)
	{
		crc = Crc8CheckTable[crc ^ *sur++];
	}
	return crc ^ 0x00;
}

bool8 spt::Crc8MAXIM_IsCrcOk(const void* data, uint32 Len)
{
	return Crc8MAXIM_CalCrc(data, Len) == 0;
}

spt::Crc32Check::Crc32Check(uint32 IniValue, uint32 Xorvalue, uint32 Outxorvalue, bool8 RightFirst)
{
	uint32 j, crc_32;
	uint16 i;

	iniValue = IniValue;
	xorValue = Xorvalue;
	outxorvalue = Outxorvalue;
	rightFirst = RightFirst;

	//LogReal << "mkCrc8Table key is " << "\n";
	//LogReal << "{";
	uint32 key = Xorvalue;

	if (RightFirst)
	{
		key = BitsInvertUint(key);
	}


	for (i = 0; i < 256; i++)
	{
		if ((i & 0x0f) == 0)
		{
			//	LogReal << "\n";
		}
		crc_32 = (uint8)i;
		if (rightFirst)
		{
			for (j = 8; j > 0; j--)
			{
				if (crc_32 & 0x00000001)
				{
					crc_32 = (crc_32 >> 1) ^ key;
				}
				else
				{
					crc_32 = (crc_32 >> 1);
				}
			}
		}
		else
		{
			for (j = 8; j > 0; j--)
			{
				if (crc_32 & 0x80000000)
				{
					crc_32 = (crc_32 << 1) ^ key;
				}
				else
				{
					crc_32 = (crc_32 << 1);
				}
			}
		}
		//	LogReal << crc_8 << ",";
		table[i] = crc_32;
	}
	//LogReal << "\n};\n";

}

uint32 spt::Crc32Check::CalCrc(const void* data, uint32 ByteLen)
{
	uint32 crc;
	if (data == 0)
	{
		return 0;
	}
	crc = iniValue;
	const uint8* sur = (const uint8*)data;
	while (ByteLen--)
	{
		crc = table[((crc) ^ *sur++) & 0xff] ^ (crc >> 8);
	}
	return crc ^ outxorvalue;
}

uint32 spt::Crc32Check::CalCrc(uint32 Crc, const void* data, uint32 ByteLen)
{
	uint32 crc;
	if (data == 0)
	{
		return 0;
	}
	crc = Crc ^ outxorvalue;
	const uint8* sur = (const uint8*)data;
	while (ByteLen--)
	{
		crc = table[((crc) ^ *sur++) & 0xff] ^ (crc >> 8);
	}
	return crc ^ outxorvalue;
}
Crc32Check spt::StdCrc32Check(0xFFFFFFFF, 0x04C11DB7, 0xFFFFFFFF, 1);