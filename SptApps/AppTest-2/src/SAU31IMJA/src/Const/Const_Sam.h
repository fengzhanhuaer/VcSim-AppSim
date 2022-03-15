#ifndef _CONST_SAM_H_
#define _CONST_SAM_H_

#include "IES_IMtypes.h"
/*================================================================================*/
//母线电压排序枚举，与标准保持一致
/*================================================================================*/
enum _ANA_LINK_TYPE_
{
    EN_LINK_STR=0,           // 母线电压起始
    EN_LINK_UA1=EN_LINK_STR, // 母线A相电压 AD1
    EN_LINK_UA2,             // 母线A相电压 AD2
    EN_LINK_UB1,             // 母线B相电压 AD1
    EN_LINK_UB2,             // 母线B相电压 AD2
    EN_LINK_UC1,             // 母线C相电压 AD1
    EN_LINK_UC2,             // 母线C相电压 AD2
    EN_LINK_U01,             // 母线零序电压 AD1
    EN_LINK_U02,             // 母线零序电压 AD2
    EN_LINK_UAJ,             // 母线A相计量电压
    EN_LINK_UBJ,             // 母线B相计量电压
    EN_LINK_UCJ,             // 母线C相计量电压
    EN_LINK_END              // 母线电压结束
};

/*================================================================================*/
//模拟量信号枚举
/*================================================================================*/
enum _ANA_INDEX_TYPE_
{
    EN_ANA_START,                              //
// 1.本地模拟量通道
    EN_ANA_SAM_STR=EN_ANA_START,               // 本地采样起始
    EN_ANA_UA1=EN_ANA_SAM_STR,                 // 保护测控Ua AD1
    EN_ANA_UA2,                                // 保护测控UA AD2
    EN_ANA_UB1,                                // 保护测控Ub AD1
    EN_ANA_UB2,                                // 保护测控UB AD2
    EN_ANA_UC1,                                // 保护测控Uc AD1
    EN_ANA_UC2,                                // 保护测控UC AD2
    EN_ANA_U01,                                // 零序3U0 AD1
    EN_ANA_U02,                                // 零序3U0 AD2
    EN_ANA_UX1,                                // 同期Ux AD1
    EN_ANA_UX2,                                // 同期UX AD2
    EN_ANA_UAJ,                                // 计量UAj
    EN_ANA_UBJ,                                // 计量UBj
    EN_ANA_UCJ,                                // 计量UCj
    EN_ANA_1_IA1,                              // 保护IA1 AD1
    EN_ANA_1_IA2,                              // 保护IA1 AD2
    EN_ANA_1_IB1,                              // 保护IB1 AD1
    EN_ANA_1_IB2,                              // 保护IB1 AD2
    EN_ANA_1_IC1,                              // 保护IC1 AD1
    EN_ANA_1_IC2,                              // 保护IC1 AD2
    EN_ANA_IAJ,                                // 计量测量IAj
    EN_ANA_IBJ,                                // 计量测量IBj
    EN_ANA_ICJ,                                // 计量测量ICj
    EN_ANA_2_IA1,                              // 保护IA2 AD1
    EN_ANA_2_IA2,                              // 保护IA2 AD2
    EN_ANA_2_IB1,                              // 保护IB2 AD1
    EN_ANA_2_IB2,                              // 保护IB2 AD2
    EN_ANA_2_IC1,                              // 保护IC2 AD1
    EN_ANA_2_IC2,                              // 保护IC2 AD2
    EN_ANA_SAM_END,
// 2.基准通道
    EN_ANA_JZ_STR=EN_ANA_SAM_END,
    EN_ANA_JZ1=EN_ANA_JZ_STR,                  // AD1基准电压
    EN_ANA_JZ2,                                // AD2基准电压
    EN_ANA_JZ3,                                // AD3基准电压
    EN_ANA_JZ4,                                // AD4基准电压
    EN_ANA_JZ5,                                // AD5基准电压
    EN_ANA_JZ_END,
// 3.SV订阅通道
//  注意：级联的母线电压顺序不可调整--STR
    // A套级联数据
#if(CN_DEV_CPU1)
    EN_ANA_SV_STR  =EN_ANA_JZ_END,
    EN_ANA_SVA_STR =EN_ANA_SV_STR,
    EN_ANA_SVA1_STR=EN_ANA_SVA_STR,              // A套Ⅰ母电压起始
    EN_ANA_SVA1_UA1=EN_ANA_SVA1_STR+EN_LINK_UA1,// A套Ⅰ母A相电压 AD1
    EN_ANA_SVA1_UA2=EN_ANA_SVA1_STR+EN_LINK_UA2,// A套Ⅰ母A相电压 AD2
    EN_ANA_SVA1_UB1=EN_ANA_SVA1_STR+EN_LINK_UB1,// A套Ⅰ母B相电压 AD1
    EN_ANA_SVA1_UB2=EN_ANA_SVA1_STR+EN_LINK_UB2,// A套Ⅰ母B相电压 AD2
    EN_ANA_SVA1_UC1=EN_ANA_SVA1_STR+EN_LINK_UC1,// A套Ⅰ母C相电压 AD1
    EN_ANA_SVA1_UC2=EN_ANA_SVA1_STR+EN_LINK_UC2,// A套Ⅰ母C相电压 AD2
    EN_ANA_SVA1_U01=EN_ANA_SVA1_STR+EN_LINK_U01,// A套Ⅰ母零序电压 AD1
    EN_ANA_SVA1_U02=EN_ANA_SVA1_STR+EN_LINK_U02,// A套Ⅰ母零序电压 AD2
    EN_ANA_SVA1_UAJ=EN_ANA_SVA1_STR+EN_LINK_UAJ,// A套Ⅰ母A相计量电压
    EN_ANA_SVA1_UBJ=EN_ANA_SVA1_STR+EN_LINK_UBJ,// A套Ⅰ母B相计量电压
    EN_ANA_SVA1_UCJ=EN_ANA_SVA1_STR+EN_LINK_UCJ,// A套Ⅰ母C相计量电压
    EN_ANA_SVA2_STR=EN_ANA_SVA1_STR+EN_LINK_END,// A套Ⅱ母电压起始
    EN_ANA_SVA2_UA1=EN_ANA_SVA2_STR+EN_LINK_UA1,// A套Ⅱ母A相电压 AD1
    EN_ANA_SVA2_UA2=EN_ANA_SVA2_STR+EN_LINK_UA2,// A套Ⅱ母A相电压 AD2
    EN_ANA_SVA2_UB1=EN_ANA_SVA2_STR+EN_LINK_UB1,// A套Ⅱ母B相电压 AD1
    EN_ANA_SVA2_UB2=EN_ANA_SVA2_STR+EN_LINK_UB2,// A套Ⅱ母B相电压 AD2
    EN_ANA_SVA2_UC1=EN_ANA_SVA2_STR+EN_LINK_UC1,// A套Ⅱ母C相电压 AD1
    EN_ANA_SVA2_UC2=EN_ANA_SVA2_STR+EN_LINK_UC2,// A套Ⅱ母C相电压 AD2
    EN_ANA_SVA2_U01=EN_ANA_SVA2_STR+EN_LINK_U01,// A套Ⅱ母零序电压 AD1
    EN_ANA_SVA2_U02=EN_ANA_SVA2_STR+EN_LINK_U02,// A套Ⅱ母零序电压 AD2
    EN_ANA_SVA2_UAJ=EN_ANA_SVA2_STR+EN_LINK_UAJ,// A套Ⅱ母A相计量电压
    EN_ANA_SVA2_UBJ=EN_ANA_SVA2_STR+EN_LINK_UBJ,// A套Ⅱ母B相计量电压
    EN_ANA_SVA2_UCJ=EN_ANA_SVA2_STR+EN_LINK_UCJ,// A套Ⅱ母C相计量电压
    EN_ANA_SVA_END =EN_ANA_SVA2_STR+EN_LINK_END,
    // B 套级联数据
    EN_ANA_SVB_STR=EN_ANA_SVA_END,
    EN_ANA_SVB1_STR=EN_ANA_SVA2_STR+EN_LINK_END,// B套Ⅰ母电压起始
    EN_ANA_SVB1_UA1=EN_ANA_SVB1_STR+EN_LINK_UA1,// B套Ⅰ母A相电压 AD1
    EN_ANA_SVB1_UA2=EN_ANA_SVB1_STR+EN_LINK_UA2,// B套Ⅰ母A相电压 AD2
    EN_ANA_SVB1_UB1=EN_ANA_SVB1_STR+EN_LINK_UB1,// B套Ⅰ母B相电压 AD1
    EN_ANA_SVB1_UB2=EN_ANA_SVB1_STR+EN_LINK_UB2,// B套Ⅰ母B相电压 AD2
    EN_ANA_SVB1_UC1=EN_ANA_SVB1_STR+EN_LINK_UC1,// B套Ⅰ母C相电压 AD1
    EN_ANA_SVB1_UC2=EN_ANA_SVB1_STR+EN_LINK_UC2,// B套Ⅰ母C相电压 AD2
    EN_ANA_SVB1_U01=EN_ANA_SVB1_STR+EN_LINK_U01,// B套Ⅰ母零序电压 AD1
    EN_ANA_SVB1_U02=EN_ANA_SVB1_STR+EN_LINK_U02,// B套Ⅰ母零序电压 AD2
    EN_ANA_SVB1_UAJ=EN_ANA_SVB1_STR+EN_LINK_UAJ,// B套Ⅰ母A相计量电压
    EN_ANA_SVB1_UBJ=EN_ANA_SVB1_STR+EN_LINK_UBJ,// B套Ⅰ母B相计量电压
    EN_ANA_SVB1_UCJ=EN_ANA_SVB1_STR+EN_LINK_UCJ,// B套Ⅰ母C相计量电压
    
    EN_ANA_SVB2_STR=EN_ANA_SVB1_STR+EN_LINK_END,// B套Ⅱ母电压起始
    EN_ANA_SVB2_UA1=EN_ANA_SVB2_STR+EN_LINK_UA1,// B套Ⅱ母A相电压 AD1
    EN_ANA_SVB2_UA2=EN_ANA_SVB2_STR+EN_LINK_UA2,// B套Ⅱ母A相电压 AD2
    EN_ANA_SVB2_UB1=EN_ANA_SVB2_STR+EN_LINK_UB1,// B套Ⅱ母B相电压 AD1
    EN_ANA_SVB2_UB2=EN_ANA_SVB2_STR+EN_LINK_UB2,// B套Ⅱ母B相电压 AD2
    EN_ANA_SVB2_UC1=EN_ANA_SVB2_STR+EN_LINK_UC1,// B套Ⅱ母C相电压 AD1
    EN_ANA_SVB2_UC2=EN_ANA_SVB2_STR+EN_LINK_UC2,// B套Ⅱ母C相电压 AD2
    EN_ANA_SVB2_U01=EN_ANA_SVB2_STR+EN_LINK_U01,// B套Ⅱ母零序电压 AD1
    EN_ANA_SVB2_U02=EN_ANA_SVB2_STR+EN_LINK_U02,// B套Ⅱ母零序电压 AD2
    EN_ANA_SVB2_UAJ=EN_ANA_SVB2_STR+EN_LINK_UAJ,// B套Ⅱ母A相计量电压
    EN_ANA_SVB2_UBJ=EN_ANA_SVB2_STR+EN_LINK_UBJ,// B套Ⅱ母B相计量电压
    EN_ANA_SVB2_UCJ=EN_ANA_SVB2_STR+EN_LINK_UCJ,// B套Ⅱ母C相计量电压
    EN_ANA_SVB_END=EN_ANA_SVB2_STR+EN_LINK_END,
    EN_ANA_SV_END=EN_ANA_SVB_END,
#elif(CN_DEV_CPU2)
    EN_ANA_SV_STR  =EN_ANA_JZ_END,
    EN_ANA_SVA_STR =EN_ANA_SV_STR,
    EN_ANA_SVA1_STR=EN_ANA_SVA_STR, 			 // A套Ⅰ母电压起始
    EN_ANA_SVA1_UA1=EN_ANA_SVA1_STR+EN_LINK_UA1,// A套Ⅰ母A相电压 AD1
    EN_ANA_SVA1_UA2=EN_ANA_SVA1_STR+EN_LINK_UA2,// A套Ⅰ母A相电压 AD2
    EN_ANA_SVA1_UB1=EN_ANA_SVA1_STR+EN_LINK_UB1,// A套Ⅰ母B相电压 AD1
    EN_ANA_SVA1_UB2=EN_ANA_SVA1_STR+EN_LINK_UB2,// A套Ⅰ母B相电压 AD2
    EN_ANA_SVA1_UC1=EN_ANA_SVA1_STR+EN_LINK_UC1,// A套Ⅰ母C相电压 AD1
    EN_ANA_SVA1_UC2=EN_ANA_SVA1_STR+EN_LINK_UC2,// A套Ⅰ母C相电压 AD2
    EN_ANA_SVA1_U01=EN_ANA_SVA1_STR+EN_LINK_U01,// A套Ⅰ母零序电压 AD1
    EN_ANA_SVA1_U02=EN_ANA_SVA1_STR+EN_LINK_U02,// A套Ⅰ母零序电压 AD2
    EN_ANA_SVA1_UAJ=EN_ANA_SVA1_STR+EN_LINK_UAJ,// A套Ⅰ母A相计量电压
    EN_ANA_SVA1_UBJ=EN_ANA_SVA1_STR+EN_LINK_UBJ,// A套Ⅰ母B相计量电压
    EN_ANA_SVA1_UCJ=EN_ANA_SVA1_STR+EN_LINK_UCJ,// A套Ⅰ母C相计量电压
    EN_ANA_SVA1_END=EN_ANA_SVA1_STR+EN_LINK_END,
    EN_ANA_SV_END  =EN_ANA_SVA1_END,
#endif
    //  注意：级联的母线电压顺序不可调整--end
    EN_ANA_END=EN_ANA_SV_END
};
/*================================================================================*/
//计算信号枚举
/*================================================================================*/
enum _CAL_INDEX_TYPE_
{
//  直采模拟量通道
    EN_CAL_START=0,                           //
    EN_CAL_A1_F1=EN_CAL_START,                //
    EN_CAL_A1_F2,                             //
#if(CN_DEV_CPU1)
    EN_CAL_A2_F1,                             //
    EN_CAL_A2_F2,                             //
    EN_CAL_B1_F1,                             //
    EN_CAL_B1_F2,                             //
    EN_CAL_B2_F1,                             //
    EN_CAL_B2_F2,                             //
#endif
    EN_CAL_J1_F1,                             //
    EN_CAL_J1_F2,                             //
    EN_CAL_Ux_F1,                             //
    EN_CAL_Ux_F2,                             //
    EN_CAL_END
};
#define  CN_TCHG_ENA   (1)// 温度调节系数控制

#if(CN_TCHG_ENA)
// 温度调节系数分类
enum _TCHG_INDEX_TYPE_
{
    EN_TCHG_MOD1=0,
    EN_TCHG_MOD2,
    EN_TCHG_MOD3,
    EN_TCHG_END,
};
#endif
/*================================================================================*/
//模拟量相关板卡枚举
/*================================================================================*/
enum _BOARD_ANA_TYPE_
{
    EN_BOARD_SAM_PTCT1=0,
    EN_BOARD_SAM_PTCT2,
    EN_BOARD_SAM_CPU,     //基准
    EN_BOARD_SAM_END,
    EN_BOARD_SV_SVA=0,
    EN_BOARD_SV_SVB,
    EN_BOARD_SV_END
};
/*================================================================================*/
//常量表结构体
/*================================================================================*/
// 模拟量常量信息表数据结构
typedef struct
{
	WORD            wIndex;                         // 模拟量枚举号
	WORD            wChanType;                      // 模拟量向量类型
	WORD            wParaFst;                       // 关联的额定一次值参数
	WORD            wParaScd;                       // 关联的额定二次值参数
	WORD            wFrmNo;                         // 数据源--帧类型
	WORD            wADNo;                          // 数据源--AD芯片编码
	WORD            wADChn;                         // 数据源--AD芯片通道编码
	DWORD           dwCfg;                          // 通道其他属性
	INT8S           byName[CN_LEN_NAME];            // 模拟量名称
	INT8S           byPinName[CN_LEN_NAME];         // 模拟量短地址
} tagAnaTab;
// 计算常量表结构体
typedef struct
{
	WORD            wIndex;                         // 计算量枚举号
	WORD            wChanType;                      // 计算量类型
	WORD            wSrcDType;                      // 计算源类型
	WORD            wSrcIndex[3];                   // 计算源枚举
	WORD            wParaIndex;                     // 计算量参数设置
	INT8S           byName[CN_LEN_NAME];            // 计算量名称
	INT8S           byPinName[CN_LEN_NAME];         // 计算量短地址
} tagCalTab;
// SV配置
typedef struct
{
	WORD            wStdIndex;                         // SV发布标准配置枚举
	WORD            wAnaIndex;                         // SV发布取模拟量母线电压枚举
	WORD            wAnaIndex2;                        // SV发布无母线电压枚举
	
} tagSvPubTab;
// 板卡设置常量表结构体
typedef struct
{
	WORD            wIndex;                         // 板卡枚举号
	INT8S           byName[CN_LEN_NAME];            // 板卡名称
	INT8S           byPinName[CN_LEN_NAME];         // 板卡短地址
	WORD            wIndexNum;                      // 通道个数
} tagBoardAnaTab;

/*================================================================================*/
// 宏定义
/*================================================================================*/
// 通道数据量宏定义
#define CN_NUM_SAM          (EN_ANA_SAM_END-EN_ANA_SAM_STR)   // 交流量通道数
#define CN_NUM_JZ           (EN_ANA_JZ_END-EN_ANA_JZ_STR)     // 基准通道数
#define CN_NUM_AD           (CN_NUM_SAM+CN_NUM_JZ)            // 本地通道个数
#define CN_NUM_SV           (EN_ANA_SV_END-EN_ANA_SV_STR)     // SV订阅通道数
#define CN_NUM_ANA          (EN_ANA_END)                      // SV发布相关数据总通道
#define CN_NUM_CAL          (EN_CAL_END)                      // 计算量通道数
#define CN_NUM_BOARD_SAM    (EN_BOARD_SAM_END)                // 相关模拟量板卡个数
#define CN_NUM_BOARD_SV     (EN_BOARD_SV_END)                 // 相关数字量板卡个数
// AD延时基准通道
#define CN_BASE_AD         (EN_ANA_UA1)                       // AD基准通道
// 采样配置宏定义
#define CN_SAM_RATE         (80)                              // 单周期采样点数
#define CN_SAM_NUM          (2)                               // 缓存周期
#define CN_SAM_LEN          (CN_SAM_RATE*CN_SAM_NUM)          // 缓存长度
// 谐波相关宏定义
#define CN_HUM_ENA          (0)                               // 谐波计算投退
#define CN_HUM_NUM          (13)                              // 谐波计算次数

#define CN_DFT_COE          (0.01767767f)                     // 全周傅式固定系数√2/80
#define CN_DFT_BIT          (20)                              // 全周傅式固定系数平移位数
#define CN_SV_U_Unit        (0.01f)                           // SV电压最小单位(10mV)
#define CN_SV_I_Unit        (0.001f)                          // SV电流最小单位(1mA)
// 模拟量显示倍率
#define CN_SAM_DIV_U        (3)                               // 电压显示数据倍率
#define CN_SAM_DIV_I        (3)                               // 电流显示数据倍率
#define CN_SAM_DIV_F        (2)                               // 频率显示数据倍率
#define CN_SAM_DIV_Ang      (3)                               // 相位显示数据倍率
// 测频相关宏定义
#define CN_CAL_F_UMk        (1000)                            // 电压测频门槛 1V
#define CN_CAL_F_Coe        (g_dwMul[CN_SAM_DIV_F])           // 测频计算倍数
#define CN_CAL_F_QD         (3)                               // 测频启动周波数
#define CN_CAL_F_CNT        (50*CN_SAM_RATE)                  // 标准采样频率
// 基准电压选择门槛 0.2V
#define CN_BASE_UMK          (200)                            // 基准电压门槛0.2V
#define CN_BASE_IMK          (4)                              // 基准电流门槛0.004A
#define CN_SV_IN_ENA         (TRUE)                           // SV订阅功能投退
#define CN_NUM_SVCB_SUB      (2)                              // SV订阅控制块个数
#define CN_NUM_SVCB_PUB      (2)                              // SV发布控制块个数
// SV额定延时
#define CN_SVPUB_TIME_LINK   (1876)                           // SV额定延时(带有级联数据)
#define CN_SVPUB_TIME        (876)                            // SV额定延时(无级联数据)
// SV配置字
#define CN_SVCFG_CfgErr       (DB0)                             // bit0 平台提供--配置异常
#define CN_SVCFG_ParseErr     (DB1)                             // bit1 平台提供--解析异常。
#define CN_SVCFG_DataErr      (CN_SVCFG_CfgErr+CN_SVCFG_ParseErr)
// SVSUB控制块状态字
#define CN_SVCB_NO            (0xf)                           // bit0~bit3  控制块序号
#define CN_SVCB_NetPort       (0xf0)                          // bit4~bit7  网络端口
#define CN_SVCB_LinkErr1      (DB8)                           // bit8 断链判断。1：断链；0：正常。
#define CN_SVCB_APPIDErr      (DB9)                           // bit9 APPID参数不匹配。1：不匹配；0：正常。
#define CN_SVCB_SVIDErr       (DB10)                          // bit10 SVID参数不匹配。1：不匹配；0：正常。
#define CN_SVCB_ConfRevErr    (DB11)                          // bit11 ConfRev参数不匹配。1：不匹配；0：正常。
#define CN_SVCB_DataNumErr    (DB12)                          // bit12 DataNum参数不匹配。1：不匹配；0：正常。
#define CN_SVCB_DataSetErr    (DB13)                          // bit13 DataSet参数不匹配。1：不匹配；0：正常。
#define CN_SVCB_DtErr         (DB14)                          // bit14 通道抖动异常闭锁(±20ms)。
#define CN_SVCB_SamCntErr     (DB15)                          // bit15 SamCnt乱序。1：乱序；0：正常。
#define CN_SVCB_SynErr        (DB16)                          // bit16 同步丢失指示。1：同步异常；0：正常。
#define CN_SVCB_Invalid       (DB17)                          // bit17 数据无效。1：数据无效；0：正常。
#define CN_SVCB_Test          (DB18)                          // bit18 数据检修。1：数据检修；0：正常。
#define CN_SVCB_DlyErr        (DB19)                          // bit19 定延时越限或不一致。1：不一致；0：正常。
#define CN_SVCB_CommErr       (DB20)                          // bit20 平台提供--通信异常
#define CN_SVCB_TypeErr       (DB21)                          // bit21 平台提供--帧类型异常。
#define CN_SVCB_CfgErr        (DB22)                          // bit22 平台提供--上电初始化配置异常。
                                                              // bit23~bit30 备用
#define CN_SVCB_Ena           (DB31)                          // bit31 控制块使能,1：使能 0：未使能

// SV控制块异常整合 不包含失步、断链
#define CN_SVCB_DataErr      (CN_SVCB_APPIDErr+CN_SVCB_SVIDErr+CN_SVCB_ConfRevErr+   \
	CN_SVCB_DataNumErr+CN_SVCB_DataSetErr+CN_SVCB_DtErr+CN_SVCB_SamCntErr+CN_SVCB_Invalid+ \
    CN_SVCB_CommErr+CN_SVCB_TypeErr+CN_SVCB_CfgErr)
    
// SV控制块异常至级联SV发布通道无效,不包含品质无效、检修、失步
#define CN_SVCB_Link_QErr      (CN_SVCB_LinkErr1+CN_SVCB_APPIDErr+CN_SVCB_SVIDErr+CN_SVCB_ConfRevErr+   \
		CN_SVCB_DataNumErr+CN_SVCB_DataSetErr+CN_SVCB_DtErr+CN_SVCB_SamCntErr+ \
		CN_SVCB_CommErr+CN_SVCB_TypeErr+CN_SVCB_CfgErr)

// IEC61850-9-2品质值数据定位
#define CN_SV_Q_VALIDL       (DB0)                           // 有效性两位(good/invalid/reserved/questionable) 00-正常 01-无效 10-保留 11-可疑
#define CN_SV_Q_VALIDH       (DB1)                           // 有效性两位(good/invalid/reserved/questionable) 00-正常 01-无效 10-保留 11-可疑
#define CN_SV_Q_DETAIL01     (DB2)                           // 细化品质01位(overflow)0--  无溢出，1--溢出
#define CN_SV_Q_DETAIL02     (DB3)                           // 细化品质02位(outOfRange)0--  正常范围，1--超值域
#define CN_SV_Q_DETAIL03     (DB4)                           // 细化品质03位(badReference)0--  基准正常，1--坏基准值
#define CN_SV_Q_DETAIL04     (DB5)                           // 细化品质04位(oscillatory)0--  无抖动，1--抖动
#define CN_SV_Q_DETAIL05     (DB6)                           // 细化品质05位(failure)0--  无故障，1--故障
#define CN_SV_Q_DETAIL06     (DB7)                           // 细化品质06位(oldData)0--  无超时，1--数据超时
#define CN_SV_Q_DETAIL07     (DB8)                           // 细化品质07位(inconsistent)0--一致，1--不一致
#define CN_SV_Q_DETAIL08     (DB9)                           // 细化品质08位(inaccurate)0--  精确，1--不精确
#define CN_SV_Q_SOURCE       (DB10)                          // 数据源(process/substituted)0--  过程，1--取代
#define CN_SV_Q_TEST         (DB11)                          // 测试位0--  运行，1--检修
#define CN_SV_Q_OPBLK        (DB12)                          // 操作员闭锁
// 私有品质
#define CN_SV_Q_VCLR         (DB15)                          // 私有品质(用作通道数据清零)

// 挑数设置
#define CN_SV_Pub_Index1      (0x7f)                          // 挑数--通道1(被减数) bit0-bit6
#define CN_SV_Pub_Index2      (0x3f10)                        // 挑数--通道2(减数) bit7-bit13
#define CN_SV_Pub_Pol         (DB14)                          // 挑数--极性设置
#define CN_SV_Pub_Cal         (DB15)                          // 挑数--运算设置
// 挑数操作
#define CN_SV_OPT_NULL        (0)                             // 挑数操作类型--无操作
#define CN_SV_OPT_POL_S       (DB0)                           // 挑数操作类型--极性变化成功
#define CN_SV_OPT_CHG1_S      (DB1)                           // 挑数操作类型--级联切换成功
#define CN_SV_OPT_CHG2_S      (DB2)                           // 挑数操作类型--电压切换成功
#define CN_SV_OPT_CAL_S       (DB3)                           // 挑数操作类型--线电压修正成功
#define CN_SV_OPT_CHG1_F      (DB8)                           // 挑数操作类型--级联切换失败
#define CN_SV_OPT_CHG2_F      (DB9)                           // 挑数操作类型--电压切换失败
#define CN_SV_OPT_CAL_F       (DB10)                          // 挑数操作类型--线电压修正失败
// 挑数操作成功
#define CN_SV_OPT_S           (CN_SV_OPT_POL_S+CN_SV_OPT_CHG1_S+CN_SV_OPT_CHG2_S+CN_SV_OPT_CAL_S)
// 挑数操作失败
#define CN_SV_OPT_F           (CN_SV_OPT_CHG1_F+CN_SV_OPT_CHG2_F+CN_SV_OPT_CAL_F)
/*================================================================================*/
// 变量声明
/*================================================================================*/
extern const tagAnaTab    g_tAnaTab[];
extern const DWORD        g_NUM_ANA;

extern const tagCalTab    g_tCalTab[];
extern const DWORD        g_NUM_CAL;

extern const tagSvPubTab  g_tSvPubTab[];
extern const DWORD        g_NUM_SVPUB;

extern const tagBoardAnaTab  g_tBoardSamTab[];
extern const DWORD           g_NUM_BOARDSAM;
#if 0
extern const tagBoardAnaTab  g_tBoardSvTab[];
extern const DWORD           g_NUM_BOARDSV;
#endif
extern const INT64      g_iCos80[CN_SAM_RATE];
extern const INT64      g_iSin80[CN_SAM_RATE];

/*================================================================================*/
#endif /* _CONST_SAM_H_ */
