//
// Created by Li,Datong on 28/09/2017.
//

#ifndef PROJECT_PROTOBUF_POLICY_H
#define PROJECT_PROTOBUF_POLICY_H

#include "policy.h"
#include <google/protobuf/message.h>

namespace valois {
namespace net {

class PbPolicy {//: public Policy {
public:
    PbPolicy() {}

    virtual ~PbPolicy() {}

    int Parse();

    int Send(::google::protobuf::Message &msg);

    int Recv(::google::protobuf::Message &msg);

    int Pack();
};
}
}

#endif //PROJECT_PROTOBUF_POLICY_H
