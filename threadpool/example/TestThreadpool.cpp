#include "threadpool.h"

void printA() {
    std::cout << "AAA" << std::endl;
}

void printB() {
    std::cout << "BBB" << std::endl;
}

int main() {
    base::Threadpool tpool;
    tpool.submit(printA);
    tpool.submit(printB);
    tpool.submit(printB);
    tpool.submit(printA);
    tpool.join();
    return 0;
}