#pragma once
#include "framework.h"

#include "json.hpp"
using json = nlohmann::json;

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#include "Data.h"

#define DEFAULT_IP NULL
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class clientConfig {
public:
	struct addrinfo* result = NULL, * ptr = NULL, hints;

	clientConfig() {};

	void Init();

	void AddrInfo();
	void InitWinSock();
	void CreateSocket();
	void ConnectSocketMethod();

	void SendAndReceiveData();
	void Shutdown();

private:
	Data da;
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	json data = {
		{"Player1",
			{"PlayerName", da.GetPlayerName()},
			{"PlayerToken", da.GetPlayerToken()},
		},

		{"Player2",
			{"PlayerName", da.GetPlayerName()},
			{"PlayerToken", da.GetPlayerToken()},
		},

		{"CurrentPlayer", da.GetPlayerToken()},
		{"TokenPos", da.GetBoard()},
		{"WinnerName", da.GetWinner()},
		{"Connection", da.GetConnection()},
	};

	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;
	char recvbuf[DEFAULT_BUFLEN];
};