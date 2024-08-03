#include "../include/response.h"
#include "../include/logger.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void send_response(const int client_socket, const int status_code, const char *status_text, const char *message) {
    char header[1024];
    snprintf(header, sizeof(header),
             "HTTP/1.1 %d %s\r\n"
             "Content-Type: text/html\r\n"
             "Content-Length: %ld\r\n"
             "\r\n"
             "<html><body><h1>%d %s</h1><p>%s</p></body></html>",
             status_code, status_text, strlen(message) + 36 + strlen(status_text), status_code, status_text, message);

    // Log the response details
    log_message("INFO", "Sending response: %d %s", status_code, status_text);

    const ssize_t bytes_written = write(client_socket, header, strlen(header));
    if (bytes_written < 0) {
        log_message("ERROR", "Failed to send response to client");
        perror("Failed to send response to client");
    } else {
        log_message("INFO", "Response sent successfully: %d %s", status_code, status_text);
    }
}
