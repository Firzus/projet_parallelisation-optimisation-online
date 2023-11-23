#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <exception> 
#include <map>

#include "json.hpp"
using json = nlohmann::json;

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define MAXVALUES 2

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class serverConfig {
public:
	struct addrinfo* result = NULL, * ptr = NULL, hints;

	serverConfig();
	
	void Init(HWND hWnd);

	//			SERVER PART
	void AddrInfo();
	void InitWinSock();
	void CreateSocket();

	//			WSA ASYNC SERVER
	void ConfigureServerSocket(HWND hWnd);

	//			SERVER PART
	void LinkSocket();
	void ListenSocketMethod();

	//			CLIENT PART
	bool AcceptPlayerOne(); // testing
	//			DATA
	// Player one
	void SendDataPlayerOne();// testing
	void ReceiveDataPlayerOne(); // testing

	//			SHUTDOWN
	void ShutdownPlayerOne(); // testing

	//			CLEANUP
	void Cleanup(int nb);
	
	//          HANDLE EVENT SOCKET
	void HandleSocketMessage(HWND hWnd, WPARAM wParam, LPARAM lParam);

private:

	// convert string buf to json object
	json JsonStringToJsonObject();
	// convert json file to json object
	json JsonFileToJsonObject();
	// convert json object to string
	std::string JsonObjectToString();
	// convert json object to file
	void JsonObjectToJsonFile();
	
	WSADATA wsaData;
	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientPlayerOne = INVALID_SOCKET;
	
	int iResult, iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	bool isGameOn = false;
	bool isConnected = false;

private :
	void AcceptConnection(int clientID);

	void SetNametoPlayerAddress();

	SOCKET clientIncoming = INVALID_SOCKET;
	sockaddr_in clientAddress;
	
	SOCKET PlayerOne = INVALID_SOCKET;
	sockaddr_in PlayerOneAddress;

	SOCKET PlayerTwo = INVALID_SOCKET;
	sockaddr_in PlayerTwoAddress;

	int clientCounter = 0;
};

// 1476460810