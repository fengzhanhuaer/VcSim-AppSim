/*================================================================================
 * 文件描述：事项配置常量表
 * 文件版本: V1.00
 * 开发人员:
 * 定版时间:
 * 版本修订:
 * 修订人员:
 *================================================================================*/

#include "Const_Pub.h"
//================================================================================
// GOOSE命令常量表
//  WORD            wIndex;                  // 记录枚举
//  WORD            wSrcType;                // 数据源类型
//  WORD            wSrcIndex[CN_ACT_SNUM];  // 数据源枚举
//  WORD            wCfg;                    // 其他设置
//  WORD            wValType1;               // 事项记录数据类型1
//  WORD            wValType2;               // 事项记录数据类型2
//  WORD            wValType3;               // 事项记录数据类型3
//  WORD            wValType4;               // 事项记录数据类型4
//  WORD            wValType5;               // 事项记录数据类型5
//  WORD            wValType6;               // 事项记录数据类型6
//  INT8S           byName[CN_LEN_NAME];     // 记录名称
//  INT8S           byPinName[CN_LEN_NAME];  // 虚端子名称
//================================================================================
const tagActTab g_tActTab[ ] =
{
	{EN_ACT_BHTZ  ,   EN_DTYPE_GOIN,             {EN_GOIN_BHTZ1,      // 保护跳闸1
	                                              EN_GOIN_BHTZ2,      // 保护跳闸2
	                                              EN_GOIN_BHTZ3,      // 保护跳闸3
	                                              EN_GOIN_BHTZ4,      // 保护跳闸4
	                                              EN_GOIN_BHTZ5,      // 保护跳闸5
	                                              CN_NULL_PINNO       // 结束符
	                                               },        EN_DO_BHTZ,      EN_DI_DO_BHTZ,    0, EN_MEA_DO_STATUS, EN_MEA_BHTZ_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "保护跳闸",    "ACT_BHTZ"},
	{EN_ACT_BHHZ  ,   EN_DTYPE_GOIN,             {EN_GOIN_BHHZ1,      // 保护重合闸1
	                                              EN_GOIN_BHHZ2,      // 保护重合闸2
	                                              EN_GOIN_BHHZ3,      // 保护重合闸3
	                                              EN_GOIN_BHHZ4,      // 保护重合闸4
	                                              EN_GOIN_BHHZ5,      // 保护重合闸5
	                                              CN_NULL_PINNO       // 结束符
	                                                },        EN_DO_BHHZ,    EN_DI_DO_BHHZ,    0,  EN_MEA_DO_STATUS,  EN_MEA_BHHZ_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "保护重合闸",    "ACT_BHHZ"},
	{EN_ACT_BHYT  ,   EN_DTYPE_GOIN,             {EN_GOIN_BHYT1,      // 保护永跳1
	                                              EN_GOIN_BHYT2,      // 保护永跳2
	                                              EN_GOIN_BHYT3,      // 保护永跳3
	                                              EN_GOIN_BHYT4,      // 保护永跳4
	                                              EN_GOIN_BHYT5,      // 保护永跳5
	                                              EN_GOIN_BHYT6,      // 保护永跳6
	                                              EN_GOIN_BHYT7,      // 保护永跳7
	                                              EN_GOIN_BHYT8,      // 保护永跳8
	                                              EN_GOIN_BHYT9,      // 保护永跳9
	                                              EN_GOIN_BHYT10,     // 保护永跳10
	                                              CN_NULL_PINNO       // 结束符
	                                               },         EN_DO_BHTZ,    EN_DI_DO_BHTZ,      0,  EN_MEA_DO_STATUS,  EN_MEA_BHTZ_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "保护永跳"  ,      "ACT_BHYT"},
	{EN_ACT_CKTZ  ,   EN_DTYPE_GOIN,             {EN_GOIN_CKTZ,
	                                             CN_NULL_PINNO       // 结束符
	                                                },        EN_DO_XCBR_OPN,   EN_DI_DO_XCBR_OPN,  0,  EN_MEA_DO_STATUS,  EN_MEA_CKTZ_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "测控跳闸",       "ACT_CKTZ"},
	{EN_ACT_CKHZ  ,   EN_DTYPE_GOIN,             {EN_GOIN_CKHZ,
	                                              CN_NULL_PINNO      // 结束符
	                                                 },       EN_DO_XCBR_CLS,    EN_DI_DO_XCBR_CLS,  0,  EN_MEA_DO_STATUS,  EN_MEA_CKHZ_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "测控合闸",       "ACT_CKHZ"},
	{EN_ACT_JBS_XCBR  ,   EN_DTYPE_GOIN,             {EN_GOIN_JBS_XCBR,
	                                              CN_NULL_PINNO      // 结束符
	                                                 },       EN_DO_XCBR_JBS,    EN_DI_DO_XCBR_JBS,  0,  EN_MEA_DO_STATUS,  EN_MEA_JBS_XCBR_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "断路器解闭锁",       "ACT_JBS_XCBR"},

	{EN_ACT_BZTTZ ,   EN_DTYPE_GOIN,             {EN_GOIN_BZTTZ1,
	                                              EN_GOIN_BZTTZ2,
	                                              CN_NULL_PINNO       // 结束符
	                                                 },       EN_DO_BZTTZ,              EN_DI_DO_BZTTZ,     0,  EN_MEA_DO_STATUS,  EN_MEA_BZTTZ_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "备自投跳闸",       "ACT_BZTTZ"},
	{EN_ACT_BZTHZ ,   EN_DTYPE_GOIN,             {EN_GOIN_BZTHZ1,
	                                              EN_GOIN_BZTHZ2,
	                                              CN_NULL_PINNO      // 结束符
	                                                 },       EN_DO_BZTHZ,              EN_DI_DO_BZTHZ,    0,  EN_MEA_DO_STATUS,  EN_MEA_BZTHZ_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "备自投合闸",       "ACT_BZTHZ"},
	{EN_ACT_CLS_XSWI01  ,   EN_DTYPE_GOIN,       {EN_GOIN_CLS_XSWI01,
	                                              CN_NULL_PINNO       // 结束符
	                                                 },       EN_DO_XSWI01_CLS,         EN_DI_DO_XSWI01_CLS,  0,  EN_MEA_DO_STATUS,  EN_MEA_CLS_XSWI01_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "合刀闸1",       "ACT_CLS_XSWI01"},
	{EN_ACT_OPN_XSWI01  ,   EN_DTYPE_GOIN,       {EN_GOIN_OPN_XSWI01,
	                                              CN_NULL_PINNO      // 结束符
	                                                 },       EN_DO_XSWI01_OPN,         EN_DI_DO_XSWI01_OPN,  0,  EN_MEA_DO_STATUS,  EN_MEA_OPN_XSWI01_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "分刀闸1",       "ACT_OPN_XSWI01"},
	{EN_ACT_JBS_XSWI01  ,   EN_DTYPE_GOIN,       {EN_GOIN_JBS_XSWI01,
	                                              CN_NULL_PINNO       // 结束符
	                                                 },       EN_DO_XSWI01_JBS,         EN_DI_DO_XSWI01_JBS,  0,  EN_MEA_DO_STATUS,  EN_MEA_JBS_XSWI01_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "解闭锁1"  ,       "ACT_JBS_XSWI01"},
	{EN_ACT_CLS_XSWI02  ,   EN_DTYPE_GOIN,       {EN_GOIN_CLS_XSWI02,
	                                              CN_NULL_PINNO      // 结束符
	                                                 },       EN_DO_XSWI02_CLS,         EN_DI_DO_XSWI02_CLS,  0,  EN_MEA_DO_STATUS,  EN_MEA_CLS_XSWI02_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "合刀闸2",       "ACT_CLS_XSWI02"},
	{EN_ACT_OPN_XSWI02  ,   EN_DTYPE_GOIN,       {EN_GOIN_OPN_XSWI02  ,
	                                              CN_NULL_PINNO       // 结束符
	                                                 },       EN_DO_XSWI02_OPN,         EN_DI_DO_XSWI02_OPN,  0,  EN_MEA_DO_STATUS,  EN_MEA_OPN_XSWI02_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "分刀闸2",       "ACT_OPN_XSWI02"},
	{EN_ACT_JBS_XSWI02  ,   EN_DTYPE_GOIN,       {EN_GOIN_JBS_XSWI02,
	                                              CN_NULL_PINNO      // 结束符
	                                                 },       EN_DO_XSWI02_JBS,         EN_DI_DO_XSWI02_JBS,  0,  EN_MEA_DO_STATUS,  EN_MEA_JBS_XSWI02_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "解闭锁2"  ,       "ACT_JBS_XSWI02"},
	{EN_ACT_CLS_XSWI03  ,   EN_DTYPE_GOIN,       {EN_GOIN_CLS_XSWI03,
	                                              CN_NULL_PINNO       // 结束符
	                                                 },       EN_DO_XSWI03_CLS,         EN_DI_DO_XSWI03_CLS,  0,  EN_MEA_DO_STATUS,  EN_MEA_CLS_XSWI03_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "合刀闸3",       "ACT_CLS_XSWI03"},
	{EN_ACT_OPN_XSWI03  ,   EN_DTYPE_GOIN,       {EN_GOIN_OPN_XSWI03,
	                                              CN_NULL_PINNO      // 结束符
	                                                 },       EN_DO_XSWI03_OPN,         EN_DI_DO_XSWI03_OPN,  0,  EN_MEA_DO_STATUS,  EN_MEA_OPN_XSWI03_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "分刀闸3",       "ACT_OPN_XSWI03"},
	{EN_ACT_JBS_XSWI03  ,   EN_DTYPE_GOIN,       {EN_GOIN_JBS_XSWI03,
	                                              CN_NULL_PINNO       // 结束符
	                                                 },       EN_DO_XSWI03_JBS,         EN_DI_DO_XSWI03_JBS,  0,  EN_MEA_DO_STATUS,  EN_MEA_JBS_XSWI03_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "解闭锁3"  ,       "ACT_JBS_XSWI03"},
	{EN_ACT_CLS_XSWI04  ,   EN_DTYPE_GOIN,       {EN_GOIN_CLS_XSWI04,
	                                              CN_NULL_PINNO       // 结束符
	                                                 },       EN_DO_XSWI04_CLS,         EN_DI_DO_XSWI04_CLS,  0,  EN_MEA_DO_STATUS,  EN_MEA_CLS_XSWI04_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "合刀闸4",       "ACT_CLS_XSWI04"},
	{EN_ACT_OPN_XSWI04  ,   EN_DTYPE_GOIN,       {EN_GOIN_OPN_XSWI04,
	                                              CN_NULL_PINNO      // 结束符
	                                                 },       EN_DO_XSWI04_OPN,         EN_DI_DO_XSWI04_OPN,  0,  EN_MEA_DO_STATUS,  EN_MEA_OPN_XSWI04_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "分刀闸4",       "ACT_OPN_XSWI04"},
	{EN_ACT_JBS_XSWI04  ,   EN_DTYPE_GOIN,       {EN_GOIN_JBS_XSWI04,
	                                              CN_NULL_PINNO       // 结束符
	                                                 },      EN_DO_XSWI04_JBS,         EN_DI_DO_XSWI04_JBS,  0,  EN_MEA_DO_STATUS,  EN_MEA_JBS_XSWI04_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "解闭锁4"  ,       "ACT_JBS_XSWI04"},
	{EN_ACT_CLS_XSWI05  ,   EN_DTYPE_GOIN,       {EN_GOIN_CLS_XSWI05,
	                                              CN_NULL_PINNO      // 结束符
	                                                 },      EN_DO_XSWI05_CLS,         EN_DI_DO_XSWI05_CLS,  0,  EN_MEA_DO_STATUS,  EN_MEA_CLS_XSWI05_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "合刀闸5",       "ACT_CLS_XSWI05"},
	{EN_ACT_OPN_XSWI05  ,   EN_DTYPE_GOIN,       {EN_GOIN_OPN_XSWI05,
	                                              CN_NULL_PINNO       // 结束符
	                                                 },       EN_DO_XSWI05_OPN,        EN_DI_DO_XSWI05_OPN,  0,  EN_MEA_DO_STATUS,  EN_MEA_OPN_XSWI05_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "分刀闸5",       "ACT_OPN_XSWI05"},
	{EN_ACT_JBS_XSWI05  ,   EN_DTYPE_GOIN,       {EN_GOIN_JBS_XSWI05,
	                                              CN_NULL_PINNO      // 结束符
	                                                 },       EN_DO_XSWI05_JBS,        EN_DI_DO_XSWI05_JBS,  0,  EN_MEA_DO_STATUS,  EN_MEA_JBS_XSWI05_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "解闭锁5"  ,       "ACT_JBS_XSWI05"},
	{EN_ACT_CLS_XSWI06  ,   EN_DTYPE_GOIN,       {EN_GOIN_CLS_XSWI06,
	                                              CN_NULL_PINNO       // 结束符
	                                                 },       EN_DO_XSWI06_CLS,        EN_DI_DO_XSWI06_CLS,  0,  EN_MEA_DO_STATUS,  EN_MEA_CLS_XSWI06_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "合刀闸6",       "ACT_CLS_XSWI06"},
	{EN_ACT_OPN_XSWI06  ,   EN_DTYPE_GOIN,       {EN_GOIN_OPN_XSWI06,
	                                              CN_NULL_PINNO       // 结束符
	                                                 },       EN_DO_XSWI06_OPN,        EN_DI_DO_XSWI06_OPN,  0,  EN_MEA_DO_STATUS,  EN_MEA_OPN_XSWI06_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "分刀闸6",       "ACT_OPN_XSWI06"},
	{EN_ACT_JBS_XSWI06  ,   EN_DTYPE_GOIN,       {EN_GOIN_JBS_XSWI06,
	                                              CN_NULL_PINNO      // 结束符
	                                                 },       EN_DO_XSWI06_JBS,        EN_DI_DO_XSWI06_JBS,  0,  EN_MEA_DO_STATUS,  EN_MEA_JBS_XSWI06_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "解闭锁6"  ,       "ACT_JBS_XSWI06"},
	{EN_ACT_CLS_XSWI07  ,   EN_DTYPE_GOIN,       {EN_GOIN_CLS_XSWI07,
	                                              CN_NULL_PINNO       // 结束符
	                                                 },       EN_DO_XSWI07_CLS,        EN_DI_DO_XSWI07_CLS,  0,  EN_MEA_DO_STATUS,  EN_MEA_CLS_XSWI07_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "合刀闸7",       "ACT_CLS_XSWI07"},
	{EN_ACT_OPN_XSWI07  ,   EN_DTYPE_GOIN,       {EN_GOIN_OPN_XSWI07,
	                                              CN_NULL_PINNO      // 结束符
	                                                 },       EN_DO_XSWI07_OPN,        EN_DI_DO_XSWI07_OPN,  0,  EN_MEA_DO_STATUS,  EN_MEA_OPN_XSWI07_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "分刀闸7",       "ACT_OPN_XSWI07"},
	{EN_ACT_JBS_XSWI07  ,   EN_DTYPE_GOIN,       {EN_GOIN_JBS_XSWI07,
	                                              CN_NULL_PINNO       // 结束符
	                                                 },       EN_DO_XSWI07_JBS,        EN_DI_DO_XSWI07_JBS,  0,  EN_MEA_DO_STATUS,  EN_MEA_JBS_XSWI07_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "解闭锁7"  ,       "ACT_JBS_XSWI07"},
	{EN_ACT_CLS_XSWI08  ,   EN_DTYPE_GOIN,       {EN_GOIN_CLS_XSWI08,
	                                              CN_NULL_PINNO      // 结束符
	                                                 },       EN_DO_XSWI08_CLS,        EN_DI_DO_XSWI08_CLS,  0,  EN_MEA_DO_STATUS,   EN_MEA_CLS_XSWI08_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "合刀闸8",       "ACT_CLS_XSWI08"},
	{EN_ACT_OPN_XSWI08  ,   EN_DTYPE_GOIN,       {EN_GOIN_OPN_XSWI08,
	                                              CN_NULL_PINNO       // 结束符
	                                                 },       EN_DO_XSWI08_OPN,        EN_DI_DO_XSWI08_OPN,  0,  EN_MEA_DO_STATUS,  EN_MEA_OPN_XSWI08_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "分刀闸8",       "ACT_OPN_XSWI08"},
	{EN_ACT_JBS_XSWI08  ,   EN_DTYPE_GOIN,       {EN_GOIN_JBS_XSWI08,
	                                              CN_NULL_PINNO      // 结束符
	                                                 },       EN_DO_XSWI08_JBS,        EN_DI_DO_XSWI08_JBS,  0,  EN_MEA_DO_STATUS,  EN_MEA_JBS_XSWI08_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "解闭锁8"  ,       "ACT_JBS_XSWI08"},
	{EN_ACT_BAK_01      ,   EN_DTYPE_GOIN,       {EN_GOIN_BAK_01,
	                                              CN_NULL_PINNO       // 结束符
	                                                 },       EN_DO_YK_BAK1,           EN_DI_DO_YK_BAK1,     0,  EN_MEA_DO_STATUS, EN_MEA_BAK_01_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "备用遥控1"    ,      "ACT_BAK_01"},
	{EN_ACT_BAK_02      ,   EN_DTYPE_GOIN,       {EN_GOIN_BAK_02,
	                                              CN_NULL_PINNO      // 结束符
	                                                 },       EN_DO_YK_BAK2,           EN_DI_DO_YK_BAK2,     0,  EN_MEA_DO_STATUS,  EN_MEA_BAK_02_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "备用遥控2"    ,      "ACT_BAK_02"}
};
const DWORD g_NUM_ACT = sizeof(g_tActTab) / sizeof(tagActTab);
//================================================================================
// 告警常量表
//  WORD            wIndex;            // 记录枚举
//  WORD            wParaEna;          // 投退参数枚举
//  WORD            wParaTime;         // 时间参数枚举
//  WORD            wDefTime;          // 默认时间参数
//  WORD            wRetTime;          // 默认返回时间参数
//  WORD            wCfg;              // 其他设置：NULL 无操作 DB0-运行异常出口
//  WORD            wValType1;         // 事项记录数据类型1
//  WORD            wValType2;         // 事项记录数据类型2
//  WORD            wValType3;         // 事项记录数据类型3
//  INT8S           byName[CN_LEN_NAME];        // 记录名称
//  INT8S           byPinName[CN_LEN_NAME];     // 虚端子名称
//================================================================================

const tagAlmTab g_tAlmTab[ ] =
{
	{EN_ALM_SYN           ,     CN_NULL_PINNO,         EN_PARA_T_SYNCHK,   CN_T1S,        CN_T1S,    DB0,  CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "同步异常",               "ALM_SYN"},
	{EN_ALM_SAM           ,     CN_NULL_PINNO,         EN_PARA_T_SAMCHK,   CN_T1S,        CN_T1S,    DB0,  EN_MEA_FLAG16,  EN_MEA_FLAG16,  CN_NULL_PINNO,  "采样异常",               "ALM_SAM"},
	{EN_ALM_DIPOW         ,     CN_NULL_PINNO,         EN_PARA_T_DICHK ,   CN_T1S,        CN_T1S,    DB0,  EN_MEA_FLAG16,  CN_NULL_PINNO,  CN_NULL_PINNO,  "光耦失电",               "ALM_DIPOW"},
	{EN_ALM_TIME_SINGLE   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "对时信号状态",             "ALM_TIME_SINGLE"},
	{EN_ALM_TIME_SERVICE  ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "对时服务状态",             "ALM_TIME_SERVICE"},
	{EN_ALM_TIME_CHKERR   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "时间跳变侦测状态",           "ALM_TIME_CHKERR"},
	{EN_ALM_TEST          ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "检修不一致",              "ALM_TEST"},
	{EN_ALM_SV            ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         DB0,  CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "SV总告警",              "ALM_SV"},
	{EN_ALM_SVPUB_INVALID ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "SV发布数据无效",           "ALM_SVPUB_INVALID"},
	{EN_ALM_LINK          ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "级联异常",                "ALM_LINK"},
	{EN_ALM_SVSUB         ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "SV级联数据异常",            "ALM_SVSUB"},
	{EN_ALM_SVSUB_COM01   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    EN_MEA_SVCB_SUB,CN_NULL_PINNO,  CN_NULL_PINNO,  "SVCB01断链",            "ALM_SVSUB_COM01"},
	{EN_ALM_SVSUB_COM02   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    EN_MEA_SVCB_SUB,CN_NULL_PINNO,  CN_NULL_PINNO,  "SVCB02断链",            "ALM_SVSUB_COM02"},
	{EN_ALM_SVSUB_DAT01   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    EN_MEA_SVCB_SUB,CN_NULL_PINNO,  CN_NULL_PINNO,  "SVCB01数据异常",          "ALM_SVSUB_DAT01"},
	{EN_ALM_SVSUB_DAT02   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    EN_MEA_SVCB_SUB,CN_NULL_PINNO,  CN_NULL_PINNO,  "SVCB02数据异常",          "ALM_SVSUB_DAT02"},
	{EN_ALM_SVSUB_TEST01  ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    EN_MEA_SVCB_SUB,CN_NULL_PINNO,  CN_NULL_PINNO,  "SVCB01检修不一致",         "ALM_SVSUB_TEST01"},
	{EN_ALM_SVSUB_TEST02  ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    EN_MEA_SVCB_SUB,CN_NULL_PINNO,  CN_NULL_PINNO,  "SVCB02检修不一致",         "ALM_SVSUB_TEST02"},
	{EN_ALM_SVSUB_SYN01   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    EN_MEA_SVCB_SUB,CN_NULL_PINNO,  CN_NULL_PINNO,  "SVCB01同步异常",          "ALM_SVSUB_SYN01"},
	{EN_ALM_SVSUB_SYN02   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    EN_MEA_SVCB_SUB,CN_NULL_PINNO,  CN_NULL_PINNO,  "SVCB02同步异常",          "ALM_SVSUB_SYN02"},
	{EN_ALM_SVSUB_CFG01   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "SVCB01配置错误",          "ALM_SVSUB_CFG01"},
	{EN_ALM_SVSUB_CFG02   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "SVCB02配置错误",          "ALM_SVSUB_CFG02"},

	{EN_ALM_SVLINK_QA     ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "A套级联SV数据异常",          "ALM_SVLINK_QA"},
	{EN_ALM_SVLINK_QB     ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "B套级联SV数据异常",          "ALM_SVLINK_QB"},
	{EN_ALM_SVLINK_CFGA   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "A套级联SV配置异常",          "ALM_SVLINK_CFGA"},
	{EN_ALM_SVLINK_CFGB   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "B套级联SV配置异常",          "ALM_SVLINK_CFGB"},
	{EN_ALM_SVLINK_NOCFGA ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "A套级联SV未配置",           "ALM_SVLINK_NOCFGA"},
	{EN_ALM_SVLINK_NOCFGB ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "B套级联SV未配置",           "ALM_SVLINK_NOCFGB"},
	{EN_ALM_SVLINK_TESTA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "A套级联SV检修",            "ALM_SVLINK_TESTA"},
	{EN_ALM_SVLINK_TESTB  ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "B套级联SV检修",            "ALM_SVLINK_TESTB"},
	{EN_ALM_KHDX          ,     EN_PARA_ENA_KHDX,      EN_PARA_T_KHDX,        0,         CN_T1S,     DB0,  CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "控制回路断线",              "ALM_KHDX"},
	{EN_ALM_XZBS          ,     EN_PARA_ENA_LNK,       EN_PARA_T_BS_CHK,      0,         CN_T1S,     DB0,  CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "选择把手状态异常",            "ALM_XZBS"},
	{EN_ALM_XSWI          ,     EN_PARA_ENA_VQH,       EN_PARA_T_XSWI,        0,         CN_T1S,     DB0,  CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "刀闸位置异常",              "ALM_XSWI"},
	{EN_ALM_PTACT         ,     EN_PARA_ENA_VQH,       EN_PARA_T_VQH_ACT,     0,         CN_T1S,     DB0,  CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "PT切换同时动作",            "ALM_PTACT"},
	{EN_ALM_PTRET         ,     EN_PARA_ENA_VQH,       EN_PARA_T_VQH_RET,     0,         CN_T1S,     DB0,  CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "PT切换同时返回",            "ALM_PTRET"},
	{EN_ALM_OPBP1         ,     EN_PARA_ENA_OPB1,      EN_PARA_T_OPB1,        0,         CN_T1S,     DB0,  CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "操作电源掉电监视信号",     "ALM_OPBP1"},
	{EN_ALM_SGZ           ,     EN_PARA_ENA_SGZ,       EN_PARA_T_SGZ,         0,         CN_T1S,     0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "事故总",                 "ALM_SGZ"},
	{EN_ALM_SXBYZ         ,     EN_PARA_SXBYZ_YX,      EN_PARA_T_SXBYZ,       0,         CN_T1S,     DB0,  CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "三相不一致",               "ALM_SXBYZ"},
	{EN_ALM_BSCH_OTH      ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "至另一套采执闭锁重合闸",    "ALM_BSCH_OTH"},
	{EN_ALM_BSCH          ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "闭锁本套保护重合闸",           "ALM_BSCH"},
	
	{EN_ALM_BS_LINKQH     ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "闭锁级联切换功能",            "ALM_BS_LINKQH"},
	{EN_ALM_BS_VQH        ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "闭锁电压切换功能",            "ALM_BS_VQH"},
	{EN_ALM_BS_DO         ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "闭锁出口",                "ALM_BS_DO"},
	{EN_ALM_GOOSE         ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         DB0,  CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOOSE总告警",            "ALM_GOOSE"},
	{EN_ALM_GOOSE_TEST    ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOOSE检修不一致",          "ALM_GOOSE_TEST"},

	{EN_ALM_GOCB01_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB01数据异常",    "ALM_GOCB01_DATA"},
	{EN_ALM_GOCB02_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB02数据异常",    "ALM_GOCB02_DATA"},
	{EN_ALM_GOCB03_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB03数据异常",    "ALM_GOCB03_DATA"},
	{EN_ALM_GOCB04_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB04数据异常",    "ALM_GOCB04_DATA"},
	{EN_ALM_GOCB05_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB05数据异常",    "ALM_GOCB05_DATA"},
	{EN_ALM_GOCB06_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB06数据异常",    "ALM_GOCB06_DATA"},
	{EN_ALM_GOCB07_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB07数据异常",    "ALM_GOCB07_DATA"},
	{EN_ALM_GOCB08_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB08数据异常",    "ALM_GOCB08_DATA"},
	{EN_ALM_GOCB09_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB09数据异常",    "ALM_GOCB09_DATA"},
	{EN_ALM_GOCB10_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB10数据异常",    "ALM_GOCB10_DATA"},
	{EN_ALM_GOCB11_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB11数据异常",    "ALM_GOCB11_DATA"},
	{EN_ALM_GOCB12_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB12数据异常",    "ALM_GOCB12_DATA"},
	
	{EN_ALM_GOCB01_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB01检修不一致",    "ALM_GOCB01_TEST"},
	{EN_ALM_GOCB02_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB02检修不一致",    "ALM_GOCB02_TEST"},
	{EN_ALM_GOCB03_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB03检修不一致",    "ALM_GOCB03_TEST"},
	{EN_ALM_GOCB04_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB04检修不一致",    "ALM_GOCB04_TEST"},
	{EN_ALM_GOCB05_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB05检修不一致",    "ALM_GOCB05_TEST"},
	{EN_ALM_GOCB06_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB06检修不一致",    "ALM_GOCB06_TEST"},
	{EN_ALM_GOCB07_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB07检修不一致",    "ALM_GOCB07_TEST"},
	{EN_ALM_GOCB08_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB08检修不一致",    "ALM_GOCB08_TEST"},
	{EN_ALM_GOCB09_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB09检修不一致",    "ALM_GOCB09_TEST"},
	{EN_ALM_GOCB10_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB10检修不一致",    "ALM_GOCB10_TEST"},
	{EN_ALM_GOCB11_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB11检修不一致",    "ALM_GOCB11_TEST"},
	{EN_ALM_GOCB12_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB12检修不一致",    "ALM_GOCB12_TEST"},
	{EN_ALM_GOCB01_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB01网络风暴",    "ALM_GOCB01_STORM"},
	{EN_ALM_GOCB02_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB02网络风暴",    "ALM_GOCB02_STORM"},
	{EN_ALM_GOCB03_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB03网络风暴",    "ALM_GOCB03_STORM"},
	{EN_ALM_GOCB04_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB04网络风暴",    "ALM_GOCB04_STORM"},
	{EN_ALM_GOCB05_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB05网络风暴",    "ALM_GOCB05_STORM"},
	{EN_ALM_GOCB06_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB06网络风暴",    "ALM_GOCB06_STORM"},
	{EN_ALM_GOCB07_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB07网络风暴",    "ALM_GOCB07_STORM"},
	{EN_ALM_GOCB08_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB08网络风暴",    "ALM_GOCB08_STORM"},
	{EN_ALM_GOCB09_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB09网络风暴",    "ALM_GOCB09_STORM"},
	{EN_ALM_GOCB10_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB10网络风暴",    "ALM_GOCB10_STORM"},
	{EN_ALM_GOCB11_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB11网络风暴",    "ALM_GOCB11_STORM"},
	{EN_ALM_GOCB12_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB12网络风暴",    "ALM_GOCB12_STORM"},
	{EN_ALM_CCD_SVSUB    ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "SV订阅配置异常",        "ALM_CCD_SVSUB"},
	{EN_ALM_CCD_SVPUB    ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "SV发布配置异常",        "ALM_CCD_SVPUB"},
	{EN_ALM_CCD_GOSUB    ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOOSE订阅配置异常",      "ALM_CCD_GOSUB"},
	{EN_ALM_CCD_GOPUB    ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOOSE发布配置异常",      "ALM_CCD_GOPUB"},
	{EN_ALM_BOARD_CPU2   ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "CPU2告警总",     "ALM_BOARD_CPU2"},
	{EN_ALM_BAK01        ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用告警01",      "ALM_BAK01"},
	{EN_ALM_BAK02        ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用告警02",      "ALM_BAK02"},
	{EN_ALM_BAK03        ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用告警03",      "ALM_BAK03"},
	{EN_ALM_BAK04        ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用告警04",      "ALM_BAK04"},
	{EN_ALM_BAK05        ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用告警05",      "ALM_BAK05"},
	{EN_ALM_BAK06        ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用告警06",      "ALM_BAK06"},
	{EN_ALM_BAK07        ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用告警07",      "ALM_BAK07"},
	{EN_ALM_BAK08        ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用告警08",      "ALM_BAK08"},
	{EN_ALM_BAK09        ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用告警09",      "ALM_BAK09"},
	{EN_ALM_BAK10        ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用告警10",      "ALM_BAK10"},
};
const DWORD g_NUM_ALM = sizeof(g_tAlmTab) / sizeof(tagAlmTab);
//================================================================================
// 自检常量表
//  WORD            wIndex;            // 记录枚举
//  DWORD           dwActCnt;          // 默认时间参数
//  DWORD           dwRetCnt;          // 默认返回时间参数
//  WORD            wCfg;              // 其他设置:NULL--无设置  DB0--装置故障、灭运行灯,DB1 装置总闭锁
//  WORD            wValType1;         // 事项记录数据类型1
//  WORD            wValType2;         // 事项记录数据类型2
//  WORD            wValType3;         // 事项记录数据类型3
//  INT8S           byName[CN_LEN_NAME];        // 记录名称
//  INT8S           byPinName[CN_LEN_NAME];     // 虚端子名称
//================================================================================
const tagChkTab g_tChkTab[ ] =
{
	{EN_CHK_CONST         ,       0          ,    0         ,    DB0+DB1,EN_MEA_DTYPE ,  EN_MEA_FLAG  ,EN_MEA_INDEX ,  "应用侧常量表自检",             "CHK_CONST"},
	{EN_CHK_RAM_ERR       ,       0          ,    0         ,    DB0+DB1,EN_MEA_PTR   ,  EN_MEA_INDEX ,CN_NULL_PINNO,  "应用侧内存溢出",              "CHK_RAM_ERR"},
	{EN_CHK_RAM_ALLOC     ,       0          ,    0         ,    DB0+DB1,CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "平台侧内存申请异常",            "CHK_RAM_ALLOC"},
	{EN_CHK_RAM_CHK       ,       0          ,    0         ,    DB0+DB1,CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "平台侧内存自检异常",            "CHK_RAM_CHK"},
	{EN_CHK_CCD_NO        ,       0          ,    0         ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CCD文件不存在",             "CHK_CCD_NO"},
	{EN_CHK_CCD_ERR       ,       0          ,    0         ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CCD文件解析异常",             "CHK_CCD_ERR"},
	{EN_CHK_CCD_PARALOSE  ,       0          ,    0         ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CCD文件中配置参数缺失",          "CHK_CCD_PARALOSE"},
	{EN_CHK_CCD_PARAERR   ,       0          ,    0         ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CCD文件中配置参数错误",          "CHK_CCD_PARAERR"},
	{EN_CHK_CCD_CRC       ,       0          ,    0         ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CCD文件中CRC校验码错误",        "CHK_CCD_CRC"},
	{EN_CHK_CCD_FRAME     ,       0          ,    0         ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CCD文件中配置帧长越限",        "CHK_CCD_FRAME"},
	{EN_CHK_CCD_ADDRERR   ,       0          ,    0         ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CCD文件中短地址配置错误",             "CHK_CCD_ADDRERR"},
	{EN_CHK_CCD_NUMERR    ,       0          ,    0         ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CCD文件中控制块个数越限",             "CHK_CCD_NUMERR"},
	{EN_CHK_CCD_CFGERR    ,       0          ,    0         ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CCD文件中其他配置错误",              "CHK_CCD_CFGERR"},
//	{EN_CHK_CCD_SVSUB     ,       0          ,    0         ,    DB0,    EN_MEA_FLAG,    CN_NULL_PINNO,CN_NULL_PINNO,  "CCD文件中SV订阅解析异常",            "CHK_CCD_SVSUB"},
//	{EN_CHK_CCD_SVPUB     ,       0          ,    0         ,    DB0,    EN_MEA_FLAG,    CN_NULL_PINNO,CN_NULL_PINNO,  "CCD文件中SV发布解析异常",            "CHK_CCD_SVPUB"},
//	{EN_CHK_CCD_GOSUB     ,       0          ,    0         ,    DB0,    EN_MEA_FLAG,    CN_NULL_PINNO,CN_NULL_PINNO,  "CCD文件中GOOSE订阅解析异常",         "CHK_CCD_GOSUB"},
//	{EN_CHK_CCD_GOPUB     ,       0          ,    0         ,    DB0,    EN_MEA_FLAG,    CN_NULL_PINNO,CN_NULL_PINNO,  "CCD文件中GOOSE发布解析异常",         "CHK_CCD_GOPUB"},
	{EN_CHK_DO1_RTN0      ,       4000       ,    4000      ,    DB0,    EN_MEA_INDEX,   CN_NULL_PINNO,CN_NULL_PINNO,  "开出板1控分返校自检",          "CHK_DO1_RTN0"},
#if(CN_SOFT_VER_CPU==CN_SOFT_CPU_NANJING)
	{EN_CHK_DO2_RTN0      ,       4000       ,    4000      ,    0  ,    EN_MEA_INDEX,   CN_NULL_PINNO,CN_NULL_PINNO,  "开出板2控分返校自检",          "CHK_DO2_RTN0"},
	{EN_CHK_DIO_RTN0      ,       4000       ,    4000      ,    0  ,    EN_MEA_INDEX,   CN_NULL_PINNO,CN_NULL_PINNO,  "开入开出板控分返校自检",          "CHK_DIO_RTN0"},
#else
	{EN_CHK_DO2_RTN0      ,       4000       ,    4000      ,    DB0,    EN_MEA_INDEX,   CN_NULL_PINNO,CN_NULL_PINNO,  "开出板2控分返校自检",          "CHK_DO2_RTN0"},
	{EN_CHK_DIO_RTN0      ,       4000       ,    4000      ,    DB0,    EN_MEA_INDEX,   CN_NULL_PINNO,CN_NULL_PINNO,  "开入开出板控分返校自检",          "CHK_DIO_RTN0"},
#endif
	{EN_CHK_DO1_RTN1      ,       4000       ,    4000      ,    DB0,    EN_MEA_INDEX,   CN_NULL_PINNO,CN_NULL_PINNO,  "开出板1控合返校自检",          "CHK_DO1_RTN1"},
#if(CN_SOFT_VER_CPU==CN_SOFT_CPU_NANJING)
	{EN_CHK_DO2_RTN1      ,       4000       ,    4000      ,    0  ,    EN_MEA_INDEX,   CN_NULL_PINNO,CN_NULL_PINNO,  "开出板2控合返校自检",          "CHK_DO2_RTN1"},
	{EN_CHK_DIO_RTN1      ,       4000       ,    4000      ,    0  ,    EN_MEA_INDEX,   CN_NULL_PINNO,CN_NULL_PINNO,  "开入开出板控合返校自检",          "CHK_DIO_RTN1"},
#else
	{EN_CHK_DO2_RTN1      ,       4000       ,    4000      ,    DB0,    EN_MEA_INDEX,   CN_NULL_PINNO,CN_NULL_PINNO,  "开出板2控合返校自检",          "CHK_DO2_RTN1"},
	{EN_CHK_DIO_RTN1      ,       4000       ,    4000      ,    DB0,    EN_MEA_INDEX,   CN_NULL_PINNO,CN_NULL_PINNO,  "开入开出板控合返校自检",          "CHK_DIO_RTN1"},
#endif
//	{EN_CHK_BOARD_DO1_CHN1,       10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "开出板1通道1自检",            "CHK_BOARD_DO1_CHN1"},
//	{EN_CHK_BOARD_DO2_CHN1,       10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "开出板2通道1自检",            "CHK_BOARD_DO2_CHN1"},
//	{EN_CHK_BOARD_DIO_CHN1,       10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "开入开出板通道1自检",           "CHK_BOARD_DIO_CHN1"},
//	{EN_CHK_BOARD_DO1_CHN2,       10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "开出板1通道2自检",            "CHK_BOARD_DO1_CHN2"},
//	{EN_CHK_BOARD_DO2_CHN2,       10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "开出板2通道2自检",            "CHK_BOARD_DO2_CHN2"},
//	{EN_CHK_BOARD_DIO_CHN2,       10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "开入开出板通道2自检",           "CHK_BOARD_DIO_CHN2"},
//	{EN_CHK_BOARD_DO1_POW24,      10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "开出板1电源24V自检",            "CHK_BOARD_DO1_POW24"},
//	{EN_CHK_BOARD_DO2_POW24,      10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "开出板2电源24V自检",            "CHK_BOARD_DO2_POW24"},
//	{EN_CHK_BOARD_DIO_POW24,      10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "开入开出板电源24V自检",           "CHK_BOARD_DIO_POW24"},
	{EN_CHK_BOARD_DO1_POW30,      5000       ,    500       ,    0  ,    EN_MEA_FLAG16,  CN_NULL_PINNO,CN_NULL_PINNO,  "开出板1电源30V自检",            "CHK_BOARD_DO1_POW30"},
	{EN_CHK_BOARD_DO2_POW30,      5000       ,    500       ,    0  ,    EN_MEA_FLAG16,  CN_NULL_PINNO,CN_NULL_PINNO,  "开出板2电源30V自检",            "CHK_BOARD_DO2_POW30"},
	{EN_CHK_BOARD_DIO_POW30,      5000       ,    500       ,    0  ,    EN_MEA_FLAG16,  CN_NULL_PINNO,CN_NULL_PINNO,  "开入开出板电源30V自检",           "CHK_BOARD_DIO_POW30"},
//	{EN_CHK_BOARD_DO1_PARA ,      10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "开出板1参数自检",               "CHK_BOARD_DO1_PARA"},
//	{EN_CHK_BOARD_DO2_PARA ,      10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "开出板2参数自检",               "CHK_BOARD_DO2_PARA"},
//	{EN_CHK_BOARD_DIO_PARA ,      10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "开入开出板参数自检",              "CHK_BOARD_DIO_PARA"},
	{EN_CHK_PARA_DI       ,       10000      ,    1000      ,    DB0,    EN_MEA_FLAG ,   CN_NULL_PINNO,CN_NULL_PINNO,  "开入量参数自检",             "CHK_PARA_DI"},
	{EN_CHK_PARA_DC       ,       10000      ,    1000      ,    DB0,    EN_MEA_FLAG ,   CN_NULL_PINNO,CN_NULL_PINNO,  "直流量参数自检",             "CHK_PARA_DC"},
	{EN_CHK_PARA_SAM      ,       10000      ,    1000      ,    DB0,    EN_MEA_FLAG ,   CN_NULL_PINNO,CN_NULL_PINNO,  "模拟量参数自检",             "CHK_PARA_SAM"},
	{EN_CHK_PARA_FUN      ,       10000      ,    1000      ,    DB0,    EN_MEA_FLAG ,   CN_NULL_PINNO,CN_NULL_PINNO,  "功能参数自检",              "CHK_PARA_FUN"},
	{EN_CHK_PARA_DC_COE   ,       10000      ,    1000      ,    DB0,    EN_MEA_FLAG ,   CN_NULL_PINNO,CN_NULL_PINNO,  "直流量校准系数自检",           "CHK_PARA_DC_COE"},
	{EN_CHK_PARA_AM_COE   ,       10000      ,    1000      ,    DB0,    EN_MEA_FLAG ,   CN_NULL_PINNO,CN_NULL_PINNO,  "模拟量校准系数自检",           "CHK_PARA_AM_COE"},
	{EN_CHK_PARA_DCBC_COE ,       10000      ,    1000      ,    DB0,    EN_MEA_FLAG ,   CN_NULL_PINNO,CN_NULL_PINNO,  "模拟量直流补偿自检",           "CHK_PARA_DCBC_COE"},
	{EN_CHK_PARA_ANG_COE  ,       10000      ,    1000      ,    DB0,    EN_MEA_FLAG ,   CN_NULL_PINNO,CN_NULL_PINNO,  "模拟量相位补偿自检",           "CHK_PARA_ANG_COE"},
	{EN_CHK_PARA_DI_HLD   ,       0          ,    0         ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "去颤时间设置错误自检",          "CHK_PARA_DI_HLD"},
	{EN_CHK_BOARD_DI1     ,       5000       ,    500       ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "开入板1自检",              "CHK_BOARD_DI1"},
	{EN_CHK_BOARD_DI2     ,       5000       ,    500       ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "开入板2自检",              "CHK_BOARD_DI2"},
#if(CN_SOFT_VER_CPU==CN_SOFT_CPU_NANJING)
	{EN_CHK_BOARD_DI3     ,       5000       ,    500       ,    0  ,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "开入板3自检",              "CHK_BOARD_DI3"},
	{EN_CHK_BOARD_DIO_DI  ,       5000       ,    500       ,    0  ,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "开入开出板开入自检",           "CHK_BOARD_DIO_DI"},
#else
	{EN_CHK_BOARD_DI3     ,       5000       ,    500       ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "开入板3自检",              "CHK_BOARD_DI3"},
	{EN_CHK_BOARD_DIO_DI  ,       5000       ,    500       ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "开入开出板开入自检",           "CHK_BOARD_DIO_DI"},
#endif
    {EN_CHK_BOARD_OPB1    ,       5000       ,    500       ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "操作回路板自检",             "CHK_BOARD_OPB1"},
	{EN_CHK_BOARD_DO1     ,       5000       ,    500       ,    DB0,    EN_MEA_FLAG16,  CN_NULL_PINNO,CN_NULL_PINNO,  "开出板1自检",              "CHK_BOARD_DO1"},
#if(CN_SOFT_VER_CPU==CN_SOFT_CPU_NANJING)
	{EN_CHK_BOARD_DO2     ,       5000       ,    500       ,    0  ,    EN_MEA_FLAG16,  CN_NULL_PINNO,CN_NULL_PINNO,  "开出板2自检",              "CHK_BOARD_DO2"},
	{EN_CHK_BOARD_DIO_DO  ,       5000       ,    500       ,    0  ,    EN_MEA_FLAG16,  CN_NULL_PINNO,CN_NULL_PINNO,  "开入开出板开出自检",           "CHK_BOARD_DIO_DO"},
	{EN_CHK_BOARD_DC_SAM  ,       400        ,    100       ,    0  ,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "直流板自检",                "CHK_BOARD_DC_SAM"},
#else
	{EN_CHK_BOARD_DO2     ,       5000       ,    500       ,    DB0,    EN_MEA_FLAG16,  CN_NULL_PINNO,CN_NULL_PINNO,  "开出板2自检",              "CHK_BOARD_DO2"},
	{EN_CHK_BOARD_DIO_DO  ,       5000       ,    500       ,    DB0,    EN_MEA_FLAG16,  CN_NULL_PINNO,CN_NULL_PINNO,  "开入开出板开出自检",           "CHK_BOARD_DIO_DO"},
	{EN_CHK_BOARD_DC_SAM  ,       400        ,    100       ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "直流板自检",                "CHK_BOARD_DC_SAM"},
#endif
	{EN_CHK_BOARD_DC_DEV  ,       400        ,    100       ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "状态监视自检",               "CHK_BOARD_DC_DEV"},
	{EN_CHK_BOARD_DC_OPT1_1,      400        ,    100       ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CPU1板光功率帧自检",          "CHK_BOARD_DC_OPT1_1"},
	{EN_CHK_BOARD_DC_OPT1_2,      400        ,    100       ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CPU1背板光功率帧自检",         "CHK_BOARD_DC_OPT1_2"},
	{EN_CHK_BOARD_DC_OPT2 ,       400        ,    100       ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CPU2板光功率帧自检",          "CHK_BOARD_DC_OPT2"},
	{EN_CHK_BOARD_PTCT1   ,       40000      ,    4000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "PTCT板1自检",             "CHK_BOARD_PTCT1"},
	{EN_CHK_BOARD_PTCT2   ,       40000      ,    4000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "PTCT板2自检",             "CHK_BOARD_PTCT2"},
	{EN_CHK_BOARD_CPU     ,       40000      ,    4000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CPU板AD自检",             "CHK_BOARD_CPU"},
	{EN_CHK_BOARD_CPU_AUX ,       10         ,    10        ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CPU背板自检",              "CHK_BOARD_CPU_AUX"},
	{EN_CHK_BOARD_POW     ,       40000      ,    4000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "电源掉电监视长期存在",           "CHK_BOARD_POW"},
	{EN_CHK_BOARD_CPU2    ,       0          ,    0         ,    0  ,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CPU2板自检总",             "CHK_BOARD_CPU2"},
	{EN_CHK_BOARD_LED     ,       10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "LED板自检",               "CHK_BOARD_LED"},
	{EN_CHK_FRAME_ANA     ,       10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "模拟量帧自检",               "CHK_FRAME_ANA"},
#if(CN_SOFT_VER_CPU==CN_SOFT_CPU_NANJING)
	{EN_CHK_CPUCOM_FAST   ,       10000      ,    1000      ,    0  ,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "双CPU通信自检",             "CHK_CPUCOM_SLOW"},
	{EN_CHK_CPUCOM_PARA   ,       4          ,    4         ,    0  ,    EN_MEA_FLAG16,  CN_NULL_PINNO,CN_NULL_PINNO,  "双CPU参数CRC不一致",         "CHK_CPUCOM_PARA"},
	{EN_CHK_CPUCOM_VER    ,       0          ,    0         ,    0  ,    EN_MEA_FLAG16,  EN_MEA_FLAG16,CN_NULL_PINNO,  "双CPU版本信息不一致",          "CHK_CPUCOM_VER"},
	{EN_CHK_CPUCOM_CCD    ,       0          ,    0         ,    0  ,    EN_MEA_FLAG  ,  EN_MEA_FLAG  ,CN_NULL_PINNO,  "双CPU配置CRC不一致",         "CHK_CPUCOM_CCD"},
#else
	{EN_CHK_CPUCOM_FAST   ,       10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "双CPU通信自检",             "CHK_CPUCOM_SLOW"},
	{EN_CHK_CPUCOM_PARA   ,       4          ,    4         ,    DB0,    EN_MEA_FLAG16,  CN_NULL_PINNO,CN_NULL_PINNO,  "双CPU参数CRC不一致",         "CHK_CPUCOM_PARA"},
	{EN_CHK_CPUCOM_VER    ,       0          ,    0         ,    DB0,    EN_MEA_FLAG16,  EN_MEA_FLAG16,CN_NULL_PINNO,  "双CPU版本信息不一致",          "CHK_CPUCOM_VER"},
	{EN_CHK_CPUCOM_CCD    ,       0          ,    0         ,    DB0,    EN_MEA_FLAG  ,  EN_MEA_FLAG  ,CN_NULL_PINNO,  "双CPU配置CRC不一致",         "CHK_CPUCOM_CCD"},
#endif
	
	{EN_CHK_BAK01         ,        0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用自检01",      "CHK_BAK01"},
	{EN_CHK_BAK02         ,        0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用自检02",      "CHK_BAK02"},
	{EN_CHK_BAK03         ,        0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用自检03",      "CHK_BAK03"},
	{EN_CHK_BAK04         ,        0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用自检04",      "CHK_BAK04"},
	{EN_CHK_BAK05         ,        0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用自检05",      "CHK_BAK05"},
	{EN_CHK_BAK06         ,        0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用自检06",      "CHK_BAK06"},
	{EN_CHK_BAK07         ,        0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用自检07",      "CHK_BAK07"},
	{EN_CHK_BAK08         ,        0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用自检08",      "CHK_BAK08"},
	{EN_CHK_BAK09         ,        0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用自检09",      "CHK_BAK09"},
	{EN_CHK_BAK10         ,        0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用自检10",      "CHK_BAK10"},
};
const DWORD g_NUM_CHK = sizeof(g_tChkTab) / sizeof(tagChkTab);
//================================================================================
// 运行常量表
//	WORD			wIndex; 			   // 记录枚举
//	WORD			wCfg;				   // 其他设置
//	INT8S			byName[CN_LEN_NAME];   // 记录名称
//	INT8S			byPinName[CN_LEN_NAME];// 虚端子名称
//================================================================================
const tagRunTab g_tRunTab[ ] =
{
	{EN_RUN_POW_ON      ,  0,    "装置上电"   ,              "RUN_POW_ON"},
	{EN_RUN_POW_OFF     ,  0,    "装置掉电",                 "RUN_POW_OFF"},
	{EN_RUN_SVPUB_ENA   ,  0,    "SV发布使能",               "RUN_SVPUB_ENA"},
	{EN_RUN_GOPUB_ENA   ,  0,    "GOOSE发布使能",            "RUN_GOPUB_ENA"},
	{EN_RUN_SVPUB_BS    ,  0,    "SV发布闭锁",               "RUN_SVPUB_BS"},
	{EN_RUN_GOPUB_BS    ,  0,    "GOOSE发布闭锁",            "RUN_GOPUB_BS"},
	{EN_RUN_POL         ,  0,    "极性修改下发",               "RUN_POL"},
	{EN_RUN_LNKQH_S     ,  0,    "级联切换下发",               "RUN_LNKQH_S"},
	{EN_RUN_VQH_S       ,  0,    "电压切换下发",               "RUN_VQH_S"},
	{EN_RUN_UX_S        ,  0,    "线电压设置下发",             "RUN_UX_S"},
	{EN_RUN_COM_S       ,  0,    "板间挑数设置下发",           "RUN_COM_S"},
	{EN_RUN_AM_COE_S    ,  0,    "模拟量校准系数下发",      "RUN_AM_COE_S"},
	{EN_RUN_DCBC_COE_S  ,  0,    "模拟量直流补偿下发",      "RUN_DCBC_COE_S"},
	{EN_RUN_ANG_COE_S   ,  0,    "模拟量相位补偿下发",      "RUN_ANG_COE_S"},
	
	{EN_RUN_PARASYN_S_STR+EN_BOARD_PARA_DI    ,  0,    "开入量参数同步成功",             "RUN_PARASYN_DI_S"},
	{EN_RUN_PARASYN_S_STR+EN_BOARD_PARA_DC    ,  0,    "直流量参数同步成功",             "RUN_PARASYN_DC_S"},
	{EN_RUN_PARASYN_S_STR+EN_BOARD_PARA_SAM   ,  0,    "模拟量参数同步成功",             "RUN_PARASYN_SAM_S"},
	{EN_RUN_PARASYN_S_STR+EN_BOARD_PARA_FUN   ,  0,    "功能参数同步成功",              "RUN_PARASYN_FUN_S"},
	{EN_RUN_PARASYN_S_STR+EN_BOARD_PARA_DC_COE,  0,    "直流校准系数同步成功",            "RUN_PARASYN_DC_COE_S"},
	
	{EN_RUN_PARASYN_F_STR+EN_BOARD_PARA_DI    ,  0,    "开入量参数同步失败",             "RUN_PARASYN_DI_F"},
	{EN_RUN_PARASYN_F_STR+EN_BOARD_PARA_DC    ,  0,    "直流量参数同步失败",             "RUN_PARASYN_DC_F"},
	{EN_RUN_PARASYN_F_STR+EN_BOARD_PARA_SAM   ,  0,    "模拟量参数同步失败",             "RUN_PARASYN_SAM_F"},
	{EN_RUN_PARASYN_F_STR+EN_BOARD_PARA_FUN   ,  0,    "功能参数同步失败",              "RUN_PARASYN_FUN_F"},
	{EN_RUN_PARASYN_F_STR+EN_BOARD_PARA_DC_COE,  0,    "直流校准系数同步失败",            "RUN_PARASYN_DC_COE_F"},

	{EN_RUN_BAK01           ,  0,    "备用运行01",            "RUN_BAK01"},
	{EN_RUN_BAK02           ,  0,    "备用运行02",            "RUN_BAK02"},
	{EN_RUN_BAK03           ,  0,    "备用运行03",            "RUN_BAK03"},
	{EN_RUN_BAK04           ,  0,    "备用运行04",            "RUN_BAK04"},
	{EN_RUN_BAK05           ,  0,    "备用运行05",            "RUN_BAK05"},
	{EN_RUN_BAK06           ,  0,    "备用运行06",            "RUN_BAK06"},
	{EN_RUN_BAK07           ,  0,    "备用运行07",            "RUN_BAK07"},
	{EN_RUN_BAK08           ,  0,    "备用运行08",            "RUN_BAK08"},
	{EN_RUN_BAK09           ,  0,    "备用运行09",            "RUN_BAK09"},
	{EN_RUN_BAK10           ,  0,    "备用运行10",            "RUN_BAK10"},
};
const DWORD g_NUM_RUN = sizeof(g_tRunTab) / sizeof(tagRunTab);

//================================================================================
// 操作常量表
//  WORD            wIndex;                // 记录枚举
//  WORD            wCfg;                  // 其他设置
//  WORD            wValType1;             // 事项记录数据类型1
//  WORD            wValType2;             // 事项记录数据类型2
//  WORD            wValType3;             // 事项记录数据类型3
//  INT8S           byName[CN_LEN_NAME];   // 记录名称
//  INT8S           byPinName[CN_LEN_NAME];// 虚端子名称
//================================================================================
const tagOptTab g_tOptTab[ ] =
{
	{EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_DI       ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "开关量参数修改成功"          ,        "OPT_PARA_DI_W_SUCC"    },
	{EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_DC       ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "直流量参数修改成功"          ,        "OPT_PARA_DC_W_SUCC"    },
	{EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_SAM      ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量参数修改成功"          ,        "OPT_PARA_ANA_W_SUCC"   },
	{EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_FUN      ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "功能参数修改成功"           ,        "OPT_PARA_FUN_W_SUCC"   },
	{EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_DC_COE   ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "直流量校准系数修改成功",                "OPT_PARA_DCCOE_W_SUCC"  },
	{EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_AM_COE   ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量校准系数修改成功"      ,          "OPT_PARA_AMCOE_W_SUCC"  },
	{EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_DCBC_COE ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量直流补偿修改成功",                "OPT_PARA_DCBCCOE_W_SUCC"  },
	{EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_ANG_COE  ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量相位补偿修改成功",                "OPT_PARA_ANGCOE_W_SUCC"  },

	{EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_DI       ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "开关量参数修改失败"          ,        "OPT_PARA_DI_W_FAIL"    },
	{EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_DC       ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "直流量参数修改失败"          ,        "OPT_PARA_DC_W_FAIL"    },
	{EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_SAM      ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量参数修改失败"          ,        "OPT_PARA_ANA_W_FAIL"   },
	{EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_FUN      ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "功能参数修改失败"           ,        "OPT_PARA_FUN_W_FAIL"   },
	{EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_DC_COE   ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "直流量校准系数修改失败",                "OPT_PARA_DCCOE_W_FAIL"  },
	{EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_AM_COE   ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量校准系数修改失败"      ,          "OPT_PARA_AMCOE_W_FAIL"  },
	{EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_DCBC_COE ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量直流补偿修改失败",                "OPT_PARA_DCBCCOE_W_FAIL"  },
	{EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_ANG_COE  ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量相位补偿修改失败",                "OPT_PARA_ANGCOE_W_FAIL"  },
	
	{EN_OPT_PARA_INIT_SUCC_STR+EN_BOARD_PARA_DI       , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "开关量参数初始化成功"        ,         "OPT_PARA_DI_INIT_SUCC" },
	{EN_OPT_PARA_INIT_SUCC_STR+EN_BOARD_PARA_DC       , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "直流量参数初始化成功"        ,         "OPT_PARA_DC_INIT_SUCC" },
	{EN_OPT_PARA_INIT_SUCC_STR+EN_BOARD_PARA_SAM      , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量参数初始化成功"        ,         "OPT_PARA_ANA_INIT_SUCC"},
	{EN_OPT_PARA_INIT_SUCC_STR+EN_BOARD_PARA_FUN      , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "功能参数初始化成功"          ,        "OPT_PARA_FUN_INIT_SUCC"},
	{EN_OPT_PARA_INIT_SUCC_STR+EN_BOARD_PARA_DC_COE   , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "直流量校准系数初始化成功"  ,             "OPT_PARA_DCCOE_INIT_SUCC"},
	{EN_OPT_PARA_INIT_SUCC_STR+EN_BOARD_PARA_AM_COE   , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量校准系数初始化成功"    ,           "OPT_PARA_AMCOE_INIT_SUCC"},
	{EN_OPT_PARA_INIT_SUCC_STR+EN_BOARD_PARA_DCBC_COE , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量直流补偿初始化成功"  ,             "OPT_PARA_DCBCCOE_INIT_SUCC"},
	{EN_OPT_PARA_INIT_SUCC_STR+EN_BOARD_PARA_ANG_COE  , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量相位补偿初始化成功"  ,             "OPT_PARA_ANGCOE_INIT_SUCC"},
	{EN_OPT_PARA_INIT_FAIL_STR+EN_BOARD_PARA_DI       , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "开关量参数初始化失败"        ,         "OPT_PARA_DI_INIT_FAIL" },
	{EN_OPT_PARA_INIT_FAIL_STR+EN_BOARD_PARA_DC       , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "直流量参数初始化失败"        ,         "OPT_PARA_DC_INIT_FAIL" },
	{EN_OPT_PARA_INIT_FAIL_STR+EN_BOARD_PARA_SAM      , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量参数初始化失败"        ,         "OPT_PARA_ANA_INIT_FAIL"},
	{EN_OPT_PARA_INIT_FAIL_STR+EN_BOARD_PARA_FUN      , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "功能参数初始化失败"          ,        "OPT_PARA_FUN_INIT_FAIL"},
	{EN_OPT_PARA_INIT_FAIL_STR+EN_BOARD_PARA_DC_COE   , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "直流量校准系数初始化失败"  ,             "OPT_PARA_DCCOE_INIT_FAIL"},
	{EN_OPT_PARA_INIT_FAIL_STR+EN_BOARD_PARA_AM_COE   , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量校准系数初始化失败"    ,           "OPT_PARA_AMCOE_INIT_FAIL"},
	{EN_OPT_PARA_INIT_FAIL_STR+EN_BOARD_PARA_DCBC_COE , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量直流补偿初始化失败"  ,             "OPT_PARA_DCBCCOE_INIT_FAIL"},
	{EN_OPT_PARA_INIT_FAIL_STR+EN_BOARD_PARA_ANG_COE  , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量相位补偿初始化失败",               "OPT_PARA_ANGCOE_INIT_FAIL"},

	{EN_OPT_ADJ_DCBC_SUCC     ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量直流补偿校准成功",                "OPT_ADJ_DCBC_SUCC"    },
	{EN_OPT_ADJ_DCBC_FAIL     ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量直流补偿校准失败",                "OPT_ADJ_DCBC_FAIL"    },
	{EN_OPT_ADJ_AM_SUCC       ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量幅值系数校准成功"    ,            "OPT_ADJ_AM_SUCC"      },
	{EN_OPT_ADJ_AM_FAIL       ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量幅值系数校准失败"    ,            "OPT_ADJ_AM_FAIL"      },
	{EN_OPT_ADJ_ANG_SUCC      ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量相位补偿校准成功"    ,            "OPT_ADJ_ANG_SUCC"     },
	{EN_OPT_ADJ_ANG_FAIL      ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "交流量相位补偿校准失败"    ,            "OPT_ADJ_ANG_FAIL"     },
	{EN_OPT_ADJ_DC_SUCC       ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "直流量系数校准成功"          ,        "OPT_ADJ_DC_SUCC"       },
	{EN_OPT_ADJ_DC_FAIL       ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "直流量系数校准失败"          ,        "OPT_ADJ_DC_FAIL"       },
	{EN_OPT_DEBUG_IN          ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "装置调试态进入"               ,     "OPT_DEBUG_IN"           },
	{EN_OPT_DEBUG_OUT         ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "装置调试态退出"               ,     "OPT_DEBUG_OUT"          },

	{EN_OPT_FACT_DEBUG_IN     ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "厂家调试态进入"               ,     "OPT_FACT_DEBUG_IN"      },
	{EN_OPT_FACT_DEBUG_OUT    ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "厂家调试态退出"               ,     "OPT_FACT_DEBUG_OUT"     },

	{EN_OPT_DEBUG_LED         ,      0,    EN_MEA_INDEX,  CN_NULL_PINNO,  CN_NULL_PINNO,  "指示灯调试"                 ,     "OPT_DEBUG_LED"          },
	{EN_OPT_DEBUG_DO          ,      0,    EN_MEA_INDEX ,  CN_NULL_PINNO,  CN_NULL_PINNO,  "出口传动调试"                ,     "OPT_DEBUG_DO"           },

	{EN_OPT_DEBUG_GO_S        ,      0,    EN_MEA_INDEX ,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOOSE单点出口调试"           ,     "OPT_DEBUG_GO_S"         },
	{EN_OPT_DEBUG_GO_Dp       ,      0,    EN_MEA_INDEX ,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOOSE双点出口调试"           ,     "OPT_DEBUG_GO_Dp"         },
	{EN_OPT_DEBUG_GO_DC       ,      0,    EN_MEA_INDEX ,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOOSE模拟量调试"            ,     "OPT_DEBUG_GO_DC"        },

	{EN_OPT_ACT_DEl           ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "清除GOOSE命令事项"      ,          "OPT_ACT_DEl"},
	{EN_OPT_ALM_DEl           ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "清除告警事项"        ,             "OPT_ALM_DEl"},
	{EN_OPT_CHK_DEl           ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "清除自检事项"        ,             "OPT_CHK_DEl"},
	{EN_OPT_DI_SOE_DEl        ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "清除硬开入SOE事项"    ,             "OPT_DI_SOE_DEl"},
	{EN_OPT_DO_SOE_DEl        ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "清除硬开出SOE事项"    ,             "OPT_DO_SOE_DEl"},
	{EN_OPT_GOIN_SOE_DEl      ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "清除GOOSE开入SOE事项" ,           "OPT_GOIN_SOE_DEl"},
	{EN_OPT_GOOUT_SOE_DEl     ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "清除GOOSE开出SOE事项" ,           "OPT_GOOUT_SOE_DEl"},
	{EN_OPT_LED_SOE_DEl       ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "清除指示灯SOE事项" ,               "OPT_LED_SOE_DEl"},
	{EN_OPT_DPI_SOE_DEl       ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "清除双点遥信SOE事项" ,               "OPT_DPI_SOE_DEl"},
	{EN_OPT_FLAG_SOE_DEl      ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "清除虚遥信SOE事项"   ,               "OPT_FLAG_SOE_DEl"},
	{EN_OPT_TIME_W_SUCC       ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "时钟修改成功"        ,             "OPT_TIME_W_SUCC"},
	{EN_OPT_TIME_W_FAIL       ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "时钟修改失败"        ,             "OPT_TIME_W_FAIL"},

	{EN_OPT_BAK01             ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用操作01"        ,             "OPT_BAK01"},
	{EN_OPT_BAK02             ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用操作02"        ,             "OPT_BAK02"},
	{EN_OPT_BAK03             ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用操作03"        ,             "OPT_BAK03"},
	{EN_OPT_BAK04             ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用操作04"        ,             "OPT_BAK04"},
	{EN_OPT_BAK05             ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用操作05"        ,             "OPT_BAK05"},
	{EN_OPT_BAK06             ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用操作06"        ,             "OPT_BAK06"},
	{EN_OPT_BAK07             ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用操作07"        ,             "OPT_BAK07"},
	{EN_OPT_BAK08             ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用操作08"        ,             "OPT_BAK08"},
	{EN_OPT_BAK09             ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用操作09"        ,             "OPT_BAK09"},
	{EN_OPT_BAK10             ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "备用操作10"        ,             "OPT_BAK10"},
};
const DWORD g_NUM_OPT = sizeof(g_tOptTab) / sizeof(tagOptTab);
//================================================================================
// 内部事项常量表
//  WORD            wIndex;                // 记录枚举
//  WORD            wCfg;                  // 其他设置
//  INT8S           byName[CN_LEN_NAME];   // 记录名称
//  INT8S           byPinName[CN_LEN_NAME];// 虚端子名称
//================================================================================
const tagPrvtSoeTab g_tPrvtSoeTab[ ] =
{
	{EN_PRVT_SOE_BAK0          ,      0,    "内部事项备用"           ,     "PRVT_SOE_BAK0"},
};
const DWORD g_NUM_PRVT_SOE = sizeof(g_tPrvtSoeTab) / sizeof(tagPrvtSoeTab);
//================================================================================
// 内部操作常量表
//  WORD            wIndex;                // 记录枚举
//  WORD            wCfg;                  // 其他设置
//  INT8S           byName[CN_LEN_NAME];   // 记录名称
//  INT8S           byPinName[CN_LEN_NAME];// 虚端子名称
//================================================================================
const tagPrvtOptTab g_tPrvtOptTab[ ] =
{
	{EN_PRVT_OPT_DEV_LINK          ,      0,    "调试工具连接成功"           ,     "PRVT_OPT_DEV_LINK"     },
	{EN_PRVT_OPT_DEV_BREAK         ,      0,    "调试工具连接中断"           ,     "PRVT_OPT_DEV_BREAK"    },
	{EN_PRVT_OPT_DATA_R_SUCC       ,      0,    "召唤数据成功"             ,     "PRVT_OPT_DATA_R_SUCC"  },
	{EN_PRVT_OPT_DATA_R_FAIL       ,      0,    "召唤数据失败"             ,     "PRVT_OPT_DATA_R_FAIL"  },
	{EN_PRVT_OPT_FILE_UP_SUCC      ,      0,    "文件上传成功"             ,     "PRVT_OPT_FILE_UP_SUCC" },
	{EN_PRVT_OPT_FILE_UP_FAIL      ,      0,    "文件上传失败"             ,     "PRVT_OPT_FILE_UP_FAIL"},
	{EN_PRVT_OPT_FILE_DN_SUCC      ,      0,    "文件下载成功"             ,     "PRVT_OPT_FILE_DN_SUCC"},
	{EN_PRVT_OPT_FILE_DN_FAIL      ,      0,    "文件下载失败"             ,     "PRVT_OPT_FILE_DN_FAIL"},
	{EN_PRVT_OPT_FLASH_BAK_SUCC    ,      0,    "一键备份成功"             ,     "PRVT_OPT_FLASH_BAK_SUCC"},
	{EN_PRVT_OPT_FLASH_BAK_FAIL    ,      0,    "一键备份失败"             ,     "PRVT_OPT_FLASH_BAK_FAIL"},
	{EN_PRVT_OPT_PARA_REST_SUCC    ,      0,    "参数还原成功"             ,     "PRVT_OPT_PARA_REST_SUCC"},
	{EN_PRVT_OPT_PARA_REST_FAIL    ,      0,    "参数还原失败"             ,     "PRVT_OPT_PARA_REST_FAIL"},
	{EN_PRVT_OPT_UPDATE_BOOT0_SUCC ,      0,    "BOOT0升级成功"          ,     "PRVT_OPT_UPDATE_BOOT0_SUCC"},
	{EN_PRVT_OPT_UPDATE_BOOT0_FAIL ,      0,    "BOOT0升级失败"          ,     "PRVT_OPT_UPDATE_BOOT0_FAIL"},
	{EN_PRVT_OPT_UPDATE_UBOOT_SUCC ,      0,    "UBOOT升级成功"          ,     "PRVT_OPT_UPDATE_UBOOT_SUCC"},
	{EN_PRVT_OPT_UPDATE_UBOOT_FAIL ,      0,    "UBOOT升级失败"          ,     "PRVT_OPT_UPDATE_UBOOT_FAIL"},
	{EN_PRVT_OPT_UPDATE_SYSTEM_SUCC,      0,    "SYSTEM升级成功"         ,     "PRVT_OPT_UPDATE_SYSTEM_SUCC"},
	{EN_PRVT_OPT_UPDATE_SYSTEM_FAIL,      0,    "SYSTEM升级失败"         ,     "PRVT_OPT_UPDATE_SYSTEM_FAIL"},
	{EN_PRVT_OPT_UPDATE_FPGA1_SUCC ,      0,    "FPGA1升级成功"          ,     "PRVT_OPT_UPDATE_FPGA1_SUCC"},
	{EN_PRVT_OPT_UPDATE_FPGA1_FAIL ,      0,    "FPGA1升级失败"          ,     "PRVT_OPT_UPDATE_FPGA1_FAIL"},
	{EN_PRVT_OPT_UPDATE_FPGA2_SUCC ,      0,    "FPGA2升级成功"          ,     "PRVT_OPT_UPDATE_FPGA2_SUCC"},
	{EN_PRVT_OPT_UPDATE_FPGA2_FAIL ,      0,    "FPGA2升级失败"          ,     "PRVT_OPT_UPDATE_FPGA2_FAIL"},
	{EN_PRVT_OPT_EVENT_ALL_DEl     ,      0,    "清除所有事项"          ,        "PRVT_OPT_EVENT_ALL_DEl"      },
	{EN_PRVT_OPT_RUN_DEl           ,      0,    "清除运行事项"          ,        "PRVT_OPT_RUN_DEl"},
	{EN_PRVT_OPT_OPT_DEl           ,      0,    "清除操作事项"          ,        "PRVT_OPT_OPT_DEl"},
	{EN_PRVT_OPT_PRVT_SOE_DEl      ,      0,    "清除内部事项"          ,        "PRVT_OPT_PRVT_SOE_DEl"},
	{EN_PRVT_OPT_PRVT_OPT_DEl      ,      0,    "清除内部操作"          ,        "PRVT_OPT_PRVT_OPT_DEl"},
	{EN_PRVT_OPT_ETH_W_SUCC        ,      0,    "网络参数修改成功"        ,        "PRVT_OPT_ETH_W_SUCC"},
	{EN_PRVT_OPT_ETH_W_FAIL        ,      0,    "网络参数修改失败"        ,        "PRVT_OPT_ETH_W_FAIL"},
};
const DWORD g_NUM_PRVT_OPT = sizeof(g_tPrvtOptTab) / sizeof(tagPrvtOptTab);


