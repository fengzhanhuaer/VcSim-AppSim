#ifndef _CONST_REC_H_
#define _CONST_REC_H_

/*================================================================================*/
//GOOSE命令信号枚举
/*================================================================================*/
enum _TYPE_REC_ACT_
{
	EN_ACT_STR = 0,
	EN_ACT_BHTZ=EN_ACT_STR,
	EN_ACT_BHHZ,
	EN_ACT_BHYT,
	EN_ACT_CKTZ,
	EN_ACT_CKHZ,
	EN_ACT_JBS_XCBR,
	EN_ACT_BZTTZ,
	EN_ACT_BZTHZ,
	EN_ACT_CLS_XSWI01,
	EN_ACT_OPN_XSWI01,
	EN_ACT_JBS_XSWI01,
	EN_ACT_CLS_XSWI02,
	EN_ACT_OPN_XSWI02,
	EN_ACT_JBS_XSWI02,
	EN_ACT_CLS_XSWI03,
	EN_ACT_OPN_XSWI03,
	EN_ACT_JBS_XSWI03,
	EN_ACT_CLS_XSWI04,
	EN_ACT_OPN_XSWI04,
	EN_ACT_JBS_XSWI04,
	EN_ACT_CLS_XSWI05,
	EN_ACT_OPN_XSWI05,
	EN_ACT_JBS_XSWI05,
	EN_ACT_CLS_XSWI06,
	EN_ACT_OPN_XSWI06,
	EN_ACT_JBS_XSWI06,
	EN_ACT_CLS_XSWI07,
	EN_ACT_OPN_XSWI07,
	EN_ACT_JBS_XSWI07,
	EN_ACT_CLS_XSWI08,
	EN_ACT_OPN_XSWI08,
	EN_ACT_JBS_XSWI08,
	EN_ACT_BAK_01,
	EN_ACT_BAK_02,
	EN_ACT_END
};
/*================================================================================*/
//告警信号枚举
/*================================================================================*/
enum _TYPE_REC_ALM_
{
	EN_ALM_STR = 0,
	EN_ALM_SYN=EN_ALM_STR, // 同步异常
	EN_ALM_SAM,            // 采样异常
	EN_ALM_DIPOW,          // 光耦失电
	EN_ALM_TIME_SINGLE,    // 对时信号状态
	EN_ALM_TIME_SERVICE,   // 对时服务状态
	EN_ALM_TIME_CHKERR,    // 时间跳变侦测状态
	EN_ALM_TEST,           // 检修不一致
	EN_ALM_SV,             // SV总告警
	EN_ALM_SVPUB_INVALID,  // SV发布数据无效
	EN_ALM_LINK,           // 级联异常 
	EN_ALM_SVSUB,          // SV级联数据异常
	
	EN_ALM_SVSUB_COM01,   // SVCB01断链
	EN_ALM_SVSUB_COM02,   // SVCB02断链
	EN_ALM_SVSUB_DAT01,   // SVCB01数据异常
	EN_ALM_SVSUB_DAT02,   // SVCB02数据异常
	EN_ALM_SVSUB_TEST01,  // SVCB01检修不一致
	EN_ALM_SVSUB_TEST02,  // SVCB02检修不一致
	EN_ALM_SVSUB_SYN01,   // SVCB01同步异常
	EN_ALM_SVSUB_SYN02,   // SVCB02同步异常
	EN_ALM_SVSUB_CFG01,   // SVCB01配置异常
	EN_ALM_SVSUB_CFG02,   // SVCB02配置异常

	EN_ALM_SVLINK_QA,     // A套级联SV数据异常
	EN_ALM_SVLINK_QB,     // B套级联SV数据异常
	EN_ALM_SVLINK_CFGA,   // A套级联SV配置异常
	EN_ALM_SVLINK_CFGB,   // B套级联SV配置异常
	EN_ALM_SVLINK_NOCFGA, // A套级联SV未配置
	EN_ALM_SVLINK_NOCFGB, // B套级联SV未配置
	EN_ALM_SVLINK_TESTA,  // A套级联SV检修
	EN_ALM_SVLINK_TESTB,  // B套级联SV检修

	EN_ALM_KHDX,         // 控制回路断线
	EN_ALM_XZBS,         // 选择把手状态异常
	EN_ALM_XSWI,         // 刀闸位置异常
	EN_ALM_PTACT,        // PT切换同时动作
	EN_ALM_PTRET,        // PT切换同时返回
	EN_ALM_OPBP1,        // 操作电源1掉电监视信号
//	EN_ALM_OPBP2,        // 操作电源2掉电监视信号
	EN_ALM_SGZ,          // 事故总
	EN_ALM_SXBYZ,        // 三相不一致 
	EN_ALM_BSCH_OTH,     // 至另一套采集执行单元闭锁重合闸
	EN_ALM_BSCH,         // 闭锁本套保护重合闸
	EN_ALM_BS_LINKQH,    // 级联切换功能闭锁
	EN_ALM_BS_VQH,       // 电压切换功能闭锁
	EN_ALM_BS_DO,        // 出口功能闭锁
	EN_ALM_GOOSE,                            // GOOSE总告警
	EN_ALM_GOOSE_TEST,                       // GOOSE检修不一致
	EN_ALM_GOCB_DATA_STR,                    // GOCB数据异常起始
	EN_ALM_GOCB01_DATA=EN_ALM_GOCB_DATA_STR, // GOCB01数据异常
	EN_ALM_GOCB02_DATA,                      // GOCB02数据异常
	EN_ALM_GOCB03_DATA,                      // GOCB03数据异常
	EN_ALM_GOCB04_DATA,                      // GOCB04数据异常
	EN_ALM_GOCB05_DATA,                      // GOCB05数据异常
	EN_ALM_GOCB06_DATA,                      // GOCB06数据异常
	EN_ALM_GOCB07_DATA,                      // GOCB07数据异常
	EN_ALM_GOCB08_DATA,                      // GOCB08数据异常
	EN_ALM_GOCB09_DATA,                      // GOCB09数据异常
	EN_ALM_GOCB10_DATA,                      // GOCB10数据异常
	EN_ALM_GOCB11_DATA,                      // GOCB11数据异常
	EN_ALM_GOCB12_DATA,                      // GOCB12数据异常
	EN_ALM_GOCB_DATA_END,                    // GOCB数据异常结束
	
	EN_ALM_GOCB_TEST_STR=EN_ALM_GOCB_DATA_END,// GOCB检修不一致起始
	EN_ALM_GOCB01_TEST=EN_ALM_GOCB_TEST_STR, // GOCB01检修不一致
	EN_ALM_GOCB02_TEST,                      // GOCB02检修不一致
	EN_ALM_GOCB03_TEST,                      // GOCB03检修不一致
	EN_ALM_GOCB04_TEST,                      // GOCB04检修不一致
	EN_ALM_GOCB05_TEST,                      // GOCB05检修不一致
	EN_ALM_GOCB06_TEST,                      // GOCB06检修不一致
	EN_ALM_GOCB07_TEST,                      // GOCB07检修不一致
	EN_ALM_GOCB08_TEST,                      // GOCB08检修不一致
	EN_ALM_GOCB09_TEST,                      // GOCB09检修不一致
	EN_ALM_GOCB10_TEST,                      // GOCB10检修不一致
	EN_ALM_GOCB11_TEST,                      // GOCB11检修不一致
	EN_ALM_GOCB12_TEST,                      // GOCB12检修不一致
	EN_ALM_GOCB_TEST_END,                    // GOCB检修不一致结束
	EN_ALM_GOCB_STORM_STR=EN_ALM_GOCB_TEST_END,// GOCB网络风暴
	EN_ALM_GOCB01_STORM=EN_ALM_GOCB_STORM_STR,// GOCB01网络风暴
	EN_ALM_GOCB02_STORM,                     // GOCB02网络风暴
	EN_ALM_GOCB03_STORM,                     // GOCB03网络风暴
	EN_ALM_GOCB04_STORM,                     // GOCB04网络风暴
	EN_ALM_GOCB05_STORM,                     // GOCB05网络风暴
	EN_ALM_GOCB06_STORM,                     // GOCB06网络风暴
	EN_ALM_GOCB07_STORM,                     // GOCB07网络风暴
	EN_ALM_GOCB08_STORM,                     // GOCB08网络风暴
	EN_ALM_GOCB09_STORM,                     // GOCB09网络风暴
	EN_ALM_GOCB10_STORM,                     // GOCB10网络风暴
	EN_ALM_GOCB11_STORM,                     // GOCB11网络风暴
	EN_ALM_GOCB12_STORM,                     // GOCB12网络风暴
	EN_ALM_GOCB_STORM_END,                   // GOCB检修不一致结束
	EN_ALM_CCD_SVSUB=EN_ALM_GOCB_STORM_END,
	EN_ALM_CCD_SVPUB,
	EN_ALM_CCD_GOSUB,
	EN_ALM_CCD_GOPUB,
	EN_ALM_BOARD_CPU2,
	EN_ALM_BAK01,
	EN_ALM_BAK02,
	EN_ALM_BAK03,
	EN_ALM_BAK04,
	EN_ALM_BAK05,
	EN_ALM_BAK06,
	EN_ALM_BAK07,
	EN_ALM_BAK08,
	EN_ALM_BAK09,
	EN_ALM_BAK10,
	EN_ALM_END          // 告警结束
};
/*================================================================================*/
//自检信号枚举
/*================================================================================*/
enum _TYPE_REC_CHK_
{
// 装置全局自检(闭锁装置全部功能)
	EN_CHK_STR=0,               // 自检开始
	EN_CHK_CONST=EN_CHK_STR,
	EN_CHK_RAM_ERR,
	EN_CHK_RAM_ALLOC,
	EN_CHK_RAM_CHK,
	EN_CHK_CCD_NO,
	EN_CHK_CCD_ERR,
	EN_CHK_CCD_PARALOSE,
	EN_CHK_CCD_PARAERR,
	EN_CHK_CCD_CRC,
	EN_CHK_CCD_FRAME,
	EN_CHK_CCD_ADDRERR,
	EN_CHK_CCD_NUMERR,
	EN_CHK_CCD_CFGERR,
//	EN_CHK_CCD_SVSUB,
//	EN_CHK_CCD_SVPUB,
//	EN_CHK_CCD_GOSUB,
//	EN_CHK_CCD_GOPUB,
// DO返校自检(不闭锁)
	EN_CHK_DO_RTN0_STR,
	EN_CHK_DO1_RTN0=EN_CHK_DO_RTN0_STR+EN_BOARD_DO1,
	EN_CHK_DO2_RTN0=EN_CHK_DO_RTN0_STR+EN_BOARD_DO2,
	EN_CHK_DIO_RTN0=EN_CHK_DO_RTN0_STR+EN_BOARD_DO3,
	EN_CHK_DO_RTN1_STR=EN_CHK_DO_RTN0_STR+CN_NUM_BOARD_DO_RTN,
	EN_CHK_DO1_RTN1=EN_CHK_DO_RTN1_STR+EN_BOARD_DO1,
	EN_CHK_DO2_RTN1=EN_CHK_DO_RTN1_STR+EN_BOARD_DO2,
	EN_CHK_DIO_RTN1=EN_CHK_DO_RTN1_STR+EN_BOARD_DO3,
// DO下行通道自检(不闭锁)
	//EN_CHK_BOARD_DO_CHN1_STR=EN_CHK_DO_RTN1_STR+CN_NUM_BOARD_DO_RTN,
	//EN_CHK_BOARD_DO1_CHN1=EN_CHK_BOARD_DO_CHN1_STR+EN_BOARD_DO1,
	//EN_CHK_BOARD_DO2_CHN1=EN_CHK_BOARD_DO_CHN1_STR+EN_BOARD_DO2,
	//EN_CHK_BOARD_DIO_CHN1=EN_CHK_BOARD_DO_CHN1_STR+EN_BOARD_DO3,
	//EN_CHK_BOARD_DO_CHN2_STR=EN_CHK_BOARD_DO_CHN1_STR+CN_NUM_BOARD_DO_RTN,
	//EN_CHK_BOARD_DO1_CHN2=EN_CHK_BOARD_DO_CHN2_STR+EN_BOARD_DO1,
	//EN_CHK_BOARD_DO2_CHN2=EN_CHK_BOARD_DO_CHN2_STR+EN_BOARD_DO2,
	//EN_CHK_BOARD_DIO_CHN2=EN_CHK_BOARD_DO_CHN2_STR+EN_BOARD_DO3,
	//EN_CHK_BOARD_DO_POW24_STR=EN_CHK_BOARD_DO_CHN2_STR+CN_NUM_BOARD_DO_RTN,
	//EN_CHK_BOARD_DO1_POW24=EN_CHK_BOARD_DO_POW24_STR+EN_BOARD_DO1,
	//EN_CHK_BOARD_DO2_POW24=EN_CHK_BOARD_DO_POW24_STR+EN_BOARD_DO2,
	//EN_CHK_BOARD_DIO_POW24=EN_CHK_BOARD_DO_POW24_STR+EN_BOARD_DO3,
	EN_CHK_BOARD_DO_POW30_STR=EN_CHK_DO_RTN1_STR+CN_NUM_BOARD_DO_RTN,
	EN_CHK_BOARD_DO1_POW30=EN_CHK_BOARD_DO_POW30_STR+EN_BOARD_DO1,
	EN_CHK_BOARD_DO2_POW30=EN_CHK_BOARD_DO_POW30_STR+EN_BOARD_DO2,
	EN_CHK_BOARD_DIO_POW30=EN_CHK_BOARD_DO_POW30_STR+EN_BOARD_DO3,
	//EN_CHK_BOARD_DO_PARA_STR=EN_CHK_BOARD_DO_POW30_STR+CN_NUM_BOARD_DO_RTN,
	//EN_CHK_BOARD_DO1_PARA=EN_CHK_BOARD_DO_PARA_STR+EN_BOARD_DO1,
	//EN_CHK_BOARD_DO2_PARA=EN_CHK_BOARD_DO_PARA_STR+EN_BOARD_DO2,
	//EN_CHK_BOARD_DIO_PARA=EN_CHK_BOARD_DO_PARA_STR+EN_BOARD_DO3,
// 参数自检(闭锁对应功能)
	EN_CHK_PARA_STR,
	EN_CHK_PARA_DI       =EN_CHK_PARA_STR+EN_BOARD_PARA_DI,
	EN_CHK_PARA_DC       =EN_CHK_PARA_STR+EN_BOARD_PARA_DC,
	EN_CHK_PARA_SAM      =EN_CHK_PARA_STR+EN_BOARD_PARA_SAM,
	EN_CHK_PARA_FUN      =EN_CHK_PARA_STR+EN_BOARD_PARA_FUN,
	EN_CHK_PARA_DC_COE   =EN_CHK_PARA_STR+EN_BOARD_PARA_DC_COE,
	EN_CHK_PARA_AM_COE   =EN_CHK_PARA_STR+EN_BOARD_PARA_AM_COE,
	EN_CHK_PARA_DCBC_COE =EN_CHK_PARA_STR+EN_BOARD_PARA_DCBC_COE,
	EN_CHK_PARA_ANG_COE  =EN_CHK_PARA_STR+EN_BOARD_PARA_ANG_COE,
	EN_CHK_PARA_END      =EN_CHK_PARA_STR+EN_BOARD_PARA_END,
	EN_CHK_PARA_DI_HLD   =EN_CHK_PARA_END,
// 板卡自检(对应数据无效)
	EN_CHK_BOARD_DI_STR,// 
	EN_CHK_BOARD_DI1      =EN_CHK_BOARD_DI_STR+EN_BOARD_DI1,
	EN_CHK_BOARD_DI2      =EN_CHK_BOARD_DI_STR+EN_BOARD_DI2,
	EN_CHK_BOARD_DI3      =EN_CHK_BOARD_DI_STR+EN_BOARD_DI3,
	EN_CHK_BOARD_DIO_DI   =EN_CHK_BOARD_DI_STR+EN_BOARD_DI4,
	EN_CHK_BOARD_OPB1     =EN_CHK_BOARD_DI_STR+EN_BOARD_DI5,
	
	EN_CHK_BOARD_DO_STR   =EN_CHK_BOARD_DI_STR+EN_BOARD_DI_DO_STR,// 
	EN_CHK_BOARD_DO1      =EN_CHK_BOARD_DO_STR+EN_BOARD_DO1,
	EN_CHK_BOARD_DO2      =EN_CHK_BOARD_DO_STR+EN_BOARD_DO2,
	EN_CHK_BOARD_DIO_DO   =EN_CHK_BOARD_DO_STR+EN_BOARD_DO3,
	EN_CHK_BOARD_DI_END   =EN_CHK_BOARD_DI_STR+EN_BOARD_DI_END,
	EN_CHK_BOARD_DC_STR   =EN_CHK_BOARD_DI_END,
	EN_CHK_BOARD_DC_SAM   =EN_CHK_BOARD_DC_STR+EN_BOARD_DC_SAM,
	EN_CHK_BOARD_DC_DEV   =EN_CHK_BOARD_DC_STR+EN_BOARD_DC_DEV,
	EN_CHK_BOARD_DC_OPT1_1=EN_CHK_BOARD_DC_STR+EN_BOARD_DC_OPT1_1,
	EN_CHK_BOARD_DC_OPT1_2=EN_CHK_BOARD_DC_STR+EN_BOARD_DC_OPT1_2,
	EN_CHK_BOARD_DC_OPT2  =EN_CHK_BOARD_DC_STR+EN_BOARD_DC_OPT2,
	EN_CHK_BOARD_DC_END   =EN_CHK_BOARD_DC_STR+EN_BOARD_DC_END,
	EN_CHK_BOARD_SAM_STR  =EN_CHK_BOARD_DC_END,
	EN_CHK_BOARD_PTCT1    =EN_CHK_BOARD_SAM_STR+EN_BOARD_SAM_PTCT1,
	EN_CHK_BOARD_PTCT2    =EN_CHK_BOARD_SAM_STR+EN_BOARD_SAM_PTCT2,
	EN_CHK_BOARD_CPU      =EN_CHK_BOARD_SAM_STR+EN_BOARD_SAM_CPU,
	EN_CHK_BOARD_SAM_END  =EN_CHK_BOARD_SAM_STR+CN_NUM_BOARD_SAM,
	EN_CHK_BOARD_CPU_AUX  =EN_CHK_BOARD_SAM_END,
	EN_CHK_BOARD_POW,
	EN_CHK_BOARD_CPU2,
	EN_CHK_BOARD_LED,
	EN_CHK_FRAME_ANA,    // 模拟量帧总异常
// 板间交互自检(无闭锁)
	EN_CHK_CPUCOM_FAST,
	EN_CHK_CPUCOM_PARA,
	EN_CHK_CPUCOM_VER,
	EN_CHK_CPUCOM_CCD,
// 备用自检
	EN_CHK_BAK01,
	EN_CHK_BAK02,
	EN_CHK_BAK03,
	EN_CHK_BAK04,
	EN_CHK_BAK05,
	EN_CHK_BAK06,
	EN_CHK_BAK07,
	EN_CHK_BAK08,
	EN_CHK_BAK09,
	EN_CHK_BAK10,
	EN_CHK_END                  // 自检结束
};
/*================================================================================*/
//操作信号枚举
/*================================================================================*/
enum _TYPE_RUN_OPT_
{
	EN_RUN_STR=0,
	EN_RUN_POW_ON=EN_RUN_STR,
	EN_RUN_POW_OFF,
	EN_RUN_SVPUB_ENA,
	EN_RUN_GOPUB_ENA,
	EN_RUN_SVPUB_BS,
	EN_RUN_GOPUB_BS,
	EN_RUN_POL,
	EN_RUN_LNKQH_S,
	EN_RUN_VQH_S,
	EN_RUN_UX_S,
	EN_RUN_COM_S,
	EN_RUN_AM_COE_S,
	EN_RUN_DCBC_COE_S,
	EN_RUN_ANG_COE_S,
	EN_RUN_PARASYN_S_STR,
	EN_RUN_PARASYN_S_END=EN_RUN_PARASYN_S_STR+CN_NUM_BOARD_PARA_COM,
	EN_RUN_PARASYN_F_STR=EN_RUN_PARASYN_S_END,
	EN_RUN_PARASYN_F_END=EN_RUN_PARASYN_F_STR+CN_NUM_BOARD_PARA_COM,
	// 备用运行
	EN_RUN_BAK01=EN_RUN_PARASYN_F_END,
	EN_RUN_BAK02,
	EN_RUN_BAK03,
	EN_RUN_BAK04,
	EN_RUN_BAK05,
	EN_RUN_BAK06,
	EN_RUN_BAK07,
	EN_RUN_BAK08,
	EN_RUN_BAK09,
	EN_RUN_BAK10,
	EN_RUN_END,
};
/*================================================================================*/
//操作信号枚举
/*================================================================================*/
enum _TYPE_REC_OPT_
{
	EN_OPT_STR=0,                   // 操作信号开始
	// 参数相关操作
	EN_OPT_PARA_W_SUCC_STR=EN_OPT_STR,
	EN_OPT_PARA_W_SUCC_END=EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_END,
	EN_OPT_PARA_W_FAIL_STR=EN_OPT_PARA_W_SUCC_END,
	EN_OPT_PARA_W_FAIL_END=EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_END,
	EN_OPT_PARA_INIT_SUCC_STR=EN_OPT_PARA_W_FAIL_END,      // 开关量参数初始化成功
	EN_OPT_PARA_INIT_SUCC_END=EN_OPT_PARA_INIT_SUCC_STR+EN_BOARD_PARA_END,      // 开关量参数初始化成功
	
	EN_OPT_PARA_INIT_FAIL_STR=EN_OPT_PARA_INIT_SUCC_END,      // 开关量参数初始化成功
	EN_OPT_PARA_INIT_FAIL_END=EN_OPT_PARA_INIT_FAIL_STR+EN_BOARD_PARA_END,      // 开关量参数初始化成功

	EN_OPT_ADJ_DCBC_SUCC  =EN_OPT_PARA_INIT_FAIL_END,           // 交流量直流补偿校准成功
	EN_OPT_ADJ_DCBC_FAIL,           // 交流量直流补偿校准失败
	EN_OPT_ADJ_AM_SUCC,             // 交流量幅值校准成功
	EN_OPT_ADJ_AM_FAIL,             // 交流量幅值校准失败
	EN_OPT_ADJ_ANG_SUCC,            // 交流量相位校准成功
	EN_OPT_ADJ_ANG_FAIL,            // 交流量相位校准失败
	EN_OPT_ADJ_DC_SUCC,             // 直流量自动校准成功
	EN_OPT_ADJ_DC_FAIL,             // 直流量自动校准失败
	// 界面调试
	EN_OPT_DEBUG_IN,                // 装置调试态进入
	EN_OPT_DEBUG_OUT,               // 装置调试态退出
	EN_OPT_FACT_DEBUG_IN,           // 厂家调试态进入
	EN_OPT_FACT_DEBUG_OUT,          // 厂家调试态退出
	
	EN_OPT_DEBUG_LED,               // 指示灯调试
	EN_OPT_DEBUG_DO,                // 出口传动调试
	EN_OPT_DEBUG_GO_S,              // GOOSE通信单点调试
	EN_OPT_DEBUG_GO_Dp,             // GOOSE通信双点调试
	EN_OPT_DEBUG_GO_DC,             // GOOSE置数调试
	EN_OPT_ACT_DEl,                 // 清除GOOSE命令事项
	EN_OPT_ALM_DEl,                 // 清除告警事项
	EN_OPT_CHK_DEl,                 // 清除自检事项
	EN_OPT_DI_SOE_DEl,              // 清除硬开入SOE事项
	EN_OPT_DO_SOE_DEl,              // 清除硬开出SOE事项
	EN_OPT_GOIN_SOE_DEl,            // 清除硬GOOSE开入SOE事项
	EN_OPT_GOOUT_SOE_DEl,           // 清除硬GOOSE开出SOE事项
	EN_OPT_LED_SOE_DEl,             // 清除硬指示灯SOE事项
	EN_OPT_DPI_SOE_DEl,             // 清除双点遥信SOE事项
	EN_OPT_FLAG_SOE_DEl,            // 清除虚遥信SOE事项
	EN_OPT_TIME_W_SUCC,             // 时钟修改成功
	EN_OPT_TIME_W_FAIL,             // 时钟修改失败
	EN_OPT_BAK01,
	EN_OPT_BAK02,
	EN_OPT_BAK03,
	EN_OPT_BAK04,
	EN_OPT_BAK05,
	EN_OPT_BAK06,
	EN_OPT_BAK07,
	EN_OPT_BAK08,
	EN_OPT_BAK09,
	EN_OPT_BAK10,
	EN_OPT_END,                     // 操作信号结束
};
enum _TYPE_REC_PRVT_
{
	
	EN_PRVT_SOE_STR=0,                     // 内部事项信号开始
	EN_PRVT_SOE_BAK0=EN_PRVT_SOE_STR,      // 内部事项信号备用
	EN_PRVT_SOE_END,                       // 内部事项信号结束
	
	EN_PRVT_OPT_STR=0,                     // 操作信号开始
	EN_PRVT_OPT_DEV_LINK=EN_PRVT_OPT_STR,  // 调试工具连接成功
	EN_PRVT_OPT_DEV_BREAK,                 // 调试工具连接中断
	EN_PRVT_OPT_DATA_R_SUCC,               // 召唤数据成功
	EN_PRVT_OPT_DATA_R_FAIL,               // 召唤数据失败
	EN_PRVT_OPT_FILE_UP_SUCC,              // 文件上传成功
	EN_PRVT_OPT_FILE_UP_FAIL,              // 文件上传失败
	EN_PRVT_OPT_FILE_DN_SUCC,              // 文件下载成功
	EN_PRVT_OPT_FILE_DN_FAIL,              // 文件下载失败
	EN_PRVT_OPT_FLASH_BAK_SUCC,            // 参数备份成功
	EN_PRVT_OPT_FLASH_BAK_FAIL,            // 参数备份失败
	EN_PRVT_OPT_PARA_REST_SUCC,            // 参数还原成功
	EN_PRVT_OPT_PARA_REST_FAIL,            // 参数还原失败
	EN_PRVT_OPT_UPDATE_BOOT0_SUCC,         // BOOT0升级成功
	EN_PRVT_OPT_UPDATE_BOOT0_FAIL,         // BOOT0升级失败
	EN_PRVT_OPT_UPDATE_UBOOT_SUCC,         // UBOOT升级成功
	EN_PRVT_OPT_UPDATE_UBOOT_FAIL,         // UBOOT升级失败
	EN_PRVT_OPT_UPDATE_SYSTEM_SUCC,        // SYSTEM升级成功
	EN_PRVT_OPT_UPDATE_SYSTEM_FAIL,        // SYSTEM升级失败
	EN_PRVT_OPT_UPDATE_FPGA1_SUCC,         // FPGA1升级成功
	EN_PRVT_OPT_UPDATE_FPGA1_FAIL,         // FPGA1升级失败
	EN_PRVT_OPT_UPDATE_FPGA2_SUCC,         // FPGA2升级成功
	EN_PRVT_OPT_UPDATE_FPGA2_FAIL,         // FPGA2升级失败
	EN_PRVT_OPT_EVENT_ALL_DEl,             // 清除所有事项
	EN_PRVT_OPT_RUN_DEl,                   // 清除运行事项
	EN_PRVT_OPT_OPT_DEl,                   // 清除操作事项
	EN_PRVT_OPT_PRVT_SOE_DEl,              // 清除内部事项
	EN_PRVT_OPT_PRVT_OPT_DEl,              // 清除操作事项
	EN_PRVT_OPT_ETH_W_SUCC,                // 网络参数修改成功
	EN_PRVT_OPT_ETH_W_FAIL,                // 网络参数修改失败
	EN_PRVT_OPT_END,                       // 操作信号结束
};

/*================================================================================*/
//常量表结构体
/*================================================================================*/
// GOOSE命令事项最大源枚举个数
#define CN_ACT_SNUM (32)
typedef struct
{
	WORD			wIndex; 						// 记录枚举
	WORD			wSrcType;						// 数据源类型
	WORD			wSrcIndex[CN_ACT_SNUM];			// 数据源枚举
	WORD			wDoIndex;						// 出口枚举
	WORD			wDoRetIndex;					// 出口返校
	WORD			wCfg; 							// 其他设置
	WORD			wValType1; 						// 事项记录数据类型1
	WORD			wValType2; 						// 事项记录数据类型2
	WORD			wValType3; 						// 事项记录数据类型3
	WORD			wValType4; 						// 事项记录数据类型4
	WORD			wValType5; 						// 事项记录数据类型5
	WORD			wValType6; 						// 事项记录数据类型6
	INT8S			byName[CN_LEN_NAME]; 			// 记录名称
	INT8S			byPinName[CN_LEN_NAME];			// 虚端子名称
} tagActTab;
/*================================================================================*/
//常量表结构体
/*================================================================================*/
typedef struct
{
	WORD			wIndex; 						// 记录枚举
	WORD			wParaEna; 						// 投退参数枚举
	WORD			wParaTime; 						// 时间参数枚举
	DWORD			dwDefTime; 						// 默认时间参数
	DWORD			dwRetTime; 						// 默认返回时间参数
	WORD			wCfg; 							// 其他设置
	WORD			wValType1; 						// 事项记录数据类型1
	WORD			wValType2; 						// 事项记录数据类型2
	WORD			wValType3; 						// 事项记录数据类型3
	INT8S			byName[CN_LEN_NAME]; 			// 记录名称
	INT8S			byPinName[CN_LEN_NAME];			// 虚端子名称
} tagAlmTab;
typedef struct
{
	WORD			wIndex; 						// 记录枚举
	//WORD			wParaEna; 						// 投退参数枚举
	//WORD			wParaTime; 						// 时间参数枚举
	DWORD			dwActCnt; 						// 默认时间参数
	DWORD			dwRetCnt; 						// 默认返回时间参数
	WORD			wCfg; 							// 其他设置
	WORD			wValType1; 						// 事项记录数据类型1
	WORD			wValType2; 						// 事项记录数据类型2
	WORD			wValType3; 						// 事项记录数据类型3
	INT8S			byName[CN_LEN_NAME]; 			// 记录名称
	INT8S			byPinName[CN_LEN_NAME]; 		// 虚端子名称
} tagChkTab;

typedef struct
{
	WORD			wIndex; 						// 记录枚举
	WORD			wCfg; 							// 其他设置
	INT8S			byName[CN_LEN_NAME]; 			// 记录名称
	INT8S			byPinName[CN_LEN_NAME]; 		// 虚端子名称
} tagRunTab;

typedef struct
{
	WORD			wIndex; 						// 记录枚举
	WORD			wCfg; 							// 其他设置
	WORD			wValType1; 						// 事项记录数据类型1
	WORD			wValType2; 						// 事项记录数据类型2
	WORD			wValType3; 						// 事项记录数据类型3
	INT8S			byName[CN_LEN_NAME]; 			// 记录名称
	INT8S			byPinName[CN_LEN_NAME]; 		// 虚端子名称
} tagOptTab;

typedef struct
{
	WORD			wIndex; 						// 记录枚举
	WORD			wCfg; 							// 其他设置
	INT8S			byName[CN_LEN_NAME]; 			// 记录名称
	INT8S			byPinName[CN_LEN_NAME]; 		// 虚端子名称
} tagPrvtSoeTab;

typedef struct
{
	WORD			wIndex; 						// 记录枚举
	WORD			wCfg; 							// 其他设置
	INT8S			byName[CN_LEN_NAME]; 			// 记录名称
	INT8S			byPinName[CN_LEN_NAME]; 		// 虚端子名称
} tagPrvtOptTab;

/*================================================================================*/
// 宏定义
/*================================================================================*/
#define CN_NUM_ACT    (EN_ACT_END)
#define CN_NUM_ALM    (EN_ALM_END)
#define CN_NUM_CHK    (EN_CHK_END)
#define CN_NUM_RUN    (EN_RUN_END)
#define CN_NUM_OPT    (EN_OPT_END)
#define CN_NUM_PRVT_SOE    (EN_PRVT_SOE_END)
#define CN_NUM_PRVT_OPT    (EN_PRVT_OPT_END)


#define CN_NUM_ALM_GOCB_DATA  (EN_ALM_GOCB_DATA_END-EN_ALM_GOCB_DATA_STR)
#define CN_NUM_ALM_GOCB_TEST  (EN_ALM_GOCB_TEST_END-EN_ALM_GOCB_TEST_STR)

/*================================================================================*/
// 常量表声明
/*================================================================================*/
extern const tagActTab g_tActTab[];
extern const DWORD     g_NUM_ACT;
extern const tagAlmTab g_tAlmTab[];
extern const DWORD     g_NUM_ALM;
extern const tagChkTab g_tChkTab[];
extern const DWORD     g_NUM_CHK;
extern const tagOptTab g_tOptTab[];
extern const DWORD     g_NUM_OPT;
extern const tagRunTab g_tRunTab[];
extern const DWORD     g_NUM_RUN;

extern const tagPrvtSoeTab g_tPrvtSoeTab[];
extern const DWORD         g_NUM_PRVT_SOE;
extern const tagPrvtOptTab g_tPrvtOptTab[];
extern const DWORD         g_NUM_PRVT_OPT;

#endif  // _CONST_REC_H_

