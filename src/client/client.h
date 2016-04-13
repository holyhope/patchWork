//
// Created by Pierre Peronnet on 12/04/2016.
//

#ifndef PATCHWORK_CLIENT_H
#define PATCHWORK_CLIENT_H

#include <iostream>
#include <netinet/in.h>
#include <string>
#include "../patchwork/figure.hpp"
#include "../patchwork/Image.h"

class Client {
public:
    Client(struct sockaddr_in server_addr) : server_addr(server_addr) { };

    void start();

    void stop();

    void sendFigure(Figure &figure) const;

    Image getImage() const;

protected:
    struct sockaddr_in server_addr;
    bool started = false;
    int client;
};

#endif //PATCHWORK_CLIENT_H
