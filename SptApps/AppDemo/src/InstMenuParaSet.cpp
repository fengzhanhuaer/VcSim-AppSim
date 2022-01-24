#include "InstResource.h"
bool8 MakeParaSetMenu(ApiMenu* Menu, ApiHmiGridWnd& wnd, SalParaEditGroup* ParaGroup, bool8 Edit)
{
	uint32 dataNum = ParaGroup->CurEditCellNum();
	st64value* pvalue;
	uint8 col = 1;
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalParaEditCell* para = ParaGroup->EditCell(i);
		if (para)
		{
			SalPara* des = para->Des();
			if (!des->Disp())
			{
				continue;
			}
			col = 1;
			struct HmiGridWndDataMapRow* row = wnd.CreatRow();
			row->SetName(des->Name());
			//定值
			pvalue = row->GetDataSur(col);
			pvalue->value.vptr = para;
			row->SetColData(col, Edit, para, 16);
			col++;
			row->SetColDataCfg(col, 0, E_SVT_STR | E_SVT_PTR, 5, 0);
			row->SetColStrData(col, des->Unit(), 0);
			col++;
		}
		else
		{
			break;
		}
	}
	return 1;
}
bool8 DispProtSet(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd(0);
	HmiParaEditGroup.Set((SalParaGroup*)&ProtParaGroup, 0);
	wnd.SetInfo("保护定值", ProtParaGroup.GetCrc(0), 2);
	MakeParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
	wnd.Show();
	return 1;
}
bool8 EditProtSet(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd(0);
	wnd.SetInfo("保护定值", 0, 0);
	HmiParaEditGroup.Set((SalParaGroup*)&ProtParaGroup, 0);
	MakeParaSetMenu(Menu, wnd, &HmiParaEditGroup, 1);
	wnd.Edit();
	if (wnd.IsDataChange())
	{
		ApiSelectDialog dig("定值已修改是否保存?", 0, 0, 0, 0);
		if (dig.Show() == 0)
		{
			if (HmiParaEditGroup.SavePara() == 0)
			{
				if (AppSendPara2SubBoard(&ProtParaGroup, 0) == 0)
				{
					ApiWarnDialog dig1("定值保存成功!", 0, 0, 0, 0);
					dig1.Show();
				}
				else
				{
					ApiWarnDialog dig1("定值下发失败!", 0, 0, 0, 0);
					dig1.Show();
				}
			}
			else
			{
				ApiWarnDialog dig1("定值保存失败!", 0, 0, 0, 0);
				dig1.Show();
			}
		}
	}
	return 1;
}
static int32 HmiViewAtPtCtParaAnglogUpdateData(class HmiGridWnd* Wnd, struct HmiGridWndDataMap* Map, HmiKey Key)
{
	uint32 dataNum = HmiParaEditGroup.CurEditCellNum();
	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiAnglogRmsGroup[0];
	st64value* pvalue;
	uint8 col = 1;
	uint32 rown = 0;
	uint32 bufIndex = anmsGroup->GetNewestDataIndex();
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalParaEditCell* para = HmiParaEditGroup.EditCell(i);
		if (para)
		{
			SalPara* des = para->Des();
			if (!des->Disp())
			{
				continue;
			}
			col = 1;
			SalAngRms* rms = anmsGroup->Cell((uint32)des->ExInfo1().value.i32);
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
				pvalue->value.i32 = rmsValue->data1;//二次值
				col++;
				col++;
				pvalue = row->GetDataEdit(col);
				pvalue->value.i32 = rmsValue->data2;//角度
				col++;
				//可以在此处进行校准计算，通过下述方式修改校准后的值	
				//HmiParaEditGroup.EditCell(0)->Buf()[0] = 0.01;
				//HmiParaEditGroup.EditCell(1)->Buf()[0] = 0.01;
				//HmiParaEditGroup.EditCell(2)->Buf()[0] = 0.01;
			}
			else
			{
				break;
			}
		}
	}
	return 0;
}
bool8 MakePtCtParaSetMenu(ApiMenu* Menu, ApiHmiGridWnd& wnd, SalParaEditGroup* ParaGroup, bool8 Edit)
{
	uint32 dataNum = ParaGroup->CurEditCellNum();
	SalAngRmsGroup* anmsGroup = (SalAngRmsGroup*)&ApiAnglogRmsGroup[0];
	st64value* pvalue;
	uint8 col = 1;
	for (uint16 i = 0; i < dataNum; i++)
	{
		SalParaEditCell* para = ParaGroup->EditCell(i);
		if (para)
		{
			SalPara* des = para->Des();
			if (!des->Disp())
			{
				continue;
			}
			col = 1;
			struct HmiGridWndDataMapRow* row = wnd.CreatRow();
			row->SetName(des->Name());
			SalAngRms* rms = anmsGroup->Cell((uint32)des->ExInfo1().value.i32);
			if (rms)
			{
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
			}
			else
			{
				col++;
				col++;
				col++;
				col++;
			}

			//定值
			pvalue = row->GetDataSur(col);
			pvalue->value.vptr = para;
			row->SetColData(col, Edit, para, 16);
			col++;
		}
		else
		{
			break;
		}
	}
	return 1;
}
bool8 EditPtctParaSet(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd(HmiViewAtPtCtParaAnglogUpdateData);
	wnd.SetInfo("PtCt参数", PtctParaGroup.GetCrc(0), 2);
	HmiParaEditGroup.Set((SalParaGroup*)&PtctParaGroup, 0);
	MakePtCtParaSetMenu(Menu, wnd, &HmiParaEditGroup, 1);
	//可以在此处自动进行校准，通过以下方式实现数值修改,序号与参数的定义顺序一致
	//HmiParaEditGroup.EditCell(0)->Buf()[0] = 0.01;
	//HmiParaEditGroup.EditCell(1)->Buf()[0] = 0.01;
	//HmiParaEditGroup.EditCell(2)->Buf()[0] = 0.01;
	wnd.Edit();
	if (wnd.IsDataChange())
	{
		ApiSelectDialog dig("定值已修改是否保存?", 0, 0, 0, 0);
		if (dig.Show() == 0)
		{
			if (HmiParaEditGroup.SavePara() == 0)
			{
				ApiWarnDialog dig1("定值保存成功!", 0, 0, 0, 0);
				dig1.Show();
			}
			else
			{
				ApiWarnDialog dig1("定值保存失败!", 0, 0, 0, 0);
				dig1.Show();
			}
		}
	}
	return 1;
}
bool8 DispPtctParaSet(ApiMenu* Menu)
{
	ApiHmiGridWnd wnd(HmiViewAtPtCtParaAnglogUpdateData);
	wnd.SetInfo("PtCt参数", PtctParaGroup.GetCrc(0), 2);
	HmiParaEditGroup.Set((SalParaGroup*)&PtctParaGroup, 0);
	MakePtCtParaSetMenu(Menu, wnd, &HmiParaEditGroup, 0);
	wnd.Show();
	return 1;
}
bool8 EditEthnetPara(ApiMenu* Menu)
{
	ApiSysEthNetCfg& UsrCfg = ApiSysEthNetCfg::Instance();
	ApiHmiGridWnd wnd(0);
	wnd.SetInfo("网络参数", 0, 0);
	HmiGridWndDataMapRow* row;
	UsrCfg.ValueToEditBuf();
	row = wnd.CreatRow();
	row->SetCfgData(&UsrCfg.EthNet[0].ip);
	row = wnd.CreatRow();
	row->SetCfgData(&UsrCfg.EthNet[0].musk);
	row = wnd.CreatRow();
	row->SetCfgData(&UsrCfg.EthNet[0].gate);
	row = wnd.CreatRow();
	row->SetCfgData(&UsrCfg.EthNet[0].mac);
	wnd.Edit();
	if (wnd.IsDataChange())
	{
		ApiSelectDialog dig("参数已修改是否保存?", 0, 0, 0, 0);
		if (dig.Show() == 0)
		{
			UsrCfg.EditBufToValue();

			if (UsrCfg.SaveAll() > 0)
			{
				ApiWarnDialog dig1("参数保存成功!", 0, 0, 0, 0);
				dig1.Show();
			}
			else
			{
				ApiWarnDialog dig1("参数保存失败!", 0, 0, 0, 0);
				dig1.Show();
			}
		}
	}
	return 1;
}