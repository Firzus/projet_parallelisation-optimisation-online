#pragma once
#include "framework.h"

#include "json.hpp"
using json = nlohmann::json;

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>


#define DEFAULT_IP NULL
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class clientConfig {

public:
	struct addrinfo* result = NULL, * ptr = NULL, hints;

	clientConfig();

	void AddrInfo();
	void InitWinSock();
	void CreateSocket();
	void ConnectSocketMethod();
	void SendAndReceiveData();
	void Shutdown();


private:
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	json data = {
		{"UserName", "fabien"},
		{"CurrentPlayer", "X"},
		{"arrayX", 2},
		{"arrayY", 2},
		{"PositionMouseX", 2.0},
		{"PositionMouseY", 2.0},
		{"check", 1},
	};
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;
	char recvbuf[DEFAULT_BUFLEN];
};