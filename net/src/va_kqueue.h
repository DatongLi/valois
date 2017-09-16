//
// Created by Li,Datong on 8/3/17.
//

#ifndef _VA_KQUEUE_H
#define _VA_KQUEUE_H

#include "event_loop.h"
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <cstdlib>

namespace valois {
namespace net {
class EventLoop;
class Poll : public PollBase {
public:
    Poll() : _kqfd(-1), _events(nullptr), _events_num(0) {}
    virtual ~Poll() {
        close(_kqfd);
        if(_events != nullptr) {
            std::free(_events);
            _events = nullptr;
        }
        _events_num = 0;
    }

    int PollCreate(EventLoop *eventLoop) {
        _kqfd = kqueue();
        if(_kqfd == -1) {
            return -1;
        }
        _events_num = eventLoop->GetEventSize();
        _events = (struct kevent *)std::malloc(sizeof(struct kevent) * _events_num);
        if(NULL == _events) {
            close(_kqfd);
            _events_num = 0;
            return -1;
        }
        return 0;
    }

    int EventResize(EventLoop *eventLoop, int setSize) {
        return 0;
    }

    void PollFree(EventLoop *eventLoop) {
        if (nullptr != _events) {
            std::free(_events);
            _events = nullptr;
        }
        close(_kqfd);
    }

    bool Stop(const int &wakeup_fd) {
        /*if (_epfd >= 0) {
            epoll_event evt = { EPOLLOUT,  { NULL } };
            epoll_ctl(_epfd, EPOLL_CTL_ADD, wakeup_fd, &evt);
        }*/
        return true;
    }

    int PollAddEvent(EventLoop *eventLoop, int fd, int mask) {
        struct kevent ke;

        if (mask & VA_READABLE) {
            EV_SET(&ke, fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
            if (kevent(_kqfd, &ke, 1, NULL, 0, NULL) == -1) return -1;
        }
        if (mask & VA_WRITABLE) {
            EV_SET(&ke, fd, EVFILT_WRITE, EV_ADD, 0, 0, NULL);
            if (kevent(_kqfd, &ke, 1, NULL, 0, NULL) == -1) return -1;
        }
        return 0;
    }

    int PollDelEvent(EventLoop *eventLoop, int fd, int mask) {
        struct kevent ke;

        if (mask & VA_READABLE) {
            EV_SET(&ke, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
            kevent(_kqfd, &ke, 1, NULL, 0, NULL);
        }
        if (mask & VA_WRITABLE) {
            EV_SET(&ke, fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
            kevent(_kqfd, &ke, 1, NULL, 0, NULL);
        }
        return 0;
    }

    int PollWaitEvent(EventLoop *eventLoop, struct timeval *tvp) {
        int ret = 0, nReady = 0;

        if (tvp != NULL) {
            struct timespec timeout;
            timeout.tv_sec = tvp->tv_sec;
            timeout.tv_nsec = tvp->tv_usec * 1000;
            ret = kevent(_kqfd, NULL, 0, _events, _events_num, &timeout);
        } else {
            ret = kevent(_kqfd, NULL, 0, _events, _events_num, NULL);
        }
        if (ret > 0) {
            int j;

            nReady = ret;
            for(j = 0; j < nReady; j++) {
                int mask = 0;
                struct kevent *e = _events + j;

                if (e->filter == EVFILT_READ) mask |= VA_READABLE;
                if (e->filter == EVFILT_WRITE) mask |= VA_WRITABLE;
                eventLoop->fired[j].fd = e->ident;
                eventLoop->fired[j].mask = mask;
            }
        }
        return nReady;
    }
private:
    int _kqfd;
    struct kevent *_events;
    int _events_num;
};

}
}

#endif //_VA_KQUEUE_H
