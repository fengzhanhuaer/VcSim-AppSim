#include "SptProject.h"
using namespace spt;
void spt::SalCmmMsgBufCtrl::PowerUpIni(uint32 BufSize)
{
	if (BufSize > (sizeof(SalCmmTemplateHeader) + 2))
	{
		buf = (SalCmmTemplateHeader*)Calloc(1, BufSize);
	}
	else
	{
		buf = 0;
	}

	bufSize = BufSize;
	isCheckOk = 0;
	isUsed = 0;
	if (buf)
	{
		isFree = 1;
	}
	else
	{
		isFree = 0;
		bufSize = 0;
	}
	state = 0;
	pool = 0;
	ctxLen = 0;
}

void spt::SalCmmMsgBufCtrl::FreeBuf()
{
	if (pool)
	{
		pool->FreeBuf(this);
	}
	else
	{
		state = E_SCS_Inied;
	}
}

void spt::SalCmmMsgBufCtrl::SetFlag(uint32 Flag)
{
	state |= Flag;
}

void spt::SalCmmMsgBufCtrl::UnSetFlag(uint32 Flag)
{
	state &= ~Flag;
}

void spt::SalCmmMsgBufCtrl::SetWrited()
{
	SetFlag(E_SCS_Writing | E_SCS_Writed);
}

void spt::SalCmmMsgBufCtrl::SetReaded()
{
	SetFlag(E_SCS_Reading | E_SCS_Readed);
}

uint16 spt::SalCmmMsgBufCtrl::CalcCrc()
{
	uint16 sum = 0;

	sum = Crc16ModBus.CalCrc(buf, buf->header.len);

	return sum;
}

uint16 spt::SalCmmMsgBufCtrl::AddCrc()
{
	return  Crc16ModBus.AddCrc(buf, buf->header.len + 2);
}

uint16 spt::SalCmmMsgBufCtrl::IsCrcOk()
{
	return Crc16ModBus.IsCrcOk(buf, buf->header.len + 2);
}

void spt::SalCmmMsgCtrlPool::PowerUpIni(uint32 BufNum, uint32 BufSize)
{
	usedNum = reader = writer = 0;
	if (BufNum)
	{
		Ctrl = (SalCmmMsgBufCtrl*)Calloc(BufNum, sizeof(SalCmmMsgBufCtrl));
		if (!Ctrl)
		{
			bufNum = 0;
			return;
		}
		bufNum = BufNum;
		for (uint32 i = 0; i < BufNum; i++)
		{
			Ctrl[i].PowerUpIni(BufSize);
			Ctrl[i].pool = this;
		}
	}
	else
	{
		Ctrl = 0;
	}
}

SalCmmMsgBufCtrl* spt::SalCmmMsgCtrlPool::GetNextWriteBuf()
{
	if (reader == writer)
	{
		if (usedNum >= bufNum)
		{
			outPut.getWriteBufErrCnt++;
			return 0;
		}
	}
	uint32 w = writer % bufNum;
	uint32 r = reader % bufNum;
	if (Ctrl)
	{
		if ((Ctrl[w].state == E_SCS_Inied))
		{
			Ctrl[w].state = E_SCS_Alloced;
			usedNum++;
			writer = (w + 1) % bufNum;
			outPut.writeCnt++;
			return &Ctrl[w];
		}
		w = (w + 1) % bufNum;
		if (w != r)
		{
			if ((Ctrl[w].state == E_SCS_Inied))
			{
				Ctrl[w].state = E_SCS_Alloced;
				usedNum++;
				writer = (w + 1) % bufNum;
				outPut.writeCnt++;
				return &Ctrl[w];
			}
		}
	}
	outPut.getWriteBufErrCnt++;
	return 0;
}

SalCmmMsgBufCtrl* spt::SalCmmMsgCtrlPool::GetNextReadBuf()
{
	if (reader == writer)
	{
		return 0;
	}
	uint32 w = writer % bufNum;
	uint32 r = reader % bufNum;
	while (r != w)
	{
		if ((Ctrl[r].state == E_SCS_Inied))
		{
			return 0;
		}
		if ((Ctrl[r].state & E_SCS_Writed) && (!(Ctrl[r].state & E_SCS_Readed)))
		{
			Ctrl[r].state |= E_SCS_Reading;
			return &Ctrl[r];
		}
		r = (r + 1) % bufNum;
	}
	return 0;
}

void spt::SalCmmMsgCtrlPool::UpdateReader()
{
	if (!Ctrl)
	{
		return;
	}
	uint32 w = writer % bufNum;
	uint32 r = reader % bufNum;
	do
	{
		if (Ctrl[r].state == E_SCS_Inied)
		{
			if (usedNum)
			{
				usedNum--;
			}
			if (r == w)
			{
				break;
			}
			r = (r + 1) % bufNum;
		}
		else if (Ctrl[r].state & E_SCS_Readed)
		{
			Ctrl[r].state = E_SCS_Inied;
			if (usedNum)
			{
				usedNum--;
			}
			r = (r + 1) % bufNum;
			outPut.readCnt++;
		}
		else
		{
			break;
		}
	} while (r != w);
	reader = r;
}

void spt::SalCmmMsgCtrlPool::FreeBuf(SalCmmMsgBufCtrl* Ctrl)
{
	if (Ctrl)
	{
		if (usedNum)
		{
			usedNum--;
		}
		Ctrl->state = E_SCS_Inied;
	}
}

void spt::SalCmmMsgCtrlPool::FreeAllBuf()
{
	for (uint32 i = 0; i < bufNum; i++)
	{
		Ctrl[i].FreeBuf();
	}
	reader = writer = usedNum = 0;
}

uint16 spt::SalCmmMsgHeader::CalcCrc()
{
	uint16 sum = 0;

	sum = Crc16ModBus.CalCrc(&header, len);

	return sum;
}

uint16 spt::SalCmmMsgHeader::AddCrc()
{
	return  Crc16ModBus.AddCrc(&header, len + 2);
}

uint16 spt::SalCmmMsgHeader::IsCrcOk()
{
	return Crc16ModBus.IsCrcOk(&header, len + 2);
}
