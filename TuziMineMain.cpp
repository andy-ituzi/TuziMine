/***************************************************************
 * Name:      TuziMineMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    AndyLin (andy_lin@live.cn)
 * Created:   2014-11-18
 * Copyright: AndyLin (@@@)
 * License:
 **************************************************************/

#include "TuziMineMain.h"

#include <wx/msgdlg.h>
#include <iostream>
using namespace std;

//(*InternalHeaders(TuziMineFrame)
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(TuziMineFrame)
const long TuziMineFrame::ID_MENUITEM1 = wxNewId();
const long TuziMineFrame::idMenuAbout = wxNewId();
//*)

BEGIN_EVENT_TABLE(TuziMineFrame,wxFrame)
    //(*EventTable(TuziMineFrame)
    //*)
END_EVENT_TABLE()

TuziMineFrame::TuziMineFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(TuziMineFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX, _T("wxID_ANY"));
    Move(wxPoint(0,0));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("D:\\Desktop\\Coding\\TuziMine\\images\\pink_heart_2.png"))));
    	SetIcon(FrameIcon);
    }
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, ID_MENUITEM1, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);

    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&TuziMineFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&TuziMineFrame::OnAbout);
    //*)
    SetTitle(wxString("A tiny gift for you my dear!"));
    Move(300, 10);
    SetClientSize(CLIENT_SIZE);
    m_canvas = new CGLCanvas(this, 0, CLIENT_SIZE);
}

TuziMineFrame::~TuziMineFrame()
{
    //(*Destroy(TuziMineFrame)
    //*)
}

void TuziMineFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void TuziMineFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = _("A tiny gift for you my dear!\n\n Andy.ituzi@gmail.com");
    wxMessageBox(msg, _("About..."));
}
