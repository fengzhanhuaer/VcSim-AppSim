#include "ApiProject.h"
using namespace spt;
static ApiAppFastCmm* ApiAppFastCmmInst = 0;
spt::ApiAppFastCmm::ApiAppFastCmm(const char* Name)
{
	StrNCpy(name, Name, sizeof(name));
}

int32 spt::ApiAppFastCmm::PowerUpIni(CmmMsgDriver* Driver, uint32 DriverNum, uint16 Sur, uint16 Dst, uint16 BufNum, uint16 BufLen)
{
	frmHeader.sur = Sur;
	frmHeader.dst = Dst;
	frmHeader.type = SCT_AppFastCmm;
	ApiAppFastCmmInst = this;
	driver = Driver;
	driverNum = DriverNum;
	SptAppFastCmm::PowerUpIni(BufLen, BufNum, BufLen, BufNum, BufLen, BufLen);
	return 0;
}

int32 spt::ApiAppFastCmm::SendMsg(uint32 UnPackIndex, uint16 Type, uint16 DataLen, void* Data)
{
	return SptAppFastCmm::SendMsgTo(frmHeader.dst, UnPackIndex, Type, DataLen, Data);
}

int32 spt::ApiAppFastCmm::SendMsgTo(uint16 Dst, uint32 UnPackIndex, uint16 Type, uint16 DataLen, void* Data)
{
	return SptAppFastCmm::SendMsgTo(frmHeader.dst, UnPackIndex, Type, DataLen, Data);
}

ApiAppFastCmm& spt::ApiAppFastCmm::Instance()
{
	static ApiAppFastCmm AppInstFastCmm("FastCmm");
	return AppInstFastCmm;
}

spt::ApiAppSlowCmm::ApiAppSlowCmm(const char* Name)
{
	StrNCpy(name, Name, sizeof(name));
}

int32 spt::ApiAppSlowCmm::PowerUpIni(CmmMsgDriver* Driver, uint32 DriverNum, uint16 Sur, uint16 Dst, uint16 BufNum, uint16 BufLen)
{
	frmHeader.sur = Sur;
	frmHeader.dst = Dst;
	frmHeader.type = SCT_AppSlowCmm;
	driver = Driver;
	driverNum = DriverNum;
	SptAppSlowCmm::PowerUpIni(BufLen, BufNum, BufLen, BufNum, BufLen, BufLen);
	return 0;
}

int32 spt::ApiAppSlowCmm::SendMsg(uint32 UnPackIndex, uint16 Type, uint16 DataLen, void* Data)
{
	return SptAppSlowCmm::SendMsgTo(frmHeader.dst, UnPackIndex, Type, DataLen, Data);
}

int32 spt::ApiAppSlowCmm::SendMsgTo(uint16 Dst, uint32 UnPackIndex, uint16 Type, uint16 DataLen, void* Data)
{
	return SptAppSlowCmm::SendMsgTo(frmHeader.dst, UnPackIndex, Type, DataLen, Data);
}

