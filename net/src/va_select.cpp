//
// Created by Li,Datong on 8/3/17.
//

#include "va_select.h"

int Poll::PollCreate(EventLoop *eventLoop) {
    return 0;
}

int Poll::EventResize(EventLoop *eventLoop, int setSize) {
    return 0;
}

void Poll::PollFree(EventLoop *eventLoop) {
    return nullptr;
}

int Poll::PollAddEvent(EventLoop *eventLoop, int fd, int mask) {
    return 0;
}

int Poll::PollDelEvent(EventLoop *eventLoop, int fd, int mask) {
    return 0;
}

bool Poll::Stop(const int &wakeup_fd) {
    return true;
}

int Poll::PollWaitEvent(EventLoop *eventLoop, struct timeval *tvp) {

    return 0;
}