#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/server.h"
#include "../include/messages.h"
#include "../include/logger.h"

int main() {
    display_welcome_message();

    log_message("INFO", "Server is starting...");

    // Server setup and initialization
    const int master_socket = setup_server();
    if (master_socket < 0) {
        log_message("ERROR", "Server setup failed");
        perror("Server setup failed");
        return EXIT_FAILURE;
    }

    log_message("INFO", "Server setup successfully. Listening for connections...");

    // Main loop to handle incoming connections one at a time
    handle_single_connection(master_socket);

    log_message("INFO", "Server shutting down...");
    close(master_socket);
    return 0;
}
