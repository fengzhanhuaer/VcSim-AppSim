#include "InstResource.h"

ApiBoardNormalStateOut NorDoBoard[5];
ApiNormalBoolOut NorDoOut[10];
ApiGoOutDataSet GoDataSetOut[5];
ApiGoOutFrame GoOutFrame[1];
ApiGoPosOut GoOutCell[100];


void AppStateOutPowerUpIni()
{
	NorDoBoard[0].PowerUpIni("开出板卡1", "NorDoBoard1", SptNormalStateOutBoard::E_Board_Do32Pin_1, 0, 0);
	NorDoOut[0].ProtOutPowerUpIni(NorDoBoard[0], "开出1", "NorDoOut1", 0);
	NorDoBoard[1].PowerUpIni("开出板卡2", "NorDoBoard2", SptNormalStateOutBoard::E_Board_Do32Pin_1, 1, 1);
	NorDoOut[1].ProtOutPowerUpIni(NorDoBoard[1], "开出2", "NorDoOut2", 1);
	NorDoBoard[2].PowerUpIni("开出板卡3", "NorDoBoard3", SptNormalStateOutBoard::E_Board_Do32Pin_1, 2, 2);
	NorDoOut[2].ProtOutPowerUpIni(NorDoBoard[2], "开出3", "NorDoOut3", 2);
	NorDoBoard[3].PowerUpIni("开出板卡4", "NorDoBoard4", SptNormalStateOutBoard::E_Board_Do32Pin_1, 3, 3);
	NorDoOut[3].ProtOutPowerUpIni(NorDoBoard[3], "开出4", "NorDoOut4", 3);
	NorDoBoard[4].PowerUpIni("开出板卡5", "NorDoBoard5", SptNormalStateOutBoard::E_Board_Do32Pin_1, 4, 4);
	NorDoOut[4].ProtOutPowerUpIni(NorDoBoard[4], "开出5", "NorDoOut5", 4);
	NorDoOut[5].ProtOutPowerUpIni(NorDoBoard[4], "开出6", "NorDoOut6", 5);
	NorDoOut[6].ProtOutPowerUpIni(NorDoBoard[4], "开出7", "NorDoOut7", 6);
	NorDoOut[7].ProtOutPowerUpIni(NorDoBoard[4], "开出8", "NorDoOut8", 7);
	NorDoOut[8].ProtOutPowerUpIni(NorDoBoard[4], "开出9", "NorDoOut9", 8);
	NorDoOut[9].ProtOutPowerUpIni(NorDoBoard[4], "开出10", "NorDoOut10", 9);

	GoOutFrame[0].PowerUpIni("GOOSE输出帧", "GoOutFrame[0]", 0, 100);

	GoDataSetOut[0].PowerUpIni("Go数据集1", "dsGOOSE1", "dsGOOSE1", GoOutFrame[0], 100);
	GoDataSetOut[1].PowerUpIni("Go数据集2", "dsGOOSE2", "dsGOOSE2", GoOutFrame[0], 100);
	GoDataSetOut[2].PowerUpIni("Go数据集3", "dsGOOSE3", "dsGOOSE3", GoOutFrame[0], 100);
	GoDataSetOut[3].PowerUpIni("Go数据集4", "dsGOOSE4", "dsGOOSE4", GoOutFrame[0], 100);
	GoDataSetOut[4].PowerUpIni("Go数据集5", "dsGOOSE5", "dsGOOSE5", GoOutFrame[0], 100);

	GoOutCell[0].PowerUpIni("GO1", "GoOutCell1", GoOutFrame[0], 0);
	GoOutCell[1].PowerUpIni("GO2", "GoOutCell2", GoOutFrame[0], 0);
	GoOutCell[2].PowerUpIni("GO3", "GoOutCell3", GoOutFrame[0], 0);
	GoOutCell[3].PowerUpIni("GO4", "GoOutCell4", GoOutFrame[0], 0);
	GoOutCell[4].PowerUpIni("GO5", "GoOutCell5", GoOutFrame[0], 0);
}
