#include "ApiProject.h"
using namespace spt;

GBK_SYMBOL& spt::GBK_SYMBOL::Instance()
{
	static GBK_SYMBOL inst;
	return inst;
}

spt::GBK_SYMBOL::GBK_SYMBOL()
{

}

spt::SalEscPk2Printer::SalEscPk2Printer(void* Buf, uint32 BufLen)
{
	buf = (uint8*)Buf;
	bufLen = BufLen;
	writer = 0;
}
