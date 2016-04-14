//
// Created by Pierre Peronnet on 13/04/2016.
//

#ifndef PATCHWORK_SERVER_H
#define PATCHWORK_SERVER_H

#include <netinet/in.h>

class Server {
public:
    Server(struct sockaddr_in address) : _address(address), _stopped(false), _socket(-1) { };

    void start();

    void stop();

private:
    struct sockaddr_in _address;
    bool _stopped;
    int _socket;
};

#endif //PATCHWORK_SERVER_H
