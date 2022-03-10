#include "InstResource.h"
//校验唯一性ID
//0表示成功
int32 CheckDeviceIdFunc(DbgToolsServer::E_MsgType MsgType, const char* Ip, const char* UsrInputDeviceId)
{
	return 0;
}
//校验帐号密码
//0表示成功
int32 UserLogOnFunc(DbgToolsServer::E_MsgType MsgType, const char* Ip, const char* Usr, const char* PassWord)
{
	return 0;
}
//客户端连接关闭信息
int32 UserLinkCloseFunc(DbgToolsServer::E_MsgType MsgType, const char* Ip)
{
	return 0;
}
//客户端连接信息
//StatusType 0表示连接成功
int32 UserLinkFunc(DbgToolsServer::E_MsgType MsgType, const char* Ip, int32 StatusType)
{
	return 0;
}
void AppDbgPowerUpIni()
{
	DbgToolsServer::Instance().SetCheckDeviceIdFunc(CheckDeviceIdFunc);
	DbgToolsServer::Instance().SetUserLogOnFunc(UserLogOnFunc);
	DbgToolsServer::Instance().SetUserLinkCloseFunc(UserLinkCloseFunc);
	DbgToolsServer::Instance().SetUserLinkFunc(UserLinkFunc);
}
