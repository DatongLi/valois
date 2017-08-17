//
// Created by Li,Datong on 17/08/2017.
//

#ifndef PROJECT_EVENT_HANDLER_H
#define PROJECT_EVENT_HANDLER_H


class EventHandler {
public:
    ReadEvent(int fd, void *clientData, int mask);
    WriteEvent(int fd, void *clientData, int mask);

private:
    int fd;
};


#endif //PROJECT_EVENT_HANDLER_H
