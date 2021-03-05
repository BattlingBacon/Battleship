#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void showGrid(string a[10][10]);
void setupShips(string a[10][10], bool);
void showHostileGrid(string a[10][10]);

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 200

#undef UNICODE


#define PORT "27010"

int __cdecl WinsockSend(string userStr, int messageLength, string ip)
{
    ofstream log;
    log.open("log.txt");

    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;

    const char* sendbuf = &userStr[0];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

    log << "Initializing Winsock for client..." << endl;
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    log << "Resolving server address..." << endl;
    // Resolve the server address and port
    iResult = getaddrinfo(ip.c_str(), PORT, &hints, &result);

    if (iResult != 0)
    {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    log << "Attempting to find the server..." << endl;
    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
    {
        log << "Attempting connection with a server...";

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET)
        {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR)
        {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Nobody else is connected!\n");
        WSACleanup();
        return 1;
    }

    log << "Sending initial buffer..." << endl;
    // Send an initial buffer
    iResult = send(ConnectSocket, sendbuf, messageLength, 0);
    if (iResult == SOCKET_ERROR)
    {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    log << "Cleaning up..." << endl;
    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();


    return 0;
}



int __cdecl WinsockRecieve(string &recievedStr)
{
    char signalRecieved[200] = " ";
    string recievedText = "";
    string sentText = "";

    ofstream log;
    log.open("log.txt");

    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    log << "Initilizing Winsock for server..." << endl;
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    log << "Resolving this server's address and port..." << endl;
    // Resolve the server address and port
    iResult = getaddrinfo(NULL, PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    log << "Creating a socket for connection to this server..." << endl;
    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    log << "Setting up TCP listening socket..." << endl;
    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR)
    {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    log << "Ready to accept sockets." << endl;

    WSAPOLLFD listeningSocketFD = {};
    listeningSocketFD.events = POLLRDNORM;
    listeningSocketFD.revents = 0;


    // Accept client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);

    log << "Accepted a socket." << endl;

    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Receive until the peer shuts down the connection
    do {

        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        recievedText = recvbuf;
        if (iResult < 0)
        {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }

    } while (iResult > 0);

    for (int i = 0; i < recievedText.length(); i++)
        if (int(recievedText.at(i)) >= 127 || int(recievedText.at(i)) <= 19)
            recievedText.erase(i);

    recievedStr = recievedText;
    log << "Recieved: " << recievedText << endl;
    for (int i = 0; i < recievedText.length(); i++)
        signalRecieved[i] = '\0';

    log << "Peer closed connection" << endl;
    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    log << "Closing server socket..." << endl;
    // No longer need server socket
    closesocket(ListenSocket);

    log << "Cleaning up..." << endl;
    // cleanup
    log.close();
    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}

void multiplayer()
{
    string otherPlayerArr[10][10];
    string playerArr[10][10];
    setupShips(playerArr, true);
    string hostIP = "";
    string clientIP = "";
    string recievedText = "";

    char turn = '\0';
    bool host = false;

    char choice = '\0';
    cout << "Host? (Y/N):: ";
    cin >> choice;
    while (choice != 'Y' && choice != 'N')
    {
        cout << "Invalid! Host? (Y/N):: ";
        cin >> choice;
    }
    if (choice == 'Y')
    {
        hostIP = "N/A";
        host = true;
        system("ipconfig");
        cout << endl << endl << "The above text is your IP information. Tell the other player your IPv4 address. Waiting for them to connect...";
        WinsockRecieve(recievedText);
        clientIP = recievedText;
        system("CLS");
    }
    else if (choice == 'N')
    {
        host = false;
        system("ipconfig");
        cout << endl << endl << "The above text is your IP information. What is your IPv4 address: ";
        cin >> clientIP;
        system("CLS");

        cout << "Have the host tell you their IP. What is the host's IP: ";
        cin >> hostIP;

        while (WinsockSend(clientIP, clientIP.length(), hostIP))

        system("CLS");
    }

    int x = 0;
    int y = 0;
    bool playing = true;
    bool playerWin = false;
    bool retry = true;
    int hits = 0;
    string final = "";

    if (host)
    {
        while (playing)
        {
            system("CLS");
            showHostileGrid(otherPlayerArr);
            cout << endl << "==========================" << endl << endl;
            showGrid(playerArr);
            cout << endl;

            cout << "Fire at (x y): ";
            cin >> x;
            cin >> y;
            while (retry)
            {
                while (x > 10 || x < 1 || y < 1 || y > 10)
                {
                    cout << "Error! Fire at (x y): ";
                    cin >> x;
                    cin >> y;
                }

                y--;
                x--;

                if (!(otherPlayerArr[x][y] == "XX" || otherPlayerArr[x][y] == "x "))
                {
                    retry = false;
                    cout << "You've already fired there!" << endl;
                }
            }

            final = to_string(x) + " " + to_string(y);

            WinsockSend(final, final.length(), clientIP);
            WinsockRecieve(recievedText);
            otherPlayerArr[x][y] = recievedText;
            
            WinsockRecieve(recievedText);
            stringstream ss;
            ss << recievedText;
            ss >> x;
            ss >> y;

            if (playerArr[x][y] == "")
            {
                WinsockSend("x ", 2, clientIP);
                playerArr[x][y] == "x ";
            }
            else
            {
                WinsockSend("XX", 2, clientIP);
                playerArr[x][y] == "XX";
                hits++;
            }

            if (hits >= 17)
            {
                system("CLS");
                cout << "You won!";
                playing = false;
            }
        }
    }

    if (!host)
    {
        while (playing)
        {
            system("CLS");
            WinsockRecieve(recievedText);
            stringstream ss;
            ss << recievedText;
            ss >> x;
            ss >> y;

            if (playerArr[x][y] == "")
            {
                WinsockSend("x ", 2, hostIP);
                playerArr[x][y] == "x ";
            }
            else
            {
                WinsockSend("XX", 2, hostIP);
                playerArr[x][y] == "XX";
                hits++;
            }

            if (hits >= 17)
            {
                system("CLS");
                cout << "You won!";
                playing = false;
            }

            showHostileGrid(otherPlayerArr);
            cout << endl << "==========================" << endl << endl;
            showGrid(playerArr);
            cout << endl;

            cout << "Fire at (x y): ";
            cin >> x;
            cin >> y;
            while (retry)
            {
                while (x > 10 || x < 1 || y < 1 || y > 10)
                {
                    cout << "Error! Fire at (x y): ";
                    cin >> x;
                    cin >> y;
                }

                y--;
                x--;

                if (!(otherPlayerArr[x][y] == "XX" || otherPlayerArr[x][y] == "x "))
                {
                    retry = false;
                    cout << "You've already fired there!" << endl;
                }
            }

            final = to_string(x) + " " + to_string(y);

            WinsockSend(final, final.length(), hostIP);
            WinsockRecieve(recievedText);
            otherPlayerArr[x][y] = recievedText;
        }
    }
}