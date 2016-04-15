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

    /**
     * Start the server by openning the socket.
     * \warning Does not accept client
     * \warning Server can only be started once
     * \see Server::run
     * \see Server::stop
     */
    void start();

    /**
     * Stop the server.
     * \warning Server must be started
     * \see Server::start
     */
    void stop();

    /**
     * Accept clients and deal with them.
     * \warning Server must be started
     * \see Server::start
     */
    void run();

private:
    struct sockaddr_in _address;
    bool _stopped;
    int _socketServer;
    Image _image;

    void manageClient(const int socketClient);

    void doGetAction(const int socketClient) const;

    void doPutAction(std::istringstream &buffer);
};

#endif //PATCHWORK_SERVER_H
