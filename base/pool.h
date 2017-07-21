#ifndef _POOL_H
#define _POOL_H

#include "common.h"

namespace base {

template<class T>
class Pool {
public:
    virtual bool createPool(long elem_num) = 0;
    virtual bool getElem(T* &elem) = 0;
    virtual bool putElem(T* elem) = 0;
};

}

#endif