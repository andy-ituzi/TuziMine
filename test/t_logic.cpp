#include <iostream>
#include "..\CMineLogic.h"

using namespace std;

int main()
{
    int cols = 10, rows = 4;
    char op;
    int col, row;
    int state;
    CMineLogic logic(cols, rows, 5);
    logic.PrintState();
    while (true)
    {
        if (true == logic.IsOver())
        {
            cout << "You've uncovered mine!! game over!!" << endl ;
            cout << "'r' to restart game~" << endl;
            cout << "'q' to quit~" << endl;
            cin >> op;
            if ('r' == op)
            {
                logic.ReStart();
            }
            else
            {
                break;
            }
        }
        else if (true == logic.IsWin())
        {
            cout << "Congratulations!! You've won this game !!" << endl ;
            cout << "'r' to restart game~" << endl;
            cout << "'q' to quit~" << endl;
            cin >> op;
            if ('r' == op)
            {
                logic.ReStart();
            }
            else
            {
                break;
            }
        }

        for (int i=0; i<rows; i++)
        {
            if (0 == i)
            {
                cout << " ";
                for (int j=0; j<cols; j++)
                {
                    cout << j%10;
                }
                cout << endl;
            }
            cout << i;
            for (int j=0; j<cols; j++)
            {
                state = logic.StateShowOf(j, i);
                switch (state)
                {
                    case STATE_EMPTY: cout << " ";  break;
                    case STATE_1:   cout << "1";    break;
                    case STATE_2:   cout << "2";    break;
                    case STATE_3:   cout << "3";    break;
                    case STATE_4:   cout << "4";    break;
                    case STATE_5:   cout << "5";    break;
                    case STATE_6:   cout << "6";    break;
                    case STATE_7:   cout << "7";    break;
                    case STATE_8:   cout << "8";    break;
                    case STATE_NEW: cout << "N";    break;
                    case STATE_MINE:cout << "9";    break;
                    case STATE_FLAG:cout << "F";    break;
                    default: break;
                }
            }
            cout << endl;
        }
        cout << logic.MineLeft() << " mines left." << endl;
        cin >> op;
        if ('u' == op)
        {
            cin >> col >> row;
            logic.OpenGrid(col, row);
        }
        else if ('f' == op)
        {
            cin >> col >> row;
            logic.FlagGrid(col, row);
        }
        else if ('p' == op)
        {
            cin >> col >> row;
            logic.OpenGridPlus(col, row);
        }
        else
        {
            break;
        }

    }

    return 0;
}

