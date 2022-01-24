#include "SptProject.h"
using namespace spt;
#include<string.h>

#if WIN_SIM
#pragma  warning(disable:4996)
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
char* spt::StrStr(char* Msg, char* SubMsg)
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
#ifdef WIN32_SIM
#include"windows.h"
#include"direct.h"
#include"io.h"
#elif defined(SYLIX_GZK)
#include <pthread.h>
#include <SylixOS.h>
VOID    API_TimeMSleep(ULONG   ulMSeconds);
#endif
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
#else 
	return 0;
#endif
}

int32 spt::MemCmp(const char* Dst, const char* Sur, uint32 Len)
{
	return memcmp(Dst, Sur, Len);
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
#ifdef WIN32_SIM
	return ispunct(Data);
#else 
	return 0;
#endif
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
#ifdef WIN32_SIM
	return isspace(Data);
#else 
	return 0;
#endif
}

bool8 spt::IsGraph(unsigned char Data)
{
#ifdef WIN32_SIM
	return isgraph(Data);
#else 
	return 0;
#endif
}

void* spt::Calloc(uint32 ElementNum, uint32 ElementSize)
{
#ifdef WIN32_SIM
	return calloc(ElementNum, ElementSize);
#elif defined(SYLIX_GZK)
	return calloc(ElementNum, ElementSize);
#else 
	return 0;
#endif
}

int spt::Free(void* Buf)
{
#ifdef WIN32_SIM
	free(Buf);
#elif defined(SYLIX_GZK)
	free(Buf);
#else 

#endif
	return 0;
}

int32 spt::MkDir(const char* Dir)
{

#ifdef WIN32_SIM
	return mkdir(Dir);
#elif defined(SYLIX_GZK)
	return mkdir(Dir, 0);
#else 
	return 0;
#endif
}

int32 spt::RemoveDir(const char* Dir)
{
#ifdef WIN32_SIM
	return rmdir(Dir);
#else 
	return 0;
#endif
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
#else 

#endif
}
void* spt::SemaphoreB::Creat(int IniVal)
{

#ifdef WIN32_SIM
	return handle = CreateSemaphore(0, IniVal, 1, 0);
#elif defined(SYLIX_GZK)
	return handle = (void*)Lw_SemaphoreB_Create(0, IniVal, LW_OPTION_WAIT_FIFO | LW_OPTION_OBJECT_LOCAL, 0);
#else 
	return 0;
#endif

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
#else 
	return -1;
#endif

}

int32 spt::SemaphoreB::Post()
{
#ifdef WIN32_SIM
	return int32(ReleaseSemaphore(handle, 1, 0));
#elif defined(SYLIX_GZK)
	return Lw_SemaphoreB_Post((LW_OBJECT_HANDLE)handle);
#else 
	return -1;
#endif

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
#else 
	return 0;
#endif
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
#else 
	return -1;
#endif
}

int32 spt::SemaphoreC::Post()
{
#ifdef WIN32_SIM
	return int32(ReleaseSemaphore(handle, 1, 0));
#elif defined(SYLIX_GZK)
	return Lw_SemaphoreC_Release((LW_OBJECT_HANDLE)handle, 1, 0);
#else 
	return -1;
#endif
}

int32 spt::SemaphoreC::Post(int Val)
{
#ifdef WIN32_SIM
	return int32(ReleaseSemaphore(handle, Val, 0));
#elif defined(SYLIX_GZK)
	return Lw_SemaphoreC_Release((LW_OBJECT_HANDLE)handle, Val, 0);
#else 
	return -1;
#endif
}


