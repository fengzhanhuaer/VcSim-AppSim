/*================================================================================
 * �ļ�������ϵͳ��Դ��������
 * �ļ��汾: V1.00
 * ����ʱ��:
 * �汾�޶�:
 * �޶���Ա:
 *================================================================================*/

#include "IES_IMsrc.h"
/*================================================================================*/
// Ӧ�ò�ȫ��������
/*================================================================================*/
tagDevInfor   g_tDevInfor;                // �汾��Ϣ
tagAna        g_tagAna;                   // ģ��������
tagIO         g_tagIO;                    // IO����
tagDC         g_tagDC;                    // ֱ������
tagPara       g_tagPara;                  // ����
tagRamScan    g_tagRamScan;               // �ڴ�ɨ��ṹ��
tagPub        g_tagPub;                   // ��������
BOOL          g_bFlag[CN_NUM_FLAG+1];     // ȫ�ֲ���������־����
INT32         g_iInter[CN_NUM_INTER+1];   // ȫ���ڲ����ݶ���
tagActQueue   g_tActQueue[CN_NUM_ACT];    // GOOSE�����¼��������
tagActState   g_tActState;                // GOOSE�����¼�ʵʱ״̬
tagAlmState   g_tAlmState;                // �澯�¼�ʵʱ״̬
tagChkState   g_tChkState;                // �Լ��¼�ʵʱ״̬


