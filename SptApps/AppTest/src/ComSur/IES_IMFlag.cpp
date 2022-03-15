/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * ���ɵ��ӹɷ����޹�˾
 * Ԫ�����ƣ��м��־Ԫ��
 * Ԫ�����ܣ��м��־Ԫ��
 *     1.�м��־�ϳ�
 *     2.�м��־ת��
 * Ԫ���汾��V1.00
 * ����ʱ�䣺2020-9-7
 * �汾�޸ģ�
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
 * V1.00 2021-2-24 ��־��������
 *================================================================================*/

#include "IES_IMFlag.h"

// Ԫ���ӿڽṹ��
tagIES_IMFlag      gtagIES_IMFlag;

// ============================================================================
// �������ܣ���־ת��
// ���������
// ���������
// ����ֵ��  ��
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
// ��־չ��
void IES_IMFlag_Ex(tagIES_IMFlag *pgtagIES_IMFlag)
{
	// �����־Ĭ��չ��2s
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
// �������ܣ��м��־������ʼ��
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMFlag_Para_Init()
{

}

// ============================================================================
// �������ܣ��м��־�ϵ��ʼ��
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMFlag_Init()
{
	IES_memset(&gtagIES_IMFlag,0x0,sizeof(gtagIES_IMFlag));
	IES_RamScanAdd(&gtagIES_IMFlag.byRamScan1);
	IES_RamScanAdd(&gtagIES_IMFlag.byRamScan2);
}
// ============================================================================
// �������ܣ��м��־����������
// ���������
// ���������
// ����ֵ��  ��
// ============================================================================
void IES_IMFlag()
{
	tagIES_IMFlag     *pgtagIES_IMFlag;
	pgtagIES_IMFlag = &gtagIES_IMFlag;
	// ������ʼ��
	if(pgtagIES_IMFlag->dwInit)
	{
		pgtagIES_IMFlag->dwInit = FALSE;
		return;
	}
	IES_IMFlag_Chg(pgtagIES_IMFlag);
	// չ�����־����
	IES_IMFlag_Ex(pgtagIES_IMFlag);
	// �ϵ��ʼ����λ
	pgtagIES_IMFlag->dwPWInit=TRUE;
}

