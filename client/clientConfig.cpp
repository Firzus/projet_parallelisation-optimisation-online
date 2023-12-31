#include "clientConfig.h"
#include "Game.h"

void clientConfig::Init() {
	AddrInfo();
	InitWinSock();
	CreateSocket();
	ConnectSocketMethod();
	SendAndReceiveData();
}

void clientConfig::AddrInfo() 
{
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
}

void clientConfig::InitWinSock() 
{
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
	iResult = getaddrinfo(DEFAULT_IP, DEFAULT_PORT, &hints, &result);
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

void clientConfig::ConnectSocketMethod() 
{
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

	GameManager::GetInstance().SetConnection(true);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		GameManager::GetInstance().SetConnection(false);
		WSACleanup();
	}
}

void clientConfig::SendData(const string& data) {
	iResult = send(ConnectSocket, data.c_str(), static_cast<int>(data.length()), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		CloseConnection();
		throw runtime_error("Send failed");
	}
	printf("Bytes Sent: %ld\n", iResult);
}

string clientConfig::ReceiveData() {
	string receivedData;
	do {
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			receivedData.append(recvbuf, iResult);
		}
		else if (iResult == 0) {
			printf("Connection closed\n");
			break;
		}
		else {
			printf("recv failed: %d\n", WSAGetLastError());
			CloseConnection();
			throw runtime_error("Receive failed");
		}
	} while (iResult > 0);

	return receivedData;
}

void clientConfig::SendAndReceiveData() {
	try {
		string sendbuf = data.dump();
		OutputDebugStringA(sendbuf.c_str());
		SendData(sendbuf);
		ShutdownConnection(SD_SEND);
		string receivedData = ReceiveData();
	}
	catch (const runtime_error& e) {
		cerr << e.what() << endl;
	}
}

void clientConfig::CloseConnection() {
	closesocket(ConnectSocket);
	ConnectSocket = INVALID_SOCKET;
	WSACleanup();
}

int clientConfig::ShutdownConnection(int how) {
	iResult = shutdown(ConnectSocket, how);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		CloseConnection();
	}
	return iResult;
}

void clientConfig::Shutdown() 
{
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