#include "InstResource.h"
using namespace spt;

ApiBoardAngFrameOut virSvOutBoard;
ApiSvOutVirDataSet virSvSendDateSet[1];
ApiSvOut SvSendDataSetCell[20];

ApiAngRmsGroup ApiAnglogRmsGroup[1];
ApiAngRms ApiAnglogRms[15];

void AppAngOutPowerUpIni()
{
	ApiAnglogRmsGroup[0].PowerUpIni("模拟量有效值", "ApiAnglogRmsGroup[0]", 20, 20);
	ApiAnglogRms[0].PowerUpIni("一母A相电流", "ApiAnglogRms[0]", ApiAnglogRmsGroup[0], 1, 3, Unit_A, 1, Unit_ANGLE, 2);
	ApiAnglogRms[1].PowerUpIni("一母A相电流", "ApiAnglogRms[1]", ApiAnglogRmsGroup[0], 0, 3, Unit_A, 1, Unit_ANGLE, 2);
	ApiAnglogRms[2].PowerUpIni("一母A相电流", "ApiAnglogRms[2]", ApiAnglogRmsGroup[0], 0, 3, Unit_A, 1, Unit_ANGLE, 2);
	ApiAnglogRms[3].PowerUpIni("一母A相电电压", "ApiAnglogRms[3]", ApiAnglogRmsGroup[0], 0, 3, Unit_V, 1, Unit_ANGLE, 2);
	ApiAnglogRms[4].PowerUpIni("一母A相电电压", "ApiAnglogRms[4]", ApiAnglogRmsGroup[0], 0, 3, Unit_V, 1, Unit_ANGLE, 2);
	ApiAnglogRms[5].PowerUpIni("一母A相电电压", "ApiAnglogRms[5]", ApiAnglogRmsGroup[0], 0, 3, Unit_V, 1, Unit_ANGLE, 2);

	ApiAnglogRms[6].PowerUpIni("一母A相电流", "ApiAnglogRms[6]", ApiAnglogRmsGroup[0], 0, 3, Unit_A, 1, Unit_ANGLE, 2);
	ApiAnglogRms[7].PowerUpIni("一母A相电流", "ApiAnglogRms[7]", ApiAnglogRmsGroup[0], 0, 3, Unit_A, 1, Unit_ANGLE, 2);
	ApiAnglogRms[8].PowerUpIni("一母A相电流", "ApiAnglogRms[8]", ApiAnglogRmsGroup[0], 0, 3, Unit_A, 1, Unit_ANGLE, 2);
	ApiAnglogRms[9].PowerUpIni("一母A相电电压", "ApiAnglogRms[9]", ApiAnglogRmsGroup[0], 0, 3, Unit_V, 1, Unit_ANGLE, 2);
	ApiAnglogRms[10].PowerUpIni("一母A相电电压", "ApiAnglogRms[10]", ApiAnglogRmsGroup[0], 0, 3, Unit_V, 1, Unit_ANGLE, 2);
	ApiAnglogRms[11].PowerUpIni("一母A相电电压", "ApiAnglogRms[11]", ApiAnglogRmsGroup[0], 0, 3, Unit_V, 1, Unit_ANGLE, 2);
	ApiAnglogRms[12].PowerUpIni("一母A相电电压", "ApiAnglogRms[12]", ApiAnglogRmsGroup[0], 0, 3, Unit_V, 1, Unit_ANGLE, 2);
	ApiAnglogRms[13].PowerUpIni("一母A相电电压", "ApiAnglogRms[13]", ApiAnglogRmsGroup[0], 0, 3, Unit_V, 1, Unit_ANGLE, 2);
	ApiAnglogRms[14].PowerUpIni("一母A相电电压", "ApiAnglogRms[14]", ApiAnglogRmsGroup[0], 0, 3, Unit_V, 1, Unit_ANGLE, 2);

	virSvOutBoard.PowerUpIni("虚拟数据集", "virSvOutBoard", 0, 100);
	virSvSendDateSet[0].PowerUpIni("一母发送数据集", "dsSV1", "dsSV1", virSvOutBoard, 1500, 1, M_ArrLen(SvSendDataSetCell));
	SvSendDataSetCell[0].PowerUpIni(virSvOutBoard, "一母A相电电压", "SvSendDataSetCell0", Unit_V);
	SvSendDataSetCell[1].PowerUpIni(virSvOutBoard, "一母B相电电压", "SvSendDataSetCell1", Unit_V);
	SvSendDataSetCell[2].PowerUpIni(virSvOutBoard, "一母C相电电压", "SvSendDataSetCell2", Unit_V);
	SvSendDataSetCell[3].PowerUpIni(virSvOutBoard, "一母A相电电压", "SvSendDataSetCell3", Unit_V);
	SvSendDataSetCell[4].PowerUpIni(virSvOutBoard, "一母B相电电压", "SvSendDataSetCell4", Unit_V);
	SvSendDataSetCell[5].PowerUpIni(virSvOutBoard, "一母C相电电压", "SvSendDataSetCell5", Unit_V);
	SvSendDataSetCell[6].PowerUpIni(virSvOutBoard, "一母A相电电压", "SvSendDataSetCell6", Unit_V);
	SvSendDataSetCell[7].PowerUpIni(virSvOutBoard, "一母B相电电压", "SvSendDataSetCell7", Unit_V);
	SvSendDataSetCell[8].PowerUpIni(virSvOutBoard, "一母C相电电压", "SvSendDataSetCell8", Unit_V);
	SvSendDataSetCell[9].PowerUpIni(virSvOutBoard, "一母A相电电压", "SvSendDataSetCell9", Unit_V);
	SvSendDataSetCell[10].PowerUpIni(virSvOutBoard, "一母B相电电压", "SvSendDataSetCell10", Unit_V);
	SvSendDataSetCell[11].PowerUpIni(virSvOutBoard, "一母C相电电压", "SvSendDataSetCell11", Unit_V);
	SvSendDataSetCell[12].PowerUpIni(virSvOutBoard, "一母A相电电压", "SvSendDataSetCell12", Unit_V);
	SvSendDataSetCell[13].PowerUpIni(virSvOutBoard, "一母B相电电压", "SvSendDataSetCell13", Unit_V);
	SvSendDataSetCell[14].PowerUpIni(virSvOutBoard, "一母C相电电压", "SvSendDataSetCell14", Unit_V);
}
void AppAngSampOut()
{



}