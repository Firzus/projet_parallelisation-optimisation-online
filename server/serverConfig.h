#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>

#include "json.hpp"
using json = nlohmann::json;

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")




class serverConfig {
public:
	struct addrinfo* result = NULL, * ptr = NULL, hints;

	serverConfig();

	void AddrInfo();
	void InitWinSock();
	void CreateSocket();
	void LinkSocket();
	void ListenSocketMethod();
	void AcceptConnexion();
	void ReceiveAndsendData();
	void Shutdown();


private:
	void JsonObjectToJsonFile();
	json JsonFileToJsonObject();
	std::string JsonObjectToString();

	WSADATA wsaData;
	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket;
	int iResult, iSendResult, check;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	bool loop = false;
};