#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <exception> 

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
	bool AcceptPlayerOne();
	//			DATA
	// Player one
	void SendDataPlayerOne();
	void ReceiveDataPlayerOne();

	//			SHUTDOWN
	void ShutdownPlayerOne();

	void ShutdownAll();
	//			CLEANUP
	void Cleanup(int nb);

	void LoadGame();
	void HandleSocketMessage(WPARAM wParam, LPARAM lParam);

private:

	json JsonStringToJsonObject();
	json JsonFileToJsonObject();
	std::string JsonObjectToString();
	void JsonObjectToJsonFile();


	WSADATA wsaData;
	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientPlayerOne = INVALID_SOCKET;
	int iResult, iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	bool loop = false;
	bool isGameOn = false;
};