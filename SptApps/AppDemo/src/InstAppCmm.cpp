#include "InstResource.h"
using namespace spt;

extern CmmMsgDriver SlowMsgDriver[E_ASMDI_Total];
int32 Send2SubBoardMsg(class SalCmmChannel* Cmm, struct CmmMsgDriver* Driver);
int32 AppSlowCmmMsgRecvFunc(class SalCmmChannel* Cmm, struct CmmMsgDriver* Driver, SalCmmMsgHeader* Header);

int32 AppFastCmmMsgRecvFunc(class SalCmmChannel* Cmm, struct CmmMsgDriver* Driver, SalCmmMsgHeader* Header)
{
	//AppCmmFrame* frame = (AppCmmFrame*)Header;
	//frame.data is the first address of app data.

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
	//此处缓冲区大小请向平台组咨询如何设置
	AppInstFastCmm.PowerUpIni(FastMsgDriver, M_ArrLen(FastMsgDriver), 0x0001, 0x0002, 10, 200);
	AppInstSlowCmm.PowerUpIni(SlowMsgDriver, M_ArrLen(SlowMsgDriver), 0x0001, 0x0002, 32, 256);
#ifdef WIN32_SIM
	AppInstSlowCmmTest.PowerUpIni(SlowMsgDriver, M_ArrLen(SlowMsgDriver), 0x0002, 0x0001, 32, 256);
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
	if (Driver.SendPara == E_ASMT_Inst3)
	{
		trans.Send(Driver.SendPara, 0, 0, 0);
		Driver.HasNewToSend = 0;
		return 0;
	}
	return -1;
}
int32 StartSend2SubBoardMsg(uint32 Type)
{
	CmmMsgDriver& Driver = SlowMsgDriver[E_MsgTrans];
	if (Type == E_ASMT_Inst3)
	{
		Driver.SendPara = Type;
		Driver.HasNewToSend = 1;
		return 0;
	}
	return -1;
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
	if (Msg->type == E_ASMT_Inst1)
	{
		ptrans->Send(E_ASMT_Inst1Ack, 0, 0, 0);
	}
	else if (Msg->type == E_ASMT_Inst2)
	{
		ptrans->Send(E_ASMT_Inst2Ack, 0, 0, 0);
	}
	else if (Msg->type == E_ASMT_Inst3)
	{
		ptrans->Send(E_ASMT_Inst3Ack, 0, 0, 0);
	}
	else
	{
		ptrans->Recv(Driver, Header);
	}
	return 0;
}
int32 AppSend2SubBoardMsgAndWaitAck(uint32 Type, int32 Paras, uint8* SendBuf, uint8 SendLen, uint8* RecvBuf, uint8 RecvBufLen, int32& RecvMsgLen)
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
	if (Type == E_ASMT_Inst1)
	{
		SalMsgTrans::Msg* Msg = 0;
		int32 res = trans.WaitMsg(E_ASMT_Inst1Ack, Msg, 1000);
		if (res == SalMsgTrans::E_RecvOverTime)
		{
			Driver.SendPtr = 0;
			Driver.sendMutex = 0;
			return SalMsgTrans::E_RecvOverTime;
		}
		int32 min = Min((uint32)RecvBufLen, Msg->msgLen);
		if (min)
		{
			MemCpy(RecvBuf, Msg->data, min);
		}
		RecvMsgLen = min;
		Driver.SendPtr = 0;
		Driver.sendMutex = 0;
		return Msg->paras;
	}
	//无需等待返回
	else if (Type == E_ASMT_Inst2)
	{
		RecvMsgLen = 0;
		Driver.SendPtr = 0;
		Driver.sendMutex = 0;
		return 0;
	}
	Driver.SendPtr = 0;
	Driver.sendMutex = 0;
	return -1;
}
