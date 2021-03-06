#include"SptProject.h"
using namespace spt;
const uint8 IrigB_Syn[] =
{
	0x00, 0x00, 0x63, 0x1E, 0x33, 0x30, 0x1B, 0x60, 0x0F, 0xC0, 0x07, 0x80, 0x03, 0x7C, 0x03, 0x66,
	0x03, 0x66, 0x03, 0x66, 0x03, 0x7C, 0x03, 0x66, 0x03, 0x66, 0x03, 0x66, 0x03, 0x7C, 0x00, 0x00
};
const uint8 SNTP_Syn[] =
{
	0x00,0x00,0x63,0x1E,0x33,0x30,0x1B,0x60,0x0F,0xC0,0x07,0x80,0x03,0x3C,0x03,0x66,
	0x03,0x60,0x03,0x60,0x03,0x3C,0x03,0x06,0x03,0x06,0x03,0x66,0x03,0x3C,0x00,0x00
};

const BitMapDes spt::BitMapInst[E_BMT_TOTAL] = {
	{2,sizeof(IrigB_Syn) / 2,IrigB_Syn},
	{2,sizeof(SNTP_Syn) / 2,SNTP_Syn}
};
