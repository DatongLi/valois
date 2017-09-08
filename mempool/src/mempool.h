#include "base/common.h"
#include "base/pool.h"
#include "base/ring.h"

#ifndef _MEMPOOL_H
#define _MEMPOOL_H
namespace valois {
namespace base {

template<class T>
class MemPool : public Pool<T> {
public:
    MemPool() : _elem_num(0), _used_num(0) {}

    MemPool(long elem_num) :
    _elem_num(elem_num), _used_num(0)
    {
        if(false == createPool(elem_num)) {
            std::cout << "init pool failed" << std::endl;
        }
    }

    ~MemPool() {
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
    MemPool(const MemPool&) = delete;

    bool getElem(T* &elem);
    bool putElem(T* elem);

private:
    bool createPool(long elem_num);

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
    //SpinLock _list_lock; /*no need for global lock, promote performance in the same time get&put*/
};

template<class T>
bool MemPool<T>::createPool(long elem_num) {
    T *p;
    _freelist = new Ring<T *>(elem_num);
#if 1
    char *_buf = new char[alignSizeOf(sizeof(T)) * elem_num];
    if(nullptr == _buf) {return false;}
    for(long i = 0; i < elem_num; ++i) {
        // always get the same addr, so need to add i when push
        p = new (_buf + sizeof(T) + _align_gap) T();
        if(false == _freelist->push(p + i)) {
            std::cout << "list push failed" << std::endl;
            return false;
        }
    }
#else
    for(long i = 0; i < elem_num; ++i) {
        p = new T();
        if(false == _freelist->push(p)) {
            std::cout << "list push failed" << std::endl;
            return false;
        }
    }
#endif
    return true;
}

template<class T>
bool MemPool<T>::getElem(T* &elem) {
    ScopeSpinLock _list_lock;
    if(_used_num.load(std::memory_order_acquire) < _elem_num && _elem_num > 0) {
        _used_num.fetch_add(1, std::memory_order_release);
        elem = _freelist->pop();
    } else {
        std::cout << "mempool empty" << std::endl;
        return false;
    }
    return true;
}

template<class T>
bool MemPool<T>::putElem(T *elem) {
    ScopeSpinLock _list_lock;
    if(_used_num.load(std::memory_order_acquire) > 0 && _elem_num > 0) {
        _used_num.fetch_sub(1, std::memory_order_release);
        _freelist->push(elem);
    } else {
        std::cout << "mempool full" << std::endl;
        return false;
    }
    return true;
}
}
}
#endif