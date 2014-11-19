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
	m_flag(0),
	m_white(0)
{
    m_logic.PrintState();
    for (int i=0; i<8; i++)
    {
        m_number[i] = new CImageLayer(PATH_NUMBER[i], m_clientSize);
    }
    m_flag = new CImageLayer("./images/flag.png", m_clientSize);
    m_white = new CImageLayer("./images/white.png", m_clientSize);
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
bool CMineLayer::Initialize(void)
{
    return true;
}

void CMineLayer::Update(void)
{

}

void CMineLayer::Render(void)
{
    glViewport(0, 0, m_clientSize.x, m_clientSize.y);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0, m_clientSize.x, 0, m_clientSize.y, 1, -1);

    glScalef(m_currentFrame.scale.x/100, m_currentFrame.scale.y/100, 1);
    glTranslatef(m_currentFrame.position.x / m_currentFrame.scale.x * 100 , m_currentFrame.position.y / m_currentFrame.scale.y * 100, 0);
    glRotatef(m_currentFrame.rotation.rotation_count * 360 + m_currentFrame.rotation.rotation_angle, 0, 0, 1);

    float alpha = 0.5;
    int state;
    TEXTURE texture;
    for (int i=0; i<ROWS; i++)
    {
        for (int j=0; j<COLS; j++)
        {
            state = m_logic.StateShowOf(j, i);
            switch (state)
            {
                case STATE_EMPTY:
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    m_white->GetTexture(texture);
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, texture.texture);
                    glBegin(GL_QUADS);
                        glColor4f(1.f, 1.f, 1.f, alpha+0.3);
                        glTexCoord2f(0, 1.f);
                            glVertex2f(j*CELL_SIZE-m_currentFrame.anchorPoint.x,      (ROWS-i-1)*CELL_SIZE-m_currentFrame.anchorPoint.y);
                        glTexCoord2f(1.f, 1.f);
                            glVertex2f((j+1)*CELL_SIZE-m_currentFrame.anchorPoint.x,  (ROWS-i-1)*CELL_SIZE-m_currentFrame.anchorPoint.y);
                        glTexCoord2f(1.f, 0.f);
                            glVertex2f((j+1)*CELL_SIZE-m_currentFrame.anchorPoint.x,  (ROWS-i)*CELL_SIZE-m_currentFrame.anchorPoint.y);
                        glTexCoord2f(0, 0.f);
                            glVertex2f(j*CELL_SIZE-m_currentFrame.anchorPoint.x,      (ROWS-i)*CELL_SIZE-m_currentFrame.anchorPoint.y);
                    glEnd();
                    glDisable(GL_TEXTURE_2D);
                    break;
                case STATE_1:
                case STATE_2:
                case STATE_3:
                case STATE_4:
                case STATE_5:
                case STATE_6:
                case STATE_7:
                case STATE_8:
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    m_white->GetTexture(texture);
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, texture.texture);
                    glBegin(GL_QUADS);
                        glColor4f(1.f, 1.f, 1.f, alpha+0.3);
                        glTexCoord2f(0, 1.f);
                            glVertex2f(j*CELL_SIZE-m_currentFrame.anchorPoint.x,      (ROWS-i-1)*CELL_SIZE-m_currentFrame.anchorPoint.y);
                        glTexCoord2f(1.f, 1.f);
                            glVertex2f((j+1)*CELL_SIZE-m_currentFrame.anchorPoint.x,  (ROWS-i-1)*CELL_SIZE-m_currentFrame.anchorPoint.y);
                        glTexCoord2f(1.f, 0.f);
                            glVertex2f((j+1)*CELL_SIZE-m_currentFrame.anchorPoint.x,  (ROWS-i)*CELL_SIZE-m_currentFrame.anchorPoint.y);
                        glTexCoord2f(0, 0.f);
                            glVertex2f(j*CELL_SIZE-m_currentFrame.anchorPoint.x,      (ROWS-i)*CELL_SIZE-m_currentFrame.anchorPoint.y);
                    glEnd();
                    glDisable(GL_TEXTURE_2D);
                    m_number[state-1]->GetTexture(texture);
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, texture.texture);
                    glBegin(GL_QUADS);
                        glColor4f(1.f, 1.f, 1.f, alpha);
                        glTexCoord2f(0, 1.f);
                            glVertex2f(j*CELL_SIZE-m_currentFrame.anchorPoint.x,      (ROWS-i-1)*CELL_SIZE-m_currentFrame.anchorPoint.y);
                        glTexCoord2f(1.f, 1.f);
                            glVertex2f((j+1)*CELL_SIZE-m_currentFrame.anchorPoint.x,  (ROWS-i-1)*CELL_SIZE-m_currentFrame.anchorPoint.y);
                        glTexCoord2f(1.f, 0.f);
                            glVertex2f((j+1)*CELL_SIZE-m_currentFrame.anchorPoint.x,  (ROWS-i)*CELL_SIZE-m_currentFrame.anchorPoint.y);
                        glTexCoord2f(0, 0.f);
                            glVertex2f(j*CELL_SIZE-m_currentFrame.anchorPoint.x,      (ROWS-i)*CELL_SIZE-m_currentFrame.anchorPoint.y);
                    glEnd();
                    glDisable(GL_TEXTURE_2D);
                    glDisable(GL_BLEND);
                    break;
//                case STATE_NEW: cout << "N";    break;
//                case STATE_MINE:cout << "9";    break;
                case STATE_FLAG:
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    m_flag->GetTexture(texture);
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, texture.texture);
                    glBegin(GL_QUADS);
                        glColor4f(1.f, 1.f, 1.f, alpha);
                        glTexCoord2f(0, 1.f);
                            glVertex2f(j*CELL_SIZE-m_currentFrame.anchorPoint.x,      (ROWS-i-1)*CELL_SIZE-m_currentFrame.anchorPoint.y);
                        glTexCoord2f(1.f, 1.f);
                            glVertex2f((j+1)*CELL_SIZE-m_currentFrame.anchorPoint.x,  (ROWS-i-1)*CELL_SIZE-m_currentFrame.anchorPoint.y);
                        glTexCoord2f(1.f, 0.f);
                            glVertex2f((j+1)*CELL_SIZE-m_currentFrame.anchorPoint.x,  (ROWS-i)*CELL_SIZE-m_currentFrame.anchorPoint.y);
                        glTexCoord2f(0, 0.f);
                            glVertex2f(j*CELL_SIZE-m_currentFrame.anchorPoint.x,      (ROWS-i)*CELL_SIZE-m_currentFrame.anchorPoint.y);
                    glEnd();
                    glDisable(GL_TEXTURE_2D);
                    glDisable(GL_BLEND);
                    break;
                default:
                break;
            }
        }
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
        glVertex2f(m_col*CELL_SIZE-m_currentFrame.anchorPoint.x,      (ROWS-m_row-1)*CELL_SIZE-m_currentFrame.anchorPoint.y);
        glVertex2f((m_col+1)*CELL_SIZE-m_currentFrame.anchorPoint.x,  (ROWS-m_row-1)*CELL_SIZE-m_currentFrame.anchorPoint.y);
        glVertex2f((m_col+1)*CELL_SIZE-m_currentFrame.anchorPoint.x,  (ROWS-m_row)*CELL_SIZE-m_currentFrame.anchorPoint.y);
        glVertex2f(m_col*CELL_SIZE-m_currentFrame.anchorPoint.x,      (ROWS-m_row)*CELL_SIZE-m_currentFrame.anchorPoint.y);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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
                m_white->GetTexture(texture);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texture.texture);
                glBegin(GL_QUADS);
                    glColor4f(1.f, 1.f, 1.f, alpha);
                    glTexCoord2f(0, 1.f);
                        glVertex2f( (m_col+j)*CELL_SIZE-m_currentFrame.anchorPoint.x,      (ROWS-m_row-1-i)*CELL_SIZE-m_currentFrame.anchorPoint.y);
                    glTexCoord2f(1.f, 1.f);
                        glVertex2f((m_col+1+j)*CELL_SIZE-m_currentFrame.anchorPoint.x,  (ROWS-m_row-1-i)*CELL_SIZE-m_currentFrame.anchorPoint.y);
                    glTexCoord2f(1.f, 0.f);
                        glVertex2f((m_col+1+j)*CELL_SIZE-m_currentFrame.anchorPoint.x,  (ROWS-m_row-i)*CELL_SIZE-m_currentFrame.anchorPoint.y);
                    glTexCoord2f(0, 0.f);
                        glVertex2f( (m_col+j)*CELL_SIZE-m_currentFrame.anchorPoint.x,      (ROWS-m_row-i)*CELL_SIZE-m_currentFrame.anchorPoint.y);
                glEnd();
                glDisable(GL_TEXTURE_2D);
            }
        }
    }
    else if (true == m_bLeftPressed)
    {
        m_white->GetTexture(texture);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture.texture);
        glBegin(GL_QUADS);
            glColor4f(1.f, 1.f, 1.f, alpha);
            glTexCoord2f(0, 1.f);
                glVertex2f(m_col*CELL_SIZE-m_currentFrame.anchorPoint.x,      (ROWS-m_row-1)*CELL_SIZE-m_currentFrame.anchorPoint.y);
            glTexCoord2f(1.f, 1.f);
                glVertex2f((m_col+1)*CELL_SIZE-m_currentFrame.anchorPoint.x,  (ROWS-m_row-1)*CELL_SIZE-m_currentFrame.anchorPoint.y);
            glTexCoord2f(1.f, 0.f);
                glVertex2f((m_col+1)*CELL_SIZE-m_currentFrame.anchorPoint.x,  (ROWS-m_row)*CELL_SIZE-m_currentFrame.anchorPoint.y);
            glTexCoord2f(0, 0.f);
                glVertex2f(m_col*CELL_SIZE-m_currentFrame.anchorPoint.x,      (ROWS-m_row)*CELL_SIZE-m_currentFrame.anchorPoint.y);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }

//    glBegin(GL_LINES);
//    for (int i=0; i<=ROWS; i++)
//    {
//        glVertex2f(-m_currentFrame.anchorPoint.x, i*CELL_SIZE-m_currentFrame.anchorPoint.y);
//        glVertex2f(WIDTH_LAYER-m_currentFrame.anchorPoint.x, i*CELL_SIZE-m_currentFrame.anchorPoint.y);
//        for (int j=0; j<=COLS; j++)
//        {
//            glVertex2f(j*CELL_SIZE-m_currentFrame.anchorPoint.x, -m_currentFrame.anchorPoint.y);
//            glVertex2f(j*CELL_SIZE-m_currentFrame.anchorPoint.x, HEIGHT_LAYER-m_currentFrame.anchorPoint.y);
//        }
//    }
//    glEnd();

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
