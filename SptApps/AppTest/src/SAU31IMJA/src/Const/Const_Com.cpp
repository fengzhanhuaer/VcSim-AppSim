#include "IES_IMSrc.h"

tagComVer     g_tComVer[2];

tagCom        g_tComFastTx;               // 板间交互快速数据发送组帧
tagCom        g_tComSlowTx;               // 板间交互快速数据发送组帧
tagCom        g_tComFastRx;               // 板间交互慢速数据接收缓存
tagCom        g_tComSlowRx;               // 板间交互慢速数据接收缓存

//================================================================================
// 交互数据常量表
/*================================================================================
BYTE		   *pwSrcAddr;					   // 数据源地址
BYTE		   *pwDstAddr;					   // 数据目的地址
DWORD			dwLen;						   // 数据长度
DWORD			dwCfg;						   // 通道其他属性
================================================================================*/
// 上电初始化数据交互常量表【仅母线板向间隔板传输】
const tagComSlowTab g_tComInitTab[] =
{
	{ (BYTE*)(g_tagPara.dwCrc)                           ,  sizeof(g_tagPara.dwCrc)                              ,NULL,  (BYTE*)g_tagPara.dwCrcOth                            ,  sizeof(g_tagPara.dwCrcOth)                         ,NULL},
	{ (BYTE*)&g_tagIO.byGoCbSubNum                       ,  sizeof(g_tagIO.byGoCbSubNumCom)                      ,NULL,  (BYTE*)&g_tagIO.byGoCbSubNumCom                      ,  sizeof(g_tagIO.byGoCbSubNumCom)                    ,NULL},
	// 版本信息
	{ (BYTE*)&g_tDevInfor.dwCrc                          ,  sizeof(g_tDevInfor.dwCrc)                            ,NULL,  (BYTE*)&g_tDevInfor.dwCrcOth                         ,  sizeof(g_tDevInfor.dwCrcOth)                       ,NULL},
	{ (BYTE*)&g_tComVer[CN_BOARD_CPU]                    ,  sizeof(tagComVer)                                    ,NULL,  (BYTE*)&g_tComVer[CN_BOARD_CPU_OTH]                  ,  sizeof(tagComVer)                                  ,NULL},
	{ (BYTE*)&g_tDevInfor.byVerName                      ,  sizeof(g_tDevInfor.byVerName)                        ,NULL,  (BYTE*)&g_tDevInfor.byVerOthName                     ,  sizeof(g_tDevInfor.byVerOthName)                   ,NULL},
};
const DWORD g_NUM_COM_INIT= sizeof(g_tComInitTab) / sizeof(tagComSlowTab);
// 快速数据交互常量表(CPU1-CPU2)
const tagComFastTab g_tComFast1To2Tab[] =
{
	{(BYTE*)&g_tAlmState.bAlmOut[EN_ALM_BSCH] ,  (BYTE*)&g_tagIO.bGoOutCom[EN_GOOUT_ALM_BSCH],0},
	{(BYTE*)&g_bFlag[EN_FLAG_RESET]           ,  (BYTE*)&g_bFlag[EN_FLAG_RESET_DBG]          ,0},
};
const DWORD g_NUM_COM1TO2_FAST= sizeof(g_tComFast1To2Tab) / sizeof(tagComFastTab);
// 快速数据交互常量表(CPU2-CPU1),禁止有互传数据
const tagComFastTab g_tComFast2To1Tab[] =
{
	{&g_bFlag[EN_FLAG_ALM]               ,        &g_bFlag[EN_FLAG_ALM_COM]       ,0},
	{&g_bFlag[EN_FLAG_CHK]               ,        &g_bFlag[EN_FLAG_CHK_COM]       ,0},
	{&g_bFlag[EN_FLAG_DBG]               ,        &g_bFlag[EN_FLAG_DBG_COM]       ,0},

	{&g_bFlag[EN_FLAG_ALM]               ,        &g_tAlmState.bAlmIn[EN_ALM_BOARD_CPU2]       ,0},
	{&g_bFlag[EN_FLAG_CHK]               ,        &g_tChkState.bChkIn[EN_CHK_BOARD_CPU2]       ,0},
	// 快速信息
	{&g_tagIO.bGoOut[EN_GOOUT_ALM_SYN]   ,        &g_tagIO.bGoOutCom[EN_GOOUT_ALM_SYN]   ,  0},
	{&g_tagIO.bGoOut[EN_GOOUT_ALM_KI]    ,        &g_tagIO.bGoOutCom[EN_GOOUT_ALM_KI]    ,  0},
	{&g_tagIO.bGoOut[EN_GOOUT_ALM_SV]    ,        &g_tagIO.bGoOutCom[EN_GOOUT_ALM_SV]    ,  0},
	{&g_tagIO.bGoOut[EN_GOOUT_ALM_GOOSE] ,        &g_tagIO.bGoOutCom[EN_GOOUT_ALM_GOOSE] ,  0},
	{&g_tagIO.bGoOut[EN_GOOUT_ALM_GOCB01],        &g_tagIO.bGoOutCom[EN_GOOUT_ALM_GOCB13],  0},
	{&g_tagIO.bGoOut[EN_GOOUT_ALM_GOCB02],        &g_tagIO.bGoOutCom[EN_GOOUT_ALM_GOCB14],  0},
	{&g_tagIO.bGoOut[EN_GOOUT_ALM_GOCB03],        &g_tagIO.bGoOutCom[EN_GOOUT_ALM_GOCB15],  0},
	{&g_tagIO.bGoOut[EN_GOOUT_ALM_GOCB04],        &g_tagIO.bGoOutCom[EN_GOOUT_ALM_GOCB16],  0},
	{&g_tagIO.bGoOut[EN_GOOUT_ALM_GOCB05],        &g_tagIO.bGoOutCom[EN_GOOUT_ALM_GOCB17],  0},
	{&g_tagIO.bGoOut[EN_GOOUT_ALM_GOCB06],        &g_tagIO.bGoOutCom[EN_GOOUT_ALM_GOCB18],  0},
	{&g_tagIO.bGoOut[EN_GOOUT_ALM_GOCB07],        &g_tagIO.bGoOutCom[EN_GOOUT_ALM_GOCB19],  0},
	{&g_tagIO.bGoOut[EN_GOOUT_ALM_GOCB08],        &g_tagIO.bGoOutCom[EN_GOOUT_ALM_GOCB20],  0},
	{&g_tagIO.bGoOut[EN_GOOUT_ALM_GOCB09],        &g_tagIO.bGoOutCom[EN_GOOUT_ALM_GOCB21],  0},
	{&g_tagIO.bGoOut[EN_GOOUT_ALM_GOCB10],        &g_tagIO.bGoOutCom[EN_GOOUT_ALM_GOCB22],  0},
	{&g_tagIO.bGoOut[EN_GOOUT_ALM_GOCB11],        &g_tagIO.bGoOutCom[EN_GOOUT_ALM_GOCB23],  0},
	{&g_tagIO.bGoOut[EN_GOOUT_ALM_GOCB12],        &g_tagIO.bGoOutCom[EN_GOOUT_ALM_GOCB24],  0},

	{&g_tagIO.bGoOut[EN_GOOUT_TEST_ERR]  ,        &g_tagIO.bGoOutCom[EN_GOOUT_TEST_ERR]  ,  0},
	{&g_tagIO.bGoOut[EN_GOOUT_IN_BHTZ]   ,        &g_tagIO.bGoOutCom[EN_GOOUT_IN_BHTZ]   ,  0},
	{&g_tagIO.bGoOut[EN_GOOUT_IN_BHYT]   ,        &g_tagIO.bGoOutCom[EN_GOOUT_IN_BHYT]   ,  0},
	{&g_tagIO.bGoOut[EN_GOOUT_IN_BHHZ]   ,        &g_tagIO.bGoOutCom[EN_GOOUT_IN_BHHZ]   ,  0},
	{&g_tagIO.bGoOut[EN_GOOUT_IN_BZTTZ]  ,        &g_tagIO.bGoOutCom[EN_GOOUT_IN_BZTTZ]  ,  0},
	{&g_tagIO.bGoOut[EN_GOOUT_IN_BZTHZ]  ,        &g_tagIO.bGoOutCom[EN_GOOUT_IN_BZTHZ]  ,  0},
	{&g_tagIO.bGoOut[EN_GOOUT_PARACHG]   ,        &g_tagIO.bGoOutCom[EN_GOOUT_PARACHG]   ,  0},
	{&g_tagIO.bGoOut[EN_GOOUT_TIME_SINGLE],       &g_tagIO.bGoOutCom[EN_GOOUT_TIME_SINGLE], 0},
	{&g_tagIO.bGoOut[EN_GOOUT_TIME_SERVIC],       &g_tagIO.bGoOutCom[EN_GOOUT_TIME_SERVIC], 0},
	{&g_tagIO.bGoOut[EN_GOOUT_TIME_CHKERR],       &g_tagIO.bGoOutCom[EN_GOOUT_TIME_CHKERR], 0},
	{&g_tAlmState.bAlmOut[EN_ALM_BSCH]    ,       &g_tagIO.bGoOutCom[EN_GOOUT_ALM_BSCH]   , 0},
	// 指示灯部分  
	{&g_tagIO.bLedOut[EN_LED_GO_ERR]     ,        &g_tagIO.bLedOutCom[EN_LED_GO_ERR]      , 0},
	{&g_tagIO.bLedOut[EN_LED_TEST_ERR]   ,        &g_tagIO.bLedOutCom[EN_LED_TEST_ERR]    , 0},
	{&g_tagIO.bLedOut[EN_LED_SYN_ERR]    ,        &g_tagIO.bLedOutCom[EN_LED_SYN_ERR]     , 0},
	{&g_tagIO.bLedOut[EN_LED_SAM_ERR]    ,        &g_tagIO.bLedOutCom[EN_LED_SAM_ERR]     , 0},
	{&g_tagIO.bLedOut[EN_LED_BHTZ]       ,        &g_tagIO.bLedOutCom[EN_LED_BHTZ]        , 0},
	{&g_tagIO.bLedOut[EN_LED_BHHZ]       ,        &g_tagIO.bLedOutCom[EN_LED_BHHZ]        , 0},
	{&g_tagIO.bLedOut[EN_LED_BAK21]      ,        &g_tagIO.bLedOutCom[EN_LED_BAK21]       , 0},
	{&g_tagIO.bLedOut[EN_LED_BAK22]      ,        &g_tagIO.bLedOutCom[EN_LED_BAK22]       , 0},
	{&g_tagIO.bLedOut[EN_LED_BAK23]      ,        &g_tagIO.bLedOutCom[EN_LED_BAK23]       , 0},
	{&g_tagIO.bLedOut[EN_LED_BAK24]      ,        &g_tagIO.bLedOutCom[EN_LED_BAK24]       , 0},
	{&g_tagIO.bLedOut[EN_LED_BAK31]      ,        &g_tagIO.bLedOutCom[EN_LED_BAK31]       , 0},
	{&g_tagIO.bLedOut[EN_LED_BAK32]      ,        &g_tagIO.bLedOutCom[EN_LED_BAK32]       , 0},
};
const DWORD g_NUM_COM2TO1_FAST= sizeof(g_tComFast2To1Tab) / sizeof(tagComFastTab);

// 慢速数据交互常量表(CPU1-CPU2)
const tagComSlowTab g_tComSlow1To2Tab[] =
{
	// 参数CRC
	{(BYTE*)g_tagPara.dwCrc               ,sizeof(g_tagPara.dwCrc)     ,&g_tagPara.bCrcCom                     , (BYTE*)g_tagPara.dwCrcOth              ,  sizeof(g_tagPara.dwCrcOth)                              ,&g_tagPara.bCrcOthChg},
	// IP地址
	{(BYTE*)&g_tDevInfor.tDevEthnet       ,sizeof(tagDevEthnet)        ,&g_tDevInfor.byDevEthnet               , (BYTE*)&g_tDevInfor.tDevEthnetOth      ,  sizeof(tagDevEthnet)                                    ,NULL},

};
const DWORD g_NUM_COM1TO2_SLOW= sizeof(g_tComSlow1To2Tab) / sizeof(tagComSlowTab);
// 慢速数据交互常量表(CPU2-CPU1)
const tagComSlowTab g_tComSlow2To1Tab[] =
{
	// 参数CRC
	{(BYTE*)g_tagPara.dwCrc                ,sizeof(g_tagPara.dwCrc)                                 ,&g_tagPara.bCrcCom                     , (BYTE*)g_tagPara.dwCrcOth               ,  sizeof(g_tagPara.dwCrcOth)                              ,&g_tagPara.bCrcOthChg},
	// 光功率
	{(BYTE*)&g_tagDC.iDCIn[EN_DC_OPT2_STR] ,CN_NUM_DC_OPT2*sizeof(g_tagDC.iDCIn[EN_DC_OPT2_STR])    ,&g_tagDC.bDCCommFresh[EN_BOARD_DC_OPT2], (BYTE*)&g_tagDC.iDCIn[EN_DC_OPT2_STR]    ,  CN_NUM_DC_OPT2*sizeof(g_tagDC.iDCIn[EN_DC_OPT2_STR])   ,&g_tagDC.bDCFresh[EN_BOARD_DC_OPT2]},
	// 温湿度、内部电压
	{(BYTE*)&g_tagDC.iDCIn[EN_DC_DEV2_STR] ,CN_NUM_DC_DEV_CPU2*sizeof(g_tagDC.iDCIn[EN_DC_DEV2_STR]),&g_tagDC.bDCCommFresh[EN_BOARD_DC_DEV] , (BYTE*)&g_tagDC.iDCIn[EN_DC_DEV2_STR]    ,  CN_NUM_DC_DEV_CPU2*sizeof(g_tagDC.iDCIn[EN_DC_DEV2_STR]),NULL},
	// IP地址
	{(BYTE*)&g_tDevInfor.tDevEthnet,                         sizeof(tagDevEthnet)                   ,&g_tDevInfor.byDevEthnet               , (BYTE*)&g_tDevInfor.tDevEthnetOth        ,  sizeof(tagDevEthnet)                                    ,NULL},

};
const DWORD g_NUM_COM2TO1_SLOW= sizeof(g_tComSlow2To1Tab) / sizeof(tagComSlowTab);

