
#include "poller.h"

namespace base {
namespace net {
    Poller::Poller() : _stop(true) {
        _epfd = epoll_create(1024 * 1024);
        if (_epfd < 0) {
            return;
        }
        _wakeup_fds[0] = -1;
        _wakeup_fds[1] = -1;
        if (pipe(_wakeup_fds) != 0) {
            return;
        }
    }

    Poller::~Poller() {
        Stop();
        Join();
        if (_epfd >= 0) {
            close(_epfd);
            _epfd = -1;
        }
        if (_wakeup_fds[0] > 0) {
            close(_wakeup_fds[0]);
            close(_wakeup_fds[1]);
        }

    }

    bool Poller::Start() {
        int rc = pthread_create(&_tid, NULL, &Run, NULL);
        if(rc) {
            return false;
        }
        _stop = false;
        return true;
    }

    bool Poller::Join() {
        if(_tid) {
            pthread_join(_tid);
            _tid = 0;
        }
    }

    bool Poller::Stop() {
        _stop = true;
        if (_epfd >= 0) {
            epoll_event evt = { EPOLLOUT,  { NULL } };
            epoll_ctl(_epfd, EPOLL_CTL_ADD, _wakeup_fds[1], &evt);
        }
        return true;
    }

    void* Poller::Run(void* ) {
        epoll_event e[32];
        while(!_stop) {
            const int n = epoll_wait(_epfd, e, ARRAY_SIZE(e), -1);
            if(_stop) { break; }
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

    int Poller::AddFDToEpoll(int fd) {
        return AddFDToEpoll(fd, 0, EPOLLOUT | EPOLLET);
    }

    int Poller::AddEpollOut(uint32_t socket_id, int fd, bool pollin = true) {
        return AddFDToEpoll(fd, socket_id, (pollin == true)?(EPOLLOUT | EPOLLIN| EPOLLET):(EPOLLOUT | EPOLLET));
    }

    int Poller::AddFDToEpoll(int fd, uint64_t ep_data, uint32_t ep_events) {
        if (_epfd < 0) {
            errno = EINVAL;
            return -1;
        }
        epoll_event evt;
        evt.events = ep_events;
        evt.data.u64 = ep_data;
        return epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &evt);
    }

    int Poller::RemoveFDFromEpoll(int fd) {
        if (fd < 0) {
            return -1;
        }
        if (epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, NULL) < 0) {
            return -1;
        }
        return 0;
    }

    int Poller::add(int a, int b) {
        return a+b;
    }
}
}