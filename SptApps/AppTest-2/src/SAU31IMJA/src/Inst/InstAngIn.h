#ifndef INSTANGIN_H
#define INSTANGIN_H

extern ApiBoardAngFrameIn   AngFrameIn[1];
extern ApiBoardNormalAngIn  AngNorAngIn[CN_NUM_BOARD_SAM];
extern ApiNormalAngIn       AngNorAngSampIn[CN_NUM_AD];
#if(CN_DEV_CPU1)
extern ApiSvInVirBoard      VirSvBoard[CN_NUM_BOARD_SV];
extern ApiSvIn              SvAngInDelayA;// A��SV���ʱ
extern ApiSvIn              SvAngInDelayB;// B��SV���ʱ
extern ApiSvIn              SvAngIn[CN_NUM_SV];
// ���SV������Ϣ CPU2
#elif(CN_DEV_CPU2)
extern ApiBoardCmmSvIn      CmmSvIn[CN_NUM_SV];
#endif
// ģ�����ϵ��ʼ��
void AppAngInPowerUpIni();
void AppAngInCfgRef();
void AppAngInRef();
void AppAngQRef();
void AppAngParaRef();
#endif // !INSTANGIN_H
