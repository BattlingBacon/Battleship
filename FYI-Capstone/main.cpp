#include <cstdlib>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <Windows.h>
#include <fstream>
#include <thread>;

using namespace std;

//NetworkFunctions.cpp
int __cdecl WinsockSend(string, int, string);
int __cdecl WinsockRecieve();
void multiplayer();

//ShipPlacement.cpp
void showGrid(string a[10][10]);
void setupShips(string a[10][10], bool);

//Singleplayer.cpp
void showHostileGrid(string a[10][10]);
void singleplayer();

//main.cpp
void displaySplash();
void getInput(char&);

int main()
{
	displaySplash();

	return 0;
}

void displaySplash()
{
	char choice = '/0';
	while (choice != 'S' && choice != 'M')
	{
		cout << "Singleplayer or multiplayer? (S/M): ";
		cin >> choice;
		system("CLS");
	}

	system("CLS");

	if (choice == 'S')
		singleplayer();
	else if (choice == 'M')
		multiplayer();
}

void getInput(char &choice)
{
	while (true)
	{
		cin >> choice;
	}
}