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
	AngFrameIn[0].PowerUpIni("模拟量输入帧", "AngFrameIn0", 0, 30, 5, 8);
	AngNorAngIn[0].PowerUpIni("模拟量输入板卡1", "AngNorAngIn0", AngFrameIn[0], HalBoard::E_Board_Ang24Pin_1, 0);
	AngNorAngIn[1].PowerUpIni("模拟量输入板卡2", "AngNorAngIn1", AngFrameIn[0], HalBoard::E_Board_Ang24Pin_1, 1);
	ApiNormalAngIn* SvIn = AngNorAngSampIn;
	SvIn->PowerUpIni(AngNorAngIn[0], "一母A相电流", "AngNorAngSampIn0", 0, 0, 0, Unit_A);  SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[0], "一母B相电流", "AngNorAngSampIn1", 1, 0, 1, Unit_A);  SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[0], "一母C相电流", "AngNorAngSampIn2", 2, 0, 2, Unit_A);  SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[0], "一母A相电压", "AngNorAngSampIn3", 3, 0, 3, Unit_V);  SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[0], "一母B相电压", "AngNorAngSampIn4", 4, 0, 4, Unit_V);  SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[0], "一母C相电压", "AngNorAngSampIn5", 5, 0, 5, Unit_V);  SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[1], "二母A相电流", "AngNorAngSampIn6", 0, 0, 6, Unit_A);  SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[1], "二母A相电流", "AngNorAngSampIn7", 1, 0, 7, Unit_A);  SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[1], "二母A相电流", "AngNorAngSampIn8", 2, 1, 0, Unit_A);  SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[1], "二母A相电压", "AngNorAngSampIn9", 3, 1, 1, Unit_V);  SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[1], "二母B相电压", "AngNorAngSampIn10", 4, 1, 2, Unit_V); SvIn++;
	SvIn->PowerUpIni(AngNorAngIn[1], "二母C相电压", "AngNorAngSampIn11", 5, 1, 3, Unit_V); SvIn++;
	ApiSvIn* Sv = SvAngIn;
	Sv->PowerUpIni(AngFrameIn[0], "SV一母A相电流", "SvAngIn2", 0, Unit_A);  Sv++;
	Sv->PowerUpIni(AngFrameIn[0], "SV一母B相电流", "SvAngIn3", 1, Unit_A);  Sv++;
	Sv->PowerUpIni(AngFrameIn[0], "SV一母C相电流", "SvAngIn4", 2, Unit_A);  Sv++;
	Sv->PowerUpIni(AngFrameIn[0], "SV一母A相电压", "SvAngIn5", 3, Unit_V);  Sv++;
	Sv->PowerUpIni(AngFrameIn[0], "SV一母B相电压", "SvAngIn6", 4, Unit_V);  Sv++;

	VirSvBoard[0].PowerUpIni("模拟量输入数据集1", "VirSvBoard0", AngFrameIn[0], 20);
	VirSvBoard[1].PowerUpIni("模拟量输入数据集2", "VirSvBoard0", AngFrameIn[0], 20);
	VirSvBoard[2].PowerUpIni("模拟量输入数据集3", "VirSvBoard1", AngFrameIn[0], 20);
	VirSvBoard[3].PowerUpIni("模拟量输入数据集4", "VirSvBoard2", AngFrameIn[0], 20);
	VirSvBoard[4].PowerUpIni("模拟量输入数据集5", "VirSvBoard3", AngFrameIn[0], 20);
}
double buf[80];
uint32 writer;
void AppAngSampIn()
{
	//更新有效值
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
	//更新输出的品质
	AngFrameIn[0].SetOutQ(0, 0x01);


}
