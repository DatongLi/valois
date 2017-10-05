//
// Created by Li,Datong on 28/09/2017.
//

#ifndef PROJECT_GLOBAL_H
#define PROJECT_GLOBAL_H
namespace valois {
namespace net {
    int globalInit(int &argc, char *argv[]) {
        google::InitGoogleLogging(argv[0]);
        FLAGS_log_dir = "log";
        google::SetLogDestination(google::GLOG_INFO, "log/INFO_");
        google::SetStderrLogging(google::GLOG_INFO);
        google::SetLogFilenameExtension("log_");
        FLAGS_colorlogtostderr = true;              // Set log color
        FLAGS_logbufsecs = 0;                       // Set log output speed(s)
        FLAGS_max_log_size = 1024;                  // Set max log file size
        FLAGS_stop_logging_if_full_disk = true;     // If disk is full

        gflags::ParseCommandLineFlags(&argc, &argv, true);

        return 0;
    }

    int globalClean() {
        google::ShutdownGoogleLogging();
        return 0;
    }
}
}
#endif //PROJECT_GLOBAL_H
