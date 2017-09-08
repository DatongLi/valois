//
// Created by Li,Datong on 22/08/2017.
//

#ifndef PROJECT_DEFAULT_EVENT_HANDLER_H
#define PROJECT_DEFAULT_EVENT_HANDLER_H

#include "event_handler.h"
#include <fcntl.h>

#define BUFSIZE 1024

namespace valois {
namespace net {

class DefaultEventHandler : public EventHandler {
public:
    DefaultEventHandler() : _listen_fd(-1) {}
    DefaultEventHandler(int fd) : _listen_fd(fd) {}
    int ReadEvent(int fd, void *clientData, int mask);
    int WriteEvent(int fd, void *clientData, int mask);
private:
    int SetNonBlocking(int sock);
    int _listen_fd;
};

}
}

#endif //PROJECT_DEFAULT_EVENT_HANDLER_H
