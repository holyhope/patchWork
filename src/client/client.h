#ifndef PATCHWORK_CLIENT_H
#define PATCHWORK_CLIENT_H

#include <iostream>
#include <netinet/in.h>
#include <string>
#include "../patchwork/figure.hpp"
#include "../patchwork/Image.h"

class Client {
public:
    /**
     * Construct a client for a specific server.
     */
    Client(struct sockaddr_in server_addr) : server_addr(server_addr) { };

    /**
     * Start connexion with server.
     * Its version is checked before continue.
     * \Warning client can be started only once
     * \see Client::close
     */
    void start();

    /**
     * End connexion with server.
     * Its version is checked before continue.
     * \Warning client must be started
     * \see Client::start
     */
    void stop();

    /**
     * Send a figure to the server.
     * \Warning client must be started
     * \param figure The figure to send
     * \see Client::start
     */
    void sendFigure(Figure &figure) const;

    /**
     * Get current image from the server.
     * \Warning client must be started
     * \see Client::start
     * \return The current image
     */
    Image getImage() const;

private:
    struct sockaddr_in server_addr;
    bool started = false;
    int client;

    void sendAction(const std::string &action) const;
};

#endif //PATCHWORK_CLIENT_H
