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
	}
}

void serverConfig::CreateSocket() {
	// Resolve the local address and port to be used by the server
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
	}

	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	//check if socket in invalid
	if (ListenSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
	}
}

void serverConfig::ConfigureServerSocket(HWND hWnd)
{
	WSAAsyncSelect(ListenSocket, hWnd, WM_USER, FD_ACCEPT | FD_READ | FD_CLOSE);
}

void serverConfig::LinkSocket() {
	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
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

bool serverConfig::AcceptPlayerOne() {
	// Accept a client socket
	ClientPlayerOne = accept(ListenSocket, NULL, NULL);
	if (ClientPlayerOne != INVALID_SOCKET) {
		OutputDebugString("Player one connected \n");
		return true;
	}
	else if (ClientPlayerOne == INVALID_SOCKET) {
		OutputDebugString("accept failed: %d\n");
		closesocket(ListenSocket);
		WSACleanup();
		return false;
	}
}

bool serverConfig::AcceptPlayerTwo()
{
	ClientPlayerTwo = accept(ListenSocket, NULL, NULL);
	if (ClientPlayerTwo != INVALID_SOCKET) {
		OutputDebugString("Player two connected \n");
		return true;
	}
	else if (ClientPlayerTwo == INVALID_SOCKET) {
		OutputDebugString("accept failed: %d\n");
		closesocket(ListenSocket);
		WSACleanup();
		return false;
	}
}

void serverConfig::SendDataPlayerOne() {
	std::string sendbuf = JsonObjectToString();

	iSendResult = send(ClientPlayerOne, sendbuf.c_str(), static_cast<int>(sendbuf.length()), 0);
	if (iSendResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(ClientPlayerOne);
		WSACleanup();
	}
	printf("Bytes sent: %d\n", iSendResult);
}

void serverConfig::ReceiveDataPlayerOne() {
	do {
		iResult = recv(ClientPlayerOne, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			JsonObjectToJsonFile();
		}
		else if (iResult == 0) {
			printf("Connection closing...\n");
		}
		else {
			printf("recv failed: %d\n", WSAGetLastError());
			closesocket(ClientPlayerOne);
			WSACleanup();
		}

	} while (iResult > 0);
}

void serverConfig::SendDataPlayerTwo() {
	std::string sendbuf = JsonObjectToString();

	iSendResult = send(ClientPlayerTwo, sendbuf.c_str(), static_cast<int>(sendbuf.length()), 0);
	if (iSendResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(ClientPlayerTwo);
		WSACleanup();
	}
	printf("Bytes sent: %d\n", iSendResult);
}

void serverConfig::ReceiveDataPlayerTwo() {
	do {
		iResult = recv(ClientPlayerTwo, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			JsonObjectToJsonFile();
		}
		else if (iResult == 0) {
			printf("Connection closing...\n");
		}
		else {
			printf("recv failed: %d\n", WSAGetLastError());
			closesocket(ClientPlayerTwo);
			WSACleanup();
		}

	} while (iResult > 0);
}

void serverConfig::SendDataAll()
{
	std::string sendbuf = JsonObjectToString();

	iSendResult = send(ClientPlayerOne, sendbuf.c_str(), static_cast<int>(sendbuf.length()), 0);
	if (iSendResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(ClientPlayerOne);
		WSACleanup();
	}
	printf("Bytes sent: %d\n", iSendResult);
}

void serverConfig::ReceiveDataAll()
{
	do {
		iResult = recv(ClientPlayerTwo, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			JsonObjectToJsonFile();
		}
		else if (iResult == 0) {
			printf("Connection closing...\n");
		}
		else {
			printf("recv failed: %d\n", WSAGetLastError());
			closesocket(ClientPlayerTwo);
			WSACleanup();
		}

	} while (iResult > 0);
}

void serverConfig::ShutdownPlayerOne()
{
	// shutdown the send half of the connection since no more data will be sent
	iResult = shutdown(ClientPlayerOne, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ClientPlayerOne);
		WSACleanup();
	}
	closesocket(ClientPlayerOne);
	WSACleanup();
}

void serverConfig::ShutdownPlayerTwo()
{
	iResult = shutdown(ClientPlayerTwo, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ClientPlayerTwo);
		WSACleanup();
	}
	closesocket(ClientPlayerTwo);
	WSACleanup();
}

void serverConfig::ShutdownAll() {
	// shutdown the send half of the connection since no more data will be sent
	iResult = shutdown(ClientPlayerOne, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ClientPlayerOne);
		WSACleanup();
	}

	iResult = shutdown(ClientPlayerTwo, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ClientPlayerTwo);
		WSACleanup();
	}

	// cleanup
	closesocket(ClientPlayerOne);
	closesocket(ClientPlayerTwo);
	closesocket(ListenSocket);
	WSACleanup();
	OutputDebugString("All disconnected \n");
}

void serverConfig::HandleSocketMessage(WPARAM wParam, LPARAM lParam)
{
	switch (WSAGETSELECTEVENT(lParam)) {
	case FD_ACCEPT:
		//if (AcceptPlayerOne() == false) {
		//	AcceptPlayerOne();
		//}
		//else if (AcceptPlayerOne() == true) {
		//	AcceptPlayerTwo();
		//}
		AcceptPlayerOne();
		break;
	case FD_READ:
		ReceiveDataPlayerOne();
		//ReceiveDataAll();
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
