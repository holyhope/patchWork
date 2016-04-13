//
// Created by Pierre Peronnet on 12/04/2016.
//

#include <sys/socket.h>
#include <unistd.h>

#include "client.h"

#define BUFFER_SIZE 4096

void Client::start() {
    char buffer[BUFFER_SIZE];

    if (started) {
        throw new std::runtime_error("Connexion is already started");
    }

    client = socket(AF_INET, SOCK_STREAM, 0);

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/
    /* --------------- socket() function ------------------*/

    if (client < 0) {
        throw new std::runtime_error("Error establishing socket");
    }

    if (0 > connect(client, (struct sockaddr *) &server_addr, sizeof(server_addr))) {
        throw new std::runtime_error("Error connecting to server");
    }

    started = true;

    std::cout << "=> Awaiting confirmation from the server..." << std::endl; //line 40
    recv(client, buffer, BUFFER_SIZE, 0);
    std::cout << "=> Connection confirmed, you are good to go...";
}

void Client::sendFigure(Figure &figure) const {
    string buffer = Figure::encode(figure);
    send(client, buffer.c_str(), buffer.size(), 0);
}

Image Client::getImage() const {
    char buffer[BUFFER_SIZE], *b;
    recv(client, buffer, BUFFER_SIZE - 1, 0);

    buffer[BUFFER_SIZE - 1] = '\0';

    b = buffer;

    return *(Image *) Image::decode(&b);
}

void Client::stop() {
    if (!started) {
        throw new std::runtime_error("Connexion is not started");
    }
    close(client);
    started = false;
}