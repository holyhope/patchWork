//
// Created by Pierre Peronnet on 13/04/2016.
//
#include <stdexcept>
#include <unistd.h>
#include <arpa/inet.h>
#include <sstream>
#include <iostream>
#include "server.h"
#include "../patchwork/figure.hpp"
#include "../patchwork/Image.h"

#define SERVER_VERSION "v1"

#define BUFFER_SIZE 4096

void Server::start() {
    socklen_t size;
    int clientCount = 1;
    ssize_t received;
    int client = socket(AF_INET, SOCK_STREAM, 0);
    char buffer[BUFFER_SIZE];
    std::string message;
    Image image;

    if (client < 0) {
        throw std::runtime_error("Error establishing socket");
    }

    std::cout << std::endl << "=> Socket server has been created..." << std::endl;

    if (0 > _SYS_SOCKET_H_::bind(client, (struct sockaddr *) &_address, sizeof(_address))) {
        throw std::runtime_error("Error binding connection, the socket has already been established");
    }

    size = sizeof(_address);
    std::cout << "=> Looking for clients..." << std::endl;

    listen(client, 1);

    while (!_stopped) {
        _socket = accept(client, (struct sockaddr *) &_address, &size);

        // first check if it is valid or not
        if (_socket < 0) {
            throw std::runtime_error("Error on accepting");
        }

        std::cout << "=> Connected with the client #" << clientCount << std::endl;

        sprintf(buffer, "Serveur %s\n", SERVER_VERSION);
        send(_socket, buffer, BUFFER_SIZE, 0);

        received = recv(_socket, buffer, BUFFER_SIZE - 1, 0);
        if (0 > received) {
            std::cerr << "Error with client #" << clientCount << std::endl;
        } else {
            buffer[received] = '\0';
            std::istringstream in(buffer);
            try {
                image.add(*Figure::decode(in));
                message = image.encode();
                send(_socket, message.c_str(), message.size(), 0);
            } catch (const std::exception &e) {
                std::cerr << e.what() << std::endl << " >>\t" << buffer << std::endl;
                std::cerr << " >>\t";
                while (in.good()) {
                    char c;
                    
                    in.get(c);
                    if (!in.eof()) {
                        std::cerr << c;
                    }
                }
                std::cout << std::endl;
            }
        }

        if (0 > close(_socket)) {
            std::cerr << "Cannot close connection with #" << clientCount << std::endl;
        } else {
            std::cout << std::endl << "=> Connection terminated with IP " <<
            std::string(inet_ntoa(_address.sin_addr)) << std::endl;
        }
    }

    close(client);
}

void Server::stop() {
    _stopped = true;
    close(_socket);
}