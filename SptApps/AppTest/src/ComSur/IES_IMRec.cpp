/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * ���ɵ��ӹɷ����޹�˾
 * Ԫ�����ƣ�����Ԫ��
 * Ԫ�����ܣ�����Ԫ��
 *     1.�澯��������
 *     2.Խ����������
 * Ԫ���汾��V1.00
 * ����ʱ�䣺2020-9-7
 * �汾�޸ģ�
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
 * V1.00 2021-2-24 ��־��������
 *================================================================================*/

#include "IES_IMRec.h"

// Ԫ���ӿڽṹ��
tagIES_IMRec      gtagIES_IMRec;
// ============================================================================
// �������ܣ����ʱ�����(С��ģʽ)
// ���������UTCʱ��
// ���������32λus,���4294967295us=4294967.295ms=4294.967295s=
// ����ֵ��  ��
// ============================================================================
#ifdef __cplusplus
inline UINT32 IES_IMRec_Rela_Time(tagTimeUTC *ptUTCA,tagTimeUTC *ptUTCB)
{
	//UINT64  *u64A,*u64B;
	//u64A=(UINT64*)(&tUTCA.dwUSecond_L);
	//u64B=(UINT64*)(&tUTCB.dwUSecond_L);
	return (UINT32)(*((UINT64*)ptUTCA)-*((UINT64*)ptUTCB));
}
#else

#define IES_IMRec_Rela_Time(ptUTCA,ptUTCB)            \
{                                                     \
	(UINT32)(*((UINT64*)ptUTCA)-*((UINT64*)ptUTCB));    \
}

#endif
// ============================================================================
// �������ܣ�GOOSE������������
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMRec_Act(tagIES_IMRec  *pgtagIES_IMRec)
{
	register UINT32 i,j;
	register UINT32 *piMeaValue;
	const    WORD   *pwSrcIndexIn, *pwSrcIndexOut,*pwAppId;
	BOOL    *pbActIn,*pbActOut,*pbActOutRet;
	BOOL    *pbSrcIn,*pbSrcOut,*pbSrcOutRet;
	BOOL     bActInXor,bActOutXor;
	BOOL     bDstIn=FALSE,bDstOut=FALSE,bDstOutRet=FALSE;
	BOOL    *pbyInvaild;
	
	register tagActEvent   *ptagActEvent;
	register tagCosEvent6  *ptEvent;
	const tagActTab  *ptActTab;
	
	ptActTab      = g_tActTab;
	pbActIn       = g_tActState.bActIn;
	pbActOut      = g_tActState.bActOut;
	pbActOutRet   = g_tActState.bActOutRet;
	ptagActEvent  = g_tActState.tActEvent;
	
	pbSrcOut     = g_tagIO.bGoInValid;
	pbSrcIn      = g_tagIO.bGoIn;
	pbyInvaild   = g_tagIO.byGoInInValid;
	pbSrcOutRet  = g_tagIO.bDIHldIn;
	pwAppId      = g_tagIO.wGoInAppId;
	// ��ʱ���Ӳ������ж�
	for(i=0;i<CN_NUM_ACT;i++)
	{
		// ʵʱ����ˢ��
		pwSrcIndexOut=pwSrcIndexIn=ptActTab->wSrcIndex;
		for(j=0;j<CN_ACT_SNUM;j++)
		{
			if(*pwSrcIndexIn==CN_NULL_PINNO)
			{
				bDstIn=FALSE;
				break;
			}
			if(pbSrcIn[*pwSrcIndexIn])
			{
				bDstIn=TRUE;
				break;
			}
			pwSrcIndexIn++;
		}

		for(j=0;j<CN_ACT_SNUM;j++)
		{
			if(*pwSrcIndexOut==CN_NULL_PINNO)
			{
				bDstOut=FALSE;
				break;
			}
			if(pbSrcOut[*pwSrcIndexOut])
			{
				bDstOut=TRUE;
				break;
			}
			pwSrcIndexOut++;
		}
		// �����ڳ�ʼ��
		*pbActOutRet=bDstOutRet=pbSrcOutRet[ptActTab->wDoRetIndex];
		
		piMeaValue=ptagActEvent->iMeaValue;
		// ��У�ȴ�
		if(ptagActEvent->byFlag==EN_ACTS_EVENT_WAIT)
		{
			if(*pbActOut==bDstOutRet)
			{
				// ��������
				piMeaValue[EN_VAILD_FAIL]  =EN_INVAILD_NO;
				piMeaValue[EN_VAILD_RET_T] =IES_IMRec_Rela_Time(&g_tagPub.tSysTimeUTC,&ptagActEvent->tActT);
				ptagActEvent->byFlag       =EN_ACTS_EVENT_STOP;
				// ��������
			}
			else if((++ptagActEvent->dwTimeCnt)>=CN_T7MS)
			{
				piMeaValue[EN_VAILD_FAIL]  =EN_RET_OVER;
				piMeaValue[EN_VAILD_RET_T] =IES_IMRec_Rela_Time(&g_tagPub.tSysTimeUTC,&ptagActEvent->tActT);//
				ptagActEvent->byFlag       =EN_ACTS_EVENT_STOP;
			}
		}
		bActInXor  =bDstIn^(*pbActIn);
		bActOutXor =bDstOut^(*pbActOut);
		// ����������
		if(bActInXor||bActOutXor)
		{
			*pbActIn=bDstIn;
			*pbActOut=bDstOut;
			// �����ֱ����������
			if(ptagActEvent->byFlag!=EN_ACTS_EVENT_NULL)
			{
				piMeaValue[EN_VAILD_FAIL]  =EN_RET_COVER;
				piMeaValue[EN_VAILD_RET_T] =IES_IMRec_Rela_Time(&g_tagPub.tSysTimeUTC,&ptagActEvent->tActT);
				// ����洢
				{
					ptEvent=&g_tActQueue.tEvent[g_tActQueue.wWptr];
					ptEvent->wIndex = i;
					ptEvent->wState = ptagActEvent->bActState;
					ptEvent->tTime  = ptagActEvent->tActT;
					ptEvent->iMeaValue[0]=piMeaValue[0];
					ptEvent->iMeaValue[1]=piMeaValue[1];
					ptEvent->iMeaValue[2]=piMeaValue[2];
					ptEvent->iMeaValue[3]=piMeaValue[3];
					ptEvent->iMeaValue[4]=piMeaValue[4];
					ptEvent->iMeaValue[5]=piMeaValue[5];
					
					if(++g_tActQueue.wWptr>=CN_NUM_RPT_ACT)
					{
						g_tActQueue.wWptr=0;
					}
					if(g_tActQueue.wWptr==g_tActQueue.wRptr)
					{
						g_tActQueue.wFlag=CN_RPT_FULL;
					}
				}
				ptagActEvent->byFlag=EN_ACTS_EVENT_NULL;
			}
			// ��֤���κ�������Լ�⵽�仯,�Ӷ���������
			if(bDstOut)
			{
				ptagActEvent->bActState= bDstIn+2;
			}
			else
			{
				ptagActEvent->bActState= bDstIn;
			}
			piMeaValue[EN_VAILD_GOOSE] =bDstIn;
			piMeaValue[EN_VAILD_DO] =bDstOut;
			ptagActEvent->tActT=g_tagPub.tSysTimeUTC;
			// ��¼GOOSE����AppID,�����������¼
			if(bDstOut)
			{
				piMeaValue[EN_VAILD_SRC_INDEX]=*pwSrcIndexOut;
				piMeaValue[EN_VAILD_SRC_APPID]=pwAppId[*pwSrcIndexOut];
			}
			else if(bDstIn)
			{
				piMeaValue[EN_VAILD_SRC_INDEX]=*pwSrcIndexIn;
				piMeaValue[EN_VAILD_SRC_APPID]=pwAppId[*pwSrcIndexIn];
			}
			else if((bActInXor)&&(ptagActEvent->wActInIndex!=CN_NULL_PINNO))
			{
				piMeaValue[EN_VAILD_SRC_INDEX]=ptagActEvent->wActInIndex;
				piMeaValue[EN_VAILD_SRC_APPID]=pwAppId[ptagActEvent->wActInIndex];
			}
			else if((bActOutXor)&&(ptagActEvent->wActOutIndex!=CN_NULL_PINNO))
			{
				piMeaValue[EN_VAILD_SRC_INDEX]=ptagActEvent->wActOutIndex;
				piMeaValue[EN_VAILD_SRC_APPID]=pwAppId[ptagActEvent->wActOutIndex];
			}
			else
			{
				piMeaValue[EN_VAILD_SRC_INDEX]=CN_NULL_PINNO;
				piMeaValue[EN_VAILD_SRC_APPID]=0;
			}
			// ����ֱ��ֹͣ����
			if(bDstIn^bDstOut)
			{
				if(*pwSrcIndexIn<CN_NUM_GOIN)
				{
					piMeaValue[EN_VAILD_FAIL]=(UINT32)pbyInvaild[*pwSrcIndexIn];
				}
				else
				{
					piMeaValue[EN_VAILD_FAIL]=EN_RET_DIF;
				}
				piMeaValue[EN_VAILD_RET_T]=0;
				ptagActEvent->byFlag  =EN_ACTS_EVENT_STOP;
			}
			else if(bDstOut==bDstOutRet)
			{
				piMeaValue[EN_VAILD_FAIL]=EN_RET_ELSE;
				piMeaValue[EN_VAILD_RET_T]=0;
				ptagActEvent->byFlag=EN_ACTS_EVENT_STOP;
			}
			else
			{
				piMeaValue[EN_VAILD_FAIL]=EN_INVAILD_NO;
				ptagActEvent->byFlag =EN_ACTS_EVENT_WAIT;
				ptagActEvent->dwTimeCnt=0;
			}
		}
		// ��¼ö��
		ptagActEvent->wActInIndex  =*pwSrcIndexIn;
		ptagActEvent->wActOutIndex =*pwSrcIndexOut;
		// �������
		if(ptagActEvent->byFlag==EN_ACTS_EVENT_STOP)
		{
			// ���ɶ�������
			{
				ptEvent=&g_tActQueue.tEvent[g_tActQueue.wWptr];
				ptEvent->wIndex = i;
				ptEvent->wState = ptagActEvent->bActState;
				ptEvent->tTime  = ptagActEvent->tActT;
				ptEvent->iMeaValue[0]=piMeaValue[0];
				ptEvent->iMeaValue[1]=piMeaValue[1];
				ptEvent->iMeaValue[2]=piMeaValue[2];
				ptEvent->iMeaValue[3]=piMeaValue[3];
				ptEvent->iMeaValue[4]=piMeaValue[4];
				ptEvent->iMeaValue[5]=piMeaValue[5];
				if(++g_tActQueue.wWptr>=CN_NUM_RPT_ACT)
				{
					g_tActQueue.wWptr=0;
				}
				if(g_tActQueue.wWptr==g_tActQueue.wRptr)
				{
					g_tActQueue.wFlag=CN_RPT_FULL;
				}
			}
			ptagActEvent->byFlag =EN_ACTS_EVENT_NULL;
		}
		
		ptActTab++;
		pbActIn++;
		pbActOut++;
		pbActOutRet++;
		ptagActEvent++;
	}
}

// ============================================================================
// �������ܣ��澯��������
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMRec_Alm(tagIES_IMRec  *pgtagIES_IMRec)
{
	register UINT32  i;
	register BOOL *pbAlmIn,*pbAlmEna, *pbAlmOut,*pbAlmTimerEna;//*pbAlmXor,
	register BOOL  bAlmOut;
	register BOOL  bAlmDo=FALSE;
	register tagTimeRelay *ptTimer;
	register tagCosEvent  *ptEvent;
	register UINT32       *pMeaValue;
	const    tagAlmTab    *ptAlmTab;
	
	ptAlmTab = g_tAlmTab;
	pbAlmIn  = g_tAlmState.bAlmIn;
	pbAlmOut = g_tAlmState.bAlmOut;
	//pbAlmXor = g_tAlmState.bAlmXor;
	
	pbAlmEna = pgtagIES_IMRec->bAlmEna;
	ptTimer  = pgtagIES_IMRec->tTimer_Alm;
	pbAlmTimerEna= pgtagIES_IMRec->bAlmTimerEna;
	
	for(i=0;i<CN_NUM_ALM;i++)
	{
		if(!pbAlmEna[i])
		{
			IES_TimeRelayStop(ptTimer);
			bAlmOut=FALSE;
		}
		else if(pbAlmTimerEna[i])
		{
			bAlmOut=pbAlmIn[i];
		}
		else
		{
			bAlmOut=IES_TimeRelayRun(ptTimer, pbAlmIn[i]);
		}
		// �б�λ
		if(pbAlmOut[i]!=bAlmOut)
		{
			pbAlmOut[i]=bAlmOut;
			// ����洢
			ptEvent=&g_tAlmQueue.tEvent[g_tAlmQueue.wWptr];
			ptEvent->wIndex = i;
			ptEvent->wState = bAlmOut;
			if(ptAlmTab->wValType1!=CN_NULL_PINNO)
			{
				pMeaValue=g_tAlmState.tRecValue[i].iMeaValue;
				ptEvent->iMeaValue[0]= pMeaValue[0];
				ptEvent->iMeaValue[1]= pMeaValue[1];
				ptEvent->iMeaValue[2]= pMeaValue[2];
			}
			if(++g_tAlmQueue.wWptr>=CN_NUM_RPT_ALM)
			{
				g_tAlmQueue.wWptr=0;
			}
			if(g_tAlmQueue.wWptr==g_tAlmQueue.wRptr)
			{
				g_tAlmQueue.wFlag=CN_RPT_FULL;
			}
		}
		// ���ڱ�־�ϳ�
		if(bAlmOut)
		{
			if(ptAlmTab->wCfg&DB0)
			{
				bAlmDo=TRUE;
			}
		}
		ptTimer++;
		ptAlmTab++;
	}
	// �澯�������
	g_bFlag[EN_FLAG_ALM]=bAlmDo;
}
// ============================================================================
// �������ܣ��Լ���������
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMRec_Chk(tagIES_IMRec  *pgtagIES_IMRec)
{
	register UINT32  i;
	register UINT32  *pdwActCnt,*pdwRetCnt;
	register BOOL    *pbChkOut,*pbChkIn;//,*pbChkXor;
	register BOOL     bChkIn,bChkOut,bChkDo=FALSE,bChkBs=FALSE,bChkXor=FALSE;
	register tagCosEvent  *ptEvent;
	register UINT32       *pMeaValue;
	const tagChkTab  *ptChkTab;
	
	ptChkTab = g_tChkTab;
	pbChkIn  = g_tChkState.bChkIn;
	pbChkOut = g_tChkState.bChkOut;
	//pbChkXor = g_tChkState.bChkXor;
	pdwActCnt= g_tChkState.dwChkActCnt;
	pdwRetCnt= g_tChkState.dwChkRetCnt;

	for(i=0;i<CN_NUM_CHK;i++)
	{
		bChkIn =pbChkIn[i];
		if(bChkIn!=pbChkOut[i])
		{
			if((bChkIn)&&(pdwActCnt[i]>=ptChkTab[i].dwActCnt))
			{
				bChkOut=TRUE;
				bChkXor=TRUE;
				//pbChkXor[i]=pbChkOut[i]^bChkOut;
				//pbChkOut[i]=TRUE;
			}
			else if((!bChkIn)&&(pdwRetCnt[i]>=ptChkTab[i].dwRetCnt))
			{
				bChkOut=FALSE;
				bChkXor=TRUE;
				//pbChkXor[i]=pbChkOut[i]^bChkOut;
				//pbChkOut[i]=FALSE;
			}
			if(bChkXor)
			{
				pbChkOut[i]=bChkOut;
				// ����洢
				ptEvent=&g_tChkQueue.tEvent[g_tChkQueue.wWptr];
				ptEvent->wIndex = i;
				ptEvent->wState = bChkOut;
				if(ptChkTab->wValType1!=CN_NULL_PINNO)
				{
					pMeaValue=g_tChkState.tRecValue[i].iMeaValue;
					ptEvent->iMeaValue[0]= pMeaValue[0];
					ptEvent->iMeaValue[1]= pMeaValue[1];
					ptEvent->iMeaValue[2]= pMeaValue[2];
				}
				if(++g_tChkQueue.wWptr>=CN_NUM_RPT_CHK)
				{
					g_tChkQueue.wWptr=0;
				}
				if(g_tChkQueue.wWptr==g_tChkQueue.wRptr)
				{
					g_tChkQueue.wFlag=CN_RPT_FULL;
				}
			}
		}
		if(pbChkOut[i])
		{
			if(ptChkTab[i].wCfg&DB0)
			{
				bChkDo=TRUE;
			}
			if(ptChkTab[i].wCfg&DB1)
			{
				bChkBs=TRUE;
			}
		}
	}
	g_bFlag[EN_FLAG_CHK]=bChkDo;
	g_tagPub.bSysBs=bChkBs;
}
// ============================================================================
// �������ܣ�������ʼ��
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMRec_Para_Init()
{
	tagIES_IMRec     *pgtagIES_IMRec;
	register UINT32  i;
	const tagAlmTab *ptAlmTab;
	tagTimeRelay    *ptTimer;
	BOOL            *pbEna,*pbTimerEna;
	DWORD            dwActTime,dwRetTime;
	DWORD           *pdwPara;
	
	pgtagIES_IMRec = &gtagIES_IMRec;
	ptAlmTab=&g_tAlmTab[0];
	pdwPara =g_tagPara.dwPara;
	ptTimer =pgtagIES_IMRec->tTimer_Alm;
	pbEna   =pgtagIES_IMRec->bAlmEna;
	pbTimerEna=pgtagIES_IMRec->bAlmTimerEna;
	pgtagIES_IMRec->dwInit=TRUE;
	for(i=0;i<CN_NUM_ALM;i++)
	{
		if(ptAlmTab->wParaEna<CN_NUM_PARA)
		{
			*pbEna=pdwPara[ptAlmTab->wParaEna];
		}
		else
		{
			*pbEna=TRUE;
		}
		if(ptAlmTab->wParaTime<CN_NUM_PARA)
		{
			dwActTime=T(pdwPara[ptAlmTab->wParaTime]);
		}
		else if((ptAlmTab->dwDefTime==0)&&(ptAlmTab->dwRetTime==0))
		{
			pbTimerEna[i]=TRUE;
			dwActTime=0;
		}
		else
		{
			dwActTime=ptAlmTab->dwDefTime;
		}
		dwRetTime=ptAlmTab->dwRetTime;
		IES_TimeRelaySet(ptTimer, dwActTime, dwRetTime);
		ptAlmTab++;
		ptTimer++;
		pbEna++;
	}
#if 0
	ptChkTab=&g_tChkTab[0];
	pdwPara =g_tagPara.dwPara;
	ptTimer =pgtagIES_IMRec->tTimer_Chk;
	pbEna   =pgtagIES_IMRec->bChkEna;
	pgtagIES_IMRec->dwInit=TRUE;
	for(i=0;i<CN_NUM_CHK;i++)
	{
		if(ptChkTab->wParaEna<CN_NUM_PARA)
		{
			*pbEna=pdwPara[ptChkTab->wParaEna];
		}
		else
		{
			*pbEna=TRUE;
		}
		if(ptChkTab->wParaTime<CN_NUM_PARA)
		{
			dwActTime=pdwPara[ptChkTab->wParaTime];
		}
		else
		{
			dwActTime=ptChkTab->wDefTime;
		}
		dwRetTime=ptChkTab->wRetTime;
		IES_TimeRelaySet(ptTimer, dwActTime, dwRetTime);
		ptChkTab++;
		ptTimer++;
		pbEna++;
	}
#endif
	pgtagIES_IMRec->dwInit=FALSE;
}
// ============================================================================
// �������ܣ�����Ԫ���ϵ��ʼ��
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMRec_Init()
{
	IES_memset(&gtagIES_IMRec,0x0,sizeof(gtagIES_IMRec));
	IES_RamScanAdd(&gtagIES_IMRec.byRamScan1);
	IES_RamScanAdd(&gtagIES_IMRec.byRamScan2);
	IES_RamScanAdd(&gtagIES_IMRec.byRamScan3);
	IES_RamScanAdd(&gtagIES_IMRec.byRamScan4);
	IES_RamScanAdd(&gtagIES_IMRec.byRamScan5);
}

// ============================================================================
// �������ܣ�����Ԫ��������
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMRec()
{
	tagIES_IMRec     *pgtagIES_IMRec;
	pgtagIES_IMRec =  &gtagIES_IMRec;
	
	if(pgtagIES_IMRec->dwInit)
	{
		return;
	}
	// GOOSE������������
	IES_IMRec_Act(pgtagIES_IMRec);
	// �澯��������
	IES_IMRec_Alm(pgtagIES_IMRec);
	// �Լ���������
	if(G_Sys_Div4_3)
	{
		IES_IMRec_Chk(pgtagIES_IMRec);
	}
	// �ϵ��ʼ����λ
	pgtagIES_IMRec->dwPWInit=TRUE;
}

