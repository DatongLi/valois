

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
    void run();

private:


};
}
}