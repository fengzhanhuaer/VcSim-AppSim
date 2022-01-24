#include "InstResource.h"

//状态量开入板卡
ApiBoardNormalStateIn NormalStateBoardIn[2];
//开入状态量
ApiNormalBoolIn NormalBoolIn[10];
//直流量
ApiBoardNormalDcIn AppDcInBoard[1];
ApiNormalDcIn AppNormalDcIn[2];

ApiGoInCb          GoInCB[CN_NUM_GOCB];

void AppStateInPowerUpIni()
{
	NormalStateBoardIn[0].PowerUpIni("遥信开入板卡1", "NormalStateBoardIn1", HalBoard::E_Board_YX32Pin_1, 1, 0);
	NormalBoolIn[0].PowerUpIni(NormalStateBoardIn[0], "遥信开入1", "NormalBoolIn1", 0);
	NormalBoolIn[1].PowerUpIni(NormalStateBoardIn[0], "遥信开入2", "NormalBoolIn2", 1);
	NormalStateBoardIn[1].PowerUpIni("遥信开入板卡2", "NormalStateBoardIn2", HalBoard::E_Board_YX32Pin_1, 2, 1);
	NormalBoolIn[2].PowerUpIni(NormalStateBoardIn[1], "遥信开入3", "NormalBoolIn3", 0);
	NormalBoolIn[3].PowerUpIni(NormalStateBoardIn[1], "遥信开入4", "NormalBoolIn4", 1);
	NormalBoolIn[4].PowerUpIni(NormalStateBoardIn[1], "遥信开入5", "NormalBoolIn5", 2);
	NormalBoolIn[5].PowerUpIni(NormalStateBoardIn[1], "遥信开入6", "NormalBoolIn6", 3);
	NormalBoolIn[6].PowerUpIni(NormalStateBoardIn[1], "遥信开入7", "NormalBoolIn7", 4);
	NormalBoolIn[7].PowerUpIni(NormalStateBoardIn[1], "遥信开入8", "NormalBoolIn8", 5);
	NormalBoolIn[8].PowerUpIni(NormalStateBoardIn[1], "遥信开入9", "NormalBoolIn9", 6);
	NormalBoolIn[9].PowerUpIni(NormalStateBoardIn[1], "遥信开入10", "NormalBoolIn10", 7);

	AppDcInBoard[0].PowerUpIni("直流量板卡", "AppDcInBoard[0]", HalBoard::E_Board_Dc32Pin_1, 0, 0, 6);
	AppNormalDcIn[0].PowerUpIni(AppDcInBoard[0], "直流量开入1", "AppNormalDcIn[0]", 0, Unit_A);
	AppNormalDcIn[1].PowerUpIni(AppDcInBoard[0], "直流量开入2", "AppNormalDcIn[1]", 1, Unit_A);
}

void UpdateNorStateIn()
{
	NorDoOut[0].SetValue(NormalBoolIn[0].Value());
	NorDoOut[1].SetValue(NormalBoolIn[1].Value());
	NorDoOut[2].SetValue(NormalBoolIn[2].Value());
	NorDoOut[3].SetValue(NormalBoolIn[3].Value());
	NorDoOut[4].SetValue(NormalBoolIn[4].Value());
}
