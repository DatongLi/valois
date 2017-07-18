/*
 * lock-free queue 
 */

#include "common.h"

#ifndef _RING_H
#define _RING_H

namespace base {

template<typename T>
class Ring {
public:
    Ring():_arr(nullptr), _head(0), _tail(0), len(0) {};
    Ring(long ring_len):_head(0), _tail(0), len(ring_len) {
        if(createRing(ring_len) == false) {
            std::cout << "create ring failed" << std::endl;
        }
    }

    ~Ring() {
        delete[] _arr;
    }

    bool createRing(long ring_len) {
        _arr = new T[len];
        if(_arr == nullptr) return false;
        for(int i = 0; i < len; ++i) {
            _arr[i] = nullptr;
        }
        return true;
    }

    bool resizeRing(long ring_len) {
        std::lock_guard<std::mutex> lock(_arr_lock);
        if(len > ring_len) return false;
        T *_new_arr = new T[ring_len];
        int _new_head = ring_len - 1;
        int _new_tail = ring_len - 1;
        while(false != isEmpty()) {
            _new_arr[_new_tail] = _arr[_head];
            --_new_tail;
            _arr[_head] = nullptr;
            _head = (_head - 1 + len) % len;
        }
        _head = _new_head;
        _tail = _new_tail;
        len = ring_len;
        delete[] _arr;
        _arr = _new_arr;
        return true;
    }

    bool isEmpty() {
        return (_head - _tail - 1 + len) % len == 0;
    }

    bool isFull() {
        return (_head - _tail + 1 + len) % len == 0;
    }

    long size() {
        return (_head - _tail - 1 + len) % len;
    }

    T pop() {
        SpinLock _lock;
        if((_head - _tail - 1 + len) % len == 0) return nullptr;
        //std::cout << "head " << _head << std::endl;
        //std::cout << "pop " << _arr[_head] << std::endl;
        T cur = _arr[_head];
        _arr[_head] = nullptr;
        _head = (_head - 1 + len) % len;
        return cur;
    }

    bool push(const T &tp) {
        SpinLock _lock;
        if((_head - _tail + 1 + len) % len == 0) return false;
        if(_head == _tail) {
            if(nullptr == _arr[_head]) {
                _arr[_tail] = tp;
                return true;
            }
        }
        _tail = (_tail - 1 + len) % len;
        _arr[_tail] = tp;
        //std::cout << "push success " << tp << " head = " << _head << " tail = " << _tail << std::endl;
        return true;
    }

private:
    T *_arr;
    std::mutex _arr_lock;
    int _head;
    int _tail;
    long len;
};

}

#endif