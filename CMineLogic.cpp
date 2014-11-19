#include "CMineLogic.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

CMineLogic::CMineLogic(int cols, int rows, int mines)
    :m_cols(cols),
    m_rows(rows),
    m_mines(mines),
    m_nMineLeft(m_mines),
    m_over(false)
{
    for (int i=0; i<MAX_LENGTH_PLUS; i++)
	{
	    m_stateShow[i] = STATE_NEW;
		m_stateHide[i] = STATE_EMPTY;
        m_inBoard[i] = false;
	}
	GenerateInBoard();// must before GenerateMines()
	GenerateMines();
}

void CMineLogic::ReStart(void)
{
    m_over = false;
	m_nMineLeft = m_mines;
	for (int i=0; i<MAX_LENGTH_PLUS; i++)
	{
		m_stateShow[i] = STATE_NEW;
		m_stateHide[i] = STATE_EMPTY;
	}
	GenerateMines();
}


int CMineLogic::StateShowOf(int col, int row)
{
    return m_stateShow[ Offset(col, row) ];
}

void CMineLogic::OpenGrid(int col, int row)
{
    if (true == m_over)
    {
        return;
    }
    int offset = Offset(col, row);
	if ( (true == m_inBoard[offset]) && (STATE_NEW == m_stateShow[offset]) )
	{
		m_stateShow[offset] = m_stateHide[offset];
		if (STATE_EMPTY == m_stateShow[offset])
		{
			for (int i=0; i<9; i++)
			{
				OpenGrid( Offset(offset, i, 0) );
			}
		}
		else if (STATE_MINE == m_stateShow[offset])
		{
			m_over = true;
		}
	}
}

void CMineLogic::OpenGrid(int offset)
{
    if (true == m_over)
    {
        return;
    }
	if ( (true == m_inBoard[offset]) && (STATE_NEW == m_stateShow[offset]) )
	{
		m_stateShow[offset] = m_stateHide[offset];
		if (STATE_EMPTY == m_stateShow[offset])
		{
			for (int i=0; i<9; i++)
			{
				OpenGrid( Offset(offset, i, 0) );
			}
		}
		else if (STATE_MINE == m_stateShow[offset])
		{
			m_over = true;
		}
	}
}

void CMineLogic::OpenGridPlus(int col, int row)
{
    if (true == m_over)
    {
        return;
    }
    int offset = Offset(col, row);
	if ( (STATE_1 <= m_stateShow[offset]) && (STATE_8 >= m_stateShow[offset]) )
	{
		int cnt = 0;
		int temp = 0;
		for (int i=0; i<9; i++)
		{
		    temp = Offset(offset, i, 0);
			if ( (true == m_inBoard[temp]) && (STATE_FLAG == m_stateShow[temp]) )
			{
				cnt++;
			}
		}
		if ( (cnt + STATE_1 - 1) == m_stateShow[offset] )
		{
			for (int i=0; i<9; i++)
			{
				OpenGrid( Offset(offset, i, 0) );
			}
		}
	}
}

void CMineLogic::FlagGrid(int col, int row)
{
    if (true == m_over)
    {
        return;
    }
    int offset = Offset(col, row);
	if (STATE_FLAG == m_stateShow[offset])
	{
		m_stateShow[offset] = STATE_NEW;
		m_nMineLeft++;
	}
	else if (STATE_NEW == m_stateShow[offset])
	{
		m_stateShow[offset] = STATE_FLAG;
		m_nMineLeft--;
	}
}

int CMineLogic::Offset(int offset, int dir, int unuse)
{
    switch (dir)
    {
    case DIR_LEFT_UP:
        return offset - MAX_COLS_PLUS - 1;
    case DIR_UP:
        return offset - MAX_COLS_PLUS;
    case DIR_RIGHT_UP:
        return offset - MAX_COLS_PLUS + 1;
    case DIR_LEFT:
        return offset - 1;
    case DIR_SELF:
        return offset;
    case DIR_RIGHT:
        return offset + 1;
    case DIR_LEFT_DOWN:
        return offset + MAX_COLS_PLUS - 1;
    case DIR_DOWN:
        return offset + MAX_COLS_PLUS;
    case DIR_RIGHT_DOWN:
        return offset + MAX_COLS_PLUS + 1;
    default:
        break;
    }
    return 0;
}

void CMineLogic::GenerateMines(void)
{
	int offset = 0;
	int temp = 0;
	srand( time(NULL) );
	for (int i=0; i<m_mines; i++)
	{
		while (true)
		{
			offset = rand() % ( MAX_LENGTH_PLUS );
			if ( (true == m_inBoard[offset]) && (STATE_MINE != m_stateHide[offset]) )
			{
				m_stateHide[offset] = STATE_MINE;
				//debug
				//std::cout << "DEUBG: " << Col(offset) << Row(offset) << "is a mine" << std::endl;
				break;
			}
		}
	}

	for (int i=0; i<MAX_LENGTH_PLUS; i++)
    {
        if ( (false == m_inBoard[i]) || (STATE_MINE == m_stateHide[i]) )
        {
            continue;
        }
        for (int j=0; j<9; j++)
        {
            temp = Offset(i, j, 0);
            if ( (true == m_inBoard[temp]) && (STATE_MINE == m_stateHide[temp]) )
            {
                m_stateHide[i]++;
            }
        }
    }

//    for (int i=0; i<MAX_LENGTH_PLUS; i++)
//    {
//        if ( (true == m_inBoard[i])&& (STATE_MINE != m_stateHide[i]))
//        {
//            OpenGrid(i);
//            std::cout << "open " << Col(i) << Row(i) << std::endl;
//        }
//    }
}

void CMineLogic::GenerateInBoard(void)
{
    int offset = MAX_COLS_PLUS + 1;
    for (int i=0; i<m_rows; i++)
    {
        for (int j=0; j<m_cols; j++)
        {
            m_inBoard[offset + j] = true;
            //debug
//            std::cout << "1";
        }
        offset += MAX_COLS_PLUS;
        //debug
//        std::cout << std::endl;
    }
}

void CMineLogic::PrintState(void)
{
    int offset = MAX_COLS_PLUS + 1;
    for (int i=0; i<m_rows; i++)
    {
        for (int j=0; j<m_cols; j++)
        {
            std::cout << m_stateHide[offset+j];
        }
        std::cout << std::endl;
        offset += MAX_COLS_PLUS;
    }
}

bool CMineLogic::IsWin(void)
{
	for (int i=0; i<MAX_LENGTH_PLUS; i++)
    {
        if ( (true == m_inBoard[i]) && (STATE_MINE != m_stateHide[i]) && (m_stateHide[i] != m_stateShow[i]) )
        {
            return false;
        }
    }
    return true;
}
