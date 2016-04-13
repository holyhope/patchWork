#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include "../patchwork/patchwork.h"
#include "../patchwork/Image.h"

#define BUFFER_SIZE 4096

#define SERVER_VERSION "v1"

using namespace std;

int client;
bool isExit = false;

void signal_callback_handler(int signum) {
    switch (signum) {
        case SIGTERM:
        case SIGINT:
            cout << " => Shutting down server..." << endl;
            isExit = true;
            close(client);
            break;
        default:
            cout << "Signal " << signum << " caught" << endl;
            break;
    }
}

int main() {
    Image image;

    initializePatchwork();

    int server;
    int portNum = 1500;
    char buffer[BUFFER_SIZE];
    string message;

    struct sockaddr_in server_addr;
    socklen_t size;

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0) {
        throw std::runtime_error("Error establishing socket");
    }

    cout << endl << "=> Socket server has been created..." << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);

    if (0 > _SYS_SOCKET_H_::bind(client, (struct sockaddr *) &server_addr, sizeof(server_addr))) {
        throw std::runtime_error("Error binding connection, the socket has already been established");
    }

    size = sizeof(server_addr);
    cout << "=> Looking for clients..." << endl;

    listen(client, 1);

    /* ------------- ACCEPTING CLIENTS  ------------- */
    /* ----------------- listen() ------------------- */

    int clientCount = 1;

    signal(SIGINT, signal_callback_handler);

    while (!isExit) {
        server = accept(client, (struct sockaddr *) &server_addr, &size);

        // first check if it is valid or not
        if (server < 0) {
            cerr << "=> Error on accepting..." << endl;
        } else {
            cout << "=> Connected with the client #" << clientCount << endl;

            sprintf(buffer, "Serveur %s\n", SERVER_VERSION);
            send(server, buffer, BUFFER_SIZE, 0);

            if (0 > recv(server, buffer, BUFFER_SIZE, 0)) {
                cerr << "Error with client #" << clientCount << endl;
            } else {
                char *tmp = buffer;
                image.add(*Figure::decode(&tmp));
                message = image.encode();
                send(server, message.c_str(), message.size(), 0);
            }

            if (0 > close(server)) {
                cerr << "Cannot close connection with #" << clientCount << endl;
            } else {
                cout << endl << "=> Connection terminated with IP " << string(inet_ntoa(server_addr.sin_addr)) << endl;
            }
        }

        close(client);
    }

    return 0;
}