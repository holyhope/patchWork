#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "client.h"
#include "cli.h"
#include "../patchwork/patchwork.h"
#include "../patchwork/Image.h"

int main(int argc, const char *argv[]) {
    struct sockaddr_in server_addr;
    int portNum = 1500;
    std::string ip = "127.0.0.1";

    initializePatchwork();

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
    inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);

    Client client = Client(server_addr);

    client.start();

    startCli(client);

    client.stop();

    terminatePatchwork();

    return 0;
}