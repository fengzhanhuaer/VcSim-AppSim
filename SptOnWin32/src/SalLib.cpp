#include "SptProject.h"
using namespace spt;
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#ifdef WIN32_SIM
#pragma  warning(disable:4996)
#include<memory.h>
#include"windows.h"
#include"direct.h"
#include"io.h"
#elif defined(SYLIX_GZK)
#include <pthread.h>
#include <SylixOS.h>
VOID    API_TimeMSleep(ULONG   ulMSeconds);
#endif

int32 spt::StrCmp(const char* Dst, const char* Sur)
{
	if (Dst == Sur)
	{
		return 0;
	}
	if (Dst && Sur)
	{
		return strcmp(Dst, Sur);
	}
	return -1;
}


int32 spt::StrLen(const char* Msg)
{
	if (!Msg)
	{
		return 0;
	}
	return strlen(Msg);
}

#if 0
#include<string>
void MkGbkTable()
{
	char buf[40];
	char dst[40];
	SalFile file;
	file.Path().Set(CN_CUR_ROOT);
	file.Name().Set("SalFontCode.c");
	file.Creat();
	file.WriteLine("const uint16 GbkFirstByteLen = 0xff-0x81;");
	file.WriteLine("const uint16 GbkSecondByteLen = 0xff-0x40;");
	file.WriteLine("uint16 Gbk2Unicode[GbkFirstByteLen][GbkSecondByteLen]=");
	file.WriteLine("{");
	String5000B str;
	uint16 min = 0XFFFF;
	uint16 max = 0;
	for (uint32 i = 0x81; i < 0xff; i++)
	{
		str.Clear();
		str << "	{";

		for (uint32 j = 0x40; j < 0xff; j++)
		{
			buf[0] = (char)i;
			buf[1] = (char)j;
			buf[2] = (char)0;
			if (0 >= MultiByteToWideChar(CP_ACP, 0, buf, -1, (wchar_t*)dst, sizeof(dst) / 2))
			{
				dst[0] = '?';
				dst[1] = 0;
			}
			else
			{
				uint16 v = ((uint8)dst[1] << 8) + (uint8)dst[0];
			}
			str << "0x";
			str.FormatHex((uint8)dst[1]);
			str.FormatHex((uint8)dst[0]);
			str << ",";
		}
		str << "},";
		file.WriteLine(str.Str());
	}
	file.WriteLine("};");
	file.Close();
}
#endif
#if 1
const uint16 GbkFirstByteLen = 0xff - 0x81;
const uint16 GbkSecondByteLen = 0xff - 0x40;
extern uint16 Gbk2Unicode[GbkFirstByteLen][GbkSecondByteLen];
int32 spt::StrGBK2UCS2(uint16* Dst, const char* Sur, int32 BufUint16Size)
{
	uint16* dst = Dst;
	uint8* sur = (uint8*)Sur;
	int32 len = 0;
	if (sur && dst)
	{
		while (*sur)
		{
			if (len >= BufUint16Size)
			{
				*dst = 0;
				break;
			}
			if ((uint8)sur[0] < 0x80)
			{
				*dst = *sur++;
			}
			else if (((uint8)sur[0] >= (uint8)0x81) && ((uint8)sur[0] < (uint8)0xff) && ((uint8)sur[1] < (uint8)0xff) && ((uint8)sur[1] >= (uint8)0x40))
			{
				*dst = Gbk2Unicode[(uint8)((uint8)sur[0] - (uint8)0x81)][(uint8)((uint8)sur[1] - (uint8)0x40)];
				sur += 2;
			}
			else
			{
				*dst = 0;
				len = -1;
				break;
			}
			len++;
			dst++;
		}
		if (len < BufUint16Size)
		{
			*dst = 0;
		}
	}
	else
	{
		return -1;
	}
	return len;
}
int32 spt::StrGBK2UTF8(char* Dst, const char* Sur, int32 BufLen)
{
	uint8* dst = (uint8*)Dst;
	uint8* sur = (uint8*)Sur;
	int32 len = 0;
	uint16 code = 0;
	if (sur && dst)
	{
		while (*sur)
		{
			code = 0;
			if (len >= BufLen)
			{
				*dst = 0;
				break;
			}
			if ((uint8)sur[0] < (uint8)0x80)
			{
				code = *sur++;
			}
			else if (((uint8)sur[0] >= (uint8)0x81) && ((uint8)sur[0] < (uint8)0xff) && ((uint8)sur[1] < (uint8)0xff) && ((uint8)sur[1] >= (uint8)0x40))
			{
				code = Gbk2Unicode[(uint8)((uint8)sur[0] - (uint8)0x81)][(uint8)((uint8)sur[1] - (uint8)0x40)];
				sur += 2;
			}
			else
			{
				*dst = 0;
				len = -1;
				break;
			}
			if (code <= 0x7f)
			{
				*dst++ = (uint8)code;
			}
			else if (code <= 0x7ff)
			{
				*dst++ = 0xc0 | ((code >> 6) & 0x1f);
				*dst++ = 0x80 | (code & 0x3f);
			}
			else
			{
				*dst++ = 0xe0 | ((code >> 12) & 0xf);
				*dst++ = 0x80 | (((code & 0xfff) >> 6) & 0x3f);
				*dst++ = 0x80 | (code & 0x3f);
			}
			len++;
		}
		if (len < BufLen)
		{
			*dst = 0;
		}
	}
	else
	{
		return -1;
	}
	return len;
}
#endif
const char* spt::StrStr(const char* Msg, const char* SubMsg)
{
	return strstr(Msg, SubMsg);
}
void spt::Replace(char* Sur, char Flag, char NewFlag)
{
	if (Flag == 0)
	{
		return;
	}
	if (!Sur)
	{
		return;
	}
	while (*Sur)
	{
		if (*Sur == Flag)
		{
			*Sur = NewFlag;
		}
		Sur++;
	}
}
int32 spt::PosOf(const char* Context, char flag, int No)
{
	int32 cnt = 0;
	if (No > 0)
	{
		const char* sur = Context;
		for (int i = 0; i < 2048; i++)
		{
			if (*sur)
			{
				if (*sur == flag)
				{
					cnt++;
					if (cnt == No)
					{
						return i;
					}
				}
				sur++;
			}
			else
			{
				return -1;
			}
		}
	}
	else if (No < 0)
	{
		const char* sur = Context;
		sur += StrLen(Context) - 1;
		while (sur >= Context)
		{
			if (*sur)
			{
				if (*sur == flag)
				{
					cnt--;
					if (cnt == No)
					{
						return sur - Context;
					}
				}
				sur--;
			}
			else
			{
				return -1;
			}
		}
	}
	return -1;
}
char* spt::StrNCpy(char* Dst, const char* Sur, int32 BufLen)
{
	if (!(Dst && Sur))
	{
		if (Dst)
		{
			Dst[0] = 0;
		}
		return 0;
	}
	char* dst = Dst;
	int32 i;
	for (i = 0; i < BufLen; i++)
	{
		if (!*Sur)
		{
			*dst = 0;
			break;
		}
		*dst++ = *Sur++;
	}
	if (i == BufLen)
	{
		dst--;
		*dst = 0;
	}
	return Dst;
}
char* spt::StrNCat(char* Dst, const char* Sur, int32 BufLen)
{
	if (!(Dst && Sur))
	{
		return 0;
	}
	char* dst = Dst;
	int32 i;
	for (i = 0; i < BufLen; i++)
	{
		if (!*Dst)
		{
			break;
		}
		Dst++;
	}
	for (; i < BufLen; i++)
	{
		if (*Sur)
		{
			*Dst++ = *Sur++;
		}
		else
		{
			*Dst = 0;
			break;
		}
	}
	if (i == BufLen)
	{
		Dst--;
		*Dst = 0;
	}
	return dst;
}
int32 spt::StrNCmp(char* Dst, const char* Sur, int32 BufLen)
{
	if (!(Dst && Sur))
	{
		return 0;
	}
	return strncmp(Dst, Sur, BufLen);
}

void spt::MsSleep(int32 ms)
{
#ifdef WIN32_SIM
	::Sleep(ms);
#elif defined(SYLIX_GZK)
	API_TimeMSleep(ms);
#endif
}
int32 spt::Access(const char* Dir, int Mode)
{
#ifdef WIN32_SIM
	return _access(Dir, Mode);
#elif defined(SYLIX_GZK)
	return access(Dir, Mode);
#endif
}

int32 spt::MemCmp(const char* Dst, const char* Sur, uint32 Len)
{
	return memcmp(Dst, Sur, Len);
}
void spt::MemSet(void* Sur, int Val, uint32 Len)
{
	char* sur = (char*)Sur;
	if (Sur == 0)
	{
		return;
	}
	while (Len--)
	{
		*sur++ = (char)Val;
	}
}
static void MemCpyLess8(char*& dst, const char*& sur, uint32 Len)
{
	switch (Len)
	{
	case 8:
	{
		*dst++ = *sur++;
	}
	case 7:
	{
		*dst++ = *sur++;
	}
	case 6:
	{
		*dst++ = *sur++;
	}
	case 5:
	{
		*dst++ = *sur++;
	}
	case 4:
	{
		*dst++ = *sur++;
	}
	case 3:
	{
		*dst++ = *sur++;
	}
	case 2:
	{
		*dst++ = *sur++;
	}
	case 1:
	{
		*dst++ = *sur++;
	}
	}
}
static void MemCpyLess8(uint32*& dst, const uint32*& sur, uint32 Len)
{
	switch (Len)
	{
	case 8:
	{
		*dst++ = *sur++;
	}
	case 7:
	{
		*dst++ = *sur++;
	}
	case 6:
	{
		*dst++ = *sur++;
	}
	case 5:
	{
		*dst++ = *sur++;
	}
	case 4:
	{
		*dst++ = *sur++;
	}
	case 3:
	{
		*dst++ = *sur++;
	}
	case 2:
	{
		*dst++ = *sur++;
	}
	case 1:
	{
		*dst++ = *sur++;
	}
	}
}
void spt::MemCpy(void* Dst, const void* Sur, uint32 Len)
{
	const char* sur = (char*)Sur;
	char* dst = (char*)Dst;
	if ((Sur && Dst) == 0)
	{
		return;
	}
	if (Len <= 8)
	{
		MemCpyLess8(dst, sur, Len);
	}
	else if (Len <= 16)
	{
		MemCpyLess8(dst, sur, 8);
		Len -= 8;
		MemCpyLess8(dst, sur, Len);
	}
	else if (((uint32)dst & 0x03) == ((uint32)sur & 0x03))
	{
		uint32 sw = (uint32)dst & 0x03;
		switch (sw)
		{
		case 1:
		{
			*dst++ = *sur++;
			*dst++ = *sur++;
			*dst++ = *sur++;
			Len -= 3;
			break;
		}
		case 2:
		{
			*dst++ = *sur++;
			*dst++ = *sur++;
			Len -= 2;
			break;
		}
		case 3:
		{
			*dst++ = *sur++;
			Len -= 1;
			break;
		}
		}
		uint32* udst = (uint32*)((uint32)dst);
		const uint32* usur = (uint32*)((uint32)sur);
		uint32 loop = Len >> 2;
		uint32 gend = loop << 2;
		while (loop > 8)
		{
			MemCpyLess8(udst, usur, 8);
			loop -= 8;
		}
		MemCpyLess8(udst, usur, loop);
		sur = sur + gend;
		dst = dst + gend;
		Len -= gend;
		MemCpyLess8(dst, sur, Len);
	}
	else
	{
		while (Len > 8)
		{
			MemCpyLess8(dst, sur, 8);
			Len -= 8;
		}
		MemCpyLess8(dst, sur, Len);
	}
}
bool8 spt::IsAlpha(unsigned char Data)
{
	if ((Data >= 'A') && (Data <= 'Z'))
	{
		return 1;
	}
	if ((Data >= 'a') && (Data <= 'z'))
	{
		return 1;
	}
	return 0;
}

bool8 spt::IsUpAlpha(unsigned char Data)
{
	if ((Data >= 'A') && (Data <= 'Z'))
	{
		return 1;
	}
	return 0;
}

bool8 spt::IsLowAlpha(unsigned char Data)
{
	if ((Data >= 'a') && (Data <= 'z'))
	{
		return 1;
	}
	return 0;
}

bool8 spt::IsNember(unsigned char Data)
{
	if ((Data >= '0') && (Data <= '9'))
	{
		return 1;
	}
	return 0;
}

bool8 spt::IsPunct(unsigned char Data)
{
	return ispunct(Data);
}

bool8 spt::IsAscii(unsigned char Data)
{
	if (Data < 0x7f)
	{
		return 1;
	}
	return 0;
}

bool8 spt::IsSpace(unsigned char Data)
{
	return isspace(Data);
}

bool8 spt::IsGraph(unsigned char Data)
{
	return isgraph(Data);
}

void* spt::Calloc(uint32 ElementNum, uint32 ElementSize)
{
	return calloc(ElementNum, ElementSize);
}

int spt::Free(void* Buf)
{
	free(Buf);
	return 0;
}

int32 spt::TaskLock()
{
#ifdef WIN32_SIM
	return 0;
#elif defined(SYLIX_GZK)
	return Lw_Thread_Lock();
#endif
	return 0;
}

int32 spt::TaskUnLock()
{
#ifdef WIN32_SIM
	return 0;
#elif defined(SYLIX_GZK)
	return Lw_Thread_Unlock();
#endif
	return 0;
}

int32 spt::MkDir(const char* Dir)
{

#ifdef WIN32_SIM
	return mkdir(Dir);
#elif defined(SYLIX_GZK)
	return mkdir(Dir, 0);
#endif
}

int32 spt::RemoveDir(const char* Dir)
{
	return rmdir(Dir);
}
int32 spt::RemoveFile(const char* file)
{
	return remove(file);
}

int32 spt::Rename(char* oldname, char* newname)
{
	return rename(oldname, newname);
}

spt::SemaphoreB::SemaphoreB()
{
	handle = 0;
}

spt::SemaphoreB::~SemaphoreB()
{
#ifdef WIN32_SIM
	CloseHandle(handle);
#elif defined(SYLIX_GZK)
	Lw_SemaphoreB_Delete((LW_OBJECT_HANDLE*)&handle);
#endif
}
void* spt::SemaphoreB::Creat(int IniVal)
{
#ifdef WIN32_SIM
	return handle = CreateSemaphore(0, IniVal, 1, 0);
#elif defined(SYLIX_GZK)
	return handle = (void*)Lw_SemaphoreB_Create(0, IniVal, LW_OPTION_WAIT_FIFO | LW_OPTION_OBJECT_LOCAL, 0);
#endif // WIN32_SIM

}
int32 spt::SemaphoreB::Wait(int32 timeOut)
{
#ifdef WIN32_SIM
	if (timeOut == -1)
	{
		timeOut = INFINITE;
	}

	int32 res = WaitForSingleObject(handle, timeOut);

	if (res == 0)
	{
		return 0;
	}

	return -1;
#elif defined(SYLIX_GZK)
	if (timeOut == -1)
	{
		timeOut = LW_OPTION_WAIT_INFINITE;
	}
	timeOut = (timeOut * LW_OPTION_WAIT_A_SECOND / 1000);
	int32 res = Lw_SemaphoreB_Wait((LW_OBJECT_HANDLE)handle, timeOut);

	if (res == ERROR_NONE)
	{
		return 0;
	}

	return -1;
#endif // WIN32_SIM

}

int32 spt::SemaphoreB::Post()
{
#ifdef WIN32_SIM
	return int32(ReleaseSemaphore(handle, 1, 0));
#elif defined(SYLIX_GZK)
	return Lw_SemaphoreB_Post((LW_OBJECT_HANDLE)handle);
#endif // WIN32_SIM

}

spt::SemaphoreC::SemaphoreC()
{
	handle = 0;
}

spt::SemaphoreC::~SemaphoreC()
{
#ifdef WIN32_SIM
	CloseHandle(handle);
#elif defined(SYLIX_GZK)
	Lw_SemaphoreC_Delete((LW_OBJECT_HANDLE*)&handle);
#endif
}

void* spt::SemaphoreC::Creat(int IniVal, int MaxVal)
{
#ifdef WIN32_SIM
	return handle = CreateSemaphore(0, IniVal, MaxVal, 0);
#elif defined(SYLIX_GZK)
	return  handle = (void*)Lw_SemaphoreC_Create(0, IniVal, MaxVal, LW_OPTION_WAIT_FIFO | LW_OPTION_OBJECT_LOCAL, 0);
#endif // WIN32_SIM
}

int32 spt::SemaphoreC::Wait(int32 timeOut)
{
#ifdef WIN32_SIM
	if (timeOut == -1)
	{
		timeOut = INFINITE;
	}

	int32 res = WaitForSingleObject(handle, timeOut);

	if (res == 0)
	{
		return 0;
	}

	return -1;
#elif defined(SYLIX_GZK)
	if (timeOut == -1)
	{
		timeOut = LW_OPTION_WAIT_INFINITE;
	}
	timeOut = (timeOut * LW_OPTION_WAIT_A_SECOND / 1000);
	int32 res = Lw_SemaphoreC_Wait((LW_OBJECT_HANDLE)handle, timeOut);

	if (res == ERROR_NONE)
	{
		return 0;
	}

	return -1;
#endif // WIN32_SIM
}

int32 spt::SemaphoreC::Post()
{
#ifdef WIN32_SIM
	return int32(ReleaseSemaphore(handle, 1, 0));
#elif defined(SYLIX_GZK)
	return Lw_SemaphoreC_Release((LW_OBJECT_HANDLE)handle, 1, 0);
#endif // WIN32_SIM
}

int32 spt::SemaphoreC::Post(int Val)
{
#ifdef WIN32_SIM
	return int32(ReleaseSemaphore(handle, Val, 0));
#elif defined(SYLIX_GZK)
	return Lw_SemaphoreC_Release((LW_OBJECT_HANDLE)handle, Val, 0);
#endif // WIN32_SIM
}


