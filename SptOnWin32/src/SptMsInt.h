#ifndef SPTMSINT_H
#define SPTMSINT_H

namespace spt
{
	/// <summary>
	/// Ms中断服务
	/// </summary>
	class SptMsInt
	{
		//public service interface
	public:
		/// <summary>
		/// 32位ms计数器
		/// </summary>
		/// <returns></returns>
		uint32 MsCnt32();
		/// <summary>
		/// 64位ms计数器
		/// </summary>
		/// <returns></returns>
		uint64 MsCnt64();
		/// <summary>
		/// 上电时间是否大于
		/// </summary>
		/// <param name="TimeMs"></param>
		/// <returns></returns>
		bool8 IsPowerUpOver(uint32 TimeMs);
		//platform function interface
	public:
		static SptMsInt& Instance();
		/*
		*MsIntType:0,real time ,1,normal
		*/
		void PowerUpIni(int32 MsIntType);
		void Interrupt();
	private:
		volatile uint32 msCnt32;
		volatile uint64 msCnt64;
		SptIntData intData;
	};


}


#endif // !SPTMSINT_H

