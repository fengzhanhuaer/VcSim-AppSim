#ifndef SPTBITMAP_H
#define SPTBITMAP_H

namespace spt
{
	struct BitMapDes
	{
		uint16 widthOfByte;
		uint16 height;
		const uint8* buf;
	};
	enum BitMapInstCode
	{
		E_IRIG_B_SYN,
		E_SNTP_SYN,
		E_BMT_TOTAL,
	};
	extern const BitMapDes BitMapInst[E_BMT_TOTAL];
}

#endif // SPTBITMAP_H