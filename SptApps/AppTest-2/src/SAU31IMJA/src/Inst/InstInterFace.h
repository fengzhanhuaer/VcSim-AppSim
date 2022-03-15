#ifndef INSTINTERFACE_H
#define INSTINTERFACE_H
typedef struct
{
    WORD            wIndex;                         // 通道类型枚举
    const VarUnits  *pUnit1;                        // 单位1
    const VarUnits  *pUnit2;                        // 单位2
    BYTE            byWidth;                        // 数据长度(界面显示用)
    BYTE            byDotBit;                       // 小数位数(界面显示用)
    WORD            wParaIndex;                     // 关联单位转换参数
}tagCTypeTab;
#define  CN_NUM_ENUMDES    (20)
typedef struct
{
    WORD             wIndex;                         // 通道类型枚举
    const VarUnits   *pUnit1;                        // 单位1
    const VarUnits   *pUnit2;                        // 单位2
    BYTE             byEnNum;                        // 枚举个数
    SalEnumDes       eEnumDes[CN_NUM_ENUMDES];       // 枚举列表最大20组
}tagCEnumTab;

typedef struct
{
    WORD                      wIndex;               // 记录数据类型枚举
    StatusExInfoDesItem       eventData;            // 记录数据配置 
}tagMEATab;

typedef struct
{
    BYTE  byIndex;                                   // 板卡地址
    const char *pPortName[40];                       // 光口名称
    BYTE  byPortNum;                                 // 光口个数
    BYTE  byPortOffset;                              // 光口个数偏移
}tagCardTab;
// 界面密码集
#define CN_KEY_MAX   (10)
typedef struct
{
    BYTE  byIndex;                                   // 指令枚举
    BYTE  byKey[CN_KEY_MAX];                         // 指令集和
    BYTE  byKeyNum;                                  // 指令个数
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
