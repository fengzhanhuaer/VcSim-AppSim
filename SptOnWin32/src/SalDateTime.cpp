#include<time.h>
#include "ApiProject.h"
#ifdef WIN32_SIM
#include<windows.h>
#else 
extern "C" int  BspGetHwRtc(struct tm* pTime);
extern "C" int  BspSetHwRtc(struct tm* pTime);
#endif

using namespace spt;

static const unsigned char mdays[2][12] = {
	{31,28,31,30,31,30,31,31,30,31,30,31},
	{31,29,31,30,31,30,31,31,30,31,30,31}
};
static const unsigned short yearmdays[2][13] = {
	{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334,365},
	{0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335,366}
};
static const unsigned short yeardays[2] = { 365,366 };
bool8 spt::IsLeapYear(uint16 y)
{
	return bool8(((((y) % 4) == 0 && ((y) % 100) != 0) || ((y) % 400) == 0));
}


int64 spt::SalDateStamp::Us()const
{
	int64 us = 0;
	uint32* p = (uint32*)&us;
	p[0] = usL;
	p[1] = usH;
	return us;
}

void spt::SalDateStamp::Set(int64 us)
{
	uint32* p = (uint32*)&us;
	usL = (uint32)p[0];
	usH = (uint32)p[1];
}

void spt::SalDateStamp::Now()
{
	const  SalDateStamp& stamp = SptDateTask::Instance().Now();
	do
	{
		Set(stamp.Us());
	} while (Us() != stamp.Us());
	q = stamp.q;
}

int64 spt::SalDateStamp::toUtcSec()
{
	int64 t = Us() - SalDateStamp::UTCBASE - (int64)DatePara::Instance().TimeZone.Data() * SalDateStamp::Dt1Hour;
	return (t / SalDateStamp::Dt1Second);
}

int64 spt::SalDateStamp::fromUtcSec(int64 Sec)
{
	uint64 t = (int64)Sec * SalDateStamp::Dt1Second + (int64)DatePara::Instance().TimeZone.Data() * SalDateStamp::Dt1Hour + SalDateStamp::UTCBASE;
	q.q = 0;
	return t;
}

void spt::SalDateStamp::toUtcCode(uint32& Sec, uint32& fractionAndQ)
{
	uint64 t = Us() - SalDateStamp::UTCBASE - (int64)DatePara::Instance().TimeZone.Data() * SalDateStamp::Dt1Hour;
	Sec = (uint32)(t / SalDateStamp::Dt1Second);
	uint32 us = (uint32)(t % SalDateStamp::Dt1Second);
	//us = us * 16777216 / 1000000;
	//us = us * 262144 / 15625;
	us = (uint32)(us * 16.777216f + 0.5);
	uint32 q = (this->q.q & 0xe0) | (0x0a);// (this->q.bits.TimeAccuracy);
	fractionAndQ = (us << 8) | q;
}

void spt::SalDateStamp::fromUtcCode(uint32 Sec, uint32 fractionAndQ)
{
	uint64 t = (uint64)Sec * SalDateStamp::Dt1Second + (int64)DatePara::Instance().TimeZone.Data() * SalDateStamp::Dt1Hour + SalDateStamp::UTCBASE;
	uint32 us = (uint32)((fractionAndQ >> 8) / 16.777216f);
	t = t + us;
	Set(t);
	q.q = fractionAndQ & 0xe0;
	q.bits.TimeAccuracy = fractionAndQ & 0x1f;
}

void spt::SalDateStamp::toPriUtcCode(uint32& Sec, uint32& fractionAndQ)
{
	uint64 t = Us() - SalDateStamp::UTCBASE - (int64)DatePara::Instance().TimeZone.Data() * SalDateStamp::Dt1Hour;
	Sec = (uint32)(t / SalDateStamp::Dt1Second);
	uint32 us = (uint32)(t % SalDateStamp::Dt1Second);
	uint32 q = this->q.q & 0xff;
	fractionAndQ = (us << 8) | q;
}

void spt::SalDateStamp::fromPriUtcCode(uint32 Sec, uint32 fractionAndQ)
{
	uint64 t = (uint64)Sec * SalDateStamp::Dt1Second + (int64)DatePara::Instance().TimeZone.Data() * SalDateStamp::Dt1Hour + SalDateStamp::UTCBASE;
	uint32 us = (uint32)((fractionAndQ >> 8));
	t = t + us;
	Set(t);
	q.q = fractionAndQ & 0xff;
	q.bits.TimeAccuracy = 0x0a;
}

void spt::SalDateStamp::Set(SalRtc* Rtc)
{
	Rtc->Check();
	int64 us = 0;
	int16 year = 1;
	if (Rtc->year >= 2020)
	{
		us += 63713433600000000;
		year = 2020;
	}
	else if (Rtc->year >= 2000)
	{
		us += 63082281600000000;
		year = 2000;
	}
	for (uint16 i = year; i < Rtc->year; i++)
	{
		us += yeardays[IsLeapYear(i)] * Dt1Day;
	}

	uint8 isleap = IsLeapYear(Rtc->year);

	us += yearmdays[isleap][Rtc->month - 1] * (int64)Dt1Day;
	us += (Rtc->day - 1) * (int64)Dt1Day;
	us += Rtc->hour * (int64)Dt1Hour;
	us += Rtc->minute * (int64)Dt1Minute;
	us += Rtc->second * (int64)Dt1Second;
	us += (int64)Rtc->ms * 1000;
	us += (int64)Rtc->us;
	Set(us);
	q.q = Rtc->q;
	q.bits.TimeAccuracy = 0xa;
}

void spt::SalDateStamp::FromStrFmt1(const char* Str)
{
	SalRtc rtc;
	rtc.FromStrFmt1(Str);
	Set(&rtc);
}

void spt::SalDateStamp::FromStrFmt2(const char* Str)
{
	SalRtc rtc;
	rtc.FromStrFmt2(Str);
	Set(&rtc);
}

void spt::SalDateStamp::ToStrFmt1(SalString& Str)const
{
	SalRtc rtc;
	rtc.FromStamp(this);
	rtc.ToStrFmt1(Str);
}

void spt::SalDateStamp::ToStrFmt10(SalString& Str)const
{
	SalRtc rtc;
	rtc.FromStamp(this);
	rtc.ToStrFmt10(Str);
}

void spt::SalDateStamp::ToStrFmt11(SalString& Str)const
{
	SalRtc rtc;
	rtc.FromStamp(this);
	rtc.ToStrFmt11(Str);
}

void spt::SalDateStamp::ToStrFmt12(SalString& Str)const
{
	SalRtc rtc;
	rtc.FromStamp(this);
	rtc.ToStrFmt12(Str);
}

void spt::SalDateStamp::ToStrFmt13(SalString& Str)const
{
	SalRtc rtc;
	rtc.FromStamp(this);
	rtc.ToStrFmt13(Str);
}

void spt::SalDateStamp::ToStrFmt14(SalString& Str)const
{
	SalRtc rtc;
	rtc.FromStamp(this);
	rtc.ToStrFmt14(Str);
}

void spt::SalDateStamp::ToStrFmt2(SalString& Str)const
{
	SalRtc rtc;
	rtc.FromStamp(this);
	rtc.ToStrFmt2(Str);
}

void spt::SalDateStamp::ToStrFmt22(SalString& Str)const
{
	SalRtc rtc;
	rtc.FromStamp(this);
	rtc.ToStrFmt22(Str);
}

void spt::SalDateStamp::ToStrFmt3(SalString& Str)const
{
	SalRtc rtc;
	rtc.FromStamp(this);
	rtc.ToStrFmt3(Str);
}

void spt::SalDateStamp::ToStrHzFmt1(SalString& Str)const
{
	SalRtc rtc;
	rtc.FromStamp(this);
	rtc.ToStrHzFmt1(Str);
}

void spt::SalDateStamp::ToStrHzFmt2(SalString& Str)const
{
	SalRtc rtc;
	rtc.FromStamp(this);
	rtc.ToStrHzFmt2(Str);
}

void spt::SalDateStamp::ToStrHzFmt3(SalString& Str)const
{
	SalRtc rtc;
	rtc.FromStamp(this);
	rtc.ToStrHzFmt3(Str);
}

void spt::SalDateStamp::ToStrFmt40(SalString& Str)const
{
	SalRtc rtc;
	rtc.FromStamp(this);
	rtc.ToStrFmt40(Str);
}

void spt::SalDateStamp::ToStrFmt41(SalString& Str)const
{
	SalRtc rtc;
	rtc.FromStamp(this);
	rtc.ToStrFmt41(Str);
}

void spt::SalDateStamp::ToStrFmt42(SalString& Str)const
{
	SalRtc rtc;
	rtc.FromStamp(this);
	rtc.ToStrFmt42(Str);
}

void spt::SalDateStamp::ToStrFmt43(SalString& Str)const
{
	SalRtc rtc;
	rtc.FromStamp(this);
	rtc.ToStrFmt43(Str);
}

void spt::SalDateStamp::ToStrFmt5(SalString& Str) const
{
	SalRtc rtc;
	rtc.FromStamp(this);
	rtc.ToStrFmt5(Str);
}

void spt::SalDateStamp::FromStrFmt5(const char* Str)
{
	SalRtc rtc;
	rtc.FromStrFmt5(Str);
	Set(&rtc);
}

void spt::SalDateStamp::FromStrHzFmt1(const char* Str)
{
	SalRtc rtc;
	rtc.FromStrHzFmt1(Str);
	Set(&rtc);
}

void spt::SalDateStamp::FromStrHzFmt2(const char* Str)
{
	SalRtc rtc;
	rtc.FromStrHzFmt2(Str);
	Set(&rtc);
}

void spt::SalDateStamp::FromStrHzFmt3(const char* Str)
{
	SalRtc rtc;
	rtc.FromStrHzFmt3(Str);
	Set(&rtc);
}

void spt::SalDateStamp::ToSNTPV4(uint32& sec, uint32& fraction)const
{
	uint64 t = Us() - SNTPV4BASE - (int64)DatePara::Instance().TimeZone.Data() * Dt1Hour;;
	uint32 us = (uint32)(t % Dt1Second);
	fraction = (uint32)(us * (4294.967295f));
	uint64 s = (t / Dt1Second);
	sec = (uint32)s;
}

void spt::SalDateStamp::FromSNTPV4(uint32 sec, uint32 fraction)
{
	int64 t = sec + SNTPV4BASE + (int64)DatePara::Instance().TimeZone.Data() * Dt1Hour;
	if ((sec & 0x80000000) == 0)
	{
		t += (uint32)0xffffffff;
	}
	t += (uint32)(fraction / (4294.967295f));
	Set(t);
	q.q = 0;
}

void spt::SalDateStamp::FromStrBuild(const char* Date, const char* Time)
{
	SalRtc rtc;
	rtc.FromStrBuild(Date, Time);
	Set(&rtc);
	q.q = 0;
}

void spt::SalRtc::Now()
{
	SalDateStamp cstamp;
	cstamp.Now();
	FromStamp(&cstamp);
}

void spt::SalRtc::FromTm(const tm* t)
{
	if (!t)
	{
		return;
	}
	second = t->tm_sec;
	minute = t->tm_min;
	hour = t->tm_hour;
	day = t->tm_mday;
	month = t->tm_mon + 1;
	year = t->tm_year + 1900;
	us = 0;
	ms = 0;
	q = 0;
}

void spt::SalRtc::ToTm(tm* t)const
{
	if (!t)
	{
		return;
	}
	t->tm_sec = second;
	t->tm_min = minute;
	t->tm_hour = hour;
	t->tm_mday = day;
	t->tm_mon = month - 1;
	t->tm_year = year - 1900;
}

int64 spt::SalRtc::Stamp()
{
	SalDateStamp st;
	st.Set(this);
	return st.Us();
}

void spt::SalRtc::FromStamp(uint64 Us)
{
	SalDateStamp t;
	t.Set(Us);
	t.q.q = 0;
	FromStamp(&t);
	q = 0;
}

void spt::SalRtc::FromStamp(const SalDateStamp* data)
{
	int64 stamp = data->Us();
	us = (uint16)(stamp % 1000);
	stamp = stamp / 1000;
	ms = (uint16)(stamp % 1000);
	stamp = stamp / 1000;

	second = (uint8)(stamp % 60);
	stamp = stamp / 60;
	minute = (uint8)(stamp % 60);
	stamp = stamp / 60;

	if (!(second || minute))
	{
		if (data->q.bits.isLeap && (!data->q.bits.isNegLeap))
		{
			minute = 59;
			second = 60;
			stamp -= 1;
		}
	}
	hour = (uint8)(stamp % 24);
	stamp = stamp / 24;

	int32 day = (int32)stamp;
	year = 1;
	if (day >= 737424)
	{
		day -= 737424;
		year = 2020;
	}
	else if (day >= 730119)
	{
		day -= 730119;
		year = 2000;
	}
	while (day >= yeardays[IsLeapYear(year)])
	{
		day -= yeardays[IsLeapYear(year)];
		year++;
	}
	bool8 isleap = IsLeapYear(year);
	month = 0;
	for (int i = 1; i <= 12; i++)
	{
		if (yearmdays[isleap][i] > day)
		{
			month = i;
			day -= yearmdays[isleap][i - 1];
			break;
		}
	}
	this->day = day + 1;
	q = (uint8)data->q.q;
}

void spt::SalRtc::FromStrFmt1(const char* Str)
{
	TransString tstr;
	tstr.SetBuf(Str);
	uint32 data;
	tstr.Get(data, '/');
	year = data;
	tstr.Get(data, '/');
	month = data;
	tstr.Get(data, ' ');
	day = data;
	tstr.Get(data, ':');
	hour = data;
	tstr.Get(data, ':');
	minute = data;
	tstr.Get(data, ':');
	second = data;
	ms = 0;
	us = 0;
	q = 0;
}

void spt::SalRtc::FromStrFmt2(const char* Str)
{
	TransString tstr;
	tstr.SetBuf(Str);
	uint32 data;
	tstr.Get(data, '-');
	year = data;
	tstr.Get(data, '-');
	month = data;
	tstr.Get(data, ' ');
	day = data;
	tstr.Get(data, ':');
	hour = data;
	tstr.Get(data, ':');
	minute = data;
	tstr.Get(data, ':');
	second = data;
	ms = 0;
	us = 0;
	q = 0;
}

void spt::SalRtc::FromStrBuild(const char* Date, const char* Time)
{
	TransString tstr;
	tstr.SetBuf(Date);
	uint32 data;
	String10B str;
	tstr.Get(str, ' ');
	u4bytes d;
	d.u32 = *(uint32*)str.Str();
	switch (d.u32)
	{
#if 0
		case (uint32)('Jan') : {month = 1; break; }
		case (uint32)('Feb') : {month = 2; break; }
		case (uint32)('Mar') : {month = 3; break; }
		case (uint32)('Apr') : {month = 4; break; }
		case (uint32)('May') : {month = 5; break; }
		case (uint32)('Jun') : {month = 6; break; }
		case (uint32)('Jul') : {month = 7; break; }
		case (uint32)('Aug') : {month = 8; break; }
		case (uint32)('Sep') : {month = 9; break; }
		case (uint32)('Oct') : {month = 10; break; }
		case (uint32)('Nov') : {month = 11; break; }
		case (uint32)('Dec') : {month = 12; break; }
		default: {month = 0; break; }
#else 
		case (uint32)(0x6e614a) : {month = 1; break; }
		case (uint32)(0x626546) : {month = 2; break; }
		case (uint32)(0x72614d) : {month = 3; break; }
		case (uint32)(0x727041) : {month = 4; break; }
		case (uint32)(0x79614d) : {month = 5; break; }
		case (uint32)(0x6e754a) : {month = 6; break; }
		case (uint32)(0x6c754a) : {month = 7; break; }
		case (uint32)(0x677541) : {month = 8; break; }
		case (uint32)(0x706553) : {month = 9; break; }
		case (uint32)(0x74634f) : {month = 10; break; }
		case (uint32)(0x766f4e) : {month = 11; break; }
		case (uint32)(0x636544) : {month = 12; break; }
		default: {month = 0; break; }
#endif
	}
	tstr.Get(data, ' ');
	day = data;
	tstr.Get(data, ' ');
	year = data;
	tstr.SetBuf(Time);
	tstr.Get(data, ':');
	hour = data;
	tstr.Get(data, ':');
	minute = data;
	tstr.Get(data, ':');
	second = data;
	ms = 0;
	us = 0;
	q = 0;
}

void spt::SalRtc::ToStrFmt1(SalString& Str)const
{
	Str.Format(year, 4, '0');
	Str << '/';
	Str.Format(month, 2, '0');
	Str << '/';
	Str.Format(day, 2, '0');
	Str << ' ';
	Str.Format(hour, 2, '0');
	Str << ':';
	Str.Format(minute, 2, '0');
	Str << ':';
	Str.Format(second, 2, '0');
}

void spt::SalRtc::ToStrFmt10(SalString& Str)const
{
	Str.Format(year, 4, '0');
	Str << '/';
	Str.Format(month, 2, '0');
	Str << '/';
	Str.Format(day, 2, '0');
}

void spt::SalRtc::ToStrFmt11(SalString& Str)const
{
	Str.Format(hour, 2, '0');
	Str << ':';
	Str.Format(minute, 2, '0');
	Str << ':';
	Str.Format(second, 2, '0');
}

void spt::SalRtc::ToStrFmt12(SalString& Str)const
{
	Str.Format(hour, 2, '0');
	Str << ':';
	Str.Format(minute, 2, '0');
	Str << ':';
	Str.Format(second, 2, '0');
	Str << '.';
	Str.Format(ms, 3, '0');
}

void spt::SalRtc::ToStrFmt13(SalString& Str)const
{
	Str.Format(hour, 2, '0');
	Str << ':';
	Str.Format(minute, 2, '0');
	Str << ':';
	Str.Format(second, 2, '0');
	Str << '.';
	Str.Format(ms, 3, '0');
	Str.Format(us, 3, '0');
}

void spt::SalRtc::ToStrFmt14(SalString& Str)const
{
	Str.Format(day, 2, '0');
	Str << '/';
	Str.Format(month, 2, '0');
	Str << '/';
	Str.Format(year, 4, '0');
}

void spt::SalRtc::ToStrFmt2(SalString& Str)const
{
	Str.Format(year, 4, '0');
	Str << '/';
	Str.Format(month, 2, '0');
	Str << '/';
	Str.Format(day, 2, '0');
	Str << ' ';
	Str.Format(hour, 2, '0');
	Str << ':';
	Str.Format(minute, 2, '0');
	Str << ':';
	Str.Format(second, 2, '0');
	Str << '.';
	Str.Format(ms, 3, '0');
}

void spt::SalRtc::ToStrFmt22(SalString& Str)const
{
	Str.Format(year, 4, '0');
	Str << '-';
	Str.Format(month, 2, '0');
	Str << '-';
	Str.Format(day, 2, '0');
	Str << ' ';
	Str.Format(hour, 2, '0');
	Str << ':';
	Str.Format(minute, 2, '0');
	Str << ':';
	Str.Format(second, 2, '0');
	Str << ':';
	Str.Format(ms, 3, '0');
}

void spt::SalRtc::ToStrFmt3(SalString& Str)const
{
	Str.Format(year, 4, '0');
	Str << '/';
	Str.Format(month, 2, '0');
	Str << '/';
	Str.Format(day, 2, '0');
	Str << ' ';
	Str.Format(hour, 2, '0');
	Str << ':';
	Str.Format(minute, 2, '0');
	Str << ':';
	Str.Format(second, 2, '0');
	Str << '.';
	Str.Format(ms, 3, '0');
	Str << '.';
	Str.Format(us, 3, '0');
}

void spt::SalRtc::ToStrFmt40(SalString& Str)const
{
	Str.Format(year, 4, '0');
	Str.Format(month, 2, '0');
	Str.Format(day, 2, '0');
}

void spt::SalRtc::ToStrFmt41(SalString& Str)const
{
	Str.Format(hour, 2, '0');
	Str.Format(minute, 2, '0');
	Str.Format(second, 2, '0');
}

void spt::SalRtc::ToStrFmt42(SalString& Str)const
{
	Str.Format(year, 4, '0');
	Str.Format(month, 2, '0');
	Str.Format(day, 2, '0');
	Str << '.';
	Str.Format(hour, 2, '0');
	Str.Format(minute, 2, '0');
	Str.Format(second, 2, '0');
}

void spt::SalRtc::ToStrFmt43(SalString& Str)const
{
	Str.Format(year, 4, '0');
	Str.Format(month, 2, '0');
	Str.Format(day, 2, '0');
	Str << '_';
	Str.Format(hour, 2, '0');
	Str.Format(minute, 2, '0');
	Str.Format(second, 2, '0');
	Str << '_';
	Str.Format(ms, 3, '0');
}

void spt::SalRtc::ToStrFmt5(SalString& Str) const
{
	Str.Format(year, 4, '0');
	Str << '/';
	Str.Format(month, 2, '0');
	Str << '/';
	Str.Format(day, 2, '0');
	Str << ' ';
	Str.Format(hour, 2, '0');
	Str << ':';
	Str.Format(minute, 2, '0');
	Str << ':';
	Str.Format(second, 2, '0');
	Str << '.';
	Str.Format(ms, 3, '0');
	Str << '.';
	Str.Format(us, 3, '0');
	Str << ',';
	Str.FormatHex(q);
}

void spt::SalRtc::FromStrFmt5(const char* Str)
{
	TransString tstr;
	tstr.SetBuf(Str);
	uint32 data;
	tstr.Get(data, '/');
	year = data;
	tstr.Get(data, '/');
	month = data;
	tstr.Get(data, ' ');
	day = data;
	tstr.Get(data, ':');
	hour = data;
	tstr.Get(data, ':');
	minute = data;
	tstr.Get(data, '.');
	second = data;
	tstr.Get(data, '.');
	ms = data;
	tstr.Get(data, ',');
	us = data;
	data = (uint8)tstr.GetHex(',', 2);
	q = (uint8)data;
}

void spt::SalRtc::ToStrHzFmt1(SalString& Str)const
{
	Str.Format(year, 4, '0');
	Str << "年";
	Str.Format(month, 2, '0');
	Str << "月";
	Str.Format(day, 2, '0');
	Str << "日";
	Str.Format(hour, 2, '0');
	Str << ':';
	Str.Format(minute, 2, '0');
	Str << ':';
	Str.Format(second, 2, '0');
}

void spt::SalRtc::ToStrHzFmt2(SalString& Str)const
{
	Str.Format(year, 4, '0');
	Str << "年";
	Str.Format(month, 2, '0');
	Str << "月";
	Str.Format(day, 2, '0');
	Str << "日";
	Str.Format(hour, 2, '0');
	Str << ':';
	Str.Format(minute, 2, '0');
	Str << ':';
	Str.Format(second, 2, '0');
	Str << '.';
	Str.Format(ms, 3, '0');
}

void spt::SalRtc::ToStrHzFmt3(SalString& Str)const
{
	Str.Format(year, 4, '0');
	Str << "年";
	Str.Format(month, 2, '0');
	Str << "月";
	Str.Format(day, 2, '0');
	Str << "日";
	Str.Format(hour, 2, '0');
	Str << ':';
	Str.Format(minute, 2, '0');
	Str << ':';
	Str.Format(second, 2, '0');
	Str << '.';
	Str.Format(ms, 3, '0');
	Str << '.';
	Str.Format(us, 3, '0');
}

void spt::SalRtc::FromStrHzFmt1(const char* Str)
{
	TransString tstr;
	tstr.SetBuf(Str);
	char d;
	uint32 data;
	tstr.Get(data, '/');
	year = data;
	tstr.Get(d);
	tstr.Get(d);
	tstr.Get(data, '/');
	month = data;
	tstr.Get(d);
	tstr.Get(d);
	tstr.Get(data, ' ');
	day = data;
	tstr.Get(d);
	tstr.Get(d);
	tstr.Get(data, ':');
	hour = data;
	tstr.Get(data, ':');
	minute = data;
	tstr.Get(data, '.');
	second = data;
	ms = 0;
	us = 0;
	q = 0;
}

void spt::SalRtc::FromStrHzFmt2(const char* Str)
{
	TransString tstr;
	tstr.SetBuf(Str);
	char d;
	uint32 data = 0;
	tstr.Get(data, '/');
	year = data;
	tstr.Get(d);
	tstr.Get(d);
	tstr.Get(data, '/');
	month = data;
	tstr.Get(d);
	tstr.Get(d);
	tstr.Get(data, ' ');
	day = data;
	tstr.Get(d);
	tstr.Get(d);
	tstr.Get(data, ':');
	hour = data;
	tstr.Get(data, ':');
	minute = data;
	tstr.Get(data, '.');
	second = data;
	tstr.Get(data, '.');
	ms = data;
	us = 0;
	q = 0;
}

void spt::SalRtc::FromStrHzFmt3(const char* Str)
{
	TransString tstr;
	tstr.SetBuf(Str);
	char d;
	uint32 data;
	tstr.Get(data, '/');
	year = data;
	tstr.Get(d);
	tstr.Get(d);
	tstr.Get(data, '/');
	month = data;
	tstr.Get(d);
	tstr.Get(d);
	tstr.Get(data, ' ');
	day = data;
	tstr.Get(d);
	tstr.Get(d);
	tstr.Get(data, ':');
	hour = data;
	tstr.Get(data, ':');
	minute = data;
	tstr.Get(data, '.');
	second = data;
	tstr.Get(data, '.');
	ms = data;
	tstr.Get(data, '.');
	us = data;
	q = 0;
}

void spt::SalRtc::Check()
{
	if (month > 12)
	{
		month = 12;
	}
	if (month < 1)
	{
		month = 1;
	}
	uint8 isleap = IsLeapYear(year);
	if (day > mdays[isleap][month - 1])
	{
		day = mdays[isleap][month - 1];
	}
	if (day < 1)
	{
		day = 1;
	}
	if (hour >= 23)
	{
		hour = 23;
	}
	if (minute > 60)
	{
		minute = 60;
	}
	if (second > 60)
	{
		second = 60;
	}
	if (ms >= 1000)
	{
		ms = 999;
	}
	if (us >= 1000)
	{
		us = 999;
	}
}


SalEnumDes spt::DatePara::Mode[E_Total] = {
	{0,"本地守时"},
	{1,"SNTP"},
	{2,"电B码"},
	{3,"光B码"},
	{4,"从板卡"},
};
int32 spt::DatePara::PowerUpIni(int32 Para)
{
	const struct ApiAppCfg* cfg = SptMain::Instance().AppCfg();
	if (cfg)
	{
		if (cfg->platform.devtype == ED_SAU31_Sub)
		{
			AdJustMode.Set("校时方式", E_SubBoard);
			AddCfgData(&AdJustMode);
		}
		else
		{
			AdJustMode.Set("校时方式", E_LIGHT_IRIG_B);
			AddCfgData(&AdJustMode);
		}
	}
	else
	{
		AdJustMode.Set("校时方式", E_LIGHT_IRIG_B);
		AddCfgData(&AdJustMode);
	}
	AdJustMode.SetNotes("0本地守时1SNTP2电B码3光B码4从板卡");
	TimeZone.Set("时区", 8);
	TimeZone.SetNotes("时区");
	AddCfgData(&TimeZone);
	IrigB_Delay.Set("B码额定延时", 990);
	IrigB_Delay.SetUnit(&Unit_mS);
	AddCfgData(&IrigB_Delay);
	IrigB_Precision.Set("时钟精度", 7);
	IrigB_Precision.SetNotes("6-100us;7-ms;8-10ms;9-100ms");
	AddCfgData(&IrigB_Precision);
	IrigB_AckCnt.Set("同步确认时间", 12);
	IrigB_AckCnt.SetUnit(&Unit_S);
	AddCfgData(&IrigB_AckCnt);
	IrigB_UnSynCnt.Set("失步确认时间", 5);
	IrigB_UnSynCnt.SetUnit(&Unit_S);
	AddCfgData(&IrigB_UnSynCnt);
	IrigB_CheckCode.Set("B码校验方式", 0);
	IrigB_CheckCode.SetNotes("0不校验;1奇校验;2偶校验");
	AddCfgData(&IrigB_CheckCode);
	IrigB_HostContDif.Set("时钟帧跳变阈值", 2);
	IrigB_HostContDif.SetNotes("ms");
	AddCfgData(&IrigB_HostContDif);
	IrigB_ReSyncDif.Set("时钟再同步阈值", 3600);
	IrigB_ReSyncDif.SetNotes("s");
	AddCfgData(&IrigB_ReSyncDif);
	path.Set(CN_CFG_FILE_ROOT);
	name.Set("DateTime.cfg");
	if ((uint32)ReadAll() != CfgDataNum())
	{
		SaveAll();
	}
	return 0;
}

spt::DatePara::DatePara()
{
	TimeZone.Set("时区", 8);
	TimeZone.SetNotes("时区");
}

void spt::DateUpdate::GetHwTime(SalDateStamp& Stamp)
{
#ifdef  WIN32_SIM
	FILETIME t;
	GetSystemTimeAsFileTime(&t);
	int64 us = t.dwLowDateTime + (((uint64)t.dwHighDateTime) << 32);
	us /= 10;
	SalDateStamp date;
	SalRtc rtc;
	rtc.FromStrFmt1("1601/01/01 00:00:00");
	date.Set(&rtc);
	us += date.Us() + (int64)DatePara::Instance().TimeZone.Data() * date.Dt1Hour;
	us = us / date.Dt1Second;
	us = us * date.Dt1Second;
	Stamp.Set(us);
	Stamp.q.q = 0x20;
	Stamp.q.bits.TimeAccuracy = 0x0a;
#elif defined( SYLIX_GZK)
	tm t;
	BspGetHwRtc(&t);
	SalRtc date;
	date.FromTm(&t);
	Stamp.Set(date.Stamp());
	Stamp.q.q = 0x20;
	Stamp.q.bits.TimeAccuracy = 0x0a;
#endif //  WIN32_SIM

}

void spt::DateUpdate::SetHwTime(SalDateStamp& Stamp)
{

}

void spt::DateUpdate::RecFpgaMsg(uint8* buf, uint32 MsgLen)
{
	if (MsgLen < M_ArrLen(frmDate.buf))
	{
		MemCpy(frmDate.buf, buf, MsgLen);
		state.frmDateUpdate = 1;
		SptIoProcess::Instance().RecFpgaSlowMsg(frmDate.muframe.res, sizeof(frmDate.muframe.res));
	}
}

bool8 spt::DateUpdate::HmiSetDateTime(const SalDateStamp& Stamp)
{
	if (!state.IrigBSynOk)
	{
		hmiSetStamp = Stamp;
		state.isHmiSetStamp = 1;
		return 1;
	}
	return 0;
}

const struct DateUpdate::OutPut& spt::DateUpdate::Output()
{
	return output;
}

spt::DateUpdate::DateUpdate()
{
	MemSet(&state, 0, sizeof(state));
	MemSet(&output, 0, sizeof(output));
}
void spt::GzkToolsDateUpdate::UpdateFromIrigB(SalDateStamp& Stamp)
{
	SalDateStamp stamp = Stamp;
	SalDateStamp utcdate = Stamp;
	bool8 irigbOk = 0;
	if (state.frmDateUpdate)
	{
		SptApiStatus[E_SAS_HostSvSynState].Update(frmDate.muframe.SvSyn == 0xaaaa);
		output.recFrameNum++;
		state.frmDateUpdate = 0;
		if (output.recFrameNum > 100)
		{
			state.recMoudlePowerInied = 1;
			MemCpy(&realTimerFpgaUtc, frmDate.muframe.utcSec, sizeof(realTimerFpgaUtc));
			if (frmDate.muframe.irigb_Stat & 0x01)//B码校验异常
			{
				output.HostBCodeCheckAlarm = 1;
			}
			else if (frmDate.muframe.irigb[0] & 0x01)
			{
				localIrigBCheckLost.StartTimer();
				state.IrigBHasLost = 0;
				output.HostBCodeCheckAlarm = 0;
				uint8 precision = frmDate.muframe.irigb[0] >> 3;
				output.Irig_B_precision = precision;
				if (precision > DatePara::Instance().IrigB_Precision.Data())
				{
					output.HostBCodePrecisionAlarm = 1;
				}
				else
				{
					output.HostBCodePrecisionAlarm = 0;
					realTimeIrigBRtc.us = 0;
					realTimeIrigBRtc.ms = 0;
					realTimeIrigBRtc.second = Bcd4BitToDec(frmDate.muframe.irigb[1] & 0x7f);
					realTimeIrigBRtc.minute = Bcd4BitToDec(frmDate.muframe.irigb[2] & 0x7f);
					realTimeIrigBRtc.hour = Bcd4BitToDec(frmDate.muframe.irigb[3] & 0x3f);
					uint32 Day = Bcd4BitToDec(frmDate.muframe.irigb[4] & 0xff) - 1;
					Day += 100 * Bcd4BitToDec(frmDate.muframe.irigb[5] & 0x3f);
					if (Day > 366)
					{
						Day = 0;
					}
					realTimeIrigBRtc.day = 1;
					realTimeIrigBRtc.month = 1;
					realTimeIrigBRtc.year = Bcd4BitToDec(frmDate.muframe.irigb[6] & 0xff);
					realTimeIrigBRtc.year += 2000;
					utcdate.Set(&realTimeIrigBRtc);
					int64 us = utcdate.Us() + Day * SalDateStamp::Dt1Day;
					us += (uint64)DatePara::Instance().IrigB_Delay.Data() * SalDateStamp::Dt1MilliSecond + SptSampInt::Instance().PeriodUs();
					utcdate.Set(us);
					utcdate.q.q = 0x0a00;
					if (frmDate.muframe.irigb[8] & 0x01)
					{
						if (frmDate.muframe.irigb[8] & 0x02)
						{
							utcdate.q.q |= 0x03;
						}
						else
						{
							utcdate.q.q |= 0x01;
						}
					}

					int64 utcdif = utcdate.Us() - stamp.Us();
					if (utcdif < 0)
					{
						utcdif = -utcdif;
					}
					utcdif = utcdif / SalDateStamp::Dt1MilliSecond;
					uint32 limit = DatePara::Instance().IrigB_HostContDif.Data();
					if (limit <= 0)
					{
						limit = 2;
					}
					if ((utcdate.q.q & 0x01) || (lastTimeIrigBStamp.q.q & 0x01))
					{
						if ((realTimeIrigBRtc.minute == 0) && (realTimeIrigBRtc.second == 0))
						{
							limit += 1000;
						}
					}

					if (output.HostContAlarm == 1)
					{
						if (utcdif < limit)
						{
							irigbOk = 1;
							state.IrigBContRevertCnt++;
							if (state.IrigBContRevertCnt >= 5)
							{
								output.HostContAlarm = 0;
								state.IrigBContRevertCnt = 0;
							}
						}
						else
						{
							lastTimeIrigBStamp = utcdate;
							utcdate = stamp;
							state.IrigBContRevertCnt = 0;
						}
						state.IrigBContAlmCnt = 0;
					}
					else
					{
						//B码接收正常，进行时间连续性判断
						if (state.IrigBSynOk)
						{
							if (utcdif < limit)
							{
								irigbOk = 1;
								state.IrigBContAlmCnt = 0;
							}
							else
							{
								state.IrigBContAlmCnt++;
								if (state.IrigBContAlmCnt >= 5)
								{
									//出现帧跳变,连续判断5次后动作
									LogMsg.Stamp() << utcdate << " irigb dif over " << (uint32)utcdif << "\n";
									output.HostContAlarm = 1;
									state.IrigBContAlmCnt = 0;
								}
								lastTimeIrigBStamp = utcdate;
								utcdate = stamp;
							}
						}
						else
						{
							irigbOk = 1;
						}
						state.IrigBContRevertCnt = 0;
					}
				}
			}
			else
			{
				if (!localIrigBCheckLost.IsEnable())
				{
					localIrigBCheckLost.Enable(1);
					localIrigBCheckLost.StartTimer();
				}
				if (localIrigBCheckLost.Status(1002))//B码丢失时,重新判断帧跳变
				{
					state.IrigBHasLost = 1;
					state.IrigBContAlmCnt = 0;
					state.IrigBContRevertCnt = 0;
				}
			}
			//无B码情况下的与FPGA之间守时判断
			if (((frmDate.muframe.irigb[0] & 0x01) == 0))
			{
				if (state.forceSetStampDelay > 10)
				{
					if (state.forceSetStampDelay < 0xff)
					{
						state.forceSetStampDelay++;
					}
					utcdate.fromPriUtcCode(realTimerFpgaUtc.uSec, realTimerFpgaUtc.u_Fra_Q);
					utcdate.q.q &= 0xa0f;
					int64 dif = utcdate.Us() - stamp.Us();
					if (dif < 0)
					{
						dif = -dif;
					}
					if (dif > 2 * stamp.Dt1Second)
					{
						state.frmFpgaForceUpdateSec = 1;
						LogMsg.Stamp() << utcdate << " fpga time dif over " << (uint32)dif << "\n";
						utcdate = stamp;
					}
				}
				else
				{
					state.forceSetStampDelay++;
				}
			}
		}
	}
	if (output.HostBCodeCheckAlarm || output.HostBCodePrecisionAlarm || state.IrigBHasLost)
	{
		if (output.HostTPortAlarm == 0)
		{
			if (localIrigBCheckPortErr.IsEnable())
			{
				if (localIrigBCheckPortErr.Status())
				{
					output.HostTPortAlarm = 1;
					localIrigBCheckPortErr.Enable(0);
				}
			}
			else
			{
				localIrigBCheckPortErr.UpCnt(DatePara::Instance().IrigB_UnSynCnt.Data() * 1000);
				localIrigBCheckPortErr.Enable(1);
			}
		}

		localIrigBCheckPortOk.Enable(0);

	}
	else
	{
		if (output.HostTPortAlarm == 1)
		{
			if (localIrigBCheckPortOk.IsEnable())
			{
				if (localIrigBCheckPortOk.Status())
				{
					output.HostTPortAlarm = 0;
					localIrigBCheckPortOk.Enable(0);
				}
			}
			else
			{
				localIrigBCheckPortOk.UpCnt(DatePara::Instance().IrigB_UnSynCnt.Data() * 1000);
				localIrigBCheckPortOk.Enable(1);
			}
		}
		localIrigBCheckPortErr.Enable(0);
	}
	if (state.IrigBSynOk)
	{
		if (irigbOk)
		{
			output.HostTSrvAlarm = 0;
			lastTimeIrigBStamp = utcdate;
			localIrigBLostTimer.Enable(0);
		}
		else if (localIrigBLostTimer.IsEnable())
		{
			if (localIrigBLostTimer.Status())
			{
				state.IrigBSynOk = 0;
				localIrigBLostTimer.Enable(0);
				state.IrigBProcessRecOkCnt = 0;
				output.HostTSrvAlarm = 1;
			}
		}
		else
		{
			localIrigBLostTimer.Enable(0);
			localIrigBLostTimer.UpCnt(DatePara::Instance().IrigB_UnSynCnt.Data() * 1000);
			localIrigBLostTimer.Enable(1);
		}
	}
	else
	{
		//B码接收正常，由失步到同步
		if (irigbOk)
		{
			if (state.IrigBProcessRecOkCnt >= DatePara::Instance().IrigB_AckCnt.Data())
			{
				LogMsg.Stamp() << "IrigBRecOkCnt ok \n";
				state.IrigBProcessRecOkCnt = 0;
				state.IrigBSynOk = 1;
				state.IrigBPowerUpSynOk = 1;
				output.HostTPortAlarm = 0;
				output.HostTSrvAlarm = 0;
				output.HostContAlarm = 0;
				output.HostBCodePrecisionAlarm = 0;
				output.HostBCodeCheckAlarm = 0;
				SptDateTask::Instance().ForceUpdateHwRtc();
				state.frmFpgaForceUpdateSec = 1;
				localIrigBLostTimer.Enable(0);
			}
			else
			{
				int64 utcdif = utcdate.Us() - lastTimeIrigBStamp.Us();
				lastTimeIrigBStamp = utcdate;
				utcdif -= (1000 * SalDateStamp::Dt1MilliSecond);
				if (utcdif < 0)
				{
					utcdif = -utcdif;
				}
				if (utcdif <= 2)
				{
					if (SptIoProcess::Instance().AppFlags().blUnitRevert)
					{
						state.IrigBPowerUpSynOk = 0;
					}
					if (state.IrigBPowerUpSynOk)
					{
						int64 utcdif = utcdate.Us() - stamp.Us();
						if (utcdif < 0)
						{
							utcdif = -utcdif;
						}
						utcdif = utcdif / SalDateStamp::Dt1Second;
						if (utcdif < (uint32)DatePara::Instance().IrigB_ReSyncDif.Data())
						{
							state.IrigBProcessRecOkCnt++;
						}
					}
					else
					{
						state.IrigBProcessRecOkCnt++;
					}
				}
				utcdate = stamp;
			}

			localIrigBCheckCont.StartTimer();
			localIrigBCheckSrvErr.Enable(0);
		}
		//未收到B码
		else
		{
			if (output.HostTSrvAlarm == 0)
			{
				if (localIrigBCheckSrvErr.IsEnable())
				{
					if (localIrigBCheckSrvErr.Status())
					{
						output.HostTSrvAlarm = 1;
						localIrigBCheckSrvErr.Enable(0);
					}
				}
				else
				{
					localIrigBCheckSrvErr.UpCnt(10000);
					localIrigBCheckSrvErr.Enable(1);
				}
			}

			if (!localIrigBCheckCont.IsEnable())
			{
				localIrigBCheckCont.Enable(1);
				localIrigBCheckCont.StartTimer();
			}

			if (localIrigBCheckCont.Status(1002))
			{
				state.IrigBProcessRecOkCnt = 0;
			}
		}
	}
	Stamp = utcdate;
}
void spt::GzkToolsDateUpdate::UpdateFromSntp(SalDateStamp& Stamp)
{
	//SNTP校时（待实现）

	//供中断里面更新全局时钟
	sntpSetStamp = Stamp;
	state.isSntpSetStamp = 1;
}
void spt::GzkToolsDateUpdate::UpdateTimeInMsInt(SalDateStamp& Stamp)
{
	int64 us = Stamp.Us() + SalDateStamp::Dt1MilliSecond;
	Stamp.Set(us);
}

void spt::GzkToolsDateUpdate::UpdateTimeInSampInt(SalDateStamp& Stamp)
{
	int64 us = Stamp.Us() + SptSampInt::Instance().PeriodUs();
	Stamp.Set(us);
}

spt::Gzk35kVDateUpdate::Gzk35kVDateUpdate(SalDateStamp* Sysp)
{
	SysStamp = Sysp;
}

void spt::Gzk35kVDateUpdate::UpdateTimeInMsInt(SalDateStamp& Stamp)
{
	int64 us = Stamp.Us() + SalDateStamp::Dt1MilliSecond;
	Stamp.Set(us);
}

void spt::Gzk35kVDateUpdate::UpdateTimeInSampInt(SalDateStamp& Stamp)
{
	int64 us = Stamp.Us() + SptSampInt::Instance().PeriodUs();
	Stamp.Set(us);
}

void spt::Gzk35kVDateUpdate::SetHwTime(SalDateStamp& Stamp)
{
}

void spt::Gzk35kVDateUpdate::SetStampInMsInt(SalDateStamp& Stamp)
{
#ifdef SYLIX_GZK
	if (SysStamp)
	{
		*SysStamp = Stamp;
	}
#endif
}

void spt::GzkSauDateUpdate::SetHwTime(SalDateStamp& Stamp)
{
	struct tm t;
	SalRtc date;
	date.FromStamp(&Stamp);
	date.ToTm(&t);
#ifdef  WIN32_SIM

#elif defined( SYLIX_GZK)
	BspSetHwRtc(&t);
#endif //  WIN32_SIM
}
void spt::GzkSauDateUpdate::UpdateTimeInSampInt(SalDateStamp& Stamp)
{
	const struct ApiAppCfg* cfg = SptMain::Instance().AppCfg();
	if (cfg)
	{
		if (cfg->platform.devtype == ED_SAU31_Sub)
		{
			UpdateSubBoard(Stamp);
		}
		else
		{
			UpdateMainBoard(Stamp);
		}
	}
}

void spt::GzkSauDateUpdate::UpdateFpgaTime()
{
	CpuFpgaCmmMsgBuf msg;
	updateFrame.FrmNo++;
	//fixme 后续完善喂狗措施
	updateFrame.FeedDog = 0xAA;
	UpdateFpgaFrameCfg cfg;
	cfg.u8 = 0;
	cfg.bits.DisableIrigB = 0;
	cfg.bits.CheckMode = DatePara::Instance().IrigB_CheckCode.Data() % 3;
	updateFrame.Cfg = cfg.u8;
	SalDateStamp stamp;
	stamp.Now();
	uint32 sec, fra;
	stamp.toPriUtcCode(sec, fra);
	MemCpy(updateFrame.UtcSec, &sec, sizeof(sec));
	uint8 utcqlast = updateFrame.UtcUs_Q[0];
	MemCpy(updateFrame.UtcUs_Q, &fra, sizeof(fra));
	updateFrame.Bcd_Sec = sec % 60;

	if (state.frmFpgaTimeInied == 0)
	{
		updateFrame.UpdateFlag = 0xaa;
		//LogMsg.Stamp() << "frmFpgaTimeInied\n";
		state.forceSetStampDelay = 0;
	}
	else
	{
		if (state.frmFpgaForceUpdateSec)
		{
			updateFrame.UpdateFlag = 0xaa;
			LogMsg.Stamp() << "frmFpgaForceUpdateSec\n";
			state.forceSetStampDelay = 0;
		}
		else if (utcqlast != updateFrame.UtcUs_Q[0])
		{
			updateFrame.UpdateFlag = 0xbb;
			LogMsg.Stamp() << "frmFpgaForceUpdateQ\n";
		}
		else
		{
			updateFrame.UpdateFlag = 0;
		}
	}
	msg.Write(&updateFrame, &updateFrame.Sum_L - (uint8*)&updateFrame);
	msg.IntSend(0, FpgaMsgProc::E_CPU_FPGA_Time);
	state.frmFpgaTimeInied = state.recMoudlePowerInied;
	state.frmDownFpgaTimeUpdate = 0;
	state.frmFpgaForceUpdateSec = 0;
}

void spt::GzkSauDateUpdate::UpdateMainBoard(SalDateStamp& Stamp)
{
	SalDateStamp stamp = Stamp;
	GzkToolsDateUpdate::UpdateTimeInSampInt(stamp);
	SalDateStamp utcdate = stamp;
	//B码校时
	if ((DatePara::Instance().AdJustMode.Data() == DatePara::E_LIGHT_IRIG_B))
	{
		UpdateFromIrigB(utcdate);
	}
	else
	{
		output.HostBCodeCheckAlarm = 0;
		output.HostBCodePrecisionAlarm = 0;
		output.HostTPortAlarm = 0;
		output.HostTSrvAlarm = 0;
		output.HostContAlarm = 0;
	}
	if (SptIoProcess::Instance().AppFlags().blUnitRevert)//手动复归帧跳变	
	{
		if (output.HostContAlarm == 1)
		{
			output.HostContAlarm = 0;
		}
	}
	if (state.IrigBSynOk)
	{
		utcdate.q.q = 0xa00 | (utcdate.q.q & 0x0f);
	}
	else
	{
		utcdate.q.q = 0xa20;
	}
	if (state.isHmiSetStamp && (state.IrigBSynOk == 0))
	{
		String100B str;
		hmiSetStamp.ToStrHzFmt3(str);
		LogMsg.Stamp() << "isHmiSetStamp  == 1 " << str << "\n";
		stamp.Set((int64)hmiSetStamp.Us());
		state.frmFpgaForceUpdateSec = 1;
		SptDateTask::Instance().ForceUpdateHwRtc();
		state.isHmiSetStamp = 0;
		state.forceSetStampDelay = 0;
	}
	else
	{
		stamp = utcdate;
	}
	Stamp = stamp;
	UpdateFpgaTime();
}

void spt::GzkSauDateUpdate::UpdateSubBoard(SalDateStamp& Stamp)
{
	SalDateStamp stamp = Stamp;
	GzkToolsDateUpdate::UpdateTimeInSampInt(stamp);
	if (state.frmDateUpdate)
	{
		state.frmDateUpdate = 0;
		output.recFrameNum++;
		if (output.recFrameNum > 100)
		{
			state.recMoudlePowerInied = 1;
			SptApiStatus[E_SAS_HostSvSynState].Update(frmDate.muframe.SvSyn == 0xaaaa);
			MemCpy(&realTimerFpgaUtc, frmDate.muframe.utcSec, sizeof(realTimerFpgaUtc));
			if (state.frmFpgaTimeInied)
			{
				stamp.fromPriUtcCode(realTimerFpgaUtc.uSec, realTimerFpgaUtc.u_Fra_Q);
			}
		}
	}
	Stamp = stamp;
	UpdateFpgaTime();
}

const SalDateStamp& spt::SptDateTask::Now()
{
	return (const SalDateStamp&)localStamp;
}

void spt::SptDateTask::RecFpgaMsg(uint8* buf, uint32 MsgLen)
{
	if (update)
	{
		update->RecFpgaMsg(buf, MsgLen);
	}
}

bool8 spt::SptDateTask::HmiSetDateTime(const SalDateStamp& Stamp)
{
	if (localStamp.q.bits.isSyncErr)
	{
		return update->HmiSetDateTime(Stamp);
	}
	return 0;
}

void spt::SptDateTask::ForceUpdateHwRtc()
{
	forceUpdateHwRtc = 1;
}

void spt::SptDateTask::ForceGetRtcFromHw()
{
	if (update)
	{
		update->GetHwTime(localStamp);
	}
}

int32 spt::SptDateTask::OneLoop()
{
	MsSleep(500);
	if (localRtcSetMsTimer.Status() || forceUpdateHwRtc)
	{
		forceUpdateHwRtc = 0;
		SalDateStamp rtc;
		SalDateStamp tempStamp = localStamp;
		if (update)
		{
			update->GetHwTime(rtc);
			int64 dif = tempStamp.Us() - rtc.Us();
			if ((dif <= (int32)SalDateStamp::Dt1Second * -1) || ((dif >= SalDateStamp::Dt1Second * 1)))
			{
				update->SetHwTime(tempStamp);
			}
		}
		localRtcSetMsTimer.Restart();
	}
	else if (!localRtcSetMsTimer.IsEnable())
	{
		localRtcSetMsTimer.Enable(0);
		localRtcSetMsTimer.UpCnt(localRtcSetMsTimer.Mt1Minute * 1);
		localRtcSetMsTimer.Enable(1);
	}
	if ((DatePara::Instance().AdJustMode.Data() == DatePara::E_SNTP))
	{
		if (update)
		{
			SalDateStamp Stamp;
			Stamp.Now();
			update->UpdateTimeInTask(Stamp);
		}
	}
	return 0;
}

spt::SptDateTask::SptDateTask()
	:Task("tDate", TaskBasePriority - 10, 512 * 1024, E_T_FLOAT, E_ServiceCore)
{
	localStamp.Set((int64)0);
	localStamp.q.q = 0;
}

void spt::SptDateTask::UpdateStatus()
{
	if (update)
	{
		const DateUpdate::OutPut& o = update->Output();
		SptApiStatus[E_SAS_HostBCodeCheckAlarm].Update(o.HostBCodeCheckAlarm);
		SptApiStatus[E_SAS_HostBCodePrecisionAlarm].Update(o.HostBCodePrecisionAlarm);
		SptApiStatus[E_SAS_HostTPortAlarm].Update(o.HostTPortAlarm);
		SptApiStatus[E_SAS_HostTSrvAlarm].Update(o.HostTSrvAlarm);
		SptApiStatus[E_SAS_HostContAlarm].Update(o.HostContAlarm);
	}
}

SptDateTask& spt::SptDateTask::Instance()
{
	static SptDateTask inst;
	return inst;
}

void spt::SptDateTask::UpdateTimeInMsInt()
{
	if (update)
	{
		update->UpdateTimeInMsInt(localStamp);
		UpdateStatus();

	}
}

void spt::SptDateTask::UpdateTimeInSampInt()
{
	if (update)
	{
		update->UpdateTimeInSampInt(localStamp);
		UpdateStatus();
	}
}


int32 spt::SptDateTask::PowerUpIni(int32 Para)
{
	DatePara::Instance().PowerUpIni(Para);
	if (SptMain::Instance().AppCfg())
	{
		update = 0;
		E_HARDWARE hw = SptMain::Instance().AppCfg()->platform.hardware;
		//	E_SOFTWARE sw = SptMain::Instance().AppCfg()->platform.software;
		E_DEVTYPE de = SptMain::Instance().AppCfg()->platform.devtype;
		switch (hw)
		{
		case spt::EH_GZKLCD:
			break;
		case spt::EH_GZKSAULCD:
			break;
		case spt::EH_GZK35KVSMART:
		case spt::EH_GZK35KVP:
#ifdef WIN32_SIM
			update = new PcSimDateUpdate;
#else
			if (de == ED_TOOLS)
			{
				update = new GzkToolsDateUpdate;
			}
			else
			{
				update = new Gzk35kVDateUpdate(&localStamp);
			}
#endif
			break;
		case spt::EH_GZKCK:
			break;
		case spt::EH_GZKSAU:
			update = new GzkSauDateUpdate;
			break;
		default:
			break;
		}
	}
	else
	{
		update = 0;
	}
	ForceGetRtcFromHw();
	Task::PowerUpIni(0);
	Start();
	return 0;
}

void spt::PcSimDateUpdate::UpdateTimeInTask(SalDateStamp& Stamp)
{
}
