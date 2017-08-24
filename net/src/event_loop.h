#ifndef _EVENT_LOOP_H
#define _EVENT_LOOP_H

#include "base/common.h"
#include "event_handler.h"
#include "socket_manager.h"
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
#define VA_ET 4

#define VA_FILE_EVENTS 1
#define VA_TIME_EVENTS 2
#define VA_ALL_EVENTS (VA_FILE_EVENTS|VA_TIME_EVENTS)
#define VA_DONT_WAIT 4
#define VA_CALL_AFTER_SLEEP 8

#define VA_NOMORE -1
#define VA_DELETED_EVENT_ID -1

class EventLoop {
friend class Socket;
public:
    EventLoop();
    virtual ~EventLoop();

    EventLoop *CreateEventLoop(int setEventSize);
    int GetEventSize() const { return _eventSize; }

    bool Start();
    bool Stop();
    void* Run(void* args);

    int AddFdPoll(int fd, int mask, EventHandler *event_handler);
    int DelFdPoll(int fd, int mask);

private:
    int RegisterFdEventHandler(int fd, EventHandler *event_handler);
    int RemoveFdEventHandler(int fd);
    void GetTime(long *seconds, long *milliseconds);

    std::unique_ptr<Poll> poll;
    int _event_size;
    std::atomic<bool> _stop;
    pthread_t _tid;

    /* A fired event */
    typedef struct vaEvent {
        int fd;
        int mask;
    } vaEvent;

    std::unique_ptr<std::map<int, EventHandler *>> _event_handler_maps;
    vaEvent *fired;

    /* Time event structure */
    typedef struct TimeEvent {
        long long id; /* time event identifier. */
        long when_sec; /* seconds */
        long when_ms; /* milliseconds */
        struct TimeEvent *next;
    } TimeEvent;

    // wakeup the epoll from epoll_wait when call Stop()
    int _wakeup_fds[2];
};

#endif