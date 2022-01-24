#include "SalTypes.h"
#ifndef SPTSAMPINT_H
#define SPTSAMPINT_H

namespace spt
{
	typedef void(*IntFunc)();

	typedef struct
	{
		char Enable;
		IntFunc func;
	}SptIntData;
	/// <summary>
	/// �����жϷ���
	/// </summary>
	class SptSampInt
	{
		//public service interface
	public:
		/// <summary>
		/// �����ж�����
		/// </summary>
		/// <returns></returns>
		uint32 PeriodUs();
		/// <summary>
		/// �����жϼ���
		/// </summary>
		/// <returns></returns>
		uint32 Cnt32();
		/// <summary>
		/// �����жϼ���
		/// </summary>
		/// <returns></returns>
		uint64 Cnt64();
		//platform function interface
	public:
		static SptSampInt& Instance();
		/*
		*MsIntType:0,real time ,1,normal
		*/
		void PowerUpIni(int32 IntType);
		void Interrupt();
	private:
		uint32 periodUs;
		volatile uint32 msCnt32;
		volatile uint64 msCnt64;
		SptIntData intData;
	};


}


#endif // !SPTSAMPINT_H
