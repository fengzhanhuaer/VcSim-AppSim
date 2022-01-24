#include "SptProject.h"
using namespace spt;

#include<stdio.h>
#include<sys/stat.h>

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

bool8 spt::SalFile::Creat()
{
	if (!Open("wb"))
	{
		path.Creat();
		Open("wb");
	}
	return handle != 0;
}

void spt::SalFile::Close()
{
	if (handle)
	{
		fflush((FILE*)handle);
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

}
#ifdef WIN32_SIM
#include <sys/types.h>
#include <windows.h>  
#include <direct.h>
typedef struct _dirdesc {
	HANDLE hFind;
	int     dd_fd;      /* file descriptor associated with directory */
	long    dd_loc;     /* offset in current buffer */
	long    dd_size;    /* amount of data returned by getdirentries */
	char* dd_buf;    /* data buffer */
	int     dd_len;     /* size of data buffer */
	long    dd_seek;    /* magic cookie returned by getdirentries */
} DIR;

# define __dirfd(dp)    ((dp)->dd_fd)

DIR* opendir(const char*);
struct dirent* readdir(DIR*);
void rewinddir(DIR*);
int closedir(DIR*);

DIR* opendir(const char* name)
{
	HANDLE hFind;
	DIR* dir;
	WIN32_FIND_DATAA FindData;
	char namebuf[512];
	if (name[0] == '.')
	{
		char pa[1024];
		char* res = getcwd((LPSTR)pa, sizeof(pa) / 2);
		snprintf(namebuf, sizeof(namebuf), "%s%s\\*.*", pa, &name[1]);
	}
	else
	{
		snprintf(namebuf, sizeof(namebuf), "%s\\*.*", &name[0]);
	}

	//	snprintf(namebuf, sizeof(namebuf), "%s", name);

	hFind = FindFirstFileA((LPCSTR)namebuf, &FindData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	dir = (DIR*)malloc(sizeof(DIR));

	if (!dir)
	{
		return 0;
	}

	memset(dir, 0, sizeof(DIR));
	dir->hFind = hFind;
	dir->dd_fd = 0;   // simulate return  

	return dir;
}

struct SalDir::Dirent* readdir(DIR* d, struct SalDir::Dirent& dirent)
{
	int i;
	BOOL bf;
	WIN32_FIND_DATAA FileData;
	if (!d)
	{
		return 0;
	}
findnext:
	bf = FindNextFileA(d->hFind, &FileData);
	//fail or end  
	if (!bf)
	{
		return 0;
	}
	if (FileData.cFileName[0] == '.')
	{
		goto findnext;
	}

	for (i = 0; i < 256; i++)
	{
		dirent.d_name[i] = (char)FileData.cFileName[i];
		if (FileData.cFileName[i] == '\0') break;
	}
	dirent.d_reclen = i;
	dirent.d_reclen = (uint16)FileData.nFileSizeLow;

	//check there is file or directory  
	if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		dirent.d_type = 2;
	}
	else
	{
		dirent.d_type = 1;
	}
	return (&dirent);
}

int closedir(DIR* d)
{
	if (!d)
	{
		return -1;
	}
	FindClose(d->hFind);
	d->hFind = 0;
	free(d);
	return 0;
}

#endif
#ifdef WIN32_SIM
const SalDir::Dirent* spt::SalDir::ReadDir(Dirent* Dir)
{
#ifndef GZK_LCD
	if (readdir((DIR*)this->dir, *Dir))
	{
		String500B str;
		str = parentPath;
		str << CN_FILE_DivFlag << Dir->d_name;
		struct stat s;
		int res = stat(str.Str(), &s);
		SalDate date;
		int64 t = s.st_mtime * SalDate::Dt1Second;
		date.FromUtc(t);
		Dir->time = date.Stamp();
		Dir->size = s.st_size;
		return Dir;
	}
#endif 
	return 0;
}

#else
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
const SalDir::Dirent* spt::SalDir::ReadDir(Dirent* Dir)
{
	struct dirent* ptr;
	ptr = readdir((DIR*)this->dir);
	if (ptr)
	{
		StrNCpy(Dir->d_name, ptr->d_name, sizeof(Dir->d_name));
		Dir->d_type = ptr->d_type;
		if (S_ISDIR(Dir->d_type))
		{
			Dir->d_type = 2;
		}
		else
		{
			Dir->d_type = 1;
		}
		struct stat s;
		stat(Dir->d_name, &s);
		SalDate date;
		date.FromUtc(s.st_mtime);
		Dir->time = date.Stamp();
		if (Dir->d_type == 1)
		{
			Dir->size = s.st_size;
		}
		return Dir;
	}
	return 0;
}
#endif 
// WIN32_SIM
spt::SalDir::SalDir()
{
	opened = 0;
	dir = 0;
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
	dir = opendir(Name);
	StrNCpy(parentPath, Name, sizeof(parentPath));
	return opened = (dir != 0);
}



bool8 spt::SalDir::CloseDir()
{
	if (opened)
	{
		closedir((DIR*)dir);
		opened = 0;
	}
	return 0;
}

bool8 spt::SalDir::IsOpened()
{
	return opened;
}

const char* spt::SalDir::GetAbsolutePath(char* Dst, const char* Sur, uint32 BufLen)
{
	if (Sur[0] == '.')
	{
		char pa[1024];
#ifdef WIN32_SIM
		char* res = getcwd((LPSTR)pa, sizeof(pa) / 2);

#else
		char* res = getcwd(pa, sizeof(pa));
#endif
		if (res)
		{
			snprintf(Dst, BufLen, "%s%s", pa, &Sur[1]);
		}
		else
		{
			;
		}
	}
	else
	{
		snprintf(Dst, BufLen, "%s", &Sur[0]);
	}
	return Dst;
}


