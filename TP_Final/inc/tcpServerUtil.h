#ifndef TCP_SERVER_UTIL_H
#define TCP_SERVER_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "handleServerUtil.h"

#define MAX_PENDING   5
#define BUFSIZE       256

#define WRITE_SUCCESS 1
#define SOCKET_ERROR -1
#define BIND_ERROR   -2
#define LISTEN_ERROR -4
#define ACCEPT_ERROR -8
#define RECV_ERROR   -16
#define SENT_ERROR   -32

#define SUCCESS_RESPONSE  "OK\n"
#define FAILURE_RESPONSE  "NOTFOUND\n"

// Create, bind, and listen a new TCP server socket
int setupTCPServerSocket(const int service);

// Accept a new TCP connection on a server socket
int acceptTCPConnection(int servSock);

// Handle new TCP client
void handleTCPClient(int clntSocket);

#endif // TCP_SERVER_UTIL_H
