//
// Created by Li,Datong on 22/08/2017.
//

#include "socket_manager.h"

DEFINE_int32(server_port, 8001, "server port for listening any connection request!");
DEFINE_int32(LISTENQ, 1024, "server port for listening any connection request!");

int Socket::BindSocket() {
    struct sockaddr_in server_addr;
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(FLAGS_server_port);

    bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(listen_fd, FLAGS_LISTENQ);
    return listen_fd;
}