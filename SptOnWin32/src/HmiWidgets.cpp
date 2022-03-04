#include "SptProject.h"
#include "HmiWidgets.h"
using namespace spt;

GraphicDevice* HmiWidObject::gd = 0;
HmiKeyService* HmiWidObject::key = 0;
spt::HmiWidObject::HmiWidObject()
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
	MemSet(&rect, 0, sizeof(rect));
}
int32 spt::HmiWidObject::Show()
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

bool8 spt::HmiWidObject::SetRect(const HmiRect& Rect)
{
	rect = Rect;
	SetUpdate(1);
	return 1;
}

bool8 spt::HmiWidObject::SetRect(int16 x, int16 y, int16 w, int16 h)
{
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SetUpdate(1);
	return 1;
}

bool8 spt::HmiWidObject::SetPos(int16 x, int16 y)
{
	rect.x = x;
	rect.y = y;
	SetUpdate(1);
	return 1;
}

bool8 spt::HmiWidObject::SetPosX(int16 x)
{
	rect.x = x;
	SetUpdate(1);
	return 1;
}

bool8 spt::HmiWidObject::SetPosY(int16 y)
{
	rect.y = y;
	SetUpdate(1);
	return 1;
}

bool8 spt::HmiWidObject::SetInied(bool8 is)
{
	if (is == 0)
	{
		SetUpdate(1);
		if (childList)
		{
			HmiWidObject* now = childList;
			while (now)
			{
				now->SetInied(0);
				now = now->nextObject;
			}
		}
	}
	return isInied = is;
}

bool8 spt::HmiWidObject::SetEnable(bool8 is)
{
	return isEnable = is;
}

bool8 spt::HmiWidObject::SetUpdate(bool8 is)
{
	if (is)
	{
		SetUpdateChild(is);
		isUpdateSelf = 1;
		isUpdate = 1;
		isUpdateChild = 1;
	}
	return isUpdate = is;
}

bool8 spt::HmiWidObject::SetUpdateSelf(bool8 is)
{
	if (is)
	{
		if (parent)
		{
			if (!parent->isUpdate)
			{
				parent->SetUpdateParent(is);
			}
		}
		isUpdate = 1;
	}
	return isUpdateSelf = is;
}

bool8 spt::HmiWidObject::SetUpdateChild(bool8 is)
{
	if (is)
	{
		if (parent)
		{
			if (!parent->isUpdate)
			{
				parent->SetUpdateParent(is);
			}
		}
		if (childList)
		{
			HmiWidObject* now = childList;
			while (now)
			{
				if (!now->isUpdate)
				{
					now->SetUpdateChild(is);
				}
				now = now->nextObject;
			}
		}
		isUpdateSelf = 1;
		isUpdate = 1;
		isUpdateChild = 1;
	}
	return 1;
}

bool8 spt::HmiWidObject::SetUpdateParent(bool8 is)
{
	if (is)
	{
		if (parent)
		{
			if (!parent->isUpdate)
			{
				parent->SetUpdateParent(is);
			}
		}
		isUpdateSelf = 1;
		isUpdate = 1;
		isUpdateChild = 1;
	}
	return 1;
}

bool8 spt::HmiWidObject::SetPeriodUpdate(bool8 isEnable, uint32 Period)
{
	periodUpdateTimer.UpCnt(Period);
	periodUpdateTimer.Enable(isEnable);
	return 1;
}

bool8 spt::HmiWidObject::SetCanBeSelect(bool8 is)
{
	return isCanBeSelect = is;
}

bool8 spt::HmiWidObject::SetSelected(bool8 is)
{
	return isSelected = is;
}

bool8 spt::HmiWidObject::SetReDraw(bool8 is)
{
	if (childList)
	{
		HmiWidObject* now = childList;
		while (now)
		{
			now->SetReDraw(is);
			now = now->nextObject;
		}
	}
	SetUpdateSelf(is);
	SetUpdateChild(is);
	return isReDraw = is;
}

bool8 spt::HmiWidObject::AddChild(HmiWidObject* Object)
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

void spt::HmiWidObject::ClearRect()
{
	gd->ClearRect(rect.x, rect.y, backcolor, rect.w, rect.h);
	SetUpdate(1);
}

bool8 spt::HmiWidObject::Update()
{
	gd->Update(rect.x, rect.y, rect.w, rect.h);
	return 0;
}

int32 spt::HmiWidObject::ShowSelf()
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

int32 spt::HmiWidObject::ShowChild()
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
		HmiWidObject* now = childList;
		while (now)
		{
			now->Show();
			now = now->nextObject;
		}
	}
	isUpdateChild = 0;
	return 0;
}

int32 spt::HmiWidObject::ShowPeriod()
{
	return 0;
}

HmiWidObject* spt::HmiWidObject::FindFirstSelChild()
{
	if (cursepos)
	{
		cursepos->SetSelected(0);
	}
	cursepos = 0;
	if (childList)
	{
		HmiWidObject* now = childList;
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

HmiWidObject* spt::HmiWidObject::FindLastSelChild()
{
	if (cursepos)
	{
		cursepos->SetSelected(0);
	}
	cursepos = 0;
	if (childList)
	{
		HmiWidObject* now = childListEnd;
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

HmiWidObject* spt::HmiWidObject::Go2LastSelChild()
{
	if (cursepos)
	{
		HmiWidObject* now = cursepos;
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

HmiWidObject* spt::HmiWidObject::Go2NextSelChild()
{
	if (cursepos)
	{
		HmiWidObject* now = cursepos;
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

void spt::HmiWidLine::SetStartPos(int16 x, int16 y)
{
	startPos.x = x;
	startPos.y = y;
	SetUpdate(1);
}

void spt::HmiWidLine::SetEndPos(int16 x, int16 y)
{
	endPos.x = x;
	endPos.y = y;
	SetUpdate(1);
}

void spt::HmiWidLine::SetWidth(int16 Width)
{
	w = Width;
}

int32 spt::HmiWidLine::ShowSelf()
{
	if (!isUpdateSelf)
	{
		return 0;
	}
	isUpdateSelf = 0;
	gd->DrawLine(startPos.x, startPos.y, endPos.x, endPos.y, color, w);
	return 0;
}

int32 spt::HmiWidRect::ShowSelf()
{
	if (!isUpdateSelf)
	{
		return 0;
	}
	isUpdateSelf = 0;
	gd->DrawRect(rect.x, rect.y, color, rect.w, rect.h);
	return 0;
}

spt::HmiWidTextLine::HmiWidTextLine()
{

}

bool8 spt::HmiWidTextLine::SetText(const char* Text)
{
	if (text != Text)
	{
		SetUpdateSelf(1);
		text = Text;
	}
	return 1;
}

bool8 spt::HmiWidTextLine::SetText(uint16 Index, char Data)
{
	if (Index < text.StrBufLen())
	{
		text.Str()[Index] = Data;
	}
	SetUpdateSelf(1);
	return 0;
}

int32 spt::HmiWidTextLine::ShowSelf()
{
	if (!isUpdateSelf)
	{
		return 0;
	}
	isUpdateSelf = 0;
	gd->DrawStr(rect.x, rect.y, color, text.Str());
	return 0;
}

int32 spt::HmiWidTextLineRect::ShowSelf()
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

bool8 spt::HmiWidTextLineRect::SetText(const char* Text)
{
	if (text != Text)
	{
		SetUpdateSelf(1);
		text = Text;
	}
	return 1;
}

spt::HmiWidTextWnd::HmiWidTextWnd()
{
	maxCtxLine = 0;
	maxCtxW = 0;
	lastPage = 0xffff;
	lastLine = 0xffff;
	page = 0;
	line = 0;
	totalLine = 0;
	totalPage = 0;
	SetTitle("");
	ClearCtx();
	curse.SetEnable(0);
}

void spt::HmiWidTextWnd::SetInfo(const char* Title, uint32 Crc, uint32 CrcLen, uint32 Page, uint32 TotalPage)
{
	StrNCpy(title, Title, sizeof(title));
	crc = Crc;
	crcLen = CrcLen;
	page = Page;
	totalPage = TotalPage;
	isUpdateTitle = 1;
	SetUpdateSelf(1);
}

void spt::HmiWidTextWnd::SetPage(uint16 Page)
{
	if (page != Page)
	{
		isUpdateTitle = 1;
		SetUpdateSelf(1);
	}
	page = Page;
}

void spt::HmiWidTextWnd::SetLine(uint16 Line)
{
	if (line != Line)
	{
		isUpdateTitle = 1;
		SetUpdateSelf(1);
	}
	line = Line;
}

void spt::HmiWidTextWnd::SetCrc(uint32 Crc, uint32 CrcLen)
{
	crc = crc;
	crcLen = CrcLen;
	isUpdateTitle = 1;
	SetUpdateSelf(1);
}

void spt::HmiWidTextWnd::SetTitle(const char* Title)
{
	StrNCpy(title, Title, sizeof(title));
	isUpdateTitle = 1;
	SetUpdateSelf(1);
}

void spt::HmiWidTextWnd::SetTotalPage(uint16 Page)
{
	totalPage = Page;
	isUpdateTitle = 1;
	SetUpdateSelf(1);
}

void spt::HmiWidTextWnd::SetTotalLine(uint16 Line)
{
	totalLine = Line;
	isUpdateTitle = 1;
	SetUpdateSelf(1);
}

const HmiRect spt::HmiWidTextWnd::GetRect(uint16 StartRow, uint16 StartCol, uint16 W, uint16 H)
{
	HmiRect r;
	uint16 rowh = gd->FontHeight() + gd->SpaceOfFont();
	uint16 rowx = ctxRect.x + gd->SpaceOfFont();
	uint16 rowy = ctxRect.y + gd->SpaceOfFont();
	r.x = rowx + StartCol * gd->FontWidth();
	r.y = rowy + StartRow * rowh;
	r.w = W * gd->FontWidth();
	r.h = H * rowh;
	return r;
}

uint16 spt::HmiWidTextWnd::DispMaxCtxLine()
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

uint16 spt::HmiWidTextWnd::DispMaxCtxWidth()
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

void spt::HmiWidTextWnd::SetText(uint32 Row, uint32 Col, const char* Text)
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

void spt::HmiWidTextWnd::ClearCtx()
{
	for (uint32 i = 0; i < M_ArrLen(ctx); i++)
	{
		ClearCtxLine(i);
	}
}

void spt::HmiWidTextWnd::ClearCtxLine(uint32 LineNum)
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

int32 spt::HmiWidTextWnd::ShowSelf()
{
	if (isReDraw)
	{
		SetUpdateSelf(1);
		SetUpdateChild(1);
		isUpdateTitle = 1;
		isUpdateCtx = 1;
		isReDraw = 0;
		isInied = 0;
	}
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
		uint16 titleLen = totalLen - pagestr.StrLen();
		String100B titlestr;
		String100B title;

		title = this->title;

		if (crcLen)
		{
			title << "  CRC(";
			if (crcLen == 1)
			{
				title.FormatHex((uint8)this->crc);
			}
			else if (crcLen == 2)
			{
				title.FormatHex((uint16)this->crc);
			}
			else if (crcLen == 4)
			{
				title.FormatHex((uint32)this->crc);
			}
			title << ")";
		}
		titlestr.Format(title.Str(), titleLen, 1, ' ');
		titlestr << pagestr;
		gd->ClearRect(titleRect.x + gd->SpaceOfFont(), titleRect.y + gd->SpaceOfFont(), backcolor, titleRect.w - gd->FontWidth(), gd->FontHeight());
		gd->DrawStr(titleRect.x + gd->SpaceOfFont(), titleRect.y + gd->SpaceOfFont(), color, titlestr.Str());
		gd->Update(rect);
	}
	lastPage = page;
	lastLine = line;
	isUpdateTitle = 0;
	isUpdateSelf = 0;
	return 0;
}

int32 spt::HmiWidTextWnd::ShowChild()
{
	HmiWidObject::ShowChild();
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
		if (curse.IsEnable())
		{
			curse.Show();
		}
		gd->Update(rect);
	}
	isUpdateCtx = 0;
	isUpdateChild = 0;
	return 0;
}

spt::HmiWidCurseTextLine::HmiWidCurseTextLine()
{
	backcolor = gd->E_Black;
	color = gd->E_White;
	row = 0;
	col = 0;
}

void spt::HmiWidCurseTextLine::ClearRect()
{
	gd->ClearRect(rect.x, rect.y, color, rect.w, rect.h);
	SetUpdate(1);
}

int32 spt::HmiWidCurseTextLine::ShowSelf()
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

uint16 spt::HmiWidCurseTextLine::SetRow(uint16 Row)
{
	if (row != Row)
	{
		row = Row;
	}
	return row;
}

uint16 spt::HmiWidCurseTextLine::SetCol(uint16 Col)
{
	if (col != Col)
	{
		col = Col;
	}
	return col;
}

spt::HmiWidDataLine::HmiWidDataLine()
{
}

void spt::HmiWidDataLine::SetData(uint8 Type, u64value Value, bool8 IsFromRight, uint8 Len, uint8 DotLen, bool8 IsAddZero)
{
	data.valueType = Type;

	data.valueInfo1 = Len;
	data.valueInfo2 = DotLen;
	data.valueInfo3 = IsFromRight;
	data.valueInfo4 = IsAddZero;
	text.Clear();
	SetData(Value);
}

void spt::HmiWidDataLine::SetData(u64value Value)
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

int32 spt::HmiWidDataLine::ShowSelf()
{
	if (!isUpdateSelf)
	{
		return 0;
	}
	isUpdateSelf = 0;
	gd->DrawStr(rect.x, rect.y, color, text.Str());
	return 0;
}
