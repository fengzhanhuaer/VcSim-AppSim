#ifndef DBGLCDCMM_H
#define DBGLCDCMM_H

namespace spt
{
	class VirLcdCmmClient :public DbgClient
	{
	public:
		void ReConnect();
		int32 PowerUpIni(int32 Type);
		virtual int32 OneLoop();
		void SetIedInfoIniedFlag(bool8 inied);
		TaskStep TaskStep() { return (DbgClient::TaskStep)taskStep; }
	public:
		static VirLcdCmmClient& Instance();
	protected:
		VirLcdCmmClient();
	protected:
		bool8 isAskConnect;
		bool8 IsIedInfoAsked;
		bool8 IsIedInfoInied;

	};
	bool8 AskForLogOnInfo(bool8 isCheckId, bool8 isCheckAccount, SalString& Id, SalString& Name, SalString& Pw, int32(*DoHeartCheck)());

}



#endif// DBGLCDCMM_H
