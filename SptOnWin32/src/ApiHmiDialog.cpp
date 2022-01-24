#include "ApiProject.h"
using namespace spt;


int32 spt::DispProcess(int Step, const char* info)
{
	HmiPos pos = spt::HmiMenuService::Instance().Rect().Pos();
	GraphicDevice& gd = GraphicDevice::Instance();
	pos.y += Step * (gd.FontHeight() + gd.SpaceOfFont()) + gd.SpaceOfFont();
	pos.x += gd.FontWidth() / 2;
	HmiWidTextLine text;
	text.SetPos(pos.x, pos.y, StrLen(info));
	text.SetText(info);
	text.SetVisible(1);
	text.Show(text.E_AllFrame);
	gd.Update(text.Rect());
	return 0;
}

int32 spt::DispPressAnyKey(int32 Ms)
{
	HmiKey key;
	HmiKeyService& ks = HmiKeyService::Instance();
	MsTimer msTimer;
	msTimer.UpCnt((uint32)Ms);
	msTimer.Enable(1);
	while (!msTimer.Status())
	{
		if (ks.Pop(key))
		{
			if (key.Key2)
			{
				return key.Key2;
			}
			break;
		}
		HmiMain::Instance().MsSleep(50);
	}
	return 0;
}

spt::ApiAssicInputDiglog::ApiAssicInputDiglog(const char* Default, E_Mode Mode, uint32 MaxLen)
	:HmiAssicInputDialog(Mode)
{
	SetDefault(Default);
}

int32 spt::ApiAssicInputDiglog::Show()
{
	return Edit();
}

const char* spt::ApiAssicInputDiglog::Str()
{
	return inputStr.Str();
}
spt::ApiWarnDialog::ApiWarnDialog(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5)
{
	SetTitle(Str1, Str2, Str3, Str4, Str5);
	AutoLayout();
}

int32 spt::ApiWarnDialog::Show()
{
	return HmiWarnDialog::Edit();
}

spt::ApiSelectDialog::ApiSelectDialog(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5)
{
	SetTitle(Str1, Str2, Str3, Str4, Str5);
	AutoLayout();
}

int32 spt::ApiSelectDialog::Show()
{
	return HmiSelectDialog::Edit();
}


spt::ApiHmiStrEditDialog::ApiHmiStrEditDialog(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5, uint32 MaxInputLen)
{
	SetTitle(Str1, Str2, Str3, Str4, Str5);
	SetMaxInputLen(MaxInputLen);
}

void spt::ApiHmiStrEditDialog::SetText(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5)
{
	HmiStrEditDialog::SetText(Str1, Str2, Str3, Str4, Str5);
}

void spt::ApiHmiStrEditDialog::SetEditAble(bool8 EditAble1, bool8 EditAble2, bool8 EditAble3, bool8 EditAble4, bool8 EditAble5)
{
	HmiStrEditDialog::SetEditAble(EditAble1, EditAble2, EditAble3, EditAble4, EditAble5);
}

int32 spt::ApiHmiStrEditDialog::Show()
{
	return Edit();
}

const SalString* spt::ApiHmiStrEditDialog::GetText(uint32 Index)
{
	if (Index < M_ArrLen(text))
	{
		return &text[Index].Text();
	}
	return 0;
}

spt::ApiHmiDateEditDialog::ApiHmiDateEditDialog(const char* Title, SalDateStamp& Stamp)
{
	SetTitle(Title);
	SetDefaultDate(Stamp);
}

int32 spt::ApiHmiDateEditDialog::Show()
{
	int32 res = Edit();
	return res;
}

SalDateStamp& spt::ApiHmiDateEditDialog::Stamp()
{
	return date;
}

SalRtc& spt::ApiHmiDateEditDialog::Rtc()
{
	return rtc;
}

spt::ApiHmiUInt32EditDialog::ApiHmiUInt32EditDialog(const char* Title, uint32 Min, uint32 Def, uint32 DotNum, uint32 Max)
{
	Set(Title, Min, Def, DotNum, Max);
}

int32 spt::ApiHmiUInt32EditDialog::Show()
{
	return Edit();
}

uint32 spt::ApiHmiUInt32EditDialog::Value()
{
	return Data();
}

spt::ApiHmiInt32EditDialog::ApiHmiInt32EditDialog(const char* Title, int32 Min, int32 Def, int32 DotNum, int32 Max)
{
	Set(Title, Min, Def, DotNum, Max);
}


int32 spt::ApiHmiInt32EditDialog::Show()
{
	return Edit();
}

int32 spt::ApiHmiInt32EditDialog::Value()
{
	return Data();
}

spt::ApiHmiHex32EditDialog::ApiHmiHex32EditDialog(const char* Title, int32 Min, int32 Def, int32 Max)
{
	Set(Title, Min, Def, Max);
}

int32 spt::ApiHmiHex32EditDialog::Show()
{
	return Edit();
}

uint32 spt::ApiHmiHex32EditDialog::Value()
{
	return Data();
}

spt::ApiHmiBit32EditDialog::ApiHmiBit32EditDialog(const char* Title, int32 Min, int32 Def, int32 Max, SalBitDes* Des, uint8 Len)
{
	Set(Title, Min, Def, Max, Des, Len);
}

int32 spt::ApiHmiBit32EditDialog::Show()
{
	return Edit();
}

uint32 spt::ApiHmiBit32EditDialog::Value()
{
	return Data();
}

spt::ApiHmiEnum32EditDialog::ApiHmiEnum32EditDialog(const char* Title, int32 Min, int32 Def, int32 Max, SalEnumDes* Des)
{
	Set(Title, Min, Def, Max, Des);
}

int32 spt::ApiHmiEnum32EditDialog::Show()
{
	return Edit();
}

uint32 spt::ApiHmiEnum32EditDialog::Value()
{
	return Data();
}

spt::ApiInfoDialog::ApiInfoDialog(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5)
{
	HmiInfoDialog::SetTitle(Str1, Str2, Str3, Str4, Str5);
}

spt::ApiInfoDialog::ApiInfoDialog(const char* Str1, const char* Str2, const char* Str3, const char* Str4, const char* Str5, const char* Warn)
{
	HmiInfoDialog::SetTitle(Str1, Str2, Str3, Str4, Str5, Warn);
}

int32 spt::ApiInfoDialog::Show()
{
	return Edit();
}
