#include "ApiProject.h"
using namespace spt;

HmiLcdCmm& spt::HmiLcdCmm::Instance()
{
	static HmiLcdCmm inst;
	return inst;
}

int32 spt::HmiLcdCmm::PowerUpIni(int32 Para)
{
	heartBeatCheck.SetCnt(20000, 1000);
	heartBeatCheck.Enable(1);
	virHeartBeatCheck.SetCnt(20000, 1000);
	virHeartBeatCheck.Enable(1);
	tcpCmm.PowerUpIni(0);
	serialCmm.PowerUpIni(0);
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
		// 状态栏显示
		HmiStatusBar::Instance().Show();
		GraphicDevice::Instance().UpdateLcd();
		//虚拟液晶通讯
		{
			int cnt = 0;
			while (cnt < 40)
			{
				cnt++;
				LcdMsg msg;
				if (tcpCmm.Recv(msg) > 0)
				{
					Unpack((LcdMsgContext*)&msg.data);
				}
				else
				{
					break;
				}
			}
		}
		//串口通讯
		{
			int cnt = 0;
			while (cnt < 40)
			{
				cnt++;
				LcdMsg msg;
				if (serialCmm.Recv(msg) > 0)
				{
					Unpack((LcdMsgContext*)&msg.data);
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
	tcpCmm.Proc();
	serialCmm.Proc();
	OneLoop();
	tcpCmm.ProcOut();
	serialCmm.ProcOut();
	outPut = serialCmm.OutPut();
	return 0;
}

void spt::HmiLcdCmm::Unpack(LcdMsgContext* msg)
{
	switch (msg->type)
	{
	case E_KeyMsg:
	{
		LcdKeyMsg* msg1 = (LcdKeyMsg*)msg;
		if (msg1->len != sizeof(LcdKeyMsg))
		{
			break;
		}
		HmiKey key;
		key.Key1 = msg1->key1;
		key.Key2 = msg1->key2;
		key.Key3 = msg1->key3;
		key.Key4 = msg1->key4;
		HmiKeyService::Instance().Push(key);
		break;
	}
	case E_LcdHeartBeat:
	{
		LcdHeartBeat* msg1 = (LcdHeartBeat*)msg;
		if (msg1->len != sizeof(LcdHeartBeat))
		{
			break;
		}
		SalComVersion* lcdInfo = 0;
		if (msg1->Ctx[0] == 0)
		{
			lcdInfo = &ApiVersionInfo::Instance().VirLcdVersion();
		}
		else if (msg1->Ctx[0] == 1)
		{
			lcdInfo = &ApiVersionInfo::Instance().LcdVersion();
		}
		if (lcdInfo)
		{
			if (lcdInfo->RtCrc != msg1->Ctx[5])
			{
				lcdInfo->ProgVersion = msg1->Ctx[1];
				lcdInfo->ProgDate = ((uint32)msg1->Ctx[2] << 16) | msg1->Ctx[3];
				lcdInfo->ProgCrc = msg1->Ctx[4];
				lcdInfo->RtCrc = msg1->Ctx[5];
			}
		}
		uint64 ms = msg1->PowerUpTimerMsL;
		ms = ms + ((uint64)(msg1->PowerUpTimerMsH) << 32);
		break;
	}
	case E_IedName:
	{
		LcdIedInfo lmc;

		lmc.type = E_IedName;
		lmc.len = sizeof(lmc) - sizeof(lmc.data);
		InstObjectGroup* gp = InstObjectRoot::Instance().GetGroup(EIOT_HMILED);
		if (gp)
		{
			lmc.ledNum = gp->InstNum();
		}
		else
		{
			lmc.ledNum = 0;
		}
		const ApiAppCfg* appcfg = SptMain::Instance().AppCfg();
		if (appcfg)
		{
			StrNCpy(lmc.data, appcfg->hmicfg.DispName, sizeof(lmc.data));
			lmc.len += StrLen(lmc.data) + 1;
		}
		else
		{
			StrNCpy(lmc.data, "默认名称", sizeof(lmc.data));
			lmc.len += StrLen(lmc.data) + 1;
		}
		HmiLcdCmm::Instance().Send((LcdMsgContext*)&lmc);
		break;
	}
	case E_LedInfoAsk:
	{
		LcdIedInfo* lii = (LcdIedInfo*)msg;

		LcdIedInfo lmc;

		lmc.type = E_LedInfoAsw;
		lmc.len = sizeof(lmc) - sizeof(lmc.data);
		InstObjectGroup* gp = InstObjectRoot::Instance().GetGroup(EIOT_HMILED);
		if (gp)
		{
			lmc.ledNum = lii->ledNum;
			if (gp->InstNum() <= lmc.ledNum)
			{
				return;
			}
			HmiLedGroup* Group = (HmiLedGroup*)gp;
			HmiLed* led = Group->GetObject(lii->ledNum);
			if (led)
			{
				char* buf = lmc.data;
				*buf++ = led->GetRow();
				*buf++ = led->GetCol();
				StrNCpy(buf, led->Name(), sizeof(lmc.data));
				lmc.len += StrLen(buf) + 3;
				lmc.cor = led->GetColor();
			}
			else
			{
				return;
			}
		}
		else
		{
			return;
		}
		Send((LcdMsgContext*)&lmc);
		break;
	}
	case E_SockClose:
	{
		tcpCmm.Close();
		LogMsg.Stamp() << "HmiCmm Socket Ask Closed.\n";
		break;
	}
	default:
		break;
	}
}

spt::HmiLcdCmm::HmiLcdCmm()
{
	taskStep = 0;
	SptPublicCmmTask::Instance().RgsAppCmmTask(this);
	StrNCpy(name, "HmiCmm", sizeof(name));
}
int32 spt::HmiLcdCmm::StartServer(uint32 LocalIp, uint16 LocalPort, uint32 RemoteIp, uint16 RemotePort, int32 ClientSock)
{
	return tcpCmm.StartServer(LocalIp, LocalPort, RemoteIp, RemotePort, ClientSock);
}
void spt::HmiLcdCmm::HeartBeat()
{
	if (heartBeat.Status())
	{
		heartBeat.Restart();
		LcdHeartBeat beat;
		beat.type = E_LcdHeartBeat;
		beat.len = sizeof(beat);
		uint64 ms = SptMsInt::Instance().MsCnt64();
		beat.PowerUpTimerMsL = (uint32)ms;
		beat.PowerUpTimerMsH = (uint32)(ms >> 32);
		Send((LcdMsgContext*)&beat);
	}
	else if (!heartBeat.IsStart())
	{
		heartBeat.UpCnt(1000);
		heartBeat.Enable(1);
	}
}
void spt::HmiLcdCmm::HmiLcdHeartCheck()
{
	SptApiStatus[E_SAS_LcdCmmErr].Update(heartBeatCheck.Status(0 == serialCmm.IsCmmOk()));
	SptApiStatus[E_SAS_VirLcdCmmErr].Update(virHeartBeatCheck.Status(0 == tcpCmm.IsLinkOk()));
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
	if (GraphicDevice::Instance().DrawMode() & GraphicDevice::E_PicMode)
	{
		if ((Msg->type == E_LedInfoVal)
			|| (Msg->type == E_LcdHeartBeat)
			|| (Msg->type == E_IedName)
			|| (Msg->type == E_LedInfoAsw)
			)
		{
			tcpCmm.SendMsg(Msg, Msg->len);
		}
	}
	else
	{
		tcpCmm.SendMsg(Msg, Msg->len);
	}
	const struct ApiAppCfg* cfg = SptMain::Instance().AppCfg();
	if (!cfg)
	{
		return;
	}
	if (EH_GZKSAU == cfg->platform.hardware)
	{
		if ((Msg->type == E_LedInfoVal) || (Msg->type == E_LcdHeartBeat))
		{
			serialCmm.SendMsg(Msg, Msg->len);
		}
	}
}

void spt::HmiLcdCmm::Send(LcdPicMode* Msg)
{
	if (GraphicDevice::Instance().DrawMode() & GraphicDevice::E_PicMode)
	{
		tcpCmm.SendMsg(Msg, Msg->len);
	}
}

bool8 spt::HmiLcdCmm::IsVirLcdCmmOk()
{
	return tcpCmm.IsLinkOk();
}

int32 spt::HmiTcpCmmChannel::PowerUpIni(int32 Para)
{
	StrNCpy(name, "HmiTcpCmm", sizeof(name));
	frmHeader.header = 0xd555;
	frmHeader.sur = 33002;
	frmHeader.dst = 33003;
	frmHeader.type = SCT_LCD;
	driver = 0;
	driverNum = 0;
	frameBufLen = 1024;
	appSendMsgPool.PowerUpIni(256, frameBufLen);
	appRecMsgPool.PowerUpIni(16, frameBufLen);
	halSendPool.Alloc(1, frameBufLen * 128);
	halRecvPool.Alloc(1, frameBufLen * 8);
	return 0;
}

int32 spt::HmiTcpCmmChannel::SendMsg(void* Data, uint16 DataLen)
{
	if (logOk == 0)
	{
		return 0;
	}
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
	if (logOk == 0)
	{
		return 0;
	}
	SalCmmMsgBufCtrl* ctrl = appRecMsgPool.GetNextReadBuf();
	if (ctrl)
	{
		DbgMsg& msg = *(DbgMsg*)ctrl->buf;
		MemCpy(&Msg, ctrl->buf, msg.header.len);
		ctrl->SetReaded();
		appRecMsgPool.UpdateReader();
		outPut.recvCnt++;
		return msg.header.len;
	}
	appRecMsgPool.UpdateReader();
	return 0;
}

int32 spt::HmiTcpCmmChannel::ProcIn()
{
	if (logOk == 0)
	{
		return 0;
	}
	char buf[2048];
	int32 res = virlcdCmm.Recv(buf, sizeof(buf), 0);
	if (res > 0)
	{
		DecryptData(buf, (uint32)res, 59);
		halRecvPool.Write(buf, res);
	}
	if (halRecvPool.IsEmpty())
	{
		return 0;
	}
	LcdMsg msg;
	while (sizeof(msg.header) == halRecvPool.PreRead(&msg.header, sizeof(msg.header)))
	{
		if (msg.header.header == 0xd555)
		{
			if (msg.header.len > sizeof(msg))
			{
				halRecvPool.ReaderAdd(1);
				outPut.recvErrCnt++;
				LogMsg.Stamp() << "Lcd len err\n";
			}
			else
			{
				if (msg.header.len < halRecvPool.ValidCtxLen())
				{
					halRecvPool.Read(&msg.header, msg.header.len + sizeof(msg.checkCode));
					if (Crc16ModBus.IsCrcOk(&msg, msg.header.len + sizeof(msg.checkCode)))
					{
						SalCmmMsgBufCtrl* ctrl = appRecMsgPool.GetNextWriteBuf();
						if (ctrl && ctrl->buf)
						{
							DbgMsg& Dmsg = *(DbgMsg*)ctrl->buf;

							if (msg.header.len > frameBufLen)
							{
								ctrl->SetReaded();
								ctrl->SetWrited();
								return 0;
							}
							MemCpy(&Dmsg, &msg, msg.header.len);
							ctrl->SetWrited();
						}
						else
						{
							appRecMsgPool.FreeAllBuf();
						}
					}
					else
					{
						outPut.recvErrCnt++;
						LogMsg.Stamp() << "Lcd Recv crc err\n";
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
			LogMsg.Stamp() << "Lcd halRecvPool.ReaderAdd(1)\n";
		}
	}
	return 0;
}

int32 spt::HmiTcpCmmChannel::Proc()
{
	HmiTcpCmmChannel::ProcIn();
	HmiTcpCmmChannel::ProcOut();
	CheckStatus();
	return int32();
}

int32 spt::HmiTcpCmmChannel::ProcOut()
{
	if (!sendTimer.Status())
	{
		if (!sendTimer.IsEnable())
		{
			sendTimer.UpCnt(20);
			sendTimer.Enable(1);
		}
		return 0;
	}
	SalCmmMsgBufCtrl* ctrl = appSendMsgPool.GetNextReadBuf();
	halSendPool.Clear();
	DbgMsg* msg;
	while (ctrl)
	{
		msg = (DbgMsg*)ctrl->buf;
		if (!msg->header.IsCrcOk())
		{
			LogMsg.Stamp() << "Lcd Send crc err\n";
			outPut.sendErrCnt++;
			ctrl->SetReaded();
		}
		else
		{

			halSendPool.Write(msg, msg->header.len + sizeof(DbgMsg::checkCode));
			ctrl->SetReaded();
			if (halSendPool.Top() >= halSendPool.BufSize())
			{
				break;
			}
		}
		ctrl = appSendMsgPool.GetNextReadBuf();
	}
	appSendMsgPool.UpdateReader();
	if (halSendPool.Top())
	{
		if (logOk)
		{
			EncryptData(halSendPool.BufBase(), halSendPool.Top(), 59);
			int32 res = virlcdCmm.Send(halSendPool.BufBase(), halSendPool.Top(), 0);
			if (res > 0)
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
	LcdDrawCmd cmd;
	cmd.type = E_SockClose;
	cmd.len = sizeof(cmd);
	HmiLcdCmm::Instance().Send((LcdMsgContext*)&cmd);
	virlcdCmm.Close();
	logOk = 0;
}

bool8 spt::HmiTcpCmmChannel::IsLinkOk()
{
	return virlcdCmm.IsLinkOk();
}

int32 spt::HmiTcpCmmChannel::StartServer(uint32 LocalIp, uint16 LocalPort, uint32 RemoteIp, uint16 RemotePort, int32 ClientSock)
{
	if (IsLinkOk())
	{
		LogMsg.Stamp() << "DbgLcd Socket is aready opened.\n";
		return -1;
	}
	virlcdCmm.SetLocalIp(LocalIp);
	virlcdCmm.SetLocalPort(LocalPort);
	virlcdCmm.SetRemoteIp(RemoteIp);
	virlcdCmm.SetRemotePort(RemotePort);
	virlcdCmm.EnableGmssl(DbgSimCfg::Instance().EnableGmssl.Data());
	virlcdCmm.SetClientSock(ClientSock);
	MsTimer timer;
	if (virlcdCmm.IsEnableGmssl())
	{
		virlcdCmm.CreatGmSock();
		timer.UpCnt(3000);
		timer.Enable(1);
		timer.Restart();
		while (!timer.Status())
		{
			MsSleep(50);
			if (virlcdCmm.GmAccept() >= 0)
			{
				break;
			}
		}
		if (timer.Status())
		{
			virlcdCmm.Close();
			LogWarn.Stamp() << "DbgLcd GmAccept Socket Accept Failed." << GetSocketLastError() << "\n";
			return -1;
		}
		else
		{
			LogMsg.Stamp() << "DbgLcd GmSocket Accept Ok.\n";
		}
	}
	virlcdCmm.SetLinkOk(1);
	String40B str;
	virlcdCmm.GetRemote(str);
	if (DbgToolsServer::Instance().LogOn(DbgToolsServer::E_VirLcd, virlcdCmm))
	{
		logOk = 1;
		LogMsg.Stamp() << "DbgLcd Log Ok.\n";
	}
	else
	{
		logOk = 0;
		LogMsg.Stamp() << "DbgLcd Log Err.\n";
		virlcdCmm.Close();
	}
	return  0;
}

int32 spt::HmiTcpCmmChannel::CheckStatus()
{
	if (!msTimer.IsEnable())
	{
		msTimer.UpCnt(10000);
		if (logOk && virlcdCmm.IsLinkOk())
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
			LogMsg.Stamp() << "DbgLcd Socket is Link Ok." << sendCnt << "\n";
			LogMsg << "Socket:" << outPut.sendCnt << outPut.sendErrCnt << outPut.recvCnt << outPut.recvErrCnt << "\n";
			LogMsg << "SendPool:" << appSendMsgPool.outPut.getWriteBufErrCnt << appSendMsgPool.outPut.writeCnt << appSendMsgPool.outPut.readCnt << "\n";
		}
		String20B str;
		virlcdCmm.GetRemote(str);
		DbgToolsServer::Instance().SetClientClose(DbgToolsServer::E_VirLcd, str.Str());
		recvCntBak = outPut.recvCnt;
		virlcdCmm.Close();
		logOk = 0;
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
	static char sendbuf[1024 * 60];
	static char recbuf[1024 * 2];
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
		outPut.sendErrCnt++;
		return 0;
	}
	MemCpy(msg.data, Data, DataLen);
	msg.header.AddCrc();
	halSendPool.Write(&msg, msg.header.len + sizeof(msg.checkCode));
	outPut.sendCnt++;
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
	return res;
}

int32 spt::HmiSerialCmmChannel::Proc()
{
	HmiSerialCmmChannel::ProcIn();
	HmiSerialCmmChannel::ProcOut();
	CheckStatus();
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
			halSendPool.ReaderAdd(res);
		}
	}
	else
	{
		int32 res = SptSendSerialData(E_HSPN_LCD_CMM, (uint8*)halSendPool.BufBase() + r, halSendPool.BufSize() - r);
		if (res > 0)
		{
			halSendPool.ReaderAdd(res);
		}
	}
	return 0;
}

bool8 spt::HmiSerialCmmChannel::IsCmmOk()
{
	return cmmOk;
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
