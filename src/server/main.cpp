#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "server.h"
#include "../patchwork/patchwork.h"

Server *server;

void signal_callback_handler(int signum) {
    switch (signum) {
        case SIGTERM:
        case SIGINT:
            std::cout << " => Shutting down server..." << std::endl;
            server->stop();
            break;
        default:
            std::cout << "Signal " << signum << " caught" << std::endl;
            break;
    }
}

int main(int argc, const char *argv[]) {
    initializePatchwork();

    int portNum = 1500;

    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);

    server = new Server(server_addr);

    signal(SIGINT, signal_callback_handler);

    try {
        server->start();
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }

    terminatePatchwork();

    return 0;
}