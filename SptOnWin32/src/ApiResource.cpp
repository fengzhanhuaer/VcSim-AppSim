#include"ApiProject.h"
using namespace spt;


spt::ApiStatusGroup spt::SptStatusGroup;


ApiStatus spt::SptApiStatus[E_SptApiStatusTotal];

void spt::SpStatusPowerUpIni()
{
	SptStatusGroup.PowerUpIni("���ƽ̨״̬��", "ApiStatusGroup", E_SptApiStatusTotal);
	SptApiStatus[E_SAS_LcdCmmErr].BlPowerUpIni("Һ��ͨѶ�쳣", "E_SAS_LcdCmmErr", SptStatusGroup, 0);
	SptApiStatus[E_SAS_VirLcdCmmErr].BlPowerUpIni("����Һ��ͨѶ�쳣", "E_SAS_VirLcdCmmErr", SptStatusGroup, 0);
	SptApiStatus[E_SAS_SampCntJump].BlPowerUpIni("�����������", "E_SAS_SampCntJump", SptStatusGroup, 0);
	SptApiStatus[E_SAS_HostSvSynState].BlPowerUpIni("SV����ͬ��״̬", "E_SAS_HostSvSynState", SptStatusGroup, 0);
	SptApiStatus[E_SAS_HostBCodeCheckAlarm].BlPowerUpIni("B��У���쳣", "E_SAS_HostBCodeCheckAlarm", SptStatusGroup, 0);
	SptApiStatus[E_SAS_HostBCodePrecisionAlarm].BlPowerUpIni("B�뾫���쳣", "E_SAS_HostBCodePrecisionAlarm", SptStatusGroup, 0);
	SptApiStatus[E_SAS_HostTPortAlarm].BlPowerUpIni("��ʱ�ź�״̬", "E_SAS_HostTPortAlarm", SptStatusGroup, 0);
	SptApiStatus[E_SAS_HostTSrvAlarm].BlPowerUpIni("��ʱ����״̬", "E_SAS_HostTSrvAlarm", SptStatusGroup, 0);
	SptApiStatus[E_SAS_HostContAlarm].BlPowerUpIni("��ʱ֡�����쳣", "E_SAS_HostContAlarm", SptStatusGroup, 0);
	SptApiStatus[E_SAS_CCDFileParseAlarm].BlPowerUpIni("CCD�ļ������쳣", "E_SAS_CCDFileParseAlarm", SptStatusGroup, 0);
	SptApiStatus[E_SAS_CCDFileCrcAlarm].BlPowerUpIni("CCD�ļ�CRC�쳣", "E_SAS_CCDFileCrcAlarm", SptStatusGroup, 0);
	SptApiStatus[E_SAS_UserFileLoadAlarm].BlPowerUpIni("�˺��ļ��ϵ絼���쳣", "E_SAS_UserFileLoadAlarm", SptStatusGroup, 0);
	SptApiStatus[E_SAS_RamAllocErr].BlPowerUpIni("�ڴ������쳣", "E_SAS_RamAllocErr", SptStatusGroup, 0);
	SptApiStatus[E_SAS_RamCheckErr].BlPowerUpIni("�ڴ��Լ��쳣", "E_SAS_RamCheckErr", SptStatusGroup, 0);
}