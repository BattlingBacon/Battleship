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
	PlaySound(L"anchorsaweigh.wav", NULL, SND_ASYNC);
	displaySplash();

	return 0;
}

void displaySplash()
{
	//bool run = true;
	char choice = '\0';
	/*
	thread input(getInput, ref(choice));
	ifstream inFile;
	inFile.open("titlesplash.txt");
	string splash0 = "";
	string splash1 = "";
	string splash2 = "";
	string splash3 = "";
	string addTo = "";
	int option = 0;

	for (int i = 0; i < 30; i++)
	{
		getline(inFile, addTo);
		splash0 += addTo + "\n";
	}
	inFile.close();
	inFile.open("titlesplash flak1.txt");
	for (int i = 0; i < 30; i++)
	{
		getline(inFile, addTo);
		splash1 += addTo + "\n";
	}
	inFile.close();
	inFile.open("titlesplash flak2.txt");
	for (int i = 0; i < 30; i++)
	{
		getline(inFile, addTo);
		splash2 += addTo + "\n";
	}
	inFile.close();
	inFile.open("titlesplash flak3.txt");
	for (int i = 0; i < 30; i++)
	{
		getline(inFile, addTo);
		splash3 += addTo + "\n";
	}
	inFile.close();

	while (run)
	{
		if (option >= 0 && option <= 5)
			cout << splash0;

		if (option == 6)
			cout << splash1;

		if (option >= 7 && option <= 8)
			cout << splash2;

		if (option >= 9 && option <= 11)
			cout << splash3;

		cout << "\n\n\n Singleplayer or multiplayer? (S/M): ";
		if (choice == 'S' || choice == 'M')
		{
			input.detach();
			run = false;
		}
		Sleep(500);
		option++;
		if (option > 11)
			option = 0;
		system("CLS");
	}*/
	while (choice != 'S' && choice != 'M')
	{
		cout << "\n\n\n Singleplayer or multiplayer? (S/M): ";
		cin >> choice;
		system("CLS");
	}

	PlaySound(NULL, 0, 0);
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