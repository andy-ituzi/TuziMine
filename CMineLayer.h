#ifndef CMINELAYER_H
#define CMINELAYER_H

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include "CImageLayer.h"
#include "CMineLogic.h"

const int COLS = 7;
const int ROWS = 10;
const int CELL_SIZE = 20;
const int NUM_MINE = 10;
const int WIDTH_LAYER = COLS * CELL_SIZE;
const int HEIGHT_LAYER = ROWS * CELL_SIZE;
const char PATH_NUMBER[8][256] = {
    "./images/1.png",
    "./images/2.png",
    "./images/3.png",
    "./images/4.png",
    "./images/5.png",
    "./images/6.png",
    "./images/7.png",
    "./images/8.png"
};


class CMineLayer : public CLayer
{
public:
    CMineLayer(wxSize clientSize);
    virtual ~CMineLayer();

    virtual void Update(void);
    virtual void Render(void);

    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnRightDown(wxMouseEvent& event);
    void OnRightUp(wxMouseEvent& event);
    void OnMove(wxMouseEvent& event);

    bool HasWon(void)
    {
        return m_logic.IsWin();
    }

    bool WasLost(void)
    {
        return m_logic.IsOver();
    }

    virtual void SetShown(bool show);
    virtual void StartAndEndAt(int start_frame, int end_frame)
    {
        m_repeat = false;
        m_frameCount = start_frame;
        m_end_frame = end_frame;
    }
    void SetActive(bool active)
    {
        m_active = active;
    }
    void SetMineRestart(void)
    {
        m_logic.ReStart();
    }

private:
    bool GetColAndRow(int mouse_client_x, int mouse_client_y, int& col, int& row);

private:
    CMineLogic m_logic;
    int m_col, m_row;
    wxSize m_clientSize;

	bool m_bLeftPressed;
	bool m_bRightPressed;
	bool m_bMouseIn;
    bool m_active;

    CImageLayer *m_number[8];
    CImageLayer *m_flag;
    CImageLayer *m_white;
};

#endif // CMINELAYER_H
