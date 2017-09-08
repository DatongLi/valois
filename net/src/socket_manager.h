//
// Created by Li,Datong on 22/08/2017.
//

#ifndef PROJECT_SOCKET_MANAGER_H
#define PROJECT_SOCKET_MANAGER_H

#include <gflags/gflags.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
namespace valois {
namespace net {

class Socket {
public:
    static void SetNonBlocking(int sock);
    static int BindSocket();
};

}
}

#endif //PROJECT_SOCKET_MANAGER_H
