#ifndef INSTPARA_H
#define INSTPARA_H

enum E_SoftRelayEn
{
	E_SRE_test1,
	E_SRE_test2,
	E_SRE_Total,
};
enum E_ProtPara
{
	E_PP_Zone,
	E_PP_test1,
	E_PP_test2,
	E_PP_UnitName,
	E_PP_Ct,
	E_PP_Current,
	E_PP_Bit,
	E_PP_Hex,
	E_PP_Total,
};

class AppPara :public ApiPara
{
public:
	void MyPowerUpIni(uint32 Para);
	uint32 myPara;
};

extern AppPara ProtPara[E_PP_Total];
extern ApiParaGroup SoftRelayEnGroup;
extern ApiParaGroup ProtParaGroup;
extern SalParaEditGroup HmiParaEditGroup;
extern AppPara PtctPara[2];
extern ApiParaGroup PtctParaGroup;

void AppParaPowerUpIni();


#endif // !INSTPARA_H

