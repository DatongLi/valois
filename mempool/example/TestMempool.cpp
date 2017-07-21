#include "mempool.h"

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

int main() {
    base::Mempool<Node> mpool(10);
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