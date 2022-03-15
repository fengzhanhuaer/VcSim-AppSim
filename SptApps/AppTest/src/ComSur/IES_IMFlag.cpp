/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * 积成电子股份有限公司
 * 元件名称：中间标志元件
 * 元件功能：中间标志元件
 *     1.中间标志合成
 *     2.中间标志转换
 * 元件版本：V1.00
 * 定版时间：2020-9-7
 * 版本修改：
 * <版本号> <修改日期>, <修改人员>: <修改功能概述>
 * V1.00 2021-2-24 刘志利：初版
 *================================================================================*/

#include "IES_IMFlag.h"

// 元件接口结构体
tagIES_IMFlag      gtagIES_IMFlag;

// ============================================================================
// 函数功能：标志转换
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMFlag_Chg(tagIES_IMFlag *pgtagIES_IMFlag)
{
	register  UINT32 i,j,dwPara;
	const  WORD   *pwSrcIndex;
	BOOL   *pbFlagDst,*pbFlagSrc;
	const  tagFlagTab *ptFlagTab;
	
	ptFlagTab   =g_tFlagTab;
	pbFlagDst   =g_bFlag;
	
	for(i=0;i<CN_NUM_FLAG;i++,ptFlagTab++)
	{
		if(ptFlagTab->wSrcType<CN_NUM_DTYPE)
		{
			pbFlagSrc  = g_tDTypeTab[ptFlagTab->wSrcType].bDatAtr;
			pwSrcIndex = ptFlagTab->wSrcIndex;
			
			if((pbFlagSrc!=NULL)&&(*pwSrcIndex!=CN_NULL_PINNO))
			{
				switch(ptFlagTab->wCalCfg)
				{
					case CN_FLAG_OR:
						for(j=0;j<CN_FLAG_SNUM;j++)
						{
							if(*pwSrcIndex==CN_NULL_PINNO)
							{
								pbFlagDst[i]=FALSE;
								break;
							}
							if(pbFlagSrc[*pwSrcIndex++])
							{
								pbFlagDst[i]=TRUE;
								break;
							}
						};
						break;
					case CN_FLAG_NO:
						pbFlagDst[i]=!pbFlagSrc[*pwSrcIndex];
						break;
					case CN_FLAG_EQL:
						pbFlagDst[i]=pbFlagSrc[*pwSrcIndex];
						break;
					case CN_FLAG_MAT:
						dwPara = G_Get_PARA_I(ptFlagTab->wPara);
						for(j=0;j<CN_FLAG_SNUM;j++)
						{
							if(*pwSrcIndex==CN_NULL_PINNO)
							{
								pbFlagDst[i]=FALSE;
								break;
							}
							if((pbFlagSrc[*pwSrcIndex++])&&(dwPara&g_dwBit[j]))
							{
								pbFlagDst[i]=TRUE;
								break;
							}
						};
						break;
					default:
						break;
				}
			}
		}
	}
}
//
// 标志展宽
void IES_IMFlag_Ex(tagIES_IMFlag *pgtagIES_IMFlag)
{
	// 复归标志默认展宽2s
	if(g_bFlag[EN_FLAG_RESET])
	{
		g_tagPub.bSysReset=TRUE;
		pgtagIES_IMFlag->dwResetCnt++;
	}
	else if(g_tagPub.bSysReset)
	{
		if(pgtagIES_IMFlag->dwResetCnt<CN_T2S)
		{
			pgtagIES_IMFlag->dwResetCnt++;
		}
		else
		{
			g_tagPub.bSysReset=FALSE;
			pgtagIES_IMFlag->dwResetCnt=0;
		}
	}
	
}

// ============================================================================
// 函数功能：中间标志参数初始化
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMFlag_Para_Init()
{

}

// ============================================================================
// 函数功能：中间标志上电初始化
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMFlag_Init()
{
	IES_memset(&gtagIES_IMFlag,0x0,sizeof(gtagIES_IMFlag));
	IES_RamScanAdd(&gtagIES_IMFlag.byRamScan1);
	IES_RamScanAdd(&gtagIES_IMFlag.byRamScan2);
}
// ============================================================================
// 函数功能：中间标志处理主函数
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMFlag()
{
	tagIES_IMFlag     *pgtagIES_IMFlag;
	pgtagIES_IMFlag = &gtagIES_IMFlag;
	// 参数初始化
	if(pgtagIES_IMFlag->dwInit)
	{
		pgtagIES_IMFlag->dwInit = FALSE;
		return;
	}
	IES_IMFlag_Chg(pgtagIES_IMFlag);
	// 展宽类标志处理
	IES_IMFlag_Ex(pgtagIES_IMFlag);
	// 上电初始化清位
	pgtagIES_IMFlag->dwPWInit=TRUE;
}

