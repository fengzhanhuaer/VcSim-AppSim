#ifndef SALAPPCMM_H
#define SALAPPCMM_H

namespace spt
{
	struct AppCmmCtrl
	{
		uint16 msgType;
		uint16 recvCnt;
		uint16 lastRecvCnt;
		uint16 recvBufSize;
		bool8 msgOk;
		uint16 recvCtxLen;
		void* msgBuf;
	};


}

#endif // !SALAPPCMM_H

