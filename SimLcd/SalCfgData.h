#ifndef SALCFGDATA_H
#define SALCFGDATA_H

namespace spt
{
	class CfgDataBase
	{
	public:
		enum CfgDataType
		{
			E_Normal,
			E_STRING,
			E_IP,
			E_MAC,
		};
	public:
		void SetRange(int64 Min, int64 Max);
		const char* Name();
		const char* Notes();
		virtual void DataStr(SalString& Str);
		void SetName(const char* Name);
		void SetNotes(const char* Notes);
		void Set(const char* Name, const char* Notes, int64 Default);
		virtual bool8 Save2File(class CfgFile& file);
		virtual bool8 ReadFromFile(class CfgFile& file);
		virtual bool8 ValueToEditBuf();
		virtual bool8 EditBufToValue();
		int64 Max() { return max; };
		int64 Min() { return min; };
		st64value& Value() { return value; };
		st64value& EditValue() { return editValue; };
		uint8 CfgType() { return type; };
		uint8 DotNum() { return dotNum; };
		uint8 SetDotNum(uint8 DotNum) { return dotNum = DotNum; };
		/// <summary>
		/// 是否已经初始化
		/// </summary>
		/// <returns></returns>
		bool8 SetDefault(int64 Value, bool8 Force);
		virtual void ApplyDefault();
	protected:
		CfgDataBase();
	protected:
		bool8 isSetDefault;
		uint8 dotNum;
		uint8 type;
		char name[40];
		char notes[100];
		st64value value;
		st64value editValue;
		st64value defValue;
		int64 max;
		int64 min;
	};
	class CfgStr :public CfgDataBase
	{
	public:
		void DataStr(SalString& Str);
		char* StrData();
		int32 StrDataBufLen();
		void SetData(const char* DataStr);
		void Set(const char* Name, const char* Notes, const char* Default);
		bool8 SetDefault(const char* Value, bool8 Force);
		bool8 ReadFromFile(CfgFile& file);
		virtual void ApplyDefault();
		CfgStr();
	protected:
		char data[100];
		char defdata[100];

	};
	class CfgUint32 :public CfgDataBase
	{
	public:
		CfgUint32();
		virtual void DataStr(SalString& Str);
		bool8 SetData(uint32 Data);
		virtual bool8 ReadFromFile(class CfgFile& file);
		uint32 Data()const;
	protected:

	};
	class CfgHex32 :public CfgDataBase
	{
	public:
		CfgHex32();
		virtual void DataStr(SalString& Str);
		void SetData(uint32 Data);
		virtual bool8 ReadFromFile(class CfgFile& file);
		uint32 Data()const;
	protected:

	};
	class CfgInt32 :public CfgDataBase
	{
	public:
		CfgInt32();
		virtual void DataStr(SalString& Str);
		bool8 SetData(int32 Data);
		virtual bool8 ReadFromFile(class CfgFile& file);
		int32 Data()const;
	protected:

	};
	class CfgBool :public CfgDataBase
	{
	public:
		CfgBool();
		virtual void DataStr(SalString& Str);
		void SetData(bool8 Data);
		virtual bool8 ReadFromFile(class CfgFile& file);
		bool8 Data()const;
	protected:

	};
	class CfgIp :public CfgDataBase
	{
	public:
		CfgIp();
		virtual void DataStr(SalString& Str);
		void SetData(uint32 Data);
		void SetData(uint32 Data1, uint32 Data2, uint32 Data3, uint32 Data4);
		void Set(const char* Name, uint32 Data);
		virtual bool8 ReadFromFile(class CfgFile& file);
		uint32 Data()const;
	protected:

	};
	class CfgMac :public CfgDataBase
	{
	public:
		CfgMac();
		virtual void DataStr(SalString& Str);
		void SetData(uint8 Data1, uint8 Data2, uint8 Data3, uint8 Data4, uint8 Data5, uint8 Data6);
		void Set(const char* Name, uint8 Data1, uint8 Data2, uint8 Data3, uint8 Data4, uint8 Data5, uint8 Data6);
		virtual bool8 ReadFromFile(class CfgFile& file);
		void Data(uint8& Data1, uint8& Data2, uint8& Data3, uint8& Data4, uint8& Data5, uint8& Data6)const;
	protected:

	};

}


#endif // !SALCFGDATA_H

