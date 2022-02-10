#include "InstResource.h"

AppPara SoftRelayEn[E_SRE_Total];
ApiParaGroup SoftRelayEnGroup;

AppPara ProtPara[E_PP_Total];
ApiParaGroup ProtParaGroup;

AppPara PtctPara[2];
ApiParaGroup PtctParaGroup;

SalParaEditGroup HmiParaEditGroup;
SalBitDes TripDes[16] = {
	{0,"备用"},
	{1,"Bit1"},
	{2,"Bit2"},
	{3,"Bit3"},
	{4,"Bit4"},
	{5,"Bit5"},
	{6,"Bit6"},
	{7,"Bit7"},
	{8,"Bit8"},
	{9,"Bit9"},
	{10,"Bit10"},
	{11,"Bit11"},
	{12,"Bit12"},
	{13,"Bit13"},
	{14,"Bit14"},
	{15,"Bit15"},
};

void AppParaPowerUpIni()
{
	SoftRelayEnGroup.PowerUpIni("保护软压板", "SoftRelayEnGroup", E_PP_Total);
	SoftRelayEn[E_SRE_test1].BlPowerUpIni("测试1", "E_SRE_test1", SoftRelayEnGroup, 0);
	SoftRelayEn[E_SRE_test2].BlPowerUpIni("测试2", "E_SRE_test2", SoftRelayEnGroup, 0);
	ProtPara[E_PP_Zone].ZonePowerUpIni("定值区号", "E_PP_Zone", SoftRelayEnGroup, 1, 1, 16, 0, Unit_NULL);
	ProtPara[E_PP_Zone].MyPowerUpIni(2 * 10);
	SoftRelayEnGroup.UpdateForUse();
	//由于字符型参数占用多个定值位置，因此，含有字符参数参数组的参数数目多于实际数目，每个参数为4个字节，每个字符参数应根据(最大长度/4)+2开辟内存空间
	int32 Zone = ProtPara[E_PP_Zone].Int32();
	if (Zone >= 1 && (Zone < 16))
	{
		ProtParaGroup.PowerUpIni("保护定值", "ProtParaGroup", Zone - 1, 16, E_PP_Total + 10);
	}
	else
	{
		ProtParaGroup.PowerUpIni("保护定值", "ProtParaGroup", 0, 16, E_PP_Total + 10);
	}


	ProtPara[E_PP_test1].PowerUpIni("测试1", "E_PP_test1", ProtParaGroup, -50, 0, 1, 0, Unit_A);
	ProtPara[E_PP_test2].PowerUpIni("测试2", "E_PP_test2", ProtParaGroup, 50, 50, 100, 0, Unit_NULL);
	ProtPara[E_PP_UnitName].StrPowerUpIni("装置名称", "UnitName", ProtParaGroup, "测试设备");
	ProtPara[E_PP_Ct].CTEnumPowerUpIni("CT二次值", "E_PP_Ct", ProtParaGroup, 0);
	ProtPara[E_PP_Current].RelatedCTPowerUpIni("电流值", "E_PP_Current", ProtParaGroup, 50, 12345, 20000, 3, Unit_A, ProtPara[E_PP_Ct]);
	ProtPara[E_PP_Bit].BitOnOffPowerUpIni("跳闸矩阵", "E_PP_Bit", ProtParaGroup, 0, 0xF, 0XFFFF, 2, TripDes);
	ProtPara[E_PP_Hex].HexPowerUpIni("Hex定值", "E_PP_Hex", ProtParaGroup, 0, 0xF, 0XFFFF, 2);
	ProtParaGroup.UpdateForUse();
	HmiParaEditGroup.PowerUpIni(1000);

	PtctParaGroup.PowerUpIni("Ptct参数", "PtctParaGroup", 10);
	PtctPara[0].UInt32PowerUpIni("测试1", "E_PP_test1", PtctParaGroup, 50, 0, 3000000000, 0, Unit_A, 0);
	PtctPara[1].UInt32PowerUpIni("测试1", "E_PP_test1", PtctParaGroup, 50, 0, 3000000000, 0, Unit_A, 1);
	//异常掉电，参数恢复
	if (ProtParaGroup.CheckStatus() != SalParaGroup::E_OK)
	{
		if (ProtParaGroup.GetSaveStepFlag(0) == SalParaGroup::E_SaveStart)
		{
			int32 res = ProtParaGroup.LoadBakParaForUse(0);
			if (res)
			{
				res = ProtParaGroup.CheckStatus();
			}
		}
	}

}

void AppPara::MyPowerUpIni(uint32 Para)
{
	myPara = Para;
}
