#include "base/common.h"
#include "base/pool.h"

#ifndef _MEMPOOL_H
#define _MEMPOOL_H

namespace base {

template<class T>
class Mempool : public Pool<T> {
public:
    Mempool() : _used_num(0), _elem_num(0) {}

    Mempool(long elem_num) :
    _used_num(0), _elem_num(elem_num)
    {
        if(false == createPool(elem_num)) {
            std::cout << "init pool failed" << std::endl;
        }
    }

    ~Mempool() {
        if(_used_num > 0) {
            std::cout << "Failed to release all elem in mempool, memory leak!" << std::endl;
        }
        T *elem;
        for(int i = 0; i < _freelist.size(); ++i) {
            elem = _freelist.front();
            _freelist.pop();
            elem->~T();
        }
    }
    Mempool(const Mempool&) = delete;

    bool createPool(long elem_num);

    T* getElem();
    bool putElem(T* elem);

private:
    int alignSizeOf(int object_size) {
        int size = floor(log2(object_size)) + 1;
        int real_size = exp2(size);
        _align_gap = real_size - object_size;
        return real_size;
    }

    int _align_gap;
    long _elem_num;
    std::atomic<long> _used_num;
    std::queue<T *> _freelist;
};

template<class T>
bool Mempool<T>::createPool(long elem_num) {
    char *_buf = new char[alignSizeOf(sizeof(T)) * elem_num];
    if(_buf == nullptr) {return false;}
    for(long i = 0; i < elem_num; ++i) {
        _freelist.push(new (_buf + sizeof(T) + _align_gap) T());
    }
    return true;
}

template<class T>
T* Mempool<T>::getElem() {
    long unum = _used_num.load(std::memory_order_acquire);
    if(unum < _elem_num) {
        _used_num.fetch_add(1, std::memory_order_release);
        T* elem = _freelist.front();
        _freelist.pop();
        return elem;
    } else {
        std::cout << "mempool empty" << std::endl;
        return nullptr;
    }
}

template<class T>
bool Mempool<T>::putElem(T *elem) {
    _used_num.fetch_sub(1, std::memory_order_release);
    _freelist.push(elem);
    return true;
}
}
#endif