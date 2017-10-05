//
// Created by Li,Datong on 28/09/2017.
//

#ifndef PROJECT_CHANNEL_H
#define PROJECT_CHANNEL_H

namespace valois {
namespace net {

class ChannelOption {
friend class Channel;
public:
    ChannelOption() {}

    virtual ~ChannelOption() {}

    int SetCb(std::function<void(std::string)> &cb) {
        _cb = cb;
        return 0;
    }

    int SetAddress(std::string &add) {
        _remote_add = std::move(add);
        return 0;
    }

    int SetPort(int port) {
        _remote_port = port;
        return 0;
    }

private:
    std::function<void(std::string)> _cb;
    std::string _remote_add;
    int _remote_port;
};

class Channel {
public:
    Channel() {}
    virtual ~Channel() {}
    int Init(ChannelOption *opt);
    int Call(const std::string& msg);
private:
    std::function<void(std::string)> _cb;
};

}
}

#endif //PROJECT_CHANNEL_H
