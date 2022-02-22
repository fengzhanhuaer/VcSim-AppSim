#ifndef HMIDIALOG_H
#define HMIDIALOG_H

namespace spt
{
	class HmiWidDialog :public WidRect
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
		virtual void AutoLayout();
	protected:

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
		virtual int32 ShowSelf();
	protected:
		WidTextLine title[5];
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
		virtual int32 ShowSelf();
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
		//return 0 编辑正常
		//return -1 ESC退出
		//return -2 强制退出
		virtual int32 Edit();
		const char* InputStr();
	protected:
		virtual int32 ShowSelf();
	protected:
		E_Mode mode;
		uint8 maxTextLine;
		uint32 inputMaxLen;
		String100B inputStr;
		WidTextLineRect input;
		WidTextLine text[6];
		WidCurseTextLine curse;
	};
	class HmiStrEditDialog :public HmiWidDialog
	{
	public:
		void SetTitle(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5);
		void SetText(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5);
		void SetEditAble(bool8 EditAble1, bool8 EditAble2, bool8 EditAble3, bool8 EditAble4, bool8 EditAble5);
		void SetMaxInputLen(uint32 Len);
		//return 0 编辑正常
		//return -1 ESC退出
		//return -2 强制退出
		virtual int32 Edit();
		virtual void AutoLayout();
		const char* InputStr(uint32 Index);
	protected:
		virtual int32 ShowSelf();
	protected:
		uint32 titleMaxLen;
		uint32 inputMaxLen;
		WidTextLine title[5];
		WidTextLine text[5];
	};
	class HmiIntDataEditDialog :public HmiWidDialog
	{
	public:
		virtual void AutoLayout();
	protected:
		virtual int32 ShowSelf();
	protected:
		uint32 titleMaxLen;
		uint32 inputMaxLen;
		uint8 selectIndex;
		uint8 dataNum;
		WidTextLine title[3];
		WidTextLine text[3];
		WidTextLine titleMid;
		WidCurseTextLine curse;
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
		virtual int32 ShowSelf();
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
		virtual int32 ShowSelf();
	protected:
		SalBitDes* Des;
		uint8 BitNum;
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
		virtual int32 ShowSelf();
		void UpdateDate();
	protected:
		SalRtc rtc;
		SalDateStamp date;
		uint32 titleMaxLen;
		uint32 inputMaxLen;
		uint8 selectIndex;
		uint8 dataNum;
		WidTextLine title[7];
		WidTextLine text[7];
		WidDataLine data[7];
		WidCurseTextLine curse;
	};
}

#endif // !HMIDIALOG_H
