#include "InstResource.h"

AppPara SoftRelayEn[E_SRE_Total];
ApiParaGroup SoftRelayEnGroup;

AppPara ProtPara[E_PP_Total];
ApiParaGroup ProtParaGroup;

AppPara PtctPara[2];
ApiParaGroup PtctParaGroup;

SalParaEditGroup HmiParaEditGroup;
SalBitDes TripDes[16] = {
	{0,"����"},
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
	SoftRelayEnGroup.PowerUpIni("������ѹ��", "SoftRelayEnGroup", E_PP_Total);
	SoftRelayEn[E_SRE_test1].BlPowerUpIni("����1", "E_SRE_test1", SoftRelayEnGroup, 0);
	SoftRelayEn[E_SRE_test2].BlPowerUpIni("����2", "E_SRE_test2", SoftRelayEnGroup, 0);
	ProtPara[E_PP_Zone].ZonePowerUpIni("��ֵ����", "E_PP_Zone", SoftRelayEnGroup, 1, 1, 16, 0, Unit_NULL);
	ProtPara[E_PP_Zone].MyPowerUpIni(2 * 10);
	SoftRelayEnGroup.UpdateForUse();
	//�����ַ��Ͳ���ռ�ö����ֵλ�ã���ˣ������ַ�����������Ĳ�����Ŀ����ʵ����Ŀ��ÿ������Ϊ4���ֽڣ�ÿ���ַ�����Ӧ����(��󳤶�/4)+2�����ڴ�ռ�
	int32 Zone = ProtPara[E_PP_Zone].Int32();
	if (Zone >= 1 && (Zone < 16))
	{
		ProtParaGroup.PowerUpIni("������ֵ", "ProtParaGroup", Zone - 1, 16, E_PP_Total + 10);
	}
	else
	{
		ProtParaGroup.PowerUpIni("������ֵ", "ProtParaGroup", 0, 16, E_PP_Total + 10);
	}


	ProtPara[E_PP_test1].PowerUpIni("����1", "E_PP_test1", ProtParaGroup, -50, 0, 1, 0, Unit_A);
	ProtPara[E_PP_test2].PowerUpIni("����2", "E_PP_test2", ProtParaGroup, 50, 50, 100, 0, Unit_NULL);
	ProtPara[E_PP_UnitName].StrPowerUpIni("װ������", "UnitName", ProtParaGroup, "�����豸");
	ProtPara[E_PP_Ct].CTEnumPowerUpIni("CT����ֵ", "E_PP_Ct", ProtParaGroup, 0);
	ProtPara[E_PP_Current].RelatedCTPowerUpIni("����ֵ", "E_PP_Current", ProtParaGroup, 50, 12345, 20000, 3, Unit_A, ProtPara[E_PP_Ct]);
	ProtPara[E_PP_Bit].BitOnOffPowerUpIni("��բ����", "E_PP_Bit", ProtParaGroup, 0, 0xF, 0XFFFF, 2, TripDes);
	ProtPara[E_PP_Hex].HexPowerUpIni("Hex��ֵ", "E_PP_Hex", ProtParaGroup, 0, 0xF, 0XFFFF, 2);
	ProtParaGroup.UpdateForUse();
	HmiParaEditGroup.PowerUpIni(1000);

	PtctParaGroup.PowerUpIni("Ptct����", "PtctParaGroup", 10);
	PtctPara[0].UInt32PowerUpIni("����1", "E_PP_test1", PtctParaGroup, 50, 0, 3000000000, 0, Unit_A, 0);
	PtctPara[1].UInt32PowerUpIni("����1", "E_PP_test1", PtctParaGroup, 50, 0, 3000000000, 0, Unit_A, 1);
	//�쳣���磬�����ָ�
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
