#include "InstResource.h"

bool8 CheckDeviceIdFunc(DbgToolsServer::E_MsgType MsgType, const char* Ip, const char* UsrInputDeviceId)
{
	return 1;
}
bool8 UserLogOnFunc(DbgToolsServer::E_MsgType MsgType, const char* Ip, const char* Usr, const char* PassWord)
{
	return 1;
}
bool8 UserLinkCloseFunc(DbgToolsServer::E_MsgType MsgType, const char* Ip)
{
	return 1;
}

void AppDbgPowerUpIni()
{
	DbgToolsServer::Instance().SetCheckDeviceIdFunc(CheckDeviceIdFunc);
	DbgToolsServer::Instance().SetUserLogOnFunc(UserLogOnFunc);
	DbgToolsServer::Instance().SetUserLinkCloseFunc(UserLinkCloseFunc);
}
