//
// Created by Li,Datong on 23/09/2017.
//

#ifndef PROJECT_USER_HANDLER_H
#define PROJECT_USER_HANDLER_H


class UserHandler {
public:
    virtual ~UserHandler() = default;
    virtual RequestParse() = 0;
    virtual RequestProcess() = 0;
    virtual Response() = 0;
};


#endif //PROJECT_USER_HANDLER_H
