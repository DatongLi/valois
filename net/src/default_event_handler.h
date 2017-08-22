//
// Created by Li,Datong on 22/08/2017.
//

#ifndef PROJECT_DEFAULT_EVENT_HANDLER_H
#define PROJECT_DEFAULT_EVENT_HANDLER_H

#include "event_handler.h"
#include <fcntl.h>

#define BUFFSIZE 1024

class DefaultEventHandler : public EventHandler {
public:
    DefaultEventHandler(int fd) : _listen_fd(-1) {}
    DefaultEventHandler(int fd) : _listen_fd(fd) {}
    int ReadEvent(int fd, void *clientData, int mask);
    int WriteEvent(int fd, void *clientData, int mask);
private:
    int SetNonBlocking(int sock);
    int _listen_fd;
};


#endif //PROJECT_DEFAULT_EVENT_HANDLER_H
