#ifndef INSTMENUINFOVIEW_H
#define INSTMENUINFOVIEW_H

bool8 ViewSptWarnStatus(ApiMenu* Menu);
bool8 ViewWarnStatus(ApiMenu* Menu);
bool8 ViewWarnDetailedStatus(ApiMenu* Menu);
bool8 ViewPrivateVersion(ApiMenu* Menu);
//显示模拟量
bool8 ViewAnglog(ApiMenu* Menu);
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

