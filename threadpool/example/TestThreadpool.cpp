#include "threadpool.h"
#include "base/common.h"
void* printA(void *arg) {
    int tid = *(int *)arg;
    std::cout << "AAA in " << tid << std::endl;
    return nullptr;
}

void* printB(void *arg) {
    int tid = *(int *)arg;
    std::cout << "BBB in " << tid << std::endl;
    return nullptr;
}

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

int main(int argc, char** argv) {
    globalInit(argc, argv);
    LOG(INFO) << "main begin";
    valois::base::ThreadPool tpool;
    int a = 0;
    tpool.submit(printA, (void *)&(a));
    int b = 1;
    tpool.submit(printB, (void *)&(b));
    int c = 3;
    tpool.submit(printB, (void *)&(c));
    int d = 5;
    tpool.submit(printB, (void *)&(d));
    tpool.submit(printA, (void *)&(d));
    tpool.join();
    globalClean();
    return 0;
}