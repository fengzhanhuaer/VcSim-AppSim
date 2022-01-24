#ifndef HALPROJECT_H
#define HALPROJECT_H

//MsIntFunc为回调函数
//Enable为1时使能中断，为0则禁止中断
extern"C" void SetMsInt(void(*MsIntFunc)(), char Enable);
extern"C" void SetSampInt(void(*MsIntFunc)(), char Enable, unsigned int Us);
void SetMsNormalInt(void(*MsIntFunc)(), char Enable);
extern "C" unsigned int HwUsCnt();//硬件层提供微秒计数器
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
	E_SerialNum,
};
extern"C"  int SptSendSerialData(unsigned int No, void* Sur, int MsgLen);
extern"C"  int SptReadSerialData(unsigned int No, void* Sur, int MsgLen);
extern"C"  int LcdSetLedDispVal(unsigned IedSerial, unsigned Cor);
extern"C"  int LcdWriteDispBuf(unsigned x, unsigned y, unsigned w, unsigned h, void* buf, unsigned bufW, unsigned bufH);
namespace spt
{




}


#endif // !HALPROJECT_H

