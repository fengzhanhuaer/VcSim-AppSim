#ifndef  APIAIO_H
#define APIAIO_H
namespace spt
{
	/** @defgroup ApiIOAnalogIO
	* 模拟量输入输出模块
	* @{
	*/
	/// <summary>
	/// 模拟量输入帧管理类
	/// </summary>
	class ApiBoardAngFrameIn :protected SptAngVirInputBoard
	{
	public:
		/// <summary>
		/// 输入模拟量帧上电初始化
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="FrameNo"></param>
		/// <param name="ElementNum">元素数目</param>
		/// <param name="AdNum">AD的数目</param>
		/// <param name="AdNodeNum">每个AD有效管脚的数目</param>
		void PowerUpIni(const char* Name, const char* DesName, uint16 FrameNo, uint16 ElementNum, uint32 AdNum, uint8 AdNodeNum);
		/// <summary>
		/// 采样序号
		/// </summary>
		/// <returns></returns>
		uint32 StateNum();
		void SetOutValue(uint32 Index, int32 Value);
		/// <summary>
		/// 按照输入帧的顺序设置Coe，注:与AD顺序不一定一致，AD系数设置参见ApiNormalAngIn::SetAdCoe
		/// </summary>
		/// <param name="Index"></param>
		/// <param name="Value"></param>
		void SetOutCoe(uint32 Index, uint32 Value);
		/// <summary>
		/// 设置AD校准系数
		/// </summary>
		/// <param name="ADIndex">AD编号</param>
		/// <param name="AdNode">AD端子号</param>
		/// <param name="Value"></param>
		void SetOutCoe(uint32 ADIndex, uint32 AdNode, uint32 Value);
		/// <summary>
		/// 设置AD微调系数
		/// </summary>
		/// <param name="AdNo"></param>
		/// <param name="Index"></param>
		/// <param name="Value"></param>
		void SetADAdJust(uint32 AdNo, uint32 Index, uint32 Value);
		/// <summary>
		/// 设置AD直流微调系数
		/// </summary>
		/// <param name="AdNo"></param>
		/// <param name="Index"></param>
		/// <param name="Value"></param>
		void SetAdDcAdJust(uint32 AdNo, uint32 Index, int32 Value);
		/// <summary>
		/// 设置发送的Q值
		/// </summary>
		/// <param name="Index"></param>
		/// <param name="Value"></param>
		void SetOutQ(uint32 Index, uint32 Value);
		/// <summary>
		/// 自检状态
		/// </summary>
		const struct stOutStatus* CheckStatus() { return &ostatus; };
	};
	/// <summary>
	/// 常规模拟量输入板卡
	/// </summary>
	class ApiBoardNormalAngIn :protected SptNormalAngInBoard
	{
	public:
		/// <summary>
		/// 上电初始化
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="Frame"></param>
		/// <param name="CardType"></param>
		/// <param name="CardAddr"></param>
		void PowerUpIni(const char* Name, const char* DesName, ApiBoardAngFrameIn& Frame, uint16 CardType, uint16 CardAddr);
		/// <summary>
		/// 自检状态
		/// </summary>
		const struct stOutStatus* CheckStatus() { return &ostatus; };
	};
	/// <summary>
	/// 常规模拟量输入
	/// </summary>
	class ApiNormalAngIn :protected SptNormalAngSampCell
	{
	public:
		/// <summary>
		/// 上电初始化
		/// </summary>
		/// <param name="Board"></param>
		/// <param name="Name">信号名称</param>
		/// <param name="DesName">虚端子</param>
		/// <param name="Node">开入序号，在单板卡的中节点序号值，由0开始</param>
		/// <param name="AdIndex">AD号</param>
		/// <param name="AdNode">AD端子号</param>
		/// <param name="Units"></param>
		void PowerUpIni(class ApiBoardNormalAngIn& Board, const char* Name, const char* DesName, uint16 Node, uint16 AdIndex, uint16 AdNode, const VarUnits& Units);
		int32 Value();
		int32 Value(uint32 Index);
		/// <summary>
		/// 设置AD校准系数
		/// </summary>
		/// <param name="Value"></param>
		void SetAdCoe(uint32 Value);
		/// <summary>
		/// 采样序号
		/// </summary>
		/// <returns></returns>
		uint32 StateNum();
		/// <summary>
		/// 设置反极性
		/// </summary>
		/// <param name="Flag"></param>
		/// <returns></returns>
		bool8 SetReversal(bool8 Flag);
		/// <summary>
		/// 设置单AD标志
		/// </summary>
		/// <param name="IsSingle"></param>
		/// <returns></returns>
		bool8 SetSingleAdFlag(bool8 IsSingle);
	};
	/** @brief SV开入数据集 */
	class ApiSvInVirBoard : protected SptSvInDataSet
	{
	public:
		//ElementNum虚拟板卡元素个数
		void PowerUpIni(const char* Name, const char* DesName, ApiBoardAngFrameIn& Frame, uint16 ElementNum);
		bool8 IsEnable();
		/// <summary>
		/// 自检状态
		/// </summary>
		const struct stOutStatus* CheckStatus() { return &ostatus; };
		/// <summary>
		/// 配置异常
		/// </summary>
		/// <returns></returns>
		bool8 CfgErr();
		/// <summary>
		/// 解析异常
		/// </summary>
		/// <returns></returns>
		bool8 ParseErr();
		/// <summary>
		/// CCD解析信息
		/// </summary>
		/// <returns>0,if parse err.</returns>
		struct SVcbInfo* SvCbInfo();
	};
	/// <summary>
	/// SV输入信息
	/// </summary>
	class ApiSvIn : protected SptSampAng_9_2SampCell
	{
	public:
		//Name信号名称
		//DesName虚端子
		//Node开入序号，在单板卡的中节点序号值，由0开始
		//FrameIndex，在开入帧里面的顺序号
		void PowerUpIni(class ApiBoardAngFrameIn& Board, const char* Name, const char* DesName, uint16 Node, const VarUnits& Units);
		//虚端子是否连接
		bool8 IsLinked();
		uint16 FrameIndex();
		uint16 Node();
		int32 Value();
		/**
		 * @brief 获取ApiSvIn数据值.
		 *
		 * \param Index 0带当前值，1代表上一点，依次类推
		 * \return
		 */
		int32 Value(uint32 Index);
		uint32 Q();
		uint32 Q(uint32 Index);
		//采样序号
		uint32 StateNum();
		//设置反极性
		bool8 SetReversal(bool8 Flag);
		ApiSvInVirBoard* DataSet();
	};
	/// <summary>
	/// 板间SV输入信息
	/// </summary>
	class ApiBoardCmmSvIn : protected SptSampAng_9_2SampCell
	{
	public:
		//Name信号名称
		//DesName虚端子
		//Node开入序号，在单板卡的中节点序号值，由0开始
		//FrameIndex，在开入帧里面的顺序号
		void PowerUpIni(class ApiBoardAngFrameIn& Board, const char* Name, const char* DesName, uint16 Node, const VarUnits& Units);
		int32 Value();
		int32 Value(uint32 Index);
		uint32 Q();
		uint32 Q(uint32 Index);
		//采样序号
		uint32 StateNum();
		//设置反极性
		bool8 SetReversal(bool8 Flag);
		/// <summary>
		/// 设置连接状态
		/// </summary>
		/// <param name="Flag">是否使能</param>
		/// <param name="SvCbIndex">控制块编号</param>
		/// <param name="SvCbNode">控制块中的偏移</param>
		void SetNodeLinkFlag(bool8 Flag, uint16 SvCbIndex, uint16 SvCbNode);
	};
	/// <summary>
	/// 模拟量输出虚拟板卡
	/// </summary>
	class ApiBoardAngFrameOut :protected SptAngVirOutputBoard
	{
	public:
		//ElementNum 元素数目
		void PowerUpIni(const char* Name, const char* DesName, uint16 FrameNo, uint16 ElementNum);
	};
	/// <summary>
	/// SV输出信息
	/// </summary>
	class ApiSvOut : protected SptSampAng_9_2SampCell
	{
	public:
		//Name信号名称
		//DesName虚端子
		void PowerUpIni(class ApiBoardAngFrameOut& Board, const char* Name, const char* DesName, const VarUnits& Units);
		//虚端子连接是否正常
		bool8 IsNodeLinkOk();
		//虚端子在输出数据集中的位置
		uint16 Node();
	};
	/// <summary>
	/// SV开出数据集
	/// </summary>
	class ApiSvOutVirDataSet : protected SptSvOutDataSet
	{
	public:
		//ElementNum虚拟板卡元素个数
		//Delay额定延时
		void PowerUpIni(const char* Name, const char* OutName, const char* DesName, ApiBoardAngFrameOut& Frame, uint32 Delay, uint16 FrameIndex, uint16 ElementNum);
		//DataSet数据集的个数
		uint32 DataSetCellNum();
		//设置发送数据挑数表
		void SetOutSelIndex(uint32 Index, uint32 SelIndex);
		//获取发送数据挑数表
		uint32 GetOutSelIndex(uint32 Index);
		// 配置异常
		bool8 CfgErr();
		// 解析异常
		bool8 ParseErr();
		/// <summary>
		/// CCD解析信息
		/// </summary>
		/// <returns>0,if parse err.</returns>
		struct SVcbInfo* SvCbInfo();
		/// <summary>
		/// 设置额定延时
		/// </summary>
		/// <param name="DealyUs"></param>
		void SetDealy(uint16 DealyUs);
	};
	/// <summary>
	/// 板间传输SV输出信息
	/// </summary>
	class ApiBoardCmmSv : protected SptSampAng_9_2SampCell
	{
	public:
		//Name信号名称
		//DesName虚端子
		//Node开入序号，在单板卡的中节点序号值，由0开始
		//FrameIndex，在开入帧里面的顺序号
		void PowerUpIni(class ApiBoardCmmSvOutVirDataSet& Board, const char* Name, const char* DesName, const VarUnits& Units);
	};
	/// <summary>
	/// 板间SV开出数据集
	/// </summary>
	class ApiBoardCmmSvOutVirDataSet : protected SptSvOutDataSet
	{
	public:
		//ElementNum虚拟板卡元素个数
		//Delay额定延时
		void PowerUpIni(const char* Name, const char* OutName, const char* DesName, ApiBoardAngFrameOut& Frame, uint16 FrameIndex, uint16 ElementNum);
		uint32 DataSetCellNum();
		/// <summary>
		/// 设置发送数据挑数表
		/// </summary>
		/// <param name="Index"></param>
		/// <param name="SelIndex"></param>
		void SetOutSelIndex(uint32 Index, uint32 SelIndex);
	};
	/// <summary>
	/// 模拟量有效值组
	/// </summary>
	class ApiAngRmsGroup :protected SalAngRmsGroup
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint16 EventNum, uint32 BufLen);
		/// <summary>
		///  更新模拟量有效值 
		/// </summary>
		/// <param name="AdJustAngle">是否自动校正角度</param>
		void Update(bool8 AdJustAngle);
	};
	/// <summary>
	/// 模拟量有效值
	/// </summary>
	class ApiAngRms :protected SalAngRms
	{
	public:
		//二元量，如电流
		//IsBase 是否为本组的角度基准数据
		//QLen 品质位字节宽度,无品质位则填0
		void PowerUpIni(const char* Name, const char* DesName, ApiAngRmsGroup& Group, bool8 IsBase, uint16 Data1DotNum, const VarUnits& Units1, uint16 Data2DotNum, const VarUnits& Units2, uint8 QLen);
		//一元量，如频率
		void PowerUpIni(const char* Name, const char* DesName, ApiAngRmsGroup& Group, uint16 Data1DotNum, const VarUnits& Units1, uint8 QLen);
		//设置模拟量变换的后的单位
		void SetDataUnit(const VarUnits& Units1, const VarUnits& Units2);
		//是否显示
		void SetDisp(bool8 Disp);
		// 设置模拟量变换的系数
		void SetDataCoe(float32 Data1Coe1, float32 Data2Coe);
		//输入数据
		bool8 PushData(int32 Data1, int32 Data2, uint32 Q);
		//输入向量数据，平台转为幅角值存储,其中角度以Data2的小数位数存储
		bool8 PushVectData(int32 Real, int32 Img, uint32 Q);
		//输入数据
		bool8 PushData(int32 Data1, int32 Data2);
		//输入向量数据，平台转为幅角值存储,其中角度以Data2的小数位数存储
		bool8 PushVectData(int32 Real, int32 Img);
	};
	/// <summary>
	/// 全局Io交互标志
	/// </summary>
	class ApiIoGlobalFlag
	{
	public:
		/// <summary>
		/// 重置分板卡状态
		/// 对于采执装置：重新下发板卡配置帧
		/// </summary>
		void ResetSubBoardState();
		/// <summary>
		/// 状态信号
		/// </summary>
		/// <returns></returns>
		const tsAppFlags& AppFlags() { return *appFlags; }
		/// <summary>
		/// 使能SV发送
		/// </summary>
		/// <param name="Enable"></param>
		void EnableSVSend(bool8 Enable);
		/// <summary>
		/// 飞点处理
		/// </summary>
		/// <param name="Enable"></param>
		void EnableAngErrPointDeal(bool8 Enable);
		/// <summary>
		/// 使能GO发送
		/// </summary>
		/// <param name="Enable"></param>
		void EnableGoSend(bool8 Enable);
		/// <summary>
		/// 测控远方状态
		/// </summary>
		/// <param name="Flag"></param>
		/// <returns></returns>
		bool8 SetCkRemoteState(bool8 Flag);
		/// <summary>
		/// 保护远方状态
		/// </summary>
		/// <param name="Flag"></param>
		/// <returns></returns>
		bool8 SetProtRemoteState(bool8 Flag);
		/// <summary>
		/// 检修状态
		/// </summary>
		/// <param name="Flag"></param>
		/// <returns></returns>
		bool8 SetUnitTestState(bool8 Flag);
		/// <summary>
		/// 调试状态
		/// </summary>
		/// <param name="Flag"></param>
		/// <returns></returns>
		bool8 SetUnitDebugState(bool8 Flag);
		/// <summary>
		/// 应用启动完成标志
		/// </summary>
		/// <param name="Flag"></param>
		/// <returns></returns>
		bool8 SetAppPowerUpIniOver(bool8 Flag);
		/// <summary>
		/// 设置装置复归标志（平台自动展宽200ms）
		/// </summary>
		/// <param name="Flag"></param>
		/// <returns></returns>
		bool8 SetUnitRevert(bool8 Flag);
		/// <summary>
		/// 获取FPGA工作的慢速状态
		/// </summary>
		/// <param name="Index">
		/// AEU装置:0 板卡地址 1 丛板卡判断通讯中断的状态
		/// </param>
		/// <returns></returns>
		uint8 GetFpagSlowFlags(uint16 Index);
		/// <summary>
		/// 板卡在线状态
		/// </summary>
		/// <returns></returns>
		uint32 BoardOnLineState();
		/// <summary>
		/// 平台自有的实时状态标志
		/// </summary>
		/// <returns></returns>
		const SptFlags& SptFlag();
	public:
		static ApiIoGlobalFlag& Instance();
	protected:
		ApiIoGlobalFlag();
	private:
		SptIoProcess& sptIoProcess;
		SptCcdFile::OutStatus ccdstatus;
		tsAppFlags* appFlags;
	};
	/** @} */ // end of ApiIOAnalogIO
}


#endif // ! APIAIO_H

