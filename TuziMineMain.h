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
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

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
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(TuziMineFrame)
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // TUZIMINEMAIN_H
