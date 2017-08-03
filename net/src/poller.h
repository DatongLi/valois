#include <pthread.h>
#include <sys/epoll.h>
#include "base/common.h"

#ifndef _POLLER_H
#define _POLLER_H

#if defined(__cplusplus)
extern "C"
#endif

namespace base {
namespace net {

/* Poller will build a epoll thread to wait the input/output events,
 * then pass the socket_fd to the worker threads.
 * So, the first step of Poller is to build the epoll fd and put the
 * tcp listen socket to epoll.
 * The second step is to add a tcp connect fd to epoll after someone ask
 * to connect with listen socket.
 * The third step is to put the socket fd to other worker threads by queue.
 */
class Poller {
public:

    Poller();
    virtual ~Poller();

    bool Start();
    bool Stop();
    void* Run();

    Poller(const Poller& ) = delete;
    Poller &operator = (const Poller &) = delete;
    Poller(Poller &&) = delete;
    Poller &operator = (const Poller &&) = delete;

    int AddEpollOut(uint32_t socket_id, int fd, bool pollin = true);
    int AddFDToEpoll(int fd, uint32_t ep_events);

    int RemoveFDFromEpoll(int fd);

    int add(int a, int b);
private:
    int AddFDToEpoll(int fd, uint64_t ep_data, uint32_t ep_events);

    volatile bool _stop;
    int _epfd;
    pthread_t _tid;

    // wakeup the epoll from epoll_wait when call Stop()
    int _wakeup_fds[2];
};
}
}

#endif