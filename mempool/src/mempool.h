#include "base/common.h"

template<class T>
class Mempool {
public:
    Mempool(long elem_num) :
    _used_num(0), _elem_num(elem_num)
    {
        for(long i = 0; i < elem_num; ++i) {
            _freelist.push(new T());
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
            delete elem;
        }
    }
    Mempool(const Mempool&) = delete;

    T* GetElem();
    bool PutElem(T* elem);

private:
    long _elem_num;
    std::atomic<long> _used_num;
    std::queue<T *> _freelist;
};