#ifndef APIHMILED_H
#define APIHMILED_H

namespace spt
{
	class ApiHmiLedGroup :protected HmiLedGroup
	{
	public:
		//Name,����
		//DesName,�̵�ַ
		//LedNum��ָʾ�Ƹ���
		void PowerUpIni(const char* Name, const char* DesName, uint16 LedNum);
	};
	class ApiHmiLed :protected HmiLed
	{
	public:
		//Name,����
		//DesName,�̵�ַ
		//Group,ָʾ�����������
		//color,ָʾ�Ƶ���ɫ
		//Col,ָʾ�����ڵ���
		//Row,ָʾ�����ڵ���
		//HoldOn,ָʾ���Ƿ���籣��
		void PowerUpIni(const char* Name, const char* DesName, ApiHmiLedGroup& Group, Color color, uint8 Col, uint8 Row, bool8 HoldOn);
		void SetValue(uint8 Val);
		uint8 Value();
	};
}

#endif // !APIHMILED_H
