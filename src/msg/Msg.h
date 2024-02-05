#ifndef MSG_COMMAND_H
#define MSG_COMMAND_H
#include <sys/types.h>

#include <cassert>
#include <cmath>
#include <string>
#include <vector>

#include "Constant.h"
#include "Logging.h"
#include "file/server/Directory.h"
#include "msg/proto/command_msg.pb.h"
#include "msg/proto/fileinfos_msg.pb.h"
#include "msg/proto/package_msg.pb.h"

using namespace msg::proto;
namespace msg {

const u_int EXTENT_INFO_LEN = sizeof(u_long) + (sizeof(u_int) * 3) + 5;
const u_int PALYLOAD_LEN = MAX_MSG_LENGTH - EXTENT_INFO_LEN;

template <typename T>
inline bool basePaserAndValidateMsg(T& resqMsg, std::string& strData, std::string& errMsg) {
    if (!resqMsg.ParseFromString(strData)) {
        errMsg = "parse falut ";
        return false;
    }
    debug_log("str is %s", resqMsg.DebugString().c_str());
    if (!resqMsg.IsInitialized()) {
        errMsg = "require has not be set ";
        errMsg += resqMsg.InitializationErrorString();
        return false;
    }
    return true;
}

struct Package {
    u_long ack;       // 标识唯一一个信息 信息可能会被分成很多包
    u_int order;      // 此包在信息中的位置 0,1,2,3,4,5
    u_int tatolSzie;  // 整个信息的总长度
    u_int dataLen;    // 本次信息的长度
    ::MsgType msgType;
    std::string data;  // 数据
    void serialized(std::string* out) {
        PackageMsg resMsg;
        resMsg.set_ack(ack);
        resMsg.set_order(order);
        resMsg.set_datalen(dataLen);
        resMsg.set_tatolszie(tatolSzie);
        resMsg.set_data(data);
        resMsg.set_msgtype(msgType);
        assert(resMsg.ByteSizeLong() <= MAX_MSG_LENGTH);
        assert(resMsg.SerializeToString(out));
    }
    bool build(std::string& strData, std::string& errMsg) {
        PackageMsg resqMsg;
        if (!basePaserAndValidateMsg<PackageMsg>(resqMsg, strData, errMsg)) {
            return false;
        }
        if (!resqMsg.unknown_fields().empty()) {
            errMsg = "command type undefind";
            return false;
        }
        ack = resqMsg.ack();
        order = resqMsg.order();
        tatolSzie = resqMsg.tatolszie();
        dataLen = resqMsg.datalen();
        data = resqMsg.data();
        msgType = resqMsg.msgtype();
        return true;
    };
};

struct Command {
    CommandType command;
    std::string args;
    std::string msg;
    void serialized(std::string* out) {
        CommandMsg resMsg;
        resMsg.set_command(command);
        if (!msg.empty()) {
            resMsg.set_msg(msg);
        }
        if (!args.empty()) {
            resMsg.set_args(args);
        }
        assert(resMsg.SerializeToString(out));
    };
    bool build(std::string& strData, std::string& errMsg) {
        CommandMsg resqMsg;
        if (!basePaserAndValidateMsg<CommandMsg>(resqMsg, strData, errMsg)) {
            return false;
        }
        if (!resqMsg.unknown_fields().empty()) {
            errMsg = "command type undefind";
            return false;
        }
        if ((resqMsg.command() == COMMAND_ERRORMSG) && resqMsg.msg().empty()) {
            errMsg = "no err msg form error command";
            return false;
        }
        if ((resqMsg.command() == COMMAND_DOWNFILE) && resqMsg.args().empty()) {
            errMsg = "downfile without args";
            return false;
        }
        command = resqMsg.command();
        args = resqMsg.args();
        msg = resqMsg.msg();
        return true;
    }
};

struct FileInfos {
    file::server::filesInfo infos = {};
    void serialized(std::string* out) {
        FileInfoMsg resMsg;
        for (auto& it : infos) {
            auto data = resMsg.add_fileinfos();
            data->set_name(it.name);
            data->set_size(it.size);
            data->set_last_write_time(it.last_write_time);
        }
        assert(resMsg.SerializeToString(out));
    };
    bool build(std::string& strData, std::string& errMsg) {
        FileInfoMsg resqMsg;
        if (!basePaserAndValidateMsg<FileInfoMsg>(resqMsg, strData, errMsg)) {
            return false;
        }
        for (int i = 0; i < resqMsg.fileinfos_size(); i++) {
            auto fileinfo = resqMsg.fileinfos(i);
            file::server::fileInfo tmp = {fileinfo.last_write_time(), fileinfo.size(), fileinfo.name()};
            infos.push_back(tmp);
        }
        return true;
    }
};

inline std::vector<Package> getsubcontractInfo(std::string& seriallizeStr, u_long ack, MsgType type) {
    double tatolSzie = seriallizeStr.size();
    double tatolPackges = std::ceil(tatolSzie / PALYLOAD_LEN);
    std::vector<Package> msgs;
    msgs.resize(tatolPackges);
    int startPos = 0;
    u_short order = 0;
    for (auto& it : msgs) {
        it.tatolSzie = tatolSzie;
        if ((PALYLOAD_LEN + startPos) <= tatolSzie) {
            it.data = seriallizeStr.substr(startPos, PALYLOAD_LEN);
            it.dataLen = PALYLOAD_LEN;
        } else {
            it.data = seriallizeStr.substr(startPos, tatolSzie - startPos);
            it.dataLen = tatolSzie - startPos;
        }
        it.ack = ack;
        it.order = order;
        it.msgType = type;
        order++;
        startPos += PALYLOAD_LEN;
    }
    return msgs;
}

}  // namespace msg

#endif