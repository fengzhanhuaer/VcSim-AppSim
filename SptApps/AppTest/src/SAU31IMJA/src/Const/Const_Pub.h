/*================================================================================
 * 文件描述：公用配置
 * 文件版本: V1.00
 * 定版时间:
 * 版本修订:
 * 修订人员:
 *================================================================================*/
#ifndef _CONST_EQUIP_H_
#define _CONST_EQUIP_H_

#include "Const_DC.h"
#include "Const_IO.h"
#include "Const_Sam.h"
#include "Const_Para.h"
#include "Const_Rec.h"
#include "Const_Flag.h"
#include "Const_Com.h"

// 板件属性
#ifndef CN_DEV_CPU1
#error  装置型号设置错误:缺少宏定义CN_DEV_CPU1
#define CN_DEV_CPU1    ( FALSE )                   // 间隔采集执行单元-间隔板
#endif
#ifndef CN_DEV_CPU2
#error  装置型号设置错误:缺少宏定义CN_DEV_CPU2
#define CN_DEV_CPU2    ( FALSE )                   // 间隔采集执行单元-母线板
#endif
//增加宏定义校验,防止型号宏定义设置错误
#if((CN_DEV_CPU1+CN_DEV_CPU2)!=1)
#error  装置板卡设置错误:宏定义设置错
#endif

// 系统测试内部版本V1.00,对外展示版本V1.00
// 程序公共版本
#define CN_DEV_TITLE_NAME   "SAU-32IMJA-DA-GZK"
#define CN_CPU1_PUBLIC_SOFT "V1.00 57B2 20211101"
#define CN_CPU2_PUBLIC_SOFT "V1.00 348F 20211101"
#if(CN_DEV_CPU1)
#define CN_CPU_NAME         "CPU1"
#define CN_CPU_SOFT_VER_P   1              // CPU主版本信息
#define CN_CPU_SOFT_VER_A   0              // CPU辅助版本信息
#define CN_CPU_SOFT_VER_M   0              // CPU细化版本信息
#elif(CN_DEV_CPU2)
#define CN_CPU_NAME         "CPU2"
#define CN_CPU_SOFT_VER_P   1              // CPU主版本信息
#define CN_CPU_SOFT_VER_A   0              // CPU辅助版本信息
#define CN_CPU_SOFT_VER_M   0              // CPU细化版本信息
#endif
// 数据类常量表枚举
enum  _DATA_TYPE_
{
    EN_DTYPE_STR=0,
    EN_DTYPE_ANA=EN_DTYPE_STR,
    EN_DTYPE_CAL,
    EN_DTYPE_DC,
// 状态量数据源起始
    EN_DTYPE_BOOL_STR,
    EN_DTYPE_DI=EN_DTYPE_BOOL_STR,
    EN_DTYPE_DPI,
    EN_DTYPE_GOIN,
    EN_DTYPE_DO,
    EN_DTYPE_GOOUT,
    EN_DTYPE_LED,
    EN_DTYPE_ACT,
    EN_DTYPE_ALM,
    EN_DTYPE_CHK,
    EN_DTYPE_FLAG,
    EN_DTYPE_INTER,
    EN_DTYPE_BOOL_END,
// 状态量数据源结束
    EN_DTYPE_PARA=EN_DTYPE_BOOL_END,
    EN_DTYPE_END,
    
    EN_CFG_STR=EN_DTYPE_END,
    EN_CFG_DTYPE=EN_CFG_STR,
    EN_CFG_SAM_PUB,
    EN_CFG_SAM_BOARD,
    EN_CFG_DI_BOARD,
    EN_CFG_DO_BOARD,
    EN_CFG_DC_BOARD,
    EN_CFG_PARA_BOARD,
    EN_CFG_RUN,
    EN_CFG_OPT,
    EN_CFG_COM_INIT,
    EN_CFG_COM_FAST1_2,
    EN_CFG_COM_FAST2_1,
    EN_CFG_COM_SLOW1_2,
    EN_CFG_COM_SLOW2_1,
    EN_CFG_END,
};

// 通道类型枚举
enum  _CHN_TYPE_
{
	EN_CTYPE_STR,
	// 模拟量表格g_tAnaTab通道类型
	EN_CTYPE_ANA_STR=EN_CTYPE_STR,
	EN_CTYPE_ANA_I=EN_CTYPE_ANA_STR,
	EN_CTYPE_ANA_U,
	EN_CTYPE_ANA_J,
	EN_CTYPE_SV_I,
	EN_CTYPE_SV_U,
	EN_CTYPE_SV_T,
	EN_CTYPE_ANA_END,
	// 计算量表格g_tCalTab通道类型
	EN_CTYPE_CAL_STR=EN_CTYPE_ANA_END,
	EN_CTYPE_CAL_F=EN_CTYPE_CAL_STR,
	EN_CTYPE_CAL_END,
	// IO类表格通道类型
	EN_CTYPE_IO_STR=EN_CTYPE_CAL_END,
	EN_CTYPE_IO_S=EN_CTYPE_IO_STR,
	EN_CTYPE_IO_D,
	EN_CTYPE_IO_P,
	EN_CTYPE_IO_T,
	EN_CTYPE_IO_END,
	// 直流表格g_tDCTab通道类型
	EN_CTYPE_DC_STR=EN_CTYPE_IO_END,
	EN_CTYPE_DC_ZL1=EN_CTYPE_DC_STR,
	EN_CTYPE_DC_ZL2,
#if(!CN_FUN_DBUG1)
	EN_CTYPE_DC_ZL3,
	EN_CTYPE_DC_ZL4,
	EN_CTYPE_DC_ZL5,
	EN_CTYPE_DC_ZL6,
	EN_CTYPE_DC_ZL7,
#endif
	EN_CTYPE_DC_mA,
	EN_CTYPE_DC_V,
	EN_CTYPE_DC_T,
	EN_CTYPE_DC_Hum,
	EN_CTYPE_DC_DBM,
	EN_CTYPE_DC_OPTT,
	EN_CTYPE_DC_OPTV,
	EN_CTYPE_DC_H,
	EN_CTYPE_DC_END,
	// 参数表格g_tParaTab通道类型
	EN_CTYPE_PARA_STR=EN_CTYPE_DC_END,
	EN_CTYPE_PARA_S=EN_CTYPE_PARA_STR,
	EN_CTYPE_PARA_Ms,
	EN_CTYPE_PARA_Us,
	EN_CTYPE_PARA_Us_1,
//	EN_CTYPE_PARA_Ns,
	EN_CTYPE_PARA_PT1,
	EN_CTYPE_PARA_PT2,
	EN_CTYPE_PARA_CT1,
	EN_CTYPE_PARA_CT2,
	EN_CTYPE_PARA_V,
	EN_CTYPE_PARA_mV,
	EN_CTYPE_PARA_A,
	EN_CTYPE_PARA_mA,
	EN_CTYPE_PARA_T,       // 温度
	EN_CTYPE_PARA_Hum,     // 湿度
	EN_CTYPE_PARA_OBM,     // 光功率
	EN_CTYPE_PARA_Per,     // 百分比
// 无单位参数类型
	EN_CTYPE_PARA_H,       // 16进制类型
	EN_CTYPE_PARA_MAT,     // 带枚举矩阵类型
	EN_CTYPE_PARA_D,       // 无符号10进制类型
	EN_CTYPE_PARA_D_1,     // 无符号10进制浮点1位小数显示
	EN_CTYPE_PARA_D_2,     // 无符号10进制浮点2位小数显示
	EN_CTYPE_PARA_D_3,     // 无符号10进制浮点3位小数显示
	EN_CTYPE_PARA_D_4,     // 无符号10进制浮点4位小数显示
	EN_CTYPE_PARA_D_5,     // 无符号10进制浮点5位小数显示
	EN_CTYPE_PARA_D_6,     // 无符号10进制浮点6位小数显示
	EN_CTYPE_PARA_I,       // 有符号10进制
	EN_CTYPE_PARA_I_1,     // 有符号10进制浮点1位小数显示
	EN_CTYPE_PARA_I_2,     // 有符号10进制浮点2位小数显示
	EN_CTYPE_PARA_I_3,     // 有符号10进制浮点3位小数显示
	EN_CTYPE_PARA_I_4,     // 有符号10进制浮点4位小数显示
	EN_CTYPE_PARA_I_5,     // 有符号10进制浮点5位小数显示
	EN_CTYPE_PARA_I_6,     // 有符号10进制浮点6位小数显示	
	EN_CTYPE_PARA_B,       // 布尔类型
	EN_CTYPE_PARA_END,
};
// 通道类型枚举
enum  _CHN_ENUM_
{
	// 枚举部分
	EN_CENUM_STR=EN_CTYPE_PARA_END,
	EN_CENUM_PARA_DCIN=EN_CENUM_STR,
	EN_CENUM_PARA_DCOUT,
	EN_CENUM_PARA_CT2,
	EN_CENUM_PARA_BusLik,
	EN_CENUM_PARA_Fr,
	EN_CENUM_PARA_MSAM,
	EN_CENUM_PARA_UxSAM,
//	EN_CENUM_PARA_XCBR,
	EN_CENUM_PARA_DISAM,
	EN_CENUM_PARA_Ux,
	EN_CENUM_DO_STATUS,
	EN_CENUM_FAIL_RET,
	EN_CENUM_END,
	EN_CTYPE_END=EN_CENUM_END,
};

enum _MEA_TYPE_
{
	EN_MEA_INDEX=0,							// 序号
	EN_MEA_LC_RX,							// 接收功率
	EN_MEA_LC_TX,							// 发送功率
	EN_MEA_PTR,								// 地址
	EN_MEA_DTYPE, 							// 数据类型
	EN_MEA_FLAG,							// 标志字
	EN_MEA_FLAG16,							// 标志字
	EN_MEA_FLAG8,							// 标志字
	EN_MEA_V,								// 电压
	EN_MEA_mA,								// 电流
	EN_MEA_VALUE,							// 测量值
	EN_MEA_PORT,							// 网口号
	EN_MEA_BOARD,							// 板卡号
	EN_MEA_SVCB,							// SVCB号
	EN_MEA_SVCB_SUB,						// SVCB定阅控制块状态字
	EN_MEA_SVCB_CFG,						// SVCB配置标志字
	EN_MEA_GOCB,							// GOCB号
	EN_MEA_GOCB_A,							// GOOSE A网状态字
	EN_MEA_GOCB_B,							// GOOSE B网状态字
	EN_MEA_GOCB_CFG,						// GOOSE 订阅配置状态字
	EN_MEA_BHTZ_DO,
	EN_MEA_BHHZ_DO,
	EN_MEA_CKTZ_DO,
	EN_MEA_CKHZ_DO,
	EN_MEA_SHTQ_DO,
	EN_MEA_BZTTZ_DO,
	EN_MEA_BZTHZ_DO,
	EN_MEA_CLS_XSWI01_DO,
	EN_MEA_OPN_XSWI01_DO,
	EN_MEA_JBS_XSWI01_DO,
	EN_MEA_CLS_XSWI02_DO,
	EN_MEA_OPN_XSWI02_DO,
	EN_MEA_JBS_XSWI02_DO,
	EN_MEA_CLS_XSWI03_DO,
	EN_MEA_OPN_XSWI03_DO,
	EN_MEA_JBS_XSWI03_DO,
	EN_MEA_CLS_XSWI04_DO,
	EN_MEA_OPN_XSWI04_DO,
	EN_MEA_JBS_XSWI04_DO,
	EN_MEA_CLS_XSWI05_DO,
	EN_MEA_OPN_XSWI05_DO,
	EN_MEA_JBS_XSWI05_DO,
	EN_MEA_CLS_XSWI06_DO,
	EN_MEA_OPN_XSWI06_DO,
	EN_MEA_JBS_XSWI06_DO,
	EN_MEA_CLS_XSWI07_DO,
	EN_MEA_OPN_XSWI07_DO,
	EN_MEA_JBS_XSWI07_DO,
	EN_MEA_CLS_XSWI08_DO,
	EN_MEA_OPN_XSWI08_DO,
	EN_MEA_JBS_XSWI08_DO,
	EN_MEA_BAK_01_DO,
	EN_MEA_BAK_02_DO,
	EN_MEA_DO_STATUS,
	EN_MEA_DO_FAIL,
	EN_MEA_DO_APPID,
	EN_MEA_DO_RET_T,
	EN_MEA_END
};
// 颜色枚举
enum  _COLOR_TYPE_
{
    EN_COLOR_NULL=0,
    EN_COLOR_RED,
    EN_COLOR_GREEN,
    EN_COLOR_YELLOW,
    EN_COLOR_END
};
// 软件枚举
enum  _SOFT_VER_TYPE_
{
    EN_SOFT_STR=0,
    EN_SOFT_CPU1_CPU=EN_SOFT_STR,// 本板CPU
    EN_SOFT_CPU1_CPU_BOOT0,      // 本板CPU Boot0
    EN_SOFT_CPU1_CPU_UBOOT,      // 本板CPU Uboot
    EN_SOFT_CPU1_CPU_BSP,        // 本板CPU BSP
    EN_SOFT_CPU1_FPGA,           // 本板FPGA
    EN_SOFT_CPU1_FPGA2,              
    EN_SOFT_CPU2_CPU,            // 另一CPU
    EN_SOFT_CPU2_FPGA,           // 另一CPU板FPGA
    EN_SOFT_DI1_CPU,
    EN_SOFT_DI2_CPU,
    EN_SOFT_DI3_CPU,
    EN_SOFT_DO1_CPU,
    EN_SOFT_DO2_CPU,
    EN_SOFT_DIO_CPU,
    EN_SOFT_DC_CPU,
    EN_SOFT_END
};
// 板卡枚举
enum  _CARD_INDEX_TYPE_
{
    EN_CARD_STR=0,
    EN_CARD_CPU1=EN_CARD_STR,// CPU1
    EN_CARD_CPU2,            // CPU2
    EN_CARD_END
};
// 指令枚举
enum  _KEY_INDEX_TYPE_
{
    EN_KEY_STR=0,
    EN_KEY_VER=EN_KEY_STR,// CPU1
    EN_KEY_END
};

#if(CN_DEV_CPU1)
#define  CN_BOARD_CPU        (EN_CARD_CPU1)
#define  CN_BOARD_CPU_OTH    (EN_CARD_CPU2)
#elif(CN_DEV_CPU2)
#define  CN_BOARD_CPU        (EN_CARD_CPU2)
#define  CN_BOARD_CPU_OTH    (EN_CARD_CPU1)
#endif
#define CN_NUM_DTYPE         (EN_DTYPE_END)             // 数据类型常量表枚举数
#define CN_NUM_CFG           (EN_CFG_END-EN_CFG_STR)    // 配置类型常量表枚举数
#define CN_NUM_PUB           (EN_CFG_END)               // 配置类型常量表枚举数
#define CN_NUM_SOFT          (EN_SOFT_END)              // 软件个数
#define CN_NULL_PINNO        (0xAAAA)                   // 无此虚端子

// 事项队列长度
#define CN_NUM_RPT_ACT   (512)
#define CN_NUM_RPT_ALM   (512)
#define CN_NUM_RPT_CHK   (512)
#define CN_NUM_RPT_RUN   (512)
#define CN_NUM_RPT_OPT   (1024)
#define CN_NUM_RPT_DI    (4096)
#define CN_NUM_RPT_GOIN  (1024)
#define CN_NUM_RPT_FLAG  (512)
#define CN_NUM_RPT_DO    (512)
#define CN_NUM_RPT_GOOUT (512)
#define CN_NUM_RPT_LED   (512)
#define CN_NUM_RPT_DPI   (512)

// 内存扫描相关宏定义
#define CN_RAMSCAN_MAX      (1024)
#define CN_RAMSCAN_VALUE    (0x5A)
// 板卡类型
#define CN_BOARD_CPU1_ADDR  (0x5A5A5A5A)
#define CN_BOARD_CPU2_ADDR  (0xA5A5A5A5)
// 界面触发模拟量计算等待时间(100ms)
#define CN_FACE_TIME        (100)
// 中断频率
#define  T(t)                   ((t)*4)
// 时间常量(中断点数):    按照一个中断调用一次的延时时间常量
#define CN_T1MS                 (T(1))
#define CN_T2MS                 (T(2))
#define CN_T3MS                 (T(3))
#define CN_T4MS                 (T(4))
#define CN_T5MS                 (T(5))
#define CN_T6MS                 (T(6))
#define CN_T7MS                 (T(7))
#define CN_T8MS                 (T(8))
#define CN_T9MS                 (T(9))
#define CN_T10MS                (T(10))
#define CN_T20MS                (CN_T10MS*2)
#define CN_T21MS                (T(21))
#define CN_T23MS                (T(23))
#define CN_T25MS                (CN_T10MS*2.5)
#define CN_T30MS                (CN_T10MS*3)
#define CN_T40MS                (CN_T10MS*4)
#define CN_T50MS                (CN_T10MS*5)
#define CN_T60MS                (CN_T10MS*6)
#define CN_T70MS                (CN_T10MS*7)
#define CN_T80MS                (CN_T10MS*8)
#define CN_T90MS                (CN_T10MS*9)
#define CN_T100MS               (CN_T10MS*10)
#define CN_T110MS               (CN_T10MS*11)
#define CN_T140MS               (CN_T10MS*14)
#define CN_T160MS               (CN_T10MS*16)
#define CN_T200MS               (CN_T10MS*20)
#define CN_T250MS               (CN_T10MS*25)
#define CN_T400MS               (CN_T10MS*40)
#define CN_T500MS               (CN_T10MS*50)
#define CN_T600MS               (CN_T10MS*60)
#define CN_T1300MS              (CN_T10MS*130)
#define CN_T1500MS              (CN_T10MS*150)
#define CN_T2500MS              (CN_T10MS*250)
#define CN_T1S                  (CN_T10MS*100)
#define CN_T2S                  (CN_T1S*2)
#define CN_T3S                  (CN_T1S*3)
#define CN_T4S                  (CN_T1S*4)
#define CN_T5S                  (CN_T1S*5)
#define CN_T6S                  (CN_T1S*6)
#define CN_T7S                  (CN_T1S*7)
#define CN_T8S                  (CN_T1S*8)
#define CN_T9S                  (CN_T1S*9)
#define CN_T10S                 (CN_T1S*10)
#define CN_T11S                 (CN_T1S*11)
#define CN_T12S                 (CN_T1S*12)
#define CN_T13S                 (CN_T1S*13)
#define CN_T14S                 (CN_T1S*14)
#define CN_T15S                 (CN_T1S*15)
#define CN_T20S                 (CN_T1S*20)
#define CN_T30S                 (CN_T1S*30)
#define CN_T40S                 (CN_T1S*40)
#define CN_T50S                 (CN_T1S*50)
#define CN_T60S                 (CN_T1S*60)
#define CN_T70S                 (CN_T1S*70)
#define CN_T80S                 (CN_T1S*80)
#define CN_T90S                 (CN_T1S*90)
#define CN_T100S                (CN_T1S*100)
#define CN_T120S                (CN_T1S*120)
#define CN_T300S                (CN_T1S*300)
#define CN_T600S                (CN_T1S*600)
#define CN_T900S                (CN_T1S*900)

// 时间常量(ms):
#define CN_MS_T_1MS             (1)
#define CN_MS_T_3MS             (3)
#define CN_MS_T_5MS             (5)
#define CN_MS_T_10MS            (10)
#define CN_MS_T_20MS            (CN_MS_T_10MS*2)
#define CN_MS_T_100MS           (CN_MS_T_10MS*10)
#define CN_MS_T_200MS           (CN_MS_T_10MS*20)
#define CN_MS_T_250MS           (CN_MS_T_10MS*25)
#define CN_MS_T_400MS           (CN_MS_T_10MS*40)
#define CN_MS_T_500MS           (CN_MS_T_10MS*50)
#define CN_MS_T_600MS           (CN_MS_T_10MS*60)
#define CN_MS_T_2500MS          (CN_MS_T_10MS*250)
#define CN_MS_T_1S              (CN_MS_T_10MS*100)
#define CN_MS_T_2S              (CN_MS_T_1S*2)
#define CN_MS_T_3S              (CN_MS_T_1S*3)
#define CN_MS_T_4S              (CN_MS_T_1S*4)
#define CN_MS_T_5S              (CN_MS_T_1S*5)
#define CN_MS_T_6S              (CN_MS_T_1S*6)
#define CN_MS_T_7S              (CN_MS_T_1S*7)
#define CN_MS_T_8S              (CN_MS_T_1S*8)
#define CN_MS_T_9S              (CN_MS_T_1S*9)
#define CN_MS_T_10S             (CN_MS_T_1S*10)
#define CN_MS_T_20S             (CN_MS_T_1S*20)
#define CN_MS_T_60S             (CN_MS_T_1S*60)
#define CN_MS_T_100S            (CN_MS_T_1S*100)
#define CN_MS_T_120S            (CN_MS_T_1S*120)
#define CN_MS_T_300S            (CN_MS_T_1S*300)
#define CN_MS_T_600S            (CN_MS_T_1S*600)
#define CN_MS_T_900S            (CN_MS_T_1S*900)
// BIT位定义
#define DB0                 (0x01)
#define DB1                 (0x02)
#define DB2                 (0x04)
#define DB3                 (0x08)
#define DB4                 (0x10)
#define DB5                 (0x20)
#define DB6                 (0x40)
#define DB7                 (0x80)
#define DB8                 (0x100)
#define DB9                 (0x200)
#define DB10                (0x400)
#define DB11                (0x800)
#define DB12                (0x1000)
#define DB13                (0x2000)
#define DB14                (0x4000)
#define DB15                (0x8000)
#define DB16                (0x10000)
#define DB17                (0x20000)
#define DB18                (0x40000)
#define DB19                (0x80000)
#define DB20                (0x100000)
#define DB21                (0x200000)
#define DB22                (0x400000)
#define DB23                (0x800000)
#define DB24                (0x1000000)
#define DB25                (0x2000000)
#define DB26                (0x4000000)
#define DB27                (0x8000000)
#define DB28                (0x10000000)
#define DB29                (0x20000000)
#define DB30                (0x40000000)
#define DB31                (0x80000000)
// GOOSE品质值数据定位
#define CN_Go_Q_VALIDL       (DB0)                           // 有效性两位(good/invalid/reserved/questionable) 00-正常 01-无效 10-保留 11-可疑
#define CN_Go_Q_VALIDH       (DB1)                           // 有效性两位(good/invalid/reserved/questionable) 00-正常 01-无效 10-保留 11-可疑
#define CN_Go_Q_DETAIL01     (DB2)                           // 细化品质01位(overflow)0--  无溢出，1--溢出
#define CN_Go_Q_DETAIL02     (DB3)                           // 细化品质02位(outOfRange)0--  正常范围，1--超值域
#define CN_Go_Q_DETAIL03     (DB4)                           // 细化品质03位(badReference)0--  基准正常，1--错误引用
#define CN_Go_Q_DETAIL04     (DB5)                           // 细化品质04位(oscillatory)0--  无抖动，1--抖动
#define CN_Go_Q_DETAIL05     (DB6)                           // 细化品质05位(failure)0--  无故障，1--失败
#define CN_Go_Q_DETAIL06     (DB7)                           // 细化品质06位(oldData)0--  无超时，1--旧数据
#define CN_Go_Q_DETAIL07     (DB8)                           // 细化品质07位(inconsistent)0--一致，1--不一致
#define CN_Go_Q_DETAIL08     (DB9)                           // 细化品质08位(inaccurate)0--  精确，1--不精确
#define CN_Go_Q_SOURCE       (DB10)                          // 数据源(process/substituted)0--  过程，1--取代
#define CN_Go_Q_TEST         (DB11)                          // 测试位0--  运行，1--检修
#define CN_Go_Q_OPBLK        (DB12)                          // 操作员闭锁
// 常量表自检标志集
#define CN_CONST_CHK_NUM      (DB0)                           // 常量表个数错误
#define CN_CONST_CHK_NO       (DB1)                           // 常量表顺序错误
#define CN_CONST_CHK_TYPE     (DB2)                           // 常量表类型错误
#define CN_CONST_CHK_CHAR     (DB3)                           // 常量表字符串溢出
#define CN_CONST_CHK_LMT      (DB4)                           // 常量表范围配置错误
#define CN_CONST_CHK_PARA1    (DB5)                           // 常量表参数1配置错误
#define CN_CONST_CHK_PARA2    (DB6)                           // 常量表参数2配置错误
#define CN_CONST_CHK_ADDR     (DB7)                           // 常量表地址配置错误
#define CN_CONST_CHK_LINK     (DB8)                           // 常量表关联配置错误
#define CN_CONST_CHK_SUB      (DB9)                           // 常量表附加配置错误

typedef struct
{
	WORD            wIndex;                         // 数据类型枚举
	BYTE           *bTabAtr;                        // 数据常量表地址
	BYTE           *bDatAtr;                        // 数据地址
	WORD            wDatNumCal;                     // 数据个数计算
	WORD            wDatNum;                        // 数据个数
	INT8S           byName[CN_LEN_NAME];            // 数据名称
	INT8S           bPinAdd[CN_LEN_NAME];           // 数据短短地址前缀
}tagDTypeTab;
typedef struct
{
	WORD            wIndex;                         // 常量表类型枚举
	BYTE           *bTabAtr;                        // 常量表地址
	const DWORD     dwDatNumCal;                    // 数据个数计算
	const DWORD     dwDatNum;                       // 数据个数
	INT8S           byName[CN_LEN_NAME];            // 常量表名称
	INT8S           bPinAdd[CN_LEN_NAME];           // 常量表短地址前缀
}tagCfgTab;

extern const tagDTypeTab  g_tDTypeTab[];
extern const DWORD        g_NUM_DTYPE;

extern const tagCfgTab    g_tCfgTab[];
extern const DWORD        g_NUM_CFG;

extern const UINT32   g_dwMul[];                    // 系数常量表
extern const FLOAT32  g_fDiv[];                     // 倍率常量表
extern const UINT32   g_dwBit[];                    // 比特位常量表

#endif  /* _CONST_EQUIP_H_ */
