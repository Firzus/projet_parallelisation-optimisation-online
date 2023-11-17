#include "clientConfig.h"

clientConfig::clientConfig()
{
	AddrInfo();
	InitWinSock();
	CreateSocket();
	ConnectSocketMethod();
	SendAndReceiveData();
	Shutdown();
}

void clientConfig::AddrInfo() {
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
}

void clientConfig::InitWinSock() {
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
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
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

void clientConfig::ConnectSocketMethod() {
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

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		//return 1;
	}
}

void clientConfig::SendAndReceiveData() {
	// Convertir l'objet JSON en chaû‹e JSON
	std::string sendbuf = data.dump();

	// Utiliser sendbuf dans la portée actuelle
	iResult = send(ConnectSocket, sendbuf.c_str(), sendbuf.length(), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		
		closesocket(ConnectSocket);
		WSACleanup();
		//return 1;
	}
	MessageBox(NULL, "1", 0, 0);
	printf("Bytes Sent: %ld\n", iResult);
	


	// shutdown the send half of the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		
		closesocket(ConnectSocket);
		WSACleanup();
		//return 1;
	}

	// Receive data until the server closes the connection
	//do {
	//	iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
	//	if (iResult > 0) {
	//		printf("Bytes received: %d\n", iResult);
	//		
	//	}

	//	else if (iResult == 0){
	//		printf("Connection closed\n");
	//		
	//	}
	//	else {
	//		printf("recv failed: %d\n", WSAGetLastError());
	//		
	//	}
	//} while (iResult > 0);
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
	closesocket(ConnectSocket);
	WSACleanup();
}