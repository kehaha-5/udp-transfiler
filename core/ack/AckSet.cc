#include <sys/types.h>

#include <cassert>
#include <mutex>

#include "AckSet.h"
#include "ack/AckRandom.h"

using namespace ack;

u_long AckSet::getAck(std::string msg) {
    auto ack = AckRandom::getAck();
    {
        std::lock_guard<std::mutex> lock_guard(_ackMsgMapLock);
        _ackMsgMap.insert({ack, msg});
    }
    return ack;
}

std::string& AckSet::getMsgByAck(u_long& ack) {
    AckMsgMap::iterator it;
    {
        std::lock_guard<std::mutex> lock_guard(_ackMsgMapLock);
        it = _ackMsgMap.find(ack);
    }
    assert(it != _ackMsgMap.end());
    return it->second;
}

void AckSet::delMsgByAck(const u_long& ack) {
    {
        std::lock_guard<std::mutex> lock_guard(_ackMsgMapLock);
        _ackMsgMap.erase(ack);
    }
}