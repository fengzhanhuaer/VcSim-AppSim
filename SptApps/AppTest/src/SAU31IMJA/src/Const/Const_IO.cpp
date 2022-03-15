#include "Const_Pub.h"

/*================================================================================*/
//1. Ӳ���뵥�㿪�볣����
/*================================================================================
    WORD            wIndex;                         // Ӳ����ö��
    WORD            wCfg;                           // Ӳ����������������
    INT8S           byName[CN_LEN_NAME];            // Ӳ����������
    INT8S           byPinName[CN_LEN_NAME];         // Ӳ�������̵�ַ����
*================================================================================*/
const tagDiTab  g_tDiTab[] =
// ����������
{
/*=============================*/
// DWORD1.�����1
/*=============================*/
	// wIndex               wCfg byName               byPinName
	{EN_DI_TEST,            0,  "����״̬",           "DI_TEST"},
	{EN_DI_RESET,           0,  "�źŸ���",           "DI_RESET"},
	{EN_DI_XCBR_OPN,        0,  "��·����λ",         "DI_XCBR_OPN"},
	{EN_DI_XCBR_CLS,        0,  "��·����λ",         "DI_XCBR_CLS"},
	{EN_DI_XSWI01_OPN,      0,  "��բ1��λ",          "DI_XSWI01_OPN"},
	{EN_DI_XSWI01_CLS,      0,  "��բ1��λ",          "DI_XSWI01_CLS"},
	{EN_DI_XSWI02_OPN,      0,  "��բ2��λ",          "DI_XSWI02_OPN"},
	{EN_DI_XSWI02_CLS,      0,  "��բ2��λ",          "DI_XSWI02_CLS"},
	{EN_DI_XSWI03_OPN,      0,  "��բ3��λ",          "DI_XSWI03_OPN"},
	{EN_DI_XSWI03_CLS,      0,  "��բ3��λ",          "DI_XSWI03_CLS"},
	{EN_DI_XSWI04_OPN,      0,  "��բ4��λ",          "DI_XSWI04_OPN"},
	{EN_DI_XSWI04_CLS,      0,  "��բ4��λ",          "DI_XSWI04_CLS"},
	{EN_DI_XSWI05_OPN,      0,  "��բ5��λ",          "DI_XSWI05_OPN"},
	{EN_DI_XSWI05_CLS,      0,  "��բ5��λ",          "DI_XSWI05_CLS"},
	{EN_DI_XSWI06_OPN,      0,  "��բ6��λ",          "DI_XSWI06_OPN"},
	{EN_DI_XSWI06_CLS,      0,  "��բ6��λ",          "DI_XSWI06_CLS"},
	{EN_DI_XSWI07_OPN,      0,  "��բ7��λ",          "DI_XSWI07_OPN"},
	{EN_DI_XSWI07_CLS,      0,  "��բ7��λ",          "DI_XSWI07_CLS"},
	{EN_DI_XSWI08_OPN,      0,  "��բ8��λ",          "DI_XSWI08_OPN"},
	{EN_DI_XSWI08_CLS,      0,  "��բ8��λ",          "DI_XSWI08_CLS"},
	{EN_DI_BC_YLD,          0,  "ѹ���ͱ���",         "DI_BC_YLD"  },
	{EN_DI_BC_OTH,          0,  "��һ�ױ����ź�",     "DI_BC_OTH"  },
	{EN_DI_TJF,             0,  "TJF��բ�ź�",        "DI_TJF"  },
	{EN_DI_STJ,             0,  "����",               "DI_STJ"  },
	{EN_DI_SHJ,             0,  "�ֺ�",               "DI_SHJ"  },
	{EN_DI_KKJ,             0,  "�Ϻ�",               "DI_KKJ"  },
	{EN_DI_LNK_A,           0,  "ȡA��",              "DI_LNK_A"  },
	{EN_DI_LNK_B,           0,  "ȡB��",              "DI_LNK_B"  },
	{EN_DI_LNK_AUTO,        0,  "�Զ�",               "DI_LNK_AUTO"},
	{EN_DI_SHJ_SYN,         0,  "�ֺ�ͬ�ڿ���",        "DI_SHJ_SYN"},
	{EN_DI_POW1,            0,  "�����1��Դ����",     "DI_POW1"},
/*=============================*/
// DWORD2.�����2
/*=============================*/
	// wIndex              wCfg byName                       byPinName
	{EN_DI_OTH_ALM,         0,  "��һ�ײ�ִ�����쳣", "DI_OTH_ALM"      },
	{EN_DI_OTH_CHK,         0,  "��һ�ײ�ִ����","DI_OTH_CHK"},
	{EN_DI_YX_BAK01,        0,  "���ÿ���01",     "DI_YX_BAK01"},
	{EN_DI_YX_BAK02,        0,  "���ÿ���02",     "DI_YX_BAK02"},
	{EN_DI_YX_BAK03,        0,  "���ÿ���03",     "DI_YX_BAK03"},
	{EN_DI_YX_BAK04,        0,  "���ÿ���04",     "DI_YX_BAK04"},
	{EN_DI_YX_BAK05,        0,  "���ÿ���05",     "DI_YX_BAK05"},
	{EN_DI_YX_BAK06,        0,  "���ÿ���06",     "DI_YX_BAK06"},
	{EN_DI_YX_BAK07,        0,  "���ÿ���07",     "DI_YX_BAK07"},
	{EN_DI_YX_BAK08,        0,  "���ÿ���08",     "DI_YX_BAK08"},
	{EN_DI_YX_BAK09,        0,  "���ÿ���09",     "DI_YX_BAK09"},
	{EN_DI_YX_BAK10,        0,  "���ÿ���10",     "DI_YX_BAK10"},
	{EN_DI_YX_BAK11,        0,  "���ÿ���11",     "DI_YX_BAK11"},
	{EN_DI_YX_BAK12,        0,  "���ÿ���12",     "DI_YX_BAK12"},
	{EN_DI_YX_BAK13,        0,  "���ÿ���13",     "DI_YX_BAK13"},
	{EN_DI_YX_BAK14,        0,  "���ÿ���14",     "DI_YX_BAK14"},
	{EN_DI_YX_BAK15,        0,  "���ÿ���15",     "DI_YX_BAK15"},
	{EN_DI_YX_BAK16,        0,  "���ÿ���16",     "DI_YX_BAK16"},
	{EN_DI_YX_BAK17,        0,  "���ÿ���17",     "DI_YX_BAK17"},
	{EN_DI_YX_BAK18,        0,  "���ÿ���18",     "DI_YX_BAK18"},
	{EN_DI_YX_BAK19,        0,  "���ÿ���19",     "DI_YX_BAK19"},
	{EN_DI_YX_BAK20,        0,  "���ÿ���20",     "DI_YX_BAK20"},
	{EN_DI_YX_BAK21,        0,  "���ÿ���21",     "DI_YX_BAK21"},
	{EN_DI_YX_BAK22,        0,  "���ÿ���22",     "DI_YX_BAK22"},
	{EN_DI_YX_BAK23,        0,  "���ÿ���23",     "DI_YX_BAK23"},
	{EN_DI_YX_BAK24,        0,  "���ÿ���24",     "DI_YX_BAK24"},
	{EN_DI_YX_BAK25,        0,  "���ÿ���25",     "DI_YX_BAK25"},
	{EN_DI_YX_BAK26,        0,  "���ÿ���26",     "DI_YX_BAK26"},
	{EN_DI_YX_BAK27,        0,  "���ÿ���27",     "DI_YX_BAK27"},
	{EN_DI_YX_BAK28,        0,  "���ÿ���28",     "DI_YX_BAK28"},
	{EN_DI_POW2,            0,  "�����2��Դ����","DI_POW2"},
/*=============================*/
// DWORD3.�����3
/*=============================*/
	// wIndex              wCfg byName        byPinName
	{EN_DI_YX_BAK29,        0,  "���ÿ���29",     "DI_YX_BAK29"},
	{EN_DI_YX_BAK30,        0,  "���ÿ���30",     "DI_YX_BAK30"},
	{EN_DI_YX_BAK31,        0,  "���ÿ���31",     "DI_YX_BAK31"},
	{EN_DI_YX_BAK32,        0,  "���ÿ���32",     "DI_YX_BAK32"},
	{EN_DI_YX_BAK33,        0,  "���ÿ���33",     "DI_YX_BAK33"},
	{EN_DI_YX_BAK34,        0,  "���ÿ���34",     "DI_YX_BAK34"},
	{EN_DI_YX_BAK35,        0,  "���ÿ���35",     "DI_YX_BAK35"},
	{EN_DI_YX_BAK36,        0,  "���ÿ���36",     "DI_YX_BAK36"},
	{EN_DI_YX_BAK37,        0,  "���ÿ���37",     "DI_YX_BAK37"},
	{EN_DI_YX_BAK38,        0,  "���ÿ���38",     "DI_YX_BAK38"},
	{EN_DI_YX_BAK39,        0,  "���ÿ���39",     "DI_YX_BAK39"},
	{EN_DI_YX_BAK40,        0,  "���ÿ���40",     "DI_YX_BAK40"},
	{EN_DI_YX_BAK41,        0,  "���ÿ���41",     "DI_YX_BAK41"},
	{EN_DI_YX_BAK42,        0,  "���ÿ���42",     "DI_YX_BAK42"},
	{EN_DI_YX_BAK43,        0,  "���ÿ���43",     "DI_YX_BAK43"},
	{EN_DI_YX_BAK44,        0,  "���ÿ���44",     "DI_YX_BAK44"},
	{EN_DI_YX_BAK45,        0,  "���ÿ���45",     "DI_YX_BAK45"},
	{EN_DI_YX_BAK46,        0,  "���ÿ���46",     "DI_YX_BAK46"},
	{EN_DI_YX_BAK47,        0,  "���ÿ���47",     "DI_YX_BAK47"},
	{EN_DI_YX_BAK48,        0,  "���ÿ���48",     "DI_YX_BAK48"},
	{EN_DI_YX_BAK49,        0,  "���ÿ���49",     "DI_YX_BAK49"},
	{EN_DI_YX_BAK50,        0,  "���ÿ���50",     "DI_YX_BAK50"},
	{EN_DI_YX_BAK51,        0,  "���ÿ���51",     "DI_YX_BAK51"},
	{EN_DI_YX_BAK52,        0,  "���ÿ���52",     "DI_YX_BAK52"},
	{EN_DI_YX_BAK53,        0,  "���ÿ���53",     "DI_YX_BAK53"},
	{EN_DI_YX_BAK54,        0,  "���ÿ���54",     "DI_YX_BAK54"},
	{EN_DI_YX_BAK55,        0,  "���ÿ���55",     "DI_YX_BAK55"},
	{EN_DI_YX_BAK56,        0,  "���ÿ���56",     "DI_YX_BAK56"},
	{EN_DI_YX_BAK57,        0,  "���ÿ���57",     "DI_YX_BAK57"},
	{EN_DI_YX_BAK58,        0,  "���ÿ���58",     "DI_YX_BAK58"},
	{EN_DI_POW3,            0,  "�����3��Դ����","DI_POW3"},
/*=============================*/
// DWORD4.�����4
/*=============================*/
	// wIndex             wCfg  byName        byPinName
	{EN_DI_YX_BAK59,        0,  "���ÿ���59",     "DI_YX_BAK59"},
	{EN_DI_YX_BAK60,        0,  "���ÿ���60",     "DI_YX_BAK60"},
	{EN_DI_YX_BAK61,        0,  "���ÿ���61",     "DI_YX_BAK61"},
	{EN_DI_YX_BAK62,        0,  "���ÿ���62",     "DI_YX_BAK62"},
	{EN_DI_YX_BAK63,        0,  "���ÿ���63",     "DI_YX_BAK63"},
	{EN_DI_YX_BAK64,        0,  "���ÿ���64",     "DI_YX_BAK64"},
	{EN_DI_YX_BAK65,        0,  "���ÿ���65",     "DI_YX_BAK65"},
	{EN_DI_YX_BAK66,        0,  "���ÿ���66",     "DI_YX_BAK66"},
	{EN_DI_YX_BAK67,        0,  "���ÿ���67",     "DI_YX_BAK67"},
	{EN_DI_YX_BAK68,        0,  "���ÿ���68",     "DI_YX_BAK68"},
	{EN_DI_YX_BAK69,        0,  "���ÿ���69",     "DI_YX_BAK69"},
	{EN_DI_YX_BAK70,        0,  "���ÿ���70",     "DI_YX_BAK70"},
	{EN_DI_YX_BAK71,        0,  "���ÿ���71",     "DI_YX_BAK71"},
	{EN_DI_POW4,            0,  "���뿪�����Դ����","DI_POW4"},
//	{EN_DI_YX_BAK72,        0,  "���ÿ���72",     "DI_YX_BAK72"},
//	{EN_DI_YX_BAK73,        0,  "���ÿ���73",     "DI_YX_BAK73"},
//	{EN_DI_YX_BAK74,        0,  "���ÿ���74",     "DI_YX_BAK74"},
//	{EN_DI_YX_BAK75,        0,  "���ÿ���75",     "DI_YX_BAK75"},
//	{EN_DI_YX_BAK76,        0,  "���ÿ���76",     "DI_YX_BAK76"},
//	{EN_DI_YX_BAK77,        0,  "���ÿ���77",     "DI_YX_BAK77"},
//	{EN_DI_YX_BAK78,        0,  "���ÿ���78",     "DI_YX_BAK78"},
//	{EN_DI_YX_BAK79,        0,  "���ÿ���79",     "DI_YX_BAK79"},
//	{EN_DI_YX_BAK80,        0,  "���ÿ���80",     "DI_YX_BAK80"},
//	{EN_DI_YX_BAK81,        0,  "���ÿ���81",     "DI_YX_BAK81"},
//	{EN_DI_YX_BAK82,        0,  "���ÿ���82",     "DI_YX_BAK82"},
//	{EN_DI_YX_BAK83,        0,  "���ÿ���83",     "DI_YX_BAK83"},
//	{EN_DI_YX_BAK84,        0,  "���ÿ���84",     "DI_YX_BAK84"},
//	{EN_DI_YX_BAK85,        0,  "���ÿ���85",     "DI_YX_BAK85"},
//	{EN_DI_YX_BAK86,        0,  "���ÿ���86",     "DI_YX_BAK86"},
//	{EN_DI_YX_BAK87,        0,  "���ÿ���87",     "DI_YX_BAK87"},
//	{EN_DI_YX_BAK88,        0,  "���ÿ���88",     "DI_YX_BAK88"},
/*=============================*/
// DWORD5.������·���ڲ�
/*=============================*/
	{EN_DI_OPB1_HWJ,        0,  "��բ��·����",   "DI_OPB1_HWJ"},
	{EN_DI_OPB1_TWJ,        0,  "��բ��·����",   "DI_OPB1_TWJ"},
	{EN_DI_OPB1_POW,        0,  "������Դ����",   "DI_OPB1_POW"},
	{EN_DI_OPB1_KKJ,        0,  "KKJ",   "DI_OPB1_KKJ"},
	{EN_DI_OPB1_TJF,        0,  "TJF",   "DI_OPB1_TJF"},
	{EN_DI_OPB1_STJ,        0,  "STJ",   "DI_OPB1_STJ"},
	{EN_DI_OPB1_SHJ,        0,  "SHJ",   "DI_OPB1_SHJ"},

//	{EN_DI_OPB2_HWJ,        0,  "OPB2 ��բ��·����",   "DI_OPB2_HWJ"},
//	{EN_DI_OPB2_TWJ,        0,  "OPB2 ��բ��·����",   "DI_OPB2_TWJ"},
//	{EN_DI_OPB2_POW,        0,  "OPB2 ������Դ����",   "DI_OPB2_POW"},
//	{EN_DI_OPB2_KKJ,        0,  "OPB2 KKJ",   "DI_OPB2_KKJ"},
//	{EN_DI_OPB2_TJF,        0,  "OPB2 TJF",   "DI_OPB2_TJF"},
//	{EN_DI_OPB2_STJ,        0,  "OPB2 STJ",   "DI_OPB2_STJ"},
//	{EN_DI_OPB2_SHJ,        0,  "OPB2 SHJ",   "DI_OPB2_SHJ"},
/*=============================*/
// DWORD6.������1
/*=============================*/
	// wIndex             wCfg  byName               byPinName
	{EN_DI_DO_BHTZ ,        0,  "��բ���ڻز�",            "DI_DO_BHTZ"},
	{EN_DI_DO_BHHZ ,        0,  "��բ���ڻز�",            "DI_DO_BHHZ"},
	{EN_DI_DO_BZTTZ,        0,  "����Ͷ��բ���ڻز�",   "DI_DO_BZTTZ"},
	{EN_DI_DO_BZTHZ,        0,  "����Ͷ��բ���ڻز�",   "DI_DO_BZTHZ"},
	{EN_DI_DO_BAK1 ,        0,  "���ó���1�ز�",           "DI_DO_BAK1"},
	{EN_DI_DO_BAK2 ,        0,  "���ó���2�ز�",           "DI_DO_BAK2"},
	{EN_DI_DO_BAK3 ,        0,  "���ó���3�ز�",           "DI_DO_BAK3"},
	{EN_DI_DO_BAK4 ,        0,  "���ó���4�ز�",           "DI_DO_BAK4"},
	{EN_DI_DO_XCBR_OPN  ,   0,  "ң�ط�բ���ڻز�",            "DI_DO_XCBR_OPN"},
	{EN_DI_DO_XCBR_CLS  ,   0,  "ң�غ�բ���ڻز�",            "DI_DO_XCBR_CLS"},
	{EN_DI_DO_BSCH      ,   0,  "�����غ�բ���ڻز�",           "DI_DO_BSCH"},
	{EN_DI_DO_XCBR_JBS  ,   0,  "��·����������ڻز�",          "DI_DO_XCBR_JBS"},
	{EN_DI_DO_XSWI01_JBS,   0,  "��բ1��������ڻز�",          "DI_DO_XSWI01_JBS"},
	{EN_DI_DO_XSWI02_JBS,   0,  "��բ2��������ڻز�",          "DI_DO_XSWI02_JBS"},
	{EN_DI_DO_XSWI03_JBS,   0,  "��բ3��������ڻز�",          "DI_DO_XSWI03_JBS"},
	{EN_DI_DO_XSWI04_JBS,   0,  "��բ4��������ڻز�",          "DI_DO_XSWI04_JBS"},
/*=============================*/
// DWORD7.������2
/*=============================*/
	{EN_DI_DO_XSWI05_JBS,   0,  "��բ5��������ڻز�",          "DI_DO_XSWI05_JBS"},
	{EN_DI_DO_XSWI06_JBS,   0,  "��բ6��������ڻز�",          "DI_DO_XSWI06_JBS"},
	{EN_DI_DO_XSWI07_JBS,   0,  "��բ7��������ڻز�",          "DI_DO_XSWI07_JBS"},
	{EN_DI_DO_XSWI08_JBS,   0,  "��բ8��������ڻز�",          "DI_DO_XSWI08_JBS"},
	{EN_DI_DO_XSWI01_OPN,   0,  "��բ1��բ���ڻز�",           "DI_DO_XSWI01_OPN"},
	{EN_DI_DO_XSWI01_CLS,   0,  "��բ1��բ���ڻز�",           "DI_DO_XSWI01_CLS"},
	{EN_DI_DO_XSWI02_OPN,   0,  "��բ2��բ���ڻز�",           "DI_DO_XSWI02_OPN"},
	{EN_DI_DO_XSWI02_CLS,   0,  "��բ2��բ���ڻز�",           "DI_DO_XSWI02_CLS"},
	{EN_DI_DO_XSWI03_OPN,   0,  "��բ3��բ���ڻز�",           "DI_DO_XSWI03_OPN"},
	{EN_DI_DO_XSWI03_CLS,   0,  "��բ3��բ���ڻز�",           "DI_DO_XSWI03_CLS"},
	{EN_DI_DO_XSWI04_OPN,   0,  "��բ4��բ���ڻز�",           "DI_DO_XSWI04_OPN"},
	{EN_DI_DO_XSWI04_CLS,   0,  "��բ4��բ���ڻز�",           "DI_DO_XSWI04_CLS"},
	{EN_DI_DO_XSWI05_OPN,   0,  "��բ5��բ���ڻز�",           "DI_DO_XSWI05_OPN"},
	{EN_DI_DO_XSWI05_CLS,   0,  "��բ5��բ���ڻز�",           "DI_DO_XSWI05_CLS"},
	{EN_DI_DO_XSWI06_OPN,   0,  "��բ6��բ���ڻز�",           "DI_DO_XSWI06_OPN"},
	{EN_DI_DO_XSWI06_CLS,   0,  "��բ6��բ���ڻز�",           "DI_DO_XSWI06_CLS"},
/*=============================*/
// DWORD8.���뿪������ڷ�У
/*=============================*/
	{EN_DI_DO_XSWI07_OPN,   0,  "��բ7��բ���ڻز�",           "DI_DO_XSWI07_OPN"},
	{EN_DI_DO_XSWI07_CLS,   0,  "��բ7��բ���ڻز�",           "DI_DO_XSWI07_CLS"},
	{EN_DI_DO_XSWI08_OPN,   0,  "��բ8��բ���ڻز�",           "DI_DO_XSWI08_OPN"},
	{EN_DI_DO_XSWI08_CLS,   0,  "��բ8��բ���ڻز�",           "DI_DO_XSWI08_CLS"},
	{EN_DI_DO_YK_BAK1   ,   0,  "����ң��1���ڻز�",           "DI_DO_YK_BAK1"},
	{EN_DI_DO_YK_BAK2   ,   0,  "����ң��2���ڻز�",           "DI_DO_YK_BAK2"},
	{EN_DI_DO_BHBAK5    ,   0,  "���ó���5(����)�ز�",         "DI_DO_BHBAK5"},
};
const DWORD g_NUM_DI = sizeof(g_tDiTab) / sizeof(tagDiTab);
/*================================================================================*/
//2. Ӳ����˫��ϳɳ�����
/*================================================================================
    WORD            wIndex;                         // ˫�㿪��ö��
    WORD            wSrcType;                       // �����ź�Դ
    WORD            wSrcOpn;                        // ������λ�ź�
    WORD            wSrcCls;                        // ������λ�ź�
    WORD            wParaIndex;                     // ��������1
    WORD            wCfg;                           // ������������
    INT8S           byName[CN_LEN_NAME];            // ˫�㿪��������
    INT8S           byPinName[CN_LEN_NAME];         // ˫�㿪�����̵�ַ����
*================================================================================*/
const tagDpiTab  g_tDpiTab[] =
{
//	wIndex           wSrcType       wSrcOpn            wSrcCls            wParaIndex     wCfg             byName         byPinName
	//˫����Ϣ
	{EN_DPI_XCBR,     EN_DTYPE_DI,   EN_DI_XCBR_OPN,    EN_DI_XCBR_CLS,    CN_NULL_PINNO,  0,           "��·��λ��",       "DPI_XCBR"},
	{EN_DPI_XSWI01,   EN_DTYPE_DI,   EN_DI_XSWI01_OPN,  EN_DI_XSWI01_CLS,  CN_NULL_PINNO,  0,           "��բ1λ��",       "DPI_XSWI01"},
	{EN_DPI_XSWI02,   EN_DTYPE_DI,   EN_DI_XSWI02_OPN,  EN_DI_XSWI02_CLS,  CN_NULL_PINNO,  0,           "��բ2λ��",       "DPI_XSWI02"},
	{EN_DPI_XSWI03,   EN_DTYPE_DI,   EN_DI_XSWI03_OPN,  EN_DI_XSWI03_CLS,  CN_NULL_PINNO,  0,           "��բ3λ��",       "DPI_XSWI03"},
	{EN_DPI_XSWI04,   EN_DTYPE_DI,   EN_DI_XSWI04_OPN,  EN_DI_XSWI04_CLS,  CN_NULL_PINNO,  0,           "��բ4λ��",       "DPI_XSWI04"},
	{EN_DPI_XSWI05,   EN_DTYPE_DI,   EN_DI_XSWI05_OPN,  EN_DI_XSWI05_CLS,  CN_NULL_PINNO,  0,           "��բ5λ��",       "DPI_XSWI05"},
	{EN_DPI_XSWI06,   EN_DTYPE_DI,   EN_DI_XSWI06_OPN,  EN_DI_XSWI06_CLS,  CN_NULL_PINNO,  0,           "��բ6λ��",       "DPI_XSWI06"},
	{EN_DPI_XSWI07,   EN_DTYPE_DI,   EN_DI_XSWI07_OPN,  EN_DI_XSWI07_CLS,  CN_NULL_PINNO,  0,           "��բ7λ��",       "DPI_XSWI07"},
	{EN_DPI_XSWI08,   EN_DTYPE_DI,   EN_DI_XSWI08_OPN,  EN_DI_XSWI08_CLS,  CN_NULL_PINNO,  0,           "��բ8λ��",       "DPI_XSWI08"},
};
const DWORD g_NUM_DPI = sizeof(g_tDpiTab) / sizeof(tagDpiTab);
/*================================================================================*/
//3. GOOSE���ĳ�����
/*================================================================================
    WORD            wIndex;                         // GOOSE����ö�ٺ�
    WORD            wChnType;                       // �ź�����
    WORD            wParaIndex;                     // ��������
    WORD            wCfg;                           // GOOSE����������������
    INT8S           byName[CN_LEN_NAME];            // GOOSE��������
    INT8S           byPinName[CN_LEN_NAME];         // GOOSE����̵�ַ 
*================================================================================*/
const tagGoInTab  g_tGoInTab[] =
{
	{EN_GOIN_RESET   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "Զ������",     "GOIN_RESET" },
	{EN_GOIN_CKTZ    ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "�����բ",     "GOIN_CKTZ" },
	{EN_GOIN_CKHZ    ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "��غ�բ",     "GOIN_CKHZ" },
	{EN_GOIN_JBS_XCBR,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "��·�������",     "GOIN_JBS_XCBR" },
	{EN_GOIN_BZTTZ1  ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "����Ͷ��բ1",  "GOIN_BZTTZ1" },
	{EN_GOIN_BZTTZ2  ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "����Ͷ��բ2",  "GOIN_BZTTZ2" },
	{EN_GOIN_BZTHZ1  ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "����Ͷ��բ1",  "GOIN_BZTHZ1" },
	{EN_GOIN_BZTHZ2  ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "����Ͷ��բ2",  "GOIN_BZTHZ2" },
	{EN_GOIN_BHTZ1   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "������բ1",   "GOIN_BHTZ1" },
	{EN_GOIN_BHTZ2   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "������բ2",   "GOIN_BHTZ2" },
	{EN_GOIN_BHTZ3   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "������բ3",   "GOIN_BHTZ3" },
	{EN_GOIN_BHTZ4   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "������բ4",   "GOIN_BHTZ4" },
	{EN_GOIN_BHTZ5   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "������բ5",   "GOIN_BHTZ5" },
	{EN_GOIN_BHHZ1   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "�����غ�բ1", "GOIN_BHHZ1" },
	{EN_GOIN_BHHZ2   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "�����غ�բ2", "GOIN_BHHZ2" },
	{EN_GOIN_BHHZ3   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "�����غ�բ3", "GOIN_BHHZ3" },
	{EN_GOIN_BHHZ4   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "�����غ�բ4", "GOIN_BHHZ4" },
	{EN_GOIN_BHHZ5   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "�����غ�բ5", "GOIN_BHHZ5" },
	{EN_GOIN_BSHZ1   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "�����غ�բ1", "GOIN_BSHZ1" },
	{EN_GOIN_BSHZ2   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "�����غ�բ2", "GOIN_BSHZ2" },
	{EN_GOIN_BSHZ3   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "�����غ�բ3", "GOIN_BSHZ3" },
	{EN_GOIN_BSHZ4   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "�����غ�բ4", "GOIN_BSHZ4" },
	{EN_GOIN_BSHZ5   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "�����غ�բ5", "GOIN_BSHZ5" },
	{EN_GOIN_BHYT1   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "��������1",   "GOIN_BHYT1" },
	{EN_GOIN_BHYT2   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "��������2",   "GOIN_BHYT2" },
	{EN_GOIN_BHYT3   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "��������3",   "GOIN_BHYT3" },
	{EN_GOIN_BHYT4   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "��������4",   "GOIN_BHYT4" },
	{EN_GOIN_BHYT5   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "��������5",   "GOIN_BHYT5" },
	{EN_GOIN_BHYT6   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "��������6",   "GOIN_BHYT6" },
	{EN_GOIN_BHYT7   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "��������7",   "GOIN_BHYT7" },
	{EN_GOIN_BHYT8   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "��������8",   "GOIN_BHYT8" },
	{EN_GOIN_BHYT9   ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "��������9",   "GOIN_BHYT9" },
	{EN_GOIN_BHYT10  ,      EN_CTYPE_IO_S,     CN_NULL_PINNO,  0,      "��������10",  "GOIN_BHYT10" },
	//��բ 1~9 ��λ
	{EN_GOIN_CLS_XSWI01,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�ϵ�բ1",   "GOIN_CLS_XSWI01"},
	{EN_GOIN_OPN_XSWI01,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�ֵ�բ1",   "GOIN_OPN_XSWI01"},
	{EN_GOIN_JBS_XSWI01,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�����1",   "GOIN_JBS_XSWI01"},
	{EN_GOIN_CLS_XSWI02,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�ϵ�բ2",   "GOIN_CLS_XSWI02"},
	{EN_GOIN_OPN_XSWI02,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�ֵ�բ2",   "GOIN_OPN_XSWI02"},
	{EN_GOIN_JBS_XSWI02,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�����2",   "GOIN_JBS_XSWI02"},
	{EN_GOIN_CLS_XSWI03,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�ϵ�բ3",   "GOIN_CLS_XSWI03"},
	{EN_GOIN_OPN_XSWI03,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�ֵ�բ3",   "GOIN_OPN_XSWI03"},
	{EN_GOIN_JBS_XSWI03,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�����3",   "GOIN_JBS_XSWI03"},
	{EN_GOIN_CLS_XSWI04,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�ϵ�բ4",   "GOIN_CLS_XSWI04"},
	{EN_GOIN_OPN_XSWI04,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�ֵ�բ4",   "GOIN_OPN_XSWI04"},
	{EN_GOIN_JBS_XSWI04,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�����4",   "GOIN_JBS_XSWI04"},
	{EN_GOIN_CLS_XSWI05,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�ϵ�բ5",   "GOIN_CLS_XSWI05"},
	{EN_GOIN_OPN_XSWI05,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�ֵ�բ5",   "GOIN_OPN_XSWI05"},
	{EN_GOIN_JBS_XSWI05,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�����5",   "GOIN_JBS_XSWI05"},
	{EN_GOIN_CLS_XSWI06,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�ϵ�բ6",   "GOIN_CLS_XSWI06"},
	{EN_GOIN_OPN_XSWI06,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�ֵ�բ6",   "GOIN_OPN_XSWI06"},
	{EN_GOIN_JBS_XSWI06,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�����6",   "GOIN_JBS_XSWI06"},
	{EN_GOIN_CLS_XSWI07,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�ϵ�բ7",   "GOIN_CLS_XSWI07"},
	{EN_GOIN_OPN_XSWI07,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�ֵ�բ7",   "GOIN_OPN_XSWI07"},
	{EN_GOIN_JBS_XSWI07,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�����7",   "GOIN_JBS_XSWI07"},
	{EN_GOIN_CLS_XSWI08,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�ϵ�բ8",   "GOIN_CLS_XSWI08"},
	{EN_GOIN_OPN_XSWI08,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�ֵ�բ8",   "GOIN_OPN_XSWI08"},
	{EN_GOIN_JBS_XSWI08,     EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,      "�����8",   "GOIN_JBS_XSWI08"},
	{EN_GOIN_BAK_01,         EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,     "����ң��1",   "GOIN_BAK_01"},
	{EN_GOIN_BAK_02,         EN_CTYPE_IO_S,    CN_NULL_PINNO,  0,     "����ң��2",   "GOIN_BAK_02"},
	// ʱ��������� 
	{EN_GOIN_TIME_SYN,       EN_CTYPE_IO_T,    CN_NULL_PINNO,  0,     "ʱ���������","GOIN_TIME_SYN"},
};
const DWORD g_NUM_GOIN = sizeof(g_tGoInTab) / sizeof(tagGoInTab);

/*================================================================================*/
//4. ����������
/*================================================================================
    WORD            wIndex;                         // ������ö��
    BYTE            wSrcType;                       // �����ź�Դ
    BYTE            wSrcIndex;                      // �����ź�Դö��
    WORD            wParaIndex;                     // ��������1
    WORD            wRtnIndex;                      // ������Уң��
    WORD            wCfg;                           // ����������������
    INT8S           byName[CN_LEN_NAME];            // ����������
    INT8S           byPinName[CN_LEN_NAME];         // �������̵�ַ
*================================================================================*/
const tagDoTab  g_tDoTab[ ] =
{
	// wIndex      byNam  byPinName
// ���ڰ�1
	{EN_DO_BHTZ,            EN_DTYPE_FLAG,  EN_FLAG_BHTZ_DO   ,    CN_NULL_PINNO,  EN_DI_DO_BHTZ,        0,  "������բ���",    "DO_BHTZ"},
	{EN_DO_BHHZ,            EN_DTYPE_ACT,   EN_ACT_BHHZ       ,    CN_NULL_PINNO,  EN_DI_DO_BHHZ,        0,  "������բ���",    "DO_BHHZ"},
	{EN_DO_BZTTZ,           EN_DTYPE_ACT,   EN_ACT_BZTTZ      ,    CN_NULL_PINNO,  EN_DI_DO_BZTTZ,       0,  "����Ͷ��բ���",  "DO_BZTTZ"},
	{EN_DO_BZTHZ,           EN_DTYPE_ACT,   EN_ACT_BZTHZ      ,    CN_NULL_PINNO,  EN_DI_DO_BZTHZ,       0,  "����Ͷ��բ���",  "DO_BZTHZ"},
	{EN_DO_BHBAK1,          EN_DTYPE_FLAG,  EN_FLAG_DO_BHBAK1 ,    CN_NULL_PINNO,  EN_DI_DO_BAK1,        0,  "���ó���1",       "DO_BHBAK1"},
	{EN_DO_BHBAK2,          EN_DTYPE_FLAG,  EN_FLAG_DO_BHBAK2 ,    CN_NULL_PINNO,  EN_DI_DO_BAK2,        0,  "���ó���2",       "DO_BHBAK2"},
	{EN_DO_BHBAK3,          EN_DTYPE_FLAG,  EN_FLAG_DO_BHBAK3 ,    CN_NULL_PINNO,  EN_DI_DO_BAK3,        0,  "���ó���3",       "DO_BHBAK3"},
	{EN_DO_BHBAK4,          EN_DTYPE_FLAG,  EN_FLAG_DO_BHBAK4 ,    CN_NULL_PINNO,  EN_DI_DO_BAK4,        0,  "���ó���4 ",      "DO_BHBAK4"},
	{EN_DO_XCBR_OPN,        EN_DTYPE_GOIN,  EN_GOIN_CKTZ      ,    CN_NULL_PINNO,  EN_DI_DO_XCBR_OPN,    0,  "ң�ط�բ���",    "DO_XCBR_OPN"},
	{EN_DO_XCBR_CLS,        EN_DTYPE_GOIN,  EN_GOIN_CKHZ      ,    CN_NULL_PINNO,  EN_DI_DO_XCBR_CLS,    0,  "ң�غ�բ���",    "DO_XCBR_CLS"},
	{EN_DO_BSCH,            EN_DTYPE_ALM ,  EN_ALM_BSCH_OTH   ,    CN_NULL_PINNO,  EN_DI_DO_BSCH,        0,  "�����غ�բ���",   "DO_BSCH"},
	{EN_DO_XCBR_JBS,        EN_DTYPE_GOIN,  EN_GOIN_JBS_XCBR  ,    CN_NULL_PINNO,  EN_DI_DO_XCBR_JBS,    0,  "��·����������",  "DO_XCBR_JBS"},
	{EN_DO_XSWI01_JBS,      EN_DTYPE_GOIN,  EN_GOIN_JBS_XSWI01,    CN_NULL_PINNO,  EN_DI_DO_XSWI01_JBS,  0,  "��բ1��������", "DO_XSWI01_JBS"},
	{EN_DO_XSWI02_JBS,      EN_DTYPE_GOIN,  EN_GOIN_JBS_XSWI02,    CN_NULL_PINNO,  EN_DI_DO_XSWI02_JBS,  0,  "��բ2��������", "DO_XSWI02_JBS"},
	{EN_DO_XSWI03_JBS,      EN_DTYPE_GOIN,  EN_GOIN_JBS_XSWI03,    CN_NULL_PINNO,  EN_DI_DO_XSWI03_JBS,  0,  "��բ3��������", "DO_XSWI03_JBS"},
	{EN_DO_XSWI04_JBS,      EN_DTYPE_GOIN,  EN_GOIN_JBS_XSWI04,    CN_NULL_PINNO,  EN_DI_DO_XSWI04_JBS,  0,  "��բ4��������", "DO_XSWI04_JBS"},
// ���ڰ�2
	{EN_DO_XSWI05_JBS,      EN_DTYPE_GOIN,  EN_GOIN_JBS_XSWI05,    CN_NULL_PINNO,  EN_DI_DO_XSWI05_JBS,  0,  "��բ5��������", "DO_XSWI05_JBS"},
	{EN_DO_XSWI06_JBS,      EN_DTYPE_GOIN,  EN_GOIN_JBS_XSWI06,    CN_NULL_PINNO,  EN_DI_DO_XSWI06_JBS,  0,  "��բ6��������", "DO_XSWI06_JBS"},
	{EN_DO_XSWI07_JBS,      EN_DTYPE_GOIN,  EN_GOIN_JBS_XSWI07,    CN_NULL_PINNO,  EN_DI_DO_XSWI07_JBS,  0,  "��բ7��������", "DO_XSWI07_JBS"},
	{EN_DO_XSWI08_JBS,      EN_DTYPE_GOIN,  EN_GOIN_JBS_XSWI08,    CN_NULL_PINNO,  EN_DI_DO_XSWI08_JBS,  0,  "��բ8��������", "DO_XSWI08_JBS"},
	{EN_DO_XSWI01_OPN,      EN_DTYPE_GOIN,  EN_GOIN_OPN_XSWI01,    CN_NULL_PINNO,  EN_DI_DO_XSWI01_OPN,  0,  "��բ1��բ���",   "DO_XSWI01_OPN"},
	{EN_DO_XSWI01_CLS,      EN_DTYPE_GOIN,  EN_GOIN_CLS_XSWI01,    CN_NULL_PINNO,  EN_DI_DO_XSWI01_CLS,  0,  "��բ1��բ���",   "DO_XSWI01_CLS"},
	{EN_DO_XSWI02_OPN,      EN_DTYPE_GOIN,  EN_GOIN_OPN_XSWI02,    CN_NULL_PINNO,  EN_DI_DO_XSWI02_OPN,  0,  "��բ2��բ���",   "DO_XSWI02_OPN"},
	{EN_DO_XSWI02_CLS,      EN_DTYPE_GOIN,  EN_GOIN_CLS_XSWI02,    CN_NULL_PINNO,  EN_DI_DO_XSWI02_CLS,  0,  "��բ2��բ���",   "DO_XSWI02_CLS"},
	{EN_DO_XSWI03_OPN,      EN_DTYPE_GOIN,  EN_GOIN_OPN_XSWI03,    CN_NULL_PINNO,  EN_DI_DO_XSWI03_OPN,  0,  "��բ3��բ���",   "DO_XSWI03_OPN"},
	{EN_DO_XSWI03_CLS,      EN_DTYPE_GOIN,  EN_GOIN_CLS_XSWI03,    CN_NULL_PINNO,  EN_DI_DO_XSWI03_CLS,  0,  "��բ3��բ���",   "DO_XSWI03_CLS"},
	{EN_DO_XSWI04_OPN,      EN_DTYPE_GOIN,  EN_GOIN_OPN_XSWI04,    CN_NULL_PINNO,  EN_DI_DO_XSWI04_OPN,  0,  "��բ4��բ���",   "DO_XSWI04_OPN"},
	{EN_DO_XSWI04_CLS,      EN_DTYPE_GOIN,  EN_GOIN_CLS_XSWI04,    CN_NULL_PINNO,  EN_DI_DO_XSWI04_CLS,  0,  "��բ4��բ���",   "DO_XSWI04_CLS"},
	{EN_DO_XSWI05_OPN,      EN_DTYPE_GOIN,  EN_GOIN_OPN_XSWI05,    CN_NULL_PINNO,  EN_DI_DO_XSWI05_OPN,  0,  "��բ5��բ���",   "DO_XSWI05_OPN"},
	{EN_DO_XSWI05_CLS,      EN_DTYPE_GOIN,  EN_GOIN_CLS_XSWI05,    CN_NULL_PINNO,  EN_DI_DO_XSWI05_CLS,  0,  "��բ5��բ���",   "DO_XSWI05_CLS"},
	{EN_DO_XSWI06_OPN,      EN_DTYPE_GOIN,  EN_GOIN_OPN_XSWI06,    CN_NULL_PINNO,  EN_DI_DO_XSWI06_OPN,  0,  "��բ6��բ���",   "DO_XSWI06_OPN"},
	{EN_DO_XSWI06_CLS,      EN_DTYPE_GOIN,  EN_GOIN_CLS_XSWI06,    CN_NULL_PINNO,  EN_DI_DO_XSWI06_CLS,  0,  "��բ6��բ���",   "DO_XSWI06_CLS"},
// ���뿪����
	{EN_DO_XSWI07_OPN,      EN_DTYPE_GOIN,  EN_GOIN_OPN_XSWI07,    CN_NULL_PINNO,  EN_DI_DO_XSWI07_OPN,  0,  "��բ7��բ���",   "DO_XSWI07_OPN"},
	{EN_DO_XSWI07_CLS,      EN_DTYPE_GOIN,  EN_GOIN_CLS_XSWI07,    CN_NULL_PINNO,  EN_DI_DO_XSWI07_CLS,  0,  "��բ7��բ���",   "DO_XSWI07_CLS"},
	{EN_DO_XSWI08_OPN,      EN_DTYPE_GOIN,  EN_GOIN_OPN_XSWI08,    CN_NULL_PINNO,  EN_DI_DO_XSWI08_OPN,  0,  "��բ8��բ���",   "DO_XSWI08_OPN"},
	{EN_DO_XSWI08_CLS,      EN_DTYPE_GOIN,  EN_GOIN_CLS_XSWI08,    CN_NULL_PINNO,  EN_DI_DO_XSWI08_CLS,  0,  "��բ8��բ���",   "DO_XSWI08_CLS"},
	{EN_DO_YK_BAK1,         EN_DTYPE_GOIN,  EN_GOIN_BAK_01    ,    CN_NULL_PINNO,  EN_DI_DO_YK_BAK1,     0,  "����ң��1",       "DO_YK_BAK1"},
	{EN_DO_YK_BAK2,         EN_DTYPE_GOIN,  EN_GOIN_BAK_02    ,    CN_NULL_PINNO,  EN_DI_DO_YK_BAK2,     0,  "����ң��2",       "DO_YK_BAK2"},
	{EN_DO_BHBAK5,          EN_DTYPE_FLAG,  EN_FLAG_DO_BHBAK5_0,   CN_NULL_PINNO,  EN_DI_DO_BHBAK5,      0,  "���ó���5(����)",  "DO_BHBAK5"},
// ��Դ��
	{EN_DO_ALM,             EN_DTYPE_FLAG,  EN_FLAG_DO_ALM    ,    CN_NULL_PINNO,  CN_NULL_PINNO,        0,  "�����쳣",        "DO_ALM"},
	{EN_DO_CHK,             EN_DTYPE_FLAG,  EN_FLAG_DO_CHK    ,    CN_NULL_PINNO,  CN_NULL_PINNO,        0,  "װ�ù���",        "DO_CHK"},
};
const DWORD g_NUM_DO = sizeof(g_tDoTab) / sizeof(tagDoTab);
/*================================================================================*/
//5. GOOSE����������
/*================================================================================
    WORD            wIndex;                         // ˫�㿪��ö��
    WORD            wChnType;                       // ��������
    BYTE            wSrcType;                       // �����ź�Դ
    BYTE            wSrcIndex;                      // ������λ�ź�
    WORD            wParaIndex;                     // ��������
    WORD            wCfg;                           // ������������ NULL:����Ʒ��\����ʱ�� DB0:ʱ��ת��  DB1Ʒ��ת��
    INT8S           byName[CN_LEN_NAME];            // ˫�㿪��������
    INT8S           byPinName[CN_LEN_NAME];         // ˫�㿪�����̵�ַ����
================================================================================*/

const tagGoOutTab  g_tGoOutTab[ ] =
{
	{EN_GOOUT_CHK        ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG, EN_FLAG_DO_CHK     ,  CN_NULL_PINNO,  0,  "װ�ù���",   "GOOUT_CHK"},
	{EN_GOOUT_ALM        ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG, EN_FLAG_DO_ALM     ,  CN_NULL_PINNO,  0,  "�����쳣",   "GOOUT_ALM"},
	{EN_GOOUT_ALM_SYN    ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_SYN         ,  CN_NULL_PINNO,  0,  "ͬ���쳣",   "GOOUT_ALM_SYN"},
	{EN_GOOUT_ALM_KI     ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_DIPOW       ,  CN_NULL_PINNO,  0,  "����ʧ��",   "GOOUT_ALM_KI"},
	{EN_GOOUT_ALM_SV     ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_SV          ,  CN_NULL_PINNO,  0,  "SV�ܸ澯",   "GOOUT_ALM_SV"},
	{EN_GOOUT_ALM_GOOSE  ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOOSE       ,  CN_NULL_PINNO,  0,  "GOOSE�ܸ澯",      "GOOUT_ALM_GOOSE"},
	{EN_GOOUT_ALM_GOCB01 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB01_DATA ,  CN_NULL_PINNO,  0,  "GOOSE1�����쳣",   "GOOUT_ALM_GOCB01"},
	{EN_GOOUT_ALM_GOCB02 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB02_DATA ,  CN_NULL_PINNO,  0,  "GOOSE2�����쳣",   "GOOUT_ALM_GOCB02"},
	{EN_GOOUT_ALM_GOCB03 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB03_DATA ,  CN_NULL_PINNO,  0,  "GOOSE3�����쳣",   "GOOUT_ALM_GOCB03"},
	{EN_GOOUT_ALM_GOCB04 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB04_DATA ,  CN_NULL_PINNO,  0,  "GOOSE4�����쳣",   "GOOUT_ALM_GOCB04"},
	{EN_GOOUT_ALM_GOCB05 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB05_DATA ,  CN_NULL_PINNO,  0,  "GOOSE5�����쳣",   "GOOUT_ALM_GOCB05"},
	{EN_GOOUT_ALM_GOCB06 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB06_DATA ,  CN_NULL_PINNO,  0,  "GOOSE6�����쳣",   "GOOUT_ALM_GOCB06"},
	{EN_GOOUT_ALM_GOCB07 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB07_DATA ,  CN_NULL_PINNO,  0,  "GOOSE7�����쳣",   "GOOUT_ALM_GOCB07"},
	{EN_GOOUT_ALM_GOCB08 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB08_DATA ,  CN_NULL_PINNO,  0,  "GOOSE8�����쳣",   "GOOUT_ALM_GOCB08"},
	{EN_GOOUT_ALM_GOCB09 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB09_DATA ,  CN_NULL_PINNO,  0,  "GOOSE9�����쳣",   "GOOUT_ALM_GOCB09"},
	{EN_GOOUT_ALM_GOCB10 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB10_DATA ,  CN_NULL_PINNO,  0,  "GOOSE10�����쳣",   "GOOUT_ALM_GOCB10"},
	{EN_GOOUT_ALM_GOCB11 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB11_DATA ,  CN_NULL_PINNO,  0,  "GOOSE11�����쳣",   "GOOUT_ALM_GOCB11"},
	{EN_GOOUT_ALM_GOCB12 ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_GOCB12_DATA ,  CN_NULL_PINNO,  0,  "GOOSE12�����쳣",   "GOOUT_ALM_GOCB12"},
	{EN_GOOUT_ALM_GOCB13 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE13�����쳣",   "GOOUT_ALM_GOCB13"},
	{EN_GOOUT_ALM_GOCB14 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE14�����쳣",   "GOOUT_ALM_GOCB14"},
	{EN_GOOUT_ALM_GOCB15 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE15�����쳣",   "GOOUT_ALM_GOCB15"},
	{EN_GOOUT_ALM_GOCB16 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE16�����쳣",   "GOOUT_ALM_GOCB16"},
	{EN_GOOUT_ALM_GOCB17 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE17�����쳣",   "GOOUT_ALM_GOCB17"},
	{EN_GOOUT_ALM_GOCB18 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE18�����쳣",   "GOOUT_ALM_GOCB18"},
	{EN_GOOUT_ALM_GOCB19 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE19�����쳣",   "GOOUT_ALM_GOCB19"},
	{EN_GOOUT_ALM_GOCB20 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE20�����쳣",   "GOOUT_ALM_GOCB20"},
	{EN_GOOUT_ALM_GOCB21 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE21�����쳣",   "GOOUT_ALM_GOCB21"},
	{EN_GOOUT_ALM_GOCB22 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE22�����쳣",   "GOOUT_ALM_GOCB22"},
	{EN_GOOUT_ALM_GOCB23 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE23�����쳣",   "GOOUT_ALM_GOCB23"},
	{EN_GOOUT_ALM_GOCB24 ,   EN_CTYPE_IO_S,   CN_NULL_PINNO, CN_NULL_PINNO      ,  CN_NULL_PINNO,  0,  "GOOSE24�����쳣",   "GOOUT_ALM_GOCB24"},
	{EN_GOOUT_TEST_ERR   ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_TEST        ,  CN_NULL_PINNO,  0,  "���޲�һ��",        "GOOUT_TEST_ERR"},
	{EN_GOOUT_ALM_BSCH   ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_BSCH       ,  CN_NULL_PINNO,  0,  "�����غ�բ",         "GOOUT_ALM_BSCH"},
	{EN_GOOUT_FLAG_TJF   ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG, EN_FLAG_DI_TJF    ,  CN_NULL_PINNO,  0,  "����ֱ���ź�TJF",    "GOOUT_FLAG_TJF"},
	{EN_GOOUT_FLAG_KKJ   ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG, EN_FLAG_DI_KKJ    ,  CN_NULL_PINNO,  0,  "KKJ�Ϻ�",           "GOOUT_FLAG_KKJ"},
	{EN_GOOUT_FLAG_STJ   ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG, EN_FLAG_DI_STJ    ,  CN_NULL_PINNO,  0,  "STJ�ź�",           "GOOUT_FLAG_STJ"},
	{EN_GOOUT_FLAG_SHJ   ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG, EN_FLAG_DI_SHJ    ,  CN_NULL_PINNO,  0,  "SHJ�ź�",           "GOOUT_FLAG_SHJ"},
	{EN_GOOUT_ALM_KHDX   ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_KHDX       ,  CN_NULL_PINNO,  0,  "���ƻ�·����",       "GOOUT_ALM_KHDX"},
	{EN_GOOUT_ALM_XSWI   ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_XSWI       ,  CN_NULL_PINNO,  0,  "��բλ���쳣",       "GOOUT_ALM_XSWI"},
	{EN_GOOUT_ALM_VCHG   ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_XZBS       ,  CN_NULL_PINNO,  0,  "ѡ�����״̬�쳣",    "GOOUT_ALM_VCHG"},
	{EN_GOOUT_ALM_PTACT  ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_PTACT      ,  CN_NULL_PINNO,  0,  "PT�л�ͬʱ����",        "GOOUT_ALM_PTACT"},
	{EN_GOOUT_ALM_PTRET  ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_PTRET      ,  CN_NULL_PINNO,  0,  "PT�л�ͬʱ����",        "GOOUT_ALM_PTRET"},
	{EN_GOOUT_ALM_LNK    ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_SVSUB      ,  CN_NULL_PINNO,  0,  "SV���������쳣",       "GOOUT_ALM_LNK"},
	{EN_GOOUT_ALM_OPBP1  ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_OPBP1      ,  CN_NULL_PINNO,  0,  "������Դ��������ź�",   "GOOUT_ALM_OPBP1"},
	{EN_GOOUT_ALM_SGZ    ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM ,  EN_ALM_SGZ       ,  CN_NULL_PINNO,  0,  "�¹����ź�",         "GOOUT_ALM_SGZ"},
	{EN_GOOUT_ALM_SXBYZ  ,   EN_CTYPE_IO_S,   EN_DTYPE_ALM ,  EN_ALM_SXBYZ     ,  CN_NULL_PINNO,  0,  "���಻һ��",         "GOOUT_ALM_SXBYZ"},
	{EN_GOOUT_IN_BHTZ    ,   EN_CTYPE_IO_S,   EN_DTYPE_ACT ,  EN_ACT_BHTZ      ,  CN_NULL_PINNO,  0,  "�յ�������բ����",   "GOOUT_IN_BHTZ"},
	{EN_GOOUT_IN_BHYT    ,   EN_CTYPE_IO_S,   EN_DTYPE_ACT ,  EN_ACT_BHYT      ,  CN_NULL_PINNO,  0,  "�յ�������������",   "GOOUT_IN_BHYT"},
	{EN_GOOUT_IN_BHHZ    ,   EN_CTYPE_IO_S,   EN_DTYPE_ACT ,  EN_ACT_BHHZ      ,  CN_NULL_PINNO,  0,  "�յ�������������",   "GOOUT_IN_BHHZ"},
	{EN_GOOUT_IN_CKTZ    ,   EN_CTYPE_IO_S,   EN_DTYPE_GOIN,  EN_GOIN_CKTZ     ,  CN_NULL_PINNO,  0,  "�յ������բ����",   "GOOUT_IN_CKTZ"},
	{EN_GOOUT_IN_CKHZ    ,   EN_CTYPE_IO_S,   EN_DTYPE_GOIN,  EN_GOIN_CKHZ     ,  CN_NULL_PINNO,  0,  "�յ���غ�բ����",   "GOOUT_IN_CKHZ"},
	{EN_GOOUT_IN_BZTTZ   ,   EN_CTYPE_IO_S,   EN_DTYPE_ACT ,  EN_ACT_BZTTZ     ,  CN_NULL_PINNO,  0,  "�յ�����Ͷ��բ����", "GOOUT_IN_BZTTZ"},
	{EN_GOOUT_IN_BZTHZ   ,   EN_CTYPE_IO_S,   EN_DTYPE_ACT ,  EN_ACT_BZTHZ     ,  CN_NULL_PINNO,  0,  "�յ�����Ͷ��բ����", "GOOUT_IN_BZTHZ"},
	{EN_GOOUT_DO_BHTZ    ,   EN_CTYPE_IO_S,   EN_DTYPE_DI  ,  EN_DI_DO_BHTZ    ,  CN_NULL_PINNO,  0,  "��բ���ڻز�",       "GOOUT_DO_BHTZ"},
	{EN_GOOUT_DO_BHHZ    ,   EN_CTYPE_IO_S,   EN_DTYPE_DI  ,  EN_DI_DO_BHHZ    ,  CN_NULL_PINNO,  0,  "��բ���ڻز�",       "GOOUT_DO_BHHZ"},
	{EN_GOOUT_DO_BZTTZ   ,   EN_CTYPE_IO_S,   EN_DTYPE_DI  ,  EN_DI_DO_BZTTZ   ,  CN_NULL_PINNO,  0,  "����Ͷ��բ���ڻز�", "GOOUT_DO_BZTTZ"},
	{EN_GOOUT_DO_BZTHZ   ,   EN_CTYPE_IO_S,   EN_DTYPE_DI  ,  EN_DI_DO_BZTHZ   ,  CN_NULL_PINNO,  0,  "����Ͷ��բ���ڻز�", "GOOUT_DO_BZTHZ"},
	{EN_GOOUT_V_I        ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG,  EN_FLAG_V_I      ,  CN_NULL_PINNO,  0,  "ѹ��ȡ��ĸ",       "GOOUT_V_I"},
	{EN_GOOUT_V_II       ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG,  EN_FLAG_V_II     ,  CN_NULL_PINNO,  0,  "ѹ��ȡ��ĸ",       "GOOUT_V_II"},
	{EN_GOOUT_SV_A       ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG,  EN_FLAG_SV_A     ,  CN_NULL_PINNO,  0,  "A����������",      "GOOUT_SV_A"},
	{EN_GOOUT_SV_B       ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG,  EN_FLAG_SV_B     ,  CN_NULL_PINNO,  0,  "B����������",      "GOOUT_SV_B"},
	{EN_GOOUT_LNK_A      ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG,  EN_FLAG_LNK_A    ,  CN_NULL_PINNO,  0,  "����ȡA��",       "GOOUT_LNK_A"},
	{EN_GOOUT_LNK_B      ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG,  EN_FLAG_LNK_B    ,  CN_NULL_PINNO,  0,  "����ȡB��",       "GOOUT_LNK_B"},
	{EN_GOOUT_PARACHG    ,   EN_CTYPE_IO_S,   EN_DTYPE_FLAG,  EN_FLAG_PARACHG   , CN_NULL_PINNO,  0,  "�����仯�ź�",   "GOOUT_PARACHG"},

	{EN_GOOUT_TIME_RECV  ,   EN_CTYPE_IO_S,   EN_DTYPE_GOIN, EN_GOIN_TIME_SYN,     CN_NULL_PINNO,  0,  "����SOE",   "GOOUT_TIME_RECV"},
	{EN_GOOUT_TIME_SEND  ,   EN_CTYPE_IO_S,   EN_DTYPE_GOIN, EN_GOIN_TIME_SYN,     CN_NULL_PINNO,  0,  "����SOE",   "GOOUT_TIME_SEND"},
	{EN_GOOUT_TIME_SINGLE,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_TIME_SINGLE,   CN_NULL_PINNO,  0,  "��ʱ�ź�״̬",   "GOOUT_TIME_SINGLE"},
	{EN_GOOUT_TIME_SERVIC,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_TIME_SERVICE,  CN_NULL_PINNO,  0,  "��ʱ����״̬",   "GOOUT_TIME_SERVIC"},
	{EN_GOOUT_TIME_CHKERR,   EN_CTYPE_IO_S,   EN_DTYPE_ALM,  EN_ALM_TIME_CHKERR,   CN_NULL_PINNO,  0,  "ʱ���������״̬",   "GOOUT_TIME_CHKERR"},
};
const DWORD g_NUM_GOOUT = sizeof(g_tGoOutTab) / sizeof(tagGoOutTab);
/*================================================================================*/
//6. LED������
/*================================================================================
    WORD            wIndex;                         // ˫�㿪��ö��
    BYTE            wSrcType;                       // �����ź�Դ
    BYTE            wSrcIndex;                      // ������λ�ź�
    WORD            wParaIndex1;                    // ��������1
    BYTE            byCol;                          // ��λ��
    BYTE            byRow;                          // ��λ��
    BYTE            bycolor;                        // ָʾ����ɫ
    BOOL            bHld;                           // ָʾ�Ʊ��ֱ�־
    INT8S           byName[CN_LEN_NAME];            // ˫�㿪��������
    INT8S           byPinName[CN_LEN_NAME];         // ˫�㿪�����̵�ַ����
*================================================================================*/

const tagLedTab  g_tLedTab[ ] =
{
	{EN_LED_RUN       ,      EN_DTYPE_FLAG,  EN_FLAG_LED_RUN ,  CN_NULL_PINNO,  0,    0,    EN_COLOR_GREEN,    0,  "����",        "LED_RUN"},
	{EN_LED_ALM       ,      EN_DTYPE_FLAG,  EN_FLAG_LED_ALM ,  CN_NULL_PINNO,  0,    1,    EN_COLOR_RED  ,    0,  "�澯",        "LED_ALM"},
	{EN_LED_TEST      ,      EN_DTYPE_DI  ,  EN_DI_TEST      ,  CN_NULL_PINNO,  0,    2,    EN_COLOR_RED  ,    0,  "����",        "LED_TEST"},
	{EN_LED_GO_ERR    ,      EN_DTYPE_ALM ,  EN_ALM_GOOSE    ,  CN_NULL_PINNO,  0,    3,    EN_COLOR_RED  ,    0,  "GOOSE�쳣",   "LED_GO_ERR"},
	{EN_LED_TEST_ERR  ,      EN_DTYPE_ALM ,  EN_ALM_TEST     ,  CN_NULL_PINNO,  0,    4,    EN_COLOR_RED  ,    0,  "���޲�һ��",  "LED_TEST_ERR"},
	{EN_LED_SYN_ERR   ,      EN_DTYPE_ALM ,  EN_ALM_SYN      ,  CN_NULL_PINNO,  0,    5,    EN_COLOR_RED  ,    0,  "ͬ���쳣",      "LED_SYN_ERR"},
	{EN_LED_SAM_ERR   ,      EN_DTYPE_ALM ,  EN_ALM_SAM      ,  CN_NULL_PINNO,  0,    6,    EN_COLOR_RED  ,    0,  "�����쳣",      "LED_SAM_ERR"},
	{EN_LED_KHDX      ,      EN_DTYPE_ALM ,  EN_ALM_KHDX     ,  CN_NULL_PINNO,  0,    7,    EN_COLOR_RED  ,    0,  "���ƻ�·����",  "LED_KHDX"},
	{EN_LED_BHTZ      ,      EN_DTYPE_FLAG,  EN_FLAG_BHTZ    ,  CN_NULL_PINNO,  1,    0,    EN_COLOR_RED  ,    1,  "������բ",     "LED_BHTZ"},
	{EN_LED_BHHZ      ,      EN_DTYPE_FLAG,  EN_FLAG_BHHZ    ,  CN_NULL_PINNO,  1,    1,    EN_COLOR_RED  ,    1,  "������բ",     "LED_BHHZ"},
	{EN_LED_ZTF       ,      EN_DTYPE_FLAG,  EN_FLAG_DI_TJF  ,  CN_NULL_PINNO,  1,    2,    EN_COLOR_RED  ,    1,  "�ǵ���ֱ��",   "LED_ZTF"},
	{EN_LED_BAK21     ,      EN_DTYPE_FLAG,  EN_FLAG_LED_BAK21, CN_NULL_PINNO,  1,    3,    EN_COLOR_RED  ,    0,  "����1",       "LED_BAK21"},
	{EN_LED_BAK22     ,      EN_DTYPE_FLAG,  EN_FLAG_LED_BAK22, CN_NULL_PINNO,  1,    4,    EN_COLOR_RED  ,    0,  "����2",       "LED_BAK22"},
	{EN_LED_BAK23     ,      EN_DTYPE_FLAG,  EN_FLAG_LED_BAK23, CN_NULL_PINNO,  1,    5,    EN_COLOR_RED  ,    0,  "����3",       "LED_BAK23"},
	{EN_LED_BAK24     ,      EN_DTYPE_FLAG,  EN_FLAG_LED_BAK24, CN_NULL_PINNO,  1,    6,    EN_COLOR_RED  ,    0,  "����4",       "LED_BAK24"},
	{EN_LED_HWJ       ,      EN_DTYPE_DI  ,  EN_DI_XCBR_CLS  ,  CN_NULL_PINNO,  1,    7,    EN_COLOR_RED  ,    0,  "��·����λ",  "LED_HWJ"},

	{EN_LED_WAR_LNK   ,      EN_DTYPE_ALM ,  EN_ALM_LINK     ,  CN_NULL_PINNO,  2,    0,    EN_COLOR_RED  ,    0,  "�����쳣",    "LED_WAR_LNK"},
	{EN_LED_VCHG_I    ,      EN_DTYPE_FLAG,  EN_FLAG_V_I     ,  CN_NULL_PINNO,  2,    1,    EN_COLOR_RED  ,    0,  "ѹ��ȡ��ĸ",  "LED_VCHG_I"},
	{EN_LED_VCHG_II   ,      EN_DTYPE_FLAG,  EN_FLAG_V_II    ,  CN_NULL_PINNO,  2,    2,    EN_COLOR_RED  ,    0,  "ѹ��ȡ��ĸ",  "LED_VCHG_II"},
	{EN_LED_LNK_A     ,      EN_DTYPE_FLAG,  EN_FLAG_LNK_A   ,  CN_NULL_PINNO,  2,    3,    EN_COLOR_RED  ,    0,  "����ȡA��",   "LED_LNK_A"},
	{EN_LED_LNK_B     ,      EN_DTYPE_FLAG,  EN_FLAG_LNK_B   ,  CN_NULL_PINNO,  2,    4,    EN_COLOR_RED  ,    0,  "����ȡB��",   "LED_LNK_B"},
	{EN_LED_BAK31     ,      EN_DTYPE_FLAG,  EN_FLAG_LED_BAK31, CN_NULL_PINNO,  2,    5,    EN_COLOR_GREEN,    0,  "����5",      "LED_BAK31"},
	{EN_LED_BAK32     ,      EN_DTYPE_FLAG,  EN_FLAG_LED_BAK32, CN_NULL_PINNO,  2,    6,    EN_COLOR_GREEN,    0,  "����6",      "LED_BAK32"},
	{EN_LED_TWJ       ,      EN_DTYPE_DI  ,  EN_DI_XCBR_OPN  ,  CN_NULL_PINNO,  2,    7,    EN_COLOR_GREEN,    0,  "��·����λ",  "LED_TWJ"},

	{EN_LED_XSWI01_CLS,      EN_DTYPE_DI,  EN_DI_XSWI01_CLS  ,  CN_NULL_PINNO,  3,    0,    EN_COLOR_RED  ,    0,  "��բ1��λ",   "LED_XSWI01_CLS"},
	{EN_LED_XSWI02_CLS,      EN_DTYPE_DI,  EN_DI_XSWI02_CLS  ,  CN_NULL_PINNO,  3,    1,    EN_COLOR_RED  ,    0,  "��բ2��λ",   "LED_XSWI02_CLS"},
	{EN_LED_XSWI03_CLS,      EN_DTYPE_DI,  EN_DI_XSWI03_CLS  ,  CN_NULL_PINNO,  3,    2,    EN_COLOR_RED  ,    0,  "��բ3��λ",   "LED_XSWI03_CLS"},
	{EN_LED_XSWI04_CLS,      EN_DTYPE_DI,  EN_DI_XSWI04_CLS  ,  CN_NULL_PINNO,  3,    3,    EN_COLOR_RED  ,    0,  "��բ4��λ",   "LED_XSWI04_CLS"},
	{EN_LED_XSWI05_CLS,      EN_DTYPE_DI,  EN_DI_XSWI05_CLS  ,  CN_NULL_PINNO,  3,    4,    EN_COLOR_RED  ,    0,  "��բ5��λ",   "LED_XSWI05_CLS"},
	{EN_LED_XSWI06_CLS,      EN_DTYPE_DI,  EN_DI_XSWI06_CLS  ,  CN_NULL_PINNO,  3,    5,    EN_COLOR_RED  ,    0,  "��բ6��λ",   "LED_XSWI06_CLS"},
	{EN_LED_XSWI07_CLS,      EN_DTYPE_DI,  EN_DI_XSWI07_CLS  ,  CN_NULL_PINNO,  3,    6,    EN_COLOR_RED  ,    0,  "��բ7��λ",   "LED_XSWI07_CLS"},
	{EN_LED_XSWI08_CLS,      EN_DTYPE_DI,  EN_DI_XSWI08_CLS  ,  CN_NULL_PINNO,  3,    7,    EN_COLOR_RED  ,    0,  "��բ8��λ",   "LED_XSWI08_CLS"},

	{EN_LED_XSWI01_OPN,      EN_DTYPE_DI,  EN_DI_XSWI01_OPN  ,  CN_NULL_PINNO,  4,    0,    EN_COLOR_GREEN,    0,  "��բ1��λ",   "LED_XSWI01_OPN"},
	{EN_LED_XSWI02_OPN,      EN_DTYPE_DI,  EN_DI_XSWI02_OPN  ,  CN_NULL_PINNO,  4,    1,    EN_COLOR_GREEN,    0,  "��բ2��λ",   "LED_XSWI02_OPN"},
	{EN_LED_XSWI03_OPN,      EN_DTYPE_DI,  EN_DI_XSWI03_OPN  ,  CN_NULL_PINNO,  4,    2,    EN_COLOR_GREEN,    0,  "��բ3��λ",   "LED_XSWI03_OPN"},
	{EN_LED_XSWI04_OPN,      EN_DTYPE_DI,  EN_DI_XSWI04_OPN  ,  CN_NULL_PINNO,  4,    3,    EN_COLOR_GREEN,    0,  "��բ4��λ",   "LED_XSWI04_OPN"},
	{EN_LED_XSWI05_OPN,      EN_DTYPE_DI,  EN_DI_XSWI05_OPN  ,  CN_NULL_PINNO,  4,    4,    EN_COLOR_GREEN,    0,  "��բ5��λ",   "LED_XSWI05_OPN"},
	{EN_LED_XSWI06_OPN,      EN_DTYPE_DI,  EN_DI_XSWI06_OPN  ,  CN_NULL_PINNO,  4,    5,    EN_COLOR_GREEN,    0,  "��բ6��λ",   "LED_XSWI06_OPN"},
	{EN_LED_XSWI07_OPN,      EN_DTYPE_DI,  EN_DI_XSWI07_OPN  ,  CN_NULL_PINNO,  4,    6,    EN_COLOR_GREEN,    0,  "��բ7��λ",   "LED_XSWI07_OPN"},
	{EN_LED_XSWI08_OPN,      EN_DTYPE_DI,  EN_DI_XSWI08_OPN  ,  CN_NULL_PINNO,  4,    7,    EN_COLOR_GREEN,    0,  "��բ8��λ",   "LED_XSWI08_OPN"}
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


