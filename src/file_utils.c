#include "../include/file_utils.h"
#include "../include/response.h"
#include "../include/logger.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

void serve_file(const int client_socket, const char *filepath) {
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "../public%s", filepath);

    if (access(full_path, F_OK) == -1) {
        log_message("WARN", "File not found: %s", full_path);
        send_response(client_socket, 404, "Not Found", "The requested resource could not be found.");
        return;
    }

    const int file_fd = open(full_path, O_RDONLY);
    if (file_fd == -1) {
        log_message("ERROR", "Failed to open file: %s", full_path);
        send_response(client_socket, 500, "Internal Server Error", "An error occurred while processing your request.");
        return;
    }

    struct stat file_stat;
    if (fstat(file_fd, &file_stat) < 0) {
        log_message("ERROR", "Failed to get file status: %s", full_path);
        send_response(client_socket, 500, "Internal Server Error", "An error occurred while processing your request.");
        close(file_fd);
        return;
    }

    log_message("INFO", "Serving file: %s", full_path);

    char header[1024];
    snprintf(header, sizeof(header),
             "HTTP/1.1 200 OK\r\n"
             "Content-Length: %lld\r\n"
             "Content-Type: text/html\r\n"
             "\r\n", (long long)file_stat.st_size);
    write(client_socket, header, strlen(header));

    char file_buffer[1024];
    int bytes_read;
    while ((bytes_read = read(file_fd, file_buffer, sizeof(file_buffer))) > 0) {
        write(client_socket, file_buffer, bytes_read);
    }

    close(file_fd);
    log_message("INFO", "File served successfully: %s", full_path);

    shutdown(client_socket, SHUT_WR);
    close(client_socket);
}
