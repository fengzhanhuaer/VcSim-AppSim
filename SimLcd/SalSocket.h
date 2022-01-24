#ifndef SALSOCKET_H
#define SALSOCKET_H

namespace spt
{
	uint32 HtoNl(uint32 x);
	uint16 HtoNs(uint16 x);
	uint32 NtoHl(uint32 x);
	uint16 NtoHs(uint16 x);
	uint32 InetAddr(const char* name);
	int32 Socket(int32 domain, int32 type, int32 protocol);
	int32 Bind(int32 socket, uint32 Ip, uint16 Port);
	int32 Connect(int32 socket, uint32 Ip, uint16 Port);
	int32 SelectSocketR(int32 socket, uint32 Sec, uint32 Ms);
	int32 SelectSocketW(int32 socket, uint32 Sec, uint32 Ms);
	int32 SelectSocketRW(int32 socket, uint32 Sec, uint32 Ms);
	int32 Send(int32 socket, const void* buf, int32 len, uint32 flags);
	int32 SendTo(int32 socket, const void* buf, int32 len, uint32 flags, uint32 Ip, uint16 Port);
	int32 Recv(int32 socket, void* buf, int32 len, uint32 flags);
	int32 RecvFrom(int32 socket, void* buf, int32 len, uint32 flags, uint32& Ip, uint16& Port);
	int32 Listen(int32 socket, int32 BackLog);
	int32 Accept(int32 socket, uint32& Ip, uint16& Port);
	int32 CloseSocket(int32 socket);
	int32 GetSocketLastError();
	int32 SetSocketNonBlock(int32 socket, bool8 block);
	int32 SetSocketRecvTimeOut(int32 socket, int32 Sec, int32 uSec);
	typedef enum
	{
		E_SC_UNSPEC = 0,
		E_SC_INET = 2,
	}E_SC_FAMILY;
	typedef enum
	{
		E_SC_STREAM = 1,
		E_SC_DGRAM = 2,
		E_SC_RAW = 3,
		E_SC_SEQPACKET = 5,
	}E_SC_TYPE;
	typedef enum
	{
		E_SC_IP = 0,
		E_SC_TCP = 6,
		E_SC_UDP = 17,
	}E_PT_TYPE;

	void SocketEnvStartUp();
	void SocketEnvClearUp();

}

#endif // !SALSOCKET_H

