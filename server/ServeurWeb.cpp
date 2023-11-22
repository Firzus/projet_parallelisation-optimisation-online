#include "ServeurWeb.h"
#include <iostream>
#include <fstream>
#include <string>

ServeurWeb::ServeurWeb()
{
	AddrInfo();
	InitWinSock();
	CreateSocket();
	LinkSocket();
	ListenSocketMethod();
	AcceptConnexion();
	SendHTMLResponse(filePath);
	Shutdown();
}

void ServeurWeb::AddrInfo()
{
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
}

void ServeurWeb::InitWinSock() {
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		//return 1;
	}
}

void ServeurWeb::CreateSocket() {
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

void ServeurWeb::LinkSocket() {
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

void ServeurWeb::ListenSocketMethod() {

	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		//return 1;
	}
}

void ServeurWeb::AcceptConnexion() {
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

void ServeurWeb::SendHTMLResponse(const std::string& filePath) {
	std::ifstream file(filePath, std::ios::in | std::ios::binary | std::ios::ate);
	while (loop == false) {
		//check if client socket is valid
		if (ClientSocket != INVALID_SOCKET) {
			// Receive until the peer shuts down the connection
			do {
				iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
				if (iResult > 0) {
					std::streamsize fileSize = file.tellg();
					file.seekg(0, std::ios::beg);

					std::string httpResponse = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nContent-Length: " + std::to_string(fileSize) + "\r\n\r\n";
					std::string fileContent;
					fileContent.resize(static_cast<size_t>(fileSize));
					file.read(&fileContent[0], fileSize);

					httpResponse += fileContent;

					int iSendResult = send(ClientSocket, httpResponse.c_str(), httpResponse.length(), 0);
					if (iSendResult == SOCKET_ERROR) {
						std::cout << "send failed: " << WSAGetLastError() << std::endl;
					}
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

void ServeurWeb::Shutdown() {
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
