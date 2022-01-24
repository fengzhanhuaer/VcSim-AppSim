#ifndef HMILEDSTATUS_H
#define HMILEDSTATUS_H

namespace spt
{
	class HmiLedGroup :public InstObjectGroup
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint16 ElementNum);
	public:
		class HmiLed* GetObject(uint16 InstId);

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
		void PowerUpIni(const char* Name, const char* DesName, HmiLedGroup* Group, Color color, uint8 Col, uint8 Row);
		uint16 GetColor() { return cor; }
		uint8 GetVal() { return val; }
		uint8 GetRow() { return row; }
		uint8 GetCol() { return col; }
	protected:
		Color cor;
		uint8 val;
		uint8 row;
		uint8 col;
	};


	class Hmi
	{

	};
}

#endif // !HMILEDSTATUS_H

