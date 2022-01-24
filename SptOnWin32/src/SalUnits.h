#ifndef SALUNITS_H

namespace spt
{
	typedef enum
	{
		E_NULL,//""
		E_A,//"A"
		E_KA,//"kA"
		E_mA,//"mA"
		E_V,//"V"
		E_KV,//"kV"
		E_mV,//"mV"
		E_W,//W
		E_KW,//kW
		E_MW,//MW
		E_mW,//mW
		E_ANGLE,//°
		E_TEMPR,//℃
		E_VAR,//VAR
		E_KVAR,//KVAR
		E_KWH,//kW*h
		E_OUM,//欧姆
		E_HZ,//Hz
		E_F,//F
		E_Sec,//秒
		E_mSec,//毫秒
		E_uSec,//微秒
		E_minute,//分钟
		E_Hour,//小时
		E_Day,//小时
		E_Percent,//%
		E_dB,//分贝
	}E_UNITS_TYPE;

	class VarUnits
	{
	public:
		static const VarUnits& GetUnitsByType(uint32 type);
		VarUnits(const char* Units, uint32 Type);
		const char* toString()const;
		uint32 Type()const;
	protected:
		uint8 type;
		char unit[7];
	};

	extern const VarUnits Unit_NULL;//空
	extern const VarUnits Unit_A;//电流A
	extern const VarUnits Unit_KA;//电流kA
	extern const VarUnits Unit_mA;//电流mA
	extern const VarUnits Unit_V;//电压V
	extern const VarUnits Unit_KV;//电压kV
	extern const VarUnits Unit_mV;//电压mV
	extern const VarUnits Unit_W;//功率W
	extern const VarUnits Unit_KW;//功率kW
	extern const VarUnits Unit_MW;//功率MW
	extern const VarUnits Unit_mW;//功率mW
	extern const VarUnits Unit_ANGLE;//角度
	extern const VarUnits Unit_TEMPR;//温度
	extern const VarUnits Unit_VAR;//无功功率Var
	extern const VarUnits Unit_KVAR;//无功功率kVar
	extern const VarUnits Unit_KWH;//电度量kW*h
	extern const VarUnits Unit_OUM;//欧姆
	extern const VarUnits Unit_F;//电容F
	extern const VarUnits Unit_HZ;//赫兹
	extern const VarUnits Unit_S;//秒
	extern const VarUnits Unit_mS;//m秒
	extern const VarUnits Unit_uS;//u秒
	extern const VarUnits Unit_Minute;//分钟
	extern const VarUnits Unit_Hour;//小时
	extern const VarUnits Unit_Day;//天
	extern const VarUnits Unit_Percent;//百分比
	extern const VarUnits Unit_dB;//分贝
}

#endif // !SALUNITS_H
