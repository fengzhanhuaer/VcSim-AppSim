#ifndef SALADT_H
#define SALADT_H

namespace spt
{
	struct  AdtBufDes
	{
		uint32 bufLen;
		uint32 ctxLen;
		void* buf;
		void* pri;
	};
	struct  LinkedAdtBufDes
	{
		struct  AdtBufDes Des;
		struct  AdtBufDes* Last;
		struct  AdtBufDes* Next;
	};
	template<const uint32 BufLen>
	struct  StaticAdtBufDes
	{
		uint8 buf[BufLen];
		struct  LinkedAdtBufDes Des;
		StaticAdtBufDes()
		{
			Des.Last = Des.Next = 0;
			Des.Des.bufLen = BufLen;
			Des.Des.ctxLen = BufLen;
			Des.Des.buf = buf;
			Des.Des.pri = 0;
		}
	};
	class AllocBuf
	{
	public:
		AllocBuf(bool8 AutoFree);
		void* Alloc(uint32 ElementSize, uint32 ElementNum);
		void Free();
		uint32 ElementSize();
		uint32 ElementNum();
		uint32 BufSize();
		void* AddrOf(int32 No);
		void* BufBase();
		void AutoFree();
	public:
		~AllocBuf();
	private:
		bool8 autoFree;
		bool8 alloced;
		char* bufBase;
		uint32 elementSize;
		uint32 elementNum;
	};
	template <const int CN_ElementSize, const  int CN_ElementNum>
	class StaticBuf
	{
	public:
		StaticBuf() : elementSize(CN_ElementSize), elementNum(CN_ElementNum) { }
		uint32 ElementSize() { return elementSize; }
		uint32 ElementNum() { return elementNum; }
		uint32 BufSize() { return elementSize * elementNum; }
		void* BufBase() { return bufBase; }
	private:
		char bufBase[CN_ElementNum][CN_ElementSize];
		const uint32 elementSize;
		const uint32 elementNum;
	};
	//数组型缓冲区
	class ArrayBuf
	{
	public:
		ArrayBuf();
		ArrayBuf(void* Buf, uint32 ElementSize, uint32 ElementNum);
		//不会自动释放缓冲区
		void* Alloc(uint32 ElementSize, uint32 ElementNum);
		void SetBuf(void* Buf, uint32 ElementSize, uint32 ElementNum);
		void SetBuf(AllocBuf* Buf);
		void* GetElement(uint32 No);
		void* GetElement(uint32 No, void* Buf);
		bool8 SetElement(uint32 No, void* Buf);
		uint32 ElementSize()const;
		uint32 ElementNum()const;
		uint32 BufSize()const;
		void* BufBase();
		//存储指针型数据专用接口
		void* GetAddrElement(uint32 No);
		void* GetAddrElement(uint32 No, void*& Buf);
		bool8 SetAddrElement(uint32 No, void* Buf);
	protected:
		char* bufBase;
		uint32 elementSize;
		uint32 elementNum;
	};

	class SingleStackBuf :public ArrayBuf
	{
	public:
		SingleStackBuf();
		SingleStackBuf(void* Buf, uint32 ElementSize, uint32 ElementNum);
		bool8 Push(void* Buf);
		void* Pop();
		bool8 Pop(void* Buf);
		uint32 Top() { return top; }
		uint32 Bottom() { return bottom; }
		void Clear();
		//存储指针型数据专用接口
		void* GetAddrElement(uint32 No);
	protected:
		uint32 top;
		uint32 bottom;
	};
	class SingleCharBuf :public ArrayBuf
	{
	public:
		SingleCharBuf();
		SingleCharBuf(void* Buf, uint32 BufSize);
	public:
		uint32 Write(void* Buf, uint32 Len);
		void* GetAddr(uint32 No);
		uint32 Read(void* Buf, uint32 Len);
		bool8 IsEmpty();
		void Clear();
		uint32 Top() { return top; };
		uint32 Bottom() { return bottom; };
		uint32 ReaderAdd(int32 Add);
		uint32 WriterAdd(int32 Add);
	protected:
		uint32 top;
		uint32 bottom;
	};
	template <const uint32 BufLen>
	class StaticSingleCharBuf :public SingleCharBuf
	{
	public:
		StaticSingleCharBuf()
			:SingleCharBuf(charbuf, BufLen)
		{

		}
	protected:
		char charbuf[BufLen + 4];
	};
	typedef StaticSingleCharBuf<512> SCharStream512b;
	typedef StaticSingleCharBuf<1024> SCharStream1kb;
	typedef StaticSingleCharBuf<2 * 1024> SCharStream2kb;
	typedef StaticSingleCharBuf<5 * 1024> SCharStream5kb;
	class RingCharBuf :public ArrayBuf
	{
	public:
		RingCharBuf();
		RingCharBuf(void* Buf, uint32 BufSize);
	public:
		uint32 ValidCtxLen();
		uint32 Write(void* Buf, uint32 Len);
		uint32 Read(void* Buf, uint32 Len);
		uint8* PreGet(uint32 Index);
		uint32 PreRead(void* Buf, uint32 Len);
		bool8 IsEmpty();
		void Clear();
		uint32 Top() { return top; };
		uint32 Bottom() { return bottom; };
		uint32 ReaderAdd(int32 Add);
	protected:
		uint32 top;
		uint32 bottom;
	};
	class RingBuf :public ArrayBuf
	{
	public:
		RingBuf();
		RingBuf(void* Buf, uint32 ElementSize, uint32 ElementNum);
		bool8 Push(void* Buf);
		void* Pop();
		bool8 Pop(void* Buf);
		void Clear();
		void* Get(uint32 No);
		void* GetNextWriteBuf();
		void* GetWritedBuf(uint32 Index);
		void* GetNextValidReadBuf();
		uint32 Reader();
		uint32 Writer();
		uint32 ReaderAdd(int32 Add);
		uint32 WriterAdd(int32 Add);
	protected:
		uint32 fullcnt;
		bool8 isFull;
		uint32 top;
		uint32 bottom;
	};

	class PtrRingBuf
	{
	public:
		PtrRingBuf();
		void PowerUpIni(uint32 BufNum);
		void* Get(uint32 No);
		void* GetNextWriteBuf();
		void* GetWritedBuf(uint32 Index);
		void* GetNextValidReadBuf();
		void Set(uint32 No, void* Buf);
		uint32 Reader();
		uint32 Writer();
		uint32 ReaderAdd(int32 Add);
		uint32 WriterAdd(int32 Add);
		uint32 BufNum();
	protected:
		uint32 bufNum;
		uint32 writer;
		uint32 reader;
		void** bufBase;
	};
	class CharStreamReader
	{
	public:
		CharStreamReader(void* Buf, uint32 BufLen);
		void SetBuf(void* Buf, uint32 BufLen);
		bool8 Read(uint32& Data);
		bool8 Read(uint16& Data);
		bool8 Read(uint8& Data);
		bool8 Read(int32& Data);
		bool8 Read(int16& Data);
		bool8 Read(int8& Data);
		bool8 Read(void* Data, uint32 Len);
		void* Base() { return buf; };
		void* Top() { return &buf[reader]; };
	protected:
		uint32 reader;
		uint8* buf;
		uint32 bufLen;
	};

}

#endif // !SALADT_H
