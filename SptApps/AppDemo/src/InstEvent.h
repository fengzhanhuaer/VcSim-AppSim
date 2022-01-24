#ifndef INSTEVENT_H
#define INSTEVENT_H

enum Event_Warn
{
	E_Test1,
	E_Test2,
	E_Warn_Total
};

extern ApiEvent AppEventWarn[E_Warn_Total];
extern ApiEventGroup AppEventWarnGroup;
extern ApiEventViewPool HmiViewEventPool;

void AppEventPowerUpIni();



#endif // !INSTEVENT_H

