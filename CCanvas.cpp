#include "CCanvas.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;


const int CGLCanvas::TIMER_ID = wxID_HIGHEST + 1;

BEGIN_EVENT_TABLE(CGLCanvas, wxGLCanvas)
    EVT_LEFT_DOWN(CGLCanvas::OnLeftDown)
    EVT_LEFT_UP(CGLCanvas::OnLeftUp)
    EVT_RIGHT_DOWN(CGLCanvas::OnRightDown)
    EVT_RIGHT_UP(CGLCanvas::OnRightUp)
    EVT_MOTION(CGLCanvas::OnMove)
    EVT_TIMER(TIMER_ID, CGLCanvas::OnTimer)
END_EVENT_TABLE()

CGLCanvas::CGLCanvas(wxWindow *parent, int *attribList, wxSize clientSize)
    : wxGLCanvas(parent, wxID_ANY, attribList,
                 wxPoint(0, 0), clientSize,
                 wxFULL_REPAINT_ON_RESIZE),
    wxGLContext(this),
    m_timer(this, TIMER_ID),
    m_clientSize(clientSize),
    m_totalLayer(0),
    m_frameCount(0),
    m_frame_mine_over(-1000)
{
    for (int i=0; i<MAX_NUM_LAYER; i++)
    {
        m_layer[i] = 0;
    }
    wxGLContext::SetCurrent(*this);
    m_timer.Start(MS_PER_FRAME);
    LoadConfig();
}

void CGLCanvas::Update(void)
{
    for (int i=0; i<m_totalLayer; i++)
    {
        if (0 != m_layer[i])
        {
            m_layer[i]->Update();
        }
    }
}

void CGLCanvas::Render(void)
{
    glViewport(0, 0, m_clientSize.x, m_clientSize.y);
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i=0; i<m_totalLayer; i++)
    {
        if (0 != m_layer[i])
        {
            m_layer[i]->Render();
        }
    }

    SwapBuffers();
}

void CGLCanvas::OnLeftDown(wxMouseEvent& event)
{
    CMineLayer* layer_mine = (CMineLayer*)GetLayer("mine");
    if (0 != layer_mine)
    {
        layer_mine->OnLeftDown(event);
    }
}

void CGLCanvas::OnLeftUp(wxMouseEvent& event)
{
    CMineLayer* layer_mine = (CMineLayer*)GetLayer("mine");
    if (0 != layer_mine)
    {
        layer_mine->OnLeftUp(event);
    }
}

void CGLCanvas::OnRightDown(wxMouseEvent& event)
{
    CMineLayer* layer_mine = (CMineLayer*)GetLayer("mine");
    if (0 != layer_mine)
    {
        layer_mine->OnRightDown(event);
    }
}

void CGLCanvas::OnRightUp(wxMouseEvent& event)
{
    CMineLayer* layer_mine = (CMineLayer*)GetLayer("mine");
    if (0 != layer_mine)
    {
        layer_mine->OnRightUp(event);
    }
}

void CGLCanvas::OnMove(wxMouseEvent& event)
{
    CMineLayer* layer_mine = (CMineLayer*)GetLayer("mine");
    if (0 != layer_mine)
    {
        layer_mine->OnMove(event);
    }
}

void CGLCanvas::OnTimer(wxTimerEvent& event)
{
    Update();
    Render();
}

CGLCanvas::~CGLCanvas()
{
    CloseUp();
}

void CGLCanvas::AddLayer(int type, const char* name, const char* path, int seq_total)
{
    if (0 == name)
    {
        return;
    }
    if (LAYER_TYPE_IMG == type)
    {
        m_layer[m_totalLayer] = new CImageLayer(path, m_clientSize);
    }
    else if (LAYER_TYPE_MINE == type)
    {
        m_layer[m_totalLayer] = new CMineLayer(m_clientSize);
    }
    else
    {
        m_layer[m_totalLayer] = new CAnimateLayer(path, seq_total, m_clientSize);
    }
    strcpy(m_layerName[m_totalLayer], name);
    m_totalLayer++;
}

CLayer* CGLCanvas::GetLayer(const char* name)
{
    if (0 == name)
    {
        return 0;
    }
    for (int i=0; i<m_totalLayer; i++)
    {
        if (0 == strcmp(m_layerName[i], name))
        {
            return m_layer[i];
        }
    }
    return 0;
}

void CGLCanvas::CloseUp(void)
{
    for (int i=0; i<m_totalLayer; i++)
    {
        if (0 != m_layer[i])
        {
            delete m_layer[i];
            m_layer[i] = 0;
        }
    }
    m_timer.Stop();
}

void CGLCanvas::ReStart(void)
{
    m_timer.Start(MS_PER_FRAME);
    m_totalLayer = 0;
    m_frameCount = 0;
    m_frame_mine_over = -1000;
    LoadConfig();
}

bool CGLCanvas::LoadConfig(void)
{
    ifstream fin("./canvas.config");
    if (false == fin.is_open())
    {
        cout << ".config is opened..." << endl;
        return false;
    }
    int type;
    char name[256];
    char path[256];
    int seq_total;
    fin >> type;
    while (-1 != type)
    {
        fin >> name >> path >> seq_total;
        AddLayer(type, name, path, seq_total);
        cout << name << " is loaded..." << endl;
        fin >> type;
    }

    int fc;
    double ox, oy, px, py, sx, sy, rc, ra, op;
    CLayer *layer;

    fin >> name;
    cout << name << "..." << endl;
    while (0 != strcmp(name, "END"))
    {
        layer = GetLayer(name);
        if (0 == layer)
        {
            break;
        }
        fin >> fc;
        while (-1 != fc)
        {
            fin >> ox >> oy >> px >> py >> sx >> sy >> rc >> ra >> op;
            layer->AddKeyFrame(fc, ox, oy, px, py, sx, sy, rc, ra, op);
            cout << fc << " is added.." << endl;
            fin >> fc;
        }
        fin >> name;
        cout << name << "..." << endl;
    }
    int from, to;
    CImageLayer* img_layer;
    CAnimateLayer* seq_layer;
    fin >> name;
    while (0 != strcmp(name, "END"))
    {
        fin >> type >> from >> to;
        if (LAYER_TYPE_IMG == type)
        {
            img_layer = (CImageLayer*)GetLayer(name);
            img_layer->RepeatBetween(from, to);
            img_layer->SetShown(true);
        }
        else if (LAYER_TYPE_SEQ == type)
        {
            seq_layer = (CAnimateLayer*)GetLayer(name);
            seq_layer->SetFramesPerImage(15);
            seq_layer->RepeatBetween(from, to);
            seq_layer->SetShown(true);
        }
        fin >> name;
        cout << name << "..." << endl;
    }
    fin.close();
    return true;
}
//
//int CGLCanvas::intOf(const char* c)
//{
//    int value = 0;
//    int sign = 1;
//    if( *c == '+' || *c == '-' ) {
//        if( *c == '-' )
//            sign = -1;
//        c++;
//    }
//    while ( isdigit( *c ) ) {
//        value *= 10;
//        value += (int) (*c-'0');
//        c++;
//    }
//    return value * sign;
//}
