#include "ApiProject.h"
using namespace spt;

void spt::HmiGridWndDataMap::ResetStatus()
{
	rowNum = 0;
	pageNum = 0;
	maxRowCellNum = 0;
	for (uint32 i = 0; i < CN_Max_Hmi_Grid_Page; i++)
	{
		page[i].ResetStatus();
		page[i].page = i;
		page[i].pMap = this;
	}
	for (uint32 i = 0; i < M_ArrLen(row); i++)
	{
		row[i].ResetStatus();
	}
	for (uint32 i = 0; i < M_ArrLen(rowCellLen); i++)
	{
		rowCellLen[i] = 0;
		rowCellDataLen[i] = 0;
		rowCellUnitLen[i] = 0;
		cellCol[i] = 0;
	}
}


void spt::HmiGridWndDataMapCell::ResetStatus()
{
	edit = 0;
	toStr = 0;
	editMax = editMin = 0;
	isEnable = 0;
	isCanSelect = 0;
	MemSet(&dataSur, 0, sizeof(st32value));
	MemSet(&dataExInfo, 0, sizeof(st32value));
	MemSet(&dataDisp, 0, sizeof(st32value));
	row = 0;
	pRow = 0;
	col = 0;
	dataLen = 0;
	unitLen = 0;
	fullLen = 0;
	isFromRight = 0;
	page = 0;
	pPageCell = 0;
	dotLen = 0;
	unit = 0;
}

void spt::HmiGridWndDataMapPage::ResetStatus()
{
	isEnable = 0;
	rowNum = 0;
	isCanSelect = 0;
	page = 0;
	pMap = 0;
	for (uint32 i = 0; i < M_ArrLen(pRow); i++)
	{
		pRow[i] = 0;
	}
}

void spt::HmiGridWndDataMapRow::SetName(const char* Name)
{
	isEnable = 1;
	cell[0].dataDisp.valueType = E_SVT_STR;
	cell[0].dataDisp.value.str = (char*)Name;
	cell[0].dataLen = StrLen(Name);
	cell[0].toStr = HmiGridWndDataMapCellStrDisp;
	cell[0].isEnable = 1;
}
void spt::HmiGridWndDataMapRow::SetName(const char* Name, HmiGridWndDataMapCellEidt edit)
{
	isEnable = 1;
	cell[0].dataDisp.valueType = E_SVT_STR;
	cell[0].dataDisp.value.str = (char*)Name;
	cell[0].dataLen = StrLen(Name);
	cell[0].toStr = HmiGridWndDataMapCellStrDisp;
	cell[0].isEnable = 1;
	cell[0].isCanSelect = 1;
	cell[0].edit = edit;
}
const char dotassic[] = ".";
const char coloassic[] = ":";
void spt::HmiGridWndDataMapRow::SetCfgData(CfgDataBase* DataCfg)
{
	SetName(DataCfg->Name());
	if (DataCfg->CfgType() == CfgDataBase::E_Normal)
	{
		SetColDataRange(1, DataCfg->Max(), DataCfg->Min());
		if (DataCfg->Value().valueType == E_SVT_I32)
		{
			SetColDataCfg(1, 1, E_SVT_I32 | E_SVT_PTR, 11, DataCfg->DotNum());
			SetColData(1, &DataCfg->EditValue().value.i32);
			SetColDataCfg(2, 0, E_SVT_STR | E_SVT_PTR, 5, 0);
			SetColStrData(2, DataCfg->Unit(), 0);
		}
		else if (DataCfg->Value().valueType == E_SVT_U32)
		{
			SetColDataCfg(1, 1, E_SVT_U32 | E_SVT_PTR, 11, DataCfg->DotNum());
			SetColData(1, &DataCfg->EditValue().value.u32);
			SetColDataCfg(2, 0, E_SVT_STR | E_SVT_PTR, 5, 0);
			SetColStrData(2, DataCfg->Unit(), 0);
		}
		else if (DataCfg->Value().valueType == E_SVT_BOOL)
		{
			SetColDataCfg(1, 1, E_SVT_U8 | E_SVT_PTR, 11, 0);
			SetColData(1, &DataCfg->EditValue().value.u8);
			SetColDataCfg(2, 0, E_SVT_STR | E_SVT_PTR, 5, 0);
			SetColStrData(2, DataCfg->Unit(), 0);
		}
		else if (DataCfg->Value().valueType == E_SVT_HEX32)
		{
			SetColDataCfg(1, 1, E_SVT_HEX32 | E_SVT_PTR, 11, 0);
			SetColData(1, &DataCfg->EditValue().value.u32);
			SetColDataCfg(2, 0, E_SVT_STR | E_SVT_PTR, 5, 0);
			SetColStrData(2, DataCfg->Unit(), 0);
		}
	}
	else if (DataCfg->CfgType() == CfgDataBase::E_IP)
	{
		SetColDataRange(1, 255, 0);
		SetColDataCfg(1, 1, E_SVT_U8 | E_SVT_PTR, 3, DataCfg->DotNum(), dotassic);
		SetColData(1, &DataCfg->EditValue().value.u8);

		SetColDataRange(2, 255, 0);
		SetColDataCfg(2, 1, E_SVT_U8 | E_SVT_PTR, 3, DataCfg->DotNum(), dotassic);
		SetColData(2, &DataCfg->EditValue().value.u8 + 1);

		SetColDataRange(3, 255, 0);
		SetColDataCfg(3, 1, E_SVT_U8 | E_SVT_PTR, 3, DataCfg->DotNum(), dotassic);
		SetColData(3, &DataCfg->EditValue().value.u8 + 2);

		SetColDataRange(4, 255, 0);
		SetColDataCfg(4, 1, E_SVT_U8 | E_SVT_PTR, 3, DataCfg->DotNum());
		SetColData(4, &DataCfg->EditValue().value.u8 + 3);
	}
	else if (DataCfg->CfgType() == CfgDataBase::E_MAC)
	{
		SetColDataRange(1, 255, 0);
		SetColDataCfg(1, 1, E_SVT_U8 | E_SVT_PTR, 3, DataCfg->DotNum(), coloassic);
		SetColData(1, &DataCfg->EditValue().value.u8);

		SetColDataRange(2, 255, 0);
		SetColDataCfg(2, 1, E_SVT_U8 | E_SVT_PTR, 3, DataCfg->DotNum(), coloassic);
		SetColData(2, &DataCfg->EditValue().value.u8 + 1);

		SetColDataRange(3, 255, 0);
		SetColDataCfg(3, 1, E_SVT_U8 | E_SVT_PTR, 3, DataCfg->DotNum(), coloassic);
		SetColData(3, &DataCfg->EditValue().value.u8 + 2);

		SetColDataRange(4, 255, 0);
		SetColDataCfg(4, 1, E_SVT_U8 | E_SVT_PTR, 3, DataCfg->DotNum(), coloassic);
		SetColData(4, &DataCfg->EditValue().value.u8 + 3);

		SetColDataRange(5, 255, 0);
		SetColDataCfg(5, 1, E_SVT_U8 | E_SVT_PTR, 3, DataCfg->DotNum(), coloassic);
		SetColData(5, &DataCfg->EditValue().value.u8 + 4);

		SetColDataRange(6, 255, 0);
		SetColDataCfg(6, 1, E_SVT_U8 | E_SVT_PTR, 3, DataCfg->DotNum());
		SetColData(6, &DataCfg->EditValue().value.u8 + 5);
	}

}

void spt::HmiGridWndDataMapRow::SetColDataCfg(uint32 Col, HmiGridWndDataMapCellToStr toStr, HmiGridWndDataMapCellEidt edit, bool8 IsEditAble, uint16 Type, uint16 Len, uint16 DotLen, bool8 isFromRight)
{
	if (Col < M_ArrLen(cell))
	{
		cell[Col].edit = edit;
		cell[Col].toStr = toStr;
		cell[Col].dataDisp.valueType = (uint8)Type;
		cell[Col].dataLen = (uint8)Len;
		cell[Col].dotLen = (uint8)DotLen;
		cell[Col].dataDisp.value.i64 = 0;
		cell[Col].isFromRight = isFromRight;
		cell[Col].isCanSelect = (IsEditAble == 1);
	}
}

void spt::HmiGridWndDataMapRow::SetColDataCfg(uint32 Col, bool8 IsEditAble, uint16 Type, uint16 Len, uint16 DotLen, const char* Unit, bool8 isFromRight)
{
	if (Col < M_ArrLen(cell))
	{
		cell[Col].unit = Unit;
		switch (Type)
		{
		case E_SVT_PTR | E_SVT_STR:
			SetColDataCfg(Col, HmiGridWndDataMapCellStrDisp, HmiGridWndDataMapCellEdit, IsEditAble == 1, Type, Len, DotLen, isFromRight);
			break;
		case E_SVT_PTR | E_SVT_U8:
			SetColDataCfg(Col, HmiGridWndDataMapCellPU8Disp, HmiGridWndDataMapCellEdit, IsEditAble == 1, Type, Len, DotLen, isFromRight);
			break;
		case E_SVT_PTR | E_SVT_U16:
			SetColDataCfg(Col, HmiGridWndDataMapCellPU16Disp, HmiGridWndDataMapCellEdit, IsEditAble == 1, Type, Len, DotLen, isFromRight);
			break;
		case E_SVT_PTR | E_SVT_U32:
			SetColDataCfg(Col, HmiGridWndDataMapCellPU32Disp, HmiGridWndDataMapCellEdit, IsEditAble == 1, Type, Len, DotLen, isFromRight);
			break;
		case E_SVT_PTR | E_SVT_HEX8:
			SetColDataCfg(Col, HmiGridWndDataMapCellPHex8Disp, HmiGridWndDataMapCellEdit, IsEditAble == 1, Type, Len, DotLen, isFromRight);
			break;
		case E_SVT_PTR | E_SVT_HEX16:
			SetColDataCfg(Col, HmiGridWndDataMapCellPHex16Disp, HmiGridWndDataMapCellEdit, IsEditAble == 1, Type, Len, DotLen, isFromRight);
			break;
		case E_SVT_PTR | E_SVT_HEX32:
			SetColDataCfg(Col, HmiGridWndDataMapCellPHex32Disp, HmiGridWndDataMapCellEdit, IsEditAble == 1, Type, Len, DotLen, isFromRight);
			break;
		case E_SVT_PTR | E_SVT_BIT8:
			SetColDataCfg(Col, HmiGridWndDataMapCellPHex8Disp, HmiGridWndDataMapCellEdit, IsEditAble == 1, Type, Len, DotLen, isFromRight);
			break;
		case E_SVT_PTR | E_SVT_BIT16:
			SetColDataCfg(Col, HmiGridWndDataMapCellPHex16Disp, HmiGridWndDataMapCellEdit, IsEditAble == 1, Type, Len, DotLen, isFromRight);
			break;
		case E_SVT_PTR | E_SVT_BIT32:
			SetColDataCfg(Col, HmiGridWndDataMapCellPHex32Disp, HmiGridWndDataMapCellEdit, IsEditAble == 1, Type, Len, DotLen, isFromRight);
			break;
		case E_SVT_PTR | E_SVT_I8:
			SetColDataCfg(Col, HmiGridWndDataMapCellPI8Disp, HmiGridWndDataMapCellEdit, IsEditAble == 1, Type, Len, DotLen, isFromRight);
			break;
		case E_SVT_PTR | E_SVT_I16:
			SetColDataCfg(Col, HmiGridWndDataMapCellPI16Disp, HmiGridWndDataMapCellEdit, IsEditAble == 1, Type, Len, DotLen, isFromRight);
			break;
		case E_SVT_PTR | E_SVT_I32:
			SetColDataCfg(Col, HmiGridWndDataMapCellPI32Disp, HmiGridWndDataMapCellEdit, IsEditAble == 1, Type, Len, DotLen, isFromRight);
			break;
		case E_SVT_PTR | E_SVT_ENUM8:
			SetColDataCfg(Col, HmiGridWndDataMapCellPEDUM8Disp, HmiGridWndDataMapCellEdit, IsEditAble == 1, Type, Len, DotLen, isFromRight);
			break;
		case E_SVT_PTR | E_SVT_ENUM16:
			SetColDataCfg(Col, HmiGridWndDataMapCellPEDUM16Disp, HmiGridWndDataMapCellEdit, IsEditAble == 1, Type, Len, DotLen, isFromRight);
			break;
		case E_SVT_PTR | E_SVT_ENUM32:
			SetColDataCfg(Col, HmiGridWndDataMapCellPEDUM32Disp, HmiGridWndDataMapCellEdit, IsEditAble == 1, Type, Len, DotLen, isFromRight);
			break;
		default:
			break;
		}
	}
}

void spt::HmiGridWndDataMapRow::SetColData(uint32 Col, const uint32* Ptr)
{
	if (Col < M_ArrLen(cell))
	{
		if ((E_SVT_PTR | E_SVT_U32) == cell[Col].dataDisp.valueType)
		{
			cell[Col].dataDisp.value.vptr = (uint32*)Ptr;
			cell[Col].isEnable = 1;
		}
		else if ((E_SVT_PTR | E_SVT_HEX32) == cell[Col].dataDisp.valueType)
		{
			cell[Col].dataDisp.value.vptr = (uint32*)Ptr;
			cell[Col].isEnable = 1;
		}
		else if ((E_SVT_PTR | E_SVT_BIT32) == cell[Col].dataDisp.valueType)
		{
			cell[Col].dataDisp.value.vptr = (uint32*)Ptr;
			cell[Col].isEnable = 1;
		}
		else
		{
			cell[Col].dataDisp.value.vptr = 0;
		}
	}
}

void spt::HmiGridWndDataMapRow::SetColDataDp(uint32 Col, const uint8* Ptr)
{
	if (Col < M_ArrLen(cell))
	{
		if ((E_SVT_PTR | E_SVT_ENUM8) == cell[Col].dataDisp.valueType)
		{
			SetColData(Col, (uint8*)Ptr, DpEnumDes, 4);
		}
	}
}

void spt::HmiGridWndDataMapRow::SetColData(uint32 Col, const uint16* Ptr)
{
	if (Col < M_ArrLen(cell))
	{
		if ((E_SVT_PTR | E_SVT_U16) == cell[Col].dataDisp.valueType)
		{
			cell[Col].dataDisp.value.vptr = (uint16*)Ptr;
			cell[Col].isEnable = 1;
		}
		else if ((E_SVT_PTR | E_SVT_HEX16) == cell[Col].dataDisp.valueType)
		{
			cell[Col].dataDisp.value.vptr = (uint16*)Ptr;
			cell[Col].isEnable = 1;
		}
		else if ((E_SVT_PTR | E_SVT_BIT16) == cell[Col].dataDisp.valueType)
		{
			cell[Col].dataDisp.value.vptr = (uint16*)Ptr;
			cell[Col].isEnable = 1;
		}
		else
		{
			cell[Col].dataDisp.value.vptr = 0;
		}
	}
}

void spt::HmiGridWndDataMapRow::SetColData(uint32 Col, const uint8* Ptr)
{
	if (Col < M_ArrLen(cell))
	{
		if ((E_SVT_PTR | E_SVT_U8) == cell[Col].dataDisp.valueType)
		{
			cell[Col].dataDisp.value.vptr = (uint8*)Ptr;
			cell[Col].isEnable = 1;
		}
		else if ((E_SVT_PTR | E_SVT_HEX8) == cell[Col].dataDisp.valueType)
		{
			cell[Col].dataDisp.value.vptr = (uint8*)Ptr;
			cell[Col].isEnable = 1;
		}
		else if ((E_SVT_PTR | E_SVT_BIT8) == cell[Col].dataDisp.valueType)
		{
			cell[Col].dataDisp.value.vptr = (uint8*)Ptr;
			cell[Col].isEnable = 1;
		}
		else
		{
			cell[Col].dataDisp.value.vptr = 0;
		}
	}
}

void spt::HmiGridWndDataMapRow::SetColData(uint32 Col, const int32* Ptr)
{
	if (Col < M_ArrLen(cell))
	{
		if ((E_SVT_PTR | E_SVT_I32) == cell[Col].dataDisp.valueType)
		{
			cell[Col].dataDisp.value.vptr = (int32*)Ptr;
			cell[Col].isEnable = 1;
		}
		else
		{
			cell[Col].dataDisp.value.vptr = 0;
		}
	}
}

void spt::HmiGridWndDataMapRow::SetColData(uint32 Col, const int16* Ptr)
{
	if (Col < M_ArrLen(cell))
	{
		if ((E_SVT_PTR | E_SVT_I16) == cell[Col].dataDisp.valueType)
		{
			cell[Col].dataDisp.value.vptr = (int16*)Ptr;
			cell[Col].isEnable = 1;
		}
		else
		{
			cell[Col].dataDisp.value.vptr = 0;
		}
	}
}

void spt::HmiGridWndDataMapRow::SetColData(uint32 Col, bool8 Edit, SalParaEditCell* Ptr, uint8 Len)
{
	SalPara* des = Ptr->Des();
	if (des->ValueType() == SalPara::E_PT_Str)
	{
		SetColDataCfg(Col, Edit, E_SVT_PTR | E_SVT_STR, Len, des->DotNum());
		SetColStrData(Col, (const char*)Ptr->Buf(), 1);
	}
	else if (des->ValueType() == SalPara::E_PT_Int32)
	{
		if (Len > 12)
		{
			SetColDataCfg(Col, Edit, E_SVT_PTR | E_SVT_I32, 12, des->DotNum());
		}
		else
		{
			SetColDataCfg(Col, Edit, E_SVT_PTR | E_SVT_I32, Len, des->DotNum());
		}
		SetColDataRange(Col, des->Max(), des->Min());
		SetColData(Col, Ptr->Buf());
	}
	else if (des->ValueType() == SalPara::E_PT_UInt32)
	{
		if (Len > 12)
		{
			SetColDataCfg(Col, Edit, E_SVT_PTR | E_SVT_U32, 12, des->DotNum());
		}
		else
		{
			SetColDataCfg(Col, Edit, E_SVT_PTR | E_SVT_U32, Len, des->DotNum());

		}
		SetColDataRange(Col, (uint32)des->Max(), (uint32)des->Min());
		SetColData(Col, (uint32*)Ptr->Buf());
	}
	else if (des->ValueType() == SalPara::E_PT_Ct_Second)
	{
		SetColDataCfg(Col, Edit, E_SVT_PTR | E_SVT_ENUM32, 1, 0);
		SetColDataRange(Col, des->Max(), des->Min());
		SetColData(Col, (uint32*)Ptr->Buf(), (SalEnumDes*)des->ExInfo1().value.vptr, des->ExInfo1().valueInfo1);
	}
	else if (des->ValueType() == SalPara::E_PT_Enum)
	{
		SetColDataCfg(Col, Edit, E_SVT_PTR | E_SVT_ENUM32, Len, 0);
		SetColDataRange(Col, des->Max(), des->Min());
		SetColData(Col, (uint32*)Ptr->Buf(), (SalEnumDes*)des->ExInfo1().value.vptr, des->ExInfo1().valueInfo1);
	}
	else if (des->ValueType() == SalPara::E_PT_BIT8)
	{
		SetColDataCfg(Col, Edit, E_SVT_PTR | E_SVT_BIT8, 2, 0);
		SetColDataRange(Col, (uint32)des->Max(), (uint32)des->Min());
		SetColData(Col, (uint8*)Ptr->Buf(), (SalBitDes*)des->ExInfo1().value.vptr);
	}
	else if (des->ValueType() == SalPara::E_PT_BIT16)
	{
		SetColDataCfg(Col, Edit, E_SVT_PTR | E_SVT_BIT16, 4, 0);
		SetColDataRange(Col, (uint32)des->Max(), (uint32)des->Min());
		SetColData(Col, (uint16*)Ptr->Buf(), (SalBitDes*)des->ExInfo1().value.vptr);
	}
	else if (des->ValueType() == SalPara::E_PT_BIT32)
	{
		SetColDataCfg(Col, Edit, E_SVT_PTR | E_SVT_BIT32, 8, 0);
		SetColDataRange(Col, (uint32)des->Max(), (uint32)des->Min());
		SetColData(Col, (uint32*)Ptr->Buf(), (SalBitDes*)des->ExInfo1().value.vptr);
	}
	else if (des->ValueType() == SalPara::E_PT_Zone)
	{
		SetColDataCfg(Col, 0, E_SVT_PTR | E_SVT_I32, 2, des->DotNum());
		SetColDataRange(Col, (uint32)des->Max(), (uint32)des->Min());
		SetColData(Col, Ptr->Buf());
	}
	else if (des->ValueType() == SalPara::E_PT_HEX8)
	{
		SetColDataCfg(Col, Edit, E_SVT_PTR | E_SVT_HEX8, Len, 0);
		SetColDataRange(Col, (uint32)des->Max(), (uint32)des->Min());
		SetColData(Col, (uint8*)Ptr->Buf());
	}
	else if (des->ValueType() == SalPara::E_PT_HEX16)
	{
		SetColDataCfg(Col, Edit, E_SVT_PTR | E_SVT_HEX16, Len, 0);
		SetColDataRange(Col, (uint32)des->Max(), (uint32)des->Min());
		SetColData(Col, (uint16*)Ptr->Buf());
	}
	else if (des->ValueType() == SalPara::E_PT_HEX32)
	{
		SetColDataCfg(Col, Edit, E_SVT_PTR | E_SVT_HEX32, Len, 0);
		SetColDataRange(Col, (uint32)des->Max(), (uint32)des->Min());
		SetColData(Col, (uint32*)Ptr->Buf());
	}
	else if (des->ValueType() == SalPara::E_PT_UnitSet)
	{
		//fixme 间隔投退编辑框需要单独在开发，暂时使用通用编辑框
		SetColDataCfg(Col, HmiGridWndDataMapCellStrDisp, HmiGridWndDataMapCellEdit, Edit, E_SVT_PTR | E_SVT_U32, 2, 0, 1);
		SetColDataRange(Col, (uint32)des->Max(), (uint32)des->Min());
		SetColData(Col, (uint32*)Ptr->Buf());
	}
}

void spt::HmiGridWndDataMapRow::SetColData(uint32 Col, const int8* Ptr)
{
	if (Col < M_ArrLen(cell))
	{
		if ((E_SVT_PTR | E_SVT_I8) == cell[Col].dataDisp.valueType)
		{
			cell[Col].dataDisp.value.vptr = (int8*)Ptr;
			cell[Col].isEnable = 1;
		}
		else
		{
			cell[Col].dataDisp.value.vptr = 0;
		}
	}
}

void spt::HmiGridWndDataMapRow::SetColData(uint32 Col, SalStatus* Ptr, uint8 Len)
{
	if (Col < M_ArrLen(cell))
	{
		SetColDataCfg(Col, HmiGridWndDataMapCellStatusFmt1Disp, 0, 0, E_SVT_PTR | E_SVT_Status, Len, 0, 1);
		cell[Col].dataDisp.value.vptr = (void*)Ptr;
		cell[Col].dataDisp.valueInfo1 = 0;
		cell[Col].isEnable = 1;
		cell[Col].unit = 0;
	}
}

void spt::HmiGridWndDataMapRow::SetColStatusTime(uint32 Col, const SalStatus* Ptr, uint8 Len, uint8 Type)
{
	if (Col < M_ArrLen(cell))
	{
		SetColDataCfg(Col, HmiGridWndDataMapCellStatusTimeDisp, 0, 0, E_SVT_PTR | E_SVT_LocalStamp, Len, 0, 1);
		cell[Col].dataDisp.value.vptr = (void*)Ptr;
		cell[Col].dataDisp.valueInfo1 = Type;
		cell[Col].isEnable = 1;
		cell[Col].unit = 0;
	}
}

void spt::HmiGridWndDataMapRow::SetColStrData(uint32 Col, const char* Ptr, bool8 IsFromRight)
{
	if (Col < M_ArrLen(cell))
	{
		if ((E_SVT_PTR | E_SVT_STR) == cell[Col].dataDisp.valueType)
		{
			cell[Col].dataDisp.value.vptr = (int8*)Ptr;
			cell[Col].isEnable = 1;
			cell[Col].isFromRight = IsFromRight;
		}
		else
		{
			cell[Col].dataDisp.value.vptr = 0;
		}
	}
}

void spt::HmiGridWndDataMapRow::SetColData(uint32 Col, const uint32* Ptr, const SalEnumDes* Des, uint32 Total)
{
	if (Col < M_ArrLen(cell))
	{
		if ((E_SVT_PTR | E_SVT_ENUM32) == cell[Col].dataDisp.valueType)
		{
			cell[Col].dataDisp.value.Enum.value.ptr = (uint8*)Ptr;
			cell[Col].dataDisp.value.Enum.des = (SalEnumDes*)Des;
			cell[Col].dataDisp.valueInfo4 = Total;
			cell[Col].isEnable = 1;
		}
		else
		{
			cell[Col].dataDisp.value.vptr = 0;
		}
	}
}

void spt::HmiGridWndDataMapRow::SetColData(uint32 Col, const uint16* Ptr, const SalEnumDes* Des, uint32 Total)
{
	if (Col < M_ArrLen(cell))
	{
		if ((E_SVT_PTR | E_SVT_ENUM16) == cell[Col].dataDisp.valueType)
		{
			cell[Col].dataDisp.value.Enum.value.ptr = (uint8*)Ptr;
			cell[Col].dataDisp.value.Enum.des = (SalEnumDes*)Des;
			cell[Col].dataDisp.valueInfo4 = Total;
			cell[Col].isEnable = 1;
		}
		else
		{
			cell[Col].dataDisp.value.vptr = 0;
		}
	}
}

void spt::HmiGridWndDataMapRow::SetColData(uint32 Col, const uint8* Ptr, const SalEnumDes* Des, uint32 Total)
{
	if (Col < M_ArrLen(cell))
	{
		if ((E_SVT_PTR | E_SVT_ENUM8) == cell[Col].dataDisp.valueType)
		{
			cell[Col].dataDisp.value.Enum.value.ptr = (uint8*)Ptr;
			cell[Col].dataDisp.value.Enum.des = (SalEnumDes*)Des;
			cell[Col].dataDisp.valueInfo4 = Total;
			cell[Col].isEnable = 1;
		}
		else
		{
			cell[Col].dataDisp.value.vptr = 0;
		}
	}
}

void spt::HmiGridWndDataMapRow::SetColData(uint32 Col, const uint32* Ptr, const SalBitDes* Des)
{
	if (Col < M_ArrLen(cell))
	{
		if ((E_SVT_PTR | E_SVT_BIT8) == cell[Col].dataDisp.valueType)
		{
			cell[Col].dataDisp.value.BitDes.value.ptr = (void*)Ptr;
			cell[Col].dataDisp.value.BitDes.des = (SalBitDes*)Des;
			cell[Col].dataDisp.valueInfo4 = 32;
			cell[Col].isEnable = 1;
		}
		else
		{
			cell[Col].dataDisp.value.vptr = 0;
		}
	}
}

void spt::HmiGridWndDataMapRow::SetColData(uint32 Col, const uint16* Ptr, const SalBitDes* Des)
{
	if (Col < M_ArrLen(cell))
	{
		if ((E_SVT_PTR | E_SVT_BIT16) == cell[Col].dataDisp.valueType)
		{
			cell[Col].dataDisp.value.BitDes.value.ptr = (void*)Ptr;
			cell[Col].dataDisp.value.BitDes.des = (SalBitDes*)Des;
			cell[Col].dataDisp.valueInfo4 = 16;
			cell[Col].isEnable = 1;
		}
		else
		{
			cell[Col].dataDisp.value.vptr = 0;
		}
	}
}

void spt::HmiGridWndDataMapRow::SetColData(uint32 Col, const uint8* Ptr, const SalBitDes* Des)
{
	if (Col < M_ArrLen(cell))
	{
		if ((E_SVT_PTR | E_SVT_BIT32) == cell[Col].dataDisp.valueType)
		{
			cell[Col].dataDisp.value.BitDes.value.ptr = (void*)Ptr;
			cell[Col].dataDisp.value.BitDes.des = (SalBitDes*)Des;
			cell[Col].dataDisp.valueInfo4 = 8;
			cell[Col].isEnable = 1;
		}
		else
		{
			cell[Col].dataDisp.value.vptr = 0;
		}
	}
}

st64value* spt::HmiGridWndDataMapRow::GetDataSur(uint32 Col)
{
	if (Col < M_ArrLen(cell))
	{
		return &cell[Col].dataSur;
	}
	return 0;
}

st64value* spt::HmiGridWndDataMapRow::GetDataExInfo(uint32 Col)
{
	if (Col < M_ArrLen(cell))
	{
		return &cell[Col].dataExInfo;
	}
	return 0;
}

st64value* spt::HmiGridWndDataMapRow::GetDataEdit(uint32 Col)
{
	if (Col < M_ArrLen(cell))
	{
		return &cell[Col].dataEdit;
	}
	return 0;
}

void spt::HmiGridWndDataMapRow::SetColDataCfg(uint32 Col, bool8 IsEditAble, uint16 Type, uint16 Len, uint16 DotLen, bool8 isFromRight)
{
	SetColDataCfg(Col, IsEditAble, Type, Len, DotLen, 0, isFromRight);
}

void spt::HmiGridWndDataMapRow::SetColDataRange(uint32 Col, int64 Max, int64 Min)
{
	if (Col < M_ArrLen(cell))
	{
		cell[Col].editMin = Min;
		cell[Col].editMax = Max;
	}
}

void spt::HmiGridWndDataMapRow::ResetStatus()
{
	isEnable = 0;
	isCanSelect = 0;
	page = 0;
	cellNum = 0;
	for (uint32 i = 0; i < M_ArrLen(cell); i++)
	{
		cell[i].ResetStatus();
		cell[i].pRow = this;
	}
	pPage = 0;
}


spt::HmiGridWnd::HmiGridWnd()
{
	isFirstLayerout = 0;
	map.ResetStatus();
	isEditData = isDataChange = 0;
	context.SetVisible(1);
	title.SetVisible(1);
	updateData = 0;
}
HmiGridWndDataMap HmiGridWnd::map;
void spt::HmiGridWnd::Show()
{
	HmiKey key = { 0 };
	bool8 first = 1;
	MsStampTimer timer;
	timer.Enable(1);
	uint32 total;
	uint32 step;
	uint32 page;
	AutoLayerOut();
	if (title.TotalPage() >= M_ArrLen(map.page))
	{
		HmiWarnDialog dig;
		dig.SetTitle("总页数超过最大允许值", 0, 0, 0, 0);
		return;
	}
	while (1)
	{
		if (this->key->Pop(key))
		{
			if (key.Key1 == EK1_KEYVALUE)
			{
				E_KEY2 k2 = (E_KEY2)key.Key2;
				switch (k2)
				{
				case spt::EK_ENTER:
					first = 1;
					break;
				case spt::EK_LEFT:
					total = title.TotalPage();
					step = total / 5;
					if (!step)
					{
						step = 1;
					}
					page = title.Page();
					if (page > step)
					{
						page = page - step;
					}
					else
					{
						page = 0;
					}
					title.SetPage(page, total);
					SetPage(&map.page[title.Page()]);
					first = 1;
					break;
				case spt::EK_UP:
					total = title.TotalPage();
					step = 1;
					page = title.Page();
					if (page >= step)
					{
						page = page - step;
					}
					else
					{
						page = total - step;
					}
					title.SetPage(page, total);
					SetPage(&map.page[title.Page()]);
					first = 1;
					break;
				case spt::EK_RIGHT:
					total = title.TotalPage();
					step = total / 5;
					if (!step)
					{
						step = 1;
					}
					page = title.Page() + step;
					if (page >= total)
					{
						page = total - 1;
					}
					title.SetPage(page, total);
					SetPage(&map.page[title.Page()]);
					first = 1;
					break;
				case spt::EK_DOWN:
					total = title.TotalPage();
					step = 1;
					page = title.Page() + step;
					if (page >= total)
					{
						page = 0;
					}
					title.SetPage(page, total);
					SetPage(&map.page[title.Page()]);
					first = 1;
					break;
				case spt::EK_ESC:
					UnShow();
					gd->Update(rect);
					return;
				case spt::EK_MD_STOP:
					UnShow();
					gd->Update(rect);
					return;
				default:
					break;
				}
			}
		}
		else
		{
			HmiMain::Instance().MsSleep(50);
		}
		if (timer.Status(100))
		{
			if (first)
			{
				if (updateData)
				{
					updateData(this, &map, key);
				}
				first = 0;
				HmiGridPage::Show(E_AllFrame);
				gd->Update(rect);
				timer.StartTimer();
			}
			else if (timer.Status(1000))
			{
				if (updateData)
				{
					key.Key1 = 0;
					updateData(this, &map, key);
				}
				HmiGridPage::Show(E_Update);
				gd->Update(rect);
				timer.StartTimer();
			}
		}
	}
	UnShow();
	gd->Update(rect);
	return;
}

int32 spt::HmiGridWnd::Edit()
{
	isEditCellMode = 1;
	HmiKey key;
	bool8 first = 1;
	MsStampTimer timer;
	timer.Enable(1);
	uint32 total;
	uint32 step;
	uint32 page;
	AutoLayerOut();
	isDataChange = isEditData = 0;
	if (title.TotalPage() >= M_ArrLen(map.page))
	{
		HmiWarnDialog dig;
		dig.SetTitle("总页数超过最大允许值", 0, 0, 0, 0);
		return -1;
	}
	while (1)
	{
		if (this->key->Pop(key))
		{
			if (key.Key1 == EK1_KEYVALUE)
			{
				E_KEY2 k2 = (E_KEY2)key.Key2;
				switch (k2)
				{
				case spt::EK_ENTER:
					if (selectChild && selectChild->pCell)
					{
						if (selectChild->pCell->edit)
						{
							bool8 iChange = 0;
							if (0 == selectChild->pCell->edit(iChange, selectChild->pCell))
							{
								isDataChange |= iChange;
							}
							isEditData = 1;
						}
					}
					first = 1;
					break;
				case spt::EK_LEFT:
					total = title.TotalPage();
					step = 1;
					if (!step)
					{
						step = 1;
					}
					page = title.Page();
					if (page > step)
					{
						page = page - step;
					}
					else
					{
						page = 0;
					}
					title.SetPage(page, total);
					SetPage(&map.page[title.Page()]);
					SetSelectedChildAt(0);
					first = 1;
					break;
				case spt::EK_UP:
					GoToLastCanBeSelected();
					first = 1;
					break;
				case spt::EK_RIGHT:
					total = title.TotalPage();
					step = 1;
					if (!step)
					{
						step = 1;
					}
					page = title.Page() + step;
					if (page >= total)
					{
						page = total - 1;
					}
					title.SetPage(page, total);
					SetPage(&map.page[title.Page()]);
					SetSelectedChildAt(0);
					first = 1;
					break;
				case spt::EK_DOWN:
					GoToNextCanBeSelected();
					first = 1;
					break;
				case spt::EK_ESC:
					UnShow();
					gd->Update(rect);
					return 0;
				case spt::EK_MD_STOP:
					UnShow();
					gd->Update(rect);
					return -1;
				default:
					break;
				}
			}
		}
		else
		{
			HmiMain::Instance().MsSleep(50);
		}
		if (timer.Status(100))
		{
			if (first)
			{
				if (updateData)
				{
					updateData(this, &map, key);
				}
				first = 0;
				HmiGridPage::Show(E_AllFrame);
				gd->Update(rect);
				timer.StartTimer();
			}
			else if (timer.Status(2000))
			{
				if (updateData)
				{
					key.Key1 = 0;
					updateData(this, &map, key);
				}
				HmiGridPage::Show(E_Update);
				gd->Update(rect);
				timer.StartTimer();
			}
		}
	}
	UnShow();
	gd->Update(rect);
	return -1;
}

void spt::HmiGridWnd::AutoLayerOut()
{
	if (isFirstLayerout == 0)
	{
		HmiWidSinglePage::AutoLayerOut();
		uint16 pageRowNum = context.MaxDispRowNum();
		if (hasTitleRow)
		{
			pageRowNum = pageRowNum - 1;
		}
		map.pageNum = (map.rowNum + pageRowNum - 1) / pageRowNum;
		if (!map.pageNum)
		{
			map.pageNum = 1;
		}
		title.SetPage(0, map.pageNum);
		isFirstLayerout = 1;

		for (uint32 i = 0; i < map.rowNum; i++)
		{
			map.row[i].row = i % pageRowNum;
			uint16 page = map.row[i].page = i / pageRowNum;
			map.row[i].pPage = &map.page[page];
			map.page[page].pRow[map.page[page].rowNum] = &map.row[i];
			map.page[page].rowNum++;
			for (uint32 j = 0; j < CN_Max_Hmi_Grid_Page_Row_Cell; j++)
			{
				if (map.row[i].cell[j].unit)
				{
					map.row[i].cell[j].unitLen = StrLen(map.row[i].cell[j].unit);
				}
				else
				{
					map.row[i].cell[j].unitLen = 0;
				}
				if (map.rowCellDataLen[j] < map.row[i].cell[j].dataLen)
				{
					map.rowCellDataLen[j] = map.row[i].cell[j].dataLen;
				}
				if (map.rowCellUnitLen[j] < map.row[i].cell[j].unitLen)
				{
					map.rowCellUnitLen[j] = map.row[i].cell[j].unitLen;
				}
				map.row[i].cell[j].fullLen = map.row[i].cell[j].unitLen + map.row[i].cell[j].dataLen;
				if (map.rowCellLen[j] < map.row[i].cell[j].fullLen)
				{
					map.rowCellLen[j] = map.row[i].cell[j].fullLen;
				}
				if (map.row[i].cell[j].isEnable)
				{
					map.row[i].cellNum++;
				}
				map.row[i].cell[j].page = page;
				map.row[i].cell[j].row = i % pageRowNum;
				map.row[i].cell[j].pRow = &map.row[i];
			}
			if (map.row[i].cellNum > map.maxRowCellNum)
			{
				map.maxRowCellNum = map.row[i].cellNum;
			}
		}
		if (hasTitleRow && (titleCol > map.maxRowCellNum))
		{
			map.maxRowCellNum = titleCol;
		}
		if (hasTitleRow)
		{
			for (uint32 i = 0; i < map.maxRowCellNum; i++)
			{
				if (map.rowCellLen[i] < titleRow[i].Text().StrLen())
				{
					map.rowCellLen[i] = titleRow[i].Text().StrLen();
				}
				titleRow[i].Len = map.rowCellLen[i];
			}
		}
		uint16 rowLen = 0;
		for (uint32 i = 0; i < map.maxRowCellNum; i++)
		{
			rowLen += map.rowCellLen[i];
		}

		uint16 cellspace = 0;
		uint16 endCol = context.MaxDispColNum();
		if ((rowLen < endCol) && (map.maxRowCellNum))
		{
			cellspace = (endCol - rowLen) / map.maxRowCellNum;
			if (cellspace > 3)
			{
				cellspace = 3;
			}
			if (!cellspace)
			{
				cellspace = 1;
			}
		}
		else
		{
			cellspace = 1;
		}
		map.cellCol[0] = titleRow[0].Col = 0;
		if (map.maxRowCellNum >= 2)
		{
			titleRow[map.maxRowCellNum - 1].Col = endCol - map.rowCellLen[map.maxRowCellNum - 1] - cellspace;
			titleRow[map.maxRowCellNum - 1].isFromRight = 1;
			for (uint32 j = map.maxRowCellNum - 2; j > 0; j--)
			{
				map.cellCol[j] = titleRow[j].Col = titleRow[j + 1].Col - map.rowCellLen[j] - cellspace;
				titleRow[j].isFromRight = 1;
			}
		}
		for (uint32 i = 0; i < map.rowNum; i++)
		{
			for (uint32 j = 0; j < CN_Max_Hmi_Grid_Page_Row_Cell; j++)
			{
				if (map.row[i].cell[j].isFromRight)
				{
					map.row[i].cell[j].col = titleRow[j].Col + map.rowCellLen[j] - map.rowCellUnitLen[j] - map.row[i].cell[j].dataLen;
				}
				else
				{
					map.row[i].cell[j].col = titleRow[j].Col;
				}
			}
		}
		pPage = &map.page[0];
	}
	SetPage(&map.page[title.Page()]);
}
HmiGridPageCell HmiGridPage::text[CN_Max_Hmi_Grid_Page_Row][CN_Max_Hmi_Grid_Page_Row_Cell];
spt::HmiGridPage::HmiGridPage()
{
	titleCol = 0;
	hasTitleRow = 0;
	isEditCellMode = 0;
	selectChild = 0;
	context.DeleteAllChild();
	ResetStatus();
}

void spt::HmiGridPage::ResetStatus()
{
	for (uint32 i = 0; i < CN_Max_Hmi_Grid_Page_Row; i++)
	{
		for (uint32 j = 0; j < CN_Max_Hmi_Grid_Page_Row_Cell; j++)
		{
			text[i][j].ResetStatus();
		}
	}
	for (uint32 j = 0; j < CN_Max_Hmi_Grid_Page_Row_Cell; j++)
	{
		titleRow[j].ResetStatus();
	}
}

void spt::HmiGridPage::Show(ShowType Type)
{
	HmiWidSinglePage::Show(Type);
	if (isEditCellMode)
	{
		if (selectChild)
		{
			curse.Rect() = context.GetTextRect(selectChild->Row, selectChild->Col, selectChild->Cell()->dataLen);
			curse.SetText(selectChild->Text().Str());
			curse.IsFromRight() = selectChild->isFromRight;
			curse.ShowSelf(Type);
		}
	}
}

void spt::HmiGridPage::SetColTitle(const char* Title1, const char* Title2, const char* Title3, const char* Title4, const char* Title5, const char* Title6, const char* Title7, const char* Title8, const char* Title9, const char* Title10)
{
	titleCol = 0;
	titleRow[0].SetText(Title1);
	if (Title1)
	{
		titleCol++;
	}
	titleRow[1].SetText(Title2);
	if (Title2)
	{
		titleCol++;
	}
	titleRow[2].SetText(Title3);
	if (Title3)
	{
		titleCol++;
	}
	titleRow[3].SetText(Title4);
	if (Title4)
	{
		titleCol++;
	}
	titleRow[4].SetText(Title5);
	if (Title5)
	{
		titleCol++;
	}
	titleRow[5].SetText(Title6);
	if (Title6)
	{
		titleCol++;
	}
	titleRow[6].SetText(Title7);
	if (Title7)
	{
		titleCol++;
	}
	titleRow[7].SetText(Title8);
	if (Title8)
	{
		titleCol++;
	}
	titleRow[8].SetText(Title9);
	if (Title9)
	{
		titleCol++;
	}
	titleRow[9].SetText(Title10);
	if (Title10)
	{
		titleCol++;
	}
	hasTitleRow = 1;
}

void spt::HmiGridPage::SetPage(HmiGridWndDataMapPage* Page)
{
	selectChild = 0;
	context.DeleteAllChild();
	pPage = Page;
	SetUpdate();
	if (0 == pPage)
	{
		return;
	}
	for (uint32 i = 0; i < CN_Max_Hmi_Grid_Page_Row; i++)
	{
		for (uint32 j = 0; j < CN_Max_Hmi_Grid_Page_Row_Cell; j++)
		{
			text[i][j].ResetStatus();
		}
	}
	uint16 endi = pPage->rowNum;
	uint16 endj = pPage->pMap->maxRowCellNum;
	if (hasTitleRow)
	{
		for (uint16 j = 0; j < endj; j++)
		{
			context.AddChild(&titleRow[j]);
			titleRow[j].SetVisible(1);
		}
	}
	for (uint16 i = 0; i < endi; i++)
	{
		for (uint16 j = 0; j < endj; j++)
		{
			if (Page->pRow[i]->cell[j].isEnable)
			{
				context.AddChild(&text[i][j]);
				text[i][j].SeCell(hasTitleRow == 1, &Page->pRow[i]->cell[j]);
			}
		}
	}
	if (isEditCellMode)
	{
		curse.IsCanBeSelect() = 0;
		curse.IsSelected() = 1;
		SetSelectedChildAt(0);
	}
}

HmiGridPageCell* spt::HmiGridPage::SetSelectedChildAt(int32 Index)
{
	if (selectChild)
	{
		selectChild->IsSelected() = 0;
	}
	selectChild = 0;
	if (0 == pPage)
	{
		return 0;
	}
	uint16 endi = pPage->rowNum;
	uint16 endj = pPage->pMap->maxRowCellNum;
	uint16 now = 0;
	for (uint16 i = 0; i < endi; i++)
	{
		for (uint16 j = 0; j < endj; j++)
		{
			if (text[i][j].IsEnable() && text[i][j].IsCanBeSelect())
			{
				if (now == Index)
				{
					selectChild = &text[i][j];
					selectChild->IsSelected() = 1;
					return selectChild;
				}
				now++;
			}
		}
	}
	return selectChild;
}

HmiGridPageCell* spt::HmiGridPage::GoToNextCanBeSelected()
{
	HmiGridPageCell* end = &text[CN_Max_Hmi_Grid_Page_Row - 1][CN_Max_Hmi_Grid_Page_Row_Cell - 1];
	if (!selectChild)
	{
		return 0;
	}
	HmiGridPageCell* now = selectChild + 1;
	selectChild->IsSelected() = 0;
	while (now <= end)
	{
		if (now->IsEnable() && now->IsCanBeSelect())
		{
			selectChild = now;
			break;
		}
		now++;
	}
	selectChild->IsSelected() = 1;
	return selectChild;
}

HmiGridPageCell* spt::HmiGridPage::GoToLastCanBeSelected()
{
	HmiGridPageCell* end = &text[0][0];
	if (!selectChild)
	{
		return 0;
	}
	HmiGridPageCell* now = selectChild - 1;
	selectChild->IsSelected() = 0;
	while (now >= end)
	{
		if (now->IsEnable() && now->IsCanBeSelect())
		{
			selectChild = now;
			break;
		}
		now--;
	}
	selectChild->IsSelected() = 1;
	return selectChild;
}

void spt::HmiGridPageCell::ResetStatus()
{
	HmiWidContextAreaTextLine::ResetStatus();
	text.Clear();
}

void spt::HmiGridPageCell::SeCell(bool8 HasTitle, HmiGridWndDataMapCell* Cell)
{
	pCell = Cell;
	HasTitle = (HasTitle == 1);
	if (pCell && pCell->isEnable)
	{
		IsCanBeSelect() = pCell->isCanSelect;
		SetVisible(1);
		Row = pCell->row + HasTitle;
		Col = pCell->col;
		isSelected = 0;
		Cell->pPageCell = this;
		Len = pCell->dataLen;
		isFromRight = pCell->isFromRight;
	}
	else
	{
		SetVisible(0);
	}
}

void spt::HmiGridPageCell::UpdateCheck(ShowType Type)
{
	if (pCell && pCell->toStr)
	{
		String100B str;
		SetText(pCell->toStr(str, pCell));
		if (isFromRight)
		{
			HmiWidContextAreaTextLine::UpdateCheck(Type);
		}
	}
}

void spt::HmiGridPageCell::ShowSelf(ShowType Type)
{
	HmiWidContextAreaTextLine::ShowSelf(Type);
	if (pCell->unit && IsHmiWidContextParent())
	{
		HmiWidContextArea* p = (HmiWidContextArea*)parent;
		p->SetText(Row, Len + Col, pCell->unit);
	}
}


const char* spt::HmiGridWndDataMapCellStrDisp(SalString& Str, HmiGridWndDataMapCell* Cell)
{
	Str.Clear();
	Str = Cell->dataDisp.value.str;
	return Str.Str();
}

const char* spt::HmiGridWndDataMapCellPU32Disp(SalString& Str, HmiGridWndDataMapCell* Cell)
{
	Str.Clear();
	if (Cell->dataDisp.value.vptr)
	{
		Str.Format(*Cell->dataDisp.value.pu32, Cell->dotLen);
	}
	return Str.Str();
}

const char* spt::HmiGridWndDataMapCellPU16Disp(SalString& Str, HmiGridWndDataMapCell* Cell)
{
	Str.Clear();
	if (Cell->dataDisp.value.vptr)
	{
		Str.Format((uint32)*Cell->dataDisp.value.pu16, Cell->dotLen);
	}
	return Str.Str();
}

const char* spt::HmiGridWndDataMapCellPU8Disp(SalString& Str, HmiGridWndDataMapCell* Cell)
{
	Str.Clear();
	if (Cell->dataDisp.value.vptr)
	{
		Str.Format((uint32)*Cell->dataDisp.value.pu8, Cell->dotLen);
	}
	return Str.Str();
}

const char* spt::HmiGridWndDataMapCellPI32Disp(SalString& Str, HmiGridWndDataMapCell* Cell)
{
	Str.Clear();
	if (Cell->dataDisp.value.vptr)
	{
		Str.Format(*Cell->dataDisp.value.pi32, Cell->dotLen);
	}
	return Str.Str();
}

const char* spt::HmiGridWndDataMapCellPI16Disp(SalString& Str, HmiGridWndDataMapCell* Cell)
{
	Str.Clear();
	if (Cell->dataDisp.value.vptr)
	{
		Str.Format(*Cell->dataDisp.value.pi16, Cell->dotLen);
	}
	return Str.Str();
}

const char* spt::HmiGridWndDataMapCellPI8Disp(SalString& Str, HmiGridWndDataMapCell* Cell)
{
	Str.Clear();
	if (Cell->dataDisp.value.vptr)
	{
		Str.Format(*Cell->dataDisp.value.pi8, Cell->dotLen);
	}
	return Str.Str();
}

const char* spt::HmiGridWndDataMapCellPHex32Disp(SalString& Str, HmiGridWndDataMapCell* Cell)
{
	Str.Clear();
	if (Cell->dataDisp.value.vptr)
	{
		Str.FormatHex(*Cell->dataDisp.value.pu32);
	}
	return Str.Str();
}

const char* spt::HmiGridWndDataMapCellPHex16Disp(SalString& Str, HmiGridWndDataMapCell* Cell)
{
	Str.Clear();
	if (Cell->dataDisp.value.vptr)
	{
		Str.FormatHex(*Cell->dataDisp.value.pu16);
	}
	return Str.Str();
}

const char* spt::HmiGridWndDataMapCellPHex8Disp(SalString& Str, HmiGridWndDataMapCell* Cell)
{
	Str.Clear();
	if (Cell->dataDisp.value.vptr)
	{
		Str.FormatHex(*Cell->dataDisp.value.pu8);
	}
	return Str.Str();
}

const char* spt::HmiGridWndDataMapCellPEDUM32Disp(SalString& Str, HmiGridWndDataMapCell* Cell)
{
	Str.Clear();
	if (Cell->dataDisp.value.Enum.des && Cell->dataDisp.value.Enum.value.ptr && (Cell->dataDisp.valueInfo4 > *Cell->dataDisp.value.Enum.value.pu32))
	{
		Str = Cell->dataDisp.value.Enum.des[*Cell->dataDisp.value.Enum.value.pu32].des;
	}
	else
	{
		Str = "Err";
	}
	return Str.Str();
}

const char* spt::HmiGridWndDataMapCellPEDUM16Disp(SalString& Str, HmiGridWndDataMapCell* Cell)
{
	Str.Clear();
	if (Cell->dataDisp.value.Enum.des && Cell->dataDisp.value.Enum.value.ptr && Cell->dataDisp.valueInfo4 <= *Cell->dataDisp.value.Enum.value.pu16)
	{
		Str = Cell->dataDisp.value.Enum.des[*Cell->dataDisp.value.Enum.value.pu16].des;
	}
	else
	{
		Str = "Err";
	}
	return Str.Str();
}

const char* spt::HmiGridWndDataMapCellPEDUM8Disp(SalString& Str, HmiGridWndDataMapCell* Cell)
{
	Str.Clear();
	if (Cell->dataDisp.value.Enum.des && Cell->dataDisp.value.Enum.value.ptr && (Cell->dataDisp.valueInfo4 > *Cell->dataDisp.value.Enum.value.pu8))
	{
		Str = Cell->dataDisp.value.Enum.des[*Cell->dataDisp.value.Enum.value.pu8].des;
	}
	else
	{
		Str = "Err";
	}
	return Str.Str();
}

const char* spt::HmiGridWndDataMapCellStatusFmt1Disp(SalString& Str, HmiGridWndDataMapCell* Cell)
{
	Str.Clear();
	const SalStatus* sta = (SalStatus*)Cell->dataDisp.value.vptr;
	sta->Data().ValueStr(Str, 40);
	return  Str.Str();
}

const char* spt::HmiGridWndDataMapCellStatusTimeDisp(SalString& Str, HmiGridWndDataMapCell* Cell)
{
	Str.Clear();
	SalDateStamp stamp;
	const SalStatus* sta = (SalStatus*)Cell->dataDisp.value.vptr;
	sta->Data().GetStamp(stamp);
	if (Cell->dataDisp.valueInfo1 == 1)
	{
		stamp.ToStrHzFmt1(Str);
	}
	else if (Cell->dataDisp.valueInfo1 == 2)
	{
		stamp.ToStrHzFmt2(Str);
	}
	else if (Cell->dataDisp.valueInfo1 == 3)
	{
		stamp.ToStrHzFmt3(Str);
	}
	return  Str.Str();
}

int32 spt::HmiGridWndDataMapCellEdit(bool8& isDataChange, HmiGridWndDataMapCell* Cell)
{
	isDataChange = 0;
	String100B title;
	Cell->pRow->cell[0].toStr(title, &Cell->pRow->cell[0]);

	if (Cell->dataDisp.valueType == (E_SVT_PTR | E_SVT_I32))
	{
		if (Cell->editMin >= 0)
		{
			int64 data = *Cell->dataDisp.value.pu32;
			ApiHmiUInt32EditDialog dia(title.Str(), (uint32)Cell->editMin, *Cell->dataDisp.value.pu32, Cell->dotLen, (uint32)Cell->editMax);
			if (dia.Show() == 0)
			{
				*Cell->dataDisp.value.pu32 = dia.Value();
				isDataChange = (data != dia.Value());
			}
		}
		else
		{
			int64 data = *Cell->dataDisp.value.pi32;
			ApiHmiInt32EditDialog dia(title.Str(), (int32)Cell->editMin, *Cell->dataDisp.value.pi32, Cell->dotLen, (int32)Cell->editMax);
			if (dia.Show() == 0)
			{
				*Cell->dataDisp.value.pi32 = dia.Value();
				isDataChange = (data != dia.Value());
			}
		}
	}
	else if (Cell->dataDisp.valueType == (E_SVT_PTR | E_SVT_I16))
	{
		if (Cell->editMin >= 0)
		{
			int64 data = *Cell->dataDisp.value.pu16;
			ApiHmiUInt32EditDialog dia(title.Str(), (uint32)Cell->editMin, *Cell->dataDisp.value.pu16, Cell->dotLen, (uint32)Cell->editMax);
			if (dia.Show() == 0)
			{
				*Cell->dataDisp.value.pu16 = dia.Value();
				isDataChange = (data != dia.Value());
			}
		}
		else
		{
			int64 data = *Cell->dataDisp.value.pi16;
			ApiHmiInt32EditDialog dia(title.Str(), (int32)Cell->editMin, *Cell->dataDisp.value.pi16, Cell->dotLen, (int32)Cell->editMax);
			if (dia.Show() == 0)
			{
				*Cell->dataDisp.value.pi16 = dia.Value();
				isDataChange = (data != dia.Value());
			}
		}
	}
	else if (Cell->dataDisp.valueType == (E_SVT_PTR | E_SVT_I8))
	{
		if (Cell->editMin >= 0)
		{
			int64 data = *Cell->dataDisp.value.pu8;
			ApiHmiUInt32EditDialog dia(title.Str(), (uint32)Cell->editMin, *Cell->dataDisp.value.pu8, Cell->dotLen, (uint32)Cell->editMax);
			if (dia.Show() == 0)
			{
				*Cell->dataDisp.value.pu8 = dia.Value();
				isDataChange = (data != dia.Value());
			}
		}
		else
		{
			int64 data = *Cell->dataDisp.value.pi8;
			ApiHmiInt32EditDialog dia(title.Str(), (int32)Cell->editMin, *Cell->dataDisp.value.pi8, Cell->dotLen, (int32)Cell->editMax);
			if (dia.Show() == 0)
			{
				*Cell->dataDisp.value.pi8 = dia.Value();
				isDataChange = (data != dia.Value());
			}
		}
	}
	else if (Cell->dataDisp.valueType == (E_SVT_PTR | E_SVT_U32))
	{
		int64 data = *Cell->dataDisp.value.pu32;
		ApiHmiUInt32EditDialog dia(title.Str(), (uint32)Cell->editMin, *Cell->dataDisp.value.pu32, Cell->dotLen, (uint32)Cell->editMax);
		if (dia.Show() == 0)
		{
			*Cell->dataDisp.value.pu32 = dia.Value();
			isDataChange = (data != dia.Value());
		}
	}
	else if (Cell->dataDisp.valueType == (E_SVT_PTR | E_SVT_U16))
	{
		int64 data = *Cell->dataDisp.value.pu16;
		ApiHmiUInt32EditDialog dia(title.Str(), (uint32)Cell->editMin, *Cell->dataDisp.value.pu16, Cell->dotLen, (uint32)Cell->editMax);
		if (dia.Show() == 0)
		{
			*Cell->dataDisp.value.pu16 = dia.Value();
			isDataChange = (data != dia.Value());
		}
	}
	else if (Cell->dataDisp.valueType == (E_SVT_PTR | E_SVT_U8))
	{
		int64 data = *Cell->dataDisp.value.pu8;
		ApiHmiUInt32EditDialog dia(title.Str(), (uint32)Cell->editMin, *Cell->dataDisp.value.pu8, Cell->dotLen, (uint32)Cell->editMax);
		if (dia.Show() == 0)
		{
			*Cell->dataDisp.value.pu8 = dia.Value();
			isDataChange = (data != dia.Value());
		}
	}
	else if ((Cell->dataDisp.valueType == (E_SVT_PTR | E_SVT_HEX32))
		)
	{
		int64 data = *Cell->dataDisp.value.pu32;
		ApiHmiHex32EditDialog dia(title.Str(), (uint32)Cell->editMin, *Cell->dataDisp.value.pu32, (uint32)Cell->editMax);
		if (dia.Show() == 0)
		{
			*Cell->dataDisp.value.pu32 = dia.Value();
			isDataChange = (data != dia.Value());
		}
	}
	else if ((Cell->dataDisp.valueType == (E_SVT_PTR | E_SVT_HEX16))
		)
	{
		int64 data = *Cell->dataDisp.value.pu16;
		ApiHmiHex32EditDialog dia(title.Str(), (uint32)Cell->editMin, *Cell->dataDisp.value.pu16, (uint32)Cell->editMax);
		if (dia.Show() == 0)
		{
			*Cell->dataDisp.value.pu16 = dia.Value();
			isDataChange = (data != dia.Value());
		}
	}
	else if ((Cell->dataDisp.valueType == (E_SVT_PTR | E_SVT_HEX8))
		)
	{
		int64 data = *Cell->dataDisp.value.pu8;
		ApiHmiHex32EditDialog dia(title.Str(), (uint32)Cell->editMin, *Cell->dataDisp.value.pu8, (uint32)Cell->editMax);
		if (dia.Show() == 0)
		{
			*Cell->dataDisp.value.pu8 = dia.Value();
			isDataChange = (data != dia.Value());
		}
	}
	else if ((Cell->dataDisp.valueType == (E_SVT_PTR | E_SVT_BIT32))
		)
	{
		int64 data = *Cell->dataDisp.value.pu32;
		ApiHmiBit32EditDialog dia(title.Str(), (uint32)Cell->editMin, *Cell->dataDisp.value.BitDes.value.pu32, (uint32)Cell->editMax, Cell->dataDisp.value.BitDes.des, (uint8)Cell->dataDisp.valueInfo4);
		if (dia.Show() == 0)
		{
			*Cell->dataDisp.value.pu32 = dia.Value();
			isDataChange = (data != dia.Value());
		}
	}
	else if ((Cell->dataDisp.valueType == (E_SVT_PTR | E_SVT_BIT32))
		)
	{
		int64 data = *Cell->dataDisp.value.BitDes.value.pu32;
		ApiHmiBit32EditDialog dia(title.Str(), (uint32)Cell->editMin, *Cell->dataDisp.value.BitDes.value.pu32, (uint32)Cell->editMax, Cell->dataDisp.value.BitDes.des, (uint8)Cell->dataDisp.valueInfo4);
		if (dia.Show() == 0)
		{
			*Cell->dataDisp.value.BitDes.value.pu32 = dia.Value();
			isDataChange = (data != dia.Value());
		}
	}
	else if ((Cell->dataDisp.valueType == (E_SVT_PTR | E_SVT_BIT16))
		)
	{
		int64 data = *Cell->dataDisp.value.BitDes.value.pu16;
		ApiHmiBit32EditDialog dia(title.Str(), (uint32)Cell->editMin, *Cell->dataDisp.value.BitDes.value.pu16, (uint32)Cell->editMax, Cell->dataDisp.value.BitDes.des, (uint8)Cell->dataDisp.valueInfo4);
		if (dia.Show() == 0)
		{
			*Cell->dataDisp.value.BitDes.value.pu16 = dia.Value();
			isDataChange = (data != dia.Value());
		}
	}
	else if ((Cell->dataDisp.valueType == (E_SVT_PTR | E_SVT_BIT8))
		)
	{
		int64 data = *Cell->dataDisp.value.BitDes.value.pu8;
		ApiHmiBit32EditDialog dia(title.Str(), (uint32)Cell->editMin, *Cell->dataDisp.value.BitDes.value.pu8, (uint32)Cell->editMax, Cell->dataDisp.value.BitDes.des, (uint8)Cell->dataDisp.valueInfo4);
		if (dia.Show() == 0)
		{
			*Cell->dataDisp.value.BitDes.value.pu8 = dia.Value();
			isDataChange = (data != dia.Value());
		}
	}
	else if ((Cell->dataDisp.valueType == (E_SVT_PTR | E_SVT_ENUM8))
		)
	{
		int64 data = *Cell->dataDisp.value.Enum.value.pu8;
		ApiHmiEnum32EditDialog dia(title.Str(), (uint32)Cell->editMin, *Cell->dataDisp.value.Enum.value.pu8, (uint32)Cell->editMax, Cell->dataDisp.value.Enum.des);
		if (dia.Show() == 0)
		{
			*Cell->dataDisp.value.Enum.value.pu8 = dia.Value();
			isDataChange = (data != dia.Value());
		}
	}
	else if ((Cell->dataDisp.valueType == (E_SVT_PTR | E_SVT_ENUM16))
		)
	{
		int64 data = *Cell->dataDisp.value.Enum.value.pu16;
		ApiHmiEnum32EditDialog dia(title.Str(), (uint32)Cell->editMin, *Cell->dataDisp.value.Enum.value.pu16, (uint32)Cell->editMax, Cell->dataDisp.value.Enum.des);
		if (dia.Show() == 0)
		{
			*Cell->dataDisp.value.Enum.value.pu16 = dia.Value();
			isDataChange = (data != dia.Value());
		}
	}
	else if ((Cell->dataDisp.valueType == (E_SVT_PTR | E_SVT_ENUM32))
		)
	{
		int64 data = *Cell->dataDisp.value.Enum.value.pu32;
		ApiHmiEnum32EditDialog dia(title.Str(), (uint32)Cell->editMin, *Cell->dataDisp.value.Enum.value.pu32, (uint32)Cell->editMax, Cell->dataDisp.value.Enum.des);
		if (dia.Show() == 0)
		{
			*Cell->dataDisp.value.Enum.value.pu32 = dia.Value();
			isDataChange = (data != dia.Value());
		}
	}
	else
	{
		return -1;
	}
	return 0;
}
