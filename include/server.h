#ifndef SERVER_H
#define SERVER_H

int setup_server();
void handle_single_connection(int master_socket);

#endif
