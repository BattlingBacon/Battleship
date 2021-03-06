// sources:
// USS Iowa: https://ascii.co.uk/art/battleship
// text to ascii: https://www.patorjk.com/

#include <cstdlib>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <Windows.h>
#include <fstream>


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
	ifstream inFile;
	inFile.open("title.txt");

	string paste = "";
	for (int i = 0; i < 19; i++)
	{
		getline(inFile, paste);
		cout << paste << endl;
	}

	cout << "                (Artwork by Matthew Bace)" << endl;

	PlaySound(L"anchorsaweigh.wav", NULL, SND_ASYNC);


	char choice = '\0';
	cout << "\nSingleplayer or multiplayer? (S/M): ";
	cin >> choice;
	while (choice != 'S' && choice != 'M')
	{
		cout << "Invalid! Singleplayer or multiplayer (S/M): ";
		cin >> choice;
	}
	PlaySound(NULL, 0, 0);
	system("CLS");

	if (choice == 'S')
		singleplayer();
	else if (choice == 'M')
		multiplayer();

	return 0;
}