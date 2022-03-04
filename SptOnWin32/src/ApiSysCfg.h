#ifndef APISYSCFG_H
#define APISYSCFG_H

namespace spt
{
	class ApiSysEthNetCfg :public CfgFile
	{
	public:
		int32 PowerUpIni(int32 Para);
		M_Singleton(ApiSysEthNetCfg);
	public:
		int32 AppEthnetPara();
	protected:
		virtual PCfgDataBase* CfgPool() { return pool; };
		virtual uint32 CfgPoolSize() { return M_ArrLen(pool); };
	public:
		CfgUint32 EthNetNum;
		SalCmmEthNetPara EthNet[5];
		CfgUint32 IpWhiteBillEthNetNum;
		CfgIp	IpWhiteBill[20];
	private:
		PCfgDataBase pool[60];
	};
	class ApiUnitCfg :public CfgFile
	{
	public:
		int32 PowerUpIni(int32 Para);
		M_Singleton(ApiUnitCfg);
	public:
		CfgUint32 NodeId;//节点号
		CfgStr DeviceID;//装置代码
		CfgStr StationId;//变电站名称
		CfgStr FwRecId;//保护设备名称
		CfgStr UnitRcdId;//装置录波简写
	protected:
		virtual PCfgDataBase* CfgPool() { return pool; };
		virtual uint32 CfgPoolSize() { return M_ArrLen(pool); };
	private:
		PCfgDataBase pool[60];
	};
}





#endif // !APISYSCFG_H

