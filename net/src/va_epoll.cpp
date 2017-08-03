//
// Created by Li,Datong on 8/3/17.
//

#include "va_epoll.h"

int Poll::PollCreate(EventLoop *eventLoop) {
    _epfd = epoll_create(1024 * 1024);
    if (_epfd < 0) {
        return -1;
    }
    _events = malloc(sizeof(struct epoll_event) * eventLoop->GetEventSize());
    if (nullptr == _events) {
        close(_epfd);
        return -1;
    }
    return 0;
}

void Poll::PollFree(EventLoop *eventLoop) {
    if (nullptr != _events) {
        free(_events);
        _events = nullptr;
    }
    close(_epfd);
}

bool Poller::Stop(const int &wakeup_fd) {
    if (_epfd >= 0) {
        epoll_event evt = { EPOLLOUT,  { NULL } };
        epoll_ctl(_epfd, EPOLL_CTL_ADD, wakeup_fd, &evt);
    }
    return true;
}

int Poll::PollAddEvent(EventLoop *eventLoop, int fd, int mask) {

}

int Poll::PollDelEvent(EventLoop *eventLoop, int fd, int mask) {

}