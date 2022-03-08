#include "InstResource.h"

int32 CheckDeviceIdFunc(DbgToolsServer::E_MsgType MsgType, const char* Ip, const char* UsrInputDeviceId)
{
	return 0;
}
int32 UserLogOnFunc(DbgToolsServer::E_MsgType MsgType, const char* Ip, const char* Usr, const char* PassWord)
{
	return 0;
}
int32 UserLinkCloseFunc(DbgToolsServer::E_MsgType MsgType, const char* Ip)
{
	return 0;
}

void AppDbgPowerUpIni()
{
	DbgToolsServer::Instance().SetCheckDeviceIdFunc(CheckDeviceIdFunc);
	DbgToolsServer::Instance().SetUserLogOnFunc(UserLogOnFunc);
	DbgToolsServer::Instance().SetUserLinkCloseFunc(UserLinkCloseFunc);
}
