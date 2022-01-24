#ifndef SALFILE_H
#define SALFILE_H

namespace spt
{
#ifdef WIN32_SIM
#define CN_FILE_DivFlag	"\\"
#define CN_SYS_PATH	 ".\\SptSim"
#define CN_DATA_PATH	".\\SptSim"
#define CN_UPDATE1_FILE_ROOT CN_DATA_PATH "\\Update"
#define CN_CUR_ROOT CN_SYS_PATH
#elif defined(SYLIX_GZK)
#define CN_FILE_DivFlag	"/"
#define CN_SYS_PATH	  "/yaffs2"
#define CN_DATA_PATH	 "/media"
#define CN_UPDATE1_FILE_ROOT "/media/sdcard1/Update"
#define CN_CUR_ROOT	"/yaffs2/flash1/apps"
#endif // WIN32_SIM
#define CN_APPS_ROOT	CN_SYS_PATH CN_FILE_DivFlag "apps"
#define CN_USING_PATH	CN_DATA_PATH CN_FILE_DivFlag "Using"
#define CN_PARA_FILE_ROOT	CN_USING_PATH CN_FILE_DivFlag "Para"
#define CN_CFG_FILE_ROOT	CN_USING_PATH CN_FILE_DivFlag "Cfg"
#define CN_INFO_FILE_ROOT	CN_USING_PATH CN_FILE_DivFlag "Info"
#define CN_LOG_FILE_ROOT	CN_USING_PATH CN_FILE_DivFlag "Log"
#define CN_EVENT_FILE_ROOT	CN_USING_PATH CN_FILE_DivFlag "Event"
#define CN_SJRECORD_FILE_ROOT	CN_USING_PATH CN_FILE_DivFlag "SjRecord"
#define CN_STATUS_FILE_ROOT	CN_USING_PATH CN_FILE_DivFlag "Status"
#define CN_PRINT_FILE_ROOT	CN_USING_PATH CN_FILE_DivFlag "Printer"
#define CN_GMSSL_FILE_ROOT	CN_USING_PATH CN_FILE_DivFlag "GmSsl"
#define CN_FWRECORD_FILE_ROOT	CN_USING_PATH CN_FILE_DivFlag "FwRecord"
#define CN_T860_FILE_ROOT	CN_USING_PATH CN_FILE_DivFlag "T860"
#define CN_T860_CFG_FILE_ROOT CN_T860_FILE_ROOT CN_FILE_DivFlag "Public" CN_FILE_DivFlag "configuration"
#define CN_T860_COMTRADE_FILE_ROOT CN_T860_FILE_ROOT CN_FILE_DivFlag "Public" CN_FILE_DivFlag "COMTRADE"
#define CN_T860_Private_FILE_ROOT CN_T860_FILE_ROOT CN_FILE_DivFlag "Private" 
#define CN_BAK_FILE_ROOT	CN_USING_PATH CN_FILE_DivFlag "Bakup"
#define CN_BAK_FLASH_FILE_ROOT	CN_BAK_FILE_ROOT CN_FILE_DivFlag "Flash"
#define CN_UPDATE_FILE_ROOT	 CN_DATA_PATH CN_FILE_DivFlag "Update"

	class FilePath
	{
	public:
#ifdef WIN32_SIM
		static const char DivFlag = '\\';
#else 
		static const char DivFlag = '/';
#endif // WIN32_SIM

	public:
		void Set(FilePath& Path);
		void Set(const char* Path);
		const char* Path() { return buf; }
		void Creat();
		void Remove();
		void Copy(const FilePath& Sur);
		void ToLocal();
	private:
		void creat(const char* dir);
	private:
		char buf[200];
	};
	class FileName
	{
	public:
		void Set(const char* Path);
		const char* Name() { return buf; }
	private:
		char buf[100];
	};

	class SalFile
	{
	public:
		void SetFullName(const char* File);
		void FullName(SalString& Name);
		FilePath& Path();
		FileName& Name();
		bool8 Open(const char* Mode);
		bool8 OpenReadOnly();
		bool8 OpenAppend();
		bool8 OpenRw();
		bool8 Creat();
		void Close();
		bool8 IsOpened();
		bool8 IsExist();
		bool8 Delete();
		int32 Read(void* Buf, int32 BufLen);
		int32 ReadLine(char* Buf, int32 BufLen);
		int32 ReadLine(SalString& Str);
		int32 Write(void* Buf, int32 BufLen);
		int32 Write(const char* Buf);
		int32 Write(SalString& Buf);
		int32 WriteLine(const char* Buf);
		uint16 GetCrc(uint32 Len);
		uint16 GetCrc();
		bool8 Copy(SalFile& File);
		bool8 Copy(const char* OldFile);
		bool8 AppendSize(int32 Len);
		enum E_Seek
		{
			E_SET = 0,//起始位置
			E_CUR = 1,//当前位置
			E_END = 2,//结束位置
		};
		int32 Seek(int32 seek, int32 OffSet);
		int32 SeekLineNext(const char* Line);
		int32 Size();
		bool8 Encry(uint8 seed);
		bool8 Decry(uint8 seed);
	public:
		SalFile();
		~SalFile();
	protected:
		FilePath path;
		FileName name;
		void* handle;
	};
	class SalDir
	{
	public:
		enum FileType
		{
			FT_DIR = 1,
			FT_FILE = 2,
		};
		struct Dirent
		{
			int64 creatT;
			int64 accessT;
			int64 writeT;
			int64 size;
			uint32 type;      /* the type of fname,1 is file, 2 is dir*/
			char fname[256];          /* file name (null-terminated)*/
		};
	public:
		SalDir();
		~SalDir();
		bool8 OpenDir(const char* Name);
		const Dirent* ReadNext();
		bool8 CloseDir();
		bool8 IsOpened();
	protected:
		bool8 opened;
		Dirent curDir;
		char path[256];
		char dirbuf[512];
		void* dir;
	};
	void PrintFile2Hex(const char* FullName);
}

#include"SalCfgFile.h"



#endif//SALFILE_H
