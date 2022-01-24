#ifndef SPTAPPFLAGS_H
#define SPTAPPFLAGS_H

namespace spt
{
	typedef struct stAppFlags
	{
		/// <summary>
		/// 测控远方状态
		/// </summary>
		bool8 ckRemoteState;
		/// <summary>
		/// 保护远方状态
		/// </summary>
		bool8 protRemoteState;
		/// <summary>
		/// 装置检修状态
		/// </summary>
		bool8 unitTestState;
		/// <summary>
		/// 装置调试状态
		/// </summary>
		bool8 unitDebugState;
		/// <summary>
		/// 装置初始化完成进入工作状态
		/// </summary>
		bool8 blAppPowerUpIniOver;
		/// <summary>
		/// 装置界面复归(固定展宽200ms)
		/// </summary>
		bool8 blFaceRevert;
		/// <summary>
		/// 装置复归(固定展宽2000ms),由应用进行设置
		/// </summary>
		bool8 blUnitRevert;
	}tsAppFlags;
	class SptFlags
	{
	public:
		/// <summary>
		/// 装置掉电信号
		/// 20ms确认，5ms返回
		/// 掉电信号持续50ms后，平台开始开始陆续闭锁事项存储、定值存储等功能
		/// </summary>
		bool8 PowerDownFlags()const { return powerDownFlags; };
		/// <summary>
		/// 掉电信号为1的去颤前开始时间，ms
		/// </summary>
		uint32 PowerDownStartEdgeMs()const { return powerDownStartEdgeMs; };
		/// <summary>
		/// 掉电信号(去颤后)是否在时间范围内
		/// </summary>
		/// <param name="LowLimit">下限时间ms</param>
		/// <param name="HighLimit">上限时间ms</param>
		/// <returns>掉电信号为0时，返回0，掉电信号为1时，判断时间范围</returns>
		bool8 IsPowerDownAtRange(uint32 LowLimit, uint32 HighLimit)const;
		void SptFlagProcess();
	private:
		MsDelayTimer msPowerDownDelayTimer;
		bool8 powerDownFlags;
		uint32 powerDownStartEdgeMs;
	};
}


#endif // !SPTAPPFLAGS_H

