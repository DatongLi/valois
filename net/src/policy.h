//
// Created by Li,Datong on 23/09/2017.
//

#ifndef PROJECT_POLICY_H
#define PROJECT_POLICY_H

namespace valois {
namespace net {
    class Policy {
    public:
        virtual ~UserHandler() = default;

        virtual int Parse() = 0;

        virtual int Send() = 0;

        virtual int Recv() = 0;

        virtual int Pack() = 0;
    };
}
}

#endif //PROJECT_POLICY_H
