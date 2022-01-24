#ifndef INSTSTATEIN_H
#define INSTSTATEIN_H

//硬开入
extern ApiBoardNormalStateIn NormalStateBoardIn[CN_NUM_BOARD_DI_DI];
extern ApiNormalBoolIn NormalBoolIn[CN_NUM_DI_DI];
//直流量
extern ApiBoardNormalDcIn AppDcInBoard;
extern ApiNormalDcIn      AppNormalDcIn[CN_NUM_DC_SAM];
// GOOSE开入
extern ApiGoInFrame       GoInFrame[1];
extern ApiGoInCb          GoInCB[CN_NUM_GOCB_SUB];
extern ApiGoPosIn         GoPosIn[CN_NUM_GOIN_S];
// 光功率信息
extern ApiSmartBoardInfo      SmartBoard[2];


void AppStateInPowerUpIni();
void AppStateInCfgRef();
void AppStateInRef();

#endif //INSTSTATEIN_H
