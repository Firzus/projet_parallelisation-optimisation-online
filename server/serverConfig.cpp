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
		OutputDebugString("Player one accept failed: %d\n");
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
		OutputDebugString("Player two accept failed: %d\n");
		closesocket(ListenSocket);
		WSACleanup();
		return false;
	}
}

void serverConfig::SendDataPlayerOne() {
	std::string sendbuf = JsonObjectToString();

	iSendResult = send(ClientPlayerOne, sendbuf.c_str(), static_cast<int>(sendbuf.length()), 0);
	if (iSendResult == SOCKET_ERROR) {
		printf("Player one send failed: %d\n", WSAGetLastError());
		closesocket(ClientPlayerOne);
		WSACleanup();
	}
}

void serverConfig::ReceiveDataPlayerOne() {
	do {
		iResult = recv(ClientPlayerOne, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			JsonStringToJsonObject();
		}
		else if (iResult == 0) {
			printf("Player one Connection closing...\n");
		}
		else {
			printf("Player one recv failed: %d\n", WSAGetLastError());
			closesocket(ClientPlayerOne);
			WSACleanup();
		}

	} while (iResult > 0);
}

void serverConfig::SendDataPlayerTwo() {
	std::string sendbuf = JsonObjectToString();

	iSendResult = send(ClientPlayerTwo, sendbuf.c_str(), static_cast<int>(sendbuf.length()), 0);
	if (iSendResult == SOCKET_ERROR) {
		printf("Player two send failed: %d\n", WSAGetLastError());
		closesocket(ClientPlayerTwo);
		WSACleanup();
	}
}

void serverConfig::ReceiveDataPlayerTwo() {
	do {
		iResult = recv(ClientPlayerTwo, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			JsonStringToJsonObject();
		}
		else if (iResult == 0) {
			printf("Player two Connection closing...\n");
		}
		else {
			printf("Player two recv failed: %d\n", WSAGetLastError());
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
		printf("Player one send failed: %d\n", WSAGetLastError());
		closesocket(ClientPlayerOne);
		WSACleanup();
	}
	iSendResult2 = send(ClientPlayerTwo, sendbuf.c_str(), static_cast<int>(sendbuf.length()), 0);
	if (iSendResult2 == SOCKET_ERROR) {
		printf("Player two send failed: %d\n", WSAGetLastError());
		closesocket(ClientPlayerOne);
		WSACleanup();
	}
}

void serverConfig::ReceiveDataAll()
{
	do {
		iResult = recv(ClientPlayerOne, recvbuf, recvbuflen, 0);
		iResult2 = recv(ClientPlayerTwo, recvbuf, recvbuflen, 0);
		if (iResult > 0 || iResult2 > 0) {
			JsonStringToJsonObject();
		}
		else if (iResult == 0 || iResult2 == 0) {
			printf("All Connection closing...\n");
		}
		else {
			printf("All recv failed: %d\n", WSAGetLastError());
			closesocket(ClientPlayerOne);
			closesocket(ClientPlayerTwo);
			WSACleanup();
		}

	} while (iResult > 0);
}

void serverConfig::ShutdownPlayerOne()
{
	iResult = shutdown(ClientPlayerOne, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("Player one shutdown failed: %d\n", WSAGetLastError());
		closesocket(ClientPlayerOne);
		WSACleanup();
	}
}

void serverConfig::ShutdownPlayerTwo()
{
	iResult = shutdown(ClientPlayerTwo, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("Player two shutdown failed: %d\n", WSAGetLastError());
		closesocket(ClientPlayerTwo);
		WSACleanup();
	}
}

void serverConfig::ShutdownAll() {
	iResult = shutdown(ClientPlayerOne, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("Player one shutdown failed: %d\n", WSAGetLastError());
		closesocket(ClientPlayerOne);
		WSACleanup();
	}

	iResult = shutdown(ClientPlayerTwo, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("Player two shutdown failed: %d\n", WSAGetLastError());
		closesocket(ClientPlayerTwo);
		WSACleanup();
	}
}

void serverConfig::Cleanup(int nb) {
	// cleanup
	switch (nb) {
	case 1:
		closesocket(ClientPlayerOne);
		OutputDebugString("Player one disconnected \n");
		break;
	case 2:
		closesocket(ClientPlayerTwo);
		OutputDebugString("Player  two disconnected \n");
		break;
	case 3:
		closesocket(ClientPlayerOne);
		closesocket(ClientPlayerTwo);
		closesocket(ListenSocket);
		OutputDebugString("All disconnected \n");
		break;
	}
	WSACleanup();
}

void serverConfig::HandleSocketMessage(WPARAM wParam, LPARAM lParam)
{
	switch (WSAGETSELECTEVENT(lParam)) {
	case FD_ACCEPT:
		AcceptPlayerOne();
		AcceptPlayerTwo();
		break;
	case FD_READ:
		ReceiveDataPlayerOne();
		break;
	case FD_CLOSE:
		closesocket(wParam);
		break;
	}
}

json serverConfig::JsonStringToJsonObject()
{
	//Get string data
	std::string jsonString(recvbuf);

	//parse into json object
	json receivedJson = json::parse(jsonString);
	OutputDebugStringA(jsonString.c_str());
	OutputDebugString("\n");

	return receivedJson;
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
	std::string data = JsonStringToJsonObject().dump();

	return data;
}

void serverConfig::JsonObjectToJsonFile()
{
	//Json object to Json File
	std::fstream jsonFile("Data.json");

	if (jsonFile.is_open()) {

		jsonFile << std::setw(4) << JsonStringToJsonObject() << std::endl;

		jsonFile.close();
	}
	else {
		OutputDebugString("Impossible d'ouvrir le fichier \n");
	}
}
