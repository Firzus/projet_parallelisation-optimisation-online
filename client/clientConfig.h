#pragma once
#include "framework.h"

#include "json.hpp"
using json = nlohmann::json;

#include <winsock2.h>


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

	void Init(HWND hWnd);
	//create client 
	void AddrInfo();
	void InitWinSock();
	void CreateSocket();
	void ConfigureClientSocket(HWND hWnd);
	void ConnectSocketMethod();
	// Handle message
	void HandleSocketMessage(WPARAM wParam, LPARAM lParam);

	void sendJson();
	string ReceiveData();
	void SendData(const string& data);
	void CloseConnection();
	int ShutdownConnection(int how);
	void Shutdown();
	// cleanup
	void Cleanup();

private:
	void JsonStringToJsonObject();

	Data da;
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;

	json data = 
	{
		{"Player1", {
			{"PlayerName", da.GetPlayerName()},
			{"PlayerToken", "O"}
		}},
		{"Player2", {
			{"PlayerName", da.GetPlayerName()},
			{"PlayerToken", "X"}
		}},
		{"CurrentPlayer", da.GetCurrentToken()},
		{"TokenPos", da.GetBoardAsJson()},
		{"WinnerName", da.GetWinner()},
		{"Connection", da.GetConnection()},
		{"IsGameOver", da.GetGameOver()}
	};

	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;
	char recvbuf[DEFAULT_BUFLEN];
};