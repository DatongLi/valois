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
#include <string>
#include "example/echo.pb.h"

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
    EventLoop *eventLoop = static_cast<EventLoop *>(clientData);
    int ret = -1;
    if(fd == _listen_fd) {
        struct sockaddr_in cli_addr;
        socklen_t cli_len;
        int con_fd = ::accept(_listen_fd, (struct sockaddr*)&cli_addr, &cli_len);
        SetNonBlocking(con_fd);
        eventLoop->AddFdPoll(con_fd, VA_READABLE | VA_WRITABLE | VA_ET, this);
    } else {
        std::string message;
        message.reserve(BUFSIZE);
        char* buf = &message[0];
        int pos = 0;
        ssize_t n = 0;

        do {
            n = read(fd, buf + pos, message.capacity() - pos - 1);
            if (n < 0) {
                // errno handle
                if(errno == EAGAIN) {
                    continue;
                }
                goto OUT;
            }  else if (n == 0) {
                // read empty
                break;
            }
            pos += n;
            message.reserve(message.capacity() * 1.5);
        } while(true);
        ret = pos;
        // TODO : deal with the data by calling user's callback, policy handler
        example::Hello hel;
        if(!hel.ParseFromString(message)) {
            goto OUT;
        }
        std::cout << "id = " << hel.id() << " , info = " << hel.info() << std::endl;
        // TODO: response to client after getting request
    }
    return ret;
OUT:
    return -1;
}

int DefaultEventHandler::WriteEvent(int fd, void *clientData, int mask) {
    EventLoop *eventLoop = (EventLoop *)clientData;
    // TODO : write handle

    return 0;
}

}
}