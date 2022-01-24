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
		CfgBool NeedUsrLog;
		CfgStrData20 ServerIp;
		CfgBool EnableGmssl;
		CfgUint32 GmsslVerifyMode;
		CfgStrData40 GmsslLinkMode;
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
			E_ServiceAsk = 1,
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
		DbgUdpServer signIn;
	};
	class DbgClient :public Task
	{
	public:
		enum TaskStep
		{
			E_PowerUpIni = 0,
			E_ClentIni,
			E_LogOn,
			E_SendCmd,
			E_AskIniInfo,
			E_Work,
			E_Check,
		};
	protected:
		DbgClient();
		void LogOn();
	protected:
		uint32 signInStep;
		DbgUdpClient signIn;
		MsPeriodTimer checkTimer;
	};
}
#include"DbgServer.h"

#endif
