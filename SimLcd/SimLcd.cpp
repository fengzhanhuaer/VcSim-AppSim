#include"SimLcd.h"
#include"LcdMain.h"

using namespace spt;
IMPLEMENT_APP(MyApp)

const int lcdPixelHight = 272;
const int lcdPixelWidght = 480;

uint8 lcdPixelBuf[lcdPixelHight][lcdPixelWidght / 8 + 1];
bool lcdPixelBufUpdate = 1;
static const uint32 LedColMax = 5;
static const uint32 LedRowMax = 12;
struct LedCfg
{
	wxStaticText* Led;
	uint32 LedCor;
	uint8 serial;
	uint8 map;
};
LedCfg ledCfg[LedRowMax][LedColMax];
uint32 ledNum;

uint32 drawdelta;
extern uint32 mainLoopLoaddelta;
class SetLcdColourInst : public SetLcdColour
{
public:
	SetLcdColourInst() : SetLcdColour(0) {}
	void Show()
	{
		m_staticText3->SetForegroundColour(m_colourPicker1->GetColour());
		m_staticText3->SetBackgroundColour(m_colourPicker2->GetColour());
		m_staticText3->Refresh();
		ShowModal();
	}
	wxColourPickerCtrl* ForeGroundColour() { return m_colourPicker1; };
	wxColourPickerCtrl* BackGroundColour() { return m_colourPicker2; };
	virtual void ForeCorlourChanged(wxColourPickerEvent& event) {
		event.Skip();
		m_staticText3->SetForegroundColour(m_colourPicker1->GetColour());
		m_staticText3->Refresh();
	}
	virtual void BackCorlourChanged(wxColourPickerEvent& event) {
		event.Skip();
		m_staticText3->SetBackgroundColour(m_colourPicker2->GetColour());
		m_staticText3->Refresh();
	}
	virtual void ApplySet(wxCommandEvent& event);
};
class LcdConfig :public CfgFile
{
public:
	CfgHex32 ForeGroundColour;
	CfgHex32 BackGroundColour;
public:
	int32 PowerUpIni(int32 Para)
	{
		ForeGroundColour.Set("FrontCorlor", 0xff40ff00);
		AddCfgData(&ForeGroundColour);
		BackGroundColour.Set("BackCorlor", 0xff000000);
		AddCfgData(&BackGroundColour);
		path.Set(CN_CFG_FILE_ROOT);
		name.Set("LcdCfg.cfg");
		if ((uint32)ReadAll() != CfgDataNum())
		{
			SaveAll();
		}
		LoadSet();
		return 0;
	}
	void SaveSet()
	{
		SaveAll();
	}
	void LoadSet()
	{
		ReadAll();

	}
	void SetLcdCorlor()
	{
		LoadSet();
		SetLcdColourInst inst;
		inst.ForeGroundColour()->SetColour(ForeGroundColour.Data());
		inst.BackGroundColour()->SetColour(BackGroundColour.Data());
		inst.Show();

		SaveSet();
	}

public:
	M_Singleton(LcdConfig);
	LcdConfig() {	}
protected:
	virtual PCfgDataBase* CfgPool() { return pool; };
	virtual uint32 CfgPoolSize() { return M_ArrLen(pool); };
private:
	PCfgDataBase pool[20];
};
void SetLcdColourInst::ApplySet(wxCommandEvent& event) {

	LcdConfig::Instance().ForeGroundColour.SetData(ForeGroundColour()->GetColour().GetRGBA());
	LcdConfig::Instance().BackGroundColour.SetData(BackGroundColour()->GetColour().GetRGBA());
	event.Skip();
}
class InstLogOnWnd :public LogOnWnd
{
public:
	InstLogOnWnd(bool8 isCheckId, bool8 isCheckAccount, SalString& Id, SalString& Name, SalString& Pw)
		:LogOnWnd(0), Id(Id), Name(Name), Pw(Pw)
	{
		this->isCheckId = isCheckId;
		this->isCheckAccount = isCheckAccount;
		if (!isCheckId)
		{
			LogBox->Hide((size_t)0);
		}
		if (!isCheckAccount)
		{
			LogBox->Hide((size_t)1);
		}
	}
	virtual void Enter(wxCommandEvent& event)
	{
		event.Skip(0);
		Id = idtext->GetValue();
		Name = nametext->GetValue();
		Pw = pwtext->GetValue();
		Close(1);
	}
	virtual void Cancel(wxCommandEvent& event)
	{
		event.Skip(0);
		Close(1);
	}
	bool8 isCheckId;
	bool8 isCheckAccount;
	SalString& Id;
	SalString& Name;
	SalString& Pw;
};
class MySimLcd :public SimLcd
{
public:
	MsTimer forceCloseSocket;
public:
	MySimLcd() :SimLcd(NULL) {

		LcdConfig::Instance().PowerUpIni(0);
		m_textCtrl1->SetFocus();
		wxString str = DbgSimCfg::Instance().ServerIp.StrData();
		m_IpStr->SetValue(str);
		for (size_t i = 0; i < LedRowMax; i++)
		{
			for (size_t j = 0; j < LedColMax; j++)
			{
				wxString str("LED未启用   ");
				ledCfg[i][j].Led = new wxStaticText(this, wxID_ANY, str, wxDefaultPosition, wxDefaultSize, 0);
				ledCfg[i][j].Led->Wrap(-1);
				ledCfg[i][j].LedCor = 0;
				ledCfg[i][j].serial = 0xff;
				ledCfg[i][j].map = 0xff;
				ledCfg[i][j].Led->SetForegroundColour(wxColour(255, 255, 255, 0));
				ledCfg[i][j].Led->SetBackgroundColour(wxColour(0, 0, 0, 0));
				LedFrame->Add(ledCfg[i][j].Led, 1, wxEXPAND, 1);
			}
		}
		IniLcdInfo();
	}
	void IniLcdInfo()
	{
		for (int16 i = 0; i < lcdPixelHight; i++)
		{
			for (int16 j = 0; j < lcdPixelWidght; j++)
			{
				lcdPixelBuf[i][j / 8] = 0;
			}
		}
		for (size_t i = 0; i < LedRowMax; i++)
		{
			for (size_t j = 0; j < LedColMax; j++)
			{
				wxString str("LED未启用");
				ledCfg[i][j].Led->SetLabelText(str);
				ledCfg[i][j].LedCor = 0;
				ledCfg[i][j].serial = 0xff;
				ledCfg[i][j].map = 0xff;
				ledCfg[i][j].Led->SetForegroundColour(wxColour(255, 255, 255, 0));
				ledCfg[i][j].Led->SetBackgroundColour(wxColour(0, 0, 0, 0));
			}
		}
	}
	virtual void UpdateUi(wxTimerEvent& event)
	{
		HmiLcdCmm::Instance().CheckStatus();
		wxString str;
		if (VirLcdCmmClient::Instance().TaskStep() == DbgClient::E_ClentIni)
		{
			str << "初始化";
		}
		else if (VirLcdCmmClient::Instance().TaskStep() == DbgClient::E_WaitConnect)
		{
			str << "等待建立链接···";
		}
		else if (VirLcdCmmClient::Instance().TaskStep() == DbgClient::E_AskConnect)
		{
			str << "申请链接···";
		}
		else if (VirLcdCmmClient::Instance().TaskStep() == DbgClient::E_LogOn)
		{
			str << "正在登录···";
		}
		else if (VirLcdCmmClient::Instance().TaskStep() == DbgClient::E_AskIniInfo)
		{
			str << "索要信息···";
		}
		else if (VirLcdCmmClient::Instance().TaskStep() == DbgClient::E_Work)
		{
			str << "已连接";
		}
		else if (VirLcdCmmClient::Instance().TaskStep() == DbgClient::E_Check)
		{
			str << "自检···";
		}
		if ((!isloging) && (needlog))
		{
			isloging = 1;
			InstLogOnWnd w(isCheckId, isCheckAccount, Id, Name, Pw);
			w.ShowModal();
			needlog = 0;
			Sleep(500);
			while (VirLcdCmmClient::Instance().LogStatus() == DbgClient::E_CheckPw)
			{
				Sleep(100);
			}
			isloging = 0;
			uint8 status = VirLcdCmmClient::Instance().LogStatus();
			if (status == DbgClient::E_LogOnIdErr)
			{
				wxMessageDialog dia(0, "唯一性代码不正确");
				dia.ShowModal();
			}
			else if (status == DbgClient::E_LogOnAccountErr)
			{
				wxMessageDialog dia(0, "帐号或密码错误");
				dia.ShowModal();
			}
			else if (status == DbgClient::E_LogOnLinkErr)
			{
				wxMessageDialog dia(0, "网络连接异常");
				dia.ShowModal();
			}
			else if (status == DbgClient::E_LogOverTime)
			{
				wxMessageDialog dia(0, "登录超时");
				dia.ShowModal();
			}
		}
		m_statusBar1->SetStatusText(str, 0);
		str.Clear();
		str << "接收:" << HmiLcdCmm::Instance().OutPut().recvCnt << "-" << HmiLcdCmm::Instance().OutPut().recvErrCnt;
		m_statusBar1->SetStatusText(str, 1);
		str.Clear();
		str << "发送:" << HmiLcdCmm::Instance().OutPut().sendCnt << "-" << HmiLcdCmm::Instance().OutPut().sendErrCnt;
		m_statusBar1->SetStatusText(str, 2);
		str.Clear();
		str << drawdelta << "-" << mainLoopLoaddelta;
		m_statusBar1->SetStatusText(str, 3);
		event.Skip(0);
	}
	virtual void UpdateLcd(wxTimerEvent& event) {
		if (lcdPixelBufUpdate == 0)
		{
			if (forceCloseSocket.IsEnable() == 0)
			{
				forceCloseSocket.UpCnt(5000);
				forceCloseSocket.Enable(1);
			}
			if (forceCloseSocket.Status())
			{
				if (HmiLcdCmm::Instance().IsLinkOk())
				{
					HmiLcdCmm::Instance().CheckStatus();
				}
			}
			return;
		}
		forceCloseSocket.Restart();
		lcdPixelBufUpdate = 0;
		uint32 start = HwUsCnt();

		wxImage LcdCache(484, 276);
		uint8* bf;
		wxColour fore, back;
		fore.SetRGBA(LcdConfig::Instance().ForeGroundColour.Data());
		back.SetRGBA(LcdConfig::Instance().BackGroundColour.Data());
		for (uint32 i = 0; i < 276; i++)
		{
			for (uint32 j = 0; j < 484; j++)
			{
				LcdCache.SetRGB(j, i, back.Red(), back.Green(), back.Blue());
			}
		}
		for (uint32 i = 0; i < lcdPixelHight; i++)
		{
			bf = lcdPixelBuf[i];
			for (uint32 j = 0; j < lcdPixelWidght; j++)
			{
				if (GetBit(bf[j / 8], 7 - j % 8))
				{
					LcdCache.SetRGB(j + 2, i + 2, fore.Red(), fore.Green(), fore.Blue());
				}
			}
		}
		wxBitmap  hwWndCacheImage(LcdCache);
		m_bitmap1->SetBitmap(hwWndCacheImage);
		event.Skip(0);
		uint32 end = HwUsCnt();
		drawdelta = (end - start) / 1000;
	}
	void ReSize()
	{

	}
	virtual void CaptureBmp(wxCommandEvent& event) {
		event.Skip(0);
		wxBitmap hwWndCacheImage1 = m_bitmap1->GetBitmap();
		String100B str;
		str << ".\\Captue\\";
		wxDateTime dt = wxDateTime::UNow();

		wxString st = dt.Format("%Y年%m月%d日 %H-%M-%S.");
		str << st.c_str();
		str.Format(dt.GetMillisecond(), 3, '0') << ".bmp";
		hwWndCacheImage1.SaveFile(wxString(str.Str()), wxBITMAP_TYPE_BMP);
		m_textCtrl1->SetFocus();
	}
	virtual void OnKey(wxKeyEvent& event)
	{
		String100B str;
		uint32 code = event.GetKeyCode();
		uint8 type = EK1_KEYVALUE;
		uint8 ctrl = 0;
		if (event.AltDown())
		{
			ctrl |= EK_ALT;
		}
		if (event.ShiftDown())
		{
			ctrl |= EK_SHIFT;
		}
		if (event.ControlDown())
		{
			ctrl |= EK_CTRL;
		}
		if (code == WXK_NUMPAD_ENTER)
		{
			event.Skip(0);
			HmiKey key = { type ,(uint8)EK_ENTER,0,ctrl };
			HmiKeyService::Instance().Push(key);
			m_textCtrl1->Clear();
			m_textCtrl1->SetLabelText("EK_ENTER");
		}
		else if (code == WXK_RETURN)
		{
			event.Skip(0);
			HmiKey key = { type ,(uint8)EK_ENTER,0,ctrl };
			HmiKeyService::Instance().Push(key);
			m_textCtrl1->Clear();
			m_textCtrl1->SetLabelText("EK_ENTER");
		}
		else if (code == WXK_BACK)
		{
			event.Skip(0);
			HmiKey key = { type, (uint8)EK_BACK,0,ctrl };
			HmiKeyService::Instance().Push(key);
			m_textCtrl1->Clear();
			m_textCtrl1->SetLabelText("EK_BACK");
		}
		else if (code == WXK_ESCAPE)
		{
			event.Skip(0);
			HmiKey key = { type,(uint8)EK_ESC,0,ctrl };
			HmiKeyService::Instance().Push(key);
			m_textCtrl1->SetLabelText("EK_ESC");
		}
		else if (code == WXK_LEFT)
		{
			event.Skip(0);
			HmiKey key = { type,(uint8)EK_LEFT,0,0 };
			HmiKeyService::Instance().Push(key);
			m_textCtrl1->SetLabelText("EK_LEFT");
		}
		else if (code == WXK_UP)
		{
			event.Skip(0);
			HmiKey key = { type,(uint8)EK_UP,0,ctrl };
			HmiKeyService::Instance().Push(key);
			m_textCtrl1->SetLabelText("EK_UP");
		}
		else if (code == WXK_RIGHT)
		{
			event.Skip(0);
			HmiKey key = { type,(uint8)EK_RIGHT,0,ctrl };
			HmiKeyService::Instance().Push(key);
			m_textCtrl1->SetLabelText("EK_RIGHT");
		}
		else if (code == WXK_DOWN)
		{
			event.Skip(0);
			HmiKey key = { type, (uint8)EK_DOWN,0,ctrl };
			HmiKeyService::Instance().Push(key);
			m_textCtrl1->SetLabelText("EK_DOWN");
		}
		else if (code == WXK_NUMPAD_ADD)
		{
			event.Skip(1);
			HmiKey key = { type, (uint8)EK_ADD,0,ctrl };
			HmiKeyService::Instance().Push(key);
			m_textCtrl1->SetLabelText("EK_ADD");
		}
		else if (code == WXK_NUMPAD_SUBTRACT)
		{
			event.Skip(1);
			HmiKey key = { type,(uint8)EK_SUB,0,ctrl };
			HmiKeyService::Instance().Push(key);
			m_textCtrl1->SetLabelText("EK_SUB");
		}
		else if (code == WXK_NUMPAD_DECIMAL)
		{
			event.Skip(1);
			HmiKey key = { type,(uint8)EK_DOT,0,ctrl };
			HmiKeyService::Instance().Push(key);
			m_textCtrl1->SetLabelText("EK_DOT");
		}
		else if (code == WXK_MEDIA_STOP)
		{
			event.Skip(1);
			HmiKey key = { type,(uint8)EK_MD_STOP,0,ctrl };
			HmiKeyService::Instance().Push(key);
			m_textCtrl1->SetLabelText("EK_MD_STOP");
		}
		else if (code == WXK_F1)
		{
			event.Skip(1);
			HmiKey key = { type,(uint8)EK_F1,0,ctrl };
			HmiKeyService::Instance().Push(key);
			m_textCtrl1->SetLabelText("EK_F1");
		}
		else
		{
			wxString str;
			str << code;
			event.Skip(1);
		}
	}
	virtual void OnChar(wxKeyEvent& event)
	{
		uint32 code = event.GetKeyCode();
		uint8 ctrl = 0;
		if (event.AltDown())
		{
			ctrl |= EK_ALT;
		}
		if (event.ShiftDown())
		{
			ctrl |= EK_SHIFT;
		}
		if (event.ControlDown())
		{
			ctrl |= EK_CTRL;
		}
		if ((code <= 126) && (code >= WXK_SPACE))
		{
			uint8 type = EK1_ASSIC;
			HmiKey key = { type, (uint8)code,0,ctrl };
			HmiKeyService::Instance().Push(key);
			String100B str;
			str << (char)code;
			m_textCtrl1->SetLabelText(str.Str());
			event.Skip(0);
		}
	}
	virtual void SetIpAddr(wxCommandEvent& event)
	{
		event.Skip(1);
	}
	virtual void LinkLcd(wxCommandEvent& event)
	{
		event.Skip(0);
		wxString str = m_IpStr->GetValue();

		String100B cstr;
		cstr = str.c_str();
		if (cstr != DbgSimCfg::Instance().ServerIp.StrData())
		{
			DbgSimCfg::Instance().ServerIp.SetData(cstr.Str());
			DbgSimCfg::Instance().SaveAll();
		}
		VirLcdCmmClient::Instance().ReConnect();
		m_textCtrl1->SetFocus();
	}
	virtual void WndClose(wxCloseEvent& event);
	virtual void CreatRstKey(wxCommandEvent& event)
	{
		event.Skip(0);
		uint8 type = EK1_KEYVALUE;
		uint8 ctrl = 0;
		HmiKey key = { type ,(uint8)EK_F1,0,ctrl };
		HmiKeyService::Instance().Push(key);
		m_textCtrl1->Clear();
		m_textCtrl1->SetLabelText("EK_F1");
		event.Skip();
		m_textCtrl1->SetFocus();
	}
	virtual void OnLostFocus(wxFocusEvent& event) {
		event.Skip();
		m_textCtrl1->SetBackgroundColour(*wxRED);
		m_textCtrl1->SetLabelText("点击此处输入按键");
	}
	virtual void OnGetFocus(wxFocusEvent& event) {
		event.Skip();
		m_textCtrl1->SetBackgroundColour(*wxWHITE);
	}
	virtual void ShowAbout(wxCommandEvent& event)
	{
		wxMessageDialog dig(this, "iESLab, All Rights Reserved.\n冯占华\n V1.0.1\n" __DATE__" " __TIME__, "关于", wxOK);
		dig.ShowModal();
		event.Skip();
	}
	virtual void SetLCDCorlor(wxCommandEvent& event) {
		event.Skip();
		LcdConfig::Instance().SetLcdCorlor();
	}
	bool8 AskForLogOnInfo(bool8 isCheckId, bool8 isCheckAccount, SalString& Id, SalString& Name, SalString& Pw, int32(*DoHeartCheck)())
	{
		this->isCheckId = isCheckId;
		this->isCheckAccount = isCheckAccount;
		needlog = 0;
		if (isCheckAccount || isCheckId)
		{
			needlog = 1;
		}
		while (needlog)
		{
			Sleep(200);
			if (DoHeartCheck)
			{
				DoHeartCheck();
			}
		}
		if (isCheckAccount || isCheckId)
		{
			Id = this->Id.Str();
			Name = this->Name.Str();
			Pw = this->Pw.Str();
		}
		return 1;
	}
	bool8 isloging;
	bool8 needlog;
	bool8 isCheckId;
	bool8 isCheckAccount;
	String100B Id;
	String100B Name;
	String100B Pw;
};
void MySimLcd::WndClose(wxCloseEvent& event)
{
	LcdMain::Instance().Exit();
	SimLcd::WndClose(event);
}

extern"C"  int LcdWriteDispBuf(unsigned x, unsigned y, unsigned w, unsigned h, void* buf, unsigned bufW, unsigned bufH)
{
	uint8* bf;
	for (uint32 i = 0; i < bufH; i++)
	{
		bf = (uint8*)buf + i * bufW;
		for (uint32 j = 0; j < bufW; j++)
		{
			lcdPixelBuf[i][j] = bf[j];
		}
	}
	lcdPixelBufUpdate = 1;
	return 0;
}
void AskForLedInfo(uint16 IedNum)
{
	LcdIedInfo lmc;
	lmc.type = E_LedInfoAsk;
	lmc.len = sizeof(lmc) - sizeof(lmc.data);
	lmc.ledNum = IedNum;
	HmiLcdCmm::Instance().Send((LcdMsgContext*)&lmc);
}
MySimLcd* lcdwnd = 0;
void spt::LcdSetDispInfo(uint16 IedNum, const char* Name)
{
	if (lcdwnd)
	{
		lcdwnd->m_unitName->SetLabelText(Name);
		ledNum = IedNum;
		lcdwnd->IniLcdInfo();
	}

	if (IedNum)
	{
		AskForLedInfo(0);
	}
}
uint32 GetLedColor(uint16 Cor)
{
	switch (Cor)
	{
	case HmiLed::E_RED:
	{
		return RGB(255, 0, 0);
		break;
	}
	case HmiLed::E_GREEN:
	{
		return RGB(0, 128, 0);
		break;
	}
	case HmiLed::E_YELLOW:
	{
		return RGB(255, 165, 0);
		break;
	}
	default:
		break;
	}
	return RGB(0, 0, 0);;
}
void spt::LcdSetLedDispInfo(uint16 IedSerial, uint16 Cor, const char* LedName)
{
	if (!lcdwnd)
	{
		return;
	}
	if (IedSerial < ledNum)
	{
		ledCfg[LedName[0]][LedName[1]].serial = IedSerial;
		ledCfg[IedSerial / LedColMax][IedSerial % LedColMax].map = LedName[0] * LedColMax + LedName[1];
		ledCfg[LedName[0]][LedName[1]].Led->SetLabelText(LedName + 2);
		ledCfg[LedName[0]][LedName[1]].Led->Refresh();
		ledCfg[LedName[0]][LedName[1]].LedCor = GetLedColor(Cor);
		uint8 map = ledCfg[IedSerial / LedColMax][IedSerial % LedColMax].map;
		ledCfg[map / LedColMax][map % LedColMax].Led->SetForegroundColour(wxColour(ledCfg[LedName[0]][LedName[1]].LedCor));
		ledCfg[map / LedColMax][map % LedColMax].Led->SetBackgroundColour(wxColour(255, 255, 255, 0));
		ledCfg[map / LedColMax][map % LedColMax].Led->Refresh();
		IedSerial++;
		if (IedSerial == ledNum)
		{
			VirLcdCmmClient::Instance().SetIedInfoIniedFlag(1);
			lcdwnd->ReSize();
		}
		else
		{
			AskForLedInfo(IedSerial);
		}
	}
	else
	{
		VirLcdCmmClient::Instance().SetIedInfoIniedFlag(1);
	}
}
extern "C" int LcdSetLedDispVal(unsigned IedSerial, unsigned Cor)
{
	uint8 map = ledCfg[IedSerial / LedColMax][IedSerial % LedColMax].map;
	if (map == 255)
	{
		return 0;
	}
	if (Cor)
	{
		ledCfg[map / LedColMax][map % LedColMax].Led->SetForegroundColour(wxColour(255, 255, 255, 0));
		ledCfg[map / LedColMax][map % LedColMax].Led->SetBackgroundColour(wxColour((ledCfg[map / LedColMax][map % LedColMax].LedCor)));
	}
	else
	{
		ledCfg[map / LedColMax][map % LedColMax].Led->SetForegroundColour(wxColour((ledCfg[map / LedColMax][map % LedColMax].LedCor)));
		ledCfg[map / LedColMax][map % LedColMax].Led->SetBackgroundColour(wxColour(255, 255, 255, 0));
	}
	ledCfg[map / LedColMax][map % LedColMax].Led->Refresh();
	return 0;
}


bool MyApp::OnInit()
{
	HANDLE hProc = GetCurrentProcess();
	bool res = SetPriorityClass(hProc, HIGH_PRIORITY_CLASS);
	static HANDLE hThread = GetCurrentThread();
	//bool res = SetThreadPriority(hThread, THREAD_PRIORITY_ABOVE_NORMAL);
	DbgSimCfg::Instance().PowerUpIni(0);
	CheckDbgClientCrt();
	SalFile file;
	file.Path().Set(".\\Captue\\");
	file.Path().Creat();
	if (!wxApp::OnInit())
	{
		return false;
	}
	lcdwnd = new MySimLcd();
	LcdMain::Instance().PowerUpIni(0);
	lcdwnd->Show();
	return true;
}

int32 DoLogHeartBeat()
{
	VirLcdCmmClient::Instance().SendLogHeartBeat();
	return 0;
}
bool8 spt::AskForLogOnInfo(bool8 isCheckId, bool8 isCheckAccount, SalString& Id, SalString& Name, SalString& Pw, int32(*DoHeartCheck)())
{
	return lcdwnd->AskForLogOnInfo(isCheckId, isCheckAccount, Id, Name, Pw, DoLogHeartBeat);
}