#ifndef MEM_POOL_H
#define MEM_POOL_H
#include <atomic>
#include <cstdlib>
#include <cstring>
#include <list>
#include <memory>
#include <mutex>
#include <vector>

typedef std::vector<char> Mem;
struct Node;
struct NodeList;
typedef Node* NodePtr;

struct Node {
    NodePtr head;
    NodePtr next;
    Mem mem;
    char* get() { return mem.data(); }
};

struct NodeList {
    NodePtr tailPtr;
    NodePtr headPtr;
    int num;
    NodePtr pop() {
        NodePtr ptr = tailPtr;
        if (tailPtr == nullptr) {
            return nullptr;
        }
        num--;
        tailPtr = tailPtr->head;
        if (tailPtr == nullptr) {
            return ptr;
        }
        return ptr;
    }
    void push(NodePtr ptr) {
        if (headPtr == nullptr) {
            headPtr = ptr;
            tailPtr = ptr;
            num++;
            return;
        }
        ptr->head = tailPtr;
        tailPtr->next = ptr;
        tailPtr = ptr;
        num++;
    }
};

class MemPool {
   public:
    MemPool(int _size, int _initNum, int _maxNum);
    ~MemPool() {
        NodePtr curr = _nodeList.pop();
        while (curr != nullptr) {
            curr->mem.clear();
            curr->mem.shrink_to_fit();
            delete curr;
            curr = nullptr;
            curr = _nodeList.pop();
        }
    };
    NodePtr getMem();
    int getTotalSize() { return _totalSize; };
    void clear(NodePtr ptr);

   private:
    void initNodeList();
    void initNode();
    void adjustNode();
    NodeList _nodeList;
    int _initNum;
    int _maxNum;
    int _size;
    std::atomic_uint _totalSize = 0;
    std::mutex _nodeListLock;
};

#endif