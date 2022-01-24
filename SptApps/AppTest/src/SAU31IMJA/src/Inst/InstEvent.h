#ifndef INSTEVENT_H
#define INSTEVENT_H

extern ApiEvent AppEventAct[CN_NUM_ACT];
extern ApiEvent AppEventWarn[CN_NUM_ALM];
extern ApiEvent AppEventChek[CN_NUM_CHK];
extern ApiEvent AppEventRun[CN_NUM_RUN];
extern ApiEvent AppEventOpt[CN_NUM_OPT];
extern ApiEvent AppEventDISoe[CN_NUM_DI];
extern ApiEvent AppEventGoInSoe[CN_NUM_GOIN];
extern ApiEvent AppEventFlagSoe[CN_NUM_FLAG];
extern ApiEvent AppEventDOSoe[CN_NUM_DO];
extern ApiEvent AppEventGoOutSoe[CN_NUM_GOOUT];
extern ApiEvent AppEventLedSoe[CN_NUM_LED];
extern ApiEvent AppEventDpiSoe[CN_NUM_DPI];

extern ApiEventGroup AppEventActGroup;
extern ApiEventGroup AppEventWarnGroup;
extern ApiEventGroup AppEventChekGroup;
extern ApiEventGroup AppEventRunGroup;
extern ApiEventGroup AppEventOptGroup;

extern ApiEventGroup AppEventDISoeGroup;
extern ApiEventGroup AppEventGoInSoeGroup;
extern ApiEventGroup AppEventFlagSoeGroup;
extern ApiEventGroup AppEventDOSoeGroup;
extern ApiEventGroup AppEventGoOutSoeGroup;
extern ApiEventGroup AppEventLedSoeGroup;
extern ApiEventGroup AppEventDpiSoeGroup;
extern ApiEventViewPool HmiViewEventPool;

void AppEventPowerUpIni();
void AppEventOutRef();
void AppEventRunRef(WORD wRunIndex);
void AppEventOptRef(WORD wOptIndex);
void AppEventOptValueRef(WORD wOptIndex,DWORD iMeaValue1,DWORD iMeaValue2,DWORD iMeaValue3);
INT32 AppEventClear(WORD wIndex);
#endif // !INSTEVENT_H

