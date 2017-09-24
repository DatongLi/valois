//
// Created by Li,Datong on 04/09/2017.
//

#include "task_group.h"
#include <cstdio>

DEFINE_int32(task_num_per_group, 128, "task number per group");
namespace valois {
namespace base {
    TaskGroup::TaskGroup()
            : _task_num_per_group(FLAGS_task_num_per_group) {
        _task_pool = new base::MemPool<base::Task>(_task_num_per_group);
        if (nullptr == _task_pool) {
            exit(-1);
        }
    }

    TaskGroup::~TaskGroup() {
        if (nullptr != _task_pool) {
            delete [] _task_pool;
            _task_pool = nullptr;
        }
    }

    int TaskGroup::Submit(void *(*fn)(void *), void *arg) {
        Task *task;
        _task_pool->getElem(task);
        task->_fn = fn;
        task->_arg = arg;
        Push(task);
        return 0;
    }

    int TaskGroup::Finish(Task *task){
        _task_pool->putElem(task);
        return 0;
    }

    bool TaskGroup::TryPop(Task *&task) {
        if(_running_queue.empty()) return false;
        task = _running_queue.back();
        _running_queue.pop_back();
        return true;
    }

    bool TaskGroup::Push(Task *task) {
        _running_queue.push_back(task);
        return true;
    }

    int TaskGroup::setTid(int tid) {
        _tid = tid;
        return 0;
    }

    bool TaskGroup::IsEmpty() {
        return _running_queue.empty();
    }
}
}