#include "SptProject.h"
using namespace spt;

spt::CfgFile::CfgFile()
{
	DataNum = 0;
}

PCfgDataBase* spt::CfgFile::CfgPool()
{
	return 0;
}

uint32 spt::CfgFile::CfgPoolSize()
{
	return 0;
}

bool8 spt::CfgFile::AddCfgData(PCfgDataBase pData)
{
	PCfgDataBase* pool = CfgPool();
	if (!pool)
	{
		return 0;
	}
	uint32 size = CfgPoolSize();
	if (DataNum >= size)
	{
		return 0;
	}
	pool[DataNum++] = pData;
	return 1;
}

uint32 spt::CfgFile::CfgDataNum()
{
	PCfgDataBase* pool = CfgPool();
	if (!pool)
	{
		return DataNum = 0;
	}
	uint32 size = CfgPoolSize();
	if (DataNum >= size)
	{
		DataNum = size;
		return 0;
	}
	return DataNum;
}

int32 spt::CfgFile::ReadAll()
{
	if (!Open("r"))
	{
		return -1;
	}
	PCfgDataBase* pool = CfgPool();
	if (!pool)
	{
		Close();
		DataNum = 0;
		return -1;
	}
	uint32 size = CfgPoolSize();
	if (DataNum >= size)
	{
		DataNum = size;
	}

	int num = 0;
	for (uint32 i = 0; i < DataNum; i++)
	{
		num += pool[i]->ReadFromFile(*this);
	}
	Close();
	return num;
}

int32 spt::CfgFile::SaveAll()
{
	if (!Open("wb"))
	{
		Path().Creat();
		if (!Open("wb"))
		{
			return -1;
		}
	}
	PCfgDataBase* pool = CfgPool();
	if (!pool)
	{
		Close();
		DataNum = 0;
		return -1;
	}
	uint32 size = CfgPoolSize();
	if (DataNum >= size)
	{
		DataNum = size;
	}

	int num = 0;
	for (uint32 i = 0; i < DataNum; i++)
	{
		num += pool[i]->Save2File(*this);
	}
	Close();
	return num;
}

int32 spt::CfgFile::ValueToEditBuf()
{
	PCfgDataBase* pool = CfgPool();
	if (!pool)
	{
		Close();
		DataNum = 0;
		return -1;
	}
	for (uint32 i = 0; i < DataNum; i++)
	{
		pool[i]->ValueToEditBuf();
	}
	return 0;
}

int32 spt::CfgFile::EditBufToValue()
{
	PCfgDataBase* pool = CfgPool();
	if (!pool)
	{
		Close();
		DataNum = 0;
		return -1;
	}
	for (uint32 i = 0; i < DataNum; i++)
	{
		pool[i]->EditBufToValue();
	}
	return 0;
}

bool8 spt::CfgFile::Get(const char* Name, bool8& Data)
{
	uint32 data = 0;
	bool8 res = Get(Name, data);
	if (res)
	{
		Data = (data == 1);
	}

	return res;
}

bool8 spt::CfgFile::Get(const char* Name, int32& Data)
{
	char buf[30];
	bool8 res = Get(Name, buf, sizeof(buf));
	if (res != 1)
	{
		return 0;
	}
	TransString ts;
	ts.SetBuf(buf);
	ts.Get(Data, 0);
	return 1;
}

bool8 spt::CfgFile::Get(const char* Name, uint32& Data)
{
	char buf[30];
	bool8 res = Get(Name, buf, sizeof(buf));
	if (res != 1)
	{
		return 0;
	}
	TransString ts;
	ts.SetBuf(buf);
	ts.Get(Data, 0);
	return 1;
}

bool8 spt::CfgFile::GetHex(const char* Name, uint32& Data)
{
	char buf[30];
	bool8 res = Get(Name, buf, sizeof(buf));
	if (res != 1)
	{
		return 0;
	}
	TransString ts;
	ts.SetBuf(buf);
	ts.GetHex(Data, 0);
	return 1;
}

bool8 spt::CfgFile::Get(const char* Name, char* Buf, int32 BufLen)
{
	if ((!Name) || (!Buf))
	{
		return 0;
	}
	char buf[400];


	const char* data = 0;

	while (ReadLine(buf, sizeof(buf)) > 0)
	{
		if ((data = SelectByName(Name, buf)) != 0)
		{
			break;
		}
	}
	if (!data)
	{
		Seek(E_SET, 0);
		while (ReadLine(buf, sizeof(buf)) > 0)
		{
			if ((data = SelectByName(Name, buf)) != 0)
			{
				break;
			}
		}
	}
	if (data)
	{
		StrNCpy(Buf, data, BufLen);
		return 1;
	}
	return 0;
}

bool8 spt::CfgFile::Get(CfgStr& Data)
{
	return Get(Data.Name(), Data.StrData(), Data.StrDataBufLen());
}

const char* spt::CfgFile::SelectByName(const char* Name, const char* Source)
{
	const char* sur = Source;
	if (sur[0] == '/')
	{
		if (sur[1] == '/')
		{
			if (sur[2] == '/')
			{
				return 0;
			}
			return 0;
		}
	}

	if (!Name)
	{
		return 0;
	}
	if (!Source)
	{
		return 0;
	}
	const char* name = Name;
	while (*name)
	{
		if (*name != *sur)
		{
			return 0;
		}
		name++;
		sur++;
	}
	if (*sur != '=')
	{
		return 0;
	}
	sur++;
	const char* data = sur;

	while (*sur)
	{
		if ((sur[0] == '/') && (sur[1] == '/') && (sur[2] == '/'))
		{
			*(char*)sur = 0;
			*(char*)(sur + 1) = 0;
			break;
		}
		sur++;
	}
	while (sur > data)
	{
		if (sur[0] == ' ')
		{
			*(char*)sur = 0;
		}
		else if (sur[0] == '	')
		{
			*(char*)sur = 0;
		}
		else if (sur[0] == 0)
		{
			*(char*)sur = 0;
		}
		else
		{
			break;
		}
		sur--;
	}
	return data;
}
