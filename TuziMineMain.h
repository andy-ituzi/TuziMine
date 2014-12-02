/***************************************************************
 * Name:      TuziMineMain.h
 * Purpose:   Defines Application Frame
 * Author:    AndyLin (andy_lin@live.cn)
 * Created:   2014-11-18
 * Copyright: AndyLin (@@@)
 * License:
 **************************************************************/

#ifndef TUZIMINEMAIN_H
#define TUZIMINEMAIN_H


//(*Headers(TuziMineFrame)
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/frame.h>
//*)
#include "CCanvas.h"

const wxSize CLIENT_SIZE = wxSize(600, 600);
const bool EDIT_MODE = true;

class TuziMineFrame: public wxFrame
{
public:

    TuziMineFrame(wxWindow* parent,wxWindowID id = -1);
    virtual ~TuziMineFrame();

private:

    //(*Handlers(TuziMineFrame)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnEditLoad(wxCommandEvent& event);
    void OnEditSave(wxCommandEvent& event);
    void OnEditRestart(wxCommandEvent& event);
    //*)

    //(*Identifiers(TuziMineFrame)
    static const long ID_TEXTCTRL1;
    static const long ID_PANEL1;
    static const long ID_PANEL2;
    static const long ID_QUIT;
    static const long ID_EDIT_LOAD;
    static const long ID_EDIT_SAVE;
    static const long ID_EDIT_RESTART;
    //*)

    //(*Declarations(TuziMineFrame)
    wxTextCtrl* TextCtrl_file;
    wxPanel* Panel_canvas;
    wxPanel* Panel_edit;
    //*)

    CGLCanvas* m_canvas;

    DECLARE_EVENT_TABLE()
};

#endif // TUZIMINEMAIN_H
