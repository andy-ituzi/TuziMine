/***************************************************************
 * Name:      TuziMineMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    AndyLin (andy_lin@live.cn)
 * Created:   2014-11-18
 * Copyright: AndyLin (@@@)
 * License:
 **************************************************************/

#include "TuziMineMain.h"
#include <wx/filedlg.h>
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

#include "CCanvas.h"

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
const long TuziMineFrame::ID_TEXTCTRL1 = wxNewId();
const long TuziMineFrame::ID_PANEL1 = wxNewId();
const long TuziMineFrame::ID_PANEL2 = wxNewId();
const long TuziMineFrame::ID_QUIT = wxNewId();
const long TuziMineFrame::ID_EDIT_LOAD = wxNewId();
const long TuziMineFrame::ID_EDIT_SAVE = wxNewId();
const long TuziMineFrame::ID_EDIT_RESTART = wxNewId();
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
    wxMenuItem* MenuItem4;
    wxMenu* Menu1;
    wxMenuItem* MenuItem3;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX, _T("wxID_ANY"));
    Move(wxPoint(0,0));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T(".\\images\\pink_heart_2.png"))));
    	SetIcon(FrameIcon);
    }
    Panel_edit = new wxPanel(this, ID_PANEL1, wxPoint(0,0), wxSize(400,600), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    TextCtrl_file = new wxTextCtrl(Panel_edit, ID_TEXTCTRL1, wxEmptyString, wxPoint(0,0), wxSize(400,600), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    Panel_canvas = new wxPanel(this, ID_PANEL2, wxPoint(600,0), wxSize(600,600), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, ID_QUIT, _("Quit\tAlt+F4"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, ID_EDIT_LOAD, _("Load Config\tAlt+L"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuItem3 = new wxMenuItem(Menu2, ID_EDIT_SAVE, _("Save Config\tAlt-S"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem3);
    MenuItem4 = new wxMenuItem(Menu2, ID_EDIT_RESTART, _("Restart Canvas\tAlt-R"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem4);
    MenuBar1->Append(Menu2, _("&Edit"));
    SetMenuBar(MenuBar1);

    Connect(ID_QUIT,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&TuziMineFrame::OnQuit);
    Connect(ID_EDIT_LOAD,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&TuziMineFrame::OnEditLoad);
    Connect(ID_EDIT_SAVE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&TuziMineFrame::OnEditSave);
    Connect(ID_EDIT_RESTART,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&TuziMineFrame::OnEditRestart);
    //*)
    SetTitle(wxString("A tiny gift for you my dear!"));
    Move(200, 10);
    SetClientSize(1000, 600);
    if (true == EDIT_MODE)
    {
        m_canvas = new CGLCanvas(Panel_canvas, 0, CLIENT_SIZE);
        Panel_canvas->Move(0,0);
        Panel_edit->Move(600,0);
    }
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


void TuziMineFrame::OnEditLoad(wxCommandEvent& event)
{
    TextCtrl_file->LoadFile("canvas.config");
}

void TuziMineFrame::OnEditSave(wxCommandEvent& event)
{
    TextCtrl_file->SaveFile("canvas.config");
}

void TuziMineFrame::OnEditRestart(wxCommandEvent& event)
{
    m_canvas->CloseUp();
    m_canvas->ReStart();
}
