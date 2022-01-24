#ifndef SPTCHECKTASK_H
#define SPTCHECKTASK_H

namespace spt
{
	/// <summary>
	/// 自检类
	/// </summary>
	class SptCheckTask :public Task
	{
	public:

	public:
		M_Singleton(SptCheckTask);
		struct CheckAppInst;
		typedef int (*CheckFunction)(struct CheckAppInst* Inst);
		/// <summary>
		/// 应用自检回调接口
		/// </summary>
		struct CheckAppInst
		{
			/// <summary>
			/// 使能
			/// </summary>
			bool8 enable;
			/// <summary>
			/// 周期
			/// </summary>
			uint32 period;
			/// <summary>
			/// 应用自用参数
			/// </summary>
			void* para;
			/// <summary>
			/// 回调函数
			/// </summary>
			CheckFunction func;
			uint32 lastRunTime;
		};
		/// <summary>
		/// 添加应用自检任务
		/// </summary>
		/// <param name="Inst"></param>
		/// <returns>-1 is fail </returns>
		int32 AddAppCheckInst(struct CheckAppInst* Inst);
		/// <summary>
		/// 自检任务初始化
		/// </summary>
		/// <param name="Para"></param>
		/// <returns></returns>
		virtual int32 PowerUpIni(int32 Para);
	protected:
		virtual int32 OneLoop();
		SptCheckTask();
	private:
		uint32 checkInstNum;
		CheckAppInst* checkInst[40];
	};

}

#endif // !SPTCHECKTASK_H

