///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.0-4761b0c)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "LcdWnd.h"

///////////////////////////////////////////////////////////////////////////

SimLcd::SimLcd( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetToolTip( wxT("控制命令输入框") );

	m_menubar1 = new wxMenuBar( 0 );
	m_menu1 = new wxMenu();
	m_menubar1->Append( m_menu1, wxT("文件") );

	m_menu2 = new wxMenu();
	wxMenuItem* m_menuItem1;
	m_menuItem1 = new wxMenuItem( m_menu2, wxID_ANY, wxString( wxT("连接方式") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( m_menuItem1 );

	wxMenuItem* m_menuItem3;
	m_menuItem3 = new wxMenuItem( m_menu2, wxID_ANY, wxString( wxT("设置颜色") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( m_menuItem3 );

	m_menubar1->Append( m_menu2, wxT("设置") );

	HelpMenu = new wxMenu();
	wxMenuItem* m_menuItem2;
	m_menuItem2 = new wxMenuItem( HelpMenu, wxID_ANY, wxString( wxT("关于") ) , wxEmptyString, wxITEM_NORMAL );
	HelpMenu->Append( m_menuItem2 );

	m_menubar1->Append( HelpMenu, wxT("帮助") );

	this->SetMenuBar( m_menubar1 );

	m_toolBar1 = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY );
	m_staticText2 = new wxStaticText( m_toolBar1, wxID_ANY, wxT("按键输入框："), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	m_toolBar1->AddControl( m_staticText2 );
	m_textCtrl1 = new wxTextCtrl( m_toolBar1, wxID_ANY, wxT("点击此处输入按键"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar1->AddControl( m_textCtrl1 );
	m_button1 = new wxButton( m_toolBar1, wxID_ANY, wxT("截屏"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar1->AddControl( m_button1 );
	m_IpStr = new wxTextCtrl( m_toolBar1, wxID_ANY, wxT("100.100.100.100"), wxDefaultPosition, wxSize( 110,-1 ), 0 );
	m_toolBar1->AddControl( m_IpStr );
	m_button2 = new wxButton( m_toolBar1, wxID_ANY, wxT("连接"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar1->AddControl( m_button2 );
	b_ReSet = new wxButton( m_toolBar1, wxID_ANY, wxT("复归"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar1->AddControl( b_ReSet );
	m_toolBar1->Realize();

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	bSizer6->SetMinSize( wxSize( 488,-1 ) );
	m_unitName = new wxStaticText( this, wxID_ANY, wxT("虚拟液晶"), wxDefaultPosition, wxSize( 484,-1 ), wxALIGN_CENTER_HORIZONTAL );
	m_unitName->Wrap( -1 );
	bSizer6->Add( m_unitName, 0, wxALL, 5 );

	m_bitmap1 = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 500,280 ), 0 );
	m_bitmap1->SetMinSize( wxSize( 500,280 ) );
	m_bitmap1->SetMaxSize( wxSize( 500,280 ) );

	bSizer6->Add( m_bitmap1, 0, wxALL, 1 );


	bSizer5->Add( bSizer6, 1, wxEXPAND, 5 );

	LedFrame = new wxFlexGridSizer( 12, 5, 8, 5 );
	LedFrame->AddGrowableCol( 0 );
	LedFrame->AddGrowableCol( 1 );
	LedFrame->AddGrowableCol( 2 );
	LedFrame->AddGrowableCol( 3 );
	LedFrame->AddGrowableCol( 4 );
	LedFrame->SetFlexibleDirection( wxHORIZONTAL );
	LedFrame->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );


	bSizer5->Add( LedFrame, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer5 );
	this->Layout();
	m_statusBar1 = this->CreateStatusBar( 4, wxSTB_SHOW_TIPS|wxSTB_SIZEGRIP, wxID_ANY );
	m_timer1.SetOwner( this, wxID_ANY );
	m_timer1.Start( 1000 );

	m_timer2.SetOwner( this, wxID_ANY );
	m_timer2.Start( 20 );


	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( SimLcd::WndClose ) );
	m_menu2->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( SimLcd::SetLCDCorlor ), this, m_menuItem3->GetId());
	HelpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( SimLcd::ShowAboat ), this, m_menuItem2->GetId());
	m_textCtrl1->Connect( wxEVT_CHAR, wxKeyEventHandler( SimLcd::OnChar ), NULL, this );
	m_textCtrl1->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( SimLcd::OnKey ), NULL, this );
	m_textCtrl1->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( SimLcd::OnLostFocus ), NULL, this );
	m_textCtrl1->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( SimLcd::OnGetFocus ), NULL, this );
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SimLcd::CaptureBmp ), NULL, this );
	m_IpStr->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SimLcd::SetIpAddr ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SimLcd::LinkLcd ), NULL, this );
	b_ReSet->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SimLcd::CreatRstKey ), NULL, this );
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( SimLcd::UpdateUi ) );
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( SimLcd::UpdateLcd ) );
}

SimLcd::~SimLcd()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( SimLcd::WndClose ) );
	m_textCtrl1->Disconnect( wxEVT_CHAR, wxKeyEventHandler( SimLcd::OnChar ), NULL, this );
	m_textCtrl1->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( SimLcd::OnKey ), NULL, this );
	m_textCtrl1->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( SimLcd::OnLostFocus ), NULL, this );
	m_textCtrl1->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( SimLcd::OnGetFocus ), NULL, this );
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SimLcd::CaptureBmp ), NULL, this );
	m_IpStr->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SimLcd::SetIpAddr ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SimLcd::LinkLcd ), NULL, this );
	b_ReSet->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SimLcd::CreatRstKey ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( SimLcd::UpdateUi ) );
	this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( SimLcd::UpdateLcd ) );

}

SetLcdColour::SetLcdColour( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	wxGridBagSizer* gbSizer1;
	gbSizer1 = new wxGridBagSizer( 0, 0 );
	gbSizer1->SetFlexibleDirection( wxBOTH );
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_colourPicker1 = new wxColourPickerCtrl( this, wxID_ANY, wxColour( 0, 255, 64 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	gbSizer1->Add( m_colourPicker1, wxGBPosition( 1, 2 ), wxGBSpan( 1, 2 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("前景色"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	gbSizer1->Add( m_staticText5, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("实验文本"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	gbSizer1->Add( m_staticText3, wxGBPosition( 0, 2 ), wxGBSpan( 1, 3 ), wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("背景色"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	gbSizer1->Add( m_staticText6, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_colourPicker2 = new wxColourPickerCtrl( this, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	gbSizer1->Add( m_colourPicker2, wxGBPosition( 2, 2 ), wxGBSpan( 1, 2 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	Apply = new wxButton( this, wxID_ANY, wxT("应用"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( Apply, wxGBPosition( 3, 4 ), wxGBSpan( 1, 1 ), wxALL, 5 );


	bSizer3->Add( gbSizer1, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer3 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( SetLcdColour::SetCorlorClose ) );
	m_colourPicker1->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( SetLcdColour::ForeCorlourChanged ), NULL, this );
	m_colourPicker2->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( SetLcdColour::BackCorlourChanged ), NULL, this );
	Apply->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SetLcdColour::ApplySet ), NULL, this );
}

SetLcdColour::~SetLcdColour()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( SetLcdColour::SetCorlorClose ) );
	m_colourPicker1->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( SetLcdColour::ForeCorlourChanged ), NULL, this );
	m_colourPicker2->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( SetLcdColour::BackCorlourChanged ), NULL, this );
	Apply->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SetLcdColour::ApplySet ), NULL, this );

}
