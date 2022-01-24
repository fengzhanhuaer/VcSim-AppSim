///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.0-4761b0c)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/menu.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/toolbar.h>
#include <wx/statbmp.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
#include <wx/timer.h>
#include <wx/frame.h>
#include <wx/clrpicker.h>
#include <wx/gbsizer.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class SimLcd
///////////////////////////////////////////////////////////////////////////////
class SimLcd : public wxFrame
{
	private:

	protected:
		wxMenuBar* m_menubar1;
		wxMenu* m_menu1;
		wxMenu* m_menu2;
		wxMenu* HelpMenu;
		wxToolBar* m_toolBar1;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_textCtrl1;
		wxButton* m_button1;
		wxTextCtrl* m_IpStr;
		wxButton* m_button2;
		wxButton* b_ReSet;
		wxStatusBar* m_statusBar1;
		wxTimer m_timer1;
		wxTimer m_timer2;

		// Virtual event handlers, override them in your derived class
		virtual void WndClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void SetLCDCorlor( wxCommandEvent& event ) { event.Skip(); }
		virtual void ShowAboat( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChar( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnKey( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnLostFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnGetFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void CaptureBmp( wxCommandEvent& event ) { event.Skip(); }
		virtual void SetIpAddr( wxCommandEvent& event ) { event.Skip(); }
		virtual void LinkLcd( wxCommandEvent& event ) { event.Skip(); }
		virtual void CreatRstKey( wxCommandEvent& event ) { event.Skip(); }
		virtual void UpdateUi( wxTimerEvent& event ) { event.Skip(); }
		virtual void UpdateLcd( wxTimerEvent& event ) { event.Skip(); }


	public:
		wxStaticText* m_unitName;
		wxStaticBitmap* m_bitmap1;
		wxFlexGridSizer* LedFrame;

		SimLcd( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SimLcd"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 993,429 ), long style = wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLIP_CHILDREN|wxTAB_TRAVERSAL );

		~SimLcd();

};

///////////////////////////////////////////////////////////////////////////////
/// Class SetLcdColour
///////////////////////////////////////////////////////////////////////////////
class SetLcdColour : public wxDialog
{
	private:

	protected:
		wxColourPickerCtrl* m_colourPicker1;
		wxStaticText* m_staticText5;
		wxStaticText* m_staticText3;
		wxStaticText* m_staticText6;
		wxColourPickerCtrl* m_colourPicker2;
		wxButton* Apply;

		// Virtual event handlers, override them in your derived class
		virtual void SetCorlorClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void ForeCorlourChanged( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void BackCorlourChanged( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void ApplySet( wxCommandEvent& event ) { event.Skip(); }


	public:

		SetLcdColour( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("…Ë÷√—’…´"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 305,182 ), long style = wxDEFAULT_DIALOG_STYLE );

		~SetLcdColour();

};

