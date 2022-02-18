#ifndef HMISTATUSBAR_H
#define HMISTATUSBAR_H

namespace spt
{
	class HmiStatusBar :public WidRect
	{
	public:
		M_Singleton(HmiStatusBar);
	public:
		void Show();
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
		MsTimer updateTimer;
		MsTimer updateHmiLedTimer;
		ArrayBuf hmiLedOldStatus;
	private:
		HmiLedGroup* hmiLedGroup;
	};
}

#endif // !HMISTATUSBAR_H


