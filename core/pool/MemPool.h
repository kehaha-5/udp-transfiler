#ifndef MEM_POOL_H
#define MEM_POOL_H
#include <atomic>
#include <cstdlib>
#include <cstring>
#include <list>
#include <memory>
#include <mutex>
#include <vector>

namespace pool {
typedef std::vector<char> Mem;
struct Node;
struct NodeList;
typedef Node* MemPtr;

struct Node {
    MemPtr head;
    MemPtr next;
    Mem mem;
    char* get() { return mem.data(); }
};

struct NodeList {
    MemPtr tailPtr;
    MemPtr headPtr;
    int num;
    MemPtr pop() {
        MemPtr ptr = tailPtr;
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
    void push(MemPtr ptr) {
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
        MemPtr curr = _nodeList.pop();
        while (curr != nullptr) {
            curr->mem.clear();
            curr->mem.shrink_to_fit();
            delete curr;
            curr = nullptr;
            curr = _nodeList.pop();
        }
    };
    MemPtr getMem();
    int getTotalSize() { return _totalSize; };
    void clear(MemPtr ptr);

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

}  // namespace pool
#endif