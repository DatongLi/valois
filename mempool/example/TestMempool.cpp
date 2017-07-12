#include "mempool.h"

class Node {
public:
    bool setCnt(int cnt) { _cnt = cnt; return true; }
    int GetCnt() { return _cnt;}

private:
    int _cnt;
};

int main() {
    Mempool<Node> mpool(10);
    Node *node = mpool.GetElem();
    node->setCnt(3);
    mpool.PutElem(node);
    return 0;
}