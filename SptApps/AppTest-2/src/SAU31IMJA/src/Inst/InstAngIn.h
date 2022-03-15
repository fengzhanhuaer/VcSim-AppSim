#ifndef INSTANGIN_H
#define INSTANGIN_H

extern ApiBoardAngFrameIn   AngFrameIn[1];
extern ApiBoardNormalAngIn  AngNorAngIn[CN_NUM_BOARD_SAM];
extern ApiNormalAngIn       AngNorAngSampIn[CN_NUM_AD];
#if(CN_DEV_CPU1)
extern ApiSvInVirBoard      VirSvBoard[CN_NUM_BOARD_SV];
extern ApiSvIn              SvAngInDelayA;// A套SV额定延时
extern ApiSvIn              SvAngInDelayB;// B套SV额定延时
extern ApiSvIn              SvAngIn[CN_NUM_SV];
// 板间SV输入信息 CPU2
#elif(CN_DEV_CPU2)
extern ApiBoardCmmSvIn      CmmSvIn[CN_NUM_SV];
#endif
// 模拟量上电初始化
void AppAngInPowerUpIni();
void AppAngInCfgRef();
void AppAngInRef();
void AppAngQRef();
void AppAngParaRef();
#endif // !INSTANGIN_H
