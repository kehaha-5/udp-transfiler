#include <cstddef>
#include <cstdio>
#include <iostream>
#include <memory>
#include <mutex>

#include "MenPool.h"

MenPool::MenPool(int size, int initNum, int maxNum) : _size(size), _initNum(initNum), _maxNum(maxNum) {
    _nodeList = {nullptr, nullptr, 0};
    initNodeList();
}
void MenPool::initNodeList() {
    initNode();
    for (int i = 1; i < _initNum; i++) {
        initNode();
    }
}

void MenPool::initNode() {
    _totalSize += _size;
    Men men = Men{0};
    men.resize(_size);
    NodePtr nodePtr = new Node();
    nodePtr->men = men;
    _nodeList.push(nodePtr);
}

NodePtr MenPool::getMen() {
    std::lock_guard<std::mutex> lock(_nodeListLock);
    NodePtr curr = _nodeList.pop();
    if (curr == nullptr) {
        initNode();
        return _nodeList.pop();
    }
    return curr;
}

void MenPool::adjustNode() {
    while (_nodeList.num > _maxNum) {
        NodePtr curr = _nodeList.pop();
        curr->men.clear();
        curr->men.shrink_to_fit();
        delete curr;
        curr = nullptr;
        _totalSize -= _size;
    }
}

void MenPool::clear(NodePtr ptr) {
    std::lock_guard<std::mutex> lock(_nodeListLock);
    printf("msg is %s and the msg addr is %p and is gonging destroy \n", ptr->get(), ptr->get());
    std::memset(ptr->get(), 0, _size);
    _nodeList.push(ptr);
    adjustNode();
}