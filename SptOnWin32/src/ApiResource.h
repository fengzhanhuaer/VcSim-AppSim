#ifndef SPTRESOURCE_H
#define SPTRESOURCE_H

namespace spt
{
	enum E_SptApiStatus
	{
		E_SAS_LcdCmmErr,//液晶通讯异常
		E_SAS_VirLcdCmmErr,//虚拟液晶通讯异常
		E_SAS_SampCntJump,//采样序号跳变(模拟量)
		E_SAS_HostSvSynState,//主机SV发送同步标志
		E_SAS_HostBCodeCheckAlarm,//B码校验异常
		E_SAS_HostBCodePrecisionAlarm,//B码精度异常
		E_SAS_HostTPortAlarm,//对时信号状态
		E_SAS_HostTSrvAlarm,//对时服务状态
		E_SAS_HostContAlarm,//对时帧跳变异常
		E_SAS_CCDFileParseAlarm,//CCD文件解析异常
		E_SAS_CCDFileCrcAlarm,//CCD文件CRC异常
		E_SAS_UserFileLoadAlarm,//账号文件上电导入异常
		E_SAS_RamAllocErr,//内存申请异常
		E_SAS_RamCheckErr,//内存自检异常
		E_SptApiStatusTotal,
	};

	extern ApiStatusGroup SptStatusGroup;
	extern ApiStatus SptApiStatus[E_SptApiStatusTotal];

	void SpStatusPowerUpIni();

}


#endif // !SPTRESOURCE_H
