#include "serverConfig.h"
#include <iostream>

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
		printf("WSAStartup failed: %d\n", iResult);
		//return 1;
	}
}

void serverConfig::CreateSocket() {
	// Resolve the local address and port to be used by the server
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		//return 1;
	}

	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	//check if socket in invalid
	if (ListenSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		//return 1;
	}
}

void serverConfig::LinkSocket() {
	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
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
		printf("Listen failed with error: %ld\n", WSAGetLastError());
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
		printf("accept failed: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		//return 1;
	}
}

void serverConfig::ReceiveAndsendData() {
	while (loop == false) {
		//check if client socket is valid
		if (ClientSocket != INVALID_SOCKET) {
			// Receive until the peer shuts down the connection
			do {

				iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
				if (iResult > 0) {

					//recvbuf[iResult] = '\0';
					std::string jsonString(recvbuf);

					std::cout << "Chaine JSON recue : " << jsonString << std::endl;

					json receivedJson = json::parse(jsonString);
					OutputDebugStringA(jsonString.c_str());
					OutputDebugString("\n");

					check = receivedJson["check"];
					OutputDebugStringA(jsonString.c_str());
					// Vous pouvez maintenant accéder aux valeurs de l'objet JSON
					//bool happy = receivedJson["happy"];
					//float pi = receivedJson["pi"];

					// Faites quelque chose avec les valeurs reçues
					//std::cout << "happy: " << happy << ", pi: " << pi << std::endl;

					printf("\n");
					printf("Bytes received: %d\n", iResult);

					// Echo the buffer back to the sender
					iSendResult = send(ClientSocket, recvbuf, iResult, 0);
					if (iSendResult == SOCKET_ERROR) {
						printf("send failed: %d\n", WSAGetLastError());
						closesocket(ClientSocket);
						WSACleanup();
					}
					printf("Bytes sent: %d\n", iSendResult);
				}
				else if (iResult == 0) {
					printf("Connection closing...\n");
				}
				else {
					printf("recv failed: %d\n", WSAGetLastError());
					closesocket(ClientSocket);
					WSACleanup();
				}
			} while (iResult > 0);
		}
		if (check == 1) {
			iResult = shutdown(ClientSocket, SD_SEND);
			if (iResult == SOCKET_ERROR) {
				printf("shutdown failed: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
			}
			// cleanup
			closesocket(ClientSocket);
			WSACleanup();
			loop = true;
		}
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) {
			printf("accept failed: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
		}

	}
}

void serverConfig::Shutdown() {
	// shutdown the send half of the connection since no more data will be sent
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		//return 1;
	}

	// cleanup
	closesocket(ListenSocket);
	WSACleanup();
}