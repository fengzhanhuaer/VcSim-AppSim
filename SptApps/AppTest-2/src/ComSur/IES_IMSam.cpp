/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * ���ɵ��ӹɷ����޹�˾
 * Ԫ�����ƣ�����Ԫ��
 * Ԫ������������Ԫ��
 * Ԫ�����ܣ����������������㼰���
 * Ԫ���汾��V1.00
 * ����ʱ�䣺2020-2-24
 * �汾�޸ģ�
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���> 
 * V1.00 2021-2-24 ��־��������
 *================================================================================*/
#include "IES_IMSam.h"
/*================================================================================*/
// Ԫ��˽�б�������
tag_IMSam     gtag_IMSam;
// ============================================================================
// �궨�庯�����ܣ���ֵʵ�鲿����
// ============================================================================
#define IES_CAL_AmpSqrt(iRe, iIm)  sqrt((INT64)iRe*iRe + (INT64)iIm*iIm)
// ============================================================================
// �궨�幦�ܣ�����ʵ�鲿�������,��Χ0.000��360.000��
// ============================================================================
#define IES_CAL_Angle(iRe,iIm)  (iIm >= 0)?(atan2(iIm,iRe)*180000/3.14159265):(360000+(atan2(iIm,iRe)*180000/3.14159265));
// =============================================================================
// �������ܣ�ʵʱ�����Լ�
// �����������
// �����������
// ����ֵ��  ��
// =============================================================================
BOOL IES_IMSam_Chk(tag_IMSam *ptag_IMSam)
{
	// ֡��������ж�
	if(g_tagAna.dwAnaFramDNum>1)
	{
		ptag_IMSam->dwJumpCnt++;
	}
	// ��֡�ж�
	else if(g_tagAna.dwAnaFramDNum==0)
	{
		ptag_IMSam->dwLostCnt++;
		return TRUE;
	}
	return FALSE;
}

// =============================================================================
// �������ܣ�ʵʱ����ˢ��(����һ��ֵ)
// �����������
// �����������
// ����ֵ��  ��
// =============================================================================
void IES_IMSam_In(tag_IMSam *ptag_IMSam)
{
	if(!ptag_IMSam->bAdjDcStr)
	{
		return;
	}
	register INT32 *piSam,iSam;
	register UINT32 i;
	
	piSam      =&(g_tagAna.iAnaSam[0]);
	
	for(i=0;i<CN_NUM_SAM;i++)
	{
		// ����AD��
		iSam=piSam[i];
		ptag_IMSam->iAdjDcBuf[i]+=iSam;
		if(iSam<ptag_IMSam->iAdjDcMin[i])
		{
			ptag_IMSam->iAdjDcMin[i]=iSam;
		}
		if(iSam>ptag_IMSam->iAdjDcMax[i])
		{
			ptag_IMSam->iAdjDcMax[i]=iSam;
		}
		if(i==(CN_NUM_SAM-1))
		{
			ptag_IMSam->wAdjDcPtr++;
			if(ptag_IMSam->wAdjDcPtr>=ptag_IMSam->wAdjDcNum)
			{
				ptag_IMSam->bAdjDcStr=FALSE;
				ptag_IMSam->wAdjDcPtr=0;
				ptag_IMSam->bAdjDcEnd=TRUE;
			}
		}
	}
}
// =============================================================================
// �������ܣ���׼��ѹ����
// �����������
// �����������
// ����ֵ��  ��
// =============================================================================
void IES_IMSam_JZ(tag_IMSam *ptag_IMSam)
{
	register tagVector *ptVector;
	register UINT32    i;
	register INT32     *piBuf,*piDcInBuf;
	register UINT32    dwBuf;
	register BOOL      *pbJzChk;
	register UINT32    dwJz1MkMin,dwJz1MkMax;
	register UINT32    dwJz2MkMin,dwJz2MkMax;
	// һ��ֵ����
	piBuf    =&(g_tagAna.iAnaSam[EN_ANA_JZ_STR]);
	ptVector =&(g_tagAna.tAnaVect[EN_ANA_JZ_STR]);
	pbJzChk  =&(ptag_IMSam->bJzChk[0]);
	piDcInBuf=&g_tagDC.iDCIn[CN_DC_INDEX_V];
	
	dwJz1MkMin=ptag_IMSam->dwJz1MkMin;
	dwJz1MkMax=ptag_IMSam->dwJz1MkMax;
	dwJz2MkMin=ptag_IMSam->dwJz2MkMin;
	dwJz2MkMax=ptag_IMSam->dwJz2MkMax;

	for(i=0;i<CN_NUM_JZ;i++,ptVector++)
	{
		dwBuf=(UINT32)(piBuf[i]);
		if((dwBuf<dwJz1MkMax)&&(dwBuf>dwJz1MkMin))
		{
			pbJzChk[i]=FALSE;
		}
		else if((dwBuf<dwJz2MkMax)&&(dwBuf>dwJz2MkMin))
		{
			pbJzChk[i]=FALSE;
		}
		else
		{
			pbJzChk[i]=TRUE;
		}
		ptVector->dwAm=dwBuf;
		ptVector->dwAmJ=dwBuf;
		piDcInBuf[i]=dwBuf;
	}
}
// =============================================================================
// �������ܣ���������
// �����������
// �����������
// ����ֵ��  ��
// =============================================================================
void IES_IMSam_Cal(tag_IMSam *ptag_IMSam)
{
	INT64   *piReal,*piImag;          // ʵ�����鲿
	UINT64   *pdwAm;                  // ��ֵ
	register  INT32    *piBuf,iBuf;             // ����
	register  DWORD     dwPtr;                   // ָ��
	register  UINT32     i;
#if(CN_HUM_ENA)	
	INT64   *piHumReal,*piHUmImag;    // г��ʵ�����鲿
	register  DWORD     dwHumPtr;                // ָ��
	register  UINT32     j;
#endif
	piReal  =&(ptag_IMSam->iAnaReal[0]);
	piImag  =&(ptag_IMSam->iAnaImag[0]);
	pdwAm   =&(ptag_IMSam->dwAnaAm[0]);
	piBuf   =&(g_tagAna.iAnaSam[0]);
	dwPtr   =ptag_IMSam->dwAnaPtr;

	for(i=0;i<CN_NUM_SAM;i++)
	{
		iBuf=*piBuf++;
		//������������
		*piReal+=(iBuf*g_iCos80[dwPtr]);
		*piImag+=(-iBuf*g_iSin80[dwPtr]);
		 piReal++;
		 piImag++;
	#if(CN_HUM_ENA)
		//2~13��г������
		piHumReal=&ptag_IMSam->iAnaHumReal[i][2];
		piHUmImag=&ptag_IMSam->iAnaHumImag[i][2];
		for(j=2;j<CN_HUM_NUM;j++)
		{
			dwHumPtr=(dwPtr*j)%CN_SAM_RATE;
			*piHumReal+=(iBuf*g_iCos80[dwHumPtr]);
			*piHUmImag+=(-iBuf*g_iSin80[dwHumPtr]);
			piHumReal++;
			piHUmImag++;
		}
	#endif
		//���ּ���(�������,ֱ�ӳ�ϵ��)
		*pdwAm+=(((INT64)iBuf)*((INT64)iBuf));
		 pdwAm++;
	}
#if(CN_SV_IN_ENA)	
	piReal  =&(ptag_IMSam->iAnaReal[EN_ANA_SV_STR]);
	piImag  =&(ptag_IMSam->iAnaImag[EN_ANA_SV_STR]);
	pdwAm   =&(ptag_IMSam->dwAnaAm[EN_ANA_SV_STR]);
	piBuf   =&(g_tagAna.iAnaSam[EN_ANA_SV_STR]);

	for(i=EN_ANA_SV_STR;i<EN_ANA_SV_END;i++)
	{
		iBuf=*piBuf++;
		//������������
		*piReal+=(iBuf*g_iCos80[dwPtr]);
		*piImag+=(-iBuf*g_iSin80[dwPtr]);
		 piReal++;
		 piImag++;
	#if(CN_HUM_ENA)
		//2~13��г������
		piHumReal=&ptag_IMSam->iAnaHumReal[i][2];
		piHUmImag=&ptag_IMSam->iAnaHumImag[i][2];
		for(j=2;j<CN_HUM_NUM;j++)
		{
			dwHumPtr=(dwPtr*j)%CN_SAM_RATE;
			*piHumReal+=(iBuf*g_iCos80[dwHumPtr]);
			*piHUmImag+=(-iBuf*g_iSin80[dwHumPtr]);
			piHumReal++;
			piHUmImag++;
		}
	#endif
		//���ּ���(�������,ֱ�ӳ�ϵ��)
		*pdwAm+=(((INT64)iBuf)*((INT64)iBuf));
		 pdwAm++;
	}
#endif
	if((++dwPtr)>=CN_SAM_RATE)
	{
		dwPtr=0;
		ptag_IMSam->dwWaveFlag=TRUE;
	}
	ptag_IMSam->dwAnaPtr=dwPtr;
}
// =============================================================================
// �������ܣ���������
// �����������
// �����������
// ����ֵ��  ��
// ���͸���,��ʱȥ���ż�����
// =============================================================================
void IES_IMSam_Fr(tag_IMSam *ptag_IMSam)
{
	register UINT32     i;
	register WORD       wIndex=0;
	register INT32     *piBuf,*piBufBak,iBuf,iBufBak;    // ����
	register UINT32    *pdwFCnt,*pdwFBc,dwFBc,*pdwFCal,*pdwFDly;
	register UINT32    *pdwPara;
	UINT32     dwAmJ;
	tagVector  *ptVector;
	const tagCalTab  *ptCalTab;
	piBuf    =&(g_tagAna.iAnaSam[0]);
	piBufBak =&(g_tagAna.iAnaSamBak[0]);
	pdwFBc   =&(ptag_IMSam->dwFBc[0]);
	pdwFCal  =&(ptag_IMSam->dwFCal[0]);
	pdwFCnt  =&(ptag_IMSam->dwFCnt[0]);
	pdwFDly  =&(ptag_IMSam->dwFDly[0]);
	pdwPara  =&(g_tagPara.dwPara[0]);
	ptVector =&(g_tagAna.tAnaVect[0]);
	ptCalTab =&g_tCalTab[0];
	
	for(i=0;i<CN_NUM_CAL;i++)
	{
		// ���ü��
		if(ptCalTab->wParaIndex==CN_NULL_PINNO)
		{
			wIndex=ptCalTab->wSrcIndex[0];
		}
		else if(ptCalTab->wParaIndex<CN_NUM_PARA)
		{
			switch(pdwPara[ptCalTab->wParaIndex])
			{
				case 0:
					wIndex=ptCalTab->wSrcIndex[0];
					break;
				case 1:
					wIndex=ptCalTab->wSrcIndex[1];
					break;
				case 2:
					wIndex=ptCalTab->wSrcIndex[2];
					break;
				default:
					wIndex=ptCalTab->wSrcIndex[0];
					break;
			}
			
			if(wIndex==CN_NULL_PINNO)
			{
				wIndex=ptCalTab->wSrcIndex[0];
			}
		}
		else
		{
			wIndex=ptCalTab->wSrcIndex[0];
		}
		dwAmJ  =ptVector[wIndex].dwAmJ;
		iBuf   =piBuf[wIndex];
		iBufBak=piBufBak[wIndex];
		if(dwAmJ>CN_CAL_F_UMk)
		{
			if((iBuf>=0)&&(iBufBak<0))
			{
				// ���㲹��
				dwFBc    =CN_CAL_F_Coe*iBuf/(iBuf-iBufBak);
				*pdwFDly+=(CN_CAL_F_Coe-dwFBc+(*pdwFBc));
				*pdwFBc  =dwFBc;
				// ����Ƶ��
				if(*pdwFCnt>CN_CAL_F_QD)
				{
					*pdwFCal=CN_CAL_F_CNT*CN_CAL_F_Coe*CN_CAL_F_Coe/(*pdwFDly);
				}
				else
				{
					*pdwFCal=0;
					(*pdwFCnt)++;
				}
				*pdwFDly=0;
			}
			else
			{
				*pdwFDly+=CN_CAL_F_Coe;
			}
		}
		else
		{
			*pdwFCal=0;
			*pdwFDly=0;
			*pdwFBc =0;
			*pdwFCnt=0;
		}
		pdwFCal++;
		pdwFDly++;
		pdwFBc++;
		pdwFCnt++;
		ptCalTab++;
	}
}

// =============================================================================
// �������ܣ�����/��ֵ/��λ���
// �����������
// �����������
// ����ֵ��  ��
// =============================================================================
void IES_IMSam_Out(tag_IMSam *ptag_IMSam)
{
	register UINT32     i;
	register tagVector *ptVectorFst,*ptVector;
	const    tagAnaTab  *ptagAnaTab;
	register UINT32   dwAm,dwAmJ,dwAngle,dwAngleBase=0;
	register UINT32   *pdwFrDst,*pdwFrSrc;
	UINT64   *pdwAm;	
	register INT32    iReal, iImag;          // ʵ���� �鲿
	INT64    *piReal, *piImag;      // ʵ�����鲿
	register FLOAT32  *pfBb;                 // ͨ��ϵ��
	register FLOAT32  fBb;                   // һ����ת�����

	register DWORD    *pdwAdjAmBuf,*pdwAdjAmMin,*pdwAdjAmMax;                                         // ��ֵУ׼����
	register DWORD    *pdwAdjAngAmMin,*pdwAdjAngAmMax;                // ��λУ׼��ֵ����
	register INT32    *piAdjAngBuf,*piAdjAngMin,*piAdjAngMax;      // ��λУ׼����
	register INT32    iAngle;
	register BOOL     bAngleBase=FALSE;

#if(CN_HUM_ENA)
	tagVector *ptVectorHum;
	INT64     *piHumReal, *piHumImag;   // г��ʵ�����鲿
	WORD      j;
#endif
	// һ��ֵ����
		
	ptagAnaTab  = &g_tAnaTab[0];
	piReal      =&(ptag_IMSam->iAnaReal[0]);
	piImag      =&(ptag_IMSam->iAnaImag[0]);
	ptVectorFst =&(g_tagAna.tAnaVectFst[0]);
	ptVector    =&(g_tagAna.tAnaVect[0]);
//	pfCoe       =&(ptag_IMSam->fAnaCoe[0]);
	pfBb        =&(ptag_IMSam->fAnaBb[0]);
	pdwAm       = &(ptag_IMSam->dwAnaAm[0]);
	
	pdwAdjAmBuf    =&(ptag_IMSam->dwAdjAmBuf[0]);
	pdwAdjAmMin    =&(ptag_IMSam->dwAdjAmMin[0]);
	pdwAdjAmMax    =&(ptag_IMSam->dwAdjAmMax[0]);
	
	piAdjAngBuf    =&(ptag_IMSam->iAdjAngBuf[0]);
	piAdjAngMin    =&(ptag_IMSam->iAdjAngMin[0]);
	piAdjAngMax    =&(ptag_IMSam->iAdjAngMax[0]);
	pdwAdjAngAmMin =&(ptag_IMSam->dwAdjAngAmMin[0]);
	pdwAdjAngAmMax =&(ptag_IMSam->dwAdjAngAmMax[0]);

	for(i=0;i<CN_NUM_SAM;i++)
	{
		fBb =*pfBb++;
		
		iReal=(INT32)(((*piReal)>>CN_DFT_BIT));
		iImag=(INT32)(((*piImag)>>CN_DFT_BIT));
		
		*piReal++=0;
		*piImag++=0;

		dwAm   = (UINT32)(sqrt(*pdwAm/CN_SAM_RATE));
		*pdwAm++=0;
		dwAmJ   = IES_CAL_AmpSqrt(iReal, iImag);
		dwAngle = IES_CAL_Angle(iReal, iImag);
		
		//����ת��
		//ptVectorFst->iRe    =(INT32)(iReal);
		//ptVectorFst->iIm    =(INT32)(iImag);
		ptVectorFst->dwAm   =(UINT32)(dwAm);
		ptVectorFst->dwAmJ  =(UINT32)(dwAmJ);
		ptVectorFst->dwAngle=dwAngle;

		//ptVector->iRe    = (INT32)(iReal*fBb);
		//ptVector->iIm    = (INT32)(iImag*fBb);
		ptVector->dwAm   = (UINT32)(dwAm*fBb);
		ptVector->dwAmJ  = (UINT32)(dwAmJ*fBb);
		ptVector->dwAngle= dwAngle;
		// �Զ�У׼���
		if(ptag_IMSam->bAdjAmStr)
		{
			*pdwAdjAmBuf+=ptVector->dwAmJ;
			if(ptVector->dwAmJ<(*pdwAdjAmMin))
			{
				*pdwAdjAmMin=ptVector->dwAmJ;
			}
			if(ptVector->dwAmJ>(*pdwAdjAmMax))
			{
				*pdwAdjAmMax=ptVector->dwAmJ;
			}
			pdwAdjAmBuf++;
			pdwAdjAmMin++;
			pdwAdjAmMax++;
			// ���һ��ͨ�������ۼ�
			if(i==(CN_NUM_SAM-1))
			{
				ptag_IMSam->wAdjAmPtr++;
				if(ptag_IMSam->wAdjAmPtr>=ptag_IMSam->wAdjAmNum)
				{
					ptag_IMSam->bAdjAmStr=FALSE;
					ptag_IMSam->bAdjAmEnd=TRUE;
					ptag_IMSam->wAdjAmPtr=0;
				}
			}
		}
		// ��׼��λ����Ӧ,��ʱ�Ե�һ��������ѹΪ��׼
		if (!bAngleBase)
		{
			// Ҫ�������ѹͨ��������ǰ
			if ((ptagAnaTab[i].wChanType == EN_CTYPE_ANA_U) && (ptVector->dwAmJ > CN_BASE_UMK))
			{
				dwAngleBase = dwAngle;
				bAngleBase = TRUE;
			}
		}
		ptVector++;
		ptVectorFst++;
	#if(CN_HUM_ENA)
		//г������
		piHumReal=&(ptag_IMSam->iAnaHumReal[i][2]);
		piHumImag=&(ptag_IMSam->iAnaHumImag[i][2]);
		ptVectorHum=&(g_tagAna.tAnaVectHum[i][2]);
		for(j=2;j<CN_HUM_NUM;j++)
		{
			iReal=(INT32)(((*piHumReal)>>CN_DFT_BIT));
			iImag=(INT32)(((*piHumImag)>>CN_DFT_BIT));
			*piHumReal++=0;
			*piHumImag++=0;
			
			dwAmJ   = IES_CAL_AmpSqrt(iReal, iImag);
			dwAngle = IES_CAL_Angle(iReal, iImag);

			//ptVectorHum->iRe=iReal*fBb;
			//ptVectorHum->iIm=iImag*fBb;
			ptVectorHum->dwAmJ=dwAmJ*fBb;
			ptVectorHum->dwAngle=dwAngle;
			ptVectorHum++;
		}
	#endif
	}
#if(CN_SV_IN_ENA)
	ptagAnaTab  = &g_tAnaTab[EN_ANA_SV_STR];
	piReal      = &(ptag_IMSam->iAnaReal[EN_ANA_SV_STR]);
	piImag      = &(ptag_IMSam->iAnaImag[EN_ANA_SV_STR]);
	ptVectorFst = &(g_tagAna.tAnaVectFst[EN_ANA_SV_STR]);
	ptVector    = &(g_tagAna.tAnaVect[EN_ANA_SV_STR]);
	pfBb        = &(ptag_IMSam->fAnaBb[EN_ANA_SV_STR]);
	pdwAm       = &(ptag_IMSam->dwAnaAm[EN_ANA_SV_STR]);
	for(i=EN_ANA_SV_STR;i<EN_ANA_SV_END;i++)
	{
		fBb =*pfBb++;
		
		iReal=(INT32)(((*piReal)>>CN_DFT_BIT));
		iImag=(INT32)(((*piImag)>>CN_DFT_BIT));
		
		*piReal++=0;
		*piImag++=0;

		dwAm   = (UINT32)(sqrt(*pdwAm/CN_SAM_RATE));
		*pdwAm++=0;
		dwAmJ   = IES_CAL_AmpSqrt(iReal, iImag);
		dwAngle = IES_CAL_Angle(iReal, iImag);
		
		//����ת��
		//ptVectorFst->iRe    =(INT32)(iReal);
		//ptVectorFst->iIm    =(INT32)(iImag);
		ptVectorFst->dwAm   =(UINT32)(dwAm);
		ptVectorFst->dwAmJ  =(UINT32)(dwAmJ);
		ptVectorFst->dwAngle=dwAngle;

		//ptVector->iRe    = (INT32)(iReal*fBb);
		//ptVector->iIm    = (INT32)(iImag*fBb);
		ptVector->dwAm   = (UINT32)(dwAm*fBb);
		ptVector->dwAmJ  = (UINT32)(dwAmJ*fBb);
		ptVector->dwAngle= dwAngle;
		// ��׼��λ����Ӧ,��ʱ�Ե�һ��������ѹΪ��׼
		if (!bAngleBase)
		{
			// Ҫ�������ѹͨ��������ǰ
			if ((ptagAnaTab[i].wChanType == EN_CTYPE_SV_U) && (ptVector->dwAmJ > CN_BASE_UMK))
			{
				dwAngleBase = dwAngle;
				bAngleBase = TRUE;
			}
		}
		ptVector++;
		ptVectorFst++;
	#if(CN_HUM_ENA)
		//г������
		piHumReal=&(ptag_IMSam->iAnaHumReal[i][2]);
		piHumImag=&(ptag_IMSam->iAnaHumImag[i][2]);
		ptVectorHum=&(g_tagAna.tAnaVectHum[i][2]);
		for(j=2;j<CN_HUM_NUM;j++)
		{
			iReal=(INT32)(((*piHumReal)>>CN_DFT_BIT));
			iImag=(INT32)(((*piHumImag)>>CN_DFT_BIT));
			*piHumReal++=0;
			*piHumImag++=0;
			
			dwAmJ   = IES_CAL_AmpSqrt(iReal, iImag);
			dwAngle = IES_CAL_Angle(iReal, iImag);

			//ptVectorHum->iRe=iReal*fBb;
			//ptVectorHum->iIm=iImag*fBb;
			ptVectorHum->dwAmJ=dwAmJ*fBb;
			ptVectorHum->dwAngle=dwAngle;
			ptVectorHum++;
		}
	#endif
	}
#endif
	// ���¾���׼�жϺ����λ
	ptVectorFst =&g_tagAna.tAnaVectFst[0];
	ptVector    =&g_tagAna.tAnaVect[0];
	ptagAnaTab = &g_tAnaTab[0];
	for(i=0;i<CN_NUM_SAM;i++)
	{
		// �жϷ�ֵ
		if ((ptagAnaTab->wChanType == EN_CTYPE_ANA_U) && (ptVector->dwAmJ > CN_BASE_UMK))
		{
			ptVector->dwAngleRel = (ptVector->dwAngle+360000 - dwAngleBase)%360000;
		}
		else if ((ptagAnaTab->wChanType == EN_CTYPE_ANA_I) && (ptVector->dwAmJ > CN_BASE_IMK))
		{
			ptVector->dwAngleRel = (ptVector->dwAngle+360000 - dwAngleBase)%360000;
		}
		else
		{
			ptVector->dwAngleRel = 0;
		}
		ptVectorFst->dwAngleRel = ptVector->dwAngleRel;
		// ��λ�Զ�У׼���(ȡ���ֵ)
		if(ptag_IMSam->bAdjAngStr)
		{
			iAngle =(ptVector->dwAngleRel>180000)?(INT32)(ptVector->dwAngleRel-360000):(INT32)(ptVector->dwAngleRel);
			dwAmJ   =ptVector->dwAmJ;
			*piAdjAngBuf+=iAngle;
			// ��¼��ֵ����
			if(dwAmJ<(*pdwAdjAngAmMin))
			{
				*pdwAdjAngAmMin=dwAmJ;
			}
			if(dwAmJ>(*pdwAdjAngAmMax))
			{
				*pdwAdjAngAmMax=dwAmJ;
			}
			// ��¼��λ����
			if(iAngle<(*piAdjAngMin))
			{
				*piAdjAngMin=iAngle;
			}
			if(iAngle>(*piAdjAngMax))
			{
				*piAdjAngMax=iAngle;
			}
			piAdjAngBuf++;
			piAdjAngMin++;
			piAdjAngMax++;
			pdwAdjAngAmMin++;
			pdwAdjAngAmMax++;
			if(i==(CN_NUM_SAM-1))
			{
				ptag_IMSam->wAdjAngPtr++;
				if(ptag_IMSam->wAdjAngPtr>=ptag_IMSam->wAdjAngNum)
				{
					ptag_IMSam->bAdjAngStr=FALSE;
					ptag_IMSam->bAdjAngEnd=TRUE;
					ptag_IMSam->wAdjAngPtr=0;
				}
			}
		}
		ptVector++;
		ptVectorFst++;
		ptagAnaTab++;
	}
#if(CN_SV_IN_ENA)	
	// ���¾���׼�жϺ����λ
	ptVectorFst =&g_tagAna.tAnaVectFst[EN_ANA_SV_STR];
	ptVector    =&g_tagAna.tAnaVect[EN_ANA_SV_STR];
	ptagAnaTab = &g_tAnaTab[EN_ANA_SV_STR];
	for(i=EN_ANA_SV_STR;i<EN_ANA_SV_END;i++)
	{
		// �жϷ�ֵ
		if ((ptagAnaTab->wChanType == EN_CTYPE_SV_U) && (ptVector->dwAmJ > CN_BASE_UMK))
		{
			ptVector->dwAngleRel = (ptVector->dwAngle+360000 - dwAngleBase)%360000;
		}
		else if ((ptagAnaTab->wChanType == EN_CTYPE_SV_I) && (ptVector->dwAmJ > CN_BASE_IMK))
		{
			ptVector->dwAngleRel = (ptVector->dwAngle+360000 - dwAngleBase)%360000;
		}
		else
		{
			ptVector->dwAngleRel = 0;
		}
		ptVectorFst->dwAngleRel = ptVector->dwAngleRel;
		// ��λ�Զ�У׼���(ȡ���ֵ)
		ptVector++;
		ptVectorFst++;
		ptagAnaTab++;
	}
#endif	
	g_tagAna.byAnaVecChg=TRUE;
	// Ƶ�ʰ���
	pdwFrDst=&(g_tagAna.dwFrCal[0]);
	pdwFrSrc=&ptag_IMSam->dwFCal[0];
	for(i=0;i<CN_NUM_CAL;i++)
	{
		*pdwFrDst++=*pdwFrSrc++;
	}
	g_tagAna.byFrChg=TRUE;
}

// =============================================================================
// �������ܣ������Զ�У׼
// �����������
// �����������
// ����ֵ��  ��
// =============================================================================
BOOL IES_IMSam_AdJAm_Str(WORD wAdjNum)
{
	tag_IMSam *ptag_IMSam;
	// �Զ�У׼�м����ݳ�ʼ��
	// ���1000�ܲ�
	if(wAdjNum>1000)
	{
		return TRUE;
	}
	ptag_IMSam=&gtag_IMSam;
	ptag_IMSam->bAdjAmStr=FALSE;
	ptag_IMSam->wAdjAmPtr=0;
	ptag_IMSam->wAdjAmNum=wAdjNum;
	ptag_IMSam->bAdjAmEnd=FALSE;
	IES_memset(ptag_IMSam->dwAdjAmMin,0xff,sizeof(ptag_IMSam->dwAdjAmMin));
	IES_memset(ptag_IMSam->dwAdjAmMax,0x0, sizeof(ptag_IMSam->dwAdjAmMax));
	IES_memset(ptag_IMSam->dwAdjAmBuf,0x0, sizeof(ptag_IMSam->dwAdjAmBuf));
	// �Զ�У׼������־һ���������(�˴�˳���ܱ䣡����)
	ptag_IMSam->bAdjAmStr=TRUE;
	
	return FALSE;
}

// =============================================================================
// �������ܣ���ֵ�Զ�У׼������(���������е���)
// �����������
// �����������
// ����ֵ��0:ȫ��У׼ʧ��,No:No��ͨ��У׼�ɹ�
// =============================================================================
UINT32  IES_IMSam_AdJAm(BOOL *pbChn)
{
	WORD     i,wChanType,wParaCoe;
	DWORD    dwAdjNo=0,dwDAm;
	INT32    iParaChg,iParaDefMin,iParaDefMax;
	WORD     wAdjNum;
	FLOAT32  fCoe=0.0f;
	const    tagAnaTab  *ptagAnaTab;
	DWORD    *pdwPara,*pdwParaBak;
	tag_IMSam *ptag_IMSam;
	if(G_Get_ChkIn_P[EN_CHK_PARA_AM_COE])
	{
		return dwAdjNo;
	}
	if(pbChn==NULL)
	{
		return dwAdjNo;
	}
	ptag_IMSam=&gtag_IMSam;
	if(ptag_IMSam->bAdjAmEnd)
	{
		ptag_IMSam->bAdjAmEnd=FALSE;
		wAdjNum=ptag_IMSam->wAdjAmNum;
		ptagAnaTab = &g_tAnaTab[0];
		pdwParaBak = &g_tagPara.dwParaBak[0];
		pdwPara    = &g_tagPara.dwPara[0];
		for(i=0;i<CN_NUM_SAM;i++)
		{
			dwDAm     = ptag_IMSam->dwAdjAmMax[i]-ptag_IMSam->dwAdjAmMin[i];
			wChanType = ptagAnaTab[i].wChanType;
			wParaCoe  = EN_PARA_AM_COE_STR+i;
			// ��ѹͨ��:��ֵ+Ƶ���ж�
			if(wChanType==EN_CTYPE_ANA_U)
			{
				// ��ѹ��ֵ�������ó���0.5V
				if(dwDAm<(g_dwMul[CN_SAM_DIV_U]>>1))

				{
					fCoe=(100.0f*wAdjNum*g_dwMul[CN_SAM_DIV_U])/ptag_IMSam->dwAdjAmBuf[i];
				}
				else
				{
					pbChn[i]=FALSE;
					continue;
				}
			}
			// ����ͨ��
			else if(wChanType==EN_CTYPE_ANA_I)
			{
				if (pdwPara[ptagAnaTab[i].wParaScd] == 1)
				{
					// 1A�ֵ,������ֵ�������ó���0.02A
					if(dwDAm<(g_dwMul[CN_SAM_DIV_I]*0.02f))
					{
						fCoe=(FLOAT32)(5.00f*wAdjNum*g_dwMul[CN_SAM_DIV_I])/(FLOAT32)ptag_IMSam->dwAdjAmBuf[i];
					}
					else
					{
						pbChn[i]=FALSE;
						continue;
					}
				}
				else
				{
					// 1A�ֵ,������ֵ�������ó���0.1A
					if(dwDAm<(g_dwMul[CN_SAM_DIV_I]*0.1f))
					{
						fCoe=(FLOAT32)(1.00f*wAdjNum*g_dwMul[CN_SAM_DIV_I])/(FLOAT32)ptag_IMSam->dwAdjAmBuf[i];
					}
					else
					{
						pbChn[i]=FALSE;
						continue;
					}
				}
			}
			iParaDefMin=g_tParaTab[wParaCoe].iValMin;
			iParaDefMax=g_tParaTab[wParaCoe].iValMax;
			iParaChg=(UINT32)(fCoe*pdwPara[wParaCoe]);
			// ϵ��΢����Χ�ж�
			if((iParaChg<iParaDefMin)||(iParaChg>iParaDefMax))
			{
				pbChn[i]=FALSE;
				continue;
			}
			pdwParaBak[wParaCoe] = iParaChg;
			dwAdjNo++;
			pbChn[i]=TRUE;
		}
		// �������±�־
		//if(dwAdjNo)
		//{
		//	g_tagPara.dwChgWRef[EN_BOARD_PARA_AM_COE]=TRUE;
		//}
		return dwAdjNo;
	}
	else
	{
		return 0;
	}
}
// =============================================================================
// �������ܣ�ֱ�������Զ�У׼
// �����������
// �����������
// ����ֵ��  ��
// =============================================================================
BOOL IES_IMSam_AdJDc_Str(WORD wAdjNum)
{
	tag_IMSam *ptag_IMSam;
	// �Զ�У׼�м����ݳ�ʼ��
	// ���100�ܲ�
	if(wAdjNum>100)
	{
		return TRUE;
	}
	ptag_IMSam=&gtag_IMSam;
	ptag_IMSam->bAdjDcStr=FALSE;
	ptag_IMSam->wAdjDcPtr=0;
	ptag_IMSam->wAdjDcNum=wAdjNum*CN_SAM_RATE;
	ptag_IMSam->bAdjDcEnd=FALSE;
	IES_memset(ptag_IMSam->iAdjDcMin,0x7F,sizeof(ptag_IMSam->iAdjDcMin));
	IES_memset(ptag_IMSam->iAdjDcMax,0x0, sizeof(ptag_IMSam->iAdjDcMax));
	IES_memset(ptag_IMSam->iAdjDcBuf,0x0, sizeof(ptag_IMSam->iAdjDcBuf));
	// �Զ�У׼������־һ���������(�˴�˳���ܱ䣡����)
	ptag_IMSam->bAdjDcStr=TRUE;
	
	return FALSE;
}

// =============================================================================
// �������ܣ�ֱ���Զ�У׼������(���������е���)
// �����������
// �����������
// ����ֵ��0:ȫ��У׼ʧ��,No:No��ͨ��У׼�ɹ�
// =============================================================================
UINT32  IES_IMSam_AdJDc(BOOL *pbChn)
{
	WORD     i;
	DWORD    dwAdjNo=0;
	DWORD    *pdwAmPara,*pdwParaBak;
	INT32     iParaDefMin,iParaDefMax;
	FLOAT32  fAmPara;
	INT32    iCoe,iDAm;
	WORD     wAdjNum;
	WORD     wParaDc;//wParaFst = 0xffff,
	tag_IMSam *ptag_IMSam;
	if(G_Get_ChkIn_P[EN_CHK_PARA_DCBC_COE])
	{
		return dwAdjNo;
	}
	// �Զ�У׼�м����ݳ�ʼ��
	if(pbChn==NULL)
	{
		return dwAdjNo;
	}
	ptag_IMSam=&gtag_IMSam;
	// ��ʱ�����ǻ�׼��У׼
	if(ptag_IMSam->bAdjDcEnd)
	{
		ptag_IMSam->bAdjDcEnd=FALSE;
		wAdjNum    = ptag_IMSam->wAdjDcNum;
		pdwParaBak = g_tagPara.dwParaBak;
		pdwAmPara  = g_tagAna.dwAnaAmCoe;
		for(i=0;i<CN_NUM_SAM;i++)
		{
			fAmPara=(FLOAT32)(pdwAmPara[i]>>16);
			if(fAmPara!=0.0f)
			{
				iDAm = (ptag_IMSam->iAdjDcMax[i]-ptag_IMSam->iAdjDcMin[i])/fAmPara;
				if((iDAm<(INT32)(g_dwMul[CN_SAM_DIV_U]>>1))&&(iDAm>=0))
				{
					iCoe=(INT32)(ptag_IMSam->iAdjDcBuf[i]/fAmPara/(wAdjNum));
				}
				else
				{
					pbChn[i]=FALSE;
					continue;
				}
			}
			else
			{
				pbChn[i]=FALSE;
				continue;
			}
			wParaDc   = EN_PARA_DCBC_COE_STR+i;
			iParaDefMin=g_tParaTab[wParaDc].iValMin;
			iParaDefMax=g_tParaTab[wParaDc].iValMax;
			// ϵ��΢����Χ�ж�
			if((iCoe>iParaDefMax)||(iCoe<iParaDefMin))
			{
				pbChn[i]=FALSE;
				continue;
			}
			pdwParaBak[wParaDc] = iCoe;
			dwAdjNo++;
			pbChn[i]=TRUE;
		}
		// �������±�־
		//if(dwAdjNo)
		//{
		//	g_tagPara.dwChgWRef[EN_BOARD_PARA_DCBC_COE]=TRUE;
		//}
		return dwAdjNo;
	}
	else
	{
		return 0;
	}
}
// =============================================================================
// �������ܣ�������λ�Զ�У׼
// �����������
// �����������
// ����ֵ��  ��
// =============================================================================
BOOL IES_IMSam_AdJAng_Str(WORD wAdjNum)
{
	tag_IMSam *ptag_IMSam;
	// ���֧��1000�ܲ�
	if(wAdjNum>1000)
	{
		return TRUE;
	}
	ptag_IMSam=&gtag_IMSam;
	ptag_IMSam->bAdjAngStr=FALSE;
	ptag_IMSam->wAdjAngPtr=0;
	ptag_IMSam->wAdjAngNum=wAdjNum;
	ptag_IMSam->bAdjAngEnd=FALSE;
	IES_memset(ptag_IMSam->iAdjAngMin,     0x7f , sizeof(ptag_IMSam->iAdjAngMin));
	IES_memset(ptag_IMSam->iAdjAngMax,     0x0  , sizeof(ptag_IMSam->iAdjAngMax));
	IES_memset(ptag_IMSam->iAdjAngBuf,     0x0  , sizeof(ptag_IMSam->iAdjAngBuf));
	IES_memset(ptag_IMSam->dwAdjAngAmMin,  0xff , sizeof(ptag_IMSam->dwAdjAngAmMin));
	IES_memset(ptag_IMSam->dwAdjAngAmMax,  0x0  , sizeof(ptag_IMSam->dwAdjAngAmMax));
	// �Զ�У׼������־һ���������(�˴�˳���ܱ䣡����)
	ptag_IMSam->bAdjAngStr=TRUE;
	return FALSE;
}

// =============================================================================
// �������ܣ���λ�Զ�У׼������(���������е���)
// �����������
// �����������
// ����ֵ��0:ȫ��У׼ʧ��,No:No��ͨ��У׼�ɹ�
// =============================================================================
UINT32  IES_IMSam_AdJAng(BOOL *pbChn)
{
	WORD      i,wAdPara;
	DWORD     dwAdjNo=0;
	WORD      wAdjNum;
	INT32     iDAng,iDTns,iAngBase,iParaDefMin,iParaDefMax,iParaChg;
	const     tagAnaTab  *ptagAnaTab;
	DWORD     *pdwPara,*pdwParaBak;
	tag_IMSam *ptag_IMSam;
	
	if(G_Get_ChkIn_P[EN_CHK_PARA_ANG_COE])
	{
		return dwAdjNo;
	}
	if(pbChn==NULL)
	{
		return dwAdjNo;
	}
	ptag_IMSam=&gtag_IMSam;
	if(ptag_IMSam->bAdjAngEnd)
	{
		ptag_IMSam->bAdjAngEnd=FALSE;
		wAdjNum    = ptag_IMSam->wAdjAngNum;
		ptagAnaTab = &g_tAnaTab[0];
		pdwParaBak = &g_tagPara.dwParaBak[0];
		pdwPara    = &g_tagPara.dwPara[0];
		// ��׼��ѹ��λѡ��Ua AD1
		if((ptag_IMSam->dwAdjAngAmMax[CN_BASE_AD]>101000)
		||(ptag_IMSam->dwAdjAngAmMin[CN_BASE_AD]<99000))
		{
			return dwAdjNo;
		}
		iAngBase=ptag_IMSam->iAdjAngBuf[CN_BASE_AD];
		// ��׼��ѹ��λѡ�� end
		for(i=0;i<CN_NUM_AD;i++)
		{
			// �ж��Ƿ���ADоƬ0ͨ����4ͨ��
			if(ptagAnaTab[i].wADChn==0)
			{
				wAdPara =EN_PARA_ANG_COE_STR+ptagAnaTab[i].wADNo;
			}
			else if(ptagAnaTab[i].wADChn==4)
			{
				wAdPara =EN_PARA_ANG_COE_STR+CN_NUM_JZ+ptagAnaTab[i].wADNo;
			}
			else
			{
				continue;
			}
			// ��ֵ��Χ�ж�
			if(ptagAnaTab[i].wChanType==EN_CTYPE_ANA_U)
			{
				// ��ѹ��ֵ��Χ[99V,101V]
				if((ptag_IMSam->dwAdjAngAmMax[i]>101000)
				||(ptag_IMSam->dwAdjAngAmMin[i]<99000))
				{
					*pbChn++=FALSE;
					continue;
				}
			}
			else if(ptagAnaTab[i].wChanType==EN_CTYPE_ANA_I)
			{
				// ������ֵ��Χ[0.95In,1.05In]
				if (pdwPara[ptagAnaTab[i].wParaScd] == 0)
				{
					if((ptag_IMSam->dwAdjAngAmMax[i]>1050)
					||(ptag_IMSam->dwAdjAngAmMin[i]<950))
					{
						*pbChn++=FALSE;
						continue;
					}
				}
				else
				{
					if((ptag_IMSam->dwAdjAngAmMax[i]>5250)
					||(ptag_IMSam->dwAdjAngAmMin[i]<4750))
					{
						*pbChn++=FALSE;
						continue;
					}
				}
			}
			// ��λ��Χ�жϣ���λ��������2��,У׼ʧ�ܣ�
			if(abs(ptag_IMSam->iAdjAngMax[i]-ptag_IMSam->iAdjAngMin[i])>2000)
			{
				*pbChn++=FALSE;
				continue;
			}
			// 100�ܲ���λ���׼�ǶȲ�(������200��)
			if(abs(iAngBase-ptag_IMSam->iAdjAngBuf[i])>2000*wAdjNum)
			{
				*pbChn++=FALSE;
				continue;
			}
			// ��λ�����
			iDAng=(iAngBase-ptag_IMSam->iAdjAngBuf[i]);
			// ʱ�����ת��(0.001��=(2/36)us)
			iDTns=iDAng*20/(36*wAdjNum);

			iParaDefMin=g_tParaTab[wAdPara].iValMin;
			iParaDefMax=g_tParaTab[wAdPara].iValMax;
			
			iParaChg=pdwPara[wAdPara]+iDTns;
			
			if((iParaChg<iParaDefMin)||(iParaChg>iParaDefMax))
			{
				*pbChn++=FALSE;
				continue;
			}
			// ϵ��΢����Χ�ж�
			pdwParaBak[wAdPara] = iParaChg;
			dwAdjNo++;
			*pbChn++=TRUE;
		}
		// �������±�־
		//if(dwAdjNo)
		//{
		//	g_tagPara.dwChgWRef[EN_BOARD_PARA_ANG_COE]=TRUE;
		//}
	}
	return dwAdjNo;
}
#if(CN_SV_IN_ENA)
// =============================================================================
// �������ܣ�SV�������ó�ʼ������
// �����������
// �����������
// ����ֵ��  ��
// =============================================================================

void IES_IMSam_SvSub_Init()
{
#if(CN_DEV_CPU1)

	WORD i;
	BOOL *pbSvSub;
	BYTE *pbySvCb;
	BYTE  bySvCbA1=0xAA,bySvCbA2=0xAA,bySvCbB1=0xAA,bySvCbB2=0xAA;

	pbSvSub=g_tagAna.bSvSub;                    // SV���ı�־
	pbySvCb=g_tagAna.bySvCb;                    // SV���Ŀ��ƿ�ӳ��(��Ҫ�Լ�)
	// ���Ŀ��ƿ�����Լ�
	for(i=0;i<EN_LINK_END;i++)
	{
		// A��Iĸ�ߵ�ѹ�ж���/δȫ����/��ѹ����ƿ鶩���ж�
		if(pbSvSub[i])
		{
			G_Set_Inter(EN_INTER_SVSUB_A1_CFG,TRUE);
			// ��¼��һ�����ƿ��
			if(bySvCbA1==0xAA)
			{
				bySvCbA1=pbySvCb[i];
			}
			else
			{
				if(pbySvCb[i]!=bySvCbA1)
				{
					G_Set_Inter(EN_INTER_SVSUB_A1_MULT,TRUE);
				}
			}
		}
		else
		{
			G_Set_Inter(EN_INTER_SVSUB_A1_LOSE,TRUE);
		}
		// A��IIĸ�ߵ�ѹ�ж���/δȫ����/��ѹ����ƿ鶩���ж�
		if(pbSvSub[i+EN_LINK_END])
		{
			G_Set_Inter(EN_INTER_SVSUB_A2_CFG,TRUE);
			if(bySvCbA2==0xAA)
			{
				bySvCbA2=pbySvCb[i+EN_LINK_END];
			}
			else
			{
				if(pbySvCb[i+EN_LINK_END]!=bySvCbA2)
				{
					G_Set_Inter(EN_INTER_SVSUB_A2_MULT,TRUE);
				}
			}
		}
		else
		{
			G_Set_Inter(EN_INTER_SVSUB_A2_LOSE,TRUE);
		}
		// B��Iĸ�ߵ�ѹ�ж���/δȫ����/��ѹ����ƿ鶩���ж�
		if(pbSvSub[i+EN_LINK_END*2])
		{
			G_Set_Inter(EN_INTER_SVSUB_B1_CFG,TRUE);
			if(bySvCbB1==0xAA)
			{
				bySvCbB1=pbySvCb[i+EN_LINK_END*2];
			}
			else
			{
				if(pbySvCb[i+EN_LINK_END*2]!=bySvCbB1)
				{
					G_Set_Inter(EN_INTER_SVSUB_B1_MULT,TRUE);
				}
			}
		}
		else
		{
			G_Set_Inter(EN_INTER_SVSUB_B1_LOSE,TRUE);
		}
		// B��IIĸ�ߵ�ѹ�ж���/δȫ����/��ѹ����ƿ鶩���ж�
		if(pbSvSub[i+EN_LINK_END*3])
		{
			G_Set_Inter(EN_INTER_SVSUB_B2_CFG,TRUE);
		}
		else
		{
			G_Set_Inter(EN_INTER_SVSUB_B2_LOSE,TRUE);
			if(bySvCbB2==0xAA)
			{
				bySvCbB2=pbySvCb[i+EN_LINK_END*3];
			}
			else
			{
				if(pbySvCb[i+EN_LINK_END*3]!=bySvCbB2)
				{
					G_Set_Inter(EN_INTER_SVSUB_B2_MULT,TRUE);
				}
			}
		}
		// A��I��IIĸ���Ĳ�һ��
		if(pbSvSub[i]^pbSvSub[i+EN_LINK_END])
		{
			G_Set_Inter(EN_INTER_SVSUB_A_DIS,TRUE);
		}
		// A��I��IIĸ����ƿ鶩��
		if((pbSvSub[i]&pbSvSub[i+EN_LINK_END])
		&&(pbySvCb[i]!=pbySvCb[i+EN_LINK_END]))
		{
			G_Set_Inter(EN_INTER_SVSUB_A_MULT,TRUE);
		}
		// B��I��IIĸ���Ĳ�һ��
		if(pbSvSub[i+EN_LINK_END*2]^pbSvSub[i+EN_LINK_END*3])
		{
			G_Set_Inter(EN_INTER_SVSUB_B_DIS,TRUE);
		}
		// B��I��IIĸ����ƿ鶩��
		if((pbSvSub[i+EN_LINK_END*2]&pbSvSub[i+EN_LINK_END*3])
		&&(pbySvCb[i+EN_LINK_END*2]!=pbySvCb[i+EN_LINK_END*3]))
		{
			G_Set_Inter(EN_INTER_SVSUB_B_MULT,TRUE);
		}
		// A��B��Iĸ���Ĳ�һ��
		if(pbSvSub[i]^pbSvSub[i+EN_LINK_END*2])
		{
			G_Set_Inter(EN_INTER_SVSUB_1M_DIS,TRUE);
		}
		// A��B��IIĸ���Ĳ�һ��
		if(pbSvSub[i+EN_LINK_END]^pbSvSub[i+EN_LINK_END*3])
		{
			G_Set_Inter(EN_INTER_SVSUB_2M_DIS,TRUE);
		}
	}
	// ĸ�߰�(CPU2)���κ�������ж�Ϊ��ĸ�ߵ��׶���
#if(CN_DEV_CPU2)
// if(g_tagBoard.dwBoardType==CN_BOARD_CPU2_ADDR)	
	{
		G_Set_Inter(EN_INTER_SVSUB_A1_CFG,TRUE);
		G_Set_Inter(EN_INTER_SVSUB_A1_LOSE,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_A1_MULT,FALSE);
		
		G_Set_Inter(EN_INTER_SVSUB_A2_CFG,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_A2_LOSE,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_A2_MULT,FALSE);
		
		G_Set_Inter(EN_INTER_SVSUB_B1_CFG,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_B1_LOSE,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_B1_MULT,FALSE);
		
		G_Set_Inter(EN_INTER_SVSUB_B2_CFG,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_B2_LOSE,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_B2_MULT,FALSE);
	}
#endif
	// A��Iĸ��Ч�ж�
	if(G_Get_Inter(EN_INTER_SVSUB_A1_CFG)
		&&(!G_Get_Inter(EN_INTER_SVSUB_A1_MULT)))
	{
		G_Set_Inter(EN_INTER_SVSUB_A1_VALID,TRUE);
	}
	// A��IIĸ��Ч�ж�
	if(G_Get_Inter(EN_INTER_SVSUB_A2_CFG)
		&&(!G_Get_Inter(EN_INTER_SVSUB_A2_MULT)))
	{
		G_Set_Inter(EN_INTER_SVSUB_A2_VALID,TRUE);
	}
	// B��Iĸ��Ч�ж�
	if(G_Get_Inter(EN_INTER_SVSUB_B1_CFG)
		&&(!G_Get_Inter(EN_INTER_SVSUB_B1_MULT)))
	{
		G_Set_Inter(EN_INTER_SVSUB_B1_VALID,TRUE);
	}
	// B��IIĸ��Ч�ж�
	if(G_Get_Inter(EN_INTER_SVSUB_B2_CFG)
		&&(!G_Get_Inter(EN_INTER_SVSUB_B2_MULT)))
	{
		G_Set_Inter(EN_INTER_SVSUB_B2_VALID,TRUE);
	}
	// ��ĸ�߽�A�׶���:A��Iĸ������Ч������ĸ�߾��޶���
	if(G_Get_Inter(EN_INTER_SVSUB_A1_VALID)&&(!G_Get_Inter(EN_INTER_SVSUB_A2_CFG))&&(!G_Get_Inter(EN_INTER_SVSUB_B1_CFG))&&(!G_Get_Inter(EN_INTER_SVSUB_B2_CFG)))
	{
		G_Set_Inter(EN_INTER_SVSUB_1M_1LINKA,TRUE);
		G_Set_Inter(EN_INTER_SVSUB_A_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_B_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_1M_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_2M_DIS,FALSE);
	}
	// ��ĸ�߽�B�׶���:B��Iĸ������Ч������ĸ�߾��޶���
	else if((!G_Get_Inter(EN_INTER_SVSUB_A1_CFG))&&(!G_Get_Inter(EN_INTER_SVSUB_A2_CFG))&&G_Get_Inter(EN_INTER_SVSUB_B1_VALID)&&(!G_Get_Inter(EN_INTER_SVSUB_B2_CFG)))
	{
		G_Set_Inter(EN_INTER_SVSUB_1M_1LINKB,TRUE);
		G_Set_Inter(EN_INTER_SVSUB_A_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_B_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_1M_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_2M_DIS,FALSE);
	}
	// ��ĸ��˫�׶���
	else if(G_Get_Inter(EN_INTER_SVSUB_A1_VALID)&&(!G_Get_Inter(EN_INTER_SVSUB_A2_CFG))&&G_Get_Inter(EN_INTER_SVSUB_B1_VALID)&&(!G_Get_Inter(EN_INTER_SVSUB_B2_CFG)))
	{
		G_Set_Inter(EN_INTER_SVSUB_1M_2LINK,TRUE);
		G_Set_Inter(EN_INTER_SVSUB_A_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_B_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_2M_DIS,FALSE);
	}
	// ˫ĸ�߽�A�׶���
	else if(G_Get_Inter(EN_INTER_SVSUB_A1_VALID)&&G_Get_Inter(EN_INTER_SVSUB_A2_VALID)&&(!G_Get_Inter(EN_INTER_SVSUB_B1_CFG))&&(!G_Get_Inter(EN_INTER_SVSUB_B2_CFG)))
	{
		G_Set_Inter(EN_INTER_SVSUB_2M_1LINKA,TRUE);
		G_Set_Inter(EN_INTER_SVSUB_B_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_1M_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_2M_DIS,FALSE);
	}
	// ˫ĸ�߽�B�׶���
	else if((!G_Get_Inter(EN_INTER_SVSUB_A1_CFG))&&(!G_Get_Inter(EN_INTER_SVSUB_A2_CFG))&&G_Get_Inter(EN_INTER_SVSUB_B1_VALID)&&G_Get_Inter(EN_INTER_SVSUB_B2_VALID))
	{
		G_Set_Inter(EN_INTER_SVSUB_2M_1LINKB,TRUE);
		G_Set_Inter(EN_INTER_SVSUB_A_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_1M_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_2M_DIS,FALSE);
	}	
	// ˫ĸ��˫�׶���
	else if(G_Get_Inter(EN_INTER_SVSUB_A1_VALID)&&G_Get_Inter(EN_INTER_SVSUB_A2_VALID)&&G_Get_Inter(EN_INTER_SVSUB_B1_VALID)&&G_Get_Inter(EN_INTER_SVSUB_B2_VALID))
	{
		G_Set_Inter(EN_INTER_SVSUB_2M_2LINK,TRUE);
	}
	// A���޶���
	if(!(G_Get_Inter(EN_INTER_SVSUB_A1_CFG)||G_Get_Inter(EN_INTER_SVSUB_A2_CFG)))
	{
		G_Set_AlmIn(EN_ALM_SVLINK_NOCFGA,TRUE);
	}
	// B���޶���
	if(!(G_Get_Inter(EN_INTER_SVSUB_B1_CFG)||G_Get_Inter(EN_INTER_SVSUB_B2_CFG)))
	{
		G_Set_AlmIn(EN_ALM_SVLINK_NOCFGB,TRUE);
	}
	// A�׶��������쳣
	if(G_Get_Inter(EN_INTER_SVSUB_A1_MULT)||G_Get_Inter(EN_INTER_SVSUB_A2_MULT)
		||G_Get_Inter(EN_INTER_SVSUB_A_DIS)||G_Get_Inter(EN_INTER_SVSUB_A_MULT)
		||G_Get_Inter(EN_INTER_SVSUB_1M_DIS)||G_Get_Inter(EN_INTER_SVSUB_2M_DIS))
	{
		G_Set_AlmIn(EN_ALM_SVLINK_CFGA,TRUE);
		G_Set_Inter(EN_INTER_SVSUB_A_CHK,TRUE);
	}
	// B�׶��������쳣
	if(G_Get_Inter(EN_INTER_SVSUB_B1_MULT)||G_Get_Inter(EN_INTER_SVSUB_B2_MULT)
		||G_Get_Inter(EN_INTER_SVSUB_B_DIS)||G_Get_Inter(EN_INTER_SVSUB_B_MULT)
		||G_Get_Inter(EN_INTER_SVSUB_1M_DIS)||G_Get_Inter(EN_INTER_SVSUB_2M_DIS))
	{
		G_Set_AlmIn(EN_ALM_SVLINK_CFGB,TRUE);
		G_Set_Inter(EN_INTER_SVSUB_B_CHK,TRUE);
	}
	// ���ƿ������쳣
	for(i=0;i<CN_NUM_SVCB_SUB;i++)
	{
		if(g_tagAna.dwSvCbSubCfg[i])
		{
			G_Set_AlmIn(EN_ALM_SVSUB_CFG01+i,TRUE);
		}
	}
	#endif
}
#endif
// =============================================================================
// �������ܣ�SV�������ó�ʼ������
// �����������
// �����������
// ����ֵ��  ��
// =============================================================================

void IES_IMSam_SvPub_Init()
{
	const tagSvPubTab  *ptSvPubTab;
	WORD *pwSvPubCfg,*pwSvPubChn,*pwSvPubSend;
	WORD wSvPubCfg,wSvPubNum;
	WORD i;
	pwSvPubCfg=g_tagAna.wSvPubCfg;
	pwSvPubSend=g_tagAna.wSvPubSend;
	pwSvPubChn=g_tagAna.wSvPubChn;
	wSvPubNum =g_tagAna.wSvPubNum-1;//��ȥ���ʱ
	// ��ʼ��ͨ������
	IES_memset(g_tagAna.wSvPubChn,0xff,sizeof(g_tagAna.wSvPubChn));

	if(g_tagAna.wSvPubNum==g_tagAna.wSvPubDatNum)
	{
		G_Set_Inter(EN_INTER_SVPUB_DLY,TRUE);
	}
	if((wSvPubNum==g_NUM_SVPUB)&& (g_tagAna.wSvPubNum == g_tagAna.wSvPubDatNum+1))
	{
		ptSvPubTab=&g_tSvPubTab[0];
		G_Set_Inter(EN_INTER_SVPUB_STD,TRUE);
		G_Set_Inter(EN_INTER_SVPUB_ANA,TRUE);
		G_Set_Inter(EN_INTER_SVPUB_M,TRUE);
		for(i=0;i<wSvPubNum;i++)
		{
			 wSvPubCfg=*pwSvPubCfg++;
			*pwSvPubSend++=wSvPubCfg;
			// ��׼
			if(wSvPubCfg!=ptSvPubTab->wStdIndex)
			{
				G_Set_Inter(EN_INTER_SVPUB_STD,FALSE);
			}
			if(wSvPubCfg!=ptSvPubTab->wAnaIndex)
			{
				G_Set_Inter(EN_INTER_SVPUB_ANA,FALSE);
			}
			if((wSvPubCfg!=ptSvPubTab->wAnaIndex2))
			{
				G_Set_Inter(EN_INTER_SVPUB_M,FALSE);
			}
			if(!(G_Get_Inter(EN_INTER_SVPUB_STD)||G_Get_Inter(EN_INTER_SVPUB_ANA)||G_Get_Inter(EN_INTER_SVPUB_M)))
			{
				G_Set_Inter(EN_INTER_SVPUB_CHK,TRUE);
			}
			ptSvPubTab++;
		}
	}
	// ͨ��������һ��,�Ǳ�׼SV����
	else
	{
		G_Set_Inter(EN_INTER_SVPUB_CHK,TRUE);
	}
		// ӳ���ϵ����
	if(g_tagAna.wSvPubDatNum>=CN_NUM_ANA)
	{
		G_Set_Inter(EN_INTER_SVPUB_CHN_NUM,TRUE);
		wSvPubNum=g_tagAna.wSvPubDatNum;
	}
	pwSvPubCfg = g_tagAna.wSvPubCfg;
	for(i=0;i<wSvPubNum;i++)
	{
		wSvPubCfg=*pwSvPubCfg++;
		if(wSvPubCfg<CN_NUM_ANA)
		{
			pwSvPubChn[wSvPubCfg]=i;
		}
		// ͨ������Խ��
		else
		{
			G_Set_Inter(EN_INTER_SVPUB_CHN_NO,TRUE);
		}
	}
}
// =============================================================================
// �������ܣ�SV�������������޸�
// �����������
// �����������
// ����ֵ��    ��
// =============================================================================

void IES_IMSam_SvPub_Chg(WORD wIndexSrc,WORD wIndexDst,WORD wAddNum,DWORD dwChg1,DWORD dwChg2)
{
	WORD *pbSvPubCfg,*pbSvPubChn,*pbSvPubSend;
	WORD bSvPubChn,bSvPubChg=FALSE;
	BOOL *pbSvPubPol;
	WORD i;
	pbSvPubCfg  =g_tagAna.wSvPubCfg;
	pbSvPubChn  =&g_tagAna.wSvPubChn[wIndexSrc];
	pbSvPubSend =g_tagAna.wSvPubSend;
	pbSvPubPol  =g_tagAna.bSvPubPol;
	//if(!(G_Get_Inter(EN_INTER_SVPUB_CHK)))
	{
		// ����ԭʼ����
		for(i=0;i<g_tagAna.wSvPubDatNum;i++)
		{
			pbSvPubSend[i]=pbSvPubCfg[i];
		}
		// GOOSE������������
		for(i=0;i<wAddNum;i++)
		{
			bSvPubChn=pbSvPubChn[i];
			if(bSvPubChn>=g_tagAna.wSvPubDatNum)
			{
				// ��̬�޸��쳣
				continue;
			}
			
			if(pbSvPubPol[wIndexDst+i])
			{
				pbSvPubSend[bSvPubChn]=wIndexDst+i+CN_SV_Pub_Pol;
			}
			else
			{
				pbSvPubSend[bSvPubChn]=wIndexDst+i;
			}
			// ����ͨ���·�,�ڴ˴�ʹ��,��û�з���������ͨ��,������
			bSvPubChg=TRUE;
		}
		if(bSvPubChg)
		{
		    g_tagAna.wSvPubChg|=dwChg1;
		}
		else
		{
		    g_tagAna.wSvPubChg|=dwChg2;
		}	
	}
}
// =============================================================================
// �������ܣ�SV�������������޸�(������Ҫͨ���ϳɵ�����)
// �����������
// �����������
// ����ֵ��    ��
// =============================================================================
BOOL IES_IMSam_SvPub_Cal(WORD wIndexSrc1,WORD wIndexSrc2,WORD wIndexDst)
{
	BOOL *pbSvPubPol;
	WORD *pbSvPubChn,*pbSvPubSend;
	WORD  wSvPubChnDst;

	pbSvPubChn  =g_tagAna.wSvPubChn;
	pbSvPubSend =g_tagAna.wSvPubSend;
	pbSvPubPol  =g_tagAna.bSvPubPol;
	// Ŀ��ö��Խ��
	if(wIndexDst>=CN_NUM_ANA)
	{
		return FALSE;
	}
	wSvPubChnDst=pbSvPubChn[wIndexDst];
	if(wSvPubChnDst>=g_tagAna.wSvPubDatNum)
	{
		g_tagAna.wSvPubChg|=CN_SV_OPT_CAL_F;
		return FALSE;
	}
	// Դö��1�ж�
	if(wIndexSrc1>=CN_NUM_ANA)
	{
		return FALSE;
	}
	// Դö��2�ж�
	if(wIndexSrc2<CN_NUM_ANA)
	{
		// �����ж�
		if(pbSvPubPol[wIndexSrc1])
		{
			pbSvPubSend[wSvPubChnDst]=CN_SV_Pub_Cal+CN_SV_Pub_Pol+(wIndexSrc1<<7)+wIndexSrc2;
		}
		else
		{
			pbSvPubSend[wSvPubChnDst]=CN_SV_Pub_Cal+(wIndexSrc1<<7)+wIndexSrc2;
		}
	}
	else
	{
		// �����ж�
		if(pbSvPubPol[wIndexSrc1])
		{
			pbSvPubSend[wSvPubChnDst]=CN_SV_Pub_Pol+wIndexSrc1;
		}
		else
		{
			pbSvPubSend[wSvPubChnDst]=wIndexSrc1;
		}
	}
	g_tagAna.wSvPubChg|=CN_SV_OPT_CAL_S;
	return TRUE;
}
// =============================================================================
// �������ܣ�SV��������������
// �����������
// �����������
// ����ֵ��    ��
// =============================================================================
BOOL IES_IMSam_SvPub_Pol(WORD wIndexStr,WORD wIndexEnd,UINT32 dwSet)
{
	WORD *pbSvPubSend,*pbSvPubCfg;
	WORD  wSvPubSend,wSvPubCfg,wSvPubIndex;
	BOOL  *pbSvPubPol;
	WORD i;
	// ��������
	if((wIndexStr>=CN_NUM_ANA)||(wIndexEnd>=CN_NUM_ANA)||(wIndexEnd<wIndexStr))
	{
		return FALSE;
	}
	pbSvPubPol  = g_tagAna.bSvPubPol;
	pbSvPubCfg  = g_tagAna.wSvPubCfg;
	pbSvPubSend = g_tagAna.wSvPubSend;
	for(i=wIndexStr;i<wIndexEnd;i++)
	{
		pbSvPubPol[i]=(dwSet&g_dwBit[i-wIndexStr])?TRUE:FALSE;		
	}
	// ���µ�ǰ������
	for(i=0;i<g_tagAna.wSvPubDatNum;i++)
	{
		// ����ԭʼ����������
		wSvPubCfg  = *pbSvPubCfg;
		wSvPubIndex=(wSvPubCfg)&CN_SV_Pub_Index1;
		if((wSvPubIndex>=wIndexStr)&&(wSvPubIndex<wIndexEnd))
		{
			if(pbSvPubPol[wSvPubIndex])
			{*pbSvPubCfg=wSvPubCfg|CN_SV_Pub_Pol;}
			else
			{*pbSvPubCfg=wSvPubCfg&(~CN_SV_Pub_Pol);};
		}
		pbSvPubCfg++;
		// �������·���������
		wSvPubSend = *pbSvPubSend;
		wSvPubIndex=(wSvPubSend)&CN_SV_Pub_Index1;
		if((wSvPubIndex>=wIndexStr)&&(wSvPubIndex<wIndexEnd))
		{
			if(pbSvPubPol[wSvPubIndex])
			{*pbSvPubSend=wSvPubSend|CN_SV_Pub_Pol;}
			else
			{*pbSvPubSend=wSvPubSend&(~CN_SV_Pub_Pol);};
		}
		pbSvPubSend++;
	}
	// �����·�
	g_tagAna.wSvPubChg|=CN_SV_OPT_POL_S;
	return TRUE;
}
// =============================================================================
// �������ܣ�����Ԫ����λ
// �����������
// �����������
// ����ֵ��  ��
// =============================================================================

void IES_IMSam_Reset()
{
	tag_IMSam *ptag_IMSam;
	ptag_IMSam=&gtag_IMSam;
// ���ָ�뼰��־
	ptag_IMSam->dwWaveFlag=FALSE;
//	ptag_IMSam->dwTDMPtr=0;                    // ��ʱ����ָ��
	ptag_IMSam->dwAnaPtr=0;                    // ��������ָ��
// ���ʵ�鲿
	IES_memset(ptag_IMSam->iAnaReal,0x0,sizeof(ptag_IMSam->iAnaReal));
	IES_memset(ptag_IMSam->iAnaImag,0x0,sizeof(ptag_IMSam->iAnaImag));
#if(CN_HUM_ENA)	
// ���13��г��ʵ�鲿
	IES_memset(ptag_IMSam->iAnaHumReal,0x0,sizeof(ptag_IMSam->iAnaHumReal));
	IES_memset(ptag_IMSam->iAnaHumImag,0x0,sizeof(ptag_IMSam->iAnaHumImag));
#endif	
// ������ַ�ֵ
	IES_memset(ptag_IMSam->dwAnaAm,0x0,sizeof(ptag_IMSam->dwAnaAm));
}
#if(CN_TCHG_ENA)
// ============================================================================
// �������ܣ��¶ȱ仯����ϵ��
// ���������ȫ�ֲ���
// �����������ȡ�У׼ϵ��
// ����ֵ��  ��
// ============================================================================
void IES_IMSam_TChg_Para(tag_IMSam *ptag_IMSam)
{
	//if(g_tagDC.bDCChg[EN_DC_T1])
	{
		if(g_tagDC.iDCOut[CN_DC_INDEX_T]>=73000)
		{
			if(ptag_IMSam->dwCoeTModStr!=EN_TCHG_MOD2)
			{
				ptag_IMSam->dwCoeTModStr=EN_TCHG_MOD2;
				ptag_IMSam->dwCoeTCnt=0;
			}
			if(ptag_IMSam->dwCoeTMod!=EN_TCHG_MOD2)
			{
				// �˴�����5�β��ܴ�������5֡,��������
				if(++ptag_IMSam->dwCoeTCnt>=5)
				{
					ptag_IMSam->dwCoeTMod=EN_TCHG_MOD2;
					ptag_IMSam->dwCoeTCnt=0;
					IES_IMSam_Para_Init();
				}
			}
		}
		else if(g_tagDC.iDCOut[CN_DC_INDEX_T]<=(-8000))
		{
			if(ptag_IMSam->dwCoeTModStr!=EN_TCHG_MOD3)
			{
				ptag_IMSam->dwCoeTModStr=EN_TCHG_MOD3;
				ptag_IMSam->dwCoeTCnt=0;
			}
			if(ptag_IMSam->dwCoeTMod!=EN_TCHG_MOD3)
			{
				if(++ptag_IMSam->dwCoeTCnt>=5)
				{
					ptag_IMSam->dwCoeTMod=EN_TCHG_MOD3;
					ptag_IMSam->dwCoeTCnt=0;
					IES_IMSam_Para_Init();
				}
			}
		}
		else
		{
			if(ptag_IMSam->dwCoeTModStr!=EN_TCHG_MOD1)
			{
				ptag_IMSam->dwCoeTModStr=EN_TCHG_MOD1;
				ptag_IMSam->dwCoeTCnt=0;
			}
			if(ptag_IMSam->dwCoeTMod!=EN_TCHG_MOD1)
			{
				if(++ptag_IMSam->dwCoeTCnt>=5)
				{
					ptag_IMSam->dwCoeTMod=EN_TCHG_MOD1;
					ptag_IMSam->dwCoeTCnt=0;
					IES_IMSam_Para_Init();
				}
			}
		}
	}
}
#endif
// ============================================================================
// �������ܣ���������
// ���������ȫ�ֲ���
// �����������ȡ�У׼ϵ��
// ����ֵ��  ��
// ============================================================================
void IES_IMSam_Para_Init()
{
	tag_IMSam *ptag_IMSam;

	const tagAnaTab  *ptagAnaTab;
	FLOAT32          *pfBb,*pfAnaPtCt;
	FLOAT32          *pfPara;
	WORD             i, wParaFst = 0xffff, wParaScd = 0xffff;
	DWORD            *pdwPara,*pdwAnaAmCoe;
	WORD             *pwAnaAngCoe,*pwAnaDcCoe;
	DWORD            dwAnaAmCoe=0;
	WORD             wAnaAngCoe=0,wAnaDcCoe=0;
	FLOAT32          fBb12 = 0.0;   // һ��ֵת����ֵ���
	FLOAT32          fBb21 = 0.0;   // ����ֵתһ��ֵ���
	FLOAT32          fTCoe = 1.0f;  // �¶ȵ���ϵ��
	BYTE             byAnaPtCtChg=FALSE, byAnaAmCoeChg = FALSE, byAnaAngCoeChg = FALSE, byAnaDcCoeChg = FALSE;
	ptag_IMSam = &gtag_IMSam;
	// �����쳣�˳���������,������
	// �������Լ��˳���������,������
	if(G_Get_ChkIn_P[EN_CHK_PARA_SAM]
	||G_Get_ChkIn_P[EN_CHK_PARA_AM_COE]
	||G_Get_ChkIn_P[EN_CHK_PARA_ANG_COE]
	/*||G_Get_ChkIn_P[EN_CHK_PARA_DCBC_COE]*/
	||G_Get_Const_Chk(EN_DTYPE_ANA)
	||G_Get_Const_Chk(EN_CFG_SAM_BOARD)
	)
	{
		g_iInter[EN_INTER_RUN_SV_BS]=TRUE;
		ptag_IMSam->dwBs = TRUE;
		return;
	}
	else 
	{
		g_iInter[EN_INTER_RUN_SV_BS]=FALSE;
		ptag_IMSam->dwBs=FALSE;
	}

	// ��ȸ���
	pfPara     = &g_tagPara.fPara[0];
	pdwPara    = &g_tagPara.dwPara[0];
	pfBb       = &(ptag_IMSam->fAnaBb[0]);
	pfAnaPtCt = &(g_tagAna.fAnaPtCt[0]);
	ptag_IMSam->dwInit = TRUE;
	// ��ȸ���
	ptagAnaTab = &g_tAnaTab[0];
	for (i = 0; i < CN_NUM_ANA; i++)
	{
		// ����һ���źű��һ��
		if ((wParaFst == ptagAnaTab->wParaFst) && (wParaScd == ptagAnaTab->wParaScd))
		{
			*pfBb = fBb12;
		}
		else
		{
			wParaFst = ptagAnaTab->wParaFst;
			wParaScd = ptagAnaTab->wParaScd;
			switch (ptagAnaTab->wChanType)
			{
			case EN_CTYPE_ANA_U:
			case EN_CTYPE_SV_U:
				// һ��ֵ��λ10mV,����ֵ����3λС��
				*pfBb = fBb12 = pfPara[wParaScd]/pfPara[wParaFst]*CN_SV_U_Unit;
				fBb21 = pfPara[wParaFst]/pfPara[wParaScd];
				break;
			case EN_CTYPE_ANA_I:
			case EN_CTYPE_SV_I:
				// CT ����Ϊö������
				// һ��ֵ��λ1mA,����ֵ����3λС��
				if (pdwPara[ptagAnaTab->wParaScd] == 1)
				{
					*pfBb = fBb12 = 5.00f/pfPara[ptagAnaTab->wParaFst];
					fBb21 = pfPara[ptagAnaTab->wParaFst]*0.2;
				}
				else
				{
					*pfBb = fBb12 = 1.00f/pfPara[ptagAnaTab->wParaFst];
					fBb21 = pfPara[ptagAnaTab->wParaFst];
				}
				break;
			default:
				*pfBb = fBb12 =fBb21= 1;
				break;
			}
		}
		if(fabs(fBb21-(*pfAnaPtCt))>0.00001)
		{
			*pfAnaPtCt   = fBb21;
			byAnaPtCtChg = TRUE;
		}
		pfAnaPtCt++;	
		ptagAnaTab++;
		pfBb++;
	}
	// ��׼�ż�����
	
	ptag_IMSam->bJzChkEna =pdwPara[EN_PARA_ENA_JZ];
	ptag_IMSam->dwJz1MkMin=pdwPara[EN_PARA_V_JZ1MIN];
	ptag_IMSam->dwJz1MkMax=pdwPara[EN_PARA_V_JZ1MAX];
	
	ptag_IMSam->dwJz2MkMin=pdwPara[EN_PARA_V_JZ2MIN];
	ptag_IMSam->dwJz2MkMax=pdwPara[EN_PARA_V_JZ2MAX];
	// ��FPGA�·���ֵУ׼ϵ������
#if(CN_TCHG_ENA)	
	// �¶ȵ���
	if(ptag_IMSam->dwCoeTMod==EN_TCHG_MOD1)
	{
		fTCoe=1.0f;
	}
	else if(ptag_IMSam->dwCoeTMod==EN_TCHG_MOD2)
	{
		fTCoe=1.0015f;
	}
	else if(ptag_IMSam->dwCoeTMod==EN_TCHG_MOD3)
	{
		fTCoe=0.9987f;
	}
#endif
	pfPara      = &g_tagPara.fPara[EN_PARA_AM_COE_STR];
	pfBb        = &(g_tagAna.fAnaPtCt[0]);
	pdwAnaAmCoe = &(g_tagAna.dwAnaAmCoe[0]);
	ptagAnaTab = &g_tAnaTab[0];
	for (i = 0; i < CN_NUM_AD; i++)
	{
		if (ptagAnaTab->wChanType == EN_CTYPE_ANA_U)
		{
			dwAnaAmCoe = (UINT32)((*pfPara)*(*pfBb)*1000*0xffff);
			dwAnaAmCoe = dwAnaAmCoe*fTCoe;
		}
		else if (ptagAnaTab->wChanType == EN_CTYPE_ANA_I)
		{
			dwAnaAmCoe = (UINT32)((*pfPara) * (*pfBb) * 2 * 0xffff);
			dwAnaAmCoe = dwAnaAmCoe*fTCoe;
		}
		else
		{
			dwAnaAmCoe = (UINT32)((*pfPara)*0xffff);
		}
		if((*pdwAnaAmCoe)!=dwAnaAmCoe)
		{
			*pdwAnaAmCoe=dwAnaAmCoe;
			byAnaAmCoeChg = TRUE;
		}
		ptagAnaTab++;
		pdwAnaAmCoe++;
		pfBb++;
		pfPara++;
	}
	
	// AD΢��ϵ������
	pwAnaAngCoe = &(g_tagAna.wAnaAngCoe[0]);
	for (i = 0; i < CN_NUM_JZ; i++)
	{
		wAnaAngCoe=pdwPara[EN_PARA_ANG_COE_STR+i];
		if(*pwAnaAngCoe!=wAnaAngCoe)
		{
			*pwAnaAngCoe=wAnaAngCoe;
			byAnaAngCoeChg = TRUE;
		}
		pwAnaAngCoe++;
		
		wAnaAngCoe=pdwPara[EN_PARA_ANG_COE_STR+CN_NUM_JZ+i];
		if(*pwAnaAngCoe!=wAnaAngCoe)
		{
			*pwAnaAngCoe=wAnaAngCoe;
			byAnaAngCoeChg = TRUE;
		}
		pwAnaAngCoe++;
	}
	
	// ֱ����������
	pwAnaDcCoe = &(g_tagAna.wAnaDcCoe[0]);
	
	for (i = 0; i < CN_NUM_AD; i++)
	{
		wAnaDcCoe=pdwPara[EN_PARA_DCBC_COE_STR+i];
		if(*pwAnaDcCoe!=wAnaDcCoe)
		{
			*pwAnaDcCoe=wAnaDcCoe;
			byAnaDcCoeChg = TRUE;
		}
		pwAnaDcCoe++;
	}
	// ��־���·����ڴ������,�ɱ�֤������ȫ�������,��һ�������У���֤�����е��ò�����ʼ�������⡣
	if(byAnaPtCtChg)
	{
		g_tagAna.byAnaPtCtChg   = TRUE;
	}
	if(byAnaAmCoeChg)
	{
		g_tagAna.byAnaAmCoeChg  = TRUE;
	}
	if(byAnaAngCoeChg)
	{
		g_tagAna.byAnaAngCoeChg = TRUE;
	}
	if(byAnaDcCoeChg)
	{
		g_tagAna.byAnaDcCoeChg  = TRUE;
	}
#if(CN_SV_IN_ENA)
	// SV��������(������CPU1)
	#if(CN_DEV_CPU1)
	if (ptag_IMSam->dwPolSvAMat != pdwPara[EN_PARA_MAT_POL_SVA])
	{
		ptag_IMSam->dwPolSvAMat = pdwPara[EN_PARA_MAT_POL_SVA];
		IES_IMSam_SvPub_Pol(EN_ANA_SVA_STR, EN_ANA_SVA_END, ptag_IMSam->dwPolSvAMat);
	}
	if (ptag_IMSam->dwPolSvBMat != pdwPara[EN_PARA_MAT_POL_SVB])
	{
		ptag_IMSam->dwPolSvBMat = pdwPara[EN_PARA_MAT_POL_SVB];
		IES_IMSam_SvPub_Pol(EN_ANA_SVB_STR, EN_ANA_SVB_END, ptag_IMSam->dwPolSvBMat);
	}
	#endif
#endif
	if(CN_NUM_SAM>32)
	{
		if (ptag_IMSam->dwPolSamMat1 != pdwPara[EN_PARA_MAT_POL_L1])
		{
			ptag_IMSam->dwPolSamMat1 = pdwPara[EN_PARA_MAT_POL_L1];
			IES_IMSam_SvPub_Pol(EN_ANA_SAM_STR, EN_ANA_SAM_STR+32, ptag_IMSam->dwPolSamMat1);
		}
		if (ptag_IMSam->dwPolSamMat2 != pdwPara[EN_PARA_MAT_POL_L2])
		{
			ptag_IMSam->dwPolSamMat2 = pdwPara[EN_PARA_MAT_POL_L2];
			IES_IMSam_SvPub_Pol(EN_ANA_SAM_STR+32, EN_ANA_SAM_END, ptag_IMSam->dwPolSamMat2);
		}
	}
	else
	{
		if (ptag_IMSam->dwPolSamMat1 != pdwPara[EN_PARA_MAT_POL_L1])
		{
			ptag_IMSam->dwPolSamMat1 = pdwPara[EN_PARA_MAT_POL_L1];
			IES_IMSam_SvPub_Pol(EN_ANA_SAM_STR, EN_ANA_SAM_END, ptag_IMSam->dwPolSamMat1);
		}
	}
}
// =============================================================================
// �������ܣ�����Ԫ����ʼ������
// �����������
// �����������
// ����ֵ��  ��
// =============================================================================

void IES_IMSam_Init()
{
	IES_memset(&gtag_IMSam,0x0,sizeof(gtag_IMSam));
	IES_RamScanAdd(&gtag_IMSam.byRamScan1);
	IES_RamScanAdd(&gtag_IMSam.byRamScan2);
	IES_RamScanAdd(&gtag_IMSam.byRamScan3);
#if(CN_HUM_ENA)
	IES_RamScanAdd(&gtag_IMSam.byRamScan4);
	IES_RamScanAdd(&gtag_IMSam.byRamScan5);
#endif
	IES_RamScanAdd(&gtag_IMSam.byRamScan6);
	IES_RamScanAdd(&gtag_IMSam.byRamScan7);
	IES_RamScanAdd(&gtag_IMSam.byRamScan8);
	IES_RamScanAdd(&gtag_IMSam.byRamScan9);
	IES_RamScanAdd(&gtag_IMSam.byRamScan10);
	IES_RamScanAdd(&gtag_IMSam.byRamScan11);
	IES_RamScanAdd(&gtag_IMSam.byRamScan12);
	IES_RamScanAdd(&gtag_IMSam.byRamScan13);
	IES_RamScanAdd(&gtag_IMSam.byRamScan14);
	IES_RamScanAdd(&gtag_IMSam.byRamScan15);
	IES_RamScanAdd(&gtag_IMSam.byRamScan16);
	IES_RamScanAdd(&gtag_IMSam.byRamScan17);
	IES_RamScanAdd(&gtag_IMSam.byRamScan18);
	IES_RamScanAdd(&gtag_IMSam.byRamScan19);
	IES_RamScanAdd(&gtag_IMSam.byRamScan20);
	IES_RamScanAdd(&gtag_IMSam.byRamScan21);
	IES_RamScanAdd(&gtag_IMSam.byRamScan22);
	IES_RamScanAdd(&gtag_IMSam.byRamScan23);
	IES_RamScanAdd(&gtag_IMSam.byRamScan24);
}
// =============================================================================
// �������ܣ�ģ����Ʒ�ʺϳ�
// �����������
// �����������
// ����ֵ��  ��
//           SV��������Ʒ�ʺϳ��߼���
//           1.AD��׼�쳣,��ӦAD�ϵ�ģ������Ʒ�ʣ���ʱ��Ч
//           2.PTCT���쳣,��ӦPTCT�ϵ�ģ������Ʒ����Ч
//           3.��������Ʒ��ת��
//           4.��������δ����,Ʒ����Ч
//           5.�������ݶ���,Ʒ����Ч
//           6.����ѹ��Ͷ��,����Ʒ�ʼ���
// =============================================================================
void IES_IMSam_Q()
{
	const    tagAnaTab  *ptagAnaTab;
	register UINT32     *pdwAnaQ,dwAnaQ;
	// SV�����Լ��־
	register BOOL     bSvPubQErr=FALSE, bSvPubCfgErr, bQchg=FALSE;;
	register BOOL     *pbJzChk,*pbBoard;
	register WORD     i;
	register UINT32   dwADErr=0,dwBoardErr=0;
	register WORD     *pwSvPubSend,wSvPubSend;
    // SV�������쳣��־
    BOOL     bSvErrAll=FALSE;
#if(CN_SV_IN_ENA)
	register UINT32   *pdwSvQ,*pdwSvCbStatus,dwSvCbStatus;
	#if(CN_DEV_CPU1)
	register BOOL     *pbSvSub;
	register BYTE     *pbySvCb,bySvCb;
	#endif	
	// SV�����Լ��־
	BOOL     bSvCbLinkErr=FALSE,bSvCbDatErr=FALSE,bSvSubCfgErr;
	// SV���������Լ��־
	BOOL     bSvAQErr=FALSE,    bSvBQErr=FALSE;
	BOOL     bSvATest=FALSE,    bSvBTest=FALSE;
    #if(CN_DEV_CPU1)
	register UINT32  *pdwSvCbSubCfg;
	pdwSvCbSubCfg =g_tagAna.dwSvCbSubCfg;
    #endif
	pdwSvCbStatus =g_tagAna.dwSvCbStatus;
#endif
#if(CN_SV_IN_ENA)
// 1.���ƿ�����Լ�
	for(i=0;i<CN_NUM_BOARD_SV;i++)
	{
		// 1.1���ƿ������쳣�Լ�
		//if(pdwSvCbSubCfg[i])
		//{
		//	bSvCbCfgErr=TRUE;
		//}	
		// 1.2���ƿ��־���Լ�
		dwSvCbStatus = pdwSvCbStatus[i];
		if(dwSvCbStatus&CN_SVCB_Ena)
		{
			// ��·�ж�
			if(dwSvCbStatus&CN_SVCB_LinkErr1)
			{
				bSvCbLinkErr=TRUE;
				G_Set_AlmIn_All(EN_ALM_SVSUB_COM01+i,TRUE,dwSvCbStatus,0,0);
				G_Set_AlmIn(EN_ALM_SVSUB_TEST01+i,FALSE);
				G_Set_AlmIn(EN_ALM_SVSUB_DAT01+i,FALSE);
				G_Set_AlmIn(EN_ALM_SVSUB_SYN01+i,FALSE);
			}
			else
			{
				G_Set_AlmIn(EN_ALM_SVSUB_COM01+i,FALSE);
				
				// ���ޱ�־
				if(((dwSvCbStatus&CN_SVCB_Test)?TRUE:FALSE)^(g_tagPub.bSysTest))
				{
					G_Set_AlmIn_All(EN_ALM_SVSUB_TEST01+i,TRUE,dwSvCbStatus,0,0);
				}
				else
				{
					G_Set_AlmIn(EN_ALM_SVSUB_TEST01+i,FALSE);
				}
				// �����쳣
				if(dwSvCbStatus&CN_SVCB_DataErr)
				{
					bSvCbDatErr=TRUE;
					G_Set_AlmIn_All(EN_ALM_SVSUB_DAT01+i,TRUE,dwSvCbStatus,0,0);
				}
				else
				{
					G_Set_AlmIn(EN_ALM_SVSUB_DAT01+i,FALSE);
				}
				// ͬ���쳣
				if(dwSvCbStatus&CN_SVCB_SynErr)
				{
					G_Set_AlmIn_All(EN_ALM_SVSUB_SYN01+i,TRUE,dwSvCbStatus,0,0);
				}
				else
				{
					G_Set_AlmIn(EN_ALM_SVSUB_SYN01+i,FALSE);
				}
			}
		}
	}
#endif
	// 2.SV����Ʒ�ʺϳ�
	pbJzChk    =&(gtag_IMSam.bJzChk[0]);
	pdwAnaQ    =&(g_tagAna.dwAnaQ[0]);
	ptagAnaTab =&(g_tAnaTab[0]);
	pbBoard    =&(g_tChkState.bChkOut[EN_CHK_BOARD_SAM_STR]);
	for(i=0;i<CN_NUM_SAM;i++)
	{
		dwAnaQ=0;
		// AD��׼�Լ�
		if(ptagAnaTab->wADNo<CN_NUM_JZ)
		{
			if(pbJzChk[ptagAnaTab->wADNo])
			{
				dwAnaQ|=(CN_SV_Q_VALIDL+CN_SV_Q_DETAIL03);
				dwADErr|=g_dwBit[ptagAnaTab->wADNo];
			}
		}
		// PTCT�忨�Լ�
		if(ptagAnaTab->wFrmNo<CN_NUM_BOARD_SAM)
		{
			if(pbBoard[ptagAnaTab->wFrmNo])
			{
				dwAnaQ|=(CN_SV_Q_VALIDL+CN_SV_Q_DETAIL05);
				dwBoardErr|=g_dwBit[ptagAnaTab->wFrmNo];
			}
		}
		// 2.3 ����Ʒ��
		if(g_tagPub.bSysTest)
		{
			dwAnaQ|=CN_SV_Q_TEST;
		}
		
		if(*pdwAnaQ!=dwAnaQ)
		{
			*pdwAnaQ=dwAnaQ;
			bQchg=TRUE;
		}
		pdwAnaQ++;
		ptagAnaTab++;
	}
#if(CN_SV_IN_ENA)
	pdwAnaQ    =&(g_tagAna.dwAnaQ[EN_ANA_SV_STR]);
	ptagAnaTab =&(g_tAnaTab[EN_ANA_SV_STR]);
	pdwSvQ     =g_tagAna.dwSvQ;
	#if(CN_DEV_CPU1)
	pbySvCb    =g_tagAna.bySvCb;
	pbSvSub    =g_tagAna.bSvSub;
	// PT�л�ͬʱ���ر�־
	#endif
	for(i=EN_ANA_SV_STR;i<EN_ANA_SV_END;i++)
	{
		dwAnaQ=0;
	#if(CN_DEV_CPU1)
		bySvCb=*pbySvCb++;
		// ���������޶���
		if(*pbSvSub++)
		{
			if(bySvCb<CN_NUM_BOARD_SV)
			{
				// ���ƿ�����쳣
				if(pdwSvCbSubCfg[bySvCb]&CN_SVCFG_DataErr)
				{
					dwAnaQ|=CN_SV_Q_VALIDL;
				}
				if(pdwSvCbStatus[bySvCb]&CN_SVCB_Ena)
				{
					// �������ݶ����������쳣
					if(pdwSvCbStatus[bySvCb]&CN_SVCB_Link_QErr)
					{
						dwAnaQ|=CN_SV_Q_VALIDL;
					}
					
					if(G_Get_Flag(EN_FLAG_V_NULL))
					{
						dwAnaQ|=CN_SV_Q_VCLR;
					}
					
				}
				// ���ƿ�δʹ�� Ʒ����Ч
				else
				{
					dwAnaQ|=CN_SV_Q_VALIDL;
				}
				// SVƷ�ʺϲ�
				dwAnaQ|=(*pdwSvQ);
			}
			// ���ƿ�ӳ����� Ʒ����Ч
			else
			{
				dwAnaQ|=CN_SV_Q_VALIDL;
			}
			// �Ѷ��ĵļ���������Ч
			if(dwAnaQ&CN_SV_Q_VALIDL)
			{
				// ����A��
				if((i<EN_ANA_SVA_END))
				{
					bSvAQErr=TRUE;
				}
				// ����B��
				else
				{
					bSvBQErr=TRUE;
				}
			}
			// �Ѷ��ĵļ������ݼ���
			if(dwAnaQ&CN_SV_Q_TEST)
			{
				// ����A��
				if(i<EN_ANA_SVA_END)
				{
					bSvATest=TRUE;
				}
				// ����B��
				else
				{
					bSvBTest=TRUE;
				}
			}
		}
		else
		{
			dwAnaQ|=CN_SV_Q_VALIDL;
		}
	#elif(CN_DEV_CPU2)
		dwAnaQ|=(*pdwSvQ);
	#endif
	
		// 2.3 ����Ʒ��
		if(g_tagPub.bSysTest)
		{
			dwAnaQ|=CN_SV_Q_TEST;
		}
		// 2.4 �ϵ��ѹ�л�����״̬,Ʒ����Ч
		if(G_Get_Flag(EN_FLAG_V_BC_INIT))
		{
			dwAnaQ|=CN_SV_Q_VALIDL;
		}
		
		if(*pdwAnaQ!=dwAnaQ)
		{
			*pdwAnaQ=dwAnaQ;
			bQchg=TRUE;
		}
		pdwSvQ++;
		pdwAnaQ++;
		ptagAnaTab++;
	}
#endif
	// ����������Ч�澯
	if(bQchg)
	{
		pdwAnaQ     =&(g_tagAna.dwAnaQ[0]);
		pwSvPubSend =&(g_tagAna.wSvPubSend[0]);
		for(i=0;i<g_tagAna.wSvPubNum;i++)
		{
			wSvPubSend=pwSvPubSend[i]&(CN_SV_Pub_Index1);
			if(wSvPubSend<CN_NUM_ANA)
			{
				if(pdwAnaQ[wSvPubSend]&CN_SV_Q_VALIDL)
				{
					bSvPubQErr=TRUE;
					break;
				}
			}
			if(pwSvPubSend[i]&CN_SV_Pub_Cal)
			{
				wSvPubSend=pwSvPubSend[i]&(CN_SV_Pub_Index2);
				wSvPubSend=wSvPubSend>>7;
				if(wSvPubSend<CN_NUM_ANA)
				{
					if(pdwAnaQ[wSvPubSend]&CN_SV_Q_VALIDL)
					{
						bSvPubQErr=TRUE;
						break;
					}
				}
			}
		}
		G_Set_AlmIn(EN_ALM_SVPUB_INVALID,bSvPubQErr);
	}
	// ����������Ч
	bSvPubQErr=G_Get_AlmIn_P[EN_ALM_SVPUB_INVALID];
	g_tagAna.byAnaQChg=bQchg;
	// 3.��ظ澯���
	// �����쳣�澯
	if(dwADErr||dwBoardErr)
	{
		G_Set_AlmIn_All(EN_ALM_SAM,TRUE,dwADErr,dwBoardErr,0);
	}
	else
	{
		G_Set_AlmIn(EN_ALM_SAM,FALSE);
	}
#if(CN_SV_IN_ENA)
	// SV������ظ澯
	G_Set_AlmIn(EN_ALM_SVLINK_QA,bSvAQErr);
	G_Set_AlmIn(EN_ALM_SVLINK_QB,bSvBQErr);
	G_Set_AlmIn(EN_ALM_SVLINK_TESTA,bSvATest);
	G_Set_AlmIn(EN_ALM_SVLINK_TESTB,bSvBTest);
	// ����ܵ�SV���������쳣
	bSvErrAll|=bSvCbLinkErr|bSvCbDatErr|bSvAQErr|bSvBQErr;
	G_Set_AlmIn(EN_ALM_SVSUB,bSvErrAll);
	// SV�����������쳣
	bSvSubCfgErr=G_Get_Inter(EN_INTER_SVSUB_CFG);
	bSvErrAll|=(bSvSubCfgErr);
	G_Set_AlmIn(EN_ALM_LINK,bSvErrAll);
#endif
	bSvPubCfgErr=G_Get_Inter(EN_INTER_SVPUB_CFG);
	bSvErrAll|=bSvPubQErr|bSvPubCfgErr;
	G_Set_AlmIn(EN_ALM_SV,bSvErrAll);
}

// =============================================================================
// �������ܣ�����Ԫ��ִ�к���
// �����������
// �����������
// ����ֵ��  ��
// =============================================================================
void IES_IMSam()
{
	tag_IMSam *ptag_IMSam;
	ptag_IMSam=&gtag_IMSam;
	// Ԫ������
	if(ptag_IMSam->dwBs)
	{
		return;
	}
	// ��������ˢ��
	IES_IMSam_In(ptag_IMSam);
	// �ϵ������
	if(!ptag_IMSam->dwPWInit)
	{
		ptag_IMSam->dwPWInit=TRUE;
	}
	// ��׼���㼰�Լ�
	IES_IMSam_JZ(ptag_IMSam);
#if(CN_TCHG_ENA)	
	// �¶ȸ��²���
	IES_IMSam_TChg_Para(ptag_IMSam);
#endif	
	// �������¹�����,��������(�ݶ���������������)
	if(ptag_IMSam->dwInit)
	{
		IES_IMSam_Reset();
		ptag_IMSam->dwInit=FALSE;
		return;
	}
	// ��������Ž��м���
	if(!(G_Get_Inter(EN_INTER_OPT_ANA)
	||G_Get_Inter(EN_INTER_OPT_ANA_J)
	||G_Get_Inter(EN_INTER_OPT_ANA_FR)))
	{
		// ���ӱ�־����,���͸���
		if(ptag_IMSam->dwMenuInit)
		{
			IES_IMSam_Reset();
			ptag_IMSam->dwMenuInit=FALSE;
		}
		return;
	}
	ptag_IMSam->dwMenuInit=TRUE;
	// ��Ƶ
	if(!G_Get_Const_Chk(EN_DTYPE_CAL))
	{
		IES_IMSam_Fr(ptag_IMSam);
	}
	// ����������ʱ
	if(!ptag_IMSam->dwWaveFlag)
	{
		IES_IMSam_Cal(ptag_IMSam);
	}
	// ������Ƶ�ʰ���
	else
	{
		IES_IMSam_Out(ptag_IMSam);
		ptag_IMSam->dwWaveFlag=FALSE;
	}
}

