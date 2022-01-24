#ifndef SPTRESOURCE_H
#define SPTRESOURCE_H

namespace spt
{
	enum E_SptApiStatus
	{
		E_SAS_LcdCmmErr,//Һ��ͨѶ�쳣
		E_SAS_VirLcdCmmErr,//����Һ��ͨѶ�쳣
		E_SAS_SampCntJump,//�����������(ģ����)
		E_SAS_HostSvSynState,//����SV����ͬ����־
		E_SAS_HostBCodeCheckAlarm,//B��У���쳣
		E_SAS_HostBCodePrecisionAlarm,//B�뾫���쳣
		E_SAS_HostTPortAlarm,//��ʱ�ź�״̬
		E_SAS_HostTSrvAlarm,//��ʱ����״̬
		E_SAS_HostContAlarm,//��ʱ֡�����쳣
		E_SAS_CCDFileParseAlarm,//CCD�ļ������쳣
		E_SAS_CCDFileCrcAlarm,//CCD�ļ�CRC�쳣
		E_SAS_UserFileLoadAlarm,//�˺��ļ��ϵ絼���쳣
		E_SAS_RamAllocErr,//�ڴ������쳣
		E_SAS_RamCheckErr,//�ڴ��Լ��쳣
		E_SptApiStatusTotal,
	};

	extern ApiStatusGroup SptStatusGroup;
	extern ApiStatus SptApiStatus[E_SptApiStatusTotal];

	void SpStatusPowerUpIni();

}


#endif // !SPTRESOURCE_H
