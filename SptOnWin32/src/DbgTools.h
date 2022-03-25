#ifndef DBGTOOLS_H
#define DBGTOOLS_H

#include"DbgCmm.h"

namespace spt
{
	class DbgSimCfg :public CfgFile
	{
	public:
		int32 PowerUpIni(int32 Para);
		static DbgSimCfg& Instance();
	protected:
		virtual PCfgDataBase* CfgPool() { return pool; };
		virtual uint32 CfgPoolSize() { return M_ArrLen(pool); };
	public:
		CfgBool EnableDbgServer;
		CfgBool EnableSimLcd;
		CfgBool EnableIedTools;
		CfgBool EnableDbgTools;
		CfgBool NeedCheckDeviceId;
		CfgBool NeedUsrLog;
		CfgStr ServerIp;
		CfgBool EnableGmssl;
		CfgUint32 GmsslVerifyMode;
		CfgStr GmsslLinkMode;
		CfgUint32 GmsslCrtFormat;
		CfgBool EnableGmCrtCheck;
	private:
		PCfgDataBase pool[20];
	};
	class DbgClientCfg :public CfgFile
	{
	public:
		int32 PowerUpIni(int32 Para);
	protected:
		virtual PCfgDataBase* CfgPool() { return pool; };
		virtual uint32 CfgPoolSize() { return M_ArrLen(pool); };
	public:
		CfgStr ServerIp;
		CfgStr ClientIp;
		CfgUint32 ClientPort;
		CfgBool EnableGmssl;
		CfgUint32 GmsslVerifyMode;
		CfgStr GmsslLinkMode;
		CfgUint32 GmsslCrtFormat;
		CfgBool EnableGmCrtCheck;
	private:
		PCfgDataBase pool[200];
	};
	class DbgToolsServer :public Task
	{

	public:
		struct HandshakeMsg
		{
			uint8 msg[256];
		};
	public:
		enum E_MsgType
		{
			E_HeartBeat,
			E_ServiceAsk,
			E_VirLcd,
			E_IedTools,
			E_DbgTools,
		};
	public:
		/// <summary>
		/// 0��ʾ�ɹ�
		/// </summary>
		typedef int32(*CheckDeviceIdFunc)(E_MsgType MsgType, const char* Ip, const char* UsrInputDeviceId);
		/// <summary>
		/// 0��ʾ�ɹ�
		/// -2��ʾ�ʺ�����
		/// -3��ʾ�ʺŻ����벻��ȷ
		/// </summary>
		typedef int32(*UserLogOnFunc)(E_MsgType MsgType, const char* Ip, const char* Usr, const char* PassWord);
		/// <summary>
		/// ���ӹر�ʱ������
		/// </summary>
		typedef int32(*UserLinkCloseFunc)(E_MsgType MsgType, const char* Ip);
		/// <summary>
		/// �û�������Ϣ
		/// StatusType,0���ӳɹ���-1,�ͻ��˶˿ڷ�ΧԽ�ޣ�-2����Ȩ����������Ϣ,-3���ֳ�ʱ��-4����ʧ��
		/// </summary>
		typedef int32(*UserLinkFunc)(E_MsgType MsgType, const char* Ip, int32 StatusType);
	public:
		int32 PowerUpIni(int32 Type);
		static DbgToolsServer& Instance();
		/// <summary>
		/// ����Ψһ�Դ�����֤����
		/// </summary>
		/// <param name="func"></param>
		void SetCheckDeviceIdFunc(CheckDeviceIdFunc func);
		CheckDeviceIdFunc GetCheckDeviceIdFunc() { return checkDeviceIdFunc; }
		/// <summary>
		/// �����û���¼��֤����
		/// </summary>
		/// <param name="func"></param>
		void SetUserLogOnFunc(UserLogOnFunc func);
		UserLogOnFunc GetUserLogOnFunc() { return userLogOnFunc; }
		/// <summary>
		/// �������ӹرպ���
		/// </summary>
		/// <param name="func"></param>
		void SetUserLinkCloseFunc(UserLinkCloseFunc func);
		UserLinkCloseFunc GetUserLinkCloseFunc() { return userLinkCloseFunc; }
		void SetClientClose(E_MsgType MsgType, const char* Ip);
		/// <summary>
		/// �����쳣���ӻص�����
		/// </summary>
		/// <param name="func"></param>
		void SetUserLinkFunc(UserLinkFunc func);
		bool8 LogOn(E_MsgType MsgType, DbgSocket& Sock);
	public:
		enum TaskStep
		{
			E_PowerUpIni = 0,
			E_IniServer,
			E_WaitClient,
			E_NetStorm,
			E_CheckClient,
		};
	protected:
		DbgToolsServer();
		virtual int32 OneLoop();
	protected:
		MsTimer msTimer;
		MsPeriodTimer checkTimer;
		DbgTcpServer signIn;
		CheckDeviceIdFunc checkDeviceIdFunc;
		UserLogOnFunc userLogOnFunc;
		UserLinkCloseFunc userLinkCloseFunc;
		UserLinkFunc userLinkFunc;
	};
	class DbgClient :public Task
	{
	public:
		enum TaskStep
		{
			E_PowerUpIni = 0,
			E_ClentIni,
			E_WaitConnect,
			E_AskConnect,
			E_LogOn,
			E_AskIniInfo,
			E_Work,
			E_Check,
		};
		enum TaskLogStep
		{
			E_StartLog,
			E_InputPw,
			E_CheckPw,
			E_LogOnOk,
			E_LogOnIdErr,
			E_LogOnLinkErr,
			E_LogOnAccountErr,
			E_LogOnAccountLock,
			E_LogOverTime,
		};
	public:
		int32 PowerUpIni(int32 Para);
		void SendLogHeartBeat();
		void ReConnect();
		void ClientIni();
		void WaitConnect();
		void AskConnect(uint16 Cmd);
		void OneLoopPowerUpIni();
		int32 StartClient(uint16 Cmd, uint32 LocalIp, uint16 LocalPort, uint32 RemoteIp, uint16 RemotePort, int32 ClientSock);
		bool8 LogOn(DbgToolsServer::E_MsgType MsgType, DbgSocket& Sock);
		uint8 LogStatus() { return logstatus; };
	protected:
		DbgClient();
		virtual bool8 AskForLogOnInfo(bool8 isCheckId, bool8 isCheckAccount, SalString& Id, SalString& Name, SalString& Pw, int32(*DoHeartCheck)()) { return 0; };
	protected:
		DbgClientCfg* cfg;
		bool8 isAskConnect;
		bool8 isIdCheck;
		bool8 isPwCheck;
		uint32 signInStep;
		DbgTcpClient signIn;
		MsPeriodTimer checkTimer;
		MsPeriodTimer logTimer;
		MsStampTimer lastUpdateReconnected;
		uint8 logstatus;
		DbgToolsServer::E_MsgType msgType;
		DbgTcpGmClient gmsock;
	};
}
#include "DbgIedTools.h"
#include "DbgDbgTools.h"

#endif
