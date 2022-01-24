#include "SptProject.h"
using namespace spt;

const char Numer2Assic[17] = { "0123456789ABCDEF" };

void spt::SalString::SetBuf(char* Buf, uint32 BufNum)
{
	SingleStackBuf::SetBuf(Buf, 1, BufNum);
}

SalString& spt::SalString::operator<<(const char* Buf)
{
	if (!Buf)
	{
		return *this;
	}
	while (*Buf)
	{
		(*this) << *Buf++;
	}
	return *this;
}

SalString& spt::SalString::operator<<(SalString& String)
{
	return (*this) << String.Str();
}

SalString& spt::SalString::operator<<(const char Flag)
{
	if (top < elementNum)
	{
		bufBase[top++] = Flag;
		if (Flag)
		{
			bufBase[top] = 0;
		}
	}
	return *this;
}
template <typename T>
void UnsignedData2Str(char* Buf, uint32 BufLen, T data)
{
	char buf[50];
	BufLen--;
	if (!BufLen)
	{
		return;
	}
	uint32 i;
	for (i = 0; i < BufLen; i++)
	{
		buf[i] = Numer2Assic[data % 10];

		data = data / 10;

		if (0 == data)
		{
			i++;
			break;
		}
	}
	if (i >= BufLen)
	{
		i = BufLen - 1;
	}
	Buf[i] = 0;
	char* sbuf = Buf;
	char* s = buf + i - 1;
	while (i--)
	{
		*sbuf++ = *s--;
	}
}
template <typename T>
void SignedData2Str(char* Buf, uint32 BufLen, T data)
{
	char buf[50];
	if (data < 0)
	{
		Buf[0] = '-';
		Buf++;
		BufLen--;
		if (!BufLen)
		{
			return;
		}
		data = -data;
	}
	BufLen--;
	if (!BufLen)
	{
		return;
	}
	uint32 i;
	for (i = 0; i < BufLen; i++)
	{
		buf[i] = Numer2Assic[data % 10];
		data = data / 10;
		if (!data)
		{
			i++;
			break;
		}
	}
	if (i == BufLen)
	{
		i = BufLen - 1;
	}
	Buf[i] = 0;
	char* sbuf = Buf;
	char* s = buf + i - 1;
	while (i--)
	{
		*sbuf++ = *s--;
	}
}
SalString& spt::SalString::operator<<(int32 Data)
{
	char buf[20];
	SignedData2Str(buf, sizeof(buf), Data);
	(*this) << buf;
	return *this;
}

SalString& spt::SalString::operator<<(int64 Data)
{
	char buf[20];
	SignedData2Str(buf, sizeof(buf), Data);
	(*this) << buf;
	return *this;
}

SalString& spt::SalString::operator<<(uint32 Data)
{
	char buf[20];
	UnsignedData2Str(buf, sizeof(buf), Data);
	(*this) << buf;
	return *this;
}

SalString& spt::SalString::operator<<(uint64 Data)
{
	char buf[50];
	UnsignedData2Str(buf, sizeof(buf), Data);
	(*this) << buf;
	return *this;
}

SalString& spt::SalString::FormatHex(uint8 Hex)
{
	uint8 b;
	b = (Hex >> 4) & 0x0f;
	(*this) << Numer2Assic[b];
	b = (Hex >> 0) & 0x0f;
	(*this) << Numer2Assic[b];
	return *this;
}

SalString& spt::SalString::FormatHex(uint16 Hex)
{
	uint8 b = Hex >> 12;
	(*this) << Numer2Assic[b];
	b = (Hex >> 8) & 0x0f;
	(*this) << Numer2Assic[b];
	b = (Hex >> 4) & 0x0f;
	(*this) << Numer2Assic[b];
	b = (Hex >> 0) & 0x0f;
	(*this) << Numer2Assic[b];
	return *this;
}

SalString& spt::SalString::FormatHex(uint32 Hex)
{
	uint8 b;
	b = (Hex >> 28) & 0x0f;
	(*this) << Numer2Assic[b];
	b = (Hex >> 24) & 0x0f;
	(*this) << Numer2Assic[b];
	b = (Hex >> 20) & 0x0f;
	(*this) << Numer2Assic[b];
	b = (Hex >> 16) & 0x0f;
	(*this) << Numer2Assic[b];
	b = (Hex >> 12) & 0x0f;
	(*this) << Numer2Assic[b];
	b = (Hex >> 8) & 0x0f;
	(*this) << Numer2Assic[b];
	b = (Hex >> 4) & 0x0f;
	(*this) << Numer2Assic[b];
	b = (Hex >> 0) & 0x0f;
	(*this) << Numer2Assic[b];
	return *this;
}

SalString& spt::SalString::FormatBin(uint8 Hex)
{
	uint32 i = 7;
	do
	{
		(*this) << Numer2Assic[GetBit(Hex, i)];
	} while (i--);
	return *this;
}

SalString& spt::SalString::FormatBin(uint16 Hex)
{
	uint32 i = 15;
	do
	{
		(*this) << Numer2Assic[GetBit(Hex, i)];
	} while (i--);
	return *this;
}

SalString& spt::SalString::FormatBin(uint32 Hex)
{
	uint32 i = 31;
	do
	{
		(*this) << Numer2Assic[GetBit(Hex, i)];
	} while (i--);
	return *this;
}

SalString& spt::SalString::FormatHex(uint64 Hex)
{
	uint32 data;
	data = (uint32)(Hex >> 32);
	FormatHex(data);
	data = (uint32)(Hex);
	FormatHex(data);
	return *this;
}


SalString& spt::SalString::FormatHex(uint8* Hex, uint32 Count)
{
	*this << "{";
	while (Count--)
	{
		*this << "0x";
		FormatHex(*Hex++);
		*this << ",";
	}
	*this << "}";
	return *this;
}

SalString& spt::SalString::FormatHex(uint16* Hex, uint32 Count)
{
	*this << "{";
	while (Count--)
	{
		*this << "0x";
		FormatHex(*Hex++);
		*this << ",";
	}
	*this << "}";
	return *this;
}

SalString& spt::SalString::FormatHex(uint32* Hex, uint32 Count)
{
	*this << "{";
	while (Count--)
	{
		*this << "0x";
		FormatHex(*Hex++);
		*this << ",";
	}
	*this << "}";
	return *this;
}

SalString& spt::SalString::FormatMs(uint64 Data)
{
	uint16 ms = Data % 1000;
	Data = Data / 1000;

	uint16 sec = Data % 60;
	Data = Data / 60;

	uint16 mi = Data % 60;
	Data = Data / 60;

	uint16 hour = Data % 24;
	Data = Data / 24;

	uint64 day = Data;

	this->Format(day, 5, ' ');
	*this << "Ìì";
	this->Format(hour, 2, '0');
	*this << ":";
	this->Format(mi, 2, '0');
	*this << ":";
	this->Format(sec, 2, '0');
	*this << ".";
	this->Format(ms, 3, '0');
	return *this;
}

SalString& spt::SalString::Format(int32 Data, uint8 DotNum)
{
	uint32 dmin = MinUint32DecData(DotNum + 1);
	if (Data < 0)
	{
		*this << '-';
		Data = -Data;
	}
	if (dmin && DotNum)
	{
		uint32 d = Data / dmin;
		*this << d;
		*this << '.';
		d = Data % dmin;
		Format(d, DotNum, '0');
	}
	else
	{
		uint32 d = Data;
		*this << d;
	}
	return *this;
}

SalString& spt::SalString::Format(uint32 Data, uint8 DotNum)
{
	uint32 dmin = MinUint32DecData(DotNum + 1);
	if (dmin && DotNum)
	{
		uint32 d = Data / dmin;
		*this << d;
		*this << '.';
		d = Data % dmin;
		Format(d, DotNum, '0');
	}
	else
	{
		uint32 d = Data;
		*this << d;
	}
	return *this;
}

SalString& spt::SalString::Format(int64 Data, uint8 DotNum)
{
	int64 dmin = MinUint32DecData(DotNum + 1);
	if (Data < 0)
	{
		*this << '-';
		Data = -Data;
	}
	if (dmin && DotNum)
	{
		uint64 d = Data / dmin;
		*this << d;
		*this << '.';
		d = Data % dmin;
		Format(d, DotNum, '0');
	}
	else
	{
		int64 d = Data;
		*this << d;
	}
	return *this;
}

SalString& spt::SalString::Format(uint64 Data, uint8 DotNum)
{
	uint64 dmin = MinUint32DecData(DotNum + 1);
	if (dmin && DotNum)
	{
		uint64 d = Data / dmin;
		*this << d;
		*this << '.';
		d = Data % dmin;
		Format(d, DotNum, '0');
	}
	else
	{
		uint64 d = Data;
		*this << d;
	}
	return *this;
}

SalString& spt::SalString::Format(int32 Data, uint16 Len, uint8 DotNum, char FromLeft, char AddFlag)
{
	String100B str;
	str.Format(Data, DotNum);
	Format(str.Str(), Len, FromLeft, AddFlag);
	return *this;
}

SalString& spt::SalString::Format(uint32 Data, uint16 Len, uint8 DotNum, char FromLeft, char AddFlag)
{
	String100B str;
	str.Format(Data, DotNum);
	Format(str.Str(), Len, FromLeft, AddFlag);
	return *this;
}

SalString& spt::SalString::Format(int64 Data, uint16 Len, uint8 DotNum, char FromLeft, char AddFlag)
{
	String100B str;
	str.Format(Data, DotNum);
	Format(str.Str(), Len, FromLeft, AddFlag);
	return *this;
}

SalString& spt::SalString::Format(uint64 Data, uint16 Len, uint8 DotNum, char FromLeft, char AddFlag)
{
	String100B str;
	str.Format(Data, DotNum);
	Format(str.Str(), Len, FromLeft, AddFlag);
	return *this;
}

SalString& spt::SalString::Format(uint16 Data, uint8 Len, char AddFlag)
{
	char buf[50];
	UnsignedData2Str(buf, sizeof(buf), Data);
	Format(buf, Len, 0, AddFlag);
	return *this;
}

SalString& spt::SalString::Format(int16 Data, uint8 Len, char AddFlag)
{
	char buf[50];
	SignedData2Str(buf, sizeof(buf), Data);
	Format(buf, Len, 0, AddFlag);
	return *this;
}

SalString& spt::SalString::Format(uint32 Data, uint8 Len, char AddFlag)
{
	char buf[50];
	UnsignedData2Str(buf, sizeof(buf), Data);
	Format(buf, Len, 0, AddFlag);
	return *this;
}

SalString& spt::SalString::Format(int32 Data, uint8 Len, char AddFlag)
{
	char buf[50];
	SignedData2Str(buf, sizeof(buf), Data);
	Format(buf, Len, 0, AddFlag);
	return *this;
}

SalString& spt::SalString::Format(uint64 Data, uint8 Len, char AddFlag)
{
	char buf[50];
	UnsignedData2Str(buf, sizeof(buf), Data);
	Format(buf, Len, 0, AddFlag);
	return *this;
}

SalString& spt::SalString::Format(int64 Data, uint8 Len, char AddFlag)
{
	char buf[50];
	UnsignedData2Str(buf, sizeof(buf), Data);
	Format(buf, Len, 0, AddFlag);
	return *this;
}

SalString& spt::SalString::Format(const char* Msg, uint16 Len, char FromLeft, char AddFlag)
{
	if (FromLeft)
	{
		uint32 l = spt::StrLen(Msg);
		if (l > Len)
		{
			l = Len;
		}
		uint32 i;
		for (i = 0; i < l; i++)
		{
			(*this) << *Msg++;
		}
		for (; i < Len; i++)
		{
			(*this) << AddFlag;
		}
	}
	else
	{
		uint32 l = spt::StrLen(Msg);
		if (l > Len)
		{
			l = Len;
		}
		uint32 i = 0;
		uint32 sl = Len - l;
		for (; i < sl; i++)
		{
			(*this) << AddFlag;
		}
		for (i = 0; i < l; i++)
		{
			(*this) << *Msg++;
		}
	}
	return *this;
}

SalString& spt::SalString::FillToLen(uint32 Len, char AddFlag)
{
	while (top < Len)
	{
		*this << AddFlag;
	}
	return *this;
}

int32 spt::SalString::IsInclude(const char* SubStr)
{
	uint32 start = 0;
	if (!SubStr)
	{
		return -1;
	}
	uint32 off = 0, end = 0;
	while (start < top)
	{
		if (bufBase[start] == SubStr[0])
		{
			off = 0;
			end = off + start;
			while ((end) < top)
			{
				if (0 == SubStr[off])
				{
					return start;
				}
				else if (bufBase[end] != SubStr[off])
				{
					break;
				}
				off++;
				end = off + start;
			}
		}
		start++;
	}

	return -1;
}

int32 spt::SalString::CharNum(char Flag)
{
	uint32 start = 0;
	int32 num = 0;
	while (start < top)
	{
		if (bufBase[start] == Flag)
		{
			num++;
		}
		start++;
	}
	return num;
}


void spt::SalString::Replace(char oldchar, char newchar)
{
	if (newchar == 0)
	{
		uint32 start = 0;
		while (start < top)
		{
			if (bufBase[start] == oldchar)
			{
				bufBase[start] = newchar;
				top = start;
				break;
			}
			start++;
		}
	}
	else
	{
		uint32 start = 0;
		while (start < top)
		{
			if (bufBase[start] == oldchar)
			{
				bufBase[start] = newchar;
			}
			start++;
		}
	}
}

void spt::SalString::Reverse()
{
	String200B str;
	int32 i = StrLen();
	char* cstr = Str() + i - 1;
	while (i--)
	{
		str << *cstr--;
	}
	Clear();
	(*this) << str;
}


void spt::SalString::Clear()
{
	SingleStackBuf::Clear();
	if (bufBase)
	{
		bufBase[top] = 0;
	}
}

int32 spt::SalString::StrLen()
{
	return top;
}

int32 spt::SalString::StrBufLen()
{
	return BufSize();
}

char* spt::SalString::Str()
{
	return bufBase;
}

const char* spt::SalString::Str() const
{
	return bufBase;
}

bool8 spt::SalString::operator==(const char* Buf)const
{
	return StrCmp(Buf, bufBase) == 0;
}

bool8 spt::SalString::operator!=(const char* Buf) const
{
	return StrCmp(Buf, bufBase) != 0;
}

SalString& spt::SalString::operator=(const char* Buf)
{
	Clear();
	(*this) << Buf;
	return *this;
}

void spt::TransString::SetBuf(const char* Buf)
{
	if (Buf)
	{
		len = StrLen(Buf);
		sur = Buf;
		pos = 0;
	}
	else
	{
		len = 0;
		pos = 0;
		sur = 0;
	}
}

void spt::TransString::GetHex(uint32& data, uint8 StopFlag)
{
	uint8 d;
	data = 0;
	while (pos < len)
	{
		d = (uint8)sur[pos];
		if (d == ' ')
		{
			pos++;
			continue;
		}
		else
		{
			break;
		}
	}
	if ((sur[pos + 1] == 'x') || sur[pos + 1] == 'X')
	{
		pos += 2;
	}
	while (pos < len)
	{
		d = (uint8)sur[pos];
		if (d == StopFlag)
		{
			pos++;
			break;
		}
		else if ((d <= '9') && (d >= '0'))
		{
			data = data * 16 + d - '0';
			pos++;
		}
		else if ((d <= 'f') && (d >= 'a'))
		{
			data = data * 16 + d - 'a' + 10;
			pos++;
		}
		else if ((d <= 'F') && (d >= 'A'))
		{
			data = data * 16 + d - 'A' + 10;
			pos++;
		}
		else if (d == ' ')
		{
			pos++;
			continue;
		}
		else
		{
			break;
		}
	}
}

void spt::TransString::Get(uint32& data, uint8 StopFlag)
{
	uint8 d;
	data = 0;
	while (pos < len)
	{
		d = (uint8)sur[pos];
		if (d == ' ')
		{
			pos++;
			continue;
		}
		else
		{
			break;
		}
	}
	while (pos < len)
	{
		d = (uint8)sur[pos];
		if (d == StopFlag)
		{
			pos++;
			break;
		}
		else if ((d <= '9') && (d >= '0'))
		{
			data = data * 10 + d - '0';
			pos++;
		}
		else if (d == ' ')
		{
			pos++;
			continue;
		}
		else
		{
			break;
		}
	}
}

void spt::TransString::Get(int32& data, uint8 StopFlag)
{
	uint8 d;
	data = 0;
	bool8 negflag = 0;

	while (pos < len)
	{
		d = (uint8)sur[pos];
		if (d == ' ')
		{
			pos++;
			continue;
		}
		else if (d == '-')
		{
			negflag = 1;
			pos++;
			break;
		}
		else if (d == '+')
		{
			negflag = 0;
			pos++;
			break;
		}
		else
		{
			break;
		}
	}
	while (pos < len)
	{
		d = (uint8)sur[pos];
		if (d == StopFlag)
		{
			pos++;
			break;
		}
		else if ((d <= '9') && (d >= '0'))
		{
			data = data * 10 + d - '0';
			pos++;
		}
		else if (d == ' ')
		{
			pos++;
			continue;
		}
		else
		{
			data = 0;
			break;
		}
	}
	if (negflag)
	{
		data = -data;
	}
}

void spt::TransString::GetFixedInt(int32& data, uint8 StopFlag, uint8& DotNum)
{
	bool8 dotflag = 0;
	DotNum = 0;
	uint8 d;
	data = 0;
	bool8 negflag = 0;

	while (pos < len)
	{
		d = (uint8)sur[pos];
		if (d == ' ')
		{
			pos++;
			continue;
		}
		else if (d == '-')
		{
			negflag = 1;
			pos++;
			break;
		}
		else if (d == '+')
		{
			negflag = 0;
			pos++;
			break;
		}
		else
		{
			break;
		}
	}
	while (pos < len)
	{
		d = (uint8)sur[pos];
		if (d == StopFlag)
		{
			pos++;
			break;
		}
		else if ((d <= '9') && (d >= '0'))
		{
			data = data * 10 + d - '0';
			pos++;
			if (dotflag)
			{
				DotNum++;
			}
		}
		else if ((d == ' '))
		{
			pos++;
			continue;
		}
		else if ((d == '.'))
		{
			dotflag = 1;
			pos++;
			continue;
		}
		else
		{
			break;
		}
	}
	if (negflag)
	{
		data = -data;
	}
}

void spt::TransString::GetFixedInt(uint32& data, uint8 StopFlag, uint8& DotNum)
{
	bool8 dotflag = 0;
	DotNum = 0;
	uint8 d;
	data = 0;
	bool8 negflag = 0;

	while (pos < len)
	{
		d = (uint8)sur[pos];
		if (d == ' ')
		{
			pos++;
			continue;
		}
		else if (d == '-')
		{
			negflag = 1;
			pos++;
			return;
		}
		else if (d == '+')
		{
			negflag = 0;
			pos++;
			break;
		}
		else
		{
			break;
		}
	}
	while (pos < len)
	{
		d = (uint8)sur[pos];
		if (d == StopFlag)
		{
			pos++;
			break;
		}
		else if ((d <= '9') && (d >= '0'))
		{
			data = data * 10 + d - '0';
			pos++;
			if (dotflag)
			{
				DotNum++;
			}
		}
		else if ((d == ' '))
		{
			pos++;
			continue;
		}
		else if ((d == '.'))
		{
			dotflag = 1;
			pos++;
			continue;
		}
		else
		{
			break;
		}
	}
}

void spt::TransString::Get(SalString& data, uint8 StopFlag)
{
	uint8 d;
	while (pos < len)
	{
		d = (uint8)sur[pos++];
		if ((d == StopFlag) || (d == 0))
		{
			break;
		}
		data << (char)d;
	}
}

bool8 spt::TransString::GetLine(SalString& data)
{
	uint8 d;
	uint32 l = data.StrLen();
	while (pos < len)
	{
		d = (uint8)sur[pos++];
		if ((d == '\r') || (d == 0))
		{
			d = (uint8)sur[pos];
			if (d == '\n')
			{
				pos++;
			}
			break;
		}
		if ((d == '\n'))
		{
			break;
		}
		data << (char)d;
	}
	return  (int32)l != data.StrLen();
}

bool8 spt::TransString::GetLine(SalString& data, uint8 StopFlag)
{
	uint8 d;
	uint32 l = data.StrLen();
	while (pos < len)
	{
		d = (uint8)sur[pos++];
		if ((d == StopFlag) || (d == 0))
		{
			break;
		}
		if ((d == '\r'))
		{
			d = (uint8)sur[pos];
			if (d == '\n')
			{
				pos++;
			}
			break;
		}
		if ((d == '\n'))
		{
			break;
		}
		data << (char)d;
	}
	return (int32)l != data.StrLen();
}

bool8 spt::TransString::IsEnd()
{
	return pos >= len;
}

uint64 spt::TransString::GetHex(uint8 StopFlag, uint32 DataLen)
{
	uint8 d;
	uint64 data = 0;
	while (pos < len)
	{
		d = (uint8)sur[pos];
		if (d == ' ')
		{
			pos++;
			continue;
		}
		else
		{
			break;
		}
	}
	if ((sur[pos + 1] == 'x') || sur[pos + 1] == 'X')
	{
		pos += 2;
	}
	uint32 datal = 0;
	while (pos < len)
	{
		d = (uint8)sur[pos];
		if (d == StopFlag)
		{
			pos++;
			break;
		}
		else if (datal == DataLen)
		{
			break;
		}
		else if ((d <= '9') && (d >= '0'))
		{
			data = data * 16 + d - '0';
			pos++;
			datal++;
		}
		else if ((d <= 'f') && (d >= 'a'))
		{
			data = data * 16 + d - 'a' + 10;
			pos++;
			datal++;
		}
		else if ((d <= 'F') && (d >= 'A'))
		{
			data = data * 16 + d - 'A' + 10;
			pos++;
			datal++;
		}
		else if (d == ' ')
		{
			pos++;
			continue;
		}
		else
		{
			data = 0;
			break;
		}
	}
	return data;
}

bool8 spt::TransString::Get(char& data)
{
	data = 0;
	if (pos < len)
	{
		data = (uint8)sur[pos++];
		return 1;
	}
	return 0;
}

