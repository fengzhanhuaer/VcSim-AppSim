#ifndef SALVERSION_H
#define SALVERSION_H

namespace spt
{
	struct SptVersion
	{
		uint64 progOk;//校验标志0x5a5a5a5aa5a5a5a5
		uint64 preamble;//前导码
		uint32 binSize;//bin内容大小
		uint32 fileSize;//bin文件大小
		uint16 crc;//按照bin内容进行的crc_modbus校验
		uint16 major;//主版本号，主框架更新时变动
		uint16 minor;//次要版本号，功能调试增减时变动
		uint16 reversion;//修正版本号，修正bug时变动
		int64 datetimeus;//公元1年1月1日 00:00:00至今的us数
		char programName[35];//程序名称
		char publisher[35];//程序发布者
		void FillInfo(uint32 fileSize, uint16 Major, uint16 Minor, uint16 Reversion, const char* ProName, const char* Publisher, const char* DateTime);
		void FillInfo(uint16 Major, uint16 Minor, uint16 Reversion, const char* Publisher, const char* Date, const char* Time);
		void ToStr(SalString& Str)const;
		void SetOk(bool8 ok);
		bool8 IsProgOk()const;
	};

	union SptVersionFile
	{
		SptVersion version;
		char buf[4096];
		void Fill(SptVersion& Version);
	};

	class ProgBinFile
	{
	public:
		static bool8 CreatBin(const char* FileName, SptVersion& Version);
		static bool8 GetVersion(const char* FileName, SptVersion& Version);
	};

}

#endif // !SALVERSION_H

