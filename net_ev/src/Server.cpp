#include "Common.h"
#include <ev++.h>
#include <iostream>
#include <list>

class TcpClientInstant {
public:
    TcpClientInstant(int fd) : fd_(fd) {
        common::setnonblock(fd);
        io_.set(fd, ev::READ);
        io_.set<TcpClientInstant, &TcpClientInstant::CallBack>(this);
        io_.start();
    }
private:
    void CallBack(ev::io &watcher, int revents) {
        if (EV_ERROR & revents) {
            std::cout << "EV error in echo stub" << std::endl;
            return;
        }
        if (revents & EV_READ) {
            ReadCb(watcher);
        }
        if (revents & EV_WRITE) {
            WriteCb(watcher);
        }
        if (write_queue.empty()) {
            io_.set(ev::READ);
        } else {
            io_.set(ev::READ | ev::WRITE);
        }
    }

    void WriteCb(ev::io &watcher) {
        if (write_queue.empty()) {
            io_.set(ev::READ);
            return;
        }
        common::Buffer* buffer = write_queue.front();
        ssize_t written = write(fd_, buffer->dpos(), buffer->nbytes());
        if (written < 0) {
            return;
        }
        buffer->pos += written;
        if (buffer->nbytes() == 0) {
            write_queue.pop_front();
            delete buffer;
        }
    }

    void ReadCb(ev::io &watcher) {
        char       buffer[1024];
        ssize_t   nread = recv(watcher.fd, buffer, sizeof(buffer), 0);
        if (nread < 0) {
            return;
        } else if (nread == 0) {
            return;
        } else {
            //std::cout << "Server Read buffer : " << buffer << std::endl;
            write_queue.push_back(new common::Buffer(buffer, nread));
        }
    }

    ev::io io_;
    std::list<common::Buffer*>     write_queue;
    int fd_;
};

class TcpEchoServer {
public:
    TcpEchoServer(int port) {
        fd_ = common::NewTcpServer(port);
        m_io.set(fd_, ev::READ);
        m_io.set<TcpEchoServer, &TcpEchoServer::Accept>(this);
        m_io.start();
    }

    void Accept(ev::io &watcher, int revents) {
        if (EV_ERROR & revents) {
            std::cout << "EV error" << std::endl;
            return;
        }
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(watcher.fd, (struct sockaddr *)&client_addr, &client_len);
        if(client_fd < 0) {
            std::cout <<  "client fd error !" << std::endl;
            return;
        }
        TcpClientInstant *echoStub  = new TcpClientInstant(client_fd);
    }

private:
    ev::io m_io;
    int fd_;
};

int main() {
    ev::default_loop loop;
    TcpEchoServer echo_server(7770);
    loop.run(0);
    return 0;
}
