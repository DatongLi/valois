//
// Created by Li,Datong on 22/08/2017.
//

#include "default_event_handler.h"

int DefaultEventHandler::SetNonBlocking(int sock) {
    int opts;
    if ((opts = fcntl(sock, F_GETFL)) < 0) {
        return -1;
    }

    opts = opts | O_NONBLOCK;
    if (fcntl(sock, F_SETFL, opts) < 0) {
        return -1;
    }
    return 0;
}

int DefaultEventHandler::ReadEvent(int fd, void *clientData, int mask) {
    int n = 0;
    char recv_line[BUFFSIZE];
    bzero(recv_line, BUFFSIZE);
    if(fd == _listen_fd) {
        struct sockaddr_in cli_addr;
        socklen_t cli_len;
        int con_fd = accept(listen_fd, (struct sockaddr*)&cli_addr, &cli_len);
        SetNonBlocking(con_fd);

    } else {
        do {
            n = read(fd, recv_line, BUFSIZE);
        } while(n > 0);
    }
    return 0;
}

int DefaultEventHandler::WriteEvent(int fd, void *clientData, int mask) {

    return 0;
}