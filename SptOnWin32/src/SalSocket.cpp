#include "SptProject.h"
using namespace spt;

#ifdef WIN32_SIM
#include<winsock2.h>
#pragma  comment (lib, "ws2_32.lib")
#elif defined(SYLIX_GZK)
#include<sys/socket.h>
#endif


uint32 spt::HtoNl(uint32 x)
{
	return htonl(x);
}

uint16 spt::HtoNs(uint16 x)
{
	return htons(x);
}

uint32 spt::NtoHl(uint32 x)
{
	return ntohl(x);
}

uint16 spt::NtoHs(uint16 x)
{
	return ntohs(x);
}

uint32 spt::InetAddr(const char* name)
{
	return inet_addr(name);
}

int32 spt::Socket(int32 domain, int32 type, int32 protocol)
{
	return socket(domain, type, protocol);
}

int32 spt::Bind(int32 socket, uint32 Ip, uint16 Port)
{
	sockaddr_in  address;
#ifdef WIN32_SIM
	address.sin_port = HtoNs(Port);
	address.sin_family = E_SC_INET;
	address.sin_addr.S_un.S_addr = Ip;
#elif defined(SYLIX_GZK)
	address.sin_len = sizeof(address);
	address.sin_port = HtoNs(Port);
	address.sin_family = E_SC_INET;
	address.sin_addr.s_addr = Ip;
#endif
	return bind(socket, (const struct sockaddr*)&address, sizeof(address));
}

int32 spt::Connect(int32 socket, uint32 Ip, uint16 Port)
{
	sockaddr_in  address;
#ifdef WIN32_SIM
	address.sin_port = HtoNs(Port);
	address.sin_family = E_SC_INET;
	address.sin_addr.S_un.S_addr = Ip;
#elif defined(SYLIX_GZK)
	address.sin_len = sizeof(address);
	address.sin_port = HtoNs(Port);
	address.sin_family = E_SC_INET;
	address.sin_addr.s_addr = Ip;
#endif
	return connect(socket, (const struct sockaddr*)&address, sizeof(address));
}

int32 spt::SelectSocketR(int32 socket, uint32 Sec, uint32 Ms)
{
	fd_set rsets;
	timeval val;
	val.tv_sec = Sec;
	val.tv_usec = Ms * 1000;
	FD_ZERO(&rsets);
	FD_SET(socket, &rsets);
	int32 res = select(socket + 1, &rsets, 0, 0, &val);
	if (res > 0)
	{
		return FD_ISSET(socket, &rsets);
	}
	return -1;
}
int32 spt::SelectSocketW(int32 socket, uint32 Sec, uint32 Ms)
{
	fd_set rsets;
	timeval val;
	val.tv_sec = Sec;
	val.tv_usec = Ms * 1000;
	FD_ZERO(&rsets);
	FD_SET(socket, &rsets);
	int32 res = select(socket + 1, 0, &rsets, 0, &val);
	if (res > 0)
	{
		return FD_ISSET(socket, &rsets);
	}
	return -1;
}

int32 spt::SelectSocketRW(int32 socket, uint32 Sec, uint32 Ms)
{
	fd_set rsets, wsets;
	timeval val;
	val.tv_sec = Sec;
	val.tv_usec = Ms * 1000;
	FD_ZERO(&rsets);
	FD_SET(socket, &rsets);
	FD_ZERO(&wsets);
	FD_SET(socket, &wsets);
	int32 res = select(socket + 1, &wsets, &rsets, 0, &val);
	if (res > 0)
	{
		return FD_ISSET(socket, &rsets) || FD_ISSET(socket, &wsets);
	}
	return -1;
}

int32 spt::Send(int32 socket, const void* buf, int32 len, uint32 flags)
{
	return send(socket, (const char*)buf, len, flags);
}

int32 spt::SendTo(int32 socket, const void* buf, int32 len, uint32 flags, uint32 Ip, uint16 Port)
{
	sockaddr_in  address;
#ifdef WIN32_SIM
	address.sin_port = HtoNs(Port);
	address.sin_family = E_SC_INET;
	address.sin_addr.S_un.S_addr = Ip;
#elif defined(SYLIX_GZK)
	address.sin_len = sizeof(address);
	address.sin_port = HtoNs(Port);
	address.sin_family = E_SC_INET;
	address.sin_addr.s_addr = Ip;
#endif
	int32 addrlen = sizeof(address);
	return sendto(socket, (const char*)buf, len, flags, (struct sockaddr*)&address, addrlen);
}

int32 spt::Recv(int32 socket, void* buf, int32 len, uint32 flags)
{
	return recv(socket, (char*)buf, len, flags);
}

int32 spt::RecvFrom(int32 socket, void* buf, int32 len, uint32 flags, uint32& Ip, uint16& Port)
{
	sockaddr_in  address;
#ifdef WIN32_SIM

	int32 addrlen = sizeof(address);
	int32 res = recvfrom(socket, (char*)buf, len, flags, (struct sockaddr*)&address, &addrlen);
	if (res > 0)
	{
		Ip = address.sin_addr.S_un.S_addr;
		Port = NtoHs(address.sin_port);
	}
#elif defined(SYLIX_GZK)
	uint32 addrlen = sizeof(address);
	int res = recvfrom(socket, (char*)buf, len, flags, (struct sockaddr*)&address, &addrlen);
	if (res > 0)
	{
		Ip = address.sin_addr.s_addr;
		Port = NtoHs(address.sin_port);
	}
#endif

	return res;
}

int32 spt::Listen(int32 socket, int32 BackLog)
{
	return listen(socket, BackLog);
}

int32 spt::Accept(int32 socket, uint32& Ip, uint16& Port)
{
	sockaddr_in  address;
#ifdef WIN32_SIM
	int32 addrlen = sizeof(address);
	int res = accept(socket, (struct sockaddr*)&address, &addrlen);
	if (res > 0)
	{
		Ip = address.sin_addr.S_un.S_addr;
		Port = NtoHs(address.sin_port);
	}
#elif defined(SYLIX_GZK)
	uint32 addrlen = sizeof(address);
	int res = accept(socket, (struct sockaddr*)&address, &addrlen);
	if (res > 0)
	{
		Ip = address.sin_addr.s_addr;
		Port = NtoHs(address.sin_port);
	}
#endif
	return res;
}

int32 spt::CloseSocket(int32 socket)
{
#ifdef WIN32_SIM
	return closesocket(socket);
#else 
	return close(socket);
#endif // WIN32_SIM

}

int32 spt::GetSocketLastError()
{
#ifdef WIN32_SIM
	return WSAGetLastError();
#else
	return 0;
#endif

}

int32 spt::SetSocketNonBlock(int32 socket, bool8 block)
{
#ifdef WIN32_SIM
	u_long para = block;
	return ioctlsocket(socket, FIONBIO, &para);
#elif  defined(SYLIX_GZK)
	if (block)
	{
		int flags = fcntl(socket, F_GETFL, 0);
		return fcntl(socket, F_SETFL, flags | O_NONBLOCK);
	}
	else
	{
		int flags = fcntl(socket, F_GETFL, 0);
		flags &= (~O_NONBLOCK);
		return fcntl(socket, F_SETFL, flags);
	}
#endif
}

int32 spt::SetSocketRecvTimeOut(int32 socket, int32 Sec, int32 uSec)
{
	struct timeval timeout;
	timeout.tv_sec = Sec;//√Î
	timeout.tv_usec = uSec;//Œ¢√Î
	return setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
}

void spt::SocketEnvStartUp()
{
#ifdef WIN32_SIM
	WSADATA wsa_data;
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
	{
		LogErr.Stamp() << "WSAStartup() error!.\n";
	}
#endif // !WIN32_SIM
}

void spt::SocketEnvClearUp()
{
#ifdef WIN32_SIM
	WSACleanup();
#endif // !WIN32_SIM
}


