#ifndef SALLIB_H
#define SALLIB_H

namespace spt
{
	int32 StrCmp(const char* Dst, const char* Sur);
	int32 StrLen(const char* Msg);
	int32 StrGBK2UCS2(uint16* Dst, const char* Sur, int32 BufUint16Size);
	int32 StrGBK2UTF8(char* Dst, const char* Sur, int32 BufLen);
	const char* StrStr(const char* Msg, const char* SubMsg);
	void Replace(char* Sur, char Flag, char NewFlag);
	int PosOf(const char* Context, char flag, int No);
	char* StrNCpy(char* Dst, const char* Sur, int32 BufLen);
	char* StrNCat(char* Dst, const char* Sur, int32 BufLen);
	int32 StrNCmp(char* Dst, const char* Sur, int32 BufLen);
	void MsSleep(int32 ms);
	int32 MkDir(const char* Dir);
	int32 RemoveDir(const char* Dir);
	int32 RemoveFile(const char* file);
	int32 Rename(char* oldname, char* newname);
	/// <summary>
	/// 文件是否存在
	/// </summary>
	/// <param name="Dir"></param>
	/// <param name="Mode">0</param>
	/// <returns>存在为0</returns>
	int32 Access(const char* Dir, int Mode);
	int32 MemCmp(const char* Dst, const char* Sur, uint32 Len);
	void MemSet(void* Sur, int Val, uint32 Len);
	void MemCpy(void* Dst, const void* Sur, uint32 Len);
	bool8 IsAlpha(unsigned char Data);
	bool8 IsUpAlpha(unsigned char Data);
	bool8 IsLowAlpha(unsigned char Data);
	bool8 IsNember(unsigned char Data);
	bool8 IsPunct(unsigned char Data);//标点符号
	bool8 IsAscii(unsigned char Data);
	bool8 IsSpace(unsigned char Data);
	bool8 IsGraph(unsigned char Data);
	void* Calloc(uint32 ElementNum, uint32 ElementSize);
	int Free(void* Buf);
	//二进制
	class SemaphoreB
	{
	public:
		SemaphoreB();
		~SemaphoreB();
	public:
		void* Creat(int IniVal);
		int32 Wait(int32 timeOutMs);
		int32 Post();
	private:
		void* handle;
	};
	//计数型
	class SemaphoreC
	{
	public:
		SemaphoreC();
		~SemaphoreC();
	public:
		void* Creat(int IniVal, int MaxVal);
		int32 Wait(int32 timeOutMs);
		int32 Post();
		int32 Post(int Val);
	private:
		void* handle;
	};
	//读写型
	class SemaphoreRW
	{

	};
}


#endif // !SALLIB_H

