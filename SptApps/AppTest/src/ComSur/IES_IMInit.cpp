
#include "IES_IMInit.h"
#include "InstResource.h"
/*================================================================================
 * �ļ���������ʼ��
 * �ļ��汾: V1.00
 * ����ʱ��:
 * �汾�޶�:
 * �޶���Ա:
 *================================================================================*/
#define AppLog   LogErr
// ============================================================================
// �������ܣ�ȫ�ֳ������Լ�
// �����������
// �����������
// ����ֵ����
// ============================================================================
void IES_IMInit_PubTabChk(void)
{
	register DWORD	 dwLoop;
	register DWORD	 dwErrFlg=0;
	register DWORD	 dwErrIndex=0;
	const tagDTypeTab  *ptDTypeTab;
	const tagCfgTab    *ptCfgTab;
	// ���ݳ������Լ�
	ptDTypeTab=&g_tDTypeTab[0];
	if(g_NUM_DTYPE!=CN_NUM_DTYPE)
	{
		AppLog<<"�������ͳ��������ô���:g_NUM_DTYPE="<<g_NUM_DTYPE<<"CN_NUM_DTYPE="<<CN_NUM_DTYPE<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_DTYPE;dwLoop++)
	{
		if(ptDTypeTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			AppLog<<"�������ͳ�����˳�����ô���:Index=" << dwLoop << "\n";
		}
		if((ptDTypeTab->bTabAtr==NULL)||(ptDTypeTab->bDatAtr==NULL))
		{
			dwErrFlg|=CN_CONST_CHK_ADDR;
			dwErrIndex=dwLoop;
			AppLog<<"�������ͳ������ַ���ô���:Index=" << dwLoop << "\n";
			//printf("�������ͳ������ַ���ô���:Index=%d\n",dwLoop);
		}
		if(ptDTypeTab->wDatNumCal!=ptDTypeTab->wDatNum)
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			AppLog<< "�������ͳ��������ݸ������ô���:Index=" << dwLoop << "\n";
		}
		if((ptDTypeTab->byName[CN_LEN_NAME-1]!=0)||(ptDTypeTab->bPinAdd[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			AppLog<< "�������ͳ��������Ƴ���Խ��:Index=" << dwLoop << "\n";
		}
		ptDTypeTab++;
	}
	
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_CFG_DTYPE,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_CFG_DTYPE,TRUE);
	}
	// ���ó������Լ�
	dwErrFlg=0;
	dwErrIndex=0;
	ptCfgTab=&g_tCfgTab[0];
	if(g_NUM_CFG!=CN_NUM_CFG)
	{
		AppLog<<"�����ೣ�������ô���:g_NUM_CFG="<<g_NUM_CFG<<"CN_NUM_CFG="<<CN_NUM_CFG<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_CFG;dwLoop++)
	{
		if(ptCfgTab->wIndex!=(dwLoop+EN_CFG_STR))
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			AppLog<<"�����ೣ����˳�����ô���:Index=" << dwLoop << "\n";
		}
		if(ptCfgTab->dwDatNumCal!=ptCfgTab->dwDatNum)
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			AppLog<< "�����ೣ�������ݸ������ô���:Index=" << dwLoop << "\n";
		}
		if((ptCfgTab->byName[CN_LEN_NAME-1]!=0)||(ptCfgTab->bPinAdd[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			AppLog<< "�����ೣ�������Ƴ���Խ��:Index=" << dwLoop << "\n";
		}
		ptCfgTab++;
	}
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_CFG_DTYPE+DB31,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_CFG_DTYPE,TRUE);
	}

}

// ============================================================================
// �������ܣ�ģ�����������Լ�
// �����������
// �����������
// ����ֵ����
// ============================================================================
void IES_IMInit_SamTabChk(void)
{
	register DWORD   dwLoop;
	register DWORD   dwErrFlg=0;
	register DWORD   dwErrIndex=0;
	const tagAnaTab  *ptAnaTab;
	const tagCalTab  *ptCalTab;
	const tagSvPubTab *ptSvPubTab;
	const tagBoardAnaTab  *ptBoardTab;

	// ģ�����������Լ�
	ptAnaTab=&g_tAnaTab[0];
	if(g_NUM_ANA!=CN_NUM_ANA)
	{
		AppLog<< "ģ�������������ô���:g_NUM_ANA=" << g_NUM_ANA << "CN_NUM_ANA=" << CN_NUM_ANA << "\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_ANA;dwLoop++)
	{
		if(ptAnaTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			AppLog<< "ģ����������˳�����ô���:Index=" << dwLoop  << "\n";

		}
		if((ptAnaTab->wChanType>=EN_CTYPE_ANA_END)||(ptAnaTab->wChanType<EN_CTYPE_ANA_STR))
		{
			dwErrFlg|=CN_CONST_CHK_TYPE;
			dwErrIndex=dwLoop;
			AppLog<< "ģ����������ͨ���������ô���:Index=" << dwLoop << "wChanType=" << ptAnaTab->wChanType << "\n";
		}
		if(dwLoop<EN_ANA_SAM_END)
		{
			if((ptAnaTab->wParaFst<EN_PARA_SAM_STR)||(ptAnaTab->wParaFst>=EN_PARA_SAM_END)
			 ||(ptAnaTab->wParaScd<EN_PARA_SAM_STR)||(ptAnaTab->wParaScd>=EN_PARA_SAM_END)
			 ||(ptAnaTab->wFrmNo>=EN_BOARD_SAM_END)
			 ||(ptAnaTab->wADNo>=CN_NUM_JZ)||(ptAnaTab->wADChn>=7))
			 {
				dwErrFlg|=CN_CONST_CHK_PARA1;
				dwErrIndex=dwLoop;
				AppLog<< "ֱ��ģ����������������ô���:Index=" << dwLoop << "wParaFst=" << ptAnaTab->wParaFst<<    \
					"wParaScd=" << ptAnaTab->wParaScd<< "wFrmNo=" << ptAnaTab->wFrmNo<< "wADNo=" << ptAnaTab->wADNo <<      \
					"wADChn=" << ptAnaTab->wADChn << "\n";

			 }

		}
		else if(dwLoop<EN_ANA_JZ_END)
		{
			if((ptAnaTab->wParaFst!=CN_NULL_PINNO)
			 ||(ptAnaTab->wParaScd!=CN_NULL_PINNO)
			 ||(ptAnaTab->wFrmNo>=EN_BOARD_SAM_END)
			 ||(ptAnaTab->wADNo>=CN_NUM_JZ)||(ptAnaTab->wADChn!=7))
			{
				dwErrFlg|=CN_CONST_CHK_PARA1;
				dwErrIndex=dwLoop;
				AppLog<< "��׼ģ����������������ô���:Index=" << dwLoop << "wParaFst=" << ptAnaTab->wParaFst << \
					"wParaScd=" << ptAnaTab->wParaScd << "wFrmNo=" << ptAnaTab->wFrmNo << "wADNo=" << ptAnaTab->wADNo << \
					"wADChn=" << ptAnaTab->wADChn << "\n";
			}
		}
		else if(dwLoop<EN_ANA_SV_END)
		{
			if((ptAnaTab->wParaFst<EN_PARA_SAM_STR)||(ptAnaTab->wParaFst>=EN_PARA_SAM_END)
			 ||(ptAnaTab->wParaScd<EN_PARA_SAM_STR)||(ptAnaTab->wParaScd>=EN_PARA_SAM_END)
			 ||(ptAnaTab->wFrmNo>=EN_BOARD_SAM_END)
			 ||(ptAnaTab->wADNo!=CN_NULL_PINNO)||(ptAnaTab->wADChn!=CN_NULL_PINNO))
			{
				dwErrFlg|=CN_CONST_CHK_PARA1;
				dwErrIndex=dwLoop;
				AppLog<< "ģ����������������ô���:Index=" << dwLoop << "wParaFst=" << ptAnaTab->wParaFst << \
					"wParaScd=" << ptAnaTab->wParaScd << "wFrmNo=" << ptAnaTab->wFrmNo << "wADNo=" << ptAnaTab->wADNo << \
					"wADChn=" << ptAnaTab->wADChn << "\n";

			}
		}
		else
		{
			if((ptAnaTab->wParaFst!=CN_NULL_PINNO)
			||(ptAnaTab->wParaScd!=CN_NULL_PINNO)
			||(ptAnaTab->wADNo!=CN_NULL_PINNO)||(ptAnaTab->wADChn!=CN_NULL_PINNO))
			{
				dwErrFlg|=CN_CONST_CHK_PARA1;
				dwErrIndex=dwLoop;
				AppLog<< "����ģ����������������ô���:Index=" << dwLoop << "wParaFst=" << ptAnaTab->wParaFst << \
					"wParaScd=" << ptAnaTab->wParaScd << "wFrmNo=" << ptAnaTab->wFrmNo << "wADNo=" << ptAnaTab->wADNo << \
					"wADChn=" << ptAnaTab->wADChn << "\n";
			}
		}
		if((ptAnaTab->byName[CN_LEN_NAME-1]!=0)||(ptAnaTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			AppLog<< "ģ�������������Ƴ���Խ��:Index=" << dwLoop << "\n";
		}
		ptAnaTab++;
	}
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_DTYPE_ANA,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_DTYPE_ANA,TRUE);
	}
	// SVPUB�������Լ�
	dwErrFlg=0;
	dwErrIndex=0;
	ptSvPubTab=&g_tSvPubTab[0];
	for(dwLoop=0;dwLoop<g_NUM_SVPUB;dwLoop++)
	{
		if(((ptSvPubTab->wStdIndex>=CN_NUM_ANA)&&(ptSvPubTab->wStdIndex!=CN_NULL_PINNO))
			||((ptSvPubTab->wAnaIndex>=CN_NUM_ANA)&&(ptSvPubTab->wAnaIndex!=CN_NULL_PINNO))
			||((ptSvPubTab->wAnaIndex2>=CN_NUM_ANA)&&(ptSvPubTab->wAnaIndex2!=CN_NULL_PINNO)))
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			AppLog<< "SUPUB���������ô���:Index=" << dwLoop << "\n";
		}
		//�̵�ַ��ϣ�������Լ�(��)
		ptSvPubTab++;
	}
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_CFG_SAM_PUB,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_CFG_SAM_PUB,TRUE);
	}
	// ģ�����忨�������Լ�
	dwErrFlg=0;
	dwErrIndex=0;
	ptBoardTab=&g_tBoardSamTab[0];
	if(g_NUM_BOARDSAM!=CN_NUM_BOARD_SAM)
	{
		AppLog<< "ģ�����忨���ô���:g_NUM_BOARDSAM=" << g_NUM_BOARDSAM << "CN_NUM_BOARD_SAM="<< CN_NUM_BOARD_SAM<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_BOARDSAM;dwLoop++)
	{
		if((ptBoardTab->wIndex !=dwLoop))
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			AppLog<< "ģ�����忨���ô���:Index=" << dwLoop << "\n";
		}
		// �ݶ������忨ͨ����󲻳���32��
		if(ptBoardTab->wIndexNum>=32)
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			AppLog<< "ģ�����忨ͨ���������ô���:Index=" << dwLoop << "\n";
		}
		
		if((ptBoardTab->byName[CN_LEN_NAME-1]!=0)||(ptBoardTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			AppLog<< "ģ�����忨���������Ƴ���Խ��:Index=" << dwLoop << "\n";
		}
		ptBoardTab++;
	}
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_CFG_SAM_BOARD,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_CFG_SAM_BOARD,TRUE);
	}
	// ģ�����������Լ�
	dwErrFlg=0;
	dwErrIndex=0;
	ptCalTab=&g_tCalTab[0];
	if(g_NUM_CAL!=CN_NUM_CAL)
	{
		AppLog<< "CAL���������ô���:g_NUM_CAL=" << g_NUM_CAL<< "CN_NUM_CAL ="<< CN_NUM_CAL << "\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_CAL;dwLoop++)
	{
		if(ptCalTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			AppLog<< "CAL������˳�����ô���:Index=" << dwLoop << "\n";
		}
		if((ptCalTab->wChanType>=EN_CTYPE_CAL_END)||(ptCalTab->wChanType<EN_CTYPE_CAL_STR))
		{
			dwErrFlg|=CN_CONST_CHK_TYPE;
			dwErrIndex=dwLoop;
			AppLog<< "CAL������ͨ���������ô���:Index=" << dwLoop<<"wChanType="<< ptCalTab->wChanType << "\n";
		}
		if((ptCalTab->wSrcDType==EN_DTYPE_ANA)
	   &&(((ptCalTab->wSrcIndex[0]>=CN_NUM_ANA)&&(ptCalTab->wSrcIndex[0]!=CN_NULL_PINNO))
		||((ptCalTab->wSrcIndex[1]>=CN_NUM_ANA)&&(ptCalTab->wSrcIndex[1]!=CN_NULL_PINNO))
		||((ptCalTab->wSrcIndex[2]>=CN_NUM_ANA)&&(ptCalTab->wSrcIndex[2]!=CN_NULL_PINNO))))
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			AppLog<< "CAL����������ԴANA���ô���:Index=" << dwLoop << "wSrcDType=" << ptCalTab->wSrcDType \
				<< "wSrcIndex[0]=" << ptCalTab->wSrcIndex[0] << "wSrcIndex[1]=" << ptCalTab->wSrcIndex[1] << "wSrcIndex[2]=" << ptCalTab->wSrcIndex[2] << "\n";
		}
		else if(ptCalTab->wSrcDType != EN_DTYPE_ANA)
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			AppLog<<"CAL����������Դ���ô���:Index="<<dwLoop<<"wSrcDType="<<ptCalTab->wSrcDType<<"\n";

		}
		if (((ptCalTab->wParaIndex >= EN_PARA_SAM_END)||(ptCalTab->wParaIndex < EN_PARA_SAM_STR))&& (ptCalTab->wParaIndex != CN_NULL_PINNO))
		{
			dwErrFlg |= CN_CONST_CHK_PARA1;
			dwErrIndex=dwLoop;
			AppLog<<"CAL����������Դ���ô���:Index="<<dwLoop<<"wParaIndex="<<ptCalTab->wParaIndex<<"\n";

		}
		
		if((ptCalTab->byName[CN_LEN_NAME-1]!=0)||(ptCalTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			AppLog<<"CAL���������Ƴ���Խ��:Index="<<dwLoop<<"\n";

		}
		//�̵�ַ��ϣ�������Լ�(��)
		ptCalTab++;
	}
	
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_DTYPE_CAL,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_DTYPE_CAL,TRUE);
	}
}
// ============================================================================
// �������ܣ�IO�������Լ�
// �����������
// �����������
// ����ֵ��  ��
// ============================================================================
void IES_IMInit_IOTabChk(void)
{
	register DWORD   dwLoop;
	register DWORD   dwErrFlg=0;
	register DWORD   dwErrIndex=0;
	const tagDiTab    *ptDiTab;
	const tagDpiTab   *ptDpiTab;
	const tagGoInTab  *ptGoInTab;
	const tagDoTab    *ptDoTab;
	const tagGoOutTab *ptGoOutTab;
	const tagLedTab   *ptLedTab;
	const tagBoardIoTab *ptBoardTab;
	ptDiTab       =&g_tDiTab[0];
	// DI�������Լ�
	if(g_NUM_DI!=CN_NUM_DI)
	{
		AppLog<<"DI���������ô���:g_NUM_DI="<<g_NUM_DI<<"CN_NUM_DI="<<CN_NUM_DI<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_DI;dwLoop++)
	{
		if(ptDiTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			AppLog<<"DI������˳�����ô���:Index="<<dwLoop<<"\n";
		}
		if((ptDiTab->byName[CN_LEN_NAME-1]!=0)||(ptDiTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			AppLog<<"DI������˳�����ô���:Index="<<dwLoop<<"\n";
		}
		//�̵�ַ��ϣ�������Լ�(��)
		ptDiTab++;
	}
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_DTYPE_DI,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_DTYPE_DI,TRUE);
	}
	// DI�忨�������Լ�
	dwErrFlg    =0;
	dwErrIndex  =0;
	ptBoardTab=&g_tBoardDITab[0];
	if(g_NUM_BOARD_DI!=CN_NUM_BOARD_DI)
	{
		AppLog<<"DI�忨���������ô���:g_NUM_BOARD_DI="<<g_NUM_BOARD_DI<<"CN_NUM_BOARD_DI="<<CN_NUM_BOARD_DI<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_BOARD_DI;dwLoop++)
	{
		if(ptBoardTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			
			AppLog<<"DI�忨���������ô���:Index="<<dwLoop<<"\n";
		}
		if((ptBoardTab->wIndexStr<EN_DI_STR)||(ptBoardTab->wIndexEnd>EN_DI_END)||(ptBoardTab->wIndexEnd<ptBoardTab->wIndexStr))
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			
			AppLog<<"DI�忨������Χ���ô���:wIndexStr="<<ptBoardTab->wIndexStr<<"wIndexEnd="<<ptBoardTab->wIndexEnd<<"\n";
		}
		if((ptBoardTab->wSrcIndexNum>=32)||(ptBoardTab->wSrcIndexNum!=ptBoardTab->wIndexEnd-ptBoardTab->wIndexStr))
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			AppLog<<"DI�忨������Χ���ô���:wIndexStr="<<ptBoardTab->wIndexStr<<"wIndexEnd="<<ptBoardTab->wIndexEnd<<"wSrcIndexNum="<<ptBoardTab->wSrcIndexNum<<"\n";

		}
		if(dwLoop<g_NUM_BOARD_DI-1)
		{
			if(ptBoardTab->wIndexEnd!=ptBoardTab[1].wIndexStr)
			{
				dwErrFlg|=CN_CONST_CHK_LMT;
				dwErrIndex=dwLoop;
				
				AppLog<<"DI�忨������Χ���ô���:wIndexEnd="<<ptBoardTab->wIndexEnd<<"wIndexStrNext="<<ptBoardTab[1].wIndexStr<<"\n";
			}
		}
		if((ptBoardTab->wPowBitNum>=ptBoardTab->wSrcIndexNum)&&(ptBoardTab->wPowBitNum!=CN_NULL_PINNO))
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			AppLog<<"DI�忨�������Դ�������ô���:wPowBitNum="<<ptBoardTab->wPowBitNum<<"wSrcIndexNum="<<ptBoardTab->wSrcIndexNum<<"\n";
		}
		if(((ptBoardTab->wParaIndex<EN_PARA_DI_STR)||(ptBoardTab->wParaIndex>=EN_PARA_DI_END))&&(ptBoardTab->wParaIndex!=CN_NULL_PINNO))
		{
			dwErrFlg|=CN_CONST_CHK_PARA1;
			dwErrIndex=dwLoop;
			AppLog<<"DI�忨������������ô���:Index="<<dwLoop<<"wParaIndex="<<ptBoardTab->wParaIndex<<"\n";
		}
		if((ptBoardTab->byName[CN_LEN_NAME-1]!=0)||(ptBoardTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			AppLog<<"DI�忨���������Ƴ���Խ��:Index="<<dwLoop<<"\n";
		}
		ptBoardTab++;
	}
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_CFG_DI_BOARD,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_CFG_DI_BOARD,TRUE);
	}

	// DPI�������Լ�
	dwErrFlg    =0;
	dwErrIndex  =0;
	ptDpiTab    =&g_tDpiTab[0];
	if(g_NUM_DPI!=CN_NUM_DPI)
	{
		AppLog<<"DPI���������ô���:g_NUM_DPI="<<g_NUM_DPI<<"CN_NUM_DPI="<<CN_NUM_DPI<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_DPI;dwLoop++)
	{
		if(ptDpiTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			AppLog<<"DPI������˳�����ô���:Index="<<dwLoop<<"\n";
		}
		if(((ptDpiTab->wParaIndex<EN_PARA_DI_STR)||(ptDpiTab->wParaIndex>=EN_PARA_DI_END))&&(ptDpiTab->wParaIndex!=CN_NULL_PINNO))
		{
			dwErrFlg|=CN_CONST_CHK_PARA1;
			dwErrIndex=dwLoop;
			AppLog<<"DPI������������ô���:Index="<<dwLoop<<"wParaIndex="<<ptDpiTab->wParaIndex<<"\n";
		}
		if((ptDpiTab->wSrcType==EN_DTYPE_DI)
		&&((ptDpiTab->wSrcOpn>=CN_NUM_DI)||(ptDpiTab->wSrcCls>=CN_NUM_DI)||(ptDpiTab->wSrcOpn==ptDpiTab->wSrcCls)))
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			AppLog<<"DPI������������ô���:Index="<<dwLoop<<"wSrcOpn="<<ptDpiTab->wSrcOpn<<"wSrcCls="<<ptDpiTab->wSrcCls<<"\n";
		}
		else if((ptDpiTab->wSrcType==EN_DTYPE_GOIN)
		&&((ptDpiTab->wSrcOpn>=CN_NUM_GOIN)||(ptDpiTab->wSrcCls>=CN_NUM_GOIN)||(ptDpiTab->wSrcOpn==ptDpiTab->wSrcCls)))
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			
			AppLog<<"DPI������������ô���:Index="<<dwLoop<<"GOIN wSrcOpn="<<ptDpiTab->wSrcOpn<<"wSrcCls="<<ptDpiTab->wSrcCls<<"\n";
		}
		else if((ptDpiTab->wSrcType!=EN_DTYPE_GOIN)&&(ptDpiTab->wSrcType!=EN_DTYPE_DI))
		{
			dwErrFlg|=CN_CONST_CHK_TYPE;
			dwErrIndex=dwLoop;
			
			AppLog<<"DPI������������ô���:Index="<<dwLoop<<"wSrcType="<<ptDpiTab->wSrcType<<"\n";
		}
		
		if((ptDpiTab->byName[CN_LEN_NAME-1]!=0)||(ptDpiTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			
			AppLog<<"DPI���������Ƴ���Խ��:Index="<<dwLoop<<"\n";
		}
		//�̵�ַ��ϣ�������Լ�(��)
		ptDpiTab++;
	}
	
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_DTYPE_DPI,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_DTYPE_DPI,TRUE);
	}
	// GOIN�������Լ�
	dwErrFlg    =0;
	dwErrIndex  =0;
	ptGoInTab   =&g_tGoInTab[0];
	if(g_NUM_GOIN!=CN_NUM_GOIN)
	{
		AppLog<<"GOIN���������ô���:g_NUM_GOIN="<<g_NUM_GOIN<<"CN_NUM_GOIN=\n"<<CN_NUM_GOIN<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	
	for(dwLoop=0;dwLoop<g_NUM_GOIN;dwLoop++)
	{
		if(ptGoInTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			AppLog<<"GOIN������˳�����ô���:Index="<<dwLoop<<"\n";
		}
		
		if((ptGoInTab->wChnType<EN_CTYPE_IO_STR)||(ptGoInTab->wChnType>=EN_CTYPE_IO_END))
		{
			dwErrFlg|=CN_CONST_CHK_TYPE;
			dwErrIndex=dwLoop;
			AppLog<<"GOIN�������ź��������ô���:Index="<<dwLoop<<"wChnType="<<ptGoInTab->wChnType<<"\n";
		}
		if(((ptGoInTab->wParaIndex<EN_PARA_DI_STR)||(ptGoInTab->wParaIndex>=EN_PARA_DI_END))&&(ptGoInTab->wParaIndex!=CN_NULL_PINNO))
		{
			dwErrFlg|=CN_CONST_CHK_PARA1;
			dwErrIndex=dwLoop;
			AppLog<<"GOIN������������ô���:Index="<<dwLoop<<"wParaIndex="<<ptGoInTab->wParaIndex<<"\n";
		}
		if((ptGoInTab->byName[CN_LEN_NAME-1]!=0)||(ptGoInTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			AppLog<<"GOIN���������Ƴ���Խ��:Index="<<dwLoop<<"\n";
		}
		//�̵�ַ��ϣ�������Լ�(��)
		ptGoInTab++;
	}
	
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_DTYPE_GOIN,dwErrFlg,dwErrIndex);
		
		G_Set_Const_Chk(EN_DTYPE_GOIN,TRUE);
	}
	// DO�������Լ�
	dwErrFlg    =0;
	dwErrIndex  =0;
	ptDoTab     =&g_tDoTab[0];
	if(g_NUM_DO!=CN_NUM_DO)
	{
	
		AppLog<<"DO���������ô���:g_NUM_DO="<<g_NUM_DO<<"CN_NUM_DO="<<CN_NUM_DO<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	
	for(dwLoop=0;dwLoop<g_NUM_DO;dwLoop++)
	{
		if(ptDoTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			
			AppLog<<"DO������˳�����ô���:Index="<<dwLoop<<"\n";
		}
		if(((ptDoTab->wParaIndex<EN_PARA_DI_STR)||(ptDoTab->wParaIndex>=EN_PARA_DI_END))&&(ptDoTab->wParaIndex!=CN_NULL_PINNO))
		{
			dwErrFlg|=CN_CONST_CHK_PARA1;
			dwErrIndex=dwLoop;
			
			AppLog<<"DO������������ô���:Index="<<dwLoop<<"wParaIndex="<<ptDoTab->wParaIndex<<"\n";
		}
		if((ptDoTab->wSrcType<EN_DTYPE_BOOL_STR)||(ptDoTab->wSrcType>=EN_DTYPE_BOOL_END))
		{
			dwErrFlg|=CN_CONST_CHK_TYPE;
			dwErrIndex=dwLoop;
			
			AppLog<<"DO����������Դ���ô���:Index="<<dwLoop<<"wSrcType="<<ptDoTab->wSrcType<<"wSrcIndex="<<ptDoTab->wSrcIndex<<"\n";
		}
		else if(ptDoTab->wSrcIndex>=g_tDTypeTab[ptDoTab->wSrcType].wDatNum)
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			
			AppLog<<"DO����������Դö�����ô���:Index="<<dwLoop<<"wSrcType="<<ptDoTab->wSrcType<<"wSrcIndex="<<ptDoTab->wSrcIndex<<"\n";
		}
		
		if((ptDoTab->byName[CN_LEN_NAME-1]!=0)||(ptDoTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			
			AppLog<<"DO���������Ƴ���Խ��:Index="<<dwLoop<<"\n";
		}
		//�̵�ַ��ϣ�������Լ�(��)
		ptDoTab++;
	}
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_DTYPE_DO,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_DTYPE_DO,TRUE);
	}
	// DO�忨�������Լ�
	dwErrFlg    =0;
	dwErrIndex  =0;
	ptBoardTab=&g_tBoardDOTab[0];
	if(g_NUM_BOARD_DO!=CN_NUM_BOARD_DO)
	{
		AppLog<<"DO�忨���������ô���:g_NUM_BOARD_DO="<<dwLoop<<"CN_NUM_BOARD_DO="<<CN_NUM_BOARD_DO<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_BOARD_DO;dwLoop++)
	{
		if(ptBoardTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			
			AppLog<<"DO�忨���������ô���:Index="<<dwLoop<<"\n";
		}
		if((ptBoardTab->wIndexStr<EN_DO_STR)||(ptBoardTab->wIndexEnd>EN_DO_END)||(ptBoardTab->wIndexEnd<ptBoardTab->wIndexStr))
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			AppLog<<"DO�忨������Χ���ô���:wIndexStr="<<ptBoardTab->wIndexStr<<"wIndexEnd="<<ptBoardTab->wIndexEnd<<"\n";
		}
		
		if(dwLoop<g_NUM_BOARD_DO-1)
		{
			if(ptBoardTab->wIndexEnd!=ptBoardTab[1].wIndexStr)
			{
				dwErrFlg|=CN_CONST_CHK_LMT;
				dwErrIndex=dwLoop;
				
				AppLog<<"D0�忨������Χ���ô���:wIndexEnd="<<ptBoardTab->wIndexEnd<<"wIndexStrNext="<<ptBoardTab[1].wIndexStr<<"\n";
			}
		}
		if((ptBoardTab->wSrcIndexNum>16)||(ptBoardTab->wSrcIndexNum!=ptBoardTab->wIndexEnd-ptBoardTab->wIndexStr))
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			
			AppLog<<"DO�忨������Χ���ô���:wIndexStr="<<ptBoardTab->wIndexStr<<"wIndexEnd="<<ptBoardTab->wIndexEnd<<"wSrcIndexNum="<<ptBoardTab->wSrcIndexNum<<"\n";
		}
		
		if((ptBoardTab->wPowBitNum!=CN_NULL_PINNO)||(ptBoardTab->wParaIndex!=CN_NULL_PINNO))
		{
			dwErrFlg|=CN_CONST_CHK_PARA1;
			dwErrIndex=dwLoop;
			
			AppLog<<"D0�忨�������Դ�������ô���:wPowBitNum="<<ptBoardTab->wPowBitNum<<"wSrcIndexNum="<<ptBoardTab->wSrcIndexNum<<"\n";
		}
		if((ptBoardTab->byName[CN_LEN_NAME-1]!=0)||(ptBoardTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			
			AppLog<<"DO�忨���������Ƴ���Խ��:Index="<<dwLoop<<"\n";
		}

		//�̵�ַ��ϣ�������Լ�(��)
		ptBoardTab++;
	}
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_CFG_DO_BOARD,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_CFG_DO_BOARD,TRUE);
	}
//  GOOUT�������Լ�
	dwErrFlg    =0;
	dwErrIndex  =0;
	ptGoOutTab  =&g_tGoOutTab[0];
	if(g_NUM_GOOUT!=CN_NUM_GOOUT)
	{
		AppLog<<"GOOUT���������ô���:g_NUM_GOOUT="<<g_NUM_GOOUT<<"CN_NUM_GOOUT="<<CN_NUM_GOOUT<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	
	for(dwLoop=0;dwLoop<g_NUM_GOOUT;dwLoop++)
	{
		if(ptGoOutTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			
			AppLog<<"GOOUT������˳�����ô���:Index="<<dwLoop<<"\n";
		}
		
		if((ptGoOutTab->wChnType<EN_CTYPE_IO_STR)||(ptGoOutTab->wChnType>=EN_CTYPE_IO_END))
		{
			dwErrFlg|=CN_CONST_CHK_TYPE;
			dwErrIndex=dwLoop;
			
			AppLog<<"GOOUT�������ź��������ô���:Index="<<dwLoop<<"wChnType="<<ptGoOutTab->wChnType<<"\n";
		}
		if(((ptGoOutTab->wParaIndex<EN_PARA_DI_STR)||(ptGoOutTab->wParaIndex>=EN_PARA_DI_END))&&(ptGoOutTab->wParaIndex!=CN_NULL_PINNO))
		{
			dwErrFlg|=CN_CONST_CHK_PARA1;
			dwErrIndex=dwLoop;
			AppLog<<"GOOUT������������ô���:Index="<<dwLoop<<"wParaIndex="<<ptGoOutTab->wParaIndex<<"\n";
		}
		if((ptGoOutTab->wSrcType<EN_DTYPE_BOOL_STR)||(ptGoOutTab->wSrcType>=EN_DTYPE_BOOL_END))
		{
			if(ptGoOutTab->wSrcType!=CN_NULL_PINNO)
			{
				dwErrFlg|=CN_CONST_CHK_LINK;
				dwErrIndex=dwLoop;
				AppLog<<"GOOUT����������Դ���ô���:Index="<<dwLoop<<"wSrcType="<<ptGoOutTab->wSrcType<<"wSrcIndex="<<ptGoOutTab->wSrcIndex<<"\n";
			}
		}
		else if(ptGoOutTab->wSrcIndex>=g_tDTypeTab[ptGoOutTab->wSrcType].wDatNum)
		{
			dwErrFlg|=CN_CONST_CHK_LINK;
			dwErrIndex=dwLoop;
			
			AppLog<<"GOOUT����������Դö�����ô���:Index="<<dwLoop<<"wSrcType="<<ptGoOutTab->wSrcType<<"wSrcIndex="<<ptGoOutTab->wSrcIndex<<"\n";
		}
		
		if((ptGoOutTab->byName[CN_LEN_NAME-1]!=0)||(ptGoOutTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			
			AppLog<<"GOOUT���������Ƴ���Խ��:Index="<<dwLoop<<"\n";
		}
		//�̵�ַ��ϣ�������Լ�(��)
		ptGoOutTab++;
	}
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_DTYPE_GOOUT,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_DTYPE_GOOUT,TRUE);
	}
//	LED�������Լ�
	dwErrFlg    =0;
	dwErrIndex  =0;
	ptLedTab   =&g_tLedTab[0];
	if(g_NUM_LED!=CN_NUM_LED)
	{
		AppLog<<"LED���������ô���:g_NUM_LED="<<g_NUM_LED<<"CN_NUM_LED="<<CN_NUM_LED<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	
	for(dwLoop=0;dwLoop<g_NUM_LED;dwLoop++)
	{
		if(ptLedTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			
			AppLog<<"LED������˳�����ô���:Index="<<dwLoop<<"\n";
		}
		if(((ptLedTab->wParaIndex<EN_PARA_DI_STR)||(ptLedTab->wParaIndex>=EN_PARA_DI_END))&&(ptLedTab->wParaIndex!=CN_NULL_PINNO))
		{
			dwErrFlg|=CN_CONST_CHK_PARA1;
			dwErrIndex=dwLoop;
			
			AppLog<<"LED������������ô���:Index="<<dwLoop<<"wParaIndex="<<ptLedTab->wParaIndex<<"\n";
		}
		if((ptLedTab->wSrcType<EN_DTYPE_BOOL_STR)||(ptLedTab->wSrcType>=EN_DTYPE_BOOL_END))
		{
			dwErrFlg|=CN_CONST_CHK_LINK;
			dwErrIndex=dwLoop;
			
			AppLog<<"LED����������Դ���ô���:Index="<<dwLoop<<"wSrcType="<<ptLedTab->wSrcType<<"wSrcIndex="<<ptLedTab->wSrcIndex<<"\n";
		}
		else if(ptLedTab->wSrcIndex>=g_tDTypeTab[ptLedTab->wSrcType].wDatNum)
		{
			dwErrFlg|=CN_CONST_CHK_LINK;
			dwErrIndex=dwLoop;
			
			AppLog<<"LED����������Դö�����ô���:Index="<<dwLoop<<"wSrcType="<<ptLedTab->wSrcType<<"wSrcIndex="<<ptLedTab->wSrcIndex<<"\n";
		}
		
		if((ptLedTab->byName[CN_LEN_NAME-1]!=0)||(ptLedTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			
			AppLog<<"LED���������Ƴ���Խ��:Index="<<dwLoop<<"\n";
		}
		//�̵�ַ��ϣ�������Լ�(��)
		ptLedTab++;
	}
	
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_DTYPE_LED,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_DTYPE_LED,TRUE);
	}

}
// ============================================================================
// �������ܣ������������Լ�
// �����������
// �����������
// ����ֵ����
// ============================================================================
void IES_IMInit_ParaTabChk(void)
{
	register DWORD   dwLoop;
	register DWORD   dwErrFlg=0;
	register DWORD   dwErrIndex=0;
	const tagParaTab *ptParaTab;
	const tagBoardParaTab  *ptBoardParaTab;
	// ģ�����������Լ�
	ptParaTab=&g_tParaTab[0];
	if(g_NUM_PARA!=CN_NUM_PARA)
	{
		AppLog<<"�������������ô���:g_NUM_PARA="<<g_NUM_PARA<<"CN_NUM_PARA=" << CN_NUM_PARA <<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_PARA;dwLoop++)
	{
		if(ptParaTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			
			AppLog<<"����������˳�����ô���:Index="<<dwLoop<<"\n";
		}
		if(((ptParaTab->wType>=EN_CTYPE_PARA_END)||(ptParaTab->wType<EN_CTYPE_PARA_STR))
			&&((ptParaTab->wType>=EN_CENUM_END)||(ptParaTab->wType<EN_CENUM_STR)))
		{
			dwErrFlg|=CN_CONST_CHK_TYPE;
			dwErrIndex=dwLoop;
			
			AppLog<<"����������ͨ���������ô���:Index="<<dwLoop<<"wType=" << ptParaTab->wType <<"\n";
		}
			
		if((ptParaTab->wType==EN_CTYPE_PARA_H)||(ptParaTab->wType==EN_CTYPE_PARA_MAT))
		{
			if(((DWORD)ptParaTab->iValMax<=(DWORD)ptParaTab->iValMin)||((DWORD)ptParaTab->iValDft<(DWORD)ptParaTab->iValMin)||((DWORD)ptParaTab->iValDft>(DWORD)ptParaTab->iValMax))
			{
				dwErrFlg|=CN_CONST_CHK_LMT;
				dwErrIndex=dwLoop;
				
				AppLog<<"����������Χ���ô���:Index="<<dwLoop<<"dwValMax=" << ptParaTab->iValMax<<"dwValMin="<<ptParaTab->iValMin<<"dwValDft="<<ptParaTab->iValDft<<"\n";
			}
		}
		else
		{
			if((ptParaTab->iValMax<=ptParaTab->iValMin)||(ptParaTab->iValDft<ptParaTab->iValMin)||(ptParaTab->iValDft>ptParaTab->iValMax))
			{
				dwErrFlg|=CN_CONST_CHK_LMT;
				dwErrIndex=dwLoop;
				
				AppLog<<"����������Χ���ô���:Index="<<dwLoop<<"dwValMax=" << ptParaTab->iValMax<<"dwValMin="<<ptParaTab->iValMin<<"dwValDft="<<ptParaTab->iValDft<<"\n";
			}
		}
			
		if((ptParaTab->byName[CN_LEN_NAME-1]!=0)||(ptParaTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			
			AppLog<<"�������������Ƴ���Խ��:Index="<<dwLoop<<"\n";
		}
		//�̵�ַ��ϣ�������Լ�(��)
		ptParaTab++;
	}
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_DTYPE_PARA,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_DTYPE_PARA,TRUE);
	}
	
	// �������ೣ�����Լ�
	dwErrFlg    =0;
	dwErrIndex  =0;
	ptBoardParaTab=&g_tBoardParaTab[0];
	if(g_NUM_BOARD_PARA!=CN_NUM_BOARD_PARA)
	{
		AppLog<<"�������ೣ�������ô���:g_NUM_BOARD_PARA="<<g_NUM_BOARD_PARA<<"CN_NUM_BOARD_PARA=" << CN_NUM_BOARD_PARA<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_BOARD_PARA;dwLoop++)
	{
		if(ptBoardParaTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			
			AppLog<<"�������ೣ�������ô���:Index="<<dwLoop<<"\n";
		}
		if((ptBoardParaTab->wIndexEnd>EN_PARA_END)||(ptBoardParaTab->wIndexEnd<ptBoardParaTab->wIndexStr)||((ptBoardParaTab->wIndexEnd-ptBoardParaTab->wIndexStr)!=ptBoardParaTab->wIndexNum))
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;

			AppLog<<"�������ೣ����Χ���ô���:Index="<<dwLoop<<"wIndexStr=" << ptBoardParaTab->wIndexStr<<"wIndexEnd=" << ptBoardParaTab->wIndexEnd<<"wIndexNum="<<ptBoardParaTab->wIndexNum<<"\n";
		}
		if(dwLoop<g_NUM_BOARD_PARA-1)
		{
			if(ptBoardParaTab->wIndexEnd!=ptBoardParaTab[1].wIndexStr)
			{
				dwErrFlg|=CN_CONST_CHK_LMT;
				dwErrIndex=dwLoop;
				
				AppLog<<"�������ೣ���������ķ�Χ���ô���:Index="<<dwLoop<<"wIndexEnd=" << ptBoardParaTab->wIndexEnd<<"wIndexStrNext=" <<ptBoardParaTab[1].wIndexStr<<"\n";
			}
		}
		if((ptBoardParaTab->wGroupNum==0)||(ptBoardParaTab->wGroupNum>=30))
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			
			AppLog<<"�������ೣ�����������ô���:Index="<<dwLoop<<"wGroupNum=" << ptBoardParaTab->wGroupNum<<"\n";
		}
		
		if((ptBoardParaTab->byName[CN_LEN_NAME-1]!=0)||(ptBoardParaTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			
			AppLog<<"�������ೣ�������Ƴ���Խ��:Index="<<dwLoop<<"\n";
		}
		ptBoardParaTab++;
	}
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_CFG_PARA_BOARD,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_CFG_PARA_BOARD,TRUE);
	}
}
// ============================================================================
// �������ܣ�ֱ���������Լ�
// �����������
// �����������
// ����ֵ����
// ============================================================================
void IES_IMInit_DCTabChk(void)
{
	register DWORD   dwLoop;
	register DWORD   dwErrFlg=0;
	register DWORD   dwErrIndex=0;
	const tagDCTab   *ptDCTab;
	const tagBoardDCTab  *ptBoardDCTab;
	// ģ�����������Լ�
	ptDCTab     =&g_tDCTab[0];
	if(g_NUM_DC!=CN_NUM_DC)
	{
	
		AppLog<<"ֱ�����������ô���:g_NUM_DC="<<g_NUM_DC<<"CN_NUM_DC=" << CN_NUM_DC<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_DC;dwLoop++)
	{
		if(ptDCTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			
			AppLog<<"ֱ��������˳�����ô���:Index="<<dwLoop<<"\n";
		}
		if((ptDCTab->wType>=EN_CTYPE_DC_END)||(ptDCTab->wType<EN_CTYPE_DC_STR))
		{
			dwErrFlg|=CN_CONST_CHK_TYPE;
			dwErrIndex=dwLoop;
			
			AppLog<<"ֱ��������ͨ���������ô���:Index="<<dwLoop<<"wType="<<ptDCTab->wType<<"\n";
		}
		
		if(((ptDCTab->wParaIndex1<EN_PARA_DC_STR)||(ptDCTab->wParaIndex1>=EN_PARA_DC_END))&&(ptDCTab->wParaIndex1!=CN_NULL_PINNO))
		{
			dwErrFlg|=CN_CONST_CHK_PARA1;
			dwErrIndex=dwLoop;
			
			AppLog<<"ֱ��������������ô���:Index="<<dwLoop<<"wParaIndex1="<<ptDCTab->wParaIndex1<<"\n";
		}
		if(((ptDCTab->wParaIndex2<EN_PARA_DC_STR)||(ptDCTab->wParaIndex2>=EN_PARA_DC_END))&&(ptDCTab->wParaIndex2!=CN_NULL_PINNO))
		{
			dwErrFlg|=CN_CONST_CHK_PARA2;
			dwErrIndex=dwLoop;
			
			AppLog<<"ֱ��������������ô���:Index="<<dwLoop<<"wParaIndex2="<<ptDCTab->wParaIndex2<<"\n";
		}
		if((ptDCTab->byName[CN_LEN_NAME-1]!=0)||(ptDCTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			
			AppLog<<"ֱ�����������Ƴ���Խ��:Index="<<dwLoop<<"\n";
		}
		//�̵�ַ��ϣ�������Լ�(��)
		ptDCTab++;
	}
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_DTYPE_DC,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_DTYPE_DC,TRUE);
	}

	// 
	dwErrFlg    =0;
	dwErrIndex  =0;
	ptBoardDCTab=&g_tBoardDCTab[0];
	if(g_NUM_BOARD_DC!=CN_NUM_BOARD_DC)
	{
	
		AppLog<<"ֱ���忨���ô���:g_NUM_DC="<<g_NUM_BOARD_DC<<"g_NUM_DC="<<CN_NUM_BOARD_DC<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_BOARD_DC;dwLoop++)
	{
		if(ptBoardDCTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			
			AppLog<<"ֱ���忨���ô���:dwLoop="<<dwLoop<<"ptBoardDCTab->wIndex="<<ptBoardDCTab->wIndex<<"\n";
		}
		if((ptBoardDCTab->wIndexStr>CN_NUM_DC)||(ptBoardDCTab->wIndexEnd>CN_NUM_DC)
			||(ptBoardDCTab->wIndexEnd<ptBoardDCTab->wIndexStr)||((ptBoardDCTab->wIndexEnd-ptBoardDCTab->wIndexStr)!=ptBoardDCTab->wSrcIndexNum))
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			AppLog<<"ֱ���忨��Ϣ���ô���:dwLoop="<<dwLoop<<"wIndexStr="<<ptBoardDCTab->wIndexStr<<"wIndexEnd="<<ptBoardDCTab->wIndexEnd<<"wSrcIndexNum="<<ptBoardDCTab->wSrcIndexNum<<"\n";
		}
		if(dwLoop!=(g_NUM_BOARD_DC-1))
		{
			if(ptBoardDCTab->wIndexEnd!=ptBoardDCTab[1].wIndexStr)
			{
				dwErrFlg|=CN_CONST_CHK_LMT;
				dwErrIndex=dwLoop;
				AppLog<<"ֱ���忨��Ϣ���ô���:dwLoop="<<dwLoop<<"wIndexEnd="<<ptBoardDCTab->wIndexEnd<<"wIndexStrNext="<<ptBoardDCTab[1].wIndexStr<<"\n";
			}
		}
		if((ptBoardDCTab->byName[CN_LEN_NAME-1]!=0)||(ptBoardDCTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			AppLog<<"ֱ���忨���������Ƴ���Խ��:dwLoop="<<dwLoop<<"\n";
		}
		ptBoardDCTab++;
	}
	
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_CFG_DC_BOARD,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_CFG_DC_BOARD,TRUE);
	}
}
// ============================================================================
// �������ܣ��м��־�������Լ�
// �����������
// �����������
// ����ֵ����
// ============================================================================
void IES_IMInit_FlagTabChk(void)
{
	register DWORD     dwLoop,j;
	register DWORD     dwErrFlg=0,dwIndexMax=0;
	register DWORD     dwErrIndex=0;
	const tagFlagTab   *ptFlagTab;
	const tagInterTab  *ptInterTab;
	// ��־�������Լ�
	ptFlagTab=&g_tFlagTab[0];
	if(g_NUM_FLAG!=CN_NUM_FLAG)
	{
		AppLog<<"�м��־���������ô���:g_NUM_FLAG="<<g_NUM_FLAG<<"CN_NUM_FLAG=" << CN_NUM_FLAG<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_FLAG;dwLoop++)
	{
		if(ptFlagTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			
			AppLog<<"�м��־������˳�����ô���:Index="<<dwLoop<<"\n";
		}
		
		if(((ptFlagTab->wSrcType<EN_DTYPE_BOOL_STR)||(ptFlagTab->wSrcType>=EN_DTYPE_BOOL_END))&&(ptFlagTab->wSrcType!=CN_NULL_PINNO))
		{
			dwErrFlg|=CN_CONST_CHK_LINK;
			dwErrIndex=dwLoop;
			
			AppLog<<"�м��־������ͨ��Դ���ô���:Index="<<dwLoop<<"wSrcType=" << ptFlagTab->wSrcType<<"\n";
		}
		else if((ptFlagTab->wSrcType==CN_NULL_PINNO)&&((ptFlagTab->wSrcIndex[0]!=CN_NULL_PINNO)||(ptFlagTab->wCalCfg!=CN_FLAG_NULL)))
		{
			dwErrFlg|=CN_CONST_CHK_LINK;
			dwErrIndex=dwLoop;
			
			AppLog<<"�м��־������ͨ��Դ���ô���:Index="<<dwLoop<<"ptFlagTab->wSrcIndex[0]=" << ptFlagTab->wSrcIndex[0]<<"\n";
		}
		else if(ptFlagTab->wSrcType!=CN_NULL_PINNO)
		{
			dwIndexMax=g_tDTypeTab[ptFlagTab->wSrcType].wDatNum;
			for(j=0;j<CN_FLAG_SNUM;j++)
			{
				if(ptFlagTab->wSrcIndex[j]==CN_NULL_PINNO)
				{
					break;
				}
				if(ptFlagTab->wSrcIndex[j]>dwIndexMax)
				{
					dwErrFlg|=CN_CONST_CHK_LINK;
					dwErrIndex=dwLoop;
					
					AppLog<<"�м��־������ͨ���ϳ����ô���:Index="<<dwLoop<<"j=" << j<<"\n";
				}
			}
			if((j>=CN_FLAG_SNUM)||(j==0))
			{
				dwErrFlg|=CN_CONST_CHK_LINK;
				dwErrIndex=dwLoop;
				
				AppLog<<"�м��־������ͨ���ϳ����ô���:Index="<<dwLoop<<"wSrcType=" << ptFlagTab->wSrcType<<"\n";
			}
		}
		if(((ptFlagTab->wPara<EN_PARA_FUN_STR)||(ptFlagTab->wPara>=EN_PARA_FUN_END))&&(ptFlagTab->wPara!=CN_NULL_PINNO))
		{
			dwErrFlg|=CN_CONST_CHK_PARA1;
			dwErrIndex=dwLoop;
			
			AppLog<<"�м��־������������ô���:Index="<<dwLoop<<"wPara=" << ptFlagTab->wPara<<"\n";
		}
		
		if((ptFlagTab->byName[CN_LEN_NAME-1]!=0)||(ptFlagTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			
			AppLog<<"�м��־���������Ƴ���Խ��:Index="<<dwLoop<<"\n";
		}
		//�̵�ַ��ϣ�������Լ�(��)
		ptFlagTab++;
	}
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_DTYPE_FLAG,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_DTYPE_FLAG,TRUE);
	}
	// �ڲ���־�������Լ�
	dwErrFlg    =0;
	dwErrIndex  =0;
	ptInterTab=&g_tInterTab[0];
	if(g_NUM_INTER!=CN_NUM_INTER)
	{
		AppLog<<"�м��־���������ô���:g_NUM_INTER="<<g_NUM_INTER<<"CN_NUM_INTER=" << CN_NUM_INTER<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_INTER;dwLoop++)
	{
		if(ptInterTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			AppLog<<"�ڲ���־������˳�����ô���:Index="<<dwLoop<<"\n";
		}
		
		if(((ptInterTab->wType>=EN_CTYPE_PARA_END)||(ptInterTab->wType<EN_CTYPE_PARA_STR))
			&&((ptInterTab->wType>=EN_CENUM_END)||(ptInterTab->wType<EN_CENUM_STR)))
		{
			dwErrFlg|=CN_CONST_CHK_TYPE;
			dwErrIndex=dwLoop;
			AppLog<<"�ڲ���־������ͨ���������ô���:Index="<<dwLoop<<"wType=" << ptInterTab->wType<<"\n";
		}
		if((ptInterTab->byName[CN_LEN_NAME-1]!=0)||(ptInterTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			
			AppLog<<"�ڲ���־���������Ƴ���Խ��:Index="<<dwLoop<<"\n";
		}
		//�̵�ַ��ϣ�������Լ�(��)
		ptInterTab++;
	}
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_DTYPE_INTER,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_DTYPE_INTER,TRUE);
	}
}
// ============================================================================
// �������ܣ���������Լ�
// �����������
// �����������
// ����ֵ����
// ============================================================================
void IES_IMInit_RecTabChk(void)
{
	register DWORD   dwLoop,j;
	register DWORD   dwErrFlg=0;
	register DWORD   dwErrIndex=0,dwIndexMax=0;
	const tagActTab *ptActTab;
	const tagAlmTab *ptAlmTab;
	const tagChkTab *ptChkTab;
	const tagRunTab *ptRunTab;	
	const tagOptTab *ptOptTab;

	// GOOSE��������Լ�
	ptActTab=&g_tActTab[0];
	if(g_NUM_ACT!=CN_NUM_ACT)
	{
	
		AppLog<<"GOOSE����������ô���:g_NUM_ACT="<<g_NUM_ACT<<"CN_NUM_ACT=" << CN_NUM_ACT<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_ACT;dwLoop++)
	{
		if(ptActTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			
			AppLog<<"GOOSE�������˳�����ô���:Index="<<dwLoop<<"\n";
		}
		
		if(ptActTab->wSrcType==EN_DTYPE_GOIN)
		{
			dwIndexMax=CN_NUM_GOIN;
		}
		else if(ptActTab->wSrcType==EN_DTYPE_DI)
		{
			dwIndexMax=CN_NUM_DI;
		}
		else if(ptActTab->wSrcType==CN_NULL_PINNO)
		{
			dwIndexMax=0;
		}
		else
		{
			dwErrFlg|=CN_CONST_CHK_LINK;
			dwErrIndex=dwLoop;
			dwIndexMax=CN_NULL_PINNO;
			
			AppLog<<"GOOSE�������ͨ��Դ���ô���:Index="<<dwLoop<<"wSrcType=" << ptActTab->wSrcType<<"\n";
		}
		
		for(j=0;j<CN_ACT_SNUM;j++)
		{
			if(ptActTab->wSrcIndex[j]==CN_NULL_PINNO)
			{
				break;
			}
			if(ptActTab->wSrcIndex[j]>dwIndexMax)
			{
				dwErrFlg|=CN_CONST_CHK_LINK;
				dwErrIndex=dwLoop;
				
				AppLog<<"GOOSE�������ͨ���ϳ����ô���:Index="<<dwLoop<<"j=" << j<<"\n";
			}
		}
		if(j>=CN_ACT_SNUM)
		{
			dwErrFlg|=CN_CONST_CHK_LINK;
			dwErrIndex=dwLoop;
			
			AppLog<<"GOOSE�������ͨ���ϳ����ô���:Index="<<dwLoop<<"wSrcType=" << ptActTab->wSrcType<<"\n";
		}
		if(((ptActTab->wDoIndex>=CN_NUM_DO)&&(ptActTab->wDoIndex!=CN_NULL_PINNO))
		||(((ptActTab->wDoRetIndex>=CN_NUM_DI)||(ptActTab->wDoRetIndex<EN_DI_DI_END))&&(ptActTab->wDoIndex!=CN_NULL_PINNO)))
		{
			dwErrFlg|=CN_CONST_CHK_LINK;
			dwErrIndex=dwLoop;
			
			AppLog<<"GOOSE����������ӳ�����ô���:Index="<<dwLoop<<"\n";
		}

		if(((ptActTab->wValType1>=EN_MEA_END)&&(ptActTab->wValType1!=CN_NULL_PINNO))||
			((ptActTab->wValType2>=EN_MEA_END)&&(ptActTab->wValType2!=CN_NULL_PINNO))||
			((ptActTab->wValType3>=EN_MEA_END)&&(ptActTab->wValType3!=CN_NULL_PINNO))||
			((ptActTab->wValType4>=EN_MEA_END)&&(ptActTab->wValType4!=CN_NULL_PINNO))||
			((ptActTab->wValType5>=EN_MEA_END)&&(ptActTab->wValType5!=CN_NULL_PINNO))||
			((ptActTab->wValType6>=EN_MEA_END)&&(ptActTab->wValType6!=CN_NULL_PINNO))
			)
		{
			dwErrFlg|=CN_CONST_CHK_SUB;
			dwErrIndex=dwLoop;
			
			AppLog<<"GOOSE���������������ô���:Index="<<dwLoop<<"wValType1=" << ptActTab->wValType1<<"wValType2=" << ptActTab->wValType2<<"wValType3=" << ptActTab->wValType3   \
				<<"wValType4=" << ptActTab->wValType4<<"wValType5=" << ptActTab->wValType5<<"wValType6="<< ptActTab->wValType6<<"\n";
		}
		
		if((ptActTab->byName[CN_LEN_NAME-1]!=0)||(ptActTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			
			AppLog<<"GOOSE����������Ƴ���Խ��:Index="<<dwLoop<<"\n";
		}
		//�̵�ַ��ϣ�������Լ�(��)
		ptActTab++;
	}
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_DTYPE_ACT,dwErrFlg,dwErrIndex);
		
		G_Set_Const_Chk(EN_DTYPE_ACT,TRUE);
	}
	// �澯�������Լ�
	ptAlmTab=&g_tAlmTab[0];
	dwErrFlg   =0;
	dwErrIndex =0;
	if(g_NUM_ALM!=CN_NUM_ALM)
	{
		AppLog<<"�澯���������ô���:g_NUM_ALM="<<g_NUM_ALM<<"CN_NUM_ALM=" << CN_NUM_ALM<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_ALM;dwLoop++)
	{
		if(ptAlmTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			
			AppLog<<"�澯������˳�����ô���:Index="<<dwLoop<<"\n";
		}
		
		if(((ptAlmTab->wParaEna<EN_PARA_FUN_STR)||(ptAlmTab->wParaEna>=EN_PARA_FUN_END))&&(ptAlmTab->wParaEna!=CN_NULL_PINNO))
		{
			dwErrFlg|=CN_CONST_CHK_PARA1;
			dwErrIndex=dwLoop;
			
			AppLog<<"�澯��������������ô���:Index="<<dwLoop<<"wParaEna="<<ptAlmTab->wParaEna<<"\n";
		}
		if(((ptAlmTab->wParaTime<EN_PARA_FUN_STR)||(ptAlmTab->wParaTime>=EN_PARA_FUN_END))&&(ptAlmTab->wParaTime!=CN_NULL_PINNO))
		{
			dwErrFlg|=CN_CONST_CHK_PARA2;
			dwErrIndex=dwLoop;
			
			AppLog<<"�澯������ʱ��������ô���:Index="<<dwLoop<<"wParaTime="<<ptAlmTab->wParaTime<<"\n";
		}
		if(((ptAlmTab->wValType1>=EN_MEA_END)&&(ptAlmTab->wValType1!=CN_NULL_PINNO))||
			((ptAlmTab->wValType2>=EN_MEA_END)&&(ptAlmTab->wValType2!=CN_NULL_PINNO))||
			((ptAlmTab->wValType3>=EN_MEA_END)&&(ptAlmTab->wValType3!=CN_NULL_PINNO)))
		{
			dwErrFlg|=CN_CONST_CHK_SUB;
			dwErrIndex=dwLoop;
			
			AppLog<<"�澯��������������ô���:Index="<<dwLoop<<"wValType1="<<ptAlmTab->wValType1<<"wValType2="<<ptAlmTab->wValType2<<"wValType3="<<ptAlmTab->wValType3<<"\n";
		}
			
		if((ptAlmTab->byName[CN_LEN_NAME-1]!=0)||(ptAlmTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			
			AppLog<<"�澯���������Ƴ���Խ��:Index="<<dwLoop<<"\n";
		}
		//�̵�ַ��ϣ�������Լ�(��)
		ptAlmTab++;
	}
	if((CN_NUM_ALM_GOCB_DATA!=CN_NUM_GOCB_SUB)||(CN_NUM_ALM_GOCB_TEST!=CN_NUM_GOCB_SUB))
	{
		dwErrFlg|=CN_CONST_CHK_LMT;
		dwErrIndex=dwLoop;
		
		AppLog<<"�澯������˳�����ô���:Index="<<dwLoop<<"\n";
	}
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_DTYPE_ALM,dwErrFlg,dwErrIndex);
		
		G_Set_Const_Chk(EN_DTYPE_ALM,TRUE);
	}
	// �澯�������Լ�
	ptChkTab=&g_tChkTab[0];
	dwErrFlg    =0;
	dwErrIndex  =0;
	if(g_NUM_CHK!=CN_NUM_CHK)
	{
		AppLog<<"�Լ쳣�������ô���:g_NUM_CHK="<<g_NUM_CHK<<"CN_NUM_CHK="<<CN_NUM_CHK<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_CHK;dwLoop++)
	{
		if(ptChkTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			
			AppLog<<"�Լ쳣����˳�����ô���:Index="<<dwLoop<<"\n";
		}
		#if 0
		if(((ptChkTab->wParaEna<EN_PARA_FUN_STR)||(ptChkTab->wParaEna>=EN_PARA_FUN_END))&&(ptChkTab->wParaEna!=CN_NULL_PINNO))
		{
			dwErrFlg|=CN_CONST_CHK_PARA1;
			dwErrIndex=dwLoop;
			
			AppLog<<"�Լ쳣����˳�����ô���:Index="<<dwLoop<<"wParaEna="<<ptChkTab->wParaEna<<"\n";
		}
		if(((ptChkTab->wParaTime<EN_PARA_FUN_STR)||(ptChkTab->wParaTime>=EN_PARA_FUN_END))&&(ptChkTab->wParaTime!=CN_NULL_PINNO))
		{
			dwErrFlg|=CN_CONST_CHK_PARA2;
			dwErrIndex=dwLoop;
			
			AppLog<<"�Լ쳣����˳�����ô���:Index="<<dwLoop<<"wParaEna="<<ptChkTab->wParaTime<<"\n";
		}
		#endif
		if(((ptChkTab->wValType1>=EN_MEA_END)&&(ptChkTab->wValType1!=CN_NULL_PINNO))||
			((ptChkTab->wValType2>=EN_MEA_END)&&(ptChkTab->wValType2!=CN_NULL_PINNO))||
			((ptChkTab->wValType3>=EN_MEA_END)&&(ptChkTab->wValType3!=CN_NULL_PINNO)))
		{
			dwErrFlg|=CN_CONST_CHK_SUB;
			dwErrIndex=dwLoop;
			
			AppLog<<"�Լ쳣������������ô���:Index="<<dwLoop<<"wValType1="<<ptChkTab->wValType1<<"wValType2="<<ptChkTab->wValType2<<"wValType3="<<ptChkTab->wValType3<<"\n";
		}
			
		if((ptChkTab->byName[CN_LEN_NAME-1]!=0)||(ptChkTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			AppLog<<"�Լ쳣�������Ƴ���Խ��:Index="<<dwLoop<<"\n";
		}
		//�̵�ַ��ϣ�������Լ�(��)
		ptChkTab++;
	}
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_DTYPE_CHK,dwErrFlg,dwErrIndex);
		
		G_Set_Const_Chk(EN_DTYPE_CHK,TRUE);
	}
	// ���г������Լ�
	ptRunTab=&g_tRunTab[0];
	dwErrFlg    =0;
	dwErrIndex  =0;
	if(g_NUM_RUN!=CN_NUM_RUN)
	{
	
		AppLog<<"���г��������ô���:g_NUM_RUN="<<g_NUM_RUN<<"CN_NUM_RUN="<<CN_NUM_RUN<<"\n";
		//printf("�������������ô���:g_NUM_OPT=%d CN_NUM_OPT=%d\n", g_NUM_OPT, CN_NUM_OPT);
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_RUN;dwLoop++)
	{
		if(ptRunTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			
			AppLog<<"���г�����˳�����ô���:Index="<<dwLoop<<"\n";
			//printf("���г�����˳�����ô���:Index=%d\n",dwLoop);
		}
		if((ptRunTab->byName[CN_LEN_NAME-1]!=0)||(ptRunTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			
			AppLog<<"�������������Ƴ���Խ��:Index="<<dwLoop<<"\n";
			//printf("�������������Ƴ���Խ��:Index=%d\n",dwLoop);
		}
		//�̵�ַ��ϣ�������Լ�(��)
		ptRunTab++;
	}
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_CFG_RUN,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_CFG_RUN,TRUE);
	}
		// �����������Լ�
	ptOptTab=&g_tOptTab[0];
	dwErrFlg    =0;
	dwErrIndex  =0;
	if(g_NUM_OPT!=CN_NUM_OPT)
	{
	
		AppLog<<"�������������ô���:g_NUM_OPT="<<g_NUM_OPT<<"CN_NUM_OPT="<<CN_NUM_OPT<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_OPT;dwLoop++)
	{
		if(ptOptTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			
			AppLog<<"����������˳�����ô���:Index="<<dwLoop<<"\n";
		}
		if(((ptOptTab->wValType1>=EN_MEA_END)&&(ptOptTab->wValType1!=CN_NULL_PINNO))||
			((ptOptTab->wValType2>=EN_MEA_END)&&(ptOptTab->wValType2!=CN_NULL_PINNO))||
			((ptOptTab->wValType3>=EN_MEA_END)&&(ptOptTab->wValType3!=CN_NULL_PINNO)))
		{
			dwErrFlg|=CN_CONST_CHK_SUB;
			dwErrIndex=dwLoop;
			
			AppLog<<"������������������ô���:Index="<<dwLoop<<"wValType1="<<ptChkTab->wValType1<<"wValType2="<<ptChkTab->wValType2<<"wValType3="<<ptChkTab->wValType3<<"\n";
		}
		if((ptOptTab->byName[CN_LEN_NAME-1]!=0)||(ptOptTab->byPinName[CN_LEN_NAME-1]!=0))
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			
			AppLog<<"�������������Ƴ���Խ��:Index="<<dwLoop<<"\n";
		}
			
		//�̵�ַ��ϣ�������Լ�(��)
		ptOptTab++;
	}
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,EN_CFG_OPT,dwErrFlg,dwErrIndex);
		G_Set_Const_Chk(EN_CFG_OPT,TRUE);
	}
}
// ============================================================================
// �������ܣ��������Լ�
// �����������
// �����������
// ����ֵ����
// ============================================================================
void IES_IMInit_ConstChk(void)
{
	IES_IMInit_PubTabChk();
	IES_IMInit_SamTabChk();
	IES_IMInit_IOTabChk();
	IES_IMInit_ParaTabChk();
	IES_IMInit_DCTabChk();
	IES_IMInit_FlagTabChk();
	IES_IMInit_RecTabChk();
}
// ============================================================================
// �������ܣ�ʵʱ���ݳ�ʼ��
// �����������
// �����������
// ����ֵ��  ��
// ============================================================================
void IES_IMInit_RealData(void)
{
// ʵʱ���ݳ�ʼ��
	IES_memset(&g_tDevInfor, 0x0,sizeof(g_tDevInfor));
	IES_memset(&g_tagAna,    0x0,sizeof(g_tagAna));
	IES_memset(&g_tagIO,     0x0,sizeof(g_tagIO));
	IES_memset(&g_tagDC,     0x0,sizeof(g_tagDC));
	IES_memset(&g_tagPara,   0x0,sizeof(g_tagPara));
	IES_memset(&g_tagRamScan,0x0,sizeof(g_tagRamScan));
	IES_memset(&g_tagPub,    0x0,sizeof(g_tagPub));
	IES_memset(g_bFlag,      0x0,sizeof(g_bFlag));
	IES_memset(g_iInter,     0x0,sizeof(g_iInter));
	IES_memset(g_tActQueue,  0x0,sizeof(g_tActQueue));
	IES_memset(&g_tActState, 0x0,sizeof(g_tActState));
	IES_memset(&g_tAlmState, 0x0,sizeof(g_tAlmState));
	IES_memset(&g_tChkState, 0x0,sizeof(g_tChkState));
// ɨ����ʼ��
	IES_RamScanAdd(&g_tDevInfor.byRamScan1);
	IES_RamScanAdd(&g_tDevInfor.byRamScan2);
	IES_RamScanAdd(&g_tDevInfor.byRamScan3);
	
	IES_RamScanAdd(&g_tagAna.byRamScan1);
	IES_RamScanAdd(&g_tagAna.byRamScan2);
	IES_RamScanAdd(&g_tagAna.byRamScan3);
	IES_RamScanAdd(&g_tagAna.byRamScan4);
	IES_RamScanAdd(&g_tagAna.byRamScan5);
	IES_RamScanAdd(&g_tagAna.byRamScan6);
	IES_RamScanAdd(&g_tagAna.byRamScan7);
#if(CN_SV_IN_ENA)
	IES_RamScanAdd(&g_tagAna.byRamScan71);
	IES_RamScanAdd(&g_tagAna.byRamScan72);
	IES_RamScanAdd(&g_tagAna.byRamScan73);
	IES_RamScanAdd(&g_tagAna.byRamScan74);
	IES_RamScanAdd(&g_tagAna.byRamScan75);
#endif
	IES_RamScanAdd(&g_tagAna.byRamScan8);
	IES_RamScanAdd(&g_tagAna.byRamScan9);
	IES_RamScanAdd(&g_tagAna.byRamScan10);
	IES_RamScanAdd(&g_tagAna.byRamScan11);
	IES_RamScanAdd(&g_tagAna.byRamScan12);
	IES_RamScanAdd(&g_tagAna.byRamScan13);
	IES_RamScanAdd(&g_tagAna.byRamScan14);
	IES_RamScanAdd(&g_tagAna.byRamScan15);
	IES_RamScanAdd(&g_tagAna.byRamScan16);
		
	IES_RamScanAdd(&g_tagIO.byRamScan1);
	IES_RamScanAdd(&g_tagIO.byRamScan2);
	IES_RamScanAdd(&g_tagIO.byRamScan3);
	IES_RamScanAdd(&g_tagIO.byRamScan4);
	IES_RamScanAdd(&g_tagIO.byRamScan5);
	IES_RamScanAdd(&g_tagIO.byRamScan6);
	IES_RamScanAdd(&g_tagIO.byRamScan7);
	IES_RamScanAdd(&g_tagIO.byRamScan8);
	IES_RamScanAdd(&g_tagIO.byRamScan9);
	IES_RamScanAdd(&g_tagIO.byRamScan10);
	IES_RamScanAdd(&g_tagIO.byRamScan11);
	IES_RamScanAdd(&g_tagIO.byRamScan12);
	IES_RamScanAdd(&g_tagIO.byRamScan13);
	IES_RamScanAdd(&g_tagIO.byRamScan14);
	IES_RamScanAdd(&g_tagIO.byRamScan15);
	IES_RamScanAdd(&g_tagIO.byRamScan16);
	IES_RamScanAdd(&g_tagIO.byRamScan17);
	IES_RamScanAdd(&g_tagIO.byRamScan18);
	IES_RamScanAdd(&g_tagIO.byRamScan19);
	IES_RamScanAdd(&g_tagIO.byRamScan20);
	IES_RamScanAdd(&g_tagIO.byRamScan21);
	IES_RamScanAdd(&g_tagIO.byRamScan22);
	IES_RamScanAdd(&g_tagIO.byRamScan23);
	IES_RamScanAdd(&g_tagIO.byRamScan24);
	IES_RamScanAdd(&g_tagIO.byRamScan25);
	IES_RamScanAdd(&g_tagIO.byRamScan26);
	IES_RamScanAdd(&g_tagIO.byRamScan27);
	IES_RamScanAdd(&g_tagIO.byRamScan28);
	IES_RamScanAdd(&g_tagIO.byRamScan29);
	IES_RamScanAdd(&g_tagIO.byRamScan30);
	IES_RamScanAdd(&g_tagIO.byRamScan31);
	IES_RamScanAdd(&g_tagIO.byRamScan32);
	IES_RamScanAdd(&g_tagIO.byRamScan33);
	IES_RamScanAdd(&g_tagIO.byRamScan34);
	IES_RamScanAdd(&g_tagIO.byRamScan35);
	IES_RamScanAdd(&g_tagIO.byRamScan36);
	IES_RamScanAdd(&g_tagIO.byRamScan37);
	IES_RamScanAdd(&g_tagIO.byRamScan38);
	IES_RamScanAdd(&g_tagIO.byRamScan39);
	IES_RamScanAdd(&g_tagIO.byRamScan40);
	IES_RamScanAdd(&g_tagIO.byRamScan41);
	IES_RamScanAdd(&g_tagIO.byRamScan42);
	IES_RamScanAdd(&g_tagIO.byRamScan43);
	IES_RamScanAdd(&g_tagIO.byRamScan44);
	IES_RamScanAdd(&g_tagIO.byRamScan45);
	IES_RamScanAdd(&g_tagIO.byRamScan46);

	IES_RamScanAdd(&g_tagDC.byRamScan1);
	IES_RamScanAdd(&g_tagDC.byRamScan2);
	IES_RamScanAdd(&g_tagDC.byRamScan3);
	IES_RamScanAdd(&g_tagDC.byRamScan4);
	IES_RamScanAdd(&g_tagDC.byRamScan5);
	IES_RamScanAdd(&g_tagDC.byRamScan6);
	IES_RamScanAdd(&g_tagDC.byRamScan7);
	IES_RamScanAdd(&g_tagDC.byRamScan8);
	IES_RamScanAdd(&g_tagDC.byRamScan9);
	IES_RamScanAdd(&g_tagDC.byRamScan10);
	IES_RamScanAdd(&g_tagDC.byRamScan11);
	IES_RamScanAdd(&g_tagDC.byRamScan12);
	IES_RamScanAdd(&g_tagDC.byRamScan13);
	IES_RamScanAdd(&g_tagDC.byRamScan14);
	IES_RamScanAdd(&g_tagDC.byRamScan15);
	IES_RamScanAdd(&g_tagDC.byRamScan16);
	IES_RamScanAdd(&g_tagDC.byRamScan17);
	IES_RamScanAdd(&g_tagDC.byRamScan18);

	IES_RamScanAdd(&g_tagPara.byRamScan1);
	IES_RamScanAdd(&g_tagPara.byRamScan2);
	IES_RamScanAdd(&g_tagPara.byRamScan3);
	IES_RamScanAdd(&g_tagPara.byRamScan4);
	IES_RamScanAdd(&g_tagPara.byRamScan5);
	IES_RamScanAdd(&g_tagPara.byRamScan6);
	IES_RamScanAdd(&g_tagPara.byRamScan7);
	IES_RamScanAdd(&g_tagPara.byRamScan8);
	IES_RamScanAdd(&g_tagPara.byRamScan9);
	
	IES_RamScanAdd(&g_tagRamScan.byRamScan1);
	IES_RamScanAdd(&g_tagRamScan.byRamScan2);
	IES_RamScanAdd(&g_tagRamScan.byRamScan3);
	
	IES_RamScanAdd(&g_tagPub.byRamScan1);
	IES_RamScanAdd(&g_tagPub.byRamScan2);

	IES_RamScanAdd(&g_bFlag[CN_NUM_FLAG]);
	IES_RamScanAdd((BYTE*)&g_iInter[CN_NUM_INTER]);
	
	IES_RamScanAdd(&g_tActState.byRamScan1);
	IES_RamScanAdd(&g_tActState.byRamScan2);
	IES_RamScanAdd(&g_tActState.byRamScan3);
	IES_RamScanAdd(&g_tActState.byRamScan4);

	IES_RamScanAdd(&g_tAlmState.byRamScan1);
	IES_RamScanAdd(&g_tAlmState.byRamScan2);
	IES_RamScanAdd(&g_tAlmState.byRamScan3);
	IES_RamScanAdd(&g_tAlmState.byRamScan4);
	IES_RamScanAdd(&g_tAlmState.byRamScan5);
	
	IES_RamScanAdd(&g_tChkState.byRamScan1);
	IES_RamScanAdd(&g_tChkState.byRamScan2);
	IES_RamScanAdd(&g_tChkState.byRamScan3);
	IES_RamScanAdd(&g_tChkState.byRamScan4);
	IES_RamScanAdd(&g_tChkState.byRamScan5);
	IES_RamScanAdd(&g_tChkState.byRamScan6);
	IES_RamScanAdd(&g_tChkState.byRamScan7);
}

