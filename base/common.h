
#ifndef _COMMON_H
#define _COMMON_H

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <atomic>
#include <cmath>
#include <algorithm>
#include <array>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <string>
#include <gflags/gflags.h>
#include <cstdio>
#include "config.h"

namespace base {

template<typename T>
static void setValue(T arr[], size_t length, const T& val)
{
    std::fill(arr, arr + length, val);
}

template<typename T, size_t N>
static void setValue(T (&arr)[N], const T& val)
{
    std::fill(arr, arr + N, val);
}

/* high performance light mutex 100x more than std::Mutex at least , implement the lock free 
 * std::mutex = 600ns~1.4us, the high performance light mutex = 13ns~30ns
 * http://preshing.com/20120226/roll-your-own-lightweight-mutex/
 */
class ScopeSpinLock {
    std::atomic_flag locked = ATOMIC_FLAG_INIT ;
public:
    ScopeSpinLock() {
        lock();
    }

    ~ScopeSpinLock() {
        if(!locked.test_and_set(std::memory_order_acquire)){
            unlock();
        }
    }

private:
    void lock() {
        while (locked.test_and_set(std::memory_order_acquire)) { ; }
    }

    void unlock() {
        locked.clear(std::memory_order_release);
    }
};

}

#endif