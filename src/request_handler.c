#include "../include/request_handler.h"
#include "../include/response.h"
#include "../include/file_utils.h"
#include "../include/logger.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int handle_request(const int client_socket) {
    char buffer[1024] = {0};
    const ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
    if (bytes_read < 0) {
        log_message("ERROR", "Error reading from socket");
        perror("Error reading from socket");
        return -1;  // Signal to close the socket
    }

    if (bytes_read == 0) {
        log_message("INFO", "Client closed connection");
        return -1;  // Client closed connection
    }

    char method[16], filepath[1024];
    if (sscanf(buffer, "%15s %1023s", method, filepath) != 2) {
        log_message("WARN", "Malformed HTTP request received: %s", buffer);
        send_response(client_socket, 400, "Bad Request", "Malformed HTTP request");
        return -1;  // Signal to close the socket
    }

    log_message("INFO", "Received %s request for %s", method, filepath);

    if (strcmp(method, "GET") == 0) {
        if (strcmp(filepath, "/") == 0) {
            strcpy(filepath, "/index.html");
        } else if (strchr(filepath, '.') == NULL) {
            strcat(filepath, ".html");
        }

        // Security: Prevent directory traversal
        if (strstr(filepath, "..") != NULL) {
            log_message("WARN", "Directory traversal attempt detected: %s", filepath);
            send_response(client_socket, 403, "Forbidden", "Access denied.");
            return -1;  // Signal to close the socket
        }

        serve_file(client_socket, filepath);
    } else {
        log_message("WARN", "Unsupported request method: %s", method);
        send_response(client_socket, 501, "Not Implemented", "This server only supports GET requests.");
    }

    return 0;  // Success, do not close the socket
}
