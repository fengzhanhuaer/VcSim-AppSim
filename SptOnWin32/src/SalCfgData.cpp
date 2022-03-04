#include"SalProject.h"
using namespace spt;

void spt::CfgDataBase::SetRange(int64 Min, int64 Max)
{
	min = Min;
	max = Max;
}

const char* spt::CfgDataBase::Name()
{
	return name;
}

const char* spt::CfgDataBase::Notes()
{
	return notes;
}

void spt::CfgDataBase::DataStr(SalString& Str)
{
	Str = "";
}

void spt::CfgDataBase::SetName(const char* Name)
{
	StrNCpy(name, Name, sizeof(name));
}

void spt::CfgDataBase::SetNotes(const char* Notes)
{
	StrNCpy(notes, Notes, sizeof(notes));
}

bool8 spt::CfgDataBase::Save2File(CfgFile& file)
{
	int32 res = file.Write(name);
	if (res <= 0)
	{
		return 0;
	}
	res = file.Write("=");
	String200B str;
	DataStr(str);
	res = file.Write(str.Str());
	if (unit && (unit != &Unit_NULL))
	{
		res = file.Write(" ///");
		res = file.Write(unit->toString());
	}
	if (notes[0])
	{
		res = file.Write(" ///");
		res = file.Write(notes);
	}
	file.WriteLine("");
	return 1;
}

bool8 spt::CfgDataBase::ReadFromFile(CfgFile& file)
{
	return 1;
}

bool8 spt::CfgDataBase::ValueToEditBuf()
{
	editValue = value;
	return 1;
}

bool8 spt::CfgDataBase::EditBufToValue()
{
	value.value.u64 = editValue.value.u64;
	return 1;
}

const char* spt::CfgDataBase::Unit()
{
	if (unit)
	{
		return unit->toString();
	}
	return Unit_NULL.toString();
}

bool8 spt::CfgDataBase::SetDefaulted()
{
	return isDefaulted = 1;
}

spt::CfgDataBase::CfgDataBase()
{
	name[0] = 0;
	notes[0] = 0;
	unit = &Unit_NULL;
	dotNum = 0;
	isDefaulted = 0;
}

void spt::CfgStrDataBase::DataStr(SalString& Str)
{
	Str = StrData();
}

char* spt::CfgStrDataBase::StrData()
{
	return 0;
}

int32 spt::CfgStrDataBase::StrDataBufLen()
{
	return 0;
}

void spt::CfgStrDataBase::SetData(const char* DataStr)
{
	char* buf = StrData();
	if (buf)
	{
		StrNCpy(buf, DataStr, StrDataBufLen());
	}
}

void spt::CfgStrDataBase::Set(const char* Name, const char* DataStr)
{
	SetName(Name);
	SetData(DataStr);
}

void spt::CfgStrDataBase::SetIfNoDefault(const char* Name, const char* Data)
{
	SetName(Name);
	if (!isDefaulted)
	{
		SetData(Data);
		isDefaulted = 1;
	}
}

bool8 spt::CfgStrDataBase::ReadFromFile(CfgFile& file)
{
	return file.Get(*this);
}

spt::CfgStrDataBase::CfgStrDataBase()
{
	value.valueType = E_SVT_STR | E_SVT_PTR;
	value.value.str = StrData();
	type = E_STRING;
}

spt::CfgUint32::CfgUint32()
{
	type = E_Normal;
	value.valueType = E_SVT_U32;
	min = 0;
	max = (uint32)-1;
}

void spt::CfgUint32::DataStr(SalString& Str)
{
	Str.Clear();
	Str << (uint32)value.value.u32;
}

bool8 spt::CfgUint32::SetData(uint32 Data)
{
	if ((Data < Min()) || Data > Max())
	{
		return 0;
	}
	value.value.u32 = Data;
	return 1;
}

void spt::CfgUint32::Set(const char* Name, uint32 Data)
{
	SetName(Name);
	SetData(Data);
}

void spt::CfgUint32::SetIfNoDefault(const char* Name, uint32 Data)
{
	SetName(Name);
	if (!isDefaulted)
	{
		SetData(Data);
		isDefaulted = 1;
	}
}

bool8 spt::CfgUint32::ReadFromFile(CfgFile& file)
{
	uint32 dat = 0;
	bool8 res = file.Get(name, dat);
	SetData(dat);
	return bool8(res);
}

uint32 spt::CfgUint32::Data()const
{
	return value.value.u32;
}

spt::CfgInt32::CfgInt32()
{
	type = E_Normal;
	value.valueType = E_SVT_I32;
	max = 0x7fffffff;
	min = (int32)0x80000000;

}
void spt::CfgInt32::DataStr(SalString& Str)
{
	Str.Clear();
	Str << value.value.i32;
}

bool8 spt::CfgInt32::SetData(int32 Data)
{
	if ((Data < min) || Data > max)
	{
		return 0;
	}
	value.value.i32 = Data;
	return 1;
}

void spt::CfgInt32::Set(const char* Name, int32 Data)
{
	SetName(Name);
	SetData(Data);
}

void spt::CfgInt32::SetIfNoDefault(const char* Name, uint32 Data)
{
	SetName(Name);
	if (!isDefaulted)
	{
		SetData(Data);
		isDefaulted = 1;
	}
}

bool8 spt::CfgInt32::ReadFromFile(CfgFile& file)
{
	int32 dat = 0;
	bool8 res = file.Get(name, dat);
	SetData(dat);
	return bool8(res);
}

int32 spt::CfgInt32::Data()const
{
	return value.value.i32;
}

spt::CfgBool::CfgBool()
{
	type = E_Normal;
	value.valueType = E_SVT_BOOL;
	max = 1;
	min = 0;
}

void spt::CfgBool::DataStr(SalString& Str)
{
	Str.Clear();
	Str << value.value.bl;
}

void spt::CfgBool::SetData(bool8 Data)
{
	value.value.bl = (Data == 1);
}

void spt::CfgBool::Set(const char* Name, bool8 Data)
{
	SetName(Name);
	SetData(Data);
}

void spt::CfgBool::SetIfNoDefault(const char* Name, uint32 Data)
{
	SetName(Name);
	if (!isDefaulted)
	{
		SetData(Data);
		isDefaulted = 1;
	}
}

bool8 spt::CfgBool::ReadFromFile(CfgFile& file)
{
	bool8 res = file.Get(name, value.value.bl);
	return bool8(res);
}

bool8 spt::CfgBool::Data()const
{
	return value.value.bl == 1;
}

spt::CfgIp::CfgIp()
{
	type = E_IP;
}

void spt::CfgIp::DataStr(SalString& Str)
{
	Str.Clear();
	Str << value.value.u8bytes.u8[0] << "." << value.value.u8bytes.u8[1] << "." << value.value.u8bytes.u8[2] << "." << value.value.u8bytes.u8[3];
}

void spt::CfgIp::SetData(uint32 Data)
{
	value.value.u8bytes.u8[0] = Data;
	value.value.u8bytes.u8[1] = Data >> 8;
	value.value.u8bytes.u8[2] = Data >> 16;
	value.value.u8bytes.u8[3] = Data >> 24;
}

void spt::CfgIp::SetData(uint32 Data1, uint32 Data2, uint32 Data3, uint32 Data4)
{
	value.value.u8bytes.u8[0] = Data1;
	value.value.u8bytes.u8[1] = Data2;
	value.value.u8bytes.u8[2] = Data3;
	value.value.u8bytes.u8[3] = Data4;
}

void spt::CfgIp::Set(const char* Name, uint32 Data)
{
	SetName(Name);
	SetData(Data);
}

bool8 spt::CfgIp::ReadFromFile(CfgFile& file)
{
	char buf[20];
	bool8 res = file.Get(name, buf, sizeof(buf));
	value.value.u8bytes.u32[0] = InetAddr(buf);
	return res;
}

uint32 spt::CfgIp::Data() const
{
	return  value.value.u8bytes.u32[0];
}
spt::CfgMac::CfgMac()
{
	type = E_MAC;
}
void spt::CfgMac::DataStr(SalString& Str)
{
	Str.Clear();
	Str << value.value.u8bytes.u8[0] << ":";
	Str << value.value.u8bytes.u8[1] << ":";
	Str << value.value.u8bytes.u8[2] << ":";
	Str << value.value.u8bytes.u8[3] << ":";
	Str << value.value.u8bytes.u8[4] << ":";
	Str << value.value.u8bytes.u8[5];
}

void spt::CfgMac::SetData(uint8 Data1, uint8 Data2, uint8 Data3, uint8 Data4, uint8 Data5, uint8 Data6)
{
	value.value.u8bytes.u8[0] = Data1;
	value.value.u8bytes.u8[1] = Data2;
	value.value.u8bytes.u8[2] = Data3;
	value.value.u8bytes.u8[3] = Data4;
	value.value.u8bytes.u8[4] = Data5;
	value.value.u8bytes.u8[5] = Data6;
}

void spt::CfgMac::Set(const char* Name, uint8 Data1, uint8 Data2, uint8 Data3, uint8 Data4, uint8 Data5, uint8 Data6)
{
	SetName(Name);
	value.value.u8bytes.u8[0] = Data1;
	value.value.u8bytes.u8[1] = Data2;
	value.value.u8bytes.u8[2] = Data3;
	value.value.u8bytes.u8[3] = Data4;
	value.value.u8bytes.u8[4] = Data5;
	value.value.u8bytes.u8[5] = Data6;
}

bool8 spt::CfgMac::ReadFromFile(CfgFile& file)
{
	char buf[30];
	bool8 res = file.Get(name, buf, sizeof(buf));

	TransString ts;
	ts.SetBuf(buf);
	uint32 dt;
	ts.Get(dt, ':');
	value.value.u8bytes.u8[0] = dt;
	ts.Get(dt, ':');
	value.value.u8bytes.u8[1] = dt;
	ts.Get(dt, ':');
	value.value.u8bytes.u8[2] = dt;
	ts.Get(dt, ':');
	value.value.u8bytes.u8[3] = dt;
	ts.Get(dt, ':');
	value.value.u8bytes.u8[4] = dt;
	ts.Get(dt, ':');
	value.value.u8bytes.u8[5] = dt;
	return res;
}

void spt::CfgMac::Data(uint8& Data1, uint8& Data2, uint8& Data3, uint8& Data4, uint8& Data5, uint8& Data6) const
{
	Data1 = value.value.u8bytes.u8[0];
	Data2 = value.value.u8bytes.u8[1];
	Data3 = value.value.u8bytes.u8[2];
	Data4 = value.value.u8bytes.u8[3];
	Data5 = value.value.u8bytes.u8[4];
	Data6 = value.value.u8bytes.u8[5];
}

spt::CfgHex32::CfgHex32()
{
	type = E_Normal;
	value.valueType = E_SVT_HEX32;
	min = 0;
	max = (uint32)-1;
}

void spt::CfgHex32::DataStr(SalString& Str)
{
	Str.Clear();
	Str << "0x";
	Str.FormatHex(value.value.u32);
}

void spt::CfgHex32::SetData(uint32 Data)
{
	value.value.u32 = Data;
}

void spt::CfgHex32::Set(const char* Name, uint32 Data)
{
	SetName(Name);
	SetData(Data);
}

void spt::CfgHex32::SetIfNoDefault(const char* Name, uint32 Data)
{
	SetName(Name);
	if (!isDefaulted)
	{
		SetData(Data);
		isDefaulted = 1;
	}
}

bool8 spt::CfgHex32::ReadFromFile(CfgFile& file)
{
	bool8 res = file.GetHex(name, value.value.u32);
	return res;
}

uint32 spt::CfgHex32::Data() const
{
	return value.value.u32;
}

spt::CfgStrData20::CfgStrData20()
{
	value.value.str = data;
}

spt::CfgStrData40::CfgStrData40()
{
	value.value.str = data;
}

spt::CfgStrData60::CfgStrData60()
{
	value.value.str = data;
}
