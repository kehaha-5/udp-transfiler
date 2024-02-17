#include <sys/types.h>

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
    // debug_log("ack will be add timer %lu", ack);
    if (it == _ackMsgMap.end()) {
        warn_log(" setCbByAck ack %lu not be found ackMap size is %i", ack, _ackMsgMap.size());
        return;
    }
    it->second = _timerPtr->runEvery(SEND_PACKAGE_TIMEOUT, cb);
}

void AckSet::delMsgByAck(const u_long& ack) {
    std::lock_guard<std::mutex> lock_guard(_ackMsgMapLock);
    // debug_log("ack will be del %lu", ack);
    auto it = _ackMsgMap.find(ack);
    if (it == _ackMsgMap.end()) {  // ack可能被重发了有其它线程处理了
        warn_log(" delMsgByAck ack %lu not be found ackMap size is %i", ack, _ackMsgMap.size());
        return;
    }
    _timerPtr->cancelTimerEven(it->second);
    _ackMsgMap.erase(ack);
    AckRandom::releasesAck(ack);
}