#ifndef HMISTATUSBAR_H
#define HMISTATUSBAR_H

namespace spt
{
	class HmiStatusBar :public HmiWidRect
	{
	public:
		M_Singleton(HmiStatusBar);
	public:
		int32 Show();
		/// <summary>
		/// ÉèÖÃ´æ´¢×èÈû²ÎÊý
		/// </summary>
		void SetSaveBlockPara(uint32 LowLimit = 80, uint32 HighLimit = 2000) { saveLowLimit = LowLimit; saveHighLimit = HighLimit; };
	protected:
		uint32 saveLowLimit;
		uint32 saveHighLimit;
	protected:
		HmiStatusBar();
		void UpdateHmiLedInfo();
		int64 lastSec;
		MsPeriodTimer updateTimer;
		MsPeriodTimer updateHmiLedTimer;
		ArrayBuf hmiLedOldStatus;
	private:
		HmiLedGroup* hmiLedGroup;
	};
}

#endif // !HMISTATUSBAR_H


