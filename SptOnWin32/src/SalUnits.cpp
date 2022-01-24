#include "SptProject.h"
using namespace spt;

namespace spt
{
	const VarUnits Unit_NULL("", E_NULL);
	const VarUnits Unit_A("A", E_A);
	const VarUnits Unit_KA("kA", E_KA);
	const VarUnits Unit_mA("mA", E_mA);
	const VarUnits Unit_V("V", E_V);
	const VarUnits Unit_KV("kV", E_KV);
	const VarUnits Unit_mV("mV", E_mV);
	const VarUnits Unit_W("W", E_W);
	const VarUnits Unit_KW("kW", E_KW);
	const VarUnits Unit_MW("MW", E_MW);
	const VarUnits Unit_mW("mW", E_mW);
	const VarUnits Unit_ANGLE("¡ã", E_ANGLE);
	const VarUnits Unit_TEMPR("¡æ", E_TEMPR);
	const VarUnits Unit_VAR("Var", E_VAR);
	const VarUnits Unit_KVAR("kVar", E_KVAR);
	const VarUnits Unit_KWH("kW¡¤h", E_KWH);
	const VarUnits Unit_OUM("¦¸", E_OUM);
	const VarUnits Unit_F("F", E_F);
	const VarUnits Unit_HZ("Hz", E_HZ);
	const VarUnits Unit_S("s", E_Sec);
	const VarUnits Unit_mS("ms", E_mSec);
	const VarUnits Unit_uS("us", E_uSec);
	const VarUnits Unit_Minute("min", E_minute);
	const VarUnits Unit_Hour("h", E_Hour);
	const VarUnits Unit_Day("Day", E_Day);
	const VarUnits Unit_Percent("%", E_Percent);
	const VarUnits Unit_dB("dB", E_dB);
}



const VarUnits& spt::VarUnits::GetUnitsByType(uint32 type)
{
	E_UNITS_TYPE t = (E_UNITS_TYPE)type;
	switch (t)
	{
	case E_NULL:
	{
		return Unit_NULL;
	}
	case E_A:
	{
		return Unit_A;
	}
	case E_KA:
	{
		return Unit_KA;
	}
	case E_mA:
	{
		return Unit_mA;
	}
	case E_V:
	{
		return Unit_V;
	}
	case E_KV:
	{
		return Unit_KV;
	}
	case E_mV:
	{
		return Unit_mV;
	}
	case E_W:
	{
		return Unit_W;
	}
	case E_KW:
	{
		return Unit_KW;
	}
	case E_MW:
	{
		return Unit_MW;
	}
	case E_mW:
	{
		return Unit_mW;
	}
	case E_ANGLE:
	{
		return Unit_ANGLE;
	}
	case E_TEMPR:
	{
		return Unit_TEMPR;
	}
	case E_VAR:
	{
		return Unit_VAR;
	}
	case E_KVAR:
	{
		return Unit_KVAR;
	}
	case E_KWH:
	{
		return Unit_KWH;
	}
	case E_OUM:
	{
		return Unit_OUM;
	}
	case E_F:
	{
		return Unit_F;
	}
	case E_HZ:
	{
		return Unit_HZ;
	}
	case E_Sec:
	{
		return Unit_S;
	}
	case E_mSec:
	{
		return Unit_mS;
	}
	case E_uSec:
	{
		return Unit_uS;
	}
	case E_minute:
	{
		return Unit_Minute;
	}
	case E_Hour:
	{
		return Unit_Hour;
	}
	case E_Day:
	{
		return Unit_Day;
	}
	case E_Percent:
	{
		return Unit_Percent;
	}
	case E_dB:
	{
		return Unit_dB;
	}
	default:
		break;
	}
	return Unit_NULL;
}

spt::VarUnits::VarUnits(const char* Units, uint32 Type)
{
	StrNCpy(unit, Units, sizeof(unit));
	type = Type;
}

const char* spt::VarUnits::toString()const
{
	return unit;
}

uint32 spt::VarUnits::Type()const
{
	return uint32(type);
}

