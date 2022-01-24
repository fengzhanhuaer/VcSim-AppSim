#ifndef INSTAPPCMM_H
#define INSTAPPCMM_H

enum AppSlowMsgDriverIndex
{
	E_MsgTrans,
	E_ParaSetTrans,
	E_FileTrans,
	E_EventTrans,
	E_SjRecordTrans,
	E_StatusTrans,
	E_EventStatusTrans,
	E_AngRmsTrans,
	E_ASMDI_Total
};
enum AppSlowMsgType
{
// 初始化交互数据
	E_ASMT_NULL=0,
	E_ASMT_INIT,
	E_ASMT_INIT_ACK,
	E_ASMT_SLOW_1,
	E_ASMT_SLOW_1_ACK,
	E_ASMT_PARA_INIT,
	E_ASMT_PARA_INIT_ACK,
	E_ASMT_PARA_CLEAR,
	E_ASMT_PARA_CLEAR_ACK,
	E_ASMT_PARA_ADJUST,
	E_ASMT_PARA_ADJUST_ACK,
	// 返校失败
	E_ASMT_ACK_NO=0x1000,
	E_ASMT_END,
};

extern ApiAppFastCmm& AppInstFastCmm;
extern ApiAppSlowCmm AppInstSlowCmm;

int32 AppCmmPowerUpIni();
int32 AppSendFile2SubBoard(const char* SurFile, const char* DstFile, int32(*Process)(int32 Step, const char* info));
int32 AppSendPara2SubBoard(ApiParaGroup* ParaGroup, uint32 Zone);
int32 AppCmmSend();
/// 进行同步消息发送（在调用线程中进行），并等待结果
/// </summary>
/// <param name="Type"></param>
/// <param name="Paras"></param>
/// <param name="SendBuf"></param>
/// <param name="SendLen"></param>
/// <param name="RecvBuf"></param>
/// <param name="RecvBufLen"></param>
/// <param name="RecvMsgLen"></param>
/// <returns></returns>
int32 AppSend2SubBoardMsgAndWaitAck(uint32 Type, int32 Paras, uint8* SendBuf, uint8 SendLen, uint8* RecvBuf, uint8 RecvBufLen);
/// <summary>
/// 启动异步消息发送，并立即返回，不等待执行结果
/// </summary>
/// <param name="Type"></param>
/// <returns></returns>
int32 StartSend2SubBoardMsg(uint32 Type);
#endif
