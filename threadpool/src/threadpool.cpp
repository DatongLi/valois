//
// Created by Li,Datong on 04/09/2017.
//
#include "threadpool.h"
extern "C" {
#include <unistd.h>
}
#include <cstdlib>

DEFINE_int32(thread_num, 2, "thread number");
namespace valois {
namespace base {

    ThreadPool::ThreadPool() {
        //_done.store(false, std::memory_order_release);
        _thread_num = FLAGS_thread_num;
        _threads = new pthread_t[_thread_num];
        if(nullptr == _threads) {
            exit(-1);
        }
        _work_queue = new TaskGroup[_thread_num];
        if(nullptr == _work_queue) {
            exit(-1);
        }
        int rc = 0;
        for(int tid = 0 ; tid < _thread_num; ++tid) {
            _work_queue[tid].setTid(tid);
            rc = pthread_create(&_threads[tid], NULL, ThreadPool::WorkerThread, (void *)&_work_queue[tid]);
            if(rc) {
                std::cout << "pthread create failed!" << std::endl;
                exit(-1);
            }
        }
    }

    ThreadPool::~ThreadPool() {
        if(_threads == nullptr) {
            delete [] _threads;
            _threads = nullptr;
        }
        if(_work_queue == nullptr) {
            delete [] _work_queue;
            _work_queue = nullptr;
        }
        //_done.store(true, std::memory_order_release);
    }

    void ThreadPool::submit(void* (*fn)(void *), void *arg) {
        int tid = PickRunThread();
        _work_queue[tid].Submit(fn, arg);
    }

    int ThreadPool::PickRunThread() {
        return rand()%_thread_num;
    }

    bool ThreadPool::join() {
        for(int tid = 0; tid < _thread_num; ++tid) {
            pthread_join(_threads[tid], NULL);
        }
        //_done.store(true, std::memory_order_release);
        return true;
    }

    void *ThreadPool::WorkerThread(void *arg) {
        TaskGroup *taskGroup = (TaskGroup *) arg;
        Task *task = nullptr;
        //while (!_done) {
        while(1) {
            if (taskGroup->TryPop(task)) {
                LOG(WARNING) << "running tid = " << taskGroup->getTid();
                int status = task->RunTask();
                if (status == TASK_FINISH) {
                    taskGroup->Finish(task);
                } else if (status == TASK_RUNNING) {
                } else {
                    std::cout << "break!!!" << std::endl;
                    break;
                }
            } else {
                //sleep(1);
            }
        }
        return nullptr;
    }
}
}