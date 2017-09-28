//
// Created by Li,Datong on 23/09/2017.
//

#ifndef PROJECT_POLICY_H
#define PROJECT_POLICY_H


class Policy {
public:
    virtual ~UserHandler() = default;
    virtual Parse() = 0;
    virtual Send() = 0;
    virtual Recv() = 0;
    virtual Pack() = 0;
};


#endif //PROJECT_POLICY_H
