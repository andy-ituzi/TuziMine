#include "CMineLayer.h"
#include <cmath>
#include <iostream>

using namespace std;

CMineLayer::CMineLayer(wxSize clientSize)
    :CLayer(WIDTH_LAYER, HEIGHT_LAYER),
    m_logic(COLS, ROWS, NUM_MINE),
    m_col(0),
    m_row(0),
    m_clientSize(clientSize),
	m_bLeftPressed(false),
	m_bRightPressed(false),
	m_bMouseIn(false),
	m_flag(0),
	m_white(0)
{
    m_logic.PrintState();
    for (int i=0; i<8; i++)
    {
        m_number[i] = new CImageLayer(PATH_NUMBER[i], clientSize);
        m_number[i]->SetCurrentFrame(0, 0, 0, 0,
                                     100.0*CELL_SIZE/m_number[i]->GetWidth(),
                                     100.0*CELL_SIZE/m_number[i]->GetHeight(),
                                     0, 0, 100);
    }
    m_flag = new CImageLayer("./images/flag.png", clientSize);
    m_flag->SetCurrentFrame(0, 0, 0, 0,
                             100.0*CELL_SIZE/m_flag->GetWidth(),
                             100.0*CELL_SIZE/m_flag->GetHeight(),
                             0, 0, 100);
    m_white = new CImageLayer("./images/white.png", clientSize);
    m_white->SetCurrentFrame(0, 0, 0, 0,
                             100.0*CELL_SIZE/m_white->GetWidth(),
                             100.0*CELL_SIZE/m_white->GetHeight(),
                             0, 0, 100);
}

CMineLayer::~CMineLayer()
{
    for (int i=0; i<8; i++)
    {
        if (0 == m_number[i])
        {
            delete m_number[i];
            m_number[i] = 0;
        }
    }
    if (0 == m_flag)
    {
        delete m_flag;
        m_flag = 0;
    }
    if (0 == m_white)
    {
        delete m_white;
        m_white = 0;
    }

}

void CMineLayer::Update(void)
{
    if (true == m_logic.IsOver())
    {
        m_logic.ReStart();
    }
    else if (true == m_logic.IsWin())
    {
        m_logic.ReStart();
    }
}

void CMineLayer::Render(void)
{
    if (false == m_show)
    {
        return;
    }
    static double alpha = 0;
    if (true == m_bMouseIn)
    {
        if (alpha < 1.0)
        {
            alpha += 0.05;
        }
        else
        {
            alpha = 1.0;
        }
    }
    else
    {
        if (alpha > 0)
        {
            alpha -= 0.05;
        }
        else
        {
            alpha = 0;
        }
    }
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0, m_clientSize.x, 0, m_clientSize.y, 1, -1);

    glScalef(m_currentFrame.scale.x/100, m_currentFrame.scale.y/100, 1);
    glTranslatef(m_currentFrame.position.x / m_currentFrame.scale.x * 100 , m_currentFrame.position.y / m_currentFrame.scale.y * 100, 0);
    glRotatef(m_currentFrame.rotation.rotation_count * 360 + m_currentFrame.rotation.rotation_angle, 0, 0, 1);

    int state;
    int ox, oy;
    ox = m_currentFrame.position.x - m_currentFrame.anchorPoint.x;
    oy = m_currentFrame.position.y - m_currentFrame.anchorPoint.y;
    for (int i=0; i<ROWS; i++)
    {
        for (int j=0; j<COLS; j++)
        {
            state = m_logic.StateShowOf(j, i);
            switch (state)
            {
                case STATE_EMPTY:
                    m_white->SetCurrentFrameOpacity(alpha*100);
                    m_white->SetCurrentFramePosition(ox+j*CELL_SIZE, oy+(ROWS-i-1)*CELL_SIZE);
                    m_white->SetCurrentFrameRotation(m_currentFrame.rotation.rotation_count,
                                                     m_currentFrame.rotation.rotation_angle);
                    m_white->Render();
                    break;
                case STATE_1:
                case STATE_2:
                case STATE_3:
                case STATE_4:
                case STATE_5:
                case STATE_6:
                case STATE_7:
                case STATE_8:
                    m_white->SetCurrentFrameOpacity(alpha*100);
                    m_white->SetCurrentFramePosition(ox+j*CELL_SIZE, oy+(ROWS-i-1)*CELL_SIZE);
                    m_white->SetCurrentFrameRotation(m_currentFrame.rotation.rotation_count,
                                                     m_currentFrame.rotation.rotation_angle);
                    m_white->Render();
                    m_number[state-1]->SetCurrentFrameOpacity(alpha*100);
                    m_number[state-1]->SetCurrentFramePosition(ox+j*CELL_SIZE, oy+(ROWS-i-1)*CELL_SIZE);
                    m_number[state-1]->SetCurrentFrameRotation(m_currentFrame.rotation.rotation_count,
                                                     m_currentFrame.rotation.rotation_angle);
                    m_number[state-1]->Render();
                    break;
                case STATE_FLAG:
                    m_flag->SetCurrentFrameOpacity(alpha*100);
                    m_flag->SetCurrentFramePosition(ox+j*CELL_SIZE, oy+(ROWS-i-1)*CELL_SIZE);
                    m_flag->SetCurrentFrameRotation(m_currentFrame.rotation.rotation_count,
                                                     m_currentFrame.rotation.rotation_angle);
                    m_flag->Render();
                    break;
                default:
                break;
            }
        }
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
        glColor4f(1.f, 1.f, 1.f, alpha);
        glVertex2f(m_col*CELL_SIZE-m_currentFrame.anchorPoint.x,      (ROWS-m_row-1)*CELL_SIZE-m_currentFrame.anchorPoint.y);
        glVertex2f((m_col+1)*CELL_SIZE-m_currentFrame.anchorPoint.x,  (ROWS-m_row-1)*CELL_SIZE-m_currentFrame.anchorPoint.y);
        glVertex2f((m_col+1)*CELL_SIZE-m_currentFrame.anchorPoint.x,  (ROWS-m_row)*CELL_SIZE-m_currentFrame.anchorPoint.y);
        glVertex2f(m_col*CELL_SIZE-m_currentFrame.anchorPoint.x,      (ROWS-m_row)*CELL_SIZE-m_currentFrame.anchorPoint.y);
        glVertex2f(-m_currentFrame.anchorPoint.x, -m_currentFrame.anchorPoint.y);
        glVertex2f(m_currentFrame.anchorPoint.x, -m_currentFrame.anchorPoint.y);
        glVertex2f(m_currentFrame.anchorPoint.x, m_currentFrame.anchorPoint.y);
        glVertex2f(-m_currentFrame.anchorPoint.x, m_currentFrame.anchorPoint.y);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_BLEND);

    if (true == m_bLeftPressed && true == m_bRightPressed)
    {
        for (int i=-1; i<=1; i++)
        {
            for (int j=-1; j<=1; j++)
            {
                if (STATE_NEW != m_logic.StateShowOf(m_col+j, m_row+i))
                {
                    continue;
                }
                m_white->SetCurrentFrameOpacity(alpha*100);
                m_white->SetCurrentFramePosition(ox+(m_col+j)*CELL_SIZE, oy+(ROWS-i-1-m_row)*CELL_SIZE);
                m_white->SetCurrentFrameRotation(m_currentFrame.rotation.rotation_count,
                                                 m_currentFrame.rotation.rotation_angle);
                m_white->Render();
            }
        }
    }
    else if (true == m_bLeftPressed)
    {
        m_white->SetCurrentFrameOpacity(alpha*100);
        m_white->SetCurrentFramePosition(ox+m_col*CELL_SIZE, oy+(ROWS-m_row-1)*CELL_SIZE);
        m_white->SetCurrentFrameRotation(m_currentFrame.rotation.rotation_count,
                                         m_currentFrame.rotation.rotation_angle);
        m_white->Render();
    }

    glPopMatrix();
    glFlush();
}

void CMineLayer::OnLeftDown(wxMouseEvent& event)
{
    int col, row;
    int mx, my;
    event.GetPosition(&mx, &my);
    if (true == GetColAndRow(mx, my, col, row))
    {
        //cout << "(" << col << "," << row << ")" << endl;
        m_bLeftPressed = true;
    }
}

void CMineLayer::OnLeftUp(wxMouseEvent& event)
{
    int col, row;
    int mx, my;
    event.GetPosition(&mx, &my);
    if (true == GetColAndRow(mx, my, col, row))
    {
        cout << "(" << col << "," << row << ")" << endl;
        if (true == m_bRightPressed)
        {
            m_logic.OpenGridPlus(col, row);
            m_logic.PrintBoard();
        }
        else
        {
            m_logic.OpenGrid(col, row);
            m_logic.PrintBoard();
        }
        m_bLeftPressed = false;
    }
}

void CMineLayer::OnRightDown(wxMouseEvent& event)
{
    int col, row;
    int mx, my;
    event.GetPosition(&mx, &my);
    if (true == GetColAndRow(mx, my, col, row))
    {
        cout << "(" << col << "," << row << ")" << endl;
        m_bRightPressed = true;
        if (false == m_bLeftPressed)
        {
            m_logic.FlagGrid(col, row);
            m_logic.PrintBoard();
        }
    }
}

void CMineLayer::OnRightUp(wxMouseEvent& event)
{
    int col, row;
    int mx, my;
    event.GetPosition(&mx, &my);
    if (true == GetColAndRow(mx, my, col, row))
    {
        cout << "(" << col << "," << row << ")" << endl;
        if (true == m_bLeftPressed)
        {
            m_logic.OpenGridPlus(col, row);
            m_logic.PrintBoard();
        }
        m_bRightPressed = false;
    }
}
void CMineLayer::OnMove(wxMouseEvent& event)
{
    int col, row;
    int mx, my;
    event.GetPosition(&mx, &my);
    if (true == GetColAndRow(mx, my, col, row))
    {
        //cout << "(" << col << "," << row << ")" << endl;
        m_col = col;
        m_row = row;
        m_bMouseIn = true;
    }
    else
    {
        m_bMouseIn = false;
    }
}
bool CMineLayer::GetColAndRow(int mouse_client_x, int mouse_client_y, int& col, int& row)
{
    int x, y;
    mouse_client_y = m_clientSize.y - mouse_client_y;
    ConvertFromClientToLocal(mouse_client_x, mouse_client_y, x, y);
    if ((x>=0) && (x<COLS*CELL_SIZE) && (y>=0) && (y<ROWS*CELL_SIZE))
    {
        col = x / CELL_SIZE;
        row = ROWS - y / CELL_SIZE - 1;
        return true;
    }
    else
    {
        return false;
    }
}

void CMineLayer::SetShown(bool show)
{
    CLayer::SetShown(show);
    for(int i=0; i<8; i++)
    {
        m_number[i]->SetShown(show);
    }
    m_flag->SetShown(show);
    m_white->SetShown(show);
}
