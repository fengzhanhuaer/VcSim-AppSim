#include "InstResource.h"
//У��Ψһ��ID
//0��ʾ�ɹ�
int32 CheckDeviceIdFunc(DbgToolsServer::E_MsgType MsgType, const char* Ip, const char* UsrInputDeviceId)
{
	return 0;
}
//У���ʺ�����
//0��ʾ�ɹ�
int32 UserLogOnFunc(DbgToolsServer::E_MsgType MsgType, const char* Ip, const char* Usr, const char* PassWord)
{
	return 0;
}
//�ͻ������ӹر���Ϣ
int32 UserLinkCloseFunc(DbgToolsServer::E_MsgType MsgType, const char* Ip)
{
	return 0;
}
//�ͻ���������Ϣ
//StatusType 0��ʾ���ӳɹ�
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
