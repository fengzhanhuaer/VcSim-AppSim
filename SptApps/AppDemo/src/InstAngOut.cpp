#include "InstResource.h"
using namespace spt;

ApiBoardAngFrameOut virSvOutBoard;
ApiSvOutVirDataSet virSvSendDateSet[1];
ApiSvOut SvSendDataSetCell[20];

ApiAngRmsGroup ApiAnglogRmsGroup[1];
ApiAngRms ApiAnglogRms[15];

void AppAngOutPowerUpIni()
{
	ApiAnglogRmsGroup[0].PowerUpIni("ģ������Чֵ", "ApiAnglogRmsGroup[0]", 20, 20);
	ApiAnglogRms[0].PowerUpIni("һĸA�����", "ApiAnglogRms[0]", ApiAnglogRmsGroup[0], 1, 3, Unit_A, 1, Unit_ANGLE, 2);
	ApiAnglogRms[1].PowerUpIni("һĸA�����", "ApiAnglogRms[1]", ApiAnglogRmsGroup[0], 0, 3, Unit_A, 1, Unit_ANGLE, 2);
	ApiAnglogRms[2].PowerUpIni("һĸA�����", "ApiAnglogRms[2]", ApiAnglogRmsGroup[0], 0, 3, Unit_A, 1, Unit_ANGLE, 2);
	ApiAnglogRms[3].PowerUpIni("һĸA����ѹ", "ApiAnglogRms[3]", ApiAnglogRmsGroup[0], 0, 3, Unit_V, 1, Unit_ANGLE, 2);
	ApiAnglogRms[4].PowerUpIni("һĸA����ѹ", "ApiAnglogRms[4]", ApiAnglogRmsGroup[0], 0, 3, Unit_V, 1, Unit_ANGLE, 2);
	ApiAnglogRms[5].PowerUpIni("һĸA����ѹ", "ApiAnglogRms[5]", ApiAnglogRmsGroup[0], 0, 3, Unit_V, 1, Unit_ANGLE, 2);

	ApiAnglogRms[6].PowerUpIni("һĸA�����", "ApiAnglogRms[6]", ApiAnglogRmsGroup[0], 0, 3, Unit_A, 1, Unit_ANGLE, 2);
	ApiAnglogRms[7].PowerUpIni("һĸA�����", "ApiAnglogRms[7]", ApiAnglogRmsGroup[0], 0, 3, Unit_A, 1, Unit_ANGLE, 2);
	ApiAnglogRms[8].PowerUpIni("һĸA�����", "ApiAnglogRms[8]", ApiAnglogRmsGroup[0], 0, 3, Unit_A, 1, Unit_ANGLE, 2);
	ApiAnglogRms[9].PowerUpIni("һĸA����ѹ", "ApiAnglogRms[9]", ApiAnglogRmsGroup[0], 0, 3, Unit_V, 1, Unit_ANGLE, 2);
	ApiAnglogRms[10].PowerUpIni("һĸA����ѹ", "ApiAnglogRms[10]", ApiAnglogRmsGroup[0], 0, 3, Unit_V, 1, Unit_ANGLE, 2);
	ApiAnglogRms[11].PowerUpIni("һĸA����ѹ", "ApiAnglogRms[11]", ApiAnglogRmsGroup[0], 0, 3, Unit_V, 1, Unit_ANGLE, 2);
	ApiAnglogRms[12].PowerUpIni("һĸA����ѹ", "ApiAnglogRms[12]", ApiAnglogRmsGroup[0], 0, 3, Unit_V, 1, Unit_ANGLE, 2);
	ApiAnglogRms[13].PowerUpIni("һĸA����ѹ", "ApiAnglogRms[13]", ApiAnglogRmsGroup[0], 0, 3, Unit_V, 1, Unit_ANGLE, 2);
	ApiAnglogRms[14].PowerUpIni("һĸA����ѹ", "ApiAnglogRms[14]", ApiAnglogRmsGroup[0], 0, 3, Unit_V, 1, Unit_ANGLE, 2);

	virSvOutBoard.PowerUpIni("�������ݼ�", "virSvOutBoard", 0, 100);
	virSvSendDateSet[0].PowerUpIni("һĸ�������ݼ�", "dsSV1", "dsSV1", virSvOutBoard, 1500, 1, M_ArrLen(SvSendDataSetCell));
	SvSendDataSetCell[0].PowerUpIni(virSvOutBoard, "һĸA����ѹ", "SvSendDataSetCell0", Unit_V);
	SvSendDataSetCell[1].PowerUpIni(virSvOutBoard, "һĸB����ѹ", "SvSendDataSetCell1", Unit_V);
	SvSendDataSetCell[2].PowerUpIni(virSvOutBoard, "һĸC����ѹ", "SvSendDataSetCell2", Unit_V);
	SvSendDataSetCell[3].PowerUpIni(virSvOutBoard, "һĸA����ѹ", "SvSendDataSetCell3", Unit_V);
	SvSendDataSetCell[4].PowerUpIni(virSvOutBoard, "һĸB����ѹ", "SvSendDataSetCell4", Unit_V);
	SvSendDataSetCell[5].PowerUpIni(virSvOutBoard, "һĸC����ѹ", "SvSendDataSetCell5", Unit_V);
	SvSendDataSetCell[6].PowerUpIni(virSvOutBoard, "һĸA����ѹ", "SvSendDataSetCell6", Unit_V);
	SvSendDataSetCell[7].PowerUpIni(virSvOutBoard, "һĸB����ѹ", "SvSendDataSetCell7", Unit_V);
	SvSendDataSetCell[8].PowerUpIni(virSvOutBoard, "һĸC����ѹ", "SvSendDataSetCell8", Unit_V);
	SvSendDataSetCell[9].PowerUpIni(virSvOutBoard, "һĸA����ѹ", "SvSendDataSetCell9", Unit_V);
	SvSendDataSetCell[10].PowerUpIni(virSvOutBoard, "һĸB����ѹ", "SvSendDataSetCell10", Unit_V);
	SvSendDataSetCell[11].PowerUpIni(virSvOutBoard, "һĸC����ѹ", "SvSendDataSetCell11", Unit_V);
	SvSendDataSetCell[12].PowerUpIni(virSvOutBoard, "һĸA����ѹ", "SvSendDataSetCell12", Unit_V);
	SvSendDataSetCell[13].PowerUpIni(virSvOutBoard, "һĸB����ѹ", "SvSendDataSetCell13", Unit_V);
	SvSendDataSetCell[14].PowerUpIni(virSvOutBoard, "һĸC����ѹ", "SvSendDataSetCell14", Unit_V);
}
void AppAngSampOut()
{



}