
#include "mempool.h"

DEFINE_int32(elem_num, 10, "pool elem number");

class Node {
public:
    Node():_cnt(0) {}
    ~Node() {}

    bool SetCnt(int cnt) {
        _cnt = cnt; 
        return true; 
    }

    int GetCnt() { return _cnt;}

private:
    int _cnt;
};

int globalInit(int &argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_log_dir="log";
    google::SetLogDestination(google::GLOG_INFO, "log/INFO_");
    google::SetStderrLogging(google::GLOG_INFO);
    google::SetLogFilenameExtension("log_");
    FLAGS_colorlogtostderr = true;  // Set log color
    FLAGS_logbufsecs = 0;  // Set log output speed(s)
    FLAGS_max_log_size = 1024;  // Set max log file size
    FLAGS_stop_logging_if_full_disk = true;  // If disk is full

    gflags::ParseCommandLineFlags(&argc, &argv, true);

    return 0;
}

int globalClean() {
    google::ShutdownGoogleLogging();
    return 0;
}

int main(int argc, char* argv[]) {
    globalInit(argc, argv);
    gflags::SetUsageMessage("some usage message");
    gflags::SetVersionString("1.0.0");
    valois::base::MemPool<Node> mpool(FLAGS_elem_num);
    Node *node;
    mpool.getElem(node);
    node->SetCnt(3);
    std::cout << "cnt = " << node->GetCnt() << std::endl;
    mpool.putElem(node);

    mpool.getElem(node);
    node->SetCnt(5);
    std::cout << "cnt = " << node->GetCnt() << std::endl;
    mpool.putElem(node);
    std::cout << "end" << std::endl;
    globalClean();
    return 0;
}