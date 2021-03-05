#include <cstdlib>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;

//NetworkFunctions.cpp
int __cdecl WinsockSend(string, int, string);
int __cdecl WinsockRecieve();
void multiplayer();

//ShipPlacement.cpp
void showGrid(string a[10][10]);
void setupShips(string a[10][10], bool);

//main.cpp
void showHostileGrid(string a[10][10]);
void singleplayer();

int main()
{
	char choice = '\0';
	cout << "Singleplayer or multiplayer (S/M): ";
	cin >> choice;
	while (choice != 'S' && choice != 'M')
	{
		cout << "Invalid! Singleplayer or multiplayer (S/M): ";
		cin >> choice;
	}

	system("CLS");

	if (choice == 'S')
		singleplayer();
	else if (choice == 'M')
		multiplayer();

	return 0;
}