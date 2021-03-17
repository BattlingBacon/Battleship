#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

using namespace std;

bool validInput(int spaces, char dir, int x, int y, string gridArr[][10])
{
    x--;
    y--;
    if (dir == 'N')
    {
        if (!(y + spaces <= 10))
            return false;

        for (int i = 0; i < spaces; i++)
            if (gridArr[x][y + i] != "")
                return false;
    }

    if (dir == 'E')
    {
        if (!(x + spaces <= 10))
            return false;

        for (int i = 0; i < spaces; i++)
            if (gridArr[x + i][y] != "")
                return false;
    }

    if (dir == 'S')
    {
        if (!(y - spaces + 2 >= 1))
            return false;

        for (int i = 0; i < spaces; i++)
            if (gridArr[x][y - i] != "")
                return false;
    }

    if (dir == 'W')
    {
        if (!(x - spaces + 2 >= 1))
            return false;

        for (int i = 0; i < spaces; i++)
            if (gridArr[x - i][y] != "")
                return false;
    }

    return true;
}

void placeShip(int spaces, string shipStr, char dir, int x, int y, string gridArr[][10])
{
    x--;
    y--;
    if (dir == 'N')
        for (int i = 0; i < spaces; i++)
            gridArr[x][y + i] = shipStr;

    if (dir == 'E')
        for (int i = 0; i < spaces; i++)
            gridArr[x + i][y] = shipStr;

    if (dir == 'S')
        for (int i = 0; i < spaces; i++)
            gridArr[x][y - i] = shipStr;

    if (dir == 'W')
        for (int i = 0; i < spaces; i++)
            gridArr[x - i][y] = shipStr;
}

void showGrid(string gridArr[][10])
{
    int line = 10;
    cout << "   ----------------------" << endl;
    for (int i = 9; i >= 0; i--)
    {
        cout << setw(2) << line << " |";
        for (int j = 0; j < 10; j++)
            cout << setw(2) << gridArr[j][i];
        cout << "|" << endl;
        line--;
    }
    cout << "   ----------------------" << endl;
    cout << "    1 2 3 4 5 6 7 8 9 10" << endl;
}

void setupShips(string gridArr[][10], bool bot)
{
    static int hasRun = time(NULL);
    srand(time(NULL) + hasRun);
    hasRun /= 2;

    string shipsAvail[5] = { "CV", "BB", "CL", "SS", "DD" };
    bool shipsTaken[5] = { false, false, false, false, false };
    int shipSpaces[5] = { 5, 4, 3, 3, 2 };

    int finished = 0;
    int found = -1;
    bool run = true;

    int StartX = 0, StartY = 0;
    string input;
    char direction = '\0';

    while (run)
    {
        int botDir = 0;

        if (bot)
        {
            botDir = rand() % 5 + 0;
            input = shipsAvail[botDir];
        }
        else
        {
            showGrid(gridArr);
            cout << endl << endl;

            cout << "On the 10 x 10 field, please choose a ship, starting position and direction " << endl;
            cout << "Ships to Place: ";
            for (int i = 0; i < 5; i++)
                if (shipsAvail[i] != "")
                    cout << shipsAvail[i] << ", ";

            cout << ":: ";
            cin >> input;
        }

        for (int i = 0; i < 5; i++)
            if (input == shipsAvail[i])
                found = i;

        if (shipsTaken[found])
            found = -1;

        if (found != -1)
        {
            if (!bot)
            {
                cout << endl << "Now choose your cardinal direction of N, E, S, or W: ";
                cin >> direction;
                while (direction != 'N' && direction != 'E' && direction != 'S' && direction != 'W')
                {
                    cout << "Invalid! Please choose N, E, S, or W: ";
                    cin >> direction;
                }

                cout << "Now choose your starting X and Y coordinate out of 10: " << endl;
                cout << "X: ";
                cin >> StartX;
                while (StartX < 1 || StartX > 10)
                {
                    cout << "Invalid! X: ";
                    cin >> StartX;
                }
                cout << "Y: ";
                cin >> StartY;
                while (StartY < 1 || StartY > 10)
                {
                    cout << "Invalid! X: ";
                    cin >> StartY;
                }
                cout << endl;
            }
            else
            {
                botDir = rand() % 4 + 1;
                if (botDir == 1)
                    direction = 'N';
                else if (botDir == 2)
                    direction = 'E';
                else if (botDir == 2)
                    direction = 'S';
                else
                    direction = 'W';
                StartY = rand() % 10 + 1;
                StartX = rand() % 10 + 1;
            }
            if (validInput(shipSpaces[found], direction, StartX, StartY, gridArr))
            {
                shipsTaken[found] = true;
                placeShip(shipSpaces[found], shipsAvail[found], direction, StartX, StartY, gridArr);
                shipsAvail[found] = "";
                finished++;
            }
            else
            {
                if (!bot)
                {
                    system("CLS");
                    cout << "Invalid placement!" << endl << endl;
                }
            }
        }
        else
        {
            if (!bot)
            {
                system("CLS");
                cout << "That ship is not an option!" << endl << endl;
            }
        }

        found = -1;
        if (finished == 5)
        {
            run = false;
        }
    }
}