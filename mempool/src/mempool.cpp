#include "mempool.h"

template<class T>
T* Mempool<T>::GetElem() {
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
bool Mempool<T>::PutElem(T *elem) {
    _used_num.fetch_sub(1, std::memory_order_release);
    _freelist.push(elem);
    return true;
}