/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * ���ɵ��ӹɷ����޹�˾
 * Ԫ�����ƣ�����ɼ�ִ�е�Ԫ�߼�Ԫ��
 * Ԫ�����ܣ�����ɼ�ִ�е�Ԫ�߼�Ԫ��
 *     1.�����л�
 *     2.��ѹ�л�
 *     3.���಻һ��
 *     4.KKJ�Ϻ�״̬
 *     5.���ƻ�·����
 *     6.�¹���
  *    7.�����غ�բ����(����һ�ײɼ�ִ�е�Ԫ)
 *     8.�����غ�բGOOSE�ź�(���ײɼ�ִ�е�Ԫ)
 * Ԫ���汾��V1.00
 * ����ʱ�䣺2020-9-7
 * �汾�޸ģ�
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
 * V1.00 2021-2-24 ��־��������
 *================================================================================*/

#include "IES_IMPub.h"
#include "IES_IMLogic.h"
#include "IES_IMSam.h"

// ����ӿڲ���
tagIES_IMJA      gtagIES_IMJA;
// ============================================================================
// �������ܣ�KKJ\SHJ\STJλ���ж�
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMJA_Relay(tagIES_IMJA  *pgtagIES_IMJA)
{
//	register BYTE    bSHJ, bSTJ, bYHJ, bYTJ;
//	register BYTE    bKHJ,bKTJ,bKKJ;

	register BYTE    bSHJ, bSTJ, bKKJ,bTJF;

	// KKJ\SHJ\STJ\TJFλ���ж�
	bKKJ=(pgtagIES_IMJA->bKKJEna)?G_Get_DI(EN_DI_KKJ):G_Get_DI(EN_DI_OPB1_KKJ);
	bSHJ=(pgtagIES_IMJA->bSHJEna)?G_Get_DI(EN_DI_SHJ):G_Get_DI(EN_DI_OPB1_SHJ);
	bSTJ=(pgtagIES_IMJA->bSTJEna)?G_Get_DI(EN_DI_STJ):G_Get_DI(EN_DI_OPB1_STJ);
	bTJF=(pgtagIES_IMJA->bTJFEna)?G_Get_DI(EN_DI_TJF):G_Get_DI(EN_DI_OPB1_TJF);
	
	// KKJ\SHJ\STJ\TJFλ�ñ���
	G_Set_Flag(EN_FLAG_DI_KKJ,bKKJ);
	G_Set_Flag(EN_FLAG_DI_SHJ,bSHJ);
	G_Set_Flag(EN_FLAG_DI_STJ,bSTJ);
	G_Set_Flag(EN_FLAG_DI_TJF,bTJF);
	// KKJ����ģ��,ԭ�ǻ�վ��ִ�淶�߼�ͼ,Ŀǰɾ����
#if 0	
	bYHJ=G_Get_GOIN(EN_GOIN_CKHZ);
	bYTJ=G_Get_GOIN(EN_GOIN_CKTZ);
	// �غ�բ����
	bKHJ = (bSHJ | bYHJ) && (!bYTJ) && (!bYTJ);
	pgtagIES_IMJA->bKHJ=bKHJ|pgtagIES_IMJA->bKHJ;
	// �ط�բ����
	bKTJ = (bSTJ | bYTJ) && (!bYHJ) && (!bYHJ);
	pgtagIES_IMJA->bKTJ=bKTJ|pgtagIES_IMJA->bKTJ;
	// KKJλ��
	bKKJ=pgtagIES_IMJA->bKHJ&&(!pgtagIES_IMJA->bKTJ);
	pgtagIES_IMJA->bKKJ=IES_TimeRelayRun(&(pgtagIES_IMJA->tTimer_KKJ),bKKJ);
	//�ź����
	G_Set_Flag(EN_FLAG_DI_STJ,pgtagIES_IMJA->bKKJ);
#endif
}

// ============================================================================
// �������ܣ������л�
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_BusMuQH(tagIES_IMJA  *pgtagIES_IMJA)
{
	// ��������
	register BYTE		  bBusMUBS,bBusMUA,bBusMUB,bBusMUAuto; // ����״̬
	register BYTE		  bBusMUAQErr,bBusMUBQErr;			   // ĸ�߲ɼ�ִ�е�Ԫ�쳣״̬
	register BYTE		  bBusMUATest,bBusMUBTest;			   // ĸ�߲ɼ�ִ�е�Ԫ����״̬
	register BYTE		  bBusMUAOK,bBusMUBOK;				   // ĸ�߲ɼ�ִ�е�Ԫ����״̬
	// �������
	register BYTE		  bBusMU=CN_MULink_BC;				   // ����ѡ���м���
	register BYTE         bBsERR=FALSE;//,bLinkAERR=FALSE,bLinkBERR=FALSE;// �澯��־
	// �����л�����Ͷ�뼰����
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
	// A��B������������� ���������л�Ͷ�˿���
	bBusMUAQErr=g_tAlmState.bAlmIn[EN_ALM_SVLINK_QA]|g_tAlmState.bAlmIn[EN_ALM_SVLINK_CFGA];
	bBusMUATest=g_tAlmState.bAlmIn[EN_ALM_SVLINK_TESTA];
	
	bBusMUBQErr=g_tAlmState.bAlmIn[EN_ALM_SVLINK_QB]|g_tAlmState.bAlmIn[EN_ALM_SVLINK_CFGB];
	bBusMUBTest=g_tAlmState.bAlmIn[EN_ALM_SVLINK_TESTB];
	//����A����̬�ж�[]
	bBusMUAOK=IES_TimeRelayRun(&pgtagIES_IMJA->tTimer_SvA,(!(bBusMUAQErr|bBusMUATest)));
	//����B����̬�ж�[]
	bBusMUBOK=IES_TimeRelayRun(&pgtagIES_IMJA->tTimer_SvB,(!(bBusMUBQErr|bBusMUBTest)));
	G_Set_Flag(EN_FLAG_SV_A,bBusMUAOK);
	G_Set_Flag(EN_FLAG_SV_B,bBusMUBOK);
	
	// �����л��˳�,�Ƿ�������װ��
	if((!G_Get_Flag(EN_FLAG_LNK_ENA))||G_Get_AlmIn_P[EN_ALM_BS_LINKQH])
	{
		// Ĭ��ȡ����A��(�����ǰB��,���л���A��???,���Ǳ��ֲ���)
		if(G_Get_Flag(EN_FLAG_LNK_B)||(!G_Get_Flag(EN_FLAG_LNK_A)))
		{
			G_Set_Flag(EN_FLAG_LNK_B,FALSE);
			G_Set_Flag(EN_FLAG_LNK_A,TRUE);
			G_Set_Flag(EN_FLAG_LNK_BC,FALSE);
			// �����л�ʹ�ܱ�־
			pgtagIES_IMJA->bBusMuQh=TRUE;
		}
		// ����澯����
		G_Set_AlmIn(EN_ALM_XZBS,FALSE);
		return;
	}
	//��բλ���쳣�ϳ�
	bBusMUA   =G_Get_DI(EN_DI_LNK_A);
	bBusMUB   =G_Get_DI(EN_DI_LNK_B);
	bBusMUAuto=G_Get_DI(EN_DI_LNK_AUTO);
	//ѡ�����״̬�쳣
	bBusMUBS=bBusMUA+bBusMUB+bBusMUAuto;
	if(bBusMUBS!=1)
	{
		bBsERR=TRUE;
	}
	//����A
	else if(bBusMUA)
	{
		bBusMU=CN_MULink_A;
	}
	//����B
	else if(bBusMUB)
	{
		bBusMU=CN_MULink_B;
	}
	//�Զ�״̬
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
	// �ϵ��ʼ��״̬
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
			// �����л�ʹ�ܱ�־
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
			// �����л�ʹ�ܱ�־
			pgtagIES_IMJA->bBusMuQh=TRUE;
		}
		//bLinkAERR=FALSE;
		//bLinkBERR=!bBusMUBOK;
	}
	G_Set_AlmIn(EN_ALM_XZBS,bBsERR);
}

// ============================================================================
// �������ܣ���ѹ�л�
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_VolQH(tagIES_IMJA  *pgtagIES_IMJA)
{
	//��������
	register BYTE         bXSWI1,bXSWI2;               // ��բλ����Ϣ
	//register WORD i;
	//register DWORD *pdwQ,dwQ;
	//�������
	register BYTE         b12QH=CN_VolQH_BC;           // ��/��ĸת���м���
	register BYTE         bXSWIERR=FALSE,bPtActERR=FALSE,bPtRetERR=FALSE;// �澯��־
	// �����л�����Ͷ�뼰����
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

	//��բλ���쳣�ϳ�
	bXSWI1=G_Get_DPI(EN_DPI_XSWI01);
	bXSWI2=G_Get_DPI(EN_DPI_XSWI02);
	//��ѹ�л�Ͷ����˫ĸ��
	if(G_Get_Flag(EN_FLAG_V_ENA)&&(!G_Get_AlmIn_P[EN_ALM_BS_VQH]))
	{
		//��բλ���쳣
		if((bXSWI1==CN_DPI_STP)||(bXSWI1==CN_DPI_CHK)||(bXSWI2==CN_DPI_STP)||(bXSWI2==CN_DPI_CHK))
		{
			bXSWIERR=TRUE;
		}
		//��ѹȡ��ĸ
		if((bXSWI1==CN_DPI_CLS)&&(bXSWI2!=CN_DPI_CLS))
		{
			b12QH=CN_VolQH_1;
		}
		//��ѹȡ��ĸ
		else if((bXSWI2==CN_DPI_CLS)&&(bXSWI1!=CN_DPI_CLS))
		{
			b12QH=CN_VolQH_2;
		}
		//PT�л�ͬʱ����
		else if((bXSWI2==CN_DPI_OPN)&&(bXSWI1==CN_DPI_OPN))
		{
			b12QH=CN_VolQH_NULL;
			bPtRetERR=TRUE;
		}
		// PT�л�ͬʱ����
		else if((bXSWI2==CN_DPI_CLS)&&(bXSWI1==CN_DPI_CLS))
		{
			b12QH=CN_VolQH_1;
			bPtActERR=TRUE;
		}
		// ����״̬
		else
		{
			b12QH=CN_VolQH_BC;
		}
	}
	// ��ĸ��
	else
	{
		b12QH=CN_VolQH_1;
		bPtActERR=FALSE;
		bPtRetERR=FALSE;
		bXSWIERR=FALSE;
		IES_TimeRelayStop(&pgtagIES_IMJA->tTimer_PTRet);
	}
	//�ϵ��ʼ������
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
		// �ϵ籣��״̬
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
	// �Ǳ���״̬,���Ʒ����Ч��־
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
			// ��ѹ�л�ʹ�ܱ�־
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
			// ��ѹ�л�ʹ�ܱ�־
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
				// ��ѹ�л�ʹ�ܱ�־
				//pgtagIES_IMJA->bVolQh=TRUE;
			}
		}
	}
	else
	{
		//����A����̬�ж�[]
		IES_TimeRelayStop(&pgtagIES_IMJA->tTimer_PTRet);
	}
}
// ============================================================================
// �������ܣ��л������·�
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_VolPub(tagIES_IMJA  *pgtagIES_IMJA)
{
	WORD  wUxAd1Set1,wUxAd1Set2,wUxAd2Set1,wUxAd2Set2,wOffSet=0;
    DWORD  dwCfg1=0;
#if(CN_DEV_CPU1)
    DWORD  dwCfg2=0;
	// ��ѹ�л�,�޼����������л�
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
			// A��Iĸ��
			if(G_Get_Flag(EN_FLAG_LNK_A)&&G_Get_Flag(EN_FLAG_V_I))
			{
				IES_IMSam_SvPub_Chg(EN_ANA_SVA1_STR,EN_ANA_SVA1_STR,EN_LINK_END,dwCfg1,dwCfg2);
			}
			// A��IIĸ��
			else if(G_Get_Flag(EN_FLAG_LNK_A)&&G_Get_Flag(EN_FLAG_V_II))
			{
				IES_IMSam_SvPub_Chg(EN_ANA_SVA1_STR,EN_ANA_SVA2_STR,EN_LINK_END,dwCfg1,dwCfg2);
			}
			// B��Iĸ��
			else if(G_Get_Flag(EN_FLAG_LNK_B)&&G_Get_Flag(EN_FLAG_V_I))
			{
				IES_IMSam_SvPub_Chg(EN_ANA_SVA1_STR,EN_ANA_SVB1_STR,EN_LINK_END,dwCfg1,dwCfg2);
			}
			// B��IIĸ��
			else if(G_Get_Flag(EN_FLAG_LNK_B)&&G_Get_Flag(EN_FLAG_V_II))
			{
				IES_IMSam_SvPub_Chg(EN_ANA_SVA1_STR,EN_ANA_SVB2_STR,EN_LINK_END,dwCfg1,dwCfg2);
			}
			// ��ѹ�л��޽��
			else if(G_Get_Flag(EN_FLAG_LNK_A))
			{
				IES_IMSam_SvPub_Chg(EN_ANA_SVA1_STR,EN_ANA_SVA1_STR,EN_LINK_END,dwCfg1,dwCfg2);
			}
			// ��ѹ�л��޽��
			else if(G_Get_Flag(EN_FLAG_LNK_B))
			{
				IES_IMSam_SvPub_Chg(EN_ANA_SVA1_STR,EN_ANA_SVB1_STR,EN_LINK_END,dwCfg1,dwCfg2);
			}
		}
	}
#endif
	// Ux�����������
	// �ϵ��ʼ�����������¡���ѹ�л������,����Ux����
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
			    // ��ѡ��
			    case 0:
			        wUxAd1Set1=EN_ANA_UX1;
			        wUxAd2Set1=EN_ANA_UX2;
			        break;
			        // ѡ��ֱ��Ua
			    case 1:
			        wUxAd1Set1=EN_ANA_UA1;
			        wUxAd2Set1=EN_ANA_UA2;
			        break;
			        // ѡ��ֱ��Ub
			    case 2:
			        wUxAd1Set1=EN_ANA_UB1;
				    wUxAd2Set1=EN_ANA_UB2;
				    break;
				    // ѡ��ֱ��Uc
			    case 3:
			        wUxAd1Set1=EN_ANA_UC1;
			        wUxAd2Set1=EN_ANA_UC2;
			        break;
			        // ѡ��ֱ��Uab
			    case 4:
			        wUxAd1Set1=EN_ANA_UA1;
			        wUxAd1Set2=EN_ANA_UB1;
			        wUxAd2Set1=EN_ANA_UA2;
			        wUxAd2Set2=EN_ANA_UB2;
			        break;
			        // ѡ��ֱ��Ubc
			    case 5:
			        wUxAd1Set1=EN_ANA_UB1;
				    wUxAd1Set2=EN_ANA_UC1;
				    wUxAd2Set1=EN_ANA_UB2;
				    wUxAd2Set2=EN_ANA_UC2;
				    break;
				    // ѡ��ֱ��Uca
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
				// ѡ�༶��Ua
				case 7:
				   wUxAd1Set1=EN_ANA_SVA1_UA1+wOffSet;
				   wUxAd2Set1=EN_ANA_SVA1_UA2+wOffSet;
				   break;
				   // ѡ�༶��Ub
				case 8:
				   wUxAd1Set1=EN_ANA_SVA1_UB1+wOffSet;
				   wUxAd2Set1=EN_ANA_SVA1_UB2+wOffSet;
				   break;
				   // ѡ�༶��Uc
				case 9:
				   wUxAd1Set1=EN_ANA_SVA1_UC1+wOffSet;
				   wUxAd2Set1=EN_ANA_SVA1_UC2+wOffSet;
				   break;
				   // ѡ�༶��Uab
				case 10:
				   wUxAd1Set1=EN_ANA_SVA1_UA1+wOffSet;
				   wUxAd1Set2=EN_ANA_SVA1_UB1+wOffSet;
				   wUxAd2Set1=EN_ANA_SVA1_UA2+wOffSet;
				   wUxAd2Set2=EN_ANA_SVA1_UB2+wOffSet;
				   break;
				   // ѡ�༶��Ubc
				case 11:
				   wUxAd1Set1=EN_ANA_SVA1_UB1+wOffSet;
				   wUxAd1Set2=EN_ANA_SVA1_UC1+wOffSet;
				   wUxAd2Set1=EN_ANA_SVA1_UB2+wOffSet;
				   wUxAd2Set2=EN_ANA_SVA1_UC2+wOffSet;
				   break;
				   // ѡ�༶��Uca
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
// �������ܣ�����ת�澯
// ���������
// ���������
// ����ֵ��  ��
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
	// ����ң���ݶ�88��,
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
// �������ܣ����ƻ�·����
// �����������բ��·����\��բ��·����
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMJA_KHDX(tagIES_IMJA  *pgtagIES_IMJA)
{
	register BYTE    bTWJ,bHWJ;
	register BYTE    bKHDX1=FALSE,bKHDX2=FALSE;
	bTWJ   =G_Get_DI(EN_DI_OPB1_TWJ);
	bHWJ   =G_Get_DI(EN_DI_OPB1_HWJ);
	bKHDX1 =!(bTWJ^bHWJ);
	// ��ʱ������˫��Ȧ
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
// �������ܣ��¹���
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMJA_SGZ(tagIES_IMJA  *pgtagIES_IMJA)
{
	register BYTE    bTWJ,bKKJ,bSGZ;
	// Ӧ��ʹ�û�·���ӻ���ʹ�ö�·��λ��,�ݶ�ʹ�ö�·��λ��
	bTWJ=G_Get_DI(EN_DI_XCBR_OPN);
	bKKJ=G_Get_Flag(EN_FLAG_DI_KKJ);
	bSGZ=bTWJ&bKKJ;
	G_Set_AlmIn(EN_ALM_SGZ,bSGZ);
}
// ============================================================================
// �������ܣ������غ�բ����(����һ�ײɼ�ִ�е�Ԫ)
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMJA_BSCH(tagIES_IMJA  *pgtagIES_IMJA)
{
	register BYTE    bYHJ,bYTJ,bSHJ,bSTJ,bBSCH,bTJF;// Ӳ����
	register BYTE    bTJRGoIn;				  // GOOSE�����ϲ�
	register BYTE    bBSCHGoIn;				  // GOOSE�����غ�բ�ϲ�
	register BYTE    bBSCHInit;				  // �ϵ����
	register BYTE    bBSCHDO;				  // �����غ�բ���ںϲ�
	register BYTE    bBSCHGO;				  // �����غ�բGoose���ںϲ�
	
	// ң��(�ֺ�)
	bYHJ=G_Get_GOIN(EN_GOIN_CKHZ);
	bSHJ=G_Get_Flag(EN_FLAG_DI_SHJ);
	// ң��(����)
	bYTJ=G_Get_GOIN(EN_GOIN_CKTZ);
	bSTJ=G_Get_Flag(EN_FLAG_DI_STJ);
	// ң��(����)���ر��ֱ�־
	if(pgtagIES_IMJA->bYTBschBcEna)
	{
		pgtagIES_IMJA->bYTBschBc=(pgtagIES_IMJA->bYTBschBc|bYTJ|bSTJ)&&(!(bYHJ|bSHJ));
	}
	else
	{
		pgtagIES_IMJA->bYTBschBc=FALSE;
	}
	// ֱ��(��־ѡ��)
	bTJF=G_Get_Flag(EN_FLAG_DI_TJF);
	// GOOSE����(�����ϳ�)
	bTJRGoIn=G_Get_ActOut(EN_ACT_BHYT);
	// GOOSE�����غ�(��־�ϳ�)
	bBSCHGoIn=G_Get_Flag(EN_FLAG_GOIN_BHBC);
	// ����һ�ױ���
	bBSCHDO=pgtagIES_IMJA->bYTBschBc|bYHJ|bYTJ|bSHJ|bSTJ|bTJF|bTJRGoIn|bBSCHGoIn;
	G_Set_AlmIn(EN_ALM_BSCH_OTH,bBSCHDO);
	// װ���ϵ�����غ�բ
	if(!pgtagIES_IMJA->dwPWInit)
	{
		pgtagIES_IMJA->tTimer_BschInit.bStatusOut=TRUE;
	}
	bBSCHInit=IES_TimeRelayRun(&pgtagIES_IMJA->tTimer_BschInit,FALSE);
	// ��һ�ױ��ؿ���
	bBSCH=G_Get_DI(EN_DI_BC_OTH);
	// GOOSE���ط���
	bBSCHGO=bBSCHDO|bBSCH|bBSCHInit;
	// ĸ��CPU������غ�բ�ź���Ҫ��CPU������ṩ��־
	G_Set_AlmIn(EN_ALM_BSCH,bBSCHGO);
}
// ============================================================================
// �������ܣ������ɼ�ִ�е�Ԫ�߼�������ʼ��
// ���������
// ���������
// ����ֵ��  ��
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
	// λ�ò���
	pgtagIES_IMJA->bDevEna =G_Get_PARA_I(EN_PARA_TYPE_DEV);
	pgtagIES_IMJA->bKKJEna =G_Get_PARA_I(EN_PARA_TYPE_KKJ);
	pgtagIES_IMJA->bSHJEna =G_Get_PARA_I(EN_PARA_TYPE_SHJ);
	pgtagIES_IMJA->bSTJEna =G_Get_PARA_I(EN_PARA_TYPE_STJ);
	pgtagIES_IMJA->bTJFEna =G_Get_PARA_I(EN_PARA_TYPE_TJF);
	//dwTimeActSet=G_Get_PARA_I(EN_PARA_T_KKJ);
	//IES_TimeRelaySet(&(pgtagIES_IMJA->tTimer_KKJ),T(dwTimeActSet), CN_T1S);
	// �����л�����ѹ�л����
	pgtagIES_IMJA->bBusMuQhEna =G_Get_PARA_I(EN_PARA_ENA_LNK);
	pgtagIES_IMJA->bVolQhEna   =G_Get_PARA_I(EN_PARA_ENA_VQH);
	// PTͬʱ����ȷ����ʱ
	dwTimeActSet=G_Get_PARA_I(EN_PARA_T_VQH_RET_RLY);
	IES_TimeRelaySet(&(pgtagIES_IMJA->tTimer_PTRet), T(dwTimeActSet), 0);
	// ����A SV������ʱ��
	dwTimeActSet=G_Get_PARA_I(EN_PARA_T_SVOK);
	IES_TimeRelaySet(&(pgtagIES_IMJA->tTimer_SvA), T(dwTimeActSet), 0);
	// ����B SV������ʱ��
	IES_TimeRelaySet(&(pgtagIES_IMJA->tTimer_SvB), T(dwTimeActSet), 0);
	// ��ѹ���뷽ʽѡ��
	//pgtagIES_IMJA->bVolType    =G_Get_PARA_I(EN_PARA_TYPE_MSAM);
	if(pgtagIES_IMJA->dwUxPhase !=G_Get_PARA_I(EN_PARA_TYPE_UxSAM))
	{
		pgtagIES_IMJA->dwUxPhase=G_Get_PARA_I(EN_PARA_TYPE_UxSAM);
		pgtagIES_IMJA->bUxPhaseRef=TRUE;
	}
	// ���಻һ��ң�Ŷ���
	pgtagIES_IMJA->dwSxbyz     = G_Get_PARA_I(EN_PARA_SXBYZ_YX);           // ���಻һ��
	// �����غ�բ��ز���
	pgtagIES_IMJA->bYTBschBcEna = G_Get_PARA_I(EN_PARA_ENA_BSBC);         // ң��(STJ)�����غ�բ����Ͷ��
	dwTimeRetSet = G_Get_PARA_I(EN_PARA_T_BSCH_INIT);                     // װ���ϵ�����غ�բ����ʱ��
	IES_TimeRelaySet(&(pgtagIES_IMJA->tTimer_BschInit), 0, T(dwTimeRetSet));
}
// ============================================================================
// �������ܣ������ɼ�ִ�е�Ԫ�߼��ϵ��ʼ��
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMLogic_Init()
{
	IES_memset(&gtagIES_IMJA,0x0,sizeof(gtagIES_IMJA));
	IES_RamScanAdd(&gtagIES_IMJA.byRamScan1);
	IES_RamScanAdd(&gtagIES_IMJA.byRamScan2);
}
// ============================================================================
// �������ܣ������ɼ�ִ�е�Ԫ�߼�������
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMLogic()
{
	tagIES_IMJA     *pgtagIES_IMJA;
	pgtagIES_IMJA = &gtagIES_IMJA;
	if(pgtagIES_IMJA->dwInit)
	{
		// ��ʱһ���ж�,�������κα���;
		pgtagIES_IMJA->dwInit=FALSE;
		return;
	}	
	// λ���ж�
	IES_IMJA_Relay(pgtagIES_IMJA);
#if(CN_DEV_CPU1)
	// �����л�
	IES_BusMuQH(pgtagIES_IMJA);
	// ��ѹ�л�
	IES_VolQH(pgtagIES_IMJA);
#endif
	// �л��������
	IES_VolPub(pgtagIES_IMJA);
	// ����ת�澯
	IES_IMJA_Alm(pgtagIES_IMJA);
	// ���ƻ�·�����ж�
	IES_IMJA_KHDX(pgtagIES_IMJA);
	// �¹����ж�
	IES_IMJA_SGZ(pgtagIES_IMJA);
	// �����غ�բ�ж�
	IES_IMJA_BSCH(pgtagIES_IMJA);
	// �ϵ��ʼ����λ
	pgtagIES_IMJA->dwPWInit=TRUE;
}

