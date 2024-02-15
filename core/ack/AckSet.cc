#include <sys/types.h>

#include <cassert>
#include <mutex>

#include "AckSet.h"
#include "Constant.h"
#include "Logging.h"
#include "ack/AckRandom.h"

using namespace ack;

u_long AckSet::getAck() {
    std::lock_guard<std::mutex> lock_guard(_ackMsgMapLock);
    auto ack = AckRandom::getAck();
    _ackMsgMap.insert({ack, 0});
    return ack;
}

void AckSet::setCbByAck(u_long& ack, Cb cb) {
    std::lock_guard<std::mutex> lock_guard(_ackMsgMapLock);
    auto it = _ackMsgMap.find(ack);
    if (it == _ackMsgMap.end()) {
        warn_log("ack %lu not be found ackMap size is %i", ack, _ackMsgMap.size());
        return;
    }
    it->second = _timerPtr->runEvery(SEND_PACKAGE_TIMEOUT, cb);
}

void AckSet::delMsgByAck(const u_long& ack) {
    std::lock_guard<std::mutex> lock_guard(_ackMsgMapLock);
    auto it = _ackMsgMap.find(ack);
    assert(it != _ackMsgMap.end());
    _timerPtr->cancelTimerEven(it->second);
    _ackMsgMap.erase(ack);
    AckRandom::releasesAck(ack);
}