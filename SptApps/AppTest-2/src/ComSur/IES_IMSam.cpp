/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * 积成电子股份有限公司
 * 元件名称：采样元件
 * 元件描述：采样元件
 * 元件功能：采样数据相量计算及输出
 * 元件版本：V1.00
 * 定版时间：2020-2-24
 * 版本修改：
 * <版本号> <修改日期>, <修改人员>: <修改功能概述> 
 * V1.00 2021-2-24 刘志利：初版
 *================================================================================*/
#include "IES_IMSam.h"
/*================================================================================*/
// 元件私有变量出口
tag_IMSam     gtag_IMSam;
// ============================================================================
// 宏定义函数功能：幅值实虚部开方
// ============================================================================
#define IES_CAL_AmpSqrt(iRe, iIm)  sqrt((INT64)iRe*iRe + (INT64)iIm*iIm)
// ============================================================================
// 宏定义功能：根据实虚部计算相角,范围0.000～360.000度
// ============================================================================
#define IES_CAL_Angle(iRe,iIm)  (iIm >= 0)?(atan2(iIm,iRe)*180000/3.14159265):(360000+(atan2(iIm,iRe)*180000/3.14159265));
// =============================================================================
// 函数功能：实时数据自检
// 输入参数：无
// 输出参数：无
// 返回值：  无
// =============================================================================
BOOL IES_IMSam_Chk(tag_IMSam *ptag_IMSam)
{
	// 帧序号跳变判断
	if(g_tagAna.dwAnaFramDNum>1)
	{
		ptag_IMSam->dwJumpCnt++;
	}
	// 无帧判断
	else if(g_tagAna.dwAnaFramDNum==0)
	{
		ptag_IMSam->dwLostCnt++;
		return TRUE;
	}
	return FALSE;
}

// =============================================================================
// 函数功能：实时数据刷新(上送一次值)
// 输入参数：无
// 输出参数：无
// 返回值：  无
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
		// 解析AD数
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
// 函数功能：基准电压计算
// 输入参数：无
// 输出参数：无
// 返回值：  无
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
	// 一次值计算
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
// 函数功能：相量运算
// 输入参数：无
// 输出参数：无
// 返回值：  无
// =============================================================================
void IES_IMSam_Cal(tag_IMSam *ptag_IMSam)
{
	INT64   *piReal,*piImag;          // 实部、虚部
	UINT64   *pdwAm;                  // 幅值
	register  INT32    *piBuf,iBuf;             // 缓存
	register  DWORD     dwPtr;                   // 指针
	register  UINT32     i;
#if(CN_HUM_ENA)	
	INT64   *piHumReal,*piHUmImag;    // 谐波实部、虚部
	register  DWORD     dwHumPtr;                // 指针
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
		//基波相量计算
		*piReal+=(iBuf*g_iCos80[dwPtr]);
		*piImag+=(-iBuf*g_iSin80[dwPtr]);
		 piReal++;
		 piImag++;
	#if(CN_HUM_ENA)
		//2~13次谐波计算
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
		//积分计算(容易溢出,直接乘系数)
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
		//基波相量计算
		*piReal+=(iBuf*g_iCos80[dwPtr]);
		*piImag+=(-iBuf*g_iSin80[dwPtr]);
		 piReal++;
		 piImag++;
	#if(CN_HUM_ENA)
		//2~13次谐波计算
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
		//积分计算(容易溢出,直接乘系数)
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
// 函数功能：相量运算
// 输入参数：无
// 输出参数：无
// 返回值：  无
// 降低负载,暂时去掉门槛限制
// =============================================================================
void IES_IMSam_Fr(tag_IMSam *ptag_IMSam)
{
	register UINT32     i;
	register WORD       wIndex=0;
	register INT32     *piBuf,*piBufBak,iBuf,iBufBak;    // 缓存
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
		// 配置检查
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
				// 计算补偿
				dwFBc    =CN_CAL_F_Coe*iBuf/(iBuf-iBufBak);
				*pdwFDly+=(CN_CAL_F_Coe-dwFBc+(*pdwFBc));
				*pdwFBc  =dwFBc;
				// 计算频率
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
// 函数功能：相量/幅值/相位输出
// 输入参数：无
// 输出参数：无
// 返回值：  无
// =============================================================================
void IES_IMSam_Out(tag_IMSam *ptag_IMSam)
{
	register UINT32     i;
	register tagVector *ptVectorFst,*ptVector;
	const    tagAnaTab  *ptagAnaTab;
	register UINT32   dwAm,dwAmJ,dwAngle,dwAngleBase=0;
	register UINT32   *pdwFrDst,*pdwFrSrc;
	UINT64   *pdwAm;	
	register INT32    iReal, iImag;          // 实部、 虚部
	INT64    *piReal, *piImag;      // 实部、虚部
	register FLOAT32  *pfBb;                 // 通道系数
	register FLOAT32  fBb;                   // 一二次转换变比

	register DWORD    *pdwAdjAmBuf,*pdwAdjAmMin,*pdwAdjAmMax;                                         // 幅值校准缓存
	register DWORD    *pdwAdjAngAmMin,*pdwAdjAngAmMax;                // 相位校准幅值缓存
	register INT32    *piAdjAngBuf,*piAdjAngMin,*piAdjAngMax;      // 相位校准缓存
	register INT32    iAngle;
	register BOOL     bAngleBase=FALSE;

#if(CN_HUM_ENA)
	tagVector *ptVectorHum;
	INT64     *piHumReal, *piHumImag;   // 谐波实部、虚部
	WORD      j;
#endif
	// 一次值计算
		
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
		
		//相量转存
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
		// 自动校准配合
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
			// 最后一个通道进行累计
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
		// 基准相位自适应,暂时以第一个正常电压为基准
		if (!bAngleBase)
		{
			// 要求常量表电压通道必须在前
			if ((ptagAnaTab[i].wChanType == EN_CTYPE_ANA_U) && (ptVector->dwAmJ > CN_BASE_UMK))
			{
				dwAngleBase = dwAngle;
				bAngleBase = TRUE;
			}
		}
		ptVector++;
		ptVectorFst++;
	#if(CN_HUM_ENA)
		//谐波搬移
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
		
		//相量转存
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
		// 基准相位自适应,暂时以第一个正常电压为基准
		if (!bAngleBase)
		{
			// 要求常量表电压通道必须在前
			if ((ptagAnaTab[i].wChanType == EN_CTYPE_SV_U) && (ptVector->dwAmJ > CN_BASE_UMK))
			{
				dwAngleBase = dwAngle;
				bAngleBase = TRUE;
			}
		}
		ptVector++;
		ptVectorFst++;
	#if(CN_HUM_ENA)
		//谐波搬移
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
	// 更新经基准判断后的相位
	ptVectorFst =&g_tagAna.tAnaVectFst[0];
	ptVector    =&g_tagAna.tAnaVect[0];
	ptagAnaTab = &g_tAnaTab[0];
	for(i=0;i<CN_NUM_SAM;i++)
	{
		// 判断幅值
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
		// 相位自动校准配合(取相对值)
		if(ptag_IMSam->bAdjAngStr)
		{
			iAngle =(ptVector->dwAngleRel>180000)?(INT32)(ptVector->dwAngleRel-360000):(INT32)(ptVector->dwAngleRel);
			dwAmJ   =ptVector->dwAmJ;
			*piAdjAngBuf+=iAngle;
			// 记录幅值波动
			if(dwAmJ<(*pdwAdjAngAmMin))
			{
				*pdwAdjAngAmMin=dwAmJ;
			}
			if(dwAmJ>(*pdwAdjAngAmMax))
			{
				*pdwAdjAngAmMax=dwAmJ;
			}
			// 记录相位波动
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
	// 更新经基准判断后的相位
	ptVectorFst =&g_tagAna.tAnaVectFst[EN_ANA_SV_STR];
	ptVector    =&g_tagAna.tAnaVect[EN_ANA_SV_STR];
	ptagAnaTab = &g_tAnaTab[EN_ANA_SV_STR];
	for(i=EN_ANA_SV_STR;i<EN_ANA_SV_END;i++)
	{
		// 判断幅值
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
		// 相位自动校准配合(取相对值)
		ptVector++;
		ptVectorFst++;
		ptagAnaTab++;
	}
#endif	
	g_tagAna.byAnaVecChg=TRUE;
	// 频率搬移
	pdwFrDst=&(g_tagAna.dwFrCal[0]);
	pdwFrSrc=&ptag_IMSam->dwFCal[0];
	for(i=0;i<CN_NUM_CAL;i++)
	{
		*pdwFrDst++=*pdwFrSrc++;
	}
	g_tagAna.byFrChg=TRUE;
}

// =============================================================================
// 函数功能：启动自动校准
// 输入参数：无
// 输出参数：无
// 返回值：  无
// =============================================================================
BOOL IES_IMSam_AdJAm_Str(WORD wAdjNum)
{
	tag_IMSam *ptag_IMSam;
	// 自动校准中间数据初始化
	// 最大1000周波
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
	// 自动校准启动标志一定放在最后(此处顺序不能变！！！)
	ptag_IMSam->bAdjAmStr=TRUE;
	
	return FALSE;
}

// =============================================================================
// 函数功能：幅值自动校准主函数(仅在任务中调用)
// 输入参数：无
// 输出参数：无
// 返回值：0:全部校准失败,No:No个通道校准成功
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
			// 电压通道:幅值+频率判断
			if(wChanType==EN_CTYPE_ANA_U)
			{
				// 电压幅值波动不得超过0.5V
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
			// 电流通道
			else if(wChanType==EN_CTYPE_ANA_I)
			{
				if (pdwPara[ptagAnaTab[i].wParaScd] == 1)
				{
					// 1A额定值,电流幅值波动不得超过0.02A
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
					// 1A额定值,电流幅值波动不得超过0.1A
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
			// 系数微调范围判断
			if((iParaChg<iParaDefMin)||(iParaChg>iParaDefMax))
			{
				pbChn[i]=FALSE;
				continue;
			}
			pdwParaBak[wParaCoe] = iParaChg;
			dwAdjNo++;
			pbChn[i]=TRUE;
		}
		// 参数更新标志
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
// 函数功能：直流启动自动校准
// 输入参数：无
// 输出参数：无
// 返回值：  无
// =============================================================================
BOOL IES_IMSam_AdJDc_Str(WORD wAdjNum)
{
	tag_IMSam *ptag_IMSam;
	// 自动校准中间数据初始化
	// 最大100周波
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
	// 自动校准启动标志一定放在最后(此处顺序不能变！！！)
	ptag_IMSam->bAdjDcStr=TRUE;
	
	return FALSE;
}

// =============================================================================
// 函数功能：直流自动校准主函数(仅在任务中调用)
// 输入参数：无
// 输出参数：无
// 返回值：0:全部校准失败,No:No个通道校准成功
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
	// 自动校准中间数据初始化
	if(pbChn==NULL)
	{
		return dwAdjNo;
	}
	ptag_IMSam=&gtag_IMSam;
	// 暂时不考虑基准的校准
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
			// 系数微调范围判断
			if((iCoe>iParaDefMax)||(iCoe<iParaDefMin))
			{
				pbChn[i]=FALSE;
				continue;
			}
			pdwParaBak[wParaDc] = iCoe;
			dwAdjNo++;
			pbChn[i]=TRUE;
		}
		// 参数更新标志
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
// 函数功能：启动相位自动校准
// 输入参数：无
// 输出参数：无
// 返回值：  无
// =============================================================================
BOOL IES_IMSam_AdJAng_Str(WORD wAdjNum)
{
	tag_IMSam *ptag_IMSam;
	// 最大支持1000周波
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
	// 自动校准启动标志一定放在最后(此处顺序不能变！！！)
	ptag_IMSam->bAdjAngStr=TRUE;
	return FALSE;
}

// =============================================================================
// 函数功能：相位自动校准主函数(仅在任务中调用)
// 输入参数：无
// 输出参数：无
// 返回值：0:全部校准失败,No:No个通道校准成功
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
		// 基准电压相位选择Ua AD1
		if((ptag_IMSam->dwAdjAngAmMax[CN_BASE_AD]>101000)
		||(ptag_IMSam->dwAdjAngAmMin[CN_BASE_AD]<99000))
		{
			return dwAdjNo;
		}
		iAngBase=ptag_IMSam->iAdjAngBuf[CN_BASE_AD];
		// 基准电压相位选择 end
		for(i=0;i<CN_NUM_AD;i++)
		{
			// 判断是否是AD芯片0通道或4通道
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
			// 幅值范围判断
			if(ptagAnaTab[i].wChanType==EN_CTYPE_ANA_U)
			{
				// 电压幅值范围[99V,101V]
				if((ptag_IMSam->dwAdjAngAmMax[i]>101000)
				||(ptag_IMSam->dwAdjAngAmMin[i]<99000))
				{
					*pbChn++=FALSE;
					continue;
				}
			}
			else if(ptagAnaTab[i].wChanType==EN_CTYPE_ANA_I)
			{
				// 电流幅值范围[0.95In,1.05In]
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
			// 相位范围判断（相位波动超过2度,校准失败）
			if(abs(ptag_IMSam->iAdjAngMax[i]-ptag_IMSam->iAdjAngMin[i])>2000)
			{
				*pbChn++=FALSE;
				continue;
			}
			// 100周波相位与基准角度差(不大于200°)
			if(abs(iAngBase-ptag_IMSam->iAdjAngBuf[i])>2000*wAdjNum)
			{
				*pbChn++=FALSE;
				continue;
			}
			// 相位差计算
			iDAng=(iAngBase-ptag_IMSam->iAdjAngBuf[i]);
			// 时间参数转换(0.001°=(2/36)us)
			iDTns=iDAng*20/(36*wAdjNum);

			iParaDefMin=g_tParaTab[wAdPara].iValMin;
			iParaDefMax=g_tParaTab[wAdPara].iValMax;
			
			iParaChg=pdwPara[wAdPara]+iDTns;
			
			if((iParaChg<iParaDefMin)||(iParaChg>iParaDefMax))
			{
				*pbChn++=FALSE;
				continue;
			}
			// 系数微调范围判断
			pdwParaBak[wAdPara] = iParaChg;
			dwAdjNo++;
			*pbChn++=TRUE;
		}
		// 参数更新标志
		//if(dwAdjNo)
		//{
		//	g_tagPara.dwChgWRef[EN_BOARD_PARA_ANG_COE]=TRUE;
		//}
	}
	return dwAdjNo;
}
#if(CN_SV_IN_ENA)
// =============================================================================
// 函数功能：SV订阅配置初始化函数
// 输入参数：无
// 输出参数：无
// 返回值：  无
// =============================================================================

void IES_IMSam_SvSub_Init()
{
#if(CN_DEV_CPU1)

	WORD i;
	BOOL *pbSvSub;
	BYTE *pbySvCb;
	BYTE  bySvCbA1=0xAA,bySvCbA2=0xAA,bySvCbB1=0xAA,bySvCbB2=0xAA;

	pbSvSub=g_tagAna.bSvSub;                    // SV订阅标志
	pbySvCb=g_tagAna.bySvCb;                    // SV订阅控制块映射(需要自检)
	// 订阅控制块个数自检
	for(i=0;i<EN_LINK_END;i++)
	{
		// A套I母线电压有订阅/未全订阅/电压跨控制块订阅判断
		if(pbSvSub[i])
		{
			G_Set_Inter(EN_INTER_SVSUB_A1_CFG,TRUE);
			// 记录第一个控制块号
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
		// A套II母线电压有订阅/未全订阅/电压跨控制块订阅判断
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
		// B套I母线电压有订阅/未全订阅/电压跨控制块订阅判断
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
		// B套II母线电压有订阅/未全订阅/电压跨控制块订阅判断
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
		// A套I、II母订阅不一致
		if(pbSvSub[i]^pbSvSub[i+EN_LINK_END])
		{
			G_Set_Inter(EN_INTER_SVSUB_A_DIS,TRUE);
		}
		// A套I、II母跨控制块订阅
		if((pbSvSub[i]&pbSvSub[i+EN_LINK_END])
		&&(pbySvCb[i]!=pbySvCb[i+EN_LINK_END]))
		{
			G_Set_Inter(EN_INTER_SVSUB_A_MULT,TRUE);
		}
		// B套I、II母订阅不一致
		if(pbSvSub[i+EN_LINK_END*2]^pbSvSub[i+EN_LINK_END*3])
		{
			G_Set_Inter(EN_INTER_SVSUB_B_DIS,TRUE);
		}
		// B套I、II母跨控制块订阅
		if((pbSvSub[i+EN_LINK_END*2]&pbSvSub[i+EN_LINK_END*3])
		&&(pbySvCb[i+EN_LINK_END*2]!=pbySvCb[i+EN_LINK_END*3]))
		{
			G_Set_Inter(EN_INTER_SVSUB_B_MULT,TRUE);
		}
		// A、B套I母订阅不一致
		if(pbSvSub[i]^pbSvSub[i+EN_LINK_END*2])
		{
			G_Set_Inter(EN_INTER_SVSUB_1M_DIS,TRUE);
		}
		// A、B套II母订阅不一致
		if(pbSvSub[i+EN_LINK_END]^pbSvSub[i+EN_LINK_END*3])
		{
			G_Set_Inter(EN_INTER_SVSUB_2M_DIS,TRUE);
		}
	}
	// 母线板(CPU2)在任何情况下判断为单母线单套订阅
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
	// A套I母有效判断
	if(G_Get_Inter(EN_INTER_SVSUB_A1_CFG)
		&&(!G_Get_Inter(EN_INTER_SVSUB_A1_MULT)))
	{
		G_Set_Inter(EN_INTER_SVSUB_A1_VALID,TRUE);
	}
	// A套II母有效判断
	if(G_Get_Inter(EN_INTER_SVSUB_A2_CFG)
		&&(!G_Get_Inter(EN_INTER_SVSUB_A2_MULT)))
	{
		G_Set_Inter(EN_INTER_SVSUB_A2_VALID,TRUE);
	}
	// B套I母有效判断
	if(G_Get_Inter(EN_INTER_SVSUB_B1_CFG)
		&&(!G_Get_Inter(EN_INTER_SVSUB_B1_MULT)))
	{
		G_Set_Inter(EN_INTER_SVSUB_B1_VALID,TRUE);
	}
	// B套II母有效判断
	if(G_Get_Inter(EN_INTER_SVSUB_B2_CFG)
		&&(!G_Get_Inter(EN_INTER_SVSUB_B2_MULT)))
	{
		G_Set_Inter(EN_INTER_SVSUB_B2_VALID,TRUE);
	}
	// 单母线仅A套订阅:A套I母订阅有效且其他母线均无订阅
	if(G_Get_Inter(EN_INTER_SVSUB_A1_VALID)&&(!G_Get_Inter(EN_INTER_SVSUB_A2_CFG))&&(!G_Get_Inter(EN_INTER_SVSUB_B1_CFG))&&(!G_Get_Inter(EN_INTER_SVSUB_B2_CFG)))
	{
		G_Set_Inter(EN_INTER_SVSUB_1M_1LINKA,TRUE);
		G_Set_Inter(EN_INTER_SVSUB_A_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_B_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_1M_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_2M_DIS,FALSE);
	}
	// 单母线仅B套订阅:B套I母订阅有效且其他母线均无订阅
	else if((!G_Get_Inter(EN_INTER_SVSUB_A1_CFG))&&(!G_Get_Inter(EN_INTER_SVSUB_A2_CFG))&&G_Get_Inter(EN_INTER_SVSUB_B1_VALID)&&(!G_Get_Inter(EN_INTER_SVSUB_B2_CFG)))
	{
		G_Set_Inter(EN_INTER_SVSUB_1M_1LINKB,TRUE);
		G_Set_Inter(EN_INTER_SVSUB_A_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_B_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_1M_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_2M_DIS,FALSE);
	}
	// 单母线双套订阅
	else if(G_Get_Inter(EN_INTER_SVSUB_A1_VALID)&&(!G_Get_Inter(EN_INTER_SVSUB_A2_CFG))&&G_Get_Inter(EN_INTER_SVSUB_B1_VALID)&&(!G_Get_Inter(EN_INTER_SVSUB_B2_CFG)))
	{
		G_Set_Inter(EN_INTER_SVSUB_1M_2LINK,TRUE);
		G_Set_Inter(EN_INTER_SVSUB_A_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_B_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_2M_DIS,FALSE);
	}
	// 双母线仅A套订阅
	else if(G_Get_Inter(EN_INTER_SVSUB_A1_VALID)&&G_Get_Inter(EN_INTER_SVSUB_A2_VALID)&&(!G_Get_Inter(EN_INTER_SVSUB_B1_CFG))&&(!G_Get_Inter(EN_INTER_SVSUB_B2_CFG)))
	{
		G_Set_Inter(EN_INTER_SVSUB_2M_1LINKA,TRUE);
		G_Set_Inter(EN_INTER_SVSUB_B_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_1M_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_2M_DIS,FALSE);
	}
	// 双母线仅B套订阅
	else if((!G_Get_Inter(EN_INTER_SVSUB_A1_CFG))&&(!G_Get_Inter(EN_INTER_SVSUB_A2_CFG))&&G_Get_Inter(EN_INTER_SVSUB_B1_VALID)&&G_Get_Inter(EN_INTER_SVSUB_B2_VALID))
	{
		G_Set_Inter(EN_INTER_SVSUB_2M_1LINKB,TRUE);
		G_Set_Inter(EN_INTER_SVSUB_A_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_1M_DIS,FALSE);
		G_Set_Inter(EN_INTER_SVSUB_2M_DIS,FALSE);
	}	
	// 双母线双套订阅
	else if(G_Get_Inter(EN_INTER_SVSUB_A1_VALID)&&G_Get_Inter(EN_INTER_SVSUB_A2_VALID)&&G_Get_Inter(EN_INTER_SVSUB_B1_VALID)&&G_Get_Inter(EN_INTER_SVSUB_B2_VALID))
	{
		G_Set_Inter(EN_INTER_SVSUB_2M_2LINK,TRUE);
	}
	// A套无订阅
	if(!(G_Get_Inter(EN_INTER_SVSUB_A1_CFG)||G_Get_Inter(EN_INTER_SVSUB_A2_CFG)))
	{
		G_Set_AlmIn(EN_ALM_SVLINK_NOCFGA,TRUE);
	}
	// B套无订阅
	if(!(G_Get_Inter(EN_INTER_SVSUB_B1_CFG)||G_Get_Inter(EN_INTER_SVSUB_B2_CFG)))
	{
		G_Set_AlmIn(EN_ALM_SVLINK_NOCFGB,TRUE);
	}
	// A套订阅配置异常
	if(G_Get_Inter(EN_INTER_SVSUB_A1_MULT)||G_Get_Inter(EN_INTER_SVSUB_A2_MULT)
		||G_Get_Inter(EN_INTER_SVSUB_A_DIS)||G_Get_Inter(EN_INTER_SVSUB_A_MULT)
		||G_Get_Inter(EN_INTER_SVSUB_1M_DIS)||G_Get_Inter(EN_INTER_SVSUB_2M_DIS))
	{
		G_Set_AlmIn(EN_ALM_SVLINK_CFGA,TRUE);
		G_Set_Inter(EN_INTER_SVSUB_A_CHK,TRUE);
	}
	// B套订阅配置异常
	if(G_Get_Inter(EN_INTER_SVSUB_B1_MULT)||G_Get_Inter(EN_INTER_SVSUB_B2_MULT)
		||G_Get_Inter(EN_INTER_SVSUB_B_DIS)||G_Get_Inter(EN_INTER_SVSUB_B_MULT)
		||G_Get_Inter(EN_INTER_SVSUB_1M_DIS)||G_Get_Inter(EN_INTER_SVSUB_2M_DIS))
	{
		G_Set_AlmIn(EN_ALM_SVLINK_CFGB,TRUE);
		G_Set_Inter(EN_INTER_SVSUB_B_CHK,TRUE);
	}
	// 控制块配置异常
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
// 函数功能：SV发布配置初始化函数
// 输入参数：无
// 输出参数：无
// 返回值：  无
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
	wSvPubNum =g_tagAna.wSvPubNum-1;//减去额定延时
	// 初始化通道配置
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
			// 标准
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
	// 通道个数不一致,非标准SV发布
	else
	{
		G_Set_Inter(EN_INTER_SVPUB_CHK,TRUE);
	}
		// 映射关系解析
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
		// 通道配置越限
		else
		{
			G_Set_Inter(EN_INTER_SVPUB_CHN_NO,TRUE);
		}
	}
}
// =============================================================================
// 函数功能：SV发布挑数在线修改
// 输入参数：无
// 输出参数：无
// 返回值：    无
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
		// 更新原始配置
		for(i=0;i<g_tagAna.wSvPubDatNum;i++)
		{
			pbSvPubSend[i]=pbSvPubCfg[i];
		}
		// GOOSE命令修正部分
		for(i=0;i<wAddNum;i++)
		{
			bSvPubChn=pbSvPubChn[i];
			if(bSvPubChn>=g_tagAna.wSvPubDatNum)
			{
				// 动态修改异常
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
			// 启动通道下发,在此处使能,如没有符合条件的通道,则不启动
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
// 函数功能：SV发布挑数在线修改(用于需要通道合成的挑数)
// 输入参数：无
// 输出参数：无
// 返回值：    无
// =============================================================================
BOOL IES_IMSam_SvPub_Cal(WORD wIndexSrc1,WORD wIndexSrc2,WORD wIndexDst)
{
	BOOL *pbSvPubPol;
	WORD *pbSvPubChn,*pbSvPubSend;
	WORD  wSvPubChnDst;

	pbSvPubChn  =g_tagAna.wSvPubChn;
	pbSvPubSend =g_tagAna.wSvPubSend;
	pbSvPubPol  =g_tagAna.bSvPubPol;
	// 目的枚举越限
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
	// 源枚举1判断
	if(wIndexSrc1>=CN_NUM_ANA)
	{
		return FALSE;
	}
	// 源枚举2判断
	if(wIndexSrc2<CN_NUM_ANA)
	{
		// 极性判断
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
		// 极性判断
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
// 函数功能：SV发布反极性设置
// 输入参数：无
// 输出参数：无
// 返回值：    无
// =============================================================================
BOOL IES_IMSam_SvPub_Pol(WORD wIndexStr,WORD wIndexEnd,UINT32 dwSet)
{
	WORD *pbSvPubSend,*pbSvPubCfg;
	WORD  wSvPubSend,wSvPubCfg,wSvPubIndex;
	BOOL  *pbSvPubPol;
	WORD i;
	// 修正极性
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
	// 更新当前挑数表
	for(i=0;i<g_tagAna.wSvPubDatNum;i++)
	{
		// 更新原始配置挑数表
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
		// 更新需下发的挑数表
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
	// 挑数下发
	g_tagAna.wSvPubChg|=CN_SV_OPT_POL_S;
	return TRUE;
}
// =============================================================================
// 函数功能：采样元件复位
// 输入参数：无
// 输出参数：无
// 返回值：  无
// =============================================================================

void IES_IMSam_Reset()
{
	tag_IMSam *ptag_IMSam;
	ptag_IMSam=&gtag_IMSam;
// 清除指针及标志
	ptag_IMSam->dwWaveFlag=FALSE;
//	ptag_IMSam->dwTDMPtr=0;                    // 分时复用指针
	ptag_IMSam->dwAnaPtr=0;                    // 相量运算指针
// 清除实虚部
	IES_memset(ptag_IMSam->iAnaReal,0x0,sizeof(ptag_IMSam->iAnaReal));
	IES_memset(ptag_IMSam->iAnaImag,0x0,sizeof(ptag_IMSam->iAnaImag));
#if(CN_HUM_ENA)	
// 清除13次谐波实虚部
	IES_memset(ptag_IMSam->iAnaHumReal,0x0,sizeof(ptag_IMSam->iAnaHumReal));
	IES_memset(ptag_IMSam->iAnaHumImag,0x0,sizeof(ptag_IMSam->iAnaHumImag));
#endif	
// 清除积分幅值
	IES_memset(ptag_IMSam->dwAnaAm,0x0,sizeof(ptag_IMSam->dwAnaAm));
}
#if(CN_TCHG_ENA)
// ============================================================================
// 函数功能：温度变化更新系数
// 输入参数：全局参数
// 输出参数：变比、校准系数
// 返回值：  无
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
				// 此处连续5次不能代表连续5帧,考虑修正
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
// 函数功能：参数更新
// 输入参数：全局参数
// 输出参数：变比、校准系数
// 返回值：  无
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
	FLOAT32          fBb12 = 0.0;   // 一次值转二次值变比
	FLOAT32          fBb21 = 0.0;   // 二次值转一次值变比
	FLOAT32          fTCoe = 1.0f;  // 温度调节系数
	BYTE             byAnaPtCtChg=FALSE, byAnaAmCoeChg = FALSE, byAnaAngCoeChg = FALSE, byAnaDcCoeChg = FALSE;
	ptag_IMSam = &gtag_IMSam;
	// 参数异常退出参数更新,并闭锁
	// 常量表自检退出参数更新,并闭锁
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

	// 变比更新
	pfPara     = &g_tagPara.fPara[0];
	pdwPara    = &g_tagPara.dwPara[0];
	pfBb       = &(ptag_IMSam->fAnaBb[0]);
	pfAnaPtCt = &(g_tagAna.fAnaPtCt[0]);
	ptag_IMSam->dwInit = TRUE;
	// 变比更新
	ptagAnaTab = &g_tAnaTab[0];
	for (i = 0; i < CN_NUM_ANA; i++)
	{
		// 与上一点信号变比一致
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
				// 一次值单位10mV,二次值保留3位小数
				*pfBb = fBb12 = pfPara[wParaScd]/pfPara[wParaFst]*CN_SV_U_Unit;
				fBb21 = pfPara[wParaFst]/pfPara[wParaScd];
				break;
			case EN_CTYPE_ANA_I:
			case EN_CTYPE_SV_I:
				// CT 参数为枚举类型
				// 一次值单位1mA,二次值保留3位小数
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
	// 基准门槛更新
	
	ptag_IMSam->bJzChkEna =pdwPara[EN_PARA_ENA_JZ];
	ptag_IMSam->dwJz1MkMin=pdwPara[EN_PARA_V_JZ1MIN];
	ptag_IMSam->dwJz1MkMax=pdwPara[EN_PARA_V_JZ1MAX];
	
	ptag_IMSam->dwJz2MkMin=pdwPara[EN_PARA_V_JZ2MIN];
	ptag_IMSam->dwJz2MkMax=pdwPara[EN_PARA_V_JZ2MAX];
	// 向FPGA下发幅值校准系数更新
#if(CN_TCHG_ENA)	
	// 温度调节
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
	
	// AD微调系数更新
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
	
	// 直流补偿更新
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
	// 标志更新放置在代码最后,可保证缓存完全更新完成,在一个断面中，保证任务中调用参数初始化无问题。
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
	// SV极性设置(仅设置CPU1)
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
// 函数功能：采样元件初始化函数
// 输入参数：无
// 输出参数：无
// 返回值：  无
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
// 函数功能：模拟量品质合成
// 输入参数：无
// 输出参数：无
// 返回值：  无
//           SV发布数据品质合成逻辑：
//           1.AD基准异常,对应AD上的模拟量置品质，暂时无效
//           2.PTCT板异常,对应PTCT上的模拟量置品质无效
//           3.级联数据品质转发
//           4.级联数据未订阅,品质无效
//           5.级联数据断链,品质无效
//           6.检修压板投入,所有品质检修
// =============================================================================
void IES_IMSam_Q()
{
	const    tagAnaTab  *ptagAnaTab;
	register UINT32     *pdwAnaQ,dwAnaQ;
	// SV发布自检标志
	register BOOL     bSvPubQErr=FALSE, bSvPubCfgErr, bQchg=FALSE;;
	register BOOL     *pbJzChk,*pbBoard;
	register WORD     i;
	register UINT32   dwADErr=0,dwBoardErr=0;
	register WORD     *pwSvPubSend,wSvPubSend;
    // SV数据总异常标志
    BOOL     bSvErrAll=FALSE;
#if(CN_SV_IN_ENA)
	register UINT32   *pdwSvQ,*pdwSvCbStatus,dwSvCbStatus;
	#if(CN_DEV_CPU1)
	register BOOL     *pbSvSub;
	register BYTE     *pbySvCb,bySvCb;
	#endif	
	// SV订阅自检标志
	BOOL     bSvCbLinkErr=FALSE,bSvCbDatErr=FALSE,bSvSubCfgErr;
	// SV级联解析自检标志
	BOOL     bSvAQErr=FALSE,    bSvBQErr=FALSE;
	BOOL     bSvATest=FALSE,    bSvBTest=FALSE;
    #if(CN_DEV_CPU1)
	register UINT32  *pdwSvCbSubCfg;
	pdwSvCbSubCfg =g_tagAna.dwSvCbSubCfg;
    #endif
	pdwSvCbStatus =g_tagAna.dwSvCbStatus;
#endif
#if(CN_SV_IN_ENA)
// 1.控制块相关自检
	for(i=0;i<CN_NUM_BOARD_SV;i++)
	{
		// 1.1控制块配置异常自检
		//if(pdwSvCbSubCfg[i])
		//{
		//	bSvCbCfgErr=TRUE;
		//}	
		// 1.2控制块标志字自检
		dwSvCbStatus = pdwSvCbStatus[i];
		if(dwSvCbStatus&CN_SVCB_Ena)
		{
			// 链路中断
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
				
				// 检修标志
				if(((dwSvCbStatus&CN_SVCB_Test)?TRUE:FALSE)^(g_tagPub.bSysTest))
				{
					G_Set_AlmIn_All(EN_ALM_SVSUB_TEST01+i,TRUE,dwSvCbStatus,0,0);
				}
				else
				{
					G_Set_AlmIn(EN_ALM_SVSUB_TEST01+i,FALSE);
				}
				// 数据异常
				if(dwSvCbStatus&CN_SVCB_DataErr)
				{
					bSvCbDatErr=TRUE;
					G_Set_AlmIn_All(EN_ALM_SVSUB_DAT01+i,TRUE,dwSvCbStatus,0,0);
				}
				else
				{
					G_Set_AlmIn(EN_ALM_SVSUB_DAT01+i,FALSE);
				}
				// 同步异常
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
	// 2.SV发布品质合成
	pbJzChk    =&(gtag_IMSam.bJzChk[0]);
	pdwAnaQ    =&(g_tagAna.dwAnaQ[0]);
	ptagAnaTab =&(g_tAnaTab[0]);
	pbBoard    =&(g_tChkState.bChkOut[EN_CHK_BOARD_SAM_STR]);
	for(i=0;i<CN_NUM_SAM;i++)
	{
		dwAnaQ=0;
		// AD基准自检
		if(ptagAnaTab->wADNo<CN_NUM_JZ)
		{
			if(pbJzChk[ptagAnaTab->wADNo])
			{
				dwAnaQ|=(CN_SV_Q_VALIDL+CN_SV_Q_DETAIL03);
				dwADErr|=g_dwBit[ptagAnaTab->wADNo];
			}
		}
		// PTCT板卡自检
		if(ptagAnaTab->wFrmNo<CN_NUM_BOARD_SAM)
		{
			if(pbBoard[ptagAnaTab->wFrmNo])
			{
				dwAnaQ|=(CN_SV_Q_VALIDL+CN_SV_Q_DETAIL05);
				dwBoardErr|=g_dwBit[ptagAnaTab->wFrmNo];
			}
		}
		// 2.3 检修品质
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
	// PT切换同时返回标志
	#endif
	for(i=EN_ANA_SV_STR;i<EN_ANA_SV_END;i++)
	{
		dwAnaQ=0;
	#if(CN_DEV_CPU1)
		bySvCb=*pbySvCb++;
		// 级联数据无订阅
		if(*pbSvSub++)
		{
			if(bySvCb<CN_NUM_BOARD_SV)
			{
				// 控制块解析异常
				if(pdwSvCbSubCfg[bySvCb]&CN_SVCFG_DataErr)
				{
					dwAnaQ|=CN_SV_Q_VALIDL;
				}
				if(pdwSvCbStatus[bySvCb]&CN_SVCB_Ena)
				{
					// 级联数据断链、数据异常
					if(pdwSvCbStatus[bySvCb]&CN_SVCB_Link_QErr)
					{
						dwAnaQ|=CN_SV_Q_VALIDL;
					}
					
					if(G_Get_Flag(EN_FLAG_V_NULL))
					{
						dwAnaQ|=CN_SV_Q_VCLR;
					}
					
				}
				// 控制块未使能 品质无效
				else
				{
					dwAnaQ|=CN_SV_Q_VALIDL;
				}
				// SV品质合并
				dwAnaQ|=(*pdwSvQ);
			}
			// 控制块映射错误 品质无效
			else
			{
				dwAnaQ|=CN_SV_Q_VALIDL;
			}
			// 已订阅的级联数据无效
			if(dwAnaQ&CN_SV_Q_VALIDL)
			{
				// 级联A套
				if((i<EN_ANA_SVA_END))
				{
					bSvAQErr=TRUE;
				}
				// 级联B套
				else
				{
					bSvBQErr=TRUE;
				}
			}
			// 已订阅的级联数据检修
			if(dwAnaQ&CN_SV_Q_TEST)
			{
				// 级联A套
				if(i<EN_ANA_SVA_END)
				{
					bSvATest=TRUE;
				}
				// 级联B套
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
	
		// 2.3 检修品质
		if(g_tagPub.bSysTest)
		{
			dwAnaQ|=CN_SV_Q_TEST;
		}
		// 2.4 上电电压切换保持状态,品质无效
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
	// 发布数据无效告警
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
	// 发布数据无效
	bSvPubQErr=G_Get_AlmIn_P[EN_ALM_SVPUB_INVALID];
	g_tagAna.byAnaQChg=bQchg;
	// 3.相关告警输出
	// 采样异常告警
	if(dwADErr||dwBoardErr)
	{
		G_Set_AlmIn_All(EN_ALM_SAM,TRUE,dwADErr,dwBoardErr,0);
	}
	else
	{
		G_Set_AlmIn(EN_ALM_SAM,FALSE);
	}
#if(CN_SV_IN_ENA)
	// SV级联相关告警
	G_Set_AlmIn(EN_ALM_SVLINK_QA,bSvAQErr);
	G_Set_AlmIn(EN_ALM_SVLINK_QB,bSvBQErr);
	G_Set_AlmIn(EN_ALM_SVLINK_TESTA,bSvATest);
	G_Set_AlmIn(EN_ALM_SVLINK_TESTB,bSvBTest);
	// 输出总的SV级联数据异常
	bSvErrAll|=bSvCbLinkErr|bSvCbDatErr|bSvAQErr|bSvBQErr;
	G_Set_AlmIn(EN_ALM_SVSUB,bSvErrAll);
	// SV订阅配置总异常
	bSvSubCfgErr=G_Get_Inter(EN_INTER_SVSUB_CFG);
	bSvErrAll|=(bSvSubCfgErr);
	G_Set_AlmIn(EN_ALM_LINK,bSvErrAll);
#endif
	bSvPubCfgErr=G_Get_Inter(EN_INTER_SVPUB_CFG);
	bSvErrAll|=bSvPubQErr|bSvPubCfgErr;
	G_Set_AlmIn(EN_ALM_SV,bSvErrAll);
}

// =============================================================================
// 函数功能：采样元件执行函数
// 输入参数：无
// 输出参数：无
// 返回值：  无
// =============================================================================
void IES_IMSam()
{
	tag_IMSam *ptag_IMSam;
	ptag_IMSam=&gtag_IMSam;
	// 元件闭锁
	if(ptag_IMSam->dwBs)
	{
		return;
	}
	// 采样数据刷新
	IES_IMSam_In(ptag_IMSam);
	// 上电防误处理
	if(!ptag_IMSam->dwPWInit)
	{
		ptag_IMSam->dwPWInit=TRUE;
	}
	// 基准计算及自检
	IES_IMSam_JZ(ptag_IMSam);
#if(CN_TCHG_ENA)	
	// 温度更新参数
	IES_IMSam_TChg_Para(ptag_IMSam);
#endif	
	// 参数更新过程中,闭锁运算(暂定仅闭锁相量运算)
	if(ptag_IMSam->dwInit)
	{
		IES_IMSam_Reset();
		ptag_IMSam->dwInit=FALSE;
		return;
	}
	// 界面浏览才进行计算
	if(!(G_Get_Inter(EN_INTER_OPT_ANA)
	||G_Get_Inter(EN_INTER_OPT_ANA_J)
	||G_Get_Inter(EN_INTER_OPT_ANA_FR)))
	{
		// 增加标志限制,降低负载
		if(ptag_IMSam->dwMenuInit)
		{
			IES_IMSam_Reset();
			ptag_IMSam->dwMenuInit=FALSE;
		}
		return;
	}
	ptag_IMSam->dwMenuInit=TRUE;
	// 测频
	if(!G_Get_Const_Chk(EN_DTYPE_CAL))
	{
		IES_IMSam_Fr(ptag_IMSam);
	}
	// 搬移与计算分时
	if(!ptag_IMSam->dwWaveFlag)
	{
		IES_IMSam_Cal(ptag_IMSam);
	}
	// 相量及频率搬移
	else
	{
		IES_IMSam_Out(ptag_IMSam);
		ptag_IMSam->dwWaveFlag=FALSE;
	}
}

