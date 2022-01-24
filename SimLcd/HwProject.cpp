#include"SptProject.h"
using namespace spt;

#ifdef  WIN32_SIM
#ifndef _WINDOWS_
#include<windows.h>
#endif
unsigned int HwUsCnt()
{
	LARGE_INTEGER m_nFreq;
	LARGE_INTEGER m_Time;

	QueryPerformanceFrequency(&m_nFreq); // 获取时钟周期
	QueryPerformanceCounter(&m_Time); // 获取时钟计数

	uint64 stamp = (uint64)m_Time.QuadPart;
	double coe = 1000000.0 / m_nFreq.QuadPart;
	stamp = (uint64)(stamp * coe);

	return (unsigned int)stamp;
}
extern"C"  int SptSendSerialData(unsigned int No, void* Sur, int MsgLen) { return 0; };
extern"C"  int SptReadSerialData(unsigned int No, void* Sur, int MsgLen) { return 0; };
#endif //  WIN32_SIM

