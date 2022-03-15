#ifndef INSTSTATEOUT_H
#define INSTSTATEOUT_H

extern ApiBoardNormalStateOut NorDoBoard[CN_NUM_BOARD_DO_RTN];
extern ApiNormalBoolOut NorDoOut[CN_NUM_DO_RTN];
// GOOSE开出
extern ApiGoOutFrame   GoOutFrame[1];
extern ApiGoOutDataSet GoDataSetOut[CN_NUM_GOCB_PUB];
extern ApiGoPosOut     GoPosOutCell[CN_NUM_DI_DI+CN_NUM_GOOUT];  // 硬开入转GOOSE开出
extern ApiGoDpPosOut   GoDpPosOutCell[CN_NUM_DPI];                  // 双点开入转GOOSE开出
extern ApiGoUnion32Out GoDcOutCell[CN_NUM_DC];                      // 直流信息

void AppStateOutPowerUpIni();
void AppStateOutCfgRef();
void AppStateOutRtnRef();
void AppStateOutRef();

#endif
