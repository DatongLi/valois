
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

int main(int argc, char* argv[]) {
    gflags::SetUsageMessage("some usage message");
    gflags::SetVersionString("1.0.0");
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    base::MemPool<Node> mpool(FLAGS_elem_num);
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
    return 0;
}