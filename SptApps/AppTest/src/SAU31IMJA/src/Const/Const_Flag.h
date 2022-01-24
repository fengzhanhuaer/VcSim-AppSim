#ifndef _CONST_FLAG_H_
#define _CONST_FLAG_H_

#include "IES_IMtypes.h"
/*================================================================================*/
// 信号枚举
/*================================================================================*/
enum _FLAG_NUMBER
{
    EN_FLAG_STR= 0,
    // 上电标志
    EN_FLAG_INIT=EN_FLAG_STR,
    //  复归标志
    EN_FLAG_RESET_DI,
    EN_FLAG_RESET_GOIN,
    EN_FLAG_RESET_DBG,
	EN_FLAG_RESET_COM,
    EN_FLAG_RESET,

    EN_FLAG_ALM_COM,
    EN_FLAG_CHK_COM,
    EN_FLAG_DBG_COM,

    EN_FLAG_ALM,
    EN_FLAG_CHK,
    EN_FLAG_DBG,
    EN_FLAG_DO_ALM,
    EN_FLAG_DO_CHK,
    EN_FLAG_LED_RUN,
    EN_FLAG_LED_ALM,
    EN_FLAG_PARACHG,
    EN_FLAG_GOIN_BHBC,
    EN_FLAG_DI_KKJ,
    EN_FLAG_DI_STJ,
    EN_FLAG_DI_SHJ,
    EN_FLAG_BHTZ_DO,
/*****保护跳合闸保持指示灯合并--STR*******/
    EN_FLAG_DI_TJF,
    EN_FLAG_BHTZ,
    EN_FLAG_BHHZ,
/*****保护跳合闸保持指示灯合并--END*******/
    EN_FLAG_DO_BHBAK1,
    EN_FLAG_DO_BHBAK2,
    EN_FLAG_DO_BHBAK3,
    EN_FLAG_DO_BHBAK4,
    EN_FLAG_DO_BHBAK5_0,
//    EN_FLAG_DO_BHBAK5_1,
    
    EN_FLAG_LED_BAK21,
    EN_FLAG_LED_BAK22,
    EN_FLAG_LED_BAK23,
    EN_FLAG_LED_BAK24,
    EN_FLAG_LED_BAK31,
    EN_FLAG_LED_BAK32,
//  功能投入
    EN_FLAG_LNK_ENA,
    EN_FLAG_V_ENA,
    EN_FLAG_V_NULL,
    EN_FLAG_V_BC_INIT,
    EN_FLAG_V_BC,
    EN_FLAG_V_I,
    EN_FLAG_V_II,
    EN_FLAG_SV_A,
    EN_FLAG_SV_B,
    EN_FLAG_LNK_BC,
    EN_FLAG_LNK_A,
    EN_FLAG_LNK_B,
    EN_FLAG_END
};
enum _INTER_NUMBER
{
// 增加内部标志部分,仅供状态存储,不对外通信
    EN_INTER_STR= 0,
    EN_INTER_SVSUB_CFG=EN_INTER_STR, // SV订阅配置异常
    EN_INTER_SVSUB_A_CHK,            // A套SV订阅异常
    EN_INTER_SVSUB_B_CHK,            // B套SV订阅异常
    EN_INTER_SVSUB_NOPUB,            // SV无订阅
    EN_INTER_SVSUB_PORT,             // SV订阅端口配置错
    EN_INTER_SVSUB_NUMERR,           // SV订阅控制块个数越限
    EN_INTER_SVSUB_PARAERR,          // SV订阅控制块解析异常
    EN_INTER_SVSUB_ADRERR,           // SV订阅控制块短地址错
    EN_INTER_SVSUB_CFGERR,           // SV订阅控制块配置错
    EN_INTER_SVSUB_1M_1LINKA,        // 单母线仅A套订阅
    EN_INTER_SVSUB_1M_1LINKB,        // 单母线仅B套订阅
    EN_INTER_SVSUB_1M_2LINK,         // 单母线双套订阅
    EN_INTER_SVSUB_2M_1LINKA,        // 双母线仅A套订阅
    EN_INTER_SVSUB_2M_1LINKB,        // 双母线仅B套订阅
    EN_INTER_SVSUB_2M_2LINK,         // 双母线双套订阅
    EN_INTER_SVSUB_A_DIS,            // A套I/II母订阅不一致
    EN_INTER_SVSUB_A_MULT,           // A套I/II母跨控制块订阅
    EN_INTER_SVSUB_B_DIS,            // B套I/II母订阅不一致
    EN_INTER_SVSUB_B_MULT,           // B套I/II母跨控制块订阅
    EN_INTER_SVSUB_1M_DIS,           // I母A/B套订阅不一致
    EN_INTER_SVSUB_2M_DIS,           // II母A/B套订阅不一致
    EN_INTER_SVSUB_A1_VALID,         // A套I母电压订阅配置有效
    EN_INTER_SVSUB_A1_CFG,           // A套I母电压有订阅
    EN_INTER_SVSUB_A1_LOSE,          // A套I母电压未全订阅
    EN_INTER_SVSUB_A1_MULT,          // A套I母电压跨控制块订阅
    EN_INTER_SVSUB_A2_VALID,         // A套II母电压订阅配置有效
    EN_INTER_SVSUB_A2_CFG,           // A套II母电压有订阅
    EN_INTER_SVSUB_A2_LOSE,          // A套II母电压未全订阅
    EN_INTER_SVSUB_A2_MULT,          // A套II母电压跨控制块订阅
    EN_INTER_SVSUB_B1_VALID,         // B套I母电压订阅配置有效
    EN_INTER_SVSUB_B1_CFG,           // B套I母电压有订阅
    EN_INTER_SVSUB_B1_LOSE,          // B套I母电压未全订阅
    EN_INTER_SVSUB_B1_MULT,          // B套I母电压跨控制块订阅
    EN_INTER_SVSUB_B2_VALID,         // B套II母电压订阅配置有效
    EN_INTER_SVSUB_B2_CFG,           // B套II母电压有订阅
    EN_INTER_SVSUB_B2_LOSE,          // B套II母电压未全订阅
    EN_INTER_SVSUB_B2_MULT,          // B套II母电压跨控制块订阅
    
    EN_INTER_SVPUB_CFG,              // SV发布配置异常
    EN_INTER_SVPUB_PORT,             // SV发布端口配置错
    EN_INTER_SVPUB_NUMERR,           // SV订阅控制块个数越限
    EN_INTER_SVPUB_PARAERR,          // SV订阅控制块解析异常
    EN_INTER_SVPUB_ADRERR,           // SV订阅控制块短地址错
    EN_INTER_SVPUB_CFGERR,           // SV订阅控制块配置错
    EN_INTER_SVPUB_CHN_NUM,          // 挑数表通道数越限
    EN_INTER_SVPUB_CHN_NO,           // 挑数表通道号越限
    EN_INTER_SVPUB_DLY,              // 发布缺少通道延时
    EN_INTER_SVPUB_SUB,              // 发布有级联通道
    EN_INTER_SVPUB_STD,              // 标准SV(母线电压级联)发布
    EN_INTER_SVPUB_ANA,              // 标准SV(母线电压直采)发布
    EN_INTER_SVPUB_M,                // 标准SV(母线板无电压配置)发布
    EN_INTER_SVPUB_CHK,              // 非标准SV发布
    
    EN_INTER_GOSUB_CFG,              // GOOSE订阅异常
    EN_INTER_GOSUB_PORT,             // GOOSE订阅端口配置错
    EN_INTER_GOSUB_NUMERR,           // GOOSE订阅控制块个数越限
    EN_INTER_GOSUB_PARAERR,          // GOOSE订阅控制块解析异常
    EN_INTER_GOSUB_ADRERR,           // GOOSE订阅控制块短地址错
    EN_INTER_GOSUB_CFGERR,           // GOOSE订阅控制块配置错
    EN_INTER_GOSUB_Dif,              // GOOSE订阅不一致
    EN_INTER_GOSUB_GOCB,             // GOOSE订阅控制块错误
    EN_INTER_GOSUB_V,                // GOOSE数据有订阅
    EN_INTER_GOSUB_T,                // GOOSE时标有订阅
    EN_INTER_GOSUB_Q,                // GOOSE品质有订阅
    
    EN_INTER_GOPUB_CFG,              // GOOSE发布异常
    EN_INTER_GOPUB_PORT,             // GOOSE发布端口配置错
    EN_INTER_GOPUB_NUMERR,           // GOOSE订阅控制块个数越限
    EN_INTER_GOPUB_PARAERR,          // GOOSE订阅控制块解析异常
    EN_INTER_GOPUB_ADRERR,           // GOOSE订阅控制块短地址错
    EN_INTER_GOPUB_CFGERR,           // GOOSE订阅控制块配置错
    EN_INTER_GOPUB_DI_LOSE,          // 单点硬遥信未全发布
    EN_INTER_GOPUB_DI_T,             // 单点硬遥信时标未全发布
    EN_INTER_GOPUB_DI_Q,             // 单点硬遥信有品质发布
    EN_INTER_GOPUB_DI_Dif,           // 单点硬遥信发布不一致
    EN_INTER_GOPUB_DPI_LOSE,         // 双点硬遥信未全发布
    EN_INTER_GOPUB_DPI_T,            // 双点硬遥信时标未全发布
    EN_INTER_GOPUB_DPI_Q,            // 双点硬遥信有品质发布
    EN_INTER_GOPUB_DPI_Dif,          // 双点硬遥信发布不一致
    EN_INTER_GOPUB_OUT_LOSE,         // 虚遥信未全发布
    EN_INTER_GOPUB_OUT_Q,            // 虚遥信有品质发布
    EN_INTER_GOPUB_OUT_Dif,          // 虚遥信发布不一致
    EN_INTER_GOPUB_DC_LOSE,          // 直流未全发布
    EN_INTER_GOPUB_DC_Q,             // 直流有品质发布
    EN_INTER_GOPUB_DC_Dif,           // 直流发布不一致
  
    EN_INTER_RUN_SV_BS,              // SV闭锁
	EN_INTER_RUN_SV_ENA,             // SV发布使能
	EN_INTER_RUN_SV_ENA_ELSE,        // SV发布使能过
    EN_INTER_RUN_GO_BS,              // GOOSE闭锁
    EN_INTER_RUN_GO_ENA,              // GOOSE发布使能
    EN_INTER_RUN_GO_ENA_ELSE,         // GOOSE发布使能过

	//	操作标志(仅在界面修改,中断中不进行写操作)
	
    EN_INTER_OPT_ANA,                 // 积分幅值查看
    EN_INTER_OPT_ANA_J,               // 基波查看
    EN_INTER_OPT_ANA_HUM,             // 谐波查看
    EN_INTER_OPT_ANA_FR,              // 频率查看
    EN_INTER_POW_LOS,                 // 装置掉电标志(瞬时)
    EN_INTER_POW_LOS_RLY,             // 装置掉电标志(去颤后)
    EN_INTER_POW_LOS_EVT,             // 装置掉电事项

    EN_INTER_CPU2_CTRL,               // CPU接管标志
    EN_INTER_CPU2_CTRL_ZK,            // 非接管状态ZK标志开放
    EN_INTER_CPU2_CTRL_DBG,
    EN_INTER_LCD_VIR,
    EN_INTER_END
};

/*================================================================================*/
// 常量表结构体
/*================================================================================*/
// 计算源枚举最大个数
#define CN_FLAG_SNUM  (32)   //
typedef struct
{
	WORD			wIndex; 					// 标志枚举号
	WORD			wSrcType;					// 数据源类型
	WORD			wSrcIndex[CN_FLAG_SNUM];	// 数据源枚举
	WORD			wCalCfg;					// 计算配置
	WORD			wPara;						// 参数枚举
	WORD			wCfg;						// 标志配置
	INT8S			byName[CN_LEN_NAME];		// 标志名称名称
	INT8S			byPinName[CN_LEN_NAME];		// 标志短地址
} tagFlagTab;

typedef struct
{
	WORD			wIndex; 					// 标志枚举号
	WORD			wType; 						// 数据类型
	INT8S			byName[CN_LEN_NAME];		// 标志名称名称
	INT8S			byPinName[CN_LEN_NAME];		// 标志短地址
} tagInterTab;

/*================================================================================*/
// 宏定义
/*================================================================================*/
#define CN_NUM_FLAG         (EN_FLAG_END)
#define CN_NUM_INTER        (EN_INTER_END)
// 标志合成方式
#define CN_FLAG_NULL (0)     // 无运算
#define CN_FLAG_OR   (DB0)   // 或运算
#define CN_FLAG_NO   (DB1)   // 非运算
#define CN_FLAG_BC   (DB2)   // 保持运算
#define CN_FLAG_MAT  (DB3)   // 跳闸矩阵
#define CN_FLAG_EQL  (DB4)   // 等于
#define CN_FLAG_WID  (DB5)   // 展宽

/*================================================================================*/
// 常量表声明
/*================================================================================*/
extern const tagFlagTab   g_tFlagTab[];
extern const DWORD        g_NUM_FLAG;
extern const tagInterTab  g_tInterTab[];
extern const DWORD        g_NUM_INTER;
#endif/*_CONST_FLAG_H_*/

