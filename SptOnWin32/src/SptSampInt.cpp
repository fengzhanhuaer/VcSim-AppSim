#include "ApiProject.h"
using namespace spt;

uint32 spt::SptSampInt::PeriodUs()
{
	return periodUs;
}

uint32 spt::SptSampInt::Cnt32()
{
	uint32 cnt;
	volatile uint32& pcnt = msCnt32;
	do
	{
		cnt = pcnt;
	} while (cnt != pcnt);
	return cnt;
}

uint64 spt::SptSampInt::Cnt64()
{
	uint64 cnt;
	volatile uint64& pcnt = msCnt64;
	do
	{
		cnt = pcnt;
	} while (cnt != pcnt);
	return cnt;
}
SptSampInt& spt::SptSampInt::Instance()
{
	static SptSampInt inst;
	return inst;
}
static void GzkMsSampIntPerInt()
{
	SptMsInt::Instance().Interrupt();
}
static void GzkMsSampIntPer4Int()
{
	static uint8 cnt = 0;
	cnt++;
	if (cnt >= 4)
	{
		cnt = 0;
		SptMsInt::Instance().Interrupt();
	}
}
static void SampInt()
{
	SptSampInt::Instance().Interrupt();
}
void spt::SptSampInt::PowerUpIni(int32 MsIntType)
{
	SptDateTask::Instance().ForceGetRtcFromHw();
	const struct ApiAppCfg* cfg = SptMain::Instance().AppCfg();
	if (cfg)
	{
		if (cfg->platform.hardware == EH_GZK35KVP
			|| cfg->platform.hardware == EH_GZK35KVSMART
			)
		{
			periodUs = 1000;
			intData.func = GzkMsSampIntPerInt;
			intData.Enable = 1;
			SetSampInt(SampInt, 1, periodUs);
		}
		else if (cfg->platform.hardware == EH_GZKSAU
			)
		{
			periodUs = 250;
			intData.func = GzkMsSampIntPer4Int;
			intData.Enable = 1;
			SetSampInt(SampInt, 1, periodUs);
		}
		else
		{
			intData.func = 0;
			intData.Enable = 0;
		}
	}
}

void spt::SptSampInt::Interrupt()
{
	msCnt32++;
	msCnt64++;
	if (intData.Enable)
	{
		intData.func();
	}
	SptSampAppTaskScheduler::Instance().PostSem();
}
