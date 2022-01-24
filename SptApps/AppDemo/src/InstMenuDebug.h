#ifndef INSTMENUDEBUG_H
#define INSTMENUDEBUG_H

bool8 FuncMenuTest(ApiMenu* Menu);
bool8 EnterDebugMode(ApiMenu* Menu);
bool8 ExitDebugMode(ApiMenu* Menu);
bool8 Boot0Update(ApiMenu* Menu);
bool8 UbootUpdate(ApiMenu* Menu);
bool8 OsUpdate(ApiMenu* Menu);
bool8 Boot0Update1(ApiMenu* Menu);
bool8 UbootUpdate1(ApiMenu* Menu);
bool8 UpdateFpga1(ApiMenu* Menu);
bool8 UpdateFpga2(ApiMenu* Menu);
bool8 UpdateFpga3(ApiMenu* Menu);
bool8 OsUpdate1(ApiMenu* Menu);
bool8 FlashBak(ApiMenu* Menu);
bool8 RestoreFlashPara(ApiMenu* Menu);
bool8 FormatSysCard(ApiMenu* Menu);
bool8 FormatDataCard(ApiMenu* Menu);
bool8 DefaultProtSetPara(ApiMenu* Menu);
bool8 HmiDoOutSim(ApiMenu* Menu);
bool8 HmiGooseOutSim(ApiMenu* Menu);
bool8 HmiLedFlowWaterSim(ApiMenu* Menu);
bool8 HmiSendFile2SubBoard(ApiMenu* Menu);
bool8 HmiSptCmmState(ApiMenu* Menu);

#endif // !INSTMENUDEBUG_H

