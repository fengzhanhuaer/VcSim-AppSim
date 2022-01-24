#ifndef APIHMILED_H
#define APIHMILED_H

namespace spt
{
	class ApiHmiLedGroup :protected HmiLedGroup
	{
	public:
		//Name,名称
		//DesName,短地址
		//LedNum，指示灯个数
		void PowerUpIni(const char* Name, const char* DesName, uint16 LedNum);
	};
	class ApiHmiLed :protected HmiLed
	{
	public:
		//Name,名称
		//DesName,短地址
		//Group,指示灯所属的组号
		//color,指示灯的颜色
		//Col,指示灯所在的列
		//Row,指示灯所在的行
		//HoldOn,指示灯是否掉电保存
		void PowerUpIni(const char* Name, const char* DesName, ApiHmiLedGroup& Group, Color color, uint8 Col, uint8 Row, bool8 HoldOn);
		void SetValue(uint8 Val);
		uint8 Value();
	};
}

#endif // !APIHMILED_H
