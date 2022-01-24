#include "ApiProject.h"
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

bool8 spt::SptMsInt::IsPowerUpOver(uint32 TimeMs)
{
	return TimeMs <= msCnt64;
}

SptMsInt& spt::SptMsInt::Instance()
{
	static SptMsInt inst;
	return inst;
}

static void MsInt()
{
	SptMsInt::Instance().Interrupt();
}

static void Gzk35kVIntProc()
{

}
static void GzkSauIntProc()
{

}

void spt::SptMsInt::PowerUpIni(int32 Para)
{
	const struct ApiAppCfg* cfg = SptMain::Instance().AppCfg();
#ifndef GZK_LCD
	if (cfg)
	{
		if (cfg->platform.hardware == EH_GZK35KVP
			|| cfg->platform.hardware == EH_GZK35KVSMART
			)
		{
			intData.func = Gzk35kVIntProc;
			intData.Enable = 1;
		}
		else if (cfg->platform.hardware == EH_GZKSAU
			)
		{
			intData.func = GzkSauIntProc;
			intData.Enable = 1;
		}
	}
	else
#endif
		if (0)
		{
			if (Para == 0)
			{
				SetMsInt(MsInt, 1);
			}
			else if (Para == 1)
			{
				SetMsNormalInt(MsInt, 1);
			}
		}

}

void spt::SptMsInt::Interrupt()
{
	msCnt32++;
	msCnt64++;
	if (intData.Enable)
	{
		intData.func();
	}
}
