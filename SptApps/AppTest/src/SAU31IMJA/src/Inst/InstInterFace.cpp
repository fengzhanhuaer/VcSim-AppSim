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
    { EN_CTYPE_DC_ZL3,   &Unit_V,     &Unit_mA,         9,    CN_DC_DSP_SAM,  EN_PARA_DC3_IN},
    { EN_CTYPE_DC_ZL4,   &Unit_V,     &Unit_mA,         9,    CN_DC_DSP_SAM,  EN_PARA_DC4_IN},
    { EN_CTYPE_DC_ZL5,   &Unit_V,     &Unit_mA,         9,    CN_DC_DSP_SAM,  EN_PARA_DC5_IN},
    { EN_CTYPE_DC_ZL6,   &Unit_V,     &Unit_mA,         9,    CN_DC_DSP_SAM,  EN_PARA_DC6_IN},
    { EN_CTYPE_DC_ZL7,   &Unit_V,     &Unit_mA,         9,    CN_DC_DSP_SAM,  EN_PARA_DC7_IN},
    { EN_CTYPE_DC_mA,   &Unit_mA,     &Unit_NULL,       9,    CN_DC_DSP_DEV,  CN_NULL_PINNO},
    { EN_CTYPE_DC_V,    &Unit_V,      &Unit_NULL,       9,    CN_DC_DSP_DEV,  CN_NULL_PINNO},
    { EN_CTYPE_DC_T,    &Unit_TEMPR,  &Unit_NULL,       9,    CN_DC_DSP_DEV,  CN_NULL_PINNO},
    { EN_CTYPE_DC_Hum,  &Unit_Percent,&Unit_NULL,       9,    CN_DC_DSP_DEV,  CN_NULL_PINNO},
    { EN_CTYPE_DC_DBM,  &Unit_dB,     &Unit_NULL,       9,    CN_DC_DSP_DEV,  CN_NULL_PINNO},
    { EN_CTYPE_DC_OPTT, &Unit_TEMPR,  &Unit_NULL,       9,    CN_DC_DSP_DEV,  CN_NULL_PINNO},
    { EN_CTYPE_DC_OPTV, &Unit_V,      &Unit_NULL,       9,    CN_DC_DSP_DEV,  CN_NULL_PINNO},
    { EN_CTYPE_DC_H,    &Unit_NULL,   &Unit_NULL,       9,    0,  CN_NULL_PINNO},
    { EN_CTYPE_DC_CLK,  &Unit_HZ,     &Unit_NULL,       9,    0,  CN_NULL_PINNO},
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
// ??????????????????????20??
// ????????????????????????????????,??????????????????
tagCEnumTab  g_tCEnumTab[] =
{
    { EN_CENUM_PARA_DCIN,   &Unit_NULL,  &Unit_NULL,  2,{{0,"4-20mA"},{1,"  0-5V"}}},
    { EN_CENUM_PARA_DCOUT,  &Unit_NULL,  &Unit_NULL,  2,{{0,"??????"},{1,   "??????"}}},
    { EN_CENUM_PARA_CT2,    &Unit_NULL,  &Unit_NULL,  2,{{0,"1A"},{1,   "5A"}}},
    { EN_CENUM_PARA_BusLik, &Unit_NULL,  &Unit_NULL,  2,{{0,"??????"},{1,   "??????"}}},
    { EN_CENUM_PARA_Fr,     &Unit_NULL,  &Unit_NULL,  3,{{0,"Ua"},{1,"Ub"},{2,"Uc"}}},
    { EN_CENUM_PARA_MSAM,   &Unit_NULL,  &Unit_NULL,  2,{{0,"??????"},{1,   "??????"}}},
    { EN_CENUM_PARA_UxSAM,  &Unit_NULL,  &Unit_NULL, 13,{{0," ??????Ux"},{1," ??????Ua"},
    {2," ??????Ub"},{3," ??????Uc"},{4,"??????Uab"},{5,"??????Ubc"},{6,"??????Uca"},
    {7," ??????Ua"},{8," ??????Ub"},{9," ??????Uc"},{10,"??????Uab"},{11,"??????Ubc"},
    {12,"??????Uca"}}},
//  { EN_CENUM_PARA_XCBR,   &Unit_NULL,  &Unit_NULL,  2,{{0,"????????"},{1,    "????????"}}},
    { EN_CENUM_PARA_DISAM,  &Unit_NULL,  &Unit_NULL,  2,{{0,"????????"},{1,    "????????"}}},
    { EN_CENUM_PARA_Ux,     &Unit_NULL,  &Unit_NULL,  2,{{0,"SV????  "},{1,"????????"}}},
    { EN_CENUM_DO_STATUS,   &Unit_NULL,  &Unit_NULL,  2,{{0,"??????"},{1,"??????"}}},
    { EN_CENUM_FAIL_RET,    &Unit_NULL,  &Unit_NULL,  EN_RET_END,{{EN_INVAILD_NO,"????"},{EN_INVAILD_TEST,"????-??????????"},
      {EN_INVAILD_LINK,"????-????"},{EN_INVAILD_Q,"????-????????"},{EN_INVAILD_DATA,"????-????????"},
      {EN_RET_OVER,"????-????"},{EN_RET_ELSE,"????-????????"},{EN_RET_COVER,"????-????????"},
      {EN_RET_DIF,"????-??????????"}}},
};
const DWORD g_NUM_CENUM= sizeof(g_tCEnumTab) / sizeof(tagCEnumTab);

#define  EDes(Index)  (g_tCEnumTab[Index- EN_CENUM_STR].eEnumDes)
#define  ENumb(Index)  (g_tCEnumTab[Index- EN_CENUM_STR].byEnNum)
tagMEATab g_tMEATab[] =
{
	{EN_MEA_INDEX,       {"????",          E_SVT_U32      , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_LC_RX,       {"????????",        E_SVT_U32      , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_LC_TX,       {"????????",        E_SVT_U32      , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_PTR,         {"????",          E_SVT_HEX32    , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_DTYPE,       {"????????",        E_SVT_U32      , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_FLAG,        {"??????",         E_SVT_HEX32    , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_FLAG16,      {"??????",         E_SVT_HEX16    , 4, 0, &Unit_NULL,0,0}},
	{EN_MEA_FLAG8,       {"??????",         E_SVT_HEX8     , 2, 0, &Unit_NULL,0,0}},
	{EN_MEA_V,           {"????",          E_SVT_I32      , 8, 3, &Unit_V   ,0,0}},
	{EN_MEA_mA,          {"????",          E_SVT_I32      , 8, 3, &Unit_mA  ,0,0}},
	{EN_MEA_VALUE,       {"??????",         E_SVT_U32      , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_PORT,        {"??????",         E_SVT_U32      , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_BOARD,       {"??????",         E_SVT_U32      , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_SVCB,        {"SVCB??",       E_SVT_U32      , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_SVCB_SUB,    {"??????",         E_SVT_HEX32    , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_SVCB_CFG,    {"??????",         E_SVT_HEX32    , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_GOCB,        {"GOCB??",        E_SVT_U32      , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_GOCB_A,      {"A??????",         E_SVT_HEX32    , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_GOCB_B,      {"B??????",         E_SVT_HEX32    , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_GOCB_CFG,    {"??????",          E_SVT_HEX32    , 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_BHTZ_DO,       {"????????????    ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_BHHZ_DO,       {"????????????    ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_CKTZ_DO,       {"????????????    ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_CKHZ_DO,       {"????????????    ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_JBS_XCBR_DO,   {"????????????????",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_BZTTZ_DO,      {"??????????????  ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_BZTHZ_DO,      {"??????????????  ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_CLS_XSWI01_DO, {"????1????????   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_OPN_XSWI01_DO, {"????1????????   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_JBS_XSWI01_DO, {"????1?????????? ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_CLS_XSWI02_DO, {"????2????????   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_OPN_XSWI02_DO, {"????2????????   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_JBS_XSWI02_DO, {"????2?????????? ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_CLS_XSWI03_DO, {"????3????????   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_OPN_XSWI03_DO, {"????3????????   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_JBS_XSWI03_DO, {"????3?????????? ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_CLS_XSWI04_DO, {"????4????????   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_OPN_XSWI04_DO, {"????4????????   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_JBS_XSWI04_DO, {"????4?????????? ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_CLS_XSWI05_DO, {"????5????????   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_OPN_XSWI05_DO, {"????5????????   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_JBS_XSWI05_DO, {"????5?????????? ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_CLS_XSWI06_DO, {"????6????????   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_OPN_XSWI06_DO, {"????6????????   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_JBS_XSWI06_DO, {"????6?????????? ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_CLS_XSWI07_DO, {"????7????????   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_OPN_XSWI07_DO, {"????7????????   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_JBS_XSWI07_DO, {"????7?????????? ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_CLS_XSWI08_DO, {"????8????????   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_OPN_XSWI08_DO, {"????8????????   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_JBS_XSWI08_DO, {"????8?????????? ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_BAK_01_DO,     {"????????1????   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_BAK_02_DO,     {"????????2????   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_DO_STATUS,     {"GOOSE????????   ",     E_SVT_ENUM8, 8, 0, &Unit_NULL,EDes(EN_CENUM_DO_STATUS),ENumb(EN_CENUM_DO_STATUS)}},
	{EN_MEA_DO_FAIL,       {"GOOSE????????   ",     E_SVT_ENUM8, 16, 0, &Unit_NULL,EDes(EN_CENUM_FAIL_RET),ENumb(EN_CENUM_FAIL_RET)}},
	{EN_MEA_DO_APPID,      {"GOOSE????APPID  ",    E_SVT_HEX16, 8, 0, &Unit_NULL,0,0}},
	{EN_MEA_DO_RET_T,      {"????????????(us)",     E_SVT_U32  , 8, 0, &Unit_uS,   0,0}},
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
	{EN_KEY_DBG,{EK_UP,EK_DOWN,EK_LEFT,EK_RIGHT},4},
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
	// ??????????????????
	ptCTypeTab = &g_tCTypeTab[0];
	if(g_NUM_CTYPE!=EN_CTYPE_PARA_END)
	{
		AppLog<<"??????????????????????:"<<"g_NUM_CTYPE="<<g_NUM_CTYPE<<"EN_CTYPE_PARA_END="<<EN_CTYPE_PARA_END<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_CTYPE;dwLoop++)
	{
		if(ptCTypeTab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			
			AppLog<<"??????????????????????:"<<"Index="<<dwLoop<<"\n";
		}
		if((ptCTypeTab->pUnit1==NULL)||(ptCTypeTab->pUnit2==NULL))
		{
			dwErrFlg|=CN_CONST_CHK_TYPE;
			dwErrIndex=dwLoop;
			AppLog<<"??????????????????????????:"<<"Index="<<dwLoop<<"\n";
		}
		if((ptCTypeTab->byWidth<ptCTypeTab->byDotBit)
		||(ptCTypeTab->byWidth>16))
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			AppLog<<"??????????????????????????????:"<<"Index="<<dwLoop<<"byWidth="<<ptCTypeTab->byWidth<<"byDotBit="<<ptCTypeTab->byDotBit<<"\n";
		}
		if((ptCTypeTab->wParaIndex!=CN_NULL_PINNO)&&(ptCTypeTab->wParaIndex>=CN_NUM_PARA))
		{
			dwErrFlg|=CN_CONST_CHK_PARA1;
			dwErrIndex=dwLoop;
			AppLog<<"????????????????????:"<<"Index="<<dwLoop<<"wParaIndex="<<ptCTypeTab->wParaIndex<<"\n";
		}
		ptCTypeTab++;
	}
	
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,DB31,dwErrFlg,dwErrIndex);
	}
	// ??????????????????
	ptCEnumTab = &g_tCEnumTab[0];
	dwErrFlg=0;
	dwErrIndex=0;
	if(g_NUM_CENUM!=EN_CTYPE_END-EN_CTYPE_PARA_END)
	{
		AppLog<<"??????????????????????:"<<"g_NUM_CENUM="<<g_NUM_CENUM<<"EN_CTYPE_END="<<EN_CTYPE_END-EN_CTYPE_PARA_END<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_CENUM;dwLoop++)
	{
		if(ptCEnumTab->wIndex!=dwLoop+EN_CTYPE_PARA_END)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			AppLog<<"??????????????????????:"<<"Index="<<dwLoop<<"\n";
		}
		
		if((ptCEnumTab->pUnit1==NULL)||(ptCEnumTab->pUnit2==NULL))
		{
			dwErrFlg|=CN_CONST_CHK_TYPE;
			dwErrIndex=dwLoop;
			
			AppLog<<"??????????????????????????:"<<"Index="<<dwLoop<<"\n";
		}
		if(ptCEnumTab->byEnNum>CN_NUM_ENUMDES)
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			AppLog<<"??????????????????????????????:"<<"Index="<<dwLoop<<"byEnNum="<<ptCEnumTab->byEnNum<<"\n";

		}
		else
		{
			for(dwLoop1=0;dwLoop1<ptCEnumTab->byEnNum;dwLoop1++)
			{
				if(ptCEnumTab->eEnumDes[dwLoop1].des==0)
				{
				
					dwErrFlg|=CN_CONST_CHK_ADDR;
					dwErrIndex=dwLoop;
					AppLog<<"??????????????????????????:"<<"Index="<<dwLoop<<"byEnNo="<<dwLoop1<<"\n";
				}
				if(ptCEnumTab->eEnumDes[dwLoop1].val!=(INT32)dwLoop1)
				{
				
					dwErrFlg|=CN_CONST_CHK_LINK;
					dwErrIndex=dwLoop;
					AppLog<<"??????????????????????????:"<<"Index="<<dwLoop<<"byEnNo="<<dwLoop1<<"\n";
				}
			}
			if(ptCEnumTab->eEnumDes[ptCEnumTab->byEnNum].des!=0)
			{
			
				dwErrFlg|=CN_CONST_CHK_ADDR;
				dwErrIndex=dwLoop;
				AppLog<<"??????????????????????????:"<<"Index="<<dwLoop<<"byEnNum="<<ptCEnumTab->byEnNum<<"\n";
			}
		}
		ptCEnumTab++;
	}
	
	if(dwErrFlg)
	{
		G_Set_ChkIn_All(EN_CHK_CONST,DB30,dwErrFlg,dwErrIndex);
	}
	// ??????????????????
	ptMEATab   = &g_tMEATab[0];
	dwErrFlg=0;
	dwErrIndex=0;
	if(g_NUM_MEA!=EN_MEA_END)
	{
		AppLog<<"??????????????????????:"<<"g_NUM_MEA="<<g_NUM_MEA<<"EN_MEA_END="<<EN_MEA_END<<"\n";
		dwErrFlg|=CN_CONST_CHK_NUM;
	}
	for(dwLoop=0;dwLoop<g_NUM_MEA;dwLoop++)
	{

		if(ptMEATab->wIndex!=dwLoop)
		{
			dwErrFlg|=CN_CONST_CHK_NO;
			dwErrIndex=dwLoop;
			AppLog<<"??????????????????????:"<<"Index="<<dwLoop<<"\n";
		}
		
		if(ptMEATab->eventData.name[20-1]!=0)
		{
			dwErrFlg|=CN_CONST_CHK_CHAR;
			dwErrIndex=dwLoop;
			AppLog<<"??????????????????????????????:"<<"Index="<<dwLoop<<"\n";
		}
		if(ptMEATab->eventData.valueType==E_SVT_NULL)
		{
			dwErrFlg|=CN_CONST_CHK_TYPE;
			dwErrIndex=dwLoop;
			AppLog<<"??????????????????????????????:"<<"Index="<<dwLoop<<"\n";
		}
		if((ptMEATab->eventData.dataWidth>32)
		||(ptMEATab->eventData.dataWidth<ptMEATab->eventData.dotNum))
		{
			dwErrFlg|=CN_CONST_CHK_LMT;
			dwErrIndex=dwLoop;
			AppLog<<"??????????????????????????????:"<<"Index="<<dwLoop<<"dataWidth="<<ptMEATab->eventData.dataWidth<<"dotNum="<<ptMEATab->eventData.dotNum<<"\n";

		}
		if(ptMEATab->eventData.units==0)
		{
			dwErrFlg|=CN_CONST_CHK_ADDR;
			dwErrIndex=dwLoop;
			AppLog<<"??????????????????????????:"<<"Index="<<dwLoop<<"\n";
		}
		if((ptMEATab->eventData.valueType ==E_SVT_ENUMDES)&&(ptMEATab->eventData.EnumNum==0))
		{
			dwErrFlg|=CN_CONST_CHK_SUB;
			dwErrIndex=dwLoop;
			AppLog<<"??????????????????????????????????:"<<"Index="<<dwLoop<<"\n";
		}
		if(ptMEATab->eventData.EnumNum!=0)
		{
			if(ptMEATab->eventData.pEnum==0)
			{
				dwErrFlg|=CN_CONST_CHK_SUB;
				dwErrIndex=dwLoop;
				AppLog<<"??????????????????????????????????:"<<"Index="<<dwLoop<<"\n";
			}
			
			else if(ptMEATab->eventData.pEnum[ptMEATab->eventData.EnumNum].des!=0)
			{
				dwErrFlg|=CN_CONST_CHK_SUB;
				dwErrIndex=dwLoop;
				AppLog<<"??????????????????????????????????:"<<"Index="<<dwLoop<<"\n";
			}
			else
			{
				for(dwLoop1=0;dwLoop1<ptMEATab->eventData.EnumNum;dwLoop1++)
				{
					if(ptMEATab->eventData.pEnum[dwLoop1].des==0)
					{
						dwErrFlg|=CN_CONST_CHK_SUB;
						dwErrIndex=dwLoop;
						AppLog<<"??????????????????????????????????:"<<"Index="<<dwLoop<<"\n";
					}
					if(ptMEATab->eventData.pEnum[dwLoop1].val!=(INT32)dwLoop1)
					{
						dwErrFlg|=CN_CONST_CHK_SUB;
						dwErrIndex=dwLoop;
						AppLog<<"????????????????????????????????????:"<<"Index="<<dwLoop<<"\n";
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



