/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * ���ɵ��ӹɷ����޹�˾
 * Ԫ�����ƣ��ӿ�Ԫ��
 * Ԫ�����ܣ��ӿ�Ԫ��
 *     1.Ӧ���ϵ��ʼ��
 *     2.Ӧ��������ò���
 *     3.Ӧ��ƽ̨���ò���
 * Ԫ���汾��V1.00
 * ����ʱ�䣺2020-9-7
 * �汾�޸ģ�
 * <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
 * V1.00 2021-2-24 ��־��������
 *================================================================================*/

#include "IES_IMInterFace.h"
// Ӧ�ó�ʼ���ӿ�
void IES_IM_Init(void)
{
	// 1.ȫ�ֱ�����ʼ��
	IES_IMInit_RealData();
	// 2.�������ϵ��Լ�
	IES_IMInit_ConstChk();
	// 3.ָ�볣���ϵ��ʼ��
	// 4.�����ʼ��
	IES_IMSam_Init();
	IES_IMFlag_Init();
	IES_IMDI_Init();
	IES_IMDC_Init();
	IES_IMLogic_Init();
	IES_IMRec_Init();
	IES_IMFlag_Init();
	IES_IMDO_Init();
	IES_IMCom_Init();
}
// �������½ӿ�
void IES_IM_Para_Init(void)
{
	IES_IMSam_Para_Init();
	IES_IMFlag_Para_Init();
	IES_IMDI_Para_Init();
	IES_IMDC_Para_Init();
	IES_IMLogic_Para_Init();
	IES_IMRec_Para_Init();
	IES_IMFlag_Para_Init();
	IES_IMDO_Para_Init();
}
// �����ϵ��Լ�ӿ�
void IES_IM_Cfg_Init(void)
{
#if(CN_SV_IN_ENA)
	IES_IMSam_SvSub_Init();
#endif
	IES_IMSam_SvPub_Init();
}

// Ӧ�����񲿷ֽӿ�(��Ҫ���ڸ���������Ϣ������)
void IES_IM_Main(void)
{

}
// Ӧ���жϲ��ֽӿ�
void IES_IM_Interrupt(void)
{
    // ע���жϺ�������˳���ܸı䣡����
	IES_RamScanChk();
	IES_IMSam();
	IES_IMDI();
	IES_IMDC();
	if(G_Sys_Div4_3)
	IES_IMCom_Fast_Rx();
	IES_IMLogic();
	// ��֤ʱЧ��,ģ����Ʒ�������
	IES_IMSam_Q();
	
	IES_IMRec();
	IES_IMFlag();
	IES_IMDO();
	// ˳���ܵߵ�
	if(G_Sys_Div4_1)
	IES_IMCom_Fast_Tx();
}
