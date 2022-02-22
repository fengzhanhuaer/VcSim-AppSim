#ifndef HALPROJECT_H
#define HALPROJECT_H

#include "HalFactoryTools.h"
#include "HalBoardIo.h"


//MsIntFuncΪ�ص�����
//EnableΪ1ʱʹ���жϣ�Ϊ0���ֹ�ж�
extern"C" void SetMsInt(void(*MsIntFunc)(), char Enable);
extern"C" void SetSampInt(void(*MsIntFunc)(), char Enable, unsigned int Us);
void SetMsNormalInt(void(*MsIntFunc)(), char Enable);
extern"C" unsigned int HwUsCnt();//Ӳ�����ṩ΢�������
extern"C"  int SptSendEmacData(int EmacNo, unsigned char* Txbuf, int TxLen);
extern"C"  int SptRecEmacData(int EmacNo, void* Buf, int BufLen);
extern"C"  int SptSetEthnetPara(int NetNo, char* Ip, char* Mask, char* Gate, char* Mac, char* Flag);
extern"C"  int SptSetEthnetWhiteBill(int NetNo, char* Ip);
extern"C"  int SptEnableEthnetPara(int Type, char Para);
enum HalSerialPortNo
{
	E_HSPN_Null,
	E_HSPN_LCD_CMM,//Һ��ͨѶ
	E_HSPN_DO_CMM,
	E_HSPN_PRINT_CMM,
	E_SerialNum,
};
enum HalSerialParaType
{
	E_HSPT_Null,
	E_HSPT_BaudRate,//������
	E_HSPT_DataLen,//���ݳ���
	E_HSPT_Parity,//��żУ��
	E_HSPT_StopBit,//ֹͣλ
	E_HSPT_AppPara,//Ӧ�����õ���������
	E_HSPT_EnableTxRx,//����/����ʹ��
	E_HSPT_EnableTx,//����ʹ��
	E_HSPT_EnableRx,//����ʹ��
	E_HSPT_Num,
};
extern"C"  int SptSendSerialData(unsigned int No, void* Sur, int MsgLen);
extern"C"  int SptReadSerialData(unsigned int No, void* Sur, int MsgLen);
extern"C" int SptSetSerial(unsigned int No, unsigned int baudrate, unsigned int dataLen, unsigned int par, unsigned int stop);
extern"C"	int SptSetSerialPara(unsigned int No, HalSerialParaType Type, unsigned int Para);
extern"C"	int SptGetSerialPara(unsigned int No, HalSerialParaType Type, unsigned int* Para);
enum HwParaType
{
	E_HPT_GetBegin,
	E_HPT_Temperature,//װ���¶�,4�ֽ�
	E_HPT_PowerUp,//װ�õ�Դ����,1�ֽ�
	E_HPT_SetBegin = 100000,
	E_HPT_UnitErr,//װ�ù���,1�ֽ�
	E_HPT_RunErr,//�����쳣,1�ֽ�
	E_HPT_RelayPower,//��Դ�̵���24V,1�ֽ�
	E_HPT_RelayPower30V,//��Դ�̵���30V,1�ֽ�
};
extern "C"  int SptGetHwVal(int Type, void* Ptr, int Len);
extern "C"  int SptSetHwVal(int Type, void* Ptr, int Len);

namespace spt
{




}


#endif // !HALPROJECT_H

