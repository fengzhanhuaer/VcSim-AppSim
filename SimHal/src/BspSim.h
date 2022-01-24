#pragma once
#include"ApiProject.h"
using namespace spt;

extern"C"  int SptSendEmacData(int EmacNo, unsigned char* Txbuf, int TxLen);
extern"C"  int SptRecEmacData(int EmacNo, void* Buf, int BufLen);
extern"C"  int SptSetEthnetPara(int NetNo, char* Ip, char* Mask, char* Gate, char* Mac, char* Flag);
extern"C"  int SptSetEthnetWhiteBill(int NetNo, char* Ip);


struct HalSimFpgaFrame :public CpuFpgaCmmMsgBuf
{
	void Send(uint16 Type);
};