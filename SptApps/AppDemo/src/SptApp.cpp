#include "InstResource.h"

//��ʼ���������ã���ʱ������δ���أ�����������
void AppPowerUpStep0()
{
	AppParaPowerUpIni();
	AppCmmPowerUpIni();
}
//��ʼ��һ����IO���ã���ʱ�����Ѿ�������ɣ����Ը��ݲ������Ի��ĳ�ʼ��IO����ʱƽ̨���ܻ�δ���أ����ɽ���������ƽ̨���е���Ϊ��
//���е�������ƽ̨����Դ��Ӧ�ڴ�Step0��Step1�н���
//Step0��Step1��������Step0�У����еĲ�����δ��ʼ����ɣ���˲����ǲ����õġ�Step1�в����Ѿ���ʼ����������ɣ�Step1�п���ʹ�ò�������ֵ����Ϣ
void AppPowerUpStep1()
{
	AppDbgPowerUpIni();
	AppEventPowerUpIni();
	AppAngInPowerUpIni();
	AppAngOutPowerUpIni();
	AppHmiLedPowerUpIni();
	AppStateInPowerUpIni();
	AppStateOutPowerUpIni();
	AppSjRecordPowerUpIni();
	AppFwRecordPowerUpIni();
	T860PowerUpIni();
	AppCheckPowerUpIni();
}
struct TaskRunInfo sampLoadnfo;//���ؼ���
//��ʱƽ̨�Ѿ���ɳ�ʼ�������ǲ����жϻ�δ��������ʱ���Խ���һЩ����ֵ��Ӧ�ò�IO��ʼ���������������ɵȹ���
//61850�Ѿ���ʼ����ϣ����Զ�ȡһЩ������Ϣ
//�˺����в��ܽ�����Ҫ������Դ����Ļ�����ж�ƽ̨������Դ�����þ�Ӧ��Setp0��Step1�����
void AppPowerUpStep2()
{
	SjUsrLogRecord.CreatRecord("SptMain", "����ϵͳ", "Ӧ�ó���", "�ϵ�����", 0, 0, 0);
#ifdef WIN32_SIM

#elif defined(SYLIX_GZK)
	//������ϵͳУ���־
	if (!ApiVersionInfo::Instance().MainSysVersion().IsProgOk())
	{
		LogErr.Stamp() << "MainSysVersion PowerUp Check err.\n";
	}
	if (!ApiVersionInfo::Instance().BakSysVersion().IsProgOk())
	{
		LogErr.Stamp() << "BakSysVersion PowerUp Check err.\n";
	}
#endif // WIN32_SIM
	sampLoadnfo.SetName("AppSamp");
	sampLoadnfo.ClearLoadInfo();
	sampLoadnfo.Rgs2TaskMonitorRunInfo();
}

//����ж�
void App1SampPointInt()
{
	sampLoadnfo.RunStart();
	UpdateNorStateIn();
	AppAngSampIn();
	AppFwUpdate();
	sampLoadnfo.RunEnd();
}
void App2SampPointInt()
{


}
void App3SampPointInt()
{


}
extern "C" int main(int argc, char** argv)
{
	LogApp.Stamp() << "Program run into app main.\n";
	ApiVersionInfo::Instance().AppVersion().FillInfo(0, 2, 0, "fengzhanhua", __DATE__, __TIME__);
	//��ƽ̨����Ӧ����Ϣ��ƽ̨�������������������FactoryMode�����ģ�ƽ̨�����FactoryMode.cfg��ִ����Ӧ�Ĳ���
	SptMain::Instance().SetAppCfg(&AppRunTimeCfg, argc, argv);
	//��ʼ����������
	AppPowerUpStep0();
	//��ʼ��IO��Ϣ
	AppPowerUpStep1();
	//ƽ̨���ܳ�ʼ��������ƽ̨�����е������
	SptMain::Instance().PowerUpIni(0);
	//��ʼ��Ӧ�ò�IO��Ϣ���������������
	AppPowerUpStep2();
	//���г�ʼ���Ѿ���ɣ�����ƽ̨����ѭ�����˺���������
	SptMain::Instance().Run();
	return  (0);
}
