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
		CfgBool NeedCheckDeviceId;
		CfgBool NeedUsrLog;
		CfgStrData20 ServerIp;
		CfgBool EnableGmssl;
		CfgUint32 GmsslVerifyMode;
		CfgStrData40 GmsslLinkMode;
		CfgUint32 GmsslCrtFormat;
		CfgBool EnableGmCrtCheck;
	private:
		PCfgDataBase pool[20];
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
			E_DbgServer
		};
	public:
		typedef bool8(*CheckDeviceIdFunc)(E_MsgType MsgType, const char* Ip, const char* UsrInputDeviceId);
		typedef bool8(*UserLogOnFunc)(E_MsgType MsgType, const char* Ip, const char* Usr, const char* PassWord);
		typedef bool8(*UserLinkCloseFunc)(E_MsgType MsgType, const char* Ip);
	public:
		int32 PowerUpIni(int32 Type);
		static DbgToolsServer& Instance();
		/// <summary>
		/// 设置唯一性代码验证函数
		/// </summary>
		/// <param name="func"></param>
		void SetCheckDeviceIdFunc(CheckDeviceIdFunc func);
		CheckDeviceIdFunc GetCheckDeviceIdFunc() { return checkDeviceIdFunc; }
		/// <summary>
		/// 设置用户登录验证函数
		/// </summary>
		/// <param name="func"></param>
		void SetUserLogOnFunc(UserLogOnFunc func);
		UserLogOnFunc GetUserLogOnFunc() { return userLogOnFunc; }
		/// <summary>
		/// 设置连接关闭函数
		/// </summary>
		/// <param name="func"></param>
		void SetUserLinkCloseFunc(UserLinkCloseFunc func);
		UserLinkCloseFunc GetUserLinkCloseFunc() { return userLinkCloseFunc; }
		void SetClientClose(E_MsgType MsgType, const char* Ip);
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
			E_SendCmd,
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
			E_LogOverTime,
		};
	public:
		void SendLogHeartBeat();
		bool8 LogOn(DbgToolsServer::E_MsgType MsgType, DbgSocket& Sock);
		uint8 LogStatus() { return logstatus; };
	protected:
		DbgClient();
		void AskConnect();
		void SendCmd(uint16 Cmd);
	protected:
		bool8 isIdCheck;
		bool8 isPwCheck;
		uint32 signInStep;
		DbgTcpClient signIn;
		MsPeriodTimer checkTimer;
		MsPeriodTimer logTimer;
		uint8 logstatus;
		DbgToolsServer::E_MsgType msgType;
		DbgSocket* sock;
	};
}
#include"DbgServer.h"

#endif
