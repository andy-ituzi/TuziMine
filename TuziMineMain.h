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

#include "CCanvas.h"

//(*Headers(TuziMineFrame)
#include <wx/menu.h>
#include <wx/frame.h>
//*)

const wxSize CLIENT_SIZE = wxSize(600, 600);

class TuziMineFrame: public wxFrame
{
public:

    TuziMineFrame(wxWindow* parent,wxWindowID id = -1);
    virtual ~TuziMineFrame();

private:

    //(*Handlers(TuziMineFrame)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    //*)

    //(*Identifiers(TuziMineFrame)
    static const long ID_MENUITEM1;
    static const long idMenuAbout;
    //*)

    //(*Declarations(TuziMineFrame)
    //*)

    DECLARE_EVENT_TABLE()

    CGLCanvas *m_canvas;
};

#endif // TUZIMINEMAIN_H
