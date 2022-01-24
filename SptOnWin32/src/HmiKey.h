#ifndef HMIKEY_H
#define HMIKEY_H

namespace spt
{
	//键值1含义状态
	enum E_KEY1
	{
		EK1_KEYVALUE = 1,//键值2为键盘值，键值4为控制键
		EK1_ASSIC,//键值2为ASSIC码,键值4为控制键
		EK1_GB2312,//键值2、3为汉字内码,键值4为控制键
	};
	enum E_KEY2
	{
		EK_BACK = 0x08,
		EK_TAB = 0x09,
		EK_ENTER = 0x0D,
		EK_ESC = 0x1B,
		EK_SPACE = 0x20,
		EK_LEFT = 0x25,
		EK_UP = 0x26,
		EK_RIGHT = 0x27,
		EK_DOWN = 0x28,
		EK_A = 0x41,
		EK_B = 0x42,
		EK_C = 0x43,
		EK_D = 0x44,
		EK_E = 0x45,
		EK_F = 0x46,
		EK_D0 = 0x30,
		EK_D1 = 0x31,
		EK_D2 = 0x32,
		EK_D3 = 0x33,
		EK_D4 = 0x34,
		EK_D5 = 0x35,
		EK_D6 = 0x36,
		EK_D7 = 0x37,
		EK_D8 = 0x38,
		EK_D9 = 0x39,
		EK_NUM0 = 0x60,
		EK_NUM1 = 0x61,
		EK_NUM2 = 0x62,
		EK_NUM3 = 0x63,
		EK_NUM4 = 0x64,
		EK_NUM5 = 0x65,
		EK_NUM6 = 0x66,
		EK_NUM7 = 0x67,
		EK_NUM8 = 0x68,
		EK_NUM9 = 0x69,
		EK_ADD = 0x6B,
		EK_SUB = 0x6D,
		EK_DOT = 0x6E,//小数点
		EK_F1 = 0x70,//复归键
		EK_F2 = 0x71,
		EK_F3 = 0x72,
		EK_F4 = 0x73,
		EK_F5 = 0x74,
		EK_F6 = 0x75,
		EK_F7 = 0x76,
		EK_F8 = 0x77,
		EK_F9 = 0x78,
		EK_F10 = 0x79,
		EK_F11 = 0x7A,
		EK_F12 = 0x7B,
		EK_MD_STOP = 0xB3,//停止键，虚拟按键产生此键值
	};
	//键值4含义状态
	enum E_KEY4
	{
		EK_CTRL = 0X01,
		EK_SHIFT = 0X02,
		EK_ALT = 0X04,
	};
	struct HmiKey
	{
		uint8 Key1;
		uint8 Key2;
		uint8 Key3;
		uint8 Key4;
	};
	struct HmiKeyMsg
	{
		HmiKey key;
		bool8 isDealed;
	};
	/// <summary>
	/// 按键服务
	/// </summary>
	class HmiKeyService
	{
	public:
		void Push(HmiKey Key);
		static HmiKeyService& Instance();
		bool8 Pop(HmiKey& Key);
		/// <summary>
		/// 自上次有按键至此时的时间
		/// </summary>
		/// <returns>ms值</returns>
		uint32 SinceLastKeyPutIn();
	protected:
		HmiKeyService();
	protected:
		uint32 lastKeyPutTime;
		uint32 forceEscTime;
		MsTimer escTimer;
		RingBuf keyBuf;
		HmiKey keyrambuf[20];
	};
}

#endif // !HMIKEY_H

