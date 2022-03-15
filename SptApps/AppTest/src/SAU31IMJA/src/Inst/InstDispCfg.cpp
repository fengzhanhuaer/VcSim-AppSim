#include "InstResource.h"
using namespace spt;
// ģ����������ʾ����
ApiAngRmsGroup ApiDispAnaGroup;
ApiAngRms ApiDispAna[CN_NUM_ANA];
// Ƶ�ʽ�����ʾ����
ApiAngRmsGroup ApiDispFrGroup;
ApiAngRms ApiDispFr[CN_NUM_CAL];
// ֱ����������ʾ����
ApiAngRmsGroup ApiDispDcGroup;
ApiAngRms ApiDispDc[CN_NUM_DC_SAM];
// ״̬���ӽ�����ʾ����
ApiAngRmsGroup ApiDispDevGroup;
ApiAngRms ApiDispDev[CN_NUM_DC_DEV];
// �⹦�ʽ�����ʾ����
ApiAngRmsGroup ApiDispOptGroup[2];
ApiAngRms ApiDispOpt[CN_NUM_DC_OPT1+CN_NUM_DC_OPT2];
// �м��־������ʾ����
ApiAngRmsGroup ApiDispInterGroup;
ApiAngRms ApiDispInter[CN_NUM_FLAG+CN_NUM_INTER];
// ��ʼ��
void AppDispAnaPowerUpIni()
{
	WORD i, wDotBit;
	const VarUnits        *pUnitTem1,*pUnitTem2;
	const tagAnaTab       *ptAnaTab;
	const tagCTypeTab     *ptCTypeTab;
	// ������ʾģ������ʼ��
	ptCTypeTab =&g_tCTypeTab[0];
	ptAnaTab   =&g_tAnaTab[0];
	ApiDispAnaGroup.PowerUpIni("ģ����", "ApiDispAnaGroup", CN_NUM_ANA,CN_NUM_ANA);
	for(i=0;i<CN_NUM_ANA;i++)
	{
		pUnitTem1=ptCTypeTab[ptAnaTab->wChanType].pUnit1;
		wDotBit =(WORD)ptCTypeTab[ptAnaTab->wChanType].byDotBit;
		// �̵�ַ����ǰ׺,��ģ������������
		if(i==0)
		{
			ApiDispAna[i].PowerUpIni(ptAnaTab->byName, ptAnaTab->byPinName, ApiDispAnaGroup,1, wDotBit, *pUnitTem1, 3, Unit_ANGLE, 2);
		}
		else
		{
			ApiDispAna[i].PowerUpIni(ptAnaTab->byName, ptAnaTab->byPinName, ApiDispAnaGroup,0, wDotBit, *pUnitTem1, 3, Unit_ANGLE, 2);
		}
		// һ��ֵ��λ����
		pUnitTem2=ptCTypeTab[ptAnaTab->wChanType].pUnit2;
		ApiDispAna[i].SetDataUnit(*pUnitTem2,Unit_ANGLE);
		ApiDispAna[i].SetDisp(TRUE);
		ptAnaTab++;
	}
}
void AppDispFrPowerUpIni()
{
	WORD i, wDotBit;
	const VarUnits        *pUnitTem1;
	const tagCalTab       *ptagCalTab;
	const tagCTypeTab     *ptCTypeTab;
	// ������ʾģ������ʼ��
	ptCTypeTab =&g_tCTypeTab[0];
	ptagCalTab =&g_tCalTab[0];
	ApiDispFrGroup.PowerUpIni("Ƶ��", "ApiDispFGroup", CN_NUM_CAL,CN_NUM_CAL);
	for(i=0;i<CN_NUM_CAL;i++)
	{
		pUnitTem1=ptCTypeTab[ptagCalTab->wChanType].pUnit1;
		wDotBit =(WORD)ptCTypeTab[ptagCalTab->wChanType].byDotBit;
		ApiDispFr[i].PowerUpIni(ptagCalTab->byName, ptagCalTab->byPinName, ApiDispFrGroup,wDotBit, *pUnitTem1,  0);
		ApiDispFr[i].SetDisp(TRUE);
		ptagCalTab++;
	}
}
// ������ʾֱ������ʼ��
void AppDispDcPowerUpIni()
{
	WORD i, wDotBit;
	const VarUnits        *pUnitTem;
	const tagDCTab        *ptagDcTab;
	const tagCTypeTab     *ptCTypeTab;
	ptCTypeTab =&g_tCTypeTab[0];
	ptagDcTab  =&g_tDCTab[EN_DC_SAM_STR];
	ApiDispDcGroup.PowerUpIni("ֱ����", "ApiDispDcGroup", CN_NUM_DC_SAM,CN_NUM_DC_SAM);
	for(i=0;i<CN_NUM_DC_SAM;i++)
	{
		pUnitTem=G_Get_PARA_I(ptCTypeTab[ptagDcTab->wType].wParaIndex)?ptCTypeTab[ptagDcTab->wType].pUnit1:ptCTypeTab[ptagDcTab->wType].pUnit2;
		wDotBit =(WORD)ptCTypeTab[ptagDcTab->wType].byDotBit;
		if(i==0)
		{
			ApiDispDc[i].PowerUpIni(ptagDcTab->byName, ptagDcTab->byPinName, ApiDispDcGroup,1, wDotBit, *pUnitTem, wDotBit, Unit_NULL, 2);
		}
		else
		{
			ApiDispDc[i].PowerUpIni(ptagDcTab->byName, ptagDcTab->byPinName, ApiDispDcGroup,0, wDotBit, *pUnitTem, wDotBit, Unit_NULL, 2);
		}
		ApiDispDc[i].SetDisp(TRUE);
		ptagDcTab++;
	}
}
// ������ʾ״̬����
void AppDispDevPowerUpIni()
{
	WORD i, wDotBit;
	const VarUnits        *pUnitTem1;
	const tagDCTab        *ptagDcTab;
	const tagCTypeTab     *ptCTypeTab;
	ptCTypeTab =&g_tCTypeTab[0];
	ptagDcTab  =&g_tDCTab[EN_DC_DEV_STR];
	ApiDispDevGroup.PowerUpIni("״̬����", "ApiDispDevGroup", CN_NUM_DC_DEV,CN_NUM_DC_DEV);
	for(i=0;i<CN_NUM_DC_DEV;i++)
	{
		pUnitTem1=ptCTypeTab[ptagDcTab->wType].pUnit1;
		wDotBit =(WORD)ptCTypeTab[ptagDcTab->wType].byDotBit;
		ApiDispDev[i].PowerUpIni(ptagDcTab->byName, ptagDcTab->byPinName, ApiDispDevGroup,wDotBit,*pUnitTem1,2);
		ApiDispDev[i].SetDisp(TRUE);
		ptagDcTab++;
	}
}
// ������ʾ״̬����
void AppDispOptPowerUpIni()
{
	WORD i, wDotBit;
	const VarUnits        *pUnitTem1;
	const tagDCTab        *ptagDcTab;
	const tagCTypeTab     *ptCTypeTab;
	ApiDispOptGroup[0].PowerUpIni("���1�⹦��", "ApiDispOptGroup[0]", CN_NUM_DC_OPT1,CN_NUM_DC_OPT1);
	ApiDispOptGroup[1].PowerUpIni("���2�⹦��", "ApiDispOptGroup[1]", CN_NUM_DC_OPT2,CN_NUM_DC_OPT2);
	ptCTypeTab =&g_tCTypeTab[0];
	ptagDcTab  =&g_tDCTab[EN_DC_OPT1_STR];
	for(i=0;i< CN_NUM_DC_OPT1;i++)
	{
		pUnitTem1=ptCTypeTab[ptagDcTab->wType].pUnit1;
		wDotBit =(WORD)ptCTypeTab[ptagDcTab->wType].byDotBit;
		ApiDispOpt[i].PowerUpIni(ptagDcTab->byName, ptagDcTab->byPinName, ApiDispOptGroup[0],wDotBit,*pUnitTem1,2);
		ApiDispOpt[i].SetDisp(TRUE);
		ptagDcTab++;
	}
	ptagDcTab  =&g_tDCTab[EN_DC_OPT2_STR];
	for(i= CN_NUM_DC_OPT1;i< (CN_NUM_DC_OPT1+ CN_NUM_DC_OPT2);i++)
	{
		pUnitTem1=ptCTypeTab[ptagDcTab->wType].pUnit1;
		wDotBit =(WORD)ptCTypeTab[ptagDcTab->wType].byDotBit;
		ApiDispOpt[i].PowerUpIni(ptagDcTab->byName, ptagDcTab->byPinName, ApiDispOptGroup[1],wDotBit,*pUnitTem1,2);
		ApiDispOpt[i].SetDisp(TRUE);
		ptagDcTab++;
	}
}
// ������ʾ�м�״̬
void AppDispInterPowerUpIni()
{
	WORD i;
	const tagInterTab   *ptagInterTab;
	ptagInterTab        =&g_tInterTab[0];
	ApiDispInterGroup.PowerUpIni("�ڲ���־", "ApiDispInterGroup", CN_NUM_FLAG+CN_NUM_INTER,CN_NUM_FLAG+CN_NUM_INTER);
	for(i=0;i<CN_NUM_INTER;i++)
	{
		ApiDispInter[i].PowerUpIni(ptagInterTab->byName, ptagInterTab->byPinName, ApiDispInterGroup,0,Unit_NULL,0);
		ApiDispInter[i].SetDisp(TRUE);
		ptagInterTab++;
	}
	
	const tagFlagTab   *ptagFlagTab;
	ptagFlagTab        =&g_tFlagTab[0];
	for(i=CN_NUM_INTER;i<CN_NUM_INTER+CN_NUM_FLAG;i++)
	{
		ApiDispInter[i].PowerUpIni(ptagFlagTab->byName, ptagFlagTab->byPinName, ApiDispInterGroup,0,Unit_NULL,0);
		ApiDispInter[i].SetDisp(TRUE);
		ptagFlagTab++;
	}
}


// ��ֵˢ��
void AppDispAnaPtctRef()
{
	WORD      i;
	FLOAT32   *pfAnaPtCt;
	// ����+Ʒ�ʸ���
	if(g_tagAna.byAnaPtCtChg)
	{
		pfAnaPtCt =&g_tagAna.fAnaPtCt[0];
		for(i=0;i<CN_NUM_ANA;i++)
		{
			ApiDispAna[i].SetDataCoe(*pfAnaPtCt++, 1.0000f);
		}
		ApiDispAnaGroup.Update(0);
		g_tagAna.byAnaPtCtChg=FALSE;
	}
}

bool8 AppDispAnaAmRef()
{
	WORD      i;
	tagVector *ptAnaVect;
	DWORD     *pdwAnaQ;
	// ����+Ʒ�ʸ���
	if(!g_iInter[EN_INTER_OPT_ANA])
	{
		return 1;
	}
	g_iInter[EN_INTER_OPT_ANA]=FALSE;
	// �ȴ�2ms����
	MsSleep(2);
	// ϵ������
	AppDispAnaPtctRef();

	if(g_tagAna.byAnaVecChg)
	{
		pdwAnaQ    =&g_tagAna.dwAnaQ[0];
		ptAnaVect  =&g_tagAna.tAnaVect[0];

		for(i=0;i<CN_NUM_ANA;i++)
		{
			ApiDispAna[i].PushData(ptAnaVect->dwAm, ptAnaVect->dwAngleRel,*pdwAnaQ);
			ptAnaVect++;
			pdwAnaQ++;
		}
		ApiDispAnaGroup.Update(0);
		g_tagAna.byAnaVecChg=FALSE;
	}
	else
	{
	    g_iInter[EN_INTER_OPT_ANA]=TRUE;
		return 1;
	}
	g_iInter[EN_INTER_OPT_ANA]=TRUE;
	return 0;
}

bool8 AppDispAnaAmjRef()
{
	WORD      i;
	tagVector *ptAnaVect;
	DWORD     *pdwAnaQ;
	
	// ����+Ʒ�ʸ���
	if(!g_iInter[EN_INTER_OPT_ANA_J])
	{
		return 1;
	}
	// ���ݸ��±���
	g_iInter[EN_INTER_OPT_ANA_J]=FALSE;
	// �ȴ�2ms����
	MsSleep(2);
	// ϵ������
	AppDispAnaPtctRef();

	if(g_tagAna.byAnaVecChg)
	{
		pdwAnaQ    =&g_tagAna.dwAnaQ[0];
		ptAnaVect  =&g_tagAna.tAnaVect[0];

		for(i=0;i<CN_NUM_ANA;i++)
		{
			ApiDispAna[i].PushData(ptAnaVect->dwAmJ, ptAnaVect->dwAngleRel,*pdwAnaQ);
			ptAnaVect++;
			pdwAnaQ++;
		}
		ApiDispAnaGroup.Update(0);
		g_tagAna.byAnaVecChg=FALSE;
	}
	else
	{
	    g_iInter[EN_INTER_OPT_ANA_J]=TRUE;
		return 1;
	}
	g_iInter[EN_INTER_OPT_ANA_J]=TRUE;
	return 0;
}
// Ƶ��ˢ��
bool8 AppDispFrRef()
{
	WORD      i;
	DWORD     *pdwFrCal;
	// ����+Ʒ�ʸ���
	if(!g_iInter[EN_INTER_OPT_ANA_FR])
	{
		return 1;
	}
	
	// �����������ʱ������,�˴�����ʹ��ֹͣ����
	
	//g_iInter[EN_INTER_OPT_ANA_FR]=FALSE;
	// �ȴ�2ms����
	//MsSleep(2);
	// ����+Ʒ�ʸ���
	if(g_tagAna.byFrChg)
	{
		pdwFrCal =&g_tagAna.dwFrCal[0];
		for(i=0;i<CN_NUM_CAL;i++)
		{
		// �Ƿ������ֲ�ر���
			ApiDispFr[i].PushData(*pdwFrCal,0);
			pdwFrCal++;
		}
		ApiDispFrGroup.Update(0);
		g_tagAna.byFrChg=FALSE;
	}
	else
	{
		return 1;
	}
	return 0;
}
// ֱ��ˢ��
bool8 AppDispDcRef()
{
	WORD      i;
	INT32     *piDCOut,*piDCOutFst;
	if(g_tagDC.bDCDispFresh[EN_BOARD_DC_SAM])
	{
		piDCOut    =&g_tagDC.iDCOut[EN_DC_SAM_STR];
		piDCOutFst =&g_tagDC.iDCOutFst[EN_DC_SAM_STR];
		
		for(i=0;i<CN_NUM_DC_SAM;i++)
		{
			ApiDispDc[i].PushData(*piDCOut++,*piDCOutFst++);
		}
		ApiDispDcGroup.Update(0);
		g_tagDC.bDCDispFresh[EN_BOARD_DC_SAM]=FALSE;
	}
	else
	{
		return 1;
	}
	return 0;
}
// ״̬��������ˢ��
bool8 AppDispDevRef()
{
	WORD      i;
	INT32     *piDCOut;
	if(g_tagDC.bDCDispFresh[EN_BOARD_DC_DEV])
	{
		piDCOut    =&g_tagDC.iDCOut[EN_DC_DEV_STR];
		for(i=0;i<CN_NUM_DC_DEV;i++)
		{
			ApiDispDev[i].PushData(*piDCOut++,0);
		}
		ApiDispDevGroup.Update(0);
		g_tagDC.bDCDispFresh[EN_BOARD_DC_DEV]=FALSE;
	}
	else
	{
		return 1;
	}
	
	return 0;
}
// CPU1�⹦������ˢ��
bool8 AppDispOpt1Ref()
{
	WORD      i;
	INT32     *piDCOut;
	if((!g_tagDC.bDCDispFresh[EN_BOARD_DC_OPT1_1])&&(!g_tagDC.bDCDispFresh[EN_BOARD_DC_OPT1_2]))
	{
		return 1;
	}
	piDCOut    =&g_tagDC.iDCOut[EN_DC_OPT1_STR];
	for(i=0;i<CN_NUM_DC_OPT1;i++)
	{
		ApiDispOpt[i].PushData(*piDCOut++,0);
	}
	g_tagDC.bDCDispFresh[EN_BOARD_DC_OPT1_1]=FALSE;
	g_tagDC.bDCDispFresh[EN_BOARD_DC_OPT1_2]=FALSE;
	ApiDispOptGroup[0].Update(0);
	return 0;
}

// �⹦������ˢ��
bool8 AppDispOpt2Ref()
{
	WORD      i;
	INT32     *piDCOut;
	if(g_tagDC.bDCDispFresh[EN_BOARD_DC_OPT2])
	{
		piDCOut    =&g_tagDC.iDCOut[EN_DC_OPT2_STR];
		for(i=CN_NUM_DC_OPT1;i<(CN_NUM_DC_OPT1+CN_NUM_DC_OPT2);i++)
		{
			ApiDispOpt[i].PushData(*piDCOut++,0);
		}
		ApiDispOptGroup[1].Update(0);
		g_tagDC.bDCDispFresh[EN_BOARD_DC_OPT2]=FALSE;
	}
	else
	{
		return 1;
	}
	
	return 0;
}
// �ڲ���־����ˢ��
bool8 AppDispInterRef()
{
	WORD      i;
	INT32     *piInter;
	piInter    =&g_iInter[0];
	for(i=0;i<CN_NUM_INTER;i++)
	{
	// �Ƿ������ֲ�ر���
		ApiDispInter[i].PushData(*piInter++,0);
	}
	BOOL *pbFlag;
	pbFlag    =&g_bFlag[0];
	for(i=CN_NUM_INTER;i<CN_NUM_INTER+CN_NUM_FLAG;i++)
	{
	// �Ƿ������ֲ�ر���
		ApiDispInter[i].PushData((INT32)(*pbFlag++),0);
	}
	ApiDispInterGroup.Update(0);
	return 0;
}

void AppDispPowerUpIni()
{
	AppDispAnaPowerUpIni();
	AppDispFrPowerUpIni();
	AppDispDcPowerUpIni();
	AppDispDevPowerUpIni();
	AppDispOptPowerUpIni();
	AppDispInterPowerUpIni();
}

