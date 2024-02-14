
#include "Buffer.h"
#include "msg/Msg.h"

using namespace msg;

void Buffer::setData(std::string &msg) {
    msg::Package packageMsg;
    std::string errMsg;
    if (!packageMsg.build(msg, errMsg)) {
        warn_log("package msg build fault %s", errMsg.c_str());
        return;
    }
    if (!_init) {
        _data.resize(packageMsg.tatolSzie);
        _ack = packageMsg.ack;
        _tatolLenght = packageMsg.tatolSzie;
        _msgType = packageMsg.msgType;
        _init = true;
    }
    packageMsg.data.copy(&_data[packageMsg.order * PALYLOAD_LEN], packageMsg.data.size());
    _hasRevLenght += packageMsg.dataLen;
}

void Buffer::setData(Package &msg) {
    if (!_init) {
        _data.resize(msg.tatolSzie);
        _ack = msg.ack;
        _tatolLenght = msg.tatolSzie;
        _msgType = msg.msgType;
        _init = true;
    }
    msg.data.copy(&_data[msg.order * PALYLOAD_LEN], msg.data.size());
    _hasRevLenght += msg.dataLen;
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