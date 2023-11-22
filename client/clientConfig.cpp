#include "clientConfig.h"
#include "Game.h"
#define MSG_CLIENT_CONNECT (WM_USER+1)

void clientConfig::Init(HWND hWnd) {
	AddrInfo();
	InitWinSock();
	CreateSocket();
	ConfigureClientSocket(hWnd);
	ConnectSocketMethod();
	SendData();
}

void clientConfig::AddrInfo() 
{
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
}

void clientConfig::InitWinSock() 
{
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		//return 1;
	}
}

void clientConfig::CreateSocket()
{
	// Resolve the server address and port 
	iResult = getaddrinfo(DEFAULT_IP, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		//return 1;
	}

	ptr = result;

	// Create a client SOCKET for connecting to server
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
		ptr->ai_protocol);

	// verify if the socket is valid
	if (ConnectSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		//return 1;
	}
}

void clientConfig::ConfigureClientSocket(HWND hWnd)
{
	WSAAsyncSelect(ConnectSocket, hWnd, MSG_CLIENT_CONNECT, FD_CONNECT | FD_READ);
}

void clientConfig::ConnectSocketMethod() 
{
	// Connect to server.
	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	// Should really try the next address returned by getaddrinfo
	// if the connect call failed
	// But for this simple example we just free the resources
	// returned by getaddrinfo and print an error message
	freeaddrinfo(result);

	GameManager::GetInstance().SetConnection(true);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		GameManager::GetInstance().SetConnection(false);
		WSACleanup();
	}
}

void clientConfig::HandleSocketMessage(WPARAM wParam, LPARAM lParam)
{
	switch (WSAGETSELECTEVENT(lParam)) {
	case FD_CONNECT:
		OutputDebugString("\nconnected\n");
		break;
	case FD_READ:
		ReceiveData();
		break;
	case FD_CLOSE:
		closesocket(wParam);
		break;
	}
}

void clientConfig::SendData()
{
	std::string sendbuf = data.dump();
	OutputDebugStringA(sendbuf.c_str());
	// Utiliser sendbuf dans la port�e actuelle
	iResult = send(ConnectSocket, sendbuf.c_str(), static_cast<int>(sendbuf.length()), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		
		closesocket(ConnectSocket);
		WSACleanup();
		//return 1;
	}
	Shutdown();
}

void clientConfig::ReceiveData()
{
	//Receive data until the server closes the connection
	do {
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			JsonStringToJsonObject();
		}
		else if (iResult == 0) {
			//Shutdown();
			printf("Connection closed\n");

		}
		else {
			printf("recv failed: %d\n", WSAGetLastError());

		}
	} while (iResult > 0);
}


void clientConfig::Shutdown() {

	// shutdown the send half of the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		//return 1;
	}

	// cleanup
	//closesocket(ConnectSocket);
	WSACleanup();
}

void clientConfig::JsonStringToJsonObject()
{
	//Get string data
	std::string jsonString(recvbuf);

	//parse into json object
	data = json::parse(jsonString);
	OutputDebugStringA(jsonString.c_str());
	OutputDebugString("\n");
}
