/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * ���ɵ��ӹɷ����޹�˾
 * Ԫ�����ƣ�DIԪ��
 * Ԫ�����ܣ�DIԪ��
 *     1.Ӳ���봦���߼�
 *     2.Ӳ����˫��ϳ�
 *     3.GOOSE���봦��
 *     4.�ϳɿ��봦��
 * Ԫ���汾��V1.00
 * ����ʱ�䣺2021-2-24
 * �汾�޸ģ�
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
 * V1.00 2021-2-24 ��־��������
 *================================================================================*/

#include "IES_IMDI.h"
// Ԫ���ӿڽṹ��
tagIES_IMDI      gtagIES_IMDI;
// ============================================================================
// �������ܣ���������ˢ��
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMDI_In(tagIES_IMDI  *pgtagIES_IMDI)
{
	register UINT32 i;
	register DWORD  *pdwSrc, *pdwDst, *pdwXorDst;
	pdwSrc    =g_tagIO.dwDIIn;
	pdwDst    =pgtagIES_IMDI->dwDIBuf;
	pdwXorDst =pgtagIES_IMDI->dwDIXor;
	
	for(i=0;i<CN_NUM_BOARD_DI;i++)
	{
		// ״̬����
		*pdwXorDst++ =(*pdwDst)^(*pdwSrc);
		*pdwDst++    =*pdwSrc++;
	}
}
// ============================================================================
// �������ܣ���һ֡ˢ�� ����������
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMDI_Fst(tagIES_IMDI  *pgtagIES_IMDI)
{
	// ״̬ˢ��
	register UINT32   i,j,k;
	register DWORD   *pdwDst,*pdwDIXor,*pdwHld;
	register DWORD    dwDIHld;
	register tagTimeUTC  *ptTimeUTC,*ptFpgaUTC,*ptDpiUTC;
	register BOOL    *pbHld,bDpiOve,*pbDpiOve;
	const tagDpiTab  *ptDpiTab;
	const tagBoardIoTab *ptBoardDITab;
	// ��һ֡ ����������
	if(pgtagIES_IMDI->dwPWInit==FALSE)
	{
		// �м����
		pdwDst      = pgtagIES_IMDI->dwDIBuf;
		pdwDIXor    = pgtagIES_IMDI->dwDIXor;
		ptFpgaUTC   = g_tagIO.tDIInUTC;
		//�������
		ptTimeUTC   = g_tagIO.tDIHldUTC;
		pdwHld      = g_tagIO.dwDIHldIn32;
		pbHld       = g_tagIO.bDIHldIn;
		ptBoardDITab= g_tBoardDITab;
		// ����״̬����
		for(i=0;i<CN_NUM_BOARD_DI;i++)
		{
			dwDIHld=pdwHld[i]=pdwDst[i];
			pdwDIXor[i]=0;
			// �������Լ��ڳ�ʼ���Ѿ�����,�˴��ݲ��ٽ����Լ�
			for(j=ptBoardDITab->wIndexStr,k=0;j<ptBoardDITab->wIndexEnd;j++,k++)
			{
				ptTimeUTC[j]=ptFpgaUTC[i];

				if(dwDIHld&g_dwBit[k])
				{
					pbHld[j]=TRUE;
				}
				else
				{
					pbHld[j]=FALSE;
				}
			}
			ptBoardDITab++;
		}
		// ˫��Ӳ����״̬����
		ptDpiTab  = g_tDpiTab;
		ptDpiUTC  = g_tagIO.tDpiUTC;
		pbDpiOve  = g_tagIO.byDpiIn;
		ptTimeUTC = g_tagIO.tDIHldUTC;
		for(i=0;i<CN_NUM_DPI;i++)
		{
			if(ptDpiTab[i].wSrcType==EN_DTYPE_DI)
			{
				bDpiOve =(pbHld[ptDpiTab->wSrcOpn]?1:0);
				bDpiOve+=(pbHld[ptDpiTab->wSrcCls]?2:0);
				pbDpiOve[i]=bDpiOve;
				// ȡ��λ����λʱ�����
				ptDpiUTC[i]=ptTimeUTC[ptDpiTab->wSrcOpn];
			}
			else
			{
				continue;
			}
		}
	}
}
// ============================================================================
// �������ܣ���Դ�����߼�
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMDI_Pow(tagIES_IMDI  *pgtagIES_IMDI)
{
	// ״̬ˢ��
	register UINT32   i,j;
	register DWORD   *pdwDst,*pdwDIXor,*pdwHld,*pdwDIHldFlg,*pdwDIHldCnt;
	register DWORD    dwDIHld,dwDst;
	const tagBoardIoTab  *ptBoardDITab;
	register WORD     wPowBitNum;
	register DWORD    dwDIPWErr;

	// �м����
	pdwDst      = pgtagIES_IMDI->dwDIBuf;
	pdwDIXor    = pgtagIES_IMDI->dwDIXor;
	
	dwDIPWErr   = pgtagIES_IMDI->dwDIPWErr;
	pdwDIHldFlg = pgtagIES_IMDI->dwDIHldFlg;
	pdwDIHldCnt = pgtagIES_IMDI->dwDIHldCnt;
	
	ptBoardDITab= g_tBoardDITab;
	// �������
	pdwHld      = g_tagIO.dwDIHldIn32;
	// ң�ŵ�Դ����Ͷ��
	for(i=0;i<CN_NUM_BOARD_DI_DI;i++)
	{
		if(pgtagIES_IMDI->bYXPowEna[i])
		{
			dwDIHld=pdwHld[i];
			dwDst  =*pdwDst;
			wPowBitNum=ptBoardDITab->wPowBitNum;
			// ��ң�ŵ�Դ���ӹ���,ֱ������
			if(wPowBitNum<ptBoardDITab->wSrcIndexNum)
			{
				// ң�ŵ�Դ�����쳣�߼�
				if(!(dwDIHld&g_dwBit[wPowBitNum]))
				{
					if(!(dwDIPWErr&g_dwBit[i]))
					{
						dwDIPWErr|=g_dwBit[i];
						// ������־����
						for(j=ptBoardDITab->wIndexStr;j<ptBoardDITab->wIndexEnd;j++)
						{
							pdwDIHldFlg[j] = CN_HLD_RD;
							pdwDIHldCnt[j] = 0;
						}
					}
				}
				else
				{
					dwDIPWErr&=(~g_dwBit[i]);
				}
				// ң�ŵ�Դ�쳣,ң��λ�ñ���ʧ��ǰ״̬,����λ�������仯
				if(dwDIPWErr&g_dwBit[i])
				{
					*pdwDst=(dwDst&g_dwBit[wPowBitNum])+(dwDIHld&(~g_dwBit[wPowBitNum]));
					*pdwDIXor=(*pdwDIXor)&g_dwBit[wPowBitNum];
				}
			}
			else
			{
				dwDIPWErr&=(~g_dwBit[i]);
			}
		}
		else
		{
			dwDIPWErr&=(~g_dwBit[i]);
		}
		pdwDst++;
		ptBoardDITab++;
		pdwDIXor++;
	}
	
	pgtagIES_IMDI->dwDIPWErr=dwDIPWErr;
	
	if(dwDIPWErr)
	{
		G_Set_AlmIn_All(EN_ALM_DIPOW, TRUE,dwDIPWErr,0,0);
	}
	else
	{
		g_tAlmState.bAlmIn[EN_ALM_DIPOW]=FALSE;
	}
}
// ============================================================================
// �������ܣ�CPU�����
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMDI_HldCpu(tagIES_IMDI  *pgtagIES_IMDI)
{
	// ״̬ˢ��
	register UINT32   i,j,k;
	register DWORD   *pdwDst,*pdwDIXor,*pdwHld,*pdwHldXor;
	register DWORD   dwDst,dwDIXor,dwDIHld,dwDIHldXor,dwDIHldXor32;
	register DWORD   dwBit;
	register tagTimeUTC  *ptTimeUTC,*ptTimeUTCF,*ptFpgaUTC;//*ptTimeUTCB,
	
	register BOOL    *pbHld;
	register DWORD   *pdwDIHldFlg,*pdwDIHldCnt,*pdwDIFdTime,*pdwDIQrTime,dwDIHldFlg;
	const tagBoardIoTab    *ptBoardDITab;
	register tagSoeEvent  *ptEvent;
	// �м����
	pdwDst      = pgtagIES_IMDI->dwDIBuf;
	pdwDIXor    = pgtagIES_IMDI->dwDIXor;
	pdwDIHldFlg = pgtagIES_IMDI->dwDIHldFlg;
	pdwDIHldCnt = pgtagIES_IMDI->dwDIHldCnt;
	pdwDIFdTime = pgtagIES_IMDI->dwDIFdTime;
	pdwDIQrTime = pgtagIES_IMDI->dwDIQrTime;
	ptTimeUTCF  = pgtagIES_IMDI->tDITimeUTCF;
	//ptTimeUTCB  = pgtagIES_IMDI->tDITimeUTCB;
	
	ptFpgaUTC   = g_tagIO.tDIInUTC;
	//�������
	ptTimeUTC   = g_tagIO.tDIHldUTC;
	pdwHld      = g_tagIO.dwDIHldIn32;
	pdwHldXor   = g_tagIO.dwDIHldXor32;
	pbHld       = g_tagIO.bDIHldIn;
	
	ptBoardDITab= g_tBoardDITab;
	// 
	for(i=0;i<CN_NUM_BOARD_DI;i++)
	{
		dwDst   = pdwDst[i];
		dwDIXor = pdwDIXor[i];
		dwDIHld = pdwHld[i];
		dwDIHldXor = dwDst^dwDIHld;
		dwDIHldXor32=0;
		for(j=ptBoardDITab->wIndexStr,k=0;j<ptBoardDITab->wIndexEnd;j++,k++)
		{
			dwDIHldFlg=pdwDIHldFlg[j];
			dwBit=g_dwBit[k];
			// ȥ������
			if(dwDIHldFlg==CN_HLD_FD)
			{
				if(++pdwDIHldCnt[j]>=pdwDIFdTime[j])
				{
					pdwDIHldFlg[j] = CN_HLD_QR;
					pdwDIHldCnt[j] = 0;
				}
				continue;
			}
			// ȷ�Ϲ���
			else if(dwDIHldFlg==CN_HLD_QR)
			{
				if(dwDIHldXor&dwBit)
				{
					if(++pdwDIHldCnt[j]>=pdwDIQrTime[j])
					{
						pdwDIHldFlg[j]=CN_HLD_RD;
						pdwDIHldCnt[j]=0;
						// ��¼������ʱ��
						//ptTimeUTCB[j]=ptFpgaUTC[i];
						// ����ǰ������ѡ��
						// �������ǰʱ��
						ptTimeUTC[j]=ptTimeUTCF[j];
						// ���·�����״̬
						if(dwDst&dwBit)
						{
							pbHld[j] = TRUE;
							pdwHld[i]|=dwBit;
							
						}
						else
						{
						
							pbHld[j]= FALSE;
							pdwHld[i]&=(~dwBit);
						}
						// ���±�λ״̬
						dwDIHldXor32|=dwBit;
						// ��������
						{
							ptEvent=&g_tDiQueue.tEvent[g_tDiQueue.wWptr];
							ptEvent->wIndex = j;
							ptEvent->wState = pbHld[j];
							ptEvent->tTime  = ptTimeUTC[j];
							if((++g_tDiQueue.wWptr)>=CN_NUM_RPT_DI)
							{
								g_tDiQueue.wWptr=0;
							}
							if(g_tDiQueue.wWptr==g_tDiQueue.wRptr)
							{
								g_tDiQueue.wFlag=CN_RPT_FULL;
							}
						}
					}
				}
				else
				{
					pdwDIHldFlg[j]=CN_HLD_RD;
					pdwDIHldCnt[j]=0;
				}
				continue;
			}
			// ������ɺ�״̬
			else
			{
				if(dwDIXor&dwBit)
				{
					pdwDIHldFlg[j]=(pdwDIFdTime[j])?CN_HLD_FD:CN_HLD_QR;
					pdwDIHldCnt[j]=0;
					// ��¼����ǰʱ��
					ptTimeUTCF[j]=ptFpgaUTC[i];
				}
			}
		}
		pdwHldXor[i]=dwDIHldXor32;
		ptBoardDITab++;
	}
	// ȫ�ּ���״̬���
	g_tagPub.bSysTest     =pbHld[EN_DI_TEST];
	if(!pgtagIES_IMDI->dwPWInit)
	{
		g_tagPub.bSysTestXor  =g_tagPub.bSysTest;//�ϵ��һ֡
	}
	else
	{
		g_tagPub.bSysTestXor  =(pdwHldXor[EN_DI_TEST>>5]&g_dwBit[EN_DI_TEST&0x1f])?TRUE:FALSE;
	}
}
// ============================================================================
// �������ܣ�GOOSE�����Լ�
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMDI_Go_Chk(tagIES_IMDI  *pgtagIES_IMDI)
{
	register UINT32      i;
	register BOOL        bTestErrA,bTestErrB,bCfgErr,bCfgEna;
	register BOOL        bTestErrHld=FALSE,bDatErrHld=FALSE,bCfgErrHld=FALSE,bCfgEnaHld=FALSE;
	register BOOL        *pbTestErrA,*pbTestErrB;
	register UINT32     *pdwStatusA,*pdwStatusB,*pdwSubStatus;
	register UINT32      dwStatusA,dwStatusB,dwSubStatus;
	// �������
	pdwSubStatus =g_tagIO.dwGoInSubStatus;
	pdwStatusA   =g_tagIO.dwGoInStatusA;
	pdwStatusB   =g_tagIO.dwGoInStatusB;
	pbTestErrA   =pgtagIES_IMDI->bTestErrA;
	pbTestErrB   =pgtagIES_IMDI->bTestErrB;
	
	// �澯��Ϣ ����
	for(i=0;i<g_tagIO.byGoCbSubNum;i++)
	{
		dwStatusA  =pdwStatusA[i];
		dwStatusB  =pdwStatusB[i];
		dwSubStatus=pdwSubStatus[i];
		bTestErrA=FALSE;
		bTestErrB=FALSE;
		// ���ƿ�����쳣
		if(dwSubStatus)
		{
			bCfgErrHld=bCfgErr=TRUE;
		}
		else
		{
			bCfgErr=FALSE;
		}
		// ���ƿ���ʹ��
		if((dwStatusA&CN_GOCB_Ena)==0)
		{
			bCfgEnaHld=bCfgEna=TRUE;
			pbTestErrA[i]=FALSE;
		}
		else
		{
			bCfgEna=FALSE;
			// A���޲�һ���ж�
			if(!(dwStatusA&CN_GOCB_LinkErr1))
			{
				bTestErrA=pbTestErrA[i]=((dwStatusA&CN_GOCB_Test)&&(!g_tagPub.bSysTest));
			}
			// AGOOSE����+�����쳣�����澯�߼�(�Ǽ��޲�һ��״̬)
			if((dwStatusA&CN_GOCB_DataAlm)&&(!pbTestErrA[i]))
			{
				bDatErrHld=TRUE;
			}
		}
		if(dwStatusB&CN_GOCB_Ena)
		{
			// B���޲�һ���ж�
			if(!(dwStatusB&CN_GOCB_LinkErr1))
			{
				bTestErrB=pbTestErrB[i]=((dwStatusB&CN_GOCB_Test)&&(!g_tagPub.bSysTest));
			}
			// BGOOSE����+�����쳣�����澯�߼�(�Ǽ��޲�һ��״̬)
			if((dwStatusB&CN_GOCB_DataAlm)&&(!pbTestErrB[i]))
			{
				bDatErrHld=TRUE;
			}
		}
		else
		{
			pbTestErrB[i]=FALSE;
		}
		// ���޲�һ�¸澯
		if(bTestErrA|bTestErrB)
		{
			bTestErrHld=TRUE;
			G_Set_AlmIn_All(EN_ALM_GOCB_TEST_STR+i,TRUE,dwSubStatus,dwStatusA,dwStatusB);
		}
		else
		{
			g_tAlmState.bAlmIn[EN_ALM_GOCB_TEST_STR+i]=FALSE;
		}
		// �����쳣�澯
		if(((dwStatusA|dwStatusB)&CN_GOCB_DataAlm)||bCfgEna||bCfgErr)
		{
			G_Set_AlmIn_All(EN_ALM_GOCB_DATA_STR+i,TRUE,dwSubStatus,dwStatusA,dwStatusB);
		}
		else
		{
			g_tAlmState.bAlmIn[EN_ALM_GOCB_DATA_STR+i]=FALSE;
		}
		// ����籩�澯
		if((dwStatusA|dwStatusB)&CN_GOCB_Storm)
		{
			G_Set_AlmIn_All(EN_ALM_GOCB_STORM_STR+i,TRUE,dwSubStatus,dwStatusA,dwStatusB);
		}
		else
		{
			g_tAlmState.bAlmIn[EN_ALM_GOCB_STORM_STR+i]=FALSE;
		}
	}
	g_tAlmState.bAlmIn[EN_ALM_GOOSE_TEST]=bTestErrHld;
	g_tAlmState.bAlmIn[EN_ALM_GOOSE]=bDatErrHld|bCfgErrHld|bCfgEnaHld|g_iInter[EN_INTER_GOSUB_CFG]|g_iInter[EN_INTER_GOPUB_CFG];
}

// ============================================================================
// �������ܣ�GOOSE��λ
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMDI_Go(tagIES_IMDI  *pgtagIES_IMDI)
{
	register UINT32      i;
	register BOOL        *pbGoIn,*pbGoInXor,*pbGoInSub,*pbGoInValid,*pbGoInValidXor;
	register BOOL         bGoInValid;
	register WORD        *pwSrcQ,wSrcQ;
	register BYTE        *pbyGoInInValid;
	register tagSoeEvent *ptEvent;
	// �������
	pwSrcQ           =g_tagIO.wGoInQ;
	pbGoInSub        =g_tagIO.byGoInSub;
	// �������
	pbGoIn           =g_tagIO.bGoIn;
	pbGoInXor        =g_tagIO.bGoInXor;
	pbGoInValid      =g_tagIO.bGoInValid;
	pbGoInValidXor   =g_tagIO.bGoInValidXor;
	pbyGoInInValid   =g_tagIO.byGoInInValid;

	for(i=0;i<CN_NUM_GOIN;i++)
	{
		// �ź�δ����,��������Ч�ж�
		//if(!pbGoInSub[i])
		//{
		//	pbGoInValid[i]        = FALSE;
		//	pbGoInValidXor[i]     = FALSE;
		//	pbyGoInInValid[i]     = EN_INVAILD_NO;
		//}
		//else
		if(pbGoInSub[i])
		{
			wSrcQ  =pwSrcQ[i];
			// ��������
			if(pbGoInXor[i])
			{
				ptEvent=&g_tGoInQueue.tEvent[g_tGoInQueue.wWptr];
				ptEvent->wIndex = i;
				ptEvent->wState = pbGoIn[i];
				ptEvent->wQ     = wSrcQ;
				ptEvent->tTime  = g_tagPub.tSysTimeUTC;
				if((++g_tGoInQueue.wWptr)>=CN_NUM_RPT_GOIN)
				{
					g_tGoInQueue.wWptr=0;
				}
				if(g_tGoInQueue.wWptr==g_tGoInQueue.wRptr)
				{
					g_tGoInQueue.wFlag=CN_RPT_FULL;
				}
				// �����λ��־,
				pbGoInXor[i]=FALSE;
			}
			// ���޲�һ��
			if(((wSrcQ&CN_GOIN_Test)?TRUE:FALSE)^g_tagPub.bSysTest)
			{
				bGoInValid=FALSE;
				pbyGoInInValid[i]=EN_INVAILD_TEST;
			}
			else if(wSrcQ&CN_GOIN_Link)
			{
				bGoInValid=FALSE;
				pbyGoInInValid[i]=EN_INVAILD_LINK;
			}
			else if(wSrcQ&CN_GOIN_Invalid)
			{
				bGoInValid=FALSE;
				pbyGoInInValid[i]=EN_INVAILD_Q;
			}
			else if(wSrcQ&CN_GOIN_DataErr)
			{
				bGoInValid=FALSE;
				pbyGoInInValid[i]=EN_INVAILD_DATA;
			}
			else
			{
				bGoInValid=pbGoIn[i];
				pbyGoInInValid[i]=EN_INVAILD_NO;
			}
			pbGoInValidXor[i]=pbGoInValid[i]^bGoInValid;
			pbGoInValid[i]=bGoInValid;
		}
	}
}
// ============================================================================
// �������ܣ�˫��λ�úϳ�
// ���������
// ���������
// ����ֵ��  ��
// ��ʱ������GOOSE����ת˫��
// ============================================================================
void IES_IMDI_Dpi(tagIES_IMDI  *pgtagIES_IMDI)
{
	register UINT32   i;
	
	register BOOL   *pbHldIn;//,*pbGoInValid;
	register BOOL   bOpn,bCls;
	register BOOL   bDpiOve,bDpiXor;
	register BOOL   *pbDpiOve,*pbDpiXor;
	register tagTimeUTC *ptTimeUTC;//,*ptDIHldUTC,*ptGoInUTC;
	register tagTimeUTC *ptDpiUTC;
	const    tagDpiTab  *ptDpiTab;
	
	register tagSoeEvent  *ptEvent;
	// �������
	pbHldIn   = g_tagIO.bDIHldIn;
	ptTimeUTC = g_tagIO.tDIHldUTC;
	// ������
	ptDpiTab  = g_tDpiTab;
	// �������
	pbDpiOve  = g_tagIO.byDpiIn;
	pbDpiXor  = g_tagIO.byDpiInXor;
	ptDpiUTC  = g_tagIO.tDpiUTC;
	
	// �ޱ�λ����
	
	for(i=0;i<CN_NUM_DPI;i++)
	{
		bOpn=pbHldIn[ptDpiTab->wSrcOpn];
		bCls=pbHldIn[ptDpiTab->wSrcCls];
		
		bDpiOve = (bOpn?DB0:0);
		bDpiOve+= (bCls?DB1:0);
		
		bDpiXor=(pbDpiOve[i])^bDpiOve;
		pbDpiXor[i]=bDpiXor;
		
		if(bDpiXor)
		{
			// ����״̬
			pbDpiOve[i]=bDpiOve;
			// ����ʱ���Ʒ��
			if(bDpiXor&DB0)
			{
				ptDpiUTC[i]=ptTimeUTC[ptDpiTab->wSrcOpn];
				
			}
			else
			{
				ptDpiUTC[i]=ptTimeUTC[ptDpiTab->wSrcCls];
			}
			// ��������
			{
				ptEvent=&g_tDpiQueue.tEvent[g_tDpiQueue.wWptr];
				ptEvent->wIndex = i;
				ptEvent->wState = bDpiOve;
				ptEvent->tTime=ptDpiUTC[i];
				if(++g_tDpiQueue.wWptr>=CN_NUM_RPT_DPI)
				{
					g_tDpiQueue.wWptr=0;
				}
				if(g_tDpiQueue.wWptr==g_tDpiQueue.wRptr)
				{
					g_tDpiQueue.wFlag=CN_RPT_FULL;
				}
			}
		}
		ptDpiTab++;
	}
}
// ============================================================================
// �������ܣ�ң��Ʒ�ʴ���
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMDI_Q(tagIES_IMDI  *pgtagIES_IMDI)
{
	register UINT32   i,j;
	BOOL  bPowChg=FALSE,bPow;
	BOOL  *pbBoardErr,*pbBoardErrXor;
	WORD  wIndexPow;
	DWORD *pdwDIQ,*pdwDpiQ;
	const tagBoardIoTab  *ptagBoardIoTab;
	const tagDpiTab  *ptDpiTab;
	// �������
	pdwDIQ  = g_tagIO.dwDIQ;

	// ���ޱ�λ
	if(g_tagPub.bSysTestXor)
	{
		if(g_tagPub.bSysTest)
		{
			for(i=0;i<CN_NUM_DI;i++,pdwDIQ++)
			{
				*pdwDIQ|=CN_Go_Q_TEST;
			}
		}
		else
		{
			for(i=0;i<CN_NUM_DI;i++,pdwDIQ++)
			{
				*pdwDIQ&=(~CN_Go_Q_TEST);
			}
		}
		g_tagIO.dwDIQChg=TRUE;
	}
	// ��ЧƷ��
	ptagBoardIoTab =g_tBoardDITab;
	pbBoardErr     =&g_tChkState.bChkOut[EN_CHK_BOARD_DI_STR];
	pbBoardErrXor  =&g_tChkState.bChkXor[EN_CHK_BOARD_DI_STR];
	for(i=0;i<CN_NUM_BOARD_DI;i++,ptagBoardIoTab++)
	{
		wIndexPow=ptagBoardIoTab->wIndexStr+ptagBoardIoTab->wPowBitNum;
		if(wIndexPow>=CN_NUM_DI)
		{
			bPowChg= FALSE;
			bPow   =TRUE;
		}
		else if(!pgtagIES_IMDI->bYXPowEna[i])
		{
			if(!pgtagIES_IMDI->bYXPowEnaRef[i])
			{
				bPowChg=TRUE;
				pgtagIES_IMDI->bYXPowEnaRef[i]=TRUE;
			}
			bPow      = TRUE;
		}
		else
		{
			bPowChg   = (g_tagIO.dwDIHldXor32[wIndexPow>>5]&g_dwBit[wIndexPow&0x1f])?TRUE:FALSE;
			bPow      = g_tagIO.bDIHldIn[wIndexPow];
			pgtagIES_IMDI->bYXPowEnaRef[i]=FALSE;
		}
		// �忨�쳣
		if((pbBoardErrXor[i])||(bPowChg))
		{
		
			pdwDIQ= &g_tagIO.dwDIQ[ptagBoardIoTab->wIndexStr];
			
			if((!pbBoardErr[i])&&(bPow))
			{
				for(j=ptagBoardIoTab->wIndexStr;j<ptagBoardIoTab->wIndexEnd;j++,pdwDIQ++)
				{
					*pdwDIQ&=(~CN_Go_Q_VALIDL);
				}
			}
			else
			{
				for(j=ptagBoardIoTab->wIndexStr;j<ptagBoardIoTab->wIndexEnd;j++,pdwDIQ++)
				{
					*pdwDIQ|=CN_Go_Q_VALIDL;
				}
			}
			g_tagIO.dwDIQChg=TRUE;
		}
	}
	if(g_tagIO.dwDIQChg)
	{
		pdwDIQ  = g_tagIO.dwDIQ;
		pdwDpiQ = g_tagIO.dwDpiQ;
		ptDpiTab= g_tDpiTab;
		for(i=0;i<CN_NUM_DPI;i++)
		{
			pdwDpiQ[i]=(G_Get_DI_Q(ptDpiTab->wSrcOpn))|(G_Get_DI_Q(ptDpiTab->wSrcCls));
			ptDpiTab++;
		}
	}
}

// ============================================================================
// �������ܣ��������ˢ��
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================

void IES_IMDI_Para_Init()
{
	// ���·���ʱ��
	
	tagIES_IMDI     *pgtagIES_IMDI;
	const tagBoardIoTab  *ptagBoardIoTab;
	register DWORD  *pdwPara,dwPara;
	register DWORD  *pdwDIFdTime,*pdwDIQrTime;
	register WORD   i,j;
	register BOOL   bParaErr=FALSE;
	
	pgtagIES_IMDI =&gtagIES_IMDI;
	// �����쳣�˳���������
	if(g_tChkState.bChkIn[EN_CHK_PARA_DI])
	{
		pgtagIES_IMDI->dwBs=TRUE;
		return;
	}
	else
	{
		pgtagIES_IMDI->dwBs=FALSE;
	}
	pdwPara       =g_tagPara.dwPara;
	pdwDIFdTime   =pgtagIES_IMDI->dwDIFdTime;
	pdwDIQrTime   =pgtagIES_IMDI->dwDIQrTime;
	pgtagIES_IMDI->dwInit=TRUE;
	// ����ʱ��
	for(i=0;i<CN_NUM_DI;i++)
	{
		dwPara=pdwPara[i];
		if(dwPara>=CN_MS_T_20MS)
		{
			pdwDIFdTime[i]=T(dwPara-CN_MS_T_10MS);
			pdwDIQrTime[i]=CN_T10MS;
		}
		else if(dwPara>=CN_MS_T_10MS)
		{
			pdwDIFdTime[i]=T(dwPara-CN_MS_T_5MS);
			pdwDIQrTime[i]=CN_T5MS;
		}
		else if(dwPara>=CN_MS_T_5MS)
		{
			pdwDIFdTime[i]=T(dwPara-CN_MS_T_3MS);
			pdwDIQrTime[i]=CN_T3MS;
		}
		else
		{
			pdwDIFdTime[i]=T(dwPara);
			pdwDIQrTime[i]=0;
		}
	}
	ptagBoardIoTab=g_tBoardDITab;
	// ��Դ����Ͷ�˸���
	for(i=0;i<CN_NUM_BOARD_DI_DI;i++,ptagBoardIoTab++)
	{
		pgtagIES_IMDI->bYXPowEna[i]=G_Get_PARA_I(ptagBoardIoTab->wParaIndex);
		// ���ӷ���ʱ���Լ�
		if(pgtagIES_IMDI->bYXPowEna[i])
		{
			dwPara=G_Get_PARA_I(ptagBoardIoTab->wPowBitNum+ptagBoardIoTab->wIndexStr);
			
			for(j=ptagBoardIoTab->wIndexStr;j<ptagBoardIoTab->wIndexEnd;j++)
			{
				if(G_Get_PARA_I(j)<dwPara)
				{
					bParaErr=TRUE;
				}
			}
		}
	}
	// ȥ��ʱ�����ô����Լ�
	if(bParaErr)
	{
		G_Set_ChkIn(EN_CHK_PARA_DI_HLD);
	}
	else
	{
		G_Clr_ChkIn(EN_CHK_PARA_DI_HLD);
	}
}

// ============================================================================
// �������ܣ�����Ԫ���ϵ��ʼ��
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMDI_Init()
{
	IES_memset(&gtagIES_IMDI,0x0,sizeof(gtagIES_IMDI));
	
	IES_RamScanAdd(&gtagIES_IMDI.byRamScan1);
	IES_RamScanAdd(&gtagIES_IMDI.byRamScan2);
	IES_RamScanAdd(&gtagIES_IMDI.byRamScan3);
	IES_RamScanAdd(&gtagIES_IMDI.byRamScan4);
	IES_RamScanAdd(&gtagIES_IMDI.byRamScan5);
	IES_RamScanAdd(&gtagIES_IMDI.byRamScan6);
	IES_RamScanAdd(&gtagIES_IMDI.byRamScan7);
	IES_RamScanAdd(&gtagIES_IMDI.byRamScan8);
	IES_RamScanAdd(&gtagIES_IMDI.byRamScan9);
	IES_RamScanAdd(&gtagIES_IMDI.byRamScan10);
	IES_RamScanAdd(&gtagIES_IMDI.byRamScan11);
	IES_RamScanAdd(&gtagIES_IMDI.byRamScan12);
	IES_RamScanAdd(&gtagIES_IMDI.byRamScan13);
}
// ============================================================================
// �������ܣ�����Ԫ��������
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMDI()
{
	tagIES_IMDI     *pgtagIES_IMDI;
	pgtagIES_IMDI = &gtagIES_IMDI;
	// �����޸ı���һ�δ���
	if(pgtagIES_IMDI->dwInit)
	{
		pgtagIES_IMDI->dwInit=FALSE;
		return;
	}
	// ����ˢ��(Ӳ���롢GOOSE����)
	IES_IMDI_In(pgtagIES_IMDI);
	// ˢ�µ�һ֡����
	if(!pgtagIES_IMDI->dwPWInit)
	{
		IES_IMDI_Fst(pgtagIES_IMDI);
		// ������ʼ�����±�־
		g_tagIO.byDIFstToSoe=TRUE;
		g_tagIO.byDIFstToGoose=TRUE;		
		g_tagIO.byDpiFstToSoe=TRUE;
		g_tagIO.byDpiFstToGoose=TRUE;
	}
	// ң�ŵ�Դ���Ӵ���
	IES_IMDI_Pow(pgtagIES_IMDI);
	// Ӳ����CPU����
	IES_IMDI_HldCpu(pgtagIES_IMDI);
	// GOOSE�Լ�
	IES_IMDI_Go_Chk(pgtagIES_IMDI);
	// GOOSE����
	IES_IMDI_Go(pgtagIES_IMDI);
	// ���뵥��ϳ�˫��
	IES_IMDI_Dpi(pgtagIES_IMDI);
	// ң��Ʒ�ʴ���
	if(g_iInter[EN_INTER_GOPUB_DI_Q]
	||g_iInter[EN_INTER_GOPUB_DPI_Q])
	{
		IES_IMDI_Q(pgtagIES_IMDI);
	}
	// �ϵ��ʼ����λ
	pgtagIES_IMDI->dwPWInit=TRUE;
}

