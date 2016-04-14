//
// Created by Pierre Peronnet on 13/04/2016.
//

#ifndef PATCHWORK_SERVER_H
#define PATCHWORK_SERVER_H

#include <netinet/in.h>

#include "../patchwork/Image.h"

class Server {
public:
    Server(struct sockaddr_in address) : _address(address), _stopped(false), _socketServer(-1) { };

    void start();

    void stop();

    void manageClient(const int socketClient);

    void doGetAction(const int socketClient) const;

    void doPutAction(std::istringstream &buffer);

private:
    struct sockaddr_in _address;
    bool _stopped;
    int _socketServer;
    Image _image;
};

#endif //PATCHWORK_SERVER_H
