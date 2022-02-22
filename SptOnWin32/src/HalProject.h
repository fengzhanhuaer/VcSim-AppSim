#ifndef HALPROJECT_H
#define HALPROJECT_H

#include "HalFactoryTools.h"
#include "HalBoardIo.h"


//MsIntFunc为回调函数
//Enable为1时使能中断，为0则禁止中断
extern"C" void SetMsInt(void(*MsIntFunc)(), char Enable);
extern"C" void SetSampInt(void(*MsIntFunc)(), char Enable, unsigned int Us);
void SetMsNormalInt(void(*MsIntFunc)(), char Enable);
extern"C" unsigned int HwUsCnt();//硬件层提供微秒计数器
extern"C"  int SptSendEmacData(int EmacNo, unsigned char* Txbuf, int TxLen);
extern"C"  int SptRecEmacData(int EmacNo, void* Buf, int BufLen);
extern"C"  int SptSetEthnetPara(int NetNo, char* Ip, char* Mask, char* Gate, char* Mac, char* Flag);
extern"C"  int SptSetEthnetWhiteBill(int NetNo, char* Ip);
extern"C"  int SptEnableEthnetPara(int Type, char Para);
enum HalSerialPortNo
{
	E_HSPN_Null,
	E_HSPN_LCD_CMM,//液晶通讯
	E_HSPN_DO_CMM,
	E_HSPN_PRINT_CMM,
	E_SerialNum,
};
enum HalSerialParaType
{
	E_HSPT_Null,
	E_HSPT_BaudRate,//波特率
	E_HSPT_DataLen,//数据长度
	E_HSPT_Parity,//奇偶校验
	E_HSPT_StopBit,//停止位
	E_HSPT_AppPara,//应用设置的上述参数
	E_HSPT_EnableTxRx,//接收/发送使能
	E_HSPT_EnableTx,//发送使能
	E_HSPT_EnableRx,//接收使能
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
	E_HPT_Temperature,//装置温度,4字节
	E_HPT_PowerUp,//装置电源正常,1字节
	E_HPT_SetBegin = 100000,
	E_HPT_UnitErr,//装置故障,1字节
	E_HPT_RunErr,//运行异常,1字节
	E_HPT_RelayPower,//电源继电器24V,1字节
	E_HPT_RelayPower30V,//电源继电器30V,1字节
};
extern "C"  int SptGetHwVal(int Type, void* Ptr, int Len);
extern "C"  int SptSetHwVal(int Type, void* Ptr, int Len);

namespace spt
{




}


#endif // !HALPROJECT_H

