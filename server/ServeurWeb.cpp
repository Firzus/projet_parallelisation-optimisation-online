#include "ServeurWeb.h"

ServeurWeb::ServeurWeb() {}

void ServeurWeb::Init()
{
	AddrInfo();
	InitWinSock();
	CreateSocket();
	LinkSocket();
	ListenSocketMethod();

	while (true) {
		std::string requestUrl = AcceptConnexion();
		std::string filePath;

		if (requestUrl == "/data.json") {
			filePath = "data.json";
		}

		SendHTMLResponse(filePath);
	}

	Shutdown();
}

std::string ServeurWeb::AcceptConnexion()
{
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET)
	{
		printf("accept failed: %d\n", WSAGetLastError());
		// Gestion de l'erreur
		return "";
	}

	// Recevoir la requ�te HTTP du client
	char buffer[1024]; // Assurez-vous que ce buffer est suffisamment grand
	int bytesReceived = recv(ClientSocket, buffer, 1024, 0);
	if (bytesReceived == SOCKET_ERROR || bytesReceived == 0)
	{
		// Gestion de l'erreur ou de la connexion ferm�e
		return "";
	}

	// Convertir le buffer en string pour une analyse plus facile
	std::string httpRequest(buffer, bytesReceived);

	std::string requestUrl = ParseHttpRequest(httpRequest);

	return requestUrl;
}

std::string ServeurWeb::ParseHttpRequest(const std::string& httpRequest)
{
	std::istringstream requestStream(httpRequest);
	std::string requestLine;
	std::getline(requestStream, requestLine);

	std::istringstream lineStream(requestLine);
	std::string method;
	std::string url;

	lineStream >> method >> url;

	return url;
}

void ServeurWeb::AddrInfo()
{
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
}

void ServeurWeb::InitWinSock()
{
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		// return 1;
	}
}

void ServeurWeb::CreateSocket()
{
	// Resolve the local address and port to be used by the server
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		// return 1;
	}

	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	// check if socket in invalid
	if (ListenSocket == INVALID_SOCKET)
	{
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		// return 1;
	}
}

void ServeurWeb::LinkSocket()
{
	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
	}

	// release the memory
	freeaddrinfo(result);
}

void ServeurWeb::ListenSocketMethod()
{

	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
	}
}

void ServeurWeb::HandleHTTPRequest(const std::string& requestUrl)
{
	if (requestUrl == "/data.json")
	{
		std::string filePath = "data.json";
		SendHTMLResponse(filePath);
	}
	else
	{
		// Vous pouvez choisir d'envoyer une réponse 404 ici
		SendNotFoundResponse();
	}
}

void ServeurWeb::SendNotFoundResponse()
{
	std::string httpResponse = "HTTP/1.0 404 Not Found\r\nContent-Length: 0\r\n\r\n";
	send(ClientSocket, httpResponse.c_str(), httpResponse.length(), 0);
	closesocket(ClientSocket);
}

void ServeurWeb::SendHTMLResponse(const std::string& filePath)
{
	// V�rifier si le fichier demand� est data.json
	OutputDebugStringA(filePath.c_str());

	std::string requestedFile = filePath; // Cette variable doit �tre d�termin�e en fonction de la requ�te HTTP re�ue
	std::string fileExtension = requestedFile.substr(requestedFile.find_last_of(".") + 1);

	// Ouverture du fichier en fonction de son type
	std::ifstream file(filePath, std::ios::in | std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << "Unable to open file: " << filePath << std::endl;
		return;
	}

	file.seekg(0, std::ios::end);
	std::streamsize fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	std::string httpResponse;

	// Cr�er l'en-t�te HTTP en fonction du type de fichier
	if (fileExtension == "json")
	{
		httpResponse = "HTTP/1.0 200 OK\r\nContent-Type: application/json\r\nContent-Length: " + std::to_string(fileSize) + "\r\n\r\n";
	}
	else
	{
		// Pour les autres types de fichiers (comme HTML)
		httpResponse = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nContent-Length: " + std::to_string(fileSize) + "\r\n\r\n";
	}

	// Lire le contenu du fichier
	std::vector<char> fileContent(static_cast<size_t>(fileSize));
	if (file.read(fileContent.data(), fileSize))
	{
		httpResponse.append(fileContent.begin(), fileContent.end());
	}
	else
	{
		std::cerr << "Failed to read the file content." << std::endl;
		return;
	}

	// Envoyer la r�ponse HTTP
	int iSendResult = send(ClientSocket, httpResponse.c_str(), httpResponse.length(), 0);
	if (iSendResult == SOCKET_ERROR)
	{
		std::cerr << "send failed: " << WSAGetLastError() << std::endl;
	}

	// Fermez la socket ici après avoir envoyé la réponse
	closesocket(ClientSocket);
}

void ServeurWeb::Shutdown()
{
	// shutdown the send half of the connection since no more data will be sent
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		// return 1;
	}

	// cleanup
	closesocket(ListenSocket);
	WSACleanup();
}
