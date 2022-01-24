#ifndef HMIDIALOG_H
#define HMIDIALOG_H

namespace spt
{
	class HmiWidDialog :public HmiWidRect
	{
	public:
		enum EditRetValue
		{
			E_OK = 0,//正常
			E_ESC = -1,//ESC退出
			E_FORCE_ESC = -2,//强制退出
		};
	public:
		HmiWidDialog();
		virtual int32 EditSelf(HmiKeyMsg key);
		virtual void AutoLayout();
	protected:
		uint32 lineCount;
		uint32 lineWidth;
	};
	class HmiInfoDialog :public HmiWidDialog
	{
	public:
		void SetTitle(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5);
		void SetTitle(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5, const char* Last);
		virtual void AutoLayout();
		//return 0 编辑正常
		//return -1 ESC退出
		//return -2 强制退出
		virtual int32 Edit();
	protected:
		HmiWidTextLine title[5];
	};
	class HmiWarnDialog :public HmiInfoDialog
	{
	public:
		void SetTitle(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5);
		//return 0 编辑正常
		//return -1 ESC退出
		//return -2 强制退出
		virtual int32 Edit();
	protected:

	};
	class HmiSelectDialog :public HmiWarnDialog
	{
	public:
		void SetTitle(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5);
		//return 0 编辑正常
		//return -1 ESC退出
		//return -2 强制退出
		virtual int32 Edit();
	protected:

	};
	class HmiAssicInputDialog :public HmiWidDialog
	{
	public:
		enum E_Mode
		{
			E_Full,//全键盘
			E_HEX,
			E_Number,
		};
	public:
		virtual void AutoLayout();
		HmiAssicInputDialog(E_Mode Mode);
		void SetMaxInputLen(uint32 Len);
		void SetDefault(const char* Def);
		virtual void Show(ShowType Type);
		//return 0 编辑正常
		//return -1 ESC退出
		//return -2 强制退出
		virtual int32 Edit();
		const char* InputStr();
	protected:
		E_Mode mode;
		uint8 maxTextLine;
		uint32 inputMaxLen;
		String100B inputStr;
		HmiWidTextRect input;
		HmiWidTextLine text[6];
		HmiWidCurseText curse;
	};
	class HmiStrEditDialog :public HmiWidDialog
	{
	public:
		void SetTitle(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5);
		void SetText(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5);
		void SetEditAble(bool8 EditAble1, bool8 EditAble2, bool8 EditAble3, bool8 EditAble4, bool8 EditAble5);
		virtual void Show(ShowType Type);
		void SetMaxInputLen(uint32 Len);
		//return 0 编辑正常
		//return -1 ESC退出
		//return -2 强制退出
		virtual int32 Edit();
		virtual void AutoLayout();
		const char* InputStr(uint32 Index);
	protected:
		uint32 titleMaxLen;
		uint32 inputMaxLen;
		HmiWidTextLine title[5];
		HmiWidTextLine text[5];
	};
	class HmiIntDataEditDialog :public HmiWidDialog
	{
	public:
		virtual void AutoLayout();
	protected:
		uint32 titleMaxLen;
		uint32 inputMaxLen;
		uint8 selectIndex;
		uint8 dataNum;
		HmiWidTextLine title[3];
		HmiWidTextLine text[3];
		HmiWidTextLine titleMid;
		HmiWidCurseText curse;
	};
	class HmiInt32DataDialog :public HmiIntDataEditDialog
	{
	public:
		//return 0 编辑正常
		//return -1 ESC退出
		//return -2 强制退出
		virtual int32 Edit();
		HmiInt32DataDialog();
		void Set(const char* Title, int32 Min, int32 Def, int32 DotNum, int32 Max);
		int32 Data();
	protected:
		int32 Min;
		int32 Def;
		int32 Cur;
		int32 Max;
		int32 DotNum;
	};
	class HmiUInt32DataDialog :public HmiIntDataEditDialog
	{
	public:
		//return 0 编辑正常
		//return -1 ESC退出
		//return -2 强制退出
		virtual int32 Edit();
		HmiUInt32DataDialog();
		void Set(const char* Title, uint32 Min, uint32 Def, uint32 DotNum, uint32 Max);
		uint32 Data();
	protected:
		uint32 Min;
		uint32 Def;
		uint32 Cur;
		uint32 Max;
		uint32 DotNum;
	};
	class HmiHex32DataDialog :protected HmiUInt32DataDialog
	{
	public:
		//return 0 编辑正常
		//return -1 ESC退出
		//return -2 强制退出
		virtual int32 Edit();
		HmiHex32DataDialog();
		void Set(const char* Title, uint32 Min, uint32 Def, uint32 Max);
		uint32 Data();
	protected:

	};
	class HmiEnum32DataDialog :public HmiHex32DataDialog
	{
	public:
		//return 0 编辑正常
		//return -1 ESC退出
		//return -2 强制退出
		virtual int32 Edit();
		HmiEnum32DataDialog();
		void Set(const char* Title, uint32 Min, uint32 Def, uint32 Max, SalEnumDes* Des);
	protected:
		SalEnumDes* Des;
	};
	class HmiBit32DataDialog :public HmiHex32DataDialog
	{
	public:
		//return 0 编辑正常
		//return -1 ESC退出
		//return -2 强制退出
		virtual int32 Edit();
		HmiBit32DataDialog();
		void Set(const char* Title, uint32 Min, uint32 Def, uint32 Max, SalBitDes* Des, uint8 BitLen);
	protected:
		SalBitDes* Des;
	};
	class HmiTimeEditDialog :public HmiWidDialog
	{
	public:
		//return 0 编辑正常
		//return -1 ESC退出
		//return -2 强制退出
		virtual int32 Edit();
		void SetDefaultDate(SalDateStamp& Date);
		void SetTitle(const char* Str1);
		virtual void AutoLayout();
		HmiTimeEditDialog();
	protected:
		void UpdateDate();
	protected:
		SalRtc rtc;
		SalDateStamp date;
		uint32 titleMaxLen;
		uint32 inputMaxLen;
		uint8 selectIndex;
		uint8 dataNum;
		HmiWidTextLine title[7];
		HmiWidTextLine text[7];
		HmiWidDataLine data[7];
		HmiWidCurseText curse;
	};
}

#endif // !HMIDIALOG_H
