#ifndef SPTMSINT_H
#define SPTMSINT_H

namespace spt
{
	class SptMsInt
	{
		//public service interface
	public:
		uint32 MsCnt32();
		uint64 MsCnt64();
		uint32 PowerUpMsCnt32();
		uint64 PowerUpMsCnt64();
		//platform function interface
	public:
		static SptMsInt& Instance();
		/*
		*MsIntType:0,real time ,1,normal
		*/
		void PowerUpIni(int32 MsIntType);
		void Interrupt();
	private:
		uint32 powerUpCnt32;
		uint32 msCnt32;
		uint64 powerUpCnt64;
		uint64 msCnt64;
	};


}


#endif // !SPTMSINT_H

