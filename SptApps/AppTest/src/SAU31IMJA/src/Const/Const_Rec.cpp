/*================================================================================
 * �ļ��������������ó�����
 * �ļ��汾: V1.00
 * ������Ա:
 * ����ʱ��:
 * �汾�޶�:
 * �޶���Ա:
 *================================================================================*/

#include "Const_Pub.h"
//================================================================================
// GOOSE�������
//  WORD            wIndex;                  // ��¼ö��
//  WORD            wSrcType;                // ����Դ����
//  WORD            wSrcIndex[CN_ACT_SNUM];  // ����Դö��
//  WORD            wCfg;                    // ��������
//  WORD            wValType1;               // �����¼��������1
//  WORD            wValType2;               // �����¼��������2
//  WORD            wValType3;               // �����¼��������3
//  WORD            wValType4;               // �����¼��������4
//  WORD            wValType5;               // �����¼��������5
//  WORD            wValType6;               // �����¼��������6
//  INT8S           byName[CN_LEN_NAME];     // ��¼����
//  INT8S           byPinName[CN_LEN_NAME];  // ���������
//================================================================================
const tagActTab g_tActTab[ ] =
{
	{EN_ACT_BHTZ  ,   EN_DTYPE_GOIN,             {EN_GOIN_BHTZ1,      // ������բ1
	                                              EN_GOIN_BHTZ2,      // ������բ2
	                                              EN_GOIN_BHTZ3,      // ������բ3
	                                              EN_GOIN_BHTZ4,      // ������բ4
	                                              EN_GOIN_BHTZ5,      // ������բ5
	                                              CN_NULL_PINNO       // ������
	                                               },        EN_DO_BHTZ,      EN_DI_DO_BHTZ,    0, EN_MEA_DO_STATUS, EN_MEA_BHTZ_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "������բ",    "ACT_BHTZ"},
	{EN_ACT_BHHZ  ,   EN_DTYPE_GOIN,             {EN_GOIN_BHHZ1,      // �����غ�բ1
	                                              EN_GOIN_BHHZ2,      // �����غ�բ2
	                                              EN_GOIN_BHHZ3,      // �����غ�բ3
	                                              EN_GOIN_BHHZ4,      // �����غ�բ4
	                                              EN_GOIN_BHHZ5,      // �����غ�բ5
	                                              CN_NULL_PINNO       // ������
	                                                },        EN_DO_BHHZ,    EN_DI_DO_BHHZ,    0,  EN_MEA_DO_STATUS,  EN_MEA_BHHZ_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�����غ�բ",    "ACT_BHHZ"},
	{EN_ACT_BHYT  ,   EN_DTYPE_GOIN,             {EN_GOIN_BHYT1,      // ��������1
	                                              EN_GOIN_BHYT2,      // ��������2
	                                              EN_GOIN_BHYT3,      // ��������3
	                                              EN_GOIN_BHYT4,      // ��������4
	                                              EN_GOIN_BHYT5,      // ��������5
	                                              EN_GOIN_BHYT6,      // ��������6
	                                              EN_GOIN_BHYT7,      // ��������7
	                                              EN_GOIN_BHYT8,      // ��������8
	                                              EN_GOIN_BHYT9,      // ��������9
	                                              EN_GOIN_BHYT10,     // ��������10
	                                              CN_NULL_PINNO       // ������
	                                               },         EN_DO_BHTZ,    EN_DI_DO_BHTZ,      0,  EN_MEA_DO_STATUS,  EN_MEA_BHTZ_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "��������"  ,      "ACT_BHYT"},
	{EN_ACT_CKTZ  ,   EN_DTYPE_GOIN,             {EN_GOIN_CKTZ,
	                                             CN_NULL_PINNO       // ������
	                                                },        EN_DO_XCBR_OPN,   EN_DI_DO_XCBR_OPN,  0,  EN_MEA_DO_STATUS,  EN_MEA_CKTZ_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�����բ",       "ACT_CKTZ"},
	{EN_ACT_CKHZ  ,   EN_DTYPE_GOIN,             {EN_GOIN_CKHZ,
	                                              CN_NULL_PINNO      // ������
	                                                 },       EN_DO_XCBR_CLS,    EN_DI_DO_XCBR_CLS,  0,  EN_MEA_DO_STATUS,  EN_MEA_CKHZ_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "��غ�բ",       "ACT_CKHZ"},
	{EN_ACT_JBS_XCBR  ,   EN_DTYPE_GOIN,             {EN_GOIN_JBS_XCBR,
	                                              CN_NULL_PINNO      // ������
	                                                 },       EN_DO_XCBR_JBS,    EN_DI_DO_XCBR_JBS,  0,  EN_MEA_DO_STATUS,  EN_MEA_JBS_XCBR_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "��·�������",       "ACT_JBS_XCBR"},

	{EN_ACT_BZTTZ ,   EN_DTYPE_GOIN,             {EN_GOIN_BZTTZ1,
	                                              EN_GOIN_BZTTZ2,
	                                              CN_NULL_PINNO       // ������
	                                                 },       EN_DO_BZTTZ,              EN_DI_DO_BZTTZ,     0,  EN_MEA_DO_STATUS,  EN_MEA_BZTTZ_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "����Ͷ��բ",       "ACT_BZTTZ"},
	{EN_ACT_BZTHZ ,   EN_DTYPE_GOIN,             {EN_GOIN_BZTHZ1,
	                                              EN_GOIN_BZTHZ2,
	                                              CN_NULL_PINNO      // ������
	                                                 },       EN_DO_BZTHZ,              EN_DI_DO_BZTHZ,    0,  EN_MEA_DO_STATUS,  EN_MEA_BZTHZ_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "����Ͷ��բ",       "ACT_BZTHZ"},
	{EN_ACT_CLS_XSWI01  ,   EN_DTYPE_GOIN,       {EN_GOIN_CLS_XSWI01,
	                                              CN_NULL_PINNO       // ������
	                                                 },       EN_DO_XSWI01_CLS,         EN_DI_DO_XSWI01_CLS,  0,  EN_MEA_DO_STATUS,  EN_MEA_CLS_XSWI01_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�ϵ�բ1",       "ACT_CLS_XSWI01"},
	{EN_ACT_OPN_XSWI01  ,   EN_DTYPE_GOIN,       {EN_GOIN_OPN_XSWI01,
	                                              CN_NULL_PINNO      // ������
	                                                 },       EN_DO_XSWI01_OPN,         EN_DI_DO_XSWI01_OPN,  0,  EN_MEA_DO_STATUS,  EN_MEA_OPN_XSWI01_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�ֵ�բ1",       "ACT_OPN_XSWI01"},
	{EN_ACT_JBS_XSWI01  ,   EN_DTYPE_GOIN,       {EN_GOIN_JBS_XSWI01,
	                                              CN_NULL_PINNO       // ������
	                                                 },       EN_DO_XSWI01_JBS,         EN_DI_DO_XSWI01_JBS,  0,  EN_MEA_DO_STATUS,  EN_MEA_JBS_XSWI01_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�����1"  ,       "ACT_JBS_XSWI01"},
	{EN_ACT_CLS_XSWI02  ,   EN_DTYPE_GOIN,       {EN_GOIN_CLS_XSWI02,
	                                              CN_NULL_PINNO      // ������
	                                                 },       EN_DO_XSWI02_CLS,         EN_DI_DO_XSWI02_CLS,  0,  EN_MEA_DO_STATUS,  EN_MEA_CLS_XSWI02_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�ϵ�բ2",       "ACT_CLS_XSWI02"},
	{EN_ACT_OPN_XSWI02  ,   EN_DTYPE_GOIN,       {EN_GOIN_OPN_XSWI02  ,
	                                              CN_NULL_PINNO       // ������
	                                                 },       EN_DO_XSWI02_OPN,         EN_DI_DO_XSWI02_OPN,  0,  EN_MEA_DO_STATUS,  EN_MEA_OPN_XSWI02_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�ֵ�բ2",       "ACT_OPN_XSWI02"},
	{EN_ACT_JBS_XSWI02  ,   EN_DTYPE_GOIN,       {EN_GOIN_JBS_XSWI02,
	                                              CN_NULL_PINNO      // ������
	                                                 },       EN_DO_XSWI02_JBS,         EN_DI_DO_XSWI02_JBS,  0,  EN_MEA_DO_STATUS,  EN_MEA_JBS_XSWI02_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�����2"  ,       "ACT_JBS_XSWI02"},
	{EN_ACT_CLS_XSWI03  ,   EN_DTYPE_GOIN,       {EN_GOIN_CLS_XSWI03,
	                                              CN_NULL_PINNO       // ������
	                                                 },       EN_DO_XSWI03_CLS,         EN_DI_DO_XSWI03_CLS,  0,  EN_MEA_DO_STATUS,  EN_MEA_CLS_XSWI03_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�ϵ�բ3",       "ACT_CLS_XSWI03"},
	{EN_ACT_OPN_XSWI03  ,   EN_DTYPE_GOIN,       {EN_GOIN_OPN_XSWI03,
	                                              CN_NULL_PINNO      // ������
	                                                 },       EN_DO_XSWI03_OPN,         EN_DI_DO_XSWI03_OPN,  0,  EN_MEA_DO_STATUS,  EN_MEA_OPN_XSWI03_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�ֵ�բ3",       "ACT_OPN_XSWI03"},
	{EN_ACT_JBS_XSWI03  ,   EN_DTYPE_GOIN,       {EN_GOIN_JBS_XSWI03,
	                                              CN_NULL_PINNO       // ������
	                                                 },       EN_DO_XSWI03_JBS,         EN_DI_DO_XSWI03_JBS,  0,  EN_MEA_DO_STATUS,  EN_MEA_JBS_XSWI03_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�����3"  ,       "ACT_JBS_XSWI03"},
	{EN_ACT_CLS_XSWI04  ,   EN_DTYPE_GOIN,       {EN_GOIN_CLS_XSWI04,
	                                              CN_NULL_PINNO       // ������
	                                                 },       EN_DO_XSWI04_CLS,         EN_DI_DO_XSWI04_CLS,  0,  EN_MEA_DO_STATUS,  EN_MEA_CLS_XSWI04_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�ϵ�բ4",       "ACT_CLS_XSWI04"},
	{EN_ACT_OPN_XSWI04  ,   EN_DTYPE_GOIN,       {EN_GOIN_OPN_XSWI04,
	                                              CN_NULL_PINNO      // ������
	                                                 },       EN_DO_XSWI04_OPN,         EN_DI_DO_XSWI04_OPN,  0,  EN_MEA_DO_STATUS,  EN_MEA_OPN_XSWI04_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�ֵ�բ4",       "ACT_OPN_XSWI04"},
	{EN_ACT_JBS_XSWI04  ,   EN_DTYPE_GOIN,       {EN_GOIN_JBS_XSWI04,
	                                              CN_NULL_PINNO       // ������
	                                                 },      EN_DO_XSWI04_JBS,         EN_DI_DO_XSWI04_JBS,  0,  EN_MEA_DO_STATUS,  EN_MEA_JBS_XSWI04_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�����4"  ,       "ACT_JBS_XSWI04"},
	{EN_ACT_CLS_XSWI05  ,   EN_DTYPE_GOIN,       {EN_GOIN_CLS_XSWI05,
	                                              CN_NULL_PINNO      // ������
	                                                 },      EN_DO_XSWI05_CLS,         EN_DI_DO_XSWI05_CLS,  0,  EN_MEA_DO_STATUS,  EN_MEA_CLS_XSWI05_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�ϵ�բ5",       "ACT_CLS_XSWI05"},
	{EN_ACT_OPN_XSWI05  ,   EN_DTYPE_GOIN,       {EN_GOIN_OPN_XSWI05,
	                                              CN_NULL_PINNO       // ������
	                                                 },       EN_DO_XSWI05_OPN,        EN_DI_DO_XSWI05_OPN,  0,  EN_MEA_DO_STATUS,  EN_MEA_OPN_XSWI05_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�ֵ�բ5",       "ACT_OPN_XSWI05"},
	{EN_ACT_JBS_XSWI05  ,   EN_DTYPE_GOIN,       {EN_GOIN_JBS_XSWI05,
	                                              CN_NULL_PINNO      // ������
	                                                 },       EN_DO_XSWI05_JBS,        EN_DI_DO_XSWI05_JBS,  0,  EN_MEA_DO_STATUS,  EN_MEA_JBS_XSWI05_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�����5"  ,       "ACT_JBS_XSWI05"},
	{EN_ACT_CLS_XSWI06  ,   EN_DTYPE_GOIN,       {EN_GOIN_CLS_XSWI06,
	                                              CN_NULL_PINNO       // ������
	                                                 },       EN_DO_XSWI06_CLS,        EN_DI_DO_XSWI06_CLS,  0,  EN_MEA_DO_STATUS,  EN_MEA_CLS_XSWI06_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�ϵ�բ6",       "ACT_CLS_XSWI06"},
	{EN_ACT_OPN_XSWI06  ,   EN_DTYPE_GOIN,       {EN_GOIN_OPN_XSWI06,
	                                              CN_NULL_PINNO       // ������
	                                                 },       EN_DO_XSWI06_OPN,        EN_DI_DO_XSWI06_OPN,  0,  EN_MEA_DO_STATUS,  EN_MEA_OPN_XSWI06_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�ֵ�բ6",       "ACT_OPN_XSWI06"},
	{EN_ACT_JBS_XSWI06  ,   EN_DTYPE_GOIN,       {EN_GOIN_JBS_XSWI06,
	                                              CN_NULL_PINNO      // ������
	                                                 },       EN_DO_XSWI06_JBS,        EN_DI_DO_XSWI06_JBS,  0,  EN_MEA_DO_STATUS,  EN_MEA_JBS_XSWI06_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�����6"  ,       "ACT_JBS_XSWI06"},
	{EN_ACT_CLS_XSWI07  ,   EN_DTYPE_GOIN,       {EN_GOIN_CLS_XSWI07,
	                                              CN_NULL_PINNO       // ������
	                                                 },       EN_DO_XSWI07_CLS,        EN_DI_DO_XSWI07_CLS,  0,  EN_MEA_DO_STATUS,  EN_MEA_CLS_XSWI07_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�ϵ�բ7",       "ACT_CLS_XSWI07"},
	{EN_ACT_OPN_XSWI07  ,   EN_DTYPE_GOIN,       {EN_GOIN_OPN_XSWI07,
	                                              CN_NULL_PINNO      // ������
	                                                 },       EN_DO_XSWI07_OPN,        EN_DI_DO_XSWI07_OPN,  0,  EN_MEA_DO_STATUS,  EN_MEA_OPN_XSWI07_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�ֵ�բ7",       "ACT_OPN_XSWI07"},
	{EN_ACT_JBS_XSWI07  ,   EN_DTYPE_GOIN,       {EN_GOIN_JBS_XSWI07,
	                                              CN_NULL_PINNO       // ������
	                                                 },       EN_DO_XSWI07_JBS,        EN_DI_DO_XSWI07_JBS,  0,  EN_MEA_DO_STATUS,  EN_MEA_JBS_XSWI07_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�����7"  ,       "ACT_JBS_XSWI07"},
	{EN_ACT_CLS_XSWI08  ,   EN_DTYPE_GOIN,       {EN_GOIN_CLS_XSWI08,
	                                              CN_NULL_PINNO      // ������
	                                                 },       EN_DO_XSWI08_CLS,        EN_DI_DO_XSWI08_CLS,  0,  EN_MEA_DO_STATUS,   EN_MEA_CLS_XSWI08_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�ϵ�բ8",       "ACT_CLS_XSWI08"},
	{EN_ACT_OPN_XSWI08  ,   EN_DTYPE_GOIN,       {EN_GOIN_OPN_XSWI08,
	                                              CN_NULL_PINNO       // ������
	                                                 },       EN_DO_XSWI08_OPN,        EN_DI_DO_XSWI08_OPN,  0,  EN_MEA_DO_STATUS,  EN_MEA_OPN_XSWI08_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�ֵ�բ8",       "ACT_OPN_XSWI08"},
	{EN_ACT_JBS_XSWI08  ,   EN_DTYPE_GOIN,       {EN_GOIN_JBS_XSWI08,
	                                              CN_NULL_PINNO      // ������
	                                                 },       EN_DO_XSWI08_JBS,        EN_DI_DO_XSWI08_JBS,  0,  EN_MEA_DO_STATUS,  EN_MEA_JBS_XSWI08_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "�����8"  ,       "ACT_JBS_XSWI08"},
	{EN_ACT_BAK_01      ,   EN_DTYPE_GOIN,       {EN_GOIN_BAK_01,
	                                              CN_NULL_PINNO       // ������
	                                                 },       EN_DO_YK_BAK1,           EN_DI_DO_YK_BAK1,     0,  EN_MEA_DO_STATUS, EN_MEA_BAK_01_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "����ң��1"    ,      "ACT_BAK_01"},
	{EN_ACT_BAK_02      ,   EN_DTYPE_GOIN,       {EN_GOIN_BAK_02,
	                                              CN_NULL_PINNO      // ������
	                                                 },       EN_DO_YK_BAK2,           EN_DI_DO_YK_BAK2,     0,  EN_MEA_DO_STATUS,  EN_MEA_BAK_02_DO,EN_MEA_DO_RET_T,EN_MEA_DO_FAIL,EN_MEA_DO_APPID,CN_NULL_PINNO,  "����ң��2"    ,      "ACT_BAK_02"}
};
const DWORD g_NUM_ACT = sizeof(g_tActTab) / sizeof(tagActTab);
//================================================================================
// �澯������
//  WORD            wIndex;            // ��¼ö��
//  WORD            wParaEna;          // Ͷ�˲���ö��
//  WORD            wParaTime;         // ʱ�����ö��
//  WORD            wDefTime;          // Ĭ��ʱ�����
//  WORD            wRetTime;          // Ĭ�Ϸ���ʱ�����
//  WORD            wCfg;              // �������ã�NULL �޲��� DB0-�����쳣����
//  WORD            wValType1;         // �����¼��������1
//  WORD            wValType2;         // �����¼��������2
//  WORD            wValType3;         // �����¼��������3
//  INT8S           byName[CN_LEN_NAME];        // ��¼����
//  INT8S           byPinName[CN_LEN_NAME];     // ���������
//================================================================================

const tagAlmTab g_tAlmTab[ ] =
{
	{EN_ALM_SYN           ,     CN_NULL_PINNO,         EN_PARA_T_SYNCHK,   CN_T1S,        CN_T1S,    DB0,  CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "ͬ���쳣",               "ALM_SYN"},
	{EN_ALM_SAM           ,     CN_NULL_PINNO,         EN_PARA_T_SAMCHK,   CN_T1S,        CN_T1S,    DB0,  EN_MEA_FLAG16,  EN_MEA_FLAG16,  CN_NULL_PINNO,  "�����쳣",               "ALM_SAM"},
	{EN_ALM_DIPOW         ,     CN_NULL_PINNO,         EN_PARA_T_DICHK ,   CN_T1S,        CN_T1S,    DB0,  EN_MEA_FLAG16,  CN_NULL_PINNO,  CN_NULL_PINNO,  "����ʧ��",               "ALM_DIPOW"},
	{EN_ALM_TIME_SINGLE   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "��ʱ�ź�״̬",             "ALM_TIME_SINGLE"},
	{EN_ALM_TIME_SERVICE  ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "��ʱ����״̬",             "ALM_TIME_SERVICE"},
	{EN_ALM_TIME_CHKERR   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "ʱ���������״̬",           "ALM_TIME_CHKERR"},
	{EN_ALM_TEST          ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���޲�һ��",              "ALM_TEST"},
	{EN_ALM_SV            ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         DB0,  CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "SV�ܸ澯",              "ALM_SV"},
	{EN_ALM_SVPUB_INVALID ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "SV����������Ч",           "ALM_SVPUB_INVALID"},
	{EN_ALM_LINK          ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "�����쳣",                "ALM_LINK"},
	{EN_ALM_SVSUB         ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "SV���������쳣",            "ALM_SVSUB"},
	{EN_ALM_SVSUB_COM01   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    EN_MEA_SVCB_SUB,CN_NULL_PINNO,  CN_NULL_PINNO,  "SVCB01����",            "ALM_SVSUB_COM01"},
	{EN_ALM_SVSUB_COM02   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    EN_MEA_SVCB_SUB,CN_NULL_PINNO,  CN_NULL_PINNO,  "SVCB02����",            "ALM_SVSUB_COM02"},
	{EN_ALM_SVSUB_DAT01   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    EN_MEA_SVCB_SUB,CN_NULL_PINNO,  CN_NULL_PINNO,  "SVCB01�����쳣",          "ALM_SVSUB_DAT01"},
	{EN_ALM_SVSUB_DAT02   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    EN_MEA_SVCB_SUB,CN_NULL_PINNO,  CN_NULL_PINNO,  "SVCB02�����쳣",          "ALM_SVSUB_DAT02"},
	{EN_ALM_SVSUB_TEST01  ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    EN_MEA_SVCB_SUB,CN_NULL_PINNO,  CN_NULL_PINNO,  "SVCB01���޲�һ��",         "ALM_SVSUB_TEST01"},
	{EN_ALM_SVSUB_TEST02  ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    EN_MEA_SVCB_SUB,CN_NULL_PINNO,  CN_NULL_PINNO,  "SVCB02���޲�һ��",         "ALM_SVSUB_TEST02"},
	{EN_ALM_SVSUB_SYN01   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    EN_MEA_SVCB_SUB,CN_NULL_PINNO,  CN_NULL_PINNO,  "SVCB01ͬ���쳣",          "ALM_SVSUB_SYN01"},
	{EN_ALM_SVSUB_SYN02   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    EN_MEA_SVCB_SUB,CN_NULL_PINNO,  CN_NULL_PINNO,  "SVCB02ͬ���쳣",          "ALM_SVSUB_SYN02"},
	{EN_ALM_SVSUB_CFG01   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "SVCB01���ô���",          "ALM_SVSUB_CFG01"},
	{EN_ALM_SVSUB_CFG02   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "SVCB02���ô���",          "ALM_SVSUB_CFG02"},

	{EN_ALM_SVLINK_QA     ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "A�׼���SV�����쳣",          "ALM_SVLINK_QA"},
	{EN_ALM_SVLINK_QB     ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "B�׼���SV�����쳣",          "ALM_SVLINK_QB"},
	{EN_ALM_SVLINK_CFGA   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "A�׼���SV�����쳣",          "ALM_SVLINK_CFGA"},
	{EN_ALM_SVLINK_CFGB   ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "B�׼���SV�����쳣",          "ALM_SVLINK_CFGB"},
	{EN_ALM_SVLINK_NOCFGA ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "A�׼���SVδ����",           "ALM_SVLINK_NOCFGA"},
	{EN_ALM_SVLINK_NOCFGB ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "B�׼���SVδ����",           "ALM_SVLINK_NOCFGB"},
	{EN_ALM_SVLINK_TESTA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "A�׼���SV����",            "ALM_SVLINK_TESTA"},
	{EN_ALM_SVLINK_TESTB  ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "B�׼���SV����",            "ALM_SVLINK_TESTB"},
	{EN_ALM_KHDX          ,     EN_PARA_ENA_KHDX,      EN_PARA_T_KHDX,        0,         CN_T1S,     DB0,  CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ƻ�·����",              "ALM_KHDX"},
	{EN_ALM_XZBS          ,     EN_PARA_ENA_LNK,       EN_PARA_T_BS_CHK,      0,         CN_T1S,     DB0,  CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "ѡ�����״̬�쳣",            "ALM_XZBS"},
	{EN_ALM_XSWI          ,     EN_PARA_ENA_VQH,       EN_PARA_T_XSWI,        0,         CN_T1S,     DB0,  CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "��բλ���쳣",              "ALM_XSWI"},
	{EN_ALM_PTACT         ,     EN_PARA_ENA_VQH,       EN_PARA_T_VQH_ACT,     0,         CN_T1S,     DB0,  CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "PT�л�ͬʱ����",            "ALM_PTACT"},
	{EN_ALM_PTRET         ,     EN_PARA_ENA_VQH,       EN_PARA_T_VQH_RET,     0,         CN_T1S,     DB0,  CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "PT�л�ͬʱ����",            "ALM_PTRET"},
	{EN_ALM_OPBP1         ,     EN_PARA_ENA_OPB1,      EN_PARA_T_OPB1,        0,         CN_T1S,     DB0,  CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "������Դ��������ź�",     "ALM_OPBP1"},
	{EN_ALM_SGZ           ,     EN_PARA_ENA_SGZ,       EN_PARA_T_SGZ,         0,         CN_T1S,     0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "�¹���",                 "ALM_SGZ"},
	{EN_ALM_SXBYZ         ,     EN_PARA_SXBYZ_YX,      EN_PARA_T_SXBYZ,       0,         CN_T1S,     DB0,  CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���಻һ��",               "ALM_SXBYZ"},
	{EN_ALM_BSCH_OTH      ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "����һ�ײ�ִ�����غ�բ",    "ALM_BSCH_OTH"},
	{EN_ALM_BSCH          ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "�������ױ����غ�բ",           "ALM_BSCH"},
	
	{EN_ALM_BS_LINKQH     ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���������л�����",            "ALM_BS_LINKQH"},
	{EN_ALM_BS_VQH        ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "������ѹ�л�����",            "ALM_BS_VQH"},
	{EN_ALM_BS_DO         ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "��������",                "ALM_BS_DO"},
	{EN_ALM_GOOSE         ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         DB0,  CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOOSE�ܸ澯",            "ALM_GOOSE"},
	{EN_ALM_GOOSE_TEST    ,     CN_NULL_PINNO,         CN_NULL_PINNO,         0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOOSE���޲�һ��",          "ALM_GOOSE_TEST"},

	{EN_ALM_GOCB01_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB01�����쳣",    "ALM_GOCB01_DATA"},
	{EN_ALM_GOCB02_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB02�����쳣",    "ALM_GOCB02_DATA"},
	{EN_ALM_GOCB03_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB03�����쳣",    "ALM_GOCB03_DATA"},
	{EN_ALM_GOCB04_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB04�����쳣",    "ALM_GOCB04_DATA"},
	{EN_ALM_GOCB05_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB05�����쳣",    "ALM_GOCB05_DATA"},
	{EN_ALM_GOCB06_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB06�����쳣",    "ALM_GOCB06_DATA"},
	{EN_ALM_GOCB07_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB07�����쳣",    "ALM_GOCB07_DATA"},
	{EN_ALM_GOCB08_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB08�����쳣",    "ALM_GOCB08_DATA"},
	{EN_ALM_GOCB09_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB09�����쳣",    "ALM_GOCB09_DATA"},
	{EN_ALM_GOCB10_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB10�����쳣",    "ALM_GOCB10_DATA"},
	{EN_ALM_GOCB11_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB11�����쳣",    "ALM_GOCB11_DATA"},
	{EN_ALM_GOCB12_DATA  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    EN_MEA_GOCB_CFG,EN_MEA_GOCB_A,EN_MEA_GOCB_B,  "GOCB12�����쳣",    "ALM_GOCB12_DATA"},
	
	{EN_ALM_GOCB01_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB01���޲�һ��",    "ALM_GOCB01_TEST"},
	{EN_ALM_GOCB02_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB02���޲�һ��",    "ALM_GOCB02_TEST"},
	{EN_ALM_GOCB03_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB03���޲�һ��",    "ALM_GOCB03_TEST"},
	{EN_ALM_GOCB04_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB04���޲�һ��",    "ALM_GOCB04_TEST"},
	{EN_ALM_GOCB05_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB05���޲�һ��",    "ALM_GOCB05_TEST"},
	{EN_ALM_GOCB06_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB06���޲�һ��",    "ALM_GOCB06_TEST"},
	{EN_ALM_GOCB07_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB07���޲�һ��",    "ALM_GOCB07_TEST"},
	{EN_ALM_GOCB08_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB08���޲�һ��",    "ALM_GOCB08_TEST"},
	{EN_ALM_GOCB09_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB09���޲�һ��",    "ALM_GOCB09_TEST"},
	{EN_ALM_GOCB10_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB10���޲�һ��",    "ALM_GOCB10_TEST"},
	{EN_ALM_GOCB11_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB11���޲�һ��",    "ALM_GOCB11_TEST"},
	{EN_ALM_GOCB12_TEST  ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,         0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB12���޲�һ��",    "ALM_GOCB12_TEST"},
	{EN_ALM_GOCB01_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB01����籩",    "ALM_GOCB01_STORM"},
	{EN_ALM_GOCB02_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB02����籩",    "ALM_GOCB02_STORM"},
	{EN_ALM_GOCB03_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB03����籩",    "ALM_GOCB03_STORM"},
	{EN_ALM_GOCB04_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB04����籩",    "ALM_GOCB04_STORM"},
	{EN_ALM_GOCB05_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB05����籩",    "ALM_GOCB05_STORM"},
	{EN_ALM_GOCB06_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB06����籩",    "ALM_GOCB06_STORM"},
	{EN_ALM_GOCB07_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB07����籩",    "ALM_GOCB07_STORM"},
	{EN_ALM_GOCB08_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB08����籩",    "ALM_GOCB08_STORM"},
	{EN_ALM_GOCB09_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB09����籩",    "ALM_GOCB09_STORM"},
	{EN_ALM_GOCB10_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB10����籩",    "ALM_GOCB10_STORM"},
	{EN_ALM_GOCB11_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB11����籩",    "ALM_GOCB11_STORM"},
	{EN_ALM_GOCB12_STORM ,     CN_NULL_PINNO,         CN_NULL_PINNO,   CN_T1S,    CN_T1S,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOCB12����籩",    "ALM_GOCB12_STORM"},
	{EN_ALM_CCD_SVSUB    ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "SV���������쳣",        "ALM_CCD_SVSUB"},
	{EN_ALM_CCD_SVPUB    ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "SV���������쳣",        "ALM_CCD_SVPUB"},
	{EN_ALM_CCD_GOSUB    ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOOSE���������쳣",      "ALM_CCD_GOSUB"},
	{EN_ALM_CCD_GOPUB    ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOOSE���������쳣",      "ALM_CCD_GOPUB"},
	{EN_ALM_BOARD_CPU2   ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "CPU2�澯��",     "ALM_BOARD_CPU2"},
	{EN_ALM_BAK01        ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ø澯01",      "ALM_BAK01"},
	{EN_ALM_BAK02        ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ø澯02",      "ALM_BAK02"},
	{EN_ALM_BAK03        ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ø澯03",      "ALM_BAK03"},
	{EN_ALM_BAK04        ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ø澯04",      "ALM_BAK04"},
	{EN_ALM_BAK05        ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ø澯05",      "ALM_BAK05"},
	{EN_ALM_BAK06        ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ø澯06",      "ALM_BAK06"},
	{EN_ALM_BAK07        ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ø澯07",      "ALM_BAK07"},
	{EN_ALM_BAK08        ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ø澯08",      "ALM_BAK08"},
	{EN_ALM_BAK09        ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ø澯09",      "ALM_BAK09"},
	{EN_ALM_BAK10        ,     CN_NULL_PINNO,         CN_NULL_PINNO,          0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ø澯10",      "ALM_BAK10"},
};
const DWORD g_NUM_ALM = sizeof(g_tAlmTab) / sizeof(tagAlmTab);
//================================================================================
// �Լ쳣����
//  WORD            wIndex;            // ��¼ö��
//  DWORD           dwActCnt;          // Ĭ��ʱ�����
//  DWORD           dwRetCnt;          // Ĭ�Ϸ���ʱ�����
//  WORD            wCfg;              // ��������:NULL--������  DB0--װ�ù��ϡ������е�,DB1 װ���ܱ���
//  WORD            wValType1;         // �����¼��������1
//  WORD            wValType2;         // �����¼��������2
//  WORD            wValType3;         // �����¼��������3
//  INT8S           byName[CN_LEN_NAME];        // ��¼����
//  INT8S           byPinName[CN_LEN_NAME];     // ���������
//================================================================================
const tagChkTab g_tChkTab[ ] =
{
	{EN_CHK_CONST         ,       0          ,    0         ,    DB0+DB1,EN_MEA_DTYPE ,  EN_MEA_FLAG  ,EN_MEA_INDEX ,  "Ӧ�òೣ�����Լ�",             "CHK_CONST"},
	{EN_CHK_RAM_ERR       ,       0          ,    0         ,    DB0+DB1,EN_MEA_PTR   ,  EN_MEA_INDEX ,CN_NULL_PINNO,  "Ӧ�ò��ڴ����",              "CHK_RAM_ERR"},
	{EN_CHK_RAM_ALLOC     ,       0          ,    0         ,    DB0+DB1,CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "ƽ̨���ڴ������쳣",            "CHK_RAM_ALLOC"},
	{EN_CHK_RAM_CHK       ,       0          ,    0         ,    DB0+DB1,CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "ƽ̨���ڴ��Լ��쳣",            "CHK_RAM_CHK"},
	{EN_CHK_CCD_NO        ,       0          ,    0         ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CCD�ļ�������",             "CHK_CCD_NO"},
	{EN_CHK_CCD_ERR       ,       0          ,    0         ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CCD�ļ������쳣",             "CHK_CCD_ERR"},
	{EN_CHK_CCD_PARALOSE  ,       0          ,    0         ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CCD�ļ������ò���ȱʧ",          "CHK_CCD_PARALOSE"},
	{EN_CHK_CCD_PARAERR   ,       0          ,    0         ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CCD�ļ������ò�������",          "CHK_CCD_PARAERR"},
	{EN_CHK_CCD_CRC       ,       0          ,    0         ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CCD�ļ���CRCУ�������",        "CHK_CCD_CRC"},
	{EN_CHK_CCD_FRAME     ,       0          ,    0         ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CCD�ļ�������֡��Խ��",        "CHK_CCD_FRAME"},
	{EN_CHK_CCD_ADDRERR   ,       0          ,    0         ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CCD�ļ��ж̵�ַ���ô���",             "CHK_CCD_ADDRERR"},
	{EN_CHK_CCD_NUMERR    ,       0          ,    0         ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CCD�ļ��п��ƿ����Խ��",             "CHK_CCD_NUMERR"},
	{EN_CHK_CCD_CFGERR    ,       0          ,    0         ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CCD�ļ����������ô���",              "CHK_CCD_CFGERR"},
//	{EN_CHK_CCD_SVSUB     ,       0          ,    0         ,    DB0,    EN_MEA_FLAG,    CN_NULL_PINNO,CN_NULL_PINNO,  "CCD�ļ���SV���Ľ����쳣",            "CHK_CCD_SVSUB"},
//	{EN_CHK_CCD_SVPUB     ,       0          ,    0         ,    DB0,    EN_MEA_FLAG,    CN_NULL_PINNO,CN_NULL_PINNO,  "CCD�ļ���SV���������쳣",            "CHK_CCD_SVPUB"},
//	{EN_CHK_CCD_GOSUB     ,       0          ,    0         ,    DB0,    EN_MEA_FLAG,    CN_NULL_PINNO,CN_NULL_PINNO,  "CCD�ļ���GOOSE���Ľ����쳣",         "CHK_CCD_GOSUB"},
//	{EN_CHK_CCD_GOPUB     ,       0          ,    0         ,    DB0,    EN_MEA_FLAG,    CN_NULL_PINNO,CN_NULL_PINNO,  "CCD�ļ���GOOSE���������쳣",         "CHK_CCD_GOPUB"},
	{EN_CHK_DO1_RTN0      ,       4000       ,    4000      ,    DB0,    EN_MEA_INDEX,   CN_NULL_PINNO,CN_NULL_PINNO,  "������1�طַ�У�Լ�",          "CHK_DO1_RTN0"},
#if(CN_SOFT_VER_CPU==CN_SOFT_CPU_NANJING)
	{EN_CHK_DO2_RTN0      ,       4000       ,    4000      ,    0  ,    EN_MEA_INDEX,   CN_NULL_PINNO,CN_NULL_PINNO,  "������2�طַ�У�Լ�",          "CHK_DO2_RTN0"},
	{EN_CHK_DIO_RTN0      ,       4000       ,    4000      ,    0  ,    EN_MEA_INDEX,   CN_NULL_PINNO,CN_NULL_PINNO,  "���뿪����طַ�У�Լ�",          "CHK_DIO_RTN0"},
#else
	{EN_CHK_DO2_RTN0      ,       4000       ,    4000      ,    DB0,    EN_MEA_INDEX,   CN_NULL_PINNO,CN_NULL_PINNO,  "������2�طַ�У�Լ�",          "CHK_DO2_RTN0"},
	{EN_CHK_DIO_RTN0      ,       4000       ,    4000      ,    DB0,    EN_MEA_INDEX,   CN_NULL_PINNO,CN_NULL_PINNO,  "���뿪����طַ�У�Լ�",          "CHK_DIO_RTN0"},
#endif
	{EN_CHK_DO1_RTN1      ,       4000       ,    4000      ,    DB0,    EN_MEA_INDEX,   CN_NULL_PINNO,CN_NULL_PINNO,  "������1�غϷ�У�Լ�",          "CHK_DO1_RTN1"},
#if(CN_SOFT_VER_CPU==CN_SOFT_CPU_NANJING)
	{EN_CHK_DO2_RTN1      ,       4000       ,    4000      ,    0  ,    EN_MEA_INDEX,   CN_NULL_PINNO,CN_NULL_PINNO,  "������2�غϷ�У�Լ�",          "CHK_DO2_RTN1"},
	{EN_CHK_DIO_RTN1      ,       4000       ,    4000      ,    0  ,    EN_MEA_INDEX,   CN_NULL_PINNO,CN_NULL_PINNO,  "���뿪����غϷ�У�Լ�",          "CHK_DIO_RTN1"},
#else
	{EN_CHK_DO2_RTN1      ,       4000       ,    4000      ,    DB0,    EN_MEA_INDEX,   CN_NULL_PINNO,CN_NULL_PINNO,  "������2�غϷ�У�Լ�",          "CHK_DO2_RTN1"},
	{EN_CHK_DIO_RTN1      ,       4000       ,    4000      ,    DB0,    EN_MEA_INDEX,   CN_NULL_PINNO,CN_NULL_PINNO,  "���뿪����غϷ�У�Լ�",          "CHK_DIO_RTN1"},
#endif
//	{EN_CHK_BOARD_DO1_CHN1,       10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "������1ͨ��1�Լ�",            "CHK_BOARD_DO1_CHN1"},
//	{EN_CHK_BOARD_DO2_CHN1,       10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "������2ͨ��1�Լ�",            "CHK_BOARD_DO2_CHN1"},
//	{EN_CHK_BOARD_DIO_CHN1,       10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "���뿪����ͨ��1�Լ�",           "CHK_BOARD_DIO_CHN1"},
//	{EN_CHK_BOARD_DO1_CHN2,       10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "������1ͨ��2�Լ�",            "CHK_BOARD_DO1_CHN2"},
//	{EN_CHK_BOARD_DO2_CHN2,       10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "������2ͨ��2�Լ�",            "CHK_BOARD_DO2_CHN2"},
//	{EN_CHK_BOARD_DIO_CHN2,       10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "���뿪����ͨ��2�Լ�",           "CHK_BOARD_DIO_CHN2"},
//	{EN_CHK_BOARD_DO1_POW24,      10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "������1��Դ24V�Լ�",            "CHK_BOARD_DO1_POW24"},
//	{EN_CHK_BOARD_DO2_POW24,      10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "������2��Դ24V�Լ�",            "CHK_BOARD_DO2_POW24"},
//	{EN_CHK_BOARD_DIO_POW24,      10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "���뿪�����Դ24V�Լ�",           "CHK_BOARD_DIO_POW24"},
	{EN_CHK_BOARD_DO1_POW30,      5000       ,    500       ,    0  ,    EN_MEA_FLAG16,  CN_NULL_PINNO,CN_NULL_PINNO,  "������1��Դ30V�Լ�",            "CHK_BOARD_DO1_POW30"},
	{EN_CHK_BOARD_DO2_POW30,      5000       ,    500       ,    0  ,    EN_MEA_FLAG16,  CN_NULL_PINNO,CN_NULL_PINNO,  "������2��Դ30V�Լ�",            "CHK_BOARD_DO2_POW30"},
	{EN_CHK_BOARD_DIO_POW30,      5000       ,    500       ,    0  ,    EN_MEA_FLAG16,  CN_NULL_PINNO,CN_NULL_PINNO,  "���뿪�����Դ30V�Լ�",           "CHK_BOARD_DIO_POW30"},
//	{EN_CHK_BOARD_DO1_PARA ,      10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "������1�����Լ�",               "CHK_BOARD_DO1_PARA"},
//	{EN_CHK_BOARD_DO2_PARA ,      10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "������2�����Լ�",               "CHK_BOARD_DO2_PARA"},
//	{EN_CHK_BOARD_DIO_PARA ,      10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "���뿪��������Լ�",              "CHK_BOARD_DIO_PARA"},
	{EN_CHK_PARA_DI       ,       10000      ,    1000      ,    DB0,    EN_MEA_FLAG ,   CN_NULL_PINNO,CN_NULL_PINNO,  "�����������Լ�",             "CHK_PARA_DI"},
	{EN_CHK_PARA_DC       ,       10000      ,    1000      ,    DB0,    EN_MEA_FLAG ,   CN_NULL_PINNO,CN_NULL_PINNO,  "ֱ���������Լ�",             "CHK_PARA_DC"},
	{EN_CHK_PARA_SAM      ,       10000      ,    1000      ,    DB0,    EN_MEA_FLAG ,   CN_NULL_PINNO,CN_NULL_PINNO,  "ģ���������Լ�",             "CHK_PARA_SAM"},
	{EN_CHK_PARA_FUN      ,       10000      ,    1000      ,    DB0,    EN_MEA_FLAG ,   CN_NULL_PINNO,CN_NULL_PINNO,  "���ܲ����Լ�",              "CHK_PARA_FUN"},
	{EN_CHK_PARA_DC_COE   ,       10000      ,    1000      ,    DB0,    EN_MEA_FLAG ,   CN_NULL_PINNO,CN_NULL_PINNO,  "ֱ����У׼ϵ���Լ�",           "CHK_PARA_DC_COE"},
	{EN_CHK_PARA_AM_COE   ,       10000      ,    1000      ,    DB0,    EN_MEA_FLAG ,   CN_NULL_PINNO,CN_NULL_PINNO,  "ģ����У׼ϵ���Լ�",           "CHK_PARA_AM_COE"},
	{EN_CHK_PARA_DCBC_COE ,       10000      ,    1000      ,    DB0,    EN_MEA_FLAG ,   CN_NULL_PINNO,CN_NULL_PINNO,  "ģ����ֱ�������Լ�",           "CHK_PARA_DCBC_COE"},
	{EN_CHK_PARA_ANG_COE  ,       10000      ,    1000      ,    DB0,    EN_MEA_FLAG ,   CN_NULL_PINNO,CN_NULL_PINNO,  "ģ������λ�����Լ�",           "CHK_PARA_ANG_COE"},
	{EN_CHK_PARA_DI_HLD   ,       0          ,    0         ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "ȥ��ʱ�����ô����Լ�",          "CHK_PARA_DI_HLD"},
	{EN_CHK_BOARD_DI1     ,       5000       ,    500       ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "�����1�Լ�",              "CHK_BOARD_DI1"},
	{EN_CHK_BOARD_DI2     ,       5000       ,    500       ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "�����2�Լ�",              "CHK_BOARD_DI2"},
#if(CN_SOFT_VER_CPU==CN_SOFT_CPU_NANJING)
	{EN_CHK_BOARD_DI3     ,       5000       ,    500       ,    0  ,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "�����3�Լ�",              "CHK_BOARD_DI3"},
	{EN_CHK_BOARD_DIO_DI  ,       5000       ,    500       ,    0  ,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "���뿪���忪���Լ�",           "CHK_BOARD_DIO_DI"},
#else
	{EN_CHK_BOARD_DI3     ,       5000       ,    500       ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "�����3�Լ�",              "CHK_BOARD_DI3"},
	{EN_CHK_BOARD_DIO_DI  ,       5000       ,    500       ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "���뿪���忪���Լ�",           "CHK_BOARD_DIO_DI"},
#endif
    {EN_CHK_BOARD_OPB1    ,       5000       ,    500       ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "������·���Լ�",             "CHK_BOARD_OPB1"},
	{EN_CHK_BOARD_DO1     ,       5000       ,    500       ,    DB0,    EN_MEA_FLAG16,  CN_NULL_PINNO,CN_NULL_PINNO,  "������1�Լ�",              "CHK_BOARD_DO1"},
#if(CN_SOFT_VER_CPU==CN_SOFT_CPU_NANJING)
	{EN_CHK_BOARD_DO2     ,       5000       ,    500       ,    0  ,    EN_MEA_FLAG16,  CN_NULL_PINNO,CN_NULL_PINNO,  "������2�Լ�",              "CHK_BOARD_DO2"},
	{EN_CHK_BOARD_DIO_DO  ,       5000       ,    500       ,    0  ,    EN_MEA_FLAG16,  CN_NULL_PINNO,CN_NULL_PINNO,  "���뿪���忪���Լ�",           "CHK_BOARD_DIO_DO"},
	{EN_CHK_BOARD_DC_SAM  ,       400        ,    100       ,    0  ,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "ֱ�����Լ�",                "CHK_BOARD_DC_SAM"},
#else
	{EN_CHK_BOARD_DO2     ,       5000       ,    500       ,    DB0,    EN_MEA_FLAG16,  CN_NULL_PINNO,CN_NULL_PINNO,  "������2�Լ�",              "CHK_BOARD_DO2"},
	{EN_CHK_BOARD_DIO_DO  ,       5000       ,    500       ,    DB0,    EN_MEA_FLAG16,  CN_NULL_PINNO,CN_NULL_PINNO,  "���뿪���忪���Լ�",           "CHK_BOARD_DIO_DO"},
	{EN_CHK_BOARD_DC_SAM  ,       400        ,    100       ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "ֱ�����Լ�",                "CHK_BOARD_DC_SAM"},
#endif
	{EN_CHK_BOARD_DC_DEV  ,       400        ,    100       ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "״̬�����Լ�",               "CHK_BOARD_DC_DEV"},
	{EN_CHK_BOARD_DC_OPT1_1,      400        ,    100       ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CPU1��⹦��֡�Լ�",          "CHK_BOARD_DC_OPT1_1"},
	{EN_CHK_BOARD_DC_OPT1_2,      400        ,    100       ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CPU1����⹦��֡�Լ�",         "CHK_BOARD_DC_OPT1_2"},
	{EN_CHK_BOARD_DC_OPT2 ,       400        ,    100       ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CPU2��⹦��֡�Լ�",          "CHK_BOARD_DC_OPT2"},
	{EN_CHK_BOARD_PTCT1   ,       40000      ,    4000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "PTCT��1�Լ�",             "CHK_BOARD_PTCT1"},
	{EN_CHK_BOARD_PTCT2   ,       40000      ,    4000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "PTCT��2�Լ�",             "CHK_BOARD_PTCT2"},
	{EN_CHK_BOARD_CPU     ,       40000      ,    4000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CPU��AD�Լ�",             "CHK_BOARD_CPU"},
	{EN_CHK_BOARD_CPU_AUX ,       10         ,    10        ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CPU�����Լ�",              "CHK_BOARD_CPU_AUX"},
	{EN_CHK_BOARD_POW     ,       40000      ,    4000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "��Դ������ӳ��ڴ���",           "CHK_BOARD_POW"},
	{EN_CHK_BOARD_CPU2    ,       0          ,    0         ,    0  ,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "CPU2���Լ���",             "CHK_BOARD_CPU2"},
	{EN_CHK_BOARD_LED     ,       10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "LED���Լ�",               "CHK_BOARD_LED"},
	{EN_CHK_FRAME_ANA     ,       10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "ģ����֡�Լ�",               "CHK_FRAME_ANA"},
#if(CN_SOFT_VER_CPU==CN_SOFT_CPU_NANJING)
	{EN_CHK_CPUCOM_FAST   ,       10000      ,    1000      ,    0  ,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "˫CPUͨ���Լ�",             "CHK_CPUCOM_SLOW"},
	{EN_CHK_CPUCOM_PARA   ,       4          ,    4         ,    0  ,    EN_MEA_FLAG16,  CN_NULL_PINNO,CN_NULL_PINNO,  "˫CPU����CRC��һ��",         "CHK_CPUCOM_PARA"},
	{EN_CHK_CPUCOM_VER    ,       0          ,    0         ,    0  ,    EN_MEA_FLAG16,  EN_MEA_FLAG16,CN_NULL_PINNO,  "˫CPU�汾��Ϣ��һ��",          "CHK_CPUCOM_VER"},
	{EN_CHK_CPUCOM_CCD    ,       0          ,    0         ,    0  ,    EN_MEA_FLAG  ,  EN_MEA_FLAG  ,CN_NULL_PINNO,  "˫CPU����CRC��һ��",         "CHK_CPUCOM_CCD"},
#else
	{EN_CHK_CPUCOM_FAST   ,       10000      ,    1000      ,    DB0,    CN_NULL_PINNO,  CN_NULL_PINNO,CN_NULL_PINNO,  "˫CPUͨ���Լ�",             "CHK_CPUCOM_SLOW"},
	{EN_CHK_CPUCOM_PARA   ,       4          ,    4         ,    DB0,    EN_MEA_FLAG16,  CN_NULL_PINNO,CN_NULL_PINNO,  "˫CPU����CRC��һ��",         "CHK_CPUCOM_PARA"},
	{EN_CHK_CPUCOM_VER    ,       0          ,    0         ,    DB0,    EN_MEA_FLAG16,  EN_MEA_FLAG16,CN_NULL_PINNO,  "˫CPU�汾��Ϣ��һ��",          "CHK_CPUCOM_VER"},
	{EN_CHK_CPUCOM_CCD    ,       0          ,    0         ,    DB0,    EN_MEA_FLAG  ,  EN_MEA_FLAG  ,CN_NULL_PINNO,  "˫CPU����CRC��һ��",         "CHK_CPUCOM_CCD"},
#endif
	
	{EN_CHK_BAK01         ,        0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "�����Լ�01",      "CHK_BAK01"},
	{EN_CHK_BAK02         ,        0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "�����Լ�02",      "CHK_BAK02"},
	{EN_CHK_BAK03         ,        0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "�����Լ�03",      "CHK_BAK03"},
	{EN_CHK_BAK04         ,        0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "�����Լ�04",      "CHK_BAK04"},
	{EN_CHK_BAK05         ,        0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "�����Լ�05",      "CHK_BAK05"},
	{EN_CHK_BAK06         ,        0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "�����Լ�06",      "CHK_BAK06"},
	{EN_CHK_BAK07         ,        0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "�����Լ�07",      "CHK_BAK07"},
	{EN_CHK_BAK08         ,        0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "�����Լ�08",      "CHK_BAK08"},
	{EN_CHK_BAK09         ,        0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "�����Լ�09",      "CHK_BAK09"},
	{EN_CHK_BAK10         ,        0,          0,    0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "�����Լ�10",      "CHK_BAK10"},
};
const DWORD g_NUM_CHK = sizeof(g_tChkTab) / sizeof(tagChkTab);
//================================================================================
// ���г�����
//	WORD			wIndex; 			   // ��¼ö��
//	WORD			wCfg;				   // ��������
//	INT8S			byName[CN_LEN_NAME];   // ��¼����
//	INT8S			byPinName[CN_LEN_NAME];// ���������
//================================================================================
const tagRunTab g_tRunTab[ ] =
{
	{EN_RUN_POW_ON      ,  0,    "װ���ϵ�"   ,              "RUN_POW_ON"},
	{EN_RUN_POW_OFF     ,  0,    "װ�õ���",                 "RUN_POW_OFF"},
	{EN_RUN_SVPUB_ENA   ,  0,    "SV����ʹ��",               "RUN_SVPUB_ENA"},
	{EN_RUN_GOPUB_ENA   ,  0,    "GOOSE����ʹ��",            "RUN_GOPUB_ENA"},
	{EN_RUN_SVPUB_BS    ,  0,    "SV��������",               "RUN_SVPUB_BS"},
	{EN_RUN_GOPUB_BS    ,  0,    "GOOSE��������",            "RUN_GOPUB_BS"},
	{EN_RUN_POL         ,  0,    "�����޸��·�",               "RUN_POL"},
	{EN_RUN_LNKQH_S     ,  0,    "�����л��·�",               "RUN_LNKQH_S"},
	{EN_RUN_VQH_S       ,  0,    "��ѹ�л��·�",               "RUN_VQH_S"},
	{EN_RUN_UX_S        ,  0,    "�ߵ�ѹ�����·�",             "RUN_UX_S"},
	{EN_RUN_COM_S       ,  0,    "������������·�",           "RUN_COM_S"},
	{EN_RUN_AM_COE_S    ,  0,    "ģ����У׼ϵ���·�",      "RUN_AM_COE_S"},
	{EN_RUN_DCBC_COE_S  ,  0,    "ģ����ֱ�������·�",      "RUN_DCBC_COE_S"},
	{EN_RUN_ANG_COE_S   ,  0,    "ģ������λ�����·�",      "RUN_ANG_COE_S"},
	
	{EN_RUN_PARASYN_S_STR+EN_BOARD_PARA_DI    ,  0,    "����������ͬ���ɹ�",             "RUN_PARASYN_DI_S"},
	{EN_RUN_PARASYN_S_STR+EN_BOARD_PARA_DC    ,  0,    "ֱ��������ͬ���ɹ�",             "RUN_PARASYN_DC_S"},
	{EN_RUN_PARASYN_S_STR+EN_BOARD_PARA_SAM   ,  0,    "ģ��������ͬ���ɹ�",             "RUN_PARASYN_SAM_S"},
	{EN_RUN_PARASYN_S_STR+EN_BOARD_PARA_FUN   ,  0,    "���ܲ���ͬ���ɹ�",              "RUN_PARASYN_FUN_S"},
	{EN_RUN_PARASYN_S_STR+EN_BOARD_PARA_DC_COE,  0,    "ֱ��У׼ϵ��ͬ���ɹ�",            "RUN_PARASYN_DC_COE_S"},
	
	{EN_RUN_PARASYN_F_STR+EN_BOARD_PARA_DI    ,  0,    "����������ͬ��ʧ��",             "RUN_PARASYN_DI_F"},
	{EN_RUN_PARASYN_F_STR+EN_BOARD_PARA_DC    ,  0,    "ֱ��������ͬ��ʧ��",             "RUN_PARASYN_DC_F"},
	{EN_RUN_PARASYN_F_STR+EN_BOARD_PARA_SAM   ,  0,    "ģ��������ͬ��ʧ��",             "RUN_PARASYN_SAM_F"},
	{EN_RUN_PARASYN_F_STR+EN_BOARD_PARA_FUN   ,  0,    "���ܲ���ͬ��ʧ��",              "RUN_PARASYN_FUN_F"},
	{EN_RUN_PARASYN_F_STR+EN_BOARD_PARA_DC_COE,  0,    "ֱ��У׼ϵ��ͬ��ʧ��",            "RUN_PARASYN_DC_COE_F"},

	{EN_RUN_BAK01           ,  0,    "��������01",            "RUN_BAK01"},
	{EN_RUN_BAK02           ,  0,    "��������02",            "RUN_BAK02"},
	{EN_RUN_BAK03           ,  0,    "��������03",            "RUN_BAK03"},
	{EN_RUN_BAK04           ,  0,    "��������04",            "RUN_BAK04"},
	{EN_RUN_BAK05           ,  0,    "��������05",            "RUN_BAK05"},
	{EN_RUN_BAK06           ,  0,    "��������06",            "RUN_BAK06"},
	{EN_RUN_BAK07           ,  0,    "��������07",            "RUN_BAK07"},
	{EN_RUN_BAK08           ,  0,    "��������08",            "RUN_BAK08"},
	{EN_RUN_BAK09           ,  0,    "��������09",            "RUN_BAK09"},
	{EN_RUN_BAK10           ,  0,    "��������10",            "RUN_BAK10"},
};
const DWORD g_NUM_RUN = sizeof(g_tRunTab) / sizeof(tagRunTab);

//================================================================================
// ����������
//  WORD            wIndex;                // ��¼ö��
//  WORD            wCfg;                  // ��������
//  WORD            wValType1;             // �����¼��������1
//  WORD            wValType2;             // �����¼��������2
//  WORD            wValType3;             // �����¼��������3
//  INT8S           byName[CN_LEN_NAME];   // ��¼����
//  INT8S           byPinName[CN_LEN_NAME];// ���������
//================================================================================
const tagOptTab g_tOptTab[ ] =
{
	{EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_DI       ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "�����������޸ĳɹ�"          ,        "OPT_PARA_DI_W_SUCC"    },
	{EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_DC       ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "ֱ���������޸ĳɹ�"          ,        "OPT_PARA_DC_W_SUCC"    },
	{EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_SAM      ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "�����������޸ĳɹ�"          ,        "OPT_PARA_ANA_W_SUCC"   },
	{EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_FUN      ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ܲ����޸ĳɹ�"           ,        "OPT_PARA_FUN_W_SUCC"   },
	{EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_DC_COE   ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "ֱ����У׼ϵ���޸ĳɹ�",                "OPT_PARA_DCCOE_W_SUCC"  },
	{EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_AM_COE   ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "������У׼ϵ���޸ĳɹ�"      ,          "OPT_PARA_AMCOE_W_SUCC"  },
	{EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_DCBC_COE ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "������ֱ�������޸ĳɹ�",                "OPT_PARA_DCBCCOE_W_SUCC"  },
	{EN_OPT_PARA_W_SUCC_STR+EN_BOARD_PARA_ANG_COE  ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "��������λ�����޸ĳɹ�",                "OPT_PARA_ANGCOE_W_SUCC"  },

	{EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_DI       ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "�����������޸�ʧ��"          ,        "OPT_PARA_DI_W_FAIL"    },
	{EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_DC       ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "ֱ���������޸�ʧ��"          ,        "OPT_PARA_DC_W_FAIL"    },
	{EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_SAM      ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "�����������޸�ʧ��"          ,        "OPT_PARA_ANA_W_FAIL"   },
	{EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_FUN      ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ܲ����޸�ʧ��"           ,        "OPT_PARA_FUN_W_FAIL"   },
	{EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_DC_COE   ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "ֱ����У׼ϵ���޸�ʧ��",                "OPT_PARA_DCCOE_W_FAIL"  },
	{EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_AM_COE   ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "������У׼ϵ���޸�ʧ��"      ,          "OPT_PARA_AMCOE_W_FAIL"  },
	{EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_DCBC_COE ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "������ֱ�������޸�ʧ��",                "OPT_PARA_DCBCCOE_W_FAIL"  },
	{EN_OPT_PARA_W_FAIL_STR+EN_BOARD_PARA_ANG_COE  ,  0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "��������λ�����޸�ʧ��",                "OPT_PARA_ANGCOE_W_FAIL"  },
	
	{EN_OPT_PARA_INIT_SUCC_STR+EN_BOARD_PARA_DI       , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "������������ʼ���ɹ�"        ,         "OPT_PARA_DI_INIT_SUCC" },
	{EN_OPT_PARA_INIT_SUCC_STR+EN_BOARD_PARA_DC       , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "ֱ����������ʼ���ɹ�"        ,         "OPT_PARA_DC_INIT_SUCC" },
	{EN_OPT_PARA_INIT_SUCC_STR+EN_BOARD_PARA_SAM      , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "������������ʼ���ɹ�"        ,         "OPT_PARA_ANA_INIT_SUCC"},
	{EN_OPT_PARA_INIT_SUCC_STR+EN_BOARD_PARA_FUN      , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ܲ�����ʼ���ɹ�"          ,        "OPT_PARA_FUN_INIT_SUCC"},
	{EN_OPT_PARA_INIT_SUCC_STR+EN_BOARD_PARA_DC_COE   , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "ֱ����У׼ϵ����ʼ���ɹ�"  ,             "OPT_PARA_DCCOE_INIT_SUCC"},
	{EN_OPT_PARA_INIT_SUCC_STR+EN_BOARD_PARA_AM_COE   , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "������У׼ϵ����ʼ���ɹ�"    ,           "OPT_PARA_AMCOE_INIT_SUCC"},
	{EN_OPT_PARA_INIT_SUCC_STR+EN_BOARD_PARA_DCBC_COE , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "������ֱ��������ʼ���ɹ�"  ,             "OPT_PARA_DCBCCOE_INIT_SUCC"},
	{EN_OPT_PARA_INIT_SUCC_STR+EN_BOARD_PARA_ANG_COE  , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "��������λ������ʼ���ɹ�"  ,             "OPT_PARA_ANGCOE_INIT_SUCC"},
	{EN_OPT_PARA_INIT_FAIL_STR+EN_BOARD_PARA_DI       , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "������������ʼ��ʧ��"        ,         "OPT_PARA_DI_INIT_FAIL" },
	{EN_OPT_PARA_INIT_FAIL_STR+EN_BOARD_PARA_DC       , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "ֱ����������ʼ��ʧ��"        ,         "OPT_PARA_DC_INIT_FAIL" },
	{EN_OPT_PARA_INIT_FAIL_STR+EN_BOARD_PARA_SAM      , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "������������ʼ��ʧ��"        ,         "OPT_PARA_ANA_INIT_FAIL"},
	{EN_OPT_PARA_INIT_FAIL_STR+EN_BOARD_PARA_FUN      , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ܲ�����ʼ��ʧ��"          ,        "OPT_PARA_FUN_INIT_FAIL"},
	{EN_OPT_PARA_INIT_FAIL_STR+EN_BOARD_PARA_DC_COE   , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "ֱ����У׼ϵ����ʼ��ʧ��"  ,             "OPT_PARA_DCCOE_INIT_FAIL"},
	{EN_OPT_PARA_INIT_FAIL_STR+EN_BOARD_PARA_AM_COE   , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "������У׼ϵ����ʼ��ʧ��"    ,           "OPT_PARA_AMCOE_INIT_FAIL"},
	{EN_OPT_PARA_INIT_FAIL_STR+EN_BOARD_PARA_DCBC_COE , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "������ֱ��������ʼ��ʧ��"  ,             "OPT_PARA_DCBCCOE_INIT_FAIL"},
	{EN_OPT_PARA_INIT_FAIL_STR+EN_BOARD_PARA_ANG_COE  , 0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "��������λ������ʼ��ʧ��",               "OPT_PARA_ANGCOE_INIT_FAIL"},

	{EN_OPT_ADJ_DCBC_SUCC     ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "������ֱ������У׼�ɹ�",                "OPT_ADJ_DCBC_SUCC"    },
	{EN_OPT_ADJ_DCBC_FAIL     ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "������ֱ������У׼ʧ��",                "OPT_ADJ_DCBC_FAIL"    },
	{EN_OPT_ADJ_AM_SUCC       ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "��������ֵϵ��У׼�ɹ�"    ,            "OPT_ADJ_AM_SUCC"      },
	{EN_OPT_ADJ_AM_FAIL       ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "��������ֵϵ��У׼ʧ��"    ,            "OPT_ADJ_AM_FAIL"      },
	{EN_OPT_ADJ_ANG_SUCC      ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "��������λ����У׼�ɹ�"    ,            "OPT_ADJ_ANG_SUCC"     },
	{EN_OPT_ADJ_ANG_FAIL      ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "��������λ����У׼ʧ��"    ,            "OPT_ADJ_ANG_FAIL"     },
	{EN_OPT_ADJ_DC_SUCC       ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "ֱ����ϵ��У׼�ɹ�"          ,        "OPT_ADJ_DC_SUCC"       },
	{EN_OPT_ADJ_DC_FAIL       ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "ֱ����ϵ��У׼ʧ��"          ,        "OPT_ADJ_DC_FAIL"       },
	{EN_OPT_DEBUG_IN          ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "װ�õ���̬����"               ,     "OPT_DEBUG_IN"           },
	{EN_OPT_DEBUG_OUT         ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "װ�õ���̬�˳�"               ,     "OPT_DEBUG_OUT"          },

	{EN_OPT_FACT_DEBUG_IN     ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ҵ���̬����"               ,     "OPT_FACT_DEBUG_IN"      },
	{EN_OPT_FACT_DEBUG_OUT    ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ҵ���̬�˳�"               ,     "OPT_FACT_DEBUG_OUT"     },

	{EN_OPT_DEBUG_LED         ,      0,    EN_MEA_INDEX,  CN_NULL_PINNO,  CN_NULL_PINNO,  "ָʾ�Ƶ���"                 ,     "OPT_DEBUG_LED"          },
	{EN_OPT_DEBUG_DO          ,      0,    EN_MEA_INDEX ,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ڴ�������"                ,     "OPT_DEBUG_DO"           },

	{EN_OPT_DEBUG_GO_S        ,      0,    EN_MEA_INDEX ,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOOSE������ڵ���"           ,     "OPT_DEBUG_GO_S"         },
	{EN_OPT_DEBUG_GO_Dp       ,      0,    EN_MEA_INDEX ,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOOSE˫����ڵ���"           ,     "OPT_DEBUG_GO_Dp"         },
	{EN_OPT_DEBUG_GO_DC       ,      0,    EN_MEA_INDEX ,  CN_NULL_PINNO,  CN_NULL_PINNO,  "GOOSEģ��������"            ,     "OPT_DEBUG_GO_DC"        },

	{EN_OPT_ACT_DEl           ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���GOOSE��������"      ,          "OPT_ACT_DEl"},
	{EN_OPT_ALM_DEl           ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "����澯����"        ,             "OPT_ALM_DEl"},
	{EN_OPT_CHK_DEl           ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "����Լ�����"        ,             "OPT_CHK_DEl"},
	{EN_OPT_DI_SOE_DEl        ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���Ӳ����SOE����"    ,             "OPT_DI_SOE_DEl"},
	{EN_OPT_DO_SOE_DEl        ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���Ӳ����SOE����"    ,             "OPT_DO_SOE_DEl"},
	{EN_OPT_GOIN_SOE_DEl      ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���GOOSE����SOE����" ,           "OPT_GOIN_SOE_DEl"},
	{EN_OPT_GOOUT_SOE_DEl     ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���GOOSE����SOE����" ,           "OPT_GOOUT_SOE_DEl"},
	{EN_OPT_LED_SOE_DEl       ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ָʾ��SOE����" ,               "OPT_LED_SOE_DEl"},
	{EN_OPT_DPI_SOE_DEl       ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���˫��ң��SOE����" ,               "OPT_DPI_SOE_DEl"},
	{EN_OPT_FLAG_SOE_DEl      ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "�����ң��SOE����"   ,               "OPT_FLAG_SOE_DEl"},
	{EN_OPT_TIME_W_SUCC       ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "ʱ���޸ĳɹ�"        ,             "OPT_TIME_W_SUCC"},
	{EN_OPT_TIME_W_FAIL       ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "ʱ���޸�ʧ��"        ,             "OPT_TIME_W_FAIL"},

	{EN_OPT_BAK01             ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ò���01"        ,             "OPT_BAK01"},
	{EN_OPT_BAK02             ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ò���02"        ,             "OPT_BAK02"},
	{EN_OPT_BAK03             ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ò���03"        ,             "OPT_BAK03"},
	{EN_OPT_BAK04             ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ò���04"        ,             "OPT_BAK04"},
	{EN_OPT_BAK05             ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ò���05"        ,             "OPT_BAK05"},
	{EN_OPT_BAK06             ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ò���06"        ,             "OPT_BAK06"},
	{EN_OPT_BAK07             ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ò���07"        ,             "OPT_BAK07"},
	{EN_OPT_BAK08             ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ò���08"        ,             "OPT_BAK08"},
	{EN_OPT_BAK09             ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ò���09"        ,             "OPT_BAK09"},
	{EN_OPT_BAK10             ,      0,    CN_NULL_PINNO,  CN_NULL_PINNO,  CN_NULL_PINNO,  "���ò���10"        ,             "OPT_BAK10"},
};
const DWORD g_NUM_OPT = sizeof(g_tOptTab) / sizeof(tagOptTab);
//================================================================================
// �ڲ��������
//  WORD            wIndex;                // ��¼ö��
//  WORD            wCfg;                  // ��������
//  INT8S           byName[CN_LEN_NAME];   // ��¼����
//  INT8S           byPinName[CN_LEN_NAME];// ���������
//================================================================================
const tagPrvtSoeTab g_tPrvtSoeTab[ ] =
{
	{EN_PRVT_SOE_BAK0          ,      0,    "�ڲ������"           ,     "PRVT_SOE_BAK0"},
};
const DWORD g_NUM_PRVT_SOE = sizeof(g_tPrvtSoeTab) / sizeof(tagPrvtSoeTab);
//================================================================================
// �ڲ�����������
//  WORD            wIndex;                // ��¼ö��
//  WORD            wCfg;                  // ��������
//  INT8S           byName[CN_LEN_NAME];   // ��¼����
//  INT8S           byPinName[CN_LEN_NAME];// ���������
//================================================================================
const tagPrvtOptTab g_tPrvtOptTab[ ] =
{
	{EN_PRVT_OPT_DEV_LINK          ,      0,    "���Թ������ӳɹ�"           ,     "PRVT_OPT_DEV_LINK"     },
	{EN_PRVT_OPT_DEV_BREAK         ,      0,    "���Թ��������ж�"           ,     "PRVT_OPT_DEV_BREAK"    },
	{EN_PRVT_OPT_DATA_R_SUCC       ,      0,    "�ٻ����ݳɹ�"             ,     "PRVT_OPT_DATA_R_SUCC"  },
	{EN_PRVT_OPT_DATA_R_FAIL       ,      0,    "�ٻ�����ʧ��"             ,     "PRVT_OPT_DATA_R_FAIL"  },
	{EN_PRVT_OPT_FILE_UP_SUCC      ,      0,    "�ļ��ϴ��ɹ�"             ,     "PRVT_OPT_FILE_UP_SUCC" },
	{EN_PRVT_OPT_FILE_UP_FAIL      ,      0,    "�ļ��ϴ�ʧ��"             ,     "PRVT_OPT_FILE_UP_FAIL"},
	{EN_PRVT_OPT_FILE_DN_SUCC      ,      0,    "�ļ����سɹ�"             ,     "PRVT_OPT_FILE_DN_SUCC"},
	{EN_PRVT_OPT_FILE_DN_FAIL      ,      0,    "�ļ�����ʧ��"             ,     "PRVT_OPT_FILE_DN_FAIL"},
	{EN_PRVT_OPT_FLASH_BAK_SUCC    ,      0,    "һ�����ݳɹ�"             ,     "PRVT_OPT_FLASH_BAK_SUCC"},
	{EN_PRVT_OPT_FLASH_BAK_FAIL    ,      0,    "һ������ʧ��"             ,     "PRVT_OPT_FLASH_BAK_FAIL"},
	{EN_PRVT_OPT_PARA_REST_SUCC    ,      0,    "������ԭ�ɹ�"             ,     "PRVT_OPT_PARA_REST_SUCC"},
	{EN_PRVT_OPT_PARA_REST_FAIL    ,      0,    "������ԭʧ��"             ,     "PRVT_OPT_PARA_REST_FAIL"},
	{EN_PRVT_OPT_UPDATE_BOOT0_SUCC ,      0,    "BOOT0�����ɹ�"          ,     "PRVT_OPT_UPDATE_BOOT0_SUCC"},
	{EN_PRVT_OPT_UPDATE_BOOT0_FAIL ,      0,    "BOOT0����ʧ��"          ,     "PRVT_OPT_UPDATE_BOOT0_FAIL"},
	{EN_PRVT_OPT_UPDATE_UBOOT_SUCC ,      0,    "UBOOT�����ɹ�"          ,     "PRVT_OPT_UPDATE_UBOOT_SUCC"},
	{EN_PRVT_OPT_UPDATE_UBOOT_FAIL ,      0,    "UBOOT����ʧ��"          ,     "PRVT_OPT_UPDATE_UBOOT_FAIL"},
	{EN_PRVT_OPT_UPDATE_SYSTEM_SUCC,      0,    "SYSTEM�����ɹ�"         ,     "PRVT_OPT_UPDATE_SYSTEM_SUCC"},
	{EN_PRVT_OPT_UPDATE_SYSTEM_FAIL,      0,    "SYSTEM����ʧ��"         ,     "PRVT_OPT_UPDATE_SYSTEM_FAIL"},
	{EN_PRVT_OPT_UPDATE_FPGA1_SUCC ,      0,    "FPGA1�����ɹ�"          ,     "PRVT_OPT_UPDATE_FPGA1_SUCC"},
	{EN_PRVT_OPT_UPDATE_FPGA1_FAIL ,      0,    "FPGA1����ʧ��"          ,     "PRVT_OPT_UPDATE_FPGA1_FAIL"},
	{EN_PRVT_OPT_UPDATE_FPGA2_SUCC ,      0,    "FPGA2�����ɹ�"          ,     "PRVT_OPT_UPDATE_FPGA2_SUCC"},
	{EN_PRVT_OPT_UPDATE_FPGA2_FAIL ,      0,    "FPGA2����ʧ��"          ,     "PRVT_OPT_UPDATE_FPGA2_FAIL"},
	{EN_PRVT_OPT_EVENT_ALL_DEl     ,      0,    "�����������"          ,        "PRVT_OPT_EVENT_ALL_DEl"      },
	{EN_PRVT_OPT_RUN_DEl           ,      0,    "�����������"          ,        "PRVT_OPT_RUN_DEl"},
	{EN_PRVT_OPT_OPT_DEl           ,      0,    "�����������"          ,        "PRVT_OPT_OPT_DEl"},
	{EN_PRVT_OPT_PRVT_SOE_DEl      ,      0,    "����ڲ�����"          ,        "PRVT_OPT_PRVT_SOE_DEl"},
	{EN_PRVT_OPT_PRVT_OPT_DEl      ,      0,    "����ڲ�����"          ,        "PRVT_OPT_PRVT_OPT_DEl"},
	{EN_PRVT_OPT_ETH_W_SUCC        ,      0,    "��������޸ĳɹ�"        ,        "PRVT_OPT_ETH_W_SUCC"},
	{EN_PRVT_OPT_ETH_W_FAIL        ,      0,    "��������޸�ʧ��"        ,        "PRVT_OPT_ETH_W_FAIL"},
};
const DWORD g_NUM_PRVT_OPT = sizeof(g_tPrvtOptTab) / sizeof(tagPrvtOptTab);


