#include <cstddef>
#include <cstdio>
#include <iostream>
#include <memory>
#include <mutex>

#include "MemPool.h"

MemPool::MemPool(int size, int initNum, int maxNum) : _size(size), _initNum(initNum), _maxNum(maxNum) {
    _nodeList = {nullptr, nullptr, 0};
    initNodeList();
}
void MemPool::initNodeList() {
    initNode();
    for (int i = 1; i < _initNum; i++) {
        initNode();
    }
}

void MemPool::initNode() {
    _totalSize += _size;
    Mem mem = Mem{0};
    mem.resize(_size);
    NodePtr nodePtr = new Node();
    nodePtr->mem = mem;
    _nodeList.push(nodePtr);
}

NodePtr MemPool::getMem() {
    std::lock_guard<std::mutex> lock(_nodeListLock);
    NodePtr curr = _nodeList.pop();
    if (curr == nullptr) {
        initNode();
        return _nodeList.pop();
    }
    return curr;
}

void MemPool::adjustNode() {
    while (_nodeList.num > _maxNum) {
        NodePtr curr = _nodeList.pop();
        curr->mem.clear();
        curr->mem.shrink_to_fit();
        delete curr;
        curr = nullptr;
        _totalSize -= _size;
    }
}

void MemPool::clear(NodePtr ptr) {
    std::lock_guard<std::mutex> lock(_nodeListLock);
    std::memset(ptr->get(), 0, _size);
    _nodeList.push(ptr);
    adjustNode();
}