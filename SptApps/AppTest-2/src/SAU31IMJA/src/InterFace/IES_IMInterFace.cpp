/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * 积成电子股份有限公司
 * 元件名称：接口元件
 * 元件功能：接口元件
 *     1.应用上电初始化
 *     2.应用任务调用部分
 *     3.应用平台调用部分
 * 元件版本：V1.00
 * 定版时间：2020-9-7
 * 版本修改：
 * <版本号> <修改日期>, <修改人员>: <修改功能概述>
 * V1.00 2021-2-24 刘志利：初版
 *================================================================================*/

#include "IES_IMInterFace.h"
// 应用初始化接口
void IES_IM_Init(void)
{
	// 1.全局变量初始化
	IES_IMInit_RealData();
	// 2.常量表上电自检
	IES_IMInit_ConstChk();
	// 3.指针常量上电初始化
	// 4.组件初始化
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
// 参数更新接口
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
// 配置上电自检接口
void IES_IM_Cfg_Init(void)
{
#if(CN_SV_IN_ENA)
	IES_IMSam_SvSub_Init();
#endif
	IES_IMSam_SvPub_Init();
}

// 应用任务部分接口(主要用于更新慢速信息及参数)
void IES_IM_Main(void)
{

}
// 应用中断部分接口
void IES_IM_Interrupt(void)
{
    // 注意中断函数调用顺序不能改变！！！
	IES_RamScanChk();
	IES_IMSam();
	IES_IMDI();
	IES_IMDC();
	if(G_Sys_Div4_3)
	IES_IMCom_Fast_Rx();
	IES_IMLogic();
	// 保证时效性,模拟量品质最后处理
	IES_IMSam_Q();
	
	IES_IMRec();
	IES_IMFlag();
	IES_IMDO();
	// 顺序不能颠倒
	if(G_Sys_Div4_1)
	IES_IMCom_Fast_Tx();
}
