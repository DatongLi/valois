#include <thread>
#include "base/common.h"

#ifndef _THREADPOOL_H
#define _THREADPOOL_H

class Threadpool {
public:

private:
    std::deque<Task> _running_queue;
    std::deque<Task> _pending_queue;
}

#endif