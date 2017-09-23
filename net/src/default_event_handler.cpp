//
// Created by Li,Datong on 22/08/2017.
//
#include "base/common.h"
#include "default_event_handler.h"
#include "event_loop.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

DEFINE_int32(server_port, 8001, "server port for listening any connection request!");
DEFINE_int32(LISTENQ, 1024, "server port for listening any connection request!");

namespace valois {
namespace net {

int DefaultEventHandler::BindSocket() {
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
    EventLoop *eventLoop = (EventLoop *)clientData;
    int n = 0;
    char recv_line[BUFSIZE];
    bzero(recv_line, BUFSIZE);
    if(fd == _listen_fd) {
        struct sockaddr_in cli_addr;
        socklen_t cli_len;
        int con_fd = ::accept(_listen_fd, (struct sockaddr*)&cli_addr, &cli_len);
        SetNonBlocking(con_fd);
        eventLoop->AddFdPoll(con_fd, VA_READABLE | VA_WRITABLE | VA_ET, this);
    } else {
        do {
            n = read(fd, recv_line, BUFSIZE);
            if (n < 0) {
                // read the wrong value
                break;
            }  else if (n == 0) {
                // read empty
                break;
            }

        } while(true);
        // TODO : deal with the data by calling user's callback

    }
    return 0;
}

int DefaultEventHandler::WriteEvent(int fd, void *clientData, int mask) {
    EventLoop *eventLoop = (EventLoop *)clientData;
    // TODO : write handle
    return 0;
}

}
}