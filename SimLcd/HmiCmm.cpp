#include "ApiProject.h"
using namespace spt;

#ifdef GZK_LCD
#include"LcdMain.h"
#endif

HmiLcdCmm& spt::HmiLcdCmm::Instance()
{
	static HmiLcdCmm inst;
	return inst;
}

int32 spt::HmiLcdCmm::PowerUpIni(int32 Para)
{
#ifdef WIN32_SIM
	HmiTcpCmmChannel::PowerUpIni(0);
#else
	HmiSerialCmmChannel::PowerUpIni(0);
#endif
	return 0;
}

int32 spt::HmiLcdCmm::OneLoop()
{
	HmiLcdHeartCheck();
	HeartBeat();
	switch (taskStep)
	{
	case spt::HmiLcdCmm::E_PowerUpIni:
	{
		taskStep = E_Work;
		break;
	}
	case spt::HmiLcdCmm::E_Restart:
	{
		break;
	}
	case spt::HmiLcdCmm::E_Work:
	{
		{
			int cnt = 0;
			while (cnt < 40)
			{
				cnt++;
				LcdMsg msg;
				if (Recv(msg) > 0)
				{
					int32 res = Unpack((LcdMsgContext*)&msg.data);
					if (res < 0)
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
		}
		break;
	}
	default:
	{
		taskStep = E_PowerUpIni;
		break;
	}
	}
	return 0;
}

int32 spt::HmiLcdCmm::Proc()
{
#ifdef WIN32_SIM
	HmiTcpCmmChannel::Proc();
#else 
	HmiSerialCmmChannel::Proc();
#endif
	OneLoop();
	CheckStatus();
	return 0;
}

int32 spt::HmiLcdCmm::Unpack(LcdMsgContext* msg)
{
	heartBeatCheck.Restart();
	GraphicDevice& gd = GraphicDevice::Instance();
	switch (msg->type)
	{
	case E_DrawAssic:
	{
		LcdDrawAssicMsg* msg1 = (LcdDrawAssicMsg*)msg;
		if (msg1->len >= sizeof(msg1->msg))
		{
			break;
		}
		msg1->msg[msg1->len] = 0;
		gd.DrawAssic(msg1->x, msg1->y, msg1->color, msg1->msg);
		break;
	}
	case E_DrawStr:
	{
		LcdDrawAssicMsg* msg1 = (LcdDrawAssicMsg*)msg;
		if (msg1->len >= sizeof(msg1->msg))
		{
			break;
		}
		msg1->msg[msg1->len] = 0;
		gd.DrawStr(msg1->x, msg1->y, msg1->color, msg1->msg);
		break;
	}
	case E_DrawLine:
	{
		LcdDrawRect* msg1 = (LcdDrawRect*)msg;
		if (msg1->len != sizeof(LcdDrawRect))
		{
			break;
		}
		gd.DrawLine(msg1->x, msg1->y, msg1->color, msg1->w, msg1->h);
		break;
	}
	case E_DrawRect:
	{
		LcdDrawRect* msg1 = (LcdDrawRect*)msg;
		if (msg1->len != sizeof(LcdDrawRect))
		{
			break;
		}
		gd.DrawRect(msg1->x, msg1->y, msg1->color, msg1->w, msg1->h);
		break;
	}
	case E_ClearRect:
	{
		LcdDrawRect* msg1 = (LcdDrawRect*)msg;
		if (msg1->len != sizeof(LcdDrawRect))
		{
			break;
		}
		gd.ClearRect(msg1->x, msg1->y, msg1->color, msg1->w, msg1->h);
		break;
	}
	case E_ClearAll:
	{
		LcdDrawCmd* msg1 = (LcdDrawCmd*)msg;
		if (msg1->len != sizeof(LcdDrawCmd))
		{
			break;
		}
		gd.ClearAll();
		break;
	}
	case E_UpdateRect:
	{
		LcdDrawRect* msg1 = (LcdDrawRect*)msg;
		if (msg1->len != sizeof(LcdDrawRect))
		{
			break;
		}
		gd.Update(msg1->x, msg1->y, msg1->w, msg1->h);
		return -1;
		break;
	}
	case E_UpdateAll:
	{
		LcdDrawCmd* msg1 = (LcdDrawCmd*)msg;
		if (msg1->len != sizeof(LcdDrawCmd))
		{
			break;
		}
		gd.Update();
		return -1;
		break;
	}
	case E_DrawUint32:
	{
		LcdDrawData* msg1 = (LcdDrawData*)msg;
		if (msg1->len != sizeof(LcdDrawRect))
		{
			break;
		}
		gd.DrawUint32(msg1->x, msg1->y, msg1->color, msg1->data, msg1->fraBit, msg1->isRight);
		break;
	}
	case E_LcdHeartBeat:
	{
		LcdHeartBeat* msg1 = (LcdHeartBeat*)msg;
		if (msg1->len != sizeof(LcdHeartBeat))
		{
			break;
		}
		uint64 ms = msg1->PowerUpTimerMsL;
		ms = ms + ((uint64)(msg1->PowerUpTimerMsH) << 32);
		break;
	}
	case E_SockClose:
	{
#ifdef WIN32_SIM
		Close();
#endif
		break;
	}
	case E_IedName:
	{
#ifdef WIN32_SIM
		LcdIedInfo* msg1 = (LcdIedInfo*)msg;
		if (msg1->len >= sizeof(LcdIedInfo))
		{
			break;
		}
		LcdSetDispInfo(msg1->ledNum, msg1->data);
#endif // WIN32_SIM
		break;
	}
	case E_LedInfoAsw:
	{
#ifdef WIN32_SIM
		LcdIedInfo* msg1 = (LcdIedInfo*)msg;
		if (msg1->len >= sizeof(LcdIedInfo))
		{
			break;
		}
		LcdSetLedDispInfo(msg1->ledNum, msg1->cor, msg1->data);
#endif // WIN32_SIM
		break;
	}
	case E_LedInfoVal:
	{
		LcdIedInfo* msg1 = (LcdIedInfo*)msg;
		if (msg1->len >= sizeof(LcdIedInfo))
		{
			break;
		}
		int32 num = msg1->ledNum;
		if (num >= sizeof(msg1->data))
		{
			break;
		}
		for (int32 i = 0; i < num; i++)
		{
			LcdSetLedDispVal(i, msg1->data[i]);
		}
		break;
	}
	case E_DrawBitMap:
	{
		LcdDrawBitMap* msg1 = (LcdDrawBitMap*)msg;
		if (msg1->len != sizeof(LcdDrawBitMap))
		{
			break;
		}
		gd.DrawBitMap(msg1->x, msg1->y, msg1->code, msg1->color);
		break;
	}
	case E_DrawPicLine:
	{
		LcdPicMode* msg1 = (LcdPicMode*)msg;
		for (uint16 i = 0; i < msg1->h; i++)
		{
			HalLcdDriver::Instance().SetBuf(msg1->x, msg1->y + i, msg1->data + i * msg1->w, msg1->w);
		}
		break;
	}
	case E_DrawPicUpdate:
	{
		LcdPicMode* msg1 = (LcdPicMode*)msg;
		gd.Update(msg1->x, msg1->y, msg1->w, msg1->h);
		break;
	}
	default:
		break;
	}
	return 0;
}

spt::HmiLcdCmm::HmiLcdCmm()
{
	taskStep = 0;

}
void spt::HmiLcdCmm::HeartBeat()
{
	if (heartBeat.Status())
	{
		heartBeat.Restart();
		LcdHeartBeat beat;
		beat.type = E_LcdHeartBeat;
		beat.len = sizeof(beat);
#ifdef WIN32_SIM
		beat.Ctx[0] = 0;
#else
		beat.Ctx[0] = 1;
#endif // WIN32_SIM
		beat.Ctx[1] = (uint16)LcdMain::Instance().Version();
		beat.Ctx[2] = (uint16)(LcdMain::Instance().ProgDate() >> 16);
		beat.Ctx[3] = (uint16)(LcdMain::Instance().ProgDate());
		beat.Ctx[4] = (uint16)(LcdMain::Instance().ProgCrc());
		beat.Ctx[5] = (uint16)(LcdMain::Instance().CheckCrc());
		uint64 ms = SptMsInt::Instance().PowerUpMsCnt64();
		beat.PowerUpTimerMsL = (uint32)ms;
		beat.PowerUpTimerMsH = (uint32)(ms >> 32);
		HmiLcdCmm::Instance().Send((LcdMsgContext*)&beat);
	}
	else if (!heartBeat.IsStart())
	{
		heartBeat.UpCnt(1000);
		heartBeat.Enable(1);
	}
}
void spt::HmiLcdCmm::HmiLcdHeartCheck()
{
#ifdef GZK_LCD
	CheckStatus();
	if (!IsLcdCmmOk())
	{
		LcdSetLedDispVal(0, 0);
	}
#else 
	ApiStatus& warn = SptApiStatus[E_SAS_LCDCMMERR];
	if (heartBeatCheck.Status())
	{
		if (!warn.Value().bl)
		{
			LogWarn.Stamp() << "Lcd cmm stop.\n";
		}
		warn.Update(1);
	}
	else
	{
		if (warn.Value().bl)
		{
			LogWarn.Stamp() << "Lcd cmm ok.\n";
		}
		warn.Update(0);
		if (!heartBeatCheck.IsStart())
		{
			heartBeatCheck.Enable(1);
			heartBeatCheck.UpCnt(10000);
		}
	}
#endif
}
int32 spt::HmiLcdCmm::ProcIn()
{
	return int32();
}
int32 spt::HmiLcdCmm::ProcOut()
{
	return int32();
}
void spt::HmiLcdCmm::Send(LcdMsgContext* Msg)
{
	SendMsg(Msg, Msg->len);
}

bool8 spt::HmiLcdCmm::IsLcdCmmOk()
{
#ifdef WIN32_SIM
	return IsLinkOk();
#else
	return IsCmmOk();
#endif // !WIN32_SIM
}
#ifdef WIN32_SIM
int32 spt::HmiTcpCmmChannel::PowerUpIni(int32 Para)
{
	frmHeader.header = 0xd555;
	frmHeader.sur = 33003;
	frmHeader.dst = 33002;
	frmHeader.type = SCT_LCD;
	driver = 0;
	driverNum = 0;
	frameBufLen = 1024;
	appSendMsgPool.PowerUpIni(256, frameBufLen);
	appRecMsgPool.PowerUpIni(16, frameBufLen);
	halSendPool.Alloc(1, frameBufLen * 32);
	halRecvPool.Alloc(1, frameBufLen * 32);
	return 0;
}

int32 spt::HmiTcpCmmChannel::SendMsg(void* Data, uint16 DataLen)
{
	SalCmmMsgBufCtrl* ctrl = appSendMsgPool.GetNextWriteBuf();
	if (ctrl && ctrl->buf)
	{
		DbgMsg& msg = *(DbgMsg*)ctrl->buf;
		msg.header.header = frmHeader.header;
		msg.header.sur = frmHeader.sur;
		msg.header.dst = frmHeader.dst;
		msg.header.type = frmHeader.type;
		msg.header.len = DataLen + sizeof(msg.header);
		if (msg.header.len > frameBufLen)
		{
			ctrl->SetReaded();
			ctrl->SetWrited();
			outPut.sendErrCnt++;
			return 0;
		}
		MemCpy(msg.data, Data, DataLen);
		ctrl->AddCrc();
		ctrl->isUsed = 1;
		ctrl->SetWrited();
		return DataLen;
	}
	else
	{
		appSendMsgPool.FreeAllBuf();
	}
	return -1;
}

int32 spt::HmiTcpCmmChannel::Recv(LcdMsg& Msg)
{
	if (halRecvPool.IsEmpty())
	{
		return 0;
	}
	while (sizeof(Msg.header) == halRecvPool.PreRead(&Msg.header, sizeof(Msg.header)))
	{
		if (Msg.header.header == 0xd555)
		{
			if (Msg.header.len > sizeof(Msg))
			{
				halRecvPool.ReaderAdd(1);
			}
			else
			{
				if (Msg.header.len < halRecvPool.ValidCtxLen())
				{
					halRecvPool.Read(&Msg.header, Msg.header.len + sizeof(Msg.checkCode));
					if (Crc16ModBus.IsCrcOk(&Msg, Msg.header.len + sizeof(Msg.checkCode)))
					{
						outPut.recvCnt++;
						return Msg.header.len;
					}
					else
					{
						outPut.recvErrCnt++;
					}
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			halRecvPool.ReaderAdd(1);
		}
	}
	return 0;
}

int32 spt::HmiTcpCmmChannel::ProcIn()
{
	if (virlcdCmm.IsReadAble() == 0)
	{
		return 0;
	}
	char buf[1024];
	int32 res = virlcdCmm.Recv(buf, sizeof(buf), 0);
	if (res > 0)
	{
		DecryptData(buf, (uint32)res, 59);
		halRecvPool.Write(buf, res);
	}
	return 0;
}

int32 spt::HmiTcpCmmChannel::Proc()
{
	HmiTcpCmmChannel::ProcIn();
	HmiTcpCmmChannel::ProcOut();
	if (forceClose)
	{
		forceClose = 0;
		virlcdCmm.Close();
	}
	return int32();
}

int32 spt::HmiTcpCmmChannel::ProcOut()
{
	SalCmmMsgBufCtrl* ctrl = appSendMsgPool.GetNextReadBuf();
	halSendPool.Clear();
	DbgMsg* msg;
	while (ctrl)
	{
		msg = (DbgMsg*)ctrl->buf;
		if (!msg->header.IsCrcOk())
		{
			outPut.sendErrCnt++;
			ctrl->SetReaded();
		}
		else
		{
			halSendPool.Write(msg, msg->header.len + sizeof(DbgMsg::checkCode));
			ctrl->SetReaded();
			if (halSendPool.Top() >= 512)
			{
				break;
			}
		}
		ctrl = appSendMsgPool.GetNextReadBuf();
	}
	appSendMsgPool.UpdateReader();
	if (halSendPool.Top())
	{
		if (halSendPool.Top() > 58)
		{
			msg = 0;
		}
		if (virlcdCmm.IsLinkOk())
		{
			EncryptData(halSendPool.BufBase(), halSendPool.Top(), 59);
			int32 res = virlcdCmm.Send(halSendPool.BufBase(), halSendPool.Top(), 0);
			if (res == halSendPool.Top())
			{
				outPut.sendCnt++;
			}
			else
			{
				outPut.sendErrCnt++;
			}
		}
		else
		{
			sendCnt++;
		}
	}
	return 0;
}

void spt::HmiTcpCmmChannel::Close()
{
#ifdef WIN32_LCD_SIM
	LcdDrawCmd cmd;
	cmd.type = E_SockClose;
	cmd.len = sizeof(cmd);
	HmiLcdCmm::Instance().Send((LcdMsgContext*)&cmd);
#endif
	forceClose = 1;
}

bool8 spt::HmiTcpCmmChannel::IsLinkOk()
{
	return virlcdCmm.IsClientOk();
}

int32 spt::HmiTcpCmmChannel::StartClient(uint32 LocalIp, uint16 LocalPort, uint32 RemoteIp, uint16 RemotePort)
{
	if (virlcdCmm.IsLinkOk())
	{
		return -1;
	}
	virlcdCmm.SetLocalIp(LocalIp);
	virlcdCmm.SetLocalPort(LocalPort);
	virlcdCmm.SetRemoteIp(RemoteIp);
	virlcdCmm.SetRemotePort(RemotePort);
	virlcdCmm.EnableGmssl(DbgSimCfg::Instance().EnableGmssl.Data());
	return virlcdCmm.StartNonBlock();
}

int32 spt::HmiTcpCmmChannel::CheckStatus()
{
	if (!msTimer.IsEnable())
	{
		msTimer.UpCnt(5000);
		if (virlcdCmm.IsLinkOk())
		{
			msTimer.Enable(1);
		}
	}
	else if (outPut.recvCnt != recvCntBak)
	{
		msTimer.Restart();
	}
	else if (msTimer.Status())
	{
		msTimer.Enable(0);
		if (virlcdCmm.IsLinkOk())
		{
		}
		virlcdCmm.Close();
		recvCntBak = outPut.recvCnt;
		return -1;
	}
	recvCntBak = outPut.recvCnt;
	if (!virlcdCmm.IsLinkOk())
	{
		return -1;
	}
	return 0;
}
spt::HmiTcpCmmChannel::HmiTcpCmmChannel()
{

}
#endif
int32 spt::HmiSerialCmmChannel::PowerUpIni(int32 Para)
{
	cmmOk = 0;
	frmHeader.header = 0xd555;
	frmHeader.sur = 33003;
	frmHeader.dst = 33002;
	frmHeader.type = SCT_LCD;
	driver = 0;
	driverNum = 0;
	frameBufLen = 128;
	static char sendbuf[512];
	static char recbuf[1024 * 16];
	halSendPool.SetBuf(sendbuf, 1, sizeof(sendbuf));
	halRecvPool.SetBuf(recbuf, 1, sizeof(recbuf));
	return 0;
}

int32 spt::HmiSerialCmmChannel::SendMsg(void* Data, uint16 DataLen)
{
	LcdMsg msg;
	msg.header.header = frmHeader.header;
	msg.header.sur = frmHeader.sur;
	msg.header.dst = frmHeader.dst;
	msg.header.type = frmHeader.type;
	msg.header.len = DataLen + sizeof(msg.header);
	if (msg.header.len > frameBufLen)
	{
		return 0;
	}
	MemCpy(msg.data, Data, DataLen);
	msg.header.AddCrc();
	halSendPool.Write(&msg, msg.header.len + sizeof(msg.checkCode));
	return DataLen;
}

int32 spt::HmiSerialCmmChannel::Recv(LcdMsg& Msg)
{
	if (halRecvPool.IsEmpty())
	{
		return 0;
	}
	while (sizeof(Msg.header) == halRecvPool.PreRead(&Msg.header, sizeof(Msg.header)))
	{
		if (Msg.header.header == 0xd555)
		{
			if (Msg.header.len > sizeof(Msg))
			{
				halRecvPool.ReaderAdd(1);
			}
			else
			{
				if (Msg.header.len < halRecvPool.ValidCtxLen())
				{
					halRecvPool.Read(&Msg.header, Msg.header.len + sizeof(Msg.checkCode));
					if (Crc16ModBus.IsCrcOk(&Msg, Msg.header.len + sizeof(Msg.checkCode)))
					{
						outPut.recvCnt++;
						return Msg.header.len;
					}
					else
					{
						outPut.recvErrCnt++;
					}
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			halRecvPool.ReaderAdd(1);
		}
	}
	return 0;
}

int32 spt::HmiSerialCmmChannel::ProcIn()
{
	char buf[512];
	int32 res = SptReadSerialData(E_HSPN_LCD_CMM, buf, sizeof(buf));
	if (res > 0)
	{
		halRecvPool.Write(buf, res);
	}
	return 0;
}

int32 spt::HmiSerialCmmChannel::Proc()
{
	HmiSerialCmmChannel::ProcIn();
	HmiSerialCmmChannel::ProcOut();
	return int32();
}

int32 spt::HmiSerialCmmChannel::ProcOut()
{
	if (halSendPool.IsEmpty() == 1)
	{
		return 0;
	}
	uint32 r = halSendPool.Bottom();
	uint32 w = halSendPool.Top();
	if (r < w)
	{
		int32 res = SptSendSerialData(E_HSPN_LCD_CMM, (uint8*)halSendPool.BufBase() + r, w - r);
		if (res > 0)
		{
			outPut.sendCnt++;
			halSendPool.ReaderAdd(res);
		}
		else
		{
			outPut.sendErrCnt++;
		}
	}
	else
	{
		int32 res = SptSendSerialData(E_HSPN_LCD_CMM, (uint8*)halSendPool.BufBase() + r, halSendPool.BufSize() - r);
		if (res > 0)
		{
			outPut.sendCnt++;
			halSendPool.ReaderAdd(res);
		}
		else
		{
			outPut.sendErrCnt++;
		}
	}
	return 0;
}

bool8 spt::HmiSerialCmmChannel::IsCmmOk()
{
	return cmmOk;
}

int32 spt::HmiSerialCmmChannel::StartClient(uint32 LocalIp, uint16 LocalPort, uint32 RemoteIp, uint16 RemotePort)
{
	return int32();
}

int32 spt::HmiSerialCmmChannel::CheckStatus()
{
	if (outPut.recvCnt != recvCntBak)
	{
		msTimer.Restart();
		cmmOk = 1;
	}
	if (!msTimer.IsEnable())
	{
		msTimer.UpCnt(60000);
		if (cmmOk)
		{
			msTimer.Enable(1);
		}
	}
	else if (msTimer.Status())
	{
		msTimer.Enable(0);
		recvCntBak = outPut.recvCnt;
		cmmOk = 0;
		return -1;
	}
	recvCntBak = outPut.recvCnt;
	return 0;
}
spt::HmiSerialCmmChannel::HmiSerialCmmChannel()
{

}
