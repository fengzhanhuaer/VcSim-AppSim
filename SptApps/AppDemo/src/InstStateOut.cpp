#include "InstResource.h"

ApiBoardNormalStateOut NorDoBoard[5];
ApiNormalBoolOut NorDoOut[10];
ApiGoOutDataSet GoDataSetOut[5];
ApiGoOutFrame GoOutFrame[1];
ApiGoPosOut GoOutCell[100];


void AppStateOutPowerUpIni()
{
	NorDoBoard[0].PowerUpIni("�����忨1", "NorDoBoard1", SptNormalStateOutBoard::E_Board_Do32Pin_1, 0, 0);
	NorDoOut[0].ProtOutPowerUpIni(NorDoBoard[0], "����1", "NorDoOut1", 0);
	NorDoBoard[1].PowerUpIni("�����忨2", "NorDoBoard2", SptNormalStateOutBoard::E_Board_Do32Pin_1, 1, 1);
	NorDoOut[1].ProtOutPowerUpIni(NorDoBoard[1], "����2", "NorDoOut2", 1);
	NorDoBoard[2].PowerUpIni("�����忨3", "NorDoBoard3", SptNormalStateOutBoard::E_Board_Do32Pin_1, 2, 2);
	NorDoOut[2].ProtOutPowerUpIni(NorDoBoard[2], "����3", "NorDoOut3", 2);
	NorDoBoard[3].PowerUpIni("�����忨4", "NorDoBoard4", SptNormalStateOutBoard::E_Board_Do32Pin_1, 3, 3);
	NorDoOut[3].ProtOutPowerUpIni(NorDoBoard[3], "����4", "NorDoOut4", 3);
	NorDoBoard[4].PowerUpIni("�����忨5", "NorDoBoard5", SptNormalStateOutBoard::E_Board_Do32Pin_1, 4, 4);
	NorDoOut[4].ProtOutPowerUpIni(NorDoBoard[4], "����5", "NorDoOut5", 4);
	NorDoOut[5].ProtOutPowerUpIni(NorDoBoard[4], "����6", "NorDoOut6", 5);
	NorDoOut[6].ProtOutPowerUpIni(NorDoBoard[4], "����7", "NorDoOut7", 6);
	NorDoOut[7].ProtOutPowerUpIni(NorDoBoard[4], "����8", "NorDoOut8", 7);
	NorDoOut[8].ProtOutPowerUpIni(NorDoBoard[4], "����9", "NorDoOut9", 8);
	NorDoOut[9].ProtOutPowerUpIni(NorDoBoard[4], "����10", "NorDoOut10", 9);

	GoOutFrame[0].PowerUpIni("GOOSE���֡", "GoOutFrame[0]", 0, 100);

	GoDataSetOut[0].PowerUpIni("Go���ݼ�1", "dsGOOSE1", "dsGOOSE1", GoOutFrame[0], 100);
	GoDataSetOut[1].PowerUpIni("Go���ݼ�2", "dsGOOSE2", "dsGOOSE2", GoOutFrame[0], 100);
	GoDataSetOut[2].PowerUpIni("Go���ݼ�3", "dsGOOSE3", "dsGOOSE3", GoOutFrame[0], 100);
	GoDataSetOut[3].PowerUpIni("Go���ݼ�4", "dsGOOSE4", "dsGOOSE4", GoOutFrame[0], 100);
	GoDataSetOut[4].PowerUpIni("Go���ݼ�5", "dsGOOSE5", "dsGOOSE5", GoOutFrame[0], 100);

	GoOutCell[0].PowerUpIni("GO1", "GoOutCell1", GoOutFrame[0], 0);
	GoOutCell[1].PowerUpIni("GO2", "GoOutCell2", GoOutFrame[0], 0);
	GoOutCell[2].PowerUpIni("GO3", "GoOutCell3", GoOutFrame[0], 0);
	GoOutCell[3].PowerUpIni("GO4", "GoOutCell4", GoOutFrame[0], 0);
	GoOutCell[4].PowerUpIni("GO5", "GoOutCell5", GoOutFrame[0], 0);
}
