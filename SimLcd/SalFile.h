#ifndef SALFILE_H
#define SALFILE_H

namespace spt
{
#ifdef WIN32_SIM
#define CN_FILE_DivFlag	"\\"
#define CN_APPS_ROOT	".\\apps"
#define CN_USING_PATH	".\\SptSim\\Using"
#define CN_SYS_PATH	".\\SptSim\\"
#define CN_DATA_PATH	".\\SptSim\\"
#define CN_PARA_FILE_ROOT	".\\SptSim\\Using\\Para"
#define CN_CFG_FILE_ROOT	".\\SptSim\\Using\\LcdCfg"
#define CN_INFO_FILE_ROOT	".\\SptSim\\Using\\Info"
#define CN_LOG_FILE_ROOT	".\\SptSim\\Using\\Log"
#define CN_EVENT_FILE_ROOT	".\\SptSim\\Using\\Event"
#define CN_SJRECORD_FILE_ROOT	".\\SptSim\\Using\\SjRecord"
#define CN_STATUS_FILE_ROOT	".\\SptSim\\Using\\Status"
#define CN_GMSSL_FILE_ROOT	".\\SptSim\\Using\\GmSsl"
#define CN_T860_FILE_ROOT	".\\SptSim\\Using\\T860"
#define CN_T860_CFG_FILE_ROOT ".\\SptSim\\Using\\T860\\Public\\configuration"
#define CN_UPDATE_FILE_ROOT	 ".\\SptSim\\Update"
#define CN_UPDATE1_FILE_ROOT  ".\\SptSim\\Update"
#define CN_BAK_FILE_ROOT	".\\SptSim\\Bakup"
#define CN_BAK_FLASH_FILE_ROOT	CN_BAK_FILE_ROOT "\\Flash"
#elif defined(SYLIX_GZK)
#define CN_FILE_DivFlag	"/"
#define CN_APPS_ROOT	"/yaffs2/flash1/apps"
#define CN_CUR_ROOT	"/yaffs2/flash1/apps"
#define CN_USING_PATH	"/media/sdcard0/Using"
#define CN_T860_FILE_ROOT	"/yaffs2/flash1/apps/Using/T860"
#define CN_T860_CFG_FILE_ROOT "/yaffs2/flash1/apps/Using/Public/configuration"
#define CN_SYS_PATH	  "/yaffs2"
#define CN_DATA_PATH	 "/media"
#define CN_PARA_FILE_ROOT	"/yaffs2/flash1/Using/Para"
#define CN_CFG_FILE_ROOT	"/media/sdcard0/Using/Cfg"
#define CN_INFO_FILE_ROOT	"/media/sdcard0/Using/Info"
#define CN_LOG_FILE_ROOT	"/media/sdcard0/Using/Log"
#define CN_EVENT_FILE_ROOT	"/media/sdcard0/Using/Event"
#define CN_SJRECORD_FILE_ROOT	"/media/sdcard0/Using/SjRecord"
#define CN_STATUS_FILE_ROOT	"/media/sdcard0/Using/Status"
#define CN_GMSSL_FILE_ROOT	"/yaffs2/flash1/Using/GmSsl"
#define CN_UPDATE_FILE_ROOT	"/media/sdcard0/Update"
#define CN_UPDATE1_FILE_ROOT "/media/sdcard1/Update"
#define CN_BAK_FILE_ROOT	"/media/sdcard0/Bakup"
#define CN_BAK_FLASH_FILE_ROOT   CN_BAK_FILE_ROOT "/Flash"
#endif // WIN32_SIM
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
		bool8 Creat();
		void Close();
		bool8 IsOpened();
		bool8 IsExist();
		bool8 Delete();
		int32 Read(void* Buf, int32 BufLen);
		int32 ReadLine(char* Buf, int32 BufLen);
		int32 Write(void* Buf, int32 BufLen);
		int32 Write(const char* Buf);
		int32 Write(SalString& Buf);
		int32 WriteLine(const char* Buf);
		uint16 GetCrc(uint32 Len);
		uint16 GetCrc();
		bool8 Copy(SalFile& File);
		bool8 AppendSize(int32 Len);
		enum E_Seek
		{
			E_SET = 0,//起始位置
			E_CUR = 1,//当前位置
			E_END = 2,//结束位置
		};
		int32 Seek(int32 seek, int32 OffSet);
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
		struct Dirent
		{
			int64 time;
			uint32 size;
			int32 d_ino;              /* inode number*/
			int32 d_off;             /* offset to this dirent*/
			unsigned short d_reclen; /* length of this d_name*/
			unsigned char d_type;    /* the type of d_name,1 is file, 2 is dir*/
			char d_name[256];          /* file name (null-terminated)*/
		};
	public:
		SalDir();
		~SalDir();
		bool8 OpenDir(const char* Name);
		const Dirent* ReadDir(Dirent* Dir);
		bool8 CloseDir();
		bool8 IsOpened();
		static const char* GetAbsolutePath(char* Dst, const char* Sur, uint32 BufLen);
	protected:
		bool8 opened;
		char parentPath[256];
		void* dir;
	};
	void PrintFile2Hex(const char* FullName);
}

#include"SalCfgFile.h"



#endif//SALFILE_H
