#include "SptProject.h"
using namespace spt;

bool8 spt::SptFlags::IsPowerDownAtRange(uint32 LowLimit, uint32 HighLimit) const
{
	if (powerDownFlags)
	{
		uint32 ms = SptMsInt::Instance().MsCnt32() - powerDownStartEdgeMs;
		if ((ms <= HighLimit) && (ms >= LowLimit))
		{
			return 1;
		}
	}
	return 0;
}

void spt::SptFlags::SptFlagProcess()
{
	uint8 flag = 0;
	SptGetHwVal(E_HPT_PowerUp, &flag, sizeof(flag));
	if (msPowerDownDelayTimer.IsEnable())
	{
		if (msPowerDownDelayTimer.Status(flag))
		{
			if (!powerDownFlags)
			{
				powerDownStartEdgeMs = msPowerDownDelayTimer.UpEdge();
			}
			powerDownFlags = 1;
		}
		else
		{
			powerDownFlags = 0;
		}
	}
	else
	{
		msPowerDownDelayTimer.SetCnt(20, 5);
		msPowerDownDelayTimer.Enable(1);
	}
}
