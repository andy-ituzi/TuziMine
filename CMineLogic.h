#ifndef CMINELOGIC
#define CMINELOGIC

const int STATE_EMPTY = 0;
const int STATE_1 = 1;
const int STATE_2 = 2;
const int STATE_3 = 3;
const int STATE_4 = 4;
const int STATE_5 = 5;
const int STATE_6 = 6;
const int STATE_7 = 7;
const int STATE_8 = 8;
const int STATE_NEW = 10;
const int STATE_FLAG = 20;
const int STATE_MINE = 9;

const int DIR_LEFT_UP = 0;
const int DIR_UP = 1;
const int DIR_RIGHT_UP = 2;
const int DIR_LEFT = 3;
const int DIR_SELF = 4;
const int DIR_RIGHT = 5;
const int DIR_LEFT_DOWN = 6;
const int DIR_DOWN = 7;
const int DIR_RIGHT_DOWN = 8;

const int MIN_COLS = 5;
const int MIN_ROWS = 5;
const int MAX_COLS = 20;
const int MAX_COLS_PLUS = MAX_COLS + 2;
const int MAX_ROWS = 20;
const int MAX_ROWS_PLUS = MAX_ROWS + 2;
const int MAX_LENGTH = MAX_COLS * MAX_ROWS;
const int MAX_LENGTH_PLUS = MAX_COLS_PLUS * MAX_ROWS_PLUS;

class CMineLogic
{
public:
    CMineLogic(int cols, int rows, int mines);

    bool IsOver(void)
    {
        return m_over;
    }
    bool IsWin(void);
    int MineLeft(void)
    {
        return m_nMineLeft;
    }
    int StateShowOf(int col, int row);
    void ReStart(void);

	void OpenGrid(int col, int row);
	void OpenGrid(int offset);
	void OpenGridPlus(int col, int row);
	void FlagGrid(int col, int row);
	void PrintState(void);

private:
    int m_cols;
    int m_rows;
    int m_mines;
    int m_nMineLeft;
    bool m_over;
    int m_stateShow[MAX_LENGTH_PLUS];
    int m_stateHide[MAX_LENGTH_PLUS];
    bool m_inBoard[MAX_LENGTH_PLUS];

private:
    int Offset(int offset, int dir, int unuse);
    int Offset(int col, int row)
    {
        return MAX_COLS_PLUS * (row + 1) + col + 1;
    }
    int Col(int offset)
    {
        return offset % MAX_COLS_PLUS -1;
    }
    int Row(int offset)
    {
        return offset / MAX_COLS_PLUS -1;
    }
    void GenerateMines(void);
    void GenerateInBoard(void);
};

#endif // CMINELOGIC
