#include"SptProject.h"
using namespace spt;


SalEnumDes* spt::GetDesByVal(int32 Val, SalEnumDes* Arr, uint32 Total)
{
	for (uint32 i = 0; i < Total; i++)
	{
		if (Arr[i].val == Val)
		{
			return &Arr[i];
		}
	}
	return 0;
}

bool8 spt::toStr(SalString& Str, u64value Value, uint16 Type, bool8 FromRight, uint16 Len, uint8 DotLen, uint8 AddFlag)
{
	String100B str;
	bool8 res = 0;
	E_SalValType Typ = (E_SalValType)Type;
	switch (Typ)
	{
	case spt::E_SVT_NULL:
		break;
	case spt::E_SVT_BOOL:
		Str.Format(Value.bl, Len, DotLen, FromRight != 1, AddFlag);
		res = 1;
		break;
	case spt::E_SVT_DP:
		if (Value.u8 == 0)
		{
			str = "00";
		}
		else if (Value.u8 == 1)
		{
			str = "01";
		}
		else if (Value.u8 == 2)
		{
			str = "10";
		}
		else if (Value.u8 == 3)
		{
			str = "11";
		}
		Str.Format(str.Str(), Len, FromRight != 1, AddFlag);
		res = 1;
		break;
	case spt::E_SVT_U8:
		Str.Format(Value.u8, Len, DotLen, FromRight != 1, AddFlag);
		res = 1;
		break;
	case spt::E_SVT_I8:
		Str.Format(Value.i8, Len, DotLen, FromRight != 1, AddFlag);
		res = 1;
		break;
	case spt::E_SVT_BIT8:
		uint8 end;
		end = sizeof(uint8) * 8;
		for (uint32 i = 0; i < end; i++)
		{
			if (GetBit(Value.u8, end - i - 1))
			{
				str << '1';
			}
			else
			{
				str << '0';
			}
		}
		Str.Format(str.Str(), Len, FromRight != 1, AddFlag);
		res = 1;
		break;
	case spt::E_SVT_8421_4_8:
		str.FormatHex(Value.u8);
		Str.Format(str.Str(), Len, FromRight != 1, AddFlag);
		break;
	case spt::E_SVT_ENUM8:
		break;
	case spt::E_SVT_HEX8:
		str.FormatHex(Value.u8);
		Str.Format(str.Str(), Len, FromRight != 1, AddFlag);
		break;
		break;
	case spt::E_SVT_U16:
		Str.Format(Value.u16, Len, DotLen, FromRight != 1, AddFlag);
		res = 1;
		break;
	case spt::E_SVT_I16:
		Str.Format(Value.i16, Len, DotLen, FromRight != 1, AddFlag);
		res = 1;
		break;
	case spt::E_SVT_BIT16:
		end = sizeof(uint16) * 8;
		for (uint32 i = 0; i < end; i++)
		{
			if (GetBit(Value.u16, end - i - 1))
			{
				str << '1';
			}
			else
			{
				str << '0';
			}
		}
		Str.Format(str.Str(), Len, FromRight != 1, AddFlag);
		res = 1;
		break;
	case spt::E_SVT_8421_4_16:
		str.FormatHex(Value.u16);
		Str.Format(str.Str(), Len, FromRight != 1, AddFlag);
		break;
	case spt::E_SVT_HEX16:
		str.FormatHex(Value.u16);
		Str.Format(str.Str(), Len, FromRight != 1, AddFlag);
		break;
	case spt::E_SVT_ENUM16:
		break;
	case spt::E_SVT_U32:
		Str.Format(Value.u32, Len, DotLen, FromRight != 1, AddFlag);
		res = 1;
		break;
	case spt::E_SVT_I32:
		Str.Format(Value.i32, Len, DotLen, FromRight != 1, AddFlag);
		res = 1;
		break;
	case spt::E_SVT_BIT32:
		end = sizeof(uint32) * 8;
		for (uint32 i = 0; i < end; i++)
		{
			if (GetBit(Value.u32, end - i - 1))
			{
				str << '1';
			}
			else
			{
				str << '0';
			}
		}
		Str.Format(str.Str(), Len, FromRight != 1, AddFlag);
		res = 1;
		break;
		break;
	case spt::E_SVT_8421_4_32:
		str.FormatHex(Value.u32);
		Str.Format(str.Str(), Len, FromRight != 1, AddFlag);
		break;
	case spt::E_SVT_HEX32:
		str.FormatHex(Value.u32);
		Str.Format(str.Str(), Len, FromRight != 1, AddFlag);
		break;
	case spt::E_SVT_ENUM32:
		break;
	case spt::E_SVT_FLOAT32:
		break;
	case spt::E_SVT_U64:
		Str.Format(Value.u64, Len, DotLen, FromRight != 1, AddFlag);
		Str.Format(str.Str(), Len, FromRight != 1, AddFlag);
		break;
	case spt::E_SVT_I64:
		Str.Format(Value.i64, Len, DotLen, FromRight != 1, AddFlag);
		Str.Format(str.Str(), Len, FromRight != 1, AddFlag);
		break;
	case spt::E_SVT_HEX64:
		str.FormatHex(Value.u64);
		Str.Format(str.Str(), Len, FromRight != 1, AddFlag);
		break;
	case spt::E_SVT_FLOAT64:
		break;
	case spt::E_SVT_INSTOBJECT:
		break;
	case spt::E_SVT_I16CPX:

		break;
	case spt::E_SVT_I32CPX:
		break;
	case spt::E_SVT_F32CPX:
		break;
	case spt::E_SVT_I16POSCPX:
		break;
	case spt::E_SVT_I32POSCPX:
		break;
	case spt::E_SVT_F32POSCPX:
		break;
	case spt::E_SVT_STR:
		Str.Format(Value.cstr, Len, FromRight != 1, AddFlag);
		break;
	case spt::E_SVT_ST32VAL:
		break;
	case spt::E_SVT_ST64VAL:
		break;
	case spt::E_SVT_PTR:
		break;
	default:
		break;
	}

	return res;
}

bool8 spt::st64value::toStr(SalString& Str, bool8 FromRight, uint16 Len, uint8 DotLen, uint8 AddFlag)
{
	return spt::toStr(Str, value, valueType, FromRight, Len, DotLen, AddFlag);
}
