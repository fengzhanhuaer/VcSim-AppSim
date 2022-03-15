#include "Const_Pub.h"

/*================================================================================*/
//1. 硬开入单点开入常量表
/*================================================================================
    WORD            wIndex;                         // 硬开入枚举
    WORD            wCfg;                           // 硬开入其他功能配置
    INT8S           byName[CN_LEN_NAME];            // 硬开入量名称
    INT8S           byPinName[CN_LEN_NAME];         // 硬开入量短地址名称
*================================================================================*/
const tagDiTab  g_tDiTab[] =
// 常量表声明
{
/*=============================*/
// DWORD1.开入板1
/*=============================*/
	// wIndex               wCfg byName               byPinName
	{EN_DI_TEST,            0,  "检修状态",           "DI_TEST"},
	{EN_DI_RESET,           0,  "信号复归",           "DI_RESET"},
	{EN_DI_XCBR_OPN,        0,  "断路器分位",         "DI_XCBR_OPN"},
	{EN_DI_XCBR_CLS,        0,  "断路器合位",         "DI_XCBR_CLS"},
	{EN_DI_XSWI01_OPN,      0,  "刀闸1分位",          "DI_XSWI01_OPN"},
	{EN_DI_XSWI01_CLS,      0,  "刀闸1合位",          "DI_XSWI01_CLS"},
	{EN_DI_XSWI02_OPN,      0,  "刀闸2分位",          "DI_XSWI02_OPN"},
	{EN_DI_XSWI02_CLS,      0,  "刀闸2合位",          "DI_XSWI02_CLS"},
	{EN_DI_XSWI03_OPN,      0,  "刀闸3分位",          "DI_XSWI03_OPN"},
	{EN_DI_XSWI03_CLS,      0,  "刀闸3合位",          "DI_XSWI03_CLS"},
	{EN_DI_XSWI04_OPN,      0,  "刀闸4分位",          "DI_XSWI04_OPN"},
	{EN_DI_XSWI04_CLS,      0,  "刀闸4合位",          "DI_XSWI04_CLS"},
	{EN_DI_XSWI05_OPN,      0,  "刀闸5分位",          "DI_XSWI05_OPN"},
	{EN_DI_XSWI05_CLS,      0,  "刀闸5合位",          "DI_XSWI05_CLS"},
	{EN_DI_XSWI06_OPN,      0,  "刀闸6分位",          "DI_XSWI06_OPN"},
	{EN_DI_XSWI06_CLS,      0,  "刀闸6合位",          "DI_XSWI06_CLS"},
	{EN_DI_XSWI07_OPN,      0,  "刀闸7分位",          "DI_XSWI07_OPN"},
	{EN_DI_XSWI07_CLS,      0,  "刀闸7合位",          "DI_XSWI07_CLS"},
	{EN_DI_XSWI08_OPN,      0,  "刀闸8分位",          "DI_XSWI08_OPN"},
	{EN_DI_XSWI08_CLS,      0,  "刀闸8合位",          "DI_XSWI08_CLS"},
	{EN_DI_BC_YLD,          0,  "压力低闭重",         "DI_BC_YLD"  },
	{EN_DI_BC_OTH,          0,  "另一套闭重信号",     "DI_BC_OTH"  },
	{EN_DI_TJF,             0,  "TJF跳闸信号",        "DI_TJF"  },
	{EN_DI_STJ,             0,  "手跳",               "DI_STJ"  },
	{EN_DI_SHJ,             0,  "手合",               "DI_SHJ"  },
	{EN_DI_KKJ,             0,  "合后",               "DI_KKJ"  },
	{EN_DI_LNK_A,           0,  "取A套",              "DI_LNK_A"  },
	{EN_DI_LNK_B,           0,  "取B套",              "DI_LNK_B"  },
	{EN_DI_LNK_AUTO,        0,  "自动",               "DI_LNK_AUTO"},
	{EN_DI_SHJ_SYN,         0,  "手合同期开入",        "DI_SHJ_SYN"},
	{EN_DI_POW1,            0,  "开入板1电源监视",     "DI_POW1"},
/*=============================*/
// DWORD2.开入板2
/*=============================*/
	// wIndex              wCfg byName                       byPinName
	{EN_DI_OTH_ALM,         0,  "另一套采执运行异常", "DI_OTH_ALM"      },
	{EN_DI_OTH_CHK,         0,  "另一套采执故障","DI_OTH_CHK"},
	{EN_DI_YX_BAK01,        0,  "备用开入01",     "DI_YX_BAK01"},
	{EN_DI_YX_BAK02,        0,  "备用开入02",     "DI_YX_BAK02"},
	{EN_DI_YX_BAK03,        0,  "备用开入03",     "DI_YX_BAK03"},
	{EN_DI_YX_BAK04,        0,  "备用开入04",     "DI_YX_BAK04"},
	{EN_DI_YX_BAK05,        0,  "备用开入05",     "DI_YX_BAK05"},
	{EN_DI_YX_BAK06,        0,  "备用开入06",     "DI_YX_BAK06"},
	{EN_DI_YX_BAK07,        0,  "备用开入07",     "DI_YX_BAK07"},
	{EN_DI_YX_BAK08,        0,  "备用开入08",     "DI_YX_BAK08"},
	{EN_DI_YX_BAK09,        0,  "备用开入09",     "DI_YX_BAK09"},
	{EN_DI_YX_BAK10,        0,  "备用开入10",     "DI_YX_BAK10"},
	{EN_DI_YX_BAK11,        0,  "备用开入11",     "DI_YX_BAK11"},
	{EN_DI_YX_BAK12,        0,  "备用开入12",     "DI_YX_BAK12"},
	{EN_DI_YX_BAK13,        0,  "备用开入13",     "DI_YX_BAK13"},
	{EN_DI_YX_BAK14,        0,  "备用开入14",     "DI_YX_BAK14"},
	{EN_DI_YX_BAK15,        0,  "备用开入15",     "DI_YX_BAK15"},
	{EN_DI_YX_BAK16,        0,  "备用开入16",     "DI_YX_BAK16"},
	{EN_DI_YX_BAK17,        0,  "备用开入17",     "DI_YX_BAK17"},
	{EN_DI_YX_BAK18,        0,  "备用开入18",     "DI_YX_BAK18"},
	{EN_DI_YX_BAK19,        0,  "备用开入19",     "DI_YX_BAK19"},
	{EN_DI_YX_BAK20,        0,  "备用开入20",     "DI_YX_BAK20"},
	{EN_DI_YX_BAK21,        0,  "备用开入21",     "DI_YX_BAK21"},
	{EN_DI_YX_BAK22,        0,  "备用开入22",     "DI_YX_BAK22"},
	{EN_DI_YX_BAK23,        0,  "备用开入23",     "DI_YX_BAK23"},
	{EN_DI_YX_BAK24,        0,  "备用开入24",     "DI_YX_BAK24"},
	{EN_DI_YX_BAK25,        0,  "备用开入25",     "DI_YX_BAK25"},
	{EN_DI_YX_BAK26,        0,  "备用开入26",     "DI_YX_BAK26"},
	{EN_DI_YX_BAK27,        0,  "备用开入27",     "DI_YX_BAK27"},
	{EN_DI_YX_BAK28,        0,  "备用开入28",     "DI_YX_BAK28"},
	{EN_DI_POW2,            0,  "开入板2电源监视","DI_POW2"},
/*=============================*/
// DWORD3.开入板3
/*=============================*/
	// wIndex              wCfg byName        byPinName
	{EN_DI_YX_BAK29,        0,  "备用开入29",     "DI_YX_BAK29"},
	{EN_DI_YX_BAK30,        0,  "备用开入30",     "DI_YX_BAK30"},
	{EN_DI_YX_BAK31,        0,  "备用开入31",     "DI_YX_BAK31"},
	{EN_DI_YX_BAK32,        0,  "备用开入32",     "DI_YX_BAK32"},
	{EN_DI_YX_BAK33,        0,  "备用开入33",     "DI_YX_BAK33"},
	{EN_DI_YX_BAK34,        0,  "备用开入34",     "DI_YX_BAK34"},
	{EN_DI_YX_BAK35,        0,  "备用开入35",     "DI_YX_BAK35"},
	{EN_DI_YX_BAK36,        0,  "备用开入36",     "DI_YX_BAK36"},
	{EN_DI_YX_BAK37,        0,  "备用开入37",     "DI_YX_BAK37"},
	{EN_DI_YX_BAK38,        0,  "备用开入38",     "DI_YX_BAK38"},
	{EN_DI_YX_BAK39,        0,  "备用开入39",     "DI_YX_BAK39"},
	{EN_DI_YX_BAK40,        0,  "备用开入40",     "DI_YX_BAK40"},
	{EN_DI_YX_BAK41,        0,  "备用开入41",     "DI_YX_BAK41"},
	{EN_DI_YX_BAK42,        0,  "备用开入42",     "DI_YX_BAK42"},
	{EN_DI_YX_BAK43,        0,  "备用开入43",     "DI_YX_BAK43"},
	{EN_DI_YX_BAK44,        0,  "备用开入44",     "DI_YX_BAK44"},
	{EN_DI_YX_BAK45,        0,  "备用开入45",     "DI_YX_BAK45"},
	{EN_DI_YX_BAK46,        0,  "备用开入46",     "DI_YX_BAK46"},
	{EN_DI_YX_BAK47,        0,  "备用开入47",     "DI_YX_BAK47"},
	{EN_DI_YX_BAK48,        0,  "备用开入48",     "DI_YX_BAK48"},
	{EN_DI_YX_BAK49,        0,  "备用开入49",     "DI_YX_BAK49"},
	{EN_DI_YX_BAK50,        0,  "备用开入50",     "DI_YX_BAK50"},
	{EN_DI_YX_BAK51,        0,  "备用开入51",     "DI_YX_BAK51"},
	{EN_DI_YX_BAK52,        0,  "备用开入52",     "DI_YX_BAK52"},
	{EN_DI_YX_BAK53,        0,  "备用开入53",     "DI_YX_BAK53"},
	{EN_DI_YX_BAK54,        0,  "备用开入54",     "DI_YX_BAK54"},
	{EN_DI_YX_BAK55,        0,  "备用开入55",     "DI_YX_BAK55"},
	{EN_DI_YX_BAK56,        0,  "备用开入56",     "DI_YX_BAK56"},
	{EN_DI_YX_BAK57,        0,  "备用开入57",     "DI_YX_BAK57"},
	{EN_DI_YX_BAK58,        0,  "备用开入58",     "DI_YX_BAK58"},
	{EN_DI_POW3,            0,  "开入板3电源监视","DI_POW3"},
/*=============================*/
// DWORD4.开入板4
/*=============================*/
	// wIndex             wCfg  byName        byPinName
	{EN_DI_YX_BAK59,        0,  "备用开入59",     "DI_YX_BAK59"},
	{EN_DI_YX_BAK60,        0,  "备用开入60",     "DI_YX_BAK60"},
	{EN_DI_YX_BAK61,        0,  "备用开入61",     "DI_YX_BAK61"},
	{EN_DI_YX_BAK62,        0,  "备用开入62",     "DI_YX_BAK62"},
	{EN_DI_YX_BAK63,        0,  "备用开入63",     "DI_YX_BAK63"},
	{EN_DI_YX_BAK64,        0,  "备用开入64",     "DI_YX_BAK64"},
	{EN_DI_YX_BAK65,        0,  "备用开入65",     "DI_YX_BAK65"},
	{EN_DI_YX_BAK66,        0,  "备用开入66",     "DI_YX_BAK66"},
	{EN_DI_YX_BAK67,        0,  "备用开入67",     "DI_YX_BAK67"},
	{EN_DI_YX_BAK68,        0,  "备用开入68",     "DI_YX_BAK68"},
	{EN_DI_YX_BAK69,        0,  "备用开入69",     "DI_YX_BAK69"},
	{EN_DI_YX_BAK70,        0,  "备用开入70",     "DI_YX_BAK70"},
	{EN_DI_YX_BAK71,        0,  "备用开入71",     "DI_YX_BAK71"},
	{EN_DI_POW4,            0,  "开入开出板电源监视","DI_POW4"},
//	{EN_DI_YX_BAK72,        0,  "备用开入72",     "DI_YX_BAK72"},
//	{EN_DI_YX_BAK73,        0,  "备用开入73",     "DI_YX_BAK73"},
//	{EN_DI_YX_BAK74,        0,  "备用开入74",     "DI_YX_BAK74"},
//	{EN_DI_YX_BAK75,        0,  "备用开入75",     "DI_YX_BAK75"},
//	{EN_DI_YX_BAK76,        0,  "备用开入76",     "DI_YX_BAK76"},
//	{EN_DI_YX_BAK77,        0,  "备用开入77",     "DI_YX_BAK77"},
//	{EN_DI_YX_BAK78,        0,  "备用开入78",     "DI_YX_BAK78"},
//	{EN_DI_YX_BAK79,        0,  "备用开入79",     "DI_YX_BAK79"},
//	{EN_DI_YX_BAK80,        0,  "备用开入80",     "DI_YX_BAK80"},
//	{EN_DI_YX_BAK81,        0,  "备用开入81",     "DI_YX_BAK81"},
//	{EN_DI_YX_BAK82,        0,  "备用开入82",     "DI_YX_BAK82"},
//	{EN_DI_YX_BAK83,        0,  "备用开入83",     "DI_YX_BAK83"},
//	{EN_DI_YX_BAK84,        0,  "备用开入84",     "DI_YX_BAK84"},
//	{EN_DI_YX_BAK85,        0,  "备用开入85",     "DI_YX_BAK85"},
//	{EN_DI_YX_BAK86,        0,  "备用开入86",     "DI_YX_BAK86"},
//	{EN_DI_YX_BAK87,        0,  "备用开入87",     "DI_YX_BAK87"},
//	{EN_DI_YX_BAK88,        0,  "备用开入88",     "DI_YX_BAK88"},
/*=============================*/
// DWORD5.操作回路板内采
/*=============================*/
	{EN_DI_OPB1_HWJ,        0,  "跳闸回路监视",   "DI_OPB1_HWJ"},
	{EN_DI_OPB1_TWJ,        0,  "合闸回路监视",   "DI_OPB1_TWJ"},
	{EN_DI_OPB1_POW,        0,  "操作电源监视",   "DI_OPB1_POW"},
	{EN_DI_OPB1_KKJ,        0,  "KKJ",   "DI_OPB1_KKJ"},
	{EN_DI_OPB1_TJF,        0,  "TJF",   "DI_OPB1_TJF"},
	{EN_DI_OPB1_STJ,        0,  "STJ",   "DI_OPB1_STJ"},
	{EN_DI_OPB1_SHJ,        0,  "SHJ",   "DI_OPB1_SHJ"},

//	{EN_DI_OPB2_HWJ,        0,  "OPB2 跳闸回路监视",   "DI_OPB2_HWJ"},
//	{EN_DI_OPB2_TWJ,        0,  "OPB2 合闸回路监视",   "DI_OPB2_TWJ"},
//	{EN_DI_OPB2_POW,        0,  "OPB2 操作电源监视",   "DI_OPB2_POW"},
//	{EN_DI_OPB2_KKJ,        0,  "OPB2 KKJ",   "DI_OPB2_KKJ"},
//	{EN_DI_OPB2_TJF,        0,  "OPB2 TJF",   "DI_OPB2_TJF"},
//	{EN_DI_OPB2_STJ,        0,  "OPB2 STJ",   "DI_OPB2_STJ"},
//	{EN_DI_OPB2_SHJ,        0,  "OPB2 SHJ",   "DI_OPB2_SHJ"},
/*=============================*/
// DWORD6.开出板1
/*=============================*/
	// wIndex             wCfg  byName               byPinName
	{EN_DI_DO_BHTZ ,        0,  "跳闸出口回采",            "DI_DO_BHTZ"},
	{EN_DI_DO_BHHZ ,        0,  "合闸出口回采",            "DI_DO_BHHZ"},
	{EN_DI_DO_BZTTZ,        0,  "备自投跳闸出口回采",   "DI_DO_BZTTZ"},
	{EN_DI_DO_BZTHZ,        0,  "备自投合闸出口回采",   "DI_DO_BZTHZ"},
	{EN_DI_DO_BAK1 ,        0,  "备用出口1回采",           "DI_DO_BAK1"},
	{EN_DI_DO_BAK2 ,        0,  "备用出口2回采",           "DI_DO_BAK2"},
	{EN_DI_DO_BAK3 ,        0,  "备用出口3回采",           "DI_DO_BAK3"},
	{EN_DI_DO_BAK4 ,        0,  "备用出口4回采",           "DI_DO_BAK4"},
	{EN_DI_DO_XCBR_OPN  ,   0,  "遥控分闸出口回采",            "DI_DO_XCBR_OPN"},
	{EN_DI_DO_XCBR_CLS  ,   0,  "遥控合闸出口回采",            "DI_DO_XCBR_CLS"},
	{EN_DI_DO_BSCH      ,   0,  "闭锁重合闸出口回采",           "DI_DO_BSCH"},
	{EN_DI_DO_XCBR_JBS  ,   0,  "断路器解闭锁出口回采",          "DI_DO_XCBR_JBS"},
	{EN_DI_DO_XSWI01_JBS,   0,  "刀闸1解闭锁出口回采",          "DI_DO_XSWI01_JBS"},
	{EN_DI_DO_XSWI02_JBS,   0,  "刀闸2解闭锁出口回采",          "DI_DO_XSWI02_JBS"},
	{EN_DI_DO_XSWI03_JBS,   0,  "刀闸3解闭锁出口回采",          "DI_DO_XSWI03_JBS"},
	{EN_DI_DO_XSWI04_JBS,   0,  "刀闸4解闭锁出口回采",          "DI_DO_XSWI04_JBS"},
/*=============================*/
// DWORD7.开出板2
/*=============================*/
	{EN_DI_DO_XSWI05_JBS,   0,  "刀闸5解闭锁出口回采",          "DI_DO_XSWI05_JBS"},
	{EN_DI_DO_XSWI06_JBS,   0,  "刀闸6解闭锁出口回采",          "DI_DO_XSWI06_JBS"},
	{EN_DI_DO_XSWI07_JBS,   0,  "刀闸7解闭锁出口回采",          "DI_DO_XSWI07_JBS"},
	{EN_DI_DO_XSWI08_JBS,   0,  "刀闸8解闭锁出口回采",          "DI_DO_XSWI08_JBS"},
	{EN_DI_DO_XSWI01_OPN,   0,  "刀闸1分闸出口回采",           "DI_DO_XSWI01_OPN"},
	{EN_DI_DO_XSWI01_CLS,   0,  "刀闸1合闸出口回采",           "DI_DO_XSWI01_CLS"},
	{EN_DI_DO_XSWI02_OPN,   0,  "刀闸2分闸出口回采",           "DI_DO_XSWI02_OPN"},
	{EN_DI_DO_XSWI02_CLS,   0,  "刀闸2合闸出口回采",           "DI_DO_XSWI02_CLS"},
	{EN_DI_DO_XSWI03_OPN,   0,  "刀闸3分闸出口回采",           "DI_DO_XSWI03_OPN"},
	{EN_DI_DO_XSWI03_CLS,   0,  "刀闸3合闸出口回采",           "DI_DO_XSWI03_CLS"},
	{EN_DI_DO_XSWI04_OPN,   0,  "刀闸4分闸出口回采",           "DI_DO_XSWI04_OPN"},
	{EN_DI_DO_XSWI04_CLS,   0,  "刀闸4合闸出口回采",           "DI_DO_XSWI04_CLS"},
	{EN_DI_DO_XSWI05_OPN,   0,  "刀闸5分闸出口回采",           "DI_DO_XSWI05_OPN"},
	{EN_DI_DO_XSWI05_CLS,   0,  "刀闸5合闸出口回采",           "DI_DO_XSWI05_CLS"},
	{EN_DI_DO_XSWI06_OPN,   0,  "刀闸6分闸出口回采",           "DI_DO_XSWI06_OPN"},
	{EN_DI_DO_XSWI06_CLS,   0,  "刀闸6合闸出口回采",           "DI_DO_XSWI06_CLS"},
/*=============================*/
// DWORD8.开入开出板出口返校
/*=============================*/
	{EN_DI_DO_XSWI07_OPN,   0,  "刀闸7分闸出口回采",           "DI_DO_XSWI07_OPN"},
	{EN_DI_DO_XSWI07_CLS,   0,  "刀闸7合闸出口回采",           "DI_DO_XSWI07_CLS"},
	{EN_DI_DO_XSWI08_OPN,   0,  "刀闸8分闸出口回采",           "DI_DO_XSWI08_OPN"},
	{EN_DI_DO_XSWI08_CLS,   0,  "刀闸8合闸出口回采",           "DI_DO_XSWI08_CLS"},
	{EN_DI_DO_YK_BAK1   ,   0,  "备用遥控1出口回采",           "DI_DO_YK_BAK1"},
	{EN_DI_DO_YK_BAK2   ,   0,  "备用遥控2出口回采",           "DI_DO_YK_BAK2"},
	{EN_DI_DO_BHBAK5    ,   0,  "备用出口5(常闭)回采",         "DI_DO_BHBAK5"},
};
const DWORD g_NUM_DI = sizeof(g_tDiTab) / sizeof(tagDiTab);
/*================================================================================*/
//2. 硬开入双点合成常量表
/*================================================================================
    WORD            wIndex;                         // 双点开入枚举
    WORD            wSrcType;                       // 关联信号源
    WORD            wSrcOpn;                        // 关联分位信号
    WORD            wSrcCls;                        // 关联合位信号
    WORD            wParaIndex;                     // 关联参数1
    WORD            wCfg;                           // 其他属性配置
    INT8S           byName[CN_LEN_NAME];            // 双点开入量名称
    INT8S           byPinName[CN_LEN_NAME];         // 双点开入量短地址名称
*================================================================================*/
const tagDpiTab  g_tDpiTab[] =
{
//	wIndex           wSrcType       wSrcOpn            wSrcCls            wParaIndex     wCfg             byName         byPinName
	//双点信息
	{EN_DPI_XCBR,     EN_DTYPE_DI,   EN_DI_XCBR_OPN,    EN_DI_XCBR_CLS,    CN_NULL_PINNO,  0,           "断路器位置",       "DPI_XCBR"},
	{EN_DPI_XSWI01,   EN_DTYPE_DI,   EN_DI_XSWI01_OPN,  EN_DI_XSWI01_CLS,  CN_NULL_PINNO,  0,           "刀闸1位置",       "DPI_XSWI01"},
	{EN_DPI_XSWI02,   EN_DTYPE_DI,   EN_DI_XSWI02_OPN,  EN_DI_XSWI02_CLS,  CN_NULL_PINNO,  0,           "刀闸2位置",       "DPI_XSWI02"},
	{EN_DPI_XSWI03,   EN_DTYPE_DI,   EN_DI_XSWI03_OPN,  EN_DI_XSWI03_CLS,  CN_NULL_PINNO,  0,           "刀闸3位置",       "DPI_XSWI03"},
	{EN_DPI_XSWI04,   EN_DTYPE_DI,   EN_DI_XSWI04_OPN,  EN_DI_XSWI04_CLS,  CN_NULL_PINNO,  0,           "刀闸4位置",       "DPI_XSWI04"},
	{EN_DPI_XSWI05,   EN_DTYPE_DI,   EN_DI_XSWI05_OPN,  EN_DI_XSWI05_CLS,  CN_NULL_PINNO,  0,           "刀闸5位置",       "DPI_XSWI05"},
	{EN_DPI_XSWI06,   EN_DTYPE_DI,   EN_DI_XSWI06_OPN,  EN_DI_XSWI06_CLS,  CN_NULL_PINNO,  0,           "刀闸6位置",       "DPI_XSWI06"},
	{EN_DPI_XSWI07,   EN_DTYPE_DI,   EN_DI_XSWI07_OPN,  EN_DI_XSWI07_CLS,  CN_NULL_PINNO,  0,           "刀闸7位置",       "DPI_XSWI07"},
	{EN_DPI_XSWI08,   EN_DTYPE_DI,   EN_DI_XSWI08_OPN,  EN_DI_XSWI08_CLS,  CN_NULL_PINNO,  0,           "刀闸8位置",       "DPI_XSWI08"},
};
const DWORD g_NUM_DPI = sizeof(g_tDpiTab) / sizeof(tagDpiTab);
/*================================================================================*/
//3. GOOSE订阅常量表
/*================================================================================
    WORD            wIndex;                         // GOOSE开入枚举号
    WORD            wChnType;                       // 信号类型
    WORD            wParaIndex;                     // 关联参数
    WORD            wCfg;                           // GOOSE开入其他功能配置
    INT8S           byName[CN_LEN_NAME];            // GOOSE开入名称
    INT8S           byPinName[CN_LEN_NAME];         // GOOSE开入短地址 
*================================================================================*/
const tagGoInTab  g_tGoInTab[] =
{
	{EN_GOIN_RESET   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "远方复归",     "GOIN_RESET" },
	{EN_GOIN_CKTZ    ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "测控跳闸",     "GOIN_CKTZ" },
	{EN_GOIN_CKHZ    ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "测控合闸",     "GOIN_CKHZ" },
	{EN_GOIN_JBS_XCBR,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "断路器解闭锁",     "GOIN_JBS_XCBR" },
	{EN_GOIN_BZTTZ1  ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "备自投跳闸1",  "GOIN_BZTTZ1" },
	{EN_GOIN_BZTTZ2  ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "备自投跳闸2",  "GOIN_BZTTZ2" },
	{EN_GOIN_BZTHZ1  ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "备自投合闸1",  "GOIN_BZTHZ1" },
	{EN_GOIN_BZTHZ2  ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "备自投合闸2",  "GOIN_BZTHZ2" },
	{EN_GOIN_BHTZ1   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "保护跳闸1",   "GOIN_BHTZ1" },
	{EN_GOIN_BHTZ2   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "保护跳闸2",   "GOIN_BHTZ2" },
	{EN_GOIN_BHTZ3   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "保护跳闸3",   "GOIN_BHTZ3" },
	{EN_GOIN_BHTZ4   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "保护跳闸4",   "GOIN_BHTZ4" },
	{EN_GOIN_BHTZ5   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "保护跳闸5",   "GOIN_BHTZ5" },
	{EN_GOIN_BHHZ1   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "保护重合闸1", "GOIN_BHHZ1" },
	{EN_GOIN_BHHZ2   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "保护重合闸2", "GOIN_BHHZ2" },
	{EN_GOIN_BHHZ3   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "保护重合闸3", "GOIN_BHHZ3" },
	{EN_GOIN_BHHZ4   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "保护重合闸4", "GOIN_BHHZ4" },
	{EN_GOIN_BHHZ5   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "保护重合闸5", "GOIN_BHHZ5" },
	{EN_GOIN_BSHZ1   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "闭锁重合闸1", "GOIN_BSHZ1" },
	{EN_GOIN_BSHZ2   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "闭锁重合闸2", "GOIN_BSHZ2" },
	{EN_GOIN_BSHZ3   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "闭锁重合闸3", "GOIN_BSHZ3" },
	{EN_GOIN_BSHZ4   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "闭锁重合闸4", "GOIN_BSHZ4" },
	{EN_GOIN_BSHZ5   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "闭锁重合闸5", "GOIN_BSHZ5" },
	{EN_GOIN_BHYT1   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "保护永跳1",   "GOIN_BHYT1" },
	{EN_GOIN_BHYT2   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "保护永跳2",   "GOIN_BHYT2" },
	{EN_GOIN_BHYT3   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "保护永跳3",   "GOIN_BHYT3" },
	{EN_GOIN_BHYT4   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "保护永跳4",   "GOIN_BHYT4" },
	{EN_GOIN_BHYT5   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "保护永跳5",   "GOIN_BHYT5" },
	{EN_GOIN_BHYT6   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "保护永跳6",   "GOIN_BHYT6" },
	{EN_GOIN_BHYT7   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "保护永跳7",   "GOIN_BHYT7" },
	{EN_GOIN_BHYT8   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "保护永跳8",   "GOIN_BHYT8" },
	{EN_GOIN_BHYT9   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "保护永跳9",   "GOIN_BHYT9" },
	{EN_GOIN_BHYT10  ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "保护永跳10",  "GOIN_BHYT10" },
	//刀闸 1~9 分位
	{EN_GOIN_CLS_XSWI01,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "合刀闸1",   "GOIN_CLS_XSWI01"},
	{EN_GOIN_OPN_XSWI01,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "分刀闸1",   "GOIN_OPN_XSWI01"},
	{EN_GOIN_JBS_XSWI01,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "解闭锁1",   "GOIN_JBS_XSWI01"},
	{EN_GOIN_CLS_XSWI02,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "合刀闸2",   "GOIN_CLS_XSWI02"},
	{EN_GOIN_OPN_XSWI02,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "分刀闸2",   "GOIN_OPN_XSWI02"},
	{EN_GOIN_JBS_XSWI02,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "解闭锁2",   "GOIN_JBS_XSWI02"},
	{EN_GOIN_CLS_XSWI03,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "合刀闸3",   "GOIN_CLS_XSWI03"},
	{EN_GOIN_OPN_XSWI03,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "分刀闸3",   "GOIN_OPN_XSWI03"},
	{EN_GOIN_JBS_XSWI03,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "解闭锁3",   "GOIN_JBS_XSWI03"},
	{EN_GOIN_CLS_XSWI04,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "合刀闸4",   "GOIN_CLS_XSWI04"},
	{EN_GOIN_OPN_XSWI04,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "分刀闸4",   "GOIN_OPN_XSWI04"},
	{EN_GOIN_JBS_XSWI04,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "解闭锁4",   "GOIN_JBS_XSWI04"},
	{EN_GOIN_CLS_XSWI05,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "合刀闸5",   "GOIN_CLS_XSWI05"},
	{EN_GOIN_OPN_XSWI05,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "分刀闸5",   "GOIN_OPN_XSWI05"},
	{EN_GOIN_JBS_XSWI05,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "解闭锁5",   "GOIN_JBS_XSWI05"},
	{EN_GOIN_CLS_XSWI06,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "合刀闸6",   "GOIN_CLS_XSWI06"},
	{EN_GOIN_OPN_XSWI06,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "分刀闸6",   "GOIN_OPN_XSWI06"},
	{EN_GOIN_JBS_XSWI06,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "解闭锁6",   "GOIN_JBS_XSWI06"},
	{EN_GOIN_CLS_XSWI07,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "合刀闸7",   "GOIN_CLS_XSWI07"},
	{EN_GOIN_OPN_XSWI07,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "分刀闸7",   "GOIN_OPN_XSWI07"},
	{EN_GOIN_JBS_XSWI07,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "解闭锁7",   "GOIN_JBS_XSWI07"},
	{EN_GOIN_CLS_XSWI08,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "合刀闸8",   "GOIN_CLS_XSWI08"},
	{EN_GOIN_OPN_XSWI08,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "分刀闸8",   "GOIN_OPN_XSWI08"},
	{EN_GOIN_JBS_XSWI08,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "解闭锁8",   "GOIN_JBS_XSWI08"},
	{EN_GOIN_BAK_01,         EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,     "备用遥控1",   "GOIN_BAK_01"},
	{EN_GOIN_BAK_02,         EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,     "备用遥控2",   "GOIN_BAK_02"},
	// 时间管理输入 
	{EN_GOIN_TIME_SYN,       EN_CTYPE_IO_T,    CN_NULL_PINNO,  0,     "时间管理输入","GOIN_TIME_SYN"},
};
const DWORD g_NUM_GOIN = sizeof(g_tGoInTab) / sizeof(tagGoInTab);

/*================================================================================*/
//4. 开出常量表
/*================================================================================
    WORD            wIndex;                         // 开出量枚举
    BYTE            wSrcType;                       // 关联信号源
    BYTE            wSrcIndex;                      // 关联信号源枚举
    WORD            wParaIndex;                     // 关联参数1
    WORD            wRtnIndex;                      // 关联返校遥信
    WORD            wCfg;                           // 开出其他功能配置
    INT8S           byName[CN_LEN_NAME];            // 开出量名称
    INT8S           byPinName[CN_LEN_NAME];         // 开出量短地址
*================================================================================*/
const tagDoTab  g_tDoTab[ ] =
{
	// wIndex      byNam  byPinName
// 出口板1
	{EN_DO_BHTZ,            EN_DTYPE_FLAG,  EN_FLAG_BHTZ_DO   ,    CN_NULL_PINNO,  EN_DI_DO_BHTZ,        0,  "保护分闸输出",    "DO_BHTZ"},
	{EN_DO_BHHZ,            EN_DTYPE_ACT,   EN_ACT_BHHZ       ,    CN_NULL_PINNO,  EN_DI_DO_BHHZ,        0,  "保护合闸输出",    "DO_BHHZ"},
	{EN_DO_BZTTZ,           EN_DTYPE_ACT,   EN_ACT_BZTTZ      ,    CN_NULL_PINNO,  EN_DI_DO_BZTTZ,       0,  "备自投分闸输出",  "DO_BZTTZ"},
	{EN_DO_BZTHZ,           EN_DTYPE_ACT,   EN_ACT_BZTHZ      ,    CN_NULL_PINNO,  EN_DI_DO_BZTHZ,       0,  "备自投合闸输出",  "DO_BZTHZ"},
	{EN_DO_BHBAK1,          EN_DTYPE_FLAG,  EN_FLAG_DO_BHBAK1 ,    CN_NULL_PINNO,  EN_DI_DO_BAK1,        0,  "备用出口1",       "DO_BHBAK1"},
	{EN_DO_BHBAK2,          EN_DTYPE_FLAG,  EN_FLAG_DO_BHBAK2 ,    CN_NULL_PINNO,  EN_DI_DO_BAK2,        0,  "备用出口2",       "DO_BHBAK2"},
	{EN_DO_BHBAK3,          EN_DTYPE_FLAG,  EN_FLAG_DO_BHBAK3 ,    CN_NULL_PINNO,  EN_DI_DO_BAK3,        0,  "备用出口3",       "DO_BHBAK3"},
	{EN_DO_BHBAK4,          EN_DTYPE_FLAG,  EN_FLAG_DO_BHBAK4 ,    CN_NULL_PINNO,  EN_DI_DO_BAK4,        0,  "备用出口4 ",      "DO_BHBAK4"},
	{EN_DO_XCBR_OPN,        EN_DTYPE_GOIN,  EN_GOIN_CKTZ      ,    CN_NULL_PINNO,  EN_DI_DO_XCBR_OPN,    0,  "遥控分闸输出",    "DO_XCBR_OPN"},
	{EN_DO_XCBR_CLS,        EN_DTYPE_GOIN,  EN_GOIN_CKHZ      ,    CN_NULL_PINNO,  EN_DI_DO_XCBR_CLS,    0,  "遥控合闸输出",    "DO_XCBR_CLS"},
	{EN_DO_BSCH,            EN_DTYPE_ALM ,  EN_ALM_BSCH_OTH   ,    CN_NULL_PINNO,  EN_DI_DO_BSCH,        0,  "闭锁重合闸输出",   "DO_BSCH"},
	{EN_DO_XCBR_JBS,        EN_DTYPE_GOIN,  EN_GOIN_JBS_XCBR  ,    CN_NULL_PINNO,  EN_DI_DO_XCBR_JBS,    0,  "断路器解闭锁输出",  "DO_XCBR_JBS"},
	{EN_DO_XSWI01_JBS,      EN_DTYPE_GOIN,  EN_GOIN_JBS_XSWI01,    CN_NULL_PINNO,  EN_DI_DO_XSWI01_JBS,  0,  "刀闸1解闭锁输出", "DO_XSWI01_JBS"},
	{EN_DO_XSWI02_JBS,      EN_DTYPE_GOIN,  EN_GOIN_JBS_XSWI02,    CN_NULL_PINNO,  EN_DI_DO_XSWI02_JBS,  0,  "刀闸2解闭锁输出", "DO_XSWI02_JBS"},
	{EN_DO_XSWI03_JBS,      EN_DTYPE_GOIN,  EN_GOIN_JBS_XSWI03,    CN_NULL_PINNO,  EN_DI_DO_XSWI03_JBS,  0,  "刀闸3解闭锁输出", "DO_XSWI03_JBS"},
	{EN_DO_XSWI04_JBS,      EN_DTYPE_GOIN,  EN_GOIN_JBS_XSWI04,    CN_NULL_PINNO,  EN_DI_DO_XSWI04_JBS,  0,  "刀闸4解闭锁输出", "DO_XSWI04_JBS"},
// 出口板2
	{EN_DO_XSWI05_JBS,      EN_DTYPE_GOIN,  EN_GOIN_JBS_XSWI05,    CN_NULL_PINNO,  EN_DI_DO_XSWI05_JBS,  0,  "刀闸5解闭锁输出", "DO_XSWI05_JBS"},
	{EN_DO_XSWI06_JBS,      EN_DTYPE_GOIN,  EN_GOIN_JBS_XSWI06,    CN_NULL_PINNO,  EN_DI_DO_XSWI06_JBS,  0,  "刀闸6解闭锁输出", "DO_XSWI06_JBS"},
	{EN_DO_XSWI07_JBS,      EN_DTYPE_GOIN,  EN_GOIN_JBS_XSWI07,    CN_NULL_PINNO,  EN_DI_DO_XSWI07_JBS,  0,  "刀闸7解闭锁输出", "DO_XSWI07_JBS"},
	{EN_DO_XSWI08_JBS,      EN_DTYPE_GOIN,  EN_GOIN_JBS_XSWI08,    CN_NULL_PINNO,  EN_DI_DO_XSWI08_JBS,  0,  "刀闸8解闭锁输出", "DO_XSWI08_JBS"},
	{EN_DO_XSWI01_OPN,      EN_DTYPE_GOIN,  EN_GOIN_OPN_XSWI01,    CN_NULL_PINNO,  EN_DI_DO_XSWI01_OPN,  0,  "刀闸1分闸输出",   "DO_XSWI01_OPN"},
	{EN_DO_XSWI01_CLS,      EN_DTYPE_GOIN,  EN_GOIN_CLS_XSWI01,    CN_NULL_PINNO,  EN_DI_DO_XSWI01_CLS,  0,  "刀闸1合闸输出",   "DO_XSWI01_CLS"},
	{EN_DO_XSWI02_OPN,      EN_DTYPE_GOIN,  EN_GOIN_OPN_XSWI02,    CN_NULL_PINNO,  EN_DI_DO_XSWI02_OPN,  0,  "刀闸2分闸输出",   "DO_XSWI02_OPN"},
	{EN_DO_XSWI02_CLS,      EN_DTYPE_GOIN,  EN_GOIN_CLS_XSWI02,    CN_NULL_PINNO,  EN_DI_DO_XSWI02_CLS,  0,  "刀闸2合闸输出",   "DO_XSWI02_CLS"},
	{EN_DO_XSWI03_OPN,      EN_DTYPE_GOIN,  EN_GOIN_OPN_XSWI03,    CN_NULL_PINNO,  EN_DI_DO_XSWI03_OPN,  0,  "刀闸3分闸输出",   "DO_XSWI03_OPN"},
	{EN_DO_XSWI03_CLS,      EN_DTYPE_GOIN,  EN_GOIN_CLS_XSWI03,    CN_NULL_PINNO,  EN_DI_DO_XSWI03_CLS,  0,  "刀闸3合闸输出",   "DO_XSWI03_CLS"},
	{EN_DO_XSWI04_OPN,      EN_DTYPE_GOIN,  EN_GOIN_OPN_XSWI04,    CN_NULL_PINNO,  EN_DI_DO_XSWI04_OPN,  0,  "刀闸4分闸输出",   "DO_XSWI04_OPN"},
	{EN_DO_XSWI04_CLS,      EN_DTYPE_GOIN,  EN_GOIN_CLS_XSWI04,    CN_NULL_PINNO,  EN_DI_DO_XSWI04_CLS,  0,  "刀闸4合闸输出",   "DO_XSWI04_CLS"},
	{EN_DO_XSWI05_OPN,      EN_DTYPE_GOIN,  EN_GOIN_OPN_XSWI05,    CN_NULL_PINNO,  EN_DI_DO_XSWI05_OPN,  0,  "刀闸5分闸输出",   "DO_XSWI05_OPN"},
	{EN_DO_XSWI05_CLS,      EN_DTYPE_GOIN,  EN_GOIN_CLS_XSWI05,    CN_NULL_PINNO,  EN_DI_DO_XSWI05_CLS,  0,  "刀闸5合闸输出",   "DO_XSWI05_CLS"},
	{EN_DO_XSWI06_OPN,      EN_DTYPE_GOIN,  EN_GOIN_OPN_XSWI06,    CN_NULL_PINNO,  EN_DI_DO_XSWI06_OPN,  0,  "刀闸6分闸输出",   "DO_XSWI06_OPN"},
	{EN_DO_XSWI06_CLS,      EN_DTYPE_GOIN,  EN_GOIN_CLS_XSWI06,    CN_NULL_PINNO,  EN_DI_DO_XSWI06_CLS,  0,  "刀闸6合闸输出",   "DO_XSWI06_CLS"},
// 开入开出板
	{EN_DO_XSWI07_OPN,      EN_DTYPE_GOIN,  EN_GOIN_OPN_XSWI07,    CN_NULL_PINNO,  EN_DI_DO_XSWI07_OPN,  0,  "刀闸7分闸输出",   "DO_XSWI07_OPN"},
	{EN_DO_XSWI07_CLS,      EN_DTYPE_GOIN,  EN_GOIN_CLS_XSWI07,    CN_NULL_PINNO,  EN_DI_DO_XSWI07_CLS,  0,  "刀闸7合闸输出",   "DO_XSWI07_CLS"},
	{EN_DO_XSWI08_OPN,      EN_DTYPE_GOIN,  EN_GOIN_OPN_XSWI08,    CN_NULL_PINNO,  EN_DI_DO_XSWI08_OPN,  0,  "刀闸8分闸输出",   "DO_XSWI08_OPN"},
	{EN_DO_XSWI08_CLS,      EN_DTYPE_GOIN,  EN_GOIN_CLS_XSWI08,    CN_NULL_PINNO,  EN_DI_DO_XSWI08_CLS,  0,  "刀闸8合闸输出",   "DO_XSWI08_CLS"},
	{EN_DO_YK_BAK1,         EN_DTYPE_GOIN,  EN_GOIN_BAK_01    ,    CN_NULL_PINNO,  EN_DI_DO_YK_BAK1,     0,  "备用遥控1",       "DO_YK_BAK1"},
	{EN_DO_YK_BAK2,         EN_DTYPE_GOIN,  EN_GOIN_BAK_02    ,    CN_NULL_PINNO,  EN_DI_DO_YK_BAK2,     0,  "备用遥控2",       "DO_YK_BAK2"},
	{EN_DO_BHBAK5,          EN_DTYPE_FLAG,  EN_FLAG_DO_BHBAK5_0,   CN_NULL_PINNO,  EN_DI_DO_BHBAK5,      0,  "备用出口5(常闭)",  "DO_BHBAK5"},
// 电源板
	{EN_DO_ALM,             EN_DTYPE_FLAG,  EN_FLAG_DO_ALM    ,    CN_NULL_PINNO,  CN_NULL_PINNO,        0,  "运行异常",        "DO_ALM"},
	{EN_DO_CHK,             EN_DTYPE_FLAG,  EN_FLAG_DO_CHK    ,    CN_NULL_PINNO,  CN_NULL_PINNO,        0,  "装置故障",        "DO_CHK"},
};
const DWORD g_NUM_DO = sizeof(g_tDoTab) / sizeof(tagDoTab);
/*================================================================================*/
//5. GOOSE发布常量表
/*================================================================================
    WORD            wIndex;                         // 双点开入枚举
    WORD            wChnType;                       // 数据类型
    BYTE            wSrcType;                       // 关联信号源
    BYTE            wSrcIndex;                      // 关联分位信号
    WORD            wParaIndex;                     // 关联参数
    WORD            wCfg;                           // 其他属性配置 NULL:本机品质\本机时标 DB0:时标转发  DB1品质转发
    INT8S           byName[CN_LEN_NAME];            // 双点开入量名称
    INT8S           byPinName[CN_LEN_NAME];         // 双点开入量短地址名称
================================================================================*/

const tagGoOutTab  g_tGoOutTab[ ] =
{
	{EN_GOOUT_CHK        ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG, EN_FLAG_DO_CHK     ,  CN_NULL_PINNO,  0,  "装置故障",   "GOOUT_CHK"},
	{EN_GOOUT_ALM        ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG, EN_FLAG_DO_ALM     ,  CN_NULL_PINNO,  0,  "运行异常",   "GOOUT_ALM"},
	{EN_GOOUT_ALM_SYN    ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_SYN         ,  CN_NULL_PINNO,  0,  "同步异常",   "GOOUT_ALM_SYN"},
	{EN_GOOUT_ALM_KI     ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_DIPOW       ,  CN_NULL_PINNO,  0,  "光耦失电",   "GOOUT_ALM_KI"},
	{EN_GOOUT_ALM_SV     ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_SV          ,  CN_NULL_PINNO,  0,  "SV总告警",   "GOOUT_ALM_SV"},
	{EN_GOOUT_ALM_GOOSE  ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOOSE       ,  CN_NULL_PINNO,  0,  "GOOSE总告警",      "GOOUT_ALM_GOOSE"},
	{EN_GOOUT_ALM_GOCB01 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB01_DATA ,  CN_NULL_PINNO,  0,  "GOOSE1数据异常",   "GOOUT_ALM_GOCB01"},
	{EN_GOOUT_ALM_GOCB02 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB02_DATA ,  CN_NULL_PINNO,  0,  "GOOSE2数据异常",   "GOOUT_ALM_GOCB02"},
	{EN_GOOUT_ALM_GOCB03 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB03_DATA ,  CN_NULL_PINNO,  0,  "GOOSE3数据异常",   "GOOUT_ALM_GOCB03"},
	{EN_GOOUT_ALM_GOCB04 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB04_DATA ,  CN_NULL_PINNO,  0,  "GOOSE4数据异常",   "GOOUT_ALM_GOCB04"},
	{EN_GOOUT_ALM_GOCB05 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB05_DATA ,  CN_NULL_PINNO,  0,  "GOOSE5数据异常",   "GOOUT_ALM_GOCB05"},
	{EN_GOOUT_ALM_GOCB06 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB06_DATA ,  CN_NULL_PINNO,  0,  "GOOSE6数据异常",   "GOOUT_ALM_GOCB06"},
	{EN_GOOUT_ALM_GOCB07 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB07_DATA ,  CN_NULL_PINNO,  0,  "GOOSE7数据异常",   "GOOUT_ALM_GOCB07"},
	{EN_GOOUT_ALM_GOCB08 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB08_DATA ,  CN_NULL_PINNO,  0,  "GOOSE8数据异常",   "GOOUT_ALM_GOCB08"},
	{EN_GOOUT_ALM_GOCB09 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB09_DATA ,  CN_NULL_PINNO,  0,  "GOOSE9数据异常",   "GOOUT_ALM_GOCB09"},
	{EN_GOOUT_ALM_GOCB10 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB10_DATA ,  CN_NULL_PINNO,  0,  "GOOSE10数据异常",   "GOOUT_ALM_GOCB10"},
	{EN_GOOUT_ALM_GOCB11 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB11_DATA ,  CN_NULL_PINNO,  0,  "GOOSE11数据异常",   "GOOUT_ALM_GOCB11"},
	{EN_GOOUT_ALM_GOCB12 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB12_DATA ,  CN_NULL_PINNO,  0,  "GOOSE12数据异常",   "GOOUT_ALM_GOCB12"},
	{EN_GOOUT_ALM_GOCB13 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE13数据异常",   "GOOUT_ALM_GOCB13"},
	{EN_GOOUT_ALM_GOCB14 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE14数据异常",   "GOOUT_ALM_GOCB14"},
	{EN_GOOUT_ALM_GOCB15 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE15数据异常",   "GOOUT_ALM_GOCB15"},
	{EN_GOOUT_ALM_GOCB16 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE16数据异常",   "GOOUT_ALM_GOCB16"},
	{EN_GOOUT_ALM_GOCB17 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE17数据异常",   "GOOUT_ALM_GOCB17"},
	{EN_GOOUT_ALM_GOCB18 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE18数据异常",   "GOOUT_ALM_GOCB18"},
	{EN_GOOUT_ALM_GOCB19 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE19数据异常",   "GOOUT_ALM_GOCB19"},
	{EN_GOOUT_ALM_GOCB20 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE20数据异常",   "GOOUT_ALM_GOCB20"},
	{EN_GOOUT_ALM_GOCB21 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE21数据异常",   "GOOUT_ALM_GOCB21"},
	{EN_GOOUT_ALM_GOCB22 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE22数据异常",   "GOOUT_ALM_GOCB22"},
	{EN_GOOUT_ALM_GOCB23 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE23数据异常",   "GOOUT_ALM_GOCB23"},
	{EN_GOOUT_ALM_GOCB24 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE24数据异常",   "GOOUT_ALM_GOCB24"},
	{EN_GOOUT_TEST_ERR   ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_TEST        ,  CN_NULL_PINNO,  0,  "检修不一致",        "GOOUT_TEST_ERR"},
	{EN_GOOUT_ALM_BSCH   ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_BSCH       ,  CN_NULL_PINNO,  0,  "闭锁重合闸",         "GOOUT_ALM_BSCH"},
	{EN_GOOUT_FLAG_TJF   ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG, EN_FLAG_DI_TJF    ,  CN_NULL_PINNO,  0,  "电缆直跳信号TJF",    "GOOUT_FLAG_TJF"},
	{EN_GOOUT_FLAG_KKJ   ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG, EN_FLAG_DI_KKJ    ,  CN_NULL_PINNO,  0,  "KKJ合后",           "GOOUT_FLAG_KKJ"},
	{EN_GOOUT_FLAG_STJ   ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG, EN_FLAG_DI_STJ    ,  CN_NULL_PINNO,  0,  "STJ信号",           "GOOUT_FLAG_STJ"},
	{EN_GOOUT_FLAG_SHJ   ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG, EN_FLAG_DI_SHJ    ,  CN_NULL_PINNO,  0,  "SHJ信号",           "GOOUT_FLAG_SHJ"},
	{EN_GOOUT_ALM_KHDX   ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_KHDX       ,  CN_NULL_PINNO,  0,  "控制回路断线",       "GOOUT_ALM_KHDX"},
	{EN_GOOUT_ALM_XSWI   ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_XSWI       ,  CN_NULL_PINNO,  0,  "刀闸位置异常",       "GOOUT_ALM_XSWI"},
	{EN_GOOUT_ALM_VCHG   ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_XZBS       ,  CN_NULL_PINNO,  0,  "选择把手状态异常",    "GOOUT_ALM_VCHG"},
	{EN_GOOUT_ALM_PTACT  ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_PTACT      ,  CN_NULL_PINNO,  0,  "PT切换同时动作",        "GOOUT_ALM_PTACT"},
	{EN_GOOUT_ALM_PTRET  ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_PTRET      ,  CN_NULL_PINNO,  0,  "PT切换同时返回",        "GOOUT_ALM_PTRET"},
	{EN_GOOUT_ALM_LNK    ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_SVSUB      ,  CN_NULL_PINNO,  0,  "SV级联数据异常",       "GOOUT_ALM_LNK"},
	{EN_GOOUT_ALM_OPBP1  ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_OPBP1      ,  CN_NULL_PINNO,  0,  "操作电源掉电监视信号",   "GOOUT_ALM_OPBP1"},
	{EN_GOOUT_ALM_SGZ    ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM ,  EN_ALM_SGZ       ,  CN_NULL_PINNO,  0,  "事故总信号",         "GOOUT_ALM_SGZ"},
	{EN_GOOUT_ALM_SXBYZ  ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM ,  EN_ALM_SXBYZ     ,  CN_NULL_PINNO,  0,  "三相不一致",         "GOOUT_ALM_SXBYZ"},
	{EN_GOOUT_IN_BHTZ    ,   EN_CTYPE_IO_S,   EN_DTYPE_ACT ,  EN_ACT_BHTZ      ,  CN_NULL_PINNO,  0,  "收到保护跳闸命令",   "GOOUT_IN_BHTZ"},
	{EN_GOOUT_IN_BHYT    ,   EN_CTYPE_IO_S,   EN_DTYPE_ACT ,  EN_ACT_BHYT      ,  CN_NULL_PINNO,  0,  "收到保护永跳命令",   "GOOUT_IN_BHYT"},
	{EN_GOOUT_IN_BHHZ    ,   EN_CTYPE_IO_S,   EN_DTYPE_ACT ,  EN_ACT_BHHZ      ,  CN_NULL_PINNO,  0,  "收到保护三合命令",   "GOOUT_IN_BHHZ"},
	{EN_GOOUT_IN_CKTZ    ,   EN_CTYPE_IO_S,   EN_DTYPE_GOIN,  EN_GOIN_CKTZ     ,  CN_NULL_PINNO,  0,  "收到测控跳闸命令",   "GOOUT_IN_CKTZ"},
	{EN_GOOUT_IN_CKHZ    ,   EN_CTYPE_IO_S,   EN_DTYPE_GOIN,  EN_GOIN_CKHZ     ,  CN_NULL_PINNO,  0,  "收到测控合闸命令",   "GOOUT_IN_CKHZ"},
	{EN_GOOUT_IN_BZTTZ   ,   EN_CTYPE_IO_S,   EN_DTYPE_ACT ,  EN_ACT_BZTTZ     ,  CN_NULL_PINNO,  0,  "收到备自投跳闸命令", "GOOUT_IN_BZTTZ"},
	{EN_GOOUT_IN_BZTHZ   ,   EN_CTYPE_IO_S,   EN_DTYPE_ACT ,  EN_ACT_BZTHZ     ,  CN_NULL_PINNO,  0,  "收到备自投合闸命令", "GOOUT_IN_BZTHZ"},
	{EN_GOOUT_DO_BHTZ    ,   EN_CTYPE_IO_S,   EN_DTYPE_DI  ,  EN_DI_DO_BHTZ    ,  CN_NULL_PINNO,  0,  "跳闸出口回采",       "GOOUT_DO_BHTZ"},
	{EN_GOOUT_DO_BHHZ    ,   EN_CTYPE_IO_S,   EN_DTYPE_DI  ,  EN_DI_DO_BHHZ    ,  CN_NULL_PINNO,  0,  "合闸出口回采",       "GOOUT_DO_BHHZ"},
	{EN_GOOUT_DO_BZTTZ   ,   EN_CTYPE_IO_S,   EN_DTYPE_DI  ,  EN_DI_DO_BZTTZ   ,  CN_NULL_PINNO,  0,  "备自投跳闸出口回采", "GOOUT_DO_BZTTZ"},
	{EN_GOOUT_DO_BZTHZ   ,   EN_CTYPE_IO_S,   EN_DTYPE_DI  ,  EN_DI_DO_BZTHZ   ,  CN_NULL_PINNO,  0,  "备自投合闸出口回采", "GOOUT_DO_BZTHZ"},
	{EN_GOOUT_V_I        ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG,  EN_FLAG_V_I      ,  CN_NULL_PINNO,  0,  "压切取Ⅰ母",       "GOOUT_V_I"},
	{EN_GOOUT_V_II       ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG,  EN_FLAG_V_II     ,  CN_NULL_PINNO,  0,  "压切取Ⅱ母",       "GOOUT_V_II"},
	{EN_GOOUT_SV_A       ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG,  EN_FLAG_SV_A     ,  CN_NULL_PINNO,  0,  "A套数据正常",      "GOOUT_SV_A"},
	{EN_GOOUT_SV_B       ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG,  EN_FLAG_SV_B     ,  CN_NULL_PINNO,  0,  "B套数据正常",      "GOOUT_SV_B"},
	{EN_GOOUT_LNK_A      ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG,  EN_FLAG_LNK_A    ,  CN_NULL_PINNO,  0,  "级联取A套",       "GOOUT_LNK_A"},
	{EN_GOOUT_LNK_B      ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG,  EN_FLAG_LNK_B    ,  CN_NULL_PINNO,  0,  "级联取B套",       "GOOUT_LNK_B"},
	{EN_GOOUT_PARACHG    ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG,  EN_FLAG_PARACHG   , CN_NULL_PINNO,  0,  "参数变化信号",   "GOOUT_PARACHG"},

	{EN_GOOUT_TIME_RECV  ,   EN_CTYPE_IO_S,   EN_DTYPE_GOIN, EN_GOIN_TIME_SYN,     CN_NULL_PINNO,  0,  "接收SOE",   "GOOUT_TIME_RECV"},
	{EN_GOOUT_TIME_SEND  ,   EN_CTYPE_IO_S,   EN_DTYPE_GOIN, EN_GOIN_TIME_SYN,     CN_NULL_PINNO,  0,  "发送SOE",   "GOOUT_TIME_SEND"},
	{EN_GOOUT_TIME_SINGLE,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_TIME_SINGLE,   CN_NULL_PINNO,  0,  "对时信号状态",   "GOOUT_TIME_SINGLE"},
	{EN_GOOUT_TIME_SERVIC,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_TIME_SERVICE,  CN_NULL_PINNO,  0,  "对时服务状态",   "GOOUT_TIME_SERVIC"},
	{EN_GOOUT_TIME_CHKERR,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_TIME_CHKERR,   CN_NULL_PINNO,  0,  "时间跳变侦测状态",   "GOOUT_TIME_CHKERR"},
};
const DWORD g_NUM_GOOUT = sizeof(g_tGoOutTab) / sizeof(tagGoOutTab);
/*================================================================================*/
//6. LED常量表
/*================================================================================
    WORD            wIndex;                         // 双点开入枚举
    BYTE            wSrcType;                       // 关联信号源
    BYTE            wSrcIndex;                      // 关联分位信号
    WORD            wParaIndex1;                    // 关联参数1
    BYTE            byCol;                          // 列位置
    BYTE            byRow;                          // 行位置
    BYTE            bycolor;                        // 指示灯颜色
    BOOL            bHld;                           // 指示灯保持标志
    INT8S           byName[CN_LEN_NAME];            // 双点开入量名称
    INT8S           byPinName[CN_LEN_NAME];         // 双点开入量短地址名称
*================================================================================*/

const tagLedTab  g_tLedTab[ ] =
{
	{EN_LED_RUN       ,      EN_DTYPE_FLAG,  EN_FLAG_LED_RUN ,  CN_NULL_PINNO,  0,    0,    EN_COLOR_GREEN,    0,  "运行",        "LED_RUN"},
	{EN_LED_ALM       ,      EN_DTYPE_FLAG,  EN_FLAG_LED_ALM ,  CN_NULL_PINNO,  0,    1,    EN_COLOR_RED  ,    0,  "告警",        "LED_ALM"},
	{EN_LED_TEST      ,      EN_DTYPE_DI  ,  EN_DI_TEST      ,  CN_NULL_PINNO,  0,    2,    EN_COLOR_RED  ,    0,  "检修",        "LED_TEST"},
	{EN_LED_GO_ERR    ,      EN_DTYPE_ALM ,  EN_ALM_GOOSE    ,  CN_NULL_PINNO,  0,    3,    EN_COLOR_RED  ,    0,  "GOOSE异常",   "LED_GO_ERR"},
	{EN_LED_TEST_ERR  ,      EN_DTYPE_ALM ,  EN_ALM_TEST     ,  CN_NULL_PINNO,  0,    4,    EN_COLOR_RED  ,    0,  "检修不一致",  "LED_TEST_ERR"},
	{EN_LED_SYN_ERR   ,      EN_DTYPE_ALM ,  EN_ALM_SYN      ,  CN_NULL_PINNO,  0,    5,    EN_COLOR_RED  ,    0,  "同步异常",      "LED_SYN_ERR"},
	{EN_LED_SAM_ERR   ,      EN_DTYPE_ALM ,  EN_ALM_SAM      ,  CN_NULL_PINNO,  0,    6,    EN_COLOR_RED  ,    0,  "采样异常",      "LED_SAM_ERR"},
	{EN_LED_KHDX      ,      EN_DTYPE_ALM ,  EN_ALM_KHDX     ,  CN_NULL_PINNO,  0,    7,    EN_COLOR_RED  ,    0,  "控制回路断线",  "LED_KHDX"},
	{EN_LED_BHTZ      ,      EN_DTYPE_FLAG,  EN_FLAG_BHTZ    ,  CN_NULL_PINNO,  1,    0,    EN_COLOR_RED  ,    1,  "保护跳闸",     "LED_BHTZ"},
	{EN_LED_BHHZ      ,      EN_DTYPE_FLAG,  EN_FLAG_BHHZ    ,  CN_NULL_PINNO,  1,    1,    EN_COLOR_RED  ,    1,  "保护合闸",     "LED_BHHZ"},
	{EN_LED_ZTF       ,      EN_DTYPE_FLAG,  EN_FLAG_DI_TJF  ,  CN_NULL_PINNO,  1,    2,    EN_COLOR_RED  ,    1,  "非电量直跳",   "LED_ZTF"},
	{EN_LED_BAK21     ,      EN_DTYPE_FLAG,  EN_FLAG_LED_BAK21, CN_NULL_PINNO,  1,    3,    EN_COLOR_RED  ,    0,  "备用1",       "LED_BAK21"},
	{EN_LED_BAK22     ,      EN_DTYPE_FLAG,  EN_FLAG_LED_BAK22, CN_NULL_PINNO,  1,    4,    EN_COLOR_RED  ,    0,  "备用2",       "LED_BAK22"},
	{EN_LED_BAK23     ,      EN_DTYPE_FLAG,  EN_FLAG_LED_BAK23, CN_NULL_PINNO,  1,    5,    EN_COLOR_RED  ,    0,  "备用3",       "LED_BAK23"},
	{EN_LED_BAK24     ,      EN_DTYPE_FLAG,  EN_FLAG_LED_BAK24, CN_NULL_PINNO,  1,    6,    EN_COLOR_RED  ,    0,  "备用4",       "LED_BAK24"},
	{EN_LED_HWJ       ,      EN_DTYPE_DI  ,  EN_DI_XCBR_CLS  ,  CN_NULL_PINNO,  1,    7,    EN_COLOR_RED  ,    0,  "断路器合位",  "LED_HWJ"},

	{EN_LED_WAR_LNK   ,      EN_DTYPE_ALM ,  EN_ALM_LINK     ,  CN_NULL_PINNO,  2,    0,    EN_COLOR_RED  ,    0,  "级联异常",    "LED_WAR_LNK"},
	{EN_LED_VCHG_I    ,      EN_DTYPE_FLAG,  EN_FLAG_V_I     ,  CN_NULL_PINNO,  2,    1,    EN_COLOR_RED  ,    0,  "压切取Ⅰ母",  "LED_VCHG_I"},
	{EN_LED_VCHG_II   ,      EN_DTYPE_FLAG,  EN_FLAG_V_II    ,  CN_NULL_PINNO,  2,    2,    EN_COLOR_RED  ,    0,  "压切取Ⅱ母",  "LED_VCHG_II"},
	{EN_LED_LNK_A     ,      EN_DTYPE_FLAG,  EN_FLAG_LNK_A   ,  CN_NULL_PINNO,  2,    3,    EN_COLOR_RED  ,    0,  "级联取A套",   "LED_LNK_A"},
	{EN_LED_LNK_B     ,      EN_DTYPE_FLAG,  EN_FLAG_LNK_B   ,  CN_NULL_PINNO,  2,    4,    EN_COLOR_RED  ,    0,  "级联取B套",   "LED_LNK_B"},
	{EN_LED_BAK31     ,      EN_DTYPE_FLAG,  EN_FLAG_LED_BAK31, CN_NULL_PINNO,  2,    5,    EN_COLOR_GREEN,    0,  "备用5",      "LED_BAK31"},
	{EN_LED_BAK32     ,      EN_DTYPE_FLAG,  EN_FLAG_LED_BAK32, CN_NULL_PINNO,  2,    6,    EN_COLOR_GREEN,    0,  "备用6",      "LED_BAK32"},
	{EN_LED_TWJ       ,      EN_DTYPE_DI  ,  EN_DI_XCBR_OPN  ,  CN_NULL_PINNO,  2,    7,    EN_COLOR_GREEN,    0,  "断路器分位",  "LED_TWJ"},

	{EN_LED_XSWI01_CLS,      EN_DTYPE_DI,  EN_DI_XSWI01_CLS  ,  CN_NULL_PINNO,  3,    0,    EN_COLOR_RED  ,    0,  "刀闸1合位",   "LED_XSWI01_CLS"},
	{EN_LED_XSWI02_CLS,      EN_DTYPE_DI,  EN_DI_XSWI02_CLS  ,  CN_NULL_PINNO,  3,    1,    EN_COLOR_RED  ,    0,  "刀闸2合位",   "LED_XSWI02_CLS"},
	{EN_LED_XSWI03_CLS,      EN_DTYPE_DI,  EN_DI_XSWI03_CLS  ,  CN_NULL_PINNO,  3,    2,    EN_COLOR_RED  ,    0,  "刀闸3合位",   "LED_XSWI03_CLS"},
	{EN_LED_XSWI04_CLS,      EN_DTYPE_DI,  EN_DI_XSWI04_CLS  ,  CN_NULL_PINNO,  3,    3,    EN_COLOR_RED  ,    0,  "刀闸4合位",   "LED_XSWI04_CLS"},
	{EN_LED_XSWI05_CLS,      EN_DTYPE_DI,  EN_DI_XSWI05_CLS  ,  CN_NULL_PINNO,  3,    4,    EN_COLOR_RED  ,    0,  "刀闸5合位",   "LED_XSWI05_CLS"},
	{EN_LED_XSWI06_CLS,      EN_DTYPE_DI,  EN_DI_XSWI06_CLS  ,  CN_NULL_PINNO,  3,    5,    EN_COLOR_RED  ,    0,  "刀闸6合位",   "LED_XSWI06_CLS"},
	{EN_LED_XSWI07_CLS,      EN_DTYPE_DI,  EN_DI_XSWI07_CLS  ,  CN_NULL_PINNO,  3,    6,    EN_COLOR_RED  ,    0,  "刀闸7合位",   "LED_XSWI07_CLS"},
	{EN_LED_XSWI08_CLS,      EN_DTYPE_DI,  EN_DI_XSWI08_CLS  ,  CN_NULL_PINNO,  3,    7,    EN_COLOR_RED  ,    0,  "刀闸8合位",   "LED_XSWI08_CLS"},

	{EN_LED_XSWI01_OPN,      EN_DTYPE_DI,  EN_DI_XSWI01_OPN  ,  CN_NULL_PINNO,  4,    0,    EN_COLOR_GREEN,    0,  "刀闸1分位",   "LED_XSWI01_OPN"},
	{EN_LED_XSWI02_OPN,      EN_DTYPE_DI,  EN_DI_XSWI02_OPN  ,  CN_NULL_PINNO,  4,    1,    EN_COLOR_GREEN,    0,  "刀闸2分位",   "LED_XSWI02_OPN"},
	{EN_LED_XSWI03_OPN,      EN_DTYPE_DI,  EN_DI_XSWI03_OPN  ,  CN_NULL_PINNO,  4,    2,    EN_COLOR_GREEN,    0,  "刀闸3分位",   "LED_XSWI03_OPN"},
	{EN_LED_XSWI04_OPN,      EN_DTYPE_DI,  EN_DI_XSWI04_OPN  ,  CN_NULL_PINNO,  4,    3,    EN_COLOR_GREEN,    0,  "刀闸4分位",   "LED_XSWI04_OPN"},
	{EN_LED_XSWI05_OPN,      EN_DTYPE_DI,  EN_DI_XSWI05_OPN  ,  CN_NULL_PINNO,  4,    4,    EN_COLOR_GREEN,    0,  "刀闸5分位",   "LED_XSWI05_OPN"},
	{EN_LED_XSWI06_OPN,      EN_DTYPE_DI,  EN_DI_XSWI06_OPN  ,  CN_NULL_PINNO,  4,    5,    EN_COLOR_GREEN,    0,  "刀闸6分位",   "LED_XSWI06_OPN"},
	{EN_LED_XSWI07_OPN,      EN_DTYPE_DI,  EN_DI_XSWI07_OPN  ,  CN_NULL_PINNO,  4,    6,    EN_COLOR_GREEN,    0,  "刀闸7分位",   "LED_XSWI07_OPN"},
	{EN_LED_XSWI08_OPN,      EN_DTYPE_DI,  EN_DI_XSWI08_OPN  ,  CN_NULL_PINNO,  4,    7,    EN_COLOR_GREEN,    0,  "刀闸8分位",   "LED_XSWI08_OPN"}
};
	
const DWORD g_NUM_LED = sizeof(g_tLedTab) / sizeof(tagLedTab);

const tagBoardIoTab    g_tBoardDITab[]=
{
    { EN_BOARD_DI1,     EN_DI_BOARD1_STR,   EN_DI_BOARD1_END,    (EN_DI_BOARD1_END-EN_DI_BOARD1_STR),     (EN_DI_POW1-EN_DI_BOARD1_STR),   EN_PARA_ENA_YXPOW1, 7,1, "DI1",   "AppDiGroup1"},
    { EN_BOARD_DI2,     EN_DI_BOARD2_STR,   EN_DI_BOARD2_END,    (EN_DI_BOARD2_END-EN_DI_BOARD2_STR),     (EN_DI_POW2-EN_DI_BOARD2_STR),   EN_PARA_ENA_YXPOW2, 6,2, "DI2",   "AppDiGroup2"},
    { EN_BOARD_DI3,     EN_DI_BOARD3_STR,   EN_DI_BOARD3_END,    (EN_DI_BOARD3_END-EN_DI_BOARD3_STR),     (EN_DI_POW3-EN_DI_BOARD3_STR),   EN_PARA_ENA_YXPOW3, 5,3, "DI3",   "AppDiGroup3"},
    { EN_BOARD_DI4,     EN_DI_BOARD4_STR,   EN_DI_BOARD4_END,    (EN_DI_BOARD4_END-EN_DI_BOARD4_STR),     (EN_DI_POW4-EN_DI_BOARD4_STR),   EN_PARA_ENA_YXPOW4, 3,0, "DIO",   "AppDiGroup4"},
    { EN_BOARD_DI5,     EN_DI_BOARD5_STR,   EN_DI_BOARD5_END,    (EN_DI_BOARD5_END-EN_DI_BOARD5_STR),     CN_NULL_PINNO,  CN_NULL_PINNO,                       4,4, "OPB",   "AppDiGroup5"},
    { EN_BOARD_DI6,     EN_DI_BOARD6_STR,   EN_DI_BOARD6_END,    (EN_DI_BOARD6_END-EN_DI_BOARD6_STR),     CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,"DI6", "AppDiGroup6"},
    { EN_BOARD_DI7,     EN_DI_BOARD7_STR,   EN_DI_BOARD7_END,    (EN_DI_BOARD7_END-EN_DI_BOARD7_STR),     CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,"DI7", "AppDiGroup7"},
    { EN_BOARD_DI8,     EN_DI_BOARD8_STR,   EN_DI_BOARD8_END,    (EN_DI_BOARD8_END-EN_DI_BOARD8_STR),     CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,"DI8", "AppDiGroup8"},
 //   { EN_BOARD_DI9,     EN_DI_BOARD9_STR,   EN_DI_BOARD9_END,    (EN_DI_BOARD9_END-EN_DI_BOARD9_STR),     CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,"DI9", "AppDiGroup9"},
};
const DWORD g_NUM_BOARD_DI= sizeof(g_tBoardDITab) / sizeof(tagBoardIoTab);
const tagBoardIoTab    g_tBoardDOTab[]=
{
    { EN_BOARD_DO1,     EN_DO_BOARD1_STR,   EN_DO_BOARD1_END,    (EN_DO_BOARD1_END-EN_DO_BOARD1_STR),     CN_NULL_PINNO,    CN_NULL_PINNO,             1,            1, "DO1",   "AppDoGroup1"},
    { EN_BOARD_DO2,     EN_DO_BOARD2_STR,   EN_DO_BOARD2_END,    (EN_DO_BOARD2_END-EN_DO_BOARD2_STR),     CN_NULL_PINNO,    CN_NULL_PINNO,             2,            2, "DO2",   "AppDoGroup2"},
    { EN_BOARD_DO3,     EN_DO_BOARD3_STR,   EN_DO_BOARD3_END,    (EN_DO_BOARD3_END-EN_DO_BOARD3_STR),     CN_NULL_PINNO,    CN_NULL_PINNO,             3,            0, "DIO",   "AppDoGroup3"},
    { EN_BOARD_DO4,     EN_DO_BOARD4_STR,   EN_DO_BOARD4_END,    (EN_DO_BOARD4_END-EN_DO_BOARD4_STR),     CN_NULL_PINNO,    CN_NULL_PINNO, CN_NULL_PINNO,CN_NULL_PINNO, "POW",   "AppDoGroup4"},
};
const DWORD g_NUM_BOARD_DO= sizeof(g_tBoardDOTab) / sizeof(tagBoardIoTab);


