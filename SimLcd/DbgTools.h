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
		CfgStr ServerIp;
		CfgStr ClientIp;
		CfgUint32 ClientPort;
		CfgBool EnableGmssl;
		CfgUint32 GmsslVerifyMode;
		CfgStr GmsslLinkMode;
		CfgUint32 GmsslCrtFormat;
		CfgBool EnableGmCrtCheck;
		CfgHex32 ForeGroundColour;
		CfgHex32 BackGroundColour;
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
		int32 PowerUpIni(int32 Type);
		static DbgToolsServer& Instance();
	public:
		enum TaskStep
		{
			E_PowerUpIni = 0,
			E_IniServer,
			E_WaitClient,
			E_NetStorm,
			E_CheckClient,
		};
		enum SignInStep
		{
			E_Wait = 0,
			E_StartLog,
			E_WaitCmd,
		};
	protected:
		DbgToolsServer();
		virtual int32 OneLoop();
	protected:
		uint32 signInStep;
		MsTimer msTimer;
		MsPeriodTimer checkTimer;
		DbgTcpServer signIn;
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
		void SendLogHeartBeat();
		void ReConnect();
		void ClientIni();
		void WaitConnect();
		void AskConnect(uint16 Cmd);
		void OneLoopPowerUpIni();
		bool8 LogOn(DbgToolsServer::E_MsgType MsgType, DbgSocket& Sock);
		uint8 LogStatus() { return logstatus; };
	protected:
		DbgClient();
	protected:
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
		DbgSocket* sock;
	};
}
#include"DbgLcdCmm.h"
#include"DbgServer.h"

#endif
