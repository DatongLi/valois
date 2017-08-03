//
// Created by Li,Datong on 8/3/17.
//

#ifndef PROJECT_POLL_BASE_H
#define PROJECT_POLL_BASE_H

#include "event_loop.h"

class PollBase {
public:
    virtual int PollCreate(EventLoop *eventLoop) = 0;
    virtual int EventResize(EventLoop *eventLoop, int setSize) = 0;
    virtual void PollFree(EventLoop *eventLoop) = 0;
    virtual int PollAddEvent(EventLoop *eventLoop, int fd, int mask) = 0;
    virtual int PollDelEvent(EventLoop *eventLoop, int fd, int mask) = 0;
};


#endif //PROJECT_POLL_BASE_H
