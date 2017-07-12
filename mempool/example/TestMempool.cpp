#include "mempool.h"

class Node {
public:
    bool SetCnt(int cnt) { _cnt = cnt; return true; }
    int GetCnt() { return _cnt;}

private:
    int _cnt;
};

int main() {
    Mempool<Node> mpool(10);
    Node *node = mpool.GetElem();
    node->SetCnt(3);
    std::cout << "cnt = " << node->GetCnt() << std::endl;
    mpool.PutElem(node);
    std::cout << "end" << std::endl;
    return 0;
}