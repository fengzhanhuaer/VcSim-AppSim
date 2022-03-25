#ifndef DBGDBGTOOLS_H
#define DBGDBGTOOLS_H
namespace spt
{
	class DbgTools :public Task
	{
	public:
		int32 StartServer(uint32 LocalIp, uint16 LocalPort, uint32 RemoteIp, uint16 RemotePort, int32 ClientSock);
		M_Singleton(DbgTools);
	protected:
		DbgTools();
	protected:
		DbgTcpGmServer gmSock;
	};
}
#endif // !DBGDBGTOOLS_H