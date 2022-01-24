#ifndef SALCFGFILE_H
#define SALCFGFILE_H

#include "SalCfgData.h"

namespace spt
{
	typedef CfgDataBase* PCfgDataBase;
	class CfgFile :public SalFile
	{
	public:
		CfgFile();
	public:
		virtual PCfgDataBase* CfgPool();
		virtual uint32 CfgPoolSize();
		bool8 AddCfgData(PCfgDataBase pData);
		uint32 CfgDataNum();
		int32 ReadAll();
		int32 SaveAll();
		int32 ValueToEditBuf();
		int32 EditBufToValue();
	public:
		bool8 Get(const char* Name, bool8& Data);
		bool8 Get(const char* Name, int32& Data);
		bool8 Get(const char* Name, uint32& Data);
		bool8 GetHex(const char* Name, uint32& Data);
		bool8 Get(const char* Name, char* Buf, int32 BufLen);
		bool8 Get(CfgStrDataBase& Data);
	protected:
		const char* SelectByName(const char* Name, const char* Source);
	protected:
		uint32 DataNum;
	};


}

#endif // !SALCFGFILE_H

