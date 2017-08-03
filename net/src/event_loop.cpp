
#include "event_loop.h"

EventLoop::EventLoop()
        : _eventSize(0)
        , _stop(true)
{
    _wakeup_fds[0] = -1;
    _wakeup_fds[1] = -1;
}

EventLoop *EventLoop::CreateEventLoop(int setEventSize) {
    _eventSize = setEventSize;
    if (pipe(_wakeup_fds) != 0) {
        return nullptr;
    }
    if (-1 == poll::PollCreate(this)) {
        return nullptr;
    }
    Start();
}

EventLoop::~EventLoop() {
    Stop();
    Join();
    if (_wakeup_fds[0] > 0) {
        close(_wakeup_fds[0]);
        close(_wakeup_fds[1]);
    }
}

bool EventLoop::Start() {
    int rc = pthread_create(&_tid, NULL, &Run, NULL);
    if(rc) {
        return false;
    }
    _stop.store(false, std::memory_order_release);
    return true;
}

bool EventLoop::Join() {
    if(_tid) {
        pthread_join(_tid);
        _tid = 0;
    }
    return true;
}

bool EventLoop::Stop() {
    if(false == poll.Stop(_wakeup_fds[1])) {
        return false;
    }
    _stop.store(true, std::memory_order_release);
    return true;
}

void* EventLoop::Run(void* ) {
    while(!_stop.load(std::memory_order_acquire)) {
        const int n = epoll_wait(_epfd, e, ARRAY_SIZE(e), -1);
        if(_stop.load(std::memory_order_acquire)) { break; }
        if(n < 0) {
            if (EINTR == errno) {
                continue;
            }
            break;
        }
        for (int i = 0; i < n; ++i) {
            if (e[i].events & (EPOLLOUT | EPOLLERR | EPOLLHUP)) {
                // Handle EpollOut event
            }
        }
        for (int i = 0; i < n; ++i) {
            if (e[i].events & (EPOLLIN | EPOLLERR | EPOLLHUP)) {
                // Handle EpollIn event
            }
        }
    }
}