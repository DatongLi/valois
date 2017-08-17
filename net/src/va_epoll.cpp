//
// Created by Li,Datong on 8/3/17.
//

#include "va_epoll.h"

int Poll::PollCreate(EventLoop *eventLoop) {
    _epfd = epoll_create(1024);
    if (_epfd < 0) {
        return -1;
    }
    _events_num = eventLoop->GetEventSize();
    _events = malloc(sizeof(struct epoll_event) * _events_num);
    if (nullptr == _events) {
        close(_epfd);
        _events_num = 0;
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
    struct epoll_event ee = {0};
    int op = eventLoop->events[fd].mask == VA_NONE ?
             EPOLL_CTL_ADD : EPOLL_CTL_MOD;
    ee.events = 0;
    mask |= eventLoop->events[fd].mask;
    if (mask & VA_READABLE) ee.events |= EPOLLIN;
    if (mask & VA_WRITABLE) ee.events |= EPOLLOUT;
    ee.data.fd = fd;
    if (epoll_ctl(_epfd, op, fd, &ee) == -1) return -1;
    return 0;
}

int Poll::PollDelEvent(EventLoop *eventLoop, int fd, int mask) {
    struct epoll_event ee = {0};
    int mask = eventLoop->events[fd].mask & (~delmask);
    ee.events = 0;
    if (mask & VA_READABLE) ee.events |= EPOLLIN;
    if (mask & VA_WRITABLE) ee.events |= EPOLLOUT;
    ee.data.fd = fd;
    if (mask != VA_NONE) {
        epoll_ctl(_epfd, EPOLL_CTL_MOD, fd, &ee);
    } else {
        /* Note, Kernel < 2.6.9 requires a non null event pointer even for
         * EPOLL_CTL_DEL. */
        epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, &ee);
    }
    return 0;
}

int Poll::PollWaitEvent(EventLoop *eventLoop, struct timeval *tvp) {
    int nReady = 0;
    int ret = epoll_wait(_epfd, _events, _events_num,
                         tvp ? (tvp->tv_sec*1000 + tvp->tv_usec/1000) : -1);
    if(ret > 0) {
        nReady = ret;
        for (int j = 0; j < numevents; j++) {
            int mask = 0;
            struct epoll_event *e = _events + j;

            if (e->events & EPOLLIN) mask |= VA_READABLE;
            if (e->events & EPOLLOUT) mask |= VA_WRITABLE;
            if (e->events & EPOLLERR) mask |= VA_WRITABLE;
            if (e->events & EPOLLHUP) mask |= VA_WRITABLE;
            eventLoop->fired[j].fd = e->data.fd;
            eventLoop->fired[j].mask = mask;
        }
    }
    return nReady;
}