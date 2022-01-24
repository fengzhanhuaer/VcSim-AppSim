#ifndef _CONST_PARA_H_
#define _CONST_PARA_H_

#include "IES_IMtypes.h"
// 直流参数组
enum _GROUP_PARA_DC
{
	EN_GROUP_DC_STR= 0,
	EN_GROUP_DC_IN   =EN_GROUP_DC_STR,        // DC输入方式
	EN_GROUP_DC_OUT ,        // DC输出模式 
	EN_GROUP_DC_MIN ,        // DC输出最小值
	EN_GROUP_DC_MAX ,        // DC输出最大值
	EN_GROUP_DC_OFST,        // DC输出最偏移量
	EN_GROUP_DC_END,
};
//
/*================================================================================*/
// 参数信号枚举
/*================================================================================*/
enum _PARA_NUMBER
{
// 防抖时间在最前位置
	EN_PARA_STR       = 0,
	EN_PARA_DI_STR    = EN_PARA_STR,
	EN_PARA_ENA_YXPOW1= EN_DI_END,
	EN_PARA_ENA_YXPOW2,
	EN_PARA_ENA_YXPOW3,
	EN_PARA_ENA_YXPOW4,
	
	EN_PARA_IO_BAK01,
	EN_PARA_IO_BAK02,
	EN_PARA_IO_BAK03,
	EN_PARA_IO_BAK04,
	EN_PARA_IO_BAK05,
	EN_PARA_IO_BAK06,
	EN_PARA_IO_BAK07,
	EN_PARA_IO_BAK08,
	EN_PARA_IO_BAK09,
	EN_PARA_IO_BAK10,
	EN_PARA_DI_END,
// 增加备用参数
// 直流数据
	EN_PARA_DC_STR  =EN_PARA_DI_END,
	EN_PARA_DC1_STR =EN_PARA_DC_STR,                         // DC1起始
	EN_PARA_DC1_IN  =EN_PARA_DC1_STR,                        // DC1输入模式
	EN_PARA_DC1_OUT =EN_PARA_DC1_STR+EN_GROUP_DC_OUT,        // DC1输出模式
	EN_PARA_DC1_MIN =EN_PARA_DC1_STR+EN_GROUP_DC_MIN,        // DC1输出最小值
	EN_PARA_DC1_MAX =EN_PARA_DC1_STR+EN_GROUP_DC_MAX,        // DC1输出最大值
	EN_PARA_DC1_OFST=EN_PARA_DC1_STR+EN_GROUP_DC_OFST,       // DC1输出最偏移量

	EN_PARA_DC2_STR =EN_PARA_DC1_STR+EN_GROUP_DC_END,        // DC2起始 
	EN_PARA_DC2_IN  =EN_PARA_DC2_STR,                        // DC2输入模式
	EN_PARA_DC2_OUT =EN_PARA_DC2_STR+EN_GROUP_DC_OUT,        // DC2输出模式
	EN_PARA_DC2_MIN =EN_PARA_DC2_STR+EN_GROUP_DC_MIN,        // DC2输出最小值
	EN_PARA_DC2_MAX =EN_PARA_DC2_STR+EN_GROUP_DC_MAX,        // DC2输出最大值
	EN_PARA_DC2_OFST=EN_PARA_DC2_STR+EN_GROUP_DC_OFST,       // DC2输出最偏移量
#if(!CN_FUN_DBUG1)
	EN_PARA_DC3_STR =EN_PARA_DC2_STR+EN_GROUP_DC_END,        // DC3起始 
	EN_PARA_DC3_IN  =EN_PARA_DC3_STR,                        // DC3输入模式
	EN_PARA_DC3_OUT =EN_PARA_DC3_STR+EN_GROUP_DC_OUT,        // DC3输出模式
	EN_PARA_DC3_MIN =EN_PARA_DC3_STR+EN_GROUP_DC_MIN,        // DC3输出最小值
	EN_PARA_DC3_MAX =EN_PARA_DC3_STR+EN_GROUP_DC_MAX,        // DC3输出最大值
	EN_PARA_DC3_OFST=EN_PARA_DC3_STR+EN_GROUP_DC_OFST,       // DC3输出最偏移量

	EN_PARA_DC4_STR =EN_PARA_DC3_STR+EN_GROUP_DC_END,        // DC4起始 
	EN_PARA_DC4_IN  =EN_PARA_DC4_STR,                        // DC4输入模式
	EN_PARA_DC4_OUT =EN_PARA_DC4_STR+EN_GROUP_DC_OUT,        // DC4输出模式
	EN_PARA_DC4_MIN =EN_PARA_DC4_STR+EN_GROUP_DC_MIN,        // DC4输出最小值
	EN_PARA_DC4_MAX =EN_PARA_DC4_STR+EN_GROUP_DC_MAX,        // DC4输出最大值
	EN_PARA_DC4_OFST=EN_PARA_DC4_STR+EN_GROUP_DC_OFST,       // DC4输出最偏移量

	EN_PARA_DC5_STR =EN_PARA_DC4_STR+EN_GROUP_DC_END,        // DC5起始 
	EN_PARA_DC5_IN  =EN_PARA_DC5_STR,                        // DC5输入模式
	EN_PARA_DC5_OUT =EN_PARA_DC5_STR+EN_GROUP_DC_OUT,        // DC5输出模式
	EN_PARA_DC5_MIN =EN_PARA_DC5_STR+EN_GROUP_DC_MIN,        // DC5输出最小值
	EN_PARA_DC5_MAX =EN_PARA_DC5_STR+EN_GROUP_DC_MAX,        // DC5输出最大值
	EN_PARA_DC5_OFST=EN_PARA_DC5_STR+EN_GROUP_DC_OFST,       // DC5输出最偏移量

	EN_PARA_DC6_STR =EN_PARA_DC5_STR+EN_GROUP_DC_END,        // DC6起始 
	EN_PARA_DC6_IN  =EN_PARA_DC6_STR,                        // DC6输入模式
	EN_PARA_DC6_OUT =EN_PARA_DC6_STR+EN_GROUP_DC_OUT,        // DC6输出模式
	EN_PARA_DC6_MIN =EN_PARA_DC6_STR+EN_GROUP_DC_MIN,        // DC6输出最小值
	EN_PARA_DC6_MAX =EN_PARA_DC6_STR+EN_GROUP_DC_MAX,        // DC6输出最大值
	EN_PARA_DC6_OFST=EN_PARA_DC6_STR+EN_GROUP_DC_OFST,       // DC6输出最偏移量
	
	EN_PARA_DC7_STR =EN_PARA_DC6_STR+EN_GROUP_DC_END,        // DC7起始 
	EN_PARA_DC7_IN  =EN_PARA_DC7_STR,                        // DC7输入模式
	EN_PARA_DC7_OUT =EN_PARA_DC7_STR+EN_GROUP_DC_OUT,        // DC7输出模式
	EN_PARA_DC7_MIN =EN_PARA_DC7_STR+EN_GROUP_DC_MIN,        // DC7输出最小值
	EN_PARA_DC7_MAX =EN_PARA_DC7_STR+EN_GROUP_DC_MAX,        // DC7输出最大值
	EN_PARA_DC7_OFST=EN_PARA_DC7_STR+EN_GROUP_DC_OFST,       // DC7输出最偏移量
#endif
	EN_PARA_DC_V_MA,
	EN_PARA_DC_TB,          // 直流突变
	EN_PARA_T_TB,           // 温度突变参数
	EN_PARA_V_TB,           // 电压突变参数
	EN_PARA_RT_TB,          // 收发功率突变
	EN_PARA_DC_BAK01,       // 直流量备用参数01
	EN_PARA_DC_BAK02,       // 直流量备用参数02
	EN_PARA_DC_BAK03,       // 直流量备用参数03
	EN_PARA_DC_BAK04,       // 直流量备用参数04
	EN_PARA_DC_BAK05,       // 直流量备用参数05
	EN_PARA_DC_BAK06,       // 直流量备用参数06
	EN_PARA_DC_BAK07,       // 直流量备用参数07
	EN_PARA_DC_BAK08,       // 直流量备用参数08
	EN_PARA_DC_BAK09,       // 直流量备用参数09
	EN_PARA_DC_BAK10,       // 直流量备用参数10
	EN_PARA_DC_END,
//  交流参数
	EN_PARA_SAM_STR=EN_PARA_DC_END,
	EN_PARA_BHPT=EN_PARA_SAM_STR,    // 保护测量PT一次值
	EN_PARA_BHPT2,   // 保护测量PT二次值
	EN_PARA_JLPT,    // 计量PT一次值
	EN_PARA_JLPT2,   // 计量PT二次值
	EN_PARA_LXPT,    // 零序PT一次值
	EN_PARA_LXPT2,   // 零序PT二次值
	EN_PARA_XLPT,    // 线路PT一次值
	EN_PARA_XLPT2,   // 线路PT二次值
	EN_PARA_SVBHPT,  // 级联SV保护测量PT一次值
	EN_PARA_SVBHPT2, // 级联SV保护测量PT二次值
	EN_PARA_SVLXPT,  // 级联SV零序PT一次值
	EN_PARA_SVLXPT2, // 级联SV零序PT二次值
	EN_PARA_SVJLPT,  // 级联SV计量PT一次值
	EN_PARA_SVJLPT2, // 级联SV计量PT二次值
	EN_PARA_CT1_1,   // 保护CT一次值
	EN_PARA_CT1_2,   // 保护CT二次值
	EN_PARA_CT2_A1,  // 保护CT2 A相一次值
	EN_PARA_CT2_A2,  // 保护CT2 A相二次值
	EN_PARA_CT2_B1,  // 保护CT2 B相一次值
	EN_PARA_CT2_B2,  // 保护CT2 B相二次值
	EN_PARA_CT2_C1,  // 保护CT2 C相一次值
	EN_PARA_CT2_C2,  // 保护CT2 C相二次值
	EN_PARA_CT_JL1,  // 测量及计量CT一次值
	EN_PARA_CT_JL2,  // 测量及计量CT二次值
	EN_PARA_MAT_POL_SVA,// 级联A套反极性矩阵
	EN_PARA_MAT_POL_SVB,// 级联B套反极性矩阵
	EN_PARA_MAT_POL_L1, // 本地测模拟量反极性1矩阵
	EN_PARA_MAT_POL_L2, // 本地测模拟量反极性2矩阵
	EN_PARA_ENA_JZ,     // AD基准监视投退
	EN_PARA_V_JZ1MIN,   // AD基准1自检门槛上限
	EN_PARA_V_JZ1MAX,   // AD基准1自检门槛下限
	EN_PARA_V_JZ2MIN,   // AD基准2自检门槛上限
	EN_PARA_V_JZ2MAX,   // AD基准2自检门槛下限
	EN_PARA_JF_TYPE,
	EN_PARA_MF_TYPE,
	EN_PARA_SAM_BAK01,       // 交流量备用参数01
	EN_PARA_SAM_BAK02,       // 交流量备用参数02
	EN_PARA_SAM_BAK03,       // 交流量备用参数03
	EN_PARA_SAM_BAK04,       // 交流量备用参数04
	EN_PARA_SAM_BAK05,       // 交流量备用参数05
	EN_PARA_SAM_BAK06,       // 交流量备用参数06
	EN_PARA_SAM_BAK07,       // 交流量备用参数07
	EN_PARA_SAM_BAK08,       // 交流量备用参数08
	EN_PARA_SAM_BAK09,       // 交流量备用参数09
	EN_PARA_SAM_BAK10,       // 交流量备用参数10
	EN_PARA_SAM_END,
	
	EN_PARA_FUN_STR=EN_PARA_SAM_END,//功能参数
	EN_PARA_T_SYNCHK=EN_PARA_FUN_STR,      // 同步异常告警时间
	EN_PARA_T_SAMCHK,      // 采样异常告警时间
	EN_PARA_T_DICHK,       // 光耦失电告警时间
	EN_PARA_T_PARA,        // 参数变化自动复归时间
	EN_PARA_T_SVOK,           // 级联正常延时
	EN_PARA_ENA_VQH,          // 电压切换功能投退
//	EN_PARA_TYPE_BUS,         // 母线连接方式
	EN_PARA_T_VQH_ACT,        // PT切换同时动作告警时间
	EN_PARA_T_VQH_RET,        // PT切换同时返回告警时间
	EN_PARA_T_VQH_RET_RLY,    // PT切换同时返回确认时间
	EN_PARA_T_XSWI,           // 刀闸位置异常告警时间
//	EN_PARA_TYPE_MSAM,        // 母线电压采集方式
	EN_PARA_TYPE_UxSAM,       // 同期电压采集方式
	EN_PARA_ENA_LNK,          // 级联切换功能投退
	EN_PARA_T_BS_CHK,         // 选择把手状态异常告警时间
	EN_PARA_T_LNK_CHK,        // 级联异常告警时间
	EN_PARA_ENA_KHDX,         // 控制回路断线告警投退
	EN_PARA_T_KHDX,           // 控制回路断线告警时间
	EN_PARA_ENA_OPB1,         // 操作电源掉电监视告警投退
	EN_PARA_T_OPB1,           // 操作电源掉电监视告警时间
//	EN_PARA_TYPE_XCBR,        // 开关接入模式
	EN_PARA_SXBYZ_YX,         // 三相不一致遥信定义
	EN_PARA_T_SXBYZ,          // 三相不一致告警时间
	EN_PARA_TYPE_DEV,         // 是否为 B 套 
	EN_PARA_TYPE_KKJ,         // KKJ接入方式
	EN_PARA_TYPE_SHJ,         // SHJ接入方式
	EN_PARA_TYPE_STJ,         // STJ接入方式
	EN_PARA_TYPE_TJF,         // TJF接入方式
//	EN_PARA_T_KKJ,            // KKJ逻辑生成防抖时间
	EN_PARA_ENA_SGZ,          // 事故总功能投退
	EN_PARA_T_SGZ,            // 事故总时间
	EN_PARA_ENA_BSBC,         // 遥分(STJ)闭锁重合闸保持投退
	EN_PARA_T_BSCH_INIT,      // 装置上电闭锁重合闸返回时间
	EN_PARA_T_DO_RTN,
	EN_PARA_ENA_POW,          // 装置电源监视投入
	EN_PARA_MAT_OUT1,         // 备用保护出口1跳闸矩阵
	EN_PARA_MAT_OUT2,         // 备用保护出口2跳闸矩阵
	EN_PARA_MAT_OUT3,         // 备用保护出口3跳闸矩阵
	EN_PARA_MAT_OUT4,         // 备用保护出口4跳闸矩阵
	EN_PARA_MAT_OUT5,         // 备用保护出口5跳闸矩阵(常闭)

	EN_PARA_MAT_LED1,        // 备用指示灯1点亮矩阵
	EN_PARA_MAT_LED2,        // 备用指示灯2点亮矩阵
	EN_PARA_MAT_LED3,        // 备用指示灯3点亮矩阵
	EN_PARA_MAT_LED4,        // 备用指示灯4点亮矩阵
	EN_PARA_MAT_LED5,        // 备用指示灯5点亮矩阵
	EN_PARA_MAT_LED6,        // 备用指示灯6点亮矩阵
	EN_PARA_FUN_BAK01,       // 功能备用参数01
	EN_PARA_FUN_BAK02,       // 功能备用参数02
	EN_PARA_FUN_BAK03,       // 功能备用参数03
	EN_PARA_FUN_BAK04,       // 功能备用参数04
	EN_PARA_FUN_BAK05,       // 功能备用参数05
	EN_PARA_FUN_BAK06,       // 功能备用参数06
	EN_PARA_FUN_BAK07,       // 功能备用参数07
	EN_PARA_FUN_BAK08,       // 功能备用参数08
	EN_PARA_FUN_BAK09,       // 功能备用参数09
	EN_PARA_FUN_BAK10,       // 功能备用参数10
	EN_PARA_FUN_BAK11,       // 功能备用参数11
	EN_PARA_FUN_BAK12,       // 功能备用参数12
	EN_PARA_FUN_BAK13,       // 功能备用参数13
	EN_PARA_FUN_BAK14,       // 功能备用参数14
	EN_PARA_FUN_BAK15,       // 功能备用参数15
	EN_PARA_FUN_BAK16,       // 功能备用参数16
	EN_PARA_FUN_BAK17,       // 功能备用参数17
	EN_PARA_FUN_BAK18,       // 功能备用参数18
	EN_PARA_FUN_BAK19,       // 功能备用参数19
	EN_PARA_FUN_BAK20,       // 功能备用参数20

	EN_PARA_FUN_END,
	
	EN_PARA_DC_COE_STR=EN_PARA_FUN_END,
	EN_PARA_DC_COE_END=EN_PARA_DC_COE_STR+CN_NUM_DC_SAM,
	
	EN_PARA_AM_COE_STR=EN_PARA_DC_COE_END,
	EN_PARA_AM_COE_END=EN_PARA_AM_COE_STR+CN_NUM_AD,
	
	EN_PARA_DCBC_COE_STR=EN_PARA_AM_COE_END,
	EN_PARA_DCBC_COE_END=EN_PARA_DCBC_COE_STR+CN_NUM_AD,
	
	EN_PARA_ANG_COE_STR=EN_PARA_DCBC_COE_END,
	EN_PARA_ANG_COE_END=EN_PARA_ANG_COE_STR+CN_NUM_JZ+CN_NUM_JZ,


	EN_PARA_END= EN_PARA_ANG_COE_END
};
// 参数分类
enum _BOARD_PARA_TYPE_
{
	EN_BOARD_PARA_STR=0,
	EN_BOARD_PARA_DI=EN_BOARD_PARA_STR,
	EN_BOARD_PARA_DC,
	EN_BOARD_PARA_SAM,
	EN_BOARD_PARA_FUN,
	// 直流校准系数单独一类
	EN_BOARD_PARA_DC_COE,
	EN_BOARD_PARA_COM_END,
	// 模拟量校准系数划分为三类,在恢复默认时不相互影响
	EN_BOARD_PARA_AM_COE=EN_BOARD_PARA_COM_END,
	EN_BOARD_PARA_DCBC_COE,
	EN_BOARD_PARA_ANG_COE,
	EN_BOARD_PARA_END,
};
/*================================================================================*/
// 常量表结构体
/*================================================================================*/
typedef struct
{
	WORD            wIndex;                         // 定值虚端子
	WORD            wType;                          // 定值类型
	INT32           iValMin;                        // 最小值
	INT32           iValMax;                        // 最大值
	INT32           iValDft;                        // 缺省值
//	WORD            wCoeRet;                        // 返回系数的100倍
	INT8S           byName[CN_LEN_NAME];            // 定值名称
	INT8S           byPinName[CN_LEN_NAME];         // 虚端子名称
}tagParaTab;
/*================================================================================*/
// 参数分类结构体
/*================================================================================*/
typedef struct
{
	WORD            wIndex;                         // 分类枚举号
	WORD            wIndexStr;                      // 关联参数源起始枚举
	WORD            wIndexEnd;                      // 关联参数源结束枚举
	WORD            wIndexNum;                      // 关联参数个数
	WORD            wGroupNum;                      // 关联参数组数
	INT8S           byName[CN_LEN_NAME];            // 分类名称
	INT8S           byPinName[CN_LEN_NAME];         // 分类短地址
}tagBoardParaTab;

/*================================================================================*/
// 宏定义
/*================================================================================*/
#define CN_NUM_PARA            (EN_PARA_END)
#define CN_NUM_BOARD_PARA_COM  (EN_BOARD_PARA_COM_END)// 板间交互参数
#define CN_NUM_BOARD_PARA      (EN_BOARD_PARA_END)
/*================================================================================*/
// 常量表声明
/*================================================================================*/
extern  const tagParaTab         g_tParaTab[];
extern  const DWORD              g_NUM_PARA;
extern  const tagBoardParaTab    g_tBoardParaTab[];
extern  const DWORD              g_NUM_BOARD_PARA;



/*================================================================================*/
#endif  /* _CONST_PARA_H_ */
