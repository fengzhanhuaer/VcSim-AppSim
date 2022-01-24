#include"InstResource.h"

bool8 MakeStatusDispMenu(ApiMenu* Menu, ApiHmiGridWnd& wnd, SalStatusGroup* Group, int32 From, int32 To)
{
	uint32 dataNum = To;
	SalStatus* cell;
	InstObject* obj;
	uint8 col = 1;
	for (uint16 i = From; i < dataNum; i++)
	{
		obj = Group->GetObject(i);
		if (obj)
		{
			cell = (SalStatus*)(obj);
			if (!cell->IsDisp())
			{
				continue;
			}
			col = 1;
			struct HmiGridWndDataMapRow* row = wnd.CreatRow();
			row->SetName(cell->Name());
			//状态量的时间
			row->SetColStatusTime(col, cell, 27, 2);
			col++;
			//状态量
			row->SetColData(col, cell, 8);
			col++;
		}
		else
		{
			break;
		}
	}
	return 1;
}
bool8 MakeStatusDispMenu(ApiMenu* Menu, ApiHmiGridWnd& wnd, SalStatusGroup* Group)
{
	return MakeStatusDispMenu(Menu, wnd, Group, 0, Group->InstNum());
}
bool8 ViewSptWarnStatus(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd;
	wnd.SetInfo(Menu->Name(), 0, 0);
	MakeStatusDispMenu(Menu, wnd, (SalStatusGroup*)&SptStatusGroup);
	wnd.Show();
	return 1;
}
bool8 ViewWarnStatus(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd;
	wnd.SetInfo(Menu->Name(), 0, 0);
	MakeStatusDispMenu(Menu, wnd, (SalStatusGroup*)&AppEventWarnGroup);
	wnd.Show();
	return 1;
}
bool8 ViewWarnDetailedStatus(ApiMenu* Menu)
{

	return 1;
}
void UpdateOtherChipVersion()
{
	ApiVersionInfo::Instance().OtherChipVersion(0).SetName("Fpga1");
	ApiVersionInfo::Instance().OtherChipVersion(0).ProgVersion = 100;
	ApiVersionInfo::Instance().OtherChipVersion(0).ProgDate = 0x20210112;
	ApiVersionInfo::Instance().OtherChipVersion(0).ProgCrc = 0x32164589;
}

bool8 ViewPrivateVersion(ApiMenu* Menu)
{
	UpdateOtherChipVersion();
	ApiVersionInfo::Instance().Print();

	ApiHmiTextWnd wnd(HmiTextWnd::E_SinglePage, 0);
	uint32 page = 0;
	String1000B str;
	ApiVersionInfo::Instance().AppVersion().ToStr(str);
	wnd.SetPage(page++, str.Str());
	str.Clear();
	ApiVersionInfo::Instance().ApiVersion().ToStr(str);
	wnd.SetPage(page++, str.Str());
#if defined(SYLIX_GZK)
	str.Clear();
	ApiVersionInfo::Instance().Boot0Version().ToStr(str);
	wnd.SetPage(page++, str.Str());
	str.Clear();
	ApiVersionInfo::Instance().UbootVersion().ToStr(str);
	wnd.SetPage(page++, str.Str());
	str.Clear();
	ApiVersionInfo::Instance().MainSysVersion().ToStr(str);
	wnd.SetPage(page++, str.Str());
	str.Clear();
	ApiVersionInfo::Instance().BakSysVersion().ToStr(str);
	wnd.SetPage(page++, str.Str());
#endif
	str.Clear();
	str << "虚拟液晶 :"; ApiVersionInfo::Instance().VirLcdVersion().RtInfoStrFmt1(str); str << "\n";
	str << "液晶程序 :"; ApiVersionInfo::Instance().LcdVersion().RtInfoStrFmt1(str); str << "\n";
	wnd.SetPage(page++, str.Str());
	str.Clear();

	wnd.SetTitle("版本信息", page);
	wnd.Show();
	return 1;
}
bool8 DispTaskLoadInfo(ApiMenu* Menu)
{
	ApiHmiGridWnd gwnd;
	uint32 lcdw = GraphicDevice::Instance().LcdWidth();
	gwnd.SetInfo("负载监视(单位us)", 0, 0);
	const TaskMonitor::RunInfo& Info = TaskMonitor::Instance().TaskRunInfo();
	if (lcdw == 480)
	{
		gwnd.SetColTitle("名称", "    实时", "   Max(H)", "   Min(H)", "   Max(D)", "   Min(D)", 0, 0, 0, 0);
		if (Info.isInfoOk)
		{
			for (uint16 i = 0; i < Info.taskNum; i++)
			{
				struct HmiGridWndDataMapRow* row = gwnd.CreatRow();
				row->SetName(Info.info[i].taskRunInfo->Name());
				row->SetColDataCfg(1, 0, E_SVT_U32 | E_SVT_PTR, 8, 0);
				row->SetColData(1, &Info.info[i].taskRunInfo->realTimeLoad);
				row->SetColDataCfg(2, 0, E_SVT_U32 | E_SVT_PTR, 8, 0);
				row->SetColData(2, &Info.info[i].taskRunInfo->maxHourLoad);
				row->SetColDataCfg(3, 0, E_SVT_U32 | E_SVT_PTR, 8, 0);
				row->SetColData(3, &Info.info[i].taskRunInfo->minHourLoad);
				row->SetColDataCfg(4, 0, E_SVT_U32 | E_SVT_PTR, 8, 0);
				row->SetColData(4, &Info.info[i].taskRunInfo->maxDayLoad);
				row->SetColDataCfg(5, 0, E_SVT_U32 | E_SVT_PTR, 8, 0);
				row->SetColData(5, &Info.info[i].taskRunInfo->minDayLoad);
			}
		}
	}
	else if (lcdw == 320)
	{

	}
	gwnd.Show();
	return 1;
}
bool8 DispTaskPeriodInfo(ApiMenu* Menu)
{
	ApiHmiGridWnd gwnd;
	uint32 lcdw = GraphicDevice::Instance().LcdWidth();
	gwnd.SetInfo("周期监视(单位us)", 0, 0);
	const TaskMonitor::RunInfo& Info = TaskMonitor::Instance().TaskRunInfo();
	if (lcdw == 480)
	{
		gwnd.SetColTitle("名称", "    实时", "   Max(H)", "   Min(H)", "   Max(D)", "   Min(D)", 0, 0, 0, 0);
		if (Info.isInfoOk)
		{
			for (uint16 i = 0; i < Info.taskNum; i++)
			{
				struct HmiGridWndDataMapRow* row = gwnd.CreatRow();
				row->SetName(Info.info[i].taskRunInfo->Name());
				row->SetColDataCfg(1, 0, E_SVT_U32 | E_SVT_PTR, 8, 0);
				row->SetColData(1, &Info.info[i].taskRunInfo->realTimePeriod);
				row->SetColDataCfg(2, 0, E_SVT_U32 | E_SVT_PTR, 8, 0);
				row->SetColData(2, &Info.info[i].taskRunInfo->maxHourPeriod);
				row->SetColDataCfg(3, 0, E_SVT_U32 | E_SVT_PTR, 8, 0);
				row->SetColData(3, &Info.info[i].taskRunInfo->minHourPeriod);
				row->SetColDataCfg(4, 0, E_SVT_U32 | E_SVT_PTR, 8, 0);
				row->SetColData(4, &Info.info[i].taskRunInfo->maxDayPeriod);
				row->SetColDataCfg(5, 0, E_SVT_U32 | E_SVT_PTR, 8, 0);
				row->SetColData(5, &Info.info[i].taskRunInfo->minDayPeriod);
			}
		}
	}
	else if (lcdw == 320)
	{

	}
	gwnd.Show();
	return 1;
}

bool8 ClearTaskRunCalInfo(ApiMenu* Menu)
{
	ApiSelectDialog sd("清空任务统计信息？", 0, 0, 0, 0);
	if (sd.Show() == 0)
	{
		TaskMonitor::Instance().ClearCalRunInfo();
		ApiWarnDialog wd("清空完成", 0, 0, 0, 0);
		wd.Show();
	}
	return 1;
}

bool8 UpdateLogCfg(ApiMenu* Menu)
{
	ApiSelectDialog sd("加载日志开关文件？", 0, 0, 0, 0);
	if (sd.Show() == 0)
	{
		SptLogTask::Instance().LoadCfg();
		ApiWarnDialog wd("加载完成", 0, 0, 0, 0);
		wd.Show();
	}
	return 1;
}

bool8 AppEthnetPara(ApiMenu* Menu)
{
	ApiSysEthNetCfg::Instance().ReadAll();
	ApiSysEthNetCfg::Instance().AppEthnetPara();
	return 1;
}

static int32 HmiViewAnglogUpdateData(class HmiGridWnd* Wnd, struct HmiGridWndDataMap* Map, HmiKey Key)
{
	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiAnglogRmsGroup[0];
	uint32 dataNum = anmsGroup->InstNum();
	st64value* pvalue;
	uint8 col = 1;
	uint32 rown = 0;
	uint32 bufIndex = anmsGroup->GetNewestDataIndex();
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalAngRms* rms = anmsGroup->Cell(i);
		if (rms)
		{
			if (!rms->IsDisp())
			{
				continue;
			}
			col = 1;
			struct HmiGridWndDataMapRow* row = &Map->row[rown++];
			const i32AngRms* rmsValue = anmsGroup->GetRealData(bufIndex, rms->InstId());
			pvalue = row->GetDataEdit(col);
			pvalue->value.i32 = (int32)(rmsValue->data1 * rms->Data1Coe());//一次值
			col++;
			col++;
			pvalue = row->GetDataEdit(col);
			pvalue->value.i32 = rmsValue->data1;//二次值
			col++;
			col++;
			pvalue = row->GetDataEdit(col);
			pvalue->value.i32 = rmsValue->data2;//角度
			col++;
			col++;
			pvalue = row->GetDataEdit(col);
			pvalue->value.u16 = rmsValue->q;//品质
		}
		else
		{
			break;
		}
	}
	return 0;
}

bool8 ViewAnglog(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd(HmiViewAnglogUpdateData);
	wnd.SetInfo("查看模拟量", 0, 0);
	wnd.SetColTitle("名称", "一次值", 0, "二次值", 0, 0, 0, "品质", 0, 0);
	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiAnglogRmsGroup[0];
	uint32 dataNum = anmsGroup->InstNum();
	st64value* pvalue;
	uint8 col = 1;
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalAngRms* rms = anmsGroup->Cell(i);
		if (rms)
		{
			if (!rms->IsDisp())
			{
				continue;
			}
			col = 1;
			struct HmiGridWndDataMapRow* row = wnd.CreatRow();
			row->SetName(rms->Name());
			//一次值
			row->SetColDataCfg(col, 0, E_SVT_I32 | E_SVT_PTR, 8, rms->Data1DotNum());
			pvalue = row->GetDataSur(col);
			pvalue->value.vptr = rms;
			pvalue = row->GetDataEdit(col);
			row->SetColData(col, &pvalue->value.i32);
			col++;
			row->SetColDataCfg(col, 0, E_SVT_STR | E_SVT_PTR, 2, 0);
			row->SetColStrData(col, rms->TransUnits1() == 0 ? Unit_NULL.toString() : rms->TransUnits1()->toString(), 0);
			col++;
			//二次值
			row->SetColDataCfg(col, 0, E_SVT_I32 | E_SVT_PTR, 8, rms->Data1DotNum());
			pvalue = row->GetDataSur(col);
			pvalue->value.vptr = rms;
			pvalue = row->GetDataEdit(col);
			row->SetColData(col, &pvalue->value.i32);
			col++;
			row->SetColDataCfg(col, 0, E_SVT_STR | E_SVT_PTR, 2, 0);
			row->SetColStrData(col, rms->Units1() == 0 ? Unit_NULL.toString() : rms->Units1()->toString(), 0);
			col++;
			if (rms->DataNum() == 2)
			{
				//角度
				row->SetColDataCfg(col, 0, E_SVT_I32 | E_SVT_PTR, 5, rms->Data2DotNum());
				pvalue = row->GetDataSur(col);
				pvalue->value.vptr = rms;
				pvalue = row->GetDataEdit(col);
				row->SetColData(col, &pvalue->value.i32);
				col++;
				row->SetColDataCfg(col, 0, E_SVT_STR | E_SVT_PTR, 2, 0);
				row->SetColStrData(col, rms->Units2() == 0 ? Unit_NULL.toString() : rms->Units2()->toString(), 0);
				col++;
			}
			else
			{
				col++;
				col++;
			}
			//品质
			if (rms->Data3Len() == 2)
			{
				row->SetColDataCfg(col, 0, E_SVT_HEX16 | E_SVT_PTR, 4, 0);
				pvalue = row->GetDataSur(col);
				pvalue->value.vptr = rms;
				pvalue = row->GetDataEdit(col);
				row->SetColData(col, &pvalue->value.u16);
				col++;
			}
		}
		else
		{
			break;
		}
	}
	wnd.Show();
	return 1;
}
