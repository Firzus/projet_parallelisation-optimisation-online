#include "serverConfig.h"

#include <iostream>
#include <fstream>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

serverConfig::serverConfig() {}

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
void serverConfig::AcceptConnection(int clientID)
{
	int clientAddressSize = sizeof(clientAddress);

	clientIncoming = accept(ListenSocket, (struct sockaddr*)&clientAddress, &clientAddressSize);
	if (clientIncoming != INVALID_SOCKET) {
		OutputDebugString("\nPlayer connected\n");

		OutputDebugStringA(("Client address: " + std::to_string(clientAddress.sin_addr.s_addr) + ", port: " + std::to_string(clientAddress.sin_port) + "\n").c_str());
	}
	else if (clientIncoming == INVALID_SOCKET) {
		OutputDebugStringA("Erreur lors de l'acceptation de la connexion du client : " + WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
	}
}

bool serverConfig::Check()
{
	if (PlayerOneAddress.sin_addr.s_addr && PlayerTwoAddress.sin_addr.s_addr != 0) {
		OutputDebugStringA(("\n" + std::to_string(PlayerOneAddress.sin_addr.s_addr) + "\n").c_str());
		OutputDebugStringA(("\n" + std::to_string(PlayerTwoAddress.sin_addr.s_addr) + "\n").c_str());
		OutputDebugString("Players are connected");
		// send both clients check ready variable
		int sendCheck = 0, sendCheck2 = 0;
		std::string buf = "1";//stoi(buf) to parse to int

		sendCheck = send(PlayerOne, buf.c_str(), static_cast<int>(buf.length()), 0);
		if (sendCheck == SOCKET_ERROR) {
			OutputDebugStringA(("Player ne send check failed: %d\n" + std::to_string(WSAGetLastError()) + "\n").c_str());
			closesocket(PlayerOne);
			WSACleanup();
		}
		Shutdown(1);
		sendCheck2 = send(PlayerTwo, buf.c_str(), static_cast<int>(buf.length()), 0);
		if (sendCheck2 == SOCKET_ERROR) {
			OutputDebugStringA(("Player two send check failed: %d\n" + std::to_string(WSAGetLastError()) + "\n").c_str());
			closesocket(PlayerOne);
			WSACleanup();
		}
		Shutdown(2);
		return true;
	}
	else {

		return false;
	}
}

void serverConfig::Checkturn()
{
	//bool turn = false | is Player One to play and send his json data, Player Two can't send anything
	//bool turn = true | is Player Two to play and send his json data, Player One can't send anyhting
	if (Check() == true) {
		OutputDebugString("check is true");

		switch (turn) {
		case false://Player One to play
			ReceiveDataPlayerOne();
			SendDataPlayerTwo(1);
			//store data to json file
			StoreJsonObjectToJsonFile();
			turn = true;//switch turn
			break;
		case true:// Player Two to play
			ReceiveDataPlayerTwo();
			SendDataPlayerOne(1);
			//store data to json file
			StoreJsonObjectToJsonFile();
			turn = false;//switch turn
			break;
		}
	}
}

void serverConfig::SendDataPlayerOne(int valueConvert) {
	std::string sendbuf = JsonObjectToString(valueConvert);
	OutputDebugStringA(sendbuf.c_str());

	iSendResult = send(PlayerOne, sendbuf.c_str(), static_cast<int>(sendbuf.length()), 0);
	if (iSendResult == SOCKET_ERROR) {
		printf("Player one send failed: %d\n", WSAGetLastError());
		closesocket(PlayerOne);
		WSACleanup();
	}
	Shutdown(1);
}

void serverConfig::SendDataPlayerTwo(int valueConvert) {
	std::string sendbuf = JsonObjectToString(valueConvert);
	OutputDebugStringA(sendbuf.c_str());

	iSendResult = send(PlayerTwo, sendbuf.c_str(), static_cast<int>(sendbuf.length()), 0);
	if (iSendResult == SOCKET_ERROR) {
		printf("Player two send failed: %d\n", WSAGetLastError());
		closesocket(PlayerTwo);
		WSACleanup();
	}
	Shutdown(2);
}

void serverConfig::ReceiveDataPlayerOne() {

	iResult = recv(PlayerOne, recvbuf, recvbuflen, 0);
	if (iResult > 0) {
		RecvBufToJsonObject();
	}
	else if (iResult == 0) {
		OutputDebugString("Player one Connection closing...\n");
	}
	else {
		printf("Player one recv failed: %d\n", WSAGetLastError());
		closesocket(PlayerOne);
		WSACleanup();
	}
}

void serverConfig::ReceiveDataPlayerTwo() {
	iResult = recv(PlayerTwo, recvbuf, recvbuflen, 0);
	if (iResult > 0) {
		RecvBufToJsonObject();
	}
	else if (iResult == 0) {
		OutputDebugString("Player one Connection closing...\n");
	}
	else {
		printf("Player one recv failed: %d\n", WSAGetLastError());
		closesocket(PlayerTwo);
		WSACleanup();
	}
}

void serverConfig::Shutdown(int value) {

	switch (value) {
	case 1:
		iResult = shutdown(PlayerOne, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("Player one shutdown failed: %d\n", WSAGetLastError());
			closesocket(PlayerTwo);
			WSACleanup();
		}
		break;
	case 2:
		iResult = shutdown(PlayerTwo, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("Player two shutdown failed: %d\n", WSAGetLastError());
			closesocket(PlayerTwo);
			WSACleanup();
		}
		break;
	case 3:
		iResult = shutdown(ListenSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("Server shutdown failed: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
		}
		break;
	}

}

void serverConfig::Cleanup(int value) {
	// cleanup
	switch (value) {
	case 1:
		closesocket(PlayerOne);
		OutputDebugString("Player one disconnected \n");
		break;
	case 2:
		closesocket(PlayerTwo);
		OutputDebugString("Player two disconnected \n");
		break;
	case 3:
		closesocket(PlayerOne);
		closesocket(PlayerTwo);
		closesocket(ListenSocket);
		OutputDebugString("All disconnected \n");
		break;
	}
	WSACleanup();
}

void serverConfig::HandleSocketMessage(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (WSAGETSELECTEVENT(lParam)) {
	case FD_ACCEPT:
		if (clientCounter < 2) {
			AcceptConnection(clientCounter);
			if (clientCounter == 0) {
				PlayerOne = clientIncoming;
				memcpy(&PlayerOneAddress, &clientAddress, sizeof(sockaddr_in));
				PlayerOneIsConnected = true;
			}
			else if (clientCounter == 1) {
				PlayerTwo = clientIncoming;
				memcpy(&PlayerTwoAddress, &clientAddress, sizeof(sockaddr_in));
				PlayerTwoIsConnected = true;
			}
			clientCounter++;
			if (clientCounter >= 2) {
				WSAAsyncSelect(ListenSocket, hWnd, WM_USER, FD_READ | FD_CLOSE);
			}
		}
		Check();
		break;
	case FD_READ:
		test();
		//Checkturn();
		break;
	case FD_CLOSE:
		closesocket(wParam);
		break;
	}
}

void serverConfig::test()
{
	ReceiveDataPlayerOne();
	StoreJsonObjectToJsonFile();
}

json serverConfig::RecvBufToJsonObject()
{
	bool statePlayerOne = PlayerOneIsConnected;
	bool statePlayerTwo = PlayerTwoIsConnected;
	//Get string data
	std::string jsonString(recvbuf);

	//parse into json object
	json jsonObject = json::parse(jsonString);
	OutputDebugStringA(jsonString.c_str());
	OutputDebugString("\n");

	jsonObject["player1"]["isConnected"] = PlayerOneIsConnected;
	jsonObject["player2"]["isConnected"] = PlayerTwoIsConnected;

	return jsonObject;
}

json serverConfig::JsonFileToJsonObject()
{
	try {
		std::fstream jsonFile("data.json");

		if (!jsonFile.is_open()) {
			throw std::runtime_error("Impossible d'ouvrir le fichier Data.json");
		}

		json jsonObject = json::parse(jsonFile);
		jsonFile.close();
		return jsonObject;

	}
	catch (const json::parse_error& e) {
		std::cerr << "Erreur de parsing JSON : " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Erreur : " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Erreur inconnue lors de la lecture du fichier JSON" << std::endl;
	}

	return json{};
}

std::string serverConfig::JsonObjectToString(int value)
{
	try {
		std::string data;
		switch (value) {
		case 0:
			data = JsonFileToJsonObject().dump();
			break;
		case 1:
			data = RecvBufToJsonObject().dump();
			break;
		}
		return data;

	}
	catch (const nlohmann::json::exception& e) {
		std::cerr << "Erreur de traitement JSON : " << e.what() << std::endl;
		return "";
	}
	catch (const std::exception& e) {
		std::cerr << "Erreur standard : " << e.what() << std::endl;
		return "";
	}
	catch (...) {
		std::cerr << "Erreur inconnue lors du traitement JSON" << std::endl;
		return "";
	}
}

void serverConfig::StoreJsonObjectToJsonFile()
{
	//Json object to Json File
	std::fstream jsonFile("data.json");

	if (jsonFile.is_open()) {

		jsonFile << std::setw(4) << RecvBufToJsonObject() << std::endl;

		jsonFile.close();
	}
	else {
		OutputDebugString("Impossible d'ouvrir le fichier \n");
	}
}
