#include "InstResource.h"

#define AppLog   LogErr


const tagCTypeTab  g_tCTypeTab[] =
{

    { EN_CTYPE_ANA_I,   &Unit_A   ,   &Unit_A   ,       9,    CN_SAM_DIV_I,  CN_NULL_PINNO},
    { EN_CTYPE_ANA_U,   &Unit_V   ,   &Unit_KV  ,       9,    CN_SAM_DIV_U,  CN_NULL_PINNO},
    { EN_CTYPE_ANA_J,   &Unit_V   ,   &Unit_V   ,       9,    CN_SAM_DIV_U,  CN_NULL_PINNO},
    { EN_CTYPE_SV_I,    &Unit_A   ,   &Unit_A   ,       9,    CN_SAM_DIV_I,  CN_NULL_PINNO},
    { EN_CTYPE_SV_U,    &Unit_V   ,   &Unit_KV  ,       9,    CN_SAM_DIV_U,  CN_NULL_PINNO},
    { EN_CTYPE_SV_T,    &Unit_uS  ,   &Unit_NULL,       9,    0           ,  CN_NULL_PINNO},
    { EN_CTYPE_CAL_F,   &Unit_HZ  ,   &Unit_NULL,       9,    CN_SAM_DIV_F,  CN_NULL_PINNO},
    { EN_CTYPE_IO_S,    &Unit_NULL,   &Unit_NULL,       2,    0           ,  CN_NULL_PINNO},
    { EN_CTYPE_IO_D,    &Unit_NULL,   &Unit_NULL,       2,    0           ,  CN_NULL_PINNO},
    { EN_CTYPE_IO_P,    &Unit_NULL,   &Unit_NULL,       8,    0           ,  CN_NULL_PINNO},
    { EN_CTYPE_IO_T,    &Unit_NULL,   &Unit_NULL,       8,    0           ,  CN_NULL_PINNO},

    { EN_CTYPE_DC_ZL1,   &Unit_V,     &Unit_mA,         9,    CN_DC_DSP_SAM,  EN_PARA_DC1_IN},
    { EN_CTYPE_DC_ZL2,   &Unit_V,     &Unit_mA,         9,    CN_DC_DSP_SAM,  EN_PARA_DC2_IN},
#if(!CN_FUN_DBUG1)
    { EN_CTYPE_DC_ZL3,   &Unit_V,     &Unit_mA,         9,    CN_DC_DSP_SAM,  EN_PARA_DC3_IN},
    { EN_CTYPE_DC_ZL4,   &Unit_V,     &Unit_mA,         9,    CN_DC_DSP_SAM,  EN_PARA_DC4_IN},
    { EN_CTYPE_DC_ZL5,   &Unit_V,     &Unit_mA,         9,    CN_DC_DSP_SAM,  EN_PARA_DC5_IN},
    { EN_CTYPE_DC_ZL6,   &Unit_V,     &Unit_mA,         9,    CN_DC_DSP_SAM,  EN_PARA_DC6_IN},
    { EN_CTYPE_DC_ZL7,   &Unit_V,     &Unit_mA,         9,    CN_DC_DSP_SAM,  EN_PARA_DC7_IN},
#endif
    { EN_CTYPE_DC_mA,   &Unit_mA,     &Unit_NULL,       9,    CN_DC_DSP_DEV,  CN_NULL_PINNO},
    { EN_CTYPE_DC_V,    &Unit_V,      &Unit_NULL,       9,    CN_DC_DSP_DEV,  CN_NULL_PINNO},
    { EN_CTYPE_DC_T,    &Unit_TEMPR,  &Unit_NULL,       9,    CN_DC_DSP_DEV,  CN_NULL_PINNO},
    { EN_CTYPE_DC_Hum,  &Unit_Percent,&Unit_NULL,       9,    CN_DC_DSP_DEV,  CN_NULL_PINNO},
    { EN_CTYPE_DC_DBM,  &Unit_dB,     &Unit_NULL,       9,    CN_DC_DSP_DEV,  CN_NULL_PINNO},
    { EN_CTYPE_DC_OPTT, &Unit_TEMPR,  &Unit_NULL,       9,    CN_DC_DSP_DEV,  CN_NULL_PINNO},
    { EN_CTYPE_DC_OPTV, &Unit_V,      &Unit_NULL,       9,    CN_DC_DSP_DEV,  CN_NULL_PINNO},
    { EN_CTYPE_DC_H,    &Unit_NULL,   &Unit_NULL,       9,    0,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_S,  &Unit_S,      &Unit_NULL,       9,    3,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_Ms, &Unit_mS,     &Unit_NULL,       8,    0,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_Us, &Unit_uS,     &Unit_NULL,       8,    0,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_Us_1,&Unit_uS,    &Unit_NULL,       8,    1,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_PT1,&Unit_KV,     &Unit_NULL,       9,    2,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_PT2,&Unit_V,      &Unit_NULL,       9,    2,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_CT1,&Unit_A,      &Unit_NULL,       8,    0,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_CT2,&Unit_A,      &Unit_NULL,       2,    0,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_V,  &Unit_V,      &Unit_NULL,       9,    3,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_mV, &Unit_mV,     &Unit_NULL,       9,    3,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_A,  &Unit_A,      &Unit_NULL,       9,    3,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_mA, &Unit_mA,     &Unit_NULL,       9,    3,  CN_NULL_PINNO},

	{ EN_CTYPE_PARA_T,  &Unit_TEMPR,  &Unit_NULL,       9,    CN_DC_DSP_DEV,  CN_NULL_PINNO},
	{ EN_CTYPE_PARA_Hum,&Unit_Percent,&Unit_NULL,       9,    CN_DC_DSP_DEV,  CN_NULL_PINNO},
	{ EN_CTYPE_PARA_OBM,&Unit_dB,     &Unit_NULL,       9,    3,  CN_NULL_PINNO},
	{ EN_CTYPE_PARA_Per,&Unit_Percent,&Unit_NULL,       9,    CN_DC_DSP_DEV,  CN_NULL_PINNO},

    { EN_CTYPE_PARA_H,  &Unit_NULL,   &Unit_NULL,       9,    0,  CN_NULL_PINNO},
	{ EN_CTYPE_PARA_MAT,&Unit_NULL,   &Unit_NULL,       9,    0,  CN_NULL_PINNO},
	{ EN_CTYPE_PARA_D,  &Unit_NULL,   &Unit_NULL,       9,    0,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_D_1,&Unit_NULL,   &Unit_NULL,       9,    1,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_D_2,&Unit_NULL,   &Unit_NULL,       9,    2,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_D_3,&Unit_NULL,   &Unit_NULL,       9,    3,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_D_4,&Unit_NULL,   &Unit_NULL,       9,    4,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_D_5,&Unit_NULL,   &Unit_NULL,       9,    5,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_D_6,&Unit_NULL,   &Unit_NULL,       9,    6,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_I,  &Unit_NULL,   &Unit_NULL,       9,    0,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_I_1,&Unit_NULL,   &Unit_NULL,       9,    1,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_I_2,&Unit_NULL,   &Unit_NULL,       9,    2,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_I_3,&Unit_NULL,   &Unit_NULL,       9,    3,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_I_4,&Unit_NULL,   &Unit_NULL,       9,    4,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_I_5,&Unit_NULL,   &Unit_NULL,       9,    5,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_I_6,&Unit_NULL,   &Unit_NULL,       9,    6,  CN_NULL_PINNO},
    { EN_CTYPE_PARA_B,  &Unit_NULL,   &Unit_NULL,       9,    0,  CN_NULL_PINNO}
};
const DWORD g_NUM_CTYPE= sizeof(g_tCTypeTab) / sizeof(tagCTypeTab);
// 目前暂定枚举个数最大为20个
// 枚举与字符串的映射必须按顺序配置,是通过枚举用作下标
tagCEnumTab  g_tCEnumTab[] =
{
    { EN_CENUM_PARA_DCIN,   &Unit_NULL,  &Unit_NULL,  2,{{0,"4-20mA"},{1,"  0-5V"}}},
    { EN_CENUM_PARA_DCOUT,  &Unit_NULL,  &Unit_NULL,  2,{{0,"一次值"},{1,   "二次值"}}},
    { EN_CENUM_PARA_CT2,    &Unit_NULL,  &Unit_NULL,  2,{{0,"1A"},{1,   "5A"}}},
    { EN_CENUM_PARA_BusLik, &Unit_NULL,  &Unit_NULL,  2,{{0,"单母线"},{1,   "双母线"}}},
    { EN_CENUM_PARA_Fr,     &Unit_NULL,  &Unit_NULL,  3,{{0,"Ua"},{1,"Ub"},{2,"Uc"}}},
    { EN_CENUM_PARA_MSAM,   &Unit_NULL,  &Unit_NULL,  2,{{0,"数字量"},{1,   "模拟量"}}},
    { EN_CENUM_PARA_UxSAM,  &Unit_NULL,  &Unit_NULL, 13,{{0," 模拟量Ux"},{1," 模拟量Ua"},
    {2," 模拟量Ub"},{3," 模拟量Uc"},{4,"模拟量Uab"},{5,"模拟量Ubc"},{6,"模拟量Uca"},
    {7," 数字量Ua"},{8," 数字量Ub"},{9," 数字量Uc"},{10,"数字量Uab"},{11,"数字量Ubc"},
    {12,"数字量Uca"}}},
//  { EN_CENUM_PARA_XCBR,   &Unit_NULL,  &Unit_NULL,  2,{{0,"三相开关"},{1,    "分相开关"}}},
    { EN_CENUM_PARA_DISAM,  &Unit_NULL,  &Unit_NULL,  2,{{0,"内部采集"},{1,    "外部接入"}}},
    { EN_CENUM_PARA_Ux,     &Unit_NULL,  &Unit_NULL,  2,{{0,"SV接入  "},{1,"直采接入"}}},
    { EN_CENUM_DO_STATUS,   &Unit_NULL,  &Unit_NULL,  2,{{0,"分命令"},{1,"合命令"}}},
    { EN_CENUM_FAIL_RET,    &Unit_NULL,  &Unit_NULL,  EN_RET_END,{{EN_INVAILD_NO,"成功"},{EN_INVAILD_TEST,"失败-检修不一致"},
      {EN_INVAILD_LINK,"失败-断链"},{EN_INVAILD_Q,"失败-品质无效"},{EN_INVAILD_DATA,"失败-数据异常"},
      {EN_RET_OVER,"返校-超时"},{EN_RET_ELSE,"返校-重复返校"},{EN_RET_COVER,"返校-命令覆盖"},
      {EN_RET_DIF,"返校-命令不一致"}}},
};
const DWORD g_NUM_CENUM= sizeof(g_tCEnumTab) / sizeof(tagCEnumTab);

#define  EDes(Index)  (g_tCEnumTab[Index- EN_CENUM_STR].eEnumDes)
#define  ENumb(Index)  (g_tCEnumTab[Index- EN_CENUM_STR].byEnNum)
tagMEATab g_tMEATab[] =
{
	{EN_MEA_INDEX,       {"序号",          E_SVT_U32      , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_LC_RX,       {"接收功率",        E_SVT_U32      , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_LC_TX,       {"发送功率",        E_SVT_U32      , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_PTR,         {"地址",          E_SVT_HEX32    , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_DTYPE,       {"数据类型",        E_SVT_U32      , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_FLAG,        {"标志字",         E_SVT_HEX32    , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_FLAG16,      {"标志字",         E_SVT_HEX16    , 4, 0, &Unit_NULL,0,0}},
	{EN_MEA_FLAG8,       {"标志字",         E_SVT_HEX8     , 2, 0, &Unit_NULL,0,0}},
	{EN_MEA_V,           {"电压",          E_SVT_I32      , 8, 3, &Unit_V   ,0,0}},
	{EN_MEA_mA,          {"电流",          E_SVT_I32      , 8, 3, &Unit_mA  ,0,0}},
	{EN_MEA_VALUE,       {"测量值",         E_SVT_U32      , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_PORT,        {"端口号",         E_SVT_U32      , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_BOARD,       {"板卡号",         E_SVT_U32      , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_SVCB,        {"SVCB号",       E_SVT_U32      , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_SVCB_SUB,    {"标志字",         E_SVT_HEX32    , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_SVCB_CFG,    {"配置字",         E_SVT_HEX32    , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_GOCB,        {"GOCB号",        E_SVT_U32      , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_GOCB_A,      {"A标志字",         E_SVT_HEX32    , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_GOCB_B,      {"B标志字",         E_SVT_HEX32    , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_GOCB_CFG,    {"配置字",          E_SVT_HEX32    , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_BHTZ_DO,       {"保护跳闸出口    ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_BHHZ_DO,       {"保护合闸出口    ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_CKTZ_DO,       {"遥控跳闸出口    ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_CKHZ_DO,       {"遥控合闸出口    ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_SHTQ_DO,       {"手合同期出口    ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_BZTTZ_DO,      {"备自投跳闸出口  ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_BZTHZ_DO,      {"备自投合闸出口  ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_CLS_XSWI01_DO, {"刀闸1合闸出口   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_OPN_XSWI01_DO, {"刀闸1分闸出口   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_JBS_XSWI01_DO, {"刀闸1解闭锁出口 ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_CLS_XSWI02_DO, {"刀闸2合闸出口   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_OPN_XSWI02_DO, {"刀闸2分闸出口   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_JBS_XSWI02_DO, {"刀闸2解闭锁出口 ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_CLS_XSWI03_DO, {"刀闸3合闸出口   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_OPN_XSWI03_DO, {"刀闸3分闸出口   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_JBS_XSWI03_DO, {"刀闸3解闭锁出口 ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_CLS_XSWI04_DO, {"刀闸4合闸出口   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_OPN_XSWI04_DO, {"刀闸4分闸出口   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_JBS_XSWI04_DO, {"刀闸4解闭锁出口 ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_CLS_XSWI05_DO, {"刀闸5合闸出口   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_OPN_XSWI05_DO, {"刀闸5分闸出口   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_JBS_XSWI05_DO, {"刀闸5解闭锁出口 ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_CLS_XSWI06_DO, {"刀闸6合闸出口   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_OPN_XSWI06_DO, {"刀闸6分闸出口   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_JBS_XSWI06_DO, {"刀闸6解闭锁出口 ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_CLS_XSWI07_DO, {"刀闸7合闸出口   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_OPN_XSWI07_DO, {"刀闸7分闸出口   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_JBS_XSWI07_DO, {"刀闸7解闭锁出口 ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_CLS_XSWI08_DO, {"刀闸8合闸出口   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_OPN_XSWI08_DO, {"刀闸8分闸出口   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_JBS_XSWI08_DO, {"刀闸8解闭锁出口 ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_BAK_01_DO,     {"备用遥控1出口   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_BAK_02_DO,     {"备用遥控2出口   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_DO_STATUS,     {"GOOSE命令状态   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_DO_FAIL,       {"GOOSE命令结果   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_FAIL_RET),ENumb(EN_CENUM_FAIL_RET)}},
	{EN_MEA_DO_APPID,      {"GOOSE命令APPID  ",    E_SVT_HEX16, 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_DO_RET_T,      {"出口返校时间(us)",     E_SVT_U32  , 8, 0, &Unit_uS,   0,0}},
};
const DWORD g_NUM_MEA= sizeof(g_tMEATab) / sizeof(tagMEATab);

const tagCardTab  g_tCardTab[] =
{
	{EN_CARD_CPU1,{"NULL","A-1","A-2","A-3","A-4","A-5","A-6",
	"A-7","A-8","A-9","A-10","A-11","A-12","A-13"},13,0},
	{EN_CARD_CPU2,{"NULL","B-1","B-2","B-3","B-4","B-5","B-6"},6,0}
};
const DWORD g_NUM_CARD= sizeof(g_tCardTab) / sizeof(g_tCardTab);

const tagKeyTab  g_tKeyTab[] =
{
	{EN_KEY_VER,{EK_LEFT,EK_UP,EK_LEFT,EK_DOWN,EK_LEFT,EK_RIGHT},6},
};
const DWORD g_NUM_KEY= sizeof(g_tKeyTab) / sizeof(tagKeyTab);


void AppInterFaceChk(void)
{
	register DWORD     dwLoop,dwLoop1;
	register DWORD     dwErrFlg=0;
	register DWORD     dwErrIndex=0;
	
	const tagCTypeTab  *ptCTypeTab;
	tagCEnumTab  *ptCEnumTab;
	tagMEATab    *ptMEATab;
	// 通道类型常量表自检
	ptCTypeTab = &g_tCTypeTab[0];
	if(g_NUM_CTYPE!=EN_CTYPE_PARA_END)
	{
		AppLog<<"通道类型常量表配置错误:"<<"g_NUM_CTYPE="<<g_NUM_CTYPE<<"EN_CTYPE_PARA_END="<<EN_CTYPE_PARA_END<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_CTYPE;dwLoop++)
	{
		if(ptCTypeTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			
			AppLog<<"通道类型常量表配置错误:"<<"Index="<<dwLoop<<"\n";
		}
		if((ptCTypeTab->pUnit1==NULL)||(ptCTypeTab->pUnit2==NULL))
		{
			dwErrFlg|=CN_CONST_CHK_TYPE;
			dwErrIndex=dwLoop;
			AppLog<<"通道类型常量表单位配置错误:"<<"Index="<<dwLoop<<"\n";
		}
		if((ptCTypeTab->byWidth<ptCTypeTab->byDotBit)
		||(ptCTypeTab->byWidth>16))
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			AppLog<<"通道类型常量表数据长度配置错误:"<<"Index="<<dwLoop<<"byWidth="<<ptCTypeTab->byWidth<<"byDotBit="<<ptCTypeTab->byDotBit<<"\n";
		}
		if((ptCTypeTab->wParaIndex!=CN_NULL_PINNO)&&(ptCTypeTab->wParaIndex>=CN_NUM_PARA))
		{
			dwErrFlg|=CN_CONST_CHK_PARA1;
			dwErrIndex=dwLoop;
			AppLog<<"通道类型参数设置错误:"<<"Index="<<dwLoop<<"wParaIndex="<<ptCTypeTab->wParaIndex<<"\n";
		}
		ptCTypeTab++;
	}
	
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,DB31,dwErrFlg,dwErrIndex);
	}
	// 枚举类型常量表自检
	ptCEnumTab = &g_tCEnumTab[0];
	dwErrFlg=0;
	dwErrIndex=0;
	if(g_NUM_CENUM!=EN_CTYPE_END-EN_CTYPE_PARA_END)
	{
		AppLog<<"枚举类型常量表配置错误:"<<"g_NUM_CENUM="<<g_NUM_CENUM<<"EN_CTYPE_END="<<EN_CTYPE_END-EN_CTYPE_PARA_END<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_CENUM;dwLoop++)
	{
		if(ptCEnumTab->wIndex!=dwLoop+EN_CTYPE_PARA_END)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			AppLog<<"枚举类型常量表配置错误:"<<"Index="<<dwLoop<<"\n";
		}
		
		if((ptCEnumTab->pUnit1==NULL)||(ptCEnumTab->pUnit2==NULL))
		{
			dwErrFlg|=CN_CONST_CHK_TYPE;
			dwErrIndex=dwLoop;
			
			AppLog<<"枚举类型常量表单位配置错误:"<<"Index="<<dwLoop<<"\n";
		}
		if(ptCEnumTab->byEnNum>CN_NUM_ENUMDES)
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			AppLog<<"枚举类型常量表枚举个数配置越限:"<<"Index="<<dwLoop<<"byEnNum="<<ptCEnumTab->byEnNum<<"\n";

		}
		else
		{
			for(dwLoop1=0;dwLoop1<ptCEnumTab->byEnNum;dwLoop1++)
			{
				if(ptCEnumTab->eEnumDes[dwLoop1].des==0)
				{
				
					dwErrFlg|=CN_CONST_CHK_ADDR;
					dwErrIndex=dwLoop;
					AppLog<<"枚举类型常量表枚举描述为空:"<<"Index="<<dwLoop<<"byEnNo="<<dwLoop1<<"\n";
				}
				if(ptCEnumTab->eEnumDes[dwLoop1].val!=(INT32)dwLoop1)
				{
				
					dwErrFlg|=CN_CONST_CHK_LINK;
					dwErrIndex=dwLoop;
					AppLog<<"枚举类型常量表枚举描述为空:"<<"Index="<<dwLoop<<"byEnNo="<<dwLoop1<<"\n";
				}
			}
			if(ptCEnumTab->eEnumDes[ptCEnumTab->byEnNum].des!=0)
			{
			
				dwErrFlg|=CN_CONST_CHK_ADDR;
				dwErrIndex=dwLoop;
				AppLog<<"枚举类型常量表枚举描述为空:"<<"Index="<<dwLoop<<"byEnNum="<<ptCEnumTab->byEnNum<<"\n";
			}
		}
		ptCEnumTab++;
	}
	
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,DB30,dwErrFlg,dwErrIndex);
	}
	// 事项参数常量表自检
	ptMEATab   = &g_tMEATab[0];
	dwErrFlg=0;
	dwErrIndex=0;
	if(g_NUM_MEA!=EN_MEA_END)
	{
		AppLog<<"事项参数常量表配置错误:"<<"g_NUM_MEA="<<g_NUM_MEA<<"EN_MEA_END="<<EN_MEA_END<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_MEA;dwLoop++)
	{

		if(ptMEATab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			AppLog<<"事项参数常量表配置错误:"<<"Index="<<dwLoop<<"\n";
		}
		
		if(ptMEATab->eventData.name[20-1]!=0)
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			AppLog<<"事项参数常量表名称长度配置错误:"<<"Index="<<dwLoop<<"\n";
		}
		if(ptMEATab->eventData.valueType==E_SVT_NULL)
		{
			dwErrFlg|=CN_CONST_CHK_TYPE;
			dwErrIndex=dwLoop;
			AppLog<<"事项参数常量表数据类型配置错误:"<<"Index="<<dwLoop<<"\n";
		}
		if((ptMEATab->eventData.dataWidth>32)
		||(ptMEATab->eventData.dataWidth<ptMEATab->eventData.dotNum))
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			AppLog<<"事项参数常量表数据长度配置错误:"<<"Index="<<dwLoop<<"dataWidth="<<ptMEATab->eventData.dataWidth<<"dotNum="<<ptMEATab->eventData.dotNum<<"\n";

		}
		if(ptMEATab->eventData.units==0)
		{
			dwErrFlg|=CN_CONST_CHK_ADDR;
			dwErrIndex=dwLoop;
			AppLog<<"事项参数常量表单位配置错误:"<<"Index="<<dwLoop<<"\n";
		}
		if((ptMEATab->eventData.valueType ==E_SVT_ENUMDES)&&(ptMEATab->eventData.EnumNum==0))
		{
			dwErrFlg|=CN_CONST_CHK_SUB;
			dwErrIndex=dwLoop;
			AppLog<<"事项参数常量表枚举类型个数配置错误:"<<"Index="<<dwLoop<<"\n";
		}
		if(ptMEATab->eventData.EnumNum!=0)
		{
			if(ptMEATab->eventData.pEnum==0)
			{
				dwErrFlg|=CN_CONST_CHK_SUB;
				dwErrIndex=dwLoop;
				AppLog<<"事项参数常量表枚举类型指针配置错误:"<<"Index="<<dwLoop<<"\n";
			}
			
			else if(ptMEATab->eventData.pEnum[ptMEATab->eventData.EnumNum].des!=0)
			{
				dwErrFlg|=CN_CONST_CHK_SUB;
				dwErrIndex=dwLoop;
				AppLog<<"事项参数常量表枚举类型与个数不一致:"<<"Index="<<dwLoop<<"\n";
			}
			else
			{
				for(dwLoop1=0;dwLoop1<ptMEATab->eventData.EnumNum;dwLoop1++)
				{
					if(ptMEATab->eventData.pEnum[dwLoop1].des==0)
					{
						dwErrFlg|=CN_CONST_CHK_SUB;
						dwErrIndex=dwLoop;
						AppLog<<"事项参数常量表枚举类型与个数不一致:"<<"Index="<<dwLoop<<"\n";
					}
					if(ptMEATab->eventData.pEnum[dwLoop1].val!=(INT32)dwLoop1)
					{
						dwErrFlg|=CN_CONST_CHK_SUB;
						dwErrIndex=dwLoop;
						AppLog<<"事项参数常量表枚举类型枚举顺序不正确:"<<"Index="<<dwLoop<<"\n";
					}
				}
			}
		}
		ptMEATab++;
	}
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,DB29,dwErrFlg,dwErrIndex);
	}
}



