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

    virtual bool Initialize(void);
    virtual void Update(void);
    virtual void Render(void);


    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnRightDown(wxMouseEvent& event);
    void OnRightUp(wxMouseEvent& event);
    void OnMove(wxMouseEvent& event);

private:
    bool GetColAndRow(int mouse_client_x, int mouse_client_y, int& col, int& row);

private:
    CMineLogic m_logic;
    int m_col, m_row;
    wxSize m_clientSize;

	bool m_bLeftPressed;
	bool m_bRightPressed;

    CImageLayer *m_number[8];
    CImageLayer *m_flag;
    CImageLayer *m_white;
};

#endif // CMINELAYER_H
