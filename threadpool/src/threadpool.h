#include <thread>
#include "base/common.h"
#include "base/thread_safe_queue.h"

#ifndef _THREADPOOL_H
#define _THREADPOOL_H

class Threadpool {
public:
    Threadpool() : done(false) {
        unsigned const thread_count = std::thread::hardware_concurrency();
        try {
            for(unsigned i = 0; i < thread_count; ++i) {
                threads.push_back(std::thread(&Threadpool::worker_thread, this));
            }
        } catch(...) {
            done = true;
            throw;
        }
    }

    ~Threadpool() {
        done = true;
    }

    template<typename FunctionType>
    void submit(FunctionType f) {
        work_queue.push(std::function<void()>(f));
    }

    bool join() {
        for(int i = 0; i < threads.size(); ++i) {
            threads[i].join();
        }
        done.store(true, std::memory_order_release);
        return true;
    }

private:
    std::atomic_bool done;
    ThreadSafeQueue<std::function<void()> > work_queue;
    std::vector<std::thread> threads;
    //join_threads joiner;

    void worker_thread() {
        while(!done) {
            std::function<void()> task;
            if(work_queue.try_pop(task)) {
                task();
            } else {
                std::this_thread::yield();
            }
        }
    }
};

#endif