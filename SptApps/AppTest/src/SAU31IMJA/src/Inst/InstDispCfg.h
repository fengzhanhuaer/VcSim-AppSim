#ifndef INSTDISPCFG_H
#define INSTDISPCFG_H

extern ApiAngRmsGroup ApiDispAnaGroup;
extern ApiAngRms ApiDispAna[CN_NUM_ANA];
// Ƶ�ʽ�����ʾ����
extern ApiAngRmsGroup ApiDispFrGroup;
extern ApiAngRms ApiDispFr[CN_NUM_CAL];
// ֱ����������ʾ����
extern ApiAngRmsGroup ApiDispDcGroup;
extern ApiAngRms ApiDispDc[CN_NUM_DC_SAM];
// ״̬���ӽ�����ʾ����
extern ApiAngRmsGroup ApiDispDevGroup;
extern ApiAngRms ApiDispDev[CN_NUM_DC_DEV];
// �⹦�ʽ�����ʾ����
extern ApiAngRmsGroup ApiDispOptGroup[2];
extern ApiAngRms ApiDispOpt[CN_NUM_DC_OPT1+CN_NUM_DC_OPT2];
// �м��־������ʾ����
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

