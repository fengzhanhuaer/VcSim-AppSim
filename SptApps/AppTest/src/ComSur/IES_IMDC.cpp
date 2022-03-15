/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * ���ɵ��ӹɷ����޹�˾
 * Ԫ�����ƣ�ֱ��Ԫ��
 * Ԫ�����ܣ�ֱ��Ԫ��
 *     1.ֱ�����ݴ���
 *     2.ֱ������
 *     3.ֱ�����
 * Ԫ���汾��V1.00
 * ����ʱ�䣺2021-2-24
 * �汾�޸ģ�
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
 * V1.00 2021-2-24 ��־��������
 *================================================================================*/

#include "IES_IMDC.h"
// Ԫ���ӿڽṹ��
tagIES_IMDC      gtagIES_IMDC;

// ============================================================================
// �������ܣ�ֱ��ֱ������ת�����ݲ�ʹ�á�
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
BOOL IES_IMDC_Sam(tagIES_IMDC  *pgtagIES_IMDC)
{
	if(!g_tagDC.bDCFresh[EN_BOARD_DC_SAM])
	{
		return FALSE;
	}
	g_tagDC.bDCFresh[EN_BOARD_DC_SAM]=FALSE;
	register UINT16         i;                                       // ԭʼ����ָ��
	register INT32         *piSrc,*piDst,*piDstFst,*piDstCom,*piBak;
	register FLOAT32       *pfDst,*pfDstFst,*pfDstCom,*pfDcCoe;
	register INT32         *piAdjDc,*piAdjMin,*piAdjMax;
	register BOOL          *pbDCChg;
	register DWORD         *pdwDcTb;
	tagSamDcSet            *ptSamDcSet;
	// ��������
	piSrc     = &g_tagDC.iDCIn[EN_DC_SAM_STR];
	// �м��־
	piBak     = &pgtagIES_IMDC->iDCOutBak[EN_DC_SAM_STR];
	pfDcCoe   = &pgtagIES_IMDC->fDcCoe[EN_DC_SAM_STR];
	
	pdwDcTb   = &pgtagIES_IMDC->dwDcTb[0];
	ptSamDcSet= &pgtagIES_IMDC->tSamDcSet[0];
	// У׼�������
	piAdjDc   = &pgtagIES_IMDC->iAdjBuf[0];
	piAdjMin  = &pgtagIES_IMDC->iAdjMin[0];
	piAdjMax  = &pgtagIES_IMDC->iAdjMax[0];
	// �������ֵ
	piDst     = &g_tagDC.iDCOut[EN_DC_SAM_STR];
	pfDst     = &g_tagDC.fDCOut[EN_DC_SAM_STR];
	// ���һ��ֵ
	piDstFst  = &g_tagDC.iDCOutFst[0];
	pfDstFst  = &g_tagDC.fDCOutFst[0];
	// ���ͨ������,����GOOSE����
	piDstCom  = &g_tagDC.iDCOutCom[EN_DC_SAM_STR];
	pfDstCom  = &g_tagDC.fDCOutCom[EN_DC_SAM_STR];
	pbDCChg   = &g_tagDC.bDCChg[EN_DC_SAM_STR];

	for(i=EN_DC_SAM_STR;i<EN_DC_SAM_END;i++)
	{
		// �������ֵ
		*piDst   = (INT32)((*pfDcCoe)*(*piSrc));
		*pfDst   = (*piDst)*g_fDiv[CN_DC_DSP_SAM];
		// ���һ��ֵ(�ݶ�һ��ֵ����С����)
		*piDstFst  = (INT32)(ptSamDcSet->fDcK*(*piDst)) +(ptSamDcSet->iDcOfst);
		*pfDstFst  = (FLOAT32)(*piDstFst);
		// �Զ�У׼���
		if(pgtagIES_IMDC->bAdjStr)
		{
			*piAdjDc+=*piDst;
			if(*piDst<(*piAdjMin))
			{
				*piAdjMin=*piDst;
			}
			if(*piDst>(*piAdjMax))
			{
				*piAdjMax=*piDst;
			}
			piAdjDc++;
			piAdjMin++;
			piAdjMax++;
			if(i==(EN_DC_SAM_END-1))
			{
				if(++(pgtagIES_IMDC->wAdjPtr)>=pgtagIES_IMDC->wAdjNum)
				{
					pgtagIES_IMDC->bAdjStr=FALSE;
					pgtagIES_IMDC->bAdjEnd=TRUE;
					pgtagIES_IMDC->wAdjPtr=0;
				}
			}
		}
		// ��ʼ�ϵ���λ����,��ֹ����Ϊ0������
		if(abs(*piDst-*piBak)>(INT32)(*pdwDcTb))//||(!bPWInit))
		{
			// ����ֵ
			if(ptSamDcSet->bDcOutType)
			{
				*piDstCom=*piDst;
				*pfDstCom=*pfDst;
			}
			else
			// һ��ֵ
			{
				*piDstCom=*piDstFst;
				*pfDstCom=*pfDstFst;
			}
			*piBak  = *piDst;
			*pbDCChg=TRUE;
			
			g_tagDC.bDCGoOutFresh[EN_BOARD_DC_SAM]=TRUE;
			// �ݲ����Ǽ�¼��ǰʱ��
		}
		piSrc++;
		piBak++;
		pdwDcTb++;
		ptSamDcSet++;
		
		pfDcCoe++;
		
		piDst++;
		pfDst++;
		
		piDstFst++;
		pfDstFst++;
		
		piDstCom++;
		pfDstCom++;
		pbDCChg++;
	}
	g_tagDC.bDCDispFresh[EN_BOARD_DC_SAM]=TRUE;
	return TRUE;
}

// ============================================================================
// �������ܣ�װ�����߼������ת��(���Է�ʱ����)���ݲ�ʹ�á�
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
BOOL IES_IMDC_Dev(tagIES_IMDC  *pgtagIES_IMDC)
{
	// ȥ���ϵ��־�ж�,ֻ�жϸ��±�־
	//register BOOL           bPWInit;
	//bPWInit=pgtagIES_IMDC->dwPWInit;
	//if((!g_tagDC.bDCFresh[EN_BOARD_DC_DEV])&&(bPWInit))
	if(!g_tagDC.bDCFresh[EN_BOARD_DC_DEV])
	{
		// װ���¶ȼ��ڲ���ѹû�и��±�־,�ʹ̶�5s����һ������
		// ��if�ڽ��ж�ʱ��,��֤�¸��жϿ�ʼ���Խ������ݰ�佻��
		if(pgtagIES_IMDC->dwDevCnt++>CN_T5S)
		{
			pgtagIES_IMDC->dwDevCnt=0;
			g_tagDC.bDCFresh[EN_BOARD_DC_DEV]=TRUE;
		}
		return FALSE;
	}
	g_tagDC.bDCFresh[EN_BOARD_DC_DEV]=FALSE;
	register UINT16         i;               // ԭʼ����ָ��
	register INT32         *piSrc,*piDst,*piDstCom,*piBak;
	register FLOAT32       *pfDst,*pfDstCom,*pfDcCoe;
	register BOOL          *pbDCChg;
	const tagDCTab         *ptDCTab;
	register DWORD          dwDcTb;
	
	g_tagDC.bDCFresh[EN_BOARD_DC_DEV]=FALSE;
	// ������
	ptDCTab   = &g_tDCTab[EN_DC_DEV_STR];
	// ��������
	piSrc     = &g_tagDC.iDCIn[EN_DC_DEV_STR];
	// �м�����
	piBak     = &pgtagIES_IMDC->iDCOutBak[EN_DC_DEV_STR];
	pfDcCoe   = &pgtagIES_IMDC->fDcCoe[EN_DC_DEV_STR];
	// �������
	piDst     = &g_tagDC.iDCOut[EN_DC_DEV_STR];
	pfDst     = &g_tagDC.fDCOut[EN_DC_DEV_STR];
	// ���ͨ������,GOOSE����ʹ��
	piDstCom  = &g_tagDC.iDCOutCom[EN_DC_DEV_STR];
	pfDstCom  = &g_tagDC.fDCOutCom[EN_DC_DEV_STR];
	pbDCChg   = &g_tagDC.bDCChg[EN_DC_DEV_STR];
	
	for(i=EN_DC_DEV_STR;i<EN_DC_DEV_END;i++)
	{
		// ��ʱ�����ǵ�ѹ���¶ȡ�CRC��������
		if((ptDCTab->wType==EN_CTYPE_DC_H)
		||(ptDCTab->wType==EN_CTYPE_DC_CLK))
		{
			*piDst = *piSrc;
		}
		else
		{
			*piDst = (INT32)((*piSrc)*(*pfDcCoe));
			*pfDst = (FLOAT32)((*piDst)*g_fDiv[CN_DC_DSP_DEV]);
		}
#if 0
		switch(ptDCTab->wType)
		{
			case EN_CTYPE_DC_mA:
			case EN_CTYPE_DC_V:
			case EN_CTYPE_DC_T:
			case EN_CTYPE_DC_Hum:
				*piDst = (INT32)((*piSrc)*(*pfDcCoe));
				*pfDst = (FLOAT32)((*piDst)*g_fDiv[CN_DC_DSP_DEV]);
				break;
			case EN_CTYPE_DC_H:
				*piDst = (INT32)(*piSrc);
				break;
			default:
				break;
		}
#endif
		// װ��ֱ����Ϣ��ͻ�������̫��һ����,Ϊ���Ḻ�أ���ʱֱ�Ӷ�ȡ,Ŀǰû���뵽�õİ취����������
		dwDcTb=G_Get_PARA_I(ptDCTab->wParaIndex2);
		
		if(abs(*piDst-*piBak)>((INT32)dwDcTb))
		{
			*piDstCom=*piDst;
			*pfDstCom=*pfDst;
			*piBak   =*piDst;
			*pbDCChg =TRUE;
			g_tagDC.bDCGoOutFresh[EN_BOARD_DC_DEV]=TRUE;
			// �Ƿ��Ǽ�¼��ǰʱ��
		}
		ptDCTab++;
		piSrc++;
		piBak++;
		pfDcCoe++;
		piDst++;
		pfDst++;
		piDstCom++;
		pfDstCom++;
		pbDCChg++;
	}
	g_tagDC.bDCDispFresh[EN_BOARD_DC_DEV]=TRUE;

	return TRUE;
}


// ============================================================================
// �������ܣ�װ�ù⹦��ת�����ݲ�ʹ�á�
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
BOOL IES_IMDC_Opt(tagIES_IMDC  *pgtagIES_IMDC)
{
	register UINT16         i,wBoardNo;               // ԭʼ����ָ��
	register INT32         *piSrc,*piDst,*piDstCom,*piBak;
	register FLOAT32       *pfDst,*pfDstCom,*pfDcCoe;
	register BOOL          *pbDCChg;
	const tagDCTab         *ptDCTab;
	register DWORD          dwDcTb;
	register WORD           wIndexStr,wIndexEnd;
	
	// �ϵ�״̬,ˢ����������
	//if(!pgtagIES_IMDC->dwPWInit)
	//{
	//	g_tagDC.bDCFresh[EN_BOARD_DC_OPT1]=TRUE;
	//	g_tagDC.bDCFresh[EN_BOARD_DC_OPT1_2]=TRUE;
	//	g_tagDC.bDCFresh[EN_BOARD_DC_OPT2]=TRUE;
	//	g_tagDC.bDCFresh[EN_BOARD_DC_OPT3]=TRUE;
	//	g_tagDC.bDCFresh[EN_BOARD_DC_OPT4]=TRUE;
	//}
	// ÿ���жϽ�����һ���忨�⹦��
	if(g_tagDC.bDCFresh[EN_BOARD_DC_OPT1_1])
	{
		wIndexStr=EN_DC_OPT1_1_STR;
		wIndexEnd=EN_DC_OPT1_1_END;
		g_tagDC.bDCFresh[EN_BOARD_DC_OPT1_1]=FALSE;
		wBoardNo=EN_BOARD_DC_OPT1_1;
	}
	else if(g_tagDC.bDCFresh[EN_BOARD_DC_OPT1_2])
	{
		wIndexStr=EN_DC_OPT1_2_STR;
		wIndexEnd=EN_DC_OPT1_2_END;
		g_tagDC.bDCFresh[EN_BOARD_DC_OPT1_2]=FALSE;
		wBoardNo=EN_BOARD_DC_OPT1_2;
	}
	else if(g_tagDC.bDCFresh[EN_BOARD_DC_OPT2])
	{
		wIndexStr=EN_DC_OPT2_STR;
		wIndexEnd=EN_DC_OPT2_END;
		g_tagDC.bDCFresh[EN_BOARD_DC_OPT2]=FALSE;
		
		wBoardNo=EN_BOARD_DC_OPT2;
	}
	//else if(g_tagDC.bDCFresh[EN_BOARD_DC_OPT3])
	//{
	//	wIndexStr=EN_DC_OPT3_STR;
	//	wIndexEnd=EN_DC_OPT3_END;
	//	g_tagDC.bDCFresh[EN_BOARD_DC_OPT3]=FALSE;
	//	wBoardNo=EN_BOARD_DC_OPT3;
	//}
	//else if(g_tagDC.bDCFresh[EN_BOARD_DC_OPT4])
	//{
	//	wIndexStr=EN_DC_OPT4_STR;
	//	wIndexEnd=EN_DC_OPT4_END;
	//	g_tagDC.bDCFresh[EN_BOARD_DC_OPT4]=FALSE;
	//	wBoardNo=EN_BOARD_DC_OPT4;
	//}
	else
	{
		return FALSE;
	}
	// ������
	ptDCTab   = &g_tDCTab[wIndexStr];
	// ��������
	piSrc	  = &g_tagDC.iDCIn[wIndexStr];
	// �м�����
	piBak     = &pgtagIES_IMDC->iDCOutBak[wIndexStr];
	pfDcCoe   = &pgtagIES_IMDC->fDcCoe[wIndexStr];
	// �������
	piDst	  = &g_tagDC.iDCOut[wIndexStr];
	pfDst	  = &g_tagDC.fDCOut[wIndexStr];
	// ���ͨ������,GOOSE����ʹ��
	piDstCom  = &g_tagDC.iDCOutCom[wIndexStr];
	pfDstCom  = &g_tagDC.fDCOutCom[wIndexStr];
	pbDCChg   = &g_tagDC.bDCChg[wIndexStr];
	
	for(i=wIndexStr;i<wIndexEnd;i++)
	{
		// �⹦��
		if(ptDCTab->wType==EN_CTYPE_DC_DBM)
		{
			*piDst = (INT32)(log10((INT16)(*piSrc)*0.0001)*(*pfDcCoe));
		}
		// �¶�
		else if(ptDCTab->wType==EN_CTYPE_DC_OPTT)
		{
			*piDst = (INT32)(((INT16)(*piSrc))*(*pfDcCoe));
		}
		// ��ѹ
		else
		{
			*piDst = (INT32)(((UINT16)(*piSrc))*(*pfDcCoe));
		}
		*pfDst = (FLOAT32)((*piDst)*g_fDiv[CN_DC_DSP_DEV]);
		// װ��ֱ����Ϣ��ͻ�������̫��һ����,Ϊ���Ḻ�أ���ʱֱ�Ӷ�ȡ,Ŀǰû���뵽�õİ취����������
		dwDcTb=G_Get_PARA_I(ptDCTab->wParaIndex2);
		
		if(abs(*piDst-*piBak)>(INT32)dwDcTb)
		{
			*piDstCom=*piDst;
			*pfDstCom=*pfDst;
			*piBak = *piDst;
			*pbDCChg =TRUE;
			
			g_tagDC.bDCGoOutFresh[wBoardNo]=TRUE;
			// �Ƿ��Ǽ�¼��ǰʱ��
		}
		// �Ƿ���Խ���Լ�
		ptDCTab++;
		piSrc++;
		piBak++;
		pfDcCoe++;
		piDst++;
		pfDst++;
		piDstCom++;
		pfDstCom++;
		pbDCChg++;
	}
	
	g_tagDC.bDCDispFresh[wBoardNo]=TRUE;

	return TRUE;
}
// ============================================================================
// �������ܣ�ֱ��ֱ������ת��
// ���������
// ���������
// ����ֵ��  ��
// �����ط���,һ���жϽ�����һ������
// ============================================================================
BOOL IES_IMDC_Sam_S(tagIES_IMDC  *pgtagIES_IMDC)
{
	if(!g_tagDC.bDCFresh[EN_BOARD_DC_SAM])
	{
		return FALSE;
	}
	
	register WORD  i,j;
	register INT32   iDcDst;
	register tagSamDcSet      *ptSamDcSet;
	
	i=g_tagDC.wDCRefPtr[EN_BOARD_DC_SAM];
	
	if(i>=CN_NUM_DC_SAM)
	{
		g_tagDC.wDCRefPtr[EN_BOARD_DC_SAM]     =0;
		g_tagDC.bDCFresh[EN_BOARD_DC_SAM]       =FALSE;
		g_tagDC.bDCGoOutFresh[EN_BOARD_DC_SAM]  =TRUE;
		g_tagDC.bDCDispFresh[EN_BOARD_DC_SAM]   =TRUE;
		return FALSE;
	}
	ptSamDcSet= &pgtagIES_IMDC->tSamDcSet[i];
	
	j=EN_DC_SAM_STR+i;
	
	g_tagDC.iDCOut[j]=(INT32)((INT16)g_tagDC.iDCIn[j]*pgtagIES_IMDC->fDcCoe[j]);
	g_tagDC.fDCOut[j]=g_tagDC.iDCOut[j]*g_fDiv[CN_DC_DSP_SAM];
	// ���һ��ֵ
	g_tagDC.iDCOutFst[i]=(INT32)(ptSamDcSet->fDcK*(g_tagDC.iDCOut[j])) +(ptSamDcSet->iDcOfst);
	g_tagDC.fDCOutFst[i]=(FLOAT32)(g_tagDC.iDCOutFst[j])*g_fDiv[CN_DC_DSP_SAM];

	iDcDst=g_tagDC.iDCOut[j];

	// �Զ�У׼���
	if(pgtagIES_IMDC->bAdjStr)
	{
		pgtagIES_IMDC->iAdjBuf[i]+=iDcDst;
		if(iDcDst<(pgtagIES_IMDC->iAdjMin[i]))
		{
			pgtagIES_IMDC->iAdjMin[i]=iDcDst;
		}
		if(iDcDst>(pgtagIES_IMDC->iAdjMax[i]))
		{
			pgtagIES_IMDC->iAdjMax[i]=iDcDst;
		}
		if(i==(CN_NUM_DC_SAM-1))
		{
			if(++(pgtagIES_IMDC->wAdjPtr)>=pgtagIES_IMDC->wAdjNum)
			{
				pgtagIES_IMDC->bAdjStr=FALSE;
				pgtagIES_IMDC->bAdjEnd=TRUE;
				pgtagIES_IMDC->wAdjPtr=0;
			}
		}
	}
	if(abs(iDcDst-pgtagIES_IMDC->iDCOutBak[j])>(INT32)(pgtagIES_IMDC->dwDcTb[i]))
	{
		if(ptSamDcSet->bDcOutType)
		{
			g_tagDC.iDCOutCom[j]=g_tagDC.iDCOut[j];
			g_tagDC.fDCOutCom[j]=g_tagDC.fDCOut[j];
		}
		else
		// һ��ֵ
		{
			g_tagDC.iDCOutCom[j]=g_tagDC.iDCOutFst[i];
			g_tagDC.fDCOutCom[j]=g_tagDC.fDCOutFst[i];
		}
		pgtagIES_IMDC->iDCOutBak[j]=iDcDst;
		g_tagDC.bDCChg[j]=TRUE;
	}
	// �������
	g_tagDC.wDCRefPtr[EN_BOARD_DC_SAM]++;
	return TRUE;
}

// ============================================================================
// �������ܣ�װ�����߼������ת��(���Է�ʱ����)
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
BOOL IES_IMDC_Dev_S(tagIES_IMDC  *pgtagIES_IMDC)
{
	if(!g_tagDC.bDCFresh[EN_BOARD_DC_DEV])
	{
		// 16284�ж�����һ��
		if(G_Sys_Div16284_768)
		{
			g_tagDC.bDCFresh[EN_BOARD_DC_DEV]=TRUE;
			g_tagDC.bDCCommFresh[EN_BOARD_DC_DEV]=TRUE;
			g_tagDC.wDCRefPtr[EN_BOARD_DC_DEV]=0;
		}
		return FALSE;
	}
	
	register WORD i,j;
	register INT32   iDcDst;
	register UINT32   dwDcTb;
	i=g_tagDC.wDCRefPtr[EN_BOARD_DC_DEV];
	if(i>=CN_NUM_DC_DEV)
	{
		g_tagDC.wDCRefPtr[EN_BOARD_DC_DEV]     =0;
		g_tagDC.bDCFresh[EN_BOARD_DC_DEV]       =FALSE;
		g_tagDC.bDCGoOutFresh[EN_BOARD_DC_DEV]  =TRUE;
		g_tagDC.bDCDispFresh[EN_BOARD_DC_DEV]   =TRUE;
		return FALSE;
	}
	j=EN_DC_DEV_STR+i;
	if(g_tDCTab[j].wType==EN_CTYPE_DC_H)
	{
		g_tagDC.iDCOut[j] = g_tagDC.iDCIn[j];
	}
	else
	{
		g_tagDC.iDCOut[j]=g_tagDC.iDCIn[j]*pgtagIES_IMDC->fDcCoe[j];
		g_tagDC.fDCOut[j]=g_tagDC.iDCOut[j]*g_fDiv[CN_DC_DSP_DEV];
	}

	iDcDst=g_tagDC.iDCOut[j];
	
	dwDcTb=G_Get_PARA_I(g_tDCTab[j].wParaIndex2);

	if(abs(iDcDst-pgtagIES_IMDC->iDCOutBak[j])>(INT32)dwDcTb)
	{
		g_tagDC.iDCOutCom[j]=g_tagDC.iDCOut[j];
		g_tagDC.fDCOutCom[j]=g_tagDC.fDCOut[j];
		pgtagIES_IMDC->iDCOutBak[j]=iDcDst;
		g_tagDC.bDCChg[j]=TRUE;
	}
	// �������
	g_tagDC.wDCRefPtr[EN_BOARD_DC_DEV]++;
	return TRUE;
}

// ============================================================================
// �������ܣ�װ�ù⹦��ת��
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
BOOL IES_IMDC_Opt_S(tagIES_IMDC  *pgtagIES_IMDC)
{
	register UINT16         i,j,k;               // ԭʼ����ָ��
	register INT32         iDcDst;
	register DWORD          dwDcTb;
	register WORD           wIndexStr,wSrcIndexNum=0;
	for(k=EN_BOARD_DC_OPT_STR;k<EN_BOARD_DC_OPT_END;k++)
	{
		if(g_tagDC.bDCFresh[k])
		{
			wIndexStr=g_tBoardDCTab[k].wIndexStr;
			wSrcIndexNum=g_tBoardDCTab[k].wSrcIndexNum;
			break;
		}
	}
	if(k==EN_BOARD_DC_OPT_END)
	{
		return FALSE;
	}
	i=g_tagDC.wDCRefPtr[k];
	
	if(i>=wSrcIndexNum)
	{
		g_tagDC.wDCRefPtr[k]     =0;
		g_tagDC.bDCFresh[k]       =FALSE;
		g_tagDC.bDCGoOutFresh[k]  =TRUE;
		g_tagDC.bDCDispFresh[k]   =TRUE;
		return FALSE;
	}
	j=wIndexStr+i;
	if(g_tDCTab[j].wType==EN_CTYPE_DC_DBM)
	{
		g_tagDC.iDCOut[j] = (INT32)(log10((INT16)(g_tagDC.iDCIn[j])*0.0001)*pgtagIES_IMDC->fDcCoe[j]);
	}
	else if(g_tDCTab[j].wType==EN_CTYPE_DC_OPTT)
	{
		g_tagDC.iDCOut[j]=(INT32)((INT16)g_tagDC.iDCIn[j]*pgtagIES_IMDC->fDcCoe[j]);
	}
	else
	{
		g_tagDC.iDCOut[j]=(INT32)((UINT16)g_tagDC.iDCIn[j]*pgtagIES_IMDC->fDcCoe[j]);
	}
	g_tagDC.fDCOut[j]=g_tagDC.iDCOut[j]*g_fDiv[CN_DC_DSP_DEV];
	
	iDcDst=g_tagDC.iDCOut[j];
	
	dwDcTb=G_Get_PARA_I(g_tDCTab[j].wParaIndex2);

	if(abs(iDcDst-pgtagIES_IMDC->iDCOutBak[j])>(INT32)dwDcTb)
	{
		g_tagDC.iDCOutCom[j]=g_tagDC.iDCOut[j];
		g_tagDC.fDCOutCom[j]=g_tagDC.fDCOut[j];
		pgtagIES_IMDC->iDCOutBak[j]=iDcDst;
		g_tagDC.bDCChg[j]=TRUE;
	}
	// �������
	g_tagDC.wDCRefPtr[k]++;
	return TRUE;
}

// =============================================================================
// �������ܣ�ֱ��Ʒ��
// �����������
// �����������
// ����ֵ��  ��
// =============================================================================
void IES_IMDC_Q(tagIES_IMDC  *pgtagIES_IMDC)
{
	register UINT16   i;
	register UINT32   *pdwDCOutQ;
	register BOOL     *pbBoardErr,*pbBoardErrXor,*pbDCOutQChg;

	pdwDCOutQ  = &g_tagDC.dwDCOutQ[0];
	pbDCOutQChg= &g_tagDC.bDCOutQChg[0];
	// ���Ʒ��δ���ı�־(�Զ����)
	// ����Ʒ�ʸ���
	if(g_tagPub.bSysTestXor)
	{
		if(g_tagPub.bSysTest)
		{
			for(i=0;i<CN_NUM_BOARD_DC;i++)
			{
				pdwDCOutQ[i]|=CN_Go_Q_TEST;
				pbDCOutQChg[i] =TRUE;
			}
		}
		else
		{
			for(i=0;i<CN_NUM_BOARD_DC;i++)
			{
				pdwDCOutQ[i]&=(~CN_Go_Q_TEST);
				pbDCOutQChg[i] =TRUE;
			}
		}
	}
	// ֱ���忨�Լ�
	pbBoardErr     =&g_tChkState.bChkOut[EN_CHK_BOARD_DC_STR];
	pbBoardErrXor  =&g_tChkState.bChkXor[EN_CHK_BOARD_DC_STR];
	for(i=0;i<CN_NUM_BOARD_DC;i++)
	{
		// ����Ʒ��
		if(pbBoardErrXor[i])
		{
			// �忨�쳣,Ʒ����Ч
			if(pbBoardErr[i])
			{
				pdwDCOutQ[i]|=CN_Go_Q_VALIDL;
				pbDCOutQChg[i] =TRUE;
			}
			else
			{
				pdwDCOutQ[i]&=(~CN_Go_Q_VALIDL);
				pbDCOutQChg[i] =TRUE;
			}
		}
	}
}
// =============================================================================
// �������ܣ������Զ�У׼
// �����������
// �����������
// ����ֵ��  ��
// =============================================================================
BOOL IES_IMDC_AdJ_Str(WORD wAdjNum)
{
	tagIES_IMDC *ptag_IMDC;
	ptag_IMDC=&gtagIES_IMDC;
	// ���1000������
	if(wAdjNum>1000)
	{
		return TRUE;
	}
	// �Զ�У׼�м����ݳ�ʼ��
	ptag_IMDC->bAdjStr=FALSE;
	ptag_IMDC->bAdjEnd=FALSE;
	ptag_IMDC->wAdjPtr=0;
	ptag_IMDC->wAdjNum=wAdjNum;
	IES_memset(ptag_IMDC->iAdjMin,0x7F,sizeof(ptag_IMDC->iAdjMin));
	IES_memset(ptag_IMDC->iAdjMax,0x0, sizeof(ptag_IMDC->iAdjMax));
	IES_memset(ptag_IMDC->iAdjBuf,0x0, sizeof(ptag_IMDC->iAdjBuf));
	// �Զ�У׼������־һ���������(�˴�˳���ܱ䣡����)
	ptag_IMDC->bAdjStr=TRUE;
	
	return FALSE;
}

// =============================================================================
// �������ܣ��Զ�У׼������(���������е���)
// �����������
// �����������
// ����ֵ��0:ȫ��У׼ʧ��,dwAdjNo:dwAdjNo��ͨ��У׼�ɹ�,*pbChn:ÿ��ͨ����У׼״̬
// =============================================================================
UINT32 IES_IMDC_AdJ(BOOL *pbChn)
{
	WORD     i,wParaCoe,wParaIn,wAdjNum;
	DWORD    dwAdjNo=0,dwDDc,dwParaChg;
	INT32    iParaDef;
	FLOAT32  fCoe=0.0f;
	const    tagDCTab  *ptagDcTab;
	DWORD    *pdwPara, *pdwParaBak;
	tagIES_IMDC     *pgtagIES_IMDC;
	if(pbChn==NULL)
	{
		return dwAdjNo;
	}
	pgtagIES_IMDC = &gtagIES_IMDC;

	if(pgtagIES_IMDC->bAdjEnd)
	{
		pgtagIES_IMDC->bAdjEnd=FALSE;
		wAdjNum=pgtagIES_IMDC->wAdjNum;
		ptagDcTab  = &g_tDCTab[0];
		pdwPara    = &g_tagPara.dwPara[0];
		pdwParaBak = &g_tagPara.dwParaBak[0];
		// У׼
		for(i=EN_DC_SAM_STR;i<EN_DC_SAM_END;i++)
		{
			dwDDc = pgtagIES_IMDC->iAdjMax[i]-pgtagIES_IMDC->iAdjMin[i];
			wParaCoe =EN_PARA_DC_COE_STR+i;
			wParaIn  =ptagDcTab[i].wParaIndex1;
			// �ж��������� ��ѹ����
			if(pdwPara[wParaIn]!=1)
			{
				pbChn[i]=FALSE;
				continue;
			}
			// ��ѹ��ֵ�������ó���0.1V
			if(dwDDc<(g_dwMul[CN_DC_DIV_SAM]*0.1))
			{
				fCoe=(5.00f*wAdjNum*g_dwMul[CN_DC_DIV_SAM])/pgtagIES_IMDC->iAdjBuf[i];
			}
			else
			{
				pbChn[i]=FALSE;
				continue;
			}
			// У׼ϵ��Ĭ��ֵ
			iParaDef=g_tParaTab[wParaCoe].iValDft;
			dwParaChg=(UINT32)(fCoe*pdwPara[wParaCoe]);
			// ϵ��΢����Χ�ж�
			if(abs((INT32)dwParaChg- iParaDef)>(0.1f* iParaDef))
			{
			   pbChn[i]=FALSE;
			   continue;
			}
			pdwParaBak[wParaCoe] = dwParaChg;
			pbChn[i]=TRUE;
			dwAdjNo++;
		}
		// �������±�־
		//if(dwAdjNo)
		//{
		//	g_tagPara.dwChgWRef[EN_BOARD_PARA_DC]=TRUE;
		//}
		return dwAdjNo;
	}
	else
	{
		return 0;
	}
}
// ============================================================================
// �������ܣ�ֱ��Ԫ������ˢ��
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMDC_Para_Init()
{
	tagIES_IMDC     *pgtagIES_IMDC;
	const tagDCTab    *ptDCTab;
	register WORD     i;
	register DWORD    *pdwDcTb;
	tagSamDcSet       *ptSamDcSet;
	register FLOAT32  *pfDcCoe,fDcVtomACoe;
	register BOOL     bDcInType,bDcOutType;
	register FLOAT32  fDcMin,fDcMax,fDcOfst;
	pgtagIES_IMDC=&gtagIES_IMDC;

	pgtagIES_IMDC->dwInit=TRUE;
	// ֱ���������Խ���
	// ϵ������
	ptDCTab   = &g_tDCTab[EN_DC_SAM_STR];
	pfDcCoe   = &pgtagIES_IMDC->fDcCoe[EN_DC_SAM_STR];
	pdwDcTb   = &pgtagIES_IMDC->dwDcTb[0];
	ptSamDcSet= &pgtagIES_IMDC->tSamDcSet[0];
	fDcVtomACoe=pgtagIES_IMDC->fDcVtomACoe=g_tagPara.fPara[EN_PARA_DC_V_MA];
	for(i=EN_DC_SAM_STR;i<EN_DC_SAM_END;i++)
	{
		bDcInType  = G_Get_PARA_I(ptDCTab->wParaIndex1);
		bDcOutType = G_Get_PARA_I(ptDCTab->wParaIndex1+EN_GROUP_DC_OUT);
		fDcMin     = G_Get_PARA_F(ptDCTab->wParaIndex1+EN_GROUP_DC_MIN);
		fDcMax     = G_Get_PARA_F(ptDCTab->wParaIndex1+EN_GROUP_DC_MAX);
		fDcOfst    = G_Get_PARA_F(ptDCTab->wParaIndex1+EN_GROUP_DC_OFST);
		// һ��ֵ/����ֵ
		ptSamDcSet->bDcOutType=bDcOutType;
		// 0~5V
		if(bDcInType)
		{
			*pfDcCoe   = G_Get_PARA_F(EN_PARA_DC_COE_STR+i);
			ptSamDcSet->fDcK    =(fDcMax-fDcMin+fDcOfst)/(5-0)*g_dwMul[CN_DC_DSP_SAM]*g_fDiv[CN_DC_DIV_SAM];
			ptSamDcSet->iDcOfst =(INT32)((fDcMax-ptSamDcSet->fDcK*5.0)*g_dwMul[CN_DC_DSP_SAM]);
			*pdwDcTb=(DWORD)(G_Get_PARA_F(ptDCTab->wParaIndex2)*5.0*g_dwMul[CN_DC_DSP_SAM]*0.01);
		}
		// 4~20mA
		else
		{
			*pfDcCoe   = G_Get_PARA_F(EN_PARA_DC_COE_STR+i)*fDcVtomACoe;
			ptSamDcSet->fDcK    =(fDcMax-fDcMin+fDcOfst)/(20-4)*g_dwMul[CN_DC_DSP_SAM]*g_fDiv[CN_DC_DIV_SAM];
			ptSamDcSet->iDcOfst =(INT32)((fDcMax-ptSamDcSet->fDcK*20.0)*g_dwMul[CN_DC_DSP_SAM]);
			*pdwDcTb=(DWORD)(G_Get_PARA_F(ptDCTab->wParaIndex2)*20.0*g_dwMul[CN_DC_DSP_SAM]*0.01);
		}
		pfDcCoe++;
		ptDCTab++;
		pdwDcTb++;
		ptSamDcSet++;
	}
	// ͻ�����
	// �˴�����ʼ��һ��
	ptDCTab   = &g_tDCTab[EN_DC_DEV_STR];
	pfDcCoe   = &pgtagIES_IMDC->fDcCoe[EN_DC_DEV_STR];
	if(pgtagIES_IMDC->dwPWInit!=TRUE)
	{
		for(i=EN_DC_DEV_STR;i<EN_DC_END;i++)
		{
			switch(ptDCTab->wType)
			{
				case EN_CTYPE_DC_mA:
				case EN_CTYPE_DC_V:
				case EN_CTYPE_DC_T:
				case EN_CTYPE_DC_Hum:
					*pfDcCoe=g_dwMul[CN_DC_DSP_DEV]*g_fDiv[CN_DC_DIV_DEV];
					break;
				case EN_CTYPE_DC_OPTT:
					*pfDcCoe=g_dwMul[CN_DC_DSP_DEV]/256;
					break;
				case EN_CTYPE_DC_OPTV:
					*pfDcCoe=5.0*g_dwMul[CN_DC_DSP_DEV]/32767.00;
					break;
				case EN_CTYPE_DC_DBM:
					*pfDcCoe=g_dwMul[CN_DC_DSP_DEV]*10;
					break;
				case EN_CTYPE_DC_H:
					*pfDcCoe=1.0;
					break;
				default:
					*pfDcCoe=1.0;
					break;
			}
			pfDcCoe++;
			ptDCTab++;
		}
	}
}

// ============================================================================
// �������ܣ�ֱ��Ԫ���ϵ��ʼ��
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMDC_Init()
{
	// �����ʼ��
	IES_memset(&gtagIES_IMDC,0x0,sizeof(gtagIES_IMDC));
	IES_RamScanAdd(&gtagIES_IMDC.byRamScan1);
	IES_RamScanAdd(&gtagIES_IMDC.byRamScan2);
	IES_RamScanAdd(&gtagIES_IMDC.byRamScan3);
	IES_RamScanAdd(&gtagIES_IMDC.byRamScan4);
	IES_RamScanAdd(&gtagIES_IMDC.byRamScan5);
	IES_RamScanAdd(&gtagIES_IMDC.byRamScan6);
	IES_RamScanAdd(&gtagIES_IMDC.byRamScan7);
	IES_RamScanAdd(&gtagIES_IMDC.byRamScan8);
}

// ============================================================================
// �������ܣ�ֱ��Ԫ��������
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMDC()
{
	tagIES_IMDC     *pgtagIES_IMDC;
	pgtagIES_IMDC = &gtagIES_IMDC;
	// �������ж����޸�,����һ�μ���
	if(pgtagIES_IMDC->dwInit)
	{
		pgtagIES_IMDC->dwInit=FALSE;
		return;
	}
	// Ʒ�ʴ���
	if(g_iInter[EN_INTER_GOPUB_DC_Q])
	{
		IES_IMDC_Q(pgtagIES_IMDC);
	}
	// ��ʱ����(���ȼ���ռ)
	// ֱ�����ݽ��ռ�ת��
	IES_IMDC_Sam_S(pgtagIES_IMDC);
	// װ�����ݽ��ռ�ת��
	IES_IMDC_Dev_S(pgtagIES_IMDC);
	// ��ڹ���ת��
	IES_IMDC_Opt_S(pgtagIES_IMDC);
	// �ϵ��ʼ����λ
	pgtagIES_IMDC->dwPWInit=TRUE;
}

