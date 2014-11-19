#ifndef CCANVAS_H
#define CCANVAS_H

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <GL/glu.h>
#include "CImageLayer.h"
#include "CMineLayer.h"


class CGLCanvas: public wxGLCanvas, wxGLContext
{
public:
    CGLCanvas(wxWindow *parent, int *attribList, wxSize clientSize);
    virtual ~CGLCanvas();

    void Initialize(void);
    void Update(void);
    void Render(void);

private:
    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnRightDown(wxMouseEvent& event);
    void OnRightUp(wxMouseEvent& event);
    void OnMove(wxMouseEvent& event);
    void OnTimer(wxTimerEvent& event);

private:
    static const int TIMER_ID;
    wxDECLARE_EVENT_TABLE();

    wxTimer m_timer;
    wxSize m_clientSize;

    CImageLayer *m_img_background;
    CImageLayer *m_img_frame;
    CImageLayer *m_img_photo;
    CImageLayer *m_img_flower;
    CImageLayer *m_img_pink_heart;
    CImageLayer *m_img_pink_heart_2;
    CImageLayer *m_img_white_heart;
    CImageLayer *m_img_white_heart_2;

    CMineLayer *m_mine;
};

#endif // CCANVAS_H

