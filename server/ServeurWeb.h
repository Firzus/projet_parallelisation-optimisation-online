#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#include "json.hpp"
using json = nlohmann::json;

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27020"
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
	void AcceptConnexion();
	void SendHTMLResponse(const std::string& filePath);
	void Shutdown();


private:
	WSADATA wsaData;
	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket;
	int iResult, iSendResult, check;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	bool loop = false;
	const std::string& filePath = "index.html";

};
