#include "SptProject.h"
#include "HmiWidgets.h"
using namespace spt;

GraphicDevice* HmiWidObject::gd = 0;
HmiKeyService* HmiWidObject::key = 0;

void spt::HmiWidObject::UpdateCheck(ShowType Type)
{
	if (childNum)
	{
		HmiWidObject* now = firstchild;
		while (now)
		{
			if (now->IsEnable())
			{
				now->UpdateCheck(Type);
			}
			now = now->next;
		}
	}
}

void spt::HmiWidObject::Show(ShowType Type)
{
	if (isEnable)
	{
		if (isVisible)
		{
			ShowSelf(Type);
			ShowChild(Type);
		}
	}
}

void spt::HmiWidObject::ShowSelf(ShowType Type)
{

}

void spt::HmiWidObject::ShowChild(ShowType Type)
{
	if (childNum)
	{
		HmiWidObject* now = firstchild;
		while (now)
		{
			if (now->IsEnable())
			{
				now->Show(Type);
			}
			now = now->next;
		}
	}
}

int32 spt::HmiWidObject::Edit()
{
	return 0;
}

int32 spt::HmiWidObject::EditSelf(HmiKeyMsg key)
{
	return 0;
}

int32 spt::HmiWidObject::EditChild(HmiKeyMsg key)
{
	return 0;
}

void spt::HmiWidObject::ResetStatus()
{
	isUpdate = 1;
	isCanBeSelect = 0;
	isSelected = 0;
	isFirst = 0;
	value.valueType = valType = E_SVT_NULL;
	childNum = 0;
	selectedChild = last = next = parent = firstchild = lastchild = 0;
	isEnable = 0;
	isVisible = 0;
	rect.x = rect.y = rect.w = rect.h = 0;
	color = GraphicDevice::E_Black;
	backcolor = GraphicDevice::E_White;
}

bool8 spt::HmiWidObject::IsClass(const void* Addr)
{
	return 0;
}

HmiRect& spt::HmiWidObject::Rect()
{
	return rect;
}

void spt::HmiWidObject::SetRect(int16 x, int16 y, int16 w, int16 h)
{
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

void spt::HmiWidObject::SetUpdate()
{
	isUpdate = 1;
	if (parent)
	{
		parent->SetUpdate();
	}
}

GraphicDevice::Color& spt::HmiWidObject::Color()
{
	return color;
}

GraphicDevice::Color& spt::HmiWidObject::BackColor()
{
	return backcolor;
}

void spt::HmiWidObject::SetVisible(bool8 En)
{
	if (En)
	{
		SetUpdate();
		isEnable = isVisible = 1;
	}
	else
	{
		isVisible = 0;
	}
}

void spt::HmiWidObject::AddChild(HmiWidObject* Child)
{
	if (childNum && lastchild && Child)
	{
		childNum++;
		Child->last = lastchild;
		Child->next = 0;
		lastchild->next = Child;
		lastchild = Child;
		Child->parent = this;
	}
	else if (Child)
	{
		childNum = 1;
		firstchild = lastchild = Child;
		Child->last = 0;
		Child->next = 0;
		Child->parent = this;
	}
}

void spt::HmiWidObject::DeleteAllChild()
{
	childNum = 0;
	firstchild = lastchild = 0;
}

HmiWidObject* spt::HmiWidObject::SetSelectedChildAt(int32 Index)
{
	int32 Cnt = 0;
	if (selectedChild)
	{
		selectedChild->IsSelected() = 0;
		selectedChild->IsUpdate() = 1;
	}
	if (Index >= 0)
	{
		HmiWidObject* now = firstchild;
		while (now)
		{
			if (now->isEnable && now->isCanBeSelect)
			{
				if (Cnt == Index)
				{
					selectedChild = now;
					break;
				}
				Cnt++;
			}
			now = now->next;
		}
	}
	else
	{
		Index = -Index;
		HmiWidObject* now = lastchild;
		while (now)
		{
			if (now->isEnable && now->isCanBeSelect)
			{
				if (Cnt == Index)
				{
					selectedChild = now;
					break;
				}
				Cnt++;
			}
			now = now->last;
		}
	}
	if (selectedChild)
	{
		selectedChild->IsSelected() = 1;
		selectedChild->IsUpdate() = 1;
	}
	return selectedChild;
}

HmiWidObject* spt::HmiWidObject::GoToNextCanBeSelected()
{
	HmiWidObject* s = this;
	HmiWidObject* now = next;
	IsUpdate() = 1;
	while (now)
	{
		if (now->isEnable && now->isCanBeSelect)
		{
			s = now;
			break;
		}
		now = now->next;
	}
	if (s)
	{
		IsSelected() = 0;
		s->IsSelected() = 1;
		parent->selectedChild = s;
		s->IsUpdate() = 1;
		return s;
	}
	return 0;
}

HmiWidObject* spt::HmiWidObject::GoToLastCanBeSelected()
{
	HmiWidObject* s = 0;
	HmiWidObject* now = last;
	IsUpdate() = 1;
	while (now)
	{
		if (now->isEnable && now->isCanBeSelect)
		{
			s = now;
			break;
		}
		now = now->last;
	}
	if (s)
	{
		IsSelected() = 0;
		s->IsSelected() = 1;
		parent->selectedChild = s;
		s->IsUpdate() = 1;
	}
	return s;
}

spt::HmiWidObject::HmiWidObject()
{
	ResetStatus();
}

spt::HmiWidLine::HmiWidLine()
{

}

void spt::HmiWidLine::ShowSelf(ShowType Type)
{
	if (isUpdate || Type == E_AllFrame)
	{
		isUpdate = 0;
	}
	else
	{
		return;
	}
	if (!gd)
	{
		return;
	}
	gd->DrawLine(rect.x, rect.y, color, rect.w, rect.h);
}


spt::HmiWidRect::HmiWidRect()
{

}

void spt::HmiWidRect::ShowSelf(ShowType Type)
{
	if (isUpdate || Type == E_AllFrame)
	{
		isUpdate = 0;
	}
	else
	{
		return;
	}
	if (!gd)
	{
		return;
	}
	gd->ClearRect(rect.x, rect.y, backcolor, rect.w, rect.h);
	gd->DrawRect(rect.x, rect.y, color, rect.w, rect.h);
}

void spt::HmiWidRect::UnShow()
{
	gd->ClearRect(rect.x, rect.y, backcolor, rect.w, rect.h);
}

void spt::HmiWidTextLine::SetText(const char* Text)
{
	text = Text;
	SetUpdate();
}

void spt::HmiWidTextLine::SetRect(int16 x, int16 y, int16 StrLen, int16 h)
{
	HmiWidObject::SetRect(x, y, StrLen * gd->FontWidth(), h);
}

void spt::HmiWidTextLine::SetPos(int16 x, int16 y, int16 StrLen)
{
	HmiWidObject::SetRect(x, y, StrLen * gd->FontWidth(), rect.h);
}

void spt::HmiWidTextLine::ResetStatus()
{
	isFromRight = 0;
	text.Clear();
	HmiWidObject::ResetStatus();
}

spt::HmiWidTextLine::HmiWidTextLine()
{
	HmiWidTextLine::ResetStatus();
	rect.h = gd->FontHeight();
}

SalString& spt::HmiWidTextLine::Text()
{
	return text;
}

bool8& spt::HmiWidTextLine::IsFromRight()
{
	return isFromRight;
}

void spt::HmiWidTextLine::ShowSelf(ShowType Type)
{
	if (isVisible && isEnable)
	{

	}
	else
	{
		return;
	}
	if (isUpdate || Type == E_AllFrame)
	{
		isUpdate = 0;
	}
	else
	{
		return;
	}
	if (!gd)
	{
		return;
	}
	GraphicDevice::Color c = color;
	GraphicDevice::Color b = backcolor;
	if (isSelected)
	{
		c = backcolor;
		b = color;
	}
	gd->ClearRect(rect.x, rect.y, b, rect.w, rect.h);
	if (isFromRight)
	{
		int32 l = text.StrLen();
		if (l < 100)
		{
			gd->DrawStr(rect.x + rect.w - l * gd->FontWidth(), rect.y + 1, c, text.Str());
		}
	}
	else
	{
		gd->DrawStr(rect.x, rect.y + 1, c, text.Str());
	}
}

void spt::HmiWidTextMultiLine::SetText(const char* Text)
{
	text = Text;
	SetUpdate();
}

SalString& spt::HmiWidTextMultiLine::Text()
{
	return text;
}

void spt::HmiWidTextMultiLine::ShowSelf(ShowType Type)
{
	if (isVisible && isEnable)
	{

	}
	else
	{
		return;
	}
	if (isUpdate || Type == E_AllFrame)
	{
		isUpdate = 0;
	}
	else
	{
		return;
	}
	if (!gd)
	{
		return;
	}
	gd->ClearRect(rect.x, rect.y, backcolor, rect.w, rect.h);
	TransString ts;
	ts.SetBuf(text.Str());
	String100B str;
	uint16 y = rect.y + gd->SpaceOfFont();
	uint16 ey = y + rect.h;
	uint16 ye = y + rect.h;
	while (!ts.IsEnd())
	{
		if (ts.GetLine(str))
		{
			gd->DrawStr(rect.x, y, color, str.Str());
			y += gd->SpaceOfFont() + gd->FontHeight();
			ye = y + gd->SpaceOfFont() + gd->FontHeight();
			if (ey <= ye)
			{
				break;
			}
			str.Clear();
		}
	}
}

spt::HmiWidCurseText::HmiWidCurseText()
{
	isSelected = 1;
	isCanBeSelect = 1;
	SetVisible(1);
}

void spt::HmiWidTextRect::SetText(const char* Text)
{
	text.SetText(Text);
	text.IsUpdate() = 1;
}

SalString& spt::HmiWidTextRect::Text()
{
	return text.Text();
}

void spt::HmiWidTextRect::AppendText(const char* Text)
{
	text.Text() << Text;
	text.IsUpdate() = 1;
}

void spt::HmiWidTextRect::ShowSelf(ShowType Type)
{
	if (isVisible && isEnable)
	{

	}
	else
	{
		return;
	}
	HmiWidRect::ShowSelf(Type);
	if (isFirst == 0)
	{
		text.Rect().x = rect.x + gd->FontWidth() / 2;
		text.Rect().y = rect.y + gd->SpaceOfFont();
		text.Rect().w = rect.w - gd->FontWidth();
		text.Rect().h = rect.h - gd->SpaceOfFont() * 2;
		isFirst = 1;
		text.SetVisible(1);
		text.IsUpdate() = 1;
	}
	text.Show(Type);
}

bool8 spt::HmiWidContextArea::IsClass(const void* Addr)
{
	return Addr == ClassAddr();
}

void spt::HmiWidContextArea::Show(ShowType Type)
{
	AutoLayerOut();
	UpdateCheck(Type);
	if (isUpdate || Type == E_AllFrame)
	{

	}
	else
	{
		return;
	}
	for (uint32 i = 0; i < maxRowNum; i++)
	{
		for (uint32 j = 0; j < maxColNum; j++)
		{
			dispBuf[i][j] = ' ';
		}
		if (maxColNum)
		{
			dispBuf[i][maxColNum] = 0;
		}
		else
		{
			dispBuf[i][0] = 0;
		}
	}
	ShowChild(Type);
	ShowSelf(Type);
}

void spt::HmiWidContextArea::ShowSelf(ShowType Type)
{
	if (isUpdate || Type == E_AllFrame)
	{

	}
	else
	{
		return;
	}
	//GraphicDevice::Color c = color;
	GraphicDevice::Color b = backcolor;
	gd->ClearRect(rect.x, rect.y, b, rect.w, rect.h);
	HmiWidRect::ShowSelf(Type);
	uint16 y = rect.y + gd->SpaceOfFont();
	uint16 x = rect.x + +gd->FontWidth() / 2;
	uint16 ey = y + rect.h;
	uint16 ye = y + rect.h;
	for (uint32 i = 0; i < maxRowNum; i++)
	{
		if (!rowUpdate[i])
		{
			continue;
		}
		rowUpdate[i] = 0;
		gd->DrawStr(x, y, color, dispBuf[i]);
		y += gd->SpaceOfFont() + gd->FontHeight();
		ye = y + gd->SpaceOfFont() + gd->FontHeight();
		if (ey <= ye)
		{
			break;
		}
	}
	isUpdate = 0;
}

uint32 spt::HmiWidContextArea::MaxDispColNum()
{
	AutoLayerOut();
	return maxColNum;
}

uint32 spt::HmiWidContextArea::MaxDispRowNum()
{
	AutoLayerOut();
	return maxRowNum;
}

HmiRect spt::HmiWidContextArea::GetTextRect(uint32 Row, uint32 Col, uint32 Len)
{
	HmiRect r;
	r.x = rect.x + gd->FontWidth() / 2 + gd->FontWidth() * Col;
	r.y = rect.y + gd->SpaceOfFont() + Row * (gd->SpaceOfFont() + gd->FontHeight());
	r.w = Len * gd->FontWidth();
	r.h = gd->FontHeight();
	return r;
}

void spt::HmiWidContextArea::SetText(uint32 Row, uint32 Col, const char* Text)
{
	if (Row >= M_ArrLen(dispBuf))
	{
		return;
	}
	if (Row >= maxColNum)
	{
		return;
	}
	rowUpdate[Row] = 1;
	uint32 endL = Min(maxColNum, M_ArrLen(dispBuf[0]) - 1);
	for (uint32 j = Col; (j < endL) && (*Text); j++)
	{
		dispBuf[Row][j] = *Text++;
	}
}

spt::HmiWidContextArea::HmiWidContextArea()
{
}

const void* spt::HmiWidContextArea::ClassAddr()
{
	static const uint32 flag = 0; return &flag;
}

void spt::HmiWidContextArea::AutoLayerOut()
{
	if (isFirst == 0)
	{
		maxRowNum = rect.h / (gd->FontHeight() + gd->SpaceOfFont());
		maxColNum = rect.w / gd->FontWidth();
		maxRowNum = Min(maxRowNum, M_ArrLen(dispBuf));
		maxColNum = Min(maxColNum, M_ArrLen(dispBuf[0]) - 1);
		isFirst = 1;
	}
}

bool8 spt::HmiWidContextAreaCell::IsClass(const void* Addr)
{
	return ClassAddr() == Addr;
}

const void* spt::HmiWidContextAreaCell::ClassAddr()
{
	static const uint32 flag = 0; return &flag;
}

void spt::HmiWidContextAreaCell::ShowSelf(ShowType Type)
{
	if (IsHmiWidContextParent())
	{

	}
}

bool8 spt::HmiWidContextAreaCell::IsHmiWidContextParent()
{
	return parent->IsClass(HmiWidContextArea::ClassAddr());
}

spt::HmiWidContextAreaCell::HmiWidContextAreaCell()
{
	Col = Row = 0;
}

void spt::HmiWidContextAreaCell::ResetStatus()
{
	Col = Row = 0;
	HmiWidObject::ResetStatus();
}

void spt::HmiWidContextAreaTextLine::SetText(const char* Str)
{
	text = Str;
	SetUpdate();
}

SalString& spt::HmiWidContextAreaTextLine::Text()
{
	return text;
}

void spt::HmiWidContextAreaTextLine::ShowSelf(ShowType Type)
{
	if (IsHmiWidContextParent())
	{
		HmiWidContextArea* p = (HmiWidContextArea*)parent;
		if (isFromRight && Len)
		{
			p->SetText(Row, Len + Col - text.StrLen(), text.Str());
		}
		else
		{
			p->SetText(Row, Col, text.Str());
		}
	}
}

void spt::HmiWidContextAreaTextLine::ResetStatus()
{
	Len = 0;
	isFromRight = 0;
	HmiWidContextAreaCell::ResetStatus();
}

void spt::HmiWidContextAreaMultiTextLine::SetText(const char* Str)
{
	SetUpdate();
	text = Str;
}

SalString& spt::HmiWidContextAreaMultiTextLine::Text()
{
	return text;
}

void spt::HmiWidContextAreaMultiTextLine::ShowSelf(ShowType Type)
{
	if (isVisible && isEnable)
	{

	}
	else
	{
		return;
	}
	if (IsHmiWidContextParent())
	{
		HmiWidContextArea* p = (HmiWidContextArea*)parent;
		TransString ts;
		ts.SetBuf(text.Str());
		String100B str;
		uint16 y = Row;
		while (!ts.IsEnd())
		{
			if (ts.GetLine(str))
			{
				p->SetText(y, Col, str.Str());
				y++;
				if (y >= p->MaxDispRowNum())
				{
					break;
				}
				str.Clear();
			}
		}
	}
}

uint32 spt::HmiWidContextAreaMultiTextLine::LineNum()
{
	return text.CharNum('\n');
}

void spt::HmiWidTitleLine::SetInfo(const char* Title, uint32 Crc, uint32 CrcLen, uint32 Page, uint32 TotalPage)
{
	SetLine(0, 0);
	SetTitle(Title);
	title = Title;
	SetCrc(Crc, CrcLen);
	page = 0;
	totalLine = line = lastLine = 0;
	SetPage(Page, TotalPage);
	SetUpdate();
}

void spt::HmiWidTitleLine::SetCrc(uint32 Crc, uint32 CrcLen)
{
	crc = Crc;
	crcLen = CrcLen;
}

void spt::HmiWidTitleLine::SetTitle(const char* Title)
{
	title = Title;
	totalLine = line = lastLine = 0;
}

void spt::HmiWidTitleLine::SetPage(uint32 Page, uint32 TotalPage)
{
	lastPage = page;
	page = Page;
	totalPage = TotalPage;
	SetUpdate();
}

void spt::HmiWidTitleLine::SetLine(uint32 Line, uint32 TotalLine)
{
	lastLine = line;
	line = Line;
	totalLine = TotalLine;
}

uint32 spt::HmiWidTitleLine::Page()
{
	return page;
}

uint32 spt::HmiWidTitleLine::LastPage()
{
	return lastPage;
}

uint32 spt::HmiWidTitleLine::TotalPage()
{
	return totalPage;
}

uint32 spt::HmiWidTitleLine::Crc()
{
	return crc;
}

void spt::HmiWidTitleLine::ShowSelf(ShowType Type)
{
	if (Type == ShowType::E_AllFrame)
	{
		isUpdate = 1;
	}
	if (!isUpdate)
	{
		return;
	}
	String100B str;
	str = title.Str();
	if (crcLen)
	{
		str << "CRC(";
		if (crcLen == 2)
		{
			str.FormatHex((uint16)crc);
		}
		else if (crcLen == 4)
		{
			str.FormatHex(crc);
		}
		str << ")";
	}
	int32 l = rect.w / gd->FontWidth() - 1;
	int32 ll = str.StrLen();
	if (l > ll)
	{
		String100B p;
		p << (page + 1) << "/" << totalPage;
		if (totalLine)
		{
			p << "Ò³" << (line + 1) << "/" << totalLine << "ÐÐ";
		}
		str.Format(p.Str(), l - ll, 0, ' ');
	}
	SetText(str.Str());
	HmiWidTextRect::ShowSelf(Type);
	isUpdate = 0;
}

spt::HmiWidSinglePage::HmiWidSinglePage()
{
	AddChild(&title);
	AddChild(&context);
}

void spt::HmiWidSinglePage::Show(ShowType Type)
{
	AutoLayerOut();
	if (Type == ShowType::E_AllFrame)
	{
		isUpdate = 1;
		ShowSelf(Type);
	}
	ShowChild(Type);
}

void spt::HmiWidSinglePage::AutoLayerOut()
{
	if (!isFirst)
	{
		title.Rect().x = rect.x + gd->SpaceOfFont();
		title.Rect().y = rect.y + gd->SpaceOfFont();
		title.Rect().w = rect.w - 2 * gd->SpaceOfFont();
		title.Rect().h = gd->FontHeight() + 3 * gd->SpaceOfFont();

		context.Rect().x = title.Rect().x;
		context.Rect().y = title.Rect().y + title.Rect().h + gd->SpaceOfFont();
		context.Rect().w = title.Rect().w;
		context.Rect().h = rect.h - title.Rect().h - 3 * gd->SpaceOfFont();
		context.AutoLayerOut();
		isFirst = 1;
	}
}

void spt::HmiWidDataLine::SetData(uint8 Type, u64value Value, bool8 IsFromRight, uint8 Len, uint8 DotLen, bool8 IsAddZero)
{
	data.valueType = Type;
	data.value = Value;
	data.valueInfo1 = Len;
	data.valueInfo2 = DotLen;
	isFromRight = IsFromRight;
	isAddZero = IsAddZero;
}

void spt::HmiWidDataLine::ResetStatus()
{
	isFromRight = 0;
	data.valueType = E_SVT_NULL;
	data.value.i64 = 0;
	HmiWidObject::ResetStatus();
}

spt::HmiWidDataLine::HmiWidDataLine()
{
	HmiWidDataLine::ResetStatus();
}

bool spt::HmiWidDataLine::toStr(SalString& Str)
{
	if (isAddZero)
	{
		return data.toStr(Str, isFromRight, data.valueInfo1, data.valueInfo2, '0');
	}
	return data.toStr(Str, isFromRight, data.valueInfo1, data.valueInfo2, ' ');
}

bool8& spt::HmiWidDataLine::IsFromRight()
{
	return isFromRight;
}

void spt::HmiWidDataLine::ShowSelf(ShowType Type)
{
	if (isVisible && isEnable)
	{

	}
	else
	{
		return;
	}
	if (isUpdate || Type == E_AllFrame)
	{
		isUpdate = 0;
	}
	else
	{
		return;
	}
	if (!gd)
	{
		return;
	}
	GraphicDevice::Color c = color;
	GraphicDevice::Color b = backcolor;
	if (isSelected)
	{
		c = backcolor;
		b = color;
	}
	gd->ClearRect(rect.x, rect.y, b, rect.w, rect.h);
	String100B text;
	toStr(text);
	if (isFromRight)
	{
		int32 l = text.StrLen();
		if (l < 100)
		{
			gd->DrawStr(rect.x + rect.w - l * gd->FontWidth(), rect.y + 1, c, text.Str());
		}
	}
	else
	{
		gd->DrawStr(rect.x, rect.y + 1, c, text.Str());
	}
}

void spt::HmiWidContextAreaDataLine::SetData(uint8 Type, u64value Value, bool8 IsFromRight, uint8 Len, uint8 DotLen, bool8 IsAddZero)
{
	data.valueType = Type;
	data.value = Value;
	data.valueInfo1 = Len;
	data.valueInfo2 = DotLen;
	isFromRight = IsFromRight;
	isAddZero = IsAddZero;
}

void spt::HmiWidContextAreaDataLine::ResetStatus()
{
	isFromRight = 0;
	data.valueType = E_SVT_NULL;
	data.value.i64 = 0;
	HmiWidContextAreaCell::ResetStatus();
}

spt::HmiWidContextAreaDataLine::HmiWidContextAreaDataLine()
{
	ResetStatus();
}

bool spt::HmiWidContextAreaDataLine::toStr(SalString& Str)
{
	if (isAddZero)
	{
		return data.toStr(Str, isFromRight, data.valueInfo1, data.valueInfo2, '0');
	}
	return data.toStr(Str, isFromRight, data.valueInfo1, data.valueInfo2, ' ');
}

bool8& spt::HmiWidContextAreaDataLine::IsFromRight()
{
	return isFromRight;
}

void spt::HmiWidContextAreaDataLine::ShowSelf(ShowType Type)
{
	if (IsHmiWidContextParent())
	{
		String100B text;
		toStr(text);
		HmiWidContextArea* p = (HmiWidContextArea*)parent;
		if (isFromRight && Len)
		{
			p->SetText(Row, Len + Col - text.StrLen(), text.Str());
		}
		else
		{
			p->SetText(Row, Col, text.Str());
		}
	}
}
GraphicDevice* WidObject::gd = 0;
HmiKeyService* WidObject::key = 0;
spt::WidObject::WidObject()
{
	childList = 0;
	lastObject = 0;
	nextObject = 0;
	parent = 0;
	clientData = 0;
	cursepos = 0;
	isInied = 0;
	isUpdate = 0;
	isUpdateSelf = 0;
	isUpdateChild = 0;
	isCanBeSelect = 0;
	isSelected = 0;
	isEnable = 1;
	periodUpdateTimer.Enable(0);
	color = gd->E_Black;
	backcolor = gd->E_White;
}
int32 spt::WidObject::Show()
{
	if (!isEnable)
	{
		return 0;
	}
	if (isInied)
	{
		if (isUpdate)
		{
			if (isUpdateSelf)
			{
				ShowSelf();
			}
			if (isUpdateChild)
			{
				ShowChild();
			}
			isUpdate = 0;
		}
		else if (periodUpdateTimer.Status())
		{
			ShowPeriod();
		}
	}
	else
	{
		ShowSelf();
		ShowChild();
		isInied = 1;
	}
	return 0;
}

bool8 spt::WidObject::SetRect(const HmiRect& Rect)
{
	rect = Rect;
	SetUpdate(1);
	return 1;
}

bool8 spt::WidObject::SetRect(int16 x, int16 y, int16 w, int16 h)
{
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SetUpdate(1);
	return 1;
}

bool8 spt::WidObject::SetPos(int16 x, int16 y)
{
	rect.x = x;
	rect.y = y;
	SetUpdate(1);
	return 1;
}

bool8 spt::WidObject::SetPosX(int16 x)
{
	rect.x = x;
	SetUpdate(1);
	return 1;
}

bool8 spt::WidObject::SetPosY(int16 y)
{
	rect.y = y;
	SetUpdate(1);
	return 1;
}

bool8 spt::WidObject::SetInied(bool8 is)
{
	if (is == 0)
	{
		SetUpdate(1);
		if (childList)
		{
			WidObject* now = childList;
			while (now)
			{
				now->SetInied(0);
				now = now->nextObject;
			}
		}
	}
	return isInied = is;
}

bool8 spt::WidObject::SetUpdate(bool8 is)
{
	if (is)
	{
		isUpdateSelf = 1;
		if (childList)
		{
			isUpdateChild = 1;
		}
		if (parent)
		{
			parent->SetUpdateChild(is);
		}
	}
	return isUpdate = is;
}

bool8 spt::WidObject::SetUpdateSelf(bool8 is)
{
	if (is)
	{
		if (parent)
		{
			parent->SetUpdateChild(is);
		}
		isUpdate = 1;
	}
	return isUpdateSelf = is;
}

bool8 spt::WidObject::SetUpdateChild(bool8 is)
{
	if (is)
	{
		if (parent)
		{
			parent->SetUpdateChild(is);
		}
		if (childList)
		{
			isUpdateChild = 1;
		}
		isUpdate = 1;
	}
	return 1;
}

bool8 spt::WidObject::SetPeriodUpdate(bool8 isEnable, uint32 Period)
{
	periodUpdateTimer.UpCnt(Period);
	periodUpdateTimer.Enable(isEnable);
	return 1;
}

bool8 spt::WidObject::SetCanBeSelect(bool8 is)
{
	return isCanBeSelect = is;
}

bool8 spt::WidObject::SetSelected(bool8 is)
{
	return isSelected = is;
}

bool8 spt::WidObject::AddChild(WidObject* Object)
{
	if (Object)
	{
		Object->parent = this;
		if (childList && childListEnd)
		{
			childListEnd->nextObject = Object;
			Object->lastObject = childListEnd;
			Object->nextObject = 0;
			childListEnd = Object;
		}
		else
		{
			childListEnd = childList = Object;
			Object->nextObject = 0;
			Object->lastObject = 0;
		}
	}
	SetUpdateChild(1);
	return 1;
}

void spt::WidObject::ClearRect()
{
	gd->ClearRect(rect.x, rect.y, backcolor, rect.w, rect.h);
	SetUpdate(1);
}

bool8 spt::WidObject::Update()
{
	gd->Update(rect.x, rect.y, rect.w, rect.h);
	return 0;
}

int32 spt::WidObject::ShowSelf()
{
	if (!isEnable)
	{
		return 0;
	}
	if (!isUpdateSelf)
	{
		return 0;
	}
	isUpdateSelf = 0;
	return 0;
}

int32 spt::WidObject::ShowChild()
{
	if (!isEnable)
	{
		return 0;
	}
	if (!isUpdateChild)
	{
		return 0;
	}
	if (childList)
	{
		WidObject* now = childList;
		while (now)
		{
			now->Show();
			now = now->nextObject;
		}
	}
	isUpdateChild = 0;
	return 0;
}

int32 spt::WidObject::ShowPeriod()
{
	return 0;
}

WidObject* spt::WidObject::FindFirstSelChild()
{
	if (cursepos)
	{
		cursepos->SetSelected(0);
	}
	cursepos = 0;
	if (childList)
	{
		WidObject* now = childList;
		while (now)
		{
			if (now->isCanBeSelect)
			{
				if (cursepos)
				{
					cursepos->SetSelected(0);
				}
				cursepos = now;
				cursepos->SetSelected(1);
				break;
			}
			now = now->nextObject;
		}
	}
	return cursepos;
}

WidObject* spt::WidObject::FindLastSelChild()
{
	if (cursepos)
	{
		cursepos->SetSelected(0);
	}
	cursepos = 0;
	if (childList)
	{
		WidObject* now = childListEnd;
		while (now)
		{
			if (now->isCanBeSelect)
			{
				if (cursepos)
				{
					cursepos->SetSelected(0);
				}
				cursepos = now;
				cursepos->SetSelected(1);
				break;
			}
			now = now->lastObject;
		}
	}
	return cursepos;
}

WidObject* spt::WidObject::Go2LastSelChild()
{
	if (cursepos)
	{
		WidObject* now = cursepos;
		now = now->lastObject;
		while (now)
		{
			if (now->isCanBeSelect)
			{
				if (cursepos)
				{
					cursepos->SetSelected(0);
				}
				cursepos = now;
				cursepos->SetSelected(1);
				break;
			}
			now = now->lastObject;
		}
		if (!now)
		{
			FindLastSelChild();
		}
	}
	return cursepos;
}

WidObject* spt::WidObject::Go2NextSelChild()
{
	if (cursepos)
	{
		WidObject* now = cursepos;
		now = now->nextObject;
		while (now)
		{
			if (now->isCanBeSelect)
			{
				if (cursepos)
				{
					cursepos->SetSelected(0);
				}
				cursepos = now;
				cursepos->SetSelected(1);
				break;
			}
			now = now->nextObject;
		}
		if (!now)
		{
			FindFirstSelChild();
		}
	}
	return cursepos;
}

void spt::WidLine::SetStartPos(int16 x, int16 y)
{
	startPos.x = x;
	startPos.y = y;
	SetUpdate(1);
}

void spt::WidLine::SetEndPos(int16 x, int16 y)
{
	endPos.x = x;
	endPos.y = y;
	SetUpdate(1);
}

void spt::WidLine::SetWidth(int16 Width)
{
	w = Width;
}

int32 spt::WidLine::ShowSelf()
{
	if (!isUpdateSelf)
	{
		return 0;
	}
	isUpdateSelf = 0;
	gd->DrawLine(startPos.x, startPos.y, endPos.x, endPos.y, color, w);
	return 0;
}

int32 spt::WidRect::ShowSelf()
{
	if (!isUpdateSelf)
	{
		return 0;
	}
	isUpdateSelf = 0;
	gd->DrawRect(rect.x, rect.y, color, rect.w, rect.h);
	return 0;
}

spt::WidTextLine::WidTextLine()
{

}

bool8 spt::WidTextLine::SetText(const char* Text)
{
	if (text != Text)
	{
		SetUpdateSelf(1);
		text = Text;
	}
	return 1;
}

bool8 spt::WidTextLine::SetText(uint16 Index, char Data)
{
	if (Index < text.StrBufLen())
	{
		text.Str()[Index] = Data;
	}
	SetUpdateSelf(1);
	return 0;
}

int32 spt::WidTextLine::ShowSelf()
{
	if (!isUpdateSelf)
	{
		return 0;
	}
	isUpdateSelf = 0;
	gd->DrawStr(rect.x, rect.y, color, text.Str());
	return 0;
}

int32 spt::WidTextLineRect::ShowSelf()
{
	if (!isUpdateSelf)
	{
		return 0;
	}
	isUpdateSelf = 0;
	gd->ClearRect(rect.x, rect.y, backcolor, rect.w, rect.h);
	gd->DrawStr(rect.x + gd->SpaceOfFont(), rect.y + gd->SpaceOfFont(), color, text.Str());
	return 0;
}

bool8 spt::WidTextLineRect::SetText(const char* Text)
{
	if (text != Text)
	{
		SetUpdateSelf(1);
		text = Text;
	}
	return 1;
}

spt::WidTextWnd::WidTextWnd()
{
	maxCtxLine = 0;
	maxCtxW = 0;
	lastPage = 0xffff;
	lastLine = 0xffff;
	page = 0;
	line = 0;
	totalLine = 0;
	totalPage = 0;
}

void spt::WidTextWnd::SetInfo(const char* Title)
{
	StrNCpy(title, Title, sizeof(title));
	isUpdateTitle = 1;
	SetUpdateSelf(1);
}

void spt::WidTextWnd::SetInfo(const char* Title, uint32 Crc, uint32 CrcLen, uint32 Page, uint32 TotalPage)
{
	StrNCpy(title, Title, sizeof(title));
	crc = Crc;
	crcLen = CrcLen;
	page = Page;
	totalPage = TotalPage;
	isUpdateTitle = 1;
	SetUpdateSelf(1);
}

void spt::WidTextWnd::SetPage(uint16 Page)
{
	if (page != Page)
	{
		isUpdateTitle = 1;
		SetUpdateSelf(1);
	}
	page = Page;
}

void spt::WidTextWnd::SetLine(uint16 Line)
{
	if (line != Line)
	{
		isUpdateTitle = 1;
		SetUpdateSelf(1);
	}
	line = Line;
}

void spt::WidTextWnd::SetCrc(uint32 Crc, uint32 CrcLen)
{
	crc = crc;
	crcLen = CrcLen;
	SetUpdateSelf(1);
}

void spt::WidTextWnd::SetTitle(const char* Title)
{
	StrNCpy(title, Title, sizeof(title));
}

void spt::WidTextWnd::SetTotalPage(uint16 Page)
{
	totalPage = Page;
	isUpdateTitle = 1;
	SetUpdateSelf(1);
}

void spt::WidTextWnd::SetTotalLine(uint16 Line)
{
	totalLine = Line;
	isUpdateTitle = 1;
	SetUpdateSelf(1);
}

uint16 spt::WidTextWnd::DispMaxCtxLine()
{
	if (!isInied)
	{
		titleRect.SetRect(rect.x, rect.y, rect.w, gd->FontHeight() + 2 * gd->SpaceOfFont());
		ctxRect.SetRect(titleRect.x, titleRect.y + titleRect.h, titleRect.w, rect.h - titleRect.h);
		maxCtxLine = ctxRect.h / (gd->FontHeight() + gd->SpaceOfFont());
		maxCtxW = ctxRect.w / (gd->FontWidth()) - 1;
	}
	return maxCtxLine;
}

uint16 spt::WidTextWnd::DispMaxCtxWidth()
{
	if (!isInied)
	{
		titleRect.SetRect(rect.x, rect.y, rect.w, gd->FontHeight() + 2 * gd->SpaceOfFont());
		ctxRect.SetRect(titleRect.x, titleRect.y + titleRect.h, titleRect.w, rect.h - titleRect.h);
		maxCtxLine = ctxRect.h / (gd->FontHeight() + gd->SpaceOfFont());
		maxCtxW = ctxRect.w / (gd->FontWidth()) - 1;
	}
	return maxCtxW;
}

void spt::WidTextWnd::SetText(uint32 Row, uint32 Col, const char* Text)
{
	if (Row >= M_ArrLen(ctx))
	{
		return;
	}
	char* buf = ctx[Row];
	for (uint32 i = Col; i < M_ArrLen(ctx[0]); i++)
	{
		if (*Text)
		{
			if (*Text != buf[i])
			{
				buf[i] = *Text;
				ctxUpdate[Row] = 1;
				isUpdateCtx = 1;
				SetUpdateSelf(1);
			}
			Text++;
		}
		else
		{
			break;
		}
	}
}

void spt::WidTextWnd::ClearCtx()
{
	for (uint32 i = 0; i < M_ArrLen(ctx); i++)
	{
		ClearCtxLine(i);
	}
}

void spt::WidTextWnd::ClearCtxLine(uint32 LineNum)
{
	if (LineNum >= M_ArrLen(ctx))
	{
		return;
	}
	char* buf = ctx[LineNum];
	for (uint32 i = 0; i < M_ArrLen(ctx[0]); i++)
	{
		buf[i] = ' ';
	}
	buf[M_ArrLen(ctx[0]) - 1] = 0;
	ctxUpdate[LineNum] = 1;
	isUpdateCtx = 1;
}

int32 spt::WidTextWnd::ShowSelf()
{
	if (!isUpdateSelf)
	{
		return 0;
	}
	if (isUpdateTitle)
	{
		if (!isInied)
		{
			titleRect.SetRect(rect.x, rect.y, rect.w, gd->FontHeight() + 2 * gd->SpaceOfFont());
			ctxRect.SetRect(titleRect.x, titleRect.y + titleRect.h, titleRect.w, rect.h - titleRect.h);
			maxCtxLine = ctxRect.h / (gd->FontHeight() + gd->SpaceOfFont());
			maxCtxW = ctxRect.w / (gd->FontWidth()) - 1;
			if (maxCtxW >= M_ArrLen(ctx[0]))
			{
				maxCtxW = M_ArrLen(ctx[0]) - 1;
			}
			ClearRect();
			gd->DrawRect(rect.x, rect.y, color, rect.w, rect.h);
			gd->DrawLine(titleRect.x, titleRect.y + titleRect.h, color, titleRect.w, 1);
		}
		String40B pagestr;
		pagestr << (page + 1) << "/" << totalPage;
		if (totalLine)
		{
			pagestr << " Ò³ " << (line + 1) << "/" << totalLine << " ÐÐ";
		}
		uint16 totalLen = rect.w / gd->FontWidth() - 1;
		totalLen -= pagestr.StrLen();
		String100B titlestr;
		titlestr.Format(title, totalLen, 1, ' ');
		titlestr << pagestr;
		gd->ClearRect(titleRect.x + gd->SpaceOfFont(), titleRect.y + gd->SpaceOfFont(), backcolor, titleRect.w - gd->FontWidth(), gd->FontHeight());
		gd->DrawStr(titleRect.x + gd->SpaceOfFont(), titleRect.y + gd->SpaceOfFont(), color, titlestr.Str());
	}
	if (isUpdateCtx)
	{
		uint16 rowh = gd->FontHeight() + gd->SpaceOfFont();
		uint16 rowx = ctxRect.x + gd->SpaceOfFont();
		uint16 rowy = ctxRect.y + gd->SpaceOfFont();
		for (uint32 i = 0; i < maxCtxLine; i++)
		{
			if (ctxUpdate[i])
			{
				ctx[i][maxCtxW] = 0;
				gd->ClearRect(rowx, rowy + i * rowh, backcolor, ctxRect.w - gd->FontWidth(), gd->FontHeight());
				gd->DrawStr(rowx, rowy + i * rowh, color, ctx[i]);
				ctxUpdate[i] = 0;
			}
		}
	}
	gd->Update(rect);
	lastPage = page;
	lastLine = line;
	isUpdateCtx = 0;
	isUpdateTitle = 0;
	isUpdateSelf = 0;
	return 0;
}

spt::WidCurseTextLine::WidCurseTextLine()
{
	backcolor = gd->E_Black;
	color = gd->E_White;
	row = 0;
	col = 0;
}

int32 spt::WidCurseTextLine::ShowSelf()
{
	if (!isUpdateSelf)
	{
		return 0;
	}
	isUpdateSelf = 0;
	gd->ClearRect(rect.x, rect.y, backcolor, rect.w, rect.h);
	gd->DrawStr(rect.x, rect.y, color, text.Str());
	return 0;
}

uint16 spt::WidCurseTextLine::SetRow(uint16 Row)
{
	if (row != Row)
	{
		row = Row;
	}
	return row;
}

uint16 spt::WidCurseTextLine::SetCol(uint16 Col)
{
	if (col != Col)
	{
		col = Col;
	}
	return col;
}

spt::WidDataLine::WidDataLine()
{
}

void spt::WidDataLine::SetData(uint8 Type, u64value Value, bool8 IsFromRight, uint8 Len, uint8 DotLen, bool8 IsAddZero)
{
	data.valueType = Type;

	data.valueInfo1 = Len;
	data.valueInfo2 = DotLen;
	data.valueInfo3 = IsFromRight;
	data.valueInfo4 = IsAddZero;
	text.Clear();
	SetData(Value);
}

void spt::WidDataLine::SetData(u64value Value)
{
	data.value = Value;
	if (data.valueInfo4)
	{
		data.toStr(text, data.valueInfo3, data.valueInfo1, data.valueInfo2, '0');
	}
	else
	{
		data.toStr(text, data.valueInfo3, data.valueInfo1, data.valueInfo2, ' ');
	}
	SetUpdateSelf(1);
}

int32 spt::WidDataLine::ShowSelf()
{
	if (!isUpdateSelf)
	{
		return 0;
	}
	isUpdateSelf = 0;
	gd->DrawStr(rect.x, rect.y, color, text.Str());
	return 0;
}
