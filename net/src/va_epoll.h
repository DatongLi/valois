//
// Created by Li,Datong on 8/3/17.
//

#ifndef _VA_EPOLL_H
#define _VA_EPOLL_H

#include <sys/epoll.h>

class Poll : public PollBase {
public:
    int PollCreate(EventLoop *eventLoop);
    int EventResize(EventLoop *eventLoop, int setSize);
    void PollFree(EventLoop *eventLoop);
    int PollAddEvent(EventLoop *eventLoop, int fd, int mask);
    int PollDelEvent(EventLoop *eventLoop, int fd, int mask);

    bool Stop(const int &wakeup_fd);

private:
    int _epfd;
    struct epoll_event *_events;
};

#endif //_VA_EPOLL_H
