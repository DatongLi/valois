#include "base/common.h"
#include "base/pool.h"
#include "base/ring.h"

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
        for(int i = 0; i < _freelist->size(); ++i) {
            elem = _freelist->pop();
            elem->~T();
        }
        delete _freelist;
        _freelist = nullptr;
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
    Ring<T *> *_freelist;
};

template<class T>
bool Mempool<T>::createPool(long elem_num) {
    T *p;
    _freelist = new Ring<T *>(elem_num);
    char *_buf = new char[alignSizeOf(sizeof(T)) * elem_num];
    if(_buf == nullptr) {return false;}
    for(long i = 0; i < elem_num; ++i) {
        // always get the same addr, so need to add i when push
        p = new (_buf + sizeof(T) + _align_gap) T();
        if(false == _freelist->push(p + i)) {
            std::cout << "list push failed" << std::endl;
            return false;
        }
    }
    return true;
}

template<class T>
T* Mempool<T>::getElem() {
    long unum = _used_num.load(std::memory_order_acquire);
    if(unum < _elem_num && _elem_num > 0) {
        _used_num.fetch_add(1, std::memory_order_relaxed);
        T* elem = _freelist->pop();
        return elem;
    } else {
        std::cout << "mempool empty" << std::endl;
        return nullptr;
    }
}

template<class T>
bool Mempool<T>::putElem(T *elem) {
    long unum = _used_num.load(std::memory_order_acquire);
    if(unum < _elem_num && _elem_num > 0) {
        _used_num.fetch_sub(1, std::memory_order_relaxed);
        _freelist->push(elem);
    } else {
        std::cout << "mempool full" << std::endl;
        return false;
    }
    return true;
}

}
#endif