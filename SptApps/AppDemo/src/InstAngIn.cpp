#include "InstResource.h"
using namespace spt;

ApiBoardAngFrameIn AngFrameIn[1];
ApiBoardNormalAngIn AngNorAngIn[2];
ApiNormalAngIn AngNorAngSampIn[13];
ApiNormalAngIn AngNorAngSampInDelay;
ApiSvInVirBoard VirSvBoard[5];
ApiSvIn SvAngIn[7];

void AppAngInPowerUpIni()
{
	AngFrameIn[0].PowerUpIni("ģ��������֡", "AngFrameIn0", 0, 30, 5, 8);
	AngNorAngIn[0].PowerUpIni("ģ��������忨1", "AngNorAngIn0", AngFrameIn[0], HalBoard::E_Board_Ang24Pin_1, 0);
	AngNorAngIn[1].PowerUpIni("ģ��������忨2", "AngNorAngIn1", AngFrameIn[0], HalBoard::E_Board_Ang24Pin_1, 1);
	ApiNormalAngIn* SvIn = AngNorAngSampIn;
	SvIn->PowerUpIni(AngNorAngIn[0], "һĸA�����", "AngNorAngSampIn0", 0, 0, 0, Unit_A);  SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[0], "һĸB�����", "AngNorAngSampIn1", 1, 0, 1, Unit_A);  SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[0], "һĸC�����", "AngNorAngSampIn2", 2, 0, 2, Unit_A);  SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[0], "һĸA���ѹ", "AngNorAngSampIn3", 3, 0, 3, Unit_V);  SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[0], "һĸB���ѹ", "AngNorAngSampIn4", 4, 0, 4, Unit_V);  SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[0], "һĸC���ѹ", "AngNorAngSampIn5", 5, 0, 5, Unit_V);  SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[1], "��ĸA�����", "AngNorAngSampIn6", 0, 0, 6, Unit_A);  SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[1], "��ĸA�����", "AngNorAngSampIn7", 1, 0, 7, Unit_A);  SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[1], "��ĸA�����", "AngNorAngSampIn8", 2, 1, 0, Unit_A);  SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[1], "��ĸA���ѹ", "AngNorAngSampIn9", 3, 1, 1, Unit_V);  SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[1], "��ĸB���ѹ", "AngNorAngSampIn10", 4, 1, 2, Unit_V); SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[1], "��ĸC���ѹ", "AngNorAngSampIn11", 5, 1, 3, Unit_V); SvIn++;
	ApiSvIn* Sv = SvAngIn;
	Sv->PowerUpIni(AngFrameIn[0], "SVһĸA�����", "SvAngIn2", 0, Unit_A);  Sv++;
	Sv->PowerUpIni(AngFrameIn[0], "SVһĸB�����", "SvAngIn3", 1, Unit_A);  Sv++;
	Sv->PowerUpIni(AngFrameIn[0], "SVһĸC�����", "SvAngIn4", 2, Unit_A);  Sv++;
	Sv->PowerUpIni(AngFrameIn[0], "SVһĸA���ѹ", "SvAngIn5", 3, Unit_V);  Sv++;
	Sv->PowerUpIni(AngFrameIn[0], "SVһĸB���ѹ", "SvAngIn6", 4, Unit_V);  Sv++;

	VirSvBoard[0].PowerUpIni("ģ�����������ݼ�1", "VirSvBoard0", AngFrameIn[0], 20);
	VirSvBoard[1].PowerUpIni("ģ�����������ݼ�2", "VirSvBoard0", AngFrameIn[0], 20);
	VirSvBoard[2].PowerUpIni("ģ�����������ݼ�3", "VirSvBoard1", AngFrameIn[0], 20);
	VirSvBoard[3].PowerUpIni("ģ�����������ݼ�4", "VirSvBoard2", AngFrameIn[0], 20);
	VirSvBoard[4].PowerUpIni("ģ�����������ݼ�5", "VirSvBoard3", AngFrameIn[0], 20);
}
double buf[80];
uint32 writer;
void AppAngSampIn()
{
	//������Чֵ
	if (writer < 80)
	{
		buf[writer++] = AngNorAngSampIn[0].Value();

	}
	else
	{
		writer = 0;
	}
	ApiAnglogRms[0].PushData(AngNorAngSampIn[0].Value(), 10);
	ApiAnglogRms[1].PushData(AngNorAngSampIn[1].Value(), 2);
	ApiAnglogRms[2].PushData(AngNorAngSampIn[2].Value(), 30);
	ApiAnglogRms[3].PushData(AngNorAngSampIn[3].Value(), 4);
	ApiAnglogRms[4].PushData(AngNorAngSampIn[4].Value(), 50);
	ApiAnglogRms[5].PushData(AngNorAngSampIn[5].Value(), 6);
	ApiAnglogRms[6].PushData(AngNorAngSampIn[6].Value(), 7);
	ApiAnglogRms[7].PushData(AngNorAngSampIn[7].Value(), 80);
	ApiAnglogRms[8].PushData(AngNorAngSampIn[8].Value(), 9);
	ApiAnglogRms[9].PushData(AngNorAngSampIn[9].Value(), 10);
	ApiAnglogRms[10].PushData(AngNorAngSampIn[10].Value(), 11);
	ApiAnglogRms[11].PushData(AngNorAngSampIn[11].Value(), 120);
	ApiAnglogRms[12].PushData(AngNorAngSampIn[10].Value(), 13);
	ApiAnglogRms[13].PushData(AngNorAngSampIn[11].Value(), 140);
	ApiAnglogRmsGroup[0].Update(0);
	//���������Ʒ��
	AngFrameIn[0].SetOutQ(0, 0x01);


}
