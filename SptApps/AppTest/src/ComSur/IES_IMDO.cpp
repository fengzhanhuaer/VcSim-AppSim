/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * ���ɵ��ӹɷ����޹�˾
 * Ԫ�����ƣ�����Ԫ��
 * Ԫ�����ܣ�����Ԫ��
 *     1.Ӳ���ڿ���
 *     2.GOOSE��������
 *     3.ָʾ�ƿ���
 * Ԫ���汾��V1.00
 * ����ʱ�䣺2020-9-7
 * �汾�޸ģ�
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
 * V1.00 2021-2-24 ��־��������
 *================================================================================*/

#include "IES_IMDO.h"

// Ԫ���ӿڽṹ��
tagIES_IMDO      gtagIES_IMDO;
// ============================================================================
// �������ܣ�Ӳ���ڿ���
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMDO_Out(tagIES_IMDO  *pgtagIES_IMDO)
{
	register UINT32 i,j;
	register WORD  wSrcType;
	register WORD  wSrcIndex,wRtn1Index,wRtn0Index,wDoStrIndex,wDoNum;
	tagTimerRtn   *ptTimerRtn;
	DWORD    *pdwRtn1,*pdwRtn0;
	BOOL     *pbDoDst,*pbDoXor;
	BOOL     bDoDst,bDoRtn=FALSE;
	BOOL     *pBoard;
	const tagBoardIoTab   *ptBoardDOTab;
	const tagDoTab *ptDoTab;
	register tagSoeEvent  *ptEvent;
	ptBoardDOTab=g_tBoardDOTab;
	pdwRtn1     =pgtagIES_IMDO->dwRtn1;
	pdwRtn0     =pgtagIES_IMDO->dwRtn0;
	// ���ڱ���(�ϵ����||װ���ܱ���)
	if((!g_tagPub.bSysPower)||(g_tagPub.bSysBs))
	{
		pbDoDst =g_tagIO.bDOOut;
		pbDoXor =g_tagIO.bDOOutXor;
		ptTimerRtn=pgtagIES_IMDO->tTimerRtn;
		for(i=0;i<CN_NUM_DO_RTN;i++)
		{
			bDoDst=FALSE;
			pbDoXor[i]=pbDoDst[i]^bDoDst;
			ptTimerRtn[i].dwTimeRtn=0;
			// ��������
			if(pbDoXor[i])
			{
				pbDoDst[i]=bDoDst;
				// ��������
				ptEvent=&g_tDoQueue.tEvent[g_tDoQueue.wWptr];
				ptEvent->wIndex = i;
				ptEvent->wState = bDoDst;
				ptEvent->tTime  = g_tagPub.tSysTimeUTC;
				if((++g_tDoQueue.wWptr)>=CN_NUM_RPT_DO)
				{
					g_tDoQueue.wWptr=0;
				}
				if(g_tDoQueue.wWptr==g_tDoQueue.wRptr)
				{
					g_tDoQueue.wFlag=CN_RPT_FULL;
				}
			}
			
		}
		// װ�ù����������쳣
		bDoDst=CN_Get_Dat_Src(EN_DTYPE_FLAG,EN_FLAG_DO_ALM);
		pbDoXor[EN_DO_ALM]=pbDoDst[EN_DO_ALM]^bDoDst;
		// ��������
		if(pbDoXor[EN_DO_ALM])
		{
			pbDoDst[EN_DO_ALM]=bDoDst;
			ptEvent=&g_tDoQueue.tEvent[g_tDoQueue.wWptr];
			ptEvent->wIndex = EN_DO_ALM;
			ptEvent->wState = bDoDst;
			ptEvent->tTime  = g_tagPub.tSysTimeUTC;
			if((++g_tDoQueue.wWptr)>=CN_NUM_RPT_DO)
			{
				g_tDoQueue.wWptr=0;
			}
			if(g_tDoQueue.wWptr==g_tDoQueue.wRptr)
			{
				g_tDoQueue.wFlag=CN_RPT_FULL;
			}
		}
		bDoDst=CN_Get_Dat_Src(EN_DTYPE_FLAG,EN_FLAG_DO_CHK)
		pbDoXor[EN_DO_CHK]=pbDoDst[EN_DO_CHK]^bDoDst;
		// ��������
		if(pbDoXor[EN_DO_CHK])
		{
			pbDoDst[EN_DO_CHK]=bDoDst;
			ptEvent=&g_tDoQueue.tEvent[g_tDoQueue.wWptr];
			ptEvent->wIndex = EN_DO_CHK;
			ptEvent->wState = bDoDst;
			ptEvent->tTime  = g_tagPub.tSysTimeUTC;
			if((++g_tDoQueue.wWptr)>=CN_NUM_RPT_DO)
			{
				g_tDoQueue.wWptr=0;
			}
			if(g_tDoQueue.wWptr==g_tDoQueue.wRptr)
			{
				g_tDoQueue.wFlag=CN_RPT_FULL;
			}
		}
		if(g_tagPub.bSysBs)
		{
			g_tAlmState.bAlmIn[EN_ALM_BS_DO]=TRUE;
		}
		return;
	}
	g_tAlmState.bAlmIn[EN_ALM_BS_DO]=FALSE;
	
	// ����״̬
	for(i=0;i<CN_NUM_BOARD_DO;i++,ptBoardDOTab++)
	{
		wDoStrIndex=ptBoardDOTab->wIndexStr;
		wDoNum    =ptBoardDOTab->wSrcIndexNum;
		ptDoTab   =&g_tDoTab[wDoStrIndex];
		pbDoDst   =&g_tagIO.bDOOut[wDoStrIndex];
		pbDoXor   =&g_tagIO.bDOOutXor[wDoStrIndex];
		ptTimerRtn=&pgtagIES_IMDO->tTimerRtn[wDoStrIndex];
		for(j=0;j<wDoNum;j++)
		{
			wSrcType  = ptDoTab->wSrcType;
			wSrcIndex = ptDoTab->wSrcIndex;
			bDoDst=CN_Get_Dat_Src(wSrcType,wSrcIndex);
			// �з�У�ж�
			if(ptDoTab->wRtnIndex<CN_NUM_DI)
			{
				bDoRtn=TRUE;
			}
			else
			{
				bDoRtn=FALSE;
			}
			//�б�λ
			*pbDoXor=*pbDoDst^bDoDst;
			if(*pbDoXor)
			{
				*pbDoDst=bDoDst;
				// ������У
				if(bDoRtn)
				{
					ptTimerRtn->bStrEna=TRUE;
					ptTimerRtn->dwTimeRtn=0;
				}
				// ��������
				{
					ptEvent=&g_tDoQueue.tEvent[g_tDoQueue.wWptr];
					ptEvent->wIndex = wDoStrIndex+j;
					ptEvent->wState = bDoDst;
					ptEvent->tTime  = g_tagPub.tSysTimeUTC;
					if((++g_tDoQueue.wWptr)>=CN_NUM_RPT_DO)
					{
						g_tDoQueue.wWptr=0;
					}
					if(g_tDoQueue.wWptr==g_tDoQueue.wRptr)
					{
						g_tDoQueue.wFlag=CN_RPT_FULL;
					}
				}
			}
			// �з�У�жϣ�Ŀǰ��û�п����Լ��Զ����ص�����
			// Ŀǰ��ʱû�п����ϵ��Լ���߼�
			if(bDoRtn)
			{
				if(ptTimerRtn->bStrEna)
				{
					if((ptTimerRtn->dwTimeRtn++)<pgtagIES_IMDO->dwDoRtnT)
					{
						if(*pbDoDst==G_Get_DI(ptDoTab->wRtnIndex))
						{
							ptTimerRtn->bStrEna=FALSE;
							ptTimerRtn->dwTimeRtn=0;
							if(*pbDoDst)
							{
								*pdwRtn1&=(~g_dwBit[j]);
							}
							else
							{
								*pdwRtn0&=(~g_dwBit[j]);
							}
						}
					}
					else
					{
						ptTimerRtn->bStrEna=FALSE;
						ptTimerRtn->dwTimeRtn=0;
						
						if(*pbDoDst)
						{
							*pdwRtn1|=g_dwBit[j];
						}
						else
						{
							*pdwRtn0|=g_dwBit[j];
						}
					}
				}
			}
			ptDoTab++;
			pbDoDst++;
			pbDoXor++;
			ptTimerRtn++;
		}
		pdwRtn1++;
		pdwRtn0++;
	}
	// �����Լ�
	pdwRtn1     =pgtagIES_IMDO->dwRtn1;
	pdwRtn0     =pgtagIES_IMDO->dwRtn0;
	pBoard      =&g_tChkState.bChkIn[EN_CHK_BOARD_DO1];
	wRtn1Index  =EN_CHK_DO_RTN1_STR;
	wRtn0Index  =EN_CHK_DO_RTN0_STR;
	for(i=0;i<CN_NUM_BOARD_DO_RTN;i++)
	{
		if(pBoard[i])
		{
			G_Clr_ChkIn(wRtn0Index+i);
			G_Clr_ChkIn(wRtn1Index+i);
			*pdwRtn1=0;
			*pdwRtn0=0;
		}
		else
		{
			if(*pdwRtn1)
			{
				G_Set_ChkIn_All(wRtn1Index+i,*pdwRtn1,0,0);
			}
			else
			{
				G_Clr_ChkIn(wRtn1Index+i);
			}
			if(*pdwRtn0)
			{
				G_Set_ChkIn_All(wRtn0Index+i,*pdwRtn0,0,0);
			}
			else
			{
				G_Clr_ChkIn(wRtn0Index+i);
			}
		}
		pdwRtn1++;
		pdwRtn0++;
	}
	
}
// ============================================================================
// �������ܣ�GOOSE������λ
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMDO_GoOut()
{
	register UINT32 i;
	register WORD  wSrcType;
	register WORD  wSrcIndex;
	register tagTimeUTC  *ptTimeUTC;//,*ptTimeUTCSrc;
	register BOOL    *pbGoOutDst,*pbGoOutXor,*pbGoOutCom;
	register BOOL     bGoOutDst;
	register UINT32   *pdwGoOutQ;
	const tagGoOutTab *ptGoOutTab;
	register tagSoeEvent  *ptEvent;
	ptGoOutTab  =g_tGoOutTab;
	pbGoOutDst  =g_tagIO.bGoOut;
	pbGoOutCom  =g_tagIO.bGoOutCom;
	pbGoOutXor  =g_tagIO.bGoOutXor;
	ptTimeUTC   =g_tagIO.tGoOutT;
	
	for(i=0;i<CN_NUM_GOOUT;i++)
	{
		wSrcType    = ptGoOutTab->wSrcType;
		wSrcIndex   = ptGoOutTab->wSrcIndex;
		bGoOutDst=CN_Get_Dat_Src(wSrcType,wSrcIndex);
		bGoOutDst|=pbGoOutCom[i];
		pbGoOutXor[i]=(pbGoOutDst[i]^bGoOutDst);

		// ʱ�����
		if(pbGoOutXor[i])
		{
			pbGoOutDst[i]=bGoOutDst;
			// Դʱ��(Ӳ����)
			if(wSrcType==EN_DTYPE_DI)
			{
				ptTimeUTC[i]=G_Get_DI_UTC(wSrcIndex);
			}
			// ����ʱ��
			//else if(i==EN_GOOUT_TIME_RECV)
			//{
			//	ptTimeUTC[i]=g_tagIO.tGoInUTCRev;
			//}
			// ����ʱ��
			else
			{
				ptTimeUTC[i]=g_tagPub.tSysTimeUTC;
			}
			// ��������
			{
				ptEvent=&g_tGoOutQueue.tEvent[g_tGoOutQueue.wWptr];
				ptEvent->wIndex = i;
				ptEvent->wState = bGoOutDst;
				ptEvent->tTime  = ptTimeUTC[i];
				if((++g_tGoOutQueue.wWptr)>=CN_NUM_RPT_GOOUT)
				{
					g_tGoOutQueue.wWptr=0;
				}
				if(g_tGoOutQueue.wWptr==g_tGoOutQueue.wRptr)
				{
					g_tGoOutQueue.wFlag=CN_RPT_FULL;
				}
			}
		}
		ptGoOutTab++;
	}
	// ��ʱ���������Ʒ��
	if(g_iInter[EN_INTER_GOPUB_OUT_Q])
	{
		pdwGoOutQ   =g_tagIO.dwGoOutQ;
		if(g_tagPub.bSysTestXor)
		{
			if(g_tagPub.bSysTest)
			{
				for(i=0;i<CN_NUM_GOOUT;i++)
				{
					pdwGoOutQ[i]|=CN_Go_Q_TEST;
				}
			}
			else
			{
				for(i=0;i<CN_NUM_GOOUT;i++)
				{
					pdwGoOutQ[i]&=(~CN_Go_Q_TEST);
				}
			}
		}
	}
}
// ============================================================================
// �������ܣ�LED����λ���ݲ�ʹ�á�
// ���������
// ���������
// ����ֵ��  ��
// ��ʱ��ʹ��32λ�����
// ============================================================================
void IES_IMDO_Led()
{
	register UINT32 i;
	register WORD  wSrcType;
	register WORD  wSrcIndex;
	BOOL    *pbLedDst;
	BOOL     bLedDst;
	const tagLedTab *ptLedTab;
	ptLedTab  =&g_tLedTab[0];
	pbLedDst  =&g_tagIO.bLedOut[0];
	for(i=0;i<CN_NUM_LED;i++)
	{
		wSrcType  = ptLedTab->wSrcType;
		wSrcIndex = ptLedTab->wSrcIndex;
		bLedDst=CN_Get_Dat_Src(wSrcType,wSrcIndex);
		pbLedDst[i]=bLedDst;
		ptLedTab++;
	}
}
// ============================================================================
// �������ܣ�LED����λ
// ���������
// ���������
// ����ֵ��  ��
// ���Ḻ��,ÿ���ж�ֻ����һ����
// ============================================================================
void IES_IMDO_Led_S()
{
	register BYTE  byLedPtr;
	byLedPtr=g_tagIO.byLedPtr;
	// �ۼӷ���ǰ��,��ֹ��ţ���
	if((++byLedPtr)>=CN_NUM_LED)
	{
		byLedPtr=0;
	}
	g_tagIO.bLedOut[byLedPtr]=CN_Get_Dat_Src(g_tLedTab[byLedPtr].wSrcType,g_tLedTab[byLedPtr].wSrcIndex);
	g_tagIO.bLedOut[byLedPtr]|=g_tagIO.bLedOutCom[byLedPtr];

	//  ָʾ�Ʊ����߼�
	if(g_tLedTab[byLedPtr].bHld)
	{
		// ���ֱ�־��ֵ
		if(g_tagIO.bLedOut[byLedPtr])
		{
			g_tagIO.bLedOutHld[byLedPtr]=g_tagIO.bLedOut[byLedPtr];
		}
		// ���ֱ�־����
		else if(g_tagPub.bSysReset)
		{
			g_tagIO.bLedOutHld[byLedPtr]=FALSE;
		}
		g_tagIO.bLedOut[byLedPtr]|=g_tagIO.bLedOutHld[byLedPtr];
	}
	g_tagIO.byLedPtr=byLedPtr;
}
// ============================================================================
// �������ܣ�����Ԫ��������ʼ��
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMDO_Para_Init()
{
	tagIES_IMDO     *pgtagIES_IMDO;
	pgtagIES_IMDO = &gtagIES_IMDO;
	pgtagIES_IMDO->dwDoRtnT=T(g_tagPara.dwPara[EN_PARA_T_DO_RTN]);
}
// ============================================================================
// �������ܣ�����Ԫ���ϵ��ʼ��
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMDO_Init()
{
	IES_memset(&gtagIES_IMDO,0x0,sizeof(gtagIES_IMDO));
	IES_RamScanAdd(&gtagIES_IMDO.byRamScan1);
	IES_RamScanAdd(&gtagIES_IMDO.byRamScan2);
	IES_RamScanAdd(&gtagIES_IMDO.byRamScan3);
	IES_RamScanAdd(&gtagIES_IMDO.byRamScan4);
}
// ============================================================================
// �������ܣ�����Ԫ��������
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMDO()
{
	tagIES_IMDO     *pgtagIES_IMDO;
	pgtagIES_IMDO = &gtagIES_IMDO;
	
	if(pgtagIES_IMDO->dwInit)
	{
		pgtagIES_IMDO->dwInit=FALSE;
		return;
	}
	// Ӳ�������ݴ���
	IES_IMDO_Out(pgtagIES_IMDO);
	// GOOSE��������
	IES_IMDO_GoOut();
	// LED��������
	IES_IMDO_Led_S();
	// �ϵ��ʼ����λ
	pgtagIES_IMDO->dwPWInit=TRUE;
}

