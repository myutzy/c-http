// ReSharper disable CppDFAEndlessLoop
#include "../include/logger.h"
#include "../include/request_handler.h"
#include "../include/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int setup_server() {
    int opt = 1;
    int master_socket;
    struct sockaddr_in address;

    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        log_message("ERROR", "Socket creation failed");
        perror("Socket failed");
        return -1;
    }

    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0) {
        log_message("ERROR", "Setting socket options failed");
        perror("Setsockopt failed");
        close(master_socket);
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        log_message("ERROR", "Binding socket failed");
        perror("Bind failed");
        close(master_socket);
        return -1;
    }

    if (listen(master_socket, 3) < 0) {
        log_message("ERROR", "Listening on socket failed");
        perror("Listen failed");
        close(master_socket);
        return -1;
    }

    log_message("INFO", "Server setup complete. Listening on port %d", PORT);
    return master_socket;
}

void handle_single_connection(const int master_socket) {
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    while (1) {
        log_message("INFO", "Waiting for a new connection...");

        const int new_socket = accept(master_socket, (struct sockaddr *) &address, (socklen_t *) &addrlen);
        if (new_socket < 0) {
            log_message("ERROR", "Accepting connection failed");
            perror("Accept failed");
            continue;
        }

        log_message("INFO", "New connection accepted from %s:%d",
                    inet_ntoa(address.sin_addr), ntohs(address.sin_port));

        if (handle_request(new_socket) < 0) {
            log_message("INFO", "Connection closed by client");
            close(new_socket);
        }
    }
}
