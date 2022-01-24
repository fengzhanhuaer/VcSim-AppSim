#ifndef INSTDISPCFG_H
#define INSTDISPCFG_H

extern ApiAngRmsGroup ApiDispAnaGroup;
extern ApiAngRms ApiDispAna[CN_NUM_ANA];
// 频率界面显示配置
extern ApiAngRmsGroup ApiDispFrGroup;
extern ApiAngRms ApiDispFr[CN_NUM_CAL];
// 直流量界面显示配置
extern ApiAngRmsGroup ApiDispDcGroup;
extern ApiAngRms ApiDispDc[CN_NUM_DC_SAM];
// 状态监视界面显示配置
extern ApiAngRmsGroup ApiDispDevGroup;
extern ApiAngRms ApiDispDev[CN_NUM_DC_DEV];
// 光功率界面显示配置
extern ApiAngRmsGroup ApiDispOptGroup[2];
extern ApiAngRms ApiDispOpt[CN_NUM_DC_OPT1+CN_NUM_DC_OPT2];
// 中间标志界面显示配置
extern ApiAngRmsGroup ApiDispInterGroup;
extern ApiAngRms ApiDispInter[CN_NUM_FLAG+CN_NUM_INTER];

void   AppDispDcPowerUpIni();
void   AppDispPowerUpIni();
bool8   AppDispAnaAmRef();
bool8   AppDispAnaAmjRef();
bool8   AppDispFrRef();
bool8   AppDispDcRef();
bool8   AppDispDevRef();
bool8   AppDispOpt1Ref();
bool8   AppDispOpt2Ref();
bool8   AppDispInterRef();

#endif // !INSTDISPCFG_H

