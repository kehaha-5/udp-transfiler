
#include "Buffer.h"
#include "msg/Msg.h"

using namespace msg;

void Buffer::setData(Package& package) {
    if (!_init) {
        _data.resize(package.tatolSzie);
        _ack = package.ack;
        _tatolLenght = package.tatolSzie;
        _msgType = package.msgType;
        _init = true;
    }
    package.data.copy(&_data[package.order * PALYLOAD_LEN], package.data.size());
    _hasRevLenght += package.dataLen;
}

void Buffer::clear() {
    if (!hasAllData()) {
        return;
    }
    _data.clear();
    _init = false;
    _ack = 0;
    _tatolLenght = 0;
    _hasRevLenght = 0;
}