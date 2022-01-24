#ifndef SALTIMER_H
#define SALTIMER_H

namespace spt
{
	//MS计时器
	class MsTimer
	{
	public:
		static const uint32 Mt1Ms = 1;
		static const uint32 Mt1Second = 1000 * Mt1Ms;
		static const uint32 Mt1Minute = 60 * Mt1Second;
		static const uint32 Mt1Hour = 60 * Mt1Minute;
		static const uint32 Mt1Day = 24 * Mt1Hour;
	public:
		MsTimer();
		uint32 UpCnt(uint32 Uc);
		uint32 UpCnt() { return upCnt; }
		bool8 Enable(bool8 En);
		bool8 IsEnable();
		bool8 IsStart();
		virtual bool8 Status();
		void Reset();
		void Restart();
		static uint32 MsCntNow();
	protected:
		uint32 upEdge;
		uint32 upCnt;
		bool8 status;
		bool8 started;
		bool8 enable;
	};
	//周期脉冲器
	class MsPeriodTimer :public MsTimer
	{
	public:
		virtual bool8 Status();
	};
	//时间戳继电器
	class MsStampTimer :protected MsTimer
	{
	public:
		MsStampTimer();
		void StartTimer();
		bool8 Enable(bool8 En);
		bool8 IsEnable();
		bool8 Status(uint32 UpCnt);
	protected:

	};
	//输入延迟继电器
	class MsDelayTimer :public MsTimer
	{
	public:
		void SetCnt(uint32 UpC, uint32 DownC);
		uint32 DownCnt(uint32 Dn);
		uint32 DownCnt() { return downCnt; }
		bool8 Status(bool8 Value);
		uint32 UpEdge()const { return upEdge; }
		uint32 DownEdge()const { return downEdge; }
	protected:
		uint32 downEdge;
		uint32 downCnt;
		bool8 upStart;
		bool8 downStart;
	};

}

#endif // !SALTIMER_H

