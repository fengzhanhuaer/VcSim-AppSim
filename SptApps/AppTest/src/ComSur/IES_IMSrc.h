/*================================================================================
 * 文件描述：系统资源变量定义
 * 文件版本: V1.00
 * 定版时间:
 * 版本修订:
 * 修订人员:
 *================================================================================*/
#ifndef _IES_IMSRC_H_
#define _IES_IMSRC_H_

#include "IES_IMPub.h"

/*================================================================================*/
// 结构体定义
/*================================================================================*/
// 软件版本信息
typedef struct
{
	UINT32        dwVerSion;                   // 程序版本号
	UINT32        dwCrc;                       // 程序CRC校验码
	UINT32        dwTime;                      // 程序版本时间
}tagSoftVer;
// 装置版本信息
typedef struct
{
	BYTE          byRamScan1;
	UINT32        dwCrc;                       // CCD文件CRC
	UINT32        dwCrcOth;                    // 另一板卡CCD文件CRC
	char          byID[64];                    // 唯一性编码
	BYTE          byRamScan2;
	char          byName[64];                  // 装置型号
	BYTE          byRamScan3;
}tagDevInfor;
// 模拟量向量(保护)
typedef struct
{
	//INT32         iRe;                                // 实部
	//INT32         iIm;                                // 虚部
	UINT32        dwAm;                               // 幅值(积分)
	UINT32        dwAmJ;                              // 幅值(基波)
	UINT32        dwAngle;                            // 绝对相位
	UINT32        dwAngleRel;                         // 相对相位
} tagVector;
// 以1970年1月1日0时0分0秒0毫秒为时钟基准开始的UTC时间数据结构
typedef struct
{
// 固定低字在前,方便取64位数据
    DWORD           dwUSecond_L;                    // us_L 微秒低32位
    DWORD           dwUSecond_H;                    // us_H 微秒高32位
    DWORD           dwLeapSecFlg;                   // 时间品质
} tagTimeUTC;
// 模拟量数据结构体
typedef struct
{
	//  配置信息
	BYTE      byRamScan1;
	WORD      wSvPubNum;                            // SV发布：SV发布通道总个数 包含额定延时
	WORD      wSvPubDatNum;                         // SV发布：SV发布通道模拟量数据个数
	WORD      wSvPubChg;                            // SV发布：SV发布配置动态修正
	WORD      wSvPubCfg[CN_NUM_ANA];                // SV发布：SV通道与本地通道映射表,无映射为0xffff
	BYTE      byRamScan2;
	WORD      wSvPubChn[CN_NUM_ANA];                // SV发布：本地通道与SV通道映射表,无映射为0xffff
	BYTE      byRamScan3;
	WORD      wSvPubSend[CN_NUM_ANA];               // SV发布：SV通道与本地通道映射表在线修正
	BYTE      byRamScan4;
	BOOL      bSvPubPol[CN_NUM_ANA];                // SV发布：极性设置
	BYTE      byRamScan5;
	// 输入数据
	DWORD     dwAnaFramNum;                         // 采样帧序号
	DWORD     dwAnaFramDNum;                        // 采样帧序号差
	INT32     iAnaSam[CN_NUM_ANA];                  // 模拟量原始采样值
	BYTE      byRamScan6;
	INT32     iAnaSamBak[CN_NUM_ANA];               // 模拟量原始采样值备份
	BYTE      byRamScan7;
	BYTE      bySvCbPubNum;                         // SV发布控制块个数
	DWORD     dwSvCbPubCfg;                         // SV发布控制块配置标志字
#if(CN_SV_IN_ENA)
	// 如何保证A、B套对应控制块
	BYTE      bySvCbSubNum;                         // SV订阅控制块个数
	DWORD     dwSvCbSubCfg[CN_NUM_BOARD_SV];        // SV订阅控制块配置标志字
	BYTE      byRamScan71;
	DWORD     dwSvCbStatus[CN_NUM_BOARD_SV];        // SV订阅控制块状态标志字
	BYTE      byRamScan72;
	// 解析数据
	DWORD     dwSvQ[CN_NUM_SV];                     // SV订阅品质
	BYTE      byRamScan73;
	BOOL      bSvSub[CN_NUM_SV];                    // SV订阅配置正常标志
	BYTE      byRamScan74;
	BYTE      bySvCb[CN_NUM_SV];                    // SV订阅控制块映射(需要自检)
	BYTE      byRamScan75;
#endif
	// 自检状态
	BOOL      bFrameErr;                            // 模拟量帧异常
	// 输出数据
	BYTE      byAnaVecChg;                          // 相量数据更新标志
	tagVector tAnaVectFst[CN_NUM_ANA];              // 模拟量一次值相量
	BYTE      byRamScan8;
	tagVector tAnaVect[CN_NUM_ANA];                 // 模拟量二次值相量
	BYTE      byRamScan9;
	tagVector tAnaVectHum[CN_NUM_ANA][CN_HUM_NUM];  // 模拟量谐波
	BYTE      byRamScan10;
	BYTE      byFrChg;                              // 频率更新标志
	DWORD     dwFrCal[CN_NUM_CAL];                  // 模拟量频率
	BYTE      byRamScan11;
	DWORD     dwAnaQ[CN_NUM_ANA];                   // 模拟量品质
	BYTE      byRamScan12;
	BYTE      byAnaQChg;                            // 品质更新
	// 向FPGA下发系数
	BYTE      byAnaAmCoeChg;                        // 幅值校准系数下发标志
	DWORD     dwAnaAmCoe[CN_NUM_AD];               // 幅值校准系数
	BYTE      byRamScan13;
	BYTE      byAnaAngCoeChg;                       // AD微调系数下发标志
	WORD      wAnaAngCoe[CN_NUM_JZ*2];              // AD微调系数
	BYTE      byRamScan14;
	BYTE      byAnaDcCoeChg;                        // 直流补偿系数下发标志
	WORD      wAnaDcCoe[CN_NUM_AD];                 // 直流补偿系数
	BYTE      byRamScan15;
	// 向界面显示下发系数
	BYTE      byAnaPtCtChg;                         // 变比下发标志
	FLOAT32   fAnaPtCt[CN_NUM_ANA];                 // 变比
	BYTE      byRamScan16;
} tagAna;
// IO数据结构体
typedef struct
{
	//1.1 DI输入数据
	BYTE       byRamScan1;
	DWORD      dwDICnt[CN_NUM_BOARD_DI];          // DI采样变位序号
	BYTE       byRamScan2;
	DWORD      dwDIIn[CN_NUM_BOARD_DI];           // DI原始采样值32位型
	BYTE       byRamScan3;
	tagTimeUTC tDIInUTC[CN_NUM_BOARD_DI];         // DI原始时标
	BYTE       byRamScan4;
	//1.2 DI输出数据
	BOOL       bDIHldIn[CN_NUM_DI];               // DI防抖后状态布尔型
	BYTE       byRamScan5;
	DWORD      dwDIHldIn32[CN_NUM_BOARD_DI];      // DI防抖后状态32位型
	BYTE       byRamScan6;
	DWORD      dwDIHldXor32[CN_NUM_BOARD_DI];     // DI防抖后状态变位标志
	BYTE       byRamScan7;
	tagTimeUTC tDIHldUTC[CN_NUM_DI];              // DI防抖前时标
	BYTE       byRamScan8;
//	DWORD      dwBoardDIQ[CN_NUM_BOARD_DI];       // DI品质
	DWORD      dwDIQ[CN_NUM_DI];                  // DI品质
	BYTE       byRamScan9;
	DWORD      dwDIQChg;                          // DI品质更新
	BYTE       byDIFstToSoe;                      // DI第一帧更新事项
	BYTE       byDIFstToGoose;                    // DI第一帧更新GOOSE
	//2.1 GOOSE订阅配置信息
	BYTE       byGoCbSubNum;                      // GO开入控制块个数(本板卡)
	BYTE       byGoCbSubNumCom;                   // GO开入控制块个数(另一板卡)
	BYTE       byGoInSub[CN_NUM_GOIN];            // GO订阅状态
	BYTE       byRamScan10;
	BYTE       byGoInGoCb[CN_NUM_GOIN];           // GO开入量控制块映射(需要自检)
	BYTE       byRamScan11;
	WORD       wGoInAppId[CN_NUM_GOIN];           // GO订阅APPID
	BYTE       byRamScan12;
	DWORD      dwGoInSubStatus[CN_NUM_GOCB_SUB];  // GO开入控制块异常汇总
	BYTE       byRamScan13;
	//2.2 GOOSE订阅输入数据
	DWORD      dwGoInCnt;                         // GO订阅计数器
	WORD       wGoQSrc[CN_NUM_GOIN];              // GO订阅值字型(品质)
	BYTE       byRamScan14;
	tagTimeUTC tGoInUTC[CN_NUM_GOIN];             // GO订阅数据时标
	BYTE       byRamScan15;
	tagTimeUTC tGoInUTCRev;                       // GO订阅数据接收时标
	//2.3 GOOSE订阅状态字
	DWORD      dwGoInStatusA[CN_NUM_GOCB_SUB];    // GO开入控制块A网状态字
	BYTE       byRamScan16;
	DWORD      dwGoInStatusB[CN_NUM_GOCB_SUB];    // GO开入控制块B网状态字
	BYTE       byRamScan17;
	//2.4 GOOSE订阅状态字解析
//	BOOL       bGoInLink[CN_NUM_GOCB_SUB];        // GO开入控制块断链
	BYTE       byRamScan18;
//	BOOL       bGoInDatErr[CN_NUM_GOCB_SUB];      // GO开入控制块数据异常
	BYTE       byRamScan19;
//	BOOL       bGoInTestErr[CN_NUM_GOCB_SUB];     // GO开入控制块检修不一致
	BYTE       byRamScan20;
//	BOOL       bTimeLive0[CN_NUM_GOCB_SUB];       // GO开入控制块生存周期为0
	BYTE       byRamScan21;
	//2.5 GOOSE订阅输出数据
	BOOL       bGoIn[CN_NUM_GOIN];                // GO开入状态
	BYTE       byRamScan22;
	BOOL       bGoInXor[CN_NUM_GOIN];             // GO开入状态变位
	BYTE       byRamScan23;
	BOOL       bGoInValid[CN_NUM_GOIN];           // GO开入有效状态
	BYTE       byRamScan24;
	BOOL       bGoInValidXor[CN_NUM_GOIN];        // GO开入有效状态变位
	BYTE       byRamScan25;
	BYTE       byGoInInValid[CN_NUM_GOIN];        // GO开入无效状态原因
	BYTE       byRamScan26;
	tagTimeUTC dwGoInValidT[CN_NUM_GOIN];         // GO订阅数据时标(暂未使用)
	BYTE       byRamScan27;
	//3.1 双点输出数据
	BYTE       byDpiIn[CN_NUM_DPI];               // 双点位置信息
	BYTE       byRamScan28;
	BYTE       byDpiInXor[CN_NUM_DPI];            // 双点位置信息变位
	BYTE       byRamScan29;
	tagTimeUTC tDpiUTC[CN_NUM_DPI];               // 双点变位时标
	BYTE       byRamScan30;
	DWORD      dwDpiQ[CN_NUM_DPI];                // 双点品质
	BYTE       byRamScan31;
	BYTE       byDpiFstToSoe;                     // 双点第一帧更新SOE
	BYTE       byDpiFstToGoose;                   // 双点第一帧更新GOOSE
	//4.1 DO合成数据
	BOOL       bDOOut[CN_NUM_DO];                 // DO开出数据布尔型
	BYTE       byRamScan32;
	BOOL       bDOOutXor[CN_NUM_DO];              // DO开出数据布尔型
	BYTE       byRamScan33;
	//5.1 GOOSE发布配置信息
	BYTE       byGoCbPubNum;                      // GO发布控制块个数
	BYTE       byGoPub[CN_NUM_GOOUT];             // GO发布短地址配置标志
	BYTE       byRamScan34;
	BYTE       byGoPubCb[CN_NUM_GOOUT];           // GO发布控制块
	BYTE       byRamScan35;
	DWORD      dwGoPubStatus[CN_NUM_GOCB_PUB];        // GO发布异常汇总
	BYTE       byRamScan36;
	//5.2 GOOSE发布合成数据
	BOOL       bGoOut[CN_NUM_GOOUT];              // GO发布值布尔型
	BYTE       byRamScan37;
	BOOL       bGoOutCom[CN_NUM_GOOUT];           // GO发布值布尔型
	BYTE       byRamScan38;
	BOOL       bGoOutXor[CN_NUM_GOOUT];           // GO发布值变化标志
	BYTE       byRamScan39;
	DWORD      dwGoOutQ[CN_NUM_GOOUT];            // GO发布品质
	BYTE       byRamScan40;
	tagTimeUTC tGoOutT[CN_NUM_GOOUT];             // GO订阅数据时标
	BYTE       byRamScan41;
	//6.1 指示灯合成数据
	BOOL       bLedOut[CN_NUM_LED];               // LED控制值布尔型
	
	BYTE       byRamScan42;
	BOOL       bLedOutCom[CN_NUM_LED];            // LED控制值布尔型
	
	BYTE       byRamScan43;
	BOOL       bLedOutHld[CN_NUM_LED];            // LED控制值保持标志
	BYTE       byRamScan44;
	BYTE       byLedPtr;                          // LED指示灯指针
	BYTE       byRamScan45;
// 板卡状态
	DWORD      dwDIBoardCnt[CN_NUM_BOARD_DI];
	BYTE       byRamScan46;
} tagIO;
// 直流数据缓冲窗
typedef struct
{
	INT32   iDCBuf;            // DC直采数据输入最大值
	INT16   iDCMax;            // DC直采数据输入最大值
	INT16   iDCMin;            // DC直采数据输入最小值
	WORD    wDCPtr;            // DC直采数据输入计数
	WORD    wDCCnt;            // DC直采数据输入有效计数
}tagDCSamIn;
// 直流数据结构体
typedef struct
{
	// 输入数据
	BYTE    byRamScan1;
	DWORD   dwDCRefCnt[CN_NUM_BOARD_DC];     // 直采DC数据刷新计数器
	BYTE    byRamScan2;
	BOOL    bDCFresh[CN_NUM_BOARD_DC];       // 直采DC数据刷新标志
	BYTE    byRamScan3;
	BOOL    bDCDispFresh[CN_NUM_BOARD_DC];   // 直采DC数据界面刷新标志
	BYTE    byRamScan4;
	BOOL    bDCGoOutFresh[CN_NUM_BOARD_DC];  // 直采DC数据板件交互刷新标志
	BYTE    byRamScan5;
	BOOL    bDCCommFresh[CN_NUM_BOARD_DC];   // 直采DC数据GOOSE刷新标志
	BYTE    byRamScan6;
	DWORD   dwDCBoardCnt[CN_NUM_BOARD_DC];   // DC板卡状态计数器
	BYTE    byRamScan7;
	WORD    wDCRefPtr[CN_NUM_BOARD_DC];     // 直采DC数据刷新指针
	BYTE    byRamScan8;
	// 原始数据
	INT32   iDCIn[CN_NUM_DC];            // DC数据输入
	BYTE    byRamScan9;
	INT32   iDCOut[CN_NUM_DC];           // DC二次值整形输出
	BYTE    byRamScan10;
	FLOAT32 fDCOut[CN_NUM_DC];           // DC二次值浮点输出
	BYTE    byRamScan11;
	// 数据窗(阶段数据窗)
	tagDCSamIn tDCSamIn[CN_NUM_DC_SAM];
	// 一次值数据
	INT32   iDCOutFst[CN_NUM_DC_SAM];    // DC一次值整形输出
	BYTE    byRamScan12;
	FLOAT32 fDCOutFst[CN_NUM_DC_SAM];    // DC一次值浮点输出
	BYTE    byRamScan13;
	// 通信数据
	BOOL    bDCChg[CN_NUM_DC];           // DC变化标志
	BYTE    byRamScan14;
	INT32   iDCOutCom[CN_NUM_DC];        // DC整形输出(GOOSE输出)
	BYTE    byRamScan15;
	FLOAT32 fDCOutCom[CN_NUM_DC];        // DC浮点输出(GOOSE输出)
	BYTE    byRamScan16;
	UINT32  dwDCOutQ[CN_NUM_BOARD_DC];   // DC品质
	BOOL    bDCOutQChg[CN_NUM_BOARD_DC]; // DC品质变化
	BYTE    byRamScan17;
	tagTimeUTC tDCOut[CN_NUM_DC];        // DC时标
	BYTE    byRamScan18;
} tagDC;

// 参数结构体
typedef struct
{
	BYTE    byRamScan1;
	DWORD   dwChgCnt[CN_NUM_BOARD_PARA];   // 参数变化计数
	BYTE    byRamScan2;
	//DWORD   dwChgWRef[CN_NUM_BOARD_PARA];  // 参数存储刷新标志
	BYTE    byRamScan3;
	BOOL    bCrcCom;                       // 参数Crc传输标志
	BOOL    bCrcOthChg;                    // 另一板卡参数Crc变化标志
	DWORD   dwCrc[CN_NUM_BOARD_PARA];      // 参数Crc校验码
	BYTE    byRamScan4;
	DWORD   dwCrcOth[CN_NUM_BOARD_PARA];   // 另一板卡参数Crc校验码
	BYTE    byRamScan5;
	DWORD   dwPara[CN_NUM_PARA];           // 
	BYTE    byRamScan6;
	DWORD   dwCoe[CN_NUM_PARA];            // 
	BYTE    byRamScan7;
	FLOAT32 fPara[CN_NUM_PARA];
	BYTE    byRamScan8;
	DWORD   dwParaBak[CN_NUM_PARA];        // 参数写备份
	BYTE    byRamScan9;
} tagPara;
// 内存扫描数据结构体
typedef struct
{
	BYTE *pbyRamPtr;    // 内存扫描点地址 
	//DWORD dwRamValue;
	DWORD dwRamNo;      // 内存扫描点序号
} tagRamDot;

typedef struct
{
	BYTE  byRamScan1;
	tagRamDot tRamDot[CN_RAMSCAN_MAX];
	BYTE  byRamScan2;
	DWORD dwRamPtr;       // 内存扫描点总序号 
	DWORD dwRamChkPtr;    // 内存扫描点自检序号 
	BYTE  byRamScan3;
} tagRamScan;

// 公共数据结构体
typedef struct
{
	BYTE  byRamScan1;
	// 系统时间
	tagTimeUTC   tSysTimeUTC;    // 系统时钟
	// 系统运行全局标志
	BOOL    bSysLockBH;          // 系统闭锁保护标志
	BOOL    bSysLockCK;          // 系统闭锁测控标志
	BOOL    bSysTest;            // 系统运行检修标志
	BOOL    bSysTestXor;         // 系统运行检修变化标志
	BOOL    bSysReset;           // 就地软复归命令
	BOOL    bSysPower;           // 上电完成标志
	BOOL    bSysBs;              // 装置总闭锁
	// 全局计数器
	UINT32  dwSysTimer;          // 时间继电器时标
	// 上电计数器
	DWORD   dwSysPowCnt;         // 上电计数器
	// 自由计数器
	DWORD   dwSysCnt;            // 自由计数器
	// 常量表自检标志
	BOOL    bConstChk[CN_NUM_DTYPE+CN_NUM_CFG];
	BYTE    byRamScan2;
} tagPub;

// 事项参数(3组)
typedef struct
{
	WORD    wMeaType[3];         // 测量类型1~3
	UINT32  iMeaValue[3];        // 测量值1~3
}tagMsgValue;
// 事项参数(6组)
typedef struct
{
	WORD    wMeaType[6];         // 测量类型1~6
	UINT32  iMeaValue[6];        // 测量值1~6
}tagMsgValue6;

// Act事项
typedef struct
{
	BOOL           bActIn;            // GOOSE命令状态
	BOOL           bActOut;           // 出口状态
	BOOL           bActOutRet;        // 出口返校状态
	tagTimeUTC     tActT;             // GOOSE命令时标
	tagTimeUTC     tActOutRetT;       // 出口返校时标
	tagMsgValue6   tRecValue6;        // 事项参数记录
}tagActEvent;
// Act队列
typedef struct
{
	tagActEvent    tActEvent;                // GOOSE命令事项
	tagActEvent    tActEventBak;             // GOOSE命令事项备份
	DWORD          dwTimeCnt;                // 时间继电器
	BYTE           byFlag;                   // 事项记录标志
	BYTE           byBakVaild;               // 备份有效标志
}tagActQueue;
// Act状态
typedef struct
{
	BYTE           byRamScan1;
	BOOL           bActIn[CN_NUM_ACT];            // GOOSE命令状态
	BYTE           byRamScan2;
	BOOL           bActOut[CN_NUM_ACT];           // 出口状态
	BYTE           byRamScan3;
	BOOL           bActOutRet[CN_NUM_ACT];        // 出口返校状态
	BYTE           byRamScan4;
	WORD           wActInIndex[CN_NUM_ACT];       // GOOSE命令枚举记录
	BYTE           byRamScan5;
	WORD           wActOutIndex[CN_NUM_ACT];      // 出口命令枚举记录
	BYTE           byRamScan6;
}tagActState;
// Alm状态
typedef struct
{
	BYTE           byRamScan1;
	BOOL           bAlmIn[CN_NUM_ALM];             // 告警事件状态输入区
	BYTE           byRamScan2;
	BOOL           bAlmOut[CN_NUM_ALM];            // 告警事件状态输出区
	BYTE           byRamScan3;
	BOOL           bAlmXor[CN_NUM_ALM];            // 告警事件变位状态
	BYTE           byRamScan4;
	tagMsgValue    tRecValue[CN_NUM_ALM];          // 事项参数记录
	BYTE           byRamScan5;
}tagAlmState;
// Chk状态
typedef struct
{
	BYTE           byRamScan1;
	BOOL           bChkIn[CN_NUM_CHK];             // 自检事件状态标志区
	BYTE           byRamScan2;
	BOOL           bChkOut[CN_NUM_CHK];            // 自检事件状态输出区
	BYTE           byRamScan3;
	BOOL           bChkXor[CN_NUM_CHK];            // 自检事件变位状态
	BYTE           byRamScan4;
	tagMsgValue    tRecValue[CN_NUM_CHK];          // 事项参数记录
	BYTE           byRamScan5;
	UINT32         dwChkActCnt[CN_NUM_CHK];
	BYTE           byRamScan6;
	UINT32         dwChkRetCnt[CN_NUM_CHK];
	BYTE           byRamScan7;
}tagChkState;

/*================================================================================*/
// 应用侧全局数据区
/*================================================================================*/
// 版本信息
extern tagDevInfor  g_tDevInfor;              // 版本信息
// 数据交互区
extern tagAna       g_tagAna;                 // 模拟量数据
extern tagIO        g_tagIO;                  // IO数据
extern tagDC        g_tagDC;                  // 直流数据
extern tagPara      g_tagPara;                // 参数
extern tagRamScan   g_tagRamScan;             // 内存扫描结构体
extern tagPub       g_tagPub;                 // 平台公共部分
// 应用中间标志
extern BOOL         g_bFlag[CN_NUM_FLAG+1];   // 全局布尔变量标志定义
extern INT32        g_iInter[CN_NUM_INTER+1]; // 全局内部数据定义
// 事项队列
extern tagActQueue     g_tActQueue[CN_NUM_ACT];
// 事项实时状态
extern tagActState     g_tActState;           // 告警事件实时状态
extern tagAlmState     g_tAlmState;           // 告警事件实时状态
extern tagChkState     g_tChkState;           // 自检事件实时状态

/*================================================================================*/
// 应用侧全局数据接口
/*================================================================================*/
// 源数据获取
#define CN_Get_Dat_Src_P(wTypeIndex)            (((wTypeIndex)<CN_NUM_DTYPE)?g_tDTypeTab[(wTypeIndex)].bDatAtr:0);
#define CN_Get_Dat_Src_NUM(wTypeIndex)          (((wTypeIndex)<CN_NUM_DTYPE)?g_tDTypeTab[(wTypeIndex)].wDatNum:0);
#define CN_Get_Dat_Src(wTypeIndex,wDatIndex)    (((wTypeIndex)<CN_NUM_DTYPE)?(((wDatIndex)<g_tDTypeTab[(wTypeIndex)].wDatNum)?g_tDTypeTab[(wTypeIndex)].bDatAtr[(wDatIndex)]:0):0);
// 模拟量部分--二次值
#define CN_Get_Ana_Am(wIndex)         (((wIndex)<CN_NUM_ANA)?g_tagAna.tAnaVect[(wIndex)].dwAm:0);
#define CN_Get_Ana_AmJ(wIndex)        (((wIndex)<CN_NUM_ANA)?g_tagAna.tAnaVect[(wIndex)].dwAmJ:0);
#define CN_Get_Ana_Ang(wIndex)        (((wIndex)<CN_NUM_ANA)?g_tagAna.tAnaVect[(wIndex)].dwAngle:0);
// 模拟量部分--二次值
#define CN_Get_Ana_FAm(wIndex)        (((wIndex)<CN_NUM_ANA)?g_tagAna.tAnaVectFst[(wIndex)].dwAm:0);
#define CN_Get_Ana_FAmJ(wIndex)       (((wIndex)<CN_NUM_ANA)?g_tagAna.tAnaVectFst[(wIndex)].dwAmJ:0);
#define CN_Get_Ana_FAng(wIndex)       (((wIndex)<CN_NUM_ANA)?g_tagAna.tAnaVectFst[(wIndex)].dwAngle:0);
// 模拟量部分--谐波
#define CN_Get_Ana_HAm(wNum,wIndex)   (((wIndex)<CN_NUM_ANA)?g_tagAna.tAnaVectHum[(wIndex)][(wNum)].dwAm:0);
#define CN_Get_Ana_HAmJ(wNum,wIndex)  (((wIndex)<CN_NUM_ANA)?g_tagAna.tAnaVectHum[(wIndex)][(wNum)].dwAmJ:0);
#define CN_Get_Ana_HAng(wNum,wIndex)  (((wIndex)<CN_NUM_ANA)?g_tagAna.tAnaVectHum[(wIndex)][(wNum)].dwAngle:0);
// 模拟量部分--频率
#define CN_Get_Cal_F(wIndex)          (((wIndex)<CN_NUM_CAL)?g_tagAna.dwFrCal[(wIndex)]:0);
// IO部分
#define G_Get_DI_P                  (g_tagIO.bDIHldIn)
#define G_Get_DPI_P                 (g_tagIO.byDpiIn)
#define G_Get_GOIN_P                (g_tagIO.bGoIn)
#define G_Get_GOIN_V_P              (g_tagIO.bGoInValid)
#define G_Get_GOIN_InV_P            (g_tagIO.byGoInInValid)
#define G_Get_DI_UTC_P              (g_tagIO.tDIHldUTC)
#define G_Get_DPI_UTC_P             (g_tagIO.tDpiUTC)
#define G_Get_GOIN_UTC_P            (g_tagIO.tGoInUTC)
#define G_Get_DI(wIndex)            (((wIndex)<CN_NUM_DI)?g_tagIO.bDIHldIn[(wIndex)]:0)
#define G_Get_DPI(wIndex)           (((wIndex)<CN_NUM_DPI)?g_tagIO.byDpiIn[(wIndex)]:0)
#define G_Get_GOIN(wIndex)          (((wIndex)<CN_NUM_GOIN)?g_tagIO.bGoInValid[(wIndex)]:0)
// 直流部分
#define G_Get_DC_In_P                (g_tagDC.iDCIn)
#define G_Get_DC_I_P                 (g_tagDC.iDCOut)
#define G_Get_DC_F_P                 (g_tagDC.fDCOut)
#define G_Get_DC_I(wIndex)           (((wIndex)<CN_NUM_DC)?g_tagDC.iDCOut[(wIndex)]:0)
#define G_Get_DC_F(wIndex)           (((wIndex)<CN_NUM_DC)?g_tagDC.fDCOut[(wIndex)]:0)
// 参数部分
#define G_Get_PARA_I_P               (g_tagPara.dwPara)
#define G_Get_PARA_F_P               (g_tagPara.fPara)
#define G_Get_PARA_COE_P             (g_tagPara.dwCoe)

#define G_Get_PARA_I(wIndex)         (((wIndex)<CN_NUM_PARA)?g_tagPara.dwPara[(wIndex)]:0)
#define G_Get_PARA_F(wIndex)         (((wIndex)<CN_NUM_PARA)?g_tagPara.fPara[(wIndex)]:0)
#define G_Get_PARA_COE(wIndex)       (((wIndex)<CN_NUM_PARA)?g_tagPara.dwCoe[(wIndex)]:0)
// 公共部分
#define G_Get_PUB_UTC                  (&g_tagPub.tSysTimeUTC)
#define G_Get_Const_Chk(wIndex)        (g_tagPub.bConstChk[(wIndex)])
#define G_Set_Const_Chk(wIndex,wState) (((wIndex)<CN_NUM_PUB)?(g_tagPub.bConstChk[(wIndex)]=(wState)):0)
// 全局标志
#define G_Get_Flag_P                (g_bFlag)
#define G_Get_Flag(wIndex)          (((wIndex)<CN_NUM_FLAG)?g_bFlag[(wIndex)]:0)
#define G_Set_Flag(wIndex,wState)   (((wIndex)<CN_NUM_FLAG)?g_bFlag[(wIndex)]=(wState):0)
// 全局标志(内部使用)
#define G_Get_Inter_P                (g_iInter)
#define G_Get_Inter(wIndex)          (((wIndex)<CN_NUM_INTER)?g_iInter[(wIndex)]:0)
#define G_Set_Inter(wIndex,iState)   (((wIndex)<CN_NUM_INTER)?g_iInter[(wIndex)]=(iState):0)
// 事项启动
#define G_Set_ActIn(wIndex,wState)  (((wIndex)<CN_NUM_ACT)?g_tActState.bActIn[(wIndex)]=(wState):0)
#define G_Set_AlmIn(wIndex,wState)  (((wIndex)<CN_NUM_ALM)?g_tAlmState.bAlmIn[(wIndex)]=(wState):0)
// GOOSE命令事项状态输出
#define G_Get_ActIn_P               (g_tActState.bActIn)
#define G_Get_ActOut_P              (g_tActState.bActOut)
#define G_Get_ActOutRet_P           (g_tActState.bActOutRet)
#define G_Get_ActOut(wIndex)        (((wIndex)<CN_NUM_ACT)?g_tActState.bActOut[(wIndex)]:0)
// 告警事项状态输出
#define G_Get_AlmIn_P               (g_tAlmState.bAlmIn)
#define G_Get_AlmOut_P              (g_tAlmState.bAlmOut)
#define G_Get_AlmXor_P              (g_tAlmState.bAlmXor)
#define G_Get_AlmOut(wIndex)        (((wIndex)<CN_NUM_ALM)?g_tAlmState.bAlmOut[(wIndex)]:0)
// 自检事项状态输出
#define G_Get_ChkIn_P               (g_tChkState.bChkIn)
#define G_Get_ChkOut_P              (g_tChkState.bChkOut)
#define G_Get_ChkXor_P              (g_tChkState.bChkXor)
#define G_Get_ChkOut(wIndex)        (((wIndex)<CN_NUM_CHK)?g_tChkState.bChkOut[(wIndex)]:0)
// 带参数事项接口
#define G_Set_AlmIn_All(wIndex,wState,iValue1,iValue2,iValue3)    \
	if((wIndex)<CN_NUM_ALM)                                       \
	{                                                             \
		g_tAlmState.bAlmIn[(wIndex)]=(wState);                        \
		g_tAlmState.tRecValue[(wIndex)].iMeaValue[0]=(iValue1);       \
		g_tAlmState.tRecValue[(wIndex)].iMeaValue[1]=(iValue2);       \
		g_tAlmState.tRecValue[(wIndex)].iMeaValue[2]=(iValue3);       \
	}
// 自检事项带参数置位
#define G_Set_ChkIn_All(wIndex,iValue1,iValue2,iValue3)           \
	if((wIndex)<CN_NUM_CHK)                                       \
	{                                                             \
		g_tChkState.tRecValue[(wIndex)].iMeaValue[0]=(iValue1);       \
		g_tChkState.tRecValue[(wIndex)].iMeaValue[1]=(iValue2);       \
		g_tChkState.tRecValue[(wIndex)].iMeaValue[2]=(iValue3);       \
		g_tChkState.dwChkActCnt[(wIndex)]++;                        \
		g_tChkState.dwChkRetCnt[(wIndex)]=0;                        \
		g_tChkState.bChkIn[(wIndex)]=TRUE;                          \
	}
// 自检事项无参数置位
#define G_Set_ChkIn(wIndex)    \
	if((wIndex)<CN_NUM_CHK)                                       \
	{                                                             \
		g_tChkState.dwChkActCnt[(wIndex)]++;                        \
		g_tChkState.dwChkRetCnt[(wIndex)]=0;                        \
		g_tChkState.bChkIn[(wIndex)]=TRUE;                          \
	}
// 自检事项无参数清位
#define G_Clr_ChkIn(wIndex)    \
	if((wIndex)<CN_NUM_CHK)                                    \
	{                                                          \
		g_tChkState.dwChkActCnt[(wIndex)]=0;                     \
		g_tChkState.dwChkRetCnt[(wIndex)]++;                     \
		g_tChkState.bChkIn[(wIndex)]=FALSE;                      \
	}
		
// 0.5ms分时复用宏定义
#define G_Sys_Div2_1   (!(g_tagPub.dwSysCnt&DB0))
#define G_Sys_Div2_2   (g_tagPub.dwSysCnt&DB0)
// 1ms分时复用宏定义
#define G_Sys_Div4_1   ((g_tagPub.dwSysCnt&0x3)==0x0)
#define G_Sys_Div4_2   ((g_tagPub.dwSysCnt&0x3)==0x1)
#define G_Sys_Div4_3   ((g_tagPub.dwSysCnt&0x3)==0x2)
#define G_Sys_Div4_4   ((g_tagPub.dwSysCnt&0x3)==0x3)
// 1024分时复用宏定义
#define G_Sys_Div1024_000   ((g_tagPub.dwSysCnt&0x3ff)==0x1)
#define G_Sys_Div1024_256   ((g_tagPub.dwSysCnt&0x3ff)==0x101)
#define G_Sys_Div1024_512   ((g_tagPub.dwSysCnt&0x3ff)==0x201)
#define G_Sys_Div1024_768   ((g_tagPub.dwSysCnt&0x3ff)==0x301)
// 2048分时复用宏定义
#define G_Sys_Div2048_000   ((g_tagPub.dwSysCnt&0x7ff)==0x2)
#define G_Sys_Div2048_256   ((g_tagPub.dwSysCnt&0x7ff)==0x102)
#define G_Sys_Div2048_512   ((g_tagPub.dwSysCnt&0x7ff)==0x202)
#define G_Sys_Div2048_768   ((g_tagPub.dwSysCnt&0x7ff)==0x302)
#define G_Sys_Div2048_1024  ((g_tagPub.dwSysCnt&0x7ff)==0x402)
// 0x4000分时复用宏定义
#define G_Sys_Div16284_000   ((g_tagPub.dwSysCnt&0x3fff)==0x3)
#define G_Sys_Div16284_256   ((g_tagPub.dwSysCnt&0x3fff)==0x103)
#define G_Sys_Div16284_512   ((g_tagPub.dwSysCnt&0x3fff)==0x203)
#define G_Sys_Div16284_768   ((g_tagPub.dwSysCnt&0x3fff)==0x303)
// 自定义分时复用(必须是2的n次方)
#define G_Sys_Div(DivCnt,DivNum)          ((g_tagPub.dwSysCnt%(DivCnt))==(DivNum))

#endif /* _IES_IMSRC_H_ */
