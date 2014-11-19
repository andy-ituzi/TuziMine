#include "CCanvas.h"
#include <iostream>
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
                 wxDefaultPosition, wxDefaultSize,
                 wxFULL_REPAINT_ON_RESIZE),
    wxGLContext(this),
    m_timer(this, TIMER_ID),
    m_clientSize(clientSize),
    m_img_background(0),
    m_img_frame(0),
    m_img_flower(0),
    m_img_pink_heart(0),
    m_img_pink_heart_2(0),
    m_img_white_heart(0),
    m_img_white_heart_2(0),
    m_mine(0)

{
    wxGLContext::SetCurrent(*this);
    m_img_background = new CImageLayer("./images/background.png", m_clientSize);
    m_img_frame = new CImageLayer("./images/frame.png", m_clientSize);
    m_img_photo = new CImageLayer("./images/photo.png", m_clientSize);
    m_img_flower = new CImageLayer("./images/flower.png", m_clientSize);
    m_img_pink_heart = new CImageLayer("./images/pink_heart.png", m_clientSize);
    m_img_pink_heart_2 = new CImageLayer("./images/pink_heart_2.png", m_clientSize);
    m_img_white_heart = new CImageLayer("./images/white_heart.png", m_clientSize);
    m_img_white_heart_2 = new CImageLayer("./images/white_heart_2.png", m_clientSize);
    m_mine = new CMineLayer(m_clientSize);
    m_timer.Start(30);
    Initialize();
}

CGLCanvas::~CGLCanvas()
{
    if (0 != m_img_background)
    {
        delete m_img_background;
        m_img_background = 0;
    }
    if (0 != m_img_frame)
    {
        delete m_img_frame;
        m_img_frame = 0;
    }
    if (0 != m_img_photo)
    {
        delete m_img_photo;
        m_img_photo = 0;
    }
    if (0 != m_img_flower)
    {
        delete m_img_flower;
        m_img_flower = 0;
    }
    if (0 != m_img_pink_heart)
    {
        delete m_img_pink_heart;
        m_img_pink_heart = 0;
    }
    if (0 != m_img_pink_heart_2)
    {
        delete m_img_pink_heart_2;
        m_img_pink_heart_2 = 0;
    }
    if (0 != m_img_white_heart)
    {
        delete m_img_white_heart;
        m_img_white_heart = 0;
    }
    if (0 != m_img_white_heart_2)
    {
        delete m_img_pink_heart_2;
        m_img_white_heart_2 = 0;
    }
    if (0 != m_mine)
    {
        delete m_mine;
        m_mine = 0;
    }
}


void CGLCanvas::Initialize(void)
{
    m_img_background->SetFirstFrame((double)m_img_background->GetWidth()/2, (double)m_img_background->GetHeight()/2,
                        (double)m_clientSize.x/2, (double)m_clientSize.y/2, 100, 100, 0, 0, 100);

    m_img_frame->SetFirstFrame((double)m_img_frame->GetWidth()/2, (double)m_img_frame->GetHeight()/2,
                        (double)m_clientSize.x/2, (double)m_clientSize.y/2, 100, 100, 0, 0, 100);

    m_img_photo->SetFirstFrame((double)m_img_photo->GetWidth()/2, (double)m_img_photo->GetHeight()/2,
                        (double)m_clientSize.x/2-55, (double)m_clientSize.y/2+60, 100, 100, 0, 0, 100);

    m_img_flower->SetFirstFrame((double)m_img_flower->GetWidth()/2, (double)m_img_flower->GetHeight()/2,
                        (double)m_clientSize.x/2+133, (double)m_clientSize.y/2+150, 100, 100, 0, 0, 100);

    m_img_pink_heart->SetFirstFrame((double)m_img_pink_heart->GetWidth()/2, (double)m_img_pink_heart->GetHeight()/2,
                        (double)m_clientSize.x/2-230, (double)m_clientSize.y/2-100, 100, 100, 0, 0, 100);

    m_img_pink_heart_2->SetFirstFrame((double)m_img_pink_heart_2->GetWidth()/2, (double)m_img_pink_heart_2->GetHeight()/2,
                        (double)m_clientSize.x/2+117, (double)m_clientSize.y/2+210, 100, 100, 0, 0, 100);

    m_img_white_heart->SetFirstFrame((double)m_img_white_heart->GetWidth()/2, (double)m_img_white_heart->GetHeight()/2,
                        (double)m_clientSize.x/2-140, (double)m_clientSize.y/2+135, 100, 100, 0, 0, 100);

    m_img_white_heart_2->SetFirstFrame((double)m_img_white_heart_2->GetWidth()/2, (double)m_img_white_heart_2->GetHeight()/2,
                        (double)m_clientSize.x/2-200, (double)m_clientSize.y/2+210, 100, 100, 0, 0, 100);

    m_mine->SetFirstFrame((double)m_mine->GetWidth()/2, (double)m_mine->GetHeight()/2,
                        (double)m_clientSize.x/2 - 52, (double)m_clientSize.y/2 + 80, 100, 100, 0, 0, 100);

    m_img_flower->AddKeyFrame(TYPE_OPACITY, 15, 100);
    m_img_flower->AddKeyFrame(TYPE_OPACITY, 150, 0);

    m_img_pink_heart->AddKeyFrame(TYPE_OPACITY, 15, 100);
    m_img_pink_heart->AddKeyFrame(TYPE_OPACITY, 150, 0);

    m_img_pink_heart_2->AddKeyFrame(TYPE_OPACITY, 15, 100);
    m_img_pink_heart_2->AddKeyFrame(TYPE_OPACITY, 150, 0);

    m_img_white_heart->AddKeyFrame(TYPE_OPACITY, 15, 100);
    m_img_white_heart->AddKeyFrame(TYPE_OPACITY, 150, 0);

    m_img_white_heart_2->AddKeyFrame(TYPE_OPACITY, 15, 100);
    m_img_white_heart_2->AddKeyFrame(TYPE_OPACITY, 150, 0);

    m_img_photo->AddKeyFrame(TYPE_OPACITY, 15, 100);
    m_img_photo->AddKeyFrame(TYPE_OPACITY, 150, 0);

    m_img_frame->AddKeyFrame(TYPE_OPACITY, 100, 100);
    m_img_frame->AddKeyFrame(TYPE_OPACITY, 200, 0);
}

void CGLCanvas::Update(void)
{
    m_img_background->Update();
    m_img_frame->Update();
    m_img_photo->Update();
    m_img_flower->Update();
    m_img_pink_heart->Update();
    m_img_pink_heart_2->Update();
    m_img_white_heart->Update();
    m_img_white_heart_2->Update();
    m_mine->Update();
}

void CGLCanvas::Render(void)
{
    glViewport(0, 0, m_clientSize.x, m_clientSize.y);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_img_background->Render();
    m_img_photo->Render();
    m_img_frame->Render();
    m_img_flower->Render();
    m_img_pink_heart->Render();
    m_img_pink_heart_2->Render();
    m_img_white_heart->Render();
    m_img_white_heart_2->Render();
    m_mine->Render();

    SwapBuffers();
}

void CGLCanvas::OnLeftDown(wxMouseEvent& event)
{
    m_mine->OnLeftDown(event);
}

void CGLCanvas::OnLeftUp(wxMouseEvent& event)
{
    m_mine->OnLeftUp(event);
}

void CGLCanvas::OnRightDown(wxMouseEvent& event)
{
    m_mine->OnRightDown(event);
}

void CGLCanvas::OnRightUp(wxMouseEvent& event)
{
    m_mine->OnRightUp(event);
}

void CGLCanvas::OnMove(wxMouseEvent& event)
{
    m_mine->OnMove(event);
}

void CGLCanvas::OnTimer(wxTimerEvent& event)
{
    Update();
    Render();
}


