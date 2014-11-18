/***************************************************************
 * Name:      TuziMineApp.cpp
 * Purpose:   Code for Application Class
 * Author:    AndyLin (andy_lin@live.cn)
 * Created:   2014-11-18
 * Copyright: AndyLin (@@@)
 * License:
 **************************************************************/

#include "TuziMineApp.h"

//(*AppHeaders
#include "TuziMineMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(TuziMineApp);

bool TuziMineApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	TuziMineFrame* Frame = new TuziMineFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
