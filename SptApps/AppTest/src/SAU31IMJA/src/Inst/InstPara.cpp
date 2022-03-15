#include "InstResource.h"

ApiPara ProtPara[CN_NUM_PARA];
ApiParaGroup ProtParaGroup[CN_NUM_BOARD_PARA];
SalParaEditGroup HmiParaEditGroup;

void AppParaPowerUpIni()
{
	WORD i,j,k,n;
	BYTE byDotNum,byEnumNum;
	const tagParaTab       *ptParaTab;
	const tagBoardParaTab  *ptBoardParaTab;
	const tagCTypeTab      *ptCTypeTab;
	const VarUnits         *pUnitTem;
	SalEnumDes   *pEnumDes;
	tagCEnumTab  *ptCEnumTab;
	
	ptCTypeTab    =&g_tCTypeTab[0];
	ptCEnumTab    =&g_tCEnumTab[0];
	ptBoardParaTab=&g_tBoardParaTab[0];
	for(i=0;i<g_NUM_BOARD_PARA;i++)
	{
		ProtParaGroup[i].PowerUpIni(ptBoardParaTab->byName, ptBoardParaTab->byPinName,  ptBoardParaTab->wIndexNum);
		if(i== EN_BOARD_PARA_DC_COE)
		{
			// ֱ����У׼ϵ��
			ptParaTab=&g_tParaTab[ptBoardParaTab->wIndexStr];
			for(j=ptBoardParaTab->wIndexStr,k=EN_DC_SAM_STR;k<EN_DC_SAM_END;j++,k++)
			{
				pUnitTem = ptCTypeTab[ptParaTab->wType].pUnit1;
				byDotNum = ptCTypeTab[ptParaTab->wType].byDotBit;
				ProtPara[j].PowerUpIni(ptParaTab->byName,ptParaTab->byPinName, ProtParaGroup[i],ptParaTab->iValMin, ptParaTab->iValDft, ptParaTab->iValMax,byDotNum,*pUnitTem,k);
				ptParaTab++;
			}
		}
		else if((i== EN_BOARD_PARA_AM_COE)||(i== EN_BOARD_PARA_DCBC_COE))
		{
			// ģ����У׼ϵ��
			ptParaTab=&g_tParaTab[ptBoardParaTab->wIndexStr];
			for(j=ptBoardParaTab->wIndexStr,k=0;k<CN_NUM_AD;j++,k++)
			{
				pUnitTem = ptCTypeTab[ptParaTab->wType].pUnit1;
				byDotNum = ptCTypeTab[ptParaTab->wType].byDotBit;
				ProtPara[j].PowerUpIni(ptParaTab->byName,ptParaTab->byPinName, ProtParaGroup[i],ptParaTab->iValMin, ptParaTab->iValDft, ptParaTab->iValMax,byDotNum,*pUnitTem,k);
				ptParaTab++;
			}
		}
		else if(i== EN_BOARD_PARA_ANG_COE)
		{
			// ��λ����AD-0
			ptParaTab=&g_tParaTab[ptBoardParaTab->wIndexStr];
			for(j=ptBoardParaTab->wIndexStr,k=0;k<CN_NUM_JZ;j++,k++)
			{
				pUnitTem = ptCTypeTab[ptParaTab->wType].pUnit1;
				byDotNum = ptCTypeTab[ptParaTab->wType].byDotBit;
				for(n=0;n<CN_NUM_AD;n++)
				{
					if((g_tAnaTab[n].wADNo==k)&&(g_tAnaTab[n].wADChn==0))
					{
						break;
					}
				}
				n=(n==CN_NUM_AD)?0:n;
				ProtPara[j].PowerUpIni(ptParaTab->byName,ptParaTab->byPinName, ProtParaGroup[i],ptParaTab->iValMin, ptParaTab->iValDft, ptParaTab->iValMax,byDotNum,*pUnitTem,n);
				ptParaTab++;
			}
			// ��λ����AD-4
			ptParaTab=&g_tParaTab[ptBoardParaTab->wIndexStr+CN_NUM_JZ];
			for(j=ptBoardParaTab->wIndexStr+CN_NUM_JZ,k=0;k<CN_NUM_JZ;j++,k++)
			{
				pUnitTem = ptCTypeTab[ptParaTab->wType].pUnit1;
				byDotNum = ptCTypeTab[ptParaTab->wType].byDotBit;
				for(n=0;n<CN_NUM_AD;n++)
				{
					if((g_tAnaTab[n].wADNo==k)&&(g_tAnaTab[n].wADChn==4))
					{
						break;
					}
				}
				n=(n==CN_NUM_AD)?0:n;
				ProtPara[j].PowerUpIni(ptParaTab->byName,ptParaTab->byPinName, ProtParaGroup[i],ptParaTab->iValMin, ptParaTab->iValDft, ptParaTab->iValMax,byDotNum,*pUnitTem,n);
				ptParaTab++;
			}
		}
		else
		{
		
			ptParaTab=&g_tParaTab[ptBoardParaTab->wIndexStr];
			for(j=ptBoardParaTab->wIndexStr;j<ptBoardParaTab->wIndexEnd;j++)
			{
				if(ptParaTab->wType==EN_CTYPE_PARA_H)
				{
					ProtPara[j].HexPowerUpIni(ptParaTab->byName,ptParaTab->byPinName, ProtParaGroup[i],ptParaTab->iValMin, ptParaTab->iValDft, ptParaTab->iValMax, 4);
				}
				//else if(ptParaTab->wType==EN_CTYPE_PARA_MAX)
				//{
				//	ProtPara[j].BitOnOffPowerUpIni(ptParaTab->byName,ptParaTab->byPinName, ProtParaGroup[i],ptParaTab->dwValMin, ptParaTab->dwValDft, ptParaTab->dwValMax, 2);
				//}
				else if(ptParaTab->wType<EN_CTYPE_PARA_END)
				{
					pUnitTem = ptCTypeTab[ptParaTab->wType].pUnit1;
					byDotNum = ptCTypeTab[ptParaTab->wType].byDotBit;
					ProtPara[j].PowerUpIni(ptParaTab->byName,ptParaTab->byPinName, ProtParaGroup[i],ptParaTab->iValMin, ptParaTab->iValDft, ptParaTab->iValMax, byDotNum, *pUnitTem);
				}
				else
				{
					byEnumNum= ptCEnumTab[ptParaTab->wType-EN_CTYPE_PARA_END].byEnNum;
					pUnitTem = ptCEnumTab[ptParaTab->wType-EN_CTYPE_PARA_END].pUnit1;
					pEnumDes = ptCEnumTab[ptParaTab->wType-EN_CTYPE_PARA_END].eEnumDes;
					ProtPara[j].EnumPowerUpIni(ptParaTab->byName,ptParaTab->byPinName, ProtParaGroup[i],ptParaTab->iValDft, pEnumDes, byEnumNum, *pUnitTem);
				}
				ptParaTab++;
			}
		}
		ptBoardParaTab++;
	}
	HmiParaEditGroup.PowerUpIni(CN_NUM_PARA);
	// �����ϵ��Լ켰ƽ̨�����
	INT32   iChgFlag;
	DWORD   *pdwCrc= g_tagPara.dwCrc;
	
	for(i=0;i<g_NUM_BOARD_PARA;i++)
	{
		if (ProtParaGroup[i].CheckStatus() != SalParaGroup::E_OK)
		{
			//�쳣���磬�����ָ�
			if (ProtParaGroup[i].GetSaveStepFlag(0) == SalParaGroup::E_SaveStart)
			{
				ProtParaGroup[i].LoadBakParaForUse(0);
			}
			else
			{
				ProtParaGroup[i].UpdateForUse();
			}
		}
		else
		{
			ProtParaGroup[i].UpdateForUse();
		}
		// CRC����
		pdwCrc[i]=ProtParaGroup[i].GetCrc(0);
		// ��ֵ�ϵ��Լ�
		iChgFlag=ProtParaGroup[i].CheckStatus();
		if(iChgFlag!=SalParaGroup::E_OK)
		{
			G_Set_ChkIn_All(EN_CHK_PARA_STR+i,iChgFlag,0,0);
		}
	}
	// �����ϵ�Ӧ�ò����
	DWORD   *pdwPara,*pdwCoe;
	FLOAT32 *pfPara;
	WORD    wDotNum;
	WORD    *pwCfg;
	ptParaTab =&g_tParaTab[0];
	pdwPara   = g_tagPara.dwPara;
	pdwCoe    = g_tagPara.dwCoe;
	pfPara    = g_tagPara.fPara;
	pwCfg     = g_tagPara.wParaCfg;
	for(i=0;i<CN_NUM_PARA;i++)
	{
		if(ptParaTab->wType < EN_CTYPE_PARA_END)
		{
			wDotNum  = ptCTypeTab[ptParaTab->wType].byDotBit;
			pdwCoe[i]= g_dwMul[wDotNum];
		}
		else
		{
			pdwCoe[i]= g_dwMul[0];    //����ѡ�����Ͳ��������������븡����ת����ת��ϵ��Ĭ��Ϊ1
		}
		pdwPara[i]=ProtPara[i].Int32();
		pfPara[i]=ProtPara[i].Float32();
		pwCfg[i]=ptParaTab->wCfg;
		//LogMsg.Stamp()<<"��ֵ��"<<i<<"-"<<pProtPara->Float32()<<"-"<<pProtPara->Int32()<<"\n";
		ptParaTab++;
	}
	// �����������
	AppEthNetParaRef();
	// ��ʼ��Ӧ���������
	IES_IM_Para_Init();
}
void AppParaRead(DWORD dwEnStr,DWORD dwEnEnd)
{
	ApiPara *pProtPara;
	DWORD   *pdwPara;
	FLOAT32 *pfPara;
	WORD    i;
	
	if((dwEnStr>=EN_PARA_END)||(dwEnEnd>EN_PARA_END)||(dwEnEnd<=dwEnStr))
	{
		return;
	}
	
	pProtPara =&ProtPara[dwEnStr];
	pdwPara   =&g_tagPara.dwPara[dwEnStr];
	pfPara    =&g_tagPara.fPara[dwEnStr];

	for(i=dwEnStr;i<dwEnEnd;i++)
	{
		*pdwPara++ =pProtPara->Int32();
		*pfPara++  =pProtPara->Float32();
		pProtPara++;
	}
}

void AppParaInAppRef(WORD wIndex)
{
	if(wIndex==EN_BOARD_PARA_DI)
	{
		IES_IMDI_Para_Init();
	}
	else if((wIndex==EN_BOARD_PARA_DC)
	||(wIndex==EN_BOARD_PARA_DC_COE))
	{
		IES_IMDC_Para_Init();
	}
	else if((wIndex==EN_BOARD_PARA_SAM)
	||(wIndex==EN_BOARD_PARA_AM_COE)
	||(wIndex==EN_BOARD_PARA_DCBC_COE)
	||(wIndex==EN_BOARD_PARA_ANG_COE))
	{
		IES_IMSam_Para_Init();
	}
	else if(wIndex==EN_BOARD_PARA_FUN)
	{
		IES_IMLogic_Para_Init();
		IES_IMRec_Para_Init();
		IES_IMFlag_Para_Init();
		IES_IMDO_Para_Init();
	}
}
// ��ʱ����
void AppParaInRef()
{ 
	static   UINT32  dwParaChgRet,dwCrcTxCnt;
	register INT32   iChgFlag;
	register ApiParaGroup  *pProtParaGroup;
	register UINT32   i;
	const tagBoardParaTab  *ptBoardParaTab;
	pProtParaGroup=  &ProtParaGroup[0];
	ptBoardParaTab=  &g_tBoardParaTab[0];
// Ĭ�ϲ����޸ı�־1s���Զ������߼�
	if(g_bFlag[EN_FLAG_PARACHG])
	{
		if((++dwParaChgRet)>T(g_tagPara.dwPara[EN_PARA_T_PARA]))
		{
			g_bFlag[EN_FLAG_PARACHG]=FALSE;
			dwParaChgRet=0;
			dwCrcTxCnt=0;
		}
	}
	else if(dwCrcTxCnt++>CN_T5S)
	{
		g_tagPara.bCrcCom=TRUE;
	}
// CRC��ʱ���ͱ�־
	for(i=0;i<g_NUM_BOARD_PARA;i++,pProtParaGroup++,ptBoardParaTab++)
	{
		// ��ֵ�Լ�(�Լ��쳣,������Ӧ��)
	    iChgFlag=pProtParaGroup->CheckStatus();
		if(iChgFlag!=SalParaGroup::E_OK)
		{
			G_Set_ChkIn_All(EN_CHK_PARA_STR+i,iChgFlag,0,0);
			continue;
		}
		else
		{
			G_Clr_ChkIn(EN_CHK_PARA_STR+i);
		}
		// ��������
		if(pProtParaGroup->DataChangeCnt()!=g_tagPara.dwChgCnt[i])
		{
			// �������±�־ǰ��
			g_tagPara.bCrcCom=FALSE;
			g_bFlag[EN_FLAG_PARACHG]=TRUE;
			dwParaChgRet=0;
			// ����������Ӧ��
			pProtParaGroup->UpdateForUse();
			AppParaRead(ptBoardParaTab->wIndexStr,ptBoardParaTab->wIndexEnd);
			AppParaInAppRef(i);
			// CRC�ͼ�������
			g_tagPara.dwCrc[i]=pProtParaGroup->GetCrc(0);
			g_tagPara.dwChgCnt[i]=pProtParaGroup->DataChangeCnt();
			return;
		}
	}
}
bool8 AppParaCoeEditUpdate(SalParaEditGroup* EditParaGroup,WORD wIndexStr,WORD wIndexEnd,WORD wIndexGroup,BOOL *pbChn)
{
	DWORD *pdwPara,i,j;
	// �Լ�1
	if((EditParaGroup!=&HmiParaEditGroup)||(wIndexGroup>=CN_NUM_BOARD_PARA))
	{
		return 1;
	}
	if(EditParaGroup->Group()!=(SalParaGroup*)&ProtParaGroup[wIndexGroup])
	{
		return 1;
	}
	// �Լ�2
	if((wIndexStr>=g_tBoardParaTab[wIndexGroup].wIndexStr)&&(wIndexEnd<=g_tBoardParaTab[wIndexGroup].wIndexEnd)&&(wIndexStr<wIndexEnd))
	{
		pdwPara=&g_tagPara.dwParaBak[wIndexStr];
		// ���ֲ���ѡ��
		if(pbChn!=NULL)
		{
			for(i=wIndexStr,j=0;i<wIndexEnd;i++,j++)
			{	
				if(pbChn[j])
				{
					EditParaGroup->EditCell(j)->Buf()[0]= (INT32)(pdwPara[j]);
				}
			}
		}
		// ���в����洢
		else
		{
			for(i=wIndexStr,j=0;i<wIndexEnd;i++,j++)
			{	
				EditParaGroup->EditCell(j)->Buf()[0]= (INT32)(pdwPara[j]);
			}
		}
		return 0;
	}
	return 1;
}

INT32 AppParaDefault(WORD wIndex)
{
	static BOOL bParaFlag=0;
	INT32 result=0;
	if(bParaFlag)
	{
		return -2;
	}
	bParaFlag=TRUE;
	if(wIndex==CN_NULL_PINNO)
	{
		for(uint32 i=0;i<CN_NUM_BOARD_PARA;i++)
		{
			ProtParaGroup[i].DefaultData();
			int32 res = ProtParaGroup[i].CheckStatus();
			if (res!=SalParaGroup::E_OK)
			{
				AppEventOptRef(EN_OPT_PARA_INIT_FAIL_STR+wIndex);
				result--;
			}
			else
			{
				AppEventOptRef(EN_OPT_PARA_INIT_SUCC_STR+wIndex);
			}

		}
	}
	else
	{
		if(wIndex>=CN_NUM_BOARD_PARA)
		{
			bParaFlag=FALSE;
			return -1;
		}
		ProtParaGroup[wIndex].DefaultData();
		int32 res = ProtParaGroup[wIndex].CheckStatus();
		if (res!=SalParaGroup::E_OK)
		{
			AppEventOptRef(EN_OPT_PARA_INIT_FAIL_STR+wIndex);
			result--;
		}
		else
		{
			AppEventOptRef(EN_OPT_PARA_INIT_SUCC_STR+wIndex);
		}
	}
	bParaFlag=FALSE;
	return result;
}
void AppEthNetParaRef()
{
	ApiSysEthNetCfg& UsrCfg = ApiSysEthNetCfg::Instance();

	g_tDevInfor.tDevEthnet.dwIp   =UsrCfg.EthNet[0].ip.Data();
	g_tDevInfor.tDevEthnet.dwMask =UsrCfg.EthNet[0].musk.Data();
	g_tDevInfor.tDevEthnet.dwGate =UsrCfg.EthNet[0].gate.Data();
	g_tDevInfor.tDevEthnet.dwFlag =UsrCfg.EthNet[0].exInfo.Data();
	g_tDevInfor.byDevEthnet=TRUE;
}

