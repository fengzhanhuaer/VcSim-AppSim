#include "SptProject.h"
using namespace spt;

#include<stdio.h>
#include<sys/stat.h>
#ifdef WIN32_SIM
#include <sys/types.h>
#include <io.h>  
#include <direct.h>
#elif defined(SYLIX_GZK)
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#endif

void spt::FilePath::Set(FilePath& Path)
{
	Set(Path.Path());
}

void spt::FilePath::Set(const char* Path)
{
	if (Path == 0)
	{
		buf[0] = 0;
		return;
	}
	StrNCpy(buf, Path, sizeof(buf));
}

void spt::FilePath::Creat()
{
	creat(buf);
}

void spt::FilePath::Remove()
{
	spt::RemoveDir(buf);
}

void spt::FilePath::Copy(const FilePath& Sur)
{



}

void spt::FilePath::ToLocal()
{
	char old = 0;
	char newc = DivFlag;
	if (DivFlag == '\\')
	{
		old = '/';
	}
	else
	{
		old = '\\';
	}
	for (uint32 i = 0; i < sizeof(buf); i++)
	{
		if (!buf[i])
		{
			break;
		}
		if (old == buf[i])
		{
			buf[i] = newc;
		}
	}
}

void spt::FilePath::creat(const char* dir)
{
	if (0 == Access(dir, 0))
	{
		return;
	}
	else
	{
		char parent[200];
		StrNCpy(parent, dir, sizeof(parent));
		int pos = PosOf(parent, DivFlag, -1);
		if (pos > 0)
		{
			parent[pos] = 0;
			creat(parent);
		}
		MkDir(dir);
	}
}

void spt::FileName::Set(const char* Path)
{
	if (Path == 0)
	{
		buf[0] = 0;
		return;
	}
	StrNCpy(buf, Path, sizeof(buf));
}

void spt::SalFile::SetFullName(const char* File)
{
	char parent[200];
	StrNCpy(parent, File, sizeof(parent));
	int pos = PosOf(parent, path.DivFlag, -1);
	if (pos > 0)
	{
		parent[pos] = 0;
		path.Set(parent);
		if (StrLen(File) > pos)
		{
			name.Set(parent + pos + 1);
		}
		else
		{
			name.Set(0);
		}
	}
	else
	{
		path.Set(0);
		name.Set(File);
	}

}

void spt::SalFile::FullName(SalString& Name)
{
	char buf[200];

	StrNCpy(buf, path.Path(), sizeof(buf));
	char div[2] = { FilePath::DivFlag,0 };
	StrNCat(buf, div, sizeof(buf));
	StrNCat(buf, name.Name(), sizeof(buf));
	Name << buf;
}

spt::SalFile::SalFile()
{
	handle = 0;
}
spt::SalFile::~SalFile()
{
	Close();
}

FilePath& spt::SalFile::Path()
{
	return path;
}

FileName& spt::SalFile::Name()
{
	return name;
}

bool8 spt::SalFile::Open(const char* Mode)
{
	Close();
	char buf[200];

	StrNCpy(buf, path.Path(), sizeof(buf));
	char div[2] = { FilePath::DivFlag,0 };
	StrNCat(buf, div, sizeof(buf));
	StrNCat(buf, name.Name(), sizeof(buf));

	handle = fopen(buf, Mode);

	return handle != 0;
}

bool8 spt::SalFile::OpenReadOnly()
{
	return Open("rb");
}

bool8 spt::SalFile::OpenAppend()
{
	return Open("ab");
}

bool8 spt::SalFile::OpenRw()
{
	return Open("rw");
}

bool8 spt::SalFile::Creat()
{
	if (!Open("wb"))
	{
		path.Creat();
		Open("wb");
	}
	return handle != 0;
}
#ifdef SYLIX_GZK
extern "C" int fsync(int);
#endif // SYLIX_GZK
void spt::SalFile::Close()
{
	if (handle)
	{
		fflush((FILE*)handle);
#ifdef SYLIX_GZK
		int32 fd = fileno((FILE*)handle);
		fsync(fd);
#endif // SYLIX_GZK
		fclose((FILE*)handle);
		handle = 0;
	}
}

bool8 spt::SalFile::IsOpened()
{
	return handle != 0;
}

bool8 spt::SalFile::IsExist()
{
	if (handle)
	{
		return 1;
	}
	char buf[200];

	StrNCpy(buf, path.Path(), sizeof(buf));
	char div[2] = { FilePath::DivFlag,0 };
	StrNCat(buf, div, sizeof(buf));
	StrNCat(buf, name.Name(), sizeof(buf));
	return Access(buf, 0) == 0;
}

bool8 spt::SalFile::Delete()
{
	String200B fname;
	FullName(fname);
	Close();
	return RemoveFile(fname.Str());
}

int32 spt::SalFile::Read(void* Buf, int32 BufLen)
{
	if (!handle)
	{
		return -1;
	}
	return fread(Buf, 1, BufLen, (FILE*)handle);
}

int32 spt::SalFile::ReadLine(char* Buf, int32 BufLen)
{
	if (!handle)
	{
		return -1;
	}
	char* buf = fgets(Buf, BufLen, (FILE*)handle);
	if (buf)
	{
		while (*Buf)
		{
			if (*Buf == '\n')
			{
				*Buf = 0;
				break;
			}
			if (*Buf == '\r')
			{
				*Buf = 0;
				break;
			}
			Buf++;
		}
	}
	else
	{
		return -1;
	}

	return StrLen(buf);
}

int32 spt::SalFile::ReadLine(SalString& Str)
{
	if (!handle)
	{
		return -1;
	}
	int32 c;
	int32 Ln = Str.StrLen();
	while ((c = fgetc((FILE*)handle)) >= 0)
	{
		if (c == '\r')
		{
			if ((c = fgetc((FILE*)handle)) != '\n')
			{
				Seek(E_CUR, -1);
			}
			break;
		}
		else if (c == '\n')
		{
			break;
		}
		Str << (char)c;
	}
	return Str.StrLen() - Ln;
}

int32 spt::SalFile::Write(void* Buf, int32 BufLen)
{
	if (!handle)
	{
		return -1;
	}
	return fwrite(Buf, 1, BufLen, (FILE*)handle);
}

int32 spt::SalFile::Write(const char* Buf)
{
	int32 res = Write((void*)Buf, StrLen(Buf));
	return res;
}

int32 spt::SalFile::Write(SalString& Buf)
{
	return Write(Buf.Str(), Buf.StrLen());
}

int32 spt::SalFile::WriteLine(const char* Buf)
{
	int32 res = Write(Buf);
	Write("\r\n");
	return res;
}

uint16 spt::SalFile::GetCrc(uint32 Len)
{
	char buf[2048];
	uint32 total = 0;
	Seek(E_SET, 0);
	int32 s, m;
	uint16 crc = 0;
	bool8 first = 0;
	while (total < Len)
	{
		s = Read(buf, sizeof(buf));
		if (s > 0)
		{
			m = Len - total;
			if (m > s)
			{
				if (!first)
				{
					first = 1;
					crc = Crc16ModBus.CalCrc(buf, (uint32)s);
				}
				else
				{
					crc = Crc16ModBus.CalCrc(crc, buf, (uint32)s);
				}
				total += s;
			}
			else
			{
				if (!first)
				{
					first = 1;
					crc = Crc16ModBus.CalCrc(buf, (uint32)m);
				}
				else
				{
					crc = Crc16ModBus.CalCrc(crc, buf, (uint32)m);
				}
				total += m;
				break;
			}
		}
		else
		{
			break;
		}
	}
	MemSet(buf, 0, sizeof(buf));
	while (total < Len)
	{
		s = sizeof(buf);

		m = Len - total;
		if (m > s)
		{
			if (!first)
			{
				first = 1;
				crc = Crc16ModBus.CalCrc(buf, (uint32)s);
			}
			else
			{
				crc = Crc16ModBus.CalCrc(crc, buf, (uint32)s);
			}
			total += s;
		}
		else
		{
			if (!first)
			{
				first = 1;
				crc = Crc16ModBus.CalCrc(buf, (uint32)m);
			}
			else
			{
				crc = Crc16ModBus.CalCrc(crc, buf, (uint32)m);
			}
			total += m;
			break;
		}
	}
	return crc;
}

uint16 spt::SalFile::GetCrc()
{
	if (!IsOpened())
	{
		OpenReadOnly();
	}
	return GetCrc((uint32)Size());
}

bool8 spt::SalFile::Copy(SalFile& File)
{
	if (!File.IsOpened())
	{
		return 0;
	}
	File.Seek(E_SET, 0);

	char buf[1024];

	int s = 0;
	if (!IsOpened())
	{
		return 0;
	}
	while ((s = File.Read(buf, sizeof(buf))) > 0)
	{
		Write(buf, s);
	}
	return 1;
}

bool8 spt::SalFile::Copy(const char* OldFile)
{
	SalFile ofile;
	if (!IsOpened())
	{
		return 0;
	}
	ofile.SetFullName(OldFile);
	ofile.OpenReadOnly();
	if (!ofile.IsOpened())
	{
		return 0;
	}
	return Copy(ofile);
}

bool8 spt::SalFile::AppendSize(int32 Len)
{
	if (!handle)
	{
		return -1;
	}
	Seek(E_END, 0);
	char buf[1024];
	MemSet(buf, 0, sizeof(buf));
	int32 total = Size();
	if (total < 0)
	{
		return 0;
	}
	int32 len = 0;

	while (total < Len)
	{
		len = Len - total;
		if (len > (int32) sizeof(buf))
		{
			len = (int32)sizeof(buf);
		}
		Write(buf, len);
		total += len;
	}
	return 1;
}

int32 spt::SalFile::Seek(int32 seek, int32 OffSet)
{
	if (!handle)
	{
		return -1;
	}
	return fseek((FILE*)handle, OffSet, seek);
}

int32 spt::SalFile::SeekLineNext(const char* Line)
{
	Seek(E_SET, 0);
	char buf[1000];
	while (ReadLine(buf, sizeof(buf)) >= 0)
	{
		if (StrNCmp(buf, Line, sizeof(buf)) == 0)
		{
			return 0;
		}
	}
	return -1;
}

int32 spt::SalFile::Size()
{
	char buf[200];

	StrNCpy(buf, path.Path(), sizeof(buf));
	char div[2] = { FilePath::DivFlag,0 };
	StrNCat(buf, div, sizeof(buf));
	StrNCat(buf, name.Name(), sizeof(buf));
#ifdef WIN32_SIM
	struct _stat statbuf;
	_stat(buf, &statbuf);
	int size = statbuf.st_size;
#elif defined(SYLIX_GZK)
	struct stat statbuf;
	stat(buf, &statbuf);
	int size = statbuf.st_size;
#endif // WIN32_SIM

	return size;
}

bool8 spt::SalFile::Encry(uint8 seed)
{
	if (!handle)
	{
		OpenReadOnly();
	}
	else
	{
		Close();
		OpenReadOnly();
	}
	if (!IsOpened())
	{
		return 0;
	}
	AllocBuf buf(1);
	int32 size = Size();
	if (size <= 0)
	{
		return 0;
	}
	void* b = buf.Alloc((uint32)size, 1);
	if (!b)
	{
		return 0;
	}
	Read(buf.BufBase(), size);
	Close();
	Creat();
	EncryptData(buf.BufBase(), size, seed);
	Write(buf.BufBase(), size);
	Close();
	return 1;
}

bool8 spt::SalFile::Decry(uint8 seed)
{
	if (!handle)
	{
		OpenReadOnly();
	}
	else
	{
		Close();
		OpenReadOnly();
	}
	if (!IsOpened())
	{
		return 0;
	}
	AllocBuf buf(1);
	int32 size = Size();
	if (size <= 0)
	{
		return 0;
	}
	void* b = buf.Alloc((uint32)size, 1);
	if (!b)
	{
		return 0;
	}
	Read(buf.BufBase(), size);
	Close();
	Creat();
	DecryptData(buf.BufBase(), size, seed);
	Write(buf.BufBase(), size);
	Close();
	return 1;
}

void spt::PrintFile2Hex(const char* FullName)
{
	SalFile file;
	file.SetFullName(FullName);
	file.OpenReadOnly();
	uint8 buf;
	String5000B str;
	LogReal << FullName << " hex  is \n  ";
	while (file.Read(&buf, sizeof(buf)))
	{
		str.Clear();
		str << "0x";
		str.FormatHex(buf);
		LogReal << str << ",";
	}
	LogReal << "\n\n";
}
spt::SalDir::SalDir()
{
	opened = 0;
	dir = 0;
	MemSet(dirbuf, 0, sizeof(dirbuf));
	MemSet(path, 0, sizeof(path));
	MemSet(&curDir, 0, sizeof(curDir));
}
spt::SalDir::~SalDir()
{
	if (opened)
	{
		CloseDir();
	}
	dir = 0;
}

bool8 spt::SalDir::OpenDir(const char* Name)
{
	opened = 0;
	dir = 0;
	MemSet(dirbuf, 0, sizeof(dirbuf));
	MemSet(path, 0, sizeof(path));
	MemSet(&curDir, 0, sizeof(curDir));
#ifdef WIN32_SIM
	dir = 0;
	opened = 0;
	if (chdir(Name) < 0)
	{
		return opened;
	}
	opened = 1;
	StrNCpy(path, Name, sizeof(path));
	return opened;
#elif defined(SYLIX_GZK)

#endif
	return opened = 0;
}
const SalDir::Dirent* spt::SalDir::ReadNext()
{
#ifdef WIN32_SIM
	__finddata64_t* data = (__finddata64_t*)dirbuf;
	if (opened)
	{
		if (!dir)
		{
			char buf[1024];
			StrNCpy(buf, path, sizeof(buf));
			StrNCat(buf, "*", sizeof(buf));
			if (dir = (void*)_findfirst64(buf, (__finddata64_t*)data))
			{
			}
			else
			{
				opened = 0;
			}
		}
		else
		{
			intptr_t ddir;
			if (ddir = _findnext64((intptr_t)dir, (__finddata64_t*)data))
			{
				dir = (void*)ddir;
			}
			else
			{
				return 0;
			}
		}
		if (dir)
		{
			StrNCpy(curDir.fname, data->name, sizeof(curDir.fname));
			SalDateStamp stmp;
			if (data->time_create == -1)
			{
				stmp.fromUtcSec(data->time_write);
			}
			else
			{
				stmp.fromUtcSec(data->time_create);
			}
			curDir.creatT = stmp.Us();
			if (data->time_access == -1)
			{
				stmp.fromUtcSec(data->time_write);
			}
			else
			{
				stmp.fromUtcSec(data->time_access);
			}
			curDir.accessT = stmp.Us();
			stmp.fromUtcSec(data->time_write);
			curDir.writeT = stmp.Us();
			curDir.size = data->size;
			if (data->attrib & _A_SUBDIR)
			{
				curDir.type = FT_DIR;
			}
			else
			{
				curDir.type = FT_FILE;
			}
			return &curDir;
		}
	}
	return 0;
#elif defined(SYLIX_GZK)

#endif
	return 0;
}
bool8 spt::SalDir::CloseDir()
{

#ifdef WIN32_SIM
	if (opened)
	{
		if (dir)
		{
			_findclose((intptr_t)dir);
			dir = 0;
		}
		opened = 0;
	}
	return 1;
#elif defined(SYLIX_GZK)

#endif
	return 0;
}

bool8 spt::SalDir::IsOpened()
{
	return opened;
}


