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
//显示模拟量
bool8 ViewAnglog(ApiMenu* Menu);
//显示频率
bool8 ViewFrlog(ApiMenu* Menu);
//显示直流信息
bool8 ViewDclog(ApiMenu* Menu);
//显示状态监视信息
bool8 ViewDevlog(ApiMenu* Menu);
//显示间隔CPU板光口信息
bool8 ViewOpt1log(ApiMenu* Menu);
//显示母线CPU板光口信息
bool8 ViewOpt2log(ApiMenu* Menu);
//显示内部信息
bool8 ViewInterlog(ApiMenu* Menu);
//显示负载信息
bool8 DispTaskLoadInfo(ApiMenu* Menu);
//显示任务周期信息
bool8 DispTaskPeriodInfo(ApiMenu* Menu);
//清楚负载统计信息
bool8 ClearTaskRunCalInfo(ApiMenu* Menu);
//重新加载日志开关
bool8 UpdateLogCfg(ApiMenu* Menu);
//应用网口信息
bool8 AppEthnetPara(ApiMenu* Menu);


#endif // !INSTMENUINFOVIEW_H

