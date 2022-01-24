#ifndef SALVERSION_H
#define SALVERSION_H

namespace spt
{
	struct SptVersion
	{
		uint64 progOk;//校验标志0x5a5a5a5aa5a5a5a5
		uint64 preamble;//前导码0x12fa990
		uint32 binSize;//bin内容大小
		uint32 fileSize;//bin文件大小
		uint32 crc;//按照bin内容进行的crc_modbus校验
		uint32 major;//主版本号，主框架更新时变动
		uint32 minor;//次要版本号，功能调试增减时变动
		uint32 reversion;//修正版本号，修正bug时变动
		int64 datetimeus;//公元1年1月1日 00:00:00至今的us数
		char programName[35];//程序名称
		char publisher[35];//程序发布者
		void FillInfo(uint32 fileSize, uint16 Major, uint16 Minor, uint16 Reversion, const char* ProName, const char* Publisher, const char* DateTime);
		void FillInfo(uint32 fileSize, uint16 Major, uint16 Minor, uint16 Reversion, const char* ProName, const char* Publisher, int64 DateTime);
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
	struct SalComVersion
	{
		/// <summary>
		/// 格式1:10234显示为1.02.34简写为2.34
		/// 1 软硬件平台版本，例如ARM版程序，X86版程序
		/// 02 表示功能版本,例如增加GOOSE发送功能版本版本号应进行变动
		/// 34 表示修正版本，例如修改GOOSE发送异常的某Bug
		/// 格式2:0114560234显示为14.56.01.02.34简写为2.34
		/// 01 软硬件平台版本，例如ARM版程序，X86版程序(0~42)
		/// 14 应用类别，例如光差、母线、变压器
		/// 56 程序类别，例如测试版本、某省份版本、常规版本等
		/// 02 表示功能版本,例如增加GOOSE发送功能版本版本号应进行变动
		/// 34 表示修正版本，例如修改GOOSE发送异常的某Bug
		/// </summary>
		uint32 ProgVersion;//通信过程中可以按照16位或32位传输
		uint32 ProgCrc;//校验码,通信过程中可以按照16位或32位传输
		/// <summary>
		/// 发布日期
		/// format 0x19900816
		/// </summary>
		uint32 ProgDate;
		uint32 RtCrc;//程序实时校验码,通信过程中可以按照16位或32位传输
		char programName[16];//程序名称
		/// <summary>
		/// 设置名称
		/// </summary>
		/// <param name="Name"></param>
		void SetName(const char* Name);
		/// <summary>
		/// 格式化输出字符串
		/// V1.00 19900816 A6B0C9D8
		/// </summary>
		/// <param name="Str"></param>
		/// <returns></returns>
		int32 RtInfoStrFmt2(SalString& Str)const;
		/// <summary>
		/// 格式化输出字符串
		/// V1.23.15.1.00 19900816 A6B0C9D8
		/// </summary>
		/// <param name="Str"></param>
		/// <returns></returns>
		int32 RtInfoStrFmt1(SalString& Str)const;
		void ToStr1(SalString& Str)const;
		void ToStr2(SalString& Str)const;
	};
}

#endif // !SALVERSION_H

