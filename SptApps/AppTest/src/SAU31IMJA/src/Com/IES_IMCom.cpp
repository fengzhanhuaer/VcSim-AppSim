/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * 积成电子股份有限公司
 * 元件名称：板件交互元件
 * 元件功能：板件交互元件
 * 元件版本：V1.00
 * 定版时间：2021-9-8
 * 版本修改：
 * <版本号> <修改日期>, <修改人员>: <修改功能概述>
 * V1.00 2021-9-8 刘志利：初版
 *================================================================================*/

#include "IES_IMCom.h"

WORD IES_IMCom_Chk_Para()
{
	WORD i;
	WORD wErr=0;
	DWORD     *pdwCrc,*pdwCrcOth;
	pdwCrc    = g_tagPara.dwCrc;
	pdwCrcOth = g_tagPara.dwCrcOth;

	for(i=0;i<CN_NUM_BOARD_PARA_COM;i++)
	{
		if(*pdwCrc++!=*pdwCrcOth++)
		{
			wErr|=g_dwBit[i];
		}
	}
	// 参数修改中
	if(G_Get_Flag(EN_FLAG_PARACHG))
	{
		return wErr;
	}
	if(wErr)
	{
		G_Set_ChkIn_All(EN_CHK_CPUCOM_PARA,wErr,0,0);
	}
	else
	{
		G_Clr_ChkIn(EN_CHK_CPUCOM_PARA);
	}
	return wErr;
}
void IES_IMCom_Chk_Ver()
{
	//CCD校验码自检
	if(g_tDevInfor.dwCrc!=g_tDevInfor.dwCrcOth)
	{
		G_Set_ChkIn_All(EN_CHK_CPUCOM_CCD,g_tDevInfor.dwCrc,g_tDevInfor.dwCrcOth,0);
	}
	if((g_tComVer[CN_BOARD_CPU].wVer       !=g_tComVer[CN_BOARD_CPU_OTH].wVer)
	||(g_tComVer[CN_BOARD_CPU].wVerNum     !=g_tComVer[CN_BOARD_CPU_OTH].wVerNum)
	||(g_tComVer[CN_BOARD_CPU].wSlowInitNum!=g_tComVer[CN_BOARD_CPU_OTH].wSlowInitNum)
	||(g_tComVer[CN_BOARD_CPU].wSlow1To2Num!=g_tComVer[CN_BOARD_CPU_OTH].wSlow1To2Num)
	||(g_tComVer[CN_BOARD_CPU].wSlow2To1Num!=g_tComVer[CN_BOARD_CPU_OTH].wSlow2To1Num)
	||(g_tComVer[CN_BOARD_CPU].wFast1To2Num!=g_tComVer[CN_BOARD_CPU_OTH].wFast1To2Num)
	||(g_tComVer[CN_BOARD_CPU].wFast2To1Num!=g_tComVer[CN_BOARD_CPU_OTH].wFast2To1Num)
	)
	{
		G_Set_ChkIn_All(EN_CHK_CPUCOM_VER,g_tComVer[CN_BOARD_CPU].wVer,g_tComVer[CN_BOARD_CPU_OTH].wVer,0);
	}
}
// 初始化交互数据组帧
void IES_IMCom_Init_Tx()
{
	WORD i,wLen=0;
	const tagComSlowTab   *ptComInitTab;
	BYTE *pbyDstData;

	ptComInitTab     =&g_tComInitTab[0];
	pbyDstData       =g_tComSlowTx.byData;
	for(i=0;i<g_NUM_COM_INIT;i++,ptComInitTab++)
	{
		wLen+=ptComInitTab->dwSrcLen;
		if(wLen>=CN_TX_MAX)
		{
			return;
		}
		IES_memcpy(pbyDstData,ptComInitTab->dwSrcLen,ptComInitTab->pwSrcAddr,ptComInitTab->dwSrcLen);
		pbyDstData+=ptComInitTab->dwSrcLen;
	}
	
	g_tComSlowTx.wLen  = wLen;
	g_tComSlowTx.wType = EN_COM_TYPE_INIT01;
	g_tComSlowTx.wFlag=TRUE;
}
// 快速交互数据组帧
void IES_IMCom_Fast_Tx()
{
	WORD i;
	const tagComFastTab   *ptComFastTab;
	BYTE   *pbyDstData;
	WORD    wLenBit=0,wLenByte=0;
	if(g_tComFastTx.wFlag)
	{
		return;
	}
	pbyDstData       =g_tComFastTx.byData;
	
#if(CN_DEV_CPU1)
	ptComFastTab  = &g_tComFast1To2Tab[0];
	wLenBit       = g_NUM_COM1TO2_FAST;
#elif(CN_DEV_CPU2)
	ptComFastTab  = &g_tComFast2To1Tab[0];
	wLenBit       = g_NUM_COM2TO1_FAST;
#endif
	wLenByte      = (wLenBit>>3)+1;
	if(wLenByte>=CN_TX_MAX)
	{
		return;
	}
	*pbyDstData=0;
	for(i=0;i<wLenBit;i++,ptComFastTab++)
	{
		if(*(ptComFastTab->pwSrcAddr))
		{
			*pbyDstData|=(BYTE)g_dwBit[i%8];
		}
		else
		{
			*pbyDstData&=(BYTE)(~g_dwBit[i%8]);
		}
		if((i%8)==7)
		{
			pbyDstData++;
			*pbyDstData=0;
		}
	}
	g_tComFastTx.wLen  = wLenByte;
	g_tComFastTx.wType = EN_COM_TYPE_FAST01;
	g_tComFastTx.wFlag=TRUE;
}

// 慢速交互数据组帧,返回长度
void IES_IMCom_Slow_Tx()
{
	register  UINT32 i;
	const tagComSlowTab  *ptComSlowTab;
	BYTE   *pSrcData,*pDstData;
	WORD   wTypeNum,wLen,wSendPtr;
	if(g_tComSlowTx.wFlag)
	{
		return;
	}
	pDstData=g_tComSlowTx.byData;
	
#if(CN_DEV_CPU1)
	ptComSlowTab  = &g_tComSlow1To2Tab[0];
	wTypeNum      = g_NUM_COM1TO2_SLOW;
#else
	ptComSlowTab  = &g_tComSlow2To1Tab[0];
	wTypeNum	  = g_NUM_COM2TO1_SLOW;
#endif
	wSendPtr=g_tComSlowTx.wSendPtr;
	if(++g_tComSlowTx.wSendPtr>=wTypeNum)
	{
		g_tComSlowTx.wSendPtr=0;
	}
	// 类型检查
	ptComSlowTab=&ptComSlowTab[wSendPtr];

	if(ptComSlowTab->pbSrcChg==NULL)
	{
		return;
	}
	if(*ptComSlowTab->pbSrcChg)
	{
		pSrcData = ptComSlowTab->pwSrcAddr;
		wLen  = ptComSlowTab->dwSrcLen;
		if(wLen>=CN_TX_MAX)
		{
			return;
		}
		for(i=0;i<wLen;i++)
		{
			*pDstData++=*pSrcData++;
		}
		g_tComSlowTx.wLen  = ptComSlowTab->dwSrcLen;
		g_tComSlowTx.wType = EN_COM_TYPE_SLOW01+wSendPtr;
		g_tComSlowTx.wFlag=TRUE;
		*ptComSlowTab->pbSrcChg=FALSE;
	}

}
// 接收帧存入缓存
BOOL IES_IMCom_Fast_Rx_Buf(BYTE *pbyData,WORD wLen,WORD wType)
{
	// 闭锁数据更新
	if(g_tComFastRx.wFlag)
	{
		return FALSE;
	}
	if((pbyData==NULL)||(wLen>CN_TX_MAX))
	{
		return TRUE;
	}
	IES_memcpy(g_tComFastRx.byData,wLen, pbyData,wLen);
	g_tComFastRx.wLen  = wLen;
	g_tComFastRx.wType = wType;
	g_tComFastRx.wFlag  = TRUE;
	return FALSE;
}
// 接收帧存入缓存
BOOL IES_IMCom_Slow_Rx_Buf(BYTE *pbyData,WORD wLen,WORD wType)
{
	WORD wTypeNum;
	// 闭锁数据更新
	if(g_tComSlowRx.wFlag)
	{
		return FALSE;
	}
	if((pbyData==NULL)||(wLen>CN_TX_MAX))
	{
		return FALSE;
	}
#if(CN_DEV_CPU1)
	wTypeNum      = g_NUM_COM2TO1_SLOW;
#else
	wTypeNum      = g_NUM_COM1TO2_SLOW;
#endif
	if((wType!=EN_COM_TYPE_INIT01)&&((wType<EN_COM_TYPE_SLOW01)||(wType>=EN_COM_TYPE_SLOW01+wTypeNum)))
	{
		return FALSE;
	}
	IES_memcpy(g_tComSlowRx.byData,wLen, pbyData,wLen);
	g_tComSlowRx.wLen  = wLen;
	g_tComSlowRx.wType = wType;
	g_tComSlowRx.wFlag  = TRUE;
	return TRUE;
}
// 快速交互数据组帧
void IES_IMCom_Init_Rx(UINT32 *pCfg)
{
	WORD i,wLen=0,wCrcFlag=0;
	const tagComSlowTab  *ptComInitTab;
	BYTE       *pbySrcData;
	tagCom    *ptComRx;
	
	ptComRx=&g_tComSlowRx;
	
	if(!ptComRx->wFlag)
	{
		return;
	}
	
	if(ptComRx->wType!=EN_COM_TYPE_INIT01)
	{
		return;
	}
	ptComInitTab=&g_tComInitTab[0];
	
	for(i=0;i<g_NUM_COM_INIT;i++)
	{
		wLen+=ptComInitTab->dwDstLen;
		ptComInitTab++;
	}
	if(ptComRx->wLen!=wLen)
	{
		ptComRx->wFlag=FALSE;
		return;
	}
	ptComInitTab=&g_tComInitTab[0];
	pbySrcData  =ptComRx->byData;
	for(i=0;i<g_NUM_COM_INIT;i++)
	{
		IES_memcpy(ptComInitTab->pwDstAddr,ptComInitTab->dwDstLen,pbySrcData,ptComInitTab->dwSrcLen);
		pbySrcData+=ptComInitTab->dwDstLen;
		ptComInitTab++;
	}
	ptComRx->wFlag=FALSE;
	//1.CRC自检
	wCrcFlag=IES_IMCom_Chk_Para();
	//2.版本信息和配置文件自检
	IES_IMCom_Chk_Ver();
	if(pCfg)
	{
		*pCfg=wCrcFlag;
	}
}
// 快速交互数据复归
void IES_IMCom_Fast_Reset()
{
	WORD i,wLenBit;
	const tagComFastTab  *ptComFastTab;
#if(CN_DEV_CPU1)
	ptComFastTab  = &g_tComFast2To1Tab[0];
	wLenBit       = g_NUM_COM2TO1_FAST;
#else
	ptComFastTab  = &g_tComFast1To2Tab[0];
	wLenBit       = g_NUM_COM1TO2_FAST;
#endif
	// 清除所有数据
	for(i=0;i<wLenBit;i++,ptComFastTab++)
	{
		if(ptComFastTab->pwDstAddr)
		{
			*(ptComFastTab->pwDstAddr)=FALSE;
		}
	}
}

// 快速交互数据组帧
void IES_IMCom_Fast_Rx()
{
	WORD i;
	const tagComFastTab  *ptComFastTab;
	BYTE       byData=0,*pbySrcData;
	WORD       wLenBit,wLenByte;
	tagCom    *ptComRx;
	ptComRx=&g_tComFastRx;
	// 交互自检清除交互数据
	if(G_Get_ChkOut_P[EN_CHK_CPUCOM_FAST])
	{
		if(!ptComRx->wReset)
		{
			IES_IMCom_Fast_Reset();
			ptComRx->wReset=TRUE;
		}
	}
	else
	{
		ptComRx->wReset=FALSE;
	}
	// 
	if(!ptComRx->wFlag)
	{
		G_Set_ChkIn(EN_CHK_CPUCOM_FAST);
		return;
	}
	if(ptComRx->wType!=EN_COM_TYPE_FAST01)
	{
		G_Set_ChkIn(EN_CHK_CPUCOM_FAST);
		ptComRx->wFlag=FALSE;
		return;
	}
	// CPU1
#if(CN_DEV_CPU1)
	ptComFastTab  = &g_tComFast2To1Tab[0];
	wLenBit       = g_NUM_COM2TO1_FAST;
#else
	ptComFastTab  = &g_tComFast1To2Tab[0];
	wLenBit       = g_NUM_COM1TO2_FAST;
#endif
	wLenByte      = (wLenBit>>3)+1;
	if(ptComRx->wLen!=wLenByte)
	{
		// 增加自检事项
		ptComRx->wFlag=FALSE;
		G_Set_ChkIn(EN_CHK_CPUCOM_FAST);
		
		return;
	}

	G_Clr_ChkIn(EN_CHK_CPUCOM_FAST);
	pbySrcData=ptComRx->byData;
	
	// 自检事项返回
	for(i=0;i<wLenBit;i++,ptComFastTab++)
	{
		if(i%8==0)
		{
			byData=*pbySrcData++;
		}
		if(byData&g_dwBit[i%8])
		{
			*(ptComFastTab->pwDstAddr)=TRUE;
		}
		else
		{
			*(ptComFastTab->pwDstAddr)=FALSE;
		}
	}
	ptComRx->wFlag=FALSE;
}
// 慢速交互数据组帧
void IES_IMCom_Slow_Rx()
{
	WORD i,wLen,wType;
	const tagComSlowTab  *ptComSlowTab;
	BYTE    *pDstData,*pSrcData;
	WORD    wTypeNum;
	tagCom  *ptComRx;
	
	ptComRx=&g_tComSlowRx;
	if(!ptComRx->wFlag)
	{
		return;
	}

#if(CN_DEV_CPU1)
	ptComSlowTab  = &g_tComSlow2To1Tab[0];
	wTypeNum      = g_NUM_COM2TO1_SLOW;
#else
	ptComSlowTab  = &g_tComSlow1To2Tab[0];
	wTypeNum      = g_NUM_COM1TO2_SLOW;
#endif	
	wType=ptComRx->wType-EN_COM_TYPE_SLOW01;
	// 类型检查
	if(wType>=wTypeNum)
	{
		ptComRx->wFlag=FALSE;
		return;
	}
	// 长度检查
	wLen=ptComRx->wLen;
	if(ptComRx->wLen!=ptComSlowTab[wType].dwSrcLen)
	{
		ptComRx->wFlag=FALSE;
		return;
	}
	pDstData=ptComSlowTab[wType].pwDstAddr;
	pSrcData=ptComRx->byData;
	// 自检事项返回
	for(i=0;i<wLen;i++)
	{
		*pDstData++=*pSrcData++;
	}
	if(ptComSlowTab[wType].pbDstChg!=NULL)
	{
		*ptComSlowTab[wType].pbDstChg=TRUE;
	}
	ptComRx->wFlag=FALSE;
	// 参数CRC自检
	if(g_tagPara.bCrcOthChg)
	{
		if(!G_Get_Flag(EN_FLAG_PARACHG))
		{
			IES_IMCom_Chk_Para();
		}
		g_tagPara.bCrcOthChg=FALSE;
	}
}
void IES_IMCom_Init()
{
	IES_memset(&g_tComFastTx, 0x0,sizeof(g_tComFastTx));
	IES_memset(&g_tComSlowTx, 0x0,sizeof(g_tComSlowTx));
	IES_memset(&g_tComFastRx, 0x0,sizeof(g_tComFastRx));
	IES_memset(&g_tComSlowRx, 0x0,sizeof(g_tComSlowRx));
	IES_memset(g_tComVer    , 0x0,sizeof(g_tComVer));

	IES_RamScanAdd(&g_tComFastTx.byRamScan1);
	IES_RamScanAdd(&g_tComFastTx.byRamScan2);
	IES_RamScanAdd(&g_tComFastTx.byRamScan3);
	
	IES_RamScanAdd(&g_tComSlowTx.byRamScan1);
	IES_RamScanAdd(&g_tComSlowTx.byRamScan2);
	IES_RamScanAdd(&g_tComSlowTx.byRamScan3);
	
	IES_RamScanAdd(&g_tComFastRx.byRamScan1);
	IES_RamScanAdd(&g_tComFastRx.byRamScan2);
	IES_RamScanAdd(&g_tComFastRx.byRamScan3);

	IES_RamScanAdd(&g_tComSlowRx.byRamScan1);
	IES_RamScanAdd(&g_tComSlowRx.byRamScan2);
	IES_RamScanAdd(&g_tComSlowRx.byRamScan3);

	g_tComVer[CN_BOARD_CPU].wVer=CN_CPU_SOFT_COM;
	g_tComVer[CN_BOARD_CPU].wVerNum=sizeof(tagComVer);
	g_tComVer[CN_BOARD_CPU].wSlowInitNum=g_NUM_COM_INIT*sizeof(tagCom);
	g_tComVer[CN_BOARD_CPU].wSlow1To2Num=g_NUM_COM1TO2_SLOW*sizeof(tagCom);
	g_tComVer[CN_BOARD_CPU].wSlow2To1Num=g_NUM_COM2TO1_SLOW*sizeof(tagCom);
	g_tComVer[CN_BOARD_CPU].wFast1To2Num=g_NUM_COM1TO2_FAST*sizeof(tagCom);
	g_tComVer[CN_BOARD_CPU].wFast2To1Num=g_NUM_COM2TO1_FAST*sizeof(tagCom);
	return;
}

