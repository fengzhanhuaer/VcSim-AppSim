#include "InstResource.h"
using namespace spt;
// SV发布配置
ApiBoardAngFrameOut virSvOutBoard;
ApiSvOutVirDataSet virSvSendDateSet;
ApiSvOut SvSendDataSetDelay;             // 额定延时通道
ApiSvOut SvSendDataSetCell[CN_NUM_ANA];  // 数据通道
#if(CN_DEV_CPU1)
ApiBoardCmmSvOutVirDataSet  virCmmSvSendDateSet;
ApiBoardCmmSv               CmmSvSendDataSetCell[EN_LINK_END];
#endif
// 初始化
void AppAngOutPowerUpIni()
{
	WORD i;
	const VarUnits        *pUnitTem1;
	const tagAnaTab       *ptAnaTab;
	const tagCTypeTab     *ptCTypeTab;
	// SV发布初始化
	virSvOutBoard.PowerUpIni("虚拟数据集", "SVPUB", 0, CN_NUM_ANA+1);
#if(CN_DEV_CPU1)
	virSvSendDateSet.PowerUpIni("间隔SV发布", "dsSV1", "dsSV1", virSvOutBoard, CN_SVPUB_TIME_LINK, 1, M_ArrLen(SvSendDataSetCell) + 1);
#elif(CN_DEV_CPU2)
	virSvSendDateSet.PowerUpIni("间隔SV发布", "dsSV2", "dsSV2", virSvOutBoard, CN_SVPUB_TIME_LINK, 1, M_ArrLen(SvSendDataSetCell) + 1);
#endif
	// 额定延时初始化
	SvSendDataSetDelay.PowerUpIni(virSvOutBoard,"额定延时", "ANA_DLY",Unit_uS);
	// 此处随意设置,不起作用
	virSvSendDateSet.SetOutSelIndex(0, 0);
	ptCTypeTab =&g_tCTypeTab[0];
	ptAnaTab   =&g_tAnaTab[0];
	for(i=0;i<CN_NUM_ANA;i++)
	{
		pUnitTem1 =ptCTypeTab[ptAnaTab->wChanType].pUnit1;
		// 短地址增加前缀,与模拟量部分区分
		SvSendDataSetCell[i].PowerUpIni(virSvOutBoard, ptAnaTab->byName, ptAnaTab->byPinName,*pUnitTem1);
		virSvSendDateSet.SetOutSelIndex(i, i);
		ptAnaTab++;
	}
	// CPU 1 板件SV发布配置
#if(CN_DEV_CPU1)
	{
		virCmmSvSendDateSet.PowerUpIni("板间SV发布", "CmmSV", "CmmSV", virSvOutBoard, EN_LINK_END,EN_LINK_END);
		ptAnaTab   =&g_tAnaTab[EN_ANA_SV_STR];
		for(i=0;i<EN_LINK_END;i++)
		{
			pUnitTem1 =ptCTypeTab[ptAnaTab->wChanType].pUnit1;
			// 短地址增加前缀,与模拟量部分区分
			CmmSvSendDataSetCell[i].PowerUpIni(virCmmSvSendDateSet, ptAnaTab->byName, ptAnaTab->byPinName,*pUnitTem1);
			virCmmSvSendDateSet.SetOutSelIndex(i, i);
			ptAnaTab++;
		}
	}
#endif
}
// 发布配置更新
void AppAngOutCfgRef()
{
	WORD  *pwSvPubCfg,i;
	pwSvPubCfg=g_tagAna.wSvPubCfg;
	g_tagAna.wSvPubNum=virSvSendDateSet.DataSetCellNum();
//	printf("g_tagAna.wSvPubNum=%d\n",g_tagAna.wSvPubNum);
	// 数据集解析接口
	if(virSvSendDateSet.CfgErr())
	{
		g_tagAna.dwSvCbPubCfg|=CN_SVCFG_CfgErr;
	}
	if(virSvSendDateSet.ParseErr())
	{
		g_tagAna.dwSvCbPubCfg|=CN_SVCFG_ParseErr;
	}
	if(g_tagAna.wSvPubNum==0)
	{
		g_tagAna.wSvPubDatNum=0;
		
		//printf("g_tagAna.wSvPubNum=0\n");
		return;
	}
	// 判断有无额定延时
	if (virSvSendDateSet.GetOutSelIndex(g_tagAna.wSvPubNum) == (UINT32)(-1))
	{
		g_tagAna.wSvPubDatNum = g_tagAna.wSvPubNum - 1;
	}
	else
	{
		g_tagAna.wSvPubDatNum = g_tagAna.wSvPubNum;
	}
	
	//printf("g_tagAna.wSvPubDatNum =%d,g_tagAna.wSvPubNum=%d\n",g_tagAna.wSvPubDatNum,g_tagAna.wSvPubNum);
	// 数据映射获取
	for(i=0;i< CN_NUM_ANA;i++,pwSvPubCfg++)
	{
		*pwSvPubCfg=virSvSendDateSet.GetOutSelIndex(i+1)-1;
		// 级联数据有发布
		if((*pwSvPubCfg>=EN_ANA_SV_STR)&&(*pwSvPubCfg<EN_ANA_SV_END))
		{
			g_iInter[EN_INTER_SVPUB_SUB]=TRUE;
		}
	}
#if(CN_DEV_CPU1)
	// 无订阅 修正发布额定延时
	if(g_iInter[EN_INTER_SVSUB_NOPUB])
	{
		virSvSendDateSet.SetDealy(CN_SVPUB_TIME);
	}
#endif
#if(CN_DEV_CPU2)
// 无级联发布 修正发布额定延时及级联通道无效
	if(!g_iInter[EN_INTER_SVPUB_SUB])
	{
		virSvSendDateSet.SetDealy(CN_SVPUB_TIME);
		for(i=0;i< CN_NUM_SV;i++)
		{
			CmmSvIn[i].SetNodeLinkFlag(0,0,0);
		}
	}
#endif
}
// SV发布挑数表下发
void AppAngListRef()
{
	register  WORD  *pwSvPubSend,i,wSvPubChg;
	wSvPubChg=g_tagAna.wSvPubChg;
	// 操作成功
	if(wSvPubChg&CN_SV_OPT_S)
	{
		pwSvPubSend =g_tagAna.wSvPubSend;
		//LogMsg.Stamp()<<"挑数下发\n";
		for(i=0;i<g_tagAna.wSvPubDatNum;i++)
		{
			//LogMsg.Stamp()<<"Chn:"<<i+1<<"  Index:"<<pwSvPubSend[i]<<"\n";
			virSvSendDateSet.SetOutSelIndex(i+1,pwSvPubSend[i]);
		}
		// 板间交互数据挑数下发
#if(CN_DEV_CPU1)
		WORD *pwSvPubChn,wLinkflag=FALSE;
		// CPU1 更新板间挑数
		//LogErr.Stamp()<<"级联挑数下发\n";
		pwSvPubChn  =&g_tagAna.wSvPubChn[EN_ANA_SV_STR];
		// 判断有无级联
		for(i=0;i<EN_LINK_END;i++)
		{
			// 有级联数据
			if(pwSvPubChn[i]<g_tagAna.wSvPubDatNum)
			{
				wLinkflag=TRUE;
			}
		}
		// 
		if(wLinkflag)
		{
			for(i=0;i<EN_LINK_END;i++)
			{
				if(pwSvPubChn[i]<g_tagAna.wSvPubDatNum)
				{
					virCmmSvSendDateSet.SetOutSelIndex(i,pwSvPubSend[pwSvPubChn[i]]);
					//LogMsg.Stamp()<<"Chn:"<<i<<"Index:"<<pwSvPubSend[pwSvPubChn[i]]<<"\n";
				}
				// CPU1有无订阅下发全F
				else
				{
					virCmmSvSendDateSet.SetOutSelIndex(i,0xffff);
					//LogMsg.Stamp()<<"Chn:"<<i<<"Index:"<<0xffff<<"\n";
				}
			}
		}
#endif
		
		if(wSvPubChg&CN_SV_OPT_POL_S)
		{
			AppEventRunRef(EN_RUN_POL);
		}
		if(wSvPubChg&CN_SV_OPT_CHG1_S)
		{
			AppEventRunRef(EN_RUN_LNKQH_S);
		}
		if(wSvPubChg&CN_SV_OPT_CHG2_S)
		{
			AppEventRunRef(EN_RUN_VQH_S);
		}
		if(wSvPubChg&CN_SV_OPT_CAL_S)
		{
			AppEventRunRef(EN_RUN_UX_S);
		}
	}
#if 0
	// 操作失败
	if(wSvPubChg&CN_SV_OPT_F)
	{
		if(wSvPubChg&CN_SV_OPT_CHG1_F)
		{
			AppEventRunRef(EN_RUN_LNKQH_F);
		}
		if(wSvPubChg&CN_SV_OPT_CHG2_F)
		{
			AppEventRunRef(EN_RUN_VQH_F);
		}
		if(wSvPubChg&CN_SV_OPT_CAL_F)
		{
			AppEventRunRef(EN_RUN_UX_F);
		}
	}
#endif
	g_tagAna.wSvPubChg=CN_SV_OPT_NULL;
}

