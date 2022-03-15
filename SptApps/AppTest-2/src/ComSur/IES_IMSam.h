/*================================================================================
 * Copyright (C) 2020-2030  All Rights Reserved
 * 积成电子股份有限公司
 * 元件名称：采样元件
 * 元件描述：采样元件
 * 元件功能：采样数据相量计算及输出
 * 元件版本：V1.00
 * 定版时间：2020-2-24
 * 版本修改：
 * <版本号> <修改日期>, <修改人员>: <修改功能概述> 
 * V1.00 2021-2-24 刘志利：初版
 *================================================================================*/
#ifndef _IES_IMSAM_H_
#define _IES_IMSAM_H_

#include "IES_IMSrc.h"
// 元件接口结构体
typedef struct
{
// 初始化标志
	BYTE            byRamScan1;                  // 扫描内存片
	UINT32          dwInit;                      // 组件复归标志
	UINT32          dwBs;                        // 组件闭锁标志
	UINT32          dwPWInit;                    // 上电初始化标志
	UINT32          dwMenuInit;                  // 界面退出闭锁标志
	UINT32          dwJumpCnt;                   // 帧序号跳变统计
	UINT32          dwLostCnt;                   // 无帧统计
// 采样数据
	UINT32          dwWaveFlag;                  // 模拟量输出标志
	UINT32          dwAnaPtr;                    // 相量运算指针
// 基波实虚部
	INT64           iAnaReal[CN_NUM_ANA];        // 实部
	BYTE            byRamScan2;                  // 扫描内存片
	INT64           iAnaImag[CN_NUM_ANA];        // 虚部
	BYTE            byRamScan3;                  // 扫描内存片
#if(CN_HUM_ENA)	
// 13次谐波实虚部
	INT64           iAnaHumReal[CN_NUM_ANA][CN_HUM_NUM];        // 谐波实部
	BYTE            byRamScan4;                                 // 扫描内存片
	INT64           iAnaHumImag[CN_NUM_ANA][CN_HUM_NUM];        // 谐波虚部
	BYTE            byRamScan5;                                 // 扫描内存片
#endif	
// 积分幅值
	UINT64          dwAnaAm[CN_NUM_ANA];         // 幅值
	BYTE            byRamScan6;                  // 扫描内存片
// 一二次转换系数
	FLOAT32         fAnaBb[CN_NUM_ANA];           // 一二次转换系数
	BYTE            byRamScan7;                  // 扫描内存片
// 基准电压门槛
	BOOL            bJzChkEna;                    // 基准电压自检控制字
	UINT32          dwJz1MkMin;                    // 基准电压1上限定值
	UINT32          dwJz1MkMax;                    // 基准电压1下限定值
	UINT32          dwJz2MkMin;                    // 基准电压2上限定值
	UINT32          dwJz2MkMax;                    // 基准电压2下限定值
	BOOL            bJzChk[CN_NUM_JZ];            // 基准电压越限
	BYTE            byRamScan8;                  // 扫描内存片
// 测频相关数据
	UINT32          dwFBc[CN_NUM_CAL];            // 测频计补偿
	BYTE            byRamScan9;                  // 扫描内存片
	UINT32          dwFDly[CN_NUM_CAL];           // 测频计数器
	BYTE            byRamScan10;                  // 扫描内存片
	UINT32          dwFCal[CN_NUM_CAL];           // 测频结果
	BYTE            byRamScan11;                  // 扫描内存片
	UINT32          dwFCnt[CN_NUM_CAL];           // 过零点计数
	BYTE            byRamScan12;                  // 扫描内存片
// 幅值自动校准缓存
	BYTE            bAdjAmStr;                    // 自动校准启动
	BYTE            bAdjAmEnd;                    // 自动校准结束
	WORD            wAdjAmPtr;                    // 自动校准计数
	WORD            wAdjAmNum;                    // 自动校准周波数
	DWORD           dwAdjAmMin[CN_NUM_SAM];       // 自动校准时间段内最小值
	BYTE            byRamScan13;                  // 扫描内存片
	DWORD           dwAdjAmMax[CN_NUM_SAM];       // 自动校准时间段内最大值
	BYTE            byRamScan14;                  // 扫描内存片
	DWORD           dwAdjAmBuf[CN_NUM_SAM];       // 自动校准数据缓存
	BYTE            byRamScan15;                  // 扫描内存片
// 直流补偿自动校准缓存
	BYTE           bAdjDcStr;                      // 自动校准启动
	BYTE           bAdjDcEnd;                      // 自动校准结束
	WORD           wAdjDcPtr;                      // 自动校准计数
	WORD           wAdjDcNum;                      // 自动校准周波数
	INT32          iAdjDcMin[CN_NUM_SAM];          // 自动校准时间段内最小值
	BYTE           byRamScan16;                    // 扫描内存片
	INT32          iAdjDcMax[CN_NUM_SAM];          // 自动校准时间段内最大值
	BYTE           byRamScan17;                    // 扫描内存片
	INT32          iAdjDcBuf[CN_NUM_SAM];          // 自动校准数据缓存
	BYTE           byRamScan18;                    // 扫描内存片
// 相位补偿自动校准缓存
	BYTE           bAdjAngStr;                    // 自动校准启动
	BYTE           bAdjAngEnd;                    // 自动校准结束
	WORD           wAdjAngPtr;                    // 自动校准计数
	WORD           wAdjAngNum;                    // 自动校准周波数
	DWORD          dwAdjAngAmMin[CN_NUM_SAM];     // 自动校准时间段内幅值最小值
	BYTE           byRamScan19;                   // 扫描内存片
	DWORD          dwAdjAngAmMax[CN_NUM_SAM];     // 自动校准时间段内幅值最大值
	BYTE           byRamScan20;                   // 扫描内存片
	INT32          iAdjAngMin[CN_NUM_SAM];        // 自动校准时间段内相位最小值
	BYTE           byRamScan21;                   // 扫描内存片
	INT32          iAdjAngMax[CN_NUM_SAM];        // 自动校准时间段内相位最大值
	BYTE           byRamScan22;                   // 扫描内存片
	INT32          iAdjAngBuf[CN_NUM_SAM];        // 自动校准数据缓存
	BYTE           byRamScan23;                   // 扫描内存片
#if(CN_TCHG_ENA)	
	// 温度补偿
	UINT32          dwCoeTMod;                     // 温度调节模式
	UINT32          dwCoeTModStr;                  // 温度调节模式启动
	UINT32          dwCoeTCnt;                     // 温度调节模式定时器
#endif
// 反极性设置
#if(CN_SV_IN_ENA)
	UINT32          dwPolSvAMat;                  // A套SV反极性反极性设置矩阵
	UINT32          dwPolSvBMat;                  // B套SV反极性反极性设置矩阵
#endif	
	UINT32          dwPolSamMat1;                 // 本套模拟量反极性设置矩阵1
	UINT32          dwPolSamMat2;                 // 本套模拟量反极性设置矩阵2
	BYTE            byRamScan24;                  // 扫描内存片
} tag_IMSam;

/*================================================================================*/
// 元件接口全局函数
/*================================================================================*/
#if(CN_SV_IN_ENA)
extern  void    IES_IMSam_SvSub_Init();          // 采样元件参数初始化函数
#endif
extern  void    IES_IMSam_SvPub_Init();          // 采样元件参数初始化函数
extern  void    IES_IMSam_Para_Init();           // 采样元件参数初始化函数
extern  void    IES_IMSam_Init();                // 采样元件上电初始化函数
extern  void    IES_IMSam_Q();                   // 采样元件执行函数
extern  void    IES_IMSam();                     // 采样元件执行函数
 // 对外接口
 
extern  BOOL    IES_IMSam_AdJAm_Str(WORD wAdjNum);    // 幅值自动校准启动
extern  UINT32  IES_IMSam_AdJAm(BOOL *pbChn);         // 幅值自动校准
extern  BOOL    IES_IMSam_AdJDc_Str(WORD wAdjNum);    // 直流补偿自动校准启动
extern  UINT32  IES_IMSam_AdJDc(BOOL *pbChn);         // 直流补偿自动校准
extern  BOOL    IES_IMSam_AdJAng_Str(WORD wAdjNum);   // 相位自动校准启动
extern  UINT32  IES_IMSam_AdJAng(BOOL *pbChn);        // 相位自动校准
extern  void    IES_IMSam_SvPub_Chg(WORD wIndexSrc,WORD wIndexDst,WORD wAddNum,DWORD dwChg1,DWORD dwChg2);      // SVPUB挑数动态修改接口
extern  BOOL    IES_IMSam_SvPub_Cal(WORD wIndexSrc1,WORD wIndexSrc2,WORD wIndexDst);  // SVPUB挑数通道计算接口
/*================================================================================*/
#endif  /* _IES_IMSAM_H_ */
