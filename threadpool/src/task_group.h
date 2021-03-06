//
// Created by Li,Datong on 04/09/2017.
//

#ifndef _TASK_GROUP_H
#define _TASK_GROUP_H

#include "base/common.h"
#include "base/thread_safe_queue.h"
#include "mempool.h"

#define TASK_FINISH 0
#define TASK_RUNNING 1
#define TASK_ERROR 2
namespace valois {
namespace base {

class Task {
friend class TaskGroup;
public:
    Task() {}
    ~Task() {}
    int GetStatus() { return _status; }
    void SetStatus(int status) { _status = status; }
    int RunTask() {
        LOG(INFO) << "RunTask fn = " << _fn << ", arg = " << _arg;
        _fn(_arg);
        return TASK_FINISH;
    }
private:
    void* (*_fn)(void *);
    void* _arg;
    int _status;
};

class TaskGroup {
friend class ThreadPool;
public:
    TaskGroup();
    virtual ~TaskGroup();
    int Submit(void* (*fn)(void *), void* arg);
    int Finish(Task *task);
    bool TryPop(Task *&task);
    bool Push(Task *task);
    int setTid(int tid);
    int getTid() { return _tid; };
    bool IsEmpty();
private:
    base::MemPool<base::Task> *_task_pool;
    //ThreadSafeQueue<base::Task *> _running_queue;
    std::deque<Task *> _running_queue;
    int _task_num_per_group;
    int _tid;
};
}
}
#endif //_TASK_GROUP_H
