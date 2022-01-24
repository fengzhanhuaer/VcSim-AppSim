#include"ApiProject.h"
using namespace spt;


int32 spt::DbgServer::StartServer()
{
	EnableGmssl(DbgSimCfg::Instance().EnableGmssl.Data());
	if (StartNonBlock() == 0)
	{
		MsTimer timer;
		timer.UpCnt(10000);
		timer.Enable(1);
		int clientsock = 0;
		while (!timer.Status())
		{
			MsSleep(1);
			clientsock = Accept();
			if (clientsock > 0)
			{
				break;
			}
		}
		CloseListener();
		if (clientsock > 0)
		{
			spt::SetSocketNonBlock(clientsock, 1);
			LogMsg.Stamp() << "DbgLcd Socket Accept Ok.\n";
		}
		else
		{
			LogWarn.Stamp() << "DbgLcd Socket Accept Failed." << GetSocketLastError() << "\n";
			return -1;
		}
		if (IsEnableGmssl())
		{
			CreatGmSock();
			timer.UpCnt(10000);
			timer.Enable(1);
			timer.Restart();
			while (!timer.Status())
			{
				if (GmAccept() <= -1)
				{
					;
				}
				else
				{
					break;
				}
			}
			if (timer.Status())
			{
				LogWarn.Stamp() << "DbgLcd GmAccept Socket Accept Failed." << GetSocketLastError() << "\n";
				return -1;
			}
			SetLinkOk(1);
		}
	}
	else
	{
		return -1;
	}
	return  0;
}

bool8 spt::DbgServer::IsRuning()
{
	return IsOk();
}

int32 spt::DbgServer::CheckStatus(bool8 Restart)
{
	if ((recvPacketLast != recvPacket) || (sendPacketLast != sendPacket))
	{
		checkTimer.UpCnt(60 * 1000);
		checkTimer.Enable(0);
		checkTimer.Enable(1);
	}
	else if (checkTimer.Status())
	{
		Close();
		checkTimer.Enable(0);
	}
	else if (!checkTimer.IsEnable())
	{
		checkTimer.UpCnt(60 * 1000);
		checkTimer.Enable(0);
		if (IsLinkOk())
		{
			checkTimer.Enable(1);
		}
	}

	return 0;
}

int32 spt::DbgServer::PowerUpIni(int32 Para)
{
	MsgBuf.Alloc(1, 1024 * 5);
	appCfg = SptMain::Instance().AppCfg();

	if (appCfg)
	{
		E_HARDWARE hw = appCfg->platform.hardware;
		switch (hw)
		{
		case EH_GZKSAU:
		{
			break;
		}
		default:
			break;
		}

	}
	else
	{

	}

	Task::Start();
	DbgToolsServer::Instance().PowerUpIni(0);
	return 0;
}

int32 spt::DbgServer::OneLoop()
{
	uint8 step = taskStep;
	switch (step)
	{
	case E_PowerUpIni:
	{
		MsSleep(100);
		taskStep = E_WaitMsg;
		break;
	}
	case E_WaitMsg:
	{
		if (IsLinkOk())
		{
			uint8 buf[5] = { 0 };
			int res = Recv(buf, 1, 0);
			if (res > 0)
			{
				MsgBuf.Clear();
				if (buf[0] == 0x55)
				{
					MsgBuf.Write(&buf[0], 1);
					int res = Recv(buf, 1, 0);
					if (res > 0)
					{
						MsgBuf.Write(&buf[0], 1);
						if (buf[0] == 0xd5)
						{
							taskStep = E_RecFullMsg;
							msgTimer.Restart();
						}
					}
				}
			}
			else
			{
				MsSleep(10);
				taskStep = E_RecNoMsgDelay;
			}
		}
		else
		{
			MsSleep(100);
		}
		break;
	}
	case E_RecNoMsgDelay:
	{
		if (msgTimer.Status())
		{
			if (IsLinkOk())
			{
				Msg5K msg;
				msg.Set(E_MSG_Real_Stamp, 0, 0, 1);
				SalDateStamp stamp;
				stamp.Now();
				msg.Write(&stamp, sizeof(stamp));
				msg.AddSum();
				Send(&msg, msg.len, 0);
			}
			msgTimer.Restart();
		}
		else if (!msgTimer.IsEnable())
		{
			msgTimer.UpCnt(1000);
			msgTimer.Enable(1);
		}
		taskStep = E_WaitMsg;
		MsSleep(30);
		break;
	}
	case E_RecFullMsg:
	{
		uint8 buf[20];

		int res = Recv(buf, HeaderLen - 2, 0);
		if (res > 0)
		{
			MsgBuf.Write(&buf[0], res);

			if (MsgBuf.Top() < HeaderLen)
			{
			}
			else  if (MsgBuf.Top() >= HeaderLen)
			{
				MsgHeadr* header = (MsgHeadr*)(MsgBuf.BufBase());

				if ((header->len < MsgBuf.BufSize()) && (MsgBuf.Top() < MsgBuf.BufSize()))
				{
					uint8* ptr = (uint8*)(MsgBuf.BufBase());
					ptr += MsgBuf.Top();
					uint16 frmLen = header->len - MsgBuf.Top();
					int res = Recv(ptr, frmLen, 0);
					if (res > 0)
					{
						MsgBuf.WriterAdd(res);
					}
					if ((header->len == MsgBuf.Top()))
					{
						taskStep = E_UnpackMsg;
					}
					else if ((header->len > MsgBuf.BufSize()))
					{
						MsgBuf.Clear();
						LogErr.Stamp() << "DbgServer.E_PackMsg err1" << MsgBuf.Top() << "\n";
						taskStep = E_WaitMsg;
					}
				}
				else
				{
					MsgBuf.Clear();
					LogErr.Stamp() << "DbgServer.E_PackMsg err2" << MsgBuf.Top() << "\n";
					taskStep = E_WaitMsg;
				}
			}
		}
		if (msgTimer.Status())
		{
			msgTimer.Restart();
			taskStep = E_WaitMsg;
		}
		else if (!msgTimer.IsEnable())
		{
			msgTimer.UpCnt(500);
			msgTimer.Enable(1);
		}
		MsSleep(10);
		break;
	}
	case E_UnpackMsg:
	{
		UnpackMsg((Msg5K*)(MsgBuf.BufBase()));
		break;
	}
	default:
		taskStep = E_PowerUpIni;
		break;
	}

	return 0;
}

void spt::DbgServer::UnpackMsg(Msg5K* Msg)
{
	if (!Msg->IsSumOk())
	{
		recvPacketErr++;
		taskStep = E_WaitMsg;
		return;
	}
	recvPacket++;
	uint16 type = Msg->type1;
	switch (type)
	{
	case E_MSG_HELLO:
	{
		String100B str;
		if (appCfg)
		{
			str = appCfg->hmicfg.FullTypeName;
			str << "  " << appCfg->hmicfg.DispName;
			Msg5K msg;
			msg.Set(E_MSG_HELLO, 1, 0, 1);
			msg.Write(str.Str(), str.StrLen() + 1);
			msg.AddSum();
			Send(&msg, msg.len, 0);
		}
		taskStep = E_WaitMsg;
		break;
	}
	case E_MSG_Real_Stamp:
	{
		taskStep = E_WaitMsg;
		break;
	}
	case E_MSG_File_Trans:
	{
		taskStep = E_WaitMsg;
		break;
	}
	default:
		taskStep = E_WaitMsg;
		break;
	}
}

int32 spt::DbgServer::RecvMsg(Msg5K* Msg, int32 Ms)
{
	uint8 buf[5] = { 0 };

	while (Ms > 0)
	{
		int res = Recv(buf, 1, 0);
		if (res > 0)
		{
			if (buf[0] == 0x55)
			{
				int res = Recv(buf, 1, 0);
				if (res > 0)
				{
					if (buf[0] == 0xd5)
					{
						Msg->header = 0xd555;

						int res = Recv(&Msg->type1, HeaderLen - 2, 0);
						if (res == (HeaderLen - 2))
						{
							uint32 len = Msg->len;
							if (len > sizeof(Msg->data))
							{
								continue;
							}
							res = Recv(&Msg->data, len - HeaderLen, 0);
							if (Msg->IsSumOk())
							{
								return Msg->len;
							}
							else
							{
								return -1;
							}
						}
					}
				}
			}
		}
		else
		{
			MsSleep(1);
			Ms -= 1;
		}
	}
	return -1;
}

int32 spt::DbgServer::Send(const void* buf, int32 bufLen, uint32 flags)
{
	int32 res = DbgTcpGmServer::Send(buf, bufLen, flags);
	if (res > 0)
	{
		sendPacket++;
	}
	return res;
}

int32 spt::DbgServer::Send(Msg5K* Msg)
{
	Msg->AddSum();
	return Send(Msg, Msg->len, 0);
}

spt::DbgServer::DbgServer()
	:Task("tServer", 120, 1024 * 1024, E_T_FLOAT, E_AuxCore)
{
	sendPacket = recvPacket = recvPacketErr = 0;
}

int32 spt::DbgServer::Msg5K::GetDataLen()
{
	return len - sizeof(MsgHeadr) + 4;
}

void spt::DbgServer::Msg5K::AddSum()
{
	uint16 sum = 0;
	this->len += 2;
	uint16 len = this->len - sizeof(sum);
	uint8* sur = (uint8*)&(this->header);
	this->header = 0xd555;
	for (uint16 i = 0; i < len; i++)
	{
		sum += *sur++;
	}
	sur[0] = (uint8)sum;
	sur[1] = (uint8)(sum >> 8);
}

void spt::DbgServer::Msg5K::Set(uint16 Type1, uint16 Type2, uint16 Seri, uint16 Total)
{
	type1 = Type1;
	type2 = Type2;
	series = Seri;
	total = Total;
	len = HeaderLen;
}

uint16 spt::DbgServer::Msg5K::Write(const void* Sur, uint16 Len)
{
	uint8* dst = (uint8*)(&this->header);

	if (len < sizeof(data))
	{
		dst += len;
		uint16 l = len + Len;

		if (l < sizeof(data))
		{
			MemCpy(dst, Sur, Len);
			len = l;
		}
	}
	else
	{
		len = 0;
	}

	return len;
}

bool8 spt::DbgServer::Msg5K::IsSumOk()
{
	uint16 sum = 0;
	uint16 le = this->len - sizeof(sum);
	uint8* sur = (uint8*)&(this->header);
	this->header = 0xd555;
	for (uint16 i = 0; i < le; i++)
	{
		sum += *sur++;
	}
	uint16 fsum;
	fsum = sur[0] + ((uint16)sur[1] << 8);
	if (sum == fsum)
	{
		return 1;
	}
	return 0;
}

void spt::DbgServer::MsgCtrl::SetMsg5KBuf(Msg5K* Buf)
{
	buf = Buf;
	reader = 0;
	msgLen = buf->len - HeaderLen;
}

uint16 spt::DbgServer::MsgCtrl::Read(void* Dst, uint16 Len)
{
	uint8* dst = (uint8*)Dst;
	uint16 l = 0;
	while ((reader < msgLen) && (l < Len))
	{
		*dst++ = buf->data[reader++];
		l++;
	}
	return l;
}
