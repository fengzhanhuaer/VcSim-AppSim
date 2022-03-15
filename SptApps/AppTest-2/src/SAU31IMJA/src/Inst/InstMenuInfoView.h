#ifndef INSTMENUINFOVIEW_H
#define INSTMENUINFOVIEW_H
bool8 EnterAnaMenu(ApiMenu* Menu);
bool8 ExitAnaMenu(ApiMenu* Menu);
bool8 EnterAnaJMenu(ApiMenu* Menu);
bool8 ExitAnaJMenu(ApiMenu* Menu);
bool8 EnterAnaFrMenu(ApiMenu* Menu);
bool8 ExitAnaFrMenu(ApiMenu* Menu);
bool8 EnterAnaHumMenu(ApiMenu* Menu);
bool8 ExitAnaFrMenu(ApiMenu* Menu);

bool8 ViewSptWarnStatus(ApiMenu* Menu);
bool8 ViewActStatus(ApiMenu* Menu);
bool8 ViewWarnStatus(ApiMenu* Menu);
bool8 ViewChekStatus(ApiMenu* Menu);
bool8 ViewDiStatus(ApiMenu* Menu);
bool8 ViewDoStatus(ApiMenu* Menu);
bool8 ViewGoInStatus(ApiMenu* Menu);
bool8 ViewGoOutStatus(ApiMenu* Menu);
bool8 ViewLedStatus(ApiMenu* Menu);
bool8 ViewFlagStatus(ApiMenu* Menu);
bool8 ViewDpiStatus(ApiMenu* Menu);
bool8 ViewWarnDetailedStatus(ApiMenu* Menu);
bool8 ViewPublicVersion(ApiMenu* Menu);
//��ʾģ����
bool8 ViewAnglog(ApiMenu* Menu);
//��ʾƵ��
bool8 ViewFrlog(ApiMenu* Menu);
//��ʾֱ����Ϣ
bool8 ViewDclog(ApiMenu* Menu);
//��ʾ״̬������Ϣ
bool8 ViewDevlog(ApiMenu* Menu);
//��ʾ���CPU������Ϣ
bool8 ViewOpt1log(ApiMenu* Menu);
//��ʾĸ��CPU������Ϣ
bool8 ViewOpt2log(ApiMenu* Menu);
//��ʾ�ڲ���Ϣ
bool8 ViewInterlog(ApiMenu* Menu);
//��ʾ������Ϣ
bool8 DispTaskLoadInfo(ApiMenu* Menu);
//��ʾ����������Ϣ
bool8 DispTaskPeriodInfo(ApiMenu* Menu);
//�������ͳ����Ϣ
bool8 ClearTaskRunCalInfo(ApiMenu* Menu);
//���¼�����־����
bool8 UpdateLogCfg(ApiMenu* Menu);
//Ӧ��������Ϣ
bool8 AppEthnetPara(ApiMenu* Menu);


#endif // !INSTMENUINFOVIEW_H

