#ifndef APIAPPCFG_H
#define APIAPPCFG_H

namespace spt
{
	struct ApiAppCfg
	{
		//平台类型配置
		struct Platform
		{
			enum E_HARDWARE hardware;
			enum E_SOFTWARE software;
			enum E_DEVTYPE devtype;
		}platform;
		//人机接口设置
		struct HmiCfg
		{
			ApiMenu* AppRootMenu;//根菜单
			/// <summary>
			/// 对外名称
			/// </summary>
			char DispName[40];//显示名称
			/// <summary>
			/// 对外版本
			/// </summary>
			char FullTypeName[40];//型号名称
			uint32 NetPortNum;//网口数目（含前网口）
			/// <summary>
			/// GZK-35kV-T3-L-31-S-1-SD-INFO
			/// GZK产品系列，SPD/GCN/GZK
			/// 35kV电压等级
			/// T3硬件平台
			/// L线路，T变压器，B母线产品类别
			/// 31产品型号,不同平台内控版本应该不同,不同型号，功能产品版本应该不同
			/// S智能N常规
			/// 1 程序分支，例如1A与5A，特殊版本、测试版本
			/// SD特殊标记，SD山东，NOR通用常规发布版本，TEST测试版本
			/// INFO其他说明信息
			/// </summary>
			char FatcoryTypeName[100];//厂家内控型号
			char DeviceSampleName[40];//型号简写,用于录波名称等
		}hmicfg;
		//应用任务配置
		struct SampAppCfg
		{
			ApiSampAppTask* AppArrBase;//应用任务
			uint32 AppArrLen;//应用任务个数
			uint32 SysHz;//正常系统频率,3位小数
			uint32 CycleSamp;//每周波采样点数
		}sampAppCfg;
		bool8 IsHardWare(E_HARDWARE hd)const;
		bool8 IsSoftWare(E_SOFTWARE st)const;
		bool8 IsDevice(E_DEVTYPE dev)const;
	};
}
#endif // !APIAPPCFG_H
