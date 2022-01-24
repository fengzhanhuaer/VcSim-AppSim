#include"ApiProject.h"
using namespace spt;


spt::ApiStatusGroup spt::SptStatusGroup;


ApiStatus spt::SptApiStatus[E_SptApiStatusTotal];

void spt::SpStatusPowerUpIni()
{
	SptStatusGroup.PowerUpIni("软件平台状态量", "ApiStatusGroup", E_SptApiStatusTotal);
	SptApiStatus[E_SAS_LcdCmmErr].BlPowerUpIni("液晶通讯异常", "E_SAS_LcdCmmErr", SptStatusGroup, 0);
	SptApiStatus[E_SAS_VirLcdCmmErr].BlPowerUpIni("虚拟液晶通讯异常", "E_SAS_VirLcdCmmErr", SptStatusGroup, 0);
	SptApiStatus[E_SAS_SampCntJump].BlPowerUpIni("采样序号跳变", "E_SAS_SampCntJump", SptStatusGroup, 0);
	SptApiStatus[E_SAS_HostSvSynState].BlPowerUpIni("SV发送同步状态", "E_SAS_HostSvSynState", SptStatusGroup, 0);
	SptApiStatus[E_SAS_HostBCodeCheckAlarm].BlPowerUpIni("B码校验异常", "E_SAS_HostBCodeCheckAlarm", SptStatusGroup, 0);
	SptApiStatus[E_SAS_HostBCodePrecisionAlarm].BlPowerUpIni("B码精度异常", "E_SAS_HostBCodePrecisionAlarm", SptStatusGroup, 0);
	SptApiStatus[E_SAS_HostTPortAlarm].BlPowerUpIni("对时信号状态", "E_SAS_HostTPortAlarm", SptStatusGroup, 0);
	SptApiStatus[E_SAS_HostTSrvAlarm].BlPowerUpIni("对时服务状态", "E_SAS_HostTSrvAlarm", SptStatusGroup, 0);
	SptApiStatus[E_SAS_HostContAlarm].BlPowerUpIni("对时帧跳变异常", "E_SAS_HostContAlarm", SptStatusGroup, 0);
	SptApiStatus[E_SAS_CCDFileParseAlarm].BlPowerUpIni("CCD文件解析异常", "E_SAS_CCDFileParseAlarm", SptStatusGroup, 0);
	SptApiStatus[E_SAS_CCDFileCrcAlarm].BlPowerUpIni("CCD文件CRC异常", "E_SAS_CCDFileCrcAlarm", SptStatusGroup, 0);
	SptApiStatus[E_SAS_UserFileLoadAlarm].BlPowerUpIni("账号文件上电导入异常", "E_SAS_UserFileLoadAlarm", SptStatusGroup, 0);
	SptApiStatus[E_SAS_RamAllocErr].BlPowerUpIni("内存申请异常", "E_SAS_RamAllocErr", SptStatusGroup, 0);
	SptApiStatus[E_SAS_RamCheckErr].BlPowerUpIni("内存自检异常", "E_SAS_RamCheckErr", SptStatusGroup, 0);
}