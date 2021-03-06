#include <cstdlib>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <windows.h>

using namespace std;

void showGrid(string a[10][10]);
void setupShips(string a[10][10], bool);

void showHostileGrid(string gridArr[][10])
{
	int line = 10;
	cout << "   ----------------------" << endl;
	for (int i = 9; i >= 0; i--)
	{
		cout << setw(2) << line << " |";
		for (int j = 0; j < 10; j++)
			if (gridArr[j][i] == "" || gridArr[j][i] == "x " || gridArr[j][i] == "XX")
				cout << setw(2) << gridArr[j][i];
			else
				cout << "  ";
		cout << "|" << endl;
		line--;
	}
	cout << "   ----------------------" << endl;
	cout << "    1 2 3 4 5 6 7 8 9 10" << endl;
}

void singleplayer()
{
	string playerArr[10][10];
	string botArr[10][10];

	srand(time(NULL));

	setupShips(playerArr, false);
	setupShips(botArr, true);

	system("CLS");

	int x = 0;
	int y = 0;
	bool playing = true;
	bool turn = true;
	bool playerWin = false;
	int hitPlayer = 0;
	int hitBot = 0;

	while (playing)
	{
		PlaySound(L"kombat.wav", NULL, SND_ASYNC);
		while (turn)
		{
			showHostileGrid(botArr);
			cout << endl << "==========================" << endl << endl;
			showGrid(playerArr);
			cout << endl;

			cout << "Fire at (x y): ";
			cin >> x;
			cin >> y;

			while (x > 10 || x < 1 || y < 1 || y > 10)
			{
				cout << "Error! Fire at (x y): ";
				cin >> x;
				cin >> y;
			}

			y--;
			x--;
			if (botArr[x][y] != "XX" && botArr[x][y] != "x ")
			{
				if (botArr[x][y] == "")
					botArr[x][y] = "x ";
				else
				{
					botArr[x][y] = "XX";
					hitBot++;
				}
				turn = false;
			}
			else
			{
				cout << "You've already tried there!\n\n";
			}
		}
		turn = true;

		while (turn)
		{
			x = rand() % 9 + 0;
			y = rand() % 9 + 0;
			if (playerArr[x][y] != "XX" && playerArr[x][y] != "x ")
			{
				if (playerArr[x][y] == "")
					playerArr[x][y] = "x ";
				else
				{
					playerArr[x][y] = "XX";
					hitPlayer++;
				}
				turn = false;
			}
		}
		turn = true;
		system("CLS");

		if (hitBot >= 17 || hitPlayer >= 17)
			playing = false;
	}

	if (hitBot >= 17)
		cout << "Player wins!";
	else
		cout << "Bot wins!";
}