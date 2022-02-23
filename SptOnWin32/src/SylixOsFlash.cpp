#include "ApiProject.h"
using namespace spt;
#ifdef SYLIX_GZK
extern "C"
{
	typedef int(*Process)(int Step, const char* info);
	int spiFlashRead(uint32  ulAddr, uint32  ulLen, void* pvData);
	int spiFlashWrite(uint32  ulAddr, uint32  ulLen, void* pvData);
	int  spiFlashErase(uint32  ulAddr, uint32  iLen);
	int  spiFlashWriteEx(uint32  ulAddr, uint32  uiLen, void* pvData);
}
const uint32  pagesize = (4 * 1024);
const uint32  sylix_boot0_start_addr = 0;//boot0起始地址
const uint32  sylix_boot0_max_size = 64 * 1024;
const uint32  sylix_boot0_end_addr = sylix_boot0_start_addr + sylix_boot0_max_size;//不含
const uint32  sylix_uboot_start_addr = sylix_boot0_end_addr;//uboot起始地址
const uint32  sylix_uboot_max_size = 1728 * 1024;//1728k
const uint32  sylix_uboot_end_addr = sylix_uboot_start_addr + sylix_uboot_max_size;//不含
const uint32  sylix_res_section_start_addr = sylix_uboot_end_addr;//1792*1024,保留区,供boot及sylix使用
const uint32  sylix_res_section_end_addr = 2 * 1024 * 1024;
const uint32  sylix_res_section_max_size = sylix_res_section_end_addr - sylix_res_section_start_addr;//256k
const uint32  sylix_start_addr = sylix_res_section_end_addr;//主操作系统起始地址
const uint32  sylix_bin_max_size = 5 * 1024 * 1024;
const uint32  sylix_end_addr = sylix_start_addr + sylix_bin_max_size;
const uint32  sylix_bak_start_addr = sylix_res_section_end_addr + sylix_bin_max_size;//备用操作系统起始地址
const uint32  sylix_bak_end_addr = sylix_bak_start_addr + sylix_bin_max_size;//主操作系统起始地址
const uint32  sylix_para_start_addr = sylix_bak_end_addr;//用户参数区起始地址12*1024*1024
const uint32  sylix_para_max_size = 4 * 1024 * 1024;
const uint32  sylix_para_end_addr = sylix_para_start_addr + sylix_para_max_size;
int SimSysStartUp()
{
	return 0;
}


bool8 CheckSylix(uint32 startAddr, uint32 binMax)
{
	char buf[pagesize];
	uint32 total = 0;
	uint16 crc = 0;
	SptVersion version;
	spiFlashRead(startAddr + binMax - pagesize, sizeof(version), &version);

	if (version.binSize >= binMax)
	{
		LogErr.Stamp() << "sylix bin size is too long " << version.binSize << "\n";
		return 0;
	}
	spiFlashRead(startAddr + total, pagesize, buf);
	total += pagesize;
	crc = Crc16ModBus.CalCrc(buf, pagesize);
	uint32 len = 0;
	while (total < version.binSize)
	{
		len = version.binSize - total;
		if (len > pagesize)
		{
			len = pagesize;
		}
		spiFlashRead(startAddr + total, len, buf);
		crc = Crc16ModBus.CalCrc(crc, buf, len);
		total += len;
	}
	if (crc == version.crc)
	{
		return 1;
	}
	else
	{
		LogErr.Stamp() << "sylix bin crc err " << version.crc << "!=" << crc << "\n";
		return 0;
	}
	return 0;
}
void CheckSylix(uint32 startAddr, uint32 binMax, SptVersion& Version)
{
	spiFlashRead(startAddr + binMax - pagesize, sizeof(Version), &Version);

	if (CheckSylix(startAddr, binMax))
	{
		Version.SetOk(1);
	}
	else
	{
		Version.SetOk(0);
	}
}
extern "C" void ieslab_get_version(uint32 * revision_out, char** url_out, char** date_out);
void spt::ApiVersionInfo::UpdateInfo()
{
	CheckSylix(sylix_boot0_start_addr, sylix_boot0_max_size, boot0);
	CheckSylix(sylix_uboot_start_addr, sylix_uboot_max_size, uboot);
	CheckSylix(sylix_start_addr, sylix_bin_max_size, mainSys);
	CheckSylix(sylix_bak_start_addr, sylix_bin_max_size, bakSys);
}
int32 UpdateOneOS(SalFile& fos, int& Step, const char* SptOsName, uint32 binMax, uint32 startAddr, Process process)
{
	fos.Seek(fos.E_SET, 0);
	String40B outInfo;
	uint32 total = 0;
	spiFlashErase(startAddr, binMax);
	int percent = 0, lastpercent = 0;

	total = 0;
	const uint32 writesize = 64 * 1024;
	char buf[writesize];
	while (total < binMax)
	{
		fos.Read(buf, sizeof(buf));
		spiFlashWrite(startAddr + total, writesize, buf);
		total += writesize;
		percent = total * 100 / binMax;
		if (percent != lastpercent)
		{
			lastpercent = percent;
			outInfo = SptOsName;
			outInfo << "写入中 ";
			outInfo << percent << "%";
			if (process)
			{
				process(Step, outInfo.Str());
			}
		}
	}
	Step++;
	outInfo = SptOsName;
	outInfo << "校验中";
	if (process)
	{
		process(Step, outInfo.Str());
	}
	LogMsg.Stamp() << outInfo << "\n";
	if (CheckSylix(startAddr, binMax))
	{
		SptVersion version;
		spiFlashRead(startAddr + binMax - pagesize, sizeof(version), &version);
		version.SetOk(1);
		spiFlashWriteEx(startAddr + binMax - pagesize, sizeof(version), &version);
		outInfo = SptOsName;
		outInfo << "校验正常(";
		outInfo.FormatHex(version.crc) << ")";
		LogMsg.Stamp() << outInfo << "\n";
		if (process)
		{
			process(Step, outInfo.Str());
		}
	}
	else
	{
		outInfo = SptOsName;
		outInfo << "校验异常";
		LogWarn.Stamp() << outInfo << "\n";
		if (process)
		{
			process(Step, outInfo.Str());
		}

		return -1;
	}
	return 0;
}
int UpdateProgram(const char* Prog, const char* Name, int& Step, uint32 binMax, uint32 startAddr, Process process)
{
	String40B outInfo;
	SalFile fos;
	fos.SetFullName(Prog);
	fos.Open("rb");

	if (!fos.IsOpened())
	{
		outInfo = fos.Name().Name();
		outInfo << "不存在";

		if (process)
		{
			process(Step, outInfo.Str());
		}
		LogWarn.Stamp() << outInfo << "\n";
		return -1;
	}
	outInfo = "开始升级";
	outInfo << fos.Name().Name();

	if (process)
	{
		process(Step, outInfo.Str());
	}
	LogMsg.Stamp() << outInfo << "\n";;
	Step++;
	int res = UpdateOneOS(fos, Step, Name, binMax, startAddr, process);
	LogMsg.Stamp() << "\n";
	return res;
}
int32 UpdateOS(const char* SptOsName, Process process)
{
	int res = 0;
	int Step = 0;
	res += UpdateProgram(SptOsName, "主系统", Step, sylix_bin_max_size, sylix_start_addr, process);
	Step++;
	res += UpdateProgram(SptOsName, "备用系统", Step, sylix_bin_max_size, sylix_bak_start_addr, process);
	if (process)
	{
		Step++;
		process(Step, "按任意键继续");
	}
	return res;
}
int32 BakupFlash(const char* Name, int& Step, uint32 startAddr, uint32 maxsize, Process process)
{
	String40B outInfo;
	SalFile fos;
	fos.SetFullName(Name);
	fos.Creat();
	if (!fos.IsOpened())
	{
		outInfo = fos.Name().Name();
		outInfo << "打开文件失败.";
		LogWarn.Stamp() << outInfo << "\n";
		if (process)
		{
			process(Step, outInfo.Str());
		}

		return -1;
	}

	uint32 total = 0;
	int percent = 0, lastpercent = 0;
	char buf[pagesize];
	while (total < maxsize)
	{
		spiFlashRead(startAddr + total, sizeof(buf), buf);
		fos.Write(buf, sizeof(buf));
		total += pagesize;
		percent = total * 100 / maxsize;
		if (percent != lastpercent)
		{
			lastpercent = percent;
			outInfo = fos.Name().Name();
			outInfo << "备份中 ";
			outInfo << percent << "%";
			if (process)
			{
				process(Step, outInfo.Str());
			}
			LogMsg.Stamp() << outInfo << "\n";
		}
	}
	return 0;
}
extern "C"
{
	int UpdateOsForLcd(const char* SptOsName, int (*Process)(int Step, const char* info))
	{
		int res = UpdateOS(SptOsName, Process);

		return res;
	}
	int UpdateBoot0ForLcd(const char* SptOsName, int (*Process)(int Step, const char* info))
	{
		int Step = 0;
		int res = UpdateProgram(SptOsName, "Boot0", Step, sylix_boot0_max_size, sylix_boot0_start_addr, Process);
		if (Process)
		{
			Step++;
			Process(Step, "按任意键继续");
		}
		return res;
	}
	int UpdateUBootForLcd(const char* SptOsName, int (*Process)(int Step, const char* info))
	{
		int Step = 0;
		int res = UpdateProgram(SptOsName, "UBoot", Step, sylix_uboot_max_size, sylix_uboot_start_addr, Process);
		if (Process)
		{
			Step++;
			Process(Step, "按任意键继续");
		}
		return res;
	}
	int BakUpFlashForLcd(int (*Process)(int Step, const char* info))
	{
		int32 res = 0;
		int Step = 0;
		String100B str;
		str = CN_BAK_FLASH_FILE_ROOT;
		str << "/boot0.bin";
		res += BakupFlash(str.Str(), Step, sylix_boot0_start_addr, sylix_boot0_max_size, Process);
		Step++;
		str = CN_BAK_FLASH_FILE_ROOT;
		str << "/uboot.bin";
		res += BakupFlash(str.Str(), Step, sylix_uboot_start_addr, sylix_uboot_max_size, Process);
		Step++;
		str = CN_BAK_FLASH_FILE_ROOT;
		str << "/res.bin";
		res += BakupFlash(str.Str(), Step, sylix_res_section_start_addr, sylix_res_section_max_size, Process);
		Step++;
		str = CN_BAK_FLASH_FILE_ROOT;
		str << "/sylix.main.bin";
		res += BakupFlash(str.Str(), Step, sylix_start_addr, sylix_bin_max_size, Process);
		Step++;
		str = CN_BAK_FLASH_FILE_ROOT;
		str << "/sylix.bak.bin";
		res += BakupFlash(str.Str(), Step, sylix_bak_start_addr, sylix_bin_max_size, Process);
		Step++;
		str = CN_BAK_FLASH_FILE_ROOT;
		str << "/para.bin";
		res += BakupFlash(str.Str(), Step, sylix_para_start_addr, sylix_para_max_size, Process);
		Step++;
		String40B outInfo;
		if (res == 0)
		{
			outInfo = "备份成功";
			LogMsg.Stamp() << outInfo;
			if (Process)
			{
				Process(Step, outInfo.Str());
			}
		}
		else
		{
			outInfo = "备份失败";
			LogMsg.Stamp() << outInfo;
			if (Process)
			{
				Process(Step, outInfo.Str());
			}
		}
		if (Process)
		{
			Step++;
			Process(Step, "按任意键继续");
		}
		return res;
	}
	int RestoreFlash(const char* Name, int& Step, uint32 startAddr, uint32 maxsize, int (*process)(int Step, const char* info))
	{
		String40B outInfo;
		SalFile fos;
		fos.SetFullName(Name);
		fos.Open("rb");

		if (!fos.IsOpened())
		{
			outInfo = fos.Name().Name();
			outInfo << "不存在";
			LogWarn.Stamp() << outInfo << "\n";
			if (process)
			{
				process(Step, outInfo.Str());
			}
			return -1;
		}
		outInfo = "开始还原";
		outInfo << fos.Name().Name();
		LogMsg.Stamp() << outInfo << "\n";
		if (process)
		{
			process(Step, outInfo.Str());
		}
		Step++;
		fos.Seek(fos.E_SET, 0);
		uint32 total = 0;
		int percent = 0, lastpercent = 0;

		LogWarn.Stamp() << outInfo;
		total = 0;
		char buf[pagesize];
		while (total < maxsize)
		{
			fos.Read(buf, sizeof(buf));
			spiFlashWriteEx(startAddr + total, pagesize, buf);
			total += pagesize;
			percent = total * 100 / maxsize;
			if (percent != lastpercent)
			{
				lastpercent = percent;
				outInfo = "写入中 ";
				outInfo << percent << "%";
				if (process)
				{
					process(Step, outInfo.Str());
				}
			}
		}
		Step++;
		outInfo = "还原完成";
		outInfo << fos.Name().Name();
		LogMsg.Stamp() << outInfo << "\n";
		if (process)
		{
			process(Step, outInfo.Str());
		}
		return 0;
	}
	extern "C" int RestoreFlashPara(int (*Process)(int Step, const char* info))
	{
		int Step = 0;
		String100B str;
		str = CN_BAK_FLASH_FILE_ROOT;
		str << "/para.bin";
		int res = RestoreFlash(str.Str(), Step, sylix_para_start_addr, sylix_para_max_size, Process);
		if (Process)
		{
			Step++;
			Process(Step, "请重启装置");
		}
		return res;
	}
	extern "C" int BspFormatSysCard(int Para);
	extern "C" int FormatSysCard(int (*Process)(int Step, const char* info))
	{
		int Step = 0;
		if (Process)
		{
			Process(Step, "开始格式化请稍等");
		}
		Step++;

		int res = BspFormatSysCard(0);

		FilePath fps;
		String100B sur;
		sur = CN_APPS_ROOT;
		fps.Set(sur.Str());

		FilePath fpd;
		String100B dst;
		dst = CN_BAK_FILE_ROOT;
		dst << fpd.DivFlag;
		dst << "apps";
		fpd.Set(dst.Str());
		fpd.Remove();
		fpd.Creat();
		String100B str;
		if (res)
		{
			str = "系统盘格式化失败。";
		}
		else
		{
			str = "系统盘格式化成功。";
			fps.Copy(fpd);
		}
		LogMsg << str << "\n";
		if (Process)
		{
			Process(Step, str.Str());
			Step++;
			Process(Step, "按任意键继续");
			Step++;
		}
		return res;
	}
	extern "C" int BspFormatDataCard(int Para);
	extern "C" int FormatDataCard(int (*Process)(int Step, const char* info))
	{
		int Step = 0;
		if (Process)
		{
			Process(Step, "开始格式化请稍等");
		}
		Step++;
		int res = BspFormatDataCard(0);
		String100B str;
		if (res)
		{
			str = "数据盘格式化失败。";
		}
		else
		{
			str = "数据盘格式化成功。";
		}
		LogMsg << str << "\n";
		if (Process)
		{
			Process(Step, str.Str());
			Step++;
			Process(Step, "请重启装置!");
			Step++;
		}
		return res;
	}

}
#else
extern "C" int UpdateOsForLcd(const char* SptOsName, int (*Process)(int Step, const char* info))
{
	String40B outInfo;
	for (size_t i = 0; i < 100; i++)
	{
		outInfo.Clear();
		outInfo << i;
		if (Process)
		{
			Process(1, outInfo.Str());
		}
		MsSleep(100);
	}
	return 0;
}
extern "C" int BakUpFlashForLcd(int (*Process)(int Step, const char* info))
{
	String40B outInfo;
	for (size_t i = 0; i < 100; i++)
	{
		outInfo.Clear();
		outInfo << i;
		if (Process)
		{
			Process(1, outInfo.Str());
		}
		MsSleep(100);
	}
	return 0;
}
extern "C" int FormatSysCard(int (*Process)(int Step, const char* info))
{
	String40B outInfo;
	for (size_t i = 0; i < 100; i++)
	{
		outInfo.Clear();
		outInfo << i;
		if (Process)
		{
			Process(1, outInfo.Str());
		}
		MsSleep(100);
	}
	return 0;
}
extern "C" int FormatDataCard(int (*Process)(int Step, const char* info))
{
	String40B outInfo;
	for (size_t i = 0; i < 100; i++)
	{
		outInfo.Clear();
		outInfo << i;
		if (Process)
		{
			Process(1, outInfo.Str());
		}
		MsSleep(100);
	}
	return 0;
}
extern "C" int UpdateBoot0ForLcd(const char* SptOsName, int (*Process)(int Step, const char* info))
{
	String40B outInfo;
	for (size_t i = 0; i < 100; i++)
	{
		outInfo.Clear();
		outInfo << i;
		if (Process)
		{
			Process(1, outInfo.Str());
		}
		MsSleep(100);
	}
	return 0;
}
extern "C" int UpdateUBootForLcd(const char* SptOsName, int (*Process)(int Step, const char* info))
{
	String40B outInfo;
	for (size_t i = 0; i < 100; i++)
	{
		outInfo.Clear();
		outInfo << i;
		if (Process)
		{
			Process(1, outInfo.Str());
		}
		MsSleep(100);
	}
	return 0;
}
extern "C" int RestoreFlashPara(int (*Process)(int Step, const char* info))
{
	String40B outInfo;
	for (size_t i = 0; i < 100; i++)
	{
		outInfo.Clear();
		outInfo << i;
		if (Process)
		{
			Process(1, outInfo.Str());
		}
		MsSleep(100);
	}
	return 0;
}

#endif//SYLIX_GZK




