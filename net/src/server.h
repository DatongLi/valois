//
// Created by Li,Datong on 28/09/2017.
//

#ifndef PROJECT_SERVER_H
#define PROJECT_SERVER_H


class ServerOption {
public:
    ServerOption() {}

    virtual ~ServerOption() {}

    int SetProcess(std::function<void()>& process) {
        _process = process;
        return 0;
    }
private:
    std::function<void()> _process;
};

class Server {
public:
    Server() {}
    virtual ~Server() {}
    int Start();

private:
    ServerOption *opt;
};


#endif //PROJECT_SERVER_H
