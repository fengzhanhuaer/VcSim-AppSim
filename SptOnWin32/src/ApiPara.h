#ifndef APIPARA_H
#define APIPARA_H

namespace spt
{
	/// <summary>
	/// 参数管理组
	/// </summary>
	class ApiParaGroup :protected SalParaGroup
	{
	public:
		/// <summary>
		/// 获取参数CRC校验和
		/// </summary>
		/// <param name="Zone"></param>
		/// <returns></returns>
		uint32 GetCrc(uint16 Zone);//获取定值CRC
		uint16 CurZone();//获取当前组号,由0开始
		/// <summary>
		/// 初始化定值组
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="CurZone">由0开始，当前组号</param>
		/// <param name="MaxZone">最大组号，如果只有一组，则填1，最大组号不能超过30</param>
		/// <param name="ElementNum"></param>
		void PowerUpIni(const char* Name, const char* DesName, uint16 CurZone, uint16 MaxZone, uint16 ElementNum);
		/// <summary>
		/// 初始化定值组(仅一组定值)
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="ElementNum"></param>
		void PowerUpIni(const char* Name, const char* DesName, uint16 ElementNum);
		int32 CheckStatus();//1 is ok,others is error.
		int32 CheckStatus(uint16 Zone);//1 is ok,others is error.
		int32 DefaultData();//默认定值
		uint16 DataChangeCnt();//定值更新标志，1~255，每次定值存储，该值加一(所有定值公用)
		uint16 DataChangeCnt(uint16 Zone);//定值更新标志，1~255，每次定值存储，该值加一
		/// <summary>
		/// 将定值更新至应用使用区
		/// 每次定值更新后，应用需要主动更新
		/// </summary>
		/// <returns></returns>
		bool8 UpdateForUse();
		const stAppFlags* AppFlags()const;
		/// <summary>
		/// 获取存储过程参数
		/// </summary>
		/// <param name="Zone"></param>
		/// <returns>参见 E_SaveStep </returns>
		int32 GetSaveStepFlag(uint32 Zone);
		/// <summary>
		/// 将备用参数转为正式参数并使用
		/// </summary>
		/// <param name="ZoneNum"></param>
		/// <returns></returns>
		int32 LoadBakParaForUse(int32 ZoneNum);
	};
	/// <summary>
	/// 参数元素
	/// </summary>
	class ApiPara :protected SalPara
	{
	public:
		/// <summary>
		/// 通用型定值（INT32）
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="Group"></param>
		/// <param name="Min"></param>
		/// <param name="Default"></param>
		/// <param name="Max"></param>
		/// <param name="DotNum"></param>
		/// <param name="Units"></param>
		void PowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, int32 Min, int32 Default, int32 Max, uint8 DotNum, const VarUnits& Units);
		/// <summary>
		/// 通用型定值（INT32）
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="Group"></param>
		/// <param name="Min"></param>
		/// <param name="Default"></param>
		/// <param name="Max"></param>
		/// <param name="DotNum"></param>
		/// <param name="Units"></param>
		/// <param name="ExInfo">供应用自用</param>
		void PowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, int32 Min, int32 Default, int32 Max, uint8 DotNum, const VarUnits& Units, int32 ExInfo);
		void SetRange(int32 Max, int32 Min);//设置定值上下限
		void SetDisp(bool8 Disp);//设置定值是否对外展示
		int32 Int32();//当前组定值数值，定点数
		float32 Float32();//当前组定值数值，浮点数
		//Bool型定值
		void BlPowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, int32 Default);
		bool8 Bool();
		//字符型定值
		// MaxLen 最大值为40
		void StrPowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, const char* DefName);
		const char* StrData();//当前组定值数值
		//只读型定值，例如定值区号
		void ZonePowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, int32 Min, int32 Default, int32 Max, uint8 DotNum, const VarUnits& Units);
		//枚举型定值，默认值填写的是枚举的序号，不是枚举的值
		void EnumPowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, int32 Default, SalEnumDes* Enum, uint8 EnumNum, const VarUnits& Units);
		int32 EnumIndex();
		int32 EnumVal();
		//CT二次值
		void CTEnumPowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, int32 Default);
		int32 CtValue();
		//关联CT二次值的电流型定值,该类定值仅在编辑时，将最大最小值乘以ct二次值处理,最大值、最小值，按照1A填写，默认值填写1A与5A都能适应的中间值
		void RelatedCTPowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, int32 Min, int32 Default, int32 Max, uint8 DotNum, const VarUnits& Units, ApiPara& SecondCt);
		//间隔投退
		void UnitOnOffPowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, int32 Default);
		/// <summary>
		/// 比特型定值
		/// </summary>
		/// <param name="Name">名称</param>
		/// <param name="DesName">描述地址</param>
		/// <param name="Group">实例组</param>
		/// <param name="Default">默认值</param>
		/// <param name="Max">最大值</param>
		/// <param name="ByteNum">字节数</param>
		/// <param name="Des">长度必须为ByteNum*8</param>
		void BitOnOffPowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, uint32 Min, uint32 Default, uint32 Max, uint32 ByteNum, SalBitDes* Des);
		/// <summary>
		/// Hex型定值
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="Group"></param>
		/// <param name="Default"></param>
		/// <param name="Max"></param>
		/// <param name="ByteNum"></param>
		void HexPowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, uint32 Min, uint32 Default, uint32 Max, uint32 ByteNum);
		/// <summary>
		/// 无符号32位整型，例如PTCT系数
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="Group"></param>
		/// <param name="Min"></param>
		/// <param name="Default"></param>
		/// <param name="Max"></param>
		/// <param name="DotNum"></param>
		/// <param name="Units"></param>
		/// <param name="ExInfo">供应用自用</param>
		void UInt32PowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, uint32 Min, uint32 Default, uint32 Max, uint8 DotNum, const VarUnits& Units, int32 ExInfo);
		uint32 Uint32();
	protected:

	};
}

#endif // !APIPARA_H

