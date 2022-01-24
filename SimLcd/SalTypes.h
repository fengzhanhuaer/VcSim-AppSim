#ifndef SPTBASICTYPES_H
#define SPTBASICTYPES_H

namespace spt
{
	typedef signed char int8;
	typedef signed short int16;
	/// <summary>
	/// 有符号32位整型
	/// </summary>
	typedef signed int int32;
	typedef signed long long int int64;
	typedef unsigned char uint8;
	typedef unsigned short uint16;
	typedef unsigned int uint32;
	typedef unsigned long long int uint64;
	typedef unsigned char bool8;
	typedef unsigned short bool16;
	typedef unsigned int bool32;
	typedef float float32;
	typedef double float64;
	typedef void* handle;
	typedef void* pvoid;
	//16位整数复数
	typedef struct
	{
		int16 real;
		int16 img;
	}i16complex;
	//32位整数复数
	typedef struct
	{
		int32 real;
		int32 img;
	}i32complex;
	//32位浮点复数
	typedef struct
	{
		float32 real;
		float32 img;
	}f32complex;
	//16位整数幅角
	typedef struct
	{
		int16 amp;
		int16 angle;
	}i16poscpx;
	//32位整数幅角
	typedef struct
	{
		int32 amp;
		int32 angle;
	}i32poscpx;
	//32位浮点幅角
	typedef struct
	{
		float32 amp;
		float32 angle;
	}f32poscpx;
	enum E_SalValType
	{
		E_SVT_NULL,
		E_SVT_BOOL,//布尔型
		E_SVT_DP,//双点数据,8bit
		E_SVT_U8,
		E_SVT_I8,
		E_SVT_BIT8,//bit型
		E_SVT_8421_4_8,//8421码_4Bit一个码
		E_SVT_ENUM8,//枚举型
		E_SVT_HEX8,
		E_SVT_U16,
		E_SVT_I16,
		E_SVT_BIT16,//bit型
		E_SVT_8421_4_16,//8421码_4Bit一个码
		E_SVT_HEX16,
		E_SVT_ENUM16,//枚举型
		E_SVT_U32,
		E_SVT_I32,
		E_SVT_BIT32,//bit型
		E_SVT_8421_4_32,//8421码_4Bit一个码
		E_SVT_HEX32,
		E_SVT_ENUM32,//枚举型
		E_SVT_FLOAT32,
		E_SVT_U64,
		E_SVT_I64,
		E_SVT_HEX64,
		E_SVT_FLOAT64,
		E_SVT_INSTOBJECT,//实例数据
		E_SVT_I16CPX,//整数，复数
		E_SVT_I32CPX,//整数，复数
		E_SVT_F32CPX,//浮点，复数
		E_SVT_I16POSCPX,//整数，幅角
		E_SVT_I32POSCPX,//整数，幅角
		E_SVT_F32POSCPX,//浮点，幅角
		E_SVT_STR,
		E_SVT_ST32VAL, //st32value
		E_SVT_ST64VAL, //st64value
		E_SVT_ENUMDES,//枚举描述数据
		E_SVT_BITDES,//枚举描述数据
		E_SVT_PTR = 0x80,//第8位如果为1，则表示对应的数据为指针类型，低7位的值上述定义
	};
	union u16value
	{
		bool8 bl;
		uint8 u8;
		int8 i8;
		uint16 u16;
		int16 i16;
	};
	struct st16value
	{
		uint8 valueType;
		u16value value;
	};
	union u2bytes
	{
		uint8 u8[2];
		int8 i8[2];
		uint16 u16;
		int16 i16;
		struct
		{
			uint8 b1;
			uint8 b2;
		}sbyte;
		u16value value;
	};
	union u32value
	{
		bool8 bl;
		uint8 u8;
		int8 i8;
		uint16 u16;
		int16 i16;
		uint32 u32;
		int32 i32;
		float32 f32;
		i16complex i16cpx;
		i16poscpx i16posc;
		union
		{
			u2bytes u2b[2];
			uint8 u8[4];
			int8 i8[4];
			uint16 u16[2];
			int16 i16[2];
			uint32 u32;
			int32 i32;
			struct
			{
				uint8 b1;
				uint8 b2;
				uint8 b3;
				uint8 b4;
			}sbyte;
		}u4bytes;
		void* vptr;
		bool8* pbl;
		uint8* pu8;
		int8* pi8;
		uint16* pu16;
		int16* pi16;
		uint32* pu32;
		int32* pi32;
		float32* pf32;
		char* str;
		const char* cstr;
	};
	struct st32value
	{
		uint8 valueType;
		uint8 valueInfo1;
		uint8 valueInfo2;
		uint8 valueInfo3;
		u32value value;
	};
	union u4bytes
	{
		u2bytes u2b[2];
		uint8 u8[4];
		int8 i8[4];
		uint16 u16[2];
		int16 i16[2];
		uint32 u32;
		int32 i32;
		struct
		{
			uint8 b1;
			uint8 b2;
			uint8 b3;
			uint8 b4;
		}sbyte;
		u32value value;
	};
	struct SalEnumDes
	{
		int32 val;
		const char* des;
	};
	/// <summary>
	/// bit型数据描述
	/// Bit值从零开始，必须是连续的数值，不能跳跃，必须是8的倍数
	/// </summary>
	struct SalBitDes
	{
		int32 Bit;
		const char* des;
	};
	SalEnumDes* GetDesByVal(int32 Val, SalEnumDes* Arr, uint32 Total);
	union u64value
	{
		bool8 bl;
		uint8 u8;
		int8 i8;
		uint16 u16;
		int16 i16;
		uint32 u32;
		int32 i32;
		uint64 u64;
		int64 i64;
		i16complex i16cpx;
		i32complex i32cpx;
		f32complex f32cpx;
		i16poscpx i16posc;
		i32poscpx i32posc;
		f32poscpx f32posc;
		union u8bytes
		{
			u4bytes u4b[2];
			uint8 u8[8];
			int8 i8[8];
			uint16 u16[4];
			int16 i16[4];
			uint32 u32[2];
			int32 i32[2];
			uint64 u64;
			int64 i64;
			struct
			{
				uint8 b1;
				uint8 b2;
				uint8 b3;
				uint8 b4;
				uint8 b5;
				uint8 b6;
				uint8 b7;
				uint8 b8;
			}sbyte;
		}u8bytes;
		struct
		{
			union
			{
				void* ptr;
				uint32 u32;
				uint32* pu32;
				uint16 u16;
				uint16* pu16;
				uint8 u8;
				uint8* pu8;
			}value;
			SalEnumDes* des;
		}Enum;
		struct
		{
			union
			{
				void* ptr;
				uint32 u32;
				uint32* pu32;
				uint16 u16;
				uint16* pu16;
				uint8 u8;
				uint8* pu8;
			}value;
			SalBitDes* des;
		}BitDes;
		void* vptr;
		bool8* pbl;
		uint8* pu8;
		int8* pi8;
		uint16* pu16;
		int16* pi16;
		uint32* pu32;
		int32* pi32;
		uint64* pu64;
		int64* pi64;
		float32* pf32;
		char* str;
		const char* cstr;
		float32 f32;
		float64 f64;
		st32value st32Val;
		st32value* pst32Val;
	};
	struct st64value
	{
		uint8 valueType;
		uint8 valueInfo1;
		uint8 valueInfo2;
		uint8 valueInfo3;
		uint16 valueInfo4;
		uint16 valueInfo5;
		u64value value;
		bool8 toStr(class SalString& Str, bool8 FromRight, uint16 Len, uint8 DotLen, uint8 AddFlag);
	};
	bool8 toStr(class SalString& Str, u64value Value, uint16 Type, bool8 FromRight, uint16 Len, uint8 DotLen, uint8 AddFlag);
	union u8bytes
	{
		u4bytes u4b[2];
		uint8 u8[8];
		int8 i8[8];
		uint16 u16[4];
		int16 i16[4];
		uint32 u32[2];
		int32 i32[2];
		uint64 u64;
		int64 i64;
		struct
		{
			uint8 b1;
			uint8 b2;
			uint8 b3;
			uint8 b4;
			uint8 b5;
			uint8 b6;
			uint8 b7;
			uint8 b8;
		}sbyte;
		u64value value;
	};




}


#endif // !SPTBASICTYPES_H
