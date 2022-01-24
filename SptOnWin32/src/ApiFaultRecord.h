#ifndef APIFAULTRECORD_H
#define APIFAULTRECORD_H

namespace spt
{
	/// <summary>
	/// 故障录波数字量
	/// </summary>
	class ApiFwDigital :protected SalFwDigitalCfgSignal
	{
	public:
		/// <summary>
		/// 故障录波数字量初始化
		/// </summary>
		/// <param name="Name">名称</param>
		/// <param name="DesName">描述地址</param>
		/// <param name="Group">组别</param>
		/// <param name="Phase">相别</param>
		/// <param name="Ccbm">一次设备描述</param>
		/// <param name="SteadyState">稳态值</param>
		/// <param name="Flag">SalFwWaveCfgCell::uFlags</param>
		/// <param name="UpBeforeSetCnt">上升沿前录波点数,不含变位的点,必须小于等于ApiFwRecordGroup的UpBeforeSetCnt</param>
		/// <param name="UpAfterSetCnt">上升沿后录波点数,含变位的点</param>
		/// <param name="DownBeforeSetCnt">下降沿前录波点数,不含变位的点,必须小于等于ApiFwRecordGroup的UpBeforeSetCnt</param>
		/// <param name="DownAfterSetCnt">下降沿后录波点数,含变位的点</param>
		/// <param name="IsDisp">是否显示</param>
		void PowerUpIni(const char* Name, const char* DesName, class  ApiFwRecordGroup& Group, E_Ang_Phase Phase, const char* Ccbm, bool8 SteadyState, uint32 Flag, uint16 UpBeforeSetCnt, uint16 UpAfterSetCnt, uint16 DownBeforeSetCnt, uint16 DownAfterSetCnt, bool8 IsDisp);
		/// <summary>
		/// 数据更新
		/// </summary>
		/// <param name="Value">1代表值，其他为0</param>
		void Update(uint32 Value);
		/// <summary>
		/// 设置是否显示
		/// </summary>
		/// <param name="Disp"></param>
		void SetDisp(bool8 Disp);
	};
	/// <summary>
	/// 故障录波模拟量
	/// </summary>
	class ApiFwAnalog :protected SalFwAnalogCfgSignal
	{
	public:
		/// <summary>
		/// 故障录波模拟量初始化
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="Group"></param>
		/// <param name="Phase">相别</param>
		/// <param name="Ccbm">一次描述</param>
		/// <param name="Units">单位</param>
		/// <param name="Skew">通道迟滞</param>
		/// <param name="CoeA">转换系数CoeA</param>
		/// <param name="CoeB">转换系数CoeB</param>
		/// <param name="Primary">一次系数</param>
		/// <param name="Secondary">二次系数</param>
		/// <param name="IsPrimary">是否为一次值</param>
		/// <param name="Flag">SalFwWaveCfgCell::uFlags</param>
		/// <param name="IsDisp"></param>
		void PowerUpIni(const char* Name, const char* DesName, class  ApiFwRecordGroup& Group, E_Ang_Phase Phase, const char* Ccbm, const VarUnits& Units, float32 Skew, float32 CoeA, float32 CoeB, float32 Primary, float32 Secondary, bool8 IsPrimary, uint32 Flag, bool8 IsDisp);
		/// <summary>
		/// 数据更新
		/// </summary>
		/// <param name="Value"></param>
		void Update(float32 Value);
		/// <summary>
		/// 设置系数
		/// </summary>
		/// <param name="Primary">一次系数</param>
		/// <param name="Secondary">二次系数</param>
		void SetCoePS(float32 Primary, float32 Secondary);
		/// <summary>
		/// 设置是否显示
		/// </summary>
		/// <param name="Disp"></param>
		void SetDisp(bool8 Disp);
	};
	/// <summary>
	/// 故障简报事项
	/// </summary>
	class ApiFwEvent : protected SalFwEventCfgSignal
	{
	public:
		/// <summary>
		/// 故障简报事项初始化
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="Event"></param>
		/// <param name="Group"></param>
		/// <param name="Phase"></param>
		/// <param name="Ccbm"></param>
		/// <param name="SteadyState">稳态值</param>
		/// <param name="Flag">SalFwWaveCfgCell::uFlags</param>
		/// <param name="UpBeforeSetCnt">上升沿前录波点数,不含变位的点,必须小于等于ApiFwRecordGroup的UpBeforeSetCnt</param>
		/// <param name="UpAfterSetCnt">上升沿后录波点数,含变位的点</param>
		/// <param name="DownBeforeSetCnt">下降沿前录波点数,不含变位的点,必须小于等于ApiFwRecordGroup的UpBeforeSetCnt</param>
		/// <param name="DownAfterSetCnt">下降沿后录波点数,含变位的点</param>
		/// <param name="IsDisp"></param>
		void PowerUpIni(const char* Name, const char* DesName, ApiEvent& Event, class ApiFwRecordGroup& Group, E_Ang_Phase Phase, const char* Ccbm, bool8 SteadyState, uint32 Flag, uint16 UpBeforeSetCnt, uint16 UpAfterSetCnt, uint16 DownBeforeSetCnt, uint16 DownAfterSetCnt, bool8 IsDisp);
		/// <summary>
		/// 设置是否显示
		/// </summary>
		/// <param name="Disp"></param>
		void SetDisp(bool8 Disp);
	};
	/// <summary>
	/// 故障录波
	/// </summary>
	class ApiFwRecordGroup :protected SalFwRecordGroup
	{
	public:
		/// <summary>
		/// 故障录波初始化
		/// 系统频率、采样评率在ApiAppCfg中设置
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="SysFreq">系统稳态频率</param>
		/// <param name="SampPerCircle">每周波采样率</param>
		/// <param name="MaxRecordPoint">一组录波最大点数,每段之间的压缩段点数按照60点计算</param>
		/// <param name="UpBeforeSetCnt">开始录波信号上升沿前录波点数,必须大于所有的数字量的前向录波点数,必须小于MaxRecordPoint</param>
		/// <param name="UpAfterSetCnt">开始录波信号上升沿后录波点数,必须小于MaxRecordPoint</param>
		/// <param name="FwAngMaxNum">模拟量最大数</param>
		/// <param name="FwDigMaxNum">数字量最大数</param>
		/// <param name="FwEventMaxNum">事项定义最大数</param>
		/// <param name="Flag">SalFwRecordGroup::Flags</param>
		void PowerUpIni(const char* Name, const char* DesName, uint32 SysFreq, uint32 SampPerCircle, int32 MaxRecordPoint, uint16 UpBeforeSetCnt, uint16 UpAfterSetCnt, uint16 FwAngMaxNum, uint16 FwDigMaxNum, uint16 FwEventMaxNum, uint32 Flag);
		/// <summary>
		/// 启动录波
		/// </summary>
		/// <param name="isStart"></param>
		void StartRecord(bool8 isStart);
		/// <summary>
		/// 记录一点录波
		/// 必须在所有的数值更新完成之后进行调用
		/// 必须在StartRecord之后调用
		/// </summary>
		/// <param name="stamp">当前录波UTC时标</param>
		/// <param name="SampStamp">当前录波绝对时标</param>
		void RecordOnePoint(SalDateStamp& stamp, uint64 SampStamp);
		/// <summary>
		/// 设置关联的参数
		/// </summary>
		/// <param name="Index">由0开始，最大为3</param>
		/// <param name="Group"></param>
		/// <returns></returns>
		int32 SetParaGroup(int32 Index, ApiParaGroup* Group);
		/// <summary>
		/// 设置动作类型
		/// 必须在开始录波后，结束录波前进行设置
		/// </summary>
		/// <param name="Type">SalFwData::ActStatus</param>
		/// <returns></returns>
		int32 SetActType(uint32 Type);
		/// <summary>
		/// 清空录波
		/// </summary>
		void ClearRecord();
	};
}

#endif // !APIFAULTRECORD_H

