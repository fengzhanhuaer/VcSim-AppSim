#ifndef _CONST_IO_H_
#define _CONST_IO_H_

/*================================================================================*/
// 开入信号枚举
/*================================================================================*/
// 硬开入信号枚举
enum _DI_NUMBER
{
	EN_DI_STR = 0,
/*=============================*/
// DWORD1.开入板1枚举
/*=============================*/
	EN_DI_BOARD1_STR = EN_DI_STR,
	EN_DI_TEST = EN_DI_BOARD1_STR,   // 检修状态硬压板
	EN_DI_RESET,                     // 信号复归
	EN_DI_XCBR_OPN,
	EN_DI_XCBR_CLS,
	//刀闸位置
	EN_DI_XSWI01_OPN,
	EN_DI_XSWI01_CLS,
	EN_DI_XSWI02_OPN,
	EN_DI_XSWI02_CLS,
	EN_DI_XSWI03_OPN,
	EN_DI_XSWI03_CLS,
	EN_DI_XSWI04_OPN,
	EN_DI_XSWI04_CLS,
	EN_DI_XSWI05_OPN,
	EN_DI_XSWI05_CLS,
	EN_DI_XSWI06_OPN,
	EN_DI_XSWI06_CLS,
	EN_DI_XSWI07_OPN,
	EN_DI_XSWI07_CLS,
	EN_DI_XSWI08_OPN,
	EN_DI_XSWI08_CLS,
	EN_DI_BC_YLD,     // 压力低闭重
	EN_DI_BC_OTH,     // 另一套闭重
	EN_DI_TJF,        // TJF跳闸信号
	EN_DI_STJ,        // 手跳
	EN_DI_SHJ,        // 手合
	EN_DI_KKJ,        // 合后
	EN_DI_LNK_A,      // 取A套
	EN_DI_LNK_B,      // 取B套
	EN_DI_LNK_AUTO,   // 自动
	EN_DI_SHJ_SYN,    // 手合同期开入
	EN_DI_POW1,       // 开入板1遥信电源监视
	EN_DI_BOARD1_END,
/*==============================*/
// DWORD2.开入板2枚举
/*=============================*/
	EN_DI_BOARD2_STR=EN_DI_BOARD1_END,
	//备用开入
	EN_DI_OTH_ALM=EN_DI_BOARD2_STR,    // 另一套采集执行单元运行异常
	EN_DI_OTH_CHK,                     // 另一套采集执行单元故障
	EN_DI_YX_BAK01,
	EN_DI_YX_BAK02,
	EN_DI_YX_BAK03,
	EN_DI_YX_BAK04,
	EN_DI_YX_BAK05,
	EN_DI_YX_BAK06,
	EN_DI_YX_BAK07,
	EN_DI_YX_BAK08,
	EN_DI_YX_BAK09,
	EN_DI_YX_BAK10,
	EN_DI_YX_BAK11,
	EN_DI_YX_BAK12,
	EN_DI_YX_BAK13,
	EN_DI_YX_BAK14,
	EN_DI_YX_BAK15,
	EN_DI_YX_BAK16,
	EN_DI_YX_BAK17,
	EN_DI_YX_BAK18,
	EN_DI_YX_BAK19,
	EN_DI_YX_BAK20,
	EN_DI_YX_BAK21,
	EN_DI_YX_BAK22,
	EN_DI_YX_BAK23,
	EN_DI_YX_BAK24,
	EN_DI_YX_BAK25,
	EN_DI_YX_BAK26,
	EN_DI_YX_BAK27,
	EN_DI_YX_BAK28,
	EN_DI_POW2,       // 开入板2遥信电源监视
	EN_DI_BOARD2_END,
/*==============================*/
// DWORD3.开入板3枚举
/*=============================*/
	EN_DI_BOARD3_STR=EN_DI_BOARD2_END,
	EN_DI_YX_BAK29=EN_DI_BOARD3_STR,
	EN_DI_YX_BAK30,
	EN_DI_YX_BAK31,
	EN_DI_YX_BAK32,
	EN_DI_YX_BAK33,
	EN_DI_YX_BAK34,
	EN_DI_YX_BAK35,
	EN_DI_YX_BAK36,
	EN_DI_YX_BAK37,
	EN_DI_YX_BAK38,
	EN_DI_YX_BAK39,
	EN_DI_YX_BAK40,
	EN_DI_YX_BAK41,
	EN_DI_YX_BAK42,
	EN_DI_YX_BAK43,
	EN_DI_YX_BAK44,
	EN_DI_YX_BAK45,
	EN_DI_YX_BAK46,
	EN_DI_YX_BAK47,
	EN_DI_YX_BAK48,
	EN_DI_YX_BAK49,
	EN_DI_YX_BAK50,
	EN_DI_YX_BAK51,
	EN_DI_YX_BAK52,
	EN_DI_YX_BAK53,
	EN_DI_YX_BAK54,
	EN_DI_YX_BAK55,
	EN_DI_YX_BAK56,
	EN_DI_YX_BAK57,
	EN_DI_YX_BAK58,
	EN_DI_POW3,       // 开入板3遥信电源监视
	EN_DI_BOARD3_END,
/*==============================*/
// DWORD4.开入开出板枚举--开入部分
/*=============================*/
	EN_DI_BOARD4_STR=EN_DI_BOARD3_END,
	EN_DI_YX_BAK59=EN_DI_BOARD4_STR,
	EN_DI_YX_BAK60,
	EN_DI_YX_BAK61,
	EN_DI_YX_BAK62,
	EN_DI_YX_BAK63,
	EN_DI_YX_BAK64,
	EN_DI_YX_BAK65,
	EN_DI_YX_BAK66,
	EN_DI_YX_BAK67,
	EN_DI_YX_BAK68,
	EN_DI_YX_BAK69,
	EN_DI_YX_BAK70,
	EN_DI_YX_BAK71,
	EN_DI_POW4,        // 开入开出板遥信电源监视
//	EN_DI_YX_BAK72,
//	EN_DI_YX_BAK73,
//	EN_DI_YX_BAK74,
//	EN_DI_YX_BAK75,
//	EN_DI_YX_BAK76,
//	EN_DI_YX_BAK77,
//	EN_DI_YX_BAK78,
//	EN_DI_YX_BAK79,
//	EN_DI_YX_BAK80,
//	EN_DI_YX_BAK81,
//	EN_DI_YX_BAK82,
//	EN_DI_YX_BAK83,
//	EN_DI_YX_BAK84,
//	EN_DI_YX_BAK85,
//	EN_DI_YX_BAK86,
//	EN_DI_YX_BAK87,
//	EN_DI_YX_BAK88,
	EN_DI_BOARD4_END,
/*==============================*/
//  DWORD5.OPB1板枚举-内部采集信号
/*==============================*/
	EN_DI_BOARD5_STR=EN_DI_BOARD4_END,
	EN_DI_OPB1_HWJ=EN_DI_BOARD5_STR,
	EN_DI_OPB1_TWJ,
	EN_DI_OPB1_POW,
	EN_DI_OPB1_KKJ,
	EN_DI_OPB1_TJF,
	EN_DI_OPB1_STJ,
	EN_DI_OPB1_SHJ,
	EN_DI_BOARD5_END,
#if 0
	EN_DI_BOARD9_STR=EN_DI_BOARD8_END,
	EN_DI_OPB2_HWJ=EN_DI_BOARD9_STR,
	EN_DI_OPB2_TWJ,
	EN_DI_OPB2_POW,
	EN_DI_OPB2_KKJ,
	EN_DI_OPB2_TJF,
	EN_DI_OPB2_STJ,
	EN_DI_OPB2_SHJ,
// 出口回采
	EN_DI_BOARD9_END,
#endif	
	EN_DI_DI_END=EN_DI_BOARD5_END,// DI采集部分
	
/*==============================*/
// DWORD6.开出板1回采枚举
/*=============================*/
	EN_DI_BOARD6_STR=EN_DI_BOARD5_END,
	EN_DI_DO_BHTZ=EN_DI_BOARD6_STR,  // 跳闸出口回采
	EN_DI_DO_BHHZ,                   // 合闸出口回采
	EN_DI_DO_BZTTZ,                  // 备自投跳闸出口回采
	EN_DI_DO_BZTHZ,                  // 备自投合闸出口回采
	EN_DI_DO_BAK1,
	EN_DI_DO_BAK2,
	EN_DI_DO_BAK3,
	EN_DI_DO_BAK4,
	EN_DI_DO_XCBR_OPN,
	EN_DI_DO_XCBR_CLS,
	EN_DI_DO_BSCH,
	EN_DI_DO_XCBR_JBS,
	EN_DI_DO_XSWI01_JBS,
	EN_DI_DO_XSWI02_JBS,
	EN_DI_DO_XSWI03_JBS,
	EN_DI_DO_XSWI04_JBS,
	EN_DI_BOARD6_END,
/*==============================*/
//  DWORD7.开出板2回采枚举
/*=============================*/
	EN_DI_BOARD7_STR=EN_DI_BOARD6_END,
	EN_DI_DO_XSWI05_JBS=EN_DI_BOARD7_STR,
	EN_DI_DO_XSWI06_JBS,
	EN_DI_DO_XSWI07_JBS,
	EN_DI_DO_XSWI08_JBS,
	EN_DI_DO_XSWI01_OPN,
	EN_DI_DO_XSWI01_CLS,
	EN_DI_DO_XSWI02_OPN,
	EN_DI_DO_XSWI02_CLS,
	EN_DI_DO_XSWI03_OPN,
	EN_DI_DO_XSWI03_CLS,
	EN_DI_DO_XSWI04_OPN,
	EN_DI_DO_XSWI04_CLS,
	EN_DI_DO_XSWI05_OPN,
	EN_DI_DO_XSWI05_CLS,
	EN_DI_DO_XSWI06_OPN,
	EN_DI_DO_XSWI06_CLS,
	EN_DI_BOARD7_END,
/*=============================*/
//  DWORD7.开入开出板枚举--开出返校部分
/*==============================*/
	EN_DI_BOARD8_STR=EN_DI_BOARD7_END,
	EN_DI_DO_XSWI07_OPN=EN_DI_BOARD8_STR,
	EN_DI_DO_XSWI07_CLS,
	EN_DI_DO_XSWI08_OPN,
	EN_DI_DO_XSWI08_CLS,
	EN_DI_DO_YK_BAK1,
	EN_DI_DO_YK_BAK2,
	EN_DI_DO_BHBAK5,
	EN_DI_BOARD8_END,

	EN_DI_END=EN_DI_BOARD8_END
};
// 硬开入双点信号枚举
enum _DPI_NUMBER
{
	EN_DPI_STR=0,
	EN_DPI_XCBR=EN_DPI_STR,
	EN_DPI_XSWI01,
	EN_DPI_XSWI02,
	EN_DPI_XSWI03,
	EN_DPI_XSWI04,
	EN_DPI_XSWI05,
	EN_DPI_XSWI06,
	EN_DPI_XSWI07,
	EN_DPI_XSWI08,
	EN_DPI_END,
};
// GOOSE订阅信号枚举
enum _GOIN_NUMBER
{
	EN_GOIN_STR=0,
	// 单点信号
	EN_GOIN_S_STR=EN_GOIN_STR,
	EN_GOIN_RESET=EN_GOIN_S_STR,  // 远方复归
	EN_GOIN_CKTZ,                 // 测控跳闸
	EN_GOIN_CKHZ,                 // 测控合闸
	EN_GOIN_JBS_XCBR,             // 断路器解闭锁
	EN_GOIN_BZTTZ1,               // 备自投跳闸1
	EN_GOIN_BZTTZ2,               // 备自投跳闸2
	EN_GOIN_BZTHZ1,               // 备自投合闸1
	EN_GOIN_BZTHZ2,               // 备自投合闸2
	EN_GOIN_BHTZ1,                // 保护跳闸1
	EN_GOIN_BHTZ2,                // 保护跳闸2
	EN_GOIN_BHTZ3,                // 保护跳闸3
	EN_GOIN_BHTZ4,                // 保护跳闸4
	EN_GOIN_BHTZ5,                // 保护跳闸5
	EN_GOIN_BHHZ1,                // 保护重合闸1
	EN_GOIN_BHHZ2,                // 保护重合闸2
	EN_GOIN_BHHZ3,                // 保护重合闸3
	EN_GOIN_BHHZ4,                // 保护重合闸4
	EN_GOIN_BHHZ5,                // 保护重合闸5
	EN_GOIN_BSHZ1,                // 闭锁重合闸1
	EN_GOIN_BSHZ2,                // 闭锁重合闸2
	EN_GOIN_BSHZ3,                // 闭锁重合闸3
	EN_GOIN_BSHZ4,                // 闭锁重合闸4
	EN_GOIN_BSHZ5,                // 闭锁重合闸5
	EN_GOIN_BHYT1,                // 保护永跳1
	EN_GOIN_BHYT2,                // 保护永跳2
	EN_GOIN_BHYT3,                // 保护永跳3
	EN_GOIN_BHYT4,                // 保护永跳4
	EN_GOIN_BHYT5,                // 保护永跳5
	EN_GOIN_BHYT6,                // 保护永跳6
	EN_GOIN_BHYT7,                // 保护永跳7
	EN_GOIN_BHYT8,                // 保护永跳8
	EN_GOIN_BHYT9,                // 保护永跳9
	EN_GOIN_BHYT10,               // 保护永跳10
	EN_GOIN_CLS_XSWI01,
	EN_GOIN_OPN_XSWI01,
	EN_GOIN_JBS_XSWI01,
	EN_GOIN_CLS_XSWI02,
	EN_GOIN_OPN_XSWI02,
	EN_GOIN_JBS_XSWI02,
	EN_GOIN_CLS_XSWI03,
	EN_GOIN_OPN_XSWI03,
	EN_GOIN_JBS_XSWI03,
	EN_GOIN_CLS_XSWI04,
	EN_GOIN_OPN_XSWI04,
	EN_GOIN_JBS_XSWI04,
	EN_GOIN_CLS_XSWI05,
	EN_GOIN_OPN_XSWI05,
	EN_GOIN_JBS_XSWI05,
	EN_GOIN_CLS_XSWI06,
	EN_GOIN_OPN_XSWI06,
	EN_GOIN_JBS_XSWI06,
	EN_GOIN_CLS_XSWI07,
	EN_GOIN_OPN_XSWI07,
	EN_GOIN_JBS_XSWI07,
	EN_GOIN_CLS_XSWI08,
	EN_GOIN_OPN_XSWI08,
	EN_GOIN_JBS_XSWI08,
	// 备用遥控 1~2 
	EN_GOIN_BAK_01,
	EN_GOIN_BAK_02,
	// 时间管理输入 
	EN_GOIN_TIME_SYN,
	EN_GOIN_S_END,
	// 双点信号
	EN_GOIN_D_STR=EN_GOIN_S_END,
	EN_GOIN_D_END=EN_GOIN_D_STR,
	EN_GOIN_END=EN_GOIN_D_END,    // GOOSE开入结束
};
// 硬开出信号枚举
enum _DO_NUMBER
{
    EN_DO_STR = 0,
// 开出板1
    EN_DO_BOARD1_STR=EN_DO_STR,
    EN_DO_BHTZ=EN_DO_BOARD1_STR,
    EN_DO_BHHZ,
    EN_DO_BZTTZ,
    EN_DO_BZTHZ,
    EN_DO_BHBAK1,
    EN_DO_BHBAK2,
    EN_DO_BHBAK3,
    EN_DO_BHBAK4,
    EN_DO_XCBR_OPN,
    EN_DO_XCBR_CLS,
    EN_DO_BSCH,
    EN_DO_XCBR_JBS,
    EN_DO_XSWI01_JBS,
    EN_DO_XSWI02_JBS,
    EN_DO_XSWI03_JBS,
    EN_DO_XSWI04_JBS,
    EN_DO_BOARD1_END,
// 开出板2
    EN_DO_BOARD2_STR=EN_DO_BOARD1_END,
    EN_DO_XSWI05_JBS=EN_DO_BOARD2_STR,
    EN_DO_XSWI06_JBS,
    EN_DO_XSWI07_JBS,
    EN_DO_XSWI08_JBS,
    EN_DO_XSWI01_OPN,
    EN_DO_XSWI01_CLS,
    EN_DO_XSWI02_OPN,
    EN_DO_XSWI02_CLS,
    EN_DO_XSWI03_OPN,
    EN_DO_XSWI03_CLS,
    EN_DO_XSWI04_OPN,
    EN_DO_XSWI04_CLS,
    EN_DO_XSWI05_OPN,
    EN_DO_XSWI05_CLS,
    EN_DO_XSWI06_OPN,
    EN_DO_XSWI06_CLS,
    EN_DO_BOARD2_END,
// 开入开出板
    EN_DO_BOARD3_STR=EN_DO_BOARD2_END,
    EN_DO_XSWI07_OPN=EN_DO_BOARD3_STR,
    EN_DO_XSWI07_CLS,
    EN_DO_XSWI08_OPN,
    EN_DO_XSWI08_CLS,
    EN_DO_YK_BAK1,
    EN_DO_YK_BAK2,
    EN_DO_BHBAK5,
    EN_DO_BOARD3_END,
    
    EN_DO_RTN_END=EN_DO_BOARD3_END,
// 直控出口
    EN_DO_BOARD4_STR=EN_DO_BOARD3_END,
    EN_DO_ALM=EN_DO_BOARD4_STR,
    EN_DO_CHK,
    EN_DO_BOARD4_END,
    EN_DO_END=EN_DO_BOARD4_END,            // 保护出口开出通道 END
};
// GOOSE发布配置
enum _GOOUT_NUMBER
{
    EN_GOOUT_START=0,
    EN_GOOUT_CHK=EN_GOOUT_START,
    EN_GOOUT_ALM,
    EN_GOOUT_ALM_SYN,
    EN_GOOUT_ALM_KI,
    EN_GOOUT_ALM_SV,
    EN_GOOUT_ALM_GOOSE,
    EN_GOOUT_ALM_GOCB01,
    EN_GOOUT_ALM_GOCB02,
    EN_GOOUT_ALM_GOCB03,
    EN_GOOUT_ALM_GOCB04,
    EN_GOOUT_ALM_GOCB05,
    EN_GOOUT_ALM_GOCB06,
    EN_GOOUT_ALM_GOCB07,
    EN_GOOUT_ALM_GOCB08,
    EN_GOOUT_ALM_GOCB09,
    EN_GOOUT_ALM_GOCB10,
    EN_GOOUT_ALM_GOCB11,
    EN_GOOUT_ALM_GOCB12,
    EN_GOOUT_ALM_GOCB13,
    EN_GOOUT_ALM_GOCB14,
    EN_GOOUT_ALM_GOCB15,
    EN_GOOUT_ALM_GOCB16,
    EN_GOOUT_ALM_GOCB17,
    EN_GOOUT_ALM_GOCB18,
    EN_GOOUT_ALM_GOCB19,
    EN_GOOUT_ALM_GOCB20,
    EN_GOOUT_ALM_GOCB21,
    EN_GOOUT_ALM_GOCB22,
    EN_GOOUT_ALM_GOCB23,
    EN_GOOUT_ALM_GOCB24,
    EN_GOOUT_TEST_ERR,
    EN_GOOUT_ALM_BSCH,   // 闭锁重合闸 
    EN_GOOUT_FLAG_TJF,   // 电缆直跳信号 TJF
    EN_GOOUT_FLAG_KKJ,   // KKJ 合后 
    EN_GOOUT_FLAG_STJ,   // STJ 信号 
    EN_GOOUT_FLAG_SHJ,   // SHJ 信号 
    EN_GOOUT_ALM_KHDX,   // 控制回路断线
    EN_GOOUT_ALM_XSWI,   // 刀闸位置异常 
    EN_GOOUT_ALM_VCHG,   // 选择把手状态异常 
    EN_GOOUT_ALM_PTACT,  // PT 切换同时动作 
    EN_GOOUT_ALM_PTRET,  // PT 切换同时返回 
    EN_GOOUT_ALM_LNK,    // SV级联数据异常
    EN_GOOUT_ALM_OPBP1,  // 操作电源掉电监视信号
    EN_GOOUT_ALM_SGZ,    // 事故总信号 
    EN_GOOUT_ALM_SXBYZ,  // 三相不一致 
    EN_GOOUT_IN_BHTZ,    // 收到保护跳闸命令 
    EN_GOOUT_IN_BHYT,    // 收到保护永跳命令 
    EN_GOOUT_IN_BHHZ,    // 收到保护三合命令 
    EN_GOOUT_IN_CKTZ,    // 收到测控跳闸命令 
    EN_GOOUT_IN_CKHZ,    // 收到测控合闸命令 
    EN_GOOUT_IN_BZTTZ,   // 收到备自投跳闸命令 
    EN_GOOUT_IN_BZTHZ,   // 收到备自投合闸命令 
    EN_GOOUT_DO_BHTZ,    // 跳闸出口回采 
    EN_GOOUT_DO_BHHZ,    // 合闸出口回采 
    EN_GOOUT_DO_BZTTZ,   // 备自投跳闸出口回采 
    EN_GOOUT_DO_BZTHZ,   // 备自投合闸出口回采 
    EN_GOOUT_V_I,        // 压切取Ⅰ母 
    EN_GOOUT_V_II,       // 压切取Ⅱ母 
    EN_GOOUT_SV_A,       // A 套数据正常 
    EN_GOOUT_SV_B,       // B 套数据正常 
    EN_GOOUT_LNK_A,      // 级联取 A 套 
    EN_GOOUT_LNK_B,      // 级联取 B 套 
    EN_GOOUT_PARACHG,
    EN_GOOUT_TIME_RECV,
    EN_GOOUT_TIME_SEND,
    EN_GOOUT_TIME_SINGLE,
    EN_GOOUT_TIME_SERVIC,
    EN_GOOUT_TIME_CHKERR,
    EN_GOOUT_END
};
//指示灯枚举
enum _LED_NUMBER
{
    EN_LED_STR=0,
// 第1列指示灯
    EN_LED_RUN=EN_LED_STR,
    EN_LED_ALM,
    EN_LED_TEST,
    EN_LED_GO_ERR,
    EN_LED_TEST_ERR,
    EN_LED_SYN_ERR,
    EN_LED_SAM_ERR,
    EN_LED_KHDX,
// 第2列指示灯
    EN_LED_BHTZ,
    EN_LED_BHHZ,
    EN_LED_ZTF,
    EN_LED_BAK21,
    EN_LED_BAK22,
    EN_LED_BAK23,
    EN_LED_BAK24,
    EN_LED_HWJ,
// 第3列指示灯
    EN_LED_WAR_LNK,    // 级联异常
    EN_LED_VCHG_I,     // 压切取Ⅰ母
    EN_LED_VCHG_II,    // 压切取Ⅱ母
    EN_LED_LNK_A,      // 级联取A套
    EN_LED_LNK_B,      // 级联取B套
    EN_LED_BAK31,
    EN_LED_BAK32,
    EN_LED_TWJ,
// 第4列指示灯
    EN_LED_XSWI01_CLS,    // 刀闸1合位
    EN_LED_XSWI02_CLS,    // 刀闸2合位
    EN_LED_XSWI03_CLS,    // 刀闸3合位
    EN_LED_XSWI04_CLS,    // 刀闸4合位
    EN_LED_XSWI05_CLS,    // 刀闸5合位
    EN_LED_XSWI06_CLS,    // 刀闸6合位
    EN_LED_XSWI07_CLS,    // 刀闸7合位
    EN_LED_XSWI08_CLS,    // 刀闸8合位
// 第5列指示灯
    EN_LED_XSWI01_OPN,    // 刀闸1分位
    EN_LED_XSWI02_OPN,    // 刀闸2分位
    EN_LED_XSWI03_OPN,    // 刀闸3分位
    EN_LED_XSWI04_OPN,    // 刀闸4分位
    EN_LED_XSWI05_OPN,    // 刀闸5分位
    EN_LED_XSWI06_OPN,    // 刀闸6分位
    EN_LED_XSWI07_OPN,    // 刀闸7分位
    EN_LED_XSWI08_OPN,    // 刀闸8分位
    EN_LED_END
};
/*================================================================================*/
//IO相关板卡枚举
/*================================================================================*/
enum _BOARD_IO_TYPE_
{
    EN_BOARD_DO1=0,
    EN_BOARD_DO2,
    EN_BOARD_DO3,
    EN_BOARD_DIO_DO=EN_BOARD_DO3,      // DIO板卡标识
    EN_BOARD_DO_RTN_END,               // 有返校的开出信号
    EN_BOARD_DO4=EN_BOARD_DO_RTN_END,  
    EN_BOARD_DO_END,
    
    EN_BOARD_DI1=0,
    EN_BOARD_DI2,
    EN_BOARD_DI3,
    EN_BOARD_DI4,
    EN_BOARD_DIO_DI=EN_BOARD_DI4,     // DIO板卡标识
    EN_BOARD_DI5,
    EN_BOARD_OPB=EN_BOARD_DI5,        // OPB板卡标识
    EN_BOARD_DI_DI_END,               // DI非返校部分
    EN_BOARD_DI_DO_STR=EN_BOARD_DI_DI_END,// DI非返校部分
    EN_BOARD_DI6=EN_BOARD_DI_DO_STR+EN_BOARD_DO1,
    EN_BOARD_DI7=EN_BOARD_DI_DO_STR+EN_BOARD_DO2,
    EN_BOARD_DI8=EN_BOARD_DI_DO_STR+EN_BOARD_DO3,
    EN_BOARD_DI_DO_END=EN_BOARD_DI_DO_STR+EN_BOARD_DO_RTN_END,
    EN_BOARD_DI_END=EN_BOARD_DI_DO_END,
};
// GOOSE信号无效原因
enum _TYPE_GOIN_INVAILD_
{
	EN_INVAILD_STR=0,              // 无效原因
	EN_INVAILD_NO=EN_INVAILD_STR,  // 成功
	EN_INVAILD_TEST,               // 失败:检修不一致
	EN_INVAILD_LINK,               // 失败:断链
	EN_INVAILD_Q,                  // 失败:品质无效
	EN_INVAILD_DATA,               // 失败:数据异常
	EN_INVAILD_END,                // 
};

/*================================================================================*/
// 常量表结构体
/*================================================================================*/
// 硬开入单点开入常量表结构体
typedef struct
{
	WORD            wIndex;                         // 硬开入枚举号
	WORD            wCfg;                           // 硬开入其他功能配置
	INT8S           byName[CN_LEN_NAME];            // 硬开入名称
	INT8S           byPinName[CN_LEN_NAME];         // 硬开入短地址	
} tagDiTab;
// 硬开入双点合成常量表结构体
typedef struct
{
	WORD            wIndex;                         // 模拟量枚举号
	WORD            wSrcType;                       // 关联信号源
	WORD            wSrcOpn;                        // 关联分位信号
	WORD            wSrcCls;                        // 关联合位信号
	WORD            wParaIndex;                     // 关联参数1
	WORD            wCfg;                           // 其他属性配置
	INT8S           byName[CN_LEN_NAME];            // 模拟量名称
	INT8S           byPinName[CN_LEN_NAME];         // 模拟量短地址
}tagDpiTab;
// GOOSE开入遥信常量表结构体
typedef struct
{
	WORD            wIndex;                         // GOOSE开入枚举号
	WORD            wChnType;                       // 信号类型
	WORD            wParaIndex;                     // 关联参数
	WORD            wCfg;                           // GOOSE开入其他功能配置
	INT8S           byName[CN_LEN_NAME];            // GOOSE开入名称
	INT8S           byPinName[CN_LEN_NAME];         // GOOSE开入短地址	
} tagGoInTab;
// 开出量信息常量表数据结构
typedef struct
{
	WORD            wIndex;                         // 开出量枚举
	WORD            wSrcType;                       // 关联信号源
	WORD            wSrcIndex;                      // 关联信号源枚举
	WORD            wParaIndex;                     // 关联参数1
	WORD            wRtnIndex;                      // 关联返校遥信
	WORD            wCfg;                           // 开出其他功能配置
	INT8S           byName[CN_LEN_NAME];            // 开出量名称
	INT8S           byPinName[CN_LEN_NAME];         // 开出量短地址
} tagDoTab;
// GOOSE发布信息常量表数据结构
typedef struct
{
	WORD            wIndex;                         // GOOSE开出量枚举
	WORD            wChnType;                       // 数据类型
	WORD            wSrcType;                       // 关联信号源
	WORD            wSrcIndex;                      // 关联信号源枚举
	WORD            wParaIndex;                     // 关联参数1
	WORD            wCfg;                           // GOOSE开出其他功能配置 NULL:本机品质\本机时标
	INT8S           byName[CN_LEN_NAME];            // GOOSE开出量名称
	INT8S           byPinName[CN_LEN_NAME];         // GOOSE开出量短地址
} tagGoOutTab;
// 指示灯息常量表数据结构
typedef struct
{
	WORD            wIndex;                         // 指示灯枚举
	WORD            wSrcType;                       // 关联信号源
	WORD            wSrcIndex;                      // 关联信号源枚举
	WORD            wParaIndex;                     // 关联参数
	BYTE            byCol;                          // 行位置
	BYTE            byRow;                          // 列位置
	BYTE            bycolor;                        // 指示灯颜色
	BOOL            bHld;                           // 指示灯保持功能
	INT8S           byName[CN_LEN_NAME];            // 指示灯名称
	INT8S           byPinName[CN_LEN_NAME];         // 指示灯短地址
} tagLedTab;

// 板卡设置常量表结构体
typedef struct
{
	WORD            wIndex;                         // 板卡枚举号
	WORD            wIndexStr;                      // 关联信号源起始枚举
	WORD            wIndexEnd;                      // 关联信号源结束枚举
	WORD            wSrcIndexNum;                   // 关联信号个数
	WORD            wPowBitNum;                     // 光耦失电信号位置
	WORD            wParaIndex;                     // 光耦失电投退参数
	WORD            wAddrBoard;                     // 板卡地址
	WORD            wAddrFrame;                     // 帧地址
	INT8S           byName[CN_LEN_NAME];            // 板卡名称
	INT8S           byPinName[CN_LEN_NAME];         // 板卡短地址
} tagBoardIoTab;

/*================================================================================*/
// 宏定义
/*================================================================================*/
#define CN_NUM_DI_DI         (EN_DI_DI_END)
#define CN_NUM_DI            (EN_DI_END)
#define CN_NUM_GOIN_S        (EN_GOIN_S_END-EN_GOIN_S_STR)     // 单点信号
#define CN_NUM_GOIN_D        (EN_GOIN_D_END-EN_GOIN_D_STR)     // 双点信号
#define CN_NUM_GOIN          (EN_GOIN_END)
#define CN_NUM_DPI           (EN_DPI_END)
#define CN_NUM_DO_RTN        (EN_DO_RTN_END)
#define CN_NUM_DO            (EN_DO_END)
#define CN_NUM_GOOUT         (EN_GOOUT_END)
#define CN_NUM_LED           (EN_LED_END)
// 板卡个数
#define CN_NUM_BOARD_DI_DI   (EN_BOARD_DI_DI_END)
#define CN_NUM_BOARD_DI_DO   (EN_BOARD_DI_DO_STR)
#define CN_NUM_BOARD_DI      (EN_BOARD_DI_END)
#define CN_NUM_BOARD_DO_RTN  (EN_BOARD_DO_RTN_END)
#define CN_NUM_BOARD_DO      (EN_BOARD_DO_END)
// 双点位置
#define CN_DPI_OPN        (0x1)                               // 分位
#define CN_DPI_CLS        (0x2)                               // 合位
#define CN_DPI_STP        (0x0)                               // 停役
#define CN_DPI_CHK        (0x3)                               // 异常

// 功能配置
#define CN_DI_HLD_CPU        (1)                               // 0--FPGA防抖,1--CPU防抖
// GOOSE控制块最大个数
#define CN_NUM_GOCB_SUB       (12)
#define CN_NUM_GOCB_PUB       (8)
// GOOSE品质(经过向右平移)
//#define CN_GOIN_St          (DB0+DB1)                       // bit0~bit1 状态信息 
#define CN_GOIN_Invalid       (DB0+DB1)                       // bit2~bit3 品质无效
#define CN_GOIN_Test          (DB2)                           // bit4 检修状态(订阅Q,取Q中检修;未订阅Q,取控制块检修):0--未检修 1--检修
#define CN_GOIN_Link          (DB3)                           // bit5 链路状态:0--未断链 1--断链 
#define CN_GOIN_TimeToLive0   (DB4)                           // bit6 TimeToLive是否为0标志:0--TimeToLive不为0 1--TimeToLive为0 
#define CN_GOIN_DataErr       (DB5)                           // bit7 数据异常
#define CN_GOIN_Bak08         (DB6)                           // bit8 备用
#define CN_GOIN_NoSub         (DB7)                           // bit9 未订阅
#define CN_GOIN_Bak10         (DB8)                           // bit10 备用
#define CN_GOIN_Bak11         (DB9)                           // bit11 备用
#define CN_GOIN_Bak12         (DB10)                          // bit12 备用
#define CN_GOIN_Bak13         (DB11)                          // bit13 备用
#define CN_GOIN_Bak14         (DB12)                          // bit14 备用
#define CN_GOIN_Bak15         (DB13)                          // bit15 备用

// GOOSE控制块状态字
#define CN_GOCB_NO            (0xff)                          // bit0~bit7  控制块序号
#define CN_GOCB_NetPort       (0xff00)                        // bit8~bit15 网络端口
#define CN_GOCB_LinkErr1      (DB16)                          // bit16 断链判断。1：断链；0：正常。
#define CN_GOCB_APPIDErr      (DB17)                          // bit17 APPID参数不匹配。1：不匹配；0：正常。
#define CN_GOCB_GoCbErr       (DB18)                          // bit18 GoCB参数不匹配。1：不匹配；0：正常。
#define CN_GOCB_DateSetErr    (DB19)                          // bit19 DatSet参数不匹配。1：不匹配；0：正常。
#define CN_GOCB_GoIDErr       (DB20)                          // bit20 GoID参数不匹配。1：不匹配；0：正常。
#define CN_GOCB_ConfRevErr    (DB21)                          // bit21 ConfRev参数不匹配。1：不匹配；0：正常。
#define CN_GOCB_DataNumErr    (DB22)                          // bit22 DataNum参数不匹配。1：不匹配；0：正常。
#define CN_GOCB_DataTypeErr   (DB23)                          // bit23 DataType参数不匹配。1：不匹配；0：正常。
#define CN_GOCB_DataChangeErr (DB24)                          // bit24 DataChangeErr。1：异常；0：正常,暂不考虑！！！！
#define CN_GOCB_Test          (DB25)                          // bit25 检修位。1：检修 0：非检修
#define CN_GOCB_Ndscom        (DB26)                          // bit26 Ndscom值
#define CN_GOCB_FrameErr      (DB27)                          // bit27 平台提供--帧通信异常或帧类型异常
#define CN_GOCB_Storm         (DB28)                          // bit28 网络风暴标识,20ms内接收正常帧超22帧即判为风暴
#define CN_GOCB_LinkErr2      (DB29)                          // bit29 断链状态 由bit16和bit30合成，按位或
#define CN_GOCB_TimeToLive0   (DB30)                          // bit30 TimeToLive是否为0, 0：否 1:是
#define CN_GOCB_Ena           (DB31)                          // bit31 控制块使能,1：使能 0：未使能

#define CN_GOCB_LinkErr      (CN_GOCB_LinkErr1+CN_GOCB_LinkErr2)                          // 断链
#define CN_GOCB_DataErr      (CN_GOCB_APPIDErr+CN_GOCB_GoCbErr+CN_GOCB_DateSetErr+CN_GOCB_GoIDErr+CN_GOCB_ConfRevErr+ \
        CN_GOCB_DataNumErr+CN_GOCB_DataTypeErr+CN_GOCB_FrameErr)    // 数据异常

#define CN_GOCB_DataAlm      (CN_GOCB_LinkErr+CN_GOCB_DataErr+CN_GOCB_TimeToLive0)

#define CN_GOCFG_CfgErr     (DB0)                             // bit0 平台提供--配置异常
#define CN_GOCFG_ParseErr   (DB1)                             // bit1 平台提供--解析异常。
#define CN_GOCFG_DataErr    (CN_GOCFG_CfgErr+CN_GOCFG_ParseErr)
// 出口板自检状态字
#define CN_DO_CHK_CHN1       (DB0)                          // bit0 通道1中断(CPU1->出口板),Do板5S收不到数据置位,收到数据200ms返回
#define CN_DO_CHK_CHN2       (DB1)                          // bit1 通道2中断(CPU2->出口板，母线采执不使用)
#define CN_DO_CHK_FPOW       (DB2)                          // bit2 快速出口30V电压长期供电，出口板单片机扫描30V供电状态，无30kV控制且供电状态存在超过5S会置位,可自动返回。
#define CN_DO_CHK_PARA       (DB3)                          // bit3 出口板参数错,出口板单片机集成SRAM,有一点概率出现bit翻转,单片机存储3份参数，周期比对，三份均不一致，置位。
#if(CN_HARDWARE_DO==CN_HARDWARE_DO_V1)
#define CN_DO_CHK_POW24      (0)
#define CN_DO_CHK_POW30      (0)
#else
#define CN_DO_CHK_POW24      (DB4)                          // bit4 出口板24V电压断,50ms更新一次。
#define CN_DO_CHK_POW30      (DB5)                          // bit5 出口板30V电压断,3min更新一次。
#endif
/*================================================================================*/
// 全局常量表声明
/*================================================================================*/
extern const tagDiTab     g_tDiTab[];
extern const DWORD        g_NUM_DI;
extern const tagDpiTab    g_tDpiTab[];
extern const DWORD        g_NUM_DPI;
extern const tagGoInTab   g_tGoInTab[];
extern const DWORD        g_NUM_GOIN;
extern const tagDoTab     g_tDoTab[];
extern const DWORD        g_NUM_DO;
extern const tagGoOutTab  g_tGoOutTab[];
extern const DWORD        g_NUM_GOOUT;
extern const tagLedTab    g_tLedTab[];
extern const DWORD        g_NUM_LED;
extern const tagBoardIoTab    g_tBoardDITab[];
extern const DWORD            g_NUM_BOARD_DI;
extern const tagBoardIoTab    g_tBoardDOTab[];
extern const DWORD            g_NUM_BOARD_DO;

/*================================================================================*/
#endif  /* _CONST_IO_H_ */
