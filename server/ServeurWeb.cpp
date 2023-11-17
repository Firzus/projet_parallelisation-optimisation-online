//#include "ServeurWeb.h"
//
//ServeurWeb::ServeurWeb() {
//
//}
//
//ServeurWeb::~ServeurWeb() {
//
//}
//
//void ServeurWeb::Init(ServeurWeb S) {
//
//}
//
//void ServeurWeb::ProtoHTTP() {
//	
//}

#include <iostream>
#include <string>
#include <sstream>
#include <winsock2.h>
#include <ws2tcpip.h>

const int PORT = 443;  //27015 deja pris !

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };

    // Création du socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Erreur lors de la création du socket" << std::endl;
        return -1;
    }

    // Configuration de l'adresse
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Attachement du socket au port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Erreur lors du bind" << std::endl;
        return -1;
    }

    // Écoute des connexions entrantes
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Erreur lors de l'écoute" << std::endl;
        return -1;
    }

    std::cout << "Serveur en attente sur le port " << PORT << std::endl;

    while (true) {
        // Acceptation de la connexion entrante
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            std::cerr << "Erreur lors de l'acceptation" << std::endl;
            return -1;
        }

        // Lecture des données du client
        listen(new_socket, 1024);
        std::cout << "Requête : " << buffer << std::endl;

        // Réponse au client
        std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><h1>Hello, World!</h1></body></html>\n";
        send(new_socket, response.c_str(), response.length(), 0);

        // Fermeture du socket client
        closesocket(new_socket);
        WSACleanup();
    }

    return 0;
}
