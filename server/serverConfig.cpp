#include "serverConfig.h"

#include <iostream>
#include <fstream>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>


serverConfig::serverConfig() {

}

void serverConfig::Init(HWND hWnd)
{
	 AddrInfo();
	 InitWinSock();
	 CreateSocket();
	 ConfigureServerSocket(hWnd);
	 LinkSocket();
	 ListenSocketMethod();
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

void serverConfig::ConfigureServerSocket(HWND hWnd)
{
	WSAAsyncSelect(ListenSocket, hWnd, WM_SOCKET, FD_ACCEPT | FD_CLOSE);
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
	OutputDebugString("Client connected \n");
}

void serverConfig::ReceiveAndsendData() {
	//while (loop == false) {
	//	//check if client socket is valid
	//	if (ClientSocket != INVALID_SOCKET) {
			// Receive until the peer shuts down the connection
			do {

				iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
				if (iResult > 0) {

					JsonObjectToJsonFile();

					/*printf("\n");
					printf("Bytes received: %d\n", iResult);*/

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
	//	}
	//	if (check == 1) {
	//		iResult = shutdown(ClientSocket, SD_SEND);
	//		if (iResult == SOCKET_ERROR) {
	//			printf("shutdown failed: %d\n", WSAGetLastError());
	//			closesocket(ClientSocket);
	//			WSACleanup();
	//		}
	//		// cleanup
	//		closesocket(ClientSocket);
	//		WSACleanup();
	//		loop = true;
	//	}
	//	ClientSocket = accept(ListenSocket, NULL, NULL);
	//	if (ClientSocket == INVALID_SOCKET) {
	//		printf("accept failed: %d\n", WSAGetLastError());
	//		closesocket(ListenSocket);
	//		WSACleanup();
	//	}

	//}
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
	OutputDebugString("Server disconnected \n");
}

void serverConfig::HandleSocketMessage(WPARAM wParam, LPARAM lParam)
{
	switch (WSAGETSELECTEVENT(lParam)) {
	case FD_ACCEPT:
		AcceptConnexion();
		break;
	case FD_READ:
		ReceiveAndsendData();
		break;
	case FD_CLOSE:
		closesocket(wParam);
		break;
	}
}

void serverConfig::JsonObjectToJsonFile()
{
	//Get string data
	std::string jsonString(recvbuf);

	//parse into json object
	json receivedJson = json::parse(jsonString);
	OutputDebugStringA(jsonString.c_str());
	OutputDebugString("\n");

	//Json object to Json File
	std::fstream jsonFile("Data.json");

	if (jsonFile.is_open()) {

		jsonFile << std::setw(4) << receivedJson << std::endl;

		jsonFile.close();
	}
	else {
		OutputDebugString("Impossible d'ouvrir le fichier \n");
	}

	check = receivedJson["check"];
}

json serverConfig::JsonFileToJsonObject()
{
	//json file to json object
	std::fstream jsonFile("Data.json");

	if (jsonFile.is_open()) {

		json jsonObject = json::parse(jsonFile);

		jsonFile.close();
		return jsonObject;
	}
	else {
		OutputDebugString("Impossible de lire le fichier \n");
	}
}

std::string serverConfig::JsonObjectToString()
{
	//parse json object to string
	std::string data = JsonFileToJsonObject().dump();

	return data;
}
