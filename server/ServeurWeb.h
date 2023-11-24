#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include <vector>

#include "json.hpp"

using json = nlohmann::json;

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "3001"
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class ServeurWeb {
public:
	struct addrinfo* result = NULL, * ptr = NULL, hints;

	ServeurWeb();

	void Init();
	void AddrInfo();
	void InitWinSock();
	void CreateSocket();
	void LinkSocket();
	void ListenSocketMethod();
	std::string AcceptConnexion();
	std::string ParseHttpRequest(const std::string& httpRequest);
	void HandleHTTPRequest(const std::string& requestUrl);
	void SendNotFoundResponse();
	void SendHTMLResponse(const std::string& filePath);
	void Shutdown();

	void Loop();
private:
	WSADATA wsaData;
	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket;
	int iResult, iSendResult, check;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	bool loop = false;
};
