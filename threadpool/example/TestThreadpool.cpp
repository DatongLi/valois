#include "threadpool.h"
#include "stdio.h"

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

int main() {
    base::ThreadPool tpool;
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
    return 0;
}