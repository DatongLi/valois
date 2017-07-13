
#ifndef _COMMON_H
#define _COMMON_H

#include <iostream>
#include <vector>
#include <queue>
#include <atomic>
#include <cmath>
#include <algorithm>
#include <array>
#include <mutex>

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

class SpinLock {
    std::atomic_flag locked = ATOMIC_FLAG_INIT ;
public:
    ~SpinLock() {
        unlock();
    }

    void lock() {
        while (locked.test_and_set(std::memory_order_acquire)) { ; }
    }
    void unlock() {
        locked.clear(std::memory_order_release);
    }
};

}

#endif