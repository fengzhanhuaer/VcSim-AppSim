/*================================================================================
 * 文件描述：公用配置
 * 文件版本: V1.00
 * 开发人员:
 * 定版时间:
 * 版本修订:
 * 修订人员:
 *================================================================================*/
#include "IES_IMSrc.h"

/*================================================================================*/
// 数据类长量表
const tagDTypeTab  g_tDTypeTab[] =
{
	{ EN_DTYPE_ANA   ,   (BYTE*)&g_tAnaTab[0],   (BYTE*)&g_tagAna.tAnaVect[0]  ,  (WORD)(sizeof(g_tagAna.tAnaVect)/sizeof(tagVector)),    CN_NUM_ANA,    "模拟量",         "ANA_"},
	{ EN_DTYPE_CAL   ,   (BYTE*)&g_tCalTab[0],   (BYTE*)&g_tagAna.dwFrCal[0]   ,  (WORD)(sizeof(g_tagAna.dwFrCal)/sizeof(DWORD))     ,    CN_NUM_CAL,    "计算量",         "CAL_"},
	{ EN_DTYPE_DC    ,   (BYTE*)&g_tDCTab[0],    (BYTE*)&g_tagDC.iDCOut[0]     ,  (WORD)(sizeof(g_tagDC.iDCOut)/sizeof(INT32))       ,    CN_NUM_DC,     "直流数据",        "DC_"},
	{ EN_DTYPE_DI    ,   (BYTE*)&g_tDiTab[0],    (BYTE*)&g_tagIO.bDIHldIn[0]   ,  (WORD)(sizeof(g_tagIO.bDIHldIn)/sizeof(BOOL))      ,    CN_NUM_DI,     "硬开入",         "DI_"},
	{ EN_DTYPE_DPI   ,   (BYTE*)&g_tDpiTab[0],   (BYTE*)&g_tagIO.byDpiIn[0]    ,  (WORD)(sizeof(g_tagIO.byDpiIn)/sizeof(BOOL))       ,    CN_NUM_DPI,    "双点硬开入",       "DPI_"},
	{ EN_DTYPE_GOIN  ,   (BYTE*)&g_tGoInTab[0],  (BYTE*)&g_tagIO.bGoInValid[0] ,  (WORD)(sizeof(g_tagIO.bGoInValid)/sizeof(BOOL))    ,    CN_NUM_GOIN,   "GOOSE订阅",     "GOIN_"},
	{ EN_DTYPE_DO    ,   (BYTE*)&g_tDoTab[0],    (BYTE*)&g_tagIO.bDOOut[0]     ,  (WORD)(sizeof(g_tagIO.bDOOut)/sizeof(BOOL))        ,    CN_NUM_DO,     "硬开出",         "DO_"},
	{ EN_DTYPE_GOOUT ,   (BYTE*)&g_tGoOutTab[0], (BYTE*)&g_tagIO.bGoOut[0]     ,  (WORD)(sizeof(g_tagIO.bGoOut)/sizeof(BOOL))        ,    CN_NUM_GOOUT,  "GOOSE发布",     "GOOUT_"},
	{ EN_DTYPE_LED   ,   (BYTE*)&g_tLedTab[0],   (BYTE*)&g_tagIO.bLedOut[0]    ,  (WORD)(sizeof(g_tagIO.bLedOut)/sizeof(BOOL))       ,    CN_NUM_LED,    "指示灯",         "LED_"},
	{ EN_DTYPE_ACT   ,   (BYTE*)&g_tActTab[0],   (BYTE*)&g_tActState.bActOut[0],  (WORD)(sizeof(g_tActState.bActOut)/sizeof(BOOL))   ,    CN_NUM_ACT,    "GOOSE命令信号",    "ACT_"},
	{ EN_DTYPE_ALM   ,   (BYTE*)&g_tAlmTab[0],   (BYTE*)&g_tAlmState.bAlmOut[0],  (WORD)(sizeof(g_tAlmState.bAlmOut)/sizeof(BOOL))   ,    CN_NUM_ALM,    "告警信号",        "ALM_"},
	{ EN_DTYPE_CHK   ,   (BYTE*)&g_tChkTab[0],   (BYTE*)&g_tChkState.bChkOut[0],  (WORD)(sizeof(g_tChkState.bChkOut)/sizeof(BOOL))   ,    CN_NUM_CHK,    "自检信号",        "CHK_"},
	{ EN_DTYPE_FLAG  ,   (BYTE*)&g_tFlagTab[0],  (BYTE*)&g_bFlag[0]            ,  (WORD)(sizeof(g_bFlag)/sizeof(BOOL))               ,    CN_NUM_FLAG+1, "中间节点",        "FLAG_"},
	{ EN_DTYPE_INTER ,   (BYTE*)&g_tInterTab[0], (BYTE*)&g_iInter[0]           ,  (WORD)(sizeof(g_iInter)/sizeof(INT32))             ,    CN_NUM_INTER+1,"内部节点",        "INTER_"},
	{ EN_DTYPE_PARA  ,   (BYTE*)&g_tParaTab[0],  (BYTE*)&g_tagPara.dwPara[0]   ,  (WORD)(sizeof(g_tagPara.dwPara)/sizeof(DWORD))     ,    CN_NUM_PARA,   "参数",          "PARA_"},
};
const DWORD g_NUM_DTYPE = sizeof(g_tDTypeTab) / sizeof(tagDTypeTab);
// 控制类常量表
const tagCfgTab  g_tCfgTab[] =
{
	{ EN_CFG_DTYPE       ,   (BYTE*)&g_tDTypeTab[0]      ,    g_NUM_DTYPE       ,  CN_NUM_DTYPE       ,    "数据常量表",                "CFG_DTYPE"},
	{ EN_CFG_SAM_PUB     ,   (BYTE*)&g_tSvPubTab[0]      ,    g_NUM_SVPUB       ,  g_NUM_SVPUB        ,    "SV发布常量表",              "CFG_SAM_PUB"},
	{ EN_CFG_SAM_BOARD   ,   (BYTE*)&g_tBoardSamTab[0]   ,    g_NUM_BOARDSAM    ,  CN_NUM_BOARD_SAM   ,    "模拟量板卡",                "CFG_SAM_BOARD"},
	{ EN_CFG_DI_BOARD    ,   (BYTE*)&g_tBoardDITab[0]    ,    g_NUM_BOARD_DI    ,  CN_NUM_BOARD_DI    ,    "DI板卡",                 "CFG_DI_BOARD"},
	{ EN_CFG_DO_BOARD    ,   (BYTE*)&g_tBoardDOTab[0]    ,    g_NUM_BOARD_DO    ,  CN_NUM_BOARD_DO    ,    "DO板卡",                 "CFG_DO_BOARD"},
	{ EN_CFG_DC_BOARD    ,   (BYTE*)&g_tBoardDCTab[0]    ,    g_NUM_BOARD_DC    ,  CN_NUM_BOARD_DC    ,    "DC板卡",                 "CFG_DC_BOARD"},
	{ EN_CFG_PARA_BOARD  ,   (BYTE*)&g_tBoardParaTab[0]  ,    g_NUM_BOARD_PARA  ,  CN_NUM_BOARD_PARA  ,    "参数分类",                 "CFG_PARA_BOARD"},
	{ EN_CFG_RUN         ,   (BYTE*)&g_tRunTab[0]        ,    g_NUM_RUN         ,  CN_NUM_RUN         ,    "运行事项",                 "CFG_RUN"},
	{ EN_CFG_OPT         ,   (BYTE*)&g_tOptTab[0]        ,    g_NUM_OPT         ,  CN_NUM_OPT         ,    "操作事项",                 "CFG_OPT"},
	{ EN_CFG_COM_INIT    ,   (BYTE*)&g_tComInitTab[0]    ,    g_NUM_COM_INIT    ,  g_NUM_COM_INIT     ,    "板间交互初始化",              "CFG_COM_INIT"},
	{ EN_CFG_COM_FAST1_2 ,   (BYTE*)&g_tComFast1To2Tab[0],    g_NUM_COM1TO2_FAST,  g_NUM_COM1TO2_FAST ,    "板间交互快速信息1-2",          "CFG_COM_FAST1_2"},
	{ EN_CFG_COM_FAST2_1 ,   (BYTE*)&g_tComFast2To1Tab[0],    g_NUM_COM2TO1_FAST,  g_NUM_COM2TO1_FAST ,    "板间交互快速信息2-1",          "CFG_COM_FAST2_1"},
	{ EN_CFG_COM_SLOW1_2 ,   (BYTE*)&g_tComSlow1To2Tab[0],    g_NUM_COM1TO2_SLOW,  g_NUM_COM1TO2_SLOW ,    "板间交互慢速信息1-2",          "CFG_COM_SLOW1_2"},
	{ EN_CFG_COM_SLOW2_1 ,   (BYTE*)&g_tComSlow2To1Tab[0],    g_NUM_COM2TO1_SLOW,  g_NUM_COM2TO1_SLOW ,    "板间交互慢速信息2-1",          "CFG_COM_SLOW2_1"},
};
const DWORD g_NUM_CFG = sizeof(g_tCfgTab) / sizeof(tagCfgTab);

// 系数常量表
const UINT32  g_dwMul[] = 
{
	1,		10,		100,		1000,
	10000,	100000,	1000000,	10000000
};
// 倍率常量表
const FLOAT32 g_fDiv[] = 
{
	1.0f,          0.1f,		0.01f,		0.001f,
	0.0001f,    0.00001f,	0.000001f,	0.0000001f
};
// 比特位常量表
const UINT32    g_dwBit[] =
{
	DB0,	DB1,	DB2,	DB3,	DB4,	DB5,	DB6,	DB7,
	DB8,	DB9,	DB10,	DB11,	DB12,	DB13,	DB14,	DB15,
	DB16,	DB17,	DB18,	DB19,	DB20,	DB21,	DB22,	DB23,
	DB24,	DB25,	DB26,	DB27,	DB28,	DB29,	DB30,	DB31
};

