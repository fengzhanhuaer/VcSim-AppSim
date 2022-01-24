#include"ApiProject.h"
using namespace spt;

int32 spt::ApiSysEthNetCfg::PowerUpIni(int32 Para)
{
	const ApiAppCfg* cfg = SptMain::Instance().AppCfg();

	if (cfg)
	{
		if (cfg->hmicfg.NetPortNum > M_ArrLen(EthNet))
		{
			EthNetNum.Set("EthNetNum", M_ArrLen(EthNet));
		}
		else
		{
			EthNetNum.Set("EthNetNum", cfg->hmicfg.NetPortNum);
		}
	}
	else
	{
		EthNetNum.Set("EthNetNum", 5);
	}
	EthNetNum.SetNotes("以太网口数目，含调试口(固定为0口)");
	AddCfgData(&EthNetNum);

	String20B str;

	for (uint32 i = 0; i < M_ArrLen(EthNet); i++)
	{
		str.Clear();
		str << "Net" << i << "Port";
		EthNet[i].port.Set(str.Str(), i);
		str.Clear();
		str << "Net" << i << "Ip";
		EthNet[i].ip.SetName(str.Str());
		str.Clear();
		str << "Net" << i << "Musk";
		EthNet[i].musk.SetName(str.Str());
		EthNet[i].musk.SetData(255, 255, 255, 0);
		str.Clear();
		str << "Net" << i << "Gate";
		EthNet[i].gate.SetName(str.Str());
		if (i < EthNetNum.Data())
		{
			if (i == 0)
			{
				EthNet[i].ip.SetData(100, 100, 100, 100);
				EthNet[i].gate.SetData(100, 100, 100, 1);
				EthNet[i].exInfo.Set(str.Str(), 3);
			}
			else
			{
				EthNet[i].ip.SetData(192, 168, i, 100);
				EthNet[i].gate.SetData(192, 168, i, 1);
				EthNet[i].exInfo.SetData(0);
			}
		}
		else
		{
			EthNet[i].ip.SetData(192, 168, i, 0);
			EthNet[i].gate.SetData(192, 168, i, 0);
			EthNet[i].exInfo.SetData(0);
		}
		str.Clear();
		str << "Net" << i << "Mac";
		EthNet[i].mac.SetName(str.Str());
		if (cfg && cfg->IsDevice(ED_SAU31_Sub))
		{
			EthNet[i].mac.SetData(0, 14, 234, 0, 0, 100 + i);
		}
		else
		{
			EthNet[i].mac.SetData(0, 14, 234, 0, 0, 20 + i);
		}
		str.Clear();
		str << "Net" << i << "Flag";
		EthNet[i].exInfo.SetName(str.Str());
		AddCfgData(&EthNet[i].port);
		AddCfgData(&EthNet[i].ip);
		AddCfgData(&EthNet[i].musk);
		AddCfgData(&EthNet[i].gate);
		AddCfgData(&EthNet[i].mac);
		AddCfgData(&EthNet[i].exInfo);
	}
	IpWhiteBillEthNetNum.Set("IpWhiteBill", 0);
	AddCfgData(&IpWhiteBillEthNetNum);
	for (uint32 i = 0; i < M_ArrLen(IpWhiteBill); i++)
	{
		str.Clear();
		str << "Ip" << i;
		IpWhiteBill[i].SetName(str.Str());
		if (i == 0)
		{
			IpWhiteBill[i].SetData(100, 100, 100, 1);
		}
		else
		{
			IpWhiteBill[i].SetData(192, 168, i, 1);
		}
		AddCfgData(&IpWhiteBill[i]);
	}
	path.Set(CN_CFG_FILE_ROOT);
	name.Set("EthNet.cfg");
	if (cfg && cfg->platform.hardware == EH_GZKSAU)
	{
		if (cfg->IsDevice(ED_SAU31_Sub))
		{
			EthNet[0].ip.SetData(100, 100, 100, 101);
		}
	}
	if ((uint32)ReadAll() != CfgDataNum())
	{
		SaveAll();
	}
	AppEthnetPara();
	return 0;
}

int32 spt::ApiSysEthNetCfg::AppEthnetPara()
{
	uint32 ip, mask, gate;
	uint8 mac[6];
	uint16 hex;
	for (uint32 i = 0; i < M_ArrLen(EthNet); i++)
	{
		ip = EthNet[i].ip.Data();
		mask = EthNet[i].musk.Data();
		gate = EthNet[i].gate.Data();
		hex = EthNet[i].exInfo.Data();
		EthNet[i].mac.Data(mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
		SptSetEthnetPara(i, (char*)&ip, (char*)&mask, (char*)&gate, (char*)&mac, (char*)&hex);
	}
	uint32 num = IpWhiteBillEthNetNum.Data();
	if (num)
	{
		for (uint32 i = 0; i < num; i++)
		{
			ip = IpWhiteBill[i].Data();
			SptSetEthnetWhiteBill(i, (char*)&ip);
		}
		SptEnableEthnetPara(2, num);
	}
	else
	{
		SptEnableEthnetPara(2, 0);
	}
	SptEnableEthnetPara(0, 0);
	return 0;
}

int32 spt::ApiUnitCfg::PowerUpIni(int32 Para)
{
	const ApiAppCfg* cfg = SptMain::Instance().AppCfg();

	NodeId.Set("NodeId", 1);
	NodeId.SetNotes("节点号");
	AddCfgData(&NodeId);
	DeviceID.Set("DeviceID", "JCDZ6004020781161101000001");
	DeviceID.SetNotes("唯一性代码");
	AddCfgData(&DeviceID);
	StationId.Set("StationId", "SubStation");
	StationId.SetNotes("变电站");
	AddCfgData(&StationId);
	if (cfg)
	{
		String100B str;
		str = cfg->hmicfg.DeviceSampleName;
		str << "_RCD";
		UnitRcdId.Set("UnitRcdId", str.Str());
		FwRecId.Set("FwRecId", cfg->hmicfg.DeviceSampleName);
	}
	else
	{
		FwRecId.Set("FwRecId", "SubStation");
		UnitRcdId.Set("UnitRcdId", "DTools");
	}
	FwRecId.SetNotes("装置名称");
	AddCfgData(&FwRecId);
	UnitRcdId.SetNotes("装置录波简写（英文）");
	AddCfgData(&UnitRcdId);
	path.Set(CN_CFG_FILE_ROOT);
	name.Set("UnitCfg.cfg");
	if ((uint32)ReadAll() != CfgDataNum())
	{
		SaveAll();
	}
	SalFile file;
	file.Path().Set(CN_CFG_FILE_ROOT);
	file.Name().Set("DeviceID.cfg");
	if (file.IsExist())
	{
		file.OpenReadOnly();
		char buf[120];
		file.ReadLine(buf, sizeof(buf));
		if (StrNCmp(buf, DeviceID.StrData(), sizeof(buf)))
		{
			DeviceID.SetData(buf);
			SaveAll();
		}
	}
	return 0;
}
