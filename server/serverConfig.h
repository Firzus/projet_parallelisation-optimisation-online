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
	//			DATA
	// Player one
	void SendDataPlayerOne(int valueConvert);
	void ReceiveDataPlayerOne();

	//Player Two
	void SendDataPlayerTwo(int valueConvert);
	void ReceiveDataPlayerTwo();

	//			SHUTDOWN
	// 1 for Player One | 2 for Player Two | 3 for Server socket
	void Shutdown(int value);

	//			CLEANUP
	void Cleanup(int value);
	
	//          HANDLE EVENT SOCKET
	void HandleSocketMessage(HWND hWnd, WPARAM wParam, LPARAM lParam);

private:

	// convert string buf data to json object data
	json RecvBufToJsonObject();
	// convert json file data to json object data
	json JsonFileToJsonObject();
	// convert json object data to string data
	// (0 for convert since json file || 1 for convert since json object) to string
	std::string JsonObjectToString(int value);
	// convert json object data to file data
	void StoreJsonObjectToJsonFile();
	
	WSADATA wsaData;
	SOCKET ListenSocket = INVALID_SOCKET;
	
	int iResult, iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

private : // 
	void AcceptConnection(int clientID);
	//void SetNametoPlayerAddress();

	bool Check();
	void Checkturn();

	SOCKET clientIncoming = INVALID_SOCKET;
	sockaddr_in clientAddress;
	
	SOCKET PlayerOne = INVALID_SOCKET;
	sockaddr_in PlayerOneAddress;

	SOCKET PlayerTwo = INVALID_SOCKET;
	sockaddr_in PlayerTwoAddress;

	int clientCounter = 0;
	bool turn = false, PlayerOneIsConnected = false, PlayerTwoIsConnected = false;
};

// 1476460810