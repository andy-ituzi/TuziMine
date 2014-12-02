#ifndef CCANVAS_H
#define CCANVAS_H

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <GL/glu.h>
#include "CImageLayer.h"
#include "CMineLayer.h"
#include "CAnimateLayer.h"

const int MAX_NUM_LAYER = 50;
const int MS_PER_FRAME = 1000/FRAME_PER_SEC;
const int LAYER_TYPE_IMG = 0;
const int LAYER_TYPE_SEQ = 1;
const int LAYER_TYPE_MINE = 2;

class CGLCanvas: public wxGLCanvas, wxGLContext
{
public:
    CGLCanvas(wxWindow *parent, int *attribList, wxSize clientSize);
    virtual ~CGLCanvas();

    //void Initialize(void);
    void Update(void);
    void Render(void);
    void CloseUp(void);
    void ReStart(void);
    bool LoadConfig(void);

private:

    int intOf(const char* str);
    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnRightDown(wxMouseEvent& event);
    void OnRightUp(wxMouseEvent& event);
    void OnMove(wxMouseEvent& event);
    void OnTimer(wxTimerEvent& event);

    bool AtTime(int sec, int frame)
    {
        return (m_frameCount == sec * FRAME_PER_SEC + frame);
    }

    bool AtTime(int frame)
    {
        return (m_frameCount == frame);
    }
    void AddLayer(int type, const char* name, const char* path = 0, int seq_total = 0);
    CLayer* GetLayer(const char* name);

private:
    static const int TIMER_ID;
    wxDECLARE_EVENT_TABLE();

    wxTimer m_timer;
    wxSize m_clientSize;

    CLayer *m_layer[MAX_NUM_LAYER];
    char m_layerName[MAX_NUM_LAYER][256];
    int m_totalLayer;

    int m_frameCount;
    int m_frame_mine_over;
};

#endif // CCANVAS_H

