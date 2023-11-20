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

//int main() {
//    int server_fd, new_socket;
//    struct sockaddr_in address;
//    int addrlen = sizeof(address);
//    char buffer[1024] = { 0 };
//
//    // Création du socket
//    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
//        std::cerr << "Erreur lors de la création du socket" << std::endl;
//        return -1;
//    }
//
//    // Configuration de l'adresse
//    address.sin_family = AF_INET;
//    address.sin_addr.s_addr = INADDR_ANY;
//    address.sin_port = htons(PORT);
//
//    // Attachement du socket au port
//    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
//        std::cerr << "Erreur lors du bind" << std::endl;
//        return -1;
//    }
//
//    // Écoute des connexions entrantes
//    if (listen(server_fd, 3) < 0) {
//        std::cerr << "Erreur lors de l'écoute" << std::endl;
//        return -1;
//    }
//
//    std::cout << "Serveur en attente sur le port " << PORT << std::endl;
//
//    while (true) {
//        // Acceptation de la connexion entrante
//        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
//            std::cerr << "Erreur lors de l'acceptation" << std::endl;
//            return -1;
//        }
//
//        // Lecture des données du client
//        listen(new_socket, 1024);
//        std::cout << "Requête : " << buffer << std::endl;
//
//        // Réponse au client
//        std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><h1>Hello, World!</h1></body></html>\n";
//        send(new_socket, response.c_str(), response.length(), 0);
//
//        // Fermeture du socket client
//        closesocket(new_socket);
//        WSACleanup();
//    }
//
//    return 0;
//}
