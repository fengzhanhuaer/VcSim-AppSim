#include "SptProject.h"
using namespace spt;

spt::RingBuf::RingBuf()
{
	SetBuf(0, 0, 0);
	Clear();
}

spt::RingBuf::RingBuf(void* Buf, uint32 Size, uint32 Num)
{
	SetBuf(Buf, Size, Num);
	Clear();
}

bool8 spt::RingBuf::Push(void* Buf)
{
	uint32 t = top;
	uint32 tb = t;
	uint32 b = bottom;
	t = (t + 1) % elementNum;
	if (t == b)
	{
		bottom = (b + 1) % elementNum;
		isFull = 1;
		fullcnt++;
	}
	top = t;
	char* dst = bufBase + tb * elementSize;
	MemCpy(dst, Buf, elementSize);
	return 1;
}

void* spt::RingBuf::Pop()
{
	uint32 t = top;
	uint32 b = bottom;
	if (t == b)
	{
		return 0;
	}
	else
	{
		bottom = (b + 1) % elementNum;
		char* dst = bufBase + b * elementSize;
		return dst;
	}
	return 0;
}

bool8 spt::RingBuf::Pop(void* Buf)
{
	void* buf = Pop();
	if (buf)
	{
		MemCpy(Buf, buf, elementSize);
		return 1;
	}
	return 0;
}

void spt::RingBuf::Clear()
{
	top = bottom = 0;
	isFull = 0;
}

void* spt::RingBuf::Get(uint32 No)
{
	return GetElement(No);
}

void* spt::RingBuf::GetNextWriteBuf()
{
	return GetElement(top);
}
void* spt::RingBuf::GetWritedBuf(uint32 Index)
{
	Index = (top + elementNum - Index - 1) % elementNum;
	return GetElement(Index);
}

void* spt::RingBuf::GetNextValidReadBuf()
{
	if (bottom != top)
	{
		return GetElement(bottom);
	}
	return 0;
}

uint32 spt::RingBuf::Reader()
{
	return bottom;
}

uint32 spt::RingBuf::Writer()
{
	return top;
}

uint32 spt::RingBuf::ReaderAdd(int32 Add)
{
	bottom = (bottom + elementNum + Add) % elementNum;
	return bottom;
}

uint32 spt::RingBuf::WriterAdd(int32 Add)
{
	top = (top + elementNum + Add) % elementNum;
	return top;
}

spt::ArrayBuf::ArrayBuf()
{
	SetBuf(0, 0, 0);
}

spt::ArrayBuf::ArrayBuf(void* Buf, uint32 Size, uint32 Num)
{
	SetBuf(Buf, Size, Num);
}

void* spt::ArrayBuf::Alloc(uint32 ElementSize, uint32 ElementNum)
{
	AllocBuf buf(0);
	void* b = buf.Alloc(ElementSize, ElementNum);
	if (b)
	{
		SetBuf(&buf);
	}
	return b;
}

void spt::ArrayBuf::SetBuf(void* Buf, uint32 Size, uint32 Num)
{
	bufBase = (char*)Buf;
	elementNum = Num;
	elementSize = Size;
}

void spt::ArrayBuf::SetBuf(AllocBuf* Buf)
{
	if (Buf)
	{
		SetBuf(Buf->BufBase(), Buf->ElementSize(), Buf->ElementNum());
	}
}

void* spt::ArrayBuf::GetElement(uint32 No)
{
	if (No < elementNum)
	{
		char* dst = bufBase + No * elementSize;
		return dst;
	}
	return 0;
}

void* spt::ArrayBuf::GetElement(uint32 No, void* Buf)
{
	if (!bufBase)
	{
		return 0;
	}
	char* dst = (char*)GetElement(No);
	if (dst && Buf)
	{
		MemCpy(Buf, dst, elementSize);
		return dst;
	}
	return 0;
}

bool8 spt::ArrayBuf::SetElement(uint32 No, void* Buf)
{
	if (!bufBase)
	{
		return 0;
	}
	if ((No < elementNum) && (Buf))
	{
		char* dst = bufBase + No * elementSize;
		MemCpy(dst, Buf, elementSize);
		return 1;
	}
	return 0;
}

void* spt::ArrayBuf::GetAddrElement(uint32 No)
{
	void* addr = 0;
	return GetAddrElement(No, addr);
}

void* spt::ArrayBuf::GetAddrElement(uint32 No, void*& Buf)
{
	if (elementSize != sizeof(void*))
	{
		return 0;
	}
	GetElement(No, &Buf);
	return Buf;
}

bool8 spt::ArrayBuf::SetAddrElement(uint32 No, void* Buf)
{
	if (elementSize != sizeof(void*))
	{
		return 0;
	}
	return SetElement(No, &Buf);
}

void* spt::ArrayBuf::BufBase()
{
	return bufBase;
}

uint32 spt::ArrayBuf::ElementSize()const
{
	return elementSize;
}

uint32 spt::ArrayBuf::ElementNum()const
{
	return elementNum;
}

uint32 spt::ArrayBuf::BufSize()const
{
	return elementNum * elementSize;
}

bool8 spt::SingleStackBuf::Push(void* Buf)
{
	bool8 res = SetElement(top, Buf);
	top++;
	if (!res)
	{
		if (top > elementNum)
		{
			top = elementNum;
		}
	}
	return res;
}

void* spt::SingleStackBuf::Pop()
{
	if (bottom < top)
	{
		return GetElement(bottom++);
	}
	return 0;
}

bool8 spt::SingleStackBuf::Pop(void* Buf)
{
	if (Buf)
	{
		void* buf = Pop();
		if (buf)
		{
			MemCpy(Buf, buf, elementSize);
			return 1;
		}
	}
	return 0;
}

void spt::SingleStackBuf::Clear()
{
	top = bottom = 0;
}

void* spt::SingleStackBuf::GetAddrElement(uint32 No)
{
	return ((void**)bufBase)[No];
}

spt::SingleStackBuf::SingleStackBuf()
{
	Clear();
	SetBuf(0, 0, 0);
}

spt::SingleStackBuf::SingleStackBuf(void* Buf, uint32 ElementSize, uint32 ElementNum)
{
	Clear();
	SetBuf(Buf, ElementSize, ElementNum);
}

spt::AllocBuf::AllocBuf(bool8 AutoFree)
{
	autoFree = AutoFree;
	bufBase = 0;
	elementNum = 0;
	elementSize = 0;
	alloced = 0;
}

void* spt::AllocBuf::Alloc(uint32 ElementSize, uint32 ElementNum)
{
	AutoFree();
	bufBase = (char*)Calloc(ElementNum, ElementSize);
	if (bufBase)
	{
		elementNum = ElementNum;
		elementSize = ElementSize;
		alloced = 1;
	}
	else
	{
		LogErr.Stamp() << "Alloc buf failed.\n";
	}
	return bufBase;
}

void spt::AllocBuf::Free()
{
	if (bufBase)
	{
		spt::Free(bufBase);
	}
	alloced = 0;
}

uint32 spt::AllocBuf::ElementSize()
{
	return elementSize;
}

uint32 spt::AllocBuf::ElementNum()
{
	return elementNum;
}

uint32 spt::AllocBuf::BufSize()
{
	return elementNum * elementSize;
}

void* spt::AllocBuf::AddrOf(int32 No)
{
	if (bufBase)
	{
		return bufBase + No * elementSize;
	}
	else
	{
		return 0;
	}
	return 0;
}

void* spt::AllocBuf::BufBase()
{
	return bufBase;
}

void spt::AllocBuf::AutoFree()
{
	if ((alloced == 1) && (autoFree == 1))
	{
		spt::Free(bufBase);
		bufBase = 0;
		alloced = 0;
	}
}

spt::AllocBuf::~AllocBuf()
{
	AutoFree();
}

spt::SingleCharBuf::SingleCharBuf()
{
	Clear();
	SetBuf(0, 0, 0);
}

spt::SingleCharBuf::SingleCharBuf(void* Buf, uint32 BufSize)
{
	Clear();
	SetBuf(Buf, 1, BufSize);
}

uint32 spt::SingleCharBuf::Write(void* Buf, uint32 Len)
{
	if (top > BufSize())
	{
		top = BufSize();
	}
	uint32 ta = Len + top;
	if (ta > BufSize())
	{
		Len = BufSize() - top;
		ta = Len + top;
	}
	if (Len)
	{
		MemCpy((char*)BufBase() + top, Buf, Len);
	}
	top = ta;
	return Len;
}

void* spt::SingleCharBuf::GetAddr(uint32 No)
{
	if (No > BufSize())
	{
		return 0;
	}
	return (char*)BufBase() + No;
}

uint32 spt::SingleCharBuf::Read(void* Buf, uint32 Len)
{
	if (bottom > top)
	{
		bottom = top;
	}
	uint32  l = top - bottom;
	if (Len > l)
	{
		Len = l;
	}
	uint32 ba = bottom + Len;
	if (Len)
	{
		MemCpy(Buf, (char*)BufBase() + bottom, Len);
	}
	bottom = ba;
	return Len;
}

bool8 spt::SingleCharBuf::IsEmpty()
{
	if (!BufBase())
	{
		return 1;
	}
	if (top == bottom)
	{
		return 1;
	}
	return 0;
}

void spt::SingleCharBuf::Clear()
{
	bottom = top = 0;
}

uint32 spt::SingleCharBuf::WriterAdd(int32 Add)
{
	if (top < BufSize())
	{
		if (Add < 0)
		{
			Add = -Add;
			if ((uint32)Add > top)
			{
				top = 0;
			}
			else
			{
				top -= Add;
			}
		}
		else
		{
			top += Add;
		}

		if (top > BufSize())
		{
			top = BufSize();
		}
	}
	return top;
}

uint32 spt::SingleCharBuf::ReaderAdd(int32 Add)
{
	if (bottom < BufSize())
	{
		if (Add < 0)
		{
			Add = -Add;
			if ((uint32)Add > bottom)
			{
				bottom = 0;
			}
			else
			{
				bottom -= Add;
			}
		}
		else
		{
			bottom += Add;
		}

		if (bottom > top)
		{
			bottom = top;
		}
	}
	return bottom;
}

spt::PtrRingBuf::PtrRingBuf()
{
	bufNum = writer = reader = 0;
	bufBase = 0;
}

void spt::PtrRingBuf::PowerUpIni(uint32 BufNum)
{
	AllocBuf buf(0);

	void* b = buf.Alloc(sizeof(void*), BufNum);
	if (b)
	{
		if (bufBase)
		{
			spt::Free(bufBase);
		}
		bufBase = (void**)b;
		bufNum = BufNum;
	}
	else
	{
		LogErr.Stamp() << "PtrRingBuf PowerUpIni err\n";
	}

}

void* spt::PtrRingBuf::Get(uint32 No)
{
	if (No >= bufNum)
	{
		return 0;
	}
	return bufBase[No];
}

void* spt::PtrRingBuf::GetNextWriteBuf()
{
	return Get(writer);
}

void* spt::PtrRingBuf::GetWritedBuf(uint32 Index)
{
	if (Index >= bufNum)
	{
		return 0;
	}
	Index = (writer + bufNum - Index - 1) % bufNum;
	return Get(Index);
}

void* spt::PtrRingBuf::GetNextValidReadBuf()
{
	if (writer != reader)
	{
		return Get(reader);
	}
	return 0;
}

void spt::PtrRingBuf::Set(uint32 No, void* Buf)
{
	if (No >= bufNum)
	{
		return;
	}
	bufBase[No] = Buf;
}

uint32 spt::PtrRingBuf::Reader()
{
	return reader;
}

uint32 spt::PtrRingBuf::Writer()
{
	return writer;
}

uint32 spt::PtrRingBuf::ReaderAdd(int32 Add)
{
	if (bufNum)
	{
		reader = (reader + bufNum + Add) % bufNum;
	}
	return reader;
}

uint32 spt::PtrRingBuf::WriterAdd(int32 Add)
{
	if (bufNum)
	{
		writer = (writer + bufNum + Add) % bufNum;
	}
	return writer;
}

uint32 spt::PtrRingBuf::BufNum()
{
	return bufNum;
}

spt::RingCharBuf::RingCharBuf()
{
	Clear();
	SetBuf(0, 0, 0);
	bottom = top = 0;
}

spt::RingCharBuf::RingCharBuf(void* Buf, uint32 BufSize)
{
	Clear();
	SetBuf(Buf, 1, BufSize);
	bottom = top = 0;
}

uint32 spt::RingCharBuf::ValidCtxLen()
{
	uint32 w = top % elementNum;
	uint32 r = bottom % elementNum;
	if (w > r)
	{
		return w - r;
	}
	else if (w < r)
	{
		return w + elementNum - r;
	}
	return 0;
}

uint32 spt::RingCharBuf::Write(void* Buf, uint32 Len)
{
	uint32 w = top % elementNum;
	uint32 r = bottom % elementNum;
	uint32 wr = 0;
	uint8* sur = (uint8*)Buf;
	uint8* dst = (uint8*)bufBase;
	uint32 len = 0;
	for (len = 0; len < Len; len++)
	{
		dst[w] = *sur++;
		wr = (w + 1) % elementNum;
		if (wr == r)
		{
			break;
		}
		w = wr;
	}
	top = w;
	return len;
}

uint32 spt::RingCharBuf::Read(void* Buf, uint32 Len)
{
	if (IsEmpty())
	{
		return 0;
	}
	uint32 w = top % elementNum;
	uint32 r = bottom % elementNum;
	uint32 wr = 0;
	uint8* sur = (uint8*)Buf;
	uint8* dst = (uint8*)bufBase;
	uint32 len = 0;
	for (len = 0; len < Len; len++)
	{
		*sur++ = dst[r];
		wr = (r + 1) % elementNum;
		r = wr;
		if (wr == w)
		{
			len++;
			break;
		}
	}
	bottom = r;
	return len;
}

uint8* spt::RingCharBuf::PreGet(uint32 Index)
{
	if (IsEmpty())
	{
		return 0;
	}
	uint32 w = top % elementNum;
	uint32 r = bottom % elementNum;
	uint8* dst = (uint8*)bufBase;
	if (w > r)
	{
		uint32 rd = r + Index;
		if (rd >= w)
		{
			return 0;
		}
		return dst + rd;
	}
	else
	{
		uint32 rd = r + Index;
		if (rd >= elementNum)
		{
			rd = rd % elementNum;
			if (rd >= w)
			{
				return 0;
			}
			return dst + rd;
		}
		return dst + rd;
	}
	return 0;
}

uint32 spt::RingCharBuf::PreRead(void* Buf, uint32 Len)
{
	if (IsEmpty())
	{
		return 0;
	}
	uint32 w = top % elementNum;
	uint32 r = bottom % elementNum;
	uint32 wr = 0;
	uint8* sur = (uint8*)Buf;
	uint8* dst = (uint8*)bufBase;
	uint32 len = 0;
	for (len = 0; len < Len; len++)
	{
		*sur++ = dst[r];
		wr = (r + 1) % elementNum;
		if (wr == w)
		{
			len++;
			break;
		}
		r = wr;
	}
	return len;
}

bool8 spt::RingCharBuf::IsEmpty()
{
	return top == bottom;
}

void spt::RingCharBuf::Clear()
{
	top = bottom;
}

uint32 spt::RingCharBuf::ReaderAdd(int32 Add)
{
	uint32 w = top % elementNum;
	uint32 r = bottom % elementNum;
	if (w > r)
	{
		int32 rd = r + Add;
		if ((uint32)rd <= w)
		{
			bottom = rd;
		}
	}
	else
	{
		int32 rd = (r + Add);
		if ((uint32)rd >= elementNum)
		{
			rd = rd % elementNum;
			if ((uint32)rd <= w)
			{
				bottom = rd;
			}
		}
		else
		{
			bottom = (uint32)rd;
		}
	}
	return bottom;
}

spt::CharStreamReader::CharStreamReader(void* Buf, uint32 BufLen)
{
	SetBuf(Buf, BufLen);
}

void spt::CharStreamReader::SetBuf(void* Buf, uint32 BufLen)
{
	reader = 0;
	buf = (uint8*)Buf;
	bufLen = BufLen;
}

bool8 spt::CharStreamReader::Read(uint32& Data)
{
	if (reader < bufLen)
	{
		MemCpy(&Data, buf + reader, sizeof(Data));
		reader += sizeof(Data);
		return 1;
	}
	return 0;
}

bool8 spt::CharStreamReader::Read(uint16& Data)
{
	if (reader < bufLen)
	{
		MemCpy(&Data, buf + reader, sizeof(Data));
		reader += sizeof(Data);
		return 1;
	}
	return 0;
}

bool8 spt::CharStreamReader::Read(uint8& Data)
{
	if (reader < bufLen)
	{
		MemCpy(&Data, buf + reader, sizeof(Data));
		reader += sizeof(Data);
		return 1;
	}
	return 0;
}

bool8 spt::CharStreamReader::Read(int32& Data)
{
	if (reader < bufLen)
	{
		MemCpy(&Data, buf + reader, sizeof(Data));
		reader += sizeof(Data);
		return 1;
	}
	return 0;
}

bool8 spt::CharStreamReader::Read(int16& Data)
{
	if (reader < bufLen)
	{
		MemCpy(&Data, buf + reader, sizeof(Data));
		reader += sizeof(Data);
		return 1;
	}
	return 0;
}

bool8 spt::CharStreamReader::Read(int8& Data)
{
	if (reader < bufLen)
	{
		MemCpy(&Data, buf + reader, sizeof(Data));
		reader += sizeof(Data);
		return 1;
	}
	return 0;
}
