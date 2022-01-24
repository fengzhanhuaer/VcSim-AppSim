#include"SptProject.h"
using namespace spt;

int32 spt::SptAppCmmTask::PowerUpIni(int32 Para)
{
	Task::PowerUpIni(0);
	Start();
	return 0;
}

int32 spt::SptAppCmmTask::OneLoop()
{
	uint32 len = cmmTask.Top();
	MsStampTimer stamp;
	for (uint32 i = 0; i < len; i++)
	{
		SalCmmChannel* cmm = (SalCmmChannel*)cmmTask.GetAddrElement(i);
		stamp.StartTimer();
		cmm->Proc();
		if (stamp.Status(2))
		{
			MsSleep(1);
		}
	}
	MsSleep(2);
	return 0;
}

int32 spt::SptAppCmmTask::RgsAppCmmTask(SalCmmChannel* Channel)
{
	bool8 res = cmmTask.Push(&Channel);
	if (res)
	{
		return 0;
	}
	return -1;
}

int32 spt::SptAppCmmTask::RecvFromHal(uint16 DataLen, void* Data)
{
	SalCmmTemplateHeader* buf = (SalCmmTemplateHeader*)Data;
	uint32 len = cmmTask.Top();
	for (uint32 i = 0; i < len; i++)
	{
		SalCmmChannel* ch = (SalCmmChannel*)cmmTask.GetAddrElement(i);
		SptAppSlowCmm* cmm = (SptAppSlowCmm*)ch;
		if (ch && (cmm->Sur() == buf->header.dst))
		{
			cmm->RecvFromHal(DataLen, Data);
			return DataLen;
			break;
		}
	}
	return -1;
}

SalCmmChannel* spt::SptAppCmmTask::CmmChannel(int32 Index)
{
	return (SalCmmChannel*)cmmTask.GetAddrElement(Index);
}

int32 spt::SptAppCmmTask::CmmChannelNum()
{
	return cmmTask.Top();
}

spt::SptAppCmmTask::SptAppCmmTask()
	:Task("tSptCmm", 70, 2 * 1024 * 1024, E_T_FLOAT, E_ServiceCore)
{
	cmmTask.Alloc(sizeof(void*), 100);
}

int32 spt::SptPublicCmmTask::PowerUpIni(int32 Para)
{
	Task::PowerUpIni(0);
	Start();
	return 0;
}

int32 spt::SptPublicCmmTask::OneLoop()
{
	uint32 len = cmmTask.Top();
	MsStampTimer stamp;
	for (uint32 i = 0; i < len; i++)
	{
		SalCmmChannel* cmm = (SalCmmChannel*)cmmTask.GetAddrElement(i);
		stamp.StartTimer();
		cmm->Proc();
		if (stamp.Status(2))
		{
			MsSleep(1);
		}
	}
	MsSleep(2);
	return 0;
}

int32 spt::SptPublicCmmTask::RgsAppCmmTask(SalCmmChannel* Channel)
{
	bool8 res = cmmTask.Push(&Channel);
	if (res)
	{
		return 0;
	}
	return -1;
}

SalCmmChannel* spt::SptPublicCmmTask::CmmChannel(int32 Index)
{
	return (SalCmmChannel*)cmmTask.GetAddrElement(Index);
}

int32 spt::SptPublicCmmTask::CmmChannelNum()
{
	return  cmmTask.Top();
}

spt::SptPublicCmmTask::SptPublicCmmTask()
	:Task("tPubCmm", 90, 2 * 1024 * 1024, E_T_FLOAT, E_ServiceCore)
{
	cmmTask.Alloc(sizeof(void*), 100);
}

int32 spt::SptAppFastCmm::SendMsgTo(uint16 Dst, uint32 UnPackIndex, uint16 Type, uint16 DataLen, void* Data)
{
	uint16 len = DataLen;
	if ((len + sizeof(SalTransHeader) + 2) > appSendMsgPool.Ctrl[0].bufSize)
	{
		len = appSendMsgPool.Ctrl[0].bufSize - sizeof(SalTransHeader) - 2;
	}
	if (UnPackIndex < driverNum)
	{
		driver[UnPackIndex].SendMsgCnt++;
	}
	outPut.sendCnt++;
	SalCmmMsg<1024> msg;
	MemCpy(&msg.header, &frmHeader, sizeof(frmHeader));
	msg.header.dst = Dst;
	msg.header.len = len + sizeof(SalTransHeader);
	SalTransFrame* buf = (SalTransFrame*)&msg;
	buf->Header.unPackIndex = (uint16)UnPackIndex;
	buf->Header.type = (uint16)Type;
	buf->Header.dataLen = (uint16)len;
	buf->Header.res = (uint16)0;
	MemCpy(buf->data, Data, len);
	msg.header.AddCrc();
	CpuFpgaCmmMsgBuf fmsg;
	fmsg.Write(&msg, msg.header.len + 2);
	return fmsg.IntSend(0, FpgaMsgProc::E_CPU_FPGA_BOARD_CMM);
}
int32 spt::SptAppFastCmm::RecvFromHal(uint16 DataLen, void* Data)
{
	SalTransFrame* buf = (SalTransFrame*)Data;
	if (!buf->Header.salHeader.IsCrcOk())
	{
		outPut.recvErrCnt++;
		return -1;
	}
	if ((buf->Header.unPackIndex < driverNum) && driver[buf->Header.unPackIndex].RecvFunc)
	{
		outPut.recvCnt++;
		driver[buf->Header.unPackIndex].RecvFunc(this, &driver[buf->Header.unPackIndex], (SalCmmMsgHeader*)buf);
		driver[buf->Header.unPackIndex].RecvMsgCnt++;
	}
	else
	{
		outPut.recvErrCnt++;
	}
	return DataLen;
}
int32 spt::SptAppFastCmm::ProcIn()
{
	return int32();
}

int32 spt::SptAppFastCmm::Proc()
{
	return int32();
}

int32 spt::SptAppFastCmm::ProcOut()
{
	return int32();
}
int32 spt::SptAppSlowCmm::ProcIn()
{
	SalCmmMsgBufCtrl* ctrl = appRecMsgPool.GetNextReadBuf();
	while (ctrl)
	{
		SalTransFrame* buf = (SalTransFrame*)ctrl->buf;

		if (ctrl->IsCrcOk())
		{
			for (uint32 i = 0; i < driverNum; i++)
			{
				if ((driver[i].Type == buf->Header.type) && driver[i].RecvFunc)
				{
					driver[i].RecvFunc(this, &driver[i], (SalCmmMsgHeader*)ctrl->buf);
					driver[i].RecvMsgCnt++;
					break;
				}
			}
		}
		else
		{
			outPut.recvErrCnt++;
		}
		ctrl->SetReaded();
		ctrl = appRecMsgPool.GetNextReadBuf();
	}
	appRecMsgPool.UpdateReader();
	return 0;
}

int32 spt::SptAppSlowCmm::Proc()
{
	ProcIn();
	ProcOut();
	return int32();
}

int32 spt::SptAppSlowCmm::ProcOut()
{
	uint32 len = driverNum;
	for (uint32 i = 0; i < len; i++)
	{
		if (driver[i].HasNewToSend && driver[i].SendFunc)
		{
			driver[i].SendFunc(this, &driver[i]);
		}
	}
	SalCmmMsgBufCtrl* ctrl = appSendMsgPool.GetNextReadBuf();
	if (ctrl)
	{
		outPut.sendCnt++;
		SalTransFrame* buf = (SalTransFrame*)ctrl->buf;
		CpuFpgaCmmMsgBuf fmsg;
		fmsg.Write(buf, ctrl->ctxLen);
		fmsg.SlowSend(0, FpgaMsgProc::E_CPU_FPGA_BOARD_CMM);
		ctrl->SetReaded();
		ctrl = appSendMsgPool.GetNextReadBuf();
	}
	appSendMsgPool.UpdateReader();
	return 0;
}

int32 spt::SptAppSlowCmm::RecvFromHal(uint16 DataLen, void* Data)
{
	SalCmmMsgBufCtrl* ctrl = appRecMsgPool.GetNextWriteBuf();
	if (ctrl && ctrl->buf)
	{
		if (DataLen >= appRecMsgPool.Ctrl[0].bufSize)
		{
			outPut.recvErrCnt++;
			return -1;
		}
		outPut.recvCnt++;
		ctrl->ctxLen = DataLen;
		MemCpy(ctrl->buf, Data, DataLen);
		ctrl->SetWrited();
		return 0;
	}
	else
	{
		appRecMsgPool.FreeAllBuf();
	}
	return -1;
}

int32 spt::SptAppSlowCmm::SendMsgTo(uint16 Dst, uint32 UnPackIndex, uint16 Type, uint16 DataLen, void* Data)
{
	SalCmmMsgBufCtrl* ctrl = appSendMsgPool.GetNextWriteBuf();
	if (ctrl && ctrl->buf)
	{
		uint16 len = DataLen;
		if ((len + sizeof(SalTransHeader) + 2) > ctrl->bufSize)
		{
			len = ctrl->bufSize - sizeof(SalTransHeader) - 2;
		}
		MemCpy(&ctrl->buf->header, &frmHeader, sizeof(frmHeader));
		ctrl->buf->header.len = len + sizeof(SalTransHeader);
		ctrl->buf->header.dst = Dst;
		SalTransFrame* buf = (SalTransFrame*)ctrl->buf;
		buf->Header.unPackIndex = (uint16)UnPackIndex;
		buf->Header.type = (uint16)Type;
		buf->Header.dataLen = (uint16)len;
		buf->Header.res = (uint16)0;
		MemCpy(buf->data, Data, len);
		ctrl->ctxLen = len + sizeof(SalTransHeader) + 2;
		ctrl->AddCrc();
		ctrl->isUsed = 1;
		ctrl->SetWrited();
		return len;
	}
	else
	{
		appSendMsgPool.FreeAllBuf();
		outPut.sendErrCnt++;
	}
	return -1;
}

spt::SptAppSlowCmm::SptAppSlowCmm()
{
	SptAppCmmTask::Instance().RgsAppCmmTask(this);
}


