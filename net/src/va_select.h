//
// Created by Li,Datong on 8/3/17.
//

#ifndef _VA_SELECT_H
#define _VA_SELECT_H

#include <sys/select.h>
#include <string.h>

class Poll : public PollBase {
public:
    int PollCreate(EventLoop *eventLoop);
    int EventResize(EventLoop *eventLoop, int setSize);
    void PollFree(EventLoop *eventLoop);
    int PollAddEvent(EventLoop *eventLoop, int fd, int mask);
    int PollDelEvent(EventLoop *eventLoop, int fd, int mask);

private:
    fd_set rfds, wfds;
    fd_set _rfds, _wfds;
};


#endif //_VA_SELECT_H
