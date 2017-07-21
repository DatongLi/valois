g++ -g -O0 -o mempool/output/TestMempool mempool/example/TestMempool.cpp -I. -Imempool/src -std=c++11
#g++ -g -O0 -o threadpool/output/TestThreadpool threadpool/example/TestThreadpool.cpp -I. -Ithreadpool/src -lpthread -std=c++11
#g++ -g -O0 -o mempool/unittest/test mempool/unittest/test.cpp -I./mempool -I./mempool/src -Ithird-64/gtest/include -Ithird-64/gtest -Lthread-64/gtest -lpthread -pthread