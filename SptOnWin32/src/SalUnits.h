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
		E_ANGLE,//��
		E_TEMPR,//��
		E_VAR,//VAR
		E_KVAR,//KVAR
		E_KWH,//kW*h
		E_OUM,//ŷķ
		E_HZ,//Hz
		E_F,//F
		E_Sec,//��
		E_mSec,//����
		E_uSec,//΢��
		E_minute,//����
		E_Hour,//Сʱ
		E_Day,//Сʱ
		E_Percent,//%
		E_dB,//�ֱ�
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

	extern const VarUnits Unit_NULL;//��
	extern const VarUnits Unit_A;//����A
	extern const VarUnits Unit_KA;//����kA
	extern const VarUnits Unit_mA;//����mA
	extern const VarUnits Unit_V;//��ѹV
	extern const VarUnits Unit_KV;//��ѹkV
	extern const VarUnits Unit_mV;//��ѹmV
	extern const VarUnits Unit_W;//����W
	extern const VarUnits Unit_KW;//����kW
	extern const VarUnits Unit_MW;//����MW
	extern const VarUnits Unit_mW;//����mW
	extern const VarUnits Unit_ANGLE;//�Ƕ�
	extern const VarUnits Unit_TEMPR;//�¶�
	extern const VarUnits Unit_VAR;//�޹�����Var
	extern const VarUnits Unit_KVAR;//�޹�����kVar
	extern const VarUnits Unit_KWH;//�����kW*h
	extern const VarUnits Unit_OUM;//ŷķ
	extern const VarUnits Unit_F;//����F
	extern const VarUnits Unit_HZ;//����
	extern const VarUnits Unit_S;//��
	extern const VarUnits Unit_mS;//m��
	extern const VarUnits Unit_uS;//u��
	extern const VarUnits Unit_Minute;//����
	extern const VarUnits Unit_Hour;//Сʱ
	extern const VarUnits Unit_Day;//��
	extern const VarUnits Unit_Percent;//�ٷֱ�
	extern const VarUnits Unit_dB;//�ֱ�
}

#endif // !SALUNITS_H
