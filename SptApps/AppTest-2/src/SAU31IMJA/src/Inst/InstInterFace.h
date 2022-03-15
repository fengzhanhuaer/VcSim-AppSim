#ifndef INSTINTERFACE_H
#define INSTINTERFACE_H
typedef struct
{
    WORD            wIndex;                         // ͨ������ö��
    const VarUnits  *pUnit1;                        // ��λ1
    const VarUnits  *pUnit2;                        // ��λ2
    BYTE            byWidth;                        // ���ݳ���(������ʾ��)
    BYTE            byDotBit;                       // С��λ��(������ʾ��)
    WORD            wParaIndex;                     // ������λת������
}tagCTypeTab;
#define  CN_NUM_ENUMDES    (20)
typedef struct
{
    WORD             wIndex;                         // ͨ������ö��
    const VarUnits   *pUnit1;                        // ��λ1
    const VarUnits   *pUnit2;                        // ��λ2
    BYTE             byEnNum;                        // ö�ٸ���
    SalEnumDes       eEnumDes[CN_NUM_ENUMDES];       // ö���б����20��
}tagCEnumTab;

typedef struct
{
    WORD                      wIndex;               // ��¼��������ö��
    StatusExInfoDesItem       eventData;            // ��¼�������� 
}tagMEATab;

typedef struct
{
    BYTE  byIndex;                                   // �忨��ַ
    const char *pPortName[40];                       // �������
    BYTE  byPortNum;                                 // ��ڸ���
    BYTE  byPortOffset;                              // ��ڸ���ƫ��
}tagCardTab;
// �������뼯
#define CN_KEY_MAX   (10)
typedef struct
{
    BYTE  byIndex;                                   // ָ��ö��
    BYTE  byKey[CN_KEY_MAX];                         // ָ���
    BYTE  byKeyNum;                                  // ָ�����
}tagKeyTab;

extern const tagCTypeTab  g_tCTypeTab[];
extern const DWORD        g_NUM_CTYPE;
extern tagCEnumTab        g_tCEnumTab[];
extern const DWORD        g_NUM_CENUM;
extern tagMEATab          g_tMEATab[];
extern const DWORD        g_NUM_MEA;
extern const tagCardTab   g_tCardTab[];
extern const DWORD        g_NUM_CARD;
extern const tagKeyTab    g_tKeyTab[];
extern const DWORD        g_NUM_KEY;

extern void AppInterFaceChk(void);
#endif // !INSTINTERFACE_H
