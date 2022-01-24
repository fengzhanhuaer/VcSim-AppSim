#ifndef ApiAppTask_H
#define ApiAppTask_H


namespace spt
{
	class ApiSampAppTask :protected SampAppTask
	{
	public:
		/*
		*TaskName应用程序名称
		*CallBack回调函数
		*Period调用周期,单位为采样点数
		*/
		ApiSampAppTask(const char* TaskName, AppTaskCallBack CallBack, bool8 Enable, uint32 Period);
		/// <summary>
		/// 运行次数,每次调用中断加一
		/// </summary>
		/// <returns></returns>
		uint64 RunCnt();
		/// <summary>
		/// 中断是否使能
		/// </summary>
		/// <returns></returns>
		bool8 IsEnable();
		/// <summary>
		/// 使能中断
		/// </summary>
		/// <param name="En"></param>
		/// <returns></returns>
		bool8 Enable(bool8 En);
		/// <summary>
		/// 清空统计信息
		/// </summary>
		void ClearLoadInfo();
		/// <summary>
		/// 名称
		/// </summary>
		/// <returns></returns>
		const char* Name() { return name; };
		/// <summary>
		/// 运行信息
		/// </summary>
		const struct TaskRunInfo& RunInfo() { return runInfo; }
	};
}




#endif // !ApiAppTask_H

