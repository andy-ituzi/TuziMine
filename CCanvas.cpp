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
    m_img_letter(0),
    m_mine(0),
    m_seq_pink_heart(0),
    m_seq_number(0),
    m_frameCount(0),
    m_frame_mine_over(-1000)
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
    m_img_letter = new CImageLayer("./images/letter.png", m_clientSize);
    m_mine = new CMineLayer(m_clientSize);
    m_seq_pink_heart = new CAnimateLayer("./images/pink_heart/pink_heart", 15, m_clientSize);
    m_seq_number = new CAnimateLayer("./images/numbers/number", 4, m_clientSize);
    m_timer.Start(MS_PER_FRAME);
    Initialize();
}

void CGLCanvas::Initialize(void)
{
    m_img_background->SetFirstFrame((double)m_img_background->GetWidth()/2, (double)m_img_background->GetHeight()/2,
                        (double)m_clientSize.x/2, (double)m_clientSize.y/2, 100, 100, 0, 0, 100);
    m_img_background->SetShown(true);

    m_img_frame->SetFirstFrame((double)m_img_frame->GetWidth()/2, (double)m_img_frame->GetHeight()/2,
                        (double)m_clientSize.x/2, (double)m_clientSize.y/2, 100, 100, 0, 0, 100);
    m_img_frame->AddKeyFrame(TYPE_OPACITY, 0, 0);
    m_img_frame->AddKeyFrame(TYPE_POSITION, 0, 400, 400);
    m_img_frame->AddKeyFrame(TYPE_SCALE, 0, 20, 20);
    m_img_frame->AddKeyFrame(TYPE_ROTATION, 0, 0, 0);
    m_img_frame->AddKeyFrame(TYPE_ROTATION, 10, 4, 0);
    m_img_frame->AddKeyFrame(TYPE_POSITION, 10, 300, 300);
    m_img_frame->AddKeyFrame(TYPE_SCALE, 20, 80, 80);
    m_img_frame->AddKeyFrame(TYPE_OPACITY, 30, 100);
    m_img_frame->AddKeyFrame(TYPE_SCALE, 30, 100, 100);

    m_img_photo->SetFirstFrame((double)m_img_photo->GetWidth()/2+55, (double)m_img_photo->GetHeight()/2-60,
                        (double)m_clientSize.x/2, (double)m_clientSize.y/2, 100, 100, 0, 0, 100);
    m_img_photo->AddKeyFrame(TYPE_OPACITY, 0, 0);
    m_img_photo->AddKeyFrame(TYPE_POSITION, 0, 400, 400);
    m_img_photo->AddKeyFrame(TYPE_SCALE, 0, 20, 20);
    m_img_photo->AddKeyFrame(TYPE_ROTATION, 0, 0, 0);
    m_img_photo->AddKeyFrame(TYPE_ROTATION, 10, 4, 0);
    m_img_photo->AddKeyFrame(TYPE_POSITION, 10, 300, 300);
    m_img_photo->AddKeyFrame(TYPE_SCALE, 20, 80, 80);
    m_img_photo->AddKeyFrame(TYPE_OPACITY, 30, 100);
    m_img_photo->AddKeyFrame(TYPE_SCALE, 30, 100, 100);

    m_img_photo->AddKeyFrame(TYPE_OPACITY, 100, 100);
    m_img_photo->AddKeyFrame(TYPE_OPACITY, 130, 0);

    m_img_letter->SetFirstFrame((double)m_img_letter->GetWidth()/2+55, (double)m_img_letter->GetHeight()/2-65,
                        (double)m_clientSize.x/2, (double)m_clientSize.y/2, 90, 100, 0, 0, 100);
    m_img_letter->AddKeyFrame(TYPE_OPACITY, 0, 0);
    m_img_letter->AddKeyFrame(TYPE_OPACITY, 30, 100);

    m_img_flower->SetFirstFrame((double)m_img_flower->GetWidth()/2, (double)m_img_flower->GetHeight()/2,
                        (double)m_clientSize.x/2+133, (double)m_clientSize.y/2+150, 100, 100, 0, 0, 100);
    m_img_flower->AddKeyFrame(TYPE_OPACITY, 0, 0);
    m_img_flower->AddKeyFrame(TYPE_OPACITY, 15, 100);

    m_img_pink_heart->SetFirstFrame((double)m_img_pink_heart->GetWidth()/2, (double)m_img_pink_heart->GetHeight()/2,
                        (double)m_clientSize.x/2-230, (double)m_clientSize.y/2-100, 100, 100, 0, 0, 100);
    m_img_pink_heart->AddKeyFrame(TYPE_OPACITY, 0, 0);
    m_img_pink_heart->AddKeyFrame(TYPE_OPACITY, 15, 100);

    m_img_pink_heart_2->SetFirstFrame((double)m_img_pink_heart_2->GetWidth()/2, (double)m_img_pink_heart_2->GetHeight()/2,
                        (double)m_clientSize.x/2+117, (double)m_clientSize.y/2+210, 100, 100, 0, 0, 100);
    m_img_pink_heart_2->AddKeyFrame(TYPE_OPACITY, 0, 0);
    m_img_pink_heart_2->AddKeyFrame(TYPE_OPACITY, 15, 100);

    m_img_white_heart->SetFirstFrame((double)m_img_white_heart->GetWidth()/2, (double)m_img_white_heart->GetHeight()/2,
                        (double)m_clientSize.x/2-140, (double)m_clientSize.y/2+135, 100, 100, 0, 0, 100);
    m_img_white_heart->AddKeyFrame(TYPE_OPACITY, 0, 0);
    m_img_white_heart->AddKeyFrame(TYPE_OPACITY, 15, 100);

    m_img_white_heart_2->SetFirstFrame((double)m_img_white_heart_2->GetWidth()/2, (double)m_img_white_heart_2->GetHeight()/2,
                        (double)m_clientSize.x/2-200, (double)m_clientSize.y/2+210, 100, 100, 0, 0, 100);
    m_img_white_heart_2->AddKeyFrame(TYPE_OPACITY, 0, 0);
    m_img_white_heart_2->AddKeyFrame(TYPE_OPACITY, 15, 100);

    m_mine->SetFirstFrame((double)m_mine->GetWidth()/2, (double)m_mine->GetHeight()/2,
                        (double)m_clientSize.x/2 - 52, (double)m_clientSize.y/2 + 80, 100, 100, 0, 0, 100);
    m_mine->AddKeyFrame(TYPE_OPACITY, 0, 100);
    m_mine->AddKeyFrame(TYPE_OPACITY, 15, 0);
    m_mine->SetShown(false);

    m_seq_pink_heart->SetFirstFrame((double)m_seq_pink_heart->GetWidth()/2, (double)m_seq_pink_heart->GetHeight()/2,
                        500, 500, 100, 100, 0, 0, 100);
    m_seq_pink_heart->SetShown(true);

    //original static condition
    m_seq_number->SetFirstFrame((double)m_seq_number->GetWidth()/2, (double)m_seq_number->GetHeight()/2,
                        300, 300, 100, 100, 0, 0, 100);
    //key frame condition
    m_seq_number->AddKeyFrame(TYPE_OPACITY, 0, 50);
    m_seq_number->AddKeyFrame(TYPE_OPACITY, 4, 100);
    m_seq_number->AddKeyFrame(TYPE_OPACITY, 15, 0);
    //set animation attributes
    m_seq_number->SetFramesPerImage(15);
    //do it
    m_seq_number->RepeatBetween(0, 14);
    m_seq_number->SetShown(true);
}

void CGLCanvas::Update(void)
{
    m_frameCount++;
    if ( AtTime(4, 0) )
    {
        m_seq_number->SetShown(false);
        m_img_flower->StartAndEndAt(0, 15);
        m_img_flower->SetShown(true);
    }
    if ( AtTime(4, 6) )
    {
        m_img_pink_heart->StartAndEndAt(0, 15);
        m_img_pink_heart->SetShown(true);
    }
    if ( AtTime(4, 9) )
    {
        m_img_pink_heart_2->StartAndEndAt(0, 15);
        m_img_pink_heart_2->SetShown(true);
        m_img_frame->StartAndEndAt(0, 30);
        m_img_frame->SetShown(true);
        m_img_photo->StartAndEndAt(0, 30);
        m_img_photo->SetShown(true);
    }
    if ( AtTime(7, 12) )
    {
        m_img_white_heart->StartAndEndAt(0, 15);
        m_img_white_heart->SetShown(true);
    }
    if ( AtTime(5, 5) )
    {
        m_img_white_heart_2->StartAndEndAt(0, 15);
        m_img_white_heart_2->SetShown(true);
    }
    if ( AtTime(7, 0) )
    {
        m_mine->SetActive(true);
        m_mine->SetShown(true);
    }

    if ( m_mine->HasWon() && m_frame_mine_over < 0)
    {
        m_frame_mine_over = m_frameCount;
        m_mine->StartAndEndAt(0, 15);
        m_img_photo->StartAndEndAt(100, 130);
    }
    if ( AtTime(m_frame_mine_over+30) )
    {
        m_img_letter->StartAndEndAt(0, 30);
        m_img_letter->SetShown(true);
        m_mine->SetActive(false);
        m_mine->SetMineRestart();
        m_mine->SetShown(false);
        m_img_photo->SetShown(false);
        m_frame_mine_over = -1000;
    }

    m_img_background->Update();
    m_img_frame->Update();
    m_img_photo->Update();
    m_img_letter->Update();
    m_img_flower->Update();
    m_img_pink_heart->Update();
    m_img_pink_heart_2->Update();
    m_img_white_heart->Update();
    m_img_white_heart_2->Update();
    m_mine->Update();
    m_seq_pink_heart->Update();
    m_seq_number->Update();
}

void CGLCanvas::Render(void)
{
    glViewport(0, 0, m_clientSize.x, m_clientSize.y);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_img_background->Render();
    m_img_photo->Render();
    m_img_letter->Render();
    m_img_frame->Render();
    m_img_flower->Render();
    m_img_pink_heart->Render();
    m_img_pink_heart_2->Render();
    m_img_white_heart->Render();
    m_img_white_heart_2->Render();
    m_mine->Render();
    m_seq_pink_heart->Render();
    m_seq_number->Render();

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
    if (0 != m_img_letter)
    {
        delete m_img_letter;
        m_img_letter = 0;
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
    if (0 != m_seq_pink_heart)
    {
        delete m_seq_pink_heart;
        m_seq_pink_heart = 0;
    }
    if (0 != m_seq_number)
    {
        delete m_seq_number;
        m_seq_number = 0;
    }
}
