//
// Created by Li,Datong on 8/3/17.
//

#ifndef _VA_SELECT_H
#define _VA_SELECT_H

#include "poll_base.h"
#include <sys/select.h>
#include <string.h>

namespace valois {
namespace net {
class Poll : public PollBase {
public:
    Poll() {}
    virtual ~Poll() {}
    int PollCreate(EventLoop *eventLoop) {
        return 0;
    }

    int EventResize(EventLoop *eventLoop, int setSize) {
        return 0;
    }

    void PollFree(EventLoop *eventLoop) {
        return nullptr;
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

private:
    fd_set rfds;
    fd_set wfds;
    fd_set _rfds;
    fd_set _wfds;
};
}
}

#endif //_VA_SELECT_H
