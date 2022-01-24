#ifndef APIDIO_H
#define APIDIO_H
namespace spt
{
	/** @defgroup ApiIOStateIO
	* 状态量输入输出模块
	* @{
	*/

	//常规开入板卡
	class ApiBoardNormalStateIn :protected SptNormalStateInBoard
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint16 CardType, uint16 CardAddr, uint16 FrameIndex);
		//变位序号，每次变位+1(未去颤)
		uint32 StateNum();
		//变位时间,未去颤
		const SalDateStamp& Stamp();
		//开入位串值,未去颤的实时状态值
		//InNo,板卡开入的32位位串号
		uint32 Bit32(uint32 InNo);
		//开入位串值,未去颤的实时状态值
		//Index 采样值序号，0代表当前点，1代表上一点，依次类推
		//InNo,板卡开入的32位位串号
		uint32 Bit32(uint32 Index, uint32 InNo);
		//变位时间
		// Index 采样值序号，0代表当前点，1代表上一点，依次类推
		const SalDateStamp& Stamp(uint32 Index);
		//自检状态
		const struct stOutStatus* CheckStatus() { return &ostatus; };
	protected:

	};
	//常规开入
	class ApiNormalBoolIn :protected SptNormalStateInCell
	{
	public:
		//Name信号名称
		//DesName虚端子
		//InNo开入序号，由0开始
		void PowerUpIni(class ApiBoardNormalStateIn& Board, const char* Name, const char* DesName, uint16 InNo);
		//变位序号，每次变位+1(未去颤)
		uint32 StateNum();
		bool8 Value();
		// Index 采样值序号，0代表当前点，1代表上一点，依次类推
		bool8 Value(uint32 Index);
		//变位时间,未去颤
		const SalDateStamp& Stamp();
		// Index 采样值序号，0代表当前点，1代表上一点，依次类推
		const SalDateStamp& Stamp(uint32 Index);
		//信号强置状态，此时输入量不再以硬件为准，输出量不再以应用为准，而是调试软件强置、HMI进行强置
		bool8 SignalForce() { return blsignalForce; };
	};
	//常规开出板卡
	class ApiBoardNormalStateOut :protected SptNormalStateOutBoard
	{
	public:
		//CardAddr 板卡地址
		//FrameNo 在DO帧里面的位移，从0开始
		void PowerUpIni(const char* Name, const char* DesName, uint16 CardType, uint16 CardAddr, uint16 FrameIndex);
		/// <summary>
		/// 开出变位时间
		/// </summary>
		/// <returns></returns>
		const SalDateStamp& Stamp();
		/// <summary>
		/// 反校状态的接收时间
		/// </summary>
		/// <returns></returns>
		const SalDateStamp& StateStamp();
		//开入位串值
		//InNo,板卡开出的32位位串号,反校信息
		uint32 VerfyCode(uint32 InNo);
		//VerfyCode 变位时加一
		uint32 VerfyCodeNum();
		//自检状态
		const struct stOutStatus* CheckStatus() { return &ostatus; };
	};
	//常规开出
	class ApiNormalBoolOut :protected SptNormalStateOutCell
	{
	public:
		//保护出口
		//Name信号名称
		//DesName虚端子
		//InNo开出序号，由0开始
		void ProtOutPowerUpIni(class ApiBoardNormalStateOut& Board, const char* Name, const char* DesName, uint16 InNo);
		//保护启动
		//Name信号名称
		//DesName虚端子
		//InNo开出序号，由0开始
		void ProtStartPowerUpIni(class ApiBoardNormalStateOut& Board, const char* Name, const char* DesName);
		//信号出口
		//Name信号名称
		//DesName虚端子
		//InNo开出序号，由0开始
		void SignalPowerUpIni(class ApiBoardNormalStateOut& Board, const char* Name, const char* DesName, uint16 InNo);
		void SetValue(bool8 Val);
		bool8 Value();
		uint32 VerfyCode();//反校信息
		//变位时间
		const SalDateStamp& Stamp();
		//信号强置状态，此时输入量不再以硬件为准，输出量不再以应用为准，而是调试软件强置、HMI进行强置
		bool8 SignalForce() { return blsignalForce; };
	};

	/// <summary>
	/// 常规直流量输入
	/// </summary>
	class ApiBoardNormalDcIn :protected SptNormalDcInBoard
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint16 CardType, uint16 CardAddr, uint16 FrameIndex, uint32 ElementNum);
		/// <summary>
		/// 采样时间
		/// </summary>
		/// <returns></returns>
		const SalDateStamp& Stamp();
		uint32 StateNum();
		/// <summary>
		/// 自检状态
		/// </summary>
		const struct stOutStatus* CheckStatus() { return &ostatus; };
		/// <summary>
		/// 板卡温度
		/// </summary>
		/// <returns></returns>
		uint16 Temperature();
	};
	//常规直流量输入
	class ApiNormalDcIn :protected SptNormalDcIn
	{
	public:
		//Name信号名称
		//DesName虚端子
		//InNo开入序号，由0开始
		void PowerUpIni(class ApiBoardNormalDcIn& Board, const char* Name, const char* DesName, uint16 InNo, const VarUnits& Units);
		int32 Value();
		//信号强置状态，此时输入量不再以硬件为准，输出量不再以应用为准，而是调试软件强置、HMI强置
		bool8 SignalForce() { return blsignalForce; };
	protected:

	};
	//Goose开入帧
	class ApiGoInFrame :protected SptGooseFrameIn
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint16 InNo, uint16 ElementNum);
		/// <summary>
		/// FPGA发送的GOOSE开入数据帧输入
		/// </summary>
		/// <returns></returns>
		uint32 PosFrameNum();
		/// <summary>
		/// FPGA发送的GOOSE模拟量数据帧个数
		/// </summary>
		/// <returns></returns>
		uint32 AngFrameNum();
		/// <summary>
		/// GOOSE帧变位时间
		/// </summary>
		/// <returns></returns>
		const SalDateStamp& FrameStamp();

	};
	//Goose开入控制块
	class ApiGoInCb :protected SptGooseDataSetIn
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, ApiGoInFrame& Frame, uint16 ElementNum);
		//自检状态
		const struct stOutStatus* CheckStatus() { return &ostatus; };
		/// <summary>
		/// A口状态
		/// </summary>
		/// <returns></returns>
		uint32 StateA();
		/// <summary>
		/// B口状态
		/// </summary>
		/// <returns></returns>
		uint32 StateB();
		// 配置异常
		bool8 CfgErr();
		// 解析异常
		bool8 ParseErr();
		/// <summary>
		/// CCD解析信息
		/// </summary>
		/// <returns>0,if parse err.</returns>
		struct GooseGocbInfo* GoCbInfo();
	};
	//Goose开入
	class ApiGoIn :protected SptGooseDataIn
	{
	public:
		//是否接收Q
		bool8 IsQLinked();
		//是否接收T
		bool8 IsTLinked();
		//是否接收V
		bool8 IsVLinked();
		//变位时间
		const SalDateStamp& Stamp();
		uint32 Q();
		//变位序号，每次变位+1(未去颤)
		uint32 StateNum();
		//该Goose所属的控制块，未订阅则为空
		const ApiGoInCb* GoCb();
		//信号强置状态，此时输入量不再以硬件为准，输出量不再以应用为准，而是调试软件强置、HMI强置
		bool8 SignalForce() { return blsignalForce; };
	protected:
		void PowerUpIni(const char* Name, const char* DesName, SptGooseFrameIn* Board, uint32 Type, uint16 InNo);
	};
	//Goose单点位置信息
	class ApiGoPosIn :public ApiGoIn
	{
	public:
		//Name信号名称
		//DesName虚端子
		//InNo开入序号，由0开始
		void PowerUpIni(const char* Name, const char* DesName, ApiGoInFrame& Frame, uint16 InNo);
		bool8 Value();
	};
	//Goose双点位置信息
	class ApiGoDpPosIn :public ApiGoIn
	{
	public:
		//Name信号名称
		//DesName虚端子
		//InNo开入序号，由0开始
		void PowerUpIni(const char* Name, const char* DesName, ApiGoInFrame& Frame, uint16 InNo);
		uint32 Value();

	};
	//Goose浮点开入
	class ApiDigFloatIn :public ApiGoIn
	{
	public:
		//Name信号名称
		//DesName虚端子
		//InNo开入序号，由0开始
		void PowerUpIni(const char* Name, const char* DesName, ApiGoInFrame& Frame, uint16 InNo);
		float32 Value();
	};
	//Goose32位Int输入
	class ApiDigInt32In :public ApiGoIn
	{
	public:
		//Name信号名称
		//DesName虚端子
		//InNo开入序号，由0开始
		void PowerUpIni(const char* Name, const char* DesName, ApiGoInFrame& Frame, uint16 InNo);
		int32 Value();
	};
	//Goose32位Uint输入
	class ApiDigUInt32In :public ApiGoIn
	{
	public:
		//Name信号名称
		//DesName虚端子
		//InNo开入序号，由0开始
		void PowerUpIni(const char* Name, const char* DesName, ApiGoInFrame& Frame, uint16 InNo);
		uint32 Value();
	};
	//Goose开出帧
	class ApiGoOutFrame :protected SptGooseFrameOut
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint16 InNo, uint16 ElementNum);
	};
	//Goose数据集
	class ApiGoOutDataSet :protected SptGooseDataSetOut
	{
	public:
		//CardAddr 允许接收的第一块板卡编号，A为0，B为1，依次类推。如果需要在多块板卡上接收则设置EnableCardAddr
		void PowerUpIni(const char* Name, const char* OutName, const char* DesName, ApiGoOutFrame& Frame, uint16 ElementNum);
		// 配置异常
		bool8 CfgErr();
		// 解析异常
		bool8 ParseErr();
		/// <summary>
		/// CCD解析信息
		/// </summary>
		/// <returns>0,if parse err.</returns>
		struct GooseGocbInfo* GoCbInfo();
	};
	//Goose开出
	class ApiGoOut :protected SptGooseDataOut
	{
	public:
		//GOOSE发送类型虚端子类型，只有IsVLinked为1时才有意义
		//具体类型参见枚举GoSvDataType
		GoSvDataType GoValueType();
		//是否接收Q
		bool8 IsQLinked();
		//是否接收T
		bool8 IsTLinked();
		//是否接收V
		bool8 IsVLinked();
		//该Goose所属的控制块，未订阅则为空
		const ApiGoOutDataSet* GoCb();
		//品质
		void SetQ(uint32 Q);
		//变位时间,发送GOOOSE如果设置了t则使用应用设置的t,如果应用未设置则使用系统时间
		void SetStamp(SalDateStamp& stamp);
		void SetValue(u32value Val);
		const SalDateStamp& Stamp();
		uint32 Q();
		//信号强置状态，此时输入量不再以硬件为准，输出量不再以应用为准，而是调试软件强置、HMI强置
		bool8 SignalForce() { return blsignalForce; };
	protected:
		void PowerUpIni(const char* Name, const char* DesName, SptGooseFrameOut* Board, uint32 Type, uint16 OutNo);
	};
	//Goose单点位置信息
	class ApiGoPosOut :public ApiGoOut
	{
	public:
		//Name信号名称
		//DesName虚端子
		//OutNo开入序号，由0开始
		void PowerUpIni(const char* Name, const char* DesName, ApiGoOutFrame& Board, uint16 OutNo);
		void SetValue(uint32 Val);
		uint32 Value();
		//以下函数继承自父类，应用层可以直接调用
		//品质
		//void SetQ(uint32 Q);
		//变位时间
		//void SetStamp(SalDateStamp& stamp);
		//const SalDateStamp& Stamp();
		//uint32 Q();
	};
	//Goose双点位置信息
	class ApiGoDpPosOut :public ApiGoOut
	{
	public:
		//Name信号名称
		//DesName虚端子
		//OutNo开入序号，由0开始
		void PowerUpIni(const char* Name, const char* DesName, ApiGoOutFrame& Board, uint16 OutNo);
		void SetValue(uint32 Val);
		uint32 Value();
		//以下函数继承自父类，应用层可以直接调用
		//品质
		//void SetQ(uint32 Q);
		//变位时间
		//void SetStamp(SalDateStamp& stamp);
		//const SalDateStamp& Stamp();
		//uint32 Q();
	};
	//Goose浮点开出
	class ApiGoFloatOut :public ApiGoOut
	{
	public:
		//Name信号名称
		//DesName虚端子
		//OutNo开入序号，由0开始
		void PowerUpIni(const char* Name, const char* DesName, ApiGoOutFrame& Board, uint16 OutNo);
		//变位时间
		void SetValue(float32 Val);
		float32 Value();
		//以下函数继承自父类，应用层可以直接调用
		//品质
		//void SetQ(uint32 Q);
		//变位时间
		//void SetStamp(SalDateStamp& stamp);
		//const SalDateStamp& Stamp();
		//uint32 Q();
	};
	//Goose32位开出
	class ApiGoInt32Out :public ApiGoOut
	{
	public:
		//Name信号名称
		//DesName虚端子
		//OutNo开入序号，由0开始
		void PowerUpIni(const char* Name, const char* DesName, ApiGoOutFrame& Board, uint16 OutNo);
		/// <summary>
		/// 设置GOOSE值
		/// </summary>
		/// <param name="Val"></param>
		void SetValue(int32 Val);
		int32 Value();
		//以下函数继承自父类，应用层可以直接调用
		//品质
		//void SetQ(uint32 Q);
		//变位时间
		//void SetStamp(SalDateStamp& stamp);
		//const SalDateStamp& Stamp();
		//uint32 Q();
	};
	class ApiGoUInt32Out :public ApiGoOut
	{
	public:
		//Name信号名称
		//DesName虚端子
		//OutNo开入序号，由0开始
		void PowerUpIni(const char* Name, const char* DesName, ApiGoOutFrame& Board, uint16 OutNo);
		//变位时间
		void SetValue(uint32 Val);
		uint32 Value();
		//以下函数继承自父类，应用层可以直接调用
		//品质
		//void SetQ(uint32 Q);
		//变位时间
		//void SetStamp(SalDateStamp& stamp);
		//const SalDateStamp& Stamp();
		//uint32 Q();
	};
	class ApiGoUnion32Out :public ApiGoOut
	{
	public:
		//Name信号名称
		//DesName虚端子
		//OutNo开入序号，由0开始
		void PowerUpIni(const char* Name, const char* DesName, ApiGoOutFrame& Board, uint16 OutNo);
		//变位时间
		void SetValue(u32value Val);
		u32value Value();
		//以下函数继承自父类，应用层可以直接调用
		//品质
		//void SetQ(uint32 Q);
		//变位时间
		//void SetStamp(SalDateStamp& stamp);
		//const SalDateStamp& Stamp();
		//uint32 Q();
	};
	/** @} */ // end of ApiIOStateIO
}

#endif // !APIDIO_H

