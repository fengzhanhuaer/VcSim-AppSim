#include "InstResource.h"
using namespace spt;

extern CmmMsgDriver SlowMsgDriver[E_ASMDI_Total];
int32 Send2SubBoardMsg(class SalCmmChannel* Cmm, struct CmmMsgDriver* Driver);
int32 AppSlowCmmMsgRecvFunc(class SalCmmChannel* Cmm, struct CmmMsgDriver* Driver, SalCmmMsgHeader* Header);

int32 AppFastCmmMsgRecvFunc(class SalCmmChannel* Cmm, struct CmmMsgDriver* Driver, SalCmmMsgHeader* Header)
{
	SalTransFrame* frame = (SalTransFrame*)Header;
	IES_IMCom_Fast_Rx_Buf(frame->data, frame->Header.dataLen, frame->Header.type);

	return 0;
}

int32 AppSlowCmmMsgRecvFileFunc(class SalCmmChannel* Cmm, struct CmmMsgDriver* Driver, SalCmmMsgHeader* Header)
{
	static StaticAdtBufDes<2048> des;
	static SalFileTrans trans(des.Des.Des, Cmm, Cmm->Dst(), Driver);
	SalFileTrans* ptrans = (SalFileTrans*)Driver->SendPtr;
	if (Driver->SendPtr && (ptrans->Dst() == Header->sur))
	{
	}
	else
	{
		ptrans = &trans;
	}
	ptrans->Recv(Driver, Header);
	if (trans.GetProcess() == trans.E_CheckAck)
	{
		if ((trans.GetRusult() == 0) && (!Driver->SendPtr))
		{
			if (trans.DstFile().IsInclude("user.dat") >= 0)
			{
				SalUserMng::Instance().LoadPool();
			}
			else if (trans.DstFile().IsInclude("AccountCfg.cfg") >= 0)
			{
				SalUserMng::Instance().UsrCfg.ReadAll();
			}
		}
	}
	return 0;
}
int32 AppSlowCmmMsgRecvParaFunc(class SalCmmChannel* Cmm, struct CmmMsgDriver* Driver, SalCmmMsgHeader* Header)
{
	static StaticAdtBufDes<128> des;
	static StaticAdtBufDes<2048> editdes;
	static SalParaTrans trans(des.Des.Des, editdes.Des.Des, Cmm, Cmm->Dst(), Driver);
	SalParaTrans* ptrans = (SalParaTrans*)Driver->SendPtr;
	if (Driver->SendPtr && (ptrans->Dst() == Header->sur))
	{
	}
	else
	{
		ptrans = &trans;
	}
	ptrans->Recv(Driver, Header);
	return 0;
}
CmmMsgDriver FastMsgDriver[1] =
{
	{"FastCMM1",0,0,0,AppFastCmmMsgRecvFunc}
};
CmmMsgDriver SlowMsgDriver[E_ASMDI_Total] =
{
	{"SlowMsg",E_MsgTrans,SalTransProtocol::E_MsgTrans,Send2SubBoardMsg,AppSlowCmmMsgRecvFunc},
	{"SlowPara",E_ParaSetTrans,SalTransProtocol::E_ParaTrans,0,AppSlowCmmMsgRecvParaFunc},
	{"SlowFile",E_FileTrans,SalTransProtocol::E_FileTrans,0,AppSlowCmmMsgRecvFileFunc},
	{"Slowvent",E_EventTrans},
	{"SlowSjRecord",E_SjRecordTrans,0,0,0},
	{"SlowStatus",E_StatusTrans,0,0,0},
	{"SlowEStatus",E_EventStatusTrans,0,0,0},
	{"SlowRms",E_AngRmsTrans,0,0,0},
};

ApiAppFastCmm& AppInstFastCmm = ApiAppFastCmm::Instance();
ApiAppSlowCmm AppInstSlowCmm("SlowCmm");
#ifdef WIN32_SIM
ApiAppSlowCmm AppInstSlowCmmTest("从板SlowCmm");
#endif // WIN32_SIM

int32 AppCmmPowerUpIni()
{
	// 缓冲区BufLen 最大256,设置不能超过256
	AppInstFastCmm.PowerUpIni(FastMsgDriver, M_ArrLen(FastMsgDriver), CN_BOARD_CPU, CN_BOARD_CPU_OTH, 10, 200);
	AppInstSlowCmm.PowerUpIni(SlowMsgDriver, M_ArrLen(SlowMsgDriver), CN_BOARD_CPU, CN_BOARD_CPU_OTH, 32, 256);
#ifdef WIN32_SIM
	AppInstSlowCmmTest.PowerUpIni(SlowMsgDriver, M_ArrLen(SlowMsgDriver), CN_BOARD_CPU_OTH, CN_BOARD_CPU, 32, 256);
#endif // WIN32_SIM
	return 0;
}
int32 AppSendFile2SubBoard(const char* SurFile, const char* DstFile, int32(*Process)(int32 Step, const char* info))
{
	CmmMsgDriver& Driver = SlowMsgDriver[E_FileTrans];
	if (Driver.sendMutex)
	{
		return -1;
	}
	Driver.sendMutex = 1;
	SalCmmChannel* cmm = (SalCmmChannel*)&AppInstSlowCmm;
	StaticAdtBufDes<2048> des;
	SalFileTrans trans(des.Des.Des, cmm, cmm->Dst(), &Driver);
	Driver.SendPtr = &trans;
	int32 res = trans.Send(Process, SurFile, DstFile);
	Driver.SendPtr = 0;
	Driver.sendMutex = 0;
	return res;
}

int32 AppSendPara2SubBoard(ApiParaGroup* ParaG, uint32 Zone)
{
	CmmMsgDriver& Driver = SlowMsgDriver[E_ParaSetTrans];
	if (Driver.sendMutex)
	{
		return -1;
	}
	Driver.sendMutex = 1;

	SalParaGroup* para = (SalParaGroup*)ParaG;
	SalCmmChannel* cmm = (SalCmmChannel*)&AppInstSlowCmm;
	StaticAdtBufDes<2048> des;
	StaticAdtBufDes<2048> editdes;
	SalParaTrans trans(des.Des.Des, editdes.Des.Des, cmm, cmm->Dst(), &Driver);
	Driver.SendPtr = &trans;
	int32 res = trans.Send(0, Zone, para->DesName());
	Driver.SendPtr = 0;
	Driver.sendMutex = 0;
	return res;
}
// 该函数在通信任务中执行，因此执行waitmsg不能有延时操作（会产生线程的阻塞，任务死锁）。
int32 Send2SubBoardMsg(class SalCmmChannel* Cmm, struct CmmMsgDriver* driver)
{
	CmmMsgDriver& Driver = *driver;
	if (Driver.sendMutex)
	{
		return -1;
	}
	StaticAdtBufDes<2048> des;
	SalMsgTrans trans(des.Des.Des, Cmm, Cmm->Dst(), &Driver);
	if ((Driver.SendPara == E_ASMT_INIT) || (Driver.SendPara == E_ASMT_SLOW_1))
	{
		trans.Send(Driver.SendPara, g_tComSlowTx.wType, g_tComSlowTx.byData, g_tComSlowTx.wLen);
		g_tComSlowTx.wSendFlag = FALSE;
		Driver.HasNewToSend = 0;
		return 0;
	}
	return -1;
}
int32 StartSend2SubBoardMsg(uint32 Type)
{
	CmmMsgDriver& Driver = SlowMsgDriver[E_MsgTrans];
	Driver.SendPara = Type;
	Driver.HasNewToSend = 1;
	return 0;
}
// 该函数在通信任务中执行，因此执行waitmsg不能有延时操作（会产生线程的阻塞，任务死锁）。
int32 AppSlowCmmMsgRecvFunc(class SalCmmChannel* Cmm, struct CmmMsgDriver* Driver, SalCmmMsgHeader* Header)
{

	static StaticAdtBufDes<2048> des;
	static SalMsgTrans trans(des.Des.Des, Cmm, Cmm->Dst(), Driver);
	SalMsgTrans* ptrans = (SalMsgTrans*)Driver->SendPtr;
	if (Driver->SendPtr && (ptrans->Dst() == Header->sur))
	{
	}
	else
	{
		ptrans = &trans;
	}
	SalTransFrame* frame = (SalTransFrame*)Header;
	SalMsgTrans::Msg* Msg = (SalMsgTrans::Msg*)frame->data;
	if ((Msg->type == E_ASMT_INIT) || (Msg->type == E_ASMT_SLOW_1))
	{
		IES_IMCom_Slow_Rx_Buf(Msg->data, Msg->msgLen, Msg->paras);
	}
	else if (Msg->type == E_ASMT_PARA_INIT)
	{
		int32 res = AppParaDefault(Msg->paras);
		ptrans->Send(E_ASMT_PARA_INIT_ACK, res, 0, 0);
	}
	else if (Msg->type == E_ASMT_PARA_CLEAR)
	{
		bool8 res = AppEventClear(Msg->paras);
		ptrans->Send(E_ASMT_PARA_CLEAR_ACK, res, 0, 0);
	}
	else if (Msg->type == E_ASMT_PARA_ADJUST)
	{
		ptrans->Send(E_ASMT_PARA_ADJUST_ACK, 0, 0, 0);
	}
	else
	{
		ptrans->Recv(Driver, Header);
	}
	return 0;
}
int32 AppSend2SubBoardMsgAndWaitAck(uint32 Type, int32 Paras, uint8* SendBuf, uint8 SendLen, uint8* RecvBuf, uint8 RecvBufLen)
{
	CmmMsgDriver& Driver = SlowMsgDriver[E_MsgTrans];
	if (Driver.sendMutex)
	{
		return -1;
	}
	Driver.sendMutex = 1;
	SalCmmChannel* cmm = (SalCmmChannel*)&AppInstSlowCmm;
	StaticAdtBufDes<2048> des;
	SalMsgTrans trans(des.Des.Des, cmm, cmm->Dst(), &Driver);
	Driver.SendPtr = &trans;
	trans.Send(Type, Paras, SendBuf, SendLen);
	//需要等待返回
	if (Type == E_ASMT_PARA_INIT)
	{
		SalMsgTrans::Msg* Msg = 0;
		int32 res = trans.WaitMsg(E_ASMT_PARA_INIT_ACK, Msg, 3000);
		if (res == SalMsgTrans::E_RecvOverTime)
		{
			Driver.SendPtr = 0;
			Driver.sendMutex = 0;
			return SalMsgTrans::E_RecvOverTime;
		}
		int32 min = Min((int32)RecvBufLen, (int32)Msg->msgLen);
		if (min)
		{
			MemCpy(RecvBuf, Msg->data, min);
		}
		Driver.SendPtr = 0;
		Driver.sendMutex = 0;
		return Msg->paras;
	}
	//需要等待返回
	if (Type == E_ASMT_PARA_CLEAR)
	{
		SalMsgTrans::Msg* Msg = 0;
		int32 res = trans.WaitMsg(E_ASMT_PARA_CLEAR_ACK, Msg, 5000);
		if (res == SalMsgTrans::E_RecvOverTime)
		{
			Driver.SendPtr = 0;
			Driver.sendMutex = 0;
			return SalMsgTrans::E_RecvOverTime;
		}
		int32 min = Min((int32)RecvBufLen, (int32)Msg->msgLen);
		if (min)
		{
			MemCpy(RecvBuf, Msg->data, min);
		}
		Driver.SendPtr = 0;
		Driver.sendMutex = 0;
		return Msg->paras;
	}
	//无需等待返回
	else if (Type == E_ASMT_PARA_ADJUST)
	{
		Driver.SendPtr = 0;
		Driver.sendMutex = 0;
		return 0;
	}
	Driver.SendPtr = 0;
	Driver.sendMutex = 0;
	return -1;
}

int32 AppCmmSend()
{
	if (g_tComFastTx.wFlag)
	{
		AppInstFastCmm.SendMsg(0, g_tComFastTx.wType, g_tComFastTx.wLen, g_tComFastTx.byData);
		g_tComFastTx.wFlag = FALSE;
	}
	return 0;
}


