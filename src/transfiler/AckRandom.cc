#include <random>
#include <unordered_set>

#include "AckRandom.h"

using namespace transfiler;

unqiueAck AckRandom::_set = std::unordered_set<u_long>{};
std::mutex AckRandom::_setLock;

u_long AckRandom::getAck() {
    std::random_device de;
    std::mt19937 engine(de());
    u_long ack = engine();
    auto res = insertMap(ack);
    while (!res) {
        ack = engine();
        res = insertMap(ack);
    }
    return ack;
}

bool AckRandom::insertMap(u_long ack) {
    std::lock_guard<std::mutex> lock(_setLock);
    auto res = _set.insert(ack);
    return res.second;
}

int AckRandom::releasesAck(u_long ack) {
    std::lock_guard<std::mutex> lock(_setLock);
    return _set.erase(ack);
}
