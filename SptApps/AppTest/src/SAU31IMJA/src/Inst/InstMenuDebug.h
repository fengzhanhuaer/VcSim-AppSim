#ifndef INSTMENUDEBUG_H
#define INSTMENUDEBUG_H

bool8 EnterDebugMode(ApiMenu* Menu);
bool8 ExitDebugMode(ApiMenu* Menu);
bool8 EnterFactDebugMode(ApiMenu* Menu);
bool8 ExitFactDebugMode(ApiMenu* Menu);
bool8 Boot0Update(ApiMenu* Menu);
bool8 UbootUpdate(ApiMenu* Menu);
bool8 OsUpdate(ApiMenu* Menu);
bool8 Boot0Update1(ApiMenu* Menu);
bool8 UbootUpdate1(ApiMenu* Menu);
bool8 UpdateFpga1(ApiMenu* Menu);
bool8 UpdateFpga2(ApiMenu* Menu);
bool8 OsUpdate1(ApiMenu* Menu);
bool8 FlashBak(ApiMenu* Menu);
bool8 RestoreFlashPara(ApiMenu* Menu);
bool8 FormatSysCard(ApiMenu* Menu);
bool8 FormatDataCard(ApiMenu* Menu);
bool8 DefaultAllPara(ApiMenu* Menu);
bool8 DefaultDiPara(ApiMenu* Menu);
bool8 DefaultDcPara(ApiMenu* Menu);
bool8 DefaultAnaPara(ApiMenu* Menu);
bool8 DefaultFunPara(ApiMenu* Menu);
bool8 DefaultDcCoePara(ApiMenu* Menu);
bool8 DefaultAmCoePara(ApiMenu* Menu);
bool8 DefaultDcBcCoePara(ApiMenu* Menu);
bool8 DefaultAngCoePara(ApiMenu* Menu);

bool8 ClaerAllEvent(ApiMenu* Menu);
bool8 ClaerActEvent(ApiMenu* Menu);
bool8 ClaerAlmEvent(ApiMenu* Menu);
bool8 ClaerChkEvent(ApiMenu* Menu);
bool8 ClaerRunEvent(ApiMenu* Menu);
bool8 ClaerOptEvent(ApiMenu* Menu);
bool8 ClaerPrvtSoeEvent(ApiMenu* Menu);
bool8 ClaerPrvtOptEvent(ApiMenu* Menu);
bool8 ClaerDiSoe(ApiMenu* Menu);
bool8 ClaerDoSoe(ApiMenu* Menu);
bool8 ClaerGoInSoe(ApiMenu* Menu);
bool8 ClaerGoOutSoe(ApiMenu* Menu);
bool8 ClaerLedSoe(ApiMenu* Menu);
bool8 ClaerDpiSoe(ApiMenu* Menu);
bool8 ClaerFlagSoe(ApiMenu* Menu);

bool8 HmiDoOutSim(ApiMenu* Menu);
bool8 HmiGooseOutSSim(ApiMenu* Menu);
bool8 HmiGooseOutDSim(ApiMenu* Menu);
bool8 HmiGooseOutDcSim(ApiMenu* Menu);
bool8 HmiLedFlowWaterSim(ApiMenu* Menu);
bool8 HmiSendFile2SubBoard(ApiMenu* Menu);
bool8 HmiSptCmmState(ApiMenu* Menu);

#endif // !INSTMENUDEBUG_H

