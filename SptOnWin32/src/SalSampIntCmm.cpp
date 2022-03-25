#include"ApiProject.h"
using namespace spt;


void spt::SampIntMsgDesFlag::PowerUpIni(SampIntMsg* Buf)
{
	if (Buf)
	{
		DataLen = 0;
		pBuf = Buf;
		state = E_SIMBS_INI;
		BufLen = sizeof(SampIntMsg);
	}
	else
	{
		DataLen = 0;
		pBuf = 0;
		state = E_SIMBS_INI;
		BufLen = 0;
	}
}

int32 spt::SampIntMsgDesFlag::Write(void* Buf, int32 Len)
{
	if (Len > BufLen)
	{
		LogErr.Stamp() << "SampIntMsgPool Write Len > des->BufLen\n";
		Len = BufLen;
	}
	state = E_SIMBS_WRITING | E_SIMBS_ALLOCED;
	MemCpy(pBuf->dstMac, Buf, Len);
	DataLen = Len;
	state |= E_SIMBS_WRITED;
	return Len;
}

int32 spt::SampIntMsgDesFlag::Read(void* Buf, int32 Len)
{
	int32 L = DataLen;
	if (Len < L)
	{
		LogErr.Stamp() << "SampIntMsgPool Read Len > des->BufLen\n";
		L = Len;
	}
	state |= E_SIMBS_READING;
	MemCpy(Buf, pBuf->dstMac, L);
	state |= E_SIMBS_READED;
	return L;
}

int32 spt::SampIntMsgDesFlag::Write(uint16 Type, void* Buf, int32 Len)
{
	int32 L = DataLen;
	if (Len < L)
	{
		LogErr.Stamp() << "SampIntMsgPool Read Len > des->BufLen\n";
		L = Len;
	}
	state |= E_SIMBS_READING;
	pBuf->frameType = Type;
	pBuf->frameLen = Len;
	MemCpy(Buf, pBuf->buf, L);
	DataLen = Len;
	state |= E_SIMBS_READED;
	return L;
}

void spt::SampIntMsgDesFlag::SetWrited(uint16 Len)
{
	DataLen = Len;
	state = E_SIMBS_WRITING | E_SIMBS_ALLOCED | E_SIMBS_WRITED;
}

void spt::SampIntMsgDesFlag::SetReaded()
{
	state = E_SIMBS_WRITING | E_SIMBS_ALLOCED | E_SIMBS_WRITED | E_SIMBS_READING | E_SIMBS_READED;
}


void spt::SampIntMsgPool::PowerUpIni(int32 BufNum)
{
	AllocBuf allocBuf(0);
	SendMsgNum = RecvMsgNum = 0;
	DesNum = Write = Read = 0;
	Des = 0;
	if (allocBuf.Alloc(sizeof(SampIntMsgDesFlag), BufNum))
	{
		Des = (SampIntMsgDesFlag*)allocBuf.BufBase();
		DesNum = BufNum;
		AllocBuf allocBuf1(0);
		if (allocBuf1.Alloc(sizeof(SampIntMsg), BufNum))
		{
			for (int32 i = 0; i < BufNum; i++)
			{
				Des[i].PowerUpIni((SampIntMsg*)allocBuf1.AddrOf(i));
			}
		}
		else
		{
			allocBuf.Free();
			DesNum = Write = Read = 0;
			Des = 0;
			LogErr.Stamp() << "SampIntMsgPool allocBuf1 alloc failed\n";
		}
	}
	else
	{
		LogErr.Stamp() << "SampIntMsgPool allocBuf alloc failed\n";
	}
}

int32 spt::SampIntMsgPool::Push(void* Buf, int32 Len)
{
	if (!DesNum)
	{
		return -1;
	}
	SampIntMsgDesFlag* des = GetNextWriteDes();
	if (!des)
	{
		return -1;
	}
	Len = des->Write(Buf, Len);
	UpdateWriter();
	return Len;
}

int32 spt::SampIntMsgPool::Pop(void* Buf, int32 Len)
{
	if (!DesNum)
	{
		return -1;
	}
	SampIntMsgDesFlag* des = GetNextReadDes();
	if (!des)
	{
		return -1;
	}
	int32 res = des->Read(Buf, Len);
	UpdateReader();
	return res;
}

SampIntMsgDesFlag* spt::SampIntMsgPool::GetNextWriteDes()
{
	if (!DesNum)
	{
		return 0;
	}
	int32 w = Write % DesNum;
	int32 r = Read % DesNum;
	SampIntMsgDesFlag* des = &Des[w];
	while (des && (des->state & E_SIMBS_WRITED))
	{
		w = (w + 1) % DesNum;
		if (w == r)
		{
			break;
		}
		des = &Des[w];
	}
	if (des && (des->state & E_SIMBS_WRITED))
	{
		return 0;
	}
	return des;
}

void spt::SampIntMsgPool::UpdateWriter()
{
	int32 w = Write % DesNum;
	int32 r = Read % DesNum;
	int32 re = w;
	SampIntMsgDesFlag* des = &Des[w];
	while (des->state & E_SIMBS_WRITED)
	{
		w = (w + 1) % DesNum;
		if (w == r)
		{
			break;
		}
		RecvMsgNum++;
		des = &Des[w];
		re = w;
	}
	Write = re;
}

SampIntMsgDesFlag* spt::SampIntMsgPool::GetNextReadDes()
{
	if (!DesNum)
	{
		return 0;
	}
	if (IsEmpty())
	{
		return 0;
	}
	int32 w = Write % DesNum;
	int32 r = Read % DesNum;
	SampIntMsgDesFlag* des = &Des[r];
	while (!(des->state & E_SIMBS_WRITED))
	{
		r = (r + 1) % DesNum;
		if (w == r)
		{
			break;
		}
		des = &Des[r];
	}
	if ((des->state & E_SIMBS_WRITED))
	{
		return des;
	}
	return 0;
}

void spt::SampIntMsgPool::UpdateReader()
{
	int32 w = Write % DesNum;
	int32 r = Read % DesNum;
	SampIntMsgDesFlag* des = &Des[r];
	while (des->state & E_SIMBS_READED)
	{
		des->state = E_SIMBS_INI;
		SendMsgNum++;
		r = (r + 1) % DesNum;
		if (w == r)
		{
			break;
		}
		des = &Des[r];
	}
	Read = r;
}

bool8 spt::SampIntMsgPool::IsFull()
{
	if (!DesNum)
	{
		return 1;
	}
	return ((Write + 1) % DesNum) == Read;
}

bool8 spt::SampIntMsgPool::IsEmpty()
{
	return(Read == Write) || (Des == 0);
}

void spt::SampIntMsgPool::ClearData()
{
	if ((Read != Write) && Des)
	{
		for (int32 i = 0; i < DesNum; i++)
		{
			Des[i].state = E_SIMBS_INI;
		}
	}
	Read = Write = 0;
}

bool8 spt::SampIntMsg::IsSumOk()
{
	uint16 len = frameLen - 2;
	if (len >= (sizeof(buf) - 2))
	{
		return 0;
	}
	uint16 sum = 0;
	for (uint16 i = 0; i < len; i++)
	{
		sum += buf[i];
	}
	uint16 fsum = buf[len];
	fsum += (((uint16)(buf[len + 1])) << 8);
	if (fsum == sum)
	{
		return 1;
	}
	return 0;
}


int32 spt::SptSampIntMsgProc::PowerUpIni(int32 Para)
{
	const ApiAppCfg* appcfg = SptMain::Instance().AppCfg();
	if (appcfg)
	{
		switch (appcfg->platform.hardware)
		{
		case EH_GZK35KVP:
		{
			fpgaMsgProc = new GzkFpgaMsgGzk35KvProts();
			break;
		}
		case EH_GZK35KVSMART:
		{
			fpgaMsgProc = new GzkFpgaMsgGzk35KvSmart();
			break;
		}
		case EH_GZKSAU:
		{
			fpgaMsgProc = new GzkFpgaMsgSau31();
			break;
		}
		default:
			fpgaMsgProc = 0;
			break;
		}
	}
	else
	{
		fpgaMsgProc = 0;
	}
	if (fpgaMsgProc)
	{
		fpgaMsgProc->PowerUpIni(Para);
	}
	return 0;
}

int32 spt::SptSampIntMsgProc::Proc(int32 Para)
{
	if (fpgaMsgProc)
	{
		fpgaMsgProc->SendProc();
		fpgaMsgProc->RecvProc();
	}
	return 0;
}

int32 spt::SptSampIntMsgProc::SendMsg(void* Buf, int32 Len)
{
	if (fpgaMsgProc)
	{
		return fpgaMsgProc->IntSend(Buf, Len);
	}
	return -1;
}

int32 spt::SptSampIntMsgProc::RecvMsg(void* Buf, int32 BufLen)
{
	if (fpgaMsgProc)
	{
		return fpgaMsgProc->IntRecv(Buf, BufLen);
	}
	return -1;
}

FpgaMsgProc* spt::SptSampIntMsgProc::FpgaMsgProc()
{
	return fpgaMsgProc;
}

spt::SptSampIntMsgProc::SptSampIntMsgProc()
{


}