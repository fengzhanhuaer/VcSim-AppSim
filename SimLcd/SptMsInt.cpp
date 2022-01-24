#include "SptProject.h"
using namespace spt;

uint32 spt::SptMsInt::MsCnt32()
{
	uint32 cnt;
	volatile uint32& pcnt = msCnt32;
	do
	{
		cnt = pcnt;
	} while (cnt != pcnt);
	return cnt;
}

uint64 spt::SptMsInt::MsCnt64()
{
	uint64 cnt;
	volatile uint64& pcnt = msCnt64;
	do
	{
		cnt = pcnt;
	} while (cnt != pcnt);
	return cnt;
}

uint32 spt::SptMsInt::PowerUpMsCnt32()
{
	uint32 cnt;
	volatile uint32& pcnt = powerUpCnt32;
	do
	{
		cnt = pcnt;
	} while (cnt != pcnt);
	return cnt;
}

uint64 spt::SptMsInt::PowerUpMsCnt64()
{
	uint64 cnt;
	volatile uint64& pcnt = powerUpCnt64;
	do
	{
		cnt = pcnt;
	} while (cnt != pcnt);
	return cnt;
}

SptMsInt& spt::SptMsInt::Instance()
{
	static SptMsInt inst;
	return inst;
}

extern "C" void MsInt()
{
	SptMsInt::Instance().Interrupt();
}

void spt::SptMsInt::PowerUpIni(int32 Para)
{
	if (Para == 0)
	{
		SetMsInt(MsInt, 1);
	}
	else if (Para == 1)
	{
#ifdef WIN32_SIM
		SetMsNormalInt(MsInt, 1);
#else 
		SetMsInt(MsInt, 1);
#endif // WIN32_SIM
	}
}

void spt::SptMsInt::Interrupt()
{
	msCnt32++;
	msCnt64++;
	if (powerUpCnt32 < (uint32)0x80000000)
	{
		powerUpCnt32++;
	}
	if (powerUpCnt64 < (uint64)0x8000000000000000)
	{
		powerUpCnt64++;
	}
#ifndef GZK_LCD
	SptSampAppTaskScheduler::Instance().PostSem();
	DateTask::Instance().UpdateTimeInMsInt();
#endif

}
