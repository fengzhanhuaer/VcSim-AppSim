/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * 积成电子股份有限公司
 * 元件名称：间隔采集执行单元逻辑元件
 * 元件功能：间隔采集执行单元逻辑元件
 *     1.级联切换
 *     2.电压切换
 *     3.三相不一致
 *     4.KKJ合后状态
 *     5.控制回路断线
 *     6.事故总
  *    7.闭锁重合闸开出(至另一套采集执行单元)
 *     8.闭锁重合闸GOOSE信号(本套采集执行单元)
 * 元件版本：V1.00
 * 定版时间：2020-9-7
 * 版本修改：
 * <版本号> <修改日期>, <修改人员>: <修改功能概述>
 * V1.00 2021-2-24 刘志利：初版
 *================================================================================*/

#include "IES_IMPub.h"
#include "IES_IMLogic.h"
#include "IES_IMSam.h"

// 组件接口部分
tagIES_IMJA      gtagIES_IMJA;
// ============================================================================
// 函数功能：KKJ\SHJ\STJ位置判断
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMJA_Relay(tagIES_IMJA  *pgtagIES_IMJA)
{
//	register BYTE    bSHJ, bSTJ, bYHJ, bYTJ;
//	register BYTE    bKHJ,bKTJ,bKKJ;

	register BYTE    bSHJ, bSTJ, bKKJ,bTJF;

	// KKJ\SHJ\STJ\TJF位置判断
	bKKJ=(pgtagIES_IMJA->bKKJEna)?G_Get_DI(EN_DI_KKJ):G_Get_DI(EN_DI_OPB1_KKJ);
	bSHJ=(pgtagIES_IMJA->bSHJEna)?G_Get_DI(EN_DI_SHJ):G_Get_DI(EN_DI_OPB1_SHJ);
	bSTJ=(pgtagIES_IMJA->bSTJEna)?G_Get_DI(EN_DI_STJ):G_Get_DI(EN_DI_OPB1_STJ);
	bTJF=(pgtagIES_IMJA->bTJFEna)?G_Get_DI(EN_DI_TJF):G_Get_DI(EN_DI_OPB1_TJF);
	
	// KKJ\SHJ\STJ\TJF位置保存
	G_Set_Flag(EN_FLAG_DI_KKJ,bKKJ);
	G_Set_Flag(EN_FLAG_DI_SHJ,bSHJ);
	G_Set_Flag(EN_FLAG_DI_STJ,bSTJ);
	G_Set_Flag(EN_FLAG_DI_TJF,bTJF);
	// KKJ计算模块,原智慧站采执规范逻辑图,目前删除。
#if 0	
	bYHJ=G_Get_GOIN(EN_GOIN_CKHZ);
	bYTJ=G_Get_GOIN(EN_GOIN_CKTZ);
	// 控合闸命令
	bKHJ = (bSHJ | bYHJ) && (!bYTJ) && (!bYTJ);
	pgtagIES_IMJA->bKHJ=bKHJ|pgtagIES_IMJA->bKHJ;
	// 控分闸命令
	bKTJ = (bSTJ | bYTJ) && (!bYHJ) && (!bYHJ);
	pgtagIES_IMJA->bKTJ=bKTJ|pgtagIES_IMJA->bKTJ;
	// KKJ位置
	bKKJ=pgtagIES_IMJA->bKHJ&&(!pgtagIES_IMJA->bKTJ);
	pgtagIES_IMJA->bKKJ=IES_TimeRelayRun(&(pgtagIES_IMJA->tTimer_KKJ),bKKJ);
	//信号输出
	G_Set_Flag(EN_FLAG_DI_STJ,pgtagIES_IMJA->bKKJ);
#endif
}

// ============================================================================
// 函数功能：级联切换
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_BusMuQH(tagIES_IMJA  *pgtagIES_IMJA)
{
	// 输入数据
	register BYTE		  bBusMUBS,bBusMUA,bBusMUB,bBusMUAuto; // 把手状态
	register BYTE		  bBusMUAQErr,bBusMUBQErr;			   // 母线采集执行单元异常状态
	register BYTE		  bBusMUATest,bBusMUBTest;			   // 母线采集执行单元检修状态
	register BYTE		  bBusMUAOK,bBusMUBOK;				   // 母线采集执行单元正常状态
	// 输出数据
	register BYTE		  bBusMU=CN_MULink_BC;				   // 级联选择中间结果
	register BYTE         bBsERR=FALSE;//,bLinkAERR=FALSE,bLinkBERR=FALSE;// 告警标志
	// 级联切换功能投入及闭锁
	if(pgtagIES_IMJA->bBusMuQhEna)
	{
		G_Set_Flag(EN_FLAG_LNK_ENA,TRUE);
		if(G_Get_Inter(EN_INTER_SVSUB_1M_2LINK)||G_Get_Inter(EN_INTER_SVSUB_2M_2LINK))
		{
			G_Set_AlmIn(EN_ALM_BS_LINKQH,FALSE);
		}
		else
		{
			G_Set_AlmIn(EN_ALM_BS_LINKQH,TRUE);
		}
	}
	else
	{
		G_Set_Flag(EN_FLAG_LNK_ENA,FALSE);
		G_Set_AlmIn(EN_ALM_BS_LINKQH,FALSE);
	}
	// A、B套数据正常检查 不经级联切换投退控制
	bBusMUAQErr=g_tAlmState.bAlmIn[EN_ALM_SVLINK_QA]|g_tAlmState.bAlmIn[EN_ALM_SVLINK_CFGA];
	bBusMUATest=g_tAlmState.bAlmIn[EN_ALM_SVLINK_TESTA];
	
	bBusMUBQErr=g_tAlmState.bAlmIn[EN_ALM_SVLINK_QB]|g_tAlmState.bAlmIn[EN_ALM_SVLINK_CFGB];
	bBusMUBTest=g_tAlmState.bAlmIn[EN_ALM_SVLINK_TESTB];
	//级联A正常态判断[]
	bBusMUAOK=IES_TimeRelayRun(&pgtagIES_IMJA->tTimer_SvA,(!(bBusMUAQErr|bBusMUATest)));
	//级联B正常态判断[]
	bBusMUBOK=IES_TimeRelayRun(&pgtagIES_IMJA->tTimer_SvB,(!(bBusMUBQErr|bBusMUBTest)));
	G_Set_Flag(EN_FLAG_SV_A,bBusMUAOK);
	G_Set_Flag(EN_FLAG_SV_B,bBusMUBOK);
	
	// 级联切换退出,是否考虑重启装置
	if((!G_Get_Flag(EN_FLAG_LNK_ENA))||G_Get_AlmIn_P[EN_ALM_BS_LINKQH])
	{
		// 默认取级联A套(如果当前B套,则切换至A套???,还是保持不变)
		if(G_Get_Flag(EN_FLAG_LNK_B)||(!G_Get_Flag(EN_FLAG_LNK_A)))
		{
			G_Set_Flag(EN_FLAG_LNK_B,FALSE);
			G_Set_Flag(EN_FLAG_LNK_A,TRUE);
			G_Set_Flag(EN_FLAG_LNK_BC,FALSE);
			// 级联切换使能标志
			pgtagIES_IMJA->bBusMuQh=TRUE;
		}
		// 清除告警事项
		G_Set_AlmIn(EN_ALM_XZBS,FALSE);
		return;
	}
	//刀闸位置异常合成
	bBusMUA   =G_Get_DI(EN_DI_LNK_A);
	bBusMUB   =G_Get_DI(EN_DI_LNK_B);
	bBusMUAuto=G_Get_DI(EN_DI_LNK_AUTO);
	//选择把手状态异常
	bBusMUBS=bBusMUA+bBusMUB+bBusMUAuto;
	if(bBusMUBS!=1)
	{
		bBsERR=TRUE;
	}
	//级联A
	else if(bBusMUA)
	{
		bBusMU=CN_MULink_A;
	}
	//级联B
	else if(bBusMUB)
	{
		bBusMU=CN_MULink_B;
	}
	//自动状态
	else if(bBusMUAuto)
	{
		if(bBusMUAOK)
		{
			bBusMU=CN_MULink_A;
		}
		else if(bBusMUBOK)
		{
			bBusMU=CN_MULink_B;
		}
	}
	// 上电初始化状态
	if(!pgtagIES_IMJA->dwPWInit)
	{
		if(bBusMU==CN_MULink_BC)
		{
			bBusMU=CN_MULink_A;
			G_Set_Flag(EN_FLAG_LNK_BC,TRUE);
		}
		else
		{
			G_Set_Flag(EN_FLAG_LNK_BC,FALSE);
		}
		
		if(bBusMU==CN_MULink_A)
		{
			G_Set_Flag(EN_FLAG_LNK_A,TRUE);
			G_Set_Flag(EN_FLAG_LNK_B,FALSE);
		}
		if(bBusMU==CN_MULink_B)
		{
			G_Set_Flag(EN_FLAG_LNK_A,FALSE);
			G_Set_Flag(EN_FLAG_LNK_B,TRUE);
		}
		pgtagIES_IMJA->bBusMuQh=TRUE;
	}
	if(bBusMU==CN_MULink_BC)
	{
		G_Set_Flag(EN_FLAG_LNK_BC,TRUE);
	}
	else
	{
		G_Set_Flag(EN_FLAG_LNK_BC,FALSE);
	}
	if(bBusMU==CN_MULink_A)
	{
		if(!G_Get_Flag(EN_FLAG_LNK_A))
		{
			G_Set_Flag(EN_FLAG_LNK_A,TRUE);
			G_Set_Flag(EN_FLAG_LNK_B,FALSE);
			// 级联切换使能标志
			pgtagIES_IMJA->bBusMuQh=TRUE;
		}
		//bLinkAERR=!bBusMUAOK;
		//bLinkBERR=FALSE;
	}
	else if(bBusMU==CN_MULink_B)
	{
		if(!G_Get_Flag(EN_FLAG_LNK_B))
		{
			G_Set_Flag(EN_FLAG_LNK_A,FALSE);
			G_Set_Flag(EN_FLAG_LNK_B,TRUE);
			// 级联切换使能标志
			pgtagIES_IMJA->bBusMuQh=TRUE;
		}
		//bLinkAERR=FALSE;
		//bLinkBERR=!bBusMUBOK;
	}
	G_Set_AlmIn(EN_ALM_XZBS,bBsERR);
}

// ============================================================================
// 函数功能：电压切换
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_VolQH(tagIES_IMJA  *pgtagIES_IMJA)
{
	//输入数据
	register BYTE         bXSWI1,bXSWI2;               // 刀闸位置信息
	//register WORD i;
	//register DWORD *pdwQ,dwQ;
	//输出数据
	register BYTE         b12QH=CN_VolQH_BC;           // Ⅰ/Ⅱ母转换中间结果
	register BYTE         bXSWIERR=FALSE,bPtActERR=FALSE,bPtRetERR=FALSE;// 告警标志
	// 级联切换功能投入及闭锁
	if(pgtagIES_IMJA->bVolQhEna)
	{
		G_Set_Flag(EN_FLAG_V_ENA,TRUE);
		if(G_Get_Inter(EN_INTER_SVSUB_2M_1LINKA)||G_Get_Inter(EN_INTER_SVSUB_2M_1LINKB)||G_Get_Inter(EN_INTER_SVSUB_2M_2LINK))
		{
			G_Set_AlmIn(EN_ALM_BS_VQH,FALSE);
		}
		else
		{
			G_Set_AlmIn(EN_ALM_BS_VQH,TRUE);
		}
	}
	else
	{
		G_Set_Flag(EN_FLAG_V_ENA,FALSE);
		G_Set_AlmIn(EN_ALM_BS_VQH,FALSE);
	}

	//刀闸位置异常合成
	bXSWI1=G_Get_DPI(EN_DPI_XSWI01);
	bXSWI2=G_Get_DPI(EN_DPI_XSWI02);
	//电压切换投入且双母线
	if(G_Get_Flag(EN_FLAG_V_ENA)&&(!G_Get_AlmIn_P[EN_ALM_BS_VQH]))
	{
		//刀闸位置异常
		if((bXSWI1==CN_DPI_STP)||(bXSWI1==CN_DPI_CHK)||(bXSWI2==CN_DPI_STP)||(bXSWI2==CN_DPI_CHK))
		{
			bXSWIERR=TRUE;
		}
		//电压取Ⅰ母
		if((bXSWI1==CN_DPI_CLS)&&(bXSWI2!=CN_DPI_CLS))
		{
			b12QH=CN_VolQH_1;
		}
		//电压取Ⅱ母
		else if((bXSWI2==CN_DPI_CLS)&&(bXSWI1!=CN_DPI_CLS))
		{
			b12QH=CN_VolQH_2;
		}
		//PT切换同时返回
		else if((bXSWI2==CN_DPI_OPN)&&(bXSWI1==CN_DPI_OPN))
		{
			b12QH=CN_VolQH_NULL;
			bPtRetERR=TRUE;
		}
		// PT切换同时动作
		else if((bXSWI2==CN_DPI_CLS)&&(bXSWI1==CN_DPI_CLS))
		{
			b12QH=CN_VolQH_1;
			bPtActERR=TRUE;
		}
		// 保持状态
		else
		{
			b12QH=CN_VolQH_BC;
		}
	}
	// 单母线
	else
	{
		b12QH=CN_VolQH_1;
		bPtActERR=FALSE;
		bPtRetERR=FALSE;
		bXSWIERR=FALSE;
		IES_TimeRelayStop(&pgtagIES_IMJA->tTimer_PTRet);
	}
	//上电初始化部分
	if(!pgtagIES_IMJA->dwPWInit)
	{
		if(b12QH==CN_VolQH_1)
		{
			G_Set_Flag(EN_FLAG_V_I,TRUE);
			G_Set_Flag(EN_FLAG_V_II,FALSE);
		}
		else if(b12QH==CN_VolQH_2)
		{
			G_Set_Flag(EN_FLAG_V_I,FALSE);
			G_Set_Flag(EN_FLAG_V_II,TRUE);
		}
		// 上电保持状态
		else if(b12QH==CN_VolQH_BC)
		{
			G_Set_Flag(EN_FLAG_V_BC_INIT,TRUE);
			G_Set_Flag(EN_FLAG_V_BC,TRUE);
			G_Set_Flag(EN_FLAG_V_I,FALSE);
			G_Set_Flag(EN_FLAG_V_II,FALSE);
		}
		else if(b12QH==CN_VolQH_NULL)
		{
			G_Set_Flag(EN_FLAG_V_I,FALSE);
			G_Set_Flag(EN_FLAG_V_II,FALSE);
		}
		pgtagIES_IMJA->bVolQh=TRUE;
	}
	G_Set_AlmIn(EN_ALM_XSWI,bXSWIERR);
	G_Set_AlmIn(EN_ALM_PTRET,bPtRetERR);
	G_Set_AlmIn(EN_ALM_PTACT,bPtActERR);
	// 非保持状态,清除品质无效标志
	if(b12QH!=CN_VolQH_BC)
	{
		G_Set_Flag(EN_FLAG_V_BC_INIT,FALSE);
		G_Set_Flag(EN_FLAG_V_BC,FALSE);
	}
	else
	{
		G_Set_Flag(EN_FLAG_V_BC,TRUE);
	}
	
	if(b12QH==CN_VolQH_1)
	{
		if(!G_Get_Flag(EN_FLAG_V_I))
		{
			G_Set_Flag(EN_FLAG_V_I,TRUE);
			G_Set_Flag(EN_FLAG_V_II,FALSE);
			G_Set_Flag(EN_FLAG_V_NULL,FALSE);
			// 电压切换使能标志
			pgtagIES_IMJA->bVolQh=TRUE;
		}
	}
	else if(b12QH==CN_VolQH_2)
	{
		if(!G_Get_Flag(EN_FLAG_V_II))
		{
			G_Set_Flag(EN_FLAG_V_I,FALSE);
			G_Set_Flag(EN_FLAG_V_II,TRUE);
			G_Set_Flag(EN_FLAG_V_NULL,FALSE);
			// 电压切换使能标志
			pgtagIES_IMJA->bVolQh=TRUE;
		}
	}
	if(b12QH==CN_VolQH_NULL)
	{
		if(IES_TimeRelayRun(&pgtagIES_IMJA->tTimer_PTRet,TRUE))
		{
			if(!G_Get_Flag(EN_FLAG_V_NULL))
			{
				G_Set_Flag(EN_FLAG_V_I,FALSE);
				G_Set_Flag(EN_FLAG_V_II,FALSE);
				G_Set_Flag(EN_FLAG_V_NULL,TRUE);
				// 电压切换使能标志
				//pgtagIES_IMJA->bVolQh=TRUE;
			}
		}
	}
	else
	{
		//级联A正常态判断[]
		IES_TimeRelayStop(&pgtagIES_IMJA->tTimer_PTRet);
	}
}
// ============================================================================
// 函数功能：切换挑数下发
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_VolPub(tagIES_IMJA  *pgtagIES_IMJA)
{
	WORD  wUxAd1Set1,wUxAd1Set2,wUxAd2Set1,wUxAd2Set2,wOffSet=0;
    DWORD  dwCfg1=0;
#if(CN_DEV_CPU1)
    DWORD  dwCfg2=0;
	// 电压切换,无级联发布不切换
	if(G_Get_Inter(EN_INTER_SVPUB_SUB))
	{
		if(pgtagIES_IMJA->bVolQh)
		{
			dwCfg1|=CN_SV_OPT_CHG1_S;
			dwCfg2|=CN_SV_OPT_CHG1_F;
		}
		if(pgtagIES_IMJA->bBusMuQh)
		{
			dwCfg1|=CN_SV_OPT_CHG2_S;
			dwCfg2|=CN_SV_OPT_CHG2_F;
		}
		
		if(dwCfg1)
		{
			// A套I母线
			if(G_Get_Flag(EN_FLAG_LNK_A)&&G_Get_Flag(EN_FLAG_V_I))
			{
				IES_IMSam_SvPub_Chg(EN_ANA_SVA1_STR,EN_ANA_SVA1_STR,EN_LINK_END,dwCfg1,dwCfg2);
			}
			// A套II母线
			else if(G_Get_Flag(EN_FLAG_LNK_A)&&G_Get_Flag(EN_FLAG_V_II))
			{
				IES_IMSam_SvPub_Chg(EN_ANA_SVA1_STR,EN_ANA_SVA2_STR,EN_LINK_END,dwCfg1,dwCfg2);
			}
			// B套I母线
			else if(G_Get_Flag(EN_FLAG_LNK_B)&&G_Get_Flag(EN_FLAG_V_I))
			{
				IES_IMSam_SvPub_Chg(EN_ANA_SVA1_STR,EN_ANA_SVB1_STR,EN_LINK_END,dwCfg1,dwCfg2);
			}
			// B套II母线
			else if(G_Get_Flag(EN_FLAG_LNK_B)&&G_Get_Flag(EN_FLAG_V_II))
			{
				IES_IMSam_SvPub_Chg(EN_ANA_SVA1_STR,EN_ANA_SVB2_STR,EN_LINK_END,dwCfg1,dwCfg2);
			}
			// 电压切换无结果
			else if(G_Get_Flag(EN_FLAG_LNK_A))
			{
				IES_IMSam_SvPub_Chg(EN_ANA_SVA1_STR,EN_ANA_SVA1_STR,EN_LINK_END,dwCfg1,dwCfg2);
			}
			// 电压切换无结果
			else if(G_Get_Flag(EN_FLAG_LNK_B))
			{
				IES_IMSam_SvPub_Chg(EN_ANA_SVA1_STR,EN_ANA_SVB1_STR,EN_LINK_END,dwCfg1,dwCfg2);
			}
		}
	}
#endif
	// Ux相别设置挑数
	// 上电初始化、参数更新、电压切换情况下,更新Ux挑数
	if((!pgtagIES_IMJA->dwPWInit)
		||(pgtagIES_IMJA->bUxPhaseRef)
		||dwCfg1)
	{
		wUxAd1Set2=CN_NULL_PINNO;
		wUxAd2Set2=CN_NULL_PINNO;
		if(pgtagIES_IMJA->dwUxPhase<=6)
		{
		    switch(pgtagIES_IMJA->dwUxPhase)
		    {
			    // 无选相
			    case 0:
			        wUxAd1Set1=EN_ANA_UX1;
			        wUxAd2Set1=EN_ANA_UX2;
			        break;
			        // 选相直采Ua
			    case 1:
			        wUxAd1Set1=EN_ANA_UA1;
			        wUxAd2Set1=EN_ANA_UA2;
			        break;
			        // 选相直采Ub
			    case 2:
			        wUxAd1Set1=EN_ANA_UB1;
				    wUxAd2Set1=EN_ANA_UB2;
				    break;
				    // 选相直采Uc
			    case 3:
			        wUxAd1Set1=EN_ANA_UC1;
			        wUxAd2Set1=EN_ANA_UC2;
			        break;
			        // 选相直采Uab
			    case 4:
			        wUxAd1Set1=EN_ANA_UA1;
			        wUxAd1Set2=EN_ANA_UB1;
			        wUxAd2Set1=EN_ANA_UA2;
			        wUxAd2Set2=EN_ANA_UB2;
			        break;
			        // 选相直采Ubc
			    case 5:
			        wUxAd1Set1=EN_ANA_UB1;
				    wUxAd1Set2=EN_ANA_UC1;
				    wUxAd2Set1=EN_ANA_UB2;
				    wUxAd2Set2=EN_ANA_UC2;
				    break;
				    // 选相直采Uca
			    case 6:
			        wUxAd1Set1=EN_ANA_UC1;
			        wUxAd1Set2=EN_ANA_UA1;
			        wUxAd2Set1=EN_ANA_UC2;
			        wUxAd2Set2=EN_ANA_UA2;
			        break;
			     default:
			        break;
		    }
		    IES_IMSam_SvPub_Cal(wUxAd1Set1,wUxAd1Set2,EN_ANA_UX1);
		    IES_IMSam_SvPub_Cal(wUxAd2Set1,wUxAd2Set2,EN_ANA_UX2);
		}
		else if(pgtagIES_IMJA->dwUxPhase<=12)
		{
			if(G_Get_Flag(EN_FLAG_V_II))
			{
				wOffSet+=DB0;
			}
			if(G_Get_Flag(EN_FLAG_LNK_B))
			{
				wOffSet+=DB1;
			}
			wOffSet=wOffSet*EN_LINK_END;

			switch(pgtagIES_IMJA->dwUxPhase)
			{
				// 选相级联Ua
				case 7:
				   wUxAd1Set1=EN_ANA_SVA1_UA1+wOffSet;
				   wUxAd2Set1=EN_ANA_SVA1_UA2+wOffSet;
				   break;
				   // 选相级联Ub
				case 8:
				   wUxAd1Set1=EN_ANA_SVA1_UB1+wOffSet;
				   wUxAd2Set1=EN_ANA_SVA1_UB2+wOffSet;
				   break;
				   // 选相级联Uc
				case 9:
				   wUxAd1Set1=EN_ANA_SVA1_UC1+wOffSet;
				   wUxAd2Set1=EN_ANA_SVA1_UC2+wOffSet;
				   break;
				   // 选相级联Uab
				case 10:
				   wUxAd1Set1=EN_ANA_SVA1_UA1+wOffSet;
				   wUxAd1Set2=EN_ANA_SVA1_UB1+wOffSet;
				   wUxAd2Set1=EN_ANA_SVA1_UA2+wOffSet;
				   wUxAd2Set2=EN_ANA_SVA1_UB2+wOffSet;
				   break;
				   // 选相级联Ubc
				case 11:
				   wUxAd1Set1=EN_ANA_SVA1_UB1+wOffSet;
				   wUxAd1Set2=EN_ANA_SVA1_UC1+wOffSet;
				   wUxAd2Set1=EN_ANA_SVA1_UB2+wOffSet;
				   wUxAd2Set2=EN_ANA_SVA1_UC2+wOffSet;
				   break;
				   // 选相级联Uca
				case 12:
				   wUxAd1Set1=EN_ANA_SVA1_UC1+wOffSet;
				   wUxAd1Set2=EN_ANA_SVA1_UA1+wOffSet;
				   wUxAd2Set1=EN_ANA_SVA1_UC2+wOffSet;
				   wUxAd2Set2=EN_ANA_SVA1_UA2+wOffSet;
				   break;
				default:
					  break;
			}
			IES_IMSam_SvPub_Cal(wUxAd1Set1,wUxAd1Set2,EN_ANA_UX1);
			IES_IMSam_SvPub_Cal(wUxAd2Set1,wUxAd2Set2,EN_ANA_UX2);
		}
		pgtagIES_IMJA->bUxPhaseRef=FALSE;
	}
	pgtagIES_IMJA->bVolQh=FALSE;
	pgtagIES_IMJA->bBusMuQh=FALSE;
}

// ============================================================================
// 函数功能：开入转告警
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMJA_Alm(tagIES_IMJA  *pgtagIES_IMJA)
{
	BOOL bSxbyz=FALSE;
	G_Set_AlmIn(EN_ALM_OPBP1,!G_Get_DI(EN_DI_OPB1_POW));
	//if(pgtagIES_IMJA->bDOpbEna)
	//{
		//G_Set_AlmIn(EN_ALM_OPBP2,G_Get_DI(EN_DI_OPB2_POW));
	//}
	if(G_Get_AlmIn_P[EN_ALM_SVSUB_TEST01]
		||G_Get_AlmIn_P[EN_ALM_SVSUB_TEST02]
		||G_Get_AlmIn_P[EN_ALM_GOOSE_TEST])
	{
		G_Set_AlmIn(EN_ALM_TEST,  TRUE);
	}
	else
	{
		G_Set_AlmIn(EN_ALM_TEST,  FALSE);
	}
	// 备用遥信暂定88个,
	if(pgtagIES_IMJA->dwSxbyz)
	{
		// 
		if(pgtagIES_IMJA->dwSxbyz<=28)
		{
			bSxbyz = G_Get_DI(pgtagIES_IMJA->dwSxbyz + EN_DI_YX_BAK01 - 1);
		}
		else if((pgtagIES_IMJA->dwSxbyz>=29)&&(pgtagIES_IMJA->dwSxbyz<=58))
		{
			bSxbyz = G_Get_DI(pgtagIES_IMJA->dwSxbyz + EN_DI_YX_BAK01);
		}
		else if((pgtagIES_IMJA->dwSxbyz>=59)&&(pgtagIES_IMJA->dwSxbyz<=71))
		{
			bSxbyz = G_Get_DI(pgtagIES_IMJA->dwSxbyz + EN_DI_YX_BAK01 + 1);
		}
		G_Set_AlmIn(EN_ALM_SXBYZ, bSxbyz);
	}
	else
	{
		G_Set_AlmIn(EN_ALM_SXBYZ,FALSE);
	}
}

// ============================================================================
// 函数功能：控制回路断线
// 输入参数：跳闸回路监视\合闸回路监视
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMJA_KHDX(tagIES_IMJA  *pgtagIES_IMJA)
{
	register BYTE    bTWJ,bHWJ;
	register BYTE    bKHDX1=FALSE,bKHDX2=FALSE;
	bTWJ   =G_Get_DI(EN_DI_OPB1_TWJ);
	bHWJ   =G_Get_DI(EN_DI_OPB1_HWJ);
	bKHDX1 =!(bTWJ^bHWJ);
	// 暂时不考虑双线圈
	// G_Set_AlmIn(EN_ALM_KHDX1,bKHDX1);
	//if(pgtagIES_IMJA->bDOpbEna)
	//{
	//bTWJ   =G_Get_DI(EN_DI_OPB2_TWJ);
	//bHWJ   =G_Get_DI(EN_DI_OPB2_HWJ);
	//bKHDX2 =!(bTWJ^bHWJ);
	//G_Set_AlmIn(EN_ALM_KHDX2,bKHDX2);
	//}
	G_Set_AlmIn(EN_ALM_KHDX,(bKHDX1|bKHDX2));
}
// ============================================================================
// 函数功能：事故总
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMJA_SGZ(tagIES_IMJA  *pgtagIES_IMJA)
{
	register BYTE    bTWJ,bKKJ,bSGZ;
	// 应该使用回路监视还是使用断路器位置,暂定使用断路器位置
	bTWJ=G_Get_DI(EN_DI_XCBR_OPN);
	bKKJ=G_Get_Flag(EN_FLAG_DI_KKJ);
	bSGZ=bTWJ&bKKJ;
	G_Set_AlmIn(EN_ALM_SGZ,bSGZ);
}
// ============================================================================
// 函数功能：闭锁重合闸出口(发另一套采集执行单元)
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMJA_BSCH(tagIES_IMJA  *pgtagIES_IMJA)
{
	register BYTE    bYHJ,bYTJ,bSHJ,bSTJ,bBSCH,bTJF;// 硬开入
	register BYTE    bTJRGoIn;				  // GOOSE永跳合并
	register BYTE    bBSCHGoIn;				  // GOOSE闭锁重合闸合并
	register BYTE    bBSCHInit;				  // 上电闭重
	register BYTE    bBSCHDO;				  // 闭锁重合闸出口合并
	register BYTE    bBSCHGO;				  // 闭锁重合闸Goose出口合并
	
	// 遥合(手合)
	bYHJ=G_Get_GOIN(EN_GOIN_CKHZ);
	bSHJ=G_Get_Flag(EN_FLAG_DI_SHJ);
	// 遥跳(手跳)
	bYTJ=G_Get_GOIN(EN_GOIN_CKTZ);
	bSTJ=G_Get_Flag(EN_FLAG_DI_STJ);
	// 遥跳(手跳)闭重保持标志
	if(pgtagIES_IMJA->bYTBschBcEna)
	{
		pgtagIES_IMJA->bYTBschBc=(pgtagIES_IMJA->bYTBschBc|bYTJ|bSTJ)&&(!(bYHJ|bSHJ));
	}
	else
	{
		pgtagIES_IMJA->bYTBschBc=FALSE;
	}
	// 直跳(标志选择)
	bTJF=G_Get_Flag(EN_FLAG_DI_TJF);
	// GOOSE永跳(动作合成)
	bTJRGoIn=G_Get_ActOut(EN_ACT_BHYT);
	// GOOSE闭锁重合(标志合成)
	bBSCHGoIn=G_Get_Flag(EN_FLAG_GOIN_BHBC);
	// 至另一套闭重
	bBSCHDO=pgtagIES_IMJA->bYTBschBc|bYHJ|bYTJ|bSHJ|bSTJ|bTJF|bTJRGoIn|bBSCHGoIn;
	G_Set_AlmIn(EN_ALM_BSCH_OTH,bBSCHDO);
	// 装置上电闭锁重合闸
	if(!pgtagIES_IMJA->dwPWInit)
	{
		pgtagIES_IMJA->tTimer_BschInit.bStatusOut=TRUE;
	}
	bBSCHInit=IES_TimeRelayRun(&pgtagIES_IMJA->tTimer_BschInit,FALSE);
	// 另一套闭重开入
	bBSCH=G_Get_DI(EN_DI_BC_OTH);
	// GOOSE闭重发布
	bBSCHGO=bBSCHDO|bBSCH|bBSCHInit;
	// 母线CPU板闭锁重合闸信号需要由CPU间隔板提供标志
	G_Set_AlmIn(EN_ALM_BSCH,bBSCHGO);
}
// ============================================================================
// 函数功能：间隔Ⅰ采集执行单元逻辑参数初始化
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMLogic_Para_Init()
{
	tagIES_IMJA     *pgtagIES_IMJA;
	UINT32           dwTimeActSet,dwTimeRetSet;
	pgtagIES_IMJA = &gtagIES_IMJA;
	if(G_Get_ChkIn_P[EN_CHK_PARA_FUN])
	{
		return;
	}
	pgtagIES_IMJA->dwInit=TRUE;
	//pgtagIES_IMJA->bDOpbEna=G_Get_PARA_I(EN_PARA_ENA_DOPB);
	// 位置参数
	pgtagIES_IMJA->bDevEna =G_Get_PARA_I(EN_PARA_TYPE_DEV);
	pgtagIES_IMJA->bKKJEna =G_Get_PARA_I(EN_PARA_TYPE_KKJ);
	pgtagIES_IMJA->bSHJEna =G_Get_PARA_I(EN_PARA_TYPE_SHJ);
	pgtagIES_IMJA->bSTJEna =G_Get_PARA_I(EN_PARA_TYPE_STJ);
	pgtagIES_IMJA->bTJFEna =G_Get_PARA_I(EN_PARA_TYPE_TJF);
	//dwTimeActSet=G_Get_PARA_I(EN_PARA_T_KKJ);
	//IES_TimeRelaySet(&(pgtagIES_IMJA->tTimer_KKJ),T(dwTimeActSet), CN_T1S);
	// 级联切换及电压切换相关
	pgtagIES_IMJA->bBusMuQhEna =G_Get_PARA_I(EN_PARA_ENA_LNK);
	pgtagIES_IMJA->bVolQhEna   =G_Get_PARA_I(EN_PARA_ENA_VQH);
	// PT同时返回确认延时
	dwTimeActSet=G_Get_PARA_I(EN_PARA_T_VQH_RET_RLY);
	IES_TimeRelaySet(&(pgtagIES_IMJA->tTimer_PTRet), T(dwTimeActSet), 0);
	// 级联A SV正常定时器
	dwTimeActSet=G_Get_PARA_I(EN_PARA_T_SVOK);
	IES_TimeRelaySet(&(pgtagIES_IMJA->tTimer_SvA), T(dwTimeActSet), 0);
	// 级联B SV正常定时器
	IES_TimeRelaySet(&(pgtagIES_IMJA->tTimer_SvB), T(dwTimeActSet), 0);
	// 电压接入方式选择
	//pgtagIES_IMJA->bVolType    =G_Get_PARA_I(EN_PARA_TYPE_MSAM);
	if(pgtagIES_IMJA->dwUxPhase !=G_Get_PARA_I(EN_PARA_TYPE_UxSAM))
	{
		pgtagIES_IMJA->dwUxPhase=G_Get_PARA_I(EN_PARA_TYPE_UxSAM);
		pgtagIES_IMJA->bUxPhaseRef=TRUE;
	}
	// 三相不一致遥信定义
	pgtagIES_IMJA->dwSxbyz     = G_Get_PARA_I(EN_PARA_SXBYZ_YX);           // 三相不一致
	// 闭锁重合闸相关参数
	pgtagIES_IMJA->bYTBschBcEna = G_Get_PARA_I(EN_PARA_ENA_BSBC);         // 遥分(STJ)闭锁重合闸保持投退
	dwTimeRetSet = G_Get_PARA_I(EN_PARA_T_BSCH_INIT);                     // 装置上电闭锁重合闸返回时间
	IES_TimeRelaySet(&(pgtagIES_IMJA->tTimer_BschInit), 0, T(dwTimeRetSet));
}
// ============================================================================
// 函数功能：间隔Ⅰ采集执行单元逻辑上电初始化
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMLogic_Init()
{
	IES_memset(&gtagIES_IMJA,0x0,sizeof(gtagIES_IMJA));
	IES_RamScanAdd(&gtagIES_IMJA.byRamScan1);
	IES_RamScanAdd(&gtagIES_IMJA.byRamScan2);
}
// ============================================================================
// 函数功能：间隔Ⅰ采集执行单元逻辑主函数
// 输入参数：
// 输出参数：
// 返回值：  无
// ============================================================================
void IES_IMLogic()
{
	tagIES_IMJA     *pgtagIES_IMJA;
	pgtagIES_IMJA = &gtagIES_IMJA;
	if(pgtagIES_IMJA->dwInit)
	{
		// 延时一个中断,不进行任何闭锁;
		pgtagIES_IMJA->dwInit=FALSE;
		return;
	}	
	// 位置判断
	IES_IMJA_Relay(pgtagIES_IMJA);
#if(CN_DEV_CPU1)
	// 级联切换
	IES_BusMuQH(pgtagIES_IMJA);
	// 电压切换
	IES_VolQH(pgtagIES_IMJA);
#endif
	// 切换结果发布
	IES_VolPub(pgtagIES_IMJA);
	// 开入转告警
	IES_IMJA_Alm(pgtagIES_IMJA);
	// 控制回路断线判断
	IES_IMJA_KHDX(pgtagIES_IMJA);
	// 事故总判断
	IES_IMJA_SGZ(pgtagIES_IMJA);
	// 闭锁重合闸判断
	IES_IMJA_BSCH(pgtagIES_IMJA);
	// 上电初始化清位
	pgtagIES_IMJA->dwPWInit=TRUE;
}

