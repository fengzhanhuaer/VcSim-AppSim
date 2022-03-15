#ifndef INSTANGOUT_H
#define INSTANGOUT_H

extern ApiBoardAngFrameOut virSvOutBoard;
extern ApiSvOutVirDataSet virSvSendDateSet;
extern ApiSvOut SvSendDataSetCell[CN_NUM_ANA];
#if(CN_DEV_CPU1)
extern ApiBoardCmmSvOutVirDataSet  virCmmSvSendDateSet;
extern ApiBoardCmmSv               CmmSvSendDataSetCell[EN_LINK_END];
#endif
void   AppAngOutPowerUpIni();
void   AppAngOutCfgRef();
void   AppAngListRef();

#endif // !INSTANGOUT_H

