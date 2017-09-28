//
// Created by Li,Datong on 28/09/2017.
//

#ifndef PROJECT_CHANNEL_H
#define PROJECT_CHANNEL_H


class ChannelOption {
public:
    ClientOption() {}

    virtual ~ClientOption() {}

    int SetCb(std::function<void()>& cb) {
        _cb = cb;
        return 0;
    }
private:
    std::function<void()> _cb;
};

class Channel {

};


#endif //PROJECT_CHANNEL_H
