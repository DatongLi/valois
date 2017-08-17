//
// Created by Li,Datong on 8/3/17.
//

#include "va_kqueue.h"

int PollCreate(EventLoop *eventLoop) {
    return 0;
}

int EventResize(EventLoop *eventLoop, int setSize) {
    return 0;
}

void PollFree(EventLoop *eventLoop) {
    return;
}

int PollAddEvent(EventLoop *eventLoop, int fd, int mask) {
    return 0;
}

int PollDelEvent(EventLoop *eventLoop, int fd, int mask) {
    return 0;
}

bool Stop(const int &wakeup_fd) {
    return true;
}

int PollWaitEvent(EventLoop *eventLoop, struct timeval *tvp) {
    return 0;
}