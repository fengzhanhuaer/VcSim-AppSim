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
	E_ASMT_Inst1,
	E_ASMT_Inst1Ack,
	E_ASMT_Inst2,
	E_ASMT_Inst2Ack,
	E_ASMT_Inst3,
	E_ASMT_Inst3Ack,
};

extern ApiAppFastCmm& AppInstFastCmm;
extern ApiAppSlowCmm AppInstSlowCmm;

int32 AppCmmPowerUpIni();
int32 AppSendFile2SubBoard(const char* SurFile, const char* DstFile, int32(*Process)(int32 Step, const char* info));
int32 AppSendPara2SubBoard(ApiParaGroup* ParaGroup, uint32 Zone);
/// <summary>
/// ����ͬ����Ϣ���ͣ��ڵ����߳��н��У������ȴ����
/// </summary>
/// <param name="Type"></param>
/// <param name="Paras"></param>
/// <param name="SendBuf"></param>
/// <param name="SendLen"></param>
/// <param name="RecvBuf"></param>
/// <param name="RecvBufLen"></param>
/// <param name="RecvMsgLen"></param>
/// <returns></returns>
int32 AppSend2SubBoardMsgAndWaitAck(uint32 Type, int32 Paras, uint8* SendBuf, uint8 SendLen, uint8* RecvBuf, uint8 RecvBufLen, int32& RecvMsgLen);
/// <summary>
/// �����첽��Ϣ���ͣ����������أ����ȴ�ִ�н��
/// </summary>
/// <param name="Type"></param>
/// <returns></returns>
int32 StartSend2SubBoardMsg(uint32 Type);


#endif
