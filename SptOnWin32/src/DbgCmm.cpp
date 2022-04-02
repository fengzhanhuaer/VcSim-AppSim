#include "SptProject.h"
#include "DbgCmm.h"
using namespace spt;

int32 spt::DbgSocket::SetLocalIp(const char* Ip)
{
	localIp.u32 = InetAddr(Ip);
	return 0;
}

int32 spt::DbgSocket::SetLocalIp(uint32 Ip)
{
	localIp.u32 = Ip;
	return 0;
}

int32 spt::DbgSocket::SetRemoteIp(const char* Ip)
{
	remoteIp.u32 = InetAddr(Ip);
	return 0;
}

int32 spt::DbgSocket::SetRemoteIp(uint32 Ip)
{
	remoteIp.u32 = Ip;
	return 0;
}

int32 spt::DbgSocket::SetLocalPort(uint16 Port)
{
	localPort.u16 = Port;
	return 0;
}

int32 spt::DbgSocket::SetRemotePort(uint16 Port)
{
	remotePort.u16 = Port;
	return 0;
}

bool8 spt::DbgSocket::GetRemote(SalString& Str)
{
	return GetIpStr(remoteIp.u32, Str);
}

bool8 spt::DbgSocket::GetIpStr(uint32 Ip, SalString& Str)
{
	u4bytes u4;
	u4.u32 = Ip;
	Str << (uint8)u4.u8[0] << ".";
	Str << (uint8)u4.u8[1] << ".";
	Str << (uint8)u4.u8[2] << ".";
	Str << (uint8)u4.u8[3];
	return 0;
}

int32 spt::DbgSocket::Send(const void* buf, int32 bufLen, uint32 flags)
{
	if (sock <= 0)
	{
		return 0;
	}
	return spt::Send(sock, buf, bufLen, flags);
}

int32 spt::DbgSocket::Send(DbgMsg& Msg)
{
	Msg.header.header = 0xd555;
	Msg.header.sur = localIp.u2b[1].u16;
	Msg.header.dst = remoteIp.u2b[1].u16;
	return Send(&Msg, Msg.header.len + sizeof(DbgMsg::checkCode), 0);
}

int32 spt::DbgSocket::SendTo(const void* buf, int32 bufLen, uint32 flags, uint32 Ip, uint16 Port)
{
	if (sock <= 0)
	{
		return 0;
	}
	return spt::SendTo(sock, buf, bufLen, flags, Ip, Port);
}

int32 spt::DbgSocket::SendTo(const void* buf, int32 bufLen, uint32 flags)
{
	return spt::SendTo(sock, buf, bufLen, flags, remoteIp.u32, remotePort.u16);
}

int32 spt::DbgSocket::Recv(void* buf, int32 bufLen, uint32 flags)
{
	if (sock <= 0)
	{
		return 0;
	}
	return spt::Recv(sock, buf, bufLen, flags);
}

int32 spt::DbgSocket::Recv(DbgMsg& Msg)
{
	SalCmmMsgHeader header;
	int cnt = 0;
	while (Recv(&header, sizeof(header), 0) == sizeof(header))
	{
		if (header.header == 0xd555)
		{
			MemCpy(&Msg, &header, sizeof(header));
			int len = Msg.header.len - sizeof(header) + sizeof(DbgMsg::checkCode);
			if (Recv(&Msg.data, len, 0) == len)
			{
				return  Msg.header.len;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			cnt++;
			if (cnt > 10)
			{
				return -1;
			}
		}
	}
	return 0;
}

int32 spt::DbgSocket::RecvFrom(void* buf, int32 bufLen, uint32 flags, uint32& Ip, uint16& Port)
{
	if (sock <= 0)
	{
		return 0;
	}
	return spt::RecvFrom(sock, buf, bufLen, flags, Ip, Port);
}

int32 spt::DbgSocket::RecvFrom(void* buf, int32 bufLen, uint32 flags)
{
	return spt::RecvFrom(sock, buf, bufLen, flags, remoteIp.u32, remotePort.u16);
}

int32 spt::DbgSocket::SetSocketNonBlock(bool8 block)
{
	return spt::SetSocketNonBlock(sock, block);
}

int32 spt::DbgSocket::SetSocketRecvTimeOut(int32 Sec, int32 uSec)
{
	return spt::SetSocketRecvTimeOut(sock, Sec, uSec);
}

int32 spt::DbgSocket::Bind()
{
	return spt::Bind(sock, localIp.u32, localPort.u16);
}

int32 spt::DbgSocket::Connect()
{
	return spt::Connect(sock, remoteIp.u32, remotePort.u16);
}

void spt::DbgSocket::Close()
{
	if (sock > 0)
	{
		CloseSocket(sock);
		sock = 0;
	}
}

spt::DbgSocket::DbgSocket()
{
	sock = -1;
	remoteIp.u32 = 0;
	remotePort.u16 = 0;
	localIp.u32 = 0;
	localPort.u16 = 0;
}
spt::DbgSocket::~DbgSocket()
{
	if (sock >= 0)
	{
		Close();
	}
}

int32 spt::DbgUdpServer::Start()
{
	if (CreatSocket() == -1)
	{
		return -1;
	}
	if (Bind() == -1)
	{
		LogWarn.Stamp() << "Socket Bind Failed." << GetSocketLastError() << "\n";
		return -1;
	}

	return 0;
}

int32 spt::DbgUdpServer::StartNonBlock()
{
	if (CreatSocket() == -1)
	{
		return -1;
	}
	if (SetSocketNonBlock(1) < 0)
	{
		LogWarn.Stamp() << "Socket SetSocketNonBlock Failed." << GetSocketLastError() << "\n";
		return -1;
	}
	if (Bind() == -1)
	{
		LogWarn.Stamp() << "Socket Bind Failed." << GetSocketLastError() << "\n";
		return -1;
	}

	return 0;
}

int32 spt::DbgUdpCmm::CreatSocket()
{
	if (sock > 0)
	{
		Close();
	}
	sock = Socket(E_SC_INET, E_SC_DGRAM, 0);
	if (sock < 0)
	{
		LogWarn.Stamp() << "Creat socket Failed." << GetSocketLastError() << "\n";
		return -1;
	}
	return sock;
}

int32 spt::DbgUdpClient::Start()
{
	if (CreatSocket() == -1)
	{
		return -1;
	}
	if (Bind() == -1)
	{
		LogWarn.Stamp() << "Socket Bind Failed." << GetSocketLastError() << "\n";
		return -1;
	}
	if (Connect() == -1)
	{
		LogWarn.Stamp() << "Socket Connect Failed." << GetSocketLastError() << "\n";
		return -1;
	}

	return 0;
}

int32 spt::DbgUdpClient::StartNonBlock()
{
	if (CreatSocket() == -1)
	{
		return -1;
	}
	if (Bind() == -1)
	{
		LogWarn.Stamp() << "Socket Bind Failed." << GetSocketLastError() << "\n";
		return -1;
	}
	if (SetSocketNonBlock(1) < 0)
	{
		LogWarn.Stamp() << "Socket SetSocketNonBlock Failed." << GetSocketLastError() << "\n";
		return -1;
	}
	if (Connect() == -1)
	{
		LogWarn.Stamp() << "Socket Connect Failed." << GetSocketLastError() << "\n";
		return -1;
	}
	return 0;
}

int32 spt::DbgTcpServer::Start()
{
	if (CreatSocket() == -1)
	{
		return -1;
	}
	if (Bind() == -1)
	{
		LogWarn.Stamp() << "Socket Bind Failed." << GetSocketLastError() << "\n";
		return -1;
	}
	int res = Listen(sock, 1);
	if (res < 0)
	{
		LogWarn.Stamp() << "Socket Listen Failed." << GetSocketLastError() << "\n";
		return -1;
	}
	return 0;
}

int32 spt::DbgTcpServer::StartNonBlock()
{
	if (CreatSocket() == -1)
	{
		return -1;
	}
	if (Bind() == -1)
	{
		LogWarn.Stamp() << "Socket Bind Failed." << GetSocketLastError() << "\n";
		return -1;
	}
	if (SetSocketNonBlock(1) < 0)
	{
		LogWarn.Stamp() << "Socket SetSocketNonBlock Failed." << GetSocketLastError() << "\n";
		return -1;
	}
	int res = Listen(sock, 1);
	if (res < 0)
	{
		LogWarn.Stamp() << "Socket Listen Failed." << GetSocketLastError() << "\n";
		return -1;
	}
	return 0;
}

void spt::DbgTcpServer::CloseListener()
{
	if (sock > 0)
	{
		CloseSocket(sock);
		sock = -1;
	}
}

void spt::DbgTcpServer::CloseClient()
{
	if (clientsock > 0)
	{
		CloseSocket(clientsock);
		clientsock = -1;
	}
}

bool8 spt::DbgTcpServer::IsReadAble()
{
	if (sock > 0)
	{
		return SelectSocketR(sock, 0, 0);
	}
	return 0;
}

spt::DbgTcpCmm::DbgTcpCmm()
{
	clientsock = -1;
}

int32 spt::DbgTcpCmm::SetClientSocketNonBlock(bool8 block)
{
	return spt::SetSocketNonBlock(clientsock, block);
}

int32 spt::DbgTcpCmm::Send(const void* buf, int32 bufLen, uint32 flags)
{
	if (clientsock <= 0)
	{
		return 0;
	}
	return spt::Send(clientsock, buf, bufLen, flags);
}
int32 spt::DbgTcpCmm::Recv(void* buf, int32 bufLen, uint32 flags)
{
	if (clientsock <= 0)
	{
		return 0;
	}
	return spt::Recv(clientsock, buf, bufLen, flags);
}

int32 spt::DbgTcpCmm::Send(DbgMsg& Msg)
{
	return DbgSocket::Send(Msg);
}

int32 spt::DbgTcpCmm::Recv(DbgMsg& Msg)
{
	return DbgSocket::Recv(Msg);
}

int32 spt::DbgTcpCmm::CreatSocket()
{
	if (sock > 0)
	{
		Close();
	}
	sock = Socket(E_SC_INET, E_SC_STREAM, 0);
	if (sock < 0)
	{
		LogWarn.Stamp() << "Creat socket Failed." << GetSocketLastError() << "\n";
		return -1;
	}
	return 0;
}

int32 spt::DbgTcpCmm::Accept()
{
	return  clientsock = spt::Accept(sock, remoteIp.u32, remotePort.u16);
}

bool8 spt::DbgTcpCmm::IsClientOk()
{
	return clientsock > 0;
}

void spt::DbgTcpCmm::Close()
{
	if (clientsock > 0)
	{
		CloseSocket(clientsock);
		clientsock = -1;
	}
	DbgSocket::Close();
}

int32 spt::DbgTcpCmm::SetClientSock(int32 sock)
{
	return clientsock = sock;
}

int32 spt::DbgTcpClient::Start()
{
	if (CreatSocket() == -1)
	{
		return -1;
	}

	if (Bind() == -1)
	{
		LogWarn.Stamp() << "Socket Bind Failed." << GetSocketLastError() << "\n";
		return -1;
	}
	MsTimer timer;
	timer.UpCnt(5000);
	timer.Enable(1);
	timer.Restart();
	while (!timer.Status())
	{
		MsSleep(20);
		if (Connect() <= -1)
		{
			LogWarn.Stamp() << "Socket Connect Failed." << GetSocketLastError() << "\n";
		}
		else
		{
			break;
		}
	}
	clientsock = sock;
	int32 res = SelectSocketRW(sock, 5, 0);
	if (res <= 0)
	{
		clientsock = -1;
		Close();
		return -1;
	}
	return 0;
}

int32 spt::DbgTcpClient::StartNonBlock()
{
	if (CreatSocket() == -1)
	{
		return -1;
	}
	if (SetSocketNonBlock(1) < 0)
	{
		LogWarn.Stamp() << "Socket SetSocketNonBlock Failed." << GetSocketLastError() << "\n";
		return -1;
	}
	if (Bind() == -1)
	{
		LogWarn.Stamp() << "Socket Bind Failed." << GetSocketLastError() << "\n";
		return -1;
	}
	Connect();
	int32 res = SelectSocketRW(sock, 5, 0);
	if (res <= 0)
	{
		clientsock = -1;
		Close();
		return -1;
	}
	clientsock = sock;
	return 0;
}

bool8 spt::DbgTcpClient::IsReadAble()
{
	if (clientsock > 0)
	{
		return SelectSocketR(clientsock, 0, 0);
	}
	return 0;
}

void spt::DbgTcpGmCmm::SetLinkOk(bool8 Ok)
{
	gmlinkOk = Ok;
}

bool8 spt::DbgTcpGmCmm::EnableGmssl(bool8 Enable)
{
	return enableGmssl = Enable;
}

bool8 spt::DbgTcpGmServer::IsLinkOk()
{
	if (!enableGmssl)
	{
		return IsClientOk();
	}
	if (!(gmSock && gmlinkOk))
	{
		return 0;
	}
	return 1;
}

int32 spt::DbgTcpGmServer::Send(const void* buf, int32 bufLen, uint32 flags)
{
	if (!enableGmssl)
	{
		return DbgTcpCmm::Send(buf, bufLen, flags);
	}
	if (!(gmSock && gmlinkOk))
	{
		return 0;
	}
	return DbgGmSslWrite(gmSock, buf, bufLen);
}

int32 spt::DbgTcpGmServer::Recv(void* buf, int32 bufLen, uint32 flags)
{
	if (!enableGmssl)
	{
		return DbgTcpCmm::Recv(buf, bufLen, flags);
	}
	if (!(gmSock && gmlinkOk))
	{
		return 0;
	}
	return DbgGmSslRead(gmSock, buf, bufLen);
}

void spt::DbgTcpGmServer::Close()
{
	if (gmSock)
	{
		DbgGmSslClose(gmSock);
		gmSock = 0;
	}
	SetLinkOk(0);
	DbgTcpServer::Close();
}

int32 spt::DbgTcpGmServer::GmAccept()
{
	if (!enableGmssl)
	{
		return -1;
	}
	return DbgGmSslAccept(gmSock);
}

int32 spt::DbgTcpGmServer::StartNonBlock()
{
	SetLinkOk(0);
	return DbgTcpServer::StartNonBlock();
}

int32 spt::DbgTcpGmServer::Start()
{
	SetLinkOk(0);
	return DbgTcpServer::Start();
}

void spt::DbgTcpGmServer::CreatGmSock()
{
	SetLinkOk(0);
	if (gmSock)
	{
		DbgGmSslClose(gmSock);
		gmSock = 0;
	}
	if (!enableGmssl)
	{
		return;
	}
	gmSock = DbgGmSslSockServerNew((void*)clientsock);
}

bool8 spt::DbgTcpGmClient::IsLinkOk()
{
	if (!enableGmssl)
	{
		return IsClientOk();
	}
	if (!(gmSock && gmlinkOk))
	{
		return 0;
	}
	return 1;
}

int32 spt::DbgTcpGmClient::Send(const void* buf, int32 bufLen, uint32 flags)
{
	if (!enableGmssl)
	{
		return DbgTcpCmm::Send(buf, bufLen, flags);
	}
	if (!(gmSock && gmlinkOk))
	{
		return 0;
	}
	return DbgGmSslWrite(gmSock, buf, bufLen);
}

int32 spt::DbgTcpGmClient::Recv(void* buf, int32 bufLen, uint32 flags)
{
	if (!enableGmssl)
	{
		return DbgTcpCmm::Recv(buf, bufLen, flags);
	}
	if (!(gmSock && gmlinkOk))
	{
		return 0;
	}
#ifdef WIN32_SIM

	return DbgGmSslRead(gmSock, buf, bufLen);

#else 
	return DbgGmSslRead(gmSock, buf, bufLen);
#endif
	return 0;
}

void spt::DbgTcpGmClient::Close()
{
	if (gmSock)
	{
		DbgGmSslClose(gmSock);
		gmSock = 0;
	}
	DbgTcpClient::Close();
	SetLinkOk(0);
}

void spt::DbgTcpGmClient::CreatGmSock()
{
	SetLinkOk(0);
	if (gmSock)
	{
		DbgGmSslClose(gmSock);
		gmSock = 0;
	}
	if (!enableGmssl)
	{
		return;
	}
	gmSock = DbgGmSslSockClientNew((void*)clientsock);
}

int32 spt::DbgTcpGmClient::StartNonBlock()
{
	SetLinkOk(0);
	if (DbgTcpClient::StartNonBlock() == -1)
	{
		return -1;
	}
	MsTimer timer;
	if (!enableGmssl)
	{
		SetLinkOk(1);
		return 0;
	}
	//TCP连接已经建立，将连接付给SSL
	gmSock = DbgGmSslSockClientNew((void*)sock);
	timer.UpCnt(5000);
	timer.Enable(1);
	timer.Restart();
	while (!timer.Status())
	{
		MsSleep(20);
		if (GmConnect() <= -1)
		{
		}
		else
		{
			break;
		}
	}
	SetLinkOk(1);
	return 0;
}
int32 spt::DbgTcpGmClient::GmConnect()
{
	if (!enableGmssl)
	{
		return -1;
	}
	return DbgGmSslConnect(gmSock);
}
spt::DbgTcpGmClient::DbgTcpGmClient()
{
	gmSock = 0;
	gmlinkOk = 0;

}

spt::UdpCmmTest::UdpCmmTest()
	:Task("tDbgMain", 90, 512 * 1024, E_T_FLOAT, E_AuxCore)
{
	period = 1000;
	SetRemoteIp("255.255.255.255");
	SetRemotePort(31001);
}

int32 spt::UdpCmmTest::PowerUpIni(int32 Para)
{
	Task::PowerUpIni(0);
	Task::Start();
	return 0;
}

int32 spt::UdpCmmTest::OneLoop()
{
	switch (taskStep)
	{
	case E_PowerUpIni:
	{
		msTimer.UpCnt(period);
		msTimer.Enable(1);
		SetLocalIp("0.0.0.0");
		SetLocalPort(31000);
		if (DbgUdpServer::StartNonBlock() == 0)
		{
			taskStep = E_WaitSendMsg;
		}
		lastRemoteSer = 0;
		lastRemoteSerDif = 0;
		break;
	}
	case E_WaitSendMsg:
	{
		if (msTimer.Status())
		{
			TestMsg msg;
			MemSet(&msg, 0, sizeof(msg));
			msg.msg.ser = series;
			msg.msg.remoteser = lastRemoteSer;
			msg.msg.remotedif = lastRemoteSerDif;
			msg.msg.remoteserlast = lastRemoteSerLast;
			msg.msg.period = period;
			series++;
			SendTo(&msg, sizeof(msg), 0);
			msTimer.Restart();
		}
		else
		{
			MsSleep(1);
		}
		taskStep = E_WaitRecvMsg;
		break;
	}
	case E_WaitRecvMsg:
	{
		TestMsg msg = { 0 };
		int res = RecvFrom(&msg, sizeof(msg), 0);
		if (res == sizeof(msg))
		{
			uint32 remotes = msg.msg.ser;
			lastRemoteSerDif = remotes - lastRemoteSer;
			lastRemoteSerLast = lastRemoteSer;
			lastRemoteSer = remotes;
			if (period != msg.msg.period)
			{
				period = msg.msg.period;
				if (!period)
				{
					period = 10;
				}
				else
				{
					taskStep = E_PowerUpIni;
					break;
				}
			}
		}
		else
		{
			MsSleep(1);
		}
		taskStep = E_WaitSendMsg;
	};
	default:
		break;
	}
	return 0;
}
