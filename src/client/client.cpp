//
// Created by Pierre Peronnet on 12/04/2016.
//

#include <sys/socket.h>
#include <unistd.h>
#include <sstream>

#include "client.h"
#include "../patchwork/common.h"

#define BUFFER_SIZE 4096

void Client::start() {
    char buffer[BUFFER_SIZE];

    if (started) {
        throw std::runtime_error("Connexion is already started");
    }

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0) {
        throw std::runtime_error("Error establishing socket");
    }

    if (0 > connect(client, (struct sockaddr *) &server_addr, sizeof(server_addr))) {
        throw std::runtime_error("Error connecting to server");
    }

    started = true;

    recv(client, buffer, BUFFER_SIZE, 0);
}

void Client::sendAction(const std::string &action) const {
    std::string line = action + "\n";
    send(client, line.c_str(), line.size() * sizeof(char), 0);
}

void Client::sendFigure(Figure &figure) const {
    std::string buffer = figure.encode();
    std::cout << buffer << std::endl;
    sendAction(PUT_ACTION);
    send(client, buffer.c_str(), buffer.size() * sizeof(char), 0);
}

Image Client::getImage() const {
    char buffer[BUFFER_SIZE];

    sendAction(GET_ACTION);
    recv(client, buffer, BUFFER_SIZE - 1, 0);

    buffer[BUFFER_SIZE - 1] = '\0';
    std::istringstream in(buffer);

    return *(Image *) Image::decode(in);
}

void Client::stop() {
    if (!started) {
        throw std::runtime_error("Connexion is not started");
    }
    close(client);
    started = false;
}