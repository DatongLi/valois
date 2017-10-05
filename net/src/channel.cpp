//
// Created by Li,Datong on 28/09/2017.
//

#include "channel.h"
#include "event_loop.h"

namespace valois {
namespace net {

    int Channel::Init(ChannelOption *opt) {
        GetGlobalLoop();
        _cb = opt->_cb;
        return 0;
    }

    int Channel::Call(const std::string &msg) {


        GetGlobalLoop();

        return 0;
    }
}
}