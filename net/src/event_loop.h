#ifndef _EVENT_LOOP_H
#define _EVENT_LOOP_H

#include "base/common.h"
#ifdef HAVE_EPOLL
    #include "va_epoll.c"
#else
    #ifdef HAVE_KQUEUE
        #include "va_kqueue.c"
    #else
        #include "va_select.c"
    #endif
#endif

#define VA_NONE 0
#define VA_READABLE 1
#define VA_WRITABLE 2

class EventLoop {
public:
    EventLoop();
    virtual ~EventLoop();

    EventLoop *CreateEventLoop(int setEventSize);
    int GetEventSize() const { return _eventSize; }

    bool Start();
    bool Stop();
    void* Run(void* args);

private:
    Poll poll;
    int _eventSize;
    std::atomic<bool> _stop;
    pthread_t _tid;

    /* A fired event */
    typedef struct vaEvent {
        int fd;
        int mask;
    } vaEvent;

    vaEvent *events;
    vaEvent *fired;

    // wakeup the epoll from epoll_wait when call Stop()
    int _wakeup_fds[2];
};

#endif