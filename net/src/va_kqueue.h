//
// Created by Li,Datong on 8/3/17.
//

#ifndef _VA_KQUEUE_H
#define _VA_KQUEUE_H

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

class Poll : public PollBase {
public:
    int PollCreate(EventLoop *eventLoop);
    int EventResize(EventLoop *eventLoop, int setSize);
    void PollFree(EventLoop *eventLoop);
    int PollAddEvent(EventLoop *eventLoop, int fd, int mask);
    int PollDelEvent(EventLoop *eventLoop, int fd, int mask);
    bool Stop(const int &wakeup_fd);
    int PollWaitEvent(EventLoop *eventLoop, struct timeval *tvp);

private:
    int kqfd;
    struct kevent *events;
    int _events_num;
};


#endif //_VA_KQUEUE_H
