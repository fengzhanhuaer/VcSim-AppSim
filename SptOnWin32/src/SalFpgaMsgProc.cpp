#include "SptProject.h"
using namespace spt;

spt::FpgaMsgProc::FpgaMsgProc()
{

}

spt::FpgaMsgProc::~FpgaMsgProc()
{
}
//#define EnableMsgLogCheck
int32 spt::FpgaMsgProc::PowerUpIni(int32 Para)
{
	slowMsgWriteSem.Creat(1);
#ifdef EnableMsgLogCheck
	msgDateTime.ClearLoadInfo();
	msgDateTime.SetName("MsgDate");
	msgDateTime.Rgs2TaskMonitorRunInfo();
	msgAnglog.ClearLoadInfo();
	msgAnglog.SetName("MsgAnglog");
	msgAnglog.Rgs2TaskMonitorRunInfo();
	msgGoPos.ClearLoadInfo();
	msgGoPos.SetName("msgGoPos");
	msgGoPos.Rgs2TaskMonitorRunInfo();
	msgGoAng.ClearLoadInfo();
	msgGoAng.SetName("MsgGoAng");
	msgGoAng.Rgs2TaskMonitorRunInfo();
	msgDioMsg.ClearLoadInfo();
	msgDioMsg.SetName("MsgDio");
	msgDioMsg.Rgs2TaskMonitorRunInfo();
	msgSvState.ClearLoadInfo();
	msgSvState.SetName("MsgSvSat");
	msgSvState.Rgs2TaskMonitorRunInfo();
	msgGoState.ClearLoadInfo();
	msgGoState.SetName("MsgGoSat");
	msgGoState.Rgs2TaskMonitorRunInfo();
	msgBoardState.ClearLoadInfo();
	msgBoardState.SetName("MsgBorSat");
	msgBoardState.Rgs2TaskMonitorRunInfo();
	msgBoardCmm.ClearLoadInfo();
	msgBoardCmm.SetName("MsgBorCmm");
	msgBoardCmm.Rgs2TaskMonitorRunInfo();
	msgBoardLig.ClearLoadInfo();
	msgBoardLig.SetName("MsgBorLig");
	msgBoardLig.Rgs2TaskMonitorRunInfo();
#endif
	return 0;
}

int32 spt::FpgaMsgProc::SendProc()
{
	Send2Hal(sampIntSendMsg);
	Send2Hal(slowTaskSendMsg);
	return 0;
}

int32 spt::FpgaMsgProc::RecvProc()
{
	sampIntRecvMsg.ClearData();
	RecvFromHal(sampIntRecvMsg);
	return 0;
}

int32 spt::FpgaMsgProc::RtSend(uint32 No, void* Buf, int32 MsgLen)
{
	return SptSendEmacData(No, (unsigned char*)Buf, MsgLen);
}

int32 spt::FpgaMsgProc::RtRecv(uint32 No, void* Buf, int32 BufLen)
{
	return SptRecEmacData(No, (unsigned char*)Buf, BufLen);
}

int32 spt::FpgaMsgProc::IntSend(void* Buf, int32 MsgLen)
{
	return sampIntSendMsg.Push(Buf, MsgLen);
}

int32 spt::FpgaMsgProc::IntRecv(void* Buf, int32 BufLen)
{
	int res = sampIntRecvMsg.Pop(Buf, BufLen);
	return  res;
}

int32 spt::FpgaMsgProc::SlowSend(void* Buf, int32 MsgLen)
{
	if (slowMsgWriteSem.Wait(500) >= 0)
	{
		int32 res = slowTaskSendMsg.Push(Buf, MsgLen);
		if (res < 0)
		{
			slowTaskSendMsg.ClearData();
			res = slowTaskSendMsg.Push(Buf, MsgLen);
		}
		slowMsgWriteSem.Post();
		return res;
	}
	return 0;
}

int32 spt::FpgaMsgProc::SlowSend(CpuFpgaCmmMsg* Msg)
{
	return SlowSend(Msg, Msg->msg.frameLen + 18);
}

void spt::FpgaMsgProc::Send2Hal(SampIntMsgPool& Pool)
{
	SampIntMsgDesFlag* Des;
	while (1)
	{
		Des = Pool.GetNextReadDes();
		if (Des)
		{
			RtSend(0, (unsigned char*)Des->pBuf, Des->DataLen);
			Des->SetReaded();
			Pool.UpdateReader();
		}
		else
		{
			break;
		}
	}
	return;
}

void spt::FpgaMsgProc::RecvFromHal(SampIntMsgPool& Pool)
{
	SampIntMsgDesFlag* Des;
	int len;
	while (1)
	{
		Des = Pool.GetNextWriteDes();
		if (Des)
		{
			len = RtRecv(0, (unsigned char*)Des->pBuf, Des->BufLen);
			if (len > 0)
			{
				Des->SetWrited((uint16)len);
				Pool.UpdateWriter();
				//LogErr<<len<<"\n";
			}
			else
			{
				//   LogErr<<len<<","<<Des->DataLen<<"\n";
				break;
			}
		}
		else
		{
			LogErr << "RecvFromHal" << -2 << "\n";
			break;
		}
	}
	return;
}

int32 spt::GzkFpgaMsgGzk35KvProts::PowerUpIni(int32 Para)
{
	FpgaMsgProc::PowerUpIni(0);
	sampIntRecvMsg.PowerUpIni(20);
	sampIntSendMsg.PowerUpIni(20);
	slowTaskSendMsg.PowerUpIni(20);
	slowTaskRecvMsg.PowerUpIni(20);
	return 0;
}

spt::GzkFpgaMsgGzk35KvProts::GzkFpgaMsgGzk35KvProts()
{

}

spt::GzkFpgaMsgGzk35KvProts::~GzkFpgaMsgGzk35KvProts()
{
}

int32 spt::GzkFpgaMsgGzk35KvSmart::PowerUpIni(int32 Para)
{
	FpgaMsgProc::PowerUpIni(0);
	sampIntRecvMsg.PowerUpIni(20);
	sampIntSendMsg.PowerUpIni(20);
	slowTaskSendMsg.PowerUpIni(20);
	slowTaskRecvMsg.PowerUpIni(20);
	return 0;
}

spt::GzkFpgaMsgGzk35KvSmart::GzkFpgaMsgGzk35KvSmart()
{

}

spt::GzkFpgaMsgGzk35KvSmart::~GzkFpgaMsgGzk35KvSmart()
{
}

int32 spt::GzkFpgaMsgGzk35KvSmart::RecvProc()
{
	sampIntRecvMsg.ClearData();
	SampIntMsg msg;
	SampIntMsg* ptr;
	int32 len;
	int32 res;
	while (1)
	{
		len = SptRecEmacData(0, (unsigned char*)&msg, sizeof(msg));
		if (len > 0)
		{
			switch (msg.frameType)
			{
			case E_Board_Cmm_F2C:
			{
				ptr = (SampIntMsg*)msg.buf;
				switch (ptr->frameType)
				{
				case E_Board_FPGA_Update:
				{
					slowTaskRecvMsg.RecvMsgNum++;
					GzkFpgaUpdate::FpgaUpdateMsgRecv(&msg, len);
					slowTaskRecvMsg.SendMsgNum++;
					break;
				}
				default:
				{
					res = sampIntRecvMsg.Push(&msg, len);
					if (res <= 0)
					{
						goto exit;
					}
					break;
				}
				}
				break;
			}
			default:
			{
				res = sampIntRecvMsg.Push(&msg, len);
				if (res <= 0)
				{
					goto exit;
				}
				break;
			}
			}
		}
		else
		{
			break;
		}
	}
exit:

	return 0;
}

int32 spt::GzkFpgaMsgSau31::PowerUpIni(int32 Para)
{
	FpgaMsgProc::PowerUpIni(0);
	sampIntRecvMsg.PowerUpIni(20);
	sampIntSendMsg.PowerUpIni(20);
	slowTaskSendMsg.PowerUpIni(20);
	slowTaskRecvMsg.PowerUpIni(20);
	int32 len;
	SampIntMsg msg;
	while (1)
	{
		len = SptRecEmacData(0, (unsigned char*)&msg, sizeof(msg));
		if (len > 0)
		{
		}
		else
		{
			break;
		}
	}
	return 0;
}

spt::GzkFpgaMsgSau31::GzkFpgaMsgSau31()
{

}

spt::GzkFpgaMsgSau31::~GzkFpgaMsgSau31()
{
}

int32 spt::GzkFpgaMsgSau31::RecvProc()
{
	sampIntRecvMsg.ClearData();
	SampIntMsg* msgptr;
	int32 len;
	int32 res;
	int32 timecnt = 0;
	uint32 beginus = HwUsCnt();
#ifdef EnableMsgLogCheck
	msgBoardLig.exInfo1 = msgBoardCmm.exInfo1 = msgBoardState.exInfo1 = msgGoState.exInfo1 = msgSvState.exInfo1 = msgDateTime.exInfo1 = msgAnglog.exInfo1 = msgGoPos.exInfo1 = msgGoAng.exInfo1 = msgDioMsg.exInfo1 = 0;
#endif
	dateTime = angSamp = goAng = goPos = 0;
	writer = 0;
	while ((writer < M_ArrLen(msgPool)) && ((len = SptRecEmacData(0, (unsigned char*)&msgPool[writer], sizeof(SampIntMsg))) > 0))
	{
		sampIntRecvMsg.RecvMsgNum++;
		sampIntRecvMsg.SendMsgNum++;
		msgptr = &msgPool[writer];
		writer++;
		if (!msgptr->IsSumOk())
		{
			if (msgptr->frameType != E_Board_Cmm_F2C)
			{
				LogErr.Stamp() << "GzkFpgaMsgSau31 " << msgptr->frameType << " Crc Err\n";
				continue;
			}
		}
		switch (msgptr->frameType)
		{
		case E_FPGA_CPU_HIO_CMM:
		{
#ifdef EnableMsgLogCheck
			msgDioMsg.RunStart();
#endif
			SptIoProcess::Instance().RecvNorIoMsg(msgptr->buf, msgptr->frameLen);
#ifdef EnableMsgLogCheck
			msgDioMsg.exInfo1++;
			msgDioMsg.RunEnd();
#endif
			break;
		}
		case E_FPGA_CPU_AngSamp_CMM:
		{
			angSamp = msgptr;
#ifdef EnableMsgLogCheck
			msgAnglog.exInfo1++;
#endif
			break;
		}
		case E_FPGA_CPU_TIME:
		{
			dateTime = msgptr;
#ifdef EnableMsgLogCheck
			msgDateTime.exInfo1++;
#endif // EnableMsgLogCheck
			timecnt++;
			break;
		}
		case E_FPGA_CPU_SVCB_STATE:
		{
#ifdef EnableMsgLogCheck
			msgSvState.RunStart();
#endif
			SptIoProcess::Instance().RecSvInCbCheckStateMsg(msgptr->buf, msgptr->frameLen);
#ifdef EnableMsgLogCheck
			msgSvState.exInfo1++;
			msgSvState.RunEnd();
#endif
			break;
		}
		case E_FPGA_CPU_GOCB_STATE:
		{
#ifdef EnableMsgLogCheck
			msgGoState.RunStart();
#endif
			SptIoProcess::Instance().RecGoInCbCheckStateMsg(msgptr->buf, msgptr->frameLen);
#ifdef EnableMsgLogCheck
			msgGoState.exInfo1++;
			msgGoState.RunEnd();
#endif
			break;
		}
		case E_FPGA_CPU_GOCB_POSSUB:
		{
			goPos = msgptr;
#ifdef EnableMsgLogCheck
			msgGoPos.exInfo1++;
#endif
			break;
		}
		case E_FPGA_CPU_GOCB_ANGSUB:
		{
			goAng = msgptr;
#ifdef EnableMsgLogCheck
			msgGoAng.exInfo1++;
#endif
			break;
		}
		case E_FPGA_CPU_BOARD_STATE:
		{
#ifdef EnableMsgLogCheck
			msgBoardState.RunStart();
#endif
			SptIoProcess::Instance().RecBoardInfoMsg(msgptr->buf, msgptr->frameLen);
#ifdef EnableMsgLogCheck
			msgBoardState.exInfo1++;
			msgBoardState.RunEnd();
#endif
			break;
		}
		case E_FPGA_CPU_BOARD_LIGHT:
		{
#ifdef EnableMsgLogCheck
			msgBoardLig.RunStart();
#endif
			SptIoProcess::Instance().RecLightInfoMsg(msgptr->buf, msgptr->frameLen);
#ifdef EnableMsgLogCheck
			msgBoardLig.exInfo1++;
			msgBoardLig.RunEnd();
#endif
			break;
		}
		case E_FPGA_CPU_Board_CMM:
		{
#ifdef EnableMsgLogCheck
			msgBoardCmm.RunStart();
#endif
			SptIoProcess::Instance().RecBoardMsg(msgptr->buf, msgptr->frameLen - 2);
#ifdef EnableMsgLogCheck
			msgBoardCmm.exInfo1++;
			msgBoardCmm.RunEnd();
#endif
			break;
		}
		case E_Board_Cmm_F2C:
		{
			SampIntMsg* ptr = (SampIntMsg*)msgptr->buf;
			if (!ptr->IsSumOk())
			{
				LogErr.Stamp() << "GzkFpgaMsgSau31 Board Cmm" << msgptr->frameType << " Crc Err\n";
				break;
			}
			switch (ptr->frameType)
			{
			case E_Board_FPGA_Update:
			{
				GzkFpgaUpdate::FpgaUpdateMsgRecv(msgptr, len);
				break;
			}
			default:
			{
				break;
			}
			}
			break;
		}
		default:
		{
			res = sampIntRecvMsg.Push(msgptr, len);
			if (res <= 0)
			{
				goto exit;
			}
			break;
		}
		}
		if (timecnt >= 3)
		{
			uint32 delta = HwUsCnt() - beginus;
			if (delta > (SptSampInt::Instance().PeriodUs() / 5))
			{
				LogErr.Stamp() << "GzkFpgaMsgSau31 RecProc Timer Over SptSampInt::Instance().PeriodUs() " << timecnt << "\n";
				goto exit;
			}
		}
	}
exit:
	if (dateTime)
	{
#ifdef EnableMsgLogCheck
		msgDateTime.RunStart();
#endif
		SptDateTask::Instance().RecFpgaMsg(dateTime->buf, dateTime->frameLen);
#ifdef EnableMsgLogCheck
		msgDateTime.RunEnd();
#endif
	}
	if (angSamp)
	{
#ifdef EnableMsgLogCheck
		msgAnglog.RunStart();
#endif
		SptIoProcess::Instance().RecvAngFrameMsg(angSamp->buf, angSamp->frameLen);
#ifdef EnableMsgLogCheck
		msgAnglog.RunEnd();
#endif
	}
	if (goPos)
	{
#ifdef EnableMsgLogCheck
		msgGoPos.RunStart();
#endif
		SptIoProcess::Instance().RecvGoPosFrameMsg(goPos->buf, goPos->frameLen);
#ifdef EnableMsgLogCheck
		msgGoPos.RunEnd();
#endif
	}
	if (goAng)
	{
#ifdef EnableMsgLogCheck
		msgGoAng.RunStart();
#endif
		SptIoProcess::Instance().RecvGoAngFrameMsg(goAng->buf, goAng->frameLen);
#ifdef EnableMsgLogCheck
		msgGoAng.RunEnd();
#endif
	}
	return 0;
}

spt::GzkFpgaUpdate::GzkFpgaUpdate(const char* FileName, uint32 BufSize, uint16 FpgaAddr, uint16 FrameLen, uint16 MaxRepeat)
{
	fileName = FileName;
	bufSize = BufSize;
	fpgaAddr = FpgaAddr;
	frameLen = FrameLen;
	AllocBuf buf(0);
	fileSize = programSize = 0;
	fpgaFileBuf = (uint8*)buf.Alloc(BufSize, 1);
	handle = this;
	enable = 1;
	maxRepeat = MaxRepeat;
	if (maxRepeat < 1)
	{
		maxRepeat = 1;
	}
}

spt::GzkFpgaUpdate::~GzkFpgaUpdate()
{
	if (fpgaFileBuf)
	{
		spt::Free(fpgaFileBuf);
		fpgaFileBuf = 0;
	}
	handle = 0;
	enable = 0;
}
int32 spt::GzkFpgaUpdate::Run(int32(*Process)(int32 Step, const char* info))
{
	String100B info;
	int32 step = 0;
	if (!fpgaFileBuf)
	{
		info = "内存申请失败,按任意键继续";
		if (Process)
		{
			Process(step, info.Str());
		}
		LogErr.Stamp().PrintLine(info.Str());
		step++;
		return -1;
	}
	SalFile file;
	file.SetFullName(fileName.Str());

	if (!file.IsExist())
	{
		info = fileName.Str();
		info << "不存在,按任意键继续";
		if (Process)
		{
			Process(step, info.Str());
		}
		LogErr.Stamp().PrintLine(info.Str());
		step++;
		return -1;
	}
	file.OpenReadOnly();

	if (!file.IsOpened())
	{
		info = "程序文件打开失败,按任意键继续";
		if (Process)
		{
			Process(step, info.Str());
		}
		LogErr.Stamp().PrintLine(info.Str());
		step++;
		return -1;
	}
	fileSize = file.Size();
	if (fileSize > bufSize)
	{
		info = "程序文件过大,按任意键继续";
		if (Process)
		{
			Process(step, info.Str());
		}
		LogErr.Stamp().PrintLine(info.Str());
		step++;
		return -1;
	}
	uint32 proinfo[8];
	fileSize = file.Read(proinfo, sizeof(proinfo));
	if (fileSize != sizeof(proinfo))
	{
		info = "程序信息读取异常,按任意键继续";
		if (Process)
		{
			Process(step, info.Str());
		}
		LogErr.Stamp().PrintLine(info.Str());
		step++;
		return -1;
	}
	fileSize = file.Read(fpgaFileBuf, bufSize);
	if (fileSize <= 0)
	{
		info = "程序文件读取异常,按任意键继续";
		if (Process)
		{
			Process(step, info.Str());
		}
		LogErr.Stamp().PrintLine(info.Str());
		step++;
		return -1;
	}
	if (fileSize != proinfo[0])
	{
		info = "程序信息大小异常,按任意键继续";
		if (Process)
		{
			Process(step, info.Str());
		}
		LogErr.Stamp().PrintLine(info.Str());
		step++;
		return -1;
	}
	if (fileSize % frameLen)
	{
		frameTotal = fileSize / frameLen + 1;
	}
	else
	{
		frameTotal = fileSize / frameLen;
	}
	fileSum = 0;
	for (uint32 i = 0; i < fileSize; i++)
	{
		fileSum += fpgaFileBuf[i];
	}
	if (fileSum != proinfo[1])
	{
		info = "程序信息校验码异常,按任意键继续";
		if (Process)
		{
			Process(step, info.Str());
		}
		LogErr.Stamp().PrintLine(info.Str());
		step++;
		return -1;
	}
	checkSum = 0;
	frameNum = 0;
	programSize = 0;
	info = "开始升级";
	info << file.Name().Name();
	if (Process)
	{
		Process(step, info.Str());
	}
	LogReal.Stamp().PrintLine(info.Str());
	step++;

	msgProc = SptSampIntMsgProc::Instance().FpgaMsgProc();
	if (!msgProc)
	{
		info = "FPGA交互通道异常";
		info << file.Name().Name();
		if (Process)
		{
			Process(step, info.Str());
		}
		LogReal.Stamp().PrintLine(info.Str());
		step++;
		return -1;
	}
	updateStep = E_UpdateStart;
	stepPathWriter = 0;
	GoOneStep(0xaa00, 0x5500, E_UpdateStart, E_UpdateStart_Wait, E_UpdateBitStreamClose, 2000);
	if (updateStep == E_UpdateBitStreamClose)
	{
		info = "正在擦除FLASH... ";
		if (Process)
		{
			Process(step, info.Str());
		}
		LogReal.Stamp().PrintLine(info.Str());
		step++;
		GoOneStep(0xaa44, 0x5544, E_UpdateBitStreamClose, E_UpdateBitStreamClose_Wait, E_UpdateProgram_Start, 20000);
		if (updateStep == E_UpdateProgram_Start)
		{
			info = "正在写入FLASH: ";
			uint32 perc = frameNum * 100 / frameTotal;
			info << perc << "%";
			if (Process)
			{
				Process(step, info.Str());
			}
			uint32 lastperc = 0;
			while (frameNum < frameTotal)
			{
				uint32 len = fileSize - programSize;
				if (len > frameLen)
				{
					len = frameLen;
				}
				uint8* p = fpgaFileBuf + programSize;
				updateStep = E_UpdateProgram_Send;
				SendProg(p, (uint16)len, frameTotal, frameNum, 5000);
				if (updateStep != E_UpdateProgram_Start)
				{
					updateStep = E_UpdateTimeOver;
					break;
				}
				else
				{
					programSize += len;
					frameNum++;
				}
				uint32 perc = frameNum * 100 / frameTotal;
				if (lastperc != perc)
				{
					info = "正在写入FLASH: ";
					info << perc << "%";
					if (Process)
					{
						Process(step, info.Str());
					}
					lastperc = perc;
				}
			}
			step++;
			if (frameNum == frameTotal)
			{
				updateStep = E_UpdateProgramCheck_Send;
				info = "正在进行程序校验";
				if (Process)
				{
					Process(step, info.Str());
				}
				step++;
				for (uint32 i = 0; i < maxRepeat; i++)
				{
					if (updateStep == E_UpdateProgramCheck_Send)
					{
						recOk = 0;

						uint8 data[100];
						MemSet(data, 0, 10);
						data[0] = (uint8)(0x33);
						data[1] = (uint8)(0xaa);
						data[2] = (uint8)(fileSize);
						data[3] = (uint8)(fileSize >> 8);
						data[4] = (uint8)(fileSize >> 16);
						data[5] = (uint8)(fileSize >> 24);
						CpuFpgaCmmMsgBuf msg;
						msg.Write(data, 10);
						msg.BoardCmmSlowSend(0, fpgaAddr, FpgaMsgProc::E_Board_FPGA_Update);
						updateStep = E_UpdateProgramCheck_Wait;
						sendDelay.Enable(1);
						sendDelay.StartTimer();
					}
					if (updateStep == E_UpdateProgramCheck_Wait)
					{
						while (!(sendDelay.Status(5000)))
						{
							if (recOk)
							{
								recOk = 0;
								uint16 cmd = *(uint16*)recMsg.BoardCmm.data1;
								if (cmd == 0x5533)
								{
									uint32 sum = recMsg.BoardCmm.data1[5];
									sum = (sum << 8) + recMsg.BoardCmm.data1[4];
									sum = (sum << 8) + recMsg.BoardCmm.data1[3];
									sum = (sum << 8) + recMsg.BoardCmm.data1[2];
									checkSum = sum;
									if (sum == fileSum)
									{
										info = "校验正常:";
										info.FormatHex(checkSum);
										updateStep = E_UpdateBitStreamOpen;
									}
									else
									{
										info = "校验异常:";
										info.FormatHex(checkSum);
										info << "!=";
										info.FormatHex(fileSum);
										updateStep = E_UpdateSumErr;
									}
									if (Process)
									{
										Process(step, info.Str());
									}
									step++;
									break;
								}
								else
								{
									LogErr.Stamp() << "GoOneStep Wait Err" << cmd << "\n";
								}
							}
							else
							{
								updateStep = E_UpdateProgramCheck_Send;
							}
							MsSleep(2);
						}

					}
				}
				if (updateStep == E_UpdateBitStreamOpen)
				{
					GoOneStep(0xaa55, 0x5555, E_UpdateBitStreamOpen, E_UpdateBitStreamOpen_Wait, E_UpdateEnd, 1000);
					if (updateStep == E_UpdateEnd)
					{
						info = "FPGA升级完成,按任意键继续";
						if (Process)
						{
							Process(step, info.Str());
						}
						LogReal.Stamp().PrintLine(info.Str());
						step++;
						return 0;
					}
					else
					{
						updateStep = E_UpdateErr;
					}
				}
			}
			else if (updateStep != E_UpdateTimeOver)
			{
				updateStep = E_UpdateErr;
			}
		}
		else
		{
			updateStep = E_UpdateTimeOver;
		}
	}
	else
	{
		updateStep = E_UpdateTimeOver;
	}

	if (updateStep == E_UpdateTimeOver)
	{
		info = "FPGA交互超时,按任意键继续";
		if (Process)
		{
			Process(step, info.Str());
		}
		LogReal.Stamp().PrintLine(info.Str());
		step++;
		return -1;
	}
	else if (updateStep == E_UpdateErr)
	{
		info = "FPGA升级异常,按任意键继续";
		if (Process)
		{
			Process(step, info.Str());
		}
		LogReal.Stamp().PrintLine(info.Str());
		step++;
		return -1;
	}
	return -1;
}
void spt::GzkFpgaUpdate::UpdateMsgRecv(void* Buf, int32 MsgLen)
{
	CpuFpgaCmmMsgBuf* msg;
	msg = (CpuFpgaCmmMsgBuf*)Buf;
	if (!msg->IsBoardCmmSumOk())
	{
		LogErr.Stamp() << "UpdateMsgRecv IsBoardCmmSumOk err\n";
		return;
	}
	MemCpy(&recMsg, Buf, MsgLen);
	recOk = 1;
	return;
}
void spt::GzkFpgaUpdate::SendCmd(uint16 cmd, uint8 NextStep)
{
	uint8 data[100];
	MemSet(data, 0, 12);
	data[0] = (uint8)(cmd);
	data[1] = (uint8)(cmd >> 8);
	CpuFpgaCmmMsgBuf msg;
	msg.Write(data, 10);
	msg.BoardCmmSlowSend(0, fpgaAddr, FpgaMsgProc::E_Board_FPGA_Update);

	updateStep = NextStep;
	sendDelay.Enable(1);
	sendDelay.StartTimer();
}
void spt::GzkFpgaUpdate::GoOneStep(uint16 cmd, uint16 WaitCmd, uint8 StepNow, uint8 WaitStep, uint8 NextStep, uint16 WaitTime)
{
	for (uint32 i = 0; i < maxRepeat; i++)
	{
		if (updateStep == StepNow)
		{
			recOk = 0;
			SendCmd(cmd, WaitStep);
		}
		if (updateStep == WaitStep)
		{
			while (!(sendDelay.Status(WaitTime)))
			{
				if (recOk)
				{
					recOk = 0;
					uint16 cmd = *(uint16*)recMsg.BoardCmm.data1;
					if (cmd == WaitCmd)
					{
						updateStep = NextStep;
						return;
					}
					else
					{
						LogErr.Stamp() << "GoOneStep Wait Err" << cmd << "\n";
					}
				}
				MsSleep(2);
			}
			updateStep = StepNow;
		}
	}
}
void spt::GzkFpgaUpdate::SendProg(uint8* Data, uint16 FrameLen, uint16 Total, uint16 FrameNum, uint16 WaitTime)
{
	for (uint32 i = 0; i < maxRepeat; i++)
	{
		if (updateStep == E_UpdateProgram_Send)
		{
			uint8 data[2048];
			data[0] = 0x22;
			data[1] = 0xaa;
			data[2] = (uint8)(Total);
			data[3] = (uint8)(Total >> 8);
			data[4] = (uint8)(FrameNum);
			data[5] = (uint8)(FrameNum >> 8);
			data[6] = (uint8)(FrameLen);
			data[7] = (uint8)(FrameLen >> 8);
			CpuFpgaCmmMsgBuf msg;
			msg.Write(data, 8);
			msg.Write(Data, FrameLen);
			msg.BoardCmmSlowSend(0, fpgaAddr, FpgaMsgProc::E_Board_FPGA_Update);
			sendDelay.Enable(1);
			sendDelay.StartTimer();
			updateStep = E_UpdateProgram_Wait;
		}
		if (updateStep == E_UpdateProgram_Wait)
		{
			while (!(sendDelay.Status(WaitTime)))
			{
				if (recOk)
				{
					recOk = 0;
					uint16 cmd = *(uint16*)recMsg.BoardCmm.data1;
					if (cmd == 0x5522)
					{
						updateStep = E_UpdateProgram_Start;
						return;
					}
					else
					{
						LogErr.Stamp() << "GoOneStep Wait Err" << cmd << "\n";
					}
				}
				MsSleep(1);
			}
			updateStep = E_UpdateProgram_Send;
		}
	}
}
GzkFpgaUpdate* GzkFpgaUpdate::handle = 0;
bool8 GzkFpgaUpdate::enable = 0;
void spt::GzkFpgaUpdate::FpgaUpdateMsgRecv(void* Buf, int32 MsgLen)
{
	if (enable)
	{
		if (handle)
		{
			if (enable && handle)
			{
				handle->UpdateMsgRecv(Buf, MsgLen);
				return;
			}
		}
	}
}

uint16 spt::CpuFpgaCmmMsgBuf::AddSum()
{
	uint16 sum = CalcSum();
	uint32 len = writer;
	msg.BoardCmm.data1[len] = (uint8)(sum);
	msg.BoardCmm.data1[len + 1] = (uint8)(sum >> 8);
	return sum;
}
int32 spt::CpuFpgaCmmMsgBuf::SlowSend(int32 EmacNo, uint16 Type)
{
	msg.BoardCmm.frameType1 = Type;
	msg.BoardCmm.res1 = 0;
	msg.BoardCmm.frameLen1 = writer + 2;
	AddSum();
	FpgaMsgProc* msgProc = SptSampIntMsgProc::Instance().FpgaMsgProc();
	if (!msgProc)
	{
		return -1;
	}
	return msgProc->SlowSend(&msg.BoardCmm.dstMac1[0], writer + 20);
}
int32 spt::CpuFpgaCmmMsgBuf::IntSend(int32 EmacNo, uint16 Type)
{
	msg.BoardCmm.frameType1 = Type;
	msg.BoardCmm.res1 = 0;
	msg.BoardCmm.frameLen1 = writer + 2;
	AddSum();
	FpgaMsgProc* msgProc = SptSampIntMsgProc::Instance().FpgaMsgProc();
	if (!msgProc)
	{
		return -1;
	}
	return msgProc->IntSend(&msg.BoardCmm.dstMac1[0], writer + 20);
}
int32 spt::CpuFpgaCmmMsgBuf::RtSend(int32 EmacNo, uint16 Type)
{
	msg.BoardCmm.frameType1 = Type;
	msg.BoardCmm.res1 = 0;
	msg.BoardCmm.frameLen1 = writer + 2;
	AddSum();
	FpgaMsgProc* msgProc = SptSampIntMsgProc::Instance().FpgaMsgProc();
	if (!msgProc)
	{
		return -1;
	}
	return msgProc->RtSend(0, &msg.BoardCmm.dstMac1[0], writer + 20);
}
int32 spt::CpuFpgaCmmMsgBuf::BoardCmmSlowSend(int32 EmacNo, uint16 Dst, uint16 Type)
{
	msg.BoardCmm.frameLen1 = writer + 2;
	msg.BoardCmm.frameLen = writer + 20;
	if (msg.BoardCmm.frameLen >= sizeof(msg.BoardCmm.data1))
	{
		writer = sizeof(msg.BoardCmm.data1) - 20;
		msg.BoardCmm.frameLen = writer + 20;
		msg.BoardCmm.frameLen1 = writer + 2;
	}
	msg.BoardCmm.dstMac1[0] = 0x01;
	msg.BoardCmm.dstMac1[1] = 0x0C;
	msg.BoardCmm.dstMac1[2] = 0xCD;
	msg.BoardCmm.dstMac1[3] = 0x01;
	msg.BoardCmm.dstMac1[4] = (uint8)Dst;
	msg.BoardCmm.dstMac1[5] = (uint8)(Dst >> 8);
	msg.BoardCmm.surMac1[0] = 0x01;
	msg.BoardCmm.surMac1[1] = 0x0C;
	msg.BoardCmm.surMac1[2] = 0xCD;
	msg.BoardCmm.surMac1[3] = 0x01;
	msg.BoardCmm.surMac1[4] = 0x01;
	msg.BoardCmm.surMac1[5] = 0x00;
	msg.BoardCmm.frameType = FpgaMsgProc::E_Board_Cmm_C2F;
	msg.BoardCmm.frameType1 = Type;
	msg.BoardCmm.res = 0;
	msg.BoardCmm.res1 = 0;

	AddSum();

	FpgaMsgProc* msgProc = SptSampIntMsgProc::Instance().FpgaMsgProc();
	if (!msgProc)
	{
		return -1;
	}
	return msgProc->SlowSend(&msg.BoardCmm.dstMac[0], writer + 38);
}
int32 spt::CpuFpgaCmmMsgBuf::BoardCmmIntSend(int32 EmacNo, uint16 Dst, uint16 Type)
{
	msg.BoardCmm.frameLen1 = writer + 2;
	msg.BoardCmm.frameLen = writer + 20;
	uint32 len = writer;
	if (msg.BoardCmm.frameLen >= sizeof(msg.BoardCmm.data1))
	{
		len = sizeof(msg.BoardCmm.data1) - 20;
		msg.BoardCmm.frameLen = len + 20;
		msg.BoardCmm.frameLen1 = len + 2;
	}
	msg.BoardCmm.dstMac1[0] = 0x01;
	msg.BoardCmm.dstMac1[1] = 0x0C;
	msg.BoardCmm.dstMac1[2] = 0xCD;
	msg.BoardCmm.dstMac1[3] = 0x01;
	msg.BoardCmm.dstMac1[4] = (uint8)Dst;
	msg.BoardCmm.dstMac1[5] = (uint8)(Dst >> 8);
	msg.BoardCmm.surMac1[0] = 0x01;
	msg.BoardCmm.surMac1[1] = 0x0C;
	msg.BoardCmm.surMac1[2] = 0xCD;
	msg.BoardCmm.surMac1[3] = 0x01;
	msg.BoardCmm.surMac1[4] = 0x01;
	msg.BoardCmm.surMac1[5] = 0x00;
	msg.BoardCmm.frameType = FpgaMsgProc::E_Board_Cmm_C2F;
	msg.BoardCmm.frameType1 = Type;
	msg.BoardCmm.res = 0;
	msg.BoardCmm.res1 = 0;

	AddSum();

	FpgaMsgProc* msgProc = SptSampIntMsgProc::Instance().FpgaMsgProc();
	if (!msgProc)
	{
		return -1;
	}
	return msgProc->IntSend(&msg.BoardCmm.dstMac[0], writer + 38);
}
uint16 spt::CpuFpgaCmmMsgBuf::Write(void* Sur, uint16 Size)
{
	if (writer >= sizeof(msg.BoardCmm.data1))
	{
		writer = sizeof(msg.BoardCmm.data1);
		return 0;
	}
	uint16 w = writer + Size;
	if (w >= sizeof(msg.BoardCmm.data1))
	{
		return 0;
	}
	MemCpy(&msg.BoardCmm.data1[writer], Sur, Size);
	writer = w;
	return Size;
}
bool8 spt::CpuFpgaCmmMsgBuf::IsCmmSumOk()
{
	uint16 len = msg.msg.frameLen - 2;
	if (len >= sizeof(msg.msg.buf))
	{
		return 0;
	}
	uint16 sum = 0;
	for (uint16 i = 0; i < len; i++)
	{
		sum += msg.msg.buf[i];
	}
	uint16 fsum = msg.msg.buf[len];
	fsum += ((uint16)(msg.msg.buf[len + 1])) << 8;
	if (fsum == sum)
	{
		return 1;
	}
	return 0;
}
bool8 spt::CpuFpgaCmmMsgBuf::IsBoardCmmSumOk()
{
	uint16 len = msg.BoardCmm.frameLen1 - 2;
	if (len >= sizeof(msg.BoardCmm.data1))
	{
		return 0;
	}
	uint16 sum = 0;
	for (uint16 i = 0; i < len; i++)
	{
		sum += msg.BoardCmm.data1[i];
	}
	uint16 fsum = msg.BoardCmm.data1[len];
	fsum += ((uint16)(msg.BoardCmm.data1[len + 1])) << 8;
	if (fsum == sum)
	{
		return 1;
	}
	return 0;
}
uint16 spt::CpuFpgaCmmMsgBuf::CalcSum()
{
	uint32 len = writer;
	uint16 sum = 0;
	for (uint16 i = 0; i < len; i++)
	{
		sum += msg.BoardCmm.data1[i];
	}
	return sum;
}
spt::CpuFpgaCmmMsgBuf::CpuFpgaCmmMsgBuf()
{
	writer = reader = 0;
}