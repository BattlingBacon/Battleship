#include <iostream>
#include <windows.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <thread>

using namespace std;

int __cdecl WinsockSend(string, int, string);
int __cdecl WinsockRecieve(char[], string);


bool InputVal(char, char, string);
void BombDefuser();
void Angel();
void Devil();
void Send(string, string);
void SendOnce(string);
void recieveThread(string, string);
void timerThread();

string port = "27010";

char recievedSignal[200] = " ";

int main()
{
	char x = 'A';
	while (true)
	{
		string inp = "";
		cout << endl << "(S)end or (R)ecieve data? ";
		cin >> x;
		if (x == 'S')
		{
			string str = "";
			cout << "Sending: ";
			cin >> str;
			WinsockSend(str, str.length(), port);
			cout << "Sent!";
		}
		else if (x == 'R')
		{
			cout << "Waiting to recieve info..." << endl;
			WinsockRecieve(recievedSignal, port);
		}
		Sleep(1000);
	}
}