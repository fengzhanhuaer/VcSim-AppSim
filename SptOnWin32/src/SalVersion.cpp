#include "SptProject.h"
#include "SalVersion.h"
using namespace spt;

void spt::SptVersion::FillInfo(uint32 FileSize, uint16 Major, uint16 Minor, uint16 Reversion, const char* ProName, const char* Publisher, const char* DateTime)
{
	SalRtc date;
	date.FromStrFmt1(DateTime);
	FillInfo(FileSize, Major, Minor, Reversion, ProName, Publisher, date.Stamp());
}
void spt::SptVersion::FillInfo(uint32 FileSize, uint16 Major, uint16 Minor, uint16 Reversion, const char* ProName, const char* Publisher, int64 DateTime)
{
	MemSet(this, 0, sizeof(*this));
	progOk = 0;
	preamble = 0x12fa990;
	fileSize = (uint32)FileSize;
	major = Major;
	minor = Minor;
	reversion = Reversion;
	StrNCpy(programName, ProName, sizeof(programName));
	StrNCpy(publisher, Publisher, sizeof(publisher));
	datetimeus = DateTime;
}
void spt::SptVersion::FillInfo(uint16 Major, uint16 Minor, uint16 Reversion, const char* Publisher, const char* Date, const char* Time)
{
	MemSet(this, 0, sizeof(*this));
	progOk = 0;
	preamble = 0x12fa990;
	major = Major;
	minor = Minor;
	reversion = Reversion;
	StrNCpy(publisher, Publisher, sizeof(publisher));
	SalRtc date;
	date.FromStrBuild(Date, Time);
	datetimeus = date.Stamp();
}

void spt::SptVersion::ToStr(SalString& Str)const
{
	Str << "ProgName :" << programName << "\n";
	Str << "Publisher:" << publisher << "\n";
	Str << "Version  :" << "V" << major << "." << minor << "." << reversion << "\n";
	if (IsProgOk())
	{
		Str << "CheckFlag:" << "OK\n";
	}
	else
	{
		Str << "CheckFlag:" << "Err\n";
	}
	SalRtc date;
	date.FromStamp(datetimeus);
	String100B info;
	date.ToStrFmt1(info);
	Str << "DateTime :" << info << "\n";

	Str << "ProgCrc  :";
	Str.FormatHex(crc) << "\n";
	Str << "BinSize  :";
	Str.Format(binSize, 12, ' ') << "\n";
	Str << "FileSize :";
	Str.Format(fileSize, 12, ' ') << "\n\n";
}
void  spt::SptVersion::SetOk(bool8 ok)
{
	if (ok == 1)
	{
		progOk = 0x5a5a5a5aa5a5a5a5;
	}
	else
	{
		progOk = 0;
	}
}

bool8 spt::SptVersion::IsProgOk()const
{
	return 0x5a5a5a5aa5a5a5a5 == progOk;
}

bool8 spt::ProgBinFile::CreatBin(const char* FileName, SptVersion& Version)
{
	SalFile sur, dst;
	sur.SetFullName(FileName);
	sur.Open("rb");
	if (!sur.IsOpened())
	{
		return 0;
	}

	uint32 size = sur.Size();
	SptVersionFile ver;
	if ((size + sizeof(ver)) >= Version.fileSize)
	{
		return 0;
	}
	Version.binSize = size;
	Version.crc = sur.GetCrc(size);
	dst.Path().Set(sur.Path());
	char buf[200];
	String200B str;
	str = Version.programName;
	str << ".V" << Version.major << "." << Version.minor << "." << Version.reversion << "(";
	str.FormatHex((uint16)Version.crc) << ").bin";
	StrNCpy(buf, str.Str(), sizeof(buf));
	dst.Name().Set(buf);
	dst.Open("wb");
	dst.Copy(sur);
	dst.AppendSize(Version.fileSize - sizeof(ver));
	ver.Fill(Version);
	dst.Write(&ver, sizeof(ver));
	dst.Close();
	return 1;
}

bool8 spt::ProgBinFile::GetVersion(const char* FileName, SptVersion& Version)
{
	SalFile sur, dst;
	sur.SetFullName(FileName);
	sur.Open("rb");
	if (!sur.IsOpened())
	{
		return 0;
	}

	uint32 size = sur.Size();
	SptVersionFile ver;
	if (size < sizeof(ver))
	{
		return 0;
	}
	sur.Seek(sur.E_END, -(int32)sizeof(ver));
	sur.Read(&ver, sizeof(ver));
	MemCpy(&Version, &ver, sizeof(Version));
	if (Version.preamble != 0x12fa990)
	{
		return 0;
	}
	return 1;
}

void spt::SptVersionFile::Fill(SptVersion& Version)
{
	MemSet(buf, 0, sizeof(buf));
	MemCpy(&version, &Version, sizeof(Version));
}

int32 spt::SalComVersion::RtInfoStrFmt1(SalString& Str) const
{
	Str << "V";
	uint32 temp = ProgVersion;
	uint32 v1 = temp % 100;
	temp = temp / 100;
	uint32 v2 = temp % 100;
	temp = temp / 100;

	Str.Format(v2, 2, '0') << ".";
	Str.Format(v1, 2, '0') << " ";
	Str.FormatHex(ProgDate) << " ";
	Str.FormatHex(ProgCrc);
	return Str.StrLen();
}

void spt::SalComVersion::ToStr1(SalString& Str) const
{
	Str.Format((const char*)programName, 16, 1, ' ') << ":";
	RtInfoStrFmt1(Str);
	Str << "\n";
}

void spt::SalComVersion::ToStr2(SalString& Str) const
{
	Str.Format((const char*)programName, 16, 1, ' ') << ":";
	RtInfoStrFmt2(Str);
	Str << "\n";
}

void spt::SalComVersion::SetName(const char* Name)
{
	StrNCpy(programName, Name, sizeof(programName));
}

int32 spt::SalComVersion::RtInfoStrFmt2(SalString& Str) const
{
	Str << "V";
	uint32 temp = ProgVersion;
	uint32 v1 = temp % 100;
	temp = temp / 100;
	uint32 v2 = temp % 100;
	temp = temp / 100;
	uint32 v3 = temp % 100;
	temp = temp / 100;
	uint32 v4 = temp % 100;
	temp = temp / 100;
	uint32 v5 = temp % 100;
	temp = temp / 100;

	Str.Format(v5, 2, '0') << ".";
	Str.Format(v4, 2, '0') << ".";
	Str.Format(v3, 2, '0') << ".";
	Str.Format(v2, 2, '0') << ".";
	Str.Format(v1, 2, '0') << " ";
	Str.FormatHex(ProgDate) << " ";
	Str.FormatHex(ProgCrc);
	return Str.StrLen();
}
