#include "SptProject.h"
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
