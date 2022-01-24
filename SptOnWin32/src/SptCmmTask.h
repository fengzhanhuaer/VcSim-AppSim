#ifndef SPTCMMTASK_H
#define SPTCMMTASK_H
namespace spt
{
	class SptAppFastCmm :public SalTransCmm
	{
	public:
		int32 SendMsgTo(uint16 Dst, uint32 UnPackIndex, uint16 Type, uint16 DataLen, void* Data);
		int32 RecvFromHal(uint16 DataLen, void* Data);
		virtual int32 ProcIn() override;
		virtual int32 Proc() override;
		virtual int32 ProcOut()override;
	};
	class SptAppSlowCmm :public SalTransCmm
	{
	public:
		virtual int32 ProcIn() override;
		virtual int32 Proc() override;
		virtual int32 ProcOut()override;
		int32 RecvFromHal(uint16 DataLen, void* Data);
		virtual int32 SendMsgTo(uint16 Dst, uint32 UnPackIndex, uint16 Type, uint16 DataLen, void* Data);
	public:
		SptAppSlowCmm();
	protected:

	};

	class SptAppCmmTask :public Task
	{
	public:
		M_Singleton(SptAppCmmTask);
		virtual int32 PowerUpIni(int32 Para);
		virtual int32 OneLoop();
		int32 RgsAppCmmTask(SalCmmChannel* Channel);
		int32 RecvFromHal(uint16 DataLen, void* Data);
		SalCmmChannel* CmmChannel(int32 Index);
		int32 CmmChannelNum();
	protected:
		SptAppCmmTask();
	protected:
		SingleStackBuf cmmTask;
	};
	class SptPublicCmmTask :public Task
	{
	public:
		M_Singleton(SptPublicCmmTask);
		virtual int32 PowerUpIni(int32 Para);
		virtual int32 OneLoop();
		int32 RgsAppCmmTask(SalCmmChannel* Channel);
		SalCmmChannel* CmmChannel(int32 Index);
		int32 CmmChannelNum();
	protected:
		SptPublicCmmTask();
	protected:
		SingleStackBuf cmmTask;
	};


}
#endif // !SPTCMMTASK_H

