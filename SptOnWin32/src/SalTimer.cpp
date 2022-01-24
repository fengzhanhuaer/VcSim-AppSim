#include"SptProject.h"
using namespace spt;

uint32 spt::MsTimer::UpCnt(uint32 Uc)
{
	return upCnt = Uc;
}

bool8 spt::MsTimer::Enable(bool8 En)
{
	if (En)
	{
		status = 0;
		if (!enable)
		{
			upEdge = MsCntNow();
			started = 1;
		}
		else
		{
			started = 1;
		}
	}
	else
	{
		started = status = 0;
	}
	return enable = En;
}

bool8 spt::MsTimer::IsEnable()
{
	return enable;
}

bool8 spt::MsTimer::IsStart()
{
	return started;
}

bool8 spt::MsTimer::Status()
{
	if (enable)
	{
		if (!started)
		{
			upEdge = MsCntNow();
			status = 0;
			started = 1;
		}
	}
	else
	{
		started = status = 0;
		return status;
	}

	if (!status)
	{
		uint32 delta = MsCntNow() - upEdge;
		if (delta > upCnt)
		{
			status = 1;
		}
	}
	return status;
}

void spt::MsTimer::Reset()
{
	enable = started = status = 0;
}

void spt::MsTimer::Restart()
{
	upEdge = MsCntNow();
	status = 0;
	if (enable)
	{
		started = 1;
	}
}


spt::MsTimer::MsTimer()
{
	upEdge = 0;
	upCnt = (uint32)-1;
	status = 0;
	enable = 0;
	started = 0;
}

uint32 spt::MsTimer::MsCntNow()
{
	return SptMsInt::Instance().MsCnt32();
}

bool8 spt::MsPeriodTimer::Status()
{
	if (enable)
	{
		uint32 now = MsCntNow();
		if (!started)
		{
			upEdge = now;
			status = 0;
			started = 1;
		}
		uint32 delta = now - upEdge;
		if (delta > upCnt)
		{
			status = 1;
			upEdge = now;
		}
		else
		{
			status = 0;
		}
	}
	else
	{
		started = status = 0;
		return status;
	}
	return status;
}

spt::MsStampTimer::MsStampTimer()
{
	StartTimer();
}

void spt::MsStampTimer::StartTimer()
{
	upEdge = MsCntNow();
}

bool8 spt::MsStampTimer::Enable(bool8 En)
{
	return MsTimer::Enable(En);
}

bool8 spt::MsStampTimer::IsEnable()
{
	return MsTimer::IsEnable();
}

bool8 spt::MsStampTimer::Status(uint32 UpCnt)
{
	if (enable)
	{
		uint32 delta = MsCntNow() - upEdge;
		if (delta >= UpCnt)
		{
			return 1;
		}
	}
	return 0;
}

void spt::MsDelayTimer::SetCnt(uint32 UpC, uint32 DownC)
{
	UpCnt(UpC);
	DownCnt(DownC);
}

uint32 spt::MsDelayTimer::DownCnt(uint32 Dn)
{
	return  downCnt = Dn;
}

bool8 spt::MsDelayTimer::Status(bool8 Value)
{
	if (enable)
	{
		uint32 now = MsCntNow();
		if (status)
		{
			if (Value == 1)
			{
				downStart = 0;
			}
			else if (downStart)
			{
				uint32 delta = now - downEdge;
				if (delta > downCnt)
				{
					status = 0;
					downStart = 0;
					upStart = 0;
				}
			}
			else
			{
				downEdge = now;
				downStart = 1;
			}
		}
		else
		{
			if (1 != Value)
			{
				upStart = 0;
			}
			else if (upStart)
			{
				uint32 delta = now - upEdge;
				if (delta > upCnt)
				{
					status = 1;
					downStart = 0;
					upStart = 0;
				}
			}
			else
			{
				upEdge = now;
				upStart = 1;
			}
		}
	}
	else
	{
		started = status = 0;
	}
	return status;
}
