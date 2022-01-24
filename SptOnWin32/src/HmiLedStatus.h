#ifndef HMILEDSTATUS_H
#define HMILEDSTATUS_H

namespace spt
{
	class HmiLedGroup :public InstObjectGroup
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint16 ElementNum);
		void SaveFile();
		//是否有变位，与Buf对比
		bool8 GetValue(uint8* Buf, uint16 BufLen);
		void SetValue(uint16 Index, bool8 HoldOn, uint8 Val);
	public:
		class HmiLed* GetObject(uint16 InstId);
		bool8 isChange;
		ArrayBuf buf;
	};
	class HmiLed :public InstObject
	{
	public:
		enum Color
		{
			E_NULL,//无色
			E_RED,//红色
			E_GREEN,//绿色
			E_YELLOW//黄色
		};
	public:
		void PowerUpIni(const char* Name, const char* DesName, HmiLedGroup* Group, Color color, uint8 Col, uint8 Row, bool8 HoldOn);
		uint16 GetColor() { return (uint16)cor; }
		uint8 GetVal() { return val; }
		uint8 GetRow() { return row; }
		uint8 GetCol() { return col; }
		bool8 blSignalForce() { return blsignalForce; };
		bool8 blSignalForce(bool8 Flag) { return blsignalForce = Flag; };
		void SetValue(uint8 Val);
		void ForceSetValue(uint8 Val);
		uint8 Value();
		bool8 IsHoldOn() { return holdOn; };
	protected:
		virtual void SaveIds(void* Ele);
	protected:
		bool8 blsignalForce;
		Color cor;
		uint8 val;
		uint8 row;
		uint8 col;
		bool8 holdOn;
	};
}

#endif // !HMILEDSTATUS_H

