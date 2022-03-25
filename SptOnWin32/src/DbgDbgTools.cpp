#include"ApiProject.h"
using namespace spt;
int32 spt::DbgTools::StartServer(uint32 LocalIp, uint16 LocalPort, uint32 RemoteIp, uint16 RemotePort, int32 ClientSock)
{
	return int32();
}

spt::DbgTools::DbgTools()
	:Task("tDbgTools", TaskBasePriority + 30, 2048 * 1024, E_T_FLOAT, E_AuxCore)
{

}
