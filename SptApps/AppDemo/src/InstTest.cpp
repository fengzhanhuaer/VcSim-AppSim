#include "InstResource.h"
bool8 FuncMenuTest(ApiMenu* Menu)
{
	FwGroupPub.StartRecord(1);
	FwGroupPrivate.StartRecord(1);
	MsSleep(300);
	FwGroupPub.StartRecord(0);
	FwGroupPrivate.StartRecord(0);
	MsSleep(300);
	FwGroupPub.StartRecord(1);
	FwGroupPrivate.StartRecord(1);
	MsSleep(3000);
	FwGroupPub.StartRecord(0);
	FwGroupPrivate.StartRecord(0);
	return 1;
}