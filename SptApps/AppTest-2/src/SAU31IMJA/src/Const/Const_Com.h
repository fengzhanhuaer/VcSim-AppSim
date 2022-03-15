#ifndef _CONST_COM_H_
#define _CONST_COM_H_

#include "IES_IMtypes.h"

#define CN_TX_MAX     (512)
#define CN_RX_FRAME   (8)
// ������ͨ���иĶ�,������У����
#define CN_CPU_SOFT_COM     (0x1000)       // CPU���У��汾

enum _COM_TYPE
{
	EN_COM_TYPE_INIT01=0x5501,
	EN_COM_TYPE_FAST01=0x5A01,
	EN_COM_TYPE_SLOW01=0xA501,
};
// ��佻���汾��Ϣ
typedef struct
{
	WORD wVer;
	WORD wVerNum;
	WORD wSlowInitNum;
	WORD wSlow1To2Num;
	WORD wSlow2To1Num;
	WORD wFast1To2Num;
	WORD wFast2To1Num;
	WORD wBak[3];
}tagComVer;
// ��佻����֡
typedef struct
{
	BYTE byRamScan1;
	WORD wReset;
	WORD wFlag;
	WORD wSendFlag;
	WORD wSendPtr;
	WORD wType;
	WORD wLen;
	BYTE byRamScan2;
	BYTE byData[CN_TX_MAX];
	BYTE byRamScan3;
}tagCom;
/*================================================================================*/
//������Ϣ������ṹ��
/*================================================================================*/
// ģ����������Ϣ�����ݽṹ
typedef struct
{
	BYTE           *pwSrcAddr;                     // ����Դ��ַ
	DWORD           dwSrcLen;                      // ���ݳ���
	BOOL           *pbSrcChg;                      // ����Դ�仯��־	
	BYTE           *pwDstAddr;                     // ����Ŀ�ĵ�ַ
	DWORD           dwDstLen;                      // ���ݳ���
	BOOL           *pbDstChg;                      // ����Ŀ�ı仯��־
} tagComSlowTab;
/*================================================================================*/
//������Ϣ������ṹ��
/*================================================================================*/
// ģ����������Ϣ�����ݽṹ
typedef struct
{
	BYTE           *pwSrcAddr;                     // ����Դ��ַ
	BYTE           *pwDstAddr;                     // ����Ŀ�ĵ�ַ
	BOOL            bSet;                          // ���Ʊ�־ 0:ȡ�� 1:ȡ��
} tagComFastTab;

/*================================================================================*/
// ��������
/*================================================================================*/
extern tagComVer  g_tComVer[2];       // �汾��Ϣ
extern tagCom  g_tComFastTx;          // ��佻���������ݷ�����֡
extern tagCom  g_tComSlowTx;          // ��佻���������ݷ�����֡
extern tagCom  g_tComFastRx;          // ��佻���������ݽ��ջ���
extern tagCom  g_tComSlowRx;          // ��佻���������ݽ��ջ���
extern const tagComSlowTab  g_tComInitTab[];
extern const DWORD          g_NUM_COM_INIT;
extern const tagComFastTab  g_tComFast1To2Tab[];
extern const DWORD          g_NUM_COM1TO2_FAST;
extern const tagComFastTab  g_tComFast2To1Tab[];
extern const DWORD          g_NUM_COM2TO1_FAST;
extern const tagComSlowTab  g_tComSlow1To2Tab[];
extern const DWORD          g_NUM_COM1TO2_SLOW;
extern const tagComSlowTab  g_tComSlow2To1Tab[];
extern const DWORD          g_NUM_COM2TO1_SLOW;
/*================================================================================*/
#endif /* _CONST_COM_H_ */
