#ifndef DBGLCDCMM_H
#define DBGLCDCMM_H

namespace spt
{
	class VirLcdCmmClient :protected DbgClient
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
		bool8 IsIedInfoAsked;
		bool8 IsIedInfoInied;
		MsStampTimer lastUpdateReconnected;
	};


}



#endif// DBGLCDCMM_H
