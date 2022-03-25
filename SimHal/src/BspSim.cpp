#include"BspSim.h"
#include <windows.h>  
#include "psapi.h"  
#include"stdio.h"
#include <tlhelp32.h>
#pragma  warning(disable:4996)

extern"C"  int SptSendSerialData(unsigned int No, void* Sur, int MsgLen)
{
	return 0;
}
extern"C"  int SptReadSerialData(unsigned int No, void* Sur, int MsgLen)
{
	return 0;
}
extern"C" int SptSetSerial(unsigned int No, unsigned int baudrate, unsigned int dataLen, unsigned int par, unsigned int stop)
{
	return 0;
}
extern"C"	int SptSetSerialPara(unsigned int No, HalSerialParaType Type, unsigned int Para)
{
	return 0;
}
extern"C"	int SptGetSerialPara(unsigned int No, HalSerialParaType Type, unsigned int* Para)
{
	return 0;
}
SampIntMsgPool EmacSendPool[1];
SampIntMsgPool EmacRecvPool[1];

void HalSimFpgaFrame::Send(uint16 Type)
{
	msg.BoardCmm.frameType1 = Type;
	msg.BoardCmm.res1 = 0;
	msg.BoardCmm.frameLen1 = writer + 2;
	AddSum();
	EmacRecvPool[0].Push(&msg.BoardCmm.dstMac1[0], writer + 20);
}

extern"C"  int SptSendEmacData(int EmacNo, unsigned char* Txbuf, int TxLen)
{
	const ApiAppCfg* cfg = SptMain::Instance().AppCfg();
	if (cfg->platform.hardware == EH_GZKSAU)
	{
		SampIntMsg* msg = (SampIntMsg*)Txbuf;
		if (msg->frameType == FpgaMsgProc::E_CPU_FPGA_BOARD_CMM)
		{
			msg->frameType = FpgaMsgProc::E_FPGA_CPU_Board_CMM;
			EmacRecvPool[EmacNo].Push(Txbuf, TxLen);
		}
	}
	return 0;
}

extern"C"  int  SptRecEmacData(int EmacNo, void* Buf, int BufLen)
{
	int32 len = EmacRecvPool[EmacNo].Pop(Buf, BufLen);
	return len;
}
int FindProcess(const wchar_t* Name)
{
	int i = 0;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	BOOL bMore = ::Process32First(hProcessSnap, &pe32);
	while (bMore)
	{
		//printf(" 进程名称：%s \n", pe32.szExeFile);
		if (wcscmp(Name, pe32.szExeFile) == 0)
		{
			i += 1;
			break;
		}
		bMore = ::Process32Next(hProcessSnap, &pe32);
	}
	::CloseHandle(hProcessSnap);
	if (i >= 1) {           //大于1，排除自身
		return 0;
	}
	else {
		return -1;
	}
}
void StartLcd()
{
	if (FindProcess(L"SimLcd.exe"))
	{
		WinExec("SimLcd.exe", SW_NORMAL);
		Sleep(1000);
	}
	else
	{
		return;
	}
#if 0
	if (FindProcess(L"SimLcd.exe"))
	{
		WinExec("..\\..\\Debug\\SimLcd.exe", SW_NORMAL);
		Sleep(1000);
	}
	else
	{
		return;
	}
	if (FindProcess(L"SimLcd.exe"))
	{
		WinExec("..\\..\\Release\\SimLcd.exe", SW_NORMAL);
		Sleep(1000);
	}
	else
	{
		return;
	}
#endif
}
extern"C" int SimSysStartUp()
{
	EmacSendPool[0].PowerUpIni(20);
	EmacRecvPool[0].PowerUpIni(20);
	StartLcd();
	return 0;
}

void SendSampFrame()
{
	char buf[] =
	{
1
	};
	//EmacRecvPool[0].Push(&buf, sizeof(buf));
}

extern "C" int HalSimSampProcess()
{
	SendSampFrame();



	return 0;
};

static uint8 HPT_PowerUp = 1;

extern "C"  int SptGetHwVal(int Type, void* Ptr, int Len)
{
	if (E_HPT_PowerUp == Type)
	{
		uint8* pHPT_PowerUp = (uint8*)Ptr;
		*pHPT_PowerUp = HPT_PowerUp;
		return 0;
	}
	return 0;
}
extern "C"  int SptSetHwVal(int Type, void* Ptr, int Len)
{
	if (E_HPT_PowerUp == Type)
	{
		uint8* pHPT_PowerUp = (uint8*)Ptr;
		HPT_PowerUp = *pHPT_PowerUp;
		return 0;
	}
	return 0;
}