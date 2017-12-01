#include "Common.h"
#include <ev++.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <list>

class TcpClient {
public:
    TcpClient(const char* ip,int port) : stop_(false), Bps_stat_(0), Qps_stat_(0) {
        fd_ = common::NewTcpClient(ip, port);
        m_io.set(fd_, ev::READ);
        m_io.set<TcpClient, &TcpClient::CallBack>(this);
        m_io.start();

        sio.set<TcpClient, &TcpClient::SignalCb>(this);
        sio.start(SIGINT);
        thread_ = new std::thread(&TcpClient::KeepEcho, this, fd_);
    }

    void Join() {
        thread_->join();
    }

    void CallBack(ev::io &watcher, int revents) {
        char       buffer[1024];
        ssize_t   nread = recv(fd_, buffer, sizeof(buffer), 0);
        if (nread < 0) {
            return;
        } else if (nread > 0) {
            //std::cout << "Echo Response : " << buffer;
        }
    }

    void SignalCb(ev::sig &signal, int revents) {
        stop_ = true;
        signal.loop.break_loop();
    }

    uint64_t GetBps() {
        return Bps_stat_.load(std::memory_order_acquire);
    }

    void SetBps(uint64_t v) {
        Bps_stat_.store(v, std::memory_order_release);
    }

    uint64_t GetQps() {
        return Qps_stat_.load(std::memory_order_acquire);
    }

    void SetQps(uint64_t v) {
        Qps_stat_.store(v, std::memory_order_release);
    }

private:
    void KeepEcho(int fd) {
        char buf[] = "hello world";
        common::Buffer *buffer = new common::Buffer(buf, strlen(buf));
        while(!stop_) {
            ssize_t written = write(fd, buffer->dpos(), buffer->nbytes());
            if (written != strlen(buf)) {
                continue;
            }
            Bps_stat_.fetch_add(written, std::memory_order_relaxed);
            Qps_stat_.fetch_add(1, std::memory_order_relaxed);
        }
    }

    ev::io m_io;
    ev::sig sio;
    int fd_;
    std::atomic<uint64_t> Bps_stat_;
    std::atomic<uint64_t> Qps_stat_;
    std::thread *thread_;
    bool stop_;
};

class TcpStat {
public:
    TcpStat() : Bps_stat_(0), Qps_stat_(0) {}
    virtual ~TcpStat() {}

    void AddStat(TcpClient *cli) {
        cli_list.push_back(cli);
    }

    void Start() {
        thread_ = new std::thread(&TcpStat::Run, this);
    }

    void Run() {
        while(1) {
            for(auto cli : cli_list) {
                Bps_stat_ += cli->GetBps();
                Qps_stat_ += cli->GetQps();
                cli->SetBps(0);
                cli->SetQps(0);
            }
            std::cout << "Sending Bps = " << Bps_stat_ << ", qps = " << Qps_stat_ << std::endl;
            Bps_stat_ = 0;
            Qps_stat_ = 0;
            sleep(1);
        }
    }
private:
    std::list<TcpClient *> cli_list;
    uint64_t Bps_stat_;
    uint64_t Qps_stat_;
    std::thread *thread_;
};


int main() {
    int cli_num = 4;
    std::list<TcpClient *> cli_list;
    TcpStat tcpStat;
    ev::default_loop loop;
    while(cli_num) {
        TcpClient *tcpClient = new TcpClient("127.0.0.1", 7770);
        cli_list.push_back(tcpClient);
        tcpStat.AddStat(tcpClient);
        cli_num--;
    }
    tcpStat.Start();
    loop.run(0);
    for(auto cli : cli_list) {
        cli->Join();
    }
    return 0;
}
