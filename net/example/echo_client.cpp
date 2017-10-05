//
// Created by Li,Datong on 23/09/2017.
//

#include "echo.pb.h"
#include "protobuf_policy.h"

using namespace std;
using namespace valois::net;
void CallBack(string &msg) {
    cout << " id = " << msg.id() << " info = " << msg.info() << endl;
}

int main(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    ChannelOption opt;
    opt.SetCb(bind(&CallBack, placeholders::_1));
    opt.SetAddress("127.0.0.1");
    opt.SetPort(8001);
    Channel _chan(&opt);

    string out;
    example::Hello hel;
    hel.set_id(10);
    string x("xxx");
    hel.set_info(x);
    hel.SerializeToString(&out);
    _chan.Call(out);
    return 0;
}