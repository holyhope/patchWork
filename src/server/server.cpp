//
// Created by Pierre Peronnet on 13/04/2016.
//
#include <stdexcept>
#include <unistd.h>
#include <arpa/inet.h>
#include <sstream>
#include <iostream>
#include "server.h"
#include "../patchwork/common.h"

#define SERVER_VERSION "v1"

#define BUFFER_SIZE 4096

void Server::start() {
    int socketClient;
    socklen_t size;

    _socketServer = socket(AF_INET, SOCK_STREAM, 0);

    if (_socketServer < 0) {
        throw std::runtime_error("Error establishing socket");
    }

    std::cout << std::endl << "=> Socket server has been created..." << std::endl;

    if (0 > _SYS_SOCKET_H_::bind(_socketServer, (struct sockaddr *) &_address, sizeof(_address))) {
        throw std::runtime_error("Error binding connection, the socket has already been established");
    }

    size = sizeof(_address);
    std::cout << "=> Looking for clients..." << std::endl;

    listen(_socketServer, 1);

    while (!_stopped) {
        std::cout << std::endl;
        socketClient = accept(_socketServer, (struct sockaddr *) &_address, &size);

        // first check if it is valid or not
        if (socketClient < 0) {
            throw std::runtime_error("Error on accepting");
        }

        manageClient(socketClient);

        std::cout << _image.encode() << std::endl;
    }
}

void Server::doPutAction(std::istringstream &in) {
    Figure *imageTmp;
    std::fpos<mbstate_t> pos = in.tellg();
    char buffer[BUFFER_SIZE];

    try {
        imageTmp = Figure::decode(in);
        _image.add(*imageTmp);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        in.seekg(pos);
        in >> buffer;
        std::cerr << " >> " << buffer << std::endl;
    }
}

void Server::doGetAction(const int socketClient) const {
    std::string message = _image.encode();
    send(socketClient, message.c_str(), message.size() * sizeof(char), 0);
}

void Server::manageClient(const int socketClient) {
    ssize_t received;
    std::istringstream in;
    char buffer[BUFFER_SIZE];
    char action[BUFFER_SIZE];

    std::cout << "=> Connected with #" << socketClient << " (" << std::string(inet_ntoa(_address.sin_addr)) << ")" <<
    std::endl;

    sprintf(buffer, "Serveur %s\n", SERVER_VERSION);
    send(socketClient, buffer, BUFFER_SIZE * sizeof(char), 0);

    std::memset(buffer, '\0', BUFFER_SIZE * sizeof(char));
    received = recv(socketClient, buffer, BUFFER_SIZE - 1, 0);

    if (0 > received) {
        std::cerr << "Error with #" << socketClient << std::endl;
    } else {
        in = std::istringstream(buffer);
        in.getline(action, BUFFER_SIZE);
        if (0 == strcmp(action, GET_ACTION)) {
            std::cerr << "Action " << action << " for #" << socketClient << std::endl;
            doGetAction(socketClient);
        } else if (0 == strcmp(action, PUT_ACTION)) {
            std::cerr << "Action " << action << " for #" << socketClient << std::endl;
            doPutAction(in);
        } else {
            std::cerr << "Unknow action (" << buffer << ") for #" << socketClient << std::endl;
        }
    }

    if (0 > close(socketClient)) {
        std::cerr << "Cannot close connection with #" << socketClient << std::endl;
    } else {
        std::cout << "=> Connection terminated with #" << socketClient << std::endl;
    }
}

void Server::stop() {
    _stopped = true;
    close(_socketServer);
}