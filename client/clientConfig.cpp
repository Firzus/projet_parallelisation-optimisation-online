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
		//printf("WSAStartup failed: %d\n", iResult);
		MessageBox(NULL, L"WSAStartup failed:" + iResult, 0, 0);
		//return 1;
	}
}

void clientConfig::CreateSocket() {

	// Resolve the server address and port 
	iResult = getaddrinfo("192.168.1.13", DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		//printf("getaddrinfo failed: %d\n", iResult);
		MessageBox(NULL, L"getaddrinfo failed:" + iResult, 0, 0);
		WSACleanup();
		//return 1;
	}

	ptr = result;


	// Create a client SOCKET for connecting to server
	
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
		ptr->ai_protocol);

	// verify if the socket is valid
	if (ConnectSocket == INVALID_SOCKET) {
		//printf("Error at socket(): %ld\n", WSAGetLastError());
		MessageBox(NULL, L"Error at socket():" + WSAGetLastError(), 0, 0);
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
		//printf("Unable to connect to server!\n");
		MessageBox(NULL, L"Unable to connect to server!", 0, 0);
		WSACleanup();
		//return 1;
	}
}

void clientConfig::SendAndReceiveData() {
	// Send an initial buffer
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		//printf("send failed: %d\n", WSAGetLastError());
		MessageBox(NULL, L"send failed:" + WSAGetLastError(), 0, 0);
		closesocket(ConnectSocket);
		WSACleanup();
		//return 1;
	}

	//printf("Bytes Sent: %ld\n", iResult);
	MessageBox(NULL, L"Bytes Sent:" + iResult, 0, 0);


	// shutdown the send half of the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		//printf("shutdown failed: %d\n", WSAGetLastError());
		MessageBox(NULL, L"shutdown failed:" + WSAGetLastError(), 0, 0);
		closesocket(ConnectSocket);
		WSACleanup();
		//return 1;
	}

	// Receive data until the server closes the connection
	do {
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			//printf("Bytes received: %d\n", iResult);
			MessageBox(NULL, L"Bytes received:" + iResult, 0, 0);
		}

		else if (iResult == 0){
			//printf("Connection closed\n");
			MessageBox(NULL, L"Connection closed", 0, 0);
		}
		else {
			//printf("recv failed: %d\n", WSAGetLastError());
			MessageBox(NULL, L"recv failed:" + WSAGetLastError(), 0, 0);
		}
	} while (iResult > 0);
}

void clientConfig::Shutdown() {

	// shutdown the send half of the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		//printf("shutdown failed: %d\n", WSAGetLastError());
		MessageBox(NULL, L"shutdown failed:" + WSAGetLastError(), 0, 0);
		closesocket(ConnectSocket);
		WSACleanup();
		//return 1;
	}

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();
}