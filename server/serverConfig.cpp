#include "serverConfig.h"

serverConfig::serverConfig()
{
	AddrInfo();
	InitWinSock();
	CreateSocket();
	LinkSocket();
	ListenSocketMethod();
	AcceptConnexion();
	ReceiveAndsendData();
	Shutdown();
}

void serverConfig::AddrInfo()
{
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
}

void serverConfig::InitWinSock() {
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		//printf("WSAStartup failed: %d\n", iResult);
		MessageBox(NULL, L"WSAStartup failed:" + iResult, 0, 0);
		//return 1;
	}
}

void serverConfig::CreateSocket() {
	// Resolve the local address and port to be used by the server
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		//printf("getaddrinfo failed: %d\n", iResult);
		MessageBox(NULL, L"getaddrinfo failed:" + iResult, 0, 0);
		WSACleanup();
		//return 1;
	}

	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	//check if socket in invalid
	if (ListenSocket == INVALID_SOCKET) {
		//printf("Error at socket(): %ld\n", WSAGetLastError());
		MessageBox(NULL, L"Error at socket() failed:" + WSAGetLastError(), 0, 0);
		freeaddrinfo(result);
		WSACleanup();
		//return 1;
	}
}

void serverConfig::LinkSocket() {
	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		//printf("bind failed with error: %d\n", WSAGetLastError());
		MessageBox(NULL, L"bind failed with error:" + WSAGetLastError(), 0, 0);
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		//return 1;
	}

	// release the memory 
	freeaddrinfo(result);
}

void serverConfig::ListenSocketMethod() {

	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		//printf("Listen failed with error: %ld\n", WSAGetLastError());
		MessageBox(NULL, L"Listen failed with error:" + WSAGetLastError(), 0, 0);
		closesocket(ListenSocket);
		WSACleanup();
		//return 1;
	}
}

void serverConfig::AcceptConnexion() {
	ClientSocket = INVALID_SOCKET;

	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		//printf("accept failed: %d\n", WSAGetLastError());
		MessageBox(NULL, L"accept failed:" + WSAGetLastError(), 0, 0);
		closesocket(ListenSocket);
		WSACleanup();
		//return 1;
	}
}

void serverConfig::ReceiveAndsendData() {
	// Receive until the peer shuts down the connection
	do {

		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			//printf("Bytes received: %d\n", iResult);
			MessageBox(NULL, L"Bytes received:" + iResult, 0, 0);

			// Echo the buffer back to the sender
			iSendResult = send(ClientSocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				//printf("send failed: %d\n", WSAGetLastError());
				MessageBox(NULL, L"send failed:" + WSAGetLastError(), 0, 0);
				closesocket(ClientSocket);
				WSACleanup();
				//return 1;
			}
			//printf("Bytes sent: %d\n", iSendResult);
			MessageBox(NULL, L"Bytes sent:" + iSendResult, 0, 0);
		}
		else if (iResult == 0) {
			//printf("Connection closing...\n");
			MessageBox(NULL, L"Connection closing...", 0, 0);
		}
		else {
			//printf("recv failed: %d\n", WSAGetLastError());
			MessageBox(NULL, L"recv failed:" + WSAGetLastError(), 0, 0);
			closesocket(ClientSocket);
			WSACleanup();
			//return 1;
		}

	} while (iResult > 0);
}

void serverConfig::Shutdown() {
	// shutdown the send half of the connection since no more data will be sent
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		//printf("shutdown failed: %d\n", WSAGetLastError());
		MessageBox(NULL, L"shutdown failed:" + WSAGetLastError(), 0, 0);
		closesocket(ClientSocket);
		WSACleanup();
		//return 1;
	}

	// cleanup
	closesocket(ListenSocket);
	WSACleanup();
}