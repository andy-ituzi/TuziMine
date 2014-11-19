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

        logic.PrintBoard();

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

