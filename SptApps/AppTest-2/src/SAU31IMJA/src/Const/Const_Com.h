#ifndef _CONST_COM_H_
#define _CONST_COM_H_

#include "IES_IMtypes.h"

#define CN_TX_MAX     (512)
#define CN_RX_FRAME   (8)
// 如果板间通信有改动,请修正校验码
#define CN_CPU_SOFT_COM     (0x1000)       // CPU板间校验版本

enum _COM_TYPE
{
	EN_COM_TYPE_INIT01=0x5501,
	EN_COM_TYPE_FAST01=0x5A01,
	EN_COM_TYPE_SLOW01=0xA501,
};
// 板间交互版本信息
typedef struct
{
	WORD wVer;
	WORD wVerNum;
	WORD wSlowInitNum;
	WORD wSlow1To2Num;
	WORD wSlow2To1Num;
	WORD wFast1To2Num;
	WORD wFast2To1Num;
	WORD wBak[3];
}tagComVer;
// 板间交互组帧
typedef struct
{
	BYTE byRamScan1;
	WORD wReset;
	WORD wFlag;
	WORD wSendFlag;
	WORD wSendPtr;
	WORD wType;
	WORD wLen;
	BYTE byRamScan2;
	BYTE byData[CN_TX_MAX];
	BYTE byRamScan3;
}tagCom;
/*================================================================================*/
//慢速信息交互表结构体
/*================================================================================*/
// 模拟量常量信息表数据结构
typedef struct
{
	BYTE           *pwSrcAddr;                     // 数据源地址
	DWORD           dwSrcLen;                      // 数据长度
	BOOL           *pbSrcChg;                      // 数据源变化标志	
	BYTE           *pwDstAddr;                     // 数据目的地址
	DWORD           dwDstLen;                      // 数据长度
	BOOL           *pbDstChg;                      // 数据目的变化标志
} tagComSlowTab;
/*================================================================================*/
//快速信息交互表结构体
/*================================================================================*/
// 模拟量常量信息表数据结构
typedef struct
{
	BYTE           *pwSrcAddr;                     // 数据源地址
	BYTE           *pwDstAddr;                     // 数据目的地址
	BOOL            bSet;                          // 控制标志 0:取或 1:取与
} tagComFastTab;

/*================================================================================*/
// 变量声明
/*================================================================================*/
extern tagComVer  g_tComVer[2];       // 版本信息
extern tagCom  g_tComFastTx;          // 板间交互快速数据发送组帧
extern tagCom  g_tComSlowTx;          // 板间交互慢速数据发送组帧
extern tagCom  g_tComFastRx;          // 板间交互快速数据接收缓存
extern tagCom  g_tComSlowRx;          // 板间交互慢速数据接收缓存
extern const tagComSlowTab  g_tComInitTab[];
extern const DWORD          g_NUM_COM_INIT;
extern const tagComFastTab  g_tComFast1To2Tab[];
extern const DWORD          g_NUM_COM1TO2_FAST;
extern const tagComFastTab  g_tComFast2To1Tab[];
extern const DWORD          g_NUM_COM2TO1_FAST;
extern const tagComSlowTab  g_tComSlow1To2Tab[];
extern const DWORD          g_NUM_COM1TO2_SLOW;
extern const tagComSlowTab  g_tComSlow2To1Tab[];
extern const DWORD          g_NUM_COM2TO1_SLOW;
/*================================================================================*/
#endif /* _CONST_COM_H_ */
