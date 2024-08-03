#ifndef RESPONSE_H
#define RESPONSE_H

void send_response(int client_socket, int status_code, const char *status_text, const char *message);

#endif
