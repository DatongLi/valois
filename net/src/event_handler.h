//
// Created by Li,Datong on 17/08/2017.
//

#ifndef PROJECT_EVENT_HANDLER_H
#define PROJECT_EVENT_HANDLER_H


class EventHandler {
public:
    int ReadEvent(int fd, void *clientData, int mask) = 0;
    int WriteEvent(int fd, void *clientData, int mask) = 0;
};


#endif //PROJECT_EVENT_HANDLER_H
