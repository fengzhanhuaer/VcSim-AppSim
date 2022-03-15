#include "InstResource.h"
using namespace spt;
// SV��������
ApiBoardAngFrameOut virSvOutBoard;
ApiSvOutVirDataSet virSvSendDateSet;
ApiSvOut SvSendDataSetDelay;             // ���ʱͨ��
ApiSvOut SvSendDataSetCell[CN_NUM_ANA];  // ����ͨ��
#if(CN_DEV_CPU1)
ApiBoardCmmSvOutVirDataSet  virCmmSvSendDateSet;
ApiBoardCmmSv               CmmSvSendDataSetCell[EN_LINK_END];
#endif
// ��ʼ��
void AppAngOutPowerUpIni()
{
	WORD i;
	const VarUnits        *pUnitTem1;
	const tagAnaTab       *ptAnaTab;
	const tagCTypeTab     *ptCTypeTab;
	// SV������ʼ��
	virSvOutBoard.PowerUpIni("�������ݼ�", "SVPUB", 0, CN_NUM_ANA+1);
#if(CN_DEV_CPU1)
	virSvSendDateSet.PowerUpIni("���SV����", "dsSV1", "dsSV1", virSvOutBoard, CN_SVPUB_TIME_LINK, 1, M_ArrLen(SvSendDataSetCell) + 1);
#elif(CN_DEV_CPU2)
	virSvSendDateSet.PowerUpIni("���SV����", "dsSV2", "dsSV2", virSvOutBoard, CN_SVPUB_TIME_LINK, 1, M_ArrLen(SvSendDataSetCell) + 1);
#endif
	// ���ʱ��ʼ��
	SvSendDataSetDelay.PowerUpIni(virSvOutBoard,"���ʱ", "ANA_DLY",Unit_uS);
	// �˴���������,��������
	virSvSendDateSet.SetOutSelIndex(0, 0);
	ptCTypeTab =&g_tCTypeTab[0];
	ptAnaTab   =&g_tAnaTab[0];
	for(i=0;i<CN_NUM_ANA;i++)
	{
		pUnitTem1 =ptCTypeTab[ptAnaTab->wChanType].pUnit1;
		// �̵�ַ����ǰ׺,��ģ������������
		SvSendDataSetCell[i].PowerUpIni(virSvOutBoard, ptAnaTab->byName, ptAnaTab->byPinName,*pUnitTem1);
		virSvSendDateSet.SetOutSelIndex(i, i);
		ptAnaTab++;
	}
	// CPU 1 ���SV��������
#if(CN_DEV_CPU1)
	{
		virCmmSvSendDateSet.PowerUpIni("���SV����", "CmmSV", "CmmSV", virSvOutBoard, EN_LINK_END,EN_LINK_END);
		ptAnaTab   =&g_tAnaTab[EN_ANA_SV_STR];
		for(i=0;i<EN_LINK_END;i++)
		{
			pUnitTem1 =ptCTypeTab[ptAnaTab->wChanType].pUnit1;
			// �̵�ַ����ǰ׺,��ģ������������
			CmmSvSendDataSetCell[i].PowerUpIni(virCmmSvSendDateSet, ptAnaTab->byName, ptAnaTab->byPinName,*pUnitTem1);
			virCmmSvSendDateSet.SetOutSelIndex(i, i);
			ptAnaTab++;
		}
	}
#endif
}
// �������ø���
void AppAngOutCfgRef()
{
	WORD  *pwSvPubCfg,i;
	pwSvPubCfg=g_tagAna.wSvPubCfg;
	g_tagAna.wSvPubNum=virSvSendDateSet.DataSetCellNum();
//	printf("g_tagAna.wSvPubNum=%d\n",g_tagAna.wSvPubNum);
	// ���ݼ������ӿ�
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
	// �ж����޶��ʱ
	if (virSvSendDateSet.GetOutSelIndex(g_tagAna.wSvPubNum) == (UINT32)(-1))
	{
		g_tagAna.wSvPubDatNum = g_tagAna.wSvPubNum - 1;
	}
	else
	{
		g_tagAna.wSvPubDatNum = g_tagAna.wSvPubNum;
	}
	
	//printf("g_tagAna.wSvPubDatNum =%d,g_tagAna.wSvPubNum=%d\n",g_tagAna.wSvPubDatNum,g_tagAna.wSvPubNum);
	// ����ӳ���ȡ
	for(i=0;i< CN_NUM_ANA;i++,pwSvPubCfg++)
	{
		*pwSvPubCfg=virSvSendDateSet.GetOutSelIndex(i+1)-1;
		// ���������з���
		if((*pwSvPubCfg>=EN_ANA_SV_STR)&&(*pwSvPubCfg<EN_ANA_SV_END))
		{
			g_iInter[EN_INTER_SVPUB_SUB]=TRUE;
		}
	}
#if(CN_DEV_CPU1)
	// �޶��� �����������ʱ
	if(g_iInter[EN_INTER_SVSUB_NOPUB])
	{
		virSvSendDateSet.SetDealy(CN_SVPUB_TIME);
	}
#endif
#if(CN_DEV_CPU2)
// �޼������� �����������ʱ������ͨ����Ч
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
// SV�����������·�
void AppAngListRef()
{
	register  WORD  *pwSvPubSend,i,wSvPubChg;
	wSvPubChg=g_tagAna.wSvPubChg;
	// �����ɹ�
	if(wSvPubChg&CN_SV_OPT_S)
	{
		pwSvPubSend =g_tagAna.wSvPubSend;
		//LogMsg.Stamp()<<"�����·�\n";
		for(i=0;i<g_tagAna.wSvPubDatNum;i++)
		{
			//LogMsg.Stamp()<<"Chn:"<<i+1<<"  Index:"<<pwSvPubSend[i]<<"\n";
			virSvSendDateSet.SetOutSelIndex(i+1,pwSvPubSend[i]);
		}
		// ��佻�����������·�
#if(CN_DEV_CPU1)
		WORD *pwSvPubChn,wLinkflag=FALSE;
		// CPU1 ���°������
		//LogErr.Stamp()<<"���������·�\n";
		pwSvPubChn  =&g_tagAna.wSvPubChn[EN_ANA_SV_STR];
		// �ж����޼���
		for(i=0;i<EN_LINK_END;i++)
		{
			// �м�������
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
				// CPU1���޶����·�ȫF
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
	// ����ʧ��
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

